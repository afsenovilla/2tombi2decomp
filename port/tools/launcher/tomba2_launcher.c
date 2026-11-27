/* tomba2-launcher.exe: the double-click start of the Windows build (docs/PORT.md §0.2).  Plain Win32 C (mingw-w64,
 * the normal C runtime: unlike tomba2.exe it is not freestanding).  The role of Tombi-Decomp's launcher
 * (tombi-port.exe, a PySide6 program; MIT, same author), cut to what a player needs and built without Python:
 *
 *   - asks once for the player's disc image (a file dialog: .bin / .img / .cue / .iso) and remembers it in
 *     tomba2-launcher.ini (next to the exe, or in %APPDATA%\Tomba2-port when that folder is not writable);
 *     hold Shift while starting it (or pass /choose) to pick another image;
 *   - runs tomba2.exe --disc IMAGE --window --save-dir SAVES [options= line of the .ini] without a console, the
 *     game's log in tomba2.log beside the .ini; memory cards in SAVES = saves\ beside the .ini;
 *   - when the game stops with an error (not the USA disc, an unreadable image, a crash) shows the FATAL line and
 *     offers to pick another image.
 * Nothing of the game is in it: tomba2.exe reads the disc image itself and checks MAIN.EXE by SHA-1. */
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <commdlg.h>
#include <shlobj.h>
#include <stdio.h>
#include <string.h>

static char exe_dir[MAX_PATH], base[MAX_PATH], ini[MAX_PATH], logp[MAX_PATH], saves[MAX_PATH];
static char disc[MAX_PATH], options[1024];

static int writable(const char *dir) {
    char t[MAX_PATH];
    snprintf(t, sizeof t, "%s\\tomba2-write-test.tmp", dir);
    HANDLE h = CreateFileA(t, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_TEMPORARY | FILE_FLAG_DELETE_ON_CLOSE, 0);
    if (h == INVALID_HANDLE_VALUE) return 0;
    CloseHandle(h);
    return 1;
}
static void load_ini(void) {
    FILE *f = fopen(ini, "r");
    char line[2048];
    if (!f) return;
    while (fgets(line, sizeof line, f)) {
        size_t n = strlen(line);
        while (n && (line[n - 1] == '\n' || line[n - 1] == '\r')) line[--n] = 0;
        if (!strncmp(line, "disc=", 5)) snprintf(disc, sizeof disc, "%s", line + 5);
        else if (!strncmp(line, "options=", 8)) snprintf(options, sizeof options, "%s", line + 8);
    }
    fclose(f);
}
static void save_ini(void) {
    FILE *f = fopen(ini, "w");
    if (!f) return;
    fprintf(f, "; Tomba! 2 port launcher settings (docs/PORT.md).  disc = your own disc image (.bin/.img/.cue/.iso).\n"
               "; options = extra tomba2.exe options, e.g. --viewer-arg --fullscreen  or  --viewer-arg --scale --viewer-arg 2\n");
    fprintf(f, "disc=%s\noptions=%s\n", disc, options);
    fclose(f);
}
static int exists(const char *p) { DWORD a = GetFileAttributesA(p); return a != INVALID_FILE_ATTRIBUTES && !(a & FILE_ATTRIBUTE_DIRECTORY); }
static int choose_disc(void) {
    OPENFILENAMEA o;
    char f[MAX_PATH];
    snprintf(f, sizeof f, "%s", disc);
    memset(&o, 0, sizeof o);
    o.lStructSize = sizeof o;
    o.lpstrFilter = "PlayStation disc images (*.bin;*.img;*.cue;*.iso)\0*.bin;*.img;*.cue;*.iso\0All files (*.*)\0*.*\0";
    o.lpstrFile = f;
    o.nMaxFile = sizeof f;
    o.lpstrTitle = "Tomba! 2 (USA) - choose your disc image";
    o.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY;
    if (!GetOpenFileNameA(&o)) return 0;
    snprintf(disc, sizeof disc, "%s", f);
    save_ini();
    return 1;
}
/* the last "[port] FATAL: ..." line of the log (or the last line) */
static void last_error(char *out, int n) {
    FILE *f = fopen(logp, "r");
    char line[1024], last[1024] = "";
    out[0] = 0;
    if (!f) return;
    while (fgets(line, sizeof line, f)) {
        size_t k = strlen(line);
        while (k && (line[k - 1] == '\n' || line[k - 1] == '\r')) line[--k] = 0;
        if (strstr(line, "FATAL")) snprintf(out, n, "%s", line);
        if (k) snprintf(last, sizeof last, "%s", line);
    }
    fclose(f);
    if (!out[0]) snprintf(out, n, "%s", last);
}
static DWORD run_game(void) {
    char cmd[4096], game[MAX_PATH];
    snprintf(game, sizeof game, "%s\\tomba2.exe", exe_dir);
    if (!exists(game)) {
        MessageBoxA(0, "tomba2.exe is missing: unzip the whole archive into one folder.", "Tomba! 2 port", MB_ICONERROR);
        return 1;
    }
    snprintf(cmd, sizeof cmd, "\"%s\" --disc \"%s\" --window --save-dir \"%s\" %s", game, disc, saves, options);
    SECURITY_ATTRIBUTES sa = { sizeof sa, 0, TRUE };
    HANDLE lg = CreateFileA(logp, GENERIC_WRITE, FILE_SHARE_READ, &sa, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
    STARTUPINFOA si; PROCESS_INFORMATION pi;
    memset(&si, 0, sizeof si);
    si.cb = sizeof si;
    si.dwFlags = STARTF_USESTDHANDLES;
    si.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
    si.hStdOutput = lg;
    si.hStdError = lg;
    if (!CreateProcessA(0, cmd, 0, 0, TRUE, CREATE_NO_WINDOW, 0, exe_dir, &si, &pi)) {
        char m[512];
        snprintf(m, sizeof m, "Cannot start %s (error %lu).", game, GetLastError());
        MessageBoxA(0, m, "Tomba! 2 port", MB_ICONERROR);
        if (lg != INVALID_HANDLE_VALUE) CloseHandle(lg);
        return 1;
    }
    if (lg != INVALID_HANDLE_VALUE) CloseHandle(lg);
    WaitForSingleObject(pi.hProcess, INFINITE);
    DWORD code = 1;
    GetExitCodeProcess(pi.hProcess, &code);
    CloseHandle(pi.hProcess); CloseHandle(pi.hThread);
    return code;
}

int WINAPI WinMain(HINSTANCE inst, HINSTANCE prev, LPSTR args, int show) {
    (void)inst; (void)prev; (void)show;
    GetModuleFileNameA(0, exe_dir, sizeof exe_dir);
    char *s = strrchr(exe_dir, '\\');
    if (s) *s = 0;
    snprintf(base, sizeof base, "%s", exe_dir);
    if (!writable(base)) {   /* e.g. unzipped under Program Files: settings, saves and the log go to %APPDATA% */
        char app[MAX_PATH];
        if (SHGetFolderPathA(0, CSIDL_APPDATA, 0, 0, app) == S_OK) {
            snprintf(base, sizeof base, "%s\\Tomba2-port", app);
            CreateDirectoryA(base, 0);
        }
    }
    snprintf(ini, sizeof ini, "%s\\tomba2-launcher.ini", base);
    snprintf(logp, sizeof logp, "%s\\tomba2.log", base);
    snprintf(saves, sizeof saves, "%s\\saves", base);
    CreateDirectoryA(saves, 0);
    load_ini();
    int choose = (GetAsyncKeyState(VK_SHIFT) & 0x8000) || (args && (strstr(args, "/choose") || strstr(args, "--choose")));
    for (;;) {
        if (choose || !disc[0] || !exists(disc)) {
            if (!choose && disc[0]) {
                char m[MAX_PATH + 128];
                snprintf(m, sizeof m, "The disc image\n%s\nis not there any more. Choose it again.", disc);
                MessageBoxA(0, m, "Tomba! 2 port", MB_ICONINFORMATION);
            }
            if (!choose_disc()) return 0;
        }
        choose = 0;
        DWORD code = run_game();
        if (code == 0) return 0;
        char err[1024], m[2048];
        last_error(err, sizeof err);
        snprintf(m, sizeof m, "The game stopped (exit code %lu):\n\n%s\n\nThe full log is %s.\n\n"
                 "Choose another disc image? (the port needs your own Tomba! 2 USA disc, SCUS-94454, as a raw .bin/.cue or .iso)",
                 code, err[0] ? err : "(no message)", logp);
        if (MessageBoxA(0, m, "Tomba! 2 port", MB_YESNO | MB_ICONWARNING) != IDYES) return (int)code;
        choose = 1;
    }
}

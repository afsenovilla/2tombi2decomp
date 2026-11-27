/* tomba2-view: the SDL2 window of the port (copied from Tombi-Decomp's port/tools/view/tombi_view.c, MIT, same
 * author; 60 Hz NTSC frames, 320x240) (`tomba2 --window`).  A separate host-native (64-bit) process, because the
 * game binary is i386 and freestanding; see port/runtime/window.c for the protocol:
 *   stdin : frames "TBFR" u32 w, u32 h, w*h RGB24 bytes
 *   fd 3  : audio, s16le stereo 44100 Hz
 *   fd 4  : we write one u16 per frame: pad 1 buttons in PSX bit order, active high
 * Keyboard: arrows = d-pad, X = Cross, Z = Square, S = Triangle, D = Circle, Q/W = L1/R1, A/E = L2/R2,
 * Return = Start, Backspace or Right Shift = Select, F = toggle 2x/3x window scale, F11 = fullscreen, F12 = screenshot
 * (tomba2_shot_NNN.bmp in the working directory: the launcher's folder), Escape = quit.
 * A game controller (SDL_GameController) maps to the same buttons.  Can also be used alone on a recording:
 *   build/port/tomba2 --frames 1200 --pad-script 1000:start | build/port/tomba2-view   (no audio / pad pipes).
 * Options (tomba2 --viewer-arg X passes them through): --scale 1|2|3  --fullscreen  --stats (pipe / audio counters per second)
 *   --renderer direct3d|direct3d11|direct3d12|opengl|opengles2|software  (SDL's render driver; default: SDL's own
 *          choice, direct3d on Windows; `tomba2 --renderer X` passes it too)  --linear (smooth scaling; default nearest)
 * At start the viewer prints its SDL version, video driver, render driver (and the others available), the display
 * mode and the texture format to stderr (the game's log, tomba2.log on Windows), so a report shows them.
 *   --dump DIR[:N]  (test) every Nth received frame as DIR/view_NNNNNN.ppm, to compare with the game's --dump-frames
 *   --keys up=Up,down=Down,left=Left,right=Right,cross=X,square=Z,triangle=S,circle=D,l1=Q,r1=W,l2=A,r2=E,
 *          start=Return,select=Backspace   (SDL key names, SDL_GetScancodeFromName; unnamed buttons keep the default)
 * Windows: the audio and pad pipes cannot be fds 3 and 4; the game passes their handles as
 *   --audio-handle N --pad-handle N (runtime/sys_win32_i386.c), and stdin is read with ReadFile. */
#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
#include <windows.h>
typedef HANDLE pipe_t;
#define NO_PIPE NULL
static long rd(pipe_t h, void *buf, size_t n) { DWORD got = 0; if (!ReadFile(h, buf, (DWORD)n, &got, NULL)) return GetLastError() == ERROR_BROKEN_PIPE ? 0 : -1; return (long)got; }
static long wr(pipe_t h, const void *buf, size_t n) { DWORD put = 0; if (!WriteFile(h, buf, (DWORD)n, &put, NULL)) return -1; return (long)put; }
#else
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
typedef int pipe_t;
#define NO_PIPE (-1)
static long rd(pipe_t fd, void *buf, size_t n) { ssize_t r; do r = read(fd, buf, n); while (r < 0 && errno == EINTR); return (long)r; }
static long wr(pipe_t fd, const void *buf, size_t n) { ssize_t r = write(fd, buf, n); return r < 0 && errno == EAGAIN ? (long)n : (long)r; }
#endif

/* Every pipe read loops until the count is complete: ReadFile on an anonymous pipe (and read on a Linux pipe)
   returns as soon as any bytes are there, so a 245 KB frame arrives in pieces.  PORT_PIPE_CHUNK=N (test hook,
   both ends) caps every read at N bytes to exercise the loops. */
static size_t pipe_chunk;
static int read_all(pipe_t fd, void *buf, size_t n) {
    char *c = buf;
    while (n) {
        long r = rd(fd, c, pipe_chunk && n > pipe_chunk ? pipe_chunk : n);
        if (r <= 0) return -1;
        c += r; n -= r;
    }
    return 0;
}

static pipe_t audio_fd = NO_PIPE;
static SDL_AudioDeviceID dev;
/* Audio: the game produces samples on its own clock, 735 stereo frames per vblank (shims/audio.c), which is
   44.1 kHz only if the game paces exactly 60 vblanks a second; the device plays on its own crystal.  The pipe is
   drained unconditionally by a thread into a ring buffer (the game is never blocked on audio: a blocked write would
   stall a vblank); the SDL callback pulls from the ring through a linear resampler whose rate follows the ring's
   fill: the fill is held near AUDIO_TARGET by playing up to 2 % faster or slower (the user's Windows run paced
   59.4 vblanks/s, 1 % less audio than the device consumed: with a fixed rate the ring ran dry every few seconds,
   the music "stuttered").  An underrun (the game stalled) pads silence and re-primes to the target; more than
   AUDIO_HIGH queued (a stall of the player) skips ahead.  Underruns and skips are logged to stderr (tomba2.log
   under the launcher) with the time, so a player's log shows them. */
#define FRAME_BYTES (44100 * 4 / 60)
#define RING_BYTES (1 << 18)                 /* 1.5 s; a power of two, so the byte counters may wrap */
#define AUDIO_TARGET (6 * 735)               /* stereo frames queued: 100 ms */
#define AUDIO_HIGH (24 * 735)                /* 400 ms: skip back to the target */
static unsigned char ring[RING_BYTES];
static volatile unsigned ring_r, ring_w;      /* byte positions, modulo RING_BYTES; w - r = fill */
static SDL_mutex *ring_lock;
static unsigned audio_dropped, audio_padded;  /* bytes, for --stats */
static unsigned audio_underruns, audio_skips;
static unsigned long audio_in, audio_out;      /* bytes received, frames played (for --stats: the two clocks) */
static unsigned audio_gap_max, audio_fill_min = ~0u;   /* --stats: longest wait for the game's audio (ms), lowest fill */
static int ring_started;                      /* playing: set once AUDIO_TARGET is queued, cleared by an underrun */
static double rs_frac;                        /* resampler position past ring_r, in source frames (0..1) */
static double rs_fill = AUDIO_TARGET;         /* smoothed fill, in frames */
static double rs_integ;                       /* the controller's integral term (rate offset) */
static Uint32 audio_t0;
static void audio_log(const char *what, unsigned n, unsigned fill) {
    if (n <= 20 || n % 100 == 0)
        fprintf(stderr, "tomba2-view: audio %s #%u at %.1f s (queued %u ms)\n", what, n,
                (SDL_GetTicks() - audio_t0) / 1000.0, fill * 1000 / 44100);
}
static inline const Sint16 *ring_frame(unsigned i) { return (const Sint16 *)(ring + ((ring_r + i * 4) % RING_BYTES)); }
static void audio_cb(void *ud, Uint8 *out, int len) {
    (void)ud;
    Sint16 *o = (Sint16 *)out;
    int m = len / 4;
    SDL_LockMutex(ring_lock);
    unsigned fill = (ring_w - ring_r) / 4;
    if (ring_started && fill < audio_fill_min) audio_fill_min = fill;
    if (!ring_started) {
        if (fill < AUDIO_TARGET) { SDL_UnlockMutex(ring_lock); memset(out, 0, len); return; }   /* priming */
        ring_started = 1; rs_frac = 0; rs_fill = fill;
    }
    if (fill > AUDIO_HIGH) {   /* the player stalled (or the game ran ahead): back to the target */
        audio_skips++; audio_log("skip", audio_skips, fill);
        audio_dropped += (fill - AUDIO_TARGET) * 4; ring_r = (ring_w & ~3u) - AUDIO_TARGET * 4; fill = AUDIO_TARGET; rs_fill = fill;
    }
    rs_fill += (fill - rs_fill) * 0.05;   /* smoothed over ~20 callbacks (~230 ms at 512-frame buffers) */
    double e = (rs_fill - AUDIO_TARGET) / AUDIO_TARGET;
    /* proportional (1 % at a quarter of the target off) + integral (the steady clock difference, e.g. 59.4 against
       60 vblanks/s, without a standing offset of the fill); at most 2 % faster or slower */
    rs_integ += e * 0.0005;
    rs_integ = rs_integ > 0.02 ? 0.02 : rs_integ < -0.02 ? -0.02 : rs_integ;
    double err = e * 0.04 + rs_integ;
    double ratio = 1.0 + (err > 0.02 ? 0.02 : err < -0.02 ? -0.02 : err);   /* source frames per output frame */
    int i = 0;
    double pos = rs_frac;
    for (; i < m; i++) {
        unsigned k = (unsigned)pos;
        if (k + 1 >= fill) break;
        const Sint16 *a = ring_frame(k), *b = ring_frame(k + 1);
        double t = pos - k;
        o[2 * i] = (Sint16)(a[0] + (b[0] - a[0]) * t);
        o[2 * i + 1] = (Sint16)(a[1] + (b[1] - a[1]) * t);
        pos += ratio;
    }
    audio_out += (unsigned long)m;
    unsigned adv = (unsigned)pos;
    if (adv > fill) adv = fill;
    ring_r += adv * 4; rs_frac = pos - adv;
    if (i < m) {   /* underrun: the game did not deliver in time (a stalled vblank): silence, re-prime */
        ring_started = 0;
        audio_underruns++; audio_log("underrun", audio_underruns, fill);
        memset(o + 2 * i, 0, (size_t)(m - i) * 4); audio_padded += (m - i) * 4;
    }
    SDL_UnlockMutex(ring_lock);
}
static int audio_thread(void *arg) {
    (void)arg;
    unsigned char buf[FRAME_BYTES];
    for (;;) {
        Uint32 t = SDL_GetTicks();
        long r = rd(audio_fd, buf, pipe_chunk && pipe_chunk < sizeof buf ? pipe_chunk : sizeof buf);
        if (r <= 0) break;
        if (SDL_GetTicks() - t > audio_gap_max) audio_gap_max = SDL_GetTicks() - t;
        SDL_LockMutex(ring_lock);
        unsigned fill = ring_w - ring_r;
        if (fill + (unsigned)r > RING_BYTES) { audio_dropped += fill + (unsigned)r - RING_BYTES; ring_r = (ring_w + (unsigned)r - RING_BYTES + 3) & ~3u; }
        for (long i = 0; i < r; i++) ring[(ring_w + i) % RING_BYTES] = buf[i];
        ring_w += (unsigned)r; audio_in += (unsigned long)r;
        SDL_UnlockMutex(ring_lock);
    }
    return 0;
}

/* Video: a thread reads frames from the game and leaves the newest one in a mailbox; the main loop presents it.
   SDL_RenderPresent with vsync blocks for up to a display period (16.7 ms at 60 Hz), so a loop that reads a frame
   and then presents it paced the game by the display, not by its own 50 Hz schedule (and a 1 MB pipe only hides
   that for four frames).  The reader never waits for the presenter: a frame that is not presented in time is
   replaced by the next one (latest wins). */
static pipe_t video_fd;
static SDL_mutex *frame_lock;
static SDL_sem *frame_sem;
static unsigned char *mbox_rgb; static size_t mbox_cap; static int mbox_w, mbox_h, mbox_new, video_eof;
static unsigned frames_in, frames_shown, frames_skipped;
static const char *dump_dir; static unsigned dump_every = 1;   /* --dump DIR[:N]: every Nth received frame as DIR/view_NNNNNN.ppm */
static void dump_frame(unsigned idx, const unsigned char *rgb, int w, int h) {
    char path[1024];
    snprintf(path, sizeof path, "%s/view_%06u.ppm", dump_dir, idx);
    FILE *f = fopen(path, "wb");
    if (!f) { fprintf(stderr, "tomba2-view: cannot write %s\n", path); return; }
    fprintf(f, "P6\n%d %d\n255\n", w, h);
    fwrite(rgb, 1, (size_t)w * h * 3, f);
    fclose(f);
}
static int video_thread(void *arg) {
    (void)arg;
    unsigned char *rgb = NULL; size_t rgb_cap = 0;
    unsigned resyncs = 0;
    for (;;) {
        Uint32 hdr[3];
        if (read_all(video_fd, hdr, 12) < 0) break;
        if (hdr[0] != 0x52464254u) {   /* not at a frame boundary: slide byte by byte to the next "TBFR" */
            unsigned char b[12]; memcpy(b, hdr, 12);
            long skipped = 0; int eof = 0;
            while (!(b[0] == 'T' && b[1] == 'B' && b[2] == 'F' && b[3] == 'R')) {
                memmove(b, b + 1, 11);
                if (read_all(video_fd, b + 11, 1) < 0) { eof = 1; break; }
                skipped++;
            }
            if (eof) break;
            memcpy(hdr, b, 12);
            if (++resyncs <= 10) fprintf(stderr, "tomba2-view: frame stream out of step: %ld bytes skipped to the next header\n", skipped);
        }
        if (hdr[1] == 0 || hdr[1] > 1024 || hdr[2] == 0 || hdr[2] > 512) {
            fprintf(stderr, "tomba2-view: bad frame header %ux%u\n", hdr[1], hdr[2]); break;
        }
        int w = (int)hdr[1], h = (int)hdr[2];
        size_t n = (size_t)w * h * 3;
        if (n > rgb_cap) { rgb = realloc(rgb, n); rgb_cap = n; }
        if (read_all(video_fd, rgb, n) < 0) break;
        if (dump_dir && (frames_in + 1) % dump_every == 0) dump_frame(frames_in + 1, rgb, w, h);   /* numbered like the game: its first vblank is frame 1 */
        SDL_LockMutex(frame_lock);
        if (n > mbox_cap) { mbox_rgb = realloc(mbox_rgb, n); mbox_cap = n; }
        memcpy(mbox_rgb, rgb, n); mbox_w = w; mbox_h = h;
        if (mbox_new) frames_skipped++;
        mbox_new = 1; frames_in++;
        SDL_UnlockMutex(frame_lock);
        SDL_SemPost(frame_sem);
    }
    video_eof = 1;
    SDL_SemPost(frame_sem);
    return 0;
}

enum { P_SELECT = 1, P_START = 8, P_UP = 0x10, P_RIGHT = 0x20, P_DOWN = 0x40, P_LEFT = 0x80, P_L2 = 0x100, P_R2 = 0x200,
       P_L1 = 0x400, P_R1 = 0x800, P_TRI = 0x1000, P_CIRCLE = 0x2000, P_CROSS = 0x4000, P_SQUARE = 0x8000 };

/* key map: two scancodes per button (the second is a fixed alternative) */
static const char *const button_names[14] = { "select", "start", "up", "right", "down", "left", "l2", "r2", "l1", "r1", "triangle", "circle", "cross", "square" };
static const Uint16 button_bits[14] = { P_SELECT, P_START, P_UP, P_RIGHT, P_DOWN, P_LEFT, P_L2, P_R2, P_L1, P_R1, P_TRI, P_CIRCLE, P_CROSS, P_SQUARE };
static SDL_Scancode keymap[14][2] = {
    { SDL_SCANCODE_BACKSPACE, SDL_SCANCODE_RSHIFT }, { SDL_SCANCODE_RETURN, SDL_SCANCODE_UNKNOWN },
    { SDL_SCANCODE_UP, SDL_SCANCODE_UNKNOWN }, { SDL_SCANCODE_RIGHT, SDL_SCANCODE_UNKNOWN },
    { SDL_SCANCODE_DOWN, SDL_SCANCODE_UNKNOWN }, { SDL_SCANCODE_LEFT, SDL_SCANCODE_UNKNOWN },
    { SDL_SCANCODE_A, SDL_SCANCODE_UNKNOWN }, { SDL_SCANCODE_E, SDL_SCANCODE_UNKNOWN },
    { SDL_SCANCODE_Q, SDL_SCANCODE_UNKNOWN }, { SDL_SCANCODE_W, SDL_SCANCODE_UNKNOWN },
    { SDL_SCANCODE_S, SDL_SCANCODE_UNKNOWN }, { SDL_SCANCODE_D, SDL_SCANCODE_UNKNOWN },
    { SDL_SCANCODE_X, SDL_SCANCODE_UNKNOWN }, { SDL_SCANCODE_Z, SDL_SCANCODE_UNKNOWN },
};
static Uint16 key_mask(SDL_Scancode k) {
    Uint16 m = 0;
    if (k == SDL_SCANCODE_UNKNOWN) return 0;
    for (int i = 0; i < 14; i++) if (keymap[i][0] == k || keymap[i][1] == k) m |= button_bits[i];
    return m;
}
/* --keys up=Up,cross=X,...: SDL key names (SDL_GetScancodeFromName) */
static void parse_keys(const char *spec) {
    char buf[512]; strncpy(buf, spec, sizeof buf - 1); buf[sizeof buf - 1] = 0;
    for (char *tok = strtok(buf, ","); tok; tok = strtok(NULL, ",")) {
        char *eq = strchr(tok, '=');
        if (!eq) continue;
        *eq = 0;
        SDL_Scancode sc = SDL_GetScancodeFromName(eq + 1);
        if (sc == SDL_SCANCODE_UNKNOWN) { fprintf(stderr, "tomba2-view: unknown key '%s' for %s\n", eq + 1, tok); continue; }
        for (int i = 0; i < 14; i++) if (!strcmp(tok, button_names[i])) { keymap[i][0] = sc; keymap[i][1] = SDL_SCANCODE_UNKNOWN; }
    }
}
static Uint16 ctrl_mask(SDL_GameControllerButton b) {
    switch (b) {
    case SDL_CONTROLLER_BUTTON_DPAD_UP: return P_UP; case SDL_CONTROLLER_BUTTON_DPAD_DOWN: return P_DOWN;
    case SDL_CONTROLLER_BUTTON_DPAD_LEFT: return P_LEFT; case SDL_CONTROLLER_BUTTON_DPAD_RIGHT: return P_RIGHT;
    case SDL_CONTROLLER_BUTTON_A: return P_CROSS; case SDL_CONTROLLER_BUTTON_B: return P_CIRCLE;
    case SDL_CONTROLLER_BUTTON_X: return P_SQUARE; case SDL_CONTROLLER_BUTTON_Y: return P_TRI;
    case SDL_CONTROLLER_BUTTON_LEFTSHOULDER: return P_L1; case SDL_CONTROLLER_BUTTON_RIGHTSHOULDER: return P_R1;
    case SDL_CONTROLLER_BUTTON_START: return P_START; case SDL_CONTROLLER_BUTTON_BACK: return P_SELECT;
    default: return 0;
    }
}

static void shot(const unsigned char *rgb, int w, int h) {   /* F12: tomba2_shot_NNN.bmp */
    static int n;
    char path[64];
    for (; n < 1000; n++) {
        snprintf(path, sizeof path, "tomba2_shot_%03d.bmp", n);
        FILE *f = fopen(path, "rb");
        if (!f) break;
        fclose(f);
    }
    SDL_Surface *sf = SDL_CreateRGBSurfaceWithFormatFrom((void *)rgb, w, h, 24, w * 3, SDL_PIXELFORMAT_RGB24);
    if (sf && SDL_SaveBMP(sf, path) == 0) fprintf(stderr, "tomba2-view: screenshot %s\n", path);
    else fprintf(stderr, "tomba2-view: screenshot failed: %s\n", SDL_GetError());
    if (sf) SDL_FreeSurface(sf);
    n++;
}

int main(int argc, char **argv) {
    int scale = 2, fullscreen = 0, stats = 0, linear = 0;
    const char *renderer = NULL;
    pipe_t pad_fd = NO_PIPE;
#ifdef _WIN32
    video_fd = GetStdHandle(STD_INPUT_HANDLE);
#else
    video_fd = 0;
    pad_fd = fcntl(4, F_GETFD) >= 0 ? 4 : -1;
    audio_fd = fcntl(3, F_GETFD) >= 0 ? 3 : -1;
#endif
    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "--scale") && i + 1 < argc) { scale = atoi(argv[++i]); if (scale < 1) scale = 1; if (scale > 6) scale = 6; }
        else if (!strcmp(argv[i], "--fullscreen")) fullscreen = 1;
        else if (!strcmp(argv[i], "--stats")) stats = 1;
        else if (!strcmp(argv[i], "--renderer") && i + 1 < argc) renderer = argv[++i];
        else if (!strcmp(argv[i], "--linear")) linear = 1;   /* every second: frames received / shown / skipped, audio fill, drops, pads */
        else if (!strcmp(argv[i], "--keys") && i + 1 < argc) parse_keys(argv[++i]);
        else if (!strcmp(argv[i], "--dump") && i + 1 < argc) {   /* DIR[:N]: every Nth received frame as DIR/view_NNNNNN.ppm (test: compare with --dump-frames) */
            static char d[1024]; strncpy(d, argv[++i], sizeof d - 1);
            char *c = strrchr(d, ':'); if (c && c[1] >= '0' && c[1] <= '9') { dump_every = (unsigned)atoi(c + 1); *c = 0; }
            if (!dump_every) dump_every = 1;
            dump_dir = d;
        }
#ifdef _WIN32
        else if (!strcmp(argv[i], "--audio-handle") && i + 1 < argc) audio_fd = (HANDLE)(uintptr_t)strtoul(argv[++i], NULL, 10);
        else if (!strcmp(argv[i], "--pad-handle") && i + 1 < argc) pad_fd = (HANDLE)(uintptr_t)strtoul(argv[++i], NULL, 10);
#endif
        else fprintf(stderr, "tomba2-view: unknown option %s\n", argv[i]);
    }
    { const char *e = getenv("PORT_PIPE_CHUNK"); if (e) pipe_chunk = (size_t)atol(e); }
    if (renderer && *renderer) SDL_SetHint(SDL_HINT_RENDER_DRIVER, renderer);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, linear ? "1" : "0");
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_GAMECONTROLLER) < 0) {
        fprintf(stderr, "tomba2-view: SDL_Init: %s\n", SDL_GetError());
        return 1;
    }
    SDL_Window *win = SDL_CreateWindow("Tomba! 2 (PC port)", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                       320 * scale, 240 * scale, SDL_WINDOW_RESIZABLE | (fullscreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0));
    if (!win) { fprintf(stderr, "tomba2-view: SDL_CreateWindow: %s\n", SDL_GetError()); return 1; }
    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!ren) ren = SDL_CreateRenderer(win, -1, 0);
    if (!ren) ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_SOFTWARE);
    if (!ren && renderer) {   /* the asked driver failed: SDL's own choice */
        fprintf(stderr, "tomba2-view: render driver %s failed (%s); trying the default\n", renderer, SDL_GetError());
        SDL_SetHint(SDL_HINT_RENDER_DRIVER, "");
        ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (!ren) ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_SOFTWARE);
    }
    if (!ren) { fprintf(stderr, "tomba2-view: SDL_CreateRenderer: %s\n", SDL_GetError()); return 1; }
    /* the 4:3 picture keeps its shape in any window size (bars instead of stretching) */
    SDL_RenderSetLogicalSize(ren, 320, 240);
    {   /* what this machine gave us, for tomba2.log */
        SDL_version v; SDL_GetVersion(&v);
        SDL_RendererInfo ri; SDL_GetRendererInfo(ren, &ri);
        char avail[256] = "";
        for (int i = 0; i < SDL_GetNumRenderDrivers(); i++) {
            SDL_RendererInfo di;
            if (SDL_GetRenderDriverInfo(i, &di) == 0 && strlen(avail) + strlen(di.name) + 2 < sizeof avail) {
                if (avail[0]) strcat(avail, " ");
                strcat(avail, di.name);
            }
        }
        SDL_DisplayMode dm; int have_dm = SDL_GetCurrentDisplayMode(SDL_GetWindowDisplayIndex(win), &dm) == 0;
        fprintf(stderr, "tomba2-view: SDL %d.%d.%d, video driver %s, renderer %s (%s%s; max texture %dx%d; available: %s)\n",
                v.major, v.minor, v.patch, SDL_GetCurrentVideoDriver(), ri.name,
                ri.flags & SDL_RENDERER_ACCELERATED ? "accelerated" : "software",
                ri.flags & SDL_RENDERER_PRESENTVSYNC ? ", vsync" : "", ri.max_texture_width, ri.max_texture_height, avail);
        if (have_dm) fprintf(stderr, "tomba2-view: display %dx%d at %d Hz, %s; window %dx%d%s, scaling %s\n", dm.w, dm.h,
                             dm.refresh_rate, SDL_GetPixelFormatName(dm.format), 320 * scale, 240 * scale,
                             fullscreen ? " (fullscreen)" : "", linear ? "linear" : "nearest");
    }
    SDL_Texture *tex = NULL; int tw = 0, th = 0;

    if (audio_fd != NO_PIPE) {
        SDL_AudioSpec want, have;
        memset(&want, 0, sizeof want);
        want.freq = 44100; want.format = AUDIO_S16LSB; want.channels = 2; want.samples = 512; want.callback = audio_cb;
        ring_lock = SDL_CreateMutex();
        audio_t0 = SDL_GetTicks();
        dev = SDL_OpenAudioDevice(NULL, 0, &want, &have, 0);
        if (dev) SDL_PauseAudioDevice(dev, 0); else fprintf(stderr, "tomba2-view: no audio device: %s\n", SDL_GetError());
        SDL_CreateThread(audio_thread, "audio", NULL);   /* drains the pipe even without a device */
    }
    SDL_GameController *ctrl = NULL;
    for (int i = 0; i < SDL_NumJoysticks(); i++) if (SDL_IsGameController(i)) { ctrl = SDL_GameControllerOpen(i); break; }

    Uint16 keys = 0, buttons = 0, tapped = 0;   /* tapped: pressed since the last sample, so a tap shorter than a frame is still sent once */
    frame_lock = SDL_CreateMutex(); frame_sem = SDL_CreateSemaphore(0);
    SDL_CreateThread(video_thread, "video", NULL);
    unsigned char *rgb = NULL; size_t rgb_cap = 0;
    int running = 1;
    Uint32 stats_t0 = SDL_GetTicks(); unsigned stats_in = 0, stats_shown = 0, stats_skipped = 0;
    while (running) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
            case SDL_QUIT: running = 0; break;
            case SDL_KEYDOWN:
                if (e.key.keysym.scancode == SDL_SCANCODE_ESCAPE) running = 0;
                else if (e.key.keysym.scancode == SDL_SCANCODE_F && !e.key.repeat) {
                    scale = scale == 2 ? 3 : 2;
                    SDL_SetWindowSize(win, 320 * scale, 240 * scale);
                } else if (e.key.keysym.scancode == SDL_SCANCODE_F12 && !e.key.repeat) {
                    if (rgb && tw) shot(rgb, tw, th);
                } else if (e.key.keysym.scancode == SDL_SCANCODE_F11 && !e.key.repeat) {
                    fullscreen = !fullscreen;
                    SDL_SetWindowFullscreen(win, fullscreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0);
                } else { keys |= key_mask(e.key.keysym.scancode); tapped |= key_mask(e.key.keysym.scancode); }
                break;
            case SDL_KEYUP: keys &= ~key_mask(e.key.keysym.scancode); break;
            case SDL_CONTROLLERBUTTONDOWN: buttons |= ctrl_mask(e.cbutton.button); tapped |= ctrl_mask(e.cbutton.button); break;
            case SDL_CONTROLLERBUTTONUP: buttons &= ~ctrl_mask(e.cbutton.button); break;
            case SDL_CONTROLLERAXISMOTION:
                if (e.caxis.axis == SDL_CONTROLLER_AXIS_TRIGGERLEFT) { if (e.caxis.value > 16000) buttons |= P_L2; else buttons &= ~P_L2; }
                if (e.caxis.axis == SDL_CONTROLLER_AXIS_TRIGGERRIGHT) { if (e.caxis.value > 16000) buttons |= P_R2; else buttons &= ~P_R2; }
                if (e.caxis.axis == SDL_CONTROLLER_AXIS_LEFTX) {
                    buttons &= ~(P_LEFT | P_RIGHT);
                    if (e.caxis.value < -16000) buttons |= P_LEFT; else if (e.caxis.value > 16000) buttons |= P_RIGHT;
                }
                if (e.caxis.axis == SDL_CONTROLLER_AXIS_LEFTY) {
                    buttons &= ~(P_UP | P_DOWN);
                    if (e.caxis.value < -16000) buttons |= P_UP; else if (e.caxis.value > 16000) buttons |= P_DOWN;
                }
                break;
            case SDL_CONTROLLERDEVICEADDED: if (!ctrl) ctrl = SDL_GameControllerOpen(e.cdevice.which); break;
            }
        }
        if (!running) break;
        /* the newest frame from the reader thread (waits for one: at most one vblank) */
        if (SDL_SemWaitTimeout(frame_sem, 100) != 0 && !video_eof) continue;
        SDL_LockMutex(frame_lock);
        int w = mbox_w, h = mbox_h, fresh = mbox_new;
        size_t n = (size_t)w * h * 3;
        if (fresh) { if (n > rgb_cap) { rgb = realloc(rgb, n); rgb_cap = n; } memcpy(rgb, mbox_rgb, n); mbox_new = 0; }
        SDL_UnlockMutex(frame_lock);
        if (!fresh) { if (video_eof) break; continue; }
        frames_shown++;
        if (!tex || tw != w || th != h) {
            if (tex) SDL_DestroyTexture(tex);
            /* XRGB8888: the native format of the Direct3D / OpenGL / software renderers (RGB24 is converted by SDL on
               every upload, a path that differs between drivers); the frame is converted here */
            tex = SDL_CreateTexture(ren, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_STREAMING, w, h);
            if (!tex) fprintf(stderr, "tomba2-view: SDL_CreateTexture %dx%d: %s\n", w, h, SDL_GetError());
            tw = w; th = h;
            /* keep the 4:3 look: 320x240 and 512x240 both fill the same window */
            if (!fullscreen) SDL_SetWindowSize(win, 320 * scale, 240 * scale);
        }
        {
            static Uint32 *x; static size_t xcap;
            if ((size_t)w * h > xcap) { x = realloc(x, (size_t)w * h * 4); xcap = (size_t)w * h; }
            for (int i = 0; i < w * h; i++) x[i] = (Uint32)rgb[i * 3] << 16 | (Uint32)rgb[i * 3 + 1] << 8 | rgb[i * 3 + 2];
            if (tex) SDL_UpdateTexture(tex, NULL, x, w * 4);
        }
        SDL_RenderClear(ren);
        SDL_RenderCopy(ren, tex, NULL, NULL);
        SDL_RenderPresent(ren);
        if (pad_fd != NO_PIPE) {
            Uint16 p = keys | buttons | tapped;
            tapped = 0;
            if (wr(pad_fd, &p, 2) != 2) break;
        }
        if (stats && SDL_GetTicks() - stats_t0 >= 1000) {
            unsigned fill = ring_w - ring_r;
            fprintf(stderr, "tomba2-view: %u frames in, %u shown, %u skipped; audio queued %u ms, dropped %u ms, padded %u ms, "
                    "%u underruns, %u skips; %lu frames in, %lu played; longest wait %u ms, lowest %u ms\n",
                    frames_in - stats_in, frames_shown - stats_shown, frames_skipped - stats_skipped,
                    fill / (44100 * 4 / 1000), audio_dropped / (44100 * 4 / 1000), audio_padded / (44100 * 4 / 1000),
                    audio_underruns, audio_skips, audio_in / 4, audio_out, audio_gap_max,
                    audio_fill_min == ~0u ? 0 : audio_fill_min * 1000 / 44100);
            audio_gap_max = 0; audio_fill_min = ~0u;
            stats_t0 = SDL_GetTicks(); stats_in = frames_in; stats_shown = frames_shown; stats_skipped = frames_skipped;
        }
    }
    if (audio_fd != NO_PIPE)
        fprintf(stderr, "tomba2-view: audio: %u underruns, %u skips, %u ms padded, %u ms dropped\n", audio_underruns,
                audio_skips, audio_padded / (44100 * 4 / 1000), audio_dropped / (44100 * 4 / 1000));
    SDL_Quit();
    return 0;
}

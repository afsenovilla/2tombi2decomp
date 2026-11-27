/* Port entry: maps the PS1 address space, loads the user's MAIN.EXE (and the boot exe SCUS_944.54 for reference),
 * then starts the retail entry point (__SN_ENTRY_POINT, crt0) in the MIPS interpreter.  Every call it makes to a
 * function with C goes to the native code; Psy-Q calls go to the shims (docs/PORT.md).  Adapted from Tombi-Decomp's
 * port/runtime/main_port.c (MIT, same author): T1 carried a C translation of main(); here main() (func_80050B08) is
 * still assembly, so the interpreter runs it. */
#include "port_runtime.h"

typedef unsigned char u8; typedef unsigned short u16; typedef unsigned int u32;

extern void port_setup_memory(void);
extern int port_realtime, port_hz;
extern const char *port_data_dir;      /* shims/psyq.c: the extracted disc files (game/usa) */
extern int port_skip_movies;
u32p port_mips_call(u32p entry, const u32p *args);

static int streq(const char *a, const char *b) { while (*a && *a == *b) { a++; b++; } return *a == *b; }
static int atoi_(const char *s) { int v = 0; while (*s >= '0' && *s <= '9') v = v * 10 + *s++ - '0'; return v; }
static u32 hex_(const char *s) {
    u32 v = 0;
    if (s[0] == '0' && (s[1] | 32) == 'x') s += 2;
    for (;; s++) {
        int c = *s, d = c >= '0' && c <= '9' ? c - '0' : (c | 32) >= 'a' && (c | 32) <= 'f' ? (c | 32) - 'a' + 10 : -1;
        if (d < 0) return v;
        v = v * 16 + d;
    }
}

/* SHA-1 (FIPS 180-1), to identify the player's MAIN.EXE */
static u32 rol(u32 x, int n) { return x << n | x >> (32 - n); }
static void sha1(const u8 *m, u32 len, u8 out[20]) {
    u32 h[5] = { 0x67452301u, 0xEFCDAB89u, 0x98BADCFEu, 0x10325476u, 0xC3D2E1F0u };
    u32 nblk = (len + 8) / 64 + 1;
    for (u32 b = 0; b < nblk; b++) {
        u32 w[80];
        for (int i = 0; i < 16; i++) {
            u32 v = 0;
            for (int k = 0; k < 4; k++) {
                u32 pos = b * 64 + i * 4 + k; u8 c;
                if (pos < len) c = m[pos]; else if (pos == len) c = 0x80;
                else if (pos >= nblk * 64 - 4) c = (u8)((u32)(len * 8ull >> (8 * (nblk * 64 - 1 - pos))));
                else c = 0;
                v = v << 8 | c;
            }
            w[i] = v;
        }
        for (int i = 16; i < 80; i++) w[i] = rol(w[i - 3] ^ w[i - 8] ^ w[i - 14] ^ w[i - 16], 1);
        u32 a = h[0], bb = h[1], c = h[2], d = h[3], e = h[4];
        for (int i = 0; i < 80; i++) {
            u32 f, k;
            if (i < 20) { f = (bb & c) | (~bb & d); k = 0x5A827999u; }
            else if (i < 40) { f = bb ^ c ^ d; k = 0x6ED9EBA1u; }
            else if (i < 60) { f = (bb & c) | (bb & d) | (c & d); k = 0x8F1BBCDCu; }
            else { f = bb ^ c ^ d; k = 0xCA62C1D6u; }
            u32 t = rol(a, 5) + f + e + k + w[i];
            e = d; d = c; c = rol(bb, 30); bb = a; a = t;
        }
        h[0] += a; h[1] += bb; h[2] += c; h[3] += d; h[4] += e;
    }
    for (int i = 0; i < 20; i++) out[i] = (u8)(h[i / 4] >> (24 - 8 * (i % 4)));
}
static void hex20(const u8 *d, char *o) { for (int i = 0; i < 20; i++) { o[2 * i] = "0123456789abcdef"[d[i] >> 4]; o[2 * i + 1] = "0123456789abcdef"[d[i] & 15]; } o[40] = 0; }
static int streq(const char *a, const char *b);
/* the USA disc (SCUS-94454) is the one the port is built from; the other versions' MAIN.EXE differ */
#define MAIN_SHA1_USA "f41c4065788e8c838cbd8b22f0fff6d4bc7de49a"
static const char *known_version(const char *h) {
    if (streq(h, "6bcee82bde552b9c044330bcc8e1889e2b80b107")) return "Tombi! 2 (Europe, SCES-02147)";
    if (streq(h, "410bd51f07893370bcf4aa7fdc2412afa38ca96a")) return "Tombi! 2 (Spain, SCES-02687)";
    return 0;
}
int port_no_verify;      /* --no-verify: run another MAIN.EXE anyway */
static u8 exe_buf[0x100000];

/* PS-X EXE: header 0x800 bytes, pc0 at 0x10, t_addr 0x18, t_size 0x1C, sp 0x30.  From the disc image (path 0) or a
   file (--exe). */
static u32 load_exe(const char *path, u32 *sp_out) {
    int n;
    const char *what = path;
    if (!path) {
        n = port_disc_read_file("MAIN.EXE", exe_buf, sizeof exe_buf);
        if (n < 0) {
            static char cnf[512]; int m = port_disc_read_file("SYSTEM.CNF", cnf, sizeof cnf - 1);
            if (m > 0) { cnf[m] = 0; for (int i = 0; i < m; i++) if (cnf[i] == '\r' || cnf[i] == '\n') cnf[i] = ' '; }
            port_fatal("%s has no MAIN.EXE: this is not the Tomba! 2 disc (USA, SCUS-94454)%s%s", port_disc_path(),
                       m > 0 ? "; its SYSTEM.CNF says: " : "", m > 0 ? cnf : "");
        }
        what = "MAIN.EXE on the disc image";
    } else {
        int fd = port_open(path);
        if (fd < 0) port_fatal("cannot open %s (the USA MAIN.EXE; or pass --disc IMAGE)", path);
        n = port_read(fd, exe_buf, sizeof exe_buf);
        port_close(fd);
    }
    {
        u8 d[20]; char h[41];
        sha1(exe_buf, (u32)n, d); hex20(d, h);
        if (!streq(h, MAIN_SHA1_USA)) {
            const char *v = known_version(h);
            if (!port_no_verify)
                port_fatal("%s is not the USA Tomba! 2 (SCUS-94454) MAIN.EXE (SHA-1 %s%s%s): the port runs the USA disc only "
                           "(--no-verify to try anyway)", what, h, v ? ": " : "", v ? v : ", an unknown version");
            port_printf("[port] warning: %s has SHA-1 %s, not the USA one (--no-verify)\n", what, h);
        } else port_printf("[port] %s: SHA-1 %s (Tomba! 2 USA, SCUS-94454)\n", what, h);
    }
    const u8 *hd = exe_buf;
    if (n < 0x800 || hd[0] != 'P' || hd[1] != 'S' || hd[2] != '-' || hd[3] != 'X') port_fatal("%s is not a PS-X EXE", what);
    u32 pc = *(u32 *)(hd + 0x10), taddr = *(u32 *)(hd + 0x18), tsize = *(u32 *)(hd + 0x1C);
    if (taddr < PSX_RAM_BASE || taddr + tsize > PSX_RAM_BASE + PSX_RAM_SIZE) port_fatal("%s: load address %08x out of RAM", what, taddr);
    if ((u32)n < 0x800 + tsize) port_fatal("%s: short file (%d of %u bytes)", what, n, 0x800 + tsize);
    for (u32 i = 0; i < tsize; i++) ((u8 *)(unsigned long)taddr)[i] = hd[0x800 + i];
    port_printf("[port] loaded %s: %u bytes at %08x, entry %08x\n", what, tsize, taddr, pc);
    if (sp_out) *sp_out = *(u32 *)(hd + 0x30);
    return pc;
}

/* hardware registers the game polls, set to "idle / ready" (the page is plain memory) */
static void init_io(void) {
    *(volatile u32 *)0x1F801814u = 0x1C802000u;   /* GPUSTAT: ready for commands, DMA, VRAM transfers; interlace off */
    *(volatile u32 *)0x1F801070u = 0;             /* I_STAT */
}

int port_main(int argc, char **argv) {
    const char *exe = 0;   /* 0: MAIN.EXE from the disc image, else game/usa/MAIN.EXE */
    u32 entry_override = 0;
    for (int i = 1; i < argc; i++) {
        if (streq(argv[i], "--exe") && i + 1 < argc) exe = argv[++i];
        else if (streq(argv[i], "--data") && i + 1 < argc) port_data_dir = argv[++i];
        else if (streq(argv[i], "--frames") && i + 1 < argc) port_max_frames = atoi_(argv[++i]);
        else if (streq(argv[i], "--dump-frames") && i + 1 < argc) port_dump_dir = argv[++i];
        else if (streq(argv[i], "--dump-every") && i + 1 < argc) port_dump_every = atoi_(argv[++i]);
        else if (streq(argv[i], "--dump-vram")) port_dump_vram = 1;
        else if (streq(argv[i], "--realtime")) port_realtime = 1;
        else if (streq(argv[i], "--hz") && i + 1 < argc) port_hz = atoi_(argv[++i]);
        else if (streq(argv[i], "--trace-cd")) port_trace_cd = 1;
        else if (streq(argv[i], "--ovl-interp") && i + 1 < argc) {
            extern const char *port_ovl_interp[8];
            for (int k = 0; k < 8; k++) if (!port_ovl_interp[k]) { port_ovl_interp[k] = argv[++i]; break; }
        }
        else if (streq(argv[i], "--no-kuseg")) { extern int port_kuseg_strict; port_kuseg_strict = 2; }
        else if (streq(argv[i], "--fake-kuseg")) { extern int port_kuseg_strict; port_kuseg_strict = 3; }
        else if (streq(argv[i], "--kuseg-strict")) { extern int port_kuseg_strict; port_kuseg_strict = 1; }
        else if (streq(argv[i], "--kuseg-mirror")) { /* Windows: read in start() (sys_win32_i386.c); Linux: the default */ }
        else if (streq(argv[i], "--no-ovl-native")) { extern int port_ovl_native; port_ovl_native = 0; }
        else if (streq(argv[i], "--dump-audio") && i + 1 < argc) { extern const char *port_dump_audio; port_dump_audio = argv[++i]; }
        else if (streq(argv[i], "--disc") && i + 1 < argc) { extern const char *port_disc_image; port_disc_image = argv[++i]; }
        else if (streq(argv[i], "--no-verify")) port_no_verify = 1;
        else if (streq(argv[i], "--save-dir") && i + 1 < argc) { extern const char *port_save_dir; port_save_dir = argv[++i]; }
        else if (streq(argv[i], "--window")) { extern int port_window; port_window = 1; }
        else if (streq(argv[i], "--headless")) { extern int port_window; port_window = 0; }
        else if (streq(argv[i], "--viewer") && i + 1 < argc) { extern const char *port_window_viewer; port_window_viewer = argv[++i]; }
        else if (streq(argv[i], "--viewer-arg") && i + 1 < argc) {
            extern const char *port_viewer_args[16]; extern int port_viewer_args_count;
            if (port_viewer_args_count < 16) port_viewer_args[port_viewer_args_count++] = argv[++i]; else i++;
        }
        else if (streq(argv[i], "--no-interp")) port_interp = 0;
        else if (streq(argv[i], "--interp") && i + 1 < argc) {
            extern u32p port_force_interp[8]; u32 v = hex_(argv[++i]);
            for (int k = 0; k < 8; k++) if (!port_force_interp[k]) { port_force_interp[k] = v; break; }
        }
        else if (streq(argv[i], "--interp-range") && i + 1 < argc) {
            /* LO-HI (hex): game functions in [LO, HI) run in the interpreter when called from interpreted code or a
               thunk; `--interp-range all` = every one (the retail code as the reference run) */
            extern u32p port_interp_lo, port_interp_hi; const char *v = argv[++i];
            if (streq(v, "all")) { port_interp_lo = 0x80000000u; port_interp_hi = 0x80200000u; }
            else { port_interp_lo = hex_(v); while (*v && *v != '-') v++; port_interp_hi = *v ? hex_(v + 1) : port_interp_lo + 4; }
        }
        else if (streq(argv[i], "--watch-pc") && i + 1 < argc) { extern u32p port_watch_pc; port_watch_pc = hex_(argv[++i]); }
        else if (streq(argv[i], "--trace-interp")) { extern int port_mips_trace; port_mips_trace = 1; }
        else if (streq(argv[i], "--entry") && i + 1 < argc) entry_override = hex_(argv[++i]);
        else if (streq(argv[i], "--pad-script") && i + 1 < argc) { extern void port_pad_script(const char *); port_pad_script(argv[++i]); }
        else if (streq(argv[i], "--autostart") && i + 1 < argc) { extern int port_autostart; port_autostart = atoi_(argv[++i]); }
        else if (streq(argv[i], "-v")) port_verbose++;
        else {
            port_printf("usage: %s [--disc IMAGE.bin|.cue|.iso] [--exe MAIN.EXE] [--data DIR] [--no-verify] [--save-dir DIR] [--frames N] [--dump-frames DIR] [--dump-every N] [--dump-vram]\n"
                        "       [--window [--viewer PATH] [--viewer-arg ARG]...] (SDL2 window: the tomba2-view process; paced)\n"
                        "       [--realtime] [--hz 50|60] [--trace-cd] [--no-interp] [--interp ADDR] [--trace-interp]\n"
                        "       [--entry ADDR] [--pad-script FRAME:BUTTONS[:LEN[xCOUNT/PERIOD]],...] [--autostart N] [-v]\n", argv[0]);
            return 2;
        }
    }
    port_setup_memory();
    { extern int port_window; extern void port_window_start(const char *); if (port_window) port_window_start(argv[0]); }
    u32 sp = 0;
    if (!port_disc_init() && !exe) exe = "game/usa/MAIN.EXE";   /* no image: the extracted files (stage 1 / 2) */
    {   /* saves next to an image named on the command line (the launcher passes --save-dir) */
        extern const char *port_disc_image, *port_save_dir;
        static char dir[1024];
        if (port_disc_image && !port_save_dir) {
            const char *p = port_disc_path(); int k = 0, d = 0;
            for (; p[k] && k < 1023; k++) { dir[k] = p[k]; if (p[k] == '/' || p[k] == '\\') d = k; }
            dir[d ? d : 0] = 0; if (!d) { dir[0] = '.'; dir[1] = 0; }
            port_save_dir = dir;
        }
    }
    u32 entry = load_exe(exe, &sp);
    if (entry_override) entry = entry_override;
    init_io();
    port_printf("[port] %d native game functions, %d shimmed Psy-Q functions; starting %08x in the MIPS interpreter\n",
                port_funcmap_count, port_libmap_count, entry);
    static const u32p args[8];
    port_mips_call(entry, args);
    port_printf("[port] the entry point returned (frame %d)\n", port_frame);
    { extern void port_audio_quit(void); port_audio_quit(); }
    { extern void port_stub_report(void); port_stub_report(); }
    return 0;
}


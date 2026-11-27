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

/* PS-X EXE: header 0x800 bytes, pc0 at 0x10, t_addr 0x18, t_size 0x1C, sp 0x30 */
static u32 load_exe(const char *path, u32 *sp_out) {
    int fd = port_open(path);
    if (fd < 0) port_fatal("cannot open %s (the USA MAIN.EXE: run tools/session_bootstrap.sh or pass --exe)", path);
    u8 h[0x800];
    if (port_read(fd, h, 0x800) != 0x800 || h[0] != 'P' || h[1] != 'S' || h[2] != '-' || h[3] != 'X')
        port_fatal("%s is not a PS-X EXE", path);
    u32 pc = *(u32 *)(h + 0x10), taddr = *(u32 *)(h + 0x18), tsize = *(u32 *)(h + 0x1C);
    if (taddr < PSX_RAM_BASE || taddr + tsize > PSX_RAM_BASE + PSX_RAM_SIZE) port_fatal("%s: load address %08x out of RAM", path, taddr);
    int got = port_pread(fd, (void *)(unsigned long)taddr, (int)tsize, 0x800);
    port_close(fd);
    if (got != (int)tsize) port_fatal("%s: short read (%d of %u bytes)", path, got, tsize);
    port_printf("[port] loaded %s: %u bytes at %08x, entry %08x\n", path, tsize, taddr, pc);
    if (sp_out) *sp_out = *(u32 *)(h + 0x30);
    return pc;
}

/* hardware registers the game polls, set to "idle / ready" (the page is plain memory) */
static void init_io(void) {
    *(volatile u32 *)0x1F801814u = 0x1C802000u;   /* GPUSTAT: ready for commands, DMA, VRAM transfers; interlace off */
    *(volatile u32 *)0x1F801070u = 0;             /* I_STAT */
}

int port_main(int argc, char **argv) {
    const char *exe = "game/usa/MAIN.EXE";
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
        else if (streq(argv[i], "--no-interp")) port_interp = 0;
        else if (streq(argv[i], "--interp") && i + 1 < argc) {
            extern u32p port_force_interp[8]; u32 v = hex_(argv[++i]);
            for (int k = 0; k < 8; k++) if (!port_force_interp[k]) { port_force_interp[k] = v; break; }
        }
        else if (streq(argv[i], "--trace-interp")) { extern int port_mips_trace; port_mips_trace = 1; }
        else if (streq(argv[i], "--entry") && i + 1 < argc) entry_override = hex_(argv[++i]);
        else if (streq(argv[i], "-v")) port_verbose++;
        else {
            port_printf("usage: %s [--exe MAIN.EXE] [--data DIR] [--frames N] [--dump-frames DIR] [--dump-every N] [--dump-vram]\n"
                        "       [--realtime] [--hz 50|60] [--trace-cd] [--no-interp] [--interp ADDR] [--trace-interp]\n"
                        "       [--entry ADDR] [-v]\n", argv[0]);
            return 2;
        }
    }
    port_setup_memory();
    u32 sp = 0;
    u32 entry = load_exe(exe, &sp);
    if (entry_override) entry = entry_override;
    init_io();
    port_printf("[port] %d native game functions, %d shimmed Psy-Q functions; starting %08x in the MIPS interpreter\n",
                port_funcmap_count, port_libmap_count, entry);
    static const u32p args[8];
    port_mips_call(entry, args);
    port_printf("[port] the entry point returned (frame %d)\n", port_frame);
    { extern void port_stub_report(void); port_stub_report(); }
    return 0;
}

/* no window yet (stage 1 is headless): the hooks gpu.c / pad.c call */
void port_window_frame(const u8 *rgb, int w, int h) { (void)rgb; (void)w; (void)h; }
int port_window_poll_pad(u16 *out) { (void)out; return 0; }

/* Psy-Q library replacements for the port prototype (headless).
 * Grouped like the Psy-Q libraries: libapi (BIOS: events, threads, critical sections), libetc (VSync,
 * callbacks), libgpu (VRAM transfers, ordering tables, environments), libgte (matrix helpers on the software
 * GTE), libcd (a virtual disc made of the extracted files in game/usa), libpress (movies skipped).
 * From Tombi-Decomp's port/shims/psyq.c (MIT, same author), cut down and adapted to Tomba! 2 (Psy-Q 4.4 names, the
 * virtual disc).  A shim replaces the Psy-Q function of the same name: gen_t2.py maps its retail address here. */
#include "port_runtime.h"

typedef unsigned char u8; typedef unsigned short u16; typedef short s16; typedef int s32; typedef unsigned int u32;
typedef struct { s16 x, y, w, h; } RECT;
void *memcpy(void *d, const void *s, unsigned int n);
typedef struct { s16 m[3][3]; s32 t[3]; } MATRIX;
typedef struct { s32 vx, vy, vz, pad; } VECTOR;
typedef struct { s16 vx, vy, vz, pad; } SVECTOR;

/* ================================================================== libapi / libetc */
void *port_vsync_event_fn;          /* OpenEvent(RCntCNT3 / VBlank, ...) handler: the game's vblankHandler (set in card.c) */
static void (*vsync_cb)(void);
static void *vsync_cbs[4];
static int cd_reads, cd_sectors;
static void cd_vblank(void);
int port_frame;
int port_max_frames;
static unsigned long long vblank_epoch_us;   /* absolute schedule: vblank n is due at epoch + n * 1e6 / hz */
static unsigned vblank_n;
int port_stall_frame, port_stall_ms;             /* --stall FRAME:MS (test hook): sleep MS ms before that vblank */
int port_show_fps;                              /* --show-fps: log the measured vblank rate every second; 2: with a histogram of the inter-vblank intervals */
static unsigned vb_hist[12];                    /* ms buckets: <10,10-14,15-17,18-19,20-21,22-24,25-29,30-39,40-59,60-99,100-199,>=200 */
static unsigned long long vb_last_us, vb_max_us;
static unsigned long long vb_total_n, vb_total_t0;
static int vb_bucket(unsigned long long us) {
    unsigned ms = (unsigned)((us + 500) / 1000);   /* nearest ms */
    return ms < 10 ? 0 : ms < 15 ? 1 : ms < 18 ? 2 : ms < 20 ? 3 : ms < 22 ? 4 : ms < 25 ? 5 : ms < 30 ? 6 : ms < 40 ? 7 : ms < 60 ? 8 : ms < 100 ? 9 : ms < 200 ? 10 : 11;
}
static const char *const vb_names[12] = { "<10", "10-14", "15-17", "18-19", "20-21", "22-24", "25-29", "30-39", "40-59", "60-99", "100-199", ">=200" };
static void vb_hist_print(const char *when) {
    char line[320]; int n = 0;
    for (int i = 0; i < 12; i++) if (vb_hist[i]) {
        const char *s = vb_names[i]; while (*s && n < 300) line[n++] = *s++;
        line[n++] = ':';
        unsigned v = vb_hist[i]; char b[12]; int k = 0; do { b[k++] = '0' + v % 10; v /= 10; } while (v);
        while (k && n < 300) line[n++] = b[--k];
        line[n++] = ' ';
    }
    line[n] = 0;
    port_printf("[port] vblank intervals (ms:count) %s: %s max %d.%d ms\n", when, line, (int)(vb_max_us / 1000), (int)(vb_max_us / 100 % 10));
    for (int i = 0; i < 12; i++) vb_hist[i] = 0;
    vb_max_us = 0;
}
/* the normal exit (frame limit reached, viewer closed): the pacing summary and the tally of emulated low accesses
   (a non-zero count on Windows means a KUSEG idiom the mask rewrite does not know: see "Windows build" in PORT.md) */
void port_quit(int code) {
    extern void port_low_report(void); extern int port_realtime;
    if (port_realtime && vb_total_n > 1) {
        unsigned long long t = port_time_us() - vb_total_t0;
        if (t) port_printf("[port] paced: %llu vblanks in %llu.%03llu s = %llu.%02llu vblank/s overall\n", vb_total_n, t / 1000000ull, t / 1000 % 1000,
                           vb_total_n * 1000000ull / t, vb_total_n * 100000000ull / t % 100);
        if (port_show_fps >= 2) vb_hist_print("at exit");
    }
    port_low_report();
    port_exit(code);
}
int port_realtime = 0;               /* 0 = run as fast as possible (headless), 1 = paced at port_hz */
int port_hz = 50;                    /* vblanks per second when paced: 50 (PAL, default) or 60 (--hz 60) */

static void call_psx(void *fn) {
    void (*f)(void) = (void (*)(void))fn;
    if ((u32)fn >= 0x80000000u && (u32)fn < 0x80200000u) f = (void (*)(void))port_resolve_call((u32)fn, "event handler");
    f();
}

void port_vblank(void) {
    if (port_realtime) {
        unsigned long long now = port_time_us(), period = 1000000ull / (unsigned)port_hz;
        if (!vblank_epoch_us) { vblank_epoch_us = now; vblank_n = 0; }
        vblank_n++;
        unsigned long long due = vblank_epoch_us + (unsigned long long)vblank_n * 1000000ull / (unsigned)port_hz;
        if (now > due + period) { vblank_epoch_us = now - (unsigned long long)vblank_n * 1000000ull / (unsigned)port_hz; due = now; }
        else if (due > now) port_sleep_until_us(due);
        { unsigned long long t = port_time_us(); if (!vb_total_t0) vb_total_t0 = t; vb_total_n++;
          if (vb_last_us) { unsigned long long d = t - vb_last_us; vb_hist[vb_bucket(d)]++; if (d > vb_max_us) vb_max_us = d; }
          vb_last_us = t; }
    }
    port_frame++;
    { extern void port_pad_vblank(void); port_pad_vblank(); }
    cd_vblank();
    for (int i = 0; i < 4; i++) if (vsync_cbs[i]) call_psx(vsync_cbs[i]);
    if (port_vsync_event_fn) call_psx(port_vsync_event_fn);
    if (vsync_cb) call_psx((void *)vsync_cb);
    port_gpu_vblank();
    if (port_frame % 100 == 0) {
        extern int port_gpu_lists(void), port_gpu_packets(void);
        port_printf("[port] frame %d: %d CD reads (%d sectors), %d ordering tables drawn (%d packets), %d interpreted calls\n",
                    port_frame, cd_reads, cd_sectors, port_gpu_lists(), port_gpu_packets(), port_mips_calls());
    }
    if (port_max_frames && port_frame >= port_max_frames) {
        extern void port_stub_report(void);
        port_printf("[port] reached %d frames, stopping\n", port_frame);
        port_stub_report();
        port_quit(0);
    }
}

int EnterCriticalSection(void) { return 1; }
void ExitCriticalSection(void) {}
/* OpenEvent/CloseEvent/TestEvent/DeliverEvent: shims/card.c (the memory card is the only event source) */
int EnableEvent(int ev) { return 1; }
int DisableEvent(int ev) { return 1; }
int WaitEvent(int ev) { return 1; }
int OpenTh(void *fn, u32 sp, u32 gp) { return port_thread_open(fn); }
/* OpenEvent: the VBlank / root-counter events run their handler every vblank (EvSpINT 0xF2000003 = RCnt3) */
int OpenEvent(u32 desc, int spec, int mode, void *fn) {
    if (port_verbose) port_printf("[port] OpenEvent(%08x, %x, %x, %p)\n", desc, spec, mode, fn);
    if ((desc == 0xF2000003u || desc == 0xF0000001u) && fn) port_vsync_event_fn = fn;
    return 0xF1000000 | (desc & 0xFF);
}
int CloseEvent(int ev) { return 1; }
int TestEvent(int ev) { return 0; }
void DeliverEvent(u32 a, u32 b) {}
int SetRCnt(u32 c, u16 t, int m) { return 1; }
int StartRCnt(u32 c) { return 1; }
int StopRCnt(u32 c) { return 1; }
int ResetRCnt(u32 c) { return 1; }
int GetRCnt(u32 c) { return 0; }
int GetIntrMask(void) { return 0; }
int SetIntrMask(int m) { return 0; }
void *SetCustomExitFromException(void *p) { return 0; }
int ReturnFromException(void) { return 0; }
void HookEntryInt(void *p) {}
void ResetEntryInt(void) {}
int ChangeTh(int h) { port_thread_change(h); return 1; }
int CloseTh(int h) { port_thread_close(h); return 1; }
void FlushCache(void) {}
u32 GetGp(void) { return 0; }
void SysEnqIntRP(int p, void *q) {}
void SysDeqIntRP(int p, void *q) {}
int ChangeClearRCnt(int t, int m) { return 0; }
int ChangeClearPAD(int v) { return 0; }
int SetVideoMode(int m) { return 1; /* PAL */ }
int GetVideoMode(void) { return 1; }
void InitHeap(void *p, u32 n) {}
int ResetCallback(void) { return 0; }
int StopCallback(void) { return 0; }
int RestartCallback(void) { return 0; }
int VSyncCallback(void (*f)(void)) { if (f && port_verbose) port_printf("[port] VSyncCallback(%p) registered\n", (void *)f); vsync_cb = f; return 0; }
int VSyncCallbacks(int n, void (*f)(void)) { if (n >= 0 && n < 4) vsync_cbs[n] = (void *)f; return 0; }
int DMACallback(int ch, void *f) { return 0; }
int InterruptCallback(int n, void *f) { return 0; }
void _96_remove(void) {}

int VSync(int mode) {
    static int last;
    if (mode < 0) return port_frame;
    if (mode == 1) { int r = port_frame - last; return r; }
    int n = mode == 0 ? 1 : mode;
    for (int i = 0; i < n; i++) port_vblank();
    int r = port_frame - last; last = port_frame;
    return r;
}

/* memory card: shims/card.c */

/* ================================================================== libgpu: see gpu.c */

/* ================================================================== libgte */
void port_gte_ctc2(int r, unsigned long v);
unsigned long port_gte_cfc2(int r);
void port_gte_mtc2(int r, unsigned long v);
unsigned long port_gte_mfc2(int r);
void port_gte_op(unsigned long op);
#define PK(a, b) (((u32)(u16)(a)) | ((u32)(u16)(b) << 16))
static void load_matrix(int base, MATRIX *m) {
    port_gte_ctc2(base, PK(m->m[0][0], m->m[0][1])); port_gte_ctc2(base + 1, PK(m->m[0][2], m->m[1][0]));
    port_gte_ctc2(base + 2, PK(m->m[1][1], m->m[1][2])); port_gte_ctc2(base + 3, PK(m->m[2][0], m->m[2][1]));
    port_gte_ctc2(base + 4, (u16)m->m[2][2]);
}
void InitGeom(void) { port_gte_ctc2(29, 0x155); port_gte_ctc2(30, 0x100); port_gte_ctc2(26, 1000);
                      port_gte_ctc2(27, -0x1062); port_gte_ctc2(28, 0x1400000); }
void SetGeomScreen(int h) { port_gte_ctc2(26, h); }
void SetGeomOffset(int x, int y) { port_gte_ctc2(24, x << 16); port_gte_ctc2(25, y << 16); }
void SetRotMatrix(MATRIX *m) { load_matrix(0, m); }
void SetLightMatrix(MATRIX *m) { load_matrix(8, m); }
void SetColorMatrix(MATRIX *m) { load_matrix(16, m); }
void SetTransMatrix(MATRIX *m) { port_gte_ctc2(5, m->t[0]); port_gte_ctc2(6, m->t[1]); port_gte_ctc2(7, m->t[2]); }
void SetBackColor(int r, int g, int b) { port_gte_ctc2(13, r << 4); port_gte_ctc2(14, g << 4); port_gte_ctc2(15, b << 4); }
void SetFarColor(int r, int g, int b) { port_gte_ctc2(21, r << 4); port_gte_ctc2(22, g << 4); port_gte_ctc2(23, b << 4); }

/* rsin/rcos: 4096 = 1.0 over a 4096-step circle; table built once with a Taylor series (no libm) */
static s16 sintab[1025];
static void sin_init(void) {
    if (sintab[1024]) return;
    for (int i = 0; i <= 1024; i++) {
        double x = i * (3.14159265358979323846 / 2048.0), t = x, s = x;
        for (int k = 1; k < 12; k++) { t *= -x * x / ((2 * k) * (2 * k + 1)); s += t; }
        sintab[i] = (s16)(s * 4096.0 + 0.5);
    }
}
int rsin(int a) {
    sin_init();
    a &= 4095;
    if (a < 1024) return sintab[a];
    if (a < 2048) return sintab[2048 - a];
    if (a < 3072) return -sintab[a - 2048];
    return -sintab[4096 - a];
}
int rcos(int a) { return rsin(a + 1024); }
int ratan2(int y, int x) {
    /* binary search on the angle: monotone in the first octant */
    int neg_y = y < 0, neg_x = x < 0, swap;
    unsigned ay = neg_y ? -y : y, ax = neg_x ? -x : x;
    if (!ax && !ay) return 0;
    swap = ay > ax;
    unsigned num = swap ? ax : ay, den = swap ? ay : ax;        /* ratio <= 1 */
    int lo = 0, hi = 512;                                        /* 0..45 degrees */
    while (lo < hi) {
        int m = (lo + hi + 1) / 2;
        if ((long long)rsin(m) * den <= (long long)rcos(m) * num) lo = m; else hi = m - 1;
    }
    int a = swap ? 1024 - lo : lo;
    if (neg_x) a = 2048 - a;
    if (neg_y) a = -a;
    return a;
}
static u32 isqrt(u32 v) { u32 r = 0, b = 1u << 30; while (b > v) b >>= 2;
    while (b) { if (v >= r + b) { v -= r + b; r = (r >> 1) + b; } else r >>= 1; b >>= 2; } return r; }
int SquareRoot0(int v) { return isqrt((u32)v); }
int csqrt(int v) { return (int)isqrt((u32)v << 12 >> 0) ; }  /* fixed 20.12 */

MATRIX *RotMatrixX(int r, MATRIX *m) {
    int s = rsin(r), c = rcos(r);
    for (int i = 0; i < 3; i++) {
        int a = m->m[1][i], b = m->m[2][i];
        m->m[1][i] = (c * a - s * b) >> 12; m->m[2][i] = (s * a + c * b) >> 12;
    }
    return m;
}
MATRIX *RotMatrixY(int r, MATRIX *m) {
    int s = rsin(r), c = rcos(r);
    for (int i = 0; i < 3; i++) {
        int a = m->m[0][i], b = m->m[2][i];
        m->m[0][i] = (c * a + s * b) >> 12; m->m[2][i] = (-s * a + c * b) >> 12;
    }
    return m;
}
MATRIX *RotMatrixZ(int r, MATRIX *m) {
    int s = rsin(r), c = rcos(r);
    for (int i = 0; i < 3; i++) {
        int a = m->m[0][i], b = m->m[1][i];
        m->m[0][i] = (c * a - s * b) >> 12; m->m[1][i] = (s * a + c * b) >> 12;
    }
    return m;
}
MATRIX *RotMatrix(SVECTOR *r, MATRIX *m) {
    /* Psy-Q RotMatrix: M = Rx * Ry * Rz applied as rotate Z, then Y, then X */
    int sx = rsin(r->vx), cx = rcos(r->vx), sy = rsin(r->vy), cy = rcos(r->vy), sz = rsin(r->vz), cz = rcos(r->vz);
    m->m[0][0] = (cy * cz) >> 12;
    m->m[0][1] = -(cy * sz) >> 12;
    m->m[0][2] = sy;
    m->m[1][0] = ((cx * sz) >> 12) + (((sx * sy) >> 12) * cz >> 12);
    m->m[1][1] = ((cx * cz) >> 12) - (((sx * sy) >> 12) * sz >> 12);
    m->m[1][2] = -(sx * cy) >> 12;
    m->m[2][0] = ((sx * sz) >> 12) - (((cx * sy) >> 12) * cz >> 12);
    m->m[2][1] = ((sx * cz) >> 12) + (((cx * sy) >> 12) * sz >> 12);
    m->m[2][2] = (cx * cy) >> 12;
    return m;
}
MATRIX *MulMatrix0(MATRIX *a, MATRIX *b, MATRIX *c) {
    MATRIX t;
    for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++)
        t.m[i][j] = (a->m[i][0] * b->m[0][j] + a->m[i][1] * b->m[1][j] + a->m[i][2] * b->m[2][j]) >> 12;
    for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) c->m[i][j] = t.m[i][j];
    return c;
}
VECTOR *ApplyMatrix(MATRIX *m, SVECTOR *v, VECTOR *r) {
    s32 x = v->vx, y = v->vy, z = v->vz;
    r->vx = (m->m[0][0] * x + m->m[0][1] * y + m->m[0][2] * z) >> 12;
    r->vy = (m->m[1][0] * x + m->m[1][1] * y + m->m[1][2] * z) >> 12;
    r->vz = (m->m[2][0] * x + m->m[2][1] * y + m->m[2][2] * z) >> 12;
    return r;
}
SVECTOR *ApplyMatrixSV(MATRIX *m, SVECTOR *v, SVECTOR *r) {
    VECTOR t; ApplyMatrix(m, v, &t); r->vx = t.vx; r->vy = t.vy; r->vz = t.vz; return r;
}
VECTOR *ApplyMatrixLV(MATRIX *m, VECTOR *v, VECTOR *r) {
    long long x = v->vx, y = v->vy, z = v->vz;
    r->vx = (s32)((m->m[0][0] * x + m->m[0][1] * y + m->m[0][2] * z) >> 12);
    r->vy = (s32)((m->m[1][0] * x + m->m[1][1] * y + m->m[1][2] * z) >> 12);
    r->vz = (s32)((m->m[2][0] * x + m->m[2][1] * y + m->m[2][2] * z) >> 12);
    return r;
}
VECTOR *ApplyRotMatrix(SVECTOR *v, VECTOR *r) {
    port_gte_mtc2(0, PK(v->vx, v->vy)); port_gte_mtc2(1, (u16)v->vz);
    port_gte_op(0x00486012);   /* MVMVA sf=1 mx=RT v=V0 cv=none */
    r->vx = (s32)port_gte_mfc2(25); r->vy = (s32)port_gte_mfc2(26); r->vz = (s32)port_gte_mfc2(27);
    return r;
}
int RotTransPers(SVECTOR *v, s32 *sxy, s32 *p, s32 *flag) {
    port_gte_mtc2(0, PK(v->vx, v->vy)); port_gte_mtc2(1, (u16)v->vz);
    port_gte_op(0x00180001);
    *sxy = (s32)port_gte_mfc2(14); *p = (s32)port_gte_mfc2(8); *flag = (s32)port_gte_cfc2(31);
    return (s32)port_gte_mfc2(19) >> 2;
}

#include "cd_virtual.inc"

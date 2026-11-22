// CC gcc-2.8.1-psx
// FLAGS -O2 -G0 -mno-split-addresses
// AS gnu
#include "common.h"
typedef struct { s16 x, y, w, h; } RECT;
typedef struct {
    RECT clip;      /* 0x00 */
    s16 ofs[2];     /* 0x08 */
    RECT tw;        /* 0x0C */
    u16 tpage;      /* 0x14 */
    u8 dtd;         /* 0x16 */
    u8 dfe;         /* 0x17 */
    u8 isbg;        /* 0x18 */
    u8 r0, g0, b0;  /* 0x19 */
    u32 dr_env[16]; /* 0x1C */
} DRAWENV;
typedef struct {
    RECT disp;      /* 0x00 */
    RECT screen;    /* 0x08 */
    u8 isinter;     /* 0x10 */
    u8 isrgb24;     /* 0x11 */
    u8 pad0, pad1;
} DISPENV;
typedef struct { u8 version; u8 queue; u8 level; u8 reverse; s16 w; s16 h; u8 pad8[8]; DRAWENV draw; DISPENV disp; } GEnvT;
extern GEnvT D_800A59A0;
typedef struct { void *f[16]; } GPUF;
extern GPUF *D_800A5998;
extern u8 D_800A5958[];
extern s32 D_800A5A20[];
extern s32 D_800A5A2C[];
extern char D_8001BE38[];
extern char D_8001BE58[];
extern s32 (*D_800A599C)();
void func_80083AF8(void *, s32, s32);
s32 func_80083214(s32);
void GPU_cw(u32);
#define GENV_VERSION (*(volatile u8 *)&D_800A59A0.version)

s32 ResetGraph(s32 mode) {
    switch (mode & 7) {
    case 3:
    case 0:
        printf(D_8001BE38, D_800A5958, &D_800A59A0);
    case 5:
        func_80083AF8(&D_800A59A0, 0, 0x80);
        ResetCallback();
        GPU_cw((u32)D_800A5998 & 0xFFFFFF);
        D_800A59A0.version = func_80083214(mode);
        D_800A59A0.queue = 1;
        D_800A59A0.w = D_800A5A20[GENV_VERSION];
        D_800A59A0.h = D_800A5A2C[GENV_VERSION];
        func_80083AF8(&D_800A59A0.draw, -1, sizeof(DRAWENV));
        func_80083AF8(&D_800A59A0.disp, -1, sizeof(DISPENV));
        return D_800A59A0.version;
    }
    if (D_800A59A0.level >= 2) D_800A599C(D_8001BE58, mode);
    return ((s32 (*)(s32))D_800A5998->f[13])(1);
}

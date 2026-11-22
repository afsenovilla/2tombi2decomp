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
extern GEnvT D_80025514;
typedef struct { void *f[16]; } GPUF;
extern GPUF *D_8002550C;
extern u8 D_800254CC[];
extern s32 D_80025594[];
extern s32 D_800255A0[];
extern char D_8001017C[];
extern char D_8001019C[];
extern s32 (*D_80025510)();
void func_80015DD4(void *, s32, s32);
s32 func_800154F0(s32);
void GPU_cw(u32);
#define GENV_VERSION (*(volatile u8 *)&D_80025514.version)

s32 ResetGraph(s32 mode) {
    switch (mode & 7) {
    case 3:
    case 0:
        printf(D_8001017C, D_800254CC, &D_80025514);
    case 5:
        func_80015DD4(&D_80025514, 0, 0x80);
        ResetCallback();
        GPU_cw((u32)D_8002550C & 0xFFFFFF);
        D_80025514.version = func_800154F0(mode);
        D_80025514.queue = 1;
        D_80025514.w = D_80025594[GENV_VERSION];
        D_80025514.h = D_800255A0[GENV_VERSION];
        func_80015DD4(&D_80025514.draw, -1, sizeof(DRAWENV));
        func_80015DD4(&D_80025514.disp, -1, sizeof(DISPENV));
        return D_80025514.version;
    }
    if (D_80025514.level >= 2) D_80025510(D_8001019C, mode);
    return ((s32 (*)(s32))D_8002550C->f[13])(1);
}

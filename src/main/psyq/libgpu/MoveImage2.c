// CC gcc-2.8.1-psx
// FLAGS -O2 -G0 -mno-split-addresses
// ASPSX 2.79
#include "common.h"
typedef struct { s16 x, y, w, h; } RECT_;
typedef struct { void *f[16]; } GPUF;
extern GPUF *D_800A5998;
extern volatile s32 *D_800A5AA8;
extern volatile s32 *D_800A5AB4;
extern s32 D_800A5ADC;
extern s32 D_800A5AE0;
s32 VSync(s32);
void checkRECT(char *, RECT_ *);
s32 func_800834D4(void);
void DMACallback(s32, void *);
void _GPU_ResetCallback(void);
extern char D_8001BF44[];
extern u32 move_image[];

s32 MoveImage2(RECT_ *rect, s32 x, s32 y) {
    checkRECT(D_8001BF44, rect);
    D_800A5ADC = VSync(-1) + 240;
    D_800A5AE0 = 0;
    while ((*D_800A5AB4 & 0x01000000) || !(*D_800A5AA8 & 0x04000000)) {
        if (func_800834D4()) return -1;
    }
    DMACallback(2, _GPU_ResetCallback);
    if (rect->w == 0 || rect->h == 0) return -1;
    move_image[2] = *(u32 *)&rect->x;
    move_image[3] = (y << 16) | (x & 0xFFFF);
    move_image[4] = *(u32 *)&rect->w;
    ((void (*)(u32 *))D_800A5998->f[6])(move_image);
    return 0;
}

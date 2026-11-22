// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// AS gnu
#include "common.h"
typedef struct { s16 x, y, w, h; } RECT_;
typedef struct { void *f[16]; } GPUF;
extern GPUF *D_800A5998;
extern volatile s32 *D_800A5AA8;
extern volatile s32 *D_800A5AB4;
extern s32 D_800A5ADC;
extern s32 D_800A5AE0;
extern char D_8001C014[];
s32 VSync(s32);
void checkRECT(char *, RECT_ *);
s32 func_800834D4(void);
void DMACallback(s32, void *);
void _GPU_ResetCallback(void);

s32 LoadImage2(RECT_ *rect, u32 *p) {
    checkRECT(D_8001C014, rect);
    D_800A5ADC = VSync(-1) + 240;
    D_800A5AE0 = 0;
    while ((*D_800A5AB4 & 0x01000000) || !(*D_800A5AA8 & 0x04000000)) {
        if (func_800834D4()) return -1;
    }
    DMACallback(2, _GPU_ResetCallback);
    ((s32 (*)(RECT_ *, u32 *))D_800A5998->f[8])(rect, p);
    return 0;
}

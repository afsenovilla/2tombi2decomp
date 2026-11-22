// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// AS gnu
#include "common.h"
typedef struct { void *f[16]; } GPUF;
extern GPUF *D_8002550C;
extern volatile s32 *D_8002561C;
extern volatile s32 *D_80025628;
extern s32 D_80025650;
extern s32 D_80025654;
extern char D_800102C4[];
extern s32 (*D_80025510)();
extern u8 D_80025516;
s32 VSync(s32);
s32 func_800157B0(void);
void _GPU_ResetCallback(void);

s32 DrawOTag2(u32 *p) {
    if (D_80025516 >= 2) D_80025510(D_800102C4, p);
    D_80025650 = VSync(-1) + 240;
    D_80025654 = 0;
    while ((*D_80025628 & 0x01000000) || !(*D_8002561C & 0x04000000)) {
        if (func_800157B0()) return -1;
    }
    DMACallback(2, _GPU_ResetCallback);
    ((s32 (*)(u32 *))D_8002550C->f[6])(p);
    return 0;
}

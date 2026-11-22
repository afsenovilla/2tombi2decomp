// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// AS gnu
#include "common.h"
typedef struct { s16 x, y, w, h; } RECT_;
typedef struct { void *f[16]; } GPUF;
extern GPUF *D_8002550C;
extern volatile s32 *D_8002561C;
extern volatile s32 *D_80025628;
extern s32 D_80025650;
extern s32 D_80025654;
extern char D_80010358[];
s32 VSync(s32);
void func_800132B0(char *, RECT_ *);
s32 func_800157B0(void);
void DMACallback(s32, void *);
void _GPU_ResetCallback(void);

s32 LoadImage2(RECT_ *rect, u32 *p) {
    func_800132B0(D_80010358, rect);
    D_80025650 = VSync(-1) + 240;
    D_80025654 = 0;
    while ((*D_80025628 & 0x01000000) || !(*D_8002561C & 0x04000000)) {
        if (func_800157B0()) return -1;
    }
    DMACallback(2, _GPU_ResetCallback);
    ((s32 (*)(RECT_ *, u32 *))D_8002550C->f[8])(rect, p);
    return 0;
}

// CC gcc-2.8.1-psx
// FLAGS -O2 -G0 -mno-split-addresses
// AS gnu
#include "common.h"
typedef struct { u8 version; u8 queue; u8 level; u8 reverse; s16 w; s16 h; } GEnvT;
typedef struct { void *f[16]; } GPUF;
extern GEnvT D_80025514;
extern GPUF *gpu;
extern s32 (*GPU_printf)();
extern char D_800101DC[];
void DMACallback(s32, void *);

int SetGraphQueue(int mode) {
    u8 *q = &D_80025514.queue;
    int prev = *q;

    if (q[1] >= 2) {
        do { /* a debug-print macro: raises mode above q for s0 */
            GPU_printf(D_800101DC, mode);
        } while (0);
    }
    if (mode != *q) {
        ((void (*)(s32))gpu->f[13])(1);
        *q = mode;
        DMACallback(2, 0);
    }
    return prev;
}

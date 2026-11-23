// CC gcc-2.8.1-psx
// FLAGS -O2 -G0 -mno-split-addresses
// AS gnu
#include "common.h"
typedef struct { u8 version; u8 queue; u8 level; u8 reverse; s16 w; s16 h; } GEnvT;
typedef struct { void *f[16]; } GPUF;
extern GEnvT D_800A59A0;
extern GPUF *D_800A5998;
extern s32 (*D_800A599C)();
extern char D_8001BE98[];
void DMACallback(s32, void *);

int SetGraphQueue(int mode) {
    u8 *q = &D_800A59A0.queue;
    int prev = *q;

    if (q[1] >= 2) {
        do { /* a debug-print macro: raises mode above q for s0 */
            D_800A599C(D_8001BE98, mode);
        } while (0);
    }
    if (mode != *q) {
        ((void (*)(s32))D_800A5998->f[13])(1);
        *q = mode;
        DMACallback(2, 0);
    }
    return prev;
}

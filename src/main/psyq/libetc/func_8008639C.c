// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// AS gnu
// Source: psy-q-decomp (github.com/sozud/psy-q-decomp, MIT) src/etc/intr_dma.c, function trapIntrDMA.
#include "common.h"
extern char D_8001C0A0[];
extern char D_8001C0BC[];
typedef unsigned long u_long;
typedef void (*Callback)();
extern volatile u_long* dma_dicr;
extern Callback dma_callbacks[8];
extern unsigned long* D_800ABE14;

void func_8008639C(void) {
    u32 mask;
    int i;
    while ((mask = (*dma_dicr >> 24) & 0x7f) != 0) {
        for (i = 0; mask != 0 && i < 7; i++, mask >>= 1) {
            if (mask & 1) {
                *dma_dicr &= (0xffffff | (1 << (i + 24)));
                if (dma_callbacks[i] != (0)) {
                    dma_callbacks[i]();
                }
            }
        }
    }
    if ((*dma_dicr & 0xFF000000) == 0x80000000 || *dma_dicr & 0x8000) {
        printf(D_8001C0A0, *dma_dicr);
        for (i = 0; i < 7; i++) {
            printf(D_8001C0BC, i, D_800ABE14[4 * i]);
        }
    }
}

// CC gcc-2.8.1-psx
// FLAGS -O2 -G0 -mno-split-addresses
// AS gnu
// EPILOGUE sony
#include "common.h"
typedef struct { u32 addr; u32 size; } Blk;
extern s32 D_800AC664;
extern Blk *D_800AC66C;
void _spu_gcSPU(void);

void SpuFree(u32 addr) {
    s32 i;
    for (i = 0; i < D_800AC664; i++) {
        if (D_800AC66C[i].addr & 0x40000000) break;
        if (D_800AC66C[i].addr == addr) { D_800AC66C[i].addr = addr | 0x80000000; break; }
    }
    _spu_gcSPU();
}

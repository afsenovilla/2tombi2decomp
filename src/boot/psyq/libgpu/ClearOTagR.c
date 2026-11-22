// CC gcc-2.8.1-psx
// FLAGS -O2 -G0 -mno-split-addresses
// ASPSX 2.79
#include "common.h"
typedef struct { u8 pad[0x2C]; void (*otc)(u32 *, s32); } GpuCb;
extern GpuCb *D_8002550C;
extern s32 (*D_80025510)();
extern u8 D_80025516;
extern u32 D_800255D4;
extern u32 D_800255C0;
extern char D_800102AC[];

u32 *ClearOTagR(u32 *ot, s32 n) {
    u32 *t;
    if (D_80025516 >= 2) D_80025510(D_800102AC, ot, n);
    D_8002550C->otc(ot, n);
    t = &D_800255D4;
    *t = ((u32)&D_800255C0 & 0xFFFFFF) | 0x04000000;
    *ot = (u32)t & 0xFFFFFF;
    return ot;
}

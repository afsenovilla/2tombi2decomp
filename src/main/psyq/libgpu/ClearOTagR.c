// CC gcc-2.8.1-psx
// FLAGS -O2 -G0 -mno-split-addresses
// ASPSX 2.79
#include "common.h"
typedef struct { u8 pad[0x2C]; void (*otc)(u32 *, s32); } GpuCb;
extern GpuCb *D_800A5998;
extern s32 (*D_800A599C)();
extern u8 D_800A59A2;
extern u32 D_800A5A60;
extern u32 D_800A5A4C;
extern char D_8001BF68[];

u32 *ClearOTagR(u32 *ot, s32 n) {
    u32 *t;
    if (D_800A59A2 >= 2) D_800A599C(D_8001BF68, ot, n);
    D_800A5998->otc(ot, n);
    t = &D_800A5A60;
    *t = ((u32)&D_800A5A4C & 0xFFFFFF) | 0x04000000;
    *ot = (u32)t & 0xFFFFFF;
    return ot;
}

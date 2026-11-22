// CC gcc-2.8.1-psx
// FLAGS -O2 -G0 -mno-split-addresses
// ASPSX 2.79
#include "common.h"
extern s32 (*D_80025510)();
extern u8 D_80025516;
extern u32 D_800255D4;
extern u32 D_800255C0;
extern char D_80010294[];
typedef struct { unsigned addr : 24; unsigned len : 8; } P_TAG;
#define setlen(p, _len) (((P_TAG *)(p))->len = (u8)(_len))
#define setaddr(p, _addr) (((P_TAG *)(p))->addr = (u32)(_addr))

u32 *ClearOTag(u32 *ot, s32 n) {
    u32 *t;
    if (D_80025516 >= 2) D_80025510(D_80010294, ot, n);
    while (--n) {
        setlen(ot, 0);
        setaddr(ot, ot + 1);
        ot++;
    }
    t = &D_800255D4;
    *t = ((u32)&D_800255C0 & 0xFFFFFF) | 0x04000000;
    *ot = (u32)t & 0xFFFFFF;
    return ot;
}

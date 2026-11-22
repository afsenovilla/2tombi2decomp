// CC gcc-2.8.1-psx
// FLAGS -O2 -G0 -mno-split-addresses
// ASPSX 2.79
#include "common.h"
extern s32 (*D_800A599C)();
extern u8 D_800A59A2;
extern u32 D_800A5A60;
extern u32 D_800A5A4C;
extern char D_8001BF50[];
typedef struct { unsigned addr : 24; unsigned len : 8; } P_TAG;
#define setlen(p, _len) (((P_TAG *)(p))->len = (u8)(_len))
#define setaddr(p, _addr) (((P_TAG *)(p))->addr = (u32)(_addr))

u32 *ClearOTag(u32 *ot, s32 n) {
    u32 *t;
    if (D_800A59A2 >= 2) D_800A599C(D_8001BF50, ot, n);
    while (--n) {
        setlen(ot, 0);
        setaddr(ot, ot + 1);
        ot++;
    }
    t = &D_800A5A60;
    *t = ((u32)&D_800A5A4C & 0xFFFFFF) | 0x04000000;
    *ot = (u32)t & 0xFFFFFF;
    return ot;
}

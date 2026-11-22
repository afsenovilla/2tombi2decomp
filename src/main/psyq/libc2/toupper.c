// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// ASPSX 2.79
#include "common.h"
extern u8 D_800ACE75[];

s8 toupper(s8 c) {
    if (D_800ACE75[(u8)c] & 2) c -= 0x20;
    return c;
}

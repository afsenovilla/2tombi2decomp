// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// ASPSX 2.79
#include "common.h"
extern u8 D_80027229[];

s8 tolower(s8 c) {
    if (D_80027229[(u8)c] & 1) c += 0x20;
    return c;
}

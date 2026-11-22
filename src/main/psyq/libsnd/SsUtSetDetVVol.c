// CC gcc-2.8.1-psx
// AS gnu
// FLAGS -O2 -G0 -mno-split-addresses
// RETURN sony first
#include "common.h"
typedef struct { s16 l, r; u8 pad[12]; } VVol;
extern VVol D_80105A28[];
extern u8 D_80105A08[];

s16 SsUtSetDetVVol(s16 vc, s16 l, s16 r) {
    if ((u16)vc >= 24) return -1;
    D_80105A28[vc].r = r;
    D_80105A28[vc].l = l;
    D_80105A08[vc] |= 3;
    return 0;
}

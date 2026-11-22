// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// AS gnu
#include "common.h"
extern u8 D_800384F0[];
extern volatile u32 *D_8002561C;

void func_80014ECC(u32 x) { *D_8002561C = x; D_800384F0[x >> 24] = x; }

// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// AS gnu
#include "common.h"
extern volatile u32 *D_800A5AA8;
extern u8 D_80100B28[];

void func_80082BF0(u32 x) { *D_800A5AA8 = x; D_80100B28[x >> 24] = x; }

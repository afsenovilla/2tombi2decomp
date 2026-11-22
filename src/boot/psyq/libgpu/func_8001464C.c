// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// ASPSX 2.79
#include "common.h"

u32 func_8001464C(s16 x, s16 y) { return 0xE5000000 | ((y & 0x7FF) << 11) | (x & 0x7FF); }

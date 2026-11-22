// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// ASPSX 2.79
#include "common.h"

s32 func_800895E8(u8 *p) {
    if (*(u16 *)(p + 0xE6) == 0 || p[0x46] != 0xFF) return 1;
    return 0;
}

// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// ASPSX 2.79
#include "common.h"
extern u32 D_80105EE8;

s32 rand(void) {
    u32 temp_v0;

    temp_v0 = (D_80105EE8 * 0x41C64E6D) + 0x3039;
    D_80105EE8 = temp_v0;
    return (temp_v0 >> 0x10) & 0x7FFF;
}

// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// ASPSX 2.79
#include "common.h"
extern s32 *D_800A5AA4;
extern s32 *D_800A5AA8;

s32 func_80082CB0(s32 arg0) {
    *D_800A5AA8 = arg0 | 0x10000000;
    return *D_800A5AA4 & 0xFFFFFF;
}

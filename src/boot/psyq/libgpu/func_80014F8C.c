// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// ASPSX 2.79
#include "common.h"
extern s32 *D_80025618;
extern s32 *D_8002561C;

s32 func_80014F8C(s32 arg0) {
    *D_8002561C = arg0 | 0x10000000;
    return *D_80025618 & 0xFFFFFF;
}

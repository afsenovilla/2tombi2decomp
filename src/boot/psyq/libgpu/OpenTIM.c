// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// ASPSX 2.79
#include "common.h"
extern s32 D_80039DF8;

s32 OpenTIM(s32 arg0) {
    D_80039DF8 = arg0;
    return 0;
}

// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// ASPSX 2.79
#include "common.h"
extern u16 *D_800ABDA8;

u16 SetIntrMask(u16 arg0) {
    u16 temp_v0;

    temp_v0 = *D_800ABDA8;
    *D_800ABDA8 = arg0;
    return temp_v0;
}

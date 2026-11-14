// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// ASPSX 2.79
#include "common.h"
extern u16 *D_8002677C;

u16 SetIntrMask(u16 arg0) {
    u16 temp_v0;

    temp_v0 = *D_8002677C;
    *D_8002677C = arg0;
    return temp_v0;
}

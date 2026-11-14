// CC gcc-2.8.1-psx
// FLAGS -O2 -G0
// ASPSX 2.79
#include "common.h"
extern u8 D_800268DC;

u8 CdStatus(void) {
    return D_800268DC;
}

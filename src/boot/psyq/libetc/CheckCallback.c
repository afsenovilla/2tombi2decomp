// CC gcc-2.8.1-psx
// FLAGS -O2 -G0
// ASPSX 2.79
#include "common.h"
extern u16 D_800256EE;

u16 CheckCallback(void) {
    return D_800256EE;
}

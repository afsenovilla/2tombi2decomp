// CC gcc-2.8.1-psx
// FLAGS -O2 -G0
// ASPSX 2.79
#include "common.h"
extern u16 *D_8002677C;

u16 GetIntrMask(void) {
    return *D_8002677C;
}

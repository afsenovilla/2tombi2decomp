// CC gcc-2.8.1-psx
// FLAGS -O2 -G0
// ASPSX 2.79
#include "common.h"
s32 CD_vol();                                         /* extern */

s32 CdMix(void) {
    CD_vol();
    return 1;
}

// CC gcc-2.8.1-psx
// FLAGS -O2 -G0
// ASPSX 2.79
#include "common.h"
s32 CD_getsector();                                 /* extern */

s32 CdGetSector(void) {
    return CD_getsector() == 0;
}

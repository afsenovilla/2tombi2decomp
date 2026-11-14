// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// ASPSX 2.79
#include "common.h"
s32 CD_flush();                                       /* extern */

void CdFlush(void) {
    CD_flush();
}

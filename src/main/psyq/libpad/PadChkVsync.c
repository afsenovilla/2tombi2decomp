// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// ASPSX 2.79
#include "common.h"
s32 _padChkVsync();                                   /* extern */

void PadChkVsync(void) {
    _padChkVsync();
}

// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// ASPSX 2.79
#include "common.h"
s32 StopCARD2();                                      /* extern */
s32 _ExitCard();                                      /* extern */

void StopCARD(void) {
    StopCARD2();
    _ExitCard();
}

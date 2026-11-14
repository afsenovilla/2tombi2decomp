// CC gcc-2.8.1-psx
// FLAGS -O2 -G0
// ASPSX 2.79
#include "common.h"
s32 ResetCallback();                                  /* extern */
s32 func_8001F3AC(s32);                               /* extern */

void DecDCTReset(s32 arg0) {
    if (arg0 == 0) {
        ResetCallback();
    }
    func_8001F3AC(arg0);
}

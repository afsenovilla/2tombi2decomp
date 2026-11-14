// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// ASPSX 2.79
#include "common.h"
s32 DisablePAD();                                     /* extern */
s32 StopPAD2();                                       /* extern */
s32 func_80017BC8();                                  /* extern */
extern s32 D_80025664;

void StopPAD(void) {
    DisablePAD();
    StopPAD2();
    func_80017BC8();
    D_80025664 = 0;
}

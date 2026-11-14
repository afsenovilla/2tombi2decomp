// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// ASPSX 2.79
#include "common.h"
s32 DisablePAD();                                     /* extern */
s32 StopPAD2();                                       /* extern */
s32 func_8009BDFC();                                  /* extern */
extern s32 D_800ACF44;

void StopPAD(void) {
    DisablePAD();
    StopPAD2();
    func_8009BDFC();
    D_800ACF44 = 0;
}

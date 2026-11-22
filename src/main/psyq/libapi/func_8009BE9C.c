// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// ASPSX 2.79
// Source: psy-q-decomp (github.com/sozud/psy-q-decomp, MIT) src/api/pad.c, function _IsVSync.
#include "common.h"
extern volatile s32* D_800ACF4C;

int func_8009BE9C(void) {
    if ((D_800ACF4C[1] & 1) == 0 || (D_800ACF4C[0] & 1) == 0) {
        return 0;
    }
    return 1;
}

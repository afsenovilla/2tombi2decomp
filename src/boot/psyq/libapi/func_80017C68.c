// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// ASPSX 2.79
// Source: psy-q-decomp (github.com/sozud/psy-q-decomp, MIT) src/api/pad.c, function _IsVSync.
#include "common.h"
extern volatile s32* D_8002566C;

int func_80017C68(void) {
    if ((D_8002566C[1] & 1) == 0 || (D_8002566C[0] & 1) == 0) {
        return 0;
    }
    return 1;
}

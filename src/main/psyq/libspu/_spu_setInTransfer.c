// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// AS gnu
#include "common.h"
extern s32 D_800AC638;

void _spu_setInTransfer(s32 arg0) {
    if (arg0 == 1) {
        D_800AC638 = 0;
        return;
    }
    D_800AC638 = 1;
}

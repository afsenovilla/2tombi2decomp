// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// AS gnu
#include "common.h"
extern s32 D_800ACF44;

void SetInitPadFlag(s32 arg0) {
    D_800ACF44 = arg0;
}

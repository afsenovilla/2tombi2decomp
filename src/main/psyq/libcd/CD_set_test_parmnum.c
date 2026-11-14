// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// AS gnu
#include "common.h"
extern s32 D_800AC264;

void CD_set_test_parmnum(s32 arg0) {
    D_800AC264 = arg0;
}

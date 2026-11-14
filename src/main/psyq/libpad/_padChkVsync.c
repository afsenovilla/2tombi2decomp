// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// AS gnu
#include "common.h"
extern s32 D_800ABEA0;

s32 _padChkVsync(void) {
    s32 temp_v0;

    temp_v0 = D_800ABEA0;
    D_800ABEA0 = 0;
    return temp_v0;
}

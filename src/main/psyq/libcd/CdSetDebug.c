// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// AS gnu
#include "common.h"
extern s32 D_800ABFC4;

s32 CdSetDebug(s32 arg0) {
    s32 temp_v0;

    temp_v0 = D_800ABFC4;
    D_800ABFC4 = arg0;
    return temp_v0;
}

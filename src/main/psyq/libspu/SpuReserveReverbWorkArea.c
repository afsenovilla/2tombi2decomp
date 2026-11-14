// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// AS gnu
#include "common.h"
s32 _SpuIsInAllocateArea_(s32);                     /* extern */
extern s32 D_800AC59C;
extern s32 D_800AC5A0;

s32 SpuReserveReverbWorkArea(s32 arg0) {
    if ((arg0 != 0) && (_SpuIsInAllocateArea_(D_800AC5A0) == 0)) {
        D_800AC59C = 1;
        return 1;
    }
    D_800AC59C = 0;
    return 0;
}

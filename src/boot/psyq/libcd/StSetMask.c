// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// AS gnu
#include "common.h"
extern s32 D_80039E74;
extern s32 D_80039E94;
extern s32 D_80039E98;

void StSetMask(s32 arg0, s32 arg1, s32 arg2) {
    D_80039E98 = arg0;
    D_80039E74 = arg1;
    D_80039E94 = arg2;
}

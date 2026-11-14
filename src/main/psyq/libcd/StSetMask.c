// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// AS gnu
#include "common.h"
extern s32 D_801026FC;
extern s32 D_8010271C;
extern s32 D_80102720;

void StSetMask(s32 arg0, s32 arg1, s32 arg2) {
    D_80102720 = arg0;
    D_801026FC = arg1;
    D_8010271C = arg2;
}

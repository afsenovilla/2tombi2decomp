// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// AS gnu
#include "common.h"
extern s32 D_801026E4;
extern s32 D_801026E0;

void setRC2wait(s32 a) {
    D_801026E4 = a;
    D_801026E0 = *(volatile u16 *)0x1F801120;
}

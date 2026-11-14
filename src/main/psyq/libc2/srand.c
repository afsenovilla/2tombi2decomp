// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// AS gnu
#include "common.h"
extern s32 D_80105EE8;

void srand(s32 arg0) {
    D_80105EE8 = arg0;
}

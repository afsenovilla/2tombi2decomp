// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// AS gnu
#include "common.h"
extern s8 D_80105D28;

void SsSetAutoKeyOffMode(s8 arg0) {
    D_80105D28 = arg0;
}

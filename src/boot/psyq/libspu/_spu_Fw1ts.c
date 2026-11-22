// CC gcc-2.8.1-psx
// FLAGS -O2 -G0 -mno-split-addresses -fno-delayed-branch
// AS gnu
#include "common.h"

void _spu_Fw1ts(void) {
    volatile s32 i;
    volatile s32 x;
    x = 13;
    for (i = 0; i < 60; i++) x *= 13;
}

// CC gcc-2.8.1-psx
// FLAGS -O2 -G0 -mno-split-addresses -fno-delayed-branch
// AS gnu
#include "common.h"
typedef struct { u32 mask; s32 mode; s16 dl, dr; s32 delay; s32 feedback; } RevAttr;
extern RevAttr D_80105BF8;
void SpuSetReverbModeParam(RevAttr *);

void SsUtSetReverbDelay(s16 delay) {
    D_80105BF8.mask = 8;
    D_80105BF8.delay = delay;
    SpuSetReverbModeParam(&D_80105BF8);
}

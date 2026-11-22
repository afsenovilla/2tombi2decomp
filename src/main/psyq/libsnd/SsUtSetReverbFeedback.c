// CC gcc-2.8.1-nocse
// FLAGS -O2 -G0 -mno-split-addresses
// AS gnu
// EPILOGUE sony
#include "common.h"
typedef struct { u32 mask; s32 mode; s16 dl, dr; s32 delay; s32 feedback; } RevAttr;
extern RevAttr D_80105BF8;
void SpuSetReverbModeParam(RevAttr *);
void SsUtSetReverbFeedback(feedback) s16 feedback; {
    D_80105BF8.mask = 0x10;
    D_80105BF8.feedback = feedback;
    SpuSetReverbModeParam(&D_80105BF8);
}

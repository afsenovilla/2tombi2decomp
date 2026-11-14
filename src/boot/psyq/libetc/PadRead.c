// CC gcc-2.8.1-psx
// FLAGS -O2 -G0
// ASPSX 2.79
#include "common.h"
s32 PAD_dr();                                         /* extern */
extern s32 D_80039E18;

s32 PadRead(void) {
    PAD_dr();
    return ~D_80039E18;
}

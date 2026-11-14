// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// AS gnu
#include "common.h"
s32 StClearRing();                                    /* extern */
extern s32 D_80039EA0;
extern s32 D_80039EA4;

void StSetRing(s32 arg0, s32 arg1) {
    D_80039EA0 = arg0;
    D_80039EA4 = arg1;
    StClearRing();
}

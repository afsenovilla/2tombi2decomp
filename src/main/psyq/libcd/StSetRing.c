// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// AS gnu
#include "common.h"
s32 StClearRing();                                    /* extern */
extern s32 D_80102728;
extern s32 D_8010272C;

void StSetRing(s32 arg0, s32 arg1) {
    D_80102728 = arg0;
    D_8010272C = arg1;
    StClearRing();
}

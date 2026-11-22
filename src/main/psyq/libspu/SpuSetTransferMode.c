// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// AS gnu
#include "common.h"
extern s32 D_800AC594, D_800AC620;

s32 SpuSetTransferMode(s32 mode) {
    s32 m;
    switch (mode) {
    case 0: m = 0; break;
    case 1: m = 1; break;
    default: m = 0; break;
    }
    D_800AC594 = mode;
    D_800AC620 = m;
    return m;
}

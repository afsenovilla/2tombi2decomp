// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// AS gnu
#include "common.h"
extern volatile u32 *D_800A5AA4;
extern volatile u32 *D_800A5AA8;

s32 func_80083618(s32 mode) {
    *D_800A5AA8 = 0x10000007;
    if ((*D_800A5AA4 & 0xFFFFFF) != 2) {
        *D_800A5AA4 = 0xE1001000 | (*D_800A5AA8 & 0x3FFF);
        *D_800A5AA4;
        return 0;
    }
    if (!(mode & 8)) return 1;
    *D_800A5AA8 = 0x09000001;
    return 2;
}

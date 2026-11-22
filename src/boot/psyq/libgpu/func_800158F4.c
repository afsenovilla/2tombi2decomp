// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// AS gnu
#include "common.h"
extern volatile u32 *D_80025618;
extern volatile u32 *D_8002561C;

s32 func_800158F4(s32 mode) {
    *D_8002561C = 0x10000007;
    if ((*D_80025618 & 0xFFFFFF) != 2) {
        *D_80025618 = 0xE1001000 | (*D_8002561C & 0x3FFF);
        *D_80025618;
        return 0;
    }
    if (!(mode & 8)) return 1;
    *D_8002561C = 0x09000001;
    return 2;
}

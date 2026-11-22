// CC gcc-2.8.1-psx
// FLAGS -O2 -G0 -mno-split-addresses -fno-delayed-branch
// AS gnu
#include "common.h"
extern volatile s32 *D_8002561C;
extern volatile s32 *D_80025618;

s32 func_80014F04(s32 *p, s32 n) {
    s32 i;
    *D_8002561C = 0x04000000;
    for (i = n - 1; i != -1; i--) *D_80025618 = *p++;
    return 0;
}

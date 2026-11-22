// CC gcc-2.8.1-psx
// FLAGS -O2 -G0 -mno-split-addresses -fno-delayed-branch
// AS gnu
#include "common.h"
extern volatile s32 *D_800A5AA8;
extern volatile s32 *D_800A5AA4;

s32 func_80082C28(s32 *p, s32 n) {
    s32 i;
    *D_800A5AA8 = 0x04000000;
    for (i = n - 1; i != -1; i--) *D_800A5AA4 = *p++;
    return 0;
}

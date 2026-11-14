// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// AS gnu
#include "common.h"
extern s32 (*D_800AC42C)();
extern s32 D_800AC438;

void func_80090A0C(void) {
    if (D_800AC438 == 0) {
        D_800AC438 = 1;
        return;
    }
    D_800AC438 = 0;
    D_800AC42C();
}

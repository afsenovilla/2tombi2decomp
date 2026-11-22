// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// AS gnu
#include "common.h"
extern s32 D_800ABDE0;
extern void (*D_800ABDC0[8])(void);

void func_80086288(void) {
    s32 i;
    D_800ABDE0++;
    for (i = 0; i < 8; i++) {
        if (D_800ABDC0[i]) D_800ABDC0[i]();
    }
}

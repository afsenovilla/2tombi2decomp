// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// AS gnu
#include "common.h"
extern s32 D_800267B4;
extern void (*D_80026794[8])(void);

void func_800187D4(void) {
    s32 i;
    D_800267B4++;
    for (i = 0; i < 8; i++) {
        if (D_80026794[i]) D_80026794[i]();
    }
}

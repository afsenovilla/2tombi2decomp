// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// AS gnu
#include "common.h"
extern s16 D_80105C90;

void _SsVmDamperOn(void) {
    D_80105C90 = 2;
}

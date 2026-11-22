// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// ASPSX 2.79
#include "common.h"
s32 CD_init(void);
s32 CD_initvol(void);

s32 func_80018DBC(void) {
    if (CD_init()) return 0;
    return CD_initvol() == 0;
}

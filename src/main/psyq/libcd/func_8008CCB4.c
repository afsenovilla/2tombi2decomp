// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// ASPSX 2.79
#include "common.h"
s32 StCdInterrupt();                                  /* extern */

void func_8008CCB4(void) {
    StCdInterrupt();
}

// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// AS gnu
#include "common.h"
extern volatile u32 *D_800AD098;
extern char D_8001CA8C[];

s32 func_8009CAEC(void) {
    volatile s32 cnt = 0x100000;
    while (*D_800AD098 & 0x20000000) {
        if (--cnt == -1) {
            func_8009CC2C(D_8001CA8C);
            return -1;
        }
    }
    return 0;
}

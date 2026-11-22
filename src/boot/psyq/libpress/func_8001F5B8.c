// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// AS gnu
#include "common.h"
extern volatile u32 *D_8002741C;
extern char D_80010D20[];

s32 func_8001F5B8(void) {
    volatile s32 cnt = 0x100000;
    while (*D_8002741C & 0x20000000) {
        if (--cnt == -1) {
            func_8001F6F8(D_80010D20);
            return -1;
        }
    }
    return 0;
}

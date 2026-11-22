// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// AS gnu
#include "common.h"
extern volatile u32 *D_800273FC;
extern char D_80010D30[];

s32 func_8001F64C(void) {
    volatile s32 cnt = 0x100000;
    while (*D_800273FC & 0x01000000) {
        if (--cnt == -1) {
            func_8001F6F8(D_80010D30);
            return -1;
        }
    }
    return 0;
}

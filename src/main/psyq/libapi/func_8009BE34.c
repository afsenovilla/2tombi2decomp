// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// AS gnu
#include "common.h"
typedef struct { u8 pad[0xA]; volatile u16 unkA; } Regs;
extern Regs *D_800ACF48;

s32 func_8009BE34(void) {
    volatile s32 i;
    s32 pad[2];
    D_800ACF48->unkA = 0;
    i = 10;
    while (--i != -1) {
    }
    return 0;
}

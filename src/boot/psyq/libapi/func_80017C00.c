// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// AS gnu
#include "common.h"
typedef struct { u8 pad[0xA]; volatile u16 unkA; } Regs;
extern Regs *D_80025668;

s32 func_80017C00(void) {
    volatile s32 i;
    s32 pad[2];
    D_80025668->unkA = 0;
    i = 10;
    while (--i != -1) {
    }
    return 0;
}

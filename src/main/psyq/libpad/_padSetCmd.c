// CC gcc-2.8.1-psx
// FLAGS -O2 -G0
// ASPSX 2.79
#define _padSetCmd _padSetCmd_hdr
#include "psyq_all.h"
#undef _padSetCmd
void _padSetCmd(void *arg0, s8 arg1, s32 arg2, s8 arg3) {
    M2C_FIELD(arg0, s8 *, 0x37) = arg1;
    M2C_FIELD(arg0, s32 *, 0x2C) = arg2;
    M2C_FIELD(arg0, s8 *, 0x36) = arg3;
}

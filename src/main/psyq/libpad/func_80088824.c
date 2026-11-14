// CC gcc-2.8.1-psx
// FLAGS -O2 -G0
// ASPSX 2.79
#define func_80088824 func_80088824_hdr
#include "psyq_all.h"
#undef func_80088824
void func_80088824(void *arg0) {
    M2C_FIELD(arg0, s8 *, 0x37) = 0x4D;
    M2C_FIELD(arg0, s8 *, 0x36) = 6;
    M2C_FIELD(arg0, s32 *, 0x2C) = (s32) M2C_FIELD(arg0, s32 *, 0x20);
}

// CC gcc-2.8.1-psx
// FLAGS -O2 -G0
// ASPSX 2.79
#define func_80088AC8 func_80088AC8_hdr
#include "psyq_all.h"
#undef func_80088AC8
void func_80088AC8(void *arg0, s8 arg1) {
    M2C_FIELD(arg0, s8 *, 0x37) = 0x47;
    M2C_FIELD(arg0, void **, 0x2C) = (void *) (arg0 + 0x24);
    M2C_FIELD(arg0, s8 *, 0x24) = arg1;
    M2C_FIELD(arg0, s8 *, 0x36) = 1;
}

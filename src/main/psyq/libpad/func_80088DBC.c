// CC gcc-2.8.1-psx
// FLAGS -O2 -G0
// ASPSX 2.79
#define func_80088DBC func_80088DBC_hdr
#include "psyq_all.h"
#undef func_80088DBC
void func_80088DBC(void *arg0) {
    u8 temp_v0;

    temp_v0 = M2C_FIELD(arg0, u8 *, 0x37);
    M2C_FIELD(arg0, u8 *, 0x37) = 0U;
    M2C_FIELD(arg0, u8 *, 0x38) = temp_v0;
}

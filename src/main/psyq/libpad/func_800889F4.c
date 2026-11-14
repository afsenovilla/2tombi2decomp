// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// ASPSX 2.79
#define func_800889F4 func_800889F4_hdr
#include "psyq_all.h"
#undef func_800889F4
extern M2C_UNK (*D_800ABE3C)();

s32 func_800889F4(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x53) != 0) {
        if (M2C_FIELD(arg0, u8 *, 0x46) == 2) {
            return 1;
        }
        M2C_FIELD(arg0, u8 *, 0x46) = 0xFEU;
        goto block_5;
    }
    D_800ABE3C();
block_5:
    return 0;
}

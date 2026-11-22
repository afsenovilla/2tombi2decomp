// CC gcc-2.8.1-psx
// FLAGS -O2 -G0
// ASPSX 2.79
#define DrawSync DrawSync_hdr
#include "psyq_all.h"
#undef DrawSync
extern M2C_UNK D_80010220;
extern void *D_8002550C;
extern M2C_UNK (*D_80025510)(M2C_UNK *, s32);
extern u8 D_80025516;

s32 DrawSync(s32 mode) {
    if ((u8) D_80025516 >= 2U) {
        D_80025510(&D_80010220, mode);
    }
    return M2C_FIELD(D_8002550C, s32 (**)(s32), 0x3C)(mode);
}

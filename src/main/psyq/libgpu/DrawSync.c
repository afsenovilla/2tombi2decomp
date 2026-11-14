// CC gcc-2.8.1-psx
// FLAGS -O2 -G0
// ASPSX 2.79
#define DrawSync DrawSync_hdr
#include "psyq_all.h"
#undef DrawSync
extern M2C_UNK D_8001BEDC;
extern void *D_800A5998;
extern M2C_UNK (*D_800A599C)(M2C_UNK *, s32);
extern u8 D_800A59A2;

s32 DrawSync(s32 mode) {
    if ((u8) D_800A59A2 >= 2U) {
        D_800A599C(&D_8001BEDC, mode);
    }
    return M2C_FIELD(D_800A5998, s32 (**)(s32), 0x3C)(mode);
}

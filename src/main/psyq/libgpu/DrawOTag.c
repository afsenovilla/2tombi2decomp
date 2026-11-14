// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// AS gnu
#define DrawOTag DrawOTag_hdr
#include "psyq_all.h"
#undef DrawOTag
extern M2C_UNK D_8001BF80;
extern void *D_800A5998;
extern M2C_UNK (*D_800A599C)(M2C_UNK *, u32 *);
extern u8 D_800A59A2;

void DrawOTag(u32 *p) {
    if ((u8) D_800A59A2 >= 2U) {
        D_800A599C(&D_8001BF80, p);
    }
    M2C_FIELD(D_800A5998, M2C_UNK (**)(s32, u32 *, M2C_UNK, M2C_UNK), 8)(M2C_FIELD(D_800A5998, s32 *, 0x18), p, 0, 0);
}

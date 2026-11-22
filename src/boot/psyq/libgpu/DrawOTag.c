// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// AS gnu
#define DrawOTag DrawOTag_hdr
#include "psyq_all.h"
#undef DrawOTag
extern M2C_UNK D_800102C4;
extern void *D_8002550C;
extern M2C_UNK (*D_80025510)(M2C_UNK *, u32 *);
extern u8 D_80025516;

void DrawOTag(u32 *p) {
    if ((u8) D_80025516 >= 2U) {
        D_80025510(&D_800102C4, p);
    }
    M2C_FIELD(D_8002550C, M2C_UNK (**)(s32, u32 *, M2C_UNK, M2C_UNK), 8)(M2C_FIELD(D_8002550C, s32 *, 0x18), p, 0, 0);
}

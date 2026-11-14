// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// AS gnu
#define LoadImage LoadImage_hdr
#include "psyq_all.h"
#undef LoadImage
M2C_UNK checkRECT(M2C_UNK *, RECT *);               /* extern */
extern M2C_UNK D_8001BF2C;
extern void *D_800A5998;

s32 LoadImage(RECT *rect, u32 *p) {
    checkRECT(&D_8001BF2C, rect);
    return M2C_FIELD(D_800A5998, s32 (**)(s32, RECT *, M2C_UNK, u32 *), 8)(M2C_FIELD(D_800A5998, s32 *, 0x20), rect, 8, p);
}

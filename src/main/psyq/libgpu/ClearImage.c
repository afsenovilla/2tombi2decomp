// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// AS gnu
#define ClearImage ClearImage_hdr
#include "psyq_all.h"
#undef ClearImage
M2C_UNK checkRECT(M2C_UNK *, RECT *);               /* extern */
extern M2C_UNK D_8001BF14;
extern void *D_800A5998;

s32 ClearImage(RECT *rect, u8 r, u8 g, u8 b) {
    checkRECT(&D_8001BF14, rect);
    return M2C_FIELD(D_800A5998, s32 (**)(s32, RECT *, M2C_UNK, s32), 8)(M2C_FIELD(D_800A5998, s32 *, 0xC), rect, 8, ((b & 0xFF) << 0x10) | ((g & 0xFF) << 8) | (r & 0xFF));
}

// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// AS gnu
#define LoadImage LoadImage_hdr
#include "psyq_all.h"
#undef LoadImage
M2C_UNK func_800132B0(M2C_UNK *, RECT *);               /* extern */
extern M2C_UNK D_80010270;
extern void *D_8002550C;

s32 LoadImage(RECT *rect, u32 *p) {
    func_800132B0(&D_80010270, rect);
    return M2C_FIELD(D_8002550C, s32 (**)(s32, RECT *, M2C_UNK, u32 *), 8)(M2C_FIELD(D_8002550C, s32 *, 0x20), rect, 8, p);
}

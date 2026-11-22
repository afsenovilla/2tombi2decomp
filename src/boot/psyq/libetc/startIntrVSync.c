// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// ASPSX 2.79
#define startIntrVSync startIntrVSync_hdr
#include "psyq_all.h"
#undef startIntrVSync
M2C_UNK InterruptCallback(M2C_UNK, M2C_UNK *);      /* extern */
M2C_UNK func_8001886C(M2C_UNK *, M2C_UNK);          /* extern */
extern M2C_UNK D_80026794;
extern s32 D_800267B4;
extern s32 *D_800267B8;
extern M2C_UNK func_800187D4;
extern M2C_UNK func_80018840;

M2C_UNK *startIntrVSync(void) {
    *D_800267B8 = 0x100;
    D_800267B4 = 0;
    func_8001886C(&D_80026794, 8);
    InterruptCallback(0, &func_800187D4);
    return &func_80018840;
}

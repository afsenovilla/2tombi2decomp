// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// ASPSX 2.79
#define startIntrVSync startIntrVSync_hdr
#include "psyq_all.h"
#undef startIntrVSync
M2C_UNK InterruptCallback(M2C_UNK, M2C_UNK *);      /* extern */
M2C_UNK func_80086320(M2C_UNK *, M2C_UNK);          /* extern */
extern M2C_UNK D_800ABDC0;
extern s32 D_800ABDE0;
extern s32 *D_800ABDE4;
extern M2C_UNK func_80086288;
extern M2C_UNK func_800862F4;

M2C_UNK *startIntrVSync(void) {
    *D_800ABDE4 = 0x100;
    D_800ABDE0 = 0;
    func_80086320(&D_800ABDC0, 8);
    InterruptCallback(0, &func_80086288);
    return &func_800862F4;
}

// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// AS gnu
#define PadInit PadInit_hdr
#include "psyq_all.h"
#undef PadInit
M2C_UNK ChangeClearPAD(M2C_UNK);                    /* extern */
M2C_UNK PAD_init(M2C_UNK, s32 *);                   /* extern */
extern s32 D_80039E18;
extern s32 D_80039E28;

void PadInit(s32 mode) {
    D_80039E28 = mode;
    D_80039E18 = -1;
    ResetCallback();
    PAD_init(0x20000001, &D_80039E18);
    ChangeClearPAD(0);
}

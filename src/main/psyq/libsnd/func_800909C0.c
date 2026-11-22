// CC gcc-2.8.1-psx
// FLAGS -O2 -G0 -mno-split-addresses -fno-delayed-branch
// AS gnu
#define func_800909C0 func_800909C0_hdr
#include "psyq_all.h"
#undef func_800909C0
extern M2C_UNK D_800AC430;

s32 func_800909C0(void) {
    if (M2C_FIELD(&D_800AC430, M2C_UNK (**)(), 0) != NULL) {
        M2C_FIELD(&D_800AC430, M2C_UNK (**)(), 0)();
    }
    return M2C_FIELD(&D_800AC430, s32 (**)(), -4)();
}

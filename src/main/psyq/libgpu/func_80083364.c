// CC gcc-2.8.1-psx
// FLAGS -O2 -G0 -mno-split-addresses
// ASPSX 2.79
#include "common.h"
extern volatile s32 *D_800A5AA8;
extern volatile s32 *D_800A5AB4;
extern volatile s32 D_800A5AC8;
extern volatile s32 D_800A5ACC;
void func_800834A0(void);
s32 func_800834D4(void);
s32 func_80082FB4(void);

s32 func_80083364(s32 mode) {
    s32 n;
    if (!mode) {
        func_800834A0();
        while (D_800A5AC8 != D_800A5ACC) {
            func_80082FB4();
            if (func_800834D4()) return -1;
        }
        while ((*D_800A5AB4 & 0x01000000) || !(*D_800A5AA8 & 0x04000000)) {
            if (func_800834D4()) return -1;
        }
        return 0;
    }
    n = (D_800A5AC8 - D_800A5ACC) & 0x3F;
    if (n) func_80082FB4();
    if ((*D_800A5AB4 & 0x01000000) || !(*D_800A5AA8 & 0x04000000)) {
        if (n) return n;
        return 1;
    }
    return n;
}

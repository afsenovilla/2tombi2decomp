// CC gcc-2.8.1-psx
// FLAGS -O2 -G0 -mno-split-addresses
// ASPSX 2.79
#include "common.h"
extern volatile s32 *D_8002561C;
extern volatile s32 *D_80025628;
extern volatile s32 D_8002563C;
extern volatile s32 D_80025640;
void func_8001577C(void);
s32 func_800157B0(void);
s32 func_80015290(void);

s32 func_80015640(s32 mode) {
    s32 n;
    if (!mode) {
        func_8001577C();
        while (D_8002563C != D_80025640) {
            func_80015290();
            if (func_800157B0()) return -1;
        }
        while ((*D_80025628 & 0x01000000) || !(*D_8002561C & 0x04000000)) {
            if (func_800157B0()) return -1;
        }
        return 0;
    }
    n = (D_8002563C - D_80025640) & 0x3F;
    if (n) func_80015290();
    if ((*D_80025628 & 0x01000000) || !(*D_8002561C & 0x04000000)) {
        if (n) return n;
        return 1;
    }
    return n;
}

// CC gcc-2.8.1-psx
// FLAGS -O2 -G0 -mno-split-addresses
// AS gnu
// EPILOGUE sony
#include "common.h"
extern volatile s32 *D_800A5AA8;
extern volatile s32 *D_800A5AAC;
extern volatile s32 *D_800A5AB4;
extern volatile s32 *D_800A5AC4;
extern volatile s32 D_800A5AC8;
extern volatile s32 D_800A5ACC;
extern s32 D_800A5AD8;
extern s32 D_800A5ADC;
extern s32 D_800A5AE0;
extern char D_8001BFE0[];
s32 VSync(s32);
s32 SetIntrMask(s32);

s32 func_800834D4(void) {
    s32 m;
    if (D_800A5ADC < VSync(-1) || D_800A5AE0++ > 0xF0000) {
        *D_800A5AA8;
        printf(D_8001BFE0, (D_800A5AC8 - D_800A5ACC) & 0x3F, *D_800A5AA8, *D_800A5AB4, *D_800A5AAC);
        m = SetIntrMask(0);
        D_800A5ACC = 0;
        D_800A5AD8 = m;
        D_800A5AC8 = D_800A5ACC;
        *D_800A5AB4 = 0x401;
        *D_800A5AC4 |= 0x800;
        *D_800A5AA8 = 0x02000000;
        *D_800A5AA8 = 0x01000000;
        SetIntrMask(D_800A5AD8);
        return -1;
    }
    return 0;
}

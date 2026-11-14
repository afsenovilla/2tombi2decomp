// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// ASPSX 2.79
#define func_800834A0 func_800834A0_hdr
#include "psyq_all.h"
#undef func_800834A0
extern s32 D_800A5ADC;
extern s32 D_800A5AE0;

void func_800834A0(void) {
    D_800A5ADC = VSync(-1) + 0xF0;
    D_800A5AE0 = 0;
}

// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// ASPSX 2.79
#define func_8001577C func_8001577C_hdr
#include "psyq_all.h"
#undef func_8001577C
extern s32 D_80025650;
extern s32 D_80025654;

void func_8001577C(void) {
    D_80025650 = VSync(-1) + 0xF0;
    D_80025654 = 0;
}

// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// ASPSX 2.79
#include "common.h"
extern s32 *D_80026D9C;

void func_8001DCB4(void) {
    *D_80026D9C = (*D_80026D9C & 0xF0FFFFFF) | 0x20000000;
}

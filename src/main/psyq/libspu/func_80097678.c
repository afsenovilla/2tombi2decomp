// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// ASPSX 2.79
#include "common.h"
extern s32 *D_800AC618;

void func_80097678(void) {
    *D_800AC618 = (*D_800AC618 & 0xF0FFFFFF) | 0x20000000;
}

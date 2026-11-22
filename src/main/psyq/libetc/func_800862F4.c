// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// ASPSX 2.79
#include "common.h"
extern s32 D_800ABDC0[];

void func_800862F4(s32 i, s32 v) { if (v != D_800ABDC0[i]) D_800ABDC0[i] = v; }

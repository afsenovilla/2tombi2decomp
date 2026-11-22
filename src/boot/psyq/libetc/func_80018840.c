// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// ASPSX 2.79
#include "common.h"
extern s32 D_80026794[];

void func_80018840(s32 i, s32 v) { if (v != D_80026794[i]) D_80026794[i] = v; }

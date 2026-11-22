// CC gcc-2.8.1-psx
// FLAGS -O2 -G0
// ASPSX 2.79
#include "common.h"

void func_800861BC(s32 *p, s32 n) { s32 i; for (i = n - 1; i != -1; i--) *p++ = 0; }

INCLUDE_ASM("asm/main/nonmatchings/psyq/libetc/func_800861BC", func_800861E0);

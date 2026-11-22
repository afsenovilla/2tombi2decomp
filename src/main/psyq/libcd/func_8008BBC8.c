// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// ASPSX 2.79
#include "common.h"
s32 strncmp(char *, char *, s32);

s32 func_8008BBC8(char *a, char *b) { return strncmp(a, b, 12) == 0; }

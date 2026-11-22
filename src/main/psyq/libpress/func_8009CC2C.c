// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// ASPSX 2.79
#include "common.h"
s32 printf(const char *, ...);
extern char D_8001CAAC[];
extern volatile u32 *D_800AD098;
extern volatile u32 *D_800AD06C;
extern volatile u32 *D_800AD078;

s32 func_8009CC2C(char *s) {
    printf(D_8001CAAC, s);
    *D_800AD098 = 0x80000000;
    *D_800AD06C = 0;
    *D_800AD078 = 0;
    *D_800AD078;
    *D_800AD098 = 0x60000000;
    return 0;
}

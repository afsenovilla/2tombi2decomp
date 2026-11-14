// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// ASPSX 2.79
#define SKIP_ASM

#include "common.h"

extern s16 rsin_tbl[];

int rsin(int a) {
    if (a < 0) {
        return -sin_1(-a & 0xFFF);
    } else {
        return sin_1(a & 0xFFF);
    }
}

int sin_1(int a);

// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// ASPSX 2.79
// Source: psyz (github.com/Xeeynamo/psyz, MIT) decomp/src/libgte/geo_01.c, function rcos.
#include "common.h"
extern short RSIN_TABLE[];

int rcos(int a) {
    if (a < 0) {
        a = -a;
    }
    a &= 0xFFF;
    if (a <= 0x800) {
        if (a <= 0x400) {
            return RSIN_TABLE[0x400 - a];
        } else {
            return -RSIN_TABLE[a - 0x400];
        }
    } else {
        if (a <= 0xC00) {
            return -RSIN_TABLE[0xC00 - a];
        } else {
            return RSIN_TABLE[a - 0xC00];
        }
    }
}

INCLUDE_ASM("asm/main/nonmatchings/psyq/libgte/rcos", func_80083FF0);

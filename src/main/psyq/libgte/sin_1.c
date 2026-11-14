// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// ASPSX 2.79
// Source: psx_tomba src/psyq/libgte/geo_00.c (MIT), cut to this function by tools/ptsrc.py.
#define SKIP_ASM
#include "pt/common.h"
extern s16 RSIN_TABLE[];
s32 rsin(s32 arg0);
s32 sin_1(s32 arg0) {
    if (arg0 < 0x801) {
        if (arg0 < 0x401) {
            return RSIN_TABLE[arg0];
        } else {
            return RSIN_TABLE[0x800 - arg0];
        }
    } else {
        if (arg0 < 0xC01) {
            return -1 * RSIN_TABLE[arg0 - 0x800];
        } else {
            return -1 * RSIN_TABLE[0x1000 - arg0];
        }
    }
}

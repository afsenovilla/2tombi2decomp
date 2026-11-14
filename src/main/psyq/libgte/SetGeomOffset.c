// CC gcc-2.8.1-psx
// FLAGS -O2 -G0
// ASPSX 2.79
// Source: psx_tomba src/psyq/libgte/reg12.c (MIT), cut to this function by tools/ptsrc.py.
#define SKIP_ASM
#include "pt/common.h"
#include "psyq/libgte.h"
#include "pt/libgte/gte_local.h"
void SetGeomOffset(long ofx, long ofy) {
    ofx <<= 16;
    ofy <<= 16;
    gte_ldofxy(ofx, ofy);
}
__asm__("nop");
__asm__("nop");

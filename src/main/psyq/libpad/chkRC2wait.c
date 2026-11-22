// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// ASPSX 2.79
// Source: psx_tomba src/psyq/libpad/waitrc2.c (MIT), cut to this function by tools/ptsrc.py.
#define D_8009B6A4 D_801026E0
#define D_8009FD80 D_801026E4
#define SKIP_ASM
#include "pt/common.h"
#include "pt/libpad/padlocal.h"
void setRC2wait(int limit);
int chkRC2wait(void) {
    register u32 current asm("$4");
    register u32 raw asm("$3");
    u32 base;
    u32 limit;

    raw = *(volatile u16 *)0x1F801120;
    base = D_8009B6A4;
    asm volatile("" : "=r"(raw) : "0"(raw));
    current = raw & 0xFFFF;
    if (current < base) {
        if (*(volatile u16 *)0x1F801128 != 0) {
            current += *(volatile u16 *)0x1F801128;
        } else {
            current += 0x10000;
        }
    }

    if ((*(volatile u16 *)0x1F801124 & 0x200) != 0) {
        limit = D_8009FD80;
        return !((current - D_8009B6A4) < limit);
    } else {
        limit = D_8009FD80;
        return !(((current - D_8009B6A4) >> 3) < limit);
    }
}

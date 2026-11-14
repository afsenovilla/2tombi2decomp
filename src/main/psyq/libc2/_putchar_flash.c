// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// ASPSX 2.79
#define _putchar_flash _putchar_flash_hdr
#include "psyq_all.h"
#undef _putchar_flash
M2C_UNK write(M2C_UNK, M2C_UNK *, s32);             /* extern */
extern s32 D_800ACF08;
extern M2C_UNK D_80105EF8;

void _putchar_flash(void) {
    if (D_800ACF08 > 0) {
        write(1, &D_80105EF8, D_800ACF08);
        D_800ACF08 = 0;
    }
}

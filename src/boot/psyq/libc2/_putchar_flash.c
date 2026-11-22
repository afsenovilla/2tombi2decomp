// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// ASPSX 2.79
#define _putchar_flash _putchar_flash_hdr
#include "psyq_all.h"
#undef _putchar_flash
M2C_UNK write(M2C_UNK, M2C_UNK *, s32);             /* extern */
extern s32 D_800272BC;
extern M2C_UNK D_8003C328;

void _putchar_flash(void) {
    if (D_800272BC > 0) {
        write(1, &D_8003C328, D_800272BC);
        D_800272BC = 0;
    }
}

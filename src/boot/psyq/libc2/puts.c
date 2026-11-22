// CC gcc-2.8.1-psx
// FLAGS -O2 -G0 -mno-split-addresses
// AS gnu
// EPILOGUE sony
#include "common.h"
extern char D_80010CF4[];
void _putchar(s8);
void _putchar_flash(void);

void puts(s8 *s) {
    s8 c;
    if (s == NULL) s = (s8 *)D_80010CF4;
    while ((c = *s++) != 0) _putchar(c);
    _putchar_flash();
}

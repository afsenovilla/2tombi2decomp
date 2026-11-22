// CC gcc-2.8.1-psx
// FLAGS -O2 -G0 -mno-split-addresses
// AS gnu
// RETURN sony
#include "common.h"
#include "psyq/stdarg.h"

void func_800889A0(u8 *p) {
    switch (p[0x46]) {
    case 2:
        p[0x37] = 0x44;
        *(u8 **)(p + 0x2C) = p + 0x51;
        p[0x36] = 2;
        break;
    case 3:
        p[0x37] = 0x4D;
        *(u8 **)(p + 0x2C) = p + 0x5D;
        p[0x36] = 6;
        break;
    }
}

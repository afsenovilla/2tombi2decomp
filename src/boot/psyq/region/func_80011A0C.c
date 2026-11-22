// Unidentified licensed-region boot module [0x80011A0C, 0x80012D2C): BIOS region byte check and a message screen
// (Krom2RawAdd / libgpu), built with the library compiler; not a known Psy-Q library (no signature covers it).
// CC gcc-2.7.2-psx
// AS gnu
#include "common.h"

extern u8 D_BFC7FF52;
extern s32 D_80025454;
extern s32 D_800384A4;

void func_80011A0C(void)
{
    switch (D_BFC7FF52) {
    case 'A':
        D_80025454 = 1;
        D_800384A4 = 1;
        break;
    case 'E':
        D_80025454 = 0;
        D_800384A4 = 2;
        break;
    case 'I':
    default:
        D_80025454 = 1;
        D_800384A4 = 0;
        break;
    }
}

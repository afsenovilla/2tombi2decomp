// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// AS gnu
#include "common.h"
s32 printf(const char *, ...);
extern volatile u32 *D_800AD098;
extern volatile u32 *D_800AD06C;
extern volatile u32 *D_800AD078;
extern u32 D_800ACF54[];
extern u32 D_800ACFD8[];
extern char D_8001CA70[];

void func_8009C8E0(s32 mode) {
    switch (mode) {
    case 0:
        *D_800AD098 = 0x80000000;
        *D_800AD06C = 0;
        *D_800AD078 = 0;
        *D_800AD098 = 0x60000000;
        func_8009C9D0(D_800ACF54, 0x20);
        func_8009C9D0(D_800ACFD8, 0x20);
        break;
    case 1:
        *D_800AD098 = 0x80000000;
        *D_800AD06C = 0;
        *D_800AD078 = 0;
        *D_800AD078;
        *D_800AD098 = 0x60000000;
        break;
    default:
        printf(D_8001CA70, mode);
        break;
    }
}

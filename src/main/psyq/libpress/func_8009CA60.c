// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// AS gnu
#include "common.h"
s32 func_8009CB80();                                  /* extern */
extern s32 *D_800AD070;
extern s32 *D_800AD074;
extern s32 *D_800AD078;
extern s32 *D_800AD09C;

void func_8009CA60(s32 arg0, u32 arg1) {
    func_8009CB80();
    *D_800AD09C |= 0x88;
    *D_800AD078 = 0;
    *D_800AD070 = arg0;
    *D_800AD074 = ((arg1 >> 5) << 0x10) | 0x20;
    *D_800AD078 = 0x01000200;
}

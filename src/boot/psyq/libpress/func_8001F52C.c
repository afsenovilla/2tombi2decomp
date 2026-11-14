// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// AS gnu
#include "common.h"
s32 func_8001F64C();                                  /* extern */
extern s32 *D_800273F4;
extern s32 *D_800273F8;
extern s32 *D_800273FC;
extern s32 *D_80027420;

void func_8001F52C(s32 arg0, u32 arg1) {
    func_8001F64C();
    *D_80027420 |= 0x88;
    *D_800273FC = 0;
    *D_800273F4 = arg0;
    *D_800273F8 = ((arg1 >> 5) << 0x10) | 0x20;
    *D_800273FC = 0x01000200;
}

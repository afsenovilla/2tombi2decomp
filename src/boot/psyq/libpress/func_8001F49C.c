// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// AS gnu
#include "common.h"
extern volatile u32 *D_800273F0;
extern volatile u32 *D_80027420;
extern volatile u32 *D_800273E8;
extern volatile u32 *D_800273EC;
extern volatile u32 *D_80027418;

void func_8001F49C(u32 *addr, u32 size) {
    func_8001F5B8();
    *D_80027420 |= 0x88;
    *D_800273E8 = (u32)(addr + 1);
    *D_800273EC = ((size >> 5) << 16) | 0x20;
    *D_80027418 = *addr;
    *D_800273F0 = 0x01000201;
}

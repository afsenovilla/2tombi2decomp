// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// AS gnu
#include "common.h"
extern volatile u32 *D_800AD06C;
extern volatile u32 *D_800AD09C;
extern volatile u32 *D_800AD064;
extern volatile u32 *D_800AD068;
extern volatile u32 *D_800AD094;

void func_8009C9D0(u32 *addr, u32 size) {
    func_8009CAEC();
    *D_800AD09C |= 0x88;
    *D_800AD064 = (u32)(addr + 1);
    *D_800AD068 = ((size >> 5) << 16) | 0x20;
    *D_800AD094 = *addr;
    *D_800AD06C = 0x01000201;
}

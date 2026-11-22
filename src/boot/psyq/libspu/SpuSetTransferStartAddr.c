// CC gcc-2.7.2-psx
// FLAGS -O1 -G0
// AS gnu
// EPILOGUE sony
#include "common.h"
extern u16 D_80026DA0;
extern s32 D_80026DB0;
s32 _spu_FsetRXXa(s32, u32);

u32 SpuSetTransferStartAddr(u32 addr) {
    u32 lim = 0x7EFE8;
    if (addr - 0x1010 > lim) return 0;
    D_80026DA0 = _spu_FsetRXXa(-1, addr);
    return D_80026DA0 << D_80026DB0;
}

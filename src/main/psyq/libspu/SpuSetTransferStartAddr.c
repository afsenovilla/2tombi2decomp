// CC gcc-2.7.2-psx
// FLAGS -O1 -G0
// AS gnu
// EPILOGUE sony
#include "common.h"
extern u16 D_800AC61C;
extern s32 D_800AC62C;
s32 _spu_FsetRXXa(s32, u32);

u32 SpuSetTransferStartAddr(u32 addr) {
    u32 lim = 0x7EFE8;
    if (addr - 0x1010 > lim) return 0;
    D_800AC61C = _spu_FsetRXXa(-1, addr);
    return D_800AC61C << D_800AC62C;
}

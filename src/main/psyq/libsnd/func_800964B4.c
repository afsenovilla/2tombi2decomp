// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// AS gnu
#include "common.h"
s32 SpuMalloc(s32);
void _spu_setInTransfer(s32);
extern u8 D_80105D18[];
extern u16 D_80105D70;

s32 func_800964B4(s32 size, s32 unused, s16 vabid) {
    s32 a = SpuMalloc(size);
    if (a == -1) {
        D_80105D18[vabid] = 0;
        _spu_setInTransfer(0);
        D_80105D70--;
        return -1;
    }
    return a;
}

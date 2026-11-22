// CC gcc-2.8.1-psx
// FLAGS -O2 -G0 -mno-split-addresses -fno-delayed-branch
// AS gnu
#include "common.h"
extern u16 D_800AC61C;
extern s32 D_800AC62C;
void _spu_t();

s32 _spu_Fr(s32 addr, s32 size) {
    _spu_t(2, D_800AC61C << D_800AC62C);
    _spu_t(0);
    _spu_t(3, addr, size);
    return size;
}

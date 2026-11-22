// CC gcc-2.8.1-psx
// FLAGS -O2 -G0 -mno-split-addresses -fno-delayed-branch
// AS gnu
#include "common.h"
extern u16 D_80026DA0;
extern s32 D_80026DB0;
void _spu_t();

s32 _spu_Fr(s32 addr, s32 size) {
    _spu_t(2, D_80026DA0 << D_80026DB0);
    _spu_t(0);
    _spu_t(3, addr, size);
    return size;
}

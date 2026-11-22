// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// AS gnu
#include "common.h"
void SpuFree(u32);
s32 _spu_getInTransfer(void);
void _spu_setInTransfer(s32);
extern u8 D_80105D18[];
extern u16 D_80105D70;
extern u32 D_80105D78[];

void SsVabClose(s16 vabid) {
    if ((u16)vabid < 16) {
        s32 st = D_80105D18[vabid];
        if (st < 3 && st != 0) {
            SpuFree(D_80105D78[vabid]);
            D_80105D18[vabid] = 0;
            D_80105D70--;
            if (_spu_getInTransfer() == 1) _spu_setInTransfer(0);
        }
    }
}

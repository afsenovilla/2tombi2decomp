// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// AS gnu
// Source: psyz (github.com/Xeeynamo/psyz, MIT) decomp/src/libspu/s_crwa.c, function SpuClearReverbWorkArea.
#include "common.h"
extern s32 _spu_EVdma;
extern s32 _spu_mem_mode_plus;
extern s32 D_800ACB94[];
extern s32 _spu_transMode;
extern void (* volatile _spu_transferCallback)();
extern void (* volatile _spu_IRQCallback)();
int _SpuIsInAllocateArea_(unsigned);
int _spu_t(int arg0, ...);
void WaitEvent(s32);
s32 _SpuIsInAllocateArea_(u32);
extern s32 D_800AC674[];

long SpuClearReverbWorkArea(long rev_mode) {
    void (* volatile callback)();
    s32 oldTransmode;
    s32 dstAddr;
    s32 var_s3;
    s32 transmodeCleared;
    unsigned size;
    unsigned length;
    callback = 0;
    transmodeCleared = 0;
    if (rev_mode < 0 || rev_mode >= 10 ||
        _SpuIsInAllocateArea_(D_800ACB94[rev_mode])) {
        return -1;
    }
    if (rev_mode == 0) {
        length = 0x10 << _spu_mem_mode_plus;
        dstAddr = 0xFFF0 << _spu_mem_mode_plus;
    } else {
        length = (0x10000 - D_800ACB94[rev_mode]) << _spu_mem_mode_plus;
        dstAddr = D_800ACB94[rev_mode] << _spu_mem_mode_plus;
    }
    oldTransmode = _spu_transMode;
    if (_spu_transMode == 1) {
        _spu_transMode = 0;
        transmodeCleared = 1;
    }
    var_s3 = 1;
    if (_spu_transferCallback != 0) {
        callback = _spu_transferCallback;
        _spu_transferCallback = 0;
    }
    while (var_s3 != 0) {
        size = 0x400;
        if (length <= 0x400) {
            size = length;
            var_s3 = 0;
        }
        _spu_t(2, dstAddr);
        _spu_t(1);
        _spu_t(3, &D_800AC674[0], size);
        WaitEvent(_spu_EVdma);
        length -= 0x400;
        dstAddr += 0x400;
    }
    if (transmodeCleared != 0) {
        _spu_transMode = oldTransmode;
    }
    if (callback != 0) {
        _spu_transferCallback = callback;
    }
    return 0;
}

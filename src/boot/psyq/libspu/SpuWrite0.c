// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// AS gnu
// Source: psy-q-decomp (github.com/sozud/psy-q-decomp, MIT) src/spu/s_w0.c, function SpuWrite0.
#include "common.h"
typedef void (*SpuIRQCallbackProc)(void);
extern s32 _spu_EVdma;
extern s8 D_80026DF8[1024];
extern s32 _spu_t(s32 arg0, ...);
extern u16 _spu_tsa;
extern s32 _spu_transMode;
extern s32 _spu_mem_mode_plus;
extern volatile SpuIRQCallbackProc _spu_transferCallback;

unsigned long SpuWrite0(unsigned long size) {
    volatile SpuIRQCallbackProc sp10;
    s32 temp_s5;
    s32 var_s2;
    s32 var_s4;
    s32 var_s6;
    u32 var_s0;
    u32 var_s3;
    temp_s5 = _spu_transMode;
    sp10 = 0;
    var_s6 = 0;
    if (temp_s5 == 1) {
        _spu_transMode = 0;
        var_s6 = 1;
    }
    var_s4 = 1;
    var_s2 = _spu_tsa << _spu_mem_mode_plus;
    if (_spu_transferCallback != 0) {
        sp10 = _spu_transferCallback;
        _spu_transferCallback = 0;
    }
    var_s3 = 0;
    while (var_s4) {
        if (size > 0x400) {
            var_s0 = 0x400;
        } else {
            var_s0 = (size >> 6) << 6;
            var_s4 = 0;
            if (var_s0 < size) {
                var_s0 += 0x40;
            }
        }
        _spu_t(2, var_s2);
        _spu_t(1);
        _spu_t(3, D_80026DF8, var_s0);
        WaitEvent(_spu_EVdma);
        size -= 0x400;
        var_s2 += 0x400;
        var_s3 += var_s0;
    }
    if (var_s6 != 0) {
        _spu_transMode = temp_s5;
    }
    if (sp10 != 0) {
        _spu_transferCallback = sp10;
    }
    return var_s3;
}

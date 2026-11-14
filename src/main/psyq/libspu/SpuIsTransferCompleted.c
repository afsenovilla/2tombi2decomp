// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// AS gnu
// Source: psx_tomba src/psyq/libspu/s_itc.c (MIT), cut to this function by tools/ptsrc.py.
#define SKIP_ASM
#include "pt/common.h"
#include "pt/libspu/libspu_internal.h"
s32 SpuIsTransferCompleted(s32 arg0) {
    s32 in_transfer;

    if ((_spu_trans_mode == 1) || (_spu_inTransfer == 1)) {
        return 1;
    }
    in_transfer = TestEvent(_spu_EVdma);
    if (arg0 == 1) {
        if (in_transfer == 0) {
            do {
            } while (TestEvent(_spu_EVdma) == 0);
        }
        in_transfer = 1;
        _spu_inTransfer = in_transfer;
        return in_transfer;
    }
    if (in_transfer == 1) {
        _spu_inTransfer = in_transfer;
    }
    return in_transfer;
}

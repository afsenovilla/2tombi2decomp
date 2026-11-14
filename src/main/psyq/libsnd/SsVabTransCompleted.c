// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// ASPSX 2.79
#include "common.h"
s16 SpuIsTransferCompleted(s16);                    /* extern */

s16 SsVabTransCompleted(s16 arg0) {
    return SpuIsTransferCompleted(arg0);
}

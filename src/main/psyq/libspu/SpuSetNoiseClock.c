// CC gcc-2.8.1-psx
// FLAGS -O2 -G0 -mno-split-addresses
// AS gnu
#include "common.h"
typedef struct { u8 pad[0x1AA]; u16 noise; } SpuRegs;
extern volatile SpuRegs *D_800AC604;

s32 SpuSetNoiseClock(s32 n_clock) {
    s32 c;
    if (n_clock < 0) c = 0;
    else if (n_clock >= 0x40) c = 0x3F;
    else c = n_clock;
    D_800AC604->noise = (D_800AC604->noise & 0xC0FF) | ((c & 0x3F) << 8);
    return c;
}

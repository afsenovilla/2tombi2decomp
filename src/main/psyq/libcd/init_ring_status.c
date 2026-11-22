// CC gcc-2.8.1-psx
// FLAGS -O2 -G0 -mno-split-addresses
// ASPSX 2.79
#include "common.h"
extern s32 D_80102728;

void init_ring_status(s32 start, u32 count) {
    s32 i;
    for (i = 0; i < count; i++) *(s32 *)(D_80102728 + ((i + start) << 5)) = 0;
}

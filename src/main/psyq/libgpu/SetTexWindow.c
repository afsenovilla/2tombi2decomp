// CC gcc-2.8.1-psx
// FLAGS -O2 -G0 -mno-split-addresses
// ASPSX 2.79
#include "common.h"
typedef struct { s16 x, y, w, h; } RECT;
typedef struct { u32 tag; u32 code[2]; } DR_TWIN;
#define setlen(p, _len) (((u8 *)(p))[3] = (u8)(_len))

void SetTexWindow(DR_TWIN *p, RECT *tw) {
    setlen(p, 2);
    if (tw) p->code[0] = 0xE2000000 | (((tw->y & 0xFF) >> 3) << 15) | (((tw->x & 0xFF) >> 3) << 10) | (((-tw->h & 0xFF) >> 3) << 5) | ((-tw->w & 0xFF) >> 3);
    else p->code[0] = 0;
    p->code[1] = 0;
}

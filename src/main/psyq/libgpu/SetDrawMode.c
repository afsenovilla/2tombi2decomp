// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// AS gnu
#include "common.h"
typedef struct { s16 x, y, w, h; } RECT;
typedef struct { u32 tag; u32 code[2]; } DR_MODE;
#define setlen(p, _len) (((u8 *)(p))[3] = (u8)(_len))

void SetDrawMode(DR_MODE *p, s32 dfe, s32 dtd, s32 tpage, RECT *tw) {
    setlen(p, 2);
    p->code[0] = (dtd ? 0xE1000200 : 0xE1000000) | (dfe ? 0x400 : 0) | (tpage & 0x9FF);
    if (tw) p->code[1] = 0xE2000000 | (((tw->y & 0xFF) >> 3) << 15) | (((tw->x & 0xFF) >> 3) << 10) | (((-tw->h & 0xFF) >> 3) << 5) | ((-tw->w & 0xFF) >> 3);
    else p->code[1] = 0;
}

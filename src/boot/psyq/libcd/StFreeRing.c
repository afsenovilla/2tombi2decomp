// CC gcc-2.8.1-psx
// FLAGS -O2 -G0 -mno-split-addresses
// AS gnu
// RETURN sony
#include "common.h"
typedef struct { u16 id; u16 type; u16 secCount; u16 nSectors; u32 pad[6]; } StHEADER;
extern StHEADER *D_80039EA0;
extern s32 D_80039EA4;
extern s32 D_80039E8C;

u32 StFreeRing(u32 *base) {
    s32 idx;
    s32 i;
    s16 n;
    StHEADER *h;
    idx = (base - (u32 *)&D_80039EA0[D_80039EA4]) / 504;
    h = &D_80039EA0[idx];
    n = D_80039EA0[idx].nSectors;
    if ((s16)h->id != 4) return 1;
    for (i = 0; i < n; i++) {
        s32 k = (i + idx) * 32;
        *(s16 *)((u8 *)D_80039EA0 + k) = 0;
    }
    D_80039E8C = i + idx;
    return 0;
}

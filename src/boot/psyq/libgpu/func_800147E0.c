// CC gcc-2.8.1-psx
// FLAGS -O2 -G0 -mno-split-addresses
// AS gnu
// EPILOGUE sony
#include "common.h"
typedef struct { s16 x, y, w, h; } RECT;
typedef struct { u8 version; u8 queue; u8 level; u8 reverse; s16 w; s16 h; } GEnvT;
extern GEnvT D_80025514;
extern volatile u32 *D_8002561C;
extern u32 D_800384A8[];
extern u32 D_800384D0[];
u32 func_80014F8C(s32);
void func_80014F44(u32 *);
#define CLAMP(a, b, c) (a >= b ? (a > c ? c : a) : b)
#define LOWU(x) (*(u32 *)&(x))

s32 func_800147E0(RECT *rect, u32 color) {
    u32 *ptr;
    rect->w = CLAMP(rect->w, 0, D_80025514.w - 1);
    rect->h = CLAMP(rect->h, 0, D_80025514.h - 1);
    if ((rect->x & 0x3F) || (rect->w & 0x3F)) {
        D_800384A8[0] = ((u32)D_800384D0 & 0xFFFFFF) | 0x08000000;
        ptr = D_800384D0;
        D_800384A8[1] = 0xE3000000;
        D_800384A8[2] = 0xE4FFFFFF;
        D_800384A8[3] = 0xE5000000;
        D_800384A8[4] = 0xE6000000;
        D_800384A8[5] = 0xE1000000 | (*D_8002561C & 0x7FF) | ((color >> 31) << 10);
        D_800384A8[6] = (color & 0xFFFFFF) | 0x60000000;
        D_800384A8[7] = LOWU(rect->x);
        D_800384A8[8] = LOWU(rect->w);
        *ptr = 0x3FFFFFF;
        ptr[1] = func_80014F8C(3) | 0xE3000000;
        ptr[2] = func_80014F8C(4) | 0xE4000000;
        ptr[3] = func_80014F8C(5) | 0xE5000000;
    } else {
        D_800384A8[0] = 0x5FFFFFF;
        D_800384A8[1] = 0xE6000000;
        D_800384A8[2] = 0xE1000000 | (*D_8002561C & 0x7FF) | ((color >> 31) << 10);
        D_800384A8[3] = (color & 0xFFFFFF) | 0x02000000;
        D_800384A8[4] = LOWU(rect->x);
        D_800384A8[5] = LOWU(rect->w);
    }
    func_80014F44(D_800384A8);
    return 0;
}

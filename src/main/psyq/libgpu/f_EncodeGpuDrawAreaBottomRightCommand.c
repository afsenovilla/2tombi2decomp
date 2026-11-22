// CC gcc-2.8.1-psx
// FLAGS -O2 -G0 -mno-split-addresses
// ASPSX 2.79
#include "common.h"
typedef struct { u8 version; u8 x1; u8 level; u8 reverse; s16 w; s16 h; } GEnvT;
extern GEnvT GEnv;
#define CLAMP(a, b, c) (a >= b ? (a > c ? c : a) : b)

u32 f_EncodeGpuDrawAreaBottomRightCommand(s16 x, s16 y) {
    x = CLAMP(x, 0, GEnv.w - 1);
    y = CLAMP(y, 0, GEnv.h - 1);
    return 0xE4000000 | ((y & 0x3FF) << 10) | (x & 0x3FF);
}

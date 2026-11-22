// CC gcc-2.8.1-psx
// FLAGS -O2 -G0 -mno-split-addresses
// AS gnu
#include "common.h"
typedef struct { u8 version; u8 x1; u8 level; u8 reverse; } GEnvT;
extern GEnvT D_80025514;
extern s32 (*D_80025510)(const char *, ...);
extern char D_800101B0[];

s32 SetGraphDebug(s32 level) {
    s32 prev = D_80025514.level;
    D_80025514.level = level;
    if (D_80025514.level) D_80025510(D_800101B0, D_80025514.level, D_80025514.version, D_80025514.reverse);
    return prev;
}

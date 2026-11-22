// CC gcc-2.8.1-psx
// FLAGS -O2 -G0 -mno-split-addresses
// AS gnu
#include "common.h"
typedef struct { u8 version; u8 x1; u8 level; u8 reverse; } GEnvT;
extern GEnvT D_800A59A0;
extern s32 (*D_800A599C)(const char *, ...);
extern char D_8001BE6C[];

s32 SetGraphDebug(s32 level) {
    s32 prev = D_800A59A0.level;
    D_800A59A0.level = level;
    if (D_800A59A0.level) D_800A599C(D_8001BE6C, D_800A59A0.level, D_800A59A0.version, D_800A59A0.reverse);
    return prev;
}

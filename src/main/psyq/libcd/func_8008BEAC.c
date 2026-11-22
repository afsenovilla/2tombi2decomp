// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// AS gnu
#include "common.h"
typedef struct { s32 parent; s32 pos; s8 name[0x24]; } CdDir;
extern CdDir D_80102D6C[];
s32 strcmp(s8 *, s8 *);

s32 func_8008BEAC(s32 parent, s8 *name) {
    s32 i;
    for (i = 0; i < 128; i++) {
        if (D_80102D6C[i].parent == 0) break;
        if (D_80102D6C[i].parent == parent && strcmp(name, D_80102D6C[i].name) == 0) return i + 1;
    }
    return -1;
}

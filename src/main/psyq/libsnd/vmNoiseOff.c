// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// AS gnu
#include "common.h"
typedef struct { s16 a; s16 p2; s16 b; u8 pad[0x1D - 6]; u8 c; u8 pad2[0x38 - 0x1E]; } Voice;
extern Voice D_801054C8[];

void vmNoiseOff(u8 v) { D_801054C8[v].c = 0; D_801054C8[v].a = 0; D_801054C8[v].b = 0; }

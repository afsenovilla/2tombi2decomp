// CC gcc-2.8.1-nocse
// FLAGS -O2 -G0 -mno-split-addresses
// AS gnu
// RETURN sony
#include "common.h"
typedef struct { u8 a; u8 n; u8 pad[2]; } Ent;
extern Ent D_800253FC[];
extern u8 D_80025444[];
extern volatile u8 *D_80025434;
extern volatile u8 *D_80025438;
extern volatile u8 *D_8002543C;
extern volatile u8 *D_80025440;

// Unidentified licensed-region boot module [0x80011A0C, 0x80012D2C): BIOS region byte check and a message screen
// (Krom2RawAdd / libgpu), built with the library compiler; not a known Psy-Q library (no signature covers it).

void func_80012584(s32 arg0)
{
    s32 i;

    *D_80025434 = 1;
    *D_80025440 = 7;
    for (i = 0; i < 4; i++) {
        *(s32 *)0 = i;
    }
    *D_80025434 = 1;
    *D_8002543C = 0x18;
    *D_80025434 = 0;
    for (i = 0; i < D_800253FC[arg0].n; i++) {
        *D_8002543C = D_80025444[i];
    }
    *D_80025434 = 0;
    *D_80025438 = D_800253FC[arg0].a;
}

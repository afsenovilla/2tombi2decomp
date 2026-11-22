// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// AS gnu
#include "common.h"
typedef struct { u8 pad[0x14]; u8 play; u8 pad2[0x98 - 0x15]; s32 flags; u8 pad3[0xB0 - 0x9C]; } Seq;
extern Seq *D_80104C30[];

void _SsSndReplay(s16 acc, s16 seq) {
    Seq *p;
    p = &D_80104C30[acc][seq];
    p->play = 1;
    D_80104C30[acc][seq].flags &= ~8;
}

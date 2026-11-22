// CC gcc-2.8.1-psx
// FLAGS -O2 -G0 -mno-split-addresses -fno-delayed-branch
// AS gnu
#include "common.h"
typedef struct { u8 pad[0x20]; u8 loop; u8 loop2; u8 pad2[0x58 - 0x22]; s16 lvol; s16 rvol; u8 pad3[0xB0 - 0x5C]; } Seq;
extern Seq *D_80104C30[];

void SsSetLoop(s16 acc, s16 seq, s16 l) {
    Seq *s;
    s = D_80104C30[acc];
    s += seq;
    s->loop = l;
    s->loop2 = 0;
}

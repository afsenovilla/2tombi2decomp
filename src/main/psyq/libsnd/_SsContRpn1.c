// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// AS gnu
#include "common.h"
typedef struct { u8 pad[0x18]; u8 ch; u8 pad1[5]; u8 cnt; u8 pad2[0x90 - 0x1F]; s32 delta; u8 pad3[0xB0 - 0x94]; } Seq;
extern Seq *D_80104C30[];
s32 _SsReadDeltaValue(s16, s16);

void _SsContRpn1(s16 acc, s16 seq, u8 ch) {
    Seq *s = &D_80104C30[acc][seq];
    s->ch = ch;
    s->cnt++;
    s->delta = _SsReadDeltaValue(acc, seq);
}

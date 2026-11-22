// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// AS gnu
#include "common.h"
typedef struct { u8 pad[0x14]; u8 eos; u8 pad2[0xB0 - 0x15]; } Seq;
extern Seq *D_80104C30[];

u8 SsIsEos(s16 acc, s16 seq) {
    Seq *s;
    s = D_80104C30[acc];
    s += seq;
    return s->eos;
}

// CC gcc-2.7.2-psx
// FLAGS -O1 -G0
// AS gnu
#include "common.h"
typedef struct { u8 pad[0x20]; u8 loop; u8 loop2; u8 pad2[0x58 - 0x22]; s16 lvol; s16 rvol; u8 pad3[0xB0 - 0x5C]; } Seq;
extern Seq *D_80104C30[];
extern s16 D_80105D0C;

s16 _SsVmGetSeqRVol(s16 n) {
    Seq *s;
    s = D_80104C30[n & 0xFF];
    D_80105D0C = n;
    s += (n & 0xFF00) >> 8;
    return s->rvol;
}

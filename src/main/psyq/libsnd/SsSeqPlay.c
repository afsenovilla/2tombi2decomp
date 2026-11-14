// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// ASPSX 2.79
#define SsSeqPlay SsSeqPlay_hdr
#include "psyq_all.h"
#undef SsSeqPlay
M2C_UNK Snd_SetPlayMode(s16, M2C_UNK, s8, s16);     /* extern */

void SsSeqPlay(s16 arg0, s8 arg1, s16 arg2) {
    Snd_SetPlayMode(arg0, 0, arg1, arg2);
}

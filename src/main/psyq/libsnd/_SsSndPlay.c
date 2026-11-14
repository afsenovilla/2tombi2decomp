// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// ASPSX 2.79
#include "common.h"
s32 _SsSeqPlay(s16, s16);                             /* extern */

void _SsSndPlay(s16 arg0, s16 arg1) {
    _SsSeqPlay(arg0, arg1);
}

// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// ASPSX 2.79
#include "common.h"
s32 _SsSndStop(s16, s16);                             /* extern */

void SsSepStop(s16 arg0, s16 arg1) {
    _SsSndStop(arg0, arg1);
}

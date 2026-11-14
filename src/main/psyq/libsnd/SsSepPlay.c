// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// ASPSX 2.79
#include "common.h"
s32 Snd_SetPlayMode(s16, s16, s8, s16);               /* extern */

void SsSepPlay(s16 arg0, s16 arg1, s8 arg2, s16 arg3) {
    Snd_SetPlayMode(arg0, arg1, arg2, arg3);
}

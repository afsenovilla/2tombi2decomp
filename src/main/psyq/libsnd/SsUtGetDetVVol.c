// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// ASPSX 2.79
#include "common.h"
void SpuGetVoiceVolume(s32, s16 *, s16 *);

s16 SsUtGetDetVVol(s16 vc, s16 *l, s16 *r) {
    if ((u16)vc < 24) {
        SpuGetVoiceVolume(vc, l, r);
        return 0;
    }
    return -1;
}

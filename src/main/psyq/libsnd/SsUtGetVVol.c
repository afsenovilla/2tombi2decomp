// CC gcc-2.8.1-psx
// FLAGS -O2 -G0 -mno-split-addresses
// AS gnu
// EPILOGUE sony
#include "common.h"
void SpuGetVoiceVolume(s32, s16 *, s16 *);

s16 SsUtGetVVol(s16 vc, s16 *voll, s16 *volr) {
    s16 vol[2];
    if ((u16)vc < 24) {
        SpuGetVoiceVolume(vc, &vol[0], &vol[1]);
        *voll = vol[0] / 129;
        *volr = vol[1] / 129;
        return 0;
    }
    return -1;
}

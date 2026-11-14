// CC gcc-2.8.1-psx
// FLAGS -O2 -G0
// ASPSX 2.79
#define SpuGetVoiceEnvelope SpuGetVoiceEnvelope_hdr
#include "psyq_all.h"
#undef SpuGetVoiceEnvelope
extern s32 D_800AC604;

void SpuGetVoiceEnvelope(s32 vNum, s16 *envx) {
    *envx = (s16) M2C_FIELD(((vNum * 0x10) + D_800AC604), u16 *, 0xC);
}

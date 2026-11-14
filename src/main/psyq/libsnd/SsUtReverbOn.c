// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// ASPSX 2.79
// Source: psx_tomba src/psyq/libsnd/ut_rfb.c (MIT), cut to this function by tools/ptsrc.py.
#define SKIP_ASM
#include "pt/common.h"
#include "pt/libsnd/libsnd_i.h"
s32 SpuSetReverb(s32);
void SsUtSetReverbFeedback(s16 feedback);
void SsUtReverbOff(void);
void SsUtReverbOn(void) { SpuSetReverb(1); }

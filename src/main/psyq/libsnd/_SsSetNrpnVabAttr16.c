// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// ASPSX 2.79
// Source: psx_tomba src/psyq/libsnd/de_16.c (MIT), cut to this function by tools/ptsrc.py.
#define SKIP_ASM
#include "pt/common.h"
#include "pt/libsnd/libsnd_i.h"
void SsUtSetReverbFeedback(short);
void SsUtSetReverbDelay(short);
void _SsSetNrpnVabAttr16(short vabId, short prog, short tone, VagAtr vagAtr, short fn, u8 data) {
    SsUtSetReverbDepth(data, data);
}
void _SsSetNrpnVabAttr17(short vabId, short prog, short tone, VagAtr vagAtr, short fn, u8 data);
void _SsSetNrpnVabAttr18(short vabId, short prog, short tone, VagAtr vagAtr, short fn, u8 data);
void _SsSetNrpnVabAttr19(short vabId, short prog, short tone, VagAtr vagAtr, short fn, u8 data);

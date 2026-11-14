// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// ASPSX 2.79
// Source: psx_tomba src/psyq/libsnd/de_15.c (MIT), cut to this function by tools/ptsrc.py.
#define SKIP_ASM
#include "pt/common.h"
#include "pt/libsnd/libsnd_i.h"
short SsUtSetReverbType(short);
void _SsSetNrpnVabAttr15(short vabId, short prog, short tone, VagAtr vagAtr, short fn, u8 data) {
    SsUtSetReverbType(data);
}

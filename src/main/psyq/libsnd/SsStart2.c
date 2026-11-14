// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// ASPSX 2.79
// Source: psx_tomba src/psyq/libsnd/ut_roff.c (MIT), cut to this function by tools/ptsrc.py.
#define SKIP_ASM
#include "pt/common.h"
#include "pt/libsnd/libsnd_i.h"
void SsStart2(void) { _SsStart(0); }
void _SsTrapIntrVSync(void);
void _SsSeqCalledTbyT_1per2(void);

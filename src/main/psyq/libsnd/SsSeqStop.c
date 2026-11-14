// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// ASPSX 2.79
// Source: psx_tomba src/psyq/libsnd/ssstop.c (MIT), cut to this function by tools/ptsrc.py.
#define SKIP_ASM
#include "pt/common.h"
#include "pt/libsnd/libsnd_i.h"
void _SsSndStop(s16 arg0, s16 arg1);
void SsSeqStop(short seq_access_num) { _SsSndStop(seq_access_num, 0); }
void SsSepStop(short sep_access_num, short arg1);

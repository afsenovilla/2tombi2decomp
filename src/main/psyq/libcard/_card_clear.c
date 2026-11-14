// CC gcc-2.8.1-psx
// FLAGS -O2 -G0
// ASPSX 2.79
// Source: psx_tomba src/psyq/libcard/card.c (MIT), cut to this function by tools/ptsrc.py.
#define SKIP_ASM
#include "pt/common.h"
void _card_clear(s32 arg0)
{
    _new_card();
    _card_write(arg0, 0x3F, 0);
}

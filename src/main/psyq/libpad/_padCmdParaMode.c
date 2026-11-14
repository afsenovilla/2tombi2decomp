// CC gcc-2.8.1-psx
// FLAGS -O2 -G0
// ASPSX 2.79
#define _padCmdParaMode _padCmdParaMode_hdr
#include "psyq_all.h"
#undef _padCmdParaMode
void _padCmdParaMode(void *arg0, s8 arg1) {
    M2C_FIELD(arg0, s8 *, 0x37) = 0x43;
    M2C_FIELD(arg0, void **, 0x2C) = (void *) (arg0 + 0x24);
    M2C_FIELD(arg0, s8 *, 0x24) = arg1;
    M2C_FIELD(arg0, s8 *, 0x36) = 1;
}

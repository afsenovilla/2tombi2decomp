// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// ASPSX 2.79
#include "common.h"
extern u8 D_80102500[];

u8 *func_8008913C(u32 port) { u8 *p = D_80102500; if (port & 0xF0) p += 0xF0; return p; }

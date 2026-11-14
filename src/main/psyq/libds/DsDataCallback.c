// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// ASPSX 2.79
#define DsDataCallback DsDataCallback_hdr
#include "psyq_all.h"
#undef DsDataCallback
M2C_UNK DMACallback(M2C_UNK, s32);                  /* extern */

void DsDataCallback(s32 arg0) {
    DMACallback(3, arg0);
}

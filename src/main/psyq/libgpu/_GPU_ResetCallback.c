// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// ASPSX 2.79
#define _GPU_ResetCallback _GPU_ResetCallback_hdr
#include "psyq_all.h"
#undef _GPU_ResetCallback
M2C_UNK DMACallback(M2C_UNK, M2C_UNK *);            /* extern */
extern M2C_UNK func_80082FB4;

void _GPU_ResetCallback(void) {
    DMACallback(2, &func_80082FB4);
}

// CC gcc-2.8.1-psx
// FLAGS -O2 -G0 -mno-split-addresses -fno-delayed-branch
// AS gnu
#define StUnSetRing StUnSetRing_hdr
#include "psyq_all.h"
#undef StUnSetRing
M2C_UNK DsDataCallback(M2C_UNK);                    /* extern */
M2C_UNK DsReadyCallback(M2C_UNK);                   /* extern */
extern s32 D_800268F0;
extern s8 *D_80026C48;
extern s8 *D_80026C54;

void StUnSetRing(void) {
    EnterCriticalSection();
    if (D_800268F0 == 1) {
        DsDataCallback(0);
        DsReadyCallback(0);
    } else {
        CdDataCallback(NULL);
        CdReadyCallback(NULL);
    }
    *D_80026C48 = 0;
    *D_80026C54 = 0;
    ExitCriticalSection();
}

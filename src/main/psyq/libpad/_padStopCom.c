// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// ASPSX 2.79
#define _padStopCom _padStopCom_hdr
#include "psyq_all.h"
#undef _padStopCom
M2C_UNK ChangeClearRCnt(M2C_UNK, M2C_UNK);          /* extern */
M2C_UNK EnterCriticalSection();                     /* extern */
M2C_UNK ExitCriticalSection();                      /* extern */
M2C_UNK SysDeqIntRP(M2C_UNK, M2C_UNK *);            /* extern */
extern M2C_UNK D_80102440;

void _padStopCom(void) {
    EnterCriticalSection();
    ChangeClearRCnt(3, 1);
    SysDeqIntRP(2, &D_80102440);
    ExitCriticalSection();
}

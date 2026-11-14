// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// ASPSX 2.79
#define func_80017BC8 func_80017BC8_hdr
#include "psyq_all.h"
#undef func_80017BC8
M2C_UNK EnterCriticalSection();                     /* extern */
M2C_UNK ExitCriticalSection();                      /* extern */
M2C_UNK SysDeqIntRP(M2C_UNK, M2C_UNK *);            /* extern */
extern M2C_UNK D_80039E30;

s32 func_80017BC8(void) {
    EnterCriticalSection();
    SysDeqIntRP(1, &D_80039E30);
    ExitCriticalSection();
    return 1;
}

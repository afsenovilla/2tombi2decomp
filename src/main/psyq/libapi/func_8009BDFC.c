// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// ASPSX 2.79
#define func_8009BDFC func_8009BDFC_hdr
#include "psyq_all.h"
#undef func_8009BDFC
M2C_UNK EnterCriticalSection();                     /* extern */
M2C_UNK ExitCriticalSection();                      /* extern */
M2C_UNK SysDeqIntRP(M2C_UNK, M2C_UNK *);            /* extern */
extern M2C_UNK D_80105F18;

s32 func_8009BDFC(void) {
    EnterCriticalSection();
    SysDeqIntRP(1, &D_80105F18);
    ExitCriticalSection();
    return 1;
}

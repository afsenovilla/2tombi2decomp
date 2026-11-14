// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// ASPSX 2.79
#define SsInit SsInit_hdr
#include "psyq_all.h"
#undef SsInit
M2C_UNK _SsInit();                                  /* extern */
M2C_UNK func_80096A70();                            /* extern */

void SsInit(void) {
    ResetCallback();
    func_80096A70();
    SpuClearReverbWorkArea(7);
    _SsInit();
}

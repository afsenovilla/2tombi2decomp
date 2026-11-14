// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// AS gnu
#define func_8008C1EC func_8008C1EC_hdr
#include "psyq_all.h"
#undef func_8008C1EC
s32 func_8008C1EC(s32 arg0, s32 arg1, u32 *arg2) {
    CdlLOC sp10;

    CdIntToPos(arg1, &sp10);
    CdControl(2U, &sp10.minute, NULL);
    CdRead(arg0, arg2, 0x80);
    return CdReadSync(0, NULL) == 0;
}

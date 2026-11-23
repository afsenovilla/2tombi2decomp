// CC gcc-2.8.1-psx
// FLAGS -O2 -G0 -mno-split-addresses
// AS gnu
#include "common.h"
typedef struct { s32 u0, u4; s32 *addr; s32 uc; s32 size; s32 nsec; s32 u18, u1c; s32 cnt; s32 done; s32 cbsync; s32 cbready; s32 cbdata; u8 *result; } CdRd;
extern volatile CdRd D_80026BF8;
s32 CdSyncCallback(s32);

void func_8001B6EC(void) {
    volatile s32 *p = &D_80026BF8.cbsync;
    volatile CdRd *r;
    CdSyncCallback(*p);
    r = (volatile CdRd *)(p - 10);
    r->done = 0;
}

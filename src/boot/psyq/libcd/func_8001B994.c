// CC gcc-2.8.1-psx
// FLAGS -O2 -G0 -mno-split-addresses -fno-delayed-branch
// AS gnu
#include "common.h"
typedef struct { s32 u0, u4; s32 *addr; s32 uc; s32 size; s32 nsec; s32 u18, u1c; s32 cnt; s32 done; s32 cbsync; s32 cbready; s32 cbdata; u8 *result; } CdRd;
extern volatile CdRd D_80026BF8;
extern void (*D_80026838)(s32, u8 *);
extern s32 D_8002683C;
s32 CdReadyCallback(s32);
s32 CdDataCallback(s32);
s32 CdSyncCallback(void *);
s32 CdControlF(s32, u8 *);
void func_8001B6EC(void);

void func_8001B994(void) {
    volatile CdRd *r = &D_80026BF8;
    r->addr += r->size;
    r->nsec--;
    r->cnt++;
    if (r->nsec == 0) {
        CdReadyCallback(r->cbready);
        if (D_8002683C & 1) CdDataCallback(r->cbdata);
        CdSyncCallback(func_8001B6EC);
        CdControlF(9, 0);
        r->done = 1;
        if (D_80026838) D_80026838(2, r->result);
    }
}

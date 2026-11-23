// CC gcc-2.8.1-psx
// FLAGS -O2 -G0 -mno-split-addresses
// AS gnu
// Source: psyz (github.com/Xeeynamo/psyz, MIT) decomp/src/libcd/cdread.c, function CdReadSync (4.4 ReadAttr layout; the fields through pointers to start_time and done).
#include "common.h"
typedef struct { s32 u0, u4; s32 *addr; s32 uc; s32 size; s32 nsec; s32 u18, u1c; s32 cnt; s32 done; s32 cbsync; s32 cbready; s32 cbdata; u8 *result; } CdRd;
extern volatile CdRd D_800AC2E4;
s32 VSync(s32);
s32 CdReady(s32, u8 *);
s32 func_8008C5D8(s32);

int CdReadSync(int mode, u8 *result)
{
    volatile s32 *t = &D_800AC2E4.u1c; volatile s32 *dn = &D_800AC2E4.done;
    int ret;

    do {
        if (VSync(-1) > *t + 1200) {
            ret = -1;
        } else if (t[-2] < 0 || VSync(-1) > t[-1] + 60) {
            func_8008C5D8(1);
            ret = t[-7];
        } else {
            ret = t[-2];
        }
    } while (mode == 0 && ((*dn && ret == 0) || ret > 0));
    CdReady(1, result);
    if (*dn && ret == 0) {
        ret = 1;
    }
    return ret;
}

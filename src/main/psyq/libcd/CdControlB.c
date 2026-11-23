// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// AS gnu
// Source: psyz (github.com/Xeeynamo/psyz, MIT) decomp/src/libcd/sys.c, CdControl* with the inline cd_cw (4.4: do/while, the -1 set at the end of the body, the 1 a long-lived local).
#include "common.h"
typedef unsigned char u_char;
typedef void (*CdlCB)(u_char,u_char *);
extern CdlCB CD_cbsync;
extern u_char CD_status;
int CD_sync(int mode, u_char* result);
int CD_cw(u8 com, u8* param, u_char* result, s32 arg3);
extern int D_800ABF34[32];
static inline int cd_cw(u8 com, u8* param, u_char* result, s32 arg3) {
    CdlCB old = CD_cbsync;
    int count = 3;
    int m1; int one = 1;
    do {

        CD_cbsync = 0;

        if (com != one && (CD_status & 0x10)) {
            CD_cw(0x01, 0, 0, 0);
        }
        if (param == 0 || D_800ABF34[com] == 0 ||
            !CD_cw(0x02, param, result, 0)) {
            CD_cbsync = old;
            if (!CD_cw(com, param, result, arg3)) {
                return 0;
            }
        }
        m1 = -1;
    } while (--count != m1);
    CD_cbsync = old;
    return -1;
}

int CdControlB(u_char com, u_char* param, u_char* result) {
    if (cd_cw(com, param, result, 0)) {
        return 0;
    }
    return CD_sync(0, result) == 0x02;
}

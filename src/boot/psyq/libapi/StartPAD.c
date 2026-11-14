// CC gcc-2.8.1-psx
// FLAGS -O2 -G0
// ASPSX 2.79
// Same function as src/main/psyq/libapi/StartPAD.c (MAIN.EXE).
#define StartPAD StartPAD_hdr
#include "psyq_all.h"
#undef StartPAD
M2C_UNK ChangeClearPAD(M2C_UNK);                    /* extern */
M2C_UNK EnablePAD();                                /* extern */
M2C_UNK StartPAD2();                                /* extern */

s32 StartPAD(void) {
    StartPAD2();
    ChangeClearPAD(0);
    EnablePAD();
    return 1;
}

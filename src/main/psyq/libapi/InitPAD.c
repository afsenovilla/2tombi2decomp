// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// AS gnu
#define InitPAD InitPAD_hdr
#include "psyq_all.h"
#undef InitPAD
M2C_UNK ChangeClearPAD(M2C_UNK);                    /* extern */
M2C_UNK EnterCriticalSection();                     /* extern */
M2C_UNK ExitCriticalSection();                      /* extern */
M2C_UNK InitPAD2(s32, M2C_UNK, M2C_UNK, M2C_UNK);   /* extern */
M2C_UNK _patch_pad();                               /* extern */
M2C_UNK _remove_ChgclrPAD();                        /* extern */
M2C_UNK func_8009BD84();                            /* extern */
extern s32 D_800ACF44;

void InitPAD(s32 arg0, M2C_UNK arg1, M2C_UNK arg2, M2C_UNK arg3) {
    _remove_ChgclrPAD();
    EnterCriticalSection();
    _patch_pad();
    ExitCriticalSection();
    ChangeClearPAD(0);
    func_8009BD84();
    InitPAD2(arg0, arg1, arg2, arg3);
    D_800ACF44 = 1;
}

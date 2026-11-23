// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// AS gnu
// Source: psyz (github.com/Xeeynamo/psyz, MIT) decomp/src/libsnd/vm_seq.c, function _SsVmSeqKeyOff (4.4: voices reserved in the mask are skipped; `one = 1` in the body keeps the sllv / and).
#include "common.h"
typedef struct { u8 pad[0x10]; s16 seq_sep_no; u8 pad2[0x38 - 0x12]; } Voice;
extern Voice D_801054C8[];
extern s8 D_80105CEC;
extern s16 D_80105D10;
extern s32 D_800AC3F4;
void _SsVmKeyOffNow(int);

void _SsVmSeqKeyOff(s16 seq_sep_num) {
    u8 i;
    s32 one;
    for (i = 0; i < D_80105CEC; i++) {
        one = 1;
        if (!(D_800AC3F4 & (one << i)) && D_801054C8[i].seq_sep_no == seq_sep_num) {
            D_80105D10 = i;
            _SsVmKeyOffNow(0);
        }
    }
}

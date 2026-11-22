// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// AS gnu
#include "common.h"
typedef struct { u8 pad[1]; u8 vol; u8 pad2[2]; u8 pan; u8 pad3[11]; } ProgAtr;
extern ProgAtr *D_80105CDC;
s32 _SsVmVSetUp(s16, s16);

s16 _SsVmSetProgVol(s16 vab, s16 prog, u8 vol) {
    if (_SsVmVSetUp(vab, prog) != 0) return -1;
    D_80105CDC[prog].vol = vol;
    return D_80105CDC[prog].vol;
}

// CC gcc-2.8.1-psx
// FLAGS -O2 -G0 -mno-split-addresses
// AS gnu
// Source: psyz (github.com/Xeeynamo/psyz, MIT) decomp/src/libcd/bios.c, function CD_flush.
#include "common.h"
typedef struct {
    s8 cd_intr;
    u8 D_800B53D1;
    u8 D_800B53D2;
} flush;
extern volatile s8* cd_reg0;
extern volatile u8* cd_reg2;
extern volatile u8* cd_reg3;
extern volatile s32* cd_com_delay;
extern volatile flush cd_intr;

void CD_flush(void) {
    *cd_reg0 = 1;
    while (*cd_reg3 & 7) {
        *cd_reg0 = 1;
        *cd_reg3 = 7;
        *cd_reg2 = 7;
    }
    {volatile flush *p = &cd_intr;
    p->D_800B53D2 = 0;
    p->D_800B53D1 = p->D_800B53D2;
    p->cd_intr = 2;}
    *cd_reg0 = 0;
    *cd_reg3 = 0;
    *cd_com_delay = 0x1325;
}

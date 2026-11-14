// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// ASPSX 2.79
// Source: psx_tomba src/psyq/libcd/c_002.c (MIT), cut to this function by tools/ptsrc.py.
#define SKIP_ASM
#include "pt/common.h"
#include "psyq/libcd.h"
extern volatile s8* c002_cd_reg0;
extern volatile s8* c002_cd_reg1;
extern volatile s8* c002_cd_reg2;
extern volatile s8* c002_cd_reg3;
extern s32 Stframe_no;
extern s16 Stsector_offset;
extern s32 StCdIntrFlag;
extern s32 StFinalSector;
extern s32 StRingIdx1;
extern s32 StRingIdx2;
extern s32 StRingIdx3;
extern s32 StRingSize;
void StClearRing(void)
{
    StRingIdx3 = 0;
    StRingIdx2 = 0;
    StRingIdx1 = 0;
    StFinalSector = 0;
    init_ring_status(0, StRingSize);
    StCdIntrFlag = 0;
    Stsector_offset = 0;
    Stframe_no = 0;
}

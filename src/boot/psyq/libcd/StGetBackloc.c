// CC gcc-2.8.1-psx
// FLAGS -O2 -G0
// ASPSX 2.79
// Source: psx_tomba src/psyq/libcd/c_004.c (MIT), cut to this function by tools/ptsrc.py.
#define SKIP_ASM
#include "pt/common.h"
#include "psyq/libcd.h"
extern volatile s8* c004_cd_reg0;
extern volatile s8* c004_cd_reg1;
extern volatile s8* c004_cd_reg2;
extern volatile s8* c004_cd_reg3;
extern CdlLOC previous_frame_location;
extern int next_frameid;
extern void (*StFunc1)(void);
extern int StFinalSector;
extern int StMode;
extern int StRingIdx1;
extern int StRingIdx2;
extern StHEADER* StRingAddr;
void data_ready_callback(void);
int StGetBackloc(CdlLOC* loc)
{
    if (StMode != 0) return -1;
    CdIntToPos(CdPosToInt(&previous_frame_location) + 1, loc);
    return next_frameid;
}

// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// AS gnu
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
void data_ready_callback(void)
{
    StHEADER* ptr = &StRingAddr[StRingIdx2];
    do {
        ptr->id = 2;
    } while(0);
    previous_frame_location = ptr->loc;
    next_frameid = ptr->frameCount;
    StRingIdx2 = StRingIdx1;
    if (StFunc1 != NULL) {
        StFunc1();
    }
    StFinalSector = 0;
}
int StGetBackloc(CdlLOC* loc);

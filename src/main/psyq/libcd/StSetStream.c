// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// AS gnu
// Source: psx_tomba src/psyq/libcd/c_005.c (MIT), cut to this function by tools/ptsrc.py.
#define SKIP_ASM
#include "pt/common.h"
#include "psyq/libcd.h"
extern volatile s8* c005_cd_reg0;
extern volatile s8* c005_cd_reg1;
extern volatile s8* c005_cd_reg2;
extern volatile s8* c005_cd_reg3;
extern int Stframe_no;
extern short Stsector_offset;
extern int StRgb24;
extern int StFunc1;
extern int StFunc2;
extern int StCHANNEL;
extern int CChannel;
extern int StEmu_Addr;
void StSetStream(u_long mode, u_long start_frame, u_long end_frame, void (*func1)(), void (*func2)())
{
    StSetMask(1, start_frame, end_frame);
    StEmu_Addr = 0;
    StFunc1 = func1;
    StRgb24 = mode & 1;
    CChannel = 0;
    StCHANNEL = 0;
    Stsector_offset = 0;
    Stframe_no = 0;
    StFunc2 = func2;
}

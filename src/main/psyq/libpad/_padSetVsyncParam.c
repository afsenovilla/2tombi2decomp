// CC gcc-2.7.2-psx
// FLAGS -O1 -G0
// ASPSX 2.79
#include "common.h"
extern s32 D_80102440[];
void func_800867CC(void);
void func_80086764(void);

void _padSetVsyncParam(void) {
    D_80102440[1] = (s32)func_800867CC;
    D_80102440[2] = (s32)func_80086764;
    D_80102440[0] = 0;
    D_80102440[3] = 0;
}

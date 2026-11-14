// CC gcc-2.8.1-psx
// FLAGS -O2 -G0
// ASPSX 2.79
#include "common.h"
extern s32 *D_8002561C;
extern s32 *D_80025620;
extern s32 *D_80025624;
extern s32 *D_80025628;

void func_80014F44(s32 arg0) {
    *D_8002561C = 0x04000002;
    *D_80025620 = arg0;
    *D_80025624 = 0;
    *D_80025628 = 0x01000401;
}

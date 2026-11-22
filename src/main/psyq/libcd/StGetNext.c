// CC gcc-2.8.1-psx
// FLAGS -O2 -G0 -mno-split-addresses
// AS gnu
// RETURN sony
// Source: psx_tomba src/psyq/libcd/c_009.c (MIT), cut to this function by tools/ptsrc.py.
#define SKIP_ASM
#include "pt/common.h"
#include "psyq/libcd.h"
extern volatile s8* c009_cd_reg0;
extern volatile s8* c009_cd_reg1;
extern volatile s8* c009_cd_reg2;
extern volatile s8* c009_cd_reg3;
extern s32 StRingIdx3;
extern s32 StEndFrame;
extern StHEADER* StRingAddr;
extern volatile s32 StRingSize;
u_long StGetNext(u_long** addr, u_long** header) {
    volatile StHEADER* ptr = &StRingAddr[StRingIdx3];
    if (ptr->id == 1) {
        StRingIdx3 = 0;
        if (StEndFrame != 0) {
            ptr->id = 0;
        }
        ptr = &StRingAddr[StRingIdx3];
    }
    if (ptr->id == 2) {
        ptr->id = 4;
        *addr = &StRingAddr[StRingSize] + (StRingIdx3 * 0x3F);
        *header = ptr;
        return 0;
    } else {
        return 1;
    }
}

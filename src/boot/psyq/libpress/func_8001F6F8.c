// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// ASPSX 2.79
#include "common.h"
s32 printf(const char *, ...);
extern char D_80010D40[];
extern volatile u32 *D_8002741C;
extern volatile u32 *D_800273F0;
extern volatile u32 *D_800273FC;

s32 func_8001F6F8(char *s) {
    printf(D_80010D40, s);
    *D_8002741C = 0x80000000;
    *D_800273F0 = 0;
    *D_800273FC = 0;
    *D_800273FC;
    *D_8002741C = 0x60000000;
    return 0;
}

// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// AS gnu
#include "common.h"
s32 printf(const char *, ...);
extern volatile u32 *D_8002741C;
extern volatile u32 *D_800273F0;
extern volatile u32 *D_800273FC;
extern u32 D_800272D8[];
extern u32 D_8002735C[];
extern char D_80010D04[];

void func_8001F3AC(s32 mode) {
    switch (mode) {
    case 0:
        *D_8002741C = 0x80000000;
        *D_800273F0 = 0;
        *D_800273FC = 0;
        *D_8002741C = 0x60000000;
        func_8001F49C(D_800272D8, 0x20);
        func_8001F49C(D_8002735C, 0x20);
        break;
    case 1:
        *D_8002741C = 0x80000000;
        *D_800273F0 = 0;
        *D_800273FC = 0;
        *D_800273FC;
        *D_8002741C = 0x60000000;
        break;
    default:
        printf(D_80010D04, mode);
        break;
    }
}

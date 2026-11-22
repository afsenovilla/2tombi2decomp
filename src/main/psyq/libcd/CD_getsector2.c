// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// AS gnu
#include "common.h"
extern volatile u8 *D_800AC280;
extern volatile u8 *D_800AC28C;
extern volatile s32 *D_800AC290;
extern volatile s32 *D_800AC2B4;
extern volatile s32 *D_800AC2B8;
extern volatile s32 *D_800AC2BC;
extern volatile s32 *D_800AC2C0;
extern volatile s32 *D_800AC2C4;

s32 CD_getsector2(s32 madr, s32 size) {
    volatile s32 x;
    *D_800AC280 = 0;
    *D_800AC28C = 0x80;
    *D_800AC2B4 = 0x21020843;
    *D_800AC290 = 0x1325;
    *D_800AC2B8 |= 0x8000;
    *D_800AC2BC = madr;
    *D_800AC2C0 = size | 0x10000;
    while (!(*D_800AC280 & 0x40));
    *D_800AC2C4 = 0x11400100;
    x = *D_800AC2C4;
    return 0;
}

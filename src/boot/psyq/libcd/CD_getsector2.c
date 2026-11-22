// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// AS gnu
#include "common.h"
extern volatile u8 *D_80026B94;
extern volatile u8 *D_80026BA0;
extern volatile s32 *D_80026BA4;
extern volatile s32 *D_80026BC8;
extern volatile s32 *D_80026BCC;
extern volatile s32 *D_80026BD0;
extern volatile s32 *D_80026BD4;
extern volatile s32 *D_80026BD8;

s32 CD_getsector2(s32 madr, s32 size) {
    volatile s32 x;
    *D_80026B94 = 0;
    *D_80026BA0 = 0x80;
    *D_80026BC8 = 0x21020843;
    *D_80026BA4 = 0x1325;
    *D_80026BCC |= 0x8000;
    *D_80026BD0 = madr;
    *D_80026BD4 = size | 0x10000;
    while (!(*D_80026B94 & 0x40));
    *D_80026BD8 = 0x11400100;
    x = *D_80026BD8;
    return 0;
}

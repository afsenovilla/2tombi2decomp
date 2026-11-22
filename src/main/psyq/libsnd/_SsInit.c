// CC gcc-2.7.2-psx
// AS gnu
// EPILOGUE sony
#include "common.h"
extern u16 D_800AC400[16];
extern s32 D_80104CB0[32][16];
extern s32 D_80104C2C;
extern s32 D_80104C28;
extern s32 D_80104C24;
void _SsVmInit(s32);

void _SsInit(void) {
    s32 i, j;
    u16 *src;
    u16 *dst;
    dst = (u16 *)0x1F801D80;
    i = 0;
    src = D_800AC400;
    for (; i < 16; i++) {
        *dst++ = *src++;
    }
    _SsVmInit(24);
    for (j = 0; j < 32; j++) {
        for (i = 15; i >= 0; i--) {
            D_80104CB0[j][i] = 0;
        }
    }
    D_80104C2C = 0x3C;
    D_80104C28 = 0;
    D_80104C24 = 0;
}

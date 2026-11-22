// CC gcc-2.8.1-psx
// FLAGS -O2 -G0 -mno-split-addresses
// AS gnu
// EPILOGUE sony
#include "common.h"
extern volatile s32 *D_8002561C;
extern volatile s32 *D_80025620;
extern volatile s32 *D_80025628;
extern volatile s32 *D_80025638;
extern volatile s32 D_8002563C;
extern volatile s32 D_80025640;
extern s32 D_8002564C;
extern s32 D_80025650;
extern s32 D_80025654;
extern char D_80010324[];
s32 VSync(s32);
s32 SetIntrMask(s32);

s32 func_800157B0(void) {
    s32 m;
    if (D_80025650 < VSync(-1) || D_80025654++ > 0xF0000) {
        *D_8002561C;
        printf(D_80010324, (D_8002563C - D_80025640) & 0x3F, *D_8002561C, *D_80025628, *D_80025620);
        m = SetIntrMask(0);
        D_80025640 = 0;
        D_8002564C = m;
        D_8002563C = D_80025640;
        *D_80025628 = 0x401;
        *D_80025638 |= 0x800;
        *D_8002561C = 0x02000000;
        *D_8002561C = 0x01000000;
        SetIntrMask(D_8002564C);
        return -1;
    }
    return 0;
}

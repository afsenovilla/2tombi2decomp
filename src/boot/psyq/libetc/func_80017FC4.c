// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// AS gnu
#include "common.h"
extern volatile s32 D_800267B4;
extern char D_800104A4[];
void puts(char *);
void ChangeClearPAD(s32);
void ChangeClearRCnt(s32, s32);

void func_80017FC4(s32 count, s32 timeout) {
    volatile s32 cnt = timeout << 15;
    while (D_800267B4 < count) {
        if (--cnt == -1) {
            puts(D_800104A4);
            ChangeClearPAD(0);
            ChangeClearRCnt(3, 0);
            return;
        }
    }
}

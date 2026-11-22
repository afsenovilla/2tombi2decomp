// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// AS gnu
#include "common.h"
extern volatile s32 D_800ABDE0;
extern char D_8001C020[];
void puts(char *);
void ChangeClearPAD(s32);
void ChangeClearRCnt(s32, s32);

void func_80085A78(s32 count, s32 timeout) {
    volatile s32 cnt = timeout << 15;
    while (D_800ABDE0 < count) {
        if (--cnt == -1) {
            puts(D_8001C020);
            ChangeClearPAD(0);
            ChangeClearRCnt(3, 0);
            return;
        }
    }
}

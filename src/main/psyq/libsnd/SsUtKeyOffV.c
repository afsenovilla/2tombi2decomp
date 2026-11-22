// CC gcc-2.8.1-psx
// FLAGS -O2 -G0 -mno-split-addresses
// AS gnu
// EPILOGUE sony
#include "common.h"
extern s32 D_80104C24;
extern s16 D_80105D10;
void _SsVmKeyOffNow(s32);

s16 SsUtKeyOffV(s16 voice) {
    if (D_80104C24 == 1) return -1;
    D_80104C24 = 1;
    if ((u16)voice < 24) {
        D_80105D10 = voice;
        _SsVmKeyOffNow(0);
        D_80104C24 = 0;
        return 0;
    }
    D_80104C24 = 0;
    return -1;
}

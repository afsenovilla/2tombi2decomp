// CC gcc-2.8.1-psx
// FLAGS -O2 -G0 -mno-split-addresses
// AS gnu
// RETURN sony
#include "common.h"
extern s8 D_80105CEC;

s8 SsSetReservedVoice(u8 voices) {
    if ((voices >= 0x19) || (voices == 0)) return -1;
    D_80105CEC = voices;
    return D_80105CEC;
}

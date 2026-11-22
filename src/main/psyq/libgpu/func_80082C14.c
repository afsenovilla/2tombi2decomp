// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// AS gnu
#include "common.h"
extern u8 D_80100B28[];

u8 func_80082C14(s32 i) {
    return D_80100B28[i];
}

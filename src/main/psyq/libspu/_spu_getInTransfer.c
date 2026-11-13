#include "common.h"

extern s32 D_800AC638;
s32 _spu_getInTransfer(void) {
    return D_800AC638 != 1;
}

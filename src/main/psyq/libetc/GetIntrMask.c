#include "common.h"

extern u16 *D_800ABDA8;
u16 GetIntrMask(void) {
    return *D_800ABDA8;
}

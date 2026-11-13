#include "common.h"

s32 CdGetSector2(void) {
    return CD_getsector2() == 0;
}

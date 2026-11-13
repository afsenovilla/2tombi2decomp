#include "common.h"

s32 CdGetSector(void) {
    return CD_getsector() == 0;
}

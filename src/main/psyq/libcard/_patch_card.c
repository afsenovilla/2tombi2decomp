// ASM by design: keeps ra in a global and calls the BIOS through t1/t2, assembly in Sony's source.
#include "common.h"

INCLUDE_ASM("asm/main/nonmatchings/psyq/libcard/_patch_card", _patch_card);

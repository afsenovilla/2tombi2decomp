// ASM by design: jumps into the BIOS (0xA000DFAC / 0xA000DF80) without a frame, assembly in Sony's source.
#include "common.h"

INCLUDE_ASM("asm/main/nonmatchings/psyq/libcard/func_8009C0D0", func_8009C0D0);

// ASM by design: patch code run inside the BIOS ($v1 base, jumps through a BIOS vector), assembly in Sony's source.
#include "common.h"

INCLUDE_ASM("asm/main/nonmatchings/psyq/libcard/func_8009C08C", func_8009C08C);

// ASM by design: restores the callee-saved registers, sp and gp, assembly in Sony's source.
#include "common.h"

INCLUDE_ASM("asm/main/nonmatchings/psyq/libc2/longjmp", longjmp);

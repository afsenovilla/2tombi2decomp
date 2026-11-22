// ASM by design: keeps ra in a global and calls the BIOS through t1/t2 (hand-written instructions), assembly in Sony's source.
#include "common.h"

INCLUDE_ASM("asm/main/nonmatchings/psyq/libapi/_remove_ChgclrPAD", _remove_ChgclrPAD);

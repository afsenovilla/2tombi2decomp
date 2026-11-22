// ASM by design: libsn start-up code (t0, linker-computed constructor count), assembly in Sony's source.
#include "common.h"

INCLUDE_ASM("asm/boot/nonmatchings/psyq/libsn/__do_global_dtors", __do_global_dtors);

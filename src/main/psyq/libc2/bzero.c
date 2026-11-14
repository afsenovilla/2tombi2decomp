// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// ASPSX 2.79
// Source: psx_tomba src/psyq/libc2/bzero.c (MIT), cut to this function by tools/ptsrc.py.
#define SKIP_ASM
#include "pt/common.h"
s8* bzero(s8* arg0, s32 arg1)
{
    s32 var_a1;
    s8* var_a0;
    s8* var_v0;

    var_a0 = arg0;
    var_a1 = arg1;
    var_v0 = NULL;
    if (var_a0 != NULL) {
        var_v0 = var_a0;
        if (var_a1 <= 0) {
            return NULL;
        }
        do {
            *var_a0 = 0;
            var_a1 -= 1;
            var_a0 += 1;
        } while (var_a1 > 0);
    }
    return var_v0;
}

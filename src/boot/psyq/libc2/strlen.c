// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// ASPSX 2.79
#include "common.h"

s32 strlen(s8 *s) {
    s32 n = 0;
    s32 r = 0;
    if (s != 0) {
        while (*s++) n++;
        r = n;
    }
    return r;
}

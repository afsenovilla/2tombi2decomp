// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// ASPSX 2.79
#include "common.h"

s32 strncmp(s8 *a, s8 *b, s32 n) {
    if ((a == NULL) || (b == NULL)) {
        s32 r = 0;
        if (a != b) r = (a != NULL) ? 1 : -1;
        return r;
    }
    while (--n >= 0) {
        if (*a != *b++) break;
        if (*a++ == '\0') return 0;
    }
    if (n < 0) return 0;
    b--;
    return *a - *b;
}

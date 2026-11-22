// CC gcc-2.8.1-psx
// FLAGS -O2 -G0 -mno-split-addresses
// AS gnu
// RETURN sony
#include "common.h"

s32 strcmp(s8 *a, s8 *b) {
    if ((a == NULL) || (b == NULL)) {
        if (a == b) return 0;
        return (a != NULL) ? 1 : -1;
    }
    while (*a == *b++) {
        if (*a++ == '\0') return 0;
    }
    b--;
    return *a - *b;
}

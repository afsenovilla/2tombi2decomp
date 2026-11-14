// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// ASPSX 2.79
// Source: psx_tomba src/psyq/libc2/strcpy.c (MIT), cut to this function by tools/ptsrc.py.
#define SKIP_ASM
#include "pt/common.h"
char* strcpy(char* dest, const char* src)
{
    char* dst;

    if (dest == NULL || src == NULL) {
        return NULL;
    }

    dst = dest;
    while ((*dest++ = *src++) != '\0') {}

    return dst;
}

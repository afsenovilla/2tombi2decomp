// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// ASPSX 2.79
// Source: psx_tomba src/psyq/libc2/memchr.c (MIT), cut to this function by tools/ptsrc.py.
#define SKIP_ASM
#include "pt/common.h"
void* memchr(unsigned char* pMem, unsigned char ch, int len) {
    if (pMem == NULL || len <= 0) {
        return NULL;
    }
    len--;
    while (len >= 0) {
        if (*pMem++ == ch) {
            return pMem - 1;
        }
        len--;
    }   
    return NULL;
}

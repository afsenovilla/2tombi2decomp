// CC gcc-2.8.1-psx
// FLAGS -O2 -G0 -mno-split-addresses
// AS gnu
// RETURN sony
#include "common.h"

void *memmove(u8 *pDst, u8 *pSrc, s32 size) {
    if (pDst >= pSrc) {
        while (size-- > 0) pDst[size] = pSrc[size];
    } else {
        while (size-- > 0) *pDst++ = *pSrc++;
    }
    return pDst;
}

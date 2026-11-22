// CC gcc-2.8.1-psx
// FLAGS -O2 -G0 -mno-split-addresses
// AS gnu
// EPILOGUE sony
#include "common.h"
s32 prnt(s32, char *, s32 *);

s32 printf(char *fmt, s32 a1, s32 a2, s32 a3) {
    s32 *ap = &a1;
    char **pf = &fmt;
    ap[1] = a2;
    ap[2] = a3;
    return prnt(1, *pf, ap);
}

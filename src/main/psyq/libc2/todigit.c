// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// AS gnu
// EPILOGUE sony
#include "common.h"
extern u8 D_800ACE75[];
s8 tolower(s8);

s32 todigit(s8 c) {
    s32 r;
    if (D_800ACE75[(u8)c] & 4) r = c - '0';
    else if (D_800ACE75[(u8)c] & 3) r = tolower(c) - 0x57;
    else r = 9999999;
    return r;
}

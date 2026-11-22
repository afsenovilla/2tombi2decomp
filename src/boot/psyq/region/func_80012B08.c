// Unidentified licensed-region boot module [0x80011A0C, 0x80012D2C): BIOS region byte check and a message screen
// (Krom2RawAdd / libgpu), built with the library compiler; not a known Psy-Q library (no signature covers it).
// CC gcc-2.8.1-psx
// FLAGS -O2 -G0 -mno-split-addresses
// AS gnu
// RETURN sony
#include "common.h"

u32 func_80012B08(u8 *p)
{
    u16 lo = 0;
    u16 hi = 7;
    s32 n;
    s32 b;
    s32 first;

    for (n = 14; n >= 0; n--) {
        first = 1;

        for (b = 7; b >= 0; b--) {
            if ((*p >> b) & 1) {
                if (first != 0) {
                    if (lo < b) {
                        lo = b;
                    }
                    if (b < hi) {
                        hi = b;
                    }
                    first = 0;
                } else if (b < hi) {
                    hi = b;
                }
            }
        }
        p++;
    }
    return (hi << 16) | lo;
}

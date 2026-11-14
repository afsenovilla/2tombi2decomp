// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// AS gnu
// Source: psx_tomba src/psyq/libapi/counter.c (MIT), cut to this function by tools/ptsrc.py.
#define SKIP_ASM
#include "pt/common.h"
typedef struct {
    u_short currentVal;
    short : 16;
    u_short mode;
    short : 16;
    u_short targetVal;
    short : 16;
    int : 32;
} RootCounter;
extern int (*_interruptReg)[];
extern volatile RootCounter (*_rootCounter0)[];
extern long _interruptMasks[];
long SetRCnt(u_long counter, u_short targetVal, long mode);
long GetRCnt(u_long spec);
long StartRCnt(u_long spec);
long StopRCnt(u_long spec) {
    int i;

    i = spec & 0xFFFF;
    (*_interruptReg)[1] &= ~_interruptMasks[i];
    return 1;
}
long ResetRCnt(u_long spec);

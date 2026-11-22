// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// ASPSX 2.79
#include "common.h"
typedef struct { u8 tag[3]; u8 len; u32 code[2]; } DrStp;

void SetDrawStp(DrStp *p, s32 pbw) {
    p->len = 2;
    p->code[0] = pbw ? 0xE6000001 : 0xE6000000;
    p->code[1] = 0;
}

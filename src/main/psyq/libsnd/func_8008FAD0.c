// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// ASPSX 2.79
#include "common.h"
typedef struct { u8 pad[0x24]; u8 v; } RevArg;
void SsUtSetReverbFeedback(s16);

void func_8008FAD0(s32 a, s32 b, s32 c, RevArg s) { SsUtSetReverbFeedback(s.v); }

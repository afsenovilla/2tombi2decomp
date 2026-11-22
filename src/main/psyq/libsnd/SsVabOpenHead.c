// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// ASPSX 2.79
#include "common.h"
s16 _SsVabOpenHeadWithMode(u8 *, s16, void *, s32);
void func_800964B4(void);

s16 SsVabOpenHead(u8 *addr, s16 vabid) { return _SsVabOpenHeadWithMode(addr, vabid, func_800964B4, 0); }

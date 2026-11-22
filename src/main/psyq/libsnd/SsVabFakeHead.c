// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// ASPSX 2.79
#include "common.h"
s16 _SsVabOpenHeadWithMode(u8 *, s16, void *, s32);
void func_80096588(void);

s16 SsVabFakeHead(u8 *addr, s16 vabid, s32 sbaddr) { return _SsVabOpenHeadWithMode(addr, vabid, func_80096588, sbaddr); }

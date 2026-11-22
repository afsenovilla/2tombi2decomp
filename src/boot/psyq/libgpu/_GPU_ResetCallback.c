// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// ASPSX 2.79
#include "common.h"
void DMACallback(s32, void *);
void func_80015290(void);

void _GPU_ResetCallback(void) { DMACallback(2, func_80015290); }

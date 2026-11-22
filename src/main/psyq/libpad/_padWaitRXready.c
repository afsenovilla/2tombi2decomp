// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// AS gnu
#include "common.h"
extern volatile u16 *D_800ABE9C;

void _padWaitRXready(void) { while (!(D_800ABE9C[2] & 2)); }

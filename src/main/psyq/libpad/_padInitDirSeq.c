// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// AS gnu
#include "common.h"
extern s32 *D_800ABE50;
extern s32 *D_800ABE54;
extern s32 *D_800ABE58;
extern s32 func_80089194;
extern s32 func_800892A4;
extern s32 func_800895E8;

void _padInitDirSeq(void) {
    D_800ABE50 = &func_80089194;
    D_800ABE54 = &func_800895E8;
    D_800ABE58 = &func_800892A4;
}

#include "common.h"

extern s32 *D_800A5AA8;
extern s32 *D_800A5AAC;
extern s32 *D_800A5AB0;
extern s32 *D_800A5AB4;
void func_80082C68(s32 arg0) {
    *D_800A5AA8 = 0x04000002;
    *D_800A5AAC = arg0;
    *D_800A5AB0 = 0;
    *D_800A5AB4 = 0x01000401;
}

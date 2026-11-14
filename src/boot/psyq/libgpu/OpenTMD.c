// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// ASPSX 2.79
#define OpenTMD OpenTMD_hdr
#include "psyq_all.h"
#undef OpenTMD
extern M2C_UNK D_80039DFC;
extern M2C_UNK D_80039E00;
extern M2C_UNK D_80039E04;
extern s32 D_80039E08;

s32 OpenTMD(u32 *tmd, s32 obj_no) {
    s32 temp_v0;

    temp_v0 = func_80016280((s32) tmd, obj_no, (s32) &D_80039E04, (s32) &D_80039DFC, /* extra? */ &D_80039E00);
    D_80039E08 = temp_v0;
    return temp_v0;
}

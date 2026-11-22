// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// ASPSX 2.86
// Source: psx_tomba src/psyq/libspu/s_m_init.c (MIT), cut to this function by tools/ptsrc.py.
#define SKIP_ASM
#include "pt/common.h"
#include "pt/libspu/libspu_internal.h"
extern s32 D_800AC664;
extern s32 _spu_AllocLastNum;
extern SPU_MALLOC* _spu_memList;
s32 SpuInitMalloc(s32 num, s8* top) {
    if (num > 0) {
        _spu_memList = top;
        _spu_memList[0].addr = 1073745936;
        _spu_memList[0].size = (0x10000 << _spu_mem_mode_plus) - 0x1010;
        _spu_AllocLastNum = 0;
        D_800AC664 = num;
        return num;
    }
    return 0;
}

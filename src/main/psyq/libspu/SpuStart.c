// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// AS gnu
// Source: psx_tomba src/psyq/libspu/s_ini.c (MIT), cut to this function by tools/ptsrc.py.
#define SKIP_ASM
#include "pt/common.h"
#include "pt/libspu/libspu_internal.h"
extern s32 _spu_EVdma;
extern s32 _spu_keystat;
extern s32 _spu_trans_mode;
extern s32 _spu_rev_flag;
extern s32 _spu_rev_reserve_wa;
extern s32 _spu_rev_offsetaddr;
extern struct SpuRevAttr _spu_rev_attr;
extern s32 _spu_RQvoice;
extern s32 _spu_RQmask;
extern u16 _spu_voice_centerNote[];
extern s32 _spu_zerobuf[];
extern s32 _spu_env;
extern s32 _spu_isCalled;
void _SpuInit(s32 arg0);
void SpuStart(void) {
    if (_spu_isCalled == 0) {
        _spu_isCalled = 1;
        EnterCriticalSection();
        _SpuDataCallback(_spu_FiDMA);
        _spu_EVdma = OpenEvent(HwSPU, EvSpCOMP, EvMdNOINTR, NULL);
        EnableEvent(_spu_EVdma);
        ExitCriticalSection();
    }
}

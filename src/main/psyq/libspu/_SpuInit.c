// CC gcc-2.8.1-psx
// FLAGS -O2 -G0 -mno-split-addresses
// ASPSX 2.79
// Source: psyz (github.com/Xeeynamo/psyz, MIT) decomp/src/libspu/s_ini.c, function _SpuInit.
#include "common.h"
int ResetCallback(void) ;
int RestartCallback(void) ;
typedef struct {
    short left;
    short right;
} SpuVolume;
typedef struct {
    unsigned long mask;
    long mode;
    SpuVolume depth;
    long delay;
    long feedback;
} SpuReverbAttr;
extern void SpuStart (void);
typedef struct tagSpuMalloc {
    unsigned addr;
    unsigned size;
} SPU_MALLOC;
extern int D_800AC664;
extern int _spu_AllocLastNum;
extern volatile s32 D_800AC5BC;
extern volatile s32 D_800AC5B8;
extern s32 D_800AC5F0;
extern s32 D_800AC590;
extern SPU_MALLOC* _spu_memList;
extern s32 _spu_rev_flag;
extern s32 _spu_rev_offsetaddr;
extern s32 _spu_rev_reserve_wa;
extern s32 D_800ACB94[];
extern SpuReverbAttr _spu_rev_attr;
extern s32 _spu_transMode;
extern int _spu_trans_mode;
extern u16 D_800AC5C0[];
extern void (* volatile _spu_transferCallback)();
extern void (* volatile _spu_IRQCallback)();
int _spu_init(int bHot);
void _spu_FsetRXX(unsigned offset, unsigned value, unsigned mode);
extern int D_800AC590;
extern int _spu_trans_mode;
extern int _spu_rev_flag;
extern int _spu_rev_reserve_wa;
extern int _spu_rev_offsetaddr;
extern SpuReverbAttr _spu_rev_attr;
extern volatile s32 D_800AC5B8;
extern volatile s32 D_800AC5BC;
extern unsigned short D_800AC5C0[24];
extern int D_800AC5F0;
void SpuStart(void);

void _SpuInit(int bHot) {
    int i;
    ResetCallback();
    _spu_init(bHot);
    if (bHot == 0) {
        u16 *p;
        u16 v = 0xC000;
        for (i = 23, p = &D_800AC5C0[23]; i >= 0; i--) {
            *p-- = v;
        }
    }
    SpuStart();
    _spu_rev_flag = 0;
    _spu_rev_reserve_wa = 0;
    _spu_rev_attr.mode = 0;
    _spu_rev_attr.depth.left = 0;
    _spu_rev_attr.depth.right = 0;
    _spu_rev_attr.delay = 0;
    _spu_rev_attr.feedback = 0;
    _spu_rev_offsetaddr = D_800ACB94[0];
    _spu_FsetRXX(0xD1, _spu_rev_offsetaddr, 0);
    D_800AC664 = 0;
    _spu_AllocLastNum = 0;
    _spu_memList = 0;
    _spu_trans_mode = 0;
    _spu_transMode = 0;
    D_800AC590 = 0;
    D_800AC5BC = 0;
    D_800AC5B8 = 0;
    D_800AC5F0 = 0;
    __asm__ volatile("");
}

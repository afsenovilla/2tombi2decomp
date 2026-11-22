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
extern int D_80026DE8;
extern int D_80026DEC;
extern volatile s32 D_80026D40;
extern volatile s32 D_80026D3C;
extern s32 D_80026D74;
extern s32 D_80026D14;
extern SPU_MALLOC* D_80026DF0;
extern s32 D_80026D1C;
extern s32 D_80026D24;
extern s32 D_80026D20;
extern s32 D_800271F8[];
extern SpuReverbAttr D_80026D28;
extern s32 _spu_transMode;
extern int _spu_trans_mode;
extern u16 D_80026D44[];
extern void (* volatile _spu_transferCallback)();
extern void (* volatile _spu_IRQCallback)();
int _spu_init(int bHot);
void _spu_FsetRXX(unsigned offset, unsigned value, unsigned mode);
extern int D_80026D14;
extern int _spu_trans_mode;
extern int D_80026D1C;
extern int D_80026D20;
extern int D_80026D24;
extern SpuReverbAttr D_80026D28;
extern volatile s32 D_80026D3C;
extern volatile s32 D_80026D40;
extern unsigned short D_80026D44[24];
extern int D_80026D74;
void SpuStart(void);

void _SpuInit(int bHot) {
    int i;
    ResetCallback();
    _spu_init(bHot);
    if (bHot == 0) {
        u16 *p;
        u16 v = 0xC000;
        for (i = 23, p = &D_80026D44[23]; i >= 0; i--) {
            *p-- = v;
        }
    }
    SpuStart();
    D_80026D1C = 0;
    D_80026D20 = 0;
    D_80026D28.mode = 0;
    D_80026D28.depth.left = 0;
    D_80026D28.depth.right = 0;
    D_80026D28.delay = 0;
    D_80026D28.feedback = 0;
    D_80026D24 = D_800271F8[0];
    _spu_FsetRXX(0xD1, D_80026D24, 0);
    D_80026DE8 = 0;
    D_80026DEC = 0;
    D_80026DF0 = 0;
    _spu_trans_mode = 0;
    _spu_transMode = 0;
    D_80026D14 = 0;
    D_80026D40 = 0;
    D_80026D3C = 0;
    D_80026D74 = 0;
    __asm__ volatile("");
}

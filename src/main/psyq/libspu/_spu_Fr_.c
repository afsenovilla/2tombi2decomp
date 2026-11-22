// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// AS gnu
// Source: psy-q-decomp (github.com/sozud/psy-q-decomp, MIT) src/spu/spu.c, function _spu_Fr_.
#include "common.h"
typedef struct {
    s16 left;
    s16 right;
} SpuVolume;
typedef struct tagSpuVoiceRegister {
    SpuVolume volume;
    u16 pitch;
    u16 addr;
    u16 adsr[2];
    u16 volumex;
    u16 loop_addr;
} SPU_VOICE_REG;
typedef struct tagSpuControl {
    SPU_VOICE_REG voice[24];
    SpuVolume main_vol;
    SpuVolume rev_vol;
    u16 key_on[2];
    u16 key_off[2];
    u16 chan_fm[2];
    u16 noise_mode[2];
    u16 rev_mode[2];
    u32 chan_on;
    u16 unk;
    u16 rev_work_addr;
    u16 irq_addr;
    u16 trans_addr;
    u16 trans_fifo;
    u16 spucnt;
    u16 data_trans;
    u16 spustat;
    SpuVolume cd_vol;
    SpuVolume ex_vol;
    SpuVolume main_volx;
    SpuVolume unk_vol;
    u16 dAPF1;
    u16 dAPF2;
    u16 vIIR;
    u16 vCOMB1;
    u16 vCOMB2;
    u16 vCOMB3;
    u16 vCOMB4;
    u16 vWALL;
    u16 vAPF1;
    u16 vAPF2;
    u16 mLSAME;
    u16 mRSAME;
    u16 mLCOMB1;
    u16 mRCOMB1;
    u16 mLCOMB2;
    u16 mRCOMB2;
    u16 dLSAME;
    u16 dRSAME;
    u16 mLDIFF;
    u16 mRDIFF;
    u16 mLCOMB3;
    u16 mRCOMB3;
    u16 mLCOMB4;
    u16 mRCOMB4;
    u16 dLDIFF;
    u16 dRDIFF;
    u16 mLAPF1;
    u16 mRAPF1;
    u16 mLAPF2;
    u16 mRAPF2;
    u16 vLIN;
    u16 vRIN;
} SPU_RXX;
union SpuUnion {
    SPU_RXX _rxx;
    SPU_RXX rxxnv;
    volatile SPU_RXX rxx;
    u16 _raw[0x100];
    volatile u16 raw[0x100];
};
extern void _spu_Fw1ts(void);
extern union SpuUnion* _spu_RXX;
void _spu_FsetDelayR(void);
void _spu_Fw1ts(void);
extern union SpuUnion* _spu_RXX;
extern volatile int* dma_spu_madr;
extern volatile int* dma_spu_bcr;
extern volatile int* dma_spu_chcr;
extern int D_800AC654;
void _spu_FsetDelayR(void);
void _spu_Fw1ts(void);

void _spu_Fr_(s32 arg0, u16 arg1, s32 arg2) {
    _spu_RXX->rxx.trans_addr = arg1;
    _spu_Fw1ts();
    _spu_RXX->rxx.spucnt |= 0x30;
    _spu_Fw1ts();
    _spu_FsetDelayR();
    *dma_spu_madr = arg0;
    *dma_spu_bcr = (arg2 << 0x10) | 0x10;
    D_800AC654 = 1;
    *dma_spu_chcr = 0x01000200;
}

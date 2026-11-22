// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// ASPSX 2.79
// Source: psyz (github.com/Xeeynamo/psyz, MIT) decomp/src/libspu/s_gvv.c, function SpuGetVoiceVolume.
#include "common.h"
typedef unsigned short u_short;
typedef unsigned long u_long;
typedef struct {
    short left;
    short right;
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
    volatile SPU_RXX rxx;
    volatile u16 raw[0x100];
};
extern union SpuUnion* _spu_RXX;
extern void (* volatile _spu_transferCallback)();
extern void (* volatile _spu_IRQCallback)();
static inline void assign(u_short val, short* out) {
    u_long offset = 0x8000;
    u_long uval = val;
    if (uval >= 0x4000) {
        *out = uval - offset;
    } else {
        *out = val;
    }
}

void SpuGetVoiceVolume(int vNum, short* volL, short* volR) {
    u_short left = (((SPU_VOICE_REG*)_spu_RXX)[vNum].volume.left);
    u_short right = (((SPU_VOICE_REG*)_spu_RXX)[vNum].volume.right);
    assign(left, volL);
    assign(right, volR);
}

// CC gcc-2.8.1-psx
// FLAGS -O2 -G0 -mno-split-addresses -fno-delayed-branch
// AS gnu
// Source: psyz (github.com/Xeeynamo/psyz, MIT) decomp/src/libspu/s_sk.c, function SpuSetKey.
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
extern volatile s32 D_800AC5BC;
extern volatile s32 D_800AC5B8;
extern volatile u16 D_80105EC8[10];
extern union SpuUnion* _spu_RXX;
extern s32 D_800AC5F0;
extern s32 D_800AC590;
extern void (* volatile _spu_transferCallback)();
extern void (* volatile _spu_IRQCallback)();

void SpuSetKey(long on_off, u_long voice_bit) {
    u_short lo_bits;
    u_short hi_bits;
    voice_bit &= 0xFFFFFF;
    lo_bits = voice_bit;
    hi_bits = voice_bit >> 16;
    switch (on_off) {
    case 1:
        if (D_800AC5F0 & 1) {
            D_80105EC8[0] = lo_bits;
            D_80105EC8[1] = hi_bits;
            D_800AC5BC |= 1;
            D_800AC5B8 |= voice_bit;
            if (D_80105EC8[2] & voice_bit) {
                D_80105EC8[2] &= ~voice_bit;
            }
            if (D_80105EC8[3] & hi_bits) {
                D_80105EC8[3] &= ~hi_bits;
            }
        } else {
            _spu_RXX->rxx.key_on[0] = (lo_bits);
            _spu_RXX->rxx.key_on[1] = (hi_bits);
            D_800AC590 |= voice_bit;
        }
        break;
    case 0:
        if (D_800AC5F0 & 1) {
            volatile u16 *rq = D_80105EC8;
            rq[2] = lo_bits;
            rq[3] = hi_bits;
            D_800AC5BC |= 1;
            D_800AC5B8 &= ~voice_bit;
            if (rq[0] & voice_bit) {
                rq[0] &= ~voice_bit;
            }
            if (rq[1] & hi_bits) {
                rq[1] &= ~hi_bits;
            }
        } else {
            _spu_RXX->rxx.key_off[0] = (lo_bits);
            _spu_RXX->rxx.key_off[1] = (hi_bits);
            D_800AC590 &= ~voice_bit;
        }
        break;
    }
    __asm__ volatile("");
}

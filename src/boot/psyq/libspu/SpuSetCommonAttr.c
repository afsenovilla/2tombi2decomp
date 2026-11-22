// CC gcc-2.8.1-nocse
// FLAGS -O2 -G0 -mno-split-addresses
// AS gnu
#include "common.h"
typedef struct {
    short left;
    short right;
} SpuVolume;
typedef struct {
    SpuVolume volume;
    long reverb;
    long mix;
} SpuExtAttr;
typedef struct {
    unsigned long mask;
    SpuVolume mvol;
    SpuVolume mvolmode;
    SpuVolume mvolx;
    SpuExtAttr cd;
    SpuExtAttr ext;
} SpuCommonAttr;
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

void SpuSetCommonAttr(SpuCommonAttr* attr) {
    u16 mvol_mode_left;
    u16 mvol_mode_right;
    u16 vol_total_left;
    u16 vol_total_right;
    u32 mask;
    s32 bSetAll;
    u16 cnt;
    vol_total_left = 0;
    vol_total_right = 0;
    mask = attr->mask;
    bSetAll = attr->mask == 0;
    if (bSetAll || mask & (0x01 << 0)) {
        if (bSetAll || mask & (0x01 << 2)) {
            switch (attr->mvolmode.left) {
            case 1:
                mvol_mode_left = 0x8000;
                break;
            case 2:
                mvol_mode_left = 0x9000;
                break;
            case 3:
                mvol_mode_left = 0xA000;
                break;
            case 4:
                mvol_mode_left = 0xB000;
                break;
            case 5:
                mvol_mode_left = 0xC000;
                break;
            case 6:
                mvol_mode_left = 0xD000;
                break;
            case 7:
                mvol_mode_left = 0xE000;
                break;
            case 0:
                vol_total_left = attr->mvol.left;
                mvol_mode_left = 0x0000;
                break;
            default:
                vol_total_left = attr->mvol.left;
                mvol_mode_left = 0x0000;
                break;
            }
        } else {
            vol_total_left = attr->mvol.left;
            mvol_mode_left = 0x0000;
        }
        if (mvol_mode_left != 0x0000) {
            if (attr->mvol.left > 0x7F) {
                vol_total_left = 0x7F;
            } else if (attr->mvol.left < 0) {
                vol_total_left = 0;
            } else {
                vol_total_left = attr->mvol.left;
            }
        }
        vol_total_left &= ~(1 << 15);
        _spu_RXX->rxx.main_vol.left = ((vol_total_left) | mvol_mode_left);
    }
    if (bSetAll || mask & (0x01 << 1)) {
        if (bSetAll || mask & (0x01 << 3)) {
            switch (attr->mvolmode.right) {
            case 1:
                mvol_mode_right = 0x8000;
                break;
            case 2:
                mvol_mode_right = 0x9000;
                break;
            case 3:
                mvol_mode_right = 0xA000;
                break;
            case 4:
                mvol_mode_right = 0xB000;
                break;
            case 5:
                mvol_mode_right = 0xC000;
                break;
            case 6:
                mvol_mode_right = 0xD000;
                break;
            case 7:
                mvol_mode_right = 0xE000;
                break;
            case 0:
                vol_total_right = attr->mvol.right;
                mvol_mode_right = 0x0000;
                break;
            default:
                vol_total_right = attr->mvol.right;
                mvol_mode_right = 0x0000;
                break;
            }
        } else {
            vol_total_right = attr->mvol.right;
            mvol_mode_right = 0x0000;
        }
        if (mvol_mode_right != 0x0000) {
            if (attr->mvol.right > 0x7F) {
                vol_total_right = 0x7F;
            } else if (attr->mvol.right < 0) {
                vol_total_right = 0;
            } else {
                vol_total_right = attr->mvol.right;
            }
        }
        vol_total_right &= ~(1 << 15);
        _spu_RXX->rxx.main_vol.right = (vol_total_right | mvol_mode_right);
    }
    if (bSetAll || (mask & (0x01 << 6))) {
        _spu_RXX->rxx.cd_vol.left = (attr->cd.volume.left);
    }
    if (bSetAll || (mask & (0x01 << 7))) {
        _spu_RXX->rxx.cd_vol.right = (attr->cd.volume.right);
    }
    if (bSetAll || (mask & (0x01 << 10))) {
        _spu_RXX->rxx.ex_vol.left = (attr->ext.volume.left);
    }
    if (bSetAll || (mask & (0x01 << 11))) {
        _spu_RXX->rxx.ex_vol.right = (attr->ext.volume.right);
    }
    if (bSetAll || (mask & (0x01 << 8))) {
        if (attr->cd.reverb == 0) {
            cnt = (_spu_RXX->rxx.spucnt);
            cnt &= ~(1 << 2);
            _spu_RXX->rxx.spucnt = (cnt);
        } else {
            cnt = (_spu_RXX->rxx.spucnt);
            cnt |= (1 << 2);
            _spu_RXX->rxx.spucnt = (cnt);
        }
    }
    if (bSetAll || (mask & (0x01 << 9))) {
        if (attr->cd.mix == 0) {
            cnt = (_spu_RXX->rxx.spucnt);
            cnt &= ~(1 << 0);
            _spu_RXX->rxx.spucnt = (cnt);
        } else {
            cnt = (_spu_RXX->rxx.spucnt);
            cnt |= (1 << 0);
            _spu_RXX->rxx.spucnt = (cnt);
        }
    }
    if (bSetAll || (mask & (0x01 << 12))) {
        if (attr->ext.reverb == 0) {
            cnt = (_spu_RXX->rxx.spucnt);
            cnt &= ~(1 << 3);
            _spu_RXX->rxx.spucnt = (cnt);
        } else {
            cnt = (_spu_RXX->rxx.spucnt);
            cnt |= (1 << 3);
            _spu_RXX->rxx.spucnt = (cnt);
        }
    }
    if (bSetAll || (mask & (0x01 << 13))) {
        if (attr->ext.mix == 0) {
            cnt = (_spu_RXX->rxx.spucnt);
            cnt &= ~(1 << 1);
            _spu_RXX->rxx.spucnt = (cnt);

        } else {
            cnt = (_spu_RXX->rxx.spucnt);
            cnt |= (1 << 1);
            _spu_RXX->rxx.spucnt = (cnt);
        }
    }
    __asm__ volatile("");
}

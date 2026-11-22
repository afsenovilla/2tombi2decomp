// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// AS gnu
// Source: psyz (github.com/Xeeynamo/psyz, MIT) decomp/src/libspu/spu.c, function _spu_init.
#include "common.h"
extern char D_80010A44[];
extern char D_80010A54[];
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
extern volatile u16 D_8003C308[10];
extern union SpuUnion* _spu_RXX;
extern int _spu_inTransfer;
extern s32 _spu_mem_mode_plus;
extern s32 D_80026DB8;
extern s32 _spu_transMode;
extern u16 _spu_tsa;
extern void (* volatile _spu_transferCallback)();
extern void (* volatile _spu_IRQCallback)();
void _spu_writeByIO(unsigned char* addr, u_long size);
void _spu_Fw1ts(void);
extern union SpuUnion* _spu_RXX;
extern volatile unsigned* dma_dpcr;
extern u16 _spu_tsa;
extern int _spu_transMode;
extern int D_80026DA8;
extern int D_80026DAC;
extern int _spu_mem_mode_plus;
extern int D_80026DB4;
extern int D_80026DB8;
extern int _spu_inTransfer;
extern void (* volatile _spu_transferCallback)();
extern void (* volatile _spu_IRQCallback)();
extern s8 D_80026DC8[16];
void _spu_writeByIO(unsigned char* addr, u_long size);
void _spu_Fw1ts(void);

int _spu_init(int bHot) {
    unsigned dmaTimer;
    int i;
    *dma_dpcr |= (3 << 16) | (1 << 19);
    _spu_RXX->rxx.main_vol.left = (0);
    _spu_RXX->rxx.main_vol.right = (0);
    _spu_RXX->rxx.spucnt = (0);
    _spu_transMode = 0;
    D_80026DA8 = 0;
    _spu_tsa = 0;
    _spu_Fw1ts();
    _spu_RXX->rxx.main_vol.left = (0);
    _spu_RXX->rxx.main_vol.right = (0);
    dmaTimer = 0;
    while ((_spu_RXX->rxx.spustat) & 0x7FF) {
        if (++dmaTimer > (0xF00U)) {
            printf(D_80010A44, D_80010A54);
            break;
        }
    }
    D_80026DAC = 2;
    _spu_mem_mode_plus = 3;
    D_80026DB4 = 8;
    D_80026DB8 = 7;
    _spu_RXX->rxx.data_trans = (4);
    _spu_RXX->rxx.rev_vol.left = (0);
    _spu_RXX->rxx.rev_vol.right = (0);
    _spu_RXX->rxx.key_off[0] = (0xFFFF);
    _spu_RXX->rxx.key_off[1] = (0xFFFF);
    _spu_RXX->rxx.rev_mode[0] = (0);
    _spu_RXX->rxx.rev_mode[1] = (0);
    for (i = 0; i < 10; i++) {
        D_8003C308[i] = 0;
    }
    if (!bHot) {
        _spu_RXX->rxx.chan_fm[0] = (0);
        _spu_RXX->rxx.chan_fm[1] = (0);
        _spu_RXX->rxx.noise_mode[0] = (0);
        _spu_RXX->rxx.noise_mode[1] = (0);
        _spu_RXX->rxx.cd_vol.left = (0);
        _spu_RXX->rxx.cd_vol.right = (0);
        _spu_RXX->rxx.ex_vol.left = (0);
        _spu_RXX->rxx.ex_vol.right = (0);
        _spu_tsa = 0x200;
        _spu_writeByIO((unsigned char*)&D_80026DC8, ((s32)(sizeof(D_80026DC8) / sizeof(*(D_80026DC8)))));
        for (i = 0; i < 24; i++) {
            _spu_RXX->rxx.voice[i].volume.left = (0);
            _spu_RXX->rxx.voice[i].volume.right = (0);
            _spu_RXX->rxx.voice[i].pitch = (0x3fff);
            _spu_RXX->rxx.voice[i].addr = (0x200);
            _spu_RXX->rxx.voice[i].adsr[0] = (0);
            _spu_RXX->rxx.voice[i].adsr[1] = (0);
        }
        _spu_RXX->rxx.key_on[0] = (0xFFFF);
        _spu_RXX->rxx.key_on[1] = (0xFF);
        _spu_Fw1ts();
        _spu_Fw1ts();
        _spu_Fw1ts();
        _spu_Fw1ts();
        _spu_RXX->rxx.key_off[0] = (0xFFFF);
        _spu_RXX->rxx.key_off[1] = (0xFF);
        _spu_Fw1ts();
        _spu_Fw1ts();
        _spu_Fw1ts();
        _spu_Fw1ts();
    }
    _spu_RXX->rxx.spucnt = ((1 << 14) | (1 << 15));
    _spu_inTransfer = 1;
    _spu_transferCallback = 0;
    _spu_IRQCallback = 0;
    return 0;
}

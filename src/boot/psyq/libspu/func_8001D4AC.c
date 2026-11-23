// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// AS gnu
// Source: psyz (github.com/Xeeynamo/psyz, MIT) decomp/src/libspu/spu.c, function _spu_FwriteByIO (gcc 2.7.2: loops as guarded do/while, the inner guard `n > 0`).
#include "common.h"
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
extern u16 _spu_tsa;
extern void (* volatile _spu_transferCallback)();
extern void (* volatile _spu_IRQCallback)();
void _spu_Fw1ts(void);
extern union SpuUnion* _spu_RXX;
extern u16 _spu_tsa;
extern void (* volatile _spu_transferCallback)();
extern void (* volatile _spu_IRQCallback)();
extern char D_80010A44[];
extern char D_80010A64[];
extern char D_80010A78[];
void _spu_Fw1ts(void);

void func_8001D4AC(unsigned char* addr, u_long size) {
    unsigned short spustat;
    int num_to_trans;
    unsigned short* cur_pos;
    int spustat_cur;
    int i;
    unsigned short cnt;
    unsigned timeout;
    cur_pos = (unsigned short*)addr;
    spustat = (_spu_RXX->rxx.spustat) & 0x7FF;
    _spu_RXX->rxx.trans_addr = (_spu_tsa);
    _spu_Fw1ts();
    if (size != 0) do {
        num_to_trans = (size > 0x40) ? 0x40 : size;
        i = 0;
        if (num_to_trans > 0) do {
            _spu_RXX->rxx.trans_fifo = (*cur_pos++);
            i += 2;
        } while (i < num_to_trans);
        cnt = (_spu_RXX->rxx.spucnt);
        _spu_RXX->rxx.spucnt = (cnt & ~0x30) | 0x10;
        _spu_Fw1ts();
        timeout = 0;
        if ((_spu_RXX->rxx.spustat) & 0x400) do {
            timeout++;
            if (timeout > 0xF00) {
                printf(D_80010A44, D_80010A64);
                break;
            }
        } while ((_spu_RXX->rxx.spustat) & 0x400);
        _spu_Fw1ts();
        _spu_Fw1ts();
        size -= num_to_trans;
    } while (size != 0);
    cnt = (_spu_RXX->rxx.spucnt);
    _spu_RXX->rxx.spucnt = cnt & ~0x30;
    timeout = 0;
    spustat_cur = (_spu_RXX->rxx.spustat) & 0x7FF;
    if (spustat_cur != spustat) do {
        timeout++;
        if (timeout > 0xF00) {
            printf(D_80010A44, D_80010A78);
            return;
        }
        spustat_cur = (_spu_RXX->rxx.spustat) & 0x7FF;
    } while (spustat_cur != spustat);
}

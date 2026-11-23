// CC gcc-2.8.1-nocse
// FLAGS -O2 -G0 -mno-split-addresses
// AS gnu
#include "common.h"
typedef unsigned int size_t;
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
extern long SpuClearReverbWorkArea (long mode);
struct rev_param_entry {
    u32 flags;
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
};
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
extern s32 _spu_rev_offsetaddr;
extern struct rev_param_entry D_800ACBC4[];
extern s32 D_800ACB94[];
extern SpuReverbAttr _spu_rev_attr;
extern void (* volatile _spu_transferCallback)();
extern void (* volatile _spu_IRQCallback)();
int _SpuIsInAllocateArea_(unsigned);
void _spu_FsetRXX(unsigned offset, unsigned value, unsigned mode);
void _spu_setReverbAttr(struct rev_param_entry* attr);
static inline void copyReverbEntry(char* dst, char* src, size_t size) {
    while (size--) {
        *dst++ = *src++;
    }
}

long SpuSetReverbModeParam(SpuReverbAttr* attr0) {
    SpuReverbAttr *attr = attr0;
    struct rev_param_entry entry;
    u32 mode;
    u16 cnt;
    int wasEnabled = 0;
    int setMode = 0;
    int setDelay = 0;
    int clearWorkArea = 0;
    int setFeedback = 0;
    u32 mask = attr->mask;
    s32 *sa;
    int setAll = attr->mask == 0;
    entry.flags = 0;
    if (setAll || mask & (0x01 << 0)) {
        mode = attr->mode;
        if (attr->mode & 0x100) {
            mode &= ~0x100;
            clearWorkArea = 1;
        }
        if (mode >= 10 ||
            _SpuIsInAllocateArea_(*(s32 *)((u8 *)D_800ACB94 + mode * 4))) {
            return -1;
        }
        sa = D_800ACB94;
        setMode = 1;
        _spu_rev_attr.mode = mode;
        _spu_rev_offsetaddr = sa[_spu_rev_attr.mode];
        copyReverbEntry(
            (char*)&entry, (char*)&D_800ACBC4[_spu_rev_attr.mode],
            sizeof(struct rev_param_entry));
        switch (_spu_rev_attr.mode) {
        case 7:
            _spu_rev_attr.feedback = 0x7F;
            _spu_rev_attr.delay = 0x7F;
            break;
        case 8:
            _spu_rev_attr.feedback = 0;
            _spu_rev_attr.delay = 0x7F;
            break;
        default:
            _spu_rev_attr.feedback = 0;
            _spu_rev_attr.delay = 0;
            break;
        }
    }
    if (setAll || mask & (0x01 << 3)) {
        switch (_spu_rev_attr.mode) {
        case 7:
        case 8:
            setDelay = 1;
            if (!setMode) {
                copyReverbEntry(
                    (char*)&entry, (char*)&D_800ACBC4[_spu_rev_attr.mode],
                    sizeof(struct rev_param_entry));
                entry.flags = (1u << 10) | (1u << 11) |
                              (1u << 12) | (1u << 16) |
                              (1u << 26) | (1u << 27);
            }
            _spu_rev_attr.delay = attr->delay;
            entry.mLSAME = ((_spu_rev_attr.delay << 13) / 0x7F) - entry.dAPF1;
            entry.mRSAME = ((_spu_rev_attr.delay << 12) / 0x7F) - entry.dAPF2;
            entry.mLCOMB1 =
                ((_spu_rev_attr.delay << 12) / 0x7F) + entry.mRCOMB1;
            entry.dLSAME = ((_spu_rev_attr.delay << 12) / 0x7F) + entry.dRSAME;
            entry.mLAPF1 = ((_spu_rev_attr.delay << 12) / 0x7F) + entry.mLAPF2;
            entry.mRAPF1 = ((_spu_rev_attr.delay << 12) / 0x7F) + entry.mRAPF2;
            break;
        }
    }
    if (setAll || mask & (0x01 << 4)) {
        switch (_spu_rev_attr.mode) {
        case 7:
        case 8:
            setFeedback = 1;
            if (!setMode) {
                if (!setDelay) {
                    copyReverbEntry((char*)&entry,
                                    (char*)&D_800ACBC4[_spu_rev_attr.mode],
                                    sizeof(struct rev_param_entry));
                    entry.flags = (1u << 7);
                } else {
                    entry.flags |= (1u << 7);
                }
            }
            _spu_rev_attr.feedback = attr->feedback;
            entry.vWALL = (_spu_rev_attr.feedback * 0x8100) / 0x7F;
            break;
        }
    }
    if (setMode) {
        wasEnabled = ((_spu_RXX->rxx.spucnt) >> 7) & 1;
        if (wasEnabled) {
            cnt = (_spu_RXX->rxx.spucnt);
            cnt &= ~0x80;
            _spu_RXX->rxx.spucnt = (cnt);
        }
    }
    if (!setMode) {
        if (setAll || mask & (0x01 << 1)) {
            _spu_RXX->rxx.rev_vol.left = (attr->depth.left);
            _spu_rev_attr.depth.left = attr->depth.left;
        }
        if (setAll || mask & (0x01 << 2)) {
            _spu_RXX->rxx.rev_vol.right = (attr->depth.right);
            _spu_rev_attr.depth.right = attr->depth.right;
        }
    } else {
        _spu_RXX->rxx.rev_vol.left = (0);
        _spu_RXX->rxx.rev_vol.right = (0);
        _spu_rev_attr.depth.left = 0;
        _spu_rev_attr.depth.right = 0;
    }
    if (setMode || setDelay || setFeedback) {
        _spu_setReverbAttr(&entry);
    }
    if (clearWorkArea) {
        SpuClearReverbWorkArea(_spu_rev_attr.mode);
    }
    if (setMode) {
        _spu_FsetRXX(0xD1, _spu_rev_offsetaddr, 0);
        if (wasEnabled) {
            cnt = (_spu_RXX->rxx.spucnt);
            cnt |= 0x80;
            _spu_RXX->rxx.spucnt = (cnt);
        }
    }
    return 0;
    __asm__ volatile("");
}

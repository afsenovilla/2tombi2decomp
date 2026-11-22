// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// AS gnu
// Source: psyz (github.com/Xeeynamo/psyz, MIT) decomp/src/libsnd/vm_nowof.c, function _SsVmKeyOffNow.
#include "common.h"
extern void (* volatile _spu_transferCallback)();
extern void (* volatile _spu_IRQCallback)();
struct SpuVoice {
    s16 vag_idx;
    s16 unk2;
    s16 unk04;
    u16 key_stat;
    s16 voll1;
    char pan;
    char unkb;
    s16 note;
    s16 seq_sep_no;
    s16 fake_program;
    s16 prog;
    s16 tone;
    s16 vabId;
    s16 priority;
    s16 unk1a;
    u8 pad4[1];
    u8 unk1b;
    s16 auto_vol;
    s16 unk1e;
    s16 unk20;
    s16 unk22;
    s16 start_vol;
    s16 end_vol;
    s16 auto_pan;
    s16 unk2a;
    s16 unk2c;
    s16 unk2e;
    s16 start_pan;
    s16 end_pan;
    s16 unk36;
};
struct struct_svm {
    char prog_tones;
    char vabId;
    char note;
    char fine;
    char volume;
    char pan;
    char prog;
    char fake_program;
    char field_8_unknown;
    char field_0x9;
    char mvol;
    char mpan;
    char tone;
    char tone_vol;
    char tone_pan;
    char tone_prior;
    char tone_center;
    unsigned char tone_shift;
    char tone_min;
    char tone_max;
    u8 tone_mode;
    u8 pad;
                          short seq_sep_no;
    short tone_vag_idx;
    short voice;
    short voiceOffset;
    short field_0x1e;
};
extern struct struct_svm D_80105CF6;
extern unsigned short D_801054B8;
extern unsigned short D_801054BA;
extern unsigned short D_80105BF0;
extern unsigned short D_80105BF2;
extern struct SpuVoice D_801054C8[24];

void _SsVmKeyOffNow(int mode) {
    int bitsUpper;
    int bitsLower;
    u16 voice;
    voice = D_80105CF6.voice;
    if (voice < 16) {
        bitsLower = 1 << voice;
        bitsUpper = 0;
    } else {
        bitsLower = 0;
        bitsUpper = 1 << (voice - 16);
    }
    D_801054C8[voice].unk1b = 0;
    D_801054C8[voice].unk04 = 0;
    D_801054C8[voice].vag_idx = 0;
    D_80105BF0 |= bitsLower;
    D_80105BF2 |= bitsUpper;
    D_801054B8 &= ~D_80105BF0;
    D_801054BA &= ~D_80105BF2;
}

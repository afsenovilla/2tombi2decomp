// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// AS gnu
// Source: psy-q-decomp (github.com/sozud/psy-q-decomp, MIT) src/snd/ut_sva.c, function SsUtSetVagAtr.
#include "common.h"
typedef struct VagAtr {
 unsigned char prior;
 unsigned char mode;
 unsigned char vol;
 unsigned char pan;
 unsigned char center;
 unsigned char shift;
 unsigned char min;
 unsigned char max;
 unsigned char vibW;
 unsigned char vibT;
 unsigned char porW;
 unsigned char porT;
 unsigned char pbmin;
 unsigned char pbmax;
 unsigned char reserved1;
 unsigned char reserved2;
 unsigned short adsr1;
 unsigned short adsr2;
 short prog;
 short vag;
 short reserved[4];
} VagAtr;
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
extern u8 _svm_vab_used[16];
extern struct struct_svm D_80105CF8;
extern VagAtr* D_80105CE8;
int _SsVmVSetUp(short vabId, short prog);

s16 SsUtSetVagAtr(s16 vabId, s16 progNum, s16 toneNum, VagAtr* vagatrptr) {
    s16 tone;
    if (_svm_vab_used[vabId] == 1) {
        _SsVmVSetUp(vabId, progNum);
        tone = toneNum + (s8)D_80105CF8.fake_program * 16;
        D_80105CE8[tone].prior = vagatrptr->prior;
        D_80105CE8[tone].mode = vagatrptr->mode;
        D_80105CE8[tone].vol = vagatrptr->vol;
        D_80105CE8[tone].pan = vagatrptr->pan;
        D_80105CE8[tone].center = vagatrptr->center;
        D_80105CE8[tone].shift = vagatrptr->shift;
        D_80105CE8[tone].max = vagatrptr->max;
        D_80105CE8[tone].min = vagatrptr->min;
        D_80105CE8[tone].vibW = vagatrptr->vibW;
        D_80105CE8[tone].vibT = vagatrptr->vibT;
        D_80105CE8[tone].porW = vagatrptr->porW;
        D_80105CE8[tone].porT = vagatrptr->porT;
        D_80105CE8[tone].pbmin = vagatrptr->pbmin;
        D_80105CE8[tone].pbmax = vagatrptr->pbmax;
        D_80105CE8[tone].adsr1 = vagatrptr->adsr1;
        D_80105CE8[tone].adsr2 = vagatrptr->adsr2;
        D_80105CE8[tone].prog = vagatrptr->prog;
        D_80105CE8[tone].vag = vagatrptr->vag;
        return 0;
    }
    return -1;
}

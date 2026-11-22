// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// AS gnu
// Source: psyz (github.com/Xeeynamo/psyz, MIT) decomp/src/libsnd/ut_gva.c, function SsUtGetVagAtr.
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
extern struct struct_svm D_80105CF8;
extern u8 _svm_vab_used[16];
extern VagAtr* D_80105CE8;
int _SsVmVSetUp(short vabId, short prog);

short SsUtGetVagAtr(short vabId, short prog, short toneNum, VagAtr* vagatrptr) {
    s16 temp_v1;
    if (_svm_vab_used[vabId] == 1) {
        _SsVmVSetUp(vabId, prog);
        temp_v1 = toneNum + (s8)D_80105CF8.fake_program * 0x10;
        vagatrptr->prior = D_80105CE8[temp_v1].prior;
        vagatrptr->mode = D_80105CE8[temp_v1].mode;
        vagatrptr->vol = D_80105CE8[temp_v1].vol;
        vagatrptr->pan = D_80105CE8[temp_v1].pan;
        vagatrptr->center = D_80105CE8[temp_v1].center;
        vagatrptr->shift = D_80105CE8[temp_v1].shift;
        vagatrptr->max = D_80105CE8[temp_v1].max;
        vagatrptr->min = D_80105CE8[temp_v1].min;
        vagatrptr->vibW = D_80105CE8[temp_v1].vibW;
        vagatrptr->vibT = D_80105CE8[temp_v1].vibT;
        vagatrptr->porW = D_80105CE8[temp_v1].porW;
        vagatrptr->porT = D_80105CE8[temp_v1].porT;
        vagatrptr->pbmin = D_80105CE8[temp_v1].pbmin;
        vagatrptr->pbmax = D_80105CE8[temp_v1].pbmax;
        vagatrptr->adsr1 = D_80105CE8[temp_v1].adsr1;
        vagatrptr->adsr2 = D_80105CE8[temp_v1].adsr2;
        vagatrptr->prog = D_80105CE8[temp_v1].prog;
        vagatrptr->vag = D_80105CE8[temp_v1].vag;
        return 0;
    }
    return -1;
}

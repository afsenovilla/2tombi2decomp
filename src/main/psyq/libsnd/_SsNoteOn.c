// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// AS gnu
// Source: psy-q-decomp (github.com/sozud/psy-q-decomp, MIT) src/snd/midinote.c, function _SsNoteOn.
#include "common.h"
struct SeqStruct {
     u8* seq_ptr;
     u8* read_pos;
     u8* next_sep_pos;
     u8* loop_pos;
     u32 unk10;
     u8 play_mode;
     u8 unk15;
     u8 running_status;
     u8 channel_idx;
     u8 unk18;
     u8 unk19;
     u8 fn_idx;
     u8 unk1B;
     u8 unk1C;
     u8 unk1D;
     u8 unk1E;
     u8 unk1F;
     s8 l_count;
     s8 unk21;
     s8 unk22;
     s8 unk23;
     u8 rhythm_n;
     u8 rhythm_d;
     s8 vab_id;
     u8 panpot[16];
     u8 programs[16];
     u8 unk47;
     short vol_l;
     short vol_r;
     s16 unk4C;
     s16 unk4E;
     s16 resolution;
     s16 unk52;
     s16 unk54;
     s16 unk56;
     u16 voll;
     u16 volr;
     s16 unk5C;
     s16 unk5E;
     short vol[16];
     s16 channel_mute;
     u8 unk82;
     u8 unk83;
     s32 unk84;
     s32 unk88;
     s32 tempo;
     s32 delta_value;
     u32 unk94;
     unsigned int flags;
     int v_time_l;
     int v_time_r;
     u32 unkA4;
     s32 unkA8;
     s32 unkAC;
};
extern struct SeqStruct* D_80104C30[32];
int _SsVmKeyOn(short seq_sep_no, short vabId, short prog, unsigned short note, unsigned short voll, unsigned short volr);
int _SsVmKeyOff(short seq_sep_no, short vabId, short prog, unsigned short note);

void _SsNoteOn(s16 seq_no, s16 sep_no, u8 note, u8 vol) {
    struct SeqStruct* score;
    u8 ch;
    u16 voll;
    u8 pan;
    score = &D_80104C30[seq_no][sep_no];
    ch = score->channel_idx;
    voll = vol;
    pan = score->panpot[ch];
    if (vol != 0) {
        if (((score->channel_mute >> ch) & 1) == 0) {
            _SsVmKeyOn(seq_no | (sep_no << 8), score->vab_id,
                       score->programs[ch], note, voll, pan);
        }
    } else {
        _SsVmKeyOff(seq_no | (sep_no << 8), score->vab_id,
                    score->programs[ch], note);
    }
}

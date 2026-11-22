// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// AS gnu
// Source: psy-q-decomp (github.com/sozud/psy-q-decomp, MIT) src/snd/midiread.c, function _SsSeqGetEof.
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
     u8 vab_id;
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
void _SsVmSeqKeyOff(s16 seq_sep_num);
void _SsSndNextSep(s16, s16);

void _SsSeqGetEof(access_num, seq_num)
short access_num;
short seq_num;
{
    struct SeqStruct* score = &D_80104C30[access_num][seq_num];
    score->unk21++;
    if (score->l_count == 0) {
        score->unk88 = 0;
        score->unk1C = 0;
        score->delta_value = 0;
        if (D_80104C30[access_num][seq_num].flags & 0x400) {
            score->seq_ptr = score->loop_pos;
        } else {
            score->seq_ptr = score->read_pos;
        }
    } else if (score->unk21 < score->l_count) {
        score->unk88 = 0;
        score->unk1C = 0;
        score->delta_value = 0;
        if (D_80104C30[access_num][seq_num].flags & 0x400) {
            score->seq_ptr = score->loop_pos;
            score->next_sep_pos = score->loop_pos;
        } else {
            score->seq_ptr = score->read_pos;
            score->next_sep_pos = score->read_pos;
        }
    } else {
        D_80104C30[access_num][seq_num].flags &= ~1;
        D_80104C30[access_num][seq_num].flags &= ~8;
        D_80104C30[access_num][seq_num].flags &= ~2;
        D_80104C30[access_num][seq_num].flags |= 0x200;
        D_80104C30[access_num][seq_num].flags |= 4;
        score->play_mode = 0;
        if (D_80104C30[access_num][seq_num].flags & 0x400) {
            score->next_sep_pos = score->loop_pos;
        } else {
            score->next_sep_pos = score->read_pos;
        }
        if (score->unk22 != -1) {
            score->play_mode = 0;
            _SsSndNextSep(score->unk22, score->unk23);
            _SsVmSeqKeyOff(access_num | (seq_num << 8));
        }
        _SsVmSeqKeyOff(access_num | (seq_num << 8));
        score->delta_value = score->unk54;
    }
}

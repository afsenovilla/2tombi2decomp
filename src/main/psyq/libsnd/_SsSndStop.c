// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// AS gnu
// Source: psyz (github.com/Xeeynamo/psyz, MIT) decomp/src/libsnd/ssstop.c, function _SsSndStop.
#include "common.h"
extern void (* volatile _spu_transferCallback)();
extern void (* volatile _spu_IRQCallback)();
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
               u8 l_count;
               u8 unk21;
               u8 unk22;
               u8 unk23;
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
void _SsVmDamperOff(void);

void _SsSndStop(short sep_access_num, short seq_num) {
    struct SeqStruct* score;
    int i;
    score = &D_80104C30[sep_access_num][seq_num];
    D_80104C30[sep_access_num][seq_num].flags &= ~1;
    D_80104C30[sep_access_num][seq_num].flags &= ~2;
    D_80104C30[sep_access_num][seq_num].flags &= ~8;
    D_80104C30[sep_access_num][seq_num].flags &= ~0x400;
    D_80104C30[sep_access_num][seq_num].flags |= 4;
    _SsVmSeqKeyOff(sep_access_num | (seq_num << 8));
    _SsVmDamperOff();
    score->play_mode = 0;
    score->unk88 = 0;
    score->unk1C = 0;
    score->unk18 = 0;
    score->unk19 = 0;
    score->unk1E = 0;
    score->fn_idx = 0;
    score->unk1B = 0;
    score->unk1F = 0;
    score->channel_idx = 0;
    score->unk21 = 0;
    score->unk1C = 0;
    score->unk1D = 0;
    score->unk15 = 0;
    score->running_status = 0;
    score->delta_value = score->unk84;
    score->unk94 = score->tempo;
    score->unk54 = score->unk56;
    score->seq_ptr = score->read_pos;
    score->next_sep_pos = score->read_pos;
    for (i = 0; i < 16; i++) {
        score->programs[i] = i;
        score->panpot[i] = 64;
        score->vol[i] = 127;
    }
    score->unk5C = 127;
    score->unk5E = 127;
}

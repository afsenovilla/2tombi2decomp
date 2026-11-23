// CC gcc-2.7.2-loop4
// FLAGS -O2 -G0
// AS gnu
// Source: psyz (github.com/Xeeynamo/psyz, MIT) decomp/src/libsnd/ssclose.c, function _SsClose (the loop as a guarded do/while: 2.7.2 gives a for loop an unused 8-byte frame slot).
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
extern s32 D_80104C28;
extern s16 D_801054B2;
extern struct SeqStruct* D_80104C30[32];
void _SsVmSeqKeyOff(s16 seq_sep_num);
short _SsVmSetSeqVol(
    short seq_sep_no, unsigned short voll, unsigned short volr, short arg3);

void func_8008DC00(s16 seq_sep_num) {
    s32 seq_num;
    _SsVmSetSeqVol(seq_sep_num, 0, 0, 1);
    _SsVmSeqKeyOff(seq_sep_num);
    D_80104C28 &= ~(1 << seq_sep_num);
    seq_num = 0;
    if (D_801054B2 > 0) do {
        D_80104C30[seq_sep_num][seq_num].flags = 0;
        D_80104C30[seq_sep_num][seq_num].unk22 = 0xFF;
        D_80104C30[seq_sep_num][seq_num].unk23 = 0;
        D_80104C30[seq_sep_num][seq_num].vol_l = 0;
        D_80104C30[seq_sep_num][seq_num].vol_r = 0;
        D_80104C30[seq_sep_num][seq_num].v_time_l = 0;
        D_80104C30[seq_sep_num][seq_num].v_time_r = 0;
        D_80104C30[seq_sep_num][seq_num].unk4C = 0;
        D_80104C30[seq_sep_num][seq_num].unkAC = 0;
        D_80104C30[seq_sep_num][seq_num].unkA8 = 0;
        D_80104C30[seq_sep_num][seq_num].unkA4 = 0;
        D_80104C30[seq_sep_num][seq_num].unk4E = 0;
        D_80104C30[seq_sep_num][seq_num].voll = 127;
        D_80104C30[seq_sep_num][seq_num].volr = 127;
        seq_num++;
    } while (seq_num < D_801054B2);
}

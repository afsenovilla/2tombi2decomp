// CC gcc-2.8.1-psx
// FLAGS -O2 -G0 -mno-split-addresses
// AS gnu
// Source: psyz (github.com/Xeeynamo/psyz, MIT) decomp/src/libsnd/miditime.c, function _SsReadDeltaValue.
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

int _SsReadDeltaValue(short seq_access_num, short seq_num) {
    struct SeqStruct* score = &D_80104C30[seq_access_num][seq_num];
    int value;
    unsigned char next;
    int result;
    value = *score->seq_ptr++;
    if (value == 0) {
        result = 0;
        goto end;
    }
    if (value & 0x80) {
        value &= 0x7F;
        do {
            next = *score->seq_ptr++;
            value = (value << 7) + (next & 0x7F);
        } while (next & 0x80);
    }
    result = value * 10;
    score->unk88 += result;
end:
    __asm__ volatile("");
    return result;
}

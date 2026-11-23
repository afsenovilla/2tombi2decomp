// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// AS gnu
// Source: psyz (github.com/Xeeynamo/psyz, MIT) decomp/src/libsnd/sscall.c, function SsSeqCalledTbyT (loops as guarded do/while: gcc 2.7.2 gives a for loop with a variable bound an unused 8-byte frame slot).
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
extern s32 D_80104C24;
extern s32 D_80104C28;
extern s16 D_801054B0;
extern s16 D_801054B2;
extern struct SeqStruct* D_80104C30[32];
void _SsVmFlush(void);
void _SsSndPlay(short, short);
void _SsSndCrescendo(short, short);
void _SsSndTempo(short, short);
void _SsSndPause(short, short);
void _SsSndReplay(short, short);
void _SsSndStop(short, short);

void SsSeqCalledTbyT(void) {
    int seq_index;
    int tIndex;
    int bit;
    if (D_80104C24 == 1) {
        return;
    }
    D_80104C24 = 1;
    _SsVmFlush();
    seq_index = 0;
    if (D_801054B0 > 0) do {
        bit = 1 << seq_index;
        if (!(D_80104C28 & bit)) {
            goto next;
        }
        tIndex = 0;
        if (D_801054B2 > 0) do {
            if (D_80104C30[seq_index][tIndex].flags & 1) {
                _SsSndPlay((short)seq_index, (short)tIndex);
                if (D_80104C30[seq_index][tIndex].flags & 0x10) {
                    _SsSndCrescendo((short)seq_index, (short)tIndex);
                }
                if (D_80104C30[seq_index][tIndex].flags & 0x20) {
                    _SsSndCrescendo((short)seq_index, (short)tIndex);
                }
                if (D_80104C30[seq_index][tIndex].flags & 0x40) {
                    _SsSndTempo((short)seq_index, (short)tIndex);
                }
                if (D_80104C30[seq_index][tIndex].flags & 0x80) {
                    _SsSndTempo((short)seq_index, (short)tIndex);
                }
            }
            if (D_80104C30[seq_index][tIndex].flags & 2) {
                _SsSndPause((short)seq_index, (short)tIndex);
            }
            if (D_80104C30[seq_index][tIndex].flags & 8) {
                _SsSndReplay((short)seq_index, (short)tIndex);
            }
            if (D_80104C30[seq_index][tIndex].flags & 4) {
                _SsSndStop((short)seq_index, (short)tIndex);
                D_80104C30[seq_index][tIndex].flags = 0;
            }
            tIndex++;
        } while (tIndex < D_801054B2);
    next:
        seq_index++;
    } while (seq_index < D_801054B0);
    D_80104C24 = 0;
}

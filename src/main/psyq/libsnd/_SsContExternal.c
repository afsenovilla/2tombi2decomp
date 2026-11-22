// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// AS gnu
#include "common.h"
typedef struct {
    u8 *read_pos;       /* 0x00 */
    u8 pad04[0x10];
    u8 play;            /* 0x14 */
    u8 pad15[2];
    u8 channel;         /* 0x17 */
    u8 rpn1;            /* 0x18 */
    u8 rpn2;            /* 0x19 */
    u8 pad1A[4];
    u8 cnt;             /* 0x1E */
    u8 pad1F;
    u8 loop;            /* 0x20 */
    u8 loop2;           /* 0x21 */
    u8 pad22[4];
    s8 vab_id;          /* 0x26 */
    u8 panpot[16];      /* 0x27 */
    u8 programs[16];    /* 0x37 */
    u8 pad47[0x58 - 0x47];
    s16 lvol;           /* 0x58 */
    s16 rvol;           /* 0x5A */
    u8 pad5C[4];
    u16 vol[16];        /* 0x60 */
    u8 pad80[0x10];
    s32 delta_value;    /* 0x90 */
    u8 pad94[4];
    s32 flags;          /* 0x98 */
    u8 pad9C[0xB0 - 0x9C];
} Seq;
extern Seq *D_80104C30[];
s32 _SsReadDeltaValue(s16, s16);
void SsUtSetReverbDepth(s16, s16);

void _SsContExternal(s16 acc, s16 seq, u8 d) {
    Seq *s = &D_80104C30[acc][seq];
    SsUtSetReverbDepth(d, d);
    s->delta_value = _SsReadDeltaValue(acc, seq);
}

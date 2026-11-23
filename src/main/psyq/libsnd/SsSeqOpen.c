// CC gcc-2.8.1-nocse
// FLAGS -O2 -G0 -mno-split-addresses
// AS gnu
// Source: psyz (github.com/Xeeynamo/psyz, MIT) decomp/src/libsnd/ssopenq.c, function SsSeqOpen (4.4: a bounded for loop over the 32 open bits).
#include "common.h"
typedef unsigned long u_long;
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
typedef void (*anon5312_noteon_t)();
typedef void (*anon5312_programchange_t)();
typedef void (*anon5312_pitchbend_t)();
typedef void (*anon5312_metaevent_t)();
typedef struct {
 anon5312_noteon_t noteon;
 anon5312_programchange_t programchange;
 anon5312_pitchbend_t pitchbend;
 anon5312_metaevent_t metaevent;
 void (*control[13]) ();
 void (*ccentry[20]) ();
} _SsFCALL;
extern void _SsNoteOn (short, short, unsigned char, unsigned char);
extern void _SsSetProgramChange(short, short, unsigned char);
extern void _SsGetMetaEvent(short, short, unsigned char);
extern void _SsSetPitchBend(short, short);
extern void _SsSetControlChange(short, short, unsigned char);
extern void _SsContBankChange(short, short);
extern void _SsContDataEntry(short, short, unsigned char);
extern void _SsContMainVol(short, short, unsigned char);
extern void _SsContPanpot(short, short, unsigned char);
extern void _SsContExpression(short, short, unsigned char);
extern void _SsContDamper(short, short, unsigned char);
extern void _SsContExternal(short, short, unsigned char);
extern void _SsContNrpn1(short, short, unsigned char);
extern void _SsContNrpn2(short, short, unsigned char);
extern void _SsContRpn1(short, short, unsigned char);
extern void _SsContRpn2(short, short, unsigned char);
extern void _SsContResetAll(short, short);
extern void _SsSetNrpnVabAttr0(short, short, short, VagAtr, short, unsigned char);
extern void _SsSetNrpnVabAttr1(short, short, short, VagAtr, short, unsigned char);
extern void _SsSetNrpnVabAttr2(short, short, short, VagAtr, short, unsigned char);
extern void _SsSetNrpnVabAttr3(short, short, short, VagAtr, short, unsigned char);
extern void _SsSetNrpnVabAttr4(short, short, short, VagAtr, short, unsigned char);
extern void _SsSetNrpnVabAttr5(short, short, short, VagAtr, short, unsigned char);
extern void _SsSetNrpnVabAttr6(short, short, short, VagAtr, short, unsigned char);
extern void _SsSetNrpnVabAttr7(short, short, short, VagAtr, short, unsigned char);
extern void _SsSetNrpnVabAttr8(short, short, short, VagAtr, short, unsigned char);
extern void _SsSetNrpnVabAttr9(short, short, short, VagAtr, short, unsigned char);
extern void _SsSetNrpnVabAttr10(short, short, short, VagAtr, short, unsigned char);
extern void _SsSetNrpnVabAttr11(short, short, short, VagAtr, short, unsigned char);
extern void _SsSetNrpnVabAttr12(short, short, short, VagAtr, short, unsigned char);
extern void _SsSetNrpnVabAttr13(short, short, short, VagAtr, short, unsigned char);
extern void _SsSetNrpnVabAttr14(short, short, short, VagAtr, short, unsigned char);
extern void _SsSetNrpnVabAttr15(short, short, short, VagAtr, short, unsigned char);
extern void _SsSetNrpnVabAttr16(short, short, short, VagAtr, short, unsigned char);
extern void D_8008FAD0(short, short, short, VagAtr, short, unsigned char);
extern void D_8008FB00(short, short, short, VagAtr, short, unsigned char);
extern void D_8008FB30(short, short, short, VagAtr, short, unsigned char);
extern _SsFCALL D_80104B90;
extern void (* volatile _spu_transferCallback)();
extern void (* volatile _spu_IRQCallback)();
typedef void (*sCb)();
extern s32 D_80104C28;
extern _SsFCALL D_80104B90;
short _SsInitSoundSeq(short seq_no, short vab_id, u8* addr);
void _SsNoteOn(short a0, short a1, unsigned char a2, unsigned char a3);
void _SsSetProgramChange(short a0, short a1, unsigned char a2);
void _SsGetMetaEvent(short a0, short a1, unsigned char a2);
void _SsSetPitchBend(short a0, short a1);
void _SsSetControlChange(short a0, short a1, unsigned char a2);
void _SsContBankChange(short a0, short a1);
void _SsContDataEntry(short a0, short a1, unsigned char a2);
void _SsContMainVol(short a0, short a1, unsigned char a2);
void _SsContPanpot(short a0, short a1, unsigned char a2);
void _SsContExpression(short a0, short a1, unsigned char a2);
void _SsContDamper(short a0, short a1, unsigned char a2);
void _SsContExternal(short a0, short a1, unsigned char a2);
void _SsContNrpn1(short a0, short a1, unsigned char a2);
void _SsContNrpn2(short a0, short a1, unsigned char a2);
void _SsContRpn1(short a0, short a1, unsigned char a2);
void _SsContRpn2(short a0, short a1, unsigned char a2);
void _SsContResetAll(short a0, short a1);
void _SsSetNrpnVabAttr0(
    short a0, short a1, short a2, VagAtr a3, short a4, unsigned char a5);
void _SsSetNrpnVabAttr1(
    short a0, short a1, short a2, VagAtr a3, short a4, unsigned char a5);
void _SsSetNrpnVabAttr2(
    short a0, short a1, short a2, VagAtr a3, short a4, unsigned char a5);
void _SsSetNrpnVabAttr3(
    short a0, short a1, short a2, VagAtr a3, short a4, unsigned char a5);
void _SsSetNrpnVabAttr4(
    short a0, short a1, short a2, VagAtr a3, short a4, unsigned char a5);
void _SsSetNrpnVabAttr5(
    short a0, short a1, short a2, VagAtr a3, short a4, unsigned char a5);
void _SsSetNrpnVabAttr6(
    short a0, short a1, short a2, VagAtr a3, short a4, unsigned char a5);
void _SsSetNrpnVabAttr7(
    short a0, short a1, short a2, VagAtr a3, short a4, unsigned char a5);
void _SsSetNrpnVabAttr8(
    short a0, short a1, short a2, VagAtr a3, short a4, unsigned char a5);
void _SsSetNrpnVabAttr9(
    short a0, short a1, short a2, VagAtr a3, short a4, unsigned char a5);
void _SsSetNrpnVabAttr10(
    short a0, short a1, short a2, VagAtr a3, short a4, unsigned char a5);
void _SsSetNrpnVabAttr11(
    short a0, short a1, short a2, VagAtr a3, short a4, unsigned char a5);
void _SsSetNrpnVabAttr12(
    short a0, short a1, short a2, VagAtr a3, short a4, unsigned char a5);
void _SsSetNrpnVabAttr13(
    short a0, short a1, short a2, VagAtr a3, short a4, unsigned char a5);
void _SsSetNrpnVabAttr14(
    short a0, short a1, short a2, VagAtr a3, short a4, unsigned char a5);
void _SsSetNrpnVabAttr15(
    short a0, short a1, short a2, VagAtr a3, short a4, unsigned char a5);
void _SsSetNrpnVabAttr16(
    short a0, short a1, short a2, VagAtr a3, short a4, unsigned char a5);
void D_8008FAD0(
    short a0, short a1, short a2, VagAtr a3, short a4, unsigned char a5);
void D_8008FB00(
    short a0, short a1, short a2, VagAtr a3, short a4, unsigned char a5);
void D_8008FB30(
    short a0, short a1, short a2, VagAtr a3, short a4, unsigned char a5);
extern char D_8001C5E0[];

short SsSeqOpen(u_long* addr, short vab_id) {
    int bit; s32 one;
    short flag;
    short ret;
    unsigned char exit_loop;
    u8* seq;
    flag = 0;
    seq = (u8*)addr;
    if (D_80104C28 == -1) {
        printf(D_8001C5E0);
        return -1;
    }
    for (bit = 0; bit < 32; bit++) {
        one = 1;
        if ((D_80104C28 & (one << bit)) == 0) {
            flag = bit;
            break;
        }
    }
    D_80104C28 |= 1 << flag;
    ret = _SsInitSoundSeq(flag, vab_id, seq);
    D_80104B90.noteon = (sCb)_SsNoteOn;
    D_80104B90.programchange = (sCb)_SsSetProgramChange;
    D_80104B90.metaevent = (sCb)_SsGetMetaEvent;
    D_80104B90.pitchbend = (sCb)_SsSetPitchBend;
    D_80104B90.control[0] = (sCb)_SsSetControlChange;
    D_80104B90.control[1] = (sCb)_SsContBankChange;
    D_80104B90.control[3] = (sCb)_SsContMainVol;
    D_80104B90.control[4] = (sCb)_SsContPanpot;
    D_80104B90.control[5] = (sCb)_SsContExpression;
    D_80104B90.control[6] = (sCb)_SsContDamper;
    D_80104B90.control[7] = (sCb)_SsContNrpn1;
    D_80104B90.control[8] = (sCb)_SsContNrpn2;
    D_80104B90.control[9] = (sCb)_SsContRpn1;
    D_80104B90.control[10] = (sCb)_SsContRpn2;
    D_80104B90.control[11] = (sCb)_SsContExternal;
    D_80104B90.control[12] = (sCb)_SsContResetAll;
    D_80104B90.control[2] = (sCb)_SsContDataEntry;
    D_80104B90.ccentry[0] = (sCb)_SsSetNrpnVabAttr0;
    D_80104B90.ccentry[1] = (sCb)_SsSetNrpnVabAttr1;
    D_80104B90.ccentry[2] = (sCb)_SsSetNrpnVabAttr2;
    D_80104B90.ccentry[3] = (sCb)_SsSetNrpnVabAttr3;
    D_80104B90.ccentry[4] = (sCb)_SsSetNrpnVabAttr4;
    D_80104B90.ccentry[5] = (sCb)_SsSetNrpnVabAttr5;
    D_80104B90.ccentry[6] = (sCb)_SsSetNrpnVabAttr6;
    D_80104B90.ccentry[7] = (sCb)_SsSetNrpnVabAttr7;
    D_80104B90.ccentry[8] = (sCb)_SsSetNrpnVabAttr8;
    D_80104B90.ccentry[9] = (sCb)_SsSetNrpnVabAttr9;
    D_80104B90.ccentry[10] = (sCb)_SsSetNrpnVabAttr10;
    D_80104B90.ccentry[11] = (sCb)_SsSetNrpnVabAttr11;
    D_80104B90.ccentry[12] = (sCb)_SsSetNrpnVabAttr12;
    D_80104B90.ccentry[13] = (sCb)_SsSetNrpnVabAttr13;
    D_80104B90.ccentry[14] = (sCb)_SsSetNrpnVabAttr14;
    D_80104B90.ccentry[15] = (sCb)_SsSetNrpnVabAttr15;
    D_80104B90.ccentry[16] = (sCb)_SsSetNrpnVabAttr16;
    D_80104B90.ccentry[17] = (sCb)D_8008FAD0;
    D_80104B90.ccentry[18] = (sCb)D_8008FB00;
    D_80104B90.ccentry[19] = (sCb)D_8008FB30;
    if (ret == -1) {
        return -1;
    }
    return flag;
    __asm__ volatile("");
}

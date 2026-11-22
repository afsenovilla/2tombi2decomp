// CC gcc-2.8.1-psx
// FLAGS -O2 -G0 -mno-split-addresses
// ASPSX 2.79
// EPILOGUE sony
// Source: psx_tomba src/psyq/libsnd/vm_key.c (MIT), cut to this function by tools/ptsrc.py.
#define SKIP_ASM
#include "pt/common.h"
#include "pt/libsnd/libsnd_i.h"
int _SsVmKeyOn(unsigned short seq_sep_no, short vabId, short prog, unsigned short note,
                unsigned short voll, unsigned short pan);
int _SsVmKeyOff(short seq_sep_no, short vabId, short prog, unsigned short note);
void _SsVmKeyOffNow(int mode);
void vmNoiseOff(u8 voice);
extern struct SpuVoice _svm_voice[24];
extern u8 _SsVmSelectToneAndVag(u8* tones, u8* vags);
extern u8 _SsVmAlloc(int mode);
extern void _SsVmDoAllocate(void);
extern void vmNoiseOn(u8 voice);
extern u16 note2pitch(void);
extern void _SsVmKeyOnNow(u8 count, u16 pitch);
int _SsVmKeyOn(unsigned short seq_sep_no, short vabId, short prog, unsigned short note,
                unsigned short voll, unsigned short pan);
int _SsVmKeyOff(short seq_sep_no, short vabId, short prog, unsigned short note);
void _SsVmSeKeyOn(short vabId, short prog, unsigned short note,
                  unsigned short pitch, unsigned short voll,
                  unsigned short volr) {
    unsigned short vol;
    unsigned short pan;

    if (voll == volr) {
        pan = 64;
        vol = voll;
    } else if (volr < voll) {
        vol = voll;
        pan = (volr << 6) / voll;
    } else {
        vol = volr;
        pan = 127 - (voll << 6) / volr;
    }
    _SsVmKeyOn(0x21, vabId, prog, note, vol, pan);
}
void _SsVmSeKeyOff(short vabId, short prog, unsigned short note);
void KeyOnCheck(void);

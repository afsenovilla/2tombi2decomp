// CC gcc-2.8.1-psx
// FLAGS -O2 -G0
// ASPSX 2.79
// Source: psx_tomba src/psyq/libpad/padentry.c (MIT), cut to this function by tools/ptsrc.py.
#define SKIP_ASM
#include "pt/common.h"
#include "pt/libpad/padlocal.h"
void PadChkVsync(void);
void PadStartCom(void);
void PadStopCom(void);
int PadChkMtap(int arg0);
int PadGetState(int channel);
int PadInfoMode(int channel, int mode, int index);
int PadInfoAct(int channel, int index, int field);
int PadInfoComb(int channel, int index0, int index1) {
    padPort *obj;
    PadCombinationRecord *entry;

    obj = _padFuncPort2Info(channel);
    if (index0 < 0) {
        return obj->combinationCount;
    }
    if (index0 >= obj->combinationCount) {
        return 0;
    }
    entry = &obj->combinations[index0];
    if (index1 < 0) {
        return entry->length;
    }
    if (index1 >= entry->length) {
        return 0;
    }
    return entry->data[index1];
}
void PadSetActAlign(int channel, u8 *command);
void PadSetMainMode(int channel, unsigned char byte1, unsigned char byte2);
void PadSetAct(int channel, u8 *payload, int size);

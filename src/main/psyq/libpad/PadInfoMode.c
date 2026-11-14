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
int PadInfoMode(int channel, int mode, int index) {
    padPort *obj;

    obj = _padFuncPort2Info(channel);
    switch (mode) {
    case 1:
        return obj->currentId;
    case 2:
        return obj->currentExtendedId;
    case 3:
        return obj->currentModeIndex;
    case 4:
        if (index < 0) {
            return obj->modeCount;
        }
        if (index < obj->modeCount) {
            return obj->modeTable[index];
        }
        break;
    case 100:
        return obj->frameCounter;
    default:
        return 0;
    }

late_fail:
    return 0;
}
int PadInfoAct(int channel, int index, int field);
int PadInfoComb(int channel, int index0, int index1);
void PadSetActAlign(int channel, u8 *command);
void PadSetMainMode(int channel, unsigned char byte1, unsigned char byte2);
void PadSetAct(int channel, u8 *payload, int size);

// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// AS gnu
// Source: psx_tomba's func_8006AB4C (MIT), cut by tools/ptsrc.py and renamed.
#define SKIP_ASM
#include "pt/common.h"
#include "pt/libpad/padlocal.h"
extern padSio* padportd_sio;
extern int D_800975AC[];
int PadInitDirect(u8 *output0, u8 *output1);
void func_80088C60(padPort *arg0) {
    int count;
    int value;
    char *ptr;

    if (arg0->communicationState != 0) {
        ptr = (char *)arg0->actuatorMap;
        value = 0xFF;
        count = 5;
        arg0->communicationState = 0;
        arg0->sequenceStep = 0;
        arg0->currentExtendedId = 0;
        arg0->fn_14 = 0;
        arg0->fn_18 = 0;
        arg0->modeCount = 0;
        arg0->currentModeIndex = 0;
        arg0->currentExtendedId = 0;
        arg0->actuatorCount = 0;
        arg0->combinationCount = 0;
        arg0->modeTable = 0;
        arg0->capabilities = 0;
        arg0->combinations = 0;

        do {
            *ptr = value;
            count -= 1;
            ptr += 1;
        } while (count >= 0);
    }
}
int func_8006ABB4(int result);
void func_8006ACA8(padPort *obj);
int func_8006ACB8(padPort *arg0, int needsAck);
void func_8006AD74(padPort *port);
int func_8006AFF0(padPort *entry);
padPort *func_8006B028(int value);

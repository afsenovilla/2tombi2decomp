// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// ASPSX 2.86
// Source: psx_tomba src/psyq/libpad/padcmd.c (MIT), cut to this function by tools/ptsrc.py.
#define SKIP_ASM
#include "pt/common.h"
#include "pt/libpad/padlocal.h"
void _padSetAct(padPort *arg0, u8 *arg1, int arg2);
void _padSetCmd(padPort *arg0, unsigned char arg1, u8 *arg2, unsigned char arg3);
void _padSendAtLoadInfo(padPort *arg0)
{
    int state = arg0->sequenceStep;

    switch (state) {
    case 2:
        func_80088A74(arg0);
        break;
    case 3:
        func_80088A88(arg0, arg0->currentModeIndex);
        break;
    case 4:
        func_80088AC8(arg0, arg0->infoRecordIndex);
        break;
    }
}
#define CARD_RESPONSE(obj) \
    (*(unsigned char * volatile *)&(obj)->response_3c)
int _padRecvAtLoadInfo(padPort *obj);
int _padGetActSize(padPort *arg0);
int _padLoadActInfo(padPort *obj, unsigned char *buffer);
void func_80069DA4(padPort *arg0);
int func_80069E4C(padPort *inPort);
int _padSetActAlign(padPort *obj, u8 *command);
void func_8006A128(padPort *arg0);
s32 func_8006A144(padPort *arg0);
int _padSetMainMode(padPort *obj, int byte1, int byte2);
void func_8006A2A4(padPort *arg0);
int func_8006A2F8(padPort *arg0);
void _padCmdParaMode(padPort *obj, unsigned char value);
void func_80088A74(padPort *obj);
void func_80088A88(padPort *obj, unsigned char value);
void func_8006A3AC(padPort *obj, unsigned char value);
void func_80088AC8(padPort *obj, unsigned char value);
void func_8006A3EC(padPort *obj);

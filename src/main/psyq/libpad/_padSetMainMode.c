// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// AS gnu
// Source: psx_tomba src/psyq/libpad/padcmd.c (MIT), cut to this function by tools/ptsrc.py.
#define func_8006A2A4 func_800889A0
#define func_8006A2F8 func_800889F4
#define SKIP_ASM
#include "pt/common.h"
#include "pt/libpad/padlocal.h"
void _padSetAct(padPort *arg0, u8 *arg1, int arg2);
void _padSetCmd(padPort *arg0, unsigned char arg1, u8 *arg2, unsigned char arg3);
void _padSendAtLoadInfo(padPort *arg0);
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
int _padSetMainMode(padPort *obj, int byte1, int byte2) {
    register int compareByte asm("$19");
    register int flag asm("$3");
    register int result;

    compareByte = byte1;
    result = _padFuncChkEng(obj);
    if (result != 0) {
        return 0;
    }

    result = 1;
    asm("" : "=r"(result) : "0"(result));
    flag = 1;
    obj->sequenceStep = flag;
    obj->fn_14 = (void (*)(void *))func_8006A2A4;
    obj->fn_18 = func_8006A2F8;
    obj->requestedModeIndex = byte1;
    obj->requestedModeLock = byte2;
    flag = (compareByte & 0xFF) ^ obj->currentModeIndex;
    flag = (unsigned int)flag < 1;
    obj->modeAlreadySelected = flag;
    return result;
}
void func_8006A2A4(padPort *arg0);
int func_8006A2F8(padPort *arg0);
void _padCmdParaMode(padPort *obj, unsigned char value);
void func_8006A378(padPort *obj);
void func_8006A38C(padPort *obj, unsigned char value);
void func_8006A3AC(padPort *obj, unsigned char value);
void func_8006A3CC(padPort *obj, unsigned char value);
void func_8006A3EC(padPort *obj);

// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// AS gnu
// Source: psx_tomba src/psyq/libpad/padcmd.c (MIT), cut to this function by tools/ptsrc.py.
#define func_80069DA4 func_8008831C
#define func_80069E4C func_800883C4
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
int _padLoadActInfo(padPort *obj, unsigned char *buffer) {
    int cursor;
    int result;
    int state;
    register int (*processFn)(padPort *);
    int rowCount;
    int columnCount;

    if (buffer == 0) {
        goto return_zero;
    }
    if (obj->capabilities != 0) {
        return 0;
    }
    if (_padFuncChkEng() != 0) {

return_zero:
    return 0;

    }
initialize:
    result = 1;
    asm volatile("" : "=r"(result) : "0"(result));
    state = 4;
    cursor = ((int)buffer + 3) >> 2;
    obj->communicationState = state;
    state = 1;
    obj->sequenceStep = state;
    obj->fn_14 = (void (*)(void *))func_80069DA4;
    asm volatile("" ::: "memory");
    rowCount = obj->modeCount;
        processFn = func_80069E4C;
    obj->fn_18 = processFn;
    asm volatile("" ::: "memory");
    columnCount = obj->actuatorCount;
    asm volatile("" : "=r"(rowCount), "=r"(columnCount), "=r"(result) : "0"(rowCount), "1"(columnCount), "2"(result));

    cursor <<= 2;
    obj->modeTable = (u16 *)cursor;
    obj->infoRecordIndex = 0;
    asm volatile("" ::: "memory");
    cursor += ((rowCount + 1) >> 1) * 4;
    obj->capabilities = (PadCapabilityRecord *)cursor;
    cursor += (columnCount * 5 + 3) & 0xFFC;
    obj->combinations = (PadCombinationRecord *)cursor;
    return result;
}
void func_80069DA4(padPort *arg0);
int func_80069E4C(padPort *inPort);
int _padSetActAlign(padPort *obj, u8 *command);
void func_8006A128(padPort *arg0);
s32 func_8006A144(padPort *arg0);
int _padSetMainMode(padPort *obj, int byte1, int byte2);
void func_8006A2A4(padPort *arg0);
int func_8006A2F8(padPort *arg0);
void _padCmdParaMode(padPort *obj, unsigned char value);
void func_8006A378(padPort *obj);
void func_8006A38C(padPort *obj, unsigned char value);
void func_8006A3AC(padPort *obj, unsigned char value);
void func_8006A3CC(padPort *obj, unsigned char value);
void func_8006A3EC(padPort *obj);

// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// AS gnu
// Source: psx_tomba src/psyq/libpad/padportd.c (MIT), cut to this function by tools/ptsrc.py.
#define D_8009B310 D_80102470
#define D_8009B358 D_801024B8
#define D_8009B3A0 D_80102500
#define func_8006AB4C func_80088C60
#define func_8006ABB4 func_80088CC8
#define func_8006ACA8 func_80088DBC
#define func_8006ACB8 func_80088DCC
#define func_8006AD74 func_80088E88
#define func_8006AFF0 func_80089104
#define func_8006B028 func_8008913C
#define SKIP_ASM
#include "pt/common.h"
#include "pt/libpad/padlocal.h"
extern padSio* padportd_sio;
extern int D_800975AC[];
int PadInitDirect(u8 *output0, u8 *output1) {
    u8 *savedOutput0 = output0;
    u8 *savedOutput1 = output1;
    register padPort *obj asm("$16");
    u8 *table3c;
    u8 *table40;
    int i;
    int fill;
    register u8 **field40 asm("$4");
    u8 *cursor;
    void (*swapCommand)(padPort *);
    padPort *clearObj;
    int count;

    _padIntExec = 0;
    _padModeMtap = 0;
    _padInitDirSeq();

    obj = &D_8009B3A0[0];
    _padFuncNextPort = func_8006ABB4;
    _padFuncClrInfo = func_8006AB4C;
    _padFuncGetTxd = func_8006ACB8;
    _padFuncCurrLimit = func_8006AD74;
    _padFuncPtr2Port = func_8006AFF0;
    _padFuncPort2Info = func_8006B028;
    swapCommand = func_8006ACA8;
    asm volatile("" : "=r"(clearObj) : "0"(obj));
    _padInfoDir = obj;
    _padFuncClrCmdNo = swapCommand;

    bzero(clearObj, sizeof(padPort) * 2);
    i = 0;
    fill = 0xFF;
    field40 = &obj->statusBuffer;
    table40 = D_8009B358;
    table3c = D_8009B310;
    cursor = (u8 *)&obj[0].output_30;
    *(u8 **)cursor = savedOutput0;
    cursor = (u8 *)&obj[1].output_30;
    *(u8 **)cursor = savedOutput1;
    do {
        PADPORT_FROM_STATUS_BUFFER(field40)->subPorts = 0;
        PADPORT_FROM_STATUS_BUFFER(field40)->ownerPort = obj;
        PADPORT_FROM_STATUS_BUFFER(field40)->output_30[0] = fill;
        PADPORT_FROM_STATUS_BUFFER(field40)->output_30[1] = 0;
        PADPORT_FROM_STATUS_BUFFER(field40)->response_3c = table3c;
        *field40 = table40;
        cursor = obj->actuatorMap;
        count = 5;
        do {
            *cursor = fill;
            count--;
            cursor++;
        } while (count >= 0);
        table40 += 0x23;
        table3c += 0x23;
        i++;
        field40 = &PADPORT_FROM_STATUS_BUFFER(field40)[1].statusBuffer;
        obj++;
    } while (i < 2);

    _padSetVsyncParam();
    _padIntExec = 1;
    return 1;
}
void func_8006AB4C(padPort *arg0);
int func_8006ABB4(int result);
void func_8006ACA8(padPort *obj);
int func_8006ACB8(padPort *arg0, int needsAck);
void func_8006AD74(padPort *port);
int func_8006AFF0(padPort *entry);
padPort *func_8006B028(int value);

// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// AS gnu
// Source: psx_tomba's func_8006A144 (MIT), cut by tools/ptsrc.py and renamed.
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
s32 func_80088840(padPort *arg0) {
    s32 i;
    s32 ff;
    u8 *cursor;
    s32 matched;
    s32 remaining;
    s32 written;
    s32 needed;
    register u8 *out asm("$6");
    register s32 limit;

    i = 0;
    if (arg0->actuatorCount != 0) {
        ff = 0xFF;
        do {
            cursor = arg0->requestedActuatorMap;
            matched = 0;
            remaining = 5;
            do {
                if (*cursor++ == i) {
                    matched += 1;
                }
                remaining -= 1;
            } while (remaining >= 0);
            needed = arg0->capabilities[i].payloadBytes;
            cursor = arg0->requestedActuatorMap;
            written = 0;
            if (needed == 0) {
                needed = 1;
            }
            out = (u8 *)arg0;
            do {
                if (*cursor++ == i) {
                    if (matched < needed) {
                        out[OFFSETOF(padPort, actuatorMap)] = ff;
                        matched -= 1;
                    } else {
                        out[OFFSETOF(padPort, actuatorMap)] = i;
                    }
                }
                written += 1;
                out += 1;
            } while (written < 6);
            limit = arg0->actuatorCount;
            i += 1;
        } while (i < limit);
    }
    arg0->sequenceStep = 0xFE;
    return 0;
}
int _padSetMainMode(padPort *obj, int byte1, int byte2);
void func_8006A2A4(padPort *arg0);
int func_8006A2F8(padPort *arg0);
void _padCmdParaMode(padPort *obj, unsigned char value);
void func_8006A378(padPort *obj);
void func_8006A38C(padPort *obj, unsigned char value);
void func_8006A3AC(padPort *obj, unsigned char value);
void func_8006A3CC(padPort *obj, unsigned char value);
void func_8006A3EC(padPort *obj);

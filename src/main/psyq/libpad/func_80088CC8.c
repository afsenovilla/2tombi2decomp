// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// AS gnu
// Source: psx_tomba's func_8006ABB4 (MIT), cut by tools/ptsrc.py and renamed.
#define D_8009B3A0 D_80102500
#define func_8006ACA8 func_80088DBC
#define SKIP_ASM
#include "pt/common.h"
#include "pt/libpad/padlocal.h"
extern padSio* padportd_sio;
extern int D_800975AC[];
int PadInitDirect(u8 *output0, u8 *output1);
void func_8006AB4C(padPort *arg0);
int func_80088CC8(int result) {
    register int callbackResult asm("$5") = result;
    padPort *objects;
    int ignoredResult;
    int *channelResults;
    padPort *obj;
    int index;
    padSio *control;
    int limit;
    int offset;
    int nextResult;
    int cleared;

    objects = &D_8009B3A0[0];
    ignoredResult = -9;
    channelResults = &_padFixResult[0];

    do {
        index = _padSioChan;
        offset = index * sizeof(padPort);
        obj = (padPort *)(offset + (int)objects);

        if (callbackResult != ignoredResult) {
            cleared = callbackResult == 0;
            if (cleared) {
                channelResults[index] = 0;
            } else {
                _dirFailAuto(obj);
                func_8006ACA8(obj);
            }
        }

        asm("" : "=r"(control), "=r"(index) : "0"(padportd_sio), "1"(_padSioChan));
        _padSioState = 0;
        asm volatile("" : : : "memory");
        control->ctrl = 0;
        limit = _padChanStop;
        index += 1;
        _padSioChan = index;
        asm volatile("" : : : "memory");
        if (limit >= index) {
            nextResult = _padInitSioMode(
                (padPort *)((((index << 4) - index) << 4) + (int)objects));
        } else {
            nextResult = 1;
        }
        callbackResult = 0xFFFF;
        asm("" : "=r"(callbackResult) : "0"(callbackResult));
    } while (nextResult == 0);

    return nextResult;
}
void func_8006ACA8(padPort *obj);
int func_8006ACB8(padPort *arg0, int needsAck);
void func_8006AD74(padPort *port);
int func_8006AFF0(padPort *entry);
padPort *func_8006B028(int value);

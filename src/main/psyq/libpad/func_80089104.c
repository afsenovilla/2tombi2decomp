// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// AS gnu
// Source: psx_tomba's func_8006AFF0 (MIT), cut by tools/ptsrc.py and renamed.
#define D_8009B3A0 D_80102500
#define SKIP_ASM
#include "pt/common.h"
#include "pt/libpad/padlocal.h"
extern padSio* padportd_sio;
extern int D_800975AC[];
int PadInitDirect(u8 *output0, u8 *output1);
void func_8006AB4C(padPort *arg0);
int func_8006ABB4(int result);
void func_8006ACA8(padPort *obj);
int func_8006ACB8(padPort *arg0, int needsAck);
void func_8006AD74(padPort *port);
int func_80089104(padPort *entry) {
    padPort *candidate;
    int index;
    int value;

    index = 0;
    value = 0x10;
    candidate = D_8009B3A0;
    for (; index < 2; index++) {
        if (entry == candidate) {
            return value;
        }
        value += 0x10;
        candidate += 1;
    }

    return 0xFF;
}
padPort *func_8006B028(int value);

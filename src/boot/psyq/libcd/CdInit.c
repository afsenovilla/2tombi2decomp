// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// AS gnu
// Source: psyz (github.com/Xeeynamo/psyz, MIT) decomp/src/libcd/event.c, function CdInit (4.4: CdReset and the callback setters inlined).
#include "common.h"
extern void *CD_cbsync;
extern void *CD_cbready;
extern void *D_80026838;
extern s32 D_8002683C;
extern char D_80010554[];
s32 func_80018DBC(void);
void func_80018DF8(void);
void func_80018E20(void);
void func_80018E48(void);
s32 printf(const char *, ...);

int CdInit(void) {
    int i = 4;
    while (func_80018DBC() != 1) {
        if (!i--) {
            printf(D_80010554);
            return 0;
        }
    }
    CD_cbsync = func_80018DF8;
    CD_cbready = func_80018E20;
    D_80026838 = func_80018E48;
    D_8002683C = 0;
    return 1;
}

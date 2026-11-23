// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// AS gnu
// Source: psyz (github.com/Xeeynamo/psyz, MIT) decomp/src/libcd/event.c, function CdInit (4.4: CdReset and the callback setters inlined).
#include "common.h"
extern void *D_800ABFBC;
extern void *D_800ABFC0;
extern void *D_800ABF24;
extern s32 D_800ABF28;
extern char D_8001C0F0[];
s32 func_80089930(void);
void func_8008996C(void);
void func_80089994(void);
void func_800899BC(void);
s32 printf(const char *, ...);

int CdInit(void) {
    int i = 4;
    while (func_80089930() != 1) {
        if (!i--) {
            printf(D_8001C0F0);
            return 0;
        }
    }
    D_800ABFBC = func_8008996C;
    D_800ABFC0 = func_80089994;
    D_800ABF24 = func_800899BC;
    D_800ABF28 = 0;
    return 1;
}

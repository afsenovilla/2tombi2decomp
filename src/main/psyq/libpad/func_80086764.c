// CC gcc-2.8.1-psx
// FLAGS -O2 -G0 -mno-split-addresses
// AS gnu
// EPILOGUE sony
#include "common.h"
typedef struct { volatile s32 stat; volatile s32 mask; } IntrRegs;
extern IntrRegs *D_800ABE98;
extern void (*D_800ABE60)(void);

s32 func_80086764(void) {
    if (D_800ABE98->mask & 1) {
        if (D_800ABE98->stat & 1) {
            if (D_800ABE60 != NULL) {
                D_800ABE60();
            }
            return 1;
        }
    }
    return 0;
}

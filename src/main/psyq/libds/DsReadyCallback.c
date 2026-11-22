// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// ASPSX 2.79
#include "common.h"
extern void *D_8010621C;

void *DsReadyCallback(void *func) {
    void **p = &D_8010621C;
    void *old = *p;
    *p = func;
    return old;
}

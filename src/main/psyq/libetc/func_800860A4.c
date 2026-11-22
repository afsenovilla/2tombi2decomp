// CC gcc-2.8.1-psx
// FLAGS -O2 -G0 -mno-split-addresses
// AS gnu
// Source: psy-q-decomp (github.com/sozud/psy-q-decomp, MIT) src/etc/intr.c, function stopIntr.
#include "common.h"
typedef int jmp_buf[12];
typedef void (*Callback)();
struct intrEnv_t {
    u16 interruptsInitialized;
    u16 inInterrupt;
    Callback handlers[11];
    u16 enabledInterruptsMask;
    u16 savedMask;
    int savedPcr;
    jmp_buf buf;
    s32 stack[1024];
};
typedef struct intrEnv_t intrEnv_t;
extern struct intrEnv_t intr_env;
extern volatile u16* intr_istat;
extern volatile u16* intr_imask;
extern volatile s32* intr_dpcr;

void* func_800860A4() {
    if (intr_env.interruptsInitialized == 0) {
        return (0);
    }
    EnterCriticalSection();
    intr_env.savedMask = *intr_imask;
    intr_env.savedPcr = *intr_dpcr;
    *intr_istat = *intr_imask = 0;
    *intr_dpcr &= 0x77777777;
    ResetEntryInt();
    intr_env.interruptsInitialized = 0;
    return &intr_env;
}

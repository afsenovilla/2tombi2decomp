// CC gcc-2.8.1-psx
// FLAGS -O2 -G0 -mno-split-addresses
// AS gnu
// EPILOGUE sony
// Source: psy-q-decomp (github.com/sozud/psy-q-decomp, MIT) src/api/pad.c, function SetPatchPad.
#include "common.h"
void EnterCriticalSection(void);
void ExitCriticalSection(void);
int SysDeqIntRP(int, void*);
int SysEnqIntRP(int, void*);
typedef int (*anon4938_func2_t)(void);
typedef int (*anon4938_func1_t)(void);
typedef struct {
    void* next;
    anon4938_func2_t func2;
    anon4938_func1_t func1;
    int dummy;
} INTRQ;
extern INTRQ D_80105F18;
int D_8009BE34(void);
int D_8009BE9C(void);
static inline void _SetVsync(void) {
    D_80105F18.func2 = D_8009BE34;
    D_80105F18.func1 = D_8009BE9C;
    D_80105F18.next = 0;
    D_80105F18.dummy = 0;
}
int D_8009BE34(void);
int D_8009BE9C(void);

int func_8009BD84(void) {
    EnterCriticalSection();
    _SetVsync();
    SysDeqIntRP(1, &D_80105F18);
    SysEnqIntRP(1, &D_80105F18);
    ExitCriticalSection();
    return 1;
}

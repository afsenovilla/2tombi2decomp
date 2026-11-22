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
typedef int (*anon635_func2_t)(void);
typedef int (*anon635_func1_t)(void);
typedef struct {
    void* next;
    anon635_func2_t func2;
    anon635_func1_t func1;
    int dummy;
} INTRQ;
extern INTRQ D_80039E30;
int D_80017C00(void);
int D_80017C68(void);
static inline void _SetVsync(void) {
    D_80039E30.func2 = D_80017C00;
    D_80039E30.func1 = D_80017C68;
    D_80039E30.next = 0;
    D_80039E30.dummy = 0;
}
int D_80017C00(void);
int D_80017C68(void);

int func_80017B50(void) {
    EnterCriticalSection();
    _SetVsync();
    SysDeqIntRP(1, &D_80039E30);
    SysEnqIntRP(1, &D_80039E30);
    ExitCriticalSection();
    return 1;
}

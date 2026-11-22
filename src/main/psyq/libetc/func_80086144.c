// CC gcc-2.8.1-psx
// FLAGS -O2 -G0 -mno-split-addresses -fno-delayed-branch
// AS gnu
#include "common.h"
typedef struct { u16 started; u8 pad[0x30]; u16 mask; s32 stat; s32 jb[12]; } IntrEnv;
extern IntrEnv D_800AAD18;
extern u16 *D_800ABDA8;
extern s32 *D_800ABDAC;
void HookEntryInt(s32 *);
void ExitCriticalSection(void);

IntrEnv *func_80086144(void) {
    IntrEnv *e = &D_800AAD18;
    if (e->started != 0) return 0;
    HookEntryInt(e->jb);
    e->started = 1;
    *D_800ABDA8 = e->mask;
    *D_800ABDAC = e->stat;
    ExitCriticalSection();
    return e;
}

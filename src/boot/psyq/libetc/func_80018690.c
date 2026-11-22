// CC gcc-2.8.1-psx
// FLAGS -O2 -G0 -mno-split-addresses -fno-delayed-branch
// AS gnu
#include "common.h"
typedef struct { u16 started; u8 pad[0x30]; u16 mask; s32 stat; s32 jb[12]; } IntrEnv;
extern IntrEnv D_800256EC;
extern u16 *D_8002677C;
extern s32 *D_80026780;
void HookEntryInt(s32 *);
void ExitCriticalSection(void);

IntrEnv *func_80018690(void) {
    IntrEnv *e = &D_800256EC;
    if (e->started != 0) return 0;
    HookEntryInt(e->jb);
    e->started = 1;
    *D_8002677C = e->mask;
    *D_80026780 = e->stat;
    ExitCriticalSection();
    return e;
}

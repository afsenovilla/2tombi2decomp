// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// AS gnu
// Source: psx_tomba's startIntr (MIT), cut by tools/ptsrc.py and renamed.
#define SKIP_ASM
#include "pt/common.h"
#include "psyq/libstamp.h"
#define JB_SP 1
extern int setjmp(jmp_buf);
long long startIntrDMA();
void* startIntrVSync();
void trapIntr();
void memclr(s32* mem, int len);
void memclr(s32* mem, int len);
typedef int jmp_buf[12];
struct Intr {
    u16 initialized;
    u16 inInterrupt;
    void (*handlers[11])();
    u16 enabledMask;
    s16 savedMask;
    s32 savedDpcr;
    jmp_buf env;
    s32 stack[0x400];
};
extern int VSyncCallback(void (*f)());
struct intr {
    const char* ver;
    void (*dma)();
    void (*set)(int arg0, void (*cb)(void));
    int (*start)();
    int (*stop)();
    int (*vsync)(int, void (*f)());
    int (*restart)();
    short* env;
};
int VSyncCallback(void (*func)());
void HookEntryInt(jmp_buf env);
extern const char intr_id[];
void* func_80018200(void);
void (*setIntr(int index, void (*fn)()))();
u16* stopIntr(void);
u16* restartIntr(void);
extern struct Intr intr_env;
extern struct intr intr_table;
extern struct intr* intr_table_ptr;
extern volatile u16* intr_istat;
extern volatile u16* intr_imask;
extern volatile s32* intr_dpcr;
extern s32 intr_timeout;
int ResetCallback(void);
void InterruptCallback(int arg0, void (*cb)(void));
void DMACallback(void);
int VSyncCallback(void (*func)());
int VSyncCallbacks(int n, void (*func)());
int StopCallback(void);
int RestartCallback(void);
int CheckCallback();
int GetIntrMask();
int SetIntrMask(int mask);
void* func_80018200(void) {
    if (intr_env.initialized) {
        return NULL;
    }
    *intr_istat = *intr_imask = 0;
    *intr_dpcr = 0x33333333;
    memclr(&intr_env, sizeof(intr_env) / sizeof(s32));
    if (setjmp(intr_env.env)) {
        trapIntr();
    }
    intr_env.env[JB_SP] = &intr_env.stack[0x3EC];
    HookEntryInt(intr_env.env);
    intr_env.initialized = 1;
    intr_table_ptr->vsync = startIntrVSync();
    intr_table_ptr->dma = startIntrDMA();
    _96_remove();
    ExitCriticalSection();
    return &intr_env.initialized;
}
extern const char intr_id[];
void trapIntr();
void (*setIntr(int index, void (*fn)()))();
u16* stopIntr(void);
u16* restartIntr(void);
void memclr(s32* mem, int len);
#if REGION == REGION_JP
extern const PsyqStamp libapi_stamp SECTION(".text");
#elif REGION == REGION_EU && VERSION == 1 && LANGUAGE != LANGUAGE_NONE
extern const PsyqStamp libapi_stamp SECTION(".text");
#else
extern const PsyqStamp libapi_stamp SECTION(".text");
#endif

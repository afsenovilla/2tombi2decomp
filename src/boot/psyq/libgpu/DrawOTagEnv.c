// CC gcc-2.8.1-psx
// FLAGS -O2 -G0 -mno-split-addresses
// ASPSX 2.79
#include "common.h"
typedef struct { s16 x, y, w, h; } RECT;
typedef struct {
    RECT clip;      /* 0x00 */
    s16 ofs[2];     /* 0x08 */
    RECT tw;        /* 0x0C */
    u16 tpage;      /* 0x14 */
    u8 dtd;         /* 0x16 */
    u8 dfe;         /* 0x17 */
    u8 isbg;        /* 0x18 */
    u8 r0, g0, b0;  /* 0x19 */
    u32 dr_env[16]; /* 0x1C */
} DRAWENV;
typedef struct { u8 version; u8 x1; u8 level; u8 reverse; s16 w; s16 h; u8 pad8[8]; DRAWENV draw; } GEnvT;
extern GEnvT D_80025514;
typedef struct { u8 pad[8]; void (*addque2)(s32, void *, s32, s32); u8 pad2[0x18 - 0xC]; s32 cwc; } GpuCb;
extern GpuCb *D_8002550C;
extern s32 (*D_80025510)();
extern char D_800102F0[];
void func_8001428C(void *, DRAWENV *);
void *memcpy(void *, void *, s32);
typedef struct { unsigned addr : 24; unsigned len : 8; } P_TAG;
#define setaddr(p, _addr) (((P_TAG *)(p))->addr = (u32)(_addr))

void DrawOTagEnv(u32 *p, DRAWENV *env) {
    if (D_80025514.level >= 2) D_80025510(D_800102F0, p, env);
    func_8001428C(&env->dr_env, env);
    setaddr(&env->dr_env, p);
    D_8002550C->addque2(D_8002550C->cwc, &env->dr_env, 0x40, 0);
    memcpy(&D_80025514.draw, env, sizeof(DRAWENV));
}

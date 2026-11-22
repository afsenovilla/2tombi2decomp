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
typedef struct { u8 version; u8 queue; u8 level; u8 reverse; s16 w; s16 h; } GEnvT;
extern GEnvT D_80025514;
typedef struct { u32 tag; u32 code[15]; } DR_ENV;
u32 func_8001451C(s16, s16);
u32 func_800145B4(s16, s16);
u32 func_8001464C(s16, s16);
u32 func_800144FC(s32, s32, u16);
u32 func_80014668(RECT *);
#define CLAMP(a, b, c) (a >= b ? (a > c ? c : a) : b)
#define LOW(x) (*(u32 *)&(x))
#define setlen(p, _len) (((u8 *)(p))[3] = (u8)(_len))
#define setRECT(r, _x, _y, _w, _h) ((r)->x = (_x), (r)->y = (_y), (r)->w = (_w), (r)->h = (_h))

void func_8001428C(DR_ENV *dr_env, DRAWENV *env) {
    DR_ENV *dr;
    RECT rect;
    s32 len = 0;

    dr = dr_env;
    dr->code[0] = func_8001451C(env->clip.x, env->clip.y);
    dr->code[1] = func_800145B4(
        (s32)(((u32)(u16)(env->clip).w + (u32)(u16)(env->clip).x + -1) * 0x10000) >> 0x10,
        (s32)(((u32)(u16)(env->clip).y + (u32)(u16)(env->clip).h + -1) * 0x10000) >> 0x10);
    dr->code[2] = func_8001464C(env->ofs[0], env->ofs[1]);
    dr->code[3] = func_800144FC(env->dfe, env->dtd, env->tpage);
    dr->code[4] = func_80014668(&env->tw);
    dr->code[5] = 0xE6000000;
    len = 7;
    if (env->isbg) {
        setRECT(&rect, env->clip.x, env->clip.y, env->clip.w, env->clip.h);
        rect.w = CLAMP(rect.w, 0, D_80025514.w - 1);
        rect.h = CLAMP(rect.h, 0, D_80025514.h - 1);
        if (rect.x & 0x3F || rect.w & 0x3F) {
            rect.x -= env->ofs[0];
            rect.y -= env->ofs[1];
            (&dr->tag)[len++] = 0x60000000 | (env->b0 << 16) | (env->g0 << 8) | env->r0;
            (&dr->tag)[len++] = LOW(rect.x);
            (&dr->tag)[len++] = LOW(rect.w);
        } else {
            (&dr->tag)[len++] = 0x02000000 | (env->b0 << 16) | (env->g0 << 8) | env->r0;
            (&dr->tag)[len++] = LOW(rect.x);
            (&dr->tag)[len++] = LOW(rect.w);
        }
    }
    setlen(dr, len - 1);
}

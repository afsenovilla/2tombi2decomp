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
s32 GetVideoMode(void);

DRAWENV *SetDefDrawEnv(DRAWENV *env, s32 x, s32 y, s32 w, s32 h) {
    s32 videomode = GetVideoMode();
    env->clip.x = x;
    env->clip.y = y;
    env->clip.w = w;
    env->tw.x = 0;
    env->tw.y = 0;
    env->tw.w = 0;
    env->tw.h = 0;
    env->r0 = 0;
    env->g0 = 0;
    env->b0 = 0;
    env->dtd = 1;
    env->clip.h = h;
    if (videomode != 0) {
        env->dfe = h <= 288;
    } else {
        env->dfe = h <= 256;
    }
    env->ofs[0] = x;
    env->ofs[1] = y;
    env->tpage = 10;
    env->isbg = 0;
    return env;
}

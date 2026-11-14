// CC gcc-2.8.1-psx
// FLAGS -O2 -G0
// ASPSX 2.79
// Source: psx_tomba src/psyq/libgpu/ext.c (MIT), cut to this function by tools/ptsrc.py.
#define SKIP_ASM
#include "pt/common.h"
#include "psyq/libgpu.h"
u_short LoadTPage(u_long* pix, int tp, int abr, int x, int y, int w, int h);
u_short LoadClut(u_long* clut, int x, int y);
u_short LoadClut2(u_long* clut, int x, int y);
DRAWENV* SetDefDrawEnv(DRAWENV* env, int x, int y, int w, int h);
DISPENV* SetDefDispEnv(DISPENV* env, int x, int y, int w, int h) {
    env->disp.x = x;
    env->disp.y = y;
    env->disp.w = w;
    env->disp.h = h;
    env->screen.x = 0;
    env->screen.y = 0;
    env->screen.w = 0;
    env->screen.h = 0;
    env->isrgb24 = 0;
    env->isinter = 0;
    env->pad1 = 0;
    env->pad0 = 0;
    return env;
}

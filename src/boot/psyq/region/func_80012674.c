// CC gcc-2.8.1-nocse
// FLAGS -O2 -G0 -mno-split-addresses -fno-builtin
// AS gnu
// RETURN sony
// Unidentified licensed-region boot module [0x80011A0C, 0x80012D2C): BIOS region byte check and a message screen
// (Krom2RawAdd / libgpu), built with the library compiler; not a known Psy-Q library (no signature covers it).
#include "psyq_all.h"

typedef struct {
    u16 unk0;
    u8 h;
    u8 pad;
    s16 x;
    s16 y;
    char *text;
} RegionMsg;
extern RegionMsg D_8002545C[];
extern s32 D_800384A4;
extern volatile s16 D_1F801DAA;
void func_800127E0(char *text, RECT *r, s32 color);
void func_80012B9C(void);
extern void exit();

void func_80012674(void)
{
    DRAWENV draw;
    DISPENV disp;
    DR_ENV env;
    u32 mask[3];
    RECT r;
    s32 i;
    s32 c;

    ResetGraph(1);
    StopCallback();
    ResetGraph(5);
    D_1F801DAA = 0;
    SetDefDrawEnv(&draw, 0, 0, 320, 240);
    SetDefDispEnv(&disp, 0, 0, 320, 240);
    draw.isbg = 1;
    SetDrawEnv(&env, &draw);
    DrawPrim(&env);
    PutDispEnv(&disp);
    mask[0] = 0x02000000;
    mask[1] = 0xE6000002;
    mask[2] = 0;
    DrawPrim(mask);
    c = 0xFFFF;
    r.h = 1;
    r.w = D_8002545C[D_800384A4].h;
    for (i = 0; i < 2; i++) {
        r.x = D_8002545C[D_800384A4].x + i;
        r.y = D_8002545C[D_800384A4].y + i;
        func_800127E0(D_8002545C[D_800384A4].text, &r, c);
        c = 0x8000;
    }
    func_80012B9C();
    SetDispMask(1);
    exit();
}

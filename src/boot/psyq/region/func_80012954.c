// CC gcc-2.8.1-psx
// FLAGS -O2 -G0 -mno-split-addresses
// AS gnu
// RETURN sony
// Unidentified licensed-region boot module: draws one 15-row 1-bit glyph row (text cell) twice with DrawPrim.
#include "common.h"
typedef struct {
    s16 x, y, w, h;
} RECT;
typedef struct {
    u8 bpr;
    u8 pad1;
    u8 w;
    u8 pad3;
    s16 x;
    s16 y;
    char *text;
} RegionMsg;
typedef struct {
    u32 tag;
    u32 code;
    u32 xy;
    u32 wh;
    u16 pix[16];
} Glyph;
extern RegionMsg D_8002545C[];
extern s32 D_800384A4;
void DrawPrim(void *p);

// Unidentified licensed-region boot module [0x80011A0C, 0x80012D2C): BIOS region byte check and a message screen
// (Krom2RawAdd / libgpu), built with the library compiler; not a known Psy-Q library (no signature covers it).

void func_80012954(RECT *r, u8 *font, s32 color, u32 ext)
{
    s32 c = color;
    u16 hi = ext;
    Glyph g;
    s32 x0;
    s32 y0;
    u16 lo = ext >> 16;
    s32 row;
    s32 j;
    s32 b;
    u16 *d;

    x0 = r->x;
    y0 = r->y;
    g.tag = (((r->w + 1) >> 1) + 3) << 24;
    g.code = 0xA0000000;
    g.wh = *(u32 *)&r->w;
    for (row = 0; row < 15; row++) {
        d = g.pix;
        for (j = 0; j < D_8002545C[D_800384A4].bpr; j++, font++) {
            for (b = hi; b >= (u16)lo; b--) {
                *d++ = ((*font >> b) & 1) ? c : 0;
            }
        }
        for (j = 0; j < 2; j++) {
            g.xy = *(u32 *)&r->x;
            DrawPrim(&g);
            r->x++;
        }
        r->x = x0;
        r->y++;
    }
    r->y = y0;
}

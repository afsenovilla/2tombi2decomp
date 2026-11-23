// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// AS gnu
#include "common.h"
typedef struct {
    u32 tag;
    u32 code;
    s16 x0, y0;
    s16 x1, y1;
    s16 x2, y2;
    s16 x3, y3;
} PolyF4;
typedef struct { s8 p[4][2]; } Pts;
extern Pts D_80010134;
extern u8 D_80025474[][2];
void DrawPrim(void *p);

// Unidentified licensed-region boot module [0x80011A0C, 0x80012D2C): BIOS region byte check and a message screen
// (Krom2RawAdd / libgpu), built with the library compiler; not a known Psy-Q library (no signature covers it).

void func_80012B9C(void)
{
    PolyF4 poly;
    s32 k;
    s32 i;
    s32 j;
    s32 v;
    s32 c;
    u32 *xy;

    poly.tag = 0x05000000;
    poly.code = 0x280000FF;
    for (k = 0; k < 16; k++) {
        for (i = 0; i < 4; i++) {
            Pts pts = D_80010134;
            xy = (u32 *)&poly;
            for (j = 0; j < 4; j++) {
                c = (j + 2) >> 2;
                v = k + (j & 1);
                xy[j + 2] = ((pts.p[i][1] * D_80025474[16 - v][c] + 0x78) << 16) | (pts.p[i][0] * D_80025474[v][c] + 0xA0);
            }
            DrawPrim(&poly);
        }
    }
    *(u32 *)&poly.x0 = 0x500070;
    *(u32 *)&poly.x1 = 0x480078;
    *(u32 *)&poly.x2 = 0xA800C8;
    *(u32 *)&poly.x3 = 0xA000D0;
    DrawPrim(&poly);
}

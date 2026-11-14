// CC gcc-2.8.1-psx
// FLAGS -O2 -G0
// ASPSX 2.79
// Source: psx_tomba src/psyq/libgpu/prim.c (MIT), cut to this function by tools/ptsrc.py.
#define SKIP_ASM
#include "pt/common.h"
#include "psyq/libgpu.h"
#define CMD_CLEAR_CACHE 0x01000000
#define CMD_COPY_CPU_TO_VRAM 0xA0000000
u_short GetTPage(int tp, int abr, int x, int y);
u_short GetClut(int x, int y);
void DumpTPage(u_short tpage);
void DumpClut(u_short clut);
void* NextPrim(void *p);
int IsEndPrim(void *p);
void AddPrim(void *ot, void *p);
void AddPrims(void *ot, void *p0, void *p1);
void CatPrim(void *p0, void *p1);
void TermPrim(void *p);
void SetSemiTrans(void *p, int abe);
void SetShadeTex(void *p, int tge);
void SetPolyF3(POLY_F3 *p);
void SetPolyFT3(POLY_FT3 *p);
void SetPolyG3(POLY_G3 *p);
void SetPolyGT3(POLY_GT3 *p);
void SetPolyF4(POLY_F4 *p);
void SetPolyFT4(POLY_FT4 *p);
void SetPolyG4(POLY_G4 *p);
void SetPolyGT4(POLY_GT4 *p);
void SetSprt8(SPRT_8 *p);
void SetSprt16(SPRT_16 *p);
void SetSprt(SPRT *p);
void SetTile1(TILE_1 *p);
void SetTile8(TILE_8 *p);
void SetTile16(TILE_16 *p);
void SetTile(TILE *p);
void SetLineF2(LINE_F2 *p);
void SetLineG2(LINE_G2 *p);
void SetLineF3(LINE_F3 *p);
void SetLineG3(LINE_G3 *p);
void SetLineF4(LINE_F4 *p);
void SetLineG4(LINE_G4 *p);
void SetDrawTPage(DR_TPAGE* p, s32 dfe, s32 dtd, s32 tpage);
void SetDrawMove(DR_MOVE* p, RECT* rect, int x, int y) {
    int len = 5;
    if (!rect->w || !rect->h) {
        len = 0;
    }
    setlen(p, len);
    p->code[0] = CMD_CLEAR_CACHE;
    p->code[1] = 0x80000000;
    p->code[2] = *(int*)&rect->x;
    p->code[3] = (y << 0x10) | (x & 0xFFFF);
    p->code[4] = *(int*)&rect->w;
}
void SetDrawLoad(DR_LOAD* p, RECT* rect);
int MargePrim(void* p0, void* p1);
void DumpDrawEnv(DRAWENV* env);
void DumpDispEnv(DISPENV* env);

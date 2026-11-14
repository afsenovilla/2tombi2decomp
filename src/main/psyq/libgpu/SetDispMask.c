// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// AS gnu
// Source: psx_tomba src/psyq/libgpu/sys.c (MIT), cut to this function by tools/ptsrc.py.
extern char D_8001BEC8[];
#define SKIP_ASM
#include "pt/common.h"
#include "psyq/libstamp.h"
#include "psyq/libgpu.h"
#define OT_TYPE u_long
#define CMD_CLEAR_CACHE 0x01000000
#define CMD_COPY_VRAM_TO_CPU 0xC0000000
#define CMD_COPY_CPU_TO_VRAM 0xA0000000
#define CMD_FILL_RECTANGLE_IN_VRAM(color) ((color & 0xFFFFFF) | 0x02000000)
#define CMD_MONOCHROME_RECTANGLE(color) ((color & 0xFFFFFF) | 0x60000000)
#define CLAMP(a, b, c) (a >= b ? (a > c ? c : a) : b)
#define CMPRECT(r1, r2)  (\
    ((volatile RECT*)r1)->x == r2.x && \
    ((volatile RECT*)r1)->y == r2.y && \
    ((volatile RECT*)r1)->w == r2.w && \
    ((volatile RECT*)r1)->h == r2.h\
)
#define TERM_PRIM(ot, p) *ot = (u_long)p & 0xFFFFFF
typedef struct {
      const char* ver; 
      void (*addque)();
      int (*addque2)();
      int (*clr)();
      void (*ctl)(unsigned int);
      int (*cwb)(u32* data, s32 n);
      void (*cwc)();
      int (*drs)();
      int (*dws)();
      int (*exeque)();
      int (*getctl)(int);
      void (*otc)(OT_TYPE* ot, s32 n);
      int (*param)(int);
      int (*reset)(int);
      u_long (*status)(void);
      int (*sync)(int mode);
} GPU;
typedef struct {
    
    
    u_char version;
    u_char D_80090C9D;
    u_char level;
    u_char reverse;
    short w;
    short h;
    u8 unk8[4];
    void (*drawSyncCb)();
    DRAWENV draw;
    DISPENV disp;
} DEBUG;
typedef struct {
    u_long tag;
    u_long code[2];
} DR_PRIO;
typedef struct QueueItem {
    int unk0;
    int unk4;
    int unk8;
    int unkC[2];
    int unk14;
    int unk18;
    char padding[0x14 + 0x1C + 0x14];
} QueueItem;
extern s32 D_8009B148;
extern s32 D_8009B14C;
extern s32 D_8009B150;
extern s32 D_8009B154;
extern s32 D_8009B158;
extern s32 D_8009B15C;
extern s32 D_8009B160;
extern s32 D_8009B164;
extern s32 D_8009B168;
extern s32 D_8009B16C;
extern s32 D_8009B170;
extern s32 D_8009B174;
extern s32 D_8009B178;
extern u8 GPU_CTLBUF[];
extern volatile QueueItem GPU_QITEM[];
extern const char D_80015BA8[];
int printf();
int _status(void);
int _otc(OT_TYPE ot, s32 n);
s32 _clr(RECT* rect, u32 color);
s32 _dws(RECT* arg0, s32* arg1);
s32 _drs(RECT* arg0, s32* arg1);
void _ctl(u32 arg0);
s32 _getctl(s32 arg0);
s32 _cwb(s32* arg0, s32 arg1);
void _cwc(s32 arg0);
s32 _param(s32 arg0);
void _addque(int arg0, int arg1, int arg2);
s32 _addque2(void (*arg0)(s32*, s32), s32* arg1, s32 arg2, s32 arg3);
s32 _exeque(void);
s32 _reset(s32 mode);
s32 _sync(s32 arg0);
extern PsyqStamp libgpu_stamp;
extern GPU _gpucb;
extern GPU* gpu;
extern int (*GPU_printf)();
extern DEBUG GEnv;
extern s32 D_80090D1C[];
extern s32 D_80090D30[];
extern u_long move_image[];
extern u_long D_80090D58[];
extern volatile s32* GPU_DATA;
extern volatile s32* GPU_STATUS;
extern volatile s32* DMA2_MADR;
extern volatile s32* DMA2_BCR;
extern volatile s32* DMA2_CHCR;
extern volatile s32* DMA6_MADR;
extern volatile s32* DMA6_BCR;
extern volatile s32* DMA6_CHCR;
extern volatile s32* DPCR;
extern volatile s32 _qlog;
extern volatile s32 D_80090D94;
extern volatile s32 D_80090D98;
extern s32 D_80090D9C;
extern volatile s32 _qin;
extern volatile s32 _qout;
extern s32 D_80090DA8;
extern s32 D_80090DAC;
extern s32 D_80090DB0;
extern s32 D_80090DB4;
extern s32 D_80090DB8;
int ResetGraph(int mode);
int SetGraphReverse(int mode);
int SetGraphDebug(int level);
int SetGraphQueue(int mode);
u8 GetGraphType(void);
s32 GetGraphDebug(void);
u_long DrawSyncCallback(void (*func)());
void SetDispMask(int mask) {
    if (GEnv.level >= 2) {
        GPU_printf(D_8001BEC8, mask);
    }
    if (mask == 0) {
        GPU_memset(&GEnv.disp, -1, sizeof(DISPENV));
    }
    gpu->ctl(mask ? 0x03000000 : 0x03000001);
}
int DrawSync(int mode);
void checkRECT(const char* log, RECT* r);
int ClearImage(RECT* rect, u8 r, u8 g, u8 b);
int ClearImage2(RECT* rect, u8 r, u8 g, u8 b);
int LoadImage(RECT* rect, u_long* p);
int StoreImage(RECT* rect, u_long* p);
int MoveImage(RECT* rect, s32 x, s32 y);
OT_TYPE* ClearOTag(OT_TYPE* ot, int n);
OT_TYPE* ClearOTagR(OT_TYPE* ot, int n);
void DrawPrim(void* p);
void DrawOTag(u_long* p);
DRAWENV* PutDrawEnv(DRAWENV* env);
void DrawOTagEnv(u_long* p, DRAWENV* env);
DRAWENV* GetDrawEnv(DRAWENV* env);
DISPENV* PutDispEnv(DISPENV* env);
DISPENV* GetDispEnv(DISPENV* env);
int GetODE(void);
void SetTexWindow(DR_TWIN* p, RECT* tw);
void SetDrawArea(DR_AREA* p, RECT* r);
void SetDrawOffset(DR_OFFSET* p, u_short* ofs);
void SetPriority(DR_PRIO* p, int pbc, int pbw);
void SetDrawMode(DR_MODE* p, s32 dfe, s32 dtd, s32 tpage, RECT* tw);
void SetDrawEnv(DR_ENV* dr_env, DRAWENV* env);
int SetDrawEnv2(DR_ENV* dr_env, DRAWENV* env);
u_long get_mode(int dfe, int dtd, u_short tpage);
u_long get_cs(short x, short y);
u_long get_ce(short x, short y);
u_long get_ofs(short x, short y);
u_long get_tw(RECT* rect);
u_long get_dx(DISPENV* env);
int _status(void);
int _otc(OT_TYPE ot, s32 n);
s32 _clr(RECT* rect, u32 color);
s32 _dws(RECT* arg0, s32* arg1);
s32 _drs(RECT* arg0, s32* arg1);
void _ctl(u32 arg0);
s32 _getctl(s32 arg0);
s32 _cwb(s32* arg0, s32 arg1);
void _cwc(s32 arg0);
s32 _param(s32 arg0);
void _addque(int arg0, int arg1, int arg2);
s32 _addque2(void (*arg0)(s32*, s32), s32* arg1, s32 arg2, s32 arg3);
s32 _exeque(void);
s32 _reset(s32 mode);
s32 _sync(s32 arg0);
void set_alarm(void);
s32 get_alarm(void);
int _version(int mode);
void * GPU_memset(s8* ptr, int value, s32 num);

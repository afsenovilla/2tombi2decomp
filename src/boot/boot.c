#include "common.h"
#include "game.h"
#include "m2c.h"

INCLUDE_ASM("asm/boot/nonmatchings/boot", func_80010D54);

INCLUDE_ASM("asm/boot/nonmatchings/boot", func_800111B4);

INCLUDE_ASM("asm/boot/nonmatchings/boot", func_8001138C);

INCLUDE_ASM("asm/boot/nonmatchings/boot", func_80011544);

INCLUDE_ASM("asm/boot/nonmatchings/boot", func_80011654);

extern s32 D_800253E4;
void func_800116CC(s32 arg0, M2C_UNK arg1) {
    s32 temp_s1;

    temp_s1 = D_800253E4;
    DecDCTReset(0);
    DecDCToutCallback(arg1);
    StSetRing(temp_s1 + 0x18000, 0x20);
    StSetStream(0, 1, -1, 0, 0);
    func_80011904(arg0);
}

typedef struct {
    u32 *vlcbuf[2];
    s32 vlcid;
} DecEnvHead;
s32 func_8001174C(DecEnvHead *dec)
{
    s32 cnt = 2000;
    u32 *next;

    while ((next = (u32 *)func_80011864(dec)) == NULL) {
        if (--cnt == 0) {
            return -1;
        }
    }
    dec->vlcid = dec->vlcid ? 0 : 1;
    DecDCTvlc(next, dec->vlcbuf[dec->vlcid]);
    StFreeRing(next);
    return 0;
}

typedef struct {
    s16 x, y, w, h;
} Rect16;
typedef struct {
    u32 *vlcbuf[2];
    s32 vlcid;
    u16 *imgbuf[2];
    s32 imgid;
    Rect16 rect[2];
    s32 rectid;
    Rect16 slice;
    s32 isdone;
} DecEnv;
typedef struct {
    u16 id;
    u16 type;
    u16 secCount;
    u16 nSectors;
    u32 frameCount;
    u32 bsHeadSize;
    u16 width;
    u16 height;
} StHeader;
extern s32 D_800253EC;
void func_800117D0(DecEnv *dec)
{
    volatile u32 cnt = 0x800000;

    while (dec->isdone == 0) {
        if (--cnt == 0) {
            dec->isdone = 1;
            dec->rectid = dec->rectid ? 0 : 1;
            dec->slice.x = dec->rect[dec->rectid].x;
            dec->slice.y = dec->rect[dec->rectid].y;
        }
    }
    dec->isdone = 0;
}

u32 *func_80011864(DecEnv *dec)
{
    u32 *addr;
    StHeader *sector;
    s32 cnt = 2000;

    while (StGetNext(&addr, &sector)) {
        if (--cnt == 0) {
            return 0;
        }
    }
    if (sector->frameCount >= 250) {
        D_800253EC = 1;
    }
    dec->rect[0].w = dec->rect[1].w = sector->width;
    dec->rect[0].h = dec->rect[1].h = sector->height;
    dec->slice.h = sector->height;
    return addr;
}

void func_80011904(u8 *pos)
{
    u8 mode = 0x80;

    do {
        while (CdControl(2, pos, 0) == 0) {
        }
        while (CdControl(0xE, &mode, 0) == 0) {
        }
        VSync(3);
    } while (CdRead2(0x1C0) == 0);
}

typedef struct {
    u32 mode;
    void *crect;
    u32 *caddr;
    void *prect;
    u32 *paddr;
} TimImage;
void func_80011974(u32 *addr)
{
    TimImage t;

    OpenTIM(addr);
    ReadTIM(&t);
    LoadImage(t.prect, t.paddr);
    if (t.mode & 8) {
        LoadImage(t.crect, t.caddr);
    }
    DrawSync(0);
}

extern M2C_UNK D_800253A4;
void func_800119D8(void) {
    _96_init();
    LoadExec(&D_800253A4, 0x80200000, 0);
}

INCLUDE_ASM("asm/boot/nonmatchings/boot", func_80011A0C);

INCLUDE_ASM("asm/boot/nonmatchings/boot", func_80011A78);

INCLUDE_ASM("asm/boot/nonmatchings/boot", func_800123B0);

INCLUDE_ASM("asm/boot/nonmatchings/boot", func_80012584);

INCLUDE_ASM("asm/boot/nonmatchings/boot", func_80012674);

INCLUDE_ASM("asm/boot/nonmatchings/boot", func_800127E0);

INCLUDE_ASM("asm/boot/nonmatchings/boot", func_80012954);

u32 func_80012B08(u8 *p)
{
    u16 lo = 0;
    u16 hi = 7;
    s32 n;
    s32 b;
    s32 first;
    

    for (n = 14; n >= 0; n--) {
        first = 1;
        
        for (b = 7; b >= 0; b--) {
            if ((*p >> b) & 1) {
                if (first != 0) {
                    if (lo < b) {
                        lo = b;
                    }
                    if (b < hi) {
                        hi = b;
                    }
                    first = 0;
                } else if (b < hi) {
                    hi = b;
                }
            }
        }
        p++;
    }
    return (hi << 16) | lo;
}

INCLUDE_ASM("asm/boot/nonmatchings/boot", func_80012B9C);

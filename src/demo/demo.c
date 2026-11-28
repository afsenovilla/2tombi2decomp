#include "common.h"
#include "game.h"
#include "m2c.h"

INCLUDE_ASM("asm/demo/nonmatchings/demo", func_801062E4);

typedef struct { u32 tag; u8 r, g, b, code; s16 x, y; u8 u, v; u16 clut; s16 w, h; } DSprt;
extern u8 *D_800BF544;
extern u32 *D_800ED8C8;
void func_80106690(void)
{
    DSprt *s;
    u32 *m;

    s = (DSprt *)D_800BF544;
    D_800BF544 = (u8 *)(s + 1);
    s->code = 0x65;
    s->x = 0;
    s->y = -8;
    s->u = 0;
    s->v = 0;
    s->w = 0x100;
    s->h = 0xF0;
    s->clut = 0x7FE8;
    do {
        s->tag = D_800ED8C8[0x7FF] | 0x04000000;
        D_800ED8C8[0x7FF] = (u32)s;
    } while (0);
    m = (u32 *)D_800BF544;
    D_800BF544 = (u8 *)(m + 3);
    func_80083DE0(m, 0, 0, 0x9A, 0);
    do {
        u32 *ot = D_800ED8C8;
        *m = ot[0x7FF] | 0x02000000;
        ot[0x7FF] = (u32)m;
    } while (0);
    s = (DSprt *)D_800BF544;
    D_800BF544 = (u8 *)(s + 1);
    s->code = 0x65;
    s->x = 0x100;
    s->y = -8;
    s->u = 0;
    s->v = 0;
    s->w = 0x40;
    s->h = 0xF0;
    s->clut = 0x7FE8;
    do {
        s->tag = D_800ED8C8[0x7FF] | 0x04000000;
        D_800ED8C8[0x7FF] = (u32)s;
    } while (0);
    m = (u32 *)D_800BF544;
    D_800BF544 = (u8 *)(m + 3);
    func_80083DE0(m, 0, 0, 0x9C, 0);
    do {
        u32 *ot = D_800ED8C8;
        *m = ot[0x7FF] | 0x02000000;
        ot[0x7FF] = (u32)m;
    } while (0);
}

INCLUDE_ASM("asm/demo/nonmatchings/demo", func_80106824);

INCLUDE_ASM("asm/demo/nonmatchings/demo", func_8010696C);

INCLUDE_ASM("asm/demo/nonmatchings/demo", func_80106AC4);

INCLUDE_ASM("asm/demo/nonmatchings/demo", func_80106C24);

extern u16 D_1F80017C;
extern u8 D_1F800136;
void func_80106E28(void)
{
    D_1F80017C++;
    if (D_1F800136 == 0) {
        func_80059D28();
        func_80069B28();
        func_80026368();
        func_8007A904();
        func_80025588();
        func_8004FE84();
        func_80026C88();
        func_80022A80();
        func_8006EC44();
        func_80050DE4();
        func_8001CAC0();
    }
    if (D_1F800136 < 2) {
        func_8003F9A8();
    }
    func_80077D8C();
    func_80075A80();
}

void func_80106EE4(void)
{
    D_1F80017C++;
    if (D_1F800136 == 0) {
        func_80026368();
        func_8007A904();
        func_80059D28();
        func_80025588();
        func_8004FE84();
        func_8006EC44();
        func_80050DE4();
    }
    if (D_1F800136 < 2) {
        func_8010B328();
    }
    func_80077D8C();
    func_80075A80();
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
    u32 unk0;
    u8 *buf;
    u32 unk8;
} MovieDef;
extern MovieDef D_80107718[];
extern DecEnv D_1F800000;
extern u8 *D_1F800138;
extern u8 D_1F800135;
extern u8 D_1F80019C;
extern u8 D_1F80019D;
extern s32 D_1F800034;
extern s16 D_800E809C;
extern u8 D_7FFFFF[];
extern char D_80106264[];
extern char D_8010627C[];
extern char D_801062A8[];
void func_801072F4(void);
s32 func_80106F80(s32 idx)
{
    u8 buf[0x18];
    u8 c;
    s32 n;
    u8 *p;
    u16 t;
    u8 *p_f;

    if (D_1F80019D != 0) {
        *(s16 *)(D_1F800138 + 0x4A) = 7;
    }
    switch (*(u16 *)(D_1F800138 + 0x4A)) {
    case 0:
        p = D_1F800138;
        p[0x69] = idx;
        c = 0x80;
        (MEMBER_AT(s16, p, 0x4A))++;
        do {
        } while (func_80089BAC(0xE, &c, 0) == 0);
        break;
    case 1:
    case 2:
    case 3:
        (*(s16 *)(D_1F800138 + 0x4A))++;
        break;
    case 4:
        func_8008B8F0(buf, D_80107718[idx].unk0);
        p_f = D_1F800138;
        t = *(u16 *)(p_f + 0x4A);
        D_1F80019C = 1;
        *(s16 *)(p_f + 0x4A) = t + 1;
        func_80075A30();
        break;
    case 5:
        func_80107400(&D_1F800000, 0, 0, 0, 0x100);
        func_801074BC((s32)buf, (s32)func_801072F4);
        if (func_8010755C(&D_1F800000, (s16)D_80107718[idx].unk8) == -1) {
            func_8009A730(D_80106264);
            *(s16 *)(D_1F800138 + 0x4A) = 7;
            return 0;
        }
        (*(s16 *)(D_1F800138 + 0x4A))++;
    case 6:
        func_8009C784(D_1F800000.vlcbuf[D_1F800000.vlcid], 0);
        func_8009C800(D_1F800000.imgbuf[D_1F800000.imgid], D_1F800000.slice.w * D_1F800000.slice.h / 2);
        if (func_8010755C(&D_1F800000, (s16)D_80107718[idx].unk8) == -1) {
            func_8009A730(D_8010627C);
            *(s16 *)(D_1F800138 + 0x4A) = 7;
        }
        n = 0x800000;
        while (D_1F800000.isdone == 0) {
            if (--n == 0) {
                func_8009A730(D_801062A8);
                D_1F800000.isdone = 1;
                D_1F800000.rectid = D_1F800135;
                D_1F800000.slice.x = D_1F800000.rect[D_1F800000.rectid].x;
                D_1F800000.slice.y = D_1F800000.rect[D_1F800000.rectid].y;
            }
        }        D_1F800034 = 0;
        D_1F80019C = 2;
        *(volatile s16 *)&D_800E809C = 1;
        break;
    case 7:
        func_8001CF00(0);
        func_8009C820(0);
        func_8009C8BC(0);
        func_8008CD40();
        func_8008CCE0();
        do {
        } while (func_80089E1C(9, 0, 0) == 0);
        D_1F80019C = 0;
        D_1F80019D = 0;
        return 1;
    }
    return 0;
}

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
void func_801072F4(void)
{
    Rect16 r;
    s32 id;
    r = D_1F800000.slice;
    id = D_1F800000.imgid;
    D_1F800000.imgid = 1 - id;
    D_1F800000.slice.x += 16;
    if (D_1F800000.slice.x < D_1F800000.rect[D_1F800000.rectid].x + D_1F800000.rect[D_1F800000.rectid].w) {
        func_8009C800(D_1F800000.imgbuf[D_1F800000.imgid], D_1F800000.slice.w * D_1F800000.slice.h / 2);
    } else {
        D_1F800000.isdone = 1;
        D_1F800000.rectid = D_1F800135;
        D_1F800000.slice.x = D_1F800000.rect[D_1F800000.rectid].x;
        D_1F800000.slice.y = D_1F800000.rect[D_1F800000.rectid].y;
    }
    func_80081218(&r, D_1F800000.imgbuf[id]);
}

void func_80107400(DecEnv *d, s16 x0, s16 y0, s16 x1, s16 y1)
{
    u8 *b;
    s32 i;
    b = D_80107718[D_1F800138[0x69]].buf;
    d->vlcid = 0;
    d->imgid = 0;
    d->rect[0].x = x0;
    d->rect[0].y = y0;
    d->rect[1].x = x1;
    d->rect[1].y = y1;
    d->isdone = 0;
    i = 1 - D_1F800135;
    d->vlcbuf[0] = (u32 *)b;
    d->rectid = i;
    d->vlcbuf[1] = (u32 *)(b + 0xA000);
    d->imgbuf[0] = (u16 *)(b + 0x14000);
    d->imgbuf[1] = (u16 *)(b + 0x16000);
    d->slice.x = d->rect[i].x;
    d->slice.y = d->rect[i].y;
    d->slice.w = 0x10;
    d->slice.h = 0xF0;
}

void func_801074BC(s32 a, s32 b)
{
    u8 *buf = D_80107718[D_1F800138[0x69]].buf;

    func_8009C620(0);
    func_8009C8BC(b);
    func_80089870(buf + 0x18000, 0x20);
    func_8008CEB0(0, 1, -1, 0, 0);
    func_801076B0(a);
}

typedef struct {
    u32 *vlcbuf[2];
    s32 vlcid;
} VlcEnv;
s32 func_8010755C(VlcEnv *dec, s32 b)
{
    s32 cnt = 2000;
    u32 *next;

    while ((next = (u32 *)func_801075F8(dec, b)) == NULL) {
        if (--cnt == 0) {
            return -1;
        }
    }
    dec->vlcid = 1 - dec->vlcid;
    func_8009CCE0(next, dec->vlcbuf[dec->vlcid]);
    func_8008CF40(next);
    return 0;
}

u32 *func_801075F8(DecEnv *dec, u32 limit)
{
    u32 *addr;
    StHeader *sector;
    s32 cnt = 2000;

    while (func_8008D030(&addr, &sector)) {
        if (--cnt == 0) {
            return 0;
        }
    }
    if (sector->frameCount >= limit) {
        *(s16 *)(D_1F800138 + 0x4A) = 7;
    }
    dec->rect[0].w = dec->rect[1].w = sector->width;
    dec->rect[0].h = dec->rect[1].h = sector->height;
    dec->slice.h = sector->height;
    return addr;
}

void func_801076B0(s32 a)
{
    s32 n = 0x1C0;

    do {
        while (func_80089BAC(2, a, 0) == 0) {
        }
    } while (func_8008CC30(n) == 0);
}

#include "common.h"
#include "game.h"
#include "m2c.h"

INCLUDE_ASM("asm/demo/nonmatchings/demo", func_801062E4);

INCLUDE_ASM("asm/demo/nonmatchings/demo", func_80106690);

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

INCLUDE_ASM("asm/demo/nonmatchings/demo", func_80106F80);

INCLUDE_ASM("asm/demo/nonmatchings/demo", func_801072F4);

INCLUDE_ASM("asm/demo/nonmatchings/demo", func_80107400);

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
extern u8 *D_1F800138;
typedef struct {
    u32 unk0;
    u8 *buf;
    u32 unk8;
} MovieDef;
extern MovieDef D_80107718[];

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

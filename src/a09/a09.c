#include "common.h"
#include "game.h"
#include "m2c.h"

INCLUDE_ASM("asm/a09/nonmatchings/a09", func_80109078);

INCLUDE_ASM("asm/a09/nonmatchings/a09", func_801091CC);

INCLUDE_ASM("asm/a09/nonmatchings/a09", func_80109398);

INCLUDE_ASM("asm/a09/nonmatchings/a09", func_801095B8);

extern u8 D_800E7E80[];

void func_80109708(void)
{
    u8 *pl = D_800E7E80;
    func_8002288C(pl);
    switch (pl[0]) {
    case 0:
    case 6:
        break;
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 7:
    default:
        if (*(u32 *)(pl + 0x158) < 2) {
            func_80109398(pl);
        }
        break;
    }
    func_801095B8();
}

extern u8 D_800BF816;
extern s32 D_1F800184;
extern u16 D_1F800210;
extern u8 D_1F800152;
extern u8 D_1F800182;
extern s32 D_1F800080;

s32 func_80109790(void)
{
    for (D_1F800182 = D_1F800152; D_1F800182 != 0; D_1F800182--) {
    }
    return D_1F800080;
}

INCLUDE_ASM("asm/a09/nonmatchings/a09", f_UpdateEvilPigDoorTombaTransitionSequence);


void func_80109CA0(void *arg0) {
    func_8006F0E4();
    M2C_FIELD(arg0, s8 *, 1) = 1;
    func_80055D5C(arg0);
    M2C_FIELD(arg0, s16 *, 0x142) = 0;
    M2C_FIELD(arg0, s16 *, 0x58) = 0;
    func_80054198(arg0);
    func_80055284(arg0);
    func_80054D14(arg0, 2, 0);
    func_8003315C(arg0);
}

INCLUDE_ASM("asm/a09/nonmatchings/a09", func_80109D04);

INCLUDE_ASM("asm/a09/nonmatchings/a09", func_80109DF4);

extern u8 D_800BF816;
extern u8 D_800E806C;
extern s32 D_1F800184;
extern u8 D_800E7E80[];

void func_80109E54(void)
{
    u8 *p;

    D_800BF816 = 0;
    D_800E806C = 0;
    D_1F800184 = 0;
    p = D_800E7E80;
    p[5] = 0x24;
    p[7] = 0;
    p[6] = 0;
    func_80054198(p);
    p[0x16B] = 0;
}

INCLUDE_ASM("asm/a09/nonmatchings/a09", f_SpawnEvilPigDoorActorsFromPlacementTable);

INCLUDE_ASM("asm/a09/nonmatchings/a09", func_8010A060);


void func_8010A188(u8 *a)
{
    switch (a[4]) {
    case 0:
        a[4] = 1;
        f_SpawnEvilPigDoorActorsFromPlacementTable(a, 0);
        func_8010A060(0);
        func_800752B4(0);
        func_80075D24(0x1FFF);
        break;
    case 1:
        func_8010A060(1);
        break;
    case 2:
        break;
    case 3:
        func_8007ADD0();
        break;
    }
}

INCLUDE_ASM("asm/a09/nonmatchings/a09", func_8010A228);

INCLUDE_ASM("asm/a09/nonmatchings/a09", f_UpdateEvilPigInteriorEntranceDoorSequence);

INCLUDE_ASM("asm/a09/nonmatchings/a09", func_8010A5D8);

INCLUDE_ASM("asm/a09/nonmatchings/a09", f_InitializeEvilPigGateModel);

INCLUDE_ASM("asm/a09/nonmatchings/a09", f_ConfigureEvilPigGateForCurrentArea);

INCLUDE_ASM("asm/a09/nonmatchings/a09", f_UpdateEvilPigGateOpeningSequence);

INCLUDE_ASM("asm/a09/nonmatchings/a09", func_8010AD9C);

INCLUDE_ASM("asm/a09/nonmatchings/a09", func_8010AFB4);

typedef struct { s16 x, y, w, h; } RECT16;
typedef struct {
    u8 *seq;
    u8 *data;
    s16 x, y;
} TexAnim;
extern TexAnim D_8010E260[];
extern s8 D_8010E608[];

void func_8010B3A8(s32 run)
{
    RECT16 r;
    s32 i;
    u8 *p;
    u8 *d;
    TexAnim *e;
    if (run == 0) {
        for (i = 0; i < 1; i++) {
            D_8010E608[i] = 0;
        }
        return;
    }
    e = D_8010E260;
    for (i = 0; i < 1; i++, e++) {
        if (--D_8010E608[i] <= 0) {
            if (e->seq[0] == 0xFF) {
                e->seq -= e->seq[1];
            }
            p = e->seq;
            d = e->data + p[0] * 32;
            D_8010E608[i] = p[1];
            r.x = e->x;
            r.y = e->y;
            r.w = 0x10;
            r.h = 1;
            func_80081218(&r, d);
            e->seq += 2;
        }
    }
}

INCLUDE_ASM("asm/a09/nonmatchings/a09", func_8010B4C8);

INCLUDE_ASM("asm/a09/nonmatchings/a09", func_8010B664);

extern s16 D_801003F8;
extern u8 D_800E806E;

s32 func_8010B8B4(u8 *a)
{
    CameraState *c;
    switch (a[0x78]) {
    case 0:
        a[0x78]++;
        func_8006E1C0(1);
        c = &g_CameraState;
        c->unk6E = 0x80;
        c->unk70 = 0x400;
        c->unk6C = D_801003F8 * 5;
        c->focusX = *(s16 *)(a + 0x2E);
        c->focusY = *(s16 *)(a + 0x32) + 0x140;
        c->focusZ = *(s16 *)(a + 0x36) - 0x190;
        goto end;
    case 1:
        if (D_800E806E == 3) {
            return 1;
        }
    end:
    default:
        return 0;
    }
}

extern u8 D_800E7EAC[];

s32 func_8010B974(void)
{
    CameraState *c = &g_CameraState;
    c->mode = 2;
    c->unk6E = 0x80;
    c->unk70 = 0x400;
    c->unk6C = D_801003F8 * 5;
    func_8006CBA8(D_800E7EAC);
    return 1;
}


s32 func_8010B9CC(void)
{
    CameraState *c = &g_CameraState;
    c->mode = 1;
    c->unk6E = 0x80;
    c->unk70 = 0x400;
    c->unk6C = D_801003F8 * 7;
    func_8006CBA8(D_800E7EAC);
    return 1;
}

INCLUDE_ASM("asm/a09/nonmatchings/a09", func_8010BA24);

INCLUDE_ASM("asm/a09/nonmatchings/a09", func_8010BB20);

extern u8 *D_800BF860;

s32 func_8010BBFC(u8 *a)
{
    u8 *s = D_800BF860;
    switch (a[0x78]) {
    case 0:
        if (*(s16 *)(s + 0x30) > *(s16 *)(a + 0x36)) {
            a[0x78]++;
            s[4] = 2;
            func_80074590(0x37, 0x16, 0);
        }
        goto step;
    case 1:
        if (s[4] == 3) {
            return 1;
        }
    step:
        *(s16 *)(s + 0x30) += 0x20;
    default:
        return 0;
    }
}


s32 func_8010BC9C(u8 *a)
{
    s16 *p = *(s16 **)(a + 0xC4);
    if (p[5] == 0) {
        func_80074590(0x18, -0xC, 0);
        return 1;
    }
    p[5] -= 0x40;
    (*(s16 **)(a + 0xC8))[5] += 0x40;
    return 0;
}

INCLUDE_ASM("asm/a09/nonmatchings/a09", f_StartOrWaitForIndexedEvilPigPlateEvent);

INCLUDE_ASM("asm/a09/nonmatchings/a09", f_UpdateRemainingEvilPigStatueArrivalSequence);

INCLUDE_ASM("asm/a09/nonmatchings/a09", func_8010C01C);

INCLUDE_ASM("asm/a09/nonmatchings/a09", f_UpdateEvilPigStatueActor);

INCLUDE_ASM("asm/a09/nonmatchings/a09", func_8010C588);

INCLUDE_ASM("asm/a09/nonmatchings/a09", func_8010C6B8);


s32 func_8010CAF8(u8 *a)
{
    CameraState *c;
    switch (a[0x78]) {
    case 0:
        c = &g_CameraState;
        a[0x78]++;
        c->mode = 1;
        c->unk6E = 0xC0;
        c->unk70 = 0x680;
        c->unk6C = D_801003F8 * 4;
        c->focusX = *(s16 *)(a + 0x2E) - 0xC8;
        c->focusY = *(s16 *)(a + 0x32) - *(s16 *)(a + 0x84) / 2;
        c->focusZ = *(s16 *)(a + 0x36);
        goto end;
    case 1:
        if (D_800E806E == 3) {
            return 1;
        }
    end:
    default:
        return 0;
    }
}

INCLUDE_ASM("asm/a09/nonmatchings/a09", func_8010CBB0);

extern u8 D_8010E3FC[];

s32 func_8010CCD8(u8 *a)
{
    switch (a[6]) {
    case 0:
        a[6]++;
        func_80040CDC(a, 0, D_8010E3FC);
        a[0x70] = 1;
        goto end;
    case 1:
        func_80041098(a);
        if (a[0x70] == 0xFF) {
            a[4] = 3;
            func_80042310();
            return 1;
        }
    end:
    default:
        return 0;
    }
}

INCLUDE_ASM("asm/a09/nonmatchings/a09", func_8010CD68);

INCLUDE_ASM("asm/a09/nonmatchings/a09", func_8010CEC4);

INCLUDE_ASM("asm/a09/nonmatchings/a09", func_8010D0B0);

INCLUDE_ASM("asm/a09/nonmatchings/a09", func_8010D30C);

INCLUDE_ASM("asm/a09/nonmatchings/a09", func_8010D5D8);

INCLUDE_ASM("asm/a09/nonmatchings/a09", func_8010D7D4);

INCLUDE_ASM("asm/a09/nonmatchings/a09", func_8010D910);

#define H(p, o) (*(s16 *)((u8 *)(p) + (o)))

void func_8010DE2C(u8 *a)
{
    switch (a[4]) {
    case 0:
        a[4] = 1;
        H(a, 0x4E) = 0;
    case 1:
        a[1] = 1;
        if (H(a, 0x4E) < 0x1D6) {
            H(a, 0x4E) += (0x1F4 - H(a, 0x4E)) >> 2;
        } else {
            H(a, 0x4E) += 6;
        }
        if (H(a, 0x4E) >= 0x3E8) {
            a[4] = 2;
        }
        break;
    case 2:
    case 3:
        func_8007A624(a);
        break;
    }
}


void func_8010DEE0(u8 *a)
{
    u32 v;
    switch (a[4]) {
    case 0:
        a[4] = 1;
        *(u32 *)(a + 0x58) = 0;
    case 1:
        v = *(u32 *)(a + 0x58);
        a[1] = 1;
        *(u32 *)(a + 0x58) = v + ((0x1000 - v) >> 3);
        break;
    case 2:
    case 3:
        func_8007A624(a);
        break;
    }
}

INCLUDE_ASM("asm/a09/nonmatchings/a09", f_UpdateEvilPigInteriorEntranceDoorActor);

#include "common.h"
#include "game.h"
#include "m2c.h"

extern s8 D_800BF808[];
extern u8 D_1F800137;
extern s32 D_1F80009C;
typedef struct { u8 pad[0x60]; s32 unk60; s32 unk64; } AreaStateF58;
typedef struct { u8 pad0[7]; u8 unk7; u8 pad8[6]; u8 unkE; u8 unkF; u8 pad10[0x21]; u8 unk31; s16 unk32; } AreaState808_E;
typedef struct { u8 pad[0xC0]; u8 *parts[1]; } AreaPartsOwner;
typedef struct { s16 unk0; s16 x, y, z; } PartPose;
typedef struct { u8 pad[0x5E]; u8 pose; u8 pad2[0xC0 - 0x5F]; s16 *parts[3]; } PosedActor;
typedef struct { s16 x, y, w, h; } ClutRect;
typedef struct {
    u8 *ptr;
    u8 *clut;
    s16 x;
    s16 y;
} ClutCycle;
typedef struct { s16 x, y, z, pad; } RingVec;
typedef struct { s16 pos; s16 vel; } RiseMotion;

void func_80109078(u8 *a, u8 *b) {
    s32 t, u;

    if (D_1F800137 != 0 || D_800BF808[5] != 0) {
        return;
    }
    if (M2C_FIELD(a, s16 *, 0x17E) & 0x8200) {
        if (func_8002300C(a, b, 0x20) != 0) {
            if (!(a[0] & 4)) {
                t = (func_80083F50(D_1F80009C + 0x800) * (M2C_FIELD(a, s16 *, 0x80) + 0x20)) >> 12;
                u = func_80083E80(D_1F80009C + 0x800) * (M2C_FIELD(a, s16 *, 0x80) + 0x20);
                M2C_FIELD(a, s16 *, 0x2E) = M2C_FIELD(b, s16 *, 0x2E) + t;
                M2C_FIELD(a, s16 *, 0x36) = M2C_FIELD(b, s16 *, 0x36) - (u >> 12);
            }
            M2C_FIELD(a, s8 *, 0x5F) = func_80077768((s16)(*(u16 *)&D_1F80009C + 0x800), M2C_FIELD(a, s16 *, 0x140), 1) + 2;
        }
    } else if (func_80022F04(a, b) != 0) {
        b[0x29] = 1;
        D_1F800137 = 2;
        D_800BF808[0x39] = 1;
    }
}

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

void f_ConfigureEvilPigGateForCurrentArea(u8 *a, s32 b) {
    s32 i;
    s32 found;

    for (i = 0; i < D_800BF870.pad1[0x12]; i++) {
        if ((D_800BF870.pad1[0x13 + i] & 0x7F) == M2C_FIELD(a, s16 *, 0x7E)) {
            found = 1;
            goto done;
        }
    }
    found = 0;
done:
    if (found == 0) {
        goto dead;
    }
    if ((D_800BF870.pad1[0x1A8] >> a[3]) & 1) {
        a[4] = 3;
        return;
    }
    if (f_InitializeEvilPigGateModel(a, b) != 0) {
    dead:
        a[4] = 3;
        return;
    }
    if (D_800BF870.pad1[0] == M2C_FIELD(a, s16 *, 0x7A)) {
        M2C_FIELD(M2C_FIELD(a, u8 **, 0xC4), s16 *, 0xA) = 0x800;
        M2C_FIELD(M2C_FIELD(a, u8 **, 0xC8), s16 *, 0xA) = 0x800;
        a[4] = 1;
        a[5] = 0;
        a[0x5E] = 2;
    } else if ((D_800BF870.pad1[0x1A6] >> a[3]) & 1) {
        M2C_FIELD(M2C_FIELD(a, u8 **, 0xC4), s16 *, 0xA) = 0x800;
        M2C_FIELD(M2C_FIELD(a, u8 **, 0xC8), s16 *, 0xA) = 0x800;
        a[0] = 1;
        a[4] = 1;
        a[5] = 0;
        a[0x5E] = 1;
    } else {
        a[5]++;
    }
}

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

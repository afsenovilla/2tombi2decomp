#include "common.h"
#include "game.h"
#include "m2c.h"
#include "gte.h"

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

#define F16(p, o) M2C_FIELD(p, s16 *, o)
#define FU16(p, o) M2C_FIELD(p, u16 *, o)
extern s8 D_800BF80D;
extern u8 D_1F800182;
void func_801091CC(u8 *a, u8 *b) {
    u8 *q = a + 0x60;
    u32 k;
    s32 s;
    s32 c;

    if (D_1F800137 != 0) {
        return;
    }
    if (D_800BF80D != 0) {
        return;
    }
    if (func_8002300C(a, b, 0x50) == 0) {
        return;
    }
    if (a[0x5F] == 0x10) {
        if ((u16)(FU16(a, 0x84) + (FU16(a, 0x32) - (FU16(b, 0x32) + (FU16(b, 0x86) - FU16(b, 0x84))) + 20)) <= F16(a, 0x86) + 40) {
            k = a[0x46] >> 1;
            if ((s32)k >= 0) {
                if ((s32)k < 2) {
                    s = (func_80083F50(F16(q, 8) + 0x800) * (F16(a, 0x80) + 0x20)) >> 12;
                    c = func_80083E80(F16(q, 8) + 0x800) * (F16(a, 0x80) + 0x20);
                    F16(a, 0x2E) = FU16(b, 0x2E) + s;
                    F16(a, 0x36) = FU16(b, 0x36) - (c >> 12);
                    F16(a, 0x32) = FU16(b, 0x32) + (FU16(b, 0x86) - FU16(b, 0x84));
                } else if ((s32)k < 4) {
                    F16(a, 0x32) = FU16(b, 0x32) + (FU16(b, 0x86) - FU16(b, 0x84));
                    F16(a, 0x2E) = FU16(b, 0x2E);
                    F16(a, 0x36) = FU16(b, 0x36);
                }
            }
            func_8001E860(a, b, 0, 0x100);
        } else {
            func_8001E860(a, b, 0, 0);
        }
        D_1F800182 = 0;
    } else if (!(func_8001E860(a, b, 0, 0) & 0x80)) {
        D_1F800182 = 0;
    }
}

extern u8 **D_1F800148;
extern u8 D_1F800150;
void func_80109398(u8 *a)
{
    u8 **l = D_1F800148;
    u8 *e;

    D_1F800182 = D_1F800150;
    while (D_1F800182 != 0) {
        e = *l;
        D_1F800182--;
        l++;
        if (e[0] & 1) {
            switch (e[2]) {
            case 0xE:
            case 0xF:
                func_8001FAE0(a, e);
                break;
            case 0xC:
                func_80020868(a, e);
                break;
            case 0x12:
                func_8002311C(a, e);
                break;
            case 0x1F:
                func_80023764(a, e);
                break;
            case 0x65:
                func_80109078(a, e);
                break;
            case 0x66:
                func_8001FC50(a, e);
                break;
            case 0x67: {
                s16 dx = *(u16 *)(a + 0x2E) - *(u16 *)(e + 0x2E);
                s16 dz = *(u16 *)(a + 0x36) - *(u16 *)(e + 0x36);
                u16 d = func_80084080(dx * dx + dz * dz);
                if (*(s16 *)(a + 0x80) + 0xC8 < d) {
                    break;
                }
                if ((u16)(*(u16 *)(a + 0x84) + (*(u16 *)(a + 0x32) - *(u16 *)(e + 0x32) + 0x140)) > *(s16 *)(a + 0x86) + 0x140) {
                    break;
                }
                e[0x29] = 1;
                func_8001F830(a, e);
                break;
            }
            }
        }
    }
}

extern u8 *D_800F2738;
void func_801095B8(void)
{
    u8 *p;
    u8 **l;
    u8 *e;

    if (*(s16 *)&D_1F800150 == 0) {
        return;
    }
    for (p = D_800F2738; p != NULL; p = *(u8 **)(p + 0x24)) {
        if (!(p[0] & 1) || p[0x2B] != 0) {
            continue;
        }
        l = D_1F800148;
        D_1F800182 = D_1F800150;
        while (D_1F800182 != 0) {
            e = *l;
            D_1F800182--;
            l++;
            if (e[0] & 1) {
                switch (e[2]) {
                case 0xC:
                    func_80023618(p, e);
                    break;
                case 0x65:
                    func_801091CC(p, e);
                    break;
                case 0x12:
                case 0x1F:
                case 0x67:
                    func_800216B4(p, e, 0);
                    break;
                }
            }
        }
    }
}

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

typedef struct {
    u8 pad0[5];
    u8 x5;
    u8 x6;
    u8 pad7[0x139];
    u16 x140;
    u8 pad142[0x29];
    u8 x16B;
} Area7E80;
extern Area7E80 D_800E7E80_eac2;
void func_80109DF4(void)
{
    func_80054198(&D_800E7E80_eac2);
    D_800BF816 = 1;
    D_1F800184 = 0;
    D_800E7E80_eac2.x5 = 0x24;
    D_800E7E80_eac2.x6 = 0;
    D_800E7E80_eac2.x16B = 8;
    D_1F800210 = D_800E7E80_eac2.x140;
}

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

typedef struct {
    u8 kind, b1, b2, slot;
    s16 x, y, z;
    u8 mode, padB;
    void *cb;
} Spawn;
typedef struct {
    u8 pad[8];
    s16 x, y, z;
} Pos;
typedef struct {
    u8 pad[8];
    s16 count;
    u8 padA[2];
    u8 *list[15];
} Owner;
extern Spawn *D_8010E044[];
extern Pos D_800BF808_76d5;
void f_SpawnEvilPigDoorActorsFromPlacementTable(Owner *a, s32 sel)
{
    Spawn *e;
    u8 *p;
    a->count = 0;
    e = D_8010E044[sel];
    while (e->kind != 0xFF) {
        if (sel == 0 || a->count < 15) {
            switch (e->mode) {
            case 0:
                break;
            case 1:
                D_800BF808_76d5.x = e->x;
                D_800BF808_76d5.y = e->y;
                D_800BF808_76d5.z = e->z;
                break;
            case 2:
                if ((D_800BF870.pad1[0x1CC] >> e->slot) & 1) {
                    goto next;
                }
                break;
            }
            p = func_80072DDC(a, e->kind, e->b1, e->b2);
            if (p != 0) {
                *(s32 *)(p + 0x2C) = e->x << 16;
                *(s32 *)(p + 0x30) = e->y << 16;
                *(s32 *)(p + 0x34) = e->z << 16;
                p[3] = e->slot;
                *(s16 *)(p + 0x54) = 0;
                *(s16 *)(p + 0x56) = 0;
                *(s16 *)(p + 0x58) = 0;
                *(void **)(p + 0x1C) = e->cb;
                if (sel != 0) {
                    a->list[a->count] = p;
                    a->count++;
                }
            }
        }
    next:
        e++;
    }
}

extern ClutCycle D_8010E0DC[];
extern s8 D_8010E5FC[];
extern u8 D_800BF873;
void func_8010A060(s32 arg0) {
    ClutRect r;
    s32 i;
    ClutCycle *e;
    u8 *data;

    if (arg0 == 0) {
        s8 *p;
        i = 8;
        p = &D_8010E5FC[i];
        do {
            *p-- = 0;
        } while (--i >= 0);
        return;
    }
    e = D_8010E0DC;
    for (i = 0; i < 9; i++, e++) {
        if (--D_8010E5FC[i] <= 0) {
            if (e->ptr[0] == 0xFF) {
                e->ptr -= e->ptr[1];
            }
            data = e->clut + e->ptr[0] * 32;
            D_8010E5FC[i] = e->ptr[1];
            r.x = e->x;
            r.y = e->y;
            r.w = 16;
            r.h = 1;
            func_80081218(&r, data);
            e->ptr += 2;
        }
    }
}

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

typedef struct { s16 x, y, z; u8 b6, b7; s16 h8, hA; } DoorEnt;
#define H(p, o) (*(s16 *)((u8 *)(p) + (o)))
extern u8 D_8010E160[];
extern DoorEnt D_8010E164[];
void func_8010A5D8(u8 *a)
{
    u8 *t;
    u8 k;

    switch (a[4]) {
    case 0:
        t = D_8010E160;
        if (func_80051B70(a, 0xC, t[a[3] * 2]) != 0) {
            break;
        }
        a[0xBF] = 1;
        H(a, 0x50) = 0;
        a[4]++;
        a[0x28] |= 0x80;
        H(a, 0x5A) = H(a, 0x56);
        k = t[a[3] * 2 + 1];
        if (k != 0) {
            a[0x2A] = k;
            H(a, 0x60) = D_8010E164[a[3]].x - H(a, 0x2E);
            H(a, 0x62) = D_8010E164[a[3]].y;
            H(a, 0x64) = D_8010E164[a[3]].z - H(a, 0x36);
            a[0x5F] = D_8010E164[a[3]].b6;
            H(a, 0x82) = D_8010E164[a[3]].h8;
            H(a, 0x80) = H(a, 0x82) / 2;
            H(a, 0x86) = D_8010E164[a[3]].hA;
            H(a, 0x84) = H(a, 0x86) / 2;
            a[0] = 1;
        }
        a[0x29] = 0;
        if (a[3] == 0) {
            a[0x46] = 0;
            a[0xBF] = 1;
            H(a, 0x50) = -0x400;
            func_80072EFC(a);
            a[0] = 2;
        }
        break;
    case 1:
        if (a[3] == 0) {
            f_UpdateEvilPigInteriorEntranceDoorSequence(a);
        }
        if (func_8007778C(a) != 0) {
            func_800517F8(a);
        }
        a[0x29] = 0;
        break;
    case 2:
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

typedef union {
    u8 b[0xC0];
    s16 h[0x60];
} ActorH;
extern s16 D_800ED098;
extern s16 D_1F8001A0;
extern s16 D_1F8001A2;
typedef struct {
    u8 b[0x56];
    s16 h56;
    u8 pad58[8];
    s16 h60;
    s16 h62;
    u8 pad64[0x5C];
    u8 *parts[3];
} DoorActor;
typedef struct {
    u8 b[6][4];
} FlickerTbl;
typedef struct {
    s16 x, y, z, pad;
} SVec4;
typedef struct {
    u8 pad0[6];
    u8 count;
    u8 pad7[5];
    u32 *tbl;
    u16 list[1];
} PartList;
s32 f_InitializeEvilPigGateModel(DoorActor *a, s16 *d) {
    s32 i;
    s32 n;
    s16 x, y;

    a->b[8] = 3;
    if (D_800ED098 < 3) {
        return 1;
    }
    n = 3;
    a->b[9] = n;
    a->b[0xD] = 4;
    M2C_FIELD(a->b, s16 *, 0x80) = 0x80;
    M2C_FIELD(a->b, s16 *, 0x82) = 0x100;
    M2C_FIELD(a->b, s16 *, 0x84) = 0xDC;
    M2C_FIELD(a->b, s16 *, 0x86) = 0x1C2;
    a->b[0xB] = 0;
    M2C_FIELD(a->b, s16 *, 0xB8) = 0x1000;
    M2C_FIELD(a->b, s16 *, 0xBA) = 0x1000;
    M2C_FIELD(a->b, s16 *, 0xBC) = 0x1000;
    for (i = 0; i < a->b[8]; i++) {
        a->parts[i] = func_8007AAE8();
        M2C_FIELD(a->parts[i], s16 *, 6) = *d++;
        M2C_FIELD(a->parts[i], s16 *, 0) = *d++;
        M2C_FIELD(a->parts[i], s16 *, 2) = *d++;
        M2C_FIELD(a->parts[i], s16 *, 4) = *d++;
        M2C_FIELD(a->parts[i], s16 *, 8) = 0;
        M2C_FIELD(a->parts[i], s16 *, 0xA) = 0;
        M2C_FIELD(a->parts[i], s16 *, 0xC) = 0;
        M2C_FIELD(a->parts[i], s16 *, 0x38) = 0x1000;
        M2C_FIELD(a->parts[i], s16 *, 0x3A) = 0x1000;
        M2C_FIELD(a->parts[i], s16 *, 0x3C) = 0x1000;
        func_80051B04(a->parts[i], 0xC, *d++);
    }
    a->parts[0][0x3F] = 0x20;
    a->parts[1][0x3F] = 0xF0;
    a->parts[2][0x3F] = 0xF0;
    a->b[0x29] = 0;
    a->b[0x2B] = 0;
    func_8004766C(a->b);
    func_80048750(a->b);
    x = D_1F8001A0;
    y = D_1F8001A2;
    a->h60 = x;
    a->h62 = y;
    a->h56 = x;
    M2C_FIELD(a->parts[0], s16 *, 0xA) = M2C_FIELD(a->b, s16 *, 0x7C);
    return 0;
}

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

extern u8 D_800BF841;
extern u8 D_800E806E;
extern u16 D_1F8000D6;
void f_UpdateEvilPigGateOpeningSequence(u8 *a) {
    u8 *t;

    switch (a[5]) {
    case 0:
        D_1F800137 = 2;
        D_800BF841 = 1;
        func_8006E1C0(8);
        func_8006CBA8(a + 0x2C);
        D_1F8000D6 = FU16(a, 0x32);
        a[5]++;
        break;
    case 1:
        if ((D_800E806E & 3) == 3) {
            t = D_800E7E80;
            a[5]++;
            a[0x46] = func_80077768((s16)func_80085690(-(s16)(FU16(a, 0x36) - FU16(t, 0x36)), (s16)(FU16(a, 0x2E) - FU16(t, 0x2E))), F16(a, 0x60), 0);
            func_80074590(0x17, -0x12, 0x1E);
        }
        break;
    case 2:
        if (a[0x46] == 0) {
            F16(M2C_FIELD(a, u8 **, 0xC4), 0xA) -= 0x40;
            F16(M2C_FIELD(a, u8 **, 0xC8), 0xA) += 0x40;
            if (F16(M2C_FIELD(a, u8 **, 0xC4), 0xA) < -0x7FF) {
                a[5]++;
            }
        } else {
            F16(M2C_FIELD(a, u8 **, 0xC4), 0xA) += 0x40;
            F16(M2C_FIELD(a, u8 **, 0xC8), 0xA) -= 0x40;
            if (F16(M2C_FIELD(a, u8 **, 0xC4), 0xA) >= 0x800) {
                a[5]++;
            }
        }
        break;
    case 3:
        F16(a, 0x40) = 30;
        a[5]++;
        break;
    case 4:
        if (--F16(a, 0x40) == 0) {
            D_1F800137 = 0;
            D_800BF841 = 0;
            func_8006E1E4();
            D_800BF870.pad1[0x1A6] |= 1 << a[3];
            a[0x5E] = 1;
            a[0] = 1;
            a[5] = 0;
        }
        break;
    }
}

extern u8 D_1F800236;
extern u8 D_800BF808_1760[];
void func_8010AD9C(u8 *a) {
    u8 *t = D_800E7E80;
    u8 v;

    switch (a[5]) {
    case 0:
        if (a[0x29] != 0) {
            a[5] = 1;
            v = func_80077768((s16)func_80085690(-(s16)(FU16(a, 0x36) - FU16(t, 0x36)), (s16)(FU16(a, 0x2E) - FU16(t, 0x2E))), F16(a, 0x60), 0);
            a[0x46] = v;
            if (v == 0) {
                F16(a, 0x44) = 0x800;
            } else {
                F16(a, 0x44) = -0x800;
            }
        }
        break;
    case 1:
        if (F16(t, 0x32) > F16(a, 0x32)) {
            F16(t, 0x32) = FU16(t, 0x32) - 20;
            if (F16(t, 0x32) < F16(a, 0x32)) {
                F16(t, 0x32) = FU16(a, 0x32);
            }
        } else if (F16(t, 0x32) < F16(a, 0x32)) {
            F16(t, 0x32) = FU16(t, 0x32) + 20;
            if (F16(t, 0x32) > F16(a, 0x32)) {
                F16(t, 0x32) = FU16(a, 0x32);
            }
        }
        M2C_FIELD(t, s32 *, 0x2C) += F16(a, 0x44) * F16(t, 0x48);
        M2C_FIELD(t, s32 *, 0x34) += F16(a, 0x44) * F16(t, 0x4C);
        func_8004766C(t);
        func_80048750(t);
        F16(t, 0xB8) -= 0x80;
        F16(t, 0xBA) -= 0x80;
        F16(t, 0xBC) -= 0x80;
        if (FU16(t, 0xB8) < 0x101) {
            a[5]++;
        }
        break;
    case 2:
        a[5] = 3;
        D_1F800236 = 7;
        D_800BF808_1760[0x31] = 1;
        F16(D_800BF808_1760, 0x32) = a[0xBF] << 4;
        break;
    }
}

typedef struct { u8 pad[0x3A]; s16 x; s16 p1; s16 y; s16 p2; s16 z; } S8008;
extern u8 D_800BF80F;
extern u16 D_1F80017C;
extern s16 D_1F8000D0[];
extern S8008 D_800E8008_ef2a;
#define W(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define P(p, o) (*(u8 **)((u8 *)(p) + (o)))

void func_8010AFB4(u8 *a, u16 *b)
{
    s16 v[6];
    u8 *e;
    u8 *pos;

    switch (a[5]) {
    case 0:
        H(a, 0x40) = 0x3C;
        a[5]++;
    case 1:
        if (D_800BF80F == 0) {
            a[5]++;
            D_1F800137 = 2;
            D_800BF870.pad1[0x1A8] |= 1 << a[3];
            func_8006E1C0(8);
            D_1F8000D0[1] = b[0];
            D_1F8000D0[3] = b[1];
            D_1F8000D0[5] = b[2];
            D_800E8008_ef2a.x = b[3];
            D_800E8008_ef2a.y = b[4];
            D_800E8008_ef2a.z = b[5];
            D_800E7E80[4] = 4;
            D_800E7E80[5] = 0x21;
            D_800E7E80[6] = 0;
        }
        break;
    case 2:
        if (D_800E806E == 3) {
            a[5]++;
        }
        break;
    case 3:
        if (--H(a, 0x40) == -1) {
            H(a, 0x40) = 0x3C;
            a[5]++;
            v[1] = H(a, 0x2E);
            v[3] = H(a, 0x32) + 0x80;
            v[5] = H(a, 0x36);
            e = func_8003116C(0x15, v, -0x32);
            e[0x28] |= 0x80;
            e = func_8003116C(0x24, v, -0x32);
            e[0x28] |= 0x80;
            func_80027144(W(P(a, 0xC0), 0x40), v, 0x800, 8);
            func_80074590(0xC, 0, 0);
            pos = a + 0x2C;
            func_80027144(W(P(a, 0xC0), 0x40), pos, 0x600, 0x18);
            func_80074590(0xC, 0, 0);
            v[1] = H(P(a, 0xC4), 0x2C);
            v[1] = H(P(a, 0xC4), 0x30) + 0x80;
            v[1] = H(P(a, 0xC4), 0x34);
            e = func_8003116C(0x24, v, -0x32);
            e[0x28] |= 0x80;
            func_80027144(W(P(a, 0xC4), 0x40), pos, 0x800, 8);
            func_80074590(0xC, 0, 0);
            func_80027144(W(P(a, 0xC4), 0x40), pos, 0x600, 0x18);
            func_80074590(0xC, 0, 0);
            v[1] = H(P(a, 0xC8), 0x2C);
            v[1] = H(P(a, 0xC8), 0x30) + 0x80;
            v[1] = H(P(a, 0xCC), 0x34);
            e = func_8003116C(0x24, v, -0x32);
            e[0x28] |= 0x80;
            func_80027144(W(P(a, 0xC8), 0x40), pos, 0x800, 8);
            func_80074590(0xC, 0, 0);
            func_80027144(W(P(a, 0xC8), 0x40), pos, 0x600, 0x18);
            func_80074590(0xC, 0, 0);
        } else {
            H(P(a, 0xC0), 2) = (D_1F80017C & 1) * 6;
            H(P(a, 0xC0), 0) = ((func_8009A450() & 3) - 2) * 6;
        }
        break;
    case 4:
        if (--H(a, 0x40) == -1) {
            a[4] = 3;
            D_1F800137 = 0;
            func_8006E1E4();
        }
        a[1] = 0;
        break;
    }
}

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

typedef struct { u8 pad[0x5C]; u8 *p5C; } Bf808;
extern Bf808 D_800BF808_71fd;
extern u8 *D_800BF864;
extern u8 D_800E807E;
s32 func_8010BB20(u8 *a)
{
    switch (a[0x78]) {
    case 0:
        a[0x78]++;
        D_800E807E = 1;
        D_800BF808_71fd.p5C[4] = 3;
        D_800BF808_71fd.p5C = (u8 *)func_8003116C(0xA01, a + 0x2C, 0);
        func_80074590(0x37, -20, 0);
        *(s16 *)(a + 0x40) = 90;
        break;
    case 1:
        if (--*(s16 *)(a + 0x40) == -1) {
            D_800E807E = 0;
            D_800BF864[4] = 3;
            return 1;
        }
        return 0;
    }
    return 0;
}

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

extern s16 D_8010E398[];
s32 f_StartOrWaitForIndexedEvilPigPlateEvent(u8 *a)
{
    switch (a[6]) {
    case 0:
        if (D_800BF870.pad1[D_8010E398[a[3]] + 0x43] != 0) {
            return 1;
        }
        a[6] = 1;
        return 0;
    case 1:
        if (a[0x2B] == 3) {
            a[6] = 2;
            func_80040B48(D_8010E398[a[3]]);
            return 0;
        }
        if (D_800BF870.pad1[D_8010E398[a[3]] + 0x43] != 0) {
            return 1;
        }
        break;
    case 2:
        if (func_80042728() != 0) {
            return 1;
        }
        break;
    }
    return 0;
}

INCLUDE_ASM("asm/a09/nonmatchings/a09", f_UpdateRemainingEvilPigStatueArrivalSequence);

INCLUDE_ASM("asm/a09/nonmatchings/a09", func_8010C01C);

extern s16 D_8010E38C[];
void f_UpdateEvilPigStatueActor(u8 *a)
{
    u8 *g;
    u8 *p;

    switch (a[4]) {
    case 0:
        g = (u8 *)&D_800BF870;
        if ((g[0x1CD] >> a[3]) & 1) {
            a[4] = 3;
            break;
        }
        if (func_80051B70(a, 0xC, D_8010E38C[a[3]]) != 0) {
            break;
        }
        H(a, 0x80) = 0x118;
        H(a, 0x82) = 0x230;
        a[0] = 1;
        H(a, 0x84) = 0x172;
        H(a, 0x86) = 0x172;
        a[0x2B] = 0;
        a[0x29] = 0;
        H(a, 0x60) = 0;
        a[4]++;
        if (g[0x1D1] == 0) {
            a[5] = 0;
            break;
        }
        if (g[D_8010E398[a[3]] + 0x44] != 0) {
            a[5] = 2;
            a[0] = 2;
        } else {
            a[5] = 1;
        }
        p = func_80031220(0xA02, 0, 0);
        if (p == NULL) {
            break;
        }
        p[3] = a[3] + 1;
        H(p, 0x2C) = H(a, 0x2E);
        H(p, 0x2E) = H(a, 0x32) - 0x96;
        H(p, 0x30) = H(a, 0x36);
        {
            s16 *q = (s16 *)(p + 0x50);

            if (a[3] == 0) {
                q[0] = 0x780;
                q[1] = -0x338;
                q[2] = 0x900;
            } else {
                q[0] = 0xD00;
                q[1] = -0x4E9;
                q[2] = 0xCED;
            }
        }
        *(u8 **)(a + 0x10) = p;
        break;
    case 1:
        a[1] = 1;
        func_80077EBC(a);
        switch (a[5]) {
        case 0:
            if (func_8010C01C(a) != 0) {
                a[6] = 0;
                a[5]++;
            }
            break;
        case 1:
            if (f_StartOrWaitForIndexedEvilPigPlateEvent(a) != 0) {
                a[6] = 0;
                a[0] = 2;
                a[5]++;
            }
        case 2:
            if (a[3] == 0) {
                f_UpdateRemainingEvilPigStatueArrivalSequence(a);
            }
            break;
        }
        func_800517F8(a);
        a[0x2B] = 0;
        a[0x29] = 0;
        break;
    case 2:
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

extern u8 D_800BFA41;
extern u8 D_800E8008[];
s32 func_8010C588(u8 *a)
{
    u8 *t;

    switch (a[6]) {
    case 0:
        if (D_800BFA41 != 6) {
            return 0;
        }
        a[6] = 1;
        t = D_800E8008;
        a[0x18] = 0xFF;
        a[0x19] = 0xFF;
        a[0x1A] = 0xFF;
        a[0xD] |= 2;
        *(s16 *)(t + 0x70) = 0x500;
        *(s16 *)(t + 0x3A) = *(s16 *)(a + 0x2E);
        *(s16 *)(t + 0x3E) = *(u16 *)(a + 0x32) - *(s16 *)(a + 0x84) / 2;
        *(s16 *)(t + 0x42) = *(s16 *)(a + 0x36);
        func_80074590(0x38, 0x12, 0);
        return 0;
    case 1:
        a[1] = 1;
        func_80077EBC(a);
        func_800517F8(a);
        a[0x18] -= 8;
        a[0x19] -= 8;
        a[0x1A] -= 8;
        if ((s8)a[0x18] < 0) {
            return 0;
        }
        a[0xD] &= ~2;
        return 1;
    }
    return 0;
}

typedef struct { s16 pad; s16 x; s16 pad2; s16 y; s16 pad3; s16 z; } PosV;
extern u8 D_800BF809;
extern u8 D_800E7EEF;
extern u8 D_8010E3B0[];
extern u8 D_8010E3FC[];
/* func_8010CBB0, inlined */
static inline s32 inl_8010CBB0(u8 *a)
{
    u8 *g;

    switch (a[6]) {
    case 0:
        if (D_800BF809 != 0) {
            return 0;
        }
        if (a[0x29] == 0) {
            break;
        }
        g = (u8 *)&D_800BF870;
        if (g[0x76] == 0) {
            func_80040B48(0x32);
        }
        if (g[0x1D0] != 0) {
            return 0;
        }
        a[6]++;
        func_80042354(1, 4);
        g[0x1D0] = 1;
        break;
    case 1:
        a[6] = 2;
        func_80040CDC(a, 0, D_8010E3B0);
        a[0x70] = 1;
        break;
    case 2:
        func_80041098(a);
        if (a[0x70] != 0xFF) {
            return 0;
        }
        a[6] = 0;
        func_80042310();
        return 1;
    }
    return 0;
}
/* func_8010CCD8, inlined */
static inline s32 inl_8010CCD8(u8 *a)
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
void func_8010C6B8(u8 *a)
{
    PosV v;

    switch (a[4]) {
    case 0:
        switch (a[5]) {
        case 0:
            if (func_80051B70(a, 0xC, 6) != 0) {
                break;
            }
            H(a, 0x80) = 0x50;
            H(a, 0x82) = 0xA0;
            H(a, 0x84) = 0x140;
            H(a, 0x86) = 0x140;
            H(a, 0x54) = 0;
            H(a, 0x56) = 0x400;
            H(a, 0x58) = 0;
            a[0x2B] = 0;
            a[0x29] = 0;
            a[5]++;
            break;
        case 1:
            if (func_8010C588(a) != 0) {
                a[4] = 1;
                a[5] = 0;
                a[6] = 0;
                a[0] = 1;
            }
            break;
        }
        break;
    case 1:
        inl_8010CBB0(a);
        a[1] = 1;
        func_80077EBC(a);
        func_800517F8(a);
        a[0x2B] = 0;
        a[0x29] = 0;
        break;
    case 2:
        switch (a[6]) {
        case 0:
            if (D_800E7EEF != 0x12) {
                a[0] = 1;
                a[4] = 1;
                a[5] = 0;
                a[6] = 0;
                a[0x29] = 0;
                if (func_8007778C(a) != 0) {
                    func_800517F8(a);
                }
                break;
            }
            a[6] = 1;
            func_80040C00(0x32);
            {
                u8 *g = (u8 *)&D_800BF870;
                g[0x1CD] |= 1 << a[3];
            }
            func_8006E1C0(8);
            v.x = H(a, 0x2E);
            v.y = H(a, 0x32) - H(a, 0x84) / 2;
            v.z = H(a, 0x36);
            func_8006CBA8(&v);
            func_8003116C(0x37, &v, -0x20);
            func_80027144(*(void **)(*(u8 **)(a + 0xC0) + 0x40), &v, 0x700, 8);
            func_80074590(0xC, 0, 0);
            func_80027144(*(void **)(*(u8 **)(a + 0xC0) + 0x40), a + 0x2C, 0x700, 8);
            func_80074590(0xC, 0, 0);
            func_80074590(0x2D, -0xC, 0x14);
            break;
        case 1:
            if (D_800BF809 != 0) {
                break;
            }
            a[6] = 2;
            func_80042354(1, 4);
            break;
        case 2:
            if (func_80042728() != 0) {
                func_8006E1E4();
                a[4] = 4;
                a[5] = 0;
                a[6] = 0;
            }
            break;
        }
        break;
    case 3:
        func_8007A624(a);
        break;
    case 4:
        inl_8010CCD8(a);
        break;
    }
}

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

s32 func_8010CBB0(u8 *a)
{
    u8 *g;

    switch (a[6]) {
    case 0:
        if (D_800BF809 != 0) {
            return 0;
        }
        if (a[0x29] == 0) {
            break;
        }
        g = (u8 *)&D_800BF870;
        if (g[0x76] == 0) {
            func_80040B48(0x32);
        }
        if (g[0x1D0] != 0) {
            return 0;
        }
        a[6]++;
        func_80042354(1, 4);
        g[0x1D0] = 1;
        break;
    case 1:
        a[6] = 2;
        func_80040CDC(a, 0, D_8010E3B0);
        a[0x70] = 1;
        break;
    case 2:
        func_80041098(a);
        if (a[0x70] != 0xFF) {
            return 0;
        }
        a[6] = 0;
        func_80042310();
        return 1;
    }
    return 0;
}

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

typedef struct { s16 x, y, z, pad; } AreaSVec;
typedef struct {
    u16 type;
    u8 pad2[6];
    u8 mag0;
    u8 mag1;
    u8 x;
    u8 y;
} AreaPadAnalog;
typedef struct {
    u8 pad[0xA];
    s16 count;
    u8 *entries;
    u32 pending;
    u32 done;
} RewardSet;
typedef struct {
    s16 pad0;
    s16 x;
    s16 pad4;
    s16 y;
    s16 pad8;
    s16 z;
} HiPos;
typedef struct { u8 pad0[7]; u8 unk7; u8 pad8[0x29]; u8 unk31; s16 unk32; } AreaState808_7;
typedef struct {
    u32 tag;
    u32 rgbc;
    s16 x0, y0;
    u8 u0, v0;
    u16 clut;
    s16 x1, y1;
    u8 u1, v1;
    u16 tpage;
    s16 x2, y2;
    u8 u2, v2;
    u16 pad1;
    s16 x3, y3;
    u8 u3, v3;
    u16 pad2;
} AreaPolyFT4;
extern u32 *D_800ED8C8;
AreaPolyFT4 *func_8010D7D4(AreaPolyFT4 *p, s32 x, s32 y, s32 w, s32 h, s16 c, s16 cy) {
    u32 rgbc;
    u16 clut;
    s16 x0, x1;

    if (c <= 0) return p; {
        rgbc = ((c | 0x2E00) << 16) | ((c << 8) | c);
        clut = ((cy + 0x1F0) << 6) | 0x17;
        x0 = x - w;
        x1 = x + w;
        p->u0 = p->u2 = 0xB9;
        p->u1 = p->u3 = 0xE7;
        p->v0 = p->v1 = 0x51;
        p->v2 = p->v3 = 0x67;
        *(u32 *)((u8 *)p + 4) = rgbc;
        p->tpage = 0x35;
        p->clut = clut;
        p->x0 = p->x2 = x0;
        p->x1 = p->x3 = x1;
        p->y0 = p->y1 = y - h;
        p->y2 = p->y3 = y;
        p->tag = D_800ED8C8[4] | 0x09000000;
        D_800ED8C8[4] = (u32)p;
        p++;
        p->u0 = p->u2 = 0xB9;
        p->u1 = p->u3 = 0xE7;
        p->v0 = p->v1 = 0x67;
        p->v2 = p->v3 = 0x51;
        *(u32 *)((u8 *)p + 4) = rgbc;
        p->tpage = 0x35;
        p->clut = clut;
        p->x0 = p->x2 = x0;
        p->x1 = p->x3 = x1;
        p->y0 = p->y1 = y;
        p->y2 = p->y3 = y + h;
        p->tag = D_800ED8C8[4] | 0x09000000;
        D_800ED8C8[4] = (u32)p;
        return p + 1;
    }

}

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

typedef struct { u16 start; u16 len; } AudioSeg;
extern AudioSeg D_8010E5A8[];
extern AudioSeg D_8010E5C0[];
extern s32 D_1F80021C;
void f_UpdateEvilPigInteriorEntranceDoorActor(s16 a, s16 i)
{
    AudioSeg *t;
    s32 ch, off, p;
    switch (a) {
    case 0:
        t = D_8010E5A8;
        ch = 3;
        off = 0;
        break;
    case 1:
        t = D_8010E5C0;
        ch = 0xB;
        off = 0x3D3;
        break;
    default:
        return;
    }
    p = D_1F80021C + t[i].start * 32 + off * 32;
    func_8001D2A8(ch, p, p + (t[i].len + 1) * 32, 0);
}

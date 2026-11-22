#include "common.h"
#include "game.h"
#include "m2c.h"

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_80109304);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_8010943C);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_80109678);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_801099E0);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_80109B0C);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_80109C54);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_80109EA8);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_8010A04C);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_8010A1D4);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_8010A3C0);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_8010A500);

extern u8 D_1F800137;
extern s8 D_800BF808[];
extern s16 D_1F80019E;

void func_8010A7B8(u8 *a)
{
    s32 pad[4];
    if (D_1F800137 == 0 && D_800BF808[5] == 0 && *(s16 *)(a + 0x32) > -0x4B0) {
        *(s16 *)(a + 0x32) = -0x4B0;
        D_800BF808[0x16] = 0;
        a[0] = 3;
        a[4] = 2;
        a[5] = 4;
        a[6] = 0;
        a[7] = 0;
        D_1F80019E = -0x4B0;
    }
}

extern void *D_1F800080;
extern u8 D_1F800182_5650;

void func_8010A830(u8 *a, u8 *b)
{
    if (func_80024BD8(a, b, *(void **)(b + 0xC0)) != 0) {
        b[0x29] = 1;
        a[0x164] = 3;
        D_1F800080 = b;
        D_1F800182_5650 = 0;
    }
}


s32 func_8010A888(s32 arg0, s32 arg1) {
    return func_80109678(arg0, arg1, M2C_FIELD(arg1, s32 *, 0xC0));
}

#define H(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define U(p, o) (*(u16 *)((u8 *)(p) + (o)))

s32 func_8010A8AC(u8 *a, u8 *b)
{
    s32 i, r;
    u8 *e;
    if ((u16)(U(a, 0x80) + (U(a, 0x36) - U(*(u8 **)(b + 0xC0), 0x34) + 0x190)) > H(a, 0x82) + 0x320) {
        return -1;
    }
    r = -1;
    for (i = 0; i < b[8]; i++) {
        e = ((u8 **)(b + 0xC0))[i];
        if (e[0x3F] != 1 && (u16)(U(a, 0x80) + (U(a, 0x2E) - U(e, 0x2C) + 0x60)) <= H(a, 0x82) + 0xC0) {
            r = i;
            break;
        }
    }
    return r;
}

extern s32 D_1F80009C;

void func_8010A970(u8 *a, u8 *b)
{
    s32 r = func_8001F40C(a, b, 1);
    if (r >= 0) {
        b[0x5F] = func_80077768((s16)(*(u16 *)&D_1F80009C + 0x800), *(s16 *)(b + 0x60), 1) + 2;
        func_8001FF7C(a, b, r, 1);
    }
}

extern s8 D_1F800182[];

void func_8010A9F0(s32 arg0, M2C_UNK arg1) {
    if ((func_80022F04() != 0) && !(func_8001DC9C(arg0, arg1, 0, 0) & 0x80)) {
        *((s8 *)D_1F800182) = 0;
    }
}

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_8010AA48);

extern u8 **D_1F80014C;
extern u8 D_1F800152;

void *func_8010AB3C(u8 *a)
{
    u8 **l = D_1F80014C;
    u8 *p;
    D_1F800182_5650 = D_1F800152;
    while (D_1F800182_5650 != 0) {
        p = *l;
        D_1F800182_5650--;
        l++;
        if ((p[0] & 1) && p[2] == 0x11 && func_80024BD8(a, p, *(void **)(p + 0xC0)) != 0) {
            p[0x29] = 1;
            a[0x164] = 3;
            D_1F800080 = p;
            D_1F800182_5650 = 0;
        }
    }
    return D_1F800080;
}

extern s8 D_1F80027E[];
extern u8 D_800BFA1A;

void func_8010AC1C(void *arg0) {
    *((s8 *)D_1F80027E) = 1;
    func_8006F0E4();
    M2C_FIELD(arg0, s8 *, 1) = 1;
    func_80055D5C(arg0);
    M2C_FIELD(arg0, s16 *, 0x142) = 0;
    M2C_FIELD(arg0, s16 *, 0x58) = 0;
    func_80054198(arg0);
    func_80055284(arg0);
    func_80054D14(arg0, 2, 0);
    func_8003315C(arg0);
    if (!(D_800BFA1A & 8)) {
        func_80042354(1, 5);
        func_8001CF2C();
        M2C_FIELD(arg0, s8 *, 4) = 4;
    }
}

typedef struct { s16 x, y, z, pad; } SV;
extern u16 D_1F8001A4;
extern SV D_8011CB40[];

void func_8010ACC0(u8 *a)
{
    s16 v[6];
    v[1] = *(s16 *)(a + 0x2E);
    v[3] = D_1F8001A4 + 0x28;
    v[5] = *(s16 *)(a + 0x36);
    func_8003116C(8, v, -0x50);
    func_80074590(7, 0, 0);
}

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_8010AD1C);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_8010AF40);


void func_8010B100(void) {
}


void func_8010B108(void) {
}

typedef struct { u16 lo; u16 hi; } Fix;
typedef struct {
    Fix at[3];
    Fix pos[3];
    s16 dir[3];
    u8 pad1E[0x2A];
    u8 m[0x20];
} Cam;
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
extern Spawn *D_80117508[];
extern Pos D_800BF808_76d5;
typedef struct { u8 x, y, z; s8 t; } Spark;
typedef struct { s16 a, b, c, d; } S8;
typedef struct { s16 x, y, z; } V3;
typedef struct { s16 x, y, z, pad; } SVec;
typedef struct { u16 x, p0, y, p1, z, p2; } LVec;
typedef struct { u16 a, b; } Range;

void func_8010B110(Owner *a, s32 sel)
{
    Spawn *e;
    u8 *p;
    a->count = 0;
    e = D_80117508[sel];
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
        e++;
    }
}

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
extern ClutCycle D_801175E0[];
extern s8 D_801258A8[];
typedef struct { s16 x, y, z, pad; } RingVec;
typedef struct { s16 pos; s16 vel; } RiseMotion;

void func_8010B288(s32 arg0) {
    ClutRect r;
    s32 i;
    ClutCycle *e;
    u8 *data;

    if (arg0 == 0) {
        for (i = 0; i < 1; i++) {
            D_801258A8[i] = 0;
        }
        return;
    }
    e = D_801175E0;
    for (i = 0; i < 1; i++, e++) {
        if (--D_801258A8[i] <= 0) {
            if (e->ptr[0] == 0xFF) {
                e->ptr -= e->ptr[1];
            }
            data = e->clut + e->ptr[0] * 32;
            D_801258A8[i] = e->ptr[1];
            r.x = e->x;
            r.y = e->y;
            r.w = 16;
            r.h = 1;
            func_80081218(&r, data);
            e->ptr += 2;
        }
    }
}


void func_8010B3A8(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 4);
    switch (temp_v1) {                              /* irregular */
    case 0:
        M2C_FIELD(arg0, u8 *, 4) = 1U;
        func_8010B110(arg0, 0U);
        func_8010B288(0);
        func_801129FC();
        func_800752B4(0);
        func_80075D24(0x1FFF);
        return;
    case 1:
        if (func_80026AD0(arg0) != 0) {
            func_8010B110(arg0, M2C_FIELD(arg0, u8 *, 3));
        }
        func_80026A68(arg0);
        func_8010B288(1);
        return;
    case 3:
        func_8007ADD0(arg0);
        /* fallthrough */
    case 2:
        return;
    }
}

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_8010B480);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_8010B6A4);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_8010B874);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_8010B960);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_8010BA70);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_8010C11C);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_8010C7B0);

extern u8 D_800BF809;
extern s16 D_1F800160_71b4;
extern s16 D_1F800164_d75f;

void func_8010D014(u8 *a)
{
    s32 s;
    if (D_800BF809 != 0) {
        return;
    }
    switch (s = a[6]) {
    case 0:
        func_80041768(a, 0xB, 4);
        func_80074590(0x8A, 0, 0);
        *(s16 *)(a + 0x40) = 0x5A;
        a[6]++;
        break;
    case 1:
        if (*(s16 *)(a + 0x40) < 0x1E && func_8010B874(a) != 0) {
            a[0] = 2;
            func_80041768(a, 3, 4);
            func_8010B960(a);
            a[5] = s;
            a[6] = s;
            a[7] = 0;
            break;
        }
        if (--*(s16 *)(a + 0x40) == 0) {
            func_80041768(a, 0, 0xA);
            a[5] = 0;
            a[6] = 0;
            *(s16 *)(a + 0x64) = 0;
        }
        *(s16 *)(a + 0x56) = func_800776F8((s16)func_800782B0(a + 0x2C, D_1F800160_71b4, D_1F800164_d75f), *(s16 *)(a + 0x56), 0x80);
        break;
    }
}

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_8010D158);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_8010DE5C);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_8010E070);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", f_SpawnEarthEvilPigDetachedPartsActor);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_8010E5EC);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", f_UpdateEarthEvilPigSplitActor);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", f_UpdateEarthEvilPigDetachedPartsAttack);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_8010FA2C);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_8010FDA8);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_8010FEBC);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_801103AC);

extern u8 *volatile D_1F800260;
extern u8 D_1F80025A;
extern M2C_UNK f_UpdateEarthEvilPigSplitActor;

s32 func_80110618(u8 *a, s32 k)
{
    u8 *p = func_80072DDC(a, 4, 2, 0x40);
    D_1F800260 = p;
    if (p != 0) {
    *(void **)(p + 0x1C) = &f_UpdateEarthEvilPigSplitActor;
    p[3] = k;
    *(s16 *)(p + 0x2E) = *(s16 *)(a + 0x2E);
    *(s16 *)(p + 0x32) = *(s16 *)(a + 0x32) + 0x12C;
    *(s16 *)(p + 0x36) = *(s16 *)(a + 0x36);
    p[0x2A] = a[0x2A];
    p[0xBE] = a[0xBE];
    D_1F80025A++;
    return 1;
    }
    return 0;
}

extern M2C_UNK func_8010FEBC;
void func_801106C8(void *arg0) {
    M2C_FIELD(arg0, M2C_UNK **, 0x1C) = &func_8010FEBC;
    M2C_FIELD(arg0, s8 *, 2) = 0x68;
    M2C_FIELD(arg0, s8 *, 4) = 1;
    M2C_FIELD(arg0, s8 *, 5) = 7;
    M2C_FIELD(arg0, s16 *, 0x80) = 0x64;
    M2C_FIELD(arg0, s16 *, 0x82) = 0xC8;
    M2C_FIELD(arg0, s16 *, 0x84) = 0xAA;
    M2C_FIELD(arg0, s16 *, 0x86) = 0x1A4;
    M2C_FIELD(arg0, s8 *, 6) = 0;
    M2C_FIELD(arg0, s8 *, 7) = 0;
    M2C_FIELD(arg0, s16 *, 0x58) = 0;
    M2C_FIELD(arg0, s16 *, 0x56) = 0;
    M2C_FIELD(arg0, s16 *, 0x54) = 0;
    M2C_FIELD(arg0, s16 *, 0xB8) = 0x1000;
    M2C_FIELD(arg0, s16 *, 0xBA) = 0x1000;
    M2C_FIELD(arg0, s16 *, 0xBC) = 0x1000;
    M2C_FIELD(arg0, s8 *, 0x29) = 0;
    M2C_FIELD(arg0, s8 *, 0x1B) = 0;
    M2C_FIELD(arg0, s8 *, 0x2B) = 0;
}


void func_80110740(void *arg0) {
    M2C_FIELD(arg0, M2C_UNK **, 0x1C) = &f_UpdateEarthEvilPigSplitActor;
    M2C_FIELD(arg0, s8 *, 2) = 0x40;
    M2C_FIELD(arg0, s8 *, 5) = 1;
    M2C_FIELD(arg0, s16 *, 0x80) = 0x32;
    M2C_FIELD(arg0, s16 *, 0x82) = 0x64;
    M2C_FIELD(arg0, s16 *, 0x84) = 0x46;
    M2C_FIELD(arg0, s16 *, 0x86) = 0xAA;
    M2C_FIELD(arg0, s8 *, 4) = 0;
    M2C_FIELD(arg0, s8 *, 6) = 0;
    M2C_FIELD(arg0, s8 *, 7) = 0;
    M2C_FIELD(arg0, s16 *, 0x58) = 0;
    M2C_FIELD(arg0, s16 *, 0x56) = 0;
    M2C_FIELD(arg0, s16 *, 0x54) = 0;
    M2C_FIELD(arg0, s16 *, 0xB8) = 0x800;
    M2C_FIELD(arg0, s16 *, 0xBA) = 0x800;
    M2C_FIELD(arg0, s16 *, 0xBC) = 0x800;
    M2C_FIELD(arg0, s8 *, 0x29) = 0;
    M2C_FIELD(arg0, s8 *, 3) = 0;
}

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_801107B0);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_801108F0);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_80110A98);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_80110C14);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_80110DBC);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_80111034);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_80111244);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_80111418);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_80111574);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_80111708);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_80111A68);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_80111C94);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_80111DA8);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_80111F54);

extern S8 D_80125ACC[];
extern s32 D_801258AC[];
extern u8 D_8012592C[];

void func_801120F8(u8 *a)
{
    s32 i;
    s32 c, g, b;
    for (i = 0; i < 0x20; i++) {
        c = ((0x20 - i) * a[5]) / 32 + 1;
        g = c - (c >> 4);
        b = c - (c >> 3);
        if (D_80125ACC[i].d == 0) {
            D_801258AC[i] = 0;
            if (i != 0) {
                D_801258AC[i - 1] = 0;
            }
            if (i != 0x1F) {
                D_801258AC[i + 1] = 0;
            }
            break;
        }
        if (i < 2) {
            D_801258AC[i] = 0;
            D_8012592C[i] = 0x10;
        } else {
            D_801258AC[i] = (b << 16) | (g << 8) | c;
            D_8012592C[i] = 0x21 - i;
        }
    }
    func_80029664(D_80125ACC, i, D_801258AC, D_8012592C);
}

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_80112210);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_801123A4);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_801124E0);


void func_801129FC(void)
{
    u32 i;
    for (i = 0; i < 6; i++) {
        func_80031220(0xE01, &D_8011CB40[i], D_8011CB40[i].pad);
    }
    func_80111418();
}


void func_80112A58(u8 *a)
{
    switch (a[4]) {
    case 0:
        *(s32 *)(a + 0x48) = 0;
        *(s32 *)(a + 0x4C) = 0;
        H(a, 0x4A) = func_8009A450();
        a[7] = 0xFF;
        a[4] = 1;
        H(a, 0x32) = -0x1E;
    case 1:
        if (++a[7] >= 8) {
            a[4] = 2;
        } else {
            a[1] = 1;
        }
        break;
    case 2:
    case 3:
        func_8007A624(a);
        break;
    }
}


void func_80112B1C(u8 *a)
{
    switch (a[4]) {
    case 0:
        a[7] = 0xFF;
        *(s32 *)(a + 0x48) = 0;
        *(s32 *)(a + 0x4C) = 0;
        a[4] = 1;
        *(s16 *)(a + 0x32) = -0x1E;
    case 1:
        if (++a[7] >= 8) {
            a[4] = 2;
        } else {
            a[1] = 1;
        }
        break;
    case 2:
    case 3:
        func_8007A624(a);
        break;
    }
}

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_80112BC4);


void func_80112D34(u8 *a)
{
    switch (a[4]) {
    case 0:
        a[4]++;
        a[7] = 0;
        *(s32 *)(a + 0x48) = func_8009A450();
        *(s32 *)(a + 0x4C) = func_8009A450();
    case 1:
        if (++a[7] >= 0x10) {
            a[4] = 2;
        } else {
            a[1] = 1;
        }
        break;
    case 2:
    case 3:
        func_8007A624(a);
        break;
    }
}

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_80112DE4);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_801131B0);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_80113628);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_80113748);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_801139EC);


void func_80113D20(u32 *p, void *b)
{
    u32 lo = *p;
    u32 packed;

    packed = lo;
    lo = packed & 0xFFFF;
    p += 4;
    func_801139EC(func_80113748(p, b, lo), b, packed >> 16);
}

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_80113D68);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_80114020);

extern u16 *D_800ECF78;

void func_80114560(u8 *a)
{
    u16 *p = D_800ECF78;
    u16 t;

    *(u16 **)(a + 0xC) = p;
    *(u16 *)(a + 8) = p[0];
    t = p[1];
    a[7] = 0;
    *(u16 *)(a + 0xA) = t;
}

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_8011458C);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_80114760);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_801149F0);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_80114BBC);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_80114CA0);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_80114F68);

extern Cam D_1F8000D0;
extern SVec D_1F8000C0;
extern LVec D_1F8000A0;
extern void *D_801250A8[];

s32 func_801151A8(u8 *a)
{
    switch (a[6]) {
    case 0:
        a[6]++;
        D_1F8000C0.x = 0;
        D_1F8000C0.y = -0x690;
        D_1F8000C0.z = 0x3E8;
        func_80084470(D_1F8000D0.m, &D_1F8000C0, &D_1F8000A0);
        *(u16 *)(a + 0x2E) = D_1F8000D0.pos[0].hi + D_1F8000A0.x;
        *(u16 *)(a + 0x32) = D_1F8000D0.pos[1].hi + D_1F8000A0.y;
        *(u16 *)(a + 0x36) = D_1F8000D0.pos[2].hi + D_1F8000A0.z;
        func_80040CDC(a, 0, D_801250A8[D_800BF870.unk0 - 10]);
        a[0x70] = 1;
        goto end;
    case 1:
        func_80041098(a);
        if (a[0x70] == 0xFF) {
            return 1;
        }
    end:
    default:
        return 0;
    }
}

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_801152CC);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_8011568C);

extern s8 D_1F800160[];
extern s8 D_1F800164[];
extern s8 D_1F800246[];
extern s8 D_1F80024C[];

void func_801157D0(void *arg0) {
    M2C_UNK var_a0;
    void *temp_s1;

    temp_s1 = *((void **)D_1F80024C);
    if (*((u8 *)D_1F800246) == 0) {
        M2C_FIELD(arg0, u8 *, 5) = 0U;
        M2C_FIELD(arg0, s8 *, 6) = 0;
        M2C_FIELD(arg0, s8 *, 7) = 2;
        M2C_FIELD(arg0, s16 *, 0x64) = 0;
        M2C_FIELD(arg0, u16 *, 0x56) = (u16) M2C_FIELD(arg0, u16 *, 0x62);
    } else {
        M2C_FIELD(arg0, u16 *, 0x56) = func_800776F8((s16) (func_800782B0(arg0 + 0x2C, *((s16 *)D_1F800160), *((s16 *)D_1F800164)) - 0x400), (s16) M2C_FIELD(arg0, u16 *, 0x56), 0x80);
        M2C_FIELD(M2C_FIELD(arg0, void **, 0xC0), s16 *, 8) = func_800776F8(0, M2C_FIELD(M2C_FIELD(arg0, void **, 0xC0), s16 *, 8), 0x80);
        func_80114CA0(arg0);
        if (M2C_FIELD(arg0, u8 *, 0x29) != 0) {
            var_a0 = 0x88;
            if (M2C_FIELD(temp_s1, s16 *, 0x6E) == 1) {
                var_a0 = 0x89;
            }
            func_80074590(var_a0, 0, 0);
            M2C_FIELD(arg0, s8 *, 6) = 0;
            M2C_FIELD(arg0, s16 *, 0x64) = 0;
            M2C_FIELD(arg0, s8 *, 7) = 3;
            M2C_FIELD(arg0, u8 *, 5) = (u8) (M2C_FIELD(arg0, u8 *, 5) + 1);
        }
    }
    M2C_FIELD(arg0, s16 *, 0x32) = (s16) (M2C_FIELD(arg0, u16 *, 0x7C) + (func_80083E80(M2C_FIELD(arg0, s16 *, 0x60)) >> 4));
    M2C_FIELD(arg0, s16 *, 0x60) = (s16) (((u16) M2C_FIELD(arg0, s16 *, 0x60) + 0x40) & 0xFFF);
}

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_801158FC);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_80115CC0);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_80116198);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_801162F4);

extern u8 D_800E806E;

s32 func_80116810(u8 *p)
{
    switch (p[0x78]) {
    case 0:
        p[0x78]++;
        func_8006E1C0(8);
        g_CameraState.focusX = *(u16 *)(p + 0x2E);
        g_CameraState.focusY = *(u16 *)(p + 0x32) + 0x4B0;
        g_CameraState.focusZ = *(u16 *)(p + 0x36);
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

extern s16 D_80124F34[];
extern s16 D_800E8046;

s32 func_801168A0(u8 *p)
{
    s16 y;

    switch (p[0x78]) {
    case 0:
        p[0x78]++;
        *(s32 *)(p + 0x38) = func_8003116C(D_80124F34[D_800BF870.unk0 - 10], p + 0x2C, -0x32);
        goto end;
    case 1:
        y = *(u16 *)(p + 0x32) + 0x10;
        *(s16 *)(p + 0x32) = y;
        *(s16 *)(*(u8 **)(p + 0x38) + 0x2E) = y;
        if (*(s16 *)(p + 0x32) >= D_800E8046 - 0xF0) {
            return 1;
        }
    end:
    default:
        return 0;
    }
}


s32 func_8011694C(void *arg0) {
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x38), s8 *, 4) = 2;
    func_80074590(0x37, 0x16, 0);
    return 1;
}

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_80116980);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_80116B9C);

extern Range D_80125748[];
extern Range D_80125760[];
extern Range D_8012578C[];
extern Range D_801257C4[];
extern u8 *D_1F80021C;

void func_80116EE0(s16 kind, s16 idx)
{
    Range *t;
    s32 n, base;
    u8 *p;
    switch (kind) {
    case 0:
        t = D_80125748;
        n = 3;
        base = 0;
        break;
    case 1:
        t = D_80125760;
        n = 0x9;
        base = 0x19A;
        break;
    case 2:
        t = D_8012578C;
        n = 0x1F;
        base = 0x1C8;
        break;
    case 3:
        t = D_801257C4;
        n = 9;
        base = 0x272;
        break;
    default:
        return;
    }
    p = D_1F80021C + t[idx].a * 32 + base * 32;
    func_8001D2A8(n, p, p + (t[idx].b + 1) * 32, 0);
}

extern s16 D_800BED82;
extern M2C_UNK D_80125160;
void func_80116FC8(void) {
    func_80075448(0xA, &D_80125160, 0x10, D_800BED82);
}

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_80116FFC);

void func_80116FFC();

u8 *func_80117378(s32 a)
{
    u8 *p = func_8007A980(1, 2, 0);
    if (p == 0) {
        return 0;
    }
    *(void **)(p + 0x1C) = func_80116FFC;
    p[2] = 0x51;
    p[3] = a;
    return p;
}

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_801173CC);

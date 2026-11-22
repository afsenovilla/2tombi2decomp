#include "common.h"
#include "game.h"
#include "m2c.h"

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_801092D4);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_8010940C);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_80109648);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_801097BC);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_80109AA0);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_80109E04);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_8010A138);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_8010A55C);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_8010A870);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_8010A9A4);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_8010AB14);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_8010AD5C);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_8010AFF8);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_8010B174);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_8010B36C);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_8010B558);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_8010B888);

extern void *D_1F800080;
extern u8 D_1F800182_5650;
extern u16 D_1F800164_7d8c;
extern u16 D_1F800160_3621;
extern u8 D_1F800137_104c;
extern s8 D_800BF808[];

void func_8010BA30(u8 *a)
{
    u16 v, m;
    if (D_1F800137_104c == 0 && D_800BF808[5] == 0) {
        v = *(u16 *)(a + 0x6A);
        m = v & 0xF00;
        if (v & 0x8000) {
            *(u16 *)(a + 0x6A) = 0;
            D_800BF808[0x16] = 0;
            if (m == 0x700) {
                a[0] = 3;
                a[4] = 2;
                a[5] = 5;
                a[6] = 0;
                a[7] = 0;
            }
        }
    }
}


void func_8010BAA4(u8 *a, u8 *b)
{
    if (func_80024BD8(a, b, *(void **)(b + 0xC0)) != 0) {
        b[0x29] = 1;
        a[0x164] = 3;
        D_1F800080 = b;
        D_1F800182_5650 = 0;
    }
}


s32 func_8010BAFC(s32 arg0, s32 arg1) {
    return func_80109AA0(arg0, arg1, M2C_FIELD(arg1, s32 *, 0xC0));
}


s32 func_8010BB20(s32 arg0, s32 arg1) {
    return func_8001F650(arg0, arg1, M2C_FIELD(arg1, s32 *, 0xC0));
}


void func_8010BB44(u8 *a, u8 *b)
{
    u16 t, u;
    if (func_80024BD8(a, b, *(void **)(b + 0xC0)) != 0) {
        t = *(u16 *)(b + 0x80);
        b[0x29] = 1;
        u = *(u16 *)(a + 0x80);
        a[0x164] = 1;
        a[0x15C] = 0;
        D_1F800080 = b;
        D_1F800182_5650 = 0;
        *(u16 *)(a + 0x152) = t + u - 0xC;
    }
}


void func_8010BBB0(u8 *a, u8 *b)
{
    if (func_8010A870(a, b, *(void **)(b + 0xC0)) != 0) {
        D_1F800080 = b;
        a[0x15C] = 0;
        a[0x164] = 1;
        b[0x29] = 1;
    }
}

extern s32 D_1F80009C;

void func_8010BC00(u8 *a, void *b)
{
    if (func_80022F04(a, b) != 0) {
        a[0x2B] = D_1F80009C >> 4;
        func_80022D08(a, b, 1, 0);
    }
}


void func_8010BC58(void *a, void *b)
{
    s32 r = func_8001F40C(a, b, 1);
    if (r >= 0) {
        func_8001FF7C(a, b, r, 1);
    }
}

extern s8 D_1F800182[];

void func_8010BCA4(s32 arg0, M2C_UNK arg1) {
    if ((func_80022F04() != 0) && !(func_8001DC9C(arg0, arg1, 0, 0) & 0x80)) {
        *((s8 *)D_1F800182) = 0;
    }
}


void func_8010BCFC(s32 arg0, void *arg1) {
    if (func_80022F04() != 0) {
        M2C_FIELD(arg1, s8 *, 0x2B) = 1;
    }
}

#define H(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define U(p, o) (*(u16 *)((u8 *)(p) + (o)))

void func_8010BD2C(u8 *a, u8 *b, u8 *c)
{
    s16 dx, dz;
    dx = H(a, 0x2E) - H(c, 0x2C);
    dz = H(a, 0x36) - H(c, 0x34);
    if ((u16)func_80084080(dx * dx + dz * dz) <= H(a, 0x80) + H(b, 0x80)) {
        if ((u16)(U(a, 0x32) - U(c, 0x30) + (U(b, 0x84) + U(a, 0x86) - U(a, 0x84))) <= H(a, 0x86) + H(b, 0x86)) {
            a[0x29] = 1;
        }
    }
}

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_8010BE10);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_8010BF40);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_8010C114);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_8010C268);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_8010C628);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_8010C7EC);

extern s8 D_1F80027E[];
extern u8 D_800BFA1A;

void func_8010CC28(void *arg0) {
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
    if (!(D_800BFA1A & 4)) {
        func_80042354(1, 5);
        func_8001CF2C();
        M2C_FIELD(arg0, s8 *, 4) = 4;
    }
}

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_8010CCCC);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_8010CDA4);


void func_8010CE90(u8 *a, void *b)
{
    u8 *c = *(u8 **)(a + 0x158);
    if (c[2] == 0x47) {
        func_8010C268(a, c, b);
    } else if (c[2] == 1) {
        func_8010C7EC(a, c, b);
    }
}

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_8010CEE4);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_8010D108);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_8010D2D8);


void func_8010D5E4(void) {
}


void func_8010D5EC(void) {
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
extern Spawn *D_80118C70[];
extern Pos D_800BF808_76d5;
typedef struct { u8 x, y, z; s8 t; } Spark;
typedef struct { s16 a, b, c, d; } S8;
typedef struct { s16 x, y, z, pad; } SV;
typedef struct { s16 x, y, z; } V3;
typedef struct { s16 x, y, z, pad; } SVec;
typedef struct { u16 x, p0, y, p1, z, p2; } LVec;
typedef struct { u16 a, b; } Range;

void func_8010D5F4(Owner *a, s32 sel)
{
    Spawn *e;
    u8 *p;
    a->count = 0;
    e = D_80118C70[sel];
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


void func_8010D76C(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 4);
    switch (temp_v1) {                              /* irregular */
    case 0:
        M2C_FIELD(arg0, u8 *, 4) = 1U;
        func_8010D5F4(arg0, 0U);
        func_800752B4(0);
        func_80075D24(0x1FFF);
        return;
    case 1:
        if (func_80026AD0(arg0) != 0) {
            func_8010D5F4(arg0, M2C_FIELD(arg0, u8 *, 3));
        }
        func_80026A68(arg0);
        return;
    case 3:
        func_8007ADD0(arg0);
        /* fallthrough */
    case 2:
        return;
    }
}

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_8010D82C);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_8010DA50);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", f_TestTombaOverlapsEvilPig);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_8010DD0C);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_8010DE1C);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_8010E4C8);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_8010EB5C);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_8010F3C0);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_8010F504);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_80110208);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_8011041C);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_80110714);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", f_UpdateGhostEvilPigRandomRicochetVolley);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", f_UpdateGhostEvilPigGraspAttack);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", f_UpdateGhostEvilPigTripleRicochetVolley);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_80110FE8);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_801114C4);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_801116A8);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_80111964);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_80111E1C);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_801125A8);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_801127D4);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_801128E8);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_80112A94);

extern S8 D_80126BD8[];
extern s32 D_801268C8[];
extern u8 D_80126948[];

void func_80112C38(u8 *a)
{
    s32 i;
    s32 c, g, b;
    for (i = 0; i < 0x20; i++) {
        c = ((0x20 - i) * a[5]) / 32 + 1;
        g = c - (c >> 4);
        b = c - (c >> 3);
        if (D_80126BD8[i].d == 0) {
            D_801268C8[i] = 0;
            if (i != 0) {
                D_801268C8[i - 1] = 0;
            }
            if (i != 0x1F) {
                D_801268C8[i + 1] = 0;
            }
            break;
        }
        if (i < 2) {
            D_801268C8[i] = 0;
            D_80126948[i] = 0x10;
        } else {
            D_801268C8[i] = (b << 16) | (g << 8) | c;
            D_80126948[i] = 0x21 - i;
        }
    }
    func_80029664(D_80126BD8, i, D_801268C8, D_80126948);
}

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_80112D50);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_80112EE4);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_80113020);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_8011353C);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_801135E0);


void func_801136D8(u8 *a)
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

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_80113788);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_80113A54);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_80113DB4);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_80113EB4);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_80114158);


void func_8011448C(u32 *p, void *b)
{
    u32 lo = *p;
    u32 packed;

    packed = lo;
    lo = packed & 0xFFFF;
    p += 4;
    func_80114158(func_80113EB4(p, b, lo), b, packed >> 16);
}

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_801144D4);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_8011478C);

extern u16 *D_800ECF78;

void func_80114CCC(u8 *a)
{
    u16 *p = D_800ECF78;
    u16 t;

    *(u16 **)(a + 0xC) = p;
    *(u16 *)(a + 8) = p[0];
    t = p[1];
    a[7] = 0;
    *(u16 *)(a + 0xA) = t;
}

extern s8 D_1F800137[];
extern s8 D_1F800162[];

void func_80114CF8(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 4);
    switch (temp_v1) {                              /* irregular */
    case 0:
        if (func_80051B70(arg0, 0xC, 1) == 0) {
            M2C_FIELD(arg0, s16 *, 0x80) = 0x20;
            M2C_FIELD(arg0, s16 *, 0x82) = 0x40;
            M2C_FIELD(arg0, s8 *, 0) = 1;
            M2C_FIELD(arg0, s16 *, 0x84) = 0;
            M2C_FIELD(arg0, s16 *, 0x86) = 0x87C;
            M2C_FIELD(arg0, u8 *, 4) = (u8) (M2C_FIELD(arg0, u8 *, 4) + 1);
            func_800517F8(arg0);
            return;
        }
    case 2:
        return;
    case 1:
        if (*((u8 *)D_1F800137) != 0) {
            func_8007778C(arg0);
            return;
        }
        func_800778E4(arg0, (s16) (*((u16 *)D_1F800162) - M2C_FIELD(arg0, u16 *, 0x32)));
        return;
    case 3:
        func_8007A624(arg0);
        break;
    }
}

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_80114E00);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_80115048);


void func_80115228(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 4);
    switch (temp_v1) {                              /* irregular */
    case 0:
        if (func_80051B70(arg0, 0xC, 0) == 0) {
            M2C_FIELD(arg0, s16 *, 0x80) = 0x8C;
            M2C_FIELD(arg0, s16 *, 0x82) = 0x118;
            M2C_FIELD(arg0, s16 *, 0x84) = 0xCB;
            M2C_FIELD(arg0, s8 *, 0) = 1;
            M2C_FIELD(arg0, s16 *, 0x86) = 0x190;
            M2C_FIELD(arg0, u8 *, 4) = (u8) (M2C_FIELD(arg0, u8 *, 4) + 1);
            return;
        }
    case 2:
        return;
    case 1:
        if (func_8007778C(arg0) != 0) {
            func_800517F8(arg0);
            return;
        }
        break;
    case 3:
        func_8007A624(arg0);
        break;
    }
}

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_80115300);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_801153E4);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_801156AC);

extern Cam D_1F8000D0;
extern SVec D_1F8000C0;
extern LVec D_1F8000A0;
extern void *D_80126100[];

s32 func_801158EC(u8 *a)
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
        func_80040CDC(a, 0, D_80126100[D_800BF870.unk0 - 10]);
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

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_80115A10);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_80115DD0);

extern s8 D_1F800160[];
extern s8 D_1F800164[];
extern s8 D_1F800246[];
extern s8 D_1F80024C[];

void func_80115F14(void *arg0) {
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
        func_801153E4(arg0);
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

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_80116040);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_80116404);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_801168DC);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_80116A38);

extern u8 D_800E806E;

s32 func_80116FAC(u8 *p)
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

extern s16 D_80125F8C[];
extern s16 D_800E8046;

s32 func_8011703C(u8 *p)
{
    s16 y;

    switch (p[0x78]) {
    case 0:
        p[0x78]++;
        *(s32 *)(p + 0x38) = func_8003116C(D_80125F8C[D_800BF870.unk0 - 10], p + 0x2C, -0x32);
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


s32 func_801170E8(void *arg0) {
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x38), s8 *, 4) = 2;
    func_80074590(0x37, 0x16, 0);
    return 1;
}


void func_8011711C(void *arg0) {
    M2C_FIELD(arg0, s16 *, 0x2E) = (s16) (((s32) (func_80083F50(M2C_FIELD(arg0, s16 *, 0x76)) * 0x4B0) >> 0xC) + 0x1600);
    M2C_FIELD(arg0, s16 *, 0x36) = (s16) (0x12C0 - ((s32) (func_80083E80(M2C_FIELD(arg0, s16 *, 0x76)) * 0x4B0) >> 0xC));
}

extern Range D_801267C8[];
extern Range D_801267E0[];
extern Range D_80126800[];
extern Range D_80126838[];
extern u8 *D_1F80021C;

void func_80117194(s16 kind, s16 idx)
{
    Range *t;
    s32 n, base;
    u8 *p;
    switch (kind) {
    case 0:
        t = D_801267C8;
        n = 3;
        base = 0;
        break;
    case 1:
        t = D_801267E0;
        n = 0x1E;
        base = 0x1C5;
        break;
    case 2:
        t = D_80126800;
        n = 0x1F;
        base = 0x1C8;
        break;
    case 3:
        t = D_80126838;
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
extern M2C_UNK D_801261E0;
void func_8011727C(void) {
    func_80075448(0xA, &D_801261E0, 0x10, D_800BED82);
}

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_801172B0);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_80117788);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_8011787C);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_8011796C);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_80117AC8);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_80117B84);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_80117BF4);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", f_UpdateGhostEvilPigRicochetProjectile);

extern s16 D_1F8001A6;

u8 func_80118168(u8 *a)
{
    if (a[0x29] == 0) {
        a[0x29] = func_800495DC(a, 0, 0);
        if (a[0x29] != 0 && (D_1F8001A6 & 0x8000)) {
            a[0x5E] = 1;
        }
    }
    return a[0x29];
}


void func_801181CC(void *arg0) {
    s16 temp_s1;
    s32 temp_lo;
    s32 temp_s2;

    temp_s1 = M2C_FIELD(arg0, s16 *, 0x60);
    temp_s2 = func_80083F50(temp_s1) * M2C_FIELD(arg0, s16 *, 0x4E);
    temp_lo = -func_80083E80(temp_s1) * M2C_FIELD(arg0, s16 *, 0x4E);
    M2C_FIELD(arg0, s32 *, 0x30) = (s32) (M2C_FIELD(arg0, s32 *, 0x30) + (M2C_FIELD(arg0, s16 *, 0x50) << 0xC));
    M2C_FIELD(arg0, s16 *, 0x50) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0x50) + 0x2D);
    M2C_FIELD(arg0, s32 *, 0x2C) = (s32) (M2C_FIELD(arg0, s32 *, 0x2C) + temp_s2);
    M2C_FIELD(arg0, s32 *, 0x34) = (s32) (M2C_FIELD(arg0, s32 *, 0x34) + temp_lo);
}

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", f_SpawnGhostEvilPigRicochetProjectile);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_8011836C);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", f_UpdateGhostEvilPigGraspActor);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", f_SpawnGhostEvilPigGraspActor);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_80118B54);

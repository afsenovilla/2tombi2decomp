#include "common.h"
#include "game.h"
#include "m2c.h"

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_80109320);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_80109458);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_80109694);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_80109808);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_80109AEC);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_80109C64);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_80109ED8);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_8010A2D4);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_8010A47C);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_8010A5F8);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_8010A7A8);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_8010AB94);

extern void *D_1F800080;
extern u8 D_1F800182;
extern u16 D_1F800164_7d8c;
extern u16 D_1F800160_3621;
extern u8 D_1F800137;
extern s8 D_800BF808[];

void func_8010ACE4(u8 *a)
{
    u16 v, m;
    if (D_1F800137 == 0 && D_800BF808[5] == 0) {
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

extern void *D_1F800080;
extern u8 D_1F800182;

void func_8010AD58(u8 *a, u8 *b)
{
    if (func_80109AEC(a, b, *(void **)(b + 0xC0)) != 0) {
        a[0x164] = 3;
        D_1F800080 = b;
        D_1F800182 = 0;
    }
}


void func_8010ADA8(u8 *a, u8 *b)
{
    u16 t, u;
    if (b[0x47] != 2 && func_80024BD8(a, b, *(void **)(b + 0xC0)) != 0) {
        t = *(u16 *)(b + 0x80);
        b[0x29] = 1;
        u = *(u16 *)(a + 0x80);
        a[0x164] = 1;
        a[0x15C] = 0;
        D_1F800080 = b;
        D_1F800182 = 0;
        *(u16 *)(a + 0x152) = t + u - 0xC;
    }
}


void func_8010AE24(void *a, u8 *b)
{
    if (b[0x47] == 2) {
        func_80109808(a, b, *(void **)(b + 0xC0));
    } else {
        func_8001F650(a, b, *(void **)(b + 0xC0));
    }
}

extern u8 *D_800E7FD8;

void func_8010AE6C(u8 *a, u8 *b)
{
    if (b[0x47] != 2 && (a[2] != 0 || b != D_800E7FD8)) {
        func_80020F7C(a, b, *(void **)(b + 0xC0), 0x1200);
    }
}


s32 func_8010AEC0(s32 arg0, s32 arg1) {
    return func_80109ED8(arg0, arg1, M2C_FIELD(arg1, s32 *, 0xC0));
}


void func_8010AEE4(void *arg0, void *arg1) {
    u16 var_v0;

    if (func_80022F04() != 0) {
        if (M2C_FIELD(arg1, u8 *, 0x46) & 1) {
            var_v0 = M2C_FIELD(arg0, u16 *, 0x140) + 0x800;
        } else {
            var_v0 = M2C_FIELD(arg0, u16 *, 0x140);
        }
        M2C_FIELD(arg0, s8 *, 0x2B) = (s8) (var_v0 >> 4);
        func_80022D08(arg0, arg1, 1, 0);
    }
}

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_8010AF60);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_8010B078);


void func_8010B194(void *arg0, void *arg1) {
    s32 temp_lo;
    s32 temp_s0;
    s32 temp_s0_2;
    s32 temp_s2_2;
    s32 temp_s3;
    void *temp_s2;

    temp_s2 = M2C_FIELD(arg0, void **, 0x10);
    M2C_FIELD(arg0, u16 *, 0x32) = (u16) (M2C_FIELD(temp_s2, u16 *, 0x30) + ((s32) (func_80083F50(M2C_FIELD(temp_s2, s16 *, 0xC)) * M2C_FIELD(arg0, s16 *, 0x156)) >> 0xC));
    M2C_FIELD(arg0, u16 *, 0x32) = (u16) (M2C_FIELD(arg0, u16 *, 0x32) + ((s32) (func_80083F50(M2C_FIELD(arg0, s16 *, 0x58)) * M2C_FIELD(arg0, s16 *, 0x64)) >> 0xC));
    temp_s0 = (s32) (func_80083E80(M2C_FIELD(temp_s2, s16 *, 0xC)) * M2C_FIELD(arg0, s16 *, 0x156)) >> 0xC;
    temp_s3 = (s32) (func_80083E80(M2C_FIELD(arg1, s16 *, 0x56)) * (s16) temp_s0) >> 0xC;
    M2C_FIELD(arg0, u16 *, 0x2E) = (u16) (M2C_FIELD(temp_s2, u16 *, 0x2C) - ((s32) (func_80083F50(M2C_FIELD(arg1, s16 *, 0x56)) * (s16) temp_s0) >> 0xC));
    M2C_FIELD(arg0, u16 *, 0x36) = (u16) (M2C_FIELD(temp_s2, u16 *, 0x34) + temp_s3);
    temp_s0_2 = (s32) (func_80083E80(M2C_FIELD(arg0, s16 *, 0x58)) * M2C_FIELD(arg0, s16 *, 0x64)) >> 0xC;
    temp_s2_2 = (s32) (func_80083E80(M2C_FIELD(arg0, s16 *, 0x56)) * (s16) temp_s0_2) >> 0xC;
    temp_lo = func_80083F50(M2C_FIELD(arg0, s16 *, 0x56)) * (s16) temp_s0_2;
    M2C_FIELD(arg0, u16 *, 0x36) = (u16) (M2C_FIELD(arg0, u16 *, 0x36) + temp_s2_2);
    M2C_FIELD(arg0, u16 *, 0x2E) = (u16) (M2C_FIELD(arg0, u16 *, 0x2E) - (temp_lo >> 0xC));
}

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_8010B2F8);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_8010B4E8);

extern s8 D_1F80027E[];
extern u8 D_800BFA1A;

void func_8010B960(void *arg0) {
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
    if (!(D_800BFA1A & 0x20)) {
        func_80042354(1, 5);
        func_8001CF2C();
        M2C_FIELD(arg0, s8 *, 4) = 4;
    }
}


s32 func_8010BA04(s32 arg0, s32 arg1) {
    s32 var_a3;
    void *temp_a1;

    temp_a1 = M2C_FIELD(arg0, void **, 0x158);
    var_a3 = 0;
    if ((M2C_FIELD(temp_a1, u8 *, 0xC) == 4) && (M2C_FIELD(temp_a1, u8 *, 2) == 0x17)) {
        var_a3 = func_8010B4E8(arg0, (s32) temp_a1, arg1);
    }
    return var_a3;
}

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_8010BA54);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_8010BC78);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_8010BE48);


void func_8010C098(void) {
}


void func_8010C0A0(void) {
}

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_8010C0A8);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_8010C198);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_8010C2F4);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_8010C448);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_8010CA3C);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_8010CB8C);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_8010CD20);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_8010CE24);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", f_InitializeLastEvilPigCopiedWeaponProjectile);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_8010D4B8);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_8010D738);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_8010D830);

extern u8 D_8011A9E4[];
extern u16 D_8011A9D8[];
extern u8 D_800BF88C;
extern u8 D_800BF9EB;
extern s16 D_1F800268;

void func_8010D924(u8 *a)
{
    u16 v = D_8011A9D8[a[3]];
    *(u16 *)(a + 0x40) = 2;
    *(u16 *)(a + 0x44) = v;
}


void func_8010D94C(u8 *a)
{
    *(u16 *)(a + 0x76) = D_8011A9E4[a[3]];
}


s32 func_8010D968(void *a)
{
    return func_800495DC(a, 0, 0) > 0;
}


s32 func_8010D98C(u8 *a, s32 b, s32 c)
{
    if (func_8004766C(a) < 0) {
        func_80049760(a);
        return 1;
    }
    func_80049760(a);
    if (c != 0) {
        return 0;
    }
    if (b == 0 && a[0x2B] != 0) {
        return 0;
    }
    return func_800495DC(a, 0, 0) > 0;
}


s32 func_8010DA1C(u8 *a)
{
    s32 r;
    if (func_8004766C(a) < 0) {
        func_80049760(a);
        r = 1;
    } else {
        func_80049760(a);
        if (a[0x2B] != 0) {
            r = 0;
        } else {
            r = func_800495DC(a, 0, 0) > 0;
        }
    }
    if (r != 0) {
        a[0] = 2;
        a[0x2B] = 2;
        func_80074590(0xE, 0, 0);
        func_80031470(2, a + 0x2C, 0, a + 0x68);
        return 1;
    }
    return 0;
}

typedef struct { s16 x, y, z, pad; } SVec;
extern SVec D_1F8000C0;
extern SVec D_1F8000C8;
extern u8 *D_1F80024C_2bfb;
extern s16 D_1F800160_71b4;
extern s16 D_1F800162;
extern s16 D_1F800164_d75f;

void func_8010DAC4(u8 *a)
{
    u8 *t = D_1F80024C_2bfb;
    if (a[3] == 0) {
        D_1F8000C0.y = -0xB4;
    } else {
        D_1F8000C0.y = -0x3C;
    }
    D_1F8000C0.x = 0;
    D_1F8000C0.z = 0;
    func_800844C0(*(u8 **)(t + 0xE4) + 0x18, &D_1F8000C0, &D_1F8000C8);
    *(u16 *)(a + 0x2E) = *(u16 *)(*(u8 **)(t + 0xE4) + 0x2C) + D_1F8000C8.x;
    *(u16 *)(a + 0x32) = *(u16 *)(*(u8 **)(t + 0xE4) + 0x30) + D_1F8000C8.y;
    *(u16 *)(a + 0x36) = *(u16 *)(*(u8 **)(t + 0xE4) + 0x34) + D_1F8000C8.z;
}


void func_8010DB90(u8 *a)
{
    u8 *t;
    D_1F8000C0.x = 0;
    D_1F8000C0.y = -0xC8;
    D_1F8000C0.z = 0;
    t = D_1F80024C_2bfb;
    func_800844C0(*(u8 **)(t + 0xE4) + 0x18, &D_1F8000C0, &D_1F8000C8);
    *(u16 *)(a + 0x2E) = *(u16 *)(*(u8 **)(t + 0xE4) + 0x2C) + D_1F8000C8.x;
    *(u16 *)(a + 0x32) = *(u16 *)(*(u8 **)(t + 0xE4) + 0x30) + D_1F8000C8.y;
    *(u16 *)(a + 0x36) = *(u16 *)(*(u8 **)(t + 0xE4) + 0x34) + D_1F8000C8.z;
}


void func_8010DC48(void *arg0) {
    u8 temp_v1;

    if (M2C_FIELD(arg0, u8 *, 3) != 3) {
        temp_v1 = M2C_FIELD(arg0, u8 *, 0);
        if (temp_v1 == 2) {
            M2C_FIELD(arg0, u8 *, 0x2B) = temp_v1;
            M2C_FIELD(arg0, u8 *, 4) = temp_v1;
        }
    }
}


void func_8010DC78(u8 *a)
{
    s16 v[6];
    if (a[0] < 2 && (func_800495DC(a, 0, 0x5A) > 0 || func_800495DC(a, 0, 0) > 0)) {
        a[0] = 2;
        v[1] = *(s16 *)(a + 0x2E);
        v[3] = *(s16 *)(a + 0x32) + 0x5A;
        v[5] = *(s16 *)(a + 0x36);
        func_8003116C(a[3] + 0xD, v, -0x50);
        func_80031470(2, v, 0, a + 0x68);
        func_80074590(0x32, -3, 0x14);
    }
}

extern void *D_8011A9F8[];

void f_SpawnLastEvilPigCopiedWeaponProjectile(u8 *a, s32 b, s32 c)
{
    u8 *p = func_8007A980(3, 2, 0);
    u8 t;
    if (p != 0) {
        *(s16 *)(p + 0x2E) = *(s16 *)(a + 0x2E);
        *(s16 *)(p + 0x32) = *(s16 *)(a + 0x32);
        *(s16 *)(p + 0x36) = *(s16 *)(a + 0x36);
        p[0x46] = b;
        *(s16 *)(p + 0x54) = 0;
        *(s16 *)(p + 0x58) = 0;
        *(s16 *)(p + 0x56) = *(s16 *)(a + 0x56);
        *(void **)(p + 0x1C) = D_8011A9F8[c];
        t = a[0x2A];
        p[2] = 0xD3;
        p[3] = c;
        p[0x2A] = t;
    }
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
extern Spawn *D_8011AA4C[];
extern Pos D_800BF808_76d5;
typedef struct { u8 x, y, z; s8 t; } Spark;
typedef struct { s16 a, b, c, d; } S8;
typedef struct { s16 x, y, z, pad; } SV;
typedef struct { s16 x, y, z; } V3;
typedef struct { u16 x, p0, y, p1, z, p2; } LVec;
typedef struct { u16 a, b; } Range;

void func_8010DDE4(Owner *a, s32 sel)
{
    Spawn *e;
    u8 *p;
    a->count = 0;
    e = D_8011AA4C[sel];
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

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_8010DF5C);


void func_8010E084(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 4);
    switch (temp_v1) {                              /* irregular */
    case 0:
        M2C_FIELD(arg0, u8 *, 4) = 1U;
        func_8010DDE4(arg0, 0U);
        func_8010DF5C(0);
        func_800752B4(0);
        func_80075D24(0x1FFF);
        func_80113330();
        return;
    case 1:
        if (func_80026AD0(arg0) != 0) {
            func_8010DDE4(arg0, M2C_FIELD(arg0, u8 *, 3));
        }
        func_80026A68(arg0);
        func_8010DF5C(1);
        return;
    case 3:
        func_8007ADD0(arg0);
        /* fallthrough */
    case 2:
        return;
    }
}

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_8010E15C);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_8010E380);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_8010E550);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_8010E63C);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_8010E74C);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_8010EDF8);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_8010F48C);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_8010FCF0);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_8010FE34);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_80110B38);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_80110D4C);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_80111044);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_80111184);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_801112B4);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", f_UpdateLastEvilPigCopiedWeaponAttack);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", f_UpdateLastEvilPigRepeatedChargeAttack);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_801123F0);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_8011290C);

extern s16 D_1F800264;

void func_80112B80(u8 *a, s32 k)
{
    if (k == 0) {
        k = 9;
    } else {
        if (k == 3) {
            k = a[3] - 3;
        }
        k += 0x12;
    }
    if (D_1F800264 != k) {
        D_1F800264 = k;
        func_80051B04(*(void **)(a + 0xE4), 0x12, k);
    }
}


s32 func_80112BE8(u8 *a)
{
    s16 *p0 = &D_1F800160_71b4;
    s16 *p1 = &D_1F800162;
    s16 *p2 = &D_1F800164_d75f;
    s32 dx = *p0 - *(s16 *)(a + 0x2E);
    s32 dy = *p1 - *(s16 *)(a + 0x32);
    s32 dz = *p2 - *(s16 *)(a + 0x36);
    s32 s = func_80083F50(-*(s16 *)(a + 0x56));
    s32 c = func_80083E80(-*(s16 *)(a + 0x56));
    u32 ang = func_80085690(dy, (s * dx + c * dz) >> 12) & 0xFFF;
    if (ang - 0xB80 <= 0x100) {
        return 6;
    }
    return (ang - 0xC81 < 0x280) ? 4 : 0;
}


void func_80112CB4(u8 *a)
{
    a[3] = D_800BF88C;
    if (a[3] >= 9) {
        a[3] = 0;
    }
}


void func_80112CE0(u8 *a)
{
    s32 t = D_1F800268;
    t |= a[0xBE];
    f_SpawnLastEvilPigCopiedWeaponProjectile(a, t, a[3]);
}

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_80112D10);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_80113068);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_80113330);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_8011348C);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_801135EC);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_8011394C);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_80113B78);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_80113C8C);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_80113E38);

extern S8 D_801299D4[];
extern s32 D_801297B4[];
extern u8 D_80129834[];

void func_80113FDC(u8 *a)
{
    s32 i;
    s32 c, g, b;
    for (i = 0; i < 0x20; i++) {
        c = ((0x20 - i) * a[5]) / 32 + 1;
        g = c - (c >> 4);
        b = c - (c >> 3);
        if (D_801299D4[i].d == 0) {
            D_801297B4[i] = 0;
            if (i != 0) {
                D_801297B4[i - 1] = 0;
            }
            if (i != 0x1F) {
                D_801297B4[i + 1] = 0;
            }
            break;
        }
        if (i < 2) {
            D_801297B4[i] = 0;
            D_80129834[i] = 0x10;
        } else {
            D_801297B4[i] = (b << 16) | (g << 8) | c;
            D_80129834[i] = 0x21 - i;
        }
    }
    func_80029664(D_801299D4, i, D_801297B4, D_80129834);
}

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_801140F4);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_80114288);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_801143C4);

extern u8 D_1F800250;
extern u8 D_800E7E7C;
#define H(p, o) (*(s16 *)((u8 *)(p) + (o)))

void func_801148E0(u8 *a)
{
    u8 *t = D_1F80024C_2bfb;
    u32 y;
    switch (a[4]) {
    case 0:
        a[4] = 1;
    case 1:
        if (D_1F800250 == 0) {
            a[4] = 2;
        }
        H(a, 0x2C) = H(t, 0x2E);
        H(a, 0x2E) = H(t, 0x32);
        y = D_800E7E7C;
        H(a, 0x30) = H(t, 0x36);
        if (y >= 0x10) {
            func_80031220(0x1006, a + 0x2C, 0);
        }
        break;
    case 2:
    case 3:
        func_8007A624(a);
        break;
    }
}


void func_801149AC(u8 *a)
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

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_80114A5C);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_80114E70);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_80115364);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_801157CC);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_80115A70);


void func_80115DA4(u32 *p, void *b)
{
    u32 lo = *p;
    u32 packed;

    packed = lo;
    lo = packed & 0xFFFF;
    p += 4;
    func_80115A70(func_801157CC(p, b, lo), b, packed >> 16);
}

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_80115DEC);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_80115FF4);

extern u16 *D_800ECF78;

void func_80116534(u8 *a)
{
    u16 *p = D_800ECF78;
    u16 t;

    *(u16 **)(a + 0xC) = p;
    *(u16 *)(a + 8) = p[0];
    t = p[1];
    a[7] = 0;
    *(u16 *)(a + 0xA) = t;
}

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_80116560);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_80116778);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_80116ABC);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_80116C2C);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_80116E5C);


void func_801175B8(void) {
}

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_801175C0);

typedef struct { s16 x, y, w, h; } ClutRect;
typedef struct { s16 m[3][3]; s16 pad; s32 t[3]; } AreaMatrix;
typedef struct { s16 x, y, z, pad; } AreaSVec;
extern AreaSVec D_1F8000C0_f4ad;
typedef struct { u8 pad[0x28]; AreaMatrix m; } AreaScratchD0;
extern AreaScratchD0 D_1F8000D0;
extern AreaMatrix D_1F800000;

void func_80117984(u8 *a) {
    D_1F8000C0_f4ad.x = M2C_FIELD(M2C_FIELD(a, u8 **, 0xC0), s16 *, 0x2C);
    D_1F8000C0_f4ad.y = M2C_FIELD(M2C_FIELD(a, u8 **, 0xC0), s16 *, 0x30);
    D_1F8000C0_f4ad.z = M2C_FIELD(M2C_FIELD(a, u8 **, 0xC0), s16 *, 0x34);
    func_80084110(&D_1F8000D0.m, M2C_FIELD(a, u8 **, 0xC0) + 0x18, &D_1F800000);
    func_80084220(&D_1F8000C0_f4ad, D_1F800000.t);
    D_1F800000.t[0] += D_1F8000D0.m.t[0];
    D_1F800000.t[1] += D_1F8000D0.m.t[1];
    D_1F800000.t[2] += D_1F8000D0.m.t[2];
    func_80084660(&D_1F800000);
    func_80084690(&D_1F800000);
    func_801175C0(a);
}

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_80117A64);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_80117C70);


void func_80117E40(void *arg0) {
    M2C_FIELD(arg0, s16 *, 0x56) = (s16) -(s16) *(u16 *)0x1F8000F2;
    func_800517F8();
}


void func_80117E6C(u8 *a)
{
    s32 n;
    switch (a[5]) {
    case 0:
        if (a[0x29] != 0) {
            a[5] = 1;
            n = (u16)(*(u16 *)(*(u8 **)(a + 0xC0) + 0x3A) / 320);
            if (n == 0) {
                n = 1;
            } else if (n >= 5) {
                n = 4;
            }
            *(s16 *)(a + 0x7C) = 0;
            *(s16 *)(a + 0x7E) = n * 8;
        }
        break;
    case 1:
        if (a[0x29] == 0) {
            a[5] = 0;
        }
        break;
    }
}


void func_80117F08(u8 *a)
{
    s32 n;
    s32 v;
    if (a[0x2B] != 0) {
        n = (u16)(*(u16 *)(*(u8 **)(a + 0xC0) + 0x3A) / 320);
        if (n == 0) {
            n = 1;
        } else if (n >= 5) {
            n = 4;
        }
        *(s16 *)(a + 0x7C) = 0;
        *(s16 *)(a + 0x7E) = n * 8;
    } else {
        v = (*(u16 *)(a + 0x7C) + 0x1E0) & 0xFFF;
        *(s16 *)(a + 0x7C) = v;
        if (v < 0x1E0 && *(s16 *)(a + 0x7E) != 0) {
            *(s16 *)(a + 0x7E) -= 8;
        }
    }
}

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_80117FA4);


s32 func_80118250(void *arg0) {
    M2C_FIELD(arg0, u8 *, 0x47) = (u8) M2C_FIELD(arg0, u8 *, 0x72);
    return 1;
}

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_80118264);


s32 func_80118378(u8 *a)
{
    void *p = func_80118534(a);
    if (p != 0) {
        D_800BF9EB = 0;
        *(void **)(a + 0x14) = p;
        return 1;
    }
    return 0;
}

extern s8 D_1F800233[];

s32 func_801183B8(void) {
    *((s8 *)D_1F800233) = 0;
    return 1;
}

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_801183C8);

void func_801183C8();

u8 *func_80118534(void *a)
{
    u8 *p = func_80072DDC(a, 4, 3, 0x24);
    if (p != 0) {
        *(void **)(p + 0x1C) = func_801183C8;
        p[3] = 1;
        *(void **)(p + 0x10) = a;
    }
    return p;
}

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_80118588);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_8011866C);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_80118934);

extern Cam D_1F8000D0_8c3c;
extern LVec D_1F8000A0;
extern void *D_8012907C[];

s32 func_80118B74(u8 *a)
{
    switch (a[6]) {
    case 0:
        a[6]++;
        D_1F8000C0.x = 0;
        D_1F8000C0.y = -0x690;
        D_1F8000C0.z = 0x3E8;
        func_80084470(D_1F8000D0_8c3c.m, &D_1F8000C0, &D_1F8000A0);
        *(u16 *)(a + 0x2E) = D_1F8000D0_8c3c.pos[0].hi + D_1F8000A0.x;
        *(u16 *)(a + 0x32) = D_1F8000D0_8c3c.pos[1].hi + D_1F8000A0.y;
        *(u16 *)(a + 0x36) = D_1F8000D0_8c3c.pos[2].hi + D_1F8000A0.z;
        func_80040CDC(a, 0, D_8012907C[D_800BF870.unk0 - 10]);
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

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_80118C98);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_80119058);

extern s8 D_1F800160[];
extern s8 D_1F800164[];
extern s8 D_1F800246[];
extern s8 D_1F80024C[];

void func_8011919C(void *arg0) {
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
        func_8011866C(arg0);
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

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_801192C8);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_8011968C);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_80119B64);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_80119CC0);

extern u8 D_800E806E;

s32 func_8011A1EC(u8 *p)
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

extern s16 D_80128F08[];
extern s16 D_800E8046;

s32 func_8011A27C(u8 *p)
{
    s16 y;

    switch (p[0x78]) {
    case 0:
        p[0x78]++;
        *(s32 *)(p + 0x38) = func_8003116C(D_80128F08[D_800BF870.unk0 - 10], p + 0x2C, -0x32);
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


s32 func_8011A328(void *arg0) {
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x38), s8 *, 4) = 2;
    func_80074590(0x37, 0x16, 0);
    return 1;
}

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_8011A35C);

extern s16 D_800BED82;
extern M2C_UNK D_80129134;
void func_8011A428(void) {
    func_80075448(0xA, &D_80129134, 0x10, D_800BED82);
}

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_8011A45C);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_8011A620);

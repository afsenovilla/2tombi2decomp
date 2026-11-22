#include "common.h"
#include "game.h"
#include "m2c.h"

extern u8 D_1F800246_6eef;
#define H(p, o) (*(s16 *)((u8 *)(p) + (o)))

void func_801092D4(u8 *a, u8 *b)
{
    s16 dx, dz;
    if (a[0] == 4 && a[0x2B] == 0) {
        if (func_80077768(H(a, 0x56), (s16)func_800782B0(a + 0x2C, H(b, 0x2E), H(b, 0x36)), 0) != 0) {
            dx = H(a, 0x2E) - H(b, 0x2E);
            dz = H(a, 0x36) - H(b, 0x36);
            if (func_80084080(dx * dx + dz * dz) > 0x100) {
                a[0x2B] = 1;
                D_1F800246_6eef = 0;
            }
        } else if (func_800240FC(a, b) != 0) {
            if (((*(u16 *)(*(u8 **)(b + 0xC0) + 8) + 0x100) & 0xFFF) <= 0x200U) {
                b[0x29] = 1;
                a[0] = 0xA;
                a[4] = 2;
                a[6] = 2;
                a[5] = 3;
                D_1F800246_6eef = 3;
            }
        }
    }
}

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_8010940C);

extern u8 D_1F800253;
#define F16(p, o) M2C_FIELD(p, s16 *, o)
#define FU16(p, o) M2C_FIELD(p, u16 *, o)
s32 func_80109648(u8 *a, u8 *b) {
    s16 dx, dz, dy, d;
    u16 h, r, bh, ah;
    s32 y;

    dx = F16(a, 0x2E) - F16(b, 0x2E);
    dz = F16(a, 0x36) - F16(b, 0x36);
    r = func_80084080(dx * dx + dz * dz);
    if (F16(a, 0x80) + F16(b, 0x80) < r) {
        return -1;
    }
    {
        dy = FU16(a, 0x32) - FU16(b, 0x32);
        bh = FU16(b, 0x84); ah = FU16(a, 0x84); h = bh + ah;
        if ((u16)(dy + h) > F16(a, 0x86) + F16(b, 0x86)) {
        fail:
            return -1;
        }
        if (dy < 0) {
            d = -h;
        } else {
            d = (F16(b, 0x86) - bh) + (F16(a, 0x86) - ah);
        }
        if (d <= 0) {
            if (a[0x145] & 1) {
                goto fail;
            }
            b[0x29] = 1;
            M2C_FIELD(a, s32 *, 0x30) = (F16(b, 0x32) + d) << 16;
            func_80022C78(a);
            return 2;
        }
        y = F16(b, 0x32) + d;
        D_1F800253 = 4;
        M2C_FIELD(a, s32 *, 0x30) = y << 16;
        if (a[0x145] == 1 && F16(a, 0x4A) < 0) {
            F16(a, 0x4A) = 0;
        }
        return 3;
    }
}

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

typedef struct { u16 lo; u16 hi; } Fix;
typedef struct {
    Fix at[3];
    Fix pos[3];
    s16 dir[3];
    u8 pad1E[0x2A];
    u8 m[0x20];
} Cam;
extern Cam D_1F8000D0;
extern u16 D_1F8000EE;
#define W(p, o) (*(s32 *)((u8 *)(p) + (o)))
void func_8010CEE4(u8 *a, u8 *b, s32 ang)
{
    Cam *c;
    s32 h, d;
    s16 t, dist, x, z;
    if (D_800BF870.unk0 == 0xC || D_800BF870.unk0 == 0xF) {
        return;
    }
    if (ang != 0) {
        if (D_1F800246_6eef == 2) {
            dist = 0x258;
            if (W(a, 0x60) < 0x190) {
                return;
            }
            h = 0x190;
        } else {
            dist = 0x3E8;
            h = 0x320;
        }
        t = ang + 0x800;
        t = U(b, 0x56) + t;
    } else {
        h = 0x190;
        t = U(b, 0x56) + 0x800;
        dist = -D_1F8000EE;
    }
    c = &D_1F8000D0;
    d = c->at[1].hi + h - c->pos[1].hi;
    if ((u16)(d + 10) >= 0x15) {
        W(c, 4) -= (d << 16) >> 3;
    } else {
        c->at[1].hi = c->pos[1].hi - h;
        a[0x66] |= 2;
    }
    x = U(b, 0x2E) + ((func_80083F50(t) * dist) >> 12);
    z = U(b, 0x36) - ((func_80083E80(t) * dist) >> 12) - D_1F8000D0.at[2].hi;
    x = x - D_1F8000D0.at[0].hi;
    t = func_80085690(-z, x);
    dist = func_80084080(x * x + z * z);
    W(&D_1F8000D0, 0) += func_80083F50(t) * dist;
    W(&D_1F8000D0, 8) -= func_80083E80(t) * dist;
    if (dist < 0x191) {
        a[0x66] |= 1;
    }
}

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_8010D108);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_8010D2D8);

void func_8010D5E4(void) {
}

void func_8010D5EC(void) {
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

void func_8010D82C(u8 *a, u8 *b, s32 ang)
{
    Cam *c;
    s32 h, d;
    s16 t, dist, x, z;
    if (D_800BF870.unk0 == 0xC || D_800BF870.unk0 == 0xF) {
        return;
    }
    if (ang != 0) {
        if (D_1F800246_6eef == 2) {
            dist = 0x258;
            if (W(a, 0x60) < 0x190) {
                return;
            }
            h = 0x190;
        } else {
            dist = 0x3E8;
            h = 0x320;
        }
        t = ang + 0x800;
        t = U(b, 0x56) + t;
    } else {
        h = 0x190;
        t = U(b, 0x56) + 0x800;
        dist = -D_1F8000EE;
    }
    c = &D_1F8000D0;
    d = c->at[1].hi + h - c->pos[1].hi;
    if ((u16)(d + 10) >= 0x15) {
        W(c, 4) -= (d << 16) >> 3;
    } else {
        c->at[1].hi = c->pos[1].hi - h;
        a[0x66] |= 2;
    }
    x = U(b, 0x2E) + ((func_80083F50(t) * dist) >> 12);
    z = U(b, 0x36) - ((func_80083E80(t) * dist) >> 12) - D_1F8000D0.at[2].hi;
    x = x - D_1F8000D0.at[0].hi;
    t = func_80085690(-z, x);
    dist = func_80084080(x * x + z * z);
    W(&D_1F8000D0, 0) += func_80083F50(t) * dist;
    W(&D_1F8000D0, 8) -= func_80083E80(t) * dist;
    if (dist < 0x191) {
        a[0x66] |= 1;
    }
}

extern u8 D_800E7E80[];
extern void *D_8011BF6C[];
extern u8 *D_1F800248;
void func_8010DA50(u8 *a)
{
    u8 *pl = D_800E7E80;
    s32 s;
    s = a[4];
    switch (s) {
    case 0:
        if (func_80051B70(a, 0xC, D_8011BF6C[D_800BF870.unk0 - 10]) == 0) {
            H(a, 0x54) = 0;
            a[4]++;
            H(a, 0x56) = func_800782B0(a + 0x2C, (s16)D_1F8000D0.at[0].hi, (s16)D_1F8000D0.at[2].hi) - 0x400;
            H(a, 0x58) = 0;
            H(a, 0x4A) = 0;
            **(s16 **)(a + 0xC0) = 0x28;
        }
        break;
    case 1:
        H(a, 0x56) = func_800782B0(a + 0x2C, (s16)D_1F8000D0.at[0].hi, (s16)D_1F8000D0.at[2].hi) - 0x400;
        func_8007778C(a);
        switch (a[5]) {
        case 0:
            func_8004BD64(a, 0, W(pl, 0xDC), W(pl, 0xD0), 0);
            break;
        case 1:
            H(a, 0x4A) -= 0x200;
            if (H(a, 0x4A) < -0x3000) {
                H(a, 0x4A) = -0x3000;
            }
            W(a, 0x30) += H(a, 0x4A) << 8;
            if (a[1] == 0) {
                a[4] = 3;
                func_8006E1C0(7);
                D_1F800248[5] = 2;
            } else {
                func_800517F8(a);
            }
            break;
        }
        break;
    case 2:
    case 3:
        func_8007A624(a);
        break;
    }
}

s32 f_TestTombaOverlapsEvilPig(u8 *a)
{
    u8 *p = D_800E7E80;
    s16 dx, dz;
    if (p[0x144] == 1) {
        dx = H(p, 0x2E) - H(a, 0x2E);
        dz = H(p, 0x36) - H(a, 0x36);
        if ((u16)func_80084080(dx * dx + dz * dz) <= H(p, 0x80) + H(a, 0x80) + 0x122) {
            return (u16)(H(p, 0x32) - H(a, 0x32) + 0x258 + (H(p, 0x84) + H(a, 0x84))) <= H(p, 0x86) + H(a, 0x84) + 0x258;
        }
    }
    return 0;
}

extern u8 *D_8011BF3C[][2];
void func_8010DD0C(u8 *a)
{
    s32 low;
    s16 v;
    u16 c;
    u8 *t;
    u8 **tt;
    s32 r;
    if (D_800BF870.unk0 == 0xF) {
        low = *(s16 *)(a + 0x6E) < 3;
    } else {
        low = *(s16 *)(a + 0x6E) < 2;
    }
    t = D_8011BF3C[D_800BF870.unk0 - 10][low];
    c = *(u16 *)(a + 0x66);
    v = t[c & 0xF];
    *(u16 *)(a + 0x66) = c + 1;
    a[6] = 0;
    switch (v) {
    case 0:
        *(u16 *)(a + 0x64) = 1;
        a[5] = 1;
        break;
    case 1:
        *(u16 *)(a + 0x64) = 2;
        a[5] = 1;
        break;
    case 2:
        *(u16 *)(a + 0x64) = 3;
        a[5] = 2;
        break;
    case 3:
        *(u16 *)(a + 0x64) = 4;
        a[5] = 2;
        break;
    case 4:
    default:
        *(u16 *)(a + 0x64) = 5;
        if (func_8009A450() & 0x40) {
            a[5] = 3;
        } else {
            a[5] = 1;
        }
        break;
    }
}

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_8010DE1C);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_8010E4C8);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_8010EB5C);

extern u8 D_800BF809;
extern s16 D_1F800160_71b4;
extern s16 D_1F800164_d75f;
typedef struct { s16 x, y, w, h; } ClutRect;
typedef struct { s16 m[3][3]; s16 pad; s32 t[3]; } AreaMatrix;
typedef struct { s16 x, y, z, pad; } AreaSVec;
typedef struct { u8 pad[0x28]; AreaMatrix m; } AreaScratchD0;
void func_8010F3C0(u8 *a)
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
        if (*(s16 *)(a + 0x40) < 0x1E && f_TestTombaOverlapsEvilPig(a) != 0) {
            a[0] = 2;
            func_80041768(a, 3, 4);
            func_8010DD0C(a);
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

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_8010F504);

extern u8 *D_1F80024C_2bfb;
extern u8 *D_1F800260;
extern s16 D_1F8001A4;
extern u16 D_1F8001A0;
extern u16 D_1F8001A2;
void func_80110208(u8 *a)
{
    u8 *p = *(u8 **)(a + 0x10);
    s32 r, v;
    switch (a[4]) {
    case 0:
        a[4] = 1;
        H(a, 0x54) = 0;
        if (*(u16 *)(p + 0xB8) == 0x800) {
            H(a, 0x40) = 0x50;
            H(a, 0x42) = 0x6E;
        } else {
            H(a, 0x40) = 0xA0;
            H(a, 0x42) = 0xDC;
        }
        H(a, 0xE) = 0;
        a[0x2B] = 0;
        a[0x46] = 0;
        break;
    case 1:
        if (D_1F80024C_2bfb != p && D_1F800260 == 0) {
            a[4] = 3;
            break;
        }
        if ((W(p, 0) & 0xFF0C) != 0x100) {
            break;
        }
        W(a, 0x2C) = W(p, 0x2C);
        W(a, 0x30) = W(p, 0x30);
        W(a, 0x34) = W(p, 0x34);
        a[0x2A] = p[0x2A];
        r = func_800489E4(a, H(a, 0x32));
        if (r == 1 && H(a, 0x32) <= D_1F8001A4) {
            s16 y = D_1F8001A4;
            s16 x = H(a, 0x2E);
            s16 z = H(a, 0x36);
            u16 c0 = D_1F8001A0;
            u16 c1 = D_1F8001A2;
            H(a, 0x4A) = y;
            a[1] = r;
            H(a, 0x48) = x;
            H(a, 0x4C) = z;
            H(a, 0x56) = c0;
            H(a, 0x58) = c1;
        } else {
            a[1] = 0;
        }
        if (a[1] == 0) {
            break;
        }
        v = 0x80 - ((H(a, 0x4A) - H(p, 0x32)) >> 4);
        H(a, 0x4E) = v;
        if (v < 0) {
            H(a, 0x4E) = 0;
            a[1] = 0;
        } else if (v > 0x80) {
            H(a, 0x4E) = 0x80;
        }
        v = 0x100 - ((H(a, 0x4A) - H(p, 0x32)) >> 4);
        H(a, 0x50) = v;
        if (v < 0) {
            H(a, 0x50) = 0;
            a[1] = 0;
        } else if (v > 0x100) {
            H(a, 0x50) = 0x100;
        }
        break;
    case 2:
    case 3:
        func_8007A624(a);
        break;
    }
}

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

void func_801125A8(u8 *a)
{
    Spark *sp = (Spark *)(a + 0x50);
    Spark *e;
    s32 i;
    switch (a[4]) {
    case 0:
        for (i = 0; i < 10; i++) {
            sp[i].x = func_8009A450();
            sp[i].y = func_8009A450();
            sp[i].z = 0;
            sp[i].t = func_8009A450() & 0xF;
        }
        a[4] = 1;
        H(a, 0x48) = 0;
        H(a, 0x4E) = 0;
        a[5] = 0;
        a[6] = 0xE;
        a[7] = 0;
    case 1:
        if (H(a, 0x48) < 0x400) {
            H(a, 0x4E) += 0x199;
            a[5] += 10;
            a[6] += 10;
            H(a, 0x48) += 0x66;
        } else {
            H(a, 0x48) += 0x28;
        }
        if (H(a, 0x48) >= 0x800) {
            H(a, 0x48) = 0;
        }
        if (++a[5] >= 0x1C) {
            a[5] = 0;
        }
        if (++a[6] >= 0x1C) {
            a[6] = 0;
        }
        if ((s8)(a[7] += 4) < 0) {
            a[4] = 2;
            break;
        }
        for (i = 0; i < 10; i++) {
            if (sp[i].t > 0) {
                sp[i].t += 10;
                if (sp[i].t >= 0x48) {
                    if (H(a, 0x48) < 0x400) {
                        sp[i].t = func_8009A450() & 0xF;
                        sp[i].x = func_8009A450();
                        sp[i].y = func_8009A450();
                    } else {
                        sp[i].t = -1;
                    }
                }
            }
        }
        a[1] = 1;
        break;
    case 2:
    case 3:
        func_8007A624(a);
        break;
    }
}

#define gte_ldfcdir(r0, r1, r2) __asm__ volatile("ctc2	%0, $21;" "ctc2	%1, $22;" "ctc2	%2, $23" : : "r"(r0), "r"(r1), "r"(r2))
#define gte_ldv0m(p) __asm__ volatile("lwc2	$0, %0;" "lwc2	$1, %1" : : "m"(((s32 *)(p))[0]), "m"(((s32 *)(p))[1]))
extern s32 D_1F800084[];
extern s32 D_1F800088;
extern s32 D_1F800090[];
extern u8 D_8011DBC0[];
extern u8 D_8011DB78[];
extern u8 D_8011DC50[];
void func_801127D4(u8 *a)
{
    s32 s;
    u8 *b = a;
    s32 *p = D_1F800084;
    s32 *d = D_1F800090;
    gte_ldfcdir(0, 0, 0);
    *d = 0;
    func_800329E0(6);
    gte_ldv0m(b + 0x2C);
    if (func_800317CC(*(s16 *)(a + 0x32)) == 0) {
        s = func_80083E80(*(s16 *)(a + 0x48)) >> 3;
        s += func_80083E80(*(s16 *)(a + 0x4E)) >> 8;
        if (s < 0x10) {
            s = 0x10;
        }
        D_1F800088 = *p = (*p * s) >> 8;
        func_8002847C(D_8011DBC0, D_8011DC50[b[5] >> 1], 0);
        func_8002847C(D_8011DB78, D_8011DC50[b[6] >> 1], 0);
    }
}

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_801128E8);

extern S8 D_80126BD8[];
extern u8 D_1F800250;
void func_80112A94(u8 *a)
{
    u8 *t = D_1F80024C_2bfb;
    s32 i;
    H(a, 0x2C) = H(t, 0x2E);
    H(a, 0x2E) = H(t, 0x32);
    H(a, 0x30) = H(t, 0x36);
    switch (a[4]) {
    case 0:
        for (i = 0; i < 0x20; i++) {
            D_80126BD8[i].a = H(a, 0x2C);
            D_80126BD8[i].b = H(a, 0x2E);
            D_80126BD8[i].c = H(a, 0x30);
            D_80126BD8[i].d = 0;
        }
        a[4] = 1;
        a[5] = 0;
    case 1:
        if (D_1F800250 == 0) {
            a[4] = 2;
        }
        for (i = 0x1F; i > 0; i--) {
            D_80126BD8[i].a = D_80126BD8[i - 1].a;
            D_80126BD8[i].b = D_80126BD8[i - 1].b;
            D_80126BD8[i].c = D_80126BD8[i - 1].c;
            D_80126BD8[i].d = D_80126BD8[i - 1].d;
        }
        D_80126BD8[0].a = H(a, 0x2C);
        D_80126BD8[0].b = H(a, 0x2E);
        D_80126BD8[0].c = H(a, 0x30);
        D_80126BD8[0].d = 1;
        a[1] = 1;
        a[5] += (0xFF - a[5]) >> 3;
        break;
    case 2:
        a[1] = 1;
        a[5] >>= 1;
        if (a[5] <= 0x10) {
            a[4] = 3;
        }
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

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
AreaPolyFT4 *func_80112EE4(AreaPolyFT4 *p, s32 x, s32 y, s32 w, s32 h, s16 c, s16 cy) {
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

#define gte_SetRotMatrix(r0) __asm__ volatile("lw	$12, 0( %0 );" "lw	$13, 4( %0 );" "ctc2	$12, $0;" "ctc2	$13, $1;" "lw	$12, 8( %0 );" "lw	$13, 12( %0 );" "lw	$14, 16( %0 );" "ctc2	$12, $2;" "ctc2	$13, $3;" "ctc2	$14, $4" : : "r"(r0) : "$12", "$13", "$14")
#define gte_SetTransMatrix(r0) __asm__ volatile("lw	$12, 20( %0 );" "lw	$13, 24( %0 );" "ctc2	$12, $5;" "lw	$14, 28( %0 );" "ctc2	$13, $6;" "ctc2	$14, $7" : : "r"(r0) : "$12", "$13", "$14")
extern u8 D_1F8000F8[];
extern void *D_800ED8C8_a098;
typedef struct {
    u8 pad0[6];
    u8 count;
    u8 pad7[5];
    u32 *tbl;
    u16 list[1];
} PartList;
void func_80113DB4(PartList *a)
{
    u16 *p = a->list;
    u16 *end;
    void *ot;
    u32 *tbl;
    u32 *e;
    u32 v;
    void *r;
    if (a->count == 0) {
        return;
    }
    end = &a->list[a->count];
    ot = D_800ED8C8_a098;
    tbl = a->tbl;
    gte_SetRotMatrix(D_1F8000F8);
    gte_SetTransMatrix(D_1F8000F8);
    for (; p < end; p++) {
        e = &tbl[*p];
        v = *e;
        r = func_80113788(e + 1, ot, v & 0xFF);
        v >>= 16;
        func_80113A54(r, ot, v & 0xFF);
    }
}

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

extern SVec D_1F8000C0;
extern LVec D_1F8000A0;
extern u16 D_800E7ED6;
extern u8 D_80125DA8[];
extern void *D_80125E30[];
extern void *D_80125F64[];
extern void *D_80125F78[];
s32 func_801156AC(u8 *a)
{
    s32 s;
    void *q;
    u8 *pl;
    u16 r;
    s = a[6];
    switch (s) {
    case 0:
        a[6] = 1;
        func_80040CDC(a, 0, D_80125DA8);
        a[0x70] = 1;
        break;
    case 1:
        func_80041098(a);
        if (a[0x70] != 0xFF) {
            return 0;
        }
        a[6]++;
        func_80040CDC(a, 0, D_80125E30[D_800BF870.unk0 - 10]);
        a[0x70] = 1;
        break;
    case 2:
        func_80041098(a);
        if (a[0x70] != 0xFF) {
            return 0;
        }
        a[6]++;
        if (!(D_800BF870.pad1[0x1A7] & 0x1F)) {
            func_80040CDC(a, 0, D_80125F78[D_800BF870.unk0 - 10]);
        } else {
            func_80040CDC(a, 0, D_80125F64[D_800BF870.unk0 - 10]);
        }
        a[0x70] = 1;
        r = D_800E7ED6;
        H(a, 0xB8) = 0x1000;
        H(a, 0xBA) = 0x1000;
        H(a, 0xBC) = 0x1000;
        H(a, 0x56) = r;
        break;
    case 3:
        func_80041098(a);
        if (a[0x70] == 0xFF) {
            return 1;
        }
        pl = D_800E7E80;
        func_8004BD64(a, 0, W(pl, 0xDC), W(pl, 0xD0), 0);
        D_1F8000C0.x = -0x28;
        D_1F8000C0.y = -0x30;
        D_1F8000C0.z = 0;
        func_80084470(D_1F8000D0.m, &D_1F8000C0, &D_1F8000A0);
        *(u16 *)(a + 0x2E) += D_1F8000A0.x;
        *(u16 *)(a + 0x32) += D_1F8000A0.y;
        *(u16 *)(a + 0x36) += D_1F8000A0.z;
        func_8007778C(a);
        func_800518FC(a);
        break;
    default:
        return 0;
    }
    return 0;
}

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

s32 func_80115DD0(u8 *a, u8 *b)
{
    s16 dy, m, dx, dz, ang;
    u16 by;
    s32 ret;
    s32 sx, sz, t;
    dy = H(a, 0x32) - H(b, 0x32);
    m = ((dy >= 0) ? dy : -dy) - 0x30;
    if (m < 0) m = 0;
    if (dy >= 0) H(b, 0x32) += m; else H(b, 0x32) -= m;
    dx = H(a, 0x2E) - H(b, 0x2E);
    dz = H(a, 0x36) - H(b, 0x36);
    ret = 1;
    if (func_80084080(dx * dx + dz * dz) >= 0x40) {
        ang = func_80085690(-dz, dx);
        sx = (func_80083F50(ang) * 0x30) >> 12;
        sz = func_80083E80(ang);
        H(b, 0x2E) += sx;
        H(b, 0x36) += -(sz * 0x30) >> 12;
        ret = 0;
    }
    return ret;
}

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

typedef struct {
    u8 pad0[0x50];
    s16 x50;
    u8 pad52[4];
    s16 x56;
    u8 pad58[0x14];
    s16 x6C;
    s16 x6E;
    u8 pad70[0x4E];
    u8 xBE;
} T787C;
s32 func_8011787C(T787C *a)
{
    switch (a->x6E) {
    case 0:
        if (a->xBE) {
            a->x50 = -0x80;
            a->x6C = a->x56 - 0x800;
        } else {
            a->x50 = 0x80;
            a->x6C = a->x56 + 0x800;
        }
        a->x6E++;
    case 1:
        a->x56 += a->x50;
        if (a->xBE) {
            if (a->x6C < a->x56) {
                break;
            }
            a->x56 = a->x6C;
            a->x6E = -1;
            a->xBE ^= 1;
            return 1;
        } else {
            if (a->x56 < a->x6C) {
                break;
            }
            a->x56 = a->x6C;
            a->x6E = -1;
            a->xBE ^= 1;
            return 1;
        }
    }
    return 0;
}

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_8011796C);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_80117AC8);

s32 func_80117B84(u8 *a) {
    u16 z = D_1F800164_7d8c;
    u16 x = D_1F800160_3621;
    return func_80077768((s16)-func_80085690((s16)(z - *(u16 *)(a + 0x36)), (s16)(x - *(u16 *)(a + 0x2E))), *(s16 *)(a + 0x56), 0) != 0;
}

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

#include "common.h"
#include "game.h"
#include "m2c.h"

extern u8 D_1F800246_6eef;
#define H(p, o) (*(s16 *)((u8 *)(p) + (o)))

void func_80109314(u8 *a, u8 *b)
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

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_8010944C);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80109688);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_801097FC);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80109AE0);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80109C00);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80109F08);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_8010A0C8);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_8010A234);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_8010A3D8);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_8010A554);

void func_8010A788(void *a, u8 *b)
{
    if (b[0x47] == 2) {
        func_801097FC(a, b, *(void **)(b + 0xC0));
    } else {
        func_8001F650(a, b, *(void **)(b + 0xC0));
    }
}

extern u8 *D_800E7FD8;

void func_8010A7D0(u8 *a, u8 *b)
{
    if (b[0x47] != 2 && (a[2] != 0 || b != D_800E7FD8)) {
        func_80020F7C(a, b, *(void **)(b + 0xC0), 0x1200);
    }
}

extern void *D_1F800080;
extern u8 D_1F800182;

void func_8010A824(u8 *a, u8 *b)
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

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_8010A8A0);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_8010A988);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_8010AA94);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_8010AC84);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_8010B0FC);

extern s8 D_1F80027E[];
extern u8 D_800BFA1A;

void func_8010B338(void *arg0) {
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
    if (!(D_800BFA1A & 1)) {
        func_80042354(1, 5);
        func_8001CF2C();
        M2C_FIELD(arg0, s8 *, 4) = 4;
    }
}


s32 func_8010B3DC(s32 arg0, s32 arg1) {
    s32 var_a3;
    void *temp_a1;

    temp_a1 = M2C_FIELD(arg0, void **, 0x158);
    var_a3 = 0;
    if ((M2C_FIELD(temp_a1, u8 *, 0xC) == 4) && (M2C_FIELD(temp_a1, u8 *, 2) == 0x17)) {
        var_a3 = func_8010AC84(arg0, (s32) temp_a1, arg1);
    }
    return var_a3;
}

s32 func_8010B42C(u8 *a)
{
    u8 *b = *(u8 **)(a + 0x158);

    if (b[0xC] != 4) {
        return 0;
    }
    if (b[2] != 0x16) {
        return 0;
    }
    return func_8010B0FC(a, b);
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
#define U(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define W(p, o) (*(s32 *)((u8 *)(p) + (o)))

void func_8010B474(u8 *a, u8 *b, s32 ang)
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

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_8010B698);


void func_8010B824(void) {
}


void func_8010B82C(void) {
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
extern Spawn *D_80118EB8[];
extern Pos D_800BF808;

void func_8010B834(Owner *a, s32 sel)
{
    Spawn *e;
    u8 *p;
    a->count = 0;
    e = D_80118EB8[sel];
    while (e->kind != 0xFF) {
        if (sel == 0 || a->count < 15) {
            switch (e->mode) {
            case 0:
                break;
            case 1:
                D_800BF808.x = e->x;
                D_800BF808.y = e->y;
                D_800BF808.z = e->z;
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

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_8010B9AC);


void func_8010BAD4(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 4);
    switch (temp_v1) {                              /* irregular */
    case 0:
        M2C_FIELD(arg0, u8 *, 4) = 1U;
        func_8010B834(arg0, 0U);
        func_8010B9AC(0);
        func_80113708();
        func_800752B4(0);
        func_80075D24(0x1FFF);
        return;
    case 1:
        if (func_80026AD0(arg0) != 0) {
            func_8010B834(arg0, M2C_FIELD(arg0, u8 *, 3));
        }
        func_80026A68(arg0);
        func_80113724();
        func_8010B9AC(1);
        return;
    case 3:
        func_8007ADD0(arg0);
        /* fallthrough */
    case 2:
        return;
    }
}

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_8010BBB4);

extern u8 D_800E7E80[];
extern void *D_8011BCB0[];
extern u8 *D_1F800248;
#define W(p, o) (*(s32 *)((u8 *)(p) + (o)))

void func_8010BDD8(u8 *a)
{
    u8 *pl = D_800E7E80;
    s32 s;
    s = a[4];
    switch (s) {
    case 0:
        if (func_80051B70(a, 0xC, D_8011BCB0[D_800BF870.unk0 - 10]) == 0) {
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

#define H(p, o) (*(s16 *)((u8 *)(p) + (o)))

s32 func_8010BFA8(u8 *a)
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

extern u8 *D_8011BC80[][2];

void f_SelectNextEvilPigAttack(u8 *a)
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
    t = D_8011BC80[D_800BF870.unk0 - 10][low];
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

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", f_SelectEvilPigArenaTarget);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", f_UpdateEvilPigRelocationAttack);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", f_UpdateEvilPigRushAttack);

extern u8 D_800BF809;
extern s16 D_1F800160_71b4;
extern s16 D_1F800164_d75f;

void func_8010D748(u8 *a)
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
        if (*(s16 *)(a + 0x40) < 0x1E && func_8010BFA8(a) != 0) {
            a[0] = 2;
            func_80041768(a, 3, 4);
            f_SelectNextEvilPigAttack(a);
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

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", f_UpdateEvilPigHitAndCaptureState);

extern u8 *D_1F80024C_2bfb;
extern u8 *D_1F800260;
extern s16 D_1F8001A4;
extern u16 D_1F8001A0;
extern u16 D_1F8001A2;

void func_8010E590(u8 *a)
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

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_8010E7A4);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", f_UpdateEvilPigCenterEffectAttack);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_8010ECF0);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", f_UpdateEvilPigBattleActor);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", f_UpdateEvilPigBattleIntroduction);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_8010F97C);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_8010FD74);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_8011024C);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_801103F4);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80110698);

void func_801109CC(u32 *p, void *b)
{
    u32 lo = *p;
    u32 packed;

    packed = lo;
    lo = packed & 0xFFFF;
    p += 4;
    func_80110698(func_801103F4(p, b, lo), b, packed >> 16);
}

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80110A14);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80110CF8);

extern u16 *D_800ECF78;

void func_80111238(u8 *a)
{
    u16 *p = D_800ECF78;
    u16 t;

    *(u16 **)(a + 0xC) = p;
    *(u16 *)(a + 8) = p[0];
    t = p[1];
    a[7] = 0;
    *(u16 *)(a + 0xA) = t;
}

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80111264);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_801113A0);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80111564);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80111670);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_801117C8);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80111980);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80111B68);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80111D3C);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_8011212C);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80112244);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80112384);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_8011253C);

typedef struct { u8 x, y, z; s8 t; } Spark;

void func_80112764(u8 *a)
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
extern u8 D_8011E9FC[];
extern u8 D_8011E9B4[];
extern u8 D_8011EB2C[];

void func_80112990(u8 *a)
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
        func_8002847C(D_8011E9FC, D_8011EB2C[b[5] >> 1], 0);
        func_8002847C(D_8011E9B4, D_8011EB2C[b[6] >> 1], 0);
    }
}

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80112AA4);

typedef struct { s16 a, b, c, d; } S8;
extern S8 D_80127984[];
extern u8 D_1F800250;

void func_80112C50(u8 *a)
{
    u8 *t = D_1F80024C_2bfb;
    s32 i;
    H(a, 0x2C) = H(t, 0x2E);
    H(a, 0x2E) = H(t, 0x32);
    H(a, 0x30) = H(t, 0x36);
    switch (a[4]) {
    case 0:
        for (i = 0; i < 0x20; i++) {
            D_80127984[i].a = H(a, 0x2C);
            D_80127984[i].b = H(a, 0x2E);
            D_80127984[i].c = H(a, 0x30);
            D_80127984[i].d = 0;
        }
        a[4] = 1;
        a[5] = 0;
    case 1:
        if (D_1F800250 == 0) {
            a[4] = 2;
        }
        for (i = 0x1F; i > 0; i--) {
            D_80127984[i].a = D_80127984[i - 1].a;
            D_80127984[i].b = D_80127984[i - 1].b;
            D_80127984[i].c = D_80127984[i - 1].c;
            D_80127984[i].d = D_80127984[i - 1].d;
        }
        D_80127984[0].a = H(a, 0x2C);
        D_80127984[0].b = H(a, 0x2E);
        D_80127984[0].c = H(a, 0x30);
        D_80127984[0].d = 1;
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

extern s32 D_801278D4[];
extern u8 D_80127954[];

void func_80112DF4(u8 *a)
{
    s32 i;
    s32 c, g, b;
    for (i = 0; i < 0x20; i++) {
        c = ((0x20 - i) * a[5]) / 32 + 1;
        g = c - (c >> 4);
        b = c - (c >> 3);
        if (D_80127984[i].d == 0) {
            D_801278D4[i] = 0;
            if (i != 0) {
                D_801278D4[i - 1] = 0;
            }
            if (i != 0x1F) {
                D_801278D4[i + 1] = 0;
            }
            break;
        }
        if (i < 2) {
            D_801278D4[i] = 0;
            D_80127954[i] = 0x10;
        } else {
            D_801278D4[i] = (b << 16) | (g << 8) | c;
            D_80127954[i] = 0x21 - i;
        }
    }
    func_80029664(D_80127984, i, D_801278D4, D_80127954);
}

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80112F0C);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_801130A0);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_801131DC);


void func_801136F8(void) {
}


void func_80113700(void) {
}

extern M2C_UNK D_80127974;
void func_80113708(void) {
    M2C_FIELD(&D_80127974, s8 *, 0) = 0;
    M2C_FIELD(&D_80127974, s8 *, 1) = 0;
    M2C_FIELD(&D_80127974, s8 *, 2) = 0;
    M2C_FIELD(&D_80127974, s8 *, 3) = 0;
}

extern M2C_UNK D_80127974;
void func_80113724(void) {
    if (M2C_FIELD(&D_80127974, u8 *, 0) == 0) {
        M2C_FIELD(&D_80127974, s16 *, 4) = 0;
        func_800310F4(0xB00, 0);
        M2C_FIELD(&D_80127974, u8 *, 0) = 1U;
    }
}

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80113768);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_8011384C);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80113904);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80113A20);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80113AC0);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80113B78);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80113C70);

void func_80113D4C(u8 *a)
{
    switch (a[4]) {
    case 0:
        a[4] = 1;
        a[7] = 0;
        *(s16 *)(a + 0x48) = 0x180;
        *(s16 *)(a + 0x4A) = 0x180;
    case 1:
        if ((*(void **)(a + 0x34) = *(void **)(a + 0x38)) == 0) {
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

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80113DDC);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80113EA4);

void func_80113F84(u8 *a)
{
    switch (a[4]) {
    case 0:
        *(s32 *)(a + 0x48) = 0;
        *(s32 *)(a + 0x4C) = 0;
        a[4] = 1;
        a[7] = 0xFF;
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

void func_80114020(u8 *a)
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

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_801140D0);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_801142EC);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80114630);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80114784);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_801149D8);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80114B38);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80114C6C);

void func_80114D50(u8 *a)
{
    func_8004766C(a);
    func_80048750(a);
    *(u16 *)(a + 0x56) = D_1F8001A0;
    if (a[3] == 0) {
        *(u16 *)(a + 0x56) += 0xD8;
    } else {
        *(u16 *)(a + 0x56) += 0x200;
    }
    a[0x47] = 0;
    func_80114630(a);
}

typedef struct { s16 x, y, z; } V3;
extern V3 D_8011EC68[];

void func_80114DB0(u8 *a)
{
    *(s16 *)(a + 0x2E) = D_8011EC68[a[3]].x;
    *(s16 *)(a + 0x32) = D_8011EC68[a[3]].y;
    *(s16 *)(a + 0x36) = D_8011EC68[a[3]].z;
    func_8004766C(a);
    func_80048750(a);
    *(u16 *)(a + 0x56) = D_1F8001A0;
    if (a[3] == 0) {
        *(u16 *)(a + 0x56) -= 0xD8;
    } else {
        *(u16 *)(a + 0x56) -= 0x200;
    }
}

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80114E64);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80115338);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80115418);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80115700);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80115958);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80115C24);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80115DF0);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80115FF4);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_801160C4);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80116194);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", f_CopyEvilPigCaptureDeformationVertices);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", f_UpdateEvilPigCaptureDeformation);

typedef struct { s16 x, y, z, pad; } SVec;
typedef struct { u16 x, p0, y, p1, z, p2; } LVec;
extern SVec D_1F8000C0;
extern LVec D_1F8000A0;
extern u16 D_800E7ED6;
extern u8 D_80126DC8[];
extern void *D_80126E50[];
extern void *D_80126F84[];
extern void *D_80126F98[];

s32 func_80116634(u8 *a)
{
    s32 s;
    void *q;
    u8 *pl;
    u16 r;
    s = a[6];
    switch (s) {
    case 0:
        a[6] = 1;
        func_80040CDC(a, 0, D_80126DC8);
        a[0x70] = 1;
        break;
    case 1:
        func_80041098(a);
        if (a[0x70] != 0xFF) {
            return 0;
        }
        a[6]++;
        func_80040CDC(a, 0, D_80126E50[D_800BF870.unk0 - 10]);
        a[0x70] = 1;
        break;
    case 2:
        func_80041098(a);
        if (a[0x70] != 0xFF) {
            return 0;
        }
        a[6]++;
        if (!(D_800BF870.pad1[0x1A7] & 0x1F)) {
            func_80040CDC(a, 0, D_80126F98[D_800BF870.unk0 - 10]);
        } else {
            func_80040CDC(a, 0, D_80126F84[D_800BF870.unk0 - 10]);
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

extern void *D_80127120[];

s32 func_80116874(u8 *a)
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
        func_80040CDC(a, 0, D_80127120[D_800BF870.unk0 - 10]);
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

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", f_UpdateEvilPigRobeRewardActor);

#define U(p, o) (*(u16 *)((u8 *)(p) + (o)))

s32 f_MoveEvilPigCaptureActorTowardBoss(u8 *a, u8 *b)
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

void func_80116E9C(void *arg0) {
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
        f_UpdateEvilPigCaptureDeformation(arg0);
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

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", f_UpdateEvilPigCaptureApproachSequence);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", f_UpdateEvilPigDefeatAndRewardSequence);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80117864);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_801179C0);

extern u8 D_800E806E;

s32 func_80117EC8(u8 *p)
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

extern s16 D_80126FAC[];
extern s16 D_800E8046;

s32 func_80117F58(u8 *p)
{
    s16 y;

    switch (p[0x78]) {
    case 0:
        p[0x78]++;
        *(s32 *)(p + 0x38) = func_8003116C(D_80126FAC[D_800BF870.unk0 - 10], p + 0x2C, -0x32);
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


s32 func_80118004(void *arg0) {
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x38), s8 *, 4) = 2;
    func_80074590(0x37, 0x16, 0);
    return 1;
}

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80118038);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80118158);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_801185FC);

u8 func_80118754(u8 *a)
{
    s16 ang;
    s32 r;
    a[0x29] = 0;
    if (a[0x46] == 0) {
        ang = *(u16 *)(a + 0x60);
    } else {
        ang = *(u16 *)(a + 0x60) + 0x800;
    }
    r = func_800455C0(a, 0, (s16)(*(u16 *)(a + 0x86) - *(u16 *)(a + 0x84)), ang);
    a[0x29] = r;
    if (a[0x29] == 0) {
        return a[0x29];
    }
    a[0x29] = r & 1;
    return a[0x29];
}

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_801187E8);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_801188C0);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80118A5C);

void func_80118A5C();

u8 *func_80118C8C(s32 a)
{
    u8 *p = func_8007A980(0, 2, 0);
    if (p == 0) {
        return 0;
    }
    *(void **)(p + 0x1C) = func_80118A5C;
    p[2] = 0x4B;
    p[3] = a;
    return p;
}


void func_80118CE0(s32 arg0) {
    s32 temp_s0;

    temp_s0 = arg0 + 0x2C;
    func_8003116C(0xB05, temp_s0, -0x1E);
    func_8003116C(0xB05, temp_s0, -0x1E);
    func_8003116C(0xB09, temp_s0, -0x28);
    func_8003116C(0xB0B, temp_s0, 0);
}

typedef struct { u16 a, b; } Range;
extern Range D_801277DC[];
extern Range D_801277F4[];
extern Range D_8012781C[];
extern Range D_80127854[];
extern u8 *D_1F80021C;

void func_80118D40(s16 kind, s16 idx)
{
    Range *t;
    s32 n, base;
    u8 *p;
    switch (kind) {
    case 0:
        t = D_801277DC;
        n = 3;
        base = 0;
        break;
    case 1:
        t = D_801277F4;
        n = 0x1D;
        base = 0x1C4;
        break;
    case 2:
        t = D_8012781C;
        n = 0x1F;
        base = 0x1C8;
        break;
    case 3:
        t = D_80127854;
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
extern M2C_UNK D_801271F4;
void f_UpdateEvilPigBagOfferingSequence(void) {
    func_80075448(0xA, &D_801271F4, 0x10, D_800BED82);
}

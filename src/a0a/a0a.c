#include "common.h"
#include "game.h"
#include "m2c.h"
typedef struct { s16 x, y, w, h; } ClutRect;

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

extern s32 D_1F80009C;
#define U(p, o) (*(u16 *)((u8 *)(p) + (o)))
typedef struct { u8 pad[0x2E]; u16 x; u8 pad2[6]; u16 z; } ArenaXZ;

void func_8010944C(u8 *a, u8 *b)
{
    s32 r = func_8001F40C(a, b, 1);
    s32 t, u, s, x, y, z;
    if (r < 0) {
        return;
    }
    b[0x5F] = func_80077768((s16)(*(u16 *)&D_1F80009C + 0x800), H(b, 0x60), 1) + 2;
    s = a[0x144];
    switch (s) {
    case 1:
        if ((D_800BF870.unk0 != 14 || b[0xBF] == 0) && !(b[0] & 0x18) && r < 2) {
            func_8001FDB4(b, 6, 3, 0x1E);
            return;
        }
        break;
    case 2:
        if (b[0] & 0xA) {
            if (U(a, 0x17E) & 0x200) {
                return;
            }
            x = (func_80083F50(D_1F80009C) * (H(a, 0x80) + H(b, 0x80))) >> 12;
            y = (func_80083E80(D_1F80009C) * (H(a, 0x80) + H(b, 0x80))) >> 12;
            U(b, 0x2E) = U(a, 0x2E) - x;
            U(b, 0x36) = U(a, 0x36) + y;
            return;
        }
        z = D_1F80009C;
        b[0] = 3;
        b[4] = s;
        b[5] = 0;
        b[6] = 0;
        b[0x2B] = (z + 0x800) >> 4;
        return;
    }
    if (U(a, 0x17E) & 0x200) {
        return;
    }
    t = (func_80083F50(D_1F80009C) * (H(a, 0x80) + H(b, 0x80))) >> 12;
    u = (func_80083E80(D_1F80009C) * (H(a, 0x80) + H(b, 0x80))) >> 12;
    ((ArenaXZ *)b)->x = U(a, 0x2E) - t;
    ((ArenaXZ *)b)->z = U(a, 0x36) + u;
    a[0x2B] = D_1F80009C >> 4;
    func_80022D08(a, b, 1, 0);
}

extern u8 D_1F800253;
#define F16(p, o) M2C_FIELD(p, s16 *, o)
#define FU16(p, o) M2C_FIELD(p, u16 *, o)
s32 func_80109688(u8 *a, u8 *b) {
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

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_801097FC);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80109AE0);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80109C00);

extern u8 **D_1F80013C;
extern u8 D_1F800144;
extern s16 D_1F800150_058c;
extern u8 D_1F800150;
extern u8 D_1F800183;
extern u8 D_1F800182;
extern u8 **D_1F800148;

void func_80109F08(void)
{
    u8 **l = D_1F80013C;
    u8 *e;
    u8 **m;
    u8 *o;
    D_1F800183 = D_1F800144;
    if (D_1F800150_058c == 0) {
        return;
    }
    while (D_1F800183 != 0) {
        e = *l;
        D_1F800183--;
        l++;
        if (e[0] != 2 && !(e[0] & 8)) {
            m = D_1F800148;
            D_1F800182 = D_1F800150;
            while (D_1F800182 != 0) {
                o = *m;
                D_1F800182--;
                m++;
                if (o[0] & 1) {
                    switch (o[2]) {
                    case 0x17:
                        if (o[0x47] != 2) {
                            func_80023870(e, o, *(u8 **)(o + 0xC0));
                        }
                        break;
                    case 0x18:
                        if (e[0] == 4 && func_800240FC(e) != 0) {
                            e[0x5E] = 1;
                            e[0] = 10;
                        }
                        break;
                    case 0x64:
                        if (e[2] == 0x65) {
                            func_80109314(e, o);
                        }
                        break;
                    }
                }
            }
        }
    }
}

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

// nearcopy: 4 words off, C from a07 func_80113C20
#include "common.h"
#include "game.h"
#include "m2c.h"
typedef struct {
    u8 *ptr;
    u8 *clut;
    s16 x;
    s16 y;
} ClutCycle;
extern ClutCycle D_8011937C[];
extern s8 D_801278CC[];
extern u8 D_800BF873;

void func_8010B9AC(s32 arg0) {
    ClutRect r;
    s32 i;
    ClutCycle *e;
    u8 *data;

    if (arg0 == 0) {
        s8 *p;
        i = 4;
        p = &D_801278CC[i];
        do {
            *p-- = 0;
        } while (--i >= 0);
        return;
    }
    e = D_8011937C;
    for (i = 0; i < 5; i++, e++) {
        if (--D_801278CC[i] <= 0) {
            if (e->ptr[0] == 0xFF) {
                e->ptr -= e->ptr[1];
            }
            data = e->clut + e->ptr[0] * 32;
            D_801278CC[i] = e->ptr[1];
            r.x = e->x;
            r.y = e->y;
            r.w = 16;
            r.h = 1;
            func_80081218(&r, data);
            e->ptr += 2;
        }
    }
}

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

void func_8010BBB4(u8 *a, u8 *b, s32 ang)
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

typedef struct { u8 *v[6]; } PtrTab6;
typedef struct { u8 b[8][4]; } ByteTab8;
extern PtrTab6 D_80109210;
extern ByteTab8 D_80109228;
extern u8 D_8011E8B8[];

void func_80112AA4(u8 *a)
{
    PtrTab6 p;
    ByteTab8 t;
    u8 *q;
    s32 *d;
    u8 **pp;
    u8 (*tt)[4];
    u8 *e;
    q = a;
    d = D_1F800090;
    p = D_80109210;
    t = D_80109228;
    pp = p.v;
    tt = t.b;
    gte_ldfcdir(0, 0, 0);
    *d = 0;
    if (a[7] < 12) {
        func_80031AC4(a + 0x2C, tt, a + 0x48);
        func_80027768(p.v[a[7] >> 1], 0, 0, 0);
    }
    if (q[7] < 16) {
        e = tt[q[7] >> 1];
        func_80031AC4(q + 0x2C, e, q + 0x48);
        func_80027768(D_8011E8B8, e[3], 0, 0);
    }
}

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

extern u16 D_1F80017C;
extern u8 D_8011EB40[];
typedef struct { u8 pad[0x48]; s16 r[3]; } RotAct;

void func_80112F0C(u8 *a)
{
    u8 *p;
    s32 k;
    switch (a[4]) {
    case 0:
        *(s32 *)(a + 0x50) = 0x100;
        *(s32 *)(a + 0x54) = 0x100;
        *(s16 *)(a + 0x4E) = 0xF0;
        a[1] = 1;
        a[4] = 1;
        *(s16 *)(a + 0x48) = 0;
        *(s16 *)(a + 0x4A) = 0;
        *(s16 *)(a + 0x4C) = 0;
        *(s16 *)(a + 0x32) = -0x50;
    case 1:
        p = *(u8 **)(a + 0x38);
        *(u8 **)(a + 0x34) = p;
        if (p == NULL) {
            *(u8 **)(a + 0x34) = D_8011EB40;
        }
        ((RotAct *)a)->r[0] += func_80083F50(D_1F80017C >> 7) >> 5;
        ((RotAct *)a)->r[1] += func_80083F50(D_1F80017C >> 4) >> 7;
        ((RotAct *)a)->r[2] += func_80083F50(D_1F80017C * 2) >> 6;
        a[1] = 1;
        break;
    case 2:
        switch (a[5]) {
        case 0:
            a[5] = 1;
        case 1:
            *(s32 *)(a + 0x50) -= 0x10;
            if (*(s32 *)(a + 0x50) < 0) {
                *(s32 *)(a + 0x50) = 0;
            }
            *(s32 *)(a + 0x54) += 0x80;
            if (++a[6] > 16) {
                a[4] = 3;
            }
            a[1] = 1;
            break;
        }
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

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
AreaPolyFT4 *func_801130A0(AreaPolyFT4 *p, s32 x, s32 y, s32 w, s32 h, s16 c, s16 cy) {
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

extern s32 D_1F800090_3460;
void func_80113768(u8 *a)
{
    u8 *b = a;
    void *m = *(void **)(a + 0x34);
    s32 *p = D_1F800084;
    s32 k, x, y;
    if (m != 0) {
        func_800329E0(6);
        gte_ldv0m(b + 0x2C);
        if (func_800317CC(*(s16 *)(a + 0x32)) != 0) {
            func_80031780(a);
        } else {
            k = *p >> 8;
            x = k * *(s16 *)(b + 0x4A);
            y = k * *(s16 *)(b + 0x48);
            D_1F800088 = x;
            *p = y;
            D_1F800090_3460 = b[7] << 5;
            gte_ldfcdir(0, 0, 0);
            *(void **)(b + 0x38) = func_800328BC(b, m);
        }
    }
}

extern u8 D_8011E870[];
void func_8011384C(u8 *a)
{
    s32 i;
    s32 hi, lo;
    s32 *d = D_1F800090;
    u8 *t = D_8011E870;
    gte_ldfcdir(0, 0, 0);
    *d = 0;
    hi = a[0x53] & 0xE0;
    lo = a[0x53] & 1;
    for (i = 0; i < 4; i++) {
        func_8003265C(a + 0x2C, a + 0x50, a + 0x48);
        func_80027768(t, lo, *(s16 *)(a + 0x32), hi);
        *(s16 *)(a + 0x4E) += 0x400;
    }
}

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80113904);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80113A20);

extern u8 D_8011C114[];
#define P(p, o) (*(void **)((u8 *)(p) + (o)))
void func_80113AC0(u8 *a)
{
    u8 c;
    switch (a[4]) {
    case 0:
        a[4] = 1;
        a[7] = 0x28;
    case 1:
        if ((P(a, 0x34) = P(a, 0x38)) == 0) {
            P(a, 0x34) = P(a, 0x38) = D_8011C114;
        }
        *(s16 *)(a + 0x2E) -= 0x82;
        c = a[7];
        a[7] = c + 0xFF;
        if (c == 0) {
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

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80113B78);

#define gte_ldv0(r0) __asm__ volatile("lwc2	$0, 0( %0 );" "lwc2	$1, 4( %0 )" : : "r"(r0))
typedef struct { s16 x, y, z, pad; } SV;
extern s32 D_1F800084_8c7c;
extern void *D_8011C08C[];
void func_80113C70(u8 *a)
{
    SV v;
    void *m;
    s32 k;
    if (a[0x5E] == 0 && (m = *(void **)(a + 0x78)) != 0) {
        func_800329E0(6);
        v.x = *(s16 *)(a + 0x2E);
        v.y = *(s16 *)(a + 0x32);
        v.z = *(s16 *)(a + 0x36);
        gte_ldv0(&v);
        if (func_800317CC(-0x14) == 0) {
            D_1F800088 = D_1F800084_8c7c;
            k = func_8009A450() & 0x1FF;
            D_1F800090_3460 = k;
            m = func_80027A4C(m, D_8011C08C[0]);
            *(void **)(a + 0x78) = m;
            if (m == 0) {
                *(void **)(a + 0x78) = &D_8011C08C[1];
            }
        }
    }
}

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

void func_80113DDC(u8 *a)
{
    u8 *p = *(u8 **)(a + 0x10);
    s16 *q = (s16 *)(a + 0x50);
    s16 y, z;
    switch (a[4]) {
    case 0:
        a[4] = 1;
        H(a, 0x50) = 0x1000;
        H(a, 0x2C) = H(p, 0x2E);
        y = H(a, 0x4E);
        z = H(p, 0x36);
        H(a, 0x2E) = y;
        H(a, 0x30) = z;
    case 1:
        if (p[4] >= 2) {
            a[4] = 3;
            break;
        }
        if (*q >= -0xFFE) {
            *q -= 0x199;
        }
        a[1] = 1;
        break;
    case 2:
    case 3:
        func_8007A624(a);
        break;
    }
}

extern u8 D_8011EB28[];
extern u8 D_8011D700[];
extern u8 D_8011D6DC[];
void func_80113EA4(u8 *a)
{
    SV v;
    u8 *p;
    u8 *t;
    s32 k;
    s32 *d = D_1F800090;
    gte_ldfcdir(0, 0, 0);
    p = a + 0x2C;
    t = D_8011EB28;
    k = *(s16 *)(a + 0x50);
    v.x = *(s16 *)(a + 0x48);
    v.y = *(s16 *)(a + 0x4A);
    v.z = *(s16 *)(a + 0x32);
    *d = k;
    func_800318A0(p, t, &v);
    func_80027768(D_8011D700, 0, -0x14, 0);
    v.x = *(s16 *)(a + 0x48);
    v.y = *(s16 *)(a + 0x4A);
    v.z = *(s16 *)(a + 0x4C);
    func_800318A0(p, t, &v);
    func_80027768(D_8011D6DC, 0, -0x14, 0);
}

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

void func_80114C6C(u8 *a)
{
    u16 t;
    switch (a[4]) {
    case 0:
        func_801149D8(a);
        func_8004766C(a);
        func_80048750(a);
        t = D_1F8001A0;
        *(u16 *)(a + 0x56) = t;
        if (a[3] == 0) {
            *(u16 *)(a + 0x56) = t + 0xD8;
        } else {
            *(u16 *)(a + 0x56) = t + 0x200;
        }
        a[0x47] = 0;
        func_80114630(a);
        *(u16 *)(a + 0x32) += 0xAF;
        func_800517F8(a);
        break;
    case 1:
        func_80114784(a);
        break;
    case 2:
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

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

typedef struct { s16 m[3][3]; s16 pad; s32 t[3]; } AreaMatrix;
extern AreaSVec D_1F8000C0_f4ad;
typedef struct { u8 pad[0x28]; AreaMatrix m; } AreaScratchD0;
extern AreaScratchD0 D_1F8000D0_2539;
extern AreaMatrix D_1F800000;
void func_80115338(u8 *a) {
    D_1F8000C0_f4ad.x = M2C_FIELD(M2C_FIELD(a, u8 **, 0xC0), s16 *, 0x2C);
    D_1F8000C0_f4ad.y = M2C_FIELD(M2C_FIELD(a, u8 **, 0xC0), s16 *, 0x30);
    D_1F8000C0_f4ad.z = M2C_FIELD(M2C_FIELD(a, u8 **, 0xC0), s16 *, 0x34);
    func_80084110(&D_1F8000D0_2539.m, M2C_FIELD(a, u8 **, 0xC0) + 0x18, &D_1F800000);
    func_80084220(&D_1F8000C0_f4ad, D_1F800000.t);
    D_1F800000.t[0] += D_1F8000D0_2539.m.t[0];
    D_1F800000.t[1] += D_1F8000D0_2539.m.t[1];
    D_1F800000.t[2] += D_1F8000D0_2539.m.t[2];
    func_80084660(&D_1F800000);
    func_80084690(&D_1F800000);
    func_80114E64(a);
}

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80115418);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80115700);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80115958);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80115C24);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80115DF0);

extern u16 D_1F8000F0;
extern u16 D_1F8000F2;
void func_80115FF4(u8 *a)
{
    u8 *m;
    s16 x, y, z;
    if (a[0x47] == 2) {
        H(a, 0x54) = -D_1F8000F0;
        m = *(u8 **)(a + 0x3C);
        func_80085480(a + 0x54, a + 0x98);
    } else {
        m = *(u8 **)(a + 0x10);
        H(a, 0x56) = -U(m, 0x56) - D_1F8000F2;
        func_80085480(a + 0x54, a + 0x98);
    }
    func_80051D20(m, a + 0x88, a + 0x90);
    x = H(a, 0x90);
    y = H(a, 0x92);
    z = H(a, 0x94);
    H(a, 0x2E) = x;
    H(a, 0x32) = y;
    H(a, 0x36) = z;
    *(s32 *)(a + 0xAC) = H(a, 0x2E);
    *(s32 *)(a + 0xB0) = H(a, 0x32);
    *(s32 *)(a + 0xB4) = H(a, 0x36);
    func_80084360(m + 0x98, a + 0x98);
    func_80051300(a);
}

void func_801160C4(u8 *a) {
    s32 n;
    s32 x;

    if (a[0x47] == 2) {
        return;
    }
    if (a[0x2B] != 0) {
        n = (u16)(M2C_FIELD(M2C_FIELD(a, u8 **, 0xC0), u16 *, 0x3A) / 320);
        if (n == 0) {
            n = 1;
        } else if (n >= 5) {
            n = 4;
        }
        M2C_FIELD(a, s16 *, 0x7C) = 0;
        M2C_FIELD(a, s16 *, 0x7E) = n * 8;
        func_80074590(0x8D, 0, 0);
        return;
    }
    x = (M2C_FIELD(a, u16 *, 0x7C) + 0x1E0) & 0xFFF;
    M2C_FIELD(a, s16 *, 0x7C) = x;
    if (x < 0x1E0 && M2C_FIELD(a, s16 *, 0x7E) != 0) {
        M2C_FIELD(a, s16 *, 0x7E) -= 8;
    }
}

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80116194);

extern s16 D_80126A5C[];

void f_CopyEvilPigCaptureDeformationVertices(u16 *a, s16 *v)
{
    s32 i;
    s32 n = a[0];
    s16 *t;
    s16 *s;
    s16 *d = (s16 *)a;
    if (n == 0) return;
    t = D_80126A5C;
    i = 0;
    do {
        s = v + t[i * 3] * 3;
        d[0x10] = *s++;
        d[0x11] = s[0];
        d[0x12] = s[1];
        s = v + t[i * 3 + 1] * 3;
        d[0x14] = *s++;
        d[0x15] = s[0];
        d[0x13] = s[1];
        s = v + t[i * 3 + 2] * 3;
        d[0x16] = *s++;
        d[0x17] = s[0];
        d[0x18] = s[1];
        d += 18;
    } while (++i < n);
}

extern u8 *D_8011FC8C[];
extern u8 *D_80120A20[];
extern u8 *D_80122524[];
extern u8 *D_80125568[];
extern u8 *D_80126904[];
extern u8 *D_80126A44[];
#define EP_FRAME(a) (*(s16 *)((a) + 0x64))
#define EP_MODEL(a) (*(u8 **)(*(u8 **)((a) + 0xC0) + 0x40))

s32 f_UpdateEvilPigCaptureDeformation(u8 *a)
{
    switch (a[7]) {
    case 0:
        break;
    case 1:
        f_CopyEvilPigCaptureDeformationVertices(EP_MODEL(a), D_8011FC8C[EP_FRAME(a)]);
        if (++EP_FRAME(a) >= 8) {
            EP_FRAME(a) = 7;
            return 1;
        }
        break;
    case 2:
        f_CopyEvilPigCaptureDeformationVertices(EP_MODEL(a), D_80120A20[EP_FRAME(a)]);
        if (++EP_FRAME(a) >= 7) {
            EP_FRAME(a) = 0;
            a[7] = 0;
            return 1;
        }
        break;
    case 3:
        f_CopyEvilPigCaptureDeformationVertices(EP_MODEL(a), D_80122524[EP_FRAME(a)]);
        if (++EP_FRAME(a) >= 6) {
            EP_FRAME(a) = 5;
            return 1;
        }
        break;
    case 4:
        f_CopyEvilPigCaptureDeformationVertices(EP_MODEL(a), D_80122524[EP_FRAME(a)]);
        if (++EP_FRAME(a) >= 14) {
            EP_FRAME(a) = 13;
            return 1;
        }
        break;
    case 5:
        f_CopyEvilPigCaptureDeformationVertices(EP_MODEL(a), D_80126A44[EP_FRAME(a)]);
        if (++EP_FRAME(a) >= 6) {
            EP_FRAME(a) = 5;
            return 1;
        }
        break;
    case 6:
    case 7:
    case 8:
        f_CopyEvilPigCaptureDeformationVertices(EP_MODEL(a), D_80125568[EP_FRAME(a)]);
        if (++EP_FRAME(a) >= 25) {
            if (a[7] == 8) {
                EP_FRAME(a) = 24;
                return 1;
            }
            EP_FRAME(a) = 0;
            a[7]++;
        }
        break;
    case 9:
        f_CopyEvilPigCaptureDeformationVertices(EP_MODEL(a), D_80126904[EP_FRAME(a)]);
        if (++EP_FRAME(a) >= 10) {
            EP_FRAME(a) = 9;
            return 1;
        }
        break;
    }
    return 0;
}

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

s32 func_80117864(u8 *a0)
{
    u8 *a = a0;
    Cam *c = &D_1F8000D0;
    s16 dx, dy, dz;
    s32 d;
    dx = *(u16 *)(a + 0x2E) - c->at[0].hi;
    dy = *(u16 *)(a + 0x32) - c->at[1].hi;
    dz = *(u16 *)(a + 0x36) - c->at[2].hi;
    d = (u16)func_80077FB0(dx * dx + dy * dy + dz * dz);
    a[1] = 0;
    if (d < 0x200) {
        return 0;
    }
    if (d > 0x2300) {
        return 0;
    }
    if ((c->dir[0] * dx + c->dir[1] * dy + c->dir[2] * dz) / (d * 4) < 0x358) {
        return 0;
    }
    a[1] = 1;
    func_80077EBC(a);
    return 1;
}

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

s32 func_801187E8(u8 *a)
{
    s16 h = *(u16 *)(a + 0x86) - *(u16 *)(a + 0x84);
    s16 ang;
    s16 d = 0x3C;
    a[0x5F] = 0;
    if (a[0x46] == 0) {
        ang = *(u16 *)(a + 0x60);
    } else {
        ang = *(u16 *)(a + 0x60) + 0x800;
    }
    if (func_80045CAC(a, d, h, ang) == 0 && func_80045CAC(a, d, (s16)-(h + 0x28), ang) == 0) {
        return 0;
    }
    a[0x5F] = 1;
    return 1;
}

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

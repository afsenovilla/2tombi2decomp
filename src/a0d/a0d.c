#include "common.h"
#include "game.h"
#include "m2c.h"
#include "gte.h"

extern u8 D_1F800246_6eef;
#define H(p, o) (*(s16 *)((u8 *)(p) + (o)))

void func_80109304(u8 *a, u8 *b)
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
void func_8010943C(u8 *a, u8 *b)
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

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_80109678);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_801099E0);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_80109B0C);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_80109C54);

extern u8 **D_1F80013C;
extern u8 D_1F800144;
extern s16 D_1F800150_058c;
extern u8 D_1F800150;
extern u8 D_1F800183;
extern u8 D_1F800182_5650;
extern u8 **D_1F800148;
void func_80109EA8(void)
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
            D_1F800182_5650 = D_1F800150;
            while (D_1F800182_5650 != 0) {
                o = *m;
                D_1F800182_5650--;
                m++;
                if (o[0] & 1) {
                    switch (o[2]) {
                    case 0x18:
                        if (e[0] == 4 && func_800240FC(e) != 0) {
                            e[0x5E] = 1;
                            e[0] = 10;
                        }
                        break;
                    case 0x46:
                        func_801099E0(e, o);
                        break;
                    case 0x64:
                        if (e[2] == 0x68) {
                            func_80109304(e, o);
                        }
                        break;
                    }
                }
            }
        }
    }
}

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
void func_8010AD1C(u8 *a, u8 *b, s32 ang)
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

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_8010AF40);

void func_8010B100(void) {
}

void func_8010B108(void) {
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

void func_8010B480(u8 *a, u8 *b, s32 ang)
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
extern void *D_8011A9DC[];
extern u8 *D_1F800248;
void func_8010B6A4(u8 *a)
{
    u8 *pl = D_800E7E80;
    s32 s;
    s = a[4];
    switch (s) {
    case 0:
        if (func_80051B70(a, 0xC, D_8011A9DC[D_800BF870.unk0 - 10]) == 0) {
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

s32 func_8010B874(u8 *a)
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

extern u8 *D_8011A9AC[][2];
void func_8010B960(u8 *a)
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
    t = D_8011A9AC[D_800BF870.unk0 - 10][low];
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

extern u8 *D_1F80024C_2bfb;
extern u8 *D_1F800260_e3a9;
extern s16 D_1F8001A4_f18c;
extern u16 D_1F8001A0;
extern u16 D_1F8001A2;
void func_8010DE5C(u8 *a)
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
        if (D_1F80024C_2bfb != p && D_1F800260_e3a9 == 0) {
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
        if (r == 1 && H(a, 0x32) <= D_1F8001A4_f18c) {
            s16 y = D_1F8001A4_f18c;
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

extern u8 D_800BF80E;
extern u8 D_800BF80F;
extern u8 D_800E8008[];
extern u8 D_801175EC[];
extern s16 D_80119704[];
extern s32 D_8011A9F4[];
void func_8010B6A4();

void func_8010E070(u8 *a)
{
    u8 *pl = D_800E7E80;
    u8 *e;
    s16 *t;

    switch (a[6]) {
    case 0:
        pl[5] = 0x22;
        pl[6] = 2;
        func_80054D14(pl, 0x73, 0);
        e = func_80072DDC(0, 1, 3, 0x21);
        if (e != NULL) {
            *(void **)(e + 0x1C) = func_8010B6A4;
        }
        *(u8 **)(a + 0x14) = e;
        a[6]++;
        break;
    case 1:
        if (D_800BF80F == 0) {
            a[6]++;
            pl[6] = 0;
            func_8004D604(D_8011A9F4[D_800BF870.unk0 - 10], 1);
        }
        break;
    case 2:
        if (D_800BF80E != 0) {
            a[6]++;
            func_80054D14(pl, 0xEA, 2);
            pl[6] = 0;
        }
        break;
    case 3:
        if (D_800BF80E != 0) {
            a[6]++;
            (*(u8 **)(a + 0x14))[5] = 1;
            H(a, 0x40) = 10;
        }
        break;
    case 4:
        if (--H(a, 0x40) == 0) {
            a[6]++;
            pl[6] = 0;
            func_80054D14(pl, 2, 5);
        }
        break;
    case 5:
        if (D_800BF80E != 0) {
            a[6]++;
            pl[6] = 0;
            H(a, 0x40) = 100;
        }
        break;
    case 6:
        if (--H(a, 0x40) == 0) {
            a[6]++;
            pl[6] = 0;
            func_80054D14(pl, 1, 5);
            H(a, 0x40) = 20;
        }
        break;
    case 7:
        if (H(a, 0x40) == 0) {
            if (D_800BF80E != 0) {
                a[6]++;
                pl[6] = 0;
            }
        } else {
            H(a, 0x40)--;
        }
        break;
    case 8:
        if (D_800E8008[0x64] != 7) {
            a[6] = 0;
            H(a, 0x6A) = 0;
            a[5]++;
            func_8006CBD0(D_800E8008, D_801175EC);
            t = &D_80119704[H(a, 0x6A) * 3];
            U(a, 0x2E) = t[0];
            U(a, 0x32) = t[1];
            U(a, 0x36) = t[2];
            H(a, 0x6A)++;
            func_8006E1C0(7);
        }
        break;
    }
}

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", f_SpawnEarthEvilPigDetachedPartsActor);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_8010E5EC);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", f_UpdateEarthEvilPigSplitActor);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", f_UpdateEarthEvilPigDetachedPartsAttack);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_8010FA2C);

void func_8010FDA8(u8 *a)
{
    s32 k;
    switch (a[6]) {
    case 0:
        a[0] = 1;
        *(s16 *)(a + 0x40) = 0x96;
        a[6]++;
        func_80041768(a, 10, 6);
        if (func_80077768((s16)func_800782B0(a + 0x2C, D_1F800160_71b4, D_1F800164_d75f), *(s16 *)(a + 0x60), 0) != 0) {
            a[0xBE] = 1;
        } else {
            a[0xBE] = 0;
        }
    case 1:
        if (a[0xBE] == 0) {
            k = *(u16 *)(a + 0x60) & 0xFFF;
        } else {
            k = (*(u16 *)(a + 0x60) + 0x800) & 0xFFF;
        }
        *(s16 *)(a + 0x56) = func_800776F8(k, *(s16 *)(a + 0x56), 0x80);
        if (--*(s16 *)(a + 0x40) == 0) {
            a[5] = 0;
            a[6] = 0;
            *(s16 *)(a + 0x64) = 0;
        }
        break;
    }
}

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

void func_80111A68(u8 *a)
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
extern u8 D_8011CAB0[];
extern u8 D_8011CA68[];
extern u8 D_8011CB70[];
void func_80111C94(u8 *a)
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
        func_8002847C(D_8011CAB0, D_8011CB70[b[5] >> 1], 0);
        func_8002847C(D_8011CA68, D_8011CB70[b[6] >> 1], 0);
    }
}

typedef struct { u8 *v[6]; } PtrTab6;
typedef struct { u8 b[8][4]; } ByteTab8;
extern PtrTab6 D_80109218;
extern ByteTab8 D_80109230;
extern u8 D_8011CA44[];
void func_80111DA8(u8 *a)
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
    p = D_80109218;
    t = D_80109230;
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
        func_80027768(D_8011CA44, e[3], 0, 0);
    }
}

extern S8 D_80125ACC[];
extern u8 D_1F800250;
void func_80111F54(u8 *a)
{
    u8 *t = D_1F80024C_2bfb;
    s32 i;
    H(a, 0x2C) = H(t, 0x2E);
    H(a, 0x2E) = H(t, 0x32);
    H(a, 0x30) = H(t, 0x36);
    switch (a[4]) {
    case 0:
        for (i = 0; i < 0x20; i++) {
            D_80125ACC[i].a = H(a, 0x2C);
            D_80125ACC[i].b = H(a, 0x2E);
            D_80125ACC[i].c = H(a, 0x30);
            D_80125ACC[i].d = 0;
        }
        a[4] = 1;
        a[5] = 0;
    case 1:
        if (D_1F800250 == 0) {
            a[4] = 2;
        }
        for (i = 0x1F; i > 0; i--) {
            D_80125ACC[i].a = D_80125ACC[i - 1].a;
            D_80125ACC[i].b = D_80125ACC[i - 1].b;
            D_80125ACC[i].c = D_80125ACC[i - 1].c;
            D_80125ACC[i].d = D_80125ACC[i - 1].d;
        }
        D_80125ACC[0].a = H(a, 0x2C);
        D_80125ACC[0].b = H(a, 0x2E);
        D_80125ACC[0].c = H(a, 0x30);
        D_80125ACC[0].d = 1;
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

extern u16 D_1F80017C;
extern u8 D_8011CB84[];
typedef struct { u8 pad[0x48]; s16 r[3]; } RotAct;
void func_80112210(u8 *a)
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
            *(u8 **)(a + 0x34) = D_8011CB84;
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
AreaPolyFT4 *func_801123A4(AreaPolyFT4 *p, s32 x, s32 y, s32 w, s32 h, s16 c, s16 cy) {
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

typedef struct {
    u32 tag;
    u32 rgb0;
    u16 x0, y0;
    u32 uv0;
    u32 rgb1;
    u16 x1, y1;
    u32 uv1;
    u32 rgb2;
    u16 x2, y2;
    u16 uv2;
    u16 pad;
} T2PolyGT3;
#define T2_ldv3t(r0)                                                                                                   \
    __asm__ volatile("lwc2 $0, 0x10(%0);"                                                                              \
                     "lw $12, 0x14(%0);"                                                                               \
                     "lwc2 $2, 0x18(%0);"                                                                              \
                     "mtc2 $12, $1;"                                                                                   \
                     "lwc2 $4, 0x1C(%0);"                                                                              \
                     "srl $12, $12, 16;"                                                                               \
                     "mtc2 $12, $3;"                                                                                   \
                     "lwc2 $5, 0x20(%0)"                                                                               \
                     :                                                                                                 \
                     : "r"(r0)                                                                                         \
                     : "$12")
#define T2_rtpt() __asm__ volatile(".word 0x4A280030")
#define T2_nclip() __asm__ volatile(".word 0x4B400006")
#define T2_avsz3() __asm__ volatile(".word 0x4B58002D")
#define T2_stflg(r0) __asm__ volatile("cfc2 $12, $31;" "nop;" "sw $12, 0( %0 )" : : "r"(r0) : "$12", "memory")
#define T2_stopz(r0) __asm__ volatile("swc2 $24, 0( %0 )" : : "r"(r0) : "memory")
#define T2_stotz(r0) __asm__ volatile("swc2 $7, 0( %0 )" : : "r"(r0) : "memory")
#define T2_stsxy3_gt3(r0)                                                                                              \
    __asm__ volatile("swc2 $12, 8( %0 );" "swc2 $13, 20( %0 );" "swc2 $14, 32( %0 )" : : "r"(r0) : "memory")
#define T2_stsz1(r0) __asm__ volatile("swc2 $17, 0( %0 )" : : "r"(r0) : "memory")
#define T2_stsz2(r0) __asm__ volatile("swc2 $18, 0( %0 )" : : "r"(r0) : "memory")
#define T2_stsz3(r0) __asm__ volatile("swc2 $19, 0( %0 )" : : "r"(r0) : "memory")
extern void *D_800BF544;

u32 *func_80113748(u32 *f, u32 *ot, s32 n)
{
    s32 sz[3];
    s32 *otz = (s32 *)0x1F800004;
    T2PolyGT3 *p = D_800BF544;
    s32 *flg = (s32 *)0x1F800000;
    u32 c;
    u32 mode;
    s32 b, e;
    u32 *o;

    while (n-- != 0) {
        T2_ldv3t(f);
        p->rgb0 = f[0];
        T2_rtpt();
        p->uv0 = f[2];
        p->uv1 = f[3];
        c = f[1];
        T2_stflg(flg);
        if (*flg >= 0) {
            T2_nclip();
            p->rgb1 = c & 0xF0F0F0;
            T2_stopz(flg);
            if (*flg > 0) {
                T2_stsxy3_gt3(p);
                if ((p->x0 < 320 || p->x1 < 320 || p->x2 < 320) && (p->y0 < 240 || p->y1 < 240 || p->y2 < 240)) {
                    p->rgb2 = (c << 4) & 0xF0F0F0;
                    mode = c >> 24;
                    if (mode != 0) {
                        T2_stsz1(&sz[0]);
                        T2_stsz2(&sz[1]);
                        T2_stsz3(&sz[2]);
                        if (mode == 1) {
                            if (sz[0] > sz[1]) {
                                b = sz[2];
                                if (b < sz[0]) {
                                    b = sz[0];
                                }
                                e = b;
                            } else {
                                b = sz[2];
                                if (b < sz[1]) {
                                    b = sz[1];
                                }
                                e = b;
                            }
                        } else {
                            if (sz[0] < sz[1]) {
                                b = sz[2];
                                if (sz[0] < b) {
                                    b = sz[0];
                                }
                                e = b;
                            } else {
                                b = sz[2];
                                if (sz[1] < b) {
                                    b = sz[1];
                                }
                                e = b;
                            }
                        }
                        *otz = e >> 2;
                    } else {
                        T2_avsz3();
                        T2_stotz(otz);
                    }
                    e = *otz >> 10;
                    *otz = (*otz >> e) + (e << 9);
                    if ((u32)(*otz - 4) >= 0x7FC) {
                        *otz = -1;
                    }
                    if (*otz >= 0) {
                        p->uv2 = ((u16 *)f)[0x11];
                        do {
                            o = ot + *otz;
                            p->tag = *o | 0x09000000;
                            *o = (u32)p;
                        } while (0);
                        p++;
                    }
                }
            }
        }
        f += 9;
    }
    D_800BF544 = p;
    return f;
}

typedef struct {
    u32 tag;
    u32 rgb0;
    u16 x0, y0;
    u32 uv0;
    u32 rgb1;
    u16 x1, y1;
    u32 uv1;
    u32 rgb2;
    u16 x2, y2;
    u32 uv2;
    u32 rgb3;
    u16 x3, y3;
    u32 uv3;
} T2PolyGT4;
#define T2_ldv3p(r0)                                                                                                   \
    __asm__ volatile("lw $12, 0x18(%0);"                                                                               \
                     "lwc2 $0, 0x14(%0);"                                                                              \
                     "mtc2 $12, $1;"                                                                                   \
                     "srl $12, $12, 16;"                                                                               \
                     "mtc2 $12, $3;"                                                                                   \
                     "lwc2 $2, 0x1C(%0);"                                                                              \
                     "lw $12, 0x24(%0);"                                                                               \
                     "lwc2 $4, 0x20(%0);"                                                                              \
                     "mtc2 $12, $5"                                                                                    \
                     :                                                                                                 \
                     : "r"(r0)                                                                                         \
                     : "$12")
#define T2_ldv1p(r0)                                                                                                   \
    __asm__ volatile("lw $12, 0x24(%0);"                                                                               \
                     "lwc2 $0, 0x28(%0);"                                                                              \
                     "srl $12, $12, 16;"                                                                               \
                     "mtc2 $12, $1"                                                                                    \
                     :                                                                                                 \
                     : "r"(r0)                                                                                         \
                     : "$12")
#define T2_rtps() __asm__ volatile(".word 0x4A180001")
#define T2_avsz4() __asm__ volatile(".word 0x4B68002E")
#define T2_stsxy(r0) __asm__ volatile("swc2 $14, 0( %0 )" : : "r"(r0) : "memory")
#define T2_stsxy3_gt4(r0)                                                                                              \
    __asm__ volatile("swc2 $12, 8( %0 );" "swc2 $13, 20( %0 );" "swc2 $14, 32( %0 )" : : "r"(r0) : "memory")
#define T2_stsz0(r0) __asm__ volatile("swc2 $16, 0( %0 )" : : "r"(r0) : "memory")

u32 *func_801139EC(u32 *f, u32 *ot, s32 n)
{
    s32 sz[4];
    s32 *otz = (s32 *)0x1F800004;
    T2PolyGT4 *p = D_800BF544;
    s32 *flg = (s32 *)0x1F800000;
    u32 c;
    u32 mode;
    s32 b, a, v, e;
    u32 *o;

    while (n-- != 0) {
        T2_ldv3p(f);
        c = f[0];
        p->rgb0 = c & 0xFFF0F0F0;
        T2_rtpt();
        p->rgb1 = (c << 4) & 0xF0F0F0;
        c = f[1];
        T2_stflg(flg);
        if (*flg >= 0) {
            T2_nclip();
            p->uv0 = f[2];
            T2_stopz(flg);
            if (*flg > 0) {
                T2_stsxy3_gt4(p);
                T2_ldv1p(f);
                p->rgb2 = c & 0xF0F0F0;
                T2_rtps();
                p->rgb3 = (c << 4) & 0xF0F0F0;
                p->uv1 = f[3];
                T2_stflg(flg);
                if (*flg >= 0) {
                    T2_stsxy(&p->x3);
                    if ((p->x0 < 320 || p->x1 < 320 || p->x2 < 320 || p->x3 < 320) &&
                        (p->y0 < 240 || p->y1 < 240 || p->y2 < 240 || p->y3 < 240)) {
                        p->uv1 = f[3];
                        mode = c >> 24;
                        if (mode != 0) {
                            T2_stsz0(&sz[0]);
                            T2_stsz1(&sz[1]);
                            T2_stsz2(&sz[2]);
                            T2_stsz3(&sz[3]);
                            do {
                                if (mode == 1) {
                                    a = sz[1];
                                    if (a < sz[0]) {
                                        a = sz[0];
                                    }
                                    b = sz[3];
                                    if (b < sz[2]) {
                                        b = sz[2];
                                    }
                                    if (b < a) {
                                        b = a;
                                    }
                                } else {
                                    a = sz[1];
                                    if (sz[0] < a) {
                                        a = sz[0];
                                    }
                                    b = sz[3];
                                    if (sz[2] < b) {
                                        b = sz[2];
                                    }
                                    if (a < b) {
                                        b = a;
                                    }
                                }
                                *otz = b >> 2;
                            } while (0);
                        } else {
                            T2_avsz4();
                            do {
                                T2_stotz(otz);
                            } while (0);
                            do {
                                e = *otz >> 10;
                                *otz = (*otz >> e) + (e << 9);
                            } while (0);
                            do {
                                if ((u32)(*otz - 4) >= 0x7FC) {
                                    *otz = -1;
                                }
                            } while (0);
                            if (*otz >= 0) {
                                do {
                                    o = ot + *otz;
                                    p->tag = *o | 0x0C000000;
                                    *o = (u32)p;
                                } while (0);
                                v = f[4];
                                p->uv2 = v;
                                p->uv3 = (u32)v >> 16;
                                p++;
                            }
                        }
                    }
                }
            }
        }
        f += 11;
    }
    D_800BF544 = p;
    return f;
}

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

extern s16 D_801249E4[];
void func_80114BBC(u16 *a, s16 *v)
{
    s32 i;
    s32 n = a[0];
    s16 *t;
    s16 *s;
    s16 *d = (s16 *)a;
    if (n == 0) return;
    t = D_801249E4;
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

extern u8 *D_8011DC14[];
extern u8 *D_8011E9A8[];
extern u8 *D_801204AC[];
extern u8 *D_801234F0[];
extern u8 *D_8012488C[];
extern u8 *D_801249CC[];
#define EP_FRAME(a) (*(s16 *)((a) + 0x64))
#define EP_MODEL(a) (*(u8 **)(*(u8 **)((a) + 0xC0) + 0x40))
s32 func_80114CA0(u8 *a)
{
    switch (a[7]) {
    case 0:
        break;
    case 1:
        func_80114BBC(EP_MODEL(a), D_8011DC14[EP_FRAME(a)]);
        if (++EP_FRAME(a) >= 8) {
            EP_FRAME(a) = 7;
            return 1;
        }
        break;
    case 2:
        func_80114BBC(EP_MODEL(a), D_8011E9A8[EP_FRAME(a)]);
        if (++EP_FRAME(a) >= 7) {
            EP_FRAME(a) = 0;
            a[7] = 0;
            return 1;
        }
        break;
    case 3:
        func_80114BBC(EP_MODEL(a), D_801204AC[EP_FRAME(a)]);
        if (++EP_FRAME(a) >= 6) {
            EP_FRAME(a) = 5;
            return 1;
        }
        break;
    case 4:
        func_80114BBC(EP_MODEL(a), D_801204AC[EP_FRAME(a)]);
        if (++EP_FRAME(a) >= 14) {
            EP_FRAME(a) = 13;
            return 1;
        }
        break;
    case 5:
        func_80114BBC(EP_MODEL(a), D_801249CC[EP_FRAME(a)]);
        if (++EP_FRAME(a) >= 6) {
            EP_FRAME(a) = 5;
            return 1;
        }
        break;
    case 6:
    case 7:
    case 8:
        func_80114BBC(EP_MODEL(a), D_801234F0[EP_FRAME(a)]);
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
        func_80114BBC(EP_MODEL(a), D_8012488C[EP_FRAME(a)]);
        if (++EP_FRAME(a) >= 10) {
            EP_FRAME(a) = 9;
            return 1;
        }
        break;
    }
    return 0;
}

extern SVec D_1F8000C0;
extern LVec D_1F8000A0;
extern u16 D_800E7ED6;
extern u8 D_80124D50[];
extern void *D_80124DD8[];
extern void *D_80124F0C[];
extern void *D_80124F20[];
s32 func_80114F68(u8 *a)
{
    s32 s;
    void *q;
    u8 *pl;
    u16 r;
    s = a[6];
    switch (s) {
    case 0:
        a[6] = 1;
        func_80040CDC(a, 0, D_80124D50);
        a[0x70] = 1;
        break;
    case 1:
        func_80041098(a);
        if (a[0x70] != 0xFF) {
            return 0;
        }
        a[6]++;
        func_80040CDC(a, 0, D_80124DD8[D_800BF870.unk0 - 10]);
        a[0x70] = 1;
        break;
    case 2:
        func_80041098(a);
        if (a[0x70] != 0xFF) {
            return 0;
        }
        a[6]++;
        if (!(D_800BF870.pad1[0x1A7] & 0x1F)) {
            func_80040CDC(a, 0, D_80124F20[D_800BF870.unk0 - 10]);
        } else {
            func_80040CDC(a, 0, D_80124F0C[D_800BF870.unk0 - 10]);
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

extern s16 D_800BF83A;
extern s32 D_800ECF58[];
extern s32 D_80124D14[];
extern s32 D_80124D28[];
extern s32 D_80124D3C[];
extern u8 D_801249A4[];
extern u8 D_80017FC0[];
extern u8 D_1F800236;
extern s16 D_1F800240;
typedef struct { u8 pad[0x5E6]; u16 f5E6; } GameState5E6;
#define G ((u8 *)&D_800BF870)

void func_801152CC(u8 *a)
{
    s32 one = 1;
    u8 v;
    u8 *g;
    u8 *q;
    s32 k;

    switch (a[4]) {
    case 0:
        if (func_800519E0(a, 5, D_800ECF58[D_80124D14[D_800BF870.unk0 - 10]], D_801249A4) == 0) {
            W(a, 0x3C) = D_800ECF58[D_80124D28[D_800BF870.unk0 - 10]];
            func_80077C40(a, D_80017FC0, 0);
            H(a, 0x54) = 0;
            H(a, 0x56) = 0;
            H(a, 0x58) = 0;
            a[0] = one;
            H(a, 0x80) = 50;
            H(a, 0x82) = 100;
            H(a, 0x84) = 50;
            H(a, 0x86) = 100;
            a[4]++;
        }
        break;
    case 1:
        U(a, 0x32) += 8;
        U(a, 0x56) += 0x40;
        func_8007778C(a);
        func_8004190C(a);
        func_800518FC(a);
        break;
    case 2:
        switch (a[5]) {
        case 0:
            func_8004D4C4(D_80124D3C[D_800BF870.unk0 - 10], 1);
            func_8004B0D8(a);
            H(a, 0x40) = 60;
            a[5]++;
            break;
        case 1:
            if (--H(a, 0x40) == 0) {
                a[6] = 0;
                a[5]++;
                func_80042354(1, 3);
            }
            break;
        case 2:
            if (func_80114F68(a) != 0) {
                a[5]++;
            }
            break;
        case 3:
            k = D_800BF870.unk0 - 10;
            g = G;
            v = g[0x1A8] | (1 << k);
            g[0x1A8] = v;
            if ((v & 0x1F) == 0x1F) {
                a[6] = 0;
                a[5]++;
            } else {
                a[5] += 2;
            }
            break;
        case 4:
            if (func_801151A8(a) != 0) {
                a[5]++;
            }
            break;
        case 5:
            a[4] = 3;
            q = (u8 *)&D_800BF808_76d5;
            q[0x31] = 1;
            q[7] = 0;
            switch (D_800BF870.unk0) {
            case 10:
                D_800BF83A = 0x607;
                ((GameState5E6 *)G)->f5E6 |= 6;
                break;
            case 11:
                D_800BF83A = 0x80C;
                ((GameState5E6 *)G)->f5E6 |= 0x30;
                break;
            case 12:
                D_800BF83A = 0x105;
                ((GameState5E6 *)G)->f5E6 |= 0x40;
                break;
            case 13:
                D_800BF83A = 0x404;
                ((GameState5E6 *)G)->f5E6 |= 0x80;
                break;
            case 14:
                D_800BF83A = 0xB;
                ((GameState5E6 *)G)->f5E6 |= 0x100;
                break;
            }
            D_1F800236 = 8;
            D_1F800240 = D_800BF870.unk0;
            break;
        }
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

s32 func_8011568C(u8 *a, u8 *b)
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

#define P(p, o) (*(void **)((u8 *)(p) + (o)))
#define P(p, o) (*(u8 **)((u8 *)(p) + (o)))
extern u8 D_1F800259;
extern u8 D_800BF84C;

void func_801158FC(u8 *a)
{
    u8 *b = D_1F80024C_2bfb;
    s32 r, done, x, z, k;
    u16 t;

    switch (a[6]) {
    case 0:
        func_800521F4(0, 0, 0x81, 2);
        func_80114CA0(a);
        if (func_8011568C(a, b) != 0) {
            a[7] = 4;
            a[6]++;
            b[6] = 3;
            H(a, 0x44) = -0x3000;
            U(a, 0x66) = U(a, 0x2E);
            U(a, 0x68) = U(a, 0x32);
            U(a, 0x6A) = U(a, 0x36);
        }
        break;
    case 1:
        r = func_80114CA0(a);
        if (H(a, 0x44) > 0x3000) {
            done = 1;
        } else {
            x = (func_80083F50(H(a, 0x56) + 0x400) * H(a, 0x44)) >> 4;
            z = func_80083E80(H(a, 0x56) + 0x400) * H(a, 0x44);
            W(a, 0x2C) += x;
            t = U(a, 0x44) + 0x500;
            done = (s16)t > 0x3000;
            U(a, 0x44) = t;
            W(a, 0x34) += -z >> 4;
        }
        if (done && r) {
            U(a, 0x2E) = U(a, 0x66);
            U(a, 0x36) = U(a, 0x6A);
            U(b, 0x6E)--;
            a[7] = 6;
            H(a, 0x64) = 0;
            a[6]++;
        }
        break;
    case 2:
        U(a, 0x32) = H(a, 0x68) - 0x20 + (func_8009A450() & 0x3F);
        if (func_80114CA0(a) != 0) {
            if (H(b, 0x6E) == 0) {
                D_800BF84C = 1;
                func_80075070(0xFE);
                D_1F800259 = 1;
                a[5] = 3;
                a[6] = 0;
                a[7] = 9;
                H(a, 0x64) = 0;
                break;
            }
            func_80074590(0x83, 0, 0);
            a[7] = 5;
            H(a, 0x64) = 0;
            a[6]++;
            U(a, 0x2E) = U(a, 0x66);
            U(a, 0x32) = U(a, 0x68);
            U(a, 0x36) = U(a, 0x6A);
        }
        break;
    case 3:
        if (func_80114CA0(a) != 0) {
            k = 1;
            a[6] += k;
            b[6] = 6;
            b[7] = 0;
            if (D_800BF870.unk0 == 15) {
                k = 2;
            }
            if (H(b, 0x6E) == k) {
                switch (D_800BF870.unk0) {
                case 10:
                case 11:
                case 15:
                    W(P(b, 0xE0), 0x40) = 0;
                    W(P(b, 0xE4), 0x40) = 0;
                    break;
                case 12:
                    W(P(b, 0xE4), 0x40) = 0;
                    W(P(b, 0xE8), 0x40) = 0;
                    W(P(b, 0xEC), 0x40) = 0;
                    W(P(b, 0xF0), 0x40) = 0;
                    W(P(b, 0xF4), 0x40) = 0;
                    W(P(b, 0xF8), 0x40) = 0;
                    W(P(b, 0xFC), 0x40) = 0;
                    W(P(b, 0x100), 0x40) = 0;
                    break;
                case 13:
                case 14:
                    W(P(b, 0xE0), 0x40) = 0;
                    W(P(b, 0xE4), 0x40) = 0;
                    W(P(b, 0xE8), 0x40) = 0;
                    break;
                }
            }
            U(a, 0x40) = 0x14;
        }
        break;
    case 4:
        if (--H(a, 0x40) == 0) {
            a[0x29] = 0;
            a[5] = 0;
            a[6] = 0;
            a[7] = 2;
            H(a, 0x64) = 0;
        }
        break;
    }
}

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_80115CC0);

s32 func_80116198(u8 *a0)
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

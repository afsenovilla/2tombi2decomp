#include "common.h"
#include "game.h"
#include "m2c.h"
#include "gte.h"

extern u8 D_1F800246_6eef;
#define H(p, o) (*(s16 *)((u8 *)(p) + (o)))

void func_801092BC(u8 *a, u8 *b)
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
void func_801093F4(u8 *a, u8 *b)
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

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80109630);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80109ACC);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80109F7C);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8010A3D0);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8010A550);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8010A6E0);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8010A93C);

extern u8 **D_1F80013C;
extern u8 D_1F800144;
extern s16 D_1F800150_058c;
extern u8 D_1F800150;
extern u8 D_1F800183;
extern u8 D_1F800182;
extern u8 **D_1F800148;
void func_8010ACA8(void)
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
                    case 8:
                        func_8010A6E0(e, o, *(u8 **)(o + 0xC0));
                        break;
                    case 0x18:
                        if (e[0] == 4 && func_800240FC(e) != 0) {
                            e[0x5E] = 1;
                            e[0] = 10;
                        }
                        break;
                    case 0x64:
                        if (e[2] == 0x66) {
                            func_801092BC(e, o);
                        }
                        break;
                    }
                }
            }
        }
    }
}

extern u8 *D_800F2738;
void func_8010AE50(void)
{
    u8 *p;
    u8 **l;
    u8 *e;
    s32 r;

    if (*(s16 *)&D_1F800144 == 0) {
        return;
    }
    for (p = D_800F2738; p != NULL; p = *(u8 **)(p + 0x24)) {
        if (!(p[0] & 1) || p[0x2B] != 0) {
            continue;
        }
        l = D_1F80013C;
        D_1F800182 = D_1F800144;
        while (D_1F800182 != 0) {
            e = *l;
            D_1F800182--;
            l++;
            if (e[0] & 1) {
                switch (e[2]) {
                case 0x55:
                    break;
                case 0x4F:
                    func_8010A550(p, e);
                    break;
                case 0x66:
                    if (func_80022F04(p, e) != 0) {
                        if (D_800BF870.unk0 == 14) {
                            if (e[0xBF] != 0) {
                                r = func_8001E860(p, e, 0, 0);
                            } else {
                                r = func_8001DC9C(p, e, 0, 1);
                            }
                        } else if (e[0] & 8) {
                            r = func_8001E860(p, e, 0, 0);
                        } else {
                            r = func_8001DC9C(p, e, 0, 1);
                        }
                        if (!(r & 0x80)) {
                            D_1F800182 = 0;
                        }
                    }
                    break;
                }
            }
        }
    }
}

void func_8010B010(void)
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
                case 0x12:
                    func_800216B4(p, e, 0);
                case 8:
                    func_80109ACC(p, e, *(void **)(e + 0xC0));
                    break;
                }
            }
        }
    }
}

extern s8 D_800BF808[];
extern u8 D_1F800137;
extern u8 D_800E7E80[];
/* func_8010B680, inlined */
static inline void inl_8010B680(u8 *a)
{
    u8 **l = D_1F800148;
    u8 *p;
    D_1F800182 = D_1F800150;
    while (D_1F800182 != 0) {
        p = *l;
        D_1F800182--;
        l++;
        if ((p[0] & 1) && p[2] == 8) {
            func_80109630(a, p, *(void **)(p + 0xC0));
        }
    }
}
static inline void inl_list13C_8010B128(u8 *a)
{
    u8 **l = D_1F80013C;
    u8 *p;
    D_1F800182 = D_1F800144;
    while (D_1F800182 != 0) {
        p = *l;
        D_1F800182--;
        l++;
        if (p[0] & 1) {
            switch (p[2]) {
            case 0x4F:
                func_8010A3D0(a, p);
                break;
            case 0x55:
                func_8010A93C(a, p);
                break;
            case 0x66:
                func_801093F4(a, p);
                break;
            }
        }
    }
}
void func_8010B128(void)
{
    u8 *g = D_800E7E80;
    u16 v;
    s32 m;

    func_8002288C(g);
    switch (g[0]) {
    case 0:
    case 6:
        break;
    case 2:
        if (*(u32 *)(g + 0x158) < 2) {
            inl_8010B680(g);
        }
        break;
    case 1:
    case 3:
    case 4:
    case 5:
    case 7:
    default:
        func_80022760(g);
        inl_list13C_8010B128(g);
        if (*(u32 *)(g + 0x158) < 2) {
            inl_8010B680(g);
        }
        break;
    }
    func_8010AE50();
    func_8010B010();
    func_8010ACA8();
    if (D_1F800137 == 0 && D_800BF808[5] == 0) {
        v = *(u16 *)(g + 0x6A);
        m = v & 0xF00;
        if (v & 0x8000) {
            *(u16 *)(g + 0x6A) = 0;
            D_800BF808[0x16] = 0;
            if (m == 0x700) {
                g[0] = 3;
                g[4] = 2;
                g[5] = 5;
                g[6] = 0;
                g[7] = 0;
            } else if (m == 0x900) {
                g[0x2B] = (*(s16 *)(g + 0x56) + 0x800) >> 4;
                func_80022D08(g, 0, 1, 1);
            }
        }
    }
}

void func_8010B444(u8 *a)
{
    u16 v;
    s32 m;
    if (D_800BF808[5] == 0) {
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
            } else if (m == 0x900) {
                a[0x2B] = (*(s16 *)(a + 0x56) + 0x800) >> 4;
                func_80022D08(a, 0, 1, 1);
            }
        }
    }
}

void func_8010B4E4(u8 *a)
{
    u16 v;
    s32 m;
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
            } else if (m == 0x900) {
                a[0x2B] = (*(s16 *)(a + 0x56) + 0x800) >> 4;
                func_80022D08(a, 0, 1, 1);
            }
        }
    }
}

void func_8010B590(u8 *a)
{
    u8 **l = D_1F80013C;
    u8 *e;

    D_1F800182 = D_1F800144;
    while (D_1F800182 != 0) {
        e = *l;
        D_1F800182--;
        l++;
        if (e[0] & 1) {
            switch (e[2]) {
            case 0x4F:
                func_8010A3D0(a, e);
                break;
            case 0x55:
                func_8010A93C(a, e);
                break;
            case 0x66:
                func_801093F4(a, e);
                break;
            }
        }
    }
}

void func_8010B680(u8 *a)
{
    u8 **l = D_1F800148;
    u8 *p;
    D_1F800182 = D_1F800150;
    while (D_1F800182 != 0) {
        p = *l;
        D_1F800182--;
        l++;
        if ((p[0] & 1) && p[2] == 8) {
            func_80109630(a, p, *(void **)(p + 0xC0));
        }
    }
}

s32 func_8010B734(void) {
    return 0;
}

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8010B73C);

extern u8 D_800BF809;
void func_80114608();
/* func_8010BDF4, inlined */
static inline void inl_8010BDF4(void *arg0) {
    s16 temp_a1;
    s16 temp_v0;
    s16 var_v0;
    s16 var_v1;

    temp_a1 = M2C_FIELD(arg0, s16 *, 0x44);
    var_v0 = temp_a1;
    if (temp_a1 < 0) {
        var_v0 = -var_v0;
    }
    temp_v0 = var_v0 - 0xE0;
    var_v1 = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        var_v1 = 0;
    }
    if (temp_a1 >= 0) {
        M2C_FIELD(arg0, s16 *, 0x44) = var_v1;
        return;
    }
    M2C_FIELD(arg0, s16 *, 0x44) = (s16) -var_v1;
}
void func_8010B938(u8 *a)
{
    s8 k;
    u8 *e;
    s32 s;

    a[0x177] |= 2;
    func_80076D68();
    switch (a[6]) {
    case 0:
        if (a[7] == 0) {
            func_80074590(0x23, 0, 0);
            func_800312D4(6, a + 0x2C, -0x50);
        }
        D_800BF809 = 0;
        a[7] = 0;
        a[0x61] = 0;
        a[0x146] = 0;
        *(s16 *)(a + 0x58) = 0;
        func_80053D90(a);
        k = a[0x147] + 2;
        a[0x14A] = k;
        a[0x149] = k;
        func_80054D14(a, 2, 4);
        e = func_8007A980(2, 3, 1);
        if (e != NULL) {
            *(void **)(e + 0x1C) = func_80114608;
            e[2] = 0;
            e[0x28] |= 0x80;
        }
        func_800551C4(a);
        s = a[0x145];
        if (s == 1) {
            a[6] = 1;
            break;
        }
        if (s == 2) {
            a[6] = s;
            break;
        }
        a[0x145] = 0;
        a[4] = 1;
        a[5] = 0x1A;
        a[6] = 0;
        a[7] = 0;
        break;
    case 1:
        inl_8010BDF4(a);
        func_80056B48(a, 1);
        func_80055D5C(a);
        *(s16 *)(a + 0x4A) += 0x400;
        if (*(s16 *)(a + 0x4A) > 0) {
            a[0x145] = 2;
            a[6]++;
        }
        *(s32 *)(a + 0x30) += *(s16 *)(a + 0x4A) << 8;
        func_800551C4(a);
        break;
    case 2:
        inl_8010BDF4(a);
        func_80056B48(a, 1);
        func_80055D5C(a);
        *(s16 *)(a + 0x4A) += 0x400;
        if (*(s16 *)(a + 0x4A) > 0x3E00) {
            *(s16 *)(a + 0x4A) = 0x3E00;
        }
        *(s32 *)(a + 0x30) += *(s16 *)(a + 0x4A) << 8;
        func_8005444C(a);
        if (a[0x29] != 0) {
            func_8005314C(a);
            func_800551C4(a);
            a[4] = 1;
            a[0x148] = 0;
            *(s16 *)(a + 0x50) = 0;
            a[0x145] = 0;
            a[5] = 0x1A;
            a[6] = 0;
            a[7] = 0;
        }
        break;
    }
}

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8010BC10);

extern s8 D_1F80027E[];
extern u8 D_800BFA1A;
void func_8010BD50(void *arg0) {
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
    if (!(D_800BFA1A & 2)) {
        func_80042354(1, 5);
        func_8001CF2C();
        M2C_FIELD(arg0, s8 *, 4) = 4;
    }
}

void func_8010BDF4(void *arg0) {
    s16 temp_a1;
    s16 temp_v0;
    s16 var_v0;
    s16 var_v1;

    temp_a1 = M2C_FIELD(arg0, s16 *, 0x44);
    var_v0 = temp_a1;
    if (temp_a1 < 0) {
        var_v0 = -var_v0;
    }
    temp_v0 = var_v0 - 0xE0;
    var_v1 = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        var_v1 = 0;
    }
    if (temp_a1 >= 0) {
        M2C_FIELD(arg0, s16 *, 0x44) = var_v1;
        return;
    }
    M2C_FIELD(arg0, s16 *, 0x44) = (s16) -var_v1;
}

u8 *func_8010BE38(void) {
    u8 *p = func_8007A980(2, 3, 1);
    if (p != NULL) {
    M2C_FIELD(p, void **, 0x1C) = func_80114608;
    p[2] = 0;
    p[0x28] |= 0x80;
    return p;
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
#define U(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define W(p, o) (*(s32 *)((u8 *)(p) + (o)))
void func_8010BE80(u8 *a, u8 *b, s32 ang)
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

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8010C0A4);

void func_8010C300(void) {
}

void func_8010C308(void) {
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
extern Spawn *D_801182B4[];
extern Pos D_800BF808_76d5;
typedef struct { u8 x, y, z; s8 t; } Spark;
typedef struct { s16 a, b, c, d; } S8;
typedef struct { s16 x, y, z, pad; } SV;
typedef struct { s16 x, y, z; } V3;
typedef struct { s16 x, y, z, pad; } SVec;
typedef struct { u16 x, p0, y, p1, z, p2; } LVec;
typedef struct { u16 a, b; } Range;
void func_8010C310(Owner *a, s32 sel)
{
    Spawn *e;
    u8 *p;
    a->count = 0;
    e = D_801182B4[sel];
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

void func_8010C488(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 4);
    switch (temp_v1) {                              /* irregular */
    case 0:
        M2C_FIELD(arg0, u8 *, 4) = 1U;
        func_8010C310(arg0, 0U);
        func_800310F4(0xC05, 0);
        func_800752B4(1);
        func_80075D24(0x1FFF);
        return;
    case 1:
        if (func_80026AD0(arg0) != 0) {
            func_8010C310(arg0, M2C_FIELD(arg0, u8 *, 3));
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

void func_8010C554(u8 *a, u8 *b, s32 ang)
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

extern void *D_8011A52C[];
extern u8 *D_1F800248;
void func_8010C778(u8 *a)
{
    u8 *pl = D_800E7E80;
    s32 s;
    s = a[4];
    switch (s) {
    case 0:
        if (func_80051B70(a, 0xC, D_8011A52C[D_800BF870.unk0 - 10]) == 0) {
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

s32 func_8010C948(u8 *a)
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

extern u8 *D_8011A4FC[][2];
void func_8010CA34(u8 *a)
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
    t = D_8011A4FC[D_800BF870.unk0 - 10][low];
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

typedef struct {
    s16 x;
    s16 y;
    s16 z;
    s16 f;
} SelPt;
extern SelPt D_8011A26C_75fb[];
extern u8 D_800E7EAA;
extern u8 D_1F80025C[];
extern u16 D_1F800160_71b4_70bb;
extern u16 D_1F800162_b816;
extern u16 D_1F800164_d75f_59c5;
s32 func_8010CB44(void *arg0, s32 mode)
{
    u8 *a = arg0;
    s16 dist[4];
    s32 best;
    s32 sel;
    s32 i, j, k;
    s32 d;
    s32 found;
    s32 fl;
    s32 v;
    SelPt *p;
    s16 dx, dy, dz;

    sel = 0;
    best = 0xFFFFFFF;
    dist[0] = -1;
    dist[1] = -1;
    dist[2] = -1;
    dist[3] = -1;
    *(s16 *)(a + 0x72) = -1;
    D_1F80025C[0] = 0xFF;
    D_1F80025C[1] = 0xFF;
    D_1F80025C[2] = 0xFF;
    D_1F80025C[3] = 0xFF;
    switch (D_800BF870.unk0) {
    case 10:
    case 11:
    case 13:
    case 14:
        fl = D_800BF870.unk0 == 11;
        for (i = 0; i < 0x3A; i++) {
            if (fl) {
                if (D_800E7EAA == 1) {
                    if (D_8011A26C_75fb[i].f != 1) {
                        continue;
                    }
                } else if (D_8011A26C_75fb[i].f == 1) {
                    continue;
                }
            }
            dx = D_1F800160_71b4_70bb - D_8011A26C_75fb[i].x;
            dz = D_1F800164_d75f_59c5 - D_8011A26C_75fb[i].z;
            d = func_80084080(dx * dx + dz * dz);
            dy = D_1F800162_b816 - 0x190;
            if (d < 0x640 && dy < D_8011A26C_75fb[i].y) {
                found = 0;
                for (k = 0; k < 4; k++) {
                    if (dist[k] == -1) {
                        found = 1;
                        dist[k] = d;
                        D_1F80025C[k] = i;
                        break;
                    }
                }
                if (!found) {
                    for (j = 0; j < 4; j++) {
                        for (k = j + 1; k < 4; k++) {
                            s32 t = dist[j];
                            if (t < dist[k]) {
                                dist[j] = dist[k];
                                dist[k] = t;
                                t = D_1F80025C[j];
                                D_1F80025C[j] = D_1F80025C[k];
                                D_1F80025C[k] = t;
                            }
                        }
                    }
                    for (k = 0; k < 4; k++) {
                        if (d < dist[k]) {
                            dist[k] = d;
                            D_1F80025C[k] = i;
                            break;
                        }
                    }
                }
            }
            if (d < best) {
                best = d;
                sel = i;
            }
        }
        switch (mode) {
        case 0:
            i = (func_8009A450() & 0x30) >> 4;
            break;
        case 1:
            i = 0;
            break;
        case 2:
            i = (func_8009A450() & 0x20) >> 5;
            break;
        case 3:
        case 4:
            i = (func_8009A450() & 0x20) >> 5;
            i++;
            break;
        case 5:
            i = (func_8009A450() & 0x40) >> 6;
            i++;
            break;
        }
        for (k = 0; k < 4; k++, i++) {
            j = D_1F80025C[i & 3];
            if (j != -1) {
                break;
            }
        }
        if (j != -1) {
            sel = j;
        }
        *(s16 *)(a + 0x72) = sel;
        return sel;
    case 12:
    case 15:
        fl = D_800BF870.unk0 == 15;
        for (i = 0; i < 0x3A; i++) {
            if (fl) {
                if (D_800E7EAA == 1) {
                    if (D_8011A26C_75fb[i].f != 1) {
                        continue;
                    }
                } else if (D_8011A26C_75fb[i].f == 1) {
                    continue;
                }
            }
            dx = D_1F800160_71b4_70bb - D_8011A26C_75fb[i].x;
            dy = D_1F800162_b816 - D_8011A26C_75fb[i].y;
            dz = D_1F800164_d75f_59c5 - D_8011A26C_75fb[i].z;
            d = func_80084080(dx * dx + dy * dy + dz * dz);
            if (d < 0x640) {
                found = 0;
                for (k = 0; k < 4; k++) {
                    if (dist[k] == -1) {
                        found = 1;
                        dist[k] = d;
                        D_1F80025C[k] = i;
                        break;
                    }
                }
                if (!found) {
                    for (j = 0; j < 4; j++) {
                        for (k = j + 1; k < 4; k++) {
                            s32 t = dist[j];
                            if (t < dist[k]) {
                                dist[j] = dist[k];
                                dist[k] = t;
                                t = D_1F80025C[j];
                                D_1F80025C[j] = D_1F80025C[k];
                                D_1F80025C[k] = t;
                            }
                        }
                    }
                    for (k = 0; k < 4; k++) {
                        if (d < dist[k]) {
                            dist[k] = d;
                            D_1F80025C[k] = i;
                            break;
                        }
                    }
                }
            }
            if (d < best) {
                best = d;
                sel = i;
            }
        }
        switch (mode) {
        case 0:
            i = (func_8009A450() & 0x30) >> 4;
            break;
        case 1:
            i = 0;
            break;
        case 2:
            i = (func_8009A450() & 0x10) >> 4;
            break;
        case 3:
        case 4:
            i = (func_8009A450() & 0x20) >> 5;
            i++;
            break;
        case 5:
            i = (func_8009A450() & 0x40) >> 6;
            i += 2;
            break;
        }
        for (k = 0; k < 4; k++, i++) {
            j = D_1F80025C[i & 3];
            if (j != -1) {
                break;
            }
        }
        if (j != -1) {
            sel = j;
        }
        *(s16 *)(a + 0x72) = sel;
        return sel;
    }
}

typedef struct { u16 x, y, z; u8 k; u8 pad; } ArenaPt;
extern u8 D_800E7FC5;
extern ArenaPt D_8011A26C[];
extern s16 D_1F800160_71b4;
extern s16 D_1F800164_d75f;
extern s16 D_1F800162;
extern s16 D_1F8001A4;
extern u8 D_1F80025B;
void func_8010D1F0(u8 *a)
{
    ArenaPt *e;
    ArenaPt *e2;
    ArenaPt *e3;
    u8 *q;
    u8 *g;
    s32 k;
    ArenaPt *t, *t2, *t3;
    s32 o;

    switch (a[6]) {
    case 0:
        func_80041768(a, 2, 6);
        a[6]++;
    case 1:
        if (func_8010C948(a) != 0) {
            a[0] = 2;
            func_80041768(a, 3, 2);
        }
        if (U(*(u8 **)(a + 0x38), 2) & 0x8000) {
            func_80074590(0x80, 0, 0);
            a[0] = 2;
            H(a, 0x40) = 0x10;
            a[0x1A] = 0x80;
            a[0x19] = 0x80;
            a[0x18] = 0x80;
            H(a, 0x4A) = 0;
            a[6]++;
            a[0xD] |= 2;
        }
        break;
    case 2:
        if ((H(a, 0x4A) -= 0x300) < -0x3000) {
            H(a, 0x4A) = -0x3000;
        }
        W(a, 0x30) += H(a, 0x4A) << 8;
        if (--H(a, 0x40) == 0) {
            a[1] = 0;
            H(a, 0x40) = 0x28;
            a[6]++;
        }
        a[0x19] = a[0x1A] = a[0x18] -= 8;
        break;
    case 3:
        a[1] = 0;
        if (D_800BF809 != 0) {
            break;
        }
        if (--H(a, 0x40) != 0) {
            break;
        }
        k = func_8010CB44(a, H(a, 0x64));
        switch (D_800BF870.unk0) {
        case 10:
        case 11:
        case 13:
            t = D_8011A26C; e = &t[k];
            H(a, 0x2E) = e->x;
            H(a, 0x32) = e->y;
            H(a, 0x36) = e->z;
            a[0x2A] = e->k;
            if (D_800E7FC5 == 0 && H(a, 0x32) > D_1F800162) {
                U(a, 0x32) = *(u16 *)&D_1F800162;
            }
            func_80048894(a);
            if (H(a, 0x32) > D_1F8001A4) {
                U(a, 0x32) = *(u16 *)&D_1F8001A4;
            }
            U(a, 0x32) = (u16)(U(a, 0x32) - 0x168) - (u16)(U(a, 0x86) - U(a, 0x84));
            switch (H(a, 0x64)) {
            case 0:
            case 1:
            case 2:
            case 5:
                U(a, 0x32) -= (func_8009A450() & 0x30) * 8;
                break;
            case 3:
                U(a, 0x32) -= 0x64;
                break;
            case 4:
                U(a, 0x32) -= 0xC8;
                break;
            }
            break;
        case 14:
            t2 = D_8011A26C; e2 = &t2[k];
            H(a, 0x2E) = e2->x;
            H(a, 0x32) = e2->y;
            H(a, 0x36) = e2->z;
            a[0x2A] = e2->k;
            func_80048894(a);
            if (H(a, 0x32) > D_1F8001A4) {
                U(a, 0x32) = *(u16 *)&D_1F8001A4;
            }
            U(a, 0x32) = (u16)(U(a, 0x32) - 0x168) - (u16)(U(a, 0x86) - U(a, 0x84));
            switch (H(a, 0x64)) {
            case 0:
                U(a, 0x32) -= (func_8009A450() & 0x30) * 9;
                break;
            case 1:
            case 2:
            case 5:
                U(a, 0x32) -= (func_8009A450() & 0x30) * 8;
                break;
            case 3:
                U(a, 0x32) -= 0x64;
                break;
            case 4:
                U(a, 0x32) -= 0xC8;
                break;
            }
            break;
        case 12:
        case 15:
            t3 = D_8011A26C; e3 = &t3[k];
            H(a, 0x2E) = e3->x;
            H(a, 0x32) = e3->y;
            H(a, 0x36) = e3->z;
            a[0x2A] = e3->k;
            U(a, 0x32) = (u16)(U(a, 0x32) - 0x168) - (u16)(U(a, 0x86) - U(a, 0x84));            break;
        }
        H(a, 0x40) = 0x10;
        func_80041768(a, 4, 4);
        a[6]++;
        MEMBER_AT(s16, a, 0x4A) = 0x3000;
        H(a, 0x56) = func_800776F8((s16)func_800782B0(a + 0x2C, D_1F800160_71b4, D_1F800164_d75f), H(a, 0x56), 0x80);
        func_80041AC0(a);
        func_80074590(0x81, 0, 0);
        if (D_800BF870.unk0 == 0xD && H(a, 0x6E) >= 2) {
            q = *(u8 **)(a + 0xE0);
            if (W(q, 0x40) == 0 && D_1F80025B == 0) {
                g = (u8 *)&D_800BF808_76d5;
                W(q, 0x40) = W(g, 0x58);
                W(*(u8 **)(a + 0xE8), 0x40) = W(g, 0x60);
            }
        }
        break;
    case 4:
        if ((H(a, 0x4A) -= 0x300) < 0) {
            H(a, 0x4A) = 0;
        }
        W(a, 0x30) += H(a, 0x4A) << 8;
        if (--H(a, 0x40) == 0) {
            a[6]++;
            a[0xD] &= 0xFD;
        }
        a[0x19] = a[0x1A] = a[0x18] += 8;
        H(a, 0x56) = func_800776F8((s16)func_800782B0(a + 0x2C, D_1F800160_71b4, D_1F800164_d75f), H(a, 0x56), 0x80);
        break;
    case 5:
        a[0] = 1;
        func_80041768(a, 0, 6);
        switch (H(a, 0x64)) {
        case 0:
            a[5] = 0;
            break;
        case 1:
        case 2:
            if (D_800BF870.unk0 == 0xF) {
                if (H(a, 0x6E) < 3) {
                    a[5] = 6;
                } else {
                    a[5] = 5;
                }
            } else {
                if (H(a, 0x6E) < 2) {
                    a[5] = 6;
                } else {
                    a[5] = 5;
                }
            }
            break;
        case 3:
        case 4:
            a[5] = 2;
            break;
        case 5:
            a[5] = 3;
            break;
        }
        a[6] = 0;
        a[7] = 0;
        H(a, 0x56) = func_800776F8((s16)func_800782B0(a + 0x2C, D_1F800160_71b4, D_1F800164_d75f), H(a, 0x56), 0x80);
        break;
    }
}

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8010D884);

void func_8010E0E8(u8 *a)
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
        if (*(s16 *)(a + 0x40) < 0x1E && func_8010C948(a) != 0) {
            a[0] = 2;
            func_80041768(a, 3, 4);
            func_8010CA34(a);
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

typedef struct {
    u16 lo;
    s16 hi;
} Half;
extern u8 D_1F800250;
extern s16 D_1F800240;
extern s16 D_1F800244;
extern u16 D_1F8000F2;
extern s32 D_800BF850;
extern u8 D_800E8008[];
void func_8010E22C(u8 *a, u8 *b)
{
    Half v[3];
    s32 s, c;
    s16 v44;

    switch (a[5]) {
    case 0:
    case 2:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
        switch (a[6]) {
        case 0:
            {
                u8 *g = (u8 *)&D_800BF808_76d5;
                if (g[0x39] != 0) {
                    g[1] = 0;
                    g[0x39] = 0;
                }
            }
            a[0] = 8;
            D_1F800246_6eef = 0;
            a[0x5E] = 0;
            D_1F800250 = 0;
            if (a[5] == 2) {
                if (b[0x147] != 0) {
                    a[0xBE] = 0;
                    H(a, 0x44) = -0x1000;
                } else {
                    a[0xBE] = 1;
                    H(a, 0x44) = 0x1000;
                }
            } else if (func_80077768(H(a, 0x60), a[0x2B] << 4, 0) != 0) {
                a[0xBE] = 0;
                H(a, 0x44) = -0x1000;
            } else {
                a[0xBE] = 1;
                H(a, 0x44) = 0x1000;
            }
            H(a, 0x4A) = -0x3400;
            a[6]++;
            func_80041768(a, 9, 4);
            func_8004130C(a, 0);
            break;
        case 1:
            if ((H(a, 0x4A) += 0x360) > 0) {
                a[0x18] = a[0x19] = a[0x1A] = 0x80;
                a[6]++;
                a[0xD] |= 2;
            }
            W(a, 0x30) += H(a, 0x4A) << 8;
            func_80076D68(a);
            func_80041A1C(a, 1);
            if (a[0x5F] == 0) {
                s16 h = (H(a, 0x86) - H(a, 0x84)) / 2;
                s16 q = H(a, 0x84) / 2;
                s16 d = U(a, 0x80);
                s16 ang;
                if (a[0xBE] == 0) {
                    ang = U(a, 0x60);
                } else {
                    ang = U(a, 0x60) + 0x800;
                }
                if (func_80045CAC(a, d, h, ang) != 0 || func_80045CAC(a, d, (s16)-q, ang) != 0) {
                    a[0x5F] = a[0xBE] + 2;
                }
            }
            func_80041AC0(a);
            func_8004130C(a, 0);
            break;
        case 2:
            H(a, 0x4A) += 0x360;
            if (H(a, 0x4A) > 0x3000) {
                H(a, 0x4A) = 0x3000;
            }
            func_80076D68(a);
            func_80041A1C(a, 1);
            W(a, 0x30) += H(a, 0x4A) << 8;
            if (a[0x5F] == 0) {
                s16 h = (H(a, 0x86) - H(a, 0x84)) / 2;
                s16 q = H(a, 0x84) / 2;
                s16 d = U(a, 0x80);
                s16 ang;
                if (a[0xBE] == 0) {
                    ang = U(a, 0x60);
                } else {
                    ang = U(a, 0x60) + 0x800;
                }
                if (func_80045CAC(a, d, h, ang) != 0 || func_80045CAC(a, d, (s16)-q, ang) != 0) {
                    a[0x5F] = a[0xBE] + 2;
                }
            }
            func_80041AC0(a);
            func_8004130C(a, 0);
            a[0x19] = a[0x1A] = (a[0x18] -= 0x10);
            if (a[0x18] == 0) {
                a[1] = 2;
                a[0] = 2;
                a[0x2B] = 0;
                a[4] = 1;
                H(a, 0x40) = 0x3C;
                func_8010CA34(a);
                a[5] = 1;
                a[6] = 3;
                a[7] = 0;
                H(a, 0x54) = 0;
                H(a, 0x58) = 0;
            }
            break;
        }
        break;
    case 1:
        switch (a[6]) {
        case 0:
            H(a, 0x80) = 0x64;
            H(a, 0x82) = 0xC8;
            if (D_800BF870.unk0 == 0xD) {
                H(a, 0x84) = 0x10E;
                H(a, 0x86) = 0x208;
            } else {
                H(a, 0x84) = 0x64;
                H(a, 0x86) = 0xC8;
            }
            D_1F800250 = 0;
            D_1F800246_6eef = 1;
            func_80041718(a, 5, 4);
            a[6]++;
            func_80074590(0x87, 0, 0);
            H(a, 0x40) = 0x5A;
             
        case 1:
            if (H(a, 0x40) == 0) {
                if (D_800BF870.unk0 == 0xF) {
                    func_80074590(0x8C, 0, 0);
                }
                if (U(b, 4) != 0x301 || (b[5] == 3 && b[6] >= 3)) {
                    a[6]++;
                } else if (b[0] == 1 && b[5] == 3 && b[6] < 3) {
                    H(a, 0x2E) = H(b, 0x2E);
                    H(a, 0x36) = H(b, 0x36);
                    {
                        u8 e = b[0x2A];
                        H(a, 0x58) = 0;
                        a[0] = 8;
                        a[0x2A] = e;
                    }
                    b[0x2B] = U(b, 0x140) >> 4;
                    if (func_80022D08(b, a, 1, 1) == 0) {
                        b[4] = 2;
                        b[5] = 2;
                        b[6] = 0;
                        b[7] = 0;
                        H(b, 0x172) = 0x78;
                    }
                }
            } else {
                H(a, 0x40)--;
            }
             
        case 2:
        {
            s16 r = func_800776F8((s16)func_800782B0(a + 0x2C, D_1F800240, D_1F800244), H(a, 0x56), 0x80);
            s16 x = D_1F800240;
            H(a, 0x56) = r;
            H(b, 0x56) = r;
            v[0].hi = x;
            v[1].hi = U(b, 0x32);
            v[2].hi = D_1F800244;
        }
            func_8006CBA8(v);
            break;
        }
        break;
    case 3:
        switch (a[6]) {
        case 0:
            D_1F800250 = 0;
            a[0] = 4;
            MEMBER_AT(s16, a, 0x80) = 0x64;
            MEMBER_AT(s16, a, 0x82) = 0xC8;
            MEMBER_AT(s16, a, 0x84) = 0x64;
            MEMBER_AT(s16, a, 0x86) = 0xC8;
            a[0x2B] = 0;
            {
                u8 *g = (u8 *)&D_800BF808_76d5;
                g[0x39] = 1;
                g[1] = 1;
            }
            D_1F800246_6eef = 2;
            H(b, 0x56) = H(a, 0x56) = func_800776F8((s16)func_800782B0(a + 0x2C, D_1F800240, D_1F800244), H(a, 0x56), 0x80);
            func_80041718(a, 6, 4);
            a[6]++;
            v[0].hi = D_1F800240;
            v[1].hi = U(b, 0x32);
            v[2].hi = D_1F800244;
            func_8006CBA8(v);
            H(a, 0x44) = 0x40;
            H(a, 0x40) = 0x5A;
            if (((((0xC00 - D_1F8000F2) & 0xFFF) - U(a, 0x56)) & 0xFFF) < 0x800) {
                H(a, 0x6A) = 0x200;
            } else {
                H(a, 0x6A) = -0x200;
            }
            break;
        case 1:
            H(a, 0x58) = (U(a, 0x58) + 0x200) & 0xFFF;
            s = (func_80083F50(H(a, 0x56)) * H(a, 0x44)) >> 12;
            c = func_80083E80(H(a, 0x56));
            H(a, 0x2E) += s;
            H(a, 0x36) += -(c * H(a, 0x44)) >> 12;
            if (a[0x2B] == 0) {
                func_8010C554(D_800E8008, a, H(a, 0x6A));
            }
            if (a[0x5E] != 0) {
                D_1F800246_6eef = 0;
                a[6] = 4;
                a[7] = 0;
            } else if (H(a, 0x40) == 0) {
                a[0] = 8;
                a[6] = 7;
                a[7] = 0;
            } else {
                H(a, 0x40)--;
            }
            break;
        case 2:
        {
            s16 t;
            s16 k;
            s32 m;
            H(a, 0xB8) -= 0x80;
            if (H(a, 0xB8) < 0xC00) {
                H(a, 0xB8) = 0xC00;
            }
            t = H(a, 0x6A);
            m = __builtin_abs(t) + 0x20;
            k = m;
            {
                s16 bb = H(a, 0xB8);
                s16 r58 = (U(a, 0x58) + 0x200) & 0xFFF;
                H(a, 0xBA) = bb;
                H(a, 0xBC) = bb;
                H(a, 0x58) = r58;
            }
            if ((s16)m > 0x380) {
                k = 0x380;
            }
            if (t < 0) {
                H(a, 0x6A) = -k;
            } else {
                H(a, 0x6A) = k;
            }
            func_8010C554(D_800E8008, a, H(a, 0x6A));
            break;
        }
        case 3:
            a[1] = 2;
            H(a, 0xB8) = 0x1000;
            H(a, 0xBA) = 0x1000;
            H(a, 0xBC) = 0x1000;
            func_8010C554(D_800E8008, a, H(a, 0x6A));
            break;
        case 4:
        case 6:
            if (a[6] == 6) {
                func_8010C554(D_800E8008, a, H(a, 0x6A));
            }
            func_8006CBA8(a + 0x2C);
            switch (a[7]) {
            case 0:
                if (a[6] == 4) {
                    H(a, 0x4A) = -0x1000;
                    H(a, 0x44) = -0x1400;
                    H(a, 0x50) = 0x200;
                    func_80074590(0xE, 0, 0);
                } else {
                    H(a, 0x44) = -0x3000;
                    H(a, 0x4A) = 0;
                    H(a, 0x50) = 0x40;
                }
                H(a, 0x40) = 0x10;
                a[7]++;
                goto end;
            case 1:
                H(a, 0x58) -= 0x200;
                if ((H(a, 0x4A) += H(a, 0x50)) > 0) {
                    a[0x18] = a[0x19] = a[0x1A] = 0x80;
                    a[7]++;
                    a[0xD] |= 2;
                }
                break;
            case 2:
                a[0x19] = a[0x1A] = (a[0x18] -= 8);
                if (--H(a, 0x40) == 0) {
                    if (a[6] == 6) {
                        D_1F800246_6eef = 0;
                        if (D_800BF870.unk0 == 0xE && H(a, 0x6E) == 1) {
                            D_1F800137 = 2;
                            D_800BF850 = 1;
                            a[6] = 9;
                        } else {
                            a[6] = 5;
                        }
                    } else {
                        a[6] = 5;
                    }
                    a[7] = 0;
                }
                H(a, 0x58) -= 0x200;
                H(a, 0x4A) += 0x200;
                if (H(a, 0x4A) > 0x2000) {
                    H(a, 0x4A) = 0x2000;
                }
                break;
            default:
                goto end;
            }
            W(a, 0x30) += H(a, 0x4A) << 8;
            W(a, 0x2C) += (func_80083F50(H(a, 0x56)) * H(a, 0x44)) >> 4;
            W(a, 0x34) -= (func_80083E80(H(a, 0x56)) * H(a, 0x44)) >> 4;
            break;
        case 5:
            a[0x2B] = 0;
            a[1] = 2;
            func_8010CA34(a);
            H(a, 0x40) = 0x5A;
            a[4] = 1;
            a[5] = 1;
            a[0] = 2;
            a[6] = 3;
            a[7] = 0;
            H(a, 0x54) = 0;
            H(a, 0x58) = 0;
            H(a, 0x56) = 0;
            break;
        case 7:
        {
            s32 t;
            func_8006CBA8(a + 0x2C);
            H(a, 0x44) -= 8;
            if (H(a, 0x44) < 0x10) {
                H(a, 0x44) = 0x10;
            }
            t = (U(a, 0x58) + (U(a, 0x44) << 3)) & 0xFFF;
            H(a, 0x58) = t;
            if (H(a, 0x44) == 0x10 && (u32)((t + 0x80) & 0xFFF) < 0x101) {
                H(a, 0x58) = 0;
                a[6]++;
            }
            s = (func_80083F50(H(a, 0x56)) * H(a, 0x44)) >> 12;
            c = func_80083E80(H(a, 0x56));
            H(a, 0x2E) += s;
            H(a, 0x36) += -(c * H(a, 0x44)) >> 12;
            break;
        }
        case 8:
            D_1F800246_6eef = 0;
            a[1] = 2;
            a[0x2B] = 0;
            a[0] = 0xA;
            func_8010CA34(a);
            a[4] = 1;
            a[5] = 1;
            a[6] = 0;
            a[7] = 0;
            H(a, 0x54) = 0;
            H(a, 0x58) = 0;
            break;
        case 9:
            a[1] = 2;
            if (D_800BF850 == 0x80) {
                a[6] = 5;
                a[7] = 0;
            }
            break;
        }
        break;
    }
end:
    a[0x5E] = 0;
    a[0x29] = 0;
    a[0x5F] = 0;
    if (a[1] == 0) {
        func_80077E7C(a);
        a[1] = 1;
        func_8004190C(a);
        func_800518FC(a);
    }
}

extern u8 *D_1F80024C_2bfb;
extern u8 *D_1F800260;
extern u16 D_1F8001A0;
extern u16 D_1F8001A2;
void func_8010EF30(u8 *a)
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

extern u8 D_800BF80E;
extern u8 D_800BF80F;
extern u8 D_801182BC[];
extern s16 D_801197E0[];
extern s32 D_8011A544[];
void func_8010C778();
void func_8010F144(u8 *a)
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
            *(void **)(e + 0x1C) = func_8010C778;
        }
        *(u8 **)(a + 0x14) = e;
        a[6]++;
        break;
    case 1:
        if (D_800BF80F == 0) {
            a[6]++;
            pl[6] = 0;
            func_8004D604(D_8011A544[D_800BF870.unk0 - 10], 1);
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
            func_8006CBD0(D_800E8008, D_801182BC);
            t = &D_801197E0[H(a, 0x6A) * 3];
            U(a, 0x2E) = t[0];
            U(a, 0x32) = t[1];
            U(a, 0x36) = t[2];
            H(a, 0x6A)++;
            func_8006E1C0(7);
        }
        break;
    }
}

extern u8 *D_1F800214;
s32 func_8010F43C(u8 *a)
{
    u16 v = *(u16 *)(a + 0x72);
    u16 spd = v & 0xFFFE;
    u8 *o;
    u8 *t;
    s32 ang;

    if (!(v & 1)) {
        o = a;
    } else {
        o = D_1F800214;
    }
    t = D_1F800248;
    switch (a[0x78]) {
    case 0:
        ang = func_80085690(*(s16 *)(o + 0x36) - *(s16 *)(t + 0x36), *(s16 *)(t + 0x2E) - *(s16 *)(o + 0x2E)) & 0xFFF;
        *(s16 *)(a + 0x64) = ang;
        if (((ang - *(s16 *)(o + 0x56)) & 0xFFF) < (s16)spd || (s16)spd <= 0) {
            *(s16 *)(o + 0x56) = ang;
            return 1;
        }
        a[0x78]++;
        break;
    case 1:
        return func_80041438(o, *(s16 *)(a + 0x64), (s16)spd);
    }
    return 0;
}

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8010F544);

extern u8 D_1F80025A;
void f_UpdateLastEvilPigProjectileAttack(u8 *a)
{
    s16 t;
    s16 k;

    if (D_800BF809 != 0) {
        return;
    }
    switch (a[6]) {
    case 0:
        if (func_80077768((s16)func_800782B0(a + 0x2C, D_1F800160_71b4, D_1F800164_d75f), H(a, 0x60), 0) != 0) {
            a[0xBE] = 1;
        } else {
            a[0xBE] = 0;
        }
        if (D_1F80025A != 0) {
            H(a, 0x64) = 3;
            a[5] = 2;
            a[6] = 0;
            a[7] = 0;
            break;
        }
        a[6]++;
        break;
    case 1:
        if (func_8010C948(a) != 0) {
            goto hit;
        }
        if (a[0xBE] == 0) {
            k = U(a, 0x60);
        } else {
            k = U(a, 0x60) + 0x800;
        }
        k &= 0xFFF;
        t = func_800776F8(k, H(a, 0x56), 0x100);
        H(a, 0x56) = t;
        if (t == k) {
            func_80041768(a, 0xD, 5);
            a[6]++;
        }
        break;
    case 2:
        if (a[0x79] == 1) {
            a[6]++;
            func_80074590(0x8C, 0, 0);
            f_SpawnLastEvilPigBattleProjectile(a);
            H(a, 0x40) = 0x28;
        }
        break;
    case 3:
        if (func_8010C948(a) != 0) {
            goto hit;
        }
        if (--H(a, 0x40) == 0) {
            a[6]++;
            func_80041768(a, 0, 6);
            H(a, 0x40) = 0x1E;
        }
        break;
    case 4:
        if (func_8010C948(a) != 0) {
        hit:
            a[0] = 2;
            func_80041768(a, 3, 4);
            func_8010CA34(a);
            a[5] = 1;
            a[6] = 1;
            a[7] = 0;
            break;
        }
        if (--H(a, 0x40) == 0) {
            a[5] = 0;
            a[6] = 0;
            H(a, 0x64) = 0;
        }
        break;
    }
}

extern u8 D_800BF808_1760[];
extern u8 D_800ECF58_742e[];
extern u8 D_8011A634[];
extern u8 D_8011A574[];
extern u8 D_80124F20[];
extern u8 D_8002AB5C[];
void func_8010EF30();
void func_80110118();
extern s32 D_1F800254;
static inline s32 set_pos(u8 *a, s16 *v)
{
    H(a, 0x2E) = v[0];
    H(a, 0x32) = v[1];
    H(a, 0x36) = v[2];
    return func_801175B8(a, 1, 0);
}
void func_8010FC1C(u8 *a)
{
    u8 *pl = D_800E7E80;
    u8 *t;
    u8 *p;

    switch (a[4]) {
    case 0:
        switch (a[5]) {
        case 0:
            t = D_800ECF58_742e;
            if (func_800519E0(a, 0x11, *(void **)(t + 0x48), D_8011A634) != 0) {
                break;
            }
            H(a, 0x80) = 0x5A;
            H(a, 0x82) = 0xB4;
            H(a, 0x84) = 0xAA;
            H(a, 0x86) = 0x10E;
            a[0x1B] = 0;
            H(a, 0x58) = 0;
            H(a, 0x56) = 0;
            H(a, 0x54) = 0;
            a[0x47] = 0;
            H(a, 0x40) = 0;
            a[0x29] = 0;
            a[0x5E] = 0;
            a[1] = 0;
            a[0x1A] = 0x80;
            a[0x19] = 0x80;
            a[0x18] = 0x80;
            a[0xD] |= 1;
            p = func_8007A980(0, 6, 1);
            if (p != NULL) {
                *(void **)(p + 0x1C) = func_8010EF30;
                p[0xB] = 0x20;
                *(u8 **)(p + 0x10) = a;
                *(void **)(p + 0x18) = D_8002AB5C;
                p[0x28] |= 0x80;
            }
            *(void **)(a + 0x3C) = *(void **)(t + 0x4C);
            D_1F80024C_2bfb = a;
            if (D_800BFA1A & 2) {
                *(void **)(a + 0x7C) = D_80124F20;
                a[5]++;
                break;
            }
            a[0] = 8;
            a[0xBE] = 0;
            func_80040CDC(a, D_80124F20, D_8011A574);
            a[0x7B] = 0;
            *(void **)(a + 0x1C) = func_80110118;
            a[5] = 0;
            func_80041718(a, 0, 0);
            D_1F800254 = set_pos(a, D_801197E0);
            break;
        case 1:
            a[4] = 1;
            a[5] = 0;
            a[6] = 0;
            a[7] = 0;
            H(a, 0x64) = 0;
            H(a, 0x66) = 0;
            H(a, 0x68) = 0;
            H(a, 0x6A) = 0;
            H(a, 0x6C) = 0;
            H(a, 0x6E) = 3;
            a[0x2A] = 0;
            func_80041718(a, 0, 0);
            a[0] = 2;
            H(a, 0x56) = func_800782B0(a + 0x2C, D_1F800160_71b4, D_1F800164_d75f);
            break;
        }
        break;
    case 1:
        a[1] = 1;
        H(a, 0x80) = 0x5A;
        H(a, 0x82) = 0xB4;
        H(a, 0x84) = 0xAA;
        H(a, 0x86) = 0x10E;
        if (a[0x2B] != 0) {
            a[0x2B]--;
        } else {
            if (D_800BF809 == 0) {
                func_8004190C(a);
            }
            switch (a[5]) {
            case 0:
                {
                    u8 *g = D_800BF808_1760;
                    if (((s8 *)g)[5] != 0 || g[1] != 0) {
                        break;
                    }
                }
                switch (a[6]) {
                case 0:
                    a[6]++;
                case 1:
                    func_8010CA34(a);
                    if (func_8010C948(a) != 0) {
                        a[1] = 1;
                        a[0] = 2;
                        a[5] = 1;
                        a[6] = 1;
                        func_80041768(a, 3, 4);
                    }
                    a[7] = 0;
                    break;
                }
                H(a, 0x56) = func_800776F8((s16)func_800782B0(a + 0x2C, D_1F800160_71b4, D_1F800164_d75f), H(a, 0x56), 0x80);
                break;
            case 1:
                func_8010D1F0(a);
                break;
            case 2:
                func_8010D884(a);
                break;
            case 3:
                func_8010E0E8(a);
                break;
            case 4:
                if (D_800BF809 != 0) {
                    break;
                }
                switch (a[6]) {
                case 0:
                    func_80041768(a, 0xA, 4);
                    H(a, 0x40) = (func_8009A450() & 0x30) + 0x28;
                    a[6]++;
                    break;
                case 1:
                    if (--H(a, 0x40) == 0) {
                        func_80041768(a, 0, 0xA);
                        a[5] = 0;
                        a[6] = 0;
                        H(a, 0x64) = 0;
                    }
                    H(a, 0x56) = func_800776F8((s16)func_800782B0(a + 0x2C, D_1F800160_71b4, D_1F800164_d75f), H(a, 0x56), 0x80);
                    break;
                }
                break;
            case 5:
                func_8010F544(a);
                break;
            case 6:
                f_UpdateLastEvilPigProjectileAttack(a);
                break;
            }
        }
        if (a[1] != 0) {
            func_80077E7C(a);
            func_800518FC(a);
        }
        a[0x5F] = 0;
        a[0x5E] = 0;
        a[0x29] = 0;
        break;
    case 2:
        func_8010E22C(a, pl);
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

typedef struct { s32 x, y, z; } Vec3;
void func_8010FC1C();
extern u8 *D_1F800254_7a89;
void func_80110118(u8 *a)
{
    s16 *t;
    u8 *p;
    Half v[3];
    s32 s0;
    s32 s;

    switch (a[5]) {
    case 0:
        func_8010F144(a);
        break;
    case 1:
        if (H(a, 0x6A) != -1) {
            func_8006CBD0(D_800E8008, D_801182BC + H(a, 0x6A) * 12);
            t = &D_801197E0[H(a, 0x6A) * 3];
            U(a, 0x2E) = t[0];
            U(a, 0x32) = t[1];
            U(a, 0x36) = t[2];
            H(a, 0x6A)++;
            if (*(s16 *)(D_801182BC + H(a, 0x6A) * 12) == 0) {
                H(a, 0x6A) = -1;
            }
        }
        p = D_1F800254_7a89;
        switch (a[6]) {
        case 0:
            a[1] = 2;
            *(Vec3 *)(p + 0x2C) = *(Vec3 *)(a + 0x2C);
            if (H(a, 0x6A) >= 0x168) {
                a[6]++;
                p[4] = 2;
            }
            break;
        case 1:
            H(a, 0x4A) = -0x4000;
            H(a, 0x44) = 0x3000;
            a[6]++;
            H(a, 0x64) = H(a, 0x2E);
            H(a, 0x66) = H(a, 0x32);
            H(a, 0x68) = H(a, 0x36);
        case 2:
        {
            s16 ang;
            MEMBER_AT(s16, a, 0x2E) = H(a, 0x64);
            MEMBER_AT(s16, a, 0x32) = H(a, 0x66);
            MEMBER_AT(s16, a, 0x36) = H(a, 0x68);
            ang = func_800782B0(a + 0x2C, D_1F800160_71b4, D_1F800164_d75f);
            H(a, 0x56) = ang;
            s0 = (func_80083F50(ang) * H(a, 0x44)) >> 4;
            s = func_80083E80(H(a, 0x56)) * H(a, 0x44);
            *(s32 *)(a + 0x2C) += s0;
            *(s32 *)(a + 0x30) += H(a, 0x4A) << 8;
            *(s32 *)(a + 0x34) -= s >> 4;
            if ((H(a, 0x4A) += 0x200) > 0) {
                a[6]++;
            }
            H(a, 0x44) -= 0x80;
            if (H(a, 0x44) < 0) {
                H(a, 0x44) = 0;
            }
            H(a, 0x64) = H(a, 0x2E);
            H(a, 0x66) = H(a, 0x32);
            H(a, 0x68) = H(a, 0x36);
            break;
        }
        case 3:
            H(a, 0x2E) = H(a, 0x64);
            H(a, 0x32) = H(a, 0x66);
            H(a, 0x36) = H(a, 0x68);
            v[0].hi = 0x2C7E;
            v[1].hi = -0x2101;
            v[2].hi = 0x2011;
            if (func_8006CEC4(a + 0x2C, v, 0xE0) != 0) {
                a[6]++;
            }
            MEMBER_AT(s16, a, 0x64) = H(a, 0x2E);
            MEMBER_AT(s16, a, 0x66) = H(a, 0x32);
            MEMBER_AT(s16, a, 0x68) = H(a, 0x36);
            H(a, 0x56) = func_800782B0(a + 0x2C, D_1F800160_71b4, D_1F800164_d75f);
            break;
        case 4:
            H(a, 0x2E) = H(a, 0x64);
            H(a, 0x32) = H(a, 0x66);
            H(a, 0x36) = H(a, 0x68);
            if (H(a, 0x6A) == -1) {
                a[0x70] = 2;
                a[6]++;
            }
            break;
        case 5:
            func_80041098(a);
            if ((s8)a[0x70] <= 0) {
                a[6]++;
            }
            break;
        case 6:
        {
            u8 *g;
            a[0] = 1;
            *(void **)(a + 0x1C) = func_8010FC1C;
            a[5] = 1;
            a[6] = 0;
            func_8006E1E4();
            func_80042310();
            H(a, 0x2E) = 0x9C0;
            H(a, 0x32) = -0x578;
            H(a, 0x36) = 0xEED;
            g = (u8 *)&D_800BF870;
            H(a, 0x58) = 0;
            g[0x1AA] |= 2;
            break;
        }
        }
        if (a[1] == 0) {
            func_8007778C(a);
            func_8004190C(a);
            func_800518FC(a);
        }
        break;
    }
}

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80110540);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_801106A4);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80110800);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80110A98);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_801110BC);

extern u8 *D_800ECF88;
typedef struct { u8 a, b, c, d; } Ent;
void func_801113B4(u8 *a)
{
    Ent *e;
    s32 i;
    s32 k;
    u8 *b;
    s32 *h;
    u8 *base = a + 0x50;

    switch (a[4]) {
    case 0:
        e = (Ent *)base;
        for (i = 0; i < 0xE; i++) {
            k = i & 3;
            e[i].b = func_8009A450();
            e[i].c = func_8009A450() & 0x1F;
            if (k == 0) {
                e[i].a = func_8009A450() & 0x7F;
            } else if (k == 1) {
                e[i].a = (func_8009A450() & 0x7F) + 0x30;
            } else {
                e[i].a = (func_8009A450() & 0x7F) + 0x60;
            }
            ;
        }
        a[4] = 1;
        a[5] = 0;
        a[7] = 0x19;
        *(s16 *)(a + 0x48) = func_8009A450();
        *(s16 *)(a + 0x4A) = func_8009A450();
        *(s16 *)(a + 0x4C) = func_8009A450();
        b = D_800ECF88;
        h = (s32 *)(b + 4);
        *(u8 **)(a + 0x3C) = b + h[4];
        *(u8 **)(a + 0x34) = b + h[5];
        *(u8 **)(a + 0x38) = b + h[6];
    case 1:
        if (--a[7] == 0) {
            a[4] = 2;
            break;
        }
        e = (Ent *)base;
        for (i = 0; i < 0xE; i++) {
            e[i].c += 4;
            ;
        }
        *(s16 *)(a + 0x48) += func_8009A450() >> 7;
        k = func_8009A450();
        a[1] = 1;
        *(s16 *)(a + 0x4A) += k >> 8;
        break;
    case 2:
    case 3:
        func_8007A624(a);
        break;
    }
}

typedef struct {
    u8 b[4];
} T2Bytes4;
typedef struct {
    s16 x, y, z;
} T2Vec3s;
extern T2Bytes4 D_801091CC;
extern s32 D_800ED8C8_7a94;
void func_8011159C(u8 *a)
{
    T2Bytes4 c;
    T2Vec3s pos, rot;
    s32 i = 0;
    u8 *e = a + 0x50;
    s32 ang;
    s32 r, sx, sz, k, o;

    c = D_801091CC;
    ang = H(a, 0x4C);
    do {
        r = e[i * 4 + 2] * 16;
        sx = func_80083F50(ang) * e[i * 4 + 1];
        sz = func_80083E80(ang) * e[i * 4 + 1];
        pos.x = U(a, 0x2C) + ((sx * r) >> 20);
        pos.z = U(a, 0x30) + ((sz * r) >> 20);
        pos.y = U(a, 0x2E) - ((func_80083E80(r) * e[i * 4 + 0]) >> 10);
        k = i & 3;
        if (i & 1) {
            rot.x = -U(a, 0x48);
            rot.y = -U(a, 0x4A);
            rot.z = -U(a, 0x4C);
        } else {
            rot.x = U(a, 0x48);
            rot.y = U(a, 0x4A);
            rot.z = U(a, 0x4C);
        }
        func_800318A0(&pos, &c, &rot);
        if (k == 0) {
            func_8003F698(W(a, 0x3C), D_800ED8C8_7a94, 0);
        } else if (k == 1) {
            func_8003F698(W(a, 0x34), D_800ED8C8_7a94, 0);
        } else {
            func_8003F698(W(a, 0x38), D_800ED8C8_7a94, 0);
        }
        i++;
        ang += 0x124;
    } while (i < 14);
}

void func_80111770(u8 *a)
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
extern s32 D_1F800090_81f3[];
extern u8 D_8011BFA0[];
extern u8 D_8011BF58[];
extern u8 D_8011C034[];
void func_8011199C(u8 *a)
{
    s32 s;
    u8 *b = a;
    s32 *p = D_1F800084;
    s32 *d = D_1F800090_81f3;
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
        func_8002847C(D_8011BFA0, D_8011C034[b[5] >> 1], 0);
        func_8002847C(D_8011BF58, D_8011C034[b[6] >> 1], 0);
    }
}

typedef struct { u8 *v[6]; } PtrTab6;
typedef struct { u8 b[8][4]; } ByteTab8;
extern PtrTab6 D_801091D0;
extern ByteTab8 D_801091E8;
extern u8 D_8011BF34[];
void func_80111AB0(u8 *a)
{
    PtrTab6 p;
    ByteTab8 t;
    u8 *q;
    s32 *d;
    u8 **pp;
    u8 (*tt)[4];
    u8 *e;
    q = a;
    d = D_1F800090_81f3;
    p = D_801091D0;
    t = D_801091E8;
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
        func_80027768(D_8011BF34, e[3], 0, 0);
    }
}

extern S8 D_80124E20[];
void func_80111C5C(u8 *a)
{
    u8 *t = D_1F80024C_2bfb;
    s32 i;
    H(a, 0x2C) = H(t, 0x2E);
    H(a, 0x2E) = H(t, 0x32);
    H(a, 0x30) = H(t, 0x36);
    switch (a[4]) {
    case 0:
        for (i = 0; i < 0x20; i++) {
            D_80124E20[i].a = H(a, 0x2C);
            D_80124E20[i].b = H(a, 0x2E);
            D_80124E20[i].c = H(a, 0x30);
            D_80124E20[i].d = 0;
        }
        a[4] = 1;
        a[5] = 0;
    case 1:
        if (D_1F800250 == 0) {
            a[4] = 2;
        }
        for (i = 0x1F; i > 0; i--) {
            D_80124E20[i].a = D_80124E20[i - 1].a;
            D_80124E20[i].b = D_80124E20[i - 1].b;
            D_80124E20[i].c = D_80124E20[i - 1].c;
            D_80124E20[i].d = D_80124E20[i - 1].d;
        }
        D_80124E20[0].a = H(a, 0x2C);
        D_80124E20[0].b = H(a, 0x2E);
        D_80124E20[0].c = H(a, 0x30);
        D_80124E20[0].d = 1;
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

extern s32 D_80124D80[];
extern u8 D_80124E00[];
void func_80111E00(u8 *a)
{
    s32 i;
    s32 c, g, b;
    for (i = 0; i < 0x20; i++) {
        c = ((0x20 - i) * a[5]) / 32 + 1;
        g = c - (c >> 4);
        b = c - (c >> 3);
        if (D_80124E20[i].d == 0) {
            D_80124D80[i] = 0;
            if (i != 0) {
                D_80124D80[i - 1] = 0;
            }
            if (i != 0x1F) {
                D_80124D80[i + 1] = 0;
            }
            break;
        }
        if (i < 2) {
            D_80124D80[i] = 0;
            D_80124E00[i] = 0x10;
        } else {
            D_80124D80[i] = (b << 16) | (g << 8) | c;
            D_80124E00[i] = 0x21 - i;
        }
    }
    func_80029664(D_80124E20, i, D_80124D80, D_80124E00);
}

extern u16 D_1F80017C;
extern u8 D_8011C048[];
typedef struct { u8 pad[0x48]; s16 r[3]; } RotAct;
void func_80111F18(u8 *a)
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
            *(u8 **)(a + 0x34) = D_8011C048;
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
extern u32 *D_800ED8C8_065b;
AreaPolyFT4 *func_801120AC(AreaPolyFT4 *p, s32 x, s32 y, s32 w, s32 h, s16 c, s16 cy) {
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
        p->tag = D_800ED8C8_065b[4] | 0x09000000;
        D_800ED8C8_065b[4] = (u32)p;
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
        p->tag = D_800ED8C8_065b[4] | 0x09000000;
        D_800ED8C8_065b[4] = (u32)p;
        return p + 1;
    }

}

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_801121E8);

#define P(p, o) (*(void **)((u8 *)(p) + (o)))
void func_80112704(u8 *a)
{
    s16 v;
    switch (a[4]) {
    case 0:
        a[4] = 1;
        v = (func_8009A450() & 0x1FF) + 0x180;
        *(s16 *)(a + 0x4A) = v;
        *(s16 *)(a + 0x48) = v;
    case 1:
        if ((P(a, 0x34) = P(a, 0x38)) == 0) {
            a[4] = 2;
        } else if (func_8002B278(a) == 0) {
            func_80031780(a);
        }
        break;
    case 2:
    case 3:
        func_8007A624(a);
        break;
    }
}

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_801127BC);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80112880);

void func_80112974(u8 *a)
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
#define T2_ldv1p(r0)                                                                                                   \
    __asm__ volatile("lw $12, 0x24(%0);"                                                                               \
                     "lwc2 $0, 0x28(%0);"                                                                              \
                     "srl $12, $12, 16;"                                                                               \
                     "mtc2 $12, $1"                                                                                    \
                     :                                                                                                 \
                     : "r"(r0)                                                                                         \
                     : "$12")
#define T2_rtpt() __asm__ volatile(".word 0x4A280030")
#define T2_rtps() __asm__ volatile(".word 0x4A180001")
#define T2_nclip() __asm__ volatile(".word 0x4B400006")
#define T2_avsz3() __asm__ volatile(".word 0x4B58002D")
#define T2_avsz4() __asm__ volatile(".word 0x4B68002E")
#define T2_stflg(r0) __asm__ volatile("cfc2 $12, $31;" "nop;" "sw $12, 0( %0 )" : : "r"(r0) : "$12", "memory")
#define T2_stopz(r0) __asm__ volatile("swc2 $24, 0( %0 )" : : "r"(r0) : "memory")
#define T2_stotz(r0) __asm__ volatile("swc2 $7, 0( %0 )" : : "r"(r0) : "memory")
#define T2_stsxy(r0) __asm__ volatile("swc2 $14, 0( %0 )" : : "r"(r0) : "memory")
#define T2_stsxy3_gt4(r0)                                                                                              \
    __asm__ volatile("swc2 $12, 8( %0 );" "swc2 $13, 20( %0 );" "swc2 $14, 32( %0 )" : : "r"(r0) : "memory")
#define T2_stsxy3_gt3(r0)                                                                                              \
    __asm__ volatile("swc2 $12, 8( %0 );" "swc2 $13, 20( %0 );" "swc2 $14, 32( %0 )" : : "r"(r0) : "memory")
#define T2_stsz0(r0) __asm__ volatile("swc2 $16, 0( %0 )" : : "r"(r0) : "memory")
#define T2_stsz1(r0) __asm__ volatile("swc2 $17, 0( %0 )" : : "r"(r0) : "memory")
#define T2_stsz2(r0) __asm__ volatile("swc2 $18, 0( %0 )" : : "r"(r0) : "memory")
#define T2_stsz3(r0) __asm__ volatile("swc2 $19, 0( %0 )" : : "r"(r0) : "memory")
extern void *D_800BF544;
u32 *func_80112A24(u32 *f, u32 *ot, s32 n)
{
    s32 sz[6];
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
                    __asm__ volatile("nop");
                    p->rgb2 = (c << 4) & 0xF0F0F0;
                    mode = c >> 24;
                    switch (mode) {
                    case 1:
                        T2_stsz1(&sz[0]);
                        T2_stsz2(&sz[1]);
                        T2_stsz3(&sz[2]);
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
                        goto store;
                    case 2:
                        T2_stsz1(&sz[3]);
                        T2_stsz2(&sz[4]);
                        T2_stsz3(&sz[5]);
                        if (sz[3] < sz[4]) {
                            b = sz[5];
                            if (sz[3] < b) {
                                b = sz[3];
                            }
                            e = b;
                        } else {
                            b = sz[5];
                            if (sz[4] < b) {
                                b = sz[4];
                            }
                            e = b;
                        }
                    store:
                        *otz = e >> 2;
                        break;
                    default:
                        T2_avsz3();
                        T2_stotz(otz);
                        break;
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

u32 *func_80112CF0(u32 *f, u32 *ot, s32 n)
{
    s32 sz[8];
    s32 *otz = (s32 *)0x1F800004;
    T2PolyGT4 *p = D_800BF544;
    s32 *flg = (s32 *)0x1F800000;
    u32 c;
    u32 w;
    u32 mode;
    s32 b, a, v, e;
    u32 *o;

    while (n-- != 0) {
        T2_ldv3p(f);
        w = f[0];
        p->rgb0 = w & 0xFFF0F0F0;
        T2_rtpt();
        p->rgb1 = (w << 4) & 0xF0F0F0;
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
                        mode = c >> 24;
                        switch (mode) {
                        case 1:
                            T2_stsz0(&sz[0]);
                            T2_stsz1(&sz[1]);
                            T2_stsz2(&sz[2]);
                            T2_stsz3(&sz[3]);
                            do {
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
                                e = b;
                            } while (0);
                            goto store;
                        case 2:
                            T2_stsz0(&sz[4]);
                            T2_stsz1(&sz[5]);
                            T2_stsz2(&sz[6]);
                            T2_stsz3(&sz[7]);
                            do {
                                a = sz[5];
                                if (sz[4] < a) {
                                    a = sz[4];
                                }
                                b = sz[7];
                                if (sz[6] < b) {
                                    b = sz[6];
                                }
                                if (a < b) {
                                    b = a;
                                }
                                e = b;
                            } while (0);
                        store:
                            *otz = e >> 2;
                            break;
                        default:
                            T2_avsz4();
                            T2_stotz(otz);
                            break;
                        }
                        do {
                            e = *otz >> 10;
                            *otz = (*otz >> e) + (e << 9);
                        } while (0);
                        if ((u32)(*otz - 4) >= 0x7FC) {
                            *otz = -1;
                        }
                        if (*otz >= 0) {
                            v = f[4];
                            p->uv2 = v;
                            p->uv3 = (u32)v >> 16;
                            do {
                                o = ot + *otz;
                                p->tag = *o | 0x0C000000;
                                *o = (u32)p;
                            } while (0);
                            p++;
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

#define gte_SetRotMatrix(r0) __asm__ volatile("lw	$12, 0( %0 );" "lw	$13, 4( %0 );" "ctc2	$12, $0;" "ctc2	$13, $1;" "lw	$12, 8( %0 );" "lw	$13, 12( %0 );" "lw	$14, 16( %0 );" "ctc2	$12, $2;" "ctc2	$13, $3;" "ctc2	$14, $4" : : "r"(r0) : "$12", "$13", "$14")
#define gte_SetTransMatrix(r0) __asm__ volatile("lw	$12, 20( %0 );" "lw	$13, 24( %0 );" "ctc2	$12, $5;" "lw	$14, 28( %0 );" "ctc2	$13, $6;" "ctc2	$14, $7" : : "r"(r0) : "$12", "$13", "$14")
extern u8 D_1F8000F8[];
extern void *D_800ED8C8;
typedef struct {
    u8 pad0[6];
    u8 count;
    u8 pad7[5];
    u32 *tbl;
    u16 list[1];
} PartList;
void func_80113050(PartList *a)
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
    ot = D_800ED8C8;
    tbl = a->tbl;
    gte_SetRotMatrix(D_1F8000F8);
    gte_SetTransMatrix(D_1F8000F8);
    for (; p < end; p++) {
        e = &tbl[*p];
        v = *e;
        r = func_80112A24(e + 1, ot, v & 0xFF);
        v >>= 16;
        func_80112CF0(r, ot, v & 0xFF);
    }
}

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
u32 *func_80113150(u32 *f, u32 *ot, s32 n)
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
u32 *func_801133F4(u32 *f, u32 *ot, s32 n)
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

void func_80113728(u32 *p, void *b)
{
    u32 lo = *p;
    u32 packed;

    packed = lo;
    lo = packed & 0xFFFF;
    p += 4;
    func_801133F4(func_80113150(p, b, lo), b, packed >> 16);
}

typedef struct {
    s32 vx, vy;
} T2Pt32;
typedef struct {
    u8 pad0[2];
    s16 x;
    u8 pad4[6];
    s16 y;
    u8 padC[0x14];
    s16 rx;
    u16 ry;
} T2CamD0;
extern T2CamD0 D_1F8000D0_3bb0;
extern s32 D_800A3F90;
extern s32 D_800A3F94;
void func_80113770(u8 *a)
{
    T2Pt32 v0, v1, v2;
    T2CamD0 *c = &D_1F8000D0_3bb0;
    s32 ang, r, dx, dz;
    u16 t;

    D_800A3F90 = 0x5000;
    t = c->ry;
    D_800A3F94 = 0x25E;
    ang = (-(s16)t - D_800A3F94) & 0xFFF;
    v0.vx = c->x;
    v0.vy = c->y;
    v1.vx = v0.vx + ((func_80083E80(ang) * D_800A3F90) >> 12);
    v1.vy = v0.vy + ((func_80083F50(ang) * D_800A3F90) >> 12);
    ang = (D_800A3F94 - (s16)c->ry) & 0xFFF;
    v2.vx = v0.vx + ((func_80083E80(ang) * D_800A3F90) >> 12);
    v2.vy = v0.vy + ((func_80083F50(ang) * D_800A3F90) >> 12);
    r = abs(func_80083E80(c->rx));
    dx = (func_80083E80(-(s16)c->ry) * r) >> 12;
    dz = (func_80083F50(-(s16)c->ry) * r) >> 12;
    dx = (dx * D_800A3F90 * 5) >> 16;
    dz = (dz * D_800A3F90 * 5) >> 16;
    v1.vx -= dx;
    v1.vy -= dz;
    v2.vx -= dx;
    v0.vx -= dx;
    v2.vy -= dz;
    v0.vy -= dz;
    v0.vx /= 640;
    v0.vy /= 640;
    v1.vx /= 640;
    v1.vy /= 640;
    v2.vx /= 640;
    v2.vy /= 640;
    a[6] = 0;
    func_80113A28(a, &v0, &v1, &v2);
}

extern s32 D_800ECF58[];
typedef struct { u8 pad0[0x10]; s16 list[1]; } TriGrid;
#define TRI_ROW(L, R, N)                                                 \
    {                                                                    \
        s32 xe = (R) >> 16;                                              \
        s32 xs = (L) >> 16;                                              \
        s32 x;                                                           \
        if (y >= 0 && y < *(s16 *)(g + 0xA)) {                          \
            s16 *cell;                                                   \
            if (xe >= *(s16 *)(g + 8)) {                                 \
                xe = *(s16 *)(g + 8) - 1;                                \
            }                                                            \
            x = xs;                                                      \
            if (x < 0) {                                                 \
                x = 0;                                                   \
            }                                                            \
            cell = (s16 *)D_800ECF58[8];                                 \
            cell += 2;                                                   \
            cell += x * *(s16 *)(g + 0xA) + y;                           \
            while (x <= xe) {                                            \
                if (*cell != -1) {                                       \
                    u8 n = g[6];                                         \
                    if (n < 0xFE) {                                      \
                        g[6] = n + 1;                                    \
                        ((TriGrid *)g)->list[n] = *cell;                  \
                    }                                                    \
                }                                                        \
                x++;                                                     \
                cell += *(s16 *)(g + 0xA);                               \
            }                                                            \
        }                                                                \
    }
void func_80113A28(u8 *g, T2Pt32 *p0, T2Pt32 *p1, T2Pt32 *p2)
{
    s32 x0, y0, x1, y1, x2, y2, t;
    s32 dx01, dx02, dy01, dy02;
    s32 l, r, s01, s12, s02, cross, y;

    x0 = p0->vx;
    y0 = p0->vy;
    x1 = p1->vx;
    y1 = p1->vy;
    x2 = p2->vx;
    y2 = p2->vy;
    if (y1 == y0 && y1 == y2) {
        return;
    }
    if (y1 < y0) {
        t = x0; x0 = x1; x1 = t;
        t = y0; y0 = y1; y1 = t;
    }
    if (y2 < y0) {
        t = x0; x0 = x2; x2 = t;
        t = y0; y0 = y2; y2 = t;
    }
    if (y2 < y1) {
        t = x1; x1 = x2; x2 = t;
        t = y1; y1 = y2; y2 = t;
    }
    dx01 = x1 - x0;
    dx02 = x2 - x0;
    dy01 = y1 - y0;
    dy02 = y2 - y0;
    if (y1 == y0) {
        if (x0 < x1) {
            l = x0 << 16;
            r = x1 << 16;
        } else {
            l = x1 << 16;
            r = x0 << 16;
        }
        s01 = 0;
    } else {
        r = l = x0 << 16;
        s01 = (dx01 << 16) / dy01;
    }
    r += 0x10000;
    if (y1 == y2) {
        s12 = 0;
    } else {
        s12 = ((x2 - x1) << 16) / (y2 - y1);
    }
    s02 = (dx02 << 16) / dy02;
    cross = -dy02 * dx01 + dx02 * dy01;
    if (cross > 0) {
        for (y = y0; y < y1; y++) {
            TRI_ROW(l, r, 0);
            l += s01;
            r += s02;
        }
        for (; y <= y2; y++) {
            TRI_ROW(l, r, 1);
            l += s12;
            r += s02;
        }
    } else {
        for (y = y0; y < y1; y++) {
            TRI_ROW(l, r, 2);
            r += s01;
            l += s02;
        }
        for (; y <= y2; y++) {
            TRI_ROW(l, r, 3);
            l += s02;
            r += s12;
        }
    }
}

extern u16 *D_800ECF78;
void func_80113F68(u8 *a)
{
    u16 *p = D_800ECF78;
    u16 t;

    *(u16 **)(a + 0xC) = p;
    *(u16 *)(a + 8) = p[0];
    t = p[1];
    a[7] = 0;
    *(u16 *)(a + 0xA) = t;
}

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80113F94);

typedef struct {
    u32 tag;
    u32 rgbc;
    u32 xy;
    u16 uv;
    u16 clut;
} T2Sprt16;
extern T2Sprt16 *D_800BF544_e6cf;
void func_801141B0(u8 *a)
{
    s32 w2 = a[0x10] * 2;
    s32 size = w2 * a[0x11];
    u16 sx = U(a, 0x28);
    u16 sy = U(a, 0x2A);
    s16 x0 = sx - 160;
    s16 y0 = sy - 120;
    s16 row, col, x, y, c;
    T2Sprt16 *p, *start, *last, *q;
    u16 t;
    u16 k;
    s32 yy;

    last = NULL;

    row = y0 >> 4;
    if (row < 0) {
        do {
            row += a[0x11];
        } while (row < 0);
    }
    while (row >= a[0x11]) {
        row -= a[0x11];
    }
    sx = -sx + 0x98;
    sy = -sy + 0x70;
    row *= w2;
    col = x0 >> 4;
    if (col < 0) {
        do {
            col += a[0x10];
        } while (col < 0);
    }
    while (col >= a[0x10]) {
        col -= a[0x10];
    }
    col <<= 1;
    p = D_800BF544_e6cf;
    start = p;
    for (y = y0; y < y0 + 0x100; y += 16) {
        c = col;
        yy = (y & 0xFFF0) + (s16)sy;
        for (x = x0; x < x0 + 0x160;) {
            t = *(u16 *)(*(u8 **)(a + 0x14) + (row + c));
            c += 2;
            last = p;
            if (c >= w2) {
                c = 0;
            }
            p->xy = (((x & 0xFFF0) + (s16)sx) & 0xFFFF) | (yy << 16);
            p->uv = ((t << 4) & 0xF0) | ((t & 0xF0) << 8);
            k = U(a, 6);
            p->rgbc = 0x7D808080;
            ((u8 *)p)[3] = 3;
            ((u8 *)p)[7] = 0x7C;
            p->clut = k + ((t & 0xF00) >> 2);
            p++;
            x += 16;
            last->tag = (u32)p | 0x03000000;
        }
        row += w2;
        if (row >= size) {
            row -= size;
        }
    }
    last->tag = (last->tag & 0xFF000000) | D_800ED8C8_065b[0x7FF];
    func_80083DE0(p, 0, 0, U(a, 4), 0);
    p->tag = (u32)start | 0x02000000;
    q = p;
    p = (T2Sprt16 *)((u32 *)p + 3);
    *(T2Sprt16 **)&D_800ED8C8_065b[0x7FF] = q;
    D_800BF544_e6cf = p;
}

typedef struct { s16 h[7]; } E8013F238;
extern E8013F238 D_8011C120[];
void func_801144F4(u8 *a, s32 i)
{
    u8 **slot;
    u8 *e = func_8007AAE8();

    slot = (u8 **)(a + i * 4);
    if ((slot[0x30] = e) != NULL) {
        E8013F238 *tb = D_8011C120; s16 *t = tb[i].h;
        *(s16 *)(e + 6) = t[0];
        *(s16 *)(slot[0x30] + 0) = t[1];
        *(s16 *)(slot[0x30] + 2) = t[2];
        do {
            *(s16 *)(slot[0x30] + 4) = t[3];
        } while (0);
        *(s16 *)(slot[0x30] + 8) = 0;
        *(s16 *)(slot[0x30] + 0xA) = 0;
        *(s16 *)(slot[0x30] + 0xC) = 0;
        *(s16 *)(slot[0x30] + 0x38) = 0x1000;
        *(s16 *)(slot[0x30] + 0x3A) = 0;
        i++;
        *(s16 *)(slot[0x30] + 0x3C) = 0x1000;
        func_80051B04(slot[0x30], 0x16, i);
        a[9] = i;
        a[8] = i;
        func_80074590(0x91, 0, 0);
    } else {
        a[4] = 3;
    }
}

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80114608);

#define M(a) (*(u8 **)((a) + 0xC0))
void func_80114AA8(u8 *a)
{
    s32 d = 0;

    switch (a[4]) {
    case 0:
        if (func_80051B70(a, 0xC, 1) != 0) {
            break;
        }
        H(a, 0x80) = 0x2E9;
        H(a, 0x82) = 0x5D2;
        a[0] = 1;
        H(a, 0x84) = 0;
        H(a, 0x86) = 0x96;
        a[0x2B] = 0;
        a[0x29] = 0;
        H(a, 0x60) = 0;
        H(a, 0x96) = 0;
        a[0xBF] = 0;
        a[0x46] = 0;
        a[4]++;
        break;
    case 1:
        a[1] = 1;
        func_80077EBC(a);
        if (H(a, 0x44) != 0) {
            d = H(a, 0x44) >> 8;
            if (H(a, 0x44) < -0x20) {
                H(a, 0x44) += 0x20;
            } else if (H(a, 0x44) > 0x20) {
                H(a, 0x44) -= 0x20;
            } else {
                H(a, 0x44) = 0;
            }
        }
        if (a[0x29] != 0) {
            d += H(a, 0x60) * 48 / H(a, 0x80);
            d >>= 2;
        }
        if (d != 0) {
            H(M(a), 0xC) += d;
            if (d > 0) {
                if (H(M(a), 0xC) >= 0x200) {
                    H(M(a), 0xC) = 0x1FF;
                }
                if (a[0x46] != 1) {
                    a[0xBF] = 0;
                    a[0x46] = 1;
                }
            } else {
                if (H(M(a), 0xC) < -0x1FF) {
                    H(M(a), 0xC) = -0x1FF;
                }
                if (a[0x46] != 0xFF) {
                    a[0xBF] = 0;
                    a[0x46] = 0xFF;
                }
            }
            if (a[0xBF] == 0) {
                a[0xBF] = 1;
            }
        } else {
            a[0xBF] = 0;
        }
        func_800517F8(a);
        a[0x29] = 0;
        a[0x2B] = 0;
        break;
    case 2:
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

typedef struct { u16 a, b, c, d; } Box4;
extern Box4 D_8011C158[];
void func_80114CEC(u8 *a)
{
    switch (a[4]) {
    case 0:
        *(u16 *)(a + 0x80) = D_8011C158[a[3]].a;
        *(u16 *)(a + 0x82) = D_8011C158[a[3]].b;
        *(u16 *)(a + 0x84) = D_8011C158[a[3]].c;
        *(u16 *)(a + 0x86) = D_8011C158[a[3]].d;
        a[8] = 0;
        a[9] = 0;
        a[0] = 1;
        a[0xB] = 0;
        a[0x2B] = 0;
        *(s16 *)(a + 0x7C) = 0;
        *(s16 *)(a + 0x7E) = 0;
        a[4]++;
        break;
    case 1:
        func_8007778C(a);
        break;
    case 2:
    case 3:
        func_8007A624(a);
        break;
    }
}

extern s16 D_80123EF8[];
void func_80114DE8(u16 *a, s16 *v)
{
    s32 i;
    s32 n = a[0];
    s16 *t;
    s16 *s;
    s16 *d = (s16 *)a;
    if (n == 0) return;
    t = D_80123EF8;
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

extern u8 *D_8011D128[];
extern u8 *D_8011DEBC[];
extern u8 *D_8011F9C0[];
extern u8 *D_80122A04[];
extern u8 *D_80123DA0[];
extern u8 *D_80123EE0[];
#define EP_FRAME(a) (*(s16 *)((a) + 0x64))
#define EP_MODEL(a) (*(u8 **)(*(u8 **)((a) + 0xC0) + 0x40))
s32 func_80114ECC(u8 *a)
{
    switch (a[7]) {
    case 0:
        break;
    case 1:
        func_80114DE8(EP_MODEL(a), D_8011D128[EP_FRAME(a)]);
        if (++EP_FRAME(a) >= 8) {
            EP_FRAME(a) = 7;
            return 1;
        }
        break;
    case 2:
        func_80114DE8(EP_MODEL(a), D_8011DEBC[EP_FRAME(a)]);
        if (++EP_FRAME(a) >= 7) {
            EP_FRAME(a) = 0;
            a[7] = 0;
            return 1;
        }
        break;
    case 3:
        func_80114DE8(EP_MODEL(a), D_8011F9C0[EP_FRAME(a)]);
        if (++EP_FRAME(a) >= 6) {
            EP_FRAME(a) = 5;
            return 1;
        }
        break;
    case 4:
        func_80114DE8(EP_MODEL(a), D_8011F9C0[EP_FRAME(a)]);
        if (++EP_FRAME(a) >= 14) {
            EP_FRAME(a) = 13;
            return 1;
        }
        break;
    case 5:
        func_80114DE8(EP_MODEL(a), D_80123EE0[EP_FRAME(a)]);
        if (++EP_FRAME(a) >= 6) {
            EP_FRAME(a) = 5;
            return 1;
        }
        break;
    case 6:
    case 7:
    case 8:
        func_80114DE8(EP_MODEL(a), D_80122A04[EP_FRAME(a)]);
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
        func_80114DE8(EP_MODEL(a), D_80123DA0[EP_FRAME(a)]);
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
extern u8 D_80124264[];
extern void *D_801242EC[];
extern void *D_80124420[];
extern void *D_80124434[];
s32 func_80115194(u8 *a)
{
    s32 s;
    void *q;
    u8 *pl;
    u16 r;
    s = a[6];
    switch (s) {
    case 0:
        a[6] = 1;
        func_80040CDC(a, 0, D_80124264);
        a[0x70] = 1;
        break;
    case 1:
        func_80041098(a);
        if (a[0x70] != 0xFF) {
            return 0;
        }
        a[6]++;
        func_80040CDC(a, 0, D_801242EC[D_800BF870.unk0 - 10]);
        a[0x70] = 1;
        break;
    case 2:
        func_80041098(a);
        if (a[0x70] != 0xFF) {
            return 0;
        }
        a[6]++;
        if (!(D_800BF870.pad1[0x1A7] & 0x1F)) {
            func_80040CDC(a, 0, D_80124434[D_800BF870.unk0 - 10]);
        } else {
            func_80040CDC(a, 0, D_80124420[D_800BF870.unk0 - 10]);
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

extern void *D_801245BC[];
s32 func_801153D4(u8 *a)
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
        func_80040CDC(a, 0, D_801245BC[D_800BF870.unk0 - 10]);
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
extern s32 D_80124228[];
extern s32 D_8012423C[];
extern s32 D_80124250[];
extern u8 D_80123EB8[];
extern u8 D_80017FC0[];
extern u8 D_1F800236;
typedef struct { u8 pad[0x5E6]; u16 f5E6; } GameState5E6;
#define G ((u8 *)&D_800BF870)
void func_801154F8(u8 *a)
{
    s32 one = 1;
    u8 v;
    u8 *g;
    u8 *q;
    s32 k;

    switch (a[4]) {
    case 0:
        if (func_800519E0(a, 5, D_800ECF58[D_80124228[D_800BF870.unk0 - 10]], D_80123EB8) == 0) {
            W(a, 0x3C) = D_800ECF58[D_8012423C[D_800BF870.unk0 - 10]];
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
            func_8004D4C4(D_80124250[D_800BF870.unk0 - 10], 1);
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
            if (func_80115194(a) != 0) {
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
            if (func_801153D4(a) != 0) {
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

s32 func_801158B8(u8 *a, u8 *b)
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
void func_801159FC(void *arg0) {
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
        func_80114ECC(arg0);
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

#define P(p, o) (*(u8 **)((u8 *)(p) + (o)))
extern u8 D_1F800259;
extern u8 D_800BF84C;
void func_80115B28(u8 *a)
{
    u8 *b = D_1F80024C_2bfb;
    s32 r, done, x, z, k;
    u16 t;

    switch (a[6]) {
    case 0:
        func_800521F4(0, 0, 0x81, 2);
        func_80114ECC(a);
        if (func_801158B8(a, b) != 0) {
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
        r = func_80114ECC(a);
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
        if (func_80114ECC(a) != 0) {
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
        if (func_80114ECC(a) != 0) {
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

extern u8 D_800BF841;
extern s16 *D_800A54A8[];
extern s32 D_801245D0[];
extern s32 D_801245E8[];
extern s16 D_80124600[];
extern u8 D_801243F0[];
extern u8 D_80117FA4[];
void func_801154F8();
void func_80115EEC(u8 *a)
{
    u8 *e = D_800E7E80;
    u8 *p = D_1F80024C_2bfb;
    s16 *t;
    u8 *r;
    u16 v;
    u16 w;

    switch (a[6]) {
    case 0:
        if (func_80114ECC(a) != 0) {
            func_8004D298(D_800BF870.unk0 - 10);
            p[4] = 3;
            H(a, 0x40) = 0x1E;
            a[6]++;
        }
        break;
    case 1:
        if (--H(a, 0x40) == 0) {
            H(a, 0x40) = 0x3C;
            func_8003116C(D_801245D0[D_800BF870.unk0 - 10], a + 0x2C, -0x50);
            a[6]++;
            func_80074590(0x84, 0, 0);
        }
        break;
    case 2:
        if ((H(a, 0xB8) -= 0x80) < 0) {
            H(a, 0xB8) = 0;
        }
        H(a, 0xBA) = H(a, 0xBC) = H(a, 0xB8);
        if (--H(a, 0x40) == 0) {
            a[6]++;
            func_80040C00(D_80124600[D_800BF870.unk0 - 10]);
            switch (D_800BF870.unk0) {
            case 10:
                D_800BF870.pad1[0x188] = 6;
                break;
            case 13:
                D_800BF870.pad1[0x166] = 5;
                break;
            }
            D_1F800137 = 2;
        }
        break;
    case 3:
        if (func_80042728() != 0) {
            D_1F800246_6eef = 0;
            D_800BF841 = 0;
            t = D_800A54A8[D_800BF870.unk0];
            if (D_800BF870.unk0 == 0xE) {
                t += 8;
            }
            MEMBER_AT(s32, e, 0x2C) = t[0] << 16;
            if (MEMBER_AT(s16, e, 0x17E) < 0) {
                MEMBER_AT(s32, e, 0x30) = t[1] << 16;
                MEMBER_AT(s16, e, 0x32) += 0x46;
            } else {
                MEMBER_AT(s32, e, 0x30) = t[1] << 16;
            }
            MEMBER_AT(s32, e, 0x34) = t[2] << 16;
            v = t[3];
            e[4] = 4;
            e[5] = 0x21;
            e[6] = 0;
            e[7] = 0;
            e[0x2A] = v & 0x7F;
            e[0x147] = (v >> 8) & 1;
            func_80054D14(e, 0xC4, 0, t);
            func_80055D5C(e);
            func_80055284(e);
            H(a, 0x2E) = MEMBER_AT(u16, e, 0x2E);
            H(a, 0x32) = MEMBER_AT(u16, e, 0x32) - 0x3E8;
            w = MEMBER_AT(u16, e, 0x36);
            H(a, 0x4A) = 0x3000;
            H(a, 0xB8) = 0x800;
            H(a, 0xBC) = 0x800;
            H(a, 0xBA) = 0x800;
            a[6]++;
            H(a, 0x36) = w;
        }
        break;
    case 4:
        if ((H(a, 0x4A) -= 0x200) < 0) {
            H(a, 0x4A) = 0;
            if (D_800BF870.unk0 == 0xF) {
                D_1F800137 = 1;
                func_80040CDC(a, 0, D_801243F0);
                a[0x70] = 2;
                a[6] = 10;
            } else {
                H(a, 0x40) = 0x14;
                a[6]++;
            }
        }
        W(a, 0x30) += H(a, 0x4A) << 8;
        break;
    case 5:
        if (--H(a, 0x40) == 0) {
            func_8003116C(D_801245E8[D_800BF870.unk0 - 10], a + 0x2C, -0x1E);
            func_80074590(0x85, 0, 0);
            H(a, 0x40) = 5;
            a[6]++;
        }
        break;
    case 6:
        a[1] = 1;
        if (--H(a, 0x40) == 0) {
            a[6]++;
            if (D_800BF870.unk0 != 0xF) {
                r = func_80072DDC(0, 3, 5, 3);
                if (r != NULL) {
                    W(r, 0x1C) = (s32)func_801154F8;
                    H(r, 0x2E) = U(a, 0x2E);
                    H(r, 0x32) = U(a, 0x32);
                    H(r, 0x36) = U(a, 0x36);
                }
            } else {
                r = func_80072DDC(0, 3, 3, 0x24);
                if (r != NULL) {
                    W(r, 0x1C) = (s32)D_80117FA4;
                }
            }
        }
        break;
    case 7:
        a[1] = 1;
        a[4] = 3;
        break;
    case 8:
    case 9:
        break;
    case 10:
        func_80041098(a);
        if (a[0x70] == 0xFF) {
            H(a, 0x40) = 0x14;
            a[6] = 5;
        }
        break;
    }
}

s32 func_801163C4(u8 *a0)
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

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80116520);

extern u8 D_800E806E;
s32 func_801169E0(u8 *p)
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

extern s16 D_80124448[];
extern s16 D_800E8046;
s32 func_80116A70(u8 *p)
{
    s16 y;

    switch (p[0x78]) {
    case 0:
        p[0x78]++;
        *(s32 *)(p + 0x38) = func_8003116C(D_80124448[D_800BF870.unk0 - 10], p + 0x2C, -0x32);
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

s32 func_80116B1C(void *arg0) {
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x38), s8 *, 4) = 2;
    func_80074590(0x37, 0x16, 0);
    return 1;
}

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80116B50);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80116CB0);

extern s16 D_800E7FEE;

void f_UpdateEvilPigBattleProjectile(u8 *a)
{
    u8 *q = a + 0x60;
    s32 k;
    s32 k2;
    s16 ang;
    s32 m, n;
    u8 *r;
    u8 *p;
    Fix v[3];

    switch (a[4]) {
    case 0:
        func_80116B50(a);
        break;
    case 1:
        if (a[3] == 0) {
        if (D_800BF809 != 0 || D_800E7FEE == 0) {
            goto done;
        }
        switch (a[5]) {
        case 2:
            if (--H(a, 0x40) == 0) {
                a[0] = 1;
                a[5] = 0;
                if (a[0x46] != 0) {
                    if (a[0xBE] == 0) {
                        H(a, 0x44) += 0x80;
                    } else {
                        H(a, 0x44) -= 0x80;
                    }
                }
            }
        case 0:
            if (H(q, 0xE) < 0x15E) {
                H(q, 0xE) += 2;
            }
            if (H(a, 0x84) < 0x118) {
                H(a, 0x80) = H(a, 0x84) += 2;
            }
            if (H(a, 0x80) < 0xC8) {
                H(a, 0x80) += 1;
            }
            H(a, 0x82) = U(a, 0x80) << 1;
            H(a, 0x86) = U(a, 0x84) << 1;
            H(a, 0xB8) = H(a, 0xBA) = H(a, 0xBC) = H(q, 0xE) * 29;
            U(q, 6) = U(a, 0x2E);
            U(q, 8) = U(a, 0x32);
            U(q, 0xA) = U(a, 0x36);
            r = a + 0x60;
            if (a[0x5F] == 0) {
                ang = H(a, 0x60);
                m = func_80083F50(ang) * H(a, 0x44);
                n = -func_80083E80(ang) * H(a, 0x44);
                W(a, 0x2C) += m;
                W(a, 0x34) += n;
            }
            W(a, 0x30) += H(a, 0x50) << 12;
            p = r;
            if (a[0x5F] == 0) {
                s16 w;
                if (H(a, 0x44) >= 0) {
                    w = U(a, 0x80);
                } else {
                    w = -U(a, 0x80);
                }
                if (func_80045CAC(a, w, 0, H(p, 0)) != 0) {
                    a[0x5F] = a[0xBE] | 4;
                }
            }
            func_80116CB0(a);
            if (func_8004766C(a) < 0) {
                H(q, 4) = 0;
            }
            H(a, 0x56) = func_800776F8(H(q, 0), H(a, 0x56), 0x20);
            k = ((u16)func_80077FB0((H(q, 6) - H(a, 0x2E)) * (H(q, 6) - H(a, 0x2E)) +
                                    (H(q, 8) - H(a, 0x32)) * (H(q, 8) - H(a, 0x32)) +
                                    (H(q, 0xA) - H(a, 0x36)) * (H(q, 0xA) - H(a, 0x36))) << 10) / H(a, 0x84);
            if (a[0xBE] != 0) {
                H(a, 0x58) -= k;
            } else {
                H(a, 0x58) += k;
            }
            if (k != 0) {
                H(q, 0xC) += k;
                if (H(q, 0xC) > 0xC00) {
                    func_80074590(0x8E, 0, 0);
                    H(q, 0xC) = 0;
                }
            }
            if ((a[0x5F] & 4) || H(q, 4) == 0) {
                a[0] = 2;
                a[4] = 2;
                a[6] = 0;
            } else {
                H(q, 4)--;
            }
            break;
        case 1:
            H(a, 0x40) = 0x14;
            a[5]++;
            if (a[0x2B] != 0) {
                H(a, 0x44) = 0;
            }
            a[0x46] = a[0x2B];
            goto done;
        }
    done:
        a[0x29] = 0;
        a[0x5F] = 0;
        a[1] = 1;
        func_80077E7C(a);
        func_800518FC(a);
            break;
        }
            a[1] = 1;
            func_80077E7C(a);
            func_800518FC(a);
            k2 = ((u16)func_80077FB0((H(q, 6) - H(a, 0x2E)) * (H(q, 6) - H(a, 0x2E)) +
                                    (H(q, 8) - H(a, 0x32)) * (H(q, 8) - H(a, 0x32)) +
                                    (H(q, 0xA) - H(a, 0x36)) * (H(q, 0xA) - H(a, 0x36))) << 10) / H(a, 0x84);
            H(a, 0x58) -= k2;
            if (k2 != 0) {
                H(q, 0xC) += k2;
                H(q, 0x10) += k2;
                if (H(q, 0xC) > 0xC00) {
                    func_80074590(0x8E, 0, 0);
                    H(q, 0xC) = 0;
                }
                if (H(q, 0x10) > 0x400) {
                    H(q, 0x10) = 0;
                    v[0].hi = U(a, 0x2E);
                    v[1].hi = U(a, 0x32) + U(a, 0x84);
                    v[2].hi = U(a, 0x36);
                    func_8003116C(0xC00, v, -0x50);
                }
                H(a, 0x56) = func_800782B0(a + 0x2C, H(q, 6), H(q, 0xA));
            }
            U(q, 6) = U(a, 0x2E);
            U(q, 8) = U(a, 0x32);
            U(q, 0xA) = U(a, 0x36);
        break;
    case 2:
        switch (a[6]) {
        case 0:
            func_8003116C(0xC01, a + 0x2C, -0x50);
            func_8003116C(0xC06, a + 0x2C, -0x50);
            func_80074590(0x8D, 0, 0);
            a[6]++;
            break;
        case 1:
        case 2:
            a[6]++;
            break;
        case 3:
            a[4] = 3;
            break;
        }
        a[1] = 1;
        func_80077E7C(a);
        func_800518FC(a);
        break;
    case 3:
        if (a[3] == 0) {
            D_1F80025A--;
        }
        func_8007A624(a);
        break;
    }
}

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_801175B8);

extern s32 D_8012460C[];
void func_80117720(u8 *a)
{
    func_80051B04(*(void **)(a + 0xC0), 0xC, D_8012460C[a[0x5E] - 1]);
    func_80074590(0x8D, 0, 0);
}

u8 func_80117774(u8 *a)
{
    s16 *p = (s16 *)(a + 0x60);
    s16 v;
    if (a[0x5F] == 0) {
        if (*(s16 *)(a + 0x44) >= 0) {
            v = *(s16 *)(a + 0x80);
        } else {
            v = -*(s16 *)(a + 0x80);
        }
        if (func_80045CAC(a, v, 0, *p) != 0) {
            a[0x5F] = a[0xBE] | 4;
        }
    }
    return a[0x5F];
}

void func_80117800(void *arg0) {
    s16 temp_s0;
    s32 temp_lo;
    s32 temp_s2;

    if (M2C_FIELD(arg0, u8 *, 0x5F) == 0) {
        temp_s0 = M2C_FIELD(arg0, s16 *, 0x60);
        temp_s2 = func_80083F50(temp_s0) * M2C_FIELD(arg0, s16 *, 0x44);
        temp_lo = -func_80083E80(temp_s0) * M2C_FIELD(arg0, s16 *, 0x44);
        M2C_FIELD(arg0, s32 *, 0x2C) = (s32) (M2C_FIELD(arg0, s32 *, 0x2C) + temp_s2);
        M2C_FIELD(arg0, s32 *, 0x34) = (s32) (M2C_FIELD(arg0, s32 *, 0x34) + temp_lo);
    }
    M2C_FIELD(arg0, s32 *, 0x30) = (s32) (M2C_FIELD(arg0, s32 *, 0x30) + (M2C_FIELD(arg0, s16 *, 0x50) << 0xC));
}

extern Range D_80124C94[];
extern Range D_80124CAC[];
extern Range D_80124CD0[];
extern Range D_80124D08[];
extern u8 *D_1F80021C;
void func_801178A0(s16 kind, s16 idx)
{
    Range *t;
    s32 n, base;
    u8 *p;
    switch (kind) {
    case 0:
        t = D_80124C94;
        n = 3;
        base = 0;
        break;
    case 1:
        t = D_80124CAC;
        n = 0x1B;
        base = 0x300;
        break;
    case 2:
        t = D_80124CD0;
        n = 0x1F;
        base = 0x1C8;
        break;
    case 3:
        t = D_80124D08;
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
extern M2C_UNK D_801246AC;
void func_80117988(void) {
    func_80075448(0xA, &D_801246AC, 0x10, D_800BED82);
}

extern s16 D_1F8001A6;
/* func_801180E8, inlined */
static inline u8 inl_801180E8(u8 *a)
{
    s16 ang;
    if (a[0x29] == 0) {
        if (a[0xBE] == 0) {
            ang = *(u16 *)(a + 0x60);
        } else {
            ang = *(u16 *)(a + 0x60) + 0x800;
        }
        a[0x29] = func_800455C0(a, 0, 0, ang);
        if (a[0x29] != 0) {
            if (D_1F8001A6 & 0x8000) {
                *(s16 *)(a + 0x40) = 0;
            }
            a[0x29] &= 1;
            if (a[0x29] != 0) {
                func_80049674(a);
                *(u16 *)(a + 0x60) = D_1F8001A0;
            }
        }
    }
    return a[0x29];
}
/* func_801181AC, inlined */
static inline s32 inl_801181AC(u8 *a)
{
    s16 h = -0x1E;
    s16 ang;
    s16 d = 0x3C;
    if (a[0xBE] == 0) {
        ang = *(u16 *)(a + 0x60);
    } else {
        ang = *(u16 *)(a + 0x60) + 0x800;
    }
    if (func_80045CAC(a, d, h, ang) == 0 && func_80045CAC(a, d, (s16)(0x64 - h), ang) == 0) {
        return 0;
    }
    a[0x5F] = 1;
    return 1;
}
void func_801179BC(u8 *a)
{
    s16 v;
    s32 w;
    s16 t;
    u8 *o;
    u16 b;

    switch (a[4]) {
    case 0:
        a[0xB] = 0xFF;
        *(u16 *)(a + 0xB8) = 0x200;
        *(s16 *)(a + 0x80) = 0xF;
        *(s16 *)(a + 0x82) = 0x1E;
        a[0x29] = 0;
        a[0x5F] = 0;
        a[0x5E] = 0;
        a[0] = 1;
        *(s16 *)(a + 0x64) = 0;
        *(s16 *)(a + 0x66) = 0;
        *(s16 *)(a + 0x40) = 0x140;
        v = (u32)(*(u16 *)(a + 0xB8) * 5) >> 5;
        *(s16 *)(a + 0x86) = v;
        *(s16 *)(a + 0x84) = v;
        func_80041AC0(a);
        *(u16 *)(a + 0x4A) = 0;
        o = func_800310F4(0xC02, 0);
        if (o != NULL) {
            *(u8 **)(o + 0x10) = a;
            *(u8 **)(a + 0x10) = o;
            a[4] = 1;
        } else {
            *(u8 **)(a + 0x10) = NULL;
            a[4] = 3;
        }
        break;
    case 1:
        if (D_1F800259 != 0) {
            a[0] = 2;
            a[4] = 2;
        } else if (D_800BF809 == 0) {
            switch (a[5]) {
            case 0:
                w = *(s16 *)(a + 0x44);
                if (w < 0) {
                    w = -w;
                }
                w += 0x80;
                if ((s16)w >= 0x301) {
                    t = 0x300;
                } else {
                    t = w;
                }
                if (a[0xBE] == 0) {
                    *(s16 *)(a + 0x44) = t;
                } else {
                    *(s16 *)(a + 0x44) = -t;
                }
                *(u16 *)(a + 0x4A) += 0x300;
                if (*(s16 *)(a + 0x4A) >= 0x2001) {
                    *(u16 *)(a + 0x4A) = 0x2000;
                }
                *(s32 *)(a + 0x30) += *(s16 *)(a + 0x4A) << 8;
                inl_801181AC(a);
                if ((a[0x5F] | a[0x5E]) == 0) {
                    func_80041A1C(a, 1);
                }
                if (func_80041AC0(a) < 0) {
                    *(s16 *)(a + 0x40) = 0;
                }
                if (inl_801180E8(a) != 0) {
                    *(u16 *)(a + 0x4A) = 0;
                    a[5]++;
                }
                break;
            case 1:
                w = *(s16 *)(a + 0x44);
                if (w < 0) {
                    w = -w;
                }
                w += 0x200;
                if ((s16)w >= 0x1C01) {
                    t = 0x1C00;
                } else {
                    t = w;
                }
                if (a[0xBE] == 0) {
                    *(s16 *)(a + 0x44) = t;
                } else {
                    *(s16 *)(a + 0x44) = -t;
                }
                inl_801181AC(a);
                if ((a[0x5F] | a[0x5E]) == 0) {
                    func_80041A1C(a, 0);
                }
                if (func_80041AC0(a) < 0) {
                    *(s16 *)(a + 0x40) = 0;
                }
                *(u16 *)(a + 0x32) += 0xA;
                if (inl_801180E8(a) == 0) {
                    *(u16 *)(a + 0x32) += 0x14;
                }
                break;
            }
            if (*(s16 *)(a + 0x40) == 0) {
                a[0] = 2;
                a[4] = 2;
            } else {
                if (!(--*(s16 *)(a + 0x40) & 0x1F)) {
                    func_80074590(0x8C, 0, 0);
                }
                *(u16 *)(a + 0xB8) += 0x20;
                if (*(u16 *)(a + 0xB8) >= 0x1401) {
                    *(u16 *)(a + 0xB8) = 0x1400;
                }
            }
            b = *(u16 *)(a + 0xB8);
            do {
                w = (b * 0xF) >> 9;
                *(s16 *)(a + 0x80) = w;
                *(s16 *)(a + 0x82) = w * 2;
            } while (0);
            w = (u32)(b * 5) >> 5;
            *(s16 *)(a + 0x86) = w;
            *(s16 *)(a + 0x84) = w;
        }
        a[0x29] = 0;
        a[0x5F] = 0;
        a[1] = 1;
        func_80077E7C(a);
        break;
    case 2:
        o = *(u8 **)(a + 0x10);
        if (o != NULL) {
            o[4] = 2;
            *(u8 **)(a + 0x10) = NULL;
            break;
        }
    case 3:
        D_1F80025A--;
        func_8007A624(a);
        break;
    }
}

extern SVec D_1F8000C8;
void func_801179BC(u8 *a);
u8 *f_SpawnLastEvilPigBattleProjectile(u8 *a)
{
    u8 *p = func_8007A980(1, 2, 0);
    SVec *v;
    SVec *w;

    if (p == NULL) {
        return NULL;
    }
    v = &D_1F8000C0;
    *(void **)(p + 0x1C) = func_801179BC;
    p[2] = 0x55;
    w = &D_1F8000C8;
    p[3] = 0;
    D_1F8000C0.x = 0x12C;
    v->y = 0;
    v->z = 0;
    func_800844C0(*(u8 **)(a + 0xC4) + 0x18, v, w);
    *(u16 *)(p + 0x2E) = *(u16 *)(*(u8 **)(a + 0xC4) + 0x2C) + D_1F8000C8.x;
    *(u16 *)(p + 0x32) = *(u16 *)(*(u8 **)(a + 0xC4) + 0x30) + w->y;
    *(u16 *)(p + 0x36) = *(u16 *)(*(u8 **)(a + 0xC4) + 0x34) + w->z;
    p[0x2A] = a[0x2A];
    p[0xBE] = a[0xBE];
    D_1F80025A++;
    return p;
}

#define gte_ldv0m(p) __asm__ volatile("lwc2	$0, %0;" "lwc2	$1, %1" : : "m"(((s32 *)(p))[0]), "m"(((s32 *)(p))[1]))
extern s32 D_1F800090;
u8 func_801180E8(u8 *a)
{
    s16 ang;
    if (a[0x29] == 0) {
        if (a[0xBE] == 0) {
            ang = *(u16 *)(a + 0x60);
        } else {
            ang = *(u16 *)(a + 0x60) + 0x800;
        }
        a[0x29] = func_800455C0(a, 0, 0, ang);
        if (a[0x29] != 0) {
            if (D_1F8001A6 & 0x8000) {
                *(s16 *)(a + 0x40) = 0;
            }
            a[0x29] &= 1;
            if (a[0x29] != 0) {
                func_80049674(a);
                *(u16 *)(a + 0x60) = D_1F8001A0;
            }
        }
    }
    return a[0x29];
}

s32 func_801181AC(u8 *a)
{
    s16 h = -0x1E;
    s16 ang;
    s16 d = 0x3C;
    if (a[0xBE] == 0) {
        ang = *(u16 *)(a + 0x60);
    } else {
        ang = *(u16 *)(a + 0x60) + 0x800;
    }
    if (func_80045CAC(a, d, h, ang) == 0 && func_80045CAC(a, d, (s16)(0x64 - h), ang) == 0) {
        return 0;
    }
    a[0x5F] = 1;
    return 1;
}

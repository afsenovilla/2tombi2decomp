#include "common.h"
#include "game.h"
#include "m2c.h"
#include "gte.h"

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

extern s32 D_1F80009C;
#define U(p, o) (*(u16 *)((u8 *)(p) + (o)))
typedef struct { u8 pad[0x2E]; u16 x; u8 pad2[6]; u16 z; } ArenaXZ;
void func_8010940C(u8 *a, u8 *b)
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

extern s32 D_1F800098;
s32 func_801097BC(u8 *a, u8 *b, u8 *c) {
    s16 dx, dz, dy, e, f;
    u16 h, bh, ah;
    u16 r;
    s32 ang, s, t, k, y;

    dx = FU16(a, 0x2E) - FU16(c, 0x2C);
    dz = FU16(a, 0x36) - FU16(c, 0x34);
    r = func_80084080(dx * dx + dz * dz);
    if (r > F16(a, 0x80) + F16(b, 0x80)) {
        return -1;
    }
    dy = FU16(a, 0x32) - FU16(c, 0x30);
    bh = FU16(b, 0x84); ah = FU16(a, 0x84); h = bh + ah;
    if ((u16)(dy + h) > F16(a, 0x86) + F16(b, 0x86)) {
    fail:
        return -1;
    }
    if (dy < 0) {
        dy = -dy;
        e = h;
        f = -h;
    } else {
        f = e = (FU16(b, 0x86) - bh) + (FU16(a, 0x86) - ah);
    }
    ang = func_80085690(-dz, dx);
    s = F16(a, 0x80) + F16(b, 0x80) - (s16)r;
    k = e - dy;
    D_1F80009C = ang;
    if (s < k) {
        if (!(a[0] & 4)) {
                        e = (func_80083F50(ang) * (F16(a, 0x80) + F16(b, 0x80))) >> 12;
                        t = func_80083E80(D_1F80009C) * (F16(a, 0x80) + F16(b, 0x80));
                        F16(a, 0x2E) = FU16(c, 0x2C) + e;
            F16(a, 0x36) = FU16(c, 0x34) - (t >> 12);
        }
        a[0x5F] = func_80077768((s16)D_1F80009C, F16(a, 0x140), 1) + 2;
        if (k >= 0x92) {
            a[0x60] = 1;
        }
        return 1;
    }
    if (f <= 0) {
        if (a[0x145] & 1) {
            goto fail;
        }
        b[0x29] = 1;
        M2C_FIELD(a, s32 *, 0x30) = (F16(c, 0x30) + f) << 16;
        func_80022C78(a);
        return 2;
    }
    if (D_1F800098 == 0) {
        y = F16(c, 0x30) + f;
        D_1F800253 = 4;
        M2C_FIELD(a, s32 *, 0x30) = y << 16;
        if (a[0x145] == 1 && F16(a, 0x4A) < 0) {
            F16(a, 0x4A) = 0;
        }
    }
    return 3;
}

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_80109AA0);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_80109E04);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_8010A138);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_8010A55C);

extern s32 D_1F800088;
extern u8 *D_1F800084_66c9;
extern u8 D_1F800182_5650;
s32 func_8010A870(u8 *a, u8 *b, u8 *c)
{
    s16 dx = *(u16 *)(a + 0x14C) - *(u16 *)(c + 0x2C);
    s16 dz = *(u16 *)(a + 0x150) - *(u16 *)(c + 0x34);
    u16 d = func_80084080(dx * dx + dz * dz);
    u16 cy;
    s16 t;
    u16 h;

    if (*(s16 *)(b + 0x80) + D_1F800088 < d) {
        return 0;
    }
    {
        s32 k = *(u16 *)(a + 0x14E);
        cy = *(u16 *)(c + 0x30);
        k = k - cy + 0x64;
        h = *(volatile u16 *)(a + 0x68);
        k = (u16)(h + k);
        if ((s16)h + 0xC8 < k) {
            return 0;
        }
    }
    t = *(u16 *)(a + 0x32) - cy;
    if ((u16)(t + 0x3C) >= 0x51) {
        if (t < 0) {
            *(s16 *)(a + 0x156) = -0x3C;
        } else {
            *(s16 *)(a + 0x156) = 0x14;
        }
    } else {
        *(s16 *)(a + 0x156) = t;
    }
    D_1F800084_66c9 = c;
    {
        u16 w = *(u16 *)(b + 0x80);
        D_1F800182_5650 = 0;
        *(s16 *)(a + 0x152) = w + 0x1E;
    }
    return 1;
}

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_8010A9A4);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_8010AB14);

extern u8 **D_1F80013C;
extern u8 D_1F800144;
extern s16 D_1F800150_058c;
extern u8 D_1F800150;
extern u8 D_1F800183;
extern u8 **D_1F800148;
/* func_8010BD2C, inlined */
static inline void inl_8010BD2C(u8 *a, u8 *b, u8 *c)
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
void func_8010AD5C(void)
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
                    if (e[2] == 0x58) {
                        switch (o[2]) {
                        case 0x11:
                        case 0x47:
                        case 0x1:
                            inl_8010BD2C(e, o, *(u8 **)(o + 0xC0));
                            break;
                        case 0x8:
                            func_8010AB14(e, o, *(u8 **)(o + 0xC0));
                            break;
                        }
                    } else {
                        switch (o[2]) {
                        case 0x18:
                            if (e[0] == 4 && func_800240FC(e, o) != 0) {
                                e[0x5E] = 1;
                                e[0] = 0xA;
                            }
                            break;
                        case 0x64:
                            if (e[2] == 0x67) {
                                func_801092D4(e, o);
                            }
                            break;
                        }
                    }
                }
            }
        }
    }
}

void func_8010AFF8(u8 *a)
{
    u8 **l = D_1F80013C;
    u8 *e;
    s32 r;

    D_1F800182_5650 = D_1F800144;
    while (D_1F800182_5650 != 0) {
        e = *l;
        D_1F800182_5650--;
        l++;
        if (e[0] & 1) {
            switch (e[2]) {
            case 0x40:
                r = func_8001F40C(a, e, 1);
                if (r >= 0) {
                    func_8001FF7C(a, e, r, 1);
                }
                break;
            case 0x58:
                if (func_80022F04(a, e) != 0) {
                    a[0x2B] = D_1F80009C >> 4;
                    func_80022D08(a, e, 1, 0);
                }
                break;
            case 0x67:
                func_8010940C(a, e);
                break;
            case 0xD1:
                if (func_80022F04(a, e) != 0) {
                    e[0x2B] = 1;
                }
                break;
            }
        }
    }
}

extern u8 *D_800F2738;
void func_8010B174(void)
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
        D_1F800182_5650 = D_1F800144;
        while (D_1F800182_5650 != 0) {
            e = *l;
            D_1F800182_5650--;
            l++;
            if (e[0] & 1) {
                switch (e[2]) {
                case 0x40:
                    if (func_80022F04(p, e) != 0) {
                        r = func_8001DC9C(p, e, 0, 0);
                        if (!(r & 0x80)) {
                            D_1F800182_5650 = 0;
                        }
                    }
                    break;
                case 0x58:
                    if (func_8002192C(p, e, 1) != 0) {
                        e[0x5E] = 1;
                    }
                    break;
                case 0x67:
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
                            D_1F800182_5650 = 0;
                        }
                    }
                    break;
                }
            }
        }
    }
}

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_8010B36C);

extern u8 D_1F800137_104c;
extern s8 D_800BF808[];
extern u8 D_800E7E80[];
static inline void inl_list_8010B558(u8 *a)
{
    u8 **p;
    u8 *b;
    p = D_1F800148;
    D_1F800182_5650 = D_1F800150;
    while (D_1F800182_5650 != 0) {
        b = *p;
        D_1F800182_5650--;
        p++;
        if (b[0] & 1) {
            switch (b[2]) {
            case 0x12:
                func_8002311C(a, b);
                break;
            case 0x11:
                func_80109AA0(a, b, *(s32 *)(b + 0xC0));
                break;
            case 0x8:
                func_80109E04(a, b, *(s32 *)(b + 0xC0));
                break;
            case 0x1:
                func_8001F650(a, b, *(s32 *)(b + 0xC0));
                break;
            case 0x47:
                func_801097BC(a, b, *(s32 *)(b + 0xC0));
                break;
            }
        }
    }
}
/* func_8010BA30, inlined */
static inline void inl_8010BA30(u8 *a)
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
void func_8010B558(void)
{
    u8 *g = D_800E7E80;

    func_8002288C(g);
    switch (g[0]) {
    case 0:
    case 6:
        break;
    case 2:
        if (*(u32 *)(g + 0x158) < 2) {
            inl_list_8010B558(g);
        }
        break;
    case 1:
    case 3:
    case 4:
    case 5:
    case 7:
    default:
        func_80022760(g);
        func_8010AFF8(g);
        if (*(u32 *)(g + 0x158) < 2) {
            inl_list_8010B558(g);
        }
        break;
    }
    func_8010B174();
    func_8010B36C();
    func_8010AD5C();
    inl_8010BA30(g);
}

extern u8 **D_1F80014C;
extern u8 D_1F800152;
extern void *D_1F800080;
void *func_8010B888(u8 *a)
{
    u8 **l = D_1F80014C;
    u8 *p;

    D_1F800182_5650 = D_1F800152;
    while (D_1F800182_5650 != 0) {
        p = *l;
        D_1F800182_5650--;
        l++;
        if (p[0] & 1) {
            switch (p[2]) {
            case 0x11:
                if (func_80024BD8(a, p, *(void **)(p + 0xC0)) != 0) {
                    p[0x29] = 1;
                    a[0x164] = 3;
                    D_1F800080 = p;
                    D_1F800182_5650 = 0;
                }
                break;
            case 8:
                func_8010A55C(a, p, *(void **)(p + 0xC0));
                break;
            case 1:
                if (func_80024BD8(a, p, *(void **)(p + 0xC0)) != 0) {
                    u16 x = *(u16 *)(p + 0x80);
                    u16 y;
                    p[0x29] = 1;
                    y = *(u16 *)(a + 0x80);
                    a[0x164] = 1;
                    a[0x15C] = 0;
                    D_1F800080 = p;
                    D_1F800182_5650 = 0;
                    *(s16 *)(a + 0x152) = x + y - 0xC;
                }
                break;
            case 0x47:
                if (func_8010A870(a, p, *(void **)(p + 0xC0)) != 0) {
                    D_1F800080 = p;
                    a[0x15C] = 0;
                    a[0x164] = 1;
                    p[0x29] = 1;
                }
                break;
            }
        }
    }
    return D_1F800080;
}

extern u16 D_1F800164_7d8c;
extern u16 D_1F800160_3621;
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

void func_8010BE10(u8 *a)
{
    u8 **l = D_1F800148;
    u8 *e;

    D_1F800182_5650 = D_1F800150;
    while (D_1F800182_5650 != 0) {
        e = *l;
        D_1F800182_5650--;
        l++;
        if (e[0] & 1) {
            switch (e[2]) {
            case 0x12:
                func_8002311C(a, e);
                break;
            case 0x11:
                func_80109AA0(a, e, *(void **)(e + 0xC0));
                break;
            case 8:
                func_80109E04(a, e, *(void **)(e + 0xC0));
                break;
            case 1:
                func_8001F650(a, e, *(void **)(e + 0xC0));
                break;
            case 0x47:
                func_801097BC(a, e, *(void **)(e + 0xC0));
                break;
            }
        }
    }
}

void func_8010BF40(u8 *a, u8 *b)
{
    u8 *p = *(u8 **)(a + 0x10);
    s32 t, u, s;
    s16 r;
    s16 x;
    s16 z;

    t = (func_80083F50(H(p, 0xC)) * H(a, 0x156)) >> 12;
    u = func_80083E80(H(p, 0xC)) * H(a, 0x152);
    H(a, 0x32) = t + (H(p, 0x30) + (-u >> 12));
    r = (func_80083F50(H(p, 0xC) + 0x400) * H(a, 0x156)) >> 12;
    s = (func_80083F50(H(p, 0xA)) * r) >> 12;
    u = func_80083E80(H(p, 0xA)) * r;
    x = H(p, 0x2C) - (u >> 12);
    z = H(p, 0x34) + s;
    r = (func_80083F50(H(p, 0xC)) * H(a, 0x152)) >> 12;
    u = func_80083E80(H(b, 0x56)) * r;
    H(a, 0x2E) = x;
    H(a, 0x36) = z + (u >> 12);
    r = (func_80083E80(H(a, 0x58)) * H(a, 0x64)) >> 12;
    z = (func_80083E80(H(a, 0x56)) * r) >> 12;
    u = func_80083F50(H(a, 0x56)) * r;
    H(a, 0x36) += z;
    H(a, 0x2E) -= u >> 12;
    H(a, 0x32) += (func_80083F50(H(a, 0x58)) * H(a, 0x64)) >> 12;
}

extern u16 D_800ECF54;
extern s16 D_1F80016C;
extern s16 D_1F80016E;
extern u8 D_800BF840;
void func_8010C114(u8 *a)
{
    if (++*(s16 *)(a + 0x42) >= 6) {
        if ((D_800ECF54 & D_1F80016C) && a[0x147] == 0) {
            a[7] = 0;
            *(s16 *)(a + 0x154) = 0;
            *(s16 *)(a + 0x42) = 0;
            a[0] |= 4;
            func_80054D14(a, 0x38, 0);
            return;
        } else if ((D_800ECF54 & D_1F80016E) && a[0x147] == 1) {
            a[7] = 0;
            *(s16 *)(a + 0x154) = 0;
            *(s16 *)(a + 0x42) = 0;
            a[0] |= 4;
            func_80054D14(a, 0x38, 0);
            return;
        }
    }
    if ((D_800ECF54 & D_1F80016C) && a[0x147] == 1) {
        a[7] = 6;
        func_80054D14(a, 0xAA, 0);
    } else if ((D_800ECF54 & D_1F80016E) && a[0x147] == 0) {
        a[7] = 6;
        func_80054D14(a, 0xAA, 0);
    } else if (*(s16 *)(a + 0x42) >= 0x97) {
        D_800BF840 = 0x48;
    }
}

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_8010C268);

void func_8010C628(u8 *a, u8 *b) {
    if (++H(a, 0x42) >= 6) {
        if ((D_800ECF54 & D_1F80016C) && a[0x147] == 0) {
            a[7] = 0;
            H(a, 0x154) = 0;
            H(a, 0x42) = 0;
            a[0] |= 4;
            func_80054D14(a, 0x37, 0);
            return;
        } else if ((D_800ECF54 & D_1F80016E) && a[0x147] == 1) {
            a[7] = 0;
            H(a, 0x154) = 0;
            H(a, 0x42) = 0;
            a[0] |= 4;
            func_80054D14(a, 0x37, 0);
            return;
        }
    }
    if ((D_800ECF54 & D_1F80016C) && a[0x147] == 1) {
        a[7] = 6;
        func_80054D14(a, 0xA8, 0);
    } else if ((D_800ECF54 & D_1F80016E) && a[0x147] == 0) {
        a[7] = 6;
        func_80054D14(a, 0xA8, 0);
    } else if (D_800ECF54 & 0x10) {
        a[7] = 5;
        func_80054D14(a, 0x34, 0);
        func_80062A30(a, b, 0);
    } else if (D_800ECF54 & 0x40) {
        a[7] = 5;
        func_80054D14(a, 0x3D, 0);
        func_80062A30(a, b, 1);
    }
}

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

extern u16 D_1F800172;
s32 func_8010CCCC(u8 *a, u8 *b)
{
    u8 *o = *(u8 **)(a + 0x10);
    s32 d;
    b[0x29] = 1;
    *(s16 *)(b + 0x60) = -*(u16 *)(a + 0x152);
    func_800635D4(a, 1);
    func_80076D68(a);
    if (a[0x169] == 0 && (D_800ECF54 & (D_1F800172 | 0x50))) {
        *(s16 *)(a + 0x58) = 0;
        func_8010BF40(a, b);
        return D_800ECF54;
    }
    func_8010BF40(a, b);
    d = *(s16 *)(o + 0xC);
    if (d < 0) {
        d = -d;
    }
    if (d > 0x200) {
        *(s16 *)(a + 0x58) = 0;
        return 0x40;
    }
    return 0;
}

s32 func_8010CDA4(u8 *a)
{
    u8 *b = *(u8 **)(a + 0x158);
    u8 *o;
    s32 d;
    if (b[2] == 8) {
    o = *(u8 **)(a + 0x10);
    b[0x29] = 1;
    *(s16 *)(b + 0x60) = -*(u16 *)(a + 0x152);
    func_800635D4(a, 1);
    func_80076D68(a);
    if (a[0x169] == 0 && (D_800ECF54 & (D_1F800172 | 0x50))) {
        *(s16 *)(a + 0x58) = 0;
        func_8010BF40(a, b);
        return D_800ECF54;
    }
    func_8010BF40(a, b);
    d = *(s16 *)(o + 0xC);
    if (d < 0) {
        d = -d;
    }
    if (d > 0x200) {
        *(s16 *)(a + 0x58) = 0;
        return 0x40;
    }
    }
    return 0;
}

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

extern u8 D_1F8000D0_b839[];

void func_8010D108(u8 *a, u8 *b)
{
    s16 ang;
    s32 x, z;
    s16 dx, dz, r, dist;
    s32 k;
    u16 t;
    s16 d16;

    {
        u8 *p = D_800E7E80;
        ang = U(p, 0x56);
        if (H(p, 0x2E) < H(b, 0x2E)) {
            ang -= 0x100;
        } else {
            ang += 0x100;
        }
    }
    {
        u8 *c = D_1F8000D0_b839;
        t = U(b, 0x7C);
        d16 = U(c, 6) + 0xC8 - t;
        if ((u16)(d16 + 10) >= 0x15) {
            W(c, 4) -= d16 << 13;
        } else {
            U(c, 6) = t - 0xC8;
            a[0x66] |= 2;
        }
    }
    k = 0x578;
    x = U(b, 0x2E) + ((func_80083F50(ang) * k) >> 12);
    {
        u8 *c = D_1F8000D0_b839;
        z = U(b, 0x36) - ((func_80083E80(ang) * k) >> 12) - U(c, 0xA);
        dz = z;
        dx = x - U(c, 2);
        r = func_80085690(-dz, dx);
        dist = func_80084080(dx * dx + dz * dz);
        W(c, 0) += func_80083F50(r) * dist;
        W(c, 8) -= func_80083E80(r) * dist;
    }
    if (dist < 0x191) {
        a[0x66] |= 1;
    }
}

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

typedef struct { u16 x, y, z; u8 k; u8 pad; } ArenaPt;
extern u8 D_800BF809;
extern u8 D_800E7FC5;
extern ArenaPt D_8011BBFC[];
extern s16 D_1F800160_71b4;
extern s16 D_1F800164_d75f;
extern s16 D_1F800162_b816_b4b8;
extern s16 D_1F8001A4;
extern u8 D_1F80025B;
void func_8010E4C8(u8 *a)
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
        if (f_TestTombaOverlapsEvilPig(a) != 0) {
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
        k = func_8010DE1C(a, H(a, 0x64));
        switch (D_800BF870.unk0) {
        case 10:
        case 11:
        case 13:
            t = D_8011BBFC; e = &t[k];
            H(a, 0x2E) = e->x;
            H(a, 0x32) = e->y;
            H(a, 0x36) = e->z;
            a[0x2A] = e->k;
            if (D_800E7FC5 == 0 && H(a, 0x32) > D_1F800162_b816_b4b8) {
                U(a, 0x32) = *(u16 *)&D_1F800162_b816_b4b8;
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
            t2 = D_8011BBFC; e2 = &t2[k];
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
            t3 = D_8011BBFC; e3 = &t3[k];
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

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_8010EB5C);

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

extern u8 D_800BF80E;
extern u8 D_800BF80F;
extern u8 D_800E8008[];
extern u8 D_80118C78[];
extern s16 D_8011AC28[];
extern s32 D_8011BF84[];
void func_8010DA50();
void func_8011041C(u8 *a)
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
            *(void **)(e + 0x1C) = func_8010DA50;
        }
        *(u8 **)(a + 0x14) = e;
        a[6]++;
        break;
    case 1:
        if (D_800BF80F == 0) {
            a[6]++;
            pl[6] = 0;
            func_8004D604(D_8011BF84[D_800BF870.unk0 - 10], 1);
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
            func_8006CBD0(D_800E8008, D_80118C78);
            t = &D_8011AC28[H(a, 0x6A) * 3];
            U(a, 0x2E) = t[0];
            U(a, 0x32) = t[1];
            U(a, 0x36) = t[2];
            H(a, 0x6A)++;
            func_8006E1C0(7);
        }
        break;
    }
}

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

typedef struct { u8 *v[6]; } PtrTab6;
typedef struct { u8 b[8][4]; } ByteTab8;
extern PtrTab6 D_801091E8;
extern ByteTab8 D_80109200;
extern u8 D_8011DB54[];
void func_801128E8(u8 *a)
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
    p = D_801091E8;
    t = D_80109200;
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
        func_80027768(D_8011DB54, e[3], 0, 0);
    }
}

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

extern u16 D_1F80017C;
extern u8 D_8011DC64[];
typedef struct { u8 pad[0x48]; s16 r[3]; } RotAct;
void func_80112D50(u8 *a)
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
            *(u8 **)(a + 0x34) = D_8011DC64;
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
u32 *func_80113788(u32 *f, u32 *ot, s32 n)
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
u32 *func_80113A54(u32 *f, u32 *ot, s32 n)
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
u32 *func_80113EB4(u32 *f, u32 *ot, s32 n)
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
u32 *func_80114158(u32 *f, u32 *ot, s32 n)
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

void func_8011448C(u32 *p, void *b)
{
    u32 lo = *p;
    u32 packed;

    packed = lo;
    lo = packed & 0xFFFF;
    p += 4;
    func_80114158(func_80113EB4(p, b, lo), b, packed >> 16);
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
void func_801144D4(u8 *a)
{
    T2Pt32 v0, v1, v2;
    T2CamD0 *c = &D_1F8000D0_3bb0;
    s32 ang, r, dx, dz;
    u16 t;

    D_800A3F90 = 0x5000;
    t = c->ry;
    D_800A3F94 = 455;
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
    func_8011478C(a, &v0, &v1, &v2);
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
void func_8011478C(u8 *g, T2Pt32 *p0, T2Pt32 *p1, T2Pt32 *p2)
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

extern s16 D_80125A3C[];
void func_80115300(u16 *a, s16 *v)
{
    s32 i;
    s32 n = a[0];
    s16 *t;
    s16 *s;
    s16 *d = (s16 *)a;
    if (n == 0) return;
    t = D_80125A3C;
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

extern u8 *D_8011EC6C[];
extern u8 *D_8011FA00[];
extern u8 *D_80121504[];
extern u8 *D_80124548[];
extern u8 *D_801258E4[];
extern u8 *D_80125A24[];
#define EP_FRAME(a) (*(s16 *)((a) + 0x64))
#define EP_MODEL(a) (*(u8 **)(*(u8 **)((a) + 0xC0) + 0x40))
s32 func_801153E4(u8 *a)
{
    switch (a[7]) {
    case 0:
        break;
    case 1:
        func_80115300(EP_MODEL(a), D_8011EC6C[EP_FRAME(a)]);
        if (++EP_FRAME(a) >= 8) {
            EP_FRAME(a) = 7;
            return 1;
        }
        break;
    case 2:
        func_80115300(EP_MODEL(a), D_8011FA00[EP_FRAME(a)]);
        if (++EP_FRAME(a) >= 7) {
            EP_FRAME(a) = 0;
            a[7] = 0;
            return 1;
        }
        break;
    case 3:
        func_80115300(EP_MODEL(a), D_80121504[EP_FRAME(a)]);
        if (++EP_FRAME(a) >= 6) {
            EP_FRAME(a) = 5;
            return 1;
        }
        break;
    case 4:
        func_80115300(EP_MODEL(a), D_80121504[EP_FRAME(a)]);
        if (++EP_FRAME(a) >= 14) {
            EP_FRAME(a) = 13;
            return 1;
        }
        break;
    case 5:
        func_80115300(EP_MODEL(a), D_80125A24[EP_FRAME(a)]);
        if (++EP_FRAME(a) >= 6) {
            EP_FRAME(a) = 5;
            return 1;
        }
        break;
    case 6:
    case 7:
    case 8:
        func_80115300(EP_MODEL(a), D_80124548[EP_FRAME(a)]);
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
        func_80115300(EP_MODEL(a), D_801258E4[EP_FRAME(a)]);
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

extern s16 D_800BF83A;
extern s32 D_80125D6C[];
extern s32 D_80125D80[];
extern s32 D_80125D94[];
extern u8 D_801259FC[];
extern u8 D_80017FC0[];
extern u8 D_1F800236;
extern s16 D_1F800240;
typedef struct { u8 pad[0x5E6]; u16 f5E6; } GameState5E6;
#define G ((u8 *)&D_800BF870)
void func_80115A10(u8 *a)
{
    s32 one = 1;
    u8 v;
    u8 *g;
    u8 *q;
    s32 k;

    switch (a[4]) {
    case 0:
        if (func_800519E0(a, 5, D_800ECF58[D_80125D6C[D_800BF870.unk0 - 10]], D_801259FC) == 0) {
            W(a, 0x3C) = D_800ECF58[D_80125D80[D_800BF870.unk0 - 10]];
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
            func_8004D4C4(D_80125D94[D_800BF870.unk0 - 10], 1);
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
            if (func_801156AC(a) != 0) {
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
            if (func_801158EC(a) != 0) {
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

#define P(p, o) (*(void **)((u8 *)(p) + (o)))
#define P(p, o) (*(u8 **)((u8 *)(p) + (o)))
extern u8 D_1F800259;
extern u8 D_800BF84C;
void func_80116040(u8 *a)
{
    u8 *b = D_1F80024C_2bfb;
    s32 r, done, x, z, k;
    u16 t;

    switch (a[6]) {
    case 0:
        func_800521F4(0, 0, 0x81, 2);
        func_801153E4(a);
        if (func_80115DD0(a, b) != 0) {
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
        r = func_801153E4(a);
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
        if (func_801153E4(a) != 0) {
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
        if (func_801153E4(a) != 0) {
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
extern s32 D_80126114[];
extern s32 D_8012612C[];
extern s16 D_80126144[];
extern u8 D_80125F34[];
extern u8 D_80117FA4[];
void func_80115A10();
void func_80116404(u8 *a)
{
    u8 *e = D_800E7E80;
    u8 *p = D_1F80024C_2bfb;
    s16 *t;
    u8 *r;
    u16 v;
    u16 w;

    switch (a[6]) {
    case 0:
        if (func_801153E4(a) != 0) {
            func_8004D298(D_800BF870.unk0 - 10);
            p[4] = 3;
            H(a, 0x40) = 0x1E;
            a[6]++;
        }
        break;
    case 1:
        if (--H(a, 0x40) == 0) {
            H(a, 0x40) = 0x3C;
            func_8003116C(D_80126114[D_800BF870.unk0 - 10], a + 0x2C, -0x50);
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
            func_80040C00(D_80126144[D_800BF870.unk0 - 10]);
            switch (D_800BF870.unk0) {
            case 10:
                D_800BF870.pad1[0x188] = 6;
                break;
            case 13:
                D_800BF870.pad1[0x166] = 5;
                break;
            }
            D_1F800137_104c = 2;
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
                D_1F800137_104c = 1;
                func_80040CDC(a, 0, D_80125F34);
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
            func_8003116C(D_8012612C[D_800BF870.unk0 - 10], a + 0x2C, -0x1E);
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
                    W(r, 0x1C) = (s32)func_80115A10;
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

s32 func_801168DC(u8 *a0)
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

extern u8 D_801270BC[];
extern u16 D_1F800162_b816;
void func_80117788(u8 *a)
{
    s16 dx, dz, dy;
    s16 ang;
    s16 v;
    dx = D_1F800160_3621 - *(u16 *)(a + 0x2E);
    dz = D_1F800164_7d8c - *(u16 *)(a + 0x36);
    dy = D_1F800162_b816 - *(u16 *)(a + 0x32);
    ang = func_80085690(dy, (s16)func_80084080(dx * dx + dz * dz)) + 0x400;
    *(s16 *)(a + 0x4A) = -func_80083F50(ang);
    v = func_80083E80(ang);
    if (a[0xBE] != 0) {
        *(s16 *)(a + 0x44) = -v;
    } else {
        *(s16 *)(a + 0x44) = v;
    }
    func_80077CFC(a, D_801270BC, 1, 4);
}

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

extern s16 D_1F8001A6;
extern u8 D_1F80025A;
/* func_801181CC, inlined */
static inline void inl_801181CC(void *arg0) {
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
static inline void inl_ricochet_move(u8 *a)
{
    u16 t;

    inl_801181CC(a);
    func_8004766C(a);
    func_80049760(a);
    t = D_1F8001A0;
    *(s16 *)(a + 0x60) = t;
    *(u16 *)(a + 0x56) = t;
    if (a[0x29] == 0) {
        a[0x29] = func_800495DC(a, 0, 0);
        if (a[0x29] != 0 && (D_1F8001A6 & 0x8000)) {
            a[0x5E] = 1;
        }
    }
}
void f_UpdateGhostEvilPigRicochetProjectile(u8 *a)
{
    u8 *p;

    switch (a[4]) {
    case 0:
        func_80117BF4(a);
        break;
    case 1:
        if (D_1F800259 != 0) {
            a[0] = 2;
            a[4] = 2;
            a[0x5E] = 1;
        } else if (D_800BF809 == 0) {
            switch (a[5]) {
            case 0:
                inl_ricochet_move(a);
                if (*(volatile u8 *)(a + 0x29) == 0) {
                    if (*(s16 *)(a + 0x50) > 0x80) {
                        if (a[0x5E] != 0 || D_1F80025A >= 4) {
                            a[0x5E] = 1;
                            a[5]++;
                        } else {
                            goto hit;
                        }
                    }
                } else {
                    goto hit;
                }
                break;
            case 1:
                inl_ricochet_move(a);
                if (*(volatile u8 *)(a + 0x29) != 0) {
                hit:
                    a[0] = 2;
                    a[4] = 2;
                }
                break;
            }
            *(s16 *)(a + 0x58) += 0x111;
        }
        func_8007778C(a);
        break;
    case 2:
        if (a[0x5E] == 0 && D_1F80025A < 4) {
            func_80117AC8(a);
        }
        func_8003116C(0xD02, a + 0x2C, -0x14);
        a[4]++;
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

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

extern SVec D_1F8000C8;
void f_UpdateGhostEvilPigRicochetProjectile(u8 *a);
u8 *f_SpawnGhostEvilPigRicochetProjectile(u8 *a, s32 k)
{
    u8 *p = func_8007A980(1, 2, 0);
    SVec *v;
    SVec *w;

    if (p == NULL) {
        return NULL;
    }
    v = &D_1F8000C0;
    *(void **)(p + 0x1C) = f_UpdateGhostEvilPigRicochetProjectile;
    p[2] = 0x58;
    w = &D_1F8000C8;
    p[3] = k;
    D_1F8000C0.x = 0x32;
    v->y = 0;
    v->z = 0;
    func_800844C0(*(u8 **)(a + 0x100) + 0x18, v, w);
    *(u16 *)(p + 0x2E) = *(u16 *)(*(u8 **)(a + 0x100) + 0x2C) + D_1F8000C8.x;
    *(u16 *)(p + 0x32) = *(u16 *)(*(u8 **)(a + 0x100) + 0x30) + w->y;
    *(u16 *)(p + 0x36) = *(u16 *)(*(u8 **)(a + 0x100) + 0x34) + w->z;
    p[0x2A] = a[0x2A];
    p[0xBE] = a[0xBE];
    return p;
}

void func_8011836C(u8 *a)
{
    s32 dx, dy, dz, s, c;
    {
        s16 *p0 = &D_1F800160_71b4;
        s16 *p1 = &D_1F800162_b816_b4b8;
        s16 *p2 = &D_1F800164_d75f;
        dx = *p0 - H(a, 0x2E);
        dy = *p1 - H(a, 0x32);
        dz = *p2 - H(a, 0x36);
    }
    s = func_80083F50(-H(a, 0x56));
    c = func_80083E80(-H(a, 0x56));

    H(a, 0x64) = func_800776F8((s16)func_80085690(dy, (s * dx + c * dz) >> 12), H(a, 0x64), 0x40);
    H(a, 0x44) += 0xE0;
    if (H(a, 0x44) > 0x1800) {
        H(a, 0x44) = 0x1800;
    }
}

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", f_UpdateGhostEvilPigGraspActor);

void f_UpdateGhostEvilPigGraspActor(u8 *a);
u8 *f_SpawnGhostEvilPigGraspActor(u8 *a)
{
    u8 *p = func_8007A980(1, 2, 0);
    SVec *v;
    SVec *w;

    if (p == NULL) {
        return NULL;
    }
    v = &D_1F8000C0;
    w = &D_1F8000C8;
    *(void **)(p + 0x1C) = f_UpdateGhostEvilPigGraspActor;
    p[2] = 0xD1;
    p[3] = 0;
    D_1F8000C0.x = 0xC8;
    v->y = 0;
    v->z = 0;
    {
        u8 *m = *(u8 **)(a + 0xC4);
        D_1F80025B++;
        func_800844C0(m + 0x18, v, w);
    }
    *(u16 *)(p + 0x2E) = *(u16 *)(*(u8 **)(a + 0xC4) + 0x2C) + D_1F8000C8.x;
    *(u16 *)(p + 0x32) = *(u16 *)(*(u8 **)(a + 0xC4) + 0x30) + w->y;
    *(u16 *)(p + 0x36) = *(u16 *)(*(u8 **)(a + 0xC4) + 0x34) + w->z;
    p[0x2A] = a[0x2A];
    p[0xBE] = a[0xBE];
    return p;
}

void func_80118B54(u8 *a)
{
    u8 *e;
    u16 t;
    a[0xB] = 0xFF;
    a[0xD] = 1;
    a[0x29] = 0;
    a[0x5F] = 0;
    a[0x2B] = 0;
    a[0x5E] = 0;
    a[0xBF] = 0;
    *(s16 *)(a + 0x62) = 0x12C;
    *(s16 *)(a + 0x42) = 0;
    if (func_8004766C() == 0) {
        a[4] = 3;
        return;
    }
    a[4] = 1;
    func_80049760(a);
    t = D_1F8001A0;
    *(s16 *)(a + 0x44) = 0x100;
    *(u16 *)(a + 0x60) = t;
    *(u16 *)(a + 0x56) = t;
    if (a[0xBE] != 0) {
        *(s16 *)(a + 0x64) = 0x800;
    } else {
        *(s16 *)(a + 0x64) = 0;
    }
    *(s16 *)(a + 0x80) = 0x50;
    *(s16 *)(a + 0x82) = 0xA0;
    *(s16 *)(a + 0x84) = 0x50;
    *(s16 *)(a + 0x86) = 0xA0;
    e = func_800310F4(0xD01, 0);
    *(u8 **)(a + 0x10) = e;
    if (e != NULL) {
        *(u8 **)(e + 0x10) = a;
    }
}

#include "common.h"
#include "game.h"
#include "m2c.h"
#include "gte.h"
#include "psyq/gtemac.h"
typedef struct { s16 x, y, w, h; } ClutRect;

extern u8 D_1F800246_6eef;
#define H(p, o) (*(s16 *)((u8 *)(p) + (o)))

void func_80109320(u8 *a, u8 *b)
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
void func_80109458(u8 *a, u8 *b)
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
s32 func_80109694(u8 *a, u8 *b) {
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
extern void (*D_8009D1D4[])(void);
extern void (*D_8009D22C[])(void);
extern void (*D_8009D314[])(u8 *);
extern void (*D_8009D52C[])(u8 *);
extern void (*D_800A4AF8[])(void);
extern void (*D_800A4B50[])(void);
extern void (*D_800A4AA0[])(u8 *);
extern u8 D_800E8008[];
extern u8 D_1F8000DC[];
s32 func_80109808(u8 *a, u8 *b, u8 *c) {
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

extern s32 D_1F800088;
extern u8 *D_1F800084;
s32 func_80109AEC(u8 *a, u8 *b, u8 *c) {
    s16 rad, ox, oz, dx, dz;
    u16 r, ah, ay;
    s32 h;

    rad = (func_80083E80(F16(c, 0xC)) * 110) >> 12;
    ox = (func_80083E80(F16(b, 0x56)) * rad) >> 12;
    oz = (func_80083F50(F16(b, 0x56)) * rad) >> 12;
    dx = FU16(a, 0x14C) - (FU16(c, 0x2C) - oz);
    dz = FU16(a, 0x150) - (FU16(c, 0x34) + ox);
    r = func_80084080(dx * dx + dz * dz);
    if (F16(b, 0x80) + D_1F800088 < r) {
        return 0;
    }
    h = ((func_80083F50(F16(c, 0xC)) * 110) >> 12) + FU16(c, 0x30);
    ay = FU16(a, 0x14E);
    ah = FU16(a, 0x68);
    if ((u16)(ay - h + (FU16(b, 0x84) + ah)) > F16(b, 0x86) + ((s16)ah << 1)) {
        return 0;
    }
    F16(a, 0x156) = 110;
    D_1F800084 = c;
    return 1;
}

extern u8 D_1F800182;
void func_80109C64(u8 *a, u8 *b, u8 *c) {
    u8 *q = a + 0x60;
    s32 r;
    s32 s1;
    u16 x;
    u16 z;
    u16 y;
    s16 dx;
    s16 dz;
    s32 t;
    s32 u;

    r = (func_80083E80(F16(c, 0xC)) * 0x6E) >> 12;
    s1 = (func_80083E80(F16(b, 0x56)) * (s16)r) >> 12;
    x = FU16(c, 0x2C) - ((func_80083F50(F16(b, 0x56)) * (s16)r) >> 12);
    dx = FU16(a, 0x2E) - x;
    z = FU16(c, 0x34) + s1;
    dz = FU16(a, 0x36) - z;
    if ((u16)func_80084080(dx * dx + dz * dz) > F16(a, 0x80) + F16(b, 0x80)) {
        return;
    }
    y = FU16(c, 0x30) + ((func_80083F50(F16(c, 0xC)) * 0x6E) >> 12);
    if ((u16)((FU16(a, 0x32) - y) + (FU16(a, 0x84) + FU16(b, 0x84))) > F16(a, 0x86) + F16(b, 0x86)) {
        return;
    }
    if (a[0x5F] == 0x10) {
        switch (a[0x46] >> 1) {
        case 0:
        case 1:
            t = (func_80083F50(F16(q, 8) + 0x800) * (F16(a, 0x80) + F16(b, 0x80))) >> 12;
            u = func_80083E80(F16(q, 8) + 0x800) * (F16(a, 0x80) + F16(b, 0x80));
            F16(a, 0x2E) = x + t;
            F16(a, 0x32) = y;
            F16(a, 0x36) = z - (u >> 12);
            break;
        case 2:
        case 3:
            F16(a, 0x2E) = x;
            F16(a, 0x36) = z;
            F16(a, 0x32) = FU16(a, 0x84) + (y + (FU16(b, 0x86) - FU16(b, 0x84)));
            break;
        }
    } else {
        b[0x2B] = 1;
        b[0x5F] = FU16(a, 0x56) >> 4;
    }
    func_8001E860(a, b, c, 0x200);
    D_1F800182 = 0;
}

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_80109ED8);

extern u8 **D_1F80013C;
extern u8 D_1F800144;
extern s16 D_1F800150_058c;
extern u8 D_1F800150;
extern u8 D_1F800183;
extern u8 **D_1F800148;
void func_8010A2D4(void)
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
                        func_80023870(e, o, *(u8 **)(o + 0xC0));
                        break;
                    case 0x18:
                        if (e[0] == 4 && func_800240FC(e) != 0) {
                            e[0x5E] = 1;
                            e[0] = 10;
                        }
                        break;
                    case 0x64:
                        if (e[2] == 0x6A) {
                            func_80109320(e, o);
                        }
                        break;
                    }
                }
            }
        }
    }
}

extern u8 *D_800F2738;
void func_8010A47C(void)
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
            if ((e[0] & 1) && e[2] == 0x6A && func_80022F04(p, e) != 0) {
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
        }
    }
}

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_8010A5F8);

extern s8 D_800BF808[];
extern u8 D_1F800137;
extern u8 D_800E7E80[];
/* func_8010AEE4, inlined */
static inline void inl_8010AEE4(void *arg0, void *arg1) {
    u16 var_v0;

    if (func_80022F04(arg0, arg1) != 0) {
        if (M2C_FIELD(arg1, u8 *, 0x46) & 1) {
            var_v0 = M2C_FIELD(arg0, u16 *, 0x140) + 0x800;
        } else {
            var_v0 = M2C_FIELD(arg0, u16 *, 0x140);
        }
        M2C_FIELD(arg0, s8 *, 0x2B) = (s8) (var_v0 >> 4);
        func_80022D08(arg0, arg1, 1, 0);
    }
}
/* func_8010AF60, inlined */
static inline void inl_8010AF60(u8 *a)
{
    u8 **l = D_1F80013C;
    u8 *p;
    D_1F800182 = D_1F800144;
    while (D_1F800182 != 0) {
        p = *l;
        D_1F800182--;
        l++;
        if (p[0] & 1) {
            if (p[2] != 0x6A) {
                if (p[2] == 0xD3) {
                    inl_8010AEE4(a, p);
                }
            } else {
                func_80109458(a, p);
            }
        }
    }
}
static inline void inl_list148_8010A7A8(u8 *a)
{
    u8 **p;
    u8 *b;
    p = D_1F800148;
    D_1F800182 = D_1F800150;
    while (D_1F800182 != 0) {
        b = *p;
        D_1F800182--;
        p++;
        if (b[0] & 1) {
            switch (b[2]) {
            case 18:
                func_8002311C(a, b);
                break;
            case 7:
                func_80109ED8(a, b, *(s32 *)(b + 0xC0));
                break;
            case 23:
                if (b[0x47] == 2) {
                    func_80109808(a, b, *(s32 *)(b + 0xC0));
                } else {
                    func_8001F650(a, b, *(s32 *)(b + 0xC0));
                }
                break;
            }
        }
    }
}
void func_8010A7A8(void)
{
    u8 *g = D_800E7E80;
    u16 v, m;

    func_8002288C(g);
    switch (g[0]) {
    case 0:
    case 6:
        break;
    case 2:
        if (*(u32 *)(g + 0x158) < 2) {
            inl_list148_8010A7A8(g);
        }
        break;
    case 1:
    case 3:
    case 4:
    case 5:
    case 7:
    default:
        func_80022760(g);
        inl_8010AF60(g);
        if (*(u32 *)(g + 0x158) < 2) {
            inl_list148_8010A7A8(g);
        }
        break;
    }
    func_8010A47C();
    func_8010A5F8();
    func_8010A2D4();
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
            }
        }
    }
}

extern u8 **D_1F80014C;
extern u8 D_1F800152;
extern void *D_1F800080;
void *func_8010AB94(u8 *a)
{
    u8 **l = D_1F80014C;
    u8 *p;

    D_1F800182 = D_1F800152;
    while (D_1F800182 != 0) {
        p = *l;
        D_1F800182--;
        l++;
        if (p[0] & 1) {
            switch (p[2]) {
            case 7:
                if (func_80109AEC(a, p, *(void **)(p + 0xC0)) != 0) {
                    a[0x164] = 3;
                    D_1F800080 = p;
                    D_1F800182 = 0;
                }
                break;
            case 0x17:
                if (p[0x47] != 2 && func_80024BD8(a, p, *(void **)(p + 0xC0)) != 0) {
                    u16 x = *(u16 *)(p + 0x80);
                    u16 y;
                    p[0x29] = 1;
                    y = *(u16 *)(a + 0x80);
                    a[0x164] = 1;
                    a[0x15C] = 0;
                    D_1F800080 = p;
                    D_1F800182 = 0;
                    *(s16 *)(a + 0x152) = x + y - 0xC;
                }
                break;
            }
        }
    }
    return D_1F800080;
}

extern u16 D_1F800164_7d8c;
extern u16 D_1F800160_3621;
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

void func_8010AF60(u8 *a)
{
    u8 **l = D_1F80013C;
    u8 *p;
    D_1F800182 = D_1F800144;
    while (D_1F800182 != 0) {
        p = *l;
        D_1F800182--;
        l++;
        if (p[0] & 1) {
            if (p[2] != 0x6A) {
                if (p[2] == 0xD3) {
                    inl_8010AEE4(a, p);
                }
            } else {
                func_80109458(a, p);
            }
        }
    }
}

void func_8010B078(u8 *a)
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
            case 0x12:
                func_8002311C(a, e);
                break;
            case 7:
                func_80109ED8(a, e, *(void **)(e + 0xC0));
                break;
            case 0x17:
                if (e[0x47] == 2) {
                    func_80109808(a, e, *(void **)(e + 0xC0));
                } else {
                    func_8001F650(a, e, *(void **)(e + 0xC0));
                }
                break;
            }
        }
    }
}

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

extern u8 D_800BF840;
extern u16 D_800ECF54;
extern s16 D_1F80016C;
extern s16 D_1F80016E;
void func_8010B2F8(u8 *a, u8 *b) {
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
    } else {
        if (H(a, 0x42) >= 0x97) {
            D_800BF840 = 0x48;
        }
        func_80062A30(a, b, 3);
    }
}

extern u16 D_1F80017C;
s32 func_8010B4E8(u8 *a, u8 *b, s32 skip) {
    u8 *p;
    s16 ang;

    a[0x160] = 0;
    if (skip == 0) {
        switch (a[7]) {
        case 0:
            func_80063098(a);
            func_80076D68(a);
            break;
        case 1:
            func_80063158(a);
            func_80076D68(a);
            break;
        case 2:
            a[0x5E] = 0;
            H(a, 0x42) = 0;
            func_80054D14(a, 0x29, 4);
            H(a, 0x40) = 0x5A;
            a[7]++;
        case 3:
            if (--H(a, 0x40) == 0) {
                H(a, 0x40) = 0x5A;
                a[7]++;
                if (!(func_8009A450() & 1)) {
                    func_80054D14(a, 0x28, 0);
                } else {
                    func_80054D14(a, 0x27, 0);
                }
            }
            func_8010B2F8(a, b);
            func_80076D68(a);
            break;
        case 4:
            if (--H(a, 0x40) == 0) {
                a[7]--;
                H(a, 0x40) = ((func_8009A450() & 3) + 3) * 30;
                if (H(a, 0x42) < 8) {
                    H(a, 0x42) = 8;
                }
                func_80054D14(a, 0x29, 4);
            }
            func_8010B2F8(a, b);
            func_80076D68(a);
            break;
        case 5:
            func_80076D68(a);
            if (D_800ECF54 & 0x10) {
                if (!(D_1F80017C & 3)) {
                    func_80074590(0x27, -5, -0x46);
                }
                func_80054D14(a, 0x34, 0);
                func_80062A30(a, b, 0);
            } else if (D_800ECF54 & 0x40) {
                if (!(D_1F80017C & 3)) {
                    func_80074590(0x27, -3, -0x46);
                }
                func_80054D14(a, 0x3D, 0);
                func_80062A30(a, b, 1);
            } else {
                a[7] = 3;
                H(a, 0x42) = 8;
                func_80054D14(a, 0x29, 4);
                H(a, 0x40) = 0x5A;
                func_80062A30(a, b, 3);
            }
            break;
        case 6:
            if (D_800ECF54 & 0xF0) {
                if ((D_800ECF54 & D_1F80016C) && a[0x147] == 0) {
                    a[7] = 0;
                    H(a, 0x154) = 0;
                    H(a, 0x42) = 0;
                    a[0] |= 4;
                    func_80054D14(a, 0x37, 0);
                } else if ((D_800ECF54 & D_1F80016E) && a[0x147] == 1) {
                    a[7] = 0;
                    H(a, 0x154) = 0;
                    H(a, 0x42) = 0;
                    a[0] |= 4;
                    func_80054D14(a, 0x37, 0);
                } else if (D_800ECF54 & 0x10) {
                    a[7] = 5;
                    func_80054D14(a, 0x34, 0);
                    func_80062A30(a, b, 0);
                } else if (D_800ECF54 & 0x40) {
                    a[7] = 5;
                    func_80054D14(a, 0x3D, 0);
                    func_80062A30(a, b, 1);
                } else {
                    func_80076D68(a);
                    func_80062A30(a, b, 3);
                }
            } else {
                H(a, 0x40) = 0x5A;
                H(a, 0x42) = 8;
                a[7] = 3;
                func_80054D14(a, 0xA9, 0);
                func_80062A30(a, b, 3);
            }
            break;
        }
    } else {
        func_80062A30(a, b, 3);
    }
    p = *(u8 **)(a + 0x10);
    if (*(s32 *)(a + 0x158) != 0) {
        ang = H(a, 0x56) + 0x800;
        H(a, 0x2E) = H(p, 0x2C) + ((func_80083F50(ang) * H(a, 0x152)) >> 12);
        H(a, 0x36) = H(p, 0x34) - ((func_80083E80(ang) * H(a, 0x152)) >> 12);
        H(a, 0x32) = H(p, 0x30) + H(a, 0x156);
        return 0;
    }
    H(a, 0x32) = H(p, 0x30) + H(a, 0x156);
    return 1;
}

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

typedef struct { u16 lo; u16 hi; } Fix;
typedef struct {
    Fix at[3];
    Fix pos[3];
    s16 dir[3];
    u8 pad1E[0x2A];
    u8 m[0x20];
} Cam;
extern Cam D_1F8000D0_8c3c;
extern u16 D_1F8000EE;
#define U(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define W(p, o) (*(s32 *)((u8 *)(p) + (o)))
void func_8010BA54(u8 *a, u8 *b, s32 ang)
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
    c = &D_1F8000D0_8c3c;
    d = c->at[1].hi + h - c->pos[1].hi;
    if ((u16)(d + 10) >= 0x15) {
        W(c, 4) -= (d << 16) >> 3;
    } else {
        c->at[1].hi = c->pos[1].hi - h;
        a[0x66] |= 2;
    }
    x = U(b, 0x2E) + ((func_80083F50(t) * dist) >> 12);
    z = U(b, 0x36) - ((func_80083E80(t) * dist) >> 12) - D_1F8000D0_8c3c.at[2].hi;
    x = x - D_1F8000D0_8c3c.at[0].hi;
    t = func_80085690(-z, x);
    dist = func_80084080(x * x + z * z);
    W(&D_1F8000D0_8c3c, 0) += func_80083F50(t) * dist;
    W(&D_1F8000D0_8c3c, 8) -= func_80083E80(t) * dist;
    if (dist < 0x191) {
        a[0x66] |= 1;
    }
}

extern u8 D_1F8000D0_b839[];
void func_8010BC78(u8 *a, u8 *b)
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
        if (H(p, 0x2E) > H(b, 0x2E)) {
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

typedef struct { s16 xl, x, yl, y, zl, z; } PosBE48;
extern u8 D_800BF821;
extern s16 D_1F8000EE_be48;
extern u8 D_1F800246_be48;
extern u8 *D_1F800248_be48;
extern u8 *D_1F80024C_be48;
extern u8 D_800BF808_be48[];
extern u8 D_1F8000D0_be48[];
void func_8010BC78(u8 *a, u8 *b);
void func_8010BE48(u8 *a)
{
    u8 *g;
    u8 *m;
    PosBE48 pos;

    switch (a[3]) {
    case 0:
        H(a, 0x26) = -0x3E8;
        D_800BF821 = 2;
        H(a, 0x56) = 0;
        D_1F8000EE_be48 = -0x6D6;
        a[3]++;
        break;
    case 1:
        if (D_1F800246_be48 != 0) {
            a[0x64] |= 0x80;
            a[3]++;
            ((void (*)())func_8010BC78)(a, D_1F800248_be48, 0);
            func_8006E3F4(a, D_1F80024C_be48 + 0x2C);
        }
        break;
    case 2:
        if (D_1F800246_be48 == 0) {
            a[0x64] &= 0x7F;
            a[3]++;
            D_800BF821 = 2;
            H(a, 0x56) = 0;
            D_1F8000EE_be48 = -0x8CA;
            func_8006EA00();
            H(a, 0x68) = 0xC;
        } else if (D_1F800246_be48 == 1) {
            ((void (*)())func_8010BC78)(a, D_1F800248_be48, 0);
            func_8006E3F4(a, D_1F80024C_be48 + 0x2C);
        } else if (D_1F800246_be48 == 2) {
            func_8006E3F4(a, D_1F80024C_be48 + 0x2C);
            pos.x = U(D_1F800248_be48, 0x2E);
            pos.y = U(D_1F800248_be48, 0x7C) - 0x64;
            pos.z = 0xAF0;
            func_8006CEC4(D_1F8000D0_be48, &pos, 0);
        } else {
            func_8006E3F4(a, D_1F800248_be48 + 0x2C);
            pos.x = U(D_1F800248_be48, 0x2E);
            pos.y = U(D_1F800248_be48, 0x7C) - 0x64;
            pos.z = 0xAF0;
            func_8006CEC4(D_1F8000D0_be48, &pos, 0);
        }
        break;
    case 3:
        if (--H(a, 0x68) == 0) {
            g = D_800BF808_be48;
            if (g[0x39] != 0) {
                g[1] = 0;
                g[0x39] = 0;
            }
            a[3] = 1;
        }
        break;
    }
    m = D_1F8000D0_be48;
    if (H(m, 6) < -0x3366) {
        a[0x74] = 2;
        H(m, 6) = -0x3366;
        H(a, 0x4A) = -0x3366;
    } else {
        a[0x74] = 0;
    }
}

void func_8010C098(void) {
}

void func_8010C0A0(void) {
}

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_8010C0A8);

typedef struct { s16 x, y, z, pad; } SVec;
extern SVec D_1F8000C0;
extern SVec D_1F8000C8;
extern u8 *D_1F80024C_2bfb;
extern u16 D_8011A9D8[];
/* func_8010DAC4, inlined */
static inline void inl_8010DAC4(u8 *a)
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
/* func_8010D924, inlined */
static inline void inl_8010D924(u8 *a)
{
    u16 v = D_8011A9D8[a[3]];
    *(u16 *)(a + 0x40) = 2;
    *(u16 *)(a + 0x44) = v;
}
void func_8010C198(u8 *a)
{
    u8 *b = a + 0x60;
    switch ((a[0x46] >> 1) & 3) {
    case 0:
    case 1:
        *(u16 *)(b + 0xA) = 0;
        break;
    case 2:
        *(u16 *)(b + 0xA) = 0xE40;
        break;
    case 3:
        *(u16 *)(b + 0xA) = 0xC10;
        break;
    }
    a[0x46] &= 7;
    *(u16 *)(a + 0x58) = *(u16 *)(b + 0xA);
    inl_8010D924(a);
    inl_8010DAC4(a);
    func_80031558(a, a[3]);
}

void func_8010C2F4(u8 *a)
{
    u8 *m = a + 0x60;

    switch (a[7]) {
    case 0:
        a[7] = 1;
        *(s16 *)(m + 6) = 3;
    case 1:
        if (a[0x2B] != 0) {
            a[6] = 8;
            *(s16 *)(a + 0x44) = 0;
            return;
        }
        *(s16 *)(a + 0x40) = 1;
        a[7]++;
        return;
    case 2:
        if (a[0x2B] != 0) {
            *(s16 *)(a + 0x44) = 0;
            a[7]++;
            return;
        }
        if (--*(s16 *)(a + 0x40) == 0) {
            a[7]++;
        }
        return;
    case 3:
        if (a[3] == 0) {
            *(s16 *)(a + 0x44) -= *(s16 *)(m + 0x16);
            if (*(s16 *)(a + 0x44) < 0 || a[0x2B] != 0) {
                *(s16 *)(a + 0x44) = 0;
                a[0] = 2;
                a[6]++;
            }
        } else {
            *(s16 *)(a + 0x44) -= *(s16 *)(m + 0x16);
            if (*(s16 *)(a + 0x44) < 0x46 || a[0x2B] != 0) {
                *(s16 *)(a + 0x44) = 0;
                a[0] = 2;
                a[6]++;
            }
        }
        break;
    }
}

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_8010C448);

void func_8010CA3C(u8 *a)
{
    u8 *b = a + 0x60;
    u8 *t;

    switch ((a[0x46] >> 1) & 3) {
    case 0:
    case 1:
        *(u16 *)(b + 0xA) = 0;
        break;
    case 2:
        *(u16 *)(b + 0xA) = 0xE40;
        break;
    case 3:
        *(u16 *)(b + 0xA) = 0xC20;
        break;
    }
    a[0x46] &= 7;
    inl_8010D924(a);
    func_80031558(a, a[3]);
    *(u16 *)(a + 0x56) = *(u16 *)(b + 8);
    *(u16 *)(a + 0x42) = 2;
    t = D_1F80024C_2bfb;
    D_1F8000C0.x = 0;
    D_1F8000C0.y = -0xC8;
    D_1F8000C0.z = 0;
    func_800844C0(*(u8 **)(t + 0xE4) + 0x18, &D_1F8000C0, &D_1F8000C8);
    *(u16 *)(a + 0x2E) = *(u16 *)(*(u8 **)(t + 0xE4) + 0x2C) + D_1F8000C8.x;
    *(u16 *)(a + 0x32) = *(u16 *)(*(u8 **)(t + 0xE4) + 0x30) + D_1F8000C8.y;
    *(u16 *)(a + 0x36) = *(u16 *)(*(u8 **)(t + 0xE4) + 0x34) + D_1F8000C8.z;
}

void func_8010CB8C(u8 *a)
{
    u8 *m = a + 0x60;

    switch (a[7]) {
    case 0:
        a[7] = 1;
    case 1:
        if (a[0x2B] >= 2) {
            *(u16 *)(a + 0x44) = 0;
            a[7] = 3;
            return;
        }
        a[7]++;
        break;
    case 2:
        if (a[0x2B] == 1) {
            *(u16 *)(a + 0x42) = 2;
            a[0x2B] = 0;
        } else if (a[0x2B] >= 2) {
            *(u16 *)(a + 0x44) = 0;
        }
        a[7]++;
        break;
    case 3:
        *(u16 *)(a + 0x44) -= *(u16 *)(m + 0x16);
        *(u16 *)(m + 0xA) -= 0x80;
        if (a[0x2B] == 1) {
            if (--*(s16 *)(a + 0x42) == 0) {
                a[0x2B] = 0;
                *(u16 *)(a + 0x42) = 2;
            }
        }
        if (*(s16 *)(a + 0x44) < 0 || a[0x2B] >= 2) {
            a[0x2B] = 2;
            *(u16 *)(a + 0x44) = 0;
            a[7] = 0;
            a[6]++;
            switch ((a[0x46] >> 1) & 3) {
            case 0:
            case 1:
                *(u16 *)(m + 0xA) = 0xC00;
                break;
            case 2:
                *(u16 *)(m + 0xA) = 0x980;
                break;
            case 3:
                *(u16 *)(m + 0xA) = 0x700;
                break;
            }
        }
        break;
    }
}

s32 func_8010CD20(u8 *a)
{
    u8 s;

    if (func_80069858(a, 0, 0) == 0) {
        return 0;
    }
    if (*(s16 *)(a + 0x44) > 0) {
        *(s16 *)(a + 0x44) = 0;
    }
    a[0] = 2;
    a[0x2B] = 2;
    switch (a[3]) {
    case 4:
    case 5:
        func_80074590(0x2C, 0, 0);
        func_80074590(0x2D, 0, 0);
        func_80027144(*(s32 *)(*(u8 **)(a + 0xC0) + 0x40), a + 0x2C, 0x400, 0x15);
        func_80074590(0xC, 0, 0);
        break;
    }
    func_80074590(0x2F, 0, 0);
    func_80031470(2, a + 0x2C, 0, a + 0x68);
    if (a[3] != 3) {
        s = a[0];
        if (s == 2) {
            a[0x2B] = s;
            a[4] = s;
        }
    }
    return 1;
}

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_8010CE24);

extern void *D_800ECF80;
extern u8 D_80129EC0[];
extern u8 D_8011A9EC[];
void f_InitializeLastEvilPigCopiedWeaponProjectile(u8 *a)
{
    s16 *p = (s16 *)(a + 0x60);
    s16 v;

    switch (a[3]) {
    case 0:
        a[0xB] = 0x10;
        a[0xD] = 0;
        *(s16 *)(a + 0x5C) = 0;
        *(void **)(a + 0x3C) = D_800ECF80;
        func_80077B38(a, D_80129EC0, 0);
        *(s16 *)(a + 0x80) = 0x46;
        *(s16 *)(a + 0x82) = 0x8C;
        *(s16 *)(a + 0x84) = 0x46;
        *(s16 *)(a + 0x86) = 0x8C;
        break;
    case 1:
        func_80051B70(a, 1, D_8011A9EC[a[3]]);
        a[0xB] = 0;
        *(s16 *)(a + 0x80) = 0x46;
        *(s16 *)(a + 0x82) = 0x8C;
        *(s16 *)(a + 0x84) = 0x46;
        *(s16 *)(a + 0x86) = 0x8C;
        break;
    case 2:
        func_80051B70(a, 1, D_8011A9EC[a[3]]);
        a[0xB] = 0;
        *(s16 *)(a + 0x80) = 0x46;
        *(s16 *)(a + 0x82) = 0x8C;
        *(s16 *)(a + 0x84) = 0x46;
        *(s16 *)(a + 0x86) = 0x8C;
        break;
    case 3:
        func_80051B70(a, 1, D_8011A9EC[a[3]]);
        a[0xB] = 0;
        *(s16 *)(a + 0x80) = 0x46;
        *(s16 *)(a + 0x82) = 0x8C;
        *(s16 *)(a + 0x84) = 0x46;
        *(s16 *)(a + 0x86) = 0x8C;
        break;
    case 4:
        func_80051B70(a, 1, D_8011A9EC[a[3]]);
        a[0xB] = 0;
        *(s16 *)(a + 0x80) = 0x46;
        *(s16 *)(a + 0x82) = 0x8C;
        *(s16 *)(a + 0x84) = 0x46;
        *(s16 *)(a + 0x86) = 0x8C;
        break;
    case 5:
        func_80051B70(a, 1, D_8011A9EC[a[3]]);
        a[0xB] = 0;
        *(s16 *)(a + 0x80) = 0x46;
        *(s16 *)(a + 0x82) = 0x8C;
        *(s16 *)(a + 0x84) = 0x46;
        *(s16 *)(a + 0x86) = 0x8C;
        break;
    }
    p[9] = 0;
    a[0x29] = 0;
    *(s16 *)(a + 0x54) = 0;
    *(s16 *)(a + 0x58) = 0;
    if (a[3] == 5) {
        *(s16 *)(a + 0xB8) = 0x1C00;
        *(s16 *)(a + 0xBA) = 0x1C00;
        *(s16 *)(a + 0xBC) = 0x1C00;
    } else {
        *(s16 *)(a + 0xB8) = 0x1800;
        *(s16 *)(a + 0xBA) = 0x1800;
        *(s16 *)(a + 0xBC) = 0x1800;
    }
    a[0x2B] = 0;
    *(s16 *)(a + 0x44) = 0;
    a[0x5E] = 0;
    func_8004766C(a);
    func_80049760(a);
}

extern s16 D_1F800266;
/* func_8010DC78, inlined */
static inline void inl_8010DC78(u8 *a)
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
void func_8010D4B8(u8 *a)
{
    u8 *b = a + 0x60;
    u8 *t = D_1F80024C_2bfb;

    switch (a[4]) {
    case 0:
        a[0xB] = 0xFF;
        *(s16 *)(a + 0x80) = 0x96;
        *(s16 *)(a + 0x82) = 0x12C;
        *(s16 *)(a + 0x84) = 0xD2;
        *(s16 *)(a + 0x86) = 0x168;
        a[0] = 1;
        a[0x2B] = 0;
        *(s16 *)(a + 0x40) = 0xA;
        a[4]++;
        func_80074590(0xA, -3, 0x14);
        *(s16 *)(a + 0x56) = *(s16 *)(t + 0x56);
        *(s16 *)(b + 8) = *(s16 *)(t + 0x56);
        *(s16 *)(b + 0xA) = 0x400;
        func_80031558(a, a[3]);
    case 1:
        if (a[3] == 6) {
            D_1F8000C0.y = -0xC8;
        } else if (a[3] == 7) {
            D_1F8000C0.y = -0xC8;
        } else {
            D_1F8000C0.y = -0xFA;
        }
        D_1F8000C0.x = 0;
        D_1F8000C0.z = 0;
        func_800844C0(*(u8 **)(t + 0xE4) + 0x18, &D_1F8000C0, &D_1F8000C8);
        *(u16 *)(a + 0x2E) = *(u16 *)(*(u8 **)(t + 0xE4) + 0x2C) + D_1F8000C8.x;
        *(u16 *)(a + 0x32) = *(u16 *)(*(u8 **)(t + 0xE4) + 0x30) + D_1F8000C8.y;
        *(u16 *)(a + 0x36) = *(u16 *)(*(u8 **)(t + 0xE4) + 0x34) + D_1F8000C8.z;
        if (*(s16 *)(a + 0x40) < 5) {
            inl_8010DC78(a);
        }
        if (--*(s16 *)(a + 0x40) == 0) {
            a[0] = 2;
            a[4] = 2;
        }
        func_8007778C(a);
        break;
    case 2:
    case 3:
        D_1F800266 = 1;
        func_8007A624(a);
        break;
    }
}

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_8010D738);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_8010D830);

extern u8 D_8011A9E4[];
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

typedef struct {
    u8 *ptr;
    u8 *clut;
    s16 x;
    s16 y;
} ClutCycle;
extern ClutCycle D_8011AE60[];
extern s8 D_801297A8[];
extern u8 D_800BF873;
void func_8010DF5C(s32 arg0) {
    ClutRect r;
    s32 i;
    ClutCycle *e;
    u8 *data;

    if (arg0 == 0) {
        s8 *p;
        i = 11;
        p = &D_801297A8[i];
        do {
            *p-- = 0;
        } while (--i >= 0);
        return;
    }
    e = D_8011AE60;
    for (i = 0; i < 12; i++, e++) {
        if (--D_801297A8[i] <= 0) {
            if (e->ptr[0] == 0xFF) {
                e->ptr -= e->ptr[1];
            }
            data = e->clut + e->ptr[0] * 32;
            D_801297A8[i] = e->ptr[1];
            r.x = e->x;
            r.y = e->y;
            r.w = 16;
            r.h = 1;
            func_80081218(&r, data);
            e->ptr += 2;
        }
    }
}

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

void func_8010E15C(u8 *a, u8 *b, s32 ang)
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
    c = &D_1F8000D0_8c3c;
    d = c->at[1].hi + h - c->pos[1].hi;
    if ((u16)(d + 10) >= 0x15) {
        W(c, 4) -= (d << 16) >> 3;
    } else {
        c->at[1].hi = c->pos[1].hi - h;
        a[0x66] |= 2;
    }
    x = U(b, 0x2E) + ((func_80083F50(t) * dist) >> 12);
    z = U(b, 0x36) - ((func_80083E80(t) * dist) >> 12) - D_1F8000D0_8c3c.at[2].hi;
    x = x - D_1F8000D0_8c3c.at[0].hi;
    t = func_80085690(-z, x);
    dist = func_80084080(x * x + z * z);
    W(&D_1F8000D0_8c3c, 0) += func_80083F50(t) * dist;
    W(&D_1F8000D0_8c3c, 8) -= func_80083E80(t) * dist;
    if (dist < 0x191) {
        a[0x66] |= 1;
    }
}

extern void *D_8011F054[];
extern u8 *D_1F800248;
void func_8010E380(u8 *a)
{
    u8 *pl = D_800E7E80;
    s32 s;
    s = a[4];
    switch (s) {
    case 0:
        if (func_80051B70(a, 0xC, D_8011F054[D_800BF870.unk0 - 10]) == 0) {
            H(a, 0x54) = 0;
            a[4]++;
            H(a, 0x56) = func_800782B0(a + 0x2C, (s16)D_1F8000D0_8c3c.at[0].hi, (s16)D_1F8000D0_8c3c.at[2].hi) - 0x400;
            H(a, 0x58) = 0;
            H(a, 0x4A) = 0;
            **(s16 **)(a + 0xC0) = 0x28;
        }
        break;
    case 1:
        H(a, 0x56) = func_800782B0(a + 0x2C, (s16)D_1F8000D0_8c3c.at[0].hi, (s16)D_1F8000D0_8c3c.at[2].hi) - 0x400;
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

s32 func_8010E550(u8 *a)
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

extern u8 *D_8011F024[][2];
void func_8010E63C(u8 *a)
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
    t = D_8011F024[D_800BF870.unk0 - 10][low];
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
extern SelPt D_8011EBAC_e50f[];
extern u8 D_800E7EAA;
extern u8 D_1F80025C[];
extern u16 D_1F800162_b816;
s32 func_8010E74C(void *arg0, s32 mode)
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
        for (i = 0; i < 0x77; i++) {
            if (fl) {
                if (D_800E7EAA == 1) {
                    if (D_8011EBAC_e50f[i].f != 1) {
                        continue;
                    }
                } else if (D_8011EBAC_e50f[i].f == 1) {
                    continue;
                }
            }
            dx = D_1F800160_3621 - D_8011EBAC_e50f[i].x;
            dz = D_1F800164_7d8c - D_8011EBAC_e50f[i].z;
            d = func_80084080(dx * dx + dz * dz);
            dy = D_1F800162_b816 - 0x190;
            if (d < 0x640 && dy < D_8011EBAC_e50f[i].y) {
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
        for (i = 0; i < 0x77; i++) {
            if (fl) {
                if (D_800E7EAA == 1) {
                    if (D_8011EBAC_e50f[i].f != 1) {
                        continue;
                    }
                } else if (D_8011EBAC_e50f[i].f == 1) {
                    continue;
                }
            }
            dx = D_1F800160_3621 - D_8011EBAC_e50f[i].x;
            dy = D_1F800162_b816 - D_8011EBAC_e50f[i].y;
            dz = D_1F800164_7d8c - D_8011EBAC_e50f[i].z;
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
extern u8 D_800BF809;
extern u8 D_800E7FC5;
extern ArenaPt D_8011EBAC[];
extern s16 D_1F8001A4;
extern u8 D_1F80025B;
void func_8010EDF8(u8 *a)
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
        if (func_8010E550(a) != 0) {
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
        k = func_8010E74C(a, H(a, 0x64));
        switch (D_800BF870.unk0) {
        case 10:
        case 11:
        case 13:
            t = D_8011EBAC; e = &t[k];
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
            t2 = D_8011EBAC; e2 = &t2[k];
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
            t3 = D_8011EBAC; e3 = &t3[k];
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

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_8010F48C);

typedef struct { s16 m[3][3]; s16 pad; s32 t[3]; } AreaMatrix;
typedef struct { s16 x, y, z, pad; } AreaSVec;
typedef struct { u8 pad[0x28]; AreaMatrix m; } AreaScratchD0;
void func_8010FCF0(u8 *a)
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
        if (*(s16 *)(a + 0x40) < 0x1E && func_8010E550(a) != 0) {
            a[0] = 2;
            func_80041768(a, 3, 4);
            func_8010E63C(a);
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
void func_8010FE34(u8 *a, u8 *b)
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
                func_8010E63C(a);
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
                func_8010E15C(D_800E8008, a, H(a, 0x6A));
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
            func_8010E15C(D_800E8008, a, H(a, 0x6A));
            break;
        }
        case 3:
            a[1] = 2;
            H(a, 0xB8) = 0x1000;
            H(a, 0xBA) = 0x1000;
            H(a, 0xBC) = 0x1000;
            func_8010E15C(D_800E8008, a, H(a, 0x6A));
            break;
        case 4:
        case 6:
            if (a[6] == 6) {
                func_8010E15C(D_800E8008, a, H(a, 0x6A));
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
            func_8010E63C(a);
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
            func_8010E63C(a);
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

extern u8 *D_1F800260;
extern u16 D_1F8001A0;
extern u16 D_1F8001A2;
void func_80110B38(u8 *a)
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
extern u8 D_8011AEF0[];
extern s16 D_8011D770[];
extern s32 D_8011F06C[];
void func_8010E380();
void func_80110D4C(u8 *a)
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
            *(void **)(e + 0x1C) = func_8010E380;
        }
        *(u8 **)(a + 0x14) = e;
        a[6]++;
        break;
    case 1:
        if (D_800BF80F == 0) {
            a[6]++;
            pl[6] = 0;
            func_8004D604(D_8011F06C[D_800BF870.unk0 - 10], 1);
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
            func_8006CBD0(D_800E8008, D_8011AEF0);
            t = &D_8011D770[H(a, 0x6A) * 3];
            U(a, 0x2E) = t[0];
            U(a, 0x32) = t[1];
            U(a, 0x36) = t[2];
            H(a, 0x6A)++;
            func_8006E1C0(7);
        }
        break;
    }
}

extern u8 *D_1F800254;
s32 func_80111044(u8 *a)
{
    u8 *p;

    switch (a[0x78]) {
    case 0:
        p = D_1F800254;
        p[5] = 0;
        p[4] = 2;
        a[0x47] = 0;
        a[0x1A] = 0x10;
        a[0x19] = 0x10;
        a[0x18] = 0x10;
        a[0xD] |= 2;
        func_80041768(a, 2, 6);
        func_80074590(0x81, 0, 0);
        a[0x78]++;
        break;
    case 1:
        a[0x18] += 8;
        if ((s8)a[0x18] < 0) {
            func_80041768(a, 4, 4);
            a[0x18] = 0x80;
            a[0xD] &= 0xFD;
            a[0x78]++;
        }
        a[0x1A] = a[0x18];
        break;
    case 2:
        if (a[0x79] == 1) {
            func_80041768(a, 0, 4);
            return 1;
        }
        break;
    }
    return 0;
}

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_80111184);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_801112B4);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", f_UpdateLastEvilPigCopiedWeaponAttack);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", f_UpdateLastEvilPigRepeatedChargeAttack);

extern s16 D_1F800264;
extern u8 D_800BF808_1760[];
extern u8 D_800ECF58_742e[];
extern u8 D_8011F198[];
extern u8 D_8011F09C[];
extern u8 D_80129AD4[];
extern u8 D_8002AB5C[];
void func_80110B38();
void func_8011290C();
static inline void set_state(u8 *a, void *fn)
{
    *(void **)(a + 0x1C) = fn;
    a[0x7B] = 0;
    a[5] = 0;
    func_80041718(a, 0, 0);
}
void func_801123F0(u8 *a)
{
    u8 *pl = D_800E7E80;
    u8 *t;
    u8 *p;

    switch (a[4]) {
    case 0:
        switch (a[5]) {
        case 0:
            t = D_800ECF58_742e;
            if (func_800519E0(a, 0x13, *(void **)(t + 0x48), D_8011F198) != 0) {
                break;
            }
            D_1F800264 = 9;
            (&D_1F800264)[1] = 0;
            H(a, 0xB8) = 0xC00;
            H(a, 0xBA) = 0xC00;
            H(a, 0xBC) = 0xC00;
            H(a, 0x80) = 0x46;
            H(a, 0x82) = 0x8C;
            H(a, 0x84) = 0x8C;
            H(a, 0x86) = 0xF0;
            a[0x1B] = 0;
            H(a, 0x58) = 0;
            H(a, 0x56) = 0;
            H(a, 0x54) = 0;
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
                *(void **)(p + 0x1C) = func_80110B38;
                p[0xB] = 0x20;
                *(u8 **)(p + 0x10) = a;
                *(void **)(p + 0x18) = D_8002AB5C;
                p[0x28] |= 0x80;
            }
            *(void **)(a + 0x3C) = *(void **)(t + 0x4C);
            D_1F80024C_2bfb = a;
            if (D_800BFA1A & 0x20) {
                *(void **)(a + 0x7C) = D_80129AD4;
                a[5]++;
                break;
            }
            a[0] = 8;
            a[0xBE] = 0;
            func_80040CDC(a, D_80129AD4, D_8011F09C);
            set_state(a, func_8011290C);
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
            H(a, 0x6E) = 5;
            a[0x2A] = 0;
            func_80041718(a, 0, 0);
            a[0] = 2;
            H(a, 0x56) = func_800782B0(a + 0x2C, D_1F800160_71b4, D_1F800164_d75f);
            break;
        }
        break;
    case 1:
        a[1] = 1;
        H(a, 0x80) = 0x46;
        H(a, 0x82) = 0x8C;
        H(a, 0x84) = 0x8C;
        H(a, 0x86) = 0xF0;
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
                    func_8010E63C(a);
                    if (func_8010E550(a) != 0) {
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
                func_8010EDF8(a);
                break;
            case 2:
                func_8010F48C(a);
                break;
            case 3:
                func_8010FCF0(a);
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
                f_UpdateLastEvilPigCopiedWeaponAttack(a);
                break;
            case 6:
                f_UpdateLastEvilPigRepeatedChargeAttack(a);
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
        if (H(a, 0x6E) >= 3) {
            if (D_1F800264 != 9) {
                D_1F800264 = 9;
                func_80051B04(*(void **)(a + 0xE4), 0x12, 9);
            }
        }
        func_8010FE34(a, pl);
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

void func_801123F0();
void func_8011290C(u8 *a)
{
    s16 *t;

    switch (a[5]) {
    case 0:
        func_80110D4C(a);
        break;
    case 1:
        if (H(a, 0x6A) != -1) {
            func_8006CBD0(D_800E8008, D_8011AEF0 + H(a, 0x6A) * 12);
            t = &D_8011D770[H(a, 0x6A) * 3];
            U(a, 0x2E) = t[0];
            U(a, 0x32) = t[1];
            U(a, 0x36) = t[2];
            H(a, 0x6A)++;
            if (*(s16 *)(D_8011AEF0 + H(a, 0x6A) * 12) == 0) {
                H(a, 0x6A) = -1;
            }
        }
        switch (a[6]) {
        case 0:
            a[1] = 1;
            D_1F800254 = func_8003116C(0x1003, a + 0x2C, 0);
            a[6]++;
        case 1:
        {
            u8 *p = D_1F800254;
            U(p, 0x2C) = U(a, 0x2E);
            U(p, 0x2E) = U(a, 0x32);
            U(p, 0x30) = U(a, 0x36);
            a[1] = 1;
            H(a, 0x56) = func_800782B0(a + 0x2C, D_1F800160_71b4, D_1F800164_d75f);
            if (H(a, 0x6A) == -1) {
                a[0x47] = 1;
                a[0x70] = 2;
                a[6]++;
            }
            break;
        }
        case 2:
            a[1] = a[0x47];
            func_80041098(a);
            if ((s8)a[0x70] <= 0) {
                a[6]++;
            }
            break;
        case 3:
        {
            u8 *g;
            a[0] = 1;
            *(void **)(a + 0x1C) = func_801123F0;
            a[5] = 1;
            a[6] = 0;
            func_8006E1E4();
            func_80042310();
            g = (u8 *)&D_800BF870;
            H(a, 0x58) = 0;
            g[0x1AA] |= 0x20;
            break;
        }
        }
        if (a[1] == 0) {
            a[1] = 1;
            func_80077E7C(a);
            func_8004190C(a);
            func_800518FC(a);
        }
        break;
    }
}

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

#define W_211f(p, o) (*(u32 *)((u8 *)(p) + (o)))
typedef struct { u8 v[6][4]; } Tab64;
extern Tab64 D_801091F8;
void func_80113068(u8 *a)
{
    Tab64 t = D_801091F8;
    u32 r, h;

    switch (a[4]) {
    case 0:
        a[4] = 1;
        a[6] = 0xA;
        a[5] = 0;
        a[7] = 0;
        *(s16 *)(a + 0x32) = -0xC8;
    case 1:
    case 2:
        if (a[4] == 1) {
            r = func_8009A450() & 0x3F;
            h = r >> 1;
            switch (a[5]) {
            case 0:
                if (--a[6] == 0xFF) {
                    a[5] = 1;
                    a[6] = 0xA;
                }
                break;
            case 1:
                if (--a[6] == 0xFF) {
                    a[4] = 2;
                }
                break;
            }
            W_211f(a, 0x60) = h + 0x200;
            W_211f(a, 0x64) = r + 0x300;
            W_211f(a, 0x68) = r + 0x300;
            W_211f(a, 0x6C) = h + 0x200;
        } else {
            W_211f(a, 0x60) -= W_211f(a, 0x60) >> 2;
            W_211f(a, 0x64) -= W_211f(a, 0x64) >> 2;
            W_211f(a, 0x68) -= W_211f(a, 0x68) >> 2;
            W_211f(a, 0x6C) -= W_211f(a, 0x6C) >> 2;
            if (W_211f(a, 0x6C) < 9) {
                a[4] = 3;
            }
            if (++a[7] >= 6) {
                a[7] = 0;
            }
        }
        W_211f(a, 0x50) = (W_211f(a, 0x60) * t.v[a[7]][0]) >> 4;
        W_211f(a, 0x54) = (W_211f(a, 0x64) * t.v[a[7]][1]) >> 4;
        W_211f(a, 0x58) = (W_211f(a, 0x68) * t.v[a[7]][2]) >> 4;
        W_211f(a, 0x5C) = (W_211f(a, 0x6C) * t.v[a[7]][3]) >> 4;
        a[1] = 1;
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

extern s16 D_80129854[];
extern s32 D_80129954[];
void func_80113330(void)
{
    s16 *p = D_80129854;
    s32 *c = D_80129954;
    u32 seed = 0xEDCBA987;
    s32 pad[2];
    s32 i;
    s32 r, a, b, col, y, x, z;

    for (i = 0; i < 0x20; i++) {
        {
            s32 rs_t = (seed & 0xFF) + 0x40;
            r = rs_t;
        }
        seed = seed * 0x7D2B89DD + 1;
        a = seed;
        seed = seed * 0x7D2B89DD + 1;
        b = seed;
        seed = seed * 0x7D2B89DD + 1;
        col = (seed & 0x3F) + 0xC0;
        *c = col | (col << 8);
        seed = seed * 0x7D2B89DD + 1;
        y = (func_80083E80(a) * r) >> 12;
        r = (func_80083F50(a) * r) >> 12;
        x = (func_80083E80(b) * r) >> 12;
        z = (func_80083F50(b) * r) >> 12;
        c++;
        p[0] = x;
        p[1] = y;
        p[2] = z;
        p += 4;
    }
}

#define UW(p, o) (*(u32 *)((u8 *)(p) + (o)))
void func_8011348C(u8 *a)
{
    switch (a[4]) {
    case 0:
        a[4] = 1;
        a[5] = 0;
        a[6] = 0;
        W(a, 0x54) = func_8009A450() >> 9;
        W(a, 0x58) = func_8009A450() >> 9;
        W(a, 0x5C) = func_8009A450() >> 9;
    case 1:
    case 2:
        if (a[4] == 1) {
            if ((s8)a[6] >= 0) {
                a[6] += 0x10;
            }
            a[5] += (0x60 - a[5]) >> 4;
            if (a[5] >= 0x40) {
                a[4] = 2;
            }
        } else {
            a[5] += (0x60 - a[5]) >> 4;
            a[6] -= 5;
            if (a[6] < 0xA) {
                a[4] = 3;
                break;
            }
        }
        a[1] = 1;
        H(a, 0x48) += U(a, 0x54);
        H(a, 0x4A) += U(a, 0x58);
        H(a, 0x4C) += U(a, 0x5C);
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

typedef struct { s16 m[3][3]; s32 t[3]; } Mat;
typedef struct { u8 pad[0x3C]; s32 x, y, z; } CamT;
extern Mat D_1F800000_8be2;
extern Mat D_1F8000F8;
extern s32 D_1F800014[];
extern CamT D_1F8000D0_b4b6;
extern s32 D_1F800080_e4a3;
extern u32 *D_800BF544_5fe3;
extern u32 *D_800ED8C8;
extern u32 D_80129954_592f[];
#define gte_SetRotMatrix(r0) __asm__ volatile("lw	$12, 0( %0 );" "lw	$13, 4( %0 );" "ctc2	$12, $0;" "ctc2	$13, $1;" "lw	$12, 8( %0 );" "lw	$13, 12( %0 );" "lw	$14, 16( %0 );" "ctc2	$12, $2;" "ctc2	$13, $3;" "ctc2	$14, $4" : : "r"(r0) : "$12", "$13", "$14")
#define gte_SetTransMatrix(r0) __asm__ volatile("lw	$12, 20( %0 );" "lw	$13, 24( %0 );" "ctc2	$12, $5;" "lw	$14, 28( %0 );" "ctc2	$13, $6;" "ctc2	$14, $7" : : "r"(r0) : "$12", "$13", "$14")
void func_801135EC(u8 *a)
{
    s16 *v = D_80129854;
    u32 *c = D_80129954_592f;
    Mat *m = &D_1F800000_8be2;
    u32 *p = D_800BF544_5fe3;
    s32 *sz = &D_1F800080_e4a3;
    s32 *flg;
    s32 pad[2];
    s32 s[4];
    s32 n;
    u32 *ot;

    s[0] = s[1] = s[2] = a[5] << 6;
    flg = sz;
    func_80085480(a + 0x48, m);
    func_80084520(m, s);
    gte_MulMatrix0(&D_1F8000F8, &D_1F800000_8be2, &D_1F800000_8be2);
    gte_ldv0(a + 0x2C);
    gte_rtv0();
    gte_stlvnl(D_1F800014);
    m->t[0] += D_1F8000D0_b4b6.x;
    m->t[1] += D_1F8000D0_b4b6.y;
    m->t[2] += D_1F8000D0_b4b6.z;
    gte_SetRotMatrix(m);
    gte_SetTransMatrix(m);
    n = a[6] >> 2;
    while (n > 0) {
        gte_ldv0(v);
        gte_rtps();
        gte_stflg(flg);
        if (*flg >= 0) {
            gte_stsz(sz);
            if (*sz > 0) {
                *sz >>= 2;
                if (*sz < 4) {
                    *sz = 4;
                }
                *sz = (*sz >> (*sz >> 10)) + ((*sz >> 10) << 9);
                if ((u32)(*sz - 4) >= 0x7FC) {
                    do {
                        *sz = -1;
                    } while (0);
                }
                gte_stsxy(p + 2);
                p[1] = *c | 0x6A000000;
                do {
                    ot = &D_800ED8C8[*sz];
                } while (0);
                do {
                    p[0] = *ot | 0x02000000;
                } while (0);
                *ot = (u32)p;
                p += 3;
            }
        }
        n--;
        v += 4;
        c++;
    }
    D_800BF544_5fe3 = p;
}

void func_8011394C(u8 *a)
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
extern s32 D_1F800084_9ba3[];
extern s32 D_1F800090[];
extern u8 D_801207CC[];
extern u8 D_80120784[];
extern u8 D_8012086C[];
void func_80113B78(u8 *a)
{
    s32 s;
    u8 *b = a;
    s32 *p = D_1F800084_9ba3;
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
        func_8002847C(D_801207CC, D_8012086C[b[5] >> 1], 0);
        func_8002847C(D_80120784, D_8012086C[b[6] >> 1], 0);
    }
}

typedef struct { u8 *v[6]; } PtrTab6;
typedef struct { u8 b[8][4]; } ByteTab8;
extern PtrTab6 D_80109210;
extern ByteTab8 D_80109228;
extern u8 D_80120760[];
void func_80113C8C(u8 *a)
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
        func_80027768(D_80120760, e[3], 0, 0);
    }
}

extern S8 D_801299D4[];
void func_80113E38(u8 *a)
{
    u8 *t = D_1F80024C_2bfb;
    s32 i;
    H(a, 0x2C) = H(t, 0x2E);
    H(a, 0x2E) = H(t, 0x32);
    H(a, 0x30) = H(t, 0x36);
    switch (a[4]) {
    case 0:
        for (i = 0; i < 0x20; i++) {
            D_801299D4[i].a = H(a, 0x2C);
            D_801299D4[i].b = H(a, 0x2E);
            D_801299D4[i].c = H(a, 0x30);
            D_801299D4[i].d = 0;
        }
        a[4] = 1;
        a[5] = 0;
    case 1:
        if (D_1F800250 == 0) {
            a[4] = 2;
        }
        for (i = 0x1F; i > 0; i--) {
            D_801299D4[i].a = D_801299D4[i - 1].a;
            D_801299D4[i].b = D_801299D4[i - 1].b;
            D_801299D4[i].c = D_801299D4[i - 1].c;
            D_801299D4[i].d = D_801299D4[i - 1].d;
        }
        D_801299D4[0].a = H(a, 0x2C);
        D_801299D4[0].b = H(a, 0x2E);
        D_801299D4[0].c = H(a, 0x30);
        D_801299D4[0].d = 1;
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

extern u8 D_80120880[];
typedef struct { u8 pad[0x48]; s16 r[3]; } RotAct;
void func_801140F4(u8 *a)
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
            *(u8 **)(a + 0x34) = D_80120880;
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
AreaPolyFT4 *func_80114288(AreaPolyFT4 *p, s32 x, s32 y, s32 w, s32 h, s16 c, s16 cy) {
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

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_801143C4);

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
u32 *func_801157CC(u32 *f, u32 *ot, s32 n)
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
u32 *func_80115A70(u32 *f, u32 *ot, s32 n)
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

typedef struct {
    s32 vx, vy;
} T2Pt32;
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
void func_80115FF4(u8 *g, T2Pt32 *p0, T2Pt32 *p1, T2Pt32 *p2)
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

extern u8 *D_800ECF84;
extern s16 D_1F8000F2_a096;
extern s16 D_1F8000F0_7cc6;
void func_80116560(u8 *a)
{
    s32 pad;
    u8 *p = D_800ECF84;
    s32 x, y;

    switch (a[0]) {
    case 0:
        a[0] = 1;
        a[3] = 0;
        *(u16 *)(a + 4) = *(u16 *)(p + 0);
        *(u16 *)(a + 6) = *(u16 *)(p + 2);
        *(u16 *)(a + 8) = *(u16 *)(p + 4);
        *(u16 *)(a + 0xA) = *(u16 *)(p + 6);
        *(u16 *)(a + 0xC) = *(u16 *)(p + 8);
        *(u16 *)(a + 0xE) = *(u16 *)(p + 0xA);
        a[0x10] = p[0xC];
        a[0x11] = p[0xD];
        {
            s32 h = 0x8E8;
            u16 l1;
            u16 l0;
            h = (a[0x11] * h) / 144;
            l1 = *(u16 *)(p + 0xE);
            l0 = *(u16 *)(p + 0x10);
            {
                u8 *b0 = p + 0x14;
                u8 *b1;
                u8 *b2;
                *(u8 **)(a + 0x18) = b0;
                *(u16 *)(a + 0x2C) = 0x280;
                *(u16 *)(a + 0x30) = 0x280;
                b1 = b0 + l0;
                b2 = b1 + l1;
                *(s16 *)(a + 0x2E) = 0x8E8;
                a[0x38] = 1;
                *(u8 **)(a + 0x1C) = b2;
                *(u8 **)(a + 0x14) = b1;
                *(u8 **)(a + 0x34) = *(u8 **)(a + 0x1C);
            }
            *(u16 *)(a + 0x32) = h;
        }
        break;
    case 2: break;
    case 1:
        { s32 k = D_1F8000F2_a096; u16 w = *(u16 *)(a + 0x2C); x = ((w + 0x140) >> 1) - ((k * w) >> 12); }
        while (x < 0) {
            x += *(u16 *)(a + 0x30);
        }
        while (x >= *(u16 *)(a + 0x30)) {
            x -= *(u16 *)(a + 0x30);
        }
        y = ((D_1F8000F0_7cc6 * *(u16 *)(a + 0x2E)) >> 12) + a[0x11] * 8;
        while (y < 0) {
            y += *(u16 *)(a + 0x32);
        }
        while (y >= *(u16 *)(a + 0x32)) {
            y -= *(u16 *)(a + 0x32);
        }
        if (--*(s8 *)(a + 0x38) <= 0) {
            a[3] = 1;
        }
        *(s16 *)(a + 0x28) = x;
        *(s16 *)(a + 0x2A) = y;
        break;
    }
}

typedef struct {
    u32 tag;
    u32 rgbc;
    u32 xy;
    u16 uv;
    u16 clut;
} T2Sprt16;
extern T2Sprt16 *D_800BF544_e6cf;
void func_80116778(u8 *a)
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
    last->tag = (last->tag & 0xFF000000) | D_800ED8C8[0x7FF];
    func_80083DE0(p, 0, 0, U(a, 4), 0);
    p->tag = (u32)start | 0x02000000;
    q = p;
    p = (T2Sprt16 *)((u32 *)p + 3);
    *(T2Sprt16 **)&D_800ED8C8[0x7FF] = q;
    D_800BF544_e6cf = p;
}

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_80116ABC);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_80116C2C);

typedef struct { s16 x0, x1, z0, z1; } Box6E5C;
#define P(p, o) (*(u8 **)((u8 *)(p) + (o)))
extern s16 D_1F800160_6e5c;
extern Box6E5C D_8012096C[];
static inline void Decay6E5C(s16 *q)
{
    if (q[1] > 0) {
        q[2] += 0x88;
        if (--q[1] > 0) {
            return;
        }
    }
    q[1] = 0;
}
static inline void Wave6E5C(u8 *a)
{
    s16 *q = (s16 *)(a + 0x60);

    H(a, 0x32) = H(a, 0x60) + ((func_80083E80(q[2]) * q[1]) >> 12);
}
static inline void Parts6E5C(u8 *a, s16 v)
{
    s16 t;

    H(P(a, 0xC0), 0xC) = v;
    H(P(a, 0xC4), 0xC) = v;
    t = -(v * 3) >> 1;
    H(P(a, 0xC8), 0xC) = t;
    H(P(a, 0xCC), 0xC) = t;
}
void func_80116E5C(u8 *a)
{
    u8 *b;
    s16 *p;
    Box6E5C *r;

    p = (s16 *)(a + 0x60);
    b = D_800E7E80;
    switch (a[5]) {
    case 0:
        if (a[0x29] != 0) {
            goto c2;
        }
        {
            s16 *q = (s16 *)(a + 0x60);

            Decay6E5C(q);
            Wave6E5C(a);
            if (q[1] == 0) {
                a[5] = 1;
                a[6] = 0;
                H(a, 0x42) = 0x400;
            }
        }
        break;
    case 1:
        if (a[0x29] != 0) {
            goto c2;
        }
        if (a[0x2B] != 0) {
            if (D_1F800160_6e5c < H(a, 0x2E)) {
                H(a, 0x44) = -0x200;
            } else {
                H(a, 0x44) = 0x200;
            }
            a[5] = 8;
            a[0x29] = 0;
        } else {
            p[2] += 0x33;
            p[1] = (u32)func_80083F50(H(a, 0x42)) >> 7;
            H(a, 0x42) += 0x22 + (func_8009A450() >> 9);
        }
        Wave6E5C(a);
        break;
    case 2:
    c2:
        p[2] = 0x200;
        H(a, 0x62) = 0x32;
        H(a, 0x42) = 0;
        a[5] = 3;
    case 3:
        Decay6E5C((s16 *)(a + 0x60));
        Wave6E5C(a);
        if (a[0x29] == 0) {
            a[5] = 7;
            break;
        }
        H(a, 0x44) = U(b, 0x44);
        if (b[0x147] != 0) {
            Parts6E5C(a, -H(b, 0x58));
        } else {
            u16 v = U(b, 0x58);
            s16 t = -(H(b, 0x58) * 3) >> 1;

            H(P(a, 0xC0), 0xC) = v;
            H(P(a, 0xC4), 0xC) = v;
            H(P(a, 0xC8), 0xC) = t;
            H(P(a, 0xCC), 0xC) = t;
        }
        if (b[0x168] >= 3) {
            a[5] = 4;
        }
        break;
    case 4:
        a[5] = 5;
    case 5:
        if (a[0x29] == 0) {
            a[5] = 7;
            break;
        }
        H(a, 0x44) = U(b, 0x44);
        r = &D_8012096C[a[3]];
        if (b[0x147] == 0) {
            H(a, 0x2E) += (func_80083F50(H(a, 0x56)) * (b[0x168] - 2) * 6) >> 12;
            H(a, 0x36) += (func_80083E80(H(a, 0x56)) * (b[0x168] - 2) * 6) >> 12;
            p[2] = U(b, 0x58);
        } else {
            H(a, 0x2E) -= (func_80083F50(H(a, 0x56)) * (b[0x168] - 2) * 6) >> 12;
            H(a, 0x36) -= (func_80083E80(H(a, 0x56)) * (b[0x168] - 2) * 6) >> 12;
            p[2] = -U(b, 0x58);
        }
        if (H(a, 0x2E) < r->x0) {
            H(a, 0x2E) = r->x0;
        } else if (H(a, 0x2E) > r->x1) {
            H(a, 0x2E) = r->x1;
        }
        if (H(a, 0x36) < r->z0) {
            H(a, 0x36) = r->z0;
        } else if (H(a, 0x36) > r->z1) {
            H(a, 0x36) = r->z1;
        }
        if (b[0x168] < 3) {
            a[5] = 3;
        }
        if (b[0x147] != 0) {
            Parts6E5C(a, -H(b, 0x58));
        } else {
            u16 v = U(b, 0x58);
            s16 t = -(H(b, 0x58) * 3) >> 1;

            H(P(a, 0xC0), 0xC) = v;
            H(P(a, 0xC4), 0xC) = v;
            H(P(a, 0xC8), 0xC) = t;
            H(P(a, 0xCC), 0xC) = t;
        }
        {
            s16 *q = (s16 *)(a + 0x60);

            q[1] = 0x32;
        }
        Wave6E5C(a);
        break;
    case 6:
        break;
    case 7:
        a[5] = 8;
        if (b[0x147] != 0) {
            H(a, 0x44) = -H(a, 0x44);
        }
    case 8:
        Decay6E5C((s16 *)(a + 0x60));
        Wave6E5C(a);
        if (a[0x29] != 0) {
            a[5] = 2;
            a[0x2B] = 0;
            break;
        }
        {
            s16 ang;
            s16 spd;

            ang = H(P(a, 0xC0), 0xC);
            spd = H(a, 0x44);
            ang &= 0xFFF;
            if (spd > 0) {
                spd -= 10;
                if (spd < 0) {
                    spd = 0;
                }
            } else {
                spd += 10;
                if (spd > 0) {
                    spd = 0;
                }
            }
            if (ang > 0x800) {
                ang += spd;
                if (ang < 0x1000) {
                    if (spd < 0x96) {
                        spd += 0x1E;
                    }
                    goto store;
                }
            } else {
                ang += spd;
                if (ang > 0) {
                    goto dec;
                }
            }
            if (__builtin_abs(spd) < 0x5A) {
                ang = 0;
                spd = 0;
                a[5] = 0;
                a[0x2B] = 0;
            }
            goto store;
        dec:
            if (spd > -0x96) {
                spd -= 0x1E;
            }
        store:
            H(a, 0x44) = spd;
            Parts6E5C(a, ang);
        }
        break;
    }
}

void func_801175B8(void) {
}

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_801175C0);

extern AreaSVec D_1F8000C0_f4ad;
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

extern s16 D_800ED098;
extern s16 D_80120998;
typedef struct {
    s16 f0, f2, f4, f6, f8, fA, fC, pad0E[2], f12, pad14, f16;
    u8 pad18[0x22];
    s16 f3A;
    u8 pad3C[4];
    s32 f40;
} Sub;
void func_80117A64(u8 *a)
{
    s16 t;
    a[8] = 1;
    if (D_800ED098 <= 0) {
        a[4] = 3;
        return;
    }
    t = 1;
    a[9] = t;
    a[0] = t;
    a[0xB] = 2;
    H(a, 0x60) = 0xA;
    H(a, 0x62) = 0x3FEB;
    H(a, 0x64) = -0x1C00;
    H(a, 0x66) = -0x1BF1;
    H(a, 0x68) = -0xC00;
    H(a, 0x6A) = -0xBF1;
    a[0x29] = 0;
    a[0x2B] = 0;
    a[0x5E] = 0;
    a[0xBF] = 0;
    H(a, 0x6C) = 0x50;
    H(a, 0x6E) = 0;
    H(a, 0x7C) = 0;
    H(a, 0x7E) = 0;
    H(a, 0x7A) = 0;
    a[4]++;
    *(Sub **)(a + 0xC0) = func_8007AAE8();
    (*(Sub **)(a + 0xC0))->f6 = -1;
    (*(Sub **)(a + 0xC0))->f0 = 0;
    (*(Sub **)(a + 0xC0))->f4 = 0;
    (*(Sub **)(a + 0xC0))->f8 = 0;
    (*(Sub **)(a + 0xC0))->fA = 0;
    (*(Sub **)(a + 0xC0))->fC = 0;
    (*(Sub **)(a + 0xC0))->f40 = 0;
    H(a, 0x88) = D_80120998;
    H(a, 0x8A) = (&D_80120998)[1];
    H(a, 0x8C) = (&D_80120998)[2];
    H(a, 0x54) = (&D_80120998)[3];
    H(a, 0x56) = (&D_80120998)[4];
    H(a, 0x58) = (&D_80120998)[5];
    (*(Sub **)(a + 0xC0))->f3A = (&D_80120998)[6];
    H(a, 0x80) = (&D_80120998)[7];
    H(a, 0x82) = (&D_80120998)[8];
    H(a, 0x84) = (&D_80120998)[9];
    H(a, 0x86) = (&D_80120998)[10];
    (*(Sub **)(a + 0xC0))->f2 = 0x140;
    H(a, 0x4A) = 0;
    H(a, 0x50) = 0x200;
    (*(Sub **)(a + 0xC0))->f16 = (*(Sub **)(a + 0xC0))->f3A;
    (*(Sub **)(a + 0xC0))->f12 = 0;
    t = (*(Sub **)(a + 0xC0))->f2;
    a[0x47] = 3;
    H(a, 0x78) = t;
    H(a, 0x32) -= (*(Sub **)(a + 0xC0))->f3A;
    H(a, 0x56) = -D_1F8000F2;
    func_800517F8(a);
}

void func_80117C70(u8 *a)
{
    s32 n;
    s32 x;

    switch (a[4]) {
    case 0:
        func_80117A64(a);
        break;
    case 1:
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
            x = (*(u16 *)(a + 0x7C) + 0x1E0) & 0xFFF;
            *(s16 *)(a + 0x7C) = x;
            if (x < 0x1E0 && *(s16 *)(a + 0x7E) != 0) {
                *(s16 *)(a + 0x7E) -= 8;
            }
        }
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
        *(s16 *)(a + 0x56) = -D_1F8000F2;
        func_800517F8(a);
        a[1] = 1;
        func_80077EBC(a);
        a[0x2B] = 0;
        break;
    case 2:
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

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

extern u8 D_8011F230[];
extern u8 D_80129EC8[];
extern u8 D_801209E0[];
extern u8 D_1F800236;
void func_80117FA4(u8 *a)
{
    u8 *g;
    u8 *p;
    s16 h;
    s32 k;
    u8 *g_f;
    u8 *g_s9;

    switch (a[4]) {
    case 0:
        g_s9 = D_800ECF58_742e;
        if (func_800519E0(a, 0xF, *(s32 *)(g_s9 + 0x54), D_8011F230) == 0) {
        *(s32 *)(a + 0x3C) = *(s32 *)(g_s9 + 0x58);
        func_80040CDC(a, D_80129EC8, D_801209E0);
        a[0x70] = 2;
        a[0x7B] = 3;
        func_80041718(a, 0xA, 0);
        H(a, 0x80) = 0x32;
        H(a, 0x82) = 0x64;
        H(a, 0x84) = 0xA0;
        H(a, 0x86) = 0x140;
        H(a, 0x2E) = 0x1DC0;
        H(a, 0x32) = -0x354D;
        H(a, 0x36) = 0x15E0;
        a[0] = 3;
        a[0x47] = 0;
        H(a, 0x58) = 0;
        H(a, 0x54) = 0;
        H(a, 0x56) = 0x400;
        H(a, 0x40) = 0;
        a[4]++;
        }
        break;
    case 1:
        switch (a[5]) {
        case 0:
            a[1] = 1;
            func_80041098(a);
            if (a[0x70] == 0xFF) {
                a[5]++;
            }
            if (a[0x47] != 0) {
                p = D_800E8008;
                H(p, 0x3A) = H(a, 0x4E);
                H(p, 0x3E) = H(a, 0x50);
                H(p, 0x42) = H(a, 0x52);
                switch (a[0x47]) {
                case 1:
                    k = 7;
                    break;
                case 2:
                    k = 0x1F;
                    break;
                default:
                    k = 0;
                    a[0x47] = 0;
                    break;
                }
                h = (s16)k >> 1;
                if ((s16)k != 0) {
                    H(p, 0x3A) += h - (k & func_8009A450());
                    H(p, 0x3E) += h - (k & func_8009A450());
                    H(p, 0x42) += h - (k & func_8009A450());
                }
            }
            break;
        case 1:
            D_1F800236 = 7;
            g = D_800BF808_1760;
            g[0x31] = 1;
            H(g, 0x32) = 0x1500;
            g_f = (u8 *)&D_800BF870;
            H(g_f, 0x2E) = 0;
            g_f[0x1F] = 0;
            a[4] = 3;
            break;
        }
        func_8004190C(a);
        if (a[1] != 0) {
            func_800518FC(a);
        }
        break;
    case 2:
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

s32 func_80118250(void *arg0) {
    M2C_FIELD(arg0, u8 *, 0x47) = (u8) M2C_FIELD(arg0, u8 *, 0x72);
    return 1;
}

typedef struct { u8 pad[0xC0]; u8 *parts[1]; } PartsOwner;
s32 func_80118264(u8 *a)
{
    s32 e;
    s32 i;
    switch (a[0x78]) {
    case 0:
        e = func_8003116C(0x1005, a + 0x2C, -10);
        if (e != 0) {
            func_80074590(0x84, 0x18, 0);
            *(s32 *)(a + 0x10) = e;
            *(s16 *)(a + 0x40) = 0;
            a[0x78]++;
        }
        break;
    case 1:
        if (++*(s16 *)(a + 0x40) >= 10) {
            for (i = 0; i < a[9]; i++) {
                func_80051B04(((PartsOwner *)a)->parts[i], 0x14, i);
            }
            *(s16 *)(a + 0x56) = 0x60E;
            func_80041718(a, 6, 0);
            return 1;
        }
        return 0;
    }
    return 0;
}

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

/* extern */
M2C_UNK func_80041098(void *);
/* extern */
M2C_UNK func_80041718(void *, M2C_UNK, M2C_UNK);
/* extern */
M2C_UNK func_8004190C(void *);
/* extern */
M2C_UNK func_800518FC(void *);
/* extern */
s32 func_800519E0(void *, M2C_UNK, s32, M2C_UNK *);
/* extern */
M2C_UNK func_8007A624(void *);
/* extern */
extern M2C_UNK D_8001B354;
extern M2C_UNK D_800A43E8;
extern M2C_UNK D_800ECF58_6b74;
extern M2C_UNK D_80120C20;
void func_801183C8(u8 *a)
{
    u8 *g;

    switch (a[4]) {
    case 0:
        g = (u8 *)&D_800ECF58_6b74;
        if (func_800519E0(a, 0x12, *(s32 *)(g + 0x14), &D_800A43E8) == 0) {
            *(s32 *)(a + 0x3C) = (s32) *(s32 *)(g + 0x18);
            M2C_FIELD(a, M2C_UNK **, 0x7C) = &D_8001B354;
            *(s8 *)(a + 0x7B) = 0;
            func_80041718(a, 0, 0);
            func_80040CDC(a, &D_8001B354, &D_80120C20);
            a[0x70] = 2U;
            *(s16 *)(a + 0x2E) = 0x1AE0;
            *(s16 *)(a + 0x32) = -0x354D;
            *(s16 *)(a + 0x36) = 0x1370;
            *(s16 *)(a + 0x58) = 0;
            *(s16 *)(a + 0x54) = 0;
            *(s16 *)(a + 0x56) = 0xDBC;
            a[4]++;
            return;
        }
        break;
    case 1:
        if (a[5] == 0) {
            a[1] = 1;
            func_80041098(a);
            if (a[0x70] == 0xFF) {
                a[4] = 3U;
            }
        }
        func_8004190C(a);
        if (a[1] != 0) {
            func_800518FC(a);
            return;
        }
        break;
    case 2:
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

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

extern s16 D_801289B8[];
void func_80118588(u16 *a, s16 *v)
{
    s32 i;
    s32 n = a[0];
    s16 *t;
    s16 *s;
    s16 *d = (s16 *)a;
    if (n == 0) return;
    t = D_801289B8;
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

extern u8 *D_80121BE8[];
extern u8 *D_8012297C[];
extern u8 *D_80124480[];
extern u8 *D_801274C4[];
extern u8 *D_80128860[];
extern u8 *D_801289A0[];
#define EP_FRAME(a) (*(s16 *)((a) + 0x64))
#define EP_MODEL(a) (*(u8 **)(*(u8 **)((a) + 0xC0) + 0x40))
s32 func_8011866C(u8 *a)
{
    switch (a[7]) {
    case 0:
        break;
    case 1:
        func_80118588(EP_MODEL(a), D_80121BE8[EP_FRAME(a)]);
        if (++EP_FRAME(a) >= 8) {
            EP_FRAME(a) = 7;
            return 1;
        }
        break;
    case 2:
        func_80118588(EP_MODEL(a), D_8012297C[EP_FRAME(a)]);
        if (++EP_FRAME(a) >= 7) {
            EP_FRAME(a) = 0;
            a[7] = 0;
            return 1;
        }
        break;
    case 3:
        func_80118588(EP_MODEL(a), D_80124480[EP_FRAME(a)]);
        if (++EP_FRAME(a) >= 6) {
            EP_FRAME(a) = 5;
            return 1;
        }
        break;
    case 4:
        func_80118588(EP_MODEL(a), D_80124480[EP_FRAME(a)]);
        if (++EP_FRAME(a) >= 14) {
            EP_FRAME(a) = 13;
            return 1;
        }
        break;
    case 5:
        func_80118588(EP_MODEL(a), D_801289A0[EP_FRAME(a)]);
        if (++EP_FRAME(a) >= 6) {
            EP_FRAME(a) = 5;
            return 1;
        }
        break;
    case 6:
    case 7:
    case 8:
        func_80118588(EP_MODEL(a), D_801274C4[EP_FRAME(a)]);
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
        func_80118588(EP_MODEL(a), D_80128860[EP_FRAME(a)]);
        if (++EP_FRAME(a) >= 10) {
            EP_FRAME(a) = 9;
            return 1;
        }
        break;
    }
    return 0;
}

extern LVec D_1F8000A0;
extern u16 D_800E7ED6;
extern u8 D_80128D24[];
extern void *D_80128DAC[];
extern void *D_80128EE0[];
extern void *D_80128EF4[];
s32 func_80118934(u8 *a)
{
    s32 s;
    void *q;
    u8 *pl;
    u16 r;
    s = a[6];
    switch (s) {
    case 0:
        a[6] = 1;
        func_80040CDC(a, 0, D_80128D24);
        a[0x70] = 1;
        break;
    case 1:
        func_80041098(a);
        if (a[0x70] != 0xFF) {
            return 0;
        }
        a[6]++;
        func_80040CDC(a, 0, D_80128DAC[D_800BF870.unk0 - 10]);
        a[0x70] = 1;
        break;
    case 2:
        func_80041098(a);
        if (a[0x70] != 0xFF) {
            return 0;
        }
        a[6]++;
        if (!(D_800BF870.pad1[0x1A7] & 0x1F)) {
            func_80040CDC(a, 0, D_80128EF4[D_800BF870.unk0 - 10]);
        } else {
            func_80040CDC(a, 0, D_80128EE0[D_800BF870.unk0 - 10]);
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
        func_80084470(D_1F8000D0_8c3c.m, &D_1F8000C0, &D_1F8000A0);
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

extern s16 D_800BF83A;
extern s32 D_80128CE8[];
extern s32 D_80128CFC[];
extern s32 D_80128D10[];
extern u8 D_80128978[];
extern u8 D_80017FC0[];
typedef struct { u8 pad[0x5E6]; u16 f5E6; } GameState5E6;
#define G ((u8 *)&D_800BF870)
void func_80118C98(u8 *a)
{
    s32 one = 1;
    u8 v;
    u8 *g;
    u8 *q;
    s32 k;

    switch (a[4]) {
    case 0:
        if (func_800519E0(a, 5, D_800ECF58[D_80128CE8[D_800BF870.unk0 - 10]], D_80128978) == 0) {
            W(a, 0x3C) = D_800ECF58[D_80128CFC[D_800BF870.unk0 - 10]];
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
            func_8004D4C4(D_80128D10[D_800BF870.unk0 - 10], 1);
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
            if (func_80118934(a) != 0) {
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
            if (func_80118B74(a) != 0) {
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

s32 func_80119058(u8 *a, u8 *b)
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

#define P(p, o) (*(void **)((u8 *)(p) + (o)))
#define P(p, o) (*(u8 **)((u8 *)(p) + (o)))
extern u8 D_1F800259;
extern u8 D_800BF84C;
void func_801192C8(u8 *a)
{
    u8 *b = D_1F80024C_2bfb;
    s32 r, done, x, z, k;
    u16 t;

    switch (a[6]) {
    case 0:
        func_800521F4(0, 0, 0x81, 2);
        func_8011866C(a);
        if (func_80119058(a, b) != 0) {
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
        r = func_8011866C(a);
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
        if (func_8011866C(a) != 0) {
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
        if (func_8011866C(a) != 0) {
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
extern s32 D_80129090[];
extern s32 D_801290A8[];
extern s16 D_801290C0[];
extern u8 D_80128EB0[];
void func_80117FA4();
void func_80118C98();
void func_8011968C(u8 *a)
{
    u8 *e = D_800E7E80;
    u8 *p = D_1F80024C_2bfb;
    s16 *t;
    u8 *r;
    u16 v;
    u16 w;

    switch (a[6]) {
    case 0:
        if (func_8011866C(a) != 0) {
            func_8004D298(D_800BF870.unk0 - 10);
            p[4] = 3;
            H(a, 0x40) = 0x1E;
            a[6]++;
        }
        break;
    case 1:
        if (--H(a, 0x40) == 0) {
            H(a, 0x40) = 0x3C;
            func_8003116C(D_80129090[D_800BF870.unk0 - 10], a + 0x2C, -0x50);
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
            func_80040C00(D_801290C0[D_800BF870.unk0 - 10]);
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
                func_80040CDC(a, 0, D_80128EB0);
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
            func_8003116C(D_801290A8[D_800BF870.unk0 - 10], a + 0x2C, -0x1E);
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
                    W(r, 0x1C) = (s32)func_80118C98;
                    H(r, 0x2E) = U(a, 0x2E);
                    H(r, 0x32) = U(a, 0x32);
                    H(r, 0x36) = U(a, 0x36);
                }
            } else {
                r = func_80072DDC(0, 3, 3, 0x24);
                if (r != NULL) {
                    W(r, 0x1C) = (s32)func_80117FA4;
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

s32 func_80119B64(u8 *a0)
{
    u8 *a = a0;
    Cam *c = &D_1F8000D0_8c3c;
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

extern s16 D_1F800242;
extern u16 D_800E7EB2;
static inline void f9cc0_circle(u8 *a)
{
    H(a, 0x36) = 0x1468;
    H(a, 0x2E) = ((func_80083E80(H(a, 0x76)) * 832) >> 12) + 0x1DC0;
    H(a, 0x76) = (U(a, 0x76) + 0x10) & 0xFFF;
    H(a, 0x62) = (U(a, 0x62) + 8) & 0xFFF;
}
void func_80119CC0(u8 *a)
{
    switch (a[4]) {
    case 0:
        switch (a[5]) {
        case 0:
            if (func_80051B70(a, 0xC, 3) != 0) {
                break;
            }
            H(a, 0x80) = 0x190;
            H(a, 0x82) = 0x320;
            H(a, 0x84) = 0x64;
            H(a, 0x86) = 0xC8;
            H(a, 0x62) = 0x400;
            H(a, 0x78) = 0x340;
            H(a, 0x7A) = 0x1DC0;
            H(a, 0x7C) = -0x2454;
            H(a, 0x32) = -0x2454;
            H(a, 0x76) = 0;
            a[0] = 1;
            a[0x29] = 0;
            H(a, 0x60) = 0;
            H(a, 0x64) = 0;
            H(a, 0x54) = 0;
            H(a, 0x58) = 0;
            H(a, 0x7E) = 0x1468;
            H(a, 0x40) = 0;
            D_1F800248 = a;
            H(a, 0x56) = MEMBER_AT(s16, a, 0x62);
            H(a, 0x2E) = ((func_80083E80(MEMBER_AT(s16, a, 0x76)) * 832) >> 12) + 0x1DC0;
            H(a, 0x36) = 0x1468;
            if (D_800BFA1A & 0x20) {
                a[4]++;
            } else {
                a[5]++;
                H(a, 0x32) -= 0x7D0;
            }
            func_8006CBA8(a + 0x2C);
            break;
        case 1:
            break;
        case 2:
            H(a, 0x32) += 0x10;
            if (H(a, 0x7C) < H(a, 0x32)) {
                H(a, 0x32) = H(a, 0x7C);
                func_8006E1E4();
                a[5]++;
            } else {
                func_8006CBA8(a + 0x2C);
            }
            if (func_8007778C(a) != 0) {
                func_800517F8(a);
            }
            break;
        case 3:
            if (D_1F800137 == 0) {
                a[4] = 1;
                a[5] = 0;
            }
            H(a, 0x32) = U(a, 0x7C) + (func_80083E80(H(a, 0x60)) >> 4);
            H(a, 0x60) = (U(a, 0x60) + 0x40) & 0xFFF;
            if (func_8007778C(a) != 0) {
                func_800517F8(a);
            }
            break;
        }
        break;
    case 1:
        switch (a[5]) {
        case 0:
            f9cc0_circle(a);
            func_8011866C(a);
            if (D_1F800246_6eef == 0) {
                H(a, 0x56) = H(a, 0x62);
            } else {
                a[7] = 1;
                a[5]++;
                H(a, 0x56) = func_800776F8((s16)(func_800782B0(a + 0x2C, D_1F800160_71b4, D_1F800164_d75f) - 0x400), H(a, 0x56), 0x80);
            }
            H(W(a, 0xC0), 8) += 0x40;
            H(W(a, 0xC0), 8) &= 0xFFF;
            H(a, 0x32) = U(a, 0x7C) + (func_80083E80(H(a, 0x60)) >> 4);
            H(a, 0x60) = (U(a, 0x60) + 0x40) & 0xFFF;
            {
                s16 d = D_800E7EB2 - H(a, 0x7C);
                if ((u16)(d + 0x20) > 0x40) {
                    s16 m = __builtin_abs(d);
                    s16 n;
                    if (m > 0x200) {
                        m = 0x200;
                    }
                    if (d < 0) n = -m; else n = m;
                    H(a, 0x7C) += n >> 4;
                } else {
                    H(a, 0x7C) = D_800E7EB2;
                }
            }
            break;
        case 1:
            if (D_800BF841 == 0) {
                f9cc0_circle(a);
            }
            func_8011919C(a);
            break;
        case 2:
            func_801192C8(a);
            break;
        case 3:
            func_8011968C(a);
            break;
        }
        if (a[1] == 0 && func_8007778C(a) != 0) {
            func_80051844(a);
        }
        D_1F800240 = H(a, 0x2E);
        D_1F800242 = H(a, 0x32);
        D_1F800244 = H(a, 0x36);
        break;
    case 2:
    case 3:
        func_8007A624(a);
        break;
    }
}

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

extern Range D_8012971C[];
extern Range D_80129734[];
extern Range D_8012976C[];
extern u8 *D_1F80021C;
void func_8011A35C(s16 kind, s16 idx)
{
    Range *t;
    s32 n, base;
    u8 *p;
    switch (kind) {
    case 0:
        t = D_8012971C;
        n = 3;
        base = 0;
        break;
    case 1:
        t = D_80129734;
        n = 0x1F;
        base = 0x1C8;
        break;
    case 3:
        t = D_8012976C;
        n = 10;
        base = 951;
        break;
    default:
        return;
    }
    p = D_1F80021C + t[idx].a * 32 + base * 32;
    func_8001D2A8(n, p, p + (t[idx].b + 1) * 32, 0);
}

extern s16 D_800BED82;
extern M2C_UNK D_80129134;
void func_8011A428(void) {
    func_80075448(0xA, &D_80129134, 0x10, D_800BED82);
}

s32 func_8011A45C(u8 *a)
{
    u8 *g = D_800E8008;
    u8 s = a[0x78];
    s32 pad[4];

    switch (s) {
    case 0:
        if (!(*(u16 *)(a + 0x72) & 1)) {
            func_8006E1C0(7);
        } else {
            g[0x64] = 7;
        }
        if (*(s16 *)(a + 0x66) == 0) {
            func_8006CBD0(g, *(s32 *)(a + 0x74));
            if (*(s16 *)(a + 0x64) != 0) {
                *(s16 *)(a + 0x4E) = *(s16 *)(g + 0x3A);
                *(s16 *)(a + 0x50) = *(s16 *)(g + 0x3E);
                *(s16 *)(a + 0x52) = *(s16 *)(g + 0x42);
            }
            return 1;
        }
        func_8006CBA8(D_1F8000DC);
        func_8006CC1C(g, *(s32 *)(a + 0x74), *(s16 *)(a + 0x66));
        if (*(s16 *)(a + 0x64) != 0) {
            *(s16 *)(a + 0x4E) = *(s16 *)(g + 0x3A);
            *(s16 *)(a + 0x50) = *(s16 *)(g + 0x3E);
            *(s16 *)(a + 0x52) = *(s16 *)(g + 0x42);
        }
        if (*(s16 *)(a + 0x68) != 0) {
            return 1;
        }
        a[0x78]++;
        break;
    case 1:
        if (*(s16 *)(a + 0x64) != 0) {
            *(s16 *)(g + 0x3A) = *(s16 *)(a + 0x4E);
            *(s16 *)(g + 0x3E) = *(s16 *)(a + 0x50);
            *(s16 *)(g + 0x42) = *(s16 *)(a + 0x52);
        }
        {
            s32 r = func_8006CDCC(g);
            if (*(s16 *)(a + 0x64) != 0) {
                *(s16 *)(a + 0x4E) = *(s16 *)(g + 0x3A);
                *(s16 *)(a + 0x50) = *(s16 *)(g + 0x3E);
                *(s16 *)(a + 0x52) = *(s16 *)(g + 0x42);
            }
            if (r == s) {
                return 1;
            }
        }
        break;
    
    }
    return 0;
}

#define S16(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define U16(p, o) (*(u16 *)((u8 *)(p) + (o)))
s32 func_8011A620(u8 *a)
{
    u8 *g = D_800E7E80;
    u8 *o;
    u16 k;
    s16 n;
    s16 h;
    u8 snd;
    s32 vol;

    o = *(u8 **)(a + 0x6C);
    k = U16(o, 0xA);
    switch (a[0x78]) {
    case 0:
        g[5] = 0x21;
        g[6] = 0;
        n = S16(a, 0x64) >> 8;
        if (n == 0) {
            n = 10;
        }
        S16(a, 0x48) = U16(a, 0x74) - U16(g, 0x2E);
        S16(a, 0x4C) = U16(a, 0x76) - U16(g, 0x36);
        S16(a, 0x64) = (s16)func_80084080(S16(a, 0x4C) * S16(a, 0x4C) + S16(a, 0x48) * S16(a, 0x48)) / n;
        if (S16(a, 0x64) == 0) {
            S16(a, 0x64) = 1;
        }
        S16(a, 0x64) = 0x1000 / S16(a, 0x64);
        S16(a, 0x44) = 0x1000;
        n = k;
        if (n == -1) {
            S16(g, 0x56) = func_80085690(-S16(a, 0x4C), S16(a, 0x48)) & 0xFFF;
        } else if (n == 0) {
            a[0x78] = 2;
            return 0;
        }
        S16(a, 0x66) = func_80085690(-S16(a, 0x4C), S16(a, 0x48)) & 0xFFF;
        a[0x78]++;
    case 1:
        if (func_80041438(g, S16(a, 0x66), 0x100) != 0) {
            a[0x78]++;
        }
        if ((s16)k == 1) {
            return 0;
        }
    case 2:
        func_80054D14(g, U16(a, 0x72) & 0xFFF, 4);
        S16(a, 0x44) -= U16(a, 0x64);
        if (S16(a, 0x44) <= 0) {
            S16(a, 0x44) = 0;
        }
        S16(g, 0x2E) = U16(o, 4) - S16(a, 0x44) * S16(a, 0x48) / 0x1000;
        S16(g, 0x36) = U16(o, 6) - S16(a, 0x44) * S16(a, 0x4C) / 0x1000;
        if (S16(a, 0x44) == 0) {
            if (!(S16(a, 0x72) & 0x8000)) {
                func_80054DAC(g, 2, 4);
            }
            return 1;
        }
        h = S16(a, 0x68);
        if (h != 0) {
            snd = S16(a, 0x6A);
            vol = (S16(a, 0x6A) & 0xFF00) >> 8;
            if (h & 0x3F) {
                if (!(D_1F80017C & h)) {
                    func_80074590(snd, 0, (s8)vol);
                }
            } else if (h & 0x80) {
                if ((*(u8 **)(g + 0x38))[4] != 0) {
                    if (!(h & 0x40)) {
                        S16(a, 0x68) = h | 0x40;
                        func_80074590(snd, 0, (s8)vol);
                    }
                } else {
                    S16(a, 0x68) = h & 0xFFBF;
                }
            }
        }
        break;
    }
    return 0;
}

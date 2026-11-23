#include "common.h"
#include "game.h"
#include "m2c.h"
#include "gte.h"

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_0x8010a32c);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8010A530);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8010A704);

extern u8 D_1F800137;
extern u8 D_800BF808[];
void func_8010A7FC(void)
{
    u8 *s;

    D_1F800137 = 2;
    s = D_800BF808;
    s[7] = 2;
    s[5] = 3;
    s[0x31] = 0;
}

void func_8010A824(void)
{
    u8 *s;

    D_1F800137 = 2;
    s = D_800BF808;
    s[7] = 2;
    s[0x31] = 3;
    s[5] = 0;
    *(s16 *)(s + 0x32) = 0x502;
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8010A854);

extern s32 D_1F80009C_baed;
s32 func_8010AA70(u8 *a, u8 *b)
{
    s32 r = func_8001F40C(a, b, 1);
    s32 x, z;

    if (r < 0) {
        return 0;
    }
    func_8001FF7C(a, b, r, 1);
    if (*(u16 *)(a + 0x17E) & 0x200) {
        return 0;
    }
    x = (func_80083F50(D_1F80009C_baed) * (M2C_FIELD(a, s16 *, 0x80) + M2C_FIELD(b, s16 *, 0x80))) >> 0xC;
    z = (func_80083E80(D_1F80009C_baed) * (M2C_FIELD(a, s16 *, 0x80) + M2C_FIELD(b, s16 *, 0x80))) >> 0xC;
    if (b[0x5F] == 0) {
        M2C_FIELD(b, u16 *, 0x2E) = M2C_FIELD(a, u16 *, 0x2E) - x;
        M2C_FIELD(b, u16 *, 0x36) = M2C_FIELD(a, u16 *, 0x36) + z;
    } else if (!(a[0] & 4)) {
        M2C_FIELD(a, u16 *, 0x2E) = M2C_FIELD(b, u16 *, 0x2E) + x;
        M2C_FIELD(a, u16 *, 0x36) = M2C_FIELD(b, u16 *, 0x36) - z;
    }
    a[0x2B] = D_1F80009C_baed >> 4;
    return 1;
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8010ABA0);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8010AD64);

#define F16(p, o) M2C_FIELD(p, s16 *, o)
#define FU16(p, o) M2C_FIELD(p, u16 *, o)
static inline void land_inl(u8 *p, s32 y)
{
    M2C_FIELD(p, s32 *, 0x30) = y << 16;
    func_80022C78(p);
}
s32 func_8010AF84(u8 *a, u8 *b) {
    s16 dx, dz, dy, e, f;
    u16 h, bh, ah;
    u16 r;
    s32 ang, s, k, m1, t1, m2, t2, m3, t3;

    dx = FU16(a, 0x2E) - FU16(b, 0x2E);
    dz = FU16(a, 0x36) - FU16(b, 0x36);
    r = func_80084080(dx * dx + dz * dz);
    if (r > F16(a, 0x80) + F16(b, 0x80)) {
        return -1;
    }
    dy = FU16(a, 0x32) - FU16(b, 0x32);
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
    D_1F80009C_baed = ang;
    if (b[0x29] & 1) {
        if (!(a[0] & 4)) {
            m1 = (func_80083F50(ang) * (F16(a, 0x80) + F16(b, 0x80))) >> 12;
            t1 = func_80083E80(D_1F80009C_baed) * (F16(a, 0x80) + F16(b, 0x80));
            F16(a, 0x2E) = FU16(b, 0x2E) + m1;
            F16(a, 0x36) = FU16(b, 0x36) - (t1 >> 12);
        }
        if (e - dy >= 0x92) {
            a[0x60] = 1;
        }
        a[0x5F] = func_80077768((s16)D_1F80009C_baed, F16(a, 0x140), 1) + 2;
        return 1;
    }
    if (f < 0 && e - dy < 0x18) {
        if (a[0x145] & 1) {
            goto fail;
        }
        b[0x29] |= 1;
        land_inl(a, F16(b, 0x32) + f);
        return 2;
    }
    s = F16(a, 0x80) + F16(b, 0x80) - (s16)r;
    k = e - dy;
    if (s < k) {
        if (!(a[0] & 4)) {
            m2 = (func_80083F50(D_1F80009C_baed) * (F16(a, 0x80) + F16(b, 0x80))) >> 12;
            t2 = func_80083E80(D_1F80009C_baed) * (F16(a, 0x80) + F16(b, 0x80));
            F16(a, 0x2E) = FU16(b, 0x2E) + m2;
            F16(a, 0x36) = FU16(b, 0x36) - (t2 >> 12);
        }
        if (k >= 0x92) {
            a[0x60] = 1;
        }
        a[0x5F] = func_80077768((s16)D_1F80009C_baed, F16(a, 0x140), 1) + 2;
        return 1;
    }
    if (f <= 0) {
        if (a[0x145] & 1) {
            goto fail;
        }
        if (b[0x29] & 1) {
            goto fail;
        }
        b[0x29] |= 1;
        land_inl(a, F16(b, 0x32) + f);
        return 2;
    }
    if (!(b[0x29] & 0x80) && a[0x78] == 0 && a[0x164] == 0 && F16(a, 0x44) != 0) {
        if (F16(a, 0x44) >= 0) {
            D_1F80009C_baed = F16(a, 0x140) + 0x800;
        } else {
            D_1F80009C_baed = F16(a, 0x140);
        }
    }
    if (!(a[0] & 4)) {
        m3 = (func_80083F50(D_1F80009C_baed) * (F16(a, 0x80) + F16(b, 0x80))) >> 12;
        t3 = func_80083E80(D_1F80009C_baed) * (F16(a, 0x80) + F16(b, 0x80));
        F16(a, 0x2E) = FU16(b, 0x2E) + m3;
        F16(a, 0x36) = FU16(b, 0x36) - (t3 >> 12);
    }
    return 3;
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8010B424);

void func_8010B5E8(u8 *a, u8 *b)
{
    s32 temp_lo;
    s32 temp_s1;
    s32 temp_v0;
    u16 temp_v1;

    temp_v1 = *(u16 *)(a + 0x17E);
    if (!(temp_v1 & 0x200)) {
        if (temp_v1 & 0x8000) {
            func_8001F054(a, b);
            return;
        }
        temp_v0 = func_8001F40C(a, b, 0);
        if (temp_v0 >= 0) {
            if ((a[0x144] == 1) && (temp_v0 < 2)) {
                func_8001FDB4(b, -0x7FFC, 0x10, 0x1E);
                return;
            }
            temp_s1 = (s32) (func_80083F50(D_1F80009C_baed) * (M2C_FIELD(a, s16 *, 0x80) + M2C_FIELD(b, s16 *, 0x80))) >> 0xC;
            temp_lo = func_80083E80(D_1F80009C_baed) * (M2C_FIELD(a, s16 *, 0x80) + M2C_FIELD(b, s16 *, 0x80));
            M2C_FIELD(a, s16 *, 0x2E) = (s16) (M2C_FIELD(b, u16 *, 0x2E) + temp_s1);
            MEMBER_AT(s16, a, 0x36) = (s16) (M2C_FIELD(b, u16 *, 0x36) - (temp_lo >> 0xC));
            a[0x60] = 1;
            a[0x5F] = func_80077768((s16)D_1F80009C_baed, *(s16 *)(a + 0x140), 1) + 2;
        }
    }
}

extern u8 D_800BF840;
extern u16 D_1F80009C_baed_759c;
extern s16 D_1F80018C;
extern s16 D_1F80018E;
extern u16 D_1F80008C_7310;
void func_8010B724(u8 *a, u8 *b)
{
    s16 ang;
    s32 d;
    s32 k;
    s16 t;

    if (func_8002300C(a, b, *(s16 *)(b + 0x80) * 4) != 0) {
        ang = D_1F80009C_baed_759c + 0x800;
        b[0x2B] = 1;
        if (D_1F800137 == 0) {
            k = *(u16 *)(a + 0x140) - 0x400;
            d = func_80085690(-(s16)(*(u16 *)(b + 0x36) - *(u16 *)(a + 0x36)), (s16)(*(u16 *)(b + 0x2E) - *(u16 *)(a + 0x2E))) << 4;
            t = d - k * 16;
            if (abs(t) < 0x1000) {
                D_1F80018E = 0x4100;
                D_1F80018C = *(u16 *)(a + 0x140) - 0x400;
                D_800BF840 = 0x42;
            } else {
                s32 m = *(u16 *)(a + 0x140) + 0x400;
                t = d - m * 16;
                if (abs(t) < 0x1000) {
                    D_1F80018C = m;
                    D_1F80018E = 0x4200;
                    D_800BF840 = 0x43;
                }
            }
        }
        if (*(s16 *)(a + 0x80) + *(s16 *)(b + 0x80) + 0x50 >= D_1F80008C_7310) {
            b[0x2B] = 2;
            if (*(s16 *)(a + 0x80) + *(s16 *)(b + 0x80) >= D_1F80008C_7310 && !(a[0] & 4)) {
                s32 x = (func_80083F50(ang) * (*(s16 *)(a + 0x80) + *(s16 *)(b + 0x80))) >> 12;
                s32 z = func_80083E80(ang) * (*(s16 *)(a + 0x80) + *(s16 *)(b + 0x80));
                *(s16 *)(a + 0x2E) = *(s16 *)(b + 0x2E) + x;
                *(s16 *)(a + 0x36) = *(s16 *)(b + 0x36) - (z >> 12);
            }
        }
    }
}

extern u8 **D_1F800154;
extern u8 D_1F80015C;
extern u8 D_1F800183;
extern u8 D_1F800182_5650;
extern u8 D_1F800150;
extern u8 **D_1F80013C;
extern u8 D_1F800144;
#define TOWER_SCAN_LIST(e)                                          \
    {                                                    \
        u8 **m;                                          \
        u8 *o;                                           \
        D_1F800182_5650 = D_1F800150;                         \
        while (D_1F800182_5650 != 0) {                        \
            D_1F800182_5650--;                                \
        }                                                \
        m = D_1F80013C;                                  \
        D_1F800182_5650 = D_1F800144;                         \
        while (D_1F800182_5650 != 0) {                        \
            o = *m;                                      \
            D_1F800182_5650--;                                \
            m++;                                         \
            if ((o[0] & 1) && o[2] == 8) {               \
                func_8002423C(e, o);                     \
            }                                            \
        }                                                \
    }
void func_8010B930(void)
{
    u8 **l = D_1F800154;
    u8 *e;
    D_1F800183 = D_1F80015C;
    while (D_1F800183 != 0) {
        e = *l;
        D_1F800183--;
        l++;
        if (!(e[0] & 2)) {
            switch (e[2]) {
            case 1:
                if (e[3] == 1) {
                    TOWER_SCAN_LIST(e);
                }
                break;
            case 0:
            case 4:
                TOWER_SCAN_LIST(e);
                break;
            }
        }
    }
}

void func_8010BB54(u8 *a, u8 *b)
{
    s16 dx = *(u16 *)(a + 0x2E) - *(u16 *)(b + 0x2E);
    s16 dz = *(u16 *)(a + 0x36) - *(u16 *)(b + 0x36);
    s32 d = func_80084080(dx * dx + dz * dz);
    s32 ang;

    if ((u16)d > *(s16 *)(a + 0x80) + *(s16 *)(b + 0x80)) {
        return;
    }
    if ((u16)((*(u16 *)(a + 0x32) - *(u16 *)(b + 0x32)) + (*(u16 *)(b + 0x84) + (*(u16 *)(a + 0x86) - *(u16 *)(a + 0x84)))) > *(s16 *)(a + 0x86) + *(s16 *)(b + 0x86)) {
        return;
    }
    a[0x2B] = 1;
    ang = func_80085690(-dz, dx);
    D_1F80009C_baed = ang;
    {
        s32 temp_s0 = (s32) (func_80083F50(ang) * (M2C_FIELD(a, s16 *, 0x80) + M2C_FIELD(b, s16 *, 0x80))) >> 0xC;
        s32 temp_lo = func_80083E80(D_1F80009C_baed) * (M2C_FIELD(a, s16 *, 0x80) + M2C_FIELD(b, s16 *, 0x80));
        u16 x = M2C_FIELD(b, u16 *, 0x2E);

        D_1F800182_5650 = 0;
        M2C_FIELD(a, s16 *, 0x2E) = (s16) (x + temp_s0);
        M2C_FIELD(a, s16 *, 0x36) = (s16) (M2C_FIELD(b, u16 *, 0x36) - (temp_lo >> 0xC));
    }
}

void func_8010BCB8(u8 *a, u8 *b, u8 *c)
{
    s16 dx = *(u16 *)(a + 0x2E) - *(u16 *)(c + 0x2C);
    s16 dz = *(u16 *)(a + 0x36) - *(u16 *)(c + 0x34);
    s32 d = func_80084080(dx * dx + dz * dz);
    s32 ang;

    if ((u16)d > *(s16 *)(a + 0x80) + *(s16 *)(b + 0x80)) {
        return;
    }
    if ((u16)((*(u16 *)(a + 0x32) - *(u16 *)(c + 0x30)) + (*(u16 *)(b + 0x84) + (*(u16 *)(a + 0x86) - *(u16 *)(a + 0x84)))) > *(s16 *)(a + 0x86) + *(s16 *)(b + 0x86)) {
        return;
    }
    ang = func_80085690(-dz, dx);
    D_1F80009C_baed = ang;
    if (b[0x5E] == 0) {
        s32 temp_s0 = (s32) (func_80083F50(ang) * (M2C_FIELD(a, s16 *, 0x80) + M2C_FIELD(b, s16 *, 0x80))) >> 0xC;
        s32 temp_lo = func_80083E80(D_1F80009C_baed) * (M2C_FIELD(a, s16 *, 0x80) + M2C_FIELD(b, s16 *, 0x80));
        u16 z;

        M2C_FIELD(a, s16 *, 0x2E) = (s16) (M2C_FIELD(c, u16 *, 0x2C) + temp_s0);
        z = M2C_FIELD(c, u16 *, 0x34);
        a[0x2B] = 1;
        M2C_FIELD(a, s16 *, 0x36) = (s16) (z - (temp_lo >> 0xC));
    } else {
        a[0x2B] = 0x80;
        b[0x2B] = 1;
        *(u8 **)(b + 0x10) = a;
    }
    D_1F800182_5650 = 0;
}

extern u8 **D_1F80014C;
extern u8 D_1F800152;
extern u8 **D_1F800140;
extern u8 D_1F800146;
u8 func_8010BE54(u8 *a, s32 f)
{
    u8 **l;
    u8 *p;

    if (f != 0) {
        l = D_1F80014C;
        D_1F800182_5650 = D_1F800152;
        while (D_1F800182_5650 != 0) {
            p = *l;
            D_1F800182_5650--;
            l++;
            if (p[0] & 1) {
                if (p[2] == 0x3F) {
                    func_8010BCB8(a, p, *(u8 **)(p + 0xC8));
                } else if (p[2] == 0x18) {
                    func_8010BB54(a, p);
                }
            }
        }
    }
    l = D_1F800140;
    D_1F800182_5650 = D_1F800146;
    while (D_1F800182_5650 != 0) {
        p = *l;
        D_1F800182_5650--;
        l++;
        if ((p[0] & 1) && p[0xC] == 9 && func_80023A04(a, p, 0) >= 0) {
            a[0x2B] |= 1;
        }
    }
    return a[0x2B];
}

extern s32 D_1F800098;
#define F16(p, o) M2C_FIELD(p, s16 *, o)
#define FU16(p, o) M2C_FIELD(p, u16 *, o)
s32 func_8010BFAC(u8 *a, u8 *b, u8 *c) {
    s16 dx, dz, dy, e, f, v;
    u16 h, bh, ah;
    u16 r;
    s32 ang, s, t, m;

    if (F16(b, 0x62) == 0) {
        return func_8001EC3C(a, b);
    }
    dx = FU16(a, 0x2E) - FU16(c, 0x2C);
    dz = FU16(a, 0x36) - FU16(c, 0x34);
    r = func_80084080(dx * dx + dz * dz);
    if (r > F16(a, 0x80) + F16(b, 0x80)) {
        return 0;
    }
    dy = FU16(a, 0x32) - FU16(c, 0x30);
    ah = FU16(a, 0x84); bh = FU16(b, 0x84); h = ah + bh;
    if ((u16)(dy + h) > F16(a, 0x86) + F16(b, 0x86)) {
        return 0;
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
    D_1F80009C_baed = ang;
    if (s < e - dy || s < 3) {
        m = (func_80083F50(ang) * (F16(a, 0x80) + F16(b, 0x80))) >> 12;
        t = func_80083E80(D_1F80009C_baed) * (F16(a, 0x80) + F16(b, 0x80));
        F16(a, 0x2E) = FU16(c, 0x2C) + m;
        MEMBER_AT(s16, a, 0x36) = FU16(c, 0x34) - (t >> 12);
        a[0x60] = 1;
        a[0x5F] = func_80077768((s16)D_1F80009C_baed, F16(a, 0x140), 1) + 2;
        if (func_80077768(F16(a, 0x56), (s16)D_1F80009C_baed, 0) != 0) {
            if (b[0x5F] == 1) {
                if (a[4] == 1 && a[5] != 0x13) {
                    s32 d = D_1F80009C_baed;
                    a[5] = 0x13;
                    a[6] = 0;
                    a[7] = 0;
                    a[0x2B] = d >> 4;
                }
            } else if (a[0x165] != 0) {
                if (D_1F800098 != 1) {
                    goto ret1;
                }
                if (F16(a, 0x44) < 0) {
                    dx = -F16(a, 0x44);
                } else {
                    dx = F16(a, 0x44);
                }
                if (dx <= 0x1A00) {
                    goto ret1;
                }
                if (a[4] != 1) {
                    goto ret1;
                }
                if (a[5] != 0x13) {
                    s32 d2 = D_1F80009C_baed;
                    a[5] = 0x13;
                    a[6] = 0;
                    a[7] = 0;
                    a[0x2B] = d2 >> 4;
                    D_1F80009C_baed = (D_1F80009C_baed - 0x400) & 0xFFF;
                    if (D_1F80009C_baed < 0x800) {
                        b[0x2B] = 2;
                    } else {
                        b[0x2B] = 3;
                    }
                }
            }
        }
    ret1:
        return 1;
    }
    if (a[0x145] & 1) {
        return 0;
    }
    a[0x29] = 1;
    M2C_FIELD(a, s32 *, 0x30) = (M2C_FIELD(c, s32 *, 0x30) + f) << 16;
    F16(b, 0x44) = F16(a, 0x44);
    b[0x29] = 1;
    if (F16(b, 0x62) != 0 && !(a[0] & 4) && a[0x145] == 2 && a[4] < 2) {
        if (func_80055844() != 0) {
            a[0x145] = 0;
            b[0x5E] = 2;
            a[0x148] = 0;
            F16(a, 0x50) = 0;
            a[5] = 0x17;
            a[6] = 0;
            a[7] = 0;
            goto done;
        }
        if (a[5] != 0x17 || F16(a, 0x4A) > 0x2C00) {
            a[0x145] = 0;
            b[0x5E] = 1;
            a[0x148] = 0;
            F16(a, 0x50) = 0;
            a[5] = 0x17;
            a[6] = 0;
            a[7] = 0;
            goto done;
        }
    }
    func_80022C78(a);
    b[0x5E] = 0;
done:
    return 2;
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8010C410);

#define H(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define U(p, o) (*(u16 *)((u8 *)(p) + (o)))
static inline s32 e814_hit(u8 *a, u8 *b)
{
    s16 dx = U(a, 0x2E) - (U(b, 0x2E) + U(b, 0x60));
    s16 dz = U(a, 0x36) - (U(b, 0x36) + U(b, 0x64));

    u16 d = func_80084080(dx * dx + dz * dz);
    u16 h;

    if (H(a, 0x80) + H(b, 0x80) < d) {
        return 0;
    }
    h = U(a, 0x86);
    return (u16)((U(a, 0x32) - (U(b, 0x32) + U(b, 0x62))) + (U(b, 0x84) + (h - U(a, 0x84)))) <= (s16)h + H(b, 0x86);
}
void func_8010C548(u8 *a, u8 *b)
{
    if (e814_hit(a, b)) {
        s16 ang;
        s32 t, u;
        if (b[0x5F] == 0) {
            ang = U(a, 0x60);
        } else {
            ang = U(a, 0x60) + 0x800;
        }
        t = (func_80083F50(ang) * (H(a, 0x80) + H(b, 0x80))) >> 12;
        u = func_80083E80(ang) * (H(a, 0x80) + H(b, 0x80));
        H(a, 0x2E) = t + (U(b, 0x2E) + U(b, 0x60));
        { s32 w = u >> 12; H(a, 0x36) = (U(b, 0x36) + U(b, 0x64)) - w; }
    }
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8010C6E0);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8010C990);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8010CDEC);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8010D0C4);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8010D308);

extern u16 D_800BFE56;
/* func_8010E7EC, inlined */
static inline void func_8010E7EC_inl(void *arg0, void *arg1) {
    if (!(M2C_FIELD(arg0, u16 *, 0x17E) & 0x200) && (func_80022F04(arg0, arg1) != 0) && !(M2C_FIELD(arg0, u8 *, 0) & 6)) {
        M2C_FIELD(arg0, s8 *, 0x2B) = (s8) (D_1F80009C_baed >> 4);
        func_80022D08(arg0, 0, 1, 1);
        func_80058304(arg0, 0);
        M2C_FIELD(arg1, s8 *, 0) = 2;
        M2C_FIELD(arg1, s8 *, 4) = 2;
        M2C_FIELD(arg1, s8 *, 5) = 0;
        M2C_FIELD(arg1, s8 *, 6) = 0;
    }
}
void func_8010D490(u8 *a)
{
    u8 **l = D_1F80013C;
    u8 *b;
    u16 f;

    D_1F800182_5650 = D_1F800144;
    while (D_1F800182_5650 != 0) {
        b = *l;
        D_1F800182_5650--;
        l++;
        if (!(b[0] & 1)) {
            continue;
        }
        if (b[0xC] == 9) {
            if (!(*(s16 *)(a + 0x17E) & 0x8200)) {
                func_8010B724(a, b);
            }
            continue;
        }
        switch (b[2]) {
        case 1:
            f = *(u16 *)(a + 0x17E);
            if (f & 0x200) {
                break;
            }
            if (f & 0x8000) {
                func_8001F830(a, b);
            } else if (func_80020364(a, b, 0x80) == 3) {
                b[0x5F] = func_80077768((s16)D_1F80009C_baed, *(s16 *)(a + 0x140), 1) + 2;
            }
            break;
        case 8:
            func_800205CC(a, b);
            break;
        case 0x2E:
            if (D_800BFE56 & 0x20) {
                func_80020364(a, b, 0x40);
            } else if (b[0] & 2) {
                func_80020364(a, b, 1);
            } else {
                func_80020364(a, b, 2);
            }
            break;
        case 0x2D:
            func_8010AA70(a, b);
            break;
        case 0x21:
            func_8010E7EC_inl(a, b);
            break;
        case 0x42:
            func_8010ABA0(a, b);
            break;
        case 0x32:
            func_8010B5E8(a, b);
            break;
        case 0x50:
            func_80020364(a, b, 0);
            break;
        }
    }
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8010D720);

extern s8 D_1F800182[];
extern u8 *D_800F2738;
/* func_8010EC7C, inlined */
static inline void func_8010EC7C_inl(s32 arg0, u8 *arg1) {
    s32 var_v0;

    if (func_80022F04(arg0, arg1) != 0) {
        if (*arg1 & 0xA) {
            var_v0 = func_8001E860(arg0, arg1, 0, 0);
        } else {
            var_v0 = func_8001DC9C(arg0, arg1, 0, 1);
        }
        if (!(var_v0 & 0x80)) {
            D_1F800182_5650 = 0;
        }
    }
}
/* func_8010EA50, inlined */
static inline void func_8010EA50_inl(void *arg0, s8 *arg1)
{
    if (func_80022F04(arg0, arg1) != 0) {
        if (!(func_8001DC9C(arg0, arg1, 0, 4) & 4)) {
            arg1[0x2B] = 10;
        }
        D_1F800182_5650 = 0;
    }
}
void func_8010DB50(void)
{
    u8 *a;
    u8 **p;
    u8 *b;
    if (*(s16 *)&D_1F800144 == 0) {
        return;
    }
    for (a = D_800F2738; a != NULL; a = *(u8 **)(a + 0x24)) {
        if ((a[0] & 1) && a[0x2B] == 0) {
            p = D_1F80013C;
            D_1F800182_5650 = D_1F800144;
            while (D_1F800182_5650 != 0) {
                b = *p;
                D_1F800182_5650--;
                p++;
                if (b[0] & 1) {
                    switch (b[2]) {
                    case 8:
                        func_80021394(a, b, 0x100);
                        break;
                    case 0x2D:
                        func_8010EA50_inl(a, b);
                        break;
                    case 0x42:
                        func_8010EC7C_inl((s32)a, b);
                        break;
                    case 0x2E:
                        if (D_800BFE56 & 0x20) {
                            func_8010EC7C_inl((s32)a, b);
                        } else {
                            func_800216B4(a, b, 0);
                        }
                        break;
                    case 0x50:
                        func_80021DF4(a, b);
                        break;
                    }
                }
            }
        }
    }
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8010DDAC);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8010E240);

extern void *D_1F800080;
extern s32 D_1F80008C;
u8 *func_8010E36C(u8 *a)
{
    u8 **l = D_1F80014C;
    u8 *p;

    D_1F800182_5650 = D_1F800152;
    while (D_1F800182_5650 != 0) {
        p = *l;
        D_1F800182_5650--;
        l++;
        if (p[0] & 1) {
            s32 t = p[2];

            if (t >= 0x2F) {
                if (t >= 0x31) {
                    if (t == 0x41 && p[0x5E] == 0 && func_80024338(a, p) != 0) {
                        s32 v = D_1F80008C;

                        p[0x29] = 1;
                        p[0x2B] = (v + 0x800) >> 4;
                        *(s16 *)(a + 0x156) = -0x1B;
                        {
                            s16 r = *(s16 *)(p + 0x80) + *(s16 *)(a + 0x80) - 0xC;

                            a[0x164] = 1;
                            a[0x15C] = 0;
                            D_1F800080 = p;
                            D_1F800182_5650 = 0;
                            *(s16 *)(a + 0x152) = r;
                        }
                    }
                } else {
                    func_8010E240(a, p);
                }
            }
        }
    }
    return D_1F800080;
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8010E4B0);

extern s32 D_80140D38[];
extern s16 D_80140E38;
extern void *D_80140E3C;
void func_8010E5A8(void)
{
    D_80140E3C = &D_80140D38[0x40];
    D_80140E38 = 0;
}

void func_8010E5C4(s32 arg0) {
    void *temp_a0;

    if (D_80140E38 < 0x40) {
        temp_a0 = D_80140E3C;
        D_80140E3C = temp_a0 - 4;
        M2C_FIELD(temp_a0, s32 *, -4) = arg0;
        D_80140E38 = (u16) D_80140E38 + 1;
    }
}

extern u8 D_800BF816;
void func_8010E604(u8 *a0, u8 *a1)
{
    u8 *b = a1;
    u8 *a = a0;
    if (!(b[0] & 2) && func_80022F04() != 0) {
        if (D_800BF816 == 0 || a[0x164] == 4) {
            b[0x29] = 1;
            return;
        }
        if (*(s16 *)(b + 0x32) > *(s16 *)(a + 0x32)) {
            *(s16 *)(a + 0x32) = *(s16 *)(b + 0x32);
        }
    }
}

extern u8 D_800BF8CD;
void func_8010E698(u8 *a)
{
    u8 *g;
    s32 h;

    if (a[0] == 2) {
        return;
    }
    g = D_800BF808;
    h = *(u16 *)(g + 0xA);
    if (g[0xF] != 0) {
        if (g[0xF] != 2) {
            return;
        }
        if (D_800BF8CD != 0xFF) {
            if (*(s16 *)(a + 0x2E) < 0x2D2C) {
                *(s16 *)(a + 0x2E) = 0x2D2B;
            }
            if (*(s16 *)(a + 0x36) >= 0x4B34) {
                *(s16 *)(a + 0x36) = 0x4B34;
            }
        }
    }
    if (!(a[0x145] & 1) && *(s16 *)(a + 0x32) >= (s16)h - *(s16 *)(a + 0x62)) {
        *(s16 *)(a + 0x32) = h - *(s16 *)(a + 0x62);
        func_80022C78(a, a, h);
    }
}

extern s16 D_1F80009C_c31a;
void func_8010E760(u8 *a, u8 *b)
{
    u16 f = *(u16 *)(a + 0x17E);

    if (!(f & 0x200)) {
        if (f & 0x8000) {
            func_8001F830(a, b);
            return;
        }
        if (func_80020364(a, b, 0x80) == 3) {
            b[0x5F] = func_80077768(D_1F80009C_c31a, *(s16 *)(a + 0x140), 1) + 2;
        }
    }
}

extern s8 D_1F80009C[];
void func_8010E7EC(void *arg0, void *arg1) {
    if (!(M2C_FIELD(arg0, u16 *, 0x17E) & 0x200) && (func_80022F04() != 0) && !(M2C_FIELD(arg0, u8 *, 0) & 6)) {
        M2C_FIELD(arg0, s8 *, 0x2B) = (s8) ((s32) *((s32 *)D_1F80009C) >> 4);
        func_80022D08(arg0, 0, 1, 1);
        func_80058304(arg0, 0);
        M2C_FIELD(arg1, s8 *, 0) = 2;
        M2C_FIELD(arg1, s8 *, 4) = 2;
        M2C_FIELD(arg1, s8 *, 5) = 0;
        M2C_FIELD(arg1, s8 *, 6) = 0;
    }
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8010E88C);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8010E974);

extern s32 D_800ECF80;
extern u8 D_80140E40_ebd8[];
extern u8 D_800BFA49;
void func_80126E4C();
extern u16 D_1F8001A0;
extern u16 D_1F8001A2;
void func_8010EA50(void *arg0, s8 *arg1)
{
    if (func_80022F04(arg0, arg1) != 0) {
        if (!(func_8001DC9C(arg0, arg1, 0, 4) & 4)) {
            arg1[0x2B] = 10;
        }
        *((s8 *)D_1F800182) = 0;
    }
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8010EAB4);

void func_8010EBA4(void *a0)
{
    u8 **list;
    u8 *e;

    for (D_1F800182_5650 = D_1F800150; D_1F800182_5650 != 0; D_1F800182_5650--) {
    }
    list = D_1F80013C;
    D_1F800182_5650 = D_1F800144;
    while (D_1F800182_5650 != 0) {
        e = *list++;
        D_1F800182_5650--;
        if ((e[0] & 1) && e[2] == 8) {
            func_8002423C(a0, e);
        }
    }
}

void func_8010EC7C(s32 arg0, u8 *arg1) {
    s32 var_v0;

    if (func_80022F04() != 0) {
        if (*arg1 & 0xA) {
            var_v0 = func_8001E860(arg0, arg1, 0, 0) & 0x80;
        } else {
            var_v0 = func_8001DC9C(arg0, arg1, 0, 1) & 0x80;
        }
        if (var_v0 == 0) {
            *((s8 *)D_1F800182) = 0;
        }
    }
}

void func_8010ED00(u8 *a, u8 *b)
{
    if (func_8002313C(a, b, *(void **)(b + 0xC0)) != 0) {
        if (*(s16 *)(b + 0x62) == 0) {
            func_8001DC9C(a, b, 0, 5);
            D_1F800182_5650 = 0;
        } else {
            s32 v;
            func_8001E860(a, b, *(void **)(b + 0xC0), 0x400);
            v = D_1F80009C_baed;
            b[0x2B] = 1;
            b[0x46] = v >> 4;
            if (a[0x5E] != 0) {
                b[0x2B] = 0x81;
            }
            D_1F800182_5650 = 0;
        }
    }
}

void func_8010EDA8(void *arg0, void *arg1) {
    if (func_800240FC() != 0) {
        M2C_FIELD(arg0, s8 *, 0) = 2;
        M2C_FIELD(arg0, s8 *, 4) = 2;
        M2C_FIELD(arg0, s8 *, 6) = 0;
        if (M2C_FIELD(arg1, u8 *, 0x5E) == 0) {
            M2C_FIELD(arg0, s8 *, 5) = 1;
            return;
        }
        M2C_FIELD(arg0, s8 *, 5) = 2;
    }
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8010EE08);

extern u8 D_800E7E80[];
void f_UpdateReturnedKujaraActor();
extern u8 D_1F800207_9c67;
void f_UpdateKujaraSummitMechanismActor();
void func_8010EF30(u8 *p)
{
    u8 *e;

    if (func_800240FC(p)) {
        e = D_800E7E80;
        if ((e[0x78] == 0 || p != *(u8 **)(e + 0x10)) && p[4] < 3) {
            p[0] = 2;
            p[4] = 3;
        }
    }
}

void func_8010EFA0(u8 *a, u8 *b)
{
    if (b[0x5E] == 0 && func_80024338(a, b) != 0) {
        s16 h;
        b[0x2B] = (D_1F80008C + 0x800) >> 4;
        b[0x29] = 1;
        *(s16 *)(a + 0x156) = -0x1B;
        h = *(s16 *)(b + 0x80) + *(s16 *)(a + 0x80);
        a[0x164] = 1;
        a[0x15C] = 0;
        D_1F800080 = b;
        D_1F800182_5650 = 0;
        *(s16 *)(a + 0x152) = h - 0xC;
    }
}

s32 func_8010F034(void *a)
{
    u8 **l = D_1F80014C;
    u8 *e;

    D_1F800182_5650 = D_1F800152;
    while (D_1F800182_5650 != 0) {
        e = *l;
        D_1F800182_5650--;
        l++;
        if (e[0] & 1) {
            s32 k = e[2];
            if (k < 0x31) {
                if (k >= 0x2F) {
                    if (func_8010E240(a, e)) {
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8010F0F8);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8010F304);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8010F948);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8010FF20);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80110074);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80110380);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801105FC);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8011099C);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80110CB8);

extern s8 D_1F800138[];
extern s8 D_1F80019B[];
void func_80110F38(void) {
    func_80045258(M2C_FIELD(*((volatile void **)D_1F800138), u8 *, 0x6E), 0xF);
    *((volatile s8 *)D_1F80019B) = 1;
    func_80051FB4();
}

s32 func_80110F78(s32 arg0, s32 arg1) {
    void *temp_a1;

    temp_a1 = M2C_FIELD(arg0, void **, 0x158);
    if (M2C_FIELD(temp_a1, u8 *, 2) == 0x41) {
        func_80110074(arg0, (s32) temp_a1, arg1);
    }
    return 0;
}

void func_80110FB4(u8 *a)
{
    if (a[0x2A] == 1 && a[0x29] != 0 && *(s16 *)(a + 0x36) < 0x1DB1) {
        if ((*(s16 *)(a + 0x44) -= 0xE0) < -0x1400) {
            *(s16 *)(a + 0x44) = -0x1400;
        }
    } else {
        s16 v = *(s16 *)(a + 0x44);
        s32 k = abs(v) - 0xE0;
        s16 m = k;
        if ((s16)k <= 0) {
            m = 0;
        }
        if (v >= 0) {
            *(s16 *)(a + 0x44) = m;
        } else {
            *(s16 *)(a + 0x44) = -m;
        }
    }
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8011105C);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801110A4);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801112B4);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80111480);

extern s8 D_1F800138[];
extern s8 D_1F80019B[];
void func_80111A74(void) {
    func_80045258(M2C_FIELD(*((volatile void **)D_1F800138), u8 *, 0x6E), 0xF);
    *((volatile s8 *)D_1F80019B) = 1;
    func_80051FB4();
}

extern u8 D_1F8000D0[];
void func_80111AB4(u8 *a)
{
    u8 *p = a + 0x38;

    func_8006D934(a, p);
    func_8006D950(a, p);
    if (a[0x76] == 0) {
        u8 *c;
        func_8006DAD8(a);
        func_8006DEF0(a);
        c = D_1F8000D0;
        if (*(s16 *)(c + 0xA) < 0x447F) {
            *(s16 *)(c + 0xA) = 0x447E;
        } else if (*(s16 *)(c + 0xA) >= 0x4C14) {
            *(s16 *)(c + 0xA) = 0x4C14;
        }
    }
    func_8006D02C(a);
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", f_SpawnKujaraSummitSceneActorsFromPlacementTable);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80112020);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801121AC);

extern u8 D_800BF9CA;
extern char D_801097F0[];
void func_801124AC(void *unused)
{
    char buf[0x20];
    s32 n = D_800BF9CA + 1;

    func_8009B0C0(buf, D_801097F0, n);
    func_80079374(0x80, 0x70, 0, buf, 4);
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801124FC);

void func_801126C0(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 4);
    switch (temp_v1) {                              /* irregular */
    case 0:
        if (M2C_FIELD(arg0, u8 *, 3) == 0) {
            func_8004BEF4(arg0);
        }
        M2C_FIELD(arg0, u8 *, 4) = (u8) (M2C_FIELD(arg0, u8 *, 4) + 1);
        return;
    case 1:
        if (M2C_FIELD(arg0, u8 *, 3) == 0) {
            func_801124FC(arg0);
            return;
        }
    case 2:
        return;
    case 3:
        func_8007A624(arg0);
        break;
    }
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80112778);

INCLUDE_ASM("asm/a05/nonmatchings/a05", f_UpdateKujaraSummitQuestPickupActor);

void f_UpdateKujaraSummitQuestPickupActor();
u8 *func_80112CD8(void *a0, s32 a1)
{
    u8 *r = func_80072DDC(a0, 0x80, 5, 3);

    if (r == 0) {
        return 0;
    }
    r[3] = 0;
    r[0x5E] = a1;
    *(void **)(r + 0x1C) = f_UpdateKujaraSummitQuestPickupActor;
    return r;
}

void func_80112D28(u8 *p)
{
    *(s32 *)(p + 0x3C) = D_800ECF80;
    func_80077B38(p, D_80140E40_ebd8, 0);
    p[0xD] = 0;
    *(s16 *)(p + 0x5C) = 0;
    p[0xB] = 0x10;
    *(s16 *)(p + 0x5A) = 0;
    p[0x47] = 0;
    p[8] = 0;
    func_8004B354(p, 0);
}

void func_80112D8C(u8 *p)
{
    *(s16 *)(p + 0x2E) = *(s16 *)(*(u8 **)(p + 0x10) + 0x2E);
    *(s16 *)(p + 0x32) = *(s16 *)(*(u8 **)(p + 0x10) + 0x32) - 0x64;
    *(s16 *)(p + 0x36) = *(s16 *)(*(u8 **)(p + 0x10) + 0x36);
}

void func_80112DBC(u8 *a)
{
    if (a[5] == 0) {
        a[5] = 1;
        a[0] = 1;
        *(s16 *)(a + 0x80) = 0x20;
        *(s16 *)(a + 0x82) = 0x40;
        *(s16 *)(a + 0x84) = 0x40;
        *(s16 *)(a + 0x86) = 0x80;
        func_80041194(a, (s16)(*(s16 *)(a + 0x82) - *(s16 *)(a + 0x80)), 0, 0);
        *(s16 *)(a + 0x5A) = 0x400;
    }
}

/* func_80112D8C, inlined */
static inline void func_80112D8C_inl(u8 *p)
{
    *(s16 *)(p + 0x2E) = *(s16 *)(*(u8 **)(p + 0x10) + 0x2E);
    *(s16 *)(p + 0x32) = *(s16 *)(*(u8 **)(p + 0x10) + 0x32) - 0x64;
    *(s16 *)(p + 0x36) = *(s16 *)(*(u8 **)(p + 0x10) + 0x36);
}
/* func_80112DBC, inlined */
static inline void func_80112DBC_inl(u8 *a)
{
    if (a[5] == 0) {
        a[5] = 1;
        a[0] = 1;
        *(s16 *)(a + 0x80) = 0x20;
        *(s16 *)(a + 0x82) = 0x40;
        *(s16 *)(a + 0x84) = 0x40;
        *(s16 *)(a + 0x86) = 0x80;
        func_80041194(a, (s16)(*(s16 *)(a + 0x82) - *(s16 *)(a + 0x80)), 0, 0);
        *(s16 *)(a + 0x5A) = 0x400;
    }
}
void func_80112E38(u8 *a)
{
    if (D_800BF816 == 0) {
        a[4] = 3;
        return;
    }
    switch (a[0x5E]) {
    case 0:
        func_80112D8C_inl(a);
        break;
    case 1:
        func_80112DBC_inl(a);
        break;
    }
    func_8007778C(a);
    func_8004B374(a, 0);
}

void func_80112F30(void *arg0) {
    func_8004D4C4(0x4E, 1);
    func_8004B0D8(arg0);
    D_800BF870.pad1[0x149] |= 2;
    func_80040B48(0x7A);
    M2C_FIELD(arg0, s8 *, 4) = 3;
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80112F88);

typedef struct {
    u8 x0;
    u8 pad1;
    s16 x2;
} S4;
extern S4 D_8013C510[];
void func_8011318C(s32 i)
{
    S4 *e = &D_8013C510[i];
    s32 v = e->x2;

    if (!(e->x0 & 0x80)) {
        func_8004D7EC(v, 1);
    } else {
        func_8004D868(v, 1);
    }
}

extern u8 D_8004C238[];
extern s32 D_800BF85C;
s32 func_801131E0(u8 *p, s32 i)
{
    S4 *e;
    s32 r;

    p[0xC] = 5;
    p[2] = 4;
    *(void **)(p + 0x1C) = D_8004C238;
    e = &D_8013C510[i];
    p[3] = e->pad1;
    p[0x5E] = e->x0 & 0x7F;
    *(s16 *)(p + 0x60) = 1;
    *(s16 *)(p + 0x62) = e->x2;
    *(s16 *)(p + 0x64) = 2;
    if (e->x0 & 0x80) {
        *(s16 *)(p + 0x64) = 6;
    }
    r = func_8004A828(p, e);
    p[4] = 1;
    p[5] = 0;
    p[6] = 0;
    p[7] = 0;
    return r;
}

void func_80113294(u8 *p, s32 a1)
{
    u8 *r = func_8004C0E4(p, a1 + 6, 0);

    if (r) {
        *(s16 *)(r + 0x2E) = *(s16 *)(p + 0x2E);
        *(s16 *)(r + 0x32) = *(s16 *)(p + 0x32);
        *(s16 *)(r + 0x36) = *(s16 *)(p + 0x36);
    }
}

void func_801132F0(u8 *p)
{
    switch (p[5]) {
    case 0:
        p[5]++;
        p[0] = 1;
    case 1:
        func_8007778C(p);
        func_80077B5C(p);
        break;
    }
}

extern u8 D_800ECF58[];
extern u8 D_8013B634[];
extern u8 D_80140F7C_8010[];
extern u8 D_800A3D18[];
s32 func_80113348(u8 *p)
{
    u8 *s = D_800ECF58;
    s32 k;

    if (func_800519E0(p, 0xF, *(s32 *)(s + 0x3C), D_8013B634) != 0) {
        return 0;
    }
    *(s32 *)(p + 0x3C) = *(s32 *)(s + 0x38);
    func_80040CDC(p, D_80140F7C_8010, D_800A3D18);

    p[0x7B] = 0x1D;
    p[0xB] = 0;
    p[0] = 1;
    *(s16 *)(p + 0x80) = 0x50;
    *(s16 *)(p + 0x82) = 0xA0;
    *(s16 *)(p + 0x84) = 0x80;
    *(s16 *)(p + 0x86) = 0xE0;
    p[0x2B] = 0;
    p[0x29] = 0;
    *(s16 *)(p + 0x54) = 0;
    p[0x46] = 0x1D;
    p[0xB] = (p[0xB] & 0xC0) | 0x80;
    func_80041718(p, p[0x7B], 1);
    p[0x2A] = 0x2B;
    *(s32 *)(p + 0x2C) = 0x3A800000;
    *(s32 *)(p + 0x30) = 0xD6FC0000;
    *(s32 *)(p + 0x34) = 0x12F00000;
    p[0xBE] = 1;
    func_80041194(p, 0x60, 1, 0);
    func_8004130C(p, 1);
    *(s16 *)(p + 0x44) = 0;
    *(s16 *)(p + 0x52) = 0;
    return 1;
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80113468);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801136A8);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80113A6C);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80113D24);

void func_80114178(u8 *a, s32 k, s32 m, s32 flag)
{
    s16 mm = m;
    if (a[0x46] != (u8)k) {
        if (flag) {
            func_800416A8(a, -1, 0);
        } else {
            func_800416A8(a, 0xE, D_80140F7C_8010);
        }
        func_80041718(a, k, mm);
    }
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801141F8);

INCLUDE_ASM("asm/a05/nonmatchings/a05", f_UpdateKujaraHotSpringActor);

s32 func_801145A0(void *arg0) {
    s32 temp_a0;
    s32 temp_a2;
    s32 var_s0;
    void *var_s1;

    var_s0 = 0;
    var_s1 = arg0;
    do {
        temp_a0 = M2C_FIELD(var_s1, s32 *, 0xC0);
        var_s1 += 4;
        temp_a2 = var_s0;
        var_s0 += 1;
        func_80051B04(temp_a0, 0x21, temp_a2);
    } while (var_s0 < 0xD);
    return 1;
}

extern u8 D_80141AF8[];
extern u8 D_8013C748[];
extern u8 D_8013C83C[];
s32 func_801145F0(u8 *p)
{
    s32 s = p[6];

    switch (s) {
    case 0:
        p[6] = 1;
        func_80040CDC(p, D_80141AF8, D_8013C748);
        p[0x70] = 1;
        break;
    case 1:
        func_80041098(p);
        if (p[0x70] != 0xFF) {
            return 0;
        }
        func_80040CDC(p, D_80141AF8, D_8013C83C);
        p[0x70] = s;
        p[6]++;
        break;
    case 2:
        func_80041098(p);
        if (p[0x70] != 0xFF) {
            return 0;
        }
        p[6] = 0;
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801146E8);

typedef struct {
    s16 x0;
    s16 x2;
    u8 pad4[6];
} S10;
extern S10 D_8013C9D4[];
void func_80114838(s32 i)
{
    func_8004D7EC(D_8013C9D4[i].x2, 1);
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80114874);

void func_80114934(void *arg0) {
    u8 temp_v1;

    if ((M2C_FIELD(arg0, u8 *, 0x5F) != 0) || ((temp_v1 = M2C_FIELD(arg0, u8 *, 0x29), (temp_v1 != 0)) && (temp_v1 != 0x80))) {
        func_80027144(M2C_FIELD(M2C_FIELD(arg0, void **, 0xC0), s32 *, 0x40), arg0 + 0x2C, 0x700, 8);
        func_80074590(0xC, 0, 0);
        M2C_FIELD(arg0, s8 *, 4) = 3;
    }
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801149A8);

extern u8 D_8013CA08[];
extern u8 D_8013CA80[];
extern u8 D_8013CAB0[];
extern u8 D_800BF925;
/* func_80115668, inlined */
static inline s32 func_80115668_inl(u8 *p) {
    switch (p[6]) {
    case 0:
        if (p[0x2B] == 3) {
            p[6] = 1;
            func_80042354(1, 1);
        }
        break;
    case 1:
        p[6] = 2;
        func_80040CDC(p, D_80140F7C_8010, D_8013CA08);
        p[0x70] = 1;
        break;
    case 2:
        func_80041098(p);
        if (p[0x70] == 0xFF) {
            p[6] = 0;
            return 1;
        }
        break;
    }
    return 0;
}
/* func_8011541C, inlined */
static inline s32 func_8011541C_inl(void)
{
    u8 *g = (u8 *)&D_800BF870;

    if (g[0x27E]) {
        return 1;
    }
    if (g[0x281]) {
        return 2;
    }
    if (g[0x27F]) {
        return 3;
    }
    return g[0x280] ? 4 : 0;
}
/* func_80115740, inlined */
static inline void func_80115740_inl(u8 *p)
{
    switch (p[6]) {
    case 0:
        if (p[0x2B] == 3) {
            p[6]++;
            func_80042354(1, 1);
        }
        break;
    case 1:
        p[6] = 2;
        func_80040CDC(p, D_80140F7C_8010, D_8013CA80);
        p[0x70] = 1;
        break;
    case 2:
        func_80041098(p);
        if (p[0x70] == 0xFF) {
            p[6] = 0;
            func_80042310();
        }
        break;
    }
}
/* func_80115810, inlined */
static inline void func_80115810_inl(u8 *p)
{
    switch (p[6]) {
    case 0:
        if (p[0x2B] == 3) {
            p[6]++;
            func_80042354(1, 1);
        }
        break;
    case 1:
        p[6] = 2;
        func_80040CDC(p, D_80140F7C_8010, D_8013CAB0);
        p[0x70] = 1;
        break;
    case 2:
        func_80041098(p);
        if (p[0x70] == 0xFF) {
            p[6] = 0;
            func_80042310();
        }
        break;
    }
}
void func_80114CC8(u8 *a)
{
    switch (a[5]) {
    case 0:
        if (func_80115668_inl(a) != 0) {
            if (func_8011541C_inl() != 0) {
                a[5] = 2;
                *(u16 *)(a + 0x40) = 0x1E;
            } else {
                func_80042310();
                a[5] = 1;
            }
        }
        break;
    case 1:
        func_80115740_inl(a);
        break;
    case 2:
        if (--*(s16 *)(a + 0x40) == 0) {
            a[6] = 1;
            a[5]++;
        }
        break;
    case 3:
        if (func_801149A8(a) != 0) {
            if (D_800BF925 == 0xFF) {
                a[5] = 4;
            } else {
                a[5] = 1;
            }
        }
        break;
    case 4:
        func_80115810_inl(a);
        break;
    }
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80114F88);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80115198);

s32 func_8011541C(void)
{
    u8 *g = (u8 *)&D_800BF870;

    if (g[0x27E]) {
        return 1;
    }
    if (g[0x281]) {
        return 2;
    }
    if (g[0x27F]) {
        return 3;
    }
    return g[0x280] ? 4 : 0;
}

s32 func_80115478(void *a0)
{
    func_80130D44(a0, 0);
    return 1;
}

s32 func_80115498(void *a0)
{
    func_80130D44(a0, 1);
    return 1;
}

s32 func_801154B8(void *a0)
{
    func_80130D44(a0, 0x2);
    return 1;
}

s32 func_801154D8(void *a0)
{
    func_80130D44(a0, 0x3);
    return 1;
}

extern u8 D_800E8008[];
extern s16 D_801003F8;
s32 func_801154F8(u8 *a)
{
    u8 *e = D_800E8008;

    switch (a[0x78]) {
    case 0:
        a[0x78] = 1;
        e[0x64] = 1;
        *(s16 *)(e + 0x3A) = 0x3AEA;
        *(s16 *)(e + 0x3E) = -0x1F4C;
        *(s16 *)(e + 0x42) = 0x2866;
        *(s16 *)(e + 0x6E) = 0x100;
        *(s16 *)(e + 0x70) = 0x240;
        *(s16 *)(e + 0x6C) = D_801003F8 * 5;
        *(s16 *)(a + 0x40) = 0x3C;
        break;
    case 1:
        if (--*(s16 *)(a + 0x40) == -1) {
            return 1;
        }
        break;
    }
    return 0;
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801155A4);

extern void *D_800BF868;
s32 func_80115650(void) {
    M2C_FIELD(D_800BF868, s8 *, 4) = 3;
    return 1;
}

s32 func_80115668(u8 *p) {
    switch (p[6]) {
    case 0:
        if (p[0x2B] == 3) {
            p[6] = 1;
            func_80042354(1, 1);
        }
        break;
    case 1:
        p[6] = 2;
        func_80040CDC(p, D_80140F7C_8010, D_8013CA08);
        p[0x70] = 1;
        break;
    case 2:
        func_80041098(p);
        if (p[0x70] == 0xFF) {
            p[6] = 0;
            return 1;
        }
        break;
    }
    return 0;
}

void func_80115740(u8 *p)
{
    switch (p[6]) {
    case 0:
        if (p[0x2B] == 3) {
            p[6]++;
            func_80042354(1, 1);
        }
        break;
    case 1:
        p[6] = 2;
        func_80040CDC(p, D_80140F7C_8010, D_8013CA80);
        p[0x70] = 1;
        break;
    case 2:
        func_80041098(p);
        if (p[0x70] == 0xFF) {
            p[6] = 0;
            func_80042310();
        }
        break;
    }
}

typedef struct {
    s16 v[3];
} S16x3;
typedef struct {
    u8 x[8];
} S8;
void func_80115810(u8 *p)
{
    switch (p[6]) {
    case 0:
        if (p[0x2B] == 3) {
            p[6]++;
            func_80042354(1, 1);
        }
        break;
    case 1:
        p[6] = 2;
        func_80040CDC(p, D_80140F7C_8010, D_8013CAB0);
        p[0x70] = 1;
        break;
    case 2:
        func_80041098(p);
        if (p[0x70] == 0xFF) {
            p[6] = 0;
            func_80042310();
        }
        break;
    }
}

void func_801158E0(u8 *p)
{
    switch (p[6]) {
    case 0:
        if (p[0x2B] == 3) {
            p[6]++;
            func_80042354(1, 1);
        }
        break;
    case 1:
        p[6] = 2;
        func_80040CDC(p, D_80140F7C_8010, D_8013CAB0);
        p[0x70] = 1;
        break;
    case 2:
        func_80041098(p);
        if (p[0x70] == 0xFF) {
            p[6] = 0;
            func_80042310();
        }
        break;
    }
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801159B0);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80115B48);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80115E04);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801160CC);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8011632C);

void func_801164D0(s32 arg0) {
    s32 temp_s0;

    temp_s0 = arg0 + 0x2C;
    func_800313A0(0x606, temp_s0, -0xA, arg0 + 0x54);
    func_8003116C(0x607, temp_s0, -0xA);
}

void func_80116518(u8 *a)
{
    u8 *p = a + 0x2C;

    *(s32 *)(a + 0x2C) += *(s16 *)(a + 0x4E) << 8;
    *(s32 *)(a + 0x30) += *(s16 *)(a + 0x50) << 8;
    *(s32 *)(a + 0x34) += *(s16 *)(a + 0x52) << 8;
    *(s16 *)(a + 0x58) += 0x800;
    func_800313A0(0x606, p, -0xA, a + 0x54);
    *(s16 *)(a + 0x58) -= 0x800;
    func_8003116C(0x607, p, -0xA);
}

void func_801165BC(void *arg0) {
    M2C_UNK var_a0;

    var_a0 = 0x612;
    if (M2C_FIELD(arg0, s16 *, 0x52) >= 0) {
        var_a0 = 0x60F;
    }
    func_8003116C(var_a0, arg0 + 0x2C, -0xA);
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801165F8);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801166F4);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801169D0);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80116BE4);

extern u8 D_800BF9BC;
extern S16x3 D_8013CF34[];
s32 func_8011711C(void *a0, s32 a1)
{
    s16 *row = D_8013CF34[D_800BF9BC & 0xF].v;

    return row[a1];
}

void func_80132418();
s32 func_80117154(s16 a)
{
    switch (a) {
    case 8:
        return 0x32;
    case 4:
        return 0x34;
    case 2:
        return 0x33;
    case 1:
        return 0x35;
    }
    return 0x36;
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801171BC);

extern u8 D_8013B24C[];
s32 func_80117404(u8 *p)
{
    u8 *s = D_800ECF58;

    if (func_800519E0(p, 0xF, *(s32 *)(s + 0x50), D_8013B24C) != 0) {
        return 0;
    }
    p[0xB] = 0;
    p[0] = 9;
    *(s16 *)(p + 0x80) = 0x55;
    *(s16 *)(p + 0x82) = 0xAA;
    *(s16 *)(p + 0x84) = 0x80;
    *(s16 *)(p + 0x86) = 0x100;
    p[0x2B] = 0;
    p[0x29] = 0;
    *(s16 *)(p + 0x54) = 0;
    *(s16 *)(p + 0x56) = 0;
    *(s16 *)(p + 0x58) = 0;
    p[0xB] = (p[0xB] & 0xC0) | 0x80;
    *(s32 *)(p + 0x3C) = *(s32 *)(s + 0x38);
    return 1;
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801174AC);

extern u8 D_8013B2C4[];
s32 func_801177EC(u8 *p)
{
    u8 *s = D_800ECF58;

    if (func_800519E0(p, 0xF, *(s32 *)(s + 0x54), D_8013B2C4) != 0) {
        return 0;
    }
    p[0xB] = 0;
    p[0] = 9;
    *(s16 *)(p + 0x80) = 0x55;
    *(s16 *)(p + 0x82) = 0xAA;
    *(s16 *)(p + 0x84) = 0x80;
    *(s16 *)(p + 0x86) = 0xE0;
    p[0x2B] = 0;
    p[0x29] = 0;
    *(s16 *)(p + 0x54) = 0;
    *(s16 *)(p + 0x56) = 0;
    *(s16 *)(p + 0x58) = 0;
    p[0xB] = (p[0xB] & 0xC0) | 0x80;
    *(s32 *)(p + 0x3C) = *(s32 *)(s + 0x38);
    return 1;
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80117894);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80117984);

extern u8 D_8013B33C[];
s32 func_80117CC4(u8 *p)
{
    u8 *s = D_800ECF58;

    if (func_800519E0(p, 0xF, *(s32 *)(s + 0x58), D_8013B33C) != 0) {
        return 0;
    }
    p[0xB] = 0;
    p[0] = 9;
    *(s16 *)(p + 0x80) = 0x55;
    *(s16 *)(p + 0x82) = 0xAA;
    *(s16 *)(p + 0x84) = 0x80;
    *(s16 *)(p + 0x86) = 0xD0;
    p[0x2B] = 0;
    p[0x29] = 0;
    *(s16 *)(p + 0x54) = 0;
    *(s16 *)(p + 0x56) = 0;
    *(s16 *)(p + 0x58) = 0;
    p[0xB] = (p[0xB] & 0xC0) | 0x80;
    *(s32 *)(p + 0x3C) = *(s32 *)(s + 0x38);
    return 1;
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80117D6C);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80117EE0);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8011807C);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80118238);

INCLUDE_ASM("asm/a05/nonmatchings/a05", f_UpdateWhosTheLiarSisterActorA);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801189B4);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80118A9C);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80118C24);

INCLUDE_ASM("asm/a05/nonmatchings/a05", f_UpdateWhosTheLiarSisterActorB);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8011917C);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80119310);

INCLUDE_ASM("asm/a05/nonmatchings/a05", f_UpdateWhosTheLiarSisterActorC);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801198B8);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80119E24);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8011A03C);

INCLUDE_ASM("asm/a05/nonmatchings/a05", f_UpdateStaticExplosionQuestActor);

extern s32 D_800BF850;
extern u8 D_800BF9C6;
s32 func_8011A5F0(u8 *a)
{
    switch (a[0x78]) {
    case 0:
        if ((D_800BF850 & 0x1F00) == 0x1F00) {
            *(s16 *)(a + 0x40) = 0x1E;
            a[0x78]++;
        }
        break;
    case 1:
        if (--*(s16 *)(a + 0x40) == 0) {
            D_800BF9C6 = 8;
            return 1;
        }
        break;
    }
    return 0;
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8011A678);

extern s8 D_1F800233[];
s32 func_8011A7B4(void *arg0) {
    *((s8 *)D_1F800233) = 0;
    M2C_FIELD(arg0, s16 *, 0x42) = 0;
    M2C_FIELD(arg0, u8 *, 6) = (u8) (M2C_FIELD(arg0, u8 *, 6) + 1);
    return 1;
}

extern s8 D_1F8000F2[];
extern void *D_800BF844;
s32 func_8011A7D4(s32 arg0) {
    u8 temp_v1;
    void *temp_a0;
    void *temp_v0;

    temp_v1 = M2C_FIELD(arg0, u8 *, 0x78);
    switch (temp_v1) {                              /* irregular */
    case 0:
        temp_v0 = func_8006FB0C(arg0, 0x18);
        M2C_FIELD(arg0, void **, 0x14) = temp_v0;
        D_800BF844 = temp_v0;
        temp_a0 = M2C_FIELD(arg0, void **, 0x14);
        if (temp_a0 != NULL) {
            M2C_FIELD(temp_a0, s16 *, 0x60) = 0x60;
            M2C_FIELD(temp_a0, s16 *, 0x62) = 0x30;
            M2C_FIELD(temp_a0, s8 *, 0x5E) = 1;
            M2C_FIELD(temp_a0, u8 *, 0x5F) = (u8) (M2C_FIELD(temp_a0, u8 *, 0x5F) | 1);
            M2C_FIELD(arg0, u8 *, 0x78) = (u8) (M2C_FIELD(arg0, u8 *, 0x78) + 1);
        }
        return 0;
    case 1:
        M2C_FIELD(M2C_FIELD(arg0, void **, 0x14), s16 *, 0x56) = (s16) (-(s32) *((u16 *)D_1F8000F2) & 0xFFF);
        return 1;
    default:
        return 0;
    }
}

s32 func_8011A894(s32 arg0) {
    func_8011FB18(arg0, 0xA);
    func_8011FB18(arg0, 0xB);
    func_8011FB18(arg0, 0xC);
    return 1;
}

s32 func_8011A8D8(s32 arg0) {
    s32 temp_a0;

    if (M2C_FIELD(arg0, s16 *, 0x72) == 0) {
        M2C_FIELD(arg0, s32 *, 0x14) = func_801310F8(arg0);
    } else {
        temp_a0 = M2C_FIELD(arg0, s32 *, 0x14);
        if (temp_a0 != 0) {
            M2C_FIELD(temp_a0, s8 *, 4) = 3;
        }
    }
    return 1;
}

extern u8 D_800BFB28;
s32 func_8011A930(u8 *p)
{
    if (D_800BFB28 == 0) {
        p[0x7A] = 0xD;
    } else {
        p[0x7A] = 0x10;
    }
    return 1;
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8011A95C);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8011ACC4);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8011AE5C);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8011B210);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8011B3E8);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8011B9EC);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8011BB94);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8011BCB0);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8011BE44);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8011BFA4);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8011C1D4);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8011C2E4);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8011C790);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8011C988);

s32 func_8011CAA0(void *arg0) {
    return func_80077768((s16) (func_80085690((s16) (M2C_FIELD(arg0, u16 *, 0x64) - M2C_FIELD(arg0, u16 *, 0x36)), (s16) (M2C_FIELD(arg0, u16 *, 0x62) - M2C_FIELD(arg0, u16 *, 0x2E))) * -1), M2C_FIELD(arg0, s16 *, 0x56), 0) != 0;
}

extern s8 D_1F800164[];
extern s8 D_1F800164[];
extern s16 D_800E7FFE;
extern s8 D_1F800160[];
s32 func_8011CB08(u8 *a) {
    s16 dz, dx;

    if (!(D_800E7FFE & 0x8200) && !a[3]) {
        dx = *(u16 *)D_1F800160 - M2C_FIELD(a, u16 *, 0x2E);
        dz = *(u16 *)D_1F800164 - M2C_FIELD(a, u16 *, 0x36);
        return func_80077768((s16)-func_80085690(dz, dx), M2C_FIELD(a, s16 *, 0x56), 0) != 0;
    }
    return 0;
}

extern u8 D_80141E14_7ad9[];
void func_8011CB9C(u8 *a, s16 x, s16 y, s16 z)
{
    func_80077CFC(a, D_80141E14_7ad9, 6, 6);
    a[0xBF] = 1;
    if (a[0xBE] != 0) {
        *(s16 *)(a + 0x44) = -x;
    } else {
        *(s16 *)(a + 0x44) = x;
    }
    *(s16 *)(a + 0x4A) = y;
    *(s16 *)(a + 0x50) = z;
}

extern M2C_UNK D_80141E14;
void func_8011CC1C(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 6) == 0) {
        M2C_FIELD(arg0, u8 *, 0x1B) = (u8) (M2C_FIELD(arg0, u8 *, 0x1B) & 0xBF);
        func_80051B04(M2C_FIELD(arg0, s32 *, 0xC0), 0x19, 8);
        func_80077C40(arg0, &D_80141E14, 0x1C);
        M2C_FIELD(M2C_FIELD(arg0, void **, 0xC4), s16 *, 0x38) = 0x1000;
        M2C_FIELD(M2C_FIELD(arg0, void **, 0xC4), s16 *, 0x3A) = 0x1000;
        M2C_FIELD(M2C_FIELD(arg0, void **, 0xC4), s16 *, 0x3C) = 0x1000;
        func_80026100(4);
        M2C_FIELD(arg0, s16 *, 0x84) = 0x32;
        M2C_FIELD(arg0, s16 *, 0x86) = 0x92;
        M2C_FIELD(arg0, u8 *, 6) = (u8) (M2C_FIELD(arg0, u8 *, 6) + 1);
    }
}

s32 func_8011CCBC(u8 *p)
{
    switch (p[0xBF]) {
    case 1:
        if (*(s16 *)(p + 0x4A) >= 0) {
            p[0xBF] = 2;
        }
    case 2:
        *(s16 *)(p + 0x4A) += *(s16 *)(p + 0x50);
        if (*(s16 *)(p + 0x4A) > 0x2800) {
            *(s16 *)(p + 0x4A) = 0x2800;
            return 1;
        }
    default:
        return 0;
    }
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8011CD30);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8011D70C);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8011DA2C);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8011DDC0);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8011E000);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8011E3AC);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8011E4C4);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8011E870);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8011EB84);

u8 func_8011EC58(u8 *a, s32 k)
{
    if (!(a[0x29] & 0x80)) {
        if (k) {
            *(s16 *)(a + 0x32) += 0x10;
        }
        func_8004766C(a);
        if (func_80049250(a, 0, (s16)(*(s16 *)(a + 0x86) - *(s16 *)(a + 0x84))) != 1) {
            return 0;
        }
        a[0x29] |= 0x40;
    }
    return a[0x29];
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8011ECEC);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8011EDCC);

void func_8011EEBC(void *arg0, s16 arg1) {
    if (M2C_FIELD(arg0, u8 *, 0xBE) == 0) {
        M2C_FIELD(arg0, s16 *, 0x44) = arg1;
        return;
    }
    M2C_FIELD(arg0, s16 *, 0x44) = (s16) -arg1;
}

void func_8011EEDC(u8 *p, s32 a1)
{
    if (p[0xBE] == 0) {
        *(s16 *)(p + 0x56) = D_1F8001A0;
        if (a1) {
            *(s16 *)(p + 0x58) = D_1F8001A2;
        }
    } else {
        *(s16 *)(p + 0x56) = (D_1F8001A0 + 0x800) & 0xFFF;
        if (a1) {
            *(s16 *)(p + 0x58) = (0x1000 - D_1F8001A2) & 0xFFF;
        }
    }
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8011EF40);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8011F1BC);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8011F374);

INCLUDE_ASM("asm/a05/nonmatchings/a05", f_UpdateReturnedKujaraActor);

u8 *func_8011FB18(void *a0, u8 a1)
{
    u8 *r = func_8007A980(3, 2, 0);

    if (r) {
        r[2] = 0x2E;
        r[3] = a1;
        *(void **)(r + 0x1C) = f_UpdateReturnedKujaraActor;
        *(void **)(r + 0x10) = a0;
        r[0x28] |= 0x80;
    }
    return r;
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8011FB88);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8011FE08);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8011FF44);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80120160);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80120378);

INCLUDE_ASM("asm/a05/nonmatchings/a05", f_UpdateIceBlockAndSculptureQuestActor);

extern u8 D_8013E454[];
extern u8 D_800BF9C5;
s32 func_80120B48(u8 *p)
{
    s32 s = p[6];

    switch (s) {
    case 0:
        if (p[0x2B] == 3) {
            p[6] = 1;
            func_80042354(1, 1);
            return 0;
        }
        if (D_800BF9C5 != 2) {
            return 0;
        }
        *(s16 *)(p + 0x56) = -0x200;
        p[5]++;
        func_80077C40(p, D_80140F7C_8010, 0x19);
        return 0;
    case 1:
        p[6] = 2;
        func_80040CDC(p, D_80140F7C_8010, D_8013E454);
        p[0x70] = s;
        break;
    case 2:
        func_80041098(p);
        if (p[0x70] != 0xFF) {
            return 0;
        }
        p[6] = 0;
        func_80042310();
        return 1;
    }
    return 0;
}

extern u8 D_8013E474[];
s32 func_80120C64(u8 *p)
{
    switch (p[6]) {
    case 0:
        p[6] = 1;
        break;
    case 1:
        if (p[0x2B] != 3) {
            return 0;
        }
        p[6] = 2;
        func_80042354(1, 1);
        return 0;
    case 2:
        p[6]++;
        func_80040CDC(p, D_80140F7C_8010, D_8013E474);
        p[0x70] = 1;
        break;
    case 3:
        func_80041098(p);
        if (p[0x70] != 0xFF) {
            return 0;
        }
        p[6] = 0;
        func_80042310();
        return 1;
    }
    return 0;
}

extern u8 D_8013E51C[];
s32 func_80120D50(u8 *p)
{
    switch (p[6]) {
    case 0:
        p[6] = 1;
        func_80077C40(p, D_80140F7C_8010, 0x17);
        *(s16 *)(p + 0x56) = -0xC8;
        break;
    case 1:
        if (p[0x2B] != 3) {
            return 0;
        }
        p[6] = 2;
        func_80042354(1, 1);
        return 0;
    case 2:
        p[6]++;
        func_80040CDC(p, D_80140F7C_8010, D_8013E51C);
        p[0x70] = 1;
        break;
    case 3:
        func_80041098(p);
        if (p[0x70] != 0xFF) {
            return 0;
        }
        p[6] = 0;
        func_80042310();
        return 1;
    }
    return 0;
}

extern u8 D_8013E618[];
s32 func_80120E58(u8 *p)
{
    switch (p[6]) {
    case 0:
        if (p[0x2B] == 3) {
            p[6]++;
            func_80042354(1, 1);
        }
        return 0;
    case 1:
        p[6] = 2;
        func_80040CDC(p, D_80140F7C_8010, D_8013E618);
        p[0x70] = 1;
        break;
    case 2:
        func_80041098(p);
        if (p[0x70] == 0xFF) {
            p[6] = 0;
            func_80042310();
            return 1;
        }
        return 0;
    default:
        return 0;
    }
    return 0;
}

typedef struct { s16 x, y, w, h; } ClutRect;
extern u8 D_80140F7C_8010[];
extern u8 D_8013E6F8[];
typedef struct { s16 m[3][3]; s16 pad; s32 t[3]; } AreaMatrix;
typedef struct { s16 x, y, z, pad; } AreaSVec;
typedef struct { u8 pad[0x28]; AreaMatrix m; } AreaScratchD0;
s32 func_80120F34(u8 *p) {
    switch (p[6]) {
    case 0:
        if (p[0x2B] == 3) {
            p[6] = 1;
            func_80042354(1, 1);
        }
        break;
    case 1:
        p[6] = 2;
        func_80040CDC(p, D_80140F7C_8010, D_8013E6F8);
        p[0x70] = 1;
        break;
    case 2:
        func_80041098(p);
        if (p[0x70] == 0xFF) {
            p[6] = 0;
            func_80042310();
            return 1;
        }
        break;
    }
    return 0;
}

extern u8 D_8013E738[];
s32 func_80121010(u8 *p) {
    switch (p[6]) {
    case 0:
        if (p[0x2B] == 3) {
            p[6] = 1;
            func_80042354(1, 1);
        }
        break;
    case 1:
        p[6] = 2;
        func_80040CDC(p, D_80140F7C_8010, D_8013E738);
        p[0x70] = 1;
        break;
    case 2:
        func_80041098(p);
        if (p[0x70] == 0xFF) {
            p[6] = 0;
            func_80042310();
            return 1;
        }
        break;
    }
    return 0;
}

extern u8 D_8013E778[];
s32 func_801210EC(u8 *p) {
    switch (p[6]) {
    case 0:
        if (p[0x2B] == 3) {
            p[6] = 1;
            func_80042354(1, 1);
        }
        break;
    case 1:
        p[6] = 2;
        func_80040CDC(p, D_80140F7C_8010, D_8013E778);
        p[0x70] = 1;
        break;
    case 2:
        func_80041098(p);
        if (p[0x70] == 0xFF) {
            p[6] = 0;
            func_80042310();
            return 1;
        }
        break;
    }
    return 0;
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801211C8);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801215BC);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801217E8);

extern u8 D_800BF80F;
extern u8 D_800BFB02;
extern M2C_UNK D_8013EAC0;
extern M2C_UNK D_80140F7C;
void func_80121A50(void *arg0) {
    u16 temp_v0;
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 6);
    switch (temp_v1) {                              /* irregular */
    case 0:
        if (D_800BF80F == 0) {
            M2C_FIELD(arg0, u8 *, 6) = 1U;
            func_80042354(1, 1);
            if ((u8) D_800BF870.pad1[0x159] < 9U) {
                D_800BF870.pad1[0x159] += 1;
            }
            D_800BF870.pad1[0x152] = 0;
            return;
        }
        return;
    case 1:
        M2C_FIELD(arg0, u8 *, 6) = 2U;
        func_80040CDC(arg0, &D_80140F7C, &D_8013EAC0);
        M2C_FIELD(arg0, u8 *, 0x70) = 1U;
        return;
    case 2:
        func_80041098(arg0);
        if (M2C_FIELD(arg0, u8 *, 0x70) == 0xFF) {
            if (D_800BFB02 == 0) {
                M2C_FIELD(arg0, s8 *, 5) = 6;
                M2C_FIELD(arg0, u8 *, 6) = 0U;
                func_80042310();
                return;
            }
            M2C_FIELD(arg0, u16 *, 0x40) = 0x3CU;
            M2C_FIELD(arg0, u8 *, 6) = (u8) (M2C_FIELD(arg0, u8 *, 6) + 1);
            return;
        }
        break;
    case 3:
        temp_v0 = M2C_FIELD(arg0, u16 *, 0x40) - 1;
        M2C_FIELD(arg0, u16 *, 0x40) = temp_v0;
        if ((temp_v0 << 0x10) == 0) {
            M2C_FIELD(arg0, s8 *, 5) = 6;
            M2C_FIELD(arg0, u8 *, 6) = 1U;
        }
        break;
    }
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80121BA0);

INCLUDE_ASM("asm/a05/nonmatchings/a05", f_UpdateKujaraWashingExpertActor);

extern u8 D_8013E798[];
extern u8 D_8013EDD0[];
extern u8 D_8013EE10[];
extern u8 D_800BFA11;
extern u8 D_800BF9C3;
void func_801223FC(u8 *p)
{
    s32 s = p[6];

    switch (s) {
    case 0:
        if (p[0x2B] == 3) {
            p[6] = 1;
            D_800BFA11 = 1;
            func_80042354(1, 3);
        }
        break;
    case 1:
        p[6] = 2;
        func_80040CDC(p, D_80140F7C_8010, D_8013E798);
        p[0x70] = s;
        break;
    case 2:
        func_80041098(p);
        if (p[0x70] == 0xFF) {
            p[6]++;
            func_80042310();
            p[4] = 3;
        }
        break;
    }
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801224E4);

extern u8 D_8013E820[];
void func_801225CC(u8 *p)
{
    switch (p[6]) {
    case 0:
        if (p[0x2B] == 3) {
            p[6]++;
            func_80042354(1, 1);
        }
        break;
    case 1:
        p[6] = 2;
        func_80040CDC(p, D_80140F7C_8010, D_8013E820);
        p[0x70] = 1;
        break;
    case 2:
        func_80041098(p);
        if (p[0x70] == 0xFF) {
            p[6]++;
        }
        break;
    }
}

extern u8 D_8013E8B0[];
void func_801226A4(u8 *p)
{
    switch (p[6]) {
    case 0:
        if (p[0x2B] == 3) {
            p[6]++;
            func_80042354(1, 1);
        }
        break;
    case 1:
        p[6] = 2;
        func_80040CDC(p, D_80140F7C_8010, D_8013E8B0);
        p[0x70] = 1;
        break;
    case 2:
        func_80041098(p);
        if (p[0x70] == 0xFF) {
            p[6]++;
            func_80042310();
        }
        break;
    }
}

extern u8 D_8013EC00[];
extern u8 D_8013EBD0[];
extern u8 D_800BF92E;
void func_80122780(u8 *p)
{
    switch (p[6]) {
    case 0:
        if (p[0x2B] == 3) {
            p[6] = 1;
            func_80042354(1, 1);
        }
        break;
    case 1:
        p[6] = 2;
        if (D_800BFB02) {
            func_80040CDC(p, D_80140F7C_8010, D_8013EC00);
        } else {
            func_80040CDC(p, D_80140F7C_8010, D_8013EBD0);
        }
        p[0x70] = 1;
        break;
    case 2:
        func_80041098(p);
        if (p[0x70] == 0xFF) {
            if (D_800BF92E == 0xFF) {
                p[5] = 7;
            }
            p[6] = 0;
            func_80042310();
        }
        break;
    }
}

extern u8 D_8013E868[];
void func_80122888(u8 *p)
{
    switch (p[6]) {
    case 0:
        if (p[0x2B] == 3) {
            p[6]++;
            func_80042354(1, 1);
        }
        break;
    case 1:
        p[6] = 2;
        func_80040CDC(p, D_80140F7C_8010, D_8013E868);
        p[0x70] = 1;
        break;
    case 2:
        func_80041098(p);
        if (p[0x70] == 0xFF) {
            p[6]++;
        }
        break;
    }
}

extern u8 D_8013ED18[];
void func_80122960(u8 *p)
{
    s32 s = p[6];
    u8 *g;

    switch (s) {
    case 0:
        if (D_800BF80F == 0) {
            p[6] = 1;
            func_80042354(1, 1);
            g = (u8 *)&D_800BF870;
            if (g[0x15A] < 9) {
                g[0x15A]++;
            }
            g[0x153] = 0;
        }
        break;
    case 1:
        p[6] = 2;
        func_80040CDC(p, D_80140F7C_8010, D_8013ED18);
        p[0x70] = s;
        break;
    case 2:
        func_80041098(p);
        if (p[0x70] == 0xFF) {
            p[5] = 9;
            p[6] = 0;
            func_80042310();
        }
        break;
    }
}

extern u8 D_8013ED98[];
void func_80122A54(u8 *p)
{
    switch (p[6]) {
    case 0:
        if (p[0x2B] == 3) {
            p[6]++;
            func_80042354(1, 1);
        }
        break;
    case 1:
        p[6] = 2;
        func_80040CDC(p, D_80140F7C_8010, D_8013ED98);
        p[0x70] = 1;
        break;
    case 2:
        func_80041098(p);
        if (p[0x70] == 0xFF) {
            p[6] = 0;
            func_80042310();
        }
        break;
    }
}

void func_80122B24(u8 *p)
{
    s32 s = p[6];

    switch (s) {
    case 0:
        if (D_800BF80F == 0) {
            p[6] = 1;
            func_80042354(1, 1);
            D_800BF9C3 = 0;
        }
        break;
    case 1:
        p[6] = 2;
        func_80040CDC(p, D_80140F7C_8010, D_8013EDD0);
        p[0x70] = s;
        break;
    case 2:
        func_80041098(p);
        if (p[0x70] == 0xFF) {
            p[5] = 9;
            p[6] = 0;
            func_80042310();
        }
        break;
    }
}

void func_80122BFC(u8 *p)
{
    s32 s = p[6];

    switch (s) {
    case 0:
        if (D_800BF80F == 0) {
            p[6] = 1;
            func_80042354(1, 1);
            D_800BF9C3 = 0;
        }
        break;
    case 1:
        p[6] = 2;
        func_80040CDC(p, D_80140F7C_8010, D_8013EE10);
        p[0x70] = s;
        break;
    case 2:
        func_80041098(p);
        if (p[0x70] == 0xFF) {
            p[5] = 9;
            p[6] = 0;
            func_80042310();
        }
        break;
    }
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80122CD4);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80122E10);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80123108);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80123318);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80123880);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80123CE8);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801240E4);

extern u8 D_800E7EAA;
extern u8 D_80142108[];
/* func_801266E8, inlined */
static inline void func_801266E8_inl(u8 *a, u8 *b, s32 k)
{
    s16 dx, dz;

    if (k == 0) {
        dx = *(u16 *)(b + 0x2E) - *(u16 *)(a + 0x2E);
        dz = *(u16 *)(b + 0x36) - *(u16 *)(a + 0x36);
    } else {
        dx = *(u16 *)(a + 0x2E) - *(u16 *)(b + 0x2E);
        dz = *(u16 *)(a + 0x36) - *(u16 *)(b + 0x36);
    }
    a[0xBE] = func_80077768((s16)func_80085690(-dz, dx), *(s16 *)(a + 0x60), 0);
    func_8004130C(a, 0);
    a[0x46] = a[0xBE];
}
void func_801244DC(u8 *a)
{
    s32 n, d, v, t;
    s16 m;

    switch (a[6]) {
    case 0:
        a[6] = 1;
        func_801266E8_inl(a, D_800E7E80, H(a, 0x64));
        func_80077C40(a, D_80142108, 3);
        n = a[0x1B] * 3 + 1;
        if (n >= 0x14) {
            n = 0x13;
        }
        v = 0x34800;
        d = 0x20;
        d -= D_800BF85C;
        d -= n;
        v = v / d;
        H(a, 0x6A) = d;
        H(a, 0x4A) = -v;
        H(a, 0x50) = v / d;
        if (a[0x2A] == D_800E7EAA) {
            func_80074590(0x8A, 0, -0x14);
        }
        break;
    case 1:
        *(s32 *)(a + 0x30) += H(a, 0x4A) << 8;
        m = H(a, 0x4A) + H(a, 0x50);
        H(a, 0x4A) = m;
        if (H(a, 0x50) < m) {
            a[6]++;
            H(a, 0x50) = H(a, 0x50) * 2;
        }
        break;
    case 2:
        *(s32 *)(a + 0x30) += H(a, 0x4A) << 8;
        m = H(a, 0x4A) + H(a, 0x50);
        H(a, 0x4A) = m;
        if (m <= 0) {
            H(a, 0x4A) = 0x7FFF;
        }
        func_8004766C(a);
        a[0x29] |= func_80049250(a, 0, (s16)(H(a, 0x86) - H(a, 0x84)));
        if (a[0x29] != 0) {
            func_80049674(a);
            if (a[0x46] & 1) {
                H(a, 0x56) = (D_1F8001A0 - 0x800) & 0xFFF;
            } else {
                H(a, 0x56) = D_1F8001A0;
            }
            {
                u16 y = D_1F8001A2;
                u16 x = D_1F8001A0;
                H(a, 0x58) = y;
                H(a, 0x60) = x;
                H(a, 0x62) = y;
            }
        } else {
            func_80049760(a);
        }
        if (a[0x29] != 0) {
            a[5] = 10;
            a[6] = 0;
            if (a[0x2A] == D_800E7EAA) {
                func_80074590(0x89, 0, -0x14);
            }
            func_8003116C(0, a + 0x2C, -0x32);
        }
        break;
    }
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80124828);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80124A64);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80124FE4);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801251F4);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80125560);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801257E8);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80125A20);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80125BA4);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8012640C);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801264D0);

void func_80126598(void *arg0, s32 arg1) {
    s32 temp_lo;
    s32 temp_lo_2;
    s32 temp_v1;

    M2C_FIELD(arg0, u16 *, 0x58) = (u16) (M2C_FIELD(arg0, u16 *, 0x58) + 0x200);
    if (arg1 == 0) {
        M2C_FIELD(arg0, s32 *, 0x30) = (s32) (M2C_FIELD(arg0, s32 *, 0x30) + (func_80083E80(M2C_FIELD(arg0, s16 *, 0x52)) * M2C_FIELD(arg0, s16 *, 0x44) * 0x10));
    }
    temp_v1 = (s32) (func_80083F50(M2C_FIELD(arg0, s16 *, 0x52)) * M2C_FIELD(arg0, s16 *, 0x44)) >> 4;
    temp_lo = M2C_FIELD(arg0, s16 *, 0x48) * temp_v1;
    temp_lo_2 = M2C_FIELD(arg0, s16 *, 0x4C) * temp_v1;
    M2C_FIELD(arg0, s32 *, 0x2C) = (s32) (M2C_FIELD(arg0, s32 *, 0x2C) + temp_lo);
    M2C_FIELD(arg0, s32 *, 0x34) = (s32) (M2C_FIELD(arg0, s32 *, 0x34) + temp_lo_2);
    if (!(M2C_FIELD(arg0, u8 *, 0x46) & 8)) {
        M2C_FIELD(arg0, s16 *, 0x56) = func_80085690(-temp_lo_2, temp_lo);
    }
}

s32 func_80126664(u8 *a, u8 *b)
{
    s16 dx = *(s16 *)(a + 0x2E) - *(s16 *)(b + 0x2E);
    s16 dz = *(s16 *)(a + 0x36) - *(s16 *)(b + 0x36);
    s16 dy = *(s16 *)(a + 0x32) - *(s16 *)(b + 0x32);
    return func_80084080(dx * dx + dz * dz + dy * dy);
}

void func_801266E8(u8 *a, u8 *b, s32 k)
{
    s16 dx, dz;

    if (k == 0) {
        dx = *(u16 *)(b + 0x2E) - *(u16 *)(a + 0x2E);
        dz = *(u16 *)(b + 0x36) - *(u16 *)(a + 0x36);
    } else {
        dx = *(u16 *)(a + 0x2E) - *(u16 *)(b + 0x2E);
        dz = *(u16 *)(a + 0x36) - *(u16 *)(b + 0x36);
    }
    a[0xBE] = func_80077768((s16)func_80085690(-dz, dx), *(s16 *)(a + 0x60), 0);
    func_8004130C(a, 0);
    a[0x46] = a[0xBE];
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80126788);

void func_80126844(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s16 *, 0x44) = (s16) ((s32) (arg1 << 8) / (s16) M2C_FIELD(arg0, s16 *, 0x6A));
}

void func_80126880(u8 *p, s32 a1)
{
    s32 n = p[0x1B] + 1;
    s32 d;
    s32 v;

    if (n >= 0x14) {
        n = 0x13;
    }
    d = 0x22;
    d -= D_800BF85C;
    d -= n;
    v = (a1 << 9) / d;
    *(s16 *)(p + 0x44) = v;
    *(s16 *)(p + 0x4E) = -(v / d);
}

void func_80126924(u8 *a)
{
    switch (a[6]) {
    case 0:
        a[6]++;
        *(s16 *)(a + 0x40) = 0x5A;
        func_80077C40(a, D_80142108, 9);
        break;
    case 1:
        if (--*(s16 *)(a + 0x40) == 0) {
            a[5] = func_80123108(a);
            a[6] = 0;
        }
        break;
    }
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801269B8);

void func_80126AB4(void) {
}

extern s32 D_800BF854;
extern u16 D_1F8000EE;
void func_80126ABC(u8 *a, s32 k)
{
    u8 *e = D_800E8008;
    s32 n;

    *(s16 *)(e + 0x3A) = *(s16 *)(a + 0x2E);
    *(s16 *)(e + 0x3E) = *(s16 *)(a + 0x32);
    *(s16 *)(e + 0x42) = *(s16 *)(a + 0x36);
    *(s16 *)(e + 0x6C) = -D_1F8000EE;
    n = D_800BF854;
    if (k == 0) {
        *(s16 *)(e + 0x6E) = 0x120;
        if (n < 3) {
            *(s16 *)(e + 0x70) = 0x200;
        } else {
            *(s16 *)(e + 0x70) = -0x200;
        }
    } else {
        *(s16 *)(e + 0x6E) = 0x80;
        *(s16 *)(e + 0x70) = 0;
    }
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80126B34);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80126CD4);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80126E4C);

u8 *func_80127168(void *a0, s32 a1)
{
    u8 *r;

    if (D_800BFA49 & 1) {
        return 0;
    }
    r = func_80072DDC(a0, 0, 2, 0x50);
    if (r) {
        *(void **)(r + 0x1C) = func_80126E4C;
        r[3] = a1;
    }
    return r;
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801271CC);

void func_801272EC(void *arg0) {
    func_8004D4C4(0x3B, 1);
    func_8004B0D8(arg0);
    M2C_FIELD(arg0, s8 *, 4) = 3;
    D_800BF870.pad1[0x1D8] |= 1;
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80127340);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801274F8);

typedef struct { u8 pad[0x48]; s32 unk48; } AreaState808;
extern s8 D_1F80017C[];
typedef struct { s16 x, y, z; } AreaVec3s;
extern AreaVec3s D_8013EED8[];
void func_8012761C(u8 *a) {
    s16 i;

    switch (a[6]) {
    case 0:
        if (--M2C_FIELD(a, s16 *, 0x40) <= 0) {
            a[6]++;
        }
        break;
    case 1:
        if (!(*(u16 *)D_1F80017C & 0xF)) {
            M2C_FIELD(a, s16 *, 0xB8) = D_8013EED8[M2C_FIELD(a, s16 *, 0x7A)].x;
            M2C_FIELD(a, s16 *, 0xBA) = D_8013EED8[M2C_FIELD(a, s16 *, 0x7A)].y;
            M2C_FIELD(a, s16 *, 0xBC) = D_8013EED8[M2C_FIELD(a, s16 *, 0x7A)].z;
            M2C_FIELD(a, s16 *, 0x7A) = (M2C_FIELD(a, s16 *, 0x7A) + 1) & 7;
        }
        break;
    }
    if ((s16)func_80127F18(a)) {
        func_80127E30(a, 0);
        a[5] = 3;
        a[6] = 0;
        M2C_FIELD(a, s16 *, 0x6C) = 0;
    }
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80127734);

void func_801279B4(u8 *a)
{
    s32 r = 0;
    s32 t;
    u8 *g;

    switch (a[6]) {
    case 0:
        M2C_FIELD(*(u8 **)(a + 0xC0), u16 *, 0x38) += M2C_FIELD(a, u16 *, 0x4E);
        M2C_FIELD(*(u8 **)(a + 0xC0), u16 *, 0x3A) -= M2C_FIELD(a, u16 *, 0x50);
        if (M2C_FIELD(*(u8 **)(a + 0xC0), u16 *, 0x3A) < M2C_FIELD(a, s16 *, 0x74) - M2C_FIELD(a, s16 *, 0x40)) {
            M2C_FIELD(*(u8 **)(a + 0xC0), u16 *, 0x3A) = M2C_FIELD(a, s16 *, 0x74) - M2C_FIELD(a, s16 *, 0x40);
            r = 1;
        }
        t = r;
        break;
    case 1:
        M2C_FIELD(*(u8 **)(a + 0xC0), u16 *, 0x38) -= M2C_FIELD(a, u16 *, 0x4E);
        M2C_FIELD(*(u8 **)(a + 0xC0), u16 *, 0x3A) += M2C_FIELD(a, u16 *, 0x50);
        if (M2C_FIELD(a, s16 *, 0x74) + M2C_FIELD(a, s16 *, 0x40) < M2C_FIELD(*(u8 **)(a + 0xC0), u16 *, 0x3A)) {
            M2C_FIELD(*(u8 **)(a + 0xC0), u16 *, 0x3A) = M2C_FIELD(a, s16 *, 0x74) + M2C_FIELD(a, s16 *, 0x40);
            r = 1;
        }
        t = r;
        break;
    default:
        t = r;
    }
    if (t) {
        M2C_FIELD(a, s16 *, 0x40) -= M2C_FIELD(a, s16 *, 0x4A);
        if (M2C_FIELD(a, s16 *, 0x40) <= 0) {
            M2C_FIELD(*(u8 **)(a + 0xC0), u16 *, 0x3A) = M2C_FIELD(a, s16 *, 0x74);
            if (M2C_FIELD(a, s16 *, 0x6C) != 0) {
                M2C_FIELD(*(u8 **)(a + 0xC0), u16 *, 0x38) = M2C_FIELD(a, s16 *, 0x64);
                M2C_FIELD(*(u8 **)(a + 0xC0), u16 *, 0x3A) = M2C_FIELD(a, s16 *, 0x66);
                a[5] = 0;
                a[6] = 0;
                M2C_FIELD(a, s16 *, 0x40) = 0x14;
            } else {
                a[5] = 4;
            }
            return;
        }
        a[6] = 1 - a[6];
    }
    if (M2C_FIELD(a, s16 *, 0x6C) == 0) {
        if (a[0x5E] == 0) {
            if (a[0x29] != 0 && a[6] == 0) {
                g = D_800E7E80;
                if (!(g[0x145] & 1) && g[0x164] == 0) {
                    M2C_FIELD(g, u16 *, 0x32) += 5;
                }
            }
        } else {
            func_80127E30(a, a[0x5E]);
            a[6] = 1;
            M2C_FIELD(a, s16 *, 0x6C) = 1;
        }
    } else if ((s16)func_80127F18(a)) {
        M2C_FIELD(*(u8 **)(a + 0xC0), u16 *, 0x38) = M2C_FIELD(a, s16 *, 0x64);
        M2C_FIELD(*(u8 **)(a + 0xC0), u16 *, 0x3A) = M2C_FIELD(a, s16 *, 0x66);
        func_80127E30(a, 0);
        a[6] = 0;
        M2C_FIELD(a, s16 *, 0x6C) = 0;
    }
    if (M2C_FIELD(a, s16 *, 0x50) > 0x20) {
        M2C_FIELD(a, s16 *, 0x50)--;
    }
    func_80127F7C(a);
}

void func_80127C4C(u8 *a)
{
    if (a[0x29] == 0) {
        func_80127E30(a, 1);
        a[5] = 3;
        a[6] = 1;
        *(s16 *)(a + 0x6C) = 1;
    }
}

void func_80127C9C(u8 *a) {
    func_80027144(M2C_FIELD(M2C_FIELD(a, u8 **, 0xC0), s32 *, 0x40), a + 0x2C, 0xA00, 0x24);
    func_80074590(0xC, 0, 0);
    M2C_FIELD(a, s16 *, 0x32) -= 0x96;
    func_80027144(M2C_FIELD(M2C_FIELD(a, u8 **, 0xC0), s32 *, 0x40), a + 0x2C, 0xA00, 0x2C);
    func_80074590(0xC, 0, 0);
    if (func_80040B48(0x7F) >= 0) {
        D_800BF870.pad1[0x15B] |= 0x80;
        if (++D_800BF870.pad1[0x1C0] >= 10) {
            func_8004ED94(0x6E, 0x41);
        }
    }
    a[4] = 3;
}

#define F16(p, o) M2C_FIELD(p, s16 *, o)
#define C0(p) M2C_FIELD(p, u8 **, 0xC0)
#define F16(p, o) M2C_FIELD(p, s16 *, o)
#define C0(p) M2C_FIELD(p, u8 **, 0xC0)
void func_80127D70(u8 *a)
{
    switch (F16(a, 0x78)) {
    case 1:
        F16(C0(a), 0xC) += F16(C0(a), 0x14);
        F16(C0(a), 0x14) -= 8;
        if (F16(C0(a), 0x14) < -0x20) {
            F16(a, 0x78) = 0;
            F16(C0(a), 0xC) = 0;
        }
        break;
    case 2:
        F16(C0(a), 0xC) -= F16(C0(a), 0x14);
        F16(C0(a), 0x14) -= 8;
        if (F16(C0(a), 0x14) < -0x20) {
            F16(a, 0x78) = 0;
            F16(C0(a), 0xC) = 0;
        }
        break;
    }
    if (a[0x2B]) {
        F16(a, 0x78) = 0;
        F16(C0(a), 0xC) = 0;
    }
}

void func_80127E30(u8 *a, s16 b)
{
    s32 v = 0x50;

    F16(a, 0x4E) = v;
    F16(a, 0x50) = v;
    switch (b) {
    case 0:
        F16(a, 0x4A) = 0x10;
        F16(a, 0x74) = F16(a, 0x66) - (F16(a, 0x66) >> 4);
        F16(a, 0x40) = F16(a, 0x66) >> 5;
        break;
    case 1:
        F16(a, 0x74) = F16(a, 0x66);
        F16(a, 0x40) = F16(a, 0x66) >> 5;
        F16(a, 0x40) += F16(a, 0x66) >> 6;
        F16(a, 0x4A) = 0x20;
        break;
    case 2:
        F16(a, 0x74) = F16(a, 0x66);
        F16(a, 0x40) = F16(a, 0x66) >> 3;
        F16(a, 0x4E) += 0x70;
        F16(a, 0x50) += 0x70;
        F16(a, 0x4A) = 0x40;
        break;
    }
}

s32 func_80127F18(u8 *a)
{
    s16 v;

    if (a[0x29] != 0) {
    if (*(s16 *)(a + 0x78) == 0) {
        v = *(s16 *)(a + 0x44);
        if (v > 0) {
            *(s16 *)(a + 0x78) = 1;
            *(s16 *)(*(u8 **)(a + 0xC0) + 0x14) = 0x20;
        } else if (v < 0) {
            *(s16 *)(a + 0x78) = 2;
            *(s16 *)(*(u8 **)(a + 0xC0) + 0x14) = 0x20;
        }
    }
    return 1;
    }
    return 0;
}

void func_80127F7C(void *arg0) {
    s32 temp_v0_2;
    u32 temp_v0;

    temp_v0 = (u16) M2C_FIELD(M2C_FIELD(arg0, void **, 0xC0), u16 *, 0x38) >> 5;
    M2C_FIELD(arg0, s16 *, 0x80) = (s16) temp_v0;
    M2C_FIELD(arg0, s16 *, 0x82) = (s16) (temp_v0 * 2);
    temp_v0_2 = (s32) (M2C_FIELD(M2C_FIELD(arg0, void **, 0xC0), u16 *, 0x3A) * 0x113) >> 0xC;
    M2C_FIELD(arg0, s16 *, 0x84) = (s16) temp_v0_2;
    M2C_FIELD(arg0, s16 *, 0x86) = (s16) (temp_v0_2 + 0x32);
}

void func_80127FD0(void *arg0) {
    if (M2C_FIELD(arg0, s16 *, 0x62) == 0) {
        M2C_FIELD(arg0, s16 *, 0x62) = 1;
        func_80051B04(M2C_FIELD(arg0, s32 *, 0xC0), 0xC, 0x52);
        func_8003116C(0x24, arg0 + 0x2C, -0xA);
    }
    M2C_FIELD(arg0, s8 *, 0x2B) = 0;
    M2C_FIELD(arg0, s8 *, 0) = 1;
    M2C_FIELD(arg0, s8 *, 4) = 1;
    M2C_FIELD(arg0, s8 *, 5) = 0;
    M2C_FIELD(arg0, s8 *, 6) = 0;
}

extern s8 D_1F800207[];
s32 func_80128040(void *arg0) {
    if ((D_800BFE56 & 0x20) || (M2C_FIELD(arg0, u8 *, 0x2A) == *((u8 *)D_1F800207))) {
        return 0;
    }
    M2C_FIELD(arg0, s16 *, 0x62) = 0;
    func_80051B04(M2C_FIELD(arg0, s32 *, 0xC0), 0xC, 0x51);
    return 1;
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8012809C);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801284F0);

INCLUDE_ASM("asm/a05/nonmatchings/a05", f_UpdateKujaraWashingShedEntrance);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80128904);

INCLUDE_ASM("asm/a05/nonmatchings/a05", Door);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80128CF0);

INCLUDE_ASM("asm/a05/nonmatchings/a05", f_UpdateKujaraInteriorEntranceActor);

void func_801294DC(s32 arg0) {
    func_80073328();
    func_800735F4(arg0, 0x5C);
}

void func_8012950C(void) {
    func_801284F0();
}

void func_8012952C(u8 *a)
{
    u8 *g = D_800BF808;

    if (g[0xE] != 0 && g[0xF] == a[3]) {
        *(s16 *)(a + 0x2E) = *(s16 *)(a + 0x88) - 0x26D;
        *(s16 *)(a + 0x32) = *(s16 *)(a + 0x8A);
        *(s16 *)(a + 0x36) = *(s16 *)(a + 0x8C) + 0x394;
    } else {
        *(s16 *)(a + 0x2E) = *(s16 *)(a + 0x88);
        *(s16 *)(a + 0x32) = *(s16 *)(a + 0x8A);
        *(s16 *)(a + 0x36) = *(s16 *)(a + 0x8C);
    }
    func_80073328(a);
    func_800735F4(a, 0x58);
}

void func_801295C4(s32 arg0) {
    func_801284F0();
    func_800735F4(arg0, 0x5A);
}

void func_801295F4(s32 arg0) {
    func_80073328();
    func_800735F4(arg0, 0x6E);
}

void func_80129624(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 4);
    switch (temp_v1) {                              /* irregular */
    case 0:
        if (func_80051B70(arg0, 0xC, 0x21) == 0) {
            M2C_FIELD(arg0, u8 *, 0xD) = (u8) (M2C_FIELD(arg0, u8 *, 0xD) | 4);
            M2C_FIELD(M2C_FIELD(arg0, void **, 0xC0), s8 *, 0x3F) = 0x3C;
            M2C_FIELD(arg0, s8 *, 0) = 1;
            M2C_FIELD(arg0, s16 *, 0x80) = 0xA0;
            M2C_FIELD(arg0, s16 *, 0x82) = 0x140;
            M2C_FIELD(arg0, s16 *, 0x84) = 0xA0;
            M2C_FIELD(arg0, s16 *, 0x86) = 0x140;
            M2C_FIELD(arg0, s16 *, 0x58) = 0;
            M2C_FIELD(arg0, s16 *, 0x56) = 0;
            M2C_FIELD(arg0, s16 *, 0x54) = 0;
            if (func_8004766C(arg0) != 0) {
                M2C_FIELD(arg0, u8 *, 4) = (u8) (M2C_FIELD(arg0, u8 *, 4) + 1);
                return;
            }
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

void func_80129730(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 4);
    switch (temp_v1) {                              /* irregular */
    case 0:
        M2C_FIELD(arg0, s16 *, 0x80) = 0x40;
        M2C_FIELD(arg0, s16 *, 0x82) = 0x80;
        M2C_FIELD(arg0, s16 *, 0x84) = 0x1F4;
        M2C_FIELD(arg0, s8 *, 8) = 0;
        M2C_FIELD(arg0, s8 *, 9) = 0;
        M2C_FIELD(arg0, s8 *, 0) = 1;
        M2C_FIELD(arg0, s8 *, 0xB) = 0;
        M2C_FIELD(arg0, s8 *, 0x29) = 0;
        M2C_FIELD(arg0, s16 *, 0x86) = 0x2BC;
        M2C_FIELD(arg0, u8 *, 4) = (u8) (M2C_FIELD(arg0, u8 *, 4) + 1);
        return;
    case 1:
        func_8007778C(arg0);
        M2C_FIELD(arg0, s8 *, 0x29) = 0;
        return;
    case 3:
        func_8007A624(arg0);
        /* fallthrough */
    case 2:
        return;
    }
}

/* func_801298E0, inlined */
static inline void Init_97EC(void *arg0) {
    M2C_FIELD(arg0, s16 *, 0x80) = 0x8C;
    M2C_FIELD(arg0, s16 *, 0x82) = 0x118;
    M2C_FIELD(arg0, s16 *, 0x84) = 0x1F4;
    M2C_FIELD(arg0, s16 *, 0x86) = 0x3E8;
    M2C_FIELD(arg0, s8 *, 0x2A) = 4;
    M2C_FIELD(arg0, s32 *, 0x2C) = 0x35200000;
    M2C_FIELD(arg0, s32 *, 0x30) = 0xCEC80000;
    M2C_FIELD(arg0, s32 *, 0x34) = 0x35E80000;
}
void func_801297EC(u8 *a)
{
    switch (a[4]) {
    case 0:
        a[8] = 0;
        a[9] = 0;
        a[0] = 1;
        a[0xB] = 0;
        a[0x5E] = 0;
        a[0x29] = 0;
        a[4]++;
        if (a[3] == 0) {
            Init_97EC(a);
        }
        *(s16 *)(a + 0x60) = a[3];
        a[3] = 2;
        func_800517F8(a);
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

void func_801298E0(void *arg0) {
    M2C_FIELD(arg0, s16 *, 0x80) = 0x8C;
    M2C_FIELD(arg0, s16 *, 0x82) = 0x118;
    M2C_FIELD(arg0, s16 *, 0x84) = 0x1F4;
    M2C_FIELD(arg0, s16 *, 0x86) = 0x3E8;
    M2C_FIELD(arg0, s8 *, 0x2A) = 4;
    M2C_FIELD(arg0, s32 *, 0x2C) = 0x35200000;
    M2C_FIELD(arg0, s32 *, 0x30) = 0xCEC80000;
    M2C_FIELD(arg0, s32 *, 0x34) = 0x35E80000;
}

void func_801297EC();
u8 *func_80129924(void *a0, u8 a1)
{
    u8 *r = func_80072DDC(0, 1, 4, 0x1F);

    if (r == 0) {
        return 0;
    }
    *(void **)(r + 0x1C) = func_801297EC;
    r[3] = a1;
    *(s16 *)(r + 0x58) = 0;
    *(s16 *)(r + 0x56) = 0;
    *(s16 *)(r + 0x54) = 0;
    *(void **)(r + 0x10) = a0;
    r[0x28] |= 0x80;
    return r;
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8012999C);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80129BF8);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80129E68);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8012A0C8);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8012A244);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8012A634);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8012AA64);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8012ABFC);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8012AEFC);

s32 func_8012B118(u8 *p)
{
    s32 v = D_1F800207_9c67;

    if (v < 4 && v != 0) {
        if (p[0x2A] < 4) {
            func_8010E5C4(p);
            return 1;
        }
    } else if (p[0x2A] == D_1F800207_9c67) {
        func_8010E5C4(p);
        return 1;
    }
    return 0;
}

typedef struct { s32 x, y, z; } V3;
void func_8012B188(u8 *a)
{
    V3 v = *(V3 *)(a + 0x2C);

    ((s16 *)&v)[3] += 0xA0;
    func_8003116C(0xD, &v, -0x64);
    if (a[2] == 0x2F) {
        if (*(s16 *)(a + 0x66) != 0) {
            *(s16 *)(a + 0x66) = 0;
            return;
        }
        func_80074590(0x32, -5, 0);
    } else {
        func_80074590(0x32, -8, 0);
    }
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", f_UpdateIceBlockAndSculptureActor);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8012B824);

typedef struct { u8 pad[0x60]; s32 unk60; s32 unk64; } AreaStateF58;
typedef struct { u8 pad0[7]; u8 unk7; u8 pad8[6]; u8 unkE; u8 unkF; u8 pad10[0x21]; u8 unk31; s16 unk32; } AreaState808_E;
typedef struct { u8 pad[0xC0]; u8 *parts[1]; } AreaPartsOwner;
typedef struct { s16 unk0; s16 x, y, z; } PartPose;
extern PartPose D_8013F1B8[3];
extern PartPose D_8013F1D0[3];
typedef struct { u8 pad[0x5E]; u8 pose; u8 pad2[0xC0 - 0x5F]; s16 *parts[3]; } PosedActor;
typedef struct {
    u8 *ptr;
    u8 *clut;
    s16 x;
    s16 y;
} ClutCycle;
typedef struct { s16 x, y, z, pad; } RingVec;
typedef struct { s16 pos; s16 vel; } RiseMotion;
void func_8012BBDC(PosedActor *a, s32 b, s32 c) {
    s32 i;

    for (i = 0; i < 3; i++) {
        if (b == 0) {
            func_80051B04(a->parts[i], c, i);
            a->parts[i][0] = D_8013F1B8[i].x;
            a->parts[i][1] = D_8013F1B8[i].y;
            a->parts[i][2] = D_8013F1B8[i].z;
        } else {
            func_80051B04(a->parts[i], c, i + 3);
            a->parts[i][0] = D_8013F1D0[i].x;
            a->parts[i][1] = D_8013F1D0[i].y;
            a->parts[i][2] = D_8013F1D0[i].z;
        }
    }
    a->pose = b;
}

extern u8 D_8001B7B0[];
void D_8004C930();
void func_8012BCE8(u8 *a, s32 b) {
    u16 v;
    u8 *p;

    switch (a[5]) {
    case 0:
        if (a[0x29] == 1) {
            a[5]++;
            func_8012BBDC(a, 0, b);
            func_80077C40(a, D_8001B7B0, 0);
            D_800BF870.pad1[0x1A2] |= 1 << a[3];
            func_8004ED94(0x5B, 0x41);
        }
        break;
    case 1:
        if (a[0x29] == 2) {
            F16(a, 0x50) = 0;
            a[5]++;
            func_8003116C(8, a + 0x2C, -0x20);
        }
        break;
    case 2:
        v = (F16(a, 0x50) + 0x100) & 0xFFF;
        F16(a, 0x50) = v;
        if (v == 0) {
            F16(a, 0xBA) = 0x1000;
            a[5]++;
            break;
        }
        if (v == 0xC00) {
            p = func_80072DDC(a, 0, 5, 4);
            if (p != NULL) {
                M2C_FIELD(p, void **, 0x1C) = D_8004C930;
                F16(p, 0x2E) = F16(a, 0x2E);
                F16(p, 0x32) = F16(a, 0x32) - 0x78;
                F16(p, 0x36) = F16(a, 0x36);
                p[3] = 0xC;
            }
            M2C_FIELD(a, u8 **, 0x10) = p;
        }
        F16(a, 0xBA) += (func_80083E80(F16(a, 0x50)) << 8) >> 12;
        break;
    case 3:
        if (M2C_FIELD(a, u8 **, 0x10)[4] == 3) {
            D_1F800137 = 0;
            a[5]++;
        }
        break;
    case 4:
        if (a[0x29] == 1) {
            F16(a, 0x52) = 0;
            F16(a, 0x44) = 0x200;
            a[5]++;
        }
        break;
    case 5:
        F16(a, 0x52) = (F16(a, 0x52) + 0x200) & 0xFFF;
        F16(a, 0x58) = (func_80083E80(F16(a, 0x52)) * F16(a, 0x44)) >> 12;
        if (F16(a, 0x52) == 0) {
            a[5]++;
            F16(a, 0x44) -= 0x80;
            func_8003116C(8, a + 0x2C, -0x20);
        }
        break;
    case 6:
        F16(a, 0x52) = (F16(a, 0x52) + 0x200) & 0xFFF;
        F16(a, 0x58) = (func_80083E80(F16(a, 0x52)) * F16(a, 0x44)) >> 12;
        if (F16(a, 0x52) == 0) {
            a[5]++;
        }
        break;
    case 7:
        if (a[0x29] == 2) {
            D_1F800137 = 0;
            a[5] = 4;
        }
        break;
    }
}

extern u8 D_800BF809;
extern u8 D_8013F1B8_9a3d[];
void func_8012BFA8(u8 *a)
{
    s32 s = a[4];
    u8 *g;

    switch (s) {
    case 0:
        g = D_800ECF58;
        if (func_800519E0(a, 3, *(s32 *)(g + 0x90), D_8013F1B8_9a3d) == 0) {
            *(s32 *)(a + 0x3C) = *(s32 *)(g + 0x94);
            {
                u8 *st = (u8 *)&D_800BF870;
                if (st[3] != 0) {
                    a[4] = 3;
                    break;
                }
                if ((st[0x1A3] >> a[3]) & 1) {
                    a[0x5E] = 0;
                    func_80077C40(a, D_8001B7B0, 0);
                } else {
                    func_8012BBDC(a, 1, 0x24);
                    func_80077C40(a, D_8001B7B0, 1);
                }
            }
            a[0] = 1;
            *(s16 *)(a + 0x80) = 0x190;
            *(s16 *)(a + 0x82) = 0x320;
            *(s16 *)(a + 0x84) = 0xB4;
            *(s16 *)(a + 0x86) = 0xB4;
            a[0x29] = 0;
            a[0x2B] = 0;
            a[4]++;
            if (a[0x5E] == 0) {
                a[5] = 4;
            }
        }
        break;
    case 1:
        if (func_8007778C(a) != 0) {
            func_80076D68(a);
            switch (a[6]) {
            case 2:
                a[0] = s;
                a[6] = 0;
                D_800BF809 = 0;
            case 0:
                if (a[0x2B] == 3) {
                    *(s16 *)(a + 0x40) = 0x1E;
                    a[6]++;
                    if (a[0x5E] == 0) {
                        func_8004ED94(0x62, 0x41);
                    } else {
                        func_8004ED94(0x61, 0x41);
                    }
                    D_800BF809 = 1;
                }
                break;
            case 1:
                if (--*(s16 *)(a + 0x40) == 0) {
                    a[0] = 2;
                    a[6]++;
                }
                break;
            }
            func_8012BCE8(a, 0x24);
            func_800518FC(a);
        }
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

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8012C1F8);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8012C44C);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8012C628);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8012C858);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8012C978);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8012CA78);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8012CE34);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8012D0C8);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8012D340);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8012D5B8);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8012D67C);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8012D908);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8012DBA0);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8012DD44);

void func_8012DE08(u8 *a)
{
    switch (a[6]) {
    case 0:
        if (a[0x29] != 0) {
            a[8] = 0;
            *(s16 *)(a + 0x74) = 0;
            *(s16 *)(a + 0x76) = 0;
            a[6]++;
        } else if (a[0x2B] != 0) {
            *(s16 *)(a + 0x74) = 0;
        }
        break;
    case 1:
        if (a[0x29] == 0) {
            a[8] = 0xF0;
            *(s16 *)(a + 0x76) = 4;
            a[6] = 0;
        }
        break;
    }
}

void func_80133878();
void func_8012DE94(u8 *a)
{
    if (a[0x5E] == 1) {
        a[0x5E] = 0;
        *(s32 *)(a + 0x3C) = D_800ECF80;
        func_80077B38(a, D_80140E40_ebd8, 12);
        func_8003116C(0x24, a + 0x2C, -10);
        *(s16 *)(a + 0x84) = 0x28;
        a[0xD] = 0;
        *(s16 *)(a + 0x86) = 0x50;
    }
    a[0] = 1;
    a[4] = 1;
    a[5] = 0;
}

void func_8012DF18(u8 *p)
{
    p[0] = 1;
    p[4] = 1;
    p[5] = 0;
    if (p[0x5E] == 0) {
        p[0x5E] = 1;
        *(s32 *)(p + 0x3C) = D_800ECF80;
        func_80077B38(p, D_80140E40_ebd8, 8);
        *(s16 *)(p + 0x84) = 100;
        p[0xD] = 1;
        *(s16 *)(p + 0x86) = 0x8C;
    }
}

void func_8012DF8C(void *arg0) {
    M2C_FIELD(arg0, s8 *, 0) = 1;
    M2C_FIELD(arg0, s8 *, 4) = 1;
    M2C_FIELD(arg0, s8 *, 5) = 0;
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8012DFA0);

void func_8012E024(u8 *a) {
    switch (a[4]) {
    case 0:
        M2C_FIELD(a, s16 *, 0x80) = 290;
        M2C_FIELD(a, s16 *, 0x82) = 580;
        M2C_FIELD(a, s16 *, 0x84) = 300;
        a[4] = 1;
        a[0] = 1;
        M2C_FIELD(a, s16 *, 0x86) = 600;
        func_800517F8(a);
        break;
    case 1:
        func_8007778C(a);
        break;
    case 2:
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

extern u8 D_800BF8E7;
extern u8 D_800E7EEF;
void func_8012E0C8(u8 *a)
{
    s16 sp[8];

    switch (a[4]) {
    case 0:
        if (func_80051B70(a, 0xC, 0x5D) == 0) {
            *(s16 *)(a + 0x80) = 0x50;
            *(s16 *)(a + 0x82) = 0xA0;
            *(s16 *)(a + 0x84) = 0x140;
            *(s16 *)(a + 0x86) = 0x140;
            a[0] = 1;
            a[0x2B] = 0;
            a[0x29] = 0;
            *(s16 *)(a + 0x54) = 0;
            *(s16 *)(a + 0x56) = 0x800;
            *(s16 *)(a + 0x58) = 0;
            a[4]++;
        }
        break;
    case 1:
        if (a[0x29] != 0 && D_800BF8E7 == 0) {
            func_80040B48(0x33);
        }
        if (func_8007778C(a) != 0) {
            func_800517F8(a);
        }
        a[0x2B] = 0;
        a[0x29] = 0;
        break;
    case 2:
        switch (a[6]) {
        case 0:
            if (D_800E7EEF != 0x13) {
                a[0] = 1;
                a[4] = 1;
                a[5] = 0;
                a[6] = 0;
                a[0x29] = 0;
                if (func_8007778C(a) != 0) {
                    func_800517F8(a);
                }
            } else {
                a[6] = 1;
                func_80040C00(0x33);
                D_800BF870.pad1[0x1CC] |= 1 << a[3];
                func_8006E1C0(8, &D_800BF870);
                sp[1] = *(s16 *)(a + 0x2E);
                sp[3] = *(s16 *)(a + 0x32) - *(s16 *)(a + 0x84) / 2;
                sp[5] = *(s16 *)(a + 0x36);
                func_8006CBA8(sp);
                func_8003116C(0x37, sp, -0x20);
                func_80027144(*(s32 *)(*(u8 **)(a + 0xC0) + 0x40), sp, 0x700, 8);
                func_80074590(0xC, 0, 0);
                func_80027144(*(s32 *)(*(u8 **)(a + 0xC0) + 0x40), a + 0x2C, 0x700, 8);
                func_80074590(0xC, 0, 0);
            }
            break;
        case 1:
            if (D_800BF809 == 0) {
                a[4] = 3;
                func_8006E1E4();
            }
            break;
        }
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

typedef struct { s16 h[7]; } E8013F238;
extern E8013F238 D_8013F238[];
void func_8012E340(u8 *a, s32 i)
{
    u8 **slot;
    u8 *e = func_8007AAE8();

    slot = (u8 **)(a + i * 4);
    if ((slot[0x30] = e) != NULL) {
        E8013F238 *tb = D_8013F238; s16 *t = tb[i].h;
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
        func_80051B04(slot[0x30], 0x12, i);
        a[9] = i;
        a[8] = i;
        func_80074590(0x80, 0, 0);
    } else {
        a[4] = 3;
    }
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8012E454);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8012E918);

typedef struct { u8 pad[0xC0]; u8 *parts[1]; } PartsOwner;
typedef struct { s16 v[4]; } PartInit;
extern s16 D_800ED098;
typedef struct { s16 v[6]; } PartInit6;
extern PartInit6 D_8013F310[];
void func_8012ECA0(PartsOwner *a)
{
    s32 i;
    u8 *q;

    if (D_800ED098 < 5) {
        a->pad[4] = 3;
        return;
    }
    a->pad[8] = 5;
    a->pad[9] = 5;
    a->pad[0xD] = 0;
    a->pad[0xB] = 0;
    *(s16 *)(a->pad + 0x54) = 0;
    *(s16 *)(a->pad + 0x56) = 0;
    *(s16 *)(a->pad + 0x58) = 0;
    for (i = 0; i < a->pad[8]; i++) {
        q = func_8007AAE8();
        a->parts[i] = q;
        *(s16 *)(q + 6) = -1;
        *(s16 *)(a->parts[i] + 0) = D_8013F310[i].v[0];
        *(s16 *)(a->parts[i] + 2) = D_8013F310[i].v[1];
        *(s16 *)(a->parts[i] + 4) = D_8013F310[i].v[2];
        *(s16 *)(a->parts[i] + 8) = D_8013F310[i].v[3];
        *(s16 *)(a->parts[i] + 0xA) = D_8013F310[i].v[4];
        *(s16 *)(a->parts[i] + 0xC) = D_8013F310[i].v[5];
        func_80051B04(a->parts[i], 0xC, 0xE);
    }
    func_800517F8(a);
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8012EDC8);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8012EF0C);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8012F0F4);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8012F280);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8012F404);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8012F548);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8012F7C0);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8012F8E8);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8012FCE4);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8012FF54);

extern s8 *D_800ECF80_5d21[];
extern void *D_800ECF80_1c35;
extern u8 D_800BF9BE;
/* func_801309B8, inlined */
static inline u8 *Spawn_0AFC(void *a0, u8 a1)
{
    u8 *r = func_80072DDC(0, 1, 3, 0x10);

    if (r) {
        *(void **)(r + 0x1C) = f_UpdateKujaraSummitMechanismActor;
        r[3] = 5;
        r[0x5E] = a1;
        *(void **)(r + 0x10) = a0;
        r[0x28] |= 0x80;
    }
    return r;
}
/* func_80130870, inlined */
static inline void func_80130870_inl(u8 *p)
{
    u8 *g = (u8 *)&D_800BF870;

    if (*(u16 *)(g + 0x5E6) & 0x20) {
        p[4] = 3;
        return;
    }
    if (g[0x5E] != 0xFF) {
        *(s16 *)(p + 0x32) = -0x2B5C;
    } else {
        p[5] = 2;
    }
    func_80051B70(p, 0xC, 0x14);
}
/* func_80130AFC, inlined */
static inline void func_80130AFC_inl(u8 *p)
{
    u8 *g = (u8 *)&D_800BF870;
    s32 k;

    if (*(u16 *)(g + 0x5E6) & 0x20) {
        p[4] = 3;
        return;
    }
    if (g[0x5D] == 0xFF) {
        Spawn_0AFC(p, 1);
        p[5] = 3;
        k = 0x2C;
    } else {
        k = 0x27;
        p[6] = 0;
        g[0x17B] = 0;
    }
    if (func_80051B70(p, 0xC, k) == 0) {
        *(s16 *)(p + 0x56) = -0x177;
    }
}
static inline void flag_inl(u8 *p, s32 k, s32 m)
{
    u8 *g;

    *(s32 *)(p + 0x3C) = (s32)D_800ECF80_5d21[0];
    func_80077B38(p, D_80140E40_ebd8, k);
    p[0xB] = 0x10;
    p[0xD] = 0;
    *(s16 *)(p + 0x5C) = 0;
    *(s16 *)(p + 0x5A) = 0;
    p[0x47] = 0;
    p[8] = 0;
    g = (u8 *)&D_800BF870;
    if (!(g[0x150] & m)) {
        g[0x150] |= m;
        p[0x5E] = 0;
    } else {
        p[0x5E] = 1;
    }
}
/* func_80130DB4, inlined */
static inline void func_80130DB4_inl(u8 *p)
{
    u8 *g;

    *(s32 *)(p + 0x3C) = (s32)D_800ECF80_5d21[0];
    func_80077B38(p, D_80140E40_ebd8, 0xB);
    p[0xB] = 0x10;
    *(s16 *)(p + 0x5A) = -0x400;
    p[0xD] = 0;
    *(s16 *)(p + 0x5C) = 0;
    p[0x47] = 1;
    p[8] = 0;
    g = (u8 *)&D_800BF870;
    if (!(g[0x150] & 1)) {
        g[0x150] |= 1;
        p[0x5E] = 0;
    } else {
        p[0x5E] = 1;
    }
}
void f_UpdateKujaraSummitMechanismActor(u8 *a)
{
    u8 *p;

    switch (a[4]) {
    case 0:
        a[4] = 1;
        switch (a[3]) {
        case 0:
            func_8012ECA0(a);
            break;
        case 1:
            *(s32 *)(a + 0x3C) = D_800ECF80;
            func_80077B38(a, D_80140E40_ebd8, 0xD);
            a[0xD] = 1;
            a[0xB] = 0x11;
            H(a, 0x5C) = 0;
            H(a, 0x7A) = 0x1800;
            H(a, 0x7C) = 0x1800;
            H(a, 0x7E) = 0x1800;
            H(a, 0x5A) = 0;
            a[0x47] = 0;
            a[8] = 0;
            break;
        case 2:
            func_80130870_inl(a);
            break;
        case 3:
        case 4:
            break;
        case 5:
            H(a, 0x2E) = 0x3243;
            if (a[0x5E] != 0) {
                H(a, 0x32) = -0x2FA8;
                H(a, 0x58) = 0;
                a[5] = 2;
            } else {
                H(a, 0x32) = -0x3390;
                H(a, 0x58) = 0x200;
            }
            H(a, 0x36) = 0x463C;
            if (func_80051B70(a, 0xC, 0x54) == 0) {
                H(a, 0xBC) = 0x800;
                H(a, 0xBA) = 0x800;
                H(a, 0xB8) = 0x800;
                H(a, 0x56) = 0;
                H(a, 0x54) = 0;
                H(a, 0x50) = 0x38;
            }
            break;
        case 6:
            func_8012F0F4(a);
            break;
        case 7:
            func_8012F548(a);
            break;
        case 8:
            func_80130AFC_inl(a);
            break;
        case 9:
            if (func_80051B70(a, 0xC, 0x28) == 0) {
                H(a, 0x56) = -0x177;
            }
            break;
        case 10:
            if (func_80051B70(a, 0xC, 0x29) == 0) {
                H(a, 0x56) = -0x177;
            }
            break;
        case 11:
            break;
        case 12:
            *(void **)(a + 0x3C) = D_800ECF80_1c35;
            func_80077B38(a, D_80140E40_ebd8, 0x12);
            a[0xD] = 0;
            H(a, 0x5C) = 0;
            a[0xB] = 0x10;
            H(a, 0x5A) = 0;
            a[0x47] = 0;
            a[8] = 0;
            break;
        case 13:
            func_80130DB4_inl(a);
            break;
        case 14:
            flag_inl(a, 3, 2);
            break;
        case 15:
            flag_inl(a, 5, 4);
            break;
        case 16:
            flag_inl(a, 4, 8);
            break;
        case 17:
            if (func_80051B70(a, 0xC, 0x2A) == 0) {
                H(a, 0x56) = 0x800;
                H(a, 0x58) = 0x400;
                H(a, 0x54) = 0;
                H(*(u8 **)(a + 0xC0), 2) = 0x40;
                H(*(u8 **)(a + 0xC0), 4) = -0x40;
            }
            break;
        }
        break;
    case 1:
        switch (a[3]) {
        case 0:
            func_8012EDC8(a);
            break;
        case 1:
        case 12:
            a[1] = 1;
            func_80077B5C(a);
            break;
        case 2:
            switch (a[5]) {
            case 0:
                if (D_800BF9BE & 4) {
                    H(a, 0x32) -= 8;
                    if (H(a, 0x32) < -0x2F0D) {
                        a[5]++;
                    } else if (!(*(u16 *)D_1F80017C & 3)) {
                        func_80074590(0x8F, 0, 0);
                    }
                }
                break;
            case 1:
                H(a, 0x32) = -0x2F00;
                D_800BF870.pad1[0x14D] |= 8;
                a[5]++;
                break;
            }
            func_800517F8(a);
            a[1] = 1;
            break;
        case 3:
        case 4:
            break;
        case 5:
            func_8012EF0C(a);
            break;
        case 6:
            switch (a[0x5E]) {
            case 0:
                func_8012F280(a);
                break;
            case 1:
            case 2:
                func_8012F404(a);
                break;
            }
            func_800517F8(a);
            a[1] = 1;
            break;
        case 7:
            func_8012F8E8(a);
            break;
        case 8:
            func_8012FCE4(a);
            break;
        case 9:
        case 10:
            if (D_800BF9C6 >= 0x15) {
                a[4] = 2;
            }
            func_800517F8(a);
            a[1] = 1;
            break;
        case 11:
            break;
        case 13:
        case 14:
        case 15:
        case 16:
            if (a[0x5E] == 0) {
                func_8012FF54(a);
            }
            a[1] = 1;
            func_80077B5C(a);
            break;
        case 17:
            p = *(u8 **)(a + 0x10);
            a[1] = 1;
            H(a, 0x2E) = H(*(u8 **)(p + 0xDC), 0x2C);
            H(a, 0x32) = H(*(u8 **)(p + 0xDC), 0x30);
            H(a, 0x36) = H(*(u8 **)(p + 0xDC), 0x34);
            func_800518FC(a);
            break;
        }
        break;
    case 2:
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

void func_801333F0();
void func_801307E0(u8 *p)
{
    *(s32 *)(p + 0x3C) = D_800ECF80;
    func_80077B38(p, D_80140E40_ebd8, 0xD);
    p[0xD] = 1;
    p[0xB] = 0x11;
    *(s16 *)(p + 0x5C) = 0;
    *(s16 *)(p + 0x7A) = 0x1800;
    *(s16 *)(p + 0x7C) = 0x1800;
    *(s16 *)(p + 0x7E) = 0x1800;
    *(s16 *)(p + 0x5A) = 0;
    p[0x47] = 0;
    p[8] = 0;
}

void func_8013084C(void *arg0) {
    M2C_FIELD(arg0, s8 *, 1) = 1;
    func_80077B5C();
}

void func_80130870(u8 *p)
{
    u8 *g = (u8 *)&D_800BF870;

    if (*(u16 *)(g + 0x5E6) & 0x20) {
        p[4] = 3;
        return;
    }
    if (g[0x5E] != 0xFF) {
        *(s16 *)(p + 0x32) = -0x2B5C;
    } else {
        p[5] = 2;
    }
    func_80051B70(p, 0xC, 0x14);
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801308D8);

u8 *func_801309B8(void *a0, u8 a1)
{
    u8 *r = func_80072DDC(0, 1, 3, 0x10);

    if (r) {
        *(void **)(r + 0x1C) = f_UpdateKujaraSummitMechanismActor;
        r[3] = 5;
        r[0x5E] = a1;
        *(void **)(r + 0x10) = a0;
        r[0x28] |= 0x80;
    }
    return r;
}

u8 *func_80130A2C(void *a0, u8 a1)
{
    u8 *r = func_80072DDC(0, 1, 3, 0x10);

    if (r) {
        *(void **)(r + 0x1C) = f_UpdateKujaraSummitMechanismActor;
        r[3] = 0x6;
        r[0x5E] = a1;
        *(void **)(r + 0x10) = a0;
        r[0x28] |= 0x80;
    }
    return r;
}

s32 func_80130AA0(s32 arg0, s32 arg1) {
    void *var_v0;
    void *var_v1;

    if (arg0 == 0) {
        var_v0 = func_800310F4(arg1, -0x14);
        var_v1 = var_v0;
    } else {
        var_v0 = func_8003116C(arg1, arg0, -0x14);
        var_v1 = var_v0;
    }
    if (var_v1 != NULL) {
        var_v0 = (void *) (M2C_FIELD(var_v1, u8 *, 0x28) | 0x80);
        M2C_FIELD(var_v1, u8 *, 0x28) = (u8) var_v0;
    }
    return (s32) var_v0;
}

void func_80130AFC(u8 *p)
{
    u8 *g = (u8 *)&D_800BF870;
    s32 k;

    if (*(u16 *)(g + 0x5E6) & 0x20) {
        p[4] = 3;
        return;
    }
    if (g[0x5D] == 0xFF) {
        Spawn_0AFC(p, 1);
        p[5] = 3;
        k = 0x2C;
    } else {
        k = 0x27;
        p[6] = 0;
        g[0x17B] = 0;
    }
    if (func_80051B70(p, 0xC, k) == 0) {
        *(s16 *)(p + 0x56) = -0x177;
    }
}

void func_80130BC8(u8 *p)
{
    if (func_80051B70(p, 0xC, 0x28) == 0) {
        *(s16 *)(p + 0x56) = -0x177;
    }
}

void func_80130C00(void *arg0) {
    if ((u8) D_800BF9C6 >= 0x15U) {
        M2C_FIELD(arg0, s8 *, 4) = 2;
    }
    func_800517F8(arg0);
    M2C_FIELD(arg0, s8 *, 1) = 1;
}

void func_80130C48(u8 *p)
{
    if (func_80051B70(p, 0xC, 0x29) == 0) {
        *(s16 *)(p + 0x56) = -0x177;
    }
}

extern u8 D_800BF9C6;
void func_80130C80(void *arg0) {
    if ((u8) D_800BF9C6 >= 0x15U) {
        M2C_FIELD(arg0, s8 *, 4) = 2;
    }
    func_800517F8(arg0);
    M2C_FIELD(arg0, s8 *, 1) = 1;
}

void func_80130CC8(u8 *a)
{
    *(void **)(a + 0x3C) = D_800ECF80_1c35;
    func_80077B38(a, D_80140E40_ebd8, 0x12);
    a[0xD] = 0;
    *(s16 *)(a + 0x5C) = 0;
    a[0xB] = 0x10;
    *(s16 *)(a + 0x5A) = 0;
    a[0x47] = 0;
    a[8] = 0;
}

void func_80130D20(void *arg0) {
    M2C_FIELD(arg0, s8 *, 1) = 1;
    func_80077B5C();
}

u8 *func_80130D44(void *a0, s32 a1)
{
    u8 *r = func_80072DDC(0, 0, 3, 0x10);

    if (r) {
        *(void **)(r + 0x1C) = f_UpdateKujaraSummitMechanismActor;
        r[3] = a1 + 0xD;
        *(void **)(r + 0x10) = a0;
        r[0x28] |= 0x80;
    }
    return r;
}

void func_80130DB4(u8 *p)
{
    u8 *g;

    *(s32 *)(p + 0x3C) = (s32)D_800ECF80_5d21[0];
    func_80077B38(p, D_80140E40_ebd8, 0xB);
    p[0xB] = 0x10;
    *(s16 *)(p + 0x5A) = -0x400;
    p[0xD] = 0;
    *(s16 *)(p + 0x5C) = 0;
    p[0x47] = 1;
    p[8] = 0;
    g = (u8 *)&D_800BF870;
    if (!(g[0x150] & 1)) {
        g[0x150] |= 1;
        p[0x5E] = 0;
    } else {
        p[0x5E] = 1;
    }
}

void func_80130E40(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x5E) == 0) {
        func_8012FF54();
    }
    M2C_FIELD(arg0, s8 *, 1) = 1;
    func_80077B5C(arg0);
}

void func_80130E88(u8 *p)
{
    u8 *g;

    *(s32 *)(p + 0x3C) = (s32)D_800ECF80_5d21[0];
    func_80077B38(p, D_80140E40_ebd8, 3);
    p[0xB] = 0x10;
    p[0xD] = 0;
    *(s16 *)(p + 0x5C) = 0;
    *(s16 *)(p + 0x5A) = 0;
    p[0x47] = 0;
    p[8] = 0;
    g = (u8 *)&D_800BF870;
    if (!(g[0x150] & 2)) {
        g[0x150] |= 2;
        p[0x5E] = 0;
    } else {
        p[0x5E] = 1;
    }
}

void func_80130F10(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x5E) == 0) {
        func_8012FF54();
    }
    M2C_FIELD(arg0, s8 *, 1) = 1;
    func_80077B5C(arg0);
}

void func_80130F58(u8 *p)
{
    u8 *g;

    *(s32 *)(p + 0x3C) = (s32)D_800ECF80_5d21[0];
    func_80077B38(p, D_80140E40_ebd8, 5);
    p[0xB] = 0x10;
    p[0xD] = 0;
    *(s16 *)(p + 0x5C) = 0;
    *(s16 *)(p + 0x5A) = 0;
    p[0x47] = 0;
    p[8] = 0;
    g = (u8 *)&D_800BF870;
    if (!(g[0x150] & 4)) {
        g[0x150] |= 4;
        p[0x5E] = 0;
    } else {
        p[0x5E] = 1;
    }
}

void func_80130FE0(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x5E) == 0) {
        func_8012FF54();
    }
    M2C_FIELD(arg0, s8 *, 1) = 1;
    func_80077B5C(arg0);
}

void func_80131028(u8 *p)
{
    u8 *g;

    *(s32 *)(p + 0x3C) = (s32)D_800ECF80_5d21[0];
    func_80077B38(p, D_80140E40_ebd8, 4);
    p[0xB] = 0x10;
    p[0xD] = 0;
    *(s16 *)(p + 0x5C) = 0;
    *(s16 *)(p + 0x5A) = 0;
    p[0x47] = 0;
    p[8] = 0;
    g = (u8 *)&D_800BF870;
    if (!(g[0x150] & 8)) {
        g[0x150] |= 8;
        p[0x5E] = 0;
    } else {
        p[0x5E] = 1;
    }
}

void func_801310B0(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x5E) == 0) {
        func_8012FF54();
    }
    M2C_FIELD(arg0, s8 *, 1) = 1;
    func_80077B5C(arg0);
}

void f_UpdateKujaraSummitMechanismActor();
void func_80132418();
u8 *func_801310F8(void *a0)
{
    u8 *r = func_80072DDC(0, 1, 3, 0x10);

    if (r) {
        *(void **)(r + 0x1C) = f_UpdateKujaraSummitMechanismActor;
        r[3] = 0x11;
        *(void **)(r + 0x10) = a0;
        r[0x28] |= 0x80;
    }
    return r;
}

extern PartInit D_8013F3BC[];
void func_8013115C(PartsOwner *a)
{
    s32 i;
    u8 *q;
    PartInit *t;

    if (D_800ED098 < 3) {
        a->pad[4] = 3;
        return;
    }
    a->pad[8] = 3;
    a->pad[9] = 3;
    a->pad[0xD] = 0;
    a->pad[0xB] = 0;
    *(s16 *)(a->pad + 0x54) = 0;
    *(s16 *)(a->pad + 0x56) = 0;
    *(s16 *)(a->pad + 0x58) = 0;
    for (i = 0; i < a->pad[8]; i++) {
        q = func_8007AAE8();
        a->parts[i] = q;
        *(s16 *)(q + 6) = -1;
        *(s16 *)(a->parts[i] + 0) = D_8013F3BC[i].v[0];
        *(s16 *)(a->parts[i] + 2) = D_8013F3BC[i].v[1];
        *(s16 *)(a->parts[i] + 4) = D_8013F3BC[i].v[2];
        *(s16 *)(a->parts[i] + 8) = 0;
        *(s16 *)(a->parts[i] + 0xA) = 0;
        *(s16 *)(a->parts[i] + 0xC) = 0;
        func_80051B04(a->parts[i], 0xC, D_8013F3BC[i].v[3]);
    }
}

void func_80131274(PartsOwner *a)
{
    s32 i;
    u8 *q;
    s32 r;

    if (D_800ED098 < 3) {
        a->pad[4] = 3;
        return;
    }
    a->pad[8] = 3;
    a->pad[9] = 3;
    a->pad[0xD] = 0;
    a->pad[0xB] = 0;
    *(s16 *)(a->pad + 0x54) = 0;
    *(s16 *)(a->pad + 0x56) = 0;
    r = func_8009A450() & 3;
    if (r == 3) {
        r = 1;
    }
    *(s16 *)(a->pad + 0x58) = (r - 1) << 9;
    *(s16 *)(a->pad + 0x2E) = 0x3A7F;
    *(s16 *)(a->pad + 0x32) = -0x1910;
    *(s16 *)(a->pad + 0x36) = 0x20E1;
    for (i = 0; i < a->pad[8]; i++) {
        q = func_8007AAE8();
        a->parts[i] = q;
        *(s16 *)(q + 6) = -1;
        *(s16 *)(a->parts[i] + 0) = 0;
        *(s16 *)(a->parts[i] + 2) = 0;
        *(s16 *)(a->parts[i] + 4) = 0;
        *(s16 *)(a->parts[i] + 8) = 0x800;
        *(s16 *)(a->parts[i] + 0xA) = 0;
        *(s16 *)(a->parts[i] + 0xC) = 0;
        func_80051B04(a->parts[i], 0xC, D_8013F3BC[i].v[3]);
    }
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801313B4);

void func_80131520(PartsOwner *a, s32 b)
{
    s32 i;
    u8 *q;
    u8 *o;

    if (D_800ED098 < 3) {
        a->pad[4] = 3;
        return;
    }
    a->pad[8] = 3;
    a->pad[9] = 3;
    a->pad[0xD] = 0;
    a->pad[0xB] = 0;
    *(s16 *)(a->pad + 0x54) = 0;
    *(s16 *)(a->pad + 0x58) = 0;
    if (a->pad[0x5E] == 0) {
        *(s16 *)(a->pad + 0x56) = 0;
    } else if (a->pad[0x5E] == 1) {
        *(s16 *)(a->pad + 0x56) = 0x200;
    } else {
        *(s16 *)(a->pad + 0x56) = -0x200;
    }
    o = *(u8 **)(a->pad + 0x10);
    *(s16 *)(a->pad + 0xB8) = 0x1000;
    *(s16 *)(a->pad + 0xBA) = 0x1000;
    *(s16 *)(a->pad + 0xBC) = 0x1000;
    *(s16 *)(a->pad + 0x2E) = *(s16 *)(o + 0x2E);
    *(s16 *)(a->pad + 0x32) = *(s16 *)(o + 0x32);
    *(s16 *)(a->pad + 0x36) = *(s16 *)(o + 0x36);
    for (i = 0; i < a->pad[8]; i++) {
        q = func_8007AAE8();
        a->parts[i] = q;
        *(s16 *)(q + 6) = -1;
        *(s16 *)(a->parts[i] + 0) = 0;
        *(s16 *)(a->parts[i] + 2) = 0;
        *(s16 *)(a->parts[i] + 4) = 0;
        *(s16 *)(a->parts[i] + 8) = 0x800;
        *(s16 *)(a->parts[i] + 0xA) = 0;
        *(s16 *)(a->parts[i] + 0xC) = 0;
        *(s16 *)(a->parts[i] + 0x38) = 0x2000;
        *(s16 *)(a->parts[i] + 0x3A) = 0x2000;
        *(s16 *)(a->parts[i] + 0x3C) = 0x2000;
        func_80051B04(a->parts[i], 0xC, D_8013F3BC[i + b].v[3]);
    }
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801316C4);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80131824);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80131988);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80131B18);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80131C90);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80131E10);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80131F80);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80132154);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801322E0);

extern M2C_UNK D_80140E40;
/* func_80132AC8, inlined */
static inline void func_80132AC8_inl(u8 *a)
{
    u8 *g = (u8 *)&D_800BF870;

    if (g[0x1A1] < 2 || g[0xBE] == 0xFF) {
        func_80051B70(a, 0xC, 0x55);
        a[0x5E] = 0;
    } else {
        func_80051B70(a, 0xC, 0x56);
        a[0x5E] = 1;
    }
    a[0xD] |= 4;
    (*(u8 **)(a + 0xC0))[0x3F] = 0xE0;
}
/* func_80132B5C, inlined */
static inline void func_80132B5C_inl(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x3C) = (s32) D_800ECF80;
    func_80077B38(arg0, &D_80140E40, (func_8009A450() & 3) + 0xE);
    M2C_FIELD(arg0, s8 *, 0xD) = 0;
    M2C_FIELD(arg0, s16 *, 0x5C) = 0;
    M2C_FIELD(arg0, s8 *, 0xB) = 0x10;
    M2C_FIELD(arg0, s16 *, 0x5A) = 0;
    M2C_FIELD(arg0, s8 *, 0x47) = 0;
    M2C_FIELD(arg0, s8 *, 8) = 0;
    M2C_FIELD(arg0, s8 *, 0x5E) = (s8) (func_8009A450() & 3);
    M2C_FIELD(arg0, s16 *, 0x2E) = 0x3A41;
    M2C_FIELD(arg0, s16 *, 0x32) = -0x2D37;
    M2C_FIELD(arg0, s16 *, 0x36) = 0x46BE;
}
void func_80132418(u8 *a)
{
    u8 *o;

    switch (a[4]) {
    case 0:
        a[4] = 1;
        switch (a[3]) {
        case 0:
            func_8013115C(a);
            break;
        case 1:
            func_80131274(a);
            break;
        case 2:
            break;
        case 3:
            func_80131520(a, 0);
            break;
        case 4:
            func_80131824(a);
            break;
        case 5:
            func_80131520(a, 3);
            break;
        case 6:
            func_80132AC8_inl(a);
            break;
        case 7:
            *(s32 *)(a + 0x10) = 0;
            break;
        case 8:
            func_80132B5C_inl(a);
            break;
        }
        break;
    case 1:
        switch (a[3]) {
        case 0:
            if (D_800BF808[0xE] != 0 && D_800BF808[0xF] == 3) {
                func_800517F8(a);
                a[1] = 1;
            }
            break;
        case 1:
            func_801313B4(a);
            break;
        case 2:
            break;
        case 3:
            func_801316C4(a);
            break;
        case 4:
            func_80131B18(a);
            break;
        case 5:
            func_80131C90(a);
            break;
        case 6:
            func_80131F80(a);
            break;
        case 7:
            func_80132154(a);
            break;
        case 8:
            func_801322E0(a);
            break;
        }
        break;
    case 2:
        break;
    case 3:
        if (a[3] == 7) {
            o = *(u8 **)(a + 0x10);
            if (o != NULL) {
                o[4] = 3;
            }
        }
        func_8007A624(a);
        break;
    }
}

void func_80132418();
void func_801326F4(void)
{
    u8 *r = func_80072DDC(0, 0x82, 3, 0x10);

    if (r) {
        *(void **)(r + 0x1C) = func_80132418;
        *(s16 *)(r + 0x2E) = 0x39E0;
        *(s16 *)(r + 0x32) = -0x184C;
        r[3] = 0;
        *(s16 *)(r + 0x36) = 0x1F00;
    }
}

void func_80132750(u8 *p)
{
    u8 *s = D_800BF808;

    if (s[0xE] && s[0xF] == 3) {
        func_800517F8(p);
        p[1] = 1;
    }
}

void func_80132418();
extern u8 D_800BF873;
extern S8 D_8013F530[];
void func_801327A4(void *a0)
{
    u8 *r = func_80072DDC(0, 0x82, 3, 0x10);

    if (r) {
        *(void **)(r + 0x1C) = func_80132418;
        r[3] = 1;
        *(void **)(r + 0x10) = a0;
    }
}

void func_801327F8(void *a0, s32 a1)
{
    u8 *r = func_80072DDC(0, 2, 3, 0x10);

    if (r) {
        *(void **)(r + 0x1C) = func_80132418;
        if (a1 < 3) {
            r[3] = 3;
        } else {
            r[3] = 5;
            a1 -= 3;
        }
        r[0x5E] = a1;
        *(void **)(r + 0x10) = a0;
    }
}

u8 *func_80132874(void *a0, u8 a1)
{
    u8 *r = func_80072DDC(0, 3, 3, 0x10);

    if (r) {
        *(void **)(r + 0x1C) = func_80132418;
        r[3] = 4;
        r[0x5E] = a1;
        *(void **)(r + 0x10) = a0;
    }
    return r;
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801328DC);

void func_801329C0(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 5) == 0) {
        M2C_FIELD(arg0, u8 *, 5) = 1U;
        func_80074590(0x92, 0, 0);
    }
    func_801124AC(arg0);
    func_800517F8(arg0);
    M2C_FIELD(arg0, s8 *, 1) = 1;
}

void func_80132A1C(void *a0, u8 a1)
{
    u8 *r = func_80072DDC(0, 2, 3, 0x10);

    if (r) {
        *(void **)(r + 0x1C) = func_80132418;
        r[3] = 5;
        r[0x5E] = a1;
        *(void **)(r + 0x10) = a0;
    }
}

void func_80132418();
u8 *func_80132A80(void)
{
    u8 *r = func_80072DDC(0, 0, 3, 0x10);

    if (r) {
        *(void **)(r + 0x1C) = func_80132418;
        r[3] = 8;
    }
    return r;
}

void func_80132AC8(u8 *a)
{
    u8 *g = (u8 *)&D_800BF870;

    if (g[0x1A1] < 2 || g[0xBE] == 0xFF) {
        func_80051B70(a, 0xC, 0x55);
        a[0x5E] = 0;
    } else {
        func_80051B70(a, 0xC, 0x56);
        a[0x5E] = 1;
    }
    a[0xD] |= 4;
    (*(u8 **)(a + 0xC0))[0x3F] = 0xE0;
}

void func_80132B54(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x10) = 0;
}

void func_80132B5C(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x3C) = (s32) D_800ECF80;
    func_80077B38(arg0, &D_80140E40, (func_8009A450() & 3) + 0xE);
    M2C_FIELD(arg0, s8 *, 0xD) = 0;
    M2C_FIELD(arg0, s16 *, 0x5C) = 0;
    M2C_FIELD(arg0, s8 *, 0xB) = 0x10;
    M2C_FIELD(arg0, s16 *, 0x5A) = 0;
    M2C_FIELD(arg0, s8 *, 0x47) = 0;
    M2C_FIELD(arg0, s8 *, 8) = 0;
    M2C_FIELD(arg0, s8 *, 0x5E) = (s8) (func_8009A450() & 3);
    M2C_FIELD(arg0, s16 *, 0x2E) = 0x3A41;
    M2C_FIELD(arg0, s16 *, 0x32) = -0x2D37;
    M2C_FIELD(arg0, s16 *, 0x36) = 0x46BE;
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80132BE4);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80132DE4);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8013311C);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801332B0);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801333F0);

u8 *func_801335A0(void *a0, u8 a1)
{
    u8 *r = func_80072DDC(0, 3, 3, 0x10);

    if (r) {
        *(void **)(r + 0x1C) = func_801333F0;
        r[3] = a1;
        *(void **)(r + 0x10) = a0;
        r[0x28] |= 0x80;
    }
    return r;
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8013360C);

void func_801337BC(u8 *a) {
    switch (a[4]) {
    case 0:
        if (func_80051B70(a, 0xC, 0) == 0) {
            a[4]++;
            a[0xD] |= 4;
            M2C_FIELD(a, u8 **, 0xC0)[0x3F] = 0x10;
        }
        break;
    case 1:
        a[1] = 1;
        func_800517F8(a);
        break;
    case 2:
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80133878);

u8 *func_801339A4(void *parent)
{
    u8 *p = func_80072DDC(0, 0, 3, 0x18);

    if (p != NULL) {
    *(void **)(p + 0x1C) = func_80133878;
    p[3] = 0;
    *(void **)(p + 0x10) = parent;
    *(s32 *)(p + 0x3C) = D_800ECF80;
    func_80077B38(p, D_80140E40_ebd8, 9);
    p[0xD] = 0;
    *(s16 *)(p + 0x5C) = 0;
    *(s16 *)(p + 0x5A) = 0;
    p[0x47] = 0;
    p[8] = 0;
        return p;
    }
    return NULL;
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80133A3C);

extern s32 D_800ECF80;
extern M2C_UNK D_80140E40;
void func_80133CCC(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 4);
    switch (temp_v1) {                              /* irregular */
    case 0:
        M2C_FIELD(arg0, s32 *, 0x3C) = (s32) D_800ECF80;
        func_80077B38(arg0, &D_80140E40, M2C_FIELD(arg0, u8 *, 3) + 0x14);
        M2C_FIELD(arg0, s8 *, 0xB) = 0x11;
        M2C_FIELD(arg0, s16 *, 0x7E) = 0x1800;
        M2C_FIELD(arg0, s16 *, 0x7C) = 0x1800;
        M2C_FIELD(arg0, s16 *, 0x7A) = 0x1800;
        M2C_FIELD(arg0, s8 *, 0xD) = 0;
        M2C_FIELD(arg0, s16 *, 0x5C) = 0;
        M2C_FIELD(arg0, s8 *, 0x47) = 0;
        M2C_FIELD(arg0, s16 *, 0x5A) = 0;
        M2C_FIELD(arg0, s8 *, 8) = 0xA;
        M2C_FIELD(arg0, u8 *, 4) = (u8) (M2C_FIELD(arg0, u8 *, 4) + 1);
        return;
    case 1:
        func_80133A3C(arg0);
        return;
    case 3:
        func_8007A624(arg0);
        /* fallthrough */
    case 2:
        return;
    }
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80133DA4);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80133E8C);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80134000);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801344F4);

void func_8013466C(void *arg0) {
    u8 temp_v1;
    void *temp_s1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 4);
    temp_s1 = M2C_FIELD(arg0, void **, 0x10);
    switch (temp_v1) {                              /* irregular */
    case 0:
        func_80134000(arg0, temp_s1);
        M2C_FIELD(arg0, u8 *, 4) = (u8) (M2C_FIELD(arg0, u8 *, 4) + 1);
        return;
    case 1:
        M2C_FIELD(arg0, s16 *, 0x2E) = (s16) (M2C_FIELD(temp_s1, u16 *, 0x2E) + M2C_FIELD(arg0, u16 *, 0x60));
        M2C_FIELD(arg0, s16 *, 0x32) = (s16) (M2C_FIELD(temp_s1, u16 *, 0x32) + M2C_FIELD(arg0, u16 *, 0x62));
        M2C_FIELD(arg0, s16 *, 0x36) = (s16) (M2C_FIELD(temp_s1, u16 *, 0x36) + M2C_FIELD(arg0, u16 *, 0x64));
        if (func_800777FC(arg0) != 0) {
            if (M2C_FIELD(arg0, u8 *, 3) & 0x80) {
                if (M2C_FIELD(arg0, u8 *, 0xBE) == 0) {
                    M2C_FIELD(arg0, u16 *, 0x58) = (u16) M2C_FIELD(temp_s1, u16 *, 0x58);
                } else {
                    M2C_FIELD(arg0, u16 *, 0x58) = (u16) (-(s32) M2C_FIELD(temp_s1, u16 *, 0x58) & 0xFFF);
                }
                func_800517F8(arg0);
                return;
            }
            M2C_FIELD(arg0, u16 *, 0x5A) = (u16) M2C_FIELD(temp_s1, u16 *, 0x58);
            return;
        }
        return;
    case 2:
        func_800777FC(arg0);
        func_801344F4(arg0);
        return;
    case 3:
        func_8007A624(arg0);
        break;
    }
}

void func_801347C0(u8 *a, u8 *b)
{
    a[0x2A] = b[0x2A];
    *(V3 *)(a + 0x2C) = *(V3 *)(b + 0x2C);
    func_8004766C(a, b);
    func_80049760(a);
    if (a[3] & 0x80) {
        s16 v = D_1F8001A0;
        *(s16 *)(a + 0x58) = 0;
        *(s16 *)(a + 0x54) = 0;
        *(s16 *)(a + 0x56) = v;
    } else {
        *(s16 *)(a + 0x5A) = 0;
        *(s16 *)(a + 0x58) = 0;
        *(s16 *)(a + 0x56) = 0;
        *(s16 *)(a + 0x54) = 0;
    }
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8013484C);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80134B74);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80134F1C);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801350B4);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801351DC);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8013544C);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8013590C);

typedef struct {
    s16 x, y, w, h;
} RECT16;
void func_80135ED8(RECT16 *a) {
    RECT16 r;
    u16 buf[16];
    s32 i, j, k;
    u16 c;
    u16 g;
    s32 cr, cg, cb;

    r.w = 16;
    r.h = 1;
    for (i = 0; i < a->w; i += 16) {
        r.x = a->x + i;
        r.y = a->y;
        for (j = 0; j < a->h; j++) {
            func_80081278(&r, buf);
            func_80080F6C(0);
            for (k = 0; k < 16; k++) {
                c = buf[k];
                cg = c >> 5;
                cb = c >> 10;
                cr = c & 0x1F;
                g = cr * 77 + (cg & 0x1F) * 150 + (cb & 0x1F) * 29;
                g >>= 8;
                c &= 0x8000;
                if (g >= 32) {
                    g = 31;
                }
                buf[k] = c | (g << 10) | (g << 5) | g;
            }
            func_80081218(&r, buf);
            func_80080F6C(0);
            r.y++;
        }
    }
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8013606C);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801362CC);

void func_80136434(void)
{
    u32 i;

    if (D_800BF873) {
        for (i = 0; i < 7; i++) {
            func_80135ED8(&D_8013F530[i]);
        }
    }
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80136488);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80136788);

extern u16 *D_800ECF78;
void func_80136CB0(u8 *a)
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
extern s16 D_1F8000F0;
extern s16 D_1F8000F2_a096;
void func_80136CDC(u8 *a)
{
    s32 pad;
    u8 *p = D_800ECF84;
    s32 x, y;
    u16 n;

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
            u16 l1 = *(u16 *)(p + 0xE);
            u16 l0 = *(u16 *)(p + 0x10);
        *(u16 *)(a + 0x2C) = 0x900;
        *(u16 *)(a + 0x2E) = 0x8E8;
        {
            u8 *b0 = p + 0x14;
            u8 *b1 = b0 + l0;
            u8 *b2 = b1 + l1;
        *(u8 **)(a + 0x1C) = b2;
        *(u8 **)(a + 0x18) = b0;
        *(u8 **)(a + 0x14) = b1;
        }
        }
        *(u8 **)(a + 0x34) = *(u8 **)(a + 0x1C);
        *(u16 *)(a + 0x30) = (*(u16 *)(a + 0x2C) * a[0x10]) / 144;
        *(u16 *)(a + 0x32) = (*(u16 *)(a + 0x2E) * a[0x11]) / 144;
        a[0x38] = 1;
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
        y = ((D_1F8000F0 * *(u16 *)(a + 0x2E)) >> 12) + a[0x11] * 8 - 0x20;
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

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80136F28);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8013725C);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801374E0);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801376F4);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8013788C);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80137A50);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80137BDC);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80137D6C);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80137F0C);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801380EC);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80138220);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80138404);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801384F8);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80138758);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80138904);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80138B38);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80138C64);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80138E88);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801390B8);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80139260);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8013951C);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801399E8);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80139C0C);

void func_80139E2C(void)
{
    u8 *r = func_800310F4(0x60D, 0);

    if (r) {
        r[0x28] |= 0x80;
    }
}

#define gte_ldfcdir(r0, r1, r2) __asm__ volatile("ctc2	%0, $21;" "ctc2	%1, $22;" "ctc2	%2, $23" : : "r"(r0), "r"(r1), "r"(r2))
extern s32 D_1F800090[];
void func_80139E6C(u8 *p)
{
    s32 *d = D_1F800090;

    gte_ldfcdir(0, 0, 0);
    *d = *(s32 *)(p + 0x5C);
    func_80031D24(p + 0x2C, p + 0x50, p + 0x48);
    func_80027768(*(s32 *)(p + 0x3C), *(u16 *)(p + 0x44), *(s16 *)(p + 0x32), p[0x29]);
}

void func_80139ED8(u8 *p)
{
    s32 *d = D_1F800090;

    gte_ldfcdir(0, 0, 0);
    *d = *(s32 *)(p + 0x54);
    func_800318A0(p + 0x2C, p + 0x50, p + 0x48);
    func_80027768(*(s32 *)(p + 0x3C), *(u16 *)(p + 0x44), *(s16 *)(p + 0x32), p[0x29]);
}

typedef struct { s32 a, b; } Pair9F44;
typedef struct { Pair9F44 e[14]; } Tbl9F44;
extern Tbl9F44 D_8010A11C;
void func_80139F44(u8 *a)
{
    Tbl9F44 t = D_8010A11C;

    switch (a[4]) {
    case 0:
        *(s16 *)(a + 0x4E) = func_8009A450();
        a[4] = 1;
        a[7] = 0xFF;
    case 1:
        if (++a[7] >= 0xE) {
            a[4] = 2;
            break;
        }
        {
            Pair9F44 *e;
            *(s32 *)(a + 0x34) = *(s32 *)(a + 0x38);
            e = &t.e[a[7]];
            *(s32 *)(a + 0x3C) = e->a;
            *(s32 *)(a + 0x50) = e->b;
        }
        if (func_8002B278(a) == 0) {
            func_80031780(a);
        }
        break;
    case 2:
    case 3:
        func_8007A624(a);
        break;
    }
}

void func_8013A078(u8 *p) {
    s32 *d = D_1F800090;
    s32 i;

    gte_ldfcdir(0, 0, 0);
    *d = 0;
    for (i = 0; i < 4; i++) {
        func_80031AC4(p + 0x2C, p + 0x50, p + 0x48);
        func_80027768(M2C_FIELD(p, s32 *, 0x3C), 0, M2C_FIELD(p, s16 *, 0x32), 0);
        M2C_FIELD(p, s16 *, 0x4E) += 0x400;
    }
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8013A104);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8013A1D0);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8013A2AC);

void func_8013A3B8(void *arg0) {
    if ((u8) M2C_FIELD(M2C_FIELD(arg0, void **, 0x10), u8 *, 4) >= 2U) {
        M2C_FIELD(arg0, s8 *, 4) = 3;
    }
    func_80032918();
}

extern u8 D_8013FA88[];
void func_8013A3F8(u8 *p)
{
    s32 *d = D_1F800090;

    gte_ldfcdir(0, 0, 0);
    *d = *(s32 *)(p + 0x54);
    func_800321D8(p + 0x2C, p + 0x50, p + 0x48);
    func_80027768(D_8013FA88, 0, 0, 0);
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8013A460);

typedef struct { u8 b[4]; } B4;
extern B4 D_8010A2A4;
extern void *D_800ED8C8;
void func_8013A548(u8 *a)
{
    u8 *p = a + 0x50;
    B4 v = D_8010A2A4;
    s32 i = 0;

    do {
        func_800318A0(p, &v, a + 0x48);
        if (i & 1) {
            func_8003F698(*(void **)(a + 0x34), D_800ED8C8, 0);
        } else {
            func_8003F698(*(void **)(a + 0x3C), D_800ED8C8, 0);
        }
        i++;
        p += 0x10;
    } while (i < 3);
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8013A5F0);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8013A700);

void func_8013A7B8(u8 *a)
{
    switch (a[4]) {
    case 0:
        *(s16 *)(a + 0x32) = -0x5A;
        a[4] = 1;
        a[5] = 0x1E;
        *(s32 *)(a + 0x50) = 0;
        {
            s32 h = func_8009A450();
            *(s32 *)(a + 0x54) = (h << 16) | func_8009A450() | 1;
        }
    case 1:
        { u8 c = a[5]; a[5] = c + 0xFF; if (c == 0) {
            a[4] = 2;
        } }
        a[1] = 1;
        *(s32 *)(a + 0x50) += 2;
        break;
    case 2:
    case 3:
        func_8007A624(a);
        break;
    }
}

extern u8 D_1F8000DC[];
s32 func_8013A88C(u8 *a)
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

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8013AA50);

extern s16 D_800BED82;
extern M2C_UNK D_80140508;
extern M2C_UNK D_801406AC;
void func_8013AC40(void) {
    func_80075448(0xB, &D_801406AC, 0x10, D_800BED82);
    func_80075448(0xC, &D_80140508, 0x10, D_800BED82);
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8013AC90);

INCLUDE_ASM("asm/a05/nonmatchings/a05", f_UpdateThreeSistersCutsceneActorC);

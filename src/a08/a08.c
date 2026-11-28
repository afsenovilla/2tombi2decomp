#include "common.h"
#include "game.h"
#include "m2c.h"
#include "gte.h"
#include "psyq/gtemac.h"

extern s8 D_800BF808_c1f7[];
extern u8 D_1F800137;
extern s32 D_1F80009C;
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
typedef struct { s16 x, y, z, pad; } RingVec;
typedef struct { s16 pos; s16 vel; } RiseMotion;

void func_8010A51C(u8 *a, u8 *b) {
    s32 t, u;

    if (D_1F800137 != 0 || D_800BF808_c1f7[5] != 0) {
        return;
    }
    if (M2C_FIELD(a, s16 *, 0x17E) & 0x8200) {
        if (func_8002300C(a, b, 0x20) != 0) {
            if (!(a[0] & 4)) {
                t = (func_80083F50(D_1F80009C + 0x800) * (M2C_FIELD(a, s16 *, 0x80) + 0x20)) >> 12;
                u = func_80083E80(D_1F80009C + 0x800) * (M2C_FIELD(a, s16 *, 0x80) + 0x20);
                M2C_FIELD(a, s16 *, 0x2E) = M2C_FIELD(b, s16 *, 0x2E) + t;
                M2C_FIELD(a, s16 *, 0x36) = M2C_FIELD(b, s16 *, 0x36) - (u >> 12);
            }
            M2C_FIELD(a, s8 *, 0x5F) = func_80077768((s16)(*(u16 *)&D_1F80009C + 0x800), M2C_FIELD(a, s16 *, 0x140), 1) + 2;
        }
    } else if (func_80022F04(a, b) != 0) {
        b[0x29] = 1;
        D_1F800137 = 2;
        D_800BF808_c1f7[0x39] = 1;
    }
}

#define F16(p, o) M2C_FIELD(p, s16 *, o)
#define FU16(p, o) M2C_FIELD(p, u16 *, o)
extern s8 D_800BF80D;
extern u8 D_1F800182;
#define F16(p, o) M2C_FIELD(p, s16 *, o)
#define FU16(p, o) M2C_FIELD(p, u16 *, o)
extern u8 D_1F800182;
void func_8010A670(u8 *a, u8 *b) {
    u8 *q = a + 0x60;
    u32 k;
    s32 s;
    s32 c;

    if (D_1F800137 != 0) {
        return;
    }
    if (D_800BF80D != 0) {
        return;
    }
    if (func_8002300C(a, b, 0x50) == 0) {
        return;
    }
    if (a[0x5F] == 0x10) {
        if ((u16)(FU16(a, 0x84) + (FU16(a, 0x32) - (FU16(b, 0x32) + (FU16(b, 0x86) - FU16(b, 0x84))) + 20)) <= F16(a, 0x86) + 40) {
            k = a[0x46] >> 1;
            if ((s32)k >= 0) {
                if ((s32)k < 2) {
                    s = (func_80083F50(F16(q, 8) + 0x800) * (F16(a, 0x80) + 0x20)) >> 12;
                    c = func_80083E80(F16(q, 8) + 0x800) * (F16(a, 0x80) + 0x20);
                    F16(a, 0x2E) = FU16(b, 0x2E) + s;
                    F16(a, 0x36) = FU16(b, 0x36) - (c >> 12);
                    F16(a, 0x32) = FU16(b, 0x32) + (FU16(b, 0x86) - FU16(b, 0x84));
                } else if ((s32)k < 4) {
                    F16(a, 0x32) = FU16(b, 0x32) + (FU16(b, 0x86) - FU16(b, 0x84));
                    F16(a, 0x2E) = FU16(b, 0x2E);
                    F16(a, 0x36) = FU16(b, 0x36);
                }
            }
            func_8001E860(a, b, 0, 0x100);
        } else {
            func_8001E860(a, b, 0, 0);
        }
        D_1F800182 = 0;
    } else if (!(func_8001E860(a, b, 0, 0) & 0x80)) {
        D_1F800182 = 0;
    }
}

extern u8 **D_1F800158;
extern u8 D_1F80015E;
static inline s32 cyl_test(u8 *a, u8 *b)
{
    s16 dx = *(u16 *)(a + 0x2E) - *(u16 *)(b + 0x2E);
    s16 dz = *(u16 *)(a + 0x36) - *(u16 *)(b + 0x36);
    s32 d = func_80084080(dx * dx + dz * dz);

    if ((u16)d > *(s16 *)(a + 0x80) + *(s16 *)(b + 0x80)) {
        return 0;
    }
    return (u16)((*(u16 *)(a + 0x32) - *(u16 *)(b + 0x32)) + ((*(u16 *)(b + 0x84) + *(u16 *)(a + 0x86)) - *(u16 *)(a + 0x84))) <= *(s16 *)(a + 0x86) + *(s16 *)(b + 0x86);
}
u8 *func_8010A83C(u8 *a)
{
    u8 **l = D_1F800158;
    u8 *p;

    D_1F800182 = D_1F80015E;
    while (D_1F800182 != 0) {
        p = *l;
        D_1F800182--;
        l++;
        if ((p[0] & 1) && p[2] == 1 && p[3] == 0 && cyl_test(a, p)) {
            return p;
        }
    }
    return NULL;
}

extern u8 D_1F800137;
extern u8 D_800BF840;
extern u16 D_1F80009C_efeb;
extern s16 D_1F80018C;
extern s16 D_1F80018E;
extern u16 D_1F80008C_7310;
void func_8010A9A8(u8 *a, u8 *b)
{
    s16 ang;
    s32 d;
    s32 k;
    s16 t;

    if (!(*(u16 *)(a + 0x17E) & 0x200) && func_8002300C(a, b, *(s16 *)(b + 0x80) * 4) != 0) {
        ang = D_1F80009C_efeb + 0x800;
        b[0x2B] = 1;
        if (D_1F800137 == 0) {
            k = *(u16 *)(a + 0x140) - 0x400;
            d = func_80085690(-(s16)(*(u16 *)(b + 0x36) - *(u16 *)(a + 0x36)), (s16)(*(u16 *)(b + 0x2E) - *(u16 *)(a + 0x2E))) << 4;
            t = d - k * 16;
            if (abs(t) < 0x1000) {
                D_1F80018E = 0x4101;
                D_1F80018C = *(u16 *)(a + 0x140) - 0x400;
                D_800BF840 = 0x42;
            } else {
                s32 m = *(u16 *)(a + 0x140) + 0x400;
                t = d - m * 16;
                if (abs(t) < 0x1000) {
                    D_1F80018C = m;
                    D_1F80018E = 0x4201;
                    D_800BF840 = 0x43;
                }
            }
        }
        if (*(s16 *)(a + 0x80) + *(s16 *)(b + 0x80) + 0x50 >= D_1F80008C_7310) {
            b[0x2B] = 2;
            if (*(s16 *)(a + 0x80) + *(s16 *)(b + 0x80) >= D_1F80008C_7310) {
                s32 x = (func_80083F50(ang) * (*(s16 *)(a + 0x80) + *(s16 *)(b + 0x80))) >> 12;
                s32 z = func_80083E80(ang) * (*(s16 *)(a + 0x80) + *(s16 *)(b + 0x80));
                *(s16 *)(a + 0x2E) = *(s16 *)(b + 0x2E) + x;
                *(s16 *)(a + 0x36) = *(s16 *)(b + 0x36) - (z >> 12);
            }
        }
    }
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8010ABB0);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8010AE10);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8010AF38);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8010B104);

typedef struct { u16 x, y, z; } PoolPt;
#define H(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define U(p, o) (*(u16 *)((u8 *)(p) + (o)))
extern u16 D_1F8001A8;
extern u16 D_1F800194;
extern s16 D_1F800196;
extern u16 D_1F8001A0_b0de_1f9a;
extern u16 D_1F8001A2_7766;
extern PoolPt D_801418BC[];
void func_8010B1E8(u8 *a) {
    s32 i;
    PoolPt *p;
    s16 dx;
    s16 dz;

    if (a[0x2A] >= 3) {
        return;
    }
    for (i = 0; i < 3; i++) {
        dx = U(a, 0x2E) - D_801418BC[i].x;
        dz = U(a, 0x36) - D_801418BC[i].z;
        if ((u16)func_80084080(dx * dx + dz * dz) <= H(a, 0x80) + 0x28 &&
            (u16)(U(a, 0x84) + (U(a, 0x32) - D_801418BC[i].y + 0x50)) <= H(a, 0x86) + 0x50) {
            if (H(a, 0x4A) < 0 && func_80023290(a) != 0) {
                a[0x2B] = func_80085690(-dz, dx) >> 4;
                func_80022C0C(a, 1);
            }
            return;
        }
    }
}

#define H(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define U(p, o) (*(u16 *)((u8 *)(p) + (o)))
extern s16 D_1F80019E_3f3f;
extern s16 D_1F8001A4_f18c;
extern u8 D_800BF873;
extern u8 D_1F80027B;
/* func_8010F110, inlined */
static inline void func_8010F110_inl(u8 *a) {
    if (func_8012DE84(a, H(a, 0x32)) != 0) {
        D_1F80019E_3f3f = D_1F8001A4_f18c;
    }
    if (D_1F800137 == 0) {
        a[4] = 1;
    }
    if (a[5] == 0x2A) {
        a[0x181] = 1;
        return;
    }
    if (a[0x78] != 0 && a[5] == 3) {
        a[0x29] = 1;
        a[0x181] = 1;
    } else {
        if (a[0x144] == 1) {
            a[0x144] = 0;
        }
        if (a[5] == 6) {
            a[5] = 0x32;
            a[0x149] = (a[0x149] & 1) | 2;
        } else {
            a[5] = 0x1D;
            a[6] = 0;
        }
    }
    a[7] = 0;
    if (a[0x146] != 0 || a[0x145] == 0) {
        H(a, 0x4A) = 0;
    }
    a[0x145] = 0;
}
void func_8010B328(u8 *a) {
    s8 *g;
    s16 v[6]; /* unused: retail's frame has the 16 bytes */
    s32 k;

    if (D_800BF873 != 0) {
        return;
    }
    g = D_800BF808_c1f7;
    if (g[5] != 0) {
        return;
    }
    if (a[0] == 2) {
        return;
    }
    if (a[0x181] != 0 && (a[4] != 1 || a[5] >= 2)) {
        return;
    }
    func_8010B1E8(a);
    k = U(a, 0x6A) & 0xF00;
    if (!(U(a, 0x6A) & 0x8000)) {
        return;
    }
    g[0x16] = 0;
    if (k == 0x100 || k == 0x200) {
        if (a[4] == 2) {
            return;
        }
        if (a[0x145] & 1) {
            return;
        }
        if (U(a, 0x17E) & 0x100) {
            if (a[0x146] == 4 && D_1F80027B != 0) {
                return;
            }
            if (a[5] == 0x2C) {
                return;
            }
            func_8010F110_inl(a);
            return;
        }
        if (D_1F800137 != 0) {
            return;
        }
        a[0] = 3;
        H(a, 0x6A) = 0;
        a[4] = 2;
        a[5] = 4;
        a[6] = 0;
        a[7] = 0;
    } else if (k == 0x700) {
        if (D_1F800137 != 0) {
            return;
        }
        a[0] = 3;
        a[4] = 2;
        a[5] = 5;
        a[6] = 0;
        a[7] = 0;
    }
}

extern s32 D_1F80009C_baed;
extern s32 D_1F800098;
s32 func_8010B598(u8 *a, u8 *b, u8 *c) {
    s16 dx, dz, dy, e, f, v;
    u16 h, bh, ah;
    u16 r;
    s32 ang, s, t, m;
    s32 o;

    o = 0;
    if (b[3] == 5) {
        o = -70;
    }
    dx = FU16(a, 0x2E) - (FU16(c, 0x2C) + o);
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
        F16(a, 0x2E) = m + (FU16(c, 0x2C) + o);
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

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8010B9FC);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8010BDE4);

void func_8010BF50(u8 *a, u8 *b, u8 *c)
{
    s16 dx;
    s16 dz;
    s16 dy;
    s16 h;
    s16 k;

    if (a[0x145] & 1) {
        return;
    }
    dx = *(u16 *)(a + 0x2E) - *(u16 *)(c + 0x2C);
    dz = *(u16 *)(a + 0x36) - *(u16 *)(c + 0x34);
    if ((u16)func_80084080(dx * dx + dz * dz) > *(s16 *)(a + 0x80) + *(s16 *)(b + 0x80)) {
        return;
    }
    dy = *(u16 *)(a + 0x32) - *(u16 *)(c + 0x30);
    h = *(u16 *)(b + 0x84) + *(u16 *)(a + 0x84);
    if ((u16)(dy + h) > *(s16 *)(a + 0x86) + *(s16 *)(b + 0x86)) {
        return;
    }
    if (dy < 0) {
        k = -h;
    } else {
        k = (*(u16 *)(b + 0x86) - *(u16 *)(b + 0x84)) + (*(u16 *)(a + 0x86) - *(u16 *)(a + 0x84));
    }
    D_1F80009C = func_80085690(-dz, dx);
    b[0x29] = 1;
    *(s32 *)(a + 0x30) = (*(s16 *)(c + 0x30) + k) << 16;
    func_80022C78(a);
}

void func_8010C0BC(u8 *a, u8 *b)
{
    s16 dx = *(s16 *)(a + 0x2E) - *(s16 *)(b + 0x2E);
    s16 dz = *(s16 *)(a + 0x36) - 0x1040;

    if ((u16)func_80084080(dx * dx + dz * dz) <= *(s16 *)(a + 0x80) + *(s16 *)(b + 0x80)
        && (u16)(*(s16 *)(a + 0x32) - *(s16 *)(b + 0x32) + (*(s16 *)(a + 0x84) + *(s16 *)(b + 0x84))) <= *(s16 *)(a + 0x86) + *(s16 *)(b + 0x86)) {
        D_1F80009C = func_80085690(-dz, dx);
        a[0x5F] = func_80077768((s16)D_1F80009C, *(s16 *)(a + 0x140), 1) + 2;
        if (!(a[0] & 4)) {
            s32 temp_s0 = (s32) (func_80083F50(D_1F80009C) * (M2C_FIELD(a, s16 *, 0x80) + M2C_FIELD(b, s16 *, 0x80))) >> 0xC;
            s32 temp_lo = func_80083E80(D_1F80009C) * (M2C_FIELD(a, s16 *, 0x80) + M2C_FIELD(b, s16 *, 0x80));
            M2C_FIELD(a, s16 *, 0x2E) = (s16) (M2C_FIELD(b, u16 *, 0x2E) + temp_s0);
            M2C_FIELD(a, s16 *, 0x36) = (s16) (0x1040 - (temp_lo >> 0xC));
        }
    }
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8010C22C);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8010C378);

static inline void push_inl(u8 *a, u8 *b) {
    s32 s = (func_80083F50(D_1F80009C) * (H(a, 0x80) + H(b, 0x80))) >> 12;
    s32 c = func_80083E80(D_1F80009C) * (H(a, 0x80) + H(b, 0x80));
    H(a, 0x2E) = U(b, 0x2E) + s;
    H(a, 0x36) = U(b, 0x36) - (c >> 12);
}
static inline s32 near_inl(u8 *a, u8 *p) {
    s16 dx = U(a, 0x2E) - U(p, 0x2C);
    s16 dz = U(a, 0x36) - U(p, 0x34);

    if ((u16)func_80084080(dx * dx + dz * dz) > H(a, 0x80) + 0x64) {
        return 0;
    }
    if ((u16)((U(a, 0x32) - U(p, 0x30)) + (u16)(U(a, 0x84) + 0x32)) > H(a, 0x86) + 0x64) {
        return 0;
    }
    D_1F80009C = func_80085690(-dz, dx);
    return 1;
}
void func_8010C538(u8 *a, u8 *b) {
    s32 r;

    if (H(a, 0x16E) == 0) {
        return;
    }
    if (b[0xBF] != 0) {
        return;
    }
    if (b[3] & 0x80) {
        r = func_8001F40C(a, b, 1);
        if (r < 0) {
            return;
        }
    } else {
        r = func_8010C378(a, b, *(s32 *)(b + 0xC0));
        if (r < 0) {
            if (U(a, 0x17E) & 0x200) {
                return;
            }
            if (D_1F800137 != 0) {
                return;
            }
            if (a[0] & 6) {
                return;
            }
            if ((u32)(b[0x46] - 1) >= 2) {
                return;
            }
            if (near_inl(a, *(u8 **)(b + 0xD4)) == 0) {
                return;
            }
            if (b[0x46] == 1 || H(a, 0x16E) == 1) {
                goto tail;
            }
            if (b[0x46] == 2) {
                b[0x46] = 3;
                a[0] = 2;
                b[0] = 2;
                a[5] = 0x18;
                a[6] = 0;
                a[7] = 0;
            }
            return;
        }
    }
    switch (a[0x144]) {
    case 1:
        if (!(b[0] & 0x18) && r < 2) {
            if (b[3] & 0x80) {
                func_8001FDB4(b, -0x7FFF, 3, 0x1C);
            } else if (b[0x5E] != 0) {
                func_8001FDB4(b, -0x7FF7, 3, 0x1C);
            }
            return;
        }
        goto def;
    case 2:
        if (!(b[0] & 0xA)) {
            return;
        }
        if (U(a, 0x17E) & 0x200) {
            return;
        }
        if (a[0] & 4) {
            return;
        }
        push_inl(a, b);
        return;
    default:
    def:
        if (U(a, 0x17E) & 0x200) {
            return;
        }
        if (!(a[0] & 4)) {
            push_inl(a, b);
        }
    tail:
        a[0x2B] = D_1F80009C >> 4;
        func_80022D08(a, b, 1, 0);
        break;
    }
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8010C90C);

void func_8010CD84(u8 *a, u8 *b)
{
    s32 r;

    if (*(u16 *)(a + 0x17E) & 0x200) {
        return;
    }
    r = func_8001F40C(a, b, 0);
    if (r < 0) {
        return;
    }
    if (a[0x144] == 1 && r < 2) {
        if (*(s16 *)(a + 0x17E) & 0x8000) {
            func_8001F830(a, b);
            return;
        }
        func_8001FDB4(b, -0x7FFC, 0x10, 0x1E);
        return;
    }
    if (!(a[0] & 4)) {
        s32 temp_s0 = (s32) (func_80083F50(D_1F80009C) * (M2C_FIELD(a, s16 *, 0x80) + M2C_FIELD(b, s16 *, 0x80))) >> 0xC;
        s32 temp_lo = func_80083E80(D_1F80009C) * (M2C_FIELD(a, s16 *, 0x80) + M2C_FIELD(b, s16 *, 0x80));
        M2C_FIELD(a, s16 *, 0x2E) = (s16) (M2C_FIELD(b, u16 *, 0x2E) + temp_s0);
        M2C_FIELD(a, s16 *, 0x36) = (s16) (M2C_FIELD(b, u16 *, 0x36) - (temp_lo >> 0xC));
    }
    a[0x60] = 1;
    a[0x5F] = func_80077768((s16)D_1F80009C, *(s16 *)(a + 0x140), 1) + 2;
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8010CED8);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8010D334);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8010D9AC);

void func_8010DAF0(u8 *a, u8 *b)
{
    u8 *t = a + 0x60;
    u16 h = *(u16 *)(b + 0x86);

    *(u16 *)(b + 0x86) = *(s16 *)(b + 0x84) * 2 + 0x46;
    if (func_80022F04(a, b) == 0) {
        *(u16 *)(b + 0x86) = h;
        return;
    }
    *(u16 *)(b + 0x86) = h;
    if (a[0x5F] == 0x10) {
        switch (a[0x46] >> 1) {
        case 0:
        case 1: {
            s32 temp_s0 = (s32) (func_80083F50(*(s16 *)(t + 8) + 0x800) * (M2C_FIELD(a, s16 *, 0x80) + M2C_FIELD(b, s16 *, 0x80))) >> 0xC;
            s32 temp_lo = func_80083E80(*(s16 *)(t + 8) + 0x800) * (M2C_FIELD(a, s16 *, 0x80) + M2C_FIELD(b, s16 *, 0x80));
            M2C_FIELD(a, s16 *, 0x2E) = (s16) (M2C_FIELD(b, u16 *, 0x2E) + temp_s0);
            M2C_FIELD(a, s16 *, 0x36) = (s16) (M2C_FIELD(b, u16 *, 0x36) - (temp_lo >> 0xC));
            *(s16 *)(a + 0x32) = *(s16 *)(b + 0x32) + *(s16 *)(a + 0x84);
            break;
        }
        case 2:
        case 3:
            *(s16 *)(a + 0x2E) = *(s16 *)(b + 0x2E);
            *(s16 *)(a + 0x36) = *(s16 *)(b + 0x36);
            *(s16 *)(a + 0x32) = *(s16 *)(a + 0x84) + (*(s16 *)(b + 0x32) + (*(s16 *)(b + 0x86) - *(s16 *)(b + 0x84)));
            break;
        }
    }
    {
        s32 r = func_8001E860(a, b, 0, 0x200);

        b[0x2B] = 1;
        if (!(r & 0x80)) {
            D_1F800182 = 0;
        }
    }
}

extern u16 D_1F80008C;
#define H(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define U(p, o) (*(u16 *)((u8 *)(p) + (o)))
extern u16 D_1F80018E_f9ee;
extern u16 D_1F80018C_c065;
void func_8010DC80(u8 *a, u8 *b)
{
    s32 k;
    s32 g;
    s32 m;
    s32 c;
    s32 x, y;
    if (H(a, 0x17E) & 0x8200) {
        if (func_8002300C(a, b, H(b, 0x80)) == 0) {
            return;
        }
        k = D_1F80009C_efeb + 0x800;
        goto near;
    }
    if (func_8002300C(a, b, H(b, 0x80) * 4) == 0) {
        return;
    }
    k = D_1F80009C_efeb + 0x800;
    b[0x2B] = 1;
    if (D_1F800137 == 0) {
        m = U(a, 0x140) - 0x400;
        g = func_80085690(-(s16)(U(b, 0x36) - U(a, 0x36)), (s16)(U(b, 0x2E) - U(a, 0x2E))) << 4;
        if (abs((s16)(g - m * 16)) < 0x1000) {
            D_1F80018E_f9ee = 0x4100;
            D_1F80018C_c065 = U(a, 0x140) - 0x400;
            D_800BF840 = 0x42;
        } else {
            c = U(a, 0x140) + 0x400;
            if (abs((s16)(g - c * 16)) < 0x1000) {
                D_1F80018C_c065 = c;
                D_1F80018E_f9ee = 0x4200;
                D_800BF840 = 0x43;
            }
        }
    }
    if (D_1F80008C > H(a, 0x80) + H(b, 0x80) + 0x50) {
        return;
    }
    b[0x2B] = 2;
near:
    if (H(a, 0x80) + H(b, 0x80) < D_1F80008C) {
        return;
    }
    x = (func_80083F50((s16)k) * (H(a, 0x80) + H(b, 0x80))) >> 12;
    y = (func_80083E80((s16)k) * (H(a, 0x80) + H(b, 0x80))) >> 12;
    U(a, 0x2E) = U(b, 0x2E) + x;
    U(a, 0x36) = U(b, 0x36) - y;
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8010DEB4);

extern u8 **D_1F800154;
extern u8 D_1F80015C;
extern u8 D_1F800183;
extern u8 D_1F800150;
extern u8 **D_1F80013C;
extern u8 D_1F800144;
#define TOWER_SCAN_LIST(e)                                          \
    {                                                    \
        u8 **m;                                          \
        u8 *o;                                           \
        D_1F800182 = D_1F800150;                         \
        while (D_1F800182 != 0) {                        \
            D_1F800182--;                                \
        }                                                \
        m = D_1F80013C;                                  \
        D_1F800182 = D_1F800144;                         \
        while (D_1F800182 != 0) {                        \
            o = *m;                                      \
            D_1F800182--;                                \
            m++;                                         \
            if ((o[0] & 1) && o[2] == 8) {               \
                func_8002423C(e, o);                     \
            }                                            \
        }                                                \
    }
void func_8010E080(void)
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

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8010E2A4);

extern u8 D_1F800182;
extern u8 D_1F800182;
extern u8 D_1F800182;
extern u8 D_1F800182;
void func_8010E420(void)
{
    u8 **l;
    u8 n = D_1F800144;
    u8 k;

    D_1F800183 = n;
    if (n < 2) {
        return;
    }
    l = D_1F80013C;
    for (D_1F800183 = n - 1; D_1F800183 != 0; D_1F800183--) {
        k = (*l++)[0];
        if (k != 2 && k != 7) {
            for (D_1F800182 = D_1F800183; D_1F800182 != 0; D_1F800182--) {
            }
        }
    }
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8010E4CC);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8010E7C0);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8010EA88);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8010ED98);

extern u8 D_800E7E80[];
extern u8 D_800BF808[];
extern u8 D_800BF80F;
/* func_8010F288, inlined */
static inline void func_8010F288_inl(u8 *p)
{
    if (D_800BF808[0xE] != 0 && p[0x16B] == 8) {
        u16 h = *(u16 *)(D_800BF808 + 0xA);

        if (!(p[0x145] & 1) && !(*(s16 *)(p + 0x32) < (s16)h - *(s16 *)(p + 0x62))) {
            *(s16 *)(p + 0x32) = h - *(s16 *)(p + 0x62);
            func_80022C78(p);
            p[0x29] |= 0x80;
        }
    } else {
        func_8010B328(p);
    }
    if (D_1F800137 == 0 && D_800BF80F == 0) {
        func_8010B104(p);
    }
}
void func_8010EF9C(void)
{
    u8 *p = D_800E7E80;

    func_8002288C(p);
    switch (p[0]) {
    case 0:
    case 6:
        break;
    case 1:
    case 3:
    case 4:
    case 5:
    case 7:
    default:
        func_80022760(p);
        func_8010E4CC(p);
    case 2:
        if (*(u32 *)(p + 0x158) < 2) {
            func_8010E7C0(p);
        }
        break;
    }
    func_80022554();
    func_8010EA88();
    func_8010ED98();
    func_8010E080();
    func_8010E2A4();
    func_8010E420();
    func_8010F288_inl(p);
}

void func_8010F110(u8 *a) {
    if (func_8012DE84(a, H(a, 0x32)) != 0) {
        D_1F80019E_3f3f = D_1F8001A4_f18c;
    }
    if (D_1F800137 == 0) {
        a[4] = 1;
    }
    if (a[5] == 0x2A) {
        a[0x181] = 1;
        return;
    }
    if (a[0x78] != 0 && a[5] == 3) {
        a[0x29] = 1;
        a[0x181] = 1;
    } else {
        if (a[0x144] == 1) {
            a[0x144] = 0;
        }
        if (a[5] == 6) {
            a[5] = 0x32;
            a[0x149] = (a[0x149] & 1) | 2;
        } else {
            a[5] = 0x1D;
            a[6] = 0;
        }
    }
    a[7] = 0;
    if (a[0x146] != 0 || a[0x145] == 0) {
        H(a, 0x4A) = 0;
    }
    a[0x145] = 0;
}

extern u16 D_800BF812;
void func_8010F214(u8 *p)
{
    u16 h = D_800BF812;

    if (!(p[0x145] & 1) && !(*(s16 *)(p + 0x32) < (s16)h - *(s16 *)(p + 0x62))) {
        *(s16 *)(p + 0x32) = h - *(s16 *)(p + 0x62);
        func_80022C78(p);
        p[0x29] |= 0x80;
    }
}

void func_8010F288(u8 *p)
{
    if (D_800BF808[0xE] != 0 && p[0x16B] == 8) {
        u16 h = *(u16 *)(D_800BF808 + 0xA);

        if (!(p[0x145] & 1) && !(*(s16 *)(p + 0x32) < (s16)h - *(s16 *)(p + 0x62))) {
            *(s16 *)(p + 0x32) = h - *(s16 *)(p + 0x62);
            func_80022C78(p);
            p[0x29] |= 0x80;
        }
    } else {
        func_8010B328(p);
    }
    if (D_1F800137 == 0 && D_800BF80F == 0) {
        func_8010B104(p);
    }
}

void func_8010F35C(u8 *a, u8 *b)
{
    s32 r = func_8001F40C(a, b, 1);

    if (r >= 0) {
        b[0x2B] = (*(s32 *)0x1F80009C + 0x800) >> 4;
        if (func_8001FF7C(a, b, r, 1) != 1) {
            b[0] = 2;
            b[4] = 2;
            b[5] = 2;
            b[6] = 0;
        }
    }
}

s32 func_8010F3D8(s32 arg0, s32 arg1) {
    return func_8010B598(arg0, arg1, M2C_FIELD(arg1, s32 *, 0xC0));
}

extern u8 D_1F800182;
extern u8 D_1F800182;
void func_8010F3FC(u8 *a, u8 *b)
{
    s32 v;

    if (func_8002313C(a, b, *(void **)(b + 0xC0)) != 0) {
        func_8001E860(a, b, *(void **)(b + 0xC0), 0x400);
        v = D_1F80009C;
        b[0x2B] = 1;
        b[0x46] = v >> 4;
        if (a[0x5E] != 0) {
            b[0x2B] = 0x81;
        }
        D_1F800182 = 0;
    }
}

void func_8010F47C(void) {
    func_8010BDE4();
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8010F49C);

void func_8010F590(u8 *a, u8 *b)
{
    if (func_80022F04(a, b) != 0) {
        s32 r = func_8001E860(a, b, 0, 0x400);
        if (r & 0x10) {
            D_1F800182 = 0;
            return;
        }
        if (!(r & 0x80)) {
            D_1F800182 = 0;
        }
        b[0x2B] = (a[0x46] & 1) + 2;
    }
}

extern u8 D_800BFAD7;
void func_8010F614(u8 *a, u8 *b)
{
    if (func_80022F04(a, b) != 0) {
        if (b[3] == 0 || D_800BFAD7 == 0) {
            a[0x2B] = *(s32 *)0x1F80009C >> 4;
            func_80022D08(a, b, 1, 0);
        }
        b[0] = 2;
        b[4] = 2;
        b[5] = 2;
        b[6] = 0;
    }
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8010F6A4);

void func_8010F790(void *a0, u8 *a1)
{
    if (a1[0x5E] == 0) {
        func_8002192C(a0, a1, 0);
    }
}

void func_8010F7C0(void *a0, u8 *a1)
{
    s32 v = a1[3];

    if (v < 6) {
        if (v != 0) {
            func_800216B4(a0, a1, 0);
        }
    }
}

extern u8 D_1F800182;
extern u8 **D_1F80013C;
extern u8 D_1F800144;
typedef struct {
    u8 x0;
    u8 pad1;
    s16 x2;
} S4;
typedef struct {
    s16 x0;
    s16 x2;
    u8 pad4[6];
} S10;
typedef struct {
    s16 v[3];
} S16x3;
typedef struct {
    u8 x[8];
} S8;
void func_8010F7FC(void *a0)
{
    u8 **list;
    u8 *e;

    for (D_1F800182 = D_1F800150; D_1F800182 != 0; D_1F800182--) {
    }
    list = D_1F80013C;
    D_1F800182 = D_1F800144;
    while (D_1F800182 != 0) {
        e = *list++;
        D_1F800182--;
        if ((e[0] & 1) && e[2] == 8) {
            func_8002423C(a0, e);
        }
    }
}

extern u8 **D_1F80014C;
extern u8 D_1F800152;
extern s32 D_1F800080;
s32 func_8010F8D4(u8 *a)
{
    u8 **l = D_1F80014C;
    u8 *p;
    D_1F800182 = D_1F800152;
    while (D_1F800182 != 0) {
        p = *l;
        D_1F800182--;
        l++;
        if ((p[0] & 1) && p[2] == 0x58) {
            func_8010D9AC(a, p);
        }
    }
    return D_1F800080;
}

s32 func_8010F98C(u8 *a) {
    u16 k;

    if (D_1F800137 != 0) {
        return 0;
    }
    if ((H(a, 0x16C) & 0xC000) != 0xC000) {
        return 0;
    }
    func_8004766C(a);
    if ((*(s32 *)(a + 0x148) & 0xA0000) == 0xA0000) {
        func_80047B5C(a, 1);
        if (D_1F8001A8 & 2) {
            a[0x61] = 0x20;
            D_1F80018E = 0x1100;
            D_1F800194 = D_1F8001A2_7766 & 0xFFF;
            D_1F800196 = D_1F8001A0_b0de_1f9a & 0xFFF;
            if (a[5] != 0x2A) {
                a[5] = 0x2A;
                a[6] = 0;
            }
            return 3;
        }
    }
    func_80047B5C(a, 0);
    k = D_1F8001A8;
    if (k & 8) {
        D_1F80018E = 0x2000;
        D_1F800194 = D_1F8001A2_7766 & 0xFFF;
        D_1F800196 = D_1F8001A0_b0de_1f9a & 0xFFF;
        if (a[5] != 0x2B) {
            a[5] = 0x2B;
            a[6] = 0;
        }
        return 2;
    }
    if ((*(s32 *)(a + 0x148) & 0x60000) == 0x60000 && (k & 4)) {
        a[0x61] = 0x10;
        D_1F80018E = 0x1000;
        D_1F800194 = D_1F8001A2_7766 & 0xFFF;
        D_1F800196 = D_1F8001A0_b0de_1f9a & 0xFFF;
        if (a[5] != 0x2A) {
            a[5] = 0x2A;
            a[6] = 0;
        }
        return 1;
    }
    return 0;
}

#define W_d1fb(p, o) (*(s32 *)((u8 *)(p) + (o)))
extern u16 D_1F80017C_0fe7;
void func_8010FB44(u8 *a, s32 b) {
    s32 d;
    s16 t;
    s16 v[6];

    if (a[0x145] & 1) {
        return;
    }
    if (a[0x78] != 0) {
        d = 0x64 - U(a, 0x84);
    } else if (H(a, 0x17E) < 0) {
        d = -0xA;
    } else {
        d = -0x14;
    }
    switch (a[7]) {
    case 0:
        func_80058304(a, 2);
        H(a, 0x182) = 0;
        if (func_8012DE84(a, H(a, 0x32)) != 0) {
            D_1F80019E_3f3f = D_1F8001A4_f18c;
        }
        if ((U(a, 0x6A) & 0xF00) == 0x200) {
            {
                s32 k = 0x1400;
                H(a, 0x50) = k;
                a[7] = 2;
                W_d1fb(a, 0x30) -= k << 8;
            }
            break;
        }
        t = U(a, 0x4A) - 0x3200;
        if (t < 0) {
            H(a, 0x50) = 0x1400;
        } else {
            if (t > 0xC00) {
                t = 0xC00;
            }
            H(a, 0x50) = t / 2 + 0x1400;
        }
        a[7]++;
    case 1:
        W_d1fb(a, 0x30) += H(a, 0x50) << 8;
        if ((s16)(H(a, 0x50) -= 0x180) <= 0) {
            a[7]++;
        }
        break;
    case 2:
        if (a[0x78] == 0) {
            func_800312D4(0x903, a + 0x2C, -0xA);
        }
        a[7]++;
    case 3:
    case 4:
        W_d1fb(a, 0x30) -= H(a, 0x50) << 8;
        if (a[7] == 3) {
            H(a, 0x50) = U(a, 0x50) + 0x180;
        } else {
            H(a, 0x50) = U(a, 0x50) + 0x80;
        }
        if (H(a, 0x50) >= 0x1000) {
            H(a, 0x50) = 0x1000;
        }
        if (D_1F80019E_3f3f + (s16)d >= H(a, 0x32)) {
            H(a, 0x32) = D_1F80019E_3f3f;
            func_800312D4(0x909, a + 0x2C, -0xA);
            H(a, 0x32) += d;
            if (a[0x146] == 0 && a[0x78] == 0 && !(a[0x14A] & 2)) {
                a[7] = 6;
            } else {
                a[7] = 5;
            }
            H(a, 0x50) = 0;
        }
        break;
    case 5:
        W_d1fb(a, 0x30) += H(a, 0x50) << 8;
        if ((s16)(H(a, 0x50) += 0x80) >= 0x600) {
            H(a, 0x50) = 0;
            a[7]--;
        }
        break;
    case 6:
        if (b != 0) {
            b = 3;
        } else {
            b = 7;
        }
        if (D_1F80019E_3f3f + (s16)d < H(a, 0x32)) {
            W_d1fb(a, 0x30) -= H(a, 0x50) << 8;
            if ((s16)(H(a, 0x50) += 0x100) >= 0x1000) {
                H(a, 0x50) = 0x1000;
            }
        } else if (a[0x146] != 0 || (a[0x14A] & 2)) {
            a[7] = 5;
        }
        if (!(D_1F80017C_0fe7 & b)) {
            v[1] = U(a, 0x2E) + ((func_80083F50(H(a, 0x56) + 0x800) * 200) >> 12);
            v[3] = D_1F80019E_3f3f + 0x1E;
            v[5] = U(a, 0x36) - ((func_80083E80(H(a, 0x56) + 0x800) * 200) >> 12);
            func_800312D4(8, v, -0x50);
        }
        break;
    }
    if (D_1F80019E_3f3f + H(a, 0x62) / 2 < H(a, 0x32)) {
        a[0x148] = 1;
    } else {
        a[0x148] = 0;
    }
}

extern u16 D_800BFE56;
void func_8010FF9C(u8 *a) {
    s32 m;
    s32 n;
    s32 k;
    s16 v;

    if (!(D_800BFE56 & 0x100)) {
        m = 0x1000;
        n = 0x1800;
    } else {
        m = 0x800;
        n = 0xC00;
    }
    k = (U(a, 0x6A) >> 12) & 7;
    if (k >= 6) {
        if (H(a, 0x142) == 0) {
            if (H(a, 0x182) == 0) {
                if (k == 6) {
                    H(a, 0x182) = 0x200;
                } else {
                    H(a, 0x182) = -0x200;
                }
            } else if (k == 6) {
                H(a, 0x182) = U(a, 0x182) + 0x40;
            } else {
                H(a, 0x182) = U(a, 0x182) - 0x40;
            }
            {
                s16 t = m;
                if (H(a, 0x182) > t) {
                    H(a, 0x182) = m;
                } else if (H(a, 0x182) < -t) {
                    H(a, 0x182) = -m;
                }
            }
        } else {
            if (k == 6) {
                H(a, 0x182) = U(a, 0x182) + (H(a, 0x142) >> 1);
            } else {
                H(a, 0x182) = U(a, 0x182) - (H(a, 0x142) >> 1);
            }
            {
                s16 t = n;
                if (H(a, 0x182) > t) {
                    H(a, 0x182) = n;
                } else if (H(a, 0x182) < -t) {
                    H(a, 0x182) = -n;
                }
            }
        }
    } else {
        v = abs(H(a, 0x182)) - 0x100;
        if (v <= 0) {
            H(a, 0x182) = 0;
        } else if (H(a, 0x182) < 0) {
            H(a, 0x182) = -v;
        } else {
            H(a, 0x182) = v;
        }
    }
}

#define W_d1fb(p, o) (*(s32 *)((u8 *)(p) + (o)))
extern u16 D_1F8001A6;
extern u16 D_800E7E68;
extern u16 D_1F800170;
static inline s32 snap_inl(u8 *a) {
    s32 r;
    u16 t, p, q;

    H(a, 0x16C) = 0;
    H(a, 0x6A) = 0;
    if (func_8012DE84(a, H(a, 0x32)) != 0) {
        if (D_1F80019E_3f3f < D_1F8001A4_f18c - 0x1F4) {
            r = 0;
        } else {
            t = D_1F8001A4_f18c;
            p = D_1F8001A6;
            q = D_1F8001A8;
            D_1F80019E_3f3f = t;
            H(a, 0x6A) = p;
            H(a, 0x16C) = q;
            func_80049674(a);
            r = 1;
            H(a, 0x142) = D_1F8001A2_7766;
        }
    } else {
        r = 0;
    }
    return r;
}
static inline void swim_inl(u8 *a, s32 b) {
    s32 k;
    s16 v;

    func_80056B48(a, 0);
    func_8010FF9C(a);
    W_d1fb(a, 0x2C) += H(a, 0x48) * H(a, 0x182);
    W_d1fb(a, 0x34) += H(a, 0x4C) * H(a, 0x182);
    W_d1fb(a, 0x30) += H(a, 0x4A) * H(a, 0x182);
    if (a[0x16B] == 0 && a[0x61] == 0) {
        func_80054650(a, 0);
    } else {
        a[0x5F] &= 0xFB;
    }
    func_8010FB44(a, b);
    func_80055D5C(a);
    func_80055284(a);
    if (snap_inl(a) == 0) {
        func_80056D44(a, 0);
    } else if (func_80055390(a) == 0) {
        k = 1;
        if (U(a, 0x6A) & 0x10) {
            a[5] = 0x2B;
            a[6] = 0;
        } else {
            k = 0;
        }
        if (k == 0) {
            func_8010F98C(a);
        }
    } else if (a[5] == 6 || a[5] == 2) {
        v = U(a, 0x44) + U(a, 0x182);
        if (v < 0) {
            if (v < -H(a, 0x15E)) {
                v = -U(a, 0x15E);
            }
        } else if (H(a, 0x15E) < v) {
            v = U(a, 0x15E);
        }
        H(a, 0x44) = v;
    }
}
void func_801100F4(u8 *a) {
    func_80076D68(a);
    switch (a[6]) {
    case 0:
        a[0x16A] = 0;
        H(a, 0x182) = 0;
        H(a, 0x50) = 0;
        a[0x17B] = 1;
        H(a, 0x58) = 0;
        a[0x145] = 0;
        func_80053D90(a);
        a[0x181] = 1;
        a[0x146] = 0;
        a[7] = 0;
        a[6]++;
        func_8010FB44(a, 0);
        func_80054D14(a, 0xDC, 4);
        H(a, 0x4A) = 0;
    case 1:
        H(a, 0x58) = 0;
        func_80055E28(a, 1);
        if (!(a[0x14A] & 2)) {
            a[6]++;
        } else if (a[0x149] & 2) {
            func_80054D14(a, 0xDD, 6);
        }
        func_80056878(a, a[0x14A], 0);
        swim_inl(a, 0);
        break;
    case 2:
        func_80055E28(a, 1);
        if (a[0x14A] & 2) {
            func_80054D14(a, 0xDC, 6);
            a[6]--;
            func_80056878(a, a[0x14A], 0);
        } else {
            func_80054D14(a, 0xDB, 6);
            if (D_800E7E68 & D_1F800170) {
                H(a, 0x40) = 8;
                H(a, 0x42) = 1;
                a[6]++;
                func_80056878(a, a[0x14A], 1);
            } else {
                func_80056878(a, a[0x14A], 0);
            }
        }
        swim_inl(a, 0);
        if ((u16)(D_1F80017C_0fe7 % 15) == 0) {
            func_80074590(0x33, 0, 0);
        }
        func_800552B8(a);
        break;
    case 3:
        func_80076D68(a);
        func_80055E28(a, 1);
        if (a[0x14A] & 2) {
            func_80054D14(a, 0xDC, 6);
            a[6] = 1;
            func_80056878(a, a[0x14A], 0);
        } else {
            if (D_800E7E68 & D_1F800170) {
                H(a, 0x40) = 8;
                H(a, 0x42)++;
                func_80056878(a, a[0x14A], H(a, 0x42));
            } else {
                func_80056878(a, a[0x14A], 0);
            }
            if (--H(a, 0x40) == 0) {
                a[6]--;
            }
        }
        swim_inl(a, 1);
        if ((u16)(D_1F80017C_0fe7 % 7) == 0) {
            func_80074590(0x33, 0, 0);
        }
        func_800552B8(a);
        break;
    }
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80110AA0);

extern s32 D_1F800084;
extern u16 D_800ECF54;
void func_801114B8(u8 *a) {
    s32 s;

    switch (a[6]) {
    case 0:
        if (U(a, 0x6A) & 0x20) {
            a[0x147] = 0;
        } else {
            a[0x147] = 1;
        }
        H(a, 0x58) = 0;
        func_80054198(a);
        a[0x61] = 0x21;
        a[0] |= 4;
        if (!(U(a, 0x6A) & 0x40)) {
            if (a[0x147] != 0) {
                H(a, 0x44) = -0x1000;
            } else {
                H(a, 0x44) = 0x1000;
            }
            H(a, 0x40) = 2;
            a[6]++;
            func_80054D14(a, 0xDB, 6);
            snap_inl(a);
        } else {
            a[6] = 6;
            func_80054D14(a, 0x63, 2);
        }
        func_800551C4(a);
        break;
    case 1:
        if ((u16)(D_1F80017C_0fe7 % 7) == 0) {
            func_80074590(0x33, 0, 0);
        }
        func_80076D68(a);
        func_80056B48(a, 0);
        func_8010FB44(a, 0);
        func_80055D5C(a);
        snap_inl(a);
        if ((H(a, 0x16C) & 0xC000) == 0xC000) {
            if (H(a, 0x40) != 0) {
                H(a, 0x40)--;
            } else {
                func_80047B5C(a, 0);
                if (D_1F8001A8 & 8) {
                    D_1F80018E = 0x2000;
                    D_1F800194 = D_1F8001A2_7766 & 0xFFF;
                    D_1F800196 = D_1F8001A0_b0de_1f9a & 0xFFF;
                    a[6]++;
                }
            }
        }
        break;
    case 2:
        a[6]++;
        func_80054D14(a, 0xDC, 6);
        func_80055C9C(a, D_1F800196);
        if (a[0x147] = func_80055E28(a, 0) & 1) {
            D_1F800194 = (D_1F800196 - 0x800) & 0xFFF;
        } else {
            D_1F800194 = D_1F800196;
        }
        func_80054198(a);
        func_8010FB44(a, 0);
        snap_inl(a);
        break;
    case 3:
        func_80076D68(a);
        s = D_1F800194;
        s &= 0xFFF;
        if ((H(a, 0x56) = func_800776F8(s, H(a, 0x56), 0x100)) == s) {
            a[6]++;
        }
        func_8010FB44(a, 0);
        snap_inl(a);
        break;
    case 4:
        func_8004766C(a);
        func_8004960C(a, 0);
        H(a, 0x140) = D_1F800196;
        snap_inl(a);
        func_80076D68(a);
        a[0x61] = 0x20;
        if (U(a, 0x6A) & 0x10) {
            a[6] = 0xC;
        } else {
            if (D_1F800196 == (s16)D_1F800194) {
                a[0x147] = 0;
            } else {
                a[0x147] = 1;
            }
            func_80054198(a);
            a[6]++;
        }
        func_8010FB44(a, 0);
        snap_inl(a);
        break;
    case 11:
        func_80054D14(a, 0xDC, 6);
    case 5:
        func_80076D68(a);
        H(a, 0x172) = 0x1E;
        a[5] = 0x1D;
        a[0x61] = 0;
        a[6] = 1;
        a[0] &= 3;
        func_8010FB44(a, 0);
        snap_inl(a);
        break;
    case 12:
        snap_inl(a);
        if (U(a, 0x6A) & 0x20) {
            a[0x147] = 0;
        } else {
            a[0x147] = 1;
        }
        H(a, 0x58) = 0;
        func_80054198(a);
        if (a[0x147] != 0) {
            H(a, 0x44) = -0x1000;
        } else {
            H(a, 0x44) = 0x1000;
        }
        a[6]++;
        func_80054D14(a, 0xDB, 6);
        func_800551C4(a);
        break;
    case 13:
        if ((u16)(D_1F80017C_0fe7 % 7) == 0) {
            func_80074590(0x33, 0, 0);
        }
        func_80076D68(a);
        func_80056B48(a, 0);
        func_8010FB44(a, 0);
        func_80055D5C(a);
        snap_inl(a);
        if (!(U(a, 0x6A) & 0x10)) {
            func_80054198(a);
            a[6] = 0xB;
        }
        break;
    case 6:
        H(a, 0x6A) = 0;
        a[0x181] = 0;
        a[7] = 0;
        H(a, 0x58) = 0;
        if (a[0x147] == 0) {
            H(a, 0x44) = 0x1000;
        } else {
            H(a, 0x44) = -0x1000;
        }
        H(a, 0x4A) = -0x3000;
        a[0x29] = 0;
        a[6]++;
    case 7:
        func_80076D68(a);
        func_80056B48(a, 1);
        func_80055D5C(a);
        func_800574E0(a, 0x11);
        if (a[0x144] == 1) {
            a[0x144] = 2;
        }
        if (a[0x145] == 2) {
            func_80054D14(a, 0x67, 8);
        }
        if (a[0x29] != 0) {
            a[0x144] = 0;
            a[5] = 0xB;
            func_80054D14(a, 0x17, 2);
            H(a, 0x44) = 0;
            a[6]++;
            if ((H(a, 0x16C) & 0xC000) == 0xC000) {
                func_80047B5C(a, 0);
                if (D_1F8001A8 & 8) {
                    D_1F80018E = 0x2000;
                    D_1F800194 = D_1F8001A2_7766 & 0xFFF;
                    D_1F800196 = D_1F8001A0_b0de_1f9a & 0xFFF;
                    func_8004960C(a, 0);
                    a[0x61] = 0x20;
                    H(a, 0x140) = D_1F800196;
                    H(a, 0x40) = 2;
                }
            } else {
                if (a[0x147] != 0) {
                    H(a, 0x44) = -0x1000;
                } else {
                    H(a, 0x44) = 0x1000;
                }
                a[6] = 1;
                H(a, 0x40) = 2;
                func_80054D14(a, 4, 4);
            }
        } else if (a[0x181] != 0) {
            func_80054D14(a, 0xDC, 6);
            H(a, 0x44) = 0;
            a[7] = 0;
            if ((H(a, 0x16C) & 0xC000) == 0xC000) {
                a[6]++;
                func_80047B5C(a, 0);
                if (D_1F8001A8 & 8) {
                    D_1F80018E = 0x2000;
                    D_1F800194 = D_1F8001A2_7766 & 0xFFF;
                    D_1F800196 = D_1F8001A0_b0de_1f9a & 0xFFF;
                    func_8004960C(a, 0);
                    a[0x61] = 0x20;
                    H(a, 0x140) = D_1F800196;
                    H(a, 0x40) = 2;
                }
            } else {
                if (a[0x147] != 0) {
                    H(a, 0x44) = -0x1000;
                } else {
                    H(a, 0x44) = 0x1000;
                }
                a[6] = 1;
                H(a, 0x40) = 2;
                func_80054D14(a, 0xDB, 6);
            }
            snap_inl(a);
        }
        break;
    case 8:
        func_80076D68(a);
        if (--H(a, 0x40) == 0) {
            a[6]++;
            func_80055C9C(a, D_1F800196);
            a[0x147] = func_80055E28(a, 0) & 1;
            func_80054198(a);
            if (a[0x147] != 0) {
                D_1F800194 = (D_1F800196 - 0x800) & 0xFFF;
            } else {
                D_1F800194 = D_1F800196;
            }
        }
        func_8010FB44(a, 0);
        snap_inl(a);
        break;
    case 9:
        func_80076D68(a);
        s = D_1F800194;
        s &= 0xFFF;
        if ((H(a, 0x56) = func_800776F8(s, H(a, 0x56), 0x100)) == s) {
            a[6]++;
        }
        func_8010FB44(a, 0);
        snap_inl(a);
        break;
    case 10:
        a[0x61] = 0x20;
        func_80076D68(a);
        if (D_1F800196 == (s16)D_1F800194) {
            a[0x147] = 0;
        } else {
            a[0x147] = 1;
        }
        func_80054198(a);
        a[6]++;
        func_8010FB44(a, 0);
        snap_inl(a);
        break;
    }
}

#define W_d1fb(p, o) (*(s32 *)((u8 *)(p) + (o)))
void func_801120C4(u8 *a, s32 b) {
    s32 r;
    u16 t, p, q;

    func_80055284();
    func_80056B48(a, 1);
    func_8010FF9C(a);
    W_d1fb(a, 0x2C) += H(a, 0x48) * H(a, 0x182);
    W_d1fb(a, 0x34) += H(a, 0x4C) * H(a, 0x182);
    W_d1fb(a, 0x30) += H(a, 0x4A) * H(a, 0x182);

    if (a[0x16B] == 0 && a[0x61] == 0) {
        func_80054650(a, 0);
    } else {
        a[0x5F] &= 0xFB;
    }
    func_8010FB44(a, b);
    func_80055D5C(a);
    H(a, 0x16C) = 0;
    H(a, 0x6A) = 0;
    if (func_8012DE84(a, H(a, 0x32)) != 0) {
        if (D_1F80019E_3f3f < D_1F8001A4_f18c - 0x1F4) {
            r = 0;
        } else {
            t = D_1F8001A4_f18c;
            p = D_1F8001A6;
            q = D_1F8001A8;
            D_1F80019E_3f3f = t;
            H(a, 0x6A) = p;
            H(a, 0x16C) = q;
            func_80049674(a);
            r = 1;
            H(a, 0x142) = D_1F8001A2_7766;
        }
    } else {
        r = 0;
    }
    if (r == 0) {
        func_80056D44(a, 0);
    }
}

extern s32 D_1F800248;
extern u8 *D_1F800138_p;
void func_80112238(u8 *a) {
    u8 *g;
    s32 k;

    D_1F800248 = 0;
    func_8006F0E4();
    a[1] = 1;
    H(a, 0x142) = 0;
    H(a, 0x58) = 0;
    func_80054198(a);
    func_80055284(a);
    func_80055D5C(a);
    func_8003315C(a);
    g = (u8 *)&D_800BF870;
    k = g[1];
    if (k == 3 || k == 0x11) {
        if (k == 0x11 && g[3] != 0) {
            H(a, 0x32) = -0x140C;
            return;
        }
        a[0x181] = 1;
        a[5] = 0x1D;
        a[6] = 1;
        a[7] = 2;
        H(a, 0x50) = 0;
        H(a, 0x4A) = 0;
        if (snap_inl(a) != 0) {
            H(a, 0x32) = D_1F80019E_3f3f;
        }
        func_80054D14(a, 0xDC, 0);
    } else {
        if (k == 0xC || k == 0x10 || k == 0x13) {
            D_800BF808[0x17] = a[0x147] << 4;
            H(D_1F800138_p, 0x4C) = 3;
            H(D_1F800138_p, 0x4E) = 1;
            func_80054D14(a, 2, 0);
            func_8001CF2C();
            func_80113780();
            D_800BF808[0x10] = 2;
        }
        func_80054D14(a, 2, 0);
    }
}

extern u16 D_1F800192_4f46;
extern u8 D_800BF80E;
void func_80112418(u8 *a) {
    s32 s;

    switch (a[6]) {
    case 0:
        a[0x181] = 1;
        func_80054D14(a, 0xDD, 6);
        H(a, 0x50) = 0;
        H(a, 0x4A) = 0;
        a[6]++;
        a[0x147] = func_80055E28(a, 0) & 1;
        func_80054198(a);
        if (a[0x147] != 0) {
            D_1F800192_4f46 = (U(a, 0x140) - 0x800) & 0xFFF;
        } else {
            D_1F800192_4f46 = U(a, 0x140);
        }
    case 1:
        s = D_1F800192_4f46;
        s &= 0xFFF;
        if ((H(a, 0x56) = func_800776F8(s, H(a, 0x56), 0x100)) == s) {
            a[6]++;
        }
        break;
    case 2:
        D_800BF80E = 0;
        a[0] = 3;
        H(a, 0x172) = 0x1E;
        a[4] = 1;
        a[5] = 0x1D;
        a[6] = 1;
        func_80055D5C(a);
        a[0x180] = 6;
        break;
    }
    func_80076D68(a);
    func_8010FB44(a, 0);
    snap_inl(a);
}

extern u8 D_800BF81F_4c28;
void func_801125E4(u8 *a) {
    s32 k;

    switch (a[6]) {
    case 0:
        D_800BF80E = 0;
        func_80053D90(a);
        if (D_1F800137 == 1) {
            H(a, 0x40) = 0xE;
        } else {
            H(a, 0x40) = 0x1C;
        }
        a[0x146] = 0;
        a[0x145] = 0;
        a[0x147] = D_800BF81F_4c28 >> 4;
        a[6]++;
        func_80054198(a);
        H(a, 0x50) = 0;
        H(a, 0x4A) = 0;
        func_80054D14(a, 0xDB, 0);
        if (a[0x147] != 0) {
            H(a, 0x44) = -0x1000;
        } else {
            H(a, 0x44) = 0x1000;
        }
        a[7] = 3;
        func_800551C4(a);
        a[0x181] = 1;
        if (snap_inl(a) != 0) {
            H(a, 0x32) = D_1F80019E_3f3f;
        }
        break;
    case 1:
        a[0x14A] = a[0x147];
        func_80076D68(a);
        func_80056B48(a, 1);
        func_80055D5C(a);
        func_8010FB44(a, 0);
        k = 1;
        if (U(a, 0x6A) & 0x10) {
            a[5] = 0x2B;
            a[6] = 0;
        } else {
            k = 0;
        }
        if (k == 0) {
            if (--H(a, 0x40) == 0) {
                a[6]++;
            }
        }
        func_800551C4(a);
        if ((s16)(H(a, 0x40) % 7) == 0) {
            func_80074590(0x33, 0, 0);
        }
        snap_inl(a);
        break;
    case 2:
        snap_inl(a);
        a[0] = 3;
        H(a, 0x172) = 0x1E;
        a[5] = 0x1D;
        a[6] = 1;
        func_80054198(a);
        func_80054D14(a, 0xDD, 6);
        D_800BF80E = 1;
        func_800551C4(a);
        break;
    }
}

#define P(p, o) (*(u8 **)((u8 *)(p) + (o)))
extern s16 D_800ED098;
extern u8 D_80068FBC[];
u8 *func_8007AB20();
u8 *func_8007AAE8();
u8 *func_80112970(u8 *a, u8 *b, s32 c) {
    u8 *p;
    u8 *r;
    s32 i;

    p = func_8007AB20();
    if (p == NULL) {
        return NULL;
    }
    p[0x46] = a[0x14A];
    H(p, 0x54) = 0;
    H(p, 0x56) = H(a, 0x56);
    H(p, 0x58) = 0;
    P(p, 0x1C) = D_80068FBC;
    p[0x2A] = a[0x2A];
    p[2] = 0;
    p[3] = c;
    p[0x5E] = 0;
    p[0xB] = b[0xB];
    if (b[3] == 0) {
        if (D_800ED098 < 6) {
        fail:
            p[4] = 3;
            goto ret0;
        }
        p[8] = p[9] = 5;
    } else {
        if (D_800ED098 < 7) {
            goto fail;
        }
        p[8] = p[9] = 6;
    }
    H(p, 0x5C) = H(b, 0x5C);
    p[0xD] = b[0xD];
    p[0x18] = b[0x18];
    p[0x19] = b[0x19];
    p[0x1A] = b[0x1A];
    W_d1fb(p, 0x3C) = W_d1fb(b, 0x3C);
    for (i = 0; i < p[9]; i++) {
        r = func_8007AAE8();
        ((u8 **)(p + 0xC0))[i] = r;
        H(r, 6) = H(((u8 **)(b + 0xC0))[i], 6);
        H(r, 0) = H(((u8 **)(b + 0xC0))[i], 0);
        H(r, 2) = H(((u8 **)(b + 0xC0))[i], 2);
        H(r, 4) = H(((u8 **)(b + 0xC0))[i], 4);
        H(r, 0x38) = H(((u8 **)(b + 0xC0))[i], 0x38);
        H(r, 0x3A) = H(((u8 **)(b + 0xC0))[i], 0x3A);
        H(r, 0x3C) = H(((u8 **)(b + 0xC0))[i], 0x3C);
        H(r, 8) = H(((u8 **)(b + 0xC0))[i], 8);
        H(r, 0xA) = H(((u8 **)(b + 0xC0))[i], 0xA);
        H(r, 0xC) = H(((u8 **)(b + 0xC0))[i], 0xC);
        W_d1fb(r, 0x40) = W_d1fb(((u8 **)(b + 0xC0))[i], 0x40);
    }
    b[4] = 2;
    b[5] = 9;
    b[6] = 0;
    return p;
ret0:
    return NULL;
}

void func_80112BCC(u8 *a) {
    s32 s;
    s32 c;
    s32 v;

    switch (a[6]) {
    case 0:
        a[0x29] = 0;
        a[0x146] = 0;
        a[0x145] = 0;
        a[6]++;
        func_80054198(a);
        func_80053D90(a);
        func_80054D14(a, 0x71, 4);
        func_8006625C(a);
        H(a, 0x172) = 0x5A;
        a[0xD] |= 0x82;
        break;
    case 1:
        func_80076D68(a);
        break;
    case 2:
        func_80054198(a);
        func_800551C4(a);
        H(a, 0x44) = 0x3000;
        H(a, 0x4A) = 0x1000;
        a[0x145] = 2;
        a[6]++;
    case 3:
        func_80076D68(a);
        s = (func_80083F50(H(a, 0x56)) * H(a, 0x44)) >> 4;
        c = func_80083E80(H(a, 0x56)) * H(a, 0x44);
        W_d1fb(a, 0x2C) += s;
        W_d1fb(a, 0x30) += H(a, 0x4A) << 8;
        W_d1fb(a, 0x34) -= c >> 4;
        func_80055D5C(a);
        func_800551C4(a);
        func_8005444C(a);
        if (((H(a, 0x6A) & 0x8000) && ((U(a, 0x6A) & 0xF00) == 0x100 || (U(a, 0x6A) & 0xF00) == 0x200)) || a[0x29] != 0) {
            a[4] = 2;
            a[5] = 2;
            a[0] = 3;
            a[6] = 0;
            a[7] = 0;
            a[0x145] = 0;
            H(a, 0x172) = 0x1E;
            a[0x2B] = U(a, 0x56) >> 4;
        }
        break;
    case 4:
        a[0x61] = 0;
        a[0x146] = 0;
        func_80053D90(a);
        a[0x145] = 0;
        H(a, 0x58) = 0;
        func_80054DAC(a, 2, 0);
        a[0] = 3;
        H(a, 0x172) = 0x1E;
        a[5] = 0;
        a[6] = 0;
        a[7] = 0;
        func_800551C4(a);
        break;
    case 14:
        func_80055F48(a, 0);
        a[0x146] = 0;
        func_80053D90(a);
        a[5] = 0x17;
        H(a, 0x58) = 0;
        a[6] = 1;
        a[7] = 0;
        a[0x145] = 1;
        H(a, 0x50) = 0;
        if (func_80055844() != 0) {
            if (a[0x165] != 0) {
                H(a, 0x4A) = U(a, 0x4A) - 0xA00;
            } else {
                H(a, 0x4A) = U(a, 0x4A) - 0x100;
            }
        }
        func_80074590(0xF, 0, 0);
        func_80074590(0x25, 0, 0);
        func_80054D14(a, 0x12, 4);
        func_800538E0(a, a + 0x2C, 0);
        func_800551C4(a);
        break;
    case 15:
        func_80055E28(a, 1);
        func_80055D5C(a);
        a[0x146] = 0;
        func_80053D90(a);
        H(a, 0x58) = 0;
        func_80054D14(a, 0x16, 3);
        func_800551C4(a);
        func_80056C00(a, 1);
        a[6]++;
        break;
    case 16:
        func_80055E28(a, 1);
        func_80055D5C(a);
        func_80056C00(a, 1);
        if ((v = func_80076D68(a)) == 1) {
            a[5] = 0x17;
            a[6] = v;
            a[7] = 0;
            a[0x145] = v;
            H(a, 0x50) = 0;
            func_80074590(0xF, 0, 0);
            func_80074590(0x25, 0, 0);
            func_80054D14(a, 0x12, 4);
            func_800538E0(a, a + 0x2C, 0);
        }
        func_800551C4(a);
        break;
    }
}

#define H(p, o) (*(s16 *)((u8 *)(p) + (o)))
extern u16 D_1F800172;
s32 func_80112F84(u8 *a, u8 *b)
{
    u8 *p = *(u8 **)(a + 0x10);
    s32 t, u;
    s16 r;
    s32 t2;

    b[0x29] = 2;
    func_800635D4(a, 3);
    func_80076D68(a);
    if (a[0x169] == 0 && (D_800ECF54 & (D_1F800172 | 0x50))) {
        t = (func_80083F50(H(a, 0x56)) * (H(a, 0x152) + H(a, 0x80) + 0x10)) >> 12;
        u = func_80083E80(H(a, 0x56)) * (H(a, 0x152) + H(a, 0x80) + 0x10);
        H(a, 0x2E) = H(p, 0x2C) - t;
        H(a, 0x36) = H(p, 0x34) + (u >> 12);
        H(a, 0x32) = H(a, 0x64) + (H(p, 0x30) + H(a, 0x156)) + 0x14;
        return D_800ECF54;
    }
    t = (func_80083F50(H(a, 0x56)) * H(a, 0x152)) >> 12;
    u = func_80083E80(H(a, 0x56)) * H(a, 0x152);
    H(a, 0x2E) = H(p, 0x2C) - t;
    H(a, 0x36) = H(p, 0x34) + (u >> 12);
    r = (func_80083E80(H(a, 0x58)) * H(a, 0x64)) >> 12;
    t2 = (func_80083F50(H(a, 0x56)) * r) >> 12;
    u = func_80083E80(H(a, 0x56)) * r;
    H(a, 0x2E) -= t2;
    H(a, 0x36) += u >> 12;
    H(a, 0x32) = H(p, 0x30) + H(a, 0x156);
    H(a, 0x32) += (func_80083F50(H(a, 0x58)) * H(a, 0x64)) >> 12;
    return 0;
}

extern u16 D_1F80019E;
s32 func_80113190(u8 *a, u8 *b) {
    s16 v[8];

    switch ((U(b, 0x6A) >> 8) & 0xF) {
    case 1:
        v[1] = U(a, 0x2E);
        v[3] = D_1F80019E;
        v[5] = U(a, 0x36);
        if (b[0x145] != 0) {
            func_800312D4(0x909, v, -0xA);
            v[3] += 0x50;
            func_800312D4(0x90A, v, -0xA);
            func_80074590(7, 0, 0);
            return 2;
        }
        func_800312D4(8, v, -0x50);
        return 1;
    case 2:
        if (func_800489E4(a, H(a, 0x32)) == 0) {
            return 0;
        }
        if (H(b, 0x32) + H(b, 0x84) - D_1F8001A4_f18c < 0x15) {
            return 4;
        }
        v[1] = U(a, 0x2E);
        v[3] = D_1F8001A4_f18c;
        v[5] = U(a, 0x36);
        func_800312D4(0x909, v, -0xA);
        if ((s16)abs(H(b, 0x44)) > 0x1000) {
            v[1] = U(a, 0x2E);
            v[3] = D_1F8001A4_f18c;
            v[5] = U(a, 0x36);
            func_800312D4(8, v, -0x50);
        }
        return 3;
    }
    return 0;
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8011332C);

void func_801135C8(void) {
    ((void (*)())func_801100F4)();
}

void func_801135E8(void) {
    func_80110AA0();
}

void func_80113608(void) {
    ((void (*)())func_801114B8)();
}

void func_80113628(u8 *a, u8 *b)
{
    void *r;

    a[0x78] = 0;
    r = func_80112970(a, b, 0x90);
    if (r != 0) {
        a[0x78] = 3;
        *(void **)(a + 0x10) = r;
        return;
    }
    b[4] = 2;
    b[5] = 2;
    b[6] = 0;
    func_80054D14(a, 0x26, 0);
    a[0x145] = 1;
    a[7] = 1;
    a[6] = 7;
    a[0x29] = 0;
    a[0x144] = 0;
    a[0x148] = 0;
    *(s16 *)(a + 0x4A) = 0;
    *(s16 *)(a + 0x58) = 0x20;
}

s32 func_801136C4(u8 *a)
{
    u8 *b = *(u8 **)(a + 0x158);

    if (b[0xC] != 4) {
        return 0;
    }
    if (b[2] != 0x58) {
        return 0;
    }
    return func_80112F84(a, b);
}

extern u16 D_1F8001A4;
void func_8011370C(u8 *a)
{
    s16 v[8];

    v[1] = *(u16 *)(a + 0x2E);
    v[3] = D_1F8001A4;
    v[5] = *(u16 *)(a + 0x36);
    func_800312D4(0x909, v, -0xA);
    v[3] += 0x50;
    func_800312D4(0x90A, v, -0xA);
    func_80074590(7, 0, 0);
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80113780);

extern u8 D_800BF808_399c[];
extern u8 D_800BF817_399c;
extern u8 D_800E8008_399c[];
extern u8 D_800E7E80_399c[];
extern s32 D_1F800184_399c;
extern s16 D_1F8000D0_399c[];
void func_8011399C(void)
{
    u8 *g = D_800BF808_399c;
    u8 *cam = D_800E8008_399c;
    u8 *t = D_800E7E80_399c;
    s32 k;

    g[0xE] = 0;
    cam[0x64] = 0;
    cam[3] = 0;
    D_1F800184_399c = 0;
    if (t[0x181] == 0) {
        t[5] = 0x24;
        t[6] = 0;
        t[7] = 0;
        func_80054198(t);
    } else {
        t[0] = 7;
        t[0x181] = 1;
        g[6] = 0;
        t[5] = 0x2C;
        t[6] = 0;
        func_80054198(t);
    }
    k = D_800BF817_399c;
    if (k == 0) {
        H(t, 0x2E) = 0x1E5B;
        H(t, 0x36) = 0x2D6E;
    } else if (k == 1) {
        H(t, 0x2E) = 0x1AA7;
        H(t, 0x36) = 0x28B1;
    } else if (k == 5) {
        t[6] = 5;
    } else if (k == 7) {
        H(t, 0x2E) = 0x3680;
        H(t, 0x36) = 0x14BD;
    } else if (k == 8) {
        s16 *c = D_1F8000D0_399c;

        c[1] = 0x3AE2;
        c[3] = -0x2943;
        c[5] = 0x9E4;
    } else if (k == 9) {
        H(t, 0x2E) = 0x31BE;
        H(t, 0x36) = 0x19FC;
    }
    t[0x16B] = 0;
}

typedef struct { s16 xl, x, yl, y, zl, z; } Pos3AD8;
typedef struct { s16 x, y, z; } Ent3AD8;
extern u8 D_800BF817;
extern s16 D_80141914[];
extern Ent3AD8 D_801418D8[];
extern u8 D_1F8000D0_3ad8[];
#define TAIL3AD8() \
    { \
        s16 *v = (s16 *)&D_801418D8[D_800BF817]; \
        s16 *c = (s16 *)D_1F8000D0_3ad8; \
        c[1] = v[0]; \
        c[3] = v[1]; \
        c[5] = v[2]; \
    }
s32 func_80113AD8(u8 *a, u8 *b)
{
    Pos3AD8 pos;
    s32 i;
    s16 *w;

    switch (D_800BF817) {
    case 2:
        a[0x64] |= 0x80;
        pos.x = U(b, 0x2E);
        pos.z = U(b, 0x36);
        if (H(b, 0x32) >= -0xE73) {
            pos.y = -0xE74;
        } else {
            pos.y = H(b, 0x32);
        }
        func_8006E3F4(a, &pos);
        if (b[0x2A] == 8) {
            i = 0;
        } else if (b[0x2A] == 9) {
            i = 3;
        } else {
            i = 6;
        }
        w = &D_80141914[i];
        pos.x = w[0];
        pos.y = w[1];
        pos.z = w[2];
        func_8006CEC4(D_1F8000D0_3ad8, &pos, 0);
        a[0x66] = 3;
        return 1;
    case 6:
        a[0x64] |= 0x80;
        pos.x = U(b, 0x2E);
        pos.z = U(b, 0x36);
        if (H(b, 0x32) >= -0xECD) {
            pos.y = -0xECE;
        } else {
            pos.y = H(b, 0x32);
        }
        func_8006E3F4(a, &pos);
        TAIL3AD8()
        a[0x66] = 3;
        return 1;
    case 7:
        a[0x64] |= 0x80;
        pos.x = U(b, 0x2E);
        pos.z = U(b, 0x36);
        if (H(b, 0x32) >= -0x232D) {
            pos.y = -0x232E;
        } else {
            pos.y = H(b, 0x32);
        }
        func_8006E3F4(a, &pos);
        {
            Ent3AD8 *v = &D_801418D8[D_800BF817];
            pos.x = v->x;
            pos.y = v->y;
            pos.z = v->z;
        }
        func_8006CEC4(D_1F8000D0_3ad8, &pos, 0);
        a[0x66] = 3;
        return 1;
    case 5:
        a[0x64] |= 0x80;
        if (H(b, 0x2E) >= 0x4723) {
            H(b, 0x2E) = 0x4722;
        }
        pos.x = U(b, 0x2E);
        pos.y = U(b, 0x32);
        pos.z = U(b, 0x36);
        func_8006E3F4(a, &pos);
        TAIL3AD8()
        a[0x66] = 3;
        return 1;
    case 1:
        if (H(b, 0x2E) < 0x17AB) {
            H(b, 0x2E) = 0x17AB;
            H(b, 0x36) = 0x2EB3;
        }
    case 0:
    case 3:
    case 4:
    case 8:
        a[0x64] |= 0x80;
        func_8006E3F4(a, b + 0x2C);
        TAIL3AD8()
        a[0x66] = 3;
        return 1;
    case 9:
    default:
        a[0x64] &= 0x7F;
        return 0;
    }
}

typedef struct { s16 xl, x, yl, y, zl, z; } Pos3DDC;
extern s16 D_1F8000D0_3ddc[];
#define COPY3DDC() \
    a[0x64] |= 0x80; \
    H(a, 0xA) = U(b, 0x2E); \
    H(a, 0xE) = U(b, 0x32); \
    H(a, 0x12) = U(b, 0x36); \
    func_8006E3F4(a, a + 8)
void func_80113DDC(u8 *a, u8 *b)
{
    Pos3DDC pos;

    switch (a[3]) {
    case 0:
        a[3]++;
        if (b[0x2A] == 1) {
            s16 *c = D_1F8000D0_3ddc;

            c[1] = 0x167F;
            c[3] = U(b, 0x32) - 0x258;
            c[5] = 0x2219;
        } else if (b[0x2A] == 5) {
            s16 *c = D_1F8000D0_3ddc;

            c[1] = 0x2EFF;
            c[3] = U(b, 0x32) - 0x258;
            c[5] = 0xB1C;
        } else if (b[0x2A] == 0x25) {
            s16 *c = D_1F8000D0_3ddc;

            c[1] = 0x18BF;
            c[3] = -0x16D2;
            c[5] = 0x253D;
        }
    case 1:
        a[0x72] = 0;
        a[0x64] &= 0x7F;
        switch (b[0x2A]) {
        case 1:
            if (H(b, 0x2E) < 0x1C29) {
                COPY3DDC();
                pos.x = 0x167F;
                pos.y = U(b, 0x32) - 0x258;
                pos.z = 0x2219;
                if (func_8006CEC4(D_1F8000D0_3ddc, &pos, 0xE0) != 0) {
                    a[0x66] = 3;
                }
            }
            break;
        case 3:
        case 4:
        case 5:
            if (H(b, 0x2E) >= 0x3201) {
                COPY3DDC();
                pos.x = 0x2EFF;
                pos.y = U(b, 0x32);
                pos.z = 0xB1C;
                if (func_8006CEC4(D_1F8000D0_3ddc, &pos, 0xE0) != 0) {
                    a[0x66] = 3;
                }
            }
            break;
        case 7:
            a[0x72] = 0x40;
            H(a, 0x8C) = 0x6D2;
            break;
        case 8:
        case 9:
        case 10:
            a[0x72] = 0x40;
            H(a, 0x8C) = 0x580;
            break;
        case 0x25:
            if (H(b, 0x2E) < 0x1E54) {
                COPY3DDC();
                pos.x = 0x18BF;
                pos.y = -0x16D2;
                pos.z = 0x253D;
                if (func_8006CEC4(D_1F8000D0_3ddc, &pos, 0xE0) != 0) {
                    a[0x66] = 3;
                }
            } else if (H(b, 0x2E) < 0x1FC2) {
                COPY3DDC();
                pos.x = 0x1A93;
                pos.y = -0x1699;
                pos.z = 0x2182;
                if (func_8006CEC4(D_1F8000D0_3ddc, &pos, 0xE0) != 0) {
                    a[0x66] = 3;
                }
            } else if (H(b, 0x2E) >= 0x2261) {
                H(a, 0x26) = -0x2BC;
            }
            break;
        case 0x23:
        case 0x24:
            H(a, 0x26) = -0x2BC;
            break;
        }
        break;
    }
}

typedef struct { s16 xl, x, yl, y, zl, z; } Pos4118;
extern s16 D_1F8000D0_4118[];
#define COPY4118() \
    a[0x64] |= 0x80; \
    H(a, 0xA) = U(b, 0x2E); \
    H(a, 0xE) = U(b, 0x32); \
    H(a, 0x12) = U(b, 0x36); \
    func_8006E3F4(a, a + 8)
#define AIM4118(X, Y, Z) \
    pos.x = X; \
    pos.y = Y; \
    pos.z = Z; \
    if (func_8006CEC4(D_1F8000D0_4118, &pos, 0xE0) != 0) { \
        a[0x66] = 3; \
    }
void func_80114118(u8 *a, u8 *b)
{
    Pos4118 pos;

    switch (a[3]) {
    case 0:
        a[3]++;
        if (b[0x2A] < 6) {
            s16 *c = D_1F8000D0_4118;

            c[1] = 0x3860;
            c[3] = U(b, 0x32) - 0x258;
            c[5] = 0x9B5;
        } else if (b[0x2A] == 0xF) {
            s16 *c = D_1F8000D0_4118;

            c[1] = 0x430F;
            c[3] = -0x25DC;
            c[5] = 0x965;
        }
    case 1:
        a[0x72] = 0;
        a[0x64] &= 0x7F;
        switch (b[0x2A]) {
        case 4:
        case 5:
            a[0x64] |= 0x80;
            H(a, 0xA) = U(b, 0x2E);
            if (H(a, 0xA) < 0x3542) {
                H(a, 0xA) = 0x3542;
            }
            H(a, 0xE) = U(b, 0x32);
            H(a, 0x12) = U(b, 0x36);
            func_8006E3F4(a, a + 8);
            AIM4118(0x3860, -0x11DC, 0x9B5)
            break;
        case 11:
            a[0x72] = 0x40;
            H(a, 0x8C) = 0x400;
            break;
        case 12:
            a[0x72] = 0x40;
            H(a, 0x8C) = 0x480;
            break;
        case 15:
            a[0x72] = 0x40;
            H(a, 0x8C) = 0x540;
            break;
        case 6:
        case 32:
        case 40:
        case 41:
            if (H(b, 0x32) < -0x206C) {
                if (H(b, 0x2E) >= 0x4269) {
                    a[0x64] |= 0x80;
                    H(a, 0xA) = U(b, 0x2E);
                    if (H(a, 0xA) >= 0x4593) {
                        H(a, 0xA) = 0x4592;
                    }
                    H(a, 0xE) = U(b, 0x32);
                    H(a, 0x12) = U(b, 0x36);
                    func_8006E3F4(a, a + 8);
                    AIM4118(0x430F, U(b, 0x32) - 0x2D0, 0x965)
                }
            } else if (H(b, 0x32) >= -0x1900) {
                if (H(b, 0x32) < -0x11F8) {
                    if (H(b, 0x2E) >= 0x434D) {
                        COPY4118();
                        AIM4118(0x41FF, -0x16DC, 0x93C)
                    }
                }
            }
            break;
        case 18:
        case 19:
            if (H(b, 0x2E) < 0x3778) {
                COPY4118();
                AIM4118(0x36B2, -0x25DC, 0x975)
            }
            break;
        case 20:
            H(a, 0xA) = 0x3680;
            H(a, 0xE) = -0x230C;
            H(a, 0x12) = 0x1105;
            a[0x64] |= 0x80;
            func_8006E3F4(a, a + 8);
            AIM4118(0x3310, -0x25A4, 0xEA1)
            break;
        }
        break;
    }
}

typedef struct { s16 xl, x, yl, y, zl, z; } Pos44D4;
extern s16 D_1F8000D0_44d4[];
extern u8 D_800BF816;
extern u8 D_800BF8E3;
#define COPY44D4() \
    a[0x64] |= 0x80; \
    H(a, 0xA) = U(b, 0x2E); \
    H(a, 0xE) = U(b, 0x32); \
    H(a, 0x12) = U(b, 0x36); \
    func_8006E3F4(a, a + 8)
#define AIM44D4(X, Y, Z) \
    pos.x = X; \
    pos.y = Y; \
    pos.z = Z; \
    if (func_8006CEC4(D_1F8000D0_44d4, &pos, 0xE0) != 0) { \
        a[0x66] = 3; \
    }
#define SET44D4(X, Y, Z) \
    { \
        s16 *c = D_1F8000D0_44d4; \
        c[1] = X; \
        c[3] = Y; \
        c[5] = Z; \
    }
void func_801144D4(u8 *a, u8 *b)
{
    Pos44D4 pos;

    switch (a[3]) {
    case 0:
        a[3]++;
        if (b[0x2A] == 1) {
            SET44D4(0x12DC, -0x17C3, 0x2A2A)
        } else if (b[0x2A] == 0x25) {
            SET44D4(0x15D3, -0x1951, 0x29FA)
        } else if (b[0x2A] == 0x26) {
            SET44D4(0x1C70, -0x1A98, 0x25DA)
        } else if (b[0x2A] == 0x27) {
            SET44D4(0x16F3, -0x2375, 0x2986)
        }
    case 1:
        a[0x72] = 0;
        a[0x64] &= 0x7F;
        switch (b[0x2A]) {
        case 1:
            a[0x64] |= 0x80;
            if (H(b, 0x2E) >= 0x1952) {
                H(a, 0xA) = 0x1951;
                H(a, 0xE) = -0x15C4;
                H(a, 0x12) = 0x2BC2;
            } else {
                if (H(b, 0x2E) < 0x170C) {
                    H(a, 0xA) = 0x170C;
                    H(a, 0x12) = 0x2FE7;
                } else {
                    H(a, 0xA) = U(b, 0x2E);
                    H(a, 0x12) = U(b, 0x36);
                }
                if (H(b, 0x32) >= -0x15C3) {
                    H(a, 0xE) = -0x15C4;
                } else {
                    H(a, 0xE) = U(b, 0x32);
                }
            }
            func_8006E3F4(a, a + 8);
            AIM44D4(0x12DC, -0x17C3, 0x2A2A)
            break;
        case 21:
            if (D_800BF816 == 0) {
                COPY44D4();
                AIM44D4(0x2945, -0x2447, 0x145F)
                if (D_800BF873 != 0 && H(b, 0x2E) >= 0x30E7) {
                    H(b, 0x2E) = 0x30E6;
                    H(b, 0x36) = 0x184C;
                }
            }
            break;
        case 26:
        case 27:
            a[0x72] = 0x40;
            H(a, 0x8C) = 0x52E;
            break;
        case 30:
            a[0x72] = 0x40;
            H(a, 0x8C) = 0x380;
            break;
        case 31:
            a[0x72] = 0x40;
            H(a, 0x8C) = 0x840;
            H(a, 0x26) = 0;
            break;
        case 33:
            if (H(b, 0x2E) >= 0x35AA) {
                COPY44D4();
                AIM44D4(0x34A5, -0x1AB8, 0x916)
            }
            break;
        case 37:
            COPY44D4();
            AIM44D4(0x15D3, -0x1951, 0x29FA)
            break;
        case 38:
            a[0x64] |= 0x80;
            if (H(b, 0x36) < 0x2BF0) {
                H(a, 0xA) = 0x1B5F;
                H(a, 0xE) = -0x154C;
                H(a, 0x12) = 0x2BF0;
            } else {
                H(a, 0xA) = U(b, 0x2E);
                H(a, 0xE) = U(b, 0x32);
                H(a, 0x12) = U(b, 0x36);
            }
            func_8006E3F4(a, a + 8);
            AIM44D4(0x1C70, -0x1A98, 0x25DA)
            break;
        case 39:
            a[0x64] |= 0x80;
            if (H(b, 0x36) < 0x3167) {
                H(a, 0xA) = 0x17DE;
                H(a, 0xE) = U(b, 0x32);
                H(a, 0x12) = 0x3167;
            } else {
                H(a, 0xA) = U(b, 0x2E);
                H(a, 0xE) = U(b, 0x32);
                H(a, 0x12) = U(b, 0x36);
            }
            func_8006E3F4(a, a + 8);
            pos.x = 0x16F3;
            pos.z = 0x2986;
            if (H(a, 0xE) >= -0x1A8F) {
                pos.y = U(b, 0x32) - 0x12C;
            } else {
                pos.y = -0x2375;
            }
            if (func_8006CEC4(D_1F8000D0_44d4, &pos, 0xE0) != 0) {
                a[0x66] = 3;
            }
            break;
        case 44:
            if (D_800BF8E3 != 0xFF) {
                COPY44D4();
                AIM44D4(0x3594, -0x25DC, 0x1B52)
            }
            break;
        }
        break;
    }
}

extern u8 D_800E7E80_4a70[];
extern u8 D_800BF808_4a70[];
extern u8 D_800BF871_4a70;
extern s16 D_1F8000D0_4a70[];
#define FLOOR4A70() \
    if (g[0xE] == 0) { \
        s16 *c = D_1F8000D0_4a70; \
        if (c[3] >= -0x1130) { \
            a[0x74] = 2; \
            c[3] = -0x1130; \
            H(a, 0x4A) = -0x1130; \
        } else { \
            a[0x74] = 0; \
        } \
    } else { \
        a[0x74] = 0; \
    }
void func_80114A70(u8 *a)
{
    u8 *b = D_800E7E80_4a70;
    u8 *g = D_800BF808_4a70;

    if (g[0xE] != 0 && func_80113AD8(a, b) != 0) {
        return;
    }
    H(a, 0x26) = -0x190;
    H(a, 0x56) = 0;
    if (D_800BF871_4a70 < 9) {
        func_80113DDC(a, b);
        FLOOR4A70()
    } else if (D_800BF871_4a70 < 0x10) {
        func_80114118(a, b);
        FLOOR4A70()
    } else {
        func_801144D4(a, b);
        FLOOR4A70()
    }
}

extern u8 D_800BF871;
extern u8 D_1F80019C;
void func_80114CB8();
void func_80114B90(void)
{
    u32 s = D_800BF871;
    s32 v;
    u8 *g;

    if (s < 9) {
        v = 0x22;
    } else if (s < 0x10) {
        v = 0x26;
    } else if (s < 0x15) {
        v = 0x24;
    } else {
        v = 0x28;
    }
    g = (u8 *)&D_800BF870;
    if (g[0x5F0] != v) {
        g[0x5F0] = v;
        D_1F80019C = 3;
        func_80044BD4(func_80114CB8, v, 0, 3);
        D_1F80019C = 0;
    }
}

s32 func_8007778C();
s32 func_80114C1C(void *a, s32 k)
{
    s32 v;
    u32 s = D_800BF871;

    if (s < 9) {
        v = 0;
    } else if (s < 0x10) {
        v = 1;
    } else if (s < 0x15) {
        v = 2;
    } else {
        v = 3;
    }
    if (v == k) {
        return ((s32 (*)(void *, s32, u32))func_8007778C)(a, k, s);
    }
    return 0;
}

extern s8 D_1F800138[];
extern s8 D_1F80019B[];
void func_80114C78(void) {
    func_80045258(M2C_FIELD(*((volatile void **)D_1F800138), u8 *, 0x6E), 0xF);
    *((volatile s8 *)D_1F80019B) = 1;
    func_80051FB4();
}

extern s8 D_1F800138[];
extern s8 D_1F80019B[];
void func_80114CB8(void) {
    func_80045258(M2C_FIELD(*((volatile void **)D_1F800138), u8 *, 0x6E), 8);
    *((volatile s8 *)D_1F80019B) = 1;
    func_80051FB4();
}

extern u8 D_800BF808_s08[];
extern u8 D_800BF871_s08;
extern u8 D_80141928[];
extern u8 D_801419C8[];
extern u8 D_80141A28[];
extern u8 D_80141AD8[];
extern u8 *D_80141E68[];
u8 *func_8012B89C(u8 *a, s32 i);
static inline u8 *GS08(void)
{
    return (u8 *)&D_800BF870;
}
static inline u8 *GB08(void)
{
    return D_800BF808_s08;
}
void f_SpawnWaterTempleSceneActorsFromPlacementTable(u8 *a, s32 mode)
{
    u8 *e;
    u8 *p;

    if (mode == 0) {
        if (D_800BF871_s08 < 9) {
            e = D_80141928;
        } else if (D_800BF871_s08 < 0x10) {
            e = D_801419C8;
        } else if (D_800BF871_s08 < 0x15) {
            e = D_80141A28;
        } else {
            e = D_80141AD8;
        }
    } else {
        e = D_80141E68[mode];
    }
    H(a, 8) = 0;
    if (e[0] == 0xFF) {
        return;
    }
    do {
        if (e[0xB] == 1 && ((U(GS08(), 0x5E6) >> D_800BF870.unk0) & 1)) {
            goto next;
        }
        if (e[0xB] == 2 && GS08()[3] != 0) {
            goto next;
        }
        if (mode != 0 && H(a, 8) >= 0xF) {
            goto next;
        }
        switch (e[0xA]) {
        case 0:
            break;
        case 1:
            if (mode == 6 || mode == 8) {
                GB08()[0x45] = 1;
            } else {
                GB08()[0x45] = 0;
            }
            U(GB08(), 8) = U(e, 4);
            U(GB08(), 0xA) = U(e, 6);
            U(GB08(), 0xC) = U(e, 8);
            break;
        case 2:
            if (!(GS08()[0x15D] & 2)) {
                break;
            }
            goto next;
        case 3:
            if (GS08()[0x1C3] == 1) {
                break;
            }
            goto next;
        case 4:
            if (GS08()[0x1C8] == 0) {
                break;
            }
            goto next;
        case 5:
            if (GS08()[0xA5] != 0xFF) {
                break;
            }
            if (GS08()[0x7F] != 0xFF) {
                break;
            }
            goto next;
        case 6:
            if (!(GS08()[0x1CF] & 0x20)) {
                break;
            }
            goto next;
        case 7:
            if (GS08()[0x26B] != 0) {
                goto next;
            }
            if (GS08()[0x6F] != 0xFF) {
                break;
            }
            goto next;
        case 8:
            if (e[3] != 0) {
                break;
            }
            if (GS08()[0x1CB] < 2) {
                break;
            }
            goto next;
        case 9:
            if (GS08()[3] == 0) {
                goto next;
            }
            if (!((GS08()[0x1CD] >> e[3]) & 1)) {
                break;
            }
            goto next;
        case 10:
            if (GS08()[0x72] != 0xFF) {
                break;
            }
            goto next;
        case 11:
            if (GS08()[0x1CB] < 2) {
                goto next;
            }
            if (!(GS08()[0x1CF] & 0x40)) {
                break;
            }
            goto next;
        case 12:
            switch (e[3]) {
            case 0:
                if (GS08()[0x71] != 0xFF) {
                    break;
                }
                goto next;
            case 1:
                if (GS08()[0x71] == 0xFF) {
                    goto spawn;
                }
                goto next;
            }
            break;
        case 13:
            if (GS08()[0x71] != 0xFF) {
                goto next;
            }
            p = func_8012B89C(0, 0);
            if (p != NULL) {
                H(p, 0x2E) = 0x3425;
                H(p, 0x32) = -0x15FE;
                H(p, 0x36) = 0x1033;
                H(p, 0x56) = 0x114;
            }
            goto next;
        case 14:
            switch (e[3]) {
            case 2:
                if (GS08()[0x1C8] == 2) {
                    break;
                }
                goto next;
            case 3:
                if (GS08()[0x1C8] == 0) {
                    goto next;
                }
                break;
            }
            break;
        case 15:
            switch (e[3]) {
            case 0:
                if (GS08()[0x6E] != 0xFF) {
                    break;
                }
                goto next;
            case 1:
                if (GS08()[0x6E] == 0xFF) {
                    goto spawn;
                }
                goto next;
            }
            break;
        case 16:
            if (!(GS08()[0x1D7] & 0x80)) {
                goto next;
            }
            break;
        case 17:
            if (!(GS08()[0x1D9] & 4)) {
                break;
            }
            goto next;
        case 18:
            if (GS08()[0x1DE] < 4) {
                break;
            }
            goto next;
        case 19:
            if (GS08()[0x1DE] >= 3) {
                break;
            }
            goto next;
        case 20:
            if (GS08()[0x1C1] < 10) {
                break;
            }
            goto next;
        case 22:
            if (GS08()[0xCD] & 0x80) {
                goto next;
            }
        case 21:
            if (GS08()[0x3F] == 0) {
                goto next;
            }
            break;
        case 23:
            if (GS08()[0x74] == 0) {
                break;
            }
            goto next;
        case 24:
            if (GS08()[0x1E4] == 0) {
                break;
            }
            goto next;
        case 25:
            if (GS08()[0x73] != 0xFF) {
                break;
            }
            goto next;
        case 26:
            if (GS08()[3] == 0) {
                goto next;
            }
            break;
        }
    spawn:
        p = func_80072DDC(a, e[0], e[1], e[2]);
        if (p != NULL) {
            *(s32 *)(p + 0x2C) = H(e, 4) << 16;
            *(s32 *)(p + 0x30) = H(e, 6) << 16;
            *(s32 *)(p + 0x34) = H(e, 8) << 16;
            p[3] = e[3];
            H(p, 0x54) = 0;
            H(p, 0x56) = 0;
            H(p, 0x58) = 0;
            *(s32 *)(p + 0x1C) = *(s32 *)(e + 0xC);
            if (mode != 0) {
                *(u8 **)(a + (H(a, 8) << 2) + 0xC) = p;
                H(a, 8)++;
            }
        }
    next:
        e += 0x10;
    } while (e[0] != 0xFF);
}

extern ClutCycle D_80142EA8[];
extern s8 D_801485CC[];
void func_801152F0(s32 arg0) {
    ClutRect r;
    s32 i;
    ClutCycle *e;
    u8 *data;

    if (arg0 == 0) {
        s8 *p;
        i = 24;
        p = &D_801485CC[i];
        do {
            *p-- = 0;
        } while (--i >= 0);
        return;
    }
    if (D_800BF873) {
        return;
    }
    e = D_80142EA8;
    for (i = 0; i < 25; i++, e++) {
        if (--D_801485CC[i] <= 0) {
            if (e->ptr[0] == 0xFF) {
                e->ptr -= e->ptr[1];
            }
            data = e->clut + e->ptr[0] * 32;
            D_801485CC[i] = e->ptr[1];
            r.x = e->x;
            r.y = e->y;
            r.w = 16;
            r.h = 1;
            func_80081218(&r, data);
            e->ptr += 2;
        }
    }
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80115428);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_801155D4);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8011597C);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80115AEC);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80115BE0);

extern s32 D_800ECFB8;
extern s8 D_800BFA33;
extern s32 D_800ECF80;
extern u8 D_801486EC[];
extern u8 D_1F800207;
extern u8 D_800BFA54;
/* func_801161C4, inlined */
static inline void func_801161C4_inl(u8 *a)
{
    if (func_80051B70(a, 0x17, 5) == 0) {
        s16 *p = *(s16 **)(a + 0xC0);
        *(s32 *)(a + 0x3C) = D_800ECFB8;
        *p -= 0x64;
        if (a[5] == 0) {
            a[0] = 1;
        }
        *(s16 *)(a + 0x80) = 0x64;
        *(s16 *)(a + 0x82) = 0xC8;
        *(s16 *)(a + 0x84) = 0x14;
        *(s16 *)(a + 0x86) = 0x32;
        func_8004B354(a, 1);
    }
}
/* func_80116330, inlined */
static inline void func_80116330_inl(u8 *a) {
    a[0xB] = 0x10;
    a[0x47] = 0;
    M2C_FIELD(a, s16 *, 0x5A) = 0;
    M2C_FIELD(a, s16 *, 0x5C) = 0;
    a[0xD] = 0;
    M2C_FIELD(a, s32 *, 0x3C) = D_800ECF80;
    func_80077B38(a, D_801486EC, 16);
    a[0] = 1;
    M2C_FIELD(a, s16 *, 0x80) = 0x14;
    M2C_FIELD(a, s16 *, 0x82) = 0x28;
    M2C_FIELD(a, s16 *, 0x84) = 0x14;
    M2C_FIELD(a, s16 *, 0x86) = 0x28;
    func_8004B354(a, 0);
}
/* func_80116430, inlined */
static inline void func_80116430_inl(u8 *a) {
    a[0xB] = 0x10;
    a[0x47] = 0;
    M2C_FIELD(a, s16 *, 0x5A) = 0;
    M2C_FIELD(a, s16 *, 0x5C) = 0;
    a[0xD] = 0;
    M2C_FIELD(a, s32 *, 0x3C) = D_800ECF80;
    func_80077B38(a, D_801486EC, 1);
    M2C_FIELD(a, s16 *, 0x68) = 0xA1;
    a[0] = 1;
    M2C_FIELD(a, s16 *, 0x80) = 0x28;
    M2C_FIELD(a, s16 *, 0x82) = 0x50;
    M2C_FIELD(a, s16 *, 0x84) = 0x28;
    M2C_FIELD(a, s16 *, 0x86) = 0x50;
    M2C_FIELD(a, s16 *, 0x60) = M2C_FIELD(a, s16 *, 0x32);
    func_8004B354(a, 0);
}
/* func_8011655C, inlined */
static inline void func_8011655C_inl(u8 *a) {
    a[0xB] = 0x10;
    a[0x47] = 0;
    M2C_FIELD(a, s16 *, 0x5A) = 0;
    M2C_FIELD(a, s16 *, 0x5C) = 0;
    a[0xD] = 0;
    M2C_FIELD(a, s32 *, 0x3C) = D_800ECF80;
    func_80077B38(a, D_801486EC, 7);
    M2C_FIELD(a, s16 *, 0x68) = 0xA5;
    a[0] = 1;
    M2C_FIELD(a, s16 *, 0x80) = 0x28;
    M2C_FIELD(a, s16 *, 0x82) = 0x50;
    M2C_FIELD(a, s16 *, 0x84) = 0xA;
    M2C_FIELD(a, s16 *, 0x86) = 0x14;
    func_8004B354(a, 0);
}
/* func_80116674, inlined */
static inline void func_80116674_inl(u8 *a) {
    a[0xB] = 0x10;
    a[0x47] = 0;
    M2C_FIELD(a, s16 *, 0x5A) = 0;
    M2C_FIELD(a, s16 *, 0x5C) = 0;
    a[0xD] = 0;
    M2C_FIELD(a, s32 *, 0x3C) = D_800ECF80;
    func_80077B38(a, D_801486EC, 3);
    M2C_FIELD(a, s16 *, 0x68) = 0xA3;
    a[0x2A] = 0x1A;
    M2C_FIELD(a, s16 *, 0x80) = 0x64;
    M2C_FIELD(a, s16 *, 0x82) = 0xC8;
    M2C_FIELD(a, s16 *, 0x84) = 0x28;
    M2C_FIELD(a, s16 *, 0x86) = 0x50;
    func_8004B354(a, 0);
}
/* func_80116704, inlined */
static inline void func_80116704_inl(u8 *p)
{
    func_8007778C(p);
    if (D_1F800207 == 0x1A) {
        p[0] = 1;
    } else {
        p[0] = 2;
    }
    func_8004B374(p, 0);
}
/* func_801163E4, inlined */
static inline void func_801163E4_inl(void *arg0) {
    if (func_80040B48(0x2B) >= 0) {
        func_8004D4C4(0x27, 1);
        func_8004B0D8(arg0);
    }
    M2C_FIELD(arg0, s8 *, 4) = 3;
}
/* func_8011661C, inlined */
static inline void func_8011661C_inl(void *arg0) {
    if (func_80040B48(0x89) >= 0) {
        func_8004A3D4(arg0);
        D_800BF870.pad1[0xCC] |= 0x80;
    }
    M2C_FIELD(arg0, s8 *, 4) = 3;
}
void f_UpdateWaterTempleQuestItemPickupActor(u8 *a)
{
    u16 t;

    switch (a[4]) {
    case 0:
        a[4] = 1;
        switch (a[3]) {
        case 0:
            func_801161C4_inl(a);
            break;
        case 1:
            func_80116330_inl(a);
            break;
        case 2:
            func_80116430_inl(a);
            break;
        case 3:
            func_8011655C_inl(a);
            break;
        case 4:
            func_80116674_inl(a);
            break;
        }
        break;
    case 1:
        switch (a[3]) {
        case 0:
            func_80115BE0(a);
            break;
        case 1:
            if (func_8007778C(a) != 0) {
                func_8004B374(a, 0);
            }
            break;
        case 2:
            func_8007778C(a);
            t = (*(u16 *)(a + 0x40) + 0x40) & 0xFFF;
            *(u16 *)(a + 0x40) = t;
            *(s16 *)(a + 0x32) = *(u16 *)(a + 0x60) + (func_80083E80(t) >> 8);
            func_8004B374(a, 0);
            break;
        case 3:
            func_8007778C(a);
            func_8004B374(a, 0);
            break;
        case 4:
            func_80116704_inl(a);
            break;
        }
        break;
    case 2:
        switch (a[3]) {
        case 0:
            func_8004D4C4(0x9E, 1);
            func_8004B0D8(a);
            D_800BFA33 = 2;
            a[4] = 3;
            break;
        case 1:
            func_801163E4_inl(a);
            break;
        case 2:
            func_8004A3D4(a);
            D_800BF870.pad1[0x1CE] |= 0x40;
            a[4] = 3;
            break;
        case 3:
            func_8011661C_inl(a);
            break;
        case 4:
            func_8004A3D4(a);
            D_800BFA54 = 1;
            a[4] = 3;
            break;
        }
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

void func_801161C4(u8 *a)
{
    if (func_80051B70(a, 0x17, 5) == 0) {
        s16 *p = *(s16 **)(a + 0xC0);
        *(s32 *)(a + 0x3C) = D_800ECFB8;
        *p -= 0x64;
        if (a[5] == 0) {
            a[0] = 1;
        }
        *(s16 *)(a + 0x80) = 0x64;
        *(s16 *)(a + 0x82) = 0xC8;
        *(s16 *)(a + 0x84) = 0x14;
        *(s16 *)(a + 0x86) = 0x32;
        func_8004B354(a, 1);
    }
}

void func_80116254(void *arg0) {
    func_8004D4C4(0x9E, 1);
    func_8004B0D8(arg0);
    D_800BFA33 = 2;
    M2C_FIELD(arg0, s8 *, 4) = 3;
}

void f_UpdateWaterTempleQuestItemPickupActor();
s32 func_8011629C(u8 *a)
{
    u8 *p = func_80072DDC(a, 1, 5, 3);

    if (p == NULL) {
        return 0;
    }
    *(void **)(p + 0x1C) = f_UpdateWaterTempleQuestItemPickupActor;
    p[3] = 0;
    p[5] = 1;
    *(s16 *)(p + 0x2E) = *(s16 *)(*(u8 **)(a + 0xD4) + 0x2C);
    *(s16 *)(p + 0x32) = *(s16 *)(*(u8 **)(a + 0xD4) + 0x30);
    *(s16 *)(p + 0x36) = *(s16 *)(*(u8 **)(a + 0xD4) + 0x34);
    return 1;
}

void func_80116330(u8 *a) {
    a[0xB] = 0x10;
    a[0x47] = 0;
    M2C_FIELD(a, s16 *, 0x5A) = 0;
    M2C_FIELD(a, s16 *, 0x5C) = 0;
    a[0xD] = 0;
    M2C_FIELD(a, s32 *, 0x3C) = D_800ECF80;
    func_80077B38(a, D_801486EC, 16);
    a[0] = 1;
    M2C_FIELD(a, s16 *, 0x80) = 0x14;
    M2C_FIELD(a, s16 *, 0x82) = 0x28;
    M2C_FIELD(a, s16 *, 0x84) = 0x14;
    M2C_FIELD(a, s16 *, 0x86) = 0x28;
    func_8004B354(a, 0);
}

void func_801163B0(s32 arg0) {
    if (func_8007778C() != 0) {
        func_8004B374(arg0, 0);
    }
}

void func_801163E4(void *arg0) {
    if (func_80040B48(0x2B) >= 0) {
        func_8004D4C4(0x27, 1);
        func_8004B0D8(arg0);
    }
    M2C_FIELD(arg0, s8 *, 4) = 3;
}

void func_80116430(u8 *a) {
    a[0xB] = 0x10;
    a[0x47] = 0;
    M2C_FIELD(a, s16 *, 0x5A) = 0;
    M2C_FIELD(a, s16 *, 0x5C) = 0;
    a[0xD] = 0;
    M2C_FIELD(a, s32 *, 0x3C) = D_800ECF80;
    func_80077B38(a, D_801486EC, 1);
    M2C_FIELD(a, s16 *, 0x68) = 0xA1;
    a[0] = 1;
    M2C_FIELD(a, s16 *, 0x80) = 0x28;
    M2C_FIELD(a, s16 *, 0x82) = 0x50;
    M2C_FIELD(a, s16 *, 0x84) = 0x28;
    M2C_FIELD(a, s16 *, 0x86) = 0x50;
    M2C_FIELD(a, s16 *, 0x60) = M2C_FIELD(a, s16 *, 0x32);
    func_8004B354(a, 0);
}

void func_801164C0(void *arg0) {
    u16 temp_a0;

    func_8007778C();
    temp_a0 = (M2C_FIELD(arg0, u16 *, 0x40) + 0x40) & 0xFFF;
    M2C_FIELD(arg0, u16 *, 0x40) = temp_a0;
    M2C_FIELD(arg0, s16 *, 0x32) = (s16) (M2C_FIELD(arg0, u16 *, 0x60) + (func_80083E80(temp_a0) >> 8));
    func_8004B374(arg0, 0);
}

void func_80116518(void *arg0) {
    func_8004A3D4();
    D_800BF870.pad1[0x1CE] |= 0x40;
    M2C_FIELD(arg0, s8 *, 4) = 3;
}

void func_8011655C(u8 *a) {
    a[0xB] = 0x10;
    a[0x47] = 0;
    M2C_FIELD(a, s16 *, 0x5A) = 0;
    M2C_FIELD(a, s16 *, 0x5C) = 0;
    a[0xD] = 0;
    M2C_FIELD(a, s32 *, 0x3C) = D_800ECF80;
    func_80077B38(a, D_801486EC, 7);
    M2C_FIELD(a, s16 *, 0x68) = 0xA5;
    a[0] = 1;
    M2C_FIELD(a, s16 *, 0x80) = 0x28;
    M2C_FIELD(a, s16 *, 0x82) = 0x50;
    M2C_FIELD(a, s16 *, 0x84) = 0xA;
    M2C_FIELD(a, s16 *, 0x86) = 0x14;
    func_8004B354(a, 0);
}

void func_801165EC(s32 arg0) {
    func_8007778C();
    func_8004B374(arg0, 0);
}

void func_8011661C(void *arg0) {
    if (func_80040B48(0x89) >= 0) {
        func_8004A3D4(arg0);
        D_800BF870.pad1[0xCC] |= 0x80;
    }
    M2C_FIELD(arg0, s8 *, 4) = 3;
}

void func_80116674(u8 *a) {
    a[0xB] = 0x10;
    a[0x47] = 0;
    M2C_FIELD(a, s16 *, 0x5A) = 0;
    M2C_FIELD(a, s16 *, 0x5C) = 0;
    a[0xD] = 0;
    M2C_FIELD(a, s32 *, 0x3C) = D_800ECF80;
    func_80077B38(a, D_801486EC, 3);
    M2C_FIELD(a, s16 *, 0x68) = 0xA3;
    a[0x2A] = 0x1A;
    M2C_FIELD(a, s16 *, 0x80) = 0x64;
    M2C_FIELD(a, s16 *, 0x82) = 0xC8;
    M2C_FIELD(a, s16 *, 0x84) = 0x28;
    M2C_FIELD(a, s16 *, 0x86) = 0x50;
    func_8004B354(a, 0);
}

void func_8012485C();
extern u8 D_800BF8DF;
void func_80116704(u8 *p)
{
    func_8007778C(p);
    if (D_1F800207 == 0x1A) {
        p[0] = 1;
    } else {
        p[0] = 2;
    }
    func_8004B374(p, 0);
}

void func_80116750(u8 *a)
{
    u8 *p = *(u8 **)(a + 0x10);
    s16 k;

    switch (a[5]) {
    case 0:
        *(s16 *)(a + 0x2E) = *(s16 *)(p + 0x2E);
        *(s16 *)(a + 0x32) = *(s16 *)(p + 0x32) - 0xA0;
        *(s16 *)(a + 0x36) = *(s16 *)(p + 0x36);
        func_8004766C(a);
        func_80049760(a);
        *(s16 *)(a + 0x4A) = -0x200;
        *(s16 *)(a + 0x44) = 0x1000;
        a[0x29] = 0;
        a[5]++;
        break;
    case 1:
        if (*(s16 *)(a + 0x4A) >= 0) {
            a[0] = 1;
            a[5]++;
        }
    case 2:
    case 3:
        {
            s32 x, y, z;
            k = *(s16 *)(a + 0x44);
            x = k * *(s16 *)(a + 0x48);
            z = k * *(s16 *)(a + 0x4C);
            y = k * *(s16 *)(a + 0x4A);
            *(s32 *)(a + 0x2C) -= x;
            *(s32 *)(a + 0x34) -= z;
            *(s32 *)(a + 0x30) += y;
            func_8004766C(a);
        }
        if (func_80049250(a, 0, 0x32) == 1) {
            *(s16 *)(a + 0x4A) = -0x100;
            a[5]++;
            *(s16 *)(a + 0x44) = *(s16 *)(a + 0x44) >> 1;
        } else {
            *(s16 *)(a + 0x4A) += 0x30;
            if (*(s16 *)(a + 0x4A) > 0x1000) {
                *(s16 *)(a + 0x4A) = 0x1000;
            }
        }
        break;
    }
    if (func_8007778C(a) != 0) {
        func_80077B5C(a);
    }
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80116904);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80116D3C);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80116F70);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80117198);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8011731C);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80117628);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80117920);

typedef struct { s16 m[3][3]; s32 t[3]; } Mat;
typedef struct { u8 pad[0x3C]; s32 x, y, z; } CamT;
extern Mat D_1F800000_c2ec;
extern Mat D_1F8000F8_c2ec;
extern s32 D_1F800014_c2ec[];
extern CamT D_1F8000D0_c2ec;
extern RingVec D_80148668[];
extern void *D_800BF544;
extern u32 *D_800ED8C8;
#define T2_avsz3() __asm__ volatile(".word 0x4B58002D")
#define T2_rtpt4() __asm__ volatile("nop;nop;nop;nop;.word 0x4A280030;nop;nop;nop;nop")
#define T2_stotz(r0) __asm__ volatile("swc2 $7, 0( %0 )" : : "r"(r0) : "memory")
#define T2_stsxy3_f3(r0) __asm__ volatile("addu $12,%0,$0;" "swc2 $12,8($12);" "swc2 $13,12($12);" "swc2 $14,16($12)" : : "r"(r0) : "$12", "$13", "$14", "$15", "memory")
void func_80117E84(u8 *arg0)
{
    u8 *a = arg0;
    Mat *m = &D_1F800000_c2ec;
    s32 s = H(a, 0x50);
    s16 c;
    s32 dq;
    u32 col;
    u32 *p;
    u32 *q;
    RingVec *v;
    s16 i;
    s32 flg;
    s32 otz;
    u32 *ot;

    dq = ((s - 0x14) << 7) / H(a, 0x54);
    m->m[0][1] = 0;
    m->m[0][2] = 0;
    m->m[1][0] = 0;
    m->m[1][2] = 0;
    m->m[2][0] = 0;
    m->m[2][1] = 0;
    m->t[2] = 0;
    m->t[1] = 0;
    m->t[0] = 0;
    m->m[0][0] = s << 4;
    m->m[1][1] = s << 4;
    m->m[2][2] = s << 4;
    c = 0x80 - dq;
    col = 0x4A000000 | (c << 16) | (c << 8) | c;
    gte_MulMatrix0(&D_1F8000F8_c2ec, &D_1F800000_c2ec, &D_1F800000_c2ec);
    gte_ldv0(a + 0x2C);
    gte_rtv0();
    gte_stlvnl(D_1F800014_c2ec);
    m->t[0] += D_1F8000D0_c2ec.x;
    m->t[1] += D_1F8000D0_c2ec.y;
    m->t[2] += D_1F8000D0_c2ec.z;
    gte_SetRotMatrix(m);
    gte_SetTransMatrix(m);
    v = D_80148668;
    p = D_800BF544;
    for (i = 0; i < 7; i++, v += 2) {
        gte_ldv3(&v[0], &v[1], &v[2]);
        T2_rtpt4();
        gte_stflg(&flg);
        if (flg < 0) {
            continue;
        }
        T2_avsz3();
        T2_stotz(&otz);
        otz += H(a, 0x32);
        otz = (otz >> (otz >> 10)) + ((otz >> 10) << 9);
        if ((u32)(otz - 4) >= 0x7FC) {
            otz = -1;
        }
        if (otz <= 0) {
            continue;
        }
        T2_stsxy3_f3(p);
        p[1] = col;
        p[5] = 0x55555555;
        ot = &D_800ED8C8[otz];
        do {
            p[0] = *ot | 0x05000000;
        } while (0);
        *ot = (u32)p;
        p += 6;
        q = p;
        func_80083DE0(q, 0, 1, 0x35, 0);
        ot = &D_800ED8C8[otz];
        do {
            q[0] = *ot | 0x02000000;
        } while (0);
        *ot = (u32)q;
        q += 3;
        p = q;
        T2_stsxy3_f3(p);
        p[1] = col;
        p[5] = 0x55555555;
        *(s16 *)((u8 *)p + 8) += 2;
        *(s16 *)((u8 *)p + 12) += 2;
        *(s16 *)((u8 *)p + 16) += 2;
        *(s16 *)((u8 *)p + 10) += 1;
        *(s16 *)((u8 *)p + 14) += 1;
        *(s16 *)((u8 *)p + 18) += 1;
        ot = &D_800ED8C8[otz];
        do {
            p[0] = *ot | 0x05000000;
        } while (0);
        *ot = (u32)p;
        p += 6;
        q = p;
        func_80083DE0(q, 0, 1, 0x55, 0);
        ot = &D_800ED8C8[otz];
        do {
            q[0] = *ot | 0x02000000;
        } while (0);
        *ot = (u32)q;
        q += 3;
        p = q;
    }
    D_800BF544 = p;
}

extern u8 D_800A0B38[];
extern u8 D_801450DC[];
extern u8 D_80145110[];
void func_80118374(u8 *a)
{
    s16 sp[6];
    s8 *s = (s8 *)(a + 0x50);
    u8 *e;

    switch (a[4]) {
    case 0:
        *(u8 **)(a + 0x50) = D_800A0B38;
        *(s16 *)(a + 0x48) = 0;
        *(s16 *)(a + 0x4A) = 0;
        *(s16 *)(a + 0x4C) = 0;
        s[4] = 0;
        a[0x29] = 0;
        a[4] = 1;
        a[5] = 0;
    case 1:
        *(u8 **)(a + 0x3C) = D_801450DC + s[4] * 4;
        a[0x29] = D_80145110[s[4]];
        if (++s[4] >= 0xC) {
            a[4] = 2;
        } else {
            func_8002B278(a);
        }
        switch (a[5]) {
        case 2: break;
        case 0:
            if (++s[4] >= 6) {
                a[5] = 1;
            }
            break;
        case 1:
            sp[1] = *(s16 *)(a + 0x2C);
            sp[3] = *(s16 *)(a + 0x2E) - 0x8C;
            sp[5] = *(s16 *)(a + 0x30);
            e = func_8003116C(8, sp, 0);
            if (e != NULL) {
                e[0x28] = a[0x28];
            }
            a[5]++;
            break;
        }
        break;
    case 2:
    case 3:
        func_8007A624(a);
        break;
    }
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80118514);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_801187F4);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80118CC4);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8011920C);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80119578);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8011973C);

extern u8 D_1F8000D0_b839[];
extern u8 D_801387C0[];
extern u8 D_80138160[];
extern u8 D_8014511C[];
extern u8 D_801450B4[];
void func_801198CC(u8 *a)
{
    u8 *p;
    u8 *s;
    s32 *q = (s32 *)(a + 0x50);

    switch (a[4]) {
    case 0:
        M2C_FIELD(a, u8 **, 0x40) = D_8014511C;
        M2C_FIELD(a, u8 **, 0x3C) = D_8014511C;
        M2C_FIELD(a, u8 **, 0x50) = D_801450B4;
        a[4] = 1;
        a[5] = 0;
        a[0x29] = 0;
    case 1:
        switch (a[5]) {
        case 0:
            if (M2C_FIELD(a, s16 *, 0x2E) < q[1]) {
                a[5] = 1;
            } else {
                M2C_FIELD(a, s16 *, 0x2E) -= 0x1A;
                M2C_FIELD(a, s16 *, 0x2C) += -0x10 + (func_8009A450() >> 11);
                M2C_FIELD(a, s16 *, 0x30) += -0x10 + (func_8009A450() >> 11);
            }
            break;
        case 1:
            p = M2C_FIELD(a, u8 **, 0x40);
            M2C_FIELD(a, u8 **, 0x3C) = p;
            if (p == NULL) {
                a[4] = 2;
            }
            break;
        }
        if (func_8002B278(a) == 0) {
            func_80031708(a);
            break;
        }
        s = D_1F8000D0_b839;
        M2C_FIELD(a, s16 *, 0x48) = -M2C_FIELD(s, s16 *, 0x20);
        M2C_FIELD(a, s16 *, 0x4A) = -M2C_FIELD(s, s16 *, 0x22);
        M2C_FIELD(a, s16 *, 0x4C) = -M2C_FIELD(s, s16 *, 0x24);
        break;
    case 2:
    case 3:
        func_8007A624(a);
        break;
    }
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80119A48);

extern s16 D_1F800160;
extern s16 D_1F800162;
extern s16 D_1F800164;
typedef struct { s16 v[9]; } FxParam914;
typedef struct { FxParam914 e[10]; } FxTable914;
extern FxTable914 D_80109AA4;
/* func_8011BD98, inlined (its parameters in another order) */
static inline void Spawn914(s16 *pos, s32 k, s32 life)
{
    FxTable914 t;
    u8 *e;
    u8 *q;

    e = (u8 *)func_80031220(0x914, pos, -0x1E);
    q = e + 0x50;
    t = D_80109AA4;
    if (e != NULL) {
        *(s16 *)(q + 2) = t.e[k].v[0];
        *(s16 *)(q + 4) = t.e[k].v[1];
        *(s16 *)(q + 6) = t.e[k].v[2];
        *(s16 *)(q + 8) = t.e[k].v[3];
        *(s16 *)(q + 0xC) = t.e[k].v[4];
        *(s16 *)(q + 0xE) = t.e[k].v[5];
        *(s16 *)(q + 0x10) = t.e[k].v[6];
        *(s16 *)(q + 0x12) = t.e[k].v[7];
        *(s16 *)(q + 0) = t.e[k].v[8];
        *(s16 *)(q + 0xA) = life;
    }
}
void func_80119C84(u8 *a)
{
    u8 *o = *(u8 **)(a + 0x10);
    s32 t;

    switch (a[4]) {
    case 0:
        *(s16 *)(a + 0x32) = -0x5A;
        *(s16 *)(a + 0x48) = func_8009A450() | 1;
        *(s16 *)(a + 0x4A) = func_8009A450() | 1;
        *(s16 *)(a + 0x4C) = 5;
        *(s16 *)(a + 0x4E) = 0;
        a[4] = 1;
    case 1:
        t = ++*(s16 *)(a + 0x4E);
        if (t == 0x1E || t == 0xDB) {
            s16 p[4];
            p[0] = *(s16 *)(*(u8 **)(o + 0xD0) + 0x2C);
            p[1] = -0x2208;
            p[2] = *(s16 *)(*(u8 **)(o + 0xD0) + 0x34);
            Spawn914(p, 1, 0x10);
        }
        if (t >= 0x258) {
            a[4] = 2;
        }
        break;
    case 2:
    case 3:
        func_8007A624(a);
        break;
    }
}

void func_80119EC4(u8 *a)
{
    u8 *o = *(u8 **)(a + 0x10);
    s32 t;

    switch (a[4]) {
    case 0:
        *(s16 *)(a + 0x32) = -0x5A;
        *(s16 *)(a + 0x48) = func_8009A450() | 1;
        *(s16 *)(a + 0x4A) = func_8009A450() | 1;
        *(s16 *)(a + 0x4E) = 0;
        a[4] = 1;
    case 1:
        t = ++*(s16 *)(a + 0x4E);
        if (t >= 0x3C) {
            a[4] = 2;
        } else if (t == 8 || t == 0x32) {
            s16 p[4];
            p[0] = *(s16 *)(o + 0x2E);
            p[1] = -0x2172;
            p[2] = *(s16 *)(o + 0x36);
            Spawn914(p, 4, 0xC);
        }
        break;
    case 2:
    case 3:
        func_8007A624(a);
        break;
    }
}

void func_8011A0F8(u8 *a)
{
    u8 *o = *(u8 **)(a + 0x10);
    s32 t;

    switch (a[4]) {
    case 0:
        *(s16 *)(a + 0x32) = -0x5A;
        *(s16 *)(a + 0x48) = func_8009A450() | 1;
        *(s16 *)(a + 0x4A) = func_8009A450() | 1;
        *(s16 *)(a + 0x4E) = 0;
        a[4] = 1;
    case 1:
        t = ++*(s16 *)(a + 0x4E);
        if ((u32)(t - 0x30) < 0x6A && (t - 0x30) % 14 == 0) {
            func_80074590(0x33, -7, 0xF);
        }
        if (t == 0x16) {
            s16 p[4];
            p[0] = *(s16 *)(o + 0x2E);
            p[1] = -0x2208;
            p[2] = *(s16 *)(o + 0x36);
            Spawn914(p, 1, 0x40);
        }
        if ((u32)(t - 0x22) < 0x7D) {
            s16 p[4];
            if (((t - 0x22) & 7) == 0) {
                p[0] = *(s16 *)(o + 0x2E);
                p[1] = *(s16 *)(o + 0x32);
                p[2] = *(s16 *)(o + 0x36);
                Spawn914(p, 0, 4);
            }
            if (((t - 0x22) & 1) == 0) {
                p[0] = *(s16 *)(o + 0x2E);
                p[1] = *(s16 *)(o + 0x32) - 0x190;
                p[2] = *(s16 *)(o + 0x36) - 0x64;
                Spawn914(p, 2, 4);
            }
        }
        if ((u32)(t - 0x9C) < 0x2D && ((t - 0x9C) & 0xF) == 0) {
            s16 p[4];
            p[1] = D_1F800162 - 0x320;
            p[0] = D_1F800160 + (func_8009A450() & 0x1FF) - 0x100;
            p[2] = D_1F800164 + (func_8009A450() & 0x1FF) + 0x200;
            Spawn914(p, 0, 0xF);
        }
        if (t >= 0xD2) {
            a[4] = 2;
        }
        break;
    case 2:
    case 3:
        func_8007A624(a);
        break;
    }
}

typedef struct { s16 v[4]; } FxPos914;
extern FxPos914 D_80109B58;
void func_8011A7E8(u8 *a)
{
    s32 t;

    switch (a[4]) {
    case 0:
        *(void **)(a + 0x10) = NULL;
        *(s16 *)(a + 0x32) = -0x5A;
        *(s16 *)(a + 0x48) = func_8009A450() | 1;
        *(s16 *)(a + 0x4A) = func_8009A450() | 1;
        *(s16 *)(a + 0x4E) = 0;
        a[4] = 1;
    case 1:
        t = ++*(s16 *)(a + 0x4E);
        if (t == 0xBD || t == 0xCC) {
            FxPos914 p = D_80109B58;
            Spawn914(p.v, 3, 0x40);
        }
        if (t == 0xC2) {
            *(void **)(a + 0x10) = (void *)func_800310F4(0x908, -0x14);
        }
        if (t >= 0x167 && *(u8 **)(a + 0x10) != NULL) {
            (*(u8 **)(a + 0x10))[4] = 2;
        }
        if ((u32)(t - 0xE4) < 0x85) {
            s16 p[4];
            if (((t - 0xC2) & 3) == 0) {
                p[0] = 0x2F48;
                p[1] = -0x25E0;
                p[2] = 0x2134;
                Spawn914(p, 6, 6);
            }
        }
        if (t >= 0x16D && ((t - 0x16D) & 7) == 0) {
            s16 p[4];
            p[1] = D_1F800162 - 0x4B0;
            p[0] = D_1F800160 + (func_8009A450() & 0x1FF) - 0x180;
            p[2] = D_1F800164 + (func_8009A450() & 0x1FF) - 0x180;
            Spawn914(p, 0, 0xF);
        }
        if (*(s16 *)(a + 0x4E) >= 0x1AE) {
            a[4] = 2;
        }
        break;
    case 2:
    case 3:
        func_8007A624(a);
        break;
    }
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8011AD6C);

#define W(p, o) M2C_FIELD(p, u32 *, o)
typedef struct {
    u8 b[6][4];
} FlickerTbl;
extern FlickerTbl D_80109B60;
void func_8011B124(u8 *a) {
    FlickerTbl t = D_80109B60;

    switch (a[4]) {
    case 0:
        a[4] = 1;
        W(a, 0x60) = 0x100;
        W(a, 0x64) = 0x200;
        W(a, 0x68) = 0x200;
        W(a, 0x6C) = 0x100;
        M2C_FIELD(a, s16 *, 0x32) = -200;
    case 1:
    case 2:
        W(a, 0x60) -= W(a, 0x60) >> 2;
        W(a, 0x64) -= W(a, 0x64) >> 2;
        W(a, 0x68) -= W(a, 0x68) >> 2;
        W(a, 0x6C) -= W(a, 0x6C) >> 2;
        if (W(a, 0x6C) < 9) {
            a[4] = 3;
        }
        if (++a[7] >= 6) {
            a[7] = 0;
        }
        W(a, 0x50) = (W(a, 0x60) * t.b[a[7]][0]) >> 4;
        W(a, 0x54) = (W(a, 0x64) * t.b[a[7]][1]) >> 4;
        W(a, 0x58) = (W(a, 0x68) * t.b[a[7]][2]) >> 4;
        W(a, 0x5C) = (W(a, 0x6C) * t.b[a[7]][3]) >> 4;
        a[1] = 1;
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

s32 func_8011B344(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    void *temp_v0;

    temp_v0 = func_8003116C(0x917, arg0, (s16) arg1);
    if (temp_v0 != NULL) {
        M2C_FIELD(temp_v0, s16 *, 0x50) = (s16) arg2;
        M2C_FIELD(temp_v0, s16 *, 0x54) = (s16) arg3;
    }
    return (s32) temp_v0;
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8011B398);

#define gte_ldfcdir(r0, r1, r2) __asm__ volatile("ctc2	%0, $21;" "ctc2	%1, $22;" "ctc2	%2, $23" : : "r"(r0), "r"(r1), "r"(r2))
extern s32 D_1F800090[];
void f_UpdateWaterTempleQuestPropActor();
void func_8011B4A8(u8 *p)
{
    u8 buf[0x30];
    s32 *d;
    s32 v, a, b;

    func_800318A0(p + 0x2C, p + 0x50, p + 0x48);
    d = D_1F800090;
    gte_ldfcdir(0, 0, 0);
    v = *(s32 *)(p + 0x54);
    a = *(s32 *)(p + 0x3C);
    b = *(s16 *)(p + 0x32);
    *d = v;
    func_80027768(a, 0, b, p[0x29]);
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8011B510);

void func_8011B5EC(u8 *p)
{
    u8 buf[0x30];
    s32 *d;
    s32 v, a, b;

    func_800318A0(p + 0x2C, p + 0x50, p + 0x48);
    d = D_1F800090;
    gte_ldfcdir(0, 0, 0);
    v = *(s32 *)(p + 0x54);
    a = *(s32 *)(p + 0x3C);
    b = *(s16 *)(p + 0x32);
    *d = v;
    func_80027768(a, 0, b, p[0x29]);
}

typedef struct {
    s16 a;
    s16 b;
    s16 c;
    s16 d;
} SV;
extern u8 D_800A1CD4[];
extern u8 D_80144C10[];
extern s32 D_1F800090_3460;
void func_8011B654(u8 *p)
{
    SV v;

    v.a = *(s16 *)(p + 0x2E);
    v.b = *(s16 *)(p + 0x32);
    v.c = *(s16 *)(p + 0x36);
    func_800318A0(&v, D_800A1CD4, p + 0x54);
    D_1F800090_3460 = 0;
    func_80027768(D_80144C10, 0, -0xA, p[0x60]);
}

typedef struct { s32 a, b; } Pair9F44;
typedef struct { Pair9F44 e[14]; } Tbl9F44;
extern Tbl9F44 D_80109864;
void func_8011B6C0(u8 *a)
{
    Tbl9F44 t = D_80109864;

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
        func_8002B278(a);
        break;
    case 2:
    case 3:
        func_8007A624(a);
        break;
    }
}

void func_8011B7E4(u8 *p) {
    s32 *d = D_1F800090;
    s32 i;

    gte_ldfcdir(0, 0, 0);
    *d = 0;
    for (i = 0; i < 4; i++) {
        func_80031AC4(p + 0x2C, p + 0x50, p + 0x48);
        func_80027768(M2C_FIELD(p, s32 *, 0x3C), 0, M2C_FIELD(p, s16 *, 0x32), 0);
        M2C_FIELD(p, s16 *, 0x4E) += 0x400;
    }
    func_80027CB4(p);
}

void func_8011B878(u8 *a)
{
    u32 v;
    switch (a[4]) {
    case 0:
        *(s16 *)(a + 0x32) = -330;
        a[4] = 1;
        a[5] = 0;
    case 1:
        v = a[5];
        a[1] = 1;
        if (v < 36) {
            a[5] = v + 1;
        }
        break;
    case 2:
    case 3:
        func_8007A624(a);
        break;
    }
}

void func_8011B900(void) {
    s32 i;
    s32 ang;
    RingVec *p;

    p = D_80148668;
    for (i = 0; i < 15; i++, p++) {
        ang = (i << 12) / 15;
        p->x = func_80083F50(ang) >> 4;
        p->y = 0;
        p->z = func_80083E80(ang) >> 4;
    }
    p->x = D_80148668[0].x;
    p->y = D_80148668[0].y;
    p->z = D_80148668[0].z;
}

void func_8011B9D0(u8 *a) {
    RiseMotion *m = (RiseMotion *)(a + 0x50);

    switch (a[4]) {
    case 0:
        m->pos = 20;
        a[4] = 1;
        m->vel = 10;
        M2C_FIELD(m, s16 *, 4) = 200;
    case 1:
        func_8002B278(a);
        m->pos += m->vel;
        if (m->pos > 0xC8) {
            a[4] = 2;
        }
        break;
    case 2:
    case 3:
        func_8007A624(a);
        break;
    }
}

typedef struct { s16 pos; s16 vel; s16 max; } RiseMotion3;
void func_8011BA90(u8 *a) {
    RiseMotion3 *m = (RiseMotion3 *)(a + 0x50);

    switch (a[4]) {
    case 0:
        a[4] = 1;
        m->vel = 10;
    case 1:
        func_8002B278(a);
        m->pos += m->vel;
        if (m->pos > m->max) {
            a[4] = 2;
        }
        break;
    case 2:
    case 3:
        func_8007A624(a);
        break;
    }
}

void func_8011BB40(u8 *a)
{
    switch (a[4]) {
    case 0:
        a[4] = 1;
        *(s16 *)(a + 0x4E) = 0;
    case 1:
        if (*(s16 *)(a + 0x4E) < 8 && (D_1F80017C_0fe7 & 1)) {
            *(s16 *)(a + 0x4E) += 1;
        }
        a[1] = 1;
        break;
    case 2:
        if (*(s16 *)(a + 0x4E) <= 0) {
            goto kill;
        }
        if (D_1F80017C_0fe7 & 1) {
            *(s16 *)(a + 0x4E) -= 1;
        }
        a[1] = 1;
        break;
    case 3:
    kill:
        func_8007A624(a);
        break;
    }
}

#define AREA_gte_ldv0(r0) __asm__ volatile("lwc2	$0, 0( %0 );" "lwc2	$1, 4( %0 )" : : "r"(r0))
typedef struct { s16 x, y, z, pad; } AreaSVec;
extern u8 D_80143D48[];
extern s32 D_80143D44;
extern s32 D_1F800088;
void func_8011BC14(u8 *a) {
    AreaSVec v;
    u8 *p;
    s32 r, k;

    p = M2C_FIELD(a, u8 **, 0x78);
    if (p == NULL) {
        p = D_80143D48;
    }
    func_800329E0(6);
    v.x = M2C_FIELD(a, s16 *, 0x2E);
    v.y = M2C_FIELD(a, s16 *, 0x32);
    v.z = M2C_FIELD(a, s16 *, 0x36);
    AREA_gte_ldv0(&v);
    if (func_800317CC(-10) == 0) {
        D_1F800088 = D_1F800084;
        r = func_8009A450();
        k = D_80143D44;
        r &= 0x7FF;
        D_1F800090_3460 = r;
        M2C_FIELD(a, u8 **, 0x78) = func_80027A4C(p, k);
    }
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8011BCC8);

void func_8011BD98(s32 k, s16 *pos, s32 life)
{
    Spawn914(pos, k, life);
}

void func_8011BF0C(u8 *a)
{
    u8 *o = *(u8 **)(a + 0x10);

    switch (a[4]) {
    case 0:
        a[4] = 1;
    case 1:
        *(s16 *)(a + 0x2C) = *(s16 *)(o + 0x2E);
        *(s16 *)(a + 0x2E) = *(s16 *)(o + 0x32);
        *(s16 *)(a + 0x30) = *(s16 *)(o + 0x36);
        func_80031220(0x914, a + 0x2C, -0x1E);
        break;
    case 2:
    case 3:
        func_8007A624(a);
        break;
    }
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8011BFA8);

void func_8011C0C0(void *a, void *b, s32 x, s32 y)
{
    u8 *e;
    u8 *q;

    e = func_80031220(0x914, b, -0x1E);
    q = e + 0x50;
    if (e != NULL) {
        *(s16 *)(q + 2) = y;
        *(s16 *)(q + 4) = 0x7FF;
        *(s16 *)(q + 6) = 3;
        *(s16 *)(q + 8) = 6;
        *(s16 *)(q + 0xC) = 0x3F;
        *(s16 *)(q + 0xE) = 0x1F;
        *(s16 *)(q + 0x10) = 0x3F;
        *(s16 *)(q + 0x12) = 0x100;
        *(s16 *)(e + 0x50) = 2;
        *(s16 *)(q + 0xA) = x;
    }
}

typedef struct { u8 pad[0x48]; s32 unk48; } AreaState808;
extern s8 D_1F80017C[];
typedef struct { s16 x, y, z; } AreaVec3s;
extern AreaVec3s D_8014527C[];
void func_8011C148(u8 *a) {
    s16 i;

    switch (a[6]) {
    case 0:
        if (--M2C_FIELD(a, s16 *, 0x40) <= 0) {
            a[6]++;
        }
        break;
    case 1:
        if (!(*(u16 *)D_1F80017C & 0xF)) {
            M2C_FIELD(a, s16 *, 0xB8) = D_8014527C[M2C_FIELD(a, s16 *, 0x7A)].x;
            M2C_FIELD(a, s16 *, 0xBA) = D_8014527C[M2C_FIELD(a, s16 *, 0x7A)].y;
            M2C_FIELD(a, s16 *, 0xBC) = D_8014527C[M2C_FIELD(a, s16 *, 0x7A)].z;
            M2C_FIELD(a, s16 *, 0x7A) = (M2C_FIELD(a, s16 *, 0x7A) + 1) & 7;
        }
        break;
    }
    if ((s16)func_8011CC48(a)) {
        func_8011CB58(a, 0);
        a[5] = 3;
        a[6] = 0;
        M2C_FIELD(a, s16 *, 0x6C) = 0;
    }
}

#define F16(p, o) M2C_FIELD(p, s16 *, o)
#define C0(p) M2C_FIELD(p, u8 **, 0xC0)
#define F16(p, o) M2C_FIELD(p, s16 *, o)
#define C0(p) M2C_FIELD(p, u8 **, 0xC0)
void func_8011C260(u8 *a)
{
    s16 s = F16(a, 0x76);
    u8 *g;

    switch (s) {
    case 0:
        if (a[0x2B] == 0) {
            return;
        }
        F16(a, 0x76)++;
        break;
    case 1:
        if (a[0x2B] & 0x80) {
            F16(a, 0x48) = F16(a, 0x4C) = 0x200;
            g = D_800BF808;
            if (M2C_FIELD(g, s32 *, 0x50) == 0) {
                func_8004CBD8(a, 0);
                M2C_FIELD(g, s32 *, 0x50) = s;
            }
        } else {
            F16(a, 0x48) = F16(a, 0x4C) = 0x180;
        }
        F16(a, 0x52) = -8;
        if (func_80077768(a[0x46] << 4, F16(a, 0x56), 1)) {
            F16(a, 0x4C) = -F16(a, 0x4C);
            F16(a, 0x52) = -F16(a, 0x52);
        }
        a[0x2B] = 0;
        a[0x5F] = 1;
        if (a[1]) {
            func_80074590(0xF, -5, 0);
        }
        F16(a, 0x76)++;
        break;
    case 2:
        F16(C0(a), 0xC) += F16(a, 0x4C);
        if (F16(C0(a), 0xC) < -F16(a, 0x48) || F16(a, 0x48) < F16(C0(a), 0xC)) {
            if (F16(a, 0x4C) > 0) {
                F16(C0(a), 0xC) = F16(a, 0x48);
            } else {
                F16(C0(a), 0xC) = -F16(a, 0x48);
            }
            F16(a, 0x48) -= 0x18;
            if (F16(a, 0x48) <= 0) {
                F16(C0(a), 0xC) = 0;
                F16(a, 0x76) = 0;
                break;
            }
            if (F16(a, 0x48) <= 0xA0) {
                a[0x5F] = 0;
            }
            F16(a, 0x4C) = -F16(a, 0x4C);
            F16(a, 0x52) = -F16(a, 0x52);
        }
        F16(a, 0x4C) += F16(a, 0x52);
        if (F16(a, 0x4C) > 0 && F16(a, 0x4C) < 0x60) {
            F16(a, 0x4C) = 0x60;
        } else if (F16(a, 0x4C) < 0) {
            if (F16(a, 0x4C) > -0x60) {
                F16(a, 0x4C) = -0x60;
            }
        }
        break;
    }
    if (a[0x2B]) {
        F16(a, 0x76) = 1;
    }
}

void func_8011C4BC(u8 *a)
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
            func_8011CB58(a, a[0x5E]);
            a[6] = 1;
            M2C_FIELD(a, s16 *, 0x6C) = 1;
        }
    } else if ((s16)func_8011CC48(a)) {
        M2C_FIELD(*(u8 **)(a + 0xC0), u16 *, 0x38) = M2C_FIELD(a, s16 *, 0x64);
        M2C_FIELD(*(u8 **)(a + 0xC0), u16 *, 0x3A) = M2C_FIELD(a, s16 *, 0x66);
        func_8011CB58(a, 0);
        a[6] = 0;
        M2C_FIELD(a, s16 *, 0x6C) = 0;
    }
    if (M2C_FIELD(a, s16 *, 0x50) > 0x20) {
        M2C_FIELD(a, s16 *, 0x50)--;
    }
    func_8011CCAC(a);
}

void func_8011C754(void *arg0) {
    u8 temp_v1;
    u8 temp_v1_2;

    temp_v1 = M2C_FIELD(arg0, u8 *, 4);
    switch (temp_v1) {                              /* switch 1; irregular */
    case 0:                                         /* switch 1 */
        func_8011C890(arg0);
        return;
    case 1:                                         /* switch 1 */
        func_8007778C(arg0);
        if (D_800BF873 == 0) {
            temp_v1_2 = M2C_FIELD(arg0, u8 *, 5);
            switch (temp_v1_2) {                    /* switch 2; irregular */
            case 0:                                 /* switch 2 */
                func_8011C148(arg0);
                break;
            case 3:                                 /* switch 2 */
                func_8011C4BC(arg0);
                break;
            case 4:                                 /* switch 2 */
                func_8011C974(arg0);
                break;
            }
            func_8011CA98(arg0);
            func_8011C260(arg0);
            M2C_FIELD(arg0, s8 *, 0x29) = 0;
        }
        if (M2C_FIELD(arg0, u8 *, 1) != 0) {
            func_800518FC(arg0);
            return;
        }
        return;
    case 2:                                         /* switch 1 */
        func_8011C9C4(arg0);
        return;
    case 3:                                         /* switch 1 */
        func_8007A624(arg0);
        break;
    }
}

void func_8011C890(u8 *a)
{
    if (func_80051B70(a, 0xC, 0x67) == 0) {
        u8 *c;
        H(a, 0x62) = 1;
        H(*(u8 **)(a + 0xC0), 0x38) = 0x1000;
        H(*(u8 **)(a + 0xC0), 0x3A) = 0x1000;
        H(a, 0x64) = 0x1000;
        H(a, 0x66) = 0x1000;
        H(a, 0xBC) = 0x1000;
        H(a, 0xBA) = 0x1000;
        H(a, 0xB8) = 0x1000;
        H(a, 0x40) = 0x14;
        c = *(u8 **)(a + 0xC0);
        a[0] = 1;
        H(a, 0x6C) = 0;
        H(a, 0x76) = 0;
        H(a, 0x78) = 0;
        H(a, 0x7A) = 0;
        a[0x29] = 0;
        a[0x2B] = 0;
        a[0x5E] = 0;
        a[0x5F] = 0;
        a[4]++;
        H(c, 0x3C) = H(c, 0x38);
        func_8011CCAC(a);
        if (func_80048750(a) != 0) {
            u16 x = D_1F8001A0_b0de_1f9a;
            u16 y = D_1F8001A2_7766;
            H(a, 0x56) = x;
            H(a, 0x58) = y & 0xFFF;
        }
        func_800518FC(a);
    }
}

void func_8011C974(u8 *a)
{
    if (a[0x29] == 0) {
        func_8011CB58(a, 1);
        a[5] = 3;
        a[6] = 1;
        *(s16 *)(a + 0x6C) = 1;
    }
}

void func_8011C9C4(u8 *a) {
    func_80027144(M2C_FIELD(M2C_FIELD(a, u8 **, 0xC0), s32 *, 0x40), a + 0x2C, 0xA00, -0x7FDC);
    func_80074590(0xC, 0, 0);
    M2C_FIELD(a, s16 *, 0x32) -= 0x96;
    func_80027144(M2C_FIELD(M2C_FIELD(a, u8 **, 0xC0), s32 *, 0x40), a + 0x2C, 0xA00, 0x2C);
    func_80074590(0xC, 0, 0);
    if (func_80040B48(0x7F) >= 0) {
        D_800BF870.pad1[0x15C] |= 2;
        if (++D_800BF870.pad1[0x1C0] >= 10) {
            func_8004ED94(0x6E, 0x41);
        }
    }
    a[4] = 3;
}

void func_8011CA98(u8 *a)
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

void func_8011CB58(u8 *a, s16 b)
{
    s32 v = (F16(a, 0x62) << 5) + 0x30;

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

s32 func_8011CC48(u8 *a)
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

void func_8011CCAC(void *arg0) {
    s32 temp_v0_2;
    u32 temp_v0;

    temp_v0 = (u16) M2C_FIELD(M2C_FIELD(arg0, void **, 0xC0), u16 *, 0x38) >> 5;
    M2C_FIELD(arg0, s16 *, 0x80) = (s16) temp_v0;
    M2C_FIELD(arg0, s16 *, 0x82) = (s16) (temp_v0 * 2);
    temp_v0_2 = (s32) (M2C_FIELD(M2C_FIELD(arg0, void **, 0xC0), u16 *, 0x3A) * 0x113) >> 0xC;
    M2C_FIELD(arg0, s16 *, 0x84) = (s16) temp_v0_2;
    M2C_FIELD(arg0, s16 *, 0x86) = (s16) (temp_v0_2 * 2);
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8011CD00);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8011CEA4);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8011D144);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8011D3A0);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8011D458);

s32 func_8011D798(u8 *a)
{
    u8 *p = D_800E7E80;
    u8 *g;
    u8 *q;
    u8 *c;

    switch (a[6]) {
    case 0:
        if (p[0x2A] != a[0x2A]) {
            goto common;
        }
        if (p[0x181] == 0) {
            return 0;
        }
        if (p[0x61] != 0) {
            return 0;
        }
        {
            s32 one;
            u8 *h;
            u8 *sp;
            s32 m;

            a[0] = 2;
            a[6]++;
            func_80054198(p);
            h = D_800BF808;
            sp = &D_1F800137;
            one = 1;
            m = a[0x5F];
            h[0x10] = one;
            h[0x17] = (one - m) * 16;
            h[0xF] = a[3];
            if (*sp == 0) {
                *sp = 2;
            }
            *(s32 *)(h + 0x48) = one;
            *(s16 *)(a + 0x68) = one;
        }
        break;
    case 1:
        if (*(s16 *)(a + 0x68) != 0) {
            if (*(volatile u8 *)&D_800BF816 == 0) {
                return 0;
            }
            a[6]++;
        } else {
            if (D_800BF816 == 0) {
                return 0;
            }
            a[6]++;
        }
        break;
    case 2:
        g = D_800BF808;
        if (g[0x10] != 2 || g[7] != 0) {
            return 0;
        }
        a[0] = 1;
        a[6]++;
        *(s16 *)(a + 0x68) = 0;
        a[0x5F] = 1 - a[0x5F];
        *(s16 *)(a + 0x84) += 0x320;
        *(s16 *)(a + 0x86) += 0x320;
        break;
    case 3:
        if (a[0x29] == 0 || p[0x17B] != 0) {
            goto common;
        }
        if (p[0x181] != 0) {
            q = D_800BF808;
            if (q[7] != 0) {
                return 0;
            }
            a[0] = 2;
            a[6]++;
            func_80054198(p);
            q[0x10] = 3;
            if (D_1F800137 == 0) {
                D_1F800137 = 2;
            }
            *(s32 *)(q + 0x48) = 1;
            *(s16 *)(a + 0x68) = 1;
        }
        break;
    common:
        c = D_800BF808;
        if (*(s32 *)(c + 0x48) == 0) {
            return 0;
        }
        a[6]++;
        *(s32 *)(c + 0x48) = 0;
        break;
    case 4:
        g = D_800BF808;
        if (g[0x10] == 4) {
            if (g[7] != 0) {
                return 0;
            }
            a[6]++;
            g[0x10] = 0;
        } else {
            if (g[0x10] != 0) {
                return 0;
            }
            a[6]++;
        }
        break;
    case 5:
        a[0] = 1;
        a[6]++;
        *(s16 *)(a + 0x68) = 0;
        a[0x5F] = 1 - a[0x5F];
        *(s16 *)(a + 0x84) -= 0x320;
        *(s16 *)(a + 0x86) -= 0x320;
        break;
    case 6:
        if (p[0x2A] != a[0x2A]) {
            a[6] = 0;
            return 1;
        }
        break;
    }
    return 0;
}

s32 func_8011DAA4(u8 *a)
{
    u8 *p = D_800E7E80;
    u8 *g;
    u8 *q;
    u8 *c;

    switch (a[6]) {
    case 0:
        if (p[0x2A] != a[0x2A]) {
            goto common;
        }
        if (p[5] != 0) {
            return 0;
        }
        {
            s32 one;
            u8 *h;
            s32 m;

            a[6]++;
            D_1F800137 = 2;
            h = D_800BF808;
            one = 1;
            m = a[0x5F];
            h[0x10] = 5;
            h[0x17] = (one - m) * 16;
            h[0xF] = a[3];
            func_800732C0(a);
            *(s32 *)(h + 0x48) = one;
            a[0x29] = *(s16 *)(a + 0x68) = one;
        }
        break;
    case 1:
        if (*(s16 *)(a + 0x68) != 0) {
            if (func_80072E60(a) != 0 && D_800BF816 != 0) {
                a[6]++;
                func_80072EFC(a);
            }
        } else if (D_800BF816 != 0) {
            *(s16 *)(a + 0x50) = 0x400;
            a[6]++;
            func_80072EFC(a);
        }
        break;
    case 2:
        g = D_800BF808;
        if (g[0x10] != 2 || g[7] != 0) {
            return 0;
        }
        a[0] = 1;
        a[6]++;
        *(s16 *)(a + 0x68) = 0;
        a[0x5F] = 1 - a[0x5F];
        *(s16 *)(a + 0x84) += 0x320;
        *(s16 *)(a + 0x86) += 0x320;
        break;
    case 3:
        if (a[0x29] == 0 || p[0x17B] != 0) {
            goto common;
        }
        if (p[0x29] != 0) {
            q = D_800BF808;
            if (q[7] != 0) {
                return 0;
            }
            a[6]++;
            func_80073300(a);
            if (D_1F800137 == 0) {
                D_1F800137 = 2;
            }
            *(s32 *)(q + 0x48) = 1;
            *(s16 *)(a + 0x68) = 1;
        }
        break;
    common:
        c = D_800BF808;
        if (*(s32 *)(c + 0x48) == 0) {
            return 0;
        }
        a[6]++;
        *(s32 *)(c + 0x48) = 0;
        break;
    case 4:
        g = D_800BF808;
        if (g[0x10] == 4) {
            if (g[7] != 0) {
                return 0;
            }
            a[6]++;
            g[0x10] = 0;
        } else {
            if (g[0x10] != 0) {
                return 0;
            }
            a[6]++;
        }
        break;
    case 5:
        if (*(s16 *)(a + 0x68) != 0) {
            if (func_80072F14(a) != 0) {
                a[0] = 1;
                a[6]++;
                *(s16 *)(a + 0x68) = 0;
                a[0x5F] = 1 - a[0x5F];
                *(s16 *)(a + 0x84) -= 0x320;
                *(s16 *)(a + 0x86) -= 0x320;
            }
            break;
        }
        a[0xBF] = 0;
        while (func_80072F14(a) == 0) {
        }
        a[0xBF] = 1;
        a[0] = 1;
        a[6] = 0;
        a[0x5F] = 1 - a[0x5F];
        *(s16 *)(a + 0x84) -= 0x320;
        *(s16 *)(a + 0x86) -= 0x320;
        return 1;
    case 6:
        if (p[0x2A] != a[0x2A]) {
            a[6] = 0;
            return 1;
        }
        break;
    }
    return 0;
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8011DE38);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8011DFA4);

void func_8011E1BC(u8 *a)
{
    u8 *p = D_800E7E80;
    u8 *g;

    switch (a[6]) {
    case 0:
        if (p[0x2A] == a[0x2A] && p[0x181] != 0 && p[0x61] == 0) {
            u8 *h;
            u8 *sp;
            s32 one;
            s32 m;

            a[0] = 2;
            a[6]++;
            func_80054198(p);
            h = D_800BF808;
            sp = &D_1F800137;
            one = 1;
            m = a[0x5F];
            h[0x10] = one;
            h[0x17] = (one - m) * 16;
            h[0xF] = a[3];
            if (*sp == 0) {
                *sp = 2;
            }
        }
        break;
    case 1:
        if (D_800BF816 != 0) {
            a[6]++;
        }
        break;
    case 2:
        g = D_800BF808;
        if (g[0x10] == 2 && g[7] == 0) {
            a[0] = 1;
            a[6]++;
            a[0x5F] = 1 - a[0x5F];
            *(s16 *)(a + 0x84) += 0x320;
            *(s16 *)(a + 0x86) += 0x320;
        }
        break;
    case 3:
        if (a[0x29] != 0 && p[0x17B] == 0 && p[0x181] != 0) {
            u8 *h = D_800BF808;
            if (h[7] == 0) {
                a[0] = 2;
                a[6]++;
                func_80054198(p);
                h[0x10] = 3;
                if (D_1F800137 == 0) {
                    D_1F800137 = 2;
                }
            }
        }
        break;
    case 4:
        g = D_800BF808;
        if (g[0x10] == 4 && g[7] == 0) {
            a[6]++;
            g[0x10] = 0;
        }
        break;
    case 5:
        a[0] = 1;
        a[6]++;
        a[0x5F] = 1 - a[0x5F];
        *(s16 *)(a + 0x84) -= 0x320;
        *(s16 *)(a + 0x86) -= 0x320;
        break;
    case 6:
        if (p[0x2A] != a[0x2A]) {
            a[6] = 0;
        }
        break;
    }
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8011E438);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8011E608);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8011E884);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8011EBA8);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8011ECE4);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8011EE7C);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8011F030);

INCLUDE_ASM("asm/a08/nonmatchings/a08", f_UpdateWaterTempleEntranceAndDoorActor);

void func_8011FC88(u8 *p)
{
    u8 *s = D_800BF808;
    s16 x, z;

    if (s[0xE] && s[0xF] == p[3]) {
        x = *(s16 *)(p + 0x88) + 0x163;
        z = *(s16 *)(p + 0x8C) + 0xB2;
    } else {
        x = *(s16 *)(p + 0x88);
        z = *(s16 *)(p + 0x8C);
    }
    *(s16 *)(p + 0x2E) = x;
    *(s16 *)(p + 0x36) = z;
    func_80073328(p);
}

void func_8011FCF4(u8 *a)
{
    u8 *g = D_800BF808;

    if (g[0xE] != 0 && g[0xF] == a[3]) {
        *(s16 *)(a + 0x2E) = *(s16 *)(a + 0x88) - 0x54;
        *(s16 *)(a + 0x36) = *(s16 *)(a + 0x8C) + 0xAB;
    } else {
        *(s16 *)(a + 0x2E) = *(s16 *)(a + 0x88);
        *(s16 *)(a + 0x36) = *(s16 *)(a + 0x8C);
    }
    func_80073328(a);
    func_800735F4(a, 0x7D);
}

void func_8011FD74(void *arg0) {
    if (M2C_FIELD(arg0, s16 *, 0x66) == 0) {
        func_8011DE38();
        func_8011D798(arg0);
    } else {
        func_8011DAA4(arg0);
    }
    func_800735F4(arg0, 0x7E);
}

extern u8 D_800E7E80[];
extern s8 D_800BF81F;
void func_8011FDD0(u8 *a) {
    u8 *e = D_800E7E80;
    s32 k = a[5];

    switch (k) {
    case 0:
        if (e[0x2A] == a[0x2A] && e[5] == 0) {
            a[5] = 1;
            D_1F800137 = 2;
        }
        break;
    case 1:
        a[5] = 2;
        D_800BF81F = (k - a[0x5F]) * 16;
        a[0x29] = k;
    case 2:
        if (func_80073328(a, e) != 0) {
            a[5]++;
        }
        break;
    case 3:
        if (e[0x2A] != a[0x2A]) {
            a[5] = 0;
        }
        break;
    }
}

extern u8 D_800E7FF4;
void func_8011FECC(s32 arg0) {
    if (D_800E7FF4 & 4) {
        func_80073328();
    }
    func_800735F4(arg0, 0x67);
}

void func_8011FF10(u8 *a)
{
    u8 *g = D_800BF808;

    if (g[0xE] != 0 && g[0xF] == a[3]) {
        *(s16 *)(a + 0x36) = *(s16 *)(a + 0x8C) + 0x100;
    } else {
        *(s16 *)(a + 0x36) = *(s16 *)(a + 0x8C);
    }
    if (D_800E7FF4 & 4) {
        func_80073328(a);
    }
    func_800735F4(a, 0x84);
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8011FF9C);

void func_80122544();
void func_80120068(void *a0)
{
    u8 *r = func_80072DDC(a0, 1, 4, 0x4F);

    if (r) {
        *(void **)(r + 0x1C) = func_80122544;
        r[3] = 2;
    }
}

extern u8 D_801453F8[];
extern u8 D_800BFA32;
/* func_80120068, inlined */
static inline void func_80120068_inl(void *a0)
{
    u8 *r = func_80072DDC(a0, 1, 4, 0x4F);

    if (r) {
        *(void **)(r + 0x1C) = func_80122544;
        r[3] = 2;
    }
}
void func_801200AC(u8 *a)
{
    if (D_800ED098 < 2) {
        a[4] = 3;
        return;
    }
    func_80051B70(a, 0xC, 0x3C);
    func_801268D8(a, D_801453F8, 4, 0xC, 0x3D);
    *(s16 *)(a + 0x54) = 0;
    *(s16 *)(a + 0x56) = 0;
    *(s16 *)(a + 0x58) = 0;
    if (D_800BFA32 & 0x80) {
        a[5] = 0x63;
        a[0] = 2;
        **(u16 **)(a + 0xC0) -= 0x276;
        **(u16 **)(a + 0xC4) += 0x276;
    }
    a[0xD] |= 4;
    (*(u8 **)(a + 0xC0))[0x3F] = 0x28;
    (*(u8 **)(a + 0xC4))[0x3F] = 0x28;
    func_80120068_inl(*(u8 **)(a + 0xC0));
}

void func_801201C4(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 0x5E);
    switch (temp_v1) {                              /* irregular */
    case 0:
        func_8011EE7C(arg0);
        break;
    case 1:
        func_8011F030(arg0);
        break;
    }
    M2C_FIELD(arg0, s8 *, 1) = 1;
    func_80077EBC(arg0);
}

extern PartPose D_80145400[3];
extern PartPose D_80145418[3];
void func_8012022C(PosedActor *a, s32 b, s32 c) {
    s32 i;

    for (i = 0; i < 3; i++) {
        if (b == 0) {
            func_80051B04(a->parts[i], c, i);
            a->parts[i][0] = D_80145400[i].x;
            a->parts[i][1] = D_80145400[i].y;
            a->parts[i][2] = D_80145400[i].z;
        } else {
            func_80051B04(a->parts[i], c, i + 3);
            a->parts[i][0] = D_80145418[i].x;
            a->parts[i][1] = D_80145418[i].y;
            a->parts[i][2] = D_80145418[i].z;
        }
    }
    a->pose = b;
}

extern u8 D_8001B7B0[];
void D_8004C930();
void func_80120338(u8 *a, s32 b) {
    u16 v;
    u8 *p;

    switch (a[5]) {
    case 0:
        if (a[0x29] == 1) {
            a[5]++;
            func_8012022C(a, 0, b);
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

extern u8 D_800ECF58[];
extern u8 D_800BF809;
extern u8 D_80145400_5c5f[];
void func_801205F8(u8 *a)
{
    s32 s = a[4];
    u8 *g;

    switch (s) {
    case 0:
        g = D_800ECF58;
        if (func_800519E0(a, 3, *(s32 *)(g + 0x7C), D_80145400_5c5f) == 0) {
            *(s32 *)(a + 0x3C) = *(s32 *)(g + 0x80);
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
                    func_8012022C(a, 1, 0x1F);
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
            func_80120338(a, 0x1F);
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

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80120848);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80120998);

extern u8 D_8014005C[];
extern u8 D_800BF938;
extern u8 D_800BFA4E;
extern u8 D_800E807E_77d6;
extern u8 *D_800A29B4;
extern u8 D_1F800136;
extern u8 *D_1F800138_5432;
extern u8 D_800BFA4F;
/* func_800737F8, inlined */
static inline void draw_name(u8 *name)
{
    struct { s16 x; s16 y; s16 w; s16 h; } r;
    s32 n = func_80073750(name);
    s32 x;

    if (n < 0) {
        r.h = 0x20;
        n = -n;
    } else {
        r.h = 0x10;
    }
    x = 0xA0 - n * 4;
    r.x = x;
    r.y = 0x50;
    r.w = n * 8;
    func_80079374((s16)x, 0x50, 0, (s32)name, 0);
    func_8005019C(&r, 7, 1, 0);
}
void func_80120BC8(u8 *a)
{
    s16 t;
    u8 *st;
    u8 *p;

    switch (a[4]) {
    case 0:
        switch (a[5]) {
        case 0:
            if (func_80051B70(a, 0xC, 0x29) != 0) {
                break;
            }
            *(s16 *)(a + 0x80) = 0x8C;
            *(s16 *)(a + 0x82) = 0x118;
            *(s16 *)(a + 0x84) = 0xED;
            *(s16 *)(a + 0x86) = 0xED;
            *(s16 *)(a + 0x54) = 0;
            *(s16 *)(a + 0x56) = 0;
            *(s16 *)(a + 0x58) = 0;
            a[0x2B] = 0;
            if (D_800BF938 == 0xFF) {
                a[4] = 1;
                a[0] = 1;
                break;
            }
            a[5]++;
            *(s16 *)(a + 0x8A) = *(s16 *)(a + 0x32);
            *(s16 *)(a + 0x32) -= 0x200;
            break;
        case 1:
            if (D_800BFA4E >= 0xF) {
                a[5] = 2;
                *(s16 *)(a + 0x4A) = 0;
                *(s16 *)(a + 0x50) = 0x200;
            }
            break;
        case 2:
            *(s16 *)(a + 0x4A) += *(s16 *)(a + 0x50);
            if (*(s16 *)(a + 0x4A) > 0x2000) {
                *(s16 *)(a + 0x4A) = 0x2000;
            }
            *(s32 *)(a + 0x30) += *(s16 *)(a + 0x4A) << 8;
            if (*(s16 *)(a + 0x32) >= *(s16 *)(a + 0x8A)) {
                *(s16 *)(a + 0x32) = *(s16 *)(a + 0x8A);
                p = func_8003116C(0, a + 0x2C, -0x32);
                p[0x28] |= 0x80;
                func_80074590(0x32, -0xE, 0);
                *(s16 *)(a + 0x40) = 0xF;
                a[5]++;
                D_800E807E_77d6 = 1;
            }
            func_800517F8(a);
            a[1] = 1;
            func_80077EBC(a);
            break;
        case 3:
            if (--*(s16 *)(a + 0x40) == -1) {
                a[4] = 1;
                a[5] = 0;
                a[0] = 1;
                D_800BFA4E = 0x14;
                D_800E807E_77d6 = 0;
            }
            func_800517F8(a);
            a[1] = 1;
            func_80077EBC(a);
            break;
        }
        break;
    case 1:
        switch (a[5]) {
        case 5:
            a[0] = 1;
            a[5] = 0;
        case 0:
            if (a[0x2B] == 3) {
                a[5]++;
                st = (u8 *)&D_800BF870;
                if (st[0x1DE] < 0x28) {
                    st[0x1DE] = 0x28;
                }
            }
            break;
        case 1:
            draw_name(D_800A29B4);
            if (D_800E7E68 & 0x2000) {
                a[5]++;
                func_80074590(0x11, 0, 0);
            }
            break;
        case 2:
            func_80120848();
            if (D_800E7E68 & 0x4000) {
                a[5]++;
                D_1F800136 = 2;
                D_1F800138_5432[0x6B] = 10;
                *(s16 *)(D_1F800138_5432 + 0x50) = 0;
                D_800BFA4F = 0;
            } else if (D_800E7E68 & 0x2000) {
                a[5] += 2;
                func_80074BF8(1);
            }
            break;
        case 3:
            if (func_80120998(a) != 0) {
                a[5]++;
            }
            break;
        case 4:
            a[0] = 2;
            a[5]++;
            break;
        }
        a[0x2B] = 0;
        func_800517F8(a);
        a[1] = 1;
        func_80077EBC(a);
        break;
    case 2:
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80121040);

s32 func_80121110(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x452) == 0xFF) {
        D_800BF870.pad1[0x3B] = 1;
        D_800BF870.pad1[0x1DE] |= 1;
    }
    if (M2C_FIELD(arg0, u8 *, 0x4FA) == 0xFF) {
        D_800BF870.pad1[0x3C] = 1;
        D_800BF870.pad1[0x1DE] |= 2;
    }
    if (M2C_FIELD(arg0, u8 *, 0x449) == 0xFF) {
        D_800BF870.pad1[0x3D] = 1;
        D_800BF870.pad1[0x1DE] |= 4;
    }
    if (M2C_FIELD(arg0, u8 *, 0x44E) == 0xFF) {
        D_800BF870.pad1[0x3E] = 1;
        D_800BF870.pad1[0x1DE] |= 8;
    }
    return 1;
}

void func_801211BC(u8 *p, u8 *a, u8 *b)
{
    u8 n, m;
    s32 i;

    m = n = 0;
    for (i = 0; i < 0x100; i++) {
        u8 v = (p + i)[0x444];
        if (v != 0) {
            n++;
            if (v == 0xFF) {
                m++;
            }
        }
    }
    *a = n;
    *b = m;
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80121208);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_801214FC);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80121AD8);

extern u8 D_800BF928;
extern s32 D_800BF850;
extern u8 D_8014549C[];
u8 *func_80072DDC();
void func_8013DDD4();
static inline s32 wt_step0(u8 *a)
{
    u8 *e;

    switch (a[6]) {
    case 0:
        if (a[0x29] != 0) {
            e = D_800E7E80;
            a[6] = 1;
            func_80054198(e);
            *(s16 *)(e + 0x2E) = *(s16 *)(a + 0x2E);
            *(s16 *)(e + 0x36) = *(s16 *)(a + 0x36);
            D_800BF850 = 1;
            func_80042354(1, 2);
        }
        break;
    case 1:
        a[6] = 2;
        func_80040CDC(a, 0, D_8014549C);
        a[0x70] = 1;
        break;
    case 2:
        func_80041098(a);
        if (a[0x70] == 0xFF) {
            a[6] = 0;
            func_80042310();
            return 1;
        }
        break;
    }
    return 0;
}
static inline s32 wt_lower(u8 *a)
{
    if (*(s16 *)(a + 0x42) != 0) {
        *(s16 *)(a + 0x42) -= 1;
    } else {
        *(s16 *)(a + 0x32) -= 8;
        if (*(s16 *)(a + 0x32) < -0xF5F) {
            *(s16 *)(a + 0x32) = -0xF60;
            return 1;
        }
    }
    return 0;
}
void func_80121C2C(u8 *a)
{
    u8 *p;
    u8 *st;
    u8 *st2;

    switch (a[4]) {
    case 0:
        if (func_80051B70(a, 0xC, 0x3B) != 0) {
            break;
        }
        *(s16 *)(a + 0x80) = 0x5D;
        *(s16 *)(a + 0x82) = 0xBA;
        a[0] = 1;
        *(s16 *)(a + 0x84) = 0;
        *(s16 *)(a + 0x86) = 0x40;
        a[0x29] = 0;
        *(s16 *)(a + 0x42) = 0;
        a[4]++;
        p = func_80072DDC(0, 1, 2, 0xCE);
        if (p != NULL) {
            *(void **)(p + 0x1C) = func_8013DDD4;
            *(s16 *)(p + 0x2E) = 0x445C;
            *(s16 *)(p + 0x32) = -0x1529;
            *(s16 *)(p + 0x36) = 0x1040;
        }
        if (D_800BF928 == 0xFF) {
            a[5] = 3;
            *(s16 *)(a + 0x32) = -0xEC0;
            D_800BF850 = 1;
            p = func_80072DDC(0, 1, 3, 0x10);
            if (p != NULL) {
                *(void **)(p + 0x1C) = f_UpdateWaterTempleQuestPropActor;
                p[3] = 0x11;
            }
        } else if (D_800BF928 != 0) {
            *(s16 *)(a + 0x32) = -0xF60;
            a[5] = 1;
        } else {
            *(s16 *)(a + 0x32) = -0xF60;
            a[5] = 0;
        }
        break;
    case 1:
        st = D_800BF808;
        if (st[2] != 0 && st[3] != 0x88) {
            func_8007778C(a);
            func_800517F8(a);
            break;
        }
        switch (a[5]) {
        case 0:
            if (wt_step0(a)) {
                a[5]++;
            }
            break;
        case 1:
            a[0x5E] = 0;
            if (a[0x29] != 0) {
                *(s16 *)(a + 0x42) = 0x1E;
                if (*(s16 *)(a + 0x32) == -0xEC0) {
                    a[0x5E] = 1;
                } else {
                    *(s16 *)(a + 0x32) += 8;
                    if (*(s16 *)(a + 0x32) >= -0xEC0) {
                        *(s16 *)(a + 0x32) = -0xEC0;
                        a[0x5E] = 1;
                        func_80074590(0x1A, -8, 0);
                    }
                }
                st2 = D_800BF808;
                *(s32 *)(st2 + 0x48) = 1;
                if (st2[2] != 0 && st2[3] == 0x88) {
                    func_80042354(1, 2);
                    a[5]++;
                    p = func_80072DDC(0, 1, 3, 0x10);
                    if (p != NULL) {
                        *(void **)(p + 0x1C) = f_UpdateWaterTempleQuestPropActor;
                        p[3] = 0x11;
                    }
                }
            } else if (wt_lower(a)) {
                D_800BF850 = 0;
            }
            break;
        case 2:
            if (func_80121AD8(a)) {
                a[5]++;
            }
            break;
        }
        if (func_8007778C(a) != 0) {
            func_800517F8(a);
        }
        a[0x29] = 0;
        break;
    case 2:
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

void func_8013DDD4();
void func_80122064(void)
{
    u8 *r = func_80072DDC(0, 1, 2, 0xCE);

    if (r) {
        *(void **)(r + 0x1C) = func_8013DDD4;
        *(s16 *)(r + 0x2E) = 0x445C;
        *(s16 *)(r + 0x32) = -0x1529;
        *(s16 *)(r + 0x36) = 0x1040;
    }
}

void f_UpdateWaterTempleQuestPropActor();
extern s16 D_801459AC[];
extern u8 *D_800BF844;
void func_801220BC(void)
{
    u8 *r = func_80072DDC(0, 1, 3, 0x10);

    if (r) {
        *(void **)(r + 0x1C) = f_UpdateWaterTempleQuestPropActor;
        r[3] = 0x11;
    }
}

s32 func_80122104(u8 *p)
{
    *(s16 *)(p + 0x42) = 0x1E;
    if (*(s16 *)(p + 0x32) == -0xEC0) {
        p[0x5E] = 1;
    } else {
        *(s16 *)(p + 0x32) += 8;
        if (*(s16 *)(p + 0x32) < -0xEC0) {
            return 0;
        }
        *(s16 *)(p + 0x32) = -0xEC0;
        p[0x5E] = 1;
        func_80074590(0x1A, -8, 0);
    }
    return 1;
}

s32 func_8012217C(u8 *p)
{
    s32 s = p[6];
    u8 *g;

    switch (s) {
    case 0:
        if (p[0x29] == 0) {
            break;
        }
        p[6] = 1;
        g = D_800E7E80;
        func_80054198(g);
        *(s16 *)(g + 0x2E) = *(u16 *)(p + 0x2E);
        *(s16 *)(g + 0x36) = *(u16 *)(p + 0x36);
        D_800BF850 = 1;
        func_80042354(1, 2);
        return 0;
    case 1:
        p[6] = 2;
        func_80040CDC(p, 0, D_8014549C);
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

extern u8 D_800BFAE9;
extern void func_80042354(s32, s32);
extern void func_80054D14(u8 *, s32, s32);
extern void func_80040B48(s32);
void func_801294B4(s16 a0);
extern void func_8004D604(s32, s32);
extern void func_8004ED94(s32, s32);
extern void func_80051B04(void *, s32, s32);
extern void func_80042310();
s32 f_InsertPigNosePanelIntoTempleTower(u8 *a)
{
    u8 *e = D_800E7E80;
    u8 *g;

    switch (a[6]) {
    case 99:
        a[6] = 0;
        a[0] = 1;
    case 0:
        if (a[0x2B] != 3) {
            return 0;
        }
        if (D_800BFAE9 != 0) {
            H(a, 0x40) = 0x2D;
            a[6]++;
            func_80042354(1, 2);
            e[4] = 4;
            e[5] = 0x21;
            e[6] = 0;
            e[0x61] = 0;
            func_80054D14(e, 0x72, 0);
            func_80040B48(0x3B);
            func_801294B4(a[3]);
            func_8004D604(0x35, 1);
            return 0;
        }
        H(a, 0x40) = 0x1E;
        func_8004ED94(0x72, 0x41);
        a[6] = 4;
        break;
    case 1:
        if (--H(a, 0x40) == -1) {
            H(a, 0x40) = 0x1E;
            a[6]++;
            func_80054D14(e, 0x73, 0);
        }
        break;
    case 2:
        if (--H(a, 0x40) == -1) {
            a[6]++;
            if (a[3] == 2) {
                func_80051B04(*(void **)(a + 0xC0), 0xC, 0x40);
            } else {
                func_80051B04(*(void **)(a + 0xC0), 0xC, 0x3F);
            }
            D_800BF870.pad1[0x1C1] |= 1 << a[3];
            func_80074590(0x1A, 0xA, 0, &D_800BF870);
        }
        break;
    case 3:
        {
            u32 v = D_800BF870.pad1[0x1C1];
            if ((v & 0x1F) == 0x1F) {
                D_800BF870.pad1[0x1C1] = v | 0x80;
                a[6] = 0;
                return 1;
            }
            a[6] = 0;
            a[0] = 2;
            func_80042310(v, &D_800BF870);
        }
        return 1;
    case 4:
        if (--H(a, 0x40) == 0) {
            if (a[3] != 2) {
                a[0] = 2;
                a[6] = 99;
            } else {
                a[6]++;
            }
        }
        break;
    case 5:
        if (a[0x2B] == 0) {
            a[0] = 2;
            a[6] = 99;
        }
        break;
    }
    return 0;
}

extern u16 D_800BF89E;
void func_80122544(u8 *a)
{
    u8 *p;
    u8 *t;

    switch (a[4]) {
    case 0:
        if (a[3] == 2) {
            if (func_80051B70(a, 0xC, 0x40) != 0) {
                break;
            }
            *(s16 *)(a + 0x54) = 0;
            *(s16 *)(a + 0x56) = 0;
            *(s16 *)(a + 0x58) = 0;
            if (!((D_800BFA32 >> a[3]) & 1)) {
                *(s32 *)(*(u8 **)(a + 0xC0) + 0x40) = 0;
                *(s16 *)(a + 0x80) = 0x50;
                *(s16 *)(a + 0x82) = 0xA0;
                a[0] = 1;
                *(s16 *)(a + 0x84) = 0x68;
                *(s16 *)(a + 0x86) = 0x68;
            }
            a[0xD] |= 4;
            (*(u8 **)(a + 0xC0))[0x3F] = 0x10;
        } else if (!((D_800BFA32 >> a[3]) & 1)) {
            if (func_80051B70(a, 0xC, 0x3E) != 0) {
                break;
            }
            *(s16 *)(a + 0x80) = 0xC8;
            *(s16 *)(a + 0x82) = 0x190;
            a[0] = 1;
            *(s16 *)(a + 0x84) = 0x100;
            *(s16 *)(a + 0x86) = 0x100;
            a[5] = 0;
        } else {
            if (func_80051B70(a, 0xC, 0x3F) != 0) {
                break;
            }
            a[5] = 1;
        }
        a[0x29] = 0;
        a[0x2B] = 0;
        a[4]++;
        break;
    case 1:
        if (a[3] == 2) {
            p = *(u8 **)(a + 0x10);
            *(s16 *)(a + 0x2E) = *(s16 *)(p + 0x2C);
            *(s16 *)(a + 0x32) = *(s16 *)(p + 0x30) - 0x6B;
            *(s16 *)(a + 0x36) = *(s16 *)(p + 0x34);
            if (a[0x29] != 0) {
                t = D_800E7E80;
                if (t[0x29] != 0 && !(t[0x174] & 4) && !(D_800BF89E & 0x200) && func_8005308C() != 0) {
                    a[0x2B] = 3;
                    t[0x147] = func_80077768((s16)func_800782B0(t + 0x2C, *(s16 *)(a + 0x2E), *(s16 *)(a + 0x36)), *(s16 *)(t + 0x140), 0);
                    func_80055284(t);
                }
            }
        }
        if (a[5] == 0 && f_InsertPigNosePanelIntoTempleTower(a) != 0) {
            a[5]++;
        }
        if (D_1F800207 == 6 || D_1F800207 == 0xF) {
            a[1] = 1;
            func_80077EBC(a);
        } else {
            func_8007778C(a);
        }
        if (a[1] != 0) {
            func_800517F8(a);
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

extern u8 D_800BFA3F;
/* func_80122938, inlined */
static inline void func_80122938_inl(void *arg0) {
    M2C_FIELD(arg0, s8 *, 1) = 1;
    func_80077EBC(arg0);
    if (D_800BFA3F & 0x20) {
        func_80027144(M2C_FIELD(M2C_FIELD(arg0, void **, 0xC0), s32 *, 0x40), arg0 + 0x2C, 0x800, 8);
        M2C_FIELD(arg0, s8 *, 4) = 3;
    }
}
void func_8012282C(u8 *a)
{
    switch (a[4]) {
    case 0:
        *(s16 *)(a + 0x80) = 0xA0;
        *(s16 *)(a + 0x82) = 0x140;
        *(s16 *)(a + 0x84) = 0x20;
        a[0] = 1;
        *(s16 *)(a + 0x86) = 0x40;
        func_80051B70(a, 0xC, 0x24);
        *(s16 *)(a + 0x58) = 0;
        *(s16 *)(a + 0x54) = 0;
        *(s16 *)(a + 0x56) = 0x11E;
        a[4]++;
        break;
    case 1:
        func_80122938_inl(a);
        func_800517F8(a);
        break;
    case 2:
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

void func_80122938(void *arg0) {
    M2C_FIELD(arg0, s8 *, 1) = 1;
    func_80077EBC();
    if (D_800BFA3F & 0x20) {
        func_80027144(M2C_FIELD(M2C_FIELD(arg0, void **, 0xC0), s32 *, 0x40), arg0 + 0x2C, 0x800, 8);
        M2C_FIELD(arg0, s8 *, 4) = 3;
    }
}

extern u8 D_800BFA42;
void func_80122998(u8 *a)
{
    u8 *p = *(u8 **)(a + 0x10);

    switch (a[4]) {
    case 0:
        if (a[3] < 3) {
            func_80051B70(a, 0xC, 0x12);
        } else {
            func_80051B70(a, 0xC, 0x5D);
        }
        *(s16 *)(a + 0x80) = 0x53;
        *(s16 *)(a + 0x82) = 0xA6;
        *(s16 *)(a + 0x54) = 0;
        *(s16 *)(a + 0x56) = 0;
        *(s16 *)(a + 0x58) = 0;
        *(s16 *)(a + 0x84) = 0;
        *(s16 *)(a + 0x86) = 0x3F;
        a[4]++;
        break;
    case 1:
        if (a[3] < 3) {
            *(s16 *)(a + 0x2E) = *(s16 *)(p + 0x2E);
            *(s16 *)(a + 0x32) = *(s16 *)(p + 0x32) - *(s16 *)(p + 0x84);
            *(s16 *)(a + 0x36) = *(s16 *)(p + 0x36);
            if ((a[3] + 1) * 2 == D_800BFA42) {
                a[4] = 2;
                *(s16 *)(a + 0x4A) = 0;
            }
        } else {
            *(s16 *)(a + 0x2E) = *(s16 *)(p + 0x2E);
            *(s16 *)(a + 0x32) = *(s16 *)(p + 0x32) - *(s16 *)(p + 0x84);
            *(s16 *)(a + 0x36) = *(s16 *)(p + 0x36);
        }
        *(s16 *)(*(u8 **)(a + 0xC0) + 0xC) = func_80083E80(((a[3] << 3) + D_1F80017C_0fe7) << 7) >> 7;
        if (p[1] != 0) {
            a[1] = 1;
            func_80077EBC(a);
            func_800517F8(a);
        }
        break;
    case 2:
        switch (a[5]) {
        case 0:
            *(s16 *)(a + 0x4A) += 0x300;
            if (*(s16 *)(a + 0x4A) > 0x3E00) {
                *(s16 *)(a + 0x4A) = 0x3E00;
            }
            *(s32 *)(a + 0x30) += *(s16 *)(a + 0x4A) << 8;
            if (*(s16 *)(a + 0x32) >= -0x137D) {
                *(s16 *)(a + 0x4A) = 0;
                a[5]++;
                *(s16 *)(a + 0x40) = 0x14;
                D_1F8001A4_f18c = -0x137E;
                func_8011370C(a);
            }
            break;
        case 1:
            *(s16 *)(a + 0x4A) += 0x200;
            if (*(s16 *)(a + 0x4A) > 0x3E00) {
                *(s16 *)(a + 0x4A) = 0x3E00;
            }
            *(s32 *)(a + 0x30) += *(s16 *)(a + 0x4A) << 8;
            if (--*(s16 *)(a + 0x40) == 0) {
                a[4] = 3;
            }
            break;
        }
        if (func_8007778C(a) != 0) {
            func_800517F8(a);
        }
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

void func_80122998();
void func_80122C70(u8 *a0)
{
    u8 *r = func_80072DDC(a0, 1, 4, 0x53);

    if (r) {
        *(void **)(r + 0x1C) = func_80122998;
        r[3] = a0[3];
    }
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80122CC0);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80123028);

INCLUDE_ASM("asm/a08/nonmatchings/a08", f_UpdateWaterTempleMechanismActor);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_801237A0);

s32 func_8012388C(void *arg0) {
    M2C_FIELD(arg0, u8 *, 0x47) = (u8) M2C_FIELD(arg0, u8 *, 0x72);
    return 1;
}

s32 func_801238A0(void *arg0) {
    u16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, u16 *, 0xBA) - 0x60;
    M2C_FIELD(arg0, u16 *, 0xBA) = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        M2C_FIELD(arg0, u16 *, 0xBA) = 0U;
        return 1;
    }
    return 0;
}

void f_UpdateWaterTempleMechanismActor();
u8 *func_801238D0(void *a0, u8 a1)
{
    u8 *r = func_8007A980(1, 4, 0);

    if (r == 0) {
        return 0;
    }
    r[2] = 0x54;
    r[3] = a1;
    *(void **)(r + 0x1C) = f_UpdateWaterTempleMechanismActor;
    *(void **)(r + 0x10) = a0;
    r[0x28] |= 0x80;
    return r;
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80123940);

typedef struct { s16 x, y, z, pad; } SVec3;
extern SVec3 D_1F8000C0;
extern s32 D_800E7F5C;
void func_80123A48(u8 *a)
{
    u8 *t;
    SVec3 *v;
    a[1] = 1;
    func_80077EBC(a);
    switch (a[5]) {
    case 0:
        t = D_800E7E80;
        func_8004BD64(a, 0, *(s32 *)(t + 0xDC), *(s32 *)(t + 0xD0), 0);
        break;
    case 1:
        D_1F8000C0.x = 0;
        v = &D_1F8000C0;
        v->y = 0;
        v->z = 0;
        func_8004BD64(a, 1, D_800E7F5C, 0, v);
        break;
    case 2:
        break;
    }
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80123AE4);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80123BF0);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80123D10);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80123E60);

extern u8 D_1F80027A;
void func_80124074(u8 *a)
{
    s32 s = a[4];
    switch (s) {
    case 0:
        func_80123BF0(a);
        break;
    case 1:
        a[1] = s;
        func_80077EBC(a);
        if (D_1F80027A == 0) {
            func_80123E60(a);
            func_800517F8(a);
            a[0x29] = 0;
        }
        break;
    case 2:
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

s32 func_80124128(void *arg0) {
    s16 temp_v0;
    s16 temp_v0_2;
    s32 var_v0;
    void *temp_a0;
    void *temp_a0_2;

    if (M2C_FIELD(arg0, u8 *, 0x29) != 0) {
        temp_a0 = M2C_FIELD(arg0, void **, 0xC8);
        if (M2C_FIELD(temp_a0, s16 *, 2) < -0x1C0) {
            temp_v0 = (u16) M2C_FIELD(temp_a0, s16 *, 2) + 8;
            M2C_FIELD(temp_a0, s16 *, 2) = temp_v0;
            var_v0 = 1;
            if (temp_v0 >= -0x1C0) {
                func_80074590(0x1A, 0xA, 0);
                M2C_FIELD(M2C_FIELD(arg0, void **, 0xC8), s16 *, 2) = -0x1C0;
                goto block_5;
            }
            /* Duplicate return node #10. Try simplifying control flow for better match */
            return var_v0;
        }
        M2C_FIELD(arg0, s16 *, 0x40) = 0xF;
block_5:
        return 1;
    }
    temp_a0_2 = M2C_FIELD(arg0, void **, 0xC8);
    var_v0 = 0;
    if (M2C_FIELD(temp_a0_2, s16 *, 2) >= -0x1FF) {
        temp_v0_2 = (u16) M2C_FIELD(temp_a0_2, s16 *, 2) - 8;
        M2C_FIELD(temp_a0_2, s16 *, 2) = temp_v0_2;
        if (temp_v0_2 < -0x1FF) {
            func_80074590(0x1A, 0x10, -0x1E);
            M2C_FIELD(M2C_FIELD(arg0, void **, 0xC8), s16 *, 2) = -0x200;
        }
        var_v0 = 0;
    }
    return var_v0;
}

extern u8 D_800BF841;
extern u8 D_1F8000DC[];
extern u8 D_800E8008[];
extern u8 D_80145668[];
extern u16 D_800E7FC0;
static inline void cam_setup(void)
{
    u8 *e = D_800E8008;

    e[0x64] = 1;
    *(s16 *)(e + 0x6E) = 0x130;
    *(s16 *)(e + 0x6C) = 0x480;
    e[0x66] = 0;
    *(s32 *)(e + 0x38) = D_1F800160 << 16;
    *(s32 *)(e + 0x3C) = (D_1F800162 - 0x8C) << 16;
    *(s32 *)(e + 0x40) = D_1F800164 << 16;
    *(s16 *)(e + 0x70) = D_800E7FC0 + *(u16 *)(e + 0x52) + 0x180;
}
void func_80124210(u8 *a)
{
    s32 dx;
    s32 dz;

    switch (a[4]) {
    case 0:
        func_80051B70(a, 0xC, 0x44);
        *(s16 *)(a + 0x58) = 0;
        *(s16 *)(a + 0x56) = 0;
        *(s16 *)(a + 0x54) = 0;
        a[0x2B] = 0;
        if (!(D_800BFA42 & 0x80)) {
            *(s16 *)(a + 0x80) = 0x40;
            *(s16 *)(a + 0x82) = 0x80;
            *(s16 *)(a + 0x84) = 0x80;
            a[0] = 1;
            *(s16 *)(a + 0x86) = 0x100;
            a[4]++;
        } else {
            *(s16 *)(a + 0x56) = 0xC00;
            a[6] = 10;
            a[4] = 2;
        }
        break;
    case 1:
        if (func_8007778C(a) != 0) {
            func_800517F8(a);
        }
        if (a[0x2B] != 0) {
            a[4] = 2;
            a[5] = 0;
            a[6] = 0;
        }
        if (a[1] != 0) {
            dx = D_1F800160 - *(s16 *)(a + 0x2E);
            dz = D_1F800164 - *(s16 *)(a + 0x36);
            if (func_80084080(dx * dx + dz * dz) < 0x44D) {
                a[0] = 1;
                break;
            }
        }
        a[0] = 3;
        break;
    case 2:
        if (func_8007778C(a) != 0) {
            func_800517F8(a);
        }
        switch (a[6]) {
        case 0:
            D_800BF841 = 1;
            func_80042354(1, 1);
            a[0] = 2;
            *(s16 *)(a + 0x56) = 0x1000;
            a[6]++;
            break;
        case 1:
            *(s16 *)(a + 0x56) -= 0xA0;
            if (*(s16 *)(a + 0x56) < 0xC00) {
                func_80074590(0x2F, -0xC, 0);
                *(s16 *)(a + 0x56) = 0xC00;
                func_8006E1C0(7);
                func_8006CBA8(D_1F8000DC);
                func_8006CC1C(D_800E8008, D_80145668, 0x30);
                a[6]++;
            }
            break;
        case 2:
            if (func_8006CDCC(D_800E8008) == 1) {
                D_800BFA42 = 2;
                a[6]++;
            }
            break;
        case 3:
            if (D_800BFA42 == 0x82) {
                *(s16 *)(a + 0x40) = 0;
                a[6]++;
            }
            break;
        case 4:
            if (++*(s16 *)(a + 0x40) >= 0x1E) {
                cam_setup();
                a[6]++;
            }
            break;
        case 5:
            if (D_800BFA42 == 0x85) {
                cam_setup();
                a[6] = 10;
            }
            break;
        }
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

void func_80124600(u8 *a)
{
    func_80051B70(a, 0xC, 0x44);
    *(s16 *)(a + 0x58) = 0;
    *(s16 *)(a + 0x56) = 0;
    *(s16 *)(a + 0x54) = 0;
    a[0x2B] = 0;
    if (!(D_800BFA42 & 0x80)) {
        a[0] = 1;
        *(s16 *)(a + 0x80) = 0x40;
        *(s16 *)(a + 0x82) = 0x80;
        *(s16 *)(a + 0x84) = 0x80;
        *(s16 *)(a + 0x86) = 0x100;
        a[4]++;
    } else {
        *(s16 *)(a + 0x56) = 0xC00;
        a[6] = 0xA;
        a[4] = 2;
    }
}

extern u8 D_800BF8E2;
void func_80137C5C();
s32 func_80124698(u8 *p)
{
    s32 dx = D_1F800160 - *(s16 *)(p + 0x2E);
    s32 dz = D_1F800164 - *(s16 *)(p + 0x36);

    return func_80084080(dx * dx + dz * dz);
}

void func_801246F0(u8 *a) {
    switch (a[4]) {
    case 0:
        func_80051B70(a, 0xC, 0x68);
        M2C_FIELD(a, s16 *, 0x80) = 0x40;
        M2C_FIELD(a, s16 *, 0x82) = 0x80;
        M2C_FIELD(a, s16 *, 0x86) = 0x40;
        a[0] = 1;
        M2C_FIELD(a, s16 *, 0x84) = 0;
        M2C_FIELD(a, s16 *, 0xBA) = 0x800;
        a[4]++;
        break;
    case 1:
        if (func_8013900C(a)) {
            func_80051844(a);
        }
        break;
    case 2:
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

void func_801246F0();
s32 func_801247C4(u8 *a)
{
    u8 *p = func_80072DDC(a, 1, 4, 0x58);

    if (p != NULL) {
        *(void **)(p + 0x1C) = func_801246F0;
        p[3] = a[3];
        p[0x2A] = a[0x2A];
        *(s16 *)(p + 0x2E) = *(s16 *)(a + 0x7C);
        *(s16 *)(p + 0x32) = *(s16 *)(a + 0x32);
        *(s16 *)(p + 0x36) = *(s16 *)(a + 0x7E);
        *(s16 *)(p + 0x56) = *(s16 *)(a + 0x60);
        *(s16 *)(p + 0x54) = 0;
        *(s16 *)(p + 0x58) = 0;
        return 1;
    }
    return 0;
}

extern u8 D_800BF8F8;
void func_8012485C(u8 *a)
{
    u8 *e;

    switch (a[4]) {
    case 0:
        func_80051B70(a, 0xC, 0x23);
        *(s16 *)(a + 0x2E) = 0x2D04;
        *(s16 *)(a + 0x32) = -0xF90;
        *(s16 *)(a + 0x36) = 0x19EE;
        *(s16 *)(a + 0x56) = -0x2D8;
        *(s16 *)(a + 0x80) = 0x3AC;
        *(s16 *)(a + 0x82) = 0x758;
        *(s16 *)(a + 0x84) = 0x80;
        *(s16 *)(a + 0x86) = 0x100;
        *(s16 *)(a + 0x58) = 0;
        a[0x2B] = 0;
        a[4]++;
        if (D_800BF8F8 == 0xFF) {
            a[5] = 2;
            *(s16 *)(a + 0x54) = -0x400;
        } else {
            a[0] = 1;
            *(s16 *)(a + 0x54) = 0;
        }
        break;
    case 1:
        if (D_800BF816 == 0) {
            a[4] = 3;
            break;
        }
        switch (a[5]) {
        case 2:
            break;
        case 0:
            if (a[0x2B] == 3) {
                e = D_800E7E80;
                e[4] = 4;
                e[5] = 0x21;
                e[6] = 0;
                e[0x61] = 0;
                func_80042354(1, 2);
                a[0x5E] = 1;
                a[5]++;
            }
            break;
        case 1:
            if (a[0x5E] == 0) {
                if (D_800BF8F8 == 0xFF) {
                    a[0] = 2;
                    a[5] = 2;
                } else {
                    a[5] = 0;
                }
            }
            break;
        }
        a[1] = 1;
        func_80077EBC(a);
        func_80051C8C(a);
        a[0x2B] = 0;
        break;
    case 2:
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

u8 *func_80124A48(void *a0)
{
    u8 *r = func_80072DDC(a0, 1, 4, 0x59);

    if (r) {
        *(void **)(r + 0x1C) = func_8012485C;
        r[0x5E] = 0;
        r[0x28] |= 0x80;
    }
    return r;
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80124A94);

typedef union {
    u8 b[0xC0];
    s16 h[0x60];
} ActorH;
extern s16 D_1F8001A0_b0de;
extern s16 D_1F8001A2;
typedef struct {
    u8 b[0x56];
    s16 h56;
    u8 pad58[8];
    s16 h60;
    s16 h62;
    u8 pad64[0x5C];
    u8 *parts[3];
} DoorActor;
typedef struct {
    s16 x, y, z, pad;
} SVec4;
typedef struct {
    u8 pad0[6];
    u8 count;
    u8 pad7[5];
    u32 *tbl;
    u16 list[1];
} PartList;
s32 func_80124C14(DoorActor *a, s16 *d) {
    s32 i;
    s32 n;
    s16 x, y;

    a->b[8] = 3;
    if (D_800ED098 < 3) {
        return 1;
    }
    n = 3;
    a->b[9] = n;
    a->b[0xD] = 4;
    M2C_FIELD(a->b, s16 *, 0x80) = 0x80;
    M2C_FIELD(a->b, s16 *, 0x82) = 0x100;
    M2C_FIELD(a->b, s16 *, 0x84) = 0xDC;
    M2C_FIELD(a->b, s16 *, 0x86) = 0x1C2;
    a->b[0xB] = 0;
    M2C_FIELD(a->b, s16 *, 0xB8) = 0x1000;
    M2C_FIELD(a->b, s16 *, 0xBA) = 0x1000;
    M2C_FIELD(a->b, s16 *, 0xBC) = 0x1000;
    for (i = 0; i < a->b[8]; i++) {
        a->parts[i] = func_8007AAE8();
        M2C_FIELD(a->parts[i], s16 *, 6) = *d++;
        M2C_FIELD(a->parts[i], s16 *, 0) = *d++;
        M2C_FIELD(a->parts[i], s16 *, 2) = *d++;
        M2C_FIELD(a->parts[i], s16 *, 4) = *d++;
        M2C_FIELD(a->parts[i], s16 *, 8) = 0;
        M2C_FIELD(a->parts[i], s16 *, 0xA) = 0;
        M2C_FIELD(a->parts[i], s16 *, 0xC) = 0;
        M2C_FIELD(a->parts[i], s16 *, 0x38) = 0x1000;
        M2C_FIELD(a->parts[i], s16 *, 0x3A) = 0x1000;
        M2C_FIELD(a->parts[i], s16 *, 0x3C) = 0x1000;
        func_80051B04(a->parts[i], 0xC, *d++);
    }
    a->parts[0][0x3F] = 0x20;
    a->parts[1][0x3F] = 0xF0;
    a->parts[2][0x3F] = 0xF0;
    a->b[0x29] = 0;
    a->b[0x2B] = 0;
    func_8004766C(a->b);
    func_80048750(a->b);
    x = D_1F8001A0_b0de;
    y = D_1F8001A2;
    a->h60 = x;
    a->h62 = y;
    a->h56 = x;
    M2C_FIELD(a->parts[0], s16 *, 0xA) = M2C_FIELD(a->b, s16 *, 0x7C);
    return 0;
}

void func_80124DEC(u8 *a, s32 b) {
    s32 i;
    s32 found;

    for (i = 0; i < D_800BF870.pad1[0x12]; i++) {
        if ((D_800BF870.pad1[0x13 + i] & 0x7F) == M2C_FIELD(a, s16 *, 0x7E)) {
            found = 1;
            goto done;
        }
    }
    found = 0;
done:
    if (found == 0) {
        goto dead;
    }
    if ((D_800BF870.pad1[0x1A8] >> a[3]) & 1) {
        a[4] = 3;
        return;
    }
    if (func_80124C14(a, b) != 0) {
    dead:
        a[4] = 3;
        return;
    }
    if (D_800BF870.pad1[0] == M2C_FIELD(a, s16 *, 0x7A)) {
        M2C_FIELD(M2C_FIELD(a, u8 **, 0xC4), s16 *, 0xA) = 0x800;
        M2C_FIELD(M2C_FIELD(a, u8 **, 0xC8), s16 *, 0xA) = 0x800;
        a[4] = 1;
        a[5] = 0;
        a[0x5E] = 2;
    } else if ((D_800BF870.pad1[0x1A6] >> a[3]) & 1) {
        M2C_FIELD(M2C_FIELD(a, u8 **, 0xC4), s16 *, 0xA) = 0x800;
        M2C_FIELD(M2C_FIELD(a, u8 **, 0xC8), s16 *, 0xA) = 0x800;
        a[0] = 1;
        a[4] = 1;
        a[5] = 0;
        a[0x5E] = 1;
    } else {
        a[5]++;
    }
}

#define FU16(p, o) M2C_FIELD(p, u16 *, o)
#define FU16(p, o) M2C_FIELD(p, u16 *, o)
extern u8 D_800E806E;
extern u16 D_1F8000D6;
void func_80124F48(u8 *a) {
    u8 *t;

    switch (a[5]) {
    case 0:
        D_1F800137 = 2;
        D_800BF841 = 1;
        func_8006E1C0(8);
        func_8006CBA8(a + 0x2C);
        D_1F8000D6 = FU16(a, 0x32);
        a[5]++;
        break;
    case 1:
        if ((D_800E806E & 3) == 3) {
            t = D_800E7E80;
            a[5]++;
            a[0x46] = func_80077768((s16)func_80085690(-(s16)(FU16(a, 0x36) - FU16(t, 0x36)), (s16)(FU16(a, 0x2E) - FU16(t, 0x2E))), F16(a, 0x60), 0);
            func_80074590(0x17, -0x12, 0x1E);
        }
        break;
    case 2:
        if (a[0x46] == 0) {
            F16(M2C_FIELD(a, u8 **, 0xC4), 0xA) -= 0x40;
            F16(M2C_FIELD(a, u8 **, 0xC8), 0xA) += 0x40;
            if (F16(M2C_FIELD(a, u8 **, 0xC4), 0xA) < -0x7FF) {
                a[5]++;
            }
        } else {
            F16(M2C_FIELD(a, u8 **, 0xC4), 0xA) += 0x40;
            F16(M2C_FIELD(a, u8 **, 0xC8), 0xA) -= 0x40;
            if (F16(M2C_FIELD(a, u8 **, 0xC4), 0xA) >= 0x800) {
                a[5]++;
            }
        }
        break;
    case 3:
        F16(a, 0x40) = 30;
        a[5]++;
        break;
    case 4:
        if (--F16(a, 0x40) == 0) {
            D_1F800137 = 0;
            D_800BF841 = 0;
            func_8006E1E4();
            D_800BF870.pad1[0x1A6] |= 1 << a[3];
            a[0x5E] = 1;
            a[0] = 1;
            a[5] = 0;
        }
        break;
    }
}

extern u8 D_1F800236;
void func_80125190(u8 *a) {
    u8 *t = D_800E7E80;
    u8 v;

    switch (a[5]) {
    case 0:
        if (a[0x29] != 0) {
            a[5] = 1;
            v = func_80077768((s16)func_80085690(-(s16)(FU16(a, 0x36) - FU16(t, 0x36)), (s16)(FU16(a, 0x2E) - FU16(t, 0x2E))), F16(a, 0x60), 0);
            a[0x46] = v;
            if (v == 0) {
                F16(a, 0x44) = 0x800;
            } else {
                F16(a, 0x44) = -0x800;
            }
        }
        break;
    case 1:
        if (F16(t, 0x32) > F16(a, 0x32)) {
            F16(t, 0x32) = FU16(t, 0x32) - 20;
            if (F16(t, 0x32) < F16(a, 0x32)) {
                F16(t, 0x32) = FU16(a, 0x32);
            }
        } else if (F16(t, 0x32) < F16(a, 0x32)) {
            F16(t, 0x32) = FU16(t, 0x32) + 20;
            if (F16(t, 0x32) > F16(a, 0x32)) {
                F16(t, 0x32) = FU16(a, 0x32);
            }
        }
        M2C_FIELD(t, s32 *, 0x2C) += F16(a, 0x44) * F16(t, 0x48);
        M2C_FIELD(t, s32 *, 0x34) += F16(a, 0x44) * F16(t, 0x4C);
        func_8004766C(t);
        func_80048750(t);
        F16(t, 0xB8) -= 0x80;
        F16(t, 0xBA) -= 0x80;
        F16(t, 0xBC) -= 0x80;
        if (FU16(t, 0xB8) < 0x101) {
            a[5]++;
        }
        break;
    case 2:
        a[5] = 3;
        D_1F800236 = 7;
        D_800BF808[0x31] = 1;
        F16(D_800BF808, 0x32) = a[0xBF] << 4;
        break;
    }
}

#define P(p, o) (*(u8 **)((u8 *)(p) + (o)))
extern u16 D_1F8000D0[];
extern u16 D_800E8008_d0cf[];
void func_801253A8(u8 *a, u16 *b) {
    s16 v[8];
    u8 *p;
    u8 *q;
    u16 t;

    switch (a[5]) {
    case 0:
        H(a, 0x40) = 0x3C;
        a[5]++;
    case 1:
        if (D_800BF80F == 0) {
            a[5]++;
            D_1F800137 = 2;
            D_800BF870.pad1[0x1A8] |= 1 << a[3];
            func_8006E1C0(8);
            D_1F8000D0[1] = b[0];
            D_1F8000D0[3] = b[1];
            D_1F8000D0[5] = b[2];
            D_800E8008_d0cf[0x1D] = b[3];
            D_800E8008_d0cf[0x1F] = b[4];
            t = b[5];
            D_800E7E80[4] = 4;
            D_800E7E80[5] = 0x21;
            D_800E7E80[6] = 0;
            D_800E8008_d0cf[0x21] = t;
        }
        break;
    case 2:
        if (D_800E806E == 3) {
            a[5]++;
        }
        break;
    case 3:
        if (--H(a, 0x40) == -1) {
            H(a, 0x40) = 0x3C;
            a[5]++;
            v[1] = U(a, 0x2E);
            v[3] = U(a, 0x32) + 0x80;
            v[5] = U(a, 0x36);
            p = func_8003116C(0x15, v, -0x32);
            p[0x28] |= 0x80;
            p = func_8003116C(0x24, v, -0x32);
            p[0x28] |= 0x80;
            func_80027144(*(s32 *)(P(a, 0xC0) + 0x40), v, 0x800, 8);
            func_80074590(0xC, 0, 0);
            q = a + 0x2C;
            func_80027144(*(s32 *)(P(a, 0xC0) + 0x40), q, 0x600, 0x18);
            func_80074590(0xC, 0, 0);
            v[1] = U(P(a, 0xC4), 0x2C);
            v[1] = U(P(a, 0xC4), 0x30) + 0x80;
            v[1] = U(P(a, 0xC4), 0x34);
            p = func_8003116C(0x24, v, -0x32);
            p[0x28] |= 0x80;
            func_80027144(*(s32 *)(P(a, 0xC4) + 0x40), q, 0x800, 8);
            func_80074590(0xC, 0, 0);
            func_80027144(*(s32 *)(P(a, 0xC4) + 0x40), q, 0x600, 0x18);
            func_80074590(0xC, 0, 0);
            v[1] = U(P(a, 0xC8), 0x2C);
            v[1] = U(P(a, 0xC8), 0x30) + 0x80;
            v[1] = U(P(a, 0xCC), 0x34);
            p = func_8003116C(0x24, v, -0x32);
            p[0x28] |= 0x80;
            func_80027144(*(s32 *)(P(a, 0xC8) + 0x40), q, 0x800, 8);
            func_80074590(0xC, 0, 0);
            func_80027144(*(s32 *)(P(a, 0xC8) + 0x40), q, 0x600, 0x18);
            func_80074590(0xC, 0, 0);
        } else {
            H(P(a, 0xC0), 2) = (D_1F80017C_0fe7 & 1) * 6;
            H(P(a, 0xC0), 0) = ((func_8009A450() & 3) - 2) * 6;
        }
        break;
    case 4:
        if (--H(a, 0x40) == -1) {
            a[4] = 3;
            D_1F800137 = 0;
            func_8006E1E4();
        }
        a[1] = 0;
        break;
    }
}

extern ClutCycle D_8014579C[];
extern s8 D_801486E8[];
void func_8012579C(s32 arg0) {
    ClutRect r;
    s32 i;
    ClutCycle *e;
    u8 *data;

    if (arg0 == 0) {
        for (i = 0; i < 1; i++) {
            D_801486E8[i] = 0;
        }
        return;
    }
    e = D_8014579C;
    for (i = 0; i < 1; i++, e++) {
        if (--D_801486E8[i] <= 0) {
            if (e->ptr[0] == 0xFF) {
                e->ptr -= e->ptr[1];
            }
            data = e->clut + e->ptr[0] * 32;
            D_801486E8[i] = e->ptr[1];
            r.x = e->x;
            r.y = e->y;
            r.w = 16;
            r.h = 1;
            func_80081218(&r, data);
            e->ptr += 2;
        }
    }
}

extern s8 D_800BF80D;
extern u8 D_800BF8F5;
extern u8 D_800E7E80_d97c;
extern u8 D_801457A8[];
extern u8 D_801457C8[];
extern s16 D_1F800160_71b4;
extern s16 D_1F800162_a8d4;
extern s16 D_1F800164_d75f;
void func_801258BC(u8 *a)
{
    switch (a[4]) {
    case 0:
        switch (a[5]) {
        case 0:
            func_8012579C(0);
            a[0xBF] = 0xB0;
            *(s16 *)(a + 0x7E) = 0x18;
            *(s16 *)(a + 0x7C) = 0x400;
            *(s16 *)(a + 0x7A) = 0xC;
            *(s16 *)(a + 0x78) = 0x1B;
            *(s16 *)(a + 0x54) = 0;
            *(s16 *)(a + 0x58) = 0;
            a[5]++;
        case 1:
            func_80124DEC(a, D_801457A8);
            break;
        case 2:
            if (D_800BF8F5 == 0xFF && D_1F800137 == 0) {
                a[5] = 3;
            }
            break;
        case 3:
            if (func_80078240(D_1F800160_71b4 - *(s16 *)(a + 0x2E), D_1F800162_a8d4 - *(s16 *)(a + 0x32), D_1F800164_d75f - *(s16 *)(a + 0x36)) <= 1000
                && D_1F80027A == 0 && D_800E7E80_d97c != 6 && D_800BF80D == 0) {
                a[4] = 1;
                a[5] = 0;
                a[0x5E] = 0;
            }
            break;
        }
        break;
    case 1:
        if (func_8007778C(a) != 0) {
            func_8012579C(1);
            func_80051844(a);
        }
        switch (a[0x5E]) {
        case 0:
            func_80124F48(a);
            a[0x29] = 0;
            break;
        case 1:
            func_80125190(a);
            a[0x29] = 0;
            break;
        case 2:
            func_801253A8(a, D_801457C8);
            a[0x29] = 0;
            break;
        default:
            a[0x29] = 0;
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

extern u8 D_800BF8EA;
extern u8 D_800E7EEF;
void func_80125B10(u8 *a)
{
    s16 sp[8];

    switch (a[4]) {
    case 0:
        if (func_80051B70(a, 0xC, 0x6F) == 0) {
            *(s16 *)(a + 0x80) = 0x50;
            *(s16 *)(a + 0x82) = 0xA0;
            *(s16 *)(a + 0x84) = 0x140;
            *(s16 *)(a + 0x86) = 0x140;
            a[0] = 1;
            a[0x2B] = 0;
            a[0x29] = 0;
            *(s16 *)(a + 0x54) = 0;
            *(s16 *)(a + 0x56) = 0xC00;
            *(s16 *)(a + 0x58) = 0;
            a[4]++;
        }
        break;
    case 1:
        if (a[0x29] != 0 && D_800BF8EA == 0) {
            func_80040B48(0x36);
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
            if (D_800E7EEF != 0x16) {
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
                func_80040C00(0x36);
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

extern u8 D_800E8001;
extern u8 D_800BF818;
void func_80125D88(u8 *a)
{
    u8 *b;

    switch (a[6]) {
    case 0:
        if (D_800BFA3F & 0x10) {
            *(s16 *)(*(u8 **)(a + 0xD0) + 2) -= 4;
            a[6]++;
        }
        break;
    case 1:
        if ((*(s16 *)(*(u8 **)(a + 0xD0) + 2) -= 4) < -0x2DC) {
            *(s16 *)(*(u8 **)(a + 0xD0) + 2) = -0x2DC;
            a[6] = 0xA;
        }
        break;
    }
    if (D_800E8001 != 0) {
        a[0xBF] = 0;
    } else {
        a[0xBF] = 1;
    }
    b = *(u8 **)(a + 0xC4);
    switch (a[5]) {
    case 0:
        a[5]++;
        *(s16 *)(b + 0xE) = *(s16 *)(b + 0xA);
        func_80072FE0(a, b);
        break;
    case 1:
        if (D_800BF818 == 2) {
            *(s16 *)(a + 0x40) = 0;
            a[5]++;
        }
        break;
    case 2:
        if (++*(s16 *)(a + 0x40) >= 0x19) {
            if (func_80073194(a, b) != 0) {
                a[5]++;
            }
        }
        break;
    case 3:
        if (D_800BF818 == 3) {
            a[5]++;
        }
        break;
    case 4:
        if (func_8007302C(a, b) != 0) {
            a[5]++;
        }
        break;
    case 5:
        break;
    }
    if (D_800E8001 != 0) {
        *(s16 *)(*(u8 **)(a + 0xC4) + 0xA) = 0;
    }
}

extern u8 D_800BFA43;
void func_80125F6C(u8 *a)
{
    switch (a[5]) {
    case 0:
        if (D_800BFA43 != 5) {
            break;
        }
        a[0xD] |= 4;
        (*(u8 **)(a + 0xC4))[0x3F] = 0x46;
        (*(u8 **)(a + 0xC8))[0x3F] = 0x46;
        a[5]++;
        break;
    case 1:
        U(*(u8 **)(a + 0xC4), 2) -= 4;
        U(*(u8 **)(a + 0xC8), 2) += 4;
        if (H(*(u8 **)(a + 0xC8), 2) < 0xC8) {
            break;
        }
        D_800BFA43 = 6;
        H(*(u8 **)(a + 0xC4), 2) = -0x188;
        H(*(u8 **)(a + 0xC8), 2) = 0xC8;
        a[5]++;
        break;
    case 2:
        if (D_800BFA43 != 7) {
            break;
        }
        a[8] = 1;
        a[5] = 0xA;
        a[0xD] &= ~4;
        break;
    }
}

typedef struct { u8 pad[0xC0]; u8 *parts[16]; } A6090;
#define PT(a, i) (((A6090 *)(a))->parts[i])
extern u8 D_8014595C[][2];
extern s16 *D_80145934[];
extern u8 D_800BF922;
extern u8 D_8014597C[];
#define DOORSEQ(a) \
    { \
        u8 *p = PT(a, 1); \
        switch ((a)[5]) { \
        case 0: \
            (a)[5]++; \
            H(p, 0xE) = H(p, 0xA); \
            func_80072FE0(a); \
            break; \
        case 1: \
            if (D_800BF818 == 2) { \
                H(a, 0x40) = 0; \
                (a)[5]++; \
            } \
            break; \
        case 2: \
            H(a, 0x40)++; \
            if (H(a, 0x40) >= 0x19) { \
                if (func_80073194(a) != 0) { \
                    (a)[5]++; \
                } \
            } \
            break; \
        case 3: \
            if (D_800BF818 == 3) { \
                (a)[5]++; \
            } \
            break; \
        case 4: \
            if (func_8007302C(a) != 0) { \
                (a)[5]++; \
            } \
            break; \
        case 5: \
            break; \
        } \
    }
static inline s32 Talk6090(u8 *a)
{
    switch (a[6]) {
    case 0:
        if (D_800BF80F == 0) {
            a[6] = 1;
            func_80042354(1, 2);
            func_80040CDC(a, 0, D_8014597C);
            a[0x70] = 1;
        }
        break;
    case 1:
        func_80041098(a);
        if (a[0x70] == 0xFF) {
            a[6] = 0;
            func_80042310();
            return 1;
        }
        break;
    }
    return 0;
}
void f_UpdateWaterTempleInteriorEnvironmentActor(u8 *a)
{
    s16 *d;
    s32 i;
    u8 *g;

    switch (a[4]) {
    case 0:
        a[8] = D_8014595C[a[3]][0];
        if (D_800ED098 < a[8]) {
            a[4] = 3;
            break;
        }
        a[9] = a[8];
        a[4]++;
        a[0xD] = 0;
        a[0xB] = 0;
        H(a, 0x54) = 0;
        H(a, 0x58) = 0;
        d = D_80145934[a[3]];
        for (i = 0; i < a[8]; i++) {
            PT(a, i) = func_8007AAE8();
            H(PT(a, i), 6) = *d++;
            H(PT(a, i), 0) = *d++;
            H(PT(a, i), 2) = *d++;
            H(PT(a, i), 4) = *d++;
            H(PT(a, i), 8) = *d++;
            H(PT(a, i), 0xA) = *d++;
            H(PT(a, i), 0xC) = *d++;
            func_80051B04(PT(a, i), 0xC, *d++);
        }
        a[0xBF] = 1;
        switch (a[3]) {
        case 0:
            H(a, 0x56) = 0x2CC;
            a[0x46] = 1;
            break;
        case 1:
            H(a, 0x56) = -0x127;
            a[0x46] = 1;
            break;
        case 2:
            g = (u8 *)&D_800BF870;
            if (g[0x6F] != 0xFF) {
                func_80051B04(PT(a, 3), 0xC, 0x74);
            }
            if (g[0x1CA] >= 5) {
                W_d1fb(PT(a, 2), 0x40) = 0;
            }
            if (g[0x1CF] & 0x10) {
                H(PT(a, 4), 2) = -0x2DC;
                a[6] = 0xA;
            }
            H(a, 0x56) = 0x127;
            a[0x46] = 1;
            break;
        case 3:
        case 4:
            a[0x46] = 1;
            H(a, 0x56) = 0;
            break;
        case 5:
            a[0x46] = 0;
            H(a, 0x56) = 0x400;
            break;
        case 6:
            H(a, 0x56) = -0x2D8;
            a[0xBF] = 0;
            break;
        case 7:
        case 8:
            H(a, 0x56) = 0;
            a[0xBF] = 0;
            break;
        case 9:
            H(a, 0x56) = 0x127;
            if (D_800BFA43 >= 7) {
                a[8] = 1;
                a[5] = 0xA;
            }
            a[0xBF] = 0;
            break;
        }
        break;
    case 1:
        switch (a[3]) {
        case 0:
            DOORSEQ(a)
            break;
        case 1:
            DOORSEQ(a)
            break;
        case 2:
            func_80125D88(a);
            break;
        case 3:
            DOORSEQ(a)
            if (D_800BF922 == 0xFF) {
                a[1] = 1;
                func_800517F8(a);
            }
            return;
        case 4:
            DOORSEQ(a)
            break;
        case 5:
            DOORSEQ(a)
            break;
        case 6:
        case 7:
            break;
        case 8:
            switch (a[5]) {
            case 0:
                if (D_800BF8F5 == 0xFF) {
                    a[5] = 2;
                } else {
                    a[5] = 1;
                }
                break;
            case 1:
                if (Talk6090(a)) {
                    a[5]++;
                }
                break;
            case 2:
                break;
            }
            break;
        case 9:
            func_80125F6C(a);
            break;
        }
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

void func_801267D4(u8 *a)
{
    s32 s = a[5];
    s32 r;

    switch (s) {
    case 0:
        if (D_800BF8F5 == 0xFF) {
            a[5] = 2;
        } else {
            a[5] = 1;
        }
        break;
    case 1:
        switch (a[6]) {
        case 0:
            if (D_800BF80F != 0) {
                r = 0;
                goto done;
            }
            a[6] = s;
            func_80042354(1, 2);
            func_80040CDC(a, 0, D_8014597C);
            a[0x70] = s;
            break;
        case 1:
            func_80041098(a);
            if (a[0x70] != 0xFF) {
                r = 0;
                goto done;
            }
            a[6] = 0;
            func_80042310();
            r = 1;
            goto done;
        default:
            r = 0;
            goto done;
        }
        r = 0;
    done:
        if (r) {
            a[5]++;
        }
        break;
    case 2:
        break;
    }
}

#define PART(a) (*(u8 **)((a) + ((a)[8] << 2) + 0xC0))
s32 func_801268D8(u8 *a0, u16 *src, s32 n, s32 d, s32 e)
{
    s16 buf[7];
    u8 *a = a0;
    s32 i;

    if (D_800ED098 <= 0) {
        return 1;
    }
    for (i = 0; i < 7; i++) {
        if (i < n) {
            buf[i] = *src++;
        } else {
            buf[i] = 0;
        }
    }
    PART(a) = func_8007AAE8();
    *(s16 *)(PART(a) + 6) = buf[0];
    *(s16 *)(PART(a) + 0) = buf[1];
    *(s16 *)(PART(a) + 2) = buf[2];
    *(s16 *)(PART(a) + 4) = buf[3];
    *(s16 *)(PART(a) + 8) = buf[4];
    *(s16 *)(PART(a) + 0xA) = buf[5];
    *(s16 *)(PART(a) + 0xC) = buf[6];
    *(s16 *)(PART(a) + 0x38) = 0x1000;
    *(s16 *)(PART(a) + 0x3A) = 0x1000;
    *(s16 *)(PART(a) + 0x3C) = 0x1000;
    func_80051B04(PART(a), d, e);
    a[8]++;
    a[9]++;
    return 0;
}

extern u8 D_800BFA3B;
extern s32 D_1F800214;
void func_80126AD8(u8 *a)
{
    switch (a[5]) {
    case 0:
        if (D_800BFA3B == 0x10) {
            *(s16 *)(a + 0x48) = func_80083F50(0x52E) >> 4;
            *(s16 *)(a + 0x4C) = func_80083E80(-0x52E) >> 4;
            *(s16 *)(a + 0x44) = 0xC00;
            a[5]++;
        }
        break;
    case 1:
        if (*(s16 *)(a + 0x36) < 0x640) {
            func_80041718(D_1F800214, 4, 4);
            func_800440E4(D_800E7E80, 0xB4, 4);
            a[5]++;
        }
    case 2:
        a[1] = 1;
        func_80041A1C(a, 1);
        if (*(s16 *)(a + 0x36) < 0x44C) {
            D_800BFA3B = 0x11;
            a[5]++;
        }
        break;
    case 3:
        a[1] = 1;
        func_80041A1C(a, 1);
        if (*(s16 *)(a + 0x2E) <= 0 || *(s16 *)(a + 0x36) <= 0) {
            *(s16 *)(a + 0x36) = 0;
            *(s16 *)(a + 0x2E) = 0;
            D_800BFA3B = 0x12;
            a[5] = 0xA;
        }
        break;
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
        break;
    case 10:
        a[1] = 1;
        break;
    }
    if (a[1] != 0) {
        func_800517F8(a);
    }
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80126C68);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80126E24);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_801273B4);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_801277E0);

typedef struct { u8 pad[0xC0]; u8 *parts[1]; } PartsOwner;
typedef struct { s16 v[4]; } PartInit;
extern PartInit D_801459C4[];
void func_801279DC(PartsOwner *a)
{
    s32 i;
    u8 *q;

    a->pad[8] = 2;
    if (D_800ED098 < a->pad[8]) {
        a->pad[4] = 3;
        return;
    }
    a->pad[9] = 2;
    a->pad[0xD] = 4;
    a->pad[0xB] = 0;
    for (i = 0; i < a->pad[8]; i++) {
        q = func_8007AAE8();
        a->parts[i] = q;
        *(s16 *)(q + 6) = D_801459C4[i].v[0];
        *(s16 *)(a->parts[i] + 0) = D_801459C4[i].v[1];
        *(s16 *)(a->parts[i] + 2) = D_801459C4[i].v[2];
        *(s16 *)(a->parts[i] + 4) = D_801459C4[i].v[3];
        *(s16 *)(a->parts[i] + 8) = 0;
        *(s16 *)(a->parts[i] + 0xA) = 0;
        *(s16 *)(a->parts[i] + 0xC) = 0;
        func_80051B04(a->parts[i], 0xC, i + 0x55);
        a->parts[i][0x3F] = 8;
    }
    *(s16 *)(a->pad + 0x56) = 0x400;
    *(s16 *)(a->pad + 0x54) = 0;
    *(s16 *)(a->pad + 0x58) = 0;
    if (D_800BF922 == 0xFF) {
        a->pad[5] = 2;
        *(s16 *)(a->parts[1] + 8) = -0x700;
    }
}

extern PartInit D_801459D4[];
void func_80127B34(PartsOwner *a)
{
    s32 i;
    u8 *q;

    a->pad[8] = 2;
    if (D_800ED098 < a->pad[8]) {
        a->pad[4] = 3;
        return;
    }
    a->pad[9] = 2;
    a->pad[0xD] = 0;
    a->pad[0xB] = 0;
    for (i = 0; i < a->pad[8]; i++) {
        q = func_8007AAE8();
        a->parts[i] = q;
        *(s16 *)(q + 6) = D_801459D4[i].v[0];
        *(s16 *)(a->parts[i] + 0) = D_801459D4[i].v[1];
        *(s16 *)(a->parts[i] + 2) = D_801459D4[i].v[2];
        *(s16 *)(a->parts[i] + 4) = D_801459D4[i].v[3];
        *(s16 *)(a->parts[i] + 8) = 0;
        *(s16 *)(a->parts[i] + 0xA) = 0;
        *(s16 *)(a->parts[i] + 0xC) = 0;
        func_80051B04(a->parts[i], 0xC, i + 0x64);
    }
    *(s16 *)(a->pad + 0x54) = 0;
    *(s16 *)(a->pad + 0x56) = 0x400;
    *(s16 *)(a->pad + 0x58) = 0;
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80127C58);

extern u8 D_800BFA31;
extern u8 D_800BFB22;
extern M2C_UNK D_801459BC;
extern s8 D_800BF93E;
extern M2C_UNK func_8011973C;
extern u16 D_1F8000E2;
extern u8 D_800BFA3A;
extern u8 D_800BFA30;
static inline void func_80128C78_inl(u8 *p)
{
    u8 v = D_800BFA31;

    if (v < 4) {
        func_80051B70(p, 0xC, 0x13);
    } else if (v < 7) {
        func_80051B70(p, 0xC, 0x14);
    } else {
        func_80051B70(p, 0xC, 0x15);
    }
    func_800517F8(p);
}
static inline void func_80128D60_inl(u8 *p)
{
    *(s32 *)(p + 0x3C) = D_800ECF80;
    func_80077B38(p, D_801486EC, 0x9);
    p[0xB] = 0x10;
    *(s16 *)(p + 0x5C) = 0;
    *(s16 *)(p + 0x5A) = 0;
    p[0x47] = 0;
    p[8] = 0xF0;
}
static inline void func_80128E30_inl(u8 *p)
{
    func_80051B70(p, 0xC, 0x20);
    if (D_800BF8E2 == 0xFF) {
        p[5] = 10;
    } else {
        *(s16 *)(p + 0x2E) = 0x3FC;
        *(s16 *)(p + 0x36) = 0x7F0;
    }
}
static inline void func_80128F08_inl(u8 *a)
{
    switch (a[5]) {
    case 0:
        if (D_800BFA3B == 0xE) {
            a[5]++;
        }
        break;
    case 1:
        if ((*(s16 *)(a + 0x32) += 0x10) >= 0x1F4) {
            D_800BFA3B = 0xF;
            a[4] = 3;
        }
        break;
    }
    a[1] = 1;
    func_800517F8(a);
}
static inline void func_80128FA4_inl(u8 *p)
{
    func_80051B70(p, 0xC, 0x1F);
    func_800517F8(p);
    if (D_800BF8DF == 0xFF) {
        p[5] = 1;
    }
}
static inline void func_801290DC_inl(void *arg0) {
    if ((D_800BFB22 != 0) || (D_800ED098 < 2)) {
        M2C_FIELD(arg0, s8 *, 4) = 3;
        return;
    }
    func_80051B70(arg0, 0xC, 0x4D);
    func_801268D8(arg0, &D_801459BC, 4, 0xC, 0x4E);
    M2C_FIELD(arg0, s8 *, 0) = 1;
    M2C_FIELD(arg0, s16 *, 0x80) = 0xF8;
    M2C_FIELD(arg0, s16 *, 0x82) = 0x1F0;
    M2C_FIELD(arg0, s16 *, 0x84) = 0x220;
    M2C_FIELD(arg0, s16 *, 0x86) = 0x220;
    M2C_FIELD(arg0, s8 *, 0x29) = 0;
    M2C_FIELD(arg0, s8 *, 0x5F) = 0;
    func_8004766C(arg0);
    func_80048750(arg0);
    M2C_FIELD(arg0, u16 *, 0x60) = D_1F8001A0_b0de_1f9a;
    func_800517F8(arg0);
    M2C_FIELD(arg0, s32 *, 0x10) = func_8003116C(0x90B, arg0 + 0x2C, -0x20);
}
static inline void func_8012920C_inl(u8 *p)
{
    if (func_80051B70(p, 0xC, 0x6C) == 0) {
        *(s16 *)(p + 0x56) = 0xACD;
        *(s16 *)(p + 0x58) = 0xC5C;
        *(s16 *)(p + 0x2E) = 0x224D;
        *(s16 *)(p + 0x32) = -0x1580;
        *(s16 *)(p + 0x54) = 0;
        *(s16 *)(p + 0x36) = 0x325E;
    }
}
static inline void func_80129300_inl(u8 *p)
{
    if (func_80051B70(p, 0xC, 0x58) == 0) {
        p[0xD] |= 4;
        (*(u8 **)(p + 0xC0))[0x3F] = 0x1E;
        p[0] = 1;
        *(s16 *)(p + 0x80) = 0x78;
        *(s16 *)(p + 0x82) = 0xF0;
        *(s16 *)(p + 0x84) = 0x1C0;
        *(s16 *)(p + 0x86) = 0x1C0;
        func_800517F8(p);
    }
}
static inline void func_801293B0_inl(u8 *p)
{
    if (func_80051B70(p, 0xC, 0x57) == 0) {
        if (D_800BF928 == 0xFF) {
            p[5] = 1;
            *(s16 *)(p + 0x2E) = 0x40C9;
            *(s16 *)(p + 0x32) = -0xEB8;
            *(s16 *)(p + 0x36) = 0x10ED;
        } else {
            p[5] = 0;
        }
        *(s16 *)(p + 0x54) = 0;
        *(s16 *)(p + 0x56) = 0;
        *(s16 *)(p + 0x58) = 0;
    }
}
static inline void func_80129424_inl(u8 *a)
{
    u8 *t = D_800E7E80;

    if (a[5] == 0) {
        func_8004BD64(a, 0, *(s32 *)(t + 0xDC), *(s32 *)(t + 0xD0), 0);
        if (D_800BFA30 & 1) {
            *(s16 *)(a + 0x2E) = 0x40C9;
            *(s16 *)(a + 0x32) = -0xEB8;
            *(s16 *)(a + 0x36) = 0x10ED;
            a[5]++;
        }
    }
    func_800517F8(a);
    func_8007778C(a);
}
static inline void func_801295C4_inl(u8 *a) {
    if (func_80051B70(a, 0xC, 0x6B) == 0) {
        M2C_FIELD(a, s16 *, 0x56) = 0x4FC;
        M2C_FIELD(a, s16 *, 0x58) = 0;
        M2C_FIELD(a, s16 *, 0x54) = 0;
        M2C_FIELD(a, s16 *, 0x40) = 0;
        M2C_FIELD(a, s32 *, 0x10) = 0;
        if (*(u8 *)&D_800BF93E == 0xFF) {
            a[5] = 10;
            a[0xD] |= 4;
            M2C_FIELD(a, u8 **, 0xC0)[0x3F] = 0xF6;
        }
    }
}
static inline void func_801297E8_inl(u8 *p, s32 k)
{
    *(s32 *)(p + 0x3C) = D_800ECF80;
    func_80077B38(p, D_801486EC, k);
    p[0xD] = 0;
    *(s16 *)(p + 0x5C) = 0;
    p[0xB] = 0x10;
    *(s16 *)(p + 0x5A) = 0;
    p[0x47] = 0;
}
static inline void func_80129960_inl(void *arg0) {
    M2C_FIELD(arg0, s8 *, 0xB) = 0x20;
    M2C_FIELD(arg0, M2C_UNK **, 0x18) = &func_8011973C;
    M2C_FIELD(arg0, s16 *, 0x2E) = 0x3053;
    M2C_FIELD(arg0, s16 *, 0x32) = -0x1116;
    M2C_FIELD(arg0, s16 *, 0x36) = 0x17C3;
    M2C_FIELD(arg0, s16 *, 0x84) = 0xC8;
    M2C_FIELD(arg0, s16 *, 0x80) = 0;
    M2C_FIELD(arg0, s16 *, 0x82) = 0;
    M2C_FIELD(arg0, s16 *, 0x86) = 0x190;
}
static inline void func_801299A8_inl(u8 *a)
{
    s32 s = a[5];
    a[1] = 1;
    switch (s) {
    case 0:
        if (D_800BFA3F & 0x80) {
            a[5] = s + 1;
            return;
        }
        if (*(s16 *)(a + 0x80) != 0) {
            *(s16 *)(a + 0x80) = (s16)(*(s16 *)(a + 0x80) - 1) - (*(s16 *)(a + 0x80) >> 2);
        }
        break;
    case 1:
        if (!(D_800BFA3F & 0x80)) {
            a[5] = 0;
            return;
        }
        if (*(s16 *)(a + 0x80) < 0x100) {
            *(s16 *)(a + 0x80) = (s16)(*(s16 *)(a + 0x80) + 1) + ((0x100 - *(s16 *)(a + 0x80)) >> 2);
        }
        break;
    }
}
static inline void func_80129B40_inl(void *arg0) {
    M2C_FIELD(arg0, s8 *, 0) = 1;
    M2C_FIELD(arg0, s16 *, 0x80) = 0x40;
    M2C_FIELD(arg0, s16 *, 0x82) = 0x80;
    M2C_FIELD(arg0, s16 *, 0x84) = 0x190;
    M2C_FIELD(arg0, s16 *, 0x86) = 0x320;
}
void f_UpdateWaterTempleQuestPropActor(u8 *a)
{
    u8 *p;
    u8 *g;
    s32 s;

    switch (a[4]) {
    case 0:
        a[4] = 1;
        switch (a[3]) {
        case 0:
        case 1:
        case 2:
        case 3:
            func_80051B70(a, 0xC, D_801459AC[a[3]]);
            func_800517F8(a);
            break;
        case 4:
            func_80128C78_inl(a);
            break;
        case 5:
            func_80128D60_inl(a);
            break;
        case 6:
            func_80128E30_inl(a);
            break;
        case 7:
            if (D_800BF8E2 == 0xFF) {
                a[4] = 3;
            } else {
                func_80051B70(a, 0xC, 0x21);
            }
            break;
        case 8:
            if (D_800BF8E2 == 0xFF) {
                a[4] = 3;
            } else {
                func_80051B70(a, 0xC, 0x22);
            }
            break;
        case 9:
            func_80128FA4_inl(a);
            break;
        case 10:
            func_801290DC_inl(a);
            break;
        case 11:
            func_8012920C_inl(a);
            break;
        case 12:
        case 13:
            break;
        case 14:
            if (func_80051B70(a, 0xC, 0x2B) == 0) {
                func_800517F8(a);
            }
            break;
        case 15:
            break;
        case 16:
            func_80129300_inl(a);
            break;
        case 17:
            func_801293B0_inl(a);
            break;
        case 18:
            func_801297E8_inl(a, 0xC);
            break;
        case 19:
            func_801295C4_inl(a);
            break;
        case 20:
            if (func_80051B70(a, 0xC, 0x6E) == 0) {
                H(a, 0x58) = 0;
                H(a, 0x56) = 0;
                H(a, 0x54) = 0;
            }
            break;
        case 21:
            if (func_80051B70(a, 0xC, 0x6D) == 0) {
                H(a, 0x58) = 0;
                H(a, 0x56) = 0;
                H(a, 0x54) = 0;
            }
            break;
        case 22:
            func_801297E8_inl(a, 5);
            break;
        case 23:
            if (D_800BFA42 != 0) {
                a[4] = 3;
            } else {
                func_80051B70(a, 0xC, 0x6C);
            }
            break;
        case 24:
            func_80129960_inl(a);
            break;
        case 25:
            func_801279DC(a);
            break;
        case 26:
            func_80127B34(a);
            break;
        case 27:
            func_80129B40_inl(a);
            break;
        }
        break;
    case 1:
        switch (a[3]) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
            func_800778E4(a, (s16)(D_1F8000E2 - H(a, 0x32)));
            break;
        case 5:
            {
                u8 d = D_800BFA4E;
                s32 one = 1;
                u8 *r = *(u8 **)(a + 0x10);
                if (d == one) {
                    func_8004D4C4(0x54, one);
                    func_8004B0D8(a);
                    a[4] = 3;
                } else {
                    func_8004BD64(a, 0, *(s32 *)(r + 0xD8), *(s32 *)(r + 0xCC), 0);
                    a[1] = one;
                }
            }
            break;
        case 6:
            func_80126AD8(a);
            break;
        case 7:
            func_80126C68(a);
            break;
        case 8:
            func_80128F08_inl(a);
            break;
        case 9:
            switch (a[5]) {
            case 0:
                if (D_800BFA3A >= 0xB) {
                    a[5] = 1;
                }
                break;
            case 1:
                a[1] = 1;
                func_800517F8(a);
                break;
            }
            break;
        case 11:
            if (D_800BF816 == 0) {
                a[4] = 3;
            } else if (func_8007778C(a) != 0) {
                func_800517F8(a);
            }
            break;
        case 10:
            func_80126E24(a);
            break;
        case 12:
        case 13:
            break;
        case 14:
            a[1] = 1;
            break;
        case 15:
            break;
        case 16:
            func_8007778C(a);
            break;
        case 17:
            func_80129424_inl(a);
            break;
        case 18:
            if ((D_800BFA32 >> H(a, 0x60)) & 1) {
                a[4] = 3;
            } else {
                a[1] = 1;
                func_8004DAEC(a);
                H(a, 0x2E) += 0x20;
            }
            break;
        case 19:
            func_801273B4(a);
            break;
        case 20:
            if (D_800BFA3A == 0xB) {
                a[4] = 3;
            } else {
                a[1] = 1;
                func_800517F8(a);
            }
            break;
        case 21:
            a[1] = 1;
            func_800517F8(a);
            break;
        case 22:
            s = a[5];
            a[1] = 1;
            switch (s) {
            case 0:
                {
                    u8 *t = D_800E7E80;
                    func_8004BD64(a, 0, *(s32 *)(t + 0xDC), *(s32 *)(t + 0xD0), 0);
                }
                break;
            case 1:
                {
                    u8 *q = *(u8 **)(a + 0x10);
                    H(a, 0x2E) = (*(s32 *)(*(u8 **)(q + 0xD0) + 0x2C) + *(s32 *)(*(u8 **)(q + 0xDC) + 0x2C)) / 2;
                    H(a, 0x32) = (*(s32 *)(*(u8 **)(q + 0xD0) + 0x30) + *(s32 *)(*(u8 **)(q + 0xDC) + 0x30)) / 2 - 0x28;
                    H(a, 0x36) = (*(s32 *)(*(u8 **)(q + 0xD0) + 0x34) + *(s32 *)(*(u8 **)(q + 0xDC) + 0x34)) / 2;
                }
                break;
            case 2:
                break;
            }
            break;
        case 23:
            func_801277E0(a);
            break;
        case 24:
            func_801299A8_inl(a);
            break;
        case 25:
            g = (u8 *)&D_800BF870;
            if (g[0xB2] == 0xFF) {
                switch (a[5]) {
                case 0:
                    if (g[0x1E0] >= 0x1E) {
                        a[5] = 1;
                        func_80074590(0x1A, 0x1B, 0);
                    }
                    break;
                case 1:
                    H(*(u8 **)(a + 0xC4), 8) -= 0x40;
                    if (H(*(u8 **)(a + 0xC4), 8) < -0x6FF) {
                        a[5]++;
                        g[0x1E0] = 0x1F;
                    }
                    break;
                case 2:
                    break;
                }
                a[1] = 1;
                func_800517F8(a);
            }
            break;
        case 26:
            func_80127C58(a);
            break;
        case 27:
            if (D_800BF8E3 == 0xFF) {
                a[4] = 3;
            } else {
                a[1] = 1;
                func_80077EBC(a);
            }
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

void func_80128BF8(u8 *p)
{
    func_80051B70(p, 0xC, D_801459AC[p[3]]);
    func_800517F8(p);
}

s32 func_800778E4(void *, s16);
s32 func_80128C40(u8 *a0)
{
    return func_800778E4(a0, D_1F8000E2 - *(u16 *)(a0 + 0x32));
}

void func_80128C78(u8 *p)
{
    u8 v = D_800BFA31;

    if (v < 4) {
        func_80051B70(p, 0xC, 0x13);
    } else if (v < 7) {
        func_80051B70(p, 0xC, 0x14);
    } else {
        func_80051B70(p, 0xC, 0x15);
    }
    func_800517F8(p);
}

s32 func_80128CE4(u8 *a0)
{
    return func_800778E4(a0, D_1F8000E2 - *(u16 *)(a0 + 0x32));
}

void f_UpdateWaterTempleQuestPropActor();
u8 *func_80128D1C(void *a0)
{
    u8 *r = func_80072DDC(a0, 0x80, 3, 0x10);

    if (r) {
        *(void **)(r + 0x1C) = f_UpdateWaterTempleQuestPropActor;
        r[3] = 5;
    }
    return r;
}

void func_80128D60(u8 *p)
{
    *(s32 *)(p + 0x3C) = D_800ECF80;
    func_80077B38(p, D_801486EC, 0x9);
    p[0xB] = 0x10;
    *(s16 *)(p + 0x5C) = 0;
    *(s16 *)(p + 0x5A) = 0;
    p[0x47] = 0;
    p[8] = 0xF0;
}

void func_80128DB8(void *arg0) {
    void *temp_v1;

    temp_v1 = M2C_FIELD(arg0, void **, 0x10);
    if (D_800BFA4E == 1) {
        func_8004D4C4(0x54, 1);
        func_8004B0D8(arg0);
        M2C_FIELD(arg0, s8 *, 4) = 3;
        return;
    }
    func_8004BD64(arg0, 0, M2C_FIELD(temp_v1, s32 *, 0xD8), M2C_FIELD(temp_v1, s32 *, 0xCC), 0);
    M2C_FIELD(arg0, s8 *, 1) = 1;
}

void func_80128E30(u8 *p)
{
    func_80051B70(p, 0xC, 0x20);
    if (D_800BF8E2 == 0xFF) {
        p[5] = 10;
    } else {
        *(s16 *)(p + 0x2E) = 0x3FC;
        *(s16 *)(p + 0x36) = 0x7F0;
    }
}

void func_80128E88(u8 *p)
{
    if (D_800BF8E2 == 0xFF) {
        p[4] = 3;
    } else {
        func_80051B70(p, 0xC, 0x21);
    }
}

void func_80128EC8(u8 *p)
{
    if (D_800BF8E2 == 0xFF) {
        p[4] = 3;
    } else {
        func_80051B70(p, 0xC, 0x22);
    }
}

void func_80128F08(u8 *a)
{
    switch (a[5]) {
    case 0:
        if (D_800BFA3B == 0xE) {
            a[5]++;
        }
        break;
    case 1:
        if ((*(s16 *)(a + 0x32) += 0x10) >= 0x1F4) {
            D_800BFA3B = 0xF;
            a[4] = 3;
        }
        break;
    }
    a[1] = 1;
    func_800517F8(a);
}

void func_80128FA4(u8 *p)
{
    func_80051B70(p, 0xC, 0x1F);
    func_800517F8(p);
    if (D_800BF8DF == 0xFF) {
        p[5] = 1;
    }
}

void func_80128FF0(u8 *p)
{
    switch (p[5]) {
    case 0:
        if (D_800BFA3A >= 0xB) {
            p[5] = 1;
        }
        break;
    case 1:
        p[1] = 1;
        func_800517F8(p);
        break;
    }
}

void D_8004C930();
u8 *func_80129050(u8 *a) {
    u8 *p = func_80072DDC(a, 0, 5, 4);

    if (p != NULL) {
        M2C_FIELD(p, void **, 0x1C) = D_8004C930;
        M2C_FIELD(p, s16 *, 0x2E) = M2C_FIELD(a, u16 *, 0x2E);
        M2C_FIELD(p, s16 *, 0x32) = M2C_FIELD(a, u16 *, 0x32) - M2C_FIELD(a, s16 *, 0x84) / 2;
        M2C_FIELD(p, s16 *, 0x36) = M2C_FIELD(a, u16 *, 0x36);
        p[3] = 39;
    }
    return p;
}

void func_801290DC(void *arg0) {
    if ((D_800BFB22 != 0) || (D_800ED098 < 2)) {
        M2C_FIELD(arg0, s8 *, 4) = 3;
        return;
    }
    func_80051B70(arg0, 0xC, 0x4D);
    func_801268D8(arg0, &D_801459BC, 4, 0xC, 0x4E);
    M2C_FIELD(arg0, s8 *, 0) = 1;
    M2C_FIELD(arg0, s16 *, 0x80) = 0xF8;
    M2C_FIELD(arg0, s16 *, 0x82) = 0x1F0;
    M2C_FIELD(arg0, s16 *, 0x84) = 0x220;
    M2C_FIELD(arg0, s16 *, 0x86) = 0x220;
    M2C_FIELD(arg0, s8 *, 0x29) = 0;
    M2C_FIELD(arg0, s8 *, 0x5F) = 0;
    func_8004766C(arg0);
    func_80048750(arg0);
    M2C_FIELD(arg0, u16 *, 0x60) = (u16) *(u16 *)0x1F8001A0;
    func_800517F8(arg0);
    M2C_FIELD(arg0, s32 *, 0x10) = func_8003116C(0x90B, arg0 + 0x2C, -0x20);
}

u8 *func_801291BC(void *a0)
{
    u8 *r = func_80072DDC(a0, 1, 3, 0x10);

    if (r) {
        *(void **)(r + 0x1C) = f_UpdateWaterTempleQuestPropActor;
        r[3] = 0xB;
        r[0x28] |= 0x80;
    }
    return r;
}

void func_8012920C(u8 *p)
{
    if (func_80051B70(p, 0xC, 0x6C) == 0) {
        *(s16 *)(p + 0x56) = 0xACD;
        *(s16 *)(p + 0x58) = 0xC5C;
        *(s16 *)(p + 0x2E) = 0x224D;
        *(s16 *)(p + 0x32) = -0x1580;
        *(s16 *)(p + 0x54) = 0;
        *(s16 *)(p + 0x36) = 0x325E;
    }
}

void func_80129268(void *arg0) {
    if (D_800BF816 == 0) {
        M2C_FIELD(arg0, s8 *, 4) = 3;
        return;
    }
    if (func_8007778C(arg0) != 0) {
        func_800517F8(arg0);
    }
}

void func_801292B8(void *a)
{
    if (func_80051B70(a, 0xC, 0x2B) == 0) {
        func_800517F8(a);
    }
}

void func_801292F4(void *arg0) {
    M2C_FIELD(arg0, s8 *, 1) = 1;
}

void func_80129300(u8 *p)
{
    if (func_80051B70(p, 0xC, 0x58) == 0) {
        p[0xD] |= 4;
        (*(u8 **)(p + 0xC0))[0x3F] = 0x1E;
        p[0] = 1;
        *(s16 *)(p + 0x80) = 0x78;
        *(s16 *)(p + 0x82) = 0xF0;
        *(s16 *)(p + 0x84) = 0x1C0;
        *(s16 *)(p + 0x86) = 0x1C0;
        func_800517F8(p);
    }
}

void func_80129374(void) {
    func_8007778C();
}

void func_80129394(void *arg0) {
    M2C_FIELD(arg0, s16 *, 0x2E) = 0x40C9;
    M2C_FIELD(arg0, s16 *, 0x32) = -0xEB8;
    M2C_FIELD(arg0, s16 *, 0x36) = 0x10ED;
}

void func_801293B0(u8 *p)
{
    if (func_80051B70(p, 0xC, 0x57) == 0) {
        if (D_800BF928 == 0xFF) {
            p[5] = 1;
            *(s16 *)(p + 0x2E) = 0x40C9;
            *(s16 *)(p + 0x32) = -0xEB8;
            *(s16 *)(p + 0x36) = 0x10ED;
        } else {
            p[5] = 0;
        }
        *(s16 *)(p + 0x54) = 0;
        *(s16 *)(p + 0x56) = 0;
        *(s16 *)(p + 0x58) = 0;
    }
}

void func_80129424(u8 *a)
{
    u8 *t = D_800E7E80;

    if (a[5] == 0) {
        func_8004BD64(a, 0, *(s32 *)(t + 0xDC), *(s32 *)(t + 0xD0), 0);
        if (D_800BFA30 & 1) {
            *(s16 *)(a + 0x2E) = 0x40C9;
            *(s16 *)(a + 0x32) = -0xEB8;
            *(s16 *)(a + 0x36) = 0x10ED;
            a[5]++;
        }
    }
    func_800517F8(a);
    func_8007778C(a);
}

void func_801294B4(s16 a0)
{
    u8 *r = func_80072DDC(0, 0, 3, 0x10);

    if (r) {
        *(void **)(r + 0x1C) = f_UpdateWaterTempleQuestPropActor;
        r[3] = 0x12;
        *(s16 *)(r + 0x60) = a0;
    }
}

typedef struct {
    u8 pad0[0x4E];
    s16 x4E;
    u8 pad50[6];
    s16 x56;
    u8 pad58[0x14];
    s16 x6C;
    s16 x6E;
    u8 pad70[0x4E];
    u8 xBE;
} T4814;
typedef struct {
    s16 pad0;
    s16 a;
    s16 pad4;
    s16 b;
    s16 pad8;
    s16 c;
} S13AE38;
void func_80129508(u8 *p)
{
    *(s32 *)(p + 0x3C) = D_800ECF80;
    func_80077B38(p, D_801486EC, 0xC);
    p[0xD] = 0;
    *(s16 *)(p + 0x5C) = 0;
    p[0xB] = 0x10;
    *(s16 *)(p + 0x5A) = 0;
    p[0x47] = 0;
}

void func_8012955C(void *arg0) {
    if (((s32) D_800BFA32 >> M2C_FIELD(arg0, s16 *, 0x60)) & 1) {
        M2C_FIELD(arg0, s8 *, 4) = 3;
        return;
    }
    M2C_FIELD(arg0, s8 *, 1) = 1;
    func_8004DAEC(arg0);
    M2C_FIELD(arg0, u16 *, 0x2E) = (u16) (M2C_FIELD(arg0, u16 *, 0x2E) + 0x20);
}

void func_801295C4(u8 *a) {
    if (func_80051B70(a, 0xC, 0x6B) == 0) {
        M2C_FIELD(a, s16 *, 0x56) = 0x4FC;
        M2C_FIELD(a, s16 *, 0x58) = 0;
        M2C_FIELD(a, s16 *, 0x54) = 0;
        M2C_FIELD(a, s16 *, 0x40) = 0;
        M2C_FIELD(a, s32 *, 0x10) = 0;
        if (*(u8 *)&D_800BF93E == 0xFF) {
            a[5] = 10;
            a[0xD] |= 4;
            M2C_FIELD(a, u8 **, 0xC0)[0x3F] = 0xF6;
        }
    }
}

u8 *func_8012963C(void *a0)
{
    u8 *r = func_80072DDC(a0, 1, 3, 0x10);

    if (r == 0) {
        return 0;
    }
    r[3] = 0x14;
    *(void **)(r + 0x1C) = f_UpdateWaterTempleQuestPropActor;
    *(void **)(r + 0x10) = a0;
    *(s16 *)(r + 0x36) = 0;
    *(s16 *)(r + 0x2E) = 0;
    *(s16 *)(r + 0x32) = 0x140;
    return r;
}

void func_801296A0(u8 *p)
{
    if (func_80051B70(p, 0xC, 0x6E) == 0) {
        *(s16 *)(p + 0x58) = 0;
        *(s16 *)(p + 0x56) = 0;
        *(s16 *)(p + 0x54) = 0;
    }
}

void func_801296E0(void *arg0) {
    if (D_800BFA3A == 0xB) {
        M2C_FIELD(arg0, s8 *, 4) = 3;
        return;
    }
    M2C_FIELD(arg0, s8 *, 1) = 1;
    func_800517F8();
}

void func_80129720(u8 *a)
{
    if (func_80051B70(a, 0xC, 0x6D) == 0) {
        *(s16 *)(a + 0x58) = 0;
        *(s16 *)(a + 0x56) = 0;
        *(s16 *)(a + 0x54) = 0;
    }
}

void func_80129760(void *arg0) {
    M2C_FIELD(arg0, s8 *, 1) = 1;
    func_800517F8();
}

u8 *func_80129784(void *a0)
{
    u8 *r = func_80072DDC(0, 0, 3, 0x10);

    if (r) {
        *(void **)(r + 0x1C) = f_UpdateWaterTempleQuestPropActor;
        *(void **)(r + 0x10) = a0;
        r[3] = 0x16;
        r[0x28] |= 0x80;
    }
    return r;
}

void func_801297E8(u8 *p)
{
    *(s32 *)(p + 0x3C) = D_800ECF80;
    func_80077B38(p, D_801486EC, 5);
    p[0xD] = 0;
    *(s16 *)(p + 0x5C) = 0;
    p[0xB] = 0x10;
    *(s16 *)(p + 0x5A) = 0;
    p[0x47] = 0;
}

#define F32(p, o) M2C_FIELD(p, s32 *, o)
#define FP(p, o) (*(u8 **)((u8 *)(p) + (o)))
void func_8012983C(u8 *a) {
    u8 *e;
    u8 *g;

    a[1] = 1;
    switch (a[5]) {
    case 0:
        g = D_800E7E80;
        func_8004BD64(a, 0, FP(g, 0xDC), FP(g, 0xD0), 0);
        break;
    case 1:
        e = FP(a, 0x10);
        F16(a, 0x2E) = (F32(FP(e, 0xD0), 0x2C) + F32(FP(e, 0xDC), 0x2C)) / 2;
        F16(a, 0x32) = (F32(FP(e, 0xD0), 0x30) + F32(FP(e, 0xDC), 0x30)) / 2 - 0x28;
        F16(a, 0x36) = (F32(FP(e, 0xD0), 0x34) + F32(FP(e, 0xDC), 0x34)) / 2;
        break;
    case 2:
        break;
    }
}

void func_80129924(u8 *p)
{
    if (D_800BFA42) {
        p[4] = 3;
    } else {
        func_80051B70(p, 0xC, 0x6C);
    }
}

void func_80129960(void *arg0) {
    M2C_FIELD(arg0, s8 *, 0xB) = 0x20;
    M2C_FIELD(arg0, M2C_UNK **, 0x18) = &func_8011973C;
    M2C_FIELD(arg0, s16 *, 0x2E) = 0x3053;
    M2C_FIELD(arg0, s16 *, 0x32) = -0x1116;
    M2C_FIELD(arg0, s16 *, 0x36) = 0x17C3;
    M2C_FIELD(arg0, s16 *, 0x84) = 0xC8;
    M2C_FIELD(arg0, s16 *, 0x80) = 0;
    M2C_FIELD(arg0, s16 *, 0x82) = 0;
    M2C_FIELD(arg0, s16 *, 0x86) = 0x190;
}

void func_801299A8(u8 *a)
{
    s32 s = a[5];
    a[1] = 1;
    switch (s) {
    case 0:
        if (D_800BFA3F & 0x80) {
            a[5] = s + 1;
            return;
        }
        if (*(s16 *)(a + 0x80) != 0) {
            *(s16 *)(a + 0x80) = (s16)(*(s16 *)(a + 0x80) - 1) - (*(s16 *)(a + 0x80) >> 2);
        }
        break;
    case 1:
        if (!(D_800BFA3F & 0x80)) {
            a[5] = 0;
            return;
        }
        if (*(s16 *)(a + 0x80) < 0x100) {
            *(s16 *)(a + 0x80) = (s16)(*(s16 *)(a + 0x80) + 1) + ((0x100 - *(s16 *)(a + 0x80)) >> 2);
        }
        break;
    }
}

void func_80129A5C(u8 *a)
{
    u8 *g = (u8 *)&D_800BF870;

    if (g[0xB2] != 0xFF) {
        return;
    }
    switch (a[5]) {
    case 0:
        if (g[0x1E0] >= 0x1E) {
            a[5] = 1;
            func_80074590(0x1A, 0x1B, 0);
        }
        break;
    case 1:
        *(s16 *)(*(u8 **)(a + 0xC4) + 8) -= 0x40;
        if (*(s16 *)(*(u8 **)(a + 0xC4) + 8) < -0x6FF) {
            a[5]++;
            g[0x1E0] = 0x1F;
        }
        break;
    case 2:
        break;
    }
    a[1] = 1;
    func_800517F8(a);
}

void func_80129B40(void *arg0) {
    M2C_FIELD(arg0, s8 *, 0) = 1;
    M2C_FIELD(arg0, s16 *, 0x80) = 0x40;
    M2C_FIELD(arg0, s16 *, 0x82) = 0x80;
    M2C_FIELD(arg0, s16 *, 0x84) = 0x190;
    M2C_FIELD(arg0, s16 *, 0x86) = 0x320;
}

void func_80129B6C(void *arg0) {
    if (D_800BF8E3 == 0xFF) {
        M2C_FIELD(arg0, s8 *, 4) = 3;
        return;
    }
    M2C_FIELD(arg0, s8 *, 1) = 1;
    func_80077EBC();
}

extern s16 D_1F800164_6889_91dd;
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
extern s32 D_1F80008C_f832;
#define T2_lddp(r0) __asm__ volatile("mtc2 %0, $8" : : "r"(r0))
#define T2_ldrgb(r0) __asm__ volatile("mtc2 %0, $6" : : "r"(r0))
#define T2_dpcs() __asm__ volatile("nop; nop; .word 0x4A780010")
#define T2_strgb(r0) __asm__ volatile("swc2 $22, 0( %0 )" : : "r"(r0) : "memory")
u32 *func_80129BAC(u32 *f, u32 *ot, s32 n, s32 dp)
{
    s32 rgb;
    T2PolyGT3 *p = D_800BF544;
    s32 *otz = (s32 *)0x1F800004;
    u32 c;
    u32 mode;
    s32 b;
    s32 d0, d1, d2;
    u32 *o;

    rgb = 0x34808080;
    T2_ldrgb(&rgb);
    while (n-- != 0) {
        T2_ldv3t(f);
        p->rgb0 = f[0];
        T2_rtpt();
        p->uv0 = f[2];
        p->uv1 = f[3];
        c = f[1];
        T2_stflg((s32 *)0x1F800000);
        if (*(s32 *)0x1F800000 >= 0) {
            T2_nclip();
            p->rgb1 = c & 0xF0F0F0;
            T2_stopz((s32 *)0x1F800000);
            if (*(s32 *)0x1F800000 > 0) {
                T2_stsxy3_gt3(p);
                if ((p->x0 < 320 || p->x1 < 320 || p->x2 < 320) && (p->y0 < 240 || p->y1 < 240 || p->y2 < 240)) {
                    __asm__ volatile("nop");
                    p->rgb2 = (c << 4) & 0xF0F0F0;
                    T2_stsz1(&D_1F800084);
                    T2_stsz2(&D_1F800088);
                    T2_stsz3(&D_1F80008C_f832);
                    mode = (c >> 24) & 3;
                    switch (mode) {
                    case 1:
                    case 3:
                        if (D_1F800084 > D_1F800088) {
                            b = D_1F80008C_f832;
                            if (b < D_1F800084) {
                                b = D_1F800084;
                            }
                            *otz = b >> 2;
                        } else {
                            b = D_1F80008C_f832;
                            if (b < D_1F800088) {
                                b = D_1F800088;
                            }
                            *otz = b >> 2;
                        }
                        break;
                    case 2:
                        if (D_1F800084 < D_1F800088) {
                            b = D_1F80008C_f832;
                            if (D_1F800084 < b) {
                                b = D_1F800084;
                            }
                            *otz = b >> 2;
                        } else {
                            b = D_1F80008C_f832;
                            if (D_1F800088 < b) {
                                b = D_1F800088;
                            }
                            *otz = b >> 2;
                        }
                        break;
                    default:
                        T2_avsz3();
                        T2_stotz(otz);
                        break;
                    }
                    b = *otz >> 10;
                    *otz = (*otz >> b) + (b << 9);
                    if ((u32)(*otz - 4) >= 0x7FC) {
                        *otz = -1;
                    }
                    if (*otz >= 0) {
                        p->uv2 = ((u16 *)f)[0x11];
                        if (dp != 0) {
                            d0 = d1 = d2 = dp;
                        } else {
                            d0 = func_80078240(((s16 *)f)[8] - D_1F800160_71b4, ((s16 *)f)[9] - D_1F800162, ((s16 *)f)[10] - D_1F800164_6889_91dd) * 2;
                            d1 = func_80078240(((s16 *)f)[12] - D_1F800160_71b4, ((s16 *)f)[13] - D_1F800162, ((s16 *)f)[11] - D_1F800164_6889_91dd) * 2;
                            d2 = func_80078240(((s16 *)f)[14] - D_1F800160_71b4, ((s16 *)f)[15] - D_1F800162, ((s16 *)f)[16] - D_1F800164_6889_91dd) * 2;
                            if (d0 > 0x4000) {
                                d0 = 0x4000;
                            }
                            if (d1 > 0x4000) {
                                d1 = 0x4000;
                            }
                            if (d2 > 0x4000) {
                                d2 = 0x4000;
                            }
                        }
                        T2_lddp(d0);
                        T2_ldrgb(p->rgb0);
                        T2_dpcs();
                        T2_strgb(&p->rgb0);
                        T2_lddp(d1);
                        T2_ldrgb(p->rgb1);
                        T2_dpcs();
                        T2_strgb(&p->rgb1);
                        T2_lddp(d2);
                        T2_ldrgb(p->rgb2);
                        T2_dpcs();
                        T2_strgb(&p->rgb2);
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
extern void *D_800BF544_ff0c;
extern void *D_800BF544_ff0c;
extern void *D_800BF544_ff0c;
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
u32 *func_8012A06C(u32 *f, u32 *ot, s32 n, s32 dp)
{
    s32 rgb;
    T2PolyGT4 *p = D_800BF544_ff0c;
    s32 *otz = (s32 *)0x1F800004;
    u32 c;
    u32 w;
    u32 mode;
    s32 a, b, v;
    s32 d0, d1, d2, d3;
    u32 *o;

    rgb = 0x3C808080;
    T2_ldrgb(&rgb);
    while (n-- != 0) {
        T2_ldv3p(f);
        w = f[0];
        p->rgb0 = w & 0xFFF0F0F0;
        T2_rtpt();
        p->rgb1 = (w << 4) & 0xF0F0F0;
        c = f[1];
        T2_stflg((s32 *)0x1F800000);
        if (*(s32 *)0x1F800000 >= 0) {
            T2_nclip();
            p->uv0 = f[2];
            T2_stopz((s32 *)0x1F800000);
            if (*(s32 *)0x1F800000 > 0) {
                T2_stsxy3_gt4(p);
                T2_ldv1p(f);
                p->rgb2 = c & 0xF0F0F0;
                T2_rtps();
                p->rgb3 = (c << 4) & 0xF0F0F0;
                p->uv1 = f[3];
                T2_stflg((s32 *)0x1F800000);
                if (*(s32 *)0x1F800000 >= 0) {
                    T2_stsxy(&p->x3);
                    if ((p->x0 < 320 || p->x1 < 320 || p->x2 < 320 || p->x3 < 320) &&
                        (p->y0 < 240 || p->y1 < 240 || p->y2 < 240 || p->y3 < 240)) {
                        mode = c >> 24;
                        T2_stsz0(&D_1F800084);
                        T2_stsz1(&D_1F800088);
                        T2_stsz2(&D_1F80008C_f832);
                        T2_stsz3(&D_1F800090_3460);
                        switch (mode & 3) {
                        case 1:
                        case 3:
                            {
                                s32 *p4 = &D_1F800084;
                                {
                                    s32 *p8 = &D_1F800088;
                                    a = (*p8);
                                }
                                if (a < *p4) {
                                    a = *p4;
                                }
                            }
                            b = D_1F800090_3460;
                            if (b < D_1F80008C_f832) {
                                b = D_1F80008C_f832;
                            }
                            if (b < a) {
                                b = a;
                            }
                            *otz = b >> 2;
                            break;
                        case 2:
                            {
                                s32 *p4 = &D_1F800084;
                                a = D_1F800088;
                                if (*p4 < a) {
                                    a = *p4;
                                }
                            }
                            b = D_1F800090_3460;
                            if (D_1F80008C_f832 < b) {
                                b = D_1F80008C_f832;
                            }
                            if (a < b) {
                                b = a;
                            }
                            *otz = b >> 2;
                            break;
                        default:
                            T2_avsz4();
                            T2_stotz(otz);
                            break;
                        }
                        b = *otz >> 10;
                        *otz = (*otz >> b) + (b << 9);
                        if ((u32)(*otz - 4) >= 0x7FC) {
                            *otz = -1;
                        }
                        if (*otz >= 0) {
                            v = f[4];
                            p->uv2 = v;
                            p->uv3 = (u32)v >> 16;
                            if (dp != 0) {
                                d0 = d1 = d2 = d3 = dp;
                            } else {
                                d0 = func_80078240(((s16 *)f)[10] - D_1F800160_71b4, ((s16 *)f)[11] - D_1F800162, ((s16 *)f)[12] - D_1F800164_d75f) * 2;
                                d1 = func_80078240(((s16 *)f)[14] - D_1F800160_71b4, ((s16 *)f)[15] - D_1F800162, ((s16 *)f)[13] - D_1F800164_d75f) * 2;
                                d2 = func_80078240(((s16 *)f)[16] - D_1F800160_71b4, ((s16 *)f)[17] - D_1F800162, ((s16 *)f)[18] - D_1F800164_d75f) * 2;
                                d3 = func_80078240(((s16 *)f)[20] - D_1F800160_71b4, ((s16 *)f)[21] - D_1F800162, ((s16 *)f)[19] - D_1F800164_d75f) * 2;
                                if (d0 > 0x4000) {
                                    d0 = 0x4000;
                                }
                                if (d1 > 0x4000) {
                                    d1 = 0x4000;
                                }
                                if (d2 > 0x4000) {
                                    d2 = 0x4000;
                                }
                                if (d3 > 0x4000) {
                                    d3 = 0x4000;
                                }
                            }
                            T2_lddp(d0);
                            T2_ldrgb(p->rgb0);
                            T2_dpcs();
                            T2_strgb(&p->rgb0);
                            T2_lddp(d1);
                            T2_ldrgb(p->rgb1);
                            T2_dpcs();
                            T2_strgb(&p->rgb1);
                            T2_lddp(d2);
                            T2_ldrgb(p->rgb2);
                            T2_dpcs();
                            T2_strgb(&p->rgb2);
                            T2_lddp(d3);
                            T2_ldrgb(p->rgb3);
                            T2_dpcs();
                            T2_strgb(&p->rgb3);
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
    next:
        f += 11;
    }
    D_800BF544_ff0c = p;
    return f;
}

typedef struct {
    s16 x, y, w, h;
} RECT16;
void func_8012A638(RECT16 *a) {
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

extern u8 D_800BF918;
extern u8 D_80145A6C;
extern u8 D_80145A6D;
extern u16 D_80145A6E;
extern Mat D_1F8000F8;
u32 *func_80140FBC();
void func_8012A7CC(u8 *a)
{
    u16 *i;
    u16 *end;
    u32 *tbl;
    u32 *ot;
    u32 *m;
    u32 w;
    u32 *ot_f;
    u32 *m_f;
    u32 w_f;

    if (a[6] == 0) {
        return;
    }
    gte_SetRotMatrix(&D_1F8000F8);
    gte_SetTransMatrix(&D_1F8000F8);
    i = (u16 *)(a + 0x10);
    if (D_800BF873) {
        end = (u16 *)(a + 0x10 + a[6] * 2);
        tbl = *(u32 **)(a + 0xC);
        ot = D_800ED8C8;
        gte_ldfcdir(0, 0, 0);
        for (; i < end; i++) {
            m = tbl + *i;
            w = *m;
            func_8012A06C(func_80129BAC(m + 1, ot, w & 0xFFFF, 0), ot, w >> 16, 0);
        }
    } else {
        end = (u16 *)(a + 0x10 + a[6] * 2);
        tbl = *(u32 **)(a + 0xC);
        ot_f = D_800ED8C8;
        for (; i < end; i++) {
            m_f = tbl + *i;
            w_f = *m_f;
            m_f = func_80140FBC(m_f + 1, ot_f, w_f & 0xFF);
            w_f >>= 16;
            f_UpdateWaterTempleRaftNpcActor(m_f, ot_f, w_f & 0xFF);
        }
    }
    D_80145A6C += 0x40;
    if (D_80145A6C >= 0xC0) {
        D_80145A6C = 0;
        D_80145A6D += 0x40;
        if (D_80145A6D >= 0xC0) {
            D_80145A6D = 0;
        }
    }
    D_80145A6E = D_80145A6C | (D_80145A6D << 8);
}

extern s16 D_1F800160_d288_1b66;
extern s16 *D_1F80028C;
void func_8012A9DC(u32 *a0, void *a1)
{
    u32 *s1;
    s32 s0;
    u32 w;
    s16 *o;

    s1 = a0;
    a0 += 4;

    if (D_800BF873) {
        o = (s16 *)D_1F80028C;
        { s32 x = o[0x17]; s32 y = o[0x19]; s32 z = o[0x1B]; s0 = func_80078240(x - D_1F800160_d288_1b66, y - D_1F800162, z - D_1F800164_6889_91dd) << 1; }
        gte_ldfcdir(0, 0, 0);
        w = *s1;
        func_8012A06C(func_80129BAC(a0, a1, w & 0xFFFF, s0), a1, w >> 16, s0);
    } else {
        w = *s1;
        f_UpdateWaterTempleRaftNpcActor(func_80140FBC(a0, a1, w & 0xFFFF), a1, w >> 16);
    }
}

extern S8 D_80145A70[];
void func_8012AADC(void)
{
    u32 i;

    if (D_800BF873) {
        for (i = 0; i < 6; i++) {
            func_8012A638(&D_80145A70[i]);
        }
    }
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
extern u16 *D_800ECFA4_f863;
extern u16 *D_800ECF78;
void func_8012AEC0(u8 *a, s32 *p0, s32 *p1, s32 *p2);
void func_8012AB30(u8 *a)
{
    T2Pt32 v0, v1, v2;
    T2CamD0 *c;
    u16 *tb;
    u16 x;
    s32 k;
    s32 ang, r, dx, dz;
    u16 t;

    if (D_800BF871 < 9) {
        k = 0;
    } else if (D_800BF871 < 18) {
        k = 1;
    } else {
        k = 2;
    }
    switch (k) {
    case 0:
        *(u16 **)(a + 0xC) = D_800ECF78;
        break;
    case 1:
        *(u16 **)(a + 0xC) = D_800ECF78;
        break;
    case 2:
        *(u16 **)(a + 0xC) = D_800ECF78;
        break;
    }
    c = &D_1F8000D0_3bb0;
    tb = *(u16 **)(a + 0xC);
    x = tb[0];
    *(u16 *)(a + 8) = x;
    x = tb[1];
    MEMBER_AT(u16, a, 0xA) = x;
    D_800A3F90 = 0x3E80;
    t = c->ry;
    D_800A3F94 = 0x1C7;
    ang = (-(s16)t - D_800A3F94) & 0xFFF;
    v0.vx = c->x;
    v0.vy = c->y;
    r = func_80083E80(ang);
    v1.vx = v0.vx + ((r * D_800A3F90) >> 12);
    v1.vy = v0.vy + ((func_80083F50(ang) * D_800A3F90) >> 12);
    ang = (D_800A3F94 - (s16)c->ry) & 0xFFF;
    v2.vx = v0.vx + ((func_80083E80(ang) * D_800A3F90) >> 12);
    v2.vy = v0.vy + ((func_80083F50(ang) * D_800A3F90) >> 12);
    v0.vx -= (func_80083E80(-(s16)c->ry) * 1600) >> 12;
    v0.vy -= (func_80083F50(-(s16)c->ry) * 1600) >> 12;
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
    func_8012AEC0(a, &v0, &v1, &v2);
}

#define GH(p, o) (*(s16 *)((u8 *)(p) + (o)))
typedef struct { u8 pad[0x10]; u16 cells[1]; } GridCellList;
static inline void tri_span_8012AEC0(u8 *a, s32 y, s32 l, s32 r) {
    s32 x;
    s16 *p;
    s32 off;

    if (y >= 0 && y < GH(a, 0xA)) {
        if (r >= GH(a, 8)) r = GH(a, 8) - 1;
        x = l;
        if (x < 0) x = 0;
        p = *(s16 **)(a + 0xC);
        p += 2;
        off = x * GH(a, 0xA) + y;
        while (p += off, x <= r) {
            if (*p != -1) {
                u8 n = a[6];
                if (n < 0xFE) {
                    a[6] = n + 1;
                    ((GridCellList *)a)->cells[n] = *p;
                }
            }
            off = GH(a, 0xA);
            x++;
        }
    }
}
void func_8012AEC0(u8 *a, s32 *p0, s32 *p1, s32 *p2) {
    s32 x0 = p0[0], y0 = p0[1];
    s32 x1 = p1[0], y1 = p1[1];
    s32 x2 = p2[0], y2 = p2[1];
    s32 t, dx1, dx2, dy1, dy2;
    s32 xl, xr, y;
    s32 sl1, sl2, sl3;

    if (y1 == y0 && y1 == y2) return;
    if (y1 < y0) { t = x0; x0 = x1; x1 = t; t = y0; y0 = y1; y1 = t; }
    if (y2 < y0) { t = x0; x0 = x2; x2 = t; t = y0; y0 = y2; y2 = t; }
    if (y2 < y1) { t = x1; x1 = x2; x2 = t; t = y1; y1 = y2; y2 = t; }
    dx1 = x1 - x0;
    dx2 = x2 - x0;
    dy1 = y1 - y0;
    dy2 = y2 - y0;
    if (y1 == y0) {
        if (x0 < x1) { xl = x0 << 16; xr = x1 << 16; }
        else { xl = x1 << 16; xr = x0 << 16; }
        sl1 = 0;
    } else {
        xl = xr = x0 << 16;
        sl1 = (dx1 << 16) / dy1;
    }
    xr += 0x10000;
    if (y1 == y2) sl2 = 0;
    else sl2 = ((x2 - x1) << 16) / (y2 - y1);
    sl3 = (dx2 << 16) / dy2;
    if (-dy2 * dx1 + dx2 * dy1 > 0) {
        for (y = y0; y < y1; y++) { tri_span_8012AEC0(a, y, xl >> 16, xr >> 16); xl += sl1; xr += sl3; }
        for (; y <= y2; y++) { tri_span_8012AEC0(a, y, xl >> 16, xr >> 16); xl += sl2; xr += sl3; }
    } else {
        for (y = y0; y < y1; y++) { tri_span_8012AEC0(a, y, xl >> 16, xr >> 16); xr += sl1; xl += sl3; }
        for (; y <= y2; y++) { tri_span_8012AEC0(a, y, xl >> 16, xr >> 16); xl += sl3; xr += sl2; }
    }
}

void func_8012B3E8(u8 *a)
{
    u16 *p = D_800ECF78;
    u16 t;

    *(u16 **)(a + 0xC) = p;
    *(u16 *)(a + 8) = p[0];
    t = p[1];
    a[7] = 0;
    *(u16 *)(a + 0xA) = t;
}

extern u8 D_8014184C[];
extern u8 D_800BF9F3;
extern u8 D_80149D08[];
extern u8 D_800BF8F4;
extern u8 D_800BFA47;
void func_8012B414(u8 *a)
{
    u8 *g;
    s16 r;

    switch (a[4]) {
    case 0:
        g = D_800ECF58;
        if (func_800519E0(a, 0xF, *(s32 *)(g + 0x90), D_8014184C) != 0) {
            break;
        }
        *(s32 *)(a + 0x3C) = *(s32 *)(g + 0x94);
        a[0xB] = 0;
        a[4]++;
        if (a[3] == 0) {
            a[0x5E] = D_800BF9F3 & 4;
        } else {
            a[0x5E] = (D_800BF9F3 >> 4) & 4;
        }
        if (a[0x5E] == 0) {
            func_80077E20(a, 0x40, 0x80, 0x8A);
        } else {
            func_80077E20(a, 0x8A, 0x60, 0x50);
        }
        *(s16 *)(a + 0x56) = 0x800;
        *(s16 *)(a + 0xBC) = 0x800;
        *(s16 *)(a + 0xBA) = 0x800;
        *(s16 *)(a + 0xB8) = 0x800;
        func_80077C40(a, D_80149D08, 1);
        *(s16 *)(a + 0x54) = 0;
        *(s16 *)(a + 0x58) = 0;
        *(s16 *)(a + 0x40) = a[3] << 4;
        func_800518FC(a);
        if (a[3] == 0 && D_800BF8F4 != 0xFF) {
            a[5] = 1;
        }
        *(s16 *)(a + 0x62) = *(s16 *)(a + 0x32);
        break;
    case 1:
        a[1] = 1;
        func_80077E7C(a);
        r = func_80076D68(a);
        *(s16 *)(a + 0x60) = r;
        switch (a[5]) {
        case 0:
            if (D_800BFA4E == 10) {
                a[5] = 2;
                a[6] = 0;
                *(s16 *)(a + 0x40) = func_8009A450() & 0xF;
                break;
            }
            switch (a[6]) {
            case 0:
                if (--*(s16 *)(a + 0x40) > 0) {
                    break;
                }
                if (func_8009A450() & 1) {
                    func_80077CFC(a, D_80149D08, 2, 2);
                    *(s16 *)(a + 0x40) = ((func_8009A450() >> 3) & 3) + 1;
                    a[6]++;
                } else {
                    *(s16 *)(a + 0x40) = func_8009A450() & 0xFF;
                }
                break;
            case 1:
                if (r == 1) {
                    if (--*(s16 *)(a + 0x40) > 0) {
                        break;
                    }
                    func_80077CFC(a, D_80149D08, 1, 2);
                    *(s16 *)(a + 0x40) = func_8009A450() & 0xFF;
                    a[6] = 0;
                }
                break;
            }
            break;
        case 1:
            if (D_1F800137 == 0) {
                D_800BFA47 = 0x81;
                func_80040C00(0x40);
                a[5] = 0;
            }
            break;
        case 2:
            func_80076D68(a);
            switch (a[6]) {
            case 0:
                if (--*(s16 *)(a + 0x40) > 0) {
                    break;
                }
                func_80077CFC(a, D_80149D08, 0, 4);
                a[6]++;
                break;
            case 1:
                *(s16 *)(a + 0x32) -= 6;
                if (*(s16 *)(a + 0x32) <= *(s16 *)(a + 0x62) - 0x40) {
                    *(s16 *)(a + 0x32) = *(s16 *)(a + 0x62) - 0x40;
                }
                if (D_800BFA4E == 0xF) {
                    *(s16 *)(a + 0x40) = func_8009A450() & 0xF;
                    a[6]++;
                }
                break;
            case 2:
                if (--*(s16 *)(a + 0x40) > 0) {
                    break;
                }
                a[6]++;
                break;
            case 3:
                *(s16 *)(a + 0x32) += 6;
                if (*(s16 *)(a + 0x32) >= *(s16 *)(a + 0x62)) {
                    *(s16 *)(a + 0x32) = *(s16 *)(a + 0x62);
                    a[5] = 0;
                    a[6] = 0;
                    func_80077CFC(a, D_80149D08, 1, 8);
                }
                break;
            }
            break;
        }
        func_800518FC(a);
        break;
    case 2:
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

typedef struct { s16 x0; s16 id; u8 k; u8 p5; s16 v6; s16 v8; } Entry10;
extern Entry10 D_80145AA0[];
void f_UpdateLastEvilPigAccessActor();
u8 *func_8012B89C(u8 *a, s32 i)
{
    Entry10 *t = D_80145AA0;
    Entry10 *e = &t[i];
    u8 *p;

    if (func_8004D7EC(e->id, 1)) {
        return NULL;
    }
    p = func_80072DDC(a, 2, 2, 8);
    if (p != NULL) {
        *(void **)(p + 0x1C) = f_UpdateLastEvilPigAccessActor;
        p[0x5E] = 0;
        *(s16 *)(p + 0xE) = e->id;
        p[3] = e->k;
        *(s16 *)(p + 0x68) = e->v6;
        *(s16 *)(p + 0x60) = e->v8;
        if (*(s16 *)(p + 0x68) == 0) {
            *(s16 *)(p + 0x62) = 1;
        } else {
            *(s16 *)(p + 0x62) = 4;
        }
        *(s16 *)(p + 0x64) = 2;
        p[0x2A] = 0;
        return p;
    }
    return NULL;
}

extern u8 D_800BFAD1;
static inline void EvilTalk(u8 *a)
{
    u8 *g = D_800BF808;

    if (g[0xE] != 0 && g[0xF] == H(a, 0x6A)) {
        if (a[0x28] & 0x80) {
            a[1] = 1;
            func_80077E7C(a);
            func_800517F8(a);
        }
    } else if (!(a[0x28] & 0x80) && func_8007778C(a) != 0) {
        func_800517F8(a);
    }
}
void f_UpdateLastEvilPigAccessActor(u8 *a)
{
    switch (a[4]) {
    case 0:
        if (func_80040410(a, a[3]) != 0) {
            H(a, 0x80) = 0x40;
            H(a, 0x82) = 0x80;
            a[4] = 1;
            a[0] = 1;
            H(a, 0x84) = 0x96;
            H(a, 0x86) = 0x96;
            a[0x46] = 0;
            a[0x29] = 0;
            a[0x2B] = 0;
            a[0x5F] = 0;
            a[0x5E] = 1;
        }
        break;
    case 1:
        switch (a[5]) {
        case 0:
            func_8003FD10(a);
            break;
        case 1:
            func_8003FED8(a);
            break;
        case 2:
            func_8003FFCC(a);
            break;
        case 3:
            func_8004022C(a);
            break;
        case 4:
            func_80040390(a);
            break;
        }
        EvilTalk(a);
        a[0x29] = 0;
        a[0x5F] = 0;
        break;
    case 2:
        switch (a[5]) {
        case 0:
            break;
        case 1:
            if (a[3] == 0 && D_800BFAD1 == 0) {
                func_80040B48(0x38);
            }
            break;
        case 2:
            func_8003FE00(a);
            break;
        case 3:
            func_8003FED8(a);
            break;
        case 4:
            break;
        }
        EvilTalk(a);
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

extern u8 D_80145AAC[];
extern u8 D_8001B4DC[];
extern u8 D_800A3D18[];
extern u8 D_800BFA46;
extern u8 D_80145B34[];
extern u8 D_800A3CF0[];
extern u8 D_80145B24[];
void func_8012BC44(u8 *a)
{
    u8 *g;

    switch (a[4]) {
    case 0:
        g = D_800ECF58;
        if (func_800519E0(a, 0xF, *(s32 *)(g + 0x3C), D_80145AAC) != 0) {
            break;
        }
        *(s32 *)(a + 0x3C) = *(s32 *)(g + 0x8C);
        func_80040CDC(a, D_8001B4DC, D_800A3D18);
        a[0x7B] = 5;
        *(s16 *)(a + 0xB8) = 0x800;
        a[0] = 9;
        *(s16 *)(a + 0x80) = 0x5A;
        *(s16 *)(a + 0x82) = 0xB4;
        *(s16 *)(a + 0x84) = 0x50;
        *(s16 *)(a + 0x86) = 0x90;
        *(s16 *)(a + 0xBA) = 0x800;
        *(s16 *)(a + 0xBC) = 0x800;
        if (!(D_800BFA46 & 0x40)) {
            a[3] = 0;
            *(s16 *)(a + 0x56) = 0x800;
            func_80041718(a, 8, 0);
        } else {
            *(s16 *)(a + 0x56) = 0x400;
            *(s16 *)(a + 0x2E) = 0x4661;
            *(s16 *)(a + 0x32) = -0x1B34;
            *(s16 *)(a + 0x36) = 0x10D0;
            func_80041718(a, 5, 0);
            a[3] = 1;
        }
        a[0x2B] = 0;
        a[0x29] = 0;
        a[4]++;
        break;
    case 1:
        switch (a[3]) {
        case 0:
            switch (a[5]) {
            case 0:
                func_8007778C(a);
                if (D_800BFA46 & 0x40) {
                    func_80040D68(a, D_80145B34);
                    a[0x70] = 2;
                    a[5]++;
                }
                break;
            case 1:
                a[1] = 1;
                func_80077E7C(a);
                func_80041098(a);
                if (a[0x70] == 0xFF) {
                    a[3] = 1;
                    a[5] = 0;
                }
                break;
            }
            func_8004190C(a);
            break;
        case 1:
            switch (a[5]) {
            case 0:
                func_8007778C(a);
                if (a[0x2B] == 3) {
                    func_80042354(1, 3);
                    func_80040D68(a, D_800A3CF0);
                    a[0x70] = 2;
                    a[6] = 0;
                    a[5] = 1;
                }
                break;
            case 1:
                a[1] = 1;
                func_80077E7C(a);
                func_80041098(a);
                if (a[0x70] == 0xFF) {
                    switch (a[6]) {
                    case 0:
                        a[0x7A] = 0x13;
                        func_80040D68(a, D_80145B24);
                        a[0x70] = 2;
                        a[6] = 1;
                        break;
                    case 1:
                        a[5] = 0;
                        break;
                    }
                }
                break;
            }
            func_8004190C(a);
            break;
        }
        if (a[1] != 0) {
            func_800518FC(a);
        }
        a[0x2B] = 0;
        break;
    case 2:
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

s32 func_8012BF5C(u8 *a)
{
    s32 s = a[5];

    switch (s) {
    case 0:
        func_8007778C(a);
        if (D_800BFA46 & 0x40) {
            func_80040D68(a, D_80145B34);
            a[0x70] = 2;
            a[5]++;
        }
        break;
    case 1:
        a[1] = 1;
        func_80077E7C(a);
        func_80041098(a);
        if (a[0x70] == 0xFF) {
            a[3] = 1;
            a[5] = 0;
        }
        break;
    }
    return func_8004190C(a);
}

void func_8012C018(u8 *a) {
    switch (a[5]) {
    case 0:
        func_8007778C(a);
        if (a[0x2B] == 3) {
            func_80042354(1, 3);
            func_80040D68(a, D_800A3CF0);
            a[0x70] = 2;
            a[6] = 0;
            a[5] = 1;
        }
        break;
    case 1:
        a[1] = 1;
        func_80077E7C(a);
        func_80041098(a);
        if (a[0x70] == 0xFF) {
            switch (a[6]) {
            case 0:
                a[0x7A] = 0x13;
                func_80040D68(a, D_80145B24);
                a[0x70] = 2;
                a[6] = 1;
                break;
            case 1:
                a[5] = 0;
                break;
            }
        }
        break;
    }
    func_8004190C(a);
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8012C118);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8012C3A4);

extern u8 D_800BFA48;
extern u8 D_80145E80[];
static inline s32 nest_step(u8 *a)
{
    switch (a[6]) {
    case 0:
        if (D_800BFA4E >= 0x1E) {
            a[6] = 1;
        }
        break;
    case 1:
        a[6] = 2;
        func_80040CDC(a, D_8001B4DC, D_80145E80);
        a[0x70] = 1;
        break;
    case 2:
        func_80041098(a);
        if (a[0x70] == 0xFF) {
            a[6] = 0;
            func_80042310();
            return 1;
        }
        break;
    }
    return 0;
}
void f_UpdateNishikiBirdNestActor(u8 *a)
{
    u8 *g;
    u8 *st;

    switch (a[4]) {
    case 0:
        g = D_800ECF58;
        if (func_800519E0(a, 0xF, *(s32 *)(g + 0x3C), D_80145AAC) != 0) {
            break;
        }
        *(s32 *)(a + 0x3C) = *(s32 *)(g + 0x8C);
        a[0] = 9;
        *(s16 *)(a + 0x80) = 0x3C;
        *(s16 *)(a + 0x82) = 0x78;
        *(s16 *)(a + 0x84) = 0x50;
        *(s16 *)(a + 0x86) = 0x90;
        *(s16 *)(a + 0xB8) = 0x800;
        *(s16 *)(a + 0xBA) = 0x800;
        *(s16 *)(a + 0xBC) = 0x800;
        *(s16 *)(a + 0x54) = 0;
        *(s16 *)(a + 0x58) = 0;
        a[4]++;
        if (a[3] == 0) {
            st = (u8 *)&D_800BF870;
            if (st[0x1DE] >= 3) {
                a[5] = 2;
                *(s16 *)(a + 0x56) = 0xD00;
                func_80077C40(a, D_8001B4DC, 6);
            } else {
                a[5] = 0;
                if (st[1] == 0x10 || st[0x84] == 0xFF) {
                    *(s16 *)(a + 0x56) = 0xF00;
                } else {
                    *(s16 *)(a + 0x56) = 0x800;
                }
                func_80077C40(a, D_8001B4DC, 5);
            }
        } else {
            if (D_800BFA48 == 0) {
                func_80051B04(*(u8 **)(a + 0xEC), 0xF, 0xF);
                func_80051B04(*(u8 **)(a + 0xF0), 0xF, 0x10);
            } else if (D_800BFA48 == 1) {
                func_80051B04(*(u8 **)(a + 0xEC), 0xF, 0x13);
                func_80051B04(*(u8 **)(a + 0xF0), 0xF, 0x14);
            } else {
                func_80051B04(*(u8 **)(a + 0xEC), 0xF, 0x11);
                func_80051B04(*(u8 **)(a + 0xF0), 0xF, 0x12);
            }
            if (D_800BF938 != 0xFF) {
                a[5] = 0;
            } else {
                a[5] = 1;
                *(s16 *)(a + 0x2E) = 0x373D;
                *(s16 *)(a + 0x32) = -0x22D0;
                *(s16 *)(a + 0x36) = 0x1784;
            }
            *(s16 *)(a + 0x56) = 0x800;
            func_80077C40(a, D_8001B4DC, 5);
        }
        a[0x2B] = 0;
        a[0x29] = 0;
        break;
    case 1:
        switch (a[3]) {
        case 0:
            func_8012C118(a);
            break;
        case 1:
            switch (a[5]) {
            case 0:
                if (nest_step(a)) {
                    a[5]++;
                }
                break;
            case 1:
                func_8012C3A4(a);
                break;
            }
            break;
        }
        func_8007778C(a);
        func_8004190C(a);
        func_800518FC(a);
        a[0x2B] = 0;
        break;
    case 2:
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

s32 func_8012C8AC(void *arg0) {
    func_80128D1C(arg0);
    return 1;
}

s32 func_8012C8CC(u8 *p)
{
    if (D_800BFA48 == 0) {
        p[0x7A] = 1;
    } else if (D_800BFA48 == 1) {
        p[0x7A] = 2;
    } else {
        p[0x7A] = 3;
    }
    return 1;
}

extern s8 D_800E807E;
s32 func_8012C904(void) {
    D_800E807E = 1;
    return 1;
}

extern s8 D_800E807E;
s32 func_8012C918(void) {
    D_800E807E = 0;
    return 1;
}

void func_8012C928(u8 *a)
{
    s32 s;
    s32 r;

    switch (a[5]) {
    case 0:
        s = a[6];
        switch (s) {
        case 0:
            if (D_800BFA4E < 30) {
                r = 0;
                goto done;
            }
            a[6] = 1;
            r = 0;
            goto done;
        case 1:
            a[6] = 2;
            func_80040CDC(a, D_8001B4DC, D_80145E80);
            a[0x70] = s;
            break;
        case 2:
            func_80041098(a);
            if (a[0x70] != 0xFF) {
                r = 0;
                goto done;
            }
            a[6] = 0;
            func_80042310();
            r = 1;
            goto done;
        default:
            r = 0;
            goto done;
        }
        r = 0;
    done:
        if (r) {
            a[5]++;
        }
        break;
    case 1:
        func_8012C3A4(a);
        break;
    }
}

extern u8 D_8014159C[];
extern u8 D_80148790[];
extern u8 D_800A3D90_b2d8[];
extern u8 D_80145EF8[];
void func_8012D000(u8 *a);
void func_8012D144(u8 *a);
void func_8012CA40(u8 *a)
{
    u8 *g;
    u8 *st;

    switch (a[4]) {
    case 0:
        g = D_800ECF58;
        if (func_800519E0(a, 0xF, *(s32 *)(g + 0x6C), D_8014159C) != 0) {
            break;
        }
        *(s32 *)(a + 0x3C) = *(s32 *)(g + 0x38);
        func_80040CDC(a, D_80148790, D_800A3D90_b2d8);
        st = (u8 *)&D_800BF870;
        if (st[0xA5] == 0xFF) {
            func_80051B04(*(u8 **)(a + 0xC0), 0x1B, 0xF);
            func_80041718(a, 0, 0);
            a[0x5E] = 5;
        } else {
            func_80041718(a, 0xB, 0);
            if (st[0xA4] == 0xFF) {
                if (st[0x296] != 0) {
                    a[0x5E] = 4;
                } else {
                    a[0x5E] = 3;
                }
            } else if (st[0xA4] != 0) {
                a[0x5E] = 1;
            } else {
                a[0x5E] = 0;
            }
        }
        a[0] = 9;
        *(s16 *)(a + 0x80) = 0x8C;
        *(s16 *)(a + 0x82) = 0x118;
        *(s16 *)(a + 0x84) = 0x78;
        *(s16 *)(a + 0x86) = 0xF0;
        *(s16 *)(a + 0x56) = 0x6D2;
        a[0x2B] = 0;
        a[0x29] = 0;
        *(s16 *)(a + 0x54) = 0;
        *(s16 *)(a + 0x58) = 0;
        a[4]++;
        if (D_1F800207 == 0x27) {
            a[5] = 3;
            func_80040D68(a, D_80145EF8);
            a[0x70] = 1;
            a[0] = 2;
        }
        break;
    case 1:
        func_8007778C(a);
        func_80041098(a);
        func_8004190C(a);
        switch (a[5]) {
        case 0:
            func_8012CF20(a);
            break;
        case 1:
            func_8012D000(a);
            break;
        case 2:
            func_8012D060(a);
            break;
        case 3:
            func_8012D144(a);
            break;
        }
        a[0x2B] = 0;
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

extern s32 D_800ECF90;
void func_8012CCD4(u8 *a)
{
    u8 *p = *(u8 **)(a + 0x10);
    u8 *t;

    switch (a[4]) {
    case 0:
        if (func_80051B70(a, 0x1B, 0x10) != 0) {
            break;
        }
        *(s32 *)(a + 0x3C) = D_800ECF90;
        *(s16 *)(*(u8 **)(a + 0xC0) + 0) -= 0x2D;
        *(s16 *)(*(u8 **)(a + 0xC0) + 4) += 0x28;
        *(s16 *)(a + 0x54) = 0;
        *(s16 *)(a + 0x58) = 0;
        a[4]++;
        *(s16 *)(a + 0x56) = *(s16 *)(p + 0x56);
        *(s16 *)(a + 0x32) = *(s16 *)(p + 0x32);
        *(s16 *)(a + 0x40) = 0;
    case 1:
        switch (a[5]) {
        case 0:
            t = D_800E7E80;
            *(s16 *)(a + 0x2E) = *(s16 *)(*(u8 **)(t + 0xD0) + 0x2C);
            *(s16 *)(a + 0x36) = *(s16 *)(*(u8 * volatile *)(t + 0xD0) + 0x34);
            break;
        case 2:
            *(s16 *)(a + 0x56) += 0x70;
            if (*(s16 *)(a + 0x56) >= *(s16 *)(p + 0x56) + 0x1000) {
                *(s16 *)(a + 0x56) = *(s16 *)(p + 0x56) + 0x1000;
            }
            *(s16 *)(a + 0x40) += 1;
        case 1:
            *(s16 *)(a + 0x2E) = *(s16 *)(*(u8 **)(p + 0xDC) + 0x2C);
            *(s16 *)(a + 0x36) = *(s16 *)(*(u8 **)(p + 0xDC) + 0x34);
            *(s16 *)(a + 0x2E) -= (func_80083F50(*(s16 *)(p + 0x56)) * *(s16 *)(a + 0x40)) >> 12;
            *(s16 *)(a + 0x36) -= (-func_80083E80(*(s16 *)(p + 0x56)) * *(s16 *)(a + 0x40)) >> 12;
            break;
        case 3:
            a[4] = 3;
            return;
        }
        if (p[1] != 0) {
            a[1] = 1;
            func_800517F8(a);
        }
        break;
    case 2:
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8012CF20);

extern void *D_801461F0[];
void func_8012D000(u8 *a)
{
    if (a[0x71] == 0xFF) {
        func_80040D68(a, D_801461F0[a[0x5E]]);
        a[5] = 2;
        a[6] = 0;
        a[0x70] = 1;
    }
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8012D060);

void func_8012D144(u8 *a)
{
    if (a[0x71] == 0xFF) {
        if (a[6] == 0) {
            if (a[0x5E] == 5) {
                func_80041768(a, 0, 4);
            } else {
                func_80041768(a, 0xB, 4);
            }
            func_80074590(3, 0, 0);
        }
        a[5] = 0;
        a[0] = 9;
    }
}

s32 func_8012D1C4(void *arg0) {
    func_80051B04(M2C_FIELD(arg0, s32 *, 0xC0), 0x1B, 0xF);
    return 1;
}

extern u8 D_800BF914;
s32 func_8012D1EC(u8 *a)
{
    u8 *g;
    if (D_800BF914 == 0xFF) {
        return 0;
    }
    g = D_800BF808;
    *(s16 *)(a + 0x60) = g[3];
    switch (g[3]) {
    case 0x59 ... 0x5C:
    case 0x66 ... 0x68:
        a[0x5E] = 2;
        break;
    default:
        *(s16 *)(a + 0x60) = -1;
        return 0;
    }
    return 1;
}

extern u8 D_800BFB06;
s32 func_8012D270(u8 *a)
{
    if (D_800BFB06 != 0) {
        a[0x5E] = 4;
        return 3;
    }
    return 2;
}

s32 func_8012D298(u8 *p)
{
    if ((*(s32 *)(p + 0x14) = func_8012D398(p)) != 0) {
        func_8004D650(0x52, 1);
        return 1;
    }
    return 0;
}

s32 func_8012D2DC(void *arg0) {
    void *temp_v1;

    if (M2C_FIELD(arg0, s16 *, 0x72) == 0) {
        M2C_FIELD(arg0, u8 *, 6) = (u8) (M2C_FIELD(arg0, u8 *, 6) + 1);
    } else {
        temp_v1 = M2C_FIELD(arg0, void **, 0x14);
        M2C_FIELD(temp_v1, u8 *, 5) = (u8) (M2C_FIELD(temp_v1, u8 *, 5) + 1);
    }
    return 1;
}

s32 func_8012D320(void) {
    func_8004ED0C(0x52, 4);
    return 1;
}

s32 func_8012D344(void)
{
    u8 *e = D_800E7E80;

    if (e[0x29] == 0x81 && D_1F800162 >= -0x157C) {
        if (*(s16 *)(e + 0x17E) & 0x8200) {
            return 3;
        }
        return 2;
    }
    return 0;
}

void func_8012CCD4();
u8 *func_8012D398(void *a)
{
    u8 *r = func_80072DDC(a, 1, 3, 0x26);

    if (r != NULL) {
        *(void **)(r + 0x1C) = func_8012CCD4;
    }
    return r;
}

void func_8012D3D4(u8 *a)
{
    switch (a[4]) {
    case 0:
        if (func_80051B70(a, 0xC, 0x60) != 0) {
            break;
        }
        *(s16 *)(a + 0x80) = 0x7F;
        *(s16 *)(a + 0x82) = 0xFE;
        *(s16 *)(a + 0x84) = 0xBE;
        *(s16 *)(a + 0x86) = 0x114;
        a[0xB] = 0;
        a[0] = 1;
        a[0x29] = 0;
        a[0x2A] = 0x2B;
        a[4]++;
        break;
    case 2:
        switch (a[5]) {
        case 0:
        case 1:
            break;
        case 2:
            func_8012D560(a);
            a[4] = 3;
            return;
        case 3:
            *(s16 *)(a + 0x58) += 0x200;
            *(s16 *)(a + 0x32) += 0x20;
            if (func_8004766C(a) == 0) {
                return;
            }
            if (a[0x29] != 0 || func_80049250(a, 0, (s16)(*(u16 *)(a + 0x86) - *(u16 *)(a + 0x84)))) {
                func_8012D560(a);
                a[4] = 3;
                return;
            }
            break;
        }
    case 1:
        if (func_8007778C(a)) {
            func_800517F8(a);
        }
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

void func_8012D560(void *arg0) {
    s32 temp_s1;

    temp_s1 = arg0 + 0x2C;
    func_80027144(M2C_FIELD(M2C_FIELD(arg0, void **, 0xC0), s32 *, 0x40), temp_s1, 0x700, 0x18);
    func_80074590(0xC, 0, 0);
    M2C_FIELD(arg0, u16 *, 0x32) = (u16) (M2C_FIELD(arg0, u16 *, 0x32) + 0x64);
    func_80027144(M2C_FIELD(M2C_FIELD(arg0, void **, 0xC0), s32 *, 0x40), temp_s1, 0x800, -0x7FE8);
    func_80074590(0xC, 0, 0);
    if (func_801238D0(arg0, 5) != 0) {
        D_800BF870.pad1[0x1C7] += 1;
    }
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", f_UpdateRareCrabPickupActor);

void func_8012D8F4(void *arg0) {
    u16 temp_v0;
    u16 temp_v0_2;
    u8 temp_s1;

    func_8004766C();
    temp_s1 = M2C_FIELD(arg0, u8 *, 5);
    switch (temp_s1) {                              /* irregular */
    case 0:
        temp_v0 = M2C_FIELD(arg0, u16 *, 0x32) - 0xA;
        M2C_FIELD(arg0, u16 *, 0x32) = temp_v0;
        if (M2C_FIELD(arg0, s16 *, 0x64) >= (s16) temp_v0) {
            M2C_FIELD(arg0, u16 *, 0x32) = (u16) M2C_FIELD(arg0, s16 *, 0x64);
            M2C_FIELD(arg0, u8 *, 5) = 2U;
            return;
        }
        return;
    case 1:
        temp_v0_2 = M2C_FIELD(arg0, u16 *, 0x32) + 0xA;
        M2C_FIELD(arg0, u16 *, 0x32) = temp_v0_2;
        if ((s16) temp_v0_2 >= M2C_FIELD(arg0, s16 *, 0x64)) {
            M2C_FIELD(arg0, u16 *, 0x32) = (u16) M2C_FIELD(arg0, s16 *, 0x64);
            M2C_FIELD(arg0, u8 *, 5) = 2U;
            return;
        }
        if ((M2C_FIELD(arg0, u8 *, 0x29) != 0) || (func_80049250(arg0, 0, 0x1E) == temp_s1)) {
            M2C_FIELD(arg0, u8 *, 5) = 3U;
            return;
        }
        break;
    case 2:
        if (M2C_FIELD(arg0, s16 *, 0x4A) == 0) {
            func_8011B344(arg0 + 0x2C, -0xA, 0x14, 0x64);
        }
        M2C_FIELD(arg0, u16 *, 0x32) = (u16) ((u16) M2C_FIELD(arg0, s16 *, 0x64) + (func_80083E80(M2C_FIELD(arg0, s16 *, 0x4A)) >> 7));
        M2C_FIELD(arg0, s16 *, 0x4A) = (s16) (((u16) M2C_FIELD(arg0, s16 *, 0x4A) + 0x40) & 0xFFF);
        break;
    }
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8012DA44);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8012DC6C);

extern s16 D_1F8001BC;
extern s16 D_1F8001BE_s;
extern s16 D_1F8001C0;
extern u8 *D_1F8001E0;
extern u8 *D_1F8001E8;
s32 func_8012DE84(u8 *a, s16 y) {
    u8 *p;
    s8 h;
    s32 x;
    s32 z;

    if (D_800BF873 != 0) {
        return 0;
    }
    D_1F8001BC = H(a, 0x2E);
    D_1F8001BE_s = y;
    D_1F8001C0 = H(a, 0x36);
    do {
        func_80047778(a);
        func_80049968(a[0x2A]);
        if (func_80047CBC() == 0) {
            return 0;
        }
        if (!(*(u16 *)D_1F8001E0 & 0x4000)) {
            break;
        }
        a[0x2A] = *D_1F8001E0;
    } while (*(u16 *)D_1F8001E0 & 0x4000);
    if (func_8012DC6C() == 0) {
        return 0;
    }
    p = D_1F8001E8;
    {
        s16 hh = (s8)p[1];
        z = (s8)p[2];
        x = (s8)p[0];
        D_1F8001A0_b0de_1f9a = -func_80085690(z, x) & 0xFFF;
        D_1F8001A2_7766 = func_80085690(hh, (s16)func_80084080(x * x + z * z));
    }
    return 1;
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8012DFDC);

s32 func_8012E168(u8 *p)
{
    if (func_8012DFDC(p[0x2A]) == 0) {
        return 0;
    }
    return func_8007778C(p);
}

void func_8012DA44();
s32 func_8012E1A4(u8 *a) {
    u8 *g = (u8 *)&D_800BF870;
    u8 *e;

    if (g[0xC6] & 0x20) {
        goto fail;
    }
    if (g[0x164] != 0) {
        return 0;
    }
    e = func_80072DDC(a, 0, 2, 0x56);
    if (e == NULL) {
    fail:
        return 0;
    }
    M2C_FIELD(e, void **, 0x1C) = func_8012DA44;
    M2C_FIELD(e, s16 *, 0x2E) = M2C_FIELD(a, s16 *, 0x2E);
    M2C_FIELD(e, s16 *, 0x32) = M2C_FIELD(a, s16 *, 0x32);
    M2C_FIELD(e, s16 *, 0x36) = M2C_FIELD(a, s16 *, 0x36);
    e[0x2A] = a[0x2A];
    g[0x164] = 1;
    func_8003116C(0x30, e + 0x2C, -0xA);
    func_80074590(0x37, 0x20, 0);
    return 1;
}

extern s32 D_800ECFB0;
void func_8011B654();
void func_8012E274(u8 *a)
{
    u8 *c = a + 0x60;
    s32 unused[2];

    switch (a[4]) {
    case 0:
        a[0] = 1;
        if (a[3] != 0) {
            *(s16 *)(a + 0x80) = 0x19;
            *(s16 *)(a + 0x82) = 0x32;
            *(s16 *)(a + 0x86) = 0x32;
            a[0xB] = 0x20;
            *(void **)(a + 0x18) = func_8011B654;
            *(s16 *)(a + 0x84) = 0x19;
            a[0x60] = 0;
            *(s16 *)(a + 0x42) = 0x1E;
        } else {
            if (func_80051B70(a, 0x15, 3) != 0) {
                break;
            }
            *(s32 *)(a + 0x3C) = D_800ECFB0;
            *(s16 *)(*(u8 **)(a + 0xC0) + 0) -= 0x32;
            *(s16 *)(a + 0x80) = 0x32;
            *(s16 *)(a + 0x82) = 0x64;
            *(s16 *)(a + 0x84) = 0xF;
            *(s16 *)(a + 0x86) = 0x37;
        }
        *(s16 *)(a + 0x54) = 0;
        switch (a[3]) {
        case 0:
            *(s16 *)(a + 0x58) = 0xEFA;
            *(s16 *)(a + 0x44) = 0x2D00;
            *(s16 *)(a + 0x4A) = 0;
            *(s16 *)(a + 0x50) = 0;
            break;
        case 1:
            *(s16 *)(a + 0x44) = 0x2F00;
            *(s16 *)(a + 0x4A) = -0xE4;
            *(s16 *)(a + 0x50) = 0x10;
            break;
        case 2:
            *(s16 *)(a + 0x44) = 0x2F00;
            *(s16 *)(a + 0x4A) = -0x2AA;
            *(s16 *)(a + 0x50) = 0x30;
            break;
        case 3:
            *(s16 *)(a + 0x44) = 0x2F00;
            *(s16 *)(a + 0x4A) = -0x554;
            *(s16 *)(a + 0x50) = 0x50;
            break;
        }
        *(s16 *)(a + 0x48) = func_80083F50(*(s16 *)(a + 0x56)) >> 4;
        *(s16 *)(a + 0x4C) = -func_80083E80(*(s16 *)(a + 0x56)) >> 4;
        a[0x2B] = 0;
        a[4] = 1;
    case 1:
        if (D_1F800137 != 0) {
            func_8007778C(a);
            break;
        }
        if (a[0x2B] != 0) {
            a[0x2B]--;
            func_8007778C(a);
            break;
        }
        if (a[3] != 0) {
            *(s16 *)(a + 0x4A) += *(s16 *)(a + 0x50);
            *(s16 *)(a + 0x32) += *(s16 *)(a + 0x4A) >> 4;
            *(s16 *)(a + 0x58) = *(s16 *)(a + 0x4A) >> 1;
        }
        *(s32 *)(a + 0x2C) += *(s16 *)(a + 0x44) * *(s16 *)(a + 0x48);
        *(s32 *)(a + 0x34) += *(s16 *)(a + 0x44) * *(s16 *)(a + 0x4C);
        if (func_8007778C(a) == 0) {
            a[0] = 2;
            a[4] = 3;
            break;
        }
        func_8004766C(a);
        if (func_800495DC(a, 0, 0) != 0) {
            a[0] = 2;
            a[4] = 3;
            if (a[3] != 0) {
                func_800313A0(0x906, a + 0x2C, -0x1E, a + 0x54);
                func_80074590(0x88, 0x19, -0x32);
            }
            break;
        }
        if (a[3] != 0) {
            c[0] += 0x28;
            if (c[0] >= 0xF0) {
                c[0] = 0;
            }
        } else {
            func_800517F8(a);
        }
        break;
    case 2:
        a[0] = 2;
        a[4] = 3;
        if (a[3] != 0) {
            func_800313A0(0x906, a + 0x2C, -0x1E, a + 0x54);
            func_80074590(0x88, 0x19, -0x32);
        }
    case 3:
        func_8007A624(a);
        break;
    }
}

extern u8 *func_8007A980(s32, s32, s32);
void func_8012E274(u8 *a);
u8 *func_8012E61C(s16 kind, u8 *owner, u16 *pos)
{
    u8 *p = func_8007A980(1, 2, 0);

    if (p == NULL) {
        return NULL;
    }
    *(void **)(p + 0x1C) = func_8012E274;
    *(u8 **)(p + 0x10) = owner;
    p[2] = 0x5B;
    p[3] = kind;
    p[0x2A] = owner[0x2A];
    *(s16 *)(p + 0x2E) = pos[0];
    *(s16 *)(p + 0x32) = pos[1];
    *(s16 *)(p + 0x36) = pos[2];
    *(s16 *)(p + 0x56) = *(s16 *)(owner + 0x56);
    return p;
}

extern u16 D_1F80017C_u16;
extern u16 D_1F8000F2_e6cc;
void func_8012E6CC(u8 *a)
{
    u8 *s = a + 0x60;
    s16 d;

    a[0x60] += 0x40;
    if (a[0x60] >= 0xC0) {
        a[0x60] = 0;
        s[1] += 0x40;
        if (s[1] >= 0xC0) {
            s[1] = 0;
        }
    }
    if (D_1F80017C_u16 & 1) {
        s[2]++;
        if (s[2] >= 6) {
            s[2] = 0;
        }
    }
    s[3]++;
    if (s[3] >= 9) {
        s[3] = 0;
    }
    if (a[0x29] & 0x80) {
        U(s, 4) += (H(s, 6) - H(s, 4)) >> 3;
    } else if ((s8)a[0x29] >= 2) {
        U(s, 4) += (H(s, 6) - H(s, 4)) >> 3;
    } else {
        U(s, 4) += (H(s, 6) - H(s, 4)) >> 4;
    }
    H(a, 0x84) = U(s, 4) + 0x40;
    H(a, 0x86) = U(s, 4) + 0x1D0;
    H(a, 0x54) = 0;
    H(a, 0x56) = -D_1F8000F2_e6cc;
    H(a, 0x58) = 0;
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8012E82C);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8012EA68);

s32 func_8012ED44(u8 *a)
{
    u8 *p = D_800E7E80;
    s16 dx, dz;
    dx = H(p, 0x2E) - H(a, 0x2E);
    dz = H(p, 0x36) - H(a, 0x36);
    if ((u16)func_80084080(dx * dx + dz * dz) > H(p, 0x80)) {
        return 0;
    }
    if ((u16)(H(p, 0x32) - H(a, 0x32) + 0x258 + (H(p, 0x84) + H(a, 0x84))) > H(p, 0x86) + H(a, 0x86) + 0x258) {
        return 0;
    }
    a[0x29] = 0x80;
    return 1;
}

void func_8012EE20(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 5);
    switch (temp_v1) {                              /* irregular */
    case 0:
        if (D_800BFA42 != 0) {
            M2C_FIELD(arg0, s8 *, 0x29) = 0;
            M2C_FIELD(arg0, u8 *, 5) = (u8) (M2C_FIELD(arg0, u8 *, 5) + 1);
            return;
        }
        func_8012E82C(arg0);
        return;
    case 1:
        func_8012E82C(arg0);
        if (((M2C_FIELD(arg0, u8 *, 3) + 1) * 2) == D_800BFA42) {
            M2C_FIELD(arg0, s8 *, 4) = 2;
            M2C_FIELD(arg0, u8 *, 5) = 0U;
            M2C_FIELD(arg0, s8 *, 0x29) = 2;
        }
        return;
    }
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8012EEC8);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8012F5F0);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8012F820);

s32 func_8012FB28(u8 *p)
{
    if (func_8012FB64(p[3]) == 0) {
        return 0;
    }
    return func_8007778C(p);
}

s32 func_8012FB64(u8 a)
{
    u8 v;

    if (a == 0) {
        if (D_1F800207 < 0x18) {
            return 0;
        }
    } else {
        v = D_1F800207;
        if (v < 11 && v != 7) {
            return 0;
        }
    }
    return 1;
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8012FBB4);

void func_8012FC74(u8 *p, s32 a1)
{
    SV v;

    if (p[1]) {
        v.a = *(s16 *)(p + 0x2E);
        v.c = *(s16 *)(p + 0x36);
        v.b = *(s16 *)(p + 0x7C);
        func_8011BD98(9, &v, a1);
        func_80074590(7, 7, -0x28);
    }
}

void func_8012EEC8();
u8 *func_8012FCD8(u8 *a0, u8 a1)
{
    u8 *r = func_80072DDC(a0, 1, 2, 0x5C);

    if (r) {
        *(void **)(r + 0x1C) = func_8012EEC8;
        r[3] = a0[3];
        r[0x5E] = a1;
    }
    return r;
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8012FD38);

extern u8 D_80148E68[];
extern u8 D_800A3D40[];
void func_8012FDEC(u8 *a)
{
    u8 *g;
    u8 c;

    func_80040CDC(a, D_80148E68, D_800A3D40);
    *(s16 *)(a + 0x56) = 0x800;
    g = (u8 *)&D_800BF870;
    c = g[0xC3];
    if (c == 0xFF) {
        if (g[0x88] == c) {
            a[0x5E] = 4;
        } else {
            a[0x5E] = 3;
        }
        func_80041718(a, 1, 0);
    } else if (g[0x1C1] >= 10) {
        a[0x5E] = 2;
        func_80041718(a, 1, 0);
    } else {
        if (c & 0x80) {
            a[0x5E] = 1;
        } else {
            a[0x5E] = 0;
        }
        func_80041718(a, 0, 0);
    }
    *(s16 *)(a + 0x80) = 0xA5;
    *(s16 *)(a + 0x82) = 0x14A;
    *(s16 *)(a + 0x84) = 0x96;
    *(s16 *)(a + 0x86) = 0x1C2;
    if (D_800BFA31 >= 10) {
        *(s16 *)(a + 0x2E) = 0x19A0;
        *(s16 *)(a + 0x32) = -0x1559;
        *(s16 *)(a + 0x36) = 0x2D50;
    }
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8012FF00);

/* tools/dispatch.py draft of f_UpdateClosedClamshellQuestActor (a08, 0x2fc bytes): 3 inlined bodies
 * register maps (body -> here): 
 *   inl_8013073C (a08:func_8013073C, cover 0.95, regs 0.98): s0->s1
 *   inl_80130500 (a08:func_80130500, cover 0.90, regs 0.96): s0->s1
 *   inl_8013080C (a08:func_8013080C, cover 0.90, regs 0.92): s0->s1
 * notes:
 *   inl_8013073C: replaces 80130164-80130210
 *   inl_80130500: the copy at 80130234 branches out to .L80130344: a value-returning helper used in a condition (beqz on its result stands in for each exit; check which result goes where)
 *   inl_80130500: replaces 80130234-801302C0
 *   inl_8013080C: code inside the copy is also reached from outside (.L8013033C 8013033C, .L80130344 80130344: a tail gcc cross-jumped, or a case entering it): that path is missing from the draft; write it out in full (gcc merges the identical tails again), from tools/decomp.py's draft
 *   inl_8013080C: replaces 801302C4-80130348
 * next: fix the draft's types and the helper calls' arguments, then
 *   python3 -I tools/ccheck.py THIS.c --prog a08 --func f_UpdateClosedClamshellQuestActor --sbs
 *   python3 -I tools/install_c.py THIS.c --prog a08 */

extern u8 D_80148E68[];
extern s32 D_800ECF94;
extern s32 D_800ECFA4;
extern s32 D_800ECFA8;
extern M2C_UNK D_8014168C;
extern s32 D_800ECFA4;
extern s32 D_800ECF94;
extern s32 D_800ECFA8;
/* func_8013073C, inlined */
static inline void inl_8013073C(u8 *a)
{
    u8 *g;

    *(s32 *)(a + 0x14) = func_80124A48(a);
    func_80040CDC(a, D_80148E68, D_800A3D40);
    func_80041718(a, 1, 0);
    *(s16 *)(a + 0x56) = 0x140;
    g = (u8 *)&D_800BF870;
    if (g[0x88] == 0xFF) {
        a[0x5E] = 3;
    } else if (g[0x88] == 0) {
        a[0x5E] = 0;
        a[0] = 2;
    } else if (g[0x267]) {
        a[0x5E] = 2;
        a[0] = 2;
    } else {
        a[0x5E] = 1;
        a[0] = 2;
    }
    *(s16 *)(a + 0x80) = 0xAE;
    *(s16 *)(a + 0x82) = 0x15C;
    *(s16 *)(a + 0x84) = 0x96;
    *(s16 *)(a + 0x86) = 0x12C;
}
/* func_80130500, inlined */
static inline void inl_80130500(void *arg0) {
    u8 temp_v1;

    func_8007778C(arg0);
    func_80041098(arg0);
    func_8004190C(arg0);
    temp_v1 = M2C_FIELD(arg0, u8 *, 5);
    switch (temp_v1) {                               
    case 0:
        func_8013036C(arg0);
        break;
    case 1:
        func_80130424(arg0);
        break;
    case 2:
        func_80130484(arg0);
        break;
    }
    if (M2C_FIELD(arg0, u8 *, 1) != 0) {
        func_800518FC(arg0);
    }
}
/* func_8013080C, inlined */
static inline void inl_8013080C(void *arg0) {
    u8 temp_v1;

    M2C_FIELD(arg0, s8 *, 1) = 1;
    func_80077E7C(arg0);
    func_80041098(arg0);
    func_8004190C(arg0);
    temp_v1 = M2C_FIELD(arg0, u8 *, 5);
    switch (temp_v1) {                               
    case 0:
        func_801305AC(arg0);
        break;
    case 1:
        func_80130644(arg0);
        break;
    case 2:
        func_801306A4(arg0);
        break;
    }
    func_800518FC(arg0);
}
void f_UpdateClosedClamshellQuestActor(u8 *a)
{
    s32 v;
    s32 k;
    s32 m;
    s32 v_f;

    switch (a[4]) {
    case 0:
        if (a[3] == 0) {
            v = func_800519E0(a, 0xB, D_800ECFA4, &D_8014168C);
        } else {
            v = func_800519E0(a, 0xB, D_800ECF94, &D_8014168C);
        }
        if (v == 0) {
            v_f = D_800ECFA8;
            a[0] = 9;
            k = a[3];
            a[0x2B] = 0;
            a[0x29] = 0;
            M2C_FIELD(a, s16 *, 0x54) = 0;
            M2C_FIELD(a, s16 *, 0x58) = 0;
            M2C_FIELD(a, s32 *, 0x3C) = v_f;
            a[4]++;
            switch (k) {
            case 0:
                func_8012FDEC(a);
                break;
            case 1:
                inl_8013073C(a);
                break;
            }
        }
        break;
    case 1:
        switch (a[3]) {
        case 0:
            inl_80130500(a);
            break;
        case 1:
            inl_8013080C(a);
            break;
        }
        a[0x2B] = 0;
        break;
    case 2:
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8013036C);

extern void *D_801463B0[];
void func_80130424(u8 *a)
{
    if (a[0x71] == 0xFF) {
        func_80040D68(a, D_801463B0[a[0x5E]]);
        a[5] = 2;
        a[6] = 0;
        a[0x70] = 1;
    }
}

void func_80130484(u8 *a)
{
    u8 k = a[0x71];

    if (k == 0xFF) {
        switch (a[0x5E]) {
        case 0:
            D_800BF870.pad1[0xC2] |= 0x80;
            a[0x5E]++;
            break;
        case 2:
            if (D_800BF8F8 == k) {
                a[0x5E] = 4;
            } else {
                a[0x5E] = 3;
            }
            break;
        }
        a[5] = 0;
        a[6] = 0;
    }
}

void func_80130500(void *arg0) {
    u8 temp_v1;

    func_8007778C();
    func_80041098(arg0);
    func_8004190C(arg0);
    temp_v1 = M2C_FIELD(arg0, u8 *, 5);
    switch (temp_v1) {                              /* irregular */
    case 0:
        func_8013036C(arg0);
        break;
    case 1:
        func_80130424(arg0);
        break;
    case 2:
        func_80130484(arg0);
        break;
    }
    if (M2C_FIELD(arg0, u8 *, 1) != 0) {
        func_800518FC(arg0);
    }
}

extern u8 D_80146604[];
extern u8 D_8014661C[];
void func_801305AC(u8 *a)
{
    u8 s = a[0x5E];

    if (s == 3) {
        if (a[0x2B] != s) {
            return;
        }
        func_80042354(1, 2);
        func_80040D68(a, D_80146604);
    } else {
        if ((*(u8 **)(a + 0x14))[0x5E] == 0) {
            return;
        }
        if (s == 0) {
            func_80040D68(a, D_8014661C);
        } else {
            func_80040D68(a, D_80146604);
        }
    }
    a[0x70] = 1;
    a[5] = 1;
}

extern void *D_801465F4[];
void func_80130644(u8 *a)
{
    if (a[0x71] == 0xFF) {
        func_80040D68(a, D_801465F4[a[0x5E]]);
        a[5] = 2;
        a[6] = 0;
        a[0x70] = 1;
    }
}

void func_801306A4(u8 *p)
{
    u8 *q;

    if (p[0x71] == 0xFF) {
        q = *(u8 **)(p + 0x14);
        switch (p[0x5E]) {
        case 2:
            p[0] = 9;
        case 0:
            p[0x5E]++;
        case 1:
            q[0x5E] = 0;
            D_800BF809 = 0;
            break;
        }
        p[5] = 0;
    }
}

s32 func_80130714(u8 *a)
{
    if (D_800BFAD7 != 0) {
        a[0x5E] = 0x2;
        return 3;
    }
    return 2;
}

void func_8013073C(u8 *a)
{
    u8 *g;

    *(s32 *)(a + 0x14) = func_80124A48(a);
    func_80040CDC(a, D_80148E68, D_800A3D40);
    func_80041718(a, 1, 0);
    *(s16 *)(a + 0x56) = 0x140;
    g = (u8 *)&D_800BF870;
    if (g[0x88] == 0xFF) {
        a[0x5E] = 3;
    } else if (g[0x88] == 0) {
        a[0x5E] = 0;
        a[0] = 2;
    } else if (g[0x267]) {
        a[0x5E] = 2;
        a[0] = 2;
    } else {
        a[0x5E] = 1;
        a[0] = 2;
    }
    *(s16 *)(a + 0x80) = 0xAE;
    *(s16 *)(a + 0x82) = 0x15C;
    *(s16 *)(a + 0x84) = 0x96;
    *(s16 *)(a + 0x86) = 0x12C;
}

void func_8013080C(void *arg0) {
    u8 temp_v1;

    M2C_FIELD(arg0, s8 *, 1) = 1;
    func_80077E7C();
    func_80041098(arg0);
    func_8004190C(arg0);
    temp_v1 = M2C_FIELD(arg0, u8 *, 5);
    switch (temp_v1) {                              /* irregular */
    case 0:
        func_801305AC(arg0);
        break;
    case 1:
        func_80130644(arg0);
        break;
    case 2:
        func_801306A4(arg0);
        break;
    }
    func_800518FC(arg0);
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_801308B0);

extern u8 D_800BF822;
s32 func_80130BA0(u8 *a)
{
    u8 *p = D_800E7E80;
    u8 *b;

    switch (a[0x78]) {
    case 0:
        b = func_80129784(a);
        if (b != 0) {
            *(u8 **)(a + 0x14) = b;
            func_800440E4(p, 0xCF, 2);
            func_8004ED0C(0x10, 4);
            func_8004D650(0x10, 1);
            a[0x78]++;
        }
        break;
    case 1:
        if (D_800BF80E != 0) {
            func_80041718(a, 7, 4);
            a[0x78]++;
        }
        break;
    case 2:
        if ((*(u8 **)(a + 0x38))[4] != 0) {
            (*(u8 **)(a + 0x14))[5] = 1;
            func_800440E4(p, 2, 4);
            a[0x78]++;
        }
        break;
    case 3:
        if (a[0x79] != 1) {
            return 0;
        }
        func_80041718(a, 9, 4);
        a[0x78]++;
        break;
    case 4:
        if (!(D_800BF822 & 1)) {
            return 1;
        }
        break;
    }
    return 0;
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80130CE0);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80130F84);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_801310D8);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8013169C);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80131964);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80131BC4);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_801320B4);

extern s32 D_800ECFA0;
extern u8 D_8014168C_4b7c[];
void f_UpdateGiantFishActor(u8 *a)
{
    switch (a[4]) {
    case 0:
        switch (a[3]) {
        case 0:
            if (func_800519E0(a, 0xB, D_800ECFA0, D_8014168C_4b7c) != 0) {
                return;
            }
            *(s16 *)(a + 0x80) = 0xAA;
            *(s16 *)(a + 0x82) = 0x154;
            *(s16 *)(a + 0x84) = 0x154;
            *(s16 *)(a + 0x86) = 0x3AC;
            break;
        case 1:
            if (func_800519E0(a, 0xC, D_800ECFA0, D_8014168C_4b7c) != 0) {
                return;
            }
            func_80051B04(*(u8 **)(a + ((a[9] - 1) << 2) + 0xC0), 0x12, 0xB);
            *(s16 *)(a + 0x80) = 0x96;
            *(s16 *)(a + 0x82) = 0x12C;
            *(s16 *)(a + 0x84) = 0x12C;
            *(s16 *)(a + 0x86) = 0x384;
            break;
        }
        *(s32 *)(a + 0x3C) = D_800ECFA8;
        func_80040CDC(a, D_80148E68, D_800A3D18);
        a[0x7B] = 0;
        func_80041718(a, 0, 0);
        a[0] = 9;
        *(s16 *)(a + 0x56) = 0x92E;
        a[0x2B] = 0;
        a[0x29] = 0;
        *(s16 *)(a + 0x58) = 0;
        *(s16 *)(a + 0x54) = 0;
        if (a[3] == 1) {
            if (D_800BF8E2 != 0xFF) {
                a[0x5E] = 1;
            } else {
                a[0x5E] = 2;
            }
        } else {
            a[0x5E] = 0;
        }
        a[3] = 2;
        a[4]++;
        break;
    case 1:
        switch (a[0x5E]) {
        case 0:
            func_801310D8(a);
            break;
        case 1:
            func_80131BC4(a);
            break;
        case 2:
            func_801320B4(a);
            break;
        }
        if (a[1] != 0) {
            func_800518FC(a);
        }
        a[0x2B] = 0;
        break;
    case 2:
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

extern u8 D_800BFB53;
s32 func_80132468(void)
{
    if (D_800BFB53 != 0) {
        return 0x3;
    }
    return 0x2;
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80132488);

extern u8 D_800E7E80[];
extern u8 D_800BF81E;
extern s32 D_1F80023C;
s32 func_80132564(u8 *a)
{
    u8 *t = D_800E7E80;

    switch (a[0x78]) {
    case 0:
        if (!(*(u16 *)(t + 0x17E) & 0x180)) {
            return 1;
        }
        D_800BF81E = 0;
        t[4] = 4;
        t[5] = 0x21;
        t[6] = 0;
        t[7] = 0;
        D_1F80023C = *(s32 *)(t + 4);
        func_8004ED0C(t[0x6F], 3);
        t[0x6F] = 0;
        t[5] = 0x3A;
        t[6] = 0;
        a[0x78]++;
        break;
    case 1:
        if (t[5] == 0x21) {
            return 1;
        }
        break;
    }
    return 0;
}

extern u8 D_800E7E80[];
s32 func_8013263C(u8 *a)
{
    u8 *t = D_800E7E80;

    switch (a[0x78]) {
    case 0:
        D_800BF81E = 0;
        t[4] = 4;
        t[5] = 0x21;
        t[6] = 0;
        t[7] = 0;
        D_1F80023C = *(s32 *)(t + 4);
        if (t[0x6F] == 0) {
            func_8004ED0C(0x11, 0);
        } else {
            func_8004EDDC(t[0x6F], 0x11);
        }
        t[0x6F] = 0x11;
        t[5] = 0x3A;
        t[6] = 0;
        a[0x78]++;
        break;
    case 1:
        if (t[5] == 0x21) {
            return 1;
        }
        break;
    }
    return 0;
}

s32 func_8013271C(void *arg0) {
    if (M2C_FIELD(arg0, s16 *, 0x72) != 0) {
        M2C_FIELD(arg0, s8 *, 0xBF) = 1;
    } else {
        M2C_FIELD(arg0, s8 *, 0xBF) = 0;
    }
    return 1;
}

s32 func_80132740(void *arg0) {
    M2C_FIELD(arg0, u8 *, 0x7B) = (u8) M2C_FIELD(arg0, u8 *, 0x72);
    return 1;
}

s32 func_80132754(s32 arg0) {
    void *temp_v0;

    temp_v0 = func_80031220(0x919, 0, -0x1E);
    if (temp_v0 != NULL) {
        M2C_FIELD(temp_v0, s32 *, 0x10) = arg0;
    }
    return 1;
}

s32 func_80132794(void *arg0) {
    M2C_FIELD(arg0, u8 *, 0x5F) = (u8) M2C_FIELD(arg0, u8 *, 0x72);
    return 1;
}

extern u8 D_801416E4[];
extern u8 D_80146DDC[];
s32 func_801352CC(u8 *a);
s32 func_80135354(void *a0);
void func_80134F68(u8 *a);
void func_8013500C(void *arg0);
void func_801350D8(void *arg0);
void func_801327A8(u8 *a)
{
    u8 *g;

    switch (a[4]) {
    case 0:
        g = D_800ECF58;
        if (func_800519E0(a, 0xF, *(s32 *)(g + 0x64), D_801416E4) != 0) {
            break;
        }
        *(s32 *)(a + 0x3C) = *(s32 *)(g + 0x68);
        func_80051B04(*(u8 **)(a + 0xC4), 0x19, 0x10);
        func_80135630(a, 0, 0);
        *(s16 *)(a + 0x6E) = -1;
        a[4]++;
        a[0] = 1;
        a[0x2B] = 0;
        a[0x29] = 0;
        a[0x5F] = 0;
        a[0x5E] = 0;
        a[0xBF] = 0;
        a[0x46] = 0;
        a[0x47] = 0;
        *(s16 *)(a + 0x54) = 0;
        *(s16 *)(a + 0x58) = 0;
        *(s16 *)(a + 0x74) = 0;
        *(s16 *)(a + 0x78) = 0;
        a[0x2A] = D_80146DDC[a[3]];
        func_8004766C(a);
        func_8012DE84(a, *(s16 *)(a + 0x32));
        *(s16 *)(a + 0x32) = D_1F8001A4_f18c + 0x28;
        *(s16 *)(a + 0x7A) = D_1F8001A4_f18c;
        *(s16 *)(a + 0x7C) = *(s16 *)(a + 0x2E);
        *(s16 *)(a + 0x7E) = *(s16 *)(a + 0x36);
        func_80049674(a);
        *(s16 *)(a + 0x60) = D_1F8001A0_b0de;
        *(s16 *)(a + 0x56) = D_1F8001A0_b0de;
        a[0xBE] = 0;
        if (func_801352CC(a) != 0) {
            *(s16 *)(a + 0x56) = (D_1F8001A0_b0de + 0x800) & 0xFFF;
            a[0xBE] ^= 1;
        }
        break;
    case 1:
        func_80135354(a);
        if (a[0x2B] != 0) {
            a[0x2B]--;
        } else {
            if (D_800BF809 != 0 || D_1F800137 != 0) {
                break;
            }
            *(s16 *)(a + 0x6A) = func_80076D68(a);
            switch (a[5]) {
            case 0:
                func_80134E44(a);
                break;
            case 1:
                func_80132BC8(a);
                break;
            case 2:
                func_80132DD4(a);
                break;
            case 3:
                func_80132F90(a);
                break;
            case 4:
                func_80134F68(a);
                break;
            case 5:
                func_8013500C(a);
                break;
            case 6:
                func_801331A8(a);
                break;
            case 7:
                func_8013342C(a);
                break;
            case 8:
                func_801336F0(a);
                break;
            case 9:
                func_80133CB8(a);
                break;
            case 10:
                func_80133E8C(a);
                break;
            }
        }
        if (a[1] != 0) {
            func_800518FC(a);
        }
        a[0x29] = 0;
        a[0x5F] = 0;
        break;
    case 2:
        switch (a[5]) {
        case 0:
        case 4:
        case 5:
        case 6:
            func_80135354(a);
            if (D_800BF809 != 0 || D_1F800137 != 0) {
                break;
            }
            if (*(s16 *)(a + 0x74) == 0) {
                func_80076D68(a);
            }
            func_8013404C(a);
            break;
        case 1:
            func_8007778C(a);
            func_80076D68(a);
            func_801350D8(a);
            break;
        case 10:
            if ((s16)func_8012E1A4(a) != 0) {
                a[4] = 3;
                return;
            }
            a[5] = 2;
            goto c2;
        case 11:
            if (func_80080750(a, *(u8 **)(a + 0xC0), 2) != 0) {
                a[4] = 3;
                return;
            }
            a[5] = 2;
        case 2:
        case 7:
        case 8:
        c2:
            func_8007778C(a);
            func_801345B4(a);
            break;
        }
        a[0x29] = 0;
        a[0x5F] = 0;
        if (a[1] != 0) {
            func_800518FC(a);
        }
        break;
    case 3:
        if (a[0x1B] & 0x40) {
            a[0x1B] &= 0xBF;
            break;
        }
        func_8007A624(a);
        break;
    }
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80132BC8);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80132DD4);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80132F90);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_801331A8);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8013342C);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_801336F0);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80133CB8);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80133E8C);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8013404C);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_801345B4);

s32 func_80134814(T4814 *a)
{
    switch (a->x6E) {
    case 0:
        if (a->xBE) {
            a->x4E = -0x80;
            a->x6C = a->x56 - 0x800;
        } else {
            a->x4E = 0x80;
            a->x6C = a->x56 + 0x800;
        }
        a->x6E++;
    case 1:
        a->x56 += a->x4E;
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

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80134904);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_801349CC);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80134B2C);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80134CEC);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80134E44);

void func_80134F68(u8 *a)
{
    if (func_80135158(a) != -1) {
        func_80135574(a, 0x14, 0xC8);
        switch (a[6]) {
        case 0:
            func_80135630(a, 2, 4);
            a[6]++;
            break;
        case 1:
            if (--*(s16 *)(a + 0x40) == 0) {
                a[5] = 0xA;
                a[6] = 1;
            }
            break;
        }
    }
}

void func_8013500C(void *arg0) {
    u16 temp_v0;
    u8 temp_v1;

    if (func_80135158() != -1) {
        func_80135574(arg0, 0x64, 0x12C);
        temp_v1 = M2C_FIELD(arg0, u8 *, 6);
        switch (temp_v1) {                          /* irregular */
        case 0:
            func_80051B04(M2C_FIELD(arg0, s32 *, 0xC4), 0x19, 0x10);
            func_80135630(arg0, 0, 6);
            M2C_FIELD(arg0, u8 *, 6) = (u8) (M2C_FIELD(arg0, u8 *, 6) + 1);
            return;
        case 1:
            temp_v0 = M2C_FIELD(arg0, u16 *, 0x40) - 1;
            M2C_FIELD(arg0, u16 *, 0x40) = temp_v0;
            if ((temp_v0 << 0x10) == 0) {
                func_80051B04(M2C_FIELD(arg0, s32 *, 0xC4), 0x19, 1);
                M2C_FIELD(arg0, s8 *, 5) = 0xA;
                M2C_FIELD(arg0, u8 *, 6) = 0U;
                M2C_FIELD(arg0, u16 *, 0x40) = 6U;
            }
            break;
        }
    }
}

void func_801350D8(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 6) == 0) {
        M2C_FIELD(arg0, u8 *, 0x1B) = (u8) (M2C_FIELD(arg0, u8 *, 0x1B) & 0xBF);
        func_80051B04(M2C_FIELD(arg0, s32 *, 0xC4), 0x19, 0xF);
        func_80135630(arg0, 0x12, 4);
        func_80026100(8);
        func_80074590(0x85, 0, 0);
        M2C_FIELD(arg0, u8 *, 6) = (u8) (M2C_FIELD(arg0, u8 *, 6) + 1);
    }
}

s32 func_80135158(void *a0)
{
    func_8004766C(a0);
    if (func_80134CEC(a0) != 0) {
        return -1;
    }
    return 0;
}

void func_80135194(void *arg0) {
    s16 temp_v0;

    if (func_80134904() < 2) {
        if (M2C_FIELD(arg0, s16 *, 0x70) < 0x47F) {
            M2C_FIELD(arg0, s16 *, 0x72) = 1;
        } else {
            goto block_4;
        }
    } else {
        temp_v0 = func_80135230(arg0);
        if (temp_v0 < 0x1FE) {
block_4:
            M2C_FIELD(arg0, s16 *, 0x72) = 2;
        } else if (temp_v0 < 0x352) {
            M2C_FIELD(arg0, s16 *, 0x72) = 1;
        } else {
            M2C_FIELD(arg0, s16 *, 0x72) = 0;
        }
    }
    func_80135630(arg0, M2C_FIELD(arg0, s16 *, 0x72) + 8, 4);
}

s32 func_80135230(u8 *a)
{
    s16 dx = D_1F800160 - *(s16 *)(a + 0x2E);
    s16 dz = D_1F800164 - *(s16 *)(a + 0x36);
    s16 dy = D_1F800162 - *(s16 *)(a + 0x32);
    return (func_80085690((s16)dy, (s16)func_80084080(dx * dx + dz * dz)) + 0x400) & 0xFFF;
}

extern s8 D_1F800164_6889[];
extern s8 D_1F800164_6889[];
extern s16 D_800E7FFE;
extern s8 D_1F800160_d288[];
s32 func_801352CC(u8 *a) {
    s16 dz, dx;

    if (D_800E7FFE & 0x8200) {
        return 0;
    }
    dx = *(u16 *)D_1F800160_d288 - M2C_FIELD(a, u16 *, 0x2E);
    dz = *(u16 *)D_1F800164_6889 - M2C_FIELD(a, u16 *, 0x36);
    return func_80077768((s16)-func_80085690(dz, dx), M2C_FIELD(a, s16 *, 0x56), 0) != 0;
}

extern u16 D_1F8000E2;
s32 func_80135354(void *a0)
{
    if (func_80135388(a0) == 0) {
        return 0;
    }
    return func_8007778C(a0);
}

s32 func_80135388(u8 *a)
{
    u8 s;
    switch (a[3]) {
    case 0:
    case 1:
        if (D_1F800207 < 11) {
            break;
        }
        return 0;
    case 2:
    case 3:
        s = D_1F800207;
        if (s < 11) {
            if (s != 7) {
                return 0;
            }
        }
        break;
    case 4:
    case 5:
        if (D_1F800207 < 25) {
            return 0;
        }
        break;
    }
    return 1;
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80135424);

extern s8 D_1F8001A0[];
void func_801354F4(void *arg0) {
    u16 temp_a0;

    if (M2C_FIELD(arg0, u8 *, 0xBF) != 0) {
        func_80049760();
    } else {
        func_80049674(arg0);
    }
    temp_a0 = *((u16 *)D_1F8001A0);
    M2C_FIELD(arg0, u16 *, 0x60) = temp_a0;
    if (M2C_FIELD(arg0, s16 *, 0x6E) == -1) {
        if (M2C_FIELD(arg0, u8 *, 0xBE) == 0) {
            M2C_FIELD(arg0, u16 *, 0x56) = temp_a0;
            return;
        }
        M2C_FIELD(arg0, u16 *, 0x56) = (u16) ((temp_a0 + 0x800) & 0xFFF);
    }
}

extern s32 func_8011B344();
extern s32 func_80083E80(s32);

s32 func_80135574(u8 *a, s32 x, s32 y)
{
    u8 *q;
    s16 t = D_1F80017C_0fe7 & 0x3F;

    if (a[1] != 0) {
        if (t == 0 || t == 0x20) {
            q = (u8 *)func_8011B344(a + 0x2C, -10, (s16)x, (s16)y);
            if (q != NULL) {
                *(u16 *)(q + 0x2E) = *(u16 *)(a + 0x7A);
            }
        }
    }
    *(u16 *)(a + 0x32) = *(u16 *)(a + 0x7A) + ((func_80083E80(t << 6) >> 7) + 0x28);
    if (t == 0 || t == 0x20) {
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80135630);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_801356F8);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80135CB8);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80135EE8);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_801364F8);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_801366A4);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8013698C);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80136C94);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80136DE0);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80136F5C);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_801371CC);

extern u8 D_80149588[];
void func_8013731C(u8 *a)
{
    s16 dx = D_1F800160 - *(s16 *)(a + 0x2E);
    s16 dz = D_1F800164 - *(s16 *)(a + 0x36);
    s16 dy = D_1F800162 - *(s16 *)(a + 0x32);
    s32 ang;
    s32 k;

    ang = (func_80085690((s16)dy, (s16)func_80084080(dx * dx + dz * dz)) + 0x400) & 0xFFF;
    k = 0;
    if (ang >= 0x1FE) {
        if (ang < 0x352) {
            k = 1;
        } else if (ang < 0x4A7) {
            k = 2;
        } else {
            k = 4;
            if (ang < 0x5FB) {
                k = 3;
            }
        }
    }
    func_80077C40(a, D_80149588, k + 7);
}

s32 func_80137410(T4814 *a)
{
    switch (a->x6E) {
    case 0:
        if (a->xBE) {
            a->x4E = -0x80;
            a->x6C = a->x56 - 0x800;
        } else {
            a->x4E = 0x80;
            a->x6C = a->x56 + 0x800;
        }
        a->x6E++;
    case 1:
        a->x56 += a->x4E;
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

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80137500);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_801375D4);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80137780);

s32 func_80137898(u8 *a) {
    s16 dz, dx;

    if (D_800E7FFE & 0x8200) {
        return 0;
    }
    dx = *(u16 *)D_1F800160_d288 - M2C_FIELD(a, u16 *, 0x2E);
    dz = *(u16 *)D_1F800164_6889 - M2C_FIELD(a, u16 *, 0x36);
    return func_80077768((s16)-func_80085690(dz, dx), M2C_FIELD(a, s16 *, 0x56), 0) != 0;
}

s32 func_80137920(u8 *a)
{
    switch (a[3]) {
    case 0:
    case 1:
        if (D_1F800207 >= 11) {
            return 0;
        }
        if (D_1F800160 < 0x23F0) {
            return 0;
        }
        break;
    case 2:
        if (D_1F800162 < -0x157C) {
            return 0;
        }
        break;
    case 3:
        if (D_1F800207 < 7) {
            return 0;
        }
        break;
    }
    return func_8007778C(a);
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_801379BC);

s32 func_80137A90(u8 *a)
{
    u8 *t;
    s32 lim;

    if (a[0x5E] != 0) {
        return 0;
    }
    t = D_800E7E80;
    if (t[0x147] != a[0xBE]) {
        if (t[0x146] & 1) {
            s32 n = t[0x176];
            lim = 1000;
            if (n < 9) {
                if (n >= 6) {
                    lim = 600;
                }
            }
            if (lim >= *(s16 *)(a + 0x70)) return 1;
        }
    }
    return 0;
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80137B18);

#define P0(p) (*(u8 **)((u8 *)(p) + 0xC0))
#define FOLLOW(a, o)                       \
    U(a, 0x2E) = U(P0(o), 0x2C);           \
    U(a, 0x32) = U(P0(o), 0x30);           \
    U(a, 0x36) = U(P0(o), 0x34);           \
    U(a, 0x56) = U(o, 0x56);               \
    U(P0(a), 0xC) = U(P0(o), 0xC);         \
    U(a, 0x60) = U(o, 0x60);               \
    a[0xBE] = o[0xBE];                     \
    a[0xBF] = o[0xBF];                     \
    if (a[4] == 1) {                       \
        o[0x47] = a[0x47];                 \
        o[0x2B] = a[0x2B];                 \
    }
void func_80137C5C(u8 *a)
{
    u8 *o;
    u8 *q;

    switch (a[4]) {
    case 0:
        a[4] = 1;
        if (func_80051B70(a, 0x17, 0x12) != 0) {
            break;
        }
        W_d1fb(a, 0x3C) = D_800ECFB8;
        a[0xD] |= 4;
        P0(a)[0x3F] = 0xFD;
        o = (u8 *)W_d1fb(a, 0x10);
        H(a, 0x80) = 0x78;
        H(a, 0x82) = 0xF0;
        H(a, 0x84) = 0x8C;
        a[0] = 1;
        H(a, 0x86) = 0xA0;
        a[0x47] = 0;
        a[0x2B] = 0;
        if (o == NULL) {
            break;
        }
        FOLLOW(a, o);
        if (o[1] != 0) {
            a[1] = 1;
            goto die;
        }
        break;
    case 1:
        o = (u8 *)W_d1fb(a, 0x10);
        if (o != NULL) {
            FOLLOW(a, o);
            if (o[1] != 0) {
                a[1] = 1;
                func_80077E7C(a);
                func_800517F8(a);
            }
        }
        a[0x47] = 0;
        break;
    case 2:
        q = (u8 *)W_d1fb(a, 0x10);
        switch (a[5]) {
        case 1:
            switch (a[6]) {
            case 0:
                q[6] = 0x80;
                q[4] = 2;
                q[5] = 1;
                q[0] = 2;
                H(a, 0x84) = 0xA0;
                H(a, 0x86) = 0xB4;
                a[0xD] |= 4;
                P0(a)[0x3F] = 3;
                a[6]++;
            case 1:
                o = (u8 *)W_d1fb(a, 0x10);
                if (o == NULL) {
                    break;
                }
                FOLLOW(a, o);
                if (o[1] != 0) {
                    a[1] = 1;
                    goto die;
                }
                break;
            case 2:
                W_d1fb(q, 0x10) = 0;
                q[0x5E] = 1;
                a[0x2A] = q[0x2A];
                U(a, 0x56) = U(q, 0x56);
                W_d1fb(a, 0x10) = 0;
                a[6]++;
            case 3:
                if (func_8007778C(a) != 0) {
                die:
                    func_80077E7C(a);
                    func_800517F8(a);
                }
                break;
            }
            break;
        case 0:
        case 2:
            if (func_8007778C(a) != 0) {
                func_80077E7C(a);
                func_800517F8(a);
            }
            switch (a[6]) {
            case 0:
                W_d1fb(q, 0x10) = 0;
                q[0x5E] = 1;
                a[0x2A] = q[0x2A];
                U(a, 0x56) = U(q, 0x56);
                W_d1fb(a, 0x10) = 0;
                if (func_80077768(a[0x2B] << 4, H(a, 0x56), 0) != 0) {
                    H(a, 0x48) = -func_80083F50(H(a, 0x56)) >> 4;
                    H(a, 0x4C) = func_80083E80(H(a, 0x56)) >> 4;
                } else {
                    H(a, 0x48) = func_80083F50(H(a, 0x56)) >> 4;
                    H(a, 0x4C) = -func_80083E80(H(a, 0x56)) >> 4;
                }
                H(a, 0x4A) = -0x200;
                H(a, 0x44) = 0x1000;
                H(a, 0x40) = 0x14;
                a[6]++;
                break;
            case 1:
                U(a, 0x58) += 0x180;
                W_d1fb(a, 0x2C) += H(a, 0x48) * H(a, 0x44);
                W_d1fb(a, 0x34) += H(a, 0x4C) * H(a, 0x44);
                W_d1fb(a, 0x30) += H(a, 0x4A) * H(a, 0x44);
                func_8004766C(a);
                if (H(a, 0x40) != 0) {
                    H(a, 0x40)--;
                } else if (func_800495DC(a, 0x5A, 0x5A) != 0) {
                    if (a[1] != 0) {
                        func_80074590(0x1B, 0, 0);
                        func_800315D4(a + 0x2C);
                    }
                set3:
                    a[4] = 3;
                    break;
                }
                H(a, 0x4A) += 0x30;
                if (H(a, 0x4A) > 0x1000) {
                    H(a, 0x4A) = 0x1000;
                }
                break;
            }
            break;
        case 0xB:
            goto set3;
        }
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

void func_8013829C(s32 arg0) {
    void *temp_a0;

    temp_a0 = M2C_FIELD(arg0, void **, 0x10);
    if (temp_a0 != NULL) {
        M2C_FIELD(arg0, u16 *, 0x2E) = (u16) M2C_FIELD(M2C_FIELD(temp_a0, void **, 0xC0), u16 *, 0x2C);
        M2C_FIELD(arg0, u16 *, 0x32) = (u16) M2C_FIELD(M2C_FIELD(temp_a0, void **, 0xC0), u16 *, 0x30);
        M2C_FIELD(arg0, u16 *, 0x36) = (u16) M2C_FIELD(M2C_FIELD(temp_a0, void **, 0xC0), u16 *, 0x34);
        M2C_FIELD(arg0, u16 *, 0x56) = (u16) M2C_FIELD(temp_a0, u16 *, 0x56);
        M2C_FIELD(M2C_FIELD(arg0, void **, 0xC0), u16 *, 0xC) = (u16) M2C_FIELD(M2C_FIELD(temp_a0, void **, 0xC0), u16 *, 0xC);
        M2C_FIELD(arg0, u16 *, 0x60) = (u16) M2C_FIELD(temp_a0, u16 *, 0x60);
        M2C_FIELD(arg0, u8 *, 0xBE) = (u8) M2C_FIELD(temp_a0, u8 *, 0xBE);
        M2C_FIELD(arg0, u8 *, 0xBF) = (u8) M2C_FIELD(temp_a0, u8 *, 0xBF);
        if (M2C_FIELD(arg0, u8 *, 4) == 1) {
            M2C_FIELD(temp_a0, u8 *, 0x47) = (u8) M2C_FIELD(arg0, u8 *, 0x47);
            M2C_FIELD(temp_a0, u8 *, 0x2B) = (u8) M2C_FIELD(arg0, u8 *, 0x2B);
        }
        if (M2C_FIELD(temp_a0, u8 *, 1) != 0) {
            M2C_FIELD(arg0, s8 *, 1) = 1;
            func_80077E7C(arg0);
            func_800517F8(arg0);
        }
    }
}

u8 *func_80138398(u8 *a0)
{
    u8 *r = func_80072DDC(a0, 1, 2, 0x5F);

    if (r) {
        *(void **)(r + 0x1C) = func_80137C5C;
        r[3] = a0[3] | 0x80;
    }
    return r;
}

extern u8 D_801417EC[];
extern u8 D_80149A50_096b[];
extern u8 D_80146EA0[];
s32 func_801391C4(u8 *a);
s32 func_8013900C(void *a0);
void func_80138F00(void *arg0);
void func_801383F0(u8 *a)
{
    u8 *g;
    s32 f = 0;
    s32 s;

    switch (a[4]) {
    case 0:
        g = D_800ECF58;
        if (func_800519E0(a, 5, *(s32 *)(g + 0x54), D_801417EC) != 0) {
            break;
        }
        *(s32 *)(a + 0x3C) = *(s32 *)(g + 0x58);
        *(s16 *)(a + 0x80) = 0x6E;
        *(s16 *)(a + 0x82) = 0xDC;
        *(s16 *)(a + 0x84) = 0xAA;
        a[0] = 1;
        *(s16 *)(a + 0x86) = 0xCD;
        a[0x2B] = 0;
        a[0x29] = 0;
        *(s16 *)(a + 0x54) = 0;
        *(s16 *)(a + 0x58) = 0;
        a[4]++;
        func_80077C40(a, D_80149A50_096b, 0);
        a[0x2A] = D_80146EA0[a[3]];
        func_8004766C(a);
        func_80049760(a);
        *(s16 *)(a + 0x60) = D_1F8001A0_b0de;
        *(s16 *)(a + 0x56) = D_1F8001A0_b0de;
        a[0xBE] = 0;
        if (func_801391C4(a) != 0) {
            *(s16 *)(a + 0x56) = (D_1F8001A0_b0de + 0x800) & 0xFFF;
            a[0xBE] ^= 1;
        }
        *(s16 *)(a + 0x4A) = 0;
        *(s16 *)(a + 0x4E) = 0;
        *(s16 *)(a + 0x6E) = -1;
        *(s16 *)(a + 0x7A) = *(s16 *)(a + 0x32);
        *(s16 *)(a + 0x7C) = *(s16 *)(a + 0x2E);
        *(s16 *)(a + 0x7E) = *(s16 *)(a + 0x36);
        break;
    case 1:
        func_8013900C(a);
        *(s16 *)(a + 0x6A) = func_80076D68(a);
        if (D_800BF809 != 0 || D_1F800137 != 0) {
            break;
        }
        if (a[0x29] != 0) {
            a[5] = 3;
            a[6] = 0;
        } else if (a[0x2B] & 2) {
            a[5] = 2;
            a[6] = 0;
        }
        switch (a[5]) {
        case 0:
            func_80138784(a);
            break;
        case 1:
            func_80138B08(a);
            break;
        case 2:
            f = 1;
            func_80138F00(a);
            break;
        case 3:
            f = 1;
            func_80138CFC(a);
            break;
        }
        if (f == 0) {
            *(s16 *)(a + 0x4A) += 0x40;
            *(s32 *)(a + 0x30) += func_80083E80(*(s16 *)(a + 0x4A)) << 6;
            *(s16 *)(a + 0x4E) += 0x18;
            f = func_80083F50(*(s16 *)(a + 0x4E)) >> 3;
            *(s32 *)(a + 0x2C) += *(s16 *)(a + 0x48) * f;
            *(s32 *)(a + 0x34) += *(s16 *)(a + 0x4C) * f;
        }
        a[0x2B] = 0;
        a[0x29] = 0;
        if (a[1] != 0) {
            func_800518FC(a);
        }
        break;
    case 2:
        func_8013900C(a);
        if (a[5] == 0xB && func_80080750(a, *(u8 **)(a + 0xC0), 0) != 0) {
            a[4] = 3;
            break;
        }
        if (a[1] != 0) {
            func_80074590(0x8C, 0, 0);
            func_800315D4(a + 0x2C);
        }
        func_801247C4(a);
        a[4] = 3;
        if (a[1] != 0) {
            func_800518FC(a);
        }
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80138784);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80138B08);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80138CFC);

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
} T8E10;
s32 func_80138E10(T8E10 *a)
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

extern M2C_UNK D_80149A50;
void func_80138F00(void *arg0) {
    s8 temp_v0;
    u16 temp_v0_2;
    u16 var_v0;
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 6);
    switch (temp_v1) {                              /* irregular */
    case 0:
        M2C_FIELD(arg0, u16 *, 0x40) = 0x1EU;
        func_80077C40(arg0, &D_80149A50, 9);
        M2C_FIELD(M2C_FIELD(arg0, void **, 0xD0), s16 *, 0x38) = 0x1000;
        M2C_FIELD(M2C_FIELD(arg0, void **, 0xD0), s16 *, 0x3A) = 0x1000;
        M2C_FIELD(M2C_FIELD(arg0, void **, 0xD0), s16 *, 0x3C) = 0x1000;
        temp_v0 = (M2C_FIELD(arg0, u8 *, 0x2B) & 1) ^ 1;
        M2C_FIELD(arg0, s8 *, 0xBE) = temp_v0;
        if (temp_v0 != 0) {
            var_v0 = (M2C_FIELD(arg0, u16 *, 0x60) + 0x800) & 0xFFF;
        } else {
            var_v0 = M2C_FIELD(arg0, u16 *, 0x60);
        }
        M2C_FIELD(arg0, u16 *, 0x56) = var_v0;
        M2C_FIELD(arg0, s16 *, 0x6E) = -1;
        M2C_FIELD(arg0, u8 *, 6) = (u8) (M2C_FIELD(arg0, u8 *, 6) + 1);
        /* fallthrough */
    case 1:
        temp_v0_2 = M2C_FIELD(arg0, u16 *, 0x40) - 1;
        M2C_FIELD(arg0, u16 *, 0x40) = temp_v0_2;
        if ((temp_v0_2 << 0x10) == 0) {
            M2C_FIELD(arg0, s8 *, 5) = 0;
            M2C_FIELD(arg0, u8 *, 6) = 3U;
            M2C_FIELD(arg0, s8 *, 7) = 0;
            func_80077CFC(arg0, &D_80149A50, 0, 4);
        }
        return;
    }
}

s32 func_8013900C(void *a0)
{
    if (func_8013910C(a0) == 0) {
        return 0;
    }
    return func_8007778C(a0);
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80139040);

s32 func_8013910C(u8 *a)
{
    switch (a[3]) {
    case 0:
        if (D_1F800207 >= 4) {
            return 0;
        }
        break;
    case 1:
        if (D_1F800207 < 11 && D_1F800207 != 7) {
            return 0;
        }
        break;
    case 3:
        if (D_1F800160 >= 0x2EE1) {
            return 0;
        }
        break;
    case 4:
        if (D_1F800207 < 0x19) {
            return 0;
        }
        break;
    }
    return 1;
}

s32 func_801391C4(u8 *a) {
    s16 dz, dx;

    if (D_800E7FFE & 0x8200) {
        return 0;
    }
    dx = *(u16 *)D_1F800160_d288 - M2C_FIELD(a, u16 *, 0x2E);
    dz = *(u16 *)D_1F800164_6889 - M2C_FIELD(a, u16 *, 0x36);
    return func_80077768((s16)-func_80085690(dz, dx), M2C_FIELD(a, s16 *, 0x56), 0) != 0;
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8013924C);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80139458);

extern u8 D_80141434[];
void f_UpdateWaterTempleMermaidAndGearNpcActor(u8 *a)
{
    u8 *g;

    switch (a[4]) {
    case 0:
        g = D_800ECF58;
        if (func_800519E0(a, 0xF, *(s32 *)(g + 0x70), D_80141434) != 0) {
            break;
        }
        *(s32 *)(a + 0x3C) = *(s32 *)(g + 0x38);
        func_80040CDC(a, D_80148790, D_800A3D18);
        a[0x7B] = 1;
        func_80041718(a, 1, 0);
        a[0] = 9;
        *(s16 *)(a + 0x80) = 0x8C;
        *(s16 *)(a + 0x82) = 0x118;
        *(s16 *)(a + 0x84) = 0xC0;
        *(s16 *)(a + 0x86) = 0x180;
        *(s16 *)(a + 0x58) = 0;
        *(s16 *)(a + 0x54) = 0;
        a[0xB] = (a[0xB] & 0xC0) | 0x80;
        switch (a[3]) {
        case 0:
            if (D_800BFA3A != 0) {
                *(s16 *)(a + 0x56) = 0x52E;
            } else {
                *(s16 *)(a + 0x56) = 0xE60;
            }
            break;
        case 1:
            *(s16 *)(a + 0x56) = 0x400;
            break;
        }
        a[0x2B] = 0;
        a[4]++;
        break;
    case 1:
        switch (a[3]) {
        case 0:
            func_8013924C(a);
            break;
        case 1:
            func_80139458(a);
            break;
        }
        if (a[1] != 0) {
            func_800518FC(a);
        }
        a[0x2B] = 0;
        break;
    case 2:
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

extern s32 D_800BF860;
s32 func_801398C0(s32 arg0) {
    D_800BF860 = arg0;
    return 1;
}

extern s32 D_800BF860;
s32 func_801398D0(void) {
    return D_800BF860 == 0;
}

s32 func_801398E0(void *arg0) {
    D_800BF870.pad1[0x1D5] = (D_800BF870.pad1[0x1D5] | (1 << M2C_FIELD(arg0, u8 *, 0x47))) & 0xEF;
    func_80074590(0x1A, 0x1B, 0);
    return 1;
}

extern u8 D_800BFA35;
extern s16 D_1F800190;
extern s16 D_1F800192;
extern s16 D_1F80016C;
s32 func_8013992C(u8 *a)
{
    u8 *t;
    switch (a[0x78]) {
    case 0:
        D_1F800190 = 0;
        D_1F800192 = 0;
        t = D_800E7E80;
        t[5] = 0x1F;
        t[6] = 0;
        a[0x78]++;
        break;
    case 1:
        D_1F800190 = D_1F80016C;
        if (D_800BFA35 == 3) {
            return 1;
        }
        break;
    }
    return 0;
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_801399B4);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80139A9C);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80139CEC);

extern u8 D_800BF8E1;
extern u8 D_801474AC[];
extern u8 D_800A3D70[];
extern u8 D_8014744C[];
extern u8 D_80147434[];
void func_80139E58(u8 *a)
{
    u8 *b;
    u8 *t;

    b = P(a, 0x14);
    switch (a[5]) {
    case 0:
        func_8007778C(a);
        if (D_800BFA42 == 0x80) {
            D_800BF841 = 0;
            t = D_800E7E80;
            H(t, 0x2E) = 0x3545;
            H(t, 0x32) = -0x168C;
            H(t, 0x36) = 0x1040;
            t[0x2A] = 0x21;
            t[4] = 4;
            t[5] = 0x18;
            t[6] = 4;
            func_80040D68(a, D_801474AC);
            a[0x70] = 2;
            a[6] = 2;
            a[5] = 1;
        } else if (a[0x2B] == 3) {
            func_80042354(1, 2);
            func_80040D68(a, D_800A3D70);
            a[0x70] = 2;
            a[6] = 0;
            a[5]++;
        }
        break;
    case 1:
        a[1] = 1;
        func_80077E7C(a);
        func_80041098(a);
        if (a[0x70] == 0xFF) {
            switch (a[6]) {
            case 0:
                if (D_800BF8E1 == 0) {
                    func_80040D68(a, D_8014744C);
                } else {
                    a[0x7A] = 1;
                    func_80040D68(a, D_80147434);
                }
                a[0x70] = 2;
                a[6]++;
                break;
            case 1:
                a[5] = 0;
                break;
            case 2:
                a[4] = 3;
                break;
            }
        }
        break;
    }
    switch (a[0x5F]) {
    case 0:
        H(b, 0x2E) = H(a, 0x2E);
        H(b, 0x32) = H(a, 0x32) + 0x12C;
        H(b, 0x36) = H(a, 0x36);
        break;
    case 1:
        H(b, 0x2E) = (W_d1fb(P(a, 0xD0), 0x2C) + W_d1fb(P(a, 0xDC), 0x2C)) / 2;
        H(b, 0x32) = (W_d1fb(P(a, 0xD0), 0x30) + W_d1fb(P(a, 0xDC), 0x30)) / 2;
        H(b, 0x36) = (W_d1fb(P(a, 0xD0), 0x34) + W_d1fb(P(a, 0xDC), 0x34)) / 2;
        H(b, 0x56) = (H(a, 0x56) - 0x400) & 0xFFF;
        H(b, 0x2E) += (func_80083F50(H(a, 0x56)) * 40) >> 12;
        H(b, 0x36) += (-func_80083E80(H(a, 0x56)) * 40) >> 12;
        H(b, 0x2E) += 3 - (func_8009A450() & 7);
        H(b, 0x32) += 7 - (func_8009A450() & 0xF);
        H(b, 0x36) += 3 - (func_8009A450() & 7);
        break;
    case 2:
        H(b, 0x2E) = 0x3425;
        H(b, 0x36) = 0x1033;
        H(b, 0x32) += 0x10;
        if (H(b, 0x32) >= -0x15FE) {
            func_80074590(0xE, -0x10, 0);
            D_800BFA42 = 0x83;
            H(b, 0x32) = -0x15FE;
            a[0x5F] = 3;
        }
        break;
    }
    func_8004190C(a);
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8013A208);

extern u8 D_80141524[];
void func_8013A398(u8 *a)
{
    u8 *g;

    switch (a[4]) {
    case 0:
        g = D_800ECF58;
        if (func_800519E0(a, 0xF, *(s32 *)(g + 0x78), D_80141524) != 0) {
            break;
        }
        func_80051B04(*(u8 **)(a + 0xC0), 0x1E, 0xF);
        func_80051B04(*(u8 **)(a + 0xE0), 0x1E, 0x10);
        *(s32 *)(a + 0x3C) = *(s32 *)(g + 0x38);
        func_80040CDC(a, D_80148790, D_800A3D18);
        a[0x7B] = 0;
        func_80041718(a, 0, 0);
        a[0] = 9;
        *(s16 *)(a + 0x80) = 0x8C;
        *(s16 *)(a + 0x82) = 0x118;
        *(s16 *)(a + 0x84) = 0xC0;
        *(s16 *)(a + 0x86) = 0x156;
        *(s16 *)(a + 0x58) = 0;
        *(s16 *)(a + 0x54) = 0;
        switch (a[3]) {
        case 0:
            *(s16 *)(a + 0x56) = 0x400;
            *(void **)(a + 0x14) = func_8012B89C(a, 0);
            break;
        case 1:
            func_801291BC(a);
            *(s16 *)(a + 0x56) = 0x2A8;
            a[0xB] = (a[0xB] & 0xC0) | 0x80;
            break;
        }
        a[0x2B] = 0;
        a[4]++;
        break;
    case 1:
        switch (a[3]) {
        case 0:
            func_80139E58(a);
            break;
        case 1:
            func_8013A208(a);
            break;
        }
        if (a[1] != 0) {
            func_800518FC(a);
        }
        a[0x2B] = 0;
        break;
    case 2:
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8013A578);

s32 func_8013A630(u8 *a)
{
    switch (a[0x78]) {
    default:
        return 0;
    case 0:
        a[0x5F] = 2;
        a[0x78]++;
        break;
    case 1:
        if (a[0x5F] == 3) {
            func_80041718(a, 0, 0);
            return 1;
        }
        return 0;
    }
    return 0;
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8013A6A8);

extern s32 D_800BF854;
extern u8 D_800BFB04;
extern u8 D_80147604[];
extern u8 D_80147644[];
extern u8 D_80147664[];
extern u8 D_8014766C[];
extern u8 D_801476AC[];
s32 func_8013A7D4(u8 *a)
{
    u8 *g;

    switch (a[6]) {
    case 0:
        if (D_800BF80F == 0) {
            a[6]++;
            func_80042354(1, 2);
            func_80040CDC(a, D_80148790, D_80147604);
            a[0x70] = 1;
        }
        break;
    case 1:
        func_80041098(a);
        if (a[0x70] == 0xFF) {
            a[6]++;
            g = (u8 *)&D_800BF870;
            if ((*(u16 *)(g + 0x2E) & 0x200) || (g[0x11] & 4)) {
                func_80040CDC(a, D_80148790, D_80147664);
                a[0xBF] = 1;
            } else {
                func_80040CDC(a, D_80148790, D_80147644);
                a[0xBF] = 0;
            }
            a[0x70] = 1;
        }
        break;
    case 2:
        func_80041098(a);
        if (a[0x70] == 0xFF) {
            if (D_800BFB04 != 0 && a[0xBF] == 0) {
                a[6] = 0;
                func_80040CDC(a, D_80148790, D_801476AC);
                a[0x70] = 1;
                return 2;
            }
            a[6]++;
            func_80040CDC(a, D_80148790, D_8014766C);
            a[0x70] = 1;
        }
        break;
    case 3:
        func_80041098(a);
        if (a[0x70] == 0xFF) {
            a[6]++;
            func_80042310();
            D_1F800137 = 2;
        }
        break;
    case 4:
        if (D_800E806E == 3) {
            a[6]++;
            D_800BF854 = 1;
        }
        break;
    }
    return 0;
}

extern u8 D_80147694[];
extern u8 D_8014767C[];
extern u8 D_801478E4[];
extern u8 D_80147924[];
extern u8 D_8014791C[];
/* func_8013AF48, inlined */
static inline void func_8013AF48_inl(u8 *a)
{
    s32 s = a[6];
    u8 *g;

    switch (s) {
    case 0:
        if (D_800BF80F == 0) {
            {
                s32 one = 1;
                a[6] = one;
                func_80042354(one, 2);
            }
            g = (u8 *)&D_800BF870;
            if ((*(u16 *)(g + 0x2E) & 0x200) || (g[0x11] & 4)) {
                func_80040CDC(a, D_80148790, D_80147694);
            } else {
                func_80040CDC(a, D_80148790, D_8014767C);
            }
            a[0x70] = 1;
        }
        break;
    case 1:
        func_80041098(a);
        if (a[0x70] == 0xFF) {
            a[6]++;
            func_80042310();
            D_1F800137 = 2;
            D_800BF854 = s;
        }
        break;
    }
}
/* func_8013B058, inlined */
static inline s32 func_8013B058_inl(u8 *a)
{
    switch (a[6]) {
    case 0:
        if (D_800BF80F != 0) {
            return 0;
        }
        {
            s32 one = 1;
            a[6] = one;
            func_80042354(one, 2);
        }
        func_80040CDC(a, D_80148790, D_801478E4);
        a[0x70] = 1;
        break;
    case 1:
        func_80041098(a);
        if (a[0x70] != 0xFF) {
            return 0;
        }
        a[6] = 0;
        func_80042310();
        return 1;
    }
    return 0;
}
/* func_8013B110, inlined */
static inline void func_8013B110_inl(u8 *a)
{
    switch (a[6]) {
    case 0:
        if (a[0x2B] == 3) {
            {
                s32 one = 1;
                a[6] = one;
                func_80042354(one, 2);
            }
            if (D_800BF928 == 0xFF) {
                func_80040CDC(a, D_80148790, D_80147924);
            } else {
                func_80040CDC(a, D_80148790, D_8014791C);
            }
            a[0x70] = 1;
        }
        break;
    case 1:
        func_80041098(a);
        if (a[0x70] == 0xFF) {
            a[6] = 0;
            func_80042310();
        }
        break;
    }
}
void func_8013A9F8(u8 *a)
{
    s32 one = 1;
    u8 *g;
    u8 *h;

    switch (a[4]) {
    case 0:
        g = D_800ECF58;
        if (func_800519E0(a, 0xF, *(s32 *)(g + 0x78), D_80141524) != 0) {
            break;
        }
        *(s32 *)(a + 0x3C) = *(s32 *)(g + 0x38);
        func_80077C40(a, D_80148790, 0);
        a[0] = 9;
        *(s16 *)(a + 0x80) = 0x50;
        *(s16 *)(a + 0x82) = 0xA0;
        *(s16 *)(a + 0x84) = 0xC0;
        *(s16 *)(a + 0x86) = 0x156;
        *(s16 *)(a + 0x56) = 0x800;
        h = (u8 *)&D_800BF870;
        *(s16 *)(a + 0x54) = 0;
        *(s16 *)(a + 0x58) = 0;
        a[0x2B] = 0;
        a[0x29] = 0;
        a[4]++;
        if (h[0xB2] == 0xFF) {
            a[5] = 3;
            *(s16 *)(a + 0x32) = -0xF1E;
            *(s16 *)(a + 0x36) = 0x1602;
        } else if (h[0xB2] == 0) {
            a[5] = 0;
        } else if (!(*(u16 *)(h + 0x2E) & 0x200) && !(h[0x11] & 4) && h[0x294] != 0) {
            a[5] = 2;
        } else {
            a[5] = one;
        }
        break;
    case 1:
        func_8007778C(a);
        func_8004190C(a);
        switch (a[5]) {
        case 0:
            if (func_8013A7D4(a) == 2) {
                a[5] = 2;
                a[6] = 1;
            }
            break;
        case 1:
            func_8013AF48_inl(a);
            break;
        case 2:
            if (func_8013B058_inl(a) != 0) {
                a[5]++;
            }
            break;
        case 3:
            func_8013B110_inl(a);
            break;
        }
        func_800518FC(a);
        a[0x2B] = 0;
        if (D_800BF922 != 0xFF) {
            a[1] = 0;
        }
        break;
    case 2:
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

extern u8 D_800BFB28;
s32 func_8013AE4C(u8 *p)
{
    if (D_800BFB28 == 0) {
        p[0x7A] = 0xA;
    } else {
        p[0x7A] = 0xF;
    }
    return 1;
}

s32 func_8013AE78(void *a0)
{
    u8 *r = func_80072DDC(a0, 2, 3, 0x10);

    if (r != 0) {
        *(void **)(r + 0x1C) = f_UpdateWaterTempleQuestPropActor;
        r[3] = 0x1A;
        r[0x28] |= 0x80;
        func_8004D604(0x50, 1);
        return 1;
    }
    return 0;
}

s32 func_8013AEE0(void *a0)
{
    S13AE38 v;
    u8 *e;

    e = D_800E7E80;
    v.a = *(s16 *)(e + 0x2E);
    v.b = *(s16 *)(e + 0x32) - 0xC8;
    v.c = 0x15ED;
    func_80070F00(a0, 1, &v);
    func_800708B4(3);
    return 1;
}

s32 func_8013AF30(void) {
    return M2C_FIELD(*(void **)0x1F800214, u8 *, 3) == 0;
}

void func_8013AF48(u8 *a)
{
    s32 s = a[6];
    u8 *g;

    switch (s) {
    case 0:
        if (D_800BF80F == 0) {
            {
                s32 one = 1;
                a[6] = one;
                func_80042354(one, 2);
            }
            g = (u8 *)&D_800BF870;
            if ((*(u16 *)(g + 0x2E) & 0x200) || (g[0x11] & 4)) {
                func_80040CDC(a, D_80148790, D_80147694);
            } else {
                func_80040CDC(a, D_80148790, D_8014767C);
            }
            a[0x70] = 1;
        }
        break;
    case 1:
        func_80041098(a);
        if (a[0x70] == 0xFF) {
            a[6]++;
            func_80042310();
            D_1F800137 = 2;
            D_800BF854 = s;
        }
        break;
    }
}

s32 func_8013B058(u8 *a)
{
    switch (a[6]) {
    case 0:
        if (D_800BF80F != 0) {
            return 0;
        }
        {
            s32 one = 1;
            a[6] = one;
            func_80042354(one, 2);
        }
        func_80040CDC(a, D_80148790, D_801478E4);
        a[0x70] = 1;
        break;
    case 1:
        func_80041098(a);
        if (a[0x70] != 0xFF) {
            return 0;
        }
        a[6] = 0;
        func_80042310();
        return 1;
    }
    return 0;
}

void func_8013B110(u8 *a)
{
    switch (a[6]) {
    case 0:
        if (a[0x2B] == 3) {
            {
                s32 one = 1;
                a[6] = one;
                func_80042354(one, 2);
            }
            if (D_800BF928 == 0xFF) {
                func_80040CDC(a, D_80148790, D_80147924);
            } else {
                func_80040CDC(a, D_80148790, D_8014791C);
            }
            a[0x70] = 1;
        }
        break;
    case 1:
        func_80041098(a);
        if (a[0x70] == 0xFF) {
            a[6] = 0;
            func_80042310();
        }
        break;
    }
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8013B1DC);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8013B32C);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8013B49C);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8013B6FC);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8013B9F8);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8013BB64);

extern u8 D_801414AC[];
void func_8013BCAC(u8 *a)
{
    u8 *g;

    switch (a[4]) {
    case 0:
        g = D_800ECF58;
        if (func_800519E0(a, 0xF, *(s32 *)(g + 0x3C), D_801414AC) != 0) {
            break;
        }
        *(s32 *)(a + 0x3C) = *(s32 *)(g + 0x38);
        func_80040CDC(a, D_80148790, D_800A3D18);
        a[0x7B] = 0;
        func_80041718(a, 0, 0);
        a[0] = 9;
        *(s16 *)(a + 0x80) = 0x8C;
        *(s16 *)(a + 0x82) = 0x118;
        *(s16 *)(a + 0x84) = 0xC0;
        *(s16 *)(a + 0x86) = 0x180;
        *(s16 *)(a + 0x58) = 0;
        *(s16 *)(a + 0x54) = 0;
        *(s16 *)(a + 0x42) = 0;
        a[0xB] = (a[0xB] & 0xC0) | 0x80;
        switch (D_800BFA43) {
        case 0:
            a[0] = 2;
            *(s16 *)(a + 0x84) = 0x7D0;
            *(s16 *)(a + 0x86) = 0x890;
            *(s16 *)(a + 0x56) = 0x92E;
            a[0x5E] = 0;
            break;
        case 1:
            *(s16 *)(a + 0x2E) = 0x3911;
            *(s16 *)(a + 0x32) = -0x231C;
            *(s16 *)(a + 0x36) = 0x23A8;
            *(s16 *)(a + 0x56) = 0xD2A;
            a[0x5E] = 1;
            break;
        case 2:
        default:
            a[0] = 2;
            *(s16 *)(a + 0x2E) = 0x3731;
            *(s16 *)(a + 0x32) = -0x231C;
            *(s16 *)(a + 0x36) = 0x2008;
            *(s16 *)(a + 0x56) = 0x52A;
            if (D_800BFA43 == 2) {
                a[0x5E] = 2;
            } else {
                func_800312D4(0x90C, a + 0x2C, -0xA);
                a[0x5E] = 3;
            }
            break;
        }
        a[0x2B] = 0;
        a[4]++;
        break;
    case 1:
        switch (a[0x5E]) {
        case 0:
            func_8013B1DC(a);
            break;
        case 1:
            func_8013B32C(a);
            break;
        case 2:
            func_8013B9F8(a);
            break;
        case 3:
            func_8013BB64(a);
            break;
        }
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

extern u8 D_800BFA38;
s32 func_8013BF30(u8 *a)
{
    void *r;
    switch (a[0x78]) {
    default:
        return 0;
    case 0:
        r = func_801238D0(a, 4);
        if (r != 0) {
            D_800BFA38 = 2;
            *(void **)(a + 0x14) = r;
            func_800440E4(D_800E7E80, 0xCF, 2);
            a[0x78]++;
        }
        break;
    case 1:
        if (D_800BF80E != 0) {
            return 1;
        }
        break;
    }
    return 0;
}

s32 func_8013BFD0(void *arg0) {
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x14), s8 *, 5) = 1;
    return 1;
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8013BFE4);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8013C170);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8013C354);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8013C530);

extern u8 D_800BFA36;
void func_8013C6B4(u8 *a)
{
    u8 *g;
    s32 k;

    switch (a[4]) {
    case 0:
        g = D_800ECF58;
        if (func_800519E0(a, 0xF, *(s32 *)(g + 0x78), D_80141524) != 0) {
            break;
        }
        func_80051B04(*(u8 **)(a + 0xC4), 0x1E, 0x11);
        *(s32 *)(a + 0x3C) = *(s32 *)(g + 0x38);
        func_80040CDC(a, D_80148790, D_800A3D18);
        a[0x7B] = 2;
        func_80041718(a, 2, 0);
        k = 0x80;
        a[0xB] = k;
        a[0] = 9;
        *(s16 *)(a + 0x82) = 0x100;
        *(s16 *)(a + 0x84) = 0xA0;
        *(s16 *)(a + 0x86) = 0x136;
        *(s16 *)(a + 0x56) = 0x6D2;
        *(s16 *)(a + 0x80) = k;
        *(s16 *)(a + 0x58) = 0;
        *(s16 *)(a + 0x54) = 0;
        if (D_800BFA36 != 2) {
            a[0x5E] = 0;
        } else {
            a[0x5E] = 1;
        }
        a[0x2B] = 0;
        a[4]++;
        break;
    case 1:
        switch (a[0x5E]) {
        case 0:
            func_8013C354(a);
            break;
        case 1:
            func_8013C530(a);
            break;
        }
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

s32 func_8013C860(u8 *p)
{
    u8 *a = D_800BF844;

    a[5] = 1;
    a[0x5E] = 0;
    *(s16 *)(a + 0x60) = 0;
    a[6] = 0;
    *(s16 *)(p + 0x48) = *(s16 *)(a + 0x2E) = 0x1A90;
    *(s16 *)(p + 0x4A) = *(s16 *)(a + 0x32) = -0x125E;
    *(s16 *)(p + 0x4C) = *(s16 *)(a + 0x36) = 0x2CEC;
    return 1;
}

extern u8 D_80141614[];
void func_8013CAC0(void *arg0);
void func_8013CB14(u8 *a);
void func_8013CB70(u8 *p);
void func_8013C8A8(u8 *a)
{
    u8 *g;
    u8 *st;
    u8 v;

    switch (a[4]) {
    case 0:
        g = D_800ECF58;
        if (func_800519E0(a, 0xF, *(s32 *)(g + 0x3C), D_80141614) != 0) {
            break;
        }
        *(s32 *)(a + 0x3C) = *(s32 *)(g + 0x38);
        func_80040CDC(a, D_80148790, D_800A3D90_b2d8);
        func_80041718(a, 0xB, 0);
        *(s16 *)(a + 0x56) = 0x140;
        st = (u8 *)&D_800BF870;
        v = st[0xCD];
        if (v == 0xFF) {
            a[0x5E] = 3;
            func_80041768(a, 0, 0);
        } else if (!(v & 0x40)) {
            a[0x5E] = 0;
        } else if (st[0x2E9] != 0) {
            a[0x5E] = 2;
        } else {
            a[0x5E] = 1;
        }
        a[0] = 9;
        *(s16 *)(a + 0x80) = 0x8C;
        *(s16 *)(a + 0x82) = 0x118;
        *(s16 *)(a + 0x84) = 0x50;
        *(s16 *)(a + 0x86) = 0x90;
        a[0x2B] = 0;
        a[0x29] = 0;
        *(s16 *)(a + 0x54) = 0;
        *(s16 *)(a + 0x56) = 0x800;
        *(s16 *)(a + 0x58) = 0;
        a[4]++;
        break;
    case 1:
        a[1] = 1;
        func_80077E7C(a);
        func_80041098(a);
        func_8004190C(a);
        switch (a[5]) {
        case 0:
            func_8013CAC0(a);
            break;
        case 1:
            func_8013CB14(a);
            break;
        case 2:
            func_8013CB70(a);
            break;
        }
        a[0x2B] = 0;
        func_800518FC(a);
        break;
    case 2:
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

extern M2C_UNK D_800A3D90;
void func_8013CAC0(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x2B) == 3) {
        func_80042354(1, 1);
        func_80040D68(arg0, &D_800A3D90);
        M2C_FIELD(arg0, s8 *, 0x70) = 1;
        M2C_FIELD(arg0, s8 *, 5) = 1;
    }
}

extern void *D_80147E24[];
void func_8013CB14(u8 *a)
{
    if (a[0x71] == 0xFF) {
        func_80040D68(a, D_80147E24[a[0x5E]]);
        a[5] = 2;
        a[0x70] = 1;
    }
}

void func_8013CB70(u8 *p)
{
    u8 *g;

    if (p[0x71] == 0xFF) {
        switch (p[0x5E]) {
        case 0:
            g = (u8 *)&D_800BF870;
            g[0xCD] |= 0x40;
        case 2:
            p[0x5E]++;
            break;
        }
        p[5] = 0;
    }
}

extern u8 D_800BFB59;
s32 func_8013CBD4(u8 *a)
{
    if (D_800BFB59 != 0) {
        a[0x5E] = 0x2;
        return 3;
    }
    return 2;
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8013CBFC);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8013CF34);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8013D178);

extern u8 D_80141814[];
extern u8 D_80149E30[];
void func_8013D3C0(u8 *a)
{
    u8 *g;

    switch (a[4]) {
    case 0:
        g = D_800ECF58;
        if (func_800519E0(a, 7, *(s32 *)(g + 0x84), D_80141814) != 0) {
            break;
        }
        *(s32 *)(a + 0x3C) = *(s32 *)(g + 0x88);
        func_80051B04(*(u8 **)(a + 0xD8), 0x21, 7);
        func_80040CDC(a, D_80149E30, D_800A3D18);
        func_80041718(a, 0, 0);
        a[0] = 2;
        a[0x2B] = 0;
        a[0x29] = 0;
        *(s16 *)(a + 0x54) = 0;
        *(s16 *)(a + 0x56) = 0x568;
        *(s16 *)(a + 0x58) = 0;
        a[4]++;
        break;
    case 1:
        func_8013D178(a);
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

s32 func_8013D4EC(void *arg0) {
    u16 temp_v0;

    if ((D_800BF80E != 0) || (temp_v0 = M2C_FIELD(arg0, u16 *, 0x72), M2C_FIELD(arg0, u16 *, 0x72) = (u16) (temp_v0 - 1), ((temp_v0 << 0x10) <= 0))) {
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8013D528);

s32 func_8013D614(u8 *p)
{
    s32 i = 0;

    p[0xD] |= 4;
    for (; i < p[9]; i++) {
        (*(u8 **)(p + 0xC0 + i * 4))[0x3F] = 0xF1;
    }
    return 1;
}

s32 func_8013D65C(void *arg0) {
    M2C_FIELD(arg0, u16 *, 0x58) = (u16) M2C_FIELD(arg0, u16 *, 0x72);
    return 1;
}

typedef struct { u16 a, b; } Range;
extern Range D_80147FB4[];
extern Range D_80147FCC[];
extern Range D_8014800C[];
extern Range D_80148080[];
extern Range D_801480C0[];
extern Range D_80148100[];
extern Range D_80148148[];
extern Range D_80148188[];
extern Range D_801481F0[];
extern Range D_8014820C[];
extern Range D_80148288[];
extern Range D_80148330[];
extern Range D_80148368[];
extern Range D_801483A4[];
extern Range D_801483D0[];
extern Range D_80148414[];
extern Range D_8014846C[];
extern Range D_801484C4[];
extern Range D_8014851C[];
extern u8 *D_1F80021C;
void func_8013D670(s16 kind, s16 idx)
{
    Range *t;
    s32 n, base;
    u8 *p;
    switch (kind) {
    case 0:
        t = D_80147FB4;
        n = 0x3;
        base = 0;
        break;
    case 1:
        t = D_80147FCC;
        n = 0xC;
        base = 0;
        break;
    case 2:
        t = D_8014800C;
        n = 0xC;
        base = 0x2CF;
        break;
    case 3:
        t = D_80148080;
        n = 0xE;
        base = 0x43F;
        break;
    case 4:
        t = D_801480C0;
        n = 0x1C;
        base = 0x3F6;
        break;
    case 5:
        t = D_80148100;
        n = 0x19;
        base = 0x310;
        break;
    case 6:
        t = D_80148148;
        n = 0x15;
        base = 0x3E3;
        break;
    case 7:
        t = D_80148188;
        n = 0x1E;
        base = 0x379;
        break;
    case 8:
        t = D_801481F0;
        n = 0x6;
        base = 0x472;
        break;
    case 9:
        t = D_8014820C;
        n = 0xA;
        base = 0x143;
        break;
    case 10:
        t = D_80148288;
        n = 0x2;
        base = 0x61;
        break;
    case 11:
        t = D_80148330;
        n = 0xD;
        base = 0x3B3;
        break;
    case 12:
        t = D_80148368;
        n = 0x18;
        base = 0x1B4;
        break;
    case 13:
        t = D_801483A4;
        n = 0x7;
        base = 0x3EF;
        break;
    case 14:
        t = D_801483D0;
        n = 0x12;
        base = 0x2CA;
        break;
    case 15:
        t = D_80148414;
        n = 0x1D;
        base = 0x36C;
        break;
    case 16:
        t = D_8014846C;
        n = 0x11;
        base = 0x31C;
        break;
    case 17:
        t = D_801484C4;
        n = 0x18;
        base = 0x3AA;
        break;
    case 18:
        t = D_8014851C;
        n = 0x2;
        base = 0x42D;
        break;
    default:
        return;
    }
    p = D_1F80021C + t[idx].a * 32 + base * 32;
    func_8001D2A8(n, p, p + (t[idx].b + 1) * 32, 0);
}

extern u16 D_8014853C[];
void func_8013D874(u8 *a)
{
    s32 x;
    s32 z;
    s16 n;

    switch (a[5]) {
    case 0:
        *(s16 *)(a + 0x50) = 0;
        *(s16 *)(a + 0x40) = 0x3C;
        a[5]++;
        a[3] = func_8009A450() & 7;
    case 1:
        if (--*(s16 *)(a + 0x40) == -1) {
            *(s16 *)(a + 0x50) = 0;
            a[5]++;
            *(s16 *)(a + 0x40) = a[3] * 10;
        } else {
            *(s16 *)(a + 0x32) -= 4;
            *(s32 *)(a + 0x30) -= func_80083E80(*(s16 *)(a + 0x50)) * 0xC0;
            *(s16 *)(a + 0x50) += 0x80;
            *(s16 *)(a + 0x36) += D_8014853C[a[3]];
        }
        break;
    case 2:
        if (*(s16 *)(a + 0x40) != 0) {
            *(s32 *)(a + 0x30) -= func_80083E80(*(s16 *)(a + 0x50)) << 7;
            *(s16 *)(a + 0x50) += 0x100;
            *(s16 *)(a + 0x40) -= 1;
        } else {
            a[5]++;
        }
        break;
    case 3:
        a[5]++;
        MEMBER_AT(s16, a, 0x50) = -0x1800;
        MEMBER_AT(s16, a, 0x52) = 0x400;
        MEMBER_AT(s16, a, 0x40) = 8;
        MEMBER_AT(s16, a, 0x4A) = ((D_1F800162 - *(s16 *)(a + 0x32) - 0xFA) * 16) / *(s16 *)(a + 0x40);
        MEMBER_AT(s16, a, 0x4C) = ((D_1F800164 - *(s16 *)(a + 0x36)) * 16) / *(s16 *)(a + 0x40);
    case 4:
        *(s32 *)(a + 0x30) += *(s16 *)(a + 0x4A) << 12;
        *(s32 *)(a + 0x30) += *(s16 *)(a + 0x50) << 8;
        *(s32 *)(a + 0x34) += *(s16 *)(a + 0x4C) << 12;
        *(s16 *)(a + 0x50) += *(s16 *)(a + 0x52);
        if (--*(s16 *)(a + 0x40) == -1) {
            a[5]++;
        }
        break;
    case 5:
        a[5]++;
        if (func_8009A450() & 1) {
            *(s16 *)(a + 0x52) = 0;
        } else {
            *(s16 *)(a + 0x52) = 0x800;
        }
        *(s16 *)(a + 0x50) = 0;
        break;
    case 6:
        x = *(u16 *)&D_1F800162;
        z = *(u16 *)&D_1F800164;
        *(s16 *)(a + 0x32) = x - 0xFA;
        *(s16 *)(a + 0x36) = z;
        *(s32 *)(a + 0x30) += func_80083E80(*(s16 *)(a + 0x50)) << 11;
        if (a[3] & 1) {
            *(s16 *)(a + 0x44) = (func_80083E80(*(s16 *)(a + 0x52)) * 0xC0) >> 4;
        } else {
            *(s16 *)(a + 0x44) = (func_80083E80(*(s16 *)(a + 0x52)) * 0xA0) >> 4;
        }
        *(s16 *)(a + 0x50) += 0x28;
        *(s16 *)(a + 0x52) += 0x18;
        *(s32 *)(a + 0x34) += *(s16 *)(a + 0x4C) * *(s16 *)(a + 0x44);
        break;
    }
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8013DC04);

void func_8013DC04();
u8 *func_8013DD48(u8 *a, s32 b) {
    u8 *p = func_80072DDC(0, 0, 2, 71);

    if (p != NULL) {
        M2C_FIELD(p, void **, 0x1C) = func_8013DC04;
        p[0x3] = b;
        p[0x28] = (p[0x28] | 0x80);
        M2C_FIELD(p, s16 *, 0x2E) = M2C_FIELD(a, u16 *, 0x2);
        M2C_FIELD(p, s16 *, 0x32) = M2C_FIELD(a, u16 *, 0x6);
        M2C_FIELD(p, s16 *, 0x36) = M2C_FIELD(a, u16 *, 0xA);
    }
    return p;
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8013DDD4);

typedef struct {
    u8 x0;
    u8 x1;
    u8 x2;
    u8 x3;
    s32 x4;
    void *x8;
    void *xC;
    u8 *x10;
    u8 *x14;
    s16 x18;
    s16 x1A;
    s32 x1C;
    s32 x20;
    s32 x24;
    s32 x28;
    s32 x2C;
    s32 x30;
    s32 x34;
    s32 x38;
    u8 x3C;
    u8 x3D;
    u8 x3E;
    u8 x3F;
    u8 x40;
    u8 x41;
    u8 x42;
    u8 x43;
    u8 x44;
    u8 x45;
    u8 x46;
    u8 x47;
    u8 x48[2];
    u8 x4A[2];
    u8 x4C[2];
    u8 x4E[2];
    u8 x50;
    u8 x51;
    u8 sel;
    u8 x53;
    s16 x54;
    s16 x56;
    s16 x58;
    u8 x5A;
    u8 x5B;
} CrdMenu;
extern CrdMenu D_800BF498;
static inline u8 crd_card_event_wait(void)
{
    if (func_80080840(D_800BF498.x1C) == 1) {
        return 1;
    }
    if (func_80080840(D_800BF498.x20) == 1) {
        return 2;
    }
    if (func_80080840(D_800BF498.x24) == 1) {
        return 3;
    }
    if (func_80080840(D_800BF498.x28) == 1) {
        return 4;
    }
    if (++D_800BF498.x43 >= 0xFF) {
        return 2;
    }
    return 0;
}
typedef struct { s16 x; s16 y; u16 w; s16 h; } CrdRect;
typedef struct { u8 b[0x5F4]; } CrdSaveBlk;
u8 func_8013E038(CrdMenu *a)
{
    s32 port = a->x3D << 4;
    s32 one = 1;
    u8 r;
    switch (a->x40) {
    case 0:
        func_8009BA90(port);
        a->x40 = one;
        a->x43 = 0;
        a->x41 = 0xFF;
        break;
    case 1:
        r = crd_card_event_wait();
        if (r == 0) {
            break;
        }
        switch (r) {
        case 4:
            if (((u8 *)a + a->x3D)[0x4A] == 0) {
                a->x42 = 0;
                break;
            }
            func_80080840(D_800BF498.x2C);
            func_80080840(D_800BF498.x30);
            func_80080840(D_800BF498.x34);
            func_80080840(D_800BF498.x38);
            func_8009BAB0(port);
            while (1) {
                if (func_80080840(D_800BF498.x2C) == 1) {
                    break;
                }
                if (func_80080840(D_800BF498.x30) == 1) {
                    break;
                }
                if (func_80080840(D_800BF498.x34) == 1) {
                    break;
                }
                if (func_80080840(D_800BF498.x38) == 1) {
                    break;
                }
            }
            a->x42 = 1;
            ((u8 *)a + a->x3D)[0x48] = 0;
            ((u8 *)a + a->x3D)[0x4E] = 0xFF;
            break;
        case 1:
            a->x42 = 0;
            break;
        case 2 ... 3:
            a->x42 = 0xFE;
            ((u8 *)a + a->x3D)[0x48] = 0;
            ((u8 *)a + a->x3D)[0x4E] = 0xFF;
            break;
        }
        a->x41 = a->x42;
        ((u8 *)a + a->x3D)[0x4A] = a->x41;
        a->x40 = 0;
        a->x3D = 1 - a->x3D;
        break;
    case 2:
        break;
    }
    return a->x41;
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8013E278);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8013E3E0);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8013E638);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8013EB88);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8013F03C);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8013F150);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8013F40C);

extern u8 *D_800A2854[];
void func_8013F57C(u8 *a)
{
    s16 ids[2] = { 0x2E, 0x2F };
    CrdRect r;
    s32 i, col, mode;
    u8 *str;
    if (*(u8 *)D_800BF498.xC != 0) {
        return;
    }
    r.h = 0x10;
    for (i = 0; i < 2; i++) {
        if ((a + i)[0x4A] >= 3) {
            continue;
        }
        str = D_800A2854[ids[i]];
        r.x = 0x50 - func_8009A600(str) * 4;
        if (i != 0) {
            r.x += 0xA0;
        }
        r.y = 0x64;
        r.w = 0;
        if (a[0x44] == i + 1) {
            col = 0;
            mode = 0x40;
        } else {
            col = 6;
            mode = 0x60;
        }
        func_80079374((s16)(r.x + r.w), r.y, col, str, 3);
        r.w *= 2;
        r.w += func_8009A600(str) << 3;
        func_8005019C(&r, mode, 0, 3);
    }
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8013F6E4);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8013F8B4);

#define CRD_MSG(id, msg)                     \
    {                                        \
        CrdMenu *s;                          \
        s32 w, m;                            \
        w = id;                              \
        s = &D_800BF498;                     \
        m = -1;                              \
        if (s->x18 != w) {                   \
            func_8009A5B0(s->xC, msg);       \
            s->x18 = w;                      \
        }                                    \
        if (s->x1A != m) {                   \
            *s->x10 = 0;                     \
            s->x1A = m;                      \
        }                                    \
    }
#define CRD_MSG2(id, msg)                    \
    {                                        \
        CrdMenu *s;                          \
        s32 w, m;                            \
        m = -1;                              \
        s = &D_800BF498;                     \
        w = id;                              \
        if (s->x18 != m) {                   \
            *(u8 *)s->xC = 0;                \
            s->x18 = m;                      \
        }                                    \
        if (s->x1A != w) {                   \
            func_8009A5B0(s->x10, msg);      \
            s->x1A = w;                      \
        }                                    \
    }
extern s32 D_800A2914;
extern s32 D_800A2918;
extern s32 D_800A292C;
void func_8013FA00(u8 *a)
{
    u8 mask;
    u16 p;
    mask = a[0x4A] < 3;
    if (a[0x4B] < 3) {
        mask |= 2;
    }
    if (mask != 0) {
        if (a[0x44] == 0) {
            a[0x44] = 1;
        }
        if ((D_800E7E68 & 0x80) && (mask & 1) && a[0x44] != 1) {
            func_80074590(0x15, 0, 0);
            a[0x44] = 1;
        }
        if ((D_800E7E68 & 0x20) && (mask & 2) && a[0x44] != 2) {
            func_80074590(0x15, 0, 0);
            a[0x44] = 2;
        }
        if (!(a[0x44] & mask)) {
            a[0x44] = mask;
        }
        CRD_MSG2(0x36, D_800A292C);
    } else {
        a[0x44] = 0;
        CRD_MSG(0x31, D_800A2918);
    }
    if (D_800E7E68 & 0x2000) {
        func_8001CBA8(a, 0);
        func_8001CBA8(a, 1);
        *(u16 *)(D_1F800138_5432 + 0x50) = 2;
    }
    p = D_800E7E68;
    if (p & 0x1000) {
        func_8001CBA8(a, 0);
        func_8001CBA8(a, 1);
        *(u16 *)(D_1F800138_5432 + 0x50) = 3;
        return;
    }
    if ((p & 0x4000) && a[0x44] != 0) {
        func_80074590(0x11, 0, 0);
        a[0x45] = a[0x44];
        a[0x46] = a[0x44] - 1;
        CRD_MSG(0x30, D_800A2914);
        a[0] = 0x66;
        a[1] = 0;
        a[0x3F] = 0x6A;
    }
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8013FCD4);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8013FEEC);

extern u8 *D_800A29A8;
extern u8 *D_800A29A4;
void func_801401AC(u8 *a)
{
    s32 k;
    u8 j;
    k = a[0x3E];
    j = k;
    if (k == 0) {
    } else if (j == 1) {
        func_80074590(0x90, 0, 0);
        CRD_MSG(0x55, D_800A29A8);
        a[0x50] = 0x14;
        a[1] = 0;
        a[0] = 0x6B;
    } else {
        CRD_MSG(0x54, D_800A29A4);
        a[0x50] = 0x1E;
        a[0x44] = 0;
        a[0x4B] = 0xFC;
        a[0x4A] = 0xFC;
        (a + a[0x46])[0x48] = 0;
        (a + a[0x46])[0x4E] = 0xFF;
        a[3] = 0x64;
        a[0x46] = 0xFF;
        a[0x47] = 0;
        a[0] = 0x6D;
    }
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80140314);

#define H(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define H(p, o) (*(s16 *)((u8 *)(p) + (o)))
void func_80140608(u8 *a)
{
    CrdMenu *s;
    s32 w, m, ff;
    ff = 0xFF;
    if (a[0x46] != ff && (a + a[0x46])[0x4A] != 0) {
        w = 0x30;
        s = &D_800BF498;
        m = -1;
        if (s->x18 != w) {
            func_8009A5B0(s->xC, D_800A2914);
            s->x18 = w;
        }
        if (s->x1A != m) {
            *s->x10 = 0;
            s->x1A = m;
        }
        a[0x50] = 0;
        a[0x44] = 0;
        a[0x4B] = 0xFC;
        a[0x4A] = 0xFC;
        (a + a[0x46])[0x48] = 0;
        (a + a[0x46])[0x4E] = ff;
        a[3] = 0x64;
        a[0x46] = ff;
        a[0x47] = 0;
        a[0] = 0x6D;
    } else if (D_800E7E68 & 0x6000) {
        func_80074590(0x11, 0, 0);
        a[1] = 0;
        a[0] = a[3];
    }
}

#define H(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define H(p, o) (*(s16 *)((u8 *)(p) + (o)))
extern s32 D_800A2914;
void func_80140730(u8 *a)
{
    CrdMenu *s;
    s32 w, m;
    s32 k;
    u8 j;
    k = a[0x3E];
    j = k;
    if (k == 0) {
    } else if (j == 1) {
        w = 0x30;
        s = &D_800BF498;
        m = -1;
        if (s->x18 != w) {
            func_8009A5B0(s->xC, D_800A2914);
            s->x18 = w;
        }
        if (s->x1A != m) {
            *s->x10 = 0;
            s->x1A = m;
        }
        a[0] = 0x66;
        a[1] = 0;
        a[0x3F] = 0x6A;
    } else {
        a[0x50] = 0;
        a[0x44] = 0;
        a[0x4B] = 0xFC;
        a[0x4A] = 0xFC;
        (a + a[0x46])[0x48] = 0;
        (a + a[0x46])[0x4E] = 0xFF;
        a[3] = 0x64;
        a[0x46] = 0xFF;
        a[0x47] = 0;
        a[0] = 0x6D;
    }
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80140834);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8014095C);

void func_80140C00(u8 *p, u8 a1)
{
    p[0x50] = a1;
    p[0x44] = 0;
    p[0x4B] = 0xFC;
    p[0x4A] = 0xFC;
    (p + p[0x46])[0x48] = 0;
    (p + p[0x46])[0x4E] = 0xFF;
    p[3] = 100;
    p[0x46] = 0xFF;
    p[0x47] = 0;
    p[0] = 0x6D;
}

s32 func_80140C4C(u8 *a)
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

void func_80140E10(u8 *a)
{
    u8 *e;
    u8 *g;

    switch (a[4]) {
    case 0:
        if (func_80051B70(a, 0xC, 0x41) != 0) {
            break;
        }
        *(s16 *)(a + 0x80) = 0x3C;
        *(s16 *)(a + 0x82) = 0x78;
        *(s16 *)(a + 0x84) = 0xA0;
        a[0] = 1;
        *(s16 *)(a + 0x86) = 0x88;
        a[0x29] = 0;
        *(s16 *)(a + 0x58) = 0;
        *(s16 *)(a + 0x56) = 0;
        *(s16 *)(a + 0x54) = 0;
        func_800517F8(a);
        a[4]++;
        break;
    case 1:
        func_8007778C(a);
        func_800517F8(a);
        break;
    case 2:
        a[1] = 1;
        func_80077E7C(a);
        func_800517F8(a);
        switch (a[5]) {
        case 1:
            if (a[6] == 0) {
                *(s16 *)(a + 0x84) = 0x5A;
                *(s16 *)(a + 0x86) = 0x50;
                a[6]++;
            }
            break;
        case 2:
        case 3:
            func_80042354(1, 1);
            e = D_800E7E80;
            g = (u8 *)&D_800BF870;
            *(s16 *)(e + 0x2E) = 0x3F01;
            *(s16 *)(e + 0x36) = 0x1E3F;
            g[0x1D4] |= 2;
            func_8004D4C4(0x1B, 1);
            func_8004B0D8(a);
            func_80040B48(0x30);
            a[4] = 3;
            break;
        }
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

// ASM by design: hand-written GTE routine (no stack frame, trapping add / addi / sub, `or rd, $zero, rs` moves: never emitted by gcc 2.8.1).
INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80140FBC);

// ASM by design: hand-written GTE routine (no stack frame, trapping add / addi / sub, `or rd, $zero, rs` moves: never emitted by gcc 2.8.1).
INCLUDE_ASM("asm/a08/nonmatchings/a08", f_UpdateWaterTempleRaftNpcActor);

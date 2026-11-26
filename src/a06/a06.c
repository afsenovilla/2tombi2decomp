#include "common.h"
#include "game.h"
#include "m2c.h"
#include "gte.h"

extern s8 D_800BF808[];
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

void func_8010A518(u8 *a, u8 *b) {
    s32 t, u;

    if (D_1F800137 != 0 || D_800BF808[5] != 0) {
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
        D_800BF808[0x39] = 1;
    }
}

#define F16(p, o) M2C_FIELD(p, s16 *, o)
#define FU16(p, o) M2C_FIELD(p, u16 *, o)
extern s8 D_800BF80D;
extern u8 D_1F800182_5650;
#define F16(p, o) M2C_FIELD(p, s16 *, o)
#define FU16(p, o) M2C_FIELD(p, u16 *, o)
extern u8 D_1F800182_5650;
void func_8010A66C(u8 *a, u8 *b) {
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
        D_1F800182_5650 = 0;
    } else if (!(func_8001E860(a, b, 0, 0) & 0x80)) {
        D_1F800182_5650 = 0;
    }
}

extern u8 D_1F800253;
#define F16(p, o) M2C_FIELD(p, s16 *, o)
#define FU16(p, o) M2C_FIELD(p, u16 *, o)
s32 func_8010A838(u8 *a, u8 *b) {
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
s32 func_8010A9AC(u8 *a, u8 *b, u8 *c) {
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

extern u8 D_800BF840;
extern u16 D_1F80009C_efeb;
extern s16 D_1F80018C_67a7;
extern s16 D_1F80018E_814b;
extern u16 D_1F80008C;
void func_8010AC90(u8 *a, u8 *b)
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
                D_1F80018E_814b = 0x4101;
                D_1F80018C_67a7 = *(u16 *)(a + 0x140) - 0x400;
                D_800BF840 = 0x42;
            } else {
                s32 m = *(u16 *)(a + 0x140) + 0x400;
                t = d - m * 16;
                if (abs(t) < 0x1000) {
                    D_1F80018C_67a7 = m;
                    D_1F80018E_814b = 0x4201;
                    D_800BF840 = 0x43;
                }
            }
        }
        if (*(s16 *)(a + 0x80) + *(s16 *)(b + 0x80) + 0x50 >= D_1F80008C) {
            b[0x2B] = 2;
            if (*(s16 *)(a + 0x80) + *(s16 *)(b + 0x80) >= D_1F80008C && !(a[0] & 4)) {
                s32 x = (func_80083F50(ang) * (*(s16 *)(a + 0x80) + *(s16 *)(b + 0x80))) >> 12;
                s32 z = func_80083E80(ang) * (*(s16 *)(a + 0x80) + *(s16 *)(b + 0x80));
                *(s16 *)(a + 0x2E) = *(s16 *)(b + 0x2E) + x;
                *(s16 *)(a + 0x36) = *(s16 *)(b + 0x36) - (z >> 12);
            }
        }
    }
}

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8010AEAC);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8010B1F8);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8010B334);

extern u8 D_800BF808_1760[];
extern u8 D_800BF80F;
void func_8010B59C(u8 *a) {
    u8 *g = D_800BF808_1760;
    u16 y;

    if (g[0xE] != 0 && a[0x16B] == 8) {
        y = *(u16 *)(g + 0xA);
        if (g[0xF] == 0xA && *(s16 *)(a + 0x36) >= 0x6218) {
            *(s16 *)(a + 0x36) = 0x6217;
        }
        if (!(a[0x145] & 1) && *(s16 *)(a + 0x32) >= (s16)y - *(s16 *)(a + 0x62)) {
            *(s16 *)(a + 0x32) = y - *(u16 *)(a + 0x62);
            func_80022C78(a);
            a[0x29] |= 0x80;
        }
    } else if (D_1F800137 == 0) {
        func_8010B334(a);
    }
    if (D_1F800137 == 0 && D_800BF80F == 0) {
        func_8010AEAC(a);
    }
}

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8010B6B0);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8010B860);

static inline s32 land_inl_4199(u8 *a, u8 *b, u8 *c, s16 f, s16 rr)
{


    b[0x29] = 1;
    if (b[0x5E] == 0) {
        if (b[3] == 2 && D_1F800137 == 0 && a[0x145] == 2 && a[4] < 2) {
            if (func_80055844() != 0) {
                a[0x145] = 0;
                a[0x148] = 0;
                F16(a, 0x50) = 0;
                a[5] = 0x17;
                a[6] = 0;
                a[7] = 0;

                goto done;
            }
            if (a[5] != 0x17 || F16(a, 0x4A) > 0x2C00) {
                a[0x145] = 0;
                a[0x148] = 0;
                F16(a, 0x50) = 0;
                a[5] = 0x17;
                a[6] = 0;
                a[7] = 0;

                goto done;
            }
        }
        func_80022C78(a);

        goto done;
    }
    func_80022C78(a);
    if (rr <= F16(a, 0x80) && a[0] == 1 && !(FU16(a, 0x17E) & 0x200)) {
        a[0x2B] = D_1F80009C >> 4;
        func_80022D08(a, b, 1, 1);

        goto done;
    }
    if (func_80077768((s16)D_1F80009C, F16(a, 0x140), 1) != 0) {
        F16(a, 0x142) = 0x100;
    } else {
        F16(a, 0x142) = -0x100;
    }
    a[0x16A] = 10;

done:
    M2C_FIELD(a, s32 *, 0x30) = (F16(c, 0x30) + f) << 16;
    return 2;
}
s32 func_8010BA74(u8 *a, u8 *b, u8 *c) {
    s16 dx, dz, dy, e, f;
    u16 h, bh, ah;
    u16 r;
    s32 s, t, k, m, ret;

    dx = FU16(a, 0x2E) - FU16(c, 0x2C);
    dz = FU16(a, 0x36) - FU16(c, 0x34);
    r = func_80084080(dx * dx + dz * dz);
    if (r > F16(a, 0x80) + F16(b, 0x80)) {
        return -1;
    }
    dy = FU16(a, 0x32) - FU16(c, 0x30);
    bh = FU16(b, 0x84); ah = FU16(a, 0x84); h = bh + ah;
    if ((u16)(dy + h) > F16(a, 0x86) + F16(b, 0x86)) {
        return -1;
    }
    if (dy < 0) {
        dy = -dy;
        e = h;
        f = -h;
    } else {
        f = e = (FU16(b, 0x86) - bh) + (FU16(a, 0x86) - ah);
    }
    D_1F80009C = func_80085690(-dz, dx);
    if (f < 0 && e - dy < 0x28) {
        if (a[0x145] & 1) {
            return -1;
        }
        return land_inl_4199(a, b, c, f, r);
    }
    s = F16(a, 0x80) + F16(b, 0x80) - (s16)r;
    k = e - dy;
    if (s < k) {
        if (!(a[0] & 4)) {
            m = (func_80083F50(D_1F80009C) * (F16(a, 0x80) + F16(b, 0x80))) >> 12;
            t = func_80083E80(D_1F80009C) * (F16(a, 0x80) + F16(b, 0x80));
            F16(a, 0x2E) = FU16(c, 0x2C) + m;
            F16(a, 0x36) = FU16(c, 0x34) - (t >> 12);
        }
        if (k >= 0x92) {
            a[0x60] = 1;
        }
        a[0x5F] = func_80077768((s16)D_1F80009C, F16(a, 0x140), 1) + 2;
        return 1;
    }
    if (f <= 0) {
        if (a[0x145] & 1) {
            return -1;
        }
        return land_inl_4199(a, b, c, f, r);
    }
    if (D_1F800098 != 0) {
        return 3;
    }
    {
        s32 y = F16(c, 0x30) + f;
        D_1F800253 = 4;
        M2C_FIELD(a, s32 *, 0x30) = y << 16;
    }
    if (a[0x145] == 1 && F16(a, 0x4A) < 0) {
        F16(a, 0x4A) = 0;
    }
    if (b[0x5E] == 0 && (s16)r <= F16(a, 0x80)) {
        a[0x2B] = D_1F80009C >> 4;
        func_80022D08(a, b, 1, 1);
    }
    return 3;
}

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8010C034);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8010C240);

s32 func_8010C3B4(u8 *a, u8 *b, u8 *c) {
    s16 dx, dz, dy, e, f, v;
    u16 h, bh, ah;
    u16 r;
    s32 ang, s, t, m;

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
    D_1F80009C = ang;
    if (s < e - dy || s < 3) {
        m = (func_80083F50(ang) * (F16(a, 0x80) + F16(b, 0x80))) >> 12;
        t = func_80083E80(D_1F80009C) * (F16(a, 0x80) + F16(b, 0x80));
        F16(a, 0x2E) = FU16(c, 0x2C) + m;
        MEMBER_AT(s16, a, 0x36) = FU16(c, 0x34) - (t >> 12);
        a[0x60] = 1;
        a[0x5F] = func_80077768((s16)D_1F80009C, F16(a, 0x140), 1) + 2;
        if (func_80077768(F16(a, 0x56), (s16)D_1F80009C, 0) != 0) {
            if (b[0x5F] == 1) {
                if (a[4] == 1 && a[5] != 0x13) {
                    s32 d = D_1F80009C;
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
                    s32 d2 = D_1F80009C;
                    a[5] = 0x13;
                    a[6] = 0;
                    a[7] = 0;
                    a[0x2B] = d2 >> 4;
                    D_1F80009C = (D_1F80009C - 0x400) & 0xFFF;
                    if (D_1F80009C < 0x800) {
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

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8010C7F8);

extern u8 *D_1F800184_6cc7;
extern s16 D_1F800188;
extern s16 D_1F80018A;
extern s16 D_1F800196;
static inline void land_inl(u8 *p, s32 y)
{
    M2C_FIELD(p, s32 *, 0x30) = y << 16;
    func_80022C78(p);
}
s32 func_8010CAE8(u8 *a, u8 *b, u8 *c) {
    s16 dx, dz, dy, e, f;
    u16 h, bh, ah;
    u16 r;
    s32 ang, s, t, k, m;

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
    k = e - dy;
    D_1F80009C = ang;
    if (s < k || s < 3) {
        m = (func_80083F50(ang) * (F16(a, 0x80) + F16(b, 0x80))) >> 12;
        t = func_80083E80(D_1F80009C) * (F16(a, 0x80) + F16(b, 0x80));
        F16(a, 0x2E) = FU16(c, 0x2C) + m;
        F16(a, 0x36) = FU16(c, 0x34) - (t >> 12);
        if (k >= 0x92) {
            a[0x60] = 1;
        }
        a[0x5F] = func_80077768((s16)D_1F80009C, F16(a, 0x140), 1) + 2;
        if (b[0x5E] >= 2 && a[4] == 1 && a[5] != 0x13) {
            s32 d = D_1F80009C;
            a[5] = 0x13;
            a[6] = 0;
            a[7] = 0;
            a[0x2B] = d >> 4;
        }
        return 1;
    }
    if (f <= 0) {
        if (a[0x145] & 1) {
            return 0;
        }
        land_inl(a, M2C_FIELD(c, s32 *, 0x30) + f);
        if ((s16)r < 0x51) {
            s16 v;
            D_1F80018E_814b = 1;
            D_1F800184_6cc7 = b;
            D_1F800188 = MEMBER_AT(u16, c, 0x2C);
            D_1F80018A = FU16(c, 0x34);
            D_1F800196 = D_1F80018C_67a7 = (FU16(b, 0x56) + FU16(*(u8 **)(b + 0xC4), 0xA) + 0x400) & 0xFFF;
        }
        return 2;
    }
    if (D_1F800098 == 0) {
        s32 y = M2C_FIELD(c, s32 *, 0x30) + f;
        D_1F800253 = 4;
        M2C_FIELD(a, s32 *, 0x30) = y << 16;
        if (F16(a, 0x4A) < 0) {
            F16(a, 0x4A) = 0;
        }
    }
    return 3;
}

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8010CE50);

extern s32 D_1F800184;
void func_8010D134(u8 *a, u8 *b)
{
    if (a[0] == 6) {
        return;
    }
    b[0x29] = 0;
    if (a[0x16B] != 0) {
        if (D_1F800184 == (s32)b) {
            func_8010C7F8(a, b, *(u8 **)(b + 0xC4));
            if (*(s16 *)(b + 0x72) != 0 && (func_8010CE50(a, *(u8 **)(b + 0xD0), 0x64, 0x28) == 2 || func_8010CE50(a, *(u8 **)(b + 0xD8), 0x64, -0x7F88) >= 0)) {
                a[0x2B] = D_1F80009C >> 4;
                func_80022D08(a, b, 1, 1);
            }
        }
    } else {
        switch (func_8010CAE8(a, b, *(u8 **)(b + 0xC8))) {
        case 2:
            b[0x29] = 1;
            if (D_1F80018E_814b != 0) {
                D_1F80018E_814b = 0x10;
            }
            break;
        case 0:
            if (func_8010CAE8(a, b, *(u8 **)(b + 0xCC)) == 2) {
                b[0x29] = 0x81;
                if (D_1F80018E_814b != 0) {
                    D_1F80018E_814b = 0x20;
                }
            }
            break;
        }
    }
}

extern s32 D_1F800088;
extern u8 *D_1F800084;
s32 func_8010D288(u8 *a, u8 *b, u8 *c)
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
    D_1F800084 = c;
    {
        u16 w = *(u16 *)(b + 0x80);
        D_1F800182_5650 = 0;
        *(s16 *)(a + 0x152) = w + 0x1E;
    }
    return 1;
}

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8010D3BC);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8010D9F0);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8010DD58);

s32 func_8010DF24(u8 *a, u8 *b, u8 *c) {
    s16 dx, dz, dy, e;
    u16 h, bh, ah;
    u16 r;
    s32 ang, s, t, k, t2;

    dx = FU16(a, 0x2E) - FU16(c, 0x2C);
    dz = FU16(a, 0x36) - FU16(c, 0x34);
    r = func_80084080(dx * dx + dz * dz);
    if (r > F16(a, 0x80) + F16(b, 0x80)) {
        return -1;
    }
    dy = FU16(a, 0x32) - FU16(c, 0x30);
    bh = FU16(b, 0x84); ah = FU16(a, 0x84); h = bh + ah;
    if ((u16)(dy + h) > F16(a, 0x86) + F16(b, 0x86)) {
        return -1;
    }
    if (dy < 0) {
        dy = -dy;
        e = h;
    } else {
        e = (FU16(b, 0x86) - bh) + (FU16(a, 0x86) - ah);
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
        if (k >= 0x92) {
            a[0x60] = 1;
        }
        a[0x5F] = func_80077768((s16)D_1F80009C, F16(a, 0x140), 1) + 2;
    } else if (!(a[0] & 4)) {
        e = (func_80083F50(ang) * F16(a, 0x80)) >> 12;
        t2 = func_80083E80(D_1F80009C) * F16(a, 0x80);
        F16(a, 0x2E) = FU16(a, 0x2E) + e;
        F16(a, 0x36) = FU16(a, 0x36) - (t2 >> 12);
    }
    return 1;
}

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8010E1C4);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8010E3DC);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8010E548);

s32 func_8010E7D4(u8 *a, u8 *b, u8 *c)
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
        k = k - cy + 0x8C;
        h = *(volatile u16 *)(a + 0x68);
        k = (u16)(h + k);
        if ((s16)h + 0x118 < k) {
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
    D_1F800084 = c;
    {
        u16 w = *(u16 *)(b + 0x80);
        D_1F800182_5650 = 0;
        *(s16 *)(a + 0x152) = w + 0x1E;
    }
    return 1;
}

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8010E908);

s32 func_8010ED04(u8 *a, u8 *b, u8 *c) {
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

void func_8010EE7C(u8 *a, u8 *b, u8 *c) {
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
    D_1F800182_5650 = 0;
}

#define H(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define U(p, o) (*(u16 *)((u8 *)(p) + (o)))
extern u16 D_1F80018E;
extern u16 D_1F80018C;
void func_8010F0F0(u8 *a, u8 *b)
{
    s32 k;
    s32 g;
    s32 m;
    s32 c;
    s32 x, y;
    if (func_8002300C(a, b, H(b, 0x80) * 4) == 0) {
        return;
    }
    k = D_1F80009C_efeb + 0x800;
    b[0x2B] = 1;
    if (D_1F800137 == 0) {
        m = U(a, 0x140) - 0x400;
        g = func_80085690(-(s16)(U(b, 0x36) - U(a, 0x36)), (s16)(U(b, 0x2E) - U(a, 0x2E))) << 4;
        if (abs((s16)(g - m * 16)) < 0x1000) {
            D_1F80018E = 0x4100;
            D_1F80018C = U(a, 0x140) - 0x400;
            D_800BF840 = 0x42;
        } else {
            c = U(a, 0x140) + 0x400;
            if (abs((s16)(g - c * 16)) < 0x1000) {
                D_1F80018C = c;
                D_1F80018E = 0x4200;
                D_800BF840 = 0x43;
            }
        }
    }
    if (H(a, 0x80) + H(b, 0x80) + 0x50 < D_1F80008C) {
        return;
    }
    b[0x2B] = 2;
    if (H(a, 0x80) + H(b, 0x80) < D_1F80008C) {
        return;
    }
    x = (func_80083F50((s16)k) * (H(a, 0x80) + H(b, 0x80))) >> 12;
    y = (func_80083E80((s16)k) * (H(a, 0x80) + H(b, 0x80))) >> 12;
    U(a, 0x2E) = U(b, 0x2E) + x;
    U(a, 0x36) = U(b, 0x36) - y;
}

typedef struct {
    u8 pad0[0xC0];
    s32 xC0[1];
} S11130C;
extern u8 D_801422B0[];
extern u8 **D_1F80013C;
extern u8 D_1F800144;
extern u8 **D_1F800148;
extern u8 D_1F800150;
void func_8010F2E8(u8 *a)
{
    u8 **l = D_1F800148;
    u8 *p;

    D_1F800182_5650 = D_1F800150;
    while (D_1F800182_5650 != 0) {
        p = *l;
        D_1F800182_5650--;
        l++;
        if ((p[0] & 1) && p[2] == 0x3B && func_80023D48(a, p, ((S11130C *)p)->xC0[D_801422B0[p[3]]], 0) != 0) {
            D_1F800182_5650 = 0;
        }
    }
    l = D_1F80013C;
    D_1F800182_5650 = D_1F800144;
    while (D_1F800182_5650 != 0) {
        p = *l;
        D_1F800182_5650--;
        l++;
        if ((p[0] & 1) && p[2] == 8 && func_8002423C(a, p) == 2) {
            D_1F800182_5650 = 0;
        }
    }
}

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8010F450);

extern u8 D_1F800183;
void func_8010F608(void)
{
    u8 **l = D_1F80013C;
    u8 **m;
    u8 *a;
    u8 *b;
    s32 i;

    D_1F800183 = D_1F800144;
    if (*(s16 *)&D_1F800150 == 0) {
        return;
    }
    while (D_1F800183 != 0) {
        a = *l;
        D_1F800183--;
        l++;
        if (a[2] == 0x48 || a[0] == 2 || (a[0] & 8)) {
            continue;
        }
        m = D_1F800148;
        D_1F800182_5650 = D_1F800150;
        while (D_1F800182_5650 != 0) {
            b = *m;
            D_1F800182_5650--;
            m++;
            if (b[0] & 1) {
                switch (b[2]) {
                case 0:
                    if (func_80023D48(a, b, *(u8 **)(b + 0xC8), 0) != 0 || func_80023D48(a, b, *(u8 **)(b + 0xCC), 0) != 0) {
                        D_1F800182_5650 = 0;
                    }
                    break;
                case 2:
                case 17:
                    func_80023D48(a, b, *(u8 **)(b + 0xC0), 0);
                    break;
                case 12:
                case 31:
                case 67:
                    if (a[2] != 8 && func_8002421C(a, b) == 2) {
                        a[0x29] = 1;
                    }
                    break;
                case 59:
                    func_80023D48(a, b, ((S11130C *)b)->xC0[D_801422B0[b[3]]], 0);
                    break;
                case 11:
                    for (i = 0; i < b[8] - 1; i++) {
                        if (func_80023870(a, b, ((void **)(b + 0xC0))[i]) != 0) {
                            break;
                        }
                    }
                    break;
                }
            }
        }
    }
}

void func_8010F870(void)
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
            for (D_1F800182_5650 = D_1F800183; D_1F800182_5650 != 0; D_1F800182_5650--) {
            }
        }
    }
}

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8010F91C);

/* func_801112BC, inlined */
static inline void inl_801112BC(u8 *a0, S11130C *a1)
{
    if (a0[0] != 6) {
        func_8010BA74(a0, (u8 *)a1, (u8 *)a1->xC0[D_801422B0[((u8 *)a1)[3]]]);
    }
}
void func_8010FECC(u8 *a)
{
    u8 **l = D_1F800148;
    u8 *b;
    s32 i;

    D_1F800182_5650 = D_1F800150;
    while (D_1F800182_5650 != 0) {
        b = *l;
        D_1F800182_5650--;
        l++;
        if (b[0] & 1) {
            switch (b[2]) {
            case 0:
                func_8010D134(a, b);
                break;
            case 3:
                if (a[0] != 6 && a[0x78] != 7) {
                    func_8010C3B4(a, b, *(u8 **)(b + 0xC0));
                }
                break;
            case 14:
            case 15:
                func_8001FAE0(a, b);
                break;
            case 12:
                func_80020868(a, b);
                break;
            case 24:
                func_80020B08(a, b);
                break;
            case 31:
                func_80023764(a, b);
                break;
            case 17:
                func_8010D9F0(a, b, *(u8 **)(b + 0xC0));
                break;
            case 32:
                if (func_8001EC3C(a, b) == 1 && b[0x5E] != 0 && (a[0x5F] & 1) == a[0x147] && a[0x46] == 0xC6) {
                    b[0x5F] = a[0x5F];
                    a[0x5F] |= 8;
                }
                break;
            case 60:
                func_8010DF24(a, b, *(u8 **)(b + 0xC0));
                break;
            case 2:
                func_8010E908(a, b, *(u8 **)(b + 0xC0));
                break;
            case 59:
                inl_801112BC(a, (S11130C *)b);
                break;
            case 101:
                func_8010A518(a, b);
                break;
            case 58:
                func_8010A838(a, b);
                break;
            case 18:
            case 26:
            case 67:
                func_8002311C(a, b);
                break;
            case 66:
                if (func_8001F830(a, b) != 0) {
                    a[0x2B] = D_1F80009C >> 4;
                    func_80022D08(a, b, 1, 1);
                }
                break;
            case 11:
                for (i = 0; i < b[8] - 1; i++) {
                    if (func_8001F650(a, b, ((void **)(b + 0xC0))[i]) != 0) {
                        break;
                    }
                }
                break;
            case 51:
            case 75:
                func_8001FC50(a, b);
                break;
            case 103:
                {
                    s16 dx = *(u16 *)(a + 0x2E) - *(u16 *)(b + 0x2E);
                    s16 dz = *(u16 *)(a + 0x36) - *(u16 *)(b + 0x36);
                    s32 d = func_80084080(dx * dx + dz * dz);

                    if ((u16)d > *(s16 *)(a + 0x80) + 0xC8) {
                        break;
                    }
                    if ((u16)(*(u16 *)(a + 0x84) + (*(u16 *)(a + 0x32) - *(u16 *)(b + 0x32) + 0x140)) > *(s16 *)(a + 0x86) + 0x140) {
                        break;
                    }
                    b[0x29] = 1;
                    func_8001F830(a, b);
                }
                break;
            }
        }
    }
}

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_801102A4);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8011065C);

extern u8 D_800E7E80[];
extern u8 **D_1F800154;
extern u8 D_1F80015C;
/* func_801121D0, inlined */
static inline void func_801121D0_inl(void)
{
    u8 **list = D_1F800154;
    u8 *a;

    for (D_1F800183 = D_1F80015C; D_1F800183 != 0;) {
        a = *list++;
        D_1F800183--;
        if (!(a[0] & 2)) {
            switch (a[2]) {
            case 1:
                if (a[3] != 1) {
                    break;
                }
            case 0:
            case 4:
                func_8010F2E8(a);
                break;
            }
        }
    }
}
void func_801109F8(void)
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
        do {
            func_80022760(p);
        } while (0);
        func_8010F91C(p);
        if (p[0] == 6) {
            break;
        }
    case 2:
        if (*(u32 *)(p + 0x158) < 2) {
            func_8010FECC(p);
        }
        break;
    }
    func_80022554();
    func_801102A4();
    func_8011065C();
    func_801121D0_inl();
    func_8010F608();
    func_8010F870();
    func_8010B59C(p);
}

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80110B7C);

extern s8 D_1F80027B[];
void func_80110DD0(void *arg0) {
    if ((M2C_FIELD(arg0, u8 *, 0x181) == 0) && ((M2C_FIELD(arg0, u8 *, 0x146) != 4) || (*((u8 *)D_1F80027B) == 0))) {
        if (M2C_FIELD(arg0, u8 *, 5) == 6) {
            M2C_FIELD(arg0, s16 *, 0x6A) = 0;
            M2C_FIELD(arg0, u8 *, 5) = 0x32U;
            M2C_FIELD(arg0, u8 *, 0x149) = (u8) ((M2C_FIELD(arg0, u8 *, 0x149) & 1) | 2);
        } else {
            M2C_FIELD(arg0, u8 *, 5) = 0x1DU;
            M2C_FIELD(arg0, s8 *, 6) = 0;
        }
        M2C_FIELD(arg0, s8 *, 4) = 1;
        M2C_FIELD(arg0, s8 *, 0x16A) = 0;
        M2C_FIELD(arg0, s8 *, 7) = 0;
        if (M2C_FIELD(arg0, u8 *, 0x144) == 1) {
            M2C_FIELD(arg0, u8 *, 0x144) = 0U;
        }
    }
}

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80110E60);

void func_80110F28(void *arg0, s32 arg1) {
    s16 temp_a0;

    if (arg1 == 0) {
        if (D_800BF870.pad1[2] != 0) {
            D_800BF870.pad1[0] = 0xF;
            return;
        }
        D_800BF870.pad1[0] = 1;
        return;
    }
    if ((u8) D_800BF870.pad1[0] < 6U) {
        if (M2C_FIELD(arg0, s16 *, 0x2E) >= 0x55F1) {
            D_800BF870.pad1[0] = 2;
            return;
        }
        D_800BF870.pad1[0] = 3;
        return;
    }
    if ((u8) D_800BF870.pad1[0] < 0x10U) {
        temp_a0 = M2C_FIELD(arg0, s16 *, 0x2E);
        if (temp_a0 < 0x2260) {
            D_800BF870.pad1[0] = 0xD;
            return;
        }
        if (temp_a0 < 0x2E7C) {
            D_800BF870.pad1[0] = 0xC;
            return;
        }
        D_800BF870.pad1[0] = 0xB;
    }
}

void func_80110FE0(u8 *a)
{
    u8 *g = D_800BF808_1760;
    s32 h = *(u16 *)(g + 0xA);

    if (g[0xF] == 0xA && *(s16 *)(a + 0x36) >= 0x6218) {
        *(s16 *)(a + 0x36) = 0x6217;
    }
    if (!(a[0x145] & 1) && *(s16 *)(a + 0x32) >= (s16)h - *(s16 *)(a + 0x62)) {
        *(s16 *)(a + 0x32) = h - *(s16 *)(a + 0x62);
        func_80022C78(a, h);
        a[0x29] |= 0x80;
    }
}

void func_80111084(void *a, u8 *b)
{
    s32 i;

    for (i = 0; i < b[8] - 1; i++) {
        if (func_80023870(a, b, ((void **)(b + 0xC0))[i]) != 0) {
            break;
        }
    }
}

void func_80111108(void *a, u8 *b)
{
    s32 i;

    for (i = 0; i < b[8] - 1; i++) {
        if (func_8001F650(a, b, ((void **)(b + 0xC0))[i]) != 0) {
            break;
        }
    }
}

void func_8011118C(void *a, u8 *b)
{
    s32 i;

    for (i = 0; i < b[8] - 1; i++) {
        if (func_80022E04(a, b, ((void **)(b + 0xC0))[i]) != 0) {
            func_8001E860(a, b, ((void **)(b + 0xC0))[i], 0);
            D_1F800182_5650 = 0;
            return;
        }
    }
}

void func_80111238(void *arg0, void *arg1) {
    u8 temp_a0;

    if ((func_8001EC3C() == 1) && (M2C_FIELD(arg1, u8 *, 0x5E) != 0)) {
        temp_a0 = M2C_FIELD(arg0, u8 *, 0x5F);
        if (((temp_a0 & 1) == M2C_FIELD(arg0, u8 *, 0x147)) && (M2C_FIELD(arg0, u8 *, 0x46) == 0xC6)) {
            M2C_FIELD(arg1, u8 *, 0x5F) = temp_a0;
            M2C_FIELD(arg0, u8 *, 0x5F) = (u8) (M2C_FIELD(arg0, u8 *, 0x5F) | 8);
        }
    }
}

void f_UpdateDonglinInteriorQuestObjectActor();
extern s32 D_800BF544;
void func_801112BC(u8 *a0, S11130C *a1)
{
    if (a0[0] != 6) {
        func_8010BA74(a0, a1, a1->xC0[D_801422B0[((u8 *)a1)[3]]]);
    }
}

extern u8 D_800BF91F;
void func_8011130C(void *a0, S11130C *a1)
{
    func_80023D48(a0, a1, a1->xC0[D_801422B0[((u8 *)a1)[3]]], 0);
}

extern s32 D_1F80009C;
void func_8012A564();
void func_80111350(u8 *a0, void *a1)
{
    if (func_8001F830(a0, a1)) {
        a0[0x2B] = D_1F80009C >> 4;
        func_80022D08(a0, a1, 1, 1);
    }
}

void func_801113A8(u8 *a0, u8 *a1)
{
    if (a0[0] != 6 && a0[0x78] != 7) {
        func_8010C3B4(a0, a1, *(s32 *)(a1 + 0xC0));
    }
}

extern u8 *D_1F800080_ddd3;
void func_801113EC(u8 *a, u8 *b) {
    if (func_8010D288(a, b, M2C_FIELD(b, u8 **, 0xC8)) != 0) {
        D_1F800080_ddd3 = b;
        a[0x15C] = 0;
        a[0x164] = 1;
        b[0x29] = 1;
    } else if (func_8010D288(a, b, M2C_FIELD(b, u8 **, 0xCC)) != 0) {
        D_1F800080_ddd3 = b;
        a[0x15C] = 1;
        a[0x164] = 1;
        b[0x29] = 0x81;
    }
}

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8011146C);

s32 func_8011159C(u8 *a, u8 *p, s16 r, s32 f)
{
    s32 t = f & 0x8000;
    s32 off = 0;
    s32 h = f & 0x7FFF;
    s16 dx;
    s16 dz;
    s32 d;

    if (!t) {
        off = 0xC8;
    }
    dx = *(u16 *)(a + 0x2E) - *(u16 *)(p + 0x2C);
    dz = *(u16 *)(a + 0x36) - (*(u16 *)(p + 0x34) + off);
    d = func_80084080(dx * dx + dz * dz);
    if ((u16)d > *(s16 *)(a + 0x80) + r) {
        return 0;
    }
    if ((u16)((*(u16 *)(a + 0x32) - *(u16 *)(p + 0x30)) + (*(u16 *)(a + 0x84) + h)) > *(s16 *)(a + 0x86) + h * 2) {
        return 0;
    }
    D_1F80009C = func_80085690(-dz, dx);
    return 1;
}

extern u8 D_1F800182_5650;
void func_801116B8(u8 *a, u8 *b)
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
        D_1F800182_5650 = 0;
    }
}

extern void *D_1F800080;
extern u8 D_1F800182_5650;
void func_80111738(u8 *a, u8 *b)
{
    if (func_80024BD8(a, b, *(void **)(b + 0xC0)) != 0) {
        b[0x29] = 1;
        a[0x164] = 3;
        D_1F800080 = b;
        D_1F800182_5650 = 0;
    }
}

s32 func_80111790(s32 arg0, s32 arg1) {
    return func_8010D9F0(arg0, arg1, M2C_FIELD(arg1, s32 *, 0xC0));
}

void func_801117B4(u8 *a, u8 *b)
{
    u16 f = *(u16 *)(a + 0x17E);
    s32 r;

    if (f & 0x200) {
        return;
    }
    if (f & 0x8000) {
        func_8001F054(a, b);
        return;
    }
    r = func_8001F40C(a, b, 1);
    if (r < 0) {
        return;
    }
    if (a[0x144] == 1 && r < 2) {
        func_8001FDB4(b, 8, 0x10, 0x20);
        return;
    }
    if (!(a[0] & 4)) {
        s32 temp_s0 = (s32) (func_80083F50(D_1F80009C) * (M2C_FIELD(a, s16 *, 0x80) + M2C_FIELD(b, s16 *, 0x80))) >> 0xC;
        s32 temp_lo = func_80083E80(D_1F80009C) * (M2C_FIELD(a, s16 *, 0x80) + M2C_FIELD(b, s16 *, 0x80));
        M2C_FIELD(a, s16 *, 0x2E) = (s16) (M2C_FIELD(b, u16 *, 0x2E) + temp_s0);
        M2C_FIELD(a, s16 *, 0x36) = (s16) (M2C_FIELD(b, u16 *, 0x36) - (temp_lo >> 0xC));
    }
}

void func_801118DC(u8 *a, u8 *b)
{
    if (a[0] != 6 && !(*(u16 *)(a + 0x17E) & 0x200)) {
        if (b[0x5E] == 0) {
            if (func_80022F04(a, b) != 0 && a[4] == 1 && a[5] != 0x13) {
                s32 v = D_1F80009C;
                a[5] = 0x13;
                a[6] = 0;
                a[7] = 0;
                a[0x2B] = v >> 4;
            }
        } else {
            func_80020364(a, b, 2);
        }
    }
}

s32 func_80111988(s32 arg0, s32 arg1) {
    return func_8010DF24(arg0, arg1, M2C_FIELD(arg1, s32 *, 0xC0));
}

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_801119AC);

void func_80111A80(void *a0, u8 *a1)
{
    if (func_800216B4(a0, a1, 0) && D_800BF91F != 0xFF) {
        a1[0] = 4;
    }
}

void func_80111AC4(u8 *a, u8 *b)
{
    s32 r = func_8001F40C(a, b, 1);

    if (r >= 0) {
        if (a[0x144] == 1 && r < 2) {
            func_8001FDB4(b, 1, 3, 0x1C);
            return;
        }
        a[0x2B] = *(s32 *)0x1F80009C >> 4;
        func_80022D08(a, b, 1, 0);
    }
}

void func_80111B58(void *a0, void *a1)
{
    s32 r = func_8001F40C(a0, a1, 1);

    if (r >= 0) {
        func_8001FF7C(a0, a1, r, 1);
    }
}

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80111BA4);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80111CA4);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80111DC4);

typedef struct {
    s16 pad0;
    s16 a;
    s16 pad4;
    s16 b;
    s16 pad8;
    s16 c;
} S13AE38;
extern u8 *D_8014CE6C_28ce;
extern u16 D_8014CE68;
void func_80111ED4(u8 *a0, u8 *a1)
{
    if (a1[0x5E] == 0 && func_8010E7D4(a0, a1, *(s32 *)(a1 + 0xC0))) {
        D_1F800080_ddd3 = a1;
        a0[0x164] = 0xB;
        a0[0x15C] = 0;
        a1[0x29] = 1;
    }
}

extern s8 D_1F800182[];
void func_80111F38(void *arg0, void *arg1) {
    if (func_80022F04() != 0) {
        if (func_8001DC9C(arg0, arg1, 0, 0x81) & 0x80) {
            M2C_FIELD(arg0, s8 *, 0x2B) = 2;
            M2C_FIELD(arg1, s8 *, 0) = 2;
        }
        M2C_FIELD(arg1, s8 *, 0x2B) = 1;
        *((s8 *)D_1F800182) = 0;
    }
}

s32 func_80111FA4(s32 arg0, s32 arg1) {
    return func_8010E908(arg0, arg1, M2C_FIELD(arg1, s32 *, 0xC0));
}

extern void *D_1F800080;
extern u8 D_1F800182_5650;
extern void *D_1F800080;
extern u8 D_1F800182_5650;
void func_80111FC8(u8 *a, u8 *b)
{
    if (func_8010ED04(a, b, *(void **)(b + 0xC0)) != 0) {
        a[0x164] = 3;
        D_1F800080 = b;
        D_1F800182_5650 = 0;
    }
}

s32 func_80112018(void *arg0, s8 *arg1) {
    if (func_80022F04(arg0, arg1) == 0) {
        return 0;
    }
    if (func_8001DC9C(arg0, arg1, 0, 2) & 0x80) {
        M2C_FIELD(arg0, s8 *, 0x2B) = 2;
    }
    *((s8 *)D_1F800182) = 0;
    return 1;
}

s32 func_80112084(void *arg0, s8 *arg1) {
    if (func_80022F04(arg0, arg1) == 0) {
        return 0;
    }
    if (func_8001DC9C(arg0, arg1, 0, 1) & 0x80) {
        M2C_FIELD(arg0, s8 *, 0x2B) = 2;
    }
    *((s8 *)D_1F800182) = 0;
    return 1;
}

s32 func_801120F0(void *arg0, s8 *arg1) {
    if (func_80022F04(arg0, arg1) == 0) {
        return 0;
    }
    if (func_8001DC9C(arg0, arg1, 0, 0x801) & 0x80) {
        M2C_FIELD(arg0, s8 *, 0x2B) = 2;
    }
    *((s8 *)D_1F800182) = 0;
    return 1;
}

extern s8 D_1F800182[];
s32 func_8011215C(void *arg0, s8 *arg1) {
    if (func_80022F04() == 0) {
        return 0;
    }
    if (func_8001DC9C(arg0, arg1, 0, 1) & 0x80) {
        M2C_FIELD(arg0, s8 *, 0x2B) = 2;
    }
    *arg1 = 2;
    *((s8 *)D_1F800182) = 0;
    return 1;
}

void func_801121D0(void) {
    u8 **list = D_1F800154;
    u8 *a;

    for (D_1F800183 = D_1F80015C; D_1F800183 != 0;) {
        a = *list++;
        D_1F800183--;
        if (!(a[0] & 2)) {
            switch (a[2]) {
            case 1:
                if (a[3] != 1) {
                    break;
                }
            case 0:
            case 4:
                func_8010F2E8(a);
                break;
            }
        }
    }
}

extern u8 D_800BF8D3;
void func_801122A0(void *a0, u8 *a1)
{
    if (func_80023D48(a0, a1, *(s32 *)(a1 + 0xC8), 0) || func_80023D48(a0, a1, *(s32 *)(a1 + 0xCC), 0)) {
        *((s8 *)D_1F800182) = 0;
    }
}

extern s8 D_1F800182[];
void func_80112300(void *arg0, void *arg1) {
    if (func_80022F04() != 0) {
        if (func_8001DC9C(arg0, arg1, 0, 0x80) & 0x80) {
            M2C_FIELD(arg0, s8 *, 0x2B) = 2;
            M2C_FIELD(arg1, s8 *, 0) = 2;
            M2C_FIELD(arg1, s8 *, 4) = 2;
            M2C_FIELD(arg1, s8 *, 5) = 6;
            M2C_FIELD(arg1, s8 *, 6) = 0;
        }
        M2C_FIELD(arg1, s8 *, 0x2B) = 1;
        *((s8 *)D_1F800182) = 0;
    }
}

#define W(p, o) (*(s32 *)((u8 *)(p) + (o)))
extern s16 D_1F80019E;
extern u16 D_1F80017C_0fe7;
void func_8011237C(u8 *a, s32 arg1)
{
    s16 sp[8];
    s16 d;
    s16 t;

    s32 k;

    if (a[0x145] & 1) {
        return;
    }
    d = -0x14;
    if (H(a, 0x17E) < 0) {
        d = -0xA;
    }
    switch (a[7]) {
    case 0:
        func_80058304(a, 2);
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
        W(a, 0x30) += H(a, 0x50) << 8;
        t = U(a, 0x50) - 0x180;
        H(a, 0x50) = t;
        if (t <= 0) {
            a[7]++;
        }
        break;
    case 2:
        if (D_800BF870.unk0 == 0) {
            k = 0x10E;
        } else if (D_800BF870.unk0 == 6) {
            k = 0x70E;
        } else if (D_800BF870.unk0 == 0xE) {
            k = 0xF0D;
        } else {
            goto s2;
        }
        func_800312D4(k, a + 0x2C, -0xA);
    s2:
        a[7]++;
    case 3:
    case 4:
        W(a, 0x30) -= H(a, 0x50) << 8;
        if (a[7] == 3) {
            U(a, 0x50) += 0x180;
        } else {
            U(a, 0x50) += 0x80;
        }
        if (H(a, 0x50) >= 0x1000) {
            H(a, 0x50) = 0x1000;
        }
        if (D_1F80019E + d >= H(a, 0x32)) {
            U(a, 0x32) = *(u16 *)&D_1F80019E;
            if (D_800BF870.unk0 == 0) {
                func_8003116C(0x10D, a + 0x2C, -0xA);
            } else if (D_800BF870.unk0 == 6) {
                func_800312D4(0x704, a + 0x2C, -0xA);
            } else if (D_800BF870.unk0 == 0xE) {
                func_800312D4(0xF06, a + 0x2C, -0xA);
            }
            U(a, 0x32) += d;
            if (a[0x146] == 0 && !(a[0x14A] & 2)) {
                a[7] = 6;
            } else {
                a[7] = 5;
            }
            H(a, 0x50) = 0;
        }
        break;
    case 5:
        W(a, 0x30) += H(a, 0x50) << 8;
        t = U(a, 0x50) + 0x80;
        H(a, 0x50) = t;
        if (t >= 0x600) {
            H(a, 0x50) = 0;
            a[7]--;
        }
        break;
    case 6:
        if (D_1F80019E + d < H(a, 0x32)) {
            W(a, 0x30) -= H(a, 0x50) << 8;
            t = U(a, 0x50) + 0x100;
            H(a, 0x50) = t;
            if (t >= 0x1000) {
                H(a, 0x50) = 0x1000;
            }
            if (D_1F80019E + d >= H(a, 0x32)) {
                U(a, 0x32) = *(u16 *)&D_1F80019E;
                if (D_800BF870.unk0 == 0) {
                    func_8003116C(0x10D, a + 0x2C, -0xA);
                } else if (D_800BF870.unk0 == 6) {
                    func_800312D4(0x704, a + 0x2C, -0xA);
                } else if (D_800BF870.unk0 == 0xE) {
                    func_800312D4(0xF06, a + 0x2C, -0xA);
                }
                H(a, 0x50) = 0;
                U(a, 0x32) += d;
            }
        } else if (a[0x146] != 0 || (a[0x14A] & 2)) {
            a[7] = 5;
        }
        if (arg1 != 0) {
            arg1 = 7;
        } else {
            arg1 = 3;
        }
        if (!(D_1F80017C_0fe7 & arg1)) {
            sp[1] = U(a, 0x2E) + ((func_80083F50(H(a, 0x56) + 0x800) * 100) >> 12);
            sp[3] = *(u16 *)&D_1F80019E + 0x1E;
            sp[5] = U(a, 0x36) - ((func_80083E80(H(a, 0x56) + 0x800) * 100) >> 12);
            func_8003116C(8, sp, -0x50);
        }
        break;
    }
    if (D_1F80019E + H(a, 0x62) / 2 < H(a, 0x32)) {
        a[0x148] = 1;
    } else {
        a[0x148] = 0;
    }
}

extern u16 D_800E7E68;
extern u16 D_1F800170;
extern u16 D_1F8001A6;
extern u16 D_1F8001A8;
void func_80112838(u8 *a) {
    func_80076D68(a);
    switch (a[6]) {
    case 0:
        a[0x16A] = 0;
        H(a, 0x50) = 0;
        a[0x17B] = 1;
        H(a, 0x58) = 0;
        a[0x145] = 0;
        func_80053D90(a);
        a[0x181] = 1;
        a[0x146] = 0;
        a[7] = 0;
        a[6]++;
        func_80054D14(a, 0xDC, 4);
    case 1:
        func_80055E28(a, 1);
        if (!(a[0x14A] & 2)) {
            a[6]++;
        } else if (a[0x149] & 2) {
            func_80054D14(a, 0xDD, 6);
        }
        func_80056878(a, a[0x14A], 0);
        func_80056B48(a, 1);
        func_80055D5C(a);
        func_8011237C(a, 0);
        func_80055390(a);
        H(a, 0x16C) = 0;
        H(a, 0x6A) = 0;
        if (func_800489E4(a, H(a, 0x32)) != 0) {
            s32 p = D_1F8001A6;
            s32 q = D_1F8001A8;
            H(a, 0x6A) = p;
            H(a, 0x16C) = q;
        }
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
        func_8011237C(a, 0);
        func_80056B48(a, 1);
        func_80055D5C(a);
        func_80055390(a);
        H(a, 0x16C) = 0;
        H(a, 0x6A) = 0;
        if (func_800489E4(a, H(a, 0x32)) != 0) {
            s32 p = D_1F8001A6;
            s32 q = D_1F8001A8;
            H(a, 0x6A) = p;
            H(a, 0x16C) = q;
        }
        if ((u16)(D_1F80017C_0fe7 % 15) == 0) {
            func_80074590(0x33, 0, 0);
        }
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
        func_8011237C(a, 1);
        func_80056B48(a, 1);
        func_80055D5C(a);
        func_80055390(a);
        H(a, 0x16C) = 0;
        H(a, 0x6A) = 0;
        if (func_800489E4(a, H(a, 0x32)) != 0) {
            s32 p = D_1F8001A6;
            s32 q = D_1F8001A8;
            H(a, 0x6A) = p;
            H(a, 0x16C) = q;
        }
        if ((u16)(D_1F80017C_0fe7 % 7) == 0) {
            func_80074590(0x33, 0, 0);
        }
        break;
    }
}

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80112C60);

#define W_d1fb(p, o) (*(s32 *)((u8 *)(p) + (o)))
void func_80112E24(u8 *a) {
    s16 h;

    switch (a[6]) {
    case 0:
        func_80053D90(a);
        a[0x145] = 0;
        a[0x146] = 0;
        H(a, 0x4A) = 0;
        func_80054E24(a, 2, 0);
        a[0x29] = 0;
        H(a, 0x42) = 0;
        if (H(a, 0x142) == 0) {
            if (H(a, 0x44) == 0) {
                if (a[0x147] != 0) {
                    H(a, 0x44) = -0x1000;
                } else {
                    H(a, 0x44) = 0x1000;
                }
            } else if (H(a, 0x44) > 0) {
                H(a, 0x44) = U(a, 0x44) + 0x400;
            } else {
                H(a, 0x44) = U(a, 0x44) - 0x400;
            }
        } else if (H(a, 0x142) > 0) {
            H(a, 0x44) = 0x1200;
        } else {
            H(a, 0x44) = -0x1200;
        }
        a[0x144] = 1;
        a[6]++;
    case 1:
        if (a[0x29] == 0 && a[0x181] == 0) {
            h = H(a, 0x44) / 2;
            H(a, 0x42)++;
            W_d1fb(a, 0x2C) += H(a, 0x48) * h;
            W_d1fb(a, 0x34) += H(a, 0x4C) * h;
            if (a[0x16B] == 0 && a[0x61] == 0) {
                func_80054650(a, 0);
            } else {
                a[0x5F] &= 0xFB;
            }
            H(a, 0x32) += 8;
            W_d1fb(a, 0x30) += abs(H(a, 0x44)) << 8;
        } else {
            H(a, 0x42) = 0;
            func_80056B48(a, 1);
            H(a, 0x32) += 0xA;
        }
        func_80055D5C(a);
        func_80076D68(a);
        if (H(a, 0x142) == 0) {
            if (H(a, 0x44) > 0) {
                H(a, 0x44) = U(a, 0x44) + 0x80;
            } else {
                H(a, 0x44) = U(a, 0x44) - 0x80;
            }
        } else {
            H(a, 0x44) = U(a, 0x44) + (H(a, 0x142) >> 1);
        }
        if (H(a, 0x44) > 0x2400) {
            H(a, 0x44) = 0x2400;
        } else if (H(a, 0x44) < -0x2400) {
            H(a, 0x44) = -0x2400;
        }
        func_8005444C(a);
        if (a[0x29] & 0x80) {
            if (a[0x144] < 2) {
                a[0x144] = 0;
            }
            func_8005314C(a);
            a[0x16A] = 0;
            a[0x177] = 0;
            a[5] = 0;
            a[6] = 0;
            a[7] = 0;
            func_80054198(a);
        } else if (H(a, 0x42) >= 5) {
            H(a, 0x44) = H(a, 0x44) / 2;
            func_80056D44(a, 0);
        }
        break;
    }
    func_800551C4(a);
}

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80113110);

extern u16 D_800ECF54;
extern s16 D_1F80016C;
extern s16 D_1F80016E;
void func_80113390(u8 *a, u8 *b)
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

typedef struct { s16 x, y, z, pad; } ClingSVec;
typedef struct { s16 m[3][3]; s16 pad; s32 t[3]; } ClingMat;
extern ClingSVec D_1F8000C0_aa14;
extern ClingSVec D_1F8000C8;
extern ClingMat D_1F800000_d070;
extern ClingMat D_1F800040_b149;
/* func_80114654, inlined */
static inline void inl_80114654(u8 *a)
{
    a[0x177] |= 1;
    *(s16 *)(a + 0x154) += 0x20;
    if (*(s16 *)(a + 0x154) > 0x200) {
        *(s16 *)(a + 0x154) = 0x200;
    }
    *(u16 *)(a + 0x42) += *(u16 *)(a + 0x154);
    if ((a[0x147] ^ a[0x15C]) == 0) {
        *(u16 *)(a + 0x14E) -= *(u16 *)(a + 0x154);
        *(u16 *)(a + 0x56) = *(u16 *)(a + 0x140) + 0x800;
    } else {
        *(u16 *)(a + 0x14E) += *(u16 *)(a + 0x154);
    }
    if (*(s16 *)(a + 0x42) > 0x400) {
        func_80074590(0x1B, 0, 0);
        D_800BF840 = 0x88;
        a[7]++;
    }
}
void func_801134E4(u8 *a, u8 *b, s32 f)
{
    u8 *p;
    s16 ang;

    a[0x160] = 1;
    if (f == 0) {
        switch (a[7]) {
        case 0:
            if (b[2] == 0x3C) {
                inl_80114654(a);
            } else {
                func_80063098(a);
            }
            func_80076D68(a);
            break;
        case 1:
            if (b[2] == 0x3C) {
                func_80113110(a);
            } else {
                func_80063158(a);
            }
            func_80076D68(a);
            break;
        case 2:
            if (b[2] == 0x3C) {
                if (a[0x147] == 0) {
                    H(a, 0x14E) = 0x800;
                } else {
                    H(a, 0x14E) = 0;
                }
            }
            a[0x5E] = 0;
            H(a, 0x42) = 0;
            func_80054D14(a, 0x31, 4);
            H(a, 0x40) = 0x5A;
            a[7]++;
        case 3:
            if (--H(a, 0x40) == 0) {
                H(a, 0x40) = 0x5A;
                a[7]++;
                if (!(func_8009A450() & 1)) {
                    func_80054D14(a, 0x30, 0);
                } else {
                    func_80054D14(a, 0x2E, 0);
                }
            }
            if (b[0x5E] == 1) {
                a[7] = 5;
                if (!(func_8009A450() & 1)) {
                    func_80054D14(a, 0x32, 0);
                } else {
                    func_80054D14(a, 0x2D, 0);
                }
            } else {
                func_80113390(a, b);
                func_80076D68(a);
            }
            break;
        case 4:
            if (--H(a, 0x40) == 0) {
                a[7]--;
                if (H(a, 0x42) < 8) {
                    H(a, 0x42) = 8;
                }
                func_80054D14(a, 0x31, 4);
                H(a, 0x40) = ((func_8009A450() & 3) + 3) * 30;
            }
            func_80113390(a, b);
            func_80076D68(a);
            break;
        case 5:
            if (func_80076D68(a) == 1) {
                a[7] = 3;
                if (H(a, 0x42) < 8) {
                    H(a, 0x42) = 8;
                }
                func_80054D14(a, 0x31, 4);
                H(a, 0x40) = ((func_8009A450() & 3) + 3) * 30;
            }
            func_80113390(a, b);
            break;
        case 6:
            if (D_800ECF54 & 0xA0) {
                if ((D_800ECF54 & D_1F80016C) && a[0x147] == 0) {
                    a[7] = 0;
                    H(a, 0x154) = 0;
                    H(a, 0x42) = 0;
                    a[0] |= 4;
                    func_80054D14(a, 0x38, 0);
                } else if ((D_800ECF54 & D_1F80016E) && a[0x147] == 1) {
                    a[7] = 0;
                    H(a, 0x154) = 0;
                    H(a, 0x42) = 0;
                    a[0] |= 4;
                    func_80054D14(a, 0x38, 0);
                } else {
                    func_80076D68(a);
                }
            } else {
                H(a, 0x40) = 0x5A;
                H(a, 0x42) = 8;
                a[7] = 3;
                func_80054D14(a, 0xAB, 0);
            }
            break;
        }
    }
    p = *(u8 **)(a + 0x10);
    if (b[2] == 0x3C) {
        if (*(s32 *)(a + 0x158) != 0) {
            if (a[0x177] != 0 || a[0x147] != 0) {
                ang = -H(p, 0xC);
            } else {
                ang = H(p, 0xC);
            }
            H(a, 0x58) = ang;
            D_1F8000C8.x = H(a, 0x152);
            D_1F8000C8.y = H(a, 0x156);
            D_1F8000C8.z = 0;
            D_1F8000C0_aa14.x = 0;
            D_1F8000C0_aa14.y = H(a, 0x14E);
            D_1F8000C0_aa14.z = 0;
            func_80085480(&D_1F8000C0_aa14, &D_1F800000_d070);
            func_80084110(p + 0x18, &D_1F800000_d070, &D_1F800040_b149);
            func_80084470(&D_1F800040_b149, &D_1F8000C8, D_1F800040_b149.t);
            H(a, 0x2E) = H(p, 0x2C) + D_1F800040_b149.t[0];
            H(a, 0x32) = H(p, 0x30) + D_1F800040_b149.t[1];
            H(a, 0x36) = H(p, 0x34) + D_1F800040_b149.t[2];
        }
    } else {
        if (*(s32 *)(a + 0x158) != 0) {
            ang = H(a, 0x56) + 0x800;
            H(a, 0x2E) = H(p, 0x2C) + ((func_80083F50(ang) * H(a, 0x152)) >> 12);
            H(a, 0x36) = H(p, 0x34) - ((func_80083E80(ang) * H(a, 0x152)) >> 12);
        }
        H(a, 0x32) = H(p, 0x30) + H(a, 0x156);
    }
}

void func_80113ACC(void *arg0, void *arg1) {
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

extern u16 D_1F800172;
s32 func_80113C30(u8 *a, u8 *b)
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

extern u8 D_1F8000D0_b839[];
void func_80113E3C(u8 *a) {
    s32 k;

    switch (a[6]) {
    case 0:
        func_80054198(a);
        func_80054D14(a, 0x40, 0);
        a[7] = 0;
        a[6]++;
    case 1:
        if (D_800ECF54 & 0x10) {
            if (!(D_1F80017C_0fe7 & 3)) {
                func_80074590(5, 3, -0x3C);
            }
            k = 0;
            func_80054D14(a, 0x41, 0);
            func_80076D68(a);
        } else if (D_800ECF54 & 0x40) {
            if (!(D_1F80017C_0fe7 & 3)) {
                func_80074590(5, -2, -0x3C);
            }
            k = 1;
            func_80054D14(a, 0x42, 0);
            func_80076D68(a);
        } else {
            func_80076D68(a);
            func_80054D14(a, 0x40, 4);
            k = 2;
        }
        if (func_8006271C(a, k) != 0 && func_80055824() != 0) {
            a[5] = 4;
            a[6] = 2;
            a[0x164] = 0;
            M2C_FIELD(a, s32 *, 0x158) = 0;
            a[7] = 0;
            F16(a, 0x58) = 0;
            F16(a, 0x40) = 8;
            func_80074590(0x1D, 0, 0);
            func_80055E28(a, 0);
            a[0x149] = (a[0x14A] & 1) + 2;
            func_80054D14(a, 0x14, 0);
        }
        {
            u8 *cam = (u8 *)&D_1F8000D0_b839;
            s16 d = *(s16 *)(cam + 0x12) - *(s16 *)(cam + 6);
            if (d > 0) {
                if (d >= 0x7D0) {
                    *(s16 *)(cam + 6) += d - 0x7D0;
                }
            } else if (d < -0x258) {
                *(s16 *)(cam + 6) += d + 0x258;
            }
        }
        break;
    }
}

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8011403C);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80114294);

void func_801144F4(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 6);
    switch (temp_v1) {                              /* irregular */
    case 0:
        M2C_FIELD(arg0, s8 *, 0x146) = 0;
        func_80054198(arg0);
        func_80053D90(arg0);
        M2C_FIELD(arg0, u8 *, 6) = (u8) (M2C_FIELD(arg0, u8 *, 6) + 1);
        func_80054D14(arg0, 0x57, 4);
        func_8006625C(arg0);
        M2C_FIELD(arg0, s16 *, 0x172) = 0x5A;
        M2C_FIELD(arg0, u8 *, 0xD) = (u8) (M2C_FIELD(arg0, u8 *, 0xD) | 0x82);
        return;
    case 1:
        func_80076D68(arg0);
        return;
    case 2:
        M2C_FIELD(arg0, s8 *, 0) = 3;
        M2C_FIELD(arg0, s16 *, 0x172) = 0x14;
        func_8005444C(arg0);
        if (M2C_FIELD(arg0, u8 *, 0x29) == 0) {
            func_80056D44(arg0, 0);
            return;
        }
        M2C_FIELD(arg0, s8 *, 5) = 0;
        M2C_FIELD(arg0, u8 *, 6) = 0U;
        M2C_FIELD(arg0, s8 *, 7) = 0;
        return;
    }
}

void func_801145EC(void) {
    ((void (*)())func_80112838)();
}

void func_8011460C(void *a, void *b)
{
    func_80056B48(a, 1);
    func_8011237C(a, b);
    func_80055D5C(a);
}

void func_80114654(u8 *a)
{
    a[0x177] |= 1;
    *(s16 *)(a + 0x154) += 0x20;
    if (*(s16 *)(a + 0x154) > 0x200) {
        *(s16 *)(a + 0x154) = 0x200;
    }
    *(u16 *)(a + 0x42) += *(u16 *)(a + 0x154);
    if ((a[0x147] ^ a[0x15C]) == 0) {
        *(u16 *)(a + 0x14E) -= *(u16 *)(a + 0x154);
        *(u16 *)(a + 0x56) = *(u16 *)(a + 0x140) + 0x800;
    } else {
        *(u16 *)(a + 0x14E) += *(u16 *)(a + 0x154);
    }
    if (*(s16 *)(a + 0x42) > 0x400) {
        func_80074590(0x1B, 0, 0);
        D_800BF840 = 0x88;
        a[7]++;
    }
}

void func_80114730(u8 *a0, s32 a1)
{
    u8 *q = *(u8 **)(a0 + 0x158);

    if (q[0xC] == 4 && (q[2] == 0 || q[2] == 0x3C)) {
        func_801134E4(a0, q, a1);
    }
}

s32 func_80114784(u8 *a)
{
    u8 *b = *(u8 **)(a + 0x158);

    if (b[0xC] != 4) {
        return 0;
    }
    if (b[2] != 0x3B) {
        return 0;
    }
    return func_80113C30(a, b);
}

extern u16 D_1F8001A4;
void func_801147CC(u8 *a)
{
    s16 v[6];

    v[1] = *(u16 *)(a + 0x2E);
    v[3] = D_1F8001A4;
    v[5] = *(u16 *)(a + 0x36);
    func_800312D4(0x704, v, -10);
    v[3] += 0x50;
    func_800312D4(0x709, v, -10);
    func_80074590(7, 0, 0);
}

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80114840);

typedef struct { s16 l0, x, l1, y, l2, z; } V3Hi;
#define CH(o) (*(s16 *)(c + (o)))
#define AH(o) (*(s16 *)(a + (o)))
#define DH(o) (*(s16 *)(d + (o)))
void func_80114A18(u8 *c, u8 *a)
{
    V3Hi v;
    u8 *d;

    CH(0x26) = 0xFA;
    d = D_1F8000D0_b839;
    DH(0x1E) = -0x960;
    switch (c[3]) {
    case 0:
        c[3] = 1;
        if (a[0x2A] == 1) {
            DH(0x2) = 0x6FEA;
            DH(0x6) = -0x8F9;
            DH(0xA) = 0x4AC9;
        }
    case 1:
        c[0x64] &= 0x7F;
        if (a[0x2A] == 1) {
            if (AH(0x36) > 0x4E20) {
                c[0x64] |= 0x80;
                CH(0xA) = AH(0x2E);
                CH(0xE) = AH(0x32);
                CH(0x12) = AH(0x36);
                func_8006E3F4(c, c + 8);
                v.x = 0x6FEA;
                v.y = -0x8F9;
                v.z = 0x4AC9;
                func_8006CEC4(D_1F8000D0_b839, &v, 0xE0);
            } else if (AH(0x2E) > 0x64C8) {
                CH(0x26) = 0;
            }
        } else {
            c[3]++;
        }
        break;
    case 2:
        c[0x72] = 0;
        switch (a[0x2A]) {
        case 1:
            c[3]--;
            break;
        case 2:
            if (AH(0x32) < -0x1C20 && AH(0x36) > 0x3E1C) {
                c[0x72] = 2;
            }
            break;
        case 3:
            if (AH(0x32) < -0x1EA0 && AH(0x36) < 0x2A76) {
                c[0x72] = 3;
            }
            break;
        case 4:
        case 5:
            c[0x72] = 3;
            break;
        }
        break;
    }
}

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80114C1C);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_801151D8);

extern s8 D_1F800138[];
extern s8 D_1F80019B[];
void func_801153F8(void) {
    func_80045258(M2C_FIELD(*((volatile void **)D_1F800138), u8 *, 0x6E), 0xF);
    *((volatile s8 *)D_1F80019B) = 1;
    func_80051FB4();
}

extern u8 D_800E806C_5739;
void func_80115438(void)
{
    u8 *s = D_800BF808_1760;
    u8 *g;
    u8 k;

    s[0xE] = 0;
    D_800E806C_5739 = 0;
    D_1F800184 = 0;
    g = D_800E7E80;
    g[5] = 0x24;
    g[6] = 0;
    g[7] = 0;
    k = s[0xF];
    if (k == 2) {
        g[6] = 9;
    } else if (k == 4) {
        g[0x2A] = 0x13;
        *(s16 *)(g + 0x36) = 0x6A54;
    } else if (k == 10) {
        g[6] = 5;
    }
    func_80054198(g);
    g[0x16B] = 0;
}

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_801154D4);

void func_801155C4(u8 *p, u8 *a1)
{
    s16 x;

    p[0x72] = 0;
    switch (p[3]) {
    case 0:
        p[3] = 1;
    case 1:
        x = *(s16 *)(a1 + 0x2E);
        if (x >= 0x45ED) {
            p[0x72] = 2;
        } else if (x < 0x396C) {
            p[0x72] = 3;
        }
        break;
    }
}

INCLUDE_ASM("asm/a06/nonmatchings/a06", f_SpawnDonglinForestSceneActorsFromPlacementTable);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80115A04);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80115BC8);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80115D3C);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80115E9C);

void func_8011600C(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 4);
    switch (temp_v1) {                              /* irregular */
    case 0:
        if (M2C_FIELD(arg0, u8 *, 0x5E) == 0) {
            func_8004BEF4(arg0);
        }
        M2C_FIELD(arg0, u8 *, 4) = (u8) (M2C_FIELD(arg0, u8 *, 4) + 1);
        return;
    case 1:
        if (M2C_FIELD(arg0, u8 *, 0x5E) == 0) {
            func_80115E9C(arg0);
            return;
        }
        return;
    case 2:
        func_8004B9C8(arg0);
        return;
    case 3:
        func_8007A624(arg0);
        break;
    }
}

void func_801160D4(u8 *a)
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
            {
                s32 rs_t = k * *(s16 *)(a + 0x4A);
                y = rs_t;
            }
            z = k * *(s16 *)(a + 0x4C); 
            *(s32 *)(a + 0x2C) += x; 
            *(s32 *)(a + 0x30) += y; 
            *(s32 *)(a + 0x34) += z; 
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

void func_80116288(u8 *a)
{
    u8 *o = *(u8 **)(a + 0x10);

    switch (a[5]) {
    case 0:
        a[5]++;
        a[0] = 1;
    case 1:
        *(s16 *)(a + 0x2E) = *(s16 *)(*(u8 **)(o + 0xC8) + 0x2C);
        *(s16 *)(a + 0x32) = *(s16 *)(*(u8 **)(o + 0xC8) + 0x30) - 0xC8;
        *(s16 *)(a + 0x36) = *(s16 *)(*(u8 **)(o + 0xC8) + 0x34);
        break;
    }
    func_8007778C(a);
}

extern u8 D_800BF818_7697;
void func_80116310(u8 *a, u8 *b) {
    u8 *t;

    switch (a[5]) {
    case 0:
        a[5]++;
        F16(b, 0xE) = F16(b, 0xA);
        func_80072FE0(a);
        a[0x5E] = 1;
        break;
    case 1:
        if (D_800BF818_7697 == 2) {
            F16(a, 0x40) = 0;
            a[5]++;
        }
        break;
    case 2:
        if (++F16(a, 0x40) >= 0x19 && func_80073194(a) != 0) {
            a[0x5E] = 0;
            a[5]++;
        }
        break;
    case 3:
        t = D_800BF808_1760;
        if (t[0x10] == 3) {
            a[0x5E] = 1;
            a[5]++;
        } else if (t[0x10] == 7) {
            t[0x10] = 0;
            a[5] = 6;
            func_80074590(0x17, 0, 0);
            a[0x5E] = 1;
        }
        break;
    case 4:
        if (func_8007302C(a) != 0) {
            a[5]++;
        }
        break;
    case 6:
        if (func_8007302C(a) != 0) {
            F16(a, 0x40) = 0x18;
            a[5]++;
        }
        break;
    case 7:
        if (--F16(a, 0x40) == 0) {
            a[5]++;
        }
        break;
    case 8:
        if (func_800730C8(a) != 0) {
            a[5] = 3;
            func_80074590(0x18, 0, 0);
            D_800BF818_7697 = 0;
        }
        break;
    }
}

INCLUDE_ASM("asm/a06/nonmatchings/a06", f_UpdateDonglinInteriorEnvironmentActor);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_801168E4);

extern u8 D_800BFA22;
void func_80116AF8(u8 *a)
{
    switch (a[5]) {
    case 0:
        if (D_800BFA22 >= 0x18) {
            a[5]++;
        }
        break;
    case 1:
        *(s16 *)(*(u8 **)(a + 0xC0) + 8) += 8;
        *(s16 *)(*(u8 **)(a + 0xC4) + 8) -= 8;
        *(s16 *)(*(u8 **)(a + 0xC8) + 8) -= 8;
        if (*(s16 *)(*(u8 **)(a + 0xC0) + 8) == 0) {
            *(s16 *)(a + 0x40) = 0xC;
            a[5]++;
            func_8004ED94(0x41, 0x41);
        }
        break;
    case 2:
        if (--*(s16 *)(a + 0x40) == -1) {
            *(s16 *)(a + 0x4A) = 0;
            a[5]++;
            D_800BFA22 = 0x19;
        }
        *(s16 *)(*(u8 **)(a + 0xC0) + 2) = (D_1F80017C_0fe7 & 1) * 6;
        **(s16 **)(a + 0xC0) = ((func_8009A450() & 3) - 2) * 6;
        break;
    case 3:
        *(s32 *)(a + 0x30) += *(s16 *)(a + 0x4A) << 8;
        if ((*(s16 *)(a + 0x4A) += 0x100) > 0x1000) {
            *(s16 *)(a + 0x4A) = 0x1000;
        }
        if (*(s16 *)(a + 0x32) > *(s16 *)(a + 0x8A)) {
            *(s16 *)(a + 0x32) = *(s16 *)(a + 0x8A);
            a[5]++;
            D_800BFA22 = 0x1A;
        }
        break;
    case 4:
        break;
    }
    a[1] = 1;
    func_800517F8(a);
}

typedef struct { u8 pad[0xC0]; u8 *parts[1]; } PartsOwner;
typedef struct { s16 v[4]; } PartInit;
extern s16 D_800ED098;
typedef struct { s16 v[5]; } PartInit5;
extern PartInit5 D_80144CF4[];
void func_80116D00(PartsOwner *a)
{
    s32 i;
    u8 *q;

    a->pad[8] = 2;
    if (D_800ED098 < a->pad[8]) {
        a->pad[4] = 3;
        return;
    }
    a->pad[9] = 2;
    a->pad[0xD] = 6;
    a->pad[0xB] = 0;
    *(s16 *)(a->pad + 0x54) = 0;
    *(s16 *)(a->pad + 0x56) = 0x400;
    *(s16 *)(a->pad + 0x58) = 0;
    func_8004B354(a, 1);
    for (i = 0; i < a->pad[8]; i++) {
        q = func_8007AAE8();
        a->parts[i] = q;
        *(s16 *)(q + 6) = D_80144CF4[i].v[0];
        *(s16 *)(a->parts[i] + 0) = D_80144CF4[i].v[1];
        *(s16 *)(a->parts[i] + 2) = D_80144CF4[i].v[2];
        *(s16 *)(a->parts[i] + 4) = D_80144CF4[i].v[3];
        *(s16 *)(a->parts[i] + 8) = 0;
        *(s16 *)(a->parts[i] + 0xA) = 0;
        *(s16 *)(a->parts[i] + 0xC) = 0;
        func_80051B04(a->parts[i], 0xC, D_80144CF4[i].v[4]);
        a->parts[i][0x3F] = 0xF0;
    }
}

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80116E48);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80116FCC);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80117290);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_801174BC);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_801176D4);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_801178A4);

extern u8 D_800BFA20;
void func_80117AAC(void *arg0) {
    s16 temp_v0;
    u8 temp_v1;
    u8 temp_v1_2;

    temp_v1 = M2C_FIELD(arg0, u8 *, 6);
    switch (temp_v1) {                              /* irregular */
    case 0:
        if ((u8) D_800BFA20 >= 8U) {
            M2C_FIELD(arg0, u8 *, 6) = 1U;
            M2C_FIELD(arg0, s16 *, 0x40) = 0x1E;
            return;
        }
        return;
    case 1:
        func_8007E9C8(0xFFFFFF, 1, 4);
        temp_v0 = (u16) M2C_FIELD(arg0, s16 *, 0x40) - 1;
        M2C_FIELD(arg0, s16 *, 0x40) = temp_v0;
        if (temp_v0 == -1) {
            M2C_FIELD(arg0, s16 *, 0x40) = 0xF0;
            M2C_FIELD(arg0, u8 *, 6) = (u8) (M2C_FIELD(arg0, u8 *, 6) + 1);
            return;
        }
        break;
    case 2:
        temp_v1_2 = (u8) M2C_FIELD(arg0, s16 *, 0x40);
        func_8007E9C8((temp_v1_2 << 0x10) | (temp_v1_2 << 8) | temp_v1_2, 1, 4);
        if (M2C_FIELD(arg0, s16 *, 0x40) >= 0x21) {
            M2C_FIELD(arg0, s16 *, 0x40) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0x40) - 0x20);
            return;
        }
        func_80051B04(M2C_FIELD(arg0, s32 *, 0xC0), 0xC, 0x48);
        D_800BFA20 = 9;
        M2C_FIELD(arg0, u8 *, 6) = 0U;
        M2C_FIELD(arg0, u8 *, 5) = (u8) (M2C_FIELD(arg0, u8 *, 5) + 1);
        break;
    }
}

extern PartInit D_80144D78[];
void func_80117BD4(PartsOwner *a)
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
        *(s16 *)(q + 6) = D_80144D78[i].v[0];
        *(s16 *)(a->parts[i] + 0) = D_80144D78[i].v[1];
        *(s16 *)(a->parts[i] + 2) = D_80144D78[i].v[2];
        *(s16 *)(a->parts[i] + 4) = D_80144D78[i].v[3];
        *(s16 *)(a->parts[i] + 8) = 0;
        *(s16 *)(a->parts[i] + 0xA) = 0;
        *(s16 *)(a->parts[i] + 0xC) = 0;
        func_80051B04(a->parts[i], 0xC, i + 0x4A);
    }
    *(s16 *)(a->pad + 0x54) = 0;
    *(s16 *)(a->pad + 0x56) = 0;
    *(s16 *)(a->pad + 0x58) = 0;
}

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80117CF4);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80117F34);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_801180A0);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_801182F4);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8011847C);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80118664);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_801188B0);

extern u8 D_8014CEF0[];
extern s32 D_800ECF80;
extern void *D_800ECF80_1c35;
extern u8 D_80017334[];
extern s8 *D_800ECF58[];
extern u8 D_800BF8D5;
extern u16 D_1F8000E2;
extern u8 D_800BF8D2;
extern u8 D_8014D014[];
extern u8 D_80144D28[];
static inline void func_80119674_inl(u8 *p)
{
    *(s32 *)(p + 0x3C) = D_800ECF80;
    func_80077B38(p, D_8014CEF0, 5);
    p[0xD] = 1;
    p[0xB] = 0x11;
    *(s16 *)(p + 0x7A) = 0x1000;
    *(s16 *)(p + 0x7C) = 0x1000;
    *(s16 *)(p + 0x7E) = 0x1000;
    *(s16 *)(p + 0x5C) = 0;
    *(s16 *)(p + 0x5A) = 0;
    p[0x47] = 0;
    p[8] = 0xCE;
}
static inline void func_801196E4_inl(u8 *a)
{
    s16 v;
    switch (a[6]) {
    default:
        break;
    case 0:
        a[6]++;
        *(s16 *)(a + 0x50) = 0;
        break;
    case 1:
        *(s16 *)(a + 0x50) = (*(s16 *)(a + 0x50) + 0x40) & 0xFFF;
        v = (func_80083E80(*(s16 *)(a + 0x50)) >> 2) + 0x1400;
        *(s16 *)(a + 0x7A) = v;
        *(s16 *)(a + 0x7E) = v;
        *(s16 *)(a + 0x7C) = v;
        break;
    }
    a[1] = 1;
}
static inline void func_80119998_inl(u8 *a)
{
    void func_80120FB4();
    u8 *p;

    func_80051B70(a, 0xC, 0x2A);
    *(s16 *)(a + 0x56) = 0x800;
    *(s16 *)(a + 0x54) = 0;
    *(s16 *)(a + 0x58) = 0;
    if (D_800BF8D5 == 0xFF) {
        *(s16 *)(a + 0x32) = -0x2178;
        a[5] = 0x63;
    }
    p = func_80072DDC(a, 1, 4, 0x17);
    if (p != NULL) {
        *(void **)(p + 0x1C) = func_80120FB4;
        p[3] = 0;
        p[0x28] |= 0x80;
        *(s16 *)(p + 0x2E) = *(s16 *)(a + 0x2E);
        *(s16 *)(p + 0x32) = *(s16 *)(a + 0x32);
        *(s16 *)(p + 0x36) = *(s16 *)(a + 0x36);
    }
}
static inline void func_80119B64_inl(u8 *a) {
    M2C_FIELD(a, void **, 0x3C) = D_800ECF80_1c35;
    func_80077B38(a, D_8014CEF0, 9);
    M2C_FIELD(a, s16 *, 0x5C) = 0;
    a[0xD] = 3;
    a[0xB] = 0x11;
    M2C_FIELD(a, s16 *, 0x7A) = 0x2800;
    M2C_FIELD(a, s16 *, 0x7C) = 0x2000;
    a[8] = 0x30;
    a[0x18] = a[0x19] = a[0x1A] = 0x40;
    M2C_FIELD(a, s16 *, 0x7E) = 0x2800;
    M2C_FIELD(a, s16 *, 0x5A) = 0;
    a[0x47] = 0;
    M2C_FIELD(a, s16 *, 0x60) = 150;
}
static inline void func_80119D94_inl(u8 *a)
{
    s32 s = a[5];
    u8 *g;

    switch (s) {
    case 0:
        if (D_800BF8D2 == 0xFF) {
            a[5] = 1;
        }
        break;
    case 1:
        if (func_8005308C()) {
            a[5]++;
            func_80042354(1, 1);
            g = (u8 *)&D_800BF870;
            g[0x1AD] |= 1;
            func_80040CDC(a, D_8014D014, D_80144D28);
            a[0x70] = s;
        }
        break;
    case 2:
        func_80041098(a);
        if (a[0x70] == 0xFF) {
            a[4] = 3;
            func_80042310();
        }
        break;
    }
}
static inline void func_80119E88_inl(u8 *p)
{
    if (D_800BF8D3 != 0xFF) {
        func_80051B70(p, 0xC, 0x4C);
    } else {
        func_80051B70(p, 0xC, 0x4D);
    }
    *(s16 *)(p + 0x56) = -0x244;
    func_800517F8(p);
}
static inline void func_8011A024_inl(u8 *p)
{
    switch (p[5]) {
    case 0:
        func_801178A4(p);
        break;
    case 1:
        func_80117AAC(p);
        break;
    case 2:
        break;
    }
    func_8007778C(p);
    func_800517F8(p);
}
static inline void func_8011A104_inl(u8 *a)
{
    *(s32 *)(a + 0x3C) = D_800ECF80;
    func_80077B38(a, D_8014CEF0, a[0x5E] + 0x12);
    a[0xD] = 1;
    a[0xB] = 0x11;
    *(s16 *)(a + 0x7A) = 0x1000;
    *(s16 *)(a + 0x7C) = 0x1000;
    *(s16 *)(a + 0x7E) = 0x1000;
    a[8] = 0xFB;
    *(s16 *)(a + 0x2E) = 0x5D33;
    *(s16 *)(a + 0x32) = -0x1C20;
    *(s16 *)(a + 0x36) = 0x412C;
    *(s16 *)(a + 0x4A) = -0x2800;
    *(s16 *)(a + 0x5C) = 0;
    *(s16 *)(a + 0x5A) = 0;
    a[0x47] = 0;
    *(s16 *)(a + 0x50) = 0x280;
    *(s16 *)(a + 0x32) += 0x64;
}
static inline void func_8011A2E8_inl(u8 *p)
{
    func_80051B70(p, 0xC, 0x47);
    p[0xD] |= 4;
    (*(u8 **)(p + 0xC0))[0x3F] = 0xF6;
    *(s16 *)(p + 0x2E) = 0x2380;
    *(s16 *)(p + 0x32) = -0xC76;
    *(s16 *)(p + 0x36) = 0x34D4;
}
static inline void func_8011A344_inl(void *arg0) {
    if (func_8007778C(arg0) != 0) {
        func_800517F8(arg0);
    }
    if (D_800BF870.pad1[0x162] == 6) {
        D_800BF870.pad1[0x162] = 7;
        func_80027144(M2C_FIELD(M2C_FIELD(arg0, void **, 0xC0), s32 *, 0x40), arg0 + 0x2C, 0x700, 0x24);
        func_80074590(0xC, 0, 0);
        M2C_FIELD(arg0, s8 *, 4) = 3;
    }
}
static inline void func_8011A3C4_inl(u8 *p)
{
    func_80051B70(p, 0xC, 0x59);
    p[0xD] |= 4;
    (*(u8 **)(p + 0xC0))[0x3F] = 0x20;
    func_800517F8(p);
}
static inline void func_8011A410_inl(u8 *a)
{
    u8 *o = *(u8 **)(a + 0x10);

    func_80051B70(a, 0xC, 0x1C);
    *(s16 *)(a + 0x54) = 0;
    *(s16 *)(a + 0x56) = 0;
    *(s16 *)(a + 0x58) = 0;
    *(s16 *)(a + 0x2E) = *(s16 *)(o + 0x2E);
    *(s16 *)(a + 0x32) = *(s16 *)(o + 0x32) - 0x50;
    *(s16 *)(a + 0x36) = *(s16 *)(o + 0x36);
    func_8004B354(a, 1);
    *(s16 *)(a + 0xB8) = 0;
    *(s16 *)(a + 0xBA) = 0;
    *(s16 *)(a + 0xBC) = 0;
}
static inline void func_8011A48C_inl(u8 *p)
{
    *(s32 *)(p + 0x3C) = (s32)D_800ECF58[0];
    func_80077B38(p, D_80017334, 0x17C);
    p[0xB] = 0x11;
    p[0xD] = 0;
    *(s16 *)(p + 0x5C) = 0;
    *(s16 *)(p + 0x7A) = 0x1400;
    *(s16 *)(p + 0x7C) = 0x1400;
    *(s16 *)(p + 0x7E) = 0x1400;
    *(s16 *)(p + 0x5A) = 0;
    p[0x47] = 0;
    p[8] = 0;
}
static inline void func_8011A4F4_inl(u8 *p)
{
    *(s32 *)(p + 0x3C) = (s32)D_800ECF58[0];
    func_80077B38(p, D_80017334, 0x17C);
    p[0xB] = 0x11;
    p[0xD] = 0;
    *(s16 *)(p + 0x5C) = 0;
    *(s16 *)(p + 0x7A) = 0x1400;
    *(s16 *)(p + 0x7C) = 0x1400;
    *(s16 *)(p + 0x7E) = 0x1400;
    *(s16 *)(p + 0x5A) = 0;
    p[0x47] = 0;
    p[8] = 0;
    p[0x5E] = p[0x2E];
}
void f_UpdateDonglinInteriorQuestObjectActor(u8 *a)
{
    u8 *g;
    u8 *p;
    s32 i;
    s32 s;

    switch (a[4]) {
    case 0:
        a[4] = 1;
        switch (a[3]) {
        case 0:
            func_80119674_inl(a);
            break;
        case 1:
            *(s32 *)(a + 0x3C) = D_800ECF80;
            func_80077B38(a, D_8014CEF0, 6);
            a[0xD] = 1;
            H(a, 0x5C) = 0;
            a[0xB] = 0x10;
            H(a, 0x5A) = 0;
            a[0x47] = 0;
            a[8] = 0;
            break;
        case 2:
            break;
        case 3:
            func_801168E4(a);
            break;
        case 4:
            func_80116D00(a);
            break;
        case 5:
            func_80051B70(a, 0xC, 0x26);
            H(a, 0x54) = 0;
            H(a, 0x56) = 0x800;
            H(a, 0x58) = 0;
            break;
        case 6:
            func_80119998_inl(a);
            break;
        case 7:
            func_80119B64_inl(a);
            break;
        case 8:
            func_80116FCC(a);
            break;
        case 9:
            func_80119E88_inl(a);
            break;
        case 10:
            g = (u8 *)&D_800BF870;
            if (g[0xB1] == 0xFF) {
                if (g[0xB2] == 0xFF || g[0x294] != 0) {
                    func_80051B70(a, 0xC, 0x48);
                    a[5] = 2;
                } else {
                    func_80051B70(a, 0xC, 0x49);
                    a[5] = 1;
                }
            } else {
                func_80051B70(a, 0xC, 0x48);
                a[5] = 0;
                for (i = 0; i < g[0x1B1] && i < 10; i++) {
                    func_80141020(a + 0x2C, 1, 0);
                }
            }
            break;
        case 11:
            func_8011A104_inl(a);
            break;
        case 12:
            func_80117BD4(a);
            break;
        case 13:
            func_8011A2E8_inl(a);
            break;
        case 14:
            func_8011A3C4_inl(a);
            break;
        case 15:
            func_8011A410_inl(a);
            break;
        case 16:
            func_8011A48C_inl(a);
            break;
        case 17:
            func_8011A4F4_inl(a);
            break;
        }
        break;
    case 1:
        switch (a[3]) {
        case 0:
            func_801196E4_inl(a);
            break;
        case 1:
            func_80077B5C(a);
            a[1] = 1;
            break;
        case 2:
            break;
        case 3:
            func_80116AF8(a);
            break;
        case 4:
            switch (a[5]) {
            case 0:
                if (D_800BFA22 == 0) {
                    a[5] = 1;
                } else {
                    a[5] = 2;
                }
                break;
            case 1:
                if (D_800BFA22 != 0) {
                    a[5] = 2;
                    a[6] = 0;
                } else {
                    a[1] = 1;
                    func_800517F8(a);
                    func_8004B374(a, 1);
                }
                break;
            case 2:
                func_80116E48(a);
                break;
            }
            break;
        case 5:
            a[1] = 1;
            func_800517F8(a);
            break;
        case 6:
            switch (a[5]) {
            case 0:
                if (D_800BFA22 >= 0x19) {
                    a[5] = 1;
                    H(a, 0x4A) = 0;
                }
                break;
            case 1:
                *(s32 *)(a + 0x30) -= H(a, 0x4A) << 8;
                H(a, 0x4A) += 0x100;
                if (H(a, 0x4A) > 0x1000) {
                    H(a, 0x4A) = 0x1000;
                }
                if (D_800BFA22 >= 0x1A) {
                    a[5]++;
                }
                break;
            case 2:
                break;
            }
            a[1] = 1;
            func_800517F8(a);
            break;
        case 7:
            p = *(u8 **)(a + 0x10);
            switch (a[5]) {
            case 0:
                if (p[0x5E] == 1) {
                    a[5] = p[0x5E];
                }
                break;
            case 1:
                H(a, 0x60) -= 10;
                H(a, 0x7C) -= 0x200;
                a[0x18] += 0x10;
                a[0x19] += 0x10;
                a[0x1A] += 0x10;
                if (a[0x18] == 0) {
                    a[4] = 3;
                }
                break;
            }
            H(a, 0x2E) = H(p, 0x2E);
            H(a, 0x32) = H(p, 0x32) - H(a, 0x60);
            H(a, 0x36) = H(p, 0x36);
            a[1] = p[1];
            func_80077B5C(a);
            break;
        case 8:
            func_800778E4(a, (s16)(D_1F8000E2 - H(a, 0x32)));
            s = a[5];
            switch (s) {
            case 0:
                if (func_80117290(a) != 0) {
                    a[5]++;
                }
                break;
            case 1:
                if (func_801174BC(a) != 0) {
                    a[5]++;
                }
                break;
            case 2:
                if (func_801176D4(a) != 0) {
                    a[4] = s;
                    a[5] = 0;
                }
                break;
            }
            func_80051844(a);
            break;
        case 9:
            if ((D_800BF870.pad1[0x62] != 0xFF) && (D_800BF870.pad1[0x62] & 4)) {
                D_800BF870.pad1[0x62] &= 0xFB;
                func_80051B04(M2C_FIELD(a, s32 *, 0xC0), 0xC, 0x4D);
            }
            func_8007778C(a);
            break;
        case 10:
            func_8011A024_inl(a);
            break;
        case 11:
            a[1] = 1;
            p = *(u8 **)(a + 0x10);
            switch (a[5]) {
            case 0:
                H(a, 0x4A) += H(a, 0x50);
                if (H(a, 0x4A) > 0) {
                    H(a, 0x50) = H(a, 0x50) >> 2;
                    a[5]++;
                }
                *(s32 *)(a + 0x30) += H(a, 0x4A) << 8;
                break;
            case 1:
                H(a, 0x4A) += H(a, 0x50);
                *(s32 *)(a + 0x30) += H(a, 0x4A) << 8;
                if (*(s32 *)(*(u8 **)(p + 0xDC) + 0x30) - 0x3C < H(a, 0x32)) {
                    a[5]++;
                }
                break;
            case 2:
                H(a, 0x2E) = H(*(u8 **)(p + 0xDC), 0x2C);
                H(a, 0x32) = H(*(u8 **)(p + 0xDC), 0x30) - 0xF;
                H(a, 0x36) = H(*(u8 **)(p + 0xDC), 0x34);
                break;
            }
            break;
        case 12:
            func_80117CF4(a);
            break;
        case 13:
            func_8011A344_inl(a);
            break;
        case 14:
            func_8007778C(a);
            break;
        case 15:
            func_80117F34(a);
            break;
        case 16:
            func_801180A0(a);
            break;
        case 17:
            func_801188B0(a);
            break;
        }
        break;
    case 2:
        if (a[3] == 8) {
            func_80119D94_inl(a);
        }
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

void func_80119674(u8 *p)
{
    *(s32 *)(p + 0x3C) = D_800ECF80;
    func_80077B38(p, D_8014CEF0, 5);
    p[0xD] = 1;
    p[0xB] = 0x11;
    *(s16 *)(p + 0x7A) = 0x1000;
    *(s16 *)(p + 0x7C) = 0x1000;
    *(s16 *)(p + 0x7E) = 0x1000;
    *(s16 *)(p + 0x5C) = 0;
    *(s16 *)(p + 0x5A) = 0;
    p[0x47] = 0;
    p[8] = 0xCE;
}

void func_801196E4(u8 *a)
{
    s16 v;
    switch (a[6]) {
    default:
        break;
    case 0:
        a[6]++;
        *(s16 *)(a + 0x50) = 0;
        break;
    case 1:
        *(s16 *)(a + 0x50) = (*(s16 *)(a + 0x50) + 0x40) & 0xFFF;
        v = (func_80083E80(*(s16 *)(a + 0x50)) >> 2) + 0x1400;
        *(s16 *)(a + 0x7A) = v;
        *(s16 *)(a + 0x7E) = v;
        *(s16 *)(a + 0x7C) = v;
        break;
    }
    a[1] = 1;
}

void func_80136848();
void func_80119764(u8 *p)
{
    *(s32 *)(p + 0x3C) = D_800ECF80;
    func_80077B38(p, D_8014CEF0, 6);
    p[0xD] = 1;
    *(s16 *)(p + 0x5C) = 0;
    p[0xB] = 0x10;
    *(s16 *)(p + 0x5A) = 0;
    p[0x47] = 0;
    p[8] = 0;
}

void func_801197C0(void *arg0) {
    func_80077B5C();
    M2C_FIELD(arg0, s8 *, 1) = 1;
}

s32 func_801197EC(void *a0)
{
    u8 *r = func_80072DDC(a0, 1, 3, 0x10);

    if (r) {
        *(void **)(r + 0x1C) = f_UpdateDonglinInteriorQuestObjectActor;
        r[3] = 0xF;
        r[0x28] |= 0x80;
    }
    return 1;
}

void func_8011983C(void *arg0) {
    M2C_FIELD(arg0, s8 *, 1) = 1;
    func_800517F8();
    func_8004B374(arg0, 1);
}

void func_80119874(u8 *a)
{
    switch (a[5]) {
    case 0:
        if (D_800BFA22 == 0) {
            a[5] = 1;
        } else {
            a[5] = 2;
        }
        break;
    case 1:
        if (D_800BFA22 != 0) {
            a[5] = 2;
            a[6] = 0;
            break;
        }
        a[1] = 1;
        func_800517F8(a);
        func_8004B374(a, 1);
        break;
    case 2:
        func_80116E48(a);
        break;
    }
}

void func_80119938(u8 *p)
{
    func_80051B70(p, 0xC, 0x26);
    *(s16 *)(p + 0x54) = 0;
    *(s16 *)(p + 0x56) = 0x800;
    *(s16 *)(p + 0x58) = 0;
}

void func_80119974(void *arg0) {
    M2C_FIELD(arg0, s8 *, 1) = 1;
    func_800517F8();
}

void func_80120FB4();
void func_80119998(u8 *a)
{
    u8 *p;

    func_80051B70(a, 0xC, 0x2A);
    *(s16 *)(a + 0x56) = 0x800;
    *(s16 *)(a + 0x54) = 0;
    *(s16 *)(a + 0x58) = 0;
    if (D_800BF8D5 == 0xFF) {
        *(s16 *)(a + 0x32) = -0x2178;
        a[5] = 0x63;
    }
    p = func_80072DDC(a, 1, 4, 0x17);
    if (p != NULL) {
        *(void **)(p + 0x1C) = func_80120FB4;
        p[3] = 0;
        p[0x28] |= 0x80;
        *(s16 *)(p + 0x2E) = *(s16 *)(a + 0x2E);
        *(s16 *)(p + 0x32) = *(s16 *)(a + 0x32);
        *(s16 *)(p + 0x36) = *(s16 *)(a + 0x36);
    }
}

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80119A50);

void f_UpdateDonglinInteriorQuestObjectActor();
u8 *func_80119B20(void *a)
{
    u8 *r = func_80072DDC(a, 0, 3, 0x10);

    if (r != NULL) {
        *(void **)(r + 0x1C) = f_UpdateDonglinInteriorQuestObjectActor;
        r[3] = 7;
    }
    return r;
}

void func_80119B64(u8 *a) {
    M2C_FIELD(a, void **, 0x3C) = D_800ECF80_1c35;
    func_80077B38(a, D_8014CEF0, 9);
    M2C_FIELD(a, s16 *, 0x5C) = 0;
    a[0xD] = 3;
    a[0xB] = 0x11;
    M2C_FIELD(a, s16 *, 0x7A) = 0x2800;
    M2C_FIELD(a, s16 *, 0x7C) = 0x2000;
    a[8] = 0x30;
    a[0x18] = a[0x19] = a[0x1A] = 0x40;
    M2C_FIELD(a, s16 *, 0x7E) = 0x2800;
    M2C_FIELD(a, s16 *, 0x5A) = 0;
    a[0x47] = 0;
    M2C_FIELD(a, s16 *, 0x60) = 150;
}

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80119BF0);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80119CC0);

void func_80119D94(u8 *a)
{
    s32 s = a[5];
    u8 *g;

    switch (s) {
    case 0:
        if (D_800BF8D2 == 0xFF) {
            a[5] = 1;
        }
        break;
    case 1:
        if (func_8005308C()) {
            a[5]++;
            func_80042354(1, 1);
            g = (u8 *)&D_800BF870;
            g[0x1AD] |= 1;
            func_80040CDC(a, D_8014D014, D_80144D28);
            a[0x70] = s;
        }
        break;
    case 2:
        func_80041098(a);
        if (a[0x70] == 0xFF) {
            a[4] = 3;
            func_80042310();
        }
        break;
    }
}

void func_80119E88(u8 *p)
{
    if (D_800BF8D3 != 0xFF) {
        func_80051B70(p, 0xC, 0x4C);
    } else {
        func_80051B70(p, 0xC, 0x4D);
    }
    *(s16 *)(p + 0x56) = -0x244;
    func_800517F8(p);
}

void func_80119EE8(void *arg0) {
    if ((D_800BF870.pad1[0x62] != 0xFF) && (D_800BF870.pad1[0x62] & 4)) {
        D_800BF870.pad1[0x62] &= 0xFB;
        func_80051B04(M2C_FIELD(arg0, s32 *, 0xC0), 0xC, 0x4D);
    }
    func_8007778C(arg0);
}

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80119F44);

extern u16 D_1F800160;
extern u16 D_1F800164;
void func_8011A024(u8 *p)
{
    switch (p[5]) {
    case 0:
        func_801178A4(p);
        break;
    case 1:
        func_80117AAC(p);
        break;
    case 2:
        break;
    }
    func_8007778C(p);
    func_800517F8(p);
}

u8 *func_8011A08C(void *a0, u8 a1)
{
    u8 *r = func_8007A980(0, 3, 1);

    if (r == 0) {
        return 0;
    }
    r[2] = 0x10;
    r[3] = 0xB;
    r[0x5E] = a1;
    *(void **)(r + 0x1C) = f_UpdateDonglinInteriorQuestObjectActor;
    *(void **)(r + 0x10) = a0;
    r[0x28] |= 0x80;
    return r;
}

void func_8011A104(u8 *a)
{
    *(s32 *)(a + 0x3C) = D_800ECF80;
    func_80077B38(a, D_8014CEF0, a[0x5E] + 0x12);
    a[0xD] = 1;
    a[0xB] = 0x11;
    *(s16 *)(a + 0x7A) = 0x1000;
    *(s16 *)(a + 0x7C) = 0x1000;
    *(s16 *)(a + 0x7E) = 0x1000;
    a[8] = 0xFB;
    *(s16 *)(a + 0x2E) = 0x5D33;
    *(s16 *)(a + 0x32) = -0x1C20;
    *(s16 *)(a + 0x36) = 0x412C;
    *(s16 *)(a + 0x4A) = -0x2800;
    *(s16 *)(a + 0x5C) = 0;
    *(s16 *)(a + 0x5A) = 0;
    a[0x47] = 0;
    *(s16 *)(a + 0x50) = 0x280;
    *(s16 *)(a + 0x32) += 0x64;
}

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8011A1AC);

void func_8011A2E8(u8 *p)
{
    func_80051B70(p, 0xC, 0x47);
    p[0xD] |= 4;
    (*(u8 **)(p + 0xC0))[0x3F] = 0xF6;
    *(s16 *)(p + 0x2E) = 0x2380;
    *(s16 *)(p + 0x32) = -0xC76;
    *(s16 *)(p + 0x36) = 0x34D4;
}

void func_8011A344(void *arg0) {
    if (func_8007778C() != 0) {
        func_800517F8(arg0);
    }
    if (D_800BF870.pad1[0x162] == 6) {
        D_800BF870.pad1[0x162] = 7;
        func_80027144(M2C_FIELD(M2C_FIELD(arg0, void **, 0xC0), s32 *, 0x40), arg0 + 0x2C, 0x700, 0x24);
        func_80074590(0xC, 0, 0);
        M2C_FIELD(arg0, s8 *, 4) = 3;
    }
}

void func_8011A3C4(u8 *p)
{
    func_80051B70(p, 0xC, 0x59);
    p[0xD] |= 4;
    (*(u8 **)(p + 0xC0))[0x3F] = 0x20;
    func_800517F8(p);
}

void func_8011A410(u8 *a)
{
    u8 *o = *(u8 **)(a + 0x10);

    func_80051B70(a, 0xC, 0x1C);
    *(s16 *)(a + 0x54) = 0;
    *(s16 *)(a + 0x56) = 0;
    *(s16 *)(a + 0x58) = 0;
    *(s16 *)(a + 0x2E) = *(s16 *)(o + 0x2E);
    *(s16 *)(a + 0x32) = *(s16 *)(o + 0x32) - 0x50;
    *(s16 *)(a + 0x36) = *(s16 *)(o + 0x36);
    func_8004B354(a, 1);
    *(s16 *)(a + 0xB8) = 0;
    *(s16 *)(a + 0xBA) = 0;
    *(s16 *)(a + 0xBC) = 0;
}

void func_8011A48C(u8 *p)
{
    *(s32 *)(p + 0x3C) = (s32)D_800ECF58[0];
    func_80077B38(p, D_80017334, 0x17C);
    p[0xB] = 0x11;
    p[0xD] = 0;
    *(s16 *)(p + 0x5C) = 0;
    *(s16 *)(p + 0x7A) = 0x1400;
    *(s16 *)(p + 0x7C) = 0x1400;
    *(s16 *)(p + 0x7E) = 0x1400;
    *(s16 *)(p + 0x5A) = 0;
    p[0x47] = 0;
    p[8] = 0;
}

void func_8011A4F4(u8 *p)
{
    *(s32 *)(p + 0x3C) = (s32)D_800ECF58[0];
    func_80077B38(p, D_80017334, 0x17C);
    p[0xB] = 0x11;
    p[0xD] = 0;
    *(s16 *)(p + 0x5C) = 0;
    *(s16 *)(p + 0x7A) = 0x1400;
    *(s16 *)(p + 0x7C) = 0x1400;
    *(s16 *)(p + 0x7E) = 0x1400;
    *(s16 *)(p + 0x5A) = 0;
    p[0x47] = 0;
    p[8] = 0;
    p[0x5E] = p[0x2E];
}

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8011A564);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8011A7A8);

void func_8011A8B8(u8 *a) {
    s16 r = func_8009A450();

    if (r & 1) {
        M2C_FIELD(a, s16 *, 0x44) = 0x800;
    } else {
        M2C_FIELD(a, s16 *, 0x44) = -0x800;
    }
    if (r & 2) {
        M2C_FIELD(a, s16 *, 0x4E) = 0x180;
    } else {
        M2C_FIELD(a, s16 *, 0x54) = 0;
        M2C_FIELD(a, s16 *, 0x4E) = 0;
    }
    M2C_FIELD(a, s16 *, 0x44) += r & 0x300;
    if (a[3] == 0) {
        M2C_FIELD(a, s16 *, 0x4A) = (r & 0x700) + 0x1000;
        M2C_FIELD(a, s16 *, 0x50) = (r & 0x30) - 0x100;
        M2C_FIELD(a, s16 *, 0x60) = -0x400 - (r & 0x70);
    } else {
        s16 k = -0xA00;

        M2C_FIELD(a, s16 *, 0x4A) = k - (r & 0x700);
        M2C_FIELD(a, s16 *, 0x50) = (r & 0x30) + 0xC0;
        M2C_FIELD(a, s16 *, 0x60) = 0x1000;
    }
}

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8011A974);

/* func_8011AD3C, inlined */
static inline void func_8011AD3C_inl(void *arg0) {
    u8 temp_v0;
    void *temp_v1;

    temp_v1 = M2C_FIELD(arg0, void **, 0x10);
    temp_v0 = M2C_FIELD(temp_v1, u8 *, 1);
    M2C_FIELD(arg0, u8 *, 1) = temp_v0;
    if (temp_v0 & 0xFF) {
        M2C_FIELD(arg0, u16 *, 0x60) = (u16) M2C_FIELD(temp_v1, u16 *, 0x2E);
        M2C_FIELD(arg0, u16 *, 0x62) = (u16) M2C_FIELD(temp_v1, u16 *, 0x32);
        M2C_FIELD(arg0, s16 *, 0x64) = (s16) (M2C_FIELD(temp_v1, u16 *, 0x36) - 4);
        M2C_FIELD(arg0, u16 *, 0x66) = (u16) M2C_FIELD(temp_v1, u16 *, 0x2E);
        M2C_FIELD(arg0, u16 *, 0x68) = (u16) M2C_FIELD(temp_v1, u16 *, 0x32);
        M2C_FIELD(arg0, s16 *, 0x6A) = (s16) (M2C_FIELD(temp_v1, u16 *, 0x36) + 4);
        M2C_FIELD(arg0, u16 *, 0x6C) = (u16) M2C_FIELD(temp_v1, u16 *, 0x6A);
        M2C_FIELD(arg0, u16 *, 0x6E) = (u16) M2C_FIELD(temp_v1, u16 *, 0x6C);
        M2C_FIELD(arg0, s16 *, 0x70) = (s16) (M2C_FIELD(temp_v1, u16 *, 0x6E) - 4);
        M2C_FIELD(arg0, u16 *, 0x72) = (u16) M2C_FIELD(temp_v1, u16 *, 0x6A);
        M2C_FIELD(arg0, u16 *, 0x74) = (u16) M2C_FIELD(temp_v1, u16 *, 0x6C);
        M2C_FIELD(arg0, s16 *, 0x76) = (s16) (M2C_FIELD(temp_v1, u16 *, 0x6E) + 4);
    }
}
void func_8011AB30(u8 *a)
{
    switch (a[4]) {
    case 0:
        a[0xB] = 0x14;
        a[4]++;
        break;
    case 1:
        switch (a[3]) {
        case 0:
            func_8011A974(a);
            break;
        case 1:
            func_8011AD3C_inl(a);
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

void func_8011AB30();
u8 *func_8011AC9C(void *parent)
{
    u8 *p = func_80072DDC(0, 0, 3, 0x18);

    if (p != NULL) {
    *(void **)(p + 0x1C) = func_8011AB30;
    p[3] = 0;
    *(void **)(p + 0x10) = parent;
    *(s32 *)(p + 0x3C) = D_800ECF80;
    func_80077B38(p, D_8014CEF0, 7);
    p[0xD] = 0;
    *(s16 *)(p + 0x5C) = 0;
    *(s16 *)(p + 0x5A) = 0;
    p[0x47] = 0;
    p[8] = 0;
        return p;
    }
    return NULL;
}

s32 func_8011AD34(void) {
    return 0;
}

void func_8011AD3C(void *arg0) {
    u8 temp_v0;
    void *temp_v1;

    temp_v1 = M2C_FIELD(arg0, void **, 0x10);
    temp_v0 = M2C_FIELD(temp_v1, u8 *, 1);
    M2C_FIELD(arg0, u8 *, 1) = temp_v0;
    if (temp_v0 & 0xFF) {
        M2C_FIELD(arg0, u16 *, 0x60) = (u16) M2C_FIELD(temp_v1, u16 *, 0x2E);
        M2C_FIELD(arg0, u16 *, 0x62) = (u16) M2C_FIELD(temp_v1, u16 *, 0x32);
        M2C_FIELD(arg0, s16 *, 0x64) = (s16) (M2C_FIELD(temp_v1, u16 *, 0x36) - 4);
        M2C_FIELD(arg0, u16 *, 0x66) = (u16) M2C_FIELD(temp_v1, u16 *, 0x2E);
        M2C_FIELD(arg0, u16 *, 0x68) = (u16) M2C_FIELD(temp_v1, u16 *, 0x32);
        M2C_FIELD(arg0, s16 *, 0x6A) = (s16) (M2C_FIELD(temp_v1, u16 *, 0x36) + 4);
        M2C_FIELD(arg0, u16 *, 0x6C) = (u16) M2C_FIELD(temp_v1, u16 *, 0x6A);
        M2C_FIELD(arg0, u16 *, 0x6E) = (u16) M2C_FIELD(temp_v1, u16 *, 0x6C);
        M2C_FIELD(arg0, s16 *, 0x70) = (s16) (M2C_FIELD(temp_v1, u16 *, 0x6E) - 4);
        M2C_FIELD(arg0, u16 *, 0x72) = (u16) M2C_FIELD(temp_v1, u16 *, 0x6A);
        M2C_FIELD(arg0, u16 *, 0x74) = (u16) M2C_FIELD(temp_v1, u16 *, 0x6C);
        M2C_FIELD(arg0, s16 *, 0x76) = (s16) (M2C_FIELD(temp_v1, u16 *, 0x6E) + 4);
    }
}

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8011AE04);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8011AF68);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8011B478);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8011B76C);

extern s32 D_800BF854;
void func_8011B90C(void *arg0) {
    if (D_800BF854 == 0xFF) {
        M2C_FIELD(arg0, s8 *, 5) = 0;
        M2C_FIELD(arg0, s8 *, 0x5E) = 2;
        if (M2C_FIELD(arg0, u8 *, 3) == 0) {
            func_80074590(0x94, -0xA, -0x1E);
        }
    }
}

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8011B958);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8011BC18);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8011BF84);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8011C614);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8011C848);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8011C974);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8011CA24);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8011CB44);

void func_8011CD34(u8 *a) {
    switch (a[4]) {
    case 0:
        func_8011BC18(a);
        break;
    case 1:
        if (func_8011CA24(a) != 0) {
            a[1] = 1;
            func_80077EBC(a);
        }
        switch (a[5]) {
        case 0:
            func_8011CE70(a);
            break;
        case 1:
            if (D_1F800137 == 0) {
                func_8011BF84(a);
            }
            break;
        case 2:
            func_8011C614(a);
            break;
        }
        func_8011CB44(a);
        if (a[1] != 0) {
            func_8011B958(a);
        }
        break;
    case 2:
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

s32 func_8011CE70(s32 arg0) {
    if (M2C_FIELD(arg0, u8 *, 6) == 0) {
        func_8011CEDC(arg0);
        M2C_FIELD(arg0, u8 *, 6) = (u8) (M2C_FIELD(arg0, u8 *, 6) + 1);
    }
    if (func_8011C848(arg0, 1) != 0) {
        M2C_FIELD(arg0, s8 *, 5) = 1;
        M2C_FIELD(arg0, u8 *, 6) = 0U;
    }
    return func_8011C974(arg0);
}

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8011CEDC);

void func_8011CF8C(u8 *a) {
    u8 k = a[0x2B];
    s32 t;

    if (k == 0) {
        return;
    }
    switch (a[0x47] & 3) {
    case 0:
        if (k != 2) {
            M2C_FIELD(a, s16 *, 0x48) -= 0x2000;
        } else {
            M2C_FIELD(a, s16 *, 0x48) += 0x2000;
        }
        break;
    case 2:
        if (k == 2) {
            M2C_FIELD(a, s16 *, 0x48) -= 0x2000;
        } else {
            M2C_FIELD(a, s16 *, 0x48) += 0x2000;
        }
        break;
    }
    t = a[0x2B];
    a[0x2B] = 0;
    a[6] = 1;
    M2C_FIELD(a, s16 *, 0x6C) = t;
}

s32 func_8011D014(AreaPartsOwner *a) {
    s16 v = M2C_FIELD(a, s16 *, 0x44);
    s16 ang = M2C_FIELD(a->parts[0], u16 *, 0xC);
    ang &= 0xFFF;

    if (v > 0) {
        v -= 10;
        if (v < 0) {
            v = 0;
        }
    } else {
        v += 10;
        if (v > 0) {
            v = 0;
        }
    }
    if (ang > 0x800) {
        ang += v;
        if (ang >= 0x1000) {
        settle:
            if (abs(v) < 0x8C) {
                return 1;
            }
        } else if (v < 0x96) {
            v += 0x1E;
        }
    } else {
        ang += v;
        if (ang <= 0) {
            goto settle;
        }
        if (v >= -0x95) {
            v -= 0x1E;
        }
    }
    M2C_FIELD(a, s16 *, 0x44) = v;
    M2C_FIELD(a->parts[0], s16 *, 0xC) = ang;
    return 0;
}

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8011D100);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8011D520);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8011D67C);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8011D748);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8011D810);

typedef struct { u8 pad[0x48]; s32 unk48; } AreaState808;
extern s8 D_1F80017C[];
typedef struct { s16 x, y, z; } AreaVec3s;
extern AreaVec3s D_80144EA0[];
typedef struct { s16 x, y, z, pad; } AreaSVec;
void func_8011D8F8(u8 *a) {
    s16 i;

    switch (a[6]) {
    case 0:
        if (--M2C_FIELD(a, s16 *, 0x40) <= 0) {
            a[6]++;
        }
        break;
    case 1:
        if (!(*(u16 *)D_1F80017C & 0xF)) {
            M2C_FIELD(a, s16 *, 0xB8) = D_80144EA0[M2C_FIELD(a, s16 *, 0x7A)].x;
            M2C_FIELD(a, s16 *, 0xBA) = D_80144EA0[M2C_FIELD(a, s16 *, 0x7A)].y;
            M2C_FIELD(a, s16 *, 0xBC) = D_80144EA0[M2C_FIELD(a, s16 *, 0x7A)].z;
            M2C_FIELD(a, s16 *, 0x7A) = (M2C_FIELD(a, s16 *, 0x7A) + 1) & 7;
        }
        break;
    }
    if ((s16)func_8011E3F8(a)) {
        func_8011E308(a, 0);
        a[5] = 3;
        a[6] = 0;
        M2C_FIELD(a, s16 *, 0x6C) = 0;
    }
}

#define C0(p) M2C_FIELD(p, u8 **, 0xC0)
#define C0(p) M2C_FIELD(p, u8 **, 0xC0)
void func_8011DA10(u8 *a)
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
            g = D_800BF808_1760;
            if (M2C_FIELD(g, s32 *, 0x64) == 0) {
                func_8004CBD8(a, 0);
                M2C_FIELD(g, s32 *, 0x64) = s;
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

void func_8011DC6C(u8 *a)
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
            func_8011E308(a, a[0x5E]);
            a[6] = 1;
            M2C_FIELD(a, s16 *, 0x6C) = 1;
        }
    } else if ((s16)func_8011E3F8(a)) {
        M2C_FIELD(*(u8 **)(a + 0xC0), u16 *, 0x38) = M2C_FIELD(a, s16 *, 0x64);
        M2C_FIELD(*(u8 **)(a + 0xC0), u16 *, 0x3A) = M2C_FIELD(a, s16 *, 0x66);
        func_8011E308(a, 0);
        a[6] = 0;
        M2C_FIELD(a, s16 *, 0x6C) = 0;
    }
    if (M2C_FIELD(a, s16 *, 0x50) > 0x20) {
        M2C_FIELD(a, s16 *, 0x50)--;
    }
    func_8011E45C(a);
}

extern u8 D_800BF873;
void func_8011DF04(void *arg0) {
    u8 temp_v1;
    u8 temp_v1_2;

    temp_v1 = M2C_FIELD(arg0, u8 *, 4);
    switch (temp_v1) {                              /* switch 1; irregular */
    case 0:                                         /* switch 1 */
        func_8011E040(arg0);
        return;
    case 1:                                         /* switch 1 */
        func_8007778C(arg0);
        if (D_800BF873 == 0) {
            temp_v1_2 = M2C_FIELD(arg0, u8 *, 5);
            switch (temp_v1_2) {                    /* switch 2; irregular */
            case 0:                                 /* switch 2 */
                func_8011D8F8(arg0);
                break;
            case 3:                                 /* switch 2 */
                func_8011DC6C(arg0);
                break;
            case 4:                                 /* switch 2 */
                func_8011E124(arg0);
                break;
            }
            func_8011E248(arg0);
            func_8011DA10(arg0);
            M2C_FIELD(arg0, s8 *, 0x29) = 0;
        }
        if (M2C_FIELD(arg0, u8 *, 1) != 0) {
            func_800518FC(arg0);
            return;
        }
        return;
    case 2:                                         /* switch 1 */
        func_8011E174(arg0);
        return;
    case 3:                                         /* switch 1 */
        func_8007A624(arg0);
        break;
    }
}

void func_8011E45C(void *arg0);
extern u16 D_1F8001A0_6940;
extern u16 D_1F8001A2_7766;
void func_8011E040(u8 *a)
{
    if (func_80051B70(a, 0xC, 0xB) == 0) {
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
        func_8011E45C(a);
        if (func_80048750(a) != 0) {
            u16 x = D_1F8001A0_6940;
            u16 y = D_1F8001A2_7766;
            H(a, 0x56) = x;
            H(a, 0x58) = y & 0xFFF;
        }
        func_800518FC(a);
    }
}

void func_8011E124(u8 *a)
{
    if (a[0x29] == 0) {
        func_8011E308(a, 1);
        a[5] = 3;
        a[6] = 1;
        *(s16 *)(a + 0x6C) = 1;
    }
}

void func_8011E174(u8 *a) {
    func_80027144(M2C_FIELD(M2C_FIELD(a, u8 **, 0xC0), s32 *, 0x40), a + 0x2C, 0xA00, -0x7FDC);
    func_80074590(0xC, 0, 0);
    M2C_FIELD(a, s16 *, 0x32) -= 0x96;
    func_80027144(M2C_FIELD(M2C_FIELD(a, u8 **, 0xC0), s32 *, 0x40), a + 0x2C, 0xA00, 0x2C);
    func_80074590(0xC, 0, 0);
    if (func_80040B48(0x7F) >= 0) {
        D_800BF870.pad1[0x15C] |= 1;
        if (++D_800BF870.pad1[0x1C0] >= 10) {
            func_8004ED94(0x6E, 0x41);
        }
    }
    a[4] = 3;
}

void func_8011E248(u8 *a)
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

void func_8011E308(u8 *a, s16 b)
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

s32 func_8011E3F8(u8 *a)
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

void func_8011E45C(void *arg0) {
    s32 temp_v0_2;
    u32 temp_v0;

    temp_v0 = (u16) M2C_FIELD(M2C_FIELD(arg0, void **, 0xC0), u16 *, 0x38) >> 5;
    M2C_FIELD(arg0, s16 *, 0x80) = (s16) temp_v0;
    M2C_FIELD(arg0, s16 *, 0x82) = (s16) (temp_v0 * 2);
    temp_v0_2 = (s32) (M2C_FIELD(M2C_FIELD(arg0, void **, 0xC0), u16 *, 0x3A) * 0x113) >> 0xC;
    M2C_FIELD(arg0, s16 *, 0x84) = (s16) temp_v0_2;
    M2C_FIELD(arg0, s16 *, 0x86) = (s16) (temp_v0_2 * 2);
}

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8011E4B0);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8011E748);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8011E994);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8011EBD0);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8011EF18);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8011F1E4);

extern u8 D_800BF816;
void func_8011F4B0(u8 *a)
{
    u8 *p = D_800E7E80;
    u8 *g;

    if (p[0x78] == 7) {
    switch (a[6]) {
    case 0:
        if (a[0x29] != 0 && p[0x29] != 0 && p[0x17B] == 0) {
            u8 *h = D_800BF808_1760;
            u8 *sp = &D_1F800137;
            a[0] = 2;
            a[6]++;
            h[0x10] = 1;
            h[0xF] = a[3];
            if (*sp == 0) {
                *sp = 2;
            }
        }
        break;
    case 1:
        if (func_80072E60(a) != 0 && D_800BF816 != 0) {
            a[6]++;
            func_80072EFC(a);
        }
        break;
    case 2:
        g = D_800BF808_1760;
        if (g[0x10] == 2 && g[7] == 0) {
            a[0] = 1;
            a[6]++;
            a[0x5F] = 1 - a[0x5F];
            *(s16 *)(a + 0x84) += 0x320;
            *(s16 *)(a + 0x86) += 0x320;
        }
        break;
    case 3:
        if (a[0x29] != 0 && p[0x29] != 0 && p[0x17B] == 0 && D_800BF80F == 0) {
            a[6]++;
            func_80073300(a);
            if (D_1F800137 == 0) {
                D_1F800137 = 2;
            }
        }
        break;
    case 4:
        g = D_800BF808_1760;
        if (g[0x10] == 4 && g[7] == 0) {
            a[6]++;
            g[0x10] = 0;
        }
        break;
    case 5:
        if (func_80072F14(a) != 0) {
            a[0] = 1;
            a[6] = 0;
            a[0x5F] = 1 - a[0x5F];
            *(s16 *)(a + 0x84) -= 0x320;
            *(s16 *)(a + 0x86) -= 0x320;
        }
        break;
    }
    } else {
        func_80073328(a);
    }
}

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8011F71C);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8011F9E4);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8011FBE8);

INCLUDE_ASM("asm/a06/nonmatchings/a06", f_UpdateDonglinInteriorEntranceActor);

void func_801205E8(void) {
    func_8011EF18();
}

extern s8 D_800BF81F;
void func_80120608(u8 *a) {
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
        a[0x29] = k;
        D_800BF81F = (k - a[0x5F]) * 16;
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
    func_800735F4(a, 0x5D);
}

void func_8012070C(void) {
    func_8011E748();
}

void func_8012072C(void) {
    func_8011E994();
}

void func_8012074C(void) {
    func_80073328();
}

void func_8012076C(void) {
    func_80073328();
}

void func_8012078C(s32 arg0) {
    func_8011E748();
    func_800735F4(arg0, 0x5F);
}

extern u8 D_800BF871;
extern u8 D_800E7FF4;
void func_801207BC(u8 *a)
{
    u8 *t;

    if (D_800E7FF4 & 4) {
        func_80073328(a);
    }
    if (D_800BF871 == 0x13) {
        t = *(u8 **)(a + 0x14);
        if (t != NULL && t[4] < 2) {
            t[4] = 2;
            *(u8 **)(a + 0x14) = NULL;
            a[7] = 0;
        }
    } else {
        func_800735F4(a, 0x67);
    }
}

extern u8 D_800BF918;
void func_80120844(u8 *a) {
    switch (a[0x5E]) {
    case 0:
        switch (a[5]) {
        case 0:
            if (D_800BF918 == 1) {
                a[5] = 1;
                func_800313A0(0x719, a + 0x2C, -0x20, a + 0x54);
                func_80074590(0xD, -0x1D, 0);
            }
            break;
        case 1:
            if (D_800BF918 >= 2) {
                a[0x5E] = 1;
                a[5] = 0;
            }
            if (!(D_1F80017C_0fe7 & 0xF)) {
                func_80074590(0xD, -0x1D, 0);
            }
            break;
        }
        a[1] = 0;
        break;
    case 1:
        func_8011F71C(a);
        func_800735F4(a, 0x6C);
        break;
    case 2:
        func_8011F9E4(a);
        func_800735F4(a, 0x6C);
        break;
    }
}

#define P (*(s16 **)(a + 0xC0))
void func_80120954(u8 *a)
{
    u8 *g;

    switch (a[4]) {
    case 0:
        if (func_80051B70(a, 0xC, 0x31) != 0) {
            break;
        }
        *(s16 *)(a + 0x80) = 0x1E;
        *(s16 *)(a + 0x82) = 0x3C;
        *(s16 *)(a + 0x84) = 0x32;
        *(s16 *)(a + 0x86) = 0x64;
        a[0] = 1;
        a[0x29] = 0;
        *(s16 *)(a + 0x60) = 0x3E0;
        a[4]++;
        break;
    case 1:
        if (func_8007778C(a) == 0) {
            break;
        }
        if (a[0x29] != 0) {
            g = D_800E7E80;
            if (!(g[0x147] & 1)) {
                P[0] = -(func_80083E80(*(s16 *)(g + 0x58)) * 8) >> 12;
                P[1] = (u32)func_80083F50(*(s16 *)(g + 0x58)) >> 9;
            } else {
                P[0] = -(func_80083E80(-*(s16 *)(g + 0x58)) * 8) >> 12;
                P[1] = (u32)func_80083F50(-*(s16 *)(g + 0x58)) >> 9;
            }
            P[4] = func_80085690(P[1], *(s16 *)(a + 0x60));
            P[5] = -func_80085690(P[0], *(s16 *)(a + 0x60));
        }
        func_800517F8(a);
        break;
    case 2:
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80120B0C);

typedef struct { s16 m[3][3]; s16 pad; s32 t[3]; } AreaMatrix;
extern AreaSVec D_1F8000C0;
typedef struct { u8 pad[0x28]; AreaMatrix m; } AreaScratchD0;
extern AreaScratchD0 D_1F8000D0;
extern AreaMatrix D_1F800000_6ac3;
void func_80120D2C(u8 *a) {
    D_1F8000C0.x = M2C_FIELD(M2C_FIELD(a, u8 **, 0xC0), s16 *, 0x2C);
    D_1F8000C0.y = M2C_FIELD(M2C_FIELD(a, u8 **, 0xC0), s16 *, 0x30);
    D_1F8000C0.z = M2C_FIELD(M2C_FIELD(a, u8 **, 0xC0), s16 *, 0x34);
    func_80084110(&D_1F8000D0.m, M2C_FIELD(a, u8 **, 0xC0) + 0x18, &D_1F800000_6ac3);
    func_80084220(&D_1F8000C0, D_1F800000_6ac3.t);
    D_1F800000_6ac3.t[0] += D_1F8000D0.m.t[0];
    D_1F800000_6ac3.t[1] += D_1F8000D0.m.t[1];
    D_1F800000_6ac3.t[2] += D_1F8000D0.m.t[2];
    func_80084660(&D_1F800000_6ac3);
    func_80084690(&D_1F800000_6ac3);
    func_80120B0C(a);
}

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80120E0C);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80120FB4);

extern u16 D_800BF89E;
extern u8 D_800BFB20;
extern u8 D_800E8008[];
extern s16 D_801003F8;
extern u8 D_80144FF0[];
extern u8 D_80144FF8[];
void func_801210CC(u8 *a)
{
    u8 *t = D_800E7E80;
    u8 *c = D_800E8008;

    switch (a[6]) {
    case 0:
        if (a[0x29] != 0 && t[0x29] != 0 && t[0x17B] == 0) {
            if (D_800BF89E & 0x200) {
                a[6]++;
                func_80042354(1, 2);
                func_80054198(t);
                t[4] = 4;
                t[5] = 0x21;
                t[6] = 0;
                func_80054D14(t, 2, 4);
            }
            func_80040B48(0x7C);
        }
        break;
    case 1:
        a[6]++;
        c[0x64] = 1;
        *(s16 *)(c + 0x6E) = 0x80;
        *(s16 *)(c + 0x70) = -0x200;
        *(s16 *)(c + 0x6C) = D_801003F8 * 5;
        func_8006CBA8(a + 0x2C);
        break;
    case 2:
        if (c[0x66] == 3 && func_80041438(t, (s16)(*(s16 *)(t + 0x140) + 0x800), 0x100) != 0) {
            *(s16 *)(a + 0x40) = 0x18;
            *(s16 *)(a + 0x44) = 0;
            a[6]++;
        }
        break;
    case 3:
        if (--*(s16 *)(a + 0x40) == 0) {
            a[6]++;
        } else {
            *(s32 *)(t + 0x2C) -= *(s16 *)(t + 0x48) * *(s16 *)(a + 0x44);
            *(s32 *)(t + 0x34) -= *(s16 *)(t + 0x4C) * *(s16 *)(a + 0x44);
            if (*(s16 *)(a + 0x44) < 0x2000) {
                *(s16 *)(a + 0x44) += 0x200;
            }
        }
        break;
    case 4:
        a[6]++;
        func_80040CDC(a, 0, D_80144FF0);
        a[0x70] = 1;
        break;
    case 5:
        func_80041098(a);
        if (a[0x70] == 0xFF) {
            if (D_800BFB20 == 0) {
                a[6] += 2;
            } else {
                a[6]++;
                func_80040CDC(a, 0, D_80144FF8);
                a[0x70] = 1;
            }
        }
        break;
    case 6:
        func_80041098(a);
        if (a[0x70] == 0xFF) {
            a[6]++;
        }
        break;
    case 7:
        if (func_80041438(t, *(s16 *)(t + 0x140), 0x100) != 0) {
            *(s16 *)(a + 0x40) = 0x1E;
            *(s16 *)(a + 0x44) = 0x1A00;
            *(s16 *)(a + 0x4A) = -0x1800;
            *(s16 *)(a + 0x50) = 0x1C0;
            a[6]++;
            func_80054D14(t, 0x69, 0);
        }
        break;
    case 8:
        if (*(s16 *)(a + 0x4A) > 0) {
            t[5] = 0x22;
            a[6]++;
        }
    case 9:
        if (--*(s16 *)(a + 0x40) == 0) {
            a[6]++;
            c[0x64] = 6;
            func_80054D14(t, 2, 0);
            func_80040C00(0x7C);
        } else {
            *(s32 *)(t + 0x2C) += *(s16 *)(t + 0x48) * *(s16 *)(a + 0x44);
            *(s32 *)(t + 0x34) += *(s16 *)(t + 0x4C) * *(s16 *)(a + 0x44);
            *(s32 *)(t + 0x30) += *(s16 *)(a + 0x4A) << 8;
            *(s16 *)(a + 0x4A) += *(s16 *)(a + 0x50);
        }
        break;
    case 10:
        if (c[0x66] == 3) {
            a[6] = 0;
            func_80042310();
        }
        break;
    }
}

s32 func_801214C0(u8 *a)
{
    u8 *t = D_800E7E80;
    u8 *c = D_800E8008;

    switch (a[6]) {
    case 0:
        a[6]++;
        t[4] = 4;
        t[5] = 0x21;
        t[6] = 0;
        func_80054D14(t, 2, 0);
        *(s16 *)(t + 0x2E) = 0x647D;
        *(s16 *)(t + 0x32) = -0x70C;
        *(s16 *)(t + 0x36) = 0x478C;
        func_8006E1C0(1);
        *(s16 *)(c + 0x6E) = 0x80;
        *(s16 *)(c + 0x70) = -0x200;
        *(s16 *)(c + 0x6C) = D_801003F8 * 5;
        func_8006CBA8(a + 0x2C);
        break;
    case 1:
        if (D_800BF80F == 0) {
            a[6]++;
            func_80042354(1, 2);
            func_80040CDC(a, 0, D_80144FF0);
            a[0x70] = 1;
        }
        break;
    case 2:
        func_80041098(a);
        if (a[0x70] == 0xFF) {
            if (D_800BFB20 == 0) {
                a[6] += 2;
            } else {
                a[6]++;
                func_80040CDC(a, 0, D_80144FF8);
                a[0x70] = 1;
            }
        }
        break;
    case 3:
        func_80041098(a);
        if (a[0x70] == 0xFF) {
            a[6]++;
        }
        break;
    case 4:
        if (func_80041438(t, *(s16 *)(t + 0x140), 0x100) != 0) {
            *(s16 *)(a + 0x40) = 0x1E;
            *(s16 *)(a + 0x44) = 0x1A00;
            *(s16 *)(a + 0x4A) = -0x1800;
            *(s16 *)(a + 0x50) = 0x1C0;
            a[6]++;
            func_80054D14(t, 0x69, 0);
        }
        break;
    case 5:
        if (*(s16 *)(a + 0x4A) > 0) {
            t[5] = 0x22;
            a[6]++;
        }
    case 6:
        if (--*(s16 *)(a + 0x40) == 0) {
            a[6]++;
            func_8006E1E4();
            func_80054D14(t, 2, 0);
            func_80040C00(0x7C);
        } else {
            *(s32 *)(t + 0x2C) += *(s16 *)(t + 0x48) * *(s16 *)(a + 0x44);
            *(s32 *)(t + 0x34) += *(s16 *)(t + 0x4C) * *(s16 *)(a + 0x44);
            *(s32 *)(t + 0x30) += *(s16 *)(a + 0x4A) << 8;
            *(s16 *)(a + 0x4A) += *(s16 *)(a + 0x50);
        }
        break;
    case 7:
        if (c[0x66] == 3) {
            a[6] = 0;
            func_80042310();
            return 1;
        }
        break;
    }
    return 0;
}

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_801217E4);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80121C1C);

INCLUDE_ASM("asm/a06/nonmatchings/a06", f_UpdateGhostStickerQuestActor);

extern s8 D_800BFA2B;
void func_80122204(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 5);
    switch (temp_v1) {                              /* irregular */
    case 0:
        if ((D_800BF870.pad1[0] == 2) && (D_800BF870.pad1[0x1BA] != 0)) {
            M2C_FIELD(arg0, u8 *, 5) = (u8) D_800BF870.pad1[0];
            return;
        }
        M2C_FIELD(arg0, u8 *, 5) = 1U;
        return;
    case 1:
        func_801210CC(arg0);
        return;
    case 2:
        if (func_801214C0(arg0) != 0) {
            M2C_FIELD(arg0, u8 *, 5) = 1U;
            D_800BFA2B = 0;
        }
        return;
    }
}

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_801222C4);

extern u8 D_800BF9CB;
void func_801223DC(u8 *a)
{
    switch (a[4]) {
    case 0:
        if (func_80051B70(a, 0xC, 0x2C) != 0) {
            break;
        }
        *(s16 *)(a + 0x80) = 0x50;
        *(s16 *)(a + 0x82) = 0xA0;
        *(s16 *)(a + 0x84) = 0xFA;
        *(s16 *)(a + 0x86) = 0xFA;
        a[0] = 1;
        a[0x2B] = 0;
        a[4]++;
        if ((D_800BF9CB >> a[3]) & 1) {
            *(s16 *)(a + 0xBA) = 0x100;
            a[0] = 2;
            *(s16 *)(a + 0x32) += 0x10;
            a[0xD] |= 4;
            (*(u8 **)(a + 0xC0))[0x3F] = 0x10;
        }
        break;
    case 1:
        if (func_8007778C(a)) {
            func_80051844(a);
        }
        a[0x2B] = 0;
        break;
    case 2:
        func_8007778C(a);
        func_801222C4(a);
        func_80051844(a);
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80122524);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80122724);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80122878);

extern u8 D_800ECF58_742e[];
extern u8 D_8014005C[];
extern u8 D_800BF932;
extern u8 D_800BFA10;
extern u8 D_800BFA1D;
void func_801229A0(u8 *a)
{
    s16 t;

    switch (a[4]) {
    case 0:
        switch (a[3]) {
        case 0:
        case 1:
            if (func_80051B70(a, 0xC, 0x29) != 0) {
                break;
            }
            *(s16 *)(a + 0x80) = 0x64;
            *(s16 *)(a + 0x82) = 0xC8;
            *(s16 *)(a + 0x84) = 0x9A;
            *(s16 *)(a + 0x86) = 0x9A;
            a[0] = 1;
            a[0x29] = 0;
            *(s16 *)(a + 0x54) = 0;
            *(s16 *)(a + 0x56) = 0;
            *(s16 *)(a + 0x58) = 0;
            a[4]++;
            if (a[3] == 1 && D_800BF932 < 2) {
                func_80040B48(0x7E);
                t = *(s16 *)(a + 0x36);
                *(s16 *)(a + 0x36) = 0x21A0;
                a[0x5E] = 1;
                a[0x5F] = 0;
                a[5] = 4;
                *(s16 *)(a + 0x32) -= 0x20;
                *(s16 *)(a + 0x74) = t;
                break;
            }
            a[0x5E] = 0;
            if (a[3] == D_800BFA10) {
                a[5] = 2;
                *(s16 *)(a + 0x32) += 0x64;
            }
            break;
        case 2:
            if (func_80051B70(a, 0xC, 0x2B) != 0) {
                break;
            }
            *(s16 *)(a + 0x80) = 0xE0;
            *(s16 *)(a + 0x82) = 0x1C0;
            *(s16 *)(a + 0x84) = 0x10;
            *(s16 *)(a + 0x86) = 0x40;
            *(s16 *)(a + 0x56) = 0x800;
            a[0] = 1;
            *(s16 *)(a + 0x54) = 0;
            *(s16 *)(a + 0x58) = 0;
            a[4]++;
            if (D_800BFA1D & 4) {
                a[5] = 1;
                *(s16 *)(a + 0x32) += 0x40;
            }
            break;
        case 3:
            if (func_80051B70(a, 0xC, 0x46) != 0) {
                break;
            }
            *(s16 *)(a + 0x80) = 0x64;
            *(s16 *)(a + 0x82) = 0xC8;
            a[0] = 1;
            *(s16 *)(a + 0x84) = 0x4D;
            *(s16 *)(a + 0x86) = 0x4D;
            *(s16 *)(a + 0x54) = 0;
            *(s16 *)(a + 0x56) = 0;
            *(s16 *)(a + 0x58) = 0;
            *(s16 *)(a + 0x42) = 0;
            a[4]++;
            break;
        }
        break;
    case 1:
        switch (a[3]) {
        case 0:
        case 1:
            func_80122524(a);
            break;
        case 2:
            if (a[5] == 0) {
                func_80122724(a);
            }
            break;
        case 3:
            *(s16 *)(a + 0x42) += 1;
            break;
        }
        if (func_8007778C(a) != 0) {
            func_800517F8(a);
        }
        a[0x29] = 0;
        break;
    case 2:
        if (a[3] == 3) {
            func_80122878(a);
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

void func_80122CAC(u8 *a)
{
    switch (a[4]) {
    case 0:
        *(s16 *)(a + 0x80) = 0x8C;
        *(s16 *)(a + 0x82) = 0x118;
        *(s16 *)(a + 0x84) = 0x190;
        *(s16 *)(a + 0x86) = 0x320;
        a[8] = 0;
        a[9] = 0;
        a[0] = 1;
        a[0xB] = 0;
        a[0x5E] = 0;
        a[0x29] = 0;
        a[0x2A] = 0x12;
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

void func_80122D64(u8 *a) {
    if (func_80051B70(a, 0xC, 0x2B) == 0) {
        a[0] = 1;
        M2C_FIELD(a, s16 *, 0x80) = 0xE0;
        M2C_FIELD(a, s16 *, 0x82) = 0x1C0;
        M2C_FIELD(a, s16 *, 0x84) = 0x10;
        M2C_FIELD(a, s16 *, 0x86) = 0x40;
        M2C_FIELD(a, s16 *, 0x54) = 0;
        M2C_FIELD(a, s16 *, 0x56) = 0x800;
        M2C_FIELD(a, s16 *, 0x58) = 0;
        a[4]++;
        if (D_800BFA1D & 4) {
            a[5] = 1;
            M2C_FIELD(a, s16 *, 0x32) += 0x40;
        }
    }
}

void func_80122E00(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 5) == 0) {
        func_80122724();
    }
}

void func_80122E30(u8 *p)
{
    if (func_80051B70(p, 0xC, 0x46) == 0) {
        p[0] = 1;
        *(s16 *)(p + 0x80) = 100;
        *(s16 *)(p + 0x82) = 200;
        *(s16 *)(p + 0x84) = 0x4D;
        *(s16 *)(p + 0x86) = 0x4D;
        *(s16 *)(p + 0x54) = 0;
        *(s16 *)(p + 0x56) = 0;
        *(s16 *)(p + 0x58) = 0;
        *(s16 *)(p + 0x42) = 0;
        p[4]++;
    }
}

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80122EA0);

extern u8 D_800BF931;
extern u8 D_800A43E8[];
extern u8 D_8001B354[];
extern u8 D_80145000[];
extern u8 D_801450D0[];
extern u8 D_80145100[];
void func_80123018(u8 *a)
{
    u8 *g;
    u8 *st;
    u8 *e;

    switch (a[4]) {
    case 0:
        if (D_800BF931 == 0xFF) {
            a[4] = 3;
            break;
        }
        g = D_800ECF58_742e;
        if (func_800519E0(a, 0x12, *(s32 *)(g + 0x14), D_800A43E8) != 0) {
            break;
        }
        *(s32 *)(a + 0x3C) = *(s32 *)(g + 0x18);
        func_80077C40(a, D_8001B354, 9);
        *(s16 *)(a + 0x80) = 0xF0;
        *(s16 *)(a + 0x82) = 0x1E0;
        *(s16 *)(a + 0x84) = 0x88;
        *(s16 *)(a + 0x86) = 0x100;
        *(s16 *)(a + 0x56) = 0x100;
        a[0x18] = 0x38;
        a[0x19] = 0x3C;
        a[0] = 1;
        a[0x29] = 0;
        a[0x2B] = 0;
        *(s16 *)(a + 0x54) = 0;
        *(s16 *)(a + 0x58) = 0;
        a[0xB] = 1;
        a[0x1A] = 0x40;
        a[4]++;
        break;
    case 1:
        func_8007778C(a);
        switch (a[5]) {
        case 0:
            st = D_800BF808_1760;
            if (*(s32 *)(st + 0x4C) & 0x80) {
                a[5] = 1;
                break;
            }
            e = D_800E7E80;
            switch (a[6]) {
            case 0:
                if (a[0x2B] == 3) {
                    a[6] = 1;
                    e[4] = 4;
                    e[5] = 0x21;
                    e[6] = 0;
                    e[0x61] = 0;
                    if (D_800BF931 == 0) {
                        func_80042354(1, 4);
                        func_80040CDC(a, D_8001B354, D_80145000);
                    } else {
                        func_80042354(1, 2);
                        func_80040CDC(a, D_8001B354, D_801450D0);
                    }
                    a[0x70] = 1;
                }
                break;
            case 1:
                func_80041098(a);
                if (a[0x70] == 0xFF) {
                    func_80042310();
                    st[1] = 0;
                    a[6] = 0;
                }
                break;
            }
            break;
        case 2:
            func_8004190C(a);
        case 1:
            switch (a[6]) {
            case 0:
                a[6]++;
                func_80040CDC(a, D_8001B354, D_80145100);
                a[0x70] = 1;
                break;
            case 1:
                func_80041098(a);
                if (a[0x70] == 0xFF) {
                    func_80042310();
                    a[4] = 3;
                }
                break;
            }
            break;
        }
        if (a[1] != 0) {
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

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80123318);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80123860);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80123948);

extern s32 D_800BF854;
s32 func_80123A08(void) {
    D_800BF854 = 0;
    return 1;
}

extern s32 D_800BF854;
s32 func_80123A18(void) {
    return D_800BF854 == 1;
}

s32 func_80123A30(void *arg0) {
    M2C_FIELD(arg0, u8 *, 5) = (u8) (M2C_FIELD(arg0, u8 *, 5) + 1);
    func_80042354(1, 3);
    return 1;
}

s32 func_80123A60(u8 *p)
{
    S13AE38 v;

    v.a = *(s16 *)(p + 0x2E);
    v.b = *(s16 *)(p + 0x32) - 0xF0;
    v.c = *(s16 *)(p + 0x36);
    func_8003116C(0x70F, &v, -0x32);
    func_80074590(0x38, 0, 0);
    *(s16 *)(p + 0x40) = 0;
    return 1;
}

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80123AC4);

s32 func_80123BB8(u8 *p)
{
    u16 x;
    u16 z;

    *(s16 *)(p + 0x58) = -0x200;
    x = D_1F800160;
    z = D_1F800164;
    *(s16 *)(p + 0x2E) = x + 0x90;
    *(s16 *)(p + 0x36) = z + 0x90;
    return 1;
}

extern u8 D_800BFA1F;
s32 func_80123BE8(u8 *p)
{
    u16 x = D_1F800160;
    u16 z = D_1F800164;

    *(s16 *)(p + 0x58) = 0;
    *(s16 *)(p + 0x2E) = x + 0xC4;
    *(s16 *)(p + 0x36) = z + 0xC4;
    return 1;
}

void func_80123C14(void *a0)
{
    s32 t = D_800BF544;

    func_8003CDD8(a0, 1);
    func_80123318(a0, t, D_800BF544);
}

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80123C64);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80123E30);

void func_80124058(u8 *a)
{
    switch (a[4]) {
    case 0:
        switch (a[5]) {
        case 0:
            if (func_80051B70(a, 0xC, 0x37) != 0) {
                break;
            }
            *(s16 *)(a + 0x80) = 0x12C;
            *(s16 *)(a + 0x82) = 0x258;
            *(s16 *)(a + 0x54) = 0;
            *(s16 *)(a + 0x58) = 0;
            a[0] = 1;
            *(s16 *)(a + 0x84) = 0;
            *(s16 *)(a + 0x86) = 0x40;
            a[5]++;
            func_8004766C(a);
            func_80048750(a);
            *(s16 *)(a + 0x56) = D_1F8001A0_6940;
            break;
        case 1:
            if (func_80123C64(a)) {
                a[4] = 1;
                a[5] = 0;
                a[6] = 0;
            }
            goto common;
        }
        break;
    case 1:
        func_80123E30(a);
    common:
        func_8007778C(a);
        func_800517F8(a);
        break;
    case 2:
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80124198);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8012462C);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_801248B4);

void func_80124D70();
/* func_80124CEC, inlined */
static inline void func_80124CEC_inl(void *arg0) {
    u8 temp_v0;

    if (M2C_FIELD(arg0, u8 *, 0x5E) == 0) {
        if (M2C_FIELD(arg0, u8 *, 5) == 0) {
            func_80124D70(arg0);
            goto block_6;
        }
    } else if (M2C_FIELD(arg0, u8 *, 5) == 0) {
        temp_v0 = M2C_FIELD(arg0, u8 *, 0x29);
        if (temp_v0 != 0) {
            M2C_FIELD(arg0, u8 *, 0x2B) = temp_v0;
        }
block_6:
        func_801248B4(arg0);
    }
    M2C_FIELD(arg0, u8 *, 0x29) = 0U;
    M2C_FIELD(arg0, u8 *, 0x2B) = 0U;
}
void func_80124AA0(u8 *a0)
{
    u8 *a = a0;
    if (D_800BFA10 != a[0xBF]) {
        u8 f;
        *(u16 *)(((PartsOwner *)a)->parts[a[9] - 1] + 0xC) += 0x800;
        *(u16 *)(((PartsOwner *)a)->parts[a[9] - 1] + 0xC) &= 0xFFF;
        f = a[0x5E] ^ 1;
        a[0xBF] ^= 1;
        a[0x5E] = f;
        if (f == 0) {
            *(s16 *)(a + 0x84) = 0x82;
        } else {
            *(s16 *)(a + 0x84) = 0x64;
        }
        a[5] = 0;
        a[6] = 0;
        a[7] = 0;
    }
    func_80124CEC_inl(a);
}

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80124BCC);

void func_80124CEC(void *arg0) {
    u8 temp_v0;

    if (M2C_FIELD(arg0, u8 *, 0x5E) == 0) {
        if (M2C_FIELD(arg0, u8 *, 5) == 0) {
            func_80124D70();
            goto block_6;
        }
    } else if (M2C_FIELD(arg0, u8 *, 5) == 0) {
        temp_v0 = M2C_FIELD(arg0, u8 *, 0x29);
        if (temp_v0 != 0) {
            M2C_FIELD(arg0, u8 *, 0x2B) = temp_v0;
        }
block_6:
        func_801248B4(arg0);
    }
    M2C_FIELD(arg0, u8 *, 0x29) = 0U;
    M2C_FIELD(arg0, u8 *, 0x2B) = 0U;
}

extern u8 D_80142028[];
extern u8 D_8014D798[];
void func_80124D70(u8 *p)
{
    switch (p[6]) {
    case 0:
        if (p[0x29]) {
            p[6] = 1;
            p[7] = 1;
        }
        break;
    case 1:
        if (p[0x29] == 0) {
            p[6] = 0;
            p[7] = 3;
        }
        break;
    }
    func_8012462C(p);
}

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80124DE0);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80124ED4);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80125010);

void func_801251E8(u8 *a)
{
    switch (a[4]) {
    case 0:
        func_80124ED4(a);
        break;
    case 1:
        func_8007778C(a);
        func_80125010(a);
        a[0x29] = 0;
        break;
    case 2:
        a[4]++;
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

void func_80125284(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 4);
    switch (temp_v1) {                              /* irregular */
    case 0:
        if (func_80051B70(arg0, 0xC, 0x1F) == 0) {
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

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80125338);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_801259F8);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80125BD0);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80125D14);

extern u8 D_800BFA14;
u8 *func_80132CF8(s32 a, s32 b);
void func_80125E4C(u8 *a)
{
    S13AE38 v;
    u8 *r;

    switch (a[4]) {
    case 0:
        if (func_80051B70(a, 0xC, 0x60) != 0) {
            break;
        }
        *(s16 *)(a + 0x80) = 0x12C;
        *(s16 *)(a + 0x82) = 0x258;
        *(s16 *)(a + 0x84) = 0x3E8;
        *(s16 *)(a + 0x86) = 0x3E8;
        *(s16 *)(a + 0x56) = -0x600;
        a[0] = 1;
        *(s16 *)(a + 0x54) = 0;
        *(s16 *)(a + 0x58) = 0;
        a[4]++;
        v.a = *(s16 *)(a + 0x2E);
        v.b = *(s16 *)(a + 0x32) - 0x118;
        v.c = *(s16 *)(a + 0x36);
        r = func_8003116C(0x702, &v, -0x30);
        if (r != NULL) {
            *(u8 **)(r + 0x10) = a;
        }
        func_800517F8(a);
        if ((D_800BFA14 & 7) == 7) {
            func_80132CF8(a, 1);
            a[5] = 1;
        }
        break;
    case 1:
        func_8007778C(a);
        switch (a[5]) {
        case 0:
            func_80125338(a);
            break;
        case 1:
            func_80125D14(a);
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

s32 func_80125FC8(u8 *a0)
{
    u8 *r = func_80072DDC(a0, 0, 3, 0x10);

    if (r) {
        *(void **)(r + 0x1C) = f_UpdateDonglinInteriorQuestObjectActor;
        r[3] = 0x10;
        *(s16 *)(r + 0x2E) = *(s16 *)(a0 + 0x2E);
        *(s16 *)(r + 0x32) = *(s16 *)(a0 + 0x32) - 0x12C;
        *(s16 *)(r + 0x36) = *(s16 *)(a0 + 0x36);
    }
    return 1;
}

extern u8 D_800BFB5B;
s32 func_80126040(void) {
    return D_800BFB5B != 0;
}

extern s16 D_80147938[];
extern u8 D_800BF8D4;
extern u8 D_800BF9CE;
extern u8 D_1F800207;
extern s16 D_800E7FEE;
void func_801265E4(u8 *p);
void f_UpdateDeepForestSeesawActor(u8 *a)
{
    switch (a[4]) {
    case 0:
        if (a[3] & 0x80) {
            if (func_80051B70(a, 0xC, 0x53) != 0) {
                break;
            }
            *(s16 *)(a + 0x80) = 0xA0;
            *(s16 *)(a + 0x82) = 0x140;
            *(s16 *)(a + 0x84) = 0xA0;
            *(s16 *)(a + 0x86) = 0x140;
            func_800517F8(a);
        } else {
            if (func_80051B70(a, 0xC, D_80147938[a[3]]) != 0) {
                break;
            }
            if (!(a[3] & 2)) {
                *(s16 *)(a + 0x80) = 0x60;
            } else {
                *(s16 *)(a + 0x80) = 0x80;
            }
            *(s16 *)(a + 0x84) = 0x300;
            *(s16 *)(a + 0x86) = 0x300;
            *(s16 *)(a + 0x82) = *(s16 *)(a + 0x80) * 2;
            if (a[3] == 0) {
                if (D_800BF8D4 == 1) {
                    a[5] = 2;
                } else if (D_800BF8D4 == 0xFF) {
                    a[5] = 4;
                }
            }
        }
        a[0] = 1;
        a[4]++;
    case 1:
        if (a[3] & 0x80) {
            if ((D_800BF9CE >> (a[3] & 3)) & 1) {
                a[0] = 1;
                if (D_1F800207 == 0xE) {
                    func_8007778C(a);
                }
            } else {
                a[0] = 2;
            }
        } else {
            if (!((D_800BF9CE >> a[3]) & 1)) {
                *(s16 *)(a + 0x32) = -0x1C00;
            } else {
                *(s16 *)(a + 0x32) = -0x1A40;
            }
            if (D_800BF871 == 0x13) {
                a[1] = 1;
                func_80077EBC(a);
                func_800517F8(a);
            }
        }
        if (a[3] != 0 || D_800E7FEE == 0) {
            break;
        }
        switch (a[5]) {
        case 0:
            if (D_800BF9CE == 4) {
                if (a[1] != 0) {
                    func_80040B48(0x20);
                    a[5] = 2;
                }
            } else {
                func_801265E4(a);
            }
            break;
        case 1:
            func_80126334(a, 0);
            break;
        case 2:
            if (D_800BF9CE == 0xF) {
                func_801265E4(a);
            }
            break;
        case 3:
            func_80126334(a, 1);
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

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80126334);

void func_801265E4(u8 *p)
{
    u8 *e;

    if (func_8005308C(p)) {
        e = D_800E7E80;
        if (e[0x164] == 0) {
            e[4] = 4;
            e[5] = 0x21;
            e[6] = 0;
            func_80054D14(e, 2, 6);
        }
        func_80042354(1, 1);
        p[6] = 0;
        p[5]++;
    }
}

typedef union {
    u8 b[0xC0];
    s16 h[0x60];
} ActorH;
extern s16 D_1F8001A0;
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
    u8 b[6][4];
} FlickerTbl;
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
s32 func_8012665C(DoorActor *a, s16 *d) {
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
    x = D_1F8001A0;
    y = D_1F8001A2;
    a->h60 = x;
    a->h62 = y;
    a->h56 = x;
    M2C_FIELD(a->parts[0], s16 *, 0xA) = M2C_FIELD(a->b, s16 *, 0x7C);
    return 0;
}

void func_80126834(u8 *a, s32 b) {
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
    if (func_8012665C(a, b) != 0) {
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

extern u8 D_800BF841;
extern u8 D_800E806E;
extern u16 D_1F8000D6;
void func_80126990(u8 *a) {
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
void func_80126BD8(u8 *a) {
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
        D_800BF808_1760[0x31] = 1;
        F16(D_800BF808_1760, 0x32) = a[0xBF] << 4;
        break;
    }
}

#define P_7be1(p, o) (*(u8 **)((u8 *)(p) + (o)))
extern u16 D_1F8000D0_fb20[];
extern u16 D_800E8008_d0cf[];
void func_80126DF0(u8 *a, u16 *b) {
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
            D_1F8000D0_fb20[1] = b[0];
            D_1F8000D0_fb20[3] = b[1];
            D_1F8000D0_fb20[5] = b[2];
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
            func_80027144(*(s32 *)(P_7be1(a, 0xC0) + 0x40), v, 0x800, 8);
            func_80074590(0xC, 0, 0);
            q = a + 0x2C;
            func_80027144(*(s32 *)(P_7be1(a, 0xC0) + 0x40), q, 0x600, 0x18);
            func_80074590(0xC, 0, 0);
            v[1] = U(P_7be1(a, 0xC4), 0x2C);
            v[1] = U(P_7be1(a, 0xC4), 0x30) + 0x80;
            v[1] = U(P_7be1(a, 0xC4), 0x34);
            p = func_8003116C(0x24, v, -0x32);
            p[0x28] |= 0x80;
            func_80027144(*(s32 *)(P_7be1(a, 0xC4) + 0x40), q, 0x800, 8);
            func_80074590(0xC, 0, 0);
            func_80027144(*(s32 *)(P_7be1(a, 0xC4) + 0x40), q, 0x600, 0x18);
            func_80074590(0xC, 0, 0);
            v[1] = U(P_7be1(a, 0xC8), 0x2C);
            v[1] = U(P_7be1(a, 0xC8), 0x30) + 0x80;
            v[1] = U(P_7be1(a, 0xCC), 0x34);
            p = func_8003116C(0x24, v, -0x32);
            p[0x28] |= 0x80;
            func_80027144(*(s32 *)(P_7be1(a, 0xC8) + 0x40), q, 0x800, 8);
            func_80074590(0xC, 0, 0);
            func_80027144(*(s32 *)(P_7be1(a, 0xC8) + 0x40), q, 0x600, 0x18);
            func_80074590(0xC, 0, 0);
        } else {
            H(P_7be1(a, 0xC0), 2) = (D_1F80017C_0fe7 & 1) * 6;
            H(P_7be1(a, 0xC0), 0) = ((func_8009A450() & 3) - 2) * 6;
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

extern ClutCycle D_80147A30[];
extern s8 D_8014CE64[];
void func_801271E4(s32 arg0) {
    ClutRect r;
    s32 i;
    ClutCycle *e;
    u8 *data;

    if (arg0 == 0) {
        for (i = 0; i < 1; i++) {
            D_8014CE64[i] = 0;
        }
        return;
    }
    e = D_80147A30;
    for (i = 0; i < 1; i++, e++) {
        if (--D_8014CE64[i] <= 0) {
            if (e->ptr[0] == 0xFF) {
                e->ptr -= e->ptr[1];
            }
            data = e->clut + e->ptr[0] * 32;
            D_8014CE64[i] = e->ptr[1];
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
extern u8 D_800E7E80_d97c;
extern u8 D_80147A3C[];
extern u8 D_80147A5C[];
extern s16 D_1F800160_71b4;
extern s16 D_1F800162_a8d4;
extern s16 D_1F800164_d75f;
extern u8 D_1F80027A;
void func_80127304(u8 *a)
{
    switch (a[4]) {
    case 0:
        switch (a[5]) {
        case 0:
            func_801271E4(0);
            a[0xBF] = 0xA0;
            *(s16 *)(a + 0x7E) = 0x17;
            *(s16 *)(a + 0x7C) = 0x400;
            *(s16 *)(a + 0x7A) = 7;
            *(s16 *)(a + 0x78) = 0x13;
            *(s16 *)(a + 0x54) = 0;
            *(s16 *)(a + 0x58) = 0;
            a[5]++;
        case 1:
            func_80126834(a, D_80147A3C);
            break;
        case 2:
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
            func_801271E4(1);
            func_80051844(a);
        }
        switch (a[0x5E]) {
        case 0:
            func_80126990(a);
            a[0x29] = 0;
            break;
        case 1:
            func_80126BD8(a);
            a[0x29] = 0;
            break;
        case 2:
            func_80126DF0(a, D_80147A5C);
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

extern u8 D_800BF809;
extern u8 D_800BF8E8;
extern u8 D_800E7EEF;
void func_80127524(u8 *a)
{
    s16 sp[8];

    switch (a[4]) {
    case 0:
        if (func_80051B70(a, 0xC, 0x64) == 0) {
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
        if (a[0x29] != 0 && D_800BF8E8 == 0) {
            func_80040B48(0x34);
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
            if (D_800E7EEF != 0x14) {
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
                func_80040C00(0x34);
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

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8012779C);

extern u8 D_800BF9D3;
extern s16 D_800E7FFE;
extern u8 D_80147B10[];
extern u8 D_80147B20[];
extern u8 D_80147B38[];
extern u8 D_80147BA0[];
extern u8 D_80147BD0[];
void func_80127928(u8 *a)
{
    u8 *g;

    func_8007778C(a);
    switch (a[5]) {
    case 0:
        g = (u8 *)&D_800BF870;
        if (g[0xAE] == 0) {
            if (D_800E7FFE & 0x8200) {
                a[5] = 7;
            } else {
                a[5] = 1;
            }
        } else if (g[0x163] == 2) {
            a[5] = 2;
        } else {
            a[5] = 4;
        }
        a[6] = 0;
        break;
    case 7:
        if (D_1F800137 == 0 && !(D_800E7FFE & 0x8200) && func_8005308C() != 0) {
            a[0] = 2;
            func_80042354(1, 3);
            func_80040D68(a, D_80147B20);
            a[0x70] = 2;
            a[6] = 1;
            a[5] = 1;
        }
        break;
    case 1:
        switch (a[6]) {
        case 0:
            if (D_800BF80F == 0 && !(D_800E7FFE & 0x8200)) {
                a[0] = 2;
                if (D_800BF9D3 < 2) {
                    func_80042354(1, 3);
                }
                func_80040D68(a, D_80147B10);
                a[0x70] = 2;
                a[6]++;
            }
            break;
        case 1:
            if (a[0x70] == 0xFF) {
                a[0] = 1;
                if (D_800BF9D3 >= 2) {
                    a[0] = 2;
                    func_80040D68(a, D_80147BD0);
                    a[6] = 0;
                    a[5] = 3;
                } else {
                    func_80040D68(a, D_80147B38);
                    a[6]++;
                }
                a[0x70] = 2;
            }
            break;
        case 2:
            if (a[0x70] == 0xFF) {
                a[5] = 4;
            }
            break;
        }
        break;
    case 2:
        switch (a[6]) {
        case 0:
            if (D_800BF80F == 0) {
                func_80040D68(a, D_80147BA0);
                a[0x70] = 2;
                a[6]++;
            }
            break;
        case 1:
            if (a[0x70] == 0xFF) {
                a[0] = 2;
                func_80040D68(a, D_80147BD0);
                a[6] = 0;
                a[5] = 3;
                a[0x70] = 2;
            }
            break;
        }
        break;
    case 3:
        if (a[0x70] == 0xFF) {
            a[4] = 3;
        }
        break;
    }
    func_80041098(a);
    func_8004190C(a);
}

extern u8 D_80141F80[];
extern u8 D_800A3D18[];
void func_80127C28(u8 *a)
{
    u8 *g;
    u8 *st;

    switch (a[4]) {
    case 0:
        g = D_800ECF58_742e;
        if (func_800519E0(a, 0xF, *(s32 *)(g + 0x3C), D_80141F80) != 0) {
            break;
        }
        *(s32 *)(a + 0x3C) = *(s32 *)(g + 0x38);
        func_80040CDC(a, D_8014D014, D_800A3D18);
        *(s16 *)(a + 0x80) = 0x78;
        *(s16 *)(a + 0x82) = 0xF0;
        *(s16 *)(a + 0x84) = 0x80;
        *(s16 *)(a + 0x86) = 0xE0;
        a[0xB] = 0;
        a[0] = 1;
        a[0x2B] = 0;
        a[0x29] = 0;
        a[0x7B] = 0x10;
        func_80041718(a, 0x10, 1);
        a[0x2A] = 0xE;
        *(s32 *)(a + 0x2C) = 0x23800000;
        *(s32 *)(a + 0x30) = 0xF3120000;
        *(s32 *)(a + 0x34) = 0x34B80000;
        func_8004766C(a);
        *(s16 *)(a + 0x56) = 0xC00;
        st = (u8 *)&D_800BF870;
        *(s16 *)(a + 0x58) = 0;
        *(s16 *)(a + 0x54) = 0;
        if (st[0x163] == 1) {
            st[0x163] = 2;
        }
        a[4]++;
        break;
    case 1:
        func_80127928(a);
        if (a[1] != 0) {
            func_800518FC(a);
        }
        a[0x2B] = 0;
        a[0x5F] = 0;
        a[0x29] = 0;
        break;
    case 2:
        if (func_8007778C(a)) {
            func_800518FC(a);
        }
        switch (a[5]) {
        case 2:
        case 3:
            a[5] = 4;
            *(s16 *)(a + 0x84) = 0x80;
            a[4] = 1;
            a[0] = 1;
            *(s16 *)(a + 0x86) = 0xE0;
            break;
        }
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

typedef struct { s16 p0, x, p4, y, p8, z; } HV;
extern u8 *D_1F800214;
s32 func_80127E18(u8 *a)
{
    HV v;
    u8 *g = D_1F800214;

    switch (a[0x78]) {
    default:
        return 0;
    case 0:
        if (*(s16 *)(a + 0x72) == 0 && D_800BF9D3 != 0) {
            return 1;
        }
        v.x = *(s16 *)(g + 0x2E);
        v.y = *(s16 *)(g + 0x32);
        if (*(s16 *)(a + 0x72) == 0) {
            v.z = 0x35B6;
        } else {
            v.z = D_1F800164_d75f;
        }
        func_80070F00(a, 1, &v);
        func_800708B4(3);
        a[0x78]++;
        break;
    case 1:
        if (g[3] == 0) {
            return 1;
        }
        break;
    }
    return 0;
}

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80127EF8);

extern u8 D_800BF80E;
s32 func_80127FEC(void *arg0) {
    u16 temp_v0;

    if ((D_800BF80E != 0) || (temp_v0 = M2C_FIELD(arg0, u16 *, 0x72), M2C_FIELD(arg0, u16 *, 0x72) = (u16) (temp_v0 - 1), ((temp_v0 << 0x10) <= 0))) {
        return 1;
    }
    return 0;
}

typedef struct { s16 x0; s16 id; u8 k; u8 p5; s16 v6; s16 v8; } Entry10;
extern Entry10 D_80147D58[];
void func_80128120();
u8 *func_80128028(u8 *a, s32 i)
{
    Entry10 *t = D_80147D58;
    Entry10 *e = &t[i];
    u8 *p;

    if (func_8004D7EC(e->id, 1)) {
        return NULL;
    }
    p = func_80072DDC(a, 2, 2, 8);
    if (p != NULL) {
        *(void **)(p + 0x1C) = func_80128120;
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
        p[0x2A] = 0x12;
        *(s16 *)(p + 0x6A) = 5;
        p[0x28] |= 0x80;
        return p;
    }
    return NULL;
}

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80128120);

extern u8 D_80147D64[];
extern u8 D_8001B4DC[];
extern u8 D_80147DDC[];
extern u8 D_80147E6C[];
void f_UpdateNishikiTempleBirdActor(u8 *a)
{
    u8 *g;
    u8 *st;

    switch (a[4]) {
    case 0:
        g = D_800ECF58_742e;
        if (func_800519E0(a, 0xF, *(s32 *)(g + 0x3C), D_80147D64) != 0) {
            break;
        }
        *(s32 *)(a + 0x3C) = *(s32 *)(g + 0x7C);
        func_80077C40(a, D_8001B4DC, 0);
        *(s16 *)(a + 0xB8) = 0x800;
        *(s16 *)(a + 0xBA) = 0x800;
        *(s16 *)(a + 0xBC) = 0x800;
        *(s16 *)(a + 0x56) = 0xC00;
        a[0] = 9;
        *(s16 *)(a + 0x80) = 0x3C;
        *(s16 *)(a + 0x82) = 0x78;
        *(s16 *)(a + 0x84) = 0x50;
        *(s16 *)(a + 0x54) = 0;
        *(s16 *)(a + 0x58) = 0;
        *(s16 *)(a + 0x86) = 0x90;
        a[0x2B] = 0;
        a[4]++;
        func_80051B04(*(u8 **)(a + 0xEC), 0xF, 0x13);
        func_80051B04(*(u8 **)(a + 0xF0), 0xF, 0x14);
        break;
    case 1:
        func_8007778C(a);
        func_8004190C(a);
        switch (a[6]) {
        case 0:
            if (a[0x2B] == 3) {
                a[6] = 1;
                func_80042354(1, 3);
            }
            break;
        case 1:
            st = (u8 *)&D_800BF870;
            if (st[0x1DE] == 2 && st[0x1D8] == 1) {
                func_80040CDC(a, D_8001B4DC, D_80147DDC);
                st[0x1DE] = 3;
                a[6] += 2;
            } else {
                func_80040CDC(a, D_8001B4DC, D_80147E6C);
                a[6]++;
            }
            a[0x70] = 1;
            break;
        case 2:
            func_80041098(a);
            if (a[0x70] == 0xFF) {
                a[6] = 0;
                func_80042310();
            }
            break;
        case 3:
            func_80041098(a);
            if (a[0x70] == 0xFF) {
                a[4] = 3;
                func_80042310();
            }
            break;
        }
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

extern s8 D_800BF818;
s32 func_80128780(void) {
    D_800BF818 = 7;
    return 1;
}

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80128794);

extern u8 D_80141F08[];
extern u8 D_800A3D70[];
extern u8 D_8014801C[];
void func_80128A70(u8 *a)
{
    u8 *g;
    u8 *st;

    switch (a[4]) {
    case 0:
        g = D_800ECF58_742e;
        if (func_800519E0(a, 0xF, *(s32 *)(g + 0x3C), D_80141F08) != 0) {
            break;
        }
        *(s32 *)(a + 0x3C) = *(s32 *)(g + 0x38);
        func_80040CDC(a, D_8014D014, D_800A3D18);
        a[0] = 9;
        *(s16 *)(a + 0x80) = 0x60;
        *(s16 *)(a + 0x82) = 0xC0;
        *(s16 *)(a + 0x84) = 0xC0;
        *(s16 *)(a + 0x86) = 0x160;
        *(s16 *)(a + 0x58) = 0;
        *(s16 *)(a + 0x54) = 0;
        *(s16 *)(a + 0x56) = 0x800;
        a[0xB] = (a[0xB] & 0xC0) | 0x80;
        st = (u8 *)&D_800BF870;
        if (st[0xA2] != 0xFF) {
            func_800416A8(a, -1, 0);
            if (st[0xA2] == 0) {
                a[0x7B] = 0xBD;
            } else {
                a[0x7B] = 0xE1;
            }
            a[0x5E] = 0;
        } else {
            a[0x7B] = 0;
            a[0x5E] = 1;
        }
        func_80041718(a, a[0x7B], 0);
        a[0x2B] = 0;
        a[0x29] = 0;
        a[4]++;
        break;
    case 1:
        switch (a[0x5E]) {
        case 0:
            func_80128794(a);
            break;
        case 1:
            switch (a[5]) {
            case 0:
                if (func_8007778C(a) != 0 && a[0x2B] == 3) {
                    func_80041768(a, a[0x7B], 4);
                    func_80042354(1, 3);
                    func_80040D68(a, D_800A3D70);
                    a[0x70] = 2;
                    a[6] = 0;
                    a[5]++;
                }
                break;
            case 1:
                a[1] = 1;
                func_80077E7C(a);
                if (a[0x70] == 0xFF) {
                    switch (a[6]) {
                    case 0:
                        a[0x7A] = 5;
                        func_80040D68(a, D_8014801C);
                        a[0x70] = 2;
                        a[6]++;
                        break;
                    case 1:
                        a[5] = 0;
                        break;
                    }
                }
                func_80041098(a);
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

s32 func_80128D30(u8 *a)
{
    switch (a[0x78]) {
    default:
        return 0;
    case 0:
        *(s16 *)(a + 0x72) = 0;
        a[0x78]++;
        break;
    case 1:
        if (++*(s16 *)(a + 0x72) % 6 == 0) {
            func_80074590(8, 6, -0x1E);
        }
        if (*(s16 *)(a + 0x72) >= 0x2A) {
            return 1;
        }
        break;
    }
    return 0;
}

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80128DF0);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80128F98);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80129218);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8012945C);

void func_801296A0(u8 *a)
{
    s32 k = 0x100;

    switch (a[6]) {
    case 0:
        a[6]++;
        a[0x46] = func_80077768(a[0x2B] << 4, *(s16 *)(a + 0x60), 0);
        *(s16 *)(a + 0x44) = 0;
    case 1:
        if ((*(s16 *)(a + 0x44) += 0x40) > 0x180) {
            a[6]++;
        }
        break;
    case 2:
        if ((*(s16 *)(a + 0x44) -= 0x30) < -0x100) {
            a[6]++;
        }
        break;
    case 3:
        if ((*(s16 *)(a + 0x44) += 0x20) > 0x80) {
            a[6]++;
        }
        break;
    case 4:
        if ((*(s16 *)(a + 0x44) -= 0x10) < 0) {
            *(s16 *)(a + 0x44) = 0;
            a[4] = 1;
            a[5] = 0;
            a[6] = 0;
        }
        break;
    }
    *(s16 *)(a + 0x2E) = *(s16 *)(a + 0x64);
    *(s16 *)(a + 0x32) = *(s16 *)(a + 0x66) - k;
    *(s32 *)(a + 0x30) += (func_80083F50(*(s16 *)(a + 0x44)) * k) << 4;
    if (a[0x46] == 0) {
        *(s32 *)(a + 0x2C) += (func_80083E80(*(s16 *)(a + 0x44)) * k) << 4;
    } else {
        *(s32 *)(a + 0x2C) -= (func_80083E80(*(s16 *)(a + 0x44)) * k) << 4;
    }
}

extern u8 D_8014E4D4[];
extern s16 D_80148044[];
/* func_8012A410, inlined */
static inline void func_8012A410_inl(u8 *a)
{
    if (a[3] == 0) {
        func_80051B04(*(void **)(a + 0xC0), 0xC, 7);
        func_80077C40(a, D_8014E4D4, 0);
    } else if (a[3] == 1) {
        func_80051B04(*(void **)(a + 0xC0), 0xC, 9);
        func_80077C40(a, D_8014E4D4, 4);
    } else {
        func_80051B04(*(void **)(a + 0xC0), 0xC, 8);
        func_80077C40(a, D_8014E4D4, 1);
    }
}
/* func_8012A384, inlined */
static inline void func_8012A384_inl(u8 *a)
{
    if (a[0x5E] == 0) {
        a[0x2A] = 0;
        func_80041194(a, *(s16 *)(a + 0x86) - *(s16 *)(a + 0x84), 0, 0);
        return;
    }
    func_8004766C(a);
    func_80049760(a);
    *(s16 *)(a + 0x60) = D_1F8001A0;
    *(s16 *)(a + 0x62) = D_1F8001A2;
    *(s16 *)(a + 0x56) = *(s16 *)(a + 0x60);
    ((void (*)(void *))func_8011AD34)(a);
}
void func_80129858(u8 *a)
{
    s32 t;
    s16 n;

    switch (a[5]) {
    case 0:
        H(a, 0x40) = 0x384;
        a[5]++;
        a[3] = a[0x7C];
        func_8012A410_inl(a);
        H(a, 0x2E) = H(a, 0x64);
        H(a, 0x36) = H(a, 0x68);
        return;
    case 1:
        if (--H(a, 0x40) == 0) {
            if (a[0x5E] == 1) {
                s16 v = D_80148044[H(a, 0x7E)];
                H(a, 0x50) = 0x200;
                H(a, 0x4A) = 0;
                a[5] = 2;
                H(a, 0x32) = v;
            } else {
                H(a, 0x4A) = -0x1000;
                a[5] = 3;
                H(a, 0x32) = H(a, 0x66) + 0x12C;
            }
        }
        return;
    case 2:
        *(s32 *)(a + 0x30) += H(a, 0x4A) << 8;
        n = H(a, 0x4A) + H(a, 0x50);
        H(a, 0x4A) = n;
        if (n > 0x3000) {
            H(a, 0x4A) = 0x3000;
        }
        if (!(H(a, 0x32) < H(a, 0x66))) {
            H(a, 0x32) = H(a, 0x66);
            a[5] = 4;
        }
        break;
    case 3:
        *(s32 *)(a + 0x30) += H(a, 0x4A) << 8;
        if (H(a, 0x32) <= H(a, 0x66)) {
            H(a, 0x32) = H(a, 0x66);
            a[5] = 4;
        }
        break;
    case 4:
        func_8012A384_inl(a);
        a[4] = 1;
        a[5] = 0;
        a[6] = 0;
        a[7] = 0;
        a[0] = 1;
        break;
    }
    func_8007778C(a);
    func_80076D68(a);
    func_800518FC(a);
}

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80129AF8);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80129C50);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8012A2B8);

s32 func_8011AD34(void);
void func_8012A384(u8 *a)
{
    if (a[0x5E] == 0) {
        a[0x2A] = 0;
        func_80041194(a, *(s16 *)(a + 0x86) - *(s16 *)(a + 0x84), 0, 0);
        return;
    }
    func_8004766C(a);
    func_80049760(a);
    *(s16 *)(a + 0x60) = D_1F8001A0;
    *(s16 *)(a + 0x62) = D_1F8001A2;
    *(s16 *)(a + 0x56) = *(s16 *)(a + 0x60);
    ((void (*)(void *))func_8011AD34)(a);
}

void func_8012A410(u8 *a)
{
    if (a[3] == 0) {
        func_80051B04(*(void **)(a + 0xC0), 0xC, 7);
        func_80077C40(a, D_8014E4D4, 0);
    } else if (a[3] == 1) {
        func_80051B04(*(void **)(a + 0xC0), 0xC, 9);
        func_80077C40(a, D_8014E4D4, 4);
    } else {
        func_80051B04(*(void **)(a + 0xC0), 0xC, 8);
        func_80077C40(a, D_8014E4D4, 1);
    }
}

void func_8012A4B0(u8 *a)
{
    if (a[3] == 0) {
        func_80058304(D_800E7E80, 0xA);
    } else if (a[3] == 1) {
        func_80040B48(0x56);
        func_80058304(D_800E7E80, 0xD);
    } else {
        func_80040B48(0x57);
        func_80058304(D_800E7E80, 0xE);
    }
    a[4] = 4;
    a[5] = 0;
    a[0] = 2;
    func_800315D4(a + 0x2C);
}

void func_8012A548(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 6) == 0) {
        M2C_FIELD(arg0, u8 *, 6) = 1U;
    }
}

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8012A564);

u8 *func_8012A900(void *a0)
{
    u8 *r = func_8007A980(1, 2, 0);

    if (r == 0) {
        return 0;
    }
    r[2] = 0x3C;
    r[3] = 0;
    *(void **)(r + 0x1C) = func_8012A564;
    *(void **)(r + 0x10) = a0;
    return r;
}

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8012A958);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8012AAF0);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8012AD3C);

extern u8 D_80141D98[];
void func_8012B14C(u8 *a)
{
    u8 *g;

    switch (a[4]) {
    case 0:
        g = D_800ECF58_742e;
        if (func_800519E0(a, 0x10, *(s32 *)(g + 0x3C), D_80141D98) != 0) {
            break;
        }
        *(s32 *)(a + 0x3C) = *(s32 *)(g + 0x38);
        func_80040CDC(a, D_8014D014, D_800A3D18);
        (*(u8 **)(a + ((a[9] - 1) << 2) + 0xC0))[0x3F] = 0xF;
        *(s16 *)(a + 0x56) = 0x1A3;
        a[0xD] = 4;
        a[0] = 9;
        *(s16 *)(a + 0x80) = 0x60;
        *(s16 *)(a + 0x82) = 0xC0;
        *(s16 *)(a + 0x84) = 0x100;
        a[0xB] = 0;
        *(s16 *)(a + 0x86) = 0x160;
        a[0x2B] = 0;
        a[0x29] = 0;
        a[0x7B] = 0;
        *(s16 *)(a + 0x58) = 0;
        *(s16 *)(a + 0x54) = 0;
        *(s32 *)(a + 0x30) = 0xE3E00000;
        a[0xB] = (a[0xB] & 0xC0) | 0x40;
        *(s16 *)(a + 0x2E) = 0x5D2A - ((func_80083F50(*(s16 *)(a + 0x56)) * 0xC0) >> 12);
        *(s16 *)(a + 0x36) = 0x4122 - ((-func_80083E80(*(s16 *)(a + 0x56)) * 0xC0) >> 12);
        func_80041718(a, 0x1B, 0);
        a[4]++;
        break;
    case 1:
        func_8012AD3C(a);
        if (a[1] != 0) {
            func_800518FC(a);
            if (a[0x46] == 0x1B && !(D_1F80017C_0fe7 & 0x1F)) {
                func_80074590(2, 7, 0);
            }
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

s32 func_8012B350(u8 *p)
{
    S13AE38 v;
    u8 *r;

    v.a = 0x5D2A;
    v.b = -0x1C08;
    v.c = 0x4122;
    *(u8 **)(p + 0x14) = 0;
    r = func_8003116C(0x716, &v, -0x14);
    if (r) {
        *(u8 **)(p + 0x14) = r;
        r[0x28] |= 0x80;
    }
    return 1;
}

s32 func_8012B3C0(void)
{
    if ((D_800BFA1F & 0xF) == 0xF) {
        return 3;
    }
    return 2;
}

INCLUDE_ASM("asm/a06/nonmatchings/a06", f_UpdatePotatoBugEatsLeavesActor);

extern M2C_UNK D_1F800000;
extern M2C_UNK D_1F800020;
extern M2C_UNK D_1F800040;
void func_8012B868(void *arg0) {
    M2C_UNK *temp_s4;
    void *temp_s2;

    temp_s2 = M2C_FIELD(arg0, void **, 0xC0);
    func_800517BC(&D_1F800000, M2C_FIELD(arg0, s16 *, 0xB8), M2C_FIELD(arg0, s16 *, 0xBA), M2C_FIELD(arg0, s16 *, 0xBC));
    func_80051794(&D_1F800020);
    func_80084D10(M2C_FIELD(arg0, s16 *, 0x54), &D_1F800020);
    func_80085050(M2C_FIELD(arg0, s16 *, 0x58), &D_1F800020);
    func_80084EB0(M2C_FIELD(arg0, s16 *, 0x56), &D_1F800020);
    temp_s4 = arg0 + 0x98;
    func_80084110(&D_1F800020, &D_1F800000, temp_s4);
    M2C_FIELD(arg0, s32 *, 0xAC) = (s32) M2C_FIELD(arg0, s16 *, 0x2E);
    M2C_FIELD(arg0, s32 *, 0xB0) = (s32) M2C_FIELD(arg0, s16 *, 0x32);
    M2C_FIELD(arg0, s32 *, 0xB4) = (s32) M2C_FIELD(arg0, s16 *, 0x36);
    func_800517BC(&D_1F800000, M2C_FIELD(temp_s2, s16 *, 0x38), M2C_FIELD(temp_s2, s16 *, 0x3A), M2C_FIELD(temp_s2, s16 *, 0x3C));
    func_80051794(&D_1F800020);
    func_80084D10(M2C_FIELD(temp_s2, s16 *, 8), &D_1F800020);
    func_80085050(M2C_FIELD(temp_s2, s16 *, 0xC), &D_1F800020);
    func_80084EB0(M2C_FIELD(temp_s2, s16 *, 0xA), &D_1F800020);
    func_80084110(&D_1F800000, &D_1F800020, &D_1F800040);
    func_80084110(temp_s4, &D_1F800040, temp_s2 + 0x18);
    func_80084220(temp_s2, temp_s2 + 0x2C);
    M2C_FIELD(temp_s2, s32 *, 0x2C) = (s32) (M2C_FIELD(temp_s2, s32 *, 0x2C) + M2C_FIELD(arg0, s32 *, 0xAC));
    M2C_FIELD(temp_s2, s32 *, 0x30) = (s32) (M2C_FIELD(temp_s2, s32 *, 0x30) + M2C_FIELD(arg0, s32 *, 0xB0));
    M2C_FIELD(temp_s2, s32 *, 0x34) = (s32) (M2C_FIELD(temp_s2, s32 *, 0x34) + M2C_FIELD(arg0, s32 *, 0xB4));
}

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8012B9D8);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8012BB14);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8012BDA0);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8012C050);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8012C4C4);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8012CFA4);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8012D4E4);

void func_8012D864(u8 *a)
{
    s16 y = -0xD98;
    *(s16 *)(a + 0x2E) = 0x2380;
    *(s16 *)(a + 0x32) = y;
    *(s16 *)(a + 0x36) = 0x4B1A;
    **(s16 **)(a + 0xC0) = 0x8C;
    func_80041194(a, *(s16 *)(a + 0x86) - *(s16 *)(a + 0x84), 0, 0);
    a[0] = 1;
    *(s16 *)(a + 0x32) = y;
    *(s16 *)(a + 0x60) = 0;
    a[5] = 3;
    a[6] = 0;
}

s32 func_8012D8E4(u8 *p, s32 a1, s32 step)
{
    s16 target = a1;
    s16 cur = *(s16 *)(p + 0x58);

    if (cur == target) {
        return 1;
    }
    if (target < cur) {
        *(s16 *)(p + 0x58) = cur - step;
        if (target >= *(s16 *)(p + 0x58)) {
            *(s16 *)(p + 0x58) = a1;
            return 1;
        }
    } else if (cur < target) {
        *(s16 *)(p + 0x58) = cur + step;
        if (*(s16 *)(p + 0x58) >= target) {
            *(s16 *)(p + 0x58) = a1;
            return 1;
        }
    }
    return 0;
}

void func_8012D954(u8 *p)
{
    *(s16 *)(p + 0x32) += 0x10;
    if (*(s16 *)(p + 0x32) >= -0xD98) {
        *(s16 *)(p + 0x32) = -0xD98;
    }
    if (p[6] == 0 && *(s16 *)(p + 0xE) == 0) {
        *(s16 *)(p + 0x60) = 0;
        p[6]++;
    }
}

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8012D9B4);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8012DBF8);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8012DDC4);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8012E048);

extern u8 D_80141FF8[];
extern u8 D_8014D94C[];
void func_8012E194(u8 *a)
{
    u8 *g;
    u8 *st;
    s16 d;
    s32 k;

    switch (a[4]) {
    case 0:
        g = D_800ECF58_742e;
        if (func_800519E0(a, 6, *(s32 *)(g + 0x50), D_80141FF8) != 0) {
            break;
        }
        *(s32 *)(a + 0x3C) = *(s32 *)(g + 0x54);
        func_80077C40(a, D_8014D94C, 0);
        *(s16 *)(a + 0x80) = 0x8C;
        *(s16 *)(a + 0x82) = 0x118;
        *(s16 *)(a + 0x84) = 0x88;
        *(s16 *)(a + 0x86) = 0xC4;
        *(s16 *)(a + 0x54) = 0;
        *(s16 *)(a + 0x58) = 0;
        a[4]++;
        switch (a[3]) {
        case 0:
            a[0] = 1;
            a[0x2B] = 0;
            a[0xBE] = 0;
            func_80041194(a, *(s16 *)(a + 0x86) - *(s16 *)(a + 0x84), 0, 0);
            func_8004130C(a, 0);
            a[0x5E] = 0;
            break;
        case 1:
            *(s16 *)(a + 0x56) = -0x400;
            break;
        case 2:
            *(s16 *)(a + 0x56) = 0x400;
            break;
        }
        break;
    case 1:
        func_8007778C(a);
        st = D_800BF808_1760;
        if (st[1] == 0) {
            switch (a[3]) {
            case 0:
                func_8012D9B4(a);
                a[0x2B] = 0;
                break;
            case 1:
                st = *(u8 **)(st + 0x5C);
                d = *(s16 *)(a + 0x86) - *(s16 *)(a + 0x84) - 0x1F4;
                *(s16 *)(a + 0x32) = *(s16 *)(*(u8 **)(st + 0xC8) + 0x30) - d;
                break;
            case 2:
                func_8012E048(a);
                break;
            }
            if (a[1] == 0) {
                break;
            }
            func_8004190C(a);
        }
        func_800518FC(a);
        break;
    case 2:
        func_8007778C(a);
        func_8004190C(a);
        k = a[5];
        if (k == 1) {
            a[8] = 1;
        } else if (k != 0 && k < 4) {
            if (D_800E7FEE != 0) {
                func_80040B48(0x21);
                func_8004D4C4(0x31, 1);
                func_8004B0D8(a);
            }
            a[4] = 3;
        }
        func_800518FC(a);
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

void func_8012E438(void *arg0) {
    M2C_FIELD(arg0, s16 *, 0x80) = 0x8C;
    M2C_FIELD(arg0, s16 *, 0x82) = 0x118;
    M2C_FIELD(arg0, s16 *, 0x84) = 0x88;
    M2C_FIELD(arg0, s16 *, 0x86) = 0xC4;
}

void func_8012E45C(void *arg0) {
    M2C_FIELD(arg0, s16 *, 0x80) = 0x8C;
    M2C_FIELD(arg0, s16 *, 0x82) = 0x118;
    M2C_FIELD(arg0, s16 *, 0x84) = 0x3C;
    M2C_FIELD(arg0, s16 *, 0x86) = 0xC4;
}

void func_8012E480(void *arg0) {
    if (D_800E7FEE != 0) {
        func_80040B48(0x21);
        func_8004D4C4(0x31, 1);
        func_8004B0D8(arg0);
    }
    M2C_FIELD(arg0, s8 *, 4) = 3;
}

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8012E4D0);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8012E7A8);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8012E984);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8012ED0C);

INCLUDE_ASM("asm/a06/nonmatchings/a06", f_UpdateForestGhostAndRockCrabActor);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8012F694);

extern u8 D_8014D97C[];
void func_8012F79C(u8 *a)
{
    switch (a[6]) {
    case 0:
        a[6]++;
        func_80077C40(a, D_8014D97C, 3);
        func_80074590(0x95, 0, 0);
        break;
    case 1:
        break;
    case 2:
        if (D_1F800160_71b4 < 0x4930) {
            u8 *t = D_800E7E80;
            *(s16 *)(t + 0x2E) = 0x4930;
            *(s16 *)(t + 0x36) = 0x27B0;
        }
        break;
    }
}

void func_8012F844(u8 *a)
{
    if (D_800E7FEE == 0) {
        a[0] = 2;
        a[4] = 3;
        func_8003116C(0x706, a + 0x2C, -0x20);
    } else {
        a[0] = 2;
        a[4] = 3;
        func_8011AE04(a, a[3]);
        D_800BF870.pad1[0x1A3] |= 1 << a[3];
        func_8003116C(0x706, a + 0x2C, -0x20);
    }
}

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8012F8E0);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8012F9A8);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8012FAF0);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8012FBF0);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8012FE60);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80130468);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80130A2C);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80130BB4);

extern u8 D_800BF81E;
extern s32 D_1F80023C;
/* func_80131BB4, inlined */
static inline void Check_1BE8(void)
{
    u8 *s = D_800E7E80;

    if (s[5] == 0x18 && s[0] == 6) {
        s[6] = 2;
    }
}
void func_80130D98(u8 *a)
{
    u8 *s = D_800E7E80;
    u8 *q;

    switch (a[6]) {
    case 0:
        Check_1BE8();
        func_80074590(0x1B, 0, 0);
        q = *(u8 **)(a + 0x10);
        if (q != NULL) {
            q[6] = 0;
            q[5] = 0;
            q[4] = 3;
            *(u8 **)(a + 0x10) = NULL;
        }
        func_8003116C(0x706, a + 0x2C, -0x1E);
        a[0] = 2;
        *(s16 *)(a + 0x40) = 3;
        if (*(u16 *)(s + 0x17E) & 0x200) {
            D_800BF81E = 0;
            D_1F800137 = 2;
        }
        a[6]++;
        break;
    case 1:
        if (--*(s16 *)(a + 0x40) < 0) {
            if (*(u16 *)(s + 0x17E) & 0x200) {
                if (*(s16 *)(s + 0x16E) != 0 && s[4] != 2) {
                    D_800BF81E = 0;
                    D_1F80023C = *(s32 *)(s + 4);
                    s[5] = 0x3A;
                    s[0x6F] = 0;
                    s[6] = 0;
                    func_8004ED94(0x44, 0x41);
                }
            }
            a[5] = 0;
            a[4] = 4;
        }
        break;
    }
}

extern u8 D_800E7EAC_abee[];
/* func_80131B10, inlined */
static inline void inl_80131B10(u8 *a)
{
    u8 *o;
    switch (a[6]) {
    case 0:
        *(s16 *)(a + 0x40) = 0;
        a[6]++;
    case 1:
        if (a[1] == 0) {
            if (++*(s16 *)(a + 0x40) >= 0x708) {
                o = *(u8 **)(a + 0x10);
                if (o != NULL) {
                    o[6] = 0;
                    o[5] = 0;
                    o[4] = 3;
                    *(u8 **)(a + 0x10) = NULL;
                }
                a[5] = 1;
                a[4] = 0;
                return;
            }
        } else {
            a[6] = 0;
            a[5] = 0;
            return;
        }
        break;
    }
}
/* func_80131BE8, inlined */
static inline void inl_80131BE8(u8 *a)
{
    switch (a[6]) {
    case 0:
        Check_1BE8();
        func_80074590(0x95, 0, 0);
        *(s16 *)(a + 0x84) = 0x20;
        *(s16 *)(a + 0x86) = 0x94;
        func_80041768(a, 3, 4);
        func_80026100(4);
        *(s16 *)(a + 0x72) = *(s16 *)(a + 0x32);
        a[6]++;
    case 1:
        *(s16 *)(a + 0x42) += func_8009A450() & 0x3F;
        *(s16 *)(a + 0x32) = *(s16 *)(a + 0x72) + (func_80083E80(*(s16 *)(a + 0x42)) >> 7);
        break;
    }
}
/* func_80131CD4, inlined */
static inline void inl_80131CD4(u8 *a)
{
    u8 *q;

    switch (a[6]) {
    case 0:
        Check_1BE8();
        a[0] = 2;
        func_80041768(a, 5, 4);
        *(s16 *)(a + 0x40) = 0x10;
        a[6]++;
        break;
    case 1:
        if (--*(s16 *)(a + 0x40) < 0) {
            func_80074590(0x1B, 0, 0);
            q = *(u8 **)(a + 0x10);
            if (q != NULL) {
                q[6] = 0;
                q[5] = 0;
                q[4] = 3;
                *(u8 **)(a + 0x10) = NULL;
            }
            func_8003116C(0x706, a + 0x2C, -0x1E);
            a[5] = 0;
            a[4] = 4;
        }
        break;
    }
}
/* func_80131650, inlined */
static inline s32 inl_80131650(u8 *p)
{
    u8 *q = *(u8 **)(p + 0x10);

    if (q != 0) {
        q[6] = 0;
        q[5] = 0;
        q[4] = 3;
        *(u8 **)(p + 0x10) = 0;
        return 1;
    }
    return 0;
}
void func_80130F1C(u8 *a)
{
    u8 c;
    u8 *q;

    switch (a[4]) {
    case 0:
        func_8012F9A8(a);
        break;
    case 1:
        if (!(a[3] & 0x80)) {
            if (D_1F800207 >= 7) {
                return;
            }
        } else {
            c = D_1F800207;
            if (c == 0xE && D_1F800160_71b4 >= 0x283C) {
                return;
            }
            if (c >= 1 && c < 14) {
                return;
            }
        }
        if (a[5] != 5) {
            func_8007778C(a);
        }
        if (a[0x2B] != 0) {
            a[6] = 0;
            a[5] = 0;
            a[4] = 2;
            return;
        }
        if (D_1F800137 == 0) {
            if (D_800BF809 == 0) {
                switch (a[5]) {
                case 0:
                    func_8012FBF0(a);
                    break;
                case 1:
                    func_8012FE60(a);
                    break;
                case 2:
                    func_80130468(a);
                    break;
                case 3:
                    func_80130A2C(a);
                    break;
                case 4:
                    func_80130BB4(a);
                    break;
                case 5:
                    switch (a[6]) {
                    case 0:
                        if (func_8013B738(a, D_800E7EAC_abee, 1) < 3) {
                            func_8003116C(0x70C, a + 0x2C, -0x14);
                            *(s16 *)(a + 0x40) = 0xE;
                            a[6]++;
                        }
                        break;
                    case 1:
                        if (--*(s16 *)(a + 0x40) < 0) {
                            func_8003116C(0x705, a + 0x2C, -0x14);
                            *(s16 *)(a + 0x40) = 0x14;
                            a[6]++;
                        }
                        break;
                    case 2:
                        if (--*(s16 *)(a + 0x40) < 0) {
                            a[0] = 1;
                            a[6] = 0;
                            a[5] = 0;
                        }
                        break;
                    }
                    break;
                case 6:
                    inl_80131B10(a);
                    break;
                }
            }
        } else {
            u8 *r = *(u8 **)(a + 0x10);
            switch (a[5]) {
            case 3:
            case 4:
                if (*(u16 *)(r + 4) == 0x501) {
                    a[6] = 0;
                    a[5] = 0;
                    a[4] = 2;
                }
                break;
            }
        }
        if (a[1] != 0) {
            func_8004190C(a);
        }
        func_800518FC(a);
        a[0x5F] = 0;
        a[0x29] = 0;
        break;
    case 2:
        switch (a[5]) {
        case 1:
            func_8007778C(a);
            inl_80131BE8(a);
            break;
        case 10:
            if ((s16)func_8013B668(a) != 0) {
                Check_1BE8();
                func_80074590(0x37, 0x20, 0);
                goto release;
            }
            a[6] = 0;
            a[5] = 0;
            break;
        case 2:
            func_80130D98(a);
            break;
        case 11:
            if (func_80080750(a, *(s32 *)(a + 0xC0), 0) != 0) {
                Check_1BE8();
            release:
                q = *(u8 **)(a + 0x10);
                if (q != NULL) {
                    q[6] = 0;
                    q[5] = 0;
                    q[4] = 3;
                    *(u8 **)(a + 0x10) = NULL;
                }
                a[5] = 0;
                a[4] = 4;
                return;
            }
            a[5] = 2;
            break;
        case 0:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
            func_8007778C(a);
            inl_80131CD4(a);
            break;
        case 9:
            break;
        }
        if (a[1] != 0) {
            func_8004190C(a);
            func_800518FC(a);
        }
        a[0x5F] = 0;
        a[0x29] = 0;
        break;
    case 3:
        if (inl_80131650(a) == 0) {
            func_8007A624(a);
        }
        break;
    case 4:
        switch (a[5]) {
        case 0:
            q = *(u8 **)(a + 0x10);
            if (q != NULL) {
                q[6] = 0;
                q[5] = 0;
                q[4] = 3;
                *(u8 **)(a + 0x10) = NULL;
            }
            *(s16 *)(a + 0x40) = (func_8009A450() & 0xFF) + 0x4B0;
            a[5]++;
            break;
        case 1:
            if (--*(s16 *)(a + 0x40) < 0) {
                a[4] = 0;
            }
            break;
        }
        break;
    }
}

s32 func_80131650(u8 *p)
{
    u8 *q = *(u8 **)(p + 0x10);

    if (q != 0) {
        q[6] = 0;
        q[5] = 0;
        q[4] = 3;
        *(u8 **)(p + 0x10) = 0;
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80131680);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80131750);

void func_80131870(u8 *p)
{
    if (p[0xBE] == 0) {
        *(s16 *)(p + 0x62) = *(s16 *)(p + 0x44) >> 4;
    } else {
        *(s16 *)(p + 0x62) = (0x1000 - (*(s16 *)(p + 0x44) >> 4)) & 0xFFF;
    }
    *(s16 *)(p + 0x58) = *(s16 *)(p + 0x62);
}

void func_801318BC(void *arg0, s32 arg1) {
    s32 var_s0;
    u16 temp_a0;
    u16 temp_v1;

    var_s0 = arg1;
    if ((var_s0 == 8) && ((temp_v1 = M2C_FIELD(arg0, u16 *, 0x66), (((u32) (temp_v1 - 0xB00) < 0x201U) != 0)) || ((u32) (temp_v1 - 0x100) < 0x401U))) {
        var_s0 = 0xA;
    }
    temp_a0 = M2C_FIELD(arg0, u16 *, 0x42) + 0x1F;
    M2C_FIELD(arg0, u16 *, 0x42) = temp_a0;
    M2C_FIELD(arg0, u16 *, 0x32) = (u16) (M2C_FIELD(arg0, u16 *, 0x32) + (func_80083E80((s16) temp_a0) >> var_s0));
}

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80131944);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80131A18);

void func_80131B10(u8 *a)
{
    u8 *o;
    switch (a[6]) {
    case 0:
        *(s16 *)(a + 0x40) = 0;
        a[6]++;
    case 1:
        if (a[1] == 0) {
            if (++*(s16 *)(a + 0x40) >= 0x708) {
                o = *(u8 **)(a + 0x10);
                if (o != NULL) {
                    o[6] = 0;
                    o[5] = 0;
                    o[4] = 3;
                    *(u8 **)(a + 0x10) = NULL;
                }
                a[5] = 1;
                a[4] = 0;
                return;
            }
        } else {
            a[6] = 0;
            a[5] = 0;
            return;
        }
        break;
    }
}

void func_80131BB4(void)
{
    u8 *s = D_800E7E80;

    if (s[5] == 0x18 && s[0] == 6) {
        s[6] = 2;
    }
}

void func_80131BE8(u8 *a)
{
    switch (a[6]) {
    case 0:
        Check_1BE8();
        func_80074590(0x95, 0, 0);
        *(s16 *)(a + 0x84) = 0x20;
        *(s16 *)(a + 0x86) = 0x94;
        func_80041768(a, 3, 4);
        func_80026100(4);
        *(s16 *)(a + 0x72) = *(s16 *)(a + 0x32);
        a[6]++;
    case 1:
        *(s16 *)(a + 0x42) += func_8009A450() & 0x3F;
        *(s16 *)(a + 0x32) = *(s16 *)(a + 0x72) + (func_80083E80(*(s16 *)(a + 0x42)) >> 7);
        break;
    }
}

void func_80131CD4(u8 *a)
{
    u8 *q;

    switch (a[6]) {
    case 0:
        Check_1BE8();
        a[0] = 2;
        func_80041768(a, 5, 4);
        *(s16 *)(a + 0x40) = 0x10;
        a[6]++;
        break;
    case 1:
        if (--*(s16 *)(a + 0x40) < 0) {
            func_80074590(0x1B, 0, 0);
            q = *(u8 **)(a + 0x10);
            if (q != NULL) {
                q[6] = 0;
                q[5] = 0;
                q[4] = 3;
                *(u8 **)(a + 0x10) = NULL;
            }
            func_8003116C(0x706, a + 0x2C, -0x1E);
            a[5] = 0;
            a[4] = 4;
        }
        break;
    }
}

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80131DD8);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8013203C);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8013256C);

INCLUDE_ASM("asm/a06/nonmatchings/a06", Guards);

void Guards();
u8 *func_80132CF8(s32 a, s32 b)
{
    u8 *p = func_80072DDC(0, 3, 2, 0x44);

    if (p != NULL) {
        *(void **)(p + 0x1C) = Guards;
        p[3] = b;
        if (b == 0) {
            *(s16 *)(p + 0x2E) = 0x444A;
            *(s16 *)(p + 0x32) = -0x782;
            *(s16 *)(p + 0x36) = 0x22CA;
        } else if (b == 1) {
            *(s16 *)(p + 0x2E) = 0x46B5;
            *(s16 *)(p + 0x32) = -0x7C2;
            *(s16 *)(p + 0x36) = 0x2535;
        }
    }
    return p;
}

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80132D84);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80132ED0);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8013304C);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80133274);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80133644);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_801338A8);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_801340FC);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8013428C);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80134564);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80134B60);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80134C0C);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80134D54);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8013500C);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8013529C);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_801354C0);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8013560C);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80135A20);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80135D58);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80135E7C);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_801363E8);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80136600);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80136848);

u8 *func_80136C10(u8 *a0)
{
    u8 *r = func_8007A980(2, 2, 0);

    if (r == 0) {
        return 0;
    }
    r[2] = 0x48;
    r[3] = a0[3];
    *(void **)(r + 0x1C) = func_80136848;
    *(void **)(r + 0x10) = a0;
    return r;
}

void func_80136C6C(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 6) == 0) {
        M2C_FIELD(M2C_FIELD(arg0, void **, 0xC0), s16 *, 0) = 0;
        M2C_FIELD(M2C_FIELD(arg0, void **, 0xC0), s16 *, 2) = 0x50;
        M2C_FIELD(M2C_FIELD(arg0, void **, 0xC0), s16 *, 4) = 0x68;
        M2C_FIELD(M2C_FIELD(arg0, void **, 0xC4), s16 *, 0) = 0;
        M2C_FIELD(M2C_FIELD(arg0, void **, 0xC4), s16 *, 2) = 0x50;
        M2C_FIELD(M2C_FIELD(arg0, void **, 0xC4), s16 *, 4) = -0x68;
        M2C_FIELD(M2C_FIELD(arg0, void **, 0xC0), s16 *, 8) = 0;
        M2C_FIELD(M2C_FIELD(arg0, void **, 0xC0), s16 *, 0xA) = 0;
        M2C_FIELD(M2C_FIELD(arg0, void **, 0xC0), s16 *, 0xC) = 0;
        M2C_FIELD(M2C_FIELD(arg0, void **, 0xC4), s16 *, 8) = 0;
        M2C_FIELD(M2C_FIELD(arg0, void **, 0xC4), s16 *, 0xA) = 0;
        M2C_FIELD(M2C_FIELD(arg0, void **, 0xC4), s16 *, 0xC) = 0;
        M2C_FIELD(M2C_FIELD(arg0, void **, 0xC0), s16 *, 2) = 0;
        M2C_FIELD(M2C_FIELD(arg0, void **, 0xC4), s16 *, 2) = 0;
        M2C_FIELD(M2C_FIELD(arg0, void **, 0xC0), s16 *, 8) = -0x4E2;
        M2C_FIELD(M2C_FIELD(arg0, void **, 0xC4), s16 *, 8) = 0x4E2;
        M2C_FIELD(arg0, s16 *, 0x58) = 0xC00;
        M2C_FIELD(arg0, u8 *, 6) = (u8) (M2C_FIELD(arg0, u8 *, 6) + 1);
    }
    if (M2C_FIELD(arg0, u8 *, 1) != 0) {
        func_800518FC(arg0, arg0);
    }
}

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80136D84);

M2C_UNK func_80041768(void *, M2C_UNK, M2C_UNK);
M2C_UNK func_800440E4(M2C_UNK *, M2C_UNK, M2C_UNK);
M2C_UNK func_8004D650(M2C_UNK, M2C_UNK);
M2C_UNK func_8004ED0C(M2C_UNK, M2C_UNK);
extern u8 D_800BF80E;
extern u8 D_800BF822;
extern void *D_800BF844;
s32 func_80137148(u8 *a) {
    u8 *s = D_800BF844;
    switch (a[0x78]) {
    case 0:
        func_800440E4(D_800E7E80, 0xCF, 4);
        s[5] = 0;
        s[0x5E] = 0;
        func_8004ED0C(0x30, 4);
        func_8004D650(0x30, 1);
        a[0x78]++;
        break;
    case 1:
        if (D_800BF80E != 0) {
            func_80041768(a, 0xC, 4);
            a[0x78]++;
        }
        break;
    case 2:
        if ((*(u8 **)(a + 0x38))[4] != 0) {
            s[4] = 2;
            func_800440E4(D_800E7E80, 2, 4);
            a[0x78]++;
        }
        break;
    case 3:
        if (a[0x79] == 1) {
            func_80041768(a, 0x17, 4);
            a[0x78]++;
        }
        break;
    case 4:
        if (!(D_800BF822 & 1)) {
            return 1;
        }
        break;
    }
    return 0;
}

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80137284);

extern u8 D_800A3D40[];
extern u8 D_80148ECC[];
extern u8 D_80148F74[];
extern u8 D_80148F84[];
extern u8 D_80148FB4[];
void func_801379D4(u8 *a)
{
    a[1] = 1;
    func_80077E7C(a);
    switch (a[5]) {
    case 0:
        if (D_800BF870.pad1[0x62] == 0xFF) {
            a[5] = 3;
        } else if (!(D_800BF870.pad1[0x62] & 2)) {
            a[5] = 1;
        } else if (D_800BF870.pad1[0x273] != 0) {
            a[5] = 2;
        } else {
            a[5] = 3;
        }
        a[7] = 0;
        a[6] = 0;
        a[0x70] = 0xFF;
        break;
    case 1:
        switch (a[6]) {
        case 0:
            if (D_1F800137 == 0 && !(D_800E7FFE & 0x8200)) {
                func_80042354(1, 3);
                func_80040D68(a, D_80148ECC);
                a[0x70] = 2;
                a[6]++;
            }
            break;
        case 1:
            if (a[0x70] == 0xFF) {
                D_800BF870.pad1[0x62] |= 2;
                if (D_800BF870.pad1[0x273] == 0) {
                    func_80042310();
                    a[6] = 0;
                    a[5] = 3;
                } else {
                    func_80040D68(a, D_80148FB4);
                    a[5] = 4;
                    a[6] = 0;
                    a[0x70] = 2;
                }
            }
            break;
        }
        break;
    case 2:
        if (D_1F800137 == 0 && !(D_800E7FFE & 0x8200)) {
            func_80042354(1, 3);
            func_80040D68(a, D_80148FB4);
            a[5] = 4;
            a[6] = 0;
            a[0x70] = 2;
        }
        break;
    case 3:
        switch (a[6]) {
        case 0:
            if (a[0x2B] == 3) {
                func_80042354(1, 3);
                func_80040D68(a, D_800A3D40);
                a[7] = 0;
                a[0x70] = 2;
                a[6]++;
            }
            break;
        case 1:
            if (a[0x70] == 0xFF) {
                switch (a[7]) {
                case 0:
                    if (D_800BF870.pad1[0x62] != 0xFF) {
                        func_80040D68(a, D_80148F74);
                    } else {
                        if (D_800BF870.pad1[0x9A] == 0xFF) {
                            a[0x7A] = 0xE;
                        } else {
                            a[0x7A] = 0xD;
                        }
                        func_80040D68(a, D_80148F84);
                    }
                    a[0x70] = 2;
                    a[7]++;
                    break;
                case 1:
                    a[6] = 0;
                    break;
                }
            }
            break;
        }
        break;
    case 4:
        if (a[0x70] == 0xFF) {
            a[6] = 0;
            a[5] = 3;
        }
        break;
    case 5:
        break;
    }
    func_80041098(a);
    func_8004190C(a);
}

extern u8 D_80141E18[];
void func_80137C9C(u8 *a)
{
    u8 *g;

    switch (a[4]) {
    case 0:
        g = D_800ECF58_742e;
        if (func_800519E0(a, 0xF, *(s32 *)(g + 0x3C), D_80141E18) != 0) {
            break;
        }
        *(s32 *)(a + 0x3C) = *(s32 *)(g + 0x38);
        func_80040CDC(a, D_8014D014, D_800A3D18);
        a[0] = 9;
        *(s16 *)(a + 0x80) = 0x60;
        *(s16 *)(a + 0x82) = 0xC0;
        *(s16 *)(a + 0x84) = 0xC0;
        *(s16 *)(a + 0x86) = 0x160;
        a[0x2A] = 5;
        *(s16 *)(a + 0x56) = 0xDB6;
        *(s16 *)(a + 0x58) = 0;
        *(s16 *)(a + 0x54) = 0;
        a[0x7B] = 0x17;
        a[0xB] = (a[0xB] & 0xC0) | 0x40;
        if (D_800BF8D3 != 0xFF) {
            func_800416A8(a, -1, 0);
            func_80041718(a, 0xB7, 0);
        } else {
            func_80041718(a, 0x17, 0);
        }
        a[4]++;
        break;
    case 1:
        func_801379D4(a);
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

extern u8 D_800BF80E;
s32 func_80137E18(void *arg0) {
    u16 temp_v0;

    if ((D_800BF80E != 0) || (temp_v0 = M2C_FIELD(arg0, u16 *, 0x72), M2C_FIELD(arg0, u16 *, 0x72) = (u16) (temp_v0 - 1), ((temp_v0 << 0x10) <= 0))) {
        return 1;
    }
    return 0;
}

s32 func_80137E54(u8 *p)
{
    u8 *e = D_800E7E80;

    if (*(s16 *)(p + 0x72) == 0) {
        func_800440E4(e, 0xB9, 4);
        D_1F800184 = 2;
    } else {
        D_1F800184 = 0;
    }
    return 1;
}

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80137EA4);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80138000);

extern u8 D_80149298[];
extern u8 D_80149318[];
extern u8 D_80149360[];
extern u8 D_801493A8[];
extern u8 D_801493F0[];
extern u8 D_80149438[];
extern u8 D_80149480[];
extern u8 D_800BF8D0;
extern u8 D_800BF8D1;
extern u8 D_800BFA1B;
static inline s32 anim_r(u8 *p, u8 *t, s32 k) {
    switch (p[6]) {
    case 0:
        if (p[0x2B] == 3) {
            p[6] = 1;
            func_80042354(1, k);
        }
        break;
    case 1:
        p[6] = 2;
        func_80040CDC(p, D_8014D014, t);
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
static inline void anim(u8 *p, u8 *t, s32 k)
{
    switch (p[6]) {
    case 0:
        if (p[0x2B] == 3) {
            p[6] = 1;
            func_80042354(1, k);
        }
        break;
    case 1:
        p[6] = 2;
        func_80040CDC(p, D_8014D014, t);
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
void func_801381A8(u8 *a)
{
    u8 *g;

    switch (a[5]) {
    case 0:
        g = (u8 *)&D_800BF870;
        if (*(u16 *)(g + 0x5E6) & 0x40) {
            a[5] = 7;
        } else if (g[0x65] == 0xFF) {
            a[5] = 6;
        } else if (g[0x61] == 0xFF) {
            a[5] = 5;
        } else if (g[0x61] != 0) {
            a[5] = 4;
        } else if (g[0x60] != 0) {
            a[5] = 3;
        } else if (g[0x1AB] == 1) {
            a[5] = 2;
        } else {
            a[5] = 1;
        }
        break;
    case 1:
        if (D_800BF8D0 != 0) {
            a[5] += 2;
        } else if (anim_r(a, D_80149298, 2) != 0) {
            D_800BFA1B = 1;
            a[5]++;
        }
        break;
    case 2:
        if (D_800BF8D0 != 0) {
            a[5]++;
        } else {
            anim(a, D_80149318, 2);
        }
        break;
    case 3:
        if (D_800BF8D1 != 0) {
            a[5]++;
        } else {
            anim(a, D_80149360, 2);
        }
        break;
    case 4:
        if (D_800BF8D1 == 0xFF) {
            a[5]++;
        } else {
            anim(a, D_801493A8, 2);
        }
        break;
    case 5:
        anim(a, D_801493F0, 1);
        break;
    case 6:
        anim(a, D_80149438, 1);
        break;
    case 7:
        anim(a, D_80149480, 1);
        break;
    }
}

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80138578);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_801388CC);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80138B30);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80138C68);

typedef struct { u8 pad[0x6C]; s16 h6C, h6E, h70; } Cam8008;
extern Cam8008 D_800E8008_7f9d;
extern u8 D_801494D8[];
extern u8 D_80149570[];
extern u8 D_801495C8[];
extern u8 D_801495E8[];
void func_80139088(u8 *a)
{
    s16 x;

    switch (a[6]) {
    case 0:
        a[6]++;
        func_80041768(a, 8, 0);
        break;
    case 1:
        if (D_800BF89E & 0x200) {
            a[6] = 4;
            break;
        }
        if (D_800BF80F == 0) {
            a[6]++;
            func_80042354(1, 2);
            func_80040CDC(a, D_8014D014, D_801494D8);
            a[0x70] = 1;
            a[0x47] = 0;
            func_8006E1C0(1);
            func_8006CBA8(a + 0x2C);
            D_800E8008_7f9d.h6E = 0x80;
            D_800E8008_7f9d.h70 = 0x200;
            D_800E8008_7f9d.h6C = D_801003F8 * 5;
            *(s16 *)(a + 0x5C) = 0;
        }
        break;
    case 2:
        func_80041098(a);
        if (a[0x70] == 0xFF) {
            a[6]++;
            x = D_1F800160_71b4;
            if (x > 0x2738) {
                func_80040CDC(a, D_8014D014, D_801495C8);
            } else if (x < 0x25A8) {
                func_80040CDC(a, D_8014D014, D_801495E8);
            } else {
                func_80040CDC(a, D_8014D014, D_80149570);
            }
            a[0x70] = 1;
        }
        break;
    case 3:
        func_80041098(a);
        if (a[0x70] == 0xFF) {
            a[6] = 0;
            a[5]++;
            func_80042310();
            D_800BF870.pad1[0x1AC] |= 2;
            func_8006E1E4();
        }
        break;
    case 4:
        if (!(D_800BF89E & 0x200)) {
            a[6]++;
        }
        break;
    case 5:
        if (func_8005308C() != 0) {
            a[6] = 2;
            func_80042354(1, 2);
            func_80040CDC(a, D_8014D014, D_801494D8);
            a[0x70] = 1;
            a[0x47] = 0;
            func_8006E1C0(1);
            func_8006CBA8(a + 0x2C);
            D_800E8008_7f9d.h6E = 0x80;
            D_800E8008_7f9d.h70 = 0x200;
            D_800E8008_7f9d.h6C = D_801003F8 * 5;
            *(s16 *)(a + 0x5C) = 0;
        }
        break;
    }
}

extern u8 D_80149608[];
extern u8 D_80149658[];
extern u8 D_80149688[];
extern u8 D_801496B8[];
void func_801392D8(u8 *a)
{
    switch (a[6]) {
    case 0:
        a[6]++;
        func_80040CDC(a, D_8014D014, D_80149608);
        a[0x70] = 1;
        a[0x47] = 0;
        a[0] = 2;
        break;
    case 1:
        func_80041098(a);
        if (a[0x70] == 0xFF) {
            *(u16 *)(a + 0x40) = 0xB4;
            a[0] = 9;
            a[6]++;
        }
        break;
    case 2:
        if (func_80041438(a, 0xC00, 0x80) != 0) {
            a[6]++;
            func_80041768(a, 8, 0);
        }
        break;
    case 3:
        if (--*(s16 *)(a + 0x40) == -1) {
            a[6] = 0;
        } else if (a[0x2B] == 3) {
            a[6]++;
            if (D_800BF870.pad1[0x64] == 0xFF) {
                func_80040CDC(a, D_8014D014, D_801496B8);
                func_80042354(1, 1);
            } else if (D_800BF870.pad1[0x61] == 0xFF) {
                func_80040CDC(a, D_8014D014, D_80149688);
                func_80042354(1, 1);
            } else {
                func_80040CDC(a, D_8014D014, D_80149658);
                func_80042354(1, 2);
            }
            a[0x70] = 1;
        }
        break;
    case 4:
        func_80041098(a);
        if (a[0x70] == 0xFF) {
            a[6] = 0;
            func_80042310();
        }
        break;
    }
}

INCLUDE_ASM("asm/a06/nonmatchings/a06", f_RunRockCrabBalanceCameraSequence);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80139728);

extern u8 D_800BFAE5;
extern u8 D_80149990[];
extern u8 D_80149F38[];
extern u8 D_80149F58[];
s32 func_801398E4(u8 *a)
{
    switch (a[7]) {
    case 0:
        a[7] = 1;
        func_80040CDC(a, D_8014D014, D_80149F38);
        a[0x70] = 1;
        break;
    case 1:
        func_80041098(a);
        if (a[0x70] == 0xFF) {
            a[7]++;
            func_80040CDC(a, D_8014D014, D_80149990);
            a[0x70] = 1;
        }
        break;
    case 2:
        func_80041098(a);
        if (a[0x70] == 0xFF) {
            if (D_800BFAE5 == 0) {
                a[7]++;
                func_80040CDC(a, D_8014D014, D_80149F58);
                a[0x70] = 1;
            } else {
                a[7] = 0;
                return 3;
            }
        }
        break;
    case 3:
        func_80041098(a);
        if (a[0x70] == 0xFF) {
            a[7] = 0;
            return 2;
        }
        break;
    }
    return 0;
}

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80139A28);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80139C84);

extern u8 D_800BFB29;
extern u8 D_8014A000[];
extern u8 D_80149FC8[];
extern u8 D_8014A0A8[];
s32 func_80139F58(u8 *a)
{
    switch (a[7]) {
    case 0:
        a[7] = 1;
        func_80040CDC(a, D_8014D014, D_80149FC8);
        a[0x70] = 1;
        break;
    case 1:
        func_80041098(a);
        if (a[0x70] == 0xFF) {
            a[7]++;
            func_80040CDC(a, D_8014D014, D_8014A000);
            a[0x70] = 1;
        }
        break;
    case 2:
        func_80041098(a);
        if (a[0x70] == 0xFF) {
            if (D_800BFB29 == 0) {
                a[7]++;
                func_80040CDC(a, D_8014D014, D_8014A0A8);
                a[0x70] = 1;
            } else {
                a[7] = 0;
                return 3;
            }
        }
        break;
    case 3:
        func_80041098(a);
        if (a[0x70] == 0xFF) {
            a[7] = 0;
            return 2;
        }
        break;
    }
    return 0;
}

extern u8 D_800BFA21;
extern u8 D_800BFB03;
extern u8 D_8014A0D8[];
extern u8 D_8014A160[];
extern u8 D_8014A180[];
extern u8 D_8014A2A0[];
s32 func_8013A09C(u8 *a)
{
    switch (a[7]) {
    case 0:
        a[7]++;
        func_80040CDC(a, D_8014D014, D_80149FC8);
        a[0x70] = 1;
        break;
    case 1:
        func_80041098(a);
        if (a[0x70] == 0xFF) {
            a[7]++;
            func_80040CDC(a, D_8014D014, D_8014A0D8);
            a[0x70] = 1;
        }
        break;
    case 2:
        func_80041098(a);
        if (a[0x70] == 0xFF) {
            if (D_800BFA21 < 0x14) {
                a[7]++;
                func_80040CDC(a, D_8014D014, D_8014A160);
                a[0x70] = 1;
            } else {
                a[7] += 2;
                func_80040CDC(a, D_8014D014, D_8014A180);
                a[0x70] = 1;
            }
        }
        break;
    case 3:
        func_80041098(a);
        if (a[0x70] == 0xFF) {
            a[7] = 0;
            return 1;
        }
        break;
    case 4:
        func_80041098(a);
        if (a[0x70] == 0xFF) {
            if (D_800BFB03 == 0) {
                a[7]++;
                func_80040CDC(a, D_8014D014, D_8014A2A0);
                a[0x70] = 1;
            } else {
                a[7] = 0;
                return 3;
            }
        }
        break;
    case 5:
        func_80041098(a);
        if (a[0x70] == 0xFF) {
            a[7] = 0;
            return 2;
        }
        break;
    }
    return 0;
}

s32 func_8013A250(u8 *a)
{
    switch (a[7]) {
    case 0:
        a[7]++;
        func_80040CDC(a, D_8014D014, D_8014A0D8);
        a[0x70] = 1;
        break;
    case 1:
        func_80041098(a);
        if (a[0x70] == 0xFF) {
            if (D_800BFA21 < 0x14) {
                a[7]++;
                func_80040CDC(a, D_8014D014, D_8014A160);
                a[0x70] = 1;
            } else {
                a[7] += 2;
                func_80040CDC(a, D_8014D014, D_8014A180);
                a[0x70] = 1;
            }
        }
        break;
    case 2:
        func_80041098(a);
        if (a[0x70] == 0xFF) {
            a[7] = 0;
            return 1;
        }
        break;
    case 3:
        func_80041098(a);
        if (a[0x70] == 0xFF) {
            if (D_800BFB03 == 0) {
                a[7]++;
                func_80040CDC(a, D_8014D014, D_8014A2A0);
                a[0x70] = 1;
            } else {
                a[7] = 0;
                return 3;
            }
        }
        break;
    case 4:
        func_80041098(a);
        if (a[0x70] == 0xFF) {
            a[7] = 0;
            return 2;
        }
        break;
    }
    return 0;
}

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8013A3D0);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8013A598);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8013A81C);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8013AA14);

s32 func_8013AE18(void) {
    func_8006E1E4();
    return 1;
}

s32 func_8013AE38(void *a0)
{
    S13AE38 v;
    u8 *e;

    v.a = 0x2738;
    e = D_800E7E80;
    v.b = *(s16 *)(e + 0x32) - 0xC8;
    v.c = *(s16 *)(e + 0x36);
    func_80070F00(a0, 1, &v);
    func_800708B4(3);
    return 1;
}

s32 func_8013AE88(void *a0)
{
    S13AE38 v;
    u8 *e;

    v.a = 0x25A8;
    e = D_800E7E80;
    v.b = *(s16 *)(e + 0x32) - 0xC8;
    v.c = *(s16 *)(e + 0x36);
    func_80070F00(a0, 1, &v);
    func_800708B4(3);
    return 1;
}

s32 func_8013AED8(void) {
    return M2C_FIELD(*(void **)0x1F800214, u8 *, 3) == 0;
}

void func_8012E194();
s32 func_8013AEF0(void *a0)
{
    u8 *r = func_80072DDC(a0, 3, 3, 0x3F);

    if (r) {
        *(void **)(r + 0x1C) = func_8012E194;
        r[3] = 2;
        r[0x28] |= 0x80;
        if (D_800BF8D5 != 0xFF) {
            func_8004D604(0x31, 1);
        }
        return 1;
    }
    return 0;
}

s32 func_8013AF68(u8 *p)
{
    s8 **t;

    func_8007ADDC(p);
    t = D_800ECF58;
    func_800519E0(p, 0xD, (s32)t[0x3C / 4], D_80142028);
    *(s32 *)(p + 0x3C) = (s32)t[0x80 / 4];
    *(void **)(p + 0x7C) = D_8014D798;
    func_80077C40(p, D_8014D798, 0);
    return 1;
}

s32 func_8013AFD8(u8 *a)
{
    HV v;
    u8 *g = D_1F800214;

    switch (a[0x78]) {
    default:
        return 0;
    case 0:
        v.x = 0x34E8;
        v.y = -0x1E46;
        v.z = 0x7530;
        func_80070F00(a, 1, &v);
        func_800708B4(3);
        a[0x78]++;
        break;
    case 1:
        if (g[3] == 0) {
            return 1;
        }
        break;
    }
    return 0;
}

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8013B074);

s32 func_8013B0F8(u8 *a0)
{
    u8 *c = D_800E8008;

    c[0x64] = 2;
    *(s16 *)(c + 0x6E) = 0x200;
    *(s16 *)(c + 0x70) = -0x400;
    *(s16 *)(c + 0x6C) = D_801003F8 * 4;
    func_8006CBA8(a0 + 0x2C);
    return 1;
}

extern M2C_UNK D_800E7EAC;
extern s8 D_800E806C;
s32 func_8013B148(void) {
    D_800E806C = 8;
    func_8006CBA8(&D_800E7EAC);
    return 1;
}

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8013B178);

s32 func_8013B24C(void *arg0) {
    func_80051B04(M2C_FIELD(arg0, s32 *, 0xD0), 0xF, 0xD);
    return 1;
}

s32 func_8013B274(void *arg0) {
    func_80051B04(M2C_FIELD(arg0, s32 *, 0xD0), 0xF, 4);
    return 1;
}

#define gte_ldfcdir(r0, r1, r2) __asm__ volatile("ctc2	%0, $21;" "ctc2	%1, $22;" "ctc2	%2, $23" : : "r"(r0), "r"(r1), "r"(r2))
extern u8 D_800BE0E4;
extern s32 D_1F800090_81f3[];
extern u8 D_800A1CD4[];
extern u8 D_8014C39C[];
s32 func_8013B29C(u8 *p)
{
    switch (p[0x78]) {
    case 0:
        p[0x78]++;
        *(s16 *)(p + 0x40) = 0x3C;
    case 1:
        if (--*(s16 *)(p + 0x40) == -1 || !(D_800BE0E4 & 0x80)) {
            return 1;
        }
    }
    return 0;
}

s32 func_8013B30C(void *arg0) {
    u8 temp_s1;

    temp_s1 = D_800BF870.pad1[0x2B8];
    func_8004D688(0x75, temp_s1);
    D_800BF870.pad1[0x1B0] += temp_s1;
    M2C_FIELD(arg0, s8 *, 0xBF) = 0;
    M2C_FIELD(arg0, u8 *, 0x5F) = temp_s1;
    func_80141020(0, 0, arg0);
    return 1;
}

s32 func_8013B37C(void *arg0) {
    M2C_FIELD(arg0, s8 *, 0xBF) = 1;
    return 1;
}

extern u16 D_800BFE56;
extern u8 D_8014CA58[];
s32 func_8013B38C(void *a0)
{
    u8 *r = func_80072DDC(a0, 2, 3, 0x10);

    if (r) {
        *(void **)(r + 0x1C) = f_UpdateDonglinInteriorQuestObjectActor;
        r[3] = 0xC;
    }
    return 1;
}

extern s8 D_800BFA20_0787;
s32 func_8013B3D0(void) {
    func_8004D688(0x4F, 1);
    D_800BFA20_0787 = 7;
    return 1;
}

extern s8 D_800BFA20_0787;
s32 func_8013B400(void) {
    func_8004D4C4(0x50, 1);
    func_8004B2E8();
    D_800BFA20_0787 = 0xA;
    return 1;
}

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8013B438);

void func_8013B438();
s32 func_8013B668(u8 *a) {
    u8 *g = (u8 *)&D_800BF870;
    u8 *e;

    if (g[0xC6] & 0x10) {
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
    M2C_FIELD(e, void **, 0x1C) = func_8013B438;
    M2C_FIELD(e, s16 *, 0x2E) = M2C_FIELD(a, s16 *, 0x2E);
    M2C_FIELD(e, s16 *, 0x32) = M2C_FIELD(a, s16 *, 0x32);
    M2C_FIELD(e, s16 *, 0x36) = M2C_FIELD(a, s16 *, 0x36);
    e[0x2A] = a[0x2A];
    g[0x164] = 1;
    func_8003116C(0x30, e + 0x2C, -0xA);
    func_80074590(0x37, 0x20, 0);
    return 1;
}

s32 func_8013B738(u8 *a, u8 *b, s32 f)
{
    s16 dx, dz, dy;
    s32 d;

    f &= 1;
    dx = *(s16 *)(b + 2) - *(s16 *)(a + 0x2E);
    dz = *(s16 *)(b + 0xA) - *(s16 *)(a + 0x36);
    if (f) {
        dy = *(s16 *)(b + 6) - *(s16 *)(a + 0x32);
    } else {
        dy = 0;
    }
    d = func_80084080(dx * dx + dz * dz + dy * dy);
    if (d >= 0x800) {
        return 8;
    }
    return d >> 8;
}

void func_8013B7DC(u8 *p)
{
    u16 cz = D_1F800164;
    u16 cx = D_1F800160;
    s16 dz = cz - *(u16 *)(p + 0x36);
    s16 dx = cx - *(u16 *)(p + 0x2E);
    s32 a = func_80085690(-dz, dx);

    func_80077768(a & 0xFFF, *(s16 *)(p + 0x60), 0);
}

s32 func_8013B844(u8 *a, u8 *b)
{
    s16 dx = *(s16 *)(b + 2) - *(s16 *)(a + 0x2E);
    s16 dy = *(s16 *)(b + 6) - *(s16 *)(a + 0x32);
    s16 dz = *(s16 *)(b + 0xA) - *(s16 *)(a + 0x36);
    s32 c = func_80083F50(-*(s16 *)(a + 0x60));
    return func_80085690(dy, (c * dx + func_80083E80(-*(s16 *)(a + 0x60)) * dz) >> 12) & 0xFFF;
}

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8013B8F4);

s32 func_8013B9C0(u8 *a, u8 *b)
{
    s16 dx = *(s16 *)(b + 2) - *(s16 *)(a + 0x2E);
    s16 dy = *(s16 *)(b + 6) - *(s16 *)(a + 0x32);
    s16 dz = *(s16 *)(b + 0xA) - *(s16 *)(a + 0x36);
    return func_80084080(dx * dx + dy * dy + dz * dz);
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
extern void *D_800BF544_ff0c;
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
extern void *D_800BF544_ff0c;
#define T2_rtpt() __asm__ volatile(".word 0x4A280030")
#define T2_nclip() __asm__ volatile(".word 0x4B400006")
#define T2_stflg(r0) __asm__ volatile("cfc2 $12, $31;" "nop;" "sw $12, 0( %0 )" : : "r"(r0) : "$12", "memory")
#define T2_stopz(r0) __asm__ volatile("swc2 $24, 0( %0 )" : : "r"(r0) : "memory")
#define T2_stotz(r0) __asm__ volatile("swc2 $7, 0( %0 )" : : "r"(r0) : "memory")
#define T2_stsz1(r0) __asm__ volatile("swc2 $17, 0( %0 )" : : "r"(r0) : "memory")
#define T2_stsz2(r0) __asm__ volatile("swc2 $18, 0( %0 )" : : "r"(r0) : "memory")
#define T2_stsz3(r0) __asm__ volatile("swc2 $19, 0( %0 )" : : "r"(r0) : "memory")
extern void *D_800BF544_ff0c;
u32 *func_8013BA44(u32 *f, u32 *ot, s32 n)
{
    s32 sz[6];
    s32 *otz = (s32 *)0x1F800004;
    T2PolyGT3 *p = D_800BF544_ff0c;
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
                    if ((mode & 4) && D_1F80009C != 0) {
                        goto next;
                    }
                    switch (mode & 3) {
                    case 1:
                    case 3:
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
    next:
        f += 9;
    }
    D_800BF544_ff0c = p;
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
u32 *func_8013BD40(u32 *f, u32 *ot, s32 n)
{
    s32 sz[8];
    s32 *otz = (s32 *)0x1F800004;
    T2PolyGT4 *p = D_800BF544_ff0c;
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
                        if ((mode & 4) && D_1F80009C != 0) {
                            goto next;
                        }
                        switch (mode & 3) {
                        case 1:
                        case 3:
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
    next:
        f += 11;
    }
    D_800BF544_ff0c = p;
    return f;
}

extern s32 D_1F80008C_f832;
extern s16 D_1F800162;
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
extern s32 D_1F800084_8c7c;
#define T2_lddp(r0) __asm__ volatile("mtc2 %0, $8" : : "r"(r0))
#define T2_ldrgb(r0) __asm__ volatile("mtc2 %0, $6" : : "r"(r0))
#define T2_dpcs() __asm__ volatile("nop; nop; .word 0x4A780010")
#define T2_strgb(r0) __asm__ volatile("swc2 $22, 0( %0 )" : : "r"(r0) : "memory")
u32 *func_8013C0D8(u32 *f, u32 *ot, s32 n, s32 dp)
{
    s32 rgb;
    T2PolyGT3 *p = D_800BF544_ff0c;
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
                    T2_stsz1(&D_1F800084_8c7c);
                    T2_stsz2(&D_1F800088);
                    T2_stsz3(&D_1F80008C_f832);
                    mode = c >> 24;
                    if ((mode & 4) && D_1F80009C != 0) {
                        goto next;
                    }
                    switch (mode & 3) {
                    case 1:
                    case 3:
                        if (D_1F800084_8c7c > D_1F800088) {
                            b = D_1F80008C_f832;
                            if (b < D_1F800084_8c7c) {
                                b = D_1F800084_8c7c;
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
                        if (D_1F800084_8c7c < D_1F800088) {
                            b = D_1F80008C_f832;
                            if (D_1F800084_8c7c < b) {
                                b = D_1F800084_8c7c;
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
                            d0 = func_80078240(((s16 *)f)[8] - D_1F800160_71b4, ((s16 *)f)[9] - D_1F800162, ((s16 *)f)[10] - D_1F800164_d75f) * 2;
                            d1 = func_80078240(((s16 *)f)[12] - D_1F800160_71b4, ((s16 *)f)[13] - D_1F800162, ((s16 *)f)[11] - D_1F800164_d75f) * 2;
                            d2 = func_80078240(((s16 *)f)[14] - D_1F800160_71b4, ((s16 *)f)[15] - D_1F800162, ((s16 *)f)[16] - D_1F800164_d75f) * 2;
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
    next:
        f += 9;
    }
    D_800BF544_ff0c = p;
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
extern s32 D_1F800090;
u32 *func_8013C5B4(u32 *f, u32 *ot, s32 n, s32 dp)
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
                        if ((mode & 4) && D_1F80009C != 0) {
                            goto next;
                        }
                        T2_stsz0(&D_1F800084_8c7c);
                        T2_stsz1(&D_1F800088);
                        T2_stsz2(&D_1F80008C_f832);
                        T2_stsz3(&D_1F800090);
                        switch (mode & 3) {
                        case 1:
                        case 3:
                            a = D_1F800088;
                            if (a < D_1F800084_8c7c) {
                                a = D_1F800084_8c7c;
                            }
                            b = D_1F800090;
                            if (b < D_1F80008C_f832) {
                                b = D_1F80008C_f832;
                            }
                            if (b < a) {
                                b = a;
                            }
                            *otz = b >> 2;
                            break;
                        case 2:
                            a = D_1F800088;
                            if (D_1F800084_8c7c < a) {
                                a = D_1F800084_8c7c;
                            }
                            b = D_1F800090;
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
void func_8013CBA0(RECT16 *a) {
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

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8013CD34);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8013CF00);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8013D1E4);

extern s16 *D_1F80028C;
void func_8013D568(u32 *a0, void *a1)
{
    u32 *s1;
    s32 s0;
    u32 w;
    s16 *o;

    s1 = a0;
    a0 += 4;

    if (D_800BF873) {
        o = (s16 *)D_1F80028C;
        { s32 x = o[0x17]; s32 y = o[0x19]; s32 z = o[0x1B]; s0 = func_80078240(x - D_1F800160_71b4, y - D_1F800162, z - D_1F800164_d75f) << 1; }
        gte_ldfcdir(0, 0, 0);
        w = *s1;
        func_8013C5B4(func_8013C0D8(a0, a1, w & 0xFFFF, s0), a1, w >> 16, s0);
    } else {
        w = *s1;
        func_8013D1E4(func_8013CF00(a0, a1, w & 0xFFFF), a1, w >> 16);
    }
}

typedef struct {
    u8 x[8];
} S8;
extern S8 D_8014A428[];
void func_8013D668(void)
{
    u32 i;

    if (D_800BF873) {
        for (i = 0; i < 5; i++) {
            func_8013CBA0(&D_8014A428[i]);
        }
    }
}

extern u16 D_8014A450;
void func_8013D6BC(s32 arg0) {
    D_8014A450 = (D_8014A450 + arg0) & 0xFF;
}

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8013D6D8);

#define GH(p, o) (*(s16 *)((u8 *)(p) + (o)))
typedef struct { u8 pad[0x10]; u16 cells[1]; } A00CellList;
static inline void tri_span(u8 *a, s32 y, s32 l, s32 r) {
    s32 x;
    s16 *p;
    s32 off;

    if (y >= 0 && y < GH(a, 0xA)) {
        if (r >= GH(a, 8)) r = GH(a, 8) - 1;
        x = l;
        if (x < 0) x = 0;
        p = (s16 *)D_800ECF58[8];
        p += 2;
        off = x * GH(a, 0xA) + y;
        while (p += off, x <= r) {
            if (*p != -1 && (s16)func_8013E090(x, y) != 0) {
                u8 n = a[6];
                if (n < 0xFE) {
                    a[6] = n + 1;
                    ((A00CellList *)a)->cells[n] = *p;
                }
            }
            off = GH(a, 0xA);
            x++;
        }
    }
}
void func_8013DA8C(u8 *a, s32 *p0, s32 *p1, s32 *p2) {
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
        for (y = y0; y < y1; y++) { tri_span(a, y, xl >> 16, xr >> 16); xl += sl1; xr += sl3; }
        for (; y <= y2; y++) { tri_span(a, y, xl >> 16, xr >> 16); xl += sl2; xr += sl3; }
    } else {
        for (y = y0; y < y1; y++) { tri_span(a, y, xl >> 16, xr >> 16); xr += sl1; xl += sl3; }
        for (; y <= y2; y++) { tri_span(a, y, xl >> 16, xr >> 16); xl += sl3; xr += sl2; }
    }
}

u32 func_8013E090(s32 x, u32 y)
{
    u32 v;

    if (y >= 0x34 || x < 0 || x >= 0x34) {
        v = 0;
    } else {
        v = D_8014CE6C_28ce[y * 0x34 + x];
    }
    return v & (D_8014CE68 << 4);
}

s32 func_8013E0F4(s32 x, u32 y)
{
    if (y >= 0x34 || x < 0 || x >= 0x34) {
        return 0;
    }
    return D_8014CE6C_28ce[y * 0x34 + x];
}

extern s8 *D_8014CE6C;
void func_8013E144(u8 *a)
{
    s8 **t = D_800ECF58;
    u16 *p = (u16 *)t[8];
    u16 v;

    *(u16 **)(a + 0xC) = p;
    *(u16 *)(a + 8) = p[0];
    v = p[1];
    a[7] = 0;
    *(u16 *)(a + 0xA) = v;
    D_8014CE6C = t[9];
}

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8013E180);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8013E30C);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8013E5D8);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8013E738);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8013EC14);

extern u8 D_800A0B38[];
extern u8 D_8014C828[];
extern u8 D_8014C85C[];
void func_8013EDC0(u8 *a)
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
        *(u8 **)(a + 0x3C) = D_8014C828 + s[4] * 4;
        a[0x29] = D_8014C85C[s[4]];
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

typedef struct { u8 a, b, c, d; } Ent;
extern u8 *D_800ECF88;
void func_8013EF60(u8 *a)
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
            e[i].b = func_8009A450() | 0x20;
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
        a[7] = 0x14;
        *(s16 *)(a + 0x48) = func_8009A450();
        *(s16 *)(a + 0x4A) = func_8009A450();
        *(s16 *)(a + 0x4C) = func_8009A450();
        b = D_800ECF88;
        h = (s32 *)(b + 4);
        *(u8 **)(a + 0x3C) = b + h[0x56];
        *(u8 **)(a + 0x38) = b + h[0x57];
        *(u8 **)(a + 0x34) = b + h[0x58];
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

#define W(p, o) (*(s32 *)((u8 *)(p) + (o)))
typedef struct {
    u8 b[4];
} T2Bytes4;
typedef struct {
    s16 x, y, z;
} T2Vec3s;
extern T2Bytes4 D_8010A460;
extern s32 D_800ED8C8;
void func_8013F14C(u8 *a)
{
    T2Bytes4 c;
    T2Vec3s pos, rot;
    s32 i = 0;
    u8 *e = a + 0x50;
    s32 ang;
    s32 r, sx, sz, k, o;

    c = D_8010A460;
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
            func_8003F698(W(a, 0x3C), D_800ED8C8, 0);
        } else if (k == 1) {
            func_8003F698(W(a, 0x34), D_800ED8C8, 0);
        } else {
            func_8003F698(W(a, 0x38), D_800ED8C8, 0);
        }
        i++;
        ang += 0x124;
    } while (i < 14);
}

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8013F320);

void func_8013F51C(u8 *a)
{
    s16 *q = (s16 *)(a + 0x50);

    switch (a[4]) {
    case 0:
        a[0x29] = 0;
        *(s32 *)(a + 0x48) = 0;
        *(s32 *)(a + 0x4C) = 0;
        *(s32 *)(a + 4) = 1;
        break;
    case 1:
        switch (a[5]) {
        case 0:
            *(s16 *)(a + 0x50) = 0x1000;
            q[1] = 0;
            q[2] = 0;
            a[5] = 1;
            break;
        case 1:
            if (*(s16 *)(a + 0x50) > 0) {
                *(s16 *)(a + 0x50) -= 0x199;
            }
            if (q[2] >= 0x80) {
                a[5] = 2;
            }
            break;
        case 2:
            if (*(s16 *)(a + 0x50) < 0x1000) {
                *(s16 *)(a + 0x50) += 0x199;
            } else {
                a[4] = 2;
            }
            break;
        }
        q[2] += 6;
        *(s16 *)(a + 0x4A) += 0x22;
        func_8002B278(a);
        break;
    case 2:
    case 3:
        func_8007A624(a);
        break;
    }
}

#define W(p, o) M2C_FIELD(p, u32 *, o)
extern FlickerTbl D_8010A468;
void func_8013F658(u8 *a) {
    FlickerTbl t = D_8010A468;

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

#define U32(p, o) M2C_FIELD(p, u32 *, o)
void func_8013F878(u8 *a) {
    u32 v;

    switch (a[4]) {
    case 0:
        U32(a, 0x50) = 0x303030;
        a[1] = 1;
        U32(a, 0x58) = 0x1000;
        U32(a, 0x5C) = 0;
        U32(a, 0x48) = 0;
        U32(a, 0x4C) = 0;
        a[4] = 1;
        a[5] = 0;
    case 1:
        a[1] = 1;
        {s32 c = a[5]; if (c == 0) {
            if (U32(a, 0x58) != 0) {
                U32(a, 0x58) -= 0x100;
            } else {
                a[5] = c + 1;
            }
        }}
        goto common;
    case 2:
        v = U32(a, 0x58);
        a[1] = 1;
        if (v <= 0x1000) {
            U32(a, 0x58) = v + 0x111;
        } else {
            a[4] = 3;
        }
    common:
        if (D_1F80017C_0fe7 & 1) {
            if ((U32(a, 0x5C) += 0x20) >= 0xC0) {
                U32(a, 0x5C) = 0;
            }
        }
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8013F99C);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8013FAE4);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8013FBD0);

extern RingVec D_8014CE70[];
void func_8013FCF0(void) {
    s32 i;
    s32 ang;
    RingVec *p;

    p = D_8014CE70;
    for (i = 0; i < 15; i++, p++) {
        ang = (i << 12) / 15;
        p->x = func_80083F50(ang) >> 4;
        p->y = 0;
        p->z = func_80083E80(ang) >> 4;
    }
    p->x = D_8014CE70[0].x;
    p->y = D_8014CE70[0].y;
    p->z = D_8014CE70[0].z;
}

void func_8013FDC0(u8 *a) {
    RiseMotion *m = (RiseMotion *)(a + 0x50);

    switch (a[4]) {
    case 0:
        m->pos = 20;
        a[4] = 1;
        m->vel = 10;
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

typedef struct { s32 a, b; } Pair9F44;
typedef struct { Pair9F44 e[14]; } Tbl9F44;
extern Tbl9F44 D_8010A3F0;
void func_8013FE78(u8 *a)
{
    Tbl9F44 t = D_8010A3F0;

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

void func_8013FFAC(u8 *p) {
    s32 *d = D_1F800090_81f3;
    s32 i;

    gte_ldfcdir(0, 0, 0);
    *d = 0;
    for (i = 0; i < 4; i++) {
        func_80031AC4(p + 0x2C, p + 0x50, p + 0x48);
        func_80027768(M2C_FIELD(p, s32 *, 0x3C), 0, M2C_FIELD(p, s16 *, 0x32), 0);
        M2C_FIELD(p, s16 *, 0x4E) += 0x400;
    }
}

void func_80140038(u8 *a)
{
    u8 buf[0x30];
    void *m;
    s32 y;

    func_800318A0(a + 0x2C, a + 0x50, a + 0x48);
    m = *(void **)(a + 0x3C);
    y = *(s16 *)(a + 0x32);
    D_1F800090 = *(s32 *)(a + 0x54);
    func_80027768(m, 0, y, a[0x29]);
}

#define AREA_gte_ldv0(r0) __asm__ volatile("lwc2	$0, 0( %0 );" "lwc2	$1, 4( %0 )" : : "r"(r0))
extern u8 D_8014A5E8[];
extern s32 D_8014A5E4;
void func_80140088(u8 *a) {
    AreaSVec v;
    u8 *p;
    s32 r, k;

    p = M2C_FIELD(a, u8 **, 0x78);
    if (p == NULL) {
        p = D_8014A5E8;
    }
    func_800329E0(6);
    v.x = M2C_FIELD(a, s16 *, 0x2E);
    v.y = M2C_FIELD(a, s16 *, 0x32);
    v.z = M2C_FIELD(a, s16 *, 0x36);
    AREA_gte_ldv0(&v);
    if (func_800317CC(-10) == 0) {
        D_1F800088 = D_1F800084_8c7c;
        r = func_8009A450();
        k = D_8014A5E4;
        r &= 0x7FF;
        D_1F800090 = r;
        M2C_FIELD(a, u8 **, 0x78) = func_80027A4C(p, k);
    }
}

typedef struct { s8 x, y, z; } Byte3;
extern Byte3 D_8010A464;
extern u8 D_8014C42C[];
void func_8014013C(u8 *a)
{
    s32 *d = D_1F800090_81f3;
    u8 *s = a + 0x50;
    Byte3 c;

    c = D_8010A464;
    gte_ldfcdir(0, 0, 0);
    {
        s32 v = *(s16 *)(a + 0x50);
        u8 y = *(u16 *)(s + 4) >> 3;

        *d = v;
        c.y = y;
    }
    func_80031D24(a + 0x2C, &c, a + 0x48);
    func_80027768(D_8014C42C, 0, -0x1E, *(s16 *)(s + 2));
}

extern u8 D_8014C6FC[];
void func_801401D8(u8 *a) {
    s32 *d;
    s32 t;

    d = &D_1F800090;
    gte_ldfcdir(0, 0, 0);
    t = M2C_FIELD(a, u16 *, 0x4A) + 0x400;
    *d = M2C_FIELD(a, s32 *, 0x58);
    M2C_FIELD(a, s16 *, 0x4A) = t;
    func_800318A0(a + 0x2C, a + 0x50, a + 0x48);
    M2C_FIELD(a, s16 *, 0x4A) -= 0x400;
    func_80027768(D_8014C6FC, 0, -0x14, M2C_FIELD(a, s32 *, 0x5C));
    func_800318A0(a + 0x2C, a + 0x50, a + 0x48);
    func_80027768(D_8014C6FC, 0, -0x14, M2C_FIELD(a, s32 *, 0x5C));
}

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_801402B0);

void func_80140380(u8 *a) {
    switch (a[4]) {
    case 0:
        a[4] = 1;
        M2C_FIELD(a, s32 *, 0x50) = 0;
        M2C_FIELD(a, s16 *, 0x4E) = 0;
        M2C_FIELD(a, s16 *, 0x32) = -50;
    case 1:
        if (D_1F80017C_0fe7 & 1) {
            if (++M2C_FIELD(a, s16 *, 0x4E) == 25) {
                D_800BF918 = 2;
                a[4] = 2;
            }
        }
        a[1] = 1;
        break;
    case 2:
        M2C_FIELD(a, u32 *, 0x50) += 0xCC;
        if (M2C_FIELD(a, u32 *, 0x50) >= 0x1000) {
            a[4] = 3;
        }
        a[1] = 1;
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

void func_8014046C(u8 *p)
{
    s32 *d = D_1F800090_81f3;

    gte_ldfcdir(0, 0, 0);
    *d = *(s32 *)(p + 0x50);
    func_800318A0(p + 0x2C, D_800A1CD4, p + 0x48);
    func_80027768(D_8014C39C, *(s16 *)(p + 0x4E), *(s16 *)(p + 0x32), 0);
}

typedef struct { u16 a, b; } Range;
extern Range D_8014CA60[];
extern Range D_8014CA78[];
extern Range D_8014CA8C[];
extern Range D_8014CB10[];
extern Range D_8014CB20[];
extern Range D_8014CB34[];
extern Range D_8014CB64[];
extern Range D_8014CBA4[];
extern Range D_8014CBF4[];
extern Range D_8014CC7C[];
extern Range D_8014CCD4[];
extern Range D_8014CCEC[];
extern Range D_8014CD0C[];
extern Range D_8014CD34[];
extern Range D_8014CD70[];
extern Range D_8014CDA4[];
extern u8 *D_1F80021C;
void func_801404DC(s16 kind, s16 idx)
{
    Range *t;
    s32 n, base;
    u8 *p;
    switch (kind) {
    case 0:
        t = D_8014CA60;
        n = 0x3;
        base = 0;
        break;
    case 1:
        t = D_8014CA78;
        n = 0x16;
        base = 0x4A7;
        break;
    case 2:
        t = D_8014CA8C;
        n = 0xD;
        base = 0;
        break;
    case 3:
        t = D_8014CB10;
        n = 0x1C;
        base = 0x1AC;
        break;
    case 4:
        t = D_8014CB20;
        n = 0xD;
        base = 0x24C;
        break;
    case 5:
        t = D_8014CB34;
        n = 0x1D;
        base = 0x26A;
        break;
    case 6:
        t = D_8014CB64;
        n = 0x6;
        base = 0x334;
        break;
    case 7:
        t = D_8014CBA4;
        n = 0x13;
        base = 0x399;
        break;
    case 8:
        t = D_8014CBF4;
        n = 0x14;
        base = 0x313;
        break;
    case 9:
        t = D_8014CC7C;
        n = 0x12;
        base = 0;
        break;
    case 10:
        t = D_8014CCD4;
        n = 0x12;
        base = 0x227;
        break;
    case 11:
        t = D_8014CCEC;
        n = 0xE;
        base = 0x162;
        break;
    case 12:
        t = D_8014CD0C;
        n = 0x8;
        base = 0x194;
        break;
    case 13:
        t = D_8014CD34;
        n = 0xD;
        base = 0x2B9;
        break;
    case 14:
        t = D_8014CD70;
        n = 0x1;
        base = 0x40;
        break;
    case 15:
        t = D_8014CDA4;
        n = 0x2;
        base = 0x61;
        break;
    default:
        return;
    }
    p = D_1F80021C + t[idx].a * 32 + base * 32;
    func_8001D2A8(n, p, p + (t[idx].b + 1) * 32, 0);
}

void func_801406A4(s32 i)
{
    if (D_800BFE56 & 0x40) {
        i += 4;
    }
    func_80075070(D_8014CA58[i]);
}

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_801406E8);

typedef struct { s16 x; s16 z; } Pair;
extern Pair D_8014CE4C[];
void func_801408BC(u8 *a)
{
    s32 x;
    s32 y;
    s32 z;
    s32 t;
    s16 n;

    switch (a[5]) {
    case 0:
        *(s16 *)(a + 0x50) = 0;
        *(s16 *)(a + 0x40) = 0x3C;
        a[5]++;
        a[3] = func_8009A450() & 3;
    case 1:
        if (--*(s16 *)(a + 0x40) == -1) {
            *(s16 *)(a + 0x50) = 0;
            a[5]++;
            *(s16 *)(a + 0x40) = a[3] * 10;
        } else {
            *(s16 *)(a + 0x32) -= 4;
            *(s32 *)(a + 0x30) -= func_80083E80(*(s16 *)(a + 0x50)) * 0xC0;
            *(s16 *)(a + 0x50) += 0x80;
            *(s16 *)(a + 0x2E) += D_8014CE4C[a[3]].x;
            *(s16 *)(a + 0x36) += D_8014CE4C[a[3]].z;
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
        *(s16 *)(a + 0x50) = -0x1000;
        *(s16 *)(a + 0x52) = 0x200;
        a[5]++;
        *(s16 *)(a + 0x40) = 0x10;
        *(s16 *)(a + 0x48) = ((0x4B40 - *(s16 *)(a + 0x2E)) * 16) / *(s16 *)(a + 0x40);
        *(s16 *)(a + 0x4A) = ((-0x1F40 - *(s16 *)(a + 0x32)) * 16) / *(s16 *)(a + 0x40);
        *(s16 *)(a + 0x4C) = ((0x2DC0 - *(s16 *)(a + 0x36)) * 16) / *(s16 *)(a + 0x40);
    case 4:
        t = *(s16 *)(a + 0x50) << 8;
        *(s32 *)(a + 0x2C) += *(s16 *)(a + 0x48) << 12;
        *(s32 *)(a + 0x30) += *(s16 *)(a + 0x4A) << 12;
        *(s32 *)(a + 0x34) += *(s16 *)(a + 0x4C) << 12;
        *(s16 *)(a + 0x50) += *(s16 *)(a + 0x52);
        *(s32 *)(a + 0x30) += t;
        if (--*(s16 *)(a + 0x40) == -1) {
            a[5]++;
        }
        break;
    case 5:
        *(s16 *)(a + 0x48) = 0x180;
        *(s16 *)(a + 0x4C) = 0x180;
        a[5]++;
        if (func_8009A450() & 1) {
            *(s16 *)(a + 0x4E) = 0;
        } else {
            *(s16 *)(a + 0x4E) = 0x800;
        }
        *(s16 *)(a + 0x50) = 0;
        break;
    case 6:
        *(s16 *)(a + 0x2E) = 0x4B40;
        *(s16 *)(a + 0x32) = -0x1F40;
        *(s16 *)(a + 0x36) = 0x2DC0;
        *(s32 *)(a + 0x30) += func_80083E80(*(s16 *)(a + 0x50)) << 11;
        if (a[3] & 1) {
            *(s16 *)(a + 0x44) = (func_80083E80(*(s16 *)(a + 0x4E)) * 0x60) >> 4;
        } else {
            *(s16 *)(a + 0x44) = (func_80083E80(*(s16 *)(a + 0x4E)) << 6) >> 4;
        }
        *(s16 *)(a + 0x50) += 0x28;
        *(s16 *)(a + 0x4E) += 0x18;
        *(s32 *)(a + 0x2C) += *(s16 *)(a + 0x48) * *(s16 *)(a + 0x44);
        *(s32 *)(a + 0x34) += *(s16 *)(a + 0x4C) * *(s16 *)(a + 0x44);
        break;
    }
}

extern s32 D_800BF85C;
extern u8 D_1F80017C_0fe7_7bca;
void func_80140CCC(u8 *a)
{
    switch (a[5]) {

    case 0:
        a[5]++;
        {
            u8 r = D_1F80017C_0fe7_7bca;
            H(a, 0x4E) = 0;
            H(a, 0x4A) = -4;
            H(a, 0x40) = 0;
            a[0x46] = r & 1;
        }
    case 1:
        func_8004766C(a);
        func_80049760(a);
        H(a, 0x32) += H(a, 0x4A);
        H(a, 0x44) = func_80083E80(H(a, 0x4E));
        {

            s32 z;
            H(a, 0x4E) += 0x40;
            *(s32 *)(a + 0x2C) += H(a, 0x48) * H(a, 0x44);
            *(s32 *)(a + 0x34) += H(a, 0x4C) * H(a, 0x44);
        }
        if (a[0x46] == 0) {
            *(s32 *)(a + 0x2C) += H(a, 0x48) << 10;
            *(s32 *)(a + 0x34) += H(a, 0x4C) << 10;
        } else {
            *(s32 *)(a + 0x2C) -= H(a, 0x48) << 10;
            *(s32 *)(a + 0x34) -= H(a, 0x4C) << 10;
        }
        func_8004954C(a, H(a, 0x80), 0);
        H(a, 0x40)++;
        break;
    }
    if (a[1] == 0 && H(a, 0x40) > 0x96) {
        a[4] = 3;
        D_800BF85C = 0;
    }
}

INCLUDE_ASM("asm/a06/nonmatchings/a06", f_UpdateDonglinSnowFireflyPickup);

extern u8 D_800E7EAA;
void f_UpdateDonglinSnowFireflyPickup();
u8 *func_80141020(u8 *a, s32 b, s32 c)
{
    u8 *p;
    u8 *g;

    if (b == 2) {
        u8 *s;
        if (D_800E7EAA >= 13) {
            return NULL;
        }
        s = D_800BF808_1760;
        if (*(s32 *)(s + 0x54) != 0) {
            return NULL;
        }
        g = (u8 *)&D_800BF870;
        if (g[0x19D] + g[0x19E] >= 11) {
            return NULL;
        }
        if (g[0x19E] >= 10) {
            return NULL;
        }
        *(s32 *)(s + 0x54) = 1;
    }
    p = func_80072DDC(0, 1, 2, 0x47);
    if (p != NULL) {
        *(void **)(p + 0x1C) = f_UpdateDonglinSnowFireflyPickup;
        p[0x5E] = b;
        p[3] = c;
        if (b == 0) {
            *(s32 *)(p + 0x10) = c;
        } else {
            *(s16 *)(p + 0x2E) = *(s16 *)(a + 2);
            *(s16 *)(p + 0x32) = *(s16 *)(a + 6);
            *(s16 *)(p + 0x36) = *(s16 *)(a + 0xA);
            p[0x2A] = D_800E7EAA;
        }
    }
    return p;
}

extern s16 D_800E7FEE;
void func_80141134(void *arg0) {
    if (D_800E7FEE != 0) {
        D_800BF85C = 0;
        D_800BF870.pad1[0x19D] += 1;
        func_80040B48(0x6D, &D_800BF870);
        func_8004D4C4(0x75, 1);
        M2C_FIELD(arg0, s8 *, 4) = 3;
    }
}

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80141198);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80141304);

/* func_80141770, inlined */
static inline void inl_80141770(void *arg0)
{
    func_8004D4C4(0x3D, 1);
    func_8004B0D8(arg0);
    M2C_FIELD(arg0, s8 *, 4) = 3;
    D_800BF870.pad1[0x1D8] |= 2;
}
/* func_801417C4, inlined */
static inline void inl_801417C4(u8 *p)
{
    u8 *g;

    switch (p[6]) {
    case 0:
        p[6]++;
        p[7] = 0;
    case 1:
        if (func_8004B3F4(p, p[0x5E])) {
            g = (u8 *)&D_800BF870;
            p[4] = 3;
            g[0x1DA]++;
        }
        break;
    }
}
/* func_8014183C, inlined */
static inline void inl_8014183C(u8 *p)
{
    switch (p[6]) {
    case 0:
        p[6]++;
        p[7] = 0;
    case 1:
        if (func_80049E54(p, 1)) {
            p[4] = 3;
        }
        break;
    }
}
void func_80141480(u8 *a)
{
    switch (a[4]) {
    case 0:
        func_80141304(a);
        break;
    case 1:
        switch (a[5]) {
        case 0:
            *(s16 *)(a + 0x4A) = -0x4000;
            *(s16 *)(a + 0x50) = 0x280;
            a[5] = 1;
            *(s16 *)(a + 0x60) = 0x4000;
            a[0] = 1;
            break;
        case 1:
            *(s32 *)(a + 0x30) += *(s16 *)(a + 0x4A) << 8;
            *(s16 *)(a + 0x4A) += *(u16 *)(a + 0x50);
            if (*(s16 *)(a + 0x4A) > 0) {
                *(s16 *)(a + 0x4E) = 0;
                a[5]++;
            }
            break;
        case 2:
            *(s16 *)(a + 0x4E) += 0x200;
            if (*(s16 *)(a + 0x4E) >= 0x1000) {
                a[5]++;
            }
            break;
        case 3:
            *(s32 *)(a + 0x30) += *(s16 *)(a + 0x4A) << 8;
            *(s16 *)(a + 0x4A) += *(u16 *)(a + 0x50);
            if (*(s16 *)(a + 0x60) < *(s16 *)(a + 0x4A)) {
                a[4] = 3;
                func_8003116C(8, a + 0x2C, -0x20);
            }
            break;
        }
        if (func_8007778C(a) != 0) {
            func_80077B5C(a);
        }
        break;
    case 2:
        switch (a[3]) {
        case 0:
            switch (a[5]) {
            case 1:
                if (func_8007778C(a) != 0) {
                    func_80077B5C(a);
                }
                break;
            case 2:
            case 3:
                inl_80141770(a);
                break;
            }
            break;
        case 2:
        case 3:
            inl_801417C4(a);
            break;
        case 1:
            inl_8014183C(a);
            break;
        }
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

void func_80141770(void *arg0) {
    func_8004D4C4(0x3D, 1);
    func_8004B0D8(arg0);
    M2C_FIELD(arg0, s8 *, 4) = 3;
    D_800BF870.pad1[0x1D8] |= 2;
}

void func_801417C4(u8 *p)
{
    u8 *g;

    switch (p[6]) {
    case 0:
        p[6]++;
        p[7] = 0;
    case 1:
        if (func_8004B3F4(p, p[0x5E])) {
            g = (u8 *)&D_800BF870;
            p[4] = 3;
            g[0x1DA]++;
        }
        break;
    }
}

void func_8014183C(u8 *p)
{
    switch (p[6]) {
    case 0:
        p[6]++;
        p[7] = 0;
    case 1:
        if (func_80049E54(p, 1)) {
            p[4] = 3;
        }
        break;
    }
}

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8014189C);

INCLUDE_ASM("asm/a06/nonmatchings/a06", f_UpdatePotatoBugQuestNpcActor);

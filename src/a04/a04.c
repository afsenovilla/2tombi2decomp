#include "common.h"
#include "game.h"
#include "m2c.h"
#include "gte.h"

extern s8 D_800BF808_c1f7[];
extern u8 D_1F800137_104c;
extern s32 D_1F80009C_baed;
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

void func_8010A514(u8 *a, u8 *b) {
    s32 t, u;

    if (D_1F800137_104c != 0 || D_800BF808_c1f7[5] != 0) {
        return;
    }
    if (M2C_FIELD(a, s16 *, 0x17E) & 0x8200) {
        if (func_8002300C(a, b, 0x20) != 0) {
            if (!(a[0] & 4)) {
                t = (func_80083F50(D_1F80009C_baed + 0x800) * (M2C_FIELD(a, s16 *, 0x80) + 0x20)) >> 12;
                u = func_80083E80(D_1F80009C_baed + 0x800) * (M2C_FIELD(a, s16 *, 0x80) + 0x20);
                M2C_FIELD(a, s16 *, 0x2E) = M2C_FIELD(b, s16 *, 0x2E) + t;
                M2C_FIELD(a, s16 *, 0x36) = M2C_FIELD(b, s16 *, 0x36) - (u >> 12);
            }
            M2C_FIELD(a, s8 *, 0x5F) = func_80077768((s16)(*(u16 *)&D_1F80009C_baed + 0x800), M2C_FIELD(a, s16 *, 0x140), 1) + 2;
        }
    } else if (func_80022F04(a, b) != 0) {
        b[0x29] = 1;
        D_1F800137_104c = 2;
        D_800BF808_c1f7[0x39] = 1;
    }
}

#define F16(p, o) M2C_FIELD(p, s16 *, o)
#define FU16(p, o) M2C_FIELD(p, u16 *, o)
extern s8 D_800BF80D;
extern u8 D_1F800182_5650;
#define F16(p, o) M2C_FIELD(p, s16 *, o)
#define FU16(p, o) M2C_FIELD(p, u16 *, o)
extern u8 D_1F800182_5650;
void func_8010A668(u8 *a, u8 *b) {
    u8 *q = a + 0x60;
    u32 k;
    s32 s;
    s32 c;

    if (D_1F800137_104c != 0) {
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
s32 func_8010A834(u8 *a, u8 *b) {
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
s32 func_8010A9A8(u8 *a, u8 *b, u8 *c) {
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
    D_1F80009C_baed = ang;
    if (s < k) {
        if (!(a[0] & 4)) {
                        e = (func_80083F50(ang) * (F16(a, 0x80) + F16(b, 0x80))) >> 12;
                        t = func_80083E80(D_1F80009C_baed) * (F16(a, 0x80) + F16(b, 0x80));
                        F16(a, 0x2E) = FU16(c, 0x2C) + e;
            F16(a, 0x36) = FU16(c, 0x34) - (t >> 12);
        }
        a[0x5F] = func_80077768((s16)D_1F80009C_baed, F16(a, 0x140), 1) + 2;
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
extern s16 D_1F80018C;
extern s16 D_1F80018E;
extern u16 D_1F80008C;
void func_8010AC8C(u8 *a, u8 *b)
{
    s16 ang;
    s32 d;
    s32 k;
    s16 t;

    if (!(*(u16 *)(a + 0x17E) & 0x200) && func_8002300C(a, b, *(s16 *)(b + 0x80) * 4) != 0) {
        ang = D_1F80009C_efeb + 0x800;
        b[0x2B] = 1;
        if (D_1F800137_104c == 0) {
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

extern u8 D_800BF808_1760[];
extern u16 D_800BF812;
extern u8 D_800E8008[];
extern u8 D_1F8000D0[];
void func_8010AEA8(p)
u8 *p;
{
    u8 *e = D_800E8008;
    u8 *g = D_800BF808_1760;

    switch (g[0xF]) {
    case 0: {
        u8 *d = D_1F8000D0;

        if (*(s16 *)(d + 0xA) < 0x2141) {
            *(s16 *)(d + 0xA) = 0x2140;
            e[0x66] |= 1;
        } else if (*(s16 *)(d + 0xA) >= 0x2554) {
            *(s16 *)(d + 0xA) = 0x2554;
            e[0x66] |= 1;
        }
        return;
    }
    case 1: {
        u16 h = *(u16 *)(g + 0xA);

        if (!(p[0x145] & 1) && !(*(s16 *)(p + 0x32) < (s16)h - *(s16 *)(p + 0x62))) {
            *(s16 *)(p + 0x32) = h - *(s16 *)(p + 0x62);
            func_80022C78(p);
            p[0x29] |= 0x80;
        }
        if (D_1F800137_104c == 0 && *(s16 *)(p + 0x32) < -0x2E2C && *(s16 *)(p + 0x36) >= 0x357B) {
            *(s16 *)(p + 0x36) = 0x357A;
        }
        break;
    }
    default: {
        u16 h = D_800BF812;

        if (!(p[0x145] & 1) && !(*(s16 *)(p + 0x32) < (s16)h - *(s16 *)(p + 0x62))) {
            *(s16 *)(p + 0x32) = h - *(s16 *)(p + 0x62);
            func_80022C78(p);
            p[0x29] |= 0x80;
        }
        break;
    }
    }
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8010B024);

void func_8010B168(u8 *a, u8 *b)
{
    s32 r = func_8001F40C(a, b, 0);

    if (r < 0 || b[0] != 1) {
        return;
    }
    if (a[0x144] == 1 && r < 2) {
        if (*(s16 *)(a + 0x17E) & 0x8000) {
            func_8001F054(a, b);
            return;
        }
        func_8001FDB4(b, -0x7FFF, 3, 0x1E);
        return;
    }
    if (!(r & 1)) {
        if (!(a[0] & 4)) {
            s32 temp_s0 = (s32) (func_80083F50(D_1F80009C_baed) * (M2C_FIELD(a, s16 *, 0x80) + M2C_FIELD(b, s16 *, 0x80))) >> 0xC;
            s32 temp_lo = func_80083E80(D_1F80009C_baed) * (M2C_FIELD(a, s16 *, 0x80) + M2C_FIELD(b, s16 *, 0x80));
            M2C_FIELD(a, s16 *, 0x2E) = (s16) (M2C_FIELD(b, u16 *, 0x2E) + temp_s0);
            M2C_FIELD(a, s16 *, 0x36) = (s16) (M2C_FIELD(b, u16 *, 0x36) - (temp_lo >> 0xC));
        }
        a[0x5F] = func_80077768((s16)D_1F80009C_baed, *(s16 *)(a + 0x140), 1) + 2;
        return;
    }
    if (r == 1 && !(a[0x145] & 1)) {
        *(s16 *)(a + 0x32) = *(s16 *)(b + 0x32) - (*(s16 *)(a + 0x84) + *(s16 *)(b + 0x84));
        func_80022C78(a);
    }
}

extern s8 D_1F80009C[];
extern s8 D_1F800137[];
void func_8010B2FC(void *arg0, void *arg1, s32 arg2) {
    s32 temp_lo;
    s32 temp_s0;
    s32 temp_v0;
    u16 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u16 *, 0x17E);
    if (!(temp_v1 & 0x200)) {
        if (temp_v1 & 0x8000) {
            if (M2C_FIELD(arg1, u8 *, 0) == 1) {
                func_8001F830();
            }
        } else {
            temp_v0 = func_8001F40C(arg0, arg1, 1);
            if (temp_v0 >= 0) {
                if ((M2C_FIELD(arg0, u8 *, 0x144) == 1) && (temp_v0 < 2)) {
                    func_8001FDB4(arg1, 2, 0x10, 0x1E);
                    *((s8 *)D_1F800137) = 2;
                    return;
                }
                if ((arg2 != 0) && (M2C_FIELD(arg1, u8 *, 0) == 5)) {
                    M2C_FIELD(arg1, u8 *, 0) = 1U;
                    M2C_FIELD(arg1, s8 *, 4) = 2;
                    M2C_FIELD(arg1, s8 *, 5) = 0;
                    M2C_FIELD(arg1, s8 *, 6) = 0;
                }
                temp_s0 = (s32) (func_80083F50(*((s32 *)D_1F80009C)) * (M2C_FIELD(arg0, s16 *, 0x80) + M2C_FIELD(arg1, s16 *, 0x80))) >> 0xC;
                temp_lo = func_80083E80(*((s32 *)D_1F80009C)) * (M2C_FIELD(arg0, s16 *, 0x80) + M2C_FIELD(arg1, s16 *, 0x80));
                M2C_FIELD(arg0, s16 *, 0x2E) = (s16) (M2C_FIELD(arg1, u16 *, 0x2E) + temp_s0);
                M2C_FIELD(arg0, s16 *, 0x36) = (s16) (M2C_FIELD(arg1, u16 *, 0x36) - (temp_lo >> 0xC));
            }
        }
    }
}

s32 func_8010B45C(u8 *a, u8 *b, u8 *c) {
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

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8010B8A0);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8010BA18);

void func_8010BC80(u8 *a, u8 *b)
{
    u16 f = *(u16 *)(a + 0x17E);
    s32 r;

    if (f & 0x200) {
        return;
    }
    if (f & 0x8000) {
        func_8001F830(a, b);
        return;
    }
    r = func_8001F40C(a, b, 0);
    if (r < 0) {
        return;
    }
    if (a[0x144] == 1 && r < 2) {
        func_8001FDB4(b, -0x7FFC, 0x10, 0x1E);
        return;
    }
    if (r == 1) {
        if (!(a[0x145] & 1)) {
            func_80022C78(a);
            *(s32 *)(a + 0x30) = (*(s16 *)(b + 0x32) - (*(s16 *)(b + 0x84) + *(s16 *)(a + 0x84))) << 16;
        }
    } else {
        if (!(a[0] & 4)) {
            s32 temp_s0 = (s32) (func_80083F50(D_1F80009C_baed) * (M2C_FIELD(a, s16 *, 0x80) + M2C_FIELD(b, s16 *, 0x80))) >> 0xC;
            s32 temp_lo = func_80083E80(D_1F80009C_baed) * (M2C_FIELD(a, s16 *, 0x80) + M2C_FIELD(b, s16 *, 0x80));
            M2C_FIELD(a, s16 *, 0x2E) = (s16) (M2C_FIELD(b, u16 *, 0x2E) + temp_s0);
            M2C_FIELD(a, s16 *, 0x36) = (s16) (M2C_FIELD(b, u16 *, 0x36) - (temp_lo >> 0xC));
        }
        a[0x60] = 1;
        a[0x5F] = func_80077768((s16)D_1F80009C_baed, *(s16 *)(a + 0x140), 1) + 2;
    }
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8010BE1C);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8010C03C);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8010C320);

extern u8 D_8013FF3C[];
extern u8 D_800E7E80[];
#define H(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define U(p, o) (*(u16 *)((u8 *)(p) + (o)))
extern u8 D_8014190C[];
void func_8010C588(u8 *a, u8 *b) {
    s32 r = 0;
    s32 k;
    u8 v;

    if (D_800BF80D != 0) {
        return;
    }
    if (b[3] & 0x80) {
        if (func_80022F04(a, b) == 0) {
            return;
        }
        func_8001DC9C(a, b, r, 0x5);
        D_1F800182_5650 = 0;
        return;
    }
    if (func_8010BE1C(a, b, *(u8 **)(b + 0xCC), 1) < 0) {
        if (func_80022F04(a, b) == 0) {
            return;
        }
        r = 1;
    }
    if (r == 0) {
        k = D_8013FF3C[a[2]];
        switch (a[2]) {
        case 0:
            k |= 2;
            break;
        case 1:
        case 4:
        case 7:
        case 10:
            k |= 1;
            break;
        default:
            k = 0;
            break;
        case 3:
            k |= 3;
            break;
        case 5:
        case 6:
            k |= 4;
            break;
        case 8:
        case 9:
            k |= 5;
            break;
        }
        r = k & 0xF;
        if (a[0x5E] != 0) {
            k |= 8;
            r = k & 0xF;
        }
        if (r == 2) {
            v = b[0x5E];
            if (v == r) {
                a[0] = v;
                a[0x2B] = v;
                a[4] = v;
                a[5] = v;
                b[0x2B] = v;
                *(u8 **)(b + 0x10) = a;
                D_1F800182_5650 = 0;
                return;
            }
        }
    }
    func_8001E860(a, b, 0, 0);
    D_1F800182_5650 = 0;
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8010C710);

s32 func_8010C8B4(a, b) u8 *a; u8 *b; {
    s16 dx, dz, dy, e, f;
    u16 h, bh, ah;
    u16 r;
    s32 s, t, k, y;

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
    D_1F80009C_baed = func_80085690(-dz, dx);
    if (f < 0 && e - dy < 0x1A) {
        if (a[0x145] & 1) {
            goto fail;
        }
        b[0x29] = 1;
        func_80022C78(a);
        M2C_FIELD(a, s32 *, 0x30) = (F16(b, 0x32) + f) << 16;
        return 2;
    }
    s = F16(a, 0x80) + F16(b, 0x80) - (s16)r;
    k = e - dy;
    if (s < k) {
        if (!(a[0] & 4)) {
            e = (func_80083F50(D_1F80009C_baed) * (F16(a, 0x80) + F16(b, 0x80))) >> 12;
            t = func_80083E80(D_1F80009C_baed) * (F16(a, 0x80) + F16(b, 0x80));
            F16(a, 0x2E) = FU16(b, 0x2E) + e;
            F16(a, 0x36) = FU16(b, 0x36) - (t >> 12);
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
        b[0x29] = 1;
        func_80022C78(a);
        M2C_FIELD(a, s32 *, 0x30) = (F16(b, 0x32) + f) << 16;
        return 2;
    }
    if (D_1F800098 == 0) {
        y = F16(b, 0x32) + f;
        D_1F800253 = 4;
        M2C_FIELD(a, s32 *, 0x30) = y << 16;
        if (a[0x145] == 1 && F16(a, 0x4A) < 0) {
            F16(a, 0x4A) = 0;
        }
    }
    return 3;
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8010CBFC);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8010CDB4);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8010D270);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8010D700);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8010DB48);

void func_8010DEF0(u8 *a, u8 *b)
{
    s16 ang;
    s32 d;
    s32 k;
    s16 t;

    if (func_8002300C(a, b, *(s16 *)(b + 0x80) * 4) != 0) {
        ang = D_1F80009C_efeb + 0x800;
        b[0x2B] = 1;
        if (D_1F800137_104c == 0) {
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

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8010E0FC);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8010E2D0);

s32 func_8010E554(u8 *a, u8 *b)
{
    s16 dx = *(u16 *)(a + 0x2E) - *(u16 *)(b + 0x2E);
    s16 dz = *(u16 *)(a + 0x36) - *(u16 *)(b + 0x36);
    s32 d = func_80084080(dx * dx + dz * dz);

    if ((u16)d > *(s16 *)(a + 0x80) + *(s16 *)(b + 0x80)) {
        return 0;
    }
    if ((u16)((*(u16 *)(a + 0x32) - *(u16 *)(b + 0x32)) + (*(u16 *)(b + 0x84) + (*(u16 *)(a + 0x86) - *(u16 *)(a + 0x84)))) > *(s16 *)(a + 0x86) + *(s16 *)(b + 0x86)) {
        return 0;
    }
    D_1F80009C_baed = func_80085690(-dz, dx);
    if (a[0xC] == 2) {
        a[0x5F] = func_80077768((s16)D_1F80009C_baed, *(s16 *)(a + 0x60), 1) + 2;
    }
    {
        s32 temp_s0 = (s32) (func_80083F50(D_1F80009C_baed) * (M2C_FIELD(a, s16 *, 0x80) + M2C_FIELD(b, s16 *, 0x80))) >> 0xC;
        s32 temp_lo = func_80083E80(D_1F80009C_baed) * (M2C_FIELD(a, s16 *, 0x80) + M2C_FIELD(b, s16 *, 0x80));
        M2C_FIELD(a, s16 *, 0x2E) = (s16) (M2C_FIELD(b, u16 *, 0x2E) + temp_s0);
        M2C_FIELD(a, s16 *, 0x36) = (s16) (M2C_FIELD(b, u16 *, 0x36) - (temp_lo >> 0xC));
    }
    return 1;
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8010E6DC);

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
void func_8010E814(u8 *a, u8 *b)
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

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8010E9AC);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8010EDB0);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8010F1CC);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8010F75C);

extern s16 D_1F800144_138c;
extern u8 **D_1F80013C;
extern u8 *D_800F2738;
/* func_80110BD0, inlined */
static inline void inl_80110BD0(u8 *a, u8 *b)
{
    if (func_80022F04(a, b) != 0) {
        if (b[0] & 4) {
            func_8001E860(a, b, 0, 0);
            b[0x2B] = 4;
            return;
        }
        if (!(func_8001DC9C(a, b, 0, 0) & 0x80)) {
            D_1F800182_5650 = 0;
        }
    }
}
void func_8010FBEC(void)
{
    u8 *a;
    u8 **p;
    u8 *b;

    if (D_1F800144_138c == 0) {
        return;
    }
    for (a = D_800F2738; a != NULL; a = *(u8 **)(a + 0x24)) {
        if ((a[0] & 1) && a[0x2B] == 0) {
            p = D_1F80013C;
            D_1F800182_5650 = *(u8 *)&D_1F800144_138c;
            while (D_1F800182_5650 != 0) {
                b = *p;
                D_1F800182_5650--;
                p++;
                if (b[0] & 1) {
                    switch (b[2]) {
                    case 8:
                        func_80021394(a, b, 0x100);
                        break;
                    case 17:
                        func_8010C588(a, b);
                        break;
                    case 28:
                        func_80021AB0(a, b, 2);
                        break;
                    case 39:
                        func_80021AB0(a, b, 1);
                        break;
                    case 13:
                        func_8002192C(a, b, 0);
                        break;
                    case 27:
                        if (func_80022F04(a, b) != 0) {
                            switch (a[2]) {
                            case 0:
                            case 1:
                            case 3:
                            case 7:
                                func_8001DC9C(a, b, 0, 0);
                                b[0] = 2;
                                D_1F800182_5650 = 0;
                                break;
                            case 2:
                            case 4:
                            case 5:
                            case 6:
                            case 10:
                                func_8001E860(a, b, 0, 0);
                                D_1F800182_5650 = 0;
                                break;
                            case 8:
                                do {
                                    func_8001DC9C(a, b, 0, 0);
                                    b[0] = 2;
                                    a[0x2B] = 2;
                                } while (0);
                                D_1F800182_5650 = 0;
                                break;
                            case 9:
                                func_8001DC9C(a, b, 0, 0);
                                b[0] = 2;
                                break;
                            }
                        }
                        break;
                    case 40:
                        if (func_80022F04(a, b) != 0) {
                            if (b[0x5E] != 0) {
                                func_8001E860(a, b, 0, 0);
                            } else {
                                func_8001DC9C(a, b, 0, 5);
                            }
                            D_1F800182_5650 = 0;
                        }
                        break;
                    case 41:
                        inl_80110BD0(a, b);
                        break;
                    case 49:
                        if (func_80022F04(a, b) != 0) {
                            s32 r = func_8001DC9C(a, b, 0, 0);
                            b[0x2B] = 2;
                            if (!(r & 0x80)) {
                                D_1F800182_5650 = 0;
                            }
                        }
                        break;
                    case 52:
                        func_8002192C(a, b, 1);
                        break;
                    case 67:
                        func_8010E6DC(a, b);
                        break;
                    case 35:
                    case 36:
                    case 37:
                        func_80021DF4(a, b);
                        break;
                    case 42:
                    case 48:
                    case 51:
                        func_800216B4(a, b, 0);
                        break;
                    }
                }
            }
        }
    }
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8010FF6C);

extern u8 **D_1F80014C;
extern u8 D_1F800152;
extern u8 *D_1F800080_ddd3;
extern s16 D_1F800166;
extern s16 D_1F800190;
extern u8 D_800BF81E;
u8 *func_801103F0(u8 *a)
{
    u8 **l = D_1F80014C;
    u8 *b;

    D_1F800182_5650 = D_1F800152;
    while (D_1F800182_5650 != 0) {
        b = *l;
        D_1F800182_5650--;
        l++;
        if (b[0] & 1) {
            switch (b[2]) {
            case 1:
                if (func_80024BD8(a, b, *(void **)(b + 0xC0)) != 0) {
                    b[0x29] = 1;
                    *(s16 *)(a + 0x152) = *(u16 *)(b + 0x80) + *(u16 *)(a + 0x80) - 12;
                    if (b[3] == 0x63) {
                        D_1F800137_104c = 2;
                        a[4] = 4;
                        a[0x164] = 1;
                        D_1F800166 = 0;
                        D_1F800190 = 0;
                    } else if (b[3] == 0 || b[3] == 0x62) {
                        a[0x164] = 1;
                    } else {
                        a[0x164] = 9;
                    }
                    a[0x15C] = 0;
                    D_1F800080_ddd3 = b;
                    D_1F800182_5650 = 0;
                }
                break;
            case 17:
                if (func_80024BD8(a, b, *(void **)(b + 0xC0)) != 0) {
                    b[0x29] = 1;
                    a[0x164] = 3;
                    D_1F800080_ddd3 = b;
                    D_1F800182_5650 = 0;
                }
                break;
            case 8:
                func_8010D700(a, b, *(void **)(b + 0xC0));
                break;
            case 53:
                if (func_80024BD8(a, b, *(void **)(b + 0xC0)) != 0) {
                    s16 t;

                    D_800BF81E = 0;
                    b[0x29] = 1;
                    t = *(u16 *)(b + 0x80) + *(u16 *)(a + 0x80) - 12;
                    a[0x164] = 0x81;
                    a[0x15C] = 0;
                    D_1F800080_ddd3 = b;
                    D_1F800182_5650 = 0;
                    *(s16 *)(a + 0x152) = t;
                }
                break;
            }
        }
    }
    return D_1F800080_ddd3;
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80110608);

extern void *D_1F800080;
void func_80110714(u8 *a, u8 *b)
{
    if (func_80024BD8(a, b, *(void **)(b + 0xC0)) != 0) {
        b[0x29] = 1;
        a[0x164] = 3;
        D_1F800080 = b;
        D_1F800182_5650 = 0;
    }
}

extern u8 D_800BF816;
void func_8011076C(u8 *a0, u8 *a1)
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

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80110800);

void func_80110900(void) {
    if (D_800BF816 != 0) {
        func_8010AEA8();
        return;
    }
    if (*(u8 *)0x1F800137 == 0) {
        func_8010B024();
    }
}

void func_80110950(u8 *a, u8 *b) {
    s32 r;

    if (func_80022F04(a, b) != 0) {
        r = func_8001E860(a, b, 0, 0);
        b[0x2B] = 1;
        if (!(r & 0x80)) {
            D_1F800182_5650 = 0;
        }
    }
}

void func_801109B0(u8 *a, u8 *b)
{
    s32 v;

    if (func_8002313C(a, b, *(void **)(b + 0xC0)) != 0) {
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

void func_80110A30(u8 *a, u8 *b)
{
    if (func_8001F830(a, b) != 0) {
        a[0x2B] = D_1F80009C_baed >> 4;
        if (func_80022D08(a, 0, 1, 1) != 0 && !(a[0x177] & 2) && (*(u16 *)(a + 0x17E) & 0x30)) {
            a[5] = 0;
            a[6] = 4;
            a[7] = 0;
            a[0] |= 8;
        }
    }
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80110AC4);

void func_80110BD0(u8 *a, u8 *b)
{
    if (func_80022F04(a, b) != 0) {
        if (b[0] & 4) {
            func_8001E860(a, b, 0, 0);
            b[0x2B] = 4;
            return;
        }
        if (!(func_8001DC9C(a, b, 0, 0) & 0x80)) {
            D_1F800182_5650 = 0;
        }
    }
}

void func_80110C58(u8 *a, u8 *b) {
    if (func_80022F04(a, b) != 0) {
        if (b[0x5E] != 0) {
            func_8001E860(a, b, 0, 0);
        } else {
            func_8001DC9C(a, b, 0, 5);
        }
        D_1F800182_5650 = 0;
    }
}

void func_80110CD0(u8 *a, u8 *b)
{
    s32 r = func_8001EC3C(a, b);
    u8 v;

    if (r < 0) {
        return;
    }
    if (r == 1) {
        b[0x5E] = v = a[0x5F];
        if (!(v & 1)) {
            if ((a[0x5F] & 1) == a[0x147] && a[0x46] == 0xC6) {
                a[0x5F] |= 8;
                b[0x5E] |= 8;
                D_800BF81E = 0;
            }
        }
    }
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80110D6C);

extern u8 D_800BFA0A;
void func_80110E20(void *arg0) {
    s32 temp_v0;

    temp_v0 = func_8010C8B4();
    if ((temp_v0 >= 0) && ((u32) (D_800BFA0A & 0xF) >= 2U)) {
        if (temp_v0 == 1) {
            M2C_FIELD(arg0, s16 *, 0x142) = -0x300;
            return;
        }
        M2C_FIELD(arg0, s16 *, 0x142) = -0x100;
        M2C_FIELD(arg0, s8 *, 0x16A) = 0xA;
    }
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80110E88);

extern s8 D_1F800182[];
void func_80110F88(s32 arg0, M2C_UNK arg1) {
    if (func_80022F04() != 0) {
        func_8001DC9C(arg0, arg1, 0, 5);
        *((s8 *)D_1F800182) = 0;
    }
}

void func_80110FD8(u8 *a, u8 *b)
{
    s32 k;
    s32 v;

    if (func_80022F04() == 0) {
        return;
    }
    k = D_8013FF3C[a[2]];
    switch (a[2]) {
    case 0:
        k |= 2;
        break;
    case 1:
    case 4:
    case 7:
    case 10:
        k |= 1;
        break;
    case 2:
    default:
        k = 0;
        break;
    case 3:
        k |= 3;
        break;
    case 5:
    case 6:
        k |= 4;
        break;
    case 8:
    case 9:
        k |= 5;
        break;
    }
    v = k & 0xF;
    if (a[0x5E] != 0) {
        k |= 8;
        v = k & 0xF;
    }
    if (v == 2) {
        a[0] = v;
        a[4] = v;
        a[5] = v;
        *(u8 **)(b + 0x10) = a;
        b[4] = v;
        b[5] = 0;
        b[6] = 0;
    }
    D_1F800182_5650 = 0;
}

void func_801110B8(u8 *a, u8 *b) {
    if (func_80022F04(a, b) != 0) {
        if (func_8001DC9C(a, b, 0, 0) & 0x80) {
            a[0x2B] = 2;
        }
        D_1F800182_5650 = 0;
    }
}

void func_80111118(u8 *a, u8 *b) {
    if (!(M2C_FIELD(a, u16 *, 0x17E) & 0x200) && func_80022F04(a, b) != 0) {
        a[0x2B] = D_1F80009C_baed >> 4;
        func_80022D08(a, b, 1, 0);
        b[0x2B] = 1;
    }
}

void func_8011118C(u8 *a, u8 *b) {
    s32 r;

    if (func_80022F04(a, b) != 0) {
        r = func_8001DC9C(a, b, 0, 0);
        b[0x2B] = 2;
        if (!(r & 0x80)) {
            D_1F800182_5650 = 0;
        }
    }
}

void func_801111EC(void *arg0, void *arg1) {
    u8 temp_a0;

    if (func_8001EC3C() == 1) {
        temp_a0 = M2C_FIELD(arg0, u8 *, 0x5F);
        if (((temp_a0 & 1) == M2C_FIELD(arg0, u8 *, 0x147)) && (M2C_FIELD(arg0, u8 *, 0x46) == 0xC6)) {
            M2C_FIELD(arg1, u8 *, 0x5F) = temp_a0;
            M2C_FIELD(arg0, u8 *, 0x5F) = (u8) (M2C_FIELD(arg0, u8 *, 0x5F) | 8);
        }
    }
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80111260);

void func_80111320(u8 *a, u8 *b) {
    s16 t;

    if (func_80024BD8(a, b, M2C_FIELD(b, u8 **, 0xC0)) != 0) {
        D_800BF81E = 0;
        b[0x29] = 1;
        t = M2C_FIELD(b, s16 *, 0x80) + M2C_FIELD(a, s16 *, 0x80);
        a[0x164] = 0x81;
        a[0x15C] = 0;
        D_1F800080_ddd3 = b;
        D_1F800182_5650 = 0;
        M2C_FIELD(a, s16 *, 0x152) = t - 0xC;
    }
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80111398);

s32 func_801114A0(s32 arg0, s32 arg1) {
    return func_8010DB48(arg0, arg1, M2C_FIELD(arg1, s32 *, 0xC0));
}

void func_801114C4(u8 *a, u8 *b)
{
    if (!(*(u16 *)(a + 0x17E) & 0x200)) {
        if (b[0x5E] != 0) {
            if (func_80022F04(a, b) != 0 && a[4] == 1 && a[5] != 0x13) {
                s32 v = D_1F80009C_baed;
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

void func_80111560(u8 *a, u8 *b) {
    if (func_8001F054(a, b) == 2 && !(M2C_FIELD(a, u16 *, 0x17E) & 0x200)) {
        a[0x2B] = D_1F80009C_baed >> 4;
        func_80022D08(a, b, 1, 1);
    }
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_801115D0);

extern u8 D_1F800144;
void func_80111710(u8 *a)
{
    u8 **l = D_1F80013C;
    u8 *p;
    D_1F800182_5650 = D_1F800144;
    while (D_1F800182_5650 != 0) {
        p = *l;
        D_1F800182_5650--;
        l++;
        if ((p[0] & 1) && p[2] == 8) {
            func_8002423C(a, p);
        }
    }
}

extern s16 D_1F80009C_c31a;
void func_801117C0(u8 *a, s32 b) {
    s32 r = func_80023A04(a, b, 1);

    if (r < 0) {
        return;
    }
    if (r == 0) {
        a[0x5F] = func_80077768(D_1F80009C_c31a, M2C_FIELD(a, s16 *, 0x60), 1) + 2;
    } else if (r == 2) {
        a[0x29] = 1;
    }
}

extern u16 D_800BFE56;
typedef struct { u8 pad[0x48]; s32 unk48; } AreaState808;
extern AreaState808 D_800BF808;
s32 func_80111828(u8 *a, s32 b) {
    if (func_80023A04(a, b, 3) < 0) {
        return 0;
    }
    a[0x5F] = func_80077768(D_1F80009C_c31a, M2C_FIELD(a, s16 *, 0x60), 1) + 2;
    return 1;
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8011187C);

extern s8 D_1F80009C[];
extern u8 D_800BFAD5;
void func_80111934(void *arg0, void *arg1) {
    if (!(M2C_FIELD(arg0, u16 *, 0x17E) & 0x200) && (func_80022F04() != 0)) {
        M2C_FIELD(arg0, s8 *, 0x2B) = (s8) ((s32) *((s32 *)D_1F80009C) >> 4);
        if (M2C_FIELD(arg1, u8 *, 0) & 8) {
            if (D_800BFAD5 == 0) {
                func_80022D08(arg0, arg1, 1, 1);
            }
        } else {
            if (D_800BFAD5 == 0) {
                func_80022D08(arg0, arg1, 1, 0);
            }
            M2C_FIELD(arg1, u8 *, 0) = 2U;
            M2C_FIELD(arg1, s8 *, 4) = 2;
            M2C_FIELD(arg1, s8 *, 5) = 2;
            M2C_FIELD(arg1, s8 *, 6) = 0;
        }
    }
}

extern void *D_800ECF80;
extern u8 D_80144360[];
void func_80111A04(u8 *a, u8 *b) {
    u8 *g;

    if (func_800240FC(a, b) != 0) {
        g = D_800E7E80;
        if ((g[0x78] == 0 || a != M2C_FIELD(g, u8 **, 0x10)) && a[4] < 3) {
            a[0] = 2;
            a[4] = 3;
        }
    }
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80111A74);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80111C08);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80111D60);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80111EC8);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80112068);

extern s8 D_1F800138[];
extern s8 D_1F80019B[];
void func_801127AC(void) {
    func_80045258(M2C_FIELD(*((volatile void **)D_1F800138), u8 *, 0x6E), 0xF);
    *((volatile s8 *)D_1F80019B) = 1;
    func_80051FB4();
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_801127EC);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_801129C0);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80112B50);

extern u16 D_800ECF54;
extern s16 D_1F80016C;
extern s16 D_1F80016E;
void func_801131E0(u8 *a, u8 *b) {
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
        func_80062A30(a, b, 0x81);
    } else if (H(a, 0x42) >= 0x97) {
        D_800BF840 = 0x48;
    }
}

extern u16 D_1F80017C_0fe7;
/* func_80115FE0, inlined */
static inline void inl_80115FE0(u8 *a, s32 b) {
    func_80054D14(a, 0x3D, 0);
    func_80062A30(a, b, 0x85);
    if (!(D_1F80017C_0fe7 & 3)) {
        func_80074590(0x27, -3, -0x46);
    }
}
static inline s32 ClingTurn(u8 *a)
{
    *(u16 *)(a + 0x42) += *(u16 *)(a + 0x154);
    if ((a[0x147] ^ a[0x15C]) == 0) {
        *(u16 *)(a + 0x56) -= *(u16 *)(a + 0x154);
    } else {
        *(u16 *)(a + 0x56) += *(u16 *)(a + 0x154);
    }
    if (*(s16 *)(a + 0x42) > 0x800) {
        if (a[0x147] == 0) {
            a[0x147] = 1;
            a[0x149] = 3;
            a[0x14A] = 3;
            *(u16 *)(a + 0x56) = *(u16 *)(a + 0x140) + 0x800;
        } else {
            a[0x147] = 0;
            a[0x149] = 2;
            a[0x14A] = 2;
            *(u16 *)(a + 0x56) = *(u16 *)(a + 0x140);
        }
        H(a, 0x42) = 0;
        a[7] = 3;
        H(a, 0x154) = 0;
        a[0] &= 3;
        return 1;
    }
    return 0;
}
void func_801133CC(u8 *a, u8 *b, s32 f, s32 g)
{
    u8 *p;
    s16 ang;

    a[0x160] = 0;
    if (f == 0) {
        if (g == 0 && !(D_800BFE56 & 0x10) && !(*(u16 *)(a + 0x17E) & 0x40)) {
            switch (a[7]) {
            case 0:
                func_80063098(a);
                func_80076D68(a);
                func_80062A30(a, b, 0x45);
                break;
            case 1:
                func_80076D68(a);
                if (ClingTurn(a)) {
                    func_80062A30(a, b, 0x85);
                } else {
                    func_80062A30(a, b, 0x45);
                }
                break;
            case 2:
                a[7] = 0;
                H(a, 0x154) = 0;
                a[0x5E] = 0;
                H(a, 0x42) = 0;
                a[0] |= 4;
                func_80054D14(a, 0x29, 4);
                break;
            case 3:
                inl_80115FE0(a, b);
                func_80076D68(a);
                break;
            }
        } else {
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
                func_801131E0(a, b);
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
                func_801131E0(a, b);
                func_80076D68(a);
                break;
            case 5:
                func_80076D68(a);
                if (D_800ECF54 & 0x10) {
                    if (!(D_1F80017C_0fe7 & 3)) {
                        func_80074590(0x27, -5, -0x46);
                    }
                    func_80054D14(a, 0x34, 0);
                    func_80062A30(a, b, 0);
                } else if (D_800ECF54 & 0x40) {
                    if (!(D_1F80017C_0fe7 & 3)) {
                        func_80074590(0x27, -3, -0x46);
                    }
                    func_80054D14(a, 0x3D, 0);
                    func_80062A30(a, b, 0x81);
                } else {
                    a[7] = 3;
                    H(a, 0x42) = 8;
                    func_80054D14(a, 0x29, 4);
                    H(a, 0x40) = 0x5A;
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
                        func_80062A30(a, b, 0x81);
                    } else {
                        func_80076D68(a);
                    }
                } else {
                    H(a, 0x40) = 0x5A;
                    H(a, 0x42) = 8;
                    a[7] = 3;
                    func_80054D14(a, 0xA9, 0);
                }
                break;
            }
        }
    }
    p = *(u8 **)(a + 0x10);
    if (*(s32 *)(a + 0x158) != 0) {
        ang = H(a, 0x56) + 0x800;
        H(a, 0x2E) = H(p, 0x2C) + ((func_80083F50(ang) * H(a, 0x152)) >> 12);
        H(a, 0x36) = H(p, 0x34) - ((func_80083E80(ang) * H(a, 0x152)) >> 12);
    }
    H(a, 0x32) = H(p, 0x30) + H(a, 0x156);
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_801139F4);

void func_80113FA4(void *arg0, s32 arg1) {
    s16 temp_s0;
    s16 temp_v1_2;
    s32 temp_lo;
    s32 var_a1;
    u16 temp_v0;
    u8 temp_v1;
    void *temp_s1;

    var_a1 = arg1;
    temp_v1 = M2C_FIELD(arg0, u8 *, 7);
    switch (temp_v1) {                              /* irregular */
    case 0:
        M2C_FIELD(arg0, u16 *, 0x154) = 0x100U;
        M2C_FIELD(arg0, u16 *, 0x56) = 0U;
        M2C_FIELD(arg0, u8 *, 7) = (u8) (M2C_FIELD(arg0, u8 *, 7) + 1);
        /* fallthrough */
    case 1:
        temp_v0 = M2C_FIELD(arg0, u16 *, 0x154) - 0x20;
        M2C_FIELD(arg0, u16 *, 0x154) = temp_v0;
        if ((s16) temp_v0 < 0x20) {
            M2C_FIELD(arg0, u16 *, 0x154) = 0x20U;
        }
        temp_v1_2 = M2C_FIELD(arg0, u16 *, 0x56) - M2C_FIELD(arg0, u16 *, 0x154);
        M2C_FIELD(arg0, u16 *, 0x56) = (u16) temp_v1_2;
        if (temp_v1_2 < -0x3FF) {
            M2C_FIELD(arg0, s8 *, 0x149) = 2;
            M2C_FIELD(arg0, s8 *, 0x14A) = 2;
            M2C_FIELD(arg0, u16 *, 0x56) = 0xC00U;
            M2C_FIELD(arg0, s16 *, 0x140) = 0xC00;
            M2C_FIELD(arg0, s8 *, 0x2A) = 1;
            M2C_FIELD(arg0, s8 *, 0x147) = 0;
            M2C_FIELD(arg0, s8 *, 5) = 4;
            M2C_FIELD(arg0, s8 *, 6) = 0;
            M2C_FIELD(arg0, u8 *, 7) = 0U;
            M2C_FIELD(arg0, s8 *, 0x61) = 0;
            M2C_FIELD(arg0, u8 *, 0) = (u8) (M2C_FIELD(arg0, u8 *, 0) & 3);
        } else {
            temp_s0 = temp_v1_2 + 0x800;
            temp_s1 = M2C_FIELD(arg0, void **, 0x10);
            temp_lo = func_80083F50(temp_s0) * M2C_FIELD(arg0, s16 *, 0x152);
            M2C_FIELD(arg0, s16 *, 0x2E) = (s16) (M2C_FIELD(temp_s1, u16 *, 0x2C) + (temp_lo >> 0xC));
            var_a1 = func_80083E80(temp_s0, temp_lo) * M2C_FIELD(arg0, s16 *, 0x152);
            M2C_FIELD(arg0, s16 *, 0x36) = (s16) (M2C_FIELD(temp_s1, u16 *, 0x34) - (var_a1 >> 0xC));
            M2C_FIELD(arg0, s16 *, 0x32) = (s16) (M2C_FIELD(temp_s1, u16 *, 0x30) + M2C_FIELD(arg0, u16 *, 0x156));
        }
        break;
    }
    func_80076D68(arg0, var_a1);
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8011411C);

#define W(p, o) (*(s32 *)((u8 *)(p) + (o)))

void func_801144FC(u8 *a) {
    s16 v;
    s16 t;

    switch (a[6]) {
    case 0:
        func_80074590(0x82, 0, 0);
        a[0x145] = 0;
        a[0x146] = 0;
        func_80053D90(a);
        func_80054E24(a, 1, 0);
        H(a, 0x4A) = 0;
        H(a, 0x50) = 0;
        a[0x148] = 0;
        H(a, 0x32) += 8;
        func_8005444C(a);
        a[0x29] = 0;
        if (H(a, 0x142) == 0) {
            if (H(a, 0x44) == 0) {
                if (a[0x147] != 0) {
                    H(a, 0x44) = -0x1400;
                } else {
                    H(a, 0x44) = 0x1400;
                }
            } else if (H(a, 0x44) > 0) {
                H(a, 0x44) = U(a, 0x44) + 0x200;
            } else {
                H(a, 0x44) = U(a, 0x44) - 0x200;
            }
        } else if (H(a, 0x142) > 0) {
            H(a, 0x44) = 0x1400;
        } else {
            H(a, 0x44) = -0x1400;
        }
        if (H(a, 0x44) >= 0) {
            a[0x147] = 0;
        } else {
            a[0x147] = 1;
        }
        H(a, 0x40) = 0;
        a[0x149] = a[0x14A] = a[0x147] + 2;
        a[6]++;
    case 1:
        if (H(a, 0x40)++ >= 0xC) {
            func_80074590(0x83, 0, 0);
            H(a, 0x40) = 0;
        }
        func_80056B48(a, 1);
        func_80055D5C(a);
        func_80076D68(a);
        H(a, 0x32) += 8;
        W(a, 0x30) += (abs(H(a, 0x44)) / 2) << 8;
        func_8005444C(a);
        if (a[0x29] == 0) {
            H(a, 0x32) -= 8;
            W(a, 0x30) -= (abs(H(a, 0x44)) / 2) << 8;
            func_80056C00(a, 0);
        } else {
            W(a, 0x30) += H(a, 0x4A) * H(a, 0x44);
            func_80056C00(a, 1);
        }
        if (H(a, 0x142) == 0) {
            if (H(a, 0x44) == 0) {
                if (a[0x147] != 0) {
                    H(a, 0x44) = U(a, 0x44) - 0x200;
                } else {
                    H(a, 0x44) = U(a, 0x44) + 0x200;
                }
            } else if (H(a, 0x44) > 0) {
                H(a, 0x44) = U(a, 0x44) + 0x200;
            } else {
                H(a, 0x44) = U(a, 0x44) - 0x200;
            }
        } else {
            H(a, 0x44) = U(a, 0x44) + (H(a, 0x142) >> 1);
        }
        if (H(a, 0x44) > 0x2400) {
            H(a, 0x44) = 0x2400;
        } else if (H(a, 0x44) < -0x2400) {
            H(a, 0x44) = -0x2400;
        }
        if (a[0x148] != 0) {
            a[0x16A] = 0;
        } else if (a[0x29] != 0) {
            if (func_80055824() != 0) {
                a[0x16A] = 0;
                a[5] = 2;
                a[6] = 0;
                a[7] = 0;
            } else if ((H(a, 0x6A) & 0xF000) != 0x4000) {
                a[7] = 0;
                H(a, 0x4A) = -0x2000;
                a[6]++;
                func_80054D14(a, 0x69, 6);
            }
        }
        break;
    case 2:
        v = abs(H(a, 0x44));
        t = v;
        if (v != 0) {
            t = v - 0x80;
            if (t <= 0) {
                t = 0;
            }
        }
        if (a[0x147] == 0) {
            H(a, 0x44) = t;
        } else {
            H(a, 0x44) = -t;
        }
        func_80056B48(a, 1);
        func_80055D5C(a);
        func_80076D68(a);
        if ((s16)(H(a, 0x4A) += 0x320) > 0x3E00) {
            H(a, 0x4A) = 0x3E00;
        }
        W(a, 0x30) += H(a, 0x4A) << 8;
        if (H(a, 0x4A) > 0) {
            if (a[7] == 0) {
                a[0x144] = 1;
                a[7] = 1;
            }
            func_8005444C(a);
            if (a[0x29] != 0) {
                func_8005314C(a);
                if (a[0x144] < 2) {
                    a[0x144] = 0;
                }
                a[6]++;
                func_80054198(a);
                func_80054D14(a, 0x66, 4);
            }
        }
        break;
    case 3:
        if (func_80076D68(a) != 2) {
            a[0x16A] = 0;
            a[5] = 0;
            a[6] = 0;
            a[7] = 0;
        }
        break;
    }
    func_800551C4(a);
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_801149B8);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_801150C4);

#define H(p, o) (*(s16 *)((u8 *)(p) + (o)))
void func_80115534(u8 *a, u8 *b)
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

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80115708);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80115978);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80115AFC);

extern s8 D_1F800138[];
extern s8 D_1F80019B[];
void func_80115EB0(void) {
    func_80045258(M2C_FIELD(*((volatile void **)D_1F800138), u8 *, 0x6E), 0xF);
    *((volatile s8 *)D_1F80019B) = 1;
    func_80051FB4();
}

s32 func_80115EF0(u8 *a, void *k)
{
    u8 *t = *(u8 **)(a + 0x158);

    if (t[2] == 1) {
        if (t[3] >= 0x62) {
            func_801133CC(a, t, k, 1);
            return 0;
        }
        func_801133CC(a, t, k, 0);
        if (!(D_800BFE56 & 0x10)) {
            if (!(*(u16 *)(a + 0x17E) & 0x40)) {
                return 1;
            }
        }
    }
    return 0;
}

void func_801196C8();
void func_8011B674();
void f_UpdateBigIcePigActor();
void func_80120F08();
void func_80115F8C(void) {
    u8 *p = func_8007A980(2, 3, 1);

    if (p != NULL) {
        M2C_FIELD(p, void **, 0x1C) = func_801196C8;
        p[0x2] = 0;
        p[0x3] = 1;
        p[0x28] = (p[0x28] | 0x80);
    }
}

void func_80115FE0(u8 *a, s32 b) {
    func_80054D14(a, 0x3D, 0);
    func_80062A30(a, b, 0x85);
    if (!(D_1F80017C_0fe7 & 3)) {
        func_80074590(0x27, -3, -0x46);
    }
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8011604C);

extern u16 D_1F800172;
s32 func_80116114(u8 *a, u8 *b)
{
    u8 *o = *(u8 **)(a + 0x10);
    s32 d;
    b[0x29] = 1;
    *(s16 *)(b + 0x60) = -*(u16 *)(a + 0x152);
    func_800635D4(a, 1);
    func_80076D68(a);
    if (a[0x169] == 0 && (D_800ECF54 & (D_1F800172 | 0x50))) {
        *(s16 *)(a + 0x58) = 0;
        func_80115534(a, b);
        return D_800ECF54;
    }
    func_80115534(a, b);
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

s32 func_801161EC(u8 *a)
{
    u8 *b = *(u8 **)(a + 0x158);
    u8 *o;
    s32 d;
    if (b[0xC] == 4 && b[2] == 8) {
    o = *(u8 **)(a + 0x10);
    b[0x29] = 1;
    *(s16 *)(b + 0x60) = -*(u16 *)(a + 0x152);
    func_800635D4(a, 1);
    func_80076D68(a);
    if (a[0x169] == 0 && (D_800ECF54 & (D_1F800172 | 0x50))) {
        *(s16 *)(a + 0x58) = 0;
        func_80115534(a, b);
        return D_800ECF54;
    }
    func_80115534(a, b);
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

extern u16 D_1F8001A4;
void func_801162E8(u8 *a)
{
    s16 v[8];

    v[1] = *(u16 *)(a + 0x2E);
    v[3] = D_1F8001A4;
    v[5] = *(u16 *)(a + 0x36);
    func_800312D4(0x515, v, -0xA);
    v[3] += 0x50;
    func_800312D4(0x514, v, -0xA);
    func_80074590(7, 0, 0);
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", f_SpawnKujaraRanchSceneActorsFromPlacementTable);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80116884);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_801169E8);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80116B48);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80116CCC);

#define GH(p, o) (*(s16 *)((u8 *)(p) + (o)))
typedef struct { u8 pad[0x10]; u16 cells[1]; } GridCellList;
static inline void tri_span_70a8(u8 *a, s32 y, s32 l, s32 r) {
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
void func_801170A8(u8 *a, s32 *p0, s32 *p1, s32 *p2) {
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
        for (y = y0; y < y1; y++) { tri_span_70a8(a, y, xl >> 16, xr >> 16); xl += sl1; xr += sl3; }
        for (; y <= y2; y++) { tri_span_70a8(a, y, xl >> 16, xr >> 16); xl += sl2; xr += sl3; }
    } else {
        for (y = y0; y < y1; y++) { tri_span_70a8(a, y, xl >> 16, xr >> 16); xr += sl1; xl += sl3; }
        for (; y <= y2; y++) { tri_span_70a8(a, y, xl >> 16, xr >> 16); xl += sl3; xr += sl2; }
    }
}

extern u16 *D_800ECF78;
void func_801175D0(u8 *a)
{
    u16 *p = D_800ECF78;
    u16 t;

    *(u16 **)(a + 0xC) = p;
    *(u16 *)(a + 8) = p[0];
    t = p[1];
    a[7] = 0;
    *(u16 *)(a + 0xA) = t;
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_801175FC);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_801178A0);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80117C58);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80117E18);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80117F68);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_801181E8);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80118448);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_801185F0);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80118858);

void func_801189C4(void *arg0) {
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
            func_80118858(arg0);
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

extern s32 D_800ECF80_d353;
/* func_80118E50, inlined */
static inline void func_80118E50_inl(u8 *a) {
    if (func_80051B70(a, 0xC, 0x37) == 0) {
        a[0xB] = 0xF;
        a[0] = 1;
        a[0xD] = 0;
        M2C_FIELD(a, s16 *, 0x80) = 0x20;
        M2C_FIELD(a, s16 *, 0x82) = 0x40;
        M2C_FIELD(a, s16 *, 0x84) = 0x20;
        M2C_FIELD(a, s16 *, 0x86) = 0x40;
        func_8004B354(a, 1);
    }
}
/* func_80118F04, inlined */
static inline void func_80118F04_inl(u8 *a) {
    a[0xB] = 0x11;
    M2C_FIELD(a, s16 *, 0x7A) = 0x1C00;
    M2C_FIELD(a, s16 *, 0x7C) = 0x1C00;
    M2C_FIELD(a, s16 *, 0x7E) = 0x1C00;
    M2C_FIELD(a, s16 *, 0x5A) = 0;
    a[0x47] = 0;
    M2C_FIELD(a, s16 *, 0x5C) = 0;
    a[0xD] = 0;
    M2C_FIELD(a, s32 *, 0x3C) = D_800ECF80_d353;
    func_80077B38(a, D_80144360, 10);
    a[0x2A] = 7;
    a[0] = 1;
    M2C_FIELD(a, s16 *, 0x80) = 0x20;
    M2C_FIELD(a, s16 *, 0x82) = 0x40;
    M2C_FIELD(a, s16 *, 0x84) = 0x40;
    M2C_FIELD(a, s16 *, 0x86) = 0x80;
    func_8004B354(a, 0);
}
/* func_80119080, inlined */
static inline void func_80119080_inl(u8 *a) {
    a[0xB] = 0x11;
    M2C_FIELD(a, s16 *, 0x7A) = 0x1C00;
    M2C_FIELD(a, s16 *, 0x7C) = 0x1C00;
    M2C_FIELD(a, s16 *, 0x7E) = 0x1C00;
    M2C_FIELD(a, s16 *, 0x5A) = 0;
    a[0x47] = 0;
    M2C_FIELD(a, s16 *, 0x5C) = 0;
    a[0xD] = 0;
    M2C_FIELD(a, s32 *, 0x3C) = D_800ECF80_d353;
    func_80077B38(a, D_80144360, 11);
    a[0] = 1;
    M2C_FIELD(a, s16 *, 0x80) = 0x20;
    M2C_FIELD(a, s16 *, 0x82) = 0x40;
    M2C_FIELD(a, s16 *, 0x84) = 0x20;
    M2C_FIELD(a, s16 *, 0x86) = 0x40;
}
/* func_80118FA0, inlined */
static inline void func_80118FA0_inl(void *arg0) {
    if (func_80040B48(0x85) >= 0) {
        func_8004D4C4(0x94, 1);
        func_8004B0D8(arg0);
        D_800BF870.pad1[0xC8] |= 0x10;
    }
    M2C_FIELD(arg0, s8 *, 4) = 3;
}
/* func_80119104, inlined */
static inline void func_80119104_inl(void *arg0) {
    if (func_80040C00(0x66) >= 0) {
        func_8004D4C4(0x3F, 1);
        func_8004B0D8(arg0);
        D_800BF870.pad1[0x17B] += 1 << (M2C_FIELD(arg0, u8 *, 3) * 2);
    }
    M2C_FIELD(arg0, s8 *, 4) = 3;
}
void f_UpdateKujaraQuestPickupActor(u8 *a)
{
    switch (a[4]) {
    case 0:
        a[4] = 1;
        switch (a[3]) {
        case 0:
            func_80118E50_inl(a);
            break;
        case 1:
            func_80118F04_inl(a);
            break;
        case 2:
        case 3:
            func_80119080_inl(a);
            break;
        case 4:
            a[3] = 0x26;
            func_8004A828(a);
            a[3] = 4;
            a[0] = 1;
            a[0x2A] = 0;
            func_80041194(a, 0x20, 0, 0);
            break;
        }
        break;
    case 1:
        switch (a[3]) {
        case 0:
            if (func_8007778C(a) != 0) {
                func_800517F8(a);
                func_8004B374(a, 1);
            }
            break;
        case 1:
            if (func_8007778C(a) != 0) {
                func_8004B374(a, 0);
            }
            break;
        case 2:
        case 3:
            func_8007778C(a);
            break;
        case 4:
            func_8007778C(a);
            func_8004B374(a, 0);
            break;
        }
        break;
    case 2:
        switch (a[3]) {
        case 0:
            if (func_80040B48(0x61) >= 0) {
                func_8004D4C4(0x52, 1);
                func_8004B0D8(a);
            }
            a[4] = 3;
            break;
        case 1:
            func_80118FA0_inl(a);
            break;
        case 2:
        case 3:
            func_80119104_inl(a);
            break;
        case 4:
            if (func_8004A3D4(a) != 0) {
                a[4]++;
            }
            break;
        }
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

void func_80118E50(u8 *a) {
    if (func_80051B70(a, 0xC, 0x37) == 0) {
        a[0xB] = 0xF;
        a[0] = 1;
        a[0xD] = 0;
        M2C_FIELD(a, s16 *, 0x80) = 0x20;
        M2C_FIELD(a, s16 *, 0x82) = 0x40;
        M2C_FIELD(a, s16 *, 0x84) = 0x20;
        M2C_FIELD(a, s16 *, 0x86) = 0x40;
        func_8004B354(a, 1);
    }
}

void func_80118EB8(void *arg0) {
    if (func_80040B48(0x61) >= 0) {
        func_8004D4C4(0x52, 1);
        func_8004B0D8(arg0);
    }
    M2C_FIELD(arg0, s8 *, 4) = 3;
}

void func_80118F04(u8 *a) {
    a[0xB] = 0x11;
    M2C_FIELD(a, s16 *, 0x7A) = 0x1C00;
    M2C_FIELD(a, s16 *, 0x7C) = 0x1C00;
    M2C_FIELD(a, s16 *, 0x7E) = 0x1C00;
    M2C_FIELD(a, s16 *, 0x5A) = 0;
    a[0x47] = 0;
    M2C_FIELD(a, s16 *, 0x5C) = 0;
    a[0xD] = 0;
    M2C_FIELD(a, s32 *, 0x3C) = D_800ECF80_d353;
    func_80077B38(a, D_80144360, 10);
    a[0x2A] = 7;
    a[0] = 1;
    M2C_FIELD(a, s16 *, 0x80) = 0x20;
    M2C_FIELD(a, s16 *, 0x82) = 0x40;
    M2C_FIELD(a, s16 *, 0x84) = 0x40;
    M2C_FIELD(a, s16 *, 0x86) = 0x80;
    func_8004B354(a, 0);
}

void func_80118FA0(void *arg0) {
    if (func_80040B48(0x85) >= 0) {
        func_8004D4C4(0x94, 1);
        func_8004B0D8(arg0);
        D_800BF870.pad1[0xC8] |= 0x10;
    }
    M2C_FIELD(arg0, s8 *, 4) = 3;
}

void f_UpdateKujaraQuestPickupActor();
u8 *func_80119004(u8 *a) {
    u8 t;
    u8 *p = func_80072DDC(a, 0, 5, 3);

    if (p == NULL) {
        return NULL;
    }
    t = a[3];
    M2C_FIELD(p, void **, 0x1C) = f_UpdateKujaraQuestPickupActor;
    p[0x3] = t & 3;
    M2C_FIELD(p, s16 *, 0x2E) = M2C_FIELD(a, u16 *, 0x2E);
    M2C_FIELD(p, s16 *, 0x32) = M2C_FIELD(a, u16 *, 0x32);
    M2C_FIELD(p, s16 *, 0x36) = M2C_FIELD(a, u16 *, 0x36);
    return p;
}

void func_80119080(u8 *a) {
    a[0xB] = 0x11;
    M2C_FIELD(a, s16 *, 0x7A) = 0x1C00;
    M2C_FIELD(a, s16 *, 0x7C) = 0x1C00;
    M2C_FIELD(a, s16 *, 0x7E) = 0x1C00;
    M2C_FIELD(a, s16 *, 0x5A) = 0;
    a[0x47] = 0;
    M2C_FIELD(a, s16 *, 0x5C) = 0;
    a[0xD] = 0;
    M2C_FIELD(a, s32 *, 0x3C) = D_800ECF80_d353;
    func_80077B38(a, D_80144360, 11);
    a[0] = 1;
    M2C_FIELD(a, s16 *, 0x80) = 0x20;
    M2C_FIELD(a, s16 *, 0x82) = 0x40;
    M2C_FIELD(a, s16 *, 0x84) = 0x20;
    M2C_FIELD(a, s16 *, 0x86) = 0x40;

}

void func_80119104(void *arg0) {
    if (func_80040C00(0x66) >= 0) {
        func_8004D4C4(0x3F, 1);
        func_8004B0D8(arg0);
        D_800BF870.pad1[0x17B] += 1 << (M2C_FIELD(arg0, u8 *, 3) * 2);
    }
    M2C_FIELD(arg0, s8 *, 4) = 3;
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80119170);

void func_801193D4(u8 *a)
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

void func_80119588(u8 *a) {
    func_8004C0E4(a, 0, 0);
}

typedef struct { s16 h[7]; } E8013F238;
extern E8013F238 D_8014128C[];
void func_801195AC(u8 *a, s32 i)
{
    u8 **slot;
    u8 *e = func_8007AAE8();

    slot = (u8 **)(a + i * 4);
    if ((slot[0x30] = e) != NULL) {
        E8013F238 *tb = D_8014128C; s16 *t = tb[i].h;
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
        if (a[3] != 0) {
            func_80074590(0x85, 0, 0);
        }
    } else {
        a[4] = 3;
    }
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_801196C8);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80119B34);

void func_80119B34();
void func_80119F24(u8 *a, u8 k)
{
    u8 *e = func_8007A980(2, 3, 1);

    if (e != NULL) {
        *(void **)(e + 0x1C) = func_80119B34;
        e[2] = 0;
        e[3] = k;
        *(u8 **)(a + 0x10) = e;
        *(u8 **)(e + 0x10) = a;
        *(s16 *)(e + 0x2E) = *(s16 *)(a + 0x2E);
        *(s16 *)(e + 0x32) = *(s16 *)(a + 0x32);
        *(s16 *)(e + 0x36) = *(s16 *)(a + 0x36);
    }
}

extern u8 D_800BF818_7697;
void func_80119FA8(u8 *a, u8 *b) {
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

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8011A164);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8011A3C0);

extern s8 D_1F80017C[];
extern u8 D_800BF9BB;
void func_8011A554(void *arg0) {
    u16 temp_v0;
    u8 temp_v1;
    void *temp_a0;
    void *temp_a0_2;
    void *temp_v1_2;
    void *temp_v1_3;
    void *temp_v1_4;
    void *temp_v1_5;

    temp_v1 = M2C_FIELD(arg0, u8 *, 5);
    switch (temp_v1) {                              /* irregular */
    case 0:
        if (D_800BF9BB == 0) {
            M2C_FIELD(arg0, u8 *, 5) = 1U;
            M2C_FIELD(arg0, u16 *, 0x50) = 0U;
        } else {
            M2C_FIELD(arg0, u8 *, 5) = 2U;
        }
        break;
    case 1:
        if (((u8) D_800BF9BB >= 3U) && !(*((u16 *)D_1F80017C) & 3)) {
            temp_v0 = M2C_FIELD(arg0, u16 *, 0x50) + 1;
            M2C_FIELD(arg0, u16 *, 0x50) = temp_v0;
            if ((s16) temp_v0 >= 0xC) {
                M2C_FIELD(arg0, u8 *, 5) = (u8) (M2C_FIELD(arg0, u8 *, 5) + 1);
            }
            temp_a0 = M2C_FIELD(arg0, void **, 0xC0);
            M2C_FIELD(temp_a0, u16 *, 0x3A) = (u16) (M2C_FIELD(temp_a0, u16 *, 0x3A) + M2C_FIELD(arg0, u16 *, 0x50));
            temp_a0_2 = M2C_FIELD(arg0, void **, 0xC4);
            M2C_FIELD(temp_a0_2, u16 *, 0x3A) = (u16) (M2C_FIELD(temp_a0_2, u16 *, 0x3A) - M2C_FIELD(arg0, u16 *, 0x50));
        }
        break;
    case 2:
        temp_v1_2 = M2C_FIELD(arg0, void **, 0xC0);
        M2C_FIELD(temp_v1_2, u16 *, 0x3A) = (u16) (M2C_FIELD(temp_v1_2, u16 *, 0x3A) + 0xC);
        temp_v1_3 = M2C_FIELD(arg0, void **, 0xC4);
        M2C_FIELD(temp_v1_3, u16 *, 0x3A) = (u16) (M2C_FIELD(temp_v1_3, u16 *, 0x3A) - 0xC);
        break;
    }
    temp_v1_4 = M2C_FIELD(arg0, void **, 0xC0);
    if ((u16) M2C_FIELD(temp_v1_4, u16 *, 0x3A) >= 0x780U) {
        M2C_FIELD(temp_v1_4, u16 *, 0x3A) = 0x708U;
    }
    temp_v1_5 = M2C_FIELD(arg0, void **, 0xC4);
    if ((u16) M2C_FIELD(temp_v1_5, u16 *, 0x3A) < 0x691U) {
        M2C_FIELD(temp_v1_5, u16 *, 0x3A) = 0x708U;
    }
    M2C_FIELD(arg0, s8 *, 1) = 1;
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8011A6C4);

extern u8 D_800BF871;
void func_8011A8A0(u8 *a)
{

    if (D_800BF871 == 6) {
        a[0xBF] = 0;
    } else {
        a[0xBF] = 1;
    }
    switch (a[5]) {
    case 0:
        a[5]++;
        *(s16 *)(a + 0x5A) = *(s16 *)(*(u8 **)(a + 0xC0) + 0xA);
        func_80072FE0(a, *(u8 **)(a + 0xC0));
        break;
    case 1:
        if (D_800BF818_7697 == 2) {
            *(s16 *)(a + 0x40) = 0;
            a[5]++;
        }
        break;
    case 2:
        if (++*(s16 *)(a + 0x40) >= 9) {
            if (func_80073194(a, *(u8 **)(a + 0xC0)) != 0) {
                a[5]++;
            }
        }
        break;
    case 3:
        if (D_800BF818_7697 == 3) {
            a[5]++;
        }
        break;
    case 4:
        if (func_8007302C(a, *(u8 **)(a + 0xC0)) != 0) {
            a[5]++;
        }
        break;
    case 5:
        break;
    }
    a[1] = 1;
    func_800517F8(a);
}

extern s16 D_800ED098;
extern u8 D_80141AB7;
extern u8 D_800BFA00;
/* func_8011AFD8, inlined */
static inline void func_8011AFD8_inl(u8 *a) {
    M2C_FIELD(a, void **, 0x3C) = D_800ECF80;
    func_80077B38(a, D_80144360, 4);
    a[0xD] = 1;
    M2C_FIELD(a, s16 *, 0x5C) = 0;
    a[0xB] = 0x10;
    M2C_FIELD(a, s16 *, 0x5A) = 0;
    a[0x47] = 0;
    a[8] = 0;
}
/* func_8011B058, inlined */
static inline void func_8011B058_inl(u8 *a)
{
    *(void **)(a + 0x3C) = D_800ECF80;
    func_80077B38(a, D_80144360, 5);
    a[0xD] = 1;
    a[0xB] = 0x10;
    *(s16 *)(a + 0x5C) = 0;
    *(s16 *)(a + 0x5A) = 0;
    a[0x47] = 0;
    a[8] = 0xF0;
}
/* func_8011B0DC, inlined */
static inline void func_8011B0DC_inl(u8 *a)
{
    if (func_80051B70(a, 0xC, 0x15) == 0) {
        *(s16 *)(a + 0x54) = 0;
        *(s16 *)(a + 0x56) = 0;
        *(s16 *)(a + 0x58) = 0;
    }
}
/* func_8011B11C, inlined */
static inline void func_8011B11C_inl(void *arg0) {
    void *temp_v0;

    if (D_800ED098 < 2) {
        M2C_FIELD(arg0, s8 *, 4) = 3;
        return;
    }
    func_80051B70(arg0, 0xC, 0);
    M2C_FIELD(arg0, s8 *, 0xB) = 7;
    M2C_FIELD(M2C_FIELD(arg0, void **, 0xC0), s16 *, 2) = -0x40;
    M2C_FIELD(M2C_FIELD(arg0, void **, 0xC0), s16 *, 0xC) = -0x700;
    M2C_FIELD(M2C_FIELD(arg0, void **, 0xC0), s16 *, 0x3A) = 0x708;
    temp_v0 = func_8007AAE8();
    M2C_FIELD(arg0, void **, 0xC4) = temp_v0;
    M2C_FIELD(temp_v0, s16 *, 6) = -1;
    M2C_FIELD(M2C_FIELD(arg0, void **, 0xC4), s16 *, 0) = 0;
    M2C_FIELD(M2C_FIELD(arg0, void **, 0xC4), s16 *, 2) = 0x60;
    M2C_FIELD(M2C_FIELD(arg0, void **, 0xC4), s16 *, 4) = 0;
    M2C_FIELD(M2C_FIELD(arg0, void **, 0xC4), s16 *, 8) = 0;
    M2C_FIELD(M2C_FIELD(arg0, void **, 0xC4), s16 *, 0xA) = 0;
    M2C_FIELD(M2C_FIELD(arg0, void **, 0xC4), s16 *, 0xC) = -0x600;
    M2C_FIELD(M2C_FIELD(arg0, void **, 0xC4), s16 *, 0x3A) = 0x708;
    M2C_FIELD(arg0, s16 *, 0x56) = 0xC00;
    M2C_FIELD(arg0, s16 *, 0x54) = 0;
    M2C_FIELD(arg0, s16 *, 0x58) = 0;
    M2C_FIELD(arg0, s8 *, 8) = 2;
    M2C_FIELD(arg0, s8 *, 9) = 2;
    M2C_FIELD(arg0, s16 *, 0x50) = 0;
    func_800517F8(arg0);
    func_8013DE84(arg0);
}
/* func_8011B22C, inlined */
static inline void func_8011B22C_inl(u8 *a) {
    if (func_80051B70(a, 1, 0x13) == 0) {
        M2C_FIELD(a, s16 *, 0x54) = 0x400;
        M2C_FIELD(a, s16 *, 0x56) = 0x800;
        M2C_FIELD(a, s16 *, 0x58) = -0x100;
        M2C_FIELD(a, s16 *, 0x40) = 0x64;
    }
}
/* func_8011B460, inlined */
static inline void func_8011B460_inl(u8 *a) {
    M2C_FIELD(a, void **, 0x3C) = D_800ECF80;
    func_80077B38(a, D_80144360, 7);
    a[0xD] = 1;
    a[0xB] = 0x11;
    a[8] = 0xE0;
    M2C_FIELD(a, s16 *, 0x5C) = 0;
    M2C_FIELD(a, s16 *, 0x5A) = 0;
    a[0x47] = 0;
    M2C_FIELD(a, s16 *, 0x7A) = 0x1000;
    M2C_FIELD(a, s16 *, 0x7C) = 0x1000;
    M2C_FIELD(a, s16 *, 0x7E) = 0x1000;
}
/* func_8011B538, inlined */
static inline void func_8011B538_inl(u8 *a) {
    if (func_80051B70(a, 0xC, D_80141AB7) == 0) {
        M2C_FIELD(a, s16 *, 0x54) = 0;
        M2C_FIELD(a, s16 *, 0x56) = 0;
        M2C_FIELD(a, s16 *, 0x58) = 0;
    }
}
/* func_8011B618, inlined */
static inline void func_8011B618_inl(u8 *a) {
    if (func_80051B70(a, 0xC, 0x12) == 0) {
        M2C_FIELD(a, s16 *, 0x54) = 0;
        M2C_FIELD(a, s16 *, 0x56) = 0;
        M2C_FIELD(a, s16 *, 0x58) = 0;
        a[0xD] |= 4;
        M2C_FIELD(a, u8 **, 0xC0)[0x3F] = 0x30;
        a[0x46] = 0;
    }
}
/* func_8011B57C, inlined */
static inline void func_8011B57C_inl(u8 *a)
{
    u8 *t = D_800E7E80;

    *(s16 *)(a + 0x2E) = *(s16 *)(t + 0x2E);
    *(s16 *)(a + 0x32) = *(s16 *)(t + 0x32);
    *(s16 *)(a + 0x36) = *(s16 *)(t + 0x36);
    *(s16 *)(a + 0x56) = *(s16 *)(t + 0x140);
    *(s16 *)(a + 0x58) = *(s16 *)(t + 0x58);
    if (t[0x29] != 0) {
        func_8003116C(0x506, a + 0x2C, -0x32);
        a[4] = 3;
    }
    if (func_8007778C(a) != 0) {
        func_800517F8(a);
    }
}
void func_8011A9E4(u8 *a)
{
    s16 v[6];
    u8 *p;
    u8 *q;

    switch (a[4]) {
    case 0:
        a[4] = 1;
        switch (a[3]) {
        case 0:
            func_8011AFD8_inl(a);
            break;
        case 1:
            func_8011B058_inl(a);
            break;
        case 2:
            func_8011B0DC_inl(a);
            break;
        case 3:
            func_8011B11C_inl(a);
            break;
        case 4:
            func_8011B22C_inl(a);
            break;
        case 5:
            if (func_80051B70(a, 0xC, 0x19) != 0) {
                break;
            }
            if (D_800ED098 <= 0) {
                a[4] = 3;
                break;
            }
            a[8] = 2;
            a[9] = 2;
            {
                u8 *n = func_8007AAE8();
                *(u8 **)(a + 0xC4) = n;
                *(s16 *)(n + 6) = -1;
            }
            *(s16 *)(*(u8 **)(a + 0xC4) + 0) = 0x32;
            *(s16 *)(*(u8 **)(a + 0xC4) + 2) = 0;
            *(s16 *)(*(u8 **)(a + 0xC4) + 4) = 0;
            *(s16 *)(*(u8 **)(a + 0xC4) + 8) = 0;
            *(s16 *)(*(u8 **)(a + 0xC4) + 0xA) = 0;
            *(s16 *)(*(u8 **)(a + 0xC4) + 0xC) = 0;
            *(s16 *)(*(u8 **)(a + 0xC4) + 0x38) = 0x1770;
            *(s16 *)(*(u8 **)(a + 0xC4) + 0x3A) = 0x1000;
            *(s16 *)(*(u8 **)(a + 0xC4) + 0x3C) = 0x1770;
            func_80051B04(*(u8 **)(a + 0xC4), 0x12, 0);
            *(s16 *)(a + 0x56) = -0xFA;
            break;
        case 6:
            func_8011B460_inl(a);
            break;
        case 7:
            func_8011B538_inl(a);
            break;
        case 8:
            func_8011B618_inl(a);
            break;
        }
        break;
    case 1:
        switch (a[3]) {
        case 0:
        case 1:
            a[1] = 1;
            func_80077B5C(a);
            break;
        case 2:
            func_8011A3C0(a);
            break;
        case 3:
            func_8011A554(a);
            break;
        case 4:
            if (D_800BFA00 >= 3) {
                a[4] = 2;
            } else if (--*(s16 *)(a + 0x40) <= 0) {
                v[1] = *(u16 *)(*(u8 **)(a + 0xC0) + 0x2C) + (*(s16 *)(*(u8 **)(a + 0xC0) + 0x18) >> 5);
                v[3] = *(u16 *)(*(u8 **)(a + 0xC0) + 0x30) + (*(s16 *)(*(u8 **)(a + 0xC0) + 0x1E) >> 5);
                v[5] = *(u16 *)(*(u8 **)(a + 0xC0) + 0x34) + (*(s16 *)(*(u8 **)(a + 0xC0) + 0x24) >> 5);
                q = func_8003116C(0x14, v, -0x32);
                if (q != NULL) {
                    q[0x28] |= 0x80;
                }
                *(s16 *)(a + 0x40) = (func_8009A450() & 0x3F) + 0x78;
            }
            a[1] = 1;
            func_800517F8(a);
            break;
        case 5:
            func_8011A6C4(a);
            break;
        case 6:
            func_8007778C(a);
            break;
        case 7:
            func_8011B57C_inl(a);
            break;
        case 8:
            func_8011A8A0(a);
            break;
        }
        break;
    case 2:
        break;
    default:
        func_8007A624(a);
        break;
    }
}

extern u16 D_800E7E68;
extern u16 D_1F800174;
void func_8011AFD8(u8 *a) {
    M2C_FIELD(a, void **, 0x3C) = D_800ECF80;
    func_80077B38(a, D_80144360, 4);
    a[0xD] = 1;
    M2C_FIELD(a, s16 *, 0x5C) = 0;
    a[0xB] = 0x10;
    M2C_FIELD(a, s16 *, 0x5A) = 0;
    a[0x47] = 0;
    a[8] = 0;
}

void func_8011B034(void *arg0) {
    M2C_FIELD(arg0, s8 *, 1) = 1;
    func_80077B5C();
}

void func_8011B058(u8 *a)
{
    *(void **)(a + 0x3C) = D_800ECF80;
    func_80077B38(a, D_80144360, 5);
    a[0xD] = 1;
    a[0xB] = 0x10;
    *(s16 *)(a + 0x5C) = 0;
    *(s16 *)(a + 0x5A) = 0;
    a[0x47] = 0;
    a[8] = 0xF0;
}

void func_8011B0B8(void *arg0) {
    M2C_FIELD(arg0, s8 *, 1) = 1;
    func_80077B5C();
}

void func_8011B0DC(u8 *a)
{
    if (func_80051B70(a, 0xC, 0x15) == 0) {
        *(s16 *)(a + 0x54) = 0;
        *(s16 *)(a + 0x56) = 0;
        *(s16 *)(a + 0x58) = 0;
    }
}

void func_8011B11C(void *arg0) {
    void *temp_v0;

    if (D_800ED098 < 2) {
        M2C_FIELD(arg0, s8 *, 4) = 3;
        return;
    }
    func_80051B70(arg0, 0xC, 0);
    M2C_FIELD(arg0, s8 *, 0xB) = 7;
    M2C_FIELD(M2C_FIELD(arg0, void **, 0xC0), s16 *, 2) = -0x40;
    M2C_FIELD(M2C_FIELD(arg0, void **, 0xC0), s16 *, 0xC) = -0x700;
    M2C_FIELD(M2C_FIELD(arg0, void **, 0xC0), s16 *, 0x3A) = 0x708;
    temp_v0 = func_8007AAE8();
    M2C_FIELD(arg0, void **, 0xC4) = temp_v0;
    M2C_FIELD(temp_v0, s16 *, 6) = -1;
    M2C_FIELD(M2C_FIELD(arg0, void **, 0xC4), s16 *, 0) = 0;
    M2C_FIELD(M2C_FIELD(arg0, void **, 0xC4), s16 *, 2) = 0x60;
    M2C_FIELD(M2C_FIELD(arg0, void **, 0xC4), s16 *, 4) = 0;
    M2C_FIELD(M2C_FIELD(arg0, void **, 0xC4), s16 *, 8) = 0;
    M2C_FIELD(M2C_FIELD(arg0, void **, 0xC4), s16 *, 0xA) = 0;
    M2C_FIELD(M2C_FIELD(arg0, void **, 0xC4), s16 *, 0xC) = -0x600;
    M2C_FIELD(M2C_FIELD(arg0, void **, 0xC4), s16 *, 0x3A) = 0x708;
    M2C_FIELD(arg0, s16 *, 0x56) = 0xC00;
    M2C_FIELD(arg0, s16 *, 0x54) = 0;
    M2C_FIELD(arg0, s16 *, 0x58) = 0;
    M2C_FIELD(arg0, s8 *, 8) = 2;
    M2C_FIELD(arg0, s8 *, 9) = 2;
    M2C_FIELD(arg0, s16 *, 0x50) = 0;
    func_800517F8(arg0);
    func_8013DE84(arg0);
}

void func_8011B22C(u8 *a) {
    if (func_80051B70(a, 1, 0x13) == 0) {
        M2C_FIELD(a, s16 *, 0x54) = 0x400;
        M2C_FIELD(a, s16 *, 0x56) = 0x800;
        M2C_FIELD(a, s16 *, 0x58) = -0x100;
        M2C_FIELD(a, s16 *, 0x40) = 0x64;
    }
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8011B27C);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8011B378);

void func_8011B460(u8 *a) {
    M2C_FIELD(a, void **, 0x3C) = D_800ECF80;
    func_80077B38(a, D_80144360, 7);
    a[0xD] = 1;
    a[0xB] = 0x11;
    a[8] = 0xE0;
    M2C_FIELD(a, s16 *, 0x5C) = 0;
    M2C_FIELD(a, s16 *, 0x5A) = 0;
    a[0x47] = 0;
    M2C_FIELD(a, s16 *, 0x7A) = 0x1000;
    M2C_FIELD(a, s16 *, 0x7C) = 0x1000;
    M2C_FIELD(a, s16 *, 0x7E) = 0x1000;
}

void func_8011B4D0(void) {
    func_8007778C();
}

void func_8011A9E4();
void func_8011C3BC();
void func_8011BF60();
void func_8013A8E4();
u8 *func_8011B4F0(s32 a) {
    u8 *p = func_80072DDC(a, 1, 3, 16);

    if (p == NULL) {
        return NULL;
    }
    M2C_FIELD(p, void **, 0x1C) = func_8011A9E4;
    p[0x3] = 7;
    return p;
}

void func_8011B538(u8 *a) {
    if (func_80051B70(a, 0xC, D_80141AB7) == 0) {
        M2C_FIELD(a, s16 *, 0x54) = 0;
        M2C_FIELD(a, s16 *, 0x56) = 0;
        M2C_FIELD(a, s16 *, 0x58) = 0;
    }
}

void func_8011B57C(u8 *a)
{
    u8 *t = D_800E7E80;

    *(s16 *)(a + 0x2E) = *(s16 *)(t + 0x2E);
    *(s16 *)(a + 0x32) = *(s16 *)(t + 0x32);
    *(s16 *)(a + 0x36) = *(s16 *)(t + 0x36);
    *(s16 *)(a + 0x56) = *(s16 *)(t + 0x140);
    *(s16 *)(a + 0x58) = *(s16 *)(t + 0x58);
    if (t[0x29] != 0) {
        func_8003116C(0x506, a + 0x2C, -0x32);
        a[4] = 3;
    }
    if (func_8007778C(a) != 0) {
        func_800517F8(a);
    }
}

void func_8011B618(u8 *a) {
    if (func_80051B70(a, 0xC, 0x12) == 0) {
        M2C_FIELD(a, s16 *, 0x54) = 0;
        M2C_FIELD(a, s16 *, 0x56) = 0;
        M2C_FIELD(a, s16 *, 0x58) = 0;
        a[0xD] |= 4;
        M2C_FIELD(a, u8 **, 0xC0)[0x3F] = 0x30;
        a[0x46] = 0;
    }
}

void func_8011B674(u8 *a)
{
    u8 *g;

    switch (a[4]) {
    case 0:
        if (func_80051B70(a, 0xC, 0x2F) != 0) {
            break;
        }
        *(s16 *)(a + 0x88) = -0x5A;
        *(s16 *)(a + 0x8A) = 0x4B;
        *(s16 *)(a + 0x80) = 0x3C;
        *(s16 *)(a + 0x82) = 0x78;
        *(s16 *)(a + 0x84) = 0x96;
        *(s16 *)(a + 0x8C) = 0;
        *(s16 *)(a + 0x86) = 0x64;
        a[0x29] = 0;
        *(s16 *)(a + 0x58) = 0;
        *(s16 *)(a + 0x56) = 0;
        *(s16 *)(a + 0x54) = 0;
        func_800517F8(a);
        a[4]++;
        break;
    case 1:
        if (D_800BFA00 == 2) {
            a[4] = 3;
            break;
        }
        g = D_800E7E80;
        if (g[0x6E] == 0) {
            a[1] = g[1];
            func_80051614(a, a + 0x88, 0, 0);
        }
        break;
    case 2:
    case 3:
        func_8007A624(a);
        break;
    }
}

u8 *func_8011B79C(void) {
    u8 *p = func_8007A980(1, 3, 1);

    if (p == NULL) {
        return NULL;
    }
    p[0x2] = 18;
    p[0x3] = 0;
    M2C_FIELD(p, void **, 0x1C) = func_8011B674;
    p[0x28] = (p[0x28] | 0x80);
    return p;
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8011B7F4);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8011B958);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8011BB48);

void func_8011B958();
void func_8011BB48();
u8 *func_8011BDFC(u8 *a, s32 b) {
    u8 *p = func_80072DDC(0, 0, 3, 0x18);

    if (p != NULL) {
    M2C_FIELD(p, void **, 0x1C) = func_8011B958;
    p[3] = b;
    M2C_FIELD(p, u8 **, 0x10) = a;
        return p;
    }
    return NULL;
}

extern u8 D_1F8000F8[];
void func_8011BE5C(u8 *a)
{
    s32 pad[2];
    s32 v[3];
    s32 d, s;

    func_80084660(D_1F8000F8);
    func_80084690(D_1F8000F8);
    v[2] = func_8003F7A0(a + 0x60, &v[0]);
    d = func_8003F7A0(a + 0x68, &v[1]);
    s = d >> 10;
    v[2] = (d >> s) + (s << 9);
    if ((u32)(v[2] - 4) >= 0x7FC) {
        v[2] = -1;
    }
    if (v[2] > 0) {
        func_8011B7F4(v[0], v[1], v[2]);
    }
}

u8 *func_8011BF00(u8 *a, s32 b) {
    u8 *p = func_80072DDC(0, 0, 3, 0x18);

    if (p != NULL) {
    M2C_FIELD(p, void **, 0x1C) = func_8011BB48;
    p[3] = b;
    M2C_FIELD(p, u8 **, 0x10) = a;
        return p;
    }
    return NULL;
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8011BF60);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8011C204);

u8 *func_8011C31C(s32 a) {
    u8 *p = func_80072DDC(a, 1, 3, 40);

    if (p != NULL) {
        M2C_FIELD(p, void **, 0x1C) = func_8011C3BC;
        p[0x28] = (p[0x28] | 0x80);
    }
    return p;
}

u8 *func_8011C364(s32 a, s32 b) {
    u8 *p = func_80072DDC(a, 0, 3, 39);

    if (p != NULL) {
        M2C_FIELD(p, void **, 0x1C) = func_8011BF60;
        p[0x5] = b;
        p[0x28] = (p[0x28] | 0x80);
    }
    return p;
}

void func_8011C3BC(u8 *a)
{
    u8 *p = *(u8 **)(a + 0x10);

    switch (a[4]) {
    case 0:
        if (func_80051B70(a, 0xC, 0x32) != 0) {
            break;
        }
        *(s16 *)(a + 0x54) = 0;
        *(s16 *)(a + 0x56) = 0;
        *(s16 *)(a + 0x58) = 0;
        a[4]++;
        *(s16 *)(a + 0x2E) = *(s16 *)(p + 0x2E);
        *(s16 *)(a + 0x32) = *(s16 *)(p + 0x32) + 0xCD;
        *(s16 *)(a + 0x36) = *(s16 *)(p + 0x36);
    case 1:
        if (D_800BF816 == 0) {
            a[4] = 3;
            break;
        }
        *(s16 *)(a + 0x2E) = *(s16 *)(p + 0x2E);
        *(s16 *)(a + 0x32) = *(s16 *)(p + 0x32) + 0xCD;
        *(s16 *)(a + 0x36) = *(s16 *)(p + 0x36);
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

extern u8 D_800BF9B4;
extern u8 D_800BF841;
#define AH(o) (*(s16 *)(a + (o)))
void func_8011C4E0(u8 *a)
{
    u8 *c = D_800E8008;
    u8 *d;
    s32 v;

    switch (a[5]) {
    case 0:
        if (D_800BF9B4 & 0x10) {
            AH(0x86) = 0x7D0;
            AH(0xBA) = 0x1400;
            a[5] = 7;
        } else {
            a[5]++;
        }
        break;
    case 1:
        if (a[0x2B] != 0) {
            D_1F800137_104c = 2;
            D_800BF841 = 1;
            D_800BF870.pad1[0x143] |= 0x10;
            AH(0x40) = 10;
            a[5]++;
            c[0x64] = 8;
            d = D_1F8000D0;
            {
                s16 x = AH(0x2E) - *(s16 *)(d + 0xE);
                s16 z = AH(0x36) - *(s16 *)(d + 0x16);
                *(s16 *)(d + 2) += x;
                *(s16 *)(d + 0xA) += z;
            }
            func_8006CBA8(a + 0x2C);
        }
        break;
    case 2:
        func_8006CBA8(a + 0x2C);
        **(s16 **)(a + 0xC0) = (D_1F80017C_0fe7 & 1) * 6;
        v = func_8009A450();
        *(s16 *)(*(u8 **)(a + 0xC0) + 4) = ((v & 3) - 2) * 6;
        if (--AH(0x40) == 0) {
            AH(0x40) = 0x10;
            a[5]++;
        }
        break;
    case 3:
        if (--AH(0x40) == 0) {
            AH(0x40) = 0x10;
            a[5]++;
        }
        break;
    case 4:
        *(s16 *)(c + 0x3E) += 100;
        if (--AH(0x40) == 0) {
            a[5]++;
            **(s16 **)(a + 0xC0) = 0;
            *(s16 *)(*(u8 **)(a + 0xC0) + 4) = 0;
            AH(0x40) = 8;
        }
        break;
    case 5:
        AH(0xBA) += 0x80;
        if (--AH(0x40) == 0) {
            AH(0x40) = 0x10;
            AH(0x86) = 0x7D0;
            a[5]++;
        }
        break;
    case 6:
        if (--AH(0x40) == 0) {
            a[5]++;
            D_1F800137_104c = 0;
            D_800BF841 = 0;
            c[0x64] = 0;
        }
        break;
    case 7:
        break;
    }
}

extern s16 D_80141318[][3];
extern u16 D_1F800162_b816;
void func_8011C784(u8 *a)
{
    u8 *st;

    switch (a[4]) {
    case 0:
        if (a[3] == 3) {
            if (func_80051B70(a, 0xC, 0x23) != 0) {
                break;
            }
            st = (u8 *)&D_800BF870;
            if ((*(u16 *)(st + 0x5E6) >> st[0]) & 1) {
                *(s32 *)(*(u8 **)(a + 0xC0) + 0x40) = 0;
                st[0x144] |= 0x10;
            }
        } else {
            if (func_80051B70(a, 0xC, 0) != 0) {
                break;
            }
            *(s32 *)(*(u8 **)(a + 0xC0) + 0x40) = 0;
        }
        a[0] = 1;
        a[4]++;
        *(s16 *)(a + 0x80) = D_80141318[a[3]][0];
        *(s16 *)(a + 0x82) = *(s16 *)(a + 0x80) * 2;
        *(s16 *)(a + 0x84) = D_80141318[a[3]][1];
        *(s16 *)(a + 0x86) = D_80141318[a[3]][2];
        a[0x2B] = 0;
        func_800517F8(a);
        if (a[3] == 0 && (D_800BFE56 & 0x10)) {
            *(s16 *)(a + 0x86) += 0x12C;
        }
        break;
    case 1:
        func_800778E4(a, (s16)(D_1F800162_b816 - *(u16 *)(a + 0x32)));
        if (a[3] == 3) {
            func_8011C4E0(a);
            func_80051844(a);
            a[0x2B] = 0;
        }
        break;
    case 2:
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

typedef struct { s16 x, y, z; } AreaVec3s;
extern AreaVec3s D_80141344[];
void func_8011C974(u8 *a) {
    s16 i;

    switch (a[6]) {
    case 0:
        if (--M2C_FIELD(a, s16 *, 0x40) <= 0) {
            a[6]++;
        }
        break;
    case 1:
        if (!(*(u16 *)D_1F80017C & 0xF)) {
            M2C_FIELD(a, s16 *, 0xB8) = D_80141344[M2C_FIELD(a, s16 *, 0x7A)].x;
            M2C_FIELD(a, s16 *, 0xBA) = D_80141344[M2C_FIELD(a, s16 *, 0x7A)].y;
            M2C_FIELD(a, s16 *, 0xBC) = D_80141344[M2C_FIELD(a, s16 *, 0x7A)].z;
            M2C_FIELD(a, s16 *, 0x7A) = (M2C_FIELD(a, s16 *, 0x7A) + 1) & 7;
        }
        break;
    }
    if ((s16)func_8011D504(a)) {
        func_8011D414(a, 0);
        a[5] = 3;
        a[6] = 0;
        M2C_FIELD(a, s16 *, 0x6C) = 0;
    }
}

#define F16(p, o) M2C_FIELD(p, s16 *, o)
#define C0(p) M2C_FIELD(p, u8 **, 0xC0)
void func_8011CA8C(u8 *a)
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
            if (M2C_FIELD(g, s32 *, 0x5C) == 0) {
                func_8004CBD8(a, 7);
                M2C_FIELD(g, s32 *, 0x5C) = s;
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

void func_8011CCE8(u8 *a)
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
            func_8011D414(a, a[0x5E]);
            a[6] = 1;
            M2C_FIELD(a, s16 *, 0x6C) = 1;
        }
    } else if ((s16)func_8011D504(a)) {
        M2C_FIELD(*(u8 **)(a + 0xC0), u16 *, 0x38) = M2C_FIELD(a, s16 *, 0x64);
        M2C_FIELD(*(u8 **)(a + 0xC0), u16 *, 0x3A) = M2C_FIELD(a, s16 *, 0x66);
        func_8011D414(a, 0);
        a[6] = 0;
        M2C_FIELD(a, s16 *, 0x6C) = 0;
    }
    if (M2C_FIELD(a, s16 *, 0x50) > 0x20) {
        M2C_FIELD(a, s16 *, 0x50)--;
    }
    func_8011D568(a);
}

void func_8011CF80(void *arg0) {
    u8 temp_v1;
    u8 temp_v1_2;

    temp_v1 = M2C_FIELD(arg0, u8 *, 4);
    switch (temp_v1) {                              /* switch 1; irregular */
    case 0:                                         /* switch 1 */
        func_8011D13C(arg0);
        return;
    case 1:                                         /* switch 1 */
        func_8007778C(arg0);
        temp_v1_2 = M2C_FIELD(arg0, u8 *, 5);
        switch (temp_v1_2) {                        /* switch 2; irregular */
        case 0:                                     /* switch 2 */
            func_8011C974(arg0);
            break;
        case 3:                                     /* switch 2 */
            func_8011CCE8(arg0);
            break;
        case 4:                                     /* switch 2 */
            func_8011D230(arg0);
            break;
        }
        func_8011D354(arg0);
        func_8011CA8C(arg0);
        M2C_FIELD(arg0, s8 *, 0x29) = 0;
        if (M2C_FIELD(arg0, u8 *, 1) != 0) {
            func_800518FC(arg0);
            return;
        }
        return;
    case 2:                                         /* switch 1 */
        func_8011D280(arg0);
        return;
    case 3:                                         /* switch 1 */
        func_8007A624(arg0);
        break;
    }
}

extern u8 D_800BF9CC;
void func_8011CF80();
void func_80138140();
s32 func_8011D0A4(u8 *a)
{
    u8 *p;

    if (D_800BF9CC & 0x40) {
        return 0;
    }
    {
        p = func_80072DDC(a, 1, 4, 3);
        if (p != NULL) {
            p[3] = 6;
            *(void **)(p + 0x1C) = func_8011CF80;
            p[0x2A] = a[0x2A];
            *(s16 *)(p + 0x2E) = *(s16 *)(a + 0x2E);
            *(s16 *)(p + 0x32) = *(s16 *)(a + 0x32);
            *(s16 *)(p + 0x36) = *(s16 *)(a + 0x36);
            return 1;
        }
    }
    return 0;
}

extern s16 D_1F8001A0;
extern s16 D_1F8001A2;
void func_8011D13C(u8 *a)
{
    if (func_80051B70(a, 0xC, 0x22) == 0) {
        u8 *c;
        a[0xB] = 0xF;
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
        func_8011D568(a);
        if (func_80048894(a) != 0) {
            u16 z = D_1F8001A4;
            u16 x = D_1F8001A0;
            u16 y = D_1F8001A2;
            H(a, 0x32) = z;
            H(a, 0x56) = x;
            H(a, 0x58) = y & 0xFFF;
        }
        func_800518FC(a);
    }
}

void func_8011D230(u8 *a)
{
    if (a[0x29] == 0) {
        func_8011D414(a, 1);
        a[5] = 3;
        a[6] = 1;
        *(s16 *)(a + 0x6C) = 1;
    }
}

void func_8011D280(u8 *a) {
    func_80027144(M2C_FIELD(M2C_FIELD(a, u8 **, 0xC0), s32 *, 0x40), a + 0x2C, 0xA00, 0x24);
    func_80074590(0xC, 0, 0);
    M2C_FIELD(a, s16 *, 0x32) -= 0x96;
    func_80027144(M2C_FIELD(M2C_FIELD(a, u8 **, 0xC0), s32 *, 0x40), a + 0x2C, 0xA00, 0x2C);
    func_80074590(0xC, 0, 0);
    if (func_80040B48(0x7F) >= 0) {
        D_800BF870.pad1[0x15B] |= 0x40;
        if (++D_800BF870.pad1[0x1C0] >= 10) {
            func_8004ED94(0x6E, 0x41);
        }
    }
    a[4] = 3;
}

#define F16(p, o) M2C_FIELD(p, s16 *, o)
#define C0(p) M2C_FIELD(p, u8 **, 0xC0)
void func_8011D354(u8 *a)
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

void func_8011D414(u8 *a, s16 b)
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

s32 func_8011D504(u8 *a)
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

void func_8011D568(void *arg0) {
    s32 temp_v0_2;
    u32 temp_v0;

    temp_v0 = (u16) M2C_FIELD(M2C_FIELD(arg0, void **, 0xC0), u16 *, 0x38) >> 5;
    M2C_FIELD(arg0, s16 *, 0x80) = (s16) temp_v0;
    M2C_FIELD(arg0, s16 *, 0x82) = (s16) (temp_v0 * 2);
    temp_v0_2 = (s32) (M2C_FIELD(M2C_FIELD(arg0, void **, 0xC0), u16 *, 0x3A) * 0x113) >> 0xC;
    M2C_FIELD(arg0, s16 *, 0x84) = (s16) temp_v0_2;
    M2C_FIELD(arg0, s16 *, 0x86) = (s16) (temp_v0_2 + 0x32);
}

extern u8 D_800ECF58[];
extern u8 D_8014005C[];
extern u8 D_1F800207_9c67;
extern s16 D_1F800162_a8d4;
extern u8 D_1F80027A;
void func_8011D5BC(u8 *a)
{
    s32 d;
    s16 h;

    switch (a[4]) {
    case 0:
        if (func_80051B70(a, 0xC, 0x16) != 0) {
            break;
        }
        *(s16 *)(a + 0x56) = 0xC00;
        *(s16 *)(a + 0x80) = 0x1A7;
        *(s16 *)(a + 0x82) = 0x34E;
        *(s16 *)(a + 0x84) = 0x3E;
        a[0] = 1;
        *(s16 *)(a + 0x86) = 0x72;
        a[0x2B] = 0;
        a[0x29] = 0;
        *(s16 *)(a + 0x60) = 0;
        *(s16 *)(a + 0x96) = 0;
        a[0xBF] = 0;
        a[0x46] = 0;
        *(s16 *)(a + 0x40) = 0;
        a[4]++;
        break;
    case 1:
        if (func_8007778C(a) == 0 && (u32)(D_1F800207_9c67 - 0xF) < 4 && D_1F800162_a8d4 < -0x2648) {
            func_8007703C(a);
        }
        if (D_1F80027A != 0) {
            break;
        }
        if (a[1] != 0) {
            h = *(s16 *)(a + 0x44);
            if (h != 0) {
                d = h >> 8;
                if (h < -0x20) {
                    *(s16 *)(a + 0x44) = h + 0x20;
                } else if (h > 0x20) {
                    *(s16 *)(a + 0x44) = h - 0x20;
                } else {
                    *(s16 *)(a + 0x44) = 0;
                }
            } else {
                d = 0;
            }
            if (a[0x29] != 0) {
                d += *(s16 *)(a + 0x60) * 40 / *(s16 *)(a + 0x80);
                d >>= 2;
            }
            if (d != 0) {
                *(s16 *)(*(u8 **)(a + 0xC0) + 0xC) += d;
                if (d > 0) {
                    if (*(s16 *)(*(u8 **)(a + 0xC0) + 0xC) >= 0x200) {
                        *(s16 *)(*(u8 **)(a + 0xC0) + 0xC) = 0x1FF;
                    }
                    if (a[0x46] != 1) {
                        a[0xBF] = 0;
                        a[0x46] = 1;
                    }
                } else {
                    if (*(s16 *)(*(u8 **)(a + 0xC0) + 0xC) < -0x1FF) {
                        *(s16 *)(*(u8 **)(a + 0xC0) + 0xC) = -0x1FF;
                    }
                    if (a[0x46] != 0xFF) {
                        a[0xBF] = 0;
                        a[0x46] = 0xFF;
                    }
                }
                if (a[0xBF] == 0) {
                    func_80074590(0x89, 0, 0);
                    a[0xBF] = 1;
                }
            } else {
                a[0xBF] = 0;
            }
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

extern u8 D_800BF80F;
s32 func_8011D878(u8 *a)
{
    u8 *t = D_800E7E80;

    switch (a[6]) {
    case 0:
        if (a[0x29] != 0 && (s8)D_800BF808_1760[5] == 0) {
            a[6]++;
            D_800BF808_1760[0x39] = 1;
            D_800BF808_1760[0x10] = 1;
            D_800BF808_1760[0xF] = a[3];
        }
        break;
    case 1:
        if (D_800BF816 != 0) {
            a[6]++;
        }
        break;
    case 2:
        if (D_800BF808_1760[0x10] == 2 && D_800BF808_1760[7] == 0) {
            a[6]++;
        }
        break;
    case 3:
        if (*(s16 *)(a + 0x32) + *(s16 *)(a + 0x84) + 200 < *(s16 *)(t + 0x32)) {
            a[6]++;
        }
        break;
    case 4:
        if (a[0x29] != 0 && D_800BF808_1760[7] == 0) {
            a[6]++;
            D_800BF808_1760[0x39] = 1;
            D_800BF808_1760[0x10] = 3;
        }
        break;
    case 5:
        if (D_800BF808_1760[0x10] == 4) {
            a[6]++;
            D_800BF808_1760[0x10] = 0;
        }
        break;
    case 6:
        if (D_800BF80F == 0) {
            a[6] = 0;
            return 1;
        }
        break;
    }
    if (a[6] >= 4) {
        a[0x29] = 0;
    }
    return 0;
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8011DA24);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8011DCE4);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8011DEF4);

extern u8 D_800BF816;
void func_8011E4CC(void *arg0) {
    if (D_800BF816 == 0) {
        M2C_FIELD(arg0, u16 *, 0x32) = (u16) M2C_FIELD(arg0, u16 *, 0x7E);
    } else {
        M2C_FIELD(arg0, u16 *, 0x32) = (u16) (M2C_FIELD(arg0, u16 *, 0x7E) + 0x12C);
    }
    func_8011D878(arg0);
    func_800735F4(arg0, 0x56);
}

void func_8011E528(s32 arg0) {
    func_80073328();
    func_800735F4(arg0, 0x59);
}

extern u8 D_800E7FF4;
void func_8011E558(s32 arg0) {
    if (D_800E7FF4 & 4) {
        func_80073328();
    }
    func_800735F4(arg0, 0x67);
}

extern u8 D_800BF917;
void func_8011E59C(u8 *a) {
    switch (a[0x5E]) {
    case 0:
        switch (a[5]) {
        case 0:
            if (D_800BF917 == 1) {
                a[5] = 1;
                func_800313A0(0x510, a + 0x2C, -0x20, a + 0x54);
                func_80074590(0xD, -0x1D, 0);
            }
            break;
        case 1:
            if (D_800BF917 >= 2) {
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
        func_8011DA24(a);
        func_800735F4(a, 0x6B);
        break;
    case 2:
        func_8011DCE4(a);
        func_800735F4(a, 0x6B);
        break;
    }
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8011E6AC);

extern s16 D_801413C0[];
#define P (*(s16 **)(a + 0xC0))
void func_8011E764(u8 *a)
{
    u8 *g;

    switch (a[4]) {
    case 0:
        if (func_80051B70(a, 0xC, D_801413C0[a[3]]) != 0) {
            break;
        }
        *(s16 *)(a + 0x80) = 0x1E;
        *(s16 *)(a + 0x82) = 0x3C;
        *(s16 *)(a + 0x84) = 0x32;
        *(s16 *)(a + 0x86) = 0x64;
        a[0] = 1;
        a[0x29] = 0;
        *(s16 *)(a + 0x56) = 0xC00;
        a[4]++;
        P[5] = -0xC00;
        if (a[3] == 0) {
            *(s16 *)(a + 0x60) = 0x117;
        } else if (a[3] == 1) {
            *(s16 *)(a + 0x60) = 0x158;
        } else {
            *(s16 *)(a + 0x60) = 0x1C0;
        }
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
            P[5] -= 0xC00;
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

typedef struct { u8 pad[7]; u8 unk7; u8 pad8[0x29]; u8 unk31; s16 unk32; } S808b;
extern S808b D_800BF808_d7f4;
extern u16 D_800BF89E;
extern s8 D_800BFA2B;
extern s16 D_801003F8;
extern u8 D_1F800236;
void func_8011E988(u8 *a)
{
    u8 *p = D_800E7E80;
    u8 *q = D_800E8008;
    S808b *g;

    switch (a[5]) {
    case 0:
        if (a[0x29] != 0 && p[0x29] != 0 && p[0x17B] == 0) {
            if (D_800BF89E & 0x200) {
                a[5]++;
                D_1F800137_104c = 2;
                func_80054198(p, q);
                p[4] = 4;
                p[5] = 0x21;
                p[6] = 0;
                func_80054D14(p, 2, 0);
            }
            func_80040B48(0x7C);
        }
        break;
    case 1:
        a[5]++;
        q[0x64] = 1;
        *(s16 *)(q + 0x6E) = 0x80;
        *(s16 *)(q + 0x70) = -0x200;
        *(s16 *)(q + 0x6C) = D_801003F8 * 5;
        func_8006CBA8(a + 0x2C, q);
        break;
    case 2:
        if (q[0x66] == 3 && func_80041438(p, (s16)(*(s16 *)(p + 0x140) + 0x800), 0x100) != 0) {
            *(s16 *)(a + 0x40) = 0x18;
            *(s16 *)(a + 0x44) = 0;
            a[5]++;
        }
        break;
    case 3:
        if (*(s16 *)(a + 0x40) == 0) {
            if (func_80042728() != 0) {
                a[5]++;
                func_8005082C(0, 0, 0);
                D_1F800236 = 0;
                g = &D_800BF808_d7f4;
                g->unk31 = 1;
                g->unk7 = 2;
                g->unk32 = 0x602;
                D_800BFA2B = 1;
            }
        } else {
            *(s16 *)(a + 0x40) -= 1;
            *(s32 *)(p + 0x2C) -= *(s16 *)(p + 0x48) * *(s16 *)(a + 0x44);
            *(s32 *)(p + 0x34) -= *(s16 *)(p + 0x4C) * *(s16 *)(a + 0x44);
            if (*(s16 *)(a + 0x44) < 0x2000) {
                *(s16 *)(a + 0x44) += 0x200;
            }
        }
        break;
    case 4:
        break;
    }
}

void func_8011EBD8(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 4);
    switch (temp_v1) {                              /* irregular */
    case 0:
        M2C_FIELD(arg0, u8 *, 4) = 1U;
        M2C_FIELD(arg0, s8 *, 0) = 1;
        if (M2C_FIELD(arg0, u8 *, 3) == 0) {
            M2C_FIELD(arg0, s16 *, 0x80) = 0x40;
            M2C_FIELD(arg0, s16 *, 0x82) = 0x80;
            M2C_FIELD(arg0, s16 *, 0x84) = 0xC8;
            M2C_FIELD(arg0, s16 *, 0x86) = 0x190;
        }
        M2C_FIELD(arg0, s8 *, 0x29) = 0;
        func_8004766C(arg0);
        return;
    case 1:
        if (M2C_FIELD(arg0, u8 *, 3) == 0) {
            func_8011E988(arg0);
        }
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

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8011ECB0);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8011F0CC);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8011F3CC);

typedef struct { s16 x0; s16 id; u8 k; u8 p5; s16 v6; s16 v8; } Entry10;
extern Entry10 D_80141414[];
void D_80040558();
s32 func_8011F5FC(u8 *a, s32 i)
{
    Entry10 *t = D_80141414;
    Entry10 *e = &t[i];
    u8 *p;

    if (func_8004D7EC(e->id, 1)) {
        return 0;
    }
    p = func_80072DDC(a, 2, 2, 8);
    if (p != NULL) {
        *(void **)(p + 0x1C) = D_80040558;
        *(s16 *)(p + 0x2E) = *(s16 *)(a + 0x2E);
        *(s16 *)(p + 0x32) = *(s16 *)(a + 0x32);
        *(s16 *)(p + 0x36) = *(s16 *)(a + 0x36);
        p[0x2A] = a[0x2A];
        p[0x5E] = 1;
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
    }
    return 1;
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", f_SpawnKujaraRanchPlacementReward);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8011FA5C);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8011FBD4);

INCLUDE_ASM("asm/a04/nonmatchings/a04", f_UpdateKujaraRanchPlacementRewardActor);

void func_80120188(u8 *a) {
    if (D_800BFE56 & 0x10) {
        M2C_FIELD(a, s16 *, 0x32) += 0x5A;
    }
    func_8003FBC4(a);
    D_800BF808.unk48++;
}

extern u8 D_80141410[];
void func_801201E0(u8 *a)
{
    u8 *g = D_800BF808_1760;

    if (*(s32 *)(g + 0x4C) != 0 && func_8007778C(a) != 0) {
        func_800517F8(a);
        if (*(s32 *)(g + 0x48) == D_80141410[a[3]]) {
            a[0] = 1;
        } else {
            a[0] = 5;
        }
    }
}

void func_80120260(u8 *a, s32 b)
{
    u8 *p = func_80072DDC(0, 2, 2, 0x30);

    if (p != NULL) {
        *(void **)(p + 0x1C) = func_80138140;
        p[3] = b;
        if (b == 2) {
            p[0x28] |= 0x80;
        }
        *(u8 **)(p + 0x10) = a;
    }
    *(s16 *)(p + 0x2E) = *(s16 *)(a + 0x2E);
    *(s16 *)(p + 0x32) = *(s16 *)(a + 0x32);
    *(s16 *)(p + 0x36) = *(s16 *)(a + 0x36);
}

void func_801202F8(u8 *a)
{
    switch (a[4]) {
    case 0:
        if (func_80051B70(a, 0xC, 0xD) != 0) {
            break;
        }
        *(s16 *)(a + 0x80) = 0xA0;
        *(s16 *)(a + 0x86) = 0x140;
        *(s16 *)(a + 0x84) = 0x140;
        *(s16 *)(a + 0x82) = 0x140;
        a[0x2A] = 0x2B;
        a[0] = 1;
        a[0x5F] = 0;
        *(s16 *)(a + 0x54) = 0;
        *(s16 *)(a + 0x56) = 0;
        *(s16 *)(a + 0x58) = 0;
        a[0x29] = 0;
        a[4]++;
        func_80041194(a, *(s16 *)(a + 0x86) - *(s16 *)(a + 0x84), 0, 0);
        func_8004130C(a, 1);
        break;
    case 1:
        switch (a[5]) {
        case 0:
            if (a[0x5F] != 0) {
                a[5] = 1;
                *(s16 *)(a + 0x40) = 10;
                *(s16 *)(a + 0x4E) = 0;
            }
            break;
        case 1:
            if (a[0x5F] != 0) {
                if (*(s16 *)(a + 0x40) == 0) {
                    *(s16 *)(a + 0x44) = -0x400;
                    a[5]++;
                } else {
                    *(s16 *)(a + 0x40) -= 1;
                }
            } else {
                a[5] = 0;
            }
            break;
        case 2:
            *(s16 *)(a + 0x44) -= 0x80;
            if (*(s16 *)(a + 0x44) < -0x1000) {
                *(s16 *)(a + 0x44) = -0x1000;
            }
            func_80041A1C(a, 1);
            if (func_8004954C(a, (s16)-*(s16 *)(a + 0x80), -0xA0) != 0) {
                a[5]++;
            }
            *(s16 *)(a + 0x32) += 0x10;
            func_80041938(a, 0, *(s16 *)(a + 0x86) - *(s16 *)(a + 0x84));
            break;
        }
        a[0x5F] = 0;
        a[0x29] = 0;
        a[1] = 1;
        func_80077EBC(a);
        func_800517F8(a);
        break;
    case 2:
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

extern u8 D_8014143C[];
void func_80120544(u8 *a)
{
    switch (a[6]) {
    case 0:
        a[0] = 1;
        a[6]++;
    case 1:
        if (D_800BF9BB >= 4) {
            *(s16 *)(a + 0x40) = 0x28;
            a[6]++;
        } else if (a[0x29] != 0) {
            func_80040B48(0x16);
        }
        break;
    case 2:
        if (--*(s16 *)(a + 0x40) == 0) {
            a[6]++;
        }
        func_8006CBD0(D_800E8008, D_8014143C);
        break;
    case 3:
        *(u16 *)(*(u8 **)(a + 0xC4) + 0x38) -= 0x40;
        if (*(u16 *)(*(u8 **)(a + 0xC4) + 0x38) <= 0x400) {
            *(s16 *)(a + 0x40) = 0x1E;
            a[6]++;
        }
        break;
    case 4:
        if (--*(s16 *)(a + 0x40) == 0) {
            a[6]++;
            D_800BF9BB = 5;
        }
        break;
    case 5:
        if (D_800BF9BB == 6) {
            a[6]++;
        }
        break;
    case 6:
        a[0] = 2;
        a[5] = 2;
        a[6] = 0;
        break;
    }
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_801206DC);

INCLUDE_ASM("asm/a04/nonmatchings/a04", f_UpdateKujaraLiftDepartureSequence);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80120C14);

extern u8 D_800E800B;
u8 *func_8007AAE8();
void func_80120F08(u8 *a)
{
    s32 t;

    switch (a[4]) {
    case 0:
        if (func_80051B70(a, 0xC, 0x18) != 0) {
            break;
        }
        if ((*(u8 **)(a + 0xC4) = func_8007AAE8()) == NULL) {
            a[4] = 3;
            break;
        }
        a[8] = 2;
        a[9] = 2;
        *(s16 *)(*(u8 **)(a + 0xC4) + 6) = -1;
        *(s16 *)(*(u8 **)(a + 0xC4) + 0) = 0;
        *(s16 *)(*(u8 **)(a + 0xC4) + 2) = 0;
        *(s16 *)(*(u8 **)(a + 0xC4) + 4) = 0;
        *(s16 *)(*(u8 **)(a + 0xC4) + 8) = 0;
        *(s16 *)(*(u8 **)(a + 0xC4) + 0xA) = 0xC00;
        *(s16 *)(*(u8 **)(a + 0xC4) + 0xC) = 0;
        *(s16 *)(*(u8 **)(a + 0xC4) + 0x38) = 0x1000;
        *(s16 *)(*(u8 **)(a + 0xC4) + 0x3A) = 0x1000;
        *(s16 *)(*(u8 **)(a + 0xC4) + 0x3C) = 0x1000;
        func_80051B04(*(u8 **)(a + 0xC4), 0xC, 0x17);
        *(s16 *)(a + 0x80) = 0xA0;
        *(s16 *)(a + 0x82) = 0x140;
        *(s16 *)(a + 0x86) = 0xE0;
        a[0] = 1;
        a[0x29] = 0;
        *(s16 *)(a + 0x84) = 0;
        *(s16 *)(a + 0x54) = -0x60;
        *(s16 *)(a + 0x56) = 0;
        *(s16 *)(a + 0x58) = 0;
        a[4]++;
        break;
    case 1:
        switch (a[5]) {
        case 0:
            if (a[0x29] != 0) {
                a[5] = 1;
            }
            *(s16 *)(a + 0x84) = 0;
            break;
        case 1:
            *(s16 *)(*(u8 **)(a + 0xC0) + 0x3A) -= 0x200;
            if (*(u16 *)(*(u8 **)(a + 0xC0) + 0x3A) < 0x200) {
                a[5]++;
            }
            if (a[0x29] == 1) {
                t = (*(u16 *)(*(u8 **)(a + 0xC0) + 0x3A) * 7) >> 7;
                *(s16 *)(a + 0x84) = (0xE0 - t) / 4;
            }
            break;
        case 2:
            *(s16 *)(*(u8 **)(a + 0xC0) + 0x3A) += 0x200;
            if (*(u16 *)(*(u8 **)(a + 0xC0) + 0x3A) >= 0x1000) {
                *(s16 *)(*(u8 **)(a + 0xC0) + 0x3A) = 0x1000;
                a[5] = 0;
                a[0x29] = 0;
            }
            if (a[0x29] == 1) {
                t = (*(u16 *)(*(u8 **)(a + 0xC0) + 0x3A) * 7) >> 7;
                *(s16 *)(a + 0x84) = (0xE0 - t) / 4;
            }
            break;
        }
        if (D_800E800B == 0x14) {
            a[1] = 1;
            func_80077EBC(a);
        } else if (func_8007778C(a) != 0) {
            func_80051844(a);
        }
        break;
    case 2:
    case 3:
        func_8007A624(a);
        break;
    }
}

s32 func_801211E4(u8 *a) {
    u8 *p = func_8007A980(2, 4, 0);

    if (p == NULL) {
        return 0;
    }
    M2C_FIELD(p, void **, 0x1C) = func_80120F08;
    p[0x2] = 49;
    M2C_FIELD(p, s16 *, 0x2E) = M2C_FIELD(a, u16 *, 0x2E);
    M2C_FIELD(p, s16 *, 0x32) = (M2C_FIELD(a, u16 *, 0x32) + -100);
    M2C_FIELD(p, s16 *, 0x36) = M2C_FIELD(a, u16 *, 0x36);
    p[0x2A] = a[0x2A];
    return 1;
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8012126C);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_801214B4);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_801217F8);

void func_80121A58(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 4);
    switch (temp_v1) {                              /* irregular */
    case 0:
        M2C_FIELD(arg0, s16 *, 0x80) = 0x76;
        M2C_FIELD(arg0, s16 *, 0x82) = 0xEC;
        M2C_FIELD(arg0, s16 *, 0x84) = 0xC8;
        M2C_FIELD(arg0, u8 *, 4) = 1U;
        M2C_FIELD(arg0, s8 *, 0) = 1;
        M2C_FIELD(arg0, s16 *, 0x86) = 0x190;
        M2C_FIELD(arg0, s8 *, 0x29) = 0;
        M2C_FIELD(arg0, s8 *, 0x2B) = 0;
        return;
    case 1:
        func_8007778C(arg0);
        return;
    case 2:
        func_8007778C(arg0);
        func_801217F8(arg0);
        return;
    case 3:
        func_8007A624(arg0);
        return;
    }
}

extern s8 D_1F8000F2[];
extern s8 D_1F800164[];
void func_80121B1C(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 4);
    switch (temp_v1) {                              /* irregular */
    case 0:
        if (func_80051B70(arg0, 0xC, 7) == 0) {
            M2C_FIELD(arg0, s8 *, 0xB) = 0xF;
            M2C_FIELD(arg0, s16 *, 0x80) = 0x96;
            M2C_FIELD(arg0, s16 *, 0x82) = 0x12C;
            M2C_FIELD(arg0, s16 *, 0x86) = 0x78;
            M2C_FIELD(arg0, s16 *, 0x84) = 0x78;
            M2C_FIELD(arg0, s8 *, 0) = 1;
            M2C_FIELD(arg0, s8 *, 0x29) = 0;
            M2C_FIELD(arg0, s8 *, 0x2A) = 0;
            M2C_FIELD(arg0, u8 *, 4) = (u8) (M2C_FIELD(arg0, u8 *, 4) + 1);
            func_80041194(arg0, M2C_FIELD(arg0, s16 *, 0x86) - M2C_FIELD(arg0, s16 *, 0x84), 0, 0);
            M2C_FIELD(arg0, u16 *, 0x32) = (u16) (M2C_FIELD(arg0, u16 *, 0x32) + 0x28);
            return;
        }
    case 2:
        return;
    case 1:
        if ((*((s16 *)D_1F800164) >= 0x300D) && (*((s16 *)D_1F8000F2) < 0x400)) {
            func_8007703C(arg0);
        } else {
            func_8007778C(arg0);
        }
        if (M2C_FIELD(arg0, u8 *, 1) != 0) {
            func_800517F8(arg0);
            return;
        }
        break;
    case 3:
        func_8007A624(arg0);
        break;
    }
}

void func_80121C70(void) {
    if ((*(s16 *)0x1F800164 >= 0x300D) && (*(s16 *)0x1F8000F2 < 0x400)) {
        func_8007703C();
        return;
    }
    func_8007778C();
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80121CC8);

extern s8 D_1F8000F2[];
extern s8 D_1F800207[];
void func_80121E44(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 4);
    switch (temp_v1) {                              /* irregular */
    case 0:
        if (func_80051B70(arg0, 0xC, 0x1D) == 0) {
            *M2C_FIELD(arg0, s16 **, 0xC0) = -0xE8;
            M2C_FIELD(arg0, s16 *, 0x80) = 0xFA;
            M2C_FIELD(arg0, s16 *, 0x82) = 0x1F4;
            M2C_FIELD(arg0, s16 *, 0x84) = 0x4E2;
            M2C_FIELD(arg0, u8 *, 0x2B) = 0U;
            M2C_FIELD(arg0, s8 *, 0x29) = 0;
            M2C_FIELD(arg0, s8 *, 0) = 1;
            M2C_FIELD(arg0, s16 *, 0x86) = 0x578;
            M2C_FIELD(arg0, u8 *, 4) = (u8) (M2C_FIELD(arg0, u8 *, 4) + 1);
            return;
        }
        return;
    case 1:
        if (M2C_FIELD(arg0, u8 *, 0x2B) != 0) {
            M2C_FIELD(arg0, u8 *, 0x2B) = 0U;
            func_80040B48(0x15);
        }
        if (((u32) (*((u8 *)D_1F800207) - 0x10) < 6U) && (*((s16 *)D_1F8000F2) < 0x400)) {
            func_8007703C(arg0);
        } else {
            func_8007778C(arg0);
        }
        if (M2C_FIELD(arg0, u8 *, 1) != 0) {
            func_800518FC(arg0);
            return;
        }
        break;
    case 2:
        func_8007778C(arg0);
        func_800518FC(arg0);
        func_80121CC8(arg0);
        return;
    case 3:
        func_8007A624(arg0);
        break;
    }
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80121FB8);

INCLUDE_ASM("asm/a04/nonmatchings/a04", f_UpdateHolyTreeGrowthSequence);

INCLUDE_ASM("asm/a04/nonmatchings/a04", f_UpdateHolyTreeInteractionSequence);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8012296C);

extern u8 D_80141464[];
s32 func_80122F08(u8 *p)
{
    s32 s = p[7];

    switch (s) {
    case 0:
        if (!func_8002300C(D_800E7E80, p, *(s16 *)(p + 0x80) * 2 + 8)) {
            return 0;
        }
        if (func_8005308C()) {
            p[7]++;
            func_80042354(1, 1);
            return 0;
        }
        break;
    case 1:
        p[7] = 2;
        func_80040CDC(p, 0, D_80141464);
        p[0x70] = s;
        break;
    case 2:
        func_80041098(p);
        if (p[0x70] != 0xFF) {
            return 0;
        }
        func_80042310();
        return 1;
    }
    return 0;
}

typedef union {
    u8 b[0xC0];
    s16 h[0x60];
} ActorH;
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
s32 func_80123008(DoorActor *a, s16 *d) {
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

void func_801231E0(u8 *a, s32 b) {
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
    if (func_80123008(a, b) != 0) {
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

extern u8 D_800E806E;
extern u16 D_1F8000D6;
void func_8012333C(u8 *a) {
    u8 *t;

    switch (a[5]) {
    case 0:
        D_1F800137_104c = 2;
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
            D_1F800137_104c = 0;
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

void func_80123584(u8 *a) {
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

void func_8012379C(u8 *a, u16 *b) {
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
            D_1F800137_104c = 2;
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
            D_1F800137_104c = 0;
            func_8006E1E4();
        }
        a[1] = 0;
        break;
    }
}

extern ClutCycle D_80141584[];
extern s8 D_801442D0[];
void func_80123B90(s32 arg0) {
    ClutRect r;
    s32 i;
    ClutCycle *e;
    u8 *data;

    if (arg0 == 0) {
        for (i = 0; i < 1; i++) {
            D_801442D0[i] = 0;
        }
        return;
    }
    e = D_80141584;
    for (i = 0; i < 1; i++, e++) {
        if (--D_801442D0[i] <= 0) {
            if (e->ptr[0] == 0xFF) {
                e->ptr -= e->ptr[1];
            }
            data = e->clut + e->ptr[0] * 32;
            D_801442D0[i] = e->ptr[1];
            r.x = e->x;
            r.y = e->y;
            r.w = 16;
            r.h = 1;
            func_80081218(&r, data);
            e->ptr += 2;
        }
    }
}

extern u8 D_800E7E80_d97c;
extern u8 D_80141590[];
extern u8 D_801415B0[];
extern s16 D_1F800160_71b4;
extern s16 D_1F800164_d75f;
void func_80123CB0(u8 *a)
{
    switch (a[4]) {
    case 0:
        switch (a[5]) {
        case 0:
            func_80123B90(0);
            a[0xBF] = 0xD0;
            *(s16 *)(a + 0x7E) = 0x1A;
            *(s16 *)(a + 0x7C) = 0x400;
            *(s16 *)(a + 0x7A) = 4;
            *(s16 *)(a + 0x78) = 0x29;
            a[5]++;
        case 1:
            func_801231E0(a, D_80141590);
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
            func_80123B90(1);
            func_80051844(a);
        }
        switch (a[0x5E]) {
        case 0:
            func_8012333C(a);
            a[0x29] = 0;
            break;
        case 1:
            func_80123584(a);
            a[0x29] = 0;
            break;
        case 2:
            func_8012379C(a, D_801415B0);
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

extern u8 D_80141724[];
extern u8 D_8001B4DC[];
extern u8 D_8014179C[];
extern u8 D_8014182C[];
void func_80123EC8(u8 *a)
{
    u8 *g;
    u8 *st;

    switch (a[4]) {
    case 0:
        g = D_800ECF58;
        if (func_800519E0(a, 0xF, *(s32 *)(g + 0x3C), D_80141724) != 0) {
            break;
        }
        *(s32 *)(a + 0x3C) = *(s32 *)(g + 0xA0);
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
        func_80051B04(*(u8 **)(a + 0xEC), 0xF, 0xF);
        func_80051B04(*(u8 **)(a + 0xF0), 0xF, 0x10);
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
            if (st[0x1DE] == 2 && st[0x1D8] == 0) {
                func_80040CDC(a, D_8001B4DC, D_8014179C);
                st[0x1DE] = 3;
                a[6] += 2;
            } else {
                func_80040CDC(a, D_8001B4DC, D_8014182C);
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
s32 func_80124148(void) {
    D_800BF818 = 7;
    return 1;
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8012415C);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80124394);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80124660);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80124A08);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80124BD0);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80124E18);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80124F04);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80125600);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80125B94);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80125D5C);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80125ECC);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_801262F4);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_801264FC);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80126718);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80126A20);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_801270EC);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_801272D8);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80127478);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80127670);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_801277D4);

void func_80124394();
void func_8012BC40();
u8 *func_80127D70(u8 *a, s32 b, s32 c) {
    u8 t;
    u8 *p = func_80072DDC(0, 3, 2, 13);

    if (p != NULL) {
        M2C_FIELD(p, void **, 0x1C) = func_80124394;
        p[0x3] = c - 0x7F;
        M2C_FIELD(p, s32 *, 0x10) = 0;
        M2C_FIELD(p, s32 *, 0x14) = 0;
        M2C_FIELD(p, s32 *, 0x2C) = M2C_FIELD(a, s32 *, 0x2C);
        M2C_FIELD(p, s32 *, 0x30) = M2C_FIELD(a, s32 *, 0x30);
        M2C_FIELD(p, s32 *, 0x34) = M2C_FIELD(a, s32 *, 0x34);
        t = a[0x2A];
        p[0x46] = b;
        p[0x2A] = t;
    }
    return p;
}

s32 func_80127E14(u8 *a) {
    if (a[0x2A] >= 0x1A) {
        return 1;
    }
    return M2C_FIELD(a, s16 *, 0x36) < 0xFC1;
}

s32 func_80127E3C(void) {
    return 1;
}

void func_80127E44(u8 *a) {
    func_80127EF0(a, 4, 4);
}

s32 func_80127E68(u8 *a)
{
    u8 *p = a + 0x60;
    s32 r = (u32)((*(u16 *)(a + 0x60) - func_800782B0(a + 0x2C, D_1F800160_71b4, D_1F800164_d75f) + 0x400) & 0xFFF) > 0x800;
    u8 s = r;

    if (r) {
        *(u16 *)(p + 2) |= 1;
    } else {
        *(u16 *)(p + 2) &= ~1;
    }
    return s;
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80127EF0);

void func_80127FE8(u8 *a)
{
    if (*(u16 *)(a + 0x62) & 1) {
        *(s32 *)(a + 0x2C) -= *(s16 *)(a + 0x48) * *(s16 *)(a + 0x4E);
        *(s32 *)(a + 0x34) -= *(s16 *)(a + 0x4C) * *(s16 *)(a + 0x4E);
    } else {
        *(s32 *)(a + 0x2C) += *(s16 *)(a + 0x48) * *(s16 *)(a + 0x4E);
        *(s32 *)(a + 0x34) += *(s16 *)(a + 0x4C) * *(s16 *)(a + 0x4E);
    }
}

void func_8012807C(void *arg0) {
    if ((M2C_FIELD(arg0, u8 *, 0x2A) == 0xF) && (M2C_FIELD(arg0, s16 *, 0x36) < 0x12F6)) {
        M2C_FIELD(arg0, s16 *, 0x36) = 0x12F6;
    }
}

void func_801280AC(u8 *a)
{
    s32 k;

    switch (a[4]) {
    case 0:
        func_801282A8(a);
        break;
    case 1:
        func_80116B48(a);
        if (!(a[3] & 0x80)) {
            *(s16 *)(a + 0x6A) = func_80129C44(a, 3);
            if (!(a[0x5E] & 2) && !(*(u16 *)(a + 0x7E) & 2) && (s16)func_80128EEC(a) != 0) {
                func_80129A88(a);
                a[0x5E] = 2;
                *(s16 *)(a + 0x6C) = 0xFF;
                *(s16 *)(a + 0x7E) = 0;
                a[5] = 2;
                a[6] = 0;
            }
            switch (a[5]) {
            case 0:
                func_80128414(a);
                break;
            case 1:
                func_801285BC(a);
                break;
            case 2:
                f_UpdateSeaAnemoneFreezeSequence(a);
                break;
            }
        }
        if (a[1] != 0) {
            func_80129628(a);
            if (*(s16 *)(a + 0x72) != 0) {
                func_8012948C(a);
            }
        }
        break;
    case 2:
        func_8007778C(a);
        /* the empty cases need distinct labels (dead stores) for retail's 7-entry jump table */
        switch (a[5]) {
        case 5:
            func_80129D0C(a);
            break;
        case 0:
            k = 0;
            break;
        case 1:
            k = 1;
            break;
        case 2:
            k = 2;
            break;
        case 3:
            k = 3;
            break;
        case 4:
            k = 4;
            break;
        case 6:
            k = 6;
            break;
        }
        if (a[1] != 0) {
            func_80129628(a);
        }
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_801282A8);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80128414);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_801285BC);

#define QH(p, o) (*(s16 *)((u8 *)(p) + (o)))
s16 func_80129168();
void f_UpdateSeaAnemoneFreezeSequence(u8 *a) {
    u8 *p = *(u8 **)(a + 0x10);
    s32 one;

    if (a[0xBF] == 0 && p != NULL && a[0x2B] == 0 && (p[0x2B] != 0 || p[0] == 2)) {
        *(u8 **)(a + 0x10) = NULL;
        func_80129B54(a, 0, 0xC, 3);
        QH(a, 0x62) = 0x3C;
        a[0x5E] = 0;
        QH(a, 0x60) = 0;
        QH(a, 0x64) = 0;
        QH(a, 0x6C) = 0xFF;
        a[5] = 0;
        a[6] = 0;
        return;
    }
    switch (a[6]) {
    case 0:
        func_80128D84(a, 1);
        a[6]++;
        break;
    case 1:
        if (QH(a, 0x6A) == 1) {
            a[6]++;
        }
    case 2:
        if (a[0x2B] == 2) {
            a[6] = 3;
            a[0x5E]++;
        }
        break;
    case 3:
        if (func_80129168(a, 1) != 0) {
            a[0] = 3;
            QH(a, 0x72) = 1;
            if (QH(a, 0x6C) < 3) {
                func_80129B54(a, 0x10, 4, 3);
            } else {
                func_80129B54(a, 0x11, 4, 3);
            }
            QH(a, 0x40) = 4;
            a[6]++;
        }
        break;
    case 4:
        if (QH(a, 0x6A) == 1 && --QH(a, 0x40) == 0) {
            QH(a, 0x40) = 9;
            func_80129B54(a, 0x12, 2, 3);
            a[6]++;
        }
        break;
    case 5:
        if (--QH(a, 0x40) == 0) {
            a[0xBF] = 1;
            QH(a, 0x72) = 0;
            p[4] = 3;
            *(u8 **)(a + 0x10) = NULL;
            func_80074590(8, 0x12, 0);
        }
        if (QH(a, 0x6A) == 1) {
            func_80129B54(a, 0x13, 0, 3);
            a[6]++;
        }
        break;
    case 6:
        if ((one = QH(a, 0x6A)) == 1) {
            if (D_800BF80F == 0) {
                func_80129B54(a, 0xA, 4, 3);
                if (func_80040B48(0x66) >= 0) {
                    D_800BF870.pad1[0x17B] |= one << (a[3] * 2);
                    a[0] = one;
                    a[3] |= 0x80;
                }
                func_80119F24(a, 1);
                a[6]++;
            } else {
                func_80129B54(a, 0, 0x10, 3);
                QH(a, 0x62) = 0x3C;
                QH(a, 0x60) = 0;
                QH(a, 0x64) = 0;
                QH(a, 0x6C) = 0xFF;
                a[0x5E] = 0;
                a[0x2B] = 0;
                a[0xBF] = 0;
                a[5] = 0;
                a[6] = 0;
            }
        }
        break;
    }
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80128BEC);

s32 func_80128D84(u8 *a, s32 f) {
    u8 *t;
    s16 dx, dz, dy;
    s16 d, e;
    s32 ang;

    if (f == 0) {
        t = D_800E7E80;
    } else {
        t = *(u8 **)(a + 0x10);
    }
    dx = U(a, 0x2E) - U(t, 0x2E);
    dz = U(a, 0x36) - U(t, 0x36);
    dy = U(a, 0x32) - U(t, 0x32);
    d = func_80084080(dx * dx + dz * dz);
    e = d;
    if (func_80077768(H(a, 0x56), -func_80085690(dz, dx) & 0xFFF, 1) != 0) {
        e = -d;
    }
    ang = (func_80085690(dy, e) + 0x100) & 0xFFF;
    if (ang > 0xC00) {
        ang = 0;
    } else if (ang > 0x900) {
        ang = 0x900;
    }
    ang >>= 9;
    if (H(a, 0x6C) == ang) {
        return 0;
    }
    func_80129B54(a, D_8014190C[ang], 8, 3);
    func_80129904(a, (s16)ang);
    return 1;
}

s32 func_80128EEC(u8 *a) {
    u8 *e = *(u8 **)(a + 0x10);
    s16 dy, dx, dz;

    if (e != NULL) {
        if (e[0x2B] != 0) {
            *(u8 **)(a + 0x10) = NULL;
            H(a, 0x74) = 0;
            return 0;
        }
    } else {
        H(a, 0x74) = 0;
    }
    switch (H(a, 0x74)) {
    case 0:
        e = func_80129998();
        if (e == NULL) {
            return 0;
        }
        *(u8 **)(a + 0x10) = e;
        dy = H(a, 0x32) - (s16)(H(e, 0x32) - 0x46);
        if (H(a, 0x6E) < (u16)dy) {
            goto fail;
        }
        dx = H(a, 0x2E) - H(e, 0x2E);
        dz = H(a, 0x36) - H(e, 0x36);
        if (e[0x46] == 8) {
            if (dx * dx + dz * dz > 40000) {
                goto fail;
            }
            if (dy < 0x385) {
                return 1;
            }
            H(a, 0x74)++;
            goto ret0;
        }
        if (dy < 0x2A9 && func_80077768(H(e, 0x56), (s16)-func_80085690(dz, dx), 1) != 0) {
            if (dx * dx + dz * dz <= 0x9C400) {
                return 1;
            }
            H(a, 0x74) = 2;
            return 0;
        }
    fail:
        H(a, 0x74) = -1;
        return 0;
    case 1:
        if ((s16)(H(a, 0x32) - (s16)(H(e, 0x32) - 0x46)) >= 0x385) {
            return 0;
        }
        H(a, 0x74) = 0;
        return 1;
    case 2:
        dx = H(a, 0x2E) - H(e, 0x2E);
        dz = H(a, 0x36) - H(e, 0x36);
        if (dx * dx + dz * dz <= 0x9C400) {
            H(a, 0x74) = 0;
            return 1;
        }
        return 0;
    }
ret0:
    return 0;
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80129168);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8012948C);

typedef struct { u8 pad[0xC0]; u8 *s[8]; } A9628;
#define SLOT9628(i) (*(u8 **)(a + 0xC0 + (i) * 4))
void func_80129628(u8 *a)
{
    s32 m[8];
    s32 i;


    func_800518FC(a);
    for (i = 0; i < a[9]; i++) {
        if (i >= a[8]) {
            break;
        }
        func_80051794(m);
        func_800847F0(SLOT9628(i) + 8, m);
        if (*(s16 *)(SLOT9628(i) + 6) == -1) {
            func_80084110(a + 0x98, m, SLOT9628(i) + 0x18);
        } else {
            func_80084110((((A9628 *)a)->s[*(s16 *)(SLOT9628(i) + 6)]) + 0x18, m, SLOT9628(i) + 0x18);
        }
    }
    for (i = 0; i < a[8]; i++) {
        func_800517BC(m, *(s16 *)(SLOT9628(i) + 0x38), *(s16 *)(SLOT9628(i) + 0x3A), *(s16 *)(SLOT9628(i) + 0x3C));
        func_80084250(SLOT9628(i) + 0x18, m);
    }
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80129744);

typedef struct {
    s16 x, y;
} Pair16;
extern Pair16 D_80141914[];
void func_80129904(u8 *a, s16 k) {
    s32 t;

    M2C_FIELD(a, s16 *, 0x60) = D_80141914[k].x;
    M2C_FIELD(a, s16 *, 0x62) = D_80141914[k].y;
    M2C_FIELD(a, s16 *, 0x64) = (-func_80083E80(M2C_FIELD(a, s16 *, 0x56)) * M2C_FIELD(a, s16 *, 0x60)) >> 12;
    t = func_80083F50(M2C_FIELD(a, s16 *, 0x56)) * M2C_FIELD(a, s16 *, 0x60);
    M2C_FIELD(a, s16 *, 0x6C) = k;
    M2C_FIELD(a, s16 *, 0x60) = t >> 12;
}

u8 *func_80129998(void) {
    u8 *p;

    for (p = D_800F2738; p != NULL; p = M2C_FIELD(p, u8 **, 0x24)) {
        if ((M2C_FIELD(p, u32 *, 0) & 0xFF00FF) == 1) {
            return p;
        }
    }
    return NULL;
}

s32 func_801299E8(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    u16 temp_v1_2;
    u16 temp_v1_3;
    void *temp_v0;
    void *temp_v1;
    void *var_t0;

    temp_v0 = M2C_FIELD(arg0, void **, 0x14);
    var_t0 = NULL;
    if (temp_v0 != NULL) {
        var_t0 = temp_v0;
        M2C_FIELD(var_t0, s16 *, 0x2C) = (s16) arg1;
        M2C_FIELD(var_t0, s16 *, 0x2E) = (s16) arg2;
        M2C_FIELD(var_t0, s16 *, 0x30) = (s16) arg3;
        M2C_FIELD(var_t0, u16 *, 0x48) = (u16) M2C_FIELD(M2C_FIELD(arg0, void **, 0xCC), u16 *, 8);
        M2C_FIELD(var_t0, u16 *, 0x4A) = (u16) M2C_FIELD(arg0, u16 *, 0x56);
        temp_v1 = M2C_FIELD(arg0, void **, 0xCC);
        temp_v1_2 = (u16) M2C_FIELD(temp_v1, s16 *, 0xC);
        if (M2C_FIELD(temp_v1, s16 *, 0xC) >= 0x801) {
            M2C_FIELD(var_t0, u16 *, 0x4C) = (u16) (temp_v1_2 - 0x1000);
        } else {
            M2C_FIELD(var_t0, u16 *, 0x4C) = temp_v1_2;
        }
        temp_v1_3 = M2C_FIELD(var_t0, u16 *, 0x4C);
        M2C_FIELD(var_t0, u16 *, 0x4C) = (u16) (temp_v1_3 + ((s32) (temp_v1_3 << 0x10) >> 0x11));
        M2C_FIELD(var_t0, s32 *, 0x58) = (s32) M2C_FIELD(M2C_FIELD(arg0, void **, 0x38), u16 *, 2);
    }
    return (s32) var_t0;
}

void func_80129A88(s32 arg0)
{
  void *temp_v1;
  temp_v1 = *((void **) (((signed char *) arg0) + 0x14));
  if (temp_v1 != 0)
  {
    *((s8 *) (((signed char *) temp_v1) + 4)) = 2;
    *((void **) (((signed char *) arg0) + 0x14)) = 0;
  }
  return 2;
}

typedef struct {
    s16 x, y, w, h;
} RectA;
typedef struct { s16 m[3][3]; s16 pad; s32 t[3]; } AreaMatrix;
typedef struct { s16 x, y, z, pad; } AreaSVec;
typedef struct { u8 pad[0x28]; AreaMatrix m; } AreaScratchD0;
typedef struct {
    u8 pad0[0x38];
    u8 *p38;
    u8 pad3C[0x24];
    s16 h60[0x34];
    u8 *pC8;
} ActorDF;
typedef struct {
    s16 x, y, w, h;
} RECT16;
void func_80129AA8(ActorDF *a, s32 i) {
    s32 j = i + 1;
    s16 v;

    func_80129744(a, j);
    if (a->h60[j] != 2) {
        a->h60[i] = 0;
    } else {
        v = *(s16 *)(a->p38 + 4) >> 4;
        if (v != a->h60[i]) {
            func_80051B04(a->pC8, 0x23, v);
            a->h60[i] = v;
        }
    }
}

typedef struct {
    u8 pad[0x60];
    s16 v[8];
} ArrActor60;
extern u8 D_80145A00[];
void func_80129B54(ArrActor60 *a, s32 k, s32 f, s32 i) {
    s16 n;

    if (f == 0) {
        func_80077C40(a, D_80145A00, k);
    } else {
        func_80077CFC(a, D_80145A00, k, (s16)f);
    }
    func_80129744(a, i + 1);
    if (a->v[i + 1] != 2) {
        a->v[i] = 0;
        return;
    }
    n = (s16)M2C_FIELD(M2C_FIELD(a, u8 **, 0x38), u16 *, 4) >> 4;
    if (n != a->v[i]) {
        func_80051B04(M2C_FIELD(a, u8 **, 0xC8), 0x23, n);
        a->v[i] = n;
    }
}

s16 func_80129C44(ActorDF *a, s32 i) {
    s32 r = func_80076D68();
    s32 j = i + 1;
    s16 v;

    func_80129744(a, j);
    if (a->h60[j] != 2) {
        a->h60[i] = 0;
    } else {
        v = *(s16 *)(a->p38 + 4) >> 4;
        if (v != a->h60[i]) {
            func_80051B04(a->pC8, 0x23, v);
            a->h60[i] = v;
        }
    }
    return r;
}

void func_80129D0C(u8 *a) {
    u8 *p = M2C_FIELD(a, u8 **, 0x10);

    if (p != NULL) {
        p[4] = 2;
        M2C_FIELD(a, u8 **, 0x10)[5] = 0;
        M2C_FIELD(a, u8 **, 0x10) = NULL;
    }
    func_80119004(a);
    func_8003116C(0x24, a + 0x2C, -10);
    D_800BF870.pad1[0x17B] += 1 << ((a[3] & 0x7F) * 2);
    a[4] = 3;
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80129D98);

extern u8 D_8013FD44[];
extern u8 D_80144404[];
extern u8 D_800A3D18[];
extern u8 D_800BFA07;
extern u8 D_800A3D90[];
extern u8 D_800BF8E3;
extern u8 D_80141A94[];
void func_8012A180(u8 *a)
{
    u8 *g;

    switch (a[4]) {
    case 0:
        g = D_800ECF58;
        if (func_800519E0(a, 0xF, *(s32 *)(g + 0x78), D_8013FD44) != 0) {
            break;
        }
        *(s32 *)(a + 0x3C) = *(s32 *)(g + 0x38);
        func_80040CDC(a, D_80144404, D_800A3D18);
        a[0xB] = 0x40;
        a[0] = 9;
        *(s16 *)(a + 0x80) = 0x55;
        *(s16 *)(a + 0x82) = 0xAA;
        *(s16 *)(a + 0x84) = 0x90;
        *(s16 *)(a + 0x86) = 0x120;
        a[0x2B] = 0;
        a[0x29] = 0;
        *(s16 *)(a + 0x58) = 0;
        *(s16 *)(a + 0x54) = 0;
        switch (a[3]) {
        case 0:
            a[0x2A] = 0xF;
            a[0x7B] = 0xF;
            *(s32 *)(a + 0x2C) = 0xE860000;
            *(s32 *)(a + 0x30) = 0xDD300000;
            *(s32 *)(a + 0x34) = 0x146E0000;
            if (!(D_800BFA07 & 8)) {
                *(s16 *)(a + 0x56) = 0;
            } else {
                *(s16 *)(a + 0x56) = 0x800;
            }
            *(s16 *)(a + 0x42) = 0;
            break;
        case 1:
            *(s32 *)(a + 0x2C) = 0x9DF0000;
            *(s32 *)(a + 0x30) = 0xD3BC0000;
            *(s32 *)(a + 0x34) = 0x2EDA0000;
            a[0x7B] = 0;
            a[0x2A] = 0x19;
            *(s16 *)(a + 0x56) = 0;
            break;
        }
        func_80041718(a, a[0x7B], 0);
        a[4]++;
        break;
    case 1:
        switch (a[3]) {
        case 0:
            func_80129D98(a);
            break;
        case 1:
            switch (a[5]) {
            case 0:
                if (func_80116B48(a) != 0 && a[0x2B] == 3) {
                    func_80042354(1, 1);
                    func_80040D68(a, D_800A3D90);
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
                    if (a[6] == 0) {
                        if (D_800BF8E3 == 0xFF) {
                            a[0x7A] = 0xF;
                        } else {
                            a[0x7A] = 0xE;
                        }
                        func_80040D68(a, D_80141A94);
                        a[0x70] = 2;
                        a[6]++;
                    } else {
                        a[5] = 0;
                    }
                }
                break;
            }
            if (a[1] != 0) {
                func_8004190C(a);
            }
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

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8012A480);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8012A598);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8012A714);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8012A80C);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8012AB58);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8012AF9C);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8012B8B4);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8012BC40);

s32 func_8012C658(u8 *a)
{
    u8 *q = a + 0x60;
    u8 *p = func_8007A980(1, 2, 0);

    if (p == 0) {
        return 0;
    }
        *(void **)(p + 0x1C) = func_8012BC40;
        p[2] = 0x1B;
        p[3] = 3;
        *(s16 *)(p + 0x2E) = *(s16 *)(a + 0x2E);
        *(s16 *)(p + 0x32) = *(s16 *)(a + 0x32) - 0x64;
        *(s16 *)(p + 0x36) = *(s16 *)(a + 0x36);
        p[0x2A] = a[0x2A];
        *(s16 *)(p + 0x60) = *(s16 *)(a + 0x60);
        *(s16 *)(p + 0x56) = *(s16 *)(a + 0x60);
        p[0xBE] = q[2] & 1;
        func_8003116C(0x506, a + 0x2C, -0x32);
    return 1;
}

s32 func_8012C724(u8 *a) {
    s16 t;
    u8 *p = func_8007A980(1, 2, 0);

    if (p == NULL) {
        return 0;
    }
    M2C_FIELD(p, void **, 0x1C) = func_8012BC40;
    p[0x2] = 27;
    p[0x3] = 4;
    M2C_FIELD(p, s16 *, 0x2E) = M2C_FIELD(a, u16 *, 0x2E);
    M2C_FIELD(p, s16 *, 0x32) = M2C_FIELD(a, u16 *, 0x32);
    M2C_FIELD(p, s16 *, 0x36) = M2C_FIELD(a, u16 *, 0x36);
    p[0x2A] = a[0x2A];
    t = M2C_FIELD(a, s16 *, 0x140);
    M2C_FIELD(p, s16 *, 0x6A) = 0;
    M2C_FIELD(p, s16 *, 0x56) = M2C_FIELD(p, s16 *, 0x60) = t;
    p[0xBE] = a[0x147];
    return 1;
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8012C7CC);

typedef struct { s16 p0, x, p4, y, p8, z; } HV;
void func_8012C8AC(u8 *a, s32 k)
{
    HV v;

    if (k != 0) {
        s32 m;
        if (abs(*(s16 *)(a + 0x44)) > 0x1800) {
            m = D_1F80017C_0fe7 & 3;
        } else {
            m = D_1F80017C_0fe7 & 0xF;
        }
        if (m != 0) {
            return;
        }
    }
    v.x = *(s16 *)(a + 0x2E);
    v.y = *(s16 *)(a + 0x32) + 0x50;
    v.z = *(s16 *)(a + 0x36);
    func_8003116C(0x502, &v, -0x32);
}

extern u8 D_80141AB4[];
extern u8 D_80141ABC[];
void func_8012C934(u8 *a, s32 k)
{
    if (k != 0) {
        func_80051B04(*(void **)(a + 0xC0), 0xC, D_80141AB4[0]);
        return;
    }
    if (*(s16 *)(a + 0x40) != 0) {
        *(s16 *)(a + 0x40) -= 1;
        return;
    }
    func_80051B04(*(void **)(a + 0xC0), 0xC, D_80141AB4[D_80141ABC[*(s16 *)(a + 0xE)]]);
    if ((*(s16 *)(a + 0xE) = (*(s16 *)(a + 0xE) + 1) & 0xF) == 0) {
        *(s16 *)(a + 0x40) = (func_8009A450() & 0x3F) + 0xA;
    }
}

u8 func_8012C9E0(u8 *a)
{
    if (a[0x5F] == 0) {
        s16 v;
        if (*(s16 *)(a + 0x44) >= 0) {
            v = *(s16 *)(a + 0x80);
        } else {
            v = -*(s16 *)(a + 0x80);
        }
        if (func_80045CAC(a, (s16)v, (s16)(*(s16 *)(a + 0x86) - *(s16 *)(a + 0x84) - 0x18), (s16)*(s16 *)(a + 0x60)) != 0) {
            a[0x5F] = a[0xBE] + 2;
        }
    }
    return a[0x5F];
}

s32 func_8012CA80(void *arg0) {
    s32 var_v0;
    u8 temp_a1;

    temp_a1 = M2C_FIELD(arg0, u8 *, 0x5F);
    if ((temp_a1 & 0x80) || ((temp_a1 != 0) && ((temp_a1 & 1) == M2C_FIELD(arg0, u8 *, 0xBE)))) {
        M2C_FIELD(arg0, s8 *, 0) = 2;
        M2C_FIELD(arg0, s8 *, 4) = 2;
        M2C_FIELD(arg0, s8 *, 6) = 0;
        if (M2C_FIELD(arg0, u8 *, 0x5F) & 0x80) {
            M2C_FIELD(arg0, s8 *, 5) = 3;
        } else {
            M2C_FIELD(arg0, s8 *, 5) = 2;
            if (M2C_FIELD(arg0, u8 *, 0xBE) == 0) {
                var_v0 = (s32) (M2C_FIELD(arg0, s16 *, 0x60) + 0x800) >> 4;
            } else {
                var_v0 = (s32) ((u16) M2C_FIELD(arg0, s16 *, 0x60) >> 4);
            }
            M2C_FIELD(arg0, s8 *, 0x2B) = (s8) var_v0;
        }
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8012CB18);

extern u8 D_801415BC[];
extern u8 D_800BF809;
extern u8 D_80141B0C[];
extern u8 D_80141B00[];
void func_8012F1E4(void *arg0);
void func_8012CBD4(u8 *a)
{
    u8 *g;

    switch (a[4]) {
    case 0:
        g = D_800ECF58;
        if (func_800519E0(a, 0x10, *(s32 *)(g + 0x50), D_801415BC) != 0) {
            break;
        }
        *(s32 *)(a + 0x3C) = *(s32 *)(g + 0x58);
        a[0xB] = 0xF;
        func_8012F41C(a, 1, 0);
        func_8012CF08(a);
        *(s16 *)(a + 0x64) = 0xC8;
        *(s16 *)(a + 0x66) = 0x5A;
        *(s16 *)(a + 0x74) = 3;
        *(s16 *)(a + 0x76) = 4;
        a[4]++;
        break;
    case 1:
        ((void (*)())func_80121C70)(a);
        if (a[0x2B] != 0) {
            a[0x2B]--;
        } else {
            if (D_800BF809 != 0 || D_1F800137_104c != 0) {
                break;
            }
            *(s16 *)(a + 0x7C) = func_80076D68(a);
            *(s16 *)(a + 0x4E) = (*(s16 *)(a + 0x4E) + D_80141B0C[*(s16 *)(a + 0x7A)]) & 0xFFF;
            if (*(s16 *)(a + 0x7C) == 1) {
                *(s16 *)(a + 0x4E) = 0;
            }
            switch (a[5]) {
            case 0:
                func_8012D05C(a);
                break;
            case 1:
                func_8012D1A0(a);
                break;
            case 2:
                func_8012D424(a);
                break;
            case 3:
                func_8012D844(a);
                break;
            case 4:
                func_8012DA04(a);
                break;
            }
            a[0x29] = 0;
            a[0x5F] = 0;
            if (a[1] != 0 && D_80141B00[*(s16 *)(a + 0x7A)] != 0 && *(u16 *)(*(u8 **)(a + 0x38) + 4) == 1) {
                func_80074590(0x8F, 0, 0);
            }
        }
        if (a[1] != 0) {
            func_800518FC(a);
        }
        break;
    case 2:
        func_8007778C(a);
        switch (a[5]) {
        case 0:
        case 4:
        case 5:
        case 6:
            if (D_800BF809 == 0 && D_1F800137_104c == 0) {
                func_8012E0A8(a);
            }
            break;
        case 1:
            func_8012F1E4(a);
            break;
        case 11:
            if (func_80080750(a, 0, 0) != 0) {
                a[4] = 3;
                return;
            }
            a[5] = 2;
        case 2:
        case 7:
        case 8:
            func_8012E6A4(a);
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

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8012CF08);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8012D05C);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8012D1A0);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8012D424);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8012D844);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8012DA04);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8012E0A8);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8012E6A4);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8012E87C);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8012E9EC);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8012EAF4);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8012EC48);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8012EE00);

void func_8012F054(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x30) = (s32) (M2C_FIELD(arg0, s32 *, 0x30) - (func_80083E80(M2C_FIELD(arg0, s16 *, 0x4E)) << 6));
}

void func_8012F090(u8 *a)
{
    u16 t;

    if (func_80077768(*(s16 *)(a + 0x6C), D_1F8001A0, 1) != 0) {
        a[0xBE] = 0;
    } else {
        a[0xBE] = 1;
    }
    *(s16 *)(a + 0x6C) &= 0xFFF;
    t = *(u16 *)(a + 0x56) & 0xFFF;
    *(u16 *)(a + 0x56) = t;
    if (*(s16 *)(a + 0x50) > 0) {
        *(s16 *)(a + 0x40) = *(u16 *)(a + 0x6C) - t;
    } else {
        *(s16 *)(a + 0x40) = t - *(u16 *)(a + 0x6C);
    }
    if (*(s16 *)(a + 0x40) < 0) {
        *(s16 *)(a + 0x40) += 0x1000;
    }
    *(s16 *)(a + 0x40) = *(s16 *)(a + 0x40) >> 8;
    *(s16 *)(a + 0x58) &= 0xFFF;
}

void func_8012F148(u8 *a)
{
    s32 one = 1;
    func_8012F41C(a, 0, 8);
    a[0] = one;
    func_8012F690(a, -1, 0x28, 0x3C);
    *(s16 *)(a + 0x44) = 0x1400;
    *(s16 *)(a + 0x4A) = -0x100;
    a[5] = 4;
    a[6] = 6;
    a[4] = one;
    a[0xD] = 0;
    *(s16 *)(a + 0x78) = 0;
    a[7] = 0;
    a[0x1B] &= 0xBF;
    *(s16 *)(a + 0x40) = *(s16 *)(a + 0x32) - *(s16 *)(a + 0x70);
}

void func_8012F1E4(void *arg0) {
    M2C_UNK var_a0;

    if (M2C_FIELD(arg0, u8 *, 6) == 0) {
        func_80074590(0x91, 0, 0);
        M2C_FIELD(arg0, s8 *, 0x5E) = 0;
        M2C_FIELD(arg0, u8 *, 0x1B) = (u8) (M2C_FIELD(arg0, u8 *, 0x1B) & 0xBF);
        func_8012F41C(arg0, 3, 0);
        var_a0 = 6;
        if (M2C_FIELD(arg0, u8 *, 2) == 0x1C) {
            var_a0 = 0xC;
        }
        func_80026100(var_a0);
        func_8012F690(arg0, -1, 0x14, 0x3C);
        M2C_FIELD(arg0, u8 *, 6) = (u8) (M2C_FIELD(arg0, u8 *, 6) + 1);
    }
    if (M2C_FIELD(arg0, s16 *, 0x78) == 0) {
        func_80076D68(arg0);
    }
}

void func_8012F298(void *arg0) {
    s32 temp_v1;

    temp_v1 = func_8009A450() & 0xF;
    if (temp_v1 >= 0xA) {
        if (M2C_FIELD(arg0, u8 *, 2) == 0x1C) {
            func_8012F41C(arg0, 0, 0);
            M2C_FIELD(arg0, s8 *, 5) = 1;
            M2C_FIELD(arg0, s16 *, 0x72) = 0;
        }
    } else {
        if (temp_v1 >= 7) {
            func_8012F41C(arg0, 2, 0);
            M2C_FIELD(arg0, s16 *, 0x42) = 1;
        } else {
            M2C_FIELD(arg0, s16 *, 0x42) = 0;
        }
        M2C_FIELD(arg0, s16 *, 0x40) = 0x3C;
        M2C_FIELD(arg0, s8 *, 6) = 1;
    }
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8012F32C);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8012F41C);

s32 func_8012F4FC(u8 *a, s32 b) {
    M2C_FIELD(a, s32 *, 0x2C) += M2C_FIELD(a, s16 *, 0x48) * M2C_FIELD(a, s16 *, 0x44);
    M2C_FIELD(a, s32 *, 0x34) += M2C_FIELD(a, s16 *, 0x4C) * M2C_FIELD(a, s16 *, 0x44);
    if (b != 0) {
        return 0;
    }
    M2C_FIELD(a, s32 *, 0x30) += M2C_FIELD(a, s16 *, 0x4A) * M2C_FIELD(a, s16 *, 0x44);
    return 0;
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8012F56C);

s32 func_8012F634(u8 *a) {
    s16 m;
    u16 k = D_1F800172; u16 t = D_1F800174 | 0xF0; m = k | t;
    if (D_800E7E68 & m) {
        M2C_FIELD(a, s16 *, 0x42)++;
    }
    return M2C_FIELD(a, s16 *, 0x42) >= 3;
}

void func_8012F690(u8 *a, s32 x, s32 z, s32 w)
{
    if (x >= 0) {
        *(s16 *)(a + 0x80) = x;
        if (a[2] == 0x1C) {
            *(s16 *)(a + 0x80) = x + x / 2;
        }
        *(s16 *)(a + 0x82) = *(s16 *)(a + 0x80) * 2;
    }
    if (w >= 0) {
        s16 t;
        if (z >= 0) {
            *(s16 *)(a + 0x84) = z;
            if (a[2] == 0x1C) {
                *(s16 *)(a + 0x84) = z + z / 2;
            }
        }
        t = *(s16 *)(a + 0x84) + w;
        *(s16 *)(a + 0x86) = t;
        if (a[2] == 0x1C) {
            *(s16 *)(a + 0x86) = t + w / 2;
        }
    }
}

s32 func_8012F734(u8 *a)
{
    if ((u32)(D_1F800207_9c67 - 0xF) >= 6) return 1;
    if (D_1F800162_a8d4 >= -10000 && a[1] == 0) return 1;
    return 0;
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8012F788);

extern u8 D_8013FA74[];
static inline s32 fa5c_init(u8 *a)
{
    u8 *g = D_800ECF58;
    s32 r;

    if (func_800519E0(a, 0xF, *(s32 *)(g + 0x6C), D_8013FA74) == 0) {
        *(s32 *)(a + 0x3C) = *(s32 *)(g + 0x38);
        func_80040CDC(a, D_80144404, D_800A3D18);
        r = 1;
        a[0xB] = 0x40;
        a[0] = 9;
        *(s16 *)(a + 0x80) = 0x55;
        *(s16 *)(a + 0x82) = 0xAA;
        *(s16 *)(a + 0x84) = 0x80;
        *(s16 *)(a + 0x86) = 0x100;
        a[0x2B] = 0;
        a[0x29] = 0;
        *(s16 *)(a + 0x58) = 0;
        *(s16 *)(a + 0x56) = 0;
        *(s16 *)(a + 0x54) = 0;
    } else {
        r = 0;
    }
    return r;
}
void func_8012FA5C(u8 *a)
{
    switch (a[4]) {
    case 0:
        if (fa5c_init(a)) {
            a[0x7B] = 5;
            *(s32 *)(a + 0x2C) = 0x0ECD0000;
            *(s32 *)(a + 0x30) = 0xDBDD0000;
            *(s32 *)(a + 0x34) = 0x2A960000;
            a[0x2A] = 0x14;
            *(s16 *)(a + 0x56) = 0;
            func_80041718(a, a[0x7B], 0);
            a[4]++;
        }
        break;
    case 1:
        func_8012F788(a);
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

extern u8 D_8013FAEC[];
extern u8 D_8013FB64[];
s32 func_8012FBD8(u8 *p)
{
    u8 *s = D_800ECF58;

    if (func_800519E0(p, 0xF, *(s32 *)(s + 0x6C), D_8013FA74) != 0) {
        return 0;
    }
    *(s32 *)(p + 0x3C) = *(s32 *)(s + 0x38);
    func_80040CDC(p, D_80144404, D_800A3D18);
    p[0xB] = 0x40;
    p[0] = 9;
    *(s16 *)(p + 0x80) = 0x55;
    *(s16 *)(p + 0x82) = 0xAA;
    *(s16 *)(p + 0x84) = 0x80;
    *(s16 *)(p + 0x86) = 0x100;
    p[0x2B] = 0;
    p[0x29] = 0;
    *(s16 *)(p + 0x58) = 0;
    *(s16 *)(p + 0x56) = 0;
    *(s16 *)(p + 0x54) = 0;
    return 1;
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8012FC8C);

static inline s32 fdec_init(u8 *a)
{
    u8 *g = D_800ECF58;
    s32 r;

    if (func_800519E0(a, 0xF, *(s32 *)(g + 0x70), D_8013FAEC) == 0) {
        *(s32 *)(a + 0x3C) = *(s32 *)(g + 0x38);
        func_80040CDC(a, D_80144404, D_800A3D18);
        r = 1;
        a[0xB] = 0x40;
        a[0] = 9;
        *(s16 *)(a + 0x80) = 0x55;
        *(s16 *)(a + 0x82) = 0xAA;
        *(s16 *)(a + 0x84) = 0x80;
        *(s16 *)(a + 0x86) = 0xE0;
        a[0x2B] = 0;
        a[0x29] = 0;
        *(s16 *)(a + 0x58) = 0;
        *(s16 *)(a + 0x56) = 0;
        *(s16 *)(a + 0x54) = 0;
    } else {
        r = 0;
    }
    return r;
}
void func_8012FDEC(u8 *a)
{
    switch (a[4]) {
    case 0:
        if (fdec_init(a)) {
            a[0x7B] = 2;
            *(s32 *)(a + 0x2C) = 0x15010000;
            *(s32 *)(a + 0x30) = 0xE2E50000;
            *(s32 *)(a + 0x34) = 0x11EC0000;
            a[0x2A] = 1;
            *(s16 *)(a + 0x56) = 0;
            func_80041718(a, a[0x7B], 0);
            a[4]++;
        }
        break;
    case 1:
        func_8012FC8C(a);
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

s32 func_8012FF68(u8 *p)
{
    u8 *s = D_800ECF58;

    if (func_800519E0(p, 0xF, *(s32 *)(s + 0x70), D_8013FAEC) != 0) {
        return 0;
    }
    *(s32 *)(p + 0x3C) = *(s32 *)(s + 0x38);
    func_80040CDC(p, D_80144404, D_800A3D18);
    p[0xB] = 0x40;
    p[0] = 9;
    *(s16 *)(p + 0x80) = 0x55;
    *(s16 *)(p + 0x82) = 0xAA;
    *(s16 *)(p + 0x84) = 0x80;
    *(s16 *)(p + 0x86) = 0xE0;
    p[0x2B] = 0;
    p[0x29] = 0;
    *(s16 *)(p + 0x58) = 0;
    *(s16 *)(p + 0x56) = 0;
    *(s16 *)(p + 0x54) = 0;
    return 1;
}

extern u8 D_80141C70[];
extern u8 D_80141C80[];
extern u8 D_800BF8C8;
static inline s32 init_001c(u8 *a)
{
    u8 *g = D_800ECF58;
    s32 r;

    if (func_800519E0(a, 0xF, *(s32 *)(g + 0x74), D_8013FB64) == 0) {
        *(s32 *)(a + 0x3C) = *(s32 *)(g + 0x38);
        func_80040CDC(a, D_80144404, D_800A3D18);
        r = 1;
        a[0xB] = 0x40;
        a[0] = 9;
        *(s16 *)(a + 0x80) = 0x55;
        *(s16 *)(a + 0x82) = 0xAA;
        *(s16 *)(a + 0x84) = 0x80;
        *(s16 *)(a + 0x86) = 0xD0;
        a[0x2B] = 0;
        a[0x29] = 0;
        *(s16 *)(a + 0x58) = 0;
        *(s16 *)(a + 0x56) = 0;
        *(s16 *)(a + 0x54) = 0;
    } else {
        r = 0;
    }
    return r;
}
void func_8013001C(u8 *a)
{
    switch (a[4]) {
    case 0:
        if (init_001c(a)) {
            *(s32 *)(a + 0x2C) = 0x11C60000;
            *(s32 *)(a + 0x30) = 0xDF260000;
            *(s32 *)(a + 0x34) = 0x24CE0000;
            a[0x2A] = 0xA;
            *(s16 *)(a + 0x56) = 0;
            a[0x7B] = 0;
            func_80041718(a, 0, 0);
            a[4]++;
        }
        break;
    case 1:
        switch (a[5]) {
        case 0:
            if (func_80116B48(a) == 0) {
                goto skip;
            }
            if (a[0x2B] == 3) {
                func_80042354(1, 1);
                func_80040D68(a, D_80141C70);
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
                    if (D_800BF8C8 == 0xFF) {
                        a[0x7A] = 0x20;
                    } else {
                        a[0x7A] = 0x1F;
                    }
                    func_80040D68(a, D_80141C80);
                    a[0x70] = 2;
                    a[6]++;
                    break;
                case 1:
                    a[5] = 0;
                    break;
                }
            }
            break;
        }
        func_80041098(a);
        func_8004190C(a);
    skip:
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

s32 func_80130290(u8 *p)
{
    u8 *s = D_800ECF58;

    if (func_800519E0(p, 0xF, *(s32 *)(s + 0x74), D_8013FB64) != 0) {
        return 0;
    }
    *(s32 *)(p + 0x3C) = *(s32 *)(s + 0x38);
    func_80040CDC(p, D_80144404, D_800A3D18);
    p[0xB] = 0x40;
    p[0] = 9;
    *(s16 *)(p + 0x80) = 0x55;
    *(s16 *)(p + 0x82) = 0xAA;
    *(s16 *)(p + 0x84) = 0x80;
    *(s16 *)(p + 0x86) = 0xD0;
    p[0x2B] = 0;
    p[0x29] = 0;
    *(s16 *)(p + 0x58) = 0;
    *(s16 *)(p + 0x56) = 0;
    *(s16 *)(p + 0x54) = 0;
    return 1;
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", f_UpdateFirstReadyOrNotKujaraFoundSequence);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8013076C);

extern u8 D_800E7EA9;
extern u8 D_80141CB0[];
extern u8 D_80141D18[];
extern u8 D_80141D30[];
extern u8 D_80141D48[];
void func_801308E8(u8 *a)
{
    switch (a[6]) {
    case 0:
        func_8004766C(a);
        *(s16 *)(a + 0x4A) += *(s16 *)(a + 0x50);
        *(s32 *)(a + 0x30) += *(s16 *)(a + 0x4A) << 8;
        func_80041938(a, 0, 0x80);
        if (a[0x29] != 0) {
            if (!(D_800BFE56 & 0x10)) {
                *(s16 *)(a + 0x32) += 0x50;
                func_8003116C(0xD, a + 0x2C, -0x14);
                *(s16 *)(a + 0x32) -= 0x50;
                func_80074590(0x8A, 0xB, -0x32);
            } else {
                func_80074590(3, 0, 0);
            }
            *(s16 *)(a + 0x4A) = 0;
            a[0xB] = (a[0xB] & 0xC0) | 0x40;
            if (a[0x46] != 0xC3) {
                func_800416A8(a, -1, 0);
                func_80041718(a, 0xC3, 4);
            }
            *(s16 *)(a + 0x56) -= 0xC8;
            D_800BF870.pad1[0xB8] |= 4;
            a[6]++;
        }
        break;
    case 1:
        if (D_800E7EA9 & 0x80) {
            func_80040D68(a, D_80141D18);
            a[0x70] = 2;
            a[7] = 0;
            a[6]++;
        }
        break;
    case 2:
        func_80041098(a);
        if (a[0x70] == 0xFF) {
            switch (a[7]) {
            case 0:
                a[0x7A] = 0xB;
                func_80040D68(a, D_80141CB0);
                a[0x70] = 2;
                a[7]++;
                break;
            case 1:
                if (!(D_800BFE56 & 0x10)) {
                    func_80040D68(a, D_80141D30);
                } else {
                    func_80040D68(a, D_80141D48);
                }
                a[0x70] = 2;
                a[7]++;
                break;
            case 2:
                a[4] = 3;
                break;
            }
        }
        break;
    }
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80130B74);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80130EB4);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80130F7C);

extern u16 D_800BFE56;
extern u8 D_80141D60[];
extern u8 D_80141D70[];
extern u8 D_80141D90[];
void func_80131248(u8 *a)
{
    switch (a[6]) {
    case 0:
        func_8004766C(a);
        *(s16 *)(a + 0x4A) += *(s16 *)(a + 0x50);
        *(s32 *)(a + 0x30) += *(s16 *)(a + 0x4A) << 8;
        func_80041938(a, 0, 0x60);
        if (a[0x29] != 0) {
            if (!(D_800BFE56 & 0x10)) {
                *(s16 *)(a + 0x32) += 0x50;
                func_8003116C(0xD, a + 0x2C, -0x14);
                *(s16 *)(a + 0x32) -= 0x50;
                func_80074590(0x8A, 0xB, -0x32);
            } else {
                func_80074590(3, 0, 0);
            }
            *(s16 *)(a + 0x4A) = 0;
            a[0xB] = (a[0xB] & 0xC0) | 0x40;
            if (a[0x46] != 0xC3) {
                func_800416A8(a, -1, 0);
                func_80041718(a, 0xC3, 4);
            }
            *(s16 *)(a + 0x56) -= 0xC8;
            D_800BF870.pad1[0xB8] |= 0x10;
            a[6]++;
        }
        break;
    case 1:
        if (D_800E7EA9 & 0x80) {
            func_80040D68(a, D_80141D60);
            a[0x70] = 2;
            a[7] = 0;
            a[6]++;
        }
        break;
    case 2:
        func_80041098(a);
        if (a[0x70] == 0xFF) {
            switch (a[7]) {
            case 0:
                a[0x7A] = 0xA;
                func_80040D68(a, D_80141CB0);
                a[0x70] = 2;
                a[7]++;
                break;
            case 1:
                if (!(D_800BFE56 & 0x10)) {
                    func_80040D68(a, D_80141D70);
                } else {
                    func_80040D68(a, D_80141D90);
                }
                a[0x70] = 2;
                a[7]++;
                break;
            case 2:
                a[4] = 3;
                break;
            }
        }
        break;
    }
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_801314D4);

extern u16 D_800BFE56;
extern u8 D_80141DB0[];
extern u8 D_80141DC8[];
void func_80131848(u8 *a)
{
    switch (a[6]) {
    case 0:
        func_8004766C(a);
        *(s16 *)(a + 0x4A) += *(s16 *)(a + 0x50);
        *(s32 *)(a + 0x30) += *(s16 *)(a + 0x4A) << 8;
        func_80041938(a, 0, 0x50);
        if (a[0x29] != 0) {
            if (!(D_800BFE56 & 0x10)) {
                *(s16 *)(a + 0x32) += 0x50;
                func_8003116C(0xD, a + 0x2C, -0x14);
                *(s16 *)(a + 0x32) -= 0x50;
                func_80074590(0x8A, 0xB, -0x32);
            } else {
                func_80074590(3, 0, 0);
            }
            *(s16 *)(a + 0x4A) = 0;
            a[0xB] = (a[0xB] & 0xC0) | 0x40;
            if (a[0x46] != 0xC3) {
                func_800416A8(a, -1, 0);
                func_80041718(a, 0xC3, 4);
            }
            *(s16 *)(a + 0x56) -= 0xC8;
            D_800BF870.pad1[0xB8] |= 0x40;
            a[6]++;
        }
        break;
    case 1:
        if (D_800E7EA9 & 0x80) {
            func_80040D68(a, D_80141DB0);
            a[0x70] = 2;
            a[7] = 0;
            a[6]++;
        }
        break;
    case 2:
        func_80041098(a);
        if (a[0x70] == 0xFF) {
            switch (a[7]) {
            case 0:
                a[0x7A] = 9;
                func_80040D68(a, D_80141CB0);
                a[0x70] = 2;
                a[7]++;
                break;
            case 1:
                func_80040D68(a, D_80141DC8);
                a[0x70] = 2;
                a[7]++;
                break;
            case 2:
                a[4] = 3;
                break;
            }
        }
        break;
    }
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80131AA4);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80131D14);

extern u8 D_800E7EEE;
extern s32 D_1F800214;
void func_80131E08(u8 *a)
{
    switch (a[4]) {
    case 0:
        if (func_80051B70(a, 0xC, 0x2F) != 0) {
            break;
        }
        *(s16 *)(a + 0x80) = 0x3C;
        *(s16 *)(a + 0x82) = 0x78;
        a[0] = 1;
        *(s16 *)(a + 0x84) = 0xA0;
        *(s16 *)(a + 0x86) = 0xA0;
        a[0x29] = 0;
        *(s16 *)(a + 0x58) = 0;
        *(s16 *)(a + 0x56) = 0;
        *(s16 *)(a + 0x54) = 0;
        func_800517F8(a);
        a[4]++;
        break;
    case 1:
        func_8007778C(a);
        break;
    case 2:
        a[1] = 1;
        func_80077E7C(a);
        func_800517F8(a);
        switch (a[5]) {
        case 0:
        case 1:
            break;
        case 2:
        case 3:
            if (D_800E7EEE != 0) {
                func_8004BEC4();
            }
            ((u8 * (*)())func_8011B79C)(D_1F800214);
            func_8004D4C4(0x2D, 1);
            func_8004B0D8(a);
            func_80040B48(0x14);
            a[4] = 3;
            break;
        }
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

extern u8 D_8014163C[];
s32 func_80116B48();
void func_80131F6C(u8 *a)
{
    u8 *g;

    switch (a[4]) {
    case 0:
        g = D_800ECF58;
        if (func_800519E0(a, 0x10, *(s32 *)(g + 0x54), D_8014163C) != 0) {
            break;
        }
        *(s32 *)(a + 0x3C) = *(s32 *)(g + 0x58);
        a[0xB] = 0x0;
        func_8012F41C(a, 1, 0);
        *(u8 *)(a + 0x2A) = 0x11;
        func_8012CF08(a);
        *(s16 *)(a + 0x72) = 0x0;
        *(s16 *)(a + 0x64) = 0x87;
        *(s16 *)(a + 0x66) = 0x3C;
        *(s16 *)(a + 0x74) = 0xF;
        *(s16 *)(a + 0x76) = 0x12;
        a[4]++;
        break;
    case 1:
        ((void (*)())func_80116B48)(a);
        if (a[0x2B] != 0) {
            a[0x2B]--;
        } else {
            if (D_800BF809 != 0 || D_1F800137_104c != 0) {
                break;
            }
            *(s16 *)(a + 0x7C) = func_80076D68(a);
            *(s16 *)(a + 0x4E) = (*(s16 *)(a + 0x4E) + D_80141B0C[*(s16 *)(a + 0x7A)]) & 0xFFF;
            if (*(s16 *)(a + 0x7C) == 1) {
                *(s16 *)(a + 0x4E) = 0;
            }
            switch (a[5]) {
            case 0:
                func_801323A4(a);
                break;
            case 1:
                func_8012D1A0(a);
                break;
            case 2:
                func_8012D424(a);
                break;
            case 3:
                func_8012D844(a);
                break;
            case 4:
                func_8012DA04(a);
                break;
            }
            a[0x29] = 0;
            a[0x5F] = 0;
            if (a[1] != 0 && D_80141B00[*(s16 *)(a + 0x7A)] != 0 && *(u16 *)(*(u8 **)(a + 0x38) + 4) == 1) {
                func_80074590(0x8F, 0, 0);
            }
        }
        if (a[1] != 0) {
            func_800518FC(a);
        }
        break;
    case 2:
        func_8007778C(a);
        switch (a[5]) {
        case 0:
        case 4:
        case 5:
        case 6:
            if (D_800BF809 == 0 && D_1F800137_104c == 0) {
                func_8012E0A8(a);
            }
            break;
        case 1:
            func_8012F1E4(a);
            break;
        case 11:
            if (func_80080750(a, 0, 0) != 0) {
                a[4] = 3;
                return;
            }
            a[5] = 2;
        case 2:
        case 7:
        case 8:
            func_8012E6A4(a);
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

extern s8 D_1F8001A6[];
extern s8 D_1F8001BC[];
extern s8 D_1F8001BE[];
extern s8 D_1F8001C0[];
extern s8 D_1F8001C4[];
s32 func_801322A8(void *arg0, s16 arg1, s32 arg2) {
    s32 temp_a1;
    s32 temp_lo;
    s32 temp_s1;

    temp_s1 = (s32) (-func_80083E80(M2C_FIELD(arg0, s16 *, 0x56)) * arg1) >> 0xC;
    temp_lo = func_80083F50(M2C_FIELD(arg0, s16 *, 0x56)) * arg1;
    *((s16 *)D_1F8001BE) = M2C_FIELD(arg0, u16 *, 0x32) + arg2;
    *((s16 *)D_1F8001C0) = M2C_FIELD(arg0, u16 *, 0x36) + temp_s1;
    temp_a1 = temp_lo >> 0xC;
    *((s16 *)D_1F8001BC) = M2C_FIELD(arg0, u16 *, 0x2E) + temp_a1;
    if (func_800498C8(arg0, temp_a1) != 0) {
        if (func_80045724() != 0) {
            if ((*((u16 *)D_1F8001A6) & 0xF00) == 0x700) {
                return 2;
            }
            M2C_FIELD(arg0, u16 *, 0x32) = (u16) (M2C_FIELD(arg0, u16 *, 0x32) + *((u16 *)D_1F8001C4));
            return 1;
        }
        /* Duplicate return node #6. Try simplifying control flow for better match */
        return 0;
    }
    return 0;
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_801323A4);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_801324B0);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_801326D0);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80132968);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80132B14);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80132D10);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80132FF4);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_801332D0);

INCLUDE_ASM("asm/a04/nonmatchings/a04", f_UpdateBigIcePigActor);

u8 *func_80133A30(s32 a, s32 b) {
    u8 *p = func_8007A980(3, 2, 0);

    if (p == NULL) {
        return NULL;
    }
    M2C_FIELD(p, void **, 0x1C) = f_UpdateBigIcePigActor;
    p[0x2] = 40;
    p[0x3] = (b | 0x80);
    return p;
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80133A88);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80133E7C);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80133FF4);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80134350);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80134998);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80134CB4);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80134EBC);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_801351B8);

extern s8 D_1F800162[];
extern s8 D_1F800164[];
extern s8 D_1F800207[];
extern s16 D_800E7FFE;
s32 func_80135250(void *arg0, s32 arg1) {
    s32 temp_v1;
    u8 temp_v1_2;

    if ((D_800E7FFE & 0x8200) || ((temp_v1_2 = *((u8 *)D_1F800207), (temp_v1_2 != 1)) && ((u32) (temp_v1_2 - 5) >= 3U)) || ((u32) (((M2C_FIELD(arg0, u16 *, 0x32) - *((u16 *)D_1F800162)) + 0x96) & 0xFFFF) >= 0x259U)) {
        return 0;
    }
    temp_v1 = *((u16 *)D_1F800164) - M2C_FIELD(arg0, u16 *, 0x36);
    if (arg1 != 0) {
        return (u32) ((temp_v1 + 0x12C) & 0xFFFF) < 0x258U;
    }
    if ((u32) ((temp_v1 + 0x1F4) & 0xFFFF) >= 0x3E8U) {
        return ((u32) ((temp_v1 + 0x320) & 0xFFFF) < 0x640U) * 2;
    }
    return 1;
}

extern s16 D_80141E04[][4];
void func_80135300(u8 *a, s32 i) {
    M2C_FIELD(a, s16 *, 0x80) = D_80141E04[i][0];
    M2C_FIELD(a, s16 *, 0x82) = D_80141E04[i][1];
    M2C_FIELD(a, s16 *, 0x84) = D_80141E04[i][2];
    M2C_FIELD(a, s16 *, 0x86) = D_80141E04[i][3];
}

extern s8 D_1F800160[];
s32 func_80135340(u8 *a) {
    s16 dz, dx;

    if (D_800E7FFE & 0x8200) {
        return 0;
    }
    dx = *(u16 *)D_1F800160 - M2C_FIELD(a, u16 *, 0x2E);
    dz = *(u16 *)D_1F800164 - M2C_FIELD(a, u16 *, 0x36);
    return func_80077768((s16)-func_80085690(dz, dx), M2C_FIELD(a, s16 *, 0x56), 0) != 0;
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_801353C8);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_801354B8);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80135570);

void func_80135864(void *arg0);
void func_80135698(u8 *a)
{
    s32 v;

    switch (a[4]) {
    case 0:
        if (func_80051B70(a, 0xC, 6) != 0) {
            break;
        }
        a[0xB] = 0xF;
        a[0xD] |= 4;
        (*(u8 **)(a + 0xC0))[0x3F] = 0xC;
        *(s16 *)(a + 0x80) = 0x7F;
        *(s16 *)(a + 0x82) = 0xFE;
        *(s16 *)(a + 0x84) = 0xBE;
        *(s16 *)(a + 0x86) = 0x114;
        a[0] = 1;
        a[0x29] = 0;
        a[0x2A] = 0;
        a[4]++;
        func_80041194(a, *(s16 *)(a + 0x86) - *(s16 *)(a + 0x84), 0, 0);
        break;
    case 1:
        ((void (*)())func_80121C70)(a);
        v = a[1];
        goto tail;
    case 2:
        switch (a[5]) {
        case 0:
        case 1:
            break;
        case 2:
            func_80135864(a);
            a[4] = 3;
            return;
        case 3:
            *(s16 *)(a + 0x58) += 0x200;
            *(s16 *)(a + 0x32) += 0x20;
            if (func_8004766C(a) == 0) {
                return;
            }
            if (func_80049250(a, 0, (s16)(*(u16 *)(a + 0x86) - *(u16 *)(a + 0x84)))) {
                func_80135864(a);
                a[4] = 3;
                return;
            }
            break;
        }
        v = func_8007778C(a);
    tail:
        if (v) {
            func_800517F8(a);
        }
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

void func_80135864(void *arg0) {
    s32 temp_s1;

    temp_s1 = arg0 + 0x2C;
    func_80027144(M2C_FIELD(M2C_FIELD(arg0, void **, 0xC0), s32 *, 0x40), temp_s1, 0x700, 0x18);
    func_80074590(0xC, 0, 0);
    M2C_FIELD(arg0, u16 *, 0x32) = (u16) (M2C_FIELD(arg0, u16 *, 0x32) + 0x64);
    func_80027144(M2C_FIELD(M2C_FIELD(arg0, void **, 0xC0), s32 *, 0x40), temp_s1, 0x800, -0x7FE8);
    func_80074590(0xC, 0, 0);
    if (func_8013AA98(arg0) != 0) {
        D_800BF870.pad1[0x157] += 1;
    }
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80135910);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80135AC4);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80135DCC);

typedef struct { u8 pad[0x3C]; u8 *p3C; } S808;
extern S808 D_800BF808_bf2e;
extern u8 D_800BF80E;
extern u8 *D_800BF844;
s32 func_8013632C(u8 *a)
{
    u8 *b;
    u8 *e;
    S808 *g;
    s16 t;

    switch (a[0x78]) {
    case 0:
        func_800440E4(D_800E7E80, 0xCF, 0);
        e = func_8006FB0C(a, 0x2D);
        g = &D_800BF808_bf2e;
        g->p3C = e;
        if (e != 0) {
            *(s16 *)(e + 0x60) = 0x30;
            g->p3C[0x5E] = 0;
        }
        func_8004ED0C(0x2D, 4);
        func_8004D650(0x2D, 1);
        a[0x78]++;
        break;
    case 1:
        if (D_800BF80E != 0) {
            func_80041718(a, 0x13, 4);
            a[0x78]++;
        }
        break;
    case 2:
        if (*(u16 *)(*(u8 **)(a + 0x38) + 4) != 0) {
            func_80041718(a, 0x18, 4);
            func_800440E4(D_800E7E80, 2, 4);
            b = D_800BF844;
            *(s16 *)(b + 0x60) = 0;
            b[5] = 1;
            *(s16 *)(b + 0x58) = 0;
            *(s16 *)(b + 0x2E) = *(s16 *)(*(u8 **)(a + 0xDC) + 0x2C) - ((func_80083E80(0) * 0xA0) >> 12);
            *(s16 *)(b + 0x32) = *(s16 *)(*(u8 **)(a + 0xDC) + 0x30) + ((func_80083F50(*(s16 *)(b + 0x58)) * 0xA0) >> 12);
            *(s16 *)(b + 0x36) = *(s16 *)(*(u8 **)(a + 0xDC) + 0x34);
            a[0x78]++;
        }
        break;
    case 3:
        b = D_800BF844;
        *(s16 *)(b + 0x2E) = *(s16 *)(*(u8 **)(a + 0xDC) + 0x2C) - ((func_80083E80(*(s16 *)(b + 0x58)) * 0xA0) >> 12);
        *(s16 *)(b + 0x32) = *(s16 *)(*(u8 **)(a + 0xDC) + 0x30) + ((func_80083F50(*(s16 *)(b + 0x58)) * 0xA0) >> 12);
        *(s16 *)(b + 0x36) = *(s16 *)(*(u8 **)(a + 0xDC) + 0x34);
        if ((*(s16 *)(b + 0x58) -= 0x78) < -0xBB7) {
            func_80041718(a, 0, 4);
            b[0x5E] = 3;
            b[5] = 0;
            *(s16 *)(b + 0x60) = 0x3C;
            *(s16 *)(b + 0x62) = 0;
            *(s16 *)(b + 0x58) = 0;
            a[0] = 2;
            *(s16 *)(a + 0x80) = 0x8C;
            *(s16 *)(a + 0x40) = 0;
            a[0x78]++;
        }
        break;
    case 4:
        if (++*(s16 *)(a + 0x40) >= 0x1E) {
            return 1;
        }
        break;
    }
    return 0;
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", f_UpdateSantaBringTheBigSackConversation);

extern u8 D_8013FBDC[];
extern u8 D_80017FE8[];
static inline s32 santa_setup(u8 *a, u8 *g)
{
    u8 *e;

    a[0x47] = 0;
    if (D_800ED098 == 0) {
        return 0;
    }
    a[9] = 0x10;
    e = func_8007AAE8();
    *(u8 **)(a + 0xFC) = e;
    *(s16 *)(e + 6) = 7;
    *(s16 *)(e + 0) = 0;
    *(s16 *)(e + 2) = 0;
    *(s16 *)(e + 4) = 0;
    *(s16 *)(e + 0x38) = 0x1000;
    *(s16 *)(e + 0x3A) = 0x1000;
    *(s16 *)(e + 0x3C) = 0x1000;
    func_80051B04(e, 1, 0x13);
    *(s32 *)(a + 0x3C) = *(s32 *)(g + 0x10);
    *(u8 **)(a + 0x7C) = D_80017FE8;
    if (D_800BFA00 != 0) {
        func_80041718(a, 0xC3, 0);
    } else {
        func_80041718(a, 0xC1, 0);
    }
    *(s32 *)(a + 0x2C) = 0x11940000;
    *(s32 *)(a + 0x30) = 0xE5440000;
    *(s32 *)(a + 0x34) = 0x24DF0000;
    a[0x7B] = 0;
    *(s16 *)(a + 0x56) = 0x800;
    return 1;
}
void func_801368A0(u8 *a)
{
    u8 *g;

    switch (a[4]) {
    case 0:
        g = D_800ECF58;
        if (func_800519E0(a, 0xF, *(s32 *)(g + 0x3C), D_8013FBDC) != 0) {
            break;
        }
        *(s32 *)(a + 0x3C) = *(s32 *)(g + 0x38);
        func_80040CDC(a, D_80144404, D_800A3D18);
        a[0] = 9;
        *(s16 *)(a + 0x80) = 0x64;
        *(s16 *)(a + 0x82) = 0xC8;
        *(s16 *)(a + 0x84) = 0x90;
        a[0xB] = 0;
        *(s16 *)(a + 0x86) = 0x110;
        a[0x2B] = 0;
        a[0x29] = 0;
        *(s16 *)(a + 0x58) = 0;
        *(s16 *)(a + 0x56) = 0;
        *(s16 *)(a + 0x54) = 0;
        if (a[3] == 0 && !santa_setup(a, g)) {
            break;
        }
        a[4]++;
        break;
    case 1:
        if (a[3] == 0) {
            f_UpdateSantaBringTheBigSackConversation(a);
        }
        if (a[1] != 0) {
            func_800518FC(a);
        }
        a[0x2B] = 0;
        break;
    case 2:
        break;
    case 3:
        if (a[3] == 0) {
            a[9] = 0x10;
        }
        func_8007A624(a);
        break;
    }
}

s32 func_80136AC8(void *arg0) {
    M2C_FIELD(arg0, u8 *, 0x47) = (u8) M2C_FIELD(arg0, u8 *, 0x72);
    return 1;
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80136ADC);

extern u8 D_8013FCCC[];
extern u8 D_8013FC54[];
void func_80136CB8(u8 *a)
{
    u8 *g;
    u8 *st;
    u8 *tbl;

    switch (a[4]) {
    case 0:
        st = (u8 *)&D_800BF870;
        if (!((*(u16 *)(st + 0x5E6) >> st[0]) & 1)) {
            tbl = D_8013FC54;
        } else {
            tbl = D_8013FCCC;
        }
        g = D_800ECF58;
        if (func_800519E0(a, 0xF, *(s32 *)(g + 0x3C), tbl) != 0) {
            break;
        }
        *(s32 *)(a + 0x3C) = *(s32 *)(g + 0x38);
        func_80040CDC(a, D_80144404, D_800A3D18);
        a[0] = 9;
        *(s16 *)(a + 0x80) = 0x64;
        *(s16 *)(a + 0x82) = 0xC8;
        *(s16 *)(a + 0x84) = 0x90;
        a[0xB] = 0;
        *(s16 *)(a + 0x86) = 0x154;
        a[0x2B] = 0;
        a[0x29] = 0;
        *(s16 *)(a + 0x58) = 0;
        *(s16 *)(a + 0x56) = 0;
        *(s16 *)(a + 0x54) = 0;
        if (a[3] == 0) {
            a[0x7B] = 2;
            *(s32 *)(a + 0x2C) = 0x09DF0000;
            *(s32 *)(a + 0x30) = 0xD3BC0000;
            *(s32 *)(a + 0x34) = 0x2EDA0000;
            a[0x2A] = 0x19;
            *(s16 *)(a + 0x56) = 0;
        }
        func_80041718(a, a[0x7B], 0);
        a[4]++;
        break;
    case 1:
        if (a[3] == 0) {
            func_80136ADC(a);
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

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80136E68);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80136F24);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80137108);

extern u8 D_80145910[];
void func_80137378(u8 *a)
{
    switch (a[6]) {
    case 0:
        *(s16 *)(a + 0x40) = 0x1E;
        a[6]++;
        func_80077C40(a, D_80145910, 1);
        break;
    case 1:
        *(s16 *)(a + 0x32) -= 1;
        *(s16 *)(a + 0x36) -= 4;
        *(s16 *)(a + 0x54) -= 8;
        if (--*(s16 *)(a + 0x40) == 0) {
            *(s16 *)(a + 0x40) = 0xA;
            a[6]++;
        }
        break;
    case 2:
        *(s16 *)(a + 0x32) -= 2;
        *(s16 *)(a + 0x36) -= 4;
        *(s16 *)(a + 0x54) -= 0xC;
        if (--*(s16 *)(a + 0x40) == 0) {
            *(s16 *)(a + 0x40) = 5;
            a[6]++;
            func_80077C40(a, D_80145910, 2);
        }
        break;
    case 3:
        *(s16 *)(a + 0x32) += 4;
        *(s16 *)(a + 0x36) += 8;
        *(s16 *)(a + 0x54) += 0x18;
        if (--*(s16 *)(a + 0x40) == 0) {
            *(s16 *)(a + 0x40) = 0xF;
            a[6]++;
        }
        break;
    case 4:
        *(s16 *)(a + 0x32) += 2;
        *(s16 *)(a + 0x36) += 8;
        *(s16 *)(a + 0x54) += 0x10;
        if (--*(s16 *)(a + 0x40) == 0) {
            a[6] = 0;
        }
        break;
    }
}

void func_80137514(u8 *a)
{
    switch (a[5]) {
    case 0:
        if (D_800BF9BB == 0) {
            a[5]++;
            func_80077C40(a, D_80145910, 4);
            *(s16 *)(a + 0x56) = 0xC00;
            *(s16 *)(a + 0x54) = 0x740;
            *(s16 *)(a + 0x36) -= 0x96;
            *(s16 *)(a + 0x32) -= 0x50;
        } else {
            a[5] = 6;
            func_80077C40(a, D_80145910, 2);
            *(s16 *)(a + 0x56) = 0xC00;
        }
        break;
    case 1:
        if (D_800BF9BB == 2) {
            func_80077C40(a, D_80145910, 3);
            *(s16 *)(a + 0x56) = 0xC00;
            *(s16 *)(a + 0x54) = 0;
            *(s16 *)(a + 0x40) = 8;
            a[5]++;
        }
        break;
    case 2:
        *(s16 *)(a + 0x32) += 0xA;
        *(s32 *)(a + 0x34) += 0x64000;
        if (--*(s16 *)(a + 0x40) == -1) {
            a[5]++;
        }
        break;
    case 3:
        if (D_800BF9BB == 3) {
            func_80077C40(a, D_80145910, 1);
            *(s16 *)(a + 0x40) = 0x10;
            a[5]++;
        }
        break;
    case 4:
        {
            s16 t;
            *(s32 *)(a + 0x34) += 0x64000;
            t = --*(s16 *)(a + 0x40);
            if (t == -1) {
                a[5]++;
            }
        }
        break;
    case 5:
        if (D_800BF9BB == 4 && a[0x18] != 0) {
            func_80077C40(a, D_80145910, 2);
            a[5]++;
        }
        break;
    case 6:
        func_80137378(a);
        break;
    }
    if (a[0xBF] == 0) {
        a[0x18] = func_80076D68(a);
    }
}

extern u8 D_80143E78[];
void func_80137748(u8 *a)
{
    u8 *g;

    switch (a[4]) {
    case 0:
        g = D_800ECF58;
        if (func_800519E0(a, 5, *(s32 *)(g + 0x98), D_80143E78) != 0) {
            break;
        }
        *(s32 *)(a + 0x3C) = *(s32 *)(g + 0x9C);
        func_80077C40(a, D_80145910, 0);
        *(s16 *)(a + 0x54) = 0;
        *(s16 *)(a + 0x56) = 0;
        *(s16 *)(a + 0x58) = 0;
        a[0xBF] = 0;
        a[4]++;
        break;
    case 1:
        switch (a[3]) {
        case 0:
            func_80137108(a);
            break;
        case 1:
            func_80137514(a);
            break;
        }
        a[1] = 1;
        func_80077E7C(a);
        func_800518FC(a);
        break;
    case 2:
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80137870);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_801379F0);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80137BDC);

extern s8 D_800E806C;
void func_80137FC8(u8 *a)
{
    u8 *p = D_800E7E80;

    switch (a[5]) {
    case 0:
        if (D_800BF9BB == 6) {
            D_800E806C = 1;
            a[5]++;
            p[5] = 0x1E;
            p[6] = 2;
            p[7] = 0;
        }
        break;
    case 1:
        if (func_80041438(p, 0x400, 0x100) != 0) {
            a[5]++;
            p[5] = 0;
            p[6] = 0;
            p[7] = 0;
        }
        break;
    case 2:
        D_1F800190 = 0x80;
        if (*(s16 *)(p + 0x36) < 0x2F44) {
            D_1F800190 = 0;
            p[5] = 0x1E;
            p[6] = 2;
            p[7] = 0;
            func_80054D14(p, 2, 0);
            a[5]++;
        }
        func_8006CBA8(p + 0x2C);
        break;
    case 3:
        if (func_80041438(p, 0x800, 0x100) != 0) {
            a[5]++;
        }
        break;
    case 4:
        D_800BF9BB = 0x80;
        a[4] = 3;
        break;
    }
}

extern s16 D_800E7FEE;
/* func_801383E8, inlined */
static inline void func_801383E8_inl(void *arg0) {
    if (D_800E7FEE != 0) {
        func_8004D4C4(0x2E, 1);
        func_8004B0D8(arg0);
        func_80040C00(0x17);
        M2C_FIELD(arg0, s8 *, 4) = 3;
    }
}
/* func_80138438, inlined */
static inline void func_80138438_inl(void *arg0) {
    void *temp_v0;

    temp_v0 = func_8007AAE8();
    M2C_FIELD(arg0, void **, 0xC4) = temp_v0;
    M2C_FIELD(temp_v0, s16 *, 6) = -1;
    M2C_FIELD(M2C_FIELD(arg0, void **, 0xC4), s16 *, 0) = 0;
    M2C_FIELD(M2C_FIELD(arg0, void **, 0xC4), s16 *, 2) = 0;
    M2C_FIELD(M2C_FIELD(arg0, void **, 0xC4), s16 *, 4) = 0;
    M2C_FIELD(M2C_FIELD(arg0, void **, 0xC4), s16 *, 8) = 0;
    M2C_FIELD(M2C_FIELD(arg0, void **, 0xC4), s16 *, 0xA) = 0x400;
    M2C_FIELD(M2C_FIELD(arg0, void **, 0xC4), s16 *, 0xC) = 0;
    M2C_FIELD(M2C_FIELD(arg0, void **, 0xC4), s16 *, 0x38) = 0x1000;
    M2C_FIELD(M2C_FIELD(arg0, void **, 0xC4), s16 *, 0x3A) = 0x1000;
    M2C_FIELD(M2C_FIELD(arg0, void **, 0xC4), s16 *, 0x3C) = 0x1000;
    func_80051B04(M2C_FIELD(arg0, void **, 0xC4), 0xC, 0x20);
    M2C_FIELD(arg0, s8 *, 8) = 2;
    M2C_FIELD(arg0, s8 *, 9) = 2;
}
void func_80138140(u8 *a)
{
    s32 one = 1;

    switch (a[4]) {
    case 0:
        if (func_80051B70(a, 0xC, 0x10) == 0) {
            *(s16 *)(a + 0x80) = 0x3C;
            *(s16 *)(a + 0x82) = 0x78;
            *(s16 *)(a + 0x84) = 0x6E;
            *(s16 *)(a + 0x86) = 0x7C;
            a[0x5E] = 0;
            a[0xB] = 0;
            *(s16 *)(a + 0x54) = 0;
            *(s16 *)(a + 0x56) = 0;
            *(s16 *)(a + 0x58) = 0;
            a[4]++;
            if (a[3] < 2) {
                a[0] = one;
                *(s16 *)(a + 0x60) = *(s16 *)(a + 0x2E);
                *(s16 *)(a + 0x62) = *(s16 *)(a + 0x32);
                *(s16 *)(a + 0x64) = *(s16 *)(a + 0x36);
                func_80138438_inl(a);
            }
            func_8004766C(a);
            func_80049760(a);
            *(s16 *)(a + 0x56) = D_1F8001A0;
        }
        break;
    case 1:
        switch (a[3]) {
        case 0:
            func_80137870(a);
            break;
        case 1:
            func_801379F0(a);
            break;
        case 2:
            func_80137BDC(a);
            break;
        case 3:
            func_80137FC8(a);
            break;
        }
        break;
    case 2:
        if (func_8007778C(a) != 0) {
            func_80051844(a);
        }
        switch (a[5]) {
        case 0:
        case 1:
            break;
        case 2:
        case 3:
            func_801383E8_inl(a);
            break;
        case 4:
        case 5:
        case 6:
            break;
        }
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

void func_801383E8(void *arg0) {
    if (D_800E7FEE != 0) {
        func_8004D4C4(0x2E, 1);
        func_8004B0D8(arg0);
        func_80040C00(0x17);
        M2C_FIELD(arg0, s8 *, 4) = 3;
    }
}

void func_80138438(void *arg0) {
    void *temp_v0;

    temp_v0 = func_8007AAE8();
    M2C_FIELD(arg0, void **, 0xC4) = temp_v0;
    M2C_FIELD(temp_v0, s16 *, 6) = -1;
    M2C_FIELD(M2C_FIELD(arg0, void **, 0xC4), s16 *, 0) = 0;
    M2C_FIELD(M2C_FIELD(arg0, void **, 0xC4), s16 *, 2) = 0;
    M2C_FIELD(M2C_FIELD(arg0, void **, 0xC4), s16 *, 4) = 0;
    M2C_FIELD(M2C_FIELD(arg0, void **, 0xC4), s16 *, 8) = 0;
    M2C_FIELD(M2C_FIELD(arg0, void **, 0xC4), s16 *, 0xA) = 0x400;
    M2C_FIELD(M2C_FIELD(arg0, void **, 0xC4), s16 *, 0xC) = 0;
    M2C_FIELD(M2C_FIELD(arg0, void **, 0xC4), s16 *, 0x38) = 0x1000;
    M2C_FIELD(M2C_FIELD(arg0, void **, 0xC4), s16 *, 0x3A) = 0x1000;
    M2C_FIELD(M2C_FIELD(arg0, void **, 0xC4), s16 *, 0x3C) = 0x1000;
    func_80051B04(M2C_FIELD(arg0, void **, 0xC4), 0xC, 0x20);
    M2C_FIELD(arg0, s8 *, 8) = 2;
    M2C_FIELD(arg0, s8 *, 9) = 2;
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_801384EC);

void func_801387F4(u8 *a)
{
    u8 *p;

    switch (a[4]) {
    case 0:
        if (func_80051B70(a, 0xC, D_80141AB7) != 0) {
            break;
        }
        a[0] = 1;
        a[0x2B] = 0;
        if (*(u16 *)(*(u8 **)(a + 0x10) + 0xB8) == 0x1200) {
            *(s16 *)(a + 0x60) = 0x1800;
        } else {
            *(s16 *)(a + 0x60) = 0x1400;
        }
        *(s16 *)(a + 0xBC) = 0x200;
        *(s16 *)(a + 0xBA) = 0x200;
        *(s16 *)(a + 0xB8) = 0x200;
        *(s16 *)(a + 0x80) = 0x64;
        *(s16 *)(a + 0x82) = 0xC8;
        *(s16 *)(a + 0x84) = 0x64;
        *(s16 *)(a + 0x86) = 0xC8;
        a[4]++;
        break;
    case 1:
        func_80116B48(a);
        if (a[0x2B] != 0) {
            a[4] = 2;
            break;
        }
        if (D_1F800137_104c == 0) {
            func_801384EC(a);
        }
        if (a[1] != 0) {
            func_800518FC(a);
        }
        break;
    case 2:
        p = *(u8 **)(a + 0x10);
        if (p != NULL) {
            p[0xBF] = 0;
            *(u8 **)(a + 0x10) = NULL;
        }
        if (func_80116B48(a)) {
            func_800518FC(a);
        }
        func_8003116C(0x504, a + 0x2C, -0x32);
        func_8003116C(0x503, a + 0x2C, -0x32);
        a[4] = 3;
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80138998);

INCLUDE_ASM("asm/a04/nonmatchings/a04", f_UpdateSnowFireflyNestBlink);

void func_80138B74(void *arg0) {
    u16 temp_v0;
    u16 temp_v0_2;
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 6);
    switch (temp_v1) {                              /* irregular */
    case 0:
        temp_v0 = (M2C_FIELD(arg0, u16 *, 0x4E) - 0x100) & 0xFFF;
        M2C_FIELD(arg0, u16 *, 0x4E) = temp_v0;
        if (temp_v0 == 0) {
            M2C_FIELD(arg0, u8 *, 6) = (u8) (M2C_FIELD(arg0, u8 *, 6) + 1);
        }
        M2C_FIELD(arg0, s16 *, 0x32) = (s16) (M2C_FIELD(arg0, u16 *, 0x66) + ((s32) (func_80083E80((s16) M2C_FIELD(arg0, u16 *, 0x4E)) * 0x60) >> 0xC));
        return;
    case 1:
        temp_v0_2 = (M2C_FIELD(arg0, u16 *, 0x4E) - 0x100) & 0xFFF;
        M2C_FIELD(arg0, u16 *, 0x4E) = temp_v0_2;
        if (temp_v0_2 == 0) {
            M2C_FIELD(arg0, u8 *, 6) = (u8) (M2C_FIELD(arg0, u8 *, 6) + 1);
        }
        M2C_FIELD(arg0, s16 *, 0x32) = (s16) (M2C_FIELD(arg0, u16 *, 0x66) + ((s32) (func_80083E80((s16) M2C_FIELD(arg0, u16 *, 0x4E)) << 6) >> 0xC));
        return;
    case 2:
        M2C_FIELD(arg0, s8 *, 0) = 1;
        M2C_FIELD(arg0, s8 *, 4) = 1;
        M2C_FIELD(arg0, s8 *, 5) = 0;
        M2C_FIELD(arg0, u8 *, 6) = 0U;
        return;
    }
}

/* func_80121C70, inlined */
static inline void func_80121C70_inl(u8 *a) {
    if ((*((s16 *)D_1F800164) >= 0x300C) && (*((s16 *)D_1F8000F2) < 0x400)) {
        func_8007703C(a);
        return;
    }
    func_8007778C(a);
}
/* func_801390EC, inlined */
static inline void func_801390EC_inl(void *arg0) {
    u16 temp_v0;
    u16 temp_v0_2;
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 5);
    switch (temp_v1) {
    case 0:
        if (M2C_FIELD(arg0, u8 *, 0x2B) != 0) {
            M2C_FIELD(arg0, u8 *, 5) = 1U;
            M2C_FIELD(arg0, u16 *, 0x42) = 2U;
            return;
        }
        return;
    case 1:
        temp_v0 = (M2C_FIELD(arg0, u16 *, 0x4E) + 0x200) & 0xFFF;
        M2C_FIELD(arg0, u16 *, 0x4E) = temp_v0;
        if (temp_v0 == 0) {
            temp_v0_2 = M2C_FIELD(arg0, u16 *, 0x42) - 1;
            M2C_FIELD(arg0, u16 *, 0x42) = temp_v0_2;
            if ((temp_v0_2 << 0x10) == 0) {
                M2C_FIELD(arg0, u8 *, 5) = 0U;
            }
        }
        M2C_FIELD(arg0, s16 *, 0x32) = (s16) (M2C_FIELD(arg0, u16 *, 0x66) + ((s32) (func_80083E80((s16) M2C_FIELD(arg0, u16 *, 0x4E)) << 5) >> 0xC));
        break;
    }
}
/* func_80139058, inlined */
static inline void func_80139058_inl(u8 *a)
{
    switch (a[6]) {
    case 0:
        a[6]++;
        func_80040B48(0x6C);
    case 1:
        *(s16 *)(a + 0x4E) = (*(s16 *)(a + 0x4E) + 0x100) & 0xFFF;
        if (*(s16 *)(a + 0x4E) == 0) {
            a[6]++;
        }
        *(s16 *)(a + 0x32) = *(s16 *)(a + 0x66) + ((func_80083E80(*(s16 *)(a + 0x4E)) << 6) >> 12);
        break;
    }
}
void func_80138C80(u8 *a)
{
    s32 i = 1;


    switch (a[4]) {
    case 0:

        if (D_800BF870.pad1[0x19B] & 0x80) {
            for (i = 0; i < 5; i++) {
                if (!((D_800BF870.pad1[0x19B] >> i) & 1)) {
                    func_8013EBE4(a + 0x2C, 1, i);
                }
            }
            a[4] = 3;
            break;
        }
        if (func_80051B70(a, 0xC, 0x24) != 0) {
            break;
        }
        H(a, 0x80) = 100;
        H(a, 0x82) = 100;
        H(a, 0x84) = 0x6E;
        a[0] = i;
        H(a, 0x86) = 0xDC;
        a[4]++;
        func_8004766C(a);
        func_80048750(a);
        H(a, 0x56) = D_1F8001A0;
        H(*(u8 **)(a + 0xC0), 0xC) = 0x300;
        func_8011BDFC(a, 0);
        func_8011BDFC(a, 1);
        func_8011BF00(a, 0);
        func_8011BF00(a, 1);
        func_8011BF00(a, 2);
        func_8011BF00(a, 3);
        func_8011BF00(a, 4);
        H(a, 0x5C) = 0x363F;
        H(a, 0x40) = 0;
        H(a, 0xE) = 0;
        a[0xD] |= 8;
        H(a, 0x64) = H(a, 0x2E);
        H(a, 0x66) = H(a, 0x32);
        H(a, 0x68) = H(a, 0x36);
        func_800517F8(a);
        H(a, 0x4E) = 0;
        break;
    case 1:
        func_80121C70_inl(a);
        func_801390EC_inl(a);
        if (a[1] != 0) {
            f_UpdateSnowFireflyNestBlink(a);
            func_800517F8(a);
        }
        a[0x2B] = 0;
        break;
    case 2:
        switch (a[5]) {
        case 0:
            break;
        case 1:
            func_80139058_inl(a);
            break;
        case 2:
            func_80138B74(a);
            break;
        case 3:
            func_8003116C(0x50C, a + 0x2C, -0x32);
            a[4] = 3;
            func_80040B48(0x6C);
            break;
        case 4:
        case 5:
        case 6:
            break;
        }
        if (func_8007778C(a) != 0) {
            f_UpdateSnowFireflyNestBlink(a);
            func_800517F8(a);
        }
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

void func_80139058(u8 *a)
{
    switch (a[6]) {
    case 0:
        a[6]++;
        func_80040B48(0x6C);
    case 1:
        *(s16 *)(a + 0x4E) = (*(s16 *)(a + 0x4E) + 0x100) & 0xFFF;
        if (*(s16 *)(a + 0x4E) == 0) {
            a[6]++;
        }
        *(s16 *)(a + 0x32) = *(s16 *)(a + 0x66) + ((func_80083E80(*(s16 *)(a + 0x4E)) << 6) >> 12);
        break;
    }
}

void func_801390EC(void *arg0) {
    u16 temp_v0;
    u16 temp_v0_2;
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 5);
    switch (temp_v1) {                              /* irregular */
    case 0:
        if (M2C_FIELD(arg0, u8 *, 0x2B) != 0) {
            M2C_FIELD(arg0, u8 *, 5) = 1U;
            M2C_FIELD(arg0, u16 *, 0x42) = 2U;
            return;
        }
        return;
    case 1:
        temp_v0 = (M2C_FIELD(arg0, u16 *, 0x4E) + 0x200) & 0xFFF;
        M2C_FIELD(arg0, u16 *, 0x4E) = temp_v0;
        if (temp_v0 == 0) {
            temp_v0_2 = M2C_FIELD(arg0, u16 *, 0x42) - 1;
            M2C_FIELD(arg0, u16 *, 0x42) = temp_v0_2;
            if ((temp_v0_2 << 0x10) == 0) {
                M2C_FIELD(arg0, u8 *, 5) = 0U;
            }
        }
        M2C_FIELD(arg0, s16 *, 0x32) = (s16) (M2C_FIELD(arg0, u16 *, 0x66) + ((s32) (func_80083E80((s16) M2C_FIELD(arg0, u16 *, 0x4E)) << 5) >> 0xC));
        break;
    }
}

void func_801391A4(void *arg0) {
    func_8003116C(0x50C, arg0 + 0x2C, -0x32);
    M2C_FIELD(arg0, s8 *, 4) = 3;
    func_80040B48(0x6C);
}

void func_80121A58();
void func_801391E4(u8 *a)
{
    u8 *st;
    u8 *e;
    u8 *g;

    switch (a[4]) {
    case 0:
        st = (u8 *)&D_800BF870;
        if ((*(u16 *)(st + 0x5E6) >> st[0]) & 1) {
            a[4] = 3;
            break;
        }
        if (func_80051B70(a, 0xC, D_80141AB7) != 0) {
            break;
        }
        *(s16 *)(a + 0x80) = 0x6E;
        *(s16 *)(a + 0x82) = 0xDC;
        *(s16 *)(a + 0x84) = 0x50;
        a[0] = 1;
        *(s16 *)(a + 0x86) = 0x80;
        a[0x29] = 0;
        a[0x2B] = 0;
        *(s16 *)(a + 0x54) = 0;
        *(s16 *)(a + 0x56) = 0;
        *(s16 *)(a + 0x58) = 0;
        a[4]++;
        func_800517F8(a);
        break;
    case 1:
        func_8007778C(a);
        break;
    case 2:
        func_8007778C(a);
        if (a[6] != 0) {
            break;
        }
        g = (u8 *)&D_800BF870;
        g[0x144] |= 2;
        a[4] = 3;
        func_8003116C(0x504, a + 0x2C, -0x32);
        func_8003116C(0x503, a + 0x2C, -0x32);
        e = (u8 *)func_80072DDC(0, 0, 4, 0x37);
        if (e != NULL) {
            *(void **)(e + 0x1C) = func_80121A58;
            *(s16 *)(e + 0x2E) = *(s16 *)(a + 0x2E);
            *(s16 *)(e + 0x32) = *(s16 *)(a + 0x32);
            *(s16 *)(e + 0x36) = *(s16 *)(a + 0x36);
        }
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

void func_80121A58();
void func_8013939C(u8 *a)
{
    u8 *p;
    u8 *g;

    if (a[6] == 0) {
        g = (u8 *)&D_800BF870;
        g[0x144] |= 2;
        a[4] = 3;
        func_8003116C(0x504, a + 0x2C, -0x32);
        func_8003116C(0x503, a + 0x2C, -0x32);
        p = func_80072DDC(0, 0, 4, 0x37);
        if (p != NULL) {
            *(void **)(p + 0x1C) = func_80121A58;
            *(s16 *)(p + 0x2E) = *(s16 *)(a + 0x2E);
            *(s16 *)(p + 0x32) = *(s16 *)(a + 0x32);
            *(s16 *)(p + 0x36) = *(s16 *)(a + 0x36);
        }
    }
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8013945C);

extern u8 D_8013FE34[];
extern u8 D_8013FDBC[];
void func_80139614(u8 *a)
{
    u8 *g;
    u8 *st;
    u8 *tbl;

    switch (a[4]) {
    case 0:
        st = (u8 *)&D_800BF870;
        if (!((*(u16 *)(st + 0x5E6) >> st[0]) & 1)) {
            tbl = D_8013FDBC;
        } else {
            tbl = D_8013FE34;
        }
        g = D_800ECF58;
        if (func_800519E0(a, 0xF, *(s32 *)(g + 0x7C), tbl) != 0) {
            break;
        }
        *(s32 *)(a + 0x3C) = *(s32 *)(g + 0x38);
        func_80040CDC(a, D_80144404, D_800A3D18);
        a[0] = 9;
        *(s16 *)(a + 0x80) = 0x55;
        *(s16 *)(a + 0x82) = 0xAA;
        *(s16 *)(a + 0x84) = 0x90;
        a[0xB] = 0;
        *(s16 *)(a + 0x86) = 0x130;
        a[0x2B] = 0;
        a[0x29] = 0;
        *(s16 *)(a + 0x58) = 0;
        *(s16 *)(a + 0x56) = 0;
        *(s16 *)(a + 0x54) = 0;
        if (a[3] == 0) {
            *(s32 *)(a + 0x2C) = 0x09AE0000;
            *(s32 *)(a + 0x30) = 0xD3BF0000;
            *(s32 *)(a + 0x34) = 0x33E20000;
            a[0x7B] = 0;
            a[0x2A] = 0x19;
            *(s16 *)(a + 0x56) = 0;
        }
        func_80041718(a, a[0x7B], 0);
        a[4]++;
        break;
    case 1:
        if (a[3] == 0) {
            func_8013945C(a);
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

void func_801397C0(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 4);
    switch (temp_v1) {                              /* irregular */
    case 0:
        if (func_80051B70(arg0, 0xC, 0x2D) == 0) {
            M2C_FIELD(arg0, s16 *, 0x2E) = 0x1000;
            M2C_FIELD(arg0, s16 *, 0x32) = -0x2454;
            M2C_FIELD(arg0, s16 *, 0x36) = 0x26CD;
            M2C_FIELD(arg0, s16 *, 0x80) = 0x3E;
            M2C_FIELD(arg0, s16 *, 0x82) = 0x77;
            M2C_FIELD(arg0, s16 *, 0x84) = 0x64;
            M2C_FIELD(arg0, s16 *, 0x54) = 0;
            M2C_FIELD(arg0, s16 *, 0x58) = 0;
            M2C_FIELD(arg0, s8 *, 0) = 1;
            M2C_FIELD(arg0, s16 *, 0x86) = 0xC8;
            M2C_FIELD(arg0, u8 *, 4) = (u8) (M2C_FIELD(arg0, u8 *, 4) + 1);
            func_80041194(arg0, 0, 1, 0);
            M2C_FIELD(M2C_FIELD(arg0, void **, 0xC0), s16 *, 0xA) = (s16) -(s16) M2C_FIELD(arg0, u16 *, 0x56);
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

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_801398DC);

void func_801398DC();
s32 func_80139CBC(u8 *a) {
    u8 *g = (u8 *)&D_800BF870;
    u8 *e;

    if (g[0xC6] & 0x8) {
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
    M2C_FIELD(e, void **, 0x1C) = func_801398DC;
    M2C_FIELD(e, s16 *, 0x2E) = M2C_FIELD(a, s16 *, 0x2E);
    M2C_FIELD(e, s16 *, 0x32) = M2C_FIELD(a, s16 *, 0x32);
    M2C_FIELD(e, s16 *, 0x36) = M2C_FIELD(a, s16 *, 0x36);
    e[0x2A] = a[0x2A];
    g[0x164] = 1;
    func_8003116C(0x30, e + 0x2C, -0xA);
    func_80074590(0x37, 0x20, 0);
    return 1;
}

extern u8 D_8013FEAC[];
extern u8 D_80146098[];
extern u8 D_800A3D70[];
void func_8013A0D8(u8 *a);
void func_80139D8C(u8 *a)
{
    u8 *g;
    u8 *st;
    u8 c;

    switch (a[4]) {
    case 0:
        g = D_800ECF58;
        if (func_800519E0(a, 0xA, *(s32 *)(g + 0xA4), D_8013FEAC) != 0) {
            break;
        }
        *(s32 *)(a + 0x3C) = *(s32 *)(g + 0xA8);
        func_80040CDC(a, D_80146098, D_800A3D70);
        st = (u8 *)&D_800BF870;
        *(s16 *)(a + 0x54) = 0;
        *(s16 *)(a + 0x56) = 0;
        *(s16 *)(a + 0x58) = 0;
        c = st[0xC9];
        if (c == 0xFF) {
            a[0x5E] = 5;
            func_80041718(a, 0, 0);
            *(s16 *)(a + 0x56) = 0xC00;
        } else if (c & 0x80) {
            if (st[0x2D9] != 0) {
                a[0x5E] = 4;
                func_80041718(a, 0, 0);
            } else if (st[0x2D8] != 0) {
                if (c & 0x40) {
                    a[0x5E] = 3;
                    func_80041718(a, 0, 0);
                } else {
                    a[0x5E] = 2;
                    func_80041718(a, 1, 0);
                }
            } else {
                a[0x5E] = 1;
                func_80041718(a, 1, 0);
            }
        } else {
            a[0x5E] = 0;
            func_80041718(a, 1, 0);
            *(s16 *)(a + 0x56) = 0x800;
        }
        a[0xB] = 0x40;
        a[0] = 9;
        *(s16 *)(a + 0x80) = 0x78;
        *(s16 *)(a + 0x82) = 0xF0;
        *(s16 *)(a + 0x84) = 0x7A;
        *(s16 *)(a + 0x86) = 0xF4;
        a[0x2B] = 0;
        a[4]++;
        break;
    case 1:
        a[1] = 1;
        func_80077E7C(a);
        func_80041098(a);
        func_8004190C(a);
        switch (a[5]) {
        case 0:
            func_80139FF0(a);
            break;
        case 1:
            func_8013A0D8(a);
            break;
        case 2:
            func_8013A138(a);
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

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80139FF0);

extern void *D_80142454[];
void func_8013A0D8(u8 *a)
{
    if (a[0x71] == 0xFF) {
        func_80040D68(a, D_80142454[a[0x5E]]);
        a[5] = 2;
        a[6] = 0;
        a[0x70] = 1;
    }
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8013A138);

s32 func_8013A218(void *arg0) {
    M2C_FIELD(arg0, u8 *, 6) = (u8) (M2C_FIELD(arg0, u8 *, 6) + 1);
    return 1;
}

s32 func_8013A230(u8 *a) {
    u8 *g = (u8 *)&D_800BF870;

    if (g[0x2D8] != 0) {
        a[0x5E] = 2;
        g[0x1E1] = 2;
        return 3;
    }
    return 2;
}

s32 func_8013A260(u8 *a) {
    u8 *g = (u8 *)&D_800BF870;

    if (g[0x2D9] != 0) {
        a[0x5E] = 4;
        g[0x1E1] = 2;
        return 3;
    }
    return 2;
}

extern u8 D_8013FEFC[];
extern u8 D_801461BC[];
extern u8 D_800BFA51;
void func_8013A7F8(u8 *a);
void func_8013A294(u8 *a)
{
    u8 *g;
    u8 *st;
    u8 c;

    switch (a[4]) {
    case 0:
        g = D_800ECF58;
        if (func_800519E0(a, 8, *(s32 *)(g + 0xAC), D_8013FEFC) != 0) {
            break;
        }
        *(s32 *)(a + 0x3C) = *(s32 *)(g + 0xB0);
        func_80040CDC(a, D_801461BC, D_800A3D70);
        st = (u8 *)&D_800BF870;
        *(s16 *)(a + 0x54) = 0;
        *(s16 *)(a + 0x56) = 0;
        *(s16 *)(a + 0x58) = 0;
        c = st[0xC9];
        if (c == 0xFF) {
            a[0x5E] = 5;
            func_80041718(a, 0, 0);
            *(s16 *)(a + 0x56) = 0x400;
            func_8011C364(a, 2);
        } else if (c & 0x80) {
            if (st[0x2D9] != 0) {
                a[0x5E] = 4;
                func_80041718(a, 0, 0);
            } else if (st[0x2D8] != 0) {
                if (c & 0x40) {
                    a[0x5E] = 3;
                    func_80041718(a, 0, 0);
                } else {
                    a[0x5E] = 2;
                    func_80041718(a, 1, 0);
                }
            } else {
                a[0x5E] = 1;
                func_80041718(a, 1, 0);
            }
        } else {
            a[0x5E] = 0;
            func_80041718(a, 1, 0);
            *(s16 *)(a + 0x56) = 0x800;
        }
        a[0xB] = 0x40;
        a[0] = 9;
        *(s16 *)(a + 0x80) = 0x78;
        *(s16 *)(a + 0x82) = 0xF0;
        *(s16 *)(a + 0x84) = 0x7A;
        *(s16 *)(a + 0x86) = 0xC2;
        a[0x2B] = 0;
        a[4]++;
        D_800BFA51 = 0;
        *(s32 *)(a + 0x14) = 0;
        break;
    case 1:
        a[1] = 1;
        func_80077E7C(a);
        func_80041098(a);
        func_8004190C(a);
        switch (a[5]) {
        case 0:
            func_8013A518(a);
            break;
        case 1:
            func_8013A7F8(a);
            break;
        case 2:
            func_8013A6B8(a);
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

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8013A518);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8013A6B8);

extern void *D_801426C0[];
void func_8013A7F8(u8 *a)
{
    if (a[0x71] == 0xFF) {
        func_80040D68(a, D_801426C0[a[0x5E]]);
        a[5] = 2;
        a[6] = 0;
        a[0x70] = 1;
    }
}

s32 func_8013A858(void *arg0) {
    M2C_FIELD(arg0, u8 *, 6) = (u8) (M2C_FIELD(arg0, u8 *, 6) + 1);
    return 1;
}

s32 func_8013A870(u8 *a) {
    u8 *g = (u8 *)&D_800BF870;

    if (g[0x2D8] != 0) {
        a[0x5E] = 2;
        g[0xC9] |= 0x80;
        return 3;
    }
    return 2;
}

extern u8 D_800BFB49;
s32 func_8013A8A8(u8 *a)
{
    if (D_800BFB49 != 0) {
        a[0x5E] = 4;
        return 3;
    }
    return 2;
}

s32 func_8013A8D0(void *arg0) {
    return M2C_FIELD(arg0, u8 *, 0x79) == 1;
}

void func_8013A8E4(u8 *a)
{
    u8 *g;

    switch (a[4]) {
    case 0:
        if (func_80051B70(a, 0xC, 0x36) != 0) {
            break;
        }
        a[0xB] = 0xF;
        *(s16 *)(a + 0x80) = 0x32;
        *(s16 *)(a + 0x82) = 0x64;
        *(s16 *)(a + 0x84) = 0x78;
        *(s16 *)(a + 0x86) = 0x78;
        a[0x2A] = 4;
        a[0] = 1;
        a[0x29] = 0;
        *(s16 *)(a + 0x58) = 0;
        *(s16 *)(a + 0x54) = 0;
        *(s16 *)(a + 0x56) = 0xA00;
        func_800517F8(a);
        a[4]++;
        break;
    case 1:
        if (func_8007778C(a)) {
            func_800517F8(a);
        }
        func_8004766C(a);
        if (a[5] == 0) {
            *(s16 *)(a + 0x32) += 0xA;
            if (func_80049250(a, 0, 0x32)) {
                a[5]++;
            }
        }
        break;
    case 2:
        a[1] = 1;
        func_80077E7C(a);
        func_800517F8(a);
        switch (a[5]) {
        case 0:
        case 1:
            break;
        case 2:
        case 3:
            func_8004D4C4(0x9D, 1);
            func_8004B0D8(a);
            g = (u8 *)&D_800BF870;
            g[0x158]++;
            a[4] = 3;
            break;
        }
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

s32 func_8013AA98(u8 *a) {
    u8 *p = func_80072DDC(a, 1, 2, 207);

    if (p == NULL) {
        return 0;
    }
    M2C_FIELD(p, void **, 0x1C) = func_8013A8E4;
    M2C_FIELD(p, s16 *, 0x2E) = M2C_FIELD(a, u16 *, 0x2E);
    M2C_FIELD(p, s16 *, 0x32) = (M2C_FIELD(a, u16 *, 0x32) + -50);
    M2C_FIELD(p, s16 *, 0x36) = M2C_FIELD(a, u16 *, 0x36);
    return 1;
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8013AB0C);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8013AD90);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8013B118);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8013B7A0);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8013B94C);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8013BB98);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8013BCD0);

void func_8013C050(u8 *a)
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

void func_8013C18C(u8 *a)
{
    s16 *q = (s16 *)(a + 0x50);

    switch (a[4]) {
    case 0:
        a[0x29] = 0;
        *(s32 *)(a + 0x48) = 0;
        *(s32 *)(a + 0x4C) = 0;
        a[4] = 1;
        a[5] = 0;
        a[6] = 0;
        break;
    case 1:
        *(s16 *)(a + 0x4A) += 0x199;
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
            q[2] += 9;
            if (q[2] >= 0x180) {
                a[5] = 2;
            }
            break;
        case 2:
            if (*(s16 *)(a + 0x50) < 0x1000) {
                *(s16 *)(a + 0x50) += 0x199;
            } else {
                a[4] = 2;
            }
            q[2] += 9;
            break;
        }
        q[1] = (q[1] + 2) & 0x1F;
        func_8002B278(a);
        break;
    case 2:
    case 3:
        func_8007A624(a);
        break;
    }
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8013C2EC);

extern u8 D_800A0B38[];
extern u8 D_80143BDC[];
extern u8 D_80143C10[];
void func_8013C7C8(u8 *a)
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
        *(u8 **)(a + 0x3C) = D_80143BDC + s[4] * 4;
        a[0x29] = D_80143C10[s[4]];
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

s32 func_8013C968(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    void *temp_v0;

    temp_v0 = func_800310F4(0x507, -0x32);
    if (temp_v0 != NULL) {
        M2C_FIELD(temp_v0, s8 *, 3) = (s8) arg0;
        M2C_FIELD(temp_v0, s16 *, 0x2C) = (s16) arg1;
        M2C_FIELD(temp_v0, s16 *, 0x2E) = (s16) arg2;
        M2C_FIELD(temp_v0, s16 *, 0x30) = (s16) arg3;
    }
    return (s32) temp_v0;
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8013C9D0);

#define gte_ldfcdir(r0, r1, r2) __asm__ volatile("ctc2	%0, $21;" "ctc2	%1, $22;" "ctc2	%2, $23" : : "r"(r0), "r"(r1), "r"(r2))
extern s32 D_1F800090_81f3[];
typedef struct { s8 x, y, z; } Byte3;
extern Byte3 D_8010A4CC;
extern Byte3 D_8010A4D0;
extern u8 D_80143660[];
extern u8 D_80143930[];
void func_8013CB08(u8 *p)
{
    s32 *d = D_1F800090_81f3;
    s32 i;

    gte_ldfcdir(0, 0, 0);
    *d = *(s16 *)(p + 0x54);
    for (i = 0; i < 8; i++) {
        func_80031D24(p + 0x2C, p + 0x50, p + 0x48);
        func_80027768(*(s32 *)(p + 0x3C), *(u16 *)(p + 0x44), *(s16 *)(p + 0x32), p[0x29]);
        *(s16 *)(p + 0x4E) += 0x200;
    }
}

#define gte_ldfcdir(r0, r1, r2) __asm__ volatile("ctc2	%0, $21;" "ctc2	%1, $22;" "ctc2	%2, $23" : : "r"(r0), "r"(r1), "r"(r2))
void func_8013CB9C(u8 *p)
{
    s32 *d = D_1F800090_81f3;

    gte_ldfcdir(0, 0, 0);
    *d = *(s16 *)(p + 0x54);
    func_80031D24(p + 0x2C, p + 0x50, p + 0x48);
    func_80027768(*(s32 *)(p + 0x3C), *(u16 *)(p + 0x44), *(s16 *)(p + 0x32), p[0x29]);
}

extern M2C_UNK D_80032918;
void func_8013CC08(void *arg0) {
    M2C_FIELD(arg0, s8 *, 4) = 1;
    M2C_FIELD(arg0, s8 *, 6) = 9;
    M2C_FIELD(arg0, M2C_UNK **, 0x1C) = &D_80032918;
}

#define AREA_gte_ldv0(r0) __asm__ volatile("lwc2	$0, 0( %0 );" "lwc2	$1, 4( %0 )" : : "r"(r0))
extern u8 D_8014296C[];
extern s32 D_80142968;
extern s32 D_1F800084;
extern s32 D_1F800088;
extern s32 D_1F800090;
void func_8013CC28(u8 *a) {
    AreaSVec v;
    u8 *p;
    s32 r, k;

    p = M2C_FIELD(a, u8 **, 0x78);
    if (p == NULL) {
        p = D_8014296C;
    }
    func_800329E0(6);
    v.x = M2C_FIELD(a, s16 *, 0x2E);
    v.y = M2C_FIELD(a, s16 *, 0x32);
    v.z = M2C_FIELD(a, s16 *, 0x36);
    AREA_gte_ldv0(&v);
    if (func_800317CC(-10) == 0) {
        D_1F800088 = D_1F800084;
        r = func_8009A450();
        k = D_80142968;
        r &= 0x7FF;
        D_1F800090 = r;
        M2C_FIELD(a, u8 **, 0x78) = func_80027A4C(p, k);
    }
}

void func_8013CCDC(u8 *a)
{
    s32 *d = D_1F800090_81f3;
    u8 *s = a + 0x50;
    Byte3 c;

    c = D_8010A4CC;
    gte_ldfcdir(0, 0, 0);
    {
        s32 v = *(s16 *)(a + 0x50);
        u8 y = *(u16 *)(s + 4) >> 3;

        *d = v;
        c.y = y;
    }
    func_80031D24(a + 0x2C, &c, a + 0x48);
    func_80027768(D_80143660, 0, -0x1E, *(s16 *)(s + 2));
}

void func_8013CD78(u8 *a)
{
    s32 *d = D_1F800090_81f3;
    u8 *s = a + 0x50;
    Byte3 c;

    c = D_8010A4D0;
    gte_ldfcdir(0, 0, 0);
    {
        s32 v = *(s16 *)(a + 0x50);
        u8 y = *(u16 *)(s + 4) >> 3;

        *d = v;
        c.y = y;
    }
    func_80031D24(a + 0x2C, &c, a + 0x48);
    func_80027768(D_80143930, 0, -0x1E, *(s16 *)(s + 2));
}

void func_8013CE14(u8 *a) {
    switch (a[4]) {
    case 0:
        a[4] = 1;
        M2C_FIELD(a, s32 *, 0x50) = 0;
        M2C_FIELD(a, s16 *, 0x4E) = 0;
        M2C_FIELD(a, s16 *, 0x32) = -50;
    case 1:
        if (D_1F80017C_0fe7 & 1) {
            if (++M2C_FIELD(a, s16 *, 0x4E) == 25) {
                D_800BF917 = 2;
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

extern u8 D_800A1CD4[];
extern u8 D_801435D0[];
void func_8013CF00(u8 *p)
{
    s32 *d = D_1F800090_81f3;

    gte_ldfcdir(0, 0, 0);
    *d = *(s32 *)(p + 0x50);
    func_800318A0(p + 0x2C, D_800A1CD4, p + 0x48);
    func_80027768(D_801435D0, *(s16 *)(p + 0x4E), *(s16 *)(p + 0x32), 0);
}

extern RingVec D_801442E0[];
void func_8013CF70(void) {
    s32 i;
    s32 ang;
    RingVec *p;

    p = D_801442E0;
    for (i = 0; i < 15; i++, p++) {
        ang = (i << 12) / 15;
        p->x = func_80083F50(ang) >> 4;
        p->y = 0;
        p->z = func_80083E80(ang) >> 4;
    }
    p->x = D_801442E0[0].x;
    p->y = D_801442E0[0].y;
    p->z = D_801442E0[0].z;
}

void func_8013D040(u8 *a) {
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

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8013D0F8);

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
extern s32 D_80143D2C;
extern s32 D_80143D30;
#define T2_lddp(r0) __asm__ volatile("mtc2 %0, $8" : : "r"(r0))
#define T2_ldrgb(r0) __asm__ volatile("mtc2 %0, $6" : : "r"(r0))
#define T2_dpcs() __asm__ volatile("nop; nop; .word 0x4A780010")
#define T2_strgb(r0) __asm__ volatile("swc2 $22, 0( %0 )" : : "r"(r0) : "memory")
static inline void FogVertex(u32 *col, s32 z)
{
    u32 rgb = *col;
    s32 k = z - D_80143D2C;

    if (k < 0) {
        k = 0;
    } else {
        k = (k << 12) / (D_80143D30 - D_80143D2C);
        if (k > 0x1000) {
            k = 0x1000;
        } else if (k < 0) {
            k = 0;
        }
    }
    T2_lddp(k);
    T2_ldrgb(rgb);
    T2_dpcs();
    T2_strgb(col);
}
u32 *func_8013D568(u32 *f, u32 *ot, s32 n)
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
        p->rgb1 = (c << 4) & 0xFFF0F0F0;
        c = f[1];
        T2_stflg(flg);
        if (*flg >= 0) {
            T2_nclip();
            p->uv0 = f[2];
            T2_stopz(flg);
            if (*flg > 0) {
                T2_stsxy3_gt4(p);
                T2_ldv1p(f);
                p->rgb2 = c & 0xFFF0F0F0;
                T2_rtps();
                p->rgb3 = (c << 4) & 0xFFF0F0F0;
                p->uv1 = f[3];
                T2_stflg(flg);
                if (*flg >= 0) {
                    T2_stsxy(&p->x3);
                    if ((p->x0 < 320 || p->x1 < 320 || p->x2 < 320 || p->x3 < 320) &&
                        (p->y0 < 240 || p->y1 < 240 || p->y2 < 240 || p->y3 < 240)) {
                        p->uv1 = f[3];
                        T2_stsz0(&sz[0]);
                        T2_stsz1(&sz[1]);
                        T2_stsz2(&sz[2]);
                        T2_stsz3(&sz[3]);
                        mode = (c >> 24) & 3;
                        switch (mode) {
                        case 1:
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
                            do {
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
                        e = *otz >> 10;
                        *otz = (*otz >> e) + (e << 9);
                        if ((u32)(*otz - 4) >= 0x7FC) {
                            *otz = -1;
                        }
                        if (*otz >= 0) {
                            FogVertex(&p->rgb0, sz[0]);
                            FogVertex(&p->rgb1, sz[1]);
                            FogVertex(&p->rgb2, sz[2]);
                            FogVertex(&p->rgb3, sz[3]);
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

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8013DAFC);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8013DBC0);

typedef struct { s16 x, y, z, pad; } SVecDD58;
extern SVecDD58 D_1F8000C0;
extern u8 D_1F800000[];
void func_8013DD58(u8 *a)
{
    s32 i;
    u8 *o;

    for (i = 0; i < a[8]; i++) {
        o = ((u8 **)(a + 0xC0))[i];
        D_1F8000C0.x = *(s16 *)(o + 0x2C);
        D_1F8000C0.y = *(s16 *)(o + 0x30);
        D_1F8000C0.z = *(s16 *)(o + 0x34);
        func_80084110(&D_1F8000D0[0x28], o + 0x18, D_1F800000);
        func_80084220(&D_1F8000C0, D_1F800000 + 0x14);
        { u8 *d = D_1F8000D0;
        *(s32 *)(D_1F800000 + 0x14) += *(s32 *)(d + 0x3C);
        *(s32 *)(D_1F800000 + 0x18) += *(s32 *)(d + 0x40);
        *(s32 *)(D_1F800000 + 0x1C) += *(s32 *)(d + 0x44); }
        func_80084660(D_1F800000);
        func_80084690(D_1F800000);
        func_8013DBC0(a, o);
    }
}

void func_8013DE84(void *arg0) {
    M2C_FIELD(arg0, s16 *, 0x60) = 0xD;
    M2C_FIELD(arg0, s16 *, 0x62) = 0x38F7;
    M2C_FIELD(arg0, s16 *, 0x64) = -0x6F40;
    M2C_FIELD(arg0, s16 *, 0x66) = -0x6F39;
    M2C_FIELD(arg0, s16 *, 0x68) = -0x6040;
    M2C_FIELD(arg0, s16 *, 0x6A) = -0x6039;
    M2C_FIELD(arg0, s16 *, 0x6C) = 0x28;
    M2C_FIELD(arg0, s16 *, 0x6E) = 0x78;
    M2C_FIELD(arg0, s16 *, 0x70) = 0;
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8013DECC);

void func_8013DFE4(u8 *a)
{
    u8 *p;

    switch (a[4]) {
    case 0:
        if (func_80051B70(a, 0xC, 0x21) != 0) {
            break;
        }
        *(s16 *)(a + 0x80) = 0x38;
        *(s16 *)(a + 0x82) = 0x70;
        *(s16 *)(a + 0x84) = 0x8C;
        a[0] = 1;
        a[0x29] = 0;
        *(s16 *)(a + 0x86) = 0xF0;
        a[4] = 1;
        a[5] = 0;
    case 1:
        if (D_1F800137_104c != 0) {
            break;
        }
        if (a[3] == 1) {
            func_8013DECC(a);
        } else {
            switch (a[5]) {
            case 0:
                *(s16 *)(a + 0x40) = 0x1E;
                *(s16 *)(a + 0x54) = 0x400;
                *(s16 *)(a + 0x56) = 0;
                *(s16 *)(a + 0x58) = 0;
                a[5] = 1;
            case 1:
                if (!((*(s16 *)(a + 0x40))-- > 0)) {
                    a[0] = 2;
                    a[4] = 2;
                } else {
                    *(s32 *)(a + 0x2C) += *(s16 *)(a + 0x4E) << 8;
                    *(s32 *)(a + 0x30) += *(s16 *)(a + 0x50) << 8;
                    *(s32 *)(a + 0x34) += *(s16 *)(a + 0x52) << 8;
                }
                break;
            }
        }
        func_8004766C(a);
        if (func_800495DC(a, *(s16 *)(a + 0x80), 0)) {
            a[0] = 2;
            a[4] = 2;
            break;
        }
        if (func_80116B48(a)) {
            func_800517F8(a);
        }
        break;
    case 2:
        func_8003116C(0x503, a + 0x2C, -0x1E);
    case 3:
        p = *(u8 **)(a + 0x10);
        if (p != NULL) {
            *(s32 *)(p + 0x14) = 0;
        }
        func_8007A624(a);
        break;
    }
}

void func_8013E1DC(void *arg0) {
    u16 temp_v0;
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 5);
    switch (temp_v1) {                              /* irregular */
    case 0:
        M2C_FIELD(arg0, u16 *, 0x40) = 0x1EU;
        M2C_FIELD(arg0, s16 *, 0x54) = 0x400;
        M2C_FIELD(arg0, s16 *, 0x56) = 0;
        M2C_FIELD(arg0, s16 *, 0x58) = 0;
        M2C_FIELD(arg0, u8 *, 5) = 1U;
        /* fallthrough */
    case 1:
        temp_v0 = M2C_FIELD(arg0, u16 *, 0x40);
        M2C_FIELD(arg0, u16 *, 0x40) = (u16) (temp_v0 - 1);
        if ((temp_v0 << 0x10) <= 0) {
            M2C_FIELD(arg0, s8 *, 0) = 2;
            M2C_FIELD(arg0, s8 *, 4) = 2;
            return;
        }
        M2C_FIELD(arg0, s32 *, 0x2C) = (s32) (M2C_FIELD(arg0, s32 *, 0x2C) + (M2C_FIELD(arg0, s16 *, 0x4E) << 8));
        M2C_FIELD(arg0, s32 *, 0x30) = (s32) (M2C_FIELD(arg0, s32 *, 0x30) + (M2C_FIELD(arg0, s16 *, 0x50) << 8));
        M2C_FIELD(arg0, s32 *, 0x34) = (s32) (M2C_FIELD(arg0, s32 *, 0x34) + (M2C_FIELD(arg0, s16 *, 0x52) << 8));
        return;
    }
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", f_SpawnSnowFireflyAuxiliaryActor);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8013E3D4);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8013E510);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8013E64C);

extern s32 D_800BF858;
extern u8 D_1F80017C_26d2;
void f_UpdateCapturedSnowFireflyMotion(u8 *a)
{
    switch (a[5]) {

    case 0:
        a[5]++;
        {
            u8 r = D_1F80017C_26d2;
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
        D_800BF858 = 0;
    }
}

void func_8013CC28();
/* func_8013ECF8, inlined */
static inline void func_8013ECF8_inl(void *arg0) {
    u16 temp_v0;
    u8 temp_v1;
    void *temp_a2;

    temp_v1 = M2C_FIELD(arg0, u8 *, 5);
    temp_a2 = M2C_FIELD(arg0, void **, 0x10);
    switch (temp_v1) {
    case 0:
        M2C_FIELD(arg0, u16 *, 0x40) = 0x3CU;
        M2C_FIELD(arg0, s16 *, 0x60) = 0;
        M2C_FIELD(arg0, s16 *, 0x62) = -0x20;
        M2C_FIELD(arg0, s16 *, 0x64) = 0;
        M2C_FIELD(arg0, u8 *, 5) = (u8) (M2C_FIELD(arg0, u8 *, 5) + 1);
        /* fallthrough */
    case 1:
        temp_v0 = M2C_FIELD(arg0, u16 *, 0x40) - 1;
        M2C_FIELD(arg0, u16 *, 0x40) = temp_v0;
        if ((temp_v0 << 0x10) == 0) {
            M2C_FIELD(arg0, u8 *, 5) = (u8) (M2C_FIELD(arg0, u8 *, 5) + 1);
        }
        func_8004BD64(arg0, 1, M2C_FIELD(temp_a2, s32 *, 0xDC), 0, arg0 + 0x60);
        return;
    case 2:
        func_8004D4C4(0x75, 1, temp_a2);
        func_80040B48(0x6D);
        M2C_FIELD(arg0, s8 *, 4) = 3;
        return;
    }
}
/* func_8013EDD8, inlined */
static inline void func_8013EDD8_inl(void *arg0) {
    u8 temp_a1;
    u8 temp_v0;

    if (D_800E7FEE != 0) {
        if (M2C_FIELD(arg0, u8 *, 0x5E) == 2) {
            D_800BF858 = 0;
            D_800BF870.pad1[0x19C] += 1;
        } else {
            temp_a1 = M2C_FIELD(arg0, u8 *, 3);
            temp_v0 = D_800BF870.pad1[0x19B] | (1 << temp_a1);
            D_800BF870.pad1[0x19B] = temp_v0;
            if ((temp_v0 & 0x1F) == 0x1F) {
                func_80040C00(0x6C, temp_a1);
            }
        }
        func_80040B48(0x6D);
        func_8004D4C4(0x75, 1);
        M2C_FIELD(arg0, s8 *, 4) = 3;
    }
}
void func_8013E910(u8 *a)
{
    switch (a[4]) {
    case 0:
        a[0xB] = 0x16;
        *(void **)(a + 0x7C) = func_8013CC28;
        a[0xD] = 1;
        a[0] = 1;
        *(s32 *)(a + 0x78) = 0;
        *(s16 *)(a + 0x80) = 0x28;
        *(s16 *)(a + 0x82) = 0x50;
        *(s16 *)(a + 0x84) = 0x28;
        *(s16 *)(a + 0x86) = 0x50;
        a[4]++;
        break;
    case 1:
        func_8007778C(a);
        switch (a[0x5E]) {
        case 0:
            func_8013E510(a);
            break;
        case 1:
            func_8013E64C(a);
            break;
        case 2:
            f_UpdateCapturedSnowFireflyMotion(a);
            break;
        case 3:
            func_8013ECF8_inl(a);
            break;
        }
        break;
    case 2:
        func_8007778C(a);
        switch (a[5]) {
        case 0:
        case 1:
            break;
        case 2:
            a[5] = 3;
            break;
        case 3:
            func_8013EDD8_inl(a);
            break;
        case 4:
        case 5:
        case 6:
            break;
        }
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

extern u8 D_800E7EAA;
void func_8013E910();
u8 *func_8013EBE4(u8 *a, s32 b, s32 c)
{
    u8 *p;
    u8 *g;

    if (b == 2) {
        u8 *s = D_800BF808_1760;
        if (*(s32 *)(s + 0x50) != 0) {
            return NULL;
        }
        g = (u8 *)&D_800BF870;
        if (g[0x19D] + g[0x19E] >= 11) {
            return NULL;
        }
        if (g[0x19D] >= 10) {
            return NULL;
        }
        *(s32 *)(s + 0x50) = 1;
    }
    p = func_80072DDC(0, 0, 2, 0x47);
    if (p != NULL) {
        *(void **)(p + 0x1C) = func_8013E910;
        p[0x5E] = b;
        p[3] = c;
        if (b == 3) {
            *(s32 *)(p + 0x10) = c;
        } else {
            if (b == 1) {
                return p;
            }
            *(s16 *)(p + 0x2E) = *(s16 *)(a + 2);
            *(s16 *)(p + 0x32) = *(s16 *)(a + 6);
            *(s16 *)(p + 0x36) = *(s16 *)(a + 0xA);
            p[0x2A] = D_800E7EAA;
        }
    }
    return p;
}

void func_8013ECF8(void *arg0) {
    u16 temp_v0;
    u8 temp_v1;
    void *temp_a2;

    temp_v1 = M2C_FIELD(arg0, u8 *, 5);
    temp_a2 = M2C_FIELD(arg0, void **, 0x10);
    switch (temp_v1) {                              /* irregular */
    case 0:
        M2C_FIELD(arg0, u16 *, 0x40) = 0x3CU;
        M2C_FIELD(arg0, s16 *, 0x60) = 0;
        M2C_FIELD(arg0, s16 *, 0x62) = -0x20;
        M2C_FIELD(arg0, s16 *, 0x64) = 0;
        M2C_FIELD(arg0, u8 *, 5) = (u8) (M2C_FIELD(arg0, u8 *, 5) + 1);
        /* fallthrough */
    case 1:
        temp_v0 = M2C_FIELD(arg0, u16 *, 0x40) - 1;
        M2C_FIELD(arg0, u16 *, 0x40) = temp_v0;
        if ((temp_v0 << 0x10) == 0) {
            M2C_FIELD(arg0, u8 *, 5) = (u8) (M2C_FIELD(arg0, u8 *, 5) + 1);
        }
        func_8004BD64(arg0, 1, M2C_FIELD(temp_a2, s32 *, 0xDC), 0, arg0 + 0x60);
        return;
    case 2:
        func_8004D4C4(0x75, 1, temp_a2);
        func_80040B48(0x6D);
        M2C_FIELD(arg0, s8 *, 4) = 3;
        return;
    }
}

extern s16 D_800E7FEE;
void func_8013EDD8(void *arg0) {
    u8 temp_a1;
    u8 temp_v0;

    if (D_800E7FEE != 0) {
        if (M2C_FIELD(arg0, u8 *, 0x5E) == 2) {
            D_800BF858 = 0;
            D_800BF870.pad1[0x19C] += 1;
        } else {
            temp_a1 = M2C_FIELD(arg0, u8 *, 3);
            temp_v0 = D_800BF870.pad1[0x19B] | (1 << temp_a1);
            D_800BF870.pad1[0x19B] = temp_v0;
            if ((temp_v0 & 0x1F) == 0x1F) {
                func_80040C00(0x6C, temp_a1);
            }
        }
        func_80040B48(0x6D);
        func_8004D4C4(0x75, 1);
        M2C_FIELD(arg0, s8 *, 4) = 3;
    }
}

extern u8 *D_800ECF84;
extern s16 D_1F8000F0;
extern s16 D_1F8000F2_a096;
void func_8013EE84(u8 *a)
{
    s32 pad;
    u8 *p = D_800ECF84;
    s32 x, y;
    u16 n;

    if (!(D_800BFE56 & 0x10)) {
        return;
    }
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
        y = ((D_1F8000F0 * *(u16 *)(a + 0x2E)) >> 12) + a[0x11] * 8;
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

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8013F0DC);

// ASM by design: hand-written GTE routine (no stack frame, trapping add / addi / sub: never emitted by gcc 2.8.1).
INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8013F418);

// ASM by design: hand-written GTE routine (no stack frame, trapping add / addi / sub: never emitted by gcc 2.8.1).
INCLUDE_ASM("asm/a04/nonmatchings/a04", f_UpdateThirdReadyOrNotKujaraDialogue);

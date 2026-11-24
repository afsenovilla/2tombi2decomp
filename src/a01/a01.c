#include "common.h"
#include "game.h"
#include "m2c.h"
#include "gte.h"

typedef struct {
    u8 pad[0xD0];
    s32 *p0;
    u8 pad2[8];
    s32 *p1;
} PairOwner;

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80109F7C);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8010A0F0);

#define H(p, o) (*(s16 *)((u8 *)(p) + (o)))
extern u8 D_1F800137;
extern u8 D_800BF840;
extern u16 D_800ECF54;
extern s16 D_1F80016C;
extern s16 D_1F80016E;
#define H(p, o) (*(s16 *)((u8 *)(p) + (o)))
void func_8010A32C(u8 *a, u8 *b) {
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
        if (D_1F800137 == 0) {
            func_80062A30(a, b, 3);
        }
    }
}

extern u16 D_1F80017C;
extern u16 D_800BFE56;
s32 func_8010A530(u8 *a, u8 *b, s32 skip) {
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
            func_8010A32C(a, b);
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
            func_8010A32C(a, b);
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
        if ((a[5] == 4 && a[7] >= 2) || a[5] == 9) {
            if (!(D_800BFE56 & 2) && H(a, 0x32) >= -0xB7B) {
                a[5] = 4;
                a[6] = 3;
                a[7] = 0;
                return 1;
            }
        }
        return 0;
    }
    H(a, 0x32) = H(p, 0x30) + H(a, 0x156);
    return 1;
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8010AA20);

s32 func_8010AC3C(u8 *a) {
    u8 *p = M2C_FIELD(a, u8 **, 0x158);
    s32 r;

    if (p[0xC] == 4 && p[2] == 0x16) {
        r = func_8010A0F0(a, p);
        if (M2C_FIELD(a, s16 *, 0x32) >= -0xB7B) {
            M2C_FIELD(a, s16 *, 0x16E) = 0;
            func_800232F4(a);
        }
        return r;
    }
    return 0;
}

s32 func_8010ACB8(s32 arg0, s32 arg1) {
    s32 var_a3;
    void *temp_a1;

    temp_a1 = M2C_FIELD(arg0, void **, 0x158);
    var_a3 = 0;
    if ((M2C_FIELD(temp_a1, u8 *, 0xC) == 4) && (M2C_FIELD(temp_a1, u8 *, 2) == 0x17)) {
        var_a3 = func_8010A530(arg0, (s32) temp_a1, arg1);
    }
    return var_a3;
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8010AD08);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8010AE30);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8010AF6C);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8010B604);

extern s8 D_1F800138[];
extern s8 D_1F80019B[];
void func_8010BAA4(void) {
    func_80045258(M2C_FIELD(*((volatile void **)D_1F800138), u8 *, 0x6E), 0xF);
    *((volatile s8 *)D_1F80019B) = 1;
    func_80051FB4();
}

extern u8 D_800E8008[];
extern u8 D_800E7E80[];
extern u8 D_800BF817;
extern u8 D_800BF816;
extern s32 D_1F800184;
void func_8010BAE4(void) {
    u8 *g = D_800E8008;
    u8 *t = D_800E7E80;

    func_80054198(t);
    t[5] = 0x24;
    if (D_800BF817 == 4) {
        t[6] = 6;
    } else if (D_800BF817 == 5) {
        t[6] = 5;
    } else {
        t[6] = 0;
    }
    t[0x16B] = 0;
    D_800BF816 = 0;
    g[0x64] = 0;
    D_1F800184 = 0;
}

extern s8 D_800BF808[];
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
void func_8010BB74(u8 *a, u8 *b) {
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
void func_8010BCC8(u8 *a, u8 *b) {
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
s32 func_8010BE94(u8 *a, u8 *b) {
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
s32 func_8010C008(u8 *a, u8 *b, u8 *c) {
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

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8010C2EC);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8010C498);

extern u8 D_800BF808_1760[];
extern s16 D_800BF83A;
void func_8010C6EC(u8 *a) {

    switch (a[0x2A]) {
    case 2:
        if (M2C_FIELD(a, s16 *, 0x2E) < 0x23D6) {
            D_800BF83A = 0x111;
        } else {
            D_800BF83A = 0x112;
        }
        break;
    case 6:
    case 7:
        D_800BF83A = 0x11A;
        break;
    case 10:
        if (M2C_FIELD(a, s16 *, 0x2E) < 0x4290) {
            D_800BF83A = 0x114;
        } else {
            D_800BF83A = 0x115;
        }
        break;
    default:
        D_800BF83A = 0x113;
        break;
    case 15:
        D_800BF83A = 0x10F;
        break;
    case 24:
        D_800BF83A = 0x110;
        break;
    }
    D_1F800137 = 2;
    D_800BF808_1760[7] = 2;
    D_800BF808_1760[0x31] = 3;
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8010C7BC);

void func_8010C928(u8 *a) {
    u8 *g = D_800BF808_1760;
    u16 y;

    if (g[0xE] != 0) {
        y = FU16(g, 0xA);
        if (g[0xF] == 2) {
            if (F16(a, 0x36) >= 0x41E7) {
                y += 0x28;
            }
        } else if (g[0xF] == 5 && F16(a, 0x2E) < 0x19DF) {
            F16(a, 0x2E) = 0x19DF;
        }
        if (!(a[0x145] & 1) && F16(a, 0x32) >= (s16)y - F16(a, 0x62)) {
            F16(a, 0x32) = y - FU16(a, 0x62);
            func_80022C78(a);
            a[0x29] |= 0x80;
        }
    } else if (D_1F800137 == 0) {
        func_8010C7BC(a);
    }
    func_8010C2EC(a);
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8010CA24);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8010CF68);

#define FP(p, o) M2C_FIELD(p, u8 **, o)
extern u8 D_800BFAD6;
void func_8010D188(u8 *a, u8 *b) {
    s32 r;
    s32 t;
    s32 u;

    if (!(FU16(a, 0x17E) & 0x200) && a[0] < 4) {
        if (b[3] & 0x80) {
            if (func_8001F830(a, b) != 0) {
                func_80058304(a, 1);
                if (D_800BFAD6 == 0) {
                    a[0x2B] = D_1F80009C >> 4;
                    func_80022D08(a, b, 1, 0);
                }
            }
        } else {
            r = func_8010CF68(a, b, FP(b, 0xCC), 0);
            if (r < 0) {
                if (func_80022F04(a, b) != 0) {
                    a[0x2B] = D_1F80009C >> 4;
                    if (!(a[0] & 4)) {
                        t = (func_80083F50(D_1F80009C) * (F16(a, 0x80) + F16(b, 0x80))) >> 12;
                        u = func_80083E80(D_1F80009C) * (F16(a, 0x80) + F16(b, 0x80));
                        F16(a, 0x2E) = FU16(b, 0x2E) + t;
                        F16(a, 0x36) = FU16(b, 0x36) - (u >> 12);
                    }
                    func_80022D08(a, b, 1, 0);
                }
            } else if (r < 2 && b[0x5E] == 1 && a[0x144] == 1) {
                func_8001FF7C(a, b, r, 2);
            } else {
                a[0x2B] = D_1F80009C >> 4;
                if (!(a[0] & 4)) {
                    t = (func_80083F50(D_1F80009C) * (F16(a, 0x80) + 0x96)) >> 12;
                    u = func_80083E80(D_1F80009C) * (F16(a, 0x80) + 0x96);
                    t += FU16(FP(b, 0xCC), 0x2C) + FU16(b, 0x60);
                    F16(a, 0x2E) = t;
                    {
                        s32 w = u >> 12;
                        F16(a, 0x36) = (FU16(FP(b, 0xCC), 0x34) + FU16(b, 0x64)) - w;
                    }
                }
                func_80022D08(a, b, 1, 0);
            }
        }
    }
}

extern u8 D_80134C08[];
void func_8010D3E0(u8 *a, u8 *b) {
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
        func_8001DC9C(a, b, r, 3);
        D_1F800182_5650 = 0;
        return;
    }
    if (func_8010CF68(a, b, *(u8 **)(b + 0xCC), 1) < 0) {
        if (func_80022F04(a, b) == 0) {
            return;
        }
        r = 1;
    }
    if (r == 0) {
        k = D_80134C08[a[2]];
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

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8010D568);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8010D90C);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8010DBEC);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8010DF24);

void func_8010E0C4(u8 *a, u8 *b) {
    if (*(u16 *)(a + 0x17E) & 0x200) {
        return;
    }
    if (func_80022F04(a, b) == 0) {
        return;
    }
    if (b[3] == 0) {
        func_80058304(a, 1);
        if (D_800BFAD6 == 0) {
            a[0x2B] = D_1F80009C >> 4;
            func_80022D08(a, b, 1, 0);
        }
    } else if (D_800BFAD6 == 0) {
        switch (b[0x5E]) {
        case 0:
        case 1:
            a[0x2B] = *(u16 *)(a + 0x140) >> 4;
            break;
        case 2:
            a[0x2B] = D_1F80009C >> 4;
            break;
        case 3:
        case 4:
            a[0x2B] = (*(s16 *)(a + 0x140) + 0x800) >> 4;
            break;
        }
        func_80022D08(a, b, 1, 0);
    }
}

void func_8010E1E8(u8 *a, u8 *b) {
    s32 r;
    s32 t;
    s32 u;

    r = func_8001F40C(a, b, 0);
    if (r >= 0) {
        if (b[0x5E] != 0) {
            if (!(FU16(a, 0x17E) & 0x200)) {
                if (!(a[0] & 4)) {
                    t = (func_80083F50(D_1F80009C) * (F16(a, 0x80) + F16(b, 0x80))) >> 12;
                    u = func_80083E80(D_1F80009C) * (F16(a, 0x80) + F16(b, 0x80));
                    F16(a, 0x2E) = FU16(b, 0x2E) + t;
                    F16(a, 0x36) = FU16(b, 0x36) - (u >> 12);
                }
                func_80058304(a, 1);
                if (D_800BFAD6 == 0) {
                    a[0x2B] = D_1F80009C >> 4;
                    func_80022D08(a, b, 1, 0);
                }
            }
        } else {
            func_8001FF7C(a, b, r, 2);
            if (b[0] == 2) {
                b[0] = 6;
            }
        }
    }
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8010E338);

extern u16 D_1F80009C_efeb;
extern s16 D_1F80018C;
extern s16 D_1F80018E;
extern u16 D_1F80008C_7310;
typedef struct { u8 pad[0xC0]; u8 *s[8]; } A9628;
#define SLOT9628(i) (*(u8 **)(a + 0xC0 + (i) * 4))
extern u8 D_800E7E80_d97c;
extern u8 D_80137B48[];
extern u8 D_80137B68[];
extern s16 D_1F800160_3621_dd1a;
extern s16 D_1F800162_a8d4;
extern s16 D_1F800164_7d8c_d1dc;
extern u8 D_1F80027A;
void func_8010E4B0(u8 *a, u8 *b)
{
    s16 ang;
    s32 d;
    s32 k;
    s16 t;

    if (func_8002300C(a, b, *(s16 *)(b + 0x80) * 4) != 0) {
        ang = D_1F80009C_efeb + 0x800;
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

void func_8010E6BC(u8 *a, u8 *b)
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
            if (*(s16 *)(a + 0x80) + *(s16 *)(b + 0x80) >= D_1F80008C_7310 && !(a[0] & 4)) {
                s32 x = (func_80083F50(ang) * (*(s16 *)(a + 0x80) + *(s16 *)(b + 0x80))) >> 12;
                s32 z = func_80083E80(ang) * (*(s16 *)(a + 0x80) + *(s16 *)(b + 0x80));
                *(s16 *)(a + 0x2E) = *(s16 *)(b + 0x2E) + x;
                *(s16 *)(a + 0x36) = *(s16 *)(b + 0x36) - (z >> 12);
            }
        }
    }
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8010E8D8);

s32 func_8010ED60(u8 *a, u8 *b) {
    s16 dx = FU16(a, 0x2E) - FU16(b, 0x2E);
    s16 dz = FU16(a, 0x36) - FU16(b, 0x36);
    s32 d = func_80084080(dx * dx + dz * dz);
    u16 ra;
    u16 rb;
    u16 b84;
    u16 a84;
    u16 b86;
    s16 dy;
    s16 h;
    s16 e;
    s16 f;
    s16 s;

    ra = FU16(a, 0x80);
    rb = FU16(b, 0x80);
    if ((u16)d > F16(a, 0x80) + F16(b, 0x80)) {
        return -1;
    }
    b84 = FU16(b, 0x84);
    a84 = FU16(a, 0x84);
    b86 = FU16(b, 0x86);
    dy = FU16(a, 0x32) - FU16(b, 0x32);
    h = (b84 + FU16(a, 0x86)) - a84;
    if ((u16)(dy + h) > F16(a, 0x86) + F16(b, 0x86)) {
        return -1;
    }
    s = ra + rb - d;
    if (dy < 0) {
        dy = -dy;
        e = h;
        f = -h;
    } else {
        f = e = a84 + (b86 - b84);
    }
    if (s < (s16)(e - dy)) {
        return 0;
    }
    if (f <= 0) {
        return 2;
    }
    return 3;
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8010EEA8);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8010EFBC);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8010F240);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8010F40C);

extern u8 **D_1F800148;
extern u8 D_1F800150;
/* func_801103C0, inlined */
static inline void inl_801103C0(u8 *a, u8 *b) {
    if (func_8010C008(a, b, M2C_FIELD(b, u8 **, 0xC0)) == 2 && D_800BF80D == 0 && !(D_800BFE56 & 2) &&
        M2C_FIELD(a, s16 *, 0x32) >= -0x987) {
        M2C_FIELD(a, s16 *, 0x6A) = -0x7900;
    }
}
void func_8010F690(u8 *a) {
    u8 **l = D_1F800148;
    u8 *p;

    D_1F800182_5650 = D_1F800150;
    while (D_1F800182_5650 != 0) {
        p = *l;
        D_1F800182_5650--;
        l++;
        if (p[0] & 1) {
            switch (p[2]) {
            case 0xE:
            case 0xF:
                func_8001FAE0(a, p);
                break;
            case 0xC:
                func_80020868(a, p);
                break;
            case 0x17:
                if (p[0x47] == 2) {
                    func_8010C008(a, p, M2C_FIELD(p, u8 **, 0xC0));
                } else {
                    func_8001F650(a, p, M2C_FIELD(p, u8 **, 0xC0));
                }
                break;
            case 0x18:
                func_80020B08(a, p);
                break;
            case 0x16:
                inl_801103C0(a, p);
                break;
            case 0x13:
                func_8010DBEC(a, p, M2C_FIELD(p, u8 **, 0xC4));
                break;
            case 0x15:
                func_8010CA24(a, p, M2C_FIELD(p, u8 **, 0xC0));
                break;
            case 0x12:
            case 0x19:
            case 0x1A:
            case 0x1D:
            case 0x20:
                func_8002311C(a, p);
                break;
            case 0x1C:
                func_8010BE94(a, p);
                break;
            case 0x1F:
                func_80023764(a, p);
                break;
            case 0x65:
                func_8010BB74(a, p);
                break;
            case 0x32:
            case 0x4B:
                func_8001FC50(a, p);
                break;
            }
        }
    }
}

extern s16 D_1F800144;
extern u8 **D_1F80013C;
extern u8 *D_800F2738;

void func_8010F87C(void) {
    u8 *a;
    u8 **p;
    u8 *b;
    s32 r;
    s32 c;
    s32 k;

    if (D_1F800144 == 0) {
        return;
    }
    for (a = D_800F2738; a != NULL; a = *(u8 **)(a + 0x24)) {
        if ((a[0] & 1) && a[0x2B] == 0) {
            p = D_1F80013C;
            D_1F800182_5650 = *(u8 *)&D_1F800144;
            while (D_1F800182_5650 != 0) {
                b = *p;
                D_1F800182_5650--;
                p++;
                if (b[0] & 1) {
                    switch (b[2]) {
                    case 0:
                        func_80021AB0(a, b, 0);
                        break;
                    case 8:
                        func_80021394(a, b, 0x100);
                        break;
                    case 16:
                        if (func_80022F04(a, b) != 0) {
                            if ((u16)(FU16(a, 0x84) + (FU16(a, 0x32) - FU16(b, 0x32) + 0x78)) <= F16(a, 0x86) + 0x78) {
                                if (func_8001DC9C(a, b, 0, 1) & 0x80) {
                                    a[0x2B] = 2;
                                }
                                D_1F800182_5650 = 0;
                            }
                        }
                        break;
                    case 30:
                        if (b[0x5E] != 0) {
                            break;
                        }
                        if (func_80022F04(a, b) != 0) {
                            if (b[0x5E] == 0) {
                                if (func_8001DC9C(a, b, 0, 2) & 0x80) {
                                    a[0x2B] = 2;
                                }
                            }
                            D_1F800182_5650 = 0;
                        }
                        break;
                    case 25:
                        if (func_80022F04(a, b) != 0) {
{ u16 d; if (F16(b, 0x84) >= 0xB5) { d = FU16(a, 0x84) + (FU16(a, 0x32) - FU16(b, 0x32) + 0xB4); if (d > F16(a, 0x86) + 0xB4) { break; } } else { d = FU16(a, 0x32) - FU16(b, 0x32) + (FU16(a, 0x84) + FU16(b, 0x84)); if (d > F16(a, 0x86) + F16(b, 0x86)) { break; } } }
                            if (b[0xBF] == 0) {
                                r = func_8001DC9C(a, b, 0, 3);
                            } else {
                                r = func_8001E860(a, b, 0, 0);
                            }
                            if (r & 0x80) {
                                a[0x2B] = 2;
                            }
                            D_1F800182_5650 = 0;
                        }
                        break;
                    case 17:
                        func_8010D3E0(a, b);
                        break;
                    }
                }
            }
        }
    }
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8010FB64);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8010FD5C);

extern u8 D_1F800183;
extern u8 **D_1F800154;
extern u8 D_1F80015C;
/* func_80110CB8, inlined */
static inline void inl_80110CB8(void) {
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
                func_8010EFBC(a);
                break;
            }
        }
    }
}
void func_801100A8(void) {
    u8 *g = D_800E7E80;

    func_8002288C(g);
    switch (g[0]) {
    default:
    case 1:
    case 3:
    case 4:
    case 5:
    case 7:
        do {
            func_80022760(g);
        } while (0);
        func_8010F40C(g);
    case 2:
        if (*(u32 *)(g + 0x158) < 2) {
            func_8010F690(g);
        }
    case 0:
    case 6:
        break;
    }
    func_80022554();
    func_8010F87C();
    func_8010FD5C();
    inl_80110CB8();
    func_8010F240();
    func_8010C928(g);
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80110214);

void func_801103C0(u8 *a, u8 *b) {
    if (func_8010C008(a, b, M2C_FIELD(b, u8 **, 0xC0)) == 2 && D_800BF80D == 0 && !(D_800BFE56 & 2) &&
        M2C_FIELD(a, s16 *, 0x32) >= -0x987) {
        M2C_FIELD(a, s16 *, 0x6A) = -0x7900;
    }
}

#define FP(p, o) M2C_FIELD(p, u8 **, o)
extern u8 *D_800E7FD8;
void func_80110430(u8 *a, u8 *b) {
    if (b[0x47] == 2) {
        if (func_80022E04(a, b, FP(b, 0xC0)) != 0) {
            if (a[0x5F] == 0x10) {
                F16(a, 0x32) = FU16(a, 0x84) + (FU16(FP(b, 0xC0), 0x30) + (FU16(b, 0x86) - FU16(b, 0x84)));
            }
            func_8001E860(a, b, FP(b, 0xC0), 0x1200);
            D_1F800182_5650 = 0;
        }
    } else if (a[2] != 0 || b != D_800E7FD8) {
        func_80020F7C(a, b, FP(b, 0xC0), 0x1200);
    }
}

extern u8 *D_1F800080_ddd3;
extern s16 D_1F800166;
extern s16 D_1F800190;
void func_80110504(u8 *a, u8 *b) {
    s32 k = 2;
    u16 t, u;

    if (b[0x47] != k && func_80024BD8(a, b, M2C_FIELD(b, u8 **, 0xC0)) != 0) {
        t = M2C_FIELD(b, u16 *, 0x80);
        b[0x29] = 1;
        u = M2C_FIELD(a, u16 *, 0x80);
        a[0x164] = 1;
        a[0x15C] = 0;
        D_1F800080_ddd3 = b;
        D_1F800182_5650 = 0;
        M2C_FIELD(a, s16 *, 0x152) = t + u - 12;
        if (b[3] >= 11) {
            D_1F800137 = k;
            a[4] = 4;
            D_1F800166 = 0;
            D_1F800190 = 0;
        }
    }
}

void func_801105B8(u8 *a, u8 *b) {
    if (func_80022F04(a, b) != 0) {
        if ((u16)(M2C_FIELD(a, u16 *, 0x84) + (M2C_FIELD(a, u16 *, 0x32) - M2C_FIELD(b, u16 *, 0x32) + 0x78)) <= M2C_FIELD(a, s16 *, 0x86) + 0x78) {
            if (func_8001DC9C(a, b, 0, 1) & 0x80) {
                a[0x2B] = 2;
            }
            D_1F800182_5650 = 0;
        }
    }
}

void func_8011064C(void *a, u8 *b)
{
    if (b[0x47] == 2) {
        func_8010C008(a, b, *(void **)(b + 0xC0));
    } else {
        func_8001F650(a, b, *(void **)(b + 0xC0));
    }
}

void func_80110694(u8 *a, u8 *b) {
    u8 *c = FP(b, 0xC0);
    s16 dx, dz;
    u16 r, cy, ah;
    s32 h, d;

    dx = FU16(a, 0x2E) - FU16(c, 0x2C);
    dz = FU16(a, 0x36) - FU16(c, 0x34);
    r = func_80084080(dx * dx + dz * dz);
    if (F16(a, 0x82) - F16(a, 0x80) + F16(b, 0x80) < r) {
        return;
    }
    d = FU16(a, 0x32) - (cy = FU16(c, 0x30));
    ah = FU16(a, 0x86);
    h = FU16(b, 0x84) + (ah - FU16(a, 0x84));
    if ((u16)(d + h) > (s16)ah + F16(b, 0x86)) {
        return;
    }
    F16(a, 0x32) = cy - h;
    a[0x29] = 1;
}

extern s32 D_1F800084;
extern s32 D_1F80008C;
void func_80110788(u8 *a, u8 *b) {
    u8 v;

    if (b[2] == 0x19) {
        v = b[0xBF];
    } else {
        v = b[0x5E];
    }
    if (v == 0 && func_8002300C(a, b, M2C_FIELD(b, s16 *, 0x80) + 0x190) != 0) {
        if (D_1F80008C < D_1F800084) {
            D_1F800084 = D_1F80008C;
            D_1F800080_ddd3 = b;
        }
    }
}

void func_8011080C(u8 *a) {
    u8 *g = D_800BF808_1760;
    u16 lim = M2C_FIELD(g, u16 *, 0xA);

    if (g[0xF] == 2) {
        if (M2C_FIELD(a, s16 *, 0x36) >= 0x41E7) {
            lim += 0x28;
        }
    } else if (g[0xF] == 5) {
        if (M2C_FIELD(a, s16 *, 0x2E) < 0x19DF) {
            M2C_FIELD(a, s16 *, 0x2E) = 0x19DF;
        }
    }
    if (!(a[0x145] & 1) && M2C_FIELD(a, s16 *, 0x32) >= (s16)lim - M2C_FIELD(a, s16 *, 0x62)) {
        M2C_FIELD(a, s16 *, 0x32) = lim - M2C_FIELD(a, u16 *, 0x62);
        func_80022C78(a);
        a[0x29] |= 0x80;
    }
}

s32 func_801108D4(u8 *a, u8 *b) {
    if (b[0x5E] != 0) {
        return 0;
    }
    if (func_80022F04(a, b) == 0) {
        return 0;
    }
    if (b[0x5E] == 0) {
        if (func_8001DC9C(a, b, 0, 2) & 0x80) {
            a[0x2B] = 2;
        }
    }
    D_1F800182_5650 = 0;
    return 1;
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80110968);

void func_80110A18(u8 *a, u8 *b) {
    u16 t;

    if (b[0xBF] != 0 && func_80024BD8(a, b, M2C_FIELD(b, u8 **, 0xC0)) != 0) {
        M2C_FIELD(a, s16 *, 0x156) = 20;
        t = M2C_FIELD(b, u16 *, 0x80) + M2C_FIELD(a, u16 *, 0x80);
        a[0x164] = 2;
        D_1F800080_ddd3 = b;
        D_1F800182_5650 = 0;
        M2C_FIELD(a, s16 *, 0x152) = t - 0x28;
    }
}

extern s8 D_1F800182[];
extern s16 D_800E7EB2;
void func_80110A94(void *arg0, void *arg1) {
    if ((M2C_FIELD(arg1, s16 *, 0x32) >= (D_800E7EB2 - 0x8C)) && (func_80022F04() != 0)) {
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

void func_80110B2C(u8 *a, u8 *b) {
    s32 r = func_8001F40C(a, b, 1);

    if (r >= 0) {
        if (a[0x164] == 12) {
            func_8001FF7C(a, b, r, 4);
        } else if (b[3] == 3 || b[3] == 4) {
            func_8001FF7C(a, b, r, 2);
        } else {
            func_8001FF7C(a, b, r, 1);
        }
    }
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80110BB8);

typedef struct {
    u8 pad0[0xC0];
    s32 xC0[1];
} S11130C;
typedef struct {
    s16 pad0;
    s16 a;
    s16 pad4;
    s16 b;
    s16 pad8;
    s16 c;
} S13AE38;
typedef struct { u8 pad[0xC0]; u8 *parts[1]; } PartsOwner;
typedef struct { s16 v[4]; } PartInit;
typedef struct { s16 v[5]; } PartInit5;
typedef struct { u8 pad[0x48]; s32 unk48; } AreaState808;
typedef struct { s16 x, y, z; } AreaVec3s;
typedef struct { s16 x, y, z, pad; } AreaSVec;
typedef struct { s16 m[3][3]; s16 pad; s32 t[3]; } AreaMatrix;
typedef struct { u8 pad[0x28]; AreaMatrix m; } AreaScratchD0;
typedef struct { s16 x0; s16 id; u8 k; u8 p5; s16 v6; s16 v8; } Entry10;
typedef struct {
    s16 x, y, w, h;
} RECT16;
typedef struct {
    u8 x[8];
} S8;
typedef struct {
    u8 b[6][4];
} FlickerTbl;
void func_80110CB8(void) {
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
                func_8010EFBC(a);
                break;
            }
        }
    }
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", f_SpawnPipeAreaSceneActorsFromPlacementTable);

extern ClutCycle D_801352CC[];
extern s8 D_80138FD0[];
void func_801112C0(s32 arg0) {
    ClutRect r;
    s32 i;
    ClutCycle *e;
    u8 *data;
    u8 *g = (u8 *)&D_800BF870;

    if (*(u16 *)(g + 0x5E6) & 2) {
        return;
    }

    if (arg0 == 0) {
        s8 *p;
        i = 5;
        p = &D_80138FD0[i];
        do {
            *p-- = 0;
        } while (--i >= 0);
        return;
    }
    if (g[3]) {
        return;
    }
    e = D_801352CC;
    for (i = 0; i < 6; i++, e++) {
        if (--D_80138FD0[i] <= 0) {
            if (e->ptr[0] == 0xFF) {
                e->ptr -= e->ptr[1];
            }
            data = e->clut + e->ptr[0] * 32;
            D_80138FD0[i] = e->ptr[1];
            r.x = e->x;
            r.y = e->y;
            r.w = 16;
            r.h = 1;
            func_80081218(&r, data);
            e->ptr += 2;
        }
    }
}

extern u8 D_800BF873;
extern s32 D_80135314;
void func_80132F5C(void);
/* func_80111C58, inlined */
static inline void inl_80111C58(void) {
    u8 buf[16];

    if (D_800BF873 == 0 && D_800BF816 == 0) {
        if (--D_80135314 < 0) {
            func_8003116C(0x200, buf, 0);
            D_80135314 = (func_8009A450() >> 12) + 1;
        }
    }
}
void f_UpdatePipeAreaSceneController(u8 *a) {
    u8 *g;
    u8 *e;
    u8 *g_f;

    switch (a[4]) {
    case 0:
        a[4] = 1;
        f_SpawnPipeAreaSceneActorsFromPlacementTable(a, 0);
        func_801112C0(0);
        func_80132F5C();
        func_8004D8D8(3, 0);
        g = D_800BF808_1760;
        if (g[0xE] != 0 && g[0xF] == 2) {
            a[3] = g[0xF] + 1;
            f_SpawnPipeAreaSceneActorsFromPlacementTable(a, 3);
            a[5] = 3;
        }
        break;
    case 1:
        if (func_80026AD0(a) != 0) {
            f_SpawnPipeAreaSceneActorsFromPlacementTable(a, a[3]);
        }
        inl_80111C58();
        e = D_800E7E80;
        g_f = D_800BF808_1760;
        if (g_f[0xE] != 0) {
            if (g_f[0xF] == 0) {
                if (M2C_FIELD(e, s16 *, 0x36) >= 0x28E7) {
                    M2C_FIELD(e, s32 *, 0x34) = 0x28E60000;
                    D_1F800164_7d8c_d1dc = M2C_FIELD(e, u16 *, 0x36);
                }
            } else if (g_f[0xF] == 1) {
                if (M2C_FIELD(e, s16 *, 0x36) >= 0x2901) {
                    M2C_FIELD(e, s32 *, 0x34) = 0x29000000;
                    D_1F800164_7d8c_d1dc = M2C_FIELD(e, u16 *, 0x36);
                }
            } else if (g_f[0xF] == 4) {
                if (M2C_FIELD(e, s16 *, 0x36) >= 0x3F0A) {
                    M2C_FIELD(e, s32 *, 0x34) = 0x3F090000;
                    D_1F800164_7d8c_d1dc = M2C_FIELD(e, u16 *, 0x36);
                }
            }
        }
        func_801112C0(1);
        func_80026A68(a);
        break;
    case 2:
        break;
    case 3:
        func_8007ADD0(a);
        break;
    }
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80111620);

typedef struct {
    s16 x, y, w, h;
} RectA;
extern u8 *D_800BF544;
extern void *D_800ED8C8_a098;
void func_80111BE0(void) {
    RectA r;
    u8 *p;

    p = D_800BF544;
    r.x = 0x3F0;
    r.y = 0xE5;
    r.w = 0x10;
    r.h = 1;
    func_80083CE0(p, &r, 0x3F0, 0xEB);
    func_80083C30(D_800ED8C8_a098, p);
    D_800BF544 = (p = p + 0x18);
}

extern u32 *D_800ED8C8;
void func_80111C58(void) {
    u8 buf[16];

    if (D_800BF873 == 0 && D_800BF816 == 0) {
        if (--D_80135314 < 0) {
            func_8003116C(0x200, buf, 0);
            D_80135314 = (func_8009A450() >> 12) + 1;
        }
    }
}

typedef struct {
    s16 lo, hi;
} Range16;
extern Range16 D_80135BA0[];
extern u8 D_1F800207_9c67;
s32 func_80111CCC(s32 x) {
    u8 v;
    s32 k;
    s32 i;

    k = -1;
    v = D_1F800207_9c67;
    for (i = 0; i < 6; i++) {
        if (v >= D_80135BA0[i].lo && v <= D_80135BA0[i].hi) {
            k = i;
            break;
        }
    }
    if (k < 0) {
        return 0;
    }
    if (x >= D_80135BA0[k].lo && x <= D_80135BA0[k].hi) {
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80111D74);

void func_80111ECC(void *arg0) {
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
            func_80111D74(arg0);
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

extern s32 D_800ECF80;
extern u8 D_80139294_2487[];
extern u8 D_800A3D40[];
void func_80111F94(u8 *a)
{
    F16(a, 0x5C) = 0;
    M2C_FIELD(a, s32 *, 0x3C) = D_800ECF80;
    switch (a[3] & 0x7F) {
    case 3:
        func_80077B38(a, D_80139294_2487, 6);
        F16(a, 0x68) = 0x7C;
        a[0xD] = 0;
        break;
    case 4:
        func_80077B38(a, D_80139294_2487, 7);
        F16(a, 0x68) = 0x7D;
        a[0xD] = 0;
        break;
    case 5:
        func_80077B38(a, D_80139294_2487, 8);
        F16(a, 0x68) = 0x7E;
        a[0xD] = 1;
        break;
    }
    a[0xB] = 0x11;
    F16(a, 0x80) = 0x19;
    F16(a, 0x82) = 0x32;
    F16(a, 0x84) = 0x32;
    a[0x47] = 0;
    a[8] = 0;
    F16(a, 0x5A) = 0;
    F16(a, 0x86) = 0x64;
    a[0x2B] = 0;
    if (a[3] & 0x80) {
        a[0] = 2;
        F16(a, 0x60) = F16(a, 0x68);
        func_80040CDC(a, 0, D_800A3D40);
        a[0x70] = 1;
        func_80042354(1, 1);
        a[5] = 1;
    } else {
        a[0] = 1;
    }
    F16(a, 0x7A) = 0x1600;
    F16(a, 0x7C) = 0x1600;
    F16(a, 0x7E) = 0x1600;
}

extern u8 D_800BF871;
extern u8 D_800BF9FF;
typedef struct { s16 a2; s16 a1; u8 w; u8 h; s16 k; } PickupDef;
extern PickupDef D_800A2A74;
void f_UpdatePipeAreaScenePropActor();
void func_80112A8C(u8 *a);
void func_80112BB8(void *arg0);
void f_UpdatePipeAreaQuestPickupActor(u8 *a)
{
    u8 *p;
    PickupDef *t;
    s16 k;
    u8 *q;

    switch (a[4]) {
    case 0:
        a[4] = 1;
        switch (a[3]) {
        case 0:
            if (func_80051B70(a, 0xC, 0x18) != 0) {
                break;
            }
a[0] = 1;
F16(a, 0x80) = 0x14;
F16(a, 0x82) = 0x28;
F16(a, 0x84) = 0x14;
F16(a, 0x86) = 0x28;
FP(a, 0x10) = NULL;
F16(a, 0x56) = 0xC00;
            func_8004B354(a, 1);
            p = func_80072DDC(a, 0x82, 3, 0x10);
            if (p != NULL) {
FP(a, 0x10) = p;
p[3] = 0;
F16(p, 0x2E) = F16(a, 0x2E);
F16(p, 0x32) = F16(a, 0x32);
F16(p, 0x36) = F16(a, 0x36) + 0x64;
M2C_FIELD(p, void **, 0x1C) = f_UpdatePipeAreaScenePropActor;
            }
            break;
        case 1:
            t = &D_800A2A74;
            if (func_80051B70(a, t->a1, D_800A2A74.a2) != 0) {
                break;
            }
            a[0] = 1;
            F16(a, 0x80) = t->w;
            F16(a, 0x82) = t->w * 2;
            F16(a, 0x84) = t->h;
            F16(a, 0x86) = t->h * 2;
            k = t->k;
            F16(a, 0x56) = 0;
            F16(a, 0x54) = 0;
            F16(a, 0x58) = 0xF46;
            FP(a, 0x10) = NULL;
            F16(a, 0x68) = k;
            func_8004B354(a, 1);
            break;
        case 2:
            a[0xB] = 0x11;
            F16(a, 0x7A) = 0x1C00;
            F16(a, 0x7C) = 0x1C00;
            F16(a, 0x7E) = 0x1C00;
            F16(a, 0x5A) = 0;
            a[0x47] = 0;
            F16(a, 0x5C) = 0;
            a[0xD] = 0;
            M2C_FIELD(a, s32 *, 0x3C) = D_800ECF80;
            func_80077B38(a, D_80139294_2487, 4);
            a[0] = 1;
            F16(a, 0x80) = 0x20;
            F16(a, 0x82) = 0x40;
            F16(a, 0x84) = 0x20;
            F16(a, 0x86) = 0x40;
            func_8004B354(a, 0);
            break;
        case 3:
        case 4:
        case 5:
        case 0x83:
        case 0x84:
            func_80111F94(a);
            break;
        case 6:
        case 7:
            a[0xB] = 0x11;
            F16(a, 0x7A) = 0x1C00;
            F16(a, 0x7C) = 0x1C00;
            F16(a, 0x7E) = 0x1C00;
            F16(a, 0x5A) = 0;
            a[0x47] = 0;
            F16(a, 0x5C) = 0;
            a[0xD] = 0;
            M2C_FIELD(a, s32 *, 0x3C) = D_800ECF80;
            func_80077B38(a, D_80139294_2487, 0xC);
            a[0] = 1;
            F16(a, 0x80) = 0x20;
            F16(a, 0x82) = 0x40;
            F16(a, 0x84) = 0x20;
            F16(a, 0x86) = 0x40;
            break;
        case 8:
            if (D_800BF871 != 0x1A) {
                a[4] = 3;
                break;
            }
            a[0xB] = 0x10;
            F16(a, 0x5A) = 0;
            a[0x47] = 0;
            F16(a, 0x5C) = 0;
            a[0xD] = 0;
            M2C_FIELD(a, s32 *, 0x3C) = D_800ECF80;
            func_80077B38(a, D_80139294_2487, 0xE);
            a[0] = 1;
            F16(a, 0x80) = 0x20;
            F16(a, 0x82) = 0x40;
            F16(a, 0x84) = 0x20;
            F16(a, 0x86) = 0x40;
            func_8004B354(a, 0);
            F16(a, 0x68) = 0x92;
            break;
        case 9:
            a[3] = 0xF;
            func_8004A828(a);
            func_8004B354(a, 0);
            a[0xB] = 0x10;
            a[3] = 9;
            a[0] = 1;
            break;
        }
        break;
    case 1:
        switch (a[3]) {
        case 1:
            if (D_800BF816 == 0) {
                a[4] = 3;
                break;
            }
        case 0:
            if (func_8007778C(a) != 0) {
                func_800517F8(a);
                func_8004B374(a, 1);
            }
            break;
        case 2:
            func_8007778C(a);
            func_8004B374(a, 0);
            break;
        case 3:
        case 4:
        case 5:
        case 0x83:
        case 0x84:
            func_8007778C(a);
            func_80077B5C(a);
            switch (a[5]) {
            case 0:
                func_80112A8C(a);
                break;
            case 1:
                func_80112BB8(a);
                break;
            }
            break;
        case 6:
        case 7:
            func_8007778C(a);
            break;
        case 8:
            func_8007778C(a);
            func_8004B374(a, 0);
            break;
        case 9:
            a[1] = 1;
            func_80077EFC(a);
            func_8004B374(a, 0);
            break;
        }
        break;
    case 2:
        switch (a[3]) {
        case 0:
            func_8004D4C4(0x2B, 1);
            func_8004B0D8(a);
            func_80040C00(0x11);
a[4] = 3;
if (FP(a, 0x10) != NULL) {
    FP(a, 0x10)[4] = 3;
}

            D_800BF870.pad1[0x18B] |= 2;
            break;
        case 1:
            func_8004A3D4(a);
            a[4] = 3;
            break;
        case 2:
            func_8004D4C4(0x7F, 1);
            func_8004B0D8(a);
            a[4] = 3;
            break;
        case 3:
        case 4:
        case 5:
            if (F16(a, 0x68) != 0x7E || func_80040C00(0x50) >= 0) {
                func_8004A3D4(a);
                D_800BF9FF = 0;
            }
            a[4]++;
            break;
        case 6:
        case 7:
            if (func_80040C00(0x65) >= 0) {
                func_8004D4C4(0x3E, 1);
                func_8004B0D8(a);
                D_800BF870.pad1[0x17B] += 1 << ((a[3] & 1) * 2);
            }
            a[4] = 3;
            break;
        case 8:
            func_8004A3D4(a);
            D_800BF870.pad1[0x195] |= 0x10;
            a[4] = 3;
            break;
        case 9:
            if (func_8004A118(a) != 0) {
                D_800BF870.pad1[0x195] |= 0x20;
                a[4] = 3;
            }
            break;
        }
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

extern u16 D_1F800160_3621;
s32 func_80112784(void) {
    GameState *g = &D_800BF870;

    if ((g->pad1[0x10] & 4) || (M2C_FIELD(g, u16 *, 0x2E) & 0x200) || g->pad1[2] != 0 || g->pad1[0x18E] != 0) {
        return 0;
    }
    if (D_1F800207_9c67 != 10) {
        return 0;
    }
    return (u16)(D_1F800160_3621 - 0x50F0) < 0x1F0;
}

void f_UpdatePipeAreaQuestPickupActor();
void func_80112808(s32 k) {
    u8 *p = func_80072DDC(NULL, 0, 5, 3);
    u8 *g;

    if (p != NULL) {
        g = D_800BF808_1760;
        g[2] = 1;
        g[3] = k;
        func_8004D650(k, 1);
        M2C_FIELD(p, void **, 0x1C) = f_UpdatePipeAreaQuestPickupActor;
        switch (k) {
        case 0x7C:
            p[3] = 0x83;
            D_800BF9FF = 3;
            break;
        case 0x7D:
            p[3] = 0x84;
            D_800BF9FF = 4;
            break;
        }
    }
}

void func_80113B40();
void f_UpdatePipeAreaQuestPickupActor();
void f_UpdatePipeAreaScenePropActor();
void func_8012B464();
u8 *func_801128B8(s32 a, s32 b) {
    u8 *p = func_80072DDC(a, 1, 5, 3);

    if (p == NULL) {
        return NULL;
    }
    p[0x3] = b;
    M2C_FIELD(p, void **, 0x1C) = f_UpdatePipeAreaQuestPickupActor;
    return p;
}

u8 *func_80112904(s32 a) {
    u8 *p = func_80072DDC(a, 1, 5, 3);

    if (p == NULL) {
        return NULL;
    }
    p[0x3] = 0;
    M2C_FIELD(p, void **, 0x1C) = f_UpdatePipeAreaQuestPickupActor;
    return p;
}

void f_UpdatePipeAreaScenePropActor();
void f_UpdatePipeAreaQuestPickupActor();
u8 *func_80112948(s32 a0) {
    u8 *p = func_80072DDC(a0, 0, 5, 3);

    if (p == NULL) {
        return NULL;
    }
    p[3] = 2;
    M2C_FIELD(p, void **, 0x1C) = f_UpdatePipeAreaQuestPickupActor;
    return p;
}

void func_80112990(u8 *a) {
    a[0xB] = 0x11;
    M2C_FIELD(a, s16 *, 0x7A) = 0x1C00;
    M2C_FIELD(a, s16 *, 0x7C) = 0x1C00;
    M2C_FIELD(a, s16 *, 0x7E) = 0x1C00;
    M2C_FIELD(a, s16 *, 0x5A) = 0;
    a[0x47] = 0;
    M2C_FIELD(a, s16 *, 0x5C) = 0;
    a[0xD] = 0;
    M2C_FIELD(a, s32 *, 0x3C) = D_800ECF80;
    func_80077B38(a, D_80139294_2487, 4);
    a[0] = 1;
    M2C_FIELD(a, s16 *, 0x80) = 0x20;
    M2C_FIELD(a, s16 *, 0x82) = 0x40;
    M2C_FIELD(a, s16 *, 0x84) = 0x20;
    M2C_FIELD(a, s16 *, 0x86) = 0x40;
    func_8004B354(a, 0);
}

void func_80112A20(s32 arg0) {
    func_8007778C();
    func_8004B374(arg0, 0);
}

void func_80112A50(void *arg0) {
    func_8004D4C4(0x7F, 1);
    func_8004B0D8(arg0);
    M2C_FIELD(arg0, s8 *, 4) = 3;
}

void func_80112A8C(u8 *a) {
    switch (a[6]) {
    case 0:
        if (a[0x2B] != 0) {
            func_80112B10(a);
            a[6]++;
        }
        break;
    case 1:
        if (a[0x2B] == 0) {
            a[6] = 0;
        }
        break;
    }
    a[0x2B] = 0;
}

void func_80112B10(u8 *a) {
    switch (M2C_FIELD(a, s16 *, 0x68)) {
    case 0x7C:
        M2C_FIELD(a, s32 *, 0x3C) = D_800ECF80;
        func_80077B38(a, D_80139294_2487, 7);
        M2C_FIELD(a, s16 *, 0x68) = 0x7D;
        a[3] = 4;
        D_800BF9FF = 4;
        break;
    case 0x7D:
        M2C_FIELD(a, s32 *, 0x3C) = D_800ECF80;
        func_80077B38(a, D_80139294_2487, 8);
        a[0xD] = 1;
        M2C_FIELD(a, s16 *, 0x68) = 0x7E;
        a[3] = 5;
        D_800BF9FF = 5;
        break;
    }
}

extern M2C_UNK D_80135628;
void func_80112BB8(void *arg0) {
    u8 temp_v1;

    func_80041098();
    temp_v1 = M2C_FIELD(arg0, u8 *, 6);
    switch (temp_v1) {                              /* irregular */
    case 0:
        func_80112CB8(arg0);
        if (M2C_FIELD(arg0, u8 *, 0x71) == 0xFF) {
            func_80040D68(arg0, &D_80135628);
            M2C_FIELD(arg0, s8 *, 0x70) = 1;
            M2C_FIELD(arg0, u8 *, 6) = (u8) (M2C_FIELD(arg0, u8 *, 6) + 1);
            return;
        }
        return;
    case 1:
        func_80112CB8(arg0);
        if (M2C_FIELD(arg0, u8 *, 0x71) == 0) {
            M2C_FIELD(arg0, s16 *, 0x36) = 0x2340;
            M2C_FIELD(arg0, s8 *, 0x70) = 1;
            M2C_FIELD(arg0, u8 *, 6) = (u8) (M2C_FIELD(arg0, u8 *, 6) + 1);
            return;
        }
        break;
    case 2:
        if (M2C_FIELD(arg0, u8 *, 0x71) == 0xFF) {
            M2C_FIELD(arg0, s8 *, 0) = 1;
            M2C_FIELD(arg0, s8 *, 5) = 0;
            M2C_FIELD(arg0, u8 *, 6) = 0U;
            M2C_FIELD(arg0, u8 *, 3) = (u8) (M2C_FIELD(arg0, u8 *, 3) & 0x7F);
            M2C_FIELD(arg0, u16 *, 0x68) = (u16) M2C_FIELD(arg0, u16 *, 0x60);
        }
        break;
    }
}

extern PairOwner D_800E7E80_6978;
void func_80112CB8(u8 *a) {
    PairOwner *g = &D_800E7E80_6978;

    M2C_FIELD(a, s16 *, 0x2E) = (g->p0[0x2C / 4] + g->p1[0x2C / 4]) / 2;
    M2C_FIELD(a, s16 *, 0x32) = (g->p0[0x30 / 4] + g->p1[0x30 / 4]) / 2;
    M2C_FIELD(a, s16 *, 0x36) = (g->p0[0x34 / 4] + g->p1[0x34 / 4]) / 2;
    M2C_FIELD(a, s16 *, 0x2E) += func_80083F50(M2C_FIELD(g, s16 *, 0x56)) >> 6;
    M2C_FIELD(a, s16 *, 0x2E) += func_80083F50(M2C_FIELD(g, s16 *, 0x56)) >> 8;
    M2C_FIELD(a, s16 *, 0x32) -= 0x14;
}

extern u8 *D_800BF844;
extern u8 D_80135C38[];
extern u8 D_80135BE8[];
extern u8 *D_80138FFC_e406;
extern u8 D_80139000;
s32 func_80112DA0(u8 *a) {
    M2C_FIELD(a, s16 *, 0x32) += 8;
    if (M2C_FIELD(a, s16 *, 0x32) >= -0x1AB2) {
        M2C_FIELD(a, s16 *, 0x32) = -0x1AB2;
        return 1;
    }
    return 0;
}

u8 *func_80112DD8(u8 *a) {
    u8 t;
    u8 *p = func_80072DDC(a, 0, 5, 3);

    if (p == NULL) {
        return NULL;
    }
    t = a[3];
    M2C_FIELD(p, void **, 0x1C) = f_UpdatePipeAreaQuestPickupActor;
    p[0x3] = (t & 1) + 6;
    M2C_FIELD(p, s16 *, 0x2E) = M2C_FIELD(a, u16 *, 0x2E);
    M2C_FIELD(p, s16 *, 0x32) = M2C_FIELD(a, u16 *, 0x32);
    M2C_FIELD(p, s16 *, 0x36) = M2C_FIELD(a, u16 *, 0x36);
    return p;
}

void func_80112E58(u8 *a) {
    a[0xB] = 0x11;
    M2C_FIELD(a, s16 *, 0x7A) = 0x1C00;
    M2C_FIELD(a, s16 *, 0x7C) = 0x1C00;
    M2C_FIELD(a, s16 *, 0x7E) = 0x1C00;
    M2C_FIELD(a, s16 *, 0x5A) = 0;
    a[0x47] = 0;
    M2C_FIELD(a, s16 *, 0x5C) = 0;
    a[0xD] = 0;
    M2C_FIELD(a, s32 *, 0x3C) = D_800ECF80;
    func_80077B38(a, D_80139294_2487, 0xC);
    a[0] = 1;
    M2C_FIELD(a, s16 *, 0x80) = 0x20;
    M2C_FIELD(a, s16 *, 0x82) = 0x40;
    M2C_FIELD(a, s16 *, 0x84) = 0x20;
    M2C_FIELD(a, s16 *, 0x86) = 0x40;
}

void func_80112EDC(void) {
    func_8007778C();
}

void func_80112EFC(void *arg0) {
    if (func_80040C00(0x65) >= 0) {
        func_8004D4C4(0x3E, 1);
        func_8004B0D8(arg0);
        D_800BF870.pad1[0x17B] += 1 << ((M2C_FIELD(arg0, u8 *, 3) & 1) * 2);
    }
    M2C_FIELD(arg0, s8 *, 4) = 3;
}

extern M2C_UNK D_80139294;
void func_80112F6C(void *arg0) {
    if (D_800BF871 != 0x1A) {
        M2C_FIELD(arg0, s8 *, 4) = 3;
        return;
    }
    M2C_FIELD(arg0, s8 *, 0xB) = 0x10;
    M2C_FIELD(arg0, s16 *, 0x5A) = 0;
    M2C_FIELD(arg0, s8 *, 0x47) = 0;
    M2C_FIELD(arg0, s16 *, 0x5C) = 0;
    M2C_FIELD(arg0, s8 *, 0xD) = 0;
    M2C_FIELD(arg0, s32 *, 0x3C) = (s32) D_800ECF80;
    func_80077B38(arg0, &D_80139294, 0xE);
    M2C_FIELD(arg0, s8 *, 0) = 1;
    M2C_FIELD(arg0, s16 *, 0x80) = 0x20;
    M2C_FIELD(arg0, s16 *, 0x82) = 0x40;
    M2C_FIELD(arg0, s16 *, 0x84) = 0x20;
    M2C_FIELD(arg0, s16 *, 0x86) = 0x40;
    func_8004B354(arg0, 0);
    M2C_FIELD(arg0, s16 *, 0x68) = 0x92;
}

void func_80113014(s32 arg0) {
    func_8007778C();
    func_8004B374(arg0, 0);
}

void func_80113044(void *arg0) {
    M2C_FIELD(arg0, s8 *, 3) = 0xF;
    func_8004A828();
    func_8004B354(arg0, 0);
    M2C_FIELD(arg0, s8 *, 0xB) = 0x10;
    M2C_FIELD(arg0, s8 *, 3) = 9;
    M2C_FIELD(arg0, s8 *, 0) = 1;
}

void func_80113094(void *arg0) {
    M2C_FIELD(arg0, s8 *, 1) = 1;
    func_80077EFC();
    func_8004B374(arg0, 0);
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_801130CC);

extern u8 D_800BFA06;
void func_801132B8(void *arg0) {
    u8 temp_v1;
    void *temp_s1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 5);
    temp_s1 = M2C_FIELD(M2C_FIELD(arg0, void **, 0x10), void **, 0xC0);
    switch (temp_v1) {                              /* irregular */
    case 0:
        if (D_800BFA06 & 2) {
            M2C_FIELD(arg0, u8 *, 5) = 3U;
        } else {
            M2C_FIELD(arg0, u8 *, 5) = 1U;
        }
        M2C_FIELD(arg0, s8 *, 0) = 1;
        func_8004B354(arg0, 1);
        M2C_FIELD(arg0, s16 *, 0xB8) = 0x1800;
        M2C_FIELD(arg0, s16 *, 0xBA) = 0x1800;
        M2C_FIELD(arg0, s16 *, 0xBC) = 0x1800;
        break;
    case 1:
        if (D_800BFA06 & 2) {
            M2C_FIELD(arg0, u8 *, 5) = 2U;
            M2C_FIELD(arg0, s8 *, 6) = 0;
        }
        break;
    case 2:
        if (func_801130CC(arg0) != 0) {
            M2C_FIELD(arg0, u8 *, 5) = (u8) (M2C_FIELD(arg0, u8 *, 5) + 1);
        }
        break;
    }
    M2C_FIELD(arg0, u16 *, 0x2E) = (u16) M2C_FIELD(temp_s1, u16 *, 0x2C);
    M2C_FIELD(arg0, s16 *, 0x32) = (s16) (M2C_FIELD(temp_s1, u16 *, 0x30) - 0x48);
    M2C_FIELD(arg0, u16 *, 0x36) = (u16) M2C_FIELD(temp_s1, u16 *, 0x34);
    if (func_8007778C(arg0) != 0) {
        func_80051844(arg0);
        func_8004B374(arg0, 1);
    }
}

void func_801133F4(u8 *a) {
    u8 *q = M2C_FIELD(M2C_FIELD(a, u8 **, 0x10), u8 **, 0xC0);

    switch (a[5]) {
    case 0:
        a[5]++;
        a[0] = 1;
        func_8004B354(a, 0);
    case 1:
        M2C_FIELD(a, s16 *, 0x2E) = M2C_FIELD(q, s16 *, 0x2C);
        M2C_FIELD(a, s16 *, 0x32) = M2C_FIELD(q, s16 *, 0x30) - 0x48;
        M2C_FIELD(a, s16 *, 0x36) = M2C_FIELD(q, s16 *, 0x34);
        if (func_8007778C(a) != 0) {
            func_8004B374(a, 0);
        }
        break;
    }
}

void func_80113490(u8 *a) {
    switch (a[5]) {
    case 0:
        a[5]++;
        a[0] = 1;
        M2C_FIELD(a, s16 *, 0x4A) = 0;
    case 1:
        M2C_FIELD(a, s16 *, 0x4A) += 0x300;
        if (M2C_FIELD(a, s16 *, 0x4A) > 0x3000) {
            M2C_FIELD(a, s16 *, 0x4A) = 0x3000;
        }
        M2C_FIELD(a, s32 *, 0x30) += M2C_FIELD(a, s16 *, 0x4A) << 8;
        if (a[0x29] == 0) {
            func_8004766C(a);
            func_80049250(a, 0, (s16)(M2C_FIELD(a, u16 *, 0x86) - M2C_FIELD(a, u16 *, 0x84)));
        }
        break;
    }
    func_8007778C(a);
    a[0x29] = 0;
}

extern u8 D_800BF818;
void func_80113554(u8 *a, u8 *b) {
    u8 *t;

    switch (a[5]) {
    case 0:
        a[5]++;
        F16(b, 0xE) = F16(b, 0xA);
        func_80072FE0(a);
        a[0x5E] = 1;
        break;
    case 1:
        if (D_800BF818 == 2) {
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
            D_800BF818 = 0;
        }
        break;
    }
}

#define LH(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define LP(p) (*(u8 **)((u8 *)(p) + 0xC0))
extern u8 D_80135B24[][2];
extern s16 *D_80135B0C[];
extern s16 D_800ED098;
void func_80113710(u8 *a) {
    s32 i;
    s16 *r;
    u8 *pa;
    u8 *q;

    switch (a[4]) {
    case 0:
        a[8] = D_80135B24[a[3]][0];
        if (D_800ED098 < a[8]) {
            a[4] = 3;
            break;
        }
        a[9] = a[8];
        a[4]++;
        a[0xD] = 0;
        a[0xB] = 0;
        LH(a, 0x54) = 0;
        LH(a, 0x56) = 0;
        LH(a, 0x58) = 0;
        r = D_80135B0C[a[3]];
        i = 0;
        if (a[8] != 0) {
            pa = a;
        loop:
            i++;
            q = func_8007AAE8();
            LP(pa) = q;
            LH(q, 6) = *r++;
            LH(LP(pa), 0) = *r++;
            LH(LP(pa), 2) = *r++;
            LH(LP(pa), 4) = *r++;
            LH(LP(pa), 8) = *r++;
            LH(LP(pa), 0xA) = *r++;
            LH(LP(pa), 0xC) = *r++;
            func_80051B04(LP(pa), 0xC, *r++);
            pa += 4;
            if (i < a[8]) {
                goto loop;
            }
        }
        a[0xD] |= 4;
        LP(a)[0x3F] = 0x10;
        switch (a[3]) {
        case 0:
            a[0x46] = 1;
            a[0xBF] = 1;
            a[0x5E] = 0;
            break;
        case 1:
            LH(LP(a), 2) = 0x28A;
            break;
        case 4:
            a[0x46] = 1;
            a[0xBF] = 1;
            func_80040C00(0x56);
            break;
        case 5:
            a[0xBF] = 1;
            a[0x46] = 0;
            LH(a, 0x56) = 0xC00;
            break;
        case 2:
        case 3:
            break;
        }
        break;
    case 1:
        switch (a[3]) {
        case 0:
        case 4:
            func_80113554(a, *(u8 **)(a + 0xC4));
            LH(*(u8 **)(a + 0xC8), 0xA) = LH(*(u8 **)(a + 0xC4), 0xA);
            break;
        case 5:
            func_80113554(a, *(u8 **)(a + 0xC4));
            break;
        case 1:
        case 2:
        case 3:
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

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_801139D4);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80113B40);

void func_801139D4();
void f_UpdatePipeAreaBridgeActor();
u8 *func_80113CB4(u8 *a) {
    u8 *p = func_80072DDC((s32)a, 0, 3, 0xF);

    if (p != NULL) {
        M2C_FIELD(p, void **, 0x1C) = func_801139D4;
        p[3] = 0;
    }
    M2C_FIELD(a, u8 **, 0x14) = p;
    return p;
}

u8 *func_80113D04(s32 a) {
    u8 *p = func_80072DDC(a, 0, 3, 15);

    if (p != NULL) {
        M2C_FIELD(p, void **, 0x1C) = func_80113B40;
        p[0x3] = 0;
    }
    return p;
}

extern PartInit D_80135B30[];

s32 func_80113D44(PartsOwner *a) {
    s32 i;
    u8 *q;

    a->pad[8] = 2;
    if (D_800ED098 < a->pad[8]) {
        a->pad[4] = 3;
        return 0;
    }
    a->pad[9] = 2;
    a->pad[0xD] = 2;
    a->pad[0xB] = 0;
    *(s16 *)(a->pad + 0x54) = 0;
    *(s16 *)(a->pad + 0x56) = 0;
    *(s16 *)(a->pad + 0x58) = 0;
    *(s16 *)(a->pad + 0xB8) = 0x1500;
    *(s16 *)(a->pad + 0xBA) = 0x1500;
    *(s16 *)(a->pad + 0xBC) = 0x1500;
    func_8004B354(a, 1);
    for (i = 0; i < a->pad[8]; i++) {
        q = func_8007AAE8();
        a->parts[i] = q;
        *(s16 *)(q + 6) = D_80135B30[i].v[0];
        *(s16 *)(a->parts[i] + 0) = D_80135B30[i].v[1];
        *(s16 *)(a->parts[i] + 2) = D_80135B30[i].v[2];
        *(s16 *)(a->parts[i] + 4) = D_80135B30[i].v[3];
        *(s16 *)(a->parts[i] + 8) = 0;
        *(s16 *)(a->parts[i] + 0xA) = 0;
        *(s16 *)(a->parts[i] + 0xC) = 0;
        *(s16 *)(a->parts[i] + 0x38) = 0x1000;
        *(s16 *)(a->parts[i] + 0x3A) = 0x1000;
        *(s16 *)(a->parts[i] + 0x3C) = 0x1000;
        func_80051B04(a->parts[i], 0xC, i + 0x16);
    }
    return 1;
}

extern s16 *D_80135B60[];
void func_80113EB8(u8 *a) {

    s32 i;
    s32 k;
    s16 *r;
    u8 *q;

    a[8] = 2;
    if (D_800ED098 < 2) {
        a[4] = 3;
        return;
    }
    k = 0x23;
    { s32 n = 2; a[9] = n; }
    a[0xD] = 4;
    a[0xB] = 0;
    LH(a, 0x54) = 0;
    LH(a, 0x56) = 0;
    LH(a, 0x58) = 0;
    if (a[3] == 1) {
        k = 0x1C;
    }
    r = D_80135B60[a[3] - 1];
    for (i = 0; i < a[8]; i++) {
        q = func_8007AAE8();
        LP(a + i * 4) = q;
        LH(q, 6) = *r++;
        LH(LP(a + i * 4), 0) = *r++;
        LH(LP(a + i * 4), 2) = *r++;
        LH(LP(a + i * 4), 4) = *r++;
        LH(LP(a + i * 4), 8) = 0;
        LH(LP(a + i * 4), 0xA) = 0;
        LH(LP(a + i * 4), 0xC) = 0;
        func_80051B04(LP(a + i * 4), 0xC, k + i);
    }
    (*(u8 **)(a + 0xC4))[0x3F] = 0xF0;
}

#define H(p, o) (*(s16 *)((u8 *)(p) + (o)))
extern u8 D_800E806E;
s32 func_80114018(u8 *a) {
    u8 *p;

    switch (a[6]) {
    case 0:
        if (D_800E806E == 3) {
            a[6] = 1;
            H(a, 0x40) = 0xF;
        }
        H(*(u8 **)(a + 0xC0), 2) = -((D_1F80017C & 2) * 6);
        H(*(u8 **)(a + 0xC0), 0) = ((func_8009A450() & 3) - 2) * 6;
        break;
    case 1:
        if (--H(a, 0x40) == -1) {
            p = a + 0x2C;
            a[6]++;
            func_80027144(*(s32 *)(*(u8 **)(a + 0xC4) + 0x40), p, 0x400, 4);
            func_80074590(0xC, 0, 0);
            func_80027144(*(s32 *)(*(u8 **)(a + 0xC4) + 0x40), p, 0x400, 4);
            func_80074590(0xC, 0, 0);
            *(s32 *)(*(u8 **)(a + 0xC4) + 0x40) = 0;
        }
        H(*(u8 **)(a + 0xC0), 2) = -((D_1F80017C & 2) * 6);
        H(*(u8 **)(a + 0xC0), 0) = ((func_8009A450() & 3) - 2) * 6;
        break;
    case 2:
        a[6]++;
        H(a, 0x4A) = -0x2000;
        H(a, 0x50) = 0x200;
        break;
    case 3:
        if (a[1] == 0) {
            return 1;
        }
        H(a, 0x54) += 0x100;
        H(a, 0x56) += 0x40;
        H(a, 0x36) -= 0x10;
        *(s32 *)(a + 0x30) += H(a, 0x4A) << 8;
        H(a, 0x4A) += H(a, 0x50);
        break;
    default:
        return 0;
    }
    return 0;
}

#define H(p, o) (*(s16 *)((u8 *)(p) + (o)))
extern u8 D_800BF9FD;
void f_UpdateCoalMiningTownEntranceOpeningSequence(u8 *a) {
    s32 s;
    s32 v;
    s32 one;
    u8 *e;

    func_8007778C(a);
    one = 1;
    s = a[5];
    switch (s) {
    case 0:
        if (a[3] == one) {
            v = D_800BF9FD & 1;
        } else {
            v = D_800BF9FD & 2;
        }
        if (v != 0) {
            a[5] = one;
        }
        break;
    case 1:
        a[5] = 2;
        func_8006E1C0(one);
        e = D_800E8008;
        H(e, 0x6C) = 0x578;
        H(e, 0x6E) = 0x100;
        H(e, 0x70) = 0x400;
        H(e, 0x3A) = H(a, 0x2E);
        H(e, 0x3E) = H(a, 0x32);
        H(e, 0x42) = H(a, 0x36);
    case 2:
        if (func_80114018(a) != 0) {
            a[5]++;
        }
        break;
    case 3:
        a[4] = s;
        if (a[3] == one) {
            D_800BF870.pad1[0x18C] |= 4;
        } else {
            D_800BF870.pad1[0x18C] |= 8;
        }
        if (((D_800BF9FD >> 2) & 3) != 3) {
            func_80042310(one);
            func_8006E1E4();
        }
        break;
    }
    if (a[1] != 0) {
        func_800517F8(a);
    }
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80114380);

#define GH(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define GW(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define GPART(a, i) (*(u8 **)((u8 *)(a) + (i) * 4 + 0xC0))
extern u8 D_800BF909;
extern s16 D_800E7EB6;
/* func_80115CA0, inlined */
static inline s32 lift_ready(u8 *a, s32 b) {
    u8 *t = D_800E7E80;

    if (*(s16 *)(t + 0x36) >= 0x4149) {
        *(s16 *)(t + 0x36) = 0x4149;
        if (b == 2) {
            if (D_1F800137 == 1) {
                return 1;
            }
            if (D_800BF909 == 0xFF) {
                D_1F800137 = b;
                return 1;
            }
        }
    }
    return 0;
}
void f_UpdateTurboTrolleyLiftSequence(u8 *a) {
    s16 h;
    s32 i, k;
    s32 s = a[5];
    u8 *c = D_800E8008;
    u8 *t;

    switch (s) {
    case 0:
        if (lift_ready(a, 2) != 0) {
            a[5]++;
        }
        break;
    case 1:
        D_1F800190 = 0x80;
        t = D_800E7E80;
        if (MEMBER_AT(s16, a, 0x36) <= GH(t, 0x36)) {
            GH(t, 0x36) = GH(a, 0x36);
            D_1F800190 = 0;
            a[5]++;
            GH(c, 0x6E) = 0x60;
            GH(c, 0x70) = 0x400;
            c[0x64] = s;
            GH(c, 0x6C) = 0x6D6;
            func_8006CBA8(a + 0x2C);
            GH(a, 0x42) = s;
        }
        break;
    case 2:
        k = (u16)GH(a, 0x60) - 0xC8;
        h = ((u16)GH(a, 0x36) - k) * 8;
        GH(a, 0x44) = h;
        if (GH(a, 0x36) < 0x5208) {
            GW(a, 0x34) += h << 8;
        }
        for (i = 1; i < a[8]; i++) {
            GH(GPART(a, i), 0xC) -= GH(a, 0x44) >> 3;
        }
        if (--GH(a, 0x42) == 0) {
            func_80074590(0x8D, 0, 0);
            if (h > 0x2000) {
                h = 0x2000;
            }
            GH(a, 0x42) = (0x3000 - h) >> 8;
        }
        D_800E7EB6 = GH(a, 0x36);
        func_8006CBA8(a + 0x2C);
        break;
    }
}

#define GH(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define GW(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define GPART(a, i) (*(u8 **)((u8 *)(a) + (i) * 4 + 0xC0))
extern u8 D_1F8000D0_b839[];
extern u8 D_800E806C;
extern u8 D_800BF9FB_3655;
void f_UpdateQuickTrolleyDescentSequence(u8 *a) {
    s16 h;
    s32 i, k;
    u8 *sc;

    switch (a[5]) {
    case 0:
        GH(a, 0x36) = 0x4E20;
        GH(a, 0x44) = 0x2000;
        a[5]++;
        D_800E806C = 7;
        {
            u8 *s0 = D_1F8000D0_b839;
            GH(s0, 2) = 0x2E61;
            GH(s0, 6) = -0x11D1;
            GH(s0, 0xA) = 0x3EBF;
        }
        GH(a, 0x42) = (0x3000 - GH(a, 0x44)) >> 8;
        break;
    case 1:
        if (--GH(a, 0x42) == 0) {
            func_80074590(0x8D, 0, 0);
            GH(a, 0x42) = (0x3000 - GH(a, 0x44)) >> 8;
        }
        k = (u16)GH(a, 0x60) - 0xC8;
        h = ((u16)GH(a, 0x36) - k) * 8;
        if (h < 0x2000) {
            GH(a, 0x44) = h;
        }
        GW(a, 0x34) -= GH(a, 0x44) << 8;
        for (i = 1; i < a[8]; i++) {
            GH(GPART(a, i), 0xC) += GH(a, 0x44) >> 3;
        }
        if (GH(a, 0x36) < GH(a, 0x60) + 0x12C) {
            sc = D_1F8000D0_b839;
            if ((GH(sc, 2) -= 8) < 0x2D71) {
                GH(sc, 2) = 0x2D71;
            }
            if ((GH(sc, 6) -= 8) < -0x12A9) {
                GH(sc, 6) = -0x12A9;
            }
            if ((GH(sc, 0xA) += 0x10) > 0x409F) {
                GH(sc, 0xA) = 0x409F;
            }
        }
        if (GH(a, 0x36) < GH(a, 0x60)) {
            GH(a, 0x36) = GH(a, 0x60);
            GH(a, 0x40) = 6;
            a[5]++;
        }
        break;
    case 2:
        {
            s32 r2 = func_8009A450() & 0xF;
            s32 k2 = (u16)GH(a, 0x60) - 8;
            GH(a, 0x36) = k2 + r2;
        }
        func_800521F4(0, 0, 0x81, 2);
        if (--GH(a, 0x40) == 0) {
            GH(a, 0x40) = 0x28;
            a[5]++;
        }
        break;
    case 3:
        if (--GH(a, 0x40) == 0) {
            D_800E806C = 1;
            D_800BF9FB_3655 = 2;
            a[5] = 0;
        }
        break;
    }
    func_8006CBA8(a + 0x2C);
    if (func_8007778C(a) != 0) {
        func_800517F8(a);
    }
}

#define GH(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define GW(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define GPART(a, i) (*(u8 **)((u8 *)(a) + (i) * 4 + 0xC0))
void func_80114A28(u8 *a) {
    s16 h;
    s32 i, k;
    u8 *sc;
    u8 *t;

    switch (a[5]) {
    case 0:
        if (a[0x46] != 0) {
            break;
        }
        func_8006E1C0(7);
        {
            u8 *s0 = D_1F8000D0_b839;
            GH(s0, 2) = 0x2E61;
            GH(s0, 6) = -0x11D1;
            GH(s0, 0xA) = 0x3EBF;
        }
        GH(a, 0x36) = 0x4E20;
        GH(a, 0x42) = 1;
        a[5]++;
    case 1:
        k = (u16)GH(a, 0x60) - 0xC8;
        h = ((u16)GH(a, 0x36) - k) * 8;
        GH(a, 0x44) = h;
        GW(a, 0x34) -= h << 8;
        if (--GH(a, 0x42) == 0) {
            func_80074590(0x8D, 0, 0);
            if (h > 0x2000) {
                h = 0x2000;
            }
            GH(a, 0x42) = (0x3000 - h) >> 8;
        }
        for (i = 1; i < a[8]; i++) {
            GH(GPART(a, i), 0xC) += GH(a, 0x44) >> 3;
        }
        if (GH(a, 0x36) < GH(a, 0x60) + 0x12C) {
            sc = D_1F8000D0_b839;
            if ((GH(sc, 2) -= 8) < 0x2D71) {
                GH(sc, 2) = 0x2D71;
            }
            if ((GH(sc, 6) -= 8) < -0x12A9) {
                GH(sc, 6) = -0x12A9;
            }
            if ((GH(sc, 0xA) += 0x10) > 0x409F) {
                GH(sc, 0xA) = 0x409F;
            }
        }
        if (GH(a, 0x36) < GH(a, 0x60)) {
            GH(a, 0x36) = GH(a, 0x60);
            GH(a, 0x40) = 6;
            a[5]++;
        }
        D_800E7EB6 = GH(a, 0x36);
        func_8006CBA8(a + 0x2C);
        break;
    case 2:
        {
            s32 r2 = func_8009A450() & 0xF;
            s32 k2 = (u16)GH(a, 0x60) - 8;
            GH(a, 0x36) = k2 + r2;
        }
        if (--GH(a, 0x40) == 0) {
            GH(a, 0x40) = 0x1E;
            a[5]++;
        }
        D_800E7EB6 = GH(a, 0x36);
        func_8006CBA8(a + 0x2C);
        break;
    case 3:
        if (--GH(a, 0x40) == 0) {
            func_8006E1E4();
            D_1F800190 = 0x20;
            a[5]++;
        }
        func_8006CBA8(a + 0x2C);
        break;
    case 4:
        t = D_800E7E80;
        if (GH(t, 0x36) < 0x4011) {
            GH(t, 0x36) = 0x4010;
            D_1F800190 = 0;
            func_80054198(t);
            a[0x46] = 1;
            a[5] = 0;
        }
        break;
    case 5:
        break;
    }
}

void f_UpdatePipeAreaTrolleyCutscene(u8 *a) {
    u8 *t;

    switch (D_800BF9FB_3655) {
    case 1:
        f_UpdateQuickTrolleyDescentSequence(a);
    case 0:
        t = D_800E7E80;
        if (F16(t, 0x36) >= 0x4149) {
            F16(t, 0x36) = 0x4149;
        }
        break;
    case 2:
        f_UpdateTurboTrolleyLiftSequence(a);
        func_800517F8(a);
        a[1] = 1;
        break;
    case 3:
    case 4:
        func_80114A28(a);
        func_800517F8(a);
        a[1] = 1;
        break;
    case 5:
        func_80051B04(FP(a, 0xC0), 0xC, 0x31);
        func_80051B04(FP(a, 0xC4), 0xC, 0x32);
        func_80051B04(FP(a, 0xC8), 0xC, 0x32);
        func_80051B04(FP(a, 0xCC), 0xC, 0x33);
        func_80051B04(FP(a, 0xD0), 0xC, 0x33);
        D_800BF9FB_3655 = 0;
        break;
    }
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80114E50);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80115088);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80115278);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80115428);

INCLUDE_ASM("asm/a01/nonmatchings/a01", f_UpdatePipeAreaScenePropActor);

void func_80115BF4(s32 arg0) {
    if (func_8007778C() != 0) {
        func_80051844(arg0);
        func_8004B374(arg0, 1);
    }
}

void func_80115C34(u8 *a)
{
    if (func_80051B70(a, 0xC, 0x1F) == 0) {
        *(s16 *)(a + 0x54) = 0;
        *(s16 *)(a + 0x56) = 0;
        *(s16 *)(a + 0x58) = 0;
    }
}

void func_80115C74(void *arg0) {
    func_800517F8();
    M2C_FIELD(arg0, s8 *, 1) = 1;
}

s32 func_80115CA0(u8 *a, s32 b) {
    u8 *t = D_800E7E80;

    if (*(s16 *)(t + 0x36) >= 0x4149) {
        *(s16 *)(t + 0x36) = 0x4149;
        if (b == 2) {
            if (D_1F800137 == 1) {
                return 1;
            }
            if (D_800BF909 == 0xFF) {
                D_1F800137 = b;
                return 1;
            }
        }
    }
    return 0;
}

extern s8 D_800BF9FB;
void func_80115D0C(void *arg0) {
    func_80051B04(M2C_FIELD(arg0, s32 *, 0xC0), 0xC, 0x31);
    func_80051B04(M2C_FIELD(arg0, s32 *, 0xC4), 0xC, 0x32);
    func_80051B04(M2C_FIELD(arg0, s32 *, 0xC8), 0xC, 0x32);
    func_80051B04(M2C_FIELD(arg0, s32 *, 0xCC), 0xC, 0x33);
    func_80051B04(M2C_FIELD(arg0, s32 *, 0xD0), 0xC, 0x33);
    D_800BF9FB = 0;
}

void func_8012AF08();
void f_UpdatePipeAreaQuestSceneryActor();
void func_8011F7CC();
void func_8013362C();
void func_8011A27C();
u8 *func_80115D84(s32 a) {
    u8 *p = func_8007A980(1, 3, 1);

    if (p == NULL) {
        return NULL;
    }
    p[0x2] = 16;
    p[0x3] = 5;
    M2C_FIELD(p, void **, 0x1C) = f_UpdatePipeAreaScenePropActor;
    M2C_FIELD(p, s32 *, 0x10) = a;
    return p;
}

void func_80115DE0(u8 *a) {
    PairOwner *g;

    if (func_80051B70(a, 0xC, 0x18) != 0) {
        return;
    }
    g = &D_800E7E80_6978;
    M2C_FIELD(a, s16 *, 0x2E) = (g->p0[0x2C / 4] + g->p1[0x2C / 4]) / 2;
    M2C_FIELD(a, s16 *, 0x32) = (g->p0[0x30 / 4] + g->p1[0x30 / 4]) / 2;
    M2C_FIELD(a, s16 *, 0x36) = (g->p0[0x34 / 4] + g->p1[0x34 / 4]) / 2;
    M2C_FIELD(a, s16 *, 0x32) -= 0x20;
    M2C_FIELD(a, s16 *, 0x58) = 0;
    M2C_FIELD(a, s16 *, 0x56) = 0;
    M2C_FIELD(a, s16 *, 0x54) = 0;
    M2C_FIELD(a, s16 *, 0x80) = 0x40;
    M2C_FIELD(a, s16 *, 0x82) = 0x80;
    M2C_FIELD(a, s16 *, 0x84) = 0x64;
    M2C_FIELD(a, s16 *, 0x86) = 0x64;
}

void func_80115EC0(u8 *a) {
    if (func_80051B70(a, 0xC, 0x44) == 0) {
        M2C_FIELD(a, s16 *, 0x60) = a[2];
        a[2] = 0x10;
        func_800517F8(a);
    }
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80115F08);

u8 *func_80115F70(s32 a0) {
    u8 *p = func_80072DDC(a0, 2, 4, 0x12);

    if (p != NULL) {
        M2C_FIELD(p, void **, 0x1C) = f_UpdatePipeAreaScenePropActor;
        p[3] = 7;
    }
    return p;
}

void func_80115FB4(u8 *a)
{
    func_80051B70(a, 0xC, 0x4A);
    *(s16 *)(a + 0x54) = 0;
    *(s16 *)(a + 0x56) = 0;
    *(s16 *)(a + 0x58) = 0;
}

extern s16 D_1F8000C0_65b0[];
void func_80115FEC(u8 *a) {
    u8 *p = M2C_FIELD(a, u8 **, 0x10);
    s16 *v;
    GameState *g;

    D_1F8000C0_65b0[0] = 0;
    v = D_1F8000C0_65b0;
    v[1] = 0x62;
    v[2] = -0x20;
    func_8004BD64(a, 2, M2C_FIELD(p, void **, 0xDC), M2C_FIELD(p, void **, 0xD0), v);
    g = &D_800BF870;
    if (g->pad1[0x1CD] == 1) {
        a[4] = 3;
        func_8004D4F4(0x1C, 1);
        func_80026100(g->pad1[0xE]);
        func_8004ED94(0x70, 0x41);
        func_8004B2E8(a);
    }
    a[1] = 1;
    func_800517F8(a);
}

u8 *func_801160A4(s32 a, s32 b) {
    u8 *p = func_80072DDC(a, 0, 3, 16);

    if (p != NULL) {
        M2C_FIELD(p, void **, 0x1C) = f_UpdatePipeAreaScenePropActor;
        p[0x3] = 9;
        p[0x5E] = b;
    }
    return p;
}

void func_801160F8(u8 *a) {
    M2C_FIELD(a, s32 *, 0x3C) = D_800ECF80;
    func_80077B38(a, D_80139294_2487, func_8009A450() % 3 + 0x10);
    a[0xB] = 0x10;
    M2C_FIELD(a, s16 *, 0x2E) = 0x4C2C;
    M2C_FIELD(a, s16 *, 0x32) = -0x7EC;
    a[0xD] = 0;
    M2C_FIELD(a, s16 *, 0x5C) = 0;
    M2C_FIELD(a, s16 *, 0x5A) = 0;
    a[0x47] = 0;
    a[8] = 0;
    M2C_FIELD(a, s16 *, 0x36) = 0x1D60;
}

extern s16 D_80135BB8[];
extern s16 D_80135BA0_d762[];
void func_80116194(u8 *a)
{
    switch (a[6]) {
    case 0:
        if (a[0x5E] == 0) {
            M2C_FIELD(a, s16 *, 0x4A) = -0x2000;
            M2C_FIELD(a, s16 *, 0x50) = 0x200;
        } else if (a[0x5E] == 1) {
            M2C_FIELD(a, s16 *, 0x4A) = -0x2000;
            M2C_FIELD(a, s16 *, 0x50) = 0x200;
        } else if (a[0x5E] == 2) {
            M2C_FIELD(a, s16 *, 0x4A) = -0x2000;
            M2C_FIELD(a, s16 *, 0x50) = 0x200;
        } else {
            M2C_FIELD(a, s16 *, 0x4A) = -0x2000;
            M2C_FIELD(a, s16 *, 0x50) = 0x100;
        }
        M2C_FIELD(a, s16 *, 0x40) = 0x14;
        a[6]++;
        break;
    case 1:
        if (--M2C_FIELD(a, s16 *, 0x40) == 0) {
            a[4] = 3;
        }
        M2C_FIELD(a, s32 *, 0x30) += M2C_FIELD(a, s16 *, 0x4A) << 8;
        M2C_FIELD(a, s16 *, 0x4A) += M2C_FIELD(a, s16 *, 0x50);
        break;
    }
    a[1] = 1;
    func_80077B5C(a);
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80116294);

#define FH(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define SF(p, o) (((struct { u8 pad[o]; s16 v; } *)(p))->v)
extern s8 *D_800ECF58[];
extern u8 D_8013597C[];
extern u8 D_80139B24[];
extern u16 D_1F8001A0;
extern s16 D_1F800160_71b4;
extern s16 D_1F800164_d75f;
void func_80133D74();
/* func_80119BCC, inlined */
static inline s32 inl_80119BCC(u8 *a) {
    u8 *q = a + 0x60;
    s32 h = M2C_FIELD(q, u16 *, 4);
    s8 r;

    r = (u32)((h - func_800782B0(a + 0x2C, D_1F800160_71b4, D_1F800164_d75f) + 0x400) & 0xFFF) > 0x800;
    if (r) {
        M2C_FIELD(q, u16 *, 6) |= 1;
    } else {
        M2C_FIELD(q, u16 *, 6) &= 0xFFFE;
    }
    return r;
}
void func_8011638C(u8 *a) {
    s8 **t = D_800ECF58;
    u8 *q = a + 0x60;
    u8 *e;
    u16 h;

    if (func_800519E0(a, 0x12, t[0x6C / 4], D_8013597C) != 0) {
        return;
    }
    *(s8 **)(a + 0x3C) = t[0x70 / 4];
    func_80077C40(a, D_80139B24, 0);
    FH(a, 0x4E) = 0;
    FH(a, 0x50) = 0;
    switch (a[3]) {
    case 0:
        FH(a, 0x2E) = 0x3A60;
        FH(a, 0x32) = -0x1B58;
        FH(a, 0x36) = 0x2303;
        break;
    case 1:
        FH(a, 0x2E) = 0x304B;
        FH(a, 0x32) = -0x166C;
        FH(a, 0x36) = 0x2460;
        break;
    case 2:
        FH(a, 0x2E) = 0x3040;
        FH(a, 0x32) = -0x1A38;
        FH(a, 0x36) = 0x2DA3;
        break;
    case 3:
        FH(a, 0x2E) = 0x45BF;
        FH(a, 0x36) = 0x2340;
        FH(a, 0x32) = -0x18FA;
        FH(a, 0x4E) = FH(a, 0x2E);
        FH(a, 0x52) = FH(a, 0x36);
        break;
    case 4:
        FH(a, 0x2E) = 0x3040;
        FH(a, 0x36) = 0x1788;
        FH(a, 0x32) = -0x129E;
        FH(a, 0x4E) = FH(a, 0x2E);
        FH(a, 0x52) = FH(a, 0x36);
        break;
    }
    FH(q, 0x14) = FH(a, 0x2E);
    FH(q, 0x16) = FH(a, 0x36);
    func_8004766C(a);
    func_80049674(a);
    h = D_1F8001A0;
    q[8] = 0;
    SF(q, 6) = 0;
    SF(q, 0x12) = 0;
    SF(q, 4) = h;
    if (inl_80119BCC(a)) {
        FH(a, 0x56) = FH(q, 4) + 0x800;
    } else {
        FH(a, 0x56) = FH(q, 4);
    }
    FH(a, 0x54) = 0;
    FH(a, 0x58) = 0;
    __asm__ volatile("");
    a[0x1B] &= 0xBF;
    do { /* a barrier in its own loop block: the plain one leaves the a[3] load late */
        __asm__ volatile("");
    } while (0);
    q[0xA] = a[3];
    a[0] = 1;
    FH(a, 0xBC) = 0x1000;
    FH(a, 0xBA) = 0x1000;
    FH(a, 0xB8) = 0x1000;
    FH(a, 0x80) = 0x38;
    FH(a, 0x82) = 0x70;
    FH(a, 0x84) = 0x8C;
    FH(a, 0x86) = 0xF0;
    FH(a, 0x60) = 0;
    FH(a, 0x62) = 0;
    e = func_80072DDC(a, 3, 2, 0x22);
    *(u8 **)(a + 0x10) = e;
    if (e != NULL) {
        *(void **)(e + 0x1C) = func_80133D74;
        e[3] = 0;
        *(u8 **)(e + 0x10) = a;
    }
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80116620);

#define FH(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define FU(p, o) (*(u16 *)((u8 *)(p) + (o)))
extern u8 *D_800ECFC4;
extern s16 D_800E7FFE;
extern u8 D_80135BF8[];
extern u8 D_80135C08[];
extern u8 D_80135C18[];
extern u8 D_80135C28[];
/* func_801199DC, inlined */
static inline void inl_801199DC(u8 *a, s32 k, s32 f) {
    u8 *b;
    s32 *t;
    s32 s;

    if (a[0x46] != k) {
        a[0x46] = k;
        b = D_800ECFC4;
        t = (s32 *)(b + 4);
        switch (k) {
        case 5:
            s = 0x13;
            break;
        case 0xD:
        case 0xF:
        case 0x11:
            s = 0x12;
            break;
        default:
            s = 1;
            break;
        }
        M2C_FIELD(M2C_FIELD(a, u8 **, 0xC4), u8 **, 0x40) = b + t[s];
        if (!(f & 0xFF)) {
            func_80077C40(a, D_80139B24, k);
        } else {
            func_80077CFC(a, D_80139B24, k, (u8)f);
        }
    }
}
static inline s32 a01_target_y(u8 *a) {
    u8 *p = a + 0x2C;
    s32 v, y;

    switch (a[3]) {
    case 0:
        v = FH(p, 2);
        if (v < 0x3A14) {
            y = -0x1BCC;
        } else if (v < 0x3C69) {
            y = (v - 0x3A14) * 0x300 / 597 - 0x1BCC;
        } else {
            y = -0x18CC;
        }
        break;
    case 1:
        y = -0x156F;
        break;
    case 2:
        y = -0x1BD3;
        break;
    case 3:
        y = -0x1401;
        break;
    case 4:
        y = -0x1498;
        break;
    default:
        y = FH(p, 6);
        break;
    }
    return y;
}
s32 func_80116740(u8 *a, s32 k, s32 n) {
    s32 r = 0;
    u8 *q = a + 0x60;
    s32 y;

    switch (a[7]) {
    case 0:
        inl_801199DC(a, k, 4);
        FH(a, 0x42) = n;
        a[7]++;
    case 1:
        FH(a, 0x58) += func_80083E80(-FH(a, 0x58)) >> 5;
        FH(a, 0x4E) += -FH(a, 0x4E) >> 2;
        y = a01_target_y(a);
        y += func_80083F50(FH(q, 0x10)) >> 5;
        FH(q, 0x10) += func_8009A450() >> 9;
        FH(a, 0x32) += (y - FH(a, 0x32)) >> 4;
        if (FH(a, 0x42)-- <= 0) {
            r = 1;
        }
        break;
    }
    return r;
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80116994);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80117188);

#define FH(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define FU(p, o) (*(u16 *)((u8 *)(p) + (o)))
s32 func_80117188();
static inline void a01_turn(u8 *a) {
    u8 *q = a + 0x60;
    s32 v;
    if (!(FU(q, 6) & 1)) { FH(a, 0x56) += func_80083E80(FH(q, 4) - FH(a, 0x56)) >> 5; } else { v = FH(a, 0x56) - 0x800; FH(a, 0x56) += func_80083E80(FH(q, 4) - v) >> 5; }
}
s32 func_80117290(u8 *a) {
    s16 r = 0;
    u8 *q = a + 0x60;
    u8 *t;
    s32 y, old, d;

    switch (a[7]) {
    case 0:
        FH(a, 0x54) = 0;
        inl_801199DC(a, 2, 6);
        a[7]++;
    case 1:
        FH(a, 0x4E) += (0x70 - FH(a, 0x4E)) / 16;
        y = a01_target_y(a);
        y += func_80083F50(FH(q, 0x10)) >> 5;
        old = FH(a, 0x32);
        FH(q, 0x10) += func_8009A450() >> 9;
        FH(a, 0x32) += (y - FH(a, 0x32)) / 32;
        FH(a, 0x58) = (FH(a, 0x32) - old) * 16;
        a01_turn(a);
        r = ((s16 (*)(u8 *))func_80117188)(a);
        if (r != 0) {
            return r;
        }
    default:
        if (--FH(a, 0x42) <= 0) {
            d = func_800781E0(FH(a, 0x2E) - D_1F800160_71b4, FH(a, 0x36) - D_1F800164_d75f);
            if ((D_800E7FFE & 0x8200) || d > 0x640) {
                r = 0;
            } else {
                if (d >= 0x385) {
                    t = D_80135BF8;
                } else if (d >= 0x12D) {
                    t = D_80135C08;
                } else {
                    t = D_80135C18;
                }
                r = t[(func_8009A450() >> 8) & 0xF];
            }
            if (r == 0) {
                r = 1;
            } else {
                r = D_80135C28[func_8009A450() & 0xF];
            }
        }
        break;
    }
    return r;
}

#define FH(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define FU(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define FW(p, o) (*(s32 *)((u8 *)(p) + (o)))
s32 func_801175D0(u8 *a) {
    s32 ret = 0;
    u8 *q = a + 0x60;
    u8 *p;
    s32 r, s, t, y, w, v;

    switch (a[7]) {
    case 0:
        FH(a, 0x52) = 0;
        FH(a, 0x40) = 10;
        FH(a, 0x50) = FH(a, 0x4E);
        a[7]++;
    case 1:
        FH(a, 0x58) += func_80083E80(-FH(a, 0x58)) >> 5;
        a01_turn(a);
        if (--FH(a, 0x40) > 0) {
            break;
        }
        a[7]++;
        break;
    case 2:
        FH(a, 0x50) += (0x280 - FH(a, 0x50)) / 16;
        FH(a, 0x56) += 0x44;
        if ((FH(a, 0x52) -= 0x44) < -0x400) {
            FH(a, 0x52) = -0x400;
            FH(a, 0x40) = 0xF;
            FH(q, 4) += 0x800;
            a[7]++;
        }
        break;
    case 3:
        FH(a, 0x50) += (0xA0 - FH(a, 0x50)) / 16;
        if (--FH(a, 0x40) <= 0) {
            FH(a, 0x40) = 0xF;
            a[7]++;
            if (a[5] == 3) {
                FU(q, 6) &= ~1;
            } else {
                FU(q, 6) |= 1;
            }
        }
        break;
    case 4:
        FH(a, 0x50) += (0xA0 - FH(a, 0x50)) / 16;
        FH(a, 0x56) += 0x44;
        FH(a, 0x52) += 0x44;
        if (--FH(a, 0x40) <= 0) {
            FH(a, 0x40) = 0xF;
            FH(a, 0x52) = 0;
            a[7]++;
        }
        break;
    case 5:
        FH(a, 0x50) += (0xA0 - FH(a, 0x50)) / 16;
        if (--FH(a, 0x40) <= 0) {
            ret = 1;
        }
        break;
    }
    r = FH(a, 0x50);
    s = func_80083E80(FH(a, 0x52)) * r;
    t = func_80083F50(FH(a, 0x52)) * r;
    FW(a, 0x30) += s;
    FH(a, 0x58) = -FH(a, 0x58) >> 4;
    FH(a, 0x4E) = t >> 12;
    y = a01_target_y(a);
    y += func_80083F50(FH(q, 0x10)) >> 5;
    FH(q, 0x10) += func_8009A450() >> 9;
    FH(a, 0x32) += (y - FH(a, 0x32)) / 16;
    return ret;
}

s32 func_80117A00(u8 *a, s16 y) {
    s32 r = 0;
    s32 d;
    u8 *q = a + 0x60;

    switch (a[7]) {
    case 0:
        FH(q, 0x18) = FH(a, 0x32) + (y - FH(a, 0x32)) / 2;
        a[7]++;
    case 1:
        d = func_80083E80(-FH(a, 0x58)) >> 5;
        if (d == 0) {
            if (FH(q, 0x18) < FH(a, 0x32)) {
                a[7] = 2;
            } else {
                a[7] = 3;
            }
        } else {
            FH(a, 0x58) += d;
        }
        break;
    case 2:
        if (FH(a, 0x32) > FH(q, 0x18)) {
            FH(a, 0x58) += func_80083E80(-0x300 - FH(a, 0x58)) >> 5;
        } else {
            a[7] = 4;
        }
        break;
    case 3:
        if (FH(a, 0x32) < FH(q, 0x18)) {
            FH(a, 0x58) += func_80083E80(0x300 - FH(a, 0x58)) >> 5;
        } else {
            a[7] = 4;
        }
        break;
    case 4:
        d = func_80083E80(-FH(a, 0x58)) >> 5;
        if (d != 0) {
            FH(a, 0x58) += d;
        } else {
            r = 1;
        }
        break;
    }
    a01_turn(a);
    return r;
}

typedef struct {
    s16 x, y, z;
} SV3;
/* func_80119AAC, inlined */
static inline void inl_80119AAC(u8 *a) {
    SV3 p;
    SV3 s;

    s.x = (M2C_FIELD(M2C_FIELD(a, u8 **, 0xC4), s16 *, 0x18) * 0x5F) >> 4;
    s.y = (M2C_FIELD(M2C_FIELD(a, u8 **, 0xC4), s16 *, 0x1E) * 0x5F) >> 4;
    s.z = (M2C_FIELD(M2C_FIELD(a, u8 **, 0xC4), s16 *, 0x24) * 0x5F) >> 4;
    p.x = M2C_FIELD(M2C_FIELD(a, u8 **, 0xC4), s16 *, 0x2C);
    p.y = M2C_FIELD(M2C_FIELD(a, u8 **, 0xC4), s16 *, 0x30);
    p.z = M2C_FIELD(M2C_FIELD(a, u8 **, 0xC4), s16 *, 0x34);
    func_80133CAC(0, a, &p, &s);
}
s32 func_80117BCC(u8 *a) {
    s32 ret = 0;
    u8 *q = a + 0x60;
    s32 r, y;

    switch (a[7]) {
    case 0:
        FH(a, 0x40) = FH(q, 4) + 0x400;
        __asm__ volatile("");
        FH(a, 0x42) = 0x28;
        a[7]++;
    case 1:
        FH(a, 0x56) += func_80083E80(FH(a, 0x40) - FH(a, 0x56)) >> 7;
        if (FH(a, 0x42)-- <= 0) {
            FH(a, 0x42) = 0x1E;
            inl_801199DC(a, 9, 4);
            a[7]++;
        }
        break;
    case 2:
        r = func_80083E80(FH(a, 0x40) - FH(a, 0x56));
        if (r < 0) {
            FH(a, 0x56)--;
        } else if (r > 0) {
            FH(a, 0x56)++;
        }
        if (FH(a, 0x42)-- <= 0) {
            FH(a, 0x42) = 0xB4;
            inl_801199DC(a, 0xE, 7);
            func_80074590(0x8A, 7, 0);
            a[7]++;
        }
        break;
    case 3:
        FH(a, 0x58) += func_80083E80(0x1B8 - FH(a, 0x58)) >> 5;
        inl_80119AAC(a);
        if (FH(a, 0x42)-- <= 0) {
            inl_801199DC(a, 8, 0x1E);
            FH(a, 0x42) = 0x3C;
            a[7]++;
        }
        break;
    case 4:
        FH(a, 0x58) += func_80083E80(-FH(a, 0x58)) >> 5;
        a01_turn(a);
        if (FH(a, 0x42)-- <= 0) {
            ret = 1;
        }
        break;
    }
    y = a01_target_y(a);
    y += func_80083F50(FH(q, 0x10)) >> 5;
    FH(q, 0x10) += func_8009A450() >> 9;
    FH(a, 0x32) += (y - FH(a, 0x32)) / 16;
    return ret;
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80118070);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80118F90);

s32 func_80119104(u8 *a) {
    s32 r = 0;

    switch (a[7]) {
    case 0:
        inl_801199DC(a, 9, 10);
        F16(a, 0x42) = 0x2D;
        a[7]++;
    case 1:
        if (F16(a, 0x42)-- <= 0) {
            F16(a, 0x42) = 0x2D;
            inl_801199DC(a, 0xC, 7);
            a[7]++;
        }
        break;
    case 2:
        if (F16(a, 0x42)-- <= 0) {
            r = 1;
        } else if (F16(a, 0x42) < 0x28) {
            inl_80119AAC(a);
        }
        break;
    }
    return r;
}

extern u8 D_800BF8BF;
extern u8 D_800E7FE4;
s16 func_80118F90();
/* func_80119F94, inlined */
static inline s32 inl_80119F94(void) {
    return D_80135C38[func_8009A450() & 0xF];
}
static inline s16 inl_c(u8 *a) {
    if (D_800E7FE4 == 1) {
        switch (a[3]) {
        case 3:
            if ((u16)(D_1F800160_3621 - 0x42CD) < 0x383) {
                return 1;
            }
            return 0;
        case 4:
            if (D_1F800164_d75f < 0x1A90) {
                return 1;
            }
            return 0;
        }
    } else {
        return 0;
    }
}
void func_80119320(u8 *a) {
    u8 *q = a + 0x60;
    s16 c;
    s16 lo, hi;
    s32 r;
    s32 s;
    s32 one = 1;

    switch (a[5]) {
    case 1:
    case 2:
        switch (a[6]) {
        case 0:
            a[7] = 0;
            a[6]++;
        case 1:
            if (func_80118F90(a, 1, 0x3C) != 0) {
                a[5] = inl_80119F94();
                a[6] = 0;
            } else {
                switch (a[5]) {
                case 2:
                    H(a, 0x32) += 6;
                    break;
                case 1:
                    H(a, 0x32) -= 6;
                    break;
                }
            }
            break;
        }
        break;
    case 4:
        switch (a[6]) {
        case 0:
            a[7] = 0;
            a[6]++;
        case 1:
            if ((s16)func_80119104(a) != 0) {
                a[7] = 0;
                a[6]++;
            }
            break;
        case 2:
            if (func_80118F90(a, 8, 0x5A) != 0) {
                a[7] = 0;
                a[6]++;
            }
            break;
        case 3:
            if (func_80118F90(a, 7, 0x78) != 0) {
                a[5] = inl_80119F94();
                a[6] = 0;
            }
            break;
        }
        break;
    case 3:
        switch (a[6]) {
        case 0:
            a[7] = 0;
            a[6]++;
        case 1:
            if (func_80118F90(a, 5, 0x96) != 0) {
                a[7] = 0;
                a[6]++;
            }
            break;
        case 2:
            if (func_80118F90(a, 7, 0x3C) != 0) {
                a[5] = inl_80119F94();
                a[6] = 0;
            }
            break;
        }
        break;
    case 0:
        a[5] = inl_80119F94();
        a[6] = 0;
        break;
    default:
        a[5] = 0;
        a[6] = 0;
        break;
    }
    switch (a[3]) {
    case 3:
        hi = -0x1401;
        break;
    case 4:
        hi = -0x1280;
        break;
    }
    if (H(a, 0x32) >= hi) {
        s = 1;
        if (a[5] != s) {
            a[5] = s;
            a[6] = 0;
            r = s;
        } else {
            r = 0;
        }
    } else {
        switch (a[3]) {
        case 3:
            lo = -0x18FA;
            break;
        case 4:
            lo = -0x1B58;
            if (D_800BF8BF == 0xFF) {
                lo = -0x1280;
            }
            break;
        }
        if (H(a, 0x32) < lo && a[5] != 2) {
            a[5] = 2;
            a[6] = 0;
            r = one;
        } else {
            r = 0;
        }
    }
    if (r == 0) {
        if (a[5] != 4) {
            if (inl_c(a) != 0) {
                if (++H(q, 0x12) < 0x3D) {
                    goto move;
                }
                if (func_8009A450() < 0xA000) {
                    a[5] = 4;
                    a[6] = 0;
                }
            }
        }
        H(q, 0x12) = 0;
    }
move:
    H(a, 0x32) += func_80083F50(H(q, 0x10)) >> 9;
    H(q, 0x10) += func_8009A450() >> 11;
    H(a, 0x2E) = H(q, 0x14) + (func_80083F50(H(q, 0x10)) >> 8);
    H(a, 0x36) = H(q, 0x16) + (func_80083E80(H(q, 0x10)) >> 8);
}

extern u8 D_800BF809;
extern u8 D_800BF9F0;
void func_80119778(u8 *a)
{
    u8 *b = a + 0x60;
    s32 r;
    s32 k;
    u8 *p;

    switch (a[4]) {
    case 0:
        func_8011638C(a);
        a[4] = 1;
        a[5] = 0;
    case 1:
        if (D_1F800137 != 0 || D_800BF809 != 0) {
            if (func_80116294(a) != 0) {
                break;
            }
            if (func_800777FC(a) == 0) {
                if (a[3] != 3 || !(D_800BF9F0 & 2)) {
                    break;
                }
                a[1] = 1;
                func_80077E7C(a);
            }
            func_800518FC(a);
            break;
        }
        if (a[0x2B] != 0) {
            a[0x2B]--;
            if (D_1F80017C & 1) {
                M2C_FIELD(a, s16 *, 0x56) += 0x80;
            } else {
                M2C_FIELD(a, s16 *, 0x56) -= 0x80;
            }
            if (func_800777FC(a) != 0) {
                func_800518FC(a);
            }
            break;
        }
        if (a[3] == 1 && M2C_FIELD(a, s16 *, 0x32) < -0x16A8) {
            M2C_FIELD(a, s16 *, 0x32) = -0x16A8;
        }
        if (func_80116294(a) == 0) {
            r = func_8007778C(a);
            k = a[3];
            if (k < 5) if (k >= 3) {
                func_80119320(a);
                goto done;
            }
            func_80118070(a);
        done:
            if (r != 0) {
                func_80076D68(a);
            }
            func_800518FC(a);
        }
        a[0x29] = 0;
        b[0xB] = 0;
        break;
    case 2:
        func_80116994(a);
        if (a[5] != 4) {
            func_80076D68(a);
        }
        break;
    case 3:
        a[0] = 2;
        if (a[0x1B] & 0x40) {
            do {
                a[0x1B] &= ~0x40;
            } while (0);
            break;
        }
        p = M2C_FIELD(a, u8 **, 0x10);
        if (p != NULL) {
            p[4] = 3;
        }
        func_8007A624(a);
        break;
    }
}

void func_801199DC(u8 *a, s32 k, s32 f) {
    u8 *b;
    s32 *t;
    s32 s;

    if (a[0x46] != k) {
        a[0x46] = k;
        b = D_800ECFC4;
        t = (s32 *)(b + 4);
        switch (k) {
        case 5:
            s = 0x13;
            break;
        case 0xD:
        case 0xF:
        case 0x11:
            s = 0x12;
            break;
        default:
            s = 1;
            break;
        }
        M2C_FIELD(M2C_FIELD(a, u8 **, 0xC4), u8 **, 0x40) = b + t[s];
        if (!(f & 0xFF)) {
            func_80077C40(a, D_80139B24, k);
        } else {
            func_80077CFC(a, D_80139B24, k, (u8)f);
        }
    }
}

void func_80119AAC(u8 *a) {
    SV3 p;
    SV3 s;

    s.x = (M2C_FIELD(M2C_FIELD(a, u8 **, 0xC4), s16 *, 0x18) * 0x5F) >> 4;
    s.y = (M2C_FIELD(M2C_FIELD(a, u8 **, 0xC4), s16 *, 0x1E) * 0x5F) >> 4;
    s.z = (M2C_FIELD(M2C_FIELD(a, u8 **, 0xC4), s16 *, 0x24) * 0x5F) >> 4;
    p.x = M2C_FIELD(M2C_FIELD(a, u8 **, 0xC4), s16 *, 0x2C);
    p.y = M2C_FIELD(M2C_FIELD(a, u8 **, 0xC4), s16 *, 0x30);
    p.z = M2C_FIELD(M2C_FIELD(a, u8 **, 0xC4), s16 *, 0x34);
    func_80133CAC(0, a, &p, &s);
}

extern s8 D_1F800160[];
extern s8 D_1F800164[];
s32 func_80119B80(s32 arg0, s32 arg1) {
    return (u32) (((arg1 - func_800782B0(arg0 + 0x2C, *((s16 *)D_1F800160), *((s16 *)D_1F800164))) + 0x400) & 0xFFF) >= 0x801U;
}

s32 func_80119BCC(u8 *a) {
    u8 *q = a + 0x60;
    s32 h = M2C_FIELD(q, u16 *, 4);
    s8 r;

    r = (u32)((h - func_800782B0(a + 0x2C, D_1F800160_71b4, D_1F800164_d75f) + 0x400) & 0xFFF) > 0x800;
    if (r) {
        M2C_FIELD(q, u16 *, 6) |= 1;
    } else {
        M2C_FIELD(q, u16 *, 6) &= 0xFFFE;
    }
    return r;
}

s32 func_80119C4C(u8 *a) {
    u8 *q = a + 0x60;
    s32 h = M2C_FIELD(q, u16 *, 4);
    s8 r;

    r = (u32)((h - func_800782B0(a + 0x2C, D_1F800160_71b4, D_1F800164_d75f) + 0x400) & 0xFFF) > 0x800;
    if (M2C_FIELD(q, u16 *, 6) & 1) {
        if (!r) return 1;
    } else {
        if (r) return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80119CD4);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80119D84);

s32 func_80119E28(void) {
    return D_80135BE8[(func_8009A450() >> 8) & 0xF];
}

s32 func_80119E60(u8 *a) {
    s32 d = func_800781E0(M2C_FIELD(a, s16 *, 0x2E) - D_1F800160_71b4, M2C_FIELD(a, s16 *, 0x36) - D_1F800164_d75f);
    u8 *t;

    if (D_800E7FFE & 0x8200) {
        return 0;
    }
    if (d > 0x640) {
        return 0;
    }
    if (d >= 0x385) {
        t = D_80135BF8;
    } else if (d >= 0x12D) {
        t = D_80135C08;
    } else {
        t = D_80135C18;
    }
    return t[(func_8009A450() >> 8) & 0xF];
}

void func_80119F10(u8 *a) {
    u8 *q = a + 0x60;

    func_80116620(a);
    func_8004766C(a);
    func_80049760(a);
    M2C_FIELD(q, s16 *, 4) = D_1F8001A0;
    if (func_800493E8(a, 0, -0x5A) != 0 || func_80049250(a, 0, 0x5A) != 0) {
        a[5] = 0;
        a[6] = 0;
    }
    a[0x29] = 0;
}

s32 func_80119F94(void) {
    return D_80135C38[func_8009A450() & 0xF];
}

s32 func_80119FC8(u8 *a) {
    switch (a[3]) {
    case 3:
        return -0x1401;
    case 4:
        return -0x1280;
    }
}

s32 func_80119FF8(u8 *a) {
    switch (a[3]) {
    case 3:
        return -0x18FA;
    case 4:
        if (D_800BF8BF == 0xFF) {
            return -0x1280;
        }
        return -0x1B58;
    }
}

extern u16 D_1F800162;
s32 func_8011A03C(u8 *a) {
    if (D_800E7FE4 != 1) {
        return 0;
    }
    switch (a[3]) {
    case 3:
        return (u16)(D_1F800160_3621 - 0x42CD) < 0x383;
    case 4:
        return D_1F800164_d75f < 0x1A90;
    }
}

s32 func_8011A0A0(u8 *a, s16 lo, s16 hi) {
    s32 s;

    switch (a[3]) {
    case 3:
        hi = -0x1401;
        break;
    case 4:
        hi = -0x1280;
        break;
    }
    if (M2C_FIELD(a, s16 *, 0x32) >= hi) {
        s = 1;
        if (a[5] != s) {
            a[5] = s;
            a[6] = 0;
            return 1;
        }
    } else {
        switch (a[3]) {
        case 3:
            lo = -0x18FA;
            break;
        case 4:
            lo = -0x1B58;
            if (D_800BF8BF == 0xFF) {
                lo = -0x1280;
            }
            break;
        }
        if (M2C_FIELD(a, s16 *, 0x32) < lo) {
            s = 2;
            if (a[5] != s) {
                a[5] = s;
                a[6] = 0;
                return 1;
            }
        }
    }
    return 0;
}

extern u8 D_800BF9EB;
extern M2C_UNK D_80135D20;
void func_8011A168(void *arg0) {
    u8 temp_s1;
    void *temp_v0;

    temp_s1 = M2C_FIELD(arg0, u8 *, 5);
    switch (temp_s1) {                              /* irregular */
    case 0:
        if (M2C_FIELD(arg0, u8 *, 0x70) == 0xFF) {
            M2C_FIELD(arg0, u8 *, 5) = 1U;
        }
        break;
    case 1:
        temp_v0 = M2C_FIELD(arg0, void **, 0x14);
        M2C_FIELD(arg0, s16 *, 0x56) = (s16) (func_80085690(M2C_FIELD(arg0, s16 *, 0x36) - M2C_FIELD(temp_v0, s16 *, 0x36), M2C_FIELD(temp_v0, s16 *, 0x2E) - M2C_FIELD(arg0, s16 *, 0x2E)) & 0xFFF);
        if (D_800BF9EB == temp_s1) {
            func_80040D68(arg0, &D_80135D20);
            M2C_FIELD(arg0, u8 *, 0x70) = 2U;
            M2C_FIELD(arg0, u8 *, 5) = (u8) (M2C_FIELD(arg0, u8 *, 5) + 1);
        }
        break;
    case 2:
        if (M2C_FIELD(arg0, u8 *, 0x70) == 0xFF) {
            M2C_FIELD(arg0, s8 *, 4) = 3;
        }
        break;
    }
    M2C_FIELD(arg0, s8 *, 1) = 1;
    func_80077E7C(arg0);
    func_80041098(arg0);
    func_8004190C(arg0);
}

extern s32 D_800ECF58_a4fb[];
extern u8 D_801356AC[];
extern u8 D_801393C0_27b3[];
extern u8 D_800A3D18[];
extern u8 D_80135C48[];
void func_8011A27C(u8 *a)
{
    switch (a[4]) {
    case 0:
        if (func_800519E0(a, 0xF, D_800ECF58_a4fb[0x3C / 4], D_801356AC) != 0) {
            break;
        }
        M2C_FIELD(a, s32 *, 0x3C) = D_800ECF58_a4fb[0x38 / 4];
        func_80040CDC(a, D_801393C0_27b3, D_800A3D18);
        func_80041718(a, 0x14, 0);
        a[0x7B] = 0x14;
        a[0xB] = 0x40;
        a[0] = 9;
        M2C_FIELD(a, s16 *, 0x80) = 0xAA;
        M2C_FIELD(a, s16 *, 0x82) = 0x154;
        M2C_FIELD(a, s16 *, 0x84) = 0x80;
        M2C_FIELD(a, s16 *, 0x86) = 0xF0;
        a[0x2B] = 0;
        a[0x29] = 0;
        M2C_FIELD(a, s16 *, 0x58) = 0;
        M2C_FIELD(a, s16 *, 0x56) = 0;
        M2C_FIELD(a, s16 *, 0x54) = 0;
        if (a[3] == 0) {
            M2C_FIELD(a, s32 *, 0x2C) = 0x30400000;
            M2C_FIELD(a, s32 *, 0x30) = 0xEF520000;
            M2C_FIELD(a, s32 *, 0x34) = 0x39C30000;
            M2C_FIELD(a, s16 *, 0x56) = 0xC00;
            func_800416A8(a, -1, 0);
            func_80041718(a, 8, 0);
            func_80040D68(a, D_80135C48);
            a[0x70] = 2;
        }
        a[4]++;
        break;
    case 1:
        if (a[3] == 0) {
            func_8011A168(a);
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

u8 *func_8011A43C(s32 a, s32 b) {
    u8 *p = func_8007A980(3, 9, 0);

    if (p == NULL) {
        return NULL;
    }
    p[0x2] = 1;
    p[0x3] = b;
    M2C_FIELD(p, void **, 0x1C) = func_8011A27C;
    M2C_FIELD(p, s32 *, 0x14) = a;
    p[0x28] = (p[0x28] | 0x80);
    return p;
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8011A4AC);

extern u8 D_80135A0C[];
extern u8 D_8013995C[];
extern u8 D_80135D88[];
extern u8 D_80135F24[];
static inline s32 inl_run1(u8 *a)
{
    switch (a[6]) {
    case 0:
        if (a[0x2B] == 3) {
            a[6] = 1;
            func_80042354(1, 1);
        }
        break;
    case 1:
        a[6] = 2;
        func_80040CDC(a, D_8013995C, D_80135D88);
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
static inline s32 inl_run2(u8 *a)
{
    switch (a[6]) {
    case 0:
        if (a[0x2B] == 3) {
            a[6] = 1;
            func_80042354(1, 1);
        }
        break;
    case 1:
        a[6] = 2;
        func_80040CDC(a, D_8013995C, D_80135F24);
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
void f_UpdateKainenActor(u8 *a)
{
    s32 *t;

    switch (a[4]) {
    case 0:
        if (D_800BF873 != 0) {
            if (func_800519E0(a, 0xD, D_800ECF58_a4fb[0x8C / 4], D_80135A0C) != 0) {
                break;
            }
            M2C_FIELD(a, s32 *, 0x3C) = D_800ECF58_a4fb[0x88 / 4];
            func_80077C40(a, D_8013995C, 6);
            a[0] = 2;
        } else {
            if (func_800519E0(a, 0xD, D_800ECF58_a4fb[0x84 / 4], D_80135A0C) != 0) {
                break;
            }
            M2C_FIELD(a, s32 *, 0x3C) = D_800ECF58_a4fb[0x88 / 4];
            func_80077C40(a, D_8013995C, 0);
            a[0] = 9;
        }
        M2C_FIELD(a, s16 *, 0x80) = 0x96;
        M2C_FIELD(a, s16 *, 0x82) = 0x12C;
        M2C_FIELD(a, s16 *, 0x84) = 0x80;
        M2C_FIELD(a, s16 *, 0x86) = 0x100;
        M2C_FIELD(a, s16 *, 0x56) = 0x530;
        M2C_FIELD(a, s16 *, 0x54) = 0;
        M2C_FIELD(a, s16 *, 0x58) = 0;
        a[0x2B] = 0;
        a[0x29] = 0;
        a[4]++;
        if (D_800BF870.pad1[0x74] != 0xFF) {
            a[5] = 0;
        } else if (D_800BF870.pad1[0x1CD] < 3) {
            a[5] = 1;
        } else if (D_800BF870.pad1[2] != 0) {
            a[5] = 3;
        } else {
            a[5] = 2;
        }
        break;
    case 1:
        switch (a[5]) {
        case 0:
            if (inl_run1(a)) {
                a[5]++;
            }
            break;
        case 1:
            if (inl_run2(a)) {
                a[5]++;
            }
            break;
        case 2:
            func_8011A4AC(a);
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

s32 func_8011A984(s32 a0) {
    u8 *p = func_80072DDC(a0, 1, 3, 0x10);

    if (p != NULL) {
        M2C_FIELD(p, void **, 0x1C) = f_UpdatePipeAreaScenePropActor;
        p[3] = 8;
    }
    return 1;
}

s32 func_8011A9C8(u8 *p) {
    switch (p[6]) {
    case 0:
        if (p[0x2B] == 3) {
            p[6] = 1;
            func_80042354(1, 1);
        }
        break;
    case 1:
        p[6] = 2;
        func_80040CDC(p, D_8013995C, D_80135D88);
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

s32 func_8011AAA4(u8 *p) {
    switch (p[6]) {
    case 0:
        if (p[0x2B] == 3) {
            p[6] = 1;
            func_80042354(1, 1);
        }
        break;
    case 1:
        p[6] = 2;
        func_80040CDC(p, D_8013995C, D_80135F24);
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

extern u8 D_800A3CF0[];
extern u8 D_801360FC[];
extern u8 D_800ECF58_742e[];
extern u8 D_8001B4DC[];
extern u8 D_80136084[];
/* func_8011ADA0, inlined */
static inline void inl_8011ADA0(u8 *a) {
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
                a[0x7A] = 0;
                func_80040D68(a, D_801360FC);
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
void func_8011AB80(u8 *a) {
    u8 *g;

    switch (a[4]) {
    case 0:
        g = D_800ECF58_742e;
        if (func_800519E0(a, 0xF, M2C_FIELD(g, s32 *, 0x3C), D_80136084) == 0) {
            M2C_FIELD(a, s32 *, 0x3C) = M2C_FIELD(g, s32 *, 0x74);
            func_80040CDC(a, D_8001B4DC, D_800A3D18);
            a[0x7B] = 5;
            func_80041718(a, 5, 0);
            M2C_FIELD(a, s16 *, 0xB8) = 0x800;
            M2C_FIELD(a, s16 *, 0xBA) = 0x800;
            M2C_FIELD(a, s16 *, 0xBC) = 0x800;
            M2C_FIELD(a, s16 *, 0x56) = 0x400;
            a[0] = 9;
            M2C_FIELD(a, s16 *, 0x80) = 0x5A;
            M2C_FIELD(a, s16 *, 0x82) = 0xB4;
            M2C_FIELD(a, s16 *, 0x84) = 0x50;
            M2C_FIELD(a, s16 *, 0x54) = 0;
            M2C_FIELD(a, s16 *, 0x58) = 0;
            M2C_FIELD(a, s16 *, 0x86) = 0x90;
            a[0x2B] = 0;
            a[4]++;
        }
        break;
    case 1:
        inl_8011ADA0(a);
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

void func_8011ADA0(u8 *a) {
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
                a[0x7A] = 0;
                func_80040D68(a, D_801360FC);
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

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8011AE9C);

void func_8011AFF0(u8 *a) {
    u8 *e;
    s32 v;

    switch (a[7]) {
    case 0:
        e = D_800E7E80;
        if ((u8)(a[0xBE] = func_80077768((s16)func_80085690(-(s16)(FU16(e, 0x36) - FU16(a, 0x36)), (s16)(FU16(e, 0x2E) - FU16(a, 0x2E))), F16(a, 0x60), 0)) != a[0x46]) {
            a[7]++;
            F16(a, 0x96) = (FU16(a, 0x56) + 0x800) & 0xFFF;
            if (a[0x46] == 0) {
                F16(a, 0x92) = 0x80;
            } else {
                F16(a, 0x92) = -0x80;
            }
        }
        break;
    case 1:
        v = (FU16(a, 0x56) + FU16(a, 0x92)) & 0xFFF;
        F16(a, 0x56) = v;
        if (v == F16(a, 0x96)) {
            a[7] = 0;
            a[0x46] = a[0xBE];
        }
        break;
    }
    func_8011AE9C(a);
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8011B100);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8011B268);

extern s16 D_800E7FEE;
/* func_8011C290, inlined */
static inline void inl_8011C290(u8 *a) {
    GameState *g;

    if (D_800E7FEE != 0) {
        g = &D_800BF870;
        g->pad1[0x183] |= 1 << a[3];
        g->pad1[0x184]++;
        if (g->pad1[0x4D] != 0xFF && g->pad1[0x184] == 8) {
            func_80040C00(10);
            g->pad1[0x188] = 1;
        }
    }
}
void func_8011B3EC(u8 *a) {
    u8 *p;

    switch (a[6]) {
    case 2:
        do {
            func_80051B04(M2C_FIELD(a, s32 *, 0xC0), 0xC, 0x2C);
        } while (0);
        M2C_FIELD(a, u8 **, 0x14)[0x5E] = 1;
        M2C_FIELD(M2C_FIELD(a, u8 **, 0x14), s32 *, 0x14) = func_80133574(0, a[3]);
        func_80074590(0x92, 0, 0);
        func_80074590(0x80, 0, 0);
        if (a[3] == 6) {
            p = M2C_FIELD(a, u8 **, 0x3C);
            if (p != NULL) {
                p[5]++;
                D_800BF870.pad1[0x18B] |= 0x20;
            }
        }
    case 0:
        a[6]++;
        break;
    case 4:
        inl_8011C290(a);
        a[4] = 3;
        break;
    case 1:
    case 3:
        break;
    }
    if (func_800778E4(a, (s16)(D_1F800162_a8d4 - M2C_FIELD(a, u16 *, 0x32))) != 0) {
        func_800517F8(a);
    }
}

void func_8011B594(u8 *a) {
    GameState *g;
    s16 t;

    if (func_8007778C(a) != 0) {
        func_800517F8(a);
    }
    switch (a[6]) {
    case 0:
        if (D_800E7FEE != 0) {
            g = &D_800BF870;
            g->pad1[0x183] |= 1 << a[3];
            g->pad1[0x184]++;
            if (g->pad1[0x4D] != 0xFF && g->pad1[0x184] == 8) {
                func_80040C00(10);
                g->pad1[0x188] = 1;
            }
        }
        M2C_FIELD(a, s16 *, 0x4A) = -0x20;
        a[6]++;
    case 1:
        if (a[1] == 0) {
            a[4] = 3;
            break;
        }
        t = M2C_FIELD(a, s16 *, 0x4A);
        M2C_FIELD(a, s16 *, 0x58) += 0x100;
        M2C_FIELD(a, s16 *, 0x32) += t;
        M2C_FIELD(a, s16 *, 0x4A) += 3;
        break;
    }
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8011B6B0);

#define W(p, o) (*(s32 *)((u8 *)(p) + (o)))
u8 *func_80072DDC();
void func_8012AC84(u8 *a);
/* func_8011C06C, inlined */
static inline void inl_8011C06C(u8 *a) {
    extern void func_8011BED0();
    u8 *p = func_80072DDC((s32)a, 0, 3, 0x13);

    if (p != NULL) {
        M2C_FIELD(p, void **, 0x1C) = func_8011BED0;
        p[3] = 0;
        M2C_FIELD(p, s16 *, 0x60) = a[3];
        M2C_FIELD(p, s16 *, 0x2E) = M2C_FIELD(a, s16 *, 0x2E);
        M2C_FIELD(p, s16 *, 0x32) = M2C_FIELD(a, s16 *, 0x32);
        M2C_FIELD(p, s16 *, 0x36) = M2C_FIELD(a, s16 *, 0x36);
        p[0x5E] = 0;
        M2C_FIELD(a, u8 **, 0x14) = p;
    }
}
static inline void capper_size(u8 *a) {
    switch (a[0x5E]) {
    case 0:
        if (a[3] == 1) {
            H(a, 0x84) = 0x320;
        } else {
            H(a, 0x84) = 0xA0;
        }
        break;
    case 1:
        H(a, 0x84) = 0x78;
        break;
    }
    H(a, 0x86) = H(a, 0x84);
}
void f_UpdateCapperActor(u8 *a)
{
    GameState *g;
    u8 *p;
    s32 r;

    switch (a[4]) {
    case 0:
        if (D_800BF873 != 0) {
            a[4] = 3;
            break;
        }
        if (D_800BF816 != 0) {
            break;
        }
        H(a, 0x80) = 0x6E;
        H(a, 0x82) = 0xDC;
        capper_size(a);
        func_80041194(a, H(a, 0x86) - H(a, 0x84), 1, 0);
        W(a, 0x10) = 0;
        W(a, 0x14) = 0;
        W(a, 0x3C) = 0;
        inl_8011C06C(a);
        g = &D_800BF870;
        if ((g->pad1[0x183] >> a[3]) & 1) {
            p = (u8 *)func_80133574(0, a[3]);
            r = (s32)p;
            if (W(a, 0x14) != 0) {
                W(W(a, 0x14), 0x14) = r;
            }
            a[4] = 3;
            break;
        }
        if (a[3] == 6 && !(g->pad1[0x18B] & 0x20)) {
            p = func_80072DDC(a, 1, 4, 0x1C);
            if (p != NULL) {
                *(void **)(p + 0x1C) = func_8012AC84;
                *(u8 **)(a + 0x3C) = p;
            }
        }
        if (a[5] == 2) {
            if (func_80051B70(a, 0xC, 0x26) != 0) {
                break;
            }
            a[0x5E] = 1;
        } else {
            if (func_80051B70(a, 0xC, 0xD) != 0) {
                break;
            }
            a[0x5E] = 0;
        }
        a[0] = 1;
        H(a, 0xBC) = 0x1000;
        H(a, 0xBA) = 0x1000;
        H(a, 0xB8) = 0x1000;
        a[4]++;
        a[0xD] = 0;
        a[0x29] = 0;
        a[0x2B] = 0;
        H(*(u8 **)(a + 0xC0), 0xA) = -0x400;
        func_8004130C(a, 1);
        a[0x46] = a[0xBE];
        break;
    case 1:
        switch (a[5]) {
        case 0:
            func_8011B100(a);
            break;
        case 1:
            switch (a[6]) {
            case 0:
                a[6] = 1;
                H(a, 0x40) = 0x78;
            case 1:
                if (--H(a, 0x40) == 0) {
                    a[5] = 0;
                    a[6] = 0;
                    a[0x5E] = 0;
                }
            }
            func_8011AFF0(a);
            if (func_800778E4(a, (s16)(D_1F800162 - *(u16 *)(a + 0x32))) != 0) {
                func_800517F8(a);
            }
            break;
        case 2:
            switch (a[6]) {
            case 0:
                a[6] = 1;
                H(a, 0x40) = 0x78;
            case 1:
                if (--H(a, 0x40) == 0) {
                    a[5] = 0;
                    a[6] = 0;
                    a[0x5E] = 0;
                }
            }
            func_8011AFF0(a);
            if (func_800778E4(a, (s16)(D_1F800162 - *(u16 *)(a + 0x32))) != 0) {
                func_800517F8(a);
            }
            break;
        }
        capper_size(a);
        a[0x29] = 0;
        a[0x2B] = 0;
        break;
    case 2:
        switch (a[5]) {
        case 0:
        case 6:
            func_8011B268(a);
            break;
        case 1:
            func_8011B3EC(a);
            break;
        case 2:
            func_8011B594(a);
            break;
        case 3:
            a[0] = 1;
            a[4] = 1;
            a[5] = 1;
            a[6] = 0;
            if (func_800778E4(a, (s16)(D_1F800162 - *(u16 *)(a + 0x32))) != 0) {
                func_800517F8(a);
            }
            break;
        case 4:
            func_8011B6B0(a);
            break;
        case 5:
            break;
        }
        capper_size(a);
        a[0x29] = 0;
        a[0x2B] = 0;
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

void f_UpdateCapperActor();
void func_8011BDC4(u8 *a) {
    s32 k;
    u8 *e;

    if (a[0x5E] == 0) {
        a[4] = 1;
        a[5] = 0;
        return;
    }
    k = a[5];
    switch (k) {
    case 0:
        break;
    case 1:
        e = func_80072DDC(a, 1, 2, 0x10);
        if (e != NULL) {
            a[0x5E] = 0;
            FP(e, 0x1C) = (u8 *)f_UpdateCapperActor;
            e[3] = a[0x60];
            F16(e, 0x2E) = FU16(a, 0x2E);
            F16(e, 0x32) = FU16(a, 0x32) - 0x64;
            F16(e, 0x36) = FU16(a, 0x36);
            e[5] = 2;
            D_800BF870.pad1[0x183] &= ~(k << F16(a, 0x60));
            D_800BF870.pad1[0x184]--;
            a[4] = 3;
            if (FP(a, 0x14) != NULL) {
                FP(a, 0x14)[4] = 2;
                FP(a, 0x14)[5] = 0x80;
                FP(a, 0x14)[6] = 0;
            }
        }
        break;
    }
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8011BED0);

void func_8011BED0();
void func_8011C06C(u8 *a) {
    u8 *p = func_80072DDC((s32)a, 0, 3, 0x13);

    if (p != NULL) {
        M2C_FIELD(p, void **, 0x1C) = func_8011BED0;
        p[3] = 0;
        M2C_FIELD(p, s16 *, 0x60) = a[3];
        M2C_FIELD(p, s16 *, 0x2E) = M2C_FIELD(a, s16 *, 0x2E);
        M2C_FIELD(p, s16 *, 0x32) = M2C_FIELD(a, s16 *, 0x32);
        M2C_FIELD(p, s16 *, 0x36) = M2C_FIELD(a, s16 *, 0x36);
        p[0x5E] = 0;
        M2C_FIELD(a, u8 **, 0x14) = p;
    }
}

void func_8011C0E8(u8 *a) {
    u8 *g = D_800E7E80;
    s16 dz = M2C_FIELD(g, s16 *, 0x36) - M2C_FIELD(a, s16 *, 0x36);
    s16 dx = M2C_FIELD(g, s16 *, 0x2E) - M2C_FIELD(a, s16 *, 0x2E);

    a[0xBE] = func_80077768((s16)func_80085690(-dz, dx), M2C_FIELD(a, s16 *, 0x60), 0);
}

void func_8011C158(u8 *a) {
    switch (a[0x5E]) {
    case 0:
        if (a[3] == 1) {
            M2C_FIELD(a, s16 *, 0x84) = 0x320;
        } else {
            M2C_FIELD(a, s16 *, 0x84) = 0xA0;
        }
        break;
    case 1:
        M2C_FIELD(a, s16 *, 0x84) = 0x78;
        break;
    }
    M2C_FIELD(a, s16 *, 0x86) = M2C_FIELD(a, s16 *, 0x84);
}

void func_8011C19C(u8 *a) {
    u8 *e;

    if (M2C_FIELD(a, u8 **, 0x10) != NULL) {
        return;
    }
    if (a[3] == 1) {
        e = func_8003116C(0x202, 0, 0);
        if (e != NULL) {
            M2C_FIELD(e, u8 **, 0x10) = a;
            M2C_FIELD(a, u8 **, 0x10) = e;
            M2C_FIELD(e, s16 *, 0x2C) = M2C_FIELD(a, s16 *, 0x2E);
            M2C_FIELD(e, s16 *, 0x2E) = M2C_FIELD(a, s16 *, 0x32) - 0x30;
            M2C_FIELD(e, s16 *, 0x30) = M2C_FIELD(a, s16 *, 0x36);
            e[7] = 1;
        }
    } else {
        e = func_8003116C(0x201, 0, 0);
        if (e != NULL) {
            M2C_FIELD(e, u8 **, 0x10) = a;
            M2C_FIELD(a, u8 **, 0x10) = e;
            M2C_FIELD(e, s16 *, 0x2C) = M2C_FIELD(a, s16 *, 0x2E);
            M2C_FIELD(e, s16 *, 0x2E) = M2C_FIELD(a, s16 *, 0x32) - 0x30;
            M2C_FIELD(e, s16 *, 0x30) = M2C_FIELD(a, s16 *, 0x36);
            e[7] = 0;
        }
    }
}

void func_8011C270(s32 arg0)
{
  void *temp_v1;
  temp_v1 = *((void **) (((signed char *) arg0) + 0x10));
  if (temp_v1)
  {
  }
  if (temp_v1 != 0)
  {
    *((s8 *) (((signed char *) temp_v1) + 4)) = 3;
    *((void **) (((signed char *) arg0) + 0x10)) = 0;
  }
  return 3;
}

void func_8011C290(u8 *a) {
    GameState *g;

    if (D_800E7FEE != 0) {
        g = &D_800BF870;
        g->pad1[0x183] |= 1 << a[3];
        g->pad1[0x184]++;
        if (g->pad1[0x4D] != 0xFF && g->pad1[0x184] == 8) {
            func_80040C00(10);
            g->pad1[0x188] = 1;
        }
    }
}

void func_8011C314(u8 *a) {
    switch (a[6]) {
    case 0:
        a[6]++;
        M2C_FIELD(a, s16 *, 0x40) = 0x78;
    case 1:
        if (--M2C_FIELD(a, s16 *, 0x40) == 0) {
            a[5] = 0;
            a[6] = 0;
            a[0x5E] = 0;
        }
        break;
    }
    func_8011AFF0(a);
    if (func_800778E4(a, (s16)(D_1F800162 - M2C_FIELD(a, u16 *, 0x32))) != 0) {
        func_800517F8(a);
    }
}

void func_8011C3C0(u8 *a) {
    switch (a[6]) {
    case 0:
        a[6]++;
        M2C_FIELD(a, s16 *, 0x40) = 0x78;
    case 1:
        if (--M2C_FIELD(a, s16 *, 0x40) == 0) {
            a[5] = 0;
            a[6] = 0;
            a[0x5E] = 0;
        }
        break;
    }
    func_8011AFF0(a);
    if (func_800778E4(a, (s16)(D_1F800162 - M2C_FIELD(a, u16 *, 0x32))) != 0) {
        func_800517F8(a);
    }
}

void func_8011C46C(u8 *a) {
    a[0] = 1;
    a[4] = 1;
    a[5] = 1;
    a[6] = 0;
    if (func_800778E4(a, (s16)(D_1F800162 - M2C_FIELD(a, u16 *, 0x32))) != 0) {
        func_800517F8(a);
    }
}

void func_8011C6E4();
s16 func_8011DF24();
s32 func_8011D2C4();
void func_8011C854();
void func_8011C998();
void f_UpdateAnemoneCaptureSequence();
void func_8011D8C8();
void func_8011D754();
void func_8011E040();
void func_8011DCE0();
void func_8011D104();
void func_8011C4D0(u8 *a) {
    switch (a[4]) {
    case 0:
        func_8011C6E4(a);
        break;
    case 1:
        func_8007778C(a);
        M2C_FIELD(a, s16 *, 0x6A) = func_8011DF24(a, 3);
        if (!(a[3] & 0x80)) {
            if (!(a[0x5E] & 2) && (s16)func_8011D2C4(a) != 0) {
                a[0x5E] = 2;
                a[5] = 2;
                a[6] = 0;
            }
            switch (a[5]) {
            case 0:
                func_8011C854(a);
                break;
            case 1:
                func_8011C998(a);
                break;
            case 2:
                f_UpdateAnemoneCaptureSequence(a);
                break;
            }
        }
        if (a[1] != 0) {
            func_8011D8C8(a);
            if (M2C_FIELD(a, s16 *, 0x72) != 0) {
                func_8011D754(a);
            }
        }
        break;
    case 2:
        func_8007778C(a);
        switch (a[5]) {
        case 4:
            func_8011E040(a);
            break;
        case 0:
        case 5:
        case 6:
            M2C_FIELD(a, s16 *, 0x6A) = func_8011DF24(a, 3);
            break;
        case 1:
            M2C_FIELD(a, s16 *, 0x6A) = func_8011DF24(a, 3);
            func_8011DCE0(a);
            break;
        case 2:
            func_8011D104(a);
            break;
        case 3:
            break;
        }
        if (a[1] != 0) {
            func_8011D8C8(a);
        }
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8011C6E4);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8011C854);

#define QH(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define QU(p, o) (*(u16 *)((u8 *)(p) + (o)))
void func_8011C998(u8 *a) {
    SV3 v;
    SV3 w;
    s32 r;
    s16 s;
    s32 k, k3, r1;
    u8 *q;

    switch (a[6]) {
    case 0:
        r = func_8009A450() & 0xF;
        if (r < 4) {
            QH(a, 0x40) = 0x3C;
        } else if (r < 0xB) {
            QH(a, 0x40) = 0x5A;
        } else {
            QH(a, 0x40) = 0x96;
        }
        QH(a, 0x42) = 0xA;
        QH(a, 0x70) = QH(a, 0x40);
        func_80074590(0x89, 0, 0);
        func_80074590(0x8A, 0, 0);
        a[6]++;
        break;
    case 1:
        func_8011CF9C(a, 0);
        if (--QH(a, 0x42) == 0) {
            v.x = QH(*(u8 **)(a + 0xCC), 0x2C) + QH(a, 0x60) * 2;
            v.y = QH(*(u8 **)(a + 0xCC), 0x30) + QH(a, 0x62) * 2;
            v.z = QH(*(u8 **)(a + 0xCC), 0x34) + QH(a, 0x64) * 2;
            k = QU(a, 0x6C) << 9;
            r1 = func_8009A450() & 0x3F;
            k -= 0x1F;
            s = k + r1;
            w.y = -func_80083E80(s) >> 4;
            s = func_80083F50(s) >> 8;
            w.x = (func_80083F50(QH(a, 0x56)) * s) >> 8;
            w.z = (-func_80083E80(QH(a, 0x56)) * s) >> 8;
            w.x *= 32;
            w.y *= 32;
            w.z *= 32;
            q = func_80133CAC(1, a, &v, &w);
            if (q != NULL) {
                q[0x5E] = a[0x6C];
            }
            QH(a, 0x42) = 4;
        }
        if (!(QH(a, 0x40) & 0x1F)) {
            func_80074590(0x8A, 0, 0);
        }
        if (--QH(a, 0x40) == 0) {
            func_8011DE34(a, 0x12, 4, 3);
            a[6]++;
        }
        break;
    case 2:
        if (QH(a, 0x6A) == 1) {
            func_8011DE34(a, 1, 4, 3);
            a[6]++;
        }
        break;
    case 3:
        k3 = QH(a, 0x6A);
        if (k3 == 1) {
            func_8011DE34(a, 0xF, 0xC, 3);
            a[0x5E] = k3;
            func_8011DC4C(a, 5);
            QH(a, 0x40) = QH(a, 0x70) + 0x5A;
            a[6]++;
        }
        break;
    case 4:
        func_80076D68(a);
        if (--QH(a, 0x40) == 0) {
            func_8011DE34(a, 0, 0xC, 3);
            func_8011DC4C(a, 2);
            a[0x5E] = 0;
            QH(a, 0x6C) = 0xFF;
            a[5] = 0;
            a[6] = 0;
        }
        break;
    }
}

extern u8 D_800BF80F;
s16 func_8011D540();
void func_8011DFEC(u8 *a);
void f_UpdateAnemoneCaptureSequence(u8 *a) {
    u8 *p = *(u8 **)(a + 0x10);
    s32 one;

    if (a[0xBF] == 0 && p != NULL && a[0x2B] == 0 && p[0x2B] != 0) {
        *(u8 **)(a + 0x10) = NULL;
        func_8011DE34(a, 0, 0xC, 3);
        a[0x5E] = 0;
        QH(a, 0x60) = 0;
        QH(a, 0x62) = 0x3C;
        QH(a, 0x64) = 0;
        a[5] = 0;
        a[6] = 0;
        return;
    }
    switch (a[6]) {
    case 0:
        func_8011CF9C(a, 1);
        a[6]++;
        break;
    case 1:
        if (QH(a, 0x6A) == 1) {
            a[6]++;
        }
    case 2:
        if (a[0x2B] != 0) {
            a[6] = 3;
            a[0x5E]++;
        }
        break;
    case 3:
        if (func_8011D540(a) != 0) {
            a[0] = 3;
            QH(a, 0x72) = 1;
            if (QH(a, 0x6C) < 3) {
                func_8011DE34(a, 0x10, 4, 3);
            } else {
                func_8011DE34(a, 0x11, 4, 3);
            }
            QH(a, 0x40) = 4;
            a[6]++;
        }
        break;
    case 4:
        if (QH(a, 0x6A) == 1 && --QH(a, 0x40) == 0) {
            QH(a, 0x40) = 9;
            func_8011DE34(a, 0x12, 2, 3);
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
            func_8011DE34(a, 0x13, 0, 3);
            a[6]++;
        }
        break;
    case 6:
        if ((one = QH(a, 0x6A)) == 1) {
            if (D_800BF80F == 0) {
                func_8011DE34(a, 0xA, 4, 3);
                if (func_80040B48(0x65) >= 0) {
                    D_800BF870.pad1[0x17B] |= one << (a[3] * 2);
                    a[0] = one;
                    a[3] |= 0x80;
                }
                func_8011DFEC(a);
                a[6]++;
            } else {
                func_8011DE34(a, 0, 0x10, 3);
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

#define H(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define U(p, o) (*(u16 *)((u8 *)(p) + (o)))
extern u8 D_8013616C[];
s32 func_8011CF9C(u8 *a, s32 f) {
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
    func_8011DE34(a, D_8013616C[ang], 8, 3);
    func_8011DC4C(a, (s16)ang);
    return 1;
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8011D104);

#define H(p, o) (*(s16 *)((u8 *)(p) + (o)))
s32 func_8011D2C4(u8 *a) {
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
        e = func_8011DD38();
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

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8011D540);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8011D754);

void func_8011D8C8(u8 *a)
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

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8011D9E4);

extern u16 D_1F800164_7d8c;
s32 func_8011DBA4(u8 *a) {
    s16 dx, dz;

    if (D_800E7FFE & 0x8200) {
        return 0;
    }
    dx = D_1F800160_3621 - M2C_FIELD(a, u16 *, 0x2E);
    dz = D_1F800164_7d8c - M2C_FIELD(a, u16 *, 0x36);
    if (dx * dx + dz * dz > 0x64000) {
        return 0;
    }
    return (u16)(M2C_FIELD(a, u16 *, 0x32) - D_1F800162) <= M2C_FIELD(a, s16 *, 0x6E);
}

typedef struct {
    s16 x, y;
} Pair16;
extern Pair16 D_80136174[];
void func_8011DC4C(u8 *a, s16 k) {
    s32 t;

    M2C_FIELD(a, s16 *, 0x60) = D_80136174[k].x;
    M2C_FIELD(a, s16 *, 0x62) = D_80136174[k].y;
    M2C_FIELD(a, s16 *, 0x64) = (-func_80083E80(M2C_FIELD(a, s16 *, 0x56)) * M2C_FIELD(a, s16 *, 0x60)) >> 12;
    t = func_80083F50(M2C_FIELD(a, s16 *, 0x56)) * M2C_FIELD(a, s16 *, 0x60);
    M2C_FIELD(a, s16 *, 0x6C) = k;
    M2C_FIELD(a, s16 *, 0x60) = t >> 12;
}

void func_8011DCE0(u8 *a) {
    if (a[6] == 0) {
        a[0x5E] = 0;
        func_8011DE34(a, 0xF, 2, 3);
        func_80026100(0x10);
        a[6]++;
    }
}

u8 *func_8011DD38(void) {
    u8 *p;

    for (p = D_800F2738; p != NULL; p = M2C_FIELD(p, u8 **, 0x24)) {
        if ((M2C_FIELD(p, u32 *, 0) & 0xFF00FF) == 1) {
            return p;
        }
    }
    return NULL;
}

typedef struct {
    u8 pad0[0x38];
    u8 *p38;
    u8 pad3C[0x24];
    s16 h60[0x34];
    u8 *pC8;
} ActorDF;
void func_8011DD88(ActorDF *a, s32 i) {
    s32 j = i + 1;
    s16 v;

    func_8011D9E4(a, j);
    if (a->h60[j] != 2) {
        a->h60[i] = 0;
    } else {
        v = *(s16 *)(a->p38 + 4) >> 4;
        if (v != a->h60[i]) {
            func_80051B04(a->pC8, 0x15, v);
            a->h60[i] = v;
        }
    }
}

typedef struct {
    u8 pad[0x60];
    s16 v[8];
} ArrActor60;
extern u8 D_80139FE0[];
void func_8011DE34(ArrActor60 *a, s32 k, s32 f, s32 i) {
    s16 n;

    if (f == 0) {
        func_80077C40(a, D_80139FE0, k);
    } else {
        func_80077CFC(a, D_80139FE0, k, (s16)f);
    }
    func_8011D9E4(a, i + 1);
    if (a->v[i + 1] != 2) {
        a->v[i] = 0;
        return;
    }
    n = (s16)M2C_FIELD(M2C_FIELD(a, u8 **, 0x38), u16 *, 4) >> 4;
    if (n != a->v[i]) {
        func_80051B04(M2C_FIELD(a, u8 **, 0xC8), 0x15, n);
        a->v[i] = n;
    }
}

s16 func_8011DF24(ActorDF *a, s32 i) {
    s32 r = func_80076D68();
    s32 j = i + 1;
    s16 v;

    func_8011D9E4(a, j);
    if (a->h60[j] != 2) {
        a->h60[i] = 0;
    } else {
        v = *(s16 *)(a->p38 + 4) >> 4;
        if (v != a->h60[i]) {
            func_80051B04(a->pC8, 0x15, v);
            a->h60[i] = v;
        }
    }
    return r;
}

void func_8011DFEC(u8 *a) {
    u8 *p = func_8003116C(0x201, a + 0x2C, 0);

    if (p != NULL) {
        M2C_FIELD(p, u8 **, 0x10) = a;
        M2C_FIELD(a, u8 **, 0x10) = p;
        p[7] = 0;
        M2C_FIELD(p, s16 *, 0x2E) -= 0x30;
    }
}

void func_8011E040(u8 *a) {
    u8 *p = M2C_FIELD(a, u8 **, 0x10);

    if (p != NULL) {
        p[4] = 3;
        M2C_FIELD(a, u8 **, 0x10) = NULL;
    }
    func_80112DD8(a);
    func_8003116C(0x24, a + 0x2C, -10);
    D_800BF870.pad1[0x17B] += 1 << ((a[3] & 0x7F) * 2);
    a[4] = 3;
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8011E0C0);

extern M2C_UNK D_8013618C;
extern M2C_UNK D_801361B4;
extern M2C_UNK D_801393C0;
void func_8011E1D4(void *arg0) {
    M2C_UNK *var_a2;
    u8 temp_v1;

    if (func_8007778C() != 0) {
        temp_v1 = M2C_FIELD(arg0, u8 *, 5);
        switch (temp_v1) {                          /* irregular */
        case 0:
            if (M2C_FIELD(arg0, u8 *, 0x2B) == 3) {
                func_80042354(1, 1);
                func_80070724(1, 0, 0x9A);
                if (D_800BF870.pad1[0x247] != 0) {
                    var_a2 = &D_8013618C;
                    if (D_800BF870.pad1[0x4C] != 0xFF) {
                        M2C_FIELD(arg0, s8 *, 0x7A) = 0x11;
                    } else if (!(M2C_FIELD(&D_800BF870, u16 *, 0x5E6) & 4)) {
                        M2C_FIELD(arg0, s8 *, 0x7A) = 0x12;
                    } else {
                        M2C_FIELD(arg0, s8 *, 0x7A) = 0x13;
                    }
                } else if (D_800BF870.pad1[0x4C] != 0) {
                    var_a2 = &D_8013618C;
                    M2C_FIELD(arg0, s8 *, 0x7A) = 0x10;
                } else {
                    var_a2 = &D_801361B4;
                }
                func_80040CDC(arg0, &D_801393C0, var_a2);
                M2C_FIELD(arg0, u8 *, 0x70) = 2U;
                M2C_FIELD(arg0, u8 *, 5) = (u8) (M2C_FIELD(arg0, u8 *, 5) + 1);
            }
            func_80076D68(arg0);
            return;
        case 1:
            if (M2C_FIELD(arg0, u8 *, 0x70) == 0xFF) {
                M2C_FIELD(arg0, u8 *, 5) = 0U;
            }
            func_80041098(arg0);
            func_8004190C(arg0);
            break;
        }
    }
}

void func_8011E324(AreaPartsOwner *a) {
    switch (a->pad[4]) {
    case 0:
        M2C_FIELD(a, s16 *, 0x56) = 0x400;
        a->pad[0x7B] = 1;
        func_80051B04(a->parts[a->pad[9] - 1], 0x1A, 4);
        func_80077C40(a, D_801393C0_27b3, 1);
        a->pad[0x2B] = 0;
        a->pad[4]++;
    case 1:
        func_8011E1D4(a);
        if (a->pad[1] != 0) {
            func_800518FC(a);
        }
        a->pad[0x2B] = 0;
        break;
    case 2:
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

extern u8 D_800A3E58[];
extern u8 D_801363D4[];
void func_8011E9E8(u8 *a);
void func_8011EA60(u8 *a);
void func_8011E404(u8 *a)
{
    u8 *g;
    u32 k;

    switch (a[4]) {
    case 0:
        g = (u8 *)&D_800BF870;
        k = g[0x18B];
        if (k >= 3) {
            if (g[0x99] == 0xFF) {
                a[0x5E] = 5;
            } else if (g[0x99] != 0) {
                if (k == 4) {
                    a[0x5E] = k;
                } else {
                    a[0x5E] = 3;
                }
            } else if (g[0x97] == 0xFF) {
                a[0x5E] = 2;
            } else if (k == 4) {
                a[0x5E] = 1;
            } else {
                a[0x5E] = 0;
            }
            if (a[0x5E] == 5) {
                func_80040CDC(a, D_801393C0_27b3, D_800A3E58);
            } else {
                func_80040CDC(a, D_801393C0_27b3, D_801363D4);
            }
            a[5] = 3;
        } else {
            if (g[0x99] == 0xFF) {
                a[0x5E] = 6;
            } else if (g[0x97] == 0xFF) {
                if (g[0x2A5] == 0) {
                    a[0x5E] = 2;
                } else if (g[0x98] == 0xFF) {
                    if (g[0x99] != 0) {
                        a[0x5E] = 3;
                    } else {
                        a[0x5E] = 4;
                    }
                } else {
                    a[0x5E] = 5;
                }
            } else if (g[0x96] == 0xFF) {
                a[0x5E] = 1;
            } else {
                a[0x5E] = 0;
            }
            func_80040CDC(a, D_801393C0_27b3, D_800A3D40);
        }
        func_80041718(a, 0, 0);
        M2C_FIELD(a, s16 *, 0x56) = 0x800;
        a[4]++;
    case 1:
        a[1] = 1;
        func_80077E7C(a);
        switch (a[5]) {
        case 0:
            func_80041098(a);
            func_8004190C(a);
            func_8011E9E8(a);
            break;
        case 1:
            func_80041098(a);
            func_8004190C(a);
            func_8011EA60(a);
            break;
        case 2:
            func_80041098(a);
            func_8004190C(a);
            func_8011E6D0(a);
            break;
        case 3:
            func_8011E804(a);
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

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8011E6D0);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8011E804);

void func_8011E9E8(u8 *a) {
    if (a[0x2B] == 3) {
        func_80040D68(a, D_800A3D40);
        a[0x70] = 1;
        if (a[0x5E] == 4 || a[0x5E] == 6) {
            func_80042354(1, 3);
        } else {
            func_80042354(1, 1);
        }
        a[5] = 1;
    }
}

extern void *D_8013677C[];
extern u8 D_801367D0[];
void func_8011EA60(u8 *a) {
    if (a[0x71] == 0xFF) {
        func_80041768(a, 5, 4);
        func_80040D68(a, D_8013677C[a[0x5E]]);
        a[0x70] = 1;
        a[5] = 2;
        a[6] = D_801367D0[a[0x5E]];
    }
}

s32 func_8011EAE4(void *arg0) {
    M2C_FIELD(arg0, s8 *, 5) = 2;
    M2C_FIELD(arg0, s8 *, 6) = 2;
    M2C_FIELD(arg0, s8 *, 0x5E) = 4;
    return 1;
}

extern u8 D_800A3D70[];
extern u8 D_801367D8[];
void func_8011EB00(u8 *a)
{
    s32 i;

    switch (a[4]) {
    case 0:
        i = a[9] - 1;
        func_80051B04(*(u8 **)(a + (i << 2) + 0xC0), 0x1A, 3);
        func_80040CDC(a, D_801393C0_27b3, D_800A3D70);
        a[0x7B] = 1;
        func_80041718(a, 1, 0);
        a[0x2A] = 0x10;
        M2C_FIELD(a, s16 *, 0x2E) = 0x35E8;
        M2C_FIELD(a, s16 *, 0x32) = -0x1803;
        M2C_FIELD(a, s16 *, 0x36) = 0x3B60;
        M2C_FIELD(a, s16 *, 0x56) = 0;
        a[0x2B] = 0;
        a[4]++;
        break;
    case 1:
        if (func_8007778C(a) != 0) {
            switch (a[5]) {
            case 0:
                if (a[0x2B] == 3) {
                    func_80042354(1, 1);
                    func_80040D68(a, D_800A3D70);
                    a[0x70] = 2;
                    a[6] = 0;
                    a[5]++;
                }
                break;
            case 1:
                if (a[0x70] == 0xFF) {
                    switch (a[6]) {
                    case 0:
                        func_80040D68(a, D_801367D8);
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

extern s8 D_1F800164[];
extern s8 D_1F800207[];
extern M2C_UNK D_80136808;
extern M2C_UNK D_8013687C;
void func_8011ECFC(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 5);
    switch (temp_v1) {                              /* irregular */
    case 0:
        func_8007778C(arg0);
        if (D_800BF8BF != 0) {
            M2C_FIELD(arg0, u8 *, 5) = 1U;
        } else if ((M2C_FIELD(arg0, u8 *, 1) != 0) && (*((u8 *)D_1F800207) == 0x10) && (*((s16 *)D_1F800164) >= 0x399E) && (func_8005308C() != 0)) {
            func_80042354(1, 1);
            func_80040D68(arg0, &D_8013687C);
            M2C_FIELD(arg0, u8 *, 0x70) = 2U;
            M2C_FIELD(arg0, u8 *, 5) = 2U;
        }
        break;
    case 1:
        func_8007778C(arg0);
        if (D_800BF870.pad1[0x4E] == 0xFF) {
            M2C_FIELD(arg0, u8 *, 5) = 0U;
            M2C_FIELD(arg0, s8 *, 0xBF) = 1;
        } else if ((M2C_FIELD(arg0, u8 *, 1) != 0) && (M2C_FIELD(arg0, u8 *, 0x2B) == 3)) {
            func_80042354(1, 1);
            if (D_800BF870.pad1[0x17F] & 1) {
                M2C_FIELD(arg0, s8 *, 0x7A) = 1;
            } else {
                D_800BF870.pad1[0x17F] |= 1;
                M2C_FIELD(arg0, s8 *, 0x7A) = 0;
            }
            func_80040D68(arg0, &D_80136808);
            M2C_FIELD(arg0, u8 *, 0x70) = 2U;
            M2C_FIELD(arg0, u8 *, 5) = (u8) (M2C_FIELD(arg0, u8 *, 5) + 1);
        }
        break;
    case 2:
        if (M2C_FIELD(arg0, u8 *, 0x70) == 0xFF) {
            M2C_FIELD(arg0, u8 *, 5) = 1U;
        }
        M2C_FIELD(arg0, u8 *, 1) = 1U;
        func_80077E7C(arg0);
        break;
    }
    func_80041098(arg0);
    func_8004190C(arg0);
}

extern u8 D_800BF8BE;
extern u8 D_8013694C[];
extern u8 D_80136974[];
extern u8 D_801369BC[];
extern u8 D_80136A1C[];
void f_UpdateGranRemoveCappersDialogue(u8 *a) {
    u8 *p;
    u8 k;

    switch (a[5]) {
    case 0:
        *(u8 **)(a + 0x14) = func_8012B654(a, 0);
        a[5]++;
    case 1:
        if (func_8007778C(a) != 0 && D_1F800207_9c67 == 0x10 && D_1F800164_d75f >= 0x3A34 && func_8005308C() != 0) {
            func_80042354(1, 1);
            func_80040D68(a, D_8013694C);
            a[0x70] = 2;
            a[5]++;
        }
        break;
    case 2:
        if (a[0x70] == 0xFF) {
            func_80040D68(a, D_80136974);
            a[0x70] = 2;
            a[5]++;
        }
        a[1] = 1;
        func_80077E7C(a);
        break;
    case 3:
        k = a[0x70];
        if (k == 0xFF) {
            if (D_800BF8BE == k) {
                a[0] = 2;
                func_80040D68(a, D_801369BC);
            } else {
                func_80040D68(a, D_80136A1C);
            }
            a[0x70] = 2;
            a[5]++;
        }
        a[1] = 1;
        func_80077E7C(a);
        break;
    case 4:
        k = a[0x70];
        if (k == 0xFF) {
            p = *(u8 **)(a + 0x14);
            if (p != NULL) {
                p[4] = 3;
            }
            if (D_800BF870.pad1[0x4D] == k) {
                a[0] = 2;
                a[4] = 3;
                D_800BF870.pad1[0x190] |= 2;
            } else {
                a[5] = 0;
                a[0xBF] = 2;
            }
        }
        a[1] = 1;
        func_80077E7C(a);
        break;
    }
    func_80041098(a);
    func_8004190C(a);
}

extern u8 D_8013690C[];
extern u8 D_80136A54[];
extern u8 D_80136A7C[];
void f_UpdateGranPostPipeAreaDialogue(u8 *a) {
    u8 *p;

    switch (a[5]) {
    case 0:
        if (D_800BF8BE == 0xFF) {
            *(u8 **)(a + 0x14) = func_8012B654(a, 0);
            a[5] = 2;
        }
        if (func_8007778C(a) != 0 && a[0x2B] == 3) {
            func_80042354(1, 1);
            func_80070724(1, 0, 0x9A);
            func_80040D68(a, D_80136A54);
            a[0x70] = 2;
            a[5]++;
        }
        break;
    case 1:
        if (a[0x70] == 0xFF) {
            a[5]--;
        }
        a[1] = 1;
        func_80077E7C(a);
        break;
    case 2:
        if (func_8007778C(a) != 0 && D_1F800207_9c67 == 0x10 && D_1F800164_d75f >= 0x3A34 && func_8005308C() != 0) {
            func_80042354(1, 1);
            func_80040D68(a, D_8013690C);
            a[0x70] = 2;
            a[5]++;
        }
        break;
    case 3:
        if (a[0x70] == 0xFF) {
            func_80040D68(a, D_80136A7C);
            a[0x70] = 2;
            a[5]++;
        }
        a[1] = 1;
        func_80077E7C(a);
        break;
    case 4:
        if (a[0x70] == 0xFF) {
            p = *(u8 **)(a + 0x14);
            if (p != NULL) {
                p[4] = 3;
            }
            a[4] = 3;
            D_800BF870.pad1[0x190] |= 2;
        }
        a[1] = 1;
        func_80077E7C(a);
        break;
    }
    func_80041098(a);
    func_8004190C(a);
}

extern u8 D_800A3E38[];
extern u8 D_800BFADF;
extern u8 D_80136B58[];
extern u8 D_80136BA8[];
extern u8 D_80136BF8[];
extern u8 D_80136C08[];
void func_8011F2A4(u8 *a) {
    GameState *g;

    switch (a[5]) {
    case 0:
        if (D_1F800207_9c67 == 0xA && D_1F800160_71b4 >= 0x4B64 && func_8005308C() != 0) {
            func_80042354(1, 1);
            func_80040D68(a, D_80136B58);
            a[0x70] = 2;
            a[5]++;
        }
        break;
    case 1:
        if (a[0x70] == 0xFF) {
            g = &D_800BF870;
            if (g->pad1[0x189] == 0x15) {
                g->pad1[0x189] = 0x16;
                func_80040D68(a, D_80136BA8);
                a[5] = 2;
            } else if (g->itemCounts[0x2B] == 0) {
                func_80040D68(a, D_80136BF8);
                a[5] = 3;
            } else {
                func_80040D68(a, D_80136C08);
                a[5] = 4;
            }
            a[0x70] = 2;
        }
        break;
    case 2:
        if (a[0x70] == 0xFF) {
            if (D_800BFADF == 0) {
                func_80040D68(a, D_800A3E38);
                a[5] = 3;
            } else {
                func_80040D68(a, D_80136C08);
                a[5] = 4;
            }
            a[0x70] = 2;
        }
        break;
    case 3:
        if (a[0x70] == 0xFF && (D_1F800207_9c67 != 0xA || D_1F800160_71b4 < 0x4B64)) {
            a[5] = 0;
        }
        break;
    case 4:
        if (a[0x70] == 0xFF) {
            a[5] = 0;
            a[0xBF] = 1;
        }
        break;
    }
    if (a[5] == 0) {
        func_8007778C(a);
    } else {
        a[1] = 1;
        func_80077E7C(a);
    }
    if (a[1] != 0) {
        func_80041098(a);
        func_8004190C(a);
    }
}

#define FH(p, o) (*(s16 *)((u8 *)(p) + (o)))
extern u8 D_800BF9FA;
extern u8 D_80136CE0[];
extern u8 D_80136DA0[];
extern s32 D_1F800214;
void func_8011F4B8(u8 *a) {
    u8 *p;
    s32 s = a[5];
    s32 t;

    switch (s) {
    case 0:
        if (D_800BF9FA == 0x19) {
            func_80040D68(a, D_80136CE0);
            a[0x70] = 2;
            a[5]++;
        }
        break;
    case 1:
        if (a[0x70] == 0xFF) {
            func_80040D68(a, D_80136DA0);
            a[0x70] = 2;
            a[6] = 0;
            a[5]++;
        }
        break;
    case 2:
        p = *(u8 **)(a + 0x14);
        if (p == NULL) {
            break;
        }
        switch (a[6]) {
        case 0:
            if (FH(a, 0x2E) < 0x4877) {
                FH(p, 0x60) = 0;
                p[5] = 1;
                FH(p, 0x48) = FH(p, 0x2E);
                FH(p, 0x4A) = FH(p, 0x32);
                a[6]++;
            }
            break;
        case 1:
            if ((FH(p, 0x4A) += 0x1E) >= -0x1B8C) {
                FH(p, 0x4A) = -0x1B8C;
                FH(p, 0x4C) = 0;
                func_80074810(0x98, 0);
                a[6]++;
            }
            break;
        case 2:
            FH(p, 0x4A) = -0x1B8C;
            if (!(++FH(p, 0x4C) & 7)) {
                FH(p, 0x4C) = 0;
                a[6]++;
            } else {
                FH(p, 0x4A) -= func_8009A450() & 7;
            }
            break;
        case 3:
            FH(p, 0x4C) += 0x20;
            if ((FH(p, 0x58) += FH(p, 0x4C)) >= 0x400) {
                func_80074810(0x98, 0);
                func_800440E4(D_800E7E80, 0x80B4, 4);
                func_80041768(D_1F800214, 4, 4);
                FH(p, 0x58) = 0x400;
                a[6]++;
            }
            break;
        case 4:
            FH(p, 0x4A) = -0x1B8C;
            if (!(++FH(p, 0x4C) & 7)) {
                D_800BF844 = p;
                a[5]++;
            } else {
                FH(p, 0x4A) -= func_8009A450() & 7;
            }
            break;
        }
        FH(p, 0x2E) = FH(p, 0x48) + ((func_80083E80(FH(p, 0x58)) * 0xC0) >> 12);
        t = ((func_80083F50(FH(p, 0x58)) * 0xC0) >> 12) - 0xC0;
        FH(p, 0x32) = FH(p, 0x4A) - t;
        break;
    case 3:
        if (a[0x70] == 0xFF) {
            a[4] = s;
        }
        break;
    }
    a[1] = 1;
    func_80077E7C(a);
    if (a[1] != 0) {
        func_80041098(a);
        func_8004190C(a);
    }
}

#define W(p, o) (*(s32 *)((u8 *)(p) + (o)))
extern u8 D_801357A4[];
extern u8 D_800A3CD0[];
u8 *func_8006FB0C();
u8 *func_8012C2B4(void);
void func_8011F7CC(u8 *a)
{
    u8 *g;
    u8 *q;
    u8 *p;
    s32 t;
    s32 k;
    GameState *gs;

    switch (a[4]) {
    case 0:
        g = D_800ECF58_742e;
        W(a, 0x3C) = W(g, 0x38);
        if (func_800519E0(a, 0xF, W(g, 0x58), D_801357A4) != 0) {
            break;
        }
        q = D_801393C0_27b3;
        a[0xB] = 0x40;
        H(a, 0x80) = 0xA0;
        H(a, 0x82) = 0x140;
        H(a, 0x84) = 0xE0;
        H(a, 0x58) = 0;
        H(a, 0x56) = 0;
        H(a, 0x54) = 0;
        H(a, 0x86) = 0x180;
        a[0x2B] = 0;
        a[0x29] = 0;
        func_80040CDC(a, q, D_800A3CD0);
        switch (t = a[3]) {
        case 0:
            a[0] = 9;
            a[0x2A] = 0x10;
            H(a, 0x2E) = 0x35E8;
            H(a, 0x32) = -0x1803;
            H(a, 0x36) = 0x3B60;
            k = 2;
            a[0x7B] = k;
            func_80077C40(a, q, k);
            gs = &D_800BF870;
            if (gs->pad1[0x4E] != 0xFF) {
                a[0xBF] = 0;
            } else if (gs->pad1[0x50] == 0) {
                a[0xBF] = 1;
            } else if (!(gs->pad1[0x190] & 2)) {
                a[0xBF] = k;
            } else {
                a[4] = 3;
            }
            break;
        case 3:
            p = func_8006FB0C(a, 0x2C);
            W(a, 0x14) = (s32)p;
            if (p != NULL) {
                p[0xBE] = 0;
                H(p, 0x60) = -0x80;
                p[0x5E] = t;
                p[0x5F] |= 1;
            }
            if (D_800BF9FA != 0x18) {
                H(a, 0x2E) = 0x4F59;
                a[0xBF] = 0;
            } else {
                func_80115D84(a);
                ((u8 * (*)())func_8012C2B4)(a);
                H(a, 0x2E) = 0x526C;
                a[0xBF] = 1;
            }
            a[0] = 2;
            a[0x2A] = 0xA;
            H(a, 0x32) = -0x1B0C;
            H(a, 0x36) = 0x2340;
            H(a, 0x56) = 0x800;
            a[0x7B] = 0;
            func_80077C40(a, D_801393C0_27b3, 0);
            break;
        }
        a[5] = 0;
        a[4]++;
        break;
    case 1:
        switch (a[3]) {
        case 0:
            switch (a[0xBF]) {
            case 0:
                func_8011ECFC(a);
                break;
            case 1:
                f_UpdateGranRemoveCappersDialogue(a);
                break;
            case 2:
                f_UpdateGranPostPipeAreaDialogue(a);
                break;
            }
            break;
        case 3:
            switch (a[0xBF]) {
            case 0:
                func_8011F2A4(a);
                break;
            case 1:
                func_8011F4B8(a);
                break;
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

u8 *func_8011FB2C(s32 a, s32 b) {
    u8 *p = func_8007A980(3, 9, 0);

    if (p == NULL) {
        return NULL;
    }
    p[0x2] = 22;
    p[0x3] = b;
    M2C_FIELD(p, void **, 0x1C) = func_8011F7CC;
    return p;
}

extern u8 D_800BF80E;
extern s8 D_800BF9FA_0556;
s32 func_8011FB80(u8 *a) {
    switch (a[0x78]) {
    case 0:
        func_8004D604(0x2B, 1);
        func_800440E4(D_800E7E80, 0x72, 4);
        func_80115D84(a);
        a[0x78]++;
        break;
    case 1:
        if (D_800BF80E != 0) {
            func_800440E4(D_800E7E80, 0x73, 4);
            a[0x78]++;
        }
        break;
    case 2:
        if (D_800BF80E != 0) {
            func_800440E4(D_800E7E80, 2, 4);
            D_800BF9FA_0556 = 0x17;
            func_80074810(0x96, 0);
            return 1;
        }
        break;
    default:
        return 0;
    }
    return 0;
}

u8 *func_8012C2B4(void);
s32 func_8011FC88(u8 *a) {
    switch (a[0x78]) {
    case 0:
        func_800440E4(D_800E7E80, 0x72, 4);
        ((void (*)(u8 *))func_8012C2B4)(a);
        a[0x78]++;
        break;
    case 1:
        if (D_800BF80E != 0) {
            func_800440E4(D_800E7E80, 0x73, 4);
            a[0x78]++;
        }
        break;
    case 2:
        if (D_800BF80E != 0) {
            func_800440E4(D_800E7E80, 2, 4);
            D_800BF9FA_0556 = 0x18;
            func_80074810(0x96, 0);
            return 1;
        }
        break;
    default:
        return 0;
    }
    return 0;
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", f_HandleThirstyMinerInteraction);

#define W(p, o) (*(s32 *)((u8 *)(p) + (o)))
u8 *func_8007DEF8();
s32 func_8011FEF8(u8 *a) {
    u8 *t = D_800BF844;
    u8 *e;
    u8 *c;
    s16 s;
    s32 k;

    switch (a[0x78]) {
    case 0:
        a[0x7A] = 1;
        *(u8 **)(a + 0x10) = func_8007DEF8(6, 1, 0);
        H(a, 0x4A) = -0x4000;
        H(a, 0x50) = 0x400;
        a[0xBF] = 0xFF;
        a[0x78]++;
        break;
    case 1:
        if ((H(a, 0x4A) += H(a, 0x50)) >= 0x4000) {
            H(a, 0x4A) = 0x4000;
            a[0x78]++;
        }
    case 2:
        if (t == NULL) {
            return 0;
        }
        W(t, 0x30) += H(a, 0x4A) << 8;
        __asm__ volatile("");
        k = D_1F80017C;
        H(t, 0x54) += 0x188;
        if (k & 1) {
            e = func_8003116C(8, t + 0x2C, -0xA);
            if (e != NULL) {
                e[0x28] |= 0x80;
                H(e, 0x2E) += 0x30;
                s = func_80083F50(H(t, 0x54)) >> 6;
                H(e, 0x2E) -= s + (s >> 1);
                s = func_80083E80(H(t, 0x54)) >> 6;
                H(e, 0x30) -= s + (s >> 1);
            }
        }
        if (H(t, 0x32) < -0x1770) {
            return 0;
        }
        H(t, 0x32) = -0x1770;
        e = func_800310F4(0x20, 0);
        if (e != NULL) {
            e[0x28] |= 0x80;
            H(e, 0x50) = H(t, 0x2E);
            e += 0x50;
            H(e, 8) = H(t, 0x2E);
            H(e, 2) = H(t, 0x32) + 0x30;
            s = func_80083F50(H(t, 0x54)) >> 6;
            H(e, 2) -= s + (s >> 1);
            H(e, 0xA) = H(e, 2) + 0x64;
            H(e, 4) = H(t, 0x36);
            s = func_80083E80(H(t, 0x54)) >> 6;
            H(e, 4) -= s + (s >> 1);
            H(e, 0xC) = H(e, 4) - 0x190;
            func_80074590(7, 0, 0);
        }
        func_80051B04(*(u8 **)(t + 0xC0), 1, 0);
        H(a, 0x40) = 0;
        a[0x78]++;
        break;
    case 3:
        if (++H(a, 0x40) < 0x14) {
            return 0;
        }
        *(s32 *)(a + 0x14) = 0;
        a[0x78]++;
        break;
    case 4:
        c = *(u8 **)(a + 0x10);
        if (c != NULL) {
            if (c[4] != 2) {
                return 0;
            }
            c[4] = 3;
            *(u8 **)(a + 0x10) = NULL;
            return 1;
        }
        break;
    }
    return 0;
}

void func_80120200(u8 *a) {
    u8 *p = FP(a, 0x14);
    u8 *e;
    s16 v;

    if (p != NULL && !(D_1F80017C & 0xF)) {
        e = func_8003116C(0x204, p + 0x2C, -0xA);
        if (e != NULL) {
            e[0x28] |= 0x80;
            F16(e, 0x2E) += 0x30;
            v = func_80083F50(F16(p, 0x54)) >> 6;
            F16(e, 0x2E) -= v + (v >> 1);
            F16(e, 0x2E) -= (a[0xBF] >> 4) & func_8009A450();
            v = func_80083E80(F16(p, 0x54)) >> 6;
            F16(e, 0x30) -= v + (v >> 1);
            F16(e, 0x30) -= a[0xBF] & func_8009A450();
        }
    }
}

void func_80120420(u8 *a);
void func_80120508(u8 *a);
void f_ReturnThirstyMinerToIdleScript(u8 *a);
void func_80120308(u8 *a) {
    switch (a[4]) {
    case 0:
        func_80120420(a);
        break;
    case 1:
        a[1] = 1;
        func_80077E7C(a);
        func_80041098(a);
        func_8004190C(a);
        func_800518FC(a);
        switch (a[5]) {
        case 0:
            f_HandleThirstyMinerInteraction(a);
            break;
        case 1:
            func_80120508(a);
            break;
        case 2:
            f_ReturnThirstyMinerToIdleScript(a);
            break;
        }
        func_80120200(a);
        a[0x2B] = 0;
        break;
    case 2:
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

extern u8 D_8013581C[];
extern u8 D_80137124[];
extern u8 D_800BF910;
void func_80120420(u8 *a) {
    u8 *g = D_800ECF58_742e;

    M2C_FIELD(a, s32 *, 0x3C) = M2C_FIELD(g, s32 *, 0x38);
    if (func_800519E0(a, 0xF, M2C_FIELD(g, s32 *, 0x3C), D_8013581C) != 0) {
        return;
    }
    func_80040CDC(a, D_801393C0_27b3, D_80137124);
    if (D_800BF910 == 0xFF) {
        a[0x5E] = 1;
        func_80041718(a, 0, 0);
    } else {
        a[0x5E] = 0;
        func_80041718(a, 0xD, 0);
    }
    M2C_FIELD(a, s16 *, 0x56) = 0x800;
    a[0] = 9;
    M2C_FIELD(a, s16 *, 0x80) = 0xB4;
    M2C_FIELD(a, s16 *, 0x82) = 0x168;
    M2C_FIELD(a, s16 *, 0x84) = 0x78;
    M2C_FIELD(a, s16 *, 0x54) = 0;
    M2C_FIELD(a, s16 *, 0x58) = 0;
    a[0xB] = 0;
    M2C_FIELD(a, s16 *, 0x86) = 0xF0;
    a[0x2B] = 0;
    a[0x29] = 0;
    M2C_FIELD(a, s32 *, 0x14) = 0;
    a[4]++;
}

extern void *D_80137114[];
void func_80120508(u8 *a)
{
    if (a[0x71] == 0xFF) {
        func_80040D68(a, D_80137114[a[0x5E]]);
        a[5] = 2;
        a[0x70] = 1;
    }
}

extern u8 D_800A3E28[];
void f_ReturnThirstyMinerToIdleScript(u8 *a) {
    if (a[0x71] == 0xFF) {
        switch (a[0x5E]) {
        case 0 ... 1:
            func_80040D68(a, D_800A3E38);
            break;
        case 2 ... 3:
            a[0x5E] -= 2;
            func_80040D68(a, D_800A3E28);
            break;
        }
        a[0x70] = 1;
        a[5] = 0;
    }
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_801205E4);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_801206D8);

s32 func_801207DC(void) {
    if (M2C_FIELD(D_800BF844, s16 *, 0x68) == 0x62) {
        return 3;
    }
    return 2;
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80120804);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_801208B4);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80120C34);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80120DA0);

#define RH(p, o) (*(s16 *)((u8 *)(p) + (o)))
void func_80120F00(u8 *a) {
    switch (a[6]) {
    case 0:
        RH(a, 0x40) = (func_8009A450() & 3) + 2;
        RH(a, 0x58) = 0;
        if (a[0xBE] == 0) {
            RH(a, 0x64) = (RH(a, 0x60) + 0x200) & 0xFFF;
            RH(a, 0x66) = (RH(a, 0x60) - 0x200) & 0xFFF;
            RH(a, 0x68) = RH(a, 0x60) & 0xFFF;
        } else {
            RH(a, 0x64) = (RH(a, 0x60) + 0xA00) & 0xFFF;
            RH(a, 0x66) = (RH(a, 0x60) + 0x600) & 0xFFF;
            RH(a, 0x68) = (RH(a, 0x60) + 0x800) & 0xFFF;
        }
        a[6]++;
        break;
    case 1:
        if (RH(a, 0x64) == (RH(a, 0x56) = func_800776F8(RH(a, 0x64), RH(a, 0x56), 0x80))) {
            a[6]++;
        }
        break;
    case 2:
        if (RH(a, 0x66) == (RH(a, 0x56) = func_800776F8(RH(a, 0x66), RH(a, 0x56), 0x80))) {
            a[6]++;
        }
        break;
    case 3:
        if (RH(a, 0x68) == (RH(a, 0x56) = func_800776F8(RH(a, 0x68), RH(a, 0x56), 0x80))) {
            if (--RH(a, 0x40) == 0) {
                a[6]++;
            } else {
                a[6] = 1;
            }
        }
        break;
    case 4:
        a[5] = 4;
        a[6] = 0;
        a[7] = 0;
        break;
    }
    func_801208B4(a);
}

extern s16 D_1F8001A4;
extern u8 D_80137234[];
extern u16 D_80137238[];
/* func_80122CAC, inlined */
static inline s32 inl_80122CAC(u8 *a) {
    if (func_80049280(a, (M2C_FIELD(a, s16 *, 0x44) >> 8) + 0x20, (M2C_FIELD(a, s16 *, 0x4A) * M2C_FIELD(a, s16 *, 0x44)) >> 16) == 0 &&
        M2C_FIELD(a, s16 *, 0x32) - D_1F8001A4 < -500) {
        return 1;
    }
    if (a[0x2A] != 0x10) {
        return 0;
    }
    if (M2C_FIELD(a, s16 *, 0x36) >= 0x36D9) {
        M2C_FIELD(a, s16 *, 0x36) = 0x36D8;
        return 1;
    }
    return 0;
}
/* func_80122D70, inlined */
static inline s32 inl_80122D70(u8 *a) {
    switch (a[7]) {
    case 0:
        M2C_FIELD(a, s16 *, 0x58) = 0;
        if (a[0xBE] == 0) {
            M2C_FIELD(a, s16 *, 0x64) = (M2C_FIELD(a, u16 *, 0x60) + 0x800) & 0xFFF;
        } else {
            M2C_FIELD(a, s16 *, 0x64) = M2C_FIELD(a, u16 *, 0x60);
        }
        a[7]++;
        break;
    case 1:
        M2C_FIELD(a, s16 *, 0x56) = func_800776F8(M2C_FIELD(a, s16 *, 0x64), M2C_FIELD(a, s16 *, 0x56), 0x100);
        if (M2C_FIELD(a, s16 *, 0x64) == M2C_FIELD(a, s16 *, 0x56)) {
            a[0xBE] = 1 - a[0xBE];
            return 1;
        }
        break;
    }
    return 0;
}
/* func_80122F80, inlined */
static inline void inl_80122F80(u8 *a, s32 b) {
    if (a[0xBE] == 0) {
        M2C_FIELD(a, s16 *, 0x44) = b;
    } else {
        M2C_FIELD(a, s16 *, 0x44) = -b;
    }
    func_8004130C(a, 0);
}
void func_801210A4(u8 *a) {
    u16 v;
    u16 w;

    switch (a[6]) {
    case 0:
        M2C_FIELD(a, s16 *, 0x40) = D_80137234[func_8009A450() & 3] << 5;
        v = D_80137238[a[0xBF]];
        if (a[0xBE] != 0) {
            v = -v;
        }
        do { M2C_FIELD(a, s16 *, 0x44) = v; } while (0);
        func_8004130C(a, 0);
        a[7] = 0;
        a[6]++;
        break;
    case 1:
        func_80041A1C(a, 2);
        func_8004954C(a, M2C_FIELD(a, s16 *, 0x80), -0x5A);
        func_80041AC0(a);
        M2C_FIELD(a, s16 *, 0x32) += 8;
        func_80041938(a, 0, 0);
        if (func_80120804(a) != 0) {
            a[6]++;
            break;
        }
        if (inl_80122CAC(a) != 0) {
            a[6]++;
            break;
        }
        if (--M2C_FIELD(a, s16 *, 0x40) == 0) {
            a[6] = 3;
        }
        break;
    case 2:
        if (inl_80122D70(a) != 0) {
            w = D_80137238[a[0xBF]];
            if (a[0xBE] == 0) {
                M2C_FIELD(a, s16 *, 0x44) = w;
            } else {
                M2C_FIELD(a, s16 *, 0x44) = -w;
            }
            func_8004130C(a, 0);
            M2C_FIELD(a, s16 *, 0x42) = 0xF;
            a[6] = 4;
            a[7] = 0;
        }
        break;
    case 3:
        a[5] = 4;
        a[6] = 0;
        a[7] = 0;
        break;
    case 4:
        func_80041A1C(a, 2);
        func_8004954C(a, M2C_FIELD(a, s16 *, 0x80), -0x5A);
        func_80041AC0(a);
        M2C_FIELD(a, s16 *, 0x32) += 8;
        func_80041938(a, 0, 0);
        if (--M2C_FIELD(a, s16 *, 0x42) == 0) {
            a[6] = 1;
        }
        break;
    }
    func_801208B4(a);
}

extern u8 D_800E7E80[];
/* func_80122E3C, inlined */
static inline s32 inl_80122E3C(u8 *a) {
    u8 *g = D_800E7E80;
    s16 dz = M2C_FIELD(g, s16 *, 0x36) - M2C_FIELD(a, s16 *, 0x36);
    s16 dx = M2C_FIELD(g, s16 *, 0x2E) - M2C_FIELD(a, s16 *, 0x2E);

    return func_80077768((s16)func_80085690(-dz, dx), M2C_FIELD(a, s16 *, 0x60), 0);
}
extern u16 D_1F800162;
extern u16 D_1F800160_3621;
extern u16 D_1F800164_7d8c;
static inline s32 inl_check(u8 *a)
{
    s16 dx, dz, dy;
    u16 d;

    if (D_800E7FFE & 0x8200) {
        return 0;
    }
    dx = D_1F800160_3621 - M2C_FIELD(a, u16 *, 0x2E);
    dz = D_1F800164_7d8c - M2C_FIELD(a, u16 *, 0x36);
    dy = D_1F800162 - M2C_FIELD(a, u16 *, 0x32);
    d = func_80084080(dx * dx + dz * dz + dy * dy);
    if (d > 0x7D0 || (u16)(dy + 0x320) >= 0x44D) {
        return 0;
    }
    if (d >= 0x3E9) {
        return 1;
    }
    return 2;
}
void func_801213F4(u8 *a)
{
    s32 r;

    switch (a[6]) {
    case 0:
        r = inl_check(a);
        if (r == 1) {
            a[5] = 5;
            a[6] = 0;
            a[7] = 0;
        } else if (r == 2) {
            if (!(func_8009A450() & 1)) {
                if (a[0xBF] != 0) {
                    a[5] = 5;
                } else {
                    a[5] = 6;
                }
                a[6] = 0;
                a[7] = 0;
            } else if (a[0xBE] == inl_80122E3C(a)) {
                a[5] = 3;
                a[6] = 0;
                a[7] = 0;
            } else {
                a[6]++;
            }
        } else {
            a[5] = 0;
            a[6] = 0;
            a[7] = 0;
        }
        break;
    case 1:
        if (inl_80122D70(a)) {
            a[5] = 3;
            a[6] = 0;
            a[7] = 0;
        }
        break;
    }
    func_801208B4(a);
}

extern u16 D_8013723C[];
static inline s32 inl_near(u8 *a) {
    s16 dy;
    u16 d;

    if (D_800E7FFE & 0x8200) {
        return 0;
    }
    dy = D_1F800162 - H(a, 0x32);
    d = func_80084080((s16)(D_1F800160_3621 - H(a, 0x2E)) * (s16)(D_1F800160_3621 - H(a, 0x2E)) +
                      (s16)(*(u16 *)&D_1F800164_7d8c - H(a, 0x36)) * (s16)(*(u16 *)&D_1F800164_7d8c - H(a, 0x36)) + dy * dy);
    if (d >= 0x7D1) {
        return 0;
    }
    if ((u16)(dy + 0x320) >= 0x44D) {
        return 0;
    }
    if (d >= 0x3E9) {
        return 1;
    }
    return 2;
}
void func_80121678(u8 *a) {
    u8 *t;
    s32 k;
    u16 w;
    s32 r;
    s16 dy;
    u16 d;

    switch (a[6]) {
    case 0:
        t = D_800E7E80;
        k = a[0xBE];
        if (k != func_80077768((s16)func_80085690(-(s16)(*(u16 *)(t + 0x36) - *(u16 *)(a + 0x36)), (s16)(*(u16 *)(t + 0x2E) - *(u16 *)(a + 0x2E))), H(a, 0x60), 0)) {
            a[6] = 3;
            a[7] = 0;
            break;
        }
        w = D_8013723C[a[0xBF]];
        if (a[0xBE] == 0) {
            H(a, 0x44) = w;
        } else {
            H(a, 0x44) = -w;
        }
        func_8004130C(a, 0);
        a[7] = 0;
        a[6]++;
        break;
    case 1:
        func_80041A1C(a, 2);
        func_80041AC0(a);
        H(a, 0x32) += 8;
        func_80041938(a, 0, 0);
        if (func_80120804(a) != 0) {
            a[6]++;
            break;
        }
        if (inl_80122CAC(a) != 0) {
            a[6]++;
            break;
        }
        r = inl_near(a);
        switch (r) {
        case 0:
            a[5] = 0;
            a[6] = 0;
            a[7] = 0;
            break;
        case 1:
            a[6] = 0;
            break;
        case 2:
            a[5] = 4;
            a[6] = 0;
            a[7] = 0;
            break;
        }
        break;
    case 2:
        if (inl_80122D70(a) != 0) {
            w = D_8013723C[a[0xBF]];
            if (a[0xBE] == 0) {
                H(a, 0x44) = w;
            } else {
                H(a, 0x44) = -w;
            }
            func_8004130C(a, 0);
            H(a, 0x42) = 0xF;
            a[6] = 4;
            a[7] = 0;
        }
        break;
    case 3:
        if (inl_80122D70(a) != 0) {
            w = D_8013723C[a[0xBF]];
            if (a[0xBE] == 0) {
                H(a, 0x44) = w;
            } else {
                H(a, 0x44) = -w;
            }
            func_8004130C(a, 0);
            a[6] = 0;
            a[7] = 0;
        }
        break;
    case 4:
        func_80041A1C(a, 2);
        func_8004954C(a, H(a, 0x80), -0x5A);
        func_80041AC0(a);
        H(a, 0x32) += 8;
        func_80041938(a, 0, 0);
        if (--H(a, 0x42) == 0) {
            a[5] = 2;
            a[6] = 0;
            a[7] = 0;
        }
        break;
    }
    func_801208B4(a);
}

/* tools/dispatch.py draft of func_80121BAC (a01, 0x3a8 bytes): 4 inlined bodies
 * register maps (body -> here): 
 *   inl_80122E3C (a01:func_80122E3C, cover 1.00, regs 1.00): s0->s1
 *   inl_80122D70 (a01:func_80122D70, cover 1.00, regs 0.89): v1->v0, s0->s1, s1->s0
 *   inl_80122B78 (a01:func_80122B78, cover 1.00, regs 1.00): t0->s1
 *   inl_80122C08 (a01:func_80122C08, cover 1.00, regs 1.00): a3->s1, t0->a3
 * notes:
 *   func_80122D70: the target's helper inl_80122D70
 *   inl_80122E3C: replaces 80121BF0-80121C3C
 *   inl_80122D70: replaces 80121C5C-80121CFC
 *   inl_80122B78: replaces 80121D80-80121E00
 *   inl_80122C08: replaces 80121E78-80121F0C
 * next: fix the draft's types and the helper calls' arguments, then
 *   python3 -I tools/ccheck.py THIS.c --prog a01 --func func_80121BAC --sbs
 *   python3 -I tools/install_c.py THIS.c --prog a01 */

/* func_80122B78, inlined */
static inline s32 inl_80122B78(u8 *a) {
    u8 *p = M2C_FIELD(a, u8 **, 0x10);
    s32 r = 0;
    s16 h;

    if (p != NULL) {
        h = M2C_FIELD(p, s32 *, 0x34) >> 16;
        h += 0x10;
        if (h > 0x200) {
            h = 0x200;
            r = 1;
        }
        M2C_FIELD(a, s16 *, 0x72) = (0xA0 - h) / 2;
        M2C_FIELD(a, s16 *, 0x6A) = h;
        M2C_FIELD(p, s32 *, 0x34) = (h << 16) + 0x100;
    } else {
        r = 1;
        M2C_FIELD(a, s16 *, 0x72) = -0xB0;
        M2C_FIELD(a, s16 *, 0x6A) = 0x200;
    }
    return r;
}
/* func_80122C08, inlined */
static inline s32 inl_80122C08(u8 *a) {
    u8 *p;
    s32 r = 0;
    s16 h;
    s16 d;
    s32 y;

    if (M2C_FIELD(a, u8 **, 0x10) != NULL) {
        p = M2C_FIELD(a, u8 **, 0x10);
        y = M2C_FIELD(p, s16 *, 0x36);
        d = y - 0xA0;
        if (abs(d) <= 0x10) {
            h = 0xA0;
            r = 1;
        } else if (d < 0) {
            h = y + 0x10;
        } else {
            h = y - 0x10;
        }
        M2C_FIELD(a, s16 *, 0x72) = (0xA0 - h) / 2;
        M2C_FIELD(a, s16 *, 0x6A) = h;
        M2C_FIELD(p, s32 *, 0x34) = (h << 16) + 0x100;
    } else {
        r = 1;
        M2C_FIELD(a, s16 *, 0x72) = 0;
        M2C_FIELD(a, s16 *, 0x6A) = 0xA0;
    }
    return r;
}
void func_80121BAC(u8 *a)
{
    u8 b;
    s32 r;

    switch (a[6]) {
    case 0:
        b = a[0xBE];
        if (b == inl_80122E3C(a)) {
            a[6] = 2;
        } else {
            a[6] = a[6] + 1;
        }
        a[7] = 0;
        break;
    case 1:
        if (inl_80122D70(a) != 0) {
            a[7] = 0;
            a[6]++;
        }
        break;
    case 2:
        a[3] = 0;
        M2C_FIELD(a, s16 *, 0xE) = 0;
        M2C_FIELD(a, u16 *, 0x40) = 0x1E;
        a[6]++;
        func_80074590(0x93, 0, 0);
        break;
    case 3:
        func_801208B4(a);
        func_801208B4(a);
        if (--M2C_FIELD(a, s16 *, 0x40) == 0) {
            a[3] = 1;
            M2C_FIELD(a, s16 *, 0xE) = 0;
            a[6]++;
        }
        break;
    case 4:
        r = inl_80122B78(a);
        func_801208B4(a);
        if (a[3] == 2 && r != 0) {
            M2C_FIELD(a, u16 *, 0x40) = 0x3C;
            a[6]++;
        }
        break;
    case 5:
        func_801208B4(a);
        if (--M2C_FIELD(a, s16 *, 0x40) == 0) {
            a[3] = 3;
            M2C_FIELD(a, s16 *, 0xE) = 0;
            a[6]++;
        }
        break;
    case 6:
        r = inl_80122C08(a);
        func_801208B4(a);
        if (a[3] == 0 && r != 0) {
            a[5] = 0;
            a[6] = 0;
            a[7] = 0;
        }
        break;
    }
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80121F54);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8012212C);

typedef struct { u8 b[6]; } Ent6;
#define P(p, o) (*(u8 **)((u8 *)(p) + (o)))
extern Ent6 D_80137214[];
extern u8 D_80137230[];
extern u8 D_800BF841;
extern u8 D_800E7EAA;
extern u8 D_800E7FC7;
static inline void sync_child(u8 *a) {
    u8 *p = P(a, 0x10);

    if (p != NULL) {
        H(p, 0x2C) = H(a, 0x2E);
        H(p, 0x2E) = H(a, 0x32) + H(a, 0x72);
        H(p, 0x30) = H(a, 0x36);
    }
}
void func_801222FC(u8 *a)
{
    u8 *p;
    u16 t;

    switch (a[4]) {
    case 0:
        if (func_80051B70(a, 0xC, 0x14) != 0) {
            break;
        }
        H(a, 0x80) = 0x78;
        H(a, 0x82) = 0xF0;
        H(a, 0x84) = 0x3C;
        H(a, 0x86) = 0x3C;
        H(a, 0x6A) = 0xA0;
        H(a, 0xBC) = 0x1000;
        H(a, 0xBA) = 0x1000;
        H(a, 0xB8) = 0x1000;
        H(a, 0x74) = a[3];
        a[4]++;
        a[3] = 0;
        a[0] = 1;
        a[0x29] = 0;
        a[0x2B] = 0;
        H(a, 0x72) = 0;
        H(P(a, 0xC0), 0xA) = -0x400;
        H(a, 0xE) = 0;
        func_80041194(a, 0, D_80137214[H(a, 0x74)].b[5], 0);
        func_8004130C(a, 1);
        a[0x5E] = 0;
        a[0xBF] = 0;
        W(a, 0x10) = 0;
        W(a, 0x14) = 0;
        a[5] = 7;
        a[0x47] = a[0xBE];
        break;
    case 1:
        if (H(a, 0x74) == 3 && D_800E7EAA == 0x10) {
            func_8007703C(a);
        } else {
            func_8007778C(a);
        }
        if (a[1] != 0) {
            if (a[0xBF] == 0 && a[0x5E] == 0) {
                p = func_8003116C(0x203, 0, 0);
                if (p != NULL) {
                    P(p, 0x10) = a;
                    P(a, 0x10) = p;
                    H(p, 0x2C) = H(a, 0x2E);
                    H(p, 0x2E) = H(a, 0x32) + H(a, 0x72);
                    H(p, 0x30) = H(a, 0x36);
                    W(p, 0x34) = (H(a, 0x6A) << 16) + 0x100;
                    a[0x5E] = 1;
                } else {
                    W(a, 0x10) = 0;
                    a[0x5E] = 0;
                }
            }
            func_80051844(a);
        } else if (a[0xBF] == 0 && a[0x5E] != 0 && P(a, 0x10) != NULL) {
            P(a, 0x10)[4] = 3;
            W(a, 0x10) = 0;
            a[0x5E] = 0;
        }
        if (a[0x2B] == 0) {
            switch (a[5]) {
            case 0:
                func_80120DA0(a);
                break;
            case 1:
                switch (a[6]) {
                case 0:
                    func_80113CB4(a);
                    H(a, 0x40) = D_80137230[func_8009A450() & 3] << 6;
                    a[6]++;
                    break;
                case 1:
                    if (--H(a, 0x40) == 0) {
                        a[5] = 2;
                        a[6] = 0;
                        a[7] = 0;
                        if (P(a, 0x14) != NULL) {
                            P(a, 0x14)[4] = 3;
                        }
                    }
                    break;
                }
                func_801208B4(a);
                break;
            case 2:
                func_80120F00(a);
                break;
            case 3:
                func_801210A4(a);
                break;
            case 4:
                func_801213F4(a);
                break;
            case 5:
                func_80121678(a);
                break;
            case 6:
                func_80121BAC(a);
                break;
            case 7:
                func_80120C34(a);
                break;
            }
        } else {
            a[0x2B]--;
        }
        sync_child(a);
        a[0x29] = 0;
        break;
    case 2:
        func_8007778C(a);
        switch (a[5]) {
        case 0:
        case 5:
        case 6:
        case 8:
            a[0x2B] = 0;
            a[0] = 1;
            a[4] = 1;
            a[5] = 0;
            a[6] = 0;
            a[7] = 0;
            break;
        case 1:
            switch (a[6]) {
            case 0:
                a[0xBE] = func_80077768(H(a, 0x56), H(a, 0x60), 0);
                func_8004130C(a, 0);
                a[3] = 2;
                func_80051B04(W(a, 0xC0), 0xC, 0x2D);
                H(a, 0xE) = 0;
                a[6]++;
                func_80026100(4);
                H(a, 0x50) = 0;
            case 1:
                if (D_1F800137 == 0 && D_800BF841 == 0) {
                    if (D_800E7FC7 == 0) {
                        H(a, 0x44) = 0x2400;
                        a[0xBE] = 0;
                    } else {
                        H(a, 0x44) = -0x2400;
                        a[0xBE] = 1;
                    }
                    func_8004130C(a, 0);
                    func_80041A1C(a, 0);
                    if (H(a, 0x74) == 3 && H(a, 0x36) >= 0x3B8F) {
                        H(a, 0x36) = 0x3B8E;
                    }
                    func_8004954C(a, H(a, 0x80), -0x5A);
                    func_80041AC0(a);
                    D_800E7EAA = a[0x2A];
                    H(a, 0x32) += 8;
                    func_80041938(a, 0, 0);
                    if (a[0x29] == 0) {
                        H(a, 0x4A) = 0;
                        H(a, 0x50) += 0x300;
                        if (H(a, 0x50) > 0x3000) {
                            H(a, 0x50) = 0x3000;
                        }
                        W(a, 0x30) += H(a, 0x50) << 8;
                    } else {
                        H(a, 0x50) = 0;
                    }
                }
                func_801208B4(a);
                t = ((u32)U(P(a, 0xC0), 0x3A) * 25) >> 10;
                H(a, 0x84) = t;
                H(a, 0x86) = t;
                break;
            case 2:
                H(a, 0xBC) = 0x1000;
                H(a, 0xBA) = 0x1000;
                H(a, 0xB8) = 0x1000;
                func_80051B04(W(a, 0xC0), 0xC, 0x2F);
                H(a, 0xE) = 0;
                a[6]++;
                break;
            }
            break;
        case 11:
            if (func_80080750(a, 0, 0) != 0) {
                if (P(a, 0x10) != NULL) {
                    P(a, 0x10)[4] = 3;
                    W(a, 0x10) = 0;
                    a[0x5E] = 0;
                }
                a[4] = 3;
                break;
            }
            a[5] = 2;
        case 2:
        case 3:
            func_8012212C(a);
            break;
        case 4:
        case 7:
            func_80121F54(a);
            break;
        case 9:
        case 10:
            break;
        }
        a[0x29] = 0;
        if (a[1] != 0) {
            func_80051844(a);
            sync_child(a);
        }
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

void func_80122A2C(u8 *a) {
    u8 *p;

    if (a[0xBF] != 0 || a[0x5E] != 0) {
        return;
    }
    p = func_8003116C(0x203, 0, 0);
    if (p != NULL) {
        M2C_FIELD(p, u8 **, 0x10) = a;
        M2C_FIELD(a, u8 **, 0x10) = p;
        M2C_FIELD(p, s16 *, 0x2C) = M2C_FIELD(a, s16 *, 0x2E);
        M2C_FIELD(p, s16 *, 0x2E) = M2C_FIELD(a, s16 *, 0x32) + M2C_FIELD(a, s16 *, 0x72);
        M2C_FIELD(p, s16 *, 0x30) = M2C_FIELD(a, s16 *, 0x36);
        M2C_FIELD(p, s32 *, 0x34) = (M2C_FIELD(a, s16 *, 0x6A) << 16) + 0x100;
        a[0x5E] = 1;
    } else {
        M2C_FIELD(a, u8 **, 0x10) = NULL;
        a[0x5E] = 0;
    }
}

void func_80122ADC(s32 arg0) {
    void *temp_a1;

    temp_a1 = M2C_FIELD(arg0, void **, 0x10);
    if (temp_a1 != NULL) {
        M2C_FIELD(temp_a1, u16 *, 0x2C) = (u16) M2C_FIELD(arg0, u16 *, 0x2E);
        M2C_FIELD(temp_a1, s16 *, 0x2E) = (s16) (M2C_FIELD(arg0, u16 *, 0x32) + M2C_FIELD(arg0, u16 *, 0x72));
        M2C_FIELD(temp_a1, u16 *, 0x30) = (u16) M2C_FIELD(arg0, u16 *, 0x36);
    }
}

void func_80122B20(s32 arg0)
{
  void *temp_v1;
  ;
  if ((*((void **) (((signed char *) arg0) + 0x10))) != 0)
  {
    *((s8 *) (((signed char *) (*((void **) (((signed char *) arg0) + 0x10)))) + 4)) = 3;
    *((void **) (((signed char *) arg0) + 0x10)) = 0;
    *((s8 *) (((signed char *) arg0) + 0x5E)) = 0;
  }
  return 3;
}

void func_80122B44(void *arg0, M2C_UNK arg1) {
    func_80051B04(M2C_FIELD(arg0, s32 *, 0xC0), 0xC, arg1);
    M2C_FIELD(arg0, s16 *, 0xE) = 0;
}

s32 func_80122B78(u8 *a) {
    u8 *p = M2C_FIELD(a, u8 **, 0x10);
    s32 r = 0;
    s16 h;

    if (p != NULL) {
        h = M2C_FIELD(p, s32 *, 0x34) >> 16;
        h += 0x10;
        if (h > 0x200) {
            h = 0x200;
            r = 1;
        }
        M2C_FIELD(a, s16 *, 0x72) = (0xA0 - h) / 2;
        M2C_FIELD(a, s16 *, 0x6A) = h;
        M2C_FIELD(p, s32 *, 0x34) = (h << 16) + 0x100;
    } else {
        r = 1;
        M2C_FIELD(a, s16 *, 0x72) = -0xB0;
        M2C_FIELD(a, s16 *, 0x6A) = 0x200;
    }
    return r;
}

s32 func_80122C08(u8 *a) {
    u8 *p;
    s32 r = 0;
    s16 h;
    s16 d;
    s32 y;

    if (M2C_FIELD(a, u8 **, 0x10) != NULL) {
        p = M2C_FIELD(a, u8 **, 0x10);
        y = M2C_FIELD(p, s16 *, 0x36);
        d = y - 0xA0;
        if (abs(d) <= 0x10) {
            h = 0xA0;
            r = 1;
        } else if (d < 0) {
            h = y + 0x10;
        } else {
            h = y - 0x10;
        }
        M2C_FIELD(a, s16 *, 0x72) = (0xA0 - h) / 2;
        M2C_FIELD(a, s16 *, 0x6A) = h;
        M2C_FIELD(p, s32 *, 0x34) = (h << 16) + 0x100;
    } else {
        r = 1;
        M2C_FIELD(a, s16 *, 0x72) = 0;
        M2C_FIELD(a, s16 *, 0x6A) = 0xA0;
    }
    return r;
}

s32 func_80122CAC(u8 *a) {
    if (func_80049280(a, (M2C_FIELD(a, s16 *, 0x44) >> 8) + 0x20, (M2C_FIELD(a, s16 *, 0x4A) * M2C_FIELD(a, s16 *, 0x44)) >> 16) == 0 &&
        M2C_FIELD(a, s16 *, 0x32) - D_1F8001A4 < -500) {
        return 1;
    }
    if (a[0x2A] != 0x10) {
        return 0;
    }
    if (M2C_FIELD(a, s16 *, 0x36) < 0x36D9) {
        return 0;
    }
    M2C_FIELD(a, s16 *, 0x36) = 0x36D8;
    return 1;
}

s32 func_80122D4C(u8 *a) {
    return func_8004954C(a, M2C_FIELD(a, s16 *, 0x80), -0x5A) != 0;
}

s32 func_80122D70(u8 *a) {
    switch (a[7]) {
    case 0:
        M2C_FIELD(a, s16 *, 0x58) = 0;
        if (a[0xBE] == 0) {
            M2C_FIELD(a, s16 *, 0x64) = (M2C_FIELD(a, u16 *, 0x60) + 0x800) & 0xFFF;
        } else {
            M2C_FIELD(a, s16 *, 0x64) = M2C_FIELD(a, u16 *, 0x60);
        }
        a[7]++;
        break;
    case 1:
        M2C_FIELD(a, s16 *, 0x56) = func_800776F8(M2C_FIELD(a, s16 *, 0x64), M2C_FIELD(a, s16 *, 0x56), 0x100);
        if (M2C_FIELD(a, s16 *, 0x64) == M2C_FIELD(a, s16 *, 0x56)) {
            a[0xBE] = 1 - a[0xBE];
            return 1;
        }
        break;
    }
    return 0;
}

s32 func_80122E3C(u8 *a) {
    u8 *g = D_800E7E80;
    s16 dz = M2C_FIELD(g, s16 *, 0x36) - M2C_FIELD(a, s16 *, 0x36);
    s16 dx = M2C_FIELD(g, s16 *, 0x2E) - M2C_FIELD(a, s16 *, 0x2E);

    return func_80077768((s16)func_80085690(-dz, dx), M2C_FIELD(a, s16 *, 0x60), 0);
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80122EA8);

void func_80122F80(u8 *a, s32 b) {
    if (a[0xBE] == 0) {
        M2C_FIELD(a, s16 *, 0x44) = b;
    } else {
        M2C_FIELD(a, s16 *, 0x44) = -b;
    }
    func_8004130C(a, 0);
}

void func_80122FBC(u8 *a) {
    u8 *p;

    switch (a[6]) {
    case 0:
        func_80113CB4(a);
        M2C_FIELD(a, s16 *, 0x40) = D_80137230[func_8009A450() & 3] << 6;
        a[6]++;
        break;
    case 1:
        if (--M2C_FIELD(a, s16 *, 0x40) == 0) {
            p = M2C_FIELD(a, u8 **, 0x14);
            a[5] = 2;
            a[6] = 0;
            a[7] = 0;
            if (p != NULL) {
                p[4] = 3;
            }
        }
        break;
    }
    func_801208B4(a);
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80123078);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8012322C);

extern s32 D_800ECF90;
extern s32 D_800ECFB4;
extern u8 D_80135894[];
u8 *func_8007A980();
u8 *func_8012B654(s32 a, s32 b);
void func_801233A8(u8 *a)
{
    s32 k;
    u8 *p;
    s32 t;

    switch (a[4]) {
    case 0:
        W(a, 0x3C) = D_800ECF90;
        func_80040CDC(a, D_801393C0_27b3, D_800A3D18);
        if (a[3] == 0) {
            k = 0x10;
            a[0x7B] = 1;
        } else {
            k = 0xF;
            a[0x7B] = 0;
        }
        if (func_800519E0(a, k, D_800ECFB4, D_80135894) != 0) {
            break;
        }
        a[0xB] = 0x40;
        a[0] = 9;
        H(a, 0x80) = 0xAA;
        H(a, 0x82) = 0x154;
        H(a, 0x84) = 0x90;
        H(a, 0x86) = 0xF0;
        a[0x2B] = 0;
        a[0x29] = 0;
        H(a, 0x58) = 0;
        H(a, 0x56) = 0;
        H(a, 0x54) = 0;
        a[4]++;
        switch (t = a[3]) {
        case 0:
            W(a, 0x2C) = 0x316A0000;
            W(a, 0x30) = 0xEF520000;
            W(a, 0x34) = 0x3D540000;
            a[0x2A] = 0xF;
            H(a, 0x56) = 0x400;
            H(a, 0x40) = 0;
            func_80051B04(*(s32 *)(a + ((a[9] - 1) << 2) + 0xC0), 1, 0x12);
            break;
        case 1:
            p = func_8007A980(1, 5, 0);
            if (p == NULL) {
                a[4] = 2;
                break;
            }
            p[2] = 3;
            H(p, 0x2E) = 0x2FEE;
            H(p, 0x32) = -0x1068;
            H(p, 0x36) = 0x3F16;
            *(void **)(p + 0x1C) = f_UpdatePipeAreaQuestPickupActor;
            p[3] = t;
            p[0x28] |= 0x80;
            a[0] = 2;
            W(a, 0x2C) = 0x30700000;
            W(a, 0x30) = 0xEF520000;
            W(a, 0x34) = 0x3A340000;
            a[0x2A] = 0xF;
            H(a, 0x56) = 0xC00;
            W(a, 0x14) = func_8012B654(a, 1);
            break;
        }
        func_80041718(a, a[0x7B], 0);
        break;
    case 1:
        switch (a[3]) {
        case 0:
            func_80123078(a);
            break;
        case 1:
            func_8012322C(a);
            break;
        }
        if (a[1] != 0) {
            func_800518FC(a);
        }
        a[0x2B] = 0;
        a[0x29] = 0;
        break;
    case 2:
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

s32 func_8012364C(u8 *a) {
    switch (a[0x78]) {
    case 0:
        func_8011A43C(a, 0);
        D_800BF9EB = 0;
        a[0x78]++;
        break;
    case 1:
        if (D_800BF9EB == 2) {
            return 1;
        }
        break;
    }
    return 0;
}

/* func_80123A48, inlined */
static inline void inl_80123A48(u8 *a) {
    u8 *p = func_8003116C(0x201, 0, 0);

    if (p != NULL) {
        M2C_FIELD(p, u8 **, 0x10) = a;
        p[7] = 0;
    }
    M2C_FIELD(a, u8 **, 0x14) = p;
    M2C_FIELD(a, s16 *, 0x80) = 0x64;
    M2C_FIELD(a, s16 *, 0x82) = 0xC8;
    M2C_FIELD(a, s16 *, 0x84) = 0x100;
    M2C_FIELD(a, s16 *, 0x86) = 0x100;
    a[0x5E] = 0;
}
/* func_80123AAC, inlined */
static inline void inl_80123AAC(u8 *a) {
    u8 *p = func_8003116C(0x202, 0, 0);

    if (p != NULL) {
        M2C_FIELD(p, u8 **, 0x10) = a;
        M2C_FIELD(p, s16 *, 0x2C) = M2C_FIELD(a, s16 *, 0x2E);
        M2C_FIELD(p, s16 *, 0x2E) = M2C_FIELD(a, s16 *, 0x32) - 0x30;
        M2C_FIELD(p, s16 *, 0x30) = M2C_FIELD(a, s16 *, 0x36);
        p[7] = 2;
    }
    M2C_FIELD(a, s16 *, 0x80) = 0xC8;
    M2C_FIELD(a, s16 *, 0x82) = 0x190;
    M2C_FIELD(a, s16 *, 0x84) = 0x2D0;
    M2C_FIELD(a, u8 **, 0x14) = p;
    M2C_FIELD(a, s16 *, 0x86) = 0x310;
    a[0x5E] = 0;
}
/* func_80123B40, inlined */
static inline void inl_80123B40(void *arg0) {
    u8 temp_v0;
    void *temp_v1;
    void *temp_v1_2;

    temp_v1 = M2C_FIELD(arg0, void **, 0x10);
    M2C_FIELD(arg0, u16 *, 0x2E) = (u16) M2C_FIELD(temp_v1, u16 *, 0x2E);
    M2C_FIELD(arg0, u16 *, 0x32) = (u16) M2C_FIELD(temp_v1, u16 *, 0x32);
    M2C_FIELD(arg0, u16 *, 0x36) = (u16) M2C_FIELD(temp_v1, u16 *, 0x36);
    temp_v0 = M2C_FIELD(temp_v1, u8 *, 1);
    M2C_FIELD(arg0, u8 *, 1) = temp_v0;
    if (temp_v0 & 0xFF) {
        func_80077E7C(arg0);
    }
    temp_v1_2 = M2C_FIELD(arg0, void **, 0x14);
    M2C_FIELD(temp_v1_2, u16 *, 0x2C) = (u16) M2C_FIELD(arg0, u16 *, 0x2E);
    M2C_FIELD(temp_v1_2, s16 *, 0x2E) = (s16) (M2C_FIELD(arg0, u16 *, 0x32) - 0x40);
    M2C_FIELD(temp_v1_2, u16 *, 0x30) = (u16) M2C_FIELD(arg0, u16 *, 0x36);
}
void f_UpdatePipeAreaPersistentSceneryRewardActor(u8 *a)
{
    u8 *p;
    s32 k;

    switch (a[4]) {
    case 0:
        a[8] = 0;
        a[9] = 0;
        a[0] = 9;
        a[0xB] = 0;
        a[0x29] = 0;
        a[4]++;
        if (D_800BF870.unk0 == 1) {
            switch (a[3]) {
            case 0:
                inl_80123A48(a);
                break;
            case 1:
            case 3:
                inl_80123AAC(a);
                break;
            }
        }
        break;
    case 1:
        switch (a[3]) {
        case 0:
            inl_80123B40(a);
            break;
        case 1:
        case 3:
            func_8007778C(a);
            break;
        }
        break;
    case 2:
        switch (a[5]) {
        case 0:
            a[0] = 1;
            a[4] = 1;
            a[5] = 1;
            break;
        case 1:
        case 5:
        case 6:
            break;
        case 2:
        case 3:
        case 4:
        case 7:
            a[0] = 2;
            a[4] = 3;
            if (a[3] == 3) {
                D_800BF870.pad1[0x18B] |= 0x40;
            } else if (a[3] == 1) {
                D_800BF870.pad1[0x18B] |= 0x80;
            } else if (a[3] == 0) {
                p = M2C_FIELD(a, u8 **, 0x10);
                p[0] = 1;
                D_800BF870.pad1[0x195] |= 1;
            }
            p = M2C_FIELD(a, u8 **, 0x14);
            if (p != NULL && p[4] < 2) {
                p[4] = 2;
                M2C_FIELD(a, u8 **, 0x14) = NULL;
            }
            break;
        }
        break;
    case 3:
        p = M2C_FIELD(a, u8 **, 0x14);
        if (p != NULL && p[4] < 2) {
            p[4] = 2;
        }
        func_8007A624(a);
        break;
    }
}

void func_80123A48(u8 *a) {
    u8 *p = func_8003116C(0x201, 0, 0);

    if (p != NULL) {
        M2C_FIELD(p, u8 **, 0x10) = a;
        p[7] = 0;
    }
    M2C_FIELD(a, u8 **, 0x14) = p;
    M2C_FIELD(a, s16 *, 0x80) = 0x64;
    M2C_FIELD(a, s16 *, 0x82) = 0xC8;
    M2C_FIELD(a, s16 *, 0x84) = 0x100;
    M2C_FIELD(a, s16 *, 0x86) = 0x100;
    a[0x5E] = 0;
}

void func_80123AAC(u8 *a) {
    u8 *p = func_8003116C(0x202, 0, 0);

    if (p != NULL) {
        M2C_FIELD(p, u8 **, 0x10) = a;
        M2C_FIELD(p, s16 *, 0x2C) = M2C_FIELD(a, s16 *, 0x2E);
        M2C_FIELD(p, s16 *, 0x2E) = M2C_FIELD(a, s16 *, 0x32) - 0x30;
        M2C_FIELD(p, s16 *, 0x30) = M2C_FIELD(a, s16 *, 0x36);
        p[7] = 2;
    }
    M2C_FIELD(a, s16 *, 0x80) = 0xC8;
    M2C_FIELD(a, s16 *, 0x82) = 0x190;
    M2C_FIELD(a, s16 *, 0x84) = 0x2D0;
    M2C_FIELD(a, u8 **, 0x14) = p;
    M2C_FIELD(a, s16 *, 0x86) = 0x310;
    a[0x5E] = 0;
}

void func_80123B40(void *arg0) {
    u8 temp_v0;
    void *temp_v1;
    void *temp_v1_2;

    temp_v1 = M2C_FIELD(arg0, void **, 0x10);
    M2C_FIELD(arg0, u16 *, 0x2E) = (u16) M2C_FIELD(temp_v1, u16 *, 0x2E);
    M2C_FIELD(arg0, u16 *, 0x32) = (u16) M2C_FIELD(temp_v1, u16 *, 0x32);
    M2C_FIELD(arg0, u16 *, 0x36) = (u16) M2C_FIELD(temp_v1, u16 *, 0x36);
    temp_v0 = M2C_FIELD(temp_v1, u8 *, 1);
    M2C_FIELD(arg0, u8 *, 1) = temp_v0;
    if (temp_v0 & 0xFF) {
        func_80077E7C();
    }
    temp_v1_2 = M2C_FIELD(arg0, void **, 0x14);
    M2C_FIELD(temp_v1_2, u16 *, 0x2C) = (u16) M2C_FIELD(arg0, u16 *, 0x2E);
    M2C_FIELD(temp_v1_2, s16 *, 0x2E) = (s16) (M2C_FIELD(arg0, u16 *, 0x32) - 0x40);
    M2C_FIELD(temp_v1_2, u16 *, 0x30) = (u16) M2C_FIELD(arg0, u16 *, 0x36);
}

void func_80123BD8(void) {
    func_8007778C();
}

void func_80123BF8(u8 *a) {
    u8 *p;
    s32 k;

    switch (a[5]) {
    case 0:
        a[0] = 1;
        a[4] = 1;
        a[5] = 1;
        break;
    case 2:
    case 3:
    case 4:
    case 7:
        a[0] = 2;
        a[4] = 3;
        k = a[3];
        if (k == 3) {
            D_800BF870.pad1[0x18B] |= 0x40;
        } else if (k == 1) {
            D_800BF870.pad1[0x18B] |= 0x80;
        } else if (k == 0) {
            p = *(u8 **)(a + 0x10);
            *p = 1;
            D_800BF870.pad1[0x195] |= 1;
        }
        p = *(u8 **)(a + 0x14);
        if (p != NULL && p[4] < 2) {
            p[4] = 2;
            *(u8 **)(a + 0x14) = NULL;
        }
        break;
    case 1:
    case 5:
    case 6:
        break;
    }
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80123CFC);

void func_80123CFC();
s32 func_80123F28(u8 *a) {
    u8 *g = (u8 *)&D_800BF870;
    u8 *e;

    if (g[0xC6] & 0x4) {
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
    M2C_FIELD(e, void **, 0x1C) = func_80123CFC;
    M2C_FIELD(e, s16 *, 0x2E) = M2C_FIELD(a, s16 *, 0x2E);
    M2C_FIELD(e, s16 *, 0x32) = M2C_FIELD(a, s16 *, 0x32);
    M2C_FIELD(e, s16 *, 0x36) = M2C_FIELD(a, s16 *, 0x36);
    e[0x2A] = a[0x2A];
    g[0x164] = 1;
    func_8003116C(0x30, e + 0x2C, -0xA);
    func_80074590(0x37, 0x20, 0);
    return 1;
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80123FF8);

void func_80124164(u8 *a) {
    u8 *g = D_800E7E80;

    if (D_1F800160_71b4 < 0x19B8) {
        return;
    }
    switch (a[6]) {
    case 0:
        if (M2C_FIELD(g, s16 *, 0x2E) < 0x1C4D) {
            D_1F800190 = D_1F80016C;
            a[6]++;
        }
        break;
    case 1:
        if (M2C_FIELD(g, s16 *, 0x2E) < 0x1C4D) {
            D_1F800190 = D_1F80016C;
        } else {
            D_1F800190 = D_1F80016E;
            a[6]++;
        }
        break;
    case 2:
        if (g[0x147] != 0) {
            D_1F800190 = 0;
            a[6]++;
        } else {
            D_1F800190 = D_1F80016E;
        }
        break;
    }
}

typedef struct { s16 x, y; } Ofs4250;
extern Ofs4250 D_801375A4[];
void func_80124250(u8 *a) {
    s16 v[6];
    u8 *p;

    func_80124164(a);
    switch (a[5]) {
    case 0:
        H(a, 0x42) = 0;
        a[5]++;
    case 1:
        if (!(D_1F80017C & 3)) {
            v[1] = H(a, 0x2E) + D_801375A4[H(a, 0x42)].x;
            v[3] = H(a, 0x32) + D_801375A4[H(a, 0x42)].y;
            v[5] = H(a, 0x36) - 0x64;
            func_8003116C(0xE, v, -0xA);
            if (++H(a, 0x42) >= 8) {
                H(a, 0x42) = 0x1E;
                a[5]++;
            }
        }
        break;
    case 2:
        if (--H(a, 0x42) == -1) {
            H(a, 0x52) = -0x60;
            a[5]++;
            func_800310F4(0x207, -0xA);
            func_80074590(0x99, 0, 0);
        }
        break;
    case 3:
        H(*(u8 **)(a + 0xC0), 8) += 0x10;
        H(*(u8 **)(a + 0xC0), 4) += H(a, 0x52);
        if ((H(a, 0x52) += 4) >= -7) {
            H(a, 0x52) = -8;
        }
        if (H(*(u8 **)(a + 0xC0), 4) < -0x240) {
            H(a, 0x42) = 0x3C;
            H(a, 0x50) = -0x40;
            a[5]++;
        }
        break;
    case 4:
        H(*(u8 **)(a + 0xC0), 8) += 0xA0;
        H(*(u8 **)(a + 0xC0), 2) += H(a, 0x50);
        H(*(u8 **)(a + 0xC0), 4) += H(a, 0x52);
        H(a, 0x50) += 4;
        if (--H(a, 0x42) == -1) {
            a[8] = 0;
            a[5]++;
            *(s32 *)(*(u8 **)(a + 0xC0) + 0x40) = 0;
        }
        break;
    case 5:
        func_80042310();
        a[0x5E] = 2;
        a[0xBF] = 0;
        a[5] = 0;
        a[6] = 0;
        break;
    }
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_801244E4);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8012464C);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_801247C8);

INCLUDE_ASM("asm/a01/nonmatchings/a01", f_UpdateMythicalTowerEntranceTransition);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80124CF8);

extern u8 D_1F800236;
void func_80124F14(u8 *a) {
    u8 one;
    switch (a[5]) {
    case 0:
        if (D_800BF871 == H(a, 0x7C)) {
            H(a, 0x40) = 0xF;
            H(a, 0x50) = 0x400;
            a[5]++;
            func_80072EFC(a);
            a[0] = 2;
        } else {
            a[5] = 4;
        }
        break;
    case 1:
        if (--H(a, 0x40) == -1) {
            a[5]++;
        }
        break;
    case 2:
        if (func_80072F14(a) != 0) {
            a[5]++;
        }
        break;
    case 3:
        if (D_800E7EAA != a[0x2A]) {
            a[0] = 1;
            a[5]++;
        }
        break;
    case 4:
        if (D_800E7E80[0x2A] == a[0x2A] && (D_800E7E80[5] == 0 || a[0x29] != 0)) {
            a[0] = 2;
            a[5]++;
            D_1F800137 = 2;
            one = 1;
            D_800BF808[0x31] = one;
            D_800BF808[7] = 2;
            H(D_800BF808, 0x32) = H(a, 0x7A);
            D_1F800236 = 1;
            func_80074590(0x17, 0, 0xF);
        }
        break;
    case 5:
        if (func_80072E60(a) != 0) {
            a[5]++;
        }
        break;
    }
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_801250B8);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80125214);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80125304);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8012540C);

#define TH(p, o) (*(s16 *)((u8 *)(p) + (o)))
static inline void f125548_start(u8 *p) {
    TH(p, 0x40) = 0xF;
    p[0] = 2;
    TH(p, 0x50) = 0x400;
    p[5]++;
    func_80072EFC(p);
}
void func_80125548(u8 *a) {
    u8 *t = D_800E7E80;
    u8 *g;

    switch (a[5]) {
    case 0:
        if (D_800BF871 == 0x20) {
            f125548_start(a);
        } else {
            a[5] = 3;
        }
        break;
    case 1:
        if (--TH(a, 0x40) == -1) {
            a[5]++;
        }
        break;
    case 2:
        if (func_80072F14(a) != 0) {
            a[0] = 1;
            a[5]++;
            D_800BF871 = 0x1F;
        }
        break;
    case 3:
        if (a[0x29] != 0 && t[0x29] != 0 && t[0x17B] == 0) {
            a[5]++;
            D_1F800137 = 2;
            func_80074590(0x17, 0, 0xF);
        }
        break;
    case 4:
        if (func_80072E60(a) != 0) {
            g = (u8 *)D_800BF808;
            a[5]++;
            D_1F800236 = 0;
            g[0x31] = 1;
            g[7] = 2;
            TH(g, 0x32) = 0x900;
        }
        break;
    }
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_801256EC);

typedef struct { s16 x, y, z; u8 b6; u8 pad7; s16 h8, hA; } DoorPt;
extern u8 D_801374C4[];
extern u8 D_801374D4[];
extern DoorPt D_801374E4[];
extern u8 D_800BF9FC;
extern u8 D_800BF916;
extern u8 D_800BFA3E;
extern u8 D_800BF9DB;
extern u8 D_800E7FF4;
extern s8 D_800BF81F;
void func_8012B324();
void f_UpdatePipeAreaEntranceAndDoorActor(u8 *a)
{
    u8 v;
    u8 *g;
    u8 *g2;
    u8 *e;
    u8 *p;

    switch (a[4]) {
    case 0:
        if (func_80051B70(a, 0xC, D_801374C4[a[3]]) != 0) {
            break;
        }
        a[4]++;
        a[0x28] |= 0x80;
        v = D_801374D4[a[3]];
        if (v != 0) {
            a[0x2A] = v;
            H(a, 0x60) = D_801374E4[a[3]].x - H(a, 0x2E);
            H(a, 0x62) = D_801374E4[a[3]].y;
            H(a, 0x64) = D_801374E4[a[3]].z - H(a, 0x36);
            a[0x5F] = D_801374E4[a[3]].b6;
            H(a, 0x82) = D_801374E4[a[3]].h8;
            H(a, 0x80) = H(a, 0x82) / 2;
            {
                s16 t = D_801374E4[a[3]].hA;
                a[0] = 1;
                H(a, 0x86) = t;
            }
            H(a, 0x84) = H(a, 0x86) / 2;
        }
        a[0x29] = 0;
        H(a, 0x50) = 0;
        H(a, 0x5A) = H(a, 0x56);
        switch (a[3]) {
        case 1:
            a[0x46] = 1;
            if (!(D_800BF9FC & 1)) {
                a[0xBF] = 1;
                a[0x5E] = 0;
            } else {
                a[0xBF] = 0;
                a[0x5E] = 2;
                a[8] = 0;
                func_800517F8(a);
            }
            break;
        case 2:
            g = (u8 *)D_800BF808;
            a[0x46] = 1;
            a[0xBF] = 0;
            a[8] = 0;
            if (g[0xE] != 0 && g[0xF] == 2) {
                a[4] = 1;
                a[5] = 0;
                a[6] = 2;
                func_80072EFC(a);
            }
            break;
        case 3:
            H(a, 0x8A) = -0x19C8;
            if (D_800BF8BF != 0xFF) {
                a[0x5E] = 0;
                break;
            }
            a[0x5E] = 2;
            p = func_80072DDC(a, 0, 4, 0x18);
            if (p != NULL) {
                *(void **)(p + 0x1C) = func_8012B324;
                p[3] = 0;
                H(p, 0x2E) = H(a, 0x2E) - 0x96;
                H(p, 0x32) = -0x17C0;
                H(p, 0x36) = H(a, 0x36);
            }
            break;
        case 0:
        case 4:
            a[0x46] = 1;
            a[0xBF] = 1;
            break;
        case 5:
            a[0xBF] = 1;
            a[0x46] = 0;
            if (D_800BF873 != 0) {
                func_80051B04(W(a, 0xC0), 0xC, 0x4B);
            }
            break;
        case 6:
            a[0x46] = 1;
            a[0xBF] = 1;
            if (D_800BF916 == 0) {
                a[0x5E] = 0;
            } else if (D_800BF916 < 3) {
                a[0x5E] = 1;
            } else {
                a[0x5E] = 2;
            }
            if (D_800BF873 != 0) {
                func_80051B04(W(a, 0xC0), 0xC, 0x4C);
            }
            break;
        case 7:
            a[0x46] = 1;
            a[0xBF] = 1;
            H(a, 0x7C) = 0x1B;
            H(a, 0x7A) = 0x508;
            break;
        case 8:
            a[0x46] = 1;
            a[0xBF] = 1;
            H(a, 0x7C) = 0x1C;
            H(a, 0x7A) = 0x60E;
            break;
        case 9:
            a[0x46] = 1;
            a[0xBF] = 1;
            H(a, 0x7C) = 0x1D;
            H(a, 0x7A) = 0x702;
            break;
        case 10:
            a[0x46] = 1;
            a[0xBF] = 1;
            H(a, 0x7C) = 0x1E;
            H(a, 0x7A) = 0x814;
            break;
        case 11:
            H(a, 0x7C) = 0x16;
            H(a, 0x7A) = 0x17;
            W(P(a, 0xC0), 0x40) = 0;
            break;
        case 12:
            H(a, 0x7C) = 0x17;
            H(a, 0x7A) = 0x16;
            W(P(a, 0xC0), 0x40) = 0;
            break;
        case 13:
            H(a, 0x7C) = 0x18;
            H(a, 0x7A) = 0x19;
            W(P(a, 0xC0), 0x40) = 0;
            break;
        case 14:
            H(a, 0x7C) = 0x19;
            H(a, 0x7A) = 0x18;
            W(P(a, 0xC0), 0x40) = 0;
            break;
        case 15:
            a[0x46] = 1;
            a[0xBF] = 1;
            if (D_800BFA3E < 3) {
                a[0x5E] = 0;
                break;
            }
            a[0x5E] = 2;
            func_80051B04(W(a, 0xC0), 0xC, 0x48);
            break;
        }
        break;
    case 1:
        g2 = (u8 *)D_800BF808;
        if (g2[0xE] != 0) {
            if (g2[0xF] == a[3]) {
                func_80077EBC(a);
            }
        } else {
            func_8007778C(a);
        }
        switch (a[3]) {
        case 0:
            e = D_800E7E80;
            switch (a[5]) {
            case 0:
                if (e[0x2A] == a[0x2A] && e[5] == 0) {
                    a[5] = 1;
                    D_1F800137 = 2;
                }
                break;
            case 1:
                a[5] = 2;
                a[0x29] = 1;
                D_800BF81F = (1 - a[0x5F]) << 4;
            case 2:
                if (func_80073328(a) != 0) {
                    a[5]++;
                }
                break;
            case 3:
                if (e[0x2A] != a[0x2A]) {
                    a[5] = 0;
                }
                break;
            }
            break;
        case 1:
            func_801244E4(a);
            break;
        case 2:
            func_80073328(a);
            func_800735F4(a, 0x52);
            break;
        case 3:
            switch (a[0x5E]) {
            case 0:
                if (((D_800BF9FD >> 2) & 3) == 3) {
                    a[0x5E] = 1;
                    a[5] = 0;
                    a[6] = 0;
                    a[7] = 0;
                } else {
                    func_800735F4(a, 0x4A);
                }
                break;
            case 1:
                func_8012464C(a);
                break;
            case 2:
                if (a[5] == 0) {
                    a[5] = 1;
                    H(a, 0x32) = H(a, 0x8A);
                }
                break;
            }
            break;
        case 4:
            func_801247C8(a);
            break;
        case 5:
            if (D_800E7FF4 & 4) {
                func_80073328(a);
            }
            func_800735F4(a, 0x67);
            break;
        case 6:
            switch (a[0x5E]) {
            case 0:
                switch (a[5]) {
                case 0:
                    if (D_800BF916 == 1) {
                        a[5] = 1;
                        func_800313A0(0x20A, a + 0x2C, -0x20, a + 0x54);
                        func_80074590(0xD, -0x1D, 0);
                    }
                    break;
                case 1:
                    if (D_800BF916 >= 2) {
                        a[0x5E] = 1;
                        a[5] = 0;
                    }
                    if (!(D_1F80017C & 0xF)) {
                        func_80074590(0xD, -0x1D, 0);
                    }
                    break;
                }
                a[1] = 0;
                break;
            case 1:
                f_UpdateMythicalTowerEntranceTransition(a);
                func_800735F4(a, 0x6A);
                break;
            case 2:
                func_80124CF8(a);
                func_800735F4(a, 0x6A);
                break;
            }
            break;
        case 7:
            if (D_800BF9DB & 2) {
                func_80124F14(a);
            } else {
                func_801250B8(a);
            }
            break;
        case 8:
            if (D_800BF9DB & 4) {
                func_80124F14(a);
            } else {
                func_801250B8(a);
            }
            break;
        case 9:
            if (D_800BF9DB & 8) {
                func_80124F14(a);
            } else {
                func_801250B8(a);
            }
            break;
        case 10:
            if (D_800BF9DB & 0x10) {
                func_80124F14(a);
            } else {
                func_801250B8(a);
            }
            break;
        case 11:
        case 12:
        case 13:
            func_80125214(a);
            break;
        case 14:
            func_80125304(a);
            break;
        case 15:
            func_801256EC(a);
            break;
        }
        if (a[1] != 0) {
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

void func_80126140(u8 *a) {
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
}

void func_8012623C(u8 *a) {
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
    if (D_800BF873 == 0) {
        func_800735F4(a, 0x48);
    }
}

void func_80126354(s32 arg0) {
    func_80073328();
    func_800735F4(arg0, 0x52);
}

void func_80126384(u8 *a) {
    if (((D_800BF9FD >> 2) & 3) == 3) {
        a[0x5E] = 1;
        a[5] = 0;
        a[6] = 0;
        a[7] = 0;
    } else {
        func_800735F4(a, 0x4A);
    }
}

void func_801263D4(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 5) == 0) {
        M2C_FIELD(arg0, u8 *, 5) = 1U;
        M2C_FIELD(arg0, u16 *, 0x32) = (u16) M2C_FIELD(arg0, u16 *, 0x8A);
    }
}

void func_801263F8(u8 *a) {
    switch (a[0x5E]) {
    case 0:
        if (((D_800BF9FD >> 2) & 3) == 3) {
            a[0x5E] = 1;
            a[5] = 0;
            a[6] = 0;
            a[7] = 0;
        } else {
            func_800735F4(a, 0x4A);
        }
        break;
    case 1:
        func_8012464C(a);
        break;
    case 2:
        if (a[5] == 0) {
            a[5] = 1;
            M2C_FIELD(a, s16 *, 0x32) = M2C_FIELD(a, s16 *, 0x8A);
        }
        break;
    }
}

void func_801264B4(s32 arg0) {
    if (D_800E7FF4 & 4) {
        func_80073328();
    }
    func_800735F4(arg0, 0x67);
}

void f_UpdateMythicalTowerEntranceEffect(u8 *a) {
    switch (a[0x5E]) {
    case 0:
        switch (a[5]) {
        case 0:
            if (D_800BF916 == 1) {
                a[5] = 1;
                func_800313A0(0x20A, a + 0x2C, -0x20, a + 0x54);
                func_80074590(0xD, -0x1D, 0);
            }
            break;
        case 1:
            if (D_800BF916 >= 2) {
                a[0x5E] = 1;
                a[5] = 0;
            }
            if (!(D_1F80017C & 0xF)) {
                func_80074590(0xD, -0x1D, 0);
            }
            break;
        }
        a[1] = 0;
        break;
    case 1:
        f_UpdateMythicalTowerEntranceTransition(a);
        func_800735F4(a, 0x6A);
        break;
    case 2:
        func_80124CF8(a);
        func_800735F4(a, 0x6A);
        break;
    }
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80126608);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_801267E8);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80126A80);

extern s16 D_80137600[];
/* func_80126EB0, inlined */
static inline void inl_80126EB0(u8 *a) {
    if (a[3] == 1) {
        M2C_FIELD(a, s16 *, 0x56) = 0x180;
    } else if (a[3] == 2) {
        M2C_FIELD(a, s16 *, 0x56) = 0xB9A;
    } else if (a[3] == 3) {
        M2C_FIELD(a, s16 *, 0x56) = 0xA0;
    }
    a[0x47] = 0;
    func_80126608(a);
    M2C_FIELD(a, s16 *, 0x80) = 0x32;
    M2C_FIELD(a, s16 *, 0x82) = 0x64;
    M2C_FIELD(a, s16 *, 0x84) = D_80137600[a[3]] + 0x5A;
    M2C_FIELD(a, s16 *, 0x86) = D_80137600[a[3]] + 0xDC;
}
void func_80126C1C(u8 *a) {
    switch (a[4]) {
    case 0:
        func_80126A80(a);
        inl_80126EB0(a);
        M2C_FIELD(a, s16 *, 0x32) += 0xAF;
        func_800517F8(a);
        break;
    case 1:
        func_801267E8(a);
        break;
    case 2:
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

typedef struct {
    s16 x, y, z;
} AVec3;
extern AVec3 D_80137614[];
extern s16 D_8013764C[];
/* func_80126F60, inlined */
static inline void inl_80126F60(u8 *a) {
    u8 *p;

    M2C_FIELD(a, s16 *, 0x2E) = D_80137614[a[3]].x;
    M2C_FIELD(a, s16 *, 0x32) = D_80137614[a[3]].y;
    M2C_FIELD(a, s16 *, 0x36) = D_80137614[a[3]].z;
    p = M2C_FIELD(a, u8 **, 0x10);
    M2C_FIELD(a, s16 *, 0x54) = M2C_FIELD(p, s16 *, 0x54);
    M2C_FIELD(a, s16 *, 0x56) = M2C_FIELD(p, s16 *, 0x56);
    M2C_FIELD(a, s16 *, 0x58) = M2C_FIELD(p, s16 *, 0x58);
    M2C_FIELD(a, s16 *, 0x80) = 0x32;
    M2C_FIELD(a, s16 *, 0x82) = 0x64;
    M2C_FIELD(a, s16 *, 0x84) = D_8013764C[a[3]] + 0x5A;
    M2C_FIELD(a, s16 *, 0x86) = D_8013764C[a[3]] + 0xDC;
}
void func_80126D50(u8 *a) {
    switch (a[4]) {
    case 0:
        func_80126A80(a);
        inl_80126F60(a);
        M2C_FIELD(a, s16 *, 0x32) += 0xAF;
        func_800517F8(a);
        break;
    case 1:
        func_801267E8(a);
        break;
    case 2:
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

void func_80126EB0(u8 *a) {
    if (a[3] == 1) {
        M2C_FIELD(a, s16 *, 0x56) = 0x180;
    } else if (a[3] == 2) {
        M2C_FIELD(a, s16 *, 0x56) = 0xB9A;
    } else if (a[3] == 3) {
        M2C_FIELD(a, s16 *, 0x56) = 0xA0;
    }
    a[0x47] = 0;
    func_80126608(a);
    M2C_FIELD(a, s16 *, 0x80) = 0x32;
    M2C_FIELD(a, s16 *, 0x82) = 0x64;
    M2C_FIELD(a, s16 *, 0x84) = D_80137600[a[3]] + 0x5A;
    M2C_FIELD(a, s16 *, 0x86) = D_80137600[a[3]] + 0xDC;
}

void func_80126F60(u8 *a) {
    u8 *p;

    M2C_FIELD(a, s16 *, 0x2E) = D_80137614[a[3]].x;
    M2C_FIELD(a, s16 *, 0x32) = D_80137614[a[3]].y;
    M2C_FIELD(a, s16 *, 0x36) = D_80137614[a[3]].z;
    p = M2C_FIELD(a, u8 **, 0x10);
    M2C_FIELD(a, s16 *, 0x54) = M2C_FIELD(p, s16 *, 0x54);
    M2C_FIELD(a, s16 *, 0x56) = M2C_FIELD(p, s16 *, 0x56);
    M2C_FIELD(a, s16 *, 0x58) = M2C_FIELD(p, s16 *, 0x58);
    M2C_FIELD(a, s16 *, 0x80) = 0x32;
    M2C_FIELD(a, s16 *, 0x82) = 0x64;
    M2C_FIELD(a, s16 *, 0x84) = D_8013764C[a[3]] + 0x5A;
    M2C_FIELD(a, s16 *, 0x86) = D_8013764C[a[3]] + 0xDC;
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8012702C);

/* func_8012749C, inlined */
static inline void Step_7298(u8 *a) {
    if (func_80051B70(a, 0xC, 3) == 0) {
        a[0xB] = 0;
        a[0xD] |= 4;
        M2C_FIELD(a, u8 **, 0xC0)[0x3F] = 0x40;
        a[0x29] = 0;
        a[0x2B] = 0;
        a[0x5E] = 0;
        M2C_FIELD(a, s16 *, 0x4A) = 0;
        M2C_FIELD(a, s16 *, 0x60) = 0;
        a[4]++;
    }
}
void func_80127298(a)
    u8 *a;
{
    u8 *r;

    switch (a[4]) {
    case 0:
        Step_7298(a);
        a[0x47] = 0;
        r = func_80072DDC(a, 1, 4, 0x15);
        if (r != NULL) {
            *(void **)(r + 0x1C) = f_UpdatePipeAreaBridgeActor;
            *(u8 **)(a + 0x3C) = r;
        }
        func_80126608(a);
        func_800517F8(a);
        break;
    case 1:
        func_8012702C(a);
        break;
    case 2:
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

void func_801273AC(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 4);
    switch (temp_v1) {                              /* irregular */
    case 0:
        if (func_80051B70(arg0, 0xC, 3) == 0) {
            M2C_FIELD(arg0, s8 *, 0xB) = 0;
            M2C_FIELD(arg0, u8 *, 0xD) = (u8) (M2C_FIELD(arg0, u8 *, 0xD) | 4);
            M2C_FIELD(M2C_FIELD(arg0, void **, 0xC0), s8 *, 0x3F) = 0x40;
            M2C_FIELD(arg0, s8 *, 0x29) = 0;
            M2C_FIELD(arg0, s8 *, 0x2B) = 0;
            M2C_FIELD(arg0, s8 *, 0x5E) = 0;
            M2C_FIELD(arg0, s16 *, 0x4A) = 0;
            M2C_FIELD(arg0, s16 *, 0x60) = 0;
            M2C_FIELD(arg0, u8 *, 4) = (u8) (M2C_FIELD(arg0, u8 *, 4) + 1);
        }
        M2C_FIELD(arg0, s16 *, 0x2E) = 0x4180;
        M2C_FIELD(arg0, s16 *, 0x32) = -0x19F2;
        M2C_FIELD(arg0, s16 *, 0x36) = 0x2340;
        func_800517F8(arg0);
        return;
    case 1:
        func_8012702C(arg0);
        return;
    case 3:
        func_8007A624(arg0);
        /* fallthrough */
    case 2:
        return;
    }
}

void func_8012749C(u8 *a) {
    if (func_80051B70(a, 0xC, 3) == 0) {
        a[0xB] = 0;
        a[0xD] |= 4;
        M2C_FIELD(a, u8 **, 0xC0)[0x3F] = 0x40;
        a[0x29] = 0;
        a[0x2B] = 0;
        a[0x5E] = 0;
        M2C_FIELD(a, s16 *, 0x4A) = 0;
        M2C_FIELD(a, s16 *, 0x60) = 0;
        a[4]++;
    }
}

void func_8012750C(u8 *a) {
    u8 *p;

    a[0x47] = 0;
    p = func_80072DDC((s32)a, 1, 4, 0x15);
    if (p != NULL) {
        M2C_FIELD(p, void **, 0x1C) = f_UpdatePipeAreaBridgeActor;
        M2C_FIELD(a, u8 **, 0x3C) = p;
    }
    func_80126608(a);
}

void func_80127560(void *arg0) {
    M2C_FIELD(arg0, s16 *, 0x2E) = 0x4180;
    M2C_FIELD(arg0, s16 *, 0x32) = -0x19F2;
    M2C_FIELD(arg0, s16 *, 0x36) = 0x2340;
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8012757C);

INCLUDE_ASM("asm/a01/nonmatchings/a01", f_UpdatePipeAreaBridgeMotion);

extern u8 D_80137660[];
s32 f_UpdatePipeAreaBridgeRevealCamera(u8 *a) {
    u8 *g = D_800E8008;
    s32 pad[4];

    switch (a[0x5E]) {
    case 0:
        func_8006E1C0(7);
        H(g, 0x3A) = D_1F800160_3621;
        H(g, 0x3E) = D_1F800162;
        H(g, 0x42) = D_1F800164_d75f; 
        func_8006CC1C(g, D_80137660, 0x40);
        a[0x5E]++;
        break;
    case 1:
        if (func_8006CDCC(g) == 1) {
            a[0x5E]++;
        }
        break;
    case 2:
        if (H(*(u8 **)(a + 0x10), 0x4A) == 0) {
            H(a, 0x40) = 0x30;
            a[0x5E]++;
        }
        break;
    case 3:
        if (H(a, 0x40) != 0) {
            H(a, 0x40)--;
        } else {
            func_8006E1E4();
            a[0x5E]++;
        }
        break;
    case 4:
        if (g[0x66] == 3) {
            func_80042310();
            return 1;
        }
        break;
    }
    return 0;
}

void f_UpdatePipeAreaBridgeActor(u8 *a)
{
    u8 *g;

    switch (a[4]) {
    case 0:
        if (func_80051B70(a, 0xC, 4) != 0) {
            break;
        }
        a[0xD] |= 4;
        (*(u8 **)(a + 0xC0))[0x3F] = 0x10;
        a[0] = 1;
        a[4]++;
        if (D_800BF873 != 0) {
            H(*(u8 **)(a + 0xC0), 0) = 0;
            H(a, 0x2E) = 0x4828;
        } else {
            H(*(u8 **)(a + 0xC0), 0) = 0x420;
            H(a, 0x2E) = 0x4408;
        }
        H(a, 0x80) = 0x470;
        H(a, 0x82) = 0x8E0;
        H(a, 0x84) = 0x28;
        H(a, 0x86) = 0x50;
        H(a, 0x32) = -0x1A9A;
        H(a, 0x36) = 0x2340;
        __asm__ volatile("");
        g = (u8 *)&D_800BF870;
        a[0x29] = 0;
        a[0x2B] = 0;
        a[0x5E] = 0;
        H(a, 0x44) = 0;
        H(a, 0x4A) = 0;
        H(a, 0x54) = 0;
        H(a, 0x56) = 0;
        a[0xBF] = 0;
        H(a, 0x60) = 0;
        if (g[0x18A] == 0x18 || g[1] == 0xD || g[3] != 0) {
            H(a, 0x58) = 0;
        } else {
            H(a, 0x58) = -0x400;
        }
        break;
    case 1:
        g = (u8 *)&D_800BF870;
        if ((g[0x18A] == 0x18 || g[3] != 0) && H(a, 0x58) == 0) {
            func_800517F8(a);
            a[1] = 1;
            func_80077EBC(a);
            break;
        }
        switch (a[5]) {
        case 0:
            if (D_800BFA06 & 4) {
                a[5] = 3;
            } else {
                a[5] = 1;
            }
            break;
        case 1:
            {
            u8 *g1 = (u8 *)&D_800BF870;
            if (g1[0x196] & 4) {
                g1[0x180] |= 2;
                a[0x5E] = 0;
                a[5]++;
            }
            }
            break;
        case 2:
            if (f_UpdatePipeAreaBridgeRevealCamera(a) != 0) {
                u8 *g2 = (u8 *)&D_800BF870;
                g2[0x180] &= 0xFD;
                a[5]++;
            }
            break;
        }
        f_UpdatePipeAreaBridgeMotion(a);
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

extern s8 D_800E807E;
s32 func_80127DC4(u8 *a) {
    switch (a[7]) {
    case 0:
        a[7]++;
        a[0xBF] = 2;
        M2C_FIELD(a, s16 *, 0x42) = 8;
        D_800E807E = 1;
        if (D_800BF80F == 0) {
            func_80074590(0x84, 0, 0);
        }
    case 1:
        M2C_FIELD(M2C_FIELD(a, u8 **, 0xC0), s16 *, 2) = ((D_1F80017C & 3) - 2) * 12;
        if (--M2C_FIELD(a, s16 *, 0x42) == 0) {
            D_800E807E = 0;
            return 1;
        }
        return 0;
    }
    return 0;
}

typedef struct { s16 h0; s16 h2; u8 b4; u8 pad5; s16 h6; s16 h8; } MudEnt;
extern MudEnt D_8013766C[];
extern u8 D_80040558[];
static inline void mud_sync(u8 *a) {
    u8 *c = P(P(a, 0x10), 0xC0);

    H(a, 0x88) = 0;
    H(a, 0x8A) = U(c, 0x3A) - 0x28;
    H(a, 0x8C) = 0;
    func_80051D90(c, a + 0x88, a + 0x90);
    H(a, 0x2E) = H(a, 0x90);
    H(a, 0x32) = H(a, 0x92);
    H(a, 0x36) = H(a, 0x94);
    func_800517F8(a);
}
void f_UpdatePipeAreaMudballSurpriseCarrierActor(u8 *a)
{
    GameState *g;
    MudEnt *t;
    u8 *p;
    s32 r;
    s32 k;
    s32 n;
    u8 *a_p = a;
    u8 *p_f;
    u8 *p_f_f;

    switch (a_p[4]) {
    case 0:
        if (func_80051B70(a_p, 0xC, 5) != 0) {
            break;
        }
        a_p[0xD] |= 4;
        P(a_p, 0xC0)[0x3F] = 0x10;
        H(P(a_p, 0xC0), 2) = 0x2C8;
        if (a_p[3] == 3) {
            H(a_p, 0x56) = -0x400;
        } else if (a_p[3] == 9) {
            H(a_p, 0x56) = 0x200;
        } else {
            H(a_p, 0x56) = 0;
        }
        H(a_p, 0x54) = 0;
        H(a_p, 0x58) = 0;
        a_p[0] = 1;
        H(a_p, 0x80) = 0x82;
        H(a_p, 0x82) = 0x104;
        H(a_p, 0x84) = 0x19;
        a_p[0x29] = 0;
        a_p[0x2B] = 0;
        a_p[0x5E] = 0;
        H(a_p, 0x86) = 0x32;
        a_p[4]++;
        __asm__ volatile("");
        g = &D_800BF870;
        if (g->pad1[2] != 0) {
            a_p[0xBF] = 2;
        } else {
            t = D_8013766C;
            if (func_8004D7EC(t[a_p[3]].h2, 1) == 0) {
                if (a_p[3] == 2) {
                W(a_p, 0x14) = func_8004CC64(a_p, 0);
                a_p[0xBF] = 2;
            } else if (a_p[3] == 4) {
                W(a_p, 0x14) = func_8004CC64(a_p, 1);
                a_p[0xBF] = 3;
            } else if (a_p[3] == 6) {
                W(a_p, 0x14) = func_8004CC64(a_p, 2);
                a_p[0xBF] = 3;
            } else {
                p = func_80072DDC(a_p, 2, 2, 8);
                if (p != NULL) {
                    P(p, 0x1C) = D_80040558;
                    H(p, 0x88) = 0;
                    H(p, 0x8A) = 0x2C8;
                    H(p, 0x8C) = 0;
                    p[0x5E] = 2;
                    H(p, 0xE) = t[a_p[3]].h2;
                    p[3] = t[a_p[3]].b4;
                    H(p, 0x68) = t[a_p[3]].h6;
                    H(p, 0x60) = t[a_p[3]].h8;
                    if (H(p, 0x68) == 0) {
                        H(p, 0x62) = 1;
                    } else {
                        H(p, 0x62) = 4;
                    }
                    H(p, 0x64) = 2;
                    p[0x2A] = 0;
                }
                P(a_p, 0x14) = p;
                a_p[0xBF] = 0;
            }
            } else {
                g->pad1[0x18B] &= 0xE3;
                a_p[0xBF] = 1;
                W(a_p, 0x14) = 0;
            }
        }
        mud_sync(a_p);
        break;
    case 1:
        H(a_p, 0x4A) = H(P(a_p, 0x10), 0x4A);
        switch (a_p[5]) {
        case 0:
            if (a_p[0x29] != 0) {
                P(a_p, 0x10)[0xBF] = 1;
                a_p[5]++;
            } else if (a_p[0x5E] != 0) {
                P(a_p, 0x10)[0xBF] = 1;
                a_p[5] = 2;
            }
            break;
        case 1:
            if (a_p[0x29] != 0) {
                P(a_p, 0x10)[0xBF] = 1;
                if (a_p[0x29] == 1) {
                    u8 *e = D_800E7E80;
                    if (e[0x145] == 0) {
                        W(e, 0x30) += H(P(a_p, 0x10), 0x4A) << 8;
                    }
                }
            } else {
                P(a_p, 0x10)[0xBF] = 0;
                a_p[5] = 0;
            }
            break;
        case 2:
            if (a_p[0x5E] != 0) {
                P(a_p, 0x10)[0xBF] = 1;
            } else {
                P(a_p, 0x10)[0xBF] = 0;
                a_p[5] = 0;
            }
            break;
        }
        a_p[0x29] = 0;
        mud_sync(a_p);
        if (func_800778E4(a_p, 0x2C8) == 0) {
            func_80077EBC(a_p);
        }
        if ((k = a_p[0xBF]) == 0) {
            if (func_8004D7EC(D_8013766C[a_p[3]].h2, 1) != 0) {
                a_p[0xBF] = 1;
                W(a_p, 0x14) = 0;
            }
        } else if (k == 1) {
            p_f = P(a_p, 0x10);
            if (p_f[0x46] != 0 || H(p_f, 0x4A) == 0) {
                break;
            }
            switch (a_p[3]) {
            case 1:
                r = 0;
                n = 2;
                if (H(a_p, 0x32) >= -0x7CF) {
                    g = &D_800BF870;
                    if (!((g->pad1[0x18B] >> n) & 1)) {
                        r = func_80112948(a_p);
                        g->pad1[0x18B] |= 4;
                        a_p[0xBF] = 2;
                    }
                }
                W(a_p, 0x14) = r;
                break;
            case 2:
                r = 0;
                n = 3;
                if (H(a_p, 0x32) >= -0x7CF) {
                    g = &D_800BF870;
                    if (!((g->pad1[0x18B] >> n) & 1)) {
                        r = func_80112948(a_p);
                        g->pad1[0x18B] |= 8;
                        a_p[0xBF] = 2;
                    }
                }
                W(a_p, 0x14) = r;
                break;
            case 4:
                r = 0;
                n = 4;
                if (H(a_p, 0x32) >= -0x7CF) {
                    g = &D_800BF870;
                    if (!((g->pad1[0x18B] >> n) & 1)) {
                        r = func_80112948(a_p);
                        g->pad1[0x18B] |= 0x10;
                        a_p[0xBF] = 2;
                    }
                }
                W(a_p, 0x14) = r;
                break;
            }
        } else if (k == 2) {
            p_f = P(a_p, 0x14);
            if (p_f == NULL) {
                break;
            }
            if (p_f[4] == 2) {
                switch (a_p[3]) {
                case 1:
                    { GameState *g1 = &D_800BF870; g1->pad1[0x18B] &= 0xFB; }
                    break;
                case 2:
                    { GameState *g2 = &D_800BF870; g2->pad1[0x18B] &= 0xF7; }
                    break;
                case 4:
                    { GameState *g3 = &D_800BF870; g3->pad1[0x18B] &= 0xEF; }
                    break;
                }
                a_p[0xBF] = 1;
            } else {
                H(p_f, 0x2E) = H(a_p, 0x2E);
                H(P(a_p, 0x14), 0x32) = H(a_p, 0x32) + 0x2B8;
                H(P(a_p, 0x14), 0x36) = H(a_p, 0x36);
            }
        } else if (k == 3) {
            p_f_f = P(a_p, 0x14);
            if (p_f_f != NULL && p_f_f[4] == 2) {
                switch (a_p[3]) {
                case 4:
                    { GameState *g4 = &D_800BF870; g4->pad1[0x19E] |= 1; }
                    break;
                case 6:
                    { GameState *g5 = &D_800BF870; g5->pad1[0x19E] |= 2; }
                    break;
                }
                func_80040B48(0x4C);
                a_p[0xBF] = 1;
            }
        }
        break;
    case 2:
        break;
    case 3:
        func_8007A624(a_p);
        break;
    }
}

void func_8012866C(u8 *a) {
    s16 *v = D_1F8000C0_65b0;
    u8 *p = M2C_FIELD(a, u8 **, 0x10);

    func_80051D20(p, a + 0x88, v);
    M2C_FIELD(a, s16 *, 0x2E) = v[0];
    M2C_FIELD(a, s16 *, 0x32) = v[1];
    M2C_FIELD(a, s16 *, 0x36) = v[2];
    M2C_FIELD(a, s16 *, 0x56) = M2C_FIELD(p, s16 *, 0x56);
    func_800517F8(a);
}

typedef struct {
    s16 x, y, z;
} SVec3T;
extern SVec3T D_1F8000C0_4e9b;
void f_UpdatePipeAreaPersistentSceneryRewardActor();
void func_801286F4(u8 *a) {
    u8 *p = M2C_FIELD(a, u8 **, 0x10);
    u8 *e;

    func_80051D20(p, a + 0x88, &D_1F8000C0_4e9b);
    M2C_FIELD(a, s16 *, 0x2E) = D_1F8000C0_4e9b.x;
    M2C_FIELD(a, s16 *, 0x32) = D_1F8000C0_4e9b.y;
    M2C_FIELD(a, s16 *, 0x36) = D_1F8000C0_4e9b.z;
    M2C_FIELD(a, s16 *, 0x56) = M2C_FIELD(p, s16 *, 0x56);
    func_800517F8(a);
    if (M2C_FIELD(a, s16 *, 0xE) == 5 && !(D_800BFA06 & 1)) {
        e = func_80072DDC(a, 0, 2, 0x1E);
        if (e != NULL) {
            M2C_FIELD(e, void **, 0x1C) = f_UpdatePipeAreaPersistentSceneryRewardActor;
            e[3] = 0;
            a[0] = 3;
        }
    }
}

s32 func_801287D0(void *arg0, s32 arg1) {
    s32 var_a0;

    var_a0 = 0;
    if ((M2C_FIELD(arg0, s16 *, 0x32) >= -0x7CF) && !(((s32) D_800BF870.pad1[0x18B] >> arg1) & 1)) {
        var_a0 = func_80112948(arg0);
        D_800BF870.pad1[0x18B] |= 1 << arg1;
        M2C_FIELD(arg0, s8 *, 0xBF) = 2;
    }
    return var_a0;
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80128864);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80128B08);

extern AreaSVec D_1F8000C0;
extern AreaScratchD0 D_1F8000D0;
extern AreaMatrix D_1F800000;
void func_80129114(u8 *a) {
    D_1F8000C0.x = M2C_FIELD(M2C_FIELD(a, u8 **, 0xC0), s16 *, 0x2C);
    D_1F8000C0.y = M2C_FIELD(M2C_FIELD(a, u8 **, 0xC0), s16 *, 0x30);
    D_1F8000C0.z = M2C_FIELD(M2C_FIELD(a, u8 **, 0xC0), s16 *, 0x34);
    func_80084110(&D_1F8000D0.m, M2C_FIELD(a, u8 **, 0xC0) + 0x18, &D_1F800000);
    func_80084220(&D_1F8000C0, D_1F800000.t);
    D_1F800000.t[0] += D_1F8000D0.m.t[0];
    D_1F800000.t[1] += D_1F8000D0.m.t[1];
    D_1F800000.t[2] += D_1F8000D0.m.t[2];
    func_80084660(&D_1F800000);
    func_80084690(&D_1F800000);
    func_80128B08(a);
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_801291F4);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80129394);

INCLUDE_ASM("asm/a01/nonmatchings/a01", f_UpdatePullAndOpenGateSegmentTransform);

#define C0 (*(u8 **)(a + 0xC0))
void f_UpdatePullAndOpenGateSegment(u8 *a) {
    s32 n;

    if (a[0x5E] == 2) {
        if (H(a, 0x4A) >= 0xF80) {
            a[7] = 1;
        }
        if (H(a, 0x4A) > H(a, 0x50)) {
            func_80074590(0x8B, 0, 0);
        }
        H(a, 0x4A) = 0;
        a[0x5E] = 0;
        a[6] = 0;
        if (a[3] == 7 && !(D_800BF870.pad1[0x18C] & 1)) {
            D_800BF870.pad1[0x18C] |= 1;
        } else if (a[3] == 8 && !(D_800BF870.pad1[0x18C] & 2)) {
            D_800BF870.pad1[0x18C] |= 2;
        }
        return;
    }
    switch (a[6]) {
    case 0:
        switch (a[7]) {
        case 0:
            break;
        case 1:
            a[7] = 2;
            H(a, 0x7A) = 8;
            n = *(u16 *)(C0 + 0x3A) / 320;
            if (n == 0) {
                n = 1;
            } else if (n >= 5) {
                n = 4;
            }
            H(a, 0x7C) = 0;
            H(a, 0x7E) = n * 8;
            if (H(a, 0x7E) != 0) {
                H(a, 0x7E) = n * 8 - 8;
            }
        case 2:
            H(C0, 2) = H(a, 0x78) + (D_1F80017C & 1) * 20;
            if (--H(a, 0x7A) == 0) {
                a[7] = 0;
            }
            break;
        }
        if (a[0x5E] == 1) {
            H(C0, 2) = H(a, 0x78);
            if (a[3] == 7 && !(D_800BF9FD & 1)) {
                if (func_8005308C() == 0) {
                    break;
                }
                func_80042354(1, 1);
                func_80040B48(0xB);
                a[6]++;
            } else if (a[3] == 8 && !(D_800BF9FD & 2)) {
                if (func_8005308C() == 0) {
                    break;
                }
                func_80042354(1, 1);
                func_80040B48(0xB);
                a[6]++;
            } else {
                a[6]++;
            }
        }
        break;
    case 1:
        H(a, 0x4A) = 4;
        a[6]++;
    case 2:
        if ((H(a, 0x4A) *= 2) >= H(a, 0x50)) {
            a[6]++;
        }
        break;
    case 3:
        if ((H(a, 0x4A) += H(a, 0x50)) >= 0x1F00) {
            H(a, 0x4A) = 0x1F00;
            a[6]++;
        }
        if (a[0x5E] == 0) {
            a[6] = 5;
        }
        break;
    case 4:
        if (a[0x5E] == 0) {
            a[6]++;
        }
        break;
    case 5:
        if ((H(a, 0x4A) -= H(a, 0x50) / 2) <= 0) {
            H(a, 0x4A) = 0;
            a[6] = 0;
        }
        if (a[0x5E] == 1) {
            a[6] = 3;
        }
        break;
    }
    if (H(a, 0x4A) != 0) {
        f_UpdatePullAndOpenGateSegmentTransform(a);
    }
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", f_SynchronizePullAndOpenGateAssembly);

INCLUDE_ASM("asm/a01/nonmatchings/a01", f_UpdatePipeAreaInteractiveSceneryActor);

void f_UpdatePipeAreaMudballSurpriseCarrierActor();
void func_8012AB50(u8 *a) {
    u8 t;
    u8 *p = func_8007A980(2, 4, 0);

    if (p != NULL) {
        M2C_FIELD(p, void **, 0x1C) = f_UpdatePipeAreaMudballSurpriseCarrierActor;
        p[0x2] = 22;
        t = a[3];
        M2C_FIELD(p, u8 **, 0x10) = a;
        p[0x3] = t;
        p[0x2A] = a[0x2A];
    }
}

void func_8012ABB4(u8 *a) {
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
        func_80074590(0x81, 0, 0);
        return;
    }
    x = (M2C_FIELD(a, u16 *, 0x7C) + 0x1E0) & 0xFFF;
    M2C_FIELD(a, s16 *, 0x7C) = x;
    if (x < 0x1E0 && M2C_FIELD(a, s16 *, 0x7E) != 0) {
        M2C_FIELD(a, s16 *, 0x7E) -= 8;
    }
}

void func_8012AC84(u8 *a) {
    s32 i, k, n;
    u8 *e;

    switch (a[4]) {
    case 0:
        if (func_80051B70(a, 0xC, 0) == 0) {
            FH(a, 0x80) = 0x160;
            FH(a, 0x82) = 0x2C0;
            FH(a, 0x84) = 0xA2;
            FH(a, 0x86) = 0x144;
            FH(a, 0x2E) = 0x3040;
            FH(a, 0x32) = -0x17DF;
            a[0] = 1;
            a[0x29] = 0;
            FH(a, 0x36) = 0x2A00;
            a[3] = 0;
            FH(a, 0x54) = 0;
            FH(a, 0x56) = 0;
            FH(a, 0x58) = 0;
            a[4]++;
            func_800517F8(a);
            FH(a, 0x40) = 0x1E;
        }
        break;
    case 1:
        switch (a[5]) {
        case 0:
            break;
        case 1:
            if (--FH(a, 0x40) != -1) {
                break;
            }
            a[5]++;
            break;
        case 6:
            a[4] = 3;
        case 2:
        case 4:
            a[5]++;
            i = 0;
            n = func_800270F8(*(s32 *)(*(u8 **)(a + 0xC0) + 0x40));
            for (; i < n; i++) {
                if (i >= 8) {
                    break;
                }
                e = func_8007B26C();
                if (e != NULL) {
                    e[1] = 0;
                    e[2] = (*(u8 *)&D_1F80017C + i) & 7;
                    FH(e, 0xC) = 0x2000;
                    FH(e, 0x1E) = FH(a, 0x2E);
                    FH(e, 0x22) = FH(a, 0x32) + 0xA0;
                    FH(e, 0x26) = FH(a, 0x36) + (i - 4) * 0x32;
                    func_80027058(e, *(s32 *)(*(u8 **)(a + 0xC0) + 0x40), i);
                }
            }
            func_80074590(0xC, 0, 0);
            break;
        case 3:
        case 5:
            a[5]++;
            break;
        }
        if (D_1F800207_9c67 == 0xF || D_1F800207_9c67 == 0x11) {
            a[1] = 1;
            func_80077EBC(a);
        } else {
            func_80077870(a);
        }
        break;
    case 2:
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

#define FH(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define FU(p, o) (*(u16 *)((u8 *)(p) + (o)))
typedef struct { s32 x, y, z; } V3W;
typedef union { V3W w; s16 h[6]; } V3U;
void func_8012AF08(u8 *a) {
    V3U v;
    s32 r, r1, r2, k, k1;
    s32 one = 1;
    s32 n;

    switch (a[4]) {
    case 0:
        if (func_80051B70(a, 0xC, 0x15) == 0) {
            FH(a, 0x2E) = 0x4DAB;
            FH(a, 0x32) = -0x1A40;
            FH(a, 0x36) = 0x2342;
            FH(a, 0x80) = 0x118;
            FH(a, 0x82) = 0x230;
            FH(a, 0x84) = 0xBB8;
            FH(a, 0x58) = 0;
            FH(a, 0x56) = 0;
            FH(a, 0x54) = 0;
            a[0] = one;
            a[0x29] = 0;
            a[0x2B] = 0;
            FH(a, 0x86) = 0xC26;
            a[4]++;
        }
        break;
    case 1:
        switch (a[5]) {
        case 0:
            func_80077870(a);
            if (D_800BF9FA == 0x1B) {
                v.w = *(V3W *)(a + 0x2C);
                v.h[3] -= 0xC8;
                func_8003116C(0x208, a + 0x2C, -0x32);
                FH(a, 0x42) = 0;
                FH(a, 0x40) = 0;
                FH(a, 0x60) = 0;
                func_800725D4(a + 0x62);
                a[5]++;
            }
            break;
        case 1:
        case 2:
            a[1] = 1;
            func_80077EBC(a);
        case 3:
            if (FH(a, 0x60) < 9) {
                if (FH(a, 0x60) < 5) {
                    FH(a, 0x62) = 0xFF - (FH(a, 0x60) >> 1);
                } else {
                    FH(a, 0x62) = -1;
                }
                if (!(FU(a, 0x60) & 3)) {
                    v.h[1] = FH(a, 0x2E);
                    k1 = FU(a, 0x32) - 0x64;
                    k1 -= (FH(a, 0x60) >> 2) * 0x46;
                    v.h[3] = k1;
                    v.h[5] = FH(a, 0x36);
                    func_8003116C(0x206, &v, -0xA);
                }
                FH(a, 0x60)++;
            }
            if (--FH(a, 0x40) <= 0) {
                r = func_8009A450() & 3;
                k = (a[5] >> 1) + 2;
                n = r + k;
                while (n != 0) {
                    r1 = func_80070698(0x80) - 0x12C;
                    v.h[1] = FH(a, 0x2E) + r1;
                    r2 = (func_8009A450() & 0x1FF) - 0x64;
                    v.h[3] = FH(a, 0x32) - r2;
                    n--;
                    v.h[5] = FH(a, 0x36) + func_80070698(0x200);
                    func_80027144(*(s32 *)(*(u8 **)(a + 0xC0) + 0x40), &v, (func_8009A450() & 0x3FF) | 0x800, 8);
                    func_8003116C(0x205, &v, -0xA);
                }
                FH(a, 0x40) = (func_8009A450() & 3) + 2;
                if (!(++FH(a, 0x42) & 0xF)) {
                    FH(a, 0x42) = 0;
                    FH(a, 0x40) = 0;
                    FH(a, 0x60) = 0;
                    D_800BF9FA = a[5] + 0x1B;
                    if (++a[5] == 3) {
                        v.w = *(V3W *)(a + 0x2C);
                        v.h[3] -= 0xC8;
                        func_8003116C(0x208, &v, -0x32);
                        func_80111BE0();
                    }
                }
            }
            break;
        case 4:
            FH(a, 0x62) = -2;
            a[4] = 3;
            break;
        }
        if (a[1] != 0) {
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

u8 *func_8012B2D8(void) {
    u8 *p = func_8007A980(1, 4, 0);

    if (p == NULL) {
        return NULL;
    }
    p[0x2] = 29;
    p[0x3] = 0;
    M2C_FIELD(p, void **, 0x1C) = func_8012AF08;
    return p;
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8012B324);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8012B464);

void func_8012B5CC(void *arg0) {
    M2C_FIELD(arg0, s16 *, 0x80) = 0x12C;
    M2C_FIELD(arg0, s16 *, 0x82) = 0x258;
    M2C_FIELD(arg0, s16 *, 0x84) = 0x1F4;
    M2C_FIELD(arg0, s16 *, 0x86) = 0x3E8;
    M2C_FIELD(arg0, s8 *, 0x2A) = 0x10;
    M2C_FIELD(arg0, s32 *, 0x2C) = 0x37400000;
    M2C_FIELD(arg0, s32 *, 0x30) = 0xE6E70000;
    M2C_FIELD(arg0, s32 *, 0x34) = 0x3D540000;
}

void func_8012B610(void *arg0) {
    M2C_FIELD(arg0, s16 *, 0x80) = 0xC8;
    M2C_FIELD(arg0, s16 *, 0x82) = 0x190;
    M2C_FIELD(arg0, s16 *, 0x84) = 0x284;
    M2C_FIELD(arg0, s16 *, 0x86) = 0x508;
    M2C_FIELD(arg0, s8 *, 0x2A) = 0xF;
    M2C_FIELD(arg0, s32 *, 0x2C) = 0x30400000;
    M2C_FIELD(arg0, s32 *, 0x30) = 0xED9C0000;
    M2C_FIELD(arg0, s32 *, 0x34) = 0x3F160000;
}

u8 *func_8012B654(s32 a, s32 b) {
    u8 *p = func_80072DDC(0, 1, 4, 31);

    if (p == NULL) {
        return NULL;
    }
    M2C_FIELD(p, void **, 0x1C) = func_8012B464;
    p[0x3] = b;
    M2C_FIELD(p, s16 *, 0x58) = 0;
    M2C_FIELD(p, s16 *, 0x56) = 0;
    M2C_FIELD(p, s16 *, 0x54) = 0;
    M2C_FIELD(p, s32 *, 0x10) = a;
    p[0x28] = (p[0x28] | 0x80);
    return p;
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8012B6CC);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8012B86C);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8012BA60);

typedef struct { u8 pad[0xD0]; s32 *p0; u8 pad2[8]; s32 *p1; } MidOwner;
#define FPV(p, o) (*(u8 * volatile *)((u8 *)(p) + (o)))
#define F32(p, o) M2C_FIELD(p, s32 *, o)
extern u8 D_1F800233;
static inline void MID(u8 *a) { MidOwner *e = (MidOwner *)D_800E7E80; H(a, 0x2E) = (e->p0[0xB] + e->p1[0xB]) / 2; H(a, 0x32) = (e->p0[0xC] + e->p1[0xC]) / 2; H(a, 0x36) = (e->p0[0xD] + e->p1[0xD]) / 2; }
/* func_8012C18C, inlined */
static inline void func_8012C18C_inl(u8 *a)
{
    u8 *c;

    switch (a[5]) {
    case 0 ... 5:
        a[0] = 1;
        a[4] = 1;
        break;
    case 6:
        switch (a[6]) {
        case 0:
            a[0] = 2;
            func_80042354(1, 1);
            a[6]++;
        case 1:
            c = M2C_FIELD(a, u8 **, 0xC0);
            M2C_FIELD(c, u16 *, 0x3A) -= 0x400;
            if (M2C_FIELD(M2C_FIELD(a, u8 **, 0xC0), u16 *, 0x3A) < 0x400) {
                D_800BF870.pad1[0x18B] |= 1;
                func_80027144(M2C_FIELD(M2C_FIELD(a, u8 **, 0xC0), s32 *, 0x40), a + 0x2C, 0x400, 0xC);
                func_80074590(0xC, 0, 0);
                a[4] = 3;
                func_80074590(0x97, 0, 0);
            }
            break;
        }
        func_80051844(a);
        break;
    }
}
/* func_8012C304, inlined */
static inline void func_8012C304_inl(u8 *a) {
    u8 *e;

    switch (a[5]) {
    case 0:
        if (D_800BF9FA == 0x17) {
            a[0] = 2;
            e = D_800E7E80;
            F16(a, 0x2E) = (F32(FPV(e, 0xD0), 0x2C) + F32(FPV(e, 0xDC), 0x2C)) / 2;
            F16(a, 0x32) = (F32(FPV(e, 0xD0), 0x30) + F32(FPV(e, 0xDC), 0x30)) / 2;
            F16(a, 0x36) = (F32(FPV(e, 0xD0), 0x34) + F32(FPV(e, 0xDC), 0x34)) / 2;
        } else {
            a[0] = 1;
            F32(a, 0x2C) = 0x46E60000;
            F32(a, 0x30) = 0xE53E0000;
            F32(a, 0x34) = 0x23400000;
            a[5]++;
        }
    case 1:
        func_8007778C(a);
        break;
    }
}
/* func_8012C410, inlined */
static inline void func_8012C410_inl(u8 *a) {
    switch (a[5]) {
    case 0 ... 5:
        a[0] = 1;
        a[4] = 1;
        break;
    case 6:
        func_800521F4(0, 1, 0xC0, 4);
        D_800BF9FA = 0x19;
        func_80042354(1, 1);
        func_80054198(D_800E7E80);
        func_80027144(M2C_FIELD(M2C_FIELD(a, u8 **, 0xC0), s32 *, 0x40), a + 0x2C, 0x600, 8);
        func_80074590(0xC, 0, 0);
        func_80074810(0x97, 0);
        func_80043B88(1);
        *(volatile u8 *)&D_1F800233 = 1;
        func_8001D71C(1);
        a[4] = 3;
        break;
    }
}
void f_UpdatePipeAreaQuestSceneryActor(u8 *a)
{
    u8 *e;
    GameState *g;

    switch (a[4]) {
    case 0:
        switch (a[3]) {
        case 0:
            if (func_80051B70(a, 0xC, 0x19) != 0) {
                return;
            }
            H(a, 0x80) = 0x40;
            H(a, 0x82) = 0xA4;
            H(a, 0x84) = 0x8A;
            H(a, 0x86) = 0x8A;
            H(a, 0x60) = H(a, 0x84);
            break;
        case 1:
            if (func_80051B70(a, 0xC, 0x1E) != 0) {
                return;
            }
            H(a, 0x80) = 0x69;
            H(a, 0x82) = 0xD2;
            H(a, 0x84) = 0x92;
            H(a, 0x86) = 0x92;
            break;
        case 2:
            if (func_80113D44(a) == 0) {
                return;
            }
            a[0x1A] = 0;
            a[0x19] = 0;
            a[0x18] = 0;
            a[0xD] &= 0xFD;
            MID(a);
            H(a, 0x80) = 0x40;
            H(a, 0x82) = 0x80;
            H(a, 0x84) = 0x8C;
            H(a, 0x86) = 0x8C;
            break;
        case 3:
            if (func_80051B70(a, 0xC, 0x30) != 0) {
                return;
            }
            H(a, 0x80) = 0x5A;
            H(a, 0x82) = 0xB4;
            H(a, 0x84) = 0xA0;
            H(a, 0x86) = 0xCF;
            break;
        case 4:
            if (D_800BF871 != 0x1A) {
                a[4] = 3;
                return;
            }
            if (func_80051B70(a, 0xC, 0x47) != 0) {
                return;
            }
            H(a, 0x80) = 0x64;
            H(a, 0x82) = 0xC8;
            H(a, 0x84) = 0x82;
            H(a, 0x86) = 0x82;
            H(a, 0x60) = H(a, 0x84);
            W(a, 0x10) = (s32)func_80115F70(a);
            break;
        }
        a[0] = 1;
        a[0x29] = 0;
        a[0x2B] = 0;
        a[4]++;
        break;
    case 1:
        switch (a[3]) {
        case 0:
        case 1:
        case 3:
        case 4:
            func_8007778C(a);
            break;
        case 2:
            func_8012C304_inl(a);
            break;
        }
        func_800517F8(a);
        a[0x2B] = 0;
        break;
    case 2:
        func_8007778C(a);
        switch (a[3]) {
        case 0:
            func_8012B6CC(a);
            a[0x2B] = 0;
            return;
        case 1:
            func_8012C18C_inl(a);
            break;
        case 2:
            func_8012C410_inl(a);
            break;
        case 3:
            func_8012B86C(a);
            a[0x2B] = 0;
            return;
        case 4:
            func_8012BA60(a);
            a[0x2B] = 0;
            return;
        }
        a[0x2B] = 0;
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

void func_8012C18C(u8 *a)
{
    u8 *c;

    switch (a[5]) {
    case 0 ... 5:
        a[0] = 1;
        a[4] = 1;
        break;
    case 6:
        switch (a[6]) {
        case 0:
            a[0] = 2;
            func_80042354(1, 1);
            a[6]++;
        case 1:
            c = M2C_FIELD(a, u8 **, 0xC0);
            M2C_FIELD(c, u16 *, 0x3A) -= 0x400;
            if (M2C_FIELD(M2C_FIELD(a, u8 **, 0xC0), u16 *, 0x3A) < 0x400) {
                D_800BF870.pad1[0x18B] |= 1;
                func_80027144(M2C_FIELD(M2C_FIELD(a, u8 **, 0xC0), s32 *, 0x40), a + 0x2C, 0x400, 0xC);
                func_80074590(0xC, 0, 0);
                a[4] = 3;
                func_80074590(0x97, 0, 0);
            }
            break;
        }
        func_80051844(a);
        break;
    }
}

u8 *func_8012C2B4(void) {
    u8 *p = func_8007A980(2, 4, 0);

    if (p == NULL) {
        return NULL;
    }
    p[0x2] = 32;
    p[0x3] = 2;
    M2C_FIELD(p, void **, 0x1C) = f_UpdatePipeAreaQuestSceneryActor;
    return p;
}

#define FPV(p, o) (*(u8 * volatile *)((u8 *)(p) + (o)))
#define F32(p, o) M2C_FIELD(p, s32 *, o)
void func_8012C304(u8 *a) {
    u8 *e;

    switch (a[5]) {
    case 0:
        if (D_800BF9FA == 0x17) {
            a[0] = 2;
            e = D_800E7E80;
            F16(a, 0x2E) = (F32(FPV(e, 0xD0), 0x2C) + F32(FPV(e, 0xDC), 0x2C)) / 2;
            F16(a, 0x32) = (F32(FPV(e, 0xD0), 0x30) + F32(FPV(e, 0xDC), 0x30)) / 2;
            F16(a, 0x36) = (F32(FPV(e, 0xD0), 0x34) + F32(FPV(e, 0xDC), 0x34)) / 2;
        } else {
            a[0] = 1;
            F32(a, 0x2C) = 0x46E60000;
            F32(a, 0x30) = 0xE53E0000;
            F32(a, 0x34) = 0x23400000;
            a[5]++;
        }
    case 1:
        func_8007778C(a);
        break;
    }
}

void func_8012C410(u8 *a) {
    switch (a[5]) {
    case 0 ... 5:
        a[0] = 1;
        a[4] = 1;
        break;
    case 6:
        func_800521F4(0, 1, 0xC0, 4);
        D_800BF9FA = 0x19;
        func_80042354(1, 1);
        func_80054198(D_800E7E80);
        func_80027144(M2C_FIELD(M2C_FIELD(a, u8 **, 0xC0), s32 *, 0x40), a + 0x2C, 0x600, 8);
        func_80074590(0xC, 0, 0);
        func_80074810(0x97, 0);
        func_80043B88(1);
        *(volatile u8 *)&D_1F800233 = 1;
        func_8001D71C(1);
        a[4] = 3;
        break;
    }
}

extern PartPose D_80137A1C[3];
extern PartPose D_80137A34[3];
void func_8012C4F4(PosedActor *a, s32 b, s32 c) {
    s32 i;

    for (i = 0; i < 3; i++) {
        if (b == 0) {
            func_80051B04(a->parts[i], c, i);
            a->parts[i][0] = D_80137A1C[i].x;
            a->parts[i][1] = D_80137A1C[i].y;
            a->parts[i][2] = D_80137A1C[i].z;
        } else {
            func_80051B04(a->parts[i], c, i + 3);
            a->parts[i][0] = D_80137A34[i].x;
            a->parts[i][1] = D_80137A34[i].y;
            a->parts[i][2] = D_80137A34[i].z;
        }
    }
    a->pose = b;
}

extern u8 D_8001B7B0[];
void D_8004C930();
void func_8012C600(u8 *a, s32 b) {
    u16 v;
    u8 *p;

    switch (a[5]) {
    case 0:
        if (a[0x29] == 1) {
            a[5]++;
            func_8012C4F4(a, 0, b);
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

extern u8 D_80137A1C_e4a1[];
void func_8012C8C0(u8 *a)
{
    s32 s = a[4];
    u8 *g;

    switch (s) {
    case 0:
        g = D_800ECF58_742e;
        if (func_800519E0(a, 3, *(s32 *)(g + 0x78), D_80137A1C_e4a1) == 0) {
            *(s32 *)(a + 0x3C) = *(s32 *)(g + 0x7C);
            {
                u8 *st = (u8 *)&D_800BF870;
                if (st[3] != 0) {
                    a[4] = 3;
                    goto dbl;
                }
                if ((st[0x1A3] >> a[3]) & 1) {
                    a[0x5E] = 0;
                    func_80077C40(a, D_8001B7B0, 0);
                } else {
                    func_8012C4F4(a, 1, 0x1E);
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
        dbl:
            *(s16 *)(a + 0x84) = *(s16 *)(a + 0x84) * 2;
            *(s16 *)(a + 0x86) = *(s16 *)(a + 0x86) * 2;
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
            func_8012C600(a, 0x1E);
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
s32 func_8012CB28(DoorActor *a, s16 *d) {
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

void func_8012CD00(u8 *a, s32 b) {
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
    if (func_8012CB28(a, b) != 0) {
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

extern u16 D_1F8000D6;
void func_8012CE5C(u8 *a) {
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

void func_8012D0A4(u8 *a) {
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

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8012D2BC);

extern ClutCycle D_80137B3C[];
extern s8 D_80138FF8[];
void func_8012D6B0(s32 arg0) {
    ClutRect r;
    s32 i;
    ClutCycle *e;
    u8 *data;

    if (arg0 == 0) {
        for (i = 0; i < 1; i++) {
            D_80138FF8[i] = 0;
        }
        return;
    }
    e = D_80137B3C;
    for (i = 0; i < 1; i++, e++) {
        if (--D_80138FF8[i] <= 0) {
            if (e->ptr[0] == 0xFF) {
                e->ptr -= e->ptr[1];
            }
            data = e->clut + e->ptr[0] * 32;
            D_80138FF8[i] = e->ptr[1];
            r.x = e->x;
            r.y = e->y;
            r.w = 16;
            r.h = 1;
            func_80081218(&r, data);
            e->ptr += 2;
        }
    }
}

void func_8012D7D0(u8 *a)
{
    switch (a[4]) {
    case 0:
        switch (a[5]) {
        case 0:
            func_8012D6B0(0);
            a[0xBF] = 0xC0;
            *(s16 *)(a + 0x7E) = 0x19;
            *(s16 *)(a + 0x7C) = 0x400;
            *(s16 *)(a + 0x7A) = 0x5;
            *(s16 *)(a + 0x78) = 0x22;
            a[5]++;
        case 1:
            func_8012CD00(a, D_80137B48);
            break;
        case 2:
            if (func_80078240(D_1F800160_3621_dd1a - *(s16 *)(a + 0x2E), D_1F800162_a8d4 - *(s16 *)(a + 0x32), D_1F800164_7d8c_d1dc - *(s16 *)(a + 0x36)) <= 1000
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
            func_8012D6B0(1);
            func_80051844(a);
        }
        switch (a[0x5E]) {
        case 0:
            func_8012CE5C(a);
            a[0x29] = 0;
            break;
        case 1:
            func_8012D0A4(a);
            a[0x29] = 0;
            break;
        case 2:
            func_8012D2BC(a, D_80137B68);
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

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8012D9E8);

extern u8 D_801387C0[];
extern u8 D_80138160[];
void func_8012E014(u8 *a)
{
    u8 *p;
    u8 *s;

    switch (a[4]) {
    case 0:
        M2C_FIELD(a, u8 **, 0x40) = D_801387C0;
        M2C_FIELD(a, u8 **, 0x3C) = D_801387C0;
        M2C_FIELD(a, u8 **, 0x50) = D_80138160;
        a[4] = 1;
        a[5] = 0;
        M2C_FIELD(a, s16 *, 0x2C) = (func_8009A450() >> 5) + 0x4E0A;
        M2C_FIELD(a, s16 *, 0x30) = (func_8009A450() >> 4) + 0x1F40;
        M2C_FIELD(a, s16 *, 0x2E) = -0x1770;
        a[0x29] = 0;
        M2C_FIELD(a, s16 *, 0x32) = 0xA0;
    case 1:
        switch (a[5]) {
        case 0:
            if (M2C_FIELD(a, s16 *, 0x2E) < -0x1A0E) {
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

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8012E1B4);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8012E370);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8012E4B4);

#define AREA_gte_ldv0(r0) __asm__ volatile("lwc2	$0, 0( %0 );" "lwc2	$1, 4( %0 )" : : "r"(r0))
typedef struct {
    s16 x, y, z, pad;
} SVecE;
extern s32 D_1F800088;
extern s32 D_1F800090_3460;
void func_8012E5F8(u8 *a) {
    SVecE v;
    s32 t;
    u8 *q = a;

    func_800329E0(6);
    v.x = M2C_FIELD(a, s16 *, 0x2E);
    v.y = M2C_FIELD(a, s16 *, 0x32);
    v.z = M2C_FIELD(a, s16 *, 0x36);
    AREA_gte_ldv0(&v);
    if (func_800317CC(0) != 0) {
        func_80031780(a);
    } else {
        t = *(volatile s32 *)&D_1F800084;
        *(volatile s32 *)&D_1F800090_3460 = 0;
        D_1F800088 = t;
        M2C_FIELD(q, s32 *, 0x64) = func_80027A4C(M2C_FIELD(q, s32 *, 0x60), M2C_FIELD(q, s32 *, 0x70));
    }
}

void func_8012E6A0(u8 *a) {
    u8 *p;

    switch (a[4]) {
    case 0:
        a[4] = 1;
    case 1:
        M2C_FIELD(a, s16 *, 0x2E) -= 4;
        p = M2C_FIELD(a, u8 **, 0x38);
        M2C_FIELD(a, u8 **, 0x34) = p;
        if (p == NULL) {
            a[4] = 2;
            break;
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

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8012E74C);

void func_8012E868(u8 *a) {
    s32 *p84 = &D_1F800084;
    s32 *p88 = &D_1F800088;
    SVecE v;
    u8 *q = a + 0x60;
    u8 *s = M2C_FIELD(q, u8 **, 4);
    u32 sc = M2C_FIELD(a, u32 *, 0x60);
    u8 k;
    s32 t, x;
    u32 m2, m1;

    if (s != NULL) {
        k = *s;
        if (k & 0x80) {
            M2C_FIELD(q, u8 **, 8) = NULL;
            k &= 0x7F;
        } else {
            M2C_FIELD(q, u8 **, 8) = s + 1;
        }
        v.x = M2C_FIELD(a, s16 *, 0x2E);
        v.y = M2C_FIELD(a, s16 *, 0x32);
        v.z = M2C_FIELD(a, s16 *, 0x36);
        AREA_gte_ldv0(&v);
        func_800329E0(6);
        if (func_800317CC(0) == 0) {
            t = *p84;
            m1 = t * (sc >> 16);
            m2 = t * (sc & 0xFFFF);
            x = M2C_FIELD(q, s32 **, 0xC)[k];
            *p88 = m1 >> 8;
            *p84 = m2 >> 8;
            func_800328EC(x);
        }
    }
}

void func_8012E974(u8 *a) {
    SVecE v;
    s32 *sp = &D_1F800084;
        u8 *q = a + 0x60;
        s32 m = M2C_FIELD(a, s32 *, 0x60);
        u32 sc = M2C_FIELD(q, u32 *, 0x10);
        s32 t, x;
        s32 *pp;
        u32 m1, m2, y;

    if (m != 0) {
        v.x = M2C_FIELD(a, s16 *, 0x2E);
        v.y = M2C_FIELD(a, s16 *, 0x32);
        v.z = M2C_FIELD(a, s16 *, 0x36);
        AREA_gte_ldv0(&v);
        func_800329E0(6);
        if (func_800317CC(-0x32) == 0) {
            t = *sp;
            m1 = t * (sc >> 16);
            m2 = t * (sc & 0xFFFF);
            y = m1 >> 8;
            D_1F800088 = y;
            *sp = m2 >> 8;
            __asm__ volatile("ctc2 %0, $21; ctc2 %1, $22; ctc2 %2, $23" : : "r"(0), "r"(0), "r"(0));
            x = M2C_FIELD(q, s32 *, 0xC);
            pp = M2C_FIELD(q, s32 **, 8);
            D_1F800090_3460 = x;
            M2C_FIELD(q, s32 *, 4) = func_80027A4C(m, *pp);
        }
    }
}

void func_8012EA70(u8 *a) {
    u8 *p;

    switch (a[4]) {
    case 0:
        a[4] = 1;
    case 1:
        M2C_FIELD(a, s16 *, 0x2E) -= 0x12;
        p = M2C_FIELD(a, u8 **, 0x38);
        M2C_FIELD(a, u8 **, 0x34) = p;
        if (p == NULL) {
            a[4] = 2;
            break;
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

void func_8012EB1C(u8 *a) {
    switch (a[4]) {
    case 0:
        a[4] = 1;
        M2C_FIELD(a, s32 *, 0x50) = 0;
        M2C_FIELD(a, s16 *, 0x4E) = 0;
        M2C_FIELD(a, s16 *, 0x32) = -50;
    case 1:
        if (D_1F80017C & 1) {
            if (++M2C_FIELD(a, s16 *, 0x4E) == 25) {
                D_800BF916 = 2;
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

#define gte_ldfcdir(r0, r1, r2) __asm__ volatile("ctc2	%0, $21;" "ctc2	%1, $22;" "ctc2	%2, $23" : : "r"(r0), "r"(r1), "r"(r2))
extern s32 D_1F800090[];
extern u8 D_800A1CD4[];
extern u8 D_80137D94[];
extern s16 D_801388EC;
extern s16 D_801388EE;
extern s16 D_80139004;
extern s16 D_801388F0;
extern u8 D_80138AC0[];
void func_8012EC08(u8 *p) {
    s32 *d = D_1F800090;

    gte_ldfcdir(0, 0, 0);
    *d = M2C_FIELD(p, s32 *, 0x50);
    func_800318A0(p + 0x2C, D_800A1CD4, p + 0x48);
    func_80027768(D_80137D94, M2C_FIELD(p, s16 *, 0x4E), M2C_FIELD(p, s16 *, 0x32), 0);
}

typedef struct { s32 a, b; } PairEC;
typedef struct { PairEC p[14]; } TblEC;
extern TblEC D_80109E00;
void func_8012EC78(u8 *a) {
    TblEC t = D_80109E00;

    switch (a[4]) {
    case 0:
        F16(a, 0x4C) = 0x400;
        F16(a, 0x48) = 0;
        F16(a, 0x4A) = 0;
        F16(a, 0x4E) = 0;
        a[4] = 1;
        a[7] = 0xFF;
    case 1:
        if (++a[7] >= 14) {
            a[4] = 2;
            break;
        }
        { PairEC *q = &t.p[a[7]]; M2C_FIELD(a, s32 *, 0x3C) = q->a; M2C_FIELD(a, s32 *, 0x50) = q->b; }
        func_8002B278(a);
        break;
    case 2:
    case 3:
        func_8007A624(a);
        break;
    }
}

#define gte_ldfcdir(r0, r1, r2) __asm__ volatile("ctc2	%0, $21;" "ctc2	%1, $22;" "ctc2	%2, $23" : : "r"(r0), "r"(r1), "r"(r2))
void func_8012ED88(u8 *p) {
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
extern u8 *D_800ECFD8;
extern u8 *D_800ECF78;
extern u8 D_801388BC[];
void func_8012EE14(u8 *a)
{
    T2Pt32 v0, v1, v2;
    T2CamD0 *c;
    s32 ang, r, dx, dz;
    u16 t;
    u8 *m;

    if (D_800BF871 >= 0xF) {
        M2C_FIELD(a, u8 **, 0xC) = D_800ECFD8;
        D_80139000 = D_801388BC[D_800E7EAA - 0x1B];
    } else {
        D_80139000 = 0;
        M2C_FIELD(a, u8 **, 0xC) = D_800ECF78;
    }
    c = &D_1F8000D0_3bb0;
    {
        u16 v;
        u16 *mm = M2C_FIELD(a, u16 **, 0xC);
        v = mm[0];
        M2C_FIELD(a, s16 *, 8) = v;
        D_800A3F90 = 0x5780;
        v = mm[1];
        M2C_FIELD(a, s16 *, 0xA) = v;
    }
    t = c->ry;
    D_800A3F94 = 0x12C;
    ang = (-(s16)t - D_800A3F94) & 0xFFF;
    v0.vx = c->x;
    v0.vy = c->y;
    v1.vx = v0.vx + ((func_80083E80(ang) * D_800A3F90) >> 12);
    v1.vy = v0.vy + ((func_80083F50(ang) * D_800A3F90) >> 12);
    ang = (D_800A3F94 - (s16)c->ry) & 0xFFF;
    v2.vx = v0.vx + ((func_80083E80(ang) * D_800A3F90) >> 12);
    v2.vy = v0.vy + ((func_80083F50(ang) * D_800A3F90) >> 12);
    v0.vx -= (func_80083E80(-(s16)c->ry) * 0x3C0) >> 12;
    v0.vy -= (func_80083F50(-(s16)c->ry) * 0x3C0) >> 12;
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
    func_8012F188(a, &v0, &v1, &v2);
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8012F188);

s32 func_8012F864(s32 x, s32 y) {
    return D_80138FFC_e406[y * 52 + x] & D_80139000;
}

extern s8 *D_80138FFC;
void func_8012F89C(u8 *a)
{
    s8 **t = D_800ECF58;
    u16 *p = (u16 *)t[8];
    u16 v;

    *(u16 **)(a + 0xC) = p;
    *(u16 *)(a + 8) = p[0];
    v = p[1];
    a[7] = 0;
    *(u16 *)(a + 0xA) = v;
    D_80138FFC = t[9];
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8012F8D8);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8013000C);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80130838);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80130D9C);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_801311FC);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_801316A8);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80131BB0);

void func_801321C4(RECT16 *a) {
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

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80132358);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80132690);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_801329C4);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80132DC0);

#define AREA_gte_lddp(r0) __asm__ volatile("mtc2	%0, $8" : : "r"(r0))
#define AREA_gte_ldrgb_r(r0) __asm__ volatile("mtc2	%0, $6" : : "r"(r0))
#define AREA_gte_dpcs() __asm__ volatile("nop;" "nop;" ".word 0x4A780010")
#define AREA_gte_strgb(r0) __asm__ volatile("swc2	$22, 0( %0 )" : : "r"(r0) : "memory")
extern u32 D_1F800080;
void func_80132EFC(u32 *p, s32 b) {
    u32 s = D_1F800080 * 0x41C64E6D + 0x3039;

    D_1F800080 = s;
    AREA_gte_lddp(b / 4 + (s >> 22));
    AREA_gte_ldrgb_r(*p);
    AREA_gte_dpcs();
    AREA_gte_strgb(p);
}

void func_80132F5C(void) {
    u32 i;
    u8 *p;

    D_801388EC = 0;
    D_801388EE = 0;
    D_80139004 = 0;
    D_801388F0 = 0;
    if (D_800BF873 != 0) {
        for (i = 0, p = D_80138AC0; i < 6; i++, p += 8) {
            func_801321C4(p);
        }
    }
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80132FD0);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80133574);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8013362C);

u8 *func_80133900(s32 a) {
    u8 *p = func_8007A980(1, 2, 0);

    if (p == NULL) {
        return NULL;
    }
    M2C_FIELD(p, void **, 0x1C) = func_8013362C;
    M2C_FIELD(p, s32 *, 0x10) = a;
    p[0x2] = 26;
    p[0x3] = 0;
    return p;
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80133958);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80133CAC);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80133D74);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80133F38);

#define GTE_RTPT() __asm__ volatile("nop;" "nop;" ".word 0x4A280030")
#define GTE_RTPS() __asm__ volatile("nop;" "nop;" ".word 0x4A180001")
#define GTE_NCLIP() __asm__ volatile("nop;" "nop;" ".word 0x4B400006")
#define GTE_AVSZ4() __asm__ volatile("nop;" "nop;" ".word 0x4B68002E")
s32 func_801341E8(u8 *poly, u8 *v, s32 *flag) {
    s32 otz;
    s32 n;

    gte_ldv3c(v);
    GTE_RTPT();
    gte_stflg(flag);
    if (*flag < 0) {
        return -1;
    }
    gte_stsxy3_gt3(poly);
    GTE_NCLIP();
    gte_stopz(flag);
    n = *flag;
    if (n < 0) {
        n = -n;
    }
    if (n < 8) {
        return -1;
    }
    gte_ldv0(v + 0x18);
    GTE_RTPS();
    gte_stflg(flag);
    if (*flag < 0) {
        return -1;
    }
    gte_stsxy(poly + 0x2C);
    GTE_AVSZ4();
    gte_stotz(&otz);
    return otz;
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_801342C8);

INCLUDE_ASM("asm/a01/nonmatchings/a01", f_UpdatePipeAreaTrolleyNpcDialogue);

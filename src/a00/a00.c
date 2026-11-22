#include "common.h"
#include "game.h"
#include "m2c.h"

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateA00TombaWaterSurfaceMotion);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8010A7F8);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8010AC20);

void func_8010AD68(void *arg0, void *arg1) {
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

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateA00TombaVerticalClimb);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8010B07C);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8010B29C);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8010B42C);

extern u16 D_800ECF54;
s32 func_8010B600(s32 arg0) {
    u8 temp_v1;
    void *temp_s1;

    temp_s1 = M2C_FIELD(arg0, void **, 0x158);
    if (M2C_FIELD(temp_s1, u8 *, 0xC) == 4) {
        temp_v1 = M2C_FIELD(temp_s1, u8 *, 2);
        if (temp_v1 == 5) {
            return func_8010B29C(arg0, (s32) temp_s1);
        }
        if (temp_v1 == 8) {
            M2C_FIELD(temp_s1, s8 *, 0x29) = 1;
            M2C_FIELD(temp_s1, s16 *, 0x60) = (s16) -(s16) M2C_FIELD(arg0, u16 *, 0x152);
            func_800635D4(arg0, 1);
            func_80076D68(arg0);
            if ((M2C_FIELD(arg0, u8 *, 0x169) == 0) && (D_800ECF54 & (*(u16 *)0x1F800172 | 0x50))) {
                M2C_FIELD(arg0, s16 *, 0x58) = 0;
                func_8010B42C(arg0, (s32) temp_s1);
                return (s32) D_800ECF54;
            }
            func_8010B42C(arg0, (s32) temp_s1);
            if (func_80049280(arg0, 0, M2C_FIELD(arg0, s16 *, 0x62)) != 0) {
                M2C_FIELD(arg0, s8 *, 0x29) = 1;
                M2C_FIELD(arg0, u16 *, 0x6A) = (u16) *(u16 *)0x1F8001A6;
                func_80049674(arg0);
                M2C_FIELD(arg0, u16 *, 0x142) = (u16) *(u16 *)0x1F8001A2;
                M2C_FIELD(temp_s1, s8 *, 0x29) = 0;
                M2C_FIELD(arg0, s8 *, 0x164) = 0;
                M2C_FIELD(arg0, void **, 0x158) = NULL;
                func_80054198(arg0);
                M2C_FIELD(arg0, s8 *, 5) = 0;
                M2C_FIELD(arg0, s8 *, 6) = 0;
                M2C_FIELD(arg0, s8 *, 7) = 0;
                func_80054D14(arg0, 2, 4);
            }
            /* Duplicate return node #10. Try simplifying control flow for better match */
            return 0;
        }
        /* Duplicate return node #10. Try simplifying control flow for better match */
        return 0;
    }
    return 0;
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8010B754);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateA00TombaClingOrientation0);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8010BD7C);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateA00TombaClingOrientation1);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8010C290);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8010C40C);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateTombaInteriorEntry);

extern s8 D_1F800138[];
extern s8 D_1F80019B[];
void func_8010C740(void) {
    func_80045258(M2C_FIELD(*((volatile void **)D_1F800138), u8 *, 0x6E), 0xF);
    *((volatile s8 *)D_1F80019B) = 1;
    func_80051FB4();
}

#define F16(p, o) M2C_FIELD(p, s16 *, o)

void func_8010C780(u8 *a) {
    s32 k;

    if (D_800ECF54 & 0x10) {
        k = 0;
        func_80054D14(a, 0x41, 0);
        func_80076D68(a);
    } else if (D_800ECF54 & 0x40) {
        k = 1;
        func_80054D14(a, 0x43, 0);
        func_80076D68(a);
    } else {
        k = 2;
    }
    if (func_8010B07C(a, k) != 0 && func_80055824() != 0) {
        a[5] = 4;
        a[6] = 2;
        F16(a, 0x44) = 0;
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
}

void func_8010C87C(void) {
    func_8010A7F8();
}

void func_8010C89C(void *a, void *b)
{
    func_80056B48(a, 1);
    f_UpdateA00TombaWaterSurfaceMotion(a, b);
    func_80055D5C(a);
}

extern u16 D_1F800172;
extern u16 D_1F8001A6;
extern u16 D_1F8001A2;
s32 func_8010C8E4(u8 *a, u8 *b) {
    b[0x29] = 1;
    M2C_FIELD(b, s16 *, 0x60) = -M2C_FIELD(a, s16 *, 0x152);
    func_800635D4(a, 1);
    func_80076D68(a);
    if (a[0x169] == 0 && (D_800ECF54 & (D_1F800172 | 0x50))) {
        M2C_FIELD(a, s16 *, 0x58) = 0;
        func_8010B42C(a, b);
        return D_800ECF54;
    }
    func_8010B42C(a, b);
    if (func_80049280(a, 0, M2C_FIELD(a, s16 *, 0x62)) != 0) {
        a[0x29] = 1;
        M2C_FIELD(a, s16 *, 0x6A) = D_1F8001A6;
        func_80049674(a);
        M2C_FIELD(a, s16 *, 0x142) = D_1F8001A2;
        b[0x29] = 0;
        a[0x164] = 0;
        M2C_FIELD(a, s32 *, 0x158) = 0;
        func_80054198(a);
        a[5] = 0;
        a[6] = 0;
        a[7] = 0;
        func_80054D14(a, 2, 4);
    }
    return 0;
}

void func_8010C9F8(u8 *a, u8 *b, s32 f) {
    s16 ang;

    a[0x160] = 0;
    if (f == 0) {
        func_80054D14(a, 0x29, 4);
    }
    a[7] = 0;
    func_80076D68(a);
    ang = M2C_FIELD(a, s16 *, 0x56) + 0x800;
    M2C_FIELD(a, s16 *, 0x2E) = M2C_FIELD(b, s16 *, 0x2E) + ((func_80083F50(ang) * M2C_FIELD(a, s16 *, 0x152)) >> 12);
    M2C_FIELD(a, s16 *, 0x36) = M2C_FIELD(b, s16 *, 0x36) - ((func_80083E80(ang) * M2C_FIELD(a, s16 *, 0x152)) >> 12);
    M2C_FIELD(a, s16 *, 0x32) = M2C_FIELD(b, s16 *, 0x32) + M2C_FIELD(a, s16 *, 0x156);
    if (b[0x5E] == 2) {
        M2C_FIELD(a, s32 *, 0x158) = 0;
        a[0x164] = 0;
        M2C_FIELD(a, s16 *, 0x40) = 8;
        func_80056D44(a, 0);
    }
}

extern u16 D_1F8001A4;
void func_8010CAEC(u8 *a)
{
    s16 v[8];

    v[1] = *(u16 *)(a + 0x2E);
    v[3] = D_1F8001A4;
    v[5] = *(u16 *)(a + 0x36);
    func_8003116C(0x10D, v, -0xA);
    v[3] += 0x50;
    func_8003116C(0x107, v, -0xA);
    func_80074590(7, 0, 0);
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_InitializeA00InteriorState);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateA00InteriorCamera);

extern s16 D_1F800160_71b4;
void func_8010CED0(u8 *a) {
    s16 x = D_1F800160_71b4;
    s32 d;

    if (x < 0x1451) {
        M2C_FIELD(a, s32 *, 0x28) = 0;
        M2C_FIELD(a, s16 *, 0x26) = 0;
    } else if (x < 0x1E79) {
        M2C_FIELD(a, s32 *, 0x28) = 0;
        M2C_FIELD(a, s16 *, 0x26) = -800;
    } else if (x < 0x20D1) {
        d = x - 0x1E78;
        M2C_FIELD(a, s16 *, 0x26) = ((d * 0x32000) / 600 >> 8) - 800;
    } else if (x < 0x2969) {
        M2C_FIELD(a, s16 *, 0x26) = 0;
    } else if (x < 0x2AF9) {
        d = x - 0x2968;
        M2C_FIELD(a, s16 *, 0x26) = (d * 3) >> 2;
    } else {
        M2C_FIELD(a, s16 *, 0x26) = 300;
    }
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateFishermensTownCamera);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8010D89C);

extern s8 D_1F800138[];
extern s8 D_1F80019B[];
void func_8010DA70(void) {
    func_80045258(M2C_FIELD(*((volatile void **)D_1F800138), u8 *, 0x6E), 0xF);
    *((volatile s8 *)D_1F80019B) = 1;
    func_80051FB4();
}

extern u8 D_800E7E80[];
extern u8 D_800BF808_1760[];
extern u8 D_800E8008[];
extern s32 D_1F800184;
extern s16 D_1F8000D0[];
void func_8010DAB0(void) {
    u8 *t = D_800E7E80;
    u8 *g = D_800BF808_1760;
    u8 *e = D_800E8008;
    s16 *v;

    t[0x16B] = 0;
    g[0xE] = 0;
    e[0x64] = 0;
    D_1F800184 = 0;
    if (g[0xF] == 2) {
        t[0x2A] = 0x1F;
        v = D_1F8000D0;
        M2C_FIELD(e, s16 *, 0xA) = 0x4F00;
        M2C_FIELD(e, s16 *, 0x12) = 0x1AEE;
        v[0xB] = 0x1AEE;
        v[1] = 0x5716;
        v[7] = 0x4F00;
        v[5] = 0x1BE1;
        t[0x147] = 0;
        g[0x17] = 0;
    }
    func_80054198(t);
    t[5] = 0x24;
    t[6] = 0;
}

extern u8 D_80146EEC[];
extern u8 D_800BF871;
void func_8010DB58(u8 *a) {
    s16 *v;

    switch (a[2]) {
    case 0:
        a[2]++;
        if ((a[3] = D_80146EEC[D_800BF871]) == 9) {
            v = D_1F8000D0;
            v[1] = 0x354F;
            v[3] = -0xF8D;
            v[5] = 0x1BFD;
        }
    case 1:
        f_UpdateFishermensTownCamera();
        break;
    }
}

extern s16 D_800E7FFE;
extern u8 D_800BF821;
void func_8010DBE4(u8 *a) {
    s32 d;

    if (D_800E7FFE & 0x8000) {
        M2C_FIELD(a, s16 *, 0x26) = 0;
        return;
    }
    if (D_800BF821 != 0) {
        M2C_FIELD(a, s16 *, 0x26) = -600;
        return;
    }
    if (D_1F800160_71b4 < 0x364D) {
        d = D_1F800160_71b4 - 0x2D50;
        M2C_FIELD(a, s16 *, 0x26) = 0;
        if (d > 0) {
            M2C_FIELD(a, s16 *, 0x26) = ((d * 0x7800) / 2300) >> 8;
        }
    }
}

void func_8010DC74(u8 *a, s32 target, s32 step) {
    s32 v = M2C_FIELD(a, s32 *, 0x28);

    if (v == target) {
        return;
    }
    if (v < target) {
        M2C_FIELD(a, s32 *, 0x28) = v + step;
        if (target < v + step) {
            M2C_FIELD(a, s32 *, 0x28) = target;
        }
    } else {
        M2C_FIELD(a, s32 *, 0x28) = v - step;
        if (v - step < target) {
            M2C_FIELD(a, s32 *, 0x28) = target;
        }
    }
}

extern s8 D_800BF808[];
extern u8 D_1F800137;
extern s32 D_1F80009C;
void func_8010DCB8(u8 *a, u8 *b) {
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
void func_8010DE0C(u8 *a, u8 *b) {
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

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8010DFD8);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_ResolveTombaSpecialCylinderContact);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_HandleFishermensTownTombaHazardsAndBounds);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_EnforceA00TombaBoundsAndInteriorExit);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_ResolveTombaType13ActorContact);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8010EC58);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8010F034);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_ResolveTombaBoxPartContact);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_ResolveTombaOrientedWallContact);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_ResolveActiveColliderOrientedWallContact);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80110024);

extern s8 D_1F800182[];
void func_80110298(void *arg0, void *arg1) {
    s32 temp_lo;
    s32 temp_s0_2;
    u32 temp_v1;
    void *temp_s0;
    void *var_s1;

    temp_s0 = arg0 + 0x60;
    var_s1 = arg1;
loop_1:
    if (func_80022E04(arg0, arg1, M2C_FIELD(var_s1, void **, 0xC0)) != 0) {
        if (M2C_FIELD(arg0, u8 *, 0x5F) == 0x10) {
            temp_v1 = (u8) M2C_FIELD(arg0, u8 *, 0x46) >> 1;
            if ((s32) temp_v1 >= 0) {
                if ((s32) temp_v1 < 2) {
                    temp_s0_2 = (s32) (func_80083F50(M2C_FIELD(temp_s0, s16 *, 8) + 0x800) * (M2C_FIELD(arg0, s16 *, 0x80) + M2C_FIELD(arg1, s16 *, 0x80))) >> 0xC;
                    temp_lo = func_80083E80(M2C_FIELD(temp_s0, s16 *, 8) + 0x800) * (M2C_FIELD(arg0, s16 *, 0x80) + M2C_FIELD(arg1, s16 *, 0x80));
                    M2C_FIELD(arg0, s16 *, 0x2E) = (s16) (M2C_FIELD(M2C_FIELD(var_s1, void **, 0xC0), u16 *, 0x2C) + temp_s0_2);
                    M2C_FIELD(arg0, s16 *, 0x36) = (s16) (M2C_FIELD(M2C_FIELD(var_s1, void **, 0xC0), u16 *, 0x34) - (temp_lo >> 0xC));
                    M2C_FIELD(arg0, u16 *, 0x32) = (u16) M2C_FIELD(M2C_FIELD(var_s1, void **, 0xC0), u16 *, 0x30);
                } else if ((s32) temp_v1 < 4) {
                    M2C_FIELD(arg0, u16 *, 0x32) = (u16) (M2C_FIELD(arg0, u16 *, 0x84) + (M2C_FIELD(M2C_FIELD(var_s1, void **, 0xC0), u16 *, 0x30) + M2C_FIELD(arg1, u16 *, 0x84)));
                }
            }
        }
        func_8001E860(arg0, arg1, M2C_FIELD(var_s1, void **, 0xC0), 0x200);
        *((s8 *)D_1F800182) = 0;
        return;
    }
    var_s1 += 4;
    if ((s32) var_s1 >= (s32) (arg1 + 8)) {
        return;
    }
    goto loop_1;
}

#define F16(p, o) M2C_FIELD(p, s16 *, o)
#define FU16(p, o) M2C_FIELD(p, u16 *, o)
extern s32 D_1F800088;
extern u8 *D_1F800084;
s32 func_8011040C(u8 *a, u8 *b, u8 *c) {
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

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_ResolveTombaOrientedPlatformContact);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80110CA0);

extern u8 **D_1F800158;

s32 func_80110DE8(u8 *a) {
    s8 r;
    u8 **l;
    u8 *e;
    s32 k;
    u8 t;

    r = D_800BF80D;
    if (r != 0) {
        return r;
    }
    l = D_1F800158;
    D_1F800182_5650 = *(u8 *)0x1F80015E;
    while (D_1F800182_5650 != 0) {
        e = *l;
        (D_1F800182_5650)--;
        l++;
        if ((e[0] & 1) && (t = e[2]) == 1 && e[3] == 0) {
            k = func_80110CA0(a, e);
            if (k == 2) {
                a[0] = k;
                a[4] = k;
                a[5] = 0;
                a[6] = 0;
                e[0] = k;
                e[4] = k;
                e[5] = t;
                e[6] = 0;
            }
            return 1;
        }
    }
    return 0;
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_ResolveCarriedChickSurfaceContact);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80111128);

#define H(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define U(p, o) (*(u16 *)((u8 *)(p) + (o)))
extern u16 D_1F80018E_f9ee;
extern u16 D_1F80018C;
extern u8 D_800BF840;
extern u16 D_1F80008C;

void f_ResolveTombaPlaneSwitchActorContact(u8 *a, u8 *b)
{
    s32 k;
    s32 g;
    s32 m;
    s32 c;
    s32 x, y;
    if (func_8002300C(a, b, H(b, 0x80) * 4) == 0) {
        return;
    }
    b[0x2B] = 1;
    if (D_1F800137 == 0) {
        m = U(a, 0x140) - 0x400;
        g = func_80085690(-(s16)(U(b, 0x36) - U(a, 0x36)), (s16)(U(b, 0x2E) - U(a, 0x2E))) << 4;
        if (abs((s16)(g - m * 16)) < 0x1000) {
            D_1F80018E_f9ee = 0x4100;
            D_1F80018C = U(a, 0x140) - 0x400;
            D_800BF840 = 0x42;
        } else {
            c = U(a, 0x140) + 0x400;
            if (abs((s16)(g - c * 16)) < 0x1000) {
                D_1F80018C = c;
                D_1F80018E_f9ee = 0x4200;
                D_800BF840 = 0x43;
            }
        }
    }
    if (H(a, 0x80) + H(b, 0x80) + 60 < D_1F80008C) {
        return;
    }
    b[0x2B] = 2;
    if (H(a, 0x80) + H(b, 0x80) < D_1F80008C) {
        return;
    }
    x = (func_80083F50(D_1F80009C + 0x800) * (H(a, 0x80) + H(b, 0x80))) >> 12;
    y = (func_80083E80(D_1F80009C + 0x800) * (H(a, 0x80) + H(b, 0x80))) >> 12;
    U(a, 0x2E) = U(b, 0x2E) + x;
    U(a, 0x36) = U(b, 0x36) - y;
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_ResolveActorPairType0Contact);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_ResolveActorPairType3Contact);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80111A00);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_ResolveTombaSelectedCompoundContact);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80111E18);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_ResolveTombaInteractiveCylinderContact);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_ResolveActiveColliderType0Contact);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_ResolveActorAgainstA00CollisionLists);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_ResolveA00ActorPairContacts);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_ResolveA00PlatformPairContacts);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_ResolveTombaQuestAndSpecialContacts);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_ResolveTombaActorContacts);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_ResolveActiveColliderStaticContacts);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_ResolveActiveColliderActorContacts);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateA00CollisionInteractions);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_FindTombaSupportActor);

extern s8 D_1F80027B[];
void func_801140D0(void *arg0) {
    if ((M2C_FIELD(arg0, u8 *, 0x181) == 0) && ((M2C_FIELD(arg0, u8 *, 0x146) != 4) || (*((u8 *)D_1F80027B) == 0))) {
        M2C_FIELD(arg0, s16 *, 0x6A) = 0;
        if (M2C_FIELD(arg0, u8 *, 5) == 6) {
            M2C_FIELD(arg0, u8 *, 5) = 0x32U;
            M2C_FIELD(arg0, u8 *, 0x149) = (u8) ((M2C_FIELD(arg0, u8 *, 0x149) & 1) | 2);
        } else {
            M2C_FIELD(arg0, u8 *, 5) = 0x1DU;
            M2C_FIELD(arg0, s8 *, 6) = 0;
        }
        M2C_FIELD(arg0, s8 *, 4) = 1;
        M2C_FIELD(arg0, s8 *, 7) = 0;
        if (M2C_FIELD(arg0, u8 *, 0x144) == 1) {
            M2C_FIELD(arg0, u8 *, 0x144) = 0U;
        }
    }
}

extern u8 D_800BF818;
extern u8 D_8014A258[];
extern u8 *D_1F800080_ddd3;
void func_8011415C(u8 *a, u8 *b) {
    s16 t;

    if (func_80024BD8(a, b, M2C_FIELD(b, u8 **, 0xC0)) != 0) {
        b[0x29] = 1;
        t = M2C_FIELD(b, s16 *, 0x80) + M2C_FIELD(a, s16 *, 0x80);
        a[0x164] = 1;
        a[0x15C] = 0;
        D_1F800080_ddd3 = b;
        D_1F800182_5650 = 0;
        M2C_FIELD(a, s16 *, 0x152) = t - 0xC;
    }
}

extern u8 *D_800F2738;
extern s16 D_1F80009C_c31a;
void func_801141C8(u8 *a) {
    u8 *p;
    s32 r;

    for (p = D_800F2738; p != NULL; p = M2C_FIELD(p, u8 **, 0x24)) {
        if ((p[0] & 1) && p[0x2B] == 0) {
            if (func_80022F04(p, a) != 0) {
                if (func_80077768(0, D_1F80009C_c31a, 0) != 0) {
                    a[0x2B] = 4;
                } else {
                    a[0x2B] = 2;
                }
                func_8001E860(p, a, 0, 0);
                r = 1;
            } else {
                r = 0;
            }
            if (r != 0) {
                break;
            }
        }
    }
}

void func_80114290(u8 *a, u8 *b) {
    if (func_80111A00(a, b, M2C_FIELD(b, u8 **, 0xC8)) != 0) {
        D_1F800080_ddd3 = b;
        a[0x15C] = 0;
        a[0x164] = 1;
        b[0x29] = 1;
    } else if ((M2C_FIELD(b, u16 *, 0x60) & 2) && func_80111A00(a, b, M2C_FIELD(b, u8 **, 0xCC)) != 0) {
        D_1F800080_ddd3 = b;
        a[0x15C] = 1;
        a[0x164] = 1;
        b[0x29] = 0x81;
    }
}

void func_80114320(u8 *a, u8 *b) {
    if (func_80024338(a, b) != 0) {
        if (b[3] == 1) {
            M2C_FIELD(a, s16 *, 0x156) = -0x58;
        } else {
            M2C_FIELD(a, s16 *, 0x156) = -0x1E;
        }
        M2C_FIELD(a, s16 *, 0x152) = M2C_FIELD(b, u16 *, 0x80) + M2C_FIELD(a, u16 *, 0x80) - 12;
        b[0x5E] = 1;
        a[0x164] = 1;
        D_1F800080_ddd3 = b;
        D_1F800182_5650 = 0;
    }
}

typedef struct { u8 pad[0x60]; s32 unk60; s32 unk64; } AreaStateF58;
extern s8 *D_800ECF58[];
extern u8 D_8014C0BC[];
extern u8 D_8014DE54[];
void func_801143A4(u8 *a, u8 *b) {
    if (func_80022F04(a, b) != 0) {
        b[0x2B] = 1;
        b[0x46] = M2C_FIELD(a, u16 *, 0x56) >> 4;
        func_8001E860(a, b, 0, 0);
        D_1F800182_5650 = 0;
    }
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80114408);

s32 func_80114528(s32 arg0, s32 arg1) {
    return func_8010EC58(arg0, arg1, M2C_FIELD(arg1, s32 *, 0xC0));
}

typedef struct { u8 pad[0xC0]; u8 *parts[1]; } PartsOwner;

void f_ResolveTombaMultipartActorContact(u8 *a, PartsOwner *b) {
    s32 i;

    for (i = 2; i < b->pad[8] - 1; i++) {
        if (F16(b->parts[i], 0x16) == 2) {
            return;
        }
        if (i == b->pad[8] - 2 && F16(b->parts[b->pad[8] - 1], 0x16) == 0) {
            if (func_80022E04(a, b, b->parts[i]) != 0) {
                b->pad[0x29] = 1;
                b->pad[0x47] = func_80077768((s16)D_1F80009C, F16(a, 0x56), 1);
                return;
            }
        } else if (func_8001F650(a, b, b->parts[i]) != 0) {
            return;
        }
    }
}

s32 func_80114640(s32 arg0, s32 arg1) {
    return func_8010F034(arg0, arg1, M2C_FIELD(arg1, s32 *, 0xC4));
}

void func_80114664(u8 *a, u8 *b) {

    b[0x29] = 0;
    switch (f_ResolveTombaBoxPartContact(a, b, M2C_FIELD(b, u8 **, 0xC4), 1)) {
    case 0:
        break;
    case 2:
        goto hit;
    }
    switch (f_ResolveTombaBoxPartContact(a, b, M2C_FIELD(b, u8 **, 0xC0), 0)) {
    case 0:
        break;
    case 2:
    hit:
        b[0x29] = 1;
        break;
    }
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_801146E0);

extern s8 D_1F800182[];
void func_8011479C(s32 arg0, M2C_UNK arg1) {
    if (func_80022F04() != 0) {
        func_8001E860(arg0, arg1, 0, 0);
        *((s8 *)D_1F800182) = 0;
    }
}

void func_801147EC(u8 *a, u8 *b) {
    u16 t, u;

    if (func_80024BD8(a, b, M2C_FIELD(b, u8 **, 0xC4)) != 0 && a[0x147] == 0) {
        if (M2C_FIELD(M2C_FIELD(b, u8 **, 0xC4), s32 *, 0x2C) - M2C_FIELD(b, s16 *, 0x80) >= M2C_FIELD(a, s16 *, 0x2E)) {
            M2C_FIELD(a, s16 *, 0x156) = 20;
            t = M2C_FIELD(b, u16 *, 0x80);
            u = M2C_FIELD(a, u16 *, 0x80);
            a[0x164] = 2;
            D_1F800080_ddd3 = b;
            D_1F800182_5650 = 0;
            M2C_FIELD(a, s16 *, 0x152) = -(t + u);
        }
    }
}

extern void *D_1F800080;
void func_80114888(u8 *a, u8 *b)
{
    if (func_8011040C(a, b, *(void **)(b + 0xC0)) != 0) {
        a[0x164] = 3;
        D_1F800080 = b;
        D_1F800182_5650 = 0;
    }
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_801148D8);

extern void *D_1F800080;
extern u8 D_1F800182_5650;
void func_8011499C(u8 *a, u8 *b)
{
    if (func_80024BD8(a, b, *(void **)(b + 0xC4)) != 0) {
        b[0x29] = 1;
        a[0x164] = 3;
        D_1F800080 = b;
        D_1F800182_5650 = 0;
    }
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_ResolveActorPairMultipartContact);

void func_80114AF4(u8 *a, u8 *b) {
    s32 r = func_80023D48(a, b, M2C_FIELD(b, u8 **, 0xC8), 0);

    if (r != 0) {
        if (r == 2) {
            a[0x5F] = b[0x5E];
        }
        D_1F800182_5650 = 0;
    } else if (M2C_FIELD(b, u16 *, 0x60) & 2) {
        if (func_80023D48(a, b, M2C_FIELD(b, u8 **, 0xCC), 0) == 2) {
            a[0x5F] = b[0x5E];
            D_1F800182_5650 = 0;
        }
    }
}

extern u8 *D_8014C804_6a3a;
extern u16 D_8014C800;
void func_80114B8C(u8 *a, u8 *b) {
    if (func_80023870(a, b, M2C_FIELD(b, u8 **, 0xC0)) != 0) {
        D_1F800182_5650 = 0;
    }
}

void func_80114BBC(u8 *a, u8 *b) {
    s32 k = 3;

    if (f_ResolveActorPairType3Contact(a, b, M2C_FIELD(b, u8 **, 0xC0), a[2] == k) != 0) {
        if (a[2] == k && b[0x5F] == 1) {
            a[0] = k;
            a[0x2B] = D_1F80009C >> 4;
            a[4] = 2;
            a[5] = 0;
            a[6] = 0;
        }
        D_1F800182_5650 = 0;
    }
}

void func_80114C5C(u8 *a, s32 b) {
    if (b == 0) {
        D_800BF871 = 0;
        return;
    }
    if (a[0x2A] >= 0x16 && a[0x2A] < 0x19) {
        D_800BF871 = 8;
        return;
    }
    if (a[0x2A] == 0x22) {
        if (M2C_FIELD(a, s16 *, 0x2E) >= 0x4753) {
            D_800BF871 = 3;
            return;
        }
        D_800BF871 = 2;
    }
}

typedef struct { u8 pad0[7]; u8 unk7; u8 pad8[6]; u8 unkE; u8 unkF; u8 pad10[0x21]; u8 unk31; s16 unk32; } AreaState808_E;
extern AreaState808_E D_800BF808_9a69;
extern s8 D_800BF9E5;
extern u8 D_1F800236;
void func_80114CD0(u8 *a) {
    AreaState808_E *g = &D_800BF808_9a69;

    if (g->unkE != 0 && g->unkF == 2 && M2C_FIELD(a, s16 *, 0x32) < -0xE74 && M2C_FIELD(a, s16 *, 0x36) < 0x1451) {
        D_1F800137 = 2;
        g->unk7 = 2;
        g->unk31 = 1;
        g->unk32 = 0x100;
        D_1F800236 = 1;
    }
}

extern u8 D_800E7FEB;
void func_80114D48(u8 *a) {
    u8 *g = D_800BF808_1760;
    u16 lim = M2C_FIELD(g, u16 *, 0xA);

    switch (g[0xF]) {
    case 2:
        if (D_800E7FEB != 8) {
            break;
        }
        if (M2C_FIELD(a, s16 *, 0x36) < 0x1A05) {
            M2C_FIELD(a, s16 *, 0x36) = 0x1A04;
        }
    case 0:
    case 1:
        if (!(a[0x145] & 1) && M2C_FIELD(a, s16 *, 0x32) >= (s16)lim - M2C_FIELD(a, s16 *, 0x62)) {
            M2C_FIELD(a, s16 *, 0x32) = lim - M2C_FIELD(a, u16 *, 0x62);
            func_80022C78(a);
        }
        break;
    }
}

s32 func_80114DF4(u8 *a, u8 *b) {
    if (func_80022F04(a, b) != 0) {
        if (func_80077768(0, D_1F80009C_c31a, 0) != 0) {
            b[0x2B] = 4;
        } else {
            b[0x2B] = 2;
        }
        func_8001E860(a, b, 0, 0);
        return 1;
    }
    return 0;
}

extern s16 D_1F800162;
extern s16 D_1F800164_d75f;
void func_80114E74(u8 *a, u8 *b) {
    if (a[0x164] != 5 || a[0x147] != b[0x47]) {
        if (func_80022F04(a, b) != 0) {
            b[0] = 2;
            b[4] = 2;
            b[5] = 0;
            b[6] = 0;
        }
    }
}

void func_80114ED4(u8 *a, u8 *b) {
    s32 i;

    for (i = 0; i < 2; i++) {
        if (func_80023D48(a, b, ((u8 **)(b + 0xC0))[i], 0) != 0) {
            D_1F800182_5650 = 0;
            return;
        }
    }
}

extern s8 D_1F800182[];
void func_80114F54(s32 arg0, void *arg1) {
    if (func_80022F04() != 0) {
        M2C_FIELD(arg1, s8 *, 0) = 2;
        M2C_FIELD(arg1, s8 *, 4) = 2;
        M2C_FIELD(arg1, s8 *, 5) = 0;
        *((s8 *)D_1F800182) = 0;
    }
}

extern u8 *D_1F800184_6cc7;
extern s16 D_1F80018E;
void func_80114F94(u8 *a, u8 *b) {
    b[0x29] = 0;
    if (a[0x16B] != 0) {
        if (D_1F800184_6cc7 == b) {
            f_ResolveTombaSelectedCompoundContact(a, b, M2C_FIELD(b, u8 **, 0xC4));
        }
        return;
    }
    switch (func_80111E18(a, b, M2C_FIELD(b, u8 **, 0xC8))) {
    case 2:
        b[0x29] = 1;
        if (D_1F80018E != 0) {
            D_1F80018E = 0x10;
        }
        break;
    case 0:
        if ((M2C_FIELD(b, u16 *, 0x60) & 2) && func_80111E18(a, b, M2C_FIELD(b, u8 **, 0xCC)) == 2) {
            b[0x29] = 0x81;
            if (D_1F80018E != 0) {
                D_1F80018E = 0x20;
            }
        }
        break;
    }
}

s32 func_80115084(s32 arg0, s32 arg1) {
    return func_8001F650(arg0, arg1, M2C_FIELD(arg1, s32 *, 0xC0));
}

s32 func_801150A8(s32 arg0, s32 arg1) {
    return f_ResolveTombaInteractiveCylinderContact(arg0, arg1, M2C_FIELD(arg1, s32 *, 0xC0));
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_801150CC);

void func_801151F4(u8 *a, u8 *b)
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

// nearcopy: 7 words off, C from a01 func_80110CB8
#include "common.h"
#include "game.h"
#include "m2c.h"
extern u8 D_1F800183;
extern u8 **D_1F800154;
extern u8 D_1F80015C;
void f_ResolveA00ActiveActorCollisionCandidates(void) {
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
            case 7:
                f_ResolveActorAgainstA00CollisionLists(a);
                break;
            }
        }
    }
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8011534C);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80115598);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_801158E0);

typedef struct { s16 x, y, w, h; } ClutRect;
typedef struct {
    u8 *ptr;
    u8 *clut;
    s16 x;
    s16 y;
} ClutCycle;

// nearcopy: 5 words off, C from a07 func_80113C20
#include "common.h"
#include "game.h"
#include "m2c.h"
extern ClutCycle D_80147D84[];
extern s8 D_8014C4F0[];
extern u8 D_800BF873;
void func_80115B88(s32 arg0) {
    ClutRect r;
    s32 i;
    ClutCycle *e;
    u8 *data;

    if (arg0 == 0) {
        s8 *p;
        i = 11;
        p = &D_8014C4F0[i];
        do {
            *p-- = 0;
        } while (--i >= 0);
        return;
    }
    e = D_80147D84;
    for (i = 0; i < 12; i++, e++) {
        if (--D_8014C4F0[i] <= 0) {
            if (e->ptr[0] == 0xFF) {
                e->ptr -= e->ptr[1];
            }
            data = e->clut + e->ptr[0] * 32;
            D_8014C4F0[i] = e->ptr[1];
            r.x = e->x;
            r.y = e->y;
            r.w = 16;
            r.h = 1;
            func_80081218(&r, data);
            e->ptr += 2;
        }
    }
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_SpawnFishermensTownActorsFromPlacementTable);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80116094);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateFishermensTownAmbientAudio);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_801167AC);

INCLUDE_ASM("asm/a00/nonmatchings/a00", block);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateCrabBasketRewardDrop);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80116E3C);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_HandleKainenHouseQuestItemActor);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80117228);

void f_HandleBeachQuestPickup();
void f_HandleTownQuestRewardVisualActor();
void func_80117228();
void f_HandleFeedChicksSceneActor();
void f_HandleTownCreatureActor();
u8 *f_SpawnCrabBasketRewardActor(s32 a, s32 b) {
    u8 *p = func_80072DDC(a, 129, 5, 1);

    if (p == NULL) {
        return NULL;
    }
    p[0x3] = 1;
    p[0x5E] = b;
    M2C_FIELD(p, void **, 0x1C) = func_80117228;
    return p;
}

void func_80117460(u8 *a) {
    if (func_80051B70(a, 1, 2) == 0) {
        M2C_FIELD(a, s16 *, 0x80) = 0x28;
        M2C_FIELD(a, s16 *, 0x82) = 0x50;
        M2C_FIELD(a, s16 *, 0x84) = 0x4B;
        M2C_FIELD(a, s16 *, 0x86) = 0x73;
        M2C_FIELD(a, s16 *, 0x54) = 0;
        M2C_FIELD(a, s16 *, 0x56) = 0;
        M2C_FIELD(a, s16 *, 0x58) = 0;
        a[0x29] = 0;
        if (*(u8 *)&D_800BF9E5 == 4) {
            a[0x5E] = 1;
        }
    }
}

typedef struct {
    s16 x, y, z;
} SVec3T;
extern SVec3T D_1F8000C0_4e9b;
extern u8 D_800BF9E5_1228;
void func_801174D8(u8 *a) {
    s32 n;
    u8 *g;

    M2C_FIELD(a, s16 *, 0x54) = 0x800;
    g = D_800E7E80;
    n = 3;
    if (g[0x145] == 0 || g[0x146] != 0) {
        D_1F8000C0_4e9b.x = 6;
        D_1F8000C0_4e9b.y = 0xA;
        D_1F8000C0_4e9b.z = 0x1C;
    } else {
        n = 4;
        D_1F8000C0_4e9b.x = 0x3C;
        D_1F8000C0_4e9b.y = 8;
        D_1F8000C0_4e9b.z = 0x48;
    }
    if (D_800BF9E5_1228 == 7) {
        a[4] = 3;
        return;
    }
    func_80051614(a, &D_1F8000C0_4e9b, n, 0);
    a[1] = 1;
    func_80077EFC(a);
}

void func_801175A8(void *arg0) {
    if ((M2C_FIELD(arg0, u8 *, 5) == 0) && (func_80040C00(6) >= 0)) {
        func_80040B48(7);
        func_8004D4C4(0x29, 1);
        func_8004B0D8(arg0);
        M2C_FIELD(arg0, s8 *, 0x5E) = 2;
        M2C_FIELD(arg0, s8 *, 4) = 1;
        M2C_FIELD(arg0, u8 *, 5) = 0U;
        M2C_FIELD(arg0, s8 *, 6) = 0;
        D_800BF9E5 = 6;
    }
}

void func_80117628(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x5E) == 0) {
        f_HandleKainenHouseQuestItemActor();
    }
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_HandleRareFishOrBlueBucketPickup);

void f_HandleRareFishOrBlueBucketPickup();
u8 *f_SpawnRareFishPickup(u8 *a) {
    GameState *g = &D_800BF870;
    u8 *p;

    if (g->pad1[0x27D] == 0) {
        if (g->pad1[0x14F] & 1) {
            return NULL;
        }
        p = func_8007A980(0, 5, 0);
        if (p != NULL) {
            M2C_FIELD(p, void **, 0x1C) = f_HandleRareFishOrBlueBucketPickup;
            M2C_FIELD(p, u8 **, 0x10) = a + 0x60;
            p[2] = 2;
            p[3] = 0;
            return p;
        }
    }
    return NULL;
}

extern s32 D_800ECF80;
extern u8 D_8014C808[];
void func_80117D7C(u8 *a) {
    u8 *p;

    a[0xB] = 0x10;
    a[8] = 0xF8;
    a[0x47] = 0;
    M2C_FIELD(a, s16 *, 0x5A) = 0;
    a[0xD] = 0;
    p = M2C_FIELD(a, u8 **, 0x10);
    M2C_FIELD(a, s32 *, 0x3C) = D_800ECF80;
    func_80077B38(a, D_8014C808, 1);
    M2C_FIELD(a, s32 *, 0x2C) = 0x13D20000;
    M2C_FIELD(a, s32 *, 0x30) = 0xF7E00000;
    M2C_FIELD(a, s32 *, 0x34) = 0x15AA0000;
    M2C_FIELD(a, s16 *, 0x80) = 0x3C;
    M2C_FIELD(a, s16 *, 0x82) = 0x78;
    M2C_FIELD(a, s16 *, 0x84) = 0x50;
    M2C_FIELD(a, s16 *, 0x86) = 0xA0;
    a[0] = 4;
    M2C_FIELD(p, s16 *, 6) = M2C_FIELD(a, s16 *, 0x2E);
    M2C_FIELD(p, s16 *, 8) = M2C_FIELD(a, s16 *, 0x32) - 0x1A4;
    M2C_FIELD(p, s16 *, 0xA) = M2C_FIELD(a, s16 *, 0x36);
    M2C_FIELD(p, s16 *, 0x16) = 0x1E;
    a[4]++;
    func_8004B354(a, 0);
}

void func_80117E5C(void *arg0) {
    func_8004D4C4(0x3A, 1);
    func_8004B0D8(arg0);
    M2C_FIELD(arg0, s8 *, 4) = 3;
}

void func_80117E98(u8 *a) {
    s16 *q = M2C_FIELD(a, s16 **, 0x10);
    s16 x, y, z;

    if (func_8007778C(a) != 0) {
        if (a[5] == 2) {
            x = D_1F800160_71b4;
            y = D_1F800162;
            z = D_1F800164_d75f;
            M2C_FIELD(a, s16 *, 0x2E) = x;
            M2C_FIELD(a, s16 *, 0x32) = y;
            M2C_FIELD(a, s16 *, 0x36) = z;
        } else {
            M2C_FIELD(a, s16 *, 0x2E) = q[0] - 0x20;
            M2C_FIELD(a, s16 *, 0x32) = q[1] + 0x50;
        }
        func_80077B5C(a);
        func_8004B374(a, 0);
    }
}

extern u8 D_800BF9DC;
void f_HandleRareFishOrBlueBucketPickup();
u8 *f_SpawnBlueBucketPickup(u8 *a) {
    u8 *p;

    if (!(D_800BF9DC & 1)) {
        p = func_8007A980(1, 5, 0);
        if (p != NULL) {
            M2C_FIELD(p, void **, 0x1C) = f_HandleRareFishOrBlueBucketPickup;
            M2C_FIELD(p, u8 **, 0x10) = a + 0x60;
            p[2] = 2;
            p[3] = 1;
            return p;
        }
    }
    return NULL;
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80117FAC);

#define FP(p, o) M2C_FIELD(p, u8 **, o)

void func_801180CC(u8 *a) {
    u8 *p = FP(a, 0x10);
    u8 *c;

    if (*(u8 *)0x1F800207 < 5 && func_8007778C() != 0) {
        if (a[5] == 2) {
            u16 x = D_1F800160_71b4;
            u16 y = D_1F800162;
            u16 z = D_1F800164_d75f;
            F16(a, 0x2E) = x;
            F16(a, 0x32) = y;
            F16(a, 0x36) = z;
        } else {
            F16(a, 0x2E) = FU16(p, 0) + ((F16(FP(a, 0xC0), 0x1A) * 9) >> 8);
            F16(a, 0x32) = FU16(p, 2) + ((F16(FP(a, 0xC0), 0x20) * 9) >> 8);
            F16(a, 0x58) = -FU16(p, 0xC);
        }
        func_800517F8(a);
        func_8004B374(a, 1);
    }
}

void func_801181BC(void *arg0, void *arg1) {
    if (M2C_FIELD(arg0, u8 *, 0x2B) == 2) {
        M2C_FIELD(arg1, s16 *, 0x14) = 0x2000;
        return;
    }
    M2C_FIELD(arg1, s16 *, 0x14) = -0x2000;
}

void func_801181E0(u8 *a, u8 *b) {
    if (a[0x2B] == 2) {
        if (M2C_FIELD(b, s16 *, 0xE) < 0x800) {
            M2C_FIELD(b, s16 *, 0xE) -= 0x1000;
        } else {
            M2C_FIELD(b, s16 *, 0xE) = -M2C_FIELD(b, s16 *, 0xE);
        }
        M2C_FIELD(b, s16 *, 0x14) = 0xC00;
    } else {
        if (M2C_FIELD(b, s16 *, 0xE) < -0x7FF) {
            M2C_FIELD(b, s16 *, 0xE) = -M2C_FIELD(b, s16 *, 0xE);
        } else {
            M2C_FIELD(b, s16 *, 0xE) += 0x1000;
        }
        M2C_FIELD(b, s16 *, 0x14) = -0xC00;
    }
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_HandleBeachQuestPickup);

u8 *func_8011884C(s32 a, s32 b) {
    u8 *p = func_80072DDC(a, 0, 5, 3);

    if (p == NULL) {
        return NULL;
    }
    p[0x3] = 2;
    M2C_FIELD(p, s16 *, 0x60) = b;
    M2C_FIELD(p, void **, 0x1C) = f_HandleBeachQuestPickup;
    return p;
}

void func_801188A0(u8 *a) {
    a[4] = 3;
    func_8004D4C4(0x78, 1);
    func_8004B0D8(a);
    D_800BF870.pad1[0x179] &= ~(1 << M2C_FIELD(a, s16 *, 0x60));
    D_800BF870.pad1[0x179] &= ~(1 << (M2C_FIELD(a, s16 *, 0x60) + 4));
    func_80040C00(0x4E);
}

u8 *f_SpawnGoldFishhookPickup(s32 a, s32 b) {
    u8 *p = func_80072DDC(a, 0, 5, 3);

    if (p == NULL) {
        return NULL;
    }
    p[0x3] = 1;
    p[0x5E] = b;
    M2C_FIELD(p, void **, 0x1C) = f_HandleBeachQuestPickup;
    return p;
}

u8 *func_80118974(s32 a) {
    u8 *p = func_80072DDC(a, 0, 5, 3);

    if (p == NULL) {
        return NULL;
    }
    p[0x3] = 0;
    M2C_FIELD(p, void **, 0x1C) = f_HandleBeachQuestPickup;
    return p;
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_801189B8);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80118B10);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80118DB0);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateA00PickupHandlerCase9);

void func_80119160(void *arg0, s32 arg1, void *arg2) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 6);
    switch (temp_v1) {                              /* irregular */
    case 0:
        M2C_FIELD(arg0, s16 *, 0x4A) = -0x800;
        M2C_FIELD(arg0, u8 *, 6) = 1U;
        M2C_FIELD(arg0, u16 *, 0x50) = 0x180U;
        /* fallthrough */
    case 1:
        M2C_FIELD(arg0, s32 *, 0x30) = (s32) (M2C_FIELD(arg0, s32 *, 0x30) + (M2C_FIELD(arg0, s16 *, 0x4A) << 8));
        M2C_FIELD(arg0, s16 *, 0x4A) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0x4A) + M2C_FIELD(arg0, u16 *, 0x50));
        if ((M2C_FIELD(arg2, s32 *, 0x30) - 0x8C) < M2C_FIELD(arg0, s16 *, 0x32)) {
            M2C_FIELD(arg0, s16 *, 0x4A) = -0x800;
            M2C_FIELD(arg0, u16 *, 0x50) = 0x300U;
            M2C_FIELD(arg0, u8 *, 6) = (u8) (M2C_FIELD(arg0, u8 *, 6) + 1);
            return;
        }
        return;
    case 2:
        M2C_FIELD(arg0, s32 *, 0x30) = (s32) (M2C_FIELD(arg0, s32 *, 0x30) + (M2C_FIELD(arg0, s16 *, 0x4A) << 8));
        M2C_FIELD(arg0, s16 *, 0x4A) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0x4A) + M2C_FIELD(arg0, u16 *, 0x50));
        if ((M2C_FIELD(arg2, s32 *, 0x30) - 0x8C) < M2C_FIELD(arg0, s16 *, 0x32)) {
            M2C_FIELD(arg0, s8 *, 5) = 1;
            M2C_FIELD(arg0, u8 *, 6) = 0U;
        }
        return;
    }
}

extern u8 D_801485F0[];

void func_80119254(u8 *a) {
    u8 *p = FP(a, 0x10);
    u16 t;

    switch (a[6]) {
    case 0:
        a[6] = 1;
        a[0x2A] = D_801485F0[F16(a, 0x40)];
        F16(a, 0x2E) = FU16(p, 0x2C);
        F16(a, 0x32) = FU16(p, 0x30) + 0xF0;
        t = FU16(p, 0x34);
        F16(a, 0x4A) = 0x1000;
        F16(a, 0x50) = 0x200;
        F16(a, 0x36) = t;
        break;
    case 1:
        M2C_FIELD(a, s32 *, 0x30) += F16(a, 0x4A) << 8;
        F16(a, 0x4A) += FU16(a, 0x50);
        func_8004766C(a);
        if (func_80049250(a, 0, (s16)(FU16(a, 0x86) - FU16(a, 0x84))) != 0) {
            a[6]++;
        }
        break;
    case 2: break;
    }
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80119350);

void func_80119454(u8 *a) {
    u8 *q = M2C_FIELD(a, u8 **, 0x10);

    switch (a[5]) {
    case 0:
        a[5]++;
        a[0] = 1;
        M2C_FIELD(a, s16 *, 0x54) = 0xC00;
        M2C_FIELD(a, s16 *, 0x56) = 0x200;
        func_8004B354(a, 1);
    case 1:
        M2C_FIELD(a, s16 *, 0x2E) = M2C_FIELD(q, s16 *, 0x2C);
        M2C_FIELD(a, s16 *, 0x32) = M2C_FIELD(q, s16 *, 0x30) - 0x14;
        M2C_FIELD(a, s16 *, 0x36) = M2C_FIELD(q, s16 *, 0x34);
        if (func_8007778C(a) != 0) {
            func_80051844(a);
            func_8004B374(a, 1);
        }
        break;
    }
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80119510);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_SubmitPendingGoldenCrabs);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80119828);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_HandleGoldenCrabDialogueFirstVisit);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_HandleGoldenCrabDialogueRepeatVisit);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_StageWindmillCutsceneActor);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_ApplyWindmillCutsceneTransition);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_RunWinsWindmillCutscene);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_HandleWinConversationState);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8011A804);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8011A928);

extern u8 *D_1F800214;
s32 func_8011AB00(u8 *a) {
    u8 *t = D_1F800214;

    switch (a[0x78]) {
    case 0:
        M2C_FIELD(a, s16 *, 0x42) = func_800782B0(t + 0x2C, M2C_FIELD(a, s16 *, 0x2E), M2C_FIELD(a, s16 *, 0x36)) & 0xFFF;
        a[0x78]++;
        break;
    case 1:
        return func_80041438(t, M2C_FIELD(a, s16 *, 0x42), 0x100);
    }
    return 0;
}

s32 func_8011AB84(u8 *a) {
    switch (a[0x78]) {
    case 0:
        M2C_FIELD(a, s16 *, 0x42) = 15;
        a[0x78]++;
        D_800BF818 = 8;
        goto end;
    case 1:
        if (--M2C_FIELD(a, s16 *, 0x42) == 0) {
            return 1;
        }
    end:
    default:
        return 0;
    }
}

s32 func_8011ABF0(u8 *a) {
    switch (a[0x78]) {
    case 0:
        M2C_FIELD(a, s16 *, 0x42) = 18;
        a[0x78]++;
        D_800BF818 = 9;
        goto end;
    case 1:
        if (--M2C_FIELD(a, s16 *, 0x42) == 0) {
            return 1;
        }
    end:
    default:
        return 0;
    }
}

s32 func_8011AC5C(u8 *a) {
    s32 i;

    a[0x5F] = 0;
    if (D_800BF870.pad1[0x172] == 0) {
        return 0;
    }
    for (i = 0; i < 3; i++) {
        if (((D_800BF870.pad1[0x172] >> i) & 1) && !((D_800BF870.pad1[0x172] >> (i + 4)) & 1)) {
            a[0x5F] |= 1 << i;
        }
    }
    return a[0x5F];
}

s32 func_8011ACDC(u8 *a) {
    s32 i;
    s32 k;
    u8 *e;
    GameState *g;
    s32 one;

    i = 0;
    g = &D_800BF870;
    one = 1;
    do {
        if ((a[0x5F] >> i) & 1) {
            k = i + 4;
            e = func_8011C610(a, k);
            if (e != NULL) {
                e[0x28] |= 0x80;
                g->pad1[0x172] |= one << k;
                a[0x5F] -= one << i;
                func_8004D604(0x2A, 1);
                return 1;
            }
        }
        i++;
    } while (i < 3);
    return 0;
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateWindmillExplosionDebris);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateWindmillFallingActor);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8011B738);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8011BC3C);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8011BDB8);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateKainenHouseSceneActor);

void func_8011C090(u8 *a) {
    GameState *g;
    u8 v;

    if (D_800BF80D == 0) {
        g = &D_800BF870;
        v = g->pad1[0x172];
        func_8004ED94((v & 1) + ((v >> 1) & 1) + ((v >> 2) & 1) + 0x26, 0x42);
        func_8004B0D8(a);
        func_8004D4F4(0x2A, 1);
        v = g->pad1[0x172] |= 1 << a[3];
        if ((v & 3) == 3) {
            g->pad1[0x174] = 7;
        }
        if ((v & 7) == 7) {
            func_80040C00(7);
            func_80040B48(8);
        }
    }
    a[4] = 3;
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_HandleGoldenCrabAndWindmillActor);

void f_HandleGoldenCrabAndWindmillActor();
void func_80135D64();
void f_HandleCurvedSupportContactActor();
void func_8013A900();
u8 *func_8011C610(s32 a, u8 b) {
    u8 *p = func_8007A980(0, 2, 0);

    if (p == NULL) {
        return NULL;
    }
    M2C_FIELD(p, void **, 0x1C) = f_HandleGoldenCrabAndWindmillActor;
    M2C_FIELD(p, s32 *, 0x10) = a;
    p[0x2] = 4;
    p[0x3] = b;
    return p;
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_HandleNetBridgeRaiseNpcInteraction);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8011CA04);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8011CBD0);

extern void *D_800ECF94;
extern u8 D_8014BFB4[];
void func_8011CD14(u8 *a) {
    switch (a[7]) {
    case 0:
        if (a[1] != 0 && func_800519E0(a, 0xF, D_800ECF94, D_8014BFB4) == 0) {
            a[7]++;
        }
        break;
    case 1:
        if (a[1] == 0) {
            func_8007ADDC(a);
            a[7]--;
        }
        break;
    }
}

s32 func_8011CDB8(u8 *a) {
    switch (a[0x78]) {
    case 0:
        M2C_FIELD(a, s16 *, 0x72) = 5;
        a[0x78]++;
        break;
    case 1:
        if (--M2C_FIELD(a, s16 *, 0x72) == 0) {
            D_800BF818 = 7;
            M2C_FIELD(a, s16 *, 0x72) = 20;
            a[0x78]++;
        }
        break;
    case 2:
        if (--M2C_FIELD(a, s16 *, 0x72) == 0) {
            return 1;
        }
        break;
    }
    return 0;
}

s32 func_8011CE64(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x7A) == 1) {
        func_80040B48(0x4E);
    }
    return 1;
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_AdvanceKainenHouseRescueSequence);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_HandleKainenInteraction);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_HandleKainenNpcActor);

extern u8 *D_800ECFB8;
extern u8 D_8014934C[];
void func_8011D82C(u8 *a) {
    u8 *base = D_800ECFB8;
    s32 *t = (s32 *)(base + 4);
    s32 v;

    switch (D_8014934C[a[0x46]]) {
    case 0:
        M2C_FIELD(M2C_FIELD(a, u8 **, 0xD0), u8 **, 0x40) = base + t[4];
        v = t[7];
        break;
    case 1:
        M2C_FIELD(M2C_FIELD(a, u8 **, 0xD0), u8 **, 0x40) = base + t[13];
        v = t[14];
        break;
    default:
        return;
    }
    M2C_FIELD(M2C_FIELD(a, u8 **, 0xDC), u8 **, 0x40) = base + v;
}

s32 func_8011D8AC(u8 *a) {
    AreaStateF58 *g = (AreaStateF58 *)D_800ECF58;
    s32 t;

    if (func_800519E0(a, 0xD, g->unk60, D_8014C0BC) == 0) {
        t = g->unk64;
        M2C_FIELD(a, u8 **, 0x7C) = D_8014DE54;
        M2C_FIELD(a, s32 *, 0x3C) = t;
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8011D910);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_HandleFeedChicksSceneActor);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_InitializeFeedChicksSceneActor);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateFeedChicksActorSplinePatrol);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateFeedChicksActorEndpointTransit);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8011E7CC);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateFeedChicksActorRoaming);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8011F088);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateFeedChicksActorTombaReaction);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateFeedChicksActorRecoveryOrExit);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8011FC78);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_ResolveFeedChicksActorFacingAngle);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8011FF78);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_TryStartFeedChicksActorTombaReaction);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_AdvanceFeedChicksActorMotion);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_801205EC);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_801206F4);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80120A64);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80120C50);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_HandleFeedTheChicksController);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_SelectFeedChicksNpcSpawn);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateFeedChicksNpcPresence);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8012138C);

s16 func_801214AC(u8 *a, s16 k) {
    s32 m = k << 5;

    if (((M2C_FIELD(a, s16 *, 0x66) - M2C_FIELD(a, s16 *, 0x56)) & 0xFFF) < 0x800) {
        if (M2C_FIELD(a, s16 *, 0x66) < M2C_FIELD(a, s16 *, 0x56)) {
            M2C_FIELD(a, s16 *, 0x66) += 0x1000;
        }
        return m;
    }
    if (M2C_FIELD(a, s16 *, 0x56) < M2C_FIELD(a, s16 *, 0x66)) {
        M2C_FIELD(a, s16 *, 0x66) -= 0x1000;
    }
    return -m;
}

extern s16 D_8014A240[];
s32 f_AdvanceFeedChicksActorTurn(u8 *a) {
    M2C_FIELD(a, s16 *, 0x56) += M2C_FIELD(a, s16 *, 0x50);
    if ((M2C_FIELD(a, s16 *, 0x50) > 0 && M2C_FIELD(a, s16 *, 0x56) >= M2C_FIELD(a, s16 *, 0x66)) ||
        (M2C_FIELD(a, s16 *, 0x50) < 0 && M2C_FIELD(a, s16 *, 0x56) <= M2C_FIELD(a, s16 *, 0x66))) {
        return 1;
    }
    return 0;
}

s32 func_80121574(void) {
    s32 r = func_8009A450() & 0xF;

    if (r < 5) {
        return 0x5A;
    }
    if (r < 11) {
        return 0x96;
    }
    return 0xD2;
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_CheckFeedChicksActorRoutePointDistance);

extern u8 D_8014E1A4[];
void func_8012175C(u8 *a) {
    if (a[6] == 0) {
        a[0x5E] = 0;
        a[0x1B] &= 0xBF;
        func_80077C40(a, D_8014E1A4, 7);
        func_80026100(6);
        func_80074590(0x99, 0, 0);
        M2C_FIELD(a, s16 *, 0x84) = 0x28;
        M2C_FIELD(a, s16 *, 0x86) = 0x50;
        a[6]++;
    }
    if (M2C_FIELD(a, s16 *, 0x72) == 0) {
        func_80076D68(a);
    }
}

extern s16 D_800E7ED6;
void func_801217F4(u8 *a) {
    if (a[3] == 0) {
        switch (M2C_FIELD(a, s16 *, 0x60)) {
        case 8:
        case 9:
        case 10:
        case 12:
        case 13:
        case 14:
            a[0x2A] = 1;
            return;
        case 3:
        case 4:
        case 5:
        case 16:
        case 17:
        case 18:
            a[0x2A] = 0xA;
            break;
        }
    }
}

void func_8012185C(void *arg0) {
    s16 temp_v1;

    temp_v1 = M2C_FIELD(M2C_FIELD(arg0, void **, 0x10), s16 *, 0xA);
    switch (temp_v1) {                              /* irregular */
    case 1:
        M2C_FIELD(arg0, s8 *, 4) = 3;
        return;
    case 2:
        M2C_FIELD(arg0, s8 *, 5) = 3;
        M2C_FIELD(arg0, s8 *, 6) = 0;
        M2C_FIELD(arg0, s8 *, 7) = 1;
        return;
    }
}

void f_SpawnFeedChicksNpc(u8 *a) {
    u8 *p = func_80072DDC((s32)a, 3, 2, 7);

    if (p != NULL) {
        M2C_FIELD(p, void **, 0x1C) = f_HandleFeedChicksSceneActor;
        p[3] = a[3];
        M2C_FIELD(p, s16 *, 0x6C) = M2C_FIELD(a, s16 *, 0x8);
        M2C_FIELD(a, u8 **, 0xC) = p;
        if (a[3] == 3) {
            M2C_FIELD(a, s32 *, 0x10) = 0x1E;
        } else {
            M2C_FIELD(a, s32 *, 0x10) = 0x546;
        }
    }
}

void func_80121918(s32 a, s32 b, s32 c) {
    u8 *p = func_80072DDC(a, 3, 2, 7);

    if (p != NULL) {
        M2C_FIELD(p, void **, 0x1C) = f_HandleFeedChicksSceneActor;
        p[0x3] = 6;
        M2C_FIELD(p, s16 *, 0x68) = b;
        p[0x5E] = c;
    }
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80121978);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80121B44);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80121CF8);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_FinishStuckFishhookLineSequence);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80121FD8);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_HandleStuckFishhookQuestNpc);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_HandleNetBridgeCutsceneTrigger);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80122974);

extern s16 D_1F8000C0[];
extern s16 D_1F8000C8[];
void func_80122BF4(u8 *a) {
    u8 *p;
    s16 *v;
    s16 *w;

    if (a[0xB] == 1) {
        p = M2C_FIELD(a, u8 **, 0xE8);
        v = D_1F8000C0;
        v[0] = 0;
        v[1] = -0x77;
        v[2] = 0;
        w = D_1F8000C8;
        func_800844C0(p + 0x18, v, w);
        M2C_FIELD(a, s16 *, 0x4E) = w[0] + M2C_FIELD(p, s16 *, 0x2C);
        M2C_FIELD(a, s16 *, 0x50) = w[1] + M2C_FIELD(p, s16 *, 0x30);
        M2C_FIELD(a, s16 *, 0x52) = w[2] + M2C_FIELD(p, s16 *, 0x34);
    }
}

extern u8 D_800BF8B9;
extern u8 D_8014E4EC[];
void func_80122CA4(u8 *a) {
    if (D_800BF8B9 != 0xFF) {
        a[4] = 3;
        return;
    }
    switch (a[6]) {
    case 0:
        a[6]++;
        a[0] = 2;
        M2C_FIELD(a, s16 *, 0x56) = 0x400;
        a[0xB] = 0;
        M2C_FIELD(a, s16 *, 0x40) = 8;
        func_80077CFC(a, D_8014E4EC, 4, 4);
        break;
    case 1:
        func_80076D68(a);
        break;
    }
    func_800518FC(a);
    func_8007778C(a);
}

void func_80122D58(u8 *a) {
    switch (a[5]) {
    case 0:
        a[5]++;
        a[0] = 2;
        a[0xB] = 1;
        M2C_FIELD(a, s16 *, 0x2E) = 0x3900;
        M2C_FIELD(a, s16 *, 0x32) = -0xAE0;
        M2C_FIELD(a, s16 *, 0x36) = 0x240;
        M2C_FIELD(a, s16 *, 0x56) = 0x400;
        func_80077CFC(a, D_8014E4EC, 4, 4);
        break;
    }
    if (func_8007778C(a) != 0) {
        func_80076D68(a);
        func_800518FC(a);
    }
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80122DF0);

s32 func_80122F0C(s32 a) {
    u8 *p = func_80072DDC(a, 0, 3, 16);

    if (p == NULL) {
        return 0;
    }
    p[0x3] = 6;
    M2C_FIELD(p, void **, 0x1C) = f_HandleTownQuestRewardVisualActor;
    return 1;
}

s32 func_80122F5C(s32 a) {
    u8 *p = func_80072DDC(a, 0, 3, 16);

    if (p == NULL) {
        return 0;
    }
    p[0x3] = 7;
    M2C_FIELD(p, void **, 0x1C) = f_HandleTownQuestRewardVisualActor;
    return 1;
}

extern u8 D_800BF9B5;
extern u8 D_801494FC[];
s32 func_80122FAC(u8 *a) {
    s32 one = 1;

    switch (a[6]) {
    case 0:
        if (a[0x2B] == 3) {
            a[6] = one;
            func_80042354(1, 1);
            D_800BF9B5 = one;
        }
        break;
    case 1:
        a[6] = 2;
        func_80040CDC(a, D_8014E4EC, D_801494FC);
        a[0x70] = 1;
        break;
    case 2:
        func_80041098(a);
        if (a[0x70] == 0xFF) {
            func_80042310();
            func_80040B48(0x42);
            D_800BF9B5 = 2;
            return 1;
        }
        break;
    }
    return 0;
}

extern u8 D_80149564[];
s32 func_801230A4(u8 *p) {
    switch (p[6]) {
    case 0:
        if (p[0x2B] == 3) {
            p[6] = 1;
            func_80042354(1, 1);
        }
        break;
    case 1:
        p[6] = 2;
        func_80040CDC(p, D_8014E4EC, D_80149564);
        p[0x70] = 1;
        break;
    case 2:
        func_80041098(p);
        if (p[0x70] == 0xFF) {
            func_80042310();
            return 1;
        }
        break;
    }
    return 0;
}

s32 func_80123180(s32 arg0) {
    M2C_FIELD(arg0, s32 *, 0x14) = f_SpawnGoldFishhookPickup(arg0, 1);
    return 1;
}

s32 func_801231B0(void) {
    func_8004D650(0x45, 1);
    func_8004ED0C(0x45, 4);
    return 1;
}

extern u8 D_800BF8F6;
extern s32 D_800ECFCC;
extern u8 D_8014C02C[];
extern u8 D_1F800207_9c67;

s32 func_801231E0(u8 *a, s32 r) {
    switch (a[7]) {
    case 0:
        if (D_1F800207_9c67 < 0x19) {
            r = 0;
            break;
        }
        if (func_800519E0(a, 0x12, D_800ECFCC, D_8014C02C) != 0) {
            r = 1;
            break;
        }
        a[7]++;
        if (D_800BF8F6 == 0xFF) {
            func_80077C40(a, D_8014E4EC, 4);
        } else {
            func_80077C40(a, D_8014E4EC, 0xF);
        }
        r = 1;
        break;
    case 1:
        r = 1;
        if (D_1F800207_9c67 < 0x19) {
            func_8007ADDC(a, 1);
            r = 0;
            a[7]--;
        }
        break;
    }
    return r;
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_801232DC);

extern u8 D_80149854[];
s32 func_801233DC(u8 *a) {
    switch (a[6]) {
    case 0:
        a[6] = 1;
        func_80040CDC(a, D_8014E4EC, D_80149854);
        a[0x70] = 1;
        break;
    case 1:
        func_80041098(a);
        if (a[0x70] == 0xFF) {
            a[6]++;
            func_80042310();
        }
        break;
    case 2:
        a[6] = 0;
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_801234A4);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80123C94);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_AnimateSmallFishSuspendedMotion);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_AnimateReleasedSmallFishBounce);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_801241BC);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_AnimateNetBridgeFishIdle);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_801244E8);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateNetBridgeFishAfterCollapse);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_AnimateNetBridgeFishDropSequence);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80124C6C);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_HandleSmallFishActor);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_SpawnSmallFishActor);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_801253E8);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_801255CC);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_DeliverCarriedChickToNest);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80125C4C);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80125E0C);

extern u8 D_800BF9F2;
void func_80125E0C();
s32 f_EnsureCarriedChickActor(u8 *a) {
    s32 n;
    u8 *p;

    if (a[3] == 0) {
        n = D_800BF9F2 & 0xF;
    } else {
        n = D_800BF9F2 >> 4;
    }
    if (n == 0) {
        p = func_80072DDC(a, 2, 2, 0x13);
        if (p != NULL) {
            M2C_FIELD(p, void **, 0x1C) = func_80125E0C;
            p[3] = a[3];
        }
    }
    return n;
}

void func_80125FE0(u8 *a) {
    s16 v = M2C_FIELD(M2C_FIELD(M2C_FIELD(a, u8 **, 0x10), u8 **, 0xC4), s16 *, 0x8);

    if (v > 0x800) {
        v |= 0xF000;
    }
    M2C_FIELD(a, s16 *, 0x54) = v >> 1;
    if (a[0x2B] != 0) {
        func_80125C4C(a);
    }
}

s32 f_UpdateCarriedChickCollision(u8 *a) {
    switch (a[7]) {
    case 0:
        if (M2C_FIELD(a, s16 *, 0x4A) >= 0) {
            a[0xBF] = 2;
            a[7]++;
        }
    case 1:
        M2C_FIELD(a, s16 *, 0x4A) += 0x200;
        if (M2C_FIELD(a, s16 *, 0x4A) > 0x2000) {
            M2C_FIELD(a, s16 *, 0x4A) = 0x2000;
        }
        if (a[0x29] != 0) {
            a[0xBF] = 0;
            return 1;
        }
        break;
    }
    return 0;
}

void func_801260CC(void *arg0) {
    if (func_80077768(M2C_FIELD(arg0, u8 *, 0x46) * 0x10, M2C_FIELD(arg0, s16 *, 0x56), 0) != 0) {
        M2C_FIELD(arg0, s16 *, 0x44) = -0x800;
        M2C_FIELD(arg0, s8 *, 0x5F) = 1;
    } else {
        M2C_FIELD(arg0, s16 *, 0x44) = 0x800;
        M2C_FIELD(arg0, s8 *, 0x5F) = 0;
    }
    M2C_FIELD(arg0, s16 *, 0x4A) = -0x1800;
    M2C_FIELD(arg0, s8 *, 0xBF) = 1;
    M2C_FIELD(arg0, s8 *, 0x2B) = 0;
}

void f_UpdateCarriedChickMotion(void *arg0) {
    s16 temp_v1;

    temp_v1 = M2C_FIELD(arg0, s16 *, 0x44);
    M2C_FIELD(arg0, s32 *, 0x2C) = (s32) (M2C_FIELD(arg0, s32 *, 0x2C) + (temp_v1 * M2C_FIELD(arg0, s16 *, 0x48)));
    M2C_FIELD(arg0, s32 *, 0x34) = (s32) (M2C_FIELD(arg0, s32 *, 0x34) + (temp_v1 * M2C_FIELD(arg0, s16 *, 0x4C)));
    if (M2C_FIELD(arg0, u8 *, 0xBF) == 0) {
        if (M2C_FIELD(arg0, u8 *, 0x29) != 0) {
            M2C_FIELD(arg0, s32 *, 0x30) = (s32) (M2C_FIELD(arg0, s32 *, 0x30) + (M2C_FIELD(arg0, s16 *, 0x44) * M2C_FIELD(arg0, s16 *, 0x4A)));
        } else {
            M2C_FIELD(arg0, u16 *, 0x32) = (u16) (M2C_FIELD(arg0, u16 *, 0x32) + 8);
        }
    } else {
        M2C_FIELD(arg0, u16 *, 0x32) = (u16) (M2C_FIELD(arg0, u16 *, 0x32) + ((s32) ((u16) M2C_FIELD(arg0, s16 *, 0x4A) << 0x10) >> 0x18));
    }
    M2C_FIELD(arg0, u16 *, 0x54) = (u16) ((M2C_FIELD(arg0, u16 *, 0x54) + ((s32) ((u16) M2C_FIELD(arg0, s16 *, 0x44) << 0x10) >> 0x14)) & 0xFFF);
}

void func_801261FC(u8 *a) {
    a[4] = 1;
    if (func_80077768(D_800E7ED6, M2C_FIELD(a, s16 *, 0x56), 0) != 0) {
        a[0x46] = (u32)(M2C_FIELD(a, s16 *, 0x56) + 0x800) >> 4;
    } else {
        a[0x46] = M2C_FIELD(a, u16 *, 0x56) >> 4;
    }
    func_80125C4C(a);
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80126264);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_InitializeNestChickActor);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_801266C8);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8012681C);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80126AA8);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_HandleFeedChicksInventoryUse);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_RestoreFedChicksFromProgress);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateNestChickQuestState);

void func_80126264();
s32 f_SpawnNestChickFromParent(u8 *a) {
    u8 *p = func_80072DDC(a, 0, 2, 0x14);

    if (p != NULL) {
        M2C_FIELD(p, void **, 0x1C) = func_80126264;
        p[3] = a[3];
        if (M2C_FIELD(a, u16 *, 0x7A) & 0x40) {
            M2C_FIELD(p, s16 *, 0x5C) = 0x343F;
            p[0x5E] = 4;
        } else {
            M2C_FIELD(p, s16 *, 0x5C) = 0x347F;
            p[0x5E] = 0;
        }
        M2C_FIELD(p, s16 *, 0x60) = (M2C_FIELD(a, u16 *, 0x7A) >> 4) & 3;
        return 1;
    }
    return 0;
}

void func_80127420(void *arg0) {
    if (M2C_FIELD(M2C_FIELD(arg0, void **, 0x10), u8 *, 0x5E) == 0) {
        M2C_FIELD(arg0, s16 *, 0x40) = 0x14;
        M2C_FIELD(arg0, s16 *, 0x4A) = 0x14;
        M2C_FIELD(arg0, s8 *, 5) = 1;
    }
}

void func_80127450(u8 *a) {
    switch (M2C_FIELD(a, s16 *, 0x64)) {
    case 1:
        if (M2C_FIELD(a, s16 *, 0x4A) >= 0) {
            M2C_FIELD(a, s16 *, 0x64)++;
        }
    case 2:
        M2C_FIELD(a, s16 *, 0x4A) += M2C_FIELD(a, s16 *, 0x50);
        if (M2C_FIELD(a, s16 *, 0x4A) > 0x2000) {
            M2C_FIELD(a, s16 *, 0x4A) = 0x2000;
        }
        break;
    }
}

extern u8 *D_1F800218;
typedef struct { u8 pad[0xC0]; u8 *parts[1]; } AreaPartsOwner;
s32 func_801274BC(u8 *a) {
    s16 d;

    d = M2C_FIELD(M2C_FIELD(a, AreaPartsOwner **, 0x10)->parts[M2C_FIELD(a, s16 *, 0x60)], s16 *, 0x2C) - M2C_FIELD(a, s16 *, 0x2E);
    if (d >= 0x259) {
        return 1;
    }
    if (d >= 0xFB) {
        return -1;
    }
    return 0;
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_DeliverChickItemToNest);

s32 f_FeedChicksAtNest(u8 *a) {
    u8 *e;
    u8 *g;

    e = func_80072DDC(a, 0, 2, 0x14);
    if (e != NULL) {
        func_8004D650(0x4D, 1);
        M2C_FIELD(e, void **, 0x1C) = func_80126264;
        e[3] = 4;
        g = (u8 *)&D_800BF870;
        M2C_FIELD(e, s16 *, 0x5C) = 0;
        if (g[0x82] == 1) {
            M2C_FIELD(e, s16 *, 0x68) = 0;
            g[0x82] |= 0x10;
            e[0x5E] = g[0x183] & 4;
        } else {
            M2C_FIELD(e, s16 *, 0x68) = 1;
            e[0x5E] = (g[0x183] >> 4) & 4;
        }
        func_8004ED94(e[0x5E] ? 0x4D : 0x4E, 0x41);
        M2C_FIELD(a, s32 *, 0x24) = 0x1E;
        return 1;
    }
    return 0;
}

void func_80126264();
s32 f_UseNishikiWingsAtNest(u8 *a) {
    u8 *p = func_80072DDC(a, 0, 2, 0x14);

    if (p != NULL) {
        func_8004D604(0x54, 1);
        M2C_FIELD(p, void **, 0x1C) = func_80126264;
        p[3] = 5;
        M2C_FIELD(p, s16 *, 0x5C) = 0;
        M2C_FIELD(a, s32 *, 0x24) = 0x1E;
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80127798);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80127D1C);

void func_80127D1C();
s32 func_801280E8(u8 *a) {
    u8 *g = (u8 *)&D_800BF870;
    u8 *e;

    if (g[0xC6] & 2) {
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
    M2C_FIELD(e, void **, 0x1C) = func_80127D1C;
    M2C_FIELD(e, s16 *, 0x2E) = M2C_FIELD(a, s16 *, 0x2E);
    M2C_FIELD(e, s16 *, 0x32) = M2C_FIELD(a, s16 *, 0x32);
    M2C_FIELD(e, s16 *, 0x36) = M2C_FIELD(a, s16 *, 0x36);
    e[0x2A] = a[0x2A];
    g[0x164] = 1;
    func_8003116C(0x30, e + 0x2C, -0xA);
    func_80074590(0x37, 0x20, 0);
    return 1;
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_801281B8);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_InitializeRareFishOrBucketController);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_801284AC);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateBlueBucketPendulumMotion);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_HandleRareFishOrBucketSuspension);

s32 func_801288D8(s32 arg0) {
    u8 temp_v1;
    void *temp_v0;

    temp_v1 = M2C_FIELD(arg0, u8 *, 5);
    switch (temp_v1) {                              /* irregular */
    case 0:
        temp_v0 = M2C_FIELD(arg0, void **, 0x10);
        if ((temp_v0 == NULL) || (M2C_FIELD(temp_v0, u8 *, 0x5E) == 2)) {
            M2C_FIELD(arg0, s8 *, 0xB) = 0;
            M2C_FIELD(arg0, void **, 0x10) = NULL;
            M2C_FIELD(arg0, u8 *, 5) = (u8) (M2C_FIELD(arg0, u8 *, 5) + 1);
        }
        /* fallthrough */
    case 1:
        return func_801281B8(arg0);
    default:
        return 1;
    }
}

extern s8 D_1F800207[];
s32 func_8012894C(s32 arg0) {
    s32 var_v0;
    u8 temp_v1;
    void *temp_v0;

    temp_v1 = M2C_FIELD(arg0, u8 *, 5);
    switch (temp_v1) {                              /* irregular */
    case 0:
        temp_v0 = M2C_FIELD(arg0, void **, 0x10);
        if ((temp_v0 == NULL) || (M2C_FIELD(temp_v0, u8 *, 0x5E) == 2)) {
            M2C_FIELD(arg0, s8 *, 0xB) = 0;
            M2C_FIELD(arg0, void **, 0x10) = NULL;
            M2C_FIELD(arg0, u8 *, 5) = (u8) (M2C_FIELD(arg0, u8 *, 5) + 1);
        }
        var_v0 = (u8) *((u8 *)D_1F800207) < 6U;
        if (var_v0 != 0) {
            func_801281B8(arg0);
            return f_UpdateBlueBucketPendulumMotion(arg0);
        }
        return var_v0;
    case 1:
        var_v0 = func_801281B8(arg0);
        /* Duplicate return node #9. Try simplifying control flow for better match */
        return var_v0;
    default:
        return 1;
    }
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_RunA00Event4ItemUseCutscene);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_RunNetBridgeCogInstallationCutscene);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_HandleGoldFishhookRecovery);

extern u8 D_8001B860[];
extern u8 *D_80149E50[];
extern u8 *D_80149E70;
extern u8 D_800BF830;
extern u8 D_800BFAD8;
void func_80129008(u8 *a) {
    switch (a[6]) {
    case 0:
        func_80040CDC(a, D_8001B860, D_80149E50[D_800BF830]);
        a[0x70] = 2;
        a[6]++;
        break;
    case 1:
        if (a[0x70] == 0xFF) {
            if (D_800BFAD8 != 0) {
                func_80040CDC(a, D_8001B860, D_80149E70);
                a[0x70] = 2;
                a[0xBF] = 0xD;
                a[6] = 1;
            } else {
                func_80070798();
            }
        }
        break;
    }
    func_80041098(a);
    func_80070E60(a);
    func_8004190C(a);
}

s32 func_80129100(u8 *a) {
    if (((M2C_FIELD(a, u16 *, 0x72) - M2C_FIELD(a, u16 *, 0x58)) & 0xFFF) < 0x800) {
        M2C_FIELD(a, s16 *, 0x58) += 0x3C;
    } else {
        M2C_FIELD(a, s16 *, 0x58) -= 0x3C;
    }
    if (((M2C_FIELD(a, s16 *, 0x72) - M2C_FIELD(a, s16 *, 0x58)) & 0xFFF) < 0x3C) {
        M2C_FIELD(a, s16 *, 0x58) = M2C_FIELD(a, s16 *, 0x72);
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateKainenHouseRotatingEffect);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateWindmillInteriorEffect);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_801295B4);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_801296E0);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_InitializeTableDrivenInteriorEffect);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_InitializeLinkedWindmillInteriorEffect);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_HandleInteriorEffectActor);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateCurvedSupportGeometry);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8012A0B8);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8012A2D8);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8012A43C);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8012A54C);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_SpawnWindmillCollapseDebrisPieces);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_AdvanceWindmillCollapseEffectPoint);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_AnimateWindmillCollapseOpening);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_AnimateWindmillCollapseMainSequence);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_AnimateWindmillCollapseFinale);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateA00InteriorTransitionActor);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_HandleA00InteriorSceneEffectActor);

u8 *func_8012CE30(u8 *a, s32 b, s32 i) {
    u8 *p = func_8003116C(D_8014A240[i], b, -0x64);

    if (p != NULL) {
        M2C_FIELD(p, u8 **, 0x10) = a;
        p[0x28] |= 0x80;
        return p;
    }
    return NULL;
}

s16 f_GetWindmillControllerBearing(u8 *a) {
    u8 *t = D_1F800218;
    s16 dx = M2C_FIELD(t, s16 *, 0x2E) - M2C_FIELD(a, s16 *, 0x2);
    s16 dz = M2C_FIELD(t, s16 *, 0x36) - M2C_FIELD(a, s16 *, 0xA);

    return func_80085690(-dz, dx);
}

void func_8012CEE0(u8 *a) {
    if (a[0x5F] == 0) {
        func_80074590(6, 4, 0x1E);
        a[0x5F] = D_8014A258[(M2C_FIELD(M2C_FIELD(a, u8 **, 0xC0), u16 *, 0x16) >> 6) & 7];
    } else {
        a[0x5F]--;
    }
}

void f_UpdateKainenHouseWobbleWide(void *arg0) {
    u8 temp_v1;

    if (M2C_FIELD(arg0, s16 *, 0x50) != 0) {
        temp_v1 = M2C_FIELD(arg0, u8 *, 6);
        switch (temp_v1) {                          /* irregular */
        case 0:
            M2C_FIELD(arg0, u8 *, 6) = 1U;
            M2C_FIELD(arg0, s16 *, 0x4A) = 0;
            M2C_FIELD(arg0, u16 *, 0x5A) = (u16) (M2C_FIELD(arg0, u16 *, 0x56) + 0x700);
            /* fallthrough */
        case 1:
            M2C_FIELD(arg0, u16 *, 0x56) = (u16) (M2C_FIELD(arg0, u16 *, 0x5A) + ((s32) (func_80083F50(M2C_FIELD(arg0, s16 *, 0x4A)) << 9) >> 0xC));
            M2C_FIELD(arg0, s16 *, 0x4A) = (s16) (((u16) M2C_FIELD(arg0, s16 *, 0x4A) + (u16) M2C_FIELD(arg0, s16 *, 0x50)) & 0xFFF);
            break;
        case 2:
            M2C_FIELD(arg0, u16 *, 0x56) = (u16) (M2C_FIELD(arg0, u16 *, 0x5A) + ((s32) (func_80083F50(M2C_FIELD(arg0, s16 *, 0x4A)) << 8) >> 0xC));
            M2C_FIELD(arg0, s16 *, 0x4A) = (s16) (((u16) M2C_FIELD(arg0, s16 *, 0x4A) + (M2C_FIELD(arg0, s16 *, 0x50) * 2)) & 0xFFF);
            break;
        }
        if (M2C_FIELD(arg0, s16 *, 0x4A) == 0) {
            M2C_FIELD(arg0, u8 *, 6) = (u8) ((func_8009A450() & 1) + 1);
        }
    }
}

void f_UpdateKainenHouseWobbleNarrow(void *arg0) {
    u8 temp_v1;

    if (M2C_FIELD(arg0, s16 *, 0x50) != 0) {
        temp_v1 = M2C_FIELD(arg0, u8 *, 6);
        switch (temp_v1) {                          /* irregular */
        case 0:
            M2C_FIELD(arg0, u8 *, 6) = 1U;
            M2C_FIELD(arg0, s16 *, 0x4A) = 0;
            M2C_FIELD(arg0, u16 *, 0x5A) = (u16) (M2C_FIELD(arg0, u16 *, 0x56) + 0x300);
            /* fallthrough */
        case 1:
            M2C_FIELD(arg0, u16 *, 0x56) = (u16) (M2C_FIELD(arg0, u16 *, 0x5A) + ((s32) (func_80083F50(M2C_FIELD(arg0, s16 *, 0x4A)) << 8) >> 0xC));
            M2C_FIELD(arg0, s16 *, 0x4A) = (s16) (((u16) M2C_FIELD(arg0, s16 *, 0x4A) + (u16) M2C_FIELD(arg0, s16 *, 0x50)) & 0xFFF);
            break;
        case 2:
            M2C_FIELD(arg0, u16 *, 0x56) = (u16) (M2C_FIELD(arg0, u16 *, 0x5A) + ((s32) (func_80083F50(M2C_FIELD(arg0, s16 *, 0x4A)) << 7) >> 0xC));
            M2C_FIELD(arg0, s16 *, 0x4A) = (s16) (((u16) M2C_FIELD(arg0, s16 *, 0x4A) + (M2C_FIELD(arg0, s16 *, 0x50) * 2)) & 0xFFF);
            break;
        }
        if (M2C_FIELD(arg0, s16 *, 0x4A) == 0) {
            M2C_FIELD(arg0, u8 *, 6) = (u8) ((func_8009A450() & 1) + 1);
        }
    }
}

void f_UpdateKainenHouseWobbleInverted(void *arg0) {
    u8 temp_v1;

    if (M2C_FIELD(arg0, s16 *, 0x50) != 0) {
        temp_v1 = M2C_FIELD(arg0, u8 *, 6);
        switch (temp_v1) {                          /* irregular */
        case 0:
            M2C_FIELD(arg0, u8 *, 6) = 1U;
            M2C_FIELD(arg0, s16 *, 0x4A) = 0;
            M2C_FIELD(arg0, u16 *, 0x5A) = (u16) (M2C_FIELD(arg0, u16 *, 0x56) - 0x300);
            /* fallthrough */
        case 1:
            M2C_FIELD(arg0, u16 *, 0x56) = (u16) (M2C_FIELD(arg0, u16 *, 0x5A) - ((s32) (func_80083F50(M2C_FIELD(arg0, s16 *, 0x4A)) << 8) >> 0xC));
            M2C_FIELD(arg0, s16 *, 0x4A) = (s16) (((u16) M2C_FIELD(arg0, s16 *, 0x4A) + (u16) M2C_FIELD(arg0, s16 *, 0x50)) & 0xFFF);
            break;
        case 2:
            M2C_FIELD(arg0, u16 *, 0x56) = (u16) (M2C_FIELD(arg0, u16 *, 0x5A) - ((s32) (func_80083F50(M2C_FIELD(arg0, s16 *, 0x4A)) << 7) >> 0xC));
            M2C_FIELD(arg0, s16 *, 0x4A) = (s16) (((u16) M2C_FIELD(arg0, s16 *, 0x4A) + (M2C_FIELD(arg0, s16 *, 0x50) * 2)) & 0xFFF);
            break;
        }
        if (M2C_FIELD(arg0, s16 *, 0x4A) == 0) {
            M2C_FIELD(arg0, u8 *, 6) = (u8) ((func_8009A450() & 1) + 1);
        }
    }
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateKainenHouseWobbleEffect);

extern s16 D_8014A260[];
extern s16 D_8014A268[];
void func_8012D404(u8 *a) {
    switch (a[4]) {
    case 0:
        if (func_80051B70(a, 0xC, D_8014A260[a[3]]) == 0) {
            a[4]++;
            M2C_FIELD(a, s16 *, 0x54) = D_8014A268[a[3]];
        }
        break;
    case 1:
        if (func_8007778C(a) != 0) {
            f_UpdateKainenHouseWobbleEffect(a);
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

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_HandleGoldFishhookScenePropActor);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8012D908);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_HandleTownQuestRewardVisualActor);

extern u8 D_800BF9DD;
void func_8012DE34(u8 *a) {
    u8 *g = D_800E7E80;

    switch (a[5]) {
    case 0:
        if (D_800BF9DD == 9) {
            a[5] = 1;
            M2C_FIELD(a, s32 *, 0x3C) = D_800ECF80;
            func_80077B38(a, D_8014C808, 0xF);
            M2C_FIELD(a, s16 *, 0x60) = 0x40;
            M2C_FIELD(a, s16 *, 0x62) = 0;
            M2C_FIELD(a, s16 *, 0x64) = -0x20;
        }
        break;
    case 1:
        func_8004BD64(a, 2, M2C_FIELD(g, s32 *, 0xDC), M2C_FIELD(g, s32 *, 0xD0), a + 0x60);
        a[1] = 1;
        if (D_800BF9DD == 0xB) {
            a[4] = 3;
        }
        break;
    }
}

u8 *func_8012DF08(s32 a) {
    u8 *p = func_80072DDC(a, 128, 3, 16);

    if (p == NULL) {
        return NULL;
    }
    p[0x3] = 2;
    M2C_FIELD(p, void **, 0x1C) = f_HandleTownQuestRewardVisualActor;
    return p;
}

void func_8012DF50(u8 *a) {
    u8 *p = M2C_FIELD(a, u8 **, 0x10);

    switch (a[5]) {
    case 0:
        a[5]++;
        M2C_FIELD(a, s32 *, 0x3C) = D_800ECF80;
        func_80077B38(a, D_8014C808, 2);
        M2C_FIELD(a, s16 *, 0x60) = 0x20;
        M2C_FIELD(a, s16 *, 0x62) = 0x10;
        M2C_FIELD(a, s16 *, 0x64) = 0;
    case 1:
        func_8004BD64(a, 1, M2C_FIELD(p, void **, 0xDC), 0, a + 0x60);
        a[1] = p[1];
        break;
    }
}

void func_8012DFF8(void *arg0) {
    func_8004D4C4(0x1D, 1);
    func_8004B0D8(arg0);
    M2C_FIELD(arg0, s8 *, 4) = 3;
}

void func_8012E034(void *arg0)
{
  int new_var;
  *((s8 *) (((signed char *) arg0) + 0xB)) = 0x10;
  *((s8 *) (((signed char *) arg0) + 0xD)) = 0;
  *((s16 *) (((signed char *) arg0) + 0x5C)) = 0;
  *((s16 *) (((signed char *) arg0) + 0x5A)) = 0;
  *((s8 *) (((signed char *) arg0) + 0x47)) = 0;
  *((s16 *) (((signed char *) arg0) + 0x60)) = 0;
  new_var = 0xF0;
  *((s8 *) (((signed char *) arg0) + 8)) = new_var;
}

void f_InitializeTownQuestRewardVisualModel(u8 *a) {
    if (func_80051B70(a, 0xC, 0x4F) == 0) {
        switch (a[3]) {
        case 3:
            M2C_FIELD(M2C_FIELD(a, u8 **, 0xC0), s16 *, 0x8) = 0xB6;
            break;
        case 4:
            M2C_FIELD(M2C_FIELD(a, u8 **, 0xC0), s16 *, 0x8) = -0xB6;
            break;
        }
        func_800517F8(a);
    }
}

void func_8012E0D0(void *a)
{
    if (func_80051B70(a, 0xC, 7) == 0) {
        func_800517F8(a);
    }
}

void func_8012E10C(u8 *a) {
    u8 *p = M2C_FIELD(a, u8 **, 0x10);

    switch (a[5]) {
    case 0:
        a[5]++;
        M2C_FIELD(a, s32 *, 0x3C) = D_800ECF80;
        func_80077B38(a, D_8014C808, 0x11);
        M2C_FIELD(a, s16 *, 0x60) = -0xC8;
        M2C_FIELD(a, s16 *, 0x62) = 0x20;
        M2C_FIELD(a, s16 *, 0x64) = 0;
    case 1:
        func_8004BD64(a, 2, 0, M2C_FIELD(p, s32 *, 0xD0), a + 0x60);
        a[1] = p[1];
        if (D_800BF9B5 == 5) {
            func_8004D4C4(0xE, 1);
            func_8004B0D8(a);
            a[4] = 3;
        }
        break;
    }
}

void func_8012E1E4(u8 *a) {
    u8 *p = M2C_FIELD(a, u8 **, 0x10);

    switch (a[5]) {
    case 0:
        a[5]++;
        M2C_FIELD(a, s32 *, 0x3C) = D_800ECF80;
        func_80077B38(a, D_8014C808, 0xE);
        M2C_FIELD(a, s16 *, 0x60) = -0xC8;
        M2C_FIELD(a, s16 *, 0x62) = 0x30;
        M2C_FIELD(a, s16 *, 0x64) = 0;
    case 1:
        func_8004BD64(a, 2, 0, M2C_FIELD(p, s32 *, 0xD0), a + 0x60);
        a[1] = p[1];
        if (D_800BF9B5 == 6) {
            func_8004D4C4(0x23, 1);
            func_8004B0D8(a);
            a[4] = 3;
        }
        break;
    }
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8012E2BC);

void func_8012E478(u8 *a) {
    switch (a[4]) {
    case 0:
        switch (a[0x5E]) {
        case 0:
            func_8012E2BC(a);
            break;
        case 1:
        case 2:
            func_8012E678(a);
            break;
        }
        break;
    case 1:
        func_8007778C(a);
        func_8012E70C(a);
        break;
    case 2:
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

void func_8012E478();
u8 *func_8012E53C(u8 *a, s32 b, s16 *c) {
    u8 *p = func_80072DDC(a, 0, 3, 0x11);

    if (p != NULL) {
        M2C_FIELD(p, void **, 0x1C) = func_8012E478;
        p[3] = 0;
        p[0x5E] = 0;
        M2C_FIELD(p, s16 *, 0x40) = ((s16)b >> 4) + 2;
        M2C_FIELD(p, s16 *, 0x2E) = c[0];
        M2C_FIELD(p, s16 *, 0x32) = c[1];
        M2C_FIELD(p, s16 *, 0x36) = c[2];
    }
    return p;
}

u8 *func_8012E5CC(u8 *a, s16 *b, s16 *c) {
    u8 *p = func_80072DDC(a, 0, 3, 0x11);
    s32 r;

    if (p != NULL) {
        M2C_FIELD(p, void **, 0x1C) = func_8012E478;
        r = func_8009A450() & 0xF0;
        p[0x5E] = 1;
        M2C_FIELD(p, s16 *, 0x2E) = b[0];
        M2C_FIELD(p, s16 *, 0x32) = b[1] - r;
        M2C_FIELD(p, s16 *, 0x36) = b[2] + r;
        M2C_FIELD(p, s16 *, 0x48) = c[0];
        M2C_FIELD(p, s16 *, 0x4C) = c[2];
    }
    return p;
}

void func_8012E678(u8 *a) {
    s32 r = func_8009A450() & 3;
    a[0x3] = r;

    a[0xB] = 0x12;
    a[0x8] = 0xC4;
    M2C_FIELD(a, s16 *, 0x40) = 0x5A;
    a[0xD] = 0;
    M2C_FIELD(a, s16 *, 0x5C) = 0;
    M2C_FIELD(a, s16 *, 0x5A) = 0;
    M2C_FIELD(a, s16 *, 0x60) = 1;
    a[0x4]++;
    func_8012E7EC(a);
    M2C_FIELD(a, s32 *, 0x3C) = D_800ECF80;
    func_80077B38(a, D_8014C808, r + 0x12);
}

void func_8012E70C(u8 *a) {
    s16 s;
    s16 c;
    s32 m;
    s32 d;
    s16 e;

    c = --M2C_FIELD(a, s16 *, 0x40);
    if (a[1] == 0 || c <= 0) {
        if (a[0x5E] == 2) {
            M2C_FIELD(a, u8 **, 0x10)[0x5E] = 0;
        }
        a[4] = 3;
        return;
    }
    s = M2C_FIELD(a, s16 *, 0x44);
    m = s * M2C_FIELD(a, s16 *, 0x48);
    e = M2C_FIELD(a, s16 *, 0x4E);
    d = M2C_FIELD(a, s16 *, 0x4A) >> 8;
    M2C_FIELD(a, s16 *, 0x32) += d;
    M2C_FIELD(a, s16 *, 0x54) += e;
    M2C_FIELD(a, s32 *, 0x2C) += m;
    M2C_FIELD(a, s32 *, 0x34) += s * M2C_FIELD(a, s16 *, 0x4C);
    if ((s16)func_8012E87C(a)) {
        func_8012E7EC(a);
    }
}

void func_8012E7EC(u8 *a) {
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
    M2C_FIELD(a, s16 *, 0x4A) = (r & 0x700) + 0x1000;
    M2C_FIELD(a, s16 *, 0x50) = (r & 0x30) - 0x100;
    M2C_FIELD(a, s16 *, 0x60) = -0x400 - (r & 0x70);
    M2C_FIELD(a, s16 *, 0x44) += r & 0x300;
}

s32 func_8012E87C(void *arg0) {
    u16 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u16 *, 0x4A) + M2C_FIELD(arg0, u16 *, 0x50);
    M2C_FIELD(arg0, u16 *, 0x4A) = temp_v1;
    return M2C_FIELD(arg0, s16 *, 0x60) >= (s16) temp_v1;
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateTownBarrelChildTransforms);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_HandleTownBarrelSeesawController);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_InitializeTownBarrelSeesawController);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8012F494);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateBarrelSeesawRide);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_RotateSelectedTownBarrel);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80130524);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80130788);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_HandleBarrelSeesawContact);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80130AC4);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateBarrelLinkedSegmentSequence);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_TriggerBarrelLinkedSegments);

typedef struct {
    u8 flags;
    u8 pad;
    s16 id;
} PickupLink;
extern PickupLink D_801485BC[];
void f_HideCollectedBarrelLinkedPickups(AreaPartsOwner *a) {
    PickupLink *t = D_801485BC;
    s16 i = 2;
    s16 k = (s8)a->pad[0x63] & 0x7F;
    PickupLink *e;
    u8 r;

loop:
    e = &t[k];
    if ((e++)[1].flags & 0x80) {
        r = func_8004D868(e->id, 1);
    } else {
        r = func_8004D7EC(e->id, 1);
    }
    if (r != 0) {
        a->parts[i][0x3E] |= 0x10;
    }
    if (i == 2 && (M2C_FIELD(a, u16 *, 0x60) & 2)) {
        i++;
        k++;
        if (i < 4) {
            goto loop;
        }
    }
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_BeginScriptedBarrelRotation);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateBarrelSeesawSupportHeight);

void f_ApplyBarrelSeesawContactImpulse(u8 *a) {
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

extern u8 D_800BF9D2;
void f_RestoreTownBarrelOrientations(void *arg0) {
    s16 temp_v0;

    if ((M2C_FIELD(arg0, u16 *, 0x60) & 4) && ((M2C_FIELD(arg0, s16 *, 0x62) & 0xFF00) != 0xFF00)) {
        temp_v0 = 1 << ((u32) ((u16) M2C_FIELD(arg0, s16 *, 0x62) & 0x7F00) >> 8);
        if (D_800BF9D2 & temp_v0) {
            M2C_FIELD(M2C_FIELD(arg0, void **, 0xC8), s16 *, 0xC) = 0x800;
        } else {
            M2C_FIELD(M2C_FIELD(arg0, void **, 0xC8), s16 *, 0xC) = 0;
        }
        if ((M2C_FIELD(arg0, u16 *, 0x60) & 2) && !(M2C_FIELD(arg0, s16 *, 0x62) & 0x8000)) {
            if (D_800BF9D2 & (s16) (temp_v0 * 2)) {
                M2C_FIELD(M2C_FIELD(arg0, void **, 0xCC), s16 *, 0xC) = 0x800;
                return;
            }
            M2C_FIELD(M2C_FIELD(arg0, void **, 0xCC), s16 *, 0xC) = 0;
        }
    }
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_801316CC);

void f_ActivateBarrelLinkedSegmentPair(AreaPartsOwner *a, s16 k0, s16 flag) {
    s16 k = k0;
    s16 t = (flag != 0) << 11;
    s16 ang;

    if ((a->pad[0x5E] & 2) && M2C_FIELD(a, s16 *, 0x6C) == k) {
        ang = M2C_FIELD(a, u16 *, 0x6E) & 0xFFF;
    } else {
        ang = M2C_FIELD(a->parts[k], u16 *, 0xC);
    }
    if (ang == t) {
        k = k * 4 - 2;
    } else {
        k = k * 4 - 4;
    }
    if (!(M2C_FIELD(a, u16 *, 0x60) & 2)) {
        k--;
    }
    a->parts[k][0x3E] = 1;
    a->parts[k + 1][0x3E] = 1;
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80131840);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80131D08);

s32 f_SettleDryingRackGrabHandleRotation(AreaPartsOwner *a) {
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

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateDryingRackGrabHandle);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80132400);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80132548);

extern s8 D_1F800160[];
extern u8 D_800BF89C;
extern u8 D_800E7EAA;
void func_8013259C(void *arg0) {
    u8 temp_a0;
    u8 temp_v1;
    u8 temp_v1_2;

    temp_a0 = M2C_FIELD(arg0, u8 *, 4);
    switch (temp_a0) {                              /* switch 1; irregular */
    case 0:                                         /* switch 1 */
        func_8013272C(arg0);
        return;
    case 1:                                         /* switch 1 */
        temp_v1 = M2C_FIELD(arg0, u8 *, 3);
        if ((temp_v1 == temp_a0) || (temp_v1 == 5)) {
            if ((D_800BF89C == 2) || (D_800E7EAA != temp_a0)) {
                goto block_13;
            }
        } else {
block_13:
            if (*((s16 *)D_1F800160) < 0x4651) {
                func_8007778C(arg0);
            }
        }
        temp_v1_2 = M2C_FIELD(arg0, u8 *, 5);
        switch (temp_v1_2) {                        /* switch 2; irregular */
        case 0:                                     /* switch 2 */
            func_80132954(arg0);
            break;
        case 2:                                     /* switch 2 */
            func_80132D58(arg0);
            break;
        case 3:                                     /* switch 2 */
            f_UpdateAquaticPlantGrabMotion(arg0);
            break;
        case 4:                                     /* switch 2 */
            func_80133500(arg0);
            break;
        }
        f_UpdateAquaticPlantRotationKick(arg0);
        f_UpdateAquaticPlantHitWobble(arg0);
        M2C_FIELD(arg0, s8 *, 0x29) = 0;
        if (M2C_FIELD(arg0, u8 *, 1) != 0) {
            func_800518FC(arg0);
            return;
        }
        return;
    case 2:                                         /* switch 1 */
        func_80133184(arg0);
        return;
    case 3:                                         /* switch 1 */
        func_8007A624(arg0);
        break;
    }
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8013272C);

// nearcopy: 8 words off, C from a04 func_8011C974
#include "common.h"
#include "game.h"
#include "m2c.h"
extern s8 D_1F80017C[];
typedef struct { s16 x, y, z; } AreaVec3s;
extern AreaVec3s D_8014A684[];
void func_80132954(u8 *a) {
    s16 i;

    switch (a[6]) {
    case 0:
        if (--M2C_FIELD(a, s16 *, 0x40) <= 0) {
            a[6]++;
        }
        break;
    case 1:
        if (!(*(u16 *)D_1F80017C & 0xF)) {
            M2C_FIELD(a, s16 *, 0xB8) = D_8014A684[M2C_FIELD(a, s16 *, 0x7A)].x;
            M2C_FIELD(a, s16 *, 0xBA) = D_8014A684[M2C_FIELD(a, s16 *, 0x7A)].y;
            M2C_FIELD(a, s16 *, 0xBC) = D_8014A684[M2C_FIELD(a, s16 *, 0x7A)].z;
            M2C_FIELD(a, s16 *, 0x7A) = (M2C_FIELD(a, s16 *, 0x7A) + 1) & 7;
        }
        break;
    }
    if ((s16)f_SyncAquaticPlantLinkedState(a) == 0 && (s16)f_ClassifyAquaticPlantContact(a) == 1) {
        f_ConfigureAquaticPlantMotion(a, 0);
        a[5] = 3;
        a[6] = 0;
        M2C_FIELD(a, s16 *, 0x6C) = 0;
    }
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateAquaticPlantHitWobble);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80132D58);

// nearcopy: 9 words off, C from a04 func_8011CCE8
#include "common.h"
#include "game.h"
#include "m2c.h"
#include "gte.h"
extern u8 D_800E7E80[];
void f_UpdateAquaticPlantGrabMotion(u8 *a)
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
            if (M2C_FIELD(a, s16 *, 0x68) == 1 || M2C_FIELD(a, s16 *, 0x6C) != 0) {
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
            f_ConfigureAquaticPlantMotion(a, a[0x5E]);
            a[6] = 1;
            M2C_FIELD(a, s16 *, 0x6C) = 1;
        }
    } else if ((s16)f_ClassifyAquaticPlantContact(a)) {
        M2C_FIELD(*(u8 **)(a + 0xC0), u16 *, 0x38) = M2C_FIELD(a, s16 *, 0x64);
        M2C_FIELD(*(u8 **)(a + 0xC0), u16 *, 0x3A) = M2C_FIELD(a, s16 *, 0x66);
        f_ConfigureAquaticPlantMotion(a, 0);
        a[6] = 0;
        M2C_FIELD(a, s16 *, 0x6C) = 0;
    }
    if (M2C_FIELD(a, s16 *, 0x50) > 0x20) {
        M2C_FIELD(a, s16 *, 0x50)--;
    }
    f_UpdateAquaticPlantCollisionBounds(a);
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80133184);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_SyncAquaticPlantLinkedState);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_SpawnAquaticPlantActors);

void func_80133500(u8 *a)
{
    if (a[0x29] == 0) {
        f_ConfigureAquaticPlantMotion(a, 1);
        a[5] = 3;
        a[6] = 1;
        *(s16 *)(a + 0x6C) = 1;
    }
}

#define P0(a) M2C_FIELD(a, u8 **, 0xC0)
typedef union {
    u8 b[0xC0];
    s16 h[0x60];
} ActorH;
#define H(o) h[(o) / 2]
void f_UpdateAquaticPlantRotationKick(u8 *a) {
    switch (F16(a, 0x78)) {
    case 1:
        F16(P0(a), 0xC) = FU16(P0(a), 0xC) + FU16(P0(a), 0x14);
        F16(P0(a), 0x14) -= 8;
        if (F16(P0(a), 0x14) < -0x20) {
            F16(a, 0x78) = 0;
            F16(P0(a), 0xC) = 0;
        }
        break;
    case 2:
        F16(P0(a), 0xC) = FU16(P0(a), 0xC) - FU16(P0(a), 0x14);
        F16(P0(a), 0x14) -= 8;
        if (F16(P0(a), 0x14) < -0x20) {
            F16(a, 0x78) = 0;
            F16(P0(a), 0xC) = 0;
        }
        break;
    }
    if (a[0x2B] != 0) {
        F16(a, 0x78) = 0;
        F16(P0(a), 0xC) = 0;
    }
}

void f_ConfigureAquaticPlantMotion(ActorH *a, s16 k) {
    a->H(0x50) = a->H(0x4E) = a->H(0x62) * 32 + 0x30;
    switch (k) {
    case 0:
        a->H(0x4A) = 0x10;
        a->H(0x74) = a->H(0x66) - (a->H(0x66) >> 4);
        a->H(0x40) = a->H(0x66) >> 5;
        break;
    case 1:
        a->H(0x4A) = 0x20;
        a->H(0x74) = a->H(0x66);
        a->H(0x40) = a->H(0x66) >> 5;
        a->H(0x40) += a->H(0x66) >> 6;
        break;
    case 2:
        a->H(0x4A) = 0x40;
        a->H(0x74) = a->H(0x66);
        a->H(0x40) = a->H(0x66) >> 3;
        a->H(0x4E) += 0x70;
        a->H(0x50) += 0x70;
        break;
    }
}

s32 f_ClassifyAquaticPlantContact(u8 *a) {
    if (a[0x29] != 0) {
        if (M2C_FIELD(a, s16 *, 0x78) == 0) {
            if (M2C_FIELD(a, s16 *, 0x44) > 0) {
                M2C_FIELD(a, s16 *, 0x78) = 1;
                M2C_FIELD(M2C_FIELD(a, u8 **, 0xC0), s16 *, 0x14) = 0x20;
            } else if (M2C_FIELD(a, s16 *, 0x44) < 0) {
                M2C_FIELD(a, s16 *, 0x78) = 2;
                M2C_FIELD(M2C_FIELD(a, u8 **, 0xC0), s16 *, 0x14) = 0x20;
            }
        }
        if (M2C_FIELD(a, s16 *, 0x68) == 0) {
            return 1;
        }
        return 2;
    }
    return 0;
}

void f_UpdateAquaticPlantCollisionBounds(u8 *a) {
    s32 k1, k2, t;

    if (a[3] == 5) {
        k1 = 0x76;
        k2 = 0xF5;
    } else {
        k1 = 0x80;
        k2 = 0x113;
    }
    t = (k1 * M2C_FIELD(M2C_FIELD(a, u8 **, 0xC0), u16 *, 0x38)) >> 12;
    M2C_FIELD(a, s16 *, 0x80) = t;
    M2C_FIELD(a, s16 *, 0x82) = t << 1;
    t = (k2 * M2C_FIELD(M2C_FIELD(a, u8 **, 0xC0), u16 *, 0x3A)) >> 12;
    M2C_FIELD(a, s16 *, 0x84) = t;
    M2C_FIELD(a, s16 *, 0x86) = t << 1;
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateSingleSegmentSwingMotion);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_HandleSingleSegmentSwingActor);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80133D6C);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_DrawNetBridgeStrip);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_DrawNetBridgeSupportStrips);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_AnimateNetBridgeCollapse);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateCollapsedNetBridgeMotion);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_ResolveTombaOnNetBridge);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80134C5C);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_ResolveActorOnNetBridge);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80134FD8);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateRopeSwingInteraction);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80135D64);

u8 *func_801360F4(s32 a, u8 b) {
    u8 *p = func_8007A980(2, 4, 0);

    if (p == NULL) {
        return NULL;
    }
    M2C_FIELD(p, void **, 0x1C) = func_80135D64;
    M2C_FIELD(p, s32 *, 0x10) = a;
    p[0x2] = 7;
    p[0x3] = b;
    return p;
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_HandleA00PendulumPlatformActor);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_801365C4);

#define FP(p, o) M2C_FIELD(p, u8 **, o)
extern u8 D_1F8000D0_b839[];
extern u8 D_1F800000[];

void func_80136748(u8 *a) {
    u8 *c;
    u8 *s;
    func_8003CCA4();
    D_1F8000C0[0] = FU16(FP(a, 0xC8), 0x2C);
    D_1F8000C0[1] = FU16(FP(a, 0xC8), 0x30);
    D_1F8000C0[2] = FU16(FP(a, 0xC8), 0x34) + 0x2E;
    func_80084470(D_1F8000D0_b839 + 0x28, D_1F8000C0, D_1F800000 + 0x14);
    s = D_1F800000;
    c = D_1F8000D0_b839;
    M2C_FIELD(s, s32 *, 0x14) += M2C_FIELD(c, s32 *, 0x3C);
    M2C_FIELD(s, s32 *, 0x18) += M2C_FIELD(c, s32 *, 0x40);
    M2C_FIELD(s, s32 *, 0x1C) += M2C_FIELD(c, s32 *, 0x44);
    func_80084660(D_1F8000D0_b839 + 0x28);
    func_80084690(D_1F800000);
    func_801365C4(a, F16(a, 0xBA));
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8013681C);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80136954);

extern u8 D_800BF809;
extern u8 D_800BF89C;
extern u8 D_800E7EAA;
void func_80136D9C(void *arg0) {
    u8 temp_v1;
    u8 temp_v1_2;

    temp_v1 = M2C_FIELD(arg0, u8 *, 4);
    switch (temp_v1) {                              /* switch 1; irregular */
    case 0:                                         /* switch 1 */
        func_80136F08(arg0);
        return;
    case 1:                                         /* switch 1 */
        if ((D_800BF89C == 2) || (M2C_FIELD(arg0, u8 *, 3) != 2) || (D_800E7EAA != temp_v1)) {
            func_8007778C(arg0);
        }
        temp_v1_2 = M2C_FIELD(arg0, u8 *, 5);
        switch (temp_v1_2) {                        /* switch 2; irregular */
        case 0:                                     /* switch 2 */
            if (M2C_FIELD(arg0, u8 *, 3) != 3) {
                func_80138A64(arg0);
            } else {
                func_8018CDC4(arg0);
            }
            break;
        case 1:                                     /* switch 2 */
            if (D_800BF809 == 0) {
                f_UpdateSegmentedTownActorSequence(arg0);
            }
            break;
        case 2:                                     /* switch 2 */
            func_8018CA1C(arg0);
            break;
        }
        if (M2C_FIELD(arg0, u8 *, 1) != 0) {
            func_801389C8(arg0);
            return;
        }
    case 2:                                         /* switch 1 */
        return;
    case 3:                                         /* switch 1 */
        func_8007A624(arg0);
        break;
    }
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80136F08);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateSegmentedTownActorSequence);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_EmitSegmentedTownActorEffect);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_ConfigureSegmentedTownActorMorph);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_801386A0);

void func_80136D9C();
void f_SpawnSegmentedTownActor(u8 *a) {
    u8 *p = func_80072DDC(a, 3, 4, 0xA);

    if (p != NULL) {
        M2C_FIELD(p, void **, 0x1C) = func_80136D9C;
        M2C_FIELD(p, s16 *, 0x2E) = M2C_FIELD(a, s16 *, 0x2E);
        M2C_FIELD(p, s16 *, 0x32) = M2C_FIELD(a, s16 *, 0x32);
        M2C_FIELD(p, s16 *, 0x36) = M2C_FIELD(a, s16 *, 0x36);
        if (a[3] != 0) {
            p[3] = a[3];
        } else if (D_800BF89C == 2) {
            p[3] = 3;
        } else {
            p[3] = 0;
        }
    }
}

typedef struct {
    u8 b[0xC0];
    u8 *parts[1];
} PartsActor;
void func_801389C8(PartsActor *a0) {
    PartsActor *a = a0;
    s32 pad[4];
    s32 i;
    u8 *p;

    func_80051C8C(a);
    for (i = 0; i < a->b[8]; i++) {
        p = a->parts[i];
        func_800517BC(D_1F800000, M2C_FIELD(p, s16 *, 0x38), M2C_FIELD(p, s16 *, 0x3A), M2C_FIELD(p, s16 *, 0x3C));
        func_80084250(p + 0x18, D_1F800000);
    }
}

void func_80138A64(u8 *a) {
    u8 *p;

    if (M2C_FIELD(a, s16 *, 0x6A) != 0 && a[3] != 0) {
        if (--M2C_FIELD(a, s16 *, 0x40) < 0) {
            D_800BF821 = 0;
            M2C_FIELD(a, s16 *, 0x6A) = 0;
        }
    }
    p = M2C_FIELD(a, u8 **, 0x10);
    if (M2C_FIELD(a, s16 *, 0x6A) == 0 && M2C_FIELD(p, s16 *, 0x76) == 1) {
        if (a[3] != 0 && M2C_FIELD(p, s16 *, 0x78) == 0) {
            D_800BF821 = 1;
        }
        a[6] = 0;
        a[5]++;
    }
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_HandleA00Warp0813Entrance);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_HandleTinyMousesHouseEntrance);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_HandleFishermensTownEntranceActor);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_HandleCurvedSupportContactActor);

u8 *func_80139838(s32 a, u8 b) {
    u8 *p = func_8007A980(1, 4, 0);

    if (p == NULL) {
        return NULL;
    }
    M2C_FIELD(p, void **, 0x1C) = f_HandleCurvedSupportContactActor;
    M2C_FIELD(p, s32 *, 0x10) = a;
    p[0x2] = 13;
    p[0x3] = b;
    return p;
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_InitializeDryingRackControllerState);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80139A70);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_DeployDryingRackSegments);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_RetractDryingRackSegments);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8013A008);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_SpawnStarShapedCogPickup);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_HandleDryingRackController);

void f_HandleDryingRackController();
u8 *func_8013A730(s32 a) {
    u8 *p = func_8007A980(3, 4, 0);

    if (p == NULL) {
        return NULL;
    }
    M2C_FIELD(p, void **, 0x1C) = f_HandleDryingRackController;
    M2C_FIELD(p, s32 *, 0x10) = a;
    p[0x2] = 16;
    return p;
}

void func_8013A784(u8 *a) {
    s32 lim;
    s32 y;

    if (a[3] == 0) {
        lim = M2C_FIELD(a, s16 *, 0x68);
        y = lim << 16;
    } else {
        lim = M2C_FIELD(a, s16 *, 0x62);
        y = lim << 16;
    }
    do {
        M2C_FIELD(a, s32 *, 0x30) += M2C_FIELD(a, s16 *, 0x50) << 8;
        func_800517F8(a);
        f_DeployDryingRackSegments(a);
    } while (M2C_FIELD(a, s16 *, 0x32) < lim);
    M2C_FIELD(a, s32 *, 0x30) = y;
}

extern s16 D_800ED098;
s32 func_8013A818(AreaPartsOwner *a) {
    s32 i;
    u8 *g;

    if (D_800ED098 < 0xD) {
        return 1;
    }
    a->pad[8] = 0xD;
    a->pad[9] = 0xD;
    a->pad[0xB] = 0;
    a->pad[0xD] = 0;
    for (i = 0; i < a->pad[8]; i++) {
        a->parts[i] = func_8007AAE8();
        func_80051B04(a->parts[i], 0xC, i + 0x26);
    }
    g = (u8 *)&D_800BF870;
    a->pad[3] = 0;
    if (g[0x268] == 0 && g[0x49] != 0xFF) {
        func_80118974((s32)a->parts[4]);
    }
    f_SpawnStarShapedCogPickup(a);
    f_InitializeDryingRackControllerState(a);
    return 0;
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8013A900);

u8 *func_8013AC34(s32 a, u8 b) {
    u8 *p = func_8007A980(2, 4, 0);

    if (p == NULL) {
        return NULL;
    }
    M2C_FIELD(p, void **, 0x1C) = func_8013A900;
    M2C_FIELD(p, s32 *, 0x10) = a;
    p[0x2] = 17;
    p[0x3] = b;
    return p;
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8013AC98);

void func_8013ADBC(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 4);
    switch (temp_v1) {                              /* irregular */
    case 0:
        M2C_FIELD(arg0, s16 *, 0x80) = 0x50;
        M2C_FIELD(arg0, s16 *, 0x82) = 0xA0;
        M2C_FIELD(arg0, s16 *, 0x84) = 0xC8;
        M2C_FIELD(arg0, s16 *, 0x86) = 0x190;
        M2C_FIELD(arg0, u8 *, 4) = 1U;
        M2C_FIELD(arg0, s8 *, 0) = 1;
        M2C_FIELD(arg0, s8 *, 0xB) = 0;
        M2C_FIELD(arg0, s8 *, 0x2B) = 0;
        M2C_FIELD(arg0, s8 *, 0x29) = 0;
        M2C_FIELD(arg0, u8 *, 0x5E) = 0U;
        M2C_FIELD(arg0, s16 *, 0x40) = 0x1E;
        return;
    case 1:
        if (func_8007778C(arg0) != 0) {
            func_8013AC98(arg0);
        }
        M2C_FIELD(arg0, s8 *, 0x29) = 0;
        M2C_FIELD(arg0, s8 *, 0x2B) = 0;
        return;
    case 2:
        if (M2C_FIELD(arg0, u8 *, 5) == 0) {
            M2C_FIELD(arg0, u8 *, 4) = 1U;
            M2C_FIELD(arg0, s8 *, 0) = 1;
            M2C_FIELD(arg0, s8 *, 0x29) = 1;
            M2C_FIELD(arg0, u8 *, 5) = (u8) M2C_FIELD(arg0, u8 *, 0x5E);
        }
        func_8013AC98(arg0);
        return;
    case 3:
        func_8007A624(arg0);
        return;
    }
}

void func_8013AEC0(void *arg0) {
    M2C_FIELD(arg0, s16 *, 0x80) = 0x50;
    M2C_FIELD(arg0, s16 *, 0x82) = 0xA0;
    M2C_FIELD(arg0, s16 *, 0x84) = 0xC8;
    M2C_FIELD(arg0, s16 *, 0x86) = 0x190;
    M2C_FIELD(arg0, s16 *, 0x40) = 0x1E;
}

void func_8013AEEC(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 5) == 0) {
        M2C_FIELD(arg0, s8 *, 4) = 1;
        M2C_FIELD(arg0, s8 *, 0) = 1;
        M2C_FIELD(arg0, s8 *, 0x29) = 1;
        M2C_FIELD(arg0, u8 *, 5) = (u8) M2C_FIELD(arg0, u8 *, 0x5E);
    }
}

typedef struct { s16 unk0; s16 x, y, z; } PartPose;
extern PartPose D_8014AABC[3];
extern PartPose D_8014AAD4[3];
typedef struct { u8 pad[0x5E]; u8 pose; u8 pad2[0xC0 - 0x5F]; s16 *parts[3]; } PosedActor;
void func_8013AF18(PosedActor *a, s32 b, s32 c) {
    s32 i;

    for (i = 0; i < 3; i++) {
        if (b == 0) {
            func_80051B04(a->parts[i], c, i);
            a->parts[i][0] = D_8014AABC[i].x;
            a->parts[i][1] = D_8014AABC[i].y;
            a->parts[i][2] = D_8014AABC[i].z;
        } else {
            func_80051B04(a->parts[i], c, i + 3);
            a->parts[i][0] = D_8014AAD4[i].x;
            a->parts[i][1] = D_8014AAD4[i].y;
            a->parts[i][2] = D_8014AAD4[i].z;
        }
    }
    a->pose = b;
}

extern u8 D_8001B7B0[];
void D_8004C930();
void f_UpdateMagicFlowerWateringSequence(u8 *a, s32 b) {
    u16 v;
    u8 *p;

    switch (a[5]) {
    case 0:
        if (a[0x29] == 1) {
            a[5]++;
            func_8013AF18(a, 0, b);
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

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_HandleMagicFlowerActor);

extern s16 D_1F8001A0;
extern s16 D_1F8001A2_3da0;
typedef struct {
    u8 b[0x56];
    s16 h56;
    u8 pad58[8];
    s16 h60;
    s16 h62;
    u8 pad64[0x5C];
    u8 *parts[3];
} DoorActor;
s32 f_InitializeEvilPigDoorActor(DoorActor *a, s16 *d) {
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
    y = D_1F8001A2_3da0;
    a->h60 = x;
    a->h62 = y;
    a->h56 = x;
    M2C_FIELD(a->parts[0], s16 *, 0xA) = M2C_FIELD(a->b, s16 *, 0x7C);
    return 0;
}

void f_InitializeEvilPigDoorFromTravelState(u8 *a, s32 b) {
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
    if (f_InitializeEvilPigDoorActor(a, b) != 0) {
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
void f_OpenEvilPigDoor(u8 *a) {
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

void func_8013BAB0(u8 *a) {
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

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8013BCC8);

extern ClutCycle D_8014ABDC[];
extern s8 D_8014C77C[];
void func_8013C0BC(s32 arg0) {
    ClutRect r;
    s32 i;
    ClutCycle *e;
    u8 *data;

    if (arg0 == 0) {
        for (i = 0; i < 1; i++) {
            D_8014C77C[i] = 0;
        }
        return;
    }
    e = D_8014ABDC;
    for (i = 0; i < 1; i++, e++) {
        if (--D_8014C77C[i] <= 0) {
            if (e->ptr[0] == 0xFF) {
                e->ptr -= e->ptr[1];
            }
            data = e->clut + e->ptr[0] * 32;
            D_8014C77C[i] = e->ptr[1];
            r.x = e->x;
            r.y = e->y;
            r.w = 16;
            r.h = 1;
            func_80081218(&r, data);
            e->ptr += 2;
        }
    }
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8013C1DC);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateKainenHouseProgressEffectActor);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateKainenHouseFallingParticleActor);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8013C7F0);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8013C9C0);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8013CDD4);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8013D454);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8013D588);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8013D828);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8013D9D4);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8013DBE4);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8013DD34);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8013E08C);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8013E424);

#define W(p, o) M2C_FIELD(p, u32 *, o)
typedef struct {
    u8 b[6][4];
} FlickerTbl;
extern FlickerTbl D_8010A070;
void func_8013E620(u8 *a) {
    FlickerTbl t = D_8010A070;

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

extern u8 D_800A0B38[];
extern u8 D_8014BD14[];
extern u8 D_8014BD48[];

void func_8013E840(u8 *a)
{
    s16 sp[6];
    s8 *s = (s8 *)(a + 0x50);
    u8 *e;

    switch (a[4]) {
    case 0:
        *(u8 **)(a + 0x50) = D_800A0B38;
        *(s32 *)(a + 0x48) = 0;
        *(s16 *)(a + 0x4C) = 0;
        s[4] = 0;
        a[0x29] = 0;
        *(s16 *)(a + 4) = 1;
    case 1:
        *(u8 **)(a + 0x3C) = D_8014BD14 + s[4] * 4;
        a[0x29] = D_8014BD48[s[4]];
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

typedef struct {
    s16 x, y, z, pad;
} SVec4;
void func_8013E9D8(u8 *a) {
    SVec4 v;
    SVec4 w;

    v.x = M2C_FIELD(M2C_FIELD(a, s16 **, 0x14), s16 *, 0);
    v.y = M2C_FIELD(M2C_FIELD(a, s16 **, 0x14), s16 *, 2);
    v.z = M2C_FIELD(M2C_FIELD(a, s16 **, 0x14), s16 *, 4);
    w.x = M2C_FIELD(a, s16 *, 0x4E);
    w.y = M2C_FIELD(a, s16 *, 0x50);
    w.z = M2C_FIELD(a, s16 *, 0x52);
    func_8013DD34(&v, &w);
    func_8003CCA4(a);
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8013EA64);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8013EBA0);

extern u8 D_8014BCC0[];
extern u8 D_8014BCAC[];
void func_8013EC48(u8 *a) {
    u8 *p;

    switch (a[4]) {
    case 0:
        M2C_FIELD(a, u8 **, 0x40) = D_8014BCC0;
        M2C_FIELD(a, u8 **, 0x50) = D_8014BCAC;
        M2C_FIELD(a, s32 *, 0x48) = 0;
        M2C_FIELD(a, s16 *, 0x4C) = 0;
        a[4] = 1;
    case 1:
        p = M2C_FIELD(a, u8 **, 0x40);
        M2C_FIELD(a, u8 **, 0x3C) = p;
        if (p == NULL) {
            a[4] = 2;
            break;
        }
        if (func_8002B278(a) == 0) {
            func_80031744(a);
        }
        break;
    case 2:
    case 3:
        func_8007A624(a);
        break;
    }
}

extern s8 D_1F800090[];
void func_8013ED08(void *arg0) {
    *((s32 *)D_1F800090) = 0;
    func_800318A0(arg0 + 0x2C, arg0 + 0x54, arg0 + 0x48);
    func_80027768(M2C_FIELD(arg0, s32 *, 0x50), 0, M2C_FIELD(arg0, s16 *, 0x32), M2C_FIELD(arg0, u8 *, 7));
}

void func_8013ED54(u8 *a) {
    SVec4 v;
    SVec4 w;

    v.x = M2C_FIELD(M2C_FIELD(a, s16 **, 0x14), s16 *, 0);
    v.y = M2C_FIELD(M2C_FIELD(a, s16 **, 0x14), s16 *, 2);
    v.z = M2C_FIELD(M2C_FIELD(a, s16 **, 0x14), s16 *, 4);
    w.x = M2C_FIELD(a, s16 *, 0x4E);
    w.y = M2C_FIELD(a, s16 *, 0x50);
    w.z = M2C_FIELD(a, s16 *, 0x52);
    func_8013DD34(&v, &w);
}

typedef struct { s16 x, y, z, pad; } RingVec;
extern RingVec D_8014C780[];
void func_8013EDD0(void) {
    s32 i;
    s32 ang;
    RingVec *p;

    p = D_8014C780;
    for (i = 0; i < 15; i++, p++) {
        ang = (i << 12) / 15;
        p->x = func_80083F50(ang) >> 4;
        p->y = 0;
        p->z = func_80083E80(ang) >> 4;
    }
    p->x = D_8014C780[0].x;
    p->y = D_8014C780[0].y;
    p->z = D_8014C780[0].z;
}

typedef struct { s16 pos; s16 vel; } RiseMotion;
void func_8013EEA0(u8 *a) {
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

extern s32 D_1F800090_3460;
void func_8013EF58(u8 *a)
{
    u8 buf[0x30];
    void *m;
    s32 y;

    func_800318A0(a + 0x2C, a + 0x50, a + 0x48);
    m = *(void **)(a + 0x3C);
    y = *(s16 *)(a + 0x32);
    D_1F800090_3460 = *(s32 *)(a + 0x54);
    func_80027768(m, 0, y, a[0x29]);
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_CollectVisibleA00GridCellsForCamera);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_CollectA00GridCellsInsideTriangle);

s32 f_TestA00GridCellMask(s32 x, s32 y) {
    return D_8014C804_6a3a[y * 52 + x] & (D_8014C800 << 4);
}

s32 f_GetA00GridCellValue(s32 x, s32 y) {
    return D_8014C804_6a3a[y * 52 + x];
}

extern s8 *D_8014C804;
void func_8013FB4C(u8 *a)
{
    s8 **t = D_800ECF58;
    u16 *p = (u16 *)t[8];
    u16 v;

    *(u16 **)(a + 0xC) = p;
    *(u16 *)(a + 8) = p[0];
    v = p[1];
    a[7] = 0;
    *(u16 *)(a + 0xA) = v;
    D_8014C804 = t[9];
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_DrawTownCreatureGt3Batch);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_DrawTownCreatureGt4Batch);

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
void func_801401B8(PartList *a)
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
        r = f_DrawTownCreatureGt3Batch(e + 1, ot, v & 0xFF);
        v >>= 16;
        f_DrawTownCreatureGt4Batch(r, ot, v & 0xFF);
    }
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_801402B8);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8014047C);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80140544);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateTownCreatureTerrainContact);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateTownCreatureFaceTomba);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_801409C0);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateTownCreatureKnockbackBounce);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8014103C);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateTownCreatureFleeRun);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateTownCreatureStraightRun);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80141AC4);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateTownCreatureHopAndBrake);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateTownCreatureVerticalLaunch);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateTownCreatureLaunchLanding);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateTownCreaturePostKnockbackRecovery);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateTownCreatureRandomIdle);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateTownCreatureIdleDecision);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateTownCreatureApproachTomba);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateTownCreatureLeapingCharge);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateTownCreatureExtendedLeap);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateTownCreatureJumpingAttack);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateTownCreatureBehaviorState);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateTownCreatureVariantActivation);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateTownCreatureInteractionLifecycle);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_HandleTownCreatureActor);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateTownCreatureSpawner);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateCrabBasketCarrierSequence);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateLinkedTownCreatureActor);

s32 func_80145C78(s32 k, u8 *b) {
    if (k < 4) {
        return M2C_FIELD(b, s16 *, 0xA) >= 0x125C;
    }
    if (k == 7) {
        return M2C_FIELD(b, s16 *, 0xA) >= 0x125C;
    }
    if ((u32)(k - 4) < 8) {
        return 1;
    }
    return 2;
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80145CD0);

extern s8 D_1F800160[];
extern s8 D_1F800164[];
s32 func_80145DD4(s32 arg0, s32 arg1) {
    return (u32) (((arg1 - func_800782B0(arg0 + 0x2C, *((s16 *)D_1F800160), *((s16 *)D_1F800164))) + 0x400) & 0xFFF) >= 0x801U;
}

s32 func_80145E20(u8 *a) {
    u8 *q = a + 0x60;
    s32 h = M2C_FIELD(a, u16 *, 0x60);
    s8 r;

    r = (u32)((h - func_800782B0(a + 0x2C, D_1F800160_71b4, D_1F800164_d75f) + 0x400) & 0xFFF) > 0x800;
    if (r) {
        M2C_FIELD(q, u16 *, 2) |= 1;
    } else {
        M2C_FIELD(q, u16 *, 2) &= 0xFFFE;
    }
    return r;
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80145EA4);

extern s8 D_1F800160[];
extern s8 D_1F800164[];
void func_80145F30(void *arg0) {
    s16 temp_a2;

    temp_a2 = M2C_FIELD(arg0, s16 *, 0x2E);
    func_800781E0(temp_a2 - *((s16 *)D_1F800160), M2C_FIELD(arg0, s16 *, 0x36) - *((s16 *)D_1F800164), temp_a2);
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80145F6C);

s32 func_8014601C(u8 *a) {
    s16 d = func_800781E0(M2C_FIELD(a, s16 *, 0x2E) - D_1F800160_71b4, M2C_FIELD(a, s16 *, 0x36) - D_1F800164_d75f);

    if ((D_800E7FFE & 0x8200) || d > 0x640) {
        return -1;
    }
    if (d >= 0x44D) {
        return 0;
    }
    if (d >= 0x259) {
        return 1;
    }
    return 2;
}

s16 func_801460A4(void *arg0) {
    s16 temp_v0;

    temp_v0 = f_UpdateTownCreatureKnockbackBounce();
    if ((u8) M2C_FIELD(arg0, u8 *, 7) < 3U) {
        M2C_FIELD(arg0, s16 *, 0x58) = 0;
    }
    return temp_v0;
}

s32 f_UpdateTownCreatureTurnaround(u8 *a) {
    s32 r = 0;
    u8 *q = a + 0x60;

    switch (a[7]) {
    case 0:
        M2C_FIELD(q, u16 *, 2) &= ~4;
        func_801402B8(a, 0x1A, 8);
        M2C_FIELD(a, s16 *, 0x4E) = 0;
        a[7] = 1;
    case 1:
        if (M2C_FIELD(M2C_FIELD(a, u8 **, 0x38), u16 *, 4) != 0) {
            M2C_FIELD(q, u16 *, 2) ^= 1;
            M2C_FIELD(a, s16 *, 0x56) += 0x800;
            func_801402B8(a, 7, 0);
            a[7] = 2;
        }
        break;
    default:
        if (a[7] >= 0x14) {
            r = 1;
        } else {
            a[7]++;
        }
        break;
    }
    M2C_FIELD(a, s16 *, 0x32) += 0x10;
    f_UpdateTownCreatureTerrainContact(a);
    return r;
}

s32 func_801461E4(u8 *a, s32 b, u8 c) {
    u16 *f = (u16 *)(a + 0x60);
    s32 r = 0;

    if (a[7] == 0) {
        f[1] &= 0xFFFB;
        func_801402B8(a, (s16)b, 8);
        a[7] = c;
        M2C_FIELD(a, s16 *, 0x4E) = 0;
    }
    if (a[7] < 2) {
        r = 1;
    } else {
        a[7]--;
    }
    M2C_FIELD(a, s16 *, 0x32) += 0x10;
    f_UpdateTownCreatureTerrainContact(a);
    return r;
}

s32 func_80146288(s16 *v, u32 r) {
    return (u32)func_80078240(D_1F800160_71b4 - v[0], D_1F800162 - v[1], D_1F800164_d75f - v[2]) < r;
}

u8 *func_801462E4(s32 a, s32 b) {
    u8 *p = func_80072DDC(0, 3, 2, 3);

    if (p != NULL) {
        M2C_FIELD(p, void **, 0x1C) = f_HandleTownCreatureActor;
        p[0x3] = b;
        M2C_FIELD(p, s32 *, 0x10) = 0;
        M2C_FIELD(p, s32 *, 0x14) = a;
    }
    return p;
}

u8 *func_80146348(u8 *a, void *b) {
    u8 *g = D_800BF808_1760;
    u8 *p;

    if (g[0x1B] & 0x80) {
        return NULL;
    }
    p = func_80072DDC(a, 3, 2, 3);
    if (p != NULL) {
        g[0x1B] |= 0x80;
        p[3] = 0x80;
        M2C_FIELD(p, u8 **, 0x10) = a;
        M2C_FIELD(p, void **, 0x14) = b;
        M2C_FIELD(p, void **, 0x1C) = f_HandleTownCreatureActor;
    }
    return p;
}

extern u8 D_800BF823;
void func_801463EC(u8 *a) {
    switch (a[4]) {
    case 0:
        a[4] = 1;
        a[5] = 0;
        D_800BF823 = 0;
        break;
    case 1:
        if (D_1F800137 == 0) {
            f_UpdateTownCreatureSpawner(a);
        }
        break;
    case 2:
    case 3:
        func_8007ADD0(a);
        break;
    }
}

void func_80146478(u32 *p, void *b)
{
    u32 lo = *p;
    u32 packed;

    packed = lo;
    lo = packed & 0xFFFF;
    p += 4;
    f_UpdateWindmillCollapseParticleActor(func_801465EC(p, b, lo), b, packed >> 16);
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_ApplyOverlayModelFrameRange);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_801465EC);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateWindmillCollapseParticleActor);

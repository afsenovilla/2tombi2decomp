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

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8010C780);


void func_8010C87C(void) {
    func_8010A7F8();
}

void func_8010C89C(void *a, void *b)
{
    func_80056B48(a, 1);
    f_UpdateA00TombaWaterSurfaceMotion(a, b);
    func_80055D5C(a);
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8010C8E4);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8010C9F8);

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

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8010CED0);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateFishermensTownCamera);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8010D89C);

extern s8 D_1F800138[];
extern s8 D_1F80019B[];

void func_8010DA70(void) {
    func_80045258(M2C_FIELD(*((volatile void **)D_1F800138), u8 *, 0x6E), 0xF);
    *((volatile s8 *)D_1F80019B) = 1;
    func_80051FB4();
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8010DAB0);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8010DB58);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8010DBE4);

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

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8010DE0C);

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

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80110DE8);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_ResolveCarriedChickSurfaceContact);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80111128);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_ResolveTombaPlaneSwitchActorContact);

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
extern u8 D_1F800182_5650;

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

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_801141C8);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80114290);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80114320);

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

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_ResolveTombaMultipartActorContact);


s32 func_80114640(s32 arg0, s32 arg1) {
    return func_8010F034(arg0, arg1, M2C_FIELD(arg1, s32 *, 0xC4));
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80114664);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_801146E0);

extern s8 D_1F800182[];

void func_8011479C(s32 arg0, M2C_UNK arg1) {
    if (func_80022F04() != 0) {
        func_8001E860(arg0, arg1, 0, 0);
        *((s8 *)D_1F800182) = 0;
    }
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_801147EC);

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

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80114AF4);

extern u8 *D_8014C804_6a3a;
extern u16 D_8014C800;

void func_80114B8C(u8 *a, u8 *b) {
    if (func_80023870(a, b, M2C_FIELD(b, u8 **, 0xC0)) != 0) {
        D_1F800182_5650 = 0;
    }
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80114BBC);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80114C5C);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80114CD0);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80114D48);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80114DF4);

extern s16 D_1F800160_71b4;
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

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80114ED4);

extern s8 D_1F800182[];

void func_80114F54(s32 arg0, void *arg1) {
    if (func_80022F04() != 0) {
        M2C_FIELD(arg1, s8 *, 0) = 2;
        M2C_FIELD(arg1, s8 *, 4) = 2;
        M2C_FIELD(arg1, s8 *, 5) = 0;
        *((s8 *)D_1F800182) = 0;
    }
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80114F94);

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

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_ResolveA00ActiveActorCollisionCandidates);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8011534C);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80115598);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_801158E0);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80115B88);

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

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80117460);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_801174D8);

extern s8 D_800BF9E5;
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

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_SpawnRareFishPickup);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80117D7C);


void func_80117E5C(void *arg0) {
    func_8004D4C4(0x3A, 1);
    func_8004B0D8(arg0);
    M2C_FIELD(arg0, s8 *, 4) = 3;
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80117E98);

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

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_801180CC);


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

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_801188A0);

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

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80119254);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80119350);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80119454);

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

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8011AB00);

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

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8011AC5C);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8011ACDC);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateWindmillExplosionDebris);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateWindmillFallingActor);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8011B738);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8011BC3C);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8011BDB8);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateKainenHouseSceneActor);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8011C090);

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

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8011CD14);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8011CDB8);


s32 func_8011CE64(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x7A) == 1) {
        func_80040B48(0x4E);
    }
    return 1;
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_AdvanceKainenHouseRescueSequence);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_HandleKainenInteraction);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_HandleKainenNpcActor);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8011D82C);

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

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8012175C);

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

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80122BF4);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80122CA4);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80122D58);

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

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80122FAC);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_801230A4);


s32 func_80123180(s32 arg0) {
    M2C_FIELD(arg0, s32 *, 0x14) = f_SpawnGoldFishhookPickup(arg0, 1);
    return 1;
}


s32 func_801231B0(void) {
    func_8004D650(0x45, 1);
    func_8004ED0C(0x45, 4);
    return 1;
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_801231E0);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_801232DC);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_801233DC);

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

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_EnsureCarriedChickActor);

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

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateCarriedChickCollision);


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

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_SpawnNestChickFromParent);


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

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_FeedChicksAtNest);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UseNishikiWingsAtNest);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80127798);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80127D1C);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_801280E8);

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

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80129008);

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

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8012D404);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_HandleGoldFishhookScenePropActor);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8012D908);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_HandleTownQuestRewardVisualActor);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8012DE34);

u8 *func_8012DF08(s32 a) {
    u8 *p = func_80072DDC(a, 128, 3, 16);

    if (p == NULL) {
        return NULL;
    }
    p[0x3] = 2;
    M2C_FIELD(p, void **, 0x1C) = f_HandleTownQuestRewardVisualActor;
    return p;
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8012DF50);


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

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_InitializeTownQuestRewardVisualModel);

void func_8012E0D0(void *a)
{
    if (func_80051B70(a, 0xC, 7) == 0) {
        func_800517F8(a);
    }
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8012E10C);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8012E1E4);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8012E2BC);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8012E478);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8012E53C);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8012E5CC);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8012E678);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8012E70C);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8012E7EC);


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

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_HideCollectedBarrelLinkedPickups);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_BeginScriptedBarrelRotation);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateBarrelSeesawSupportHeight);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_ApplyBarrelSeesawContactImpulse);

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

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_ActivateBarrelLinkedSegmentPair);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80131840);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80131D08);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_SettleDryingRackGrabHandleRotation);

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

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80132954);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateAquaticPlantHitWobble);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80132D58);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateAquaticPlantGrabMotion);

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

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateAquaticPlantRotationKick);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_ConfigureAquaticPlantMotion);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_ClassifyAquaticPlantContact);

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

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80136748);

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

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_SpawnSegmentedTownActor);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_801389C8);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80138A64);

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

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8013A784);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8013A818);

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

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateMagicFlowerWateringSequence);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_HandleMagicFlowerActor);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_InitializeEvilPigDoorActor);

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

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_OpenEvilPigDoor);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8013BAB0);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8013BCC8);

typedef struct { s16 x, y, w, h; } ClutRect;
typedef struct {
    u8 *ptr;
    u8 *clut;
    s16 x;
    s16 y;
} ClutCycle;
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

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8013E620);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8013E840);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8013E9D8);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8013EA64);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8013EBA0);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8013EC48);

extern s8 D_1F800090[];

void func_8013ED08(void *arg0) {
    *((s32 *)D_1F800090) = 0;
    func_800318A0(arg0 + 0x2C, arg0 + 0x54, arg0 + 0x48);
    func_80027768(M2C_FIELD(arg0, s32 *, 0x50), 0, M2C_FIELD(arg0, s16 *, 0x32), M2C_FIELD(arg0, u8 *, 7));
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8013ED54);

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

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_801401B8);

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

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80145E20);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80145EA4);

extern s8 D_1F800160[];
extern s8 D_1F800164[];

void func_80145F30(void *arg0) {
    s16 temp_a2;

    temp_a2 = M2C_FIELD(arg0, s16 *, 0x2E);
    func_800781E0(temp_a2 - *((s16 *)D_1F800160), M2C_FIELD(arg0, s16 *, 0x36) - *((s16 *)D_1F800164), temp_a2);
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80145F6C);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8014601C);


s16 func_801460A4(void *arg0) {
    s16 temp_v0;

    temp_v0 = f_UpdateTownCreatureKnockbackBounce();
    if ((u8) M2C_FIELD(arg0, u8 *, 7) < 3U) {
        M2C_FIELD(arg0, s16 *, 0x58) = 0;
    }
    return temp_v0;
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateTownCreatureTurnaround);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_801461E4);

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

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80146348);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_801463EC);

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

#include "common.h"
#include "game.h"
#include "m2c.h"

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8010A518);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8010A66C);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8010A838);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8010A9AC);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8010AC90);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8010AEAC);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8010B1F8);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8010B334);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8010B59C);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8010B6B0);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8010B860);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8010BA74);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8010C034);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8010C240);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8010C3B4);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8010C7F8);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8010CAE8);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8010CE50);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8010D134);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8010D288);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8010D3BC);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8010D9F0);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8010DD58);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8010DF24);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8010E1C4);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8010E3DC);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8010E548);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8010E7D4);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8010E908);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8010ED04);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8010EE7C);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8010F0F0);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8010F2E8);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8010F450);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8010F608);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8010F870);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8010F91C);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8010FECC);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_801102A4);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8011065C);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_801109F8);

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

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80110FE0);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80111084);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80111108);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8011118C);


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

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_801112BC);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8011130C);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80111350);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_801113A8);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_801113EC);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8011146C);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8011159C);

extern u8 D_1F800182_5650;
extern u8 D_1F800182_5650;
extern s32 D_1F80009C;

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

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_801117B4);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_801118DC);


s32 func_80111988(s32 arg0, s32 arg1) {
    return func_8010DF24(arg0, arg1, M2C_FIELD(arg1, s32 *, 0xC0));
}

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_801119AC);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80111A80);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80111AC4);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80111B58);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80111BA4);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80111CA4);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80111DC4);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80111ED4);

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

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80112018);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80112084);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_801120F0);

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

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_801121D0);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_801122A0);

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

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8011237C);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80112838);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80112C60);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80112E24);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80113110);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80113390);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_801134E4);


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

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80113C30);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80113E3C);

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
    func_80112838();
}

void func_8011460C(void *a, void *b)
{
    func_80056B48(a, 1);
    func_8011237C(a, b);
    func_80055D5C(a);
}

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80114654);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80114730);

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

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_801147CC);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80114840);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80114A18);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80114C1C);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_801151D8);

extern s8 D_1F800138[];
extern s8 D_1F80019B[];

void func_801153F8(void) {
    func_80045258(M2C_FIELD(*((volatile void **)D_1F800138), u8 *, 0x6E), 0xF);
    *((volatile s8 *)D_1F80019B) = 1;
    func_80051FB4();
}

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80115438);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_801154D4);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_801155C4);

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

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_801160D4);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80116288);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80116310);

INCLUDE_ASM("asm/a06/nonmatchings/a06", f_UpdateDonglinInteriorEnvironmentActor);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_801168E4);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80116AF8);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80116D00);

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

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80117BD4);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80117CF4);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80117F34);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_801180A0);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_801182F4);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8011847C);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80118664);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_801188B0);

INCLUDE_ASM("asm/a06/nonmatchings/a06", f_UpdateDonglinInteriorQuestObjectActor);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80119674);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_801196E4);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80119764);


void func_801197C0(void *arg0) {
    func_80077B5C();
    M2C_FIELD(arg0, s8 *, 1) = 1;
}

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_801197EC);


void func_8011983C(void *arg0) {
    M2C_FIELD(arg0, s8 *, 1) = 1;
    func_800517F8();
    func_8004B374(arg0, 1);
}

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80119874);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80119938);


void func_80119974(void *arg0) {
    M2C_FIELD(arg0, s8 *, 1) = 1;
    func_800517F8();
}

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80119998);

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

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80119B64);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80119BF0);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80119CC0);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80119D94);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80119E88);


void func_80119EE8(void *arg0) {
    if ((D_800BF870.pad1[0x62] != 0xFF) && (D_800BF870.pad1[0x62] & 4)) {
        D_800BF870.pad1[0x62] &= 0xFB;
        func_80051B04(M2C_FIELD(arg0, s32 *, 0xC0), 0xC, 0x4D);
    }
    func_8007778C(arg0);
}

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80119F44);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8011A024);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8011A08C);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8011A104);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8011A1AC);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8011A2E8);


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

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8011A3C4);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8011A410);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8011A48C);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8011A4F4);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8011A564);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8011A7A8);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8011A8B8);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8011A974);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8011AB30);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8011AC9C);


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

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8011CD34);


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

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8011CF8C);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8011D014);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8011D100);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8011D520);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8011D67C);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8011D748);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8011D810);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8011D8F8);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8011DA10);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8011DC6C);

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

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8011E040);

void func_8011E124(u8 *a)
{
    if (a[0x29] == 0) {
        func_8011E308(a, 1);
        a[5] = 3;
        a[6] = 1;
        *(s16 *)(a + 0x6C) = 1;
    }
}

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8011E174);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8011E248);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8011E308);

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

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8011F4B0);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8011F71C);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8011F9E4);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8011FBE8);

INCLUDE_ASM("asm/a06/nonmatchings/a06", f_UpdateDonglinInteriorEntranceActor);


void func_801205E8(void) {
    func_8011EF18();
}

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80120608);


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

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_801207BC);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80120844);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80120954);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80120B0C);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80120D2C);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80120E0C);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80120FB4);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_801210CC);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_801214C0);

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

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_801223DC);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80122524);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80122724);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80122878);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_801229A0);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80122CAC);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80122D64);


void func_80122E00(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 5) == 0) {
        func_80122724();
    }
}

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80122E30);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80122EA0);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80123018);

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

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80123A60);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80123AC4);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80123BB8);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80123BE8);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80123C14);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80123C64);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80123E30);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80124058);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80124198);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8012462C);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_801248B4);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80124AA0);

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

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80124D70);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80124DE0);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80124ED4);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80125010);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_801251E8);


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

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80125E4C);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80125FC8);

extern u8 D_800BFB5B;
s32 func_80126040(void) {
    return D_800BFB5B != 0;
}

INCLUDE_ASM("asm/a06/nonmatchings/a06", f_UpdateDeepForestSeesawActor);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80126334);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_801265E4);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8012665C);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80126834);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80126990);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80126BD8);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80126DF0);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_801271E4);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80127304);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80127524);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8012779C);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80127928);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80127C28);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80127E18);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80127EF8);

extern u8 D_800BF80E;
s32 func_80127FEC(void *arg0) {
    u16 temp_v0;

    if ((D_800BF80E != 0) || (temp_v0 = M2C_FIELD(arg0, u16 *, 0x72), M2C_FIELD(arg0, u16 *, 0x72) = (u16) (temp_v0 - 1), ((temp_v0 << 0x10) <= 0))) {
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80128028);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80128120);

INCLUDE_ASM("asm/a06/nonmatchings/a06", f_UpdateNishikiTempleBirdActor);

extern s8 D_800BF818;
s32 func_80128780(void) {
    D_800BF818 = 7;
    return 1;
}

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80128794);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80128A70);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80128D30);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80128DF0);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80128F98);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80129218);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8012945C);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_801296A0);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80129858);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80129AF8);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80129C50);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8012A2B8);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8012A384);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8012A410);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8012A4B0);


void func_8012A548(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 6) == 0) {
        M2C_FIELD(arg0, u8 *, 6) = 1U;
    }
}

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8012A564);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8012A900);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8012A958);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8012AAF0);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8012AD3C);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8012B14C);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8012B350);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8012B3C0);

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

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8012D864);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8012D8E4);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8012D954);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8012D9B4);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8012DBF8);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8012DDC4);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8012E048);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8012E194);


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

extern s16 D_800E7FEE;
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

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8012F79C);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8012F844);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8012F8E0);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8012F9A8);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8012FAF0);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8012FBF0);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8012FE60);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80130468);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80130A2C);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80130BB4);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80130D98);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80130F1C);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80131650);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80131680);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80131750);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80131870);


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

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80131B10);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80131BB4);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80131BE8);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80131CD4);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80131DD8);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8013203C);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8013256C);

INCLUDE_ASM("asm/a06/nonmatchings/a06", Guards);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80132CF8);

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

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80136C10);


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

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80137148);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80137284);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_801379D4);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80137C9C);

extern u8 D_800BF80E;
s32 func_80137E18(void *arg0) {
    u16 temp_v0;

    if ((D_800BF80E != 0) || (temp_v0 = M2C_FIELD(arg0, u16 *, 0x72), M2C_FIELD(arg0, u16 *, 0x72) = (u16) (temp_v0 - 1), ((temp_v0 << 0x10) <= 0))) {
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80137E54);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80137EA4);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80138000);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_801381A8);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80138578);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_801388CC);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80138B30);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80138C68);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80139088);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_801392D8);

INCLUDE_ASM("asm/a06/nonmatchings/a06", f_RunRockCrabBalanceCameraSequence);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80139728);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_801398E4);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80139A28);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80139C84);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80139F58);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8013A09C);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8013A250);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8013A3D0);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8013A598);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8013A81C);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8013AA14);


s32 func_8013AE18(void) {
    func_8006E1E4();
    return 1;
}

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8013AE38);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8013AE88);


s32 func_8013AED8(void) {
    return M2C_FIELD(*(void **)0x1F800214, u8 *, 3) == 0;
}

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8013AEF0);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8013AF68);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8013AFD8);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8013B074);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8013B0F8);

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

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8013B29C);


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

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8013B38C);

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

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8013B668);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8013B738);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8013B7DC);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8013B844);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8013B8F4);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8013B9C0);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8013BA44);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8013BD40);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8013C0D8);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8013C5B4);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8013CBA0);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8013CD34);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8013CF00);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8013D1E4);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8013D568);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8013D668);

extern u16 D_8014A450;
void func_8013D6BC(s32 arg0) {
    D_8014A450 = (D_8014A450 + arg0) & 0xFF;
}

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8013D6D8);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8013DA8C);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8013E090);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8013E0F4);

extern s8 *D_800ECF58[];
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

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8013EDC0);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8013EF60);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8013F14C);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8013F320);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8013F51C);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8013F658);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8013F878);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8013F99C);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8013FAE4);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8013FBD0);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8013FCF0);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8013FDC0);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8013FE78);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8013FFAC);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80140038);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80140088);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8014013C);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_801401D8);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_801402B0);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80140380);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8014046C);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_801404DC);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_801406A4);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_801406E8);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_801408BC);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80140CCC);

INCLUDE_ASM("asm/a06/nonmatchings/a06", f_UpdateDonglinSnowFireflyPickup);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80141020);

extern s32 D_800BF85C;
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

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_80141480);


void func_80141770(void *arg0) {
    func_8004D4C4(0x3D, 1);
    func_8004B0D8(arg0);
    M2C_FIELD(arg0, s8 *, 4) = 3;
    D_800BF870.pad1[0x1D8] |= 2;
}

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_801417C4);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8014183C);

INCLUDE_ASM("asm/a06/nonmatchings/a06", func_8014189C);

INCLUDE_ASM("asm/a06/nonmatchings/a06", f_UpdatePotatoBugQuestNpcActor);

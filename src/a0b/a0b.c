#include "common.h"
#include "game.h"
#include "m2c.h"

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_801092BC);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_801093F4);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80109630);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80109ACC);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80109F7C);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8010A3D0);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8010A550);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8010A6E0);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8010A93C);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8010ACA8);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8010AE50);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8010B010);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8010B128);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8010B444);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8010B4E4);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8010B590);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8010B680);


s32 func_8010B734(void) {
    return 0;
}

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8010B73C);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8010B938);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8010BC10);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8010BD50);


void func_8010BDF4(void *arg0) {
    s16 temp_a1;
    s16 temp_v0;
    s16 var_v0;
    s16 var_v1;

    temp_a1 = M2C_FIELD(arg0, s16 *, 0x44);
    var_v0 = temp_a1;
    if (temp_a1 < 0) {
        var_v0 = -var_v0;
    }
    temp_v0 = var_v0 - 0xE0;
    var_v1 = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        var_v1 = 0;
    }
    if (temp_a1 >= 0) {
        M2C_FIELD(arg0, s16 *, 0x44) = var_v1;
        return;
    }
    M2C_FIELD(arg0, s16 *, 0x44) = (s16) -var_v1;
}

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8010BE38);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8010BE80);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8010C0A4);


void func_8010C300(void) {
}


void func_8010C308(void) {
}

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8010C310);


void func_8010C488(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 4);
    switch (temp_v1) {                              /* irregular */
    case 0:
        M2C_FIELD(arg0, u8 *, 4) = 1U;
        func_8010C310(arg0, 0U);
        func_800310F4(0xC05, 0);
        func_800752B4(1);
        func_80075D24(0x1FFF);
        return;
    case 1:
        if (func_80026AD0(arg0) != 0) {
            func_8010C310(arg0, M2C_FIELD(arg0, u8 *, 3));
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

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8010C554);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8010C778);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8010C948);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8010CA34);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8010CB44);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8010D1F0);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8010D884);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8010E0E8);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8010E22C);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8010EF30);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8010F144);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8010F43C);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8010F544);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", f_UpdateLastEvilPigProjectileAttack);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8010FC1C);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80110118);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80110540);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_801106A4);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80110800);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80110A98);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_801110BC);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_801113B4);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8011159C);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80111770);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8011199C);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80111AB0);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80111C5C);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80111E00);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80111F18);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_801120AC);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_801121E8);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80112704);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_801127BC);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80112880);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80112974);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80112A24);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80112CF0);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80113050);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80113150);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_801133F4);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80113728);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80113770);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80113A28);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80113F68);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80113F94);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_801141B0);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_801144F4);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80114608);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80114AA8);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80114CEC);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80114DE8);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80114ECC);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80115194);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_801153D4);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_801154F8);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_801158B8);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_801159FC);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80115B28);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80115EEC);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_801163C4);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80116520);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_801169E0);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80116A70);


s32 func_80116B1C(void *arg0) {
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x38), s8 *, 4) = 2;
    func_80074590(0x37, 0x16, 0);
    return 1;
}

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80116B50);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80116CB0);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", f_UpdateEvilPigBattleProjectile);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_801175B8);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80117720);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80117774);


void func_80117800(void *arg0) {
    s16 temp_s0;
    s32 temp_lo;
    s32 temp_s2;

    if (M2C_FIELD(arg0, u8 *, 0x5F) == 0) {
        temp_s0 = M2C_FIELD(arg0, s16 *, 0x60);
        temp_s2 = func_80083F50(temp_s0) * M2C_FIELD(arg0, s16 *, 0x44);
        temp_lo = -func_80083E80(temp_s0) * M2C_FIELD(arg0, s16 *, 0x44);
        M2C_FIELD(arg0, s32 *, 0x2C) = (s32) (M2C_FIELD(arg0, s32 *, 0x2C) + temp_s2);
        M2C_FIELD(arg0, s32 *, 0x34) = (s32) (M2C_FIELD(arg0, s32 *, 0x34) + temp_lo);
    }
    M2C_FIELD(arg0, s32 *, 0x30) = (s32) (M2C_FIELD(arg0, s32 *, 0x30) + (M2C_FIELD(arg0, s16 *, 0x50) << 0xC));
}

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_801178A0);

extern s16 D_800BED82;
extern M2C_UNK D_801246AC;
void func_80117988(void) {
    func_80075448(0xA, &D_801246AC, 0x10, D_800BED82);
}

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_801179BC);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", f_SpawnLastEvilPigBattleProjectile);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_801180E8);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_801181AC);

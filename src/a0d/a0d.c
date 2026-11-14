#include "common.h"
#include "game.h"
#include "m2c.h"

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_80109304);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_8010943C);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_80109678);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_801099E0);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_80109B0C);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_80109C54);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_80109EA8);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_8010A04C);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_8010A1D4);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_8010A3C0);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_8010A500);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_8010A7B8);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_8010A830);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_8010A888);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_8010A8AC);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_8010A970);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_8010A9F0);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_8010AA48);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_8010AB3C);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_8010AC1C);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_8010ACC0);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_8010AD1C);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_8010AF40);


void func_8010B100(void) {
}


void func_8010B108(void) {
}

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_8010B110);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_8010B288);


void func_8010B3A8(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 4);
    switch (temp_v1) {                              /* irregular */
    case 0:
        M2C_FIELD(arg0, u8 *, 4) = 1U;
        func_8010B110(arg0, 0U);
        func_8010B288(0);
        func_801129FC();
        func_800752B4(0);
        func_80075D24(0x1FFF);
        return;
    case 1:
        if (func_80026AD0(arg0) != 0) {
            func_8010B110(arg0, M2C_FIELD(arg0, u8 *, 3));
        }
        func_80026A68(arg0);
        func_8010B288(1);
        return;
    case 3:
        func_8007ADD0(arg0);
        /* fallthrough */
    case 2:
        return;
    }
}

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_8010B480);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_8010B6A4);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_8010B874);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_8010B960);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_8010BA70);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_8010C11C);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_8010C7B0);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_8010D014);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_8010D158);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_8010DE5C);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_8010E070);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", f_SpawnEarthEvilPigDetachedPartsActor);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_8010E5EC);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", f_UpdateEarthEvilPigSplitActor);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", f_UpdateEarthEvilPigDetachedPartsAttack);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_8010FA2C);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_8010FDA8);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_8010FEBC);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_801103AC);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_80110618);

extern M2C_UNK func_8010FEBC;
void func_801106C8(void *arg0) {
    M2C_FIELD(arg0, M2C_UNK **, 0x1C) = &func_8010FEBC;
    M2C_FIELD(arg0, s8 *, 2) = 0x68;
    M2C_FIELD(arg0, s8 *, 4) = 1;
    M2C_FIELD(arg0, s8 *, 5) = 7;
    M2C_FIELD(arg0, s16 *, 0x80) = 0x64;
    M2C_FIELD(arg0, s16 *, 0x82) = 0xC8;
    M2C_FIELD(arg0, s16 *, 0x84) = 0xAA;
    M2C_FIELD(arg0, s16 *, 0x86) = 0x1A4;
    M2C_FIELD(arg0, s8 *, 6) = 0;
    M2C_FIELD(arg0, s8 *, 7) = 0;
    M2C_FIELD(arg0, s16 *, 0x58) = 0;
    M2C_FIELD(arg0, s16 *, 0x56) = 0;
    M2C_FIELD(arg0, s16 *, 0x54) = 0;
    M2C_FIELD(arg0, s16 *, 0xB8) = 0x1000;
    M2C_FIELD(arg0, s16 *, 0xBA) = 0x1000;
    M2C_FIELD(arg0, s16 *, 0xBC) = 0x1000;
    M2C_FIELD(arg0, s8 *, 0x29) = 0;
    M2C_FIELD(arg0, s8 *, 0x1B) = 0;
    M2C_FIELD(arg0, s8 *, 0x2B) = 0;
}

extern M2C_UNK f_UpdateEarthEvilPigSplitActor;
void func_80110740(void *arg0) {
    M2C_FIELD(arg0, M2C_UNK **, 0x1C) = &f_UpdateEarthEvilPigSplitActor;
    M2C_FIELD(arg0, s8 *, 2) = 0x40;
    M2C_FIELD(arg0, s8 *, 5) = 1;
    M2C_FIELD(arg0, s16 *, 0x80) = 0x32;
    M2C_FIELD(arg0, s16 *, 0x82) = 0x64;
    M2C_FIELD(arg0, s16 *, 0x84) = 0x46;
    M2C_FIELD(arg0, s16 *, 0x86) = 0xAA;
    M2C_FIELD(arg0, s8 *, 4) = 0;
    M2C_FIELD(arg0, s8 *, 6) = 0;
    M2C_FIELD(arg0, s8 *, 7) = 0;
    M2C_FIELD(arg0, s16 *, 0x58) = 0;
    M2C_FIELD(arg0, s16 *, 0x56) = 0;
    M2C_FIELD(arg0, s16 *, 0x54) = 0;
    M2C_FIELD(arg0, s16 *, 0xB8) = 0x800;
    M2C_FIELD(arg0, s16 *, 0xBA) = 0x800;
    M2C_FIELD(arg0, s16 *, 0xBC) = 0x800;
    M2C_FIELD(arg0, s8 *, 0x29) = 0;
    M2C_FIELD(arg0, s8 *, 3) = 0;
}

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_801107B0);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_801108F0);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_80110A98);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_80110C14);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_80110DBC);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_80111034);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_80111244);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_80111418);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_80111574);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_80111708);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_80111A68);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_80111C94);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_80111DA8);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_80111F54);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_801120F8);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_80112210);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_801123A4);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_801124E0);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_801129FC);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_80112A58);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_80112B1C);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_80112BC4);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_80112D34);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_80112DE4);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_801131B0);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_80113628);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_80113748);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_801139EC);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_80113D20);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_80113D68);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_80114020);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_80114560);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_8011458C);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_80114760);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_801149F0);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_80114BBC);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_80114CA0);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_80114F68);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_801151A8);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_801152CC);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_8011568C);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_801157D0);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_801158FC);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_80115CC0);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_80116198);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_801162F4);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_80116810);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_801168A0);


s32 func_8011694C(void *arg0) {
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x38), s8 *, 4) = 2;
    func_80074590(0x37, 0x16, 0);
    return 1;
}

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_80116980);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_80116B9C);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_80116EE0);

extern s16 D_800BED82;
extern M2C_UNK D_80125160;
void func_80116FC8(void) {
    func_80075448(0xA, &D_80125160, 0x10, D_800BED82);
}

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_80116FFC);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_80117378);

INCLUDE_ASM("asm/a0d/nonmatchings/a0d", func_801173CC);

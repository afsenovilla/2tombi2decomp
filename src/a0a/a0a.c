#include "common.h"
#include "game.h"
#include "m2c.h"

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80109314);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_8010944C);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80109688);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_801097FC);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80109AE0);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80109C00);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80109F08);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_8010A0C8);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_8010A234);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_8010A3D8);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_8010A554);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_8010A788);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_8010A7D0);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_8010A824);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_8010A8A0);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_8010A988);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_8010AA94);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_8010AC84);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_8010B0FC);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_8010B338);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_8010B3DC);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_8010B42C);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_8010B474);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_8010B698);


void func_8010B824(void) {
}


void func_8010B82C(void) {
}

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_8010B834);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_8010B9AC);


void func_8010BAD4(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 4);
    switch (temp_v1) {                              /* irregular */
    case 0:
        M2C_FIELD(arg0, u8 *, 4) = 1U;
        func_8010B834(arg0, 0U);
        func_8010B9AC(0);
        func_80113708();
        func_800752B4(0);
        func_80075D24(0x1FFF);
        return;
    case 1:
        if (func_80026AD0(arg0) != 0) {
            func_8010B834(arg0, M2C_FIELD(arg0, u8 *, 3));
        }
        func_80026A68(arg0);
        func_80113724();
        func_8010B9AC(1);
        return;
    case 3:
        func_8007ADD0(arg0);
        /* fallthrough */
    case 2:
        return;
    }
}

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_8010BBB4);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_8010BDD8);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_8010BFA8);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", f_SelectNextEvilPigAttack);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", f_SelectEvilPigArenaTarget);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", f_UpdateEvilPigRelocationAttack);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", f_UpdateEvilPigRushAttack);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_8010D748);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", f_UpdateEvilPigHitAndCaptureState);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_8010E590);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_8010E7A4);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", f_UpdateEvilPigCenterEffectAttack);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_8010ECF0);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", f_UpdateEvilPigBattleActor);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", f_UpdateEvilPigBattleIntroduction);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_8010F97C);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_8010FD74);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_8011024C);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_801103F4);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80110698);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_801109CC);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80110A14);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80110CF8);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80111238);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80111264);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_801113A0);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80111564);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80111670);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_801117C8);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80111980);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80111B68);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80111D3C);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_8011212C);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80112244);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80112384);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_8011253C);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80112764);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80112990);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80112AA4);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80112C50);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80112DF4);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80112F0C);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_801130A0);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_801131DC);


void func_801136F8(void) {
}


void func_80113700(void) {
}

extern M2C_UNK D_80127974;
void func_80113708(void) {
    M2C_FIELD(&D_80127974, s8 *, 0) = 0;
    M2C_FIELD(&D_80127974, s8 *, 1) = 0;
    M2C_FIELD(&D_80127974, s8 *, 2) = 0;
    M2C_FIELD(&D_80127974, s8 *, 3) = 0;
}

extern M2C_UNK D_80127974;
void func_80113724(void) {
    if (M2C_FIELD(&D_80127974, u8 *, 0) == 0) {
        M2C_FIELD(&D_80127974, s16 *, 4) = 0;
        func_800310F4(0xB00, 0);
        M2C_FIELD(&D_80127974, u8 *, 0) = 1U;
    }
}

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80113768);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_8011384C);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80113904);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80113A20);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80113AC0);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80113B78);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80113C70);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80113D4C);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80113DDC);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80113EA4);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80113F84);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80114020);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_801140D0);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_801142EC);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80114630);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80114784);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_801149D8);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80114B38);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80114C6C);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80114D50);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80114DB0);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80114E64);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80115338);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80115418);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80115700);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80115958);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80115C24);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80115DF0);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80115FF4);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_801160C4);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80116194);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", f_CopyEvilPigCaptureDeformationVertices);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", f_UpdateEvilPigCaptureDeformation);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80116634);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80116874);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", f_UpdateEvilPigRobeRewardActor);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", f_MoveEvilPigCaptureActorTowardBoss);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80116E9C);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", f_UpdateEvilPigCaptureApproachSequence);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", f_UpdateEvilPigDefeatAndRewardSequence);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80117864);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_801179C0);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80117EC8);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80117F58);


s32 func_80118004(void *arg0) {
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x38), s8 *, 4) = 2;
    func_80074590(0x37, 0x16, 0);
    return 1;
}

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80118038);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80118158);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_801185FC);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80118754);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_801187E8);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_801188C0);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80118A5C);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80118C8C);


void func_80118CE0(s32 arg0) {
    s32 temp_s0;

    temp_s0 = arg0 + 0x2C;
    func_8003116C(0xB05, temp_s0, -0x1E);
    func_8003116C(0xB05, temp_s0, -0x1E);
    func_8003116C(0xB09, temp_s0, -0x28);
    func_8003116C(0xB0B, temp_s0, 0);
}

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80118D40);

extern s16 D_800BED82;
extern M2C_UNK D_801271F4;
void f_UpdateEvilPigBagOfferingSequence(void) {
    func_80075448(0xA, &D_801271F4, 0x10, D_800BED82);
}

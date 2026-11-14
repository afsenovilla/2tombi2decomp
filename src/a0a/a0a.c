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

extern s8 D_1F80027E[];
extern u8 D_800BFA1A;

void func_8010B338(void *arg0) {
    *((s8 *)D_1F80027E) = 1;
    func_8006F0E4();
    M2C_FIELD(arg0, s8 *, 1) = 1;
    func_80055D5C(arg0);
    M2C_FIELD(arg0, s16 *, 0x142) = 0;
    M2C_FIELD(arg0, s16 *, 0x58) = 0;
    func_80054198(arg0);
    func_80055284(arg0);
    func_80054D14(arg0, 2, 0);
    func_8003315C(arg0);
    if (!(D_800BFA1A & 1)) {
        func_80042354(1, 5);
        func_8001CF2C();
        M2C_FIELD(arg0, s8 *, 4) = 4;
    }
}

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

extern s8 D_1F800160[];
extern s8 D_1F800164[];
extern s8 D_1F800246[];
extern s8 D_1F80024C[];

void func_80116E9C(void *arg0) {
    M2C_UNK var_a0;
    void *temp_s1;

    temp_s1 = *((void **)D_1F80024C);
    if (*((u8 *)D_1F800246) == 0) {
        M2C_FIELD(arg0, u8 *, 5) = 0U;
        M2C_FIELD(arg0, s8 *, 6) = 0;
        M2C_FIELD(arg0, s8 *, 7) = 2;
        M2C_FIELD(arg0, s16 *, 0x64) = 0;
        M2C_FIELD(arg0, u16 *, 0x56) = (u16) M2C_FIELD(arg0, u16 *, 0x62);
    } else {
        M2C_FIELD(arg0, u16 *, 0x56) = func_800776F8((s16) (func_800782B0(arg0 + 0x2C, *((s16 *)D_1F800160), *((s16 *)D_1F800164)) - 0x400), (s16) M2C_FIELD(arg0, u16 *, 0x56), 0x80);
        M2C_FIELD(M2C_FIELD(arg0, void **, 0xC0), s16 *, 8) = func_800776F8(0, M2C_FIELD(M2C_FIELD(arg0, void **, 0xC0), s16 *, 8), 0x80);
        f_UpdateEvilPigCaptureDeformation(arg0);
        if (M2C_FIELD(arg0, u8 *, 0x29) != 0) {
            var_a0 = 0x88;
            if (M2C_FIELD(temp_s1, s16 *, 0x6E) == 1) {
                var_a0 = 0x89;
            }
            func_80074590(var_a0, 0, 0);
            M2C_FIELD(arg0, s8 *, 6) = 0;
            M2C_FIELD(arg0, s16 *, 0x64) = 0;
            M2C_FIELD(arg0, s8 *, 7) = 3;
            M2C_FIELD(arg0, u8 *, 5) = (u8) (M2C_FIELD(arg0, u8 *, 5) + 1);
        }
    }
    M2C_FIELD(arg0, s16 *, 0x32) = (s16) (M2C_FIELD(arg0, u16 *, 0x7C) + (func_80083E80(M2C_FIELD(arg0, s16 *, 0x60)) >> 4));
    M2C_FIELD(arg0, s16 *, 0x60) = (s16) (((u16) M2C_FIELD(arg0, s16 *, 0x60) + 0x40) & 0xFFF);
}

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

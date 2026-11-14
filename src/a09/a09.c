#include "common.h"
#include "game.h"
#include "m2c.h"

INCLUDE_ASM("asm/a09/nonmatchings/a09", func_80109078);

INCLUDE_ASM("asm/a09/nonmatchings/a09", func_801091CC);

INCLUDE_ASM("asm/a09/nonmatchings/a09", func_80109398);

INCLUDE_ASM("asm/a09/nonmatchings/a09", func_801095B8);

INCLUDE_ASM("asm/a09/nonmatchings/a09", func_80109708);

INCLUDE_ASM("asm/a09/nonmatchings/a09", func_80109790);

INCLUDE_ASM("asm/a09/nonmatchings/a09", f_UpdateEvilPigDoorTombaTransitionSequence);


void func_80109CA0(void *arg0) {
    func_8006F0E4();
    M2C_FIELD(arg0, s8 *, 1) = 1;
    func_80055D5C(arg0);
    M2C_FIELD(arg0, s16 *, 0x142) = 0;
    M2C_FIELD(arg0, s16 *, 0x58) = 0;
    func_80054198(arg0);
    func_80055284(arg0);
    func_80054D14(arg0, 2, 0);
    func_8003315C(arg0);
}

INCLUDE_ASM("asm/a09/nonmatchings/a09", func_80109D04);

INCLUDE_ASM("asm/a09/nonmatchings/a09", func_80109DF4);

extern u8 D_800BF816;
extern u8 D_800E806C;
extern s32 D_1F800184;
extern u8 D_800E7E80[];

void func_80109E54(void)
{
    u8 *p;

    D_800BF816 = 0;
    D_800E806C = 0;
    D_1F800184 = 0;
    p = D_800E7E80;
    p[5] = 0x24;
    p[7] = 0;
    p[6] = 0;
    func_80054198(p);
    p[0x16B] = 0;
}

INCLUDE_ASM("asm/a09/nonmatchings/a09", f_SpawnEvilPigDoorActorsFromPlacementTable);

INCLUDE_ASM("asm/a09/nonmatchings/a09", func_8010A060);

INCLUDE_ASM("asm/a09/nonmatchings/a09", func_8010A188);

INCLUDE_ASM("asm/a09/nonmatchings/a09", func_8010A228);

INCLUDE_ASM("asm/a09/nonmatchings/a09", f_UpdateEvilPigInteriorEntranceDoorSequence);

INCLUDE_ASM("asm/a09/nonmatchings/a09", func_8010A5D8);

INCLUDE_ASM("asm/a09/nonmatchings/a09", f_InitializeEvilPigGateModel);

INCLUDE_ASM("asm/a09/nonmatchings/a09", f_ConfigureEvilPigGateForCurrentArea);

INCLUDE_ASM("asm/a09/nonmatchings/a09", f_UpdateEvilPigGateOpeningSequence);

INCLUDE_ASM("asm/a09/nonmatchings/a09", func_8010AD9C);

INCLUDE_ASM("asm/a09/nonmatchings/a09", func_8010AFB4);

INCLUDE_ASM("asm/a09/nonmatchings/a09", func_8010B3A8);

INCLUDE_ASM("asm/a09/nonmatchings/a09", func_8010B4C8);

INCLUDE_ASM("asm/a09/nonmatchings/a09", func_8010B664);

INCLUDE_ASM("asm/a09/nonmatchings/a09", func_8010B8B4);

INCLUDE_ASM("asm/a09/nonmatchings/a09", func_8010B974);

INCLUDE_ASM("asm/a09/nonmatchings/a09", func_8010B9CC);

INCLUDE_ASM("asm/a09/nonmatchings/a09", func_8010BA24);

INCLUDE_ASM("asm/a09/nonmatchings/a09", func_8010BB20);

INCLUDE_ASM("asm/a09/nonmatchings/a09", func_8010BBFC);

INCLUDE_ASM("asm/a09/nonmatchings/a09", func_8010BC9C);

INCLUDE_ASM("asm/a09/nonmatchings/a09", f_StartOrWaitForIndexedEvilPigPlateEvent);

INCLUDE_ASM("asm/a09/nonmatchings/a09", f_UpdateRemainingEvilPigStatueArrivalSequence);

INCLUDE_ASM("asm/a09/nonmatchings/a09", func_8010C01C);

INCLUDE_ASM("asm/a09/nonmatchings/a09", f_UpdateEvilPigStatueActor);

INCLUDE_ASM("asm/a09/nonmatchings/a09", func_8010C588);

INCLUDE_ASM("asm/a09/nonmatchings/a09", func_8010C6B8);

INCLUDE_ASM("asm/a09/nonmatchings/a09", func_8010CAF8);

INCLUDE_ASM("asm/a09/nonmatchings/a09", func_8010CBB0);

INCLUDE_ASM("asm/a09/nonmatchings/a09", func_8010CCD8);

INCLUDE_ASM("asm/a09/nonmatchings/a09", func_8010CD68);

INCLUDE_ASM("asm/a09/nonmatchings/a09", func_8010CEC4);

INCLUDE_ASM("asm/a09/nonmatchings/a09", func_8010D0B0);

INCLUDE_ASM("asm/a09/nonmatchings/a09", func_8010D30C);

INCLUDE_ASM("asm/a09/nonmatchings/a09", func_8010D5D8);

INCLUDE_ASM("asm/a09/nonmatchings/a09", func_8010D7D4);

INCLUDE_ASM("asm/a09/nonmatchings/a09", func_8010D910);

INCLUDE_ASM("asm/a09/nonmatchings/a09", func_8010DE2C);

INCLUDE_ASM("asm/a09/nonmatchings/a09", func_8010DEE0);

INCLUDE_ASM("asm/a09/nonmatchings/a09", f_UpdateEvilPigInteriorEntranceDoorActor);

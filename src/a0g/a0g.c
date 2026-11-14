#include "common.h"
#include "game.h"
#include "m2c.h"

INCLUDE_ASM("asm/a0g/nonmatchings/a0g", func_80109180);

INCLUDE_ASM("asm/a0g/nonmatchings/a0g", func_80109378);

INCLUDE_ASM("asm/a0g/nonmatchings/a0g", func_8010959C);

INCLUDE_ASM("asm/a0g/nonmatchings/a0g", func_801096E0);

INCLUDE_ASM("asm/a0g/nonmatchings/a0g", func_8010978C);

INCLUDE_ASM("asm/a0g/nonmatchings/a0g", f_DispatchCourageTowerTombaContacts);

INCLUDE_ASM("asm/a0g/nonmatchings/a0g", func_80109CC8);

INCLUDE_ASM("asm/a0g/nonmatchings/a0g", func_80109D28);

INCLUDE_ASM("asm/a0g/nonmatchings/a0g", func_80109D98);

INCLUDE_ASM("asm/a0g/nonmatchings/a0g", func_80109E70);

INCLUDE_ASM("asm/a0g/nonmatchings/a0g", func_80109F34);

INCLUDE_ASM("asm/a0g/nonmatchings/a0g", func_8010A034);

INCLUDE_ASM("asm/a0g/nonmatchings/a0g", func_8010A134);

void func_8010A16C(void *arg0) {
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

INCLUDE_ASM("asm/a0g/nonmatchings/a0g", func_8010A1D0);

INCLUDE_ASM("asm/a0g/nonmatchings/a0g", func_8010A2B4);

INCLUDE_ASM("asm/a0g/nonmatchings/a0g", func_8010A314);

INCLUDE_ASM("asm/a0g/nonmatchings/a0g", func_8010A36C);

INCLUDE_ASM("asm/a0g/nonmatchings/a0g", func_8010A4F4);

INCLUDE_ASM("asm/a0g/nonmatchings/a0g", f_UpdateCourageTowerExitDoorSequence);

INCLUDE_ASM("asm/a0g/nonmatchings/a0g", f_UpdateCourageTowerLaughingCryingDoorSequence);

INCLUDE_ASM("asm/a0g/nonmatchings/a0g", func_8010AC00);

INCLUDE_ASM("asm/a0g/nonmatchings/a0g", func_8010ADC4);

INCLUDE_ASM("asm/a0g/nonmatchings/a0g", func_8010B08C);

INCLUDE_ASM("asm/a0g/nonmatchings/a0g", f_UpdateCourageTowerInteriorEntranceActor);

INCLUDE_ASM("asm/a0g/nonmatchings/a0g", func_8010B91C);

INCLUDE_ASM("asm/a0g/nonmatchings/a0g", func_8010B9E0);

extern u8 D_800BF916;
void func_8010BB58(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 4);
    switch (temp_v1) {                              /* irregular */
    case 0:
        M2C_FIELD(arg0, u8 *, 4) = 1U;
        func_8010B9E0(arg0, 0U);
        func_8004D8D8(0xD, 0);
        func_800752B4(0);
        func_80075D24(0x1FFF);
        return;
    case 1:
        if (func_80026AD0(arg0) != 0) {
            func_8010B9E0(arg0, M2C_FIELD(arg0, u8 *, 3));
        }
        if (D_800BF916 != 0xFF) {
            func_80040C00(0x62);
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

INCLUDE_ASM("asm/a0g/nonmatchings/a0g", func_8010BC40);

INCLUDE_ASM("asm/a0g/nonmatchings/a0g", func_8010BF28);

INCLUDE_ASM("asm/a0g/nonmatchings/a0g", func_8010C2A4);

INCLUDE_ASM("asm/a0g/nonmatchings/a0g", func_8010C3A4);

INCLUDE_ASM("asm/a0g/nonmatchings/a0g", func_8010C664);

INCLUDE_ASM("asm/a0g/nonmatchings/a0g", func_8010C9B4);

INCLUDE_ASM("asm/a0g/nonmatchings/a0g", func_8010C9FC);

INCLUDE_ASM("asm/a0g/nonmatchings/a0g", func_8010CCDC);

INCLUDE_ASM("asm/a0g/nonmatchings/a0g", func_8010D21C);

INCLUDE_ASM("asm/a0g/nonmatchings/a0g", f_PlayCourageTowerStreamedAudioSegment);

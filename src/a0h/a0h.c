#include "common.h"
#include "game.h"
#include "m2c.h"

INCLUDE_ASM("asm/a0h/nonmatchings/a0h", func_801090DC);

INCLUDE_ASM("asm/a0h/nonmatchings/a0h", func_801092D4);

INCLUDE_ASM("asm/a0h/nonmatchings/a0h", func_801094F8);

INCLUDE_ASM("asm/a0h/nonmatchings/a0h", func_8010963C);

INCLUDE_ASM("asm/a0h/nonmatchings/a0h", func_801096E8);

INCLUDE_ASM("asm/a0h/nonmatchings/a0h", f_DispatchStrengthTowerTombaContacts);

INCLUDE_ASM("asm/a0h/nonmatchings/a0h", func_80109CC4);

INCLUDE_ASM("asm/a0h/nonmatchings/a0h", func_80109D24);

INCLUDE_ASM("asm/a0h/nonmatchings/a0h", func_80109D94);

INCLUDE_ASM("asm/a0h/nonmatchings/a0h", func_80109E10);

INCLUDE_ASM("asm/a0h/nonmatchings/a0h", func_80109EE8);

INCLUDE_ASM("asm/a0h/nonmatchings/a0h", func_80109FAC);

INCLUDE_ASM("asm/a0h/nonmatchings/a0h", func_8010A0AC);

INCLUDE_ASM("asm/a0h/nonmatchings/a0h", func_8010A1AC);


void func_8010A1E4(void *arg0) {
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

INCLUDE_ASM("asm/a0h/nonmatchings/a0h", func_8010A248);

INCLUDE_ASM("asm/a0h/nonmatchings/a0h", func_8010A33C);

INCLUDE_ASM("asm/a0h/nonmatchings/a0h", func_8010A39C);

INCLUDE_ASM("asm/a0h/nonmatchings/a0h", f_UpdateStrengthTowerExitDoorSequence);

INCLUDE_ASM("asm/a0h/nonmatchings/a0h", func_8010A574);

INCLUDE_ASM("asm/a0h/nonmatchings/a0h", func_8010A854);

INCLUDE_ASM("asm/a0h/nonmatchings/a0h", func_8010A918);

INCLUDE_ASM("asm/a0h/nonmatchings/a0h", func_8010ABE8);

INCLUDE_ASM("asm/a0h/nonmatchings/a0h", func_8010ACF8);

extern u8 D_800BF917;
void func_8010AE70(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 4);
    switch (temp_v1) {                              /* irregular */
    case 0:
        M2C_FIELD(arg0, u8 *, 4) = 1U;
        func_8010ACF8(arg0, 0U);
        func_8004D8D8(0xE, 0);
        func_800752B4(0);
        func_80075D24(0x1FFF);
        return;
    case 1:
        if (func_80026AD0(arg0) != 0) {
            func_8010ACF8(arg0, M2C_FIELD(arg0, u8 *, 3));
        }
        if (D_800BF917 != 0xFF) {
            func_80040C00(0x63);
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

INCLUDE_ASM("asm/a0h/nonmatchings/a0h", func_8010AF58);

INCLUDE_ASM("asm/a0h/nonmatchings/a0h", func_8010B240);

INCLUDE_ASM("asm/a0h/nonmatchings/a0h", func_8010B5BC);

INCLUDE_ASM("asm/a0h/nonmatchings/a0h", func_8010B6BC);

INCLUDE_ASM("asm/a0h/nonmatchings/a0h", func_8010B960);

INCLUDE_ASM("asm/a0h/nonmatchings/a0h", func_8010BC94);

INCLUDE_ASM("asm/a0h/nonmatchings/a0h", func_8010BCDC);

INCLUDE_ASM("asm/a0h/nonmatchings/a0h", func_8010BFBC);

INCLUDE_ASM("asm/a0h/nonmatchings/a0h", func_8010C4FC);

INCLUDE_ASM("asm/a0h/nonmatchings/a0h", f_UpdateStrengthTowerInteriorEntranceActor);

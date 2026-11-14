#include "common.h"
#include "game.h"
#include "m2c.h"

INCLUDE_ASM("asm/a0i/nonmatchings/a0i", func_801090F0);

INCLUDE_ASM("asm/a0i/nonmatchings/a0i", func_801092E8);

INCLUDE_ASM("asm/a0i/nonmatchings/a0i", func_8010949C);

INCLUDE_ASM("asm/a0i/nonmatchings/a0i", f_DispatchWisdomTowerTombaContacts);

INCLUDE_ASM("asm/a0i/nonmatchings/a0i", func_80109AD8);

INCLUDE_ASM("asm/a0i/nonmatchings/a0i", func_80109B38);

INCLUDE_ASM("asm/a0i/nonmatchings/a0i", func_80109BA8);

INCLUDE_ASM("asm/a0i/nonmatchings/a0i", func_80109C6C);

INCLUDE_ASM("asm/a0i/nonmatchings/a0i", func_80109D6C);

INCLUDE_ASM("asm/a0i/nonmatchings/a0i", func_80109E6C);

INCLUDE_ASM("asm/a0i/nonmatchings/a0i", func_80109F44);

INCLUDE_ASM("asm/a0i/nonmatchings/a0i", f_UpdateTombaWisdomTowerRockAction);

void func_8010A554(void *arg0) {
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

INCLUDE_ASM("asm/a0i/nonmatchings/a0i", func_8010A5B8);

INCLUDE_ASM("asm/a0i/nonmatchings/a0i", func_8010A788);

INCLUDE_ASM("asm/a0i/nonmatchings/a0i", func_8010A7E8);

INCLUDE_ASM("asm/a0i/nonmatchings/a0i", f_UpdateWisdomTowerExitDoorSequence);

INCLUDE_ASM("asm/a0i/nonmatchings/a0i", func_8010A9C0);

INCLUDE_ASM("asm/a0i/nonmatchings/a0i", func_8010ACA0);

INCLUDE_ASM("asm/a0i/nonmatchings/a0i", func_8010AD64);

INCLUDE_ASM("asm/a0i/nonmatchings/a0i", func_8010B06C);

INCLUDE_ASM("asm/a0i/nonmatchings/a0i", func_8010B17C);

extern u8 D_800BF918;
void func_8010B2F4(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 4);
    switch (temp_v1) {                              /* irregular */
    case 0:
        M2C_FIELD(arg0, u8 *, 4) = 1U;
        func_8010B17C(arg0, 0U);
        func_8004D8D8(0xF, 0);
        func_800752B4(0);
        func_80075D24(0x1FFF);
        return;
    case 1:
        if (func_80026AD0(arg0) != 0) {
            func_8010B17C(arg0, M2C_FIELD(arg0, u8 *, 3));
        }
        if (D_800BF918 != 0xFF) {
            func_80040C00(0x64);
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

INCLUDE_ASM("asm/a0i/nonmatchings/a0i", func_8010B3DC);

INCLUDE_ASM("asm/a0i/nonmatchings/a0i", func_8010B6C4);

INCLUDE_ASM("asm/a0i/nonmatchings/a0i", func_8010BA40);

INCLUDE_ASM("asm/a0i/nonmatchings/a0i", func_8010BB40);

INCLUDE_ASM("asm/a0i/nonmatchings/a0i", func_8010BDE4);

INCLUDE_ASM("asm/a0i/nonmatchings/a0i", func_8010C118);

INCLUDE_ASM("asm/a0i/nonmatchings/a0i", func_8010C160);

INCLUDE_ASM("asm/a0i/nonmatchings/a0i", func_8010C440);

INCLUDE_ASM("asm/a0i/nonmatchings/a0i", func_8010C980);

INCLUDE_ASM("asm/a0i/nonmatchings/a0i", f_UpdateWisdomTowerInteriorEntranceActor);

#include "common.h"
#include "game.h"
#include "m2c.h"

INCLUDE_ASM("asm/game/nonmatchings/game", func_8010637C);

INCLUDE_ASM("asm/game/nonmatchings/game", func_80106478);

INCLUDE_ASM("asm/game/nonmatchings/game", func_80106A24);

INCLUDE_ASM("asm/game/nonmatchings/game", func_80106B98);

INCLUDE_ASM("asm/game/nonmatchings/game", func_801070B4);

INCLUDE_ASM("asm/game/nonmatchings/game", func_80107230);

INCLUDE_ASM("asm/game/nonmatchings/game", func_8010766C);

INCLUDE_ASM("asm/game/nonmatchings/game", func_80107790);

INCLUDE_ASM("asm/game/nonmatchings/game", func_801079AC);

INCLUDE_ASM("asm/game/nonmatchings/game", func_80107AFC);

INCLUDE_ASM("asm/game/nonmatchings/game", func_80107D3C);

INCLUDE_ASM("asm/game/nonmatchings/game", func_80107E20);

INCLUDE_ASM("asm/game/nonmatchings/game", func_80107F3C);

INCLUDE_ASM("asm/game/nonmatchings/game", func_8010810C);

INCLUDE_ASM("asm/game/nonmatchings/game", func_801084F8);

INCLUDE_ASM("asm/game/nonmatchings/game", func_80108624);

s32 func_801086E0(void) {
    void *temp_v0;

    temp_v0 = *(void **)0x1F800138;
    M2C_FIELD(temp_v0, s16 *, 0x48) = 2;
    M2C_FIELD(temp_v0, s16 *, 0x4A) = 0;
    M2C_FIELD(temp_v0, s16 *, 0x4C) = 0;
    M2C_FIELD(temp_v0, s8 *, 0x69) = 0;
    func_8007A8E0();
    return func_8007B38C();
}

INCLUDE_ASM("asm/game/nonmatchings/game", func_80108720);

INCLUDE_ASM("asm/game/nonmatchings/game", func_80108784);

INCLUDE_ASM("asm/game/nonmatchings/game", func_8010882C);

INCLUDE_ASM("asm/game/nonmatchings/game", func_801088D8);

INCLUDE_ASM("asm/game/nonmatchings/game", func_801089C4);

INCLUDE_ASM("asm/game/nonmatchings/game", func_80108A60);

INCLUDE_ASM("asm/game/nonmatchings/game", func_80108B0C);

INCLUDE_ASM("asm/game/nonmatchings/game", func_80108BE4);

INCLUDE_ASM("asm/game/nonmatchings/game", func_80108CAC);

s32 func_80108D64(void) {
    void *temp_v0;

    temp_v0 = *(void **)0x1F800138;
    M2C_FIELD(temp_v0, s16 *, 0x4A) = 3;
    M2C_FIELD(temp_v0, s16 *, 0x4C) = 0;
    M2C_FIELD(temp_v0, s16 *, 0x4E) = 0;
    return (s32) temp_v0;
}

INCLUDE_ASM("asm/game/nonmatchings/game", func_80108D80);

INCLUDE_ASM("asm/game/nonmatchings/game", func_80108DA4);

INCLUDE_ASM("asm/game/nonmatchings/game", func_80108DF4);

INCLUDE_ASM("asm/game/nonmatchings/game", func_80108E58);

INCLUDE_ASM("asm/game/nonmatchings/game", func_80108EBC);

extern s8 D_1F800136[];
extern s8 D_1F800138[];
extern s8 D_800BF819;

s32 func_80108F24(void) {
    M2C_FIELD(*((void **)D_1F800138), s8 *, 0x6B) = 0;
    *((s8 *)D_1F800136) = 0;
    D_800BF819 = 8;
    return func_80050970();
}

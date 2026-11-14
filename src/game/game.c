#include "common.h"
#include "game.h"
#include "m2c.h"

INCLUDE_ASM("asm/game/nonmatchings/game", func_80106374);

INCLUDE_ASM("asm/game/nonmatchings/game", func_80106478);

INCLUDE_ASM("asm/game/nonmatchings/game", func_80106A1C);

INCLUDE_ASM("asm/game/nonmatchings/game", func_80106A24);

INCLUDE_ASM("asm/game/nonmatchings/game", func_80106B90);

INCLUDE_ASM("asm/game/nonmatchings/game", func_80106B98);

INCLUDE_ASM("asm/game/nonmatchings/game", func_801070AC);

INCLUDE_ASM("asm/game/nonmatchings/game", func_801070B4);

INCLUDE_ASM("asm/game/nonmatchings/game", func_80107228);

INCLUDE_ASM("asm/game/nonmatchings/game", func_80107230);

INCLUDE_ASM("asm/game/nonmatchings/game", func_80107664);

INCLUDE_ASM("asm/game/nonmatchings/game", func_8010766C);

INCLUDE_ASM("asm/game/nonmatchings/game", func_80107788);

INCLUDE_ASM("asm/game/nonmatchings/game", func_80107790);

INCLUDE_ASM("asm/game/nonmatchings/game", func_801079A4);

INCLUDE_ASM("asm/game/nonmatchings/game", func_801079AC);

INCLUDE_ASM("asm/game/nonmatchings/game", func_80107AF4);

INCLUDE_ASM("asm/game/nonmatchings/game", func_80107AFC);

INCLUDE_ASM("asm/game/nonmatchings/game", func_80107D34);

INCLUDE_ASM("asm/game/nonmatchings/game", func_80107D3C);

INCLUDE_ASM("asm/game/nonmatchings/game", func_80107E18);

INCLUDE_ASM("asm/game/nonmatchings/game", func_80107E20);

INCLUDE_ASM("asm/game/nonmatchings/game", func_80107F34);

INCLUDE_ASM("asm/game/nonmatchings/game", func_80107F3C);

INCLUDE_ASM("asm/game/nonmatchings/game", func_80108104);

INCLUDE_ASM("asm/game/nonmatchings/game", func_8010810C);

INCLUDE_ASM("asm/game/nonmatchings/game", func_801084F0);

INCLUDE_ASM("asm/game/nonmatchings/game", func_801084F8);

INCLUDE_ASM("asm/game/nonmatchings/game", func_8010861C);

INCLUDE_ASM("asm/game/nonmatchings/game", func_80108624);

INCLUDE_ASM("asm/game/nonmatchings/game", func_801086D8);

INCLUDE_ASM("asm/game/nonmatchings/game", func_801086E0);

INCLUDE_ASM("asm/game/nonmatchings/game", func_80108718);

INCLUDE_ASM("asm/game/nonmatchings/game", func_80108720);

INCLUDE_ASM("asm/game/nonmatchings/game", func_8010877C);

INCLUDE_ASM("asm/game/nonmatchings/game", func_80108784);

INCLUDE_ASM("asm/game/nonmatchings/game", func_80108824);

INCLUDE_ASM("asm/game/nonmatchings/game", func_8010882C);

INCLUDE_ASM("asm/game/nonmatchings/game", func_801088D0);

INCLUDE_ASM("asm/game/nonmatchings/game", func_801088D8);

INCLUDE_ASM("asm/game/nonmatchings/game", func_801089BC);

INCLUDE_ASM("asm/game/nonmatchings/game", func_801089C4);

INCLUDE_ASM("asm/game/nonmatchings/game", func_80108A58);

INCLUDE_ASM("asm/game/nonmatchings/game", func_80108A60);

INCLUDE_ASM("asm/game/nonmatchings/game", func_80108B04);

INCLUDE_ASM("asm/game/nonmatchings/game", func_80108B0C);

INCLUDE_ASM("asm/game/nonmatchings/game", func_80108BDC);

INCLUDE_ASM("asm/game/nonmatchings/game", func_80108BE4);

INCLUDE_ASM("asm/game/nonmatchings/game", func_80108CA4);

INCLUDE_ASM("asm/game/nonmatchings/game", func_80108CAC);


void func_80108D5C(void) {
    void *temp_v0;

    temp_v0 = *(void **)0x1F800138;
    M2C_FIELD(temp_v0, s16 *, 0x4A) = 3;
    M2C_FIELD(temp_v0, s16 *, 0x4C) = 0;
    M2C_FIELD(temp_v0, s16 *, 0x4E) = 0;
}

extern s8 D_1F800138[];

void func_80108D78(void) {
    void *temp_v1;

    temp_v1 = *((void **)D_1F800138);
    M2C_FIELD(temp_v1, s16 *, 0x4A) = 1;
    M2C_FIELD(temp_v1, s16 *, 0x4C) = 2;
    M2C_FIELD(temp_v1, s16 *, 0x4E) = 3;
}

extern s8 D_1F800138[];
extern s8 D_1F800236[];

void func_80108D9C(void) {
    void *temp_v1;

    if ((u8) *((u8 *)D_1F800236) >= 5U) {
        func_80050894(0);
    }
    temp_v1 = *((void **)D_1F800138);
    M2C_FIELD(temp_v1, s16 *, 0x4A) = 1;
    M2C_FIELD(temp_v1, s16 *, 0x4C) = 2;
    M2C_FIELD(temp_v1, s16 *, 0x4E) = 6;
}

extern s8 D_1F800138[];

void func_80108DEC(void) {
    void *temp_v1;

    func_8007B18C();
    func_800796DC();
    func_800263E8();
    func_80072A78();
    func_80075240();
    func_800783DC();
    func_80078610();
    temp_v1 = *((void **)D_1F800138);
    M2C_FIELD(temp_v1, s16 *, 0x4E) = 1;
    M2C_FIELD(temp_v1, s8 *, 0x6B) = 0;
}

extern s8 D_1F800138[];

void func_80108E50(void) {
    s32 temp_a0;
    void *temp_v1;

    temp_a0 = (M2C_FIELD(*((void **)D_1F800138), u8 *, 0x6B) * 8) & 0xFF;
    func_8007E9C8((temp_a0 << 0x10) | (temp_a0 << 8) | temp_a0, 0, 4);
    temp_v1 = *((void **)D_1F800138);
    M2C_FIELD(temp_v1, u8 *, 0x6B) = (u8) (M2C_FIELD(temp_v1, u8 *, 0x6B) - 1);
}

extern s8 D_1F800138[];

void func_80108EB4(void) {
    s32 temp_a0;
    void *temp_v1;

    temp_a0 = -(M2C_FIELD(*((void **)D_1F800138), u8 *, 0x6B) * 8) & 0xFF;
    func_8007E9C8((temp_a0 << 0x10) | (temp_a0 << 8) | temp_a0, 1, 4);
    temp_v1 = *((void **)D_1F800138);
    M2C_FIELD(temp_v1, u8 *, 0x6B) = (u8) (M2C_FIELD(temp_v1, u8 *, 0x6B) - 1);
}

extern s8 D_1F800136[];
extern s8 D_1F800138[];
extern s8 D_800BF819;

void func_80108F1C(void) {
    M2C_FIELD(*((void **)D_1F800138), s8 *, 0x6B) = 0;
    *((s8 *)D_1F800136) = 0;
    D_800BF819 = 8;
    func_80050970();
}

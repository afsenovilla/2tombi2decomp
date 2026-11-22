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

extern u8 *D_1F800138_5432;
extern u8 D_1F800136_8901;
extern u8 D_800BF819_cf3c;

void func_80108624(void)
{
    u8 *p = D_1F800138_5432;
    s32 s = *(u16 *)(p + 0x50);

    switch (s) {
    case 0:
    case 1:
        *(s16 *)(p + 0x50) = s + 1;
        break;
    case 2:
        *(s16 *)(p + 0x50) = 3;
        func_80050894(0);
        D_1F800136_8901 = 2;
        func_8007AC6C();
        break;
    case 3:
        if (func_800346BC() != 0) {
            *(s16 *)(D_1F800138_5432 + 0x50) = 0;
            D_1F800138_5432[0x6B] = 0;
            D_1F800136_8901 = 0;
            D_800BF819_cf3c = 8;
            func_80050970();
        }
        break;
    }
}

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

extern u8 D_1F8001FF;
extern s16 D_1F800278;
extern u8 D_1F800206;
extern u8 D_1F800236;
extern u8 D_1F800234;

void func_80108720(void)
{
    u8 *p = D_1F800138_5432;

    *(s16 *)(p + 0x48) = 2;
    *(s16 *)(p + 0x4A) = 1;
    *(s16 *)(p + 0x4C) = 0;
    p[0x69] = 0;
    D_1F8001FF = 0xFF;
    D_1F800278 = 0;
    func_8007B3F4();
    D_1F800206 = 0;
    D_1F800236 = 0;
    D_1F800234 = 0;
}

void func_80108784(void)
{
    switch (*(u16 *)(D_1F800138_5432 + 0x4A)) {
    case 0:
        func_8010882C();
        break;
    case 1:
        func_801088D8();
        break;
    case 2:
        func_80106478();
        break;
    case 3:
        func_80106A24();
        break;
    case 4:
        func_801089C4();
        break;
    case 5:
        func_80108A60();
        break;
    }
}

void func_8010882C(void)
{
    u8 pad[0x10];
    u8 *p = D_1F800138_5432;

    switch (*(u16 *)(p + 0x4C)) {
    case 0:
        switch (*(u16 *)(p + 0x4E)) {
        case 0:
            func_8005082C(0, 0, 0);
            p = D_1F800138_5432;
            *(s16 *)(p + 0x50) = 0;
            (*(s16 *)(p + 0x4E))++;
            break;
        case 1:
            func_80109450();
            break;
        }
        break;
    case 1:
        *(s16 *)(p + 0x4C) = 0;
        (*(s16 *)(p + 0x4A))++;
        break;
    }
}

INCLUDE_ASM("asm/game/nonmatchings/game", func_801088D8);

void func_801089C4(void)
{
    switch (*(u16 *)(D_1F800138_5432 + 0x4C)) {
    case 0:
        func_80074BC4();
        (*(s16 *)(D_1F800138_5432 + 0x4C))++;
        break;
    case 1:
        D_1F800138_5432[0x69] = 0;
        D_1F800138_5432[0x6A] = 0;
        D_1F800138_5432[0x6B] = 0;
        *(s16 *)(D_1F800138_5432 + 0x4A) = 0;
        *(s16 *)(D_1F800138_5432 + 0x4C) = 0;
        *(s16 *)(D_1F800138_5432 + 0x4E) = 0;
        func_80052078(1);
        break;
    }
}

void func_80108A60(void)
{
    u8 *p;

    switch (*(u16 *)(D_1F800138_5432 + 0x4C)) {
    case 0:
    case 9:
        p = D_1F800138_5432;
        *(s16 *)(p + 0x48) = 2;
        *(s16 *)(p + 0x4A) = 1;
        *(s16 *)(p + 0x4C) = 0;
        *(s16 *)(p + 0x4E) = 0;
        break;
    case 1:
    case 2:
    case 3:
    case 4:
        func_80107AFC();
        break;
    case 7:
        func_80107E20();
        break;
    case 5:
    case 6:
        func_80107D3C();
        break;
    case 8:
        func_80107F3C();
        break;
    }
}

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


void func_80108D80(void)
{
    u8 *p = D_1F800138_5432;

    *(s16 *)(p + 0x4A) = 1;
    *(s16 *)(p + 0x4C) = 2;
    *(s16 *)(p + 0x4E) = 3;
}


void func_80108DA4(void)
{
    u8 *p;

    if (D_1F800236 >= 5) {
        func_80050894(0);
    }
    p = D_1F800138_5432;
    *(s16 *)(p + 0x4A) = 1;
    *(s16 *)(p + 0x4C) = 2;
    *(s16 *)(p + 0x4E) = 6;
}

void func_80108DF4(void)
{
    u8 *p;

    func_8007B18C();
    func_800796DC();
    func_800263E8();
    func_80072A78();
    func_80075240();
    func_800783DC();
    func_80078610();
    p = D_1F800138_5432;
    *(s16 *)(p + 0x4E) = 1;
    p[0x6B] = 0;
}

void func_80108E58(void)
{
    u8 c = D_1F800138_5432[0x6B] * 8;

    func_8007E9C8((c << 16) | (c << 8) | c, 0, 4);
    D_1F800138_5432[0x6B]--;
}

void func_80108EBC(void)
{
    u8 c = -(D_1F800138_5432[0x6B] * 8);

    func_8007E9C8((c << 16) | (c << 8) | c, 1, 4);
    D_1F800138_5432[0x6B]--;
}

extern s8 D_1F800136[];
extern s8 D_1F800138[];
extern s8 D_800BF819;

s32 func_80108F24(void) {
    M2C_FIELD(*((void **)D_1F800138), s8 *, 0x6B) = 0;
    *((s8 *)D_1F800136) = 0;
    D_800BF819 = 8;
    return func_80050970();
}

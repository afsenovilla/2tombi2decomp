#include "common.h"
#include "game.h"
#include "m2c.h"

INCLUDE_ASM("asm/a0e/nonmatchings/a0e", func_80109308);

INCLUDE_ASM("asm/a0e/nonmatchings/a0e", func_80109440);

INCLUDE_ASM("asm/a0e/nonmatchings/a0e", func_8010967C);

INCLUDE_ASM("asm/a0e/nonmatchings/a0e", func_80109870);

INCLUDE_ASM("asm/a0e/nonmatchings/a0e", func_80109B30);

INCLUDE_ASM("asm/a0e/nonmatchings/a0e", func_80109CEC);

INCLUDE_ASM("asm/a0e/nonmatchings/a0e", func_80109DB8);

INCLUDE_ASM("asm/a0e/nonmatchings/a0e", func_80109F44);

INCLUDE_ASM("asm/a0e/nonmatchings/a0e", func_8010A0C0);

INCLUDE_ASM("asm/a0e/nonmatchings/a0e", func_8010A1D4);

void func_8010A3DC(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x181) == 0) {
        if (M2C_FIELD(arg0, u8 *, 5) == 6) {
            M2C_FIELD(arg0, s16 *, 0x6A) = 0;
            M2C_FIELD(arg0, u8 *, 5) = 0x32U;
            M2C_FIELD(arg0, u8 *, 0x149) = (u8) ((M2C_FIELD(arg0, u8 *, 0x149) & 1) | 2);
        } else {
            M2C_FIELD(arg0, u8 *, 5) = 0x1DU;
            M2C_FIELD(arg0, s8 *, 6) = 0;
        }
        M2C_FIELD(arg0, s8 *, 4) = 1;
        M2C_FIELD(arg0, s8 *, 7) = 0;
        if (M2C_FIELD(arg0, u8 *, 0x144) == 1) {
            M2C_FIELD(arg0, u8 *, 0x144) = 0U;
        }
    }
}

INCLUDE_ASM("asm/a0e/nonmatchings/a0e", func_8010A448);

void func_8010A49C(void) {
    if (*(u8 *)0x1F800137 == 0) {
        func_8010967C();
    }
}

INCLUDE_ASM("asm/a0e/nonmatchings/a0e", func_8010A4C8);

INCLUDE_ASM("asm/a0e/nonmatchings/a0e", func_8010A520);

INCLUDE_ASM("asm/a0e/nonmatchings/a0e", func_8010A59C);

s32 func_8010A660(void) {
    return 0;
}

INCLUDE_ASM("asm/a0e/nonmatchings/a0e", func_8010A668);

INCLUDE_ASM("asm/a0e/nonmatchings/a0e", func_8010AB24);

INCLUDE_ASM("asm/a0e/nonmatchings/a0e", func_8010AF4C);

INCLUDE_ASM("asm/a0e/nonmatchings/a0e", func_8010B09C);

INCLUDE_ASM("asm/a0e/nonmatchings/a0e", func_8010B238);

void func_8010B3E8(void) {
    func_8010AB24();
}

INCLUDE_ASM("asm/a0e/nonmatchings/a0e", func_8010B408);

INCLUDE_ASM("asm/a0e/nonmatchings/a0e", func_8010B450);

INCLUDE_ASM("asm/a0e/nonmatchings/a0e", func_8010B4F4);

INCLUDE_ASM("asm/a0e/nonmatchings/a0e", func_8010B568);

INCLUDE_ASM("asm/a0e/nonmatchings/a0e", func_8010B78C);

void func_8010BCB8(void) {
}

void func_8010BCC0(void) {
}

INCLUDE_ASM("asm/a0e/nonmatchings/a0e", func_8010BCC8);

INCLUDE_ASM("asm/a0e/nonmatchings/a0e", func_8010BD38);

INCLUDE_ASM("asm/a0e/nonmatchings/a0e", func_8010BEB0);

void func_8010BFD0(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 4);
    switch (temp_v1) {                              /* irregular */
    case 0:
        M2C_FIELD(arg0, u8 *, 4) = 1U;
        func_8010BD38(arg0, 0U);
        func_8010BEB0(0);
        func_8011382C();
        func_80031220(0xF03, 0, 0);
        func_800752B4(0);
        func_80075D24(0x1FFF);
        return;
    case 1:
        if (func_80026AD0(arg0) != 0) {
            func_8010BD38(arg0, M2C_FIELD(arg0, u8 *, 3));
        }
        func_80026A68(arg0);
        func_8010BEB0(1);
        return;
    case 3:
        func_8007ADD0(arg0);
        /* fallthrough */
    case 2:
        return;
    }
}

INCLUDE_ASM("asm/a0e/nonmatchings/a0e", func_8010C0B8);

INCLUDE_ASM("asm/a0e/nonmatchings/a0e", func_8010C2DC);

INCLUDE_ASM("asm/a0e/nonmatchings/a0e", func_8010C4AC);

INCLUDE_ASM("asm/a0e/nonmatchings/a0e", func_8010C598);

INCLUDE_ASM("asm/a0e/nonmatchings/a0e", func_8010C6A8);

INCLUDE_ASM("asm/a0e/nonmatchings/a0e", func_8010CD54);

INCLUDE_ASM("asm/a0e/nonmatchings/a0e", func_8010D3E8);

INCLUDE_ASM("asm/a0e/nonmatchings/a0e", func_8010DC4C);

INCLUDE_ASM("asm/a0e/nonmatchings/a0e", func_8010DD90);

INCLUDE_ASM("asm/a0e/nonmatchings/a0e", func_8010EA94);

INCLUDE_ASM("asm/a0e/nonmatchings/a0e", func_8010ECA8);

INCLUDE_ASM("asm/a0e/nonmatchings/a0e", f_UpdateWaterEvilPigProjectileAttack);

INCLUDE_ASM("asm/a0e/nonmatchings/a0e", f_UpdateWaterEvilPigSpinningLeapAttack);

INCLUDE_ASM("asm/a0e/nonmatchings/a0e", func_8010F9B4);

INCLUDE_ASM("asm/a0e/nonmatchings/a0e", func_8010FE74);

INCLUDE_ASM("asm/a0e/nonmatchings/a0e", func_801100B0);

void func_80110128(void) {
}

INCLUDE_ASM("asm/a0e/nonmatchings/a0e", func_80110130);

INCLUDE_ASM("asm/a0e/nonmatchings/a0e", func_80110268);

INCLUDE_ASM("asm/a0e/nonmatchings/a0e", func_801104D0);

INCLUDE_ASM("asm/a0e/nonmatchings/a0e", func_80110CA4);

INCLUDE_ASM("asm/a0e/nonmatchings/a0e", func_8011141C);

INCLUDE_ASM("asm/a0e/nonmatchings/a0e", func_80111548);

INCLUDE_ASM("asm/a0e/nonmatchings/a0e", func_801117CC);

INCLUDE_ASM("asm/a0e/nonmatchings/a0e", func_80111CA8);

INCLUDE_ASM("asm/a0e/nonmatchings/a0e", func_80111E14);

INCLUDE_ASM("asm/a0e/nonmatchings/a0e", func_80111FD8);

INCLUDE_ASM("asm/a0e/nonmatchings/a0e", func_80112260);

INCLUDE_ASM("asm/a0e/nonmatchings/a0e", func_80112400);

INCLUDE_ASM("asm/a0e/nonmatchings/a0e", func_80112600);

INCLUDE_ASM("asm/a0e/nonmatchings/a0e", func_8011282C);

INCLUDE_ASM("asm/a0e/nonmatchings/a0e", func_80112940);

INCLUDE_ASM("asm/a0e/nonmatchings/a0e", func_80112AEC);

INCLUDE_ASM("asm/a0e/nonmatchings/a0e", func_80112C90);

INCLUDE_ASM("asm/a0e/nonmatchings/a0e", func_80112DA8);

INCLUDE_ASM("asm/a0e/nonmatchings/a0e", func_80112F3C);

INCLUDE_ASM("asm/a0e/nonmatchings/a0e", func_80113078);

INCLUDE_ASM("asm/a0e/nonmatchings/a0e", func_80113594);

INCLUDE_ASM("asm/a0e/nonmatchings/a0e", func_8011369C);

INCLUDE_ASM("asm/a0e/nonmatchings/a0e", func_80113754);

INCLUDE_ASM("asm/a0e/nonmatchings/a0e", func_8011382C);

INCLUDE_ASM("asm/a0e/nonmatchings/a0e", func_801138FC);

extern M2C_UNK D_80126C0C;
extern M2C_UNK D_80126E0C;
extern M2C_UNK D_80126F0C;
void func_801139B4(void) {
    func_80029664(&D_80126C0C, 0x3E, &D_80126E0C, &D_80126F0C);
}

INCLUDE_ASM("asm/a0e/nonmatchings/a0e", func_801139EC);

INCLUDE_ASM("asm/a0e/nonmatchings/a0e", func_80113A3C);

INCLUDE_ASM("asm/a0e/nonmatchings/a0e", func_80113AEC);

INCLUDE_ASM("asm/a0e/nonmatchings/a0e", func_80113DE0);

INCLUDE_ASM("asm/a0e/nonmatchings/a0e", func_80114178);

INCLUDE_ASM("asm/a0e/nonmatchings/a0e", func_80114320);

INCLUDE_ASM("asm/a0e/nonmatchings/a0e", func_80114458);

INCLUDE_ASM("asm/a0e/nonmatchings/a0e", func_801146FC);

INCLUDE_ASM("asm/a0e/nonmatchings/a0e", func_80114A30);

INCLUDE_ASM("asm/a0e/nonmatchings/a0e", func_80114A78);

INCLUDE_ASM("asm/a0e/nonmatchings/a0e", func_80114D30);

INCLUDE_ASM("asm/a0e/nonmatchings/a0e", func_80115270);

INCLUDE_ASM("asm/a0e/nonmatchings/a0e", func_8011529C);

INCLUDE_ASM("asm/a0e/nonmatchings/a0e", func_80115610);

INCLUDE_ASM("asm/a0e/nonmatchings/a0e", func_801156F4);

INCLUDE_ASM("asm/a0e/nonmatchings/a0e", func_801159BC);

INCLUDE_ASM("asm/a0e/nonmatchings/a0e", func_80115BFC);

INCLUDE_ASM("asm/a0e/nonmatchings/a0e", func_80115D20);

INCLUDE_ASM("asm/a0e/nonmatchings/a0e", func_801160E0);

INCLUDE_ASM("asm/a0e/nonmatchings/a0e", func_80116224);

INCLUDE_ASM("asm/a0e/nonmatchings/a0e", func_80116350);

INCLUDE_ASM("asm/a0e/nonmatchings/a0e", func_80116714);

INCLUDE_ASM("asm/a0e/nonmatchings/a0e", func_80116BEC);

INCLUDE_ASM("asm/a0e/nonmatchings/a0e", func_80116D48);

INCLUDE_ASM("asm/a0e/nonmatchings/a0e", func_80117254);

INCLUDE_ASM("asm/a0e/nonmatchings/a0e", func_801172E4);

s32 func_80117390(void *arg0) {
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x38), s8 *, 4) = 2;
    func_80074590(0x37, 0x16, 0);
    return 1;
}

INCLUDE_ASM("asm/a0e/nonmatchings/a0e", func_801173C4);

extern s16 D_800BED82;
extern M2C_UNK D_80125474;
void func_801174AC(void) {
    func_80075448(0xA, &D_80125474, 0x10, D_800BED82);
}

INCLUDE_ASM("asm/a0e/nonmatchings/a0e", f_UpdateWaterProjectileTerrainContact);

INCLUDE_ASM("asm/a0e/nonmatchings/a0e", func_80117600);

INCLUDE_ASM("asm/a0e/nonmatchings/a0e", func_80117960);

INCLUDE_ASM("asm/a0e/nonmatchings/a0e", func_80117ADC);

INCLUDE_ASM("asm/a0e/nonmatchings/a0e", func_80117BE0);

u8 func_80117C78(void *arg0) {
    s16 temp_s0;
    s32 temp_lo;
    s32 temp_s2;

    if (M2C_FIELD(arg0, u8 *, 0x5F) == 0) {
        temp_s0 = M2C_FIELD(arg0, s16 *, 0x60);
        temp_s2 = func_80083F50(temp_s0) * M2C_FIELD(arg0, s16 *, 0x44);
        temp_lo = -func_80083E80(temp_s0) * M2C_FIELD(arg0, s16 *, 0x44);
        M2C_FIELD(arg0, s32 *, 0x2C) = (s32) (M2C_FIELD(arg0, s32 *, 0x2C) + temp_s2);
        M2C_FIELD(arg0, s32 *, 0x34) = (s32) (M2C_FIELD(arg0, s32 *, 0x34) + temp_lo);
    }
    M2C_FIELD(arg0, s32 *, 0x30) = (s32) (M2C_FIELD(arg0, s32 *, 0x30) + (M2C_FIELD(arg0, s16 *, 0x4A) << 0xC));
    return M2C_FIELD(arg0, u8 *, 0x29);
}

INCLUDE_ASM("asm/a0e/nonmatchings/a0e", func_80117D1C);

INCLUDE_ASM("asm/a0e/nonmatchings/a0e", f_SpawnWaterEvilPigSprayActor);

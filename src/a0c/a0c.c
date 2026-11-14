#include "common.h"
#include "game.h"
#include "m2c.h"

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_801092D4);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_8010940C);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_80109648);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_801097BC);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_80109AA0);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_80109E04);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_8010A138);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_8010A55C);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_8010A870);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_8010A9A4);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_8010AB14);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_8010AD5C);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_8010AFF8);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_8010B174);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_8010B36C);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_8010B558);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_8010B888);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_8010BA30);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_8010BAA4);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_8010BAFC);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_8010BB20);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_8010BB44);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_8010BBB0);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_8010BC00);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_8010BC58);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_8010BCA4);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_8010BCFC);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_8010BD2C);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_8010BE10);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_8010BF40);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_8010C114);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_8010C268);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_8010C628);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_8010C7EC);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_8010CC28);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_8010CCCC);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_8010CDA4);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_8010CE90);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_8010CEE4);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_8010D108);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_8010D2D8);

void func_8010D5E4(void) {
}

void func_8010D5EC(void) {
}

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_8010D5F4);

void func_8010D76C(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 4);
    switch (temp_v1) {                              /* irregular */
    case 0:
        M2C_FIELD(arg0, u8 *, 4) = 1U;
        func_8010D5F4(arg0, 0U);
        func_800752B4(0);
        func_80075D24(0x1FFF);
        return;
    case 1:
        if (func_80026AD0(arg0) != 0) {
            func_8010D5F4(arg0, M2C_FIELD(arg0, u8 *, 3));
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

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_8010D82C);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_8010DA50);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", f_TestTombaOverlapsEvilPig);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_8010DD0C);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_8010DE1C);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_8010E4C8);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_8010EB5C);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_8010F3C0);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_8010F504);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_80110208);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_8011041C);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_80110714);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", f_UpdateGhostEvilPigRandomRicochetVolley);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", f_UpdateGhostEvilPigGraspAttack);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", f_UpdateGhostEvilPigTripleRicochetVolley);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_80110FE8);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_801114C4);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_801116A8);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_80111964);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_80111E1C);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_801125A8);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_801127D4);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_801128E8);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_80112A94);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_80112C38);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_80112D50);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_80112EE4);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_80113020);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_8011353C);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_801135E0);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_801136D8);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_80113788);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_80113A54);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_80113DB4);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_80113EB4);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_80114158);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_8011448C);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_801144D4);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_8011478C);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_80114CCC);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_80114CF8);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_80114E00);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_80115048);

void func_80115228(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 4);
    switch (temp_v1) {                              /* irregular */
    case 0:
        if (func_80051B70(arg0, 0xC, 0) == 0) {
            M2C_FIELD(arg0, s16 *, 0x80) = 0x8C;
            M2C_FIELD(arg0, s16 *, 0x82) = 0x118;
            M2C_FIELD(arg0, s16 *, 0x84) = 0xCB;
            M2C_FIELD(arg0, s8 *, 0) = 1;
            M2C_FIELD(arg0, s16 *, 0x86) = 0x190;
            M2C_FIELD(arg0, u8 *, 4) = (u8) (M2C_FIELD(arg0, u8 *, 4) + 1);
            return;
        }
    case 2:
        return;
    case 1:
        if (func_8007778C(arg0) != 0) {
            func_800517F8(arg0);
            return;
        }
        break;
    case 3:
        func_8007A624(arg0);
        break;
    }
}

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_80115300);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_801153E4);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_801156AC);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_801158EC);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_80115A10);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_80115DD0);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_80115F14);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_80116040);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_80116404);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_801168DC);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_80116A38);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_80116FAC);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_8011703C);

s32 func_801170E8(void *arg0) {
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x38), s8 *, 4) = 2;
    func_80074590(0x37, 0x16, 0);
    return 1;
}

void func_8011711C(void *arg0) {
    M2C_FIELD(arg0, s16 *, 0x2E) = (s16) (((s32) (func_80083F50(M2C_FIELD(arg0, s16 *, 0x76)) * 0x4B0) >> 0xC) + 0x1600);
    M2C_FIELD(arg0, s16 *, 0x36) = (s16) (0x12C0 - ((s32) (func_80083E80(M2C_FIELD(arg0, s16 *, 0x76)) * 0x4B0) >> 0xC));
}

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_80117194);

extern s16 D_800BED82;
extern M2C_UNK D_801261E0;
void func_8011727C(void) {
    func_80075448(0xA, &D_801261E0, 0x10, D_800BED82);
}

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_801172B0);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_80117788);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_8011787C);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_8011796C);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_80117AC8);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_80117B84);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_80117BF4);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", f_UpdateGhostEvilPigRicochetProjectile);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_80118168);

void func_801181CC(void *arg0) {
    s16 temp_s1;
    s32 temp_lo;
    s32 temp_s2;

    temp_s1 = M2C_FIELD(arg0, s16 *, 0x60);
    temp_s2 = func_80083F50(temp_s1) * M2C_FIELD(arg0, s16 *, 0x4E);
    temp_lo = -func_80083E80(temp_s1) * M2C_FIELD(arg0, s16 *, 0x4E);
    M2C_FIELD(arg0, s32 *, 0x30) = (s32) (M2C_FIELD(arg0, s32 *, 0x30) + (M2C_FIELD(arg0, s16 *, 0x50) << 0xC));
    M2C_FIELD(arg0, s16 *, 0x50) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0x50) + 0x2D);
    M2C_FIELD(arg0, s32 *, 0x2C) = (s32) (M2C_FIELD(arg0, s32 *, 0x2C) + temp_s2);
    M2C_FIELD(arg0, s32 *, 0x34) = (s32) (M2C_FIELD(arg0, s32 *, 0x34) + temp_lo);
}

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", f_SpawnGhostEvilPigRicochetProjectile);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_8011836C);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", f_UpdateGhostEvilPigGraspActor);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", f_SpawnGhostEvilPigGraspActor);

INCLUDE_ASM("asm/a0c/nonmatchings/a0c", func_80118B54);

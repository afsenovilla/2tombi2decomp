#include "common.h"
#include "game.h"
#include "m2c.h"

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_801095C8);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_80109788);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_801097DC);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_8010996C);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_80109AC8);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_80109C0C);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_80109DBC);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_80109F14);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_8010A034);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_8010A1F8);


void func_8010A498(void) {
}

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_8010A4A0);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_8010A550);

extern u8 **D_1F80013C;
extern u8 D_1F800144;
extern u8 D_1F800182;

void func_8010A62C(void *a)
{
    u8 **l = D_1F80013C;
    u8 *e;

    D_1F800182 = D_1F800144;
    while (D_1F800182 != 0) {
        e = *l;
        D_1F800182--;
        l++;
        if (e[0] & 1) {
            if (e[0xC] == 9) {
                func_80109C0C(a, e);
            } else if (e[2] == 8) {
                func_801097DC(a, e);
            }
        }
    }
}

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_8010A6F0);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_8010A828);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_8010A99C);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_8010AB3C);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_8010AD0C);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_8010B2F0);


void func_8010B460(void) {
}


void func_8010B468(void) {
}

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_8010B470);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_8010B54C);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_8010B5EC);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_8010B6D0);

void func_8010B744(void)
{
    CameraState *c = &g_CameraState;

    c->unk6C = 0x500;
    c->unk6E = 0xA0;
}

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_8010B760);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_8010BB48);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_8010BD54);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_8010BEF8);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_8010C160);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_8010C2E8);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_8010C4C4);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_8010C674);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_8010C7D4);

extern s8 D_800BF80E;

void func_8010C9D8(void *arg0) {
    s16 temp_v0;
    u16 temp_v0_3;
    u8 temp_v0_2;
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 6);
    switch (temp_v1) {                              /* irregular */
    case 0:
        M2C_FIELD(arg0, s8 *, 0x146) = 0;
        func_80053D90(arg0);
        func_80054198(arg0);
        func_80054D14(arg0, 0xE0, 4);
        func_80074590(0x3A, 0, 0);
        M2C_FIELD(arg0, u8 *, 0x167) = 0x1EU;
        M2C_FIELD(arg0, s8 *, 7) = 0;
        M2C_FIELD(arg0, u16 *, 0x40) = 7U;
        M2C_FIELD(arg0, s16 *, 0x42) = 0;
        M2C_FIELD(arg0, u8 *, 6) = (u8) (M2C_FIELD(arg0, u8 *, 6) + 1);
        /* fallthrough */
    case 1:
        M2C_FIELD(arg0, s8 *, 0x14B) = 3;
        M2C_FIELD(arg0, u8 *, 0x147) = (u8) (M2C_FIELD(arg0, u8 *, 0x147) & 0x7F);
        func_8010B760(arg0);
        func_80054E80(arg0, 0);
        func_8010C674(arg0, 0);
        func_80076D68(arg0);
        M2C_FIELD(arg0, u16 *, 0x32) = (u16) (M2C_FIELD(arg0, u16 *, 0x32) + 0xA);
        func_8010C4C4(arg0);
        if ((M2C_FIELD(arg0, u8 *, 0x29) != 0) && (func_8010BD54(arg0), (M2C_FIELD(arg0, u8 *, 0x29) != 0))) {
            if (M2C_FIELD(arg0, s16 *, 0x50) >= 0x1401) {
                func_80074590(3, 0, 0);
            }
            M2C_FIELD(arg0, s16 *, 0x50) = 0;
        } else {
            temp_v0 = (u16) M2C_FIELD(arg0, s16 *, 0x50) + 0x360;
            M2C_FIELD(arg0, s16 *, 0x50) = temp_v0;
            if (temp_v0 >= 0x3E01) {
                M2C_FIELD(arg0, s16 *, 0x50) = 0x3E00;
            }
            M2C_FIELD(arg0, s32 *, 0x30) = (s32) (M2C_FIELD(arg0, s32 *, 0x30) + (M2C_FIELD(arg0, s16 *, 0x50) << 8));
        }
        temp_v0_2 = M2C_FIELD(arg0, u8 *, 0x167);
        if (temp_v0_2 == 0) {
            M2C_FIELD(arg0, s8 *, 5) = 0;
            M2C_FIELD(arg0, u8 *, 6) = 0U;
            return;
        }
        M2C_FIELD(arg0, u8 *, 0x167) = (u8) (temp_v0_2 - 1);
        return;
    case 2:
        D_800BF80E = 0;
        M2C_FIELD(arg0, s8 *, 0x146) = 0;
        func_80053D90(arg0);
        func_80054198(arg0);
        func_80054D14(arg0, 0xDF, 4);
        func_80074590(0x3A, 0, 0);
        M2C_FIELD(arg0, u16 *, 0x40) = 0x1EU;
        M2C_FIELD(arg0, u8 *, 6) = (u8) (M2C_FIELD(arg0, u8 *, 6) + 1);
        return;
    case 3:
        func_80076D68(arg0);
        func_800551C4(arg0);
        temp_v0_3 = M2C_FIELD(arg0, u16 *, 0x40) - 1;
        M2C_FIELD(arg0, u16 *, 0x40) = temp_v0_3;
        if ((temp_v0_3 << 0x10) == 0) {
            D_800BF80E = 1;
            M2C_FIELD(arg0, s8 *, 4) = 4;
            M2C_FIELD(arg0, s8 *, 5) = 0x20;
            M2C_FIELD(arg0, u8 *, 6) = 0U;
            M2C_FIELD(arg0, s8 *, 7) = 0;
        }
        return;
    }
}

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_8010CC34);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_8010CD70);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_8010CF30);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_8010D3C4);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_8010D550);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_8010D750);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_8010DE18);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_8010E0F4);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_8010E3B8);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_8010E60C);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_8010E7EC);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_8010EB6C);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_8010ED6C);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_8010EF80);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_8010F544);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_8010F654);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_8010F7B0);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_8010F830);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_8010F8CC);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_8010FC70);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_8010FDD8);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_8010FF0C);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_801100B4);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_801100E4);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_8011014C);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", menu);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", f_UpdateBerryNutsRetryMenu);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_80110938);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_80110A34);

extern u8 D_1F800137;
extern u8 D_800BF808[];

void func_80110A68(void)
{
    u8 *s;

    D_1F800137 = 2;
    s = D_800BF808;
    s[7] = 2;
    s[0x31] = 3;
    s[5] = 0;
    *(s16 *)(s + 0x32) = 0x1403;
}

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", f_IncrementBerryNutsScore);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", f_SpawnTinyMouseVillageActorsFromPlacementTable);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_80110C80);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", f_UpdateTinyMouseVillageInteriorDoorSequence);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_80111074);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_8011133C);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_801114A0);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_80111658);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", f_UpdateTinyMouseVillageRewardActor);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_80111E0C);

extern s8 D_800BF841;
void func_80111E70(void *arg0) {
    if ((M2C_FIELD(arg0, u8 *, 5) == 0) && (func_8007E038(0x32, 3) != 0)) {
        M2C_FIELD(arg0, u8 *, 5) = (u8) (M2C_FIELD(arg0, u8 *, 5) + 1);
        D_800BF841 = 0;
        func_80074BF8(0xB);
        func_8004FB20();
    }
    func_800517F8(arg0);
    M2C_FIELD(arg0, s8 *, 1) = 1;
}

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_80111EE4);


void func_80111F94(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 5) == 0) {
        M2C_FIELD(arg0, u8 *, 5) = 1U;
        func_80074590(0x84, 0, 0);
    }
    func_800517F8(arg0);
    M2C_FIELD(arg0, s8 *, 1) = 1;
}

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_80111FE8);

extern u8 D_800BF871;
void func_801120BC(void *arg0) {
    if ((u8) D_800BF871 < 4U) {
        M2C_FIELD(arg0, s8 *, 4) = 3;
        return;
    }
    func_80051B70(arg0, 0xC, 0xB);
    M2C_FIELD(arg0, s8 *, 0xBF) = 1;
    M2C_FIELD(arg0, s16 *, 0x50) = 0;
    M2C_FIELD(arg0, s8 *, 0x46) = 1;
    M2C_FIELD(arg0, u16 *, 0x5A) = (u16) M2C_FIELD(arg0, u16 *, 0x56);
}

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_80112120);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_80112218);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_80112268);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_80112350);

extern void *D_800ECF80;
extern u8 D_8011FC38[];

void func_80112394(u8 *a)
{
    *(void **)(a + 0x3C) = D_800ECF80;
    func_80077B38(a, D_8011FC38, 2);
    *(s16 *)(a + 0x5C) = 0;
    a[0xB] = 0x10;
    *(s16 *)(a + 0x5A) = 0;
    a[0x47] = 0;
}

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_801123E4);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_8011243C);

extern s8 *D_800ECF58[];
extern void *D_80017334[];

void func_80112488(u8 *a)
{
    *(s8 **)(a + 0x3C) = D_800ECF58[0];
    func_80077B38(a, D_80017334, 0x164);
    *(s16 *)(a + 0x5C) = 0;
    a[0xB] = 0x10;
    *(s16 *)(a + 0x5A) = 0;
    a[0x47] = 0;
}

extern u8 D_800BFA28;
void func_801124D8(void *arg0) {
    void *temp_v1;

    temp_v1 = M2C_FIELD(arg0, void **, 0x10);
    if ((u8) D_800BFA28 >= 4U) {
        func_8004D4C4(0x6D, 1);
        func_8004B0D8(arg0);
        M2C_FIELD(arg0, s8 *, 4) = 3;
        return;
    }
    func_8004BD64(arg0, 0, M2C_FIELD(temp_v1, s32 *, 0xD8), M2C_FIELD(temp_v1, s32 *, 0xCC), 0);
    M2C_FIELD(arg0, s8 *, 1) = 1;
}

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_8011254C);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_80112598);

extern u8 D_800BFA28;
void func_801125FC(void *arg0) {
    s16 temp_v1_2;
    u16 temp_v0;
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 5);
    switch (temp_v1) {                              /* irregular */
    case 0:
        if ((u8) D_800BFA28 >= 3U) {
            M2C_FIELD(arg0, u8 *, 5) = 1U;
            M2C_FIELD(arg0, u16 *, 0x40) = 0x3CU;
        }
        temp_v1_2 = M2C_FIELD(arg0, s16 *, 0x60);
        if (temp_v1_2 != 0xE) {
            if (temp_v1_2 == 0x28) {
                M2C_FIELD(arg0, s16 *, 0x60) = 0;
                goto block_8;
            }
        } else {
block_8:
            func_80074590(0x1C, -0xF, -0x32);
        }
        M2C_FIELD(arg0, s16 *, 0x60) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0x60) + 1);
        break;
    case 1:
        temp_v0 = M2C_FIELD(arg0, u16 *, 0x40) - 1;
        M2C_FIELD(arg0, u16 *, 0x40) = temp_v0;
        if ((s16) temp_v0 == -1) {
            M2C_FIELD(arg0, s8 *, 4) = 3;
        }
        break;
    }
    M2C_FIELD(arg0, s8 *, 1) = 1;
    M2C_FIELD(arg0, u16 *, 0x36) = (u16) (M2C_FIELD(arg0, u16 *, 0x36) - 0xA);
    func_800517F8(arg0);
}

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_801126E0);

void func_8011273C(u8 *a)
{
    func_80051B70(a, 0xC, 0x29);
    *(s16 *)(a + 0x54) = 0;
    *(s16 *)(a + 0x56) = 0;
    *(s16 *)(a + 0x58) = 0;
}

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_80112774);

extern void *D_800ECF80;
extern u8 D_8011FC38[];

void func_801127C0(u8 *a)
{
    *(void **)(a + 0x3C) = D_800ECF80;
    func_80077B38(a, D_8011FC38, 0x1);
    *(s16 *)(a + 0x5C) = 0;
    a[0xB] = 0x10;
    *(s16 *)(a + 0x5A) = 0;
    a[0x47] = 0;
}

extern u8 D_800BFA28;
void func_80112810(void *arg0) {
    void *temp_v1;

    temp_v1 = M2C_FIELD(arg0, void **, 0x10);
    if ((u8) D_800BFA28 >= 9U) {
        func_8004D4C4(0x9C, 1);
        func_8004B0D8(arg0);
        M2C_FIELD(arg0, s8 *, 4) = 3;
        return;
    }
    func_8004BD64(arg0, 0, M2C_FIELD(temp_v1, s32 *, 0xD8), M2C_FIELD(temp_v1, s32 *, 0xCC), 0);
    M2C_FIELD(arg0, s8 *, 1) = 1;
}

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_80112884);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_80112D80);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_80112F34);


void func_80112F70(void) {
}

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_80112F78);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_80112FF8);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_80113338);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", f_SpawnBerryNutsScorePopup);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_80113488);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_801136F0);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_80113854);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_80113A7C);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_80113C50);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", f_UpdateBerryNutsMinigameController);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_80114170);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_801142C0);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", f_UpdateBerryNutsHostDialogue);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_801147D0);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", f_UpdateTinyMouseVillageNpcActor);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_80114EAC);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_80114F1C);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_8011562C);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_80115F1C);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_801160A4);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_8011626C);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_801163E0);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_80116708);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_80116AE8);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_80116B14);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_80116B9C);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_80116E68);

extern u16 *D_800ECF78;

void func_801173A8(u8 *a)
{
    u16 *p = D_800ECF78;
    u16 t;

    *(u16 **)(a + 0xC) = p;
    *(u16 *)(a + 8) = p[0];
    t = p[1];
    a[7] = 0;
    *(u16 *)(a + 0xA) = t;
}

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_801173D4);

extern s16 D_800BED82;
extern M2C_UNK D_8011D5D0;
extern M2C_UNK D_8011D774;
void func_801174B0(void) {
    func_80075448(0xC, &D_8011D5D0, 0x10, D_800BED82);
    func_80075448(0xB, &D_8011D774, 0x10, D_800BED82);
}

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_80117500);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_8011778C);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_80117B24);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_80117DE8);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_80118054);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", f_UpdateTinyMouseVillageEntranceActor);

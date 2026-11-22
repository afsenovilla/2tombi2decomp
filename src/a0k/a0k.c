#include "common.h"
#include "game.h"
#include "m2c.h"
#include "psyq/inline_c.h"

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_801095C8);

void func_801095C8();

u8 *func_80109788(void)
{
    u8 *a = func_8007A980(0, 3, 1);

    if (a == NULL) {
        return NULL;
    }
    *(void **)(a + 0x1C) = func_801095C8;
    a[2] = 1;
    a[0x28] |= 0x80;
    return a;
}

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

extern s16 D_1F8001C6;
extern u8 D_800BF80F;

void func_8010B6D0(u8 *a, u8 *b)
{
    if (D_1F8001C6 != 0) {
        *(s16 *)(a + 0x52) = func_8010A828(*(s16 *)(b + 0x56), *(s16 *)(a + 0x52), 2);
    } else if (D_800BF80F == 0 && b[0x17A] == 0) {
        *(s16 *)(a + 0x52) = func_8010A828(*(s16 *)(b + 0x56), *(s16 *)(a + 0x52), 1);
    }
}

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

void func_8010F7B0(s16 *a, s16 m)
{
    if (a[1] < m + 0x16A8) {
        a[1] = m + 0x16A8;
    } else if (0x6658 - m < a[1]) {
        a[1] = 0x6658 - m;
    }
    if (a[5] < m + 0x16A8) {
        a[5] = m + 0x16A8;
    } else if (0x6658 - m < a[5]) {
        a[5] = 0x6658 - m;
    }
}

extern u8 D_1F800137;

void func_8010F830(u8 *a)
{
    u8 *o = *(u8 **)(a + 0x10);

    switch (a[6]) {
    case 0:
        o[0x2B] = 1;
        a[6]++;
    case 1:
        func_80076D68(a);
        if (D_1F800137 == 0) {
            a[0x180] = 0x14;
            a[4] = 1;
            a[5] = 0;
            a[6] = 0;
            a[7] = 0;
            func_80054D14(a, 2, 6);
        }
        break;
    }
}

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_8010F8CC);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_8010FC70);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_8010FDD8);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_8010FF0C);

s32 func_801100B4(u8 *a, u8 *b, s32 bit)
{
    u8 *q = a + 0x60;

    if (b[0] == 0xFF) {
        return -1;
    }
    return (*(u32 *)(q + 0x14) & (1 << bit)) == 0;
}

typedef struct {
    s16 pad0;
    s16 x;
    s16 pad4;
    s16 y;
    s16 pad8;
    s16 z;
} HiPos;

void func_801100E4(void *a, u8 *b)
{
    HiPos p;

    if (b[3] == 0) {
        p.x = *(u16 *)(b + 4);
        p.y = *(u16 *)(b + 6);
        p.z = *(u16 *)(b + 8);
        f_IncrementBerryNutsScore(&p);
        func_80074590(0x11, 0x13, 0);
    } else {
        func_80074590(0x82, 0, 0);
    }
}

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_8011014C);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", menu);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", f_UpdateBerryNutsRetryMenu);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_80110938);

extern u8 D_800BF808[];
extern u8 D_800BF871;
void func_80112884();

void func_80110A34(void)
{
    u8 *s;

    D_1F800137 = 2;
    s = D_800BF808;
    s[7] = 2;
    s[5] = 3;
    s[0x31] = 0;
    D_800BF871 = 5;
}


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

void f_UpdateTinyMouseVillageRewardActor();
extern u16 D_800BFA26;
extern s32 D_800BF854;

void f_IncrementBerryNutsScore(void *a)
{
    u16 *p = &D_800BFA26;
    u16 n;

    if (*p < 999) {
        *(volatile u16 *)p = n = *p + 1;
        if (((volatile u16 *)p)[-1] < n) {
            p[-1] = n;
            D_800BF854 = 1;
        }
    }
    f_SpawnBerryNutsScorePopup(a, D_800BFA26);
}

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", f_SpawnTinyMouseVillageActorsFromPlacementTable);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_80110C80);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", f_UpdateTinyMouseVillageInteriorDoorSequence);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_80111074);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_8011133C);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_801114A0);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_80111658);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", f_UpdateTinyMouseVillageRewardActor);

u8 *func_80111E0C(void *a, u8 b)
{
    u8 *r = func_80072DDC(0, 3, 3, 0x10);

    if (r != NULL) {
        *(void **)(r + 0x1C) = f_UpdateTinyMouseVillageRewardActor;
        r[3] = 0;
        r[0x5E] = b;
        *(void **)(r + 0x10) = a;
    }
    return r;
}

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

void func_80112218(u8 *a)
{
    func_80051B70(a, 0xC, 0xA);
    a[0] = 1;
    *(s16 *)(a + 0x80) = 0xA0;
    *(s16 *)(a + 0x82) = 0x140;
    *(s16 *)(a + 0x84) = 0x190;
    *(s16 *)(a + 0x86) = 0x190;
}

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_80112268);

void f_UpdateTinyMouseVillageRewardActor();

u8 *func_80112350(void *a)
{
    u8 *r = func_80072DDC(a, 0, 3, 0x10);

    if (r != NULL) {
        *(void **)(r + 0x1C) = f_UpdateTinyMouseVillageRewardActor;
        r[3] = 0x3;
    }
    return r;
}

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

void func_801123E4(u8 *a)
{
    u8 *o = *(u8 **)(a + 0x10);

    func_8004BD64(a, 0, *(s32 *)(o + 0xD8), *(s32 *)(o + 0xCC), 0);
    a[1] = 1;
    *(s16 *)(a + 0x32) -= 0x10;
    *(s16 *)(a + 0x36) += 0x10;
}

s32 func_8011243C(void *a)
{
    u8 *r = func_80072DDC(a, 0, 3, 0x10);

    if (r != NULL) {
        *(void **)(r + 0x1C) = f_UpdateTinyMouseVillageRewardActor;
        r[3] = 4;
        return 1;
    }
    return 0;
}

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

s32 func_8011254C(void *a)
{
    u8 *r = func_80072DDC(a, 1, 3, 0x10);

    if (r != NULL) {
        *(void **)(r + 0x1C) = f_UpdateTinyMouseVillageRewardActor;
        r[3] = 5;
        return 1;
    }
    return 0;
}

void func_80112598(u8 *a)
{
    func_80051B70(a, 0xC, 8);
    *(s16 *)(a + 0x2E) = 0x44AD;
    *(s16 *)(a + 0x32) = -0x5C0;
    *(s16 *)(a + 0x36) = 0x1DD9;
    *(s16 *)(a + 0x54) = 0;
    *(s16 *)(a + 0x56) = 0;
    *(s16 *)(a + 0x58) = 0;
    *(s16 *)(a + 0x60) = 0;
    func_80074590(0x1C, -0xF, -0x32);
}

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

s32 func_801126E0(void *a)
{
    u8 *r = func_80072DDC(a, 1, 3, 0x10);

    if (r != NULL) {
        *(void **)(r + 0x1C) = f_UpdateTinyMouseVillageRewardActor;
        r[3] = 6;
        func_8004D688(0x53, 1);
        return 1;
    }
    return 0;
}

void func_8011273C(u8 *a)
{
    func_80051B70(a, 0xC, 0x29);
    *(s16 *)(a + 0x54) = 0;
    *(s16 *)(a + 0x56) = 0;
    *(s16 *)(a + 0x58) = 0;
}

s32 func_80112774(void *a)
{
    u8 *r = func_80072DDC(a, 0, 3, 0x10);

    if (r != NULL) {
        *(void **)(r + 0x1C) = f_UpdateTinyMouseVillageRewardActor;
        r[3] = 7;
        return 1;
    }
    return 0;
}

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

u8 *func_80112F34(void *a)
{
    u8 *r = func_80072DDC(a, 3, 3, 0x23);

    if (r != NULL) {
        *(void **)(r + 0x1C) = func_80112884;
    }
    return r;
}


void func_80112F70(void) {
}

void func_80112F78(u8 *a)
{
    s16 v[6];

    v[1] = (*(s32 *)(*(u8 **)(a + 0xE8) + 0x2C) + *(s32 *)(*(u8 **)(a + 0xF8) + 0x2C)) / 2;
    v[3] = *(s16 *)(a + 0x32) + *(s16 *)(a + 0x84);
    v[5] = (*(s32 *)(*(u8 **)(a + 0xE8) + 0x34) + *(s32 *)(*(u8 **)(a + 0xF8) + 0x34)) / 2;
    func_8003116C(0x35, v, -0x5A);
}

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_80112FF8);

void func_80113338(u8 *a)
{
    s32 s = a[4];

    switch (s) {
    case 0:
        a[4] = 1;
        *(s16 *)(a + 0x40) = 0x20;
        break;
    case 1:
        func_80112FF8(a);
        a[1] = s;
        break;
    case 2:
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

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

extern u8 D_800E7E80[];

s32 func_80114EAC(u8 *a)
{
    u8 *t;

    if (a[3] == 4) {
        *(s16 *)(a + 0x36) += 0xC;
    } else {
        *(s16 *)(a + 0x2E) += 0xC;
    }
    t = D_800E7E80;
    *(s16 *)(t + 0x2E) = *(s16 *)(a + 0x2E);
    *(s16 *)(t + 0x32) = *(s16 *)(a + 0x32) + (s16)(*(s16 *)(a + 0x8A) - 100);
    *(s16 *)(t + 0x36) = *(s16 *)(a + 0x36);
    return 0;
}

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_80114F1C);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_8011562C);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_80115F1C);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_801160A4);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_8011626C);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_801163E0);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_80116708);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_80116AE8);

void func_80116B14(u32 *a, s32 b)
{
    u8 pad[0x20];
    u32 w;
    u32 *q;

    if (D_800BF871 < 4) {
        func_800803DC();
    } else {
        q = a;
        a += 4;
        gte_ldfcdir(0, 0, 0);
        w = *q;
        func_80116708(func_801163E0(a, b, w & 0xFFFF), b, w >> 16);
    }
}

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

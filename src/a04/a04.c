#include "common.h"
#include "game.h"
#include "m2c.h"

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8010A514);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8010A668);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8010A834);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8010A9A8);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8010AC8C);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8010AEA8);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8010B024);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8010B168);

extern s8 D_1F80009C[];
extern s8 D_1F800137[];

void func_8010B2FC(void *arg0, void *arg1, s32 arg2) {
    s32 temp_lo;
    s32 temp_s0;
    s32 temp_v0;
    u16 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u16 *, 0x17E);
    if (!(temp_v1 & 0x200)) {
        if (temp_v1 & 0x8000) {
            if (M2C_FIELD(arg1, u8 *, 0) == 1) {
                func_8001F830();
            }
        } else {
            temp_v0 = func_8001F40C(arg0, arg1, 1);
            if (temp_v0 >= 0) {
                if ((M2C_FIELD(arg0, u8 *, 0x144) == 1) && (temp_v0 < 2)) {
                    func_8001FDB4(arg1, 2, 0x10, 0x1E);
                    *((s8 *)D_1F800137) = 2;
                    return;
                }
                if ((arg2 != 0) && (M2C_FIELD(arg1, u8 *, 0) == 5)) {
                    M2C_FIELD(arg1, u8 *, 0) = 1U;
                    M2C_FIELD(arg1, s8 *, 4) = 2;
                    M2C_FIELD(arg1, s8 *, 5) = 0;
                    M2C_FIELD(arg1, s8 *, 6) = 0;
                }
                temp_s0 = (s32) (func_80083F50(*((s32 *)D_1F80009C)) * (M2C_FIELD(arg0, s16 *, 0x80) + M2C_FIELD(arg1, s16 *, 0x80))) >> 0xC;
                temp_lo = func_80083E80(*((s32 *)D_1F80009C)) * (M2C_FIELD(arg0, s16 *, 0x80) + M2C_FIELD(arg1, s16 *, 0x80));
                M2C_FIELD(arg0, s16 *, 0x2E) = (s16) (M2C_FIELD(arg1, u16 *, 0x2E) + temp_s0);
                M2C_FIELD(arg0, s16 *, 0x36) = (s16) (M2C_FIELD(arg1, u16 *, 0x36) - (temp_lo >> 0xC));
            }
        }
    }
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8010B45C);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8010B8A0);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8010BA18);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8010BC80);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8010BE1C);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8010C03C);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8010C320);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8010C588);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8010C710);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8010C8B4);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8010CBFC);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8010CDB4);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8010D270);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8010D700);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8010DB48);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8010DEF0);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8010E0FC);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8010E2D0);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8010E554);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8010E6DC);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8010E814);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8010E9AC);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8010EDB0);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8010F1CC);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8010F75C);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8010FBEC);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8010FF6C);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_801103F0);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80110608);

extern void *D_1F800080;
extern u8 D_1F800182_5650;

void func_80110714(u8 *a, u8 *b)
{
    if (func_80024BD8(a, b, *(void **)(b + 0xC0)) != 0) {
        b[0x29] = 1;
        a[0x164] = 3;
        D_1F800080 = b;
        D_1F800182_5650 = 0;
    }
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8011076C);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80110800);

extern u8 D_800BF816;
void func_80110900(void) {
    if (D_800BF816 != 0) {
        func_8010AEA8();
        return;
    }
    if (*(u8 *)0x1F800137 == 0) {
        func_8010B024();
    }
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80110950);

extern s32 D_1F80009C_baed;

void func_801109B0(u8 *a, u8 *b)
{
    s32 v;

    if (func_8002313C(a, b, *(void **)(b + 0xC0)) != 0) {
        func_8001E860(a, b, *(void **)(b + 0xC0), 0x400);
        v = D_1F80009C_baed;
        b[0x2B] = 1;
        b[0x46] = v >> 4;
        if (a[0x5E] != 0) {
            b[0x2B] = 0x81;
        }
        D_1F800182_5650 = 0;
    }
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80110A30);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80110AC4);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80110BD0);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80110C58);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80110CD0);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80110D6C);

extern u8 D_800BFA0A;
void func_80110E20(void *arg0) {
    s32 temp_v0;

    temp_v0 = func_8010C8B4();
    if ((temp_v0 >= 0) && ((u32) (D_800BFA0A & 0xF) >= 2U)) {
        if (temp_v0 == 1) {
            M2C_FIELD(arg0, s16 *, 0x142) = -0x300;
            return;
        }
        M2C_FIELD(arg0, s16 *, 0x142) = -0x100;
        M2C_FIELD(arg0, s8 *, 0x16A) = 0xA;
    }
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80110E88);

extern s8 D_1F800182[];

void func_80110F88(s32 arg0, M2C_UNK arg1) {
    if (func_80022F04() != 0) {
        func_8001DC9C(arg0, arg1, 0, 5);
        *((s8 *)D_1F800182) = 0;
    }
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80110FD8);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_801110B8);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80111118);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8011118C);


void func_801111EC(void *arg0, void *arg1) {
    u8 temp_a0;

    if (func_8001EC3C() == 1) {
        temp_a0 = M2C_FIELD(arg0, u8 *, 0x5F);
        if (((temp_a0 & 1) == M2C_FIELD(arg0, u8 *, 0x147)) && (M2C_FIELD(arg0, u8 *, 0x46) == 0xC6)) {
            M2C_FIELD(arg1, u8 *, 0x5F) = temp_a0;
            M2C_FIELD(arg0, u8 *, 0x5F) = (u8) (M2C_FIELD(arg0, u8 *, 0x5F) | 8);
        }
    }
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80111260);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80111320);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80111398);


s32 func_801114A0(s32 arg0, s32 arg1) {
    return func_8010DB48(arg0, arg1, M2C_FIELD(arg1, s32 *, 0xC0));
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_801114C4);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80111560);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_801115D0);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80111710);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_801117C0);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80111828);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8011187C);

extern s8 D_1F80009C[];
extern u8 D_800BFAD5;

void func_80111934(void *arg0, void *arg1) {
    if (!(M2C_FIELD(arg0, u16 *, 0x17E) & 0x200) && (func_80022F04() != 0)) {
        M2C_FIELD(arg0, s8 *, 0x2B) = (s8) ((s32) *((s32 *)D_1F80009C) >> 4);
        if (M2C_FIELD(arg1, u8 *, 0) & 8) {
            if (D_800BFAD5 == 0) {
                func_80022D08(arg0, arg1, 1, 1);
            }
        } else {
            if (D_800BFAD5 == 0) {
                func_80022D08(arg0, arg1, 1, 0);
            }
            M2C_FIELD(arg1, u8 *, 0) = 2U;
            M2C_FIELD(arg1, s8 *, 4) = 2;
            M2C_FIELD(arg1, s8 *, 5) = 2;
            M2C_FIELD(arg1, s8 *, 6) = 0;
        }
    }
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80111A04);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80111A74);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80111C08);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80111D60);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80111EC8);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80112068);

extern s8 D_1F800138[];
extern s8 D_1F80019B[];

void func_801127AC(void) {
    func_80045258(M2C_FIELD(*((volatile void **)D_1F800138), u8 *, 0x6E), 0xF);
    *((volatile s8 *)D_1F80019B) = 1;
    func_80051FB4();
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_801127EC);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_801129C0);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80112B50);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_801131E0);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_801133CC);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_801139F4);


void func_80113FA4(void *arg0, s32 arg1) {
    s16 temp_s0;
    s16 temp_v1_2;
    s32 temp_lo;
    s32 var_a1;
    u16 temp_v0;
    u8 temp_v1;
    void *temp_s1;

    var_a1 = arg1;
    temp_v1 = M2C_FIELD(arg0, u8 *, 7);
    switch (temp_v1) {                              /* irregular */
    case 0:
        M2C_FIELD(arg0, u16 *, 0x154) = 0x100U;
        M2C_FIELD(arg0, u16 *, 0x56) = 0U;
        M2C_FIELD(arg0, u8 *, 7) = (u8) (M2C_FIELD(arg0, u8 *, 7) + 1);
        /* fallthrough */
    case 1:
        temp_v0 = M2C_FIELD(arg0, u16 *, 0x154) - 0x20;
        M2C_FIELD(arg0, u16 *, 0x154) = temp_v0;
        if ((s16) temp_v0 < 0x20) {
            M2C_FIELD(arg0, u16 *, 0x154) = 0x20U;
        }
        temp_v1_2 = M2C_FIELD(arg0, u16 *, 0x56) - M2C_FIELD(arg0, u16 *, 0x154);
        M2C_FIELD(arg0, u16 *, 0x56) = (u16) temp_v1_2;
        if (temp_v1_2 < -0x3FF) {
            M2C_FIELD(arg0, s8 *, 0x149) = 2;
            M2C_FIELD(arg0, s8 *, 0x14A) = 2;
            M2C_FIELD(arg0, u16 *, 0x56) = 0xC00U;
            M2C_FIELD(arg0, s16 *, 0x140) = 0xC00;
            M2C_FIELD(arg0, s8 *, 0x2A) = 1;
            M2C_FIELD(arg0, s8 *, 0x147) = 0;
            M2C_FIELD(arg0, s8 *, 5) = 4;
            M2C_FIELD(arg0, s8 *, 6) = 0;
            M2C_FIELD(arg0, u8 *, 7) = 0U;
            M2C_FIELD(arg0, s8 *, 0x61) = 0;
            M2C_FIELD(arg0, u8 *, 0) = (u8) (M2C_FIELD(arg0, u8 *, 0) & 3);
        } else {
            temp_s0 = temp_v1_2 + 0x800;
            temp_s1 = M2C_FIELD(arg0, void **, 0x10);
            temp_lo = func_80083F50(temp_s0) * M2C_FIELD(arg0, s16 *, 0x152);
            M2C_FIELD(arg0, s16 *, 0x2E) = (s16) (M2C_FIELD(temp_s1, u16 *, 0x2C) + (temp_lo >> 0xC));
            var_a1 = func_80083E80(temp_s0, temp_lo) * M2C_FIELD(arg0, s16 *, 0x152);
            M2C_FIELD(arg0, s16 *, 0x36) = (s16) (M2C_FIELD(temp_s1, u16 *, 0x34) - (var_a1 >> 0xC));
            M2C_FIELD(arg0, s16 *, 0x32) = (s16) (M2C_FIELD(temp_s1, u16 *, 0x30) + M2C_FIELD(arg0, u16 *, 0x156));
        }
        break;
    }
    func_80076D68(arg0, var_a1);
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8011411C);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_801144FC);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_801149B8);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_801150C4);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80115534);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80115708);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80115978);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80115AFC);

extern s8 D_1F800138[];
extern s8 D_1F80019B[];

void func_80115EB0(void) {
    func_80045258(M2C_FIELD(*((volatile void **)D_1F800138), u8 *, 0x6E), 0xF);
    *((volatile s8 *)D_1F80019B) = 1;
    func_80051FB4();
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80115EF0);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80115F8C);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80115FE0);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8011604C);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80116114);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_801161EC);

extern u16 D_1F8001A4;

void func_801162E8(u8 *a)
{
    s16 v[8];

    v[1] = *(u16 *)(a + 0x2E);
    v[3] = D_1F8001A4;
    v[5] = *(u16 *)(a + 0x36);
    func_800312D4(0x515, v, -0xA);
    v[3] += 0x50;
    func_800312D4(0x514, v, -0xA);
    func_80074590(7, 0, 0);
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", f_SpawnKujaraRanchSceneActorsFromPlacementTable);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80116884);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_801169E8);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80116B48);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80116CCC);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_801170A8);

extern u16 *D_800ECF78;

void func_801175D0(u8 *a)
{
    u16 *p = D_800ECF78;
    u16 t;

    *(u16 **)(a + 0xC) = p;
    *(u16 *)(a + 8) = p[0];
    t = p[1];
    a[7] = 0;
    *(u16 *)(a + 0xA) = t;
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_801175FC);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_801178A0);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80117C58);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80117E18);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80117F68);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_801181E8);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80118448);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_801185F0);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80118858);


void func_801189C4(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 4);
    switch (temp_v1) {                              /* irregular */
    case 0:
        if (M2C_FIELD(arg0, u8 *, 0x5E) == 0) {
            func_8004BEF4(arg0);
        }
        M2C_FIELD(arg0, u8 *, 4) = (u8) (M2C_FIELD(arg0, u8 *, 4) + 1);
        return;
    case 1:
        if (M2C_FIELD(arg0, u8 *, 0x5E) == 0) {
            func_80118858(arg0);
            return;
        }
        return;
    case 2:
        func_8004B9C8(arg0);
        return;
    case 3:
        func_8007A624(arg0);
        break;
    }
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", f_UpdateKujaraQuestPickupActor);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80118E50);


void func_80118EB8(void *arg0) {
    if (func_80040B48(0x61) >= 0) {
        func_8004D4C4(0x52, 1);
        func_8004B0D8(arg0);
    }
    M2C_FIELD(arg0, s8 *, 4) = 3;
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80118F04);


void func_80118FA0(void *arg0) {
    if (func_80040B48(0x85) >= 0) {
        func_8004D4C4(0x94, 1);
        func_8004B0D8(arg0);
        D_800BF870.pad1[0xC8] |= 0x10;
    }
    M2C_FIELD(arg0, s8 *, 4) = 3;
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80119004);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80119080);


void func_80119104(void *arg0) {
    if (func_80040C00(0x66) >= 0) {
        func_8004D4C4(0x3F, 1);
        func_8004B0D8(arg0);
        D_800BF870.pad1[0x17B] += 1 << (M2C_FIELD(arg0, u8 *, 3) * 2);
    }
    M2C_FIELD(arg0, s8 *, 4) = 3;
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80119170);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_801193D4);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80119588);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_801195AC);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_801196C8);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80119B34);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80119F24);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80119FA8);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8011A164);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8011A3C0);

extern s8 D_1F80017C[];
extern u8 D_800BF9BB;

void func_8011A554(void *arg0) {
    u16 temp_v0;
    u8 temp_v1;
    void *temp_a0;
    void *temp_a0_2;
    void *temp_v1_2;
    void *temp_v1_3;
    void *temp_v1_4;
    void *temp_v1_5;

    temp_v1 = M2C_FIELD(arg0, u8 *, 5);
    switch (temp_v1) {                              /* irregular */
    case 0:
        if (D_800BF9BB == 0) {
            M2C_FIELD(arg0, u8 *, 5) = 1U;
            M2C_FIELD(arg0, u16 *, 0x50) = 0U;
        } else {
            M2C_FIELD(arg0, u8 *, 5) = 2U;
        }
        break;
    case 1:
        if (((u8) D_800BF9BB >= 3U) && !(*((u16 *)D_1F80017C) & 3)) {
            temp_v0 = M2C_FIELD(arg0, u16 *, 0x50) + 1;
            M2C_FIELD(arg0, u16 *, 0x50) = temp_v0;
            if ((s16) temp_v0 >= 0xC) {
                M2C_FIELD(arg0, u8 *, 5) = (u8) (M2C_FIELD(arg0, u8 *, 5) + 1);
            }
            temp_a0 = M2C_FIELD(arg0, void **, 0xC0);
            M2C_FIELD(temp_a0, u16 *, 0x3A) = (u16) (M2C_FIELD(temp_a0, u16 *, 0x3A) + M2C_FIELD(arg0, u16 *, 0x50));
            temp_a0_2 = M2C_FIELD(arg0, void **, 0xC4);
            M2C_FIELD(temp_a0_2, u16 *, 0x3A) = (u16) (M2C_FIELD(temp_a0_2, u16 *, 0x3A) - M2C_FIELD(arg0, u16 *, 0x50));
        }
        break;
    case 2:
        temp_v1_2 = M2C_FIELD(arg0, void **, 0xC0);
        M2C_FIELD(temp_v1_2, u16 *, 0x3A) = (u16) (M2C_FIELD(temp_v1_2, u16 *, 0x3A) + 0xC);
        temp_v1_3 = M2C_FIELD(arg0, void **, 0xC4);
        M2C_FIELD(temp_v1_3, u16 *, 0x3A) = (u16) (M2C_FIELD(temp_v1_3, u16 *, 0x3A) - 0xC);
        break;
    }
    temp_v1_4 = M2C_FIELD(arg0, void **, 0xC0);
    if ((u16) M2C_FIELD(temp_v1_4, u16 *, 0x3A) >= 0x780U) {
        M2C_FIELD(temp_v1_4, u16 *, 0x3A) = 0x708U;
    }
    temp_v1_5 = M2C_FIELD(arg0, void **, 0xC4);
    if ((u16) M2C_FIELD(temp_v1_5, u16 *, 0x3A) < 0x691U) {
        M2C_FIELD(temp_v1_5, u16 *, 0x3A) = 0x708U;
    }
    M2C_FIELD(arg0, s8 *, 1) = 1;
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8011A6C4);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8011A8A0);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8011A9E4);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8011AFD8);


void func_8011B034(void *arg0) {
    M2C_FIELD(arg0, s8 *, 1) = 1;
    func_80077B5C();
}

extern void *D_800ECF80;
extern u8 D_80144360[];

void func_8011B058(u8 *a)
{
    *(void **)(a + 0x3C) = D_800ECF80;
    func_80077B38(a, D_80144360, 5);
    a[0xD] = 1;
    a[0xB] = 0x10;
    *(s16 *)(a + 0x5C) = 0;
    *(s16 *)(a + 0x5A) = 0;
    a[0x47] = 0;
    a[8] = 0xF0;
}


void func_8011B0B8(void *arg0) {
    M2C_FIELD(arg0, s8 *, 1) = 1;
    func_80077B5C();
}

void func_8011B0DC(u8 *a)
{
    if (func_80051B70(a, 0xC, 0x15) == 0) {
        *(s16 *)(a + 0x54) = 0;
        *(s16 *)(a + 0x56) = 0;
        *(s16 *)(a + 0x58) = 0;
    }
}

extern s16 D_800ED098;
void func_8011B11C(void *arg0) {
    void *temp_v0;

    if (D_800ED098 < 2) {
        M2C_FIELD(arg0, s8 *, 4) = 3;
        return;
    }
    func_80051B70(arg0, 0xC, 0);
    M2C_FIELD(arg0, s8 *, 0xB) = 7;
    M2C_FIELD(M2C_FIELD(arg0, void **, 0xC0), s16 *, 2) = -0x40;
    M2C_FIELD(M2C_FIELD(arg0, void **, 0xC0), s16 *, 0xC) = -0x700;
    M2C_FIELD(M2C_FIELD(arg0, void **, 0xC0), s16 *, 0x3A) = 0x708;
    temp_v0 = func_8007AAE8();
    M2C_FIELD(arg0, void **, 0xC4) = temp_v0;
    M2C_FIELD(temp_v0, s16 *, 6) = -1;
    M2C_FIELD(M2C_FIELD(arg0, void **, 0xC4), s16 *, 0) = 0;
    M2C_FIELD(M2C_FIELD(arg0, void **, 0xC4), s16 *, 2) = 0x60;
    M2C_FIELD(M2C_FIELD(arg0, void **, 0xC4), s16 *, 4) = 0;
    M2C_FIELD(M2C_FIELD(arg0, void **, 0xC4), s16 *, 8) = 0;
    M2C_FIELD(M2C_FIELD(arg0, void **, 0xC4), s16 *, 0xA) = 0;
    M2C_FIELD(M2C_FIELD(arg0, void **, 0xC4), s16 *, 0xC) = -0x600;
    M2C_FIELD(M2C_FIELD(arg0, void **, 0xC4), s16 *, 0x3A) = 0x708;
    M2C_FIELD(arg0, s16 *, 0x56) = 0xC00;
    M2C_FIELD(arg0, s16 *, 0x54) = 0;
    M2C_FIELD(arg0, s16 *, 0x58) = 0;
    M2C_FIELD(arg0, s8 *, 8) = 2;
    M2C_FIELD(arg0, s8 *, 9) = 2;
    M2C_FIELD(arg0, s16 *, 0x50) = 0;
    func_800517F8(arg0);
    func_8013DE84(arg0);
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8011B22C);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8011B27C);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8011B378);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8011B460);


void func_8011B4D0(void) {
    func_8007778C();
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8011B4F0);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8011B538);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8011B57C);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8011B618);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8011B674);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8011B79C);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8011B7F4);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8011B958);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8011BB48);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8011BDFC);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8011BE5C);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8011BF00);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8011BF60);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8011C204);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8011C31C);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8011C364);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8011C3BC);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8011C4E0);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8011C784);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8011C974);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8011CA8C);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8011CCE8);


void func_8011CF80(void *arg0) {
    u8 temp_v1;
    u8 temp_v1_2;

    temp_v1 = M2C_FIELD(arg0, u8 *, 4);
    switch (temp_v1) {                              /* switch 1; irregular */
    case 0:                                         /* switch 1 */
        func_8011D13C(arg0);
        return;
    case 1:                                         /* switch 1 */
        func_8007778C(arg0);
        temp_v1_2 = M2C_FIELD(arg0, u8 *, 5);
        switch (temp_v1_2) {                        /* switch 2; irregular */
        case 0:                                     /* switch 2 */
            func_8011C974(arg0);
            break;
        case 3:                                     /* switch 2 */
            func_8011CCE8(arg0);
            break;
        case 4:                                     /* switch 2 */
            func_8011D230(arg0);
            break;
        }
        func_8011D354(arg0);
        func_8011CA8C(arg0);
        M2C_FIELD(arg0, s8 *, 0x29) = 0;
        if (M2C_FIELD(arg0, u8 *, 1) != 0) {
            func_800518FC(arg0);
            return;
        }
        return;
    case 2:                                         /* switch 1 */
        func_8011D280(arg0);
        return;
    case 3:                                         /* switch 1 */
        func_8007A624(arg0);
        break;
    }
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8011D0A4);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8011D13C);

void func_8011D230(u8 *a)
{
    if (a[0x29] == 0) {
        func_8011D414(a, 1);
        a[5] = 3;
        a[6] = 1;
        *(s16 *)(a + 0x6C) = 1;
    }
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8011D280);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8011D354);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8011D414);

s32 func_8011D504(u8 *a)
{
    s16 v;

    if (a[0x29] != 0) {
    if (*(s16 *)(a + 0x78) == 0) {
        v = *(s16 *)(a + 0x44);
        if (v > 0) {
            *(s16 *)(a + 0x78) = 1;
            *(s16 *)(*(u8 **)(a + 0xC0) + 0x14) = 0x20;
        } else if (v < 0) {
            *(s16 *)(a + 0x78) = 2;
            *(s16 *)(*(u8 **)(a + 0xC0) + 0x14) = 0x20;
        }
    }
    return 1;
    }
    return 0;
}


void func_8011D568(void *arg0) {
    s32 temp_v0_2;
    u32 temp_v0;

    temp_v0 = (u16) M2C_FIELD(M2C_FIELD(arg0, void **, 0xC0), u16 *, 0x38) >> 5;
    M2C_FIELD(arg0, s16 *, 0x80) = (s16) temp_v0;
    M2C_FIELD(arg0, s16 *, 0x82) = (s16) (temp_v0 * 2);
    temp_v0_2 = (s32) (M2C_FIELD(M2C_FIELD(arg0, void **, 0xC0), u16 *, 0x3A) * 0x113) >> 0xC;
    M2C_FIELD(arg0, s16 *, 0x84) = (s16) temp_v0_2;
    M2C_FIELD(arg0, s16 *, 0x86) = (s16) (temp_v0_2 + 0x32);
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8011D5BC);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8011D878);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8011DA24);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8011DCE4);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8011DEF4);

extern u8 D_800BF816;
void func_8011E4CC(void *arg0) {
    if (D_800BF816 == 0) {
        M2C_FIELD(arg0, u16 *, 0x32) = (u16) M2C_FIELD(arg0, u16 *, 0x7E);
    } else {
        M2C_FIELD(arg0, u16 *, 0x32) = (u16) (M2C_FIELD(arg0, u16 *, 0x7E) + 0x12C);
    }
    func_8011D878(arg0);
    func_800735F4(arg0, 0x56);
}


void func_8011E528(s32 arg0) {
    func_80073328();
    func_800735F4(arg0, 0x59);
}

extern u8 D_800E7FF4;
void func_8011E558(s32 arg0) {
    if (D_800E7FF4 & 4) {
        func_80073328();
    }
    func_800735F4(arg0, 0x67);
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8011E59C);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8011E6AC);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8011E764);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8011E988);


void func_8011EBD8(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 4);
    switch (temp_v1) {                              /* irregular */
    case 0:
        M2C_FIELD(arg0, u8 *, 4) = 1U;
        M2C_FIELD(arg0, s8 *, 0) = 1;
        if (M2C_FIELD(arg0, u8 *, 3) == 0) {
            M2C_FIELD(arg0, s16 *, 0x80) = 0x40;
            M2C_FIELD(arg0, s16 *, 0x82) = 0x80;
            M2C_FIELD(arg0, s16 *, 0x84) = 0xC8;
            M2C_FIELD(arg0, s16 *, 0x86) = 0x190;
        }
        M2C_FIELD(arg0, s8 *, 0x29) = 0;
        func_8004766C(arg0);
        return;
    case 1:
        if (M2C_FIELD(arg0, u8 *, 3) == 0) {
            func_8011E988(arg0);
        }
        func_8007778C(arg0);
        M2C_FIELD(arg0, s8 *, 0x29) = 0;
        return;
    case 3:
        func_8007A624(arg0);
        /* fallthrough */
    case 2:
        return;
    }
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8011ECB0);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8011F0CC);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8011F3CC);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8011F5FC);

INCLUDE_ASM("asm/a04/nonmatchings/a04", f_SpawnKujaraRanchPlacementReward);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8011FA5C);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8011FBD4);

INCLUDE_ASM("asm/a04/nonmatchings/a04", f_UpdateKujaraRanchPlacementRewardActor);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80120188);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_801201E0);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80120260);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_801202F8);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80120544);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_801206DC);

INCLUDE_ASM("asm/a04/nonmatchings/a04", f_UpdateKujaraLiftDepartureSequence);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80120C14);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80120F08);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_801211E4);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8012126C);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_801214B4);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_801217F8);


void func_80121A58(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 4);
    switch (temp_v1) {                              /* irregular */
    case 0:
        M2C_FIELD(arg0, s16 *, 0x80) = 0x76;
        M2C_FIELD(arg0, s16 *, 0x82) = 0xEC;
        M2C_FIELD(arg0, s16 *, 0x84) = 0xC8;
        M2C_FIELD(arg0, u8 *, 4) = 1U;
        M2C_FIELD(arg0, s8 *, 0) = 1;
        M2C_FIELD(arg0, s16 *, 0x86) = 0x190;
        M2C_FIELD(arg0, s8 *, 0x29) = 0;
        M2C_FIELD(arg0, s8 *, 0x2B) = 0;
        return;
    case 1:
        func_8007778C(arg0);
        return;
    case 2:
        func_8007778C(arg0);
        func_801217F8(arg0);
        return;
    case 3:
        func_8007A624(arg0);
        return;
    }
}

extern s8 D_1F8000F2[];
extern s8 D_1F800164[];

void func_80121B1C(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 4);
    switch (temp_v1) {                              /* irregular */
    case 0:
        if (func_80051B70(arg0, 0xC, 7) == 0) {
            M2C_FIELD(arg0, s8 *, 0xB) = 0xF;
            M2C_FIELD(arg0, s16 *, 0x80) = 0x96;
            M2C_FIELD(arg0, s16 *, 0x82) = 0x12C;
            M2C_FIELD(arg0, s16 *, 0x86) = 0x78;
            M2C_FIELD(arg0, s16 *, 0x84) = 0x78;
            M2C_FIELD(arg0, s8 *, 0) = 1;
            M2C_FIELD(arg0, s8 *, 0x29) = 0;
            M2C_FIELD(arg0, s8 *, 0x2A) = 0;
            M2C_FIELD(arg0, u8 *, 4) = (u8) (M2C_FIELD(arg0, u8 *, 4) + 1);
            func_80041194(arg0, M2C_FIELD(arg0, s16 *, 0x86) - M2C_FIELD(arg0, s16 *, 0x84), 0, 0);
            M2C_FIELD(arg0, u16 *, 0x32) = (u16) (M2C_FIELD(arg0, u16 *, 0x32) + 0x28);
            return;
        }
    case 2:
        return;
    case 1:
        if ((*((s16 *)D_1F800164) >= 0x300D) && (*((s16 *)D_1F8000F2) < 0x400)) {
            func_8007703C(arg0);
        } else {
            func_8007778C(arg0);
        }
        if (M2C_FIELD(arg0, u8 *, 1) != 0) {
            func_800517F8(arg0);
            return;
        }
        break;
    case 3:
        func_8007A624(arg0);
        break;
    }
}


void func_80121C70(void) {
    if ((*(s16 *)0x1F800164 >= 0x300D) && (*(s16 *)0x1F8000F2 < 0x400)) {
        func_8007703C();
        return;
    }
    func_8007778C();
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80121CC8);

extern s8 D_1F8000F2[];
extern s8 D_1F800207[];

void func_80121E44(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 4);
    switch (temp_v1) {                              /* irregular */
    case 0:
        if (func_80051B70(arg0, 0xC, 0x1D) == 0) {
            *M2C_FIELD(arg0, s16 **, 0xC0) = -0xE8;
            M2C_FIELD(arg0, s16 *, 0x80) = 0xFA;
            M2C_FIELD(arg0, s16 *, 0x82) = 0x1F4;
            M2C_FIELD(arg0, s16 *, 0x84) = 0x4E2;
            M2C_FIELD(arg0, u8 *, 0x2B) = 0U;
            M2C_FIELD(arg0, s8 *, 0x29) = 0;
            M2C_FIELD(arg0, s8 *, 0) = 1;
            M2C_FIELD(arg0, s16 *, 0x86) = 0x578;
            M2C_FIELD(arg0, u8 *, 4) = (u8) (M2C_FIELD(arg0, u8 *, 4) + 1);
            return;
        }
        return;
    case 1:
        if (M2C_FIELD(arg0, u8 *, 0x2B) != 0) {
            M2C_FIELD(arg0, u8 *, 0x2B) = 0U;
            func_80040B48(0x15);
        }
        if (((u32) (*((u8 *)D_1F800207) - 0x10) < 6U) && (*((s16 *)D_1F8000F2) < 0x400)) {
            func_8007703C(arg0);
        } else {
            func_8007778C(arg0);
        }
        if (M2C_FIELD(arg0, u8 *, 1) != 0) {
            func_800518FC(arg0);
            return;
        }
        break;
    case 2:
        func_8007778C(arg0);
        func_800518FC(arg0);
        func_80121CC8(arg0);
        return;
    case 3:
        func_8007A624(arg0);
        break;
    }
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80121FB8);

INCLUDE_ASM("asm/a04/nonmatchings/a04", f_UpdateHolyTreeGrowthSequence);

INCLUDE_ASM("asm/a04/nonmatchings/a04", f_UpdateHolyTreeInteractionSequence);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8012296C);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80122F08);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80123008);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_801231E0);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8012333C);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80123584);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8012379C);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80123B90);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80123CB0);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80123EC8);

extern s8 D_800BF818;
s32 func_80124148(void) {
    D_800BF818 = 7;
    return 1;
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8012415C);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80124394);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80124660);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80124A08);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80124BD0);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80124E18);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80124F04);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80125600);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80125B94);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80125D5C);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80125ECC);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_801262F4);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_801264FC);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80126718);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80126A20);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_801270EC);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_801272D8);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80127478);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80127670);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_801277D4);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80127D70);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80127E14);


s32 func_80127E3C(void) {
    return 1;
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80127E44);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80127E68);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80127EF0);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80127FE8);


void func_8012807C(void *arg0) {
    if ((M2C_FIELD(arg0, u8 *, 0x2A) == 0xF) && (M2C_FIELD(arg0, s16 *, 0x36) < 0x12F6)) {
        M2C_FIELD(arg0, s16 *, 0x36) = 0x12F6;
    }
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_801280AC);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_801282A8);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80128414);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_801285BC);

INCLUDE_ASM("asm/a04/nonmatchings/a04", f_UpdateSeaAnemoneFreezeSequence);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80128BEC);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80128D84);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80128EEC);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80129168);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8012948C);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80129628);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80129744);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80129904);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80129998);


s32 func_801299E8(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    u16 temp_v1_2;
    u16 temp_v1_3;
    void *temp_v0;
    void *temp_v1;
    void *var_t0;

    temp_v0 = M2C_FIELD(arg0, void **, 0x14);
    var_t0 = NULL;
    if (temp_v0 != NULL) {
        var_t0 = temp_v0;
        M2C_FIELD(var_t0, s16 *, 0x2C) = (s16) arg1;
        M2C_FIELD(var_t0, s16 *, 0x2E) = (s16) arg2;
        M2C_FIELD(var_t0, s16 *, 0x30) = (s16) arg3;
        M2C_FIELD(var_t0, u16 *, 0x48) = (u16) M2C_FIELD(M2C_FIELD(arg0, void **, 0xCC), u16 *, 8);
        M2C_FIELD(var_t0, u16 *, 0x4A) = (u16) M2C_FIELD(arg0, u16 *, 0x56);
        temp_v1 = M2C_FIELD(arg0, void **, 0xCC);
        temp_v1_2 = (u16) M2C_FIELD(temp_v1, s16 *, 0xC);
        if (M2C_FIELD(temp_v1, s16 *, 0xC) >= 0x801) {
            M2C_FIELD(var_t0, u16 *, 0x4C) = (u16) (temp_v1_2 - 0x1000);
        } else {
            M2C_FIELD(var_t0, u16 *, 0x4C) = temp_v1_2;
        }
        temp_v1_3 = M2C_FIELD(var_t0, u16 *, 0x4C);
        M2C_FIELD(var_t0, u16 *, 0x4C) = (u16) (temp_v1_3 + ((s32) (temp_v1_3 << 0x10) >> 0x11));
        M2C_FIELD(var_t0, s32 *, 0x58) = (s32) M2C_FIELD(M2C_FIELD(arg0, void **, 0x38), u16 *, 2);
    }
    return (s32) var_t0;
}


void func_80129A88(s32 arg0)
{
  void *temp_v1;
  temp_v1 = *((void **) (((signed char *) arg0) + 0x14));
  if (temp_v1 != 0)
  {
    *((s8 *) (((signed char *) temp_v1) + 4)) = 2;
    *((void **) (((signed char *) arg0) + 0x14)) = 0;
  }
  return 2;
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80129AA8);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80129B54);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80129C44);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80129D0C);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80129D98);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8012A180);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8012A480);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8012A598);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8012A714);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8012A80C);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8012AB58);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8012AF9C);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8012B8B4);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8012BC40);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8012C658);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8012C724);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8012C7CC);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8012C8AC);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8012C934);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8012C9E0);


s32 func_8012CA80(void *arg0) {
    s32 var_v0;
    u8 temp_a1;

    temp_a1 = M2C_FIELD(arg0, u8 *, 0x5F);
    if ((temp_a1 & 0x80) || ((temp_a1 != 0) && ((temp_a1 & 1) == M2C_FIELD(arg0, u8 *, 0xBE)))) {
        M2C_FIELD(arg0, s8 *, 0) = 2;
        M2C_FIELD(arg0, s8 *, 4) = 2;
        M2C_FIELD(arg0, s8 *, 6) = 0;
        if (M2C_FIELD(arg0, u8 *, 0x5F) & 0x80) {
            M2C_FIELD(arg0, s8 *, 5) = 3;
        } else {
            M2C_FIELD(arg0, s8 *, 5) = 2;
            if (M2C_FIELD(arg0, u8 *, 0xBE) == 0) {
                var_v0 = (s32) (M2C_FIELD(arg0, s16 *, 0x60) + 0x800) >> 4;
            } else {
                var_v0 = (s32) ((u16) M2C_FIELD(arg0, s16 *, 0x60) >> 4);
            }
            M2C_FIELD(arg0, s8 *, 0x2B) = (s8) var_v0;
        }
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8012CB18);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8012CBD4);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8012CF08);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8012D05C);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8012D1A0);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8012D424);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8012D844);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8012DA04);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8012E0A8);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8012E6A4);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8012E87C);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8012E9EC);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8012EAF4);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8012EC48);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8012EE00);


void func_8012F054(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x30) = (s32) (M2C_FIELD(arg0, s32 *, 0x30) - (func_80083E80(M2C_FIELD(arg0, s16 *, 0x4E)) << 6));
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8012F090);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8012F148);


void func_8012F1E4(void *arg0) {
    M2C_UNK var_a0;

    if (M2C_FIELD(arg0, u8 *, 6) == 0) {
        func_80074590(0x91, 0, 0);
        M2C_FIELD(arg0, s8 *, 0x5E) = 0;
        M2C_FIELD(arg0, u8 *, 0x1B) = (u8) (M2C_FIELD(arg0, u8 *, 0x1B) & 0xBF);
        func_8012F41C(arg0, 3, 0);
        var_a0 = 6;
        if (M2C_FIELD(arg0, u8 *, 2) == 0x1C) {
            var_a0 = 0xC;
        }
        func_80026100(var_a0);
        func_8012F690(arg0, -1, 0x14, 0x3C);
        M2C_FIELD(arg0, u8 *, 6) = (u8) (M2C_FIELD(arg0, u8 *, 6) + 1);
    }
    if (M2C_FIELD(arg0, s16 *, 0x78) == 0) {
        func_80076D68(arg0);
    }
}


void func_8012F298(void *arg0) {
    s32 temp_v1;

    temp_v1 = func_8009A450() & 0xF;
    if (temp_v1 >= 0xA) {
        if (M2C_FIELD(arg0, u8 *, 2) == 0x1C) {
            func_8012F41C(arg0, 0, 0);
            M2C_FIELD(arg0, s8 *, 5) = 1;
            M2C_FIELD(arg0, s16 *, 0x72) = 0;
        }
    } else {
        if (temp_v1 >= 7) {
            func_8012F41C(arg0, 2, 0);
            M2C_FIELD(arg0, s16 *, 0x42) = 1;
        } else {
            M2C_FIELD(arg0, s16 *, 0x42) = 0;
        }
        M2C_FIELD(arg0, s16 *, 0x40) = 0x3C;
        M2C_FIELD(arg0, s8 *, 6) = 1;
    }
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8012F32C);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8012F41C);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8012F4FC);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8012F56C);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8012F634);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8012F690);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8012F734);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8012F788);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8012FA5C);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8012FBD8);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8012FC8C);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8012FDEC);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8012FF68);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8013001C);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80130290);

INCLUDE_ASM("asm/a04/nonmatchings/a04", f_UpdateFirstReadyOrNotKujaraFoundSequence);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8013076C);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_801308E8);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80130B74);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80130EB4);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80130F7C);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80131248);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_801314D4);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80131848);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80131AA4);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80131D14);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80131E08);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80131F6C);

extern s8 D_1F8001A6[];
extern s8 D_1F8001BC[];
extern s8 D_1F8001BE[];
extern s8 D_1F8001C0[];
extern s8 D_1F8001C4[];

s32 func_801322A8(void *arg0, s16 arg1, s32 arg2) {
    s32 temp_a1;
    s32 temp_lo;
    s32 temp_s1;

    temp_s1 = (s32) (-func_80083E80(M2C_FIELD(arg0, s16 *, 0x56)) * arg1) >> 0xC;
    temp_lo = func_80083F50(M2C_FIELD(arg0, s16 *, 0x56)) * arg1;
    *((s16 *)D_1F8001BE) = M2C_FIELD(arg0, u16 *, 0x32) + arg2;
    *((s16 *)D_1F8001C0) = M2C_FIELD(arg0, u16 *, 0x36) + temp_s1;
    temp_a1 = temp_lo >> 0xC;
    *((s16 *)D_1F8001BC) = M2C_FIELD(arg0, u16 *, 0x2E) + temp_a1;
    if (func_800498C8(arg0, temp_a1) != 0) {
        if (func_80045724() != 0) {
            if ((*((u16 *)D_1F8001A6) & 0xF00) == 0x700) {
                return 2;
            }
            M2C_FIELD(arg0, u16 *, 0x32) = (u16) (M2C_FIELD(arg0, u16 *, 0x32) + *((u16 *)D_1F8001C4));
            return 1;
        }
        /* Duplicate return node #6. Try simplifying control flow for better match */
        return 0;
    }
    return 0;
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_801323A4);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_801324B0);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_801326D0);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80132968);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80132B14);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80132D10);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80132FF4);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_801332D0);

INCLUDE_ASM("asm/a04/nonmatchings/a04", f_UpdateBigIcePigActor);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80133A30);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80133A88);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80133E7C);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80133FF4);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80134350);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80134998);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80134CB4);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80134EBC);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_801351B8);

extern s8 D_1F800162[];
extern s8 D_1F800164[];
extern s8 D_1F800207[];
extern s16 D_800E7FFE;

s32 func_80135250(void *arg0, s32 arg1) {
    s32 temp_v1;
    u8 temp_v1_2;

    if ((D_800E7FFE & 0x8200) || ((temp_v1_2 = *((u8 *)D_1F800207), (temp_v1_2 != 1)) && ((u32) (temp_v1_2 - 5) >= 3U)) || ((u32) (((M2C_FIELD(arg0, u16 *, 0x32) - *((u16 *)D_1F800162)) + 0x96) & 0xFFFF) >= 0x259U)) {
        return 0;
    }
    temp_v1 = *((u16 *)D_1F800164) - M2C_FIELD(arg0, u16 *, 0x36);
    if (arg1 != 0) {
        return (u32) ((temp_v1 + 0x12C) & 0xFFFF) < 0x258U;
    }
    if ((u32) ((temp_v1 + 0x1F4) & 0xFFFF) >= 0x3E8U) {
        return ((u32) ((temp_v1 + 0x320) & 0xFFFF) < 0x640U) * 2;
    }
    return 1;
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80135300);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80135340);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_801353C8);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_801354B8);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80135570);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80135698);


void func_80135864(void *arg0) {
    s32 temp_s1;

    temp_s1 = arg0 + 0x2C;
    func_80027144(M2C_FIELD(M2C_FIELD(arg0, void **, 0xC0), s32 *, 0x40), temp_s1, 0x700, 0x18);
    func_80074590(0xC, 0, 0);
    M2C_FIELD(arg0, u16 *, 0x32) = (u16) (M2C_FIELD(arg0, u16 *, 0x32) + 0x64);
    func_80027144(M2C_FIELD(M2C_FIELD(arg0, void **, 0xC0), s32 *, 0x40), temp_s1, 0x800, -0x7FE8);
    func_80074590(0xC, 0, 0);
    if (func_8013AA98(arg0) != 0) {
        D_800BF870.pad1[0x157] += 1;
    }
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80135910);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80135AC4);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80135DCC);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8013632C);

INCLUDE_ASM("asm/a04/nonmatchings/a04", f_UpdateSantaBringTheBigSackConversation);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_801368A0);


s32 func_80136AC8(void *arg0) {
    M2C_FIELD(arg0, u8 *, 0x47) = (u8) M2C_FIELD(arg0, u8 *, 0x72);
    return 1;
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80136ADC);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80136CB8);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80136E68);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80136F24);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80137108);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80137378);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80137514);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80137748);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80137870);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_801379F0);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80137BDC);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80137FC8);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80138140);

extern s16 D_800E7FEE;
void func_801383E8(void *arg0) {
    if (D_800E7FEE != 0) {
        func_8004D4C4(0x2E, 1);
        func_8004B0D8(arg0);
        func_80040C00(0x17);
        M2C_FIELD(arg0, s8 *, 4) = 3;
    }
}


void func_80138438(void *arg0) {
    void *temp_v0;

    temp_v0 = func_8007AAE8();
    M2C_FIELD(arg0, void **, 0xC4) = temp_v0;
    M2C_FIELD(temp_v0, s16 *, 6) = -1;
    M2C_FIELD(M2C_FIELD(arg0, void **, 0xC4), s16 *, 0) = 0;
    M2C_FIELD(M2C_FIELD(arg0, void **, 0xC4), s16 *, 2) = 0;
    M2C_FIELD(M2C_FIELD(arg0, void **, 0xC4), s16 *, 4) = 0;
    M2C_FIELD(M2C_FIELD(arg0, void **, 0xC4), s16 *, 8) = 0;
    M2C_FIELD(M2C_FIELD(arg0, void **, 0xC4), s16 *, 0xA) = 0x400;
    M2C_FIELD(M2C_FIELD(arg0, void **, 0xC4), s16 *, 0xC) = 0;
    M2C_FIELD(M2C_FIELD(arg0, void **, 0xC4), s16 *, 0x38) = 0x1000;
    M2C_FIELD(M2C_FIELD(arg0, void **, 0xC4), s16 *, 0x3A) = 0x1000;
    M2C_FIELD(M2C_FIELD(arg0, void **, 0xC4), s16 *, 0x3C) = 0x1000;
    func_80051B04(M2C_FIELD(arg0, void **, 0xC4), 0xC, 0x20);
    M2C_FIELD(arg0, s8 *, 8) = 2;
    M2C_FIELD(arg0, s8 *, 9) = 2;
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_801384EC);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_801387F4);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80138998);

INCLUDE_ASM("asm/a04/nonmatchings/a04", f_UpdateSnowFireflyNestBlink);


void func_80138B74(void *arg0) {
    u16 temp_v0;
    u16 temp_v0_2;
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 6);
    switch (temp_v1) {                              /* irregular */
    case 0:
        temp_v0 = (M2C_FIELD(arg0, u16 *, 0x4E) - 0x100) & 0xFFF;
        M2C_FIELD(arg0, u16 *, 0x4E) = temp_v0;
        if (temp_v0 == 0) {
            M2C_FIELD(arg0, u8 *, 6) = (u8) (M2C_FIELD(arg0, u8 *, 6) + 1);
        }
        M2C_FIELD(arg0, s16 *, 0x32) = (s16) (M2C_FIELD(arg0, u16 *, 0x66) + ((s32) (func_80083E80((s16) M2C_FIELD(arg0, u16 *, 0x4E)) * 0x60) >> 0xC));
        return;
    case 1:
        temp_v0_2 = (M2C_FIELD(arg0, u16 *, 0x4E) - 0x100) & 0xFFF;
        M2C_FIELD(arg0, u16 *, 0x4E) = temp_v0_2;
        if (temp_v0_2 == 0) {
            M2C_FIELD(arg0, u8 *, 6) = (u8) (M2C_FIELD(arg0, u8 *, 6) + 1);
        }
        M2C_FIELD(arg0, s16 *, 0x32) = (s16) (M2C_FIELD(arg0, u16 *, 0x66) + ((s32) (func_80083E80((s16) M2C_FIELD(arg0, u16 *, 0x4E)) << 6) >> 0xC));
        return;
    case 2:
        M2C_FIELD(arg0, s8 *, 0) = 1;
        M2C_FIELD(arg0, s8 *, 4) = 1;
        M2C_FIELD(arg0, s8 *, 5) = 0;
        M2C_FIELD(arg0, u8 *, 6) = 0U;
        return;
    }
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80138C80);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80139058);


void func_801390EC(void *arg0) {
    u16 temp_v0;
    u16 temp_v0_2;
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 5);
    switch (temp_v1) {                              /* irregular */
    case 0:
        if (M2C_FIELD(arg0, u8 *, 0x2B) != 0) {
            M2C_FIELD(arg0, u8 *, 5) = 1U;
            M2C_FIELD(arg0, u16 *, 0x42) = 2U;
            return;
        }
        return;
    case 1:
        temp_v0 = (M2C_FIELD(arg0, u16 *, 0x4E) + 0x200) & 0xFFF;
        M2C_FIELD(arg0, u16 *, 0x4E) = temp_v0;
        if (temp_v0 == 0) {
            temp_v0_2 = M2C_FIELD(arg0, u16 *, 0x42) - 1;
            M2C_FIELD(arg0, u16 *, 0x42) = temp_v0_2;
            if ((temp_v0_2 << 0x10) == 0) {
                M2C_FIELD(arg0, u8 *, 5) = 0U;
            }
        }
        M2C_FIELD(arg0, s16 *, 0x32) = (s16) (M2C_FIELD(arg0, u16 *, 0x66) + ((s32) (func_80083E80((s16) M2C_FIELD(arg0, u16 *, 0x4E)) << 5) >> 0xC));
        break;
    }
}


void func_801391A4(void *arg0) {
    func_8003116C(0x50C, arg0 + 0x2C, -0x32);
    M2C_FIELD(arg0, s8 *, 4) = 3;
    func_80040B48(0x6C);
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_801391E4);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8013939C);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8013945C);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80139614);


void func_801397C0(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 4);
    switch (temp_v1) {                              /* irregular */
    case 0:
        if (func_80051B70(arg0, 0xC, 0x2D) == 0) {
            M2C_FIELD(arg0, s16 *, 0x2E) = 0x1000;
            M2C_FIELD(arg0, s16 *, 0x32) = -0x2454;
            M2C_FIELD(arg0, s16 *, 0x36) = 0x26CD;
            M2C_FIELD(arg0, s16 *, 0x80) = 0x3E;
            M2C_FIELD(arg0, s16 *, 0x82) = 0x77;
            M2C_FIELD(arg0, s16 *, 0x84) = 0x64;
            M2C_FIELD(arg0, s16 *, 0x54) = 0;
            M2C_FIELD(arg0, s16 *, 0x58) = 0;
            M2C_FIELD(arg0, s8 *, 0) = 1;
            M2C_FIELD(arg0, s16 *, 0x86) = 0xC8;
            M2C_FIELD(arg0, u8 *, 4) = (u8) (M2C_FIELD(arg0, u8 *, 4) + 1);
            func_80041194(arg0, 0, 1, 0);
            M2C_FIELD(M2C_FIELD(arg0, void **, 0xC0), s16 *, 0xA) = (s16) -(s16) M2C_FIELD(arg0, u16 *, 0x56);
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

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_801398DC);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80139CBC);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80139D8C);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_80139FF0);

extern void *D_80142454[];

void func_8013A0D8(u8 *a)
{
    if (a[0x71] == 0xFF) {
        func_80040D68(a, D_80142454[a[0x5E]]);
        a[5] = 2;
        a[6] = 0;
        a[0x70] = 1;
    }
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8013A138);


s32 func_8013A218(void *arg0) {
    M2C_FIELD(arg0, u8 *, 6) = (u8) (M2C_FIELD(arg0, u8 *, 6) + 1);
    return 1;
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8013A230);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8013A260);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8013A294);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8013A518);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8013A6B8);

extern void *D_801426C0[];

void func_8013A7F8(u8 *a)
{
    if (a[0x71] == 0xFF) {
        func_80040D68(a, D_801426C0[a[0x5E]]);
        a[5] = 2;
        a[6] = 0;
        a[0x70] = 1;
    }
}


s32 func_8013A858(void *arg0) {
    M2C_FIELD(arg0, u8 *, 6) = (u8) (M2C_FIELD(arg0, u8 *, 6) + 1);
    return 1;
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8013A870);

extern u8 D_800BFB49;

s32 func_8013A8A8(u8 *a)
{
    if (D_800BFB49 != 0) {
        a[0x5E] = 4;
        return 3;
    }
    return 2;
}


s32 func_8013A8D0(void *arg0) {
    return M2C_FIELD(arg0, u8 *, 0x79) == 1;
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8013A8E4);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8013AA98);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8013AB0C);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8013AD90);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8013B118);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8013B7A0);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8013B94C);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8013BB98);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8013BCD0);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8013C050);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8013C18C);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8013C2EC);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8013C7C8);


s32 func_8013C968(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    void *temp_v0;

    temp_v0 = func_800310F4(0x507, -0x32);
    if (temp_v0 != NULL) {
        M2C_FIELD(temp_v0, s8 *, 3) = (s8) arg0;
        M2C_FIELD(temp_v0, s16 *, 0x2C) = (s16) arg1;
        M2C_FIELD(temp_v0, s16 *, 0x2E) = (s16) arg2;
        M2C_FIELD(temp_v0, s16 *, 0x30) = (s16) arg3;
    }
    return (s32) temp_v0;
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8013C9D0);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8013CB08);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8013CB9C);

extern M2C_UNK D_80032918;
void func_8013CC08(void *arg0) {
    M2C_FIELD(arg0, s8 *, 4) = 1;
    M2C_FIELD(arg0, s8 *, 6) = 9;
    M2C_FIELD(arg0, M2C_UNK **, 0x1C) = &D_80032918;
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8013CC28);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8013CCDC);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8013CD78);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8013CE14);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8013CF00);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8013CF70);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8013D040);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8013D0F8);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8013D568);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8013DAFC);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8013DBC0);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8013DD58);


void func_8013DE84(void *arg0) {
    M2C_FIELD(arg0, s16 *, 0x60) = 0xD;
    M2C_FIELD(arg0, s16 *, 0x62) = 0x38F7;
    M2C_FIELD(arg0, s16 *, 0x64) = -0x6F40;
    M2C_FIELD(arg0, s16 *, 0x66) = -0x6F39;
    M2C_FIELD(arg0, s16 *, 0x68) = -0x6040;
    M2C_FIELD(arg0, s16 *, 0x6A) = -0x6039;
    M2C_FIELD(arg0, s16 *, 0x6C) = 0x28;
    M2C_FIELD(arg0, s16 *, 0x6E) = 0x78;
    M2C_FIELD(arg0, s16 *, 0x70) = 0;
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8013DECC);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8013DFE4);


void func_8013E1DC(void *arg0) {
    u16 temp_v0;
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 5);
    switch (temp_v1) {                              /* irregular */
    case 0:
        M2C_FIELD(arg0, u16 *, 0x40) = 0x1EU;
        M2C_FIELD(arg0, s16 *, 0x54) = 0x400;
        M2C_FIELD(arg0, s16 *, 0x56) = 0;
        M2C_FIELD(arg0, s16 *, 0x58) = 0;
        M2C_FIELD(arg0, u8 *, 5) = 1U;
        /* fallthrough */
    case 1:
        temp_v0 = M2C_FIELD(arg0, u16 *, 0x40);
        M2C_FIELD(arg0, u16 *, 0x40) = (u16) (temp_v0 - 1);
        if ((temp_v0 << 0x10) <= 0) {
            M2C_FIELD(arg0, s8 *, 0) = 2;
            M2C_FIELD(arg0, s8 *, 4) = 2;
            return;
        }
        M2C_FIELD(arg0, s32 *, 0x2C) = (s32) (M2C_FIELD(arg0, s32 *, 0x2C) + (M2C_FIELD(arg0, s16 *, 0x4E) << 8));
        M2C_FIELD(arg0, s32 *, 0x30) = (s32) (M2C_FIELD(arg0, s32 *, 0x30) + (M2C_FIELD(arg0, s16 *, 0x50) << 8));
        M2C_FIELD(arg0, s32 *, 0x34) = (s32) (M2C_FIELD(arg0, s32 *, 0x34) + (M2C_FIELD(arg0, s16 *, 0x52) << 8));
        return;
    }
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", f_SpawnSnowFireflyAuxiliaryActor);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8013E3D4);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8013E510);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8013E64C);

INCLUDE_ASM("asm/a04/nonmatchings/a04", f_UpdateCapturedSnowFireflyMotion);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8013E910);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8013EBE4);


void func_8013ECF8(void *arg0) {
    u16 temp_v0;
    u8 temp_v1;
    void *temp_a2;

    temp_v1 = M2C_FIELD(arg0, u8 *, 5);
    temp_a2 = M2C_FIELD(arg0, void **, 0x10);
    switch (temp_v1) {                              /* irregular */
    case 0:
        M2C_FIELD(arg0, u16 *, 0x40) = 0x3CU;
        M2C_FIELD(arg0, s16 *, 0x60) = 0;
        M2C_FIELD(arg0, s16 *, 0x62) = -0x20;
        M2C_FIELD(arg0, s16 *, 0x64) = 0;
        M2C_FIELD(arg0, u8 *, 5) = (u8) (M2C_FIELD(arg0, u8 *, 5) + 1);
        /* fallthrough */
    case 1:
        temp_v0 = M2C_FIELD(arg0, u16 *, 0x40) - 1;
        M2C_FIELD(arg0, u16 *, 0x40) = temp_v0;
        if ((temp_v0 << 0x10) == 0) {
            M2C_FIELD(arg0, u8 *, 5) = (u8) (M2C_FIELD(arg0, u8 *, 5) + 1);
        }
        func_8004BD64(arg0, 1, M2C_FIELD(temp_a2, s32 *, 0xDC), 0, arg0 + 0x60);
        return;
    case 2:
        func_8004D4C4(0x75, 1, temp_a2);
        func_80040B48(0x6D);
        M2C_FIELD(arg0, s8 *, 4) = 3;
        return;
    }
}

extern s32 D_800BF858;
extern s16 D_800E7FEE;
void func_8013EDD8(void *arg0) {
    u8 temp_a1;
    u8 temp_v0;

    if (D_800E7FEE != 0) {
        if (M2C_FIELD(arg0, u8 *, 0x5E) == 2) {
            D_800BF858 = 0;
            D_800BF870.pad1[0x19C] += 1;
        } else {
            temp_a1 = M2C_FIELD(arg0, u8 *, 3);
            temp_v0 = D_800BF870.pad1[0x19B] | (1 << temp_a1);
            D_800BF870.pad1[0x19B] = temp_v0;
            if ((temp_v0 & 0x1F) == 0x1F) {
                func_80040C00(0x6C, temp_a1);
            }
        }
        func_80040B48(0x6D);
        func_8004D4C4(0x75, 1);
        M2C_FIELD(arg0, s8 *, 4) = 3;
    }
}

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8013EE84);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8013F0DC);

INCLUDE_ASM("asm/a04/nonmatchings/a04", func_8013F418);

INCLUDE_ASM("asm/a04/nonmatchings/a04", f_UpdateThirdReadyOrNotKujaraDialogue);

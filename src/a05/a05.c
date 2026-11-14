#include "common.h"
#include "game.h"
#include "m2c.h"

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_0x8010a32c);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8010A530);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8010A704);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8010A7FC);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8010A824);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8010A854);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8010AA70);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8010ABA0);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8010AD64);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8010AF84);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8010B424);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8010B5E8);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8010B724);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8010B930);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8010BB54);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8010BCB8);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8010BE54);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8010BFAC);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8010C410);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8010C548);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8010C6E0);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8010C990);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8010CDEC);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8010D0C4);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8010D308);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8010D490);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8010D720);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8010DB50);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8010DDAC);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8010E240);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8010E36C);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8010E4B0);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8010E5A8);

extern s16 D_80140E38;
extern void *D_80140E3C;
void func_8010E5C4(s32 arg0) {
    void *temp_a0;

    if (D_80140E38 < 0x40) {
        temp_a0 = D_80140E3C;
        D_80140E3C = temp_a0 - 4;
        M2C_FIELD(temp_a0, s32 *, -4) = arg0;
        D_80140E38 = (u16) D_80140E38 + 1;
    }
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8010E604);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8010E698);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8010E760);

extern s8 D_1F80009C[];

void func_8010E7EC(void *arg0, void *arg1) {
    if (!(M2C_FIELD(arg0, u16 *, 0x17E) & 0x200) && (func_80022F04() != 0) && !(M2C_FIELD(arg0, u8 *, 0) & 6)) {
        M2C_FIELD(arg0, s8 *, 0x2B) = (s8) ((s32) *((s32 *)D_1F80009C) >> 4);
        func_80022D08(arg0, 0, 1, 1);
        func_80058304(arg0, 0);
        M2C_FIELD(arg1, s8 *, 0) = 2;
        M2C_FIELD(arg1, s8 *, 4) = 2;
        M2C_FIELD(arg1, s8 *, 5) = 0;
        M2C_FIELD(arg1, s8 *, 6) = 0;
    }
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8010E88C);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8010E974);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8010EA50);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8010EAB4);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8010EBA4);

extern s8 D_1F800182[];

void func_8010EC7C(s32 arg0, u8 *arg1) {
    s32 var_v0;

    if (func_80022F04() != 0) {
        if (*arg1 & 0xA) {
            var_v0 = func_8001E860(arg0, arg1, 0, 0) & 0x80;
        } else {
            var_v0 = func_8001DC9C(arg0, arg1, 0, 1) & 0x80;
        }
        if (var_v0 == 0) {
            *((s8 *)D_1F800182) = 0;
        }
    }
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8010ED00);


void func_8010EDA8(void *arg0, void *arg1) {
    if (func_800240FC() != 0) {
        M2C_FIELD(arg0, s8 *, 0) = 2;
        M2C_FIELD(arg0, s8 *, 4) = 2;
        M2C_FIELD(arg0, s8 *, 6) = 0;
        if (M2C_FIELD(arg1, u8 *, 0x5E) == 0) {
            M2C_FIELD(arg0, s8 *, 5) = 1;
            return;
        }
        M2C_FIELD(arg0, s8 *, 5) = 2;
    }
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8010EE08);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8010EF30);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8010EFA0);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8010F034);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8010F0F8);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8010F304);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8010F948);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8010FF20);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80110074);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80110380);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801105FC);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8011099C);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80110CB8);

extern s8 D_1F800138[];
extern s8 D_1F80019B[];

void func_80110F38(void) {
    func_80045258(M2C_FIELD(*((volatile void **)D_1F800138), u8 *, 0x6E), 0xF);
    *((volatile s8 *)D_1F80019B) = 1;
    func_80051FB4();
}


s32 func_80110F78(s32 arg0, s32 arg1) {
    void *temp_a1;

    temp_a1 = M2C_FIELD(arg0, void **, 0x158);
    if (M2C_FIELD(temp_a1, u8 *, 2) == 0x41) {
        func_80110074(arg0, (s32) temp_a1, arg1);
    }
    return 0;
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80110FB4);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8011105C);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801110A4);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801112B4);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80111480);

extern s8 D_1F800138[];
extern s8 D_1F80019B[];

void func_80111A74(void) {
    func_80045258(M2C_FIELD(*((volatile void **)D_1F800138), u8 *, 0x6E), 0xF);
    *((volatile s8 *)D_1F80019B) = 1;
    func_80051FB4();
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80111AB4);

INCLUDE_ASM("asm/a05/nonmatchings/a05", f_SpawnKujaraSummitSceneActorsFromPlacementTable);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80112020);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801121AC);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801124AC);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801124FC);


void func_801126C0(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 4);
    switch (temp_v1) {                              /* irregular */
    case 0:
        if (M2C_FIELD(arg0, u8 *, 3) == 0) {
            func_8004BEF4(arg0);
        }
        M2C_FIELD(arg0, u8 *, 4) = (u8) (M2C_FIELD(arg0, u8 *, 4) + 1);
        return;
    case 1:
        if (M2C_FIELD(arg0, u8 *, 3) == 0) {
            func_801124FC(arg0);
            return;
        }
    case 2:
        return;
    case 3:
        func_8007A624(arg0);
        break;
    }
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80112778);

INCLUDE_ASM("asm/a05/nonmatchings/a05", f_UpdateKujaraSummitQuestPickupActor);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80112CD8);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80112D28);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80112D8C);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80112DBC);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80112E38);


void func_80112F30(void *arg0) {
    func_8004D4C4(0x4E, 1);
    func_8004B0D8(arg0);
    D_800BF870.pad1[0x149] |= 2;
    func_80040B48(0x7A);
    M2C_FIELD(arg0, s8 *, 4) = 3;
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80112F88);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8011318C);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801131E0);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80113294);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801132F0);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80113348);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80113468);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801136A8);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80113A6C);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80113D24);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80114178);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801141F8);

INCLUDE_ASM("asm/a05/nonmatchings/a05", f_UpdateKujaraHotSpringActor);


s32 func_801145A0(void *arg0) {
    s32 temp_a0;
    s32 temp_a2;
    s32 var_s0;
    void *var_s1;

    var_s0 = 0;
    var_s1 = arg0;
    do {
        temp_a0 = M2C_FIELD(var_s1, s32 *, 0xC0);
        var_s1 += 4;
        temp_a2 = var_s0;
        var_s0 += 1;
        func_80051B04(temp_a0, 0x21, temp_a2);
    } while (var_s0 < 0xD);
    return 1;
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801145F0);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801146E8);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80114838);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80114874);


void func_80114934(void *arg0) {
    u8 temp_v1;

    if ((M2C_FIELD(arg0, u8 *, 0x5F) != 0) || ((temp_v1 = M2C_FIELD(arg0, u8 *, 0x29), (temp_v1 != 0)) && (temp_v1 != 0x80))) {
        func_80027144(M2C_FIELD(M2C_FIELD(arg0, void **, 0xC0), s32 *, 0x40), arg0 + 0x2C, 0x700, 8);
        func_80074590(0xC, 0, 0);
        M2C_FIELD(arg0, s8 *, 4) = 3;
    }
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801149A8);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80114CC8);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80114F88);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80115198);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8011541C);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80115478);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80115498);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801154B8);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801154D8);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801154F8);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801155A4);

extern void *D_800BF868;
s32 func_80115650(void) {
    M2C_FIELD(D_800BF868, s8 *, 4) = 3;
    return 1;
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80115668);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80115740);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80115810);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801158E0);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801159B0);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80115B48);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80115E04);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801160CC);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8011632C);


void func_801164D0(s32 arg0) {
    s32 temp_s0;

    temp_s0 = arg0 + 0x2C;
    func_800313A0(0x606, temp_s0, -0xA, arg0 + 0x54);
    func_8003116C(0x607, temp_s0, -0xA);
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80116518);


void func_801165BC(void *arg0) {
    M2C_UNK var_a0;

    var_a0 = 0x612;
    if (M2C_FIELD(arg0, s16 *, 0x52) >= 0) {
        var_a0 = 0x60F;
    }
    func_8003116C(var_a0, arg0 + 0x2C, -0xA);
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801165F8);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801166F4);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801169D0);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80116BE4);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8011711C);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80117154);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801171BC);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80117404);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801174AC);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801177EC);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80117894);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80117984);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80117CC4);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80117D6C);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80117EE0);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8011807C);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80118238);

INCLUDE_ASM("asm/a05/nonmatchings/a05", f_UpdateWhosTheLiarSisterActorA);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801189B4);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80118A9C);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80118C24);

INCLUDE_ASM("asm/a05/nonmatchings/a05", f_UpdateWhosTheLiarSisterActorB);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8011917C);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80119310);

INCLUDE_ASM("asm/a05/nonmatchings/a05", f_UpdateWhosTheLiarSisterActorC);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801198B8);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80119E24);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8011A03C);

INCLUDE_ASM("asm/a05/nonmatchings/a05", f_UpdateStaticExplosionQuestActor);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8011A5F0);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8011A678);

extern s8 D_1F800233[];

s32 func_8011A7B4(void *arg0) {
    *((s8 *)D_1F800233) = 0;
    M2C_FIELD(arg0, s16 *, 0x42) = 0;
    M2C_FIELD(arg0, u8 *, 6) = (u8) (M2C_FIELD(arg0, u8 *, 6) + 1);
    return 1;
}

extern s8 D_1F8000F2[];
extern void *D_800BF844;

s32 func_8011A7D4(s32 arg0) {
    u8 temp_v1;
    void *temp_a0;
    void *temp_v0;

    temp_v1 = M2C_FIELD(arg0, u8 *, 0x78);
    switch (temp_v1) {                              /* irregular */
    case 0:
        temp_v0 = func_8006FB0C(arg0, 0x18);
        M2C_FIELD(arg0, void **, 0x14) = temp_v0;
        D_800BF844 = temp_v0;
        temp_a0 = M2C_FIELD(arg0, void **, 0x14);
        if (temp_a0 != NULL) {
            M2C_FIELD(temp_a0, s16 *, 0x60) = 0x60;
            M2C_FIELD(temp_a0, s16 *, 0x62) = 0x30;
            M2C_FIELD(temp_a0, s8 *, 0x5E) = 1;
            M2C_FIELD(temp_a0, u8 *, 0x5F) = (u8) (M2C_FIELD(temp_a0, u8 *, 0x5F) | 1);
            M2C_FIELD(arg0, u8 *, 0x78) = (u8) (M2C_FIELD(arg0, u8 *, 0x78) + 1);
        }
        return 0;
    case 1:
        M2C_FIELD(M2C_FIELD(arg0, void **, 0x14), s16 *, 0x56) = (s16) (-(s32) *((u16 *)D_1F8000F2) & 0xFFF);
        return 1;
    default:
        return 0;
    }
}


s32 func_8011A894(s32 arg0) {
    func_8011FB18(arg0, 0xA);
    func_8011FB18(arg0, 0xB);
    func_8011FB18(arg0, 0xC);
    return 1;
}


s32 func_8011A8D8(s32 arg0) {
    s32 temp_a0;

    if (M2C_FIELD(arg0, s16 *, 0x72) == 0) {
        M2C_FIELD(arg0, s32 *, 0x14) = func_801310F8(arg0);
    } else {
        temp_a0 = M2C_FIELD(arg0, s32 *, 0x14);
        if (temp_a0 != 0) {
            M2C_FIELD(temp_a0, s8 *, 4) = 3;
        }
    }
    return 1;
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8011A930);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8011A95C);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8011ACC4);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8011AE5C);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8011B210);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8011B3E8);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8011B9EC);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8011BB94);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8011BCB0);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8011BE44);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8011BFA4);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8011C1D4);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8011C2E4);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8011C790);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8011C988);


s32 func_8011CAA0(void *arg0) {
    return func_80077768((s16) (func_80085690((s16) (M2C_FIELD(arg0, u16 *, 0x64) - M2C_FIELD(arg0, u16 *, 0x36)), (s16) (M2C_FIELD(arg0, u16 *, 0x62) - M2C_FIELD(arg0, u16 *, 0x2E))) * -1), M2C_FIELD(arg0, s16 *, 0x56), 0) != 0;
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8011CB08);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8011CB9C);

extern M2C_UNK D_80141E14;
void func_8011CC1C(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 6) == 0) {
        M2C_FIELD(arg0, u8 *, 0x1B) = (u8) (M2C_FIELD(arg0, u8 *, 0x1B) & 0xBF);
        func_80051B04(M2C_FIELD(arg0, s32 *, 0xC0), 0x19, 8);
        func_80077C40(arg0, &D_80141E14, 0x1C);
        M2C_FIELD(M2C_FIELD(arg0, void **, 0xC4), s16 *, 0x38) = 0x1000;
        M2C_FIELD(M2C_FIELD(arg0, void **, 0xC4), s16 *, 0x3A) = 0x1000;
        M2C_FIELD(M2C_FIELD(arg0, void **, 0xC4), s16 *, 0x3C) = 0x1000;
        func_80026100(4);
        M2C_FIELD(arg0, s16 *, 0x84) = 0x32;
        M2C_FIELD(arg0, s16 *, 0x86) = 0x92;
        M2C_FIELD(arg0, u8 *, 6) = (u8) (M2C_FIELD(arg0, u8 *, 6) + 1);
    }
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8011CCBC);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8011CD30);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8011D70C);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8011DA2C);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8011DDC0);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8011E000);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8011E3AC);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8011E4C4);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8011E870);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8011EB84);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8011EC58);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8011ECEC);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8011EDCC);


void func_8011EEBC(void *arg0, s16 arg1) {
    if (M2C_FIELD(arg0, u8 *, 0xBE) == 0) {
        M2C_FIELD(arg0, s16 *, 0x44) = arg1;
        return;
    }
    M2C_FIELD(arg0, s16 *, 0x44) = (s16) -arg1;
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8011EEDC);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8011EF40);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8011F1BC);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8011F374);

INCLUDE_ASM("asm/a05/nonmatchings/a05", f_UpdateReturnedKujaraActor);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8011FB18);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8011FB88);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8011FE08);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8011FF44);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80120160);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80120378);

INCLUDE_ASM("asm/a05/nonmatchings/a05", f_UpdateIceBlockAndSculptureQuestActor);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80120B48);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80120C64);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80120D50);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80120E58);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80120F34);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80121010);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801210EC);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801211C8);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801215BC);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801217E8);

extern u8 D_800BF80F;
extern u8 D_800BFB02;
extern M2C_UNK D_8013EAC0;
extern M2C_UNK D_80140F7C;
void func_80121A50(void *arg0) {
    u16 temp_v0;
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 6);
    switch (temp_v1) {                              /* irregular */
    case 0:
        if (D_800BF80F == 0) {
            M2C_FIELD(arg0, u8 *, 6) = 1U;
            func_80042354(1, 1);
            if ((u8) D_800BF870.pad1[0x159] < 9U) {
                D_800BF870.pad1[0x159] += 1;
            }
            D_800BF870.pad1[0x152] = 0;
            return;
        }
        return;
    case 1:
        M2C_FIELD(arg0, u8 *, 6) = 2U;
        func_80040CDC(arg0, &D_80140F7C, &D_8013EAC0);
        M2C_FIELD(arg0, u8 *, 0x70) = 1U;
        return;
    case 2:
        func_80041098(arg0);
        if (M2C_FIELD(arg0, u8 *, 0x70) == 0xFF) {
            if (D_800BFB02 == 0) {
                M2C_FIELD(arg0, s8 *, 5) = 6;
                M2C_FIELD(arg0, u8 *, 6) = 0U;
                func_80042310();
                return;
            }
            M2C_FIELD(arg0, u16 *, 0x40) = 0x3CU;
            M2C_FIELD(arg0, u8 *, 6) = (u8) (M2C_FIELD(arg0, u8 *, 6) + 1);
            return;
        }
        break;
    case 3:
        temp_v0 = M2C_FIELD(arg0, u16 *, 0x40) - 1;
        M2C_FIELD(arg0, u16 *, 0x40) = temp_v0;
        if ((temp_v0 << 0x10) == 0) {
            M2C_FIELD(arg0, s8 *, 5) = 6;
            M2C_FIELD(arg0, u8 *, 6) = 1U;
        }
        break;
    }
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80121BA0);

INCLUDE_ASM("asm/a05/nonmatchings/a05", f_UpdateKujaraWashingExpertActor);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801223FC);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801224E4);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801225CC);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801226A4);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80122780);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80122888);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80122960);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80122A54);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80122B24);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80122BFC);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80122CD4);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80122E10);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80123108);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80123318);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80123880);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80123CE8);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801240E4);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801244DC);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80124828);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80124A64);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80124FE4);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801251F4);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80125560);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801257E8);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80125A20);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80125BA4);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8012640C);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801264D0);


void func_80126598(void *arg0, s32 arg1) {
    s32 temp_lo;
    s32 temp_lo_2;
    s32 temp_v1;

    M2C_FIELD(arg0, u16 *, 0x58) = (u16) (M2C_FIELD(arg0, u16 *, 0x58) + 0x200);
    if (arg1 == 0) {
        M2C_FIELD(arg0, s32 *, 0x30) = (s32) (M2C_FIELD(arg0, s32 *, 0x30) + (func_80083E80(M2C_FIELD(arg0, s16 *, 0x52)) * M2C_FIELD(arg0, s16 *, 0x44) * 0x10));
    }
    temp_v1 = (s32) (func_80083F50(M2C_FIELD(arg0, s16 *, 0x52)) * M2C_FIELD(arg0, s16 *, 0x44)) >> 4;
    temp_lo = M2C_FIELD(arg0, s16 *, 0x48) * temp_v1;
    temp_lo_2 = M2C_FIELD(arg0, s16 *, 0x4C) * temp_v1;
    M2C_FIELD(arg0, s32 *, 0x2C) = (s32) (M2C_FIELD(arg0, s32 *, 0x2C) + temp_lo);
    M2C_FIELD(arg0, s32 *, 0x34) = (s32) (M2C_FIELD(arg0, s32 *, 0x34) + temp_lo_2);
    if (!(M2C_FIELD(arg0, u8 *, 0x46) & 8)) {
        M2C_FIELD(arg0, s16 *, 0x56) = func_80085690(-temp_lo_2, temp_lo);
    }
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80126664);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801266E8);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80126788);


void func_80126844(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s16 *, 0x44) = (s16) ((s32) (arg1 << 8) / (s16) M2C_FIELD(arg0, s16 *, 0x6A));
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80126880);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80126924);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801269B8);


void func_80126AB4(void) {
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80126ABC);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80126B34);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80126CD4);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80126E4C);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80127168);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801271CC);


void func_801272EC(void *arg0) {
    func_8004D4C4(0x3B, 1);
    func_8004B0D8(arg0);
    M2C_FIELD(arg0, s8 *, 4) = 3;
    D_800BF870.pad1[0x1D8] |= 1;
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80127340);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801274F8);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8012761C);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80127734);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801279B4);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80127C4C);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80127C9C);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80127D70);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80127E30);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80127F18);


void func_80127F7C(void *arg0) {
    s32 temp_v0_2;
    u32 temp_v0;

    temp_v0 = (u16) M2C_FIELD(M2C_FIELD(arg0, void **, 0xC0), u16 *, 0x38) >> 5;
    M2C_FIELD(arg0, s16 *, 0x80) = (s16) temp_v0;
    M2C_FIELD(arg0, s16 *, 0x82) = (s16) (temp_v0 * 2);
    temp_v0_2 = (s32) (M2C_FIELD(M2C_FIELD(arg0, void **, 0xC0), u16 *, 0x3A) * 0x113) >> 0xC;
    M2C_FIELD(arg0, s16 *, 0x84) = (s16) temp_v0_2;
    M2C_FIELD(arg0, s16 *, 0x86) = (s16) (temp_v0_2 + 0x32);
}


void func_80127FD0(void *arg0) {
    if (M2C_FIELD(arg0, s16 *, 0x62) == 0) {
        M2C_FIELD(arg0, s16 *, 0x62) = 1;
        func_80051B04(M2C_FIELD(arg0, s32 *, 0xC0), 0xC, 0x52);
        func_8003116C(0x24, arg0 + 0x2C, -0xA);
    }
    M2C_FIELD(arg0, s8 *, 0x2B) = 0;
    M2C_FIELD(arg0, s8 *, 0) = 1;
    M2C_FIELD(arg0, s8 *, 4) = 1;
    M2C_FIELD(arg0, s8 *, 5) = 0;
    M2C_FIELD(arg0, s8 *, 6) = 0;
}

extern s8 D_1F800207[];
extern u16 D_800BFE56;

s32 func_80128040(void *arg0) {
    if ((D_800BFE56 & 0x20) || (M2C_FIELD(arg0, u8 *, 0x2A) == *((u8 *)D_1F800207))) {
        return 0;
    }
    M2C_FIELD(arg0, s16 *, 0x62) = 0;
    func_80051B04(M2C_FIELD(arg0, s32 *, 0xC0), 0xC, 0x51);
    return 1;
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8012809C);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801284F0);

INCLUDE_ASM("asm/a05/nonmatchings/a05", f_UpdateKujaraWashingShedEntrance);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80128904);

INCLUDE_ASM("asm/a05/nonmatchings/a05", Door);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80128CF0);

INCLUDE_ASM("asm/a05/nonmatchings/a05", f_UpdateKujaraInteriorEntranceActor);


void func_801294DC(s32 arg0) {
    func_80073328();
    func_800735F4(arg0, 0x5C);
}


void func_8012950C(void) {
    func_801284F0();
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8012952C);


void func_801295C4(s32 arg0) {
    func_801284F0();
    func_800735F4(arg0, 0x5A);
}


void func_801295F4(s32 arg0) {
    func_80073328();
    func_800735F4(arg0, 0x6E);
}


void func_80129624(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 4);
    switch (temp_v1) {                              /* irregular */
    case 0:
        if (func_80051B70(arg0, 0xC, 0x21) == 0) {
            M2C_FIELD(arg0, u8 *, 0xD) = (u8) (M2C_FIELD(arg0, u8 *, 0xD) | 4);
            M2C_FIELD(M2C_FIELD(arg0, void **, 0xC0), s8 *, 0x3F) = 0x3C;
            M2C_FIELD(arg0, s8 *, 0) = 1;
            M2C_FIELD(arg0, s16 *, 0x80) = 0xA0;
            M2C_FIELD(arg0, s16 *, 0x82) = 0x140;
            M2C_FIELD(arg0, s16 *, 0x84) = 0xA0;
            M2C_FIELD(arg0, s16 *, 0x86) = 0x140;
            M2C_FIELD(arg0, s16 *, 0x58) = 0;
            M2C_FIELD(arg0, s16 *, 0x56) = 0;
            M2C_FIELD(arg0, s16 *, 0x54) = 0;
            if (func_8004766C(arg0) != 0) {
                M2C_FIELD(arg0, u8 *, 4) = (u8) (M2C_FIELD(arg0, u8 *, 4) + 1);
                return;
            }
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


void func_80129730(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 4);
    switch (temp_v1) {                              /* irregular */
    case 0:
        M2C_FIELD(arg0, s16 *, 0x80) = 0x40;
        M2C_FIELD(arg0, s16 *, 0x82) = 0x80;
        M2C_FIELD(arg0, s16 *, 0x84) = 0x1F4;
        M2C_FIELD(arg0, s8 *, 8) = 0;
        M2C_FIELD(arg0, s8 *, 9) = 0;
        M2C_FIELD(arg0, s8 *, 0) = 1;
        M2C_FIELD(arg0, s8 *, 0xB) = 0;
        M2C_FIELD(arg0, s8 *, 0x29) = 0;
        M2C_FIELD(arg0, s16 *, 0x86) = 0x2BC;
        M2C_FIELD(arg0, u8 *, 4) = (u8) (M2C_FIELD(arg0, u8 *, 4) + 1);
        return;
    case 1:
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

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801297EC);


void func_801298E0(void *arg0) {
    M2C_FIELD(arg0, s16 *, 0x80) = 0x8C;
    M2C_FIELD(arg0, s16 *, 0x82) = 0x118;
    M2C_FIELD(arg0, s16 *, 0x84) = 0x1F4;
    M2C_FIELD(arg0, s16 *, 0x86) = 0x3E8;
    M2C_FIELD(arg0, s8 *, 0x2A) = 4;
    M2C_FIELD(arg0, s32 *, 0x2C) = 0x35200000;
    M2C_FIELD(arg0, s32 *, 0x30) = 0xCEC80000;
    M2C_FIELD(arg0, s32 *, 0x34) = 0x35E80000;
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80129924);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8012999C);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80129BF8);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80129E68);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8012A0C8);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8012A244);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8012A634);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8012AA64);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8012ABFC);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8012AEFC);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8012B118);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8012B188);

INCLUDE_ASM("asm/a05/nonmatchings/a05", f_UpdateIceBlockAndSculptureActor);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8012B824);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8012BBDC);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8012BCE8);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8012BFA8);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8012C1F8);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8012C44C);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8012C628);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8012C858);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8012C978);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8012CA78);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8012CE34);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8012D0C8);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8012D340);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8012D5B8);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8012D67C);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8012D908);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8012DBA0);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8012DD44);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8012DE08);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8012DE94);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8012DF18);


void func_8012DF8C(void *arg0) {
    M2C_FIELD(arg0, s8 *, 0) = 1;
    M2C_FIELD(arg0, s8 *, 4) = 1;
    M2C_FIELD(arg0, s8 *, 5) = 0;
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8012DFA0);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8012E024);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8012E0C8);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8012E340);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8012E454);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8012E918);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8012ECA0);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8012EDC8);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8012EF0C);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8012F0F4);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8012F280);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8012F404);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8012F548);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8012F7C0);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8012F8E8);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8012FCE4);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8012FF54);

INCLUDE_ASM("asm/a05/nonmatchings/a05", f_UpdateKujaraSummitMechanismActor);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801307E0);


void func_8013084C(void *arg0) {
    M2C_FIELD(arg0, s8 *, 1) = 1;
    func_80077B5C();
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80130870);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801308D8);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801309B8);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80130A2C);


s32 func_80130AA0(s32 arg0, s32 arg1) {
    void *var_v0;
    void *var_v1;

    if (arg0 == 0) {
        var_v0 = func_800310F4(arg1, -0x14);
        var_v1 = var_v0;
    } else {
        var_v0 = func_8003116C(arg1, arg0, -0x14);
        var_v1 = var_v0;
    }
    if (var_v1 != NULL) {
        var_v0 = (void *) (M2C_FIELD(var_v1, u8 *, 0x28) | 0x80);
        M2C_FIELD(var_v1, u8 *, 0x28) = (u8) var_v0;
    }
    return (s32) var_v0;
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80130AFC);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80130BC8);

extern u8 D_800BF9C6;
void func_80130C00(void *arg0) {
    if ((u8) D_800BF9C6 >= 0x15U) {
        M2C_FIELD(arg0, s8 *, 4) = 2;
    }
    func_800517F8(arg0);
    M2C_FIELD(arg0, s8 *, 1) = 1;
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80130C48);

extern u8 D_800BF9C6;
void func_80130C80(void *arg0) {
    if ((u8) D_800BF9C6 >= 0x15U) {
        M2C_FIELD(arg0, s8 *, 4) = 2;
    }
    func_800517F8(arg0);
    M2C_FIELD(arg0, s8 *, 1) = 1;
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80130CC8);


void func_80130D20(void *arg0) {
    M2C_FIELD(arg0, s8 *, 1) = 1;
    func_80077B5C();
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80130D44);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80130DB4);


void func_80130E40(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x5E) == 0) {
        func_8012FF54();
    }
    M2C_FIELD(arg0, s8 *, 1) = 1;
    func_80077B5C(arg0);
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80130E88);


void func_80130F10(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x5E) == 0) {
        func_8012FF54();
    }
    M2C_FIELD(arg0, s8 *, 1) = 1;
    func_80077B5C(arg0);
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80130F58);


void func_80130FE0(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x5E) == 0) {
        func_8012FF54();
    }
    M2C_FIELD(arg0, s8 *, 1) = 1;
    func_80077B5C(arg0);
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80131028);


void func_801310B0(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x5E) == 0) {
        func_8012FF54();
    }
    M2C_FIELD(arg0, s8 *, 1) = 1;
    func_80077B5C(arg0);
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801310F8);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8013115C);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80131274);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801313B4);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80131520);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801316C4);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80131824);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80131988);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80131B18);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80131C90);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80131E10);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80131F80);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80132154);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801322E0);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80132418);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801326F4);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80132750);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801327A4);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801327F8);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80132874);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801328DC);


void func_801329C0(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 5) == 0) {
        M2C_FIELD(arg0, u8 *, 5) = 1U;
        func_80074590(0x92, 0, 0);
    }
    func_801124AC(arg0);
    func_800517F8(arg0);
    M2C_FIELD(arg0, s8 *, 1) = 1;
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80132A1C);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80132A80);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80132AC8);


void func_80132B54(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x10) = 0;
}

extern s32 D_800ECF80;
extern M2C_UNK D_80140E40;
void func_80132B5C(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x3C) = (s32) D_800ECF80;
    func_80077B38(arg0, &D_80140E40, (func_8009A450() & 3) + 0xE);
    M2C_FIELD(arg0, s8 *, 0xD) = 0;
    M2C_FIELD(arg0, s16 *, 0x5C) = 0;
    M2C_FIELD(arg0, s8 *, 0xB) = 0x10;
    M2C_FIELD(arg0, s16 *, 0x5A) = 0;
    M2C_FIELD(arg0, s8 *, 0x47) = 0;
    M2C_FIELD(arg0, s8 *, 8) = 0;
    M2C_FIELD(arg0, s8 *, 0x5E) = (s8) (func_8009A450() & 3);
    M2C_FIELD(arg0, s16 *, 0x2E) = 0x3A41;
    M2C_FIELD(arg0, s16 *, 0x32) = -0x2D37;
    M2C_FIELD(arg0, s16 *, 0x36) = 0x46BE;
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80132BE4);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80132DE4);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8013311C);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801332B0);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801333F0);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801335A0);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8013360C);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801337BC);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80133878);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801339A4);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80133A3C);

extern s32 D_800ECF80;
extern M2C_UNK D_80140E40;
void func_80133CCC(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 4);
    switch (temp_v1) {                              /* irregular */
    case 0:
        M2C_FIELD(arg0, s32 *, 0x3C) = (s32) D_800ECF80;
        func_80077B38(arg0, &D_80140E40, M2C_FIELD(arg0, u8 *, 3) + 0x14);
        M2C_FIELD(arg0, s8 *, 0xB) = 0x11;
        M2C_FIELD(arg0, s16 *, 0x7E) = 0x1800;
        M2C_FIELD(arg0, s16 *, 0x7C) = 0x1800;
        M2C_FIELD(arg0, s16 *, 0x7A) = 0x1800;
        M2C_FIELD(arg0, s8 *, 0xD) = 0;
        M2C_FIELD(arg0, s16 *, 0x5C) = 0;
        M2C_FIELD(arg0, s8 *, 0x47) = 0;
        M2C_FIELD(arg0, s16 *, 0x5A) = 0;
        M2C_FIELD(arg0, s8 *, 8) = 0xA;
        M2C_FIELD(arg0, u8 *, 4) = (u8) (M2C_FIELD(arg0, u8 *, 4) + 1);
        return;
    case 1:
        func_80133A3C(arg0);
        return;
    case 3:
        func_8007A624(arg0);
        /* fallthrough */
    case 2:
        return;
    }
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80133DA4);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80133E8C);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80134000);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801344F4);


void func_8013466C(void *arg0) {
    u8 temp_v1;
    void *temp_s1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 4);
    temp_s1 = M2C_FIELD(arg0, void **, 0x10);
    switch (temp_v1) {                              /* irregular */
    case 0:
        func_80134000(arg0, temp_s1);
        M2C_FIELD(arg0, u8 *, 4) = (u8) (M2C_FIELD(arg0, u8 *, 4) + 1);
        return;
    case 1:
        M2C_FIELD(arg0, s16 *, 0x2E) = (s16) (M2C_FIELD(temp_s1, u16 *, 0x2E) + M2C_FIELD(arg0, u16 *, 0x60));
        M2C_FIELD(arg0, s16 *, 0x32) = (s16) (M2C_FIELD(temp_s1, u16 *, 0x32) + M2C_FIELD(arg0, u16 *, 0x62));
        M2C_FIELD(arg0, s16 *, 0x36) = (s16) (M2C_FIELD(temp_s1, u16 *, 0x36) + M2C_FIELD(arg0, u16 *, 0x64));
        if (func_800777FC(arg0) != 0) {
            if (M2C_FIELD(arg0, u8 *, 3) & 0x80) {
                if (M2C_FIELD(arg0, u8 *, 0xBE) == 0) {
                    M2C_FIELD(arg0, u16 *, 0x58) = (u16) M2C_FIELD(temp_s1, u16 *, 0x58);
                } else {
                    M2C_FIELD(arg0, u16 *, 0x58) = (u16) (-(s32) M2C_FIELD(temp_s1, u16 *, 0x58) & 0xFFF);
                }
                func_800517F8(arg0);
                return;
            }
            M2C_FIELD(arg0, u16 *, 0x5A) = (u16) M2C_FIELD(temp_s1, u16 *, 0x58);
            return;
        }
        return;
    case 2:
        func_800777FC(arg0);
        func_801344F4(arg0);
        return;
    case 3:
        func_8007A624(arg0);
        break;
    }
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801347C0);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8013484C);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80134B74);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80134F1C);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801350B4);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801351DC);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8013544C);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8013590C);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80135ED8);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8013606C);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801362CC);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80136434);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80136488);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80136788);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80136CB0);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80136CDC);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80136F28);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8013725C);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801374E0);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801376F4);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8013788C);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80137A50);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80137BDC);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80137D6C);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80137F0C);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801380EC);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80138220);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80138404);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801384F8);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80138758);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80138904);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80138B38);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80138C64);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80138E88);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801390B8);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80139260);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8013951C);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_801399E8);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80139C0C);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80139E2C);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80139E6C);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80139ED8);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_80139F44);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8013A078);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8013A104);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8013A1D0);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8013A2AC);


void func_8013A3B8(void *arg0) {
    if ((u8) M2C_FIELD(M2C_FIELD(arg0, void **, 0x10), u8 *, 4) >= 2U) {
        M2C_FIELD(arg0, s8 *, 4) = 3;
    }
    func_80032918();
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8013A3F8);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8013A460);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8013A548);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8013A5F0);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8013A700);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8013A7B8);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8013A88C);

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8013AA50);

extern s16 D_800BED82;
extern M2C_UNK D_80140508;
extern M2C_UNK D_801406AC;
void func_8013AC40(void) {
    func_80075448(0xB, &D_801406AC, 0x10, D_800BED82);
    func_80075448(0xC, &D_80140508, 0x10, D_800BED82);
}

INCLUDE_ASM("asm/a05/nonmatchings/a05", func_8013AC90);

INCLUDE_ASM("asm/a05/nonmatchings/a05", f_UpdateThreeSistersCutsceneActorC);

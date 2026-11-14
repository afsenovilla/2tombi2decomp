#include "common.h"
#include "game.h"
#include "m2c.h"

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8010A528);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8010A6E8);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8010A73C);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8010A7D8);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8010A868);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8010A8D0);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8010ACB8);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8010AEC4);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8010B068);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8010B2D0);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8010B458);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8010B634);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8010B8B8);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8010BABC);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8010BD80);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8010BEBC);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8010C510);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8010C6E4);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8010C8E4);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8010CF30);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8010CFAC);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8010D288);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8010D6B4);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8010DA78);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8010DBE4);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8010E1F4);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8010E3D8);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8010EA30);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8010EBA8);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8010ED88);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8010F01C);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8010F63C);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8010F798);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8010F84C);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8010F8DC);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8010F948);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8010F9E4);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8010FAB0);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8010FBFC);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8010FD30);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8010FE90);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8010FFF4);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_801101D4);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80110370);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8011053C);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_801106F0);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_801108A0);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80110AB8);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80110C7C);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80110E20);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80111184);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_801114B0);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80111640);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_801117B0);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80111974);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80111D24);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80111FB4);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80112140);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_801122A4);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80112654);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_801126DC);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80112738);


void func_8011281C(void *arg0, void *arg1) {
    if (!(M2C_FIELD(arg0, u16 *, 0x17E) & 0x200) && (func_80022F04() != 0)) {
        M2C_FIELD(arg1, s8 *, 0) = 2;
        M2C_FIELD(arg1, s8 *, 4) = 2;
    }
}

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80112864);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80112958);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80112A98);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80112B5C);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80112C58);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80112D08);

INCLUDE_ASM("asm/a02/nonmatchings/a02", f_SpawnCoalMiningTownSceneActorsFromPlacementTable);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8011321C);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80113394);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80113628);


void func_80113824(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 4);
    switch (temp_v1) {                              /* irregular */
    case 0:
        M2C_FIELD(arg0, u8 *, 4) = 1U;
        f_SpawnCoalMiningTownSceneActorsFromPlacementTable(arg0, 0U);
        func_8004D8D8(5, 0);
        func_8011321C(0);
        return;
    case 1:
        if (func_80112D08(arg0) != 0) {
            f_SpawnCoalMiningTownSceneActorsFromPlacementTable(arg0, M2C_FIELD(arg0, u8 *, 3));
        }
        func_80026A68(arg0);
        func_8011321C(1);
        return;
    case 3:
        func_8007ADD0(arg0);
        /* fallthrough */
    case 2:
        return;
    }
}

INCLUDE_ASM("asm/a02/nonmatchings/a02", f_UpdateCoalMiningTownInteriorDoorPartTransition);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80113BC4);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80113D08);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80113E4C);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80114024);

INCLUDE_ASM("asm/a02/nonmatchings/a02", f_UpdateCoalMiningTownInteriorSceneryAssemblyActor);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80114650);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_801146D8);

INCLUDE_ASM("asm/a02/nonmatchings/a02", f_UpdateCoalMiningTownScenePropActor);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80114CC8);


void func_80114D54(s32 arg0) {
    func_8007778C();
    func_800517F8(arg0);
}

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80114D80);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80114DE4);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80114E9C);


void func_80114F00(void *arg0) {
    M2C_FIELD(arg0, s8 *, 1) = 1;
    func_80077B5C();
}

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80114F24);


void func_80114F90(void) {
}

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80114F98);

extern u8 D_800BFA03;
void func_8011501C(void *arg0) {
    M2C_UNK var_a2;

    var_a2 = 0x38;
    if ((u8) D_800BFA03 >= 4U) {
        var_a2 = 0x39;
    }
    if (func_80051B70(arg0, 0xC, var_a2) == 0) {
        M2C_FIELD(arg0, u8 *, 0xD) = (u8) (M2C_FIELD(arg0, u8 *, 0xD) | 4);
        M2C_FIELD(M2C_FIELD(arg0, void **, 0xC0), s8 *, 0x3F) = 0x50;
        M2C_FIELD(arg0, s16 *, 0x54) = 0;
        M2C_FIELD(arg0, s16 *, 0x56) = 0;
        M2C_FIELD(arg0, s16 *, 0x58) = 0;
        func_800517F8(arg0);
    }
}


void func_80115090(void *arg0) {
    if (D_800BF870.pad1[0x192] == 3) {
        func_80051B04(M2C_FIELD(arg0, s32 *, 0xC0), 0xC, 0x39);
        D_800BF870.pad1[0x192] = 4;
    }
    func_8007778C(arg0);
}

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_801150EC);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80115148);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8011518C);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_801152A8);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_801154DC);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80115620);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80115794);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80115994);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80115AAC);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80115D84);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80115F58);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_801167A8);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_801167C4);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_801168A0);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80116918);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_801169D8);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80116C14);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8011718C);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_801175D0);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80117658);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_801176EC);

extern u8 D_800BF8BE;
void func_8011778C(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 5);
    switch (temp_v1) {                              /* irregular */
    case 0:
        if (D_800BF8BE == 0xFF) {
            M2C_FIELD(arg0, u8 *, 5) = 1U;
            return;
        }
        func_801169D8();
        return;
    case 1:
        func_80116C14();
        return;
    }
}

extern u8 D_800BF8BE;
void func_801177F8(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 5);
    switch (temp_v1) {                              /* irregular */
    case 0:
        if (D_800BF8BE == 0xFF) {
            M2C_FIELD(arg0, u8 *, 5) = 1U;
            return;
        }
        func_801169D8();
        return;
    case 1:
        func_80116C14();
        return;
    }
}

extern u8 D_800BF8BE;
void func_80117864(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 5);
    switch (temp_v1) {                              /* irregular */
    case 0:
        if (D_800BF8BE == 0xFF) {
            M2C_FIELD(arg0, u8 *, 5) = 1U;
            return;
        }
        func_801169D8();
        return;
    case 1:
        func_80116C14();
        return;
    }
}

extern u8 D_800BF8BE;
void func_801178D0(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 5);
    switch (temp_v1) {                              /* irregular */
    case 0:
        if (D_800BF8BE == 0xFF) {
            M2C_FIELD(arg0, u8 *, 5) = 1U;
            return;
        }
        func_801169D8();
        return;
    case 1:
        func_80116C14();
        return;
    }
}

extern u8 D_800BF8BE;
void func_8011793C(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 5);
    switch (temp_v1) {                              /* irregular */
    case 0:
        if (D_800BF8BE == 0xFF) {
            M2C_FIELD(arg0, u8 *, 5) = 1U;
            return;
        }
        func_801169D8();
        return;
    case 1:
        func_80116C14();
        return;
    }
}

extern u8 D_800BF8BE;
void func_801179A8(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 5);
    switch (temp_v1) {                              /* irregular */
    case 0:
        if (D_800BF8BE == 0xFF) {
            M2C_FIELD(arg0, u8 *, 5) = 1U;
            return;
        }
        func_801169D8();
        return;
    case 1:
        func_80116C14();
        return;
    }
}

extern u8 D_800BF8BE;
void func_80117A14(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 5);
    switch (temp_v1) {                              /* irregular */
    case 0:
        if (D_800BF8BE == 0xFF) {
            M2C_FIELD(arg0, u8 *, 5) = 1U;
            return;
        }
        func_801169D8();
        return;
    case 1:
        func_80116C14();
        return;
    }
}

extern u8 D_800BF8BE;
void func_80117A80(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 5);
    switch (temp_v1) {                              /* irregular */
    case 0:
        if (D_800BF8BE == 0xFF) {
            M2C_FIELD(arg0, u8 *, 5) = 1U;
            return;
        }
        func_801169D8();
        return;
    case 1:
        func_80116C14();
        return;
    }
}

extern u8 D_800BF8BE;
void func_80117AEC(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 5);
    switch (temp_v1) {                              /* irregular */
    case 0:
        if (D_800BF8BE == 0xFF) {
            M2C_FIELD(arg0, u8 *, 5) = 1U;
            return;
        }
        func_801169D8();
        return;
    case 1:
        func_80116C14();
        return;
    }
}

extern u8 D_800BF8BE;
void func_80117B58(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 5);
    switch (temp_v1) {                              /* irregular */
    case 0:
        if (D_800BF8BE == 0xFF) {
            M2C_FIELD(arg0, u8 *, 5) = 1U;
            return;
        }
        func_801169D8();
        return;
    case 1:
        func_80116C14();
        return;
    }
}


void func_80117BC4(void) {
}


void func_80117BCC(void) {
    func_80116C14();
}


void func_80117BEC(void) {
    func_80116C14();
}


void func_80117C0C(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 5) == 0) {
        func_801169D8();
    }
}

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80117C3C);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80117D64);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80117FC0);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80118280);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80118354);

INCLUDE_ASM("asm/a02/nonmatchings/a02", f_UpdateBuryItInTheSandPitActor);


s32 func_80118860(void) {
    func_801167A8();
    return 1;
}

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80118880);


s32 func_80118B50(s32 arg0) {
    if (M2C_FIELD(arg0, s16 *, 0x40) != 0) {
        if ((func_80119694(arg0, (s32) M2C_FIELD(arg0, s16 *, 0x2E), (s32) M2C_FIELD(arg0, s16 *, 0x36)) << 0x10) != 0) {
            M2C_FIELD(arg0, s8 *, 5) = 3;
        }
    } else if (D_800BF870.pad1[0x18D] & 0x80) {
        if ((func_80119694(arg0, (s32) (s16) ((u16) M2C_FIELD(arg0, s16 *, 0x2E) - 0x14A), (s32) (s16) ((u16) M2C_FIELD(arg0, s16 *, 0x36) - 0x10E)) << 0x10) != 0) {
            M2C_FIELD(arg0, s8 *, 5) = 1;
            M2C_FIELD(arg0, s8 *, 6) = 0;
            M2C_FIELD(arg0, s8 *, 0x5E) = 4;
        }
    } else if ((func_80119694(arg0, (s32) (s16) ((u16) M2C_FIELD(arg0, s16 *, 0x2E) - 0x118), (s32) (s16) ((u16) M2C_FIELD(arg0, s16 *, 0x36) - 0x10E)) << 0x10) != 0) {
        D_800BF870.pad1[0x18D] = 3;
        M2C_FIELD(arg0, s8 *, 5) = 0;
    }
    return func_801255A4((s32) (M2C_FIELD(arg0, u16 *, 0x44) << 0x10) >> 0x18);
}

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80118C54);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8011903C);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_801191B0);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80119390);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80119510);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80119694);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80119880);

extern u8 D_800BF8BE;
void func_80119990(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 5);
    switch (temp_v1) {                              /* irregular */
    case 0:
        if (D_800BF8BE == 0xFF) {
            M2C_FIELD(arg0, u8 *, 5) = 1U;
            return;
        }
        return;
    case 1:
        func_80076D68();
        break;
    }
}

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_801199EC);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80119ADC);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80119BAC);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80119C7C);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80119D58);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80119DEC);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80119E68);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80119F78);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8011A010);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8011A058);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8011A098);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8011A0D8);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8011A10C);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8011A1F0);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8011A280);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8011A348);

INCLUDE_ASM("asm/a02/nonmatchings/a02", f_UpdateLetsMakeAPotSequence);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8011A8D4);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8011AAC0);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8011AB34);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8011ABC8);


void func_8011AC0C(void *arg0) {
    M2C_FIELD(arg0, s8 *, 1) = 1;
    func_80077EBC();
    func_800517F8(arg0);
}

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8011AC40);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8011AEF0);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8011B1FC);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8011B5C4);

extern M2C_UNK func_8011B5C4;
void func_8011B8AC(s32 arg0, s8 arg1) {
    void *temp_v0;

    temp_v0 = func_8007A980(3, 4, 0);
    M2C_FIELD(temp_v0, s8 *, 2) = 0x25;
    M2C_FIELD(temp_v0, s8 *, 3) = arg1;
    M2C_FIELD(temp_v0, M2C_UNK **, 0x1C) = &func_8011B5C4;
    M2C_FIELD(temp_v0, s32 *, 0x10) = arg0;
}

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8011B904);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8011BACC);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8011BC0C);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8011BE48);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8011BF84);


void func_8011BFF4(void *arg0, void *arg1, s16 arg2, s32 arg3) {
    M2C_FIELD(arg0, s16 *, 0x58) = 0;
    M2C_FIELD(arg0, u16 *, 0x2E) = (u16) ((s32) (M2C_FIELD(M2C_FIELD(arg1, void **, 0xD0), s32 *, 0x2C) + M2C_FIELD(M2C_FIELD(arg1, void **, 0xDC), s32 *, 0x2C)) / 2);
    M2C_FIELD(arg0, u16 *, 0x2E) = (u16) (M2C_FIELD(arg0, u16 *, 0x2E) + ((s32) (func_80083F50(M2C_FIELD(arg1, s16 *, 0x56)) * arg2) >> 0xC));
    M2C_FIELD(arg0, u16 *, 0x36) = (u16) ((s32) (M2C_FIELD(M2C_FIELD(arg1, void **, 0xD0), s32 *, 0x34) + M2C_FIELD(M2C_FIELD(arg1, void **, 0xDC), s32 *, 0x34)) / 2);
    M2C_FIELD(arg0, u16 *, 0x36) = (u16) (M2C_FIELD(arg0, u16 *, 0x36) - ((s32) (func_80083E80(M2C_FIELD(arg1, s16 *, 0x56)) * arg2) >> 0xC));
    M2C_FIELD(arg0, s16 *, 0x32) = (s16) (arg3 + ((s32) (M2C_FIELD(M2C_FIELD(arg1, void **, 0xD0), s32 *, 0x30) + M2C_FIELD(M2C_FIELD(arg1, void **, 0xDC), s32 *, 0x30)) / 2));
}

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8011C100);

INCLUDE_ASM("asm/a02/nonmatchings/a02", f_UpdateFreedCharlesSequence);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8011C52C);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8011C710);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8011C810);

extern M2C_UNK func_8011C52C;

void func_8011C94C(s32 arg0, s8 arg1) {
    void *temp_v0;

    temp_v0 = func_8007A980(3, 9, 0);
    M2C_FIELD(temp_v0, s8 *, 2) = 1;
    M2C_FIELD(temp_v0, s8 *, 3) = arg1;
    M2C_FIELD(temp_v0, M2C_UNK **, 0x1C) = &func_8011C52C;
    M2C_FIELD(temp_v0, u8 *, 0x28) = (u8) (M2C_FIELD(temp_v0, u8 *, 0x28) | 0x80);
}

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8011C9A0);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8011C9C8);


void func_8011CA78(void *arg0) {
    u8 temp_v1;

    func_80041098();
    func_8004190C(arg0);
    temp_v1 = M2C_FIELD(arg0, u8 *, 5);
    switch (temp_v1) {                              /* irregular */
    case 0:
        func_8011CB20(arg0);
        return;
    case 1:
        f_AdvanceStarvingCharlesDialogue(arg0);
        return;
    case 2:
        func_8011C710(arg0);
        return;
    case 3:
        func_8011CCD0(arg0);
        return;
    }
}

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8011CB20);

INCLUDE_ASM("asm/a02/nonmatchings/a02", f_AdvanceStarvingCharlesDialogue);


void func_8011CCD0(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x71) == 0xFF) {
        func_8004D4F4(0x85, 1);
        M2C_FIELD(arg0, s8 *, 0x5E) = 1;
        M2C_FIELD(arg0, s8 *, 5) = 0;
    }
}

INCLUDE_ASM("asm/a02/nonmatchings/a02", f_RunTabbyHouseResidentConversation);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8011CE8C);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8011D390);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8011D4E8);

INCLUDE_ASM("asm/a02/nonmatchings/a02", f_UpdateTabbyHouseSceneController);


void func_8011DBD8(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 5);
    switch (temp_v1) {                              /* irregular */
    case 0:
        if (func_8007778C(arg0) != 0) {
            func_80076D68(arg0);
            if ((*(u8 *)0x1F800137 == 0) && (M2C_FIELD(arg0, u8 *, 0x2B) == 3)) {
                func_80042354(1, 1);
                M2C_FIELD(arg0, s8 *, 6) = 0;
                M2C_FIELD(arg0, u8 *, 5) = (u8) (M2C_FIELD(arg0, u8 *, 5) + 1);
                return;
            }
        }
        return;
    case 1:
        if (f_RunTabbyHouseResidentConversation(arg0) != 0) {
            M2C_FIELD(arg0, u8 *, 5) = 0U;
        }
        break;
    }
}

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8011DC88);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8011DE1C);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8011DF98);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8011E2D8);


void func_8011E3A8(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x71) == 0xFF) {
        M2C_FIELD(arg0, s8 *, 5) = 0;
        M2C_FIELD(arg0, s8 *, 6) = 0;
    }
}

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8011E3C8);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8011E47C);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8011E674);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8011E6EC);


void func_8011E76C(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x71) == 0xFF) {
        if (M2C_FIELD(arg0, u8 *, 0x5E) == 0) {
            M2C_FIELD(arg0, u8 *, 0x5E) = 1U;
        }
        func_80041768(arg0, 0, 4);
        M2C_FIELD(arg0, s8 *, 5) = 0;
        M2C_FIELD(arg0, s8 *, 6) = 0;
    }
}

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8011E7C8);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8011EAD4);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8011ECC8);


void func_8011EF70(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x2B) == 3) {
        M2C_FIELD(arg0, s8 *, 0) = 2;
        M2C_FIELD(arg0, s8 *, 0x70) = 1;
        M2C_FIELD(arg0, s8 *, 5) = 1;
        return;
    }
    if (M2C_FIELD(arg0, u8 *, 0x5E) == 2) {
        func_8011CE8C();
    }
}

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8011EFC8);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8011F028);

extern s32 D_800BF844;
s32 func_8011F10C(void *arg0) {
    D_800BF844 = M2C_FIELD(arg0, s32 *, 0x14);
    return 1;
}

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8011F120);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8011F23C);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8011F504);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8011F640);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8011F6EC);

extern M2C_UNK D_800A3D18;
extern M2C_UNK D_80139240;
void func_8011F8E0(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 4);
    switch (temp_v1) {                              /* irregular */
    case 0:
        func_80040CDC(arg0, &D_80139240, &D_800A3D18);
        func_80041718(arg0, 0, 0);
        M2C_FIELD(arg0, s8 *, 0x7B) = 0;
        M2C_FIELD(arg0, s16 *, 0x56) = 0xC00;
        M2C_FIELD(arg0, u8 *, 4) = (u8) (M2C_FIELD(arg0, u8 *, 4) + 1);
        return;
    case 1:
        func_8011F6EC(arg0);
        if (M2C_FIELD(arg0, u8 *, 1) != 0) {
            func_800518FC(arg0);
        }
        M2C_FIELD(arg0, s8 *, 0x2B) = 0;
        return;
    case 3:
        func_8007A624(arg0);
        /* fallthrough */
    case 2:
        return;
    }
}

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8011F9B4);

extern M2C_UNK func_8011D4E8;
void *func_8011FFFC(void) {
    void *temp_v0;

    temp_v0 = func_8007A980(3, 9, 0);
    M2C_FIELD(temp_v0, s8 *, 2) = 0x15;
    M2C_FIELD(temp_v0, s8 *, 3) = 7;
    M2C_FIELD(temp_v0, M2C_UNK **, 0x1C) = &func_8011D4E8;
    M2C_FIELD(temp_v0, s16 *, 0x2E) = 0x38A4;
    M2C_FIELD(temp_v0, s16 *, 0x32) = -0xD0C;
    M2C_FIELD(temp_v0, s16 *, 0x36) = 0x2D8A;
    M2C_FIELD(temp_v0, s32 *, 0x14) = func_801150EC(temp_v0);
    return temp_v0;
}

extern M2C_UNK D_8012B490;
extern M2C_UNK D_80139240;
void func_80120070(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 4);
    switch (temp_v1) {                              /* irregular */
    case 0:
        func_80040CDC(arg0, &D_80139240, &D_8012B490);
        func_80041718(arg0, 0x10, 0);
        M2C_FIELD(arg0, s8 *, 0x7B) = 0;
        M2C_FIELD(arg0, s16 *, 0x56) = 0x800;
        M2C_FIELD(arg0, u8 *, 4) = (u8) (M2C_FIELD(arg0, u8 *, 4) + 1);
        return;
    case 1:
        func_8011F9B4(arg0);
        if (M2C_FIELD(arg0, u8 *, 1) != 0) {
            func_800518FC(arg0);
        }
        M2C_FIELD(arg0, s8 *, 0x2B) = 0;
        return;
    case 3:
        func_8007A624(arg0);
        /* fallthrough */
    case 2:
        return;
    }
}

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80120144);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_801202DC);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_801203F0);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80120564);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80120610);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8012067C);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80120718);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80120848);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80120A3C);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80120BE0);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80120D1C);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80120F70);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80121268);

INCLUDE_ASM("asm/a02/nonmatchings/a02", f_UpdateGranActor);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8012167C);


s32 func_801216C0(void *arg0) {
    void *temp_v1;

    temp_v1 = M2C_FIELD(arg0, void **, 0x14);
    M2C_FIELD(temp_v1, u16 *, 0x50) = (u16) (M2C_FIELD(temp_v1, u16 *, 0x50) - 0x96);
    return 1;
}

extern s8 D_1F8000F2[];
extern void *D_800BF844_5c02;

s32 func_801216E0(s32 arg0) {
    u8 temp_v1;
    void *temp_a0;
    void *temp_v0;

    temp_v1 = M2C_FIELD(arg0, u8 *, 0x78);
    switch (temp_v1) {                              /* irregular */
    case 0:
        temp_v0 = func_8006FB0C(arg0, 0x17);
        M2C_FIELD(arg0, void **, 0x14) = temp_v0;
        D_800BF844_5c02 = temp_v0;
        temp_a0 = M2C_FIELD(arg0, void **, 0x14);
        if (temp_a0 != NULL) {
            M2C_FIELD(temp_a0, s16 *, 0x60) = 0x60;
            M2C_FIELD(temp_a0, s16 *, 0x62) = 0x78;
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

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_801217A0);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80121948);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80121AA4);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80121BB4);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80121C10);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80121C74);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80121DA4);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80121ED8);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80122030);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80122140);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_801221A8);


void func_801221EC(void *arg0) {
    if (M2C_FIELD(arg0, s16 *, 0x40) != 0) {
        if (M2C_FIELD(M2C_FIELD(arg0, void **, 0x38), u16 *, 4) != 0) {
            func_80074590(0xA, -3, 0);
            M2C_FIELD(arg0, s16 *, 0x40) = 0;
        }
    } else if (M2C_FIELD(M2C_FIELD(arg0, void **, 0x38), u16 *, 4) == 0) {
        M2C_FIELD(arg0, s16 *, 0x40) = 1;
    }
}


void func_80122264(void *arg0) {
    if (M2C_FIELD(arg0, s16 *, 0x40) != 0) {
        if (M2C_FIELD(M2C_FIELD(arg0, void **, 0x38), u16 *, 2) != 0) {
            func_80074590(0x33, 0xC, 0);
            M2C_FIELD(arg0, s16 *, 0x40) = 0;
        }
    } else if (M2C_FIELD(M2C_FIELD(arg0, void **, 0x38), u16 *, 2) == 0) {
        M2C_FIELD(arg0, s16 *, 0x40) = 1;
    }
}

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_801222DC);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_801223B4);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80122404);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_801225EC);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80122728);

extern M2C_UNK func_80122728;

void func_801229D4(s32 arg0, s8 arg1) {
    void *temp_v0;

    temp_v0 = func_8007A980(3, 9, 0);
    M2C_FIELD(temp_v0, s8 *, 2) = 0x1D;
    M2C_FIELD(temp_v0, s8 *, 3) = arg1;
    M2C_FIELD(temp_v0, M2C_UNK **, 0x1C) = &func_80122728;
    M2C_FIELD(temp_v0, u8 *, 0x28) = (u8) (M2C_FIELD(temp_v0, u8 *, 0x28) | 0x80);
}

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80122A28);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80122AC4);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80122EA8);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80122F6C);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8012328C);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80123470);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_801236C8);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8012383C);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8012396C);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80123BB8);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80123CD8);


void func_80123D38(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x71) == 0xFF) {
        M2C_FIELD(arg0, s8 *, 5) = 0;
    }
}


void func_80123D54(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x71) == 0xFF) {
        func_8004D4F4(M2C_FIELD(arg0, s16 *, 0x60), 1);
        M2C_FIELD(arg0, s8 *, 5) = 0;
    }
}

extern s32 D_800BF844;
s32 func_80123D94(void) {
    D_800BF844 = 0;
    return 1;
}


void func_80123DA4(void *arg0) {
    if (M2C_FIELD(arg0, s16 *, 0x40) != 0) {
        if (M2C_FIELD(M2C_FIELD(arg0, void **, 0x38), u16 *, 2) != 0) {
            func_80074590(0x2E, -0xC, -0x28);
            M2C_FIELD(arg0, s16 *, 0x40) = 0;
        }
    } else if (M2C_FIELD(M2C_FIELD(arg0, void **, 0x38), u16 *, 2) == 0) {
        M2C_FIELD(arg0, s16 *, 0x40) = 1;
    }
}

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80123E1C);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80124138);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80124678);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_801246A4);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8012496C);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80124CB8);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80124DB8);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80125100);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8012555C);

extern u16 D_8012C928;
void func_801255A4(s32 arg0) {
    D_8012C928 = (D_8012C928 + arg0) & 0xFF;
}

extern u16 D_8012C92A;
extern u16 D_8012C92C;
void func_801255C0(s32 arg0) {
    u16 temp_a0;
    u16 temp_v0;
    u16 temp_v1;

    temp_v1 = D_8012C92A + arg0;
    D_8012C92A = temp_v1;
    if ((u32) (temp_v1 & 0xFFFF) >= 0x180U) {
        D_8012C92A = temp_v1 - 0x180;
    }
    temp_a0 = D_8012C92C;
    temp_v0 = temp_a0 + 0x100;
    D_8012C92C = temp_v0;
    if ((u32) (temp_v0 & 0xFFFF) >= 0x800U) {
        D_8012C92C = temp_a0 - 0x700;
    }
}

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80125618);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_801258A4);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80125C5C);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80125F7C);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80126240);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_801265AC);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80126968);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80126C18);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80126C94);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80126D24);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80126EA8);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80127034);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80127170);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80127678);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80127784);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80127860);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_801278D8);

INCLUDE_ASM("asm/a02/nonmatchings/a02", f_UpdateBlastTheRockSequence);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80127EDC);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80128034);

INCLUDE_ASM("asm/a02/nonmatchings/a02", f_UpdateTabbyHouseResidentActor);

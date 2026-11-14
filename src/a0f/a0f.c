#include "common.h"
#include "game.h"
#include "m2c.h"

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_80109320);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_80109458);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_80109694);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_80109808);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_80109AEC);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_80109C64);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_80109ED8);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_8010A2D4);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_8010A47C);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_8010A5F8);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_8010A7A8);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_8010AB94);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_8010ACE4);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_8010AD58);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_8010ADA8);

void func_8010AE24(void *a, u8 *b)
{
    if (b[0x47] == 2) {
        func_80109808(a, b, *(void **)(b + 0xC0));
    } else {
        func_8001F650(a, b, *(void **)(b + 0xC0));
    }
}

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_8010AE6C);


s32 func_8010AEC0(s32 arg0, s32 arg1) {
    return func_80109ED8(arg0, arg1, M2C_FIELD(arg1, s32 *, 0xC0));
}


void func_8010AEE4(void *arg0, void *arg1) {
    u16 var_v0;

    if (func_80022F04() != 0) {
        if (M2C_FIELD(arg1, u8 *, 0x46) & 1) {
            var_v0 = M2C_FIELD(arg0, u16 *, 0x140) + 0x800;
        } else {
            var_v0 = M2C_FIELD(arg0, u16 *, 0x140);
        }
        M2C_FIELD(arg0, s8 *, 0x2B) = (s8) (var_v0 >> 4);
        func_80022D08(arg0, arg1, 1, 0);
    }
}

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_8010AF60);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_8010B078);


void func_8010B194(void *arg0, void *arg1) {
    s32 temp_lo;
    s32 temp_s0;
    s32 temp_s0_2;
    s32 temp_s2_2;
    s32 temp_s3;
    void *temp_s2;

    temp_s2 = M2C_FIELD(arg0, void **, 0x10);
    M2C_FIELD(arg0, u16 *, 0x32) = (u16) (M2C_FIELD(temp_s2, u16 *, 0x30) + ((s32) (func_80083F50(M2C_FIELD(temp_s2, s16 *, 0xC)) * M2C_FIELD(arg0, s16 *, 0x156)) >> 0xC));
    M2C_FIELD(arg0, u16 *, 0x32) = (u16) (M2C_FIELD(arg0, u16 *, 0x32) + ((s32) (func_80083F50(M2C_FIELD(arg0, s16 *, 0x58)) * M2C_FIELD(arg0, s16 *, 0x64)) >> 0xC));
    temp_s0 = (s32) (func_80083E80(M2C_FIELD(temp_s2, s16 *, 0xC)) * M2C_FIELD(arg0, s16 *, 0x156)) >> 0xC;
    temp_s3 = (s32) (func_80083E80(M2C_FIELD(arg1, s16 *, 0x56)) * (s16) temp_s0) >> 0xC;
    M2C_FIELD(arg0, u16 *, 0x2E) = (u16) (M2C_FIELD(temp_s2, u16 *, 0x2C) - ((s32) (func_80083F50(M2C_FIELD(arg1, s16 *, 0x56)) * (s16) temp_s0) >> 0xC));
    M2C_FIELD(arg0, u16 *, 0x36) = (u16) (M2C_FIELD(temp_s2, u16 *, 0x34) + temp_s3);
    temp_s0_2 = (s32) (func_80083E80(M2C_FIELD(arg0, s16 *, 0x58)) * M2C_FIELD(arg0, s16 *, 0x64)) >> 0xC;
    temp_s2_2 = (s32) (func_80083E80(M2C_FIELD(arg0, s16 *, 0x56)) * (s16) temp_s0_2) >> 0xC;
    temp_lo = func_80083F50(M2C_FIELD(arg0, s16 *, 0x56)) * (s16) temp_s0_2;
    M2C_FIELD(arg0, u16 *, 0x36) = (u16) (M2C_FIELD(arg0, u16 *, 0x36) + temp_s2_2);
    M2C_FIELD(arg0, u16 *, 0x2E) = (u16) (M2C_FIELD(arg0, u16 *, 0x2E) - (temp_lo >> 0xC));
}

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_8010B2F8);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_8010B4E8);

extern s8 D_1F80027E[];
extern u8 D_800BFA1A;

void func_8010B960(void *arg0) {
    *((s8 *)D_1F80027E) = 1;
    func_8006F0E4();
    M2C_FIELD(arg0, s8 *, 1) = 1;
    func_80055D5C(arg0);
    M2C_FIELD(arg0, s16 *, 0x142) = 0;
    M2C_FIELD(arg0, s16 *, 0x58) = 0;
    func_80054198(arg0);
    func_80055284(arg0);
    func_80054D14(arg0, 2, 0);
    func_8003315C(arg0);
    if (!(D_800BFA1A & 0x20)) {
        func_80042354(1, 5);
        func_8001CF2C();
        M2C_FIELD(arg0, s8 *, 4) = 4;
    }
}


s32 func_8010BA04(s32 arg0, s32 arg1) {
    s32 var_a3;
    void *temp_a1;

    temp_a1 = M2C_FIELD(arg0, void **, 0x158);
    var_a3 = 0;
    if ((M2C_FIELD(temp_a1, u8 *, 0xC) == 4) && (M2C_FIELD(temp_a1, u8 *, 2) == 0x17)) {
        var_a3 = func_8010B4E8(arg0, (s32) temp_a1, arg1);
    }
    return var_a3;
}

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_8010BA54);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_8010BC78);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_8010BE48);


void func_8010C098(void) {
}


void func_8010C0A0(void) {
}

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_8010C0A8);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_8010C198);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_8010C2F4);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_8010C448);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_8010CA3C);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_8010CB8C);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_8010CD20);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_8010CE24);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", f_InitializeLastEvilPigCopiedWeaponProjectile);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_8010D4B8);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_8010D738);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_8010D830);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_8010D924);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_8010D94C);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_8010D968);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_8010D98C);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_8010DA1C);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_8010DAC4);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_8010DB90);


void func_8010DC48(void *arg0) {
    u8 temp_v1;

    if (M2C_FIELD(arg0, u8 *, 3) != 3) {
        temp_v1 = M2C_FIELD(arg0, u8 *, 0);
        if (temp_v1 == 2) {
            M2C_FIELD(arg0, u8 *, 0x2B) = temp_v1;
            M2C_FIELD(arg0, u8 *, 4) = temp_v1;
        }
    }
}

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_8010DC78);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", f_SpawnLastEvilPigCopiedWeaponProjectile);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_8010DDE4);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_8010DF5C);


void func_8010E084(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 4);
    switch (temp_v1) {                              /* irregular */
    case 0:
        M2C_FIELD(arg0, u8 *, 4) = 1U;
        func_8010DDE4(arg0, 0U);
        func_8010DF5C(0);
        func_800752B4(0);
        func_80075D24(0x1FFF);
        func_80113330();
        return;
    case 1:
        if (func_80026AD0(arg0) != 0) {
            func_8010DDE4(arg0, M2C_FIELD(arg0, u8 *, 3));
        }
        func_80026A68(arg0);
        func_8010DF5C(1);
        return;
    case 3:
        func_8007ADD0(arg0);
        /* fallthrough */
    case 2:
        return;
    }
}

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_8010E15C);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_8010E380);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_8010E550);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_8010E63C);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_8010E74C);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_8010EDF8);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_8010F48C);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_8010FCF0);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_8010FE34);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_80110B38);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_80110D4C);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_80111044);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_80111184);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_801112B4);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", f_UpdateLastEvilPigCopiedWeaponAttack);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", f_UpdateLastEvilPigRepeatedChargeAttack);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_801123F0);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_8011290C);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_80112B80);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_80112BE8);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_80112CB4);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_80112CE0);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_80112D10);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_80113068);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_80113330);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_8011348C);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_801135EC);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_8011394C);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_80113B78);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_80113C8C);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_80113E38);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_80113FDC);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_801140F4);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_80114288);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_801143C4);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_801148E0);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_801149AC);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_80114A5C);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_80114E70);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_80115364);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_801157CC);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_80115A70);

void func_80115DA4(u32 *p, void *b)
{
    u32 lo = *p;
    u32 packed;

    packed = lo;
    lo = packed & 0xFFFF;
    p += 4;
    func_80115A70(func_801157CC(p, b, lo), b, packed >> 16);
}

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_80115DEC);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_80115FF4);

extern u16 *D_800ECF78;

void func_80116534(u8 *a)
{
    u16 *p = D_800ECF78;
    u16 t;

    *(u16 **)(a + 0xC) = p;
    *(u16 *)(a + 8) = p[0];
    t = p[1];
    a[7] = 0;
    *(u16 *)(a + 0xA) = t;
}

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_80116560);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_80116778);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_80116ABC);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_80116C2C);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_80116E5C);


void func_801175B8(void) {
}

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_801175C0);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_80117984);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_80117A64);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_80117C70);


void func_80117E40(void *arg0) {
    M2C_FIELD(arg0, s16 *, 0x56) = (s16) -(s16) *(u16 *)0x1F8000F2;
    func_800517F8();
}

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_80117E6C);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_80117F08);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_80117FA4);


s32 func_80118250(void *arg0) {
    M2C_FIELD(arg0, u8 *, 0x47) = (u8) M2C_FIELD(arg0, u8 *, 0x72);
    return 1;
}

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_80118264);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_80118378);

extern s8 D_1F800233[];

s32 func_801183B8(void) {
    *((s8 *)D_1F800233) = 0;
    return 1;
}

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_801183C8);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_80118534);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_80118588);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_8011866C);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_80118934);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_80118B74);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_80118C98);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_80119058);

extern s8 D_1F800160[];
extern s8 D_1F800164[];
extern s8 D_1F800246[];
extern s8 D_1F80024C[];

void func_8011919C(void *arg0) {
    M2C_UNK var_a0;
    void *temp_s1;

    temp_s1 = *((void **)D_1F80024C);
    if (*((u8 *)D_1F800246) == 0) {
        M2C_FIELD(arg0, u8 *, 5) = 0U;
        M2C_FIELD(arg0, s8 *, 6) = 0;
        M2C_FIELD(arg0, s8 *, 7) = 2;
        M2C_FIELD(arg0, s16 *, 0x64) = 0;
        M2C_FIELD(arg0, u16 *, 0x56) = (u16) M2C_FIELD(arg0, u16 *, 0x62);
    } else {
        M2C_FIELD(arg0, u16 *, 0x56) = func_800776F8((s16) (func_800782B0(arg0 + 0x2C, *((s16 *)D_1F800160), *((s16 *)D_1F800164)) - 0x400), (s16) M2C_FIELD(arg0, u16 *, 0x56), 0x80);
        M2C_FIELD(M2C_FIELD(arg0, void **, 0xC0), s16 *, 8) = func_800776F8(0, M2C_FIELD(M2C_FIELD(arg0, void **, 0xC0), s16 *, 8), 0x80);
        func_8011866C(arg0);
        if (M2C_FIELD(arg0, u8 *, 0x29) != 0) {
            var_a0 = 0x88;
            if (M2C_FIELD(temp_s1, s16 *, 0x6E) == 1) {
                var_a0 = 0x89;
            }
            func_80074590(var_a0, 0, 0);
            M2C_FIELD(arg0, s8 *, 6) = 0;
            M2C_FIELD(arg0, s16 *, 0x64) = 0;
            M2C_FIELD(arg0, s8 *, 7) = 3;
            M2C_FIELD(arg0, u8 *, 5) = (u8) (M2C_FIELD(arg0, u8 *, 5) + 1);
        }
    }
    M2C_FIELD(arg0, s16 *, 0x32) = (s16) (M2C_FIELD(arg0, u16 *, 0x7C) + (func_80083E80(M2C_FIELD(arg0, s16 *, 0x60)) >> 4));
    M2C_FIELD(arg0, s16 *, 0x60) = (s16) (((u16) M2C_FIELD(arg0, s16 *, 0x60) + 0x40) & 0xFFF);
}

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_801192C8);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_8011968C);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_80119B64);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_80119CC0);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_8011A1EC);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_8011A27C);


s32 func_8011A328(void *arg0) {
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x38), s8 *, 4) = 2;
    func_80074590(0x37, 0x16, 0);
    return 1;
}

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_8011A35C);

extern s16 D_800BED82;
extern M2C_UNK D_80129134;
void func_8011A428(void) {
    func_80075448(0xA, &D_80129134, 0x10, D_800BED82);
}

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_8011A45C);

INCLUDE_ASM("asm/a0f/nonmatchings/a0f", func_8011A620);

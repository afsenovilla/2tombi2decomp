#include "common.h"
#include "game.h"
#include "m2c.h"

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_801092BC);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_801093F4);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80109630);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80109ACC);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80109F7C);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8010A3D0);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8010A550);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8010A6E0);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8010A93C);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8010ACA8);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8010AE50);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8010B010);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8010B128);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8010B444);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8010B4E4);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8010B590);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8010B680);


s32 func_8010B734(void) {
    return 0;
}

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8010B73C);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8010B938);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8010BC10);

extern s8 D_1F80027E[];
extern u8 D_800BFA1A;

void func_8010BD50(void *arg0) {
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
    if (!(D_800BFA1A & 2)) {
        func_80042354(1, 5);
        func_8001CF2C();
        M2C_FIELD(arg0, s8 *, 4) = 4;
    }
}


void func_8010BDF4(void *arg0) {
    s16 temp_a1;
    s16 temp_v0;
    s16 var_v0;
    s16 var_v1;

    temp_a1 = M2C_FIELD(arg0, s16 *, 0x44);
    var_v0 = temp_a1;
    if (temp_a1 < 0) {
        var_v0 = -var_v0;
    }
    temp_v0 = var_v0 - 0xE0;
    var_v1 = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        var_v1 = 0;
    }
    if (temp_a1 >= 0) {
        M2C_FIELD(arg0, s16 *, 0x44) = var_v1;
        return;
    }
    M2C_FIELD(arg0, s16 *, 0x44) = (s16) -var_v1;
}

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8010BE38);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8010BE80);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8010C0A4);


void func_8010C300(void) {
}


void func_8010C308(void) {
}

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8010C310);


void func_8010C488(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 4);
    switch (temp_v1) {                              /* irregular */
    case 0:
        M2C_FIELD(arg0, u8 *, 4) = 1U;
        func_8010C310(arg0, 0U);
        func_800310F4(0xC05, 0);
        func_800752B4(1);
        func_80075D24(0x1FFF);
        return;
    case 1:
        if (func_80026AD0(arg0) != 0) {
            func_8010C310(arg0, M2C_FIELD(arg0, u8 *, 3));
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

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8010C554);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8010C778);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8010C948);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8010CA34);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8010CB44);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8010D1F0);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8010D884);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8010E0E8);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8010E22C);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8010EF30);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8010F144);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8010F43C);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8010F544);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", f_UpdateLastEvilPigProjectileAttack);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8010FC1C);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80110118);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80110540);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_801106A4);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80110800);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80110A98);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_801110BC);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_801113B4);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8011159C);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80111770);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8011199C);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80111AB0);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80111C5C);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80111E00);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80111F18);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_801120AC);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_801121E8);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80112704);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_801127BC);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80112880);

void func_80112974(u8 *a)
{
    switch (a[4]) {
    case 0:
        a[4]++;
        a[7] = 0;
        *(s32 *)(a + 0x48) = func_8009A450();
        *(s32 *)(a + 0x4C) = func_8009A450();
    case 1:
        if (++a[7] >= 0x10) {
            a[4] = 2;
        } else {
            a[1] = 1;
        }
        break;
    case 2:
    case 3:
        func_8007A624(a);
        break;
    }
}

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80112A24);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80112CF0);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80113050);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80113150);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_801133F4);

void func_80113728(u32 *p, void *b)
{
    u32 lo = *p;
    u32 packed;

    packed = lo;
    lo = packed & 0xFFFF;
    p += 4;
    func_801133F4(func_80113150(p, b, lo), b, packed >> 16);
}

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80113770);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80113A28);

extern u16 *D_800ECF78;

void func_80113F68(u8 *a)
{
    u16 *p = D_800ECF78;
    u16 t;

    *(u16 **)(a + 0xC) = p;
    *(u16 *)(a + 8) = p[0];
    t = p[1];
    a[7] = 0;
    *(u16 *)(a + 0xA) = t;
}

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80113F94);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_801141B0);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_801144F4);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80114608);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80114AA8);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80114CEC);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80114DE8);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80114ECC);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80115194);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_801153D4);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_801154F8);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_801158B8);

extern s8 D_1F800160[];
extern s8 D_1F800164[];
extern s8 D_1F800246[];
extern s8 D_1F80024C[];

void func_801159FC(void *arg0) {
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
        func_80114ECC(arg0);
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

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80115B28);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80115EEC);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_801163C4);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80116520);

extern u8 D_800E806E;

s32 func_801169E0(u8 *p)
{
    switch (p[0x78]) {
    case 0:
        p[0x78]++;
        func_8006E1C0(8);
        g_CameraState.focusX = *(u16 *)(p + 0x2E);
        g_CameraState.focusY = *(u16 *)(p + 0x32) + 0x4B0;
        g_CameraState.focusZ = *(u16 *)(p + 0x36);
        goto end;
    case 1:
        if (D_800E806E == 3) {
            return 1;
        }
    end:
    default:
        return 0;
    }
}

extern s16 D_80124448[];
extern s16 D_800E8046;

s32 func_80116A70(u8 *p)
{
    s16 y;

    switch (p[0x78]) {
    case 0:
        p[0x78]++;
        *(s32 *)(p + 0x38) = func_8003116C(D_80124448[D_800BF870.unk0 - 10], p + 0x2C, -0x32);
        goto end;
    case 1:
        y = *(u16 *)(p + 0x32) + 0x10;
        *(s16 *)(p + 0x32) = y;
        *(s16 *)(*(u8 **)(p + 0x38) + 0x2E) = y;
        if (*(s16 *)(p + 0x32) >= D_800E8046 - 0xF0) {
            return 1;
        }
    end:
    default:
        return 0;
    }
}


s32 func_80116B1C(void *arg0) {
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x38), s8 *, 4) = 2;
    func_80074590(0x37, 0x16, 0);
    return 1;
}

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80116B50);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80116CB0);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", f_UpdateEvilPigBattleProjectile);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_801175B8);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80117720);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80117774);


void func_80117800(void *arg0) {
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
    M2C_FIELD(arg0, s32 *, 0x30) = (s32) (M2C_FIELD(arg0, s32 *, 0x30) + (M2C_FIELD(arg0, s16 *, 0x50) << 0xC));
}

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_801178A0);

extern s16 D_800BED82;
extern M2C_UNK D_801246AC;
void func_80117988(void) {
    func_80075448(0xA, &D_801246AC, 0x10, D_800BED82);
}

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_801179BC);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", f_SpawnLastEvilPigBattleProjectile);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_801180E8);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_801181AC);

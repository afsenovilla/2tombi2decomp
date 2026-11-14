#include "common.h"
#include "game.h"
#include "m2c.h"

INCLUDE_ASM("asm/a0h/nonmatchings/a0h", func_801090DC);

INCLUDE_ASM("asm/a0h/nonmatchings/a0h", func_801092D4);

INCLUDE_ASM("asm/a0h/nonmatchings/a0h", func_801094F8);

extern u8 **D_1F80013C;
extern u8 D_1F800144;
extern u8 D_1F800182_5650;
extern u8 D_1F800183;
extern u8 D_1F800182_5650;
extern u8 D_1F800182_5650;
extern u8 D_1F800182_5650;
extern u8 D_1F800182_5650;
extern u8 D_1F800182_5650;

void func_8010963C(void)
{
    u8 **l;
    u8 n = D_1F800144;
    u8 k;

    D_1F800183 = n;
    if (n < 2) {
        return;
    }
    l = D_1F80013C;
    for (D_1F800183 = n - 1; D_1F800183 != 0; D_1F800183--) {
        k = (*l++)[0];
        if (k != 2 && k != 7) {
            for (D_1F800182_5650 = D_1F800183; D_1F800182_5650 != 0; D_1F800182_5650--) {
            }
        }
    }
}

INCLUDE_ASM("asm/a0h/nonmatchings/a0h", func_801096E8);

INCLUDE_ASM("asm/a0h/nonmatchings/a0h", f_DispatchStrengthTowerTombaContacts);

extern u16 D_800BF812;

void func_80109CC4(u8 *a)
{
    u16 limit = D_800BF812;

    if (!(a[0x145] & 1)) {
        if (*(s16 *)(a + 0x32) >= (s16)limit - *(s16 *)(a + 0x62)) {
            *(u16 *)(a + 0x32) = limit - *(u16 *)(a + 0x62);
            func_80022C78(a);
        }
    }
}

extern u8 D_800BF808[];

void func_80109D24(u8 *a)
{
    u8 *s = D_800BF808;
    u16 limit;

    if (s[0xE] != 0) {
        limit = *(u16 *)(s + 0xA);
        if (!(a[0x145] & 1)) {
            if (*(s16 *)(a + 0x32) >= (s16)limit - *(s16 *)(a + 0x62)) {
                *(u16 *)(a + 0x32) = limit - *(u16 *)(a + 0x62);
                func_80022C78(a);
            }
        }
    }
}

extern s8 D_1F800182[];

void func_80109D94(void *arg0, void *arg1) {
    if (func_80022F04() != 0) {
        if (func_8001E860(arg0, arg1, 0, 0x100) & 0x80) {
            M2C_FIELD(arg0, s8 *, 0x2B) = 2;
            M2C_FIELD(arg1, s8 *, 0) = 2;
            M2C_FIELD(arg1, s8 *, 4) = 2;
            M2C_FIELD(arg1, s8 *, 5) = 6;
            M2C_FIELD(arg1, s8 *, 6) = 0;
        }
        M2C_FIELD(arg1, s8 *, 0x2B) = 1;
        *((s8 *)D_1F800182) = 0;
    }
}

INCLUDE_ASM("asm/a0h/nonmatchings/a0h", func_80109E10);

extern u8 **D_1F80013C;
extern u8 D_1F800144;
extern u8 D_1F800182_5650;

void func_80109EE8(void *a)
{
    u8 **l = D_1F80013C;
    u8 *e;

    D_1F800182_5650 = D_1F800144;
    while (D_1F800182_5650 != 0) {
        e = *l;
        D_1F800182_5650--;
        l++;
        if (e[0] & 1) {
            if (e[0xC] == 9) {
                func_801090DC(a, e);
            } else if (e[2] == 8) {
                func_800205CC(a, e);
            }
        }
    }
}

INCLUDE_ASM("asm/a0h/nonmatchings/a0h", func_80109FAC);

INCLUDE_ASM("asm/a0h/nonmatchings/a0h", func_8010A0AC);

extern u8 D_1F800152;
extern u8 D_1F800182_5650;
extern s32 D_1F800080;

s32 func_8010A1AC(void)
{
    for (D_1F800182_5650 = D_1F800152; D_1F800182_5650 != 0; D_1F800182_5650--) {
    }
    return D_1F800080;
}


void func_8010A1E4(void *arg0) {
    func_8006F0E4();
    M2C_FIELD(arg0, s8 *, 1) = 1;
    func_80055D5C(arg0);
    M2C_FIELD(arg0, s16 *, 0x142) = 0;
    M2C_FIELD(arg0, s16 *, 0x58) = 0;
    func_80054198(arg0);
    func_80055284(arg0);
    func_80054D14(arg0, 2, 0);
    func_8003315C(arg0);
}

INCLUDE_ASM("asm/a0h/nonmatchings/a0h", func_8010A248);

INCLUDE_ASM("asm/a0h/nonmatchings/a0h", func_8010A33C);

extern u8 D_800BF816;
extern u8 D_800E806C;
extern s32 D_1F800184;
extern u8 D_800E7E80[];

void func_8010A39C(void)
{
    u8 *p;

    D_800BF816 = 0;
    D_800E806C = 0;
    D_1F800184 = 0;
    p = D_800E7E80;
    p[5] = 0x24;
    p[7] = 0;
    p[6] = 0;
    func_80054198(p);
    p[0x16B] = 0;
}

INCLUDE_ASM("asm/a0h/nonmatchings/a0h", f_UpdateStrengthTowerExitDoorSequence);

INCLUDE_ASM("asm/a0h/nonmatchings/a0h", func_8010A574);

INCLUDE_ASM("asm/a0h/nonmatchings/a0h", func_8010A854);

INCLUDE_ASM("asm/a0h/nonmatchings/a0h", func_8010A918);

INCLUDE_ASM("asm/a0h/nonmatchings/a0h", func_8010ABE8);

INCLUDE_ASM("asm/a0h/nonmatchings/a0h", func_8010ACF8);

extern u8 D_800BF917;
void func_8010AE70(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 4);
    switch (temp_v1) {                              /* irregular */
    case 0:
        M2C_FIELD(arg0, u8 *, 4) = 1U;
        func_8010ACF8(arg0, 0U);
        func_8004D8D8(0xE, 0);
        func_800752B4(0);
        func_80075D24(0x1FFF);
        return;
    case 1:
        if (func_80026AD0(arg0) != 0) {
            func_8010ACF8(arg0, M2C_FIELD(arg0, u8 *, 3));
        }
        if (D_800BF917 != 0xFF) {
            func_80040C00(0x63);
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

INCLUDE_ASM("asm/a0h/nonmatchings/a0h", func_8010AF58);

INCLUDE_ASM("asm/a0h/nonmatchings/a0h", func_8010B240);

INCLUDE_ASM("asm/a0h/nonmatchings/a0h", func_8010B5BC);

INCLUDE_ASM("asm/a0h/nonmatchings/a0h", func_8010B6BC);

INCLUDE_ASM("asm/a0h/nonmatchings/a0h", func_8010B960);

void func_8010BC94(u32 *p, void *b)
{
    u32 lo = *p;
    u32 packed;

    packed = lo;
    lo = packed & 0xFFFF;
    p += 4;
    func_8010B960(func_8010B6BC(p, b, lo), b, packed >> 16);
}

INCLUDE_ASM("asm/a0h/nonmatchings/a0h", func_8010BCDC);

INCLUDE_ASM("asm/a0h/nonmatchings/a0h", func_8010BFBC);

extern u16 *D_800ECF78;

void func_8010C4FC(u8 *a)
{
    u16 *p = D_800ECF78;
    u16 t;

    *(u16 **)(a + 0xC) = p;
    *(u16 *)(a + 8) = p[0];
    t = p[1];
    a[7] = 0;
    *(u16 *)(a + 0xA) = t;
}

INCLUDE_ASM("asm/a0h/nonmatchings/a0h", f_UpdateStrengthTowerInteriorEntranceActor);

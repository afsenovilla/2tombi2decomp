#include "common.h"
#include "game.h"
#include "m2c.h"

INCLUDE_ASM("asm/a0j/nonmatchings/a0j", func_801090C4);

INCLUDE_ASM("asm/a0j/nonmatchings/a0j", func_80109238);

INCLUDE_ASM("asm/a0j/nonmatchings/a0j", func_8010945C);

INCLUDE_ASM("asm/a0j/nonmatchings/a0j", func_801095A0);

INCLUDE_ASM("asm/a0j/nonmatchings/a0j", f_DispatchGoldenTowerTombaContacts);

INCLUDE_ASM("asm/a0j/nonmatchings/a0j", func_80109AD4);

INCLUDE_ASM("asm/a0j/nonmatchings/a0j", func_80109B34);

INCLUDE_ASM("asm/a0j/nonmatchings/a0j", func_80109BA4);

INCLUDE_ASM("asm/a0j/nonmatchings/a0j", func_80109C7C);

INCLUDE_ASM("asm/a0j/nonmatchings/a0j", func_80109D40);

INCLUDE_ASM("asm/a0j/nonmatchings/a0j", func_80109E40);


s32 func_80109F40(void) {
    return *(s32 *)0x1F800080;
}


void func_80109F50(void *arg0) {
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

INCLUDE_ASM("asm/a0j/nonmatchings/a0j", func_80109FB4);

INCLUDE_ASM("asm/a0j/nonmatchings/a0j", func_8010A0BC);

extern u16 *D_800ECF78;
extern u8 D_800BF816;
extern u8 D_800E806C;
extern s32 D_1F800184;
extern u8 D_800E7E80[];
extern void *D_800ECF80;
extern u8 D_8010D8AC[];
void func_8010CA1C();

void func_8010A11C(void)
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

INCLUDE_ASM("asm/a0j/nonmatchings/a0j", func_8010A174);


void func_8010A2EC(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 4);
    switch (temp_v1) {                              /* irregular */
    case 0:
        M2C_FIELD(arg0, u8 *, 4) = 1U;
        func_8010A174(arg0, 0U);
        func_800752B4(0);
        func_80075D24(0x1FFF);
        return;
    case 1:
        if (func_80026AD0(arg0) != 0) {
            func_8010A174(arg0, M2C_FIELD(arg0, u8 *, 3));
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

INCLUDE_ASM("asm/a0j/nonmatchings/a0j", func_8010A3AC);

INCLUDE_ASM("asm/a0j/nonmatchings/a0j", func_8010A69C);

INCLUDE_ASM("asm/a0j/nonmatchings/a0j", func_8010AA20);

INCLUDE_ASM("asm/a0j/nonmatchings/a0j", func_8010AB20);

INCLUDE_ASM("asm/a0j/nonmatchings/a0j", func_8010ADC4);

INCLUDE_ASM("asm/a0j/nonmatchings/a0j", func_8010B0F8);

INCLUDE_ASM("asm/a0j/nonmatchings/a0j", func_8010B140);

INCLUDE_ASM("asm/a0j/nonmatchings/a0j", func_8010B420);

void func_8010B960(u8 *a)
{
    u16 *p = D_800ECF78;
    u16 t;

    *(u16 **)(a + 0xC) = p;
    *(u16 *)(a + 8) = p[0];
    t = p[1];
    a[7] = 0;
    *(u16 *)(a + 0xA) = t;
}

INCLUDE_ASM("asm/a0j/nonmatchings/a0j", func_8010B98C);

INCLUDE_ASM("asm/a0j/nonmatchings/a0j", func_8010BAD8);

INCLUDE_ASM("asm/a0j/nonmatchings/a0j", func_8010BC8C);

INCLUDE_ASM("asm/a0j/nonmatchings/a0j", f_UpdateGoldenTowerPigElderActor);

s32 func_8010C1D4(void *a)
{
    u8 *r = func_80072DDC(a, 0, 3, 0x10);

    if (r != NULL) {
        *(void **)(r + 0x1C) = func_8010CA1C;
        r[3] = 2;
    }
    return 1;
}

extern s32 D_800BF850;
void func_8010C218(void) {
    D_800BF850 = 1;
}

extern s32 D_800BF850;
s32 func_8010C228(void) {
    D_800BF850 = 2;
    return 1;
}

INCLUDE_ASM("asm/a0j/nonmatchings/a0j", func_8010C23C);

INCLUDE_ASM("asm/a0j/nonmatchings/a0j", func_8010C320);

INCLUDE_ASM("asm/a0j/nonmatchings/a0j", func_8010C3D4);

INCLUDE_ASM("asm/a0j/nonmatchings/a0j", func_8010C488);

INCLUDE_ASM("asm/a0j/nonmatchings/a0j", func_8010C53C);

INCLUDE_ASM("asm/a0j/nonmatchings/a0j", func_8010C5F0);

INCLUDE_ASM("asm/a0j/nonmatchings/a0j", func_8010C958);

INCLUDE_ASM("asm/a0j/nonmatchings/a0j", func_8010CA1C);

INCLUDE_ASM("asm/a0j/nonmatchings/a0j", func_8010CDCC);


void func_8010CE6C(void) {
    func_8007778C();
}

INCLUDE_ASM("asm/a0j/nonmatchings/a0j", func_8010CE8C);


void func_8010CEEC(void *arg0) {
    u8 temp_v0;

    temp_v0 = M2C_FIELD(M2C_FIELD(arg0, void **, 0x10), u8 *, 1);
    M2C_FIELD(arg0, u8 *, 1) = temp_v0;
    if (temp_v0 & 0xFF) {
        func_8010D1F0();
    }
    func_80077B5C(arg0);
}

void func_8010CF3C(u8 *a)
{
    *(void **)(a + 0x3C) = D_800ECF80;
    func_80077B38(a, D_8010D8AC, 6);
    a[0xD] = 0;
    *(s16 *)(a + 0x5C) = 0;
    a[0xB] = 0x10;
    *(s16 *)(a + 0x5A) = 0;
    a[0x47] = 0;
    a[8] = 0;
}

INCLUDE_ASM("asm/a0j/nonmatchings/a0j", func_8010CF94);

INCLUDE_ASM("asm/a0j/nonmatchings/a0j", func_8010D094);


void func_8010D124(void *arg0) {
    if (D_800BF870.pad1[0x29B] != 0) {
        M2C_FIELD(arg0, s8 *, 4) = 3;
        M2C_FIELD(&D_800BF870, s8 *, 0x5E5) = 1;
    }
    M2C_FIELD(arg0, s8 *, 1) = 1;
}

INCLUDE_ASM("asm/a0j/nonmatchings/a0j", func_8010D154);

INCLUDE_ASM("asm/a0j/nonmatchings/a0j", func_8010D1F0);

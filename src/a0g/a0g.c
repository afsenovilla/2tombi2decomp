#include "common.h"
#include "game.h"
#include "m2c.h"

INCLUDE_ASM("asm/a0g/nonmatchings/a0g", func_80109180);

INCLUDE_ASM("asm/a0g/nonmatchings/a0g", func_80109378);

INCLUDE_ASM("asm/a0g/nonmatchings/a0g", func_8010959C);

INCLUDE_ASM("asm/a0g/nonmatchings/a0g", func_801096E0);

INCLUDE_ASM("asm/a0g/nonmatchings/a0g", func_8010978C);

INCLUDE_ASM("asm/a0g/nonmatchings/a0g", f_DispatchCourageTowerTombaContacts);

extern u16 D_800BF812;

void func_80109CC8(u8 *a)
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

void func_80109D28(u8 *a)
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

INCLUDE_ASM("asm/a0g/nonmatchings/a0g", func_80109D98);

INCLUDE_ASM("asm/a0g/nonmatchings/a0g", func_80109E70);

INCLUDE_ASM("asm/a0g/nonmatchings/a0g", func_80109F34);

INCLUDE_ASM("asm/a0g/nonmatchings/a0g", func_8010A034);

extern u8 D_1F800152;
extern u8 D_1F800182;
extern s32 D_1F800080;

s32 func_8010A134(void)
{
    for (D_1F800182 = D_1F800152; D_1F800182 != 0; D_1F800182--) {
    }
    return D_1F800080;
}


void func_8010A16C(void *arg0) {
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

INCLUDE_ASM("asm/a0g/nonmatchings/a0g", func_8010A1D0);

INCLUDE_ASM("asm/a0g/nonmatchings/a0g", func_8010A2B4);

extern u8 D_800BF816;
extern u8 D_800E806C;
extern s32 D_1F800184;
extern u8 D_800E7E80[];

void func_8010A314(void)
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

INCLUDE_ASM("asm/a0g/nonmatchings/a0g", func_8010A36C);

INCLUDE_ASM("asm/a0g/nonmatchings/a0g", func_8010A4F4);

INCLUDE_ASM("asm/a0g/nonmatchings/a0g", f_UpdateCourageTowerExitDoorSequence);

INCLUDE_ASM("asm/a0g/nonmatchings/a0g", f_UpdateCourageTowerLaughingCryingDoorSequence);

INCLUDE_ASM("asm/a0g/nonmatchings/a0g", func_8010AC00);

INCLUDE_ASM("asm/a0g/nonmatchings/a0g", func_8010ADC4);

INCLUDE_ASM("asm/a0g/nonmatchings/a0g", func_8010B08C);

INCLUDE_ASM("asm/a0g/nonmatchings/a0g", f_UpdateCourageTowerInteriorEntranceActor);

INCLUDE_ASM("asm/a0g/nonmatchings/a0g", func_8010B91C);

INCLUDE_ASM("asm/a0g/nonmatchings/a0g", func_8010B9E0);

extern u8 D_800BF916;
void func_8010BB58(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 4);
    switch (temp_v1) {                              /* irregular */
    case 0:
        M2C_FIELD(arg0, u8 *, 4) = 1U;
        func_8010B9E0(arg0, 0U);
        func_8004D8D8(0xD, 0);
        func_800752B4(0);
        func_80075D24(0x1FFF);
        return;
    case 1:
        if (func_80026AD0(arg0) != 0) {
            func_8010B9E0(arg0, M2C_FIELD(arg0, u8 *, 3));
        }
        if (D_800BF916 != 0xFF) {
            func_80040C00(0x62);
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

INCLUDE_ASM("asm/a0g/nonmatchings/a0g", func_8010BC40);

INCLUDE_ASM("asm/a0g/nonmatchings/a0g", func_8010BF28);

INCLUDE_ASM("asm/a0g/nonmatchings/a0g", func_8010C2A4);

INCLUDE_ASM("asm/a0g/nonmatchings/a0g", func_8010C3A4);

INCLUDE_ASM("asm/a0g/nonmatchings/a0g", func_8010C664);

void func_8010C9B4(u32 *p, void *b)
{
    u32 lo = *p;
    u32 packed;

    packed = lo;
    lo = packed & 0xFFFF;
    p += 4;
    func_8010C664(func_8010C3A4(p, b, lo), b, packed >> 16);
}

INCLUDE_ASM("asm/a0g/nonmatchings/a0g", func_8010C9FC);

INCLUDE_ASM("asm/a0g/nonmatchings/a0g", func_8010CCDC);

extern u16 *D_800ECF78;

void func_8010D21C(u8 *a)
{
    u16 *p = D_800ECF78;
    u16 t;

    *(u16 **)(a + 0xC) = p;
    *(u16 *)(a + 8) = p[0];
    t = p[1];
    a[7] = 0;
    *(u16 *)(a + 0xA) = t;
}

INCLUDE_ASM("asm/a0g/nonmatchings/a0g", f_PlayCourageTowerStreamedAudioSegment);

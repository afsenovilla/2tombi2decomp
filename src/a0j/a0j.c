#include "common.h"
#include "game.h"
#include "m2c.h"

INCLUDE_ASM("asm/a0j/nonmatchings/a0j", func_801090C4);

INCLUDE_ASM("asm/a0j/nonmatchings/a0j", func_80109238);

INCLUDE_ASM("asm/a0j/nonmatchings/a0j", func_8010945C);

INCLUDE_ASM("asm/a0j/nonmatchings/a0j", func_801095A0);

INCLUDE_ASM("asm/a0j/nonmatchings/a0j", f_DispatchGoldenTowerTombaContacts);

extern u16 D_800BF812;

void func_80109AD4(u8 *a)
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

void func_80109B34(u8 *a)
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

extern u8 D_1F800150;
extern u8 D_1F800182;
extern u8 D_1F800144;
extern u8 **D_1F80013C;

void func_80109BA4(u8 *a)
{
    u8 **l;
    u8 *e;

    for (D_1F800182 = D_1F800150; D_1F800182 != 0; D_1F800182--) {
    }
    l = D_1F80013C;
    D_1F800182 = D_1F800144;
    while (D_1F800182 != 0) {
        e = *l;
        D_1F800182--;
        l++;
        if ((e[0] & 1) && e[2] == 8) {
            func_8002423C(a, e);
        }
    }
}


void func_80109C7C(void *a)
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
                func_801090C4(a, e);
            } else if (e[2] == 8) {
                func_800205CC(a, e);
            }
        }
    }
}

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

void func_8010B0F8(u32 *p, void *b)
{
    u32 lo = *p;
    u32 packed;

    packed = lo;
    lo = packed & 0xFFFF;
    p += 4;
    func_8010ADC4(func_8010AB20(p, b, lo), b, packed >> 16);
}

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

typedef struct {
    s16 pad0;
    s16 x;
    s16 pad4;
    s16 y;
    s16 pad8;
    s16 z;
} HiPos;
extern u8 D_800E8008[];
extern s16 D_1F800160;
extern s16 D_1F800162;
extern s16 D_1F800164;
extern u8 D_1F8000D0[];

s32 func_8010C23C(u8 *a)
{
    u8 *c = D_800E8008;
    HiPos v;

    switch (a[0x78]) {
    case 0:
        func_8006E1C0(a[3] | 0x80);
        a[0x78]++;
        goto end;
    case 1:
        *(s16 *)(c + 0xA) = D_1F800160;
        *(s16 *)(c + 0xE) = D_1F800162;
        *(s16 *)(c + 0x12) = D_1F800164;
        func_8006E3F4(c, c + 8);
        v.x = 0x1103;
        v.y = -0x2203;
        v.z = 0x1137;
        if (func_8006CEC4(D_1F8000D0, &v, 0xE0) != 0) {
            c[0x66] = 3;
            return 1;
        }
    end:
    default:
        return 0;
    }
}

INCLUDE_ASM("asm/a0j/nonmatchings/a0j", func_8010C320);

INCLUDE_ASM("asm/a0j/nonmatchings/a0j", func_8010C3D4);

INCLUDE_ASM("asm/a0j/nonmatchings/a0j", func_8010C488);

INCLUDE_ASM("asm/a0j/nonmatchings/a0j", func_8010C53C);

INCLUDE_ASM("asm/a0j/nonmatchings/a0j", func_8010C5F0);

s32 func_8010C958(u8 *a, s16 id)
{
    u8 *o;

    switch (a[7]) {
    case 0:
        break;
    case 1:
        if ((*(u8 **)(a + 0x14) = (u8 *)func_8007E038(id, 2)) != NULL) {
            *(s16 *)(a + 0xE) = 0x5A;
            a[7]++;
        }
        break;
    case 2:
        if (--*(s16 *)(a + 0xE) == -1) {
            o = *(u8 **)(a + 0x14);
            if (o[4] < 2) {
                o[4] = 2;
                *(u8 **)(a + 0x14) = NULL;
            }
            a[7] = 0;
        }
        break;
    }
}

INCLUDE_ASM("asm/a0j/nonmatchings/a0j", func_8010CA1C);

void func_8010CDCC(u8 *a)
{
    u8 *r;

    func_80051B70(a, 0xC, 0);
    a[0xD] |= 4;
    (*(u8 **)(a + 0xC0))[0x3F] = 0xE0;
    func_800517F8(a);
    r = func_80072DDC(a, 1, 3, 0x10);
    if (r != NULL) {
        r[3] = 1;
        *(void **)(r + 0x1C) = func_8010CA1C;
        *(s16 *)(r + 0x2E) = *(s16 *)(a + 0x2E);
        *(s16 *)(r + 0x32) = *(s16 *)(a + 0x32);
        *(s16 *)(r + 0x36) = *(s16 *)(a + 0x36);
    }
}


void func_8010CE6C(void) {
    func_8007778C();
}

extern void *D_800ECF80;
extern u8 D_8010D8AC[];

void func_8010CE8C(u8 *a)
{
    *(void **)(a + 0x3C) = D_800ECF80;
    func_80077B38(a, D_8010D8AC, 5);
    a[0xD] = 1;
    a[0xB] = 0x10;
    *(s16 *)(a + 0x5C) = 0;
    *(s16 *)(a + 0x5A) = 0;
    a[0x47] = 0;
    a[8] = 0xC0;
}


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

void func_8010D094(u8 *a)
{
    u8 *o = *(u8 **)(a + 0x10);

    *(void **)(a + 0x3C) = D_800ECF80;
    func_80077B38(a, D_8010D8AC, 4);
    a[0xB] = 0x10;
    a[0xD] = 0;
    *(s16 *)(a + 0x5C) = 0;
    *(s16 *)(a + 0x5A) = 0;
    a[0x47] = 0;
    a[8] = 0xE0;
    *(s16 *)(a + 0x2E) = *(s16 *)(o + 0x2E);
    *(s16 *)(a + 0x32) = *(s16 *)(o + 0x32) - 0x118;
    *(s16 *)(a + 0x36) = *(s16 *)(o + 0x36);
}


void func_8010D124(void *arg0) {
    if (D_800BF870.pad1[0x29B] != 0) {
        M2C_FIELD(arg0, s8 *, 4) = 3;
        M2C_FIELD(&D_800BF870, s8 *, 0x5E5) = 1;
    }
    M2C_FIELD(arg0, s8 *, 1) = 1;
}

INCLUDE_ASM("asm/a0j/nonmatchings/a0j", func_8010D154);

INCLUDE_ASM("asm/a0j/nonmatchings/a0j", func_8010D1F0);

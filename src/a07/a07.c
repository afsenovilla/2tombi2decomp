#include "common.h"
#include "game.h"
#include "m2c.h"
#include "gte.h"
#include "psyq/gtemac.h"

extern u8 D_1F800137;
extern u16 D_1F80009C_efeb;
extern s16 D_1F80018E;
extern u8 *D_1F800184;
extern u16 D_1F80008C;
extern u8 D_800BF840;

void func_8010A660(u8 *a, u8 *b)
{
    s16 ang;

    if (*(u16 *)(a + 0x17E) & 0x200) {
        return;
    }
    if (func_8002300C(a, b, *(s16 *)(b + 0x80) * 2) == 0) {
        return;
    }
    b[0x2B] = 1;
    if (D_1F80008C <= *(s16 *)(a + 0x80) + *(s16 *)(b + 0x80) + 0x5A) {
        b[0x2B] = 2;
        ang = D_1F80009C_efeb & 0xFFF;
        if ((*(s16 *)(a + 0x17E) & 0x8000) && D_1F800137 == 0 && !(b[0] & 2)) {
            if (abs((s16)((ang - *(u16 *)(a + 0x56)) << 4)) < 0x2001) {
                D_1F80018E = 0x4000;
                D_1F800184 = b;
                D_800BF840 = 0x4C;
            }
        }
        if (*(s16 *)(a + 0x80) + *(s16 *)(b + 0x80) >= D_1F80008C) {
            s32 s;
            s32 c;

            ang += 0x800;
            s = (func_80083F50(ang) * (*(s16 *)(a + 0x80) + *(s16 *)(b + 0x80))) >> 12;
            c = func_80083E80(ang) * (*(s16 *)(a + 0x80) + *(s16 *)(b + 0x80));
            *(s16 *)(a + 0x2E) = *(u16 *)(b + 0x2E) + s;
            *(s16 *)(a + 0x36) = *(u16 *)(b + 0x36) - (c >> 12);
        }
    }
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8010A7FC);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8010A8F0);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8010AAA8);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8010ABE4);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8010AE18);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8010AFFC);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8010B1E0);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8010B3F8);

extern s32 D_1F80009C_baed;
extern u8 **D_1F800140;
extern u8 D_1F800146;
extern u8 D_1F800182;
s32 func_8010B5BC(u8 *a)
{
    u8 **list = D_1F800140;
    u8 *b;

    for (D_1F800182 = D_1F800146; D_1F800182 != 0;) {
        b = *list++;
        D_1F800182--;
        if (b[0xC] == 9 && (b[0] & 1) && func_80022F04(a, b) != 0) {
            s32 temp_s0 = (s32) (func_80083F50(D_1F80009C_baed) * (M2C_FIELD(a, s16 *, 0x80) + M2C_FIELD(b, s16 *, 0x80))) >> 0xC;
            s32 temp_lo = func_80083E80(D_1F80009C_baed) * (M2C_FIELD(a, s16 *, 0x80) + M2C_FIELD(b, s16 *, 0x80));
            M2C_FIELD(a, s16 *, 0x2E) = (s16) (M2C_FIELD(b, u16 *, 0x2E) + temp_s0);
            M2C_FIELD(a, s16 *, 0x36) = (s16) (M2C_FIELD(b, u16 *, 0x36) - (temp_lo >> 0xC));
            return 1;
        }
    }
    return 0;
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8010B6F4);

extern s16 D_1F80018C;
extern u8 D_800BF873;
void func_8010B944(u8 *a, u8 *b)
{
    s32 *ang;
    s32 d;

    if (func_8002300C(a, b, *(s16 *)(b + 0x80)) == 0) {
        return;
    }
    ang = &D_1F80009C_baed;
    {
        s32 temp_s0 = (s32) (func_80083F50(*ang + 0x800) * (M2C_FIELD(a, s16 *, 0x80) + M2C_FIELD(b, s16 *, 0x80))) >> 0xC;
        s32 temp_lo = func_80083E80(*ang + 0x800) * (M2C_FIELD(a, s16 *, 0x80) + M2C_FIELD(b, s16 *, 0x80));
        M2C_FIELD(a, s16 *, 0x2E) = (s16) (M2C_FIELD(b, u16 *, 0x2E) + temp_s0);
        M2C_FIELD(a, s16 *, 0x36) = (s16) (M2C_FIELD(b, u16 *, 0x36) - (temp_lo >> 0xC));
    }
    if (b[2] == 0xF && D_800BF873 != 0) {
        return;
    }
    if (D_1F800137 != 0) {
        return;
    }
    {
        u16 w = *(u16 *)(a + 0x56);
        s32 v = *(u16 *)ang & 0xFFF;

        D_1F80018C = v;
        d = abs((s16)((v - w) << 4));
    }
    if (d < 0x4001 && (a[5] != 0x1F || b == *(u8 **)(a + 0x10))) {
        if (b[2] == 0xE) {
            D_1F80018E = 0x4400;
        } else {
            D_1F80018E = 0x4800;
        }
        D_1F800184 = b;
        b[0x2B] = 1;
        if (a[0x61] != 0x80) {
            D_800BF840 = 0x4D;
        }
    }
}

void func_8010BAD0(u8 *a, u8 *b)
{
    s16 ang;

    if (*(u16 *)(a + 0x17E) & 0x200) {
        return;
    }
    if (func_8002300C(a, b, *(s16 *)(b + 0x80) + 0x96) == 0) {
        return;
    }
    ang = *(u16 *)&D_1F80009C_baed & 0xFFF;
    if (!(*(s16 *)(a + 0x17E) & 0x8000) && D_1F80018E == 0 && D_1F800137 == 0 && !(b[0] & 2)) {
        if (abs((s16)((ang - *(u16 *)(a + 0x56)) << 4)) < 0x2001 && (a[5] != 0x1F || b == *(u8 **)(a + 0x10))) {
            D_1F80018E = 0x1400;
            D_1F800184 = b;
            D_800BF840 = 0x4B;
        }
    }
    if (b[0] & 2) {
        if (D_1F80008C <= *(s16 *)(b + 0x80)) {
            b[0x29] = 1;
        }
    } else if (*(s16 *)(a + 0x80) + *(s16 *)(b + 0x80) >= D_1F80008C) {
        s32 temp_s0;
        s32 temp_lo;

        ang += 0x800;
        temp_s0 = (s32) (func_80083F50(ang) * (M2C_FIELD(a, s16 *, 0x80) + M2C_FIELD(b, s16 *, 0x80))) >> 0xC;
        temp_lo = func_80083E80(ang) * (M2C_FIELD(a, s16 *, 0x80) + M2C_FIELD(b, s16 *, 0x80));
        M2C_FIELD(a, s16 *, 0x2E) = (s16) (M2C_FIELD(b, u16 *, 0x2E) + temp_s0);
        M2C_FIELD(a, s16 *, 0x36) = (s16) (M2C_FIELD(b, u16 *, 0x36) - (temp_lo >> 0xC));
    }
}

extern u8 D_800BF808[];
void func_8010BC9C(u8 *a, u8 *b)
{
    s16 ang;

    if (func_8002300C(a, b, *(s16 *)(b + 0x80) + 0xC8) == 0) {
        return;
    }
    ang = *(u16 *)&D_1F80009C_baed & 0xFFF;
    if ((*(u16 *)(a + 0x17E) & 0x7C00) && D_800BF808[1] == 0 && D_1F800137 == 0 && !(b[0] & 2)) {
        if (abs((s16)((ang - *(u16 *)(a + 0x56)) << 4)) < 0x4001) {
            D_1F80018E = 0x1800;
            D_1F800184 = b;
            D_800BF808[0x38] = 0x4B;
        }
    }
    if (*(s16 *)(a + 0x80) + *(s16 *)(b + 0x80) >= D_1F80008C) {
        s32 temp_s0;
        s32 temp_lo;

        ang += 0x800;
        temp_s0 = (s32) (func_80083F50(ang) * (M2C_FIELD(a, s16 *, 0x80) + M2C_FIELD(b, s16 *, 0x80))) >> 0xC;
        temp_lo = func_80083E80(ang) * (M2C_FIELD(a, s16 *, 0x80) + M2C_FIELD(b, s16 *, 0x80));
        M2C_FIELD(a, s16 *, 0x2E) = (s16) (M2C_FIELD(b, u16 *, 0x2E) + temp_s0);
        M2C_FIELD(a, s16 *, 0x36) = (s16) (M2C_FIELD(b, u16 *, 0x36) - (temp_lo >> 0xC));
    }
}

void func_8010BE08(u8 *a, u8 *b) {
    s16 d;
    s32 ang;

    if (D_800BF873 != 0) {
        return;
    }
    if (M2C_FIELD(a, s16 *, 0x17E) & 0x8200) {
        return;
    }
    if (func_8002300C(a, b, M2C_FIELD(b, s16 *, 0x80) + 0xC8) == 0) {
        return;
    }
    ang = D_1F80009C_efeb & 0xFFF;
    if (D_1F80018E == 0 && D_1F800137 == 0 && !(b[0] & 2) && a[5] != 2) {
        d = (ang - M2C_FIELD(a, u16 *, 0x56)) << 4;
        if (abs(d) <= 0x2000 && (a[5] != 0x1F || b == M2C_FIELD(a, u8 **, 0x10))) {
            D_1F80018E = 0x1200;
            D_1F800184 = b;
            D_800BF840 = 0x4B;
        }
    }
}

void func_8010BF14(u8 *a, u8 *b)
{
    s16 ang;

    if (func_8002300C(a, b, *(s16 *)(b + 0x80) + 0xC8) == 0) {
        return;
    }
    ang = D_1F80009C_efeb & 0xFFF;
    if (!(*(s16 *)(a + 0x17E) & 0x8200) && D_1F80018E == 0 && D_1F800137 == 0 && !(b[0] & 2) && D_800BF873 == 0 && a[5] != 2) {
        if (abs((s16)((ang - *(u16 *)(a + 0x56)) << 4)) < 0x2001 && (a[5] != 0x1F || b == *(u8 **)(a + 0x10))) {
            D_1F80018E = 0x1200;
            D_1F800184 = b;
            D_800BF840 = 0x4B;
        }
    }
    if (*(s16 *)(a + 0x80) + *(s16 *)(b + 0x80) >= D_1F80008C) {
        s32 s;
        s32 c;

        ang += 0x800;
        s = (func_80083F50(ang) * (*(s16 *)(a + 0x80) + *(s16 *)(b + 0x80))) >> 12;
        c = func_80083E80(ang) * (*(s16 *)(a + 0x80) + *(s16 *)(b + 0x80));
        *(s16 *)(a + 0x2E) = *(u16 *)(b + 0x2E) + s;
        *(s16 *)(a + 0x36) = *(u16 *)(b + 0x36) - (c >> 12);
    }
}

void func_8010C0B8(u8 *a, u8 *b)
{
    s16 dx = *(s16 *)(a + 0x2E) - *(s16 *)(b + 0x2E);
    s16 dz = *(s16 *)(a + 0x36) - *(s16 *)(b + 0x36);

    if ((u16)func_80084080(dx * dx + dz * dz) <= *(s16 *)(a + 0x80) + *(s16 *)(b + 0x80)) {
        s32 ang = func_80085690(-dz, dx) & 0xFFF;
        s32 temp_s0 = (s32) (func_80083F50(ang) * (M2C_FIELD(a, s16 *, 0x80) + M2C_FIELD(b, s16 *, 0x80))) >> 0xC;
        s32 temp_lo = func_80083E80(ang) * (M2C_FIELD(a, s16 *, 0x80) + M2C_FIELD(b, s16 *, 0x80));
        M2C_FIELD(a, s16 *, 0x2E) = (s16) (M2C_FIELD(b, u16 *, 0x2E) + temp_s0);
        M2C_FIELD(a, s16 *, 0x36) = (s16) (M2C_FIELD(b, u16 *, 0x36) - (temp_lo >> 0xC));
    }
}

void func_8010C1C8(u8 *a, u8 *b)
{
    s16 ang;
    s32 d;
    s32 t;
    s32 k;

    if (b[2] == 0xB) {
        func_8010A660(a, b);
        return;
    }
    if (*(s16 *)(a + 0x17E) & 0x8200) {
        if (func_8002300C(a, b, *(s16 *)(b + 0x80)) == 0) {
            return;
        }
        ang = D_1F80009C_efeb & 0xFFF;
        goto push;
    }
    if (func_8002300C(a, b, *(s16 *)(b + 0x80) * 2) == 0) {
        return;
    }
    b[0x2B] = 1;
    if (D_1F80008C <= *(s16 *)(a + 0x80) + *(s16 *)(b + 0x80) + 0x5A) {
        b[0x2B] = 2;
        ang = D_1F80009C_efeb & 0xFFF;
                if (D_1F800137 == 0 && !(b[0] & 2)) {
            k = 0x4C;
            if (b[2] == k) {
                t = *(u16 *)(a + 0x56) & 0xFFF;
                *(u16 *)(a + 0x56) = t;
                if ((u32)(t - 0x600) > 0x400) {
                    goto push;
                }
                d = ang - t;
            } else {
                d = ang - *(u16 *)(a + 0x56);
            }
            if (abs((s16)(d << 4)) < 0x2001) {
                D_1F80018E = 0x4000;
                D_1F800184 = b;
                D_800BF840 = k;
            }
        }
    push:
        if (*(s16 *)(a + 0x80) + *(s16 *)(b + 0x80) >= D_1F80008C) {
            s32 s;
            s32 c;

            ang += 0x800;
            s = (func_80083F50(ang) * (*(s16 *)(a + 0x80) + *(s16 *)(b + 0x80))) >> 12;
            c = func_80083E80(ang) * (*(s16 *)(a + 0x80) + *(s16 *)(b + 0x80));
            *(s16 *)(a + 0x2E) = *(u16 *)(b + 0x2E) + s;
            *(s16 *)(a + 0x36) = *(u16 *)(b + 0x36) - (c >> 12);
        }
    }
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8010C3C4);

extern u8 **D_1F80013C;
extern u8 D_1F800144;
void f_DispatchCircusMovingActorContacts(u8 *a)
{
    u8 **l = D_1F80013C;
    u8 *b;

    D_1F800182 = D_1F800144;
    while (D_1F800182 != 0) {
        b = *l;
        D_1F800182--;
        l++;
        if (b[0] & 1) {
            if (b[0xC] == 9) {
                func_8010C1C8(a, b);
            } else if (b[2] != 8) {
                if (b[2] == 0x54 && func_80022F04(a, b) != 0) {
                s32 temp_s0 = (s32) (func_80083F50(D_1F80009C_baed) * (M2C_FIELD(a, s16 *, 0x80) + M2C_FIELD(b, s16 *, 0x80))) >> 0xC;
                s32 temp_lo = func_80083E80(D_1F80009C_baed) * (M2C_FIELD(a, s16 *, 0x80) + M2C_FIELD(b, s16 *, 0x80));
                M2C_FIELD(a, s16 *, 0x2E) = (s16) (M2C_FIELD(b, u16 *, 0x2E) + temp_s0);
                M2C_FIELD(a, s16 *, 0x36) = (s16) (M2C_FIELD(b, u16 *, 0x36) - (temp_lo >> 0xC));
                }
            } else {
                func_8010BAD0(a, b);
            }
        }
    }
}

extern u8 **D_1F800148;
extern u8 D_1F800150;
void f_DispatchCircusActorContacts(u8 *a)
{
    u8 **l = D_1F800148;
    u8 *b;

    D_1F800182 = D_1F800150;
    while (D_1F800182 != 0) {
        b = *l;
        D_1F800182--;
        l++;
        if (b[0] & 1) {
            switch (b[2]) {
            case 14:
            case 15:
                func_8010B944(a, b);
                break;
            case 12:
                func_80020868(a, b);
                break;
            case 23:
                func_8010C0B8(a, b);
                break;
            case 18:
                func_8002311C(a, b);
                break;
            case 24:
                func_80020B08(a, b);
                break;
            case 31:
                func_80023764(a, b);
                break;
            case 74:
                func_8010AFFC(a, b);
                break;
            case 54:
                func_8010BE08(a, b);
                break;
            case 9:
            case 36:
            case 50:
                func_8010BF14(a, b);
                break;
            case 76:
                func_8010A8F0(a, b);
                break;
            case 103:
                {
                    s16 dx = *(u16 *)(a + 0x2E) - *(u16 *)(b + 0x2E);
                    s16 dz = *(u16 *)(a + 0x36) - *(u16 *)(b + 0x36);
                    s32 d = func_80084080(dx * dx + dz * dz);

                    if ((u16)d <= *(s16 *)(a + 0x80) + 0xC8
                        && (u16)(*(u16 *)(a + 0x84) + (*(u16 *)(a + 0x32) - *(u16 *)(b + 0x32) + 0x140)) <= *(s16 *)(a + 0x86) + 0x140) {
                        b[0x29] = 1;
                        func_8001F830(a, b);
                    }
                    func_8010BC9C(a, b);
                }
                break;
            case 81:
                func_8010ABE4(a, b);
                break;
            }
        }
    }
}

extern s8 D_1F800182_85c9[];
extern int rcos(int a);
extern int rsin(int a);
extern s8 D_800BF80D;
extern s8 D_1F800182_85c9[];
extern s8 D_1F800154_248c[];
extern s8 D_1F80015C_055a[];
extern void (*D_8009D1D4[])(void);
extern s8 D_800BF80D;
extern void (*D_8009D22C[])(void);
extern void (*D_8009D314[])(u8 *);
extern void (*D_8009D52C[])(u8 *);
extern void (*D_800A4AF8[])(void);
extern void (*D_800A4B50[])(void);
extern void (*D_800A4AA0[])(u8 *);
extern s32 (*D_800A3B78[])(u8 *);
void f_DispatchCircusActorContactCleanup(u8 *a)
{
    u8 **list;
    u8 *e;

    if (*(s16 *)(a + 0x16E) == 0 || D_800BF80D != 0 || (*(u16 *)(a + 0x17E) & 0x200)) {
        return;
    }
    list = *(u8 ***)D_1F800154_248c;
    *(u8 *)D_1F800182_85c9 = *(u8 *)D_1F80015C_055a;
    while (*(u8 *)D_1F800182_85c9 != 0) {
        e = *list;
        *(u8 *)D_1F800182_85c9 = *(u8 *)D_1F800182_85c9 - 1;
        list++;
        if (e[0] == 1) {
            switch (e[2]) {
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
                func_80022060(a, e);
                break;
            case 5:
                func_8010B6F4(a, e);
                break;
            }
        } else if (e[0] == 5 && e[2] == 5) {
            func_8010B6F4(a, e);
        }
    }
}

void func_8010CA60(u8 *a, u8 *b)
{
    s16 dx = *(u16 *)(a + 0x2E) - *(u16 *)(b + 0x2E);
    s16 dz = *(u16 *)(a + 0x36) - *(u16 *)(b + 0x36);
    s32 d = func_80084080(dx * dx + dz * dz);
    s32 ang;

    if ((u16)d > *(s16 *)(a + 0x80) + *(s16 *)(b + 0x80)) {
        return;
    }
    if ((u16)((*(u16 *)(a + 0x32) - *(u16 *)(b + 0x32)) + ((*(u16 *)(b + 0x84) + *(u16 *)(a + 0x86)) - *(u16 *)(a + 0x84))) > *(s16 *)(a + 0x86) + *(s16 *)(b + 0x86)) {
        return;
    }
    ang = func_80085690(-dz, dx);
    D_1F80009C_baed = ang;
    {
        s32 temp_s0 = (s32) (func_80083F50(ang) * (M2C_FIELD(a, s16 *, 0x80) + M2C_FIELD(b, s16 *, 0x80))) >> 0xC;
        s32 temp_lo = func_80083E80(D_1F80009C_baed) * (M2C_FIELD(a, s16 *, 0x80) + M2C_FIELD(b, s16 *, 0x80));
        M2C_FIELD(a, s16 *, 0x2E) = (s16) (M2C_FIELD(b, u16 *, 0x2E) + temp_s0);
        M2C_FIELD(a, s16 *, 0x36) = (s16) (M2C_FIELD(b, u16 *, 0x36) - (temp_lo >> 0xC));
    }
}

void f_DispatchCircusSupportContacts(u8 *a)
{
    u8 **l = D_1F800148;
    u8 *p;
    u8 **l2;

    D_1F800182 = D_1F800150;
    while (D_1F800182 != 0) {
        p = *l;
        D_1F800182--;
        l++;
        if (p[0] & 1) {
            switch (p[2]) {
            case 0xE ... 0xF:
            case 0x32:
                func_800241FC(a, p);
                break;
            case 0x4A:
                func_8010B1E0(a, p);
                break;
            case 0x4C:
                func_8010B3F8(a, p);
                break;
            }
        }
    }
    l2 = D_1F80013C;
    D_1F800182 = D_1F800144;
    while (D_1F800182 != 0) {
        p = *l2;
        D_1F800182--;
        l2++;
        if (p[0] & 1) {
            if (p[0xC] == 9) {
                func_8010CA60(a, p);
            } else if (p[0xC] == 2) {
                if (p[2] == 0x53) {
                    func_8010AAA8(a, p);
                } else if (p[2] == 8) {
                    if (a[2] != 5) {
                        func_8002423C(a, p);
                    } else {
                        func_800241FC(a, p);
                    }
                } else if (p[2] == 0x54) {
                    func_800241FC(a, p);
                }
            }
        }
    }
}

extern u8 D_800E7E80[];
extern u8 **D_1F800154;
extern u8 D_1F80015C;
extern u8 D_1F800183;
/* func_8010D004, inlined */
static inline void func_8010D004_inl(void) {
    u8 **list = D_1F800154;
    u8 *a;

    for (D_1F800183 = D_1F80015C; D_1F800183 != 0;) {
        a = *list++;
        D_1F800183--;
        if (!(a[0] & 2)) {
            switch (a[2]) {
            case 0:
            case 4:
            case 5:
                f_DispatchCircusSupportContacts(a);
                break;
            }
        }
    }
}
/* func_8010CEDC, inlined */
static inline void func_8010CEDC_inl(u8 *p)
{
    if (p[0x17B] == 0 && (s8)D_800BF808[5] == 0 && D_800BF808[0x31] == 0) {
        func_8010A7FC(p);
    }
}
void func_8010CD8C(void)
{
    u8 *p = D_800E7E80;

    func_8002288C(p);
    switch (p[0]) {
    case 1:
    case 3:
    case 4:
    case 5:
    case 7:
        f_DispatchCircusActorContactCleanup(p);
        f_DispatchCircusMovingActorContacts(p);
        f_DispatchCircusActorContacts(p);
        break;
    case 0:
    case 2:
    case 6:
        break;
    }
    func_8010D004_inl();
    func_8010CEDC_inl(p);
}

void func_80118184();
void func_8010CEDC(u8 *p)
{
    if (p[0x17B] == 0 && (s8)D_800BF808[5] == 0 && D_800BF808[0x31] == 0) {
        func_8010A7FC();
    }
}

extern u8 *D_800BF844;
s32 func_8010CF30(u8 *p)
{
    if (p[0x174]) {
        return 1;
    }
    {
        u32 r = *(u16 *)(p + 0x17E) & 0x200;
        return r != 0;
    }
}

extern s8 D_1F80009C[];
void func_8010CF5C(void *arg0, void *arg1) {
    s32 temp_lo;
    s32 temp_s0;

    if (func_80022F04() != 0) {
        temp_s0 = (s32) (func_80083F50(*((s32 *)D_1F80009C)) * (M2C_FIELD(arg0, s16 *, 0x80) + M2C_FIELD(arg1, s16 *, 0x80))) >> 0xC;
        temp_lo = func_80083E80(*((s32 *)D_1F80009C)) * (M2C_FIELD(arg0, s16 *, 0x80) + M2C_FIELD(arg1, s16 *, 0x80));
        M2C_FIELD(arg0, s16 *, 0x2E) = (s16) (M2C_FIELD(arg1, u16 *, 0x2E) + temp_s0);
        M2C_FIELD(arg0, s16 *, 0x36) = (s16) (M2C_FIELD(arg1, u16 *, 0x36) - (temp_lo >> 0xC));
    }
}

typedef struct { s16 x, y, z, pad; } AreaSVec;
typedef struct {
    u16 type;
    u8 pad2[6];
    u8 mag0;
    u8 mag1;
    u8 x;
    u8 y;
} AreaPadAnalog;
typedef struct { u8 pad0[7]; u8 unk7; u8 pad8[0x29]; u8 unk31; s16 unk32; } AreaState808_7;
void func_8010D004(void) {
    u8 **list = D_1F800154;
    u8 *a;

    for (D_1F800183 = D_1F80015C; D_1F800183 != 0;) {
        a = *list++;
        D_1F800183--;
        if (!(a[0] & 2)) {
            switch (a[2]) {
            case 0:
            case 4:
            case 5:
                f_DispatchCircusSupportContacts(a);
                break;
            }
        }
    }
}

typedef struct { s16 a, b, c, d; } SpeedRow8010A8D0;
extern SpeedRow8010A8D0 D_800A455C_c872[];
extern SpeedRow8010A8D0 D_800A4574_8b42;
extern u16 D_1F8000F2;
#define B8(o) (*(u8 *)(a + (o)))
#define I16(o) (*(s16 *)(a + (o)))
#define W16(o) (*(u16 *)(a + (o)))
void func_8010D0B4(u8 *a) {
    SpeedRow8010A8D0 *p;
    u32 acc;
    s32 four = 4;
    u16 dec, max;
    s32 t, step, dec2, v, ang;
    u16 ang2;
    u8 f;

    if (B8(0x174) & 0x30) {
        p = &D_800A4574_8b42;
    } else {
        p = &D_800A455C_c872[B8(0x6D)];
    }
    acc = (u32)(p->a * 5) >> 2;
    dec = (u32)(p->b * 5) >> 2;
    max = (u32)(p->c * 5) >> 2;
    t = (p->d * 5) >> 2;
    dec2 = t - 0x240;
    step = t;
    if (D_800BF808[0xE] != 0 && D_800BF808[0x45] != 0) {
        v = 0xC0F;
        I16(0x15E) = v;
        max = v;
    } else if (B8(0x165) != 0) {
        acc = (u32)((s16)acc * 19) >> 4;
        dec = (s16)dec * 3;
        v = ((s16)max * 19) >> 4;
        I16(0x15E) = v;
        max = v;
    } else {
        switch ((s8)B8(0x14B)) {
        case 1:
            v = 0xF13;
            break;
        case 2:
            v = 0x1553;
            break;
        case 0:
        default:
            v = (p->c * 5) >> 2;
            break;
        }
        I16(0x15E) = v;
    }
    f = B8(0x147);
    if (f & 0x80) {
        W16(0x44) -= step;
        if (I16(0x44) <= 0) {
            W16(0x44) = 0;
            if (B8(0x149) == 4) {
                W16(0x56) = W16(0x172);
            }
            B8(0x149) = 2;
        }
        return;
    }
    ang = (((f & 0x7F) << 5) - D_1F8000F2 + 0x1000) & 0xFFF;
    ang2 = ang;
    if ((u32)(((ang - W16(0x56)) & 0xFFF) - 0x601) < 0x3FF) {
        acc = four;
        if (B8(0x149) == acc) {
            W16(0x44) -= step;
            if (I16(0x44) <= 0) {
                W16(0x44) = max;
                B8(0x149) = 0;
                W16(0x56) = ang;
            }
            return;
        }
        if (I16(0x44) >= (s16)max * 3 / 4) {
            W16(0x172) = ang;
            B8(0x149) = acc;
            I16(0x96) = abs(I16(0x44)) / (s16)step - 7;
            if (I16(0x96) <= 0) {
                I16(0x96) = 1;
            }
            W16(0x44) -= step;
            return;
        }
        W16(0x44) -= dec;
        if (I16(0x44) < 0) {
            W16(0x44) = 0;
        }
        I16(0x56) = func_800776F8(ang, I16(0x56), 0x80, acc);
    } else {
        if (B8(0x149) == 2) {
            B8(0x149) = 0;
            W16(0x44) += acc;
        } else if (B8(0x149) == 4) {
            W16(0x44) -= step;
            if (I16(0x44) <= 0) {
                W16(0x44) = max;
                B8(0x149) = 0;
                W16(0x56) = ang;
            }
        } else {
            if (I16(0x44) < (s16)acc) {
                W16(0x44) = acc;
            } else if (I16(0x15E) < I16(0x44)) {
                W16(0x44) -= dec2;
                if (I16(0x44) < I16(0x15E)) {
                    W16(0x44) = I16(0x15E);
                }
            } else {
                W16(0x44) += dec;
                if (I16(0x15E) < I16(0x44)) {
                    W16(0x44) = I16(0x15E);
                }
            }
            B8(0x149) = 0;
        }
        I16(0x56) = func_800776F8(ang2, I16(0x56), 0x80, acc);
    }
}

typedef struct { u16 acc, inc, max, dec; } SpeedTbl;
extern SpeedTbl D_800A455C[];
extern SpeedTbl D_800A4574;
#define S16(o) (*(s16 *)(a + (o)))
#define U16(o) (*(u16 *)(a + (o)))
void func_8010D49C(u8 *a)
{
    SpeedTbl *t;
    u32 acc;
    u32 inc;
    u16 dec;
    u16 dec2;
    u8 c;
    u16 ang;

    if (a[0x174] & 0x30) {
        t = &D_800A4574;
    } else {
        t = &D_800A455C[a[0x6D]];
    }
    acc = t->acc;
    inc = t->inc;
    dec = t->dec;
    dec2 = dec - 0x240;
    if (a[0x165] != 0) {
        do {
            acc = (u32)((s16)acc * 19) >> 4;
        } while (0);
        inc = (u32)((s16)inc * 19) >> 4;
        S16(0x15E) = ((s16)t->max * 19) >> 4;
    } else {
        switch ((s8)a[0x14B]) {
        case 1:
            S16(0x15E) = 0xC0F;
            break;
        case 2:
            S16(0x15E) = 0x110F;
            break;
        case 0:
        default:
            S16(0x15E) = t->max;
            break;
        }
    }
    c = a[0x147];
    if (c & 0x80) {
        U16(0x44) -= dec;
        if (S16(0x44) <= 0) {
            S16(0x44) = 0;
            a[0x149] = 2;
        }
    } else {
    ang = (((c & 0x7F) << 5) - D_1F8000F2 + 0x1000) & 0xFFF;
    if (a[0x149] == 2) {
        a[0x149] = 0;
        U16(0x44) += acc;
    } else {
        if (S16(0x44) < (s16)acc) {
            S16(0x44) = acc;
        } else if (S16(0x15E) < S16(0x44)) {
            U16(0x44) -= dec2;
            if (S16(0x44) < S16(0x15E)) {
                S16(0x44) = S16(0x15E);
            }
        } else {
            U16(0x44) += inc;
            if (S16(0x15E) < S16(0x44)) {
                S16(0x44) = S16(0x15E);
            }
        }
        a[0x149] = 0;
    }
    S16(0x56) = func_800776F8(ang, S16(0x56), 0x40, inc);
    }
}

typedef struct { s16 pad; s16 x; s16 pad2; s16 y; s16 pad3; s16 z; } PosV;
void func_8010D6A8(u8 *a)
{
    PosV v;
    PosV w;
    u8 *e;

    if (--*(s16 *)(a + 0x40) != 0) {
        return;
    }
    if (a[0x29] == 3) {
        v.x = *(s16 *)(a + 0x2E);
        v.y = *(s16 *)(a + 0x32) + *(s16 *)(a + 0x84);
        v.z = *(s16 *)(a + 0x36);
        func_8003116C(8, &v, -0x50);
        func_80074590(2, 0, 0);
        if (a[0x46] == 0x10) {
            *(s16 *)(a + 0x40) = 0xB;
        } else {
            *(s16 *)(a + 0x40) = 9;
        }
        return;
    }
    switch (a[0x46]) {
    case 4:
    case 6:
    case 8:
    case 10:
        if (*(s16 *)(a + 0x42) == 0) {
            func_80074590(0, -3, 0);
        } else {
            func_80074590(0, 5, 0);
        }
        *(s16 *)(a + 0x40) = 9;
        *(s16 *)(a + 0x42) = 1 - *(s16 *)(a + 0x42);
        break;
    case 12:
    case 14:
        func_80074590(1, 0, 0);
        *(s16 *)(a + 0x40) = 9;
        break;
    case 16:
        func_80074590(1, 0, 0);
        *(s16 *)(a + 0x40) = 0xB;
        {
            u8 *q = a + 0x2C;

            w.x = *(s16 *)(q + 2);
            w.y = *(s16 *)(q + 6) + *(s16 *)(a + 0x84);
            w.z = *(s16 *)(q + 0xA);
        }
        e = func_8003116C(0x35, &w, -0x5A);
        if (e != NULL) {
            e[0x28] |= 0x80;
        }
        break;
    default:
        *(s16 *)(a + 0x40) = 9;
        break;
    }
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8010D84C);

extern AreaPadAnalog D_800ECF48;
extern u16 D_800ECF54;
void func_8010DAB4(u8 *a) {
    AreaPadAnalog *p = &D_800ECF48;
    u8 m;

    if (p->y + p->x != 0 && p->type == 7) {
        m = p->mag1;
        if (m < p->mag0) {
            m = p->mag0;
        }
        a[0x14B] = m;
        a[0x147] = ((u32)func_80085690((s8)p->y, (s8)p->x) & 0xFFF) >> 5;
        return;
    }
    switch (D_800ECF54 & 0xF0) {
    case 0x20:
        a[0x147] = 0;
        break;
    case 0x80:
        a[0x147] = 0x40;
        break;
    case 0x10:
        a[0x147] = 0x60;
        break;
    case 0x40:
        a[0x147] = 0x20;
        break;
    case 0x30:
        a[0x147] = 0x70;
        break;
    case 0x60:
        a[0x147] = 0x10;
        break;
    case 0x90:
        a[0x147] = 0x50;
        break;
    case 0xC0:
        a[0x147] = 0x30;
        break;
    default:
        a[0x147] |= 0x80;
        a[0x14B] = 0;
        return;
    }
    a[0x14B] = 3;
}

void func_8010DC3C(u8 *a)
{
    u8 *t = a + 0x60;
    u8 *p = D_800E7E80;
    PosV v;
    u8 *e;

    switch (a[4]) {
    case 0:
        a[0] = 2;
        func_8006ACAC(a);
        **(s16 **)(a + 0xC0) = -0x96;
        *(s16 *)(a + 0x54) = 0;
        *(s16 *)(a + 0x56) = 0;
        *(s16 *)(a + 0x58) = 0;
        a[4]++;
        func_80031558(a, a[2] - 1);
        {
            s16 r = *(s16 *)(p + 0x56);

            *(s16 *)(t + 0xA) = 0x400;
            *(s16 *)(t + 8) = r;
        }
    case 1:
        switch (a[5]) {
        case 0:
            func_80074590(0xB, -2, 0);
            func_80074590(0x22, 0, 0);
            a[5]++;
            break;
        case 1:
            if (p[0x146] == 2) {
                v.x = *(s16 *)(a + 0x2E);
                v.y = *(s16 *)(a + 0x32) + 0x5A;
                v.z = *(s16 *)(a + 0x36);
                func_80074590(0x32, 0, 0);
                e = func_8003116C(0x13, &v, -0x50);
                if (e != NULL) {
                    e[0x28] |= 0x80;
                }
                func_80031470(2, &v, 0, t + 8);
                a[5]++;
            }
            break;
        }
        if (p[0x146] == 0) {
            a[4] = 2;
        }
        func_8006B020(a, 1);
        a[1] = 1;
        break;
    case 2:
        a[4]++;
        break;
    case 3:
        func_8007AB44(a);
        break;
    }
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8010DE18);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8010DF90);

extern u8 D_800BF80E;
static inline void fall_step(u8 *a)
{
    func_8010DF90(a);
    if (a[0x29] != 0) {
        if (*(s16 *)(a + 0x50) > 0x1400) {
            func_80074590(3, 0, 0);
        }
        *(s16 *)(a + 0x50) = 0;
    } else {
        *(s16 *)(a + 0x50) += 0x800;
        if (*(s16 *)(a + 0x50) > 0x3000) {
            *(s16 *)(a + 0x50) = 0x3000;
        }
        *(s32 *)(a + 0x30) += *(s16 *)(a + 0x50) << 8;
    }
}
void func_8010E244(u8 *a)
{
    func_80076D68(a);
    switch (a[6]) {
    case 0:
        a[0x146] = 0;
        func_80053D90(a);
        func_80054198(a);
        func_80054D14(a, 0xE1, 4);
        func_80074590(0x39, 0, 0);
        *(s16 *)(a + 0x40) = 0x1E;
        a[6]++;
        func_800551C4(a);
    case 1:
        func_80055D5C(a);
        *(s16 *)(a + 0x32) += 0xA;
        fall_step(a);
        if (*(s16 *)(a + 0x40) == 0) {
            a[5] = 0;
            a[6] = 0;
        } else {
            (*(s16 *)(a + 0x40))--;
        }
        break;
    case 2:
        D_800BF80E = 0;
        a[0x146] = 0;
        func_80053D90(a);
        func_80054198(a);
        func_80054D14(a, 0xE1, 4);
        func_80074590(0x39, 0, 0);
        *(s16 *)(a + 0x40) = 0x1E;
        a[6]++;
        break;
    case 3:
        func_800551C4(a);
        if (--*(s16 *)(a + 0x40) == 0) {
            D_800BF80E = 1;
            a[4] = 4;
            a[5] = 0x20;
            a[6] = 0;
            a[7] = 0;
        }
        break;
    }
}

#define H(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define U_d0c0(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define W_d1fb(p, o) (*(s32 *)((u8 *)(p) + (o)))
extern AreaSVec D_1F8000C0_f4ad;
void func_8010E448(u8 *a) {
    s32 s;
    s32 c;

    switch (a[6]) {
    case 0:
        a[0x146] = 0;
        func_80053D90(a);
        func_80054198(a);
        func_80054D14(a, 0xE0, 4);
        func_80074590(0x3A, 0, 0);
        a[0x167] = 0x1E;
        a[7] = 0;
        H(a, 0x40) = 7;
        H(a, 0x42) = 0;
        a[6]++;
    case 1:
        a[0x14B] = 3;
        a[0x147] &= 0x7F;
        func_8010D0B4(a);
        func_80054E80(a, 0);
        s = (func_80083F50(H(a, 0x56)) * H(a, 0x44)) >> 4;
        c = func_80083E80(H(a, 0x56)) * H(a, 0x44);
        W_d1fb(a, 0x2C) += s;
        W_d1fb(a, 0x34) -= c >> 4;
        D_1F8000C0_f4ad.x = 0;
        if ((u32)(a[0x29] - 2) >= 2) {
            D_1F8000C0_f4ad.y = U_d0c0(a, 0x62);
            D_1F8000C0_f4ad.z = 0;
            func_8012EE08(a + 0x2C, &D_1F8000C0_f4ad, 0);
        }
        func_80076D68(a);
        H(a, 0x32) += 0xA;
        func_8010DF90(a);
        if (a[0x29] != 0) {
            func_8010D6A8(a);
            if (a[0x29] != 0) {
                if (H(a, 0x50) > 0x1400) {
                    func_80074590(3, 0, 0);
                }
                H(a, 0x50) = 0;
                goto next;
            }
        }
        if ((s16)(H(a, 0x50) += 0x800) > 0x3000) {
            H(a, 0x50) = 0x3000;
        }
        W_d1fb(a, 0x30) += H(a, 0x50) << 8;
    next:
        if (a[0x167] == 0) {
            a[5] = 0;
            a[6] = 0;
        } else {
            a[0x167]--;
        }
        break;
    case 2:
        D_800BF80E = 0;
        a[0x146] = 0;
        func_80053D90(a);
        func_80054198(a);
        func_80054D14(a, 0xDF, 4);
        func_80074590(0x3A, 0, 0);
        H(a, 0x40) = 0x1E;
        a[6]++;
        break;
    case 3:
        func_80076D68(a);
        func_800551C4(a);
        if (--H(a, 0x40) == 0) {
            D_800BF80E = 1;
            a[4] = 4;
            a[5] = 0x20;
            a[6] = 0;
            a[7] = 0;
        }
        break;
    }
}

extern u16 D_1F800192;
void func_8010E728(u8 *a)
{
    u16 ang;

    switch (a[6]) {
    case 0:
        *(s16 *)(a + 0x58) = 0;
        D_800BF80E = 0;
        a[6]++;
        func_80054D14(a, 2, 0);
    case 1:
        ang = D_1F800192 & 0xFFF;
        if ((*(s16 *)(a + 0x56) = func_800776F8(ang, *(s16 *)(a + 0x56), 0x100)) == ang) {
            a[6]++;
            D_800BF80E = 1;
        }
        break;
    case 2:
        break;
    }
    func_80076D68(a);
    func_8010DF90(a);
    if (a[0x29] != 0) {
        if (*(s16 *)(a + 0x50) > 0x1400) {
            func_80074590(3, 0, 0);
        }
        *(s16 *)(a + 0x50) = 0;
        return;
    }
    *(s16 *)(a + 0x50) += 0x800;
    if (*(s16 *)(a + 0x50) > 0x3000) {
        *(s16 *)(a + 0x50) = 0x3000;
    }
    *(s32 *)(a + 0x30) += *(s16 *)(a + 0x50) << 8;
}

extern s16 D_1F80026C;
extern s16 D_1F800270;
extern s16 D_1F800272;
extern s16 D_1F800276;
extern void func_80083DE0(void *, s32, s32, s32, s32);
static inline s32 bebc_yaw(u8 *a, s32 x, s32 z) {
    return func_80085690(H(a, 0x36) - z, x - H(a, 0x2E));
}
void func_8010E864(u8 *a) {
    u8 *b = *(u8 **)(a + 0x10);
    s32 dx;
    s32 dz;
    register s32 t asm("$2");
    u8 *p2;

    switch (a[6]) {
    case 0:
        func_80054198(a);
        if (H(a, 0x152) == 0x1200) {
            func_80042354(1, 1);
            func_80054D14(a, 2, 6);
            H(a, 0x7C) = bebc_yaw(a, H(b, 0x2E), H(b, 0x36)) & 0xFFF;
            a[6] = 5;
        } else if (H(a, 0x152) == 0x1400) {
            func_80054D14(a, 2, 6);
            H(a, 0x7C) = bebc_yaw(a, H(b, 0x2E), H(b, 0x36)) & 0xFFF;
            a[6] = 8;
            func_8006E1C0(1);
        } else if (H(a, 0x152) == 0x1800) {
            func_80054D14(a, 2, 6);
            H(a, 0x7C) = bebc_yaw(a, H(b, 0x2E), H(b, 0x36)) & 0xFFF;
            a[6] = 0xA;
        } else if (D_800BF870.unk0 == 7 && H(a, 0x152) == 0x1000) {
            a[6] = 2;
        } else {
            if (H(a, 0x152) == 0x1500) {
                D_1F800137 = 2;
            }
            if (H(a, 0x152) == 0x1000) {
                s32 p = *(u16 *)&D_1F800272;
                s32 q = *(u16 *)&D_1F800276;
                H(a, 0x7A) = p;
                H(a, 0x7E) = q;
            } else {
                s32 p = *(u16 *)&D_1F80026C;
                s32 q = *(u16 *)&D_1F800270;
                H(a, 0x7A) = p;
                H(a, 0x7E) = q;
            }
            do {
                dx = H(b, 0x2E) + H(a, 0x7A) - H(a, 0x2E);
                dz = H(b, 0x36) - H(a, 0x7E) - H(a, 0x36);
                H(a, 0x7C) = func_80085690(-dz, dx) & 0xFFF;
                dx = (dx << 8) / 16;
                dz = (dz << 8) / 16;
            } while (0);
             
            __asm__("" : "=r"(p2) : "0"(a));
            H(p2, 0x4E) = dx;
            H(p2, 0x52) = dz;
            H(p2, 0x40) = 0x10;
            p2[6]++;
            func_80054D14(p2, 4, 6);
        }
        break;
    case 1:
        func_80076D68(a);
        W_d1fb(a, 0x2C) += H(a, 0x4E) << 8;
        W_d1fb(a, 0x34) += H(a, 0x52) << 8;
        if ((s16)(H(a, 0x40) % 7) == 0) {
            func_80074590(0, 5, 0);
        }
        if (--H(a, 0x40) == 0) {
            goto inc;
        }
        break;
    case 2:
        func_80076D68(a);
        if (H(a, 0x152) == 0x1100) {
            if (b[3] < 0x64 && H(a, 0x36) > H(b, 0x36)) {
                t = (U_d0c0(b, 0x56) + 0x400) & 0xFFF;
            } else {
                t = (U_d0c0(b, 0x56) - 0x400) & 0xFFF;
            }
        } else if (H(a, 0x152) == 0x1500) {
            t = 0x400;
        } else if (D_800BF870.unk0 == 7 && H(a, 0x152) == 0x1000) {
            t = func_800782B0(a + 0x2C, H(b, 0x2E), H(b, 0x36)) & 0xFFF;
        } else {
            t = (U_d0c0(b, 0x56) - 0x400) & 0xFFF;
        }
        b = (u8 *)t;
        H(a, 0x56) = func_800776F8((s32)b, H(a, 0x56), 0x100);
        if (H(a, 0x56) == (s32)b) {
            if (H(a, 0x152) == 0x1000) {
                func_80054D14(a, 0xCD, 6);
            inc:
                a[6]++;
            } else {
                a[6] = 4;
            }
        }
        break;
    case 3:
        if (func_80076D68(a) == 1) {
            a[6]++;
        }
        break;
    case 4:
        if (H(a, 0x152) == 0x1000) {
            a[5] = 2;
            a[6] = 0;
            b[0xBF] = 1;
            func_80054D14(a, 0xCE, 3);
            if (D_800BF870.unk0 == 7) {
                break;
            }
        } else {
            a[5] = 3;
            a[6] = 0;
        }
        H(a, 0x2E) = U_d0c0(b, 0x2E) + U_d0c0(a, 0x7A);
        H(a, 0x36) = U_d0c0(b, 0x36) - U_d0c0(a, 0x7E);
        break;
    case 5:
        func_80076D68(a);
        H(a, 0x56) = func_800776F8(H(a, 0x7C), H(a, 0x56), 0x100);
        if (H(a, 0x56) == H(a, 0x7C)) {
            a[5] = 4;
            a[6] = 0;
        }
        break;
    case 6:
        func_80054D14(a, 2, 6);
        a[6]++;
        H(a, 0x7C) = bebc_yaw(a, H(b, 0x2E), H(b, 0x36)) & 0xFFF;
    case 7:
        H(a, 0x56) = func_800776F8(H(a, 0x7C), H(a, 0x56), 0x100);
        func_80076D68(a);
        if (D_1F80018E != 0x4400 && D_1F80018E != 0x4800) {
            a[0x61] = 0;
            func_80054198(a);
            a[5] = 0;
            a[6] = 0;
            a[7] = 0;
        }
        break;
    case 8:
        func_80076D68(a);
        H(a, 0x56) = func_800776F8(H(a, 0x7C), H(a, 0x56), 0x100);
        if (H(a, 0x56) == H(a, 0x7C)) {
            H(a, 0x40) = 0x3C;
            a[6]++;
            b[0] = 3;
            b[4] = 2;
            b[5] = 2;
            b[6] = 0;
        }
        break;
    case 9:
        func_80076D68(a);
        if (--H(a, 0x40) == 0) {
            func_8006E1E4();
            func_80054198(a);
            a[5] = 0;
            a[6] = 0;
            a[7] = 0;
        }
        break;
    case 10:
        func_80076D68(a);
        H(a, 0x56) = func_800776F8(H(a, 0x7C), H(a, 0x56), 0x100);
        if (H(a, 0x56) == H(a, 0x7C)) {
            a[5] = 0x1B;
            a[6] = 0;
            a[7] = 0;
        }
        break;
    }
}

void func_8010EEB8(u8 *a)
{
    switch (a[6]) {
    case 0:
        *(s16 *)(a + 0x40) = 0x11;
        *(s16 *)(a + 0x44) = 0x1000;
        a[6]++;
        func_80054D14(a, 4, 0);
    case 1: {
        s32 x = (func_80083F50(*(s16 *)(a + 0x56)) * *(s16 *)(a + 0x44)) >> 4;
        s32 z = func_80083E80(*(s16 *)(a + 0x56)) * *(s16 *)(a + 0x44);

        *(s32 *)(a + 0x2C) += x;
        *(s32 *)(a + 0x34) -= z >> 4;
        func_80076D68(a);
        if (*(s16 *)(a + 0x40) % 7 == 0) {
            func_80074590(0, 5, 0);
        }
        if (--*(s16 *)(a + 0x40) == 0) {
            a[6]++;
        }
        break;
    }
    case 2:
        a[5] = 0;
        a[6] = 0;
        a[7] = 0;
        func_80054D14(a, 2, 6);
        if (D_1F800137 == 1) {
            D_800BF80E = 1;
        }
        break;
    case 5:
        *(s16 *)(a + 0x40) = 0x11;
        *(s16 *)(a + 0x44) = 0x800;
        a[6] = 1;
        func_80054D14(a, 4, 0);
        break;
    default:
        return;
    }
    a[0x29] = 0x81;
}

void func_8010F08C(u8 *a)
{
    s32 r = func_80076D68(a);

    switch (a[6]) {
    case 0: {
        u8 *t;

        D_800BF80E = 0;
        func_80054D14(a, 0xC7, 3);
        t = *(u8 **)(a + 0x10);
        *(s16 *)(a + 0x40) = 0;
        a[6]++;
        *(s16 *)(a + 0x7C) = func_80085690(-(s16)(*(s16 *)(t + 0x36) - *(s16 *)(a + 0x36)), (s16)(*(s16 *)(t + 0x2E) - *(s16 *)(a + 0x2E))) & 0xFFF;
        break;
    }
    case 1:
        if (*(s16 *)(a + 0x40) == 0xC) {
            func_80074590(0x26, 0, 0);
        }
        (*(s16 *)(a + 0x40))++;
        *(s16 *)(a + 0x56) = func_800776F8(*(s16 *)(a + 0x7C), *(s16 *)(a + 0x56), 0x100);
        if (r == 1) {
            func_80054D14(a, 2, 6);
            *(s16 *)(a + 0x40) = 7;
            a[6]++;
        }
        break;
    case 2:
        if (--*(s16 *)(a + 0x40) == 0) {
            if (D_1F800137 == 1) {
                D_800BF80E = D_1F800137;
                a[5] = 0x22;
            } else {
                a[5] = 0x20;
            }
            a[6] = 0;
        }
        break;
    }
    func_8010DF90(a);
    if (a[0x29] != 0) {
        if (*(s16 *)(a + 0x50) > 0x1400) {
            func_80074590(3, 0, 0);
        }
        *(s16 *)(a + 0x50) = 0;
        return;
    }
    *(s16 *)(a + 0x50) += 0x800;
    if (*(s16 *)(a + 0x50) > 0x3000) {
        *(s16 *)(a + 0x50) = 0x3000;
    }
    *(s32 *)(a + 0x30) += *(s16 *)(a + 0x50) << 8;
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8010F28C);

extern s16 D_1F80019E;
extern u8 D_800BFE55;
extern u16 D_1F80017C;
extern u16 D_1F800210;
extern u16 D_800BF812;
#define S16(p, o) (*(s16 *)((u8 *)(p) + (o)))
void func_8010F954(u8 *a)
{
    u8 *t = *(u8 **)(a + 0x10);

    switch (a[4]) {
    case 0:
        D_1F80019E = 0;
        S16(a, 0x54) = 0;
        a[4]++;
        if (S16(t, 0x17E) >= 0) {
            S16(a, 0x40) = 0x50;
            S16(a, 0x42) = 0x6E;
        } else {
            S16(a, 0x40) = 0x28;
            S16(a, 0x42) = 0x37;
        }
        S16(a, 0xE) = 0;
        break;
    case 1:
        if ((a[1] = t[1]) == 0) {
            break;
        }
        if (D_800BFE55 != 0 && abs(S16(t, 0x44)) > 0xC00 && !(D_1F80017C & 7)) {
            func_800312D4(0x2C, t + 0x2C, -0x14);
        }
        if (S16(t, 0x17E) >= 0) {
            S16(a, 0x40) = 0x50;
            S16(a, 0x42) = 0x6E;
        } else {
            S16(a, 0x40) = 0x28;
            S16(a, 0x42) = 0x37;
        }
        *(s32 *)(a + 0x2C) = *(s32 *)(t + 0x2C);
        *(s32 *)(a + 0x30) = *(s32 *)(t + 0x30);
        *(s32 *)(a + 0x34) = *(s32 *)(t + 0x34);
        if (t[0x29] != 0) {
            S16(a, 0x48) = S16(t, 0x2E);
            S16(a, 0x4A) = S16(t, 0x32) + S16(t, 0x84);
            S16(a, 0x4C) = S16(t, 0x36);
            S16(a, 0x56) = S16(t, 0x140);
            S16(a, 0x58) = S16(t, 0x142);
        } else if (t[0x16B] == 8) {
            u16 x = S16(a, 0x2E);
            u16 z = S16(a, 0x36);
            u16 h;
            u16 g;

            S16(a, 0x48) = x;
            h = D_800BF812;
            g = D_1F800210;
            S16(a, 0x4C) = z;
            S16(a, 0x58) = 0;
            S16(a, 0x56) = g;
            S16(a, 0x4A) = h;
        } else if (D_1F80019E != 0) {
            S16(a, 0x4A) = D_1F80019E;
            S16(a, 0x48) = S16(a, 0x2E);
            S16(a, 0x4C) = S16(a, 0x36);
        } else {
            a[1] = 0;
        }
        if (a[1] != 0) {
            S16(a, 0x4E) = 0x80 - ((S16(a, 0x4A) - S16(t, 0x32) - 0x78) >> 2);
            if (S16(a, 0x4E) < 0) {
                S16(a, 0x4E) = 0;
                a[1] = 0;
            } else if (S16(a, 0x4E) > 0x80) {
                S16(a, 0x4E) = 0x80;
            }
            S16(a, 0x50) = 0x100 - ((S16(a, 0x4A) - S16(t, 0x32) - 0x78) >> 2);
            if (S16(a, 0x50) < 0) {
                S16(a, 0x50) = 0;
                a[1] = 0;
            } else if (S16(a, 0x50) > 0x100) {
                S16(a, 0x50) = 0x100;
            }
        }
        break;
    case 2:
    case 3:
        func_8007A624(a);
        break;
    }
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8010FC30);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8010FF78);

void func_8010DC3C();
void func_80110258(u8 *a)
{
    u8 *p;
    s32 k;

    k = a[6];
    switch (k) {
    case 0:
        p = func_8007AB20();
        if (p != NULL) {
            *(s16 *)(p + 0x2E) = I16(0x2E);
            *(s16 *)(p + 0x32) = I16(0x32);
            *(s16 *)(p + 0x36) = I16(0x36);
            *(s16 *)(p + 0x56) = I16(0x56);
            *(void **)(p + 0x1C) = func_8010DC3C;
            p[2] = 7;
        }
        a[0x146] = 1;
        a[6]++;
        func_80054D14(a, 0x99, 5);
        I16(0x40) = 0xD;
        break;
    case 1:
        func_80076D68(a);
        if (--I16(0x40) == 0) {
            a[0x146] = 2;
            I16(0x40) = 3;
            a[6]++;
            (*(u8 **)(a + 0x10))[0x2B] = k;
        }
        break;
    case 2:
        if (--I16(0x40) == 0) {
            if (D_1F800137 == 2) {
                D_1F800137 = 0;
            }
            a[0x146] = 0;
            a[5] = 0;
            a[6] = 0;
            a[7] = 0;
            func_80054D14(a, 2, 6);
        }
        break;
    }
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_801103D8);

extern u8 D_1F80027A;
extern u8 D_800BF80A;
void func_80110850(u8 *a)
{
    u8 s;

    D_1F80027A = 1;
    a[0x17B] = 1;
    if (D_800BF80A >= 3 && a[6] != 0) {
        func_8005FB54();
        return;
    }
    s = a[6];
    switch (s) {
    case 0:
        D_800BF808[6] = 0;
        func_8004ED0C(D_800BF808[3], 1);
        if (D_800BF808[2] == 2) {
            a[0] |= 2;
        } else if (D_800BF808[2] == 3) {
            func_80054198(a);
            func_8005FA84(a);
            return;
        }
        func_80054D14(a, 0x72, 0);
        a[6]++;
    case 1:
        if (func_80076D68(a) == 1) {
            a[6]++;
            func_80054D14(a, 0x73, 2);
        }
        break;
    case 2:
        if (func_80076D68(a) == 1) {
            if (D_800BF80A == s) {
                a[5] = 0;
                a[6] = 0;
                a[7] = 0;
                a[0] &= 1;
                func_80054D14(a, 2, 5);
            } else {
                a[6]++;
            }
            D_800BF808[2] = 0;
            D_800BF808[6] = 1;
        }
        break;
    case 3:
        func_80076D68(a);
        break;
    }
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80110A30);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_801110F8);

INCLUDE_ASM("asm/a07/nonmatchings/a07", f_UpdateCircusRestrictedTombaActionState);

INCLUDE_ASM("asm/a07/nonmatchings/a07", f_UpdateCircusTombaActionState);

extern u16 D_800E7E68;
extern u8 D_800BF80F;
extern u16 D_1F800166;
extern u16 D_1F800190;
void func_80112220(u8 *a) {
    u16 held;
    u16 pad;

    switch (a[4]) {
    case 0:
        func_80058648(a, 0);
        break;
    case 1:
        held = D_800E7E68;
        pad = D_800ECF54;
        if (D_800BF80F != 0 || D_1F800137 != 0) {
            D_800E7E68 = 0;
            D_800ECF54 = 0;
            if (D_800ECF48.type == 7) {
                D_800ECF48.x = 0;
                D_800ECF48.y = 0;
            }
        }
        f_UpdateCircusRestrictedTombaActionState(a);
        func_800597AC(a);
        D_800E7E68 = held;
        D_800ECF54 = pad;
        break;
    case 2:
    case 3:
        break;
    case 4:
        held = D_800E7E68;
        pad = D_800ECF54;
        if (D_1F800137 == 0) {
            D_800E7E68 = 0;
            D_800ECF54 = 0;
        } else {
            D_800E7E68 = D_1F800166;
            D_800ECF54 = D_1F800190;
        }
        if (D_800ECF48.type == 7) {
            D_800ECF48.x = 0;
            D_800ECF48.y = 0;
        }
        f_UpdateCircusTombaActionState(a);
        func_800597AC(a);
        D_800E7E68 = held;
        D_800ECF54 = pad;
        break;
    }
}

void func_8011237C(u8 *a)
{
    u8 *o = *(u8 **)(a + 0x10);

    switch (a[6]) {
    case 0:
        o[0x2B] = 1;
        a[6]++;
        D_800BF80E = 1;
    case 1:
        func_80076D68(a);
        if (D_1F800137 == 0) {
            D_800BF80E = 0;
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

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80112428);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80112508);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80112770);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_801128BC);

s32 func_801129A8(s32 arg0, s32 arg1, s32 arg2) {
    s32 var_v0;
    s16 temp_a0;

    temp_a0 = (arg0 - arg1) & 0xFFF;
    if (temp_a0 == 0) {
        return arg1 & 0xFFF;
    }
    if ((u32)temp_a0 < 0x800) {
        if ((s32) temp_a0 >= 0x100) {
            if (arg2 == 0) {
                var_v0 = arg1 + 0x10;
            } else {
                var_v0 = arg1 + (arg2 << 5);
            }
        } else if ((s32) temp_a0 >= 0x30) {
            if (arg2 == 0) {
                var_v0 = arg1 + 8;
            } else {
                var_v0 = arg1 + (arg2 * 8);
            }
        } else if ((s32) temp_a0 >= 0x20) {
            if (arg2 == 0) {
                var_v0 = arg1 + 4;
            } else {
                var_v0 = arg1 + (arg2 * 4);
            }
        } else if ((s32) temp_a0 >= 0x10) {
            if (arg2 == 0) {
                var_v0 = arg1 + 2;
            } else {
                var_v0 = arg1 + (arg2 * 2);
            }
        } else {
            var_v0 = arg1 + 1;
        }
    } else if ((s32) temp_a0 < 0xF01) {
        if (arg2 == 0) {
            var_v0 = arg1 - 0x10;
        } else {
            var_v0 = arg1 - (arg2 << 5);
        }
    } else if ((s32) temp_a0 < 0xFD1) {
        if (arg2 == 0) {
            var_v0 = arg1 - 8;
        } else {
            var_v0 = arg1 - (arg2 * 8);
        }
    } else if ((s32) temp_a0 < 0xFE1) {
        if (arg2 == 0) {
            var_v0 = arg1 - 4;
        } else {
            var_v0 = arg1 - (arg2 * 4);
        }
    } else if ((s32) temp_a0 < 0xFF1) {
        if (arg2 == 0) {
            var_v0 = arg1 - 2;
        } else {
            var_v0 = arg1 - (arg2 * 2);
        }
    } else {
        var_v0 = arg1 - 1;
    }
    return var_v0 & 0xFFF;
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80112B1C);

extern u8 D_1F8000D0[];
extern s16 D_1F8000EE;
extern u8 D_800BF816;
void func_80112CE8(u8 *a, s16 b)
{
    s16 v;
    s16 y;
    s16 d;
    u8 *c;

    if (a[0x64] == 1) {
        s32 ang;
        if (D_800BF816 != 0) {
            ang = *(s16 *)(a + 0x6E);
        } else {
            ang = *(s16 *)(a + 0xA);
        }
        v = -(func_80083E80(ang) * *(s16 *)(a + 0x6C)) >> 12;
    } else {
        v = (func_80083E80(*(s16 *)(a + 0xA)) * (D_1F8000EE + *(s32 *)(a + 0x58))) >> 12;
    }
    y = b + v;
    *(s16 *)(a + 0xE) = y;
    c = D_1F8000D0;
    d = *(s16 *)(c + 6) - y;
    if ((u16)(d + 10) >= 21) {
        *(s32 *)(c + 4) -= d << 13;
    } else {
        *(s16 *)(c + 6) = y;
        a[0x66] |= 2;
    }
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80112DEC);

extern u8 D_1F8000D0[];
void func_80113394(u8 *a, s32 ang) {
    u8 *t = D_800E7E80;
    u8 *sc;
    s16 r;
    s16 x, z;

    r = -(func_80083F50(M2C_FIELD(a, s16 *, 0xA)) * (M2C_FIELD((sc = D_1F8000D0), s16 *, 0x1E) + M2C_FIELD(a, s32 *, 0x58))) >> 12;
    x = M2C_FIELD(t, s16 *, 0x2E) + ((func_80083F50((s16)ang) * r) >> 12);
    z = M2C_FIELD(t, s16 *, 0x36) - ((func_80083E80((s16)ang) * r) >> 12);
    M2C_FIELD(sc, s16 *, 0x2) = x;
    M2C_FIELD(sc, s16 *, 0xA) = z;
    a[0x66] |= 1;
}

#define U(p, o) (*(u16 *)((p) + (o)))
#define S(p, o) (*(s16 *)((p) + (o)))
extern u8 D_800BF817;
extern u8 *D_80131D88[];
void func_80113470(u8 *t, s32 i)
{
    u8 *p;
    u32 o;

    o = U(t, 0x6A) & 0xF0;
    p = D_80131D88[D_800BF817];
    p = p + i * 8 + (o >> 1);
    U(t, 0x2E) = U(p, 0);
    if (S(t, 0x17E) < 0) {
        U(t, 0x32) = U(p, 2) + 0x46;
    } else {
        U(t, 0x32) = U(p, 2);
    }
    U(t, 0x36) = U(p, 4);
    U(t, 0x56) = U(p, 6);
}

typedef struct {
    s16 a;
    s16 b;
    s16 c;
    s16 d;
} SV;
extern u8 D_800BFA2D;
extern u8 *D_800BF860_c64f;
extern u8 D_800BFA2C;
void f_UpdateCircusClosetKeyActor();
void func_801134E8(u8 *a0, u8 *a1)
{
    s32 neg = 0;
    s16 d = *(u16 *)(a1 + 0x36) - 0x2968;
    s16 m = d;

    if (d < 0) {
        neg = 1;
        m = -d;
    }
    m = m / 4;
    if (m > 0x300) {
        m = 0x300;
    }
    if (!neg) {
        m = 0x800 - m;
    } else {
        m = m + 0x800;
    }
    *(s16 *)(a0 + 0x52) = m;
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80113550);

void func_80113644(void)
{
    CameraState *c = &g_CameraState;

    c->unk6C = 0x500;
    c->unk6E = 0x100;
}

void func_80113660(u8 *a) {
    u8 *t = D_800E7E80;
    s16 v[6];

    switch (a[4]) {
    case 0:
        M2C_FIELD(a, s16 *, 0x52) = 0x1400 - D_1F8000F2;
        a[4]++;
        break;
    case 1:
        v[1] = M2C_FIELD(t, s16 *, 0x2E);
        v[3] = M2C_FIELD(t, s16 *, 0x32) - 0x80;
        v[5] = M2C_FIELD(t, s16 *, 0x36);
        func_8006E3F4(a, v);
        func_80112B1C(a, t, M2C_FIELD(a, s16 *, 0x52));
        func_80112CE8(a, (s16)(M2C_FIELD(t, s16 *, 0x32) - 0x80));
        break;
    }
}

extern u8 D_800BF818_7697;
extern u8 *D_1F800138;
s32 f_UpdateCircusInteriorSceneTransition(u8 *a)
{
    u8 *g;
    u8 *h;

    switch (a[5]) {
    case 0:
        if (D_800BF808[0x10] != 1) {
            return 0;
        }
        a[3] = D_800BF808[0xF] + 1;
        func_800269BC(a);
        a[5]++;
        break;
    case 1:
        g = D_800BF808;
        if (g[7] != 0) {
            return 0;
        }
        func_800269EC(a);
        *(s16 *)(D_1F800138 + 0x4E) = 2;
        a[5]++;
        g[0x10] = 2;
        return 1;
    case 2:
        if (D_800BF80F != 0) {
            return 0;
        }
        func_800269FC(a);
        a[5]++;
        break;
    case 3:
        if (D_800BF818_7697 != 3) {
            return 0;
        }
        func_800269BC(a);
        a[5]++;
        break;
    case 4:
        h = D_800BF808;
        if (h[7] != 0) {
            return 0;
        }
        func_80026A1C(a);
        func_800269EC(a);
        if (*(s32 *)(h + 0x48) != 0) {
            *(s16 *)(D_1F800138 + 0x4E) = 5;
        } else {
            *(s16 *)(D_1F800138 + 0x4E) = 4;
        }
        D_800BF818_7697 = 4;
        a[5]++;
        break;
    case 5:
        if (D_800BF80F != 0) {
            return 0;
        }
        a[5] = 0;
        func_800269FC(a);
        break;
    }
    return 0;
}

extern u8 D_800BF808_s07[];
extern u8 D_800BF871_s07;
extern u8 *D_801321D4[];
u8 *func_80072DDC();
static inline u8 *GS07(void)
{
    return (u8 *)&D_800BF870;
}
static inline u8 *GB07(void)
{
    return D_800BF808_s07;
}
void f_SpawnCircusSceneActorsFromPlacementTable(u8 *a, s32 mode)
{
    u8 *e;
    u8 *p;

    H(a, 8) = 0;
    e = D_801321D4[mode];
    if (e[0] == 0xFF) {
        return;
    }
    do {
        if (e[0xB] == 1 && ((U_d0c0(GS07(), 0x5E6) >> D_800BF870.unk0) & 1)) {
            goto next;
        }
        if (e[0xB] == 2 && GS07()[3] != 0) {
            goto next;
        }
        if (mode != 0 && H(a, 8) >= 0xF) {
            goto next;
        }
        switch (e[0xA]) {

        case 0:
            break;
        case 1:
            if (mode == 10) {
                GB07()[0x45] = 1;
            } else {
                GB07()[0x45] = 0;
            }
            U_d0c0(GB07(), 8) = U_d0c0(e, 4);
            U_d0c0(GB07(), 0xA) = U_d0c0(e, 6);
            U_d0c0(GB07(), 0xC) = U_d0c0(e, 8);
            break;
        case 5:
            if (GS07()[0x166] < 8) {
                break;
            }
            goto next;
        case 6:
            if (GS07()[0x166] == 9) {
                break;
            }
            goto next;
        case 8:
            if (GS07()[0x68] == 0) {
                goto next;
            }
            if (GS07()[0x1D5] & 1) {
                goto next;
            }
            break;
        case 10:
            if (GS07()[0x1D5] & 2) {
                goto next;
            }
            break;
        case 16:
            if (GS07()[0x9F] != 0xFF) {
                break;
            }
            goto next;
        case 17:
            if (GS07()[0x1B9] == 10) {
                break;
            }
            goto next;
        case 18:
            if (GS07()[0xA3] != 0xFF) {
                break;
            }
            if (GS07()[0x7F] != 0xFF) {
                break;
            }
            goto next;
        case 20:
            if (GS07()[3] == 0) {
                goto next;
            }
            if ((GS07()[0x1CD] >> e[3]) & 1) {
                goto next;
            }
            break;
        case 22:
            if (GS07()[0x1DE] < 3) {
                break;
            }
            if (GS07()[0x1D8] != 2) {
                break;
            }
            goto next;
        case 23:
            if (GS07()[0x3E] == 0) {
                goto next;
            }
            if (GS07()[0xCC] != 0xFF) {
                break;
            }
            goto next;
        case 24:
            if (GS07()[0x164] != 0) {
                goto next;
            }
            break;
        }
        p = func_80072DDC(a, e[0], e[1], e[2]);
        if (p != NULL) {
            *(s32 *)(p + 0x2C) = H(e, 4) << 16;
            *(s32 *)(p + 0x30) = H(e, 6) << 16;
            *(s32 *)(p + 0x34) = H(e, 8) << 16;
            p[3] = e[3];
            H(p, 0x54) = 0;
            H(p, 0x56) = 0;
            H(p, 0x58) = 0;
            *(s32 *)(p + 0x1C) = *(s32 *)(e + 0xC);
            if (mode != 0) {
                *(u8 **)(a + (H(a, 8) << 2) + 0xC) = p;
                H(a, 8)++;
            }
        }
    next:
        e += 0x10;
    } while (e[0] != 0xFF);
}

typedef struct { s16 x, y, w, h; } ClutRect;
typedef struct {
    u8 *ptr;
    u8 *clut;
    s16 x;
    s16 y;
} ClutCycle;
extern ClutCycle D_80132B14[];
extern s8 D_8013FF40[];
void func_80113C20(s32 arg0) {
    ClutRect r;
    s32 i;
    ClutCycle *e;
    u8 *data;

    if (arg0 == 0) {
        s8 *p;
        i = 4;
        p = &D_8013FF40[i];
        do {
            *p-- = 0;
        } while (--i >= 0);
        return;
    }
    if (D_800BF873) {
        return;
    }
    e = D_80132B14;
    for (i = 0; i < 5; i++, e++) {
        if (--D_8013FF40[i] <= 0) {
            if (e->ptr[0] == 0xFF) {
                e->ptr -= e->ptr[1];
            }
            data = e->clut + e->ptr[0] * 32;
            D_8013FF40[i] = e->ptr[1];
            r.x = e->x;
            r.y = e->y;
            r.w = 16;
            r.h = 1;
            func_80081218(&r, data);
            e->ptr += 2;
        }
    }
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80113D58);

extern u8 *D_800BF544_37fb;
extern u8 *D_800ED8C8_35cc;
#define OT4 (*(u32 *)(ot + 0x10))
extern s16 D_1F800160;
extern s16 D_1F800164;
void func_801140A0(void) {
    u8 *p;
    u8 *q;
    u8 *q2;
    u8 *p3;
    u8 *ot;
    u8 *ot1;
    u8 *ot3;
    s32 x;
    s32 y;
    u8 c;
    u8 g;
    u8 b;

    c = 0xFF;
    x = (D_1F800164 - 0x1680) / 182;
    y = (D_1F800160 - 0xA00) / 182;
    p = D_800BF544_37fb;
    p[7] = 0x64;
    if (D_1F80017C & 2) {
        c = 0x80;
    }
    p[4] = c;
    g = 0x20;
    if (D_1F80017C & 2) {
        g = 0x40;
    }
    p[5] = g;
    b = 0x20;
    if (D_1F80017C & 2) {
        b = 0x40;
    }
    *(s16 *)(p + 8) = x + 0xEC;
    *(s16 *)(p + 0xA) = y + 0xA0;
    *(u16 *)(p + 0xE) = 0x74E7;
    p[6] = b;
    p[0xC] = 0x50;
    p[0xD] = 0x58;
    *(s16 *)(p + 0x10) = 8;
    do {
        *(s16 *)(p + 0x12) = 8;
    } while (0);
    ot1 = D_800ED8C8_35cc;
    do {
        *(u32 *)p = (*(u32 *)(ot1 + 0x10)) | 0x04000000;
    } while (0);
    (*(u32 *)(ot1 + 0x10)) = (u32)p;
    q = D_800BF544_37fb;
    D_800BF544_37fb += 0x14;
    p = D_800BF544_37fb;
    p[7] = 0x65;
    *(s16 *)(p + 8) = 0xF0;
    *(s16 *)(p + 0xA) = 0xA4;
    *(u16 *)(p + 0xE) = 0x7527;
    p[0xC] = 0xC0;
    p[0xD] = 0x50;
    *(s16 *)(p + 0x10) = 0x40;
    *(s16 *)(p + 0x12) = 0x40;
    do {
        ot = D_800ED8C8_35cc;
        *(u32 *)(q + 0x14) = OT4 | 0x04000000;
        OT4 = (u32)p;
    } while (0);
    q2 = D_800BF544_37fb;
    p3 = q2 + 0x14;
    D_800BF544_37fb = p3;
    func_80083DE0(p3, 0, 0, 0x19, 0);
    ot3 = D_800ED8C8_35cc;
    *(u32 *)(q2 + 0x14) = (*(u32 *)(ot3 + 0x10)) | 0x02000000;
    do {
        (*(u32 *)(ot3 + 0x10)) = (u32)p3;
    } while (0);
    D_800BF544_37fb += 0xC;
}

void func_8012E2A0(void);
void func_80114294(u8 *a)
{
    u8 *g;

    switch (a[4]) {
    case 0:
        a[4] = 1;
        f_SpawnCircusSceneActorsFromPlacementTable(a, 0);
        func_80113C20(0);
        func_8012E2A0();
        func_8004D8D8(0x16, 0);
        g = D_800BF808;
        if (g[0xE] != 0 && g[0xF] == 0xC) {
            a[3] = g[0xF] + 1;
            f_SpawnCircusSceneActorsFromPlacementTable(a, a[3]);
            a[5] = 3;
            a[7] = 2;
        }
        func_800752B4(2);
        func_80075D24(0x11FFC);
        break;
    case 1:
        if (f_UpdateCircusInteriorSceneTransition(a) != 0) {
            f_SpawnCircusSceneActorsFromPlacementTable(a, a[3]);
        }
        func_80113C20(1);
        func_80026A68(a);
        break;
    case 2:
        break;
    case 3:
        func_8007ADD0(a);
        break;
    }
}

#define W(p, o) M2C_FIELD(p, u32 *, o)
typedef struct {
    u8 b[6][4];
} FlickerTbl;
extern FlickerTbl D_801094E8;
void func_801143C0(u8 *a) {
    FlickerTbl t = D_801094E8;

    switch (a[4]) {
    case 0:
        a[4] = 1;
        W(a, 0x60) = 0x100;
        W(a, 0x64) = 0x200;
        W(a, 0x68) = 0x200;
        W(a, 0x6C) = 0x100;
        M2C_FIELD(a, s16 *, 0x32) = -200;
    case 1:
    case 2:
        W(a, 0x60) -= W(a, 0x60) >> 2;
        W(a, 0x64) -= W(a, 0x64) >> 2;
        W(a, 0x68) -= W(a, 0x68) >> 2;
        W(a, 0x6C) -= W(a, 0x6C) >> 2;
        if (W(a, 0x6C) < 9) {
            a[4] = 3;
        }
        if (++a[7] >= 6) {
            a[7] = 0;
        }
        W(a, 0x50) = (W(a, 0x60) * t.b[a[7]][0]) >> 4;
        W(a, 0x54) = (W(a, 0x64) * t.b[a[7]][1]) >> 4;
        W(a, 0x58) = (W(a, 0x68) * t.b[a[7]][2]) >> 4;
        W(a, 0x5C) = (W(a, 0x6C) * t.b[a[7]][3]) >> 4;
        a[1] = 1;
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_801145E0);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80114770);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8011490C);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80114ADC);

#define W_211f(p, o) (*(u32 *)((u8 *)(p) + (o)))
typedef struct { u8 v[6][4]; } Tab64;
extern Tab64 D_801094E8_ff27;
void func_80114CF8(u8 *a)
{
    Tab64 t = D_801094E8_ff27;
    u32 r, h;

    switch (a[4]) {
    case 0:
        a[4] = 1;
        a[6] = 0xA;
        a[7] = 0;
        *(s16 *)(a + 0x32) = -0xC8;
    case 1:
    case 2:
        if (a[4] == 1) {
            r = func_8009A450() & 0x3F;
            h = r >> 1;
            if (--a[6] == 0xFF) {
                a[4] = 2;
            }
            W_211f(a, 0x60) = h + 0x100;
            W_211f(a, 0x64) = r + 0x200;
            W_211f(a, 0x68) = r + 0x200;
            W_211f(a, 0x6C) = h + 0x100;
            W_211f(a, 0x60) >>= 1;
            W_211f(a, 0x64) >>= 1;
            W_211f(a, 0x68) >>= 1;
            W_211f(a, 0x6C) >>= 1;
        } else {
            W_211f(a, 0x60) -= W_211f(a, 0x60) >> 2;
            W_211f(a, 0x64) -= W_211f(a, 0x64) >> 2;
            W_211f(a, 0x68) -= W_211f(a, 0x68) >> 2;
            W_211f(a, 0x6C) -= W_211f(a, 0x6C) >> 2;
            if (W_211f(a, 0x6C) < 9) {
                a[4] = 3;
            }
            if (++a[7] >= 6) {
                a[7] = 0;
            }
        }
        W_211f(a, 0x50) = (W_211f(a, 0x60) * t.v[a[7]][0]) >> 4;
        W_211f(a, 0x54) = (W_211f(a, 0x64) * t.v[a[7]][1]) >> 4;
        W_211f(a, 0x58) = (W_211f(a, 0x68) * t.v[a[7]][2]) >> 4;
        W_211f(a, 0x5C) = (W_211f(a, 0x6C) * t.v[a[7]][3]) >> 4;
        a[1] = 1;
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

#define gte_ldfcdir(r0, r1, r2) __asm__ volatile("ctc2	%0, $21;" "ctc2	%1, $22;" "ctc2	%2, $23" : : "r"(r0), "r"(r1), "r"(r2))
extern s32 D_1F800090[];
extern u8 D_80133F20[];
extern u8 D_80133F90[];
void func_80114F9C(u8 *p)
{
    s32 *d = D_1F800090;

    gte_ldfcdir(0, 0, 0);
    *d = *(s32 *)(p + 0x54);
    func_800318A0(p + 0x2C, p + 0x50, p + 0x48);
    func_80027768(*(s32 *)(p + 0x3C), *(u16 *)(p + 0x44), *(s16 *)(p + 0x32), p[0x29]);
}

void func_80115008(u8 *a)
{
    switch (a[4]) {
    case 0:
        *(s16 *)(a + 0x32) = -0x5A;
        a[4] = 1;
        a[5] = 0x1E;
        *(s32 *)(a + 0x50) = 0;
        {
            s32 h = func_8009A450();
            *(s32 *)(a + 0x54) = (h << 16) | func_8009A450() | 1;
        }
    case 1:
        { u8 c = a[5]; a[5] = c + 0xFF; if (c == 0) {
            a[4] = 2;
        } }
        a[1] = 1;
        *(s32 *)(a + 0x50) += 2;
        break;
    case 2:
    case 3:
        func_8007A624(a);
        break;
    }
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_801150DC);

extern u8 D_800E7E81;
void func_80115174(u8 *a) {
    u8 *p;
    s32 s;
    s32 k;
    s32 rs_k50;

    switch (a[4]) {
    case 0:
        a[1] = 0;
        *(u8 **)(a + 0x10) = NULL;
        a[0x46] = 0xFF;
        a[4]++;
        break;
    case 1:
        if (D_1F800137 != 0) {
            if (*(u8 **)(a + 0x10) != NULL) {
                p = *(u8 **)(a + 0x10);
                if (p[4] < 2) {
                    p[4] = 3;
                }
                *(u8 **)(a + 0x10) = NULL;
            }
            func_8006F04C();
        } else {
            func_8006F04C();
            if (D_800E7E81 == 0) {
                return;
            }
            k = D_800BF840;
            if ((k & 0x40) && func_8006EFF4(s = k & 0xF) == 0) {
                if (*(u8 **)(a + 0x10) == NULL) {
                    *(u8 **)(a + 0x10) = func_8007E038(s, 0);
                    func_8006F02C(s);
                    a[0x46] = s;
                } else if ((p = *(u8 **)(a + 0x10))[4] >= 2) {
                    *(u8 **)(a + 0x10) = NULL;
                } else if (a[0x46] != s) {
                    p[4] = 3;
                    *(u8 **)(a + 0x10) = NULL;
                }
            } else {
                if (*(u8 **)(a + 0x10) != NULL) {
                    p = *(u8 **)(a + 0x10);
                    if (p[4] < 2) {
                        p[4] = 3;
                    }
                    *(u8 **)(a + 0x10) = NULL;
                }
            }
        }
        break;
    case 2:
        rs_k50 = 3;
        a[4] = rs_k50;
        break;
    case 3:
        func_8007A624(a);
        break;
    }
    D_800BF840 = 0;
}

void func_80115174();
u8 *func_80115334(void)
{
    u8 *a = func_8007A980(0, 3, 1);

    if (a == NULL) {
        return NULL;
    }
    *(void **)(a + 0x1C) = func_80115174;
    a[2] = 1;
    a[0x28] |= 0x80;
    return a;
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80115388);

#define F16(p, o) M2C_FIELD(p, s16 *, o)
void func_8011545C(u8 *a, u8 *b) {
    u8 *t;

    switch (a[5]) {
    case 0:
        a[5]++;
        F16(b, 0xE) = F16(b, 0xA);
        func_80072FE0(a);
        a[0x5E] = 1;
        break;
    case 1:
        if (D_800BF818_7697 == 2) {
            F16(a, 0x40) = 0;
            a[5]++;
        }
        break;
    case 2:
        if (++F16(a, 0x40) >= 0x19 && func_80073194(a) != 0) {
            a[0x5E] = 0;
            a[5]++;
        }
        break;
    case 3:
        t = D_800BF808;
        if (t[0x10] == 3) {
            a[0x5E] = 1;
            a[5]++;
        } else if (t[0x10] == 7) {
            t[0x10] = 0;
            a[5] = 6;
            func_80074590(0x17, 0, 0);
            a[0x5E] = 1;
        }
        break;
    case 4:
        if (func_8007302C(a) != 0) {
            a[5]++;
        }
        break;
    case 6:
        if (func_8007302C(a) != 0) {
            F16(a, 0x40) = 0x18;
            a[5]++;
        }
        break;
    case 7:
        if (--F16(a, 0x40) == 0) {
            a[5]++;
        }
        break;
    case 8:
        if (func_800730C8(a) != 0) {
            a[5] = 3;
            func_80074590(0x18, 0, 0);
            D_800BF818_7697 = 0;
        }
        break;
    }
}

typedef struct { u8 pad[0xC0]; u8 *parts[16]; } A5618;
#define PT(a, i) (((A5618 *)(a))->parts[i])
extern u8 D_80133018[][2];
extern s16 *D_80132FEC[];
extern s16 D_800ED098;
u8 *func_801175B8(void *a);
void func_80115618(u8 *a)
{
    s16 *d;
    s32 i;
    u8 *p;

    switch (a[4]) {
    case 0:
        a[8] = D_80133018[a[3]][0];
        if (D_800ED098 < a[8]) {
            a[4] = 3;
            break;
        }
        a[9] = a[8];
        a[4]++;
        a[0xD] = 0;
        a[0xB] = 0;
        H(a, 0x54) = 0;
        H(a, 0x58) = 0;
        d = D_80132FEC[a[3]];
        for (i = 0; i < a[8]; i++) {
            PT(a, i) = func_8007AAE8();
            H(PT(a, i), 6) = *d++;
            H(PT(a, i), 0) = *d++;
            H(PT(a, i), 2) = *d++;
            H(PT(a, i), 4) = *d++;
            H(PT(a, i), 8) = *d++;
            H(PT(a, i), 0xA) = *d++;
            H(PT(a, i), 0xC) = *d++;
            func_80051B04(PT(a, i), 0xC, *d++);
        }
        a[0xBF] = 0;
        switch (a[3]) {
        case 1:
        case 2:
        case 3:
        case 4:
            H(a, 0x56) = -0x400;
            break;
        case 5:
            H(a, 0x56) = -0x1A4;
            break;
        case 6:
            H(a, 0x56) = -0x400;
            W_d1fb(a, 0x60) = func_80074590(0x81, 0, 0);
            break;
        case 7:
            H(a, 0x56) = 0;
            break;
        case 8:
            H(a, 0x56) = -0x29F;
            break;
        case 9:
            H(a, 0x56) = 0x105;
            func_80040C00(0x56);
            a[0xBF] = 1;
            a[0x46] = 1;
            break;
        case 10:
            H(a, 0x56) = -0x400;
            a[0xBF] = 1;
            a[0x46] = 0;
            break;
        }
        break;
    case 1:
        switch (a[3]) {
        case 1:
            if (a[5] == 0) {
                __asm__ volatile("");
                a[5] = 1;
                func_800517F8(a);
                for (i = 1; i < 4; i++) {
                    p = func_801175B8(a);
                    if (p != NULL) {
                        p[0x28] |= 0x80;
                        H(p, 0x2E) = H(PT(a, i), 0x2C) + 0x8C;
                        H(p, 0x32) = H(PT(a, i), 0x30) - 0xC8;
                        H(p, 0x36) = H(PT(a, i), 0x34) + 0x40;
                    }
                    p = func_801175B8(a);
                    if (p != NULL) {
                        p[0x28] |= 0x80;
                        H(p, 0x2E) = H(PT(a, i), 0x2C) + 0x8C;
                        H(p, 0x32) = H(PT(a, i), 0x30) - 0xC8;
                        H(p, 0x36) = H(PT(a, i), 0x34) - 0x40;
                    }
                }
            }
            break;
        case 9:
            func_8011545C(a, PT(a, 1));
            H(PT(a, 2), 0xA) = H(PT(a, 1), 0xA);
            break;
        case 10:
            func_8011545C(a, PT(a, 1));
            break;
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
            break;
        }
        a[1] = 1;
        func_800517F8(a);
        break;
    case 2:
        break;
    case 3:
        if (a[3] == 6) {
            func_80074AF0(W_d1fb(a, 0x60));
        }
        func_8007A624(a);
        break;
    }
}

typedef struct { u8 pad[0xC0]; u8 *parts[1]; } PartsOwner;
typedef struct { s16 v[4]; } PartInit;
extern PartInit D_80133030[];
extern u8 D_800BF8DC;
void func_80115A2C(PartsOwner *a)
{
    s32 i;
    u8 *q;
    s32 k;

    a->pad[8] = 3;
    k = 3;
    if (D_800ED098 < k) {
        a->pad[4] = k;
        return;
    }
    a->pad[9] = k;
    a->pad[0xD] = 0;
    a->pad[0xB] = 0;
    *(s16 *)(a->pad + 0x54) = 0;
    *(s16 *)(a->pad + 0x56) = 0;
    *(s16 *)(a->pad + 0x58) = 0;
    for (i = 0; i < a->pad[8]; i++) {
        q = func_8007AAE8();
        a->parts[i] = q;
        *(s16 *)(q + 6) = D_80133030[i].v[0];
        *(s16 *)(a->parts[i] + 0) = D_80133030[i].v[1];
        *(s16 *)(a->parts[i] + 2) = D_80133030[i].v[2];
        *(s16 *)(a->parts[i] + 4) = D_80133030[i].v[3];
        *(s16 *)(a->parts[i] + 8) = 0;
        *(s16 *)(a->parts[i] + 0xA) = 0;
        *(s16 *)(a->parts[i] + 0xC) = 0;
        func_80051B04(a->parts[i], 0xC, i + 0x20);
    }
    a->pad[0x2B] = 0;
    if (D_800BF8DC == 0xFF) {
        a->pad[4] = 3;
        return;
    }
    *(s16 *)(a->pad + 0x4E) = *(s16 *)(a->pad + 0x2E);
    *(s16 *)(a->pad + 0x50) = *(s16 *)(a->pad + 0x32);
    *(s16 *)(a->pad + 0x52) = *(s16 *)(a->pad + 0x36);
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", f_UpdateClownStatueDestructionSequence);

void func_80116538(PartsOwner *a)
{
    s32 i;
    u8 *q;

    s32 k;
    a->pad[8] = 3;
    k = 3;
    if (D_800ED098 < k) {
        a->pad[4] = k;
        return;
    }
    a->pad[9] = 3;
    a->pad[0xD] = 4;
    a->pad[0xBF] = 0;
    for (i = 0; i < a->pad[8]; i++) {
        q = func_8007AAE8();
        a->parts[i] = q;
        *(s16 *)(q + 6) = -1;
        *(s16 *)(a->parts[i] + 0) = 0;
        *(s16 *)(a->parts[i] + 2) = 0;
        *(s16 *)(a->parts[i] + 4) = 0;
        *(s16 *)(a->parts[i] + 8) = 0;
        *(s16 *)(a->parts[i] + 0xA) = 0;
        *(s16 *)(a->parts[i] + 0xC) = 0;
        func_80051B04(a->parts[i], 0xC, i + 0x33);
        a->parts[i][0x3F] = 0;
    }
}

extern PartInit D_80133048[];
void func_80116634(PartsOwner *a)
{
    s32 i;
    u8 *q;
    PartInit *t;

    a->pad[8] = 2;
    if (D_800ED098 < a->pad[8]) {
        a->pad[4] = 3;
        return;
    }
    a->pad[9] = 2;
    a->pad[0xD] = 0;
    a->pad[0xB] = 0;
    *(s16 *)(a->pad + 0x54) = 0;
    *(s16 *)(a->pad + 0x56) = 0;
    *(s16 *)(a->pad + 0x58) = 0;
    for (i = 0; i < a->pad[8]; i++) {
        q = func_8007AAE8();
        a->parts[i] = q;
        *(s16 *)(q + 6) = D_80133048[i].v[0];
        *(s16 *)(a->parts[i] + 0) = D_80133048[i].v[1];
        *(s16 *)(a->parts[i] + 2) = D_80133048[i].v[2];
        *(s16 *)(a->parts[i] + 4) = D_80133048[i].v[3];
        *(s16 *)(a->parts[i] + 8) = 0;
        *(s16 *)(a->parts[i] + 0xA) = 0;
        *(s16 *)(a->parts[i] + 0xC) = 0;
        func_80051B04(a->parts[i], 0xC, i + 0x25);
    }
    *(s16 *)(a->parts[1] + 0xC) = 0x1000;
    a->pad[0x2B] = 0;
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80116764);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80116A0C);

extern u8 D_800BFA3C;
extern s32 D_800ECF80_d353;
extern void *D_800ECF80;
extern u8 D_8013FF68[];
/* func_80117048, inlined */
static inline void func_80117048_inl(void *arg0) {
    if (D_800BFA2C != 0) {
        M2C_FIELD(arg0, s8 *, 6) = 0xA;
    } else {
        M2C_FIELD(arg0, s8 *, 6) = 0;
    }
    func_80051B70(arg0, 0xC, 0x14);
    M2C_FIELD(arg0, s16 *, 0x56) = -0x400;
}
/* func_801171EC, inlined */
static inline void func_801171EC_inl(u8 *p)
{
    *(s32 *)(p + 0x3C) = D_800ECF80_d353;
    func_80077B38(p, D_8013FF68, 0xC);
    p[0xB] = 0x10;
    *(s16 *)(p + 0x2E) = 0x67E;
    *(s16 *)(p + 0x32) = -0xAF0;
    p[0xD] = 0;
    *(s16 *)(p + 0x5C) = 0;
    *(s16 *)(p + 0x5A) = 0;
    p[0x47] = 0;
    p[8] = 0;
    *(s16 *)(p + 0x36) = 0x1AC2;
}
/* func_801173EC, inlined */
static inline void func_801173EC_inl(u8 *p)
{
    *(s32 *)(p + 0x3C) = D_800ECF80_d353;
    func_80077B38(p, D_8013FF68, 0xD);
    p[0xB] = 0x10;
    *(s16 *)(p + 0x5C) = 0;
    *(s16 *)(p + 0x5A) = 0;
    p[0x47] = 0;
    p[8] = 0xF0;
}
/* func_801174A4, inlined */
static inline void func_801174A4_inl(u8 *a)
{
    *(void **)(a + 0x3C) = D_800ECF80;
    func_80077B38(a, D_8013FF68, 0x7);
    a[0xD] = 0;
    *(s16 *)(a + 0x5C) = 0;
    a[0xB] = 0x10;
    *(s16 *)(a + 0x5A) = 0;
    a[0x47] = 0;
    a[8] = 0;
}
/* func_801175FC, inlined */
static inline void func_801175FC_inl(u8 *p)
{
    *(s32 *)(p + 0x3C) = D_800ECF80_d353;
    func_80077B38(p, D_8013FF68, 0x10);
    p[0xB] = 0x10;
    p[0xD] = 1;
    *(s16 *)(p + 0x5C) = 0;
    *(s16 *)(p + 0x5A) = 0;
    p[0x47] = 0;
    p[8] = 0xF0;
}
/* func_80117294, inlined */
static inline void func_80117294_inl(u8 *p)
{
    switch (p[5]) {
    case 0:
        if (D_800BFA3C) {
            p[5] = 1;
        }
        break;
    case 1:
        p[1] = 1;
        func_800517F8(p);
        break;
    }
}
/* func_801174FC, inlined */
static inline void func_801174FC_inl(void *arg0) {
    void *temp_s0;

    temp_s0 = M2C_FIELD(arg0, void **, 0x10);
    M2C_FIELD(arg0, s16 *, 0x2E) = (s16) (M2C_FIELD(M2C_FIELD(temp_s0, void **, 0xC0), u16 *, 0x2C) + ((s32) (func_80083F50(M2C_FIELD(temp_s0, s16 *, 0x56)) * 0x32) >> 0xC));
    M2C_FIELD(arg0, u16 *, 0x32) = (u16) M2C_FIELD(M2C_FIELD(temp_s0, void **, 0xC0), u16 *, 0x30);
    M2C_FIELD(arg0, s16 *, 0x36) = (s16) (M2C_FIELD(M2C_FIELD(temp_s0, void **, 0xC0), u16 *, 0x34) - ((s32) (func_80083E80(M2C_FIELD(temp_s0, s16 *, 0x56)) * 0x32) >> 0xC));
    M2C_FIELD(arg0, u16 *, 0x56) = (u16) M2C_FIELD(temp_s0, s16 *, 0x56);
    func_8007778C(arg0);
}
void func_80116B88(u8 *a)
{
    switch (a[4]) {
    case 0:
        a[4] = 1;
        switch (a[3]) {
        case 1:
            func_80117048_inl(a);
            break;
        case 2:
            func_80115A2C(a);
            break;
        case 3:
            func_801171EC_inl(a);
            break;
        case 4:
            func_80116538(a);
            break;
        case 5:
            func_80051B70(a, 0xC, 0x37);
            func_800517F8(a);
            break;
        case 6:
            func_80116634(a);
            break;
        case 7:
            func_801173EC_inl(a);
            break;
        case 8:
            func_801174A4_inl(a);
            break;
        case 9:
            func_801175FC_inl(a);
            break;
        }
        break;
    case 1:
        switch (a[3]) {
        case 1:
            if (D_800BF808[0xE] == 0 || D_800BF808[0xF] != 6) {
                break;
            }
            func_8007703C(a);
            switch (a[6]) {
            case 0:
                if (D_800BFA2C == 1) {
                    func_80074590(0x85, 0, 0);
                    a[6]++;
                }
                break;
            case 1:
                *(s16 *)(a + 0x56) -= 0x40;
                if (*(s16 *)(a + 0x56) < -0xA40) {
                    D_800BFA2C = 2;
                    *(s16 *)(a + 0x56) = -0xA00;
                    a[6]++;
                }
                break;
            }
            if (a[1] != 0) {
                func_800517F8(a);
            }
            break;
        case 2:
            f_UpdateClownStatueDestructionSequence(a);
            break;
        case 3:
            if (D_800BF816 == 0) {
                a[4] = 3;
                break;
            }
            func_8007778C(a);
            break;
        case 4:
            func_80117294_inl(a);
            break;
        case 5:
            func_8007778C(a);
            break;
        case 6:
            func_80116764(a);
            break;
        case 7:
            func_80116A0C(a);
            break;
        case 8:
            func_801174FC_inl(a);
            break;
        case 9:
            if (D_800BF816 == 0) {
                a[4] = 3;
                break;
            }
            a[1] = 1;
            func_80077B5C(a);
            break;
        }
        break;
    case 2:
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

void func_80117048(void *arg0) {
    if (D_800BFA2C != 0) {
        M2C_FIELD(arg0, s8 *, 6) = 0xA;
    } else {
        M2C_FIELD(arg0, s8 *, 6) = 0;
    }
    func_80051B70(arg0, 0xC, 0x14);
    M2C_FIELD(arg0, s16 *, 0x56) = -0x400;
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8011709C);

void func_80116B88();
u8 *func_8011718C(void *a0)
{
    u8 *r = func_80072DDC(a0, 0, 3, 0x10);

    if (r == 0) {
        return 0;
    }
    r[3] = 3;
    *(void **)(r + 0x1C) = func_80116B88;
    *(void **)(r + 0x10) = a0;
    r[0x28] |= 0x80;
    return r;
}

void func_801171EC(u8 *p)
{
    *(s32 *)(p + 0x3C) = D_800ECF80_d353;
    func_80077B38(p, D_8013FF68, 0xC);
    p[0xB] = 0x10;
    *(s16 *)(p + 0x2E) = 0x67E;
    *(s16 *)(p + 0x32) = -0xAF0;
    p[0xD] = 0;
    *(s16 *)(p + 0x5C) = 0;
    *(s16 *)(p + 0x5A) = 0;
    p[0x47] = 0;
    p[8] = 0;
    *(s16 *)(p + 0x36) = 0x1AC2;
}

void func_8011725C(void *arg0) {
    if (D_800BF816 == 0) {
        M2C_FIELD(arg0, s8 *, 4) = 3;
        return;
    }
    func_8007778C();
}

void func_80117294(u8 *p)
{
    switch (p[5]) {
    case 0:
        if (D_800BFA3C) {
            p[5] = 1;
        }
        break;
    case 1:
        p[1] = 1;
        func_800517F8(p);
        break;
    }
}

void func_801172F0(void *a)
{
    func_80051B70(a, 0xC, 0x37);
    func_800517F8(a);
}

void func_80117324(void) {
    func_8007778C();
}

extern u8 D_80017FE8[];
extern s32 D_800ECF68;
extern u8 D_8014005C_9175[];
extern s32 D_800ECF90;
u8 *func_80117344(void *a0, u8 a1)
{
    u8 *r = func_80072DDC(a0, 2, 3, 0x10);

    if (r == 0) {
        return 0;
    }
    r[3] = 6;
    *(void **)(r + 0x1C) = func_80116B88;
    *(void **)(r + 0x10) = a0;
    r[0x5E] = a1;
    return r;
}

void func_80116B88();
u8 *func_801173A8(void *owner)
{
    u8 *e = func_80072DDC(owner, 0, 3, 0x10);

    if (e != 0) {
        *(void **)(e + 0x1C) = func_80116B88;
        e[3] = 7;
    }
    return e;
}

extern u16 D_800E7FFE;
extern u16 D_800BFE56;
void func_801173EC(u8 *p)
{
    *(s32 *)(p + 0x3C) = D_800ECF80_d353;
    func_80077B38(p, D_8013FF68, 0xD);
    p[0xB] = 0x10;
    *(s16 *)(p + 0x5C) = 0;
    *(s16 *)(p + 0x5A) = 0;
    p[0x47] = 0;
    p[8] = 0xF0;
}

u8 *func_80117444(void *a0)
{
    u8 *r = func_80072DDC(a0, 0, 3, 0x10);

    if (r == 0) {
        return 0;
    }
    r[3] = 8;
    *(void **)(r + 0x1C) = func_80116B88;
    *(void **)(r + 0x10) = a0;
    r[0x28] |= 0x80;
    return r;
}

void func_801174A4(u8 *a)
{
    *(void **)(a + 0x3C) = D_800ECF80;
    func_80077B38(a, D_8013FF68, 0x7);
    a[0xD] = 0;
    *(s16 *)(a + 0x5C) = 0;
    a[0xB] = 0x10;
    *(s16 *)(a + 0x5A) = 0;
    a[0x47] = 0;
    a[8] = 0;
}

void func_801174FC(void *arg0) {
    void *temp_s0;

    temp_s0 = M2C_FIELD(arg0, void **, 0x10);
    M2C_FIELD(arg0, s16 *, 0x2E) = (s16) (M2C_FIELD(M2C_FIELD(temp_s0, void **, 0xC0), u16 *, 0x2C) + ((s32) (func_80083F50(M2C_FIELD(temp_s0, s16 *, 0x56)) * 0x32) >> 0xC));
    M2C_FIELD(arg0, u16 *, 0x32) = (u16) M2C_FIELD(M2C_FIELD(temp_s0, void **, 0xC0), u16 *, 0x30);
    M2C_FIELD(arg0, s16 *, 0x36) = (s16) (M2C_FIELD(M2C_FIELD(temp_s0, void **, 0xC0), u16 *, 0x34) - ((s32) (func_80083E80(M2C_FIELD(temp_s0, s16 *, 0x56)) * 0x32) >> 0xC));
    M2C_FIELD(arg0, u16 *, 0x56) = (u16) M2C_FIELD(temp_s0, s16 *, 0x56);
    func_8007778C(arg0);
}

void func_80116B88();
u8 *func_801175B8(void *a)
{
    u8 *r = func_80072DDC(a, 0, 3, 0x10);

    if (r != NULL) {
        *(void **)(r + 0x1C) = func_80116B88;
        r[3] = 0x9;
    }
    return r;
}

void func_801175FC(u8 *p)
{
    *(s32 *)(p + 0x3C) = D_800ECF80_d353;
    func_80077B38(p, D_8013FF68, 0x10);
    p[0xB] = 0x10;
    p[0xD] = 1;
    *(s16 *)(p + 0x5C) = 0;
    *(s16 *)(p + 0x5A) = 0;
    p[0x47] = 0;
    p[8] = 0xF0;
}

void func_8011765C(void *arg0) {
    M2C_FIELD(arg0, s8 *, 1) = 1;
    func_80077B5C();
}

extern u8 D_800E7EEE;
void func_80117680(u8 *a)
{
    u8 *t;
    u8 *p;

    switch (a[4]) {
    case 0:
        if (D_800E7EEE != 0) {
            func_8004BEC4();
        }
        if (func_80051B70(a, 0xC, 0xB) != 0) {
            break;
        }
        *(s16 *)(a + 0x88) = -0x5A;
        *(s16 *)(a + 0x8A) = 0;
        *(s16 *)(a + 0x8C) = 0;
        *(s16 *)(a + 0x58) = 0;
        *(s16 *)(a + 0x54) = 0;
        *(s16 *)(a + 0x56) = 0x400;
        func_800517F8(a);
        D_800BF860_c64f = a;
        a[4]++;
        break;
    case 1:
        switch (a[5]) {
        case 0:
            t = D_800E7E80;
            if (*(s16 *)(t + 0x17E) & 0x8200) {
                break;
            }
            a[1] = t[1];
            func_80051614(a, a + 0x88, 0, 0);
            if (D_800BFA2C == 0xC) {
                *(s16 *)(a + 0x2E) = 0x21FC;
                *(s16 *)(a + 0x32) = -0x9C4;
                *(s16 *)(a + 0x36) = 0x34D2;
                a[4] = 0;
                a[5] = 2;
                func_800517F8(a);
            }
            break;
        case 3:
            if (D_800BFA2C == 0x10) {
                a[4] = 3;
                break;
            }
        case 1:
            p = *(u8 **)(a + 0x10);
            a[1] = p[1];
            switch (a[6]) {
            case 0:
                *(s16 *)(a + 0x8C) = 0;
                *(s16 *)(a + 0x8A) = 0;
                *(s16 *)(a + 0x88) = 0;
                *(s16 *)(a + 0x58) = 0;
                a[6]++;
                break;
            case 1:
                *(s16 *)(a + 0x2E) = *(s16 *)(*(u8 **)(p + 0xDC) + 0x2C);
                *(s16 *)(a + 0x32) = *(s16 *)(*(u8 **)(p + 0xDC) + 0x30) + 0x32;
                *(s16 *)(a + 0x36) = *(s16 *)(*(u8 **)(p + 0xDC) + 0x34);
                break;
            }
            func_800517F8(a);
            break;
        case 2:
            if (D_800BFA2C == 0xD) {
                a[5] = 3;
            }
            a[1] = 1;
            break;
        }
        break;
    case 2:
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

void func_80117680();
u8 *func_801178E4(s32 unused)
{
    u8 *r = func_8007A980(1, 3, 1);

    if (r == 0) {
        return 0;
    }
    r[2] = 0x12;
    r[3] = 0;
    *(void **)(r + 0x1C) = func_80117680;
    r[0x28] |= 0x80;
    return r;
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8011793C);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80117AB8);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80117D4C);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80117FE0);

extern u8 *D_800BF864_ee3c;
void func_80118184(u8 *a)
{
    switch (a[4]) {
    case 0:
        if (a[3] == 0) {
            s16 *p = (s16 *)(a + 0x60);
            p[0] = 0;
            p[1] = 0x299F;
            p[2] = -0xC80;
            D_800BF864_ee3c = a;
        }
        a[4]++;
        break;
    case 1:
        switch (a[3]) {
        case 0:
            func_8011793C(a);
            func_80117D4C(a);
            break;
        case 1:
            func_80117FE0(a);
            break;
        }
        break;
    case 2:
    case 3:
        func_8007A624(a);
        break;
    }
}

extern void *D_800BF864;
void func_80118270(void *arg0) {
    void *temp_v1;

    temp_v1 = arg0 + 0x60;
    M2C_FIELD(arg0, s16 *, 0x60) = 0;
    M2C_FIELD(temp_v1, s16 *, 2) = 0x299F;
    M2C_FIELD(temp_v1, s16 *, 4) = -0xC80;
    D_800BF864 = arg0;
}

u8 *func_80118294(void *a0)
{
    u8 *r = func_80072DDC(a0, 0, 3, 0x18);

    if (r == 0) {
        return 0;
    }
    r[3] = 1;
    *(void **)(r + 0x1C) = func_80118184;
    *(void **)(r + 0x10) = a0;
    return r;
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", f_UpdateCircusSeesawLaunchedActorSequence);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80118BB4);

extern u8 D_800ECF58[];
extern u8 D_80131C10[];
extern u8 D_8014106C[];
extern u8 D_800A3D18_ed09[];
extern u8 D_800BF9D6;
u8 *func_8012B3FC(void *a0);
void func_80118EDC(u8 *a)
{
    u8 *g;

    switch (a[4]) {
    case 0:
        g = D_800ECF58;
        if (func_800519E0(a, 9, *(s32 *)(g + 0x7C), D_80131C10) != 0) {
            break;
        }
        *(s32 *)(a + 0x3C) = *(s32 *)(g + 0x80);
        func_80040CDC(a, D_8014106C, D_800A3D18_ed09);
        func_80041718(a, 0, 0);
        if (D_800BF9D6 == 0) {
            *(s16 *)(a + 0x2E) = 0x170C;
            *(s16 *)(a + 0x32) = -0xDAC;
            *(s16 *)(a + 0x36) = 0x2D26;
            a[0x5E] = 0;
        } else {
            *(s16 *)(a + 0x2E) = 0x16EE;
            *(s16 *)(a + 0x32) = -0xF8C;
            *(s16 *)(a + 0x36) = 0x2F3A;
            a[0x5E] = 1;
        }
        *(void **)(a + 0x14) = func_8012B3FC(a);
        a[4]++;
        break;
    case 1:
        switch (a[0x5E]) {
        case 0:
            f_UpdateCircusSeesawLaunchedActorSequence(a);
            break;
        case 1:
            func_80118BB4(a);
            break;
        }
        if (a[1] != 0) {
            func_8004190C(a);
            func_800518FC(a);
        }
        break;
    case 2:
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80119070);

void func_8011926C(u8 *a)
{
    if (--*(s16 *)(a + 0x40) == 0) {
        *(s16 *)(a + 0x40) = 15;
        if (*(s16 *)(a + 0x42) == 0) {
            func_80077B38(a, D_8013FF68, 8);
        } else {
            func_80077B38(a, D_8013FF68, 9);
        }
        *(s16 *)(a + 0x42) ^= 1;
    }
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_801192F0);

void func_80119454();
u8 *func_801193DC(void *a)
{
    u8 *r = func_80072DDC(a, 1, 3, 0x28);

    if (r != NULL) {
        *(void **)(r + 0x1C) = func_80119454;
    }
    return r;
}

void func_80119070();
u8 *func_80119418(void *a0)
{
    u8 *r = func_80072DDC(a0, 0, 3, 0x27);

    if (r) {
        *(void **)(r + 0x1C) = func_80119070;
    }
    return r;
}

void func_80119454(u8 *a)
{
    u8 *p = *(u8 **)(a + 0x10);

    switch (a[4]) {
    case 0:
        if (func_80051B70(a, 0xC, 0x29) != 0) {
            break;
        }
        *(s16 *)(a + 0x54) = 0;
        *(s16 *)(a + 0x56) = 0;
        *(s16 *)(a + 0x58) = 0;
        a[4]++;
        *(s16 *)(a + 0x2E) = *(s16 *)(p + 0x2E);
        *(s16 *)(a + 0x32) = *(s16 *)(p + 0x32) + 0xCD;
        *(s16 *)(a + 0x36) = *(s16 *)(p + 0x36);
    case 1:
        if (p[4] == 3) {
            a[4] = 3;
            break;
        }
        *(s16 *)(a + 0x2E) = *(s16 *)(p + 0x2E);
        *(s16 *)(a + 0x32) = *(s16 *)(p + 0x32) + 0xCD;
        *(s16 *)(a + 0x36) = *(s16 *)(p + 0x36);
        a[1] = 1;
        func_800517F8(a);
        break;
    case 2:
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

typedef struct { s16 v[5]; } PartInit5;
extern PartInit5 D_80133070[];
extern u8 D_80133098[];
void f_UpdateCircusGearMechanismActor(u8 *a)
{
    s32 i;
    s32 n;
    u8 *q;
    u8 *st;
    u8 *g;
    u8 *st2;

    switch (a[4]) {
    case 0:
        n = 4;
        a[8] = n;
        if (D_800ED098 < n) {
            a[4] = 3;
            break;
        }
        a[9] = 4;
        a[4]++;
        a[0xD] = 0;
        a[0xB] = 0;
        for (i = 0; i < a[8]; i++) {
            q = func_8007AAE8();
            ((u8 **)(a + 0xC0))[i] = q;
            *(s16 *)(q + 6) = D_80133070[i].v[0];
            *(s16 *)(((u8 **)(a + 0xC0))[i] + 0) = D_80133070[i].v[1];
            *(s16 *)(((u8 **)(a + 0xC0))[i] + 2) = D_80133070[i].v[2];
            *(s16 *)(((u8 **)(a + 0xC0))[i] + 4) = D_80133070[i].v[3];
            *(s16 *)(((u8 **)(a + 0xC0))[i] + 8) = 0;
            *(s16 *)(((u8 **)(a + 0xC0))[i] + 0xA) = 0;
            *(s16 *)(((u8 **)(a + 0xC0))[i] + 0xC) = 0;
            func_80051B04(((u8 **)(a + 0xC0))[i], 0xC, D_80133070[i].v[4]);
        }
        *(s16 *)(a + 0x58) = 0;
        *(s16 *)(a + 0x54) = 0;
        *(s16 *)(a + 0x56) = 0x800;
        break;
    case 1:
        if (func_8007778C(a) != 0) {
            func_800517F8(a);
        }
        switch (a[5]) {
        case 0:
            st = (u8 *)&D_800BF870;
            if (st[0x166] >= 0xD) {
                if (st[0xC7] == 0) {
                    func_80051B04(*(u8 **)(a + 0xC0), 0xC, 0x1A);
                    a[5] = 10;
                } else if (!(st[0x1DB] & 4)) {
                    a[0] = 1;
                    *(s16 *)(a + 0x80) = 0x96;
                    *(s16 *)(a + 0x82) = 0x12C;
                    *(s16 *)(a + 0x84) = 0xC8;
                    *(s16 *)(a + 0x86) = 0x190;
                    func_80051B04(*(u8 **)(a + 0xC0), 0xC, 0x1A);
                    a[5] = 4;
                } else {
                    a[5] = 10;
                }
            } else {
                a[5]++;
            }
            break;
        case 1:
            if (D_800BF9D6 == 0xB) {
                D_800BF860_c64f = 0;
                func_80074590(0x1A, 0x1B, 0);
                func_80051B04(*(u8 **)(a + 0xC0), 0xC, 0x1A);
                a[5]++;
            }
            break;
        case 2:
            g = D_800BF808;
            if (*(u8 **)(g + 0x58) != 0) {
                if (!(D_1F80017C & 0xF)) {
                    func_80074590(0x85, 0, 0);
                }
                *(s16 *)(*(u8 **)(a + 0xC4) + 8) = (0xA00 - (*(u16 *)(*(u8 **)(*(u8 **)(g + 0x58) + 0x38) + 2) << 9)) & 0xFFF;
                *(s16 *)(*(u8 **)(a + 0xC8) + 8) += 0x80;
            }
            if (D_800BF9D6 == 0xD) {
                *(s16 *)(*(u8 **)(a + 0xC4) + 8) = *(s16 *)(*(u8 **)(a + 0xC8) + 8) = 0;
                D_800BF860_c64f = 0;
                a[5] = 10;
            }
            break;
        case 4:
            switch (a[6]) {
            case 0:
                if (a[0x2B] == 1) {
                    func_80040CDC(a, 0, D_80133098);
                    a[0x70] = 2;
                    a[0] = 2;
                    a[6]++;
                }
                a[0x2B] = 0;
                break;
            case 1:
                st2 = (u8 *)&D_800BF870;
                if (st2[0x26A] != 0) {
                    func_80051B04(*(u8 **)(a + 0xC0), 0xC, 0x1E);
                    st2[0x1DB] |= 4;
                    a[6]++;
                }
            case 2:
                func_80041098(a);
                if (a[0x70] == 0xFF) {
                    func_80042310();
                    a[5] = 10;
                    a[6] = 0;
                }
                break;
            }
            break;
        case 10:
            break;
        }
        break;
    case 2:
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", f_UpdateCircusInteriorEntranceTransition);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80119C84);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80119DA0);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80119F74);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8011A174);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8011A398);

void func_8011A83C(void) {
    f_UpdateCircusInteriorEntranceTransition();
}

void func_8011A85C(void) {
    f_UpdateCircusInteriorEntranceTransition();
}

void func_8011A87C(void) {
    f_UpdateCircusInteriorEntranceTransition();
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8011A89C);

void func_8011A980(void) {
    f_UpdateCircusInteriorEntranceTransition();
}

void func_8011A9A0(void) {
    if ((D_800BF870.pad1[0x67] != 0) || (M2C_FIELD(&D_800BF870, u16 *, 0x2E) & 0x200)) {
        f_UpdateCircusInteriorEntranceTransition();
    }
}

void func_8011A9EC(void) {
    f_UpdateCircusInteriorEntranceTransition();
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8011AA0C);

void func_8011AAFC(void) {
    f_UpdateCircusInteriorEntranceTransition();
}

void func_8011AB1C(void) {
    f_UpdateCircusInteriorEntranceTransition();
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8011AB3C);

typedef struct { s16 m[3][3]; s16 pad; s32 t[3]; } AreaMatrix;
typedef struct { u8 pad[0x28]; AreaMatrix m; } AreaScratchD0;
extern AreaScratchD0 D_1F8000D0_2539;
extern AreaMatrix D_1F800000;
void func_8011AD44(u8 *a) {
    D_1F8000C0_f4ad.x = M2C_FIELD(M2C_FIELD(a, u8 **, 0xC0), s16 *, 0x2C);
    D_1F8000C0_f4ad.y = M2C_FIELD(M2C_FIELD(a, u8 **, 0xC0), s16 *, 0x30);
    D_1F8000C0_f4ad.z = M2C_FIELD(M2C_FIELD(a, u8 **, 0xC0), s16 *, 0x34);
    func_80084110(&D_1F8000D0_2539.m, M2C_FIELD(a, u8 **, 0xC0) + 0x18, &D_1F800000);
    func_80084220(&D_1F8000C0_f4ad, D_1F800000.t);
    D_1F800000.t[0] += D_1F8000D0_2539.m.t[0];
    D_1F800000.t[1] += D_1F8000D0_2539.m.t[1];
    D_1F800000.t[2] += D_1F8000D0_2539.m.t[2];
    func_80084660(&D_1F800000);
    func_80084690(&D_1F800000);
    func_8011AB3C(a);
}

#define H(p, o) (*(s16 *)((u8 *)(p) + (o)))
extern s16 D_801330FC;
typedef struct {
    s16 f0, f2, f4, f6, f8, fA, fC, pad0E[2], f12, pad14, f16;
    u8 pad18[0x22];
    s16 f3A;
    u8 pad3C[4];
    s32 f40;
} Sub;
void func_8011AE24(u8 *a)
{
    s16 t;
    a[8] = 1;
    if (D_800ED098 <= 0) {
        a[4] = 3;
        return;
    }
    t = 1;
    a[9] = t;
    a[0] = t;
    a[0xB] = 2;
    H(a, 0x60) = 0xF;
    H(a, 0x62) = 0x343F;
    H(a, 0x64) = -0x1C00;
    H(a, 0x66) = -0x1BF1;
    H(a, 0x68) = -0xC00;
    H(a, 0x6A) = -0xBF1;
    a[0x29] = 0;
    a[0x2B] = 0;
    a[0x5E] = 0;
    a[0xBF] = 0;
    H(a, 0x6C) = 0x50;
    H(a, 0x6E) = 0;
    H(a, 0x7C) = 0;
    H(a, 0x7E) = 0;
    H(a, 0x7A) = 0;
    a[4]++;
    *(Sub **)(a + 0xC0) = func_8007AAE8();
    (*(Sub **)(a + 0xC0))->f6 = -1;
    (*(Sub **)(a + 0xC0))->f0 = 0;
    (*(Sub **)(a + 0xC0))->f4 = 0;
    (*(Sub **)(a + 0xC0))->f8 = 0;
    (*(Sub **)(a + 0xC0))->fA = 0;
    (*(Sub **)(a + 0xC0))->fC = 0;
    (*(Sub **)(a + 0xC0))->f40 = 0;
    H(a, 0x88) = D_801330FC;
    H(a, 0x8A) = (&D_801330FC)[1];
    H(a, 0x8C) = (&D_801330FC)[2];
    H(a, 0x54) = (&D_801330FC)[3];
    H(a, 0x56) = (&D_801330FC)[4];
    H(a, 0x58) = (&D_801330FC)[5];
    (*(Sub **)(a + 0xC0))->f3A = (&D_801330FC)[6];
    H(a, 0x80) = (&D_801330FC)[7];
    H(a, 0x82) = (&D_801330FC)[8];
    H(a, 0x84) = (&D_801330FC)[9];
    H(a, 0x86) = (&D_801330FC)[10];
    (*(Sub **)(a + 0xC0))->f2 = 0x140;
    H(a, 0x4A) = 0;
    H(a, 0x50) = 0x200;
    (*(Sub **)(a + 0xC0))->f16 = (*(Sub **)(a + 0xC0))->f3A;
    (*(Sub **)(a + 0xC0))->f12 = 0;
    t = (*(Sub **)(a + 0xC0))->f2;
    a[0x47] = 3;
    H(a, 0x78) = t;
    H(a, 0x32) -= (*(Sub **)(a + 0xC0))->f3A;
    H(a, 0x56) = -D_1F8000F2;
    func_800517F8(a);
}

void func_8011B030(u8 *a)
{
    s32 s = a[4];
    switch (s) {
    case 0:
        func_8011AE24(a);
        break;
    case 1:
        *(s16 *)(a + 0x56) = -D_1F8000F2;
        func_800517F8(a);
        a[1] = s;
        func_80077EBC(a);
        a[0x2B] = 0;
        break;
    case 2:
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

void func_8011B0E0(void *arg0) {
    M2C_FIELD(arg0, s16 *, 0x56) = (s16) -(s16) *(u16 *)0x1F8000F2;
    func_800517F8();
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8011B10C);

void func_8011B3B8(u8 *a) {
    switch (a[4]) {
    case 0:
        a[4] = 1;
        a[0] = 1;
        if (a[3] == 0) {
            M2C_FIELD(a, s16 *, 0x80) = 0x9C;
            M2C_FIELD(a, s16 *, 0x82) = 0x138;
            M2C_FIELD(a, s16 *, 0x84) = 0xC8;
            M2C_FIELD(a, s16 *, 0x86) = 0x12C;
        }
        a[0x29] = 0;
        break;
    case 1:
        if (a[3] == 0) {
            func_8011B10C(a);
        }
        func_8007778C(a);
        a[0x29] = 0;
        break;
    case 2:
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

extern u8 D_80133114[];
void func_8011B480(u8 *a)
{
    u8 *g;

    switch (a[4]) {
    case 0:
        *(s32 *)(a + 0x3C) = D_800ECF80_d353;
        func_80077B38(a, D_8013FF68, 4);
        a[0xB] = 0x10;
        *(s16 *)(a + 0x80) = 0xAA;
        *(s16 *)(a + 0x82) = 0x154;
        *(s16 *)(a + 0x84) = 0x64;
        a[0xD] = 0;
        *(s16 *)(a + 0x5C) = 0;
        *(s16 *)(a + 0x5A) = 0;
        a[0x47] = 0;
        a[8] = 0;
        a[0] = 1;
        *(s16 *)(a + 0x86) = 0xC8;
        a[0x2B] = 0;
        func_8004B354(a, 0);
        a[4]++;
        break;
    case 1:
        func_8007778C(a);
        switch (a[5]) {
        case 0:
            if (a[0x2B] == 1) {
                func_80040CDC(a, 0, D_80133114);
                a[0x70] = 2;
                a[0] = 2;
                a[0x2B] = 0;
                a[5]++;
            }
            break;
        case 1:
            if (a[0x70] == 0xFF) {
                g = (u8 *)&D_800BF870;
                g[0x1D5] |= 2;
                a[4] = 2;
            }
            func_80041098(a);
            break;
        }
        func_8004B374(a, 0);
        break;
    case 2:
        func_80042310();
        *(s16 *)(a + 0x68) = 0x33;
        func_8004A3D4(a);
        a[4] = 3;
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

extern u8 D_800BF9D5;
extern PartInit D_8013313C[];
u8 *func_8007AAE8();
void func_8011B650(PartsOwner *a)
{
    s32 i;
    u8 *q;
    s32 k;

    a->pad[8] = 3;
    k = 3;
    if (D_800ED098 < k) {
        a->pad[4] = k;
        return;
    }
    a->pad[9] = k;
    a->pad[0xD] = 0;
    a->pad[0xB] = 0;
    *(s16 *)(a->pad + 0x54) = 0;
    *(s16 *)(a->pad + 0x56) = 0;
    *(s16 *)(a->pad + 0x58) = 0;
    if (D_800BF9D5 < 3) {
        *(void **)(a->pad + 0x14) = func_8011718C(a);
        a->pad[0] = 1;
    } else {
        a->pad[5] = k;
        a->pad[0] = 2;
    }
    *(s16 *)(a->pad + 0x80) = 0x12C;
    *(s16 *)(a->pad + 0x82) = 0x258;
    *(s16 *)(a->pad + 0x84) = 0x1C2;
    *(s16 *)(a->pad + 0x86) = 0x258;
    for (i = 0; i < a->pad[8]; i++) {
        q = func_8007AAE8();
        a->parts[i] = q;
        *(s16 *)(q + 6) = D_8013313C[i].v[0];
        *(s16 *)(a->parts[i] + 0) = D_8013313C[i].v[1];
        *(s16 *)(a->parts[i] + 2) = D_8013313C[i].v[2];
        *(s16 *)(a->parts[i] + 4) = D_8013313C[i].v[3];
        *(s16 *)(a->parts[i] + 8) = 0;
        *(s16 *)(a->parts[i] + 0xA) = 0;
        *(s16 *)(a->parts[i] + 0xC) = 0;
        func_80051B04(a->parts[i], 0xC, i + 0x17);
    }
    a->pad[0x2B] = 0;
    a->pad[4]++;
}

extern u8 D_80133154[];
extern u8 D_80133198[];
extern u8 D_800A3E58[];
extern u8 D_800BFAE7;
extern u8 D_800BF822;
extern void func_80041098(u8 *);
void f_UpdateCircusClothesLockerActor(u8 *a)
{
    s32 t;

    if (func_8007778C(a) != 0) {
        func_800517F8(a);
    }
    switch (a[5]) {
    case 0:
        if (a[0x2B] != 0) {
            a[0] = 2;
            a[0x2B] = 0;
            H(a, 0x40) = 0;
            a[6] = 0;
            if (D_800BFAE7 == 0) {
                func_8004ED94(0x2B, 0x41);
                a[5] = 1;
            } else {
                func_80040CDC(a, 0, D_80133154);
                a[0x70] = 2;
                a[5] = 2;
            }
        }
        break;
    case 1:
        if (!(D_800BF822 & 1) || ++H(a, 0x40) >= 0x78) {
            if (D_800BFAE7 != 0) {
                H(a, 0x60) = 0;
                a[5]++;
            } else {
                a[0] = 1;
                a[5] = 0;
                func_80042310();
            }
        }
        break;
    case 2:
        switch (a[6]) {
        case 0:
            func_80041098(a);
            if (a[0x70] == 0xFF) {
                func_8004D604(0x33, 1);
                func_80074590(0x1A, -5, 0);
                (*(u8 **)(a + 0x14))[4] = 3;
                a[6]++;
            }
            break;
        case 1:
            H(a, 0x60) += 0x10;
            if (H(a, 0x60) >= 0x400) {
                H(a, 0x60) = 0x400;
                func_80040CDC(a, 0, D_80133198);
                a[0x70] = 2;
                a[6]++;
            }
            t = func_80083E80(H(a, 0x60)) >> 2;
            H(*(u8 **)(a + 0xC4), 0xA) = t;
            H(*(u8 **)(a + 0xC8), 0xA) = -t;
            break;
        case 2:
            func_80041098(a);
            if (a[0x70] == 0xFF) {
                D_800BF9D5 = 3;
                a[6]++;
            }
            break;
        case 3:
            H(a, 0x60) -= 0x10;
            if (H(a, 0x60) <= 0) {
                func_80074590(0x1A, -5, 0);
                func_80040CDC(a, 0, D_800A3E58);
                a[0x70] = 2;
                H(a, 0x60) = 0;
                a[6]++;
            }
            t = func_80083E80(H(a, 0x60)) >> 2;
            H(*(u8 **)(a + 0xC4), 0xA) = t;
            H(*(u8 **)(a + 0xC8), 0xA) = -t;
            break;
        case 4:
            func_80041098(a);
            if (a[0x70] == 0xFF) {
                a[5] = 3;
            }
            break;
        }
        break;
    }
}

void func_8011BAB4(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 4);
    switch (temp_v1) {                              /* irregular */
    case 0:
        ((void (*)())func_8011B650)();
        return;
    case 1:
        ((void (*)())f_UpdateCircusClothesLockerActor)();
        return;
    case 3:
        func_8007A624();
        /* fallthrough */
    case 2:
        return;
    }
}

typedef struct { s16 p0, x, p4, y, p8, z; } HV;
extern u8 *D_1F800214_120a;
s32 func_8011BB38(u8 *a)
{
    HV v;
    u8 *g = D_1F800214_120a;

    switch (a[0x78]) {
    default:
        return 0;
    case 0:
        v.x = 0x63A;
        v.y = -0xAF0;
        v.z = 0x1B5C;
        func_80070F00(g, 1, &v);
        func_800708B4(3);
        a[0x78]++;
        break;
    case 1:
        if (g[3] == 0) {
            func_800708B4(1);
            *(s16 *)(a + 0x4A) = 0;
            return 1;
        }
        return 0;
    }
    return 0;
}

extern s8 D_1F800214[];
s32 func_8011BBE4(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x14) = func_80117444(*((s32 *)D_1F800214));
    return 1;
}

extern s8 D_1F800214[];
s32 func_8011BC1C(void *arg0) {
    func_80041718(*((s32 *)D_1F800214), 0, 4);
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x14), s8 *, 4) = 3;
    return 1;
}

typedef struct { u8 pad[0x60]; s32 unk60; s32 unk64; } AreaStateF58;
typedef struct { u8 pad0[7]; u8 unk7; u8 pad8[6]; u8 unkE; u8 unkF; u8 pad10[0x21]; u8 unk31; s16 unk32; } AreaState808_E;
typedef struct { u8 pad[0xC0]; u8 *parts[1]; } AreaPartsOwner;
typedef struct { s16 unk0; s16 x, y, z; } PartPose;
extern PartPose D_80133210[3];
extern PartPose D_80133228[3];
typedef struct { u8 pad[0x5E]; u8 pose; u8 pad2[0xC0 - 0x5F]; s16 *parts[3]; } PosedActor;
typedef struct { s16 x, y, z, pad; } RingVec;
typedef struct { s16 pos; s16 vel; } RiseMotion;
void func_8011BC60(PosedActor *a, s32 b, s32 c) {
    s32 i;

    for (i = 0; i < 3; i++) {
        if (b == 0) {
            func_80051B04(a->parts[i], c, i);
            a->parts[i][0] = D_80133210[i].x;
            a->parts[i][1] = D_80133210[i].y;
            a->parts[i][2] = D_80133210[i].z;
        } else {
            func_80051B04(a->parts[i], c, i + 3);
            a->parts[i][0] = D_80133228[i].x;
            a->parts[i][1] = D_80133228[i].y;
            a->parts[i][2] = D_80133228[i].z;
        }
    }
    a->pose = b;
}

extern u8 D_8001B7B0[];
void D_8004C930();
void func_8011BD6C(u8 *a, s32 b) {
    u16 v;
    u8 *p;

    switch (a[5]) {
    case 0:
        if (a[0x29] == 1) {
            a[5]++;
            func_8011BC60(a, 0, b);
            func_80077C40(a, D_8001B7B0, 0);
            D_800BF870.pad1[0x1A2] |= 1 << a[3];
            func_8004ED94(0x5B, 0x41);
        }
        break;
    case 1:
        if (a[0x29] == 2) {
            F16(a, 0x50) = 0;
            a[5]++;
            func_8003116C(8, a + 0x2C, -0x20);
        }
        break;
    case 2:
        v = (F16(a, 0x50) + 0x100) & 0xFFF;
        F16(a, 0x50) = v;
        if (v == 0) {
            F16(a, 0xBA) = 0x1000;
            a[5]++;
            break;
        }
        if (v == 0xC00) {
            p = func_80072DDC(a, 0, 5, 4);
            if (p != NULL) {
                M2C_FIELD(p, void **, 0x1C) = D_8004C930;
                F16(p, 0x2E) = F16(a, 0x2E);
                F16(p, 0x32) = F16(a, 0x32) - 0x78;
                F16(p, 0x36) = F16(a, 0x36);
                p[3] = 0xC;
            }
            M2C_FIELD(a, u8 **, 0x10) = p;
        }
        F16(a, 0xBA) += (func_80083E80(F16(a, 0x50)) << 8) >> 12;
        break;
    case 3:
        if (M2C_FIELD(a, u8 **, 0x10)[4] == 3) {
            D_1F800137 = 0;
            a[5]++;
        }
        break;
    case 4:
        if (a[0x29] == 1) {
            F16(a, 0x52) = 0;
            F16(a, 0x44) = 0x200;
            a[5]++;
        }
        break;
    case 5:
        F16(a, 0x52) = (F16(a, 0x52) + 0x200) & 0xFFF;
        F16(a, 0x58) = (func_80083E80(F16(a, 0x52)) * F16(a, 0x44)) >> 12;
        if (F16(a, 0x52) == 0) {
            a[5]++;
            F16(a, 0x44) -= 0x80;
            func_8003116C(8, a + 0x2C, -0x20);
        }
        break;
    case 6:
        F16(a, 0x52) = (F16(a, 0x52) + 0x200) & 0xFFF;
        F16(a, 0x58) = (func_80083E80(F16(a, 0x52)) * F16(a, 0x44)) >> 12;
        if (F16(a, 0x52) == 0) {
            a[5]++;
        }
        break;
    case 7:
        if (a[0x29] == 2) {
            D_1F800137 = 0;
            a[5] = 4;
        }
        break;
    }
}

extern u8 D_800BF809;
extern u8 D_800ECF58_742e[];
extern u8 D_80133210_bcc2[];
void func_8011C02C(u8 *a)
{
    s32 s = a[4];
    u8 *g;
    u8 *e;

    switch (s) {
    case 0:
        g = D_800ECF58_742e;
        if (func_800519E0(a, 3, *(s32 *)(g + 0x48), D_80133210_bcc2) == 0) {
            *(s32 *)(a + 0x3C) = *(s32 *)(g + 0x4C);
            {
                u8 *st = (u8 *)&D_800BF870;
                if (st[3] != 0) {
                    a[4] = 3;
                    goto spawn;
                }
                if ((st[0x1A3] >> a[3]) & 1) {
                    a[0x5E] = 0;
                    func_80077C40(a, D_8001B7B0, 0);
                } else {
                    func_8011BC60(a, 1, 0x12);
                    func_80077C40(a, D_8001B7B0, 1);
                }
            }
            a[0] = 1;
            *(s16 *)(a + 0x80) = 0x190;
            *(s16 *)(a + 0x82) = 0x320;
            *(s16 *)(a + 0x84) = 0xB4;
            *(s16 *)(a + 0x86) = 0xB4;
            a[0x29] = 0;
            a[0x2B] = 0;
            a[4]++;
            if (a[0x5E] == 0) {
                a[5] = 4;
            }
        spawn:
            *(s16 *)(a + 0x80) = 0xF0;
            *(s16 *)(a + 0x82) = 0x1E0;
            e = (u8 *)func_80072DDC(a, 1, 3, 0x10);
            if (e != NULL) {
                *(void **)(e + 0x1C) = func_80116B88;
                e[3] = 5;
                *(s16 *)(e + 0x2E) = *(s16 *)(a + 0x2E);
                *(s16 *)(e + 0x32) = *(s16 *)(a + 0x32);
                *(s16 *)(e + 0x36) = *(s16 *)(a + 0x36);
            }
        }
        break;
    case 1:
        if (func_8007778C(a) != 0) {
            func_80076D68(a);
            switch (a[6]) {
            case 2:
                a[0] = s;
                a[6] = 0;
            case 0:
                if (a[0x2B] == 1) {
                    *(s16 *)(a + 0x40) = 0x1E;
                    a[6]++;
                    if (a[0x5E] == 0) {
                        func_8004ED94(0x62, 0x41);
                    } else {
                        func_8004ED94(0x61, 0x41);
                    }
                }
                break;
            case 1:
                if (--*(s16 *)(a + 0x40) == 0) {
                    a[0] = 2;
                    a[6]++;
                    func_80042310();
                }
                break;
            }
            func_8011BD6C(a, 0x12);
            func_800518FC(a);
        }
        a[0x29] = 0;
        a[0x2B] = 0;
        break;
    case 2:
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

void func_8011C2D0(u8 *a0)
{
    u8 *r = func_80072DDC(a0, 1, 3, 0x10);

    if (r) {
        *(void **)(r + 0x1C) = func_80116B88;
        r[3] = 5;
        *(s16 *)(r + 0x2E) = *(s16 *)(a0 + 0x2E);
        *(s16 *)(r + 0x32) = *(s16 *)(a0 + 0x32);
        *(s16 *)(r + 0x36) = *(s16 *)(a0 + 0x36);
    }
}

void func_8011C340(u8 *a)
{
    u8 *d = (u8 *)W_d1fb(a, 0x14) + 0x60;
    u8 *o = (u8 *)W_d1fb(a, 0x10);
    u8 *q;
    s32 x0, x1, x2;

    U_d0c0(d, 4) = U_d0c0(*(u8 **)(a + 0xC0), 0x2C) + ((H(*(u8 **)(a + 0xC0), 0x1A) * -0xA0) >> 12);
    U_d0c0(d, 6) = U_d0c0(*(u8 **)(a + 0xC0), 0x30) + ((H(*(u8 **)(a + 0xC0), 0x20) * -0xA0) >> 12);
    U_d0c0(d, 8) = U_d0c0(*(u8 **)(a + 0xC0), 0x34) + ((H(*(u8 **)(a + 0xC0), 0x26) * -0xA0) >> 12);
    U_d0c0(d, 0xC) = U_d0c0(d, 4);
    U_d0c0(d, 0xE) = U_d0c0(d, 6);
    U_d0c0(d, 0x10) = U_d0c0(d, 8);
    q = *(u8 **)(o + 0xC0);
    x0 = (((H(q, 0x18) * -0xA0) >> 12) + W_d1fb(q, 0x2C) - H(d, 0xC)) / 20;
    x1 = (((H(q, 0x1E) * -0xA0) >> 12) + W_d1fb(q, 0x30) - (H(d, 0xE) + 0xC8)) / 20;
    x2 = (((H(q, 0x24) * -0xA0) >> 12) + W_d1fb(q, 0x34) - H(d, 0x10)) / 20;
    H(a, 0x40) = 0x14;
    H(a, 0x4E) = x0;
    H(a, 0x50) = x1;
    H(a, 0x52) = x2;
}

void func_8011C4D0(void *arg0) {
    void *temp_a0;
    void *temp_a0_2;
    void *temp_a0_3;
    void *temp_a0_4;
    void *temp_a1;
    void *temp_a1_2;
    void *temp_a2;
    void *temp_a3;

    temp_a1 = M2C_FIELD(arg0, void **, 0xC0);
    temp_a3 = M2C_FIELD(arg0, void **, 0x10);
    temp_a2 = M2C_FIELD(arg0, s32 *, 0x14) + 0x60;
    M2C_FIELD(temp_a2, s16 *, 4) = (s16) (M2C_FIELD(temp_a1, u16 *, 0x2C) + ((s32) -(M2C_FIELD(temp_a1, s16 *, 0x1A) * 0xA0) >> 0xC));
    temp_a1_2 = M2C_FIELD(arg0, void **, 0xC0);
    M2C_FIELD(temp_a2, s16 *, 6) = (s16) (M2C_FIELD(temp_a1_2, u16 *, 0x30) + ((s32) -(M2C_FIELD(temp_a1_2, s16 *, 0x20) * 0xA0) >> 0xC));
    temp_a0 = M2C_FIELD(arg0, void **, 0xC0);
    M2C_FIELD(temp_a2, s16 *, 8) = (s16) (M2C_FIELD(temp_a0, u16 *, 0x34) + ((s32) -(M2C_FIELD(temp_a0, s16 *, 0x26) * 0xA0) >> 0xC));
    temp_a0_2 = M2C_FIELD(temp_a3, void **, 0xC0);
    M2C_FIELD(temp_a2, s16 *, 0xC) = (s16) (M2C_FIELD(temp_a0_2, u16 *, 0x2C) + ((s32) -(M2C_FIELD(temp_a0_2, s16 *, 0x18) * 0xA0) >> 0xC));
    temp_a0_3 = M2C_FIELD(temp_a3, void **, 0xC0);
    M2C_FIELD(temp_a2, s16 *, 0xE) = (s16) ((M2C_FIELD(temp_a0_3, u16 *, 0x30) + ((s32) -(M2C_FIELD(temp_a0_3, s16 *, 0x1E) * 0xA0) >> 0xC)) - 0xC8);
    temp_a0_4 = M2C_FIELD(temp_a3, void **, 0xC0);
    M2C_FIELD(temp_a2, s16 *, 0x10) = (s16) (M2C_FIELD(temp_a0_4, u16 *, 0x34) + ((s32) -(M2C_FIELD(temp_a0_4, s16 *, 0x24) * 0xA0) >> 0xC));
}

#define P(p, o) (*(u8 **)((u8 *)(p) + (o)))
extern u8 D_800BF8DB;
static inline s32 StepC5FC(u8 *a, u8 *v)
{
    H(a, 0x40)--;
    if (H(a, 0x40) == 0) {
        return 1;
    }
    H(v, 0xC) += H(a, 0x4E);
    H(v, 0xE) += H(a, 0x50);
    H(v, 0x10) += H(a, 0x52);
    return 0;
}
void f_UpdateCircusWellLidActor(u8 *a)
{
    u8 *b;

    switch (a[4]) {
    case 0:
        if (func_80051B70(a, 0xC, 0x36) != 0) {
            break;
        }
        if (D_800BF8DB != 0) {
            if (D_800BF8DB != 0xFF) {
                a[6] = 0;
                a[5] = 0xA;
            } else {
                a[4] = 3;
                break;
            }
        } else {
            H(a, 0x80) = 0xF0;
            H(a, 0x82) = 0x1E0;
            H(a, 0x84) = 0x64;
            a[0] = 1;
            H(a, 0x86) = 0xC8;
            a[0x2B] = 0;
        }
        a[4]++;
        break;
    case 1:
        func_8007778C(a);
        switch (a[5]) {
        case 0:
            if (a[0x2B] != 0) {
                a[0x2B] = 0;
                a[0] = 2;
                func_800440E4(D_800E7E80, 0xC1, 4);
                H(a, 0x40) = 0;
                func_80040B48(0x27);
                a[5]++;
            } else if (D_800BF8DB != 0) {
                a[0] = 2;
                a[6] = 0;
                a[5] = 0xA;
            }
            break;
        case 1:
            if (func_80042728() == 0) {
                H(a, 0x40)++;
                if (H(a, 0x40) < 0xC8) {
                    break;
                }
            }
            func_80042310();
            a[6] = 0;
            a[5] = 0xA;
            break;
        case 10:
            switch (a[6]) {
            case 0:
                if (D_800BFA2C == 0xF) {
                    P(a, 0x10) = D_800BF860_c64f;
                    b = func_80118294(a);
                    P(a, 0x14) = b;
                    if (P(a, 0x10) != NULL && b != NULL) {
                        H(b, 0x60) = 1;
                        ((void (*)())func_8011C340)(a, b);
                        a[6]++;
                    }
                }
                break;
            case 1:
                if (StepC5FC(a, P(a, 0x14) + 0x60)) {
                    D_800BFA2C = 0x10;
                    a[6]++;
                }
                break;
            case 2:
                func_8011C4D0(a);
                if (D_800BFA2C == 0x12) {
                    func_80074590(0x8C, 3, 0);
                    func_80074590(0x84, 8, 0);
                    H(a, 0x56) = 0xC00;
                    H(a, 0x58) = 0x1000;
                    H(a, 0x4A) = -0x2800;
                    H(a, 0x50) = 0x280;
                    a[6]++;
                }
                break;
            case 3:
                func_8011C4D0(a);
                H(a, 0x36) -= 0x10;
                if (H(a, 0x36) < 0x37DC) {
                    H(a, 0x36) = 0x37DC;
                }
                H(a, 0x58) -= 0x20;
                if (H(a, 0x58) < 0xC00) {
                    H(a, 0x58) = 0xC00;
                }
                H(a, 0x4A) += H(a, 0x50);
                if (H(a, 0x4A) >= 0x3800) {
                    H(a, 0x4A) = 0x3800;
                }
                W_d1fb(a, 0x30) += H(a, 0x4A) << 8;
                if (H(a, 0x32) >= -0xAEF && H(a, 0x4A) > 0) {
                    H(a, 0x40) = 0;
                    func_80074590(0x84, 8, 0);
                    H(a, 0x4A) = -0x1800;
                    H(a, 0x58) = 0xC00;
                    H(a, 0x32) = -0xAF0;
                    H(a, 0x36) = 0x37DC;
                    a[6]++;
                }
                break;
            case 4:
                func_8011C4D0(a);
                H(a, 0x56) += 8;
                H(P(a, 0xC0), 0xA) += 0x40;
                H(a, 0x2E) += 0x10;
                H(a, 0x4A) += H(a, 0x50);
                if (H(a, 0x4A) >= 0x3800) {
                    H(a, 0x4A) = 0x3800;
                }
                W_d1fb(a, 0x30) += H(a, 0x4A) << 8;
                if (H(a, 0x40) < 0xF) {
                    H(a, 0x40)++;
                    if (H(a, 0x40) == 0xF) {
                        func_80074590(0x84, 8, 0);
                    }
                }
                if (H(a, 0x32) >= -0x7CF) {
                    b = P(a, 0x14);
                    b[4] = 3;
                    a[4] = 3;
                }
                break;
            }
            break;
        }
        if (a[1] != 0) {
            func_800517F8(a);
        }
        break;
    case 2:
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", f_UpdateCircusSeesawActor);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8011CF1C);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8011D10C);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8011D2D8);

void func_8011D410(u8 *a)
{
    switch (a[4]) {
    case 0:
        *(s16 *)(a + 0x80) = 0x10E;
        *(s16 *)(a + 0x82) = 0x1F4;
        *(s16 *)(a + 0x84) = 0x64;
        a[4] = 1;
        a[0] = 1;
        *(s16 *)(a + 0x86) = 0xC8;
        break;
    case 1:
        func_8007778C(a);
        break;
    case 2:
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

extern u8 D_800BF8E9;
extern u8 D_800E7EEF;
void func_8011D4AC(u8 *a)
{
    s16 sp[8];

    switch (a[4]) {
    case 0:
        if (func_80051B70(a, 0xC, 0x38) == 0) {
            *(s16 *)(a + 0x80) = 0x50;
            *(s16 *)(a + 0x82) = 0xA0;
            *(s16 *)(a + 0x84) = 0x140;
            *(s16 *)(a + 0x86) = 0x140;
            a[0] = 1;
            a[0x2B] = 0;
            a[0x29] = 0;
            *(s16 *)(a + 0x54) = 0;
            *(s16 *)(a + 0x56) = 0x638;
            *(s16 *)(a + 0x58) = 0;
            a[4]++;
        }
        break;
    case 1:
        if (a[0x29] != 0 && D_800BF8E9 == 0) {
            func_80040B48(0x35);
        }
        if (func_8007778C(a) != 0) {
            func_800517F8(a);
        }
        a[0x2B] = 0;
        a[0x29] = 0;
        break;
    case 2:
        switch (a[6]) {
        case 0:
            if (D_800E7EEF != 0x15) {
                a[0] = 1;
                a[4] = 1;
                a[5] = 0;
                a[6] = 0;
                a[0x29] = 0;
                if (func_8007778C(a) != 0) {
                    func_800517F8(a);
                }
            } else {
                a[6] = 1;
                func_80040C00(0x35);
                D_800BF870.pad1[0x1CC] |= 1 << a[3];
                func_8006E1C0(8, &D_800BF870);
                sp[1] = *(s16 *)(a + 0x2E);
                sp[3] = *(s16 *)(a + 0x32) - *(s16 *)(a + 0x84) / 2;
                sp[5] = *(s16 *)(a + 0x36);
                func_8006CBA8(sp);
                func_8003116C(0x37, sp, -0x20);
                func_80027144(*(s32 *)(*(u8 **)(a + 0xC0) + 0x40), sp, 0x700, 8);
                func_80074590(0xC, 0, 0);
                func_80027144(*(s32 *)(*(u8 **)(a + 0xC0) + 0x40), a + 0x2C, 0x700, 8);
                func_80074590(0xC, 0, 0);
            }
            break;
        case 1:
            if (D_800BF809 == 0) {
                a[4] = 3;
                func_8006E1E4();
            }
            break;
        }
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

extern u8 D_80133274[];
extern u8 D_8001B4DC[];
extern u8 D_801332EC[];
extern u8 D_8013339C[];
void func_8011D724(u8 *a)
{
    u8 *g;
    u8 *st;

    switch (a[4]) {
    case 0:
        g = D_800ECF58;
        if (func_800519E0(a, 0xF, *(s32 *)(g + 0x90), D_80133274) != 0) {
            break;
        }
        *(s32 *)(a + 0x3C) = *(s32 *)(g + 0x8C);
        func_80077C40(a, D_8001B4DC, 0);
        *(s16 *)(a + 0xB8) = 0x800;
        *(s16 *)(a + 0xBA) = 0x800;
        *(s16 *)(a + 0xBC) = 0x800;
        *(s16 *)(a + 0x56) = 0x800;
        a[0] = 9;
        *(s16 *)(a + 0x80) = 0x64;
        *(s16 *)(a + 0x82) = 0xC8;
        *(s16 *)(a + 0x84) = 0x50;
        *(s16 *)(a + 0x54) = 0;
        *(s16 *)(a + 0x58) = 0;
        *(s16 *)(a + 0x86) = 0x90;
        a[0x2B] = 0;
        a[4]++;
        func_80051B04(*(u8 **)(a + 0xEC), 0x24, 0x11);
        func_80051B04(*(u8 **)(a + 0xF0), 0x24, 0x12);
        break;
    case 1:
        func_8007778C(a);
        func_8004190C(a);
        switch (a[6]) {
        case 0:
            if (a[0x2B] == 3) {
                a[6] = 1;
                func_80042354(1, 3);
            }
            break;
        case 1:
            st = (u8 *)&D_800BF870;
            if (st[0x1DE] == 2 && st[0x1D8] == 2) {
                func_80040CDC(a, D_8001B4DC, D_801332EC);
                st[0x1DE] = 3;
                a[6] += 2;
            } else {
                func_80040CDC(a, D_8001B4DC, D_8013339C);
                a[6]++;
            }
            a[0x70] = 1;
            break;
        case 2:
            func_80041098(a);
            if (a[0x70] == 0xFF) {
                a[6] = 0;
                func_80042310();
            }
            break;
        case 3:
            func_80041098(a);
            if (a[0x70] == 0xFF) {
                a[4] = 3;
                func_80042310();
            }
            break;
        }
        func_800518FC(a);
        a[0x2B] = 0;
        break;
    case 2:
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

extern s8 D_800BF818;
s32 func_8011D9A0(void) {
    D_800BF818 = 7;
    return 1;
}

extern u8 D_801318E8[];
extern u8 D_801333F0[];
void func_8011DCEC(u8 *a);
void func_8011DD48(u8 *a);
void func_8011D9B4(u8 *a)
{
    u8 *g;
    u8 *st;

    switch (a[4]) {
    case 0:
        g = D_800ECF58;
        *(s32 *)(a + 0x3C) = *(s32 *)(g + 0x38);
        st = (u8 *)&D_800BF870;
        if (st[0xA3] == 0xFF) {
            if (func_800519E0(a, 0xF, *(s32 *)(g + 0x64), D_801318E8) != 0) {
                break;
            }
            func_80040CDC(a, D_8014005C_9175, D_801333F0);
            func_80041718(a, 0, 0);
            a[0x5E] = 4;
            a[0xB] = 0x40;
        } else {
            if (func_800519E0(a, 0xF, *(s32 *)(g + 0x68), D_801318E8) != 0) {
                break;
            }
            *(s32 *)(*(u8 **)(a + 0xC8) + 0x40) = 0;
            *(s32 *)(*(u8 **)(a + 0xCC) + 0x40) = 0;
            *(s32 *)(*(u8 **)(a + 0xD4) + 0x40) = 0;
            *(s32 *)(*(u8 **)(a + 0xD8) + 0x40) = 0;
            *(s32 *)(*(u8 **)(a + 0xE0) + 0x40) = 0;
            *(s32 *)(*(u8 **)(a + 0xE4) + 0x40) = 0;
            *(s32 *)(*(u8 **)(a + 0xF0) + 0x40) = 0;
            func_80040CDC(a, D_8014005C_9175, D_801333F0);
            if (st[0xA3] == 0) {
                func_80041718(a, 0, 0);
                a[0x5E] = 0;
            } else {
                func_80041718(a, 0xB, 0);
                a[0x5E] = 1;
            }
        }
        a[0] = 9;
        *(s16 *)(a + 0x80) = 0x8C;
        *(s16 *)(a + 0x82) = 0x118;
        *(s16 *)(a + 0x84) = 0x8C;
        *(s16 *)(a + 0x86) = 0x118;
        a[4]++;
        break;
    case 1:
        a[1] = 1;
        func_80077E7C(a);
        func_80041098(a);
        func_8004190C(a);
        func_800518FC(a);
        switch (a[5]) {
        case 0:
            func_8011DC14(a);
            break;
        case 1:
            func_8011DCEC(a);
            break;
        case 2:
            func_8011DD48(a);
            break;
        }
        a[0x2B] = 0;
        break;
    case 2:
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8011DC14);

extern void *D_80133610[];
void func_8011DCEC(u8 *a)
{
    if (a[0x71] == 0xFF) {
        func_80040D68(a, D_80133610[a[0x5E]]);
        a[5] = 2;
        a[0x70] = 1;
    }
}

void func_8011DD48(u8 *a)
{
    if (a[0x71] == 0xFF) {
        switch (a[0x5E]) {
        case 0:
        case 3:
            a[0x5E]++;
            break;
        case 2:
            func_8004D4F4(*(s16 *)(a + 0x60), 1);
            a[0x5E] = 1;
            break;
        }
        a[5] = 0;
    }
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8011DDD0);

extern u8 D_800BF913;
s32 func_8011DEB8(u8 *a)
{
    u8 *g;
    if (D_800BF913 == 0xFF) {
        return 0;
    }
    g = D_800BF808;
    *(s16 *)(a + 0x60) = g[3];
    switch (g[3]) {
    case 0x67:
        a[0x5E] = 3;
        break;
    case 0x59 ... 0x5C:
    case 0x66:
    case 0x68:
        a[0x5E] = 2;
        break;
    default:
        *(s16 *)(a + 0x60) = -1;
        return 0;
    }
    return 1;
}

s32 func_8011DF48(u8 *a)
{
    switch (a[0x78]) {
    default:
        return 0;
    case 0:
        *(s16 *)(a + 0x40) = 0x3C;
        *(s16 *)(a + 0x42) = 6;
        a[0x78]++;
        break;
    case 1:
        if (--*(s16 *)(a + 0x42) <= 0) {
            *(s16 *)(a + 0x42) = 6;
            func_80074590(8, 6, -0x1E);
        }
        if (--*(s16 *)(a + 0x40) <= 0) {
            return 1;
        }
        break;
    }
    return 0;
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8011DFF8);

void func_8011E13C(u8 *a) {
    switch (a[4]) {
    case 0:
        func_8011E248(a);
        break;
    case 1:
        func_8007778C(a);
        func_80041098(a);
        func_8004190C(a);
        switch (a[5]) {
        case 0:
            func_8011DFF8(a);
            break;
        case 1:
            func_8011E310(a);
            break;
        case 2:
            func_8011E36C(a);
            break;
        }
        func_800518FC(a);
        a[0x2B] = 0;
        break;
    case 2:
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

extern u8 D_80131960[];
extern u8 D_800A3CD0[];
void func_8011E248(u8 *p)
{
    u8 *s = D_800ECF58;

    *(s32 *)(p + 0x3C) = *(s32 *)(s + 0x38);
    if (func_800519E0(p, 0xF, *(s32 *)(s + 0x6C), D_80131960) == 0) {
        func_80040CDC(p, D_8014005C_9175, D_800A3CD0);
        func_80041718(p, 9, 0);
        p[0x5E] = D_800BFA2D;
        *(s16 *)(p + 0x80) = 0x78;
        p[0xB] = 0x40;
        *(s16 *)(p + 0x84) = 0x78;
        p[0] = 9;
        *(s16 *)(p + 0x82) = 0xF0;
        *(s16 *)(p + 0x54) = 0;
        *(s16 *)(p + 0x56) = 0;
        *(s16 *)(p + 0x58) = 0;
        *(s16 *)(p + 0x86) = 0xD2;
        p[0x2B] = 0;
        p[0x29] = 0;
        p[4]++;
    }
}

extern void *D_801337B0[];
void func_8011E310(u8 *p)
{
    if (p[0x71] == 0xFF) {
        func_80040D68(p, D_801337B0[p[0x5E]]);
        p[0x70] = 1;
        p[5] = 2;
    }
}

void func_8011E36C(u8 *p)
{
    if (p[0x71] == 0xFF) {
        switch (p[0x5E]) {
        case 0:
            p[0x5E]++;
            D_800BFA2D = 1;
            break;
        case 2:
            p[4] = 3;
            return;
        }
        p[5] = 0;
        p[6] = 0;
        *(s16 *)(p + 0x40) = 0x1E;
    }
}

extern u8 D_800BFB05;
s32 func_8011E3D4(u8 *a)
{
    if (D_800BFB05 != 0) {
        a[0x5E] = 2;
        return 3;
    }
    return 2;
}

extern u8 D_801337C8[];
extern u8 D_801337F0[];
extern u8 D_801337E0[];
extern u8 D_800BFAEA;
s32 func_8011E3FC(u8 *a)
{
    switch (a[6]) {
    case 0:
        if (a[0x2B] == 3) {
            a[6] = 1;
            func_80042354(1, 3);
            func_80040CDC(a, D_8014005C_9175, D_801337C8);
            a[0x70] = 1;
        }
        break;
    case 1:
        func_80041098(a);
        if (a[0x70] == 0xFF) {
            a[6]++;
            func_80040CDC(a, D_8014005C_9175, D_801337F0);
            a[0x70] = 1;
        }
        break;
    case 2:
        func_80041098(a);
        if (a[0x70] == 0xFF) {
            if (D_800BFAEA != 0) {
                return 2;
            }
            a[6]++;
            func_80040CDC(a, D_8014005C_9175, D_801337E0);
            a[0x70] = 1;
        }
        break;
    case 3:
        func_80041098(a);
        if (a[0x70] == 0xFF) {
            func_80042310();
            return 1;
        }
        break;
    }
    return 0;
}

extern u8 D_80133850[];
s32 func_8011E554(u8 *a)
{
    switch (a[6]) {
    case 0:
        if (a[0x2B] == 3) {
            a[6] = 1;
            func_80042354(1, 3);
            func_80040CDC(a, D_8014005C_9175, D_801337C8);
            a[0x70] = 1;
        }
        break;
    case 1:
        func_80041098(a);
        if (a[0x70] == 0xFF) {
            a[6]++;
            func_80040CDC(a, D_8014005C_9175, D_80133850);
            a[0x70] = 1;
        }
        break;
    case 2:
        func_80041098(a);
        if (a[0x70] == 0xFF) {
            a[6]++;
            func_80040CDC(a, D_8014005C_9175, D_801337E0);
            a[0x70] = 1;
        }
        break;
    case 3:
        func_80041098(a);
        if (a[0x70] == 0xFF) {
            a[6] = 0;
            func_80042310();
        }
        break;
    }
    return 0;
}

extern u8 D_800BFA37;
extern u8 D_80133860[];
extern u8 D_80133868[];
extern u8 D_801338A8[];
extern u8 D_801338B0[];
extern u8 D_801338B8[];
extern u8 D_801338C0[];
extern u8 D_801338C8[];
extern u8 D_801338D0[];
s32 func_8011E688(u8 *a)
{
    u8 *g;

    switch (a[6]) {
    case 0:
        if (a[0x2B] == 3) {
            a[6]++;
            func_80042354(1, 3);
            func_80040CDC(a, D_8014005C_9175, D_801337C8);
            a[0x70] = 1;
        }
        break;
    case 1:
        func_80041098(a);
        if (a[0x70] == 0xFF) {
            a[6]++;
            func_80040CDC(a, D_8014005C_9175, D_80133860);
            a[0x70] = 1;
        }
        break;
    case 2:
        func_80041098(a);
        if (a[0x70] == 0xFF) {
            g = (u8 *)&D_800BF870;
            if (g[0x27A] != 0) {
                a[6]++;
                func_80040CDC(a, D_8014005C_9175, D_80133868);
            } else {
                a[6] += 2;
                if (g[0x1C7] == 5) {
                    func_80040CDC(a, D_8014005C_9175, D_801337E0);
                } else {
                    func_80040CDC(a, D_8014005C_9175, D_801338D0);
                }
            }
            a[0x70] = 1;
        }
        break;
    case 3:
        func_80041098(a);
        if (a[0x70] == 0xFF) {
            if (D_800BFA37 == 1) {
                func_80040CDC(a, D_8014005C_9175, D_801338A8);
            } else if (D_800BFA37 == 2) {
                func_80040CDC(a, D_8014005C_9175, D_801338B0);
            } else if (D_800BFA37 == 3) {
                func_80040CDC(a, D_8014005C_9175, D_801338B8);
            } else if (D_800BFA37 == 4) {
                func_80040CDC(a, D_8014005C_9175, D_801338C0);
            } else if (D_800BFA37 == 5) {
                func_80040CDC(a, D_8014005C_9175, D_801338C8);
            }
            a[0x70] = 1;
            a[6]--;
        }
        break;
    case 4:
        func_80041098(a);
        if (a[0x70] == 0xFF) {
            a[6] = 0;
            func_80042310();
            return 1;
        }
        break;
    }
    return 0;
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8011E900);

extern u8 D_801315A0[];
extern u8 D_800BFA13;
void func_8011EB04(u8 *a)
{
    u8 *g;
    u8 *st;
    s32 r;
    s32 k;

    switch (a[4]) {
    case 0:
        g = D_800ECF58;
        if (func_800519E0(a, 0xF, *(s32 *)(g + 0x50), D_801315A0) != 0) {
            break;
        }
        *(s32 *)(a + 0x3C) = *(s32 *)(g + 0x38);
        a[0] = 9;
        *(s16 *)(a + 0x80) = 0x8C;
        *(s16 *)(a + 0x82) = 0x118;
        *(s16 *)(a + 0x84) = 0x88;
        *(s16 *)(a + 0x86) = 0x220;
        a[0xBF] = 0;
        a[4]++;
        a[0xB] = (a[0xB] & 0xC0) | 0x40;
        st = (u8 *)&D_800BF870;
        if ((st[0x1A3] & 0x1F) != 0x1F) {
            a[5] = 0;
            func_80051B04(*(u8 **)(a + 0xC0), 0x14, 0xF);
            a[8] = 1;
            a[0] = 2;
            break;
        }
        if (st[0xC4] != 0xFF) {
            a[5] = 1;
        } else {
            if (st[0x27A] != 0) {
                a[5] = 3;
            } else if (st[0x1C7] != 0) {
                a[5] = 4;
            } else {
                a[5] = 2;
            }
        }
        func_80077C40(a, D_8014005C_9175, 0x38);
        break;
    case 1:
        switch (a[5]) {
        case 0:
            if ((D_800BFA13 & 0x1F) == 0x1F) {
                a[5]++;
                func_80051B04(*(u8 **)(a + 0xC0), 0x14, 0);
                func_80077C40(a, D_8014005C_9175, 0x38);
                a[0] = 9;
            }
            break;
        case 1:
            r = func_8011E3FC(a);
            if (r == 1) {
                a[5] = 2;
                a[6] = 0;
            } else if (r == 2) {
                a[5] = 3;
                a[6] = 1;
            }
            break;
        case 2:
            func_8011E554(a);
            break;
        case 3:
            if (func_8011E688(a) != 0) {
                a[5]++;
            }
            break;
        case 4:
            func_8011E900(a);
            break;
        }
        if (func_8007778C(a) != 0) {
            if (a[5] != 0) {
                func_8004190C(a);
            }
            func_800518FC(a);
        }
        break;
    case 2:
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8011EDB8);

s32 func_8011EE70(u8 *p)
{
    u8 *e = D_800E7E80;

    switch (p[0x78]) {
    case 0:
        p[0x78] = 1;
        D_800BF80E = 0;
        e[5] = 0x29;
        e[6] = 0;
        goto end;
    case 1:
        if (D_800BF80E) {
            return 1;
        }
    end:
    default:
        return 0;
    }
}

s32 func_8011EED4(void *arg0) {
    func_801173A8(arg0);
    func_8004D604(0x36, 1);
    D_800BF870.pad1[0x1C6] += 1;
    return 1;
}

s32 func_8011EF18(void *arg0) {
    M2C_FIELD(arg0, s8 *, 0xBF) = 1;
    return 1;
}

s32 func_8011EF28(void *arg0) {
    return M2C_FIELD(arg0, u8 *, 0xBF) == 0;
}

extern s32 D_800ECFB0;
extern s32 D_800ECFB4;
extern u8 D_80131618[];
extern u8 D_80131708[];
extern u8 D_80131690[];
extern u8 D_80131780[];
s32 func_8011EF34(u8 *a)
{
    s32 k;


    k = 0xF;
    if (a[3] & 0x20) {
        k = 0x10;
    }
    if (!(D_800BFE56 & 0x80)) {
        if (!(a[3] & 0x40)) {
            if (func_800519E0(a, k, D_800ECFB0, D_80131618) == 0) {
                goto ret1;
            }
            return 0;
        } else {
            if (func_800519E0(a, k, D_800ECFB4, D_80131708) == 0) {
                goto ret1;
            }
            return 0;
        }
    } else if (!(a[3] & 0x40)) {
        if (func_800519E0(a, k, D_800ECFB0, D_80131690) == 0) {
            goto ret1;
        }
        return 0;
    }
    if (func_800519E0(a, k, D_800ECFB4, D_80131780) != 0) {
        return 0;
    }
ret1:
    return 1;
}

extern u8 D_80133900[];
s32 f_CompleteUseTheSeesawEventIfResolved(void);
s32 func_8011EFF8(u8 *a) {
    u8 *t;

    a[1] = 1;
    func_80077E7C(a);
    switch (a[6]) {
    case 0:
        a[0] = 3;
        a[0x47] = *(u16 *)(a + 0x56) >> 4;
        func_80040D68(a, D_800A3D18_ed09);
        a[0x70] = 2;
        a[6]++;
        break;
    case 1:
        if (a[0x70] == 0xFF) {
            if (f_CompleteUseTheSeesawEventIfResolved() == 0) {
                func_80040D68(a, &D_80133900);
            } else {
                t = *(u8 **)(a + 0x14);
                func_80040D68(a, *(void **)(t + 0xC));
                a[0x7A] = t[0x10];
            }
            a[0x70] = 2;
            a[6]++;
        }
        break;
    case 2:
        if (a[0x70] == 0xFF) {
            a[6]++;
        }
        break;
    case 3:
        if (func_80041438(a, a[0x47] << 4, 0x100) != 0) {
            func_8006E1E4();
            func_80042310();
            *(s16 *)(a + 0x40) = 0x14;
            a[6]++;
        }
        break;
    case 4:
        if (--*(s16 *)(a + 0x40) <= 0) {
            a[0] = 9;
            return 1;
        }
        break;
    }
    func_80041098(a);
    func_8004190C(a);
    return 0;
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8011F190);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8011F6A4);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8011F7F4);

/* tools/dispatch.py draft of func_8011FA0C (a07, 0x244 bytes): 2 inlined bodies
 * register maps (body -> here): 
 *   func_80120004_inl (a07:func_80120004, cover 1.00, regs 0.98): a0->s0, a1->a0
 *   func_8012009C_inl (a07:func_8012009C, cover 1.00, regs 1.00): same registers
 * notes:
 *   func_80120004_inl: the copy at 8011FA38 branches out to .L8011FC38 .L8011FB30: a value-returning helper used in a condition (beqz on its result stands in for each exit; check which result goes where)
 *   func_80120004_inl: code inside the copy is also reached from outside (.L8011FA44 8011FA44, .L8011FA5C 8011FA5C: a tail gcc cross-jumped, or a case entering it): that path is missing from the draft; write it out in full (gcc merges the identical tails again), from tools/decomp.py's draft
 *   func_80120004_inl: replaces 8011FA3C-8011FAF4
 *   func_8012009C_inl: the copy at 8011FB98 branches out to .L8011FC18 .L8011FC0C: a value-returning helper used in a condition (beqz on its result stands in for each exit; check which result goes where)
 *   func_8012009C_inl: replaces 8011FB98-8011FBF8
 * next: fix the draft's types and the helper calls' arguments, then
 *   python3 -I tools/ccheck.py THIS.c --prog a07 --func func_8011FA0C --sbs
 *   python3 -I tools/install_c.py THIS.c --prog a07 */

extern s32 D_800ECF90;
extern void *D_80133B20[];
extern u8 D_800BF9D9;
/* func_80120004, inlined */
static inline void func_80120004_inl(u8 *a)
{
    s32 k = 0x80;
    s32 t = D_800ECF90;

    *(s16 *)(a + 0x58) = 0;
    *(s16 *)(a + 0x54) = 0;
    a[0xB] = k;
    a[0] = 9;
    *(s32 *)(a + 0x3C) = t;
    if (!(D_800BFE56 & k)) {
        *(s16 *)(a + 0x80) = 0xC0;
        *(s16 *)(a + 0x82) = 0x180;
        *(s16 *)(a + 0x84) = 0xE0;
        *(s16 *)(a + 0x86) = 0x16C;
    } else {
        *(s16 *)(a + 0x82) = 0x100;
        *(s16 *)(a + 0x84) = 0xA0;
        *(s16 *)(a + 0x80) = k;
        *(s16 *)(a + 0x86) = 0x145;
        if (a[3] & 0x40) {
            *(s16 *)(a + 0x86) = 0x140;
        }
    }
    a[0x2B] = 0;
    a[0x29] = 0;
    a[0x5E] = 0;
}
/* func_8012009C, inlined */
static inline void func_8012009C_inl(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 0x5E);
    switch (temp_v1) {                               
    case 0:
        if ((M2C_FIELD(arg0, u8 *, 1) != 0) && (func_8011EF34(arg0) != 0)) {
            M2C_FIELD(arg0, u8 *, 0x5E) = 1U;
            return;
        }
        return;
    case 1:
        if (M2C_FIELD(arg0, u8 *, 1) == 0) {
            func_8007ADDC(arg0);
            M2C_FIELD(arg0, u8 *, 0x5E) = 0U;
        }
        break;
    }
}
void func_8011FA0C(u8 *a)
{
    void *f;

    switch (a[4]) {
    case 0:
        func_80120004_inl(a);
        if (!(a[3] & 0x80)) {
            func_8011EF34(a);
            f = D_80133B20[a[3] & 0x1F];
            *(void **)(a + 0x1C) = f;
            if (f == NULL) {
                func_8007A624(a);
                break;
            }
            *(s16 *)(a + 0x56) = 0;
        } else {
            func_80040CDC(a, D_8014005C_9175, *(s32 *)(*(u8 **)(a + 0x14) + 0xC));
            func_80041718(a, a[0x7B], 0);
            a[4]++;
        }
        break;
    case 1:
        if (!(a[0x5F] & 0xF)) {
            func_8011F6A4(a);
        } else {
            func_8011F7F4(a);
        }
        func_8012009C_inl(a);
        if (a[1] != 0) {
            func_800518FC(a);
        }
        a[0x29] = 0;
        a[0x2B] = 0;
        if (D_800BF9D9 == 2) {
            a[4] = 3;
        }
        break;
    case 2:
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8011FC50);

void func_80120004(u8 *a)
{
    s32 k = 0x80;
    s32 t = D_800ECF90;

    *(s16 *)(a + 0x58) = 0;
    *(s16 *)(a + 0x54) = 0;
    a[0xB] = k;
    a[0] = 9;
    *(s32 *)(a + 0x3C) = t;
    if (!(D_800BFE56 & k)) {
        *(s16 *)(a + 0x80) = 0xC0;
        *(s16 *)(a + 0x82) = 0x180;
        *(s16 *)(a + 0x84) = 0xE0;
        *(s16 *)(a + 0x86) = 0x16C;
    } else {
        *(s16 *)(a + 0x82) = 0x100;
        *(s16 *)(a + 0x84) = 0xA0;
        *(s16 *)(a + 0x80) = k;
        *(s16 *)(a + 0x86) = 0x145;
        if (a[3] & 0x40) {
            *(s16 *)(a + 0x86) = 0x140;
        }
    }
    a[0x2B] = 0;
    a[0x29] = 0;
    a[0x5E] = 0;
}

void func_8012009C(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 0x5E);
    switch (temp_v1) {                              /* irregular */
    case 0:
        if ((M2C_FIELD(arg0, u8 *, 1) != 0) && (func_8011EF34(arg0) != 0)) {
            M2C_FIELD(arg0, u8 *, 0x5E) = 1U;
            return;
        }
        return;
    case 1:
        if (M2C_FIELD(arg0, u8 *, 1) == 0) {
            func_8007ADDC(arg0);
            M2C_FIELD(arg0, u8 *, 0x5E) = 0U;
        }
        break;
    }
}

extern s32 *D_800E7E74;
extern u8 D_80133B70[];
extern u8 D_80133C00[];
extern u8 D_80133CF0[];
void func_80120120(u8 *a)
{
    switch (a[5]) {
    case 0:
        *(s16 *)(a + 0x56) = 0x800;
        *(s16 *)(a + 0x2E) = 0x170C;
        *(s16 *)(a + 0x32) = -0xD0C;
        *(s16 *)(a + 0x36) = 0x2D17;
        a[0x7B] = 0x17;
        a[0x28] &= 0x7F;
        func_80041718(a, 0x17, 0);
        a[5]++;
    case 1:
        func_8007778C(a);
        if (a[0x2B] == 3) {
            a[0x47] = 1;
            func_80042354(1, 3);
            func_80040D68(a, D_80133B70);
            a[0x70] = 2;
            a[5]++;
        }
        break;
    case 2:
        if (a[1] = a[0x47]) {
            func_80077E7C(a);
        }
        if (a[0x70] == 0xFF) {
            func_80040D68(a, D_80133C00);
            a[0x70] = 2;
            a[5]++;
        }
        break;
    case 3:
        a[1] = 1;
        func_80077E7C(a);
        if (a[0x70] == 0xFF) {
            func_80040D68(a, D_80133CF0);
            a[0x70] = 2;
            a[5]++;
        }
        break;
    case 4:
        if (a[0x70] == 0xFF) {
            D_800ED098++;
            a[9]--;
            *--D_800E7E74 = *(s32 *)(a + (a[9] << 2) + 0xC0);
            a[0x5E] = 1;
            a[6] = 0;
            a[5] = 0;
            a[8] = a[9];
            a[0x28] |= 0x80;
        }
        break;
    }
    func_80041098(a);
    func_8004190C(a);
    a[8] = a[9]; if (a[9] == 0x10) {
        *(s16 *)(*(u8 **)(a + 0xFC) + 0xA) = 0x40;
        *(s16 *)(*(u8 **)(a + 0xFC) + 0xC) = 0xE10;
    }
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80120344);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_801207AC);

void func_80120A00(u8 *a)
{
    u8 *st;
    u8 *p;

    switch (a[4]) {
    case 0:
        func_80040CDC(a, D_8014005C_9175, D_800A3D18_ed09);
        st = (u8 *)&D_800BF870;
        *(s16 *)(a + 0x58) = 0;
        *(s16 *)(a + 0x56) = 0;
        *(s16 *)(a + 0x54) = 0;
        if (st[0x68] == 0) {
            func_80051B04(*(u8 **)(a + ((a[9] - 1) << 2) + 0xC0), 0x21, 0);
            p = *(u8 **)(a + ((a[9] - 1) << 2) + 0xC0);
            *(s16 *)(p + 6) = 7;
            *(s16 *)(p + 0xA) = 0x40;
            *(s16 *)(p + 0xC) = 0xE10;
            *(s16 *)(p + 0) = 0;
            *(s16 *)(p + 2) = 0;
            *(s16 *)(p + 4) = 0;
            *(s16 *)(p + 8) = 0;
            *(s16 *)(p + 0x38) = 0x1000;
            *(s16 *)(p + 0x3A) = 0x1000;
            *(s16 *)(p + 0x3C) = 0x1000;
            a[0x5E] = 0;
        } else {
            D_800ED098++;
            a[9]--;
            *--D_800E7E74 = *(s32 *)(a + (a[9] << 2) + 0xC0);
            a[8] = a[9];
            if (st[0x166] < 0xB) {
                a[0x5E] = 1;
            } else {
                a[0x5E] = 2;
            }
        }
        a[4]++;
        break;
    case 1:
        switch (a[0x5E]) {
        case 0:
            func_80120120(a);
            break;
        case 1:
            func_80120344(a);
            break;
        case 2:
            func_801207AC(a);
            break;
        }
        if (a[1] != 0) {
            func_800518FC(a);
        }
        a[0x2B] = 0;
        break;
    case 2:
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

s32 func_80120C30(u8 *p)
{
    switch (p[0x78]) {
    case 0:
        p[0x47] = p[0x72];
        p[0x78]++;
        break;
    case 1:
        return 1;
    }
    return 0;
}

s32 func_80120C7C(u8 *a)
{
    switch (a[0x78]) {
    case 0:
        func_80041718(a, 0x2D, 4);
        a[0x78]++;
        break;
    case 1:
        if ((*(u8 **)(a + 0x38))[4] == 2) {
            D_800BF9D6 = 5;
            func_80074590(0x32, 0, 0);
            a[0x78]++;
        }
    case 2:
        if (a[0x79] == 1) {
            func_80041718(a, a[0x7B], 4);
            return 1;
        }
        break;
    }
    return 0;
}

void func_80120EC8(void *arg0);
void func_80120F38(u8 *p);
void func_80120FA4(void *arg0);
void func_80120D64(u8 *a)
{
    u8 *g;

    switch (a[4]) {
    case 0:
        func_80040CDC(a, D_8014005C_9175, D_800A3CD0);
        g = (u8 *)&D_800BF870;
        if (*(u16 *)(g + 0x5E6) & 0x80) {
            *(s16 *)(a + 0x32) -= 0x19;
        }
        func_80041718(a, 0x17, 0);
        a[0x5E] = g[0x9F];
        a[4]++;
        break;
    case 1:
        a[1] = 1;
        func_80077E7C(a);
        func_80041098(a);
        func_8004190C(a);
        switch (a[5]) {
        case 0:
            func_80120EC8(a);
            break;
        case 1:
            func_80120F38(a);
            break;
        case 2:
            func_80120FA4(a);
            break;
        }
        func_800518FC(a);
        a[0x2B] = 0;
        break;
    case 2:
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

extern M2C_UNK D_80133EF8;
extern M2C_UNK D_80133FB8;
void func_80120EC8(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x2B) == 3) {
        if (f_CompleteUseTheSeesawEventIfResolved() == 0) {
            func_80040D68(arg0, &D_80133FB8);
            M2C_FIELD(arg0, s8 *, 0x70) = 1;
            return;
        }
        func_80040D68(arg0, &D_80133EF8);
        M2C_FIELD(arg0, s8 *, 0x70) = 1;
        M2C_FIELD(arg0, s8 *, 5) = 1;
    }
}

void func_80120F38(u8 *p)
{
    if (p[0x71] == 0xFF) {
        if (p[0x5E] == 0) {
            func_80040D68(p, D_80133F20);
        } else {
            func_80040D68(p, D_80133F90);
        }
        p[0x70] = 1;
        p[5] = 2;
    }
}

void func_80120FA4(void *arg0) {
    u8 temp_v0;

    if (M2C_FIELD(arg0, u8 *, 0x71) == 0xFF) {
        temp_v0 = M2C_FIELD(arg0, u8 *, 0x5E);
        if (temp_v0 == 0) {
            M2C_FIELD(arg0, u8 *, 0x5E) = (u8) (temp_v0 + 1);
        }
        M2C_FIELD(arg0, s8 *, 5) = 0;
    }
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80120FD4);

extern s16 D_800E7EEA;
extern u8 D_80134030[];
extern u8 D_801340D4[];
extern u8 D_8013F730[];
void func_801211B0(u8 *a)
{
    u8 *t;

    switch (a[5]) {
    case 0:
        *(s16 *)(a + 0x2E) = 0x718;
        *(s16 *)(a + 0x32) = -0xA80;
        *(s16 *)(a + 0x36) = 0x1868;
        *(s16 *)(a + 0x56) = 0x400;
        a[0x28] |= 0x80;
        a[5]++;
    case 1:
        if (D_800BF808[0xE] == 0 || D_800BF808[0xF] != 6 || func_8007778C(a) == 0) {
            return;
        }
        if (a[0x2B] == 3) {
            func_80130D80(1);
            if (f_CompleteUseTheSeesawEventIfResolved() == 0) {
                func_80040D68(a, D_8013F730);
                a[5] = 2;
            } else {
                func_80040D68(a, D_800A3CD0);
                a[5] = 3;
            }
            a[6] = 0;
            a[0x70] = 2;
        }
        break;
    case 2:
        a[1] = 1;
        func_80077E7C(a);
        func_80041098(a);
        if (a[0x70] == 0xFF && func_80041438(a, 0x400, 0x100) != 0) {
            a[5] = 1;
        }
        break;
    case 3:
        a[1] = 1;
        func_80077E7C(a);
        func_80041098(a);
        if (a[0x70] == 0xFF) {
            switch (a[6]) {
            case 0:
                func_80040D68(a, D_80134030);
                a[0x70] = 2;
                a[6]++;
                break;
            case 1:
                D_800E7E80[5] = 0x21;
                D_800E7E80[6] = 0;
                a[6]++;
                break;
            case 2:
                D_800BF818 = 6;
                D_800E7EEA = 0x2006;
                a[6]++;
                break;
            case 3:
                if (D_800BF80F == 1) {
                    D_800BF870.pad1[0x166] = 3;
                    D_800BF870.pad1[0x168] = 1;
                    a[6] = 0;
                    a[5]++;
                }
                break;
            }
        }
        break;
    case 4:
        switch (a[6]) {
        case 0:
            t = D_800E7E80;
            {
                s32 f = D_800BF80F;
                t[1] = 1;
                if (f != 0) {
                    break;
                }
            }
            if (D_800BF9D9 == 0) {
                *(s16 *)(t + 0x6A) = 0;
                func_80040D68(a, D_801340D4);
                a[0x70] = 2;
                a[6]++;
            }
            break;
        case 1:
            D_800E7E81 = 1;
            func_80041098(a);
            if (a[0x70] == 0xFF) {
                a[0x5E] = 2;
                a[5] = 0;
            }
            break;
        }
        break;
    }
    func_8004190C(a);
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_801214AC);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8012168C);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_801218B0);

extern u8 D_800BF9D7;
void func_80121AB4(u8 *a)
{
    switch (a[4]) {
    case 0:
        func_80040CDC(a, D_8014005C_9175, D_800A3D18_ed09);
        a[0x7B] = 0x17;
        func_80041718(a, 0x17, 0);
        *(s16 *)(a + 0x58) = 0;
        *(s16 *)(a + 0x56) = 0;
        *(s16 *)(a + 0x54) = 0;
        switch (D_800BF9D7) {
        case 0:
        case 1:
            a[0x5E] = 0;
            break;
        case 3:
            a[0x5E] = 2;
            break;
        case 2:
        default:
            if (D_800BF8DB != 0xFF) {
                a[0x5E] = 1;
            } else {
                a[0x5E] = 3;
            }
            break;
        }
        a[4]++;
        break;
    case 1:
        switch (a[0x5E]) {
        case 0:
            func_80120FD4(a);
            break;
        case 1:
            func_801211B0(a);
            break;
        case 2:
            func_8012168C(a);
            break;
        case 3:
            func_801218B0(a);
            break;
        }
        if (a[1] != 0) {
            func_800518FC(a);
        }
        a[0x2B] = 0;
        break;
    case 2:
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

extern u8 D_800BF81E;
extern s32 D_1F80023C;
s32 func_80121C64(u8 *a)
{
    u8 *t = D_800E7E80;

    switch (a[0x78]) {
    case 0:
        if (*(u16 *)(t + 0x17E) & 0x180) {
            return 1;
        }
        D_800BF81E = 0;
        t[4] = 4;
        t[5] = 0x21;
        t[6] = 0;
        t[7] = 0;
        D_1F80023C = *(s32 *)(t + 4);
        if (t[0x6F] == 0) {
            func_8004ED0C(0x10, 0);
        } else {
            func_8004EDDC(t[0x6F], 0x10);
        }
        t[0x6F] = 0x10;
        t[5] = 0x3A;
        t[6] = 0;
        a[0x78]++;
        break;
    case 1:
        if (t[5] == 0x21) {
            return 1;
        }
        break;
    }
    return 0;
}

s32 func_80121D58(u8 *a)
{
    HV v;
    u8 *g = D_1F800214_120a;

    switch (a[0x78]) {
    default:
        return 0;
    case 0:
        v.x = 0x2288;
        v.y = -0xB22;
        v.z = 0x39BC;
        func_80070F00(g, 1, &v);
        func_800708B4(3);
        a[0x78]++;
        break;
    case 1:
        if (g[3] == 0) {
            func_800708B4(1);
            *(s16 *)(a + 0x4A) = 0;
            return 1;
        }
        return 0;
    }
    return 0;
}

s32 func_80121E04(void *arg0) {
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x14), s8 *, 4) = 3;
    return 1;
}

s32 func_80121E18(void) {
    func_8004D650(0x32, 1);
    return 1;
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80121E3C);

extern M2C_UNK D_800A3D18;
extern M2C_UNK D_8014005C;
void func_80121FF8(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 4);
    switch (temp_v1) {                              /* irregular */
    case 0:
        func_80040CDC(arg0, &D_8014005C, &D_800A3D18);
        M2C_FIELD(arg0, s8 *, 0x7B) = 0x17;
        func_80041718(arg0, 0x17, 0);
        M2C_FIELD(arg0, s16 *, 0x56) = 0xC00;
        M2C_FIELD(arg0, s16 *, 0x58) = 0;
        M2C_FIELD(arg0, s16 *, 0x54) = 0;
        if (D_800BFE56 & 0x80) {
            M2C_FIELD(arg0, s16 *, 0x32) = -0xAA0;
        }
        M2C_FIELD(arg0, u8 *, 4) = (u8) (M2C_FIELD(arg0, u8 *, 4) + 1);
        return;
    case 1:
        func_80121E3C(arg0);
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

void func_801224E8(void *arg0);
void func_80122558(u8 *a);
void func_801222A4(u8 *a);
void func_801220F8(u8 *a)
{
    u8 *g;

    switch (a[4]) {
    case 0:
        func_80040CDC(a, D_8014005C_9175, D_800A3CD0);
        g = (u8 *)&D_800BF870;
        if (*(u16 *)(g + 0x5E6) & 0x80) {
            *(s16 *)(a + 0x32) -= 0x14;
        }
        func_80041718(a, 0x17, 0);
        if (g[0xC9] & 0x20) {
            a[0x5E] = 2;
        } else if (g[0x2D8] != 0) {
            a[0x5E] = 1;
        } else {
            a[0x5E] = 0;
        }
        a[4]++;
        break;
    case 1:
        func_8007778C(a);
        func_80041098(a);
        func_8004190C(a);
        switch (a[5]) {
        case 0:
            func_801224E8(a);
            break;
        case 1:
            func_80122558(a);
            break;
        case 2:
            func_801222A4(a);
            break;
        }
        if (a[1] != 0) {
            func_800518FC(a);
        }
        a[0x2B] = 0;
        break;
    case 2:
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

#define AH(o) (*(s16 *)(a + (o)))
#define QH(o) (*(s16 *)(q + (o)))
#define PH(o) (*(s16 *)(p + (o)))
void func_801222A4(u8 *a)
{
    u8 *p;
    u8 *q;
    u8 *r;

    if (a[0x71] == 0xFF) {
        if (a[0x5E] == 1) {
            a[0x5E]++;
            D_800BF870.pad1[0xC8] |= 0x20;
        }
        a[5] = 0;
        return;
    }
    if (a[0x5E] != 1) {
        return;
    }
    switch (a[6]) {
    case 1:
        *(u8 **)(a + 0x14) = D_800BF844;
        a[6]++;
        break;
    case 3:
        q = *(u8 **)(a + 0x14);
        AH(0x48) = (0x1589 - QH(0x2E)) >> 5;
        AH(0x4A) = (-0xCC9 - QH(0x32)) >> 5;
        AH(0x4C) = (0x275B - QH(0x36)) >> 5;
        AH(0x50) = -0x10;
        AH(0x40) = 0x22;
        a[6]++;
    case 4:
        q = *(u8 **)(a + 0x14);
        QH(0x2E) += AH(0x48);
        QH(0x36) += AH(0x4C);
        QH(0x32) += AH(0x4A);
        AH(0x50)++;
        QH(0x32) += AH(0x50);
        if (--AH(0x40) <= 0) {
            a[6]++;
        }
        break;
    case 6:
        q = *(u8 **)(a + 0x14);
        func_8003116C(0x806, q + 0x2C, -0x14);
        a[6]++;
        break;
    case 7:
        r = func_80119418(a);
        *(u8 **)(a + 0x14) = r;
        if (r != NULL) {
            a[6]++;
        }
        break;
    case 9:
    case 11:
    case 13:
        p = *(u8 **)(a + 0x14);
        p[6]++;
        a[6]++;
        break;
    case 15:
        p = *(u8 **)(a + 0x14);
        p[5] = 2;
        p[6] = 0;
        a[6]++;
        break;
    case 17:
        p = *(u8 **)(a + 0x14);
        func_8004B0D8(p);
        func_8004D4C4(0x95, 1);
        p[4] = 2;
        a[6]++;
        break;
    case 2:
    case 5:
    case 8:
    case 10:
    case 12:
    case 14:
    case 16:
        break;
    }
}

extern M2C_UNK D_8013439C;
extern M2C_UNK D_80134664;
void func_801224E8(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x2B) == 3) {
        if (f_CompleteUseTheSeesawEventIfResolved() == 0) {
            func_80040D68(arg0, &D_80134664);
            M2C_FIELD(arg0, s8 *, 0x70) = 1;
            return;
        }
        func_80040D68(arg0, &D_8013439C);
        M2C_FIELD(arg0, s8 *, 0x70) = 1;
        M2C_FIELD(arg0, s8 *, 5) = 1;
    }
}

extern void *D_801346CC[];
void func_80122558(u8 *a)
{
    if (a[0x71] == 0xFF) {
        func_80040D68(a, D_801346CC[a[0x5E]]);
        a[0x70] = 1;
        a[5] = 2;
    }
}

extern u8 D_800BFB48;
s32 func_801225B4(void)
{
    if (D_800BFB48 != 0) {
        return 2;
    }
    return 3;
}

s32 func_801225D4(void *arg0) {
    M2C_FIELD(arg0, u8 *, 6) = (u8) (M2C_FIELD(arg0, u8 *, 6) + 1);
    return 1;
}

extern u8 D_800BF8D8;
void func_801225EC(u8 *a)
{
    s16 sp[4];
    u8 n;

    if (D_800BF8D8 != 0) {
        a[0] = 9;
        a[0x28] |= 0x80;
        func_80041718(a, 0x17, 0);
        a[0x5E] = 1;
        a[6] = 0;
        a[5] = 0;
        return;
    }
    if (a[5] != 0 && func_8007778C(a) == 0) {
        return;
    }
    switch (a[5]) {
    case 0:
        *(s16 *)(a + 0x2E) = 0x2040;
        *(s16 *)(a + 0x32) = -0xB30;
        *(s16 *)(a + 0x36) = 0x1C69;
        a[0x28] &= 0x7F;
        *(u16 *)(a + 0x86) *= 2;
        *(s32 *)(a + 0x10) = (s32)func_8012C104(a, 1);
        a[0xB] &= 0x3F;
        a[5]++;
    case 1:
        func_80041768(a, 0x1D, 4);
        *(s16 *)(a + 0x60) = func_8009A450() & 0xFFF;
        a[5]++;
    case 2:
        if (func_80041438(a, *(s16 *)(a + 0x60), 0x30) != 0) {
            if ((func_8009A450() & 3) == 0) {
                n = 1;
            } else {
                func_80041768(a, 0x1E, 4);
                *(s16 *)(a + 0x48) = func_80083F50(*(s16 *)(a + 0x56)) >> 4;
                *(s16 *)(a + 0x4C) = -func_80083E80(*(s16 *)(a + 0x56)) >> 4;
                *(s16 *)(a + 0x42) = *(s16 *)(a + 0x40) = (func_8009A450() & 0xF) + 0xA;
                if (func_8009A450() & 1) {
                    *(s16 *)(a + 0x44) = 0x600;
                } else {
                    *(s16 *)(a + 0x44) = -0x600;
                }
                n = a[5] + 1;
            }
            a[5] = n;
        }
        break;
    case 3:
        func_80041A1C(a, 1);
        if (--*(s16 *)(a + 0x40) == 0) {
            *(s16 *)(a + 0x44) = -*(s16 *)(a + 0x44);
            *(s16 *)(a + 0x40) = *(s16 *)(a + 0x42);
            a[5]++;
        }
        break;
    case 4:
        func_80041A1C(a, 1);
        if (--*(s16 *)(a + 0x40) == 0) {
            *(s16 *)(a + 0x44) = 0;
            a[5] = 1;
        }
        break;
    }
    {
        s16 x = *(s16 *)(a + 0x2E);
        sp[1] = -0xA00;
        sp[0] = x;
    }
    sp[2] = *(s16 *)(a + 0x36);
    func_8002AE0C(sp, *(s16 *)(a + 0x80), 1);
    func_8004190C(a);
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80122874);

void func_80122ABC(u8 *a)
{
    s16 sp[4];
    u8 n;

    if (a[5] != 0 && func_8007778C() == 0) {
        return;
    }
    switch (a[5]) {
    case 0:
        *(s16 *)(a + 0x2E) = 0x2040;
        *(s16 *)(a + 0x32) = -0xB59;
        *(s16 *)(a + 0x36) = 0x1C69;
        a[0x28] &= 0x7F;
        *(u16 *)(a + 0x86) *= 2;
        *(s32 *)(a + 0x10) = (s32)func_8012C104(a, 3);
        a[0xB] &= 0x3F;
        a[5]++;
    case 1:
        func_80041768(a, 0x1D, 4);
        *(s16 *)(a + 0x60) = func_8009A450() & 0xFFF;
        a[5]++;
    case 2:
        if (func_80041438(a, *(s16 *)(a + 0x60), 0x30) != 0) {
            if ((func_8009A450() & 3) == 0) {
                n = 1;
            } else {
                func_80041768(a, 0x1E, 4);
                *(s16 *)(a + 0x48) = func_80083F50(*(s16 *)(a + 0x56)) >> 4;
                *(s16 *)(a + 0x4C) = -func_80083E80(*(s16 *)(a + 0x56)) >> 4;
                *(s16 *)(a + 0x42) = *(s16 *)(a + 0x40) = (func_8009A450() & 0xF) + 0xA;
                if (func_8009A450() & 1) {
                    *(s16 *)(a + 0x44) = 0x600;
                } else {
                    *(s16 *)(a + 0x44) = -0x600;
                }
                n = a[5] + 1;
            }
            a[5] = n;
        }
        break;
    case 3:
        func_80041A1C(a, 1);
        if (--*(s16 *)(a + 0x40) == 0) {
            *(s16 *)(a + 0x44) = -*(s16 *)(a + 0x44);
            *(s16 *)(a + 0x40) = *(s16 *)(a + 0x42);
            a[5]++;
        }
        break;
    case 4:
        func_80041A1C(a, 1);
        if (--*(s16 *)(a + 0x40) == 0) {
            *(s16 *)(a + 0x44) = 0;
            a[5] = 1;
        }
        break;
    }
    {
        s16 x = *(s16 *)(a + 0x2E);
        sp[1] = -0xA00;
        sp[0] = x;
    }
    sp[2] = *(s16 *)(a + 0x36);
    func_8002AE0C(sp, *(s16 *)(a + 0x80), 1);
    func_8004190C(a);
}

void func_80122D04(u8 *a)
{
    u8 *g;

    switch (a[4]) {
    case 0:
        func_80040CDC(a, D_8014005C_9175, D_800A3D18_ed09);
        a[0x7B] = 0x17;
        func_80041718(a, 0x17, 0);
        g = (u8 *)&D_800BF870;
        *(s16 *)(a + 0x58) = 0;
        *(s16 *)(a + 0x56) = 0;
        *(s16 *)(a + 0x54) = 0;
        if (!(*(u16 *)(g + 0x5E6) & 0x80)) {
            if (g[0x68] == 0) {
                a[0] = 3;
                a[0x5E] = 0;
            } else {
                a[0x5E] = 1;
            }
        } else {
            a[0] = 3;
            a[0x5E] = 2;
        }
        a[4]++;
        break;
    case 1:
        switch (a[0x5E]) {
        case 0:
            func_801225EC(a);
            break;
        case 1:
            func_80122874(a);
            break;
        case 2:
            func_80122ABC(a);
            break;
        }
        if (a[1] != 0) {
            func_800518FC(a);
        }
        a[0x2B] = 0;
        break;
    case 2:
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80122E90);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80122F88);

extern M2C_UNK D_800A3D18;
extern u16 D_800BFE56;
extern M2C_UNK D_8014005C;
void func_80123294(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 4);
    switch (temp_v1) {                              /* irregular */
    case 0:
        func_80040CDC(arg0, &D_8014005C, &D_800A3D18);
        if (!(D_800BFE56 & 0x80)) {
            M2C_FIELD(arg0, u8 *, 0x7B) = 0x17U;
        } else {
            M2C_FIELD(arg0, u8 *, 0x7B) = 1U;
            M2C_FIELD(arg0, u16 *, 0x32) = (u16) (M2C_FIELD(arg0, u16 *, 0x32) - 0x20);
        }
        func_80041718(arg0, M2C_FIELD(arg0, u8 *, 0x7B), 0);
        M2C_FIELD(arg0, s16 *, 0x58) = 0;
        M2C_FIELD(arg0, s16 *, 0x54) = 0;
        M2C_FIELD(arg0, s16 *, 0x56) = 0x578;
        M2C_FIELD(arg0, u8 *, 4) = (u8) (M2C_FIELD(arg0, u8 *, 4) + 1);
        return;
    case 1:
        func_80122F88(arg0);
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

extern u8 D_801347A8[];
extern u8 D_801347B8[];
extern u8 D_801347C0[];
extern s32 func_8007778C(u8 *);
void func_80130D80(u8 a0);
extern void func_80040D68(u8 *, u8 *);
extern void func_80077E7C(u8 *);
extern s32 func_80041438(u8 *, s32, s32);
extern void func_8004190C(u8 *);
void f_UpdateCircusCharlesHintDialogue(u8 *a)
{
    u8 *g;
    s16 v;

    switch (a[5]) {
    case 0:
        H(a, 0x2E) = 0x1A9A;
        a[0xB] = (a[0xB] & 0xC0) | 0x80;
        if (D_800BFE56 & 0x80) {
            H(a, 0x32) = -0xAA0;
        } else {
            H(a, 0x32) = -0xA80;
        }
        H(a, 0x36) = 0x243A;
        H(a, 0x56) = 0;
        a[5]++;
    case 1:
        if (func_8007778C(a) == 0) {
            return;
        }
        if (a[0x2B] == 3) {
            func_80130D80(1);
            if (f_CompleteUseTheSeesawEventIfResolved() == 0) {
                func_80040D68(a, D_8013F730);
                a[5] = 2;
            } else {
                func_80040D68(a, D_800A3D18_ed09);
                a[5] = 3;
            }
            a[6] = 0;
            a[0x70] = 2;
        }
        break;
    case 2:
        a[1] = 1;
        func_80077E7C(a);
        if (a[0x70] == 0xFF && func_80041438(a, 0, 0x100) != 0) {
            a[5] = 0;
        }
        func_80041098(a);
        break;
    case 3:
        a[1] = 1;
        func_80077E7C(a);
        if (a[0x70] == 0xFF) {
            switch (a[6]) {
            case 0:
                a[0x7A] = 1;
                a[6] = 1;
                func_80040D68(a, D_801347B8);
                a[0x70] = 2;
                break;
            case 1:
                g = (u8 *)&D_800BF870;
                a[0xBF] = 0;
                if (g[0x1C9] & 1) {
                    a[0x7A] = 8;
                } else if (g[0xAC] == 0) {
                    a[0x7A] = 2;
                } else if (g[0xAC] != 0xFF) {
                    a[0x7A] = 3;
                } else if (g[0xAD] == 0) {
                    a[0x7A] = 4;
                } else if (g[0xAD] != 0xFF) {
                    a[0x7A] = 5;
                } else if (g[0xAE] == 0) {
                    a[0x7A] = 6;
                } else if (g[0xAE] != 0xFF) {
                    a[0x7A] = 7;
                } else {
                    g[0x1C9] |= 1;
                    a[0xBF] = 1;
                }
                if (a[0xBF] == 0) {
                    func_80040D68(a, D_801347A8);
                } else {
                    func_80040D68(a, D_801347C0);
                }
                a[6] = 2;
                a[0x70] = 2;
                break;
            case 2:
                if (func_80041438(a, 0, 0x100) != 0) {
                    a[5] = 1;
                }
                break;
            }
        }
        func_80041098(a);
        break;
    }
    func_8004190C(a);
}

extern M2C_UNK D_800A3D18;
extern M2C_UNK D_8014005C;
void func_80123698(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 4);
    switch (temp_v1) {                              /* irregular */
    case 0:
        func_80040CDC(arg0, &D_8014005C, &D_800A3D18);
        M2C_FIELD(arg0, s8 *, 0x7B) = 0x17;
        func_80041718(arg0, 0x17, 0);
        M2C_FIELD(arg0, s16 *, 0x58) = 0;
        M2C_FIELD(arg0, s16 *, 0x54) = 0;
        M2C_FIELD(arg0, s16 *, 0x56) = 0;
        M2C_FIELD(arg0, u8 *, 4) = (u8) (M2C_FIELD(arg0, u8 *, 4) + 1);
        return;
    case 1:
        f_UpdateCircusCharlesHintDialogue(arg0);
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

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80123774);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8012397C);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80124F44);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80125184);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80125400);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80125604);

extern s32 D_800ECFB8;
extern u8 D_801317F8[];
extern u8 D_80131870[];
extern u8 D_800BFA2E;
void func_801258E4(u8 *a)
{
    switch (a[4]) {
    case 0:
        if (!(D_800BFE56 & 0x80)) {
            if (func_800519E0(a, 0xF, D_800ECFB8, D_801317F8) != 0) {
                break;
            }
            *(s16 *)(a + 0x80) = 0xC0;
            *(s16 *)(a + 0x82) = 0x180;
            *(s16 *)(a + 0x84) = 0x100;
            *(s16 *)(a + 0x86) = 0x18C;
        } else {
            if (func_800519E0(a, 0xF, D_800ECFB8, D_80131870) != 0) {
                break;
            }
            *(s16 *)(a + 0x80) = 0x80;
            *(s16 *)(a + 0x82) = 0x100;
            *(s16 *)(a + 0x84) = 0xC0;
            *(s16 *)(a + 0x86) = 0x140;
        }
        *(s32 *)(a + 0x3C) = D_800ECF90;
        func_80040CDC(a, D_8014005C_9175, D_800A3D18_ed09);
        a[0xB] = 0x80;
        a[0] = 9;
        *(s16 *)(a + 0x58) = 0;
        *(s16 *)(a + 0x54) = 0;
        a[0x5E] = D_800BFA2E;
        a[4]++;
        break;
    case 1:
        switch (a[0x5E]) {
        case 0:
            func_80123774(a);
            break;
        case 1:
            func_8012397C(a);
            break;
        case 2:
            func_80124F44(a);
            break;
        case 3:
            func_80125184(a);
            break;
        case 4:
            func_80125400(a);
            break;
        case 5:
            func_80125604(a);
            break;
        }
        if (a[1] != 0) {
            func_800518FC(a);
        }
        a[0x2B] = 0;
        break;
    case 2:
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

s32 func_80125AE0(u8 *p)
{
    func_80041718(p, 0x28, 8);
    *(s32 *)(p + 0x14) = func_8012C770(p, 1);
    return 1;
}

s32 func_80125B20(u8 *a)
{
    switch (a[0x78]) {
    case 0:
        (*(u8 **)(a + 0x14))[5] = 1;
        func_80041718(a, 0x19, 4);
        a[0x78]++;
        break;
    case 1:
        if ((*(u8 **)(a + 0x14))[0x5E] == 0) {
            return 1;
        }
        break;
    }
    return 0;
}

s32 func_80125BAC(u8 *a)
{
    u8 *t = D_800E7E80;

    switch (a[0x78]) {
    case 0:
        if (*(u16 *)(t + 0x17E) & 0x180) {
            return 1;
        }
        D_800BF81E = 0;
        t[4] = 4;
        t[5] = 0x21;
        t[6] = 0;
        t[7] = 0;
        D_1F80023C = *(s32 *)(t + 4);
        if (t[0x6F] == 0) {
            func_8004ED0C(0x10, 0);
        } else {
            func_8004EDDC(t[0x6F], 0x10);
        }
        t[0x6F] = 0x10;
        t[5] = 0x3A;
        t[6] = 0;
        a[0x78]++;
        break;
    case 1:
        if (t[5] == 0x21) {
            return 1;
        }
        break;
    }
    return 0;
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80125CA0);

s32 func_80125D68(void)
{
    u8 *t = D_800E7E80;
    s16 d, e;

    if (t[5] != 2) {
        return 0;
    }
    d = *(u16 *)(t + 0x2E) - 0x231C;
    if ((u16)(*(u16 *)(t + 0x80) + d) > *(s16 *)(t + 0x82) + 0x708) {
        return 0;
    }
    e = *(u16 *)(t + 0x36) - 0x22FB;
    return *(s16 *)(t + 0x82) + 0xD48 >= (u16)(*(u16 *)(t + 0x80) + e);
}

void func_80125DD8(u8 *p, s32 a1)
{
    SV v;

    if ((u16)(*(u16 *)(p + 0x36) - 0x2560) < 0x87F) {
        if (a1) {
            v.a = *(s16 *)(p + 0x2E);
        } else {
            v.a = 0x25B2;
        }
        v.b = -0xA00;
        v.c = *(s16 *)(p + 0x36);
        func_8002AE0C(&v, 0x60, 1);
    }
}

/* func_80126DEC, inlined */
static inline s32 func_80126DEC_inl(u8 *a)
{
    s32 z = (-func_80083E80(*(s16 *)(a + 0x56)) * *(s16 *)(a + 0x80)) >> 12;
    s32 x = func_80083F50(*(s16 *)(a + 0x56)) * *(s16 *)(a + 0x80);
    AreaSVec *v = &D_1F8000C0_f4ad;
    D_1F8000C0_f4ad.x = x >> 12;
    v->y = *(s16 *)(a + 0x86) - *(s16 *)(a + 0x84);
    v->z = z;
    return func_8012EE08(a + 0x2C, v, 0) != 0;
}
s32 func_80125E40(u8 *a, s32 f)
{
    s32 x = (func_80083F50(*(s16 *)(a + 0x56)) * *(s16 *)(a + 0x44)) >> 4;
    s32 z = func_80083E80(*(s16 *)(a + 0x56)) * *(s16 *)(a + 0x44);
    *(s32 *)(a + 0x2C) += x;
    *(s32 *)(a + 0x34) -= z >> 4;
    if (f == 0) {
        return 0;
    }
    return func_80126DEC_inl(a);
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80125F40);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80126188);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80126270);

INCLUDE_ASM("asm/a07/nonmatchings/a07", f_UpdateCircusPaonAtWellActor);

extern u8 D_80131BC0[];
extern u8 D_80140DC8[];
void func_80126BD8(u8 *a)
{
    u8 *g;

    switch (a[4]) {
    case 0:
        g = D_800ECF58;
        if (func_800519E0(a, 0xA, *(s32 *)(g + 0x74), D_80131BC0) != 0) {
            break;
        }
        *(s32 *)(a + 0x3C) = *(s32 *)(g + 0x78);
        func_80040CDC(a, D_80140DC8, D_800A3D18_ed09);
        a[0x7B] = 0;
        func_80041768(a, 0, 0);
        a[0] = 3;
        *(s16 *)(a + 0x80) = 0x120;
        *(s16 *)(a + 0x82) = 0x240;
        *(s16 *)(a + 0x84) = 0x180;
        *(s16 *)(a + 0x86) = 0x190;
        a[0xB] = 0;
        if (D_800BF9D7 != 3) {
            a[0x5E] = 0;
        } else {
            a[0x5E] = 1;
        }
        *(s16 *)(a + 0x68) = 0x80;
        a[4]++;
        break;
    case 1:
        switch (a[0x5E]) {
        case 0:
            func_80126270(a);
            break;
        case 1:
            f_UpdateCircusPaonAtWellActor(a);
            break;
        }
        if (a[1] != 0) {
            func_800518FC(a);
            func_801150DC(a);
        }
        break;
    case 2:
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

void func_80126D6C(void *arg0) {
    if (M2C_FIELD(M2C_FIELD(arg0, void **, 0x38), u16 *, 2) == 0) {
        func_80074590(0x82, 0, 0);
        func_800521F4(0, 0, 0xF1, 2);
        M2C_FIELD(arg0, s16 *, 0x68) = 0x80;
    }
}

s32 func_80126DCC(void) {
    return (u32) ((*(u16 *)0x1F800162 + 0xCA8) & 0xFFFF) >= 0x439U;
}

s32 func_80126DEC(u8 *a)
{
    s32 z = (-func_80083E80(*(s16 *)(a + 0x56)) * *(s16 *)(a + 0x80)) >> 12;
    s32 x = func_80083F50(*(s16 *)(a + 0x56)) * *(s16 *)(a + 0x80);
    AreaSVec *v = &D_1F8000C0_f4ad;
    D_1F8000C0_f4ad.x = x >> 12;
    v->y = *(s16 *)(a + 0x86) - *(s16 *)(a + 0x84);
    v->z = z;
    return func_8012EE08(a + 0x2C, v, 0) != 0;
}

extern s16 D_800E7FFE_1cd3;
extern s16 D_1F800162;
s32 func_80126E80(u8 *a)
{
    if (!(D_800E7FFE_1cd3 & 0x8200)) {
        if (D_1F800162 >= -0xABD) {
            s16 dx = D_1F800160 - *(s16 *)(a + 0x2E);
            s16 dz = D_1F800164 - *(s16 *)(a + 0x36);
            if (func_80084080(dx * dx + dz * dz) < 0x384) {
                return 1;
            }
        }
    }
    return 0;
}

s32 func_80126F1C(u8 *p)
{
    switch (p[0x78]) {
    case 0:
        D_800BF860_c64f = p;
        D_800BFA2C = 0xF;
        p[0x78]++;
        goto end;
    case 1:
        if (D_800BFA2C == 0x11) {
            return 1;
        }
    end:
    default:
        return 0;
    }
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80126F84);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_801271BC);

void func_80126F84();
s32 func_80127358(u8 *a, s32 b)
{
    u8 *p = func_80072DDC(a, 0, 2, 0x56);

    if (p != NULL) {
        *(void **)(p + 0x1C) = func_80126F84;
        p[0x28] |= 0x80;
        *(s16 *)(p + 0x2E) = *(s16 *)(*(u8 **)(a + 0xD0) + 0x2C);
        *(s16 *)(p + 0x32) = *(s16 *)(*(u8 **)(a + 0xD0) + 0x30);
        *(s16 *)(p + 0x36) = *(s16 *)(*(u8 **)(a + 0xD0) + 0x34);
        p[3] = b;
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_801273F8);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_801274C8);

extern u8 D_80131A50[];
extern u8 D_80134E04[];
s32 func_80130BA4(u8 *a);
s32 func_80130CB0(void *a0);
void func_80127690(u8 *a)
{
    u8 *g;

    switch (a[4]) {
    case 0:
        g = D_800ECF58;
        if (func_800519E0(a, 0xF, *(s32 *)(g + 0x70), D_80131A50) != 0) {
            break;
        }
        *(s32 *)(a + 0x3C) = *(s32 *)(g + 0x38);
        func_80040CDC(a, D_8014005C_9175, D_800A3D18_ed09);
        a[0xB] = 0x40;
        a[0] = 9;
        *(s16 *)(a + 0x80) = 0x80;
        *(s16 *)(a + 0x82) = 0x100;
        *(s16 *)(a + 0x84) = 0xC0;
        *(s16 *)(a + 0x86) = 0x17A;
        a[3] = 1;
        if (D_800BF9D5 == 0) {
            a[0x5E] = 0;
        } else {
            a[0x5E] = 1;
        }
        func_80130BA4(a);
        *(s16 *)(a + 0x58) = 0;
        *(s16 *)(a + 0x56) = 0;
        *(s16 *)(a + 0x54) = 0;
        a[0x7B] = 0x35;
        func_80041718(a, 0x35, 0);
        a[0x2B] = 0;
        a[4]++;
        break;
    case 1:
        switch (a[0x5E]) {
        case 0:
            if (D_800BF9D5 == 3) {
                a[5] = 0;
                a[0x5E] = 1;
                break;
            }
            switch (a[5]) {
            case 0:
                if (func_80130CB0(a) != 0 && a[0x2B] == 3) {
                    func_80042354(1, 1);
                    func_80040D68(a, D_80134E04);
                    a[0x70] = 2;
                    a[5]++;
                }
                break;
            case 1:
                a[1] = 1;
                func_80077E7C(a);
                func_8004190C(a);
                if (a[0x70] == 0xFF) {
                    a[5] = 0;
                    a[0x5E] = 1;
                    a[3] = 1;
                }
                func_80041098(a);
                break;
            }
            break;
        case 1:
            func_801274C8(a);
            break;
        }
        a[0x2B] = 0;
        if (a[1] != 0) {
            func_800518FC(a);
        }
        break;
    case 2:
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

extern u8 D_800BFA45;
s32 func_801278F8(void)
{
    if (D_800BFA45 & 2) {
        return 3;
    }
    return 2;
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8012791C);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80127B20);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80127CC0);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80127EB8);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_801281C4);

extern u8 D_801319D8[];
void func_801283C0(u8 *a)
{
    u8 *g;
    u8 *st;

    switch (a[4]) {
    case 0:
        g = D_800ECF58;
        if (func_800519E0(a, 0xF, *(s32 *)(g + 0x88), D_801319D8) != 0) {
            break;
        }
        *(s32 *)(a + 0x3C) = *(s32 *)(g + 0x38);
        func_80040CDC(a, D_8014005C_9175, D_800A3D18_ed09);
        a[0xB] = 0x40;
        *(s16 *)(a + 0x80) = 0x80;
        *(s16 *)(a + 0x82) = 0x100;
        *(s16 *)(a + 0x84) = 0xA0;
        *(s16 *)(a + 0x86) = 0x111;
        st = (u8 *)&D_800BF870;
        *(s16 *)(a + 0x58) = 0;
        *(s16 *)(a + 0x54) = 0;
        if (st[0x6A] != 0xFF) {
            a[0x5E] = 0;
        } else if (st[0x69] != 0xFF) {
            a[0x5E] = 1;
        } else {
            a[0x5E] = 2;
        }
        a[0x2B] = 0;
        a[4]++;
        break;
    case 1:
        switch (a[0x5E]) {
        case 0:
            func_8012791C(a);
            break;
        case 1:
            func_80127B20(a);
            break;
        case 2:
            func_80127CC0(a);
            break;
        case 3:
            func_80127EB8(a);
            break;
        case 4:
            func_801281C4(a);
            break;
        }
        if (a[1] != 0) {
            func_800518FC(a);
        }
        a[0x2B] = 0;
        break;
    case 2:
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80128594);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80128798);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80128980);

extern u8 D_80131AC8[];
void func_80128BAC(u8 *a)
{
    u8 *g;
    u8 *st;

    switch (a[4]) {
    case 0:
        g = D_800ECF58;
        if (func_800519E0(a, 0x10, *(s32 *)(g + 0x54), D_80131AC8) != 0) {
            break;
        }
        func_80051B04(*(u8 **)(a + ((a[9] - 1) << 2) + 0xC0), 0x15, 0xF);
        *(s32 *)(a + 0x3C) = *(s32 *)(g + 0x38);
        func_80040CDC(a, D_8014005C_9175, D_800A3D18_ed09);
        a[0xB] = 0x40;
        *(s16 *)(a + 0x80) = 0x90;
        *(s16 *)(a + 0x82) = 0x120;
        *(s16 *)(a + 0x84) = 0xC0;
        *(s16 *)(a + 0x86) = 0x120;
        *(s16 *)(a + 0x58) = 0;
        *(s16 *)(a + 0x54) = 0;
        a[0x7B] = 0x22;
        func_80041718(a, 0x22, 0);
        st = (u8 *)&D_800BF870;
        if (st[0x6A] != 0xFF) {
            a[0x5E] = 0;
        } else if (st[0x69] != 0xFF) {
            a[0x5E] = 1;
        } else {
            a[0x5E] = 2;
        }
        a[0x2B] = 0;
        a[4]++;
        break;
    case 1:
        switch (a[0x5E]) {
        case 0:
            func_80128594(a);
            break;
        case 1:
            func_80128798(a);
            break;
        case 2:
            func_80128980(a);
            break;
        }
        if (a[1] != 0) {
            func_800518FC(a);
        }
        a[0x2B] = 0;
        break;
    case 2:
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

s32 func_80128DA0(u8 *p)
{
    if (*(s16 *)(p + 0x72) & 0x8000) {
        *(s32 *)(p + 0x3C) = D_800ECF68;
        *(void **)(p + 0x7C) = D_80017FE8;
    } else {
        *(s32 *)(p + 0x3C) = D_800ECF90;
        *(void **)(p + 0x7C) = D_8014005C_9175;
    }
    func_80041718(p, *(u16 *)(p + 0x72) & 0x7FFF, 0);
    return 1;
}

void func_80128E04(void) {
    s32 sp10;

    func_80036560(5, &sp10);
    func_80078894(sp10);
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80128E34);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80129170);

s32 func_80129360(u8 *a)
{
    switch (a[0x78]) {
    case 0:
        func_800440E4(D_800E7E80, 0xCF, 2);
        *(u8 **)(a + 0x14) = func_80117344(a, 1);
        a[0x78]++;
        break;
    case 1:
        if (D_800BF80E != 0) {
            func_80041718(a, 0x12, 4);
            a[0x78]++;
        }
        break;
    case 2:
        if ((*(u8 **)(a + 0x38))[4] != 0) {
            func_8004D650(0x34, 1);
            func_8004ED0C(0x34, 4);
            (*(u8 **)(a + 0x14))[0x5E] = 2;
            func_800440E4(D_800E7E80, 2, 4);
            a[0x78]++;
        }
        break;
    case 3:
        if (a[0x79] != 1) {
            return 0;
        }
        func_80041718(a, 0x24, 4);
        a[0x78]++;
        break;
    case 4:
        if (!(D_800BF822 & 1)) {
            return 1;
        }
        break;
    }
    return 0;
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_801294A4);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_801296AC);

void func_80129900(u8 *a)
{
    u8 *g;
    u8 *st;
    u8 v;
    s32 k;

    switch (a[4]) {
    case 0:
        st = (u8 *)&D_800BF870;
        v = st[0x69];
        if (v != 0xFF) {
            break;
        }
        g = D_800ECF58;
        if (func_800519E0(a, 0x10, *(s32 *)(g + 0x54), D_80131AC8) != 0) {
            break;
        }
        func_80051B04(*(u8 **)(a + ((a[9] - 1) << 2) + 0xC0), 0x15, 0xF);
        *(s32 *)(a + 0x3C) = *(s32 *)(g + 0x38);
        func_80040CDC(a, D_8014005C_9175, D_800A3D18_ed09);
        a[0xB] = 0x40;
        a[0] = 9;
        *(s16 *)(a + 0x80) = 0x90;
        *(s16 *)(a + 0x82) = 0x120;
        *(s16 *)(a + 0x84) = 0xC0;
        *(s16 *)(a + 0x86) = 0x120;
        *(s16 *)(a + 0x58) = 0;
        *(s16 *)(a + 0x54) = 0;
        a[0x7B] = 0x22;
        func_80041718(a, 0x22, 0);
        if (st[0x6C] == 0) {
            a[0x5E] = 0;
        } else {
            if (st[0x6C] == v) {
                k = 3;
            } else if (st[0x6B] == v) {
                k = 2;
            } else {
                a[0x5E] = 1;
                goto done;
            }
            a[0x5E] = k;
        }
    done:
        a[0x2B] = 0;
        a[4]++;
        break;
    case 1:
        switch (a[0x5E]) {
        case 0:
            func_80128E34(a);
            break;
        case 1:
            func_80129170(a);
            break;
        case 2:
            func_801294A4(a);
            break;
        case 3:
            func_801296AC(a);
            break;
        }
        if (a[1] != 0) {
            func_800518FC(a);
        }
        a[0x2B] = 0;
        break;
    case 2:
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

extern s8 D_1F800214[];
s32 func_80129B38(void) {
    func_8004BEC4();
    func_801178E4(*((s32 *)D_1F800214));
    return 1;
}

s32 func_80129B68(u8 *a) {
    switch (a[0x78]) {
    case 0:
        func_80041718(a, 0x2E, 4);
        M2C_FIELD(a, u8 **, 0x14)[5] = 1;
        a[0x78]++;
        break;
    case 1:
        if (M2C_FIELD(a, u8 **, 0x14)[5] == 2) {
            return 1;
        }
        break;
    }
    return 0;
}

extern void *D_800BF860;
s32 func_80129BF4(void *arg0) {
    M2C_FIELD(arg0, s16 *, 0x40) = 1;
    D_800BF860 = arg0;
    return 1;
}

s32 func_80129C0C(void *arg0) {
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x14), s8 *, 4) = 3;
    return 1;
}

extern u8 D_80131B48[];
extern u8 D_801359FC[];
extern u8 D_80135A24[];
extern u8 D_800E8008[];
extern s16 D_800E7ED6;
void func_80129C20(u8 *a)
{
    u8 *g;
    u8 *e = D_800E8008;

    switch (a[4]) {
    case 0:
        g = D_800ECF58;
        if (func_800519E0(a, 0xF, *(s32 *)(g + 0x94), D_80131B48) != 0) {
            break;
        }
        *(s32 *)(a + 0x3C) = *(s32 *)(g + 0x38);
        func_80040CDC(a, D_8014005C_9175, D_801359FC);
        func_80041718(a, 0x15, 0);
        *(s16 *)(a + 0x56) = 0x140;
        a[0xB] = 0x40;
        a[0] = 9;
        *(s16 *)(a + 0x80) = 0xBE;
        *(s16 *)(a + 0x82) = 0x17C;
        *(s16 *)(a + 0x84) = 0x8C;
        *(s16 *)(a + 0x86) = 0x104;
        a[0x70] = 1;
        a[0x2B] = 0;
        a[0x5E] = 0;
        *(s16 *)(a + 0x54) = 0;
        *(s16 *)(a + 0x56) = 0x800;
        *(s16 *)(a + 0x58) = 0;
        a[4]++;
        break;
    case 1:
        a[1] = 1;
        func_80077E7C(a);
        func_80041098(a);
        switch (a[5]) {
        case 0:
            if (a[0x2B] == 3) {
                a[0] = 2;
                func_80040D68(a, D_80135A24);
                a[5] = 1;
                a[6] = 0;
                a[0x70] = 1;
            }
            break;
        case 1:
            if (a[0x71] == 0xFF) {
                a[4] = 2;
            }
            if (a[0x5E] != 0) {
                func_8004190C(a);
            }
            switch (a[6]) {
            case 1:
                e[0x64] = 8;
                a[6]++;
                break;
            case 2:
                func_8006CBA8(a + 0x2C);
                D_800E7ED6 = func_80085690(D_1F800164 - *(s16 *)(a + 0x36), *(s16 *)(a + 0x2E) - D_1F800160) & 0xFFF;
                break;
            }
            break;
        }
        a[0x2B] = 0;
        func_800518FC(a);
        break;
    case 2:
        a[4] = 3;
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

s32 func_80129E88(s32 arg0) {
    s32 var_s0;

    var_s0 = 0;
    do {
        func_8004190C(arg0);
        var_s0 += 1;
    } while (var_s0 < 4);
    func_800518FC(arg0);
    return 1;
}

s32 func_80129ED8(void *arg0) {
    M2C_FIELD(arg0, s8 *, 0x5E) = 1;
    return 1;
}

s32 func_80129EE8(void)
{
    u8 *a = D_800BF844;
    u8 *b = *(u8 **)(a + 0xC0);

    a[0xD] |= 4;
    b[0x3F] = 0xED;
    *(s16 *)(a + 0x62) = 0x10;
    return 1;
}

s32 func_80129F1C(void *arg0) {
    M2C_FIELD(arg0, u8 *, 6) = (u8) (M2C_FIELD(arg0, u8 *, 6) + 1);
    return 1;
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80129F34);

void func_8012A894(u8 *a);
void func_8012A8F0(void *arg0);
void f_UpdateCircusIceCandyAndTinyPigActor(u8 *a)
{
    u8 *st;
    u8 c;
    s32 r;

    switch (a[4]) {
    case 0:
        func_80120004(a);
        if (!(D_800BFE56 & 0x80)) {
            r = func_800519E0(a, 0xF, D_800ECFB0, D_80131618);
        } else {
            a[0xB] = 0x40;
            *(s16 *)(a + 0x80) = 0xC0;
            *(s16 *)(a + 0x82) = 0x180;
            *(s16 *)(a + 0x32) -= 0x19;
            r = func_800519E0(a, 0xF, D_800ECFB0, D_80131690);
        }
        if (r != 0) {
            break;
        }
        *(s16 *)(a + 0x56) = 0xC80;
        func_80040CDC(a, D_8014005C_9175, D_800A3CD0);
        func_80041718(a, 0x17, 0);
        *(s16 *)(a + 0x60) = -1;
        *(s16 *)(a + 0x62) = 0;
        st = (u8 *)&D_800BF870;
        c = st[0xC5];
        if (c == 0xFF) {
            if (st[0x2BA] != 0) {
                a[0x5E] = 4;
                if (st[0x2BA] >= 10) {
                    *(s16 *)(a + 0x62) = 1;
                }
            } else if (st[0xC6] == 0xFF) {
                a[0x5E] = 7;
                *(s16 *)(a + 0x40) = 0;
            } else if (st[0x1BF] == 0) {
                a[0x5E] = 5;
            } else {
                a[0x5E] = 6;
            }
        } else if (c & 2) {
            if (st[0x2BA] != 0) {
                a[0x5E] = 2;
                *(s16 *)(a + 0x62) = 1;
            } else if (st[0x1BA] == 0) {
                a[0x5E] = 1;
            } else {
                a[0x5E] = 3;
            }
        } else {
            a[0x5E] = 0;
            if (st[0x2BA] != 0) {
                *(s16 *)(a + 0x62) = 1;
            }
        }
        a[4]++;
        break;
    case 1:
        a[1] = 1;
        func_80077E7C(a);
        func_80041098(a);
        func_8004190C(a);
        switch (a[5]) {
        case 0:
            if (a[0x5E] == 7) {
                f_UpdatePigBallItemInteraction(a);
            } else {
                func_8012A7A4(a);
            }
            break;
        case 1:
            func_8012A894(a);
            break;
        case 2:
            f_UpdateIceCandyAndTinyPigRewardSequence(a);
            break;
        case 3:
            func_8012A8F0(a);
            break;
        }
        func_800518FC(a);
        a[0x2B] = 0;
        break;
    case 2:
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", f_UpdatePigBallItemInteraction);

INCLUDE_ASM("asm/a07/nonmatchings/a07", f_UpdateIceCandyAndTinyPigRewardSequence);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8012A7A4);

extern void *D_80136154[];
void func_8012A894(u8 *a)
{
    if (a[0x71] == 0xFF) {
        func_80040D68(a, D_80136154[a[0x5E]]);
        a[0x70] = 1;
        a[5] = 2;
    }
}

void func_8012A8F0(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x71) == 0xFF) {
        M2C_FIELD(arg0, s8 *, 5) = 0;
    }
}

s32 func_8012A90C(void *arg0) {
    if (M2C_FIELD(arg0, s16 *, 0x62) != 0) {
        M2C_FIELD(arg0, s16 *, 0x62) = 0;
        return 3;
    }
    return 2;
}

s32 func_8012A930(u8 *p)
{
    u8 *g = (u8 *)&D_800BF870;

    if (g[0x2BA] != 0) {
        g[0xC5] |= 2;
        p[0x5E] = 3;
        return 3;
    }
    return 2;
}

s32 func_8012A96C(u8 *a)
{
    u8 *g = (u8 *)&D_800BF870;

    g[0x1BA] += 1 + g[0x2BA];
    func_8004D650(0x76, g[0x2BA]);
    if (g[0x1BA] >= 0x1E) {
        a[0x5E] = 4;
        return 3;
    }
    return 2;
}

extern u8 D_800BFB2A;
s32 func_8012A9DC(void)
{
    if (D_800BFB2A < 10) {
        return 3;
    }
    func_8004D650(0x76, 10);
    func_8004ED94(0x5D, 0x41);
    return 2;
}

s32 func_8012AA28(u8 *p)
{
    u8 *g = (u8 *)&D_800BF870;

    if (++g[0x1BF] == 5) {
        p[0] = 2;
        p[0x5F] = 0;
        p[0x5E] = 9;
        p[6] = 0;
        return 3;
    }
    return 2;
}

void func_8012C60C();
s32 func_8012AA74(u8 *p)
{
    u8 *s = D_800BF808;
    s32 v = s[3];

    if (v < 0x45) {
        if (v >= 0x40) {
            *(s16 *)(p + 0x60) = s[3];
            if (f_CompleteUseTheSeesawEventIfResolved()) {
                p[0x5E] = 8;
            }
            return 1;
        }
    }
    *(s16 *)(p + 0x60) = -1;
    return 0;
}

s32 func_8012AAE4(void *arg0) {
    s16 temp_a0;
    s32 var_v0;

    temp_a0 = M2C_FIELD(arg0, s16 *, 0x60);
    var_v0 = 2;
    if (temp_a0 != -1) {
        func_8004D4F4(temp_a0, 1);
        M2C_FIELD(arg0, s16 *, 0x60) = -1;
        var_v0 = 3;
    }
    return var_v0;
}

s32 func_8012AB2C(void *arg0) {
    M2C_FIELD(arg0, u8 *, 6) = (u8) (M2C_FIELD(arg0, u8 *, 6) + 1);
    return 1;
}

s32 func_8012AB44(void *arg0) {
    return M2C_FIELD(arg0, u8 *, 0xBF) == M2C_FIELD(arg0, s16 *, 0x72);
}

s32 func_8012AB5C(void)
{
    u8 *g = (u8 *)&D_800BF870;

    if (g[0x1BF] == 5) {
        g[0x1BF]++;
        return 3;
    }
    return 2;
}

#define S32(o) (*(s32 *)(a + (o)))
void func_8012AB88(u8 *a, void *b) {
    switch (a[5]) {
    case 0:
        I16(0x4A) = -0x2800;
        a[5] = 1;
        I16(0x50) = 0x200;
        func_8004B354(a, b);
        a[0xB] = 0x10;
        break;
    case 1:
        S32(0x30) += I16(0x4A) << 8;
        W16(0x4A) += W16(0x50);
        if (I16(0x4A) > 0) {
            a[0] = 1;
            a[5]++;
        }
        break;
    case 2:
        S32(0x30) += I16(0x4A) << 8;
        if (I16(0x4A) < 0x3000) {
            W16(0x4A) += W16(0x50);
        }
        if (a[0x29] == 0 && f_TestCircusActorGroundContact(a) == 0) {
            break;
        }
        I16(0x4A) = 0;
        a[5]++;
        break;
    }
    func_8004B374(a, b);
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8012ACC0);

INCLUDE_ASM("asm/a07/nonmatchings/a07", f_UpdateTriangleGearRewardPresentation);

INCLUDE_ASM("asm/a07/nonmatchings/a07", f_UpdateEarthPigBagRewardPresentation);

extern u8 D_800BFA29;
void func_8012B1B4(u8 *a)
{
    switch (a[4]) {
    case 0:
        switch (a[3]) {
        case 0:
            func_8012ACC0(a);
            break;
        case 1:
            if (func_80051B70(a, 0xC, 0x1F) != 0) {
                break;
            }
            *(s16 *)(a + 0x80) = 0x64;
            *(s16 *)(a + 0x82) = 0xC8;
            *(s16 *)(a + 0x86) = 0xC8;
            *(s16 *)(a + 0x84) = 0x64;
            *(s16 *)(a + 0x58) = 0;
            *(s16 *)(a + 0x56) = 0;
            *(s16 *)(a + 0x54) = 0;
            if (D_800BFA29 >= 0xA) {
                a[5] = 0xA;
                a[0] = 1;
                *(s16 *)(a + 0x56) = 0x800;
                a[0x28] |= 0x80;
            } else {
                *(s16 *)(a + 0x56) = 0x9C4;
                a[0] = 2;
                *(s16 *)(a + 0x2E) = 0x1568;
                *(s16 *)(a + 0x32) = -0x101A;
                *(s16 *)(a + 0x36) = 0x34B2;
                a[5] = 0;
            }
            *(s16 *)(a + 0x68) = 0x1A;
            break;
        }
        a[4]++;
        break;
    case 1:
        switch (a[3]) {
        case 0:
            f_UpdateTriangleGearRewardPresentation(a);
            break;
        case 1:
            f_UpdateEarthPigBagRewardPresentation(a);
            break;
        }
        break;
    case 2:
        switch (a[3]) {
        case 0:
            D_800BF9D6 = 0xA;
            func_80040C00(0x24);
            func_8004A3D4(a);
            a[4] = 3;
            break;
        case 1:
            switch (a[6]) {
            case 0:
                a[6] = 1;
                func_80040B48(0x29);
                D_800BFA29 = 0xB;
                func_8004A3D4(a);
                D_1F800137 = 2;
                break;
            case 1:
                if (func_80042728()) {
                    D_1F800137 = 0;
                    a[4] = 3;
                }
                break;
            }
            break;
        }
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

void func_8012B1B4();
u8 *func_8012B3FC(void *a0)
{
    u8 *r = func_80072DDC(a0, 0, 5, 3);

    if (r == 0) {
        return 0;
    }
    r[3] = 0;
    *(void **)(r + 0x1C) = func_8012B1B4;
    *(void **)(r + 0x10) = a0;
    return r;
}

u8 *func_8012B44C(void)
{
    u8 *r = func_80072DDC(0, 1, 5, 3);

    if (r == 0) {
        return 0;
    }
    r[3] = 1;
    *(void **)(r + 0x1C) = func_8012B1B4;
    *(void **)(r + 0x10) = 0;
    return r;
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", f_UpdateCircusThrownQuestObject);

typedef struct { s32 x, y, z; } V3w;
s32 f_TestCircusActorForwardCollision(u8 *a);
void f_UpdateCircusClosetKeyActor(u8 *a)
{
    u8 *p;
    u8 *p_f;

    switch (a[4]) {
    case 0:
        func_80051B70(a, 0xC, 0x27);
        a[0xD] = 0;
        a[0xB] = 0;
        *(s16 *)(a + 0x80) = 0x64;
        *(s16 *)(a + 0x82) = 0xC8;
        *(s16 *)(a + 0x84) = 0x64;
        *(s16 *)(a + 0x86) = 0xC8;
        *(s16 *)(a + 0x58) = 0;
        *(s16 *)(a + 0x56) = 0;
        *(s16 *)(a + 0x54) = 0;
        switch (a[3]) {
        case 0:
            a[0] = 1;
            a[0x5E] = 1;
            break;
        case 1:
            a[0] = 2;
            a[0x5E] = 0;
            break;
        case 3:
            a[0] = 2;
            a[0x5E] = 3;
            break;
        }
        a[3] = 0;
        a[4]++;
        break;
    case 1:
        if (D_800BF816 != 0) {
            if (a[0x5E] == 3) {
                break;
            }
            if (D_800BFA45 & 1) {
                a[4] = 3;
                break;
            }
            if (a[0x5E] == 1) {
                *(s16 *)(a + 0x2E) = 0x2040;
                *(s16 *)(a + 0x32) = -0xA64;
                *(s16 *)(a + 0x36) = 0x1C69;
                a[6] = 0;
                a[5] = 0;
            }
            break;
        }
        switch (a[0x5E]) {
        case 0:
            if (D_800BF8D8 != 0) {
                a[0] = 1;
                *(s16 *)(a + 0x56) = 0;
                *(s16 *)(*(u8 **)(a + 0xC0) + 0xC) = 0;
                a[0x5E] = 1;
                a[6] = 0;
                a[5] = 0;
                break;
            }
            p = *(u8 **)(a + 0x10);
            if ((a[1] = p[1]) != 0) {
                func_80077EFC(a);
            }
            *(V3w *)(a + 0x2C) = *(V3w *)(p + 0x2C);
            *(s16 *)(a + 0x32) += 0xCC;
            *(s16 *)(a + 0x56) = *(s16 *)(p + 0x56);
            *(s16 *)(*(u8 **)(a + 0xC0) + 0xC) += *(s16 *)(p + 0x44) >> 5;
            break;
        case 1:
            func_8007778C(a);
            f_TestCircusActorForwardCollision(a);
            break;
        case 2:
            f_UpdateCircusThrownQuestObject(a);
            break;
        case 3:
            p_f = *(u8 **)(a + 0x10);
            if ((a[1] = p_f[1]) != 0) {
                func_80077EFC(a);
            }
            *(V3w *)(a + 0x2C) = *(V3w *)(p_f + 0x2C);
            *(s16 *)(a + 0x32) += 0xF5;
            *(s16 *)(a + 0x56) = *(s16 *)(p_f + 0x56);
            *(s16 *)(*(u8 **)(a + 0xC0) + 0xC) += *(s16 *)(p_f + 0x44) >> 5;
            break;
        }
        if (a[1] != 0) {
            func_800517F8(a);
        }
        break;
    case 2:
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

u8 *func_8012C104(void *a0, u8 a1)
{
    u8 *r = func_80072DDC(a0, 1, 5, 5);

    if (r == 0) {
        return 0;
    }
    r[3] = a1;
    *(void **)(r + 0x1C) = f_UpdateCircusClosetKeyActor;
    *(void **)(r + 0x10) = a0;
    r[0x28] |= 0x80;
    return r;
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8012C16C);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8012C340);

extern u8 D_800BF8D9;
void func_8012C60C(u8 *a)
{
    switch (a[4]) {
    case 0:
        if (func_80051B70(a, 0xC, 0x28) != 0) {
            break;
        }
        *(s16 *)(a + 0x80) = 0x64;
        *(s16 *)(a + 0x82) = 0xC8;
        *(s16 *)(a + 0xE) = 0;
        a[0] = 1;
        *(s16 *)(a + 0x84) = 0x8C;
        *(s16 *)(a + 0x86) = 0x8C;
        *(s16 *)(a + 0x58) = 0;
        *(s16 *)(a + 0x56) = 0;
        *(s16 *)(a + 0x54) = 0;
        *(s16 *)(a + 0xE) = 0;
        a[4]++;
        break;
    case 1:
        if (D_800BF816 != 0) {
            if (a[0x5E] != 0) {
                break;
            }
            if (D_800BF8D9 == 0xFF) {
                a[4] = 3;
            } else {
                a[5] = 0;
            }
            break;
        }
        switch (a[0x5E]) {
        case 0:
            func_8012C16C(a);
            break;
        case 1:
            func_8012C340(a);
            break;
        }
        if (func_8007778C(a)) {
            func_80051844(a);
        }
        a[0x2B] = 0;
        break;
    case 2:
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

u8 *func_8012C770(void *a0, u8 a1)
{
    u8 *r = func_80072DDC(a0, 1, 5, 5);

    if (r == 0) {
        return 0;
    }
    r[3] = 1;
    r[0x5E] = a1;
    *(void **)(r + 0x1C) = func_8012C60C;
    *(void **)(r + 0x10) = a0;
    r[0x28] |= 0x80;
    return r;
}

typedef struct {
    u32 tag;
    u32 rgb0;
    u16 x0, y0;
    u32 uv0;
    u32 rgb1;
    u16 x1, y1;
    u32 uv1;
    u32 rgb2;
    u16 x2, y2;
    u16 uv2;
    u16 pad;
} T2PolyGT3;
#define T2_ldv3t(r0)                                                                                                   \
    __asm__ volatile("lwc2 $0, 0x10(%0);"                                                                              \
                     "lw $12, 0x14(%0);"                                                                               \
                     "lwc2 $2, 0x18(%0);"                                                                              \
                     "mtc2 $12, $1;"                                                                                   \
                     "lwc2 $4, 0x1C(%0);"                                                                              \
                     "srl $12, $12, 16;"                                                                               \
                     "mtc2 $12, $3;"                                                                                   \
                     "lwc2 $5, 0x20(%0)"                                                                               \
                     :                                                                                                 \
                     : "r"(r0)                                                                                         \
                     : "$12")
#define T2_rtpt() __asm__ volatile(".word 0x4A280030")
#define T2_nclip() __asm__ volatile(".word 0x4B400006")
#define T2_avsz3() __asm__ volatile(".word 0x4B58002D")
#define T2_stflg(r0) __asm__ volatile("cfc2 $12, $31;" "nop;" "sw $12, 0( %0 )" : : "r"(r0) : "$12", "memory")
#define T2_stopz(r0) __asm__ volatile("swc2 $24, 0( %0 )" : : "r"(r0) : "memory")
#define T2_stotz(r0) __asm__ volatile("swc2 $7, 0( %0 )" : : "r"(r0) : "memory")
#define T2_stsxy3_gt3(r0)                                                                                              \
    __asm__ volatile("swc2 $12, 8( %0 );" "swc2 $13, 20( %0 );" "swc2 $14, 32( %0 )" : : "r"(r0) : "memory")
#define T2_stsz1(r0) __asm__ volatile("swc2 $17, 0( %0 )" : : "r"(r0) : "memory")
#define T2_stsz2(r0) __asm__ volatile("swc2 $18, 0( %0 )" : : "r"(r0) : "memory")
#define T2_stsz3(r0) __asm__ volatile("swc2 $19, 0( %0 )" : : "r"(r0) : "memory")
extern void *D_800BF544;
typedef struct {
    u32 tag;
    u32 rgb0;
    u16 x0, y0;
    u32 uv0;
    u32 rgb1;
    u16 x1, y1;
    u32 uv1;
    u32 rgb2;
    u16 x2, y2;
    u32 uv2;
    u32 rgb3;
    u16 x3, y3;
    u32 uv3;
} T2PolyGT4;
#define T2_ldv3p(r0)                                                                                                   \
    __asm__ volatile("lw $12, 0x18(%0);"                                                                               \
                     "lwc2 $0, 0x14(%0);"                                                                              \
                     "mtc2 $12, $1;"                                                                                   \
                     "srl $12, $12, 16;"                                                                               \
                     "mtc2 $12, $3;"                                                                                   \
                     "lwc2 $2, 0x1C(%0);"                                                                              \
                     "lw $12, 0x24(%0);"                                                                               \
                     "lwc2 $4, 0x20(%0);"                                                                              \
                     "mtc2 $12, $5"                                                                                    \
                     :                                                                                                 \
                     : "r"(r0)                                                                                         \
                     : "$12")
#define T2_ldv1p(r0)                                                                                                   \
    __asm__ volatile("lw $12, 0x24(%0);"                                                                               \
                     "lwc2 $0, 0x28(%0);"                                                                              \
                     "srl $12, $12, 16;"                                                                               \
                     "mtc2 $12, $1"                                                                                    \
                     :                                                                                                 \
                     : "r"(r0)                                                                                         \
                     : "$12")
#define T2_rtps() __asm__ volatile(".word 0x4A180001")
#define T2_avsz4() __asm__ volatile(".word 0x4B68002E")
#define T2_stsxy(r0) __asm__ volatile("swc2 $14, 0( %0 )" : : "r"(r0) : "memory")
#define T2_stsxy3_gt4(r0)                                                                                              \
    __asm__ volatile("swc2 $12, 8( %0 );" "swc2 $13, 20( %0 );" "swc2 $14, 32( %0 )" : : "r"(r0) : "memory")
#define T2_stsz0(r0) __asm__ volatile("swc2 $16, 0( %0 )" : : "r"(r0) : "memory")
u32 *func_8012C7E0(u32 *f, u32 *ot, s32 n)
{
    s32 sz[6];
    s32 *otz = (s32 *)0x1F800004;
    T2PolyGT3 *p = D_800BF544;
    s32 *flg = (s32 *)0x1F800000;
    u32 c;
    u32 mode;
    s32 b, e;
    u32 *o;

    while (n-- != 0) {
        T2_ldv3t(f);
        p->rgb0 = f[0];
        T2_rtpt();
        p->uv0 = f[2];
        p->uv1 = f[3];
        c = f[1];
        T2_stflg(flg);
        if (*flg >= 0) {
            T2_nclip();
            p->rgb1 = c & 0xF0F0F0;
            T2_stopz(flg);
            if (*flg > 0) {
                T2_stsxy3_gt3(p);
                if ((p->x0 < 320 || p->x1 < 320 || p->x2 < 320) && (p->y0 < 240 || p->y1 < 240 || p->y2 < 240)) {
                    p->rgb2 = (c << 4) & 0xF0F0F0;
                    mode = (c >> 24) & 3;
                    switch (mode) {
                    case 1:
                        T2_stsz1(&sz[0]);
                        T2_stsz2(&sz[1]);
                        T2_stsz3(&sz[2]);
                        if (sz[0] > sz[1]) {
                            b = sz[2];
                            if (b < sz[0]) {
                                b = sz[0];
                            }
                            e = b;
                        } else {
                            b = sz[2];
                            if (b < sz[1]) {
                                b = sz[1];
                            }
                            e = b;
                        }
                        goto store;
                    case 2:
                        T2_stsz1(&sz[3]);
                        T2_stsz2(&sz[4]);
                        T2_stsz3(&sz[5]);
                        if (sz[3] > sz[4]) {
                            b = sz[5];
                            if (b < sz[3]) {
                                b = sz[3];
                            }
                            e = b;
                        } else {
                            b = sz[5];
                            if (b < sz[4]) {
                                b = sz[4];
                            }
                            e = b;
                        }
                    store:
                        *otz = e >> 2;
                        break;
                    default:
                        T2_avsz3();
                        T2_stotz(otz);
                        break;
                    }
                    e = *otz >> 10;
                    *otz = (*otz >> e) + (e << 9);
                    if ((u32)(*otz - 4) >= 0x7FC) {
                        *otz = -1;
                    }
                    if (*otz >= 0) {
                        p->uv2 = ((u16 *)f)[0x11];
                        do {
                            o = ot + *otz;
                            p->tag = *o | 0x09000000;
                            *o = (u32)p;
                        } while (0);
                        p++;
                    }
                }
            }
        }
        f += 9;
    }
    D_800BF544 = p;
    return f;
}

u32 *func_8012CAA8(u32 *f, u32 *ot, s32 n)
{
    s32 sz[8];
    s32 *otz = (s32 *)0x1F800004;
    T2PolyGT4 *p = D_800BF544;
    s32 *flg = (s32 *)0x1F800000;
    u32 c;
    u32 w;
    u32 mode;
    s32 b, a, v, e;
    u32 *o;

    while (n-- != 0) {
        T2_ldv3p(f);
        w = f[0];
        p->rgb0 = w & 0xFFF0F0F0;
        T2_rtpt();
        p->rgb1 = (w << 4) & 0xF0F0F0;
        c = f[1];
        T2_stflg(flg);
        if (*flg >= 0) {
            T2_nclip();
            p->uv0 = f[2];
            T2_stopz(flg);
            if (*flg > 0) {
                T2_stsxy3_gt4(p);
                T2_ldv1p(f);
                p->rgb2 = c & 0xF0F0F0;
                T2_rtps();
                p->rgb3 = (c << 4) & 0xF0F0F0;
                p->uv1 = f[3];
                T2_stflg(flg);
                if (*flg >= 0) {
                    T2_stsxy(&p->x3);
                    if ((p->x0 < 320 || p->x1 < 320 || p->x2 < 320 || p->x3 < 320) &&
                        (p->y0 < 240 || p->y1 < 240 || p->y2 < 240 || p->y3 < 240)) {
                        mode = (c >> 24) & 3;
                        switch (mode) {
                        case 1:
                            T2_stsz0(&sz[0]);
                            T2_stsz1(&sz[1]);
                            T2_stsz2(&sz[2]);
                            T2_stsz3(&sz[3]);
do {
                            a = sz[1];
                            if (a < sz[0]) {
                                a = sz[0];
                            }
                            b = sz[3];
                            if (b < sz[2]) {
                                b = sz[2];
                            }
                            if (b < a) {
                                b = a;
                            }
                            e = b;
} while (0);
                            goto store;
                        case 2:
                            T2_stsz0(&sz[4]);
                            T2_stsz1(&sz[5]);
                            T2_stsz2(&sz[6]);
                            T2_stsz3(&sz[7]);
do {
                            a = sz[5];
                            if (a < sz[4]) {
                                a = sz[4];
                            }
                            b = sz[7];
                            if (b < sz[6]) {
                                b = sz[6];
                            }
                            if (b < a) {
                                b = a;
                            }
                            e = b;
} while (0);
                        store:
                            *otz = e >> 2;
                            break;
                        default:
                            T2_avsz4();
                            T2_stotz(otz);
                            break;
                        }
do {
                        e = *otz >> 10;
                        *otz = (*otz >> e) + (e << 9);
} while (0);
                        if ((u32)(*otz - 4) >= 0x7FC) {
                            *otz = -1;
                        }
                        if (*otz >= 0) {
                            v = f[4];
                            p->uv2 = v;
                            p->uv3 = (u32)v >> 16;
                            do {
                                o = ot + *otz;
                                p->tag = *o | 0x0C000000;
                                *o = (u32)p;
                            } while (0);
                            p++;
                        }
                    }
                }
            }
        }
        f += 11;
    }
    D_800BF544 = p;
    return f;
}

extern s32 D_1F800084;
extern s32 D_1F800088;
extern s32 D_1F80008C_f832;
#define T2_lddp(r0) __asm__ volatile("mtc2 %0, $8" : : "r"(r0))
#define T2_ldrgb(r0) __asm__ volatile("mtc2 %0, $6" : : "r"(r0))
#define T2_dpcs() __asm__ volatile("nop; nop; .word 0x4A780010")
#define T2_strgb(r0) __asm__ volatile("swc2 $22, 0( %0 )" : : "r"(r0) : "memory")
u32 *func_8012CDF4(u32 *f, u32 *ot, s32 n, s32 dp)
{
    s32 rgb;
    T2PolyGT3 *p = D_800BF544;
    s32 *otz = (s32 *)0x1F800004;
    u32 c;
    u32 mode;
    s32 b;
    s32 d0, d1, d2;
    u32 *o;

    rgb = 0x34808080;
    T2_ldrgb(&rgb);
    while (n-- != 0) {
        T2_ldv3t(f);
        p->rgb0 = f[0];
        T2_rtpt();
        p->uv0 = f[2];
        p->uv1 = f[3];
        c = f[1];
        T2_stflg((s32 *)0x1F800000);
        if (*(s32 *)0x1F800000 >= 0) {
            T2_nclip();
            p->rgb1 = c & 0xF0F0F0;
            T2_stopz((s32 *)0x1F800000);
            if (*(s32 *)0x1F800000 > 0) {
                T2_stsxy3_gt3(p);
                if ((p->x0 < 320 || p->x1 < 320 || p->x2 < 320) && (p->y0 < 240 || p->y1 < 240 || p->y2 < 240)) {
                    __asm__ volatile("nop");
                    p->rgb2 = (c << 4) & 0xF0F0F0;
                    T2_stsz1(&D_1F800084);
                    T2_stsz2(&D_1F800088);
                    T2_stsz3(&D_1F80008C_f832);
                    mode = (c >> 24) & 3;
                    switch (mode) {
                    case 1:
                    case 3:
                        if (D_1F800084 > D_1F800088) {
                            b = D_1F80008C_f832;
                            if (b < D_1F800084) {
                                b = D_1F800084;
                            }
                            *otz = b >> 2;
                        } else {
                            b = D_1F80008C_f832;
                            if (b < D_1F800088) {
                                b = D_1F800088;
                            }
                            *otz = b >> 2;
                        }
                        break;
                    case 2:
                        if (D_1F800084 < D_1F800088) {
                            b = D_1F80008C_f832;
                            if (D_1F800084 < b) {
                                b = D_1F800084;
                            }
                            *otz = b >> 2;
                        } else {
                            b = D_1F80008C_f832;
                            if (D_1F800088 < b) {
                                b = D_1F800088;
                            }
                            *otz = b >> 2;
                        }
                        break;
                    default:
                        T2_avsz3();
                        T2_stotz(otz);
                        break;
                    }
                    b = *otz >> 10;
                    *otz = (*otz >> b) + (b << 9);
                    if ((u32)(*otz - 4) >= 0x7FC) {
                        *otz = -1;
                    }
                    if (*otz >= 0) {
                        p->uv2 = ((u16 *)f)[0x11];
                        if (dp != 0) {
                            d0 = d1 = d2 = dp;
                        } else {
                            d0 = func_80078240(((s16 *)f)[8] - D_1F800160, ((s16 *)f)[9] - D_1F800162, ((s16 *)f)[10] - D_1F800164) * 2;
                            d1 = func_80078240(((s16 *)f)[12] - D_1F800160, ((s16 *)f)[13] - D_1F800162, ((s16 *)f)[11] - D_1F800164) * 2;
                            d2 = func_80078240(((s16 *)f)[14] - D_1F800160, ((s16 *)f)[15] - D_1F800162, ((s16 *)f)[16] - D_1F800164) * 2;
                            if (d0 > 0x4000) {
                                d0 = 0x4000;
                            }
                            if (d1 > 0x4000) {
                                d1 = 0x4000;
                            }
                            if (d2 > 0x4000) {
                                d2 = 0x4000;
                            }
                        }
                        T2_lddp(d0);
                        T2_ldrgb(p->rgb0);
                        T2_dpcs();
                        T2_strgb(&p->rgb0);
                        T2_lddp(d1);
                        T2_ldrgb(p->rgb1);
                        T2_dpcs();
                        T2_strgb(&p->rgb1);
                        T2_lddp(d2);
                        T2_ldrgb(p->rgb2);
                        T2_dpcs();
                        T2_strgb(&p->rgb2);
                        do {
                            o = ot + *otz;
                            p->tag = *o | 0x09000000;
                            *o = (u32)p;
                        } while (0);
                        p++;
                    }
                }
            }
        }
        f += 9;
    }
    D_800BF544 = p;
    return f;
}

extern s32 D_1F800090_3460;
u32 *func_8012D2B4(u32 *f, u32 *ot, s32 n, s32 dp)
{
    s32 rgb;
    T2PolyGT4 *p = D_800BF544;
    s32 *otz = (s32 *)0x1F800004;
    u32 c;
    u32 w;
    u32 mode;
    s32 a, b, v;
    s32 d0, d1, d2, d3;
    u32 *o;

    rgb = 0x3C808080;
    T2_ldrgb(&rgb);
    while (n-- != 0) {
        T2_ldv3p(f);
        w = f[0];
        p->rgb0 = w & 0xFFF0F0F0;
        T2_rtpt();
        p->rgb1 = (w << 4) & 0xF0F0F0;
        c = f[1];
        T2_stflg((s32 *)0x1F800000);
        if (*(s32 *)0x1F800000 >= 0) {
            T2_nclip();
            p->uv0 = f[2];
            T2_stopz((s32 *)0x1F800000);
            if (*(s32 *)0x1F800000 > 0) {
                T2_stsxy3_gt4(p);
                T2_ldv1p(f);
                p->rgb2 = c & 0xF0F0F0;
                T2_rtps();
                p->rgb3 = (c << 4) & 0xF0F0F0;
                p->uv1 = f[3];
                T2_stflg((s32 *)0x1F800000);
                if (*(s32 *)0x1F800000 >= 0) {
                    T2_stsxy(&p->x3);
                    if ((p->x0 < 320 || p->x1 < 320 || p->x2 < 320 || p->x3 < 320) &&
                        (p->y0 < 240 || p->y1 < 240 || p->y2 < 240 || p->y3 < 240)) {
                        mode = c >> 24;
                        T2_stsz0(&D_1F800084);
                        T2_stsz1(&D_1F800088);
                        T2_stsz2(&D_1F80008C_f832);
                        T2_stsz3(&D_1F800090_3460);
                        switch (mode & 3) {
                        case 1:
                        case 3:
                            {
                                s32 *p4 = &D_1F800084;
                                {
                                    s32 *p8 = &D_1F800088;
                                    a = (*p8);
                                }
                                if (a < *p4) {
                                    a = *p4;
                                }
                            }
                            b = D_1F800090_3460;
                            if (b < D_1F80008C_f832) {
                                b = D_1F80008C_f832;
                            }
                            if (b < a) {
                                b = a;
                            }
                            *otz = b >> 2;
                            break;
                        case 2:
                            {
                                s32 *p4 = &D_1F800084;
                                a = D_1F800088;
                                if (*p4 < a) {
                                    a = *p4;
                                }
                            }
                            b = D_1F800090_3460;
                            if (D_1F80008C_f832 < b) {
                                b = D_1F80008C_f832;
                            }
                            if (a < b) {
                                b = a;
                            }
                            *otz = b >> 2;
                            break;
                        default:
                            T2_avsz4();
                            T2_stotz(otz);
                            break;
                        }
                        b = *otz >> 10;
                        *otz = (*otz >> b) + (b << 9);
                        if ((u32)(*otz - 4) >= 0x7FC) {
                            *otz = -1;
                        }
                        if (*otz >= 0) {
                            v = f[4];
                            p->uv2 = v;
                            p->uv3 = (u32)v >> 16;
                            if (dp != 0) {
                                d0 = d1 = d2 = d3 = dp;
                            } else {
                                d0 = func_80078240(((s16 *)f)[10] - D_1F800160, ((s16 *)f)[11] - D_1F800162, ((s16 *)f)[12] - D_1F800164) * 2;
                                d1 = func_80078240(((s16 *)f)[14] - D_1F800160, ((s16 *)f)[15] - D_1F800162, ((s16 *)f)[13] - D_1F800164) * 2;
                                d2 = func_80078240(((s16 *)f)[16] - D_1F800160, ((s16 *)f)[17] - D_1F800162, ((s16 *)f)[18] - D_1F800164) * 2;
                                d3 = func_80078240(((s16 *)f)[20] - D_1F800160, ((s16 *)f)[21] - D_1F800162, ((s16 *)f)[19] - D_1F800164) * 2;
                                if (d0 > 0x4000) {
                                    d0 = 0x4000;
                                }
                                if (d1 > 0x4000) {
                                    d1 = 0x4000;
                                }
                                if (d2 > 0x4000) {
                                    d2 = 0x4000;
                                }
                                if (d3 > 0x4000) {
                                    d3 = 0x4000;
                                }
                            }
                            T2_lddp(d0);
                            T2_ldrgb(p->rgb0);
                            T2_dpcs();
                            T2_strgb(&p->rgb0);
                            T2_lddp(d1);
                            T2_ldrgb(p->rgb1);
                            T2_dpcs();
                            T2_strgb(&p->rgb1);
                            T2_lddp(d2);
                            T2_ldrgb(p->rgb2);
                            T2_dpcs();
                            T2_strgb(&p->rgb2);
                            T2_lddp(d3);
                            T2_ldrgb(p->rgb3);
                            T2_dpcs();
                            T2_strgb(&p->rgb3);
                            do {
                                o = ot + *otz;
                                p->tag = *o | 0x0C000000;
                                *o = (u32)p;
                            } while (0);
                            p++;
                        }
                    }
                }
            }
        }
    next:
        f += 11;
    }
    D_800BF544 = p;
    return f;
}

typedef struct {
    s16 x, y, w, h;
} RECT16;
void func_8012D880(RECT16 *a) {
    RECT16 r;
    u16 buf[16];
    s32 i, j, k;
    u16 c;
    u16 g;
    s32 cr, cg, cb;

    r.w = 16;
    r.h = 1;
    for (i = 0; i < a->w; i += 16) {
        r.x = a->x + i;
        r.y = a->y;
        for (j = 0; j < a->h; j++) {
            func_80081278(&r, buf);
            func_80080F6C(0);
            for (k = 0; k < 16; k++) {
                c = buf[k];
                cg = c >> 5;
                cb = c >> 10;
                cr = c & 0x1F;
                g = cr * 77 + (cg & 0x1F) * 150 + (cb & 0x1F) * 29;
                g >>= 8;
                c &= 0x8000;
                if (g >= 32) {
                    g = 31;
                }
                buf[k] = c | (g << 10) | (g << 5) | g;
            }
            func_80081218(&r, buf);
            func_80080F6C(0);
            r.y++;
        }
    }
}

typedef struct { s16 m[3][3]; s32 t[3]; } Mat;
extern u8 D_800BF918;
extern u32 *D_800ED8C8;
extern Mat D_1F8000F8;
void func_8012DA14(u8 *a)
{
    u16 *i;
    u16 *end;
    u32 *tbl;
    u32 *ot;
    u32 *m;
    u32 w;
    u32 *ot_f;
    u32 *m_f;
    u32 w_f;

    if (a[6] == 0) {
        return;
    }
    gte_SetRotMatrix(&D_1F8000F8);
    gte_SetTransMatrix(&D_1F8000F8);
    i = (u16 *)(a + 0x10);
    if (D_800BF873) {
        end = (u16 *)(a + 0x10 + a[6] * 2);
        tbl = *(u32 **)(a + 0xC);
        ot = D_800ED8C8;
        gte_ldfcdir(0, 0, 0);
        for (; i < end; i++) {
            m = tbl + *i;
            w = *m;
            func_8012D2B4(func_8012CDF4(m + 1, ot, w & 0xFFFF, 0), ot, w >> 16, 0);
        }
    } else {
        end = (u16 *)(a + 0x10 + a[6] * 2);
        tbl = *(u32 **)(a + 0xC);
        ot_f = D_800ED8C8;
        for (; i < end; i++) {
            m_f = tbl + *i;
            w_f = *m_f;
            m_f = func_8012C7E0(m_f + 1, ot_f, w_f & 0xFF);
            w_f >>= 16;
            func_8012CAA8(m_f, ot_f, w_f & 0xFF);
        }
    }
}

extern s32 D_1F800080;
u32 *func_8012DBB4(u32 *f, u32 *ot, s32 n)
{
    s32 sz[3];
    T2PolyGT3 *p = D_800BF544;
    u32 m = 0xFFF0F0F0;
    s32 *flg = &D_1F800080;
    s32 *otz = &D_1F800084;
    u32 c;
    u32 mode;
    s32 b, e;
    u32 *o;

    while (n-- != 0) {
        T2_ldv3t(f);
        p->rgb0 = f[0];
        T2_rtpt();
        p->uv0 = f[2];
        p->uv1 = f[3];
        c = f[1];
        T2_stflg(flg);
        if (*flg >= 0) {
            T2_nclip();
            p->rgb1 = c & m;
            T2_stopz(flg);
            if (*flg > 0) {
                T2_stsxy3_gt3(p);
                if ((p->x0 < 320 || p->x1 < 320 || p->x2 < 320) && (p->y0 < 240 || p->y1 < 240 || p->y2 < 240)) {
                    p->rgb2 = (c << 4) & m;
                    c >>= 24; mode = c & 3;
                    if (mode != 0) {
                        T2_stsz1(&sz[0]);
                        T2_stsz2(&sz[1]);
                        T2_stsz3(&sz[2]);
                        if (mode == 1) {
                            if (sz[0] > sz[1]) {
                                b = sz[2];
                                if (b < sz[0]) {
                                    b = sz[0];
                                }
                                *otz = b >> 2;
                            } else {
                                b = sz[2];
                                if (b < sz[1]) {
                                    b = sz[1];
                                }
                                *otz = b >> 2;
                            }
                        } else {
                            if (sz[0] < sz[1]) {
                                b = sz[2];
                                if (sz[0] < b) {
                                    b = sz[0];
                                }
                                *otz = b >> 2;
                            } else {
                                b = sz[2];
                                if (sz[1] < b) {
                                    b = sz[1];
                                }
                                *otz = b >> 2;
                            }
                        }
                    } else {
                        T2_avsz3();
                        T2_stotz(otz);
                    }
                    e = *otz >> 10;
                    *otz = (*otz >> e) + (e << 9);
                    if ((u32)(*otz - 4) >= 0x7FC) {
                        *otz = -1;
                    }
                    if (*otz >= 0) {
                        p->uv2 = ((u16 *)f)[0x11];
                        do {
                            o = ot + *otz;
                            p->tag = *o | 0x09000000;
                            *o = (u32)p;
                        } while (0);
                        p++;
                    }
                }
            }
        }
        f += 9;
    }
    D_800BF544 = p;
    return f;
}

extern s32 D_80143D2C;
u32 *func_8012DE60(u32 *f, u32 *ot, s32 n)
{
    s32 sz[4];
    T2PolyGT4 *p = D_800BF544;
    u32 m = 0xFFF0F0F0;
    s32 *flg = &D_1F800080;
    s32 *otz = &D_1F800084;
    u32 c, c0;
    u32 mode;
    s32 b, a, v, e;
    u32 *o;

    while (n-- != 0) {
        T2_ldv1p(f);
        c = f[1];
        p->rgb2 = c & m;
        T2_rtps();
        p->uv1 = f[3];
        p->rgb3 = (c << 4) & m;
        T2_stflg(flg);
        if (*flg >= 0) {
            T2_stsxy(&p->x3);
            T2_ldv3p(f);
            c0 = f[0];
            p->rgb0 = c0 & m;
            T2_rtpt();
            p->rgb1 = (c0 << 4) & m;
            T2_stflg(flg);
            if (*flg >= 0) {
                T2_nclip();
                p->uv0 = f[2];
                T2_stopz(flg);
                if (*flg > 0) {
                    T2_stsxy3_gt4(p);
                    if ((p->x0 < 320 || p->x1 < 320 || p->x2 < 320 || p->x3 < 320) &&
                        (p->y0 < 240 || p->y1 < 240 || p->y2 < 240 || p->y3 < 240)) {
                        c >>= 24;
                        mode = c & 3;
                        if (mode != 0) {
                            T2_stsz0(&sz[0]);
                            T2_stsz1(&sz[1]);
                            T2_stsz2(&sz[2]);
                            T2_stsz3(&sz[3]);
                            if (mode == 1) {
                                a = sz[1];
                                if (a < sz[0]) {
                                    a = sz[0];
                                }
                                b = sz[3];
                                if (b < sz[2]) {
                                    do {
                                        b = sz[2];
                                    } while (0);
                                }
                                if (b < a) {
                                    b = a;
                                }
                                *otz = b >> 2;
                            } else {
                                a = sz[1];
                                if (sz[0] < a) {
                                    a = sz[0];
                                }
                                b = sz[3];
                                if (sz[2] < b) {
                                    b = sz[2];
                                }
                                if (a < b) {
                                    b = a;
                                }
                                *otz = b >> 2;
                            }
                        } else {
                            T2_avsz4();
                            T2_stotz(otz);
                        }
                        do {
                        e = *otz >> 10;
                        *otz = (*otz >> e) + (e << 9);
                        } while (0);
                        if ((u32)(*otz - 4) >= 0x7FC) {
                            *otz = -1;
                        }
                        if (*otz >= 0) {
                            v = f[4];
                            p->uv2 = v;
                            p->uv3 = (u32)v >> 16;
                            do {
                                o = ot + *otz;
                                p->tag = *o | 0x0C000000;
                                *o = (u32)p;
                            } while (0);
                            p++;
                        }
                    }
                }
            }
        }
        f += 11;
    }
    D_800BF544 = p;
    return f;
}

extern s16 *D_1F80028C;
void func_8012E1A0(u32 *a0, void *a1)
{
    u32 *s1;
    s32 s0;
    u32 w;
    s16 *o;

    s1 = a0;
    a0 += 4;

    if (D_800BF873) {
        o = (s16 *)D_1F80028C;
        { s32 x = o[0x17]; s32 y = o[0x19]; s32 z = o[0x1B]; s0 = func_80078240(x - D_1F800160, y - D_1F800162, z - D_1F800164) << 1; }
        gte_ldfcdir(0, 0, 0);
        w = *s1;
        func_8012D2B4(func_8012CDF4(a0, a1, w & 0xFFFF, s0), a1, w >> 16, s0);
    } else {
        w = *s1;
        f_UpdateCircusLockerNpcActor(func_801311D0(a0, a1, w & 0xFFFF), a1, w >> 16);
    }
}

typedef struct {
    u8 x[8];
} S8;
extern S8 D_80136248[];
void func_8012E2A0(void)
{
    u32 i;

    if (D_800BF873) {
        for (i = 0; i < 5; i++) {
            func_8012D880(&D_80136248[i]);
        }
    }
}

typedef struct {
    s16 pad0;
    s16 x;
    s16 pad4[3];
    s16 z;
    s16 padC[10];
    s16 pitch;
    u16 yaw;
} Cam80123E1C;
extern Cam80123E1C D_1F8000D0_959d;
extern s32 D_800A3F90;
extern s32 D_800A3F94;
void func_8012E2F4(u8 *a) {
    s32 p[6];
    s32 ang;
    s32 s;
    s32 dx;
    s32 dz;
    s16 y;

    D_800A3F90 = 0x4B00;
    y = D_1F8000D0_959d.yaw;
    D_800A3F94 = 0x1C7;
    ang = (-y - D_800A3F94) & 0xFFF;

    p[0] = D_1F8000D0_959d.x;
    p[1] = D_1F8000D0_959d.z;
    p[2] = p[0] + ((func_80083E80(ang) * D_800A3F90) >> 12);
    p[3] = p[1] + ((func_80083F50(ang) * D_800A3F90) >> 12);
    ang = (D_800A3F94 - (s16)D_1F8000D0_959d.yaw) & 0xFFF;
    p[4] = p[0] + ((func_80083E80(ang) * D_800A3F90) >> 12);
    p[5] = p[1] + ((func_80083F50(ang) * D_800A3F90) >> 12);
    p[0] -= (func_80083E80(-(s16)D_1F8000D0_959d.yaw) * 1600) >> 12;
    p[1] -= (func_80083F50(-(s16)D_1F8000D0_959d.yaw) * 1600) >> 12;
    s = abs(func_80083E80(D_1F8000D0_959d.pitch));
    dx = (func_80083E80(-(s16)D_1F8000D0_959d.yaw) * s) >> 12;
    dz = (func_80083F50(-(s16)D_1F8000D0_959d.yaw) * s) >> 12;
    dx = (dx * D_800A3F90 * 5) >> 16;
    dz = (dz * D_800A3F90 * 5) >> 16;
    p[2] -= dx;
    p[3] -= dz;
    p[4] -= dx;
    p[0] -= dx;
    p[5] -= dz;
    p[1] -= dz;
    p[0] /= 640;
    p[1] /= 640;
    p[2] /= 640;
    p[3] /= 640;
    p[4] /= 640;
    p[5] /= 640;
    a[6] = 0;
    func_8012E610(a, &p[0], &p[2], &p[4]);
}

extern s8 *D_800ECF58_g8[];
#define GH(p, o) (*(s16 *)((u8 *)(p) + (o)))
typedef struct { u8 pad[0x10]; u16 cells[1]; } GridCellList;
static inline void tri_span_e610(u8 *a, s32 y, s32 l, s32 r) {
    s32 x;
    s16 *p;
    s32 off;

    if (y >= 0 && y < GH(a, 0xA)) {
        if (r >= GH(a, 8)) r = GH(a, 8) - 1;
        x = l;
        if (x < 0) x = 0;
        p = (s16 *)D_800ECF58_g8[8];
        p += 2;
        off = x * GH(a, 0xA) + y;
        while (p += off, x <= r) {
            if (*p != -1) {
                u8 n = a[6];
                if (n < 0xFE) {
                    a[6] = n + 1;
                    ((GridCellList *)a)->cells[n] = *p;
                }
            }
            off = GH(a, 0xA);
            x++;
        }
    }
}
void func_8012E610(u8 *a, s32 *p0, s32 *p1, s32 *p2) {
    s32 x0 = p0[0], y0 = p0[1];
    s32 x1 = p1[0], y1 = p1[1];
    s32 x2 = p2[0], y2 = p2[1];
    s32 t, dx1, dx2, dy1, dy2;
    s32 xl, xr, y;
    s32 sl1, sl2, sl3;

    if (y1 == y0 && y1 == y2) return;
    if (y1 < y0) { t = x0; x0 = x1; x1 = t; t = y0; y0 = y1; y1 = t; }
    if (y2 < y0) { t = x0; x0 = x2; x2 = t; t = y0; y0 = y2; y2 = t; }
    if (y2 < y1) { t = x1; x1 = x2; x2 = t; t = y1; y1 = y2; y2 = t; }
    dx1 = x1 - x0;
    dx2 = x2 - x0;
    dy1 = y1 - y0;
    dy2 = y2 - y0;
    if (y1 == y0) {
        if (x0 < x1) { xl = x0 << 16; xr = x1 << 16; }
        else { xl = x1 << 16; xr = x0 << 16; }
        sl1 = 0;
    } else {
        xl = xr = x0 << 16;
        sl1 = (dx1 << 16) / dy1;
    }
    xr += 0x10000;
    if (y1 == y2) sl2 = 0;
    else sl2 = ((x2 - x1) << 16) / (y2 - y1);
    sl3 = (dx2 << 16) / dy2;
    if (-dy2 * dx1 + dx2 * dy1 > 0) {
        for (y = y0; y < y1; y++) { tri_span_e610(a, y, xl >> 16, xr >> 16); xl += sl1; xr += sl3; }
        for (; y <= y2; y++) { tri_span_e610(a, y, xl >> 16, xr >> 16); xl += sl2; xr += sl3; }
    } else {
        for (y = y0; y < y1; y++) { tri_span_e610(a, y, xl >> 16, xr >> 16); xr += sl1; xl += sl3; }
        for (; y <= y2; y++) { tri_span_e610(a, y, xl >> 16, xr >> 16); xl += sl3; xr += sl2; }
    }
}

extern u16 *D_800ECF78;
void func_8012EB50(u8 *a)
{
    u16 *p = D_800ECF78;
    u16 t;

    *(u16 **)(a + 0xC) = p;
    *(u16 *)(a + 8) = p[0];
    t = p[1];
    a[7] = 0;
    *(u16 *)(a + 0xA) = t;
}

extern s32 D_8013FF48[];
void func_8012EB7C(u8 *a, s32 *b) {
    s32 i;
    s32 j;
    s32 m;
    s32 d;
    s32 *v;
    u8 *p;

    switch (*(s32 *)(a + 4) & 0xF) {
    case 1:
        i = 0;
        break;
    case 2:
        i = 1;
        break;
    case 4:
        i = 2;
        break;
    case 8:
        i = 3;
        break;
    case 3:
        i = D_8013FF48[1] > D_8013FF48[0];
        break;
    case 5:
        i = (D_8013FF48[2] > D_8013FF48[0]) * 2;
        break;
    case 9:
        i = 0;
        if (D_8013FF48[3] > D_8013FF48[0]) {
            i = 3;
        }
        break;
    case 6:
        i = 1;
        if (D_8013FF48[2] > D_8013FF48[1]) {
            i = 2;
        }
        break;
    case 10:
        i = 1;
        if (D_8013FF48[3] > D_8013FF48[1]) {
            i = 3;
        }
        break;
    case 12:
        i = 2;
        if (D_8013FF48[3] > D_8013FF48[2]) {
            i = 3;
        }
        break;
    case 11:
        if (D_8013FF48[3] > D_8013FF48[0]) {
            i = 1;
            if (D_8013FF48[3] > D_8013FF48[1]) {
                i = 3;
            }
        } else {
            i = D_8013FF48[1] > D_8013FF48[0];
        }
        break;
    case 13:
        if (D_8013FF48[3] > D_8013FF48[0]) {
            i = 2;
            if (D_8013FF48[3] > D_8013FF48[2]) {
                i = 3;
            }
        } else {
            i = (D_8013FF48[2] > D_8013FF48[0]) * 2;
        }
        break;
    case 14:
        if (D_8013FF48[3] > D_8013FF48[1]) {
            i = 2;
            if (D_8013FF48[3] > D_8013FF48[2]) {
                i = 3;
            }
        } else {
            i = 1;
            if (D_8013FF48[2] > D_8013FF48[1]) {
                i = 2;
            }
        }
        break;
    case 7:
        if (D_8013FF48[2] > D_8013FF48[0]) {
            i = 1;
            if (D_8013FF48[2] > D_8013FF48[1]) {
                i = 2;
            }
        } else {
            i = D_8013FF48[1] > D_8013FF48[0];
        }
        break;
    case 15:
    default:
        m = D_8013FF48[0];
        i = 0;
        for (j = 1; j < 4; j++) {
            v = &D_8013FF48[j];
            if (m < *v) {
                i = j;
                m = *v;
            }
        }
        break;
    }
    m = D_8013FF48[i];
    p = a + i * 4;
    d = *(s16 *)(p + 0x20) * m;
    j = *(s16 *)(p + 0x22) * m;
    b[0] -= d;
    b[2] -= j;
}

typedef struct {
    u8 pad0[4];
    s32 flags;
    s16 a, b, c, d;
    s16 e[4][2];
    s16 n[4][2];
    u8 pad30[0];
} ColTri;
typedef struct {
    s32 x, y, z;
} V3_9da5;
typedef struct {
    u16 *list;
    u16 *grid;
    ColTri *tris;
} ColTable;
extern ColTable D_8013F718;
extern ColTable D_8013F724;
extern s32 D_8013FF58[];
extern s32 D_1F8001C8[];
s32 func_8012EE08(s32 *pos, s16 *off, s32 flag)
{
    s32 best = 0;
    s32 ret = best;
    s32 iter = 2;
    s32 n = best;
    s32 *v = D_1F8001C8;
    ColTable *t;
    ColTri *found[4];
    u16 *list;
    u16 *grid;
    ColTri *tris;
    ColTri *hit;
    ColTri *tri;
    u16 *q;
    u16 *p;
    u16 k;
    u16 cell;
    s32 m;
    s32 i, j, inside, d, y, x, z;
    s32 *e;
    s16 *pl;
    s32 w;

    if (D_800BF816 == 0) {
        t = &D_8013F718;
    } else {
        t = &D_8013F724;
    }
    list = t->list;
    grid = t->grid;
    tris = t->tris;
    ((V3_9da5 *)v)->x = pos[0] + (off[0] << 16);
    v[1] = pos[1] + (off[1] << 16);
    v[2] = pos[2] + (off[2] << 16);
    while (iter-- > 0) {
        hit = NULL;
        x = ((s16 *)v)[1];
        z = ((s16 *)v)[5];
        x /= 512;
        z /= 512;
        cell = grid[(z << 6) + x];
        if (cell == 0xFFFF) {
            return 0;
        }
        if (list[cell] != 0xFFFF) {
            m = cell;
            do {
                k = list[m];
                tri = &tris[k];
                if (tri->flags & 0x8000) {
                    if (!(tri->flags & 0x100) || flag != 0) {
                        for (i = 0; i < n; i++) {
                            if (tri == found[i]) {
                                break;
                            }
                        }
                        if (i == n) {
                            j = 0;
                            inside = 0;
                            for (; j < 4; j++) {
                                d = (((s16 *)v)[1] - tri->e[j][0]) * tri->n[j][0] +
                                    (((s16 *)v)[5] - tri->e[j][1]) * tri->n[j][1];
                                D_8013FF58[j] = d;
                                if (d > 0) {
                                    goto out;
                                }
                            }
                            inside = 1;
                        out:
                            if (inside) {
                                s32 c1, c2, c3;

                                pl = &tri->a;
                                w = pl[3] << 12;
                    y = (tri->a * ((s16 *)v)[1] + pl[2] * ((s16 *)v)[5] + w) / -pl[1];
                                c1 = y <= best;
                                c2 = y >= ((s16 *)v)[3];
                                c3 = y <= ((s16 *)v)[3] + 0x80;
                                if (c1 && c2 && c3) {
                                    hit = tri;
                                    best = y;
                                    D_8013FF48[0] = D_8013FF58[0];
                                    D_8013FF48[1] = D_8013FF58[1];
                                    D_8013FF48[2] = D_8013FF58[2];
                                    D_8013FF48[3] = D_8013FF58[3];
                                }
                            }
                        }
                    }
                }
            } while (list[++m] != 0xFFFF);
        }
        if (hit == NULL) {
            break;
        }
        func_8012EB7C(hit, v);
        ret = 1;
        found[n++] = hit;
    }
    pos[0] = v[0] - (off[0] << 16);
    pos[2] = v[2] - (off[2] << 16);
    return ret;
}

extern s16 D_1F8001A4;
extern u16 D_1F8001A6;
#define U_d0c0(p, o) (*(u16 *)((u8 *)(p) + (o)))
extern u16 D_1F800160_3621;
extern u16 D_1F800164_7d8c;
s32 func_8012F1BC(s32 *pos, s16 *off, s16 flag)
{
    s32 fl = 0;
    s32 *v = D_1F8001C8;
    ColTable *t;
    u16 *list;
    u16 *grid;
    ColTri *tris;
    ColTri *hit;
    ColTri *tri;
    u32 k;
    u16 cell;
    s32 i;
    s32 j, inside, d, y, x, z, best;
    s16 *pl;
    s32 w;

    if (D_800BF816 == 0) {
        t = &D_8013F718;
    } else {
        t = &D_8013F724;
    }
    list = t->list;
    grid = t->grid;
    tris = t->tris;
    ((V3_9da5 *)v)->x = pos[0] + (off[0] << 16);
    x = ((s16 *)v)[1];
    v[1] = pos[1] + (off[1] << 16);
    v[2] = pos[2] + (off[2] << 16);
    z = ((s16 *)v)[5];
    x /= 512;
    z /= 512;
    cell = grid[(z << 6) + x];
    if (cell == 0xFFFF) {
        D_1F8001A4 = 0;
        return 0xFF;
    }
    best = 0;
    hit = (ColTri *)best;
    if (list[cell] != 0xFFFF) {
        i = cell;
        do {
            k = list[i];
            tri = &tris[k];
            if (!(tri->flags & 0x8800)) {
                j = 0;
                inside = 0;
                for (; j < 4; j++) {
                    d = (((s16 *)v)[1] - tri->e[j][0]) * tri->n[j][0] + (((s16 *)v)[5] - tri->e[j][1]) * tri->n[j][1];
                    D_8013FF58[j] = d;
                    if (d > 0) {
                        goto out;
                    }
                }
                inside = 1;
            out:
                if (inside) {
                    s32 c1, c2, c3;

                    pl = &tri->a;
                    w = pl[3] << 12;
                    y = (tri->a * ((s16 *)v)[1] + pl[2] * ((s16 *)v)[5] + w) / -pl[1];
                    c1 = y <= best;
                    c2 = y <= ((s16 *)v)[3];
                    c3 = ((s16 *)v)[3] - 0x100 < y;
                    if (c1 && c2 && c3 && !(fl & 0x2000)) {
                        hit = tri;
                        fl = tri->flags;
                        best = y;
                    }
                }
            }
        } while (list[++i] != 0xFFFF);
    }
    if (hit != NULL) {
        if (flag) {
            D_1F8001A6 = *(u16 *)&hit->flags;
        }
        D_1F8001A4 = best;
        ((s16 *)pos)[3] = best - off[1];
        return 1;
    }
    D_1F8001A4 = 0;
    return 0;
}

s32 func_8012F480(s32 *pos, s16 *off)
{
    s32 *v = D_1F8001C8;
    ColTable *t;
    u16 *list;
    u16 *grid;
    ColTri *tris;
    ColTri *hit;
    ColTri *tri;
    u32 k;
    u16 cell;
    s32 i;
    s32 j, inside, d, y, x, z, best;
    s16 *pl;
    s32 w;

    if (D_800BF816 == 0) {
        t = &D_8013F718;
    } else {
        t = &D_8013F724;
    }
    list = t->list;
    grid = t->grid;
    tris = t->tris;
    ((V3_9da5 *)v)->x = pos[0] + (off[0] << 16);
    x = ((s16 *)v)[1];
    v[1] = pos[1] + ((off[1] - 0x28) << 16);
    v[2] = pos[2] + (off[2] << 16);
    z = ((s16 *)v)[5];
    x /= 512;
    z /= 512;
    cell = grid[(z << 6) + x];
    if (cell == 0xFFFF) {
        D_1F8001A4 = 0;
        return 0xFF;
    }
    best = 0;
    hit = (ColTri *)best;
    if (list[cell] != 0xFFFF) {
        i = cell;
        do {
            k = list[i];
            tri = &tris[k];
            j = 0;
            inside = 0;
            for (; j < 4; j++) {
                d = (((s16 *)v)[1] - tri->e[j][0]) * tri->n[j][0] + (((s16 *)v)[5] - tri->e[j][1]) * tri->n[j][1];
                D_8013FF58[j] = d;
                if (d > 0) {
                    goto out;
                }
            }
            inside = 1;
        out:
            if (inside) {
                s32 c1, c2, c3;

                pl = &tri->a;
                w = pl[3] << 12;
                y = (tri->a * ((s16 *)v)[1] + pl[2] * ((s16 *)v)[5] + w) / -pl[1];
                c1 = y <= best;
                c2 = y >= ((s16 *)v)[3];
                c3 = y <= ((s16 *)v)[3] + 0x80;
                if (c1 && c2 && c3) {
                    hit = tri;
                    best = y;
                }
            }
        } while (list[++i] != 0xFFFF);
    }
    if (hit == NULL) {
        D_1F8001A4 = 0;
        return -1;
    }
    if (!(hit->flags & 0x8000)) {
        return 0;
    }
    D_1F8001A4 = 0;
    return 1;
}

extern u8 *D_800ECF84;
extern s16 D_1F8000F0;
extern s16 D_1F8000F2_a096;
void func_8012F6EC(u8 *a)
{
    s32 pad;
    u8 *p = D_800ECF84;
    s32 x, y;
    u16 n;

    switch (a[0]) {
    case 0:
        a[0] = 1;
        a[3] = 0;
        *(u16 *)(a + 4) = *(u16 *)(p + 0);
        *(u16 *)(a + 6) = *(u16 *)(p + 2);
        *(u16 *)(a + 8) = *(u16 *)(p + 4);
        *(u16 *)(a + 0xA) = *(u16 *)(p + 6);
        *(u16 *)(a + 0xC) = *(u16 *)(p + 8);
        *(u16 *)(a + 0xE) = *(u16 *)(p + 0xA);
        a[0x10] = p[0xC];
        a[0x11] = p[0xD];
        {
            u16 l1 = *(u16 *)(p + 0xE);
            u16 l0 = *(u16 *)(p + 0x10);
        *(u16 *)(a + 0x2C) = 0x900;
        *(u16 *)(a + 0x2E) = 0x8E8;
        {
            u8 *b0 = p + 0x14;
            u8 *b1 = b0 + l0;
            u8 *b2 = b1 + l1;
        *(u8 **)(a + 0x1C) = b2;
        *(u8 **)(a + 0x18) = b0;
        *(u8 **)(a + 0x14) = b1;
        }
        }
        *(u8 **)(a + 0x34) = *(u8 **)(a + 0x1C);
        *(u16 *)(a + 0x30) = (*(u16 *)(a + 0x2C) * a[0x10]) / 144;
        *(u16 *)(a + 0x32) = (*(u16 *)(a + 0x2E) * a[0x11]) / 144;
        a[0x38] = 1;
        break;
    case 2: break;
    case 1:
        { s32 k = D_1F8000F2_a096; u16 w = *(u16 *)(a + 0x2C); x = ((w + 0x140) >> 1) - ((k * w) >> 12); }
        while (x < 0) {
            x += *(u16 *)(a + 0x30);
        }
        while (x >= *(u16 *)(a + 0x30)) {
            x -= *(u16 *)(a + 0x30);
        }
        y = ((D_1F8000F0 * *(u16 *)(a + 0x2E)) >> 12) + a[0x11] * 8 - 0x20;
        while (y < 0) {
            y += *(u16 *)(a + 0x32);
        }
        while (y >= *(u16 *)(a + 0x32)) {
            y -= *(u16 *)(a + 0x32);
        }
        if (--*(s8 *)(a + 0x38) <= 0) {
            a[3] = 1;
        }
        *(s16 *)(a + 0x28) = x;
        *(s16 *)(a + 0x2A) = y;
        break;
    }
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8012F938);

#define H16(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define U16_5dc5(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define W32(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define H16(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define U16_5dc5(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define W32(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define H16(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define U16_5dc5(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define W32(p, o) (*(s32 *)((u8 *)(p) + (o)))
s32 func_8012FC50(u8 *a) {
    u8 *w = *(u8 **)(a + 0x6C);
    s16 m = U16_5dc5(w, 0xA);
    s16 sp;
    s32 dz;

    switch (a[0x78]) {
    case 0:
        sp = (s16)U16_5dc5(a, 0x64) >> 8;
        if (sp == 0) {
            sp = 10;
        }
        dz = U16_5dc5(a, 0x76) - U16_5dc5(a, 0x36);
        U16_5dc5(a, 0x48) = U16_5dc5(a, 0x74) - U16_5dc5(a, 0x2E);
        U16_5dc5(a, 0x4C) = dz;
        H16(a, 0x64) = (s16)func_80084080((s16)dz * (s16)dz + H16(a, 0x48) * H16(a, 0x48)) / (s16)sp;
        if (H16(a, 0x64) == 0) {
            H16(a, 0x64) = 1;
        }
        H16(a, 0x64) = 0x1000 / H16(a, 0x64);
        H16(a, 0x44) = 0x1000;
        if ((s16)m == -1) {
            H16(a, 0x56) = func_80085690(-H16(a, 0x4C), H16(a, 0x48)) & 0xFFF;
        } else if ((s16)m == 0) {
            a[0x78] = 2;
            return 0;
        }
        H16(a, 0x66) = func_80085690(-H16(a, 0x4C), H16(a, 0x48)) & 0xFFF;
        a[0x78]++;
    case 1:
        if (func_80041438(a, H16(a, 0x66), 0x100) != 0) {
            a[0x78]++;
        }
        if ((s16)m == 1) {
            return 0;
        }
    case 2:
        func_80041768(a, U16_5dc5(a, 0x72) & 0xFFF, 4);
        U16_5dc5(a, 0x44) -= U16_5dc5(a, 0x64);
        if (H16(a, 0x44) <= 0) {
            H16(a, 0x44) = 0;
        }
        U16_5dc5(a, 0x2E) = U16_5dc5(w, 4) - H16(a, 0x44) * H16(a, 0x48) / 4096;
        U16_5dc5(a, 0x36) = U16_5dc5(w, 6) - H16(a, 0x44) * H16(a, 0x4C) / 4096;
        func_80130E20(a, 0);
        if (f_TestCircusActorGroundContact(a) != 0) {
            if (H16(a, 0x50) > 0x1400) {
                func_80074590(3, 0, 0);
            }
            H16(a, 0x50) = 0;
        } else {
            U16_5dc5(a, 0x50) += 0x800;
            if (H16(a, 0x50) > 0x3000) {
                H16(a, 0x50) = 0x3000;
            }
        }
        W32(a, 0x30) += H16(a, 0x50) << 8;
        a[0x29] = 0;
        if (H16(a, 0x44) == 0) {
            if (a[0x7B] != 0xFF && !(H16(a, 0x72) & 0x8000)) {
                func_80041768(a, a[0x7B], 4);
            }
            return 1;
        }
        func_80042EA4(a, a + 0x68, H16(a, 0x6A));
        return 0;
    }
    return 0;
}

s32 func_8012FFD4(u8 *a) {
    u8 *w = *(u8 **)(a + 0x6C);
    s16 m = U16_5dc5(w, 0xA);
    s16 sp;
    s32 dz;

    switch (a[0x78]) {
    case 0:
        sp = (s16)U16_5dc5(a, 0x64) >> 8;
        if (sp == 0) {
            sp = 10;
        }
        dz = U16_5dc5(a, 0x76) - U16_5dc5(a, 0x36);
        U16_5dc5(a, 0x48) = U16_5dc5(a, 0x74) - U16_5dc5(a, 0x2E);
        U16_5dc5(a, 0x4C) = dz;
        H16(a, 0x64) = (s16)func_80084080((s16)dz * (s16)dz + H16(a, 0x48) * H16(a, 0x48)) / (s16)sp;
        if (H16(a, 0x64) == 0) {
            H16(a, 0x64) = 1;
        }
        H16(a, 0x64) = 0x1000 / H16(a, 0x64);
        H16(a, 0x44) = 0x1000;
        if ((s16)m == -1) {
            H16(a, 0x56) = func_80085690(-H16(a, 0x4C), H16(a, 0x48)) & 0xFFF;
        } else if ((s16)m == 0) {
            a[0x78] = 2;
            return 0;
        }
        H16(a, 0x66) = func_80085690(-H16(a, 0x4C), H16(a, 0x48)) & 0xFFF;
        a[0x78]++;
    case 1:
        if (func_80041438(a, H16(a, 0x66), 0x100) != 0) {
            a[0x78]++;
        }
        if ((s16)m == 1) {
            return 0;
        }
    case 2:
        func_80041768(a, U16_5dc5(a, 0x72) & 0xFFF, 4);
        if (*(u16 *)(*(u8 **)(a + 0x38) + 2) == 0) {
            U16_5dc5(a, 0x44) -= U16_5dc5(a, 0x64);
            if (H16(a, 0x44) <= 0) {
                H16(a, 0x44) = 0;
            }
            U16_5dc5(a, 0x2E) = U16_5dc5(w, 4) - H16(a, 0x44) * H16(a, 0x48) / 4096;
            U16_5dc5(a, 0x36) = U16_5dc5(w, 6) - H16(a, 0x44) * H16(a, 0x4C) / 4096;
            func_80130E20(a, 0);
            if (f_TestCircusActorGroundContact(a) != 0) {
                if (H16(a, 0x50) > 0x1400) {
                    func_80074590(3, 0, 0);
                }
                H16(a, 0x50) = 0;
            } else {
                U16_5dc5(a, 0x50) += 0x800;
                if (H16(a, 0x50) > 0x3000) {
                    H16(a, 0x50) = 0x3000;
                }
            }
            W32(a, 0x30) += H16(a, 0x50) << 8;
        }
        a[0x29] = 0;
        if (H16(a, 0x44) == 0) {
            if (a[0x7B] != 0xFF) {
                func_80041768(a, a[0x7B], 4);
            }
            return 1;
        }
        if (func_80042EA4(a, a + 0x68, H16(a, 0x6A)) != 0) {
            func_800521F4(0, 0, 0xF1, 2);
        }
        return 0;
    }
    return 0;
}

s32 func_80130374(u8 *a)
{
    u8 *t = D_800E7E80;
    u8 *p;
    s32 ang;
    u16 b;

    switch (a[0x78]) {
    case 0: {
        u16 az = U_d0c0(a, 0x76);
        u16 tz = U_d0c0(t, 0x36);
        u16 ax = U_d0c0(a, 0x74);
        u16 tx = U_d0c0(t, 0x2E);
        s16 dz = az - tz;
        s16 dx = ax - tx;

        if (dz * dz + dx * dx < H(a, 0x68) * H(a, 0x68)) {
            U_d0c0(t, 0x2E) = ax;
            U_d0c0(t, 0x36) = U_d0c0(a, 0x76);
            return 1;
        }
        ang = func_80085690((s16)tz - (s16)az, (s16)ax - (s16)tx) & 0xFFF;
        b = ang;
        switch (H(a, 0x66)) {
        case -1:
            H(t, 0x56) = ang;
        case 0:
            a[0x78] = 2;
            break;
        case 2:
            b = (ang + 0x800) & 0xFFF;
        default:
            H(a, 0x66) = b;
            a[0x78]++;
            break;
        }
        if (H(a, 0x72) == 0) {
            t[5] = 0x27;
            t[6] = 0;
        }
        break;
    }
    case 1:
        if (func_80041438(t, H(a, 0x66), 0x100) != 0) {
            a[0x78]++;
        }
        break;
    case 2:
        if (H(a, 0x72) == 1) {
            func_80054D14(t, 0xCE, 4);
        }
        a[0x78]++;
    case 3:
        if ((H(t, 0x44) = H(a, 0x64) >> 8) == 0) {
            H(t, 0x44) = 10;
        }
        H(a, 0x64) = func_80084080((s16)(U_d0c0(a, 0x76) - U_d0c0(t, 0x36)) * (s16)(U_d0c0(a, 0x76) - U_d0c0(t, 0x36)) +
                                   (s16)(U_d0c0(a, 0x74) - U_d0c0(t, 0x2E)) * (s16)(U_d0c0(a, 0x74) - U_d0c0(t, 0x2E)));
        if ((H(a, 0x64) = H(a, 0x64) / H(t, 0x44)) == 0) {
            H(a, 0x64) = 1;
        }
        H(a, 0x64) = 0x1000 / H(a, 0x64);
        H(a, 0x66) = 0x1000;
        H(a, 0x74) -= U_d0c0(t, 0x2E);
        H(a, 0x76) -= U_d0c0(t, 0x36);
        a[0x78]++;
        break;
    case 4:
        p = *(u8 **)(a + 0x6C);
        if ((H(a, 0x66) -= H(a, 0x64)) <= 0) {
            H(a, 0x66) = 0;
        }
        H(t, 0x2E) = U_d0c0(p, 4) - H(a, 0x66) * H(a, 0x74) / 4096;
        H(t, 0x36) = U_d0c0(p, 6) - H(a, 0x66) * H(a, 0x76) / 4096;
        if (H(a, 0x66) == 0) {
            H(t, 0x44) = 0;
            if (H(a, 0x72) == 1) {
                func_80054D14(t, 0xCD, 4);
            }
            return 1;
        }
        break;
    }
    return 0;
}

s32 func_80130730(u8 *a)
{
    u8 *t = D_800E7E80;
    u16 dx = D_1F800160_3621 - U_d0c0(a, 0x2E);
    u16 dz = D_1F800164_7d8c - U_d0c0(a, 0x36);
    s16 ang;

    switch (a[0x78]) {
    case 0: {
        s16 sz = dz;
        s16 sx = dx;
        s16 e;

        ang = func_80085690(-sz, sx) & 0xFFF;
        H(a, 0x64) = ang;
        if (ang == H(a, 0x72)) {
            return 1;
        }
        H(a, 0x66) = func_80084080(sx * sx + sz * sz);
        e = U_d0c0(a, 0x72) + U_d0c0(a, 0x74);
        if (e > 0x1000 && e - 0x1000 >= H(a, 0x64)) {
            H(a, 0x64) += 0x1000;
        }
        if (H(a, 0x72) < H(a, 0x64) && H(a, 0x64) <= e) {
            H(a, 0x76) *= -1;
        } else if (e < H(a, 0x64)) {
            H(a, 0x64) -= 0x1000;
        }
        t[5] = 0x27;
        t[6] = 0;
        H(t, 0x44) = 10;
        a[0x78]++;
        break;
    }
    case 1:
        H(a, 0x64) += U_d0c0(a, 0x76);
        if (H(a, 0x76) >= 0) {
            if (H(a, 0x64) >= H(a, 0x72)) {
                H(a, 0x64) = H(a, 0x72);
                H(t, 0x44) = 0;
            }
            ang = func_80085690(-(s16)dz, (s16)dx) + 0x400;
        } else {
            if (H(a, 0x72) >= H(a, 0x64)) {
                H(a, 0x64) = H(a, 0x72);
                H(t, 0x44) = 0;
            }
            ang = func_80085690(-(s16)dz, (s16)dx) - 0x400;
        }
        H(t, 0x56) = ang;
        H(t, 0x2E) = U_d0c0(a, 0x2E) + func_80083F50(-H(a, 0x64)) * H(a, 0x66) / 4096;
        H(t, 0x36) = U_d0c0(a, 0x36) + func_80083E80(-H(a, 0x64)) * H(a, 0x66) / 4096;
        if (H(t, 0x44) == 0) {
            return 1;
        }
        break;
    }
    return 0;
}

extern u8 D_1F8000DC[];
s32 func_801309E0(u8 *a)
{
    u8 *g = D_800E8008;
    u8 s = a[0x78];
    s32 pad[4];

    switch (s) {
    case 0:
        if (!(*(u16 *)(a + 0x72) & 1)) {
            func_8006E1C0(7);
        } else {
            g[0x64] = 7;
        }
        if (*(s16 *)(a + 0x66) == 0) {
            func_8006CBD0(g, *(s32 *)(a + 0x74));
            if (*(s16 *)(a + 0x64) != 0) {
                *(s16 *)(a + 0x4E) = *(s16 *)(g + 0x3A);
                *(s16 *)(a + 0x50) = *(s16 *)(g + 0x3E);
                *(s16 *)(a + 0x52) = *(s16 *)(g + 0x42);
            }
            return 1;
        }
        func_8006CBA8(D_1F8000DC);
        func_8006CC1C(g, *(s32 *)(a + 0x74), *(s16 *)(a + 0x66));
        if (*(s16 *)(a + 0x64) != 0) {
            *(s16 *)(a + 0x4E) = *(s16 *)(g + 0x3A);
            *(s16 *)(a + 0x50) = *(s16 *)(g + 0x3E);
            *(s16 *)(a + 0x52) = *(s16 *)(g + 0x42);
        }
        if (*(s16 *)(a + 0x68) != 0) {
            return 1;
        }
        a[0x78]++;
        break;
    case 1:
        if (*(s16 *)(a + 0x64) != 0) {
            *(s16 *)(g + 0x3A) = *(s16 *)(a + 0x4E);
            *(s16 *)(g + 0x3E) = *(s16 *)(a + 0x50);
            *(s16 *)(g + 0x42) = *(s16 *)(a + 0x52);
        }
        {
            s32 r = func_8006CDCC(g);
            if (*(s16 *)(a + 0x64) != 0) {
                *(s16 *)(a + 0x4E) = *(s16 *)(g + 0x3A);
                *(s16 *)(a + 0x50) = *(s16 *)(g + 0x3E);
                *(s16 *)(a + 0x52) = *(s16 *)(g + 0x42);
            }
            if (r == s) {
                return 1;
            }
        }
        break;
    
    }
    return 0;
}

s32 func_80130BA4(u8 *a) {
    s16 y = M2C_FIELD(a, s16 *, 0x32);
    s32 i;

    a[0x29] = 0;
    M2C_FIELD(a, s16 *, 0x32) = y - 0x80;
    for (i = 0; i < 200; i++) {
        if (f_TestCircusActorGroundContact(a) != 0) {
            a[0x29] = 0;
            return 1;
        }
        M2C_FIELD(a, s16 *, 0x32) += 0x20;
    }
    M2C_FIELD(a, s16 *, 0x32) = y;
    return 0;
}

extern s16 D_1F8001C6;
s32 func_80130C20(u8 *a) {
    u16 f;
    s16 g;

    switch (a[0x78]) {
    case 0:
        D_800BF818_7697 = a[0x74];
        g = M2C_FIELD(a, s16 *, 0x76);
        f = M2C_FIELD(a, u16 *, 0x74);
        D_1F8001C6 = g;
        if (!(f & 1)) {
            return 1;
        }
        M2C_FIELD(a, s16 *, 0x72) = 0x10;
        a[0x78]++;
        break;
    case 1:
        if (--M2C_FIELD(a, s16 *, 0x72) == 0) {
            return 1;
        }
        break;
    }
    return 0;
}

s32 func_80130CB0(void *a0)
{
    if (func_8007778C(a0) == 0) {
        return 0;
    }
    func_8004190C(a0);
    return D_1F800137 == 0;
}

s32 f_CompleteUseTheSeesawEventIfResolved(void)
{
    s32 a = D_800E7FFE & 0x180;
    s32 b = D_800BFE56 & 0x80;

    if (a | b) {
        func_80040C00(0x23);
        return 1;
    }
    return 0;
}

s32 func_80130D44(void)
{
    if (D_800E7FFE & 0x180) {
        func_80040C00(0x23);
        return 1;
    }
    return 0;
}

void func_80130D80(u8 a0)
{
    s32 a = D_800E7FFE & 0x180;
    s32 b = D_800BFE56 & 0x80;

    if (a | b) {
        func_80042354(1, a0);
    } else {
        func_80042354(1, 2);
    }
}

void func_80130DD8(u8 a0)
{
    if (D_800E7FFE & 0x180) {
        func_80042354(1, a0);
    } else {
        func_80042354(1, 2);
    }
}

s32 func_80130E20(u8 *a, s32 b) {
    s32 s = (func_80083F50(M2C_FIELD(a, s16 *, 0x56)) * M2C_FIELD(a, s16 *, 0x44)) >> 4;
    s32 c = func_80083E80(M2C_FIELD(a, s16 *, 0x56)) * M2C_FIELD(a, s16 *, 0x44);

    M2C_FIELD(a, s32 *, 0x2C) += s;
    M2C_FIELD(a, s32 *, 0x34) -= c >> 4;
    if (b != 0) {
        return f_TestCircusActorForwardCollision(a);
    }
    return 0;
}

s32 f_TestCircusActorForwardCollision(u8 *a)
{
    s32 z = (-func_80083E80(*(s16 *)(a + 0x56)) * *(s16 *)(a + 0x80)) >> 12;
    s32 x = func_80083F50(*(s16 *)(a + 0x56)) * *(s16 *)(a + 0x80);
    AreaSVec *v = &D_1F8000C0_f4ad;
    D_1F8000C0_f4ad.x = x >> 12;
    v->y = *(s16 *)(a + 0x86) - *(s16 *)(a + 0x84);
    v->z = z;
    return func_8012EE08(a + 0x2C, v, 1) != 0;
}

extern s16 D_1F8000C0[];
s32 f_TestCircusActorGroundContact(u8 *p)
{
    if (p[0x29] == 0) {
        D_1F8000C0[0] = 0;
        D_1F8000C0[1] = *(u16 *)(p + 0x86) - *(u16 *)(p + 0x84);
        D_1F8000C0[2] = 0;
        if (func_8012F1BC(p + 0x2C, D_1F8000C0, 0) > 0) {
            p[0x29] = 1;
        }
    }
    return p[0x29];
}

typedef struct { u16 a, b; } Range;
extern Range D_8013F8AC[];
extern Range D_8013F8C4[];
extern Range D_8013F924[];
extern Range D_8013F994[];
extern Range D_8013F9AC[];
extern Range D_8013FA3C[];
extern Range D_8013FAA4[];
extern Range D_8013FAEC[];
extern Range D_8013FBBC[];
extern Range D_8013FC38[];
extern Range D_8013FC70[];
extern Range D_8013FCAC[];
extern Range D_8013FCE4[];
extern Range D_8013FD28[];
extern Range D_8013FD40[];
extern Range D_8013FD78[];
extern Range D_8013FDD4[];
extern Range D_8013FDF0[];
extern Range D_8013FE1C[];
extern Range D_8013FE98[];
extern u8 *D_1F80021C;
void func_80130FB8(s16 kind, s16 idx)
{
    Range *t;
    s32 n, base;
    u8 *p;
    switch (kind) {
    case 0:
        t = D_8013F8AC;
        n = 0x3;
        base = 0;
        break;
    case 1:
        t = D_8013F8C4;
        n = 0x1B;
        base = 0x396;
        break;
    case 2:
        t = D_8013F924;
        n = 0xB;
        base = 0x83;
        break;
    case 3:
        t = D_8013F994;
        n = 0x2;
        base = 0;
        break;
    case 4:
        t = D_8013F9AC;
        n = 0x8;
        base = 0x26E;
        break;
    case 5:
        t = D_8013FA3C;
        n = 0x1C;
        base = 0x21C;
        break;
    case 6:
        t = D_8013FAA4;
        n = 0x18;
        base = 0x94;
        break;
    case 7:
        t = D_8013FAEC;
        n = 0x1;
        base = 0x114;
        break;
    case 8:
        t = D_8013FBBC;
        n = 0x7;
        base = 0x106;
        break;
    case 9:
        t = D_8013FC38;
        n = 0x15;
        base = 0x268;
        break;
    case 10:
        t = D_8013FC70;
        n = 0x1E;
        base = 0x267;
        break;
    case 11:
        t = D_8013FCAC;
        n = 0xF;
        base = 0x438;
        break;
    case 12:
        t = D_8013FCE4;
        n = 0xC;
        base = 0x15D;
        break;
    case 13:
        t = D_8013FD28;
        n = 0xC;
        base = 0x24D;
        break;
    case 14:
        t = D_8013FD40;
        n = 0x1F;
        base = 0x1C8;
        break;
    case 15:
        t = D_8013FD78;
        n = 0xE;
        base = 0x1F8;
        break;
    case 16:
        t = D_8013FDD4;
        n = 0x1F;
        base = 0x2E2;
        break;
    case 17:
        t = D_8013FDF0;
        n = 0x11;
        base = 0x218;
        break;
    case 18:
        t = D_8013FE1C;
        n = 0xA;
        base = 0x143;
        break;
    case 19:
        t = D_8013FE98;
        n = 0x2;
        base = 0x61;
        break;
    default:
        return;
    }
    p = D_1F80021C + t[idx].a * 32 + base * 32;
    func_8001D2A8(n, p, p + (t[idx].b + 1) * 32, 0);
}

// ASM by design: hand-written GTE routine (no stack frame, trapping add / addi / sub, `or rd, $zero, rs` moves: never emitted by gcc 2.8.1).
INCLUDE_ASM("asm/a07/nonmatchings/a07", func_801311D0);

// ASM by design: hand-written GTE routine (no stack frame, trapping add / addi / sub, `or rd, $zero, rs` moves: never emitted by gcc 2.8.1).
INCLUDE_ASM("asm/a07/nonmatchings/a07", f_UpdateCircusLockerNpcActor);

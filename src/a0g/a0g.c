#include "common.h"
#include "game.h"
#include "m2c.h"
#include "gte.h"

#define H(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define U(p, o) (*(u16 *)((u8 *)(p) + (o)))
extern u16 D_1F80009C;
extern u8 D_1F800137;
extern u16 D_1F80018E;
extern u16 D_1F80018C;
extern u8 D_800BF840;
extern u16 D_1F80008C;

void func_80109180(u8 *a, u8 *b)
{
    s32 k;
    s32 g;
    s32 m;
    s32 c;
    s32 x, y;
    if (func_8002300C(a, b, H(b, 0x80) * 4) == 0) {
        return;
    }
    k = D_1F80009C + 0x800;
    b[0x2B] = 1;
    if (D_1F800137 == 0) {
        m = U(a, 0x140) - 0x400;
        g = func_80085690(-(s16)(U(b, 0x36) - U(a, 0x36)), (s16)(U(b, 0x2E) - U(a, 0x2E))) << 4;
        if (abs((s16)(g - m * 16)) < 0x1000) {
            D_1F80018E = 0x4100;
            D_1F80018C = U(a, 0x140) - 0x400;
            D_800BF840 = 0x42;
        } else {
            c = U(a, 0x140) + 0x400;
            if (abs((s16)(g - c * 16)) < 0x1000) {
                D_1F80018C = c;
                D_1F80018E = 0x4200;
                D_800BF840 = 0x43;
            }
        }
    }
    if (H(a, 0x80) + H(b, 0x80) + 0x50 < D_1F80008C) {
        return;
    }
    b[0x2B] = 2;
    if (H(a, 0x80) + H(b, 0x80) < D_1F80008C) {
        return;
    }
    x = (func_80083F50((s16)k) * (H(a, 0x80) + H(b, 0x80))) >> 12;
    y = (func_80083E80((s16)k) * (H(a, 0x80) + H(b, 0x80))) >> 12;
    U(a, 0x2E) = U(b, 0x2E) + x;
    U(a, 0x36) = U(b, 0x36) - y;
}

extern u8 **D_1F800154;
extern u8 D_1F80015C;
extern u8 D_1F800183;
extern u8 D_1F800182;
extern u8 D_1F800150;
extern u8 **D_1F80013C;
extern u8 D_1F800144;
#define TOWER_SCAN_LIST(e)                                          \
    {                                                    \
        u8 **m;                                          \
        u8 *o;                                           \
        D_1F800182 = D_1F800150;                         \
        while (D_1F800182 != 0) {                        \
            D_1F800182--;                                \
        }                                                \
        m = D_1F80013C;                                  \
        D_1F800182 = D_1F800144;                         \
        while (D_1F800182 != 0) {                        \
            o = *m;                                      \
            D_1F800182--;                                \
            m++;                                         \
            if ((o[0] & 1) && o[2] == 8) {               \
                func_8002423C(e, o);                     \
            }                                            \
        }                                                \
    }
void func_80109378(void)
{
    u8 **l = D_1F800154;
    u8 *e;
    D_1F800183 = D_1F80015C;
    while (D_1F800183 != 0) {
        e = *l;
        D_1F800183--;
        l++;
        if (!(e[0] & 2)) {
            switch (e[2]) {
            case 1:
                if (e[3] == 1) {
                    TOWER_SCAN_LIST(e);
                }
                break;
            case 0:
            case 4:
                TOWER_SCAN_LIST(e);
                break;
            }
        }
    }
}

extern s16 D_1F800144_138c;
extern s16 D_1F800150_058c;
extern u8 **D_1F800148;
void func_8010959C(void)
{
    u8 **q;
    u8 **p;
    u8 *a;
    u8 *b;
    q = D_1F80013C;
    D_1F800183 = *(u8 *)&D_1F800144_138c;
    if (D_1F800150_058c == 0) {
        return;
    }
    while (D_1F800183 != 0) {
        a = *q;
        D_1F800183--;
        q++;
        if (a[0] != 2 && !(a[0] & 8)) {
            p = D_1F800148;
            D_1F800182 = *(u8 *)&D_1F800150_058c;
            while (D_1F800182 != 0) {
                b = *p;
                D_1F800182--;
                p++;
                if ((b[0] & 1) && (b[2] == 12 || b[2] == 31)) {
                    func_8002421C(a, b);
                }
            }
        }
    }
}

extern u8 D_1F800182;
extern u8 D_1F800182;
extern u8 D_1F800182;
extern u8 D_1F800182;
extern u8 D_1F800182;
void func_801096E0(void)
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
            for (D_1F800182 = D_1F800183; D_1F800182 != 0; D_1F800182--) {
            }
        }
    }
}

extern u8 *D_800F2738;
void func_8010978C(void)
{
    u8 *a;
    u8 **p;
    u8 *b;
    if (D_1F800150_058c == 0) {
        return;
    }
    for (a = D_800F2738; a != NULL; a = *(u8 **)(a + 0x24)) {
        if ((a[0] & 1) && a[0x2B] == 0) {
            p = D_1F800148;
            D_1F800182 = *(u8 *)&D_1F800150_058c;
            while (D_1F800182 != 0) {
                b = *p;
                D_1F800182--;
                p++;
                if (b[0] & 1) {
                    switch (b[2]) {
                    case 12:
                        func_80023618(a, b);
                        break;
                    case 18:
                        func_800216B4(a, b, 0);
                        break;
                    }
                }
            }
        }
    }
}

extern u8 D_800BF808[];
extern u8 D_800E7E80[];
/* func_80109D28, inlined */
static inline void inl_80109D28(u8 *a)
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
/* func_80109E70, inlined */
static inline void inl_80109E70(void *a)
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
                func_80109180(a, e);
            } else if (e[2] == 8) {
                func_800205CC(a, e);
            }
        }
    }
}
/* func_80109F34, inlined */
static inline void inl_80109F34(u8 *a)
{
    u8 **p;
    u8 *b;
    p = D_1F800148;
    D_1F800182 = D_1F800150;
    while (D_1F800182 != 0) {
        b = *p;
        D_1F800182--;
        p++;
        if (b[0] & 1) {
            switch (b[2]) {
            case 14:
            case 15:
                func_8001FAE0(a, b);
                break;
            case 12:
                func_80020868(a, b);
                break;
            case 18:
                func_8002311C(a, b);
                break;
            case 31:
                func_80023764(a, b);
                break;
            }
        }
    }
}
/* func_8010A034, inlined */
static inline void inl_8010A034(void)
{
    u8 *a;
    u8 **p;
    u8 *b;
    if (D_1F800144_138c == 0) {
        return;
    }
    for (a = D_800F2738; a != NULL; a = *(u8 **)(a + 0x24)) {
        if ((a[0] & 1) && a[0x2B] == 0) {
            p = D_1F80013C;
            D_1F800182 = *(u8 *)&D_1F800144_138c;
            while (D_1F800182 != 0) {
                b = *p;
                D_1F800182--;
                p++;
                if ((b[0] & 1) && b[2] == 8) {
                    func_80021394(a, b, 0x100);
                }
            }
        }
    }
}
void f_DispatchCourageTowerTombaContacts(void)
{
    u8 *g = D_800E7E80;

    func_8002288C(g);
    switch (g[0]) {
    case 0:
    case 6:
        break;
    case 2:
        if (*(u32 *)(g + 0x158) < 2) {
            inl_80109F34(g);
        }
        break;
    case 1:
    case 3:
    case 4:
    case 5:
    case 7:
    default:
        func_80022760(g);
        inl_80109E70(g);
        if (*(u32 *)(g + 0x158) < 2) {
            inl_80109F34(g);
        }
        break;
    }
    func_80022554();
    inl_8010A034();
    func_8010978C();
    func_80109378();
    func_8010959C();
    func_801096E0();
    inl_80109D28(g);
}

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

void func_80109D98(u8 *a)
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

extern u8 **D_1F80013C;
extern u8 D_1F800144;
extern u8 D_1F800182;
void func_80109E70(void *a)
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
                func_80109180(a, e);
            } else if (e[2] == 8) {
                func_800205CC(a, e);
            }
        }
    }
}

void func_80109F34(u8 *a)
{
    u8 **p;
    u8 *b;
    p = D_1F800148;
    D_1F800182 = D_1F800150;
    while (D_1F800182 != 0) {
        b = *p;
        D_1F800182--;
        p++;
        if (b[0] & 1) {
            switch (b[2]) {
            case 14:
            case 15:
                func_8001FAE0(a, b);
                break;
            case 12:
                func_80020868(a, b);
                break;
            case 18:
                func_8002311C(a, b);
                break;
            case 31:
                func_80023764(a, b);
                break;
            }
        }
    }
}

void func_8010A034(void)
{
    u8 *a;
    u8 **p;
    u8 *b;
    if (D_1F800144_138c == 0) {
        return;
    }
    for (a = D_800F2738; a != NULL; a = *(u8 **)(a + 0x24)) {
        if ((a[0] & 1) && a[0x2B] == 0) {
            p = D_1F80013C;
            D_1F800182 = *(u8 *)&D_1F800144_138c;
            while (D_1F800182 != 0) {
                b = *p;
                D_1F800182--;
                p++;
                if ((b[0] & 1) && b[2] == 8) {
                    func_80021394(a, b, 0x100);
                }
            }
        }
    }
}

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

extern u8 D_800BF816;
extern s32 D_1F800184;
extern u16 D_1F800210;
typedef struct {
    u8 pad0[5];
    u8 x5;
    u8 x6;
    u8 pad7[0x139];
    u16 x140;
    u8 pad142[0x29];
    u8 x16B;
} Area7E80;
extern Area7E80 D_800E7E80_eac2;
void func_8010A2B4(void)
{
    func_80054198(&D_800E7E80_eac2);
    D_800BF816 = 1;
    D_1F800184 = 0;
    D_800E7E80_eac2.x5 = 0x24;
    D_800E7E80_eac2.x6 = 0;
    D_800E7E80_eac2.x16B = 8;
    D_1F800210 = D_800E7E80_eac2.x140;
}

extern u8 D_800E806C;
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

extern u8 D_1F800236;
#define H(p, o) (*(s16 *)((u8 *)(p) + (o)))
void f_UpdateCourageTowerExitDoorSequence(u8 *a)
{
    u8 *t = D_800E7E80;
    switch (a[5]) {
    case 0:
        H(a, 0x40) = 0xF;
        a[7] = 1;
        a[5]++;
        break;
    case 1:
        if (--H(a, 0x40) == -1) {
            a[5]++;
        }
        break;
    case 2:
        if (func_80072F14(a) != 0) {
            a[0] = 1;
            a[5]++;
        }
        break;
    case 3:
        if (a[0x29] != 0 && t[0x29] != 0 && t[0x17B] == 0) {
            a[5]++;
            D_1F800137 = 2;
            if (a[0xBF] != 0) {
                func_80074590(0x17, 0, 0xF);
            }
        }
        break;
    case 4:
        if (func_80072E60(a) != 0) {
            a[5]++;
            D_1F800236 = 1;
            D_800BF808[0x31] = 1;
            D_800BF808[7] = 2;
            H(D_800BF808, 0x32) = 0x106;
        }
        break;
    }
}

INCLUDE_ASM("asm/a0g/nonmatchings/a0g", f_UpdateCourageTowerLaughingCryingDoorSequence);

extern u8 D_800BF80F;
static inline s32 Step(u8 *a)
{
    u8 *s;

    switch (a[5]) {
    case 0:
        a[5] = 1;
        D_800BF80F = 2;
        if (a[0xBF] != 0) {
            func_80074590(0x17, 0, 0xF);
        }
        return 0;
    case 1:
        if (func_80072E60(a) != 0) {
            a[5]++;
        }
        return 0;
    case 2:
        s = D_800BF808;
        if (s[7] == 0) {
            a[5] = 0;
            *(s16 *)(a + 0x56) = *(s16 *)(a + 0x5A);
            s[7] = 1;
            *(s32 *)(s + 0x48) = 1;
            *(s32 *)(s + 0x4C) = *(s16 *)(a + 0x6A);
            return 1;
        }
        return 0;
    }
    return 0;
}

void func_8010AC00(u8 *a)
{
    u8 *s;
    u8 *g;

    switch (a[0x5E]) {
    case 0:
        s = D_800BF808;
        if (*(s32 *)(s + 0x48) != 0) {
            if (*(s32 *)(s + 0x4C) == a[3]) {
                a[0x5E] = 1;
                a[7] = 1;
            }
        } else if (a[0x29] != 0) {
            g = D_800E7E80;
            if (g[0x29] != 0 && g[0x17B] == 0) {
                D_1F800137 = 2;
                a[0x5E] = 2;
            }
        }
        break;
    case 1:
        if (func_8010A4F4(a) != 0) {
            a[0x5E] = 0;
        }
        break;
    case 2:
        if (Step(a) != 0) {
            a[0x5E] = 0;
        }
        break;
    }
}

INCLUDE_ASM("asm/a0g/nonmatchings/a0g", func_8010ADC4);

INCLUDE_ASM("asm/a0g/nonmatchings/a0g", func_8010B08C);

typedef struct { u16 x, y, z; u8 b6, b7; u16 w, h; } Ent0G;
typedef struct { u8 m, k; } Pair0G;
extern Pair0G D_8010D2AC[];
extern Ent0G D_8010D2D4[];
extern u8 D_800E7FF4;
/* func_8010B91C, inlined */
static inline void inl_8010B91C(u8 *a, s16 id)
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
void f_UpdateCourageTowerInteriorEntranceActor(u8 *a)
{
    u8 k;

    switch (a[4]) {
    case 0:
        if (func_80051B70(a, 0xC, D_8010D2AC[a[3]].m) != 0) {
            break;
        }
        a[0xBF] = 1;
        H(a, 0x50) = 0;
        a[4]++;
        a[0x28] |= 0x80;
        H(a, 0x5A) = U(a, 0x56);
        k = D_8010D2AC[a[3]].k;
        if (k != 0) {
            a[0x2A] = k;
            H(a, 0x60) = D_8010D2D4[a[3]].x - U(a, 0x2E);
            H(a, 0x62) = D_8010D2D4[a[3]].y;
            H(a, 0x64) = D_8010D2D4[a[3]].z - U(a, 0x36);
            a[0x5F] = D_8010D2D4[a[3]].b6;
            H(a, 0x82) = D_8010D2D4[a[3]].w;
            H(a, 0x80) = H(a, 0x82) / 2;
            H(a, 0x86) = D_8010D2D4[a[3]].h;
            H(a, 0x84) = H(a, 0x86) / 2;
            a[0] = 1;
        }
        a[0x46] = 1;
        a[0x29] = 0;
        a[0x5E] = 0;
        switch (a[3]) {
        case 0:
            a[0] = 2;
            H(a, 0x50) = 0x400;
            func_80072EFC(a);
            break;
        case 1:
            H(a, 0x66) = 1;
            H(a, 0x68) = 0;
            H(a, 0x6A) = 1;
            break;
        case 2:
            H(a, 0x68) = 1;
            H(a, 0x66) = 0;
            H(a, 0x6A) = 3;
            break;
        case 3:
            H(a, 0x66) = 3;
            H(a, 0x6A) = 2;
            break;
        case 5:
            H(a, 0x66) = 1;
            H(a, 0x68) = 1;
            H(a, 0x6A) = 9;
            break;
        case 7:
            H(a, 0x66) = 1;
            H(a, 0x68) = 0;
            H(a, 0x6A) = 1;
            break;
        case 9:
            H(a, 0x66) = 3;
            H(a, 0x6A) = 5;
            break;
        case 10:
            H(a, 0x66) = 1;
            H(a, 0x68) = 0;
            H(a, 0x6A) = 1;
            break;
        case 11:
            H(a, 0x68) = 1;
            H(a, 0x66) = 0;
            H(a, 0x6A) = 0xD;
            break;
        case 12:
            H(a, 0x66) = 1;
            H(a, 0x68) = 0;
            H(a, 0x6A) = 1;
            break;
        case 13:
            H(a, 0x66) = 3;
            H(a, 0x6A) = 0xB;
            break;
        case 14:
            H(a, 0x66) = 2;
            H(a, 0x6A) = 0x10;
            break;
        case 15:
            H(a, 0x66) = 4;
            H(a, 0x6A) = 1;
            break;
        case 16:
            H(a, 0x66) = 3;
            H(a, 0x6A) = 0xE;
            break;
        case 17:
            H(a, 0x66) = 1;
            H(a, 0x68) = 1;
            H(a, 0x6A) = 0x13;
            break;
        case 4:
        case 6:
        case 8:
        case 18:
            H(a, 0x66) = 0;
            H(a, 0x68) = 0;
            H(a, 0x6A) = 1;
            break;
        case 19:
            H(a, 0x66) = 4;
            H(a, 0x6A) = 0x11;
            a[8] = 0;
            a[0xBF] = 0;
            break;
        }
        break;
    case 1:
        switch (a[3]) {
        case 0:
            f_UpdateCourageTowerExitDoorSequence(a);
            inl_8010B91C(a, 0x86);
            break;
        case 1:
            f_UpdateCourageTowerLaughingCryingDoorSequence(a);
            inl_8010B91C(a, 0x86);
            break;
        case 2:
            f_UpdateCourageTowerLaughingCryingDoorSequence(a);
            inl_8010B91C(a, 0x86);
            break;
        case 3:
            func_8010AC00(a);
            inl_8010B91C(a, 0x87);
            break;
        case 4:
            f_UpdateCourageTowerLaughingCryingDoorSequence(a);
            inl_8010B91C(a, 0x87);
            break;
        case 5:
            f_UpdateCourageTowerLaughingCryingDoorSequence(a);
            inl_8010B91C(a, 0x87);
            break;
        case 6:
            f_UpdateCourageTowerLaughingCryingDoorSequence(a);
            inl_8010B91C(a, 0x87);
            break;
        case 7:
            f_UpdateCourageTowerLaughingCryingDoorSequence(a);
            inl_8010B91C(a, 0x87);
            break;
        case 8:
            f_UpdateCourageTowerLaughingCryingDoorSequence(a);
            inl_8010B91C(a, 0x87);
            break;
        case 9:
            func_8010AC00(a);
            inl_8010B91C(a, 0x88);
            break;
        case 10:
            f_UpdateCourageTowerLaughingCryingDoorSequence(a);
            inl_8010B91C(a, 0x88);
            break;
        case 11:
            f_UpdateCourageTowerLaughingCryingDoorSequence(a);
            inl_8010B91C(a, 0x88);
            break;
        case 12:
            f_UpdateCourageTowerLaughingCryingDoorSequence(a);
            inl_8010B91C(a, 0x88);
            break;
        case 13:
            func_8010AC00(a);
            inl_8010B91C(a, 0x89);
            break;
        case 14:
            func_8010ADC4(a);
            inl_8010B91C(a, 0x89);
            break;
        case 15:
            func_8010B08C(a);
            inl_8010B91C(a, 0x89);
            break;
        case 16:
            if (D_800E7FF4 & 4) {
                func_8010AC00(a);
                inl_8010B91C(a, 0x8A);
            }
            break;
        case 17:
            f_UpdateCourageTowerLaughingCryingDoorSequence(a);
            inl_8010B91C(a, 0x8A);
            break;
        case 18:
            f_UpdateCourageTowerLaughingCryingDoorSequence(a);
            inl_8010B91C(a, 0x8A);
            break;
        case 19:
            func_8010B08C(a);
            inl_8010B91C(a, 0x8B);
            break;
        }
        if (func_8007778C(a) != 0) {
            func_800517F8(a);
        }
        a[0x29] = 0;
        break;
    case 2:
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

s32 func_8010B91C(u8 *a, s16 id)
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

typedef struct { u16 lo; u16 hi; } Fix;
typedef struct {
    Fix at[3];
    Fix pos[3];
    s16 dir[3];
    u8 pad1E[0x2A];
    u8 m[0x20];
} Cam;
typedef struct {
    u8 kind, b1, b2, slot;
    s16 x, y, z;
    u8 mode, padB;
    void *cb;
} Spawn;
typedef struct {
    u8 pad[8];
    s16 x, y, z;
} Pos;
typedef struct {
    u8 pad[8];
    s16 count;
    u8 padA[2];
    u8 *list[15];
} Owner;
extern Spawn *D_8010D588[];
extern Pos D_800BF808_76d5;
typedef struct { u8 x, y, z; s8 t; } Spark;
typedef struct { s16 a, b, c, d; } S8;
typedef struct { s16 x, y, z, pad; } SV;
typedef struct { s16 x, y, z; } V3;
typedef struct { s16 x, y, z, pad; } SVec;
typedef struct { u16 x, p0, y, p1, z, p2; } LVec;
typedef struct { u16 a, b; } Range;
void func_8010B9E0(Owner *a, s32 sel)
{
    Spawn *e;
    u8 *p;
    a->count = 0;
    e = D_8010D588[sel];
    while (e->kind != 0xFF) {
        if (sel == 0 || a->count < 15) {
            switch (e->mode) {
            case 0:
                break;
            case 1:
                D_800BF808_76d5.x = e->x;
                D_800BF808_76d5.y = e->y;
                D_800BF808_76d5.z = e->z;
                break;
            }
            p = func_80072DDC(a, e->kind, e->b1, e->b2);
            if (p != 0) {
                *(s32 *)(p + 0x2C) = e->x << 16;
                *(s32 *)(p + 0x30) = e->y << 16;
                *(s32 *)(p + 0x34) = e->z << 16;
                p[3] = e->slot;
                *(s16 *)(p + 0x54) = 0;
                *(s16 *)(p + 0x56) = 0;
                *(s16 *)(p + 0x58) = 0;
                *(void **)(p + 0x1C) = e->cb;
                if (sel != 0) {
                    a->list[a->count] = p;
                    a->count++;
                }
            }
        }
        e++;
    }
}

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
#define T2_ldv1p(r0)                                                                                                   \
    __asm__ volatile("lw $12, 0x24(%0);"                                                                               \
                     "lwc2 $0, 0x28(%0);"                                                                              \
                     "srl $12, $12, 16;"                                                                               \
                     "mtc2 $12, $1"                                                                                    \
                     :                                                                                                 \
                     : "r"(r0)                                                                                         \
                     : "$12")
#define T2_rtpt() __asm__ volatile(".word 0x4A280030")
#define T2_rtps() __asm__ volatile(".word 0x4A180001")
#define T2_nclip() __asm__ volatile(".word 0x4B400006")
#define T2_avsz3() __asm__ volatile(".word 0x4B58002D")
#define T2_avsz4() __asm__ volatile(".word 0x4B68002E")
#define T2_stflg(r0) __asm__ volatile("cfc2 $12, $31;" "nop;" "sw $12, 0( %0 )" : : "r"(r0) : "$12", "memory")
#define T2_stopz(r0) __asm__ volatile("swc2 $24, 0( %0 )" : : "r"(r0) : "memory")
#define T2_stotz(r0) __asm__ volatile("swc2 $7, 0( %0 )" : : "r"(r0) : "memory")
#define T2_stsxy(r0) __asm__ volatile("swc2 $14, 0( %0 )" : : "r"(r0) : "memory")
#define T2_stsxy3_gt4(r0)                                                                                              \
    __asm__ volatile("swc2 $12, 8( %0 );" "swc2 $13, 20( %0 );" "swc2 $14, 32( %0 )" : : "r"(r0) : "memory")
#define T2_stsxy3_gt3(r0)                                                                                              \
    __asm__ volatile("swc2 $12, 8( %0 );" "swc2 $13, 20( %0 );" "swc2 $14, 32( %0 )" : : "r"(r0) : "memory")
#define T2_stsz0(r0) __asm__ volatile("swc2 $16, 0( %0 )" : : "r"(r0) : "memory")
#define T2_stsz1(r0) __asm__ volatile("swc2 $17, 0( %0 )" : : "r"(r0) : "memory")
#define T2_stsz2(r0) __asm__ volatile("swc2 $18, 0( %0 )" : : "r"(r0) : "memory")
#define T2_stsz3(r0) __asm__ volatile("swc2 $19, 0( %0 )" : : "r"(r0) : "memory")
extern void *D_800BF544;
u32 *func_8010BC40(u32 *f, u32 *ot, s32 n)
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
                    __asm__ volatile("nop");
                    p->rgb2 = (c << 4) & 0xF0F0F0;
                    mode = c >> 24;
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
                        if (sz[3] < sz[4]) {
                            b = sz[5];
                            if (sz[3] < b) {
                                b = sz[3];
                            }
                            e = b;
                        } else {
                            b = sz[5];
                            if (sz[4] < b) {
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
                    if ((u32)(*otz + 399) < 439) {
                        *otz = 40;
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

u32 *func_8010BF28(u32 *f, u32 *ot, s32 n)
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
                        mode = c >> 24;
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
                                if (sz[4] < a) {
                                    a = sz[4];
                                }
                                b = sz[7];
                                if (sz[6] < b) {
                                    b = sz[6];
                                }
                                if (a < b) {
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
                        if ((u32)(*otz + 399) < 439) {
                            *otz = 40;
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

#define gte_SetRotMatrix(r0) __asm__ volatile("lw	$12, 0( %0 );" "lw	$13, 4( %0 );" "ctc2	$12, $0;" "ctc2	$13, $1;" "lw	$12, 8( %0 );" "lw	$13, 12( %0 );" "lw	$14, 16( %0 );" "ctc2	$12, $2;" "ctc2	$13, $3;" "ctc2	$14, $4" : : "r"(r0) : "$12", "$13", "$14")
#define gte_SetTransMatrix(r0) __asm__ volatile("lw	$12, 20( %0 );" "lw	$13, 24( %0 );" "ctc2	$12, $5;" "lw	$14, 28( %0 );" "ctc2	$13, $6;" "ctc2	$14, $7" : : "r"(r0) : "$12", "$13", "$14")
extern u8 D_1F8000F8[];
extern void *D_800ED8C8;
typedef struct {
    u8 pad0[6];
    u8 count;
    u8 pad7[5];
    u32 *tbl;
    u16 list[1];
} PartList;
void func_8010C2A4(PartList *a)
{
    u16 *p = a->list;
    u16 *end;
    void *ot;
    u32 *tbl;
    u32 *e;
    u32 v;
    void *r;
    if (a->count == 0) {
        return;
    }
    end = &a->list[a->count];
    ot = D_800ED8C8;
    tbl = a->tbl;
    gte_SetRotMatrix(D_1F8000F8);
    gte_SetTransMatrix(D_1F8000F8);
    for (; p < end; p++) {
        e = &tbl[*p];
        v = *e;
        r = func_8010BC40(e + 1, ot, v & 0xFF);
        v >>= 16;
        func_8010BF28(r, ot, v & 0xFF);
    }
}

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
u32 *func_8010C3A4(u32 *f, u32 *ot, s32 n)
{
    s32 sz[3];
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
                    mode = c >> 24;
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
                                e = b;
                            } else {
                                b = sz[2];
                                if (b < sz[1]) {
                                    b = sz[1];
                                }
                                e = b;
                            }
                        } else {
                            if (sz[0] < sz[1]) {
                                b = sz[2];
                                if (sz[0] < b) {
                                    b = sz[0];
                                }
                                e = b;
                            } else {
                                b = sz[2];
                                if (sz[1] < b) {
                                    b = sz[1];
                                }
                                e = b;
                            }
                        }
                        *otz = e >> 2;
                    } else {
                        T2_avsz3();
                        T2_stotz(otz);
                    }
                    if ((u32)(*otz + 399) < 439) {
                        *otz = 40;
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
#define T2_rtpt() __asm__ volatile(".word 0x4A280030")
#define T2_rtps() __asm__ volatile(".word 0x4A180001")
#define T2_nclip() __asm__ volatile(".word 0x4B400006")
#define T2_avsz4() __asm__ volatile(".word 0x4B68002E")
#define T2_stflg(r0) __asm__ volatile("cfc2 $12, $31;" "nop;" "sw $12, 0( %0 )" : : "r"(r0) : "$12", "memory")
#define T2_stopz(r0) __asm__ volatile("swc2 $24, 0( %0 )" : : "r"(r0) : "memory")
#define T2_stotz(r0) __asm__ volatile("swc2 $7, 0( %0 )" : : "r"(r0) : "memory")
#define T2_stsxy(r0) __asm__ volatile("swc2 $14, 0( %0 )" : : "r"(r0) : "memory")
#define T2_stsxy3_gt4(r0)                                                                                              \
    __asm__ volatile("swc2 $12, 8( %0 );" "swc2 $13, 20( %0 );" "swc2 $14, 32( %0 )" : : "r"(r0) : "memory")
#define T2_stsz0(r0) __asm__ volatile("swc2 $16, 0( %0 )" : : "r"(r0) : "memory")
#define T2_stsz1(r0) __asm__ volatile("swc2 $17, 0( %0 )" : : "r"(r0) : "memory")
#define T2_stsz2(r0) __asm__ volatile("swc2 $18, 0( %0 )" : : "r"(r0) : "memory")
#define T2_stsz3(r0) __asm__ volatile("swc2 $19, 0( %0 )" : : "r"(r0) : "memory")
extern void *D_800BF544;
u32 *func_8010C664(u32 *f, u32 *ot, s32 n)
{
    s32 sz[4];
    s32 *otz = (s32 *)0x1F800004;
    T2PolyGT4 *p = D_800BF544;
    s32 *flg = (s32 *)0x1F800000;
    u32 c;
    u32 mode;
    s32 b, a, v, e;
    u32 *o;

    while (n-- != 0) {
        T2_ldv3p(f);
        c = f[0];
        p->rgb0 = c & 0xFFF0F0F0;
        T2_rtpt();
        p->rgb1 = (c << 4) & 0xF0F0F0;
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
                        p->uv1 = f[3];
                        mode = c >> 24;
                        if (mode != 0) {
                            T2_stsz0(&sz[0]);
                            T2_stsz1(&sz[1]);
                            T2_stsz2(&sz[2]);
                            T2_stsz3(&sz[3]);
                            do {
                                if (mode == 1) {
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
                                }
                                *otz = b >> 2;
                            } while (0);
                        } else {
                            T2_avsz4();
                            do {
                                T2_stotz(otz);
                            } while (0);
                            do {
                                if ((u32)(*otz + 399) < 439) {
                                    *otz = 40;
                                }
                                e = *otz >> 10;
                                *otz = (*otz >> e) + (e << 9);
                            } while (0);
                            do {
                                if ((u32)(*otz - 4) >= 0x7FC) {
                                    *otz = -1;
                                }
                            } while (0);
                            if (*otz >= 0) {
                                do {
                                    o = ot + *otz;
                                    p->tag = *o | 0x0C000000;
                                    *o = (u32)p;
                                } while (0);
                                v = f[4];
                                p->uv2 = v;
                                p->uv3 = (u32)v >> 16;
                                p++;
                            }
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

void func_8010C9B4(u32 *p, void *b)
{
    u32 lo = *p;
    u32 packed;

    packed = lo;
    lo = packed & 0xFFFF;
    p += 4;
    func_8010C664(func_8010C3A4(p, b, lo), b, packed >> 16);
}

typedef struct {
    s16 vx, vy, vz, pad;
} T2SVec;
typedef struct {
    u8 pad0[2];
    s16 x;
    u8 pad4[6];
    s16 y;
    u8 padC[0x14];
    s16 rx;
    u16 ry;
} T2CamD0;
extern T2CamD0 D_1F8000D0;
extern s32 D_800A3F90;
extern s32 D_800A3F94;
void func_8010C9FC(u8 *a)
{
    T2SVec v0, v1, v2;
    T2CamD0 *c = &D_1F8000D0;
    s32 ang, r, dx, dz;
    u16 t;

    t = c->ry;
    D_800A3F90 = 0x2F80;
    ang = (-(s16)t - D_800A3F94) & 0xFFF;
    v0.vx = c->x;
    v0.vy = c->y;
    v1.vx = v0.vx + ((func_80083E80(ang) * D_800A3F90) >> 12);
    v1.vy = v0.vy + ((func_80083F50(ang) * D_800A3F90) >> 12);
    ang = (D_800A3F94 - (s16)c->ry) & 0xFFF;
    v2.vx = v0.vx + ((func_80083E80(ang) * D_800A3F90) >> 12);
    v2.vy = v0.vy + ((func_80083F50(ang) * D_800A3F90) >> 12);
    r = abs(func_80083E80(c->rx));
    dx = (func_80083E80(-(s16)c->ry) * r) >> 12;
    dz = (func_80083F50(-(s16)c->ry) * r) >> 12;
    dx = (dx * D_800A3F90 * 5) >> 16;
    dz = (dz * D_800A3F90 * 5) >> 16;
    v1.vx -= dx;
    v0.vx -= dx;
    v1.vy -= dz;
    v0.vy -= dz;
    v2.vx -= dx;
    v2.vy -= dz;
    v0.vx /= 640;
    v0.vy /= 640;
    v1.vx /= 640;
    v1.vy /= 640;
    v2.vx /= 640;
    v2.vy /= 640;
    a[6] = 0;
    func_8010CCDC(a, &v0, &v1, &v2);
}

typedef struct {
    s16 vx, vy;
} T2Pt16;
extern s32 D_800ECF58[];
typedef struct { u8 pad0[0x10]; s16 list[1]; } TriGrid;
#define TRI_ROW(L, R, N)                                                 \
    {                                                                    \
        s32 xe = (R) >> 16;                                              \
        s32 xs = (L) >> 16;                                              \
        s32 x;                                                           \
        if (y >= 0 && y < *(s16 *)(g + 0xA)) {                          \
            s16 *cell;                                                   \
            if (xe >= *(s16 *)(g + 8)) {                                 \
                xe = *(s16 *)(g + 8) - 1;                                \
            }                                                            \
            x = xs;                                                      \
            if (x < 0) {                                                 \
                x = 0;                                                   \
            }                                                            \
            cell = (s16 *)D_800ECF58[8];                                 \
            cell += 2;                                                   \
            cell += x * *(s16 *)(g + 0xA) + y;                           \
            while (x <= xe) {                                            \
                if (*cell != -1) {                                       \
                    u8 n = g[6];                                         \
                    if (n < 0xFE) {                                      \
                        g[6] = n + 1;                                    \
                        ((TriGrid *)g)->list[n] = *cell;                  \
                    }                                                    \
                }                                                        \
                x++;                                                     \
                cell += *(s16 *)(g + 0xA);                               \
            }                                                            \
        }                                                                \
    }
void func_8010CCDC(u8 *g, T2Pt16 *p0, T2Pt16 *p1, T2Pt16 *p2)
{
    s32 x0, y0, x1, y1, x2, y2, t;
    s32 dx01, dx02, dy01, dy02;
    s32 l, r, s01, s12, s02, cross, y;

    x0 = p0->vx;
    y0 = p0->vy;
    x1 = p1->vx;
    y1 = p1->vy;
    x2 = p2->vx;
    y2 = p2->vy;
    if (y1 == y0 && y1 == y2) {
        return;
    }
    if (y1 < y0) {
        t = x0; x0 = x1; x1 = t;
        t = y0; y0 = y1; y1 = t;
    }
    if (y2 < y0) {
        t = x0; x0 = x2; x2 = t;
        t = y0; y0 = y2; y2 = t;
    }
    if (y2 < y1) {
        t = x1; x1 = x2; x2 = t;
        t = y1; y1 = y2; y2 = t;
    }
    dx01 = x1 - x0;
    dx02 = x2 - x0;
    dy01 = y1 - y0;
    dy02 = y2 - y0;
    if (y1 == y0) {
        if (x0 < x1) {
            l = x0 << 16;
            r = x1 << 16;
        } else {
            l = x1 << 16;
            r = x0 << 16;
        }
        s01 = 0;
    } else {
        r = l = x0 << 16;
        s01 = (dx01 << 16) / dy01;
    }
    r += 0x10000;
    if (y1 == y2) {
        s12 = 0;
    } else {
        s12 = ((x2 - x1) << 16) / (y2 - y1);
    }
    s02 = (dx02 << 16) / dy02;
    cross = -dy02 * dx01 + dx02 * dy01;
    if (cross > 0) {
        for (y = y0; y < y1; y++) {
            TRI_ROW(l, r, 0);
            l += s01;
            r += s02;
        }
        for (; y <= y2; y++) {
            TRI_ROW(l, r, 1);
            l += s12;
            r += s02;
        }
    } else {
        for (y = y0; y < y1; y++) {
            TRI_ROW(l, r, 2);
            r += s01;
            l += s02;
        }
        for (; y <= y2; y++) {
            TRI_ROW(l, r, 3);
            l += s02;
            r += s12;
        }
    }
}

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

extern u16 D_8010D5C0[][2];
extern s32 D_1F80021C;
void f_PlayCourageTowerStreamedAudioSegment(s16 a, s16 b)
{
    s32 base;
    u16 *t;
    if (a == 0) {
        t = D_8010D5C0[0];
        base = D_1F80021C;
        base += t[b * 2] * 32;
        func_8001D2A8(3, base, base + (t[b * 2 + 1] + 1) * 32, 0);
    }
}

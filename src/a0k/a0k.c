#include "common.h"
#include "game.h"
#include "m2c.h"
#include "gte.h"

extern u8 D_1F800137;
extern u8 D_800BF840;
extern u8 D_800E7E81;

void func_801095C8(u8 *a) {
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

void func_801095C8();
u8 *func_80109788(void)
{
    u8 *a = func_8007A980(0, 3, 1);

    if (a == NULL) {
        return NULL;
    }
    *(void **)(a + 0x1C) = func_801095C8;
    a[2] = 1;
    a[0x28] |= 0x80;
    return a;
}

extern s32 D_1F80009C_baed;
extern s16 D_1F80018E;
extern u8 *D_1F800184;
extern u16 D_1F80008C;
extern u8 D_1F800137;
void func_801097DC(u8 *a, u8 *b)
{
    s16 ang;

    if (func_8002300C(a, b, *(s16 *)(b + 0x80) + 0x96) == 0) {
        return;
    }
    ang = *(u16 *)&D_1F80009C_baed & 0xFFF;
    if (!(*(s16 *)(a + 0x17E) & 0x8000) && D_1F800137 == 0 && !(b[0] & 2)) {
        if (abs((s16)((ang - *(u16 *)(a + 0x56)) << 4)) < 0x2001) {
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
void func_8010996C(u8 *a, u8 *b)
{
    s16 ang;

    if (func_8002300C(a, b, *(s16 *)(b + 0x80) + 0x96) == 0) {
        return;
    }
    ang = *(u16 *)&D_1F80009C_baed & 0xFFF;
    if (!(*(u16 *)(a + 0x17E) & 0x200) && D_1F800137 == 0 && !(b[0] & 2)) {
        if (abs((s16)((ang - *(u16 *)(a + 0x56)) << 4)) < 0x2001) {
            D_1F80018E = 0x1200;
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

extern s16 D_1F80018C;
void func_80109AC8(u8 *a, u8 *b)
{
    s32 *ang;
    s32 d;
    s32 m;

    if (func_8002300C(a, b, *(s16 *)(b + 0x80)) == 0) {
        return;
    }
    ang = &D_1F80009C_baed;
    {
        s32 temp_s0 = (s32) (func_80083F50(*ang + 0x800) * (M2C_FIELD(a, s16 *, 0x80) + M2C_FIELD(b, s16 *, 0x80))) >> 0xC;
        s32 temp_lo = func_80083E80(*ang + 0x800) * (M2C_FIELD(a, s16 *, 0x80) + M2C_FIELD(b, s16 *, 0x80));
        m = D_1F800137;
        MEMBER_AT(s16, a, 0x2E) = (s16) (M2C_FIELD(b, u16 *, 0x2E) + temp_s0);
        M2C_FIELD(a, s16 *, 0x36) = (s16) (M2C_FIELD(b, u16 *, 0x36) - (temp_lo >> 0xC));
    }
    if (m != 0) {
        return;
    }
    {
        u16 w = *(u16 *)(a + 0x56);
        s32 v = *(u16 *)ang & 0xFFF;

        D_1F80018C = v;
        d = abs((s16)((v - w) << 4));
    }
    if (d < 0x4001) {
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

extern u16 D_1F80009C_baed_759c;
extern void func_80083DE0(void *, s32, s32, s32, s32);
void func_80109C0C(u8 *a, u8 *b)
{
    s16 ang;

    if (*(s16 *)(a + 0x17E) & 0x200) {
        if (func_8002300C(a, b, *(s16 *)(b + 0x80)) == 0) {
            return;
        }
        ang = D_1F80009C_baed_759c & 0xFFF;
    } else {
        if (func_8002300C(a, b, *(s16 *)(b + 0x80) * 2) == 0) {
            return;
        }
        b[0x2B] = 1;
        if (D_1F80008C > *(s16 *)(a + 0x80) + *(s16 *)(b + 0x80) + 0x5A) {
            return;
        }
        b[0x2B] = 2;
        ang = D_1F80009C_baed_759c & 0xFFF;
        if (D_1F800137 == 0 && !(b[0] & 2) && abs((s16)((ang - *(u16 *)(a + 0x56)) << 4)) < 0x2001) {
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

extern u8 **D_1F80013C;
extern u8 D_1F800144;
extern u8 D_1F800182;
extern u8 **D_1F800148;
extern u8 D_1F800150;
void func_80109DBC(u8 *a)
{
    u8 **l;
    u8 *e;

    l = D_1F800148;
    D_1F800182 = D_1F800150;
    while (D_1F800182 != 0) {
        e = *l;
        D_1F800182--;
        l++;
        if (e[0] & 1) {
            switch (e[2]) {
            case 14:
            case 15:
            case 0x39:
                func_800241FC(a, e);
                break;
            }
        }
    }
    l = D_1F80013C;
    D_1F800182 = D_1F800144;
    while (D_1F800182 != 0) {
        e = *l;
        D_1F800182--;
        l++;
        if (e[0] & 1) {
            if (e[0xC] == 9) {
                func_800241FC(a, e);
            } else if (e[2] == 8) {
                func_8002423C(a, e);
            }
        }
    }
}

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_80109F14);

extern u8 **D_1F800154;
extern u8 D_1F80015C;
extern s32 D_800BF85C;
typedef struct {
    u8 pad[0xA];
    s16 count;
    u8 *entries;
    u32 pending;
    u32 done;
} RewardSet;
/* func_8010A550, inlined */
static inline void inl_8010A550(void *a, u8 *b)
{
    RewardSet *r = (RewardSet *)(b + 0x60);
    u8 *e = r->entries;
    s32 i;
    u32 bit;

    for (i = 0; i < r->count; i++, e += 0x10) {
        bit = 1 << i;
        if ((r->pending & bit) && func_80109F14(a, e)) {
            r->done |= bit;
            r->pending &= ~bit;
            func_801100E4(b, e, 0);
            return;
        }
    }
}
void func_8010A034(u8 *a)
{
    u8 **l;
    u8 *e;

    if (*(s16 *)(a + 0x16E) == 0) {
        return;
    }
    if (((s8 *)D_800BF808)[5] != 0) {
        return;
    }
    if (*(u16 *)(a + 0x17E) & 0x200) {
        return;
    }
    l = D_1F800154;
    D_1F800182 = D_1F80015C;
    while (D_1F800182 != 0) {
        e = *l;
        D_1F800182--;
        l++;
        if (e[0] != 1) {
            continue;
        }
        switch (e[2]) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 7:
            func_80022060(a, e);
            break;
        case 5:
        case 6:
            break;
        case 8:
            if (D_800BF85C == 2) {
                inl_8010A550(a, e);
            }
            break;
        }
    }
}

extern u8 D_1F800183;
extern u8 D_800E7E80[];
/* func_8010A4A0, inlined */
static inline void inl_8010A4A0(void)
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
            case 0:
            case 4:
            case 5:
                func_80109DBC(e);
                break;
            }
        }
    }
}
/* func_8010A62C, inlined */
static inline void inl_8010A62C(void *a)
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
                func_80109C0C(a, e);
            } else if (e[2] == 8) {
                func_801097DC(a, e);
            }
        }
    }
}
static inline void inl_list148_8010A1F8(u8 *a)
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
                func_80109AC8(a, b);
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
            case 0x4B:
                func_8010996C(a, b);
                break;
            }
        }
    }
}
void func_8010A1F8(void)
{
    u8 *g = D_800E7E80;

    func_8002288C(g);
    switch (g[0]) {
    case 1:
    case 3:
    case 4:
    case 5:
    case 7:
        func_8010A034(g);
        inl_8010A62C(g);
        inl_list148_8010A1F8(g);
        break;
    case 0:
    case 2:
    case 6:
        break;
    }
    inl_8010A4A0();
}

void func_8010A498(void) {
}

void func_8010A4A0(void)
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
            case 0:
            case 4:
            case 5:
                func_80109DBC(e);
                break;
            }
        }
    }
}

void func_8010A550(void *a, u8 *b)
{
    RewardSet *r = (RewardSet *)(b + 0x60);
    u8 *e = r->entries;
    s32 i;
    u32 bit;

    for (i = 0; i < r->count; i++, e += 0x10) {
        bit = 1 << i;
        if ((r->pending & bit) && func_80109F14(a, e)) {
            r->done |= bit;
            r->pending &= ~bit;
            func_801100E4(b, e, 0);
            return;
        }
    }
}

void func_8010A62C(void *a)
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
                func_80109C0C(a, e);
            } else if (e[2] == 8) {
                func_801097DC(a, e);
            }
        }
    }
}

void func_8010A6F0(u8 *a)
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
                func_80109AC8(a, b);
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
            case 0x4B:
                func_8010996C(a, b);
                break;
            }
        }
    }
}

typedef struct { u16 acc, inc, max, dec; } SpeedTbl;
extern SpeedTbl D_800A455C[];
extern SpeedTbl D_800A4574;
extern u16 D_1F8000F2;
#define S16(o) (*(s16 *)(a + (o)))
#define U16(o) (*(u16 *)(a + (o)))
typedef struct { s16 pad; s16 x; s16 pad2; s16 y; s16 pad3; s16 z; } PosV;
extern u8 D_800BF80E_58ec;
extern u16 D_1F800192;
extern u8 D_1F80027A;
extern u8 D_800BF80A;
static inline void fall_step(u8 *a)
{
    func_8010C4C4(a);
    if (a[0x29] != 0) {
        if (*(s16 *)(a + 0x50) > 0x1400) {
            func_80074590(3, 0, 0);
        }
        *(s16 *)(a + 0x50) = 0;
    } else {
        *(s16 *)(a + 0x50) += 0x360;
        if (*(s16 *)(a + 0x50) > 0x3E00) {
            *(s16 *)(a + 0x50) = 0x3E00;
        }
        *(s32 *)(a + 0x30) += *(s16 *)(a + 0x50) << 8;
    }
}
s32 func_8010A828(s32 arg0, s32 arg1, s32 arg2) {
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

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_8010A99C);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_8010AB3C);

#define S16F(p, o) (((struct { u8 pad[o]; s16 v; } *)(p))->v)
extern u8 D_1F8000D0[];
extern s16 D_1F8000EE;
extern u8 D_800E8008[];
extern u8 D_1F800236;
/* func_8010B470, inlined */
static inline void inl_8010B470(u8 *a, s16 ang)
{
    u8 *t = D_800E7E80;
    u8 *c;
    s16 r;
    s16 x;

    r = -(func_80083F50(*(s16 *)(a + 0xA)) * (*(s16 *)((c = D_1F8000D0) + 0x1E) + *(s32 *)(a + 0x58))) >> 12;
    x = *(s16 *)(t + 0x2E) + ((func_80083F50(ang) * r) >> 12);
    *(s16 *)(c + 0xA) = *(s16 *)(t + 0x36) - ((func_80083E80(ang) * r) >> 12);
    *(s16 *)(c + 0x2) = x;
    a[0x66] |= 1;
}
/* func_8010B54C, inlined */
static inline void inl_8010B54C(u8 *a, u8 *b)
{
    s32 d = ((*(u16 *)(b + 0x56) - *(u16 *)(a + 0x52)) << 20) >> 8;

    if (*(s16 *)(b + 0x44) != 0) {
        *(s16 *)(a + 0x52) += d / ((*(s16 *)(b + 0x15E) << 12) / (*(s16 *)(b + 0x44) >> 3));
    }
}
/* func_8010B5EC, inlined */
static inline void inl_8010B5EC(u8 *a, s16 b)
{
    s16 v;
    s16 y;
    s16 d;
    u8 *c;

    if (a[0x64] == 1) {
        v = -(func_80083E80(*(s16 *)(a + 0xA)) * *(s16 *)(a + 0x6C)) >> 12;
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
/* func_8010B5EC, inlined (base offset form) */
static inline void inl_8010B5EC_c(u8 *a, s16 b)
{
    s16 v;
    s16 y;
    s16 d;
    u8 *c;

    if (a[0x64] == 1) {
        v = -(func_80083E80(*(s16 *)(a + 0xA)) * *(s16 *)(a + 0x6C)) >> 12;
    } else {
        v = (func_80083E80(*(s16 *)(a + 0xA)) * (*(s16 *)(D_1F8000D0 + 0x1E) + *(s32 *)(a + 0x58))) >> 12;
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
void func_8010AD0C(u8 *a)
{
    u8 *c;
    u8 *t = D_800E7E80;
    u8 *e;
    s16 v[8];

    switch (a[2]) {
    case 0:
        e = D_800E8008;
        *(s16 *)(e + 0x6C) = 0x500;
        *(s16 *)(e + 0x6E) = 0xA0;
        c = D_1F8000D0;
        a[0x65] = 0;
        *(s32 *)(a + 0x58) = 0;
        *(s16 *)(c + 0x1E) = -0x7D0;
        *(s16 *)(a + 0x68) = 0;
        *(s16 *)(a + 0x6A) = 0;
        a[5] = 0;
        a[3] = 0;
        *(s16 *)(a + 0xA) = 0x100;
        *(s16 *)(a + 0x52) = *(s16 *)(t + 0x56) + 0x800;
        S16F(a, 0xE) = *(s16 *)(t + 0x32) + ((func_80083E80(*(s16 *)(a + 0xA)) * *(s16 *)(c + 0x1E)) >> 12);
        if ((u32)(D_1F800236 - 5) < 2) {
            *(s16 *)(a + 0xA) = 0x160;
            *(s32 *)(a + 0x58) = 0x320;
            a[2] = 5;
            inl_8010B470(a, (*(s16 *)(a + 0x52) + 0x800) & 0xFFF);
            inl_8010B5EC_c(a, *(s16 *)(a + 0x3E));
            func_8006E3B0(a, t + 0x2C);
            break;
        }
        if (D_800BF870.pad1[0] < 4) {
            a[2]++;
            inl_8010B470(a, (*(s16 *)(a + 0x52) + 0x800) & 0xFFF);
        } else {
            *(s16 *)(c + 0x1E) = -0x708;
            *(s16 *)(a + 0xA) = 0;
            a[2] = 2;
            if (D_800BF870.pad1[0] == 5) {
                *(s16 *)(a + 0x52) = *(s16 *)(t + 0x56);
            }
            inl_8010B470(a, *(s16 *)(a + 0x52) & 0xFFF);
        }
        break;
    case 1:
        func_8006E3F4(a, t + 0x2C);
        v[1] = 0x3DB8;
        v[3] = -0x9B5;
        v[5] = 0x1FBA;
        func_8006CEC4(D_1F8000D0, v, 0);
        break;
    case 2:
    case 3:
        if (D_800BF85C == 0) {
            *(s16 *)(a + 0x52) = func_8010A828(*(s16 *)(t + 0x140), *(s16 *)(a + 0x52), 1);
        } else {
            inl_8010B54C(a, t);
        }
        func_8010AB3C(a, t, (s16)(*(s16 *)(a + 0x52) + 0x800));
        func_8006D02C(a);
        break;
    case 4:
        a[2]++;
        func_8006CBA8(t + 0x2C);
        *(s32 *)(a + 0x58) = 0x320;
        *(s16 *)(a + 0xA) = 0x160;
    case 5:
        func_8006E3F4(a, t + 0x2C);
        func_8010A99C(a, t, (s16)(*(s16 *)(a + 0x52) + 0x800));
        inl_8010B5EC(a, *(s16 *)(a + 0x3E));
        if (D_1F800137 == 0) {
            a[2] = 1;
            a[3] = 0;
        }
        break;
    }
}

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_8010B2F0);

void func_8010B460(void) {
}

void func_8010B468(void) {
}

void func_8010B470(u8 *a, s16 ang)
{
    u8 *t = D_800E7E80;
    u8 *c;
    s16 r;
    s16 x;

    r = -(func_80083F50(*(s16 *)(a + 0xA)) * (*(s16 *)((c = D_1F8000D0) + 0x1E) + *(s32 *)(a + 0x58))) >> 12;
    x = *(s16 *)(t + 0x2E) + ((func_80083F50(ang) * r) >> 12);
    *(s16 *)(c + 0xA) = *(s16 *)(t + 0x36) - ((func_80083E80(ang) * r) >> 12);
    *(s16 *)(c + 0x2) = x;
    a[0x66] |= 1;
}

void func_8010B54C(u8 *a, u8 *b)
{
    s32 d = ((*(u16 *)(b + 0x56) - *(u16 *)(a + 0x52)) << 20) >> 8;

    if (*(s16 *)(b + 0x44) != 0) {
        *(s16 *)(a + 0x52) += d / ((*(s16 *)(b + 0x15E) << 12) / (*(s16 *)(b + 0x44) >> 3));
    }
}

void func_8010B5EC(u8 *a, s16 b)
{
    s16 v;
    s16 y;
    s16 d;
    u8 *c;

    if (a[0x64] == 1) {
        v = -(func_80083E80(*(s16 *)(a + 0xA)) * *(s16 *)(a + 0x6C)) >> 12;
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

extern s16 D_1F8001C6;
extern u8 D_800BF80F;
void func_8010B6D0(u8 *a, u8 *b)
{
    if (D_1F8001C6 != 0) {
        *(s16 *)(a + 0x52) = func_8010A828(*(s16 *)(b + 0x56), *(s16 *)(a + 0x52), 2);
    } else if (D_800BF80F == 0 && b[0x17A] == 0) {
        *(s16 *)(a + 0x52) = func_8010A828(*(s16 *)(b + 0x56), *(s16 *)(a + 0x52), 1);
    }
}

void func_8010B744(void)
{
    CameraState *c = &g_CameraState;

    c->unk6C = 0x500;
    c->unk6E = 0xA0;
}

typedef struct { s16 a, b, c, d; } SpeedRow8010A8D0;
extern SpeedRow8010A8D0 D_800A455C_c872[];
extern SpeedRow8010A8D0 D_800A4574_8b42;
#define B8(o) (*(u8 *)(a + (o)))
#define I16(o) (*(s16 *)(a + (o)))
#define W16(o) (*(u16 *)(a + (o)))
extern s32 D_8011FC18[];
void func_8010B760(u8 *a) {
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

void func_8010BB48(u8 *a)
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

void func_8010BD54(u8 *a)
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

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_8010BEF8);

typedef struct { s16 x, y, z, pad; } AreaSVec;
typedef struct {
    u16 type;
    u8 pad2[6];
    u8 mag0;
    u8 mag1;
    u8 x;
    u8 y;
} AreaPadAnalog;
extern AreaPadAnalog D_800ECF48;
extern u16 D_800ECF54;
typedef struct { u8 pad0[7]; u8 unk7; u8 pad8[0x29]; u8 unk31; s16 unk32; } AreaState808_7;
void func_8010C160(u8 *a) {
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

void func_8010C2E8(u8 *a)
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

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_8010C4C4);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_8010C674);

void func_8010C7D4(u8 *a)
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
        D_800BF80E_58ec = 0;
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
            D_800BF80E_58ec = 1;
            a[4] = 4;
            a[5] = 0x20;
            a[6] = 0;
            a[7] = 0;
        }
        break;
    }
}

extern s8 D_800BF80E;
void func_8010C9D8(void *arg0) {
    s16 temp_v0;
    u16 temp_v0_3;
    u8 temp_v0_2;
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 6);
    switch (temp_v1) {                              /* irregular */
    case 0:
        M2C_FIELD(arg0, s8 *, 0x146) = 0;
        func_80053D90(arg0);
        func_80054198(arg0);
        func_80054D14(arg0, 0xE0, 4);
        func_80074590(0x3A, 0, 0);
        M2C_FIELD(arg0, u8 *, 0x167) = 0x1EU;
        M2C_FIELD(arg0, s8 *, 7) = 0;
        M2C_FIELD(arg0, u16 *, 0x40) = 7U;
        M2C_FIELD(arg0, s16 *, 0x42) = 0;
        M2C_FIELD(arg0, u8 *, 6) = (u8) (M2C_FIELD(arg0, u8 *, 6) + 1);
        /* fallthrough */
    case 1:
        M2C_FIELD(arg0, s8 *, 0x14B) = 3;
        M2C_FIELD(arg0, u8 *, 0x147) = (u8) (M2C_FIELD(arg0, u8 *, 0x147) & 0x7F);
        func_8010B760(arg0);
        func_80054E80(arg0, 0);
        func_8010C674(arg0, 0);
        func_80076D68(arg0);
        M2C_FIELD(arg0, u16 *, 0x32) = (u16) (M2C_FIELD(arg0, u16 *, 0x32) + 0xA);
        func_8010C4C4(arg0);
        if ((M2C_FIELD(arg0, u8 *, 0x29) != 0) && (func_8010BD54(arg0), (M2C_FIELD(arg0, u8 *, 0x29) != 0))) {
            if (M2C_FIELD(arg0, s16 *, 0x50) >= 0x1401) {
                func_80074590(3, 0, 0);
            }
            M2C_FIELD(arg0, s16 *, 0x50) = 0;
        } else {
            temp_v0 = (u16) M2C_FIELD(arg0, s16 *, 0x50) + 0x360;
            M2C_FIELD(arg0, s16 *, 0x50) = temp_v0;
            if (temp_v0 >= 0x3E01) {
                M2C_FIELD(arg0, s16 *, 0x50) = 0x3E00;
            }
            M2C_FIELD(arg0, s32 *, 0x30) = (s32) (M2C_FIELD(arg0, s32 *, 0x30) + (M2C_FIELD(arg0, s16 *, 0x50) << 8));
        }
        temp_v0_2 = M2C_FIELD(arg0, u8 *, 0x167);
        if (temp_v0_2 == 0) {
            M2C_FIELD(arg0, s8 *, 5) = 0;
            M2C_FIELD(arg0, u8 *, 6) = 0U;
            return;
        }
        M2C_FIELD(arg0, u8 *, 0x167) = (u8) (temp_v0_2 - 1);
        return;
    case 2:
        D_800BF80E = 0;
        M2C_FIELD(arg0, s8 *, 0x146) = 0;
        func_80053D90(arg0);
        func_80054198(arg0);
        func_80054D14(arg0, 0xDF, 4);
        func_80074590(0x3A, 0, 0);
        M2C_FIELD(arg0, u16 *, 0x40) = 0x1EU;
        M2C_FIELD(arg0, u8 *, 6) = (u8) (M2C_FIELD(arg0, u8 *, 6) + 1);
        return;
    case 3:
        func_80076D68(arg0);
        func_800551C4(arg0);
        temp_v0_3 = M2C_FIELD(arg0, u16 *, 0x40) - 1;
        M2C_FIELD(arg0, u16 *, 0x40) = temp_v0_3;
        if ((temp_v0_3 << 0x10) == 0) {
            D_800BF80E = 1;
            M2C_FIELD(arg0, s8 *, 4) = 4;
            M2C_FIELD(arg0, s8 *, 5) = 0x20;
            M2C_FIELD(arg0, u8 *, 6) = 0U;
            M2C_FIELD(arg0, s8 *, 7) = 0;
        }
        return;
    }
}

void func_8010CC34(u8 *a)
{
    u16 ang;

    switch (a[6]) {
    case 0:
        *(s16 *)(a + 0x58) = 0;
        D_800BF80E_58ec = 0;
        a[6]++;
        func_80054D14(a, 2, 0);
    case 1:
        ang = D_1F800192 & 0xFFF;
        if ((*(s16 *)(a + 0x56) = func_800776F8(ang, *(s16 *)(a + 0x56), 0x100)) == ang) {
            a[6]++;
            D_800BF80E_58ec = 1;
        }
        break;
    case 2:
        break;
    }
    func_80076D68(a);
    func_8010C4C4(a);
    if (a[0x29] != 0) {
        if (*(s16 *)(a + 0x50) > 0x1400) {
            func_80074590(3, 0, 0);
        }
        *(s16 *)(a + 0x50) = 0;
        return;
    }
    *(s16 *)(a + 0x50) += 0x360;
    if (*(s16 *)(a + 0x50) > 0x3E00) {
        *(s16 *)(a + 0x50) = 0x3E00;
    }
    *(s32 *)(a + 0x30) += *(s16 *)(a + 0x50) << 8;
}

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_8010CD70);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_8010CF30);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_8010D3C4);

void func_8010D550(u8 *a)
{
    s32 r = func_80076D68(a);

    switch (a[6]) {
    case 0: {
        u8 *t;

        D_800BF80E_58ec = 0;
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
                D_800BF80E_58ec = D_1F800137;
                a[5] = 0x22;
            } else {
                a[5] = 0x20;
            }
            a[6] = 0;
        }
        break;
    }
    func_8010C4C4(a);
    if (a[0x29] != 0) {
        if (*(s16 *)(a + 0x50) > 0x1400) {
            func_80074590(3, 0, 0);
        }
        *(s16 *)(a + 0x50) = 0;
        return;
    }
    *(s16 *)(a + 0x50) += 0x360;
    if (*(s16 *)(a + 0x50) > 0x3E00) {
        *(s16 *)(a + 0x50) = 0x3E00;
    }
    *(s32 *)(a + 0x30) += *(s16 *)(a + 0x50) << 8;
}

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_8010D750);

extern s16 D_1F80019E;
extern u8 D_800BFE55;
extern u16 D_1F80017C;
extern u16 D_1F800210;
extern u16 D_800BF812;
#define S16(p, o) (*(s16 *)((u8 *)(p) + (o)))
void func_8010DE18(u8 *a)
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

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_8010E0F4);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_8010E3B8);

void func_8010E60C(u8 *a)
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

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_8010E7EC);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_8010EB6C);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_8010ED6C);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_8010EF80);

extern s16 D_1F800240;
void func_8010DE18(u8 *a);
u8 *func_80109788(void);
void func_8010F544(u8 *a)
{
    u8 *g;
    u8 *q;
    u8 n;

    a[1] = 1;
    *(s16 *)(a + 0x56) = 0xC00;
    *(s16 *)(a + 0x140) = 0xC00;
    g = (u8 *)&D_800BF870;
    *(s16 *)(a + 0x6A) = 0;
    *(s16 *)(a + 0x58) = 0;
    *(s16 *)(a + 0x172) = 0;
    n = g[1];
    if (n < 4) {
        ((void (*)(u8 *))func_80109788)(a);
        q = func_8003315C(a);
        if (q != NULL) {
            *(void **)(q + 0x1C) = func_8010DE18;
        }
        func_80054D14(a, 2, 0);
    } else {
        D_1F800137 = 2;
        if (n == 4) {
            D_1F800240 = 0x320;
            g[0x1E3] = 0;
        } else {
            D_1F800240 = 0;
            g[0x1E3] = 2;
        }
        *(s16 *)(a + 0x15E) = 0x3C00;
        *(void **)(a + 0x10) = func_80112F34(a);
        a[5] = 2;
        a[6] = 0;
        a[7] = 0;
    }
    D_1F8001C6 = 0;
    func_80057DC0(a, 0);
    *(s16 *)(a + 0x32) += 0x46;
}

extern u16 D_800E7E68;
extern u16 D_1F800166;
extern u16 D_1F800190;
void func_8010F654(u8 *a) {
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
        func_8010ED6C(a);
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
        func_8010EF80(a);
        func_800597AC(a);
        D_800E7E68 = held;
        D_800ECF54 = pad;
        break;
    }
}

void func_8010F7B0(s16 *a, s16 m)
{
    if (a[1] < m + 0x16A8) {
        a[1] = m + 0x16A8;
    } else if (0x6658 - m < a[1]) {
        a[1] = 0x6658 - m;
    }
    if (a[5] < m + 0x16A8) {
        a[5] = m + 0x16A8;
    } else if (0x6658 - m < a[5]) {
        a[5] = 0x6658 - m;
    }
}

void func_8010F830(u8 *a)
{
    u8 *o = *(u8 **)(a + 0x10);

    switch (a[6]) {
    case 0:
        o[0x2B] = 1;
        a[6]++;
    case 1:
        func_80076D68(a);
        if (D_1F800137 == 0) {
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

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_8010F8CC);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_8010FC70);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_8010FDD8);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_8010FF0C);

s32 func_801100B4(u8 *a, u8 *b, s32 bit)
{
    u8 *q = a + 0x60;

    if (b[0] == 0xFF) {
        return -1;
    }
    return (*(u32 *)(q + 0x14) & (1 << bit)) == 0;
}

typedef struct {
    s16 pad0;
    s16 x;
    s16 pad4;
    s16 y;
    s16 pad8;
    s16 z;
} HiPos;
void func_801100E4(void *a, u8 *b)
{
    HiPos p;

    if (b[3] == 0) {
        p.x = *(u16 *)(b + 4);
        p.y = *(u16 *)(b + 6);
        p.z = *(u16 *)(b + 8);
        f_IncrementBerryNutsScore(&p);
        func_80074590(0x11, 0x13, 0);
    } else {
        func_80074590(0x82, 0, 0);
    }
}

#define H(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define M(a) (*(u8 **)((a) + 0xC0))
extern s16 D_8011C758[];
extern s16 D_8011C764[];
extern u32 D_8011C770[];
extern u8 D_800BF8ED;
extern u16 D_1F800174;
extern u32 D_800BF874;
extern u8 D_8004C930[];
static inline void init(u8 *p, s16 v)
{
    H(p, 0x58) = 0;
    H(p, 0x56) = v;
    func_800517F8(p);
}
void func_8011014C(u8 *a)
{
    PosV v;
    u8 *p;
    u8 *g;

    switch (a[4]) {
    case 0:
        if (func_80051B70(a, 1, 0x18) != 0) {
            break;
        }
        H(a, 0x80) = 0xA0;
        H(a, 0x82) = 0x140;
        H(a, 0x84) = 0x15E;
        H(a, 0x86) = 0x15E;
        a[0] = 1;
        a[0x2B] = 0;
        H(a, 0x54) = 0;
        a[4]++;
        init(a, D_8011C758[a[3]]);
        break;
    case 1:
        func_8007778C(a);
        switch (a[5]) {
        case 0x63:
            a[0] = 1;
            a[5] = 0;
        case 0:
            if (a[0x2B] != 1) {
                break;
            }
            if ((*(u8 **)(a + 0x14) = func_8007E110(D_8011C764[a[3]], 0)) == NULL) {
                break;
            }
            if (D_800BF8ED == 0) {
                a[5]++;
                func_80040B48(0x39);
            } else {
                a[5] += 2;
            }
            break;
        case 1:
            if (func_80042728() == 0) {
                break;
            }
            goto inc;
        case 2:
            if (D_800E7E68 & D_1F800174) {
                a[5] = 3;
            }
            break;
        case 3:
            {
                u8 *q = *(u8 **)(a + 0x14);
                if (q[4] < 2) {
                    q[4] = 2;
                    *(u8 **)(a + 0x14) = NULL;
                }
            }
            if (D_800BF874 < D_8011C770[a[3]]) {
                a[0] = 2;
                a[5] = 0x63;
                func_80042310();
                break;
            }
            p = func_80072DDC(a, 0, 5, 4);
            if (p != NULL) {
                *(void **)(p + 0x1C) = D_8004C930;
                H(p, 0x2E) = H(a, 0x2E);
                H(p, 0x32) = H(a, 0x32) - H(a, 0x84) / 2;
                H(p, 0x36) = H(a, 0x36);
                p[3] = a[3] + 0x2B;
                p[0x28] |= 0x80;
            }
            *(u8 **)(a + 0x14) = p;
            if (p == NULL) {
                break;
            }
        inc:
            a[5]++;
            break;
        case 4:
            if ((*(u8 **)(a + 0x14))[4] < 2) {
                break;
            }
            a[0] = 2;
            func_80042310();
            a[4] = 3;
            v.x = H(a, 0x2E);
            v.y = H(a, 0x32) - H(a, 0x84) / 2;
            v.z = H(a, 0x36);
            func_80027144(*(void **)(M(a) + 0x40), &v, 0x800, 0x18);
            func_80074590(0xC, 0, 0);
            func_80027144(*(void **)(M(a) + 0x40), &v, 0x800, 8);
            func_80074590(0xC, 0, 0);
            func_80040C00(0x39);
            g = (u8 *)&D_800BF870;
            g[0x1B3] |= 1 << a[3];
            if (g[0x7E] == 0) {
                func_80040B48(0x3A);
                break;
            }
            if (g[0x1B3] == 0x1F) {
                func_80040C00(0x3A);
            }
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

extern s8 D_800BF808_c1f7[];
typedef struct { u8 pad[0x104]; u8 *s[6]; } TrolleyMenuText;
extern TrolleyMenuText D_800A2854;
typedef struct { s16 x, y, w, h; } TrolleyMenuRect;
s32 menu(void) {
    u8 *strs[4];
    s32 ys[4];
    s32 xs[4];
    TrolleyMenuRect r;
    s32 i;
    s32 m;
    u8 sel;

    if (D_800E7E68 & 0x4000) {
        return *(u8 *)D_800BF808_c1f7 + 1;
    }
    if (D_800E7E68 & 0x1000) {
        return 1;
    }
    if (D_800E7E68 & 0x40) {
        if (*(u8 *)D_800BF808_c1f7 < 2) {
            *(u8 *)D_800BF808_c1f7 = *(u8 *)D_800BF808_c1f7 + 1;
            func_80074590(0x15, 0, 0);
        }
    } else if (D_800E7E68 & 0x10) {
        if (*(u8 *)D_800BF808_c1f7 != 0) {
            *(u8 *)D_800BF808_c1f7 = *(u8 *)D_800BF808_c1f7 - 1;
            func_80074590(0x15, 0, 0);
        }
    }
    ys[0] = 0x50;
    ys[1] = 0x64;
    ys[2] = 0x78;
    strs[0] = D_800A2854.s[0x19];
    strs[1] = D_800A2854.s[0x1A];
    strs[2] = D_800A2854.s[0x1B];
    func_800793C4(strs, 3, xs);
    if (xs[0] < xs[1]) {
        m = xs[2];
        if (xs[0] < m) {
            m = xs[0];
        }
    } else {
        m = xs[2];
        if (xs[1] < m) {
            m = xs[1];
        }
    }
    for (i = 0; i < 3; i++) {
        s16 x = m;

        sel = *(u8 *)D_800BF808_c1f7;
        func_80079374(x, (s16)ys[i], (sel == i) * 2, strs[i], 0);
    }
    func_8007E998(m - 0x10, ys[*(u8 *)D_800BF808_c1f7] + 4, 0);
    r.x = m - 0x20;
    r.w = (0xA0 - m) * 2 + 0x30;
    r.h = 0x40;
    r.y = ys[0] - 4;
    func_8005019C(&r, 0, 1, 1);
    return 0;
}

s32 f_UpdateBerryNutsRetryMenu(void) {
    u8 *strs[4];
    s32 ys[4];
    s32 xs[4];
    TrolleyMenuRect r;
    s32 i;
    s32 k;
    u8 sel;

    if (D_800E7E68 & 0x4000) {
        return *(u8 *)D_800BF808_c1f7 + 1;
    }
    if (D_800E7E68 & 0x40) {
        if (*(u8 *)D_800BF808_c1f7 == 0) {
            *(u8 *)D_800BF808_c1f7 = *(u8 *)D_800BF808_c1f7 + 1;
            func_80074590(0x15, 0, 0);
        }
    } else if (D_800E7E68 & 0x10) {
        if (*(u8 *)D_800BF808_c1f7 != 0) {
            *(u8 *)D_800BF808_c1f7 = *(u8 *)D_800BF808_c1f7 - 1;
            func_80074590(0x15, 0, 0);
        }
    }
    strs[0] = D_800A2854.s[0];
    func_800793C4(strs, 1, xs);
    i = 0;
    func_80079374((s16)xs[0], 0x70, i, strs[0], 0);
    r.y = 0x6C;
    ys[0] = 0x84;
    ys[1] = 0x98;
    r.x = xs[0] - 0x10;
    r.w = (0xA0 - xs[0]) * 2 + 0x20;
    strs[0] = D_800A2854.s[1];
    strs[1] = D_800A2854.s[2];
    k = func_800793C4(strs, 2, xs);
loop:
    do {
        sel = *(u8 *)D_800BF808_c1f7;
        func_80079374((s16)xs[i], (s16)ys[i], (sel == i) * 2, strs[i], 0);
    } while (0);
    i++;
    if (i < 2) {
        goto loop;
    }
    func_8007E998(k, ys[*(u8 *)D_800BF808_c1f7] + 4, 0);
    r.h = 0x40;
    func_8005019C(&r, 0, 1, 1);
    return 0;
}

extern u8 *D_1F800138_5432;
extern u8 D_1F800136;
extern u8 D_800BF9C3;
void func_80110938(void)
{
    u8 *a = D_1F800138_5432;
    s32 r;
    u8 *g;
    u8 *st;

    switch (*(u16 *)(a + 0x50)) {
    case 0:
        (*(u16 *)(a + 0x50))++;
        D_1F800136 = 1;
        D_800BF808[0] = 0;
        break;
    case 1:
        r = menu();
        if (r == 0) {
            break;
        }
        if (r == 2) {
            D_1F800137 = 2;
            D_800BF808[7] = 2;
            D_800BF808[5] = 3;
            D_800BF808[0x31] = 0;
            st = (u8 *)&D_800BF870;
            st[1] = 5;
            *(s16 *)(st + 0x1B6) = 0;
        } else if (r == 3) {
            D_1F800137 = 2;
            D_800BF808[0x31] = 3;
            D_800BF808[7] = 2;
            D_800BF808[5] = 0;
            *(s16 *)(D_800BF808 + 0x32) = 0x1403;
            D_800BF9C3 = 2;
        }
        D_1F800138_5432[0x6B] = 0;
        D_1F800136 = 0;
        *(u16 *)(D_1F800138_5432 + 0x50) = 0;
        break;
    }
}

extern u8 D_800BF871;
void func_80112884();
void func_80110A34(void)
{
    u8 *s;

    D_1F800137 = 2;
    s = D_800BF808;
    s[7] = 2;
    s[5] = 3;
    s[0x31] = 0;
    D_800BF871 = 5;
}

void func_80110A68(void)
{
    u8 *s;

    D_1F800137 = 2;
    s = D_800BF808;
    s[7] = 2;
    s[0x31] = 3;
    s[5] = 0;
    *(s16 *)(s + 0x32) = 0x1403;
}

void f_UpdateTinyMouseVillageRewardActor();
extern u16 D_800BFA26;
extern s32 D_800BF854;
void f_IncrementBerryNutsScore(void *a)
{
    u16 *p = &D_800BFA26;
    u16 n;

    if (*p < 999) {
        *(volatile u16 *)p = n = *p + 1;
        if (((volatile u16 *)p)[-1] < n) {
            p[-1] = n;
            D_800BF854 = 1;
        }
    }
    f_SpawnBerryNutsScorePopup(a, D_800BFA26);
}

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", f_SpawnTinyMouseVillageActorsFromPlacementTable);

extern u8 D_800BF8F9;
void func_80110C80(u8 *a)
{
    switch (a[4]) {
    case 0:
        a[4] = 1;
        if (D_800BF871 < 4) {
            f_SpawnTinyMouseVillageActorsFromPlacementTable(a, 0);
        } else {
            f_SpawnTinyMouseVillageActorsFromPlacementTable(a, 1);
        }
        func_800752B4(0);
        func_80075D24(0x1FFF);
        break;
    case 1:
        if (D_800BF8F9 != 0xFF) {
            func_80040C00(0x45);
        }
        break;
    case 2:
        break;
    case 3:
        func_8007ADD0();
        break;
    }
}

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", f_UpdateTinyMouseVillageInteriorDoorSequence);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_80111074);

typedef struct {
    u8 pad0[4];
    u8 state;
    u8 pad5[3];
    u8 partFrame, partCount, padA, renderKind, padC, renderMode;
    u8 padE[0x20];
    s16 x, pad30, y, pad34, z;
    u8 pad38[0x1C];
    s16 turn, unk_56, unk_58;
    u8 pad5A[4];
    u8 pickupBehaviour;
    u8 pad5F[0x61];
    u8 *parts[2];
} PartActor;
#define H(p, o) (*(s16 *)((u8 *)(p) + (o)))
extern s16 D_800ED098;
extern u16 D_801003F8;
extern s16 *D_8011CB1C[];
extern u8 D_8011CB30[][2];
void func_8011133C(PartActor *a)
{
    s16 *src;
    s32 i;
    s32 n;
    s32 d;

    a->partFrame = D_8011CB30[a->pickupBehaviour][0];
    d = D_800ED098;
    n = a->partFrame;
    if (d < n) {
        a->state = 3;
        return;
    }
    a->renderKind = 1;
    a->partCount = n;
    a->renderMode = 0;
    a->y = -0x28;
    a->turn = 0;
    a->unk_58 = 0;
    a->unk_56 = 0;
    a->x = 0;
    a->z = D_801003F8;
    src = D_8011CB1C[a->pickupBehaviour];
    for (i = 0; i < a->partFrame; i++) {
        a->parts[i] = func_8007AAE8();
        H(a->parts[i], 6) = -1;
        H(a->parts[i], 0) = *src++;
        H(a->parts[i], 2) = *src++;
        H(a->parts[i], 4) = *src++;
        H(a->parts[i], 8) = 0;
        H(a->parts[i], 0xA) = 0;
        H(a->parts[i], 0xC) = 0;
        func_80051B04(a->parts[i], 0xC, *src++);
    }
}

extern s8 D_800BF841;
/* func_80111E70, inlined */
static inline void inl_80111E70(void *arg0) {
    if ((M2C_FIELD(arg0, u8 *, 5) == 0) && (func_8007E038(0x32, 3) != 0)) {
        M2C_FIELD(arg0, u8 *, 5) = (u8) (M2C_FIELD(arg0, u8 *, 5) + 1);
        D_800BF841 = 0;
        func_80074BF8(0xB);
        func_8004FB20();
    }
    func_800517F8(arg0);
    M2C_FIELD(arg0, s8 *, 1) = 1;
}
/* func_80111EE4, inlined */
static inline void inl_80111EE4(u8 *a)
{
    switch (a[5]) {
    case 0:
        if ((*(u8 **)(a + 0x14) = (u8 *)func_8007E038(0x33, 3)) != NULL) {
            a[5]++;
            D_800BF841 = 0;
            func_80074BF8(0xC);
            func_8004FB20();
        }
        break;
    case 1:
        if (D_800BF80F != 0) {
            a[5] = 2;
            (*(u8 **)(a + 0x14))[4] = 3;
        }
        break;
    case 2:
        break;
    }
    func_800517F8(a);
    a[1] = 1;
}
/* func_80111F94, inlined */
static inline void inl_80111F94(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 5) == 0) {
        M2C_FIELD(arg0, u8 *, 5) = 1U;
        func_80074590(0x84, 0, 0);
    }
    func_800517F8(arg0);
    M2C_FIELD(arg0, s8 *, 1) = 1;
}
/* func_80111FE8, inlined */
static inline void inl_80111FE8(u8 *a)
{
    u8 *s;
    

    switch (a[5]) {
    case 0:
        s = D_800BF808;
        if ((*(u8 **)(a + 0x14) = (u8 *)func_8007E038(*(s32 *)(s + 0x4C) ? 0x35 : 0x34, 3)) != NULL) {
            a[5]++;
            s[0x39] = 0;
            func_80074590(0x84, 0, 0);
            func_8004FB20();
        }
        break;
    case 1:
        if (D_800BF80F != 0) {
            a[5] = 2;
            (*(u8 **)(a + 0x14))[4] = 3;
        }
        break;
    case 2:
        break;
    }
    func_800517F8(a);
    a[1] = 1;
}
void func_801114A0(u8 *a)
{
    switch (a[0x5E]) {
    case 0:
        inl_80111E70(a);
        break;
    case 1:
        inl_80111EE4(a);
        break;
    case 2:
        func_800517F8(a);
        a[1] = 1;
        break;
    case 3:
        inl_80111F94(a);
        break;
    case 4:
        inl_80111FE8(a);
        break;
    }
}

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_80111658);

extern u8 D_800BFA28;
extern void *D_800ECF80;
extern u8 D_8011FC38[];
extern s8 *D_800ECF58[];
extern void *D_80017334[];
/* func_801120BC, inlined */
static inline void inl_801120BC(void *arg0) {
    if ((u8) D_800BF871 < 4U) {
        M2C_FIELD(arg0, s8 *, 4) = 3;
        return;
    }
    func_80051B70(arg0, 0xC, 0xB);
    M2C_FIELD(arg0, s8 *, 0xBF) = 1;
    M2C_FIELD(arg0, s16 *, 0x50) = 0;
    M2C_FIELD(arg0, s8 *, 0x46) = 1;
    M2C_FIELD(arg0, u16 *, 0x5A) = (u16) M2C_FIELD(arg0, u16 *, 0x56);
}
/* func_80112218, inlined */
static inline void inl_80112218(u8 *a)
{
    func_80051B70(a, 0xC, 0xA);
    a[0] = 1;
    *(s16 *)(a + 0x80) = 0xA0;
    *(s16 *)(a + 0x82) = 0x140;
    *(s16 *)(a + 0x84) = 0x190;
    *(s16 *)(a + 0x86) = 0x190;
}
/* func_80112394, inlined */
static inline void inl_80112394(u8 *a)
{
    *(void **)(a + 0x3C) = D_800ECF80;
    func_80077B38(a, D_8011FC38, 2);
    *(s16 *)(a + 0x5C) = 0;
    a[0xB] = 0x10;
    *(s16 *)(a + 0x5A) = 0;
    a[0x47] = 0;
}
/* func_80112488, inlined */
static inline void inl_80112488(u8 *a)
{
    *(s8 **)(a + 0x3C) = D_800ECF58[0];
    func_80077B38(a, D_80017334, 0x164);
    *(s16 *)(a + 0x5C) = 0;
    a[0xB] = 0x10;
    *(s16 *)(a + 0x5A) = 0;
    a[0x47] = 0;
}
/* func_80112598, inlined */
static inline void inl_80112598(u8 *a)
{
    func_80051B70(a, 0xC, 8);
    *(s16 *)(a + 0x2E) = 0x44AD;
    *(s16 *)(a + 0x32) = -0x5C0;
    *(s16 *)(a + 0x36) = 0x1DD9;
    *(s16 *)(a + 0x54) = 0;
    *(s16 *)(a + 0x56) = 0;
    *(s16 *)(a + 0x58) = 0;
    *(s16 *)(a + 0x60) = 0;
    func_80074590(0x1C, -0xF, -0x32);
}
/* func_8011273C, inlined */
static inline void inl_8011273C(u8 *a)
{
    func_80051B70(a, 0xC, 0x29);
    *(s16 *)(a + 0x54) = 0;
    *(s16 *)(a + 0x56) = 0;
    *(s16 *)(a + 0x58) = 0;
}
/* func_801127C0, inlined */
static inline void inl_801127C0(u8 *a)
{
    *(void **)(a + 0x3C) = D_800ECF80;
    func_80077B38(a, D_8011FC38, 0x1);
    *(s16 *)(a + 0x5C) = 0;
    a[0xB] = 0x10;
    *(s16 *)(a + 0x5A) = 0;
    a[0x47] = 0;
}
/* func_80112120, inlined */
static inline void inl_80112120(u8 *a)
{
    switch (a[5]) {
    case 0:
        if (D_800BF871 == 4) {
            *(s16 *)(a + 0x40) = 0xF;
            a[5] = 1;
            *(s16 *)(a + 0x50) = 0x400;
            func_80072EFC(a);
        } else {
            a[5] = 3;
        }
        break;
    case 1:
        if (--*(s16 *)(a + 0x40) == -1) {
            a[5]++;
        }
        break;
    case 2:
        if (func_80072F14(a) != 0) {
            a[5]++;
        }
        break;
    }
    a[1] = 1;
    *(s16 *)(a + 0x32) = D_1F800240 - 0x5C0;
    func_800517F8(a);
}
/* func_80112268, inlined */
static inline void inl_80112268(u8 *a)
{
    switch (a[5]) {
    case 0:
        if (D_800BFA28 >= 7) {
            a[5]++;
            *(s16 *)(a + 0x4A) = -0x3000;
            *(s16 *)(a + 0x50) = 0x180;
        }
        break;
    case 1:
        if (D_800BFA28 >= 8) {
            a[4] = 3;
        } else {
            *(s16 *)(a + 0x36) -= 0xC;
            *(s16 *)(a + 0x54) += 0x80;
            *(s32 *)(a + 0x30) += *(s16 *)(a + 0x4A) << 8;
            *(s16 *)(a + 0x4A) += *(s16 *)(a + 0x50);
        }
        break;
    }
    a[1] = 1;
    func_80077EBC(a);
    func_800517F8(a);
}
/* func_801123E4, inlined */
static inline void inl_801123E4(u8 *a)
{
    u8 *o = *(u8 **)(a + 0x10);

    func_8004BD64(a, 0, *(s32 *)(o + 0xD8), *(s32 *)(o + 0xCC), 0);
    a[1] = 1;
    *(s16 *)(a + 0x32) -= 0x10;
    *(s16 *)(a + 0x36) += 0x10;
}
/* func_801124D8, inlined */
static inline void inl_801124D8(void *arg0) {
    void *temp_v1;

    temp_v1 = M2C_FIELD(arg0, void **, 0x10);
    if ((u8) D_800BFA28 >= 4U) {
        func_8004D4C4(0x6D, 1);
        func_8004B0D8(arg0);
        M2C_FIELD(arg0, s8 *, 4) = 3;
        return;
    }
    func_8004BD64(arg0, 0, M2C_FIELD(temp_v1, s32 *, 0xD8), M2C_FIELD(temp_v1, s32 *, 0xCC), 0);
    M2C_FIELD(arg0, s8 *, 1) = 1;
}
/* func_801125FC, inlined */
static inline void inl_801125FC(void *arg0) {
    s16 temp_v1_2;
    u16 temp_v0;
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 5);
    switch (temp_v1) {                              /* irregular */
    case 0:
        if ((u8) D_800BFA28 >= 3U) {
            M2C_FIELD(arg0, u8 *, 5) = 1U;
            M2C_FIELD(arg0, u16 *, 0x40) = 0x3CU;
        }
        temp_v1_2 = M2C_FIELD(arg0, s16 *, 0x60);
        if (temp_v1_2 != 0xE) {
            if (temp_v1_2 == 0x28) {
                M2C_FIELD(arg0, s16 *, 0x60) = 0;
                goto block_8;
            }
        } else {
block_8:
            func_80074590(0x1C, -0xF, -0x32);
        }
        M2C_FIELD(arg0, s16 *, 0x60) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0x60) + 1);
        break;
    case 1:
        temp_v0 = M2C_FIELD(arg0, u16 *, 0x40) - 1;
        M2C_FIELD(arg0, u16 *, 0x40) = temp_v0;
        if ((s16) temp_v0 == -1) {
            M2C_FIELD(arg0, s8 *, 4) = 3;
        }
        break;
    }
    M2C_FIELD(arg0, s8 *, 1) = 1;
    M2C_FIELD(arg0, u16 *, 0x36) = (u16) (M2C_FIELD(arg0, u16 *, 0x36) - 0xA);
    func_800517F8(arg0);
}
/* func_80112810, inlined */
static inline void inl_80112810(void *arg0) {
    void *temp_v1;

    temp_v1 = M2C_FIELD(arg0, void **, 0x10);
    if ((u8) D_800BFA28 >= 9U) {
        func_8004D4C4(0x9C, 1);
        func_8004B0D8(arg0);
        M2C_FIELD(arg0, s8 *, 4) = 3;
        return;
    }
    func_8004BD64(arg0, 0, M2C_FIELD(temp_v1, s32 *, 0xD8), M2C_FIELD(temp_v1, s32 *, 0xCC), 0);
    M2C_FIELD(arg0, s8 *, 1) = 1;
}
void f_UpdateTinyMouseVillageRewardActor(u8 *a)
{
    switch (a[4]) {
    case 0:
        a[4] = 1;
        switch (a[3]) {
        case 0:
            func_8011133C(a);
            break;
        case 1:
            inl_801120BC(a);
            break;
        case 2:
            inl_80112218(a);
            break;
        case 3:
            inl_80112394(a);
            break;
        case 4:
            inl_80112488(a);
            break;
        case 5:
            inl_80112598(a);
            break;
        case 6:
            inl_8011273C(a);
            break;
        case 7:
            inl_801127C0(a);
            break;
        }
        break;
    case 1:
        switch (a[3]) {
        case 0:
            func_801114A0(a);
            break;
        case 1:
            inl_80112120(a);
            break;
        case 2:
            inl_80112268(a);
            break;
        case 3:
            inl_801123E4(a);
            break;
        case 4:
            inl_801124D8(a);
            break;
        case 5:
            inl_801125FC(a);
            break;
        case 6:
            func_80111658(a);
            break;
        case 7:
            inl_80112810(a);
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

u8 *func_80111E0C(void *a, u8 b)
{
    u8 *r = func_80072DDC(0, 3, 3, 0x10);

    if (r != NULL) {
        *(void **)(r + 0x1C) = f_UpdateTinyMouseVillageRewardActor;
        r[3] = 0;
        r[0x5E] = b;
        *(void **)(r + 0x10) = a;
    }
    return r;
}

void func_80111E70(void *arg0) {
    if ((M2C_FIELD(arg0, u8 *, 5) == 0) && (func_8007E038(0x32, 3) != 0)) {
        M2C_FIELD(arg0, u8 *, 5) = (u8) (M2C_FIELD(arg0, u8 *, 5) + 1);
        D_800BF841 = 0;
        func_80074BF8(0xB);
        func_8004FB20();
    }
    func_800517F8(arg0);
    M2C_FIELD(arg0, s8 *, 1) = 1;
}

extern u8 D_800BF841_2c52;
void func_80111EE4(u8 *a)
{
    switch (a[5]) {
    case 0:
        if ((*(u8 **)(a + 0x14) = (u8 *)func_8007E038(0x33, 3)) != NULL) {
            a[5]++;
            D_800BF841_2c52 = 0;
            func_80074BF8(0xC);
            func_8004FB20();
        }
        break;
    case 1:
        if (D_800BF80F != 0) {
            a[5] = 2;
            (*(u8 **)(a + 0x14))[4] = 3;
        }
        break;
    case 2:
        break;
    }
    func_800517F8(a);
    a[1] = 1;
}

void func_80111F94(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 5) == 0) {
        M2C_FIELD(arg0, u8 *, 5) = 1U;
        func_80074590(0x84, 0, 0);
    }
    func_800517F8(arg0);
    M2C_FIELD(arg0, s8 *, 1) = 1;
}

void func_80111FE8(u8 *a)
{
    u8 *s;
    

    switch (a[5]) {
    case 0:
        s = D_800BF808;
        if ((*(u8 **)(a + 0x14) = (u8 *)func_8007E038(*(s32 *)(s + 0x4C) ? 0x35 : 0x34, 3)) != NULL) {
            a[5]++;
            s[0x39] = 0;
            func_80074590(0x84, 0, 0);
            func_8004FB20();
        }
        break;
    case 1:
        if (D_800BF80F != 0) {
            a[5] = 2;
            (*(u8 **)(a + 0x14))[4] = 3;
        }
        break;
    case 2:
        break;
    }
    func_800517F8(a);
    a[1] = 1;
}

void func_801120BC(void *arg0) {
    if ((u8) D_800BF871 < 4U) {
        M2C_FIELD(arg0, s8 *, 4) = 3;
        return;
    }
    func_80051B70(arg0, 0xC, 0xB);
    M2C_FIELD(arg0, s8 *, 0xBF) = 1;
    M2C_FIELD(arg0, s16 *, 0x50) = 0;
    M2C_FIELD(arg0, s8 *, 0x46) = 1;
    M2C_FIELD(arg0, u16 *, 0x5A) = (u16) M2C_FIELD(arg0, u16 *, 0x56);
}

void func_80112120(u8 *a)
{
    switch (a[5]) {
    case 0:
        if (D_800BF871 == 4) {
            *(s16 *)(a + 0x40) = 0xF;
            a[5] = 1;
            *(s16 *)(a + 0x50) = 0x400;
            func_80072EFC(a);
        } else {
            a[5] = 3;
        }
        break;
    case 1:
        if (--*(s16 *)(a + 0x40) == -1) {
            a[5]++;
        }
        break;
    case 2:
        if (func_80072F14(a) != 0) {
            a[5]++;
        }
        break;
    }
    a[1] = 1;
    *(s16 *)(a + 0x32) = D_1F800240 - 0x5C0;
    func_800517F8(a);
}

void func_80112218(u8 *a)
{
    func_80051B70(a, 0xC, 0xA);
    a[0] = 1;
    *(s16 *)(a + 0x80) = 0xA0;
    *(s16 *)(a + 0x82) = 0x140;
    *(s16 *)(a + 0x84) = 0x190;
    *(s16 *)(a + 0x86) = 0x190;
}

void func_80112268(u8 *a)
{
    switch (a[5]) {
    case 0:
        if (D_800BFA28 >= 7) {
            a[5]++;
            *(s16 *)(a + 0x4A) = -0x3000;
            *(s16 *)(a + 0x50) = 0x180;
        }
        break;
    case 1:
        if (D_800BFA28 >= 8) {
            a[4] = 3;
        } else {
            *(s16 *)(a + 0x36) -= 0xC;
            *(s16 *)(a + 0x54) += 0x80;
            *(s32 *)(a + 0x30) += *(s16 *)(a + 0x4A) << 8;
            *(s16 *)(a + 0x4A) += *(s16 *)(a + 0x50);
        }
        break;
    }
    a[1] = 1;
    func_80077EBC(a);
    func_800517F8(a);
}

void f_UpdateTinyMouseVillageRewardActor();
u8 *func_80112350(void *a)
{
    u8 *r = func_80072DDC(a, 0, 3, 0x10);

    if (r != NULL) {
        *(void **)(r + 0x1C) = f_UpdateTinyMouseVillageRewardActor;
        r[3] = 0x3;
    }
    return r;
}

void func_80112394(u8 *a)
{
    *(void **)(a + 0x3C) = D_800ECF80;
    func_80077B38(a, D_8011FC38, 2);
    *(s16 *)(a + 0x5C) = 0;
    a[0xB] = 0x10;
    *(s16 *)(a + 0x5A) = 0;
    a[0x47] = 0;
}

void func_801123E4(u8 *a)
{
    u8 *o = *(u8 **)(a + 0x10);

    func_8004BD64(a, 0, *(s32 *)(o + 0xD8), *(s32 *)(o + 0xCC), 0);
    a[1] = 1;
    *(s16 *)(a + 0x32) -= 0x10;
    *(s16 *)(a + 0x36) += 0x10;
}

s32 func_8011243C(void *a)
{
    u8 *r = func_80072DDC(a, 0, 3, 0x10);

    if (r != NULL) {
        *(void **)(r + 0x1C) = f_UpdateTinyMouseVillageRewardActor;
        r[3] = 4;
        return 1;
    }
    return 0;
}

void func_80112488(u8 *a)
{
    *(s8 **)(a + 0x3C) = D_800ECF58[0];
    func_80077B38(a, D_80017334, 0x164);
    *(s16 *)(a + 0x5C) = 0;
    a[0xB] = 0x10;
    *(s16 *)(a + 0x5A) = 0;
    a[0x47] = 0;
}

void func_801124D8(void *arg0) {
    void *temp_v1;

    temp_v1 = M2C_FIELD(arg0, void **, 0x10);
    if ((u8) D_800BFA28 >= 4U) {
        func_8004D4C4(0x6D, 1);
        func_8004B0D8(arg0);
        M2C_FIELD(arg0, s8 *, 4) = 3;
        return;
    }
    func_8004BD64(arg0, 0, M2C_FIELD(temp_v1, s32 *, 0xD8), M2C_FIELD(temp_v1, s32 *, 0xCC), 0);
    M2C_FIELD(arg0, s8 *, 1) = 1;
}

s32 func_8011254C(void *a)
{
    u8 *r = func_80072DDC(a, 1, 3, 0x10);

    if (r != NULL) {
        *(void **)(r + 0x1C) = f_UpdateTinyMouseVillageRewardActor;
        r[3] = 5;
        return 1;
    }
    return 0;
}

void func_80112598(u8 *a)
{
    func_80051B70(a, 0xC, 8);
    *(s16 *)(a + 0x2E) = 0x44AD;
    *(s16 *)(a + 0x32) = -0x5C0;
    *(s16 *)(a + 0x36) = 0x1DD9;
    *(s16 *)(a + 0x54) = 0;
    *(s16 *)(a + 0x56) = 0;
    *(s16 *)(a + 0x58) = 0;
    *(s16 *)(a + 0x60) = 0;
    func_80074590(0x1C, -0xF, -0x32);
}

extern u8 D_800BFA28;
void func_801125FC(void *arg0) {
    s16 temp_v1_2;
    u16 temp_v0;
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 5);
    switch (temp_v1) {                              /* irregular */
    case 0:
        if ((u8) D_800BFA28 >= 3U) {
            M2C_FIELD(arg0, u8 *, 5) = 1U;
            M2C_FIELD(arg0, u16 *, 0x40) = 0x3CU;
        }
        temp_v1_2 = M2C_FIELD(arg0, s16 *, 0x60);
        if (temp_v1_2 != 0xE) {
            if (temp_v1_2 == 0x28) {
                M2C_FIELD(arg0, s16 *, 0x60) = 0;
                goto block_8;
            }
        } else {
block_8:
            func_80074590(0x1C, -0xF, -0x32);
        }
        M2C_FIELD(arg0, s16 *, 0x60) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0x60) + 1);
        break;
    case 1:
        temp_v0 = M2C_FIELD(arg0, u16 *, 0x40) - 1;
        M2C_FIELD(arg0, u16 *, 0x40) = temp_v0;
        if ((s16) temp_v0 == -1) {
            M2C_FIELD(arg0, s8 *, 4) = 3;
        }
        break;
    }
    M2C_FIELD(arg0, s8 *, 1) = 1;
    M2C_FIELD(arg0, u16 *, 0x36) = (u16) (M2C_FIELD(arg0, u16 *, 0x36) - 0xA);
    func_800517F8(arg0);
}

s32 func_801126E0(void *a)
{
    u8 *r = func_80072DDC(a, 1, 3, 0x10);

    if (r != NULL) {
        *(void **)(r + 0x1C) = f_UpdateTinyMouseVillageRewardActor;
        r[3] = 6;
        func_8004D688(0x53, 1);
        return 1;
    }
    return 0;
}

void func_8011273C(u8 *a)
{
    func_80051B70(a, 0xC, 0x29);
    *(s16 *)(a + 0x54) = 0;
    *(s16 *)(a + 0x56) = 0;
    *(s16 *)(a + 0x58) = 0;
}

s32 func_80112774(void *a)
{
    u8 *r = func_80072DDC(a, 0, 3, 0x10);

    if (r != NULL) {
        *(void **)(r + 0x1C) = f_UpdateTinyMouseVillageRewardActor;
        r[3] = 7;
        return 1;
    }
    return 0;
}

extern void *D_800ECF80;
extern u8 D_8011FC38[];
void func_801127C0(u8 *a)
{
    *(void **)(a + 0x3C) = D_800ECF80;
    func_80077B38(a, D_8011FC38, 0x1);
    *(s16 *)(a + 0x5C) = 0;
    a[0xB] = 0x10;
    *(s16 *)(a + 0x5A) = 0;
    a[0x47] = 0;
}

extern u8 D_800BFA28;
void func_80112810(void *arg0) {
    void *temp_v1;

    temp_v1 = M2C_FIELD(arg0, void **, 0x10);
    if ((u8) D_800BFA28 >= 9U) {
        func_8004D4C4(0x9C, 1);
        func_8004B0D8(arg0);
        M2C_FIELD(arg0, s8 *, 4) = 3;
        return;
    }
    func_8004BD64(arg0, 0, M2C_FIELD(temp_v1, s32 *, 0xD8), M2C_FIELD(temp_v1, s32 *, 0xCC), 0);
    M2C_FIELD(arg0, s8 *, 1) = 1;
}

typedef struct {
    s16 x0;
    s16 x;
    s16 x4;
    s16 y;
    s16 x8;
    s16 z;
} V3;
#define UH(p, o) (*(u16 *)((u8 *)(p) + (o)))
extern u8 D_8001B4DC[];
extern s32 D_800BF858;
extern u8 D_800BFA53;
extern u8 D_800E800D;
extern u8 D_8011CB3C[];
void func_80112D80();
u8 *func_8003315C();
void func_80112884(u8 *a)
{
    u8 *p = D_800E7E80;
    u8 *g;
    u8 *q;
    V3 v;

    switch (a[4]) {
    case 0:
        g = (u8 *)D_800ECF58;
        if (func_800519E0(a, 0xF, *(s32 *)(g + 0x48), D_8011CB3C) != 0) {
            break;
        }
        a[0xB] = 0xF;
        H(a, 0x60) = -0x64;
        *(s32 *)(a + 0x3C) = *(s32 *)(g + 0x4C);
        *(u8 **)(a + 0x7C) = D_8001B4DC;
        func_80041718(a, 0, 0);
        H(a, 0x2E) = H(p, 0x2E);
        H(a, 0x62) = H(a, 0x32) = -0x620;
        H(a, 0x36) = H(p, 0x36);
        H(p, 0x32) = H(a, 0x8A) + (H(a, 0x32) + H(a, 0x60));
        H(a, 0x56) = H(p, 0x56);
        H(a, 0x4A) = 0;
        a[4]++;
        q = func_8003315C(a);
        if (q != NULL) {
            *(void **)(q + 0x1C) = func_80112D80;
        }
        H(a, 0x84) = 0x5A;
        a[0xBF] = 0;
        if (D_800BF871 == 5) {
            a[5] = 3;
            H(a, 0x40) = 0x5A;
        }
        break;
    case 1:
        a[1] = 1;
        func_8004190C(a);
        switch (a[5]) {
        case 0:
            if (D_800BFA53 == 1) {
                H(a, 0x4A) = -0x3000;
                a[5]++;
                func_80074590(1, 8, 0);
                func_80074590(0xA, 5, 0);
            }
            break;
        case 1:
            a[0xBF] = 1;
            if ((H(a, 0x4A) += 0x360) > 0x3000) {
                H(a, 0x4A) = 0x3000;
            }
            if ((H(a, 0x62) += H(a, 0x4A) >> 8) >= -0x61F) {
                func_80074590(0xD, -4, 0);
                H(a, 0x62) = -0x620;
                a[5]++;
                D_800E800D = 1;
                func_80074590(0x33, 0xA, 0);
            }
            break;
        case 2:
            if ((D_1F800240 -= 0x50) <= 0) {
                D_1F800240 = 0;
            }
            if (D_800E800D == 0) {
                a[5]++;
            }
            break;
        case 3:
            a[5]++;
            D_800BF85C = 1;
            H(a, 0x40) = 0x5A;
            break;
        case 4:
            if (--H(a, 0x40) == 0) {
                a[5]++;
                D_800BFA53 = 2;
                D_800BF85C = 2;
            }
            break;
        case 5:
            a[0xBF] = 0;
            if (D_800BF858 == 0) {
                a[5]++;
            }
            break;
        case 6:
            if ((D_1F800240 += 0x50) >= 0x320) {
                D_1F800240 = 0x320;
            }
            break;
        }
        H(a, 0x32) = H(a, 0x62) - D_1F800240;
        H(a, 0x2E) = H(p, 0x2E);
        H(p, 0x32) = H(a, 0x8A) + (H(a, 0x32) + H(a, 0x60));
        H(a, 0x36) = H(p, 0x36);
        H(a, 0x56) = H(p, 0x56);
        {
            u8 *c = D_1F8000D0;
            H(c, 0xE) = H(a, 0x2E);
            H(c, 0x12) = H(a, 0x32) - 0xC8;
            H(c, 0x16) = H(a, 0x36);
        }
        func_800518FC(a);
        if (p[0x149] == 4) {
            func_80041768(a, 4, 5);
            if (H(p, 0x44) == 0) {
                break;
            }
            if (D_1F80017C & 3) {
                break;
            }
        } else {
            if (H(p, 0x44) == 0) {
                func_80041768(a, 0, 5);
                break;
            }
            func_80041768(a, 2, 5);
            if (H(p, 0x44) >= 0x1800) {
                break;
            }
            if (D_1F80017C & 7) {
                break;
            }
        }
        v.x = (*(s32 *)(*(u8 **)(a + 0xE8) + 0x2C) + *(s32 *)(*(u8 **)(a + 0xF8) + 0x2C)) / 2;
        v.y = H(a, 0x32) + H(a, 0x84);
        v.z = (*(s32 *)(*(u8 **)(a + 0xE8) + 0x34) + *(s32 *)(*(u8 **)(a + 0xF8) + 0x34)) / 2;
        func_8003116C(0x35, &v, -0x5A);
        break;
    case 2:
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_80112D80);

u8 *func_80112F34(void *a)
{
    u8 *r = func_80072DDC(a, 3, 3, 0x23);

    if (r != NULL) {
        *(void **)(r + 0x1C) = func_80112884;
    }
    return r;
}

void func_80112F70(void) {
}

void func_80112F78(u8 *a)
{
    s16 v[6];

    v[1] = (*(s32 *)(*(u8 **)(a + 0xE8) + 0x2C) + *(s32 *)(*(u8 **)(a + 0xF8) + 0x2C)) / 2;
    v[3] = *(s16 *)(a + 0x32) + *(s16 *)(a + 0x84);
    v[5] = (*(s32 *)(*(u8 **)(a + 0xE8) + 0x34) + *(s32 *)(*(u8 **)(a + 0xF8) + 0x34)) / 2;
    func_8003116C(0x35, v, -0x5A);
}

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_80112FF8);

void func_80113338(u8 *a)
{
    s32 s = a[4];

    switch (s) {
    case 0:
        a[4] = 1;
        *(s16 *)(a + 0x40) = 0x20;
        break;
    case 1:
        func_80112FF8(a);
        a[1] = s;
        break;
    case 2:
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

void func_80113338();
void f_SpawnBerryNutsScorePopup(u8 *p, s32 n)
{
    u8 *r;

    if (n % 10 == 0) {
        r = func_80072DDC(0, 0, 3, 0x2A);
        if (r != NULL) {
            *(void **)(r + 0x1C) = func_80113338;
            *(s16 *)(r + 0x5C) = 0x7C7E;
            *(s16 *)(r + 0xE) = func_80079634(n, r + 0x44);
            *(s16 *)(r + 0x54) = *(s16 *)(p + 2);
            *(s16 *)(r + 0x56) = *(s16 *)(p + 6);
            *(s16 *)(r + 0x58) = *(s16 *)(p + 0xA);
        }
    }
}

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_80113488);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_801136F0);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_80113854);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_80113A7C);

extern u8 D_800BF8FA;
extern u8 *D_1F800138;
extern u16 D_800E7FEE;
extern u16 D_1F800194;
s32 func_80113C50(u8 *a)
{
    u8 *g;
    u8 *p;

    switch (a[7]) {
    case 0:
        a[7] = 1;
        func_80042310();
        D_1F800137 = 2;
        {
            u8 *g0 = D_800BF808;
            g0[0x10] = 1;
            if (D_800BF8FA != 0xFF) {
                *(s32 *)(g0 + 0x48) = 1;
            } else {
                *(s32 *)(g0 + 0x48) = 2;
            }
        }
        break;
    case 1:
        g = D_800BF808;
        if (g[0x10] != 0) {
            return 0;
        }
        a[7] = 2;
        g[7] = 2;
        break;
    case 2:
        if (D_800BF80F != 0) {
            return 0;
        }
        a[7] = 3;
        {
        u8 *g2 = (u8 *)&D_800BF870;
        *(s16 *)(g2 + 0x1B6) = 0;
        p = D_1F800138;
        *(s16 *)(p + 0x4C) = 6;
        *(s16 *)(p + 0x4E) = 0;
        g2[0x153] = 0x80;
        g2[1] = 4;
        g2[0x10] = 1;
        D_1F800194 = D_800E7FEE;
        return 1;
        }
    }
    return 0;
}

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", f_UpdateBerryNutsMinigameController);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_80114170);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_801142C0);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", f_UpdateBerryNutsHostDialogue);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_801147D0);

extern u8 D_8011CBB4[];
extern u8 D_8011CC9C[];
void func_80112D80();
void f_UpdateTinyMouseVillageNpcActor(u8 *a)
{
    s8 **g;
    u8 *p;
    u8 *s;
    u8 v;
    u8 k;

    switch (a[4]) {
    case 0:
        g = D_800ECF58;
        if (func_800519E0(a, 0xF, g[0x12], D_8011CBB4) != 0) {
            break;
        }
        *(s8 **)(a + 0x3C) = g[0x13];
        a[0] = 9;
        H(a, 0x80) = 0xB4;
        H(a, 0x82) = 0x168;
        H(a, 0x84) = 0x50;
        H(a, 0x86) = 0x90;
        a[0x2B] = 0;
        a[0x29] = 0;
        a[4]++;
        p = func_8003315C(a);
        if (p != NULL) {
            *(void **)(p + 0x1C) = func_80112D80;
        }
        switch (a[3]) {
        case 1:
            if (D_800BF9C3 & 0x80) {
                a[4] = 3;
                break;
            }
            func_80077C40(a, D_8001B4DC, 5);
            break;
        case 2:
            if (D_800BF9C3 & 0x80) {
                a[4] = 3;
                break;
            }
            func_80077C40(a, D_8001B4DC, 9);
            break;
        case 3:
            if (D_800BF9C3 & 0x80) {
                a[4] = 3;
                break;
            }
            func_80077C40(a, D_8001B4DC, 8);
            func_80051B04(*(void **)(a + 0xDC), 0x12, 0x15);
            break;
        case 4:
            if (D_800BF9C3 & 0x80) {
                a[4] = 3;
                break;
            }
            func_80077C40(a, D_8001B4DC, 3);
            break;
        case 5:
            s = (u8 *)&D_800BF870;
            v = s[0x153];
            if (v & 0x80) {
                D_800BF858 = 0x708;
                a[5] = 0x63;
            } else {
                s[0x1E2] = 0;
                if (v == 0) {
                    if (s[0x8C] != 0) {
                        a[5] = 5;
                    } else if (s[0x8B] != 0) {
                        a[5] = 4;
                    } else if (s[0x8A] != 0) {
                        a[5] = 1;
                    } else {
                        a[5] = 0;
                    }
                } else if (v == 1 || v == 3) {
                    k = s[0x8C];
                    if (k == 0xFF) {
                        a[5] = 8;
                    } else if (k != 0) {
                        if (*(u16 *)(s + 0x1B4) >= 0xC8) {
                            a[5] = 6;
                        } else {
                            a[5] = 7;
                        }
                    } else {
                        a[5] = 2;
                    }
                } else {
                    k = s[0x8C];
                    if (k == 0xFF) {
                        a[5] = 8;
                    } else if (k != 0) {
                        if (*(u16 *)(s + 0x1B4) >= 0xC8) {
                            a[5] = 6;
                        } else {
                            a[5] = 7;
                        }
                    } else {
                        a[5] = 3;
                    }
                }
                D_800BF9C3 = 0;
            }
            func_80077C40(a, D_8001B4DC, 0);
            H(a, 0x56) = 0x600;
            break;
        case 6:
            if (D_800BF9C3 & 0x80) {
                a[4] = 3;
                break;
            }
            func_80077C40(a, D_8001B4DC, 5);
            break;
        }
        break;
    case 1:
        func_8007778C(a);
        switch (a[3]) {
        case 1:
            func_80113488(a);
            break;
        case 2:
            func_801136F0(a);
            break;
        case 3:
            switch (a[6]) {
            case 0:
                if (a[0x2B] == 3) {
                    a[6] = 1;
                    func_80042354(1, 3);
                }
                break;
            case 1:
                a[6] = 2;
                func_80040CDC(a, D_8001B4DC, D_8011CC9C);
                a[0x70] = 1;
                break;
            case 2:
                func_80041098(a);
                if (a[0x70] == 0xFF) {
                    a[6] = 0;
                    func_80042310();
                }
                break;
            }
            break;
        case 4:
            func_80113A7C(a);
            break;
        case 5:
            f_UpdateBerryNutsHostDialogue(a);
            if (H(a, 0xE) == 1) {
                s16 m = H(*(u8 **)(a + 0x38), 2);
                if (m == 1) {
                    func_80074590(0x10, -3, 0);
                } else if (m == 2) {
                    func_80074590(0x81, 6, 0);
                }
            }
            break;
        case 6:
            func_801147D0(a);
            break;
        }
        func_8004190C(a);
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

s32 func_80114EAC(u8 *a)
{
    u8 *t;

    if (a[3] == 4) {
        *(s16 *)(a + 0x36) += 0xC;
    } else {
        *(s16 *)(a + 0x2E) += 0xC;
    }
    t = D_800E7E80;
    *(s16 *)(t + 0x2E) = *(s16 *)(a + 0x2E);
    *(s16 *)(t + 0x32) = *(s16 *)(a + 0x32) + (s16)(*(s16 *)(a + 0x8A) - 100);
    *(s16 *)(t + 0x36) = *(s16 *)(a + 0x36);
    return 0;
}

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_80114F1C);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_8011562C);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_80115F1C);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_801160A4);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_8011626C);

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
#define T2_rtpt() __asm__ volatile(".word 0x4A280030")
#define T2_nclip() __asm__ volatile(".word 0x4B400006")
#define T2_stflg(r0) __asm__ volatile("cfc2 $12, $31;" "nop;" "sw $12, 0( %0 )" : : "r"(r0) : "$12", "memory")
#define T2_stopz(r0) __asm__ volatile("swc2 $24, 0( %0 )" : : "r"(r0) : "memory")
#define T2_stotz(r0) __asm__ volatile("swc2 $7, 0( %0 )" : : "r"(r0) : "memory")
#define T2_stsz1(r0) __asm__ volatile("swc2 $17, 0( %0 )" : : "r"(r0) : "memory")
#define T2_stsz2(r0) __asm__ volatile("swc2 $18, 0( %0 )" : : "r"(r0) : "memory")
#define T2_stsz3(r0) __asm__ volatile("swc2 $19, 0( %0 )" : : "r"(r0) : "memory")
extern void *D_800BF544;
#define K_lddp(r0) __asm__ volatile("mtc2 %0, $8" : : "r"(r0))
#define K_ldrgb(r0) __asm__ volatile("lw $24, %0;" "nop;" "mtc2 $24, $6" : : "m"(*(r0)) : "$24")
#define K_dpcs() __asm__ volatile("nop;" "nop;" ".word 0x4A780010")
#define K_strgb2(r0) __asm__ volatile("swc2 $22, 0( %0 )" : : "r"(r0) : "memory")
static inline void K_depth(u32 *c, s32 *z)
{
    K_lddp(*z * 2);
    K_ldrgb(c);
    K_dpcs();
    K_strgb2(c);
}
u32 *func_801163E0(u32 *f, u32 *ot, s32 n)
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
                    e = *otz >> 10;
                    *otz = (*otz >> e) + (e << 9);
                    if ((u32)(*otz - 4) >= 0x7FC) {
                        *otz = -1;
                    }
                    if (*otz >= 0) {
                        p->uv2 = ((u16 *)f)[0x11];
                        K_depth(&p->rgb0, otz);
                        K_depth(&p->rgb1, otz);
                        K_depth(&p->rgb2, otz);
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
static inline void K_depth_4647(s32 z, u32 *c)
{
    K_lddp(z * 2);
    K_ldrgb(c);
    K_dpcs();
    K_strgb2(c);
}
u32 *func_80116708(u32 *f, u32 *ot, s32 n)
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
                                K_depth_4647(*otz, &p->rgb0);
                                K_depth_4647(*otz, &p->rgb1);
                                K_depth_4647(*otz, &p->rgb2);
                                K_depth_4647(*otz, &p->rgb3);
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

#define AREA_gte_lddp(r0) __asm__ volatile("mtc2	%0, $8" : : "r"(r0))
#define AREA_gte_ldrgb_r(r0) __asm__ volatile("mtc2	%0, $6" : : "r"(r0))
#define AREA_gte_dpcs() __asm__ volatile("nop;" "nop;" ".word 0x4A780010")
#define AREA_gte_strgb(r0) __asm__ volatile("swc2	$22, 0( %0 )" : : "r"(r0) : "memory")
void func_80116AE8(s32 d, u32 *p) {
    AREA_gte_lddp(d * 2);
    AREA_gte_ldrgb_r(*p);
    AREA_gte_dpcs();
    AREA_gte_strgb(p);
}

void func_80116B14(u32 *a, s32 b)
{
    u8 pad[0x20];
    u32 w;
    u32 *q;

    if (D_800BF871 < 4) {
        func_800803DC();
    } else {
        q = a;
        a += 4;
        gte_ldfcdir(0, 0, 0);
        w = *q;
        func_80116708(func_801163E0(a, b, w & 0xFFFF), b, w >> 16);
    }
}

typedef struct {
    s32 vx, vy;
} T2Pt32;
typedef struct {
    u8 pad0[2];
    s16 x;
    u8 pad4[6];
    s16 y;
    u8 padC[0x14];
    s16 rx;
    u16 ry;
} T2CamD0;
extern T2CamD0 D_1F8000D0_3bb0;
extern s32 D_800A3F90;
extern s32 D_800A3F94;
void func_80116B9C(u8 *a)
{
    T2Pt32 v0, v1, v2;
    T2CamD0 *c;
    s32 ang, r, dx, dz;
    u16 t;

    if (D_800BF871 < 4) {
        a[6] = 0;
        return;
    }
    c = &D_1F8000D0_3bb0;
    t = c->ry;
    D_800A3F90 = 0x2800;
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
    v1.vy -= dz;
    v2.vx -= dx;
    v0.vx -= dx;
    v2.vy -= dz;
    v0.vy -= dz;
    v0.vx /= 640;
    v0.vy /= 640;
    v1.vx /= 640;
    v1.vy /= 640;
    v2.vx /= 640;
    v2.vy /= 640;
    a[6] = 0;
    func_80116E68(a, &v0, &v1, &v2);
}

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
        p = (s16 *)D_800ECF58[8];
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
void func_80116E68(u8 *a, s32 *p0, s32 *p1, s32 *p2) {
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
void func_801173A8(u8 *a)
{
    u16 *p = D_800ECF78;
    u16 t;

    *(u16 **)(a + 0xC) = p;
    *(u16 *)(a + 8) = p[0];
    t = p[1];
    a[7] = 0;
    *(u16 *)(a + 0xA) = t;
}

typedef struct { u16 a, b; } Range;
extern Range D_8011D888[];
extern Range D_8011D8A0[];
extern Range D_8011D8EC[];
extern Range D_8011D908[];
extern Range D_8011D94C[];
extern u8 *D_1F80021C;
void func_801173D4(s16 kind, s16 idx)
{
    Range *t;
    s32 n, base;
    u8 *p;
    switch (kind) {
    case 0:
        t = D_8011D888;
        n = 3;
        base = 0;
        break;
    case 1:
        t = D_8011D8A0;
        n = 0x13;
        base = 0;
        break;
    case 2:
        t = D_8011D8EC;
        n = 0x14;
        base = 0;
        break;
    case 3:
        t = D_8011D908;
        n = 0xA;
        base = 0;
        break;
    case 4:
        t = D_8011D94C;
        n = 0x11;
        base = 0;
        break;
    default:
        return;
    }
    p = D_1F80021C + t[idx].a * 32 + base * 32;
    func_8001D2A8(n, p, p + (t[idx].b + 1) * 32, 0);
}

extern s16 D_800BED82;
extern M2C_UNK D_8011D5D0;
extern M2C_UNK D_8011D774;
void func_801174B0(void) {
    func_80075448(0xC, &D_8011D5D0, 0x10, D_800BED82);
    func_80075448(0xB, &D_8011D774, 0x10, D_800BED82);
}

void func_80117500(u8 *a, s32 *b) {
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
        i = D_8011FC18[1] > D_8011FC18[0];
        break;
    case 5:
        i = (D_8011FC18[2] > D_8011FC18[0]) * 2;
        break;
    case 9:
        i = 0;
        if (D_8011FC18[3] > D_8011FC18[0]) {
            i = 3;
        }
        break;
    case 6:
        i = 1;
        if (D_8011FC18[2] > D_8011FC18[1]) {
            i = 2;
        }
        break;
    case 10:
        i = 1;
        if (D_8011FC18[3] > D_8011FC18[1]) {
            i = 3;
        }
        break;
    case 12:
        i = 2;
        if (D_8011FC18[3] > D_8011FC18[2]) {
            i = 3;
        }
        break;
    case 11:
        if (D_8011FC18[3] > D_8011FC18[0]) {
            i = 1;
            if (D_8011FC18[3] > D_8011FC18[1]) {
                i = 3;
            }
        } else {
            i = D_8011FC18[1] > D_8011FC18[0];
        }
        break;
    case 13:
        if (D_8011FC18[3] > D_8011FC18[0]) {
            i = 2;
            if (D_8011FC18[3] > D_8011FC18[2]) {
                i = 3;
            }
        } else {
            i = (D_8011FC18[2] > D_8011FC18[0]) * 2;
        }
        break;
    case 14:
        if (D_8011FC18[3] > D_8011FC18[1]) {
            i = 2;
            if (D_8011FC18[3] > D_8011FC18[2]) {
                i = 3;
            }
        } else {
            i = 1;
            if (D_8011FC18[2] > D_8011FC18[1]) {
                i = 2;
            }
        }
        break;
    case 7:
        if (D_8011FC18[2] > D_8011FC18[0]) {
            i = 1;
            if (D_8011FC18[2] > D_8011FC18[1]) {
                i = 2;
            }
        } else {
            i = D_8011FC18[1] > D_8011FC18[0];
        }
        break;
    case 15:
    default:
        m = D_8011FC18[0];
        i = 0;
        for (j = 1; j < 4; j++) {
            v = &D_8011FC18[j];
            if (m < *v) {
                i = j;
                m = *v;
            }
        }
        break;
    }
    m = D_8011FC18[i];
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
extern ColTable D_8011FBF4;
extern ColTable D_8011FC00;
extern s32 D_8011FC28[];
extern u8 D_800BF816;
extern s32 D_1F8001C8[];
extern s16 D_1F8001A4;
extern u16 D_1F8001A6;

s32 func_8011778C(s32 *pos, s16 *off)
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
        t = &D_8011FBF4;
    } else {
        t = &D_8011FC00;
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
                            D_8011FC28[j] = d;
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
                                D_8011FC18[0] = D_8011FC28[0];
                                D_8011FC18[1] = D_8011FC28[1];
                                D_8011FC18[2] = D_8011FC28[2];
                                D_8011FC18[3] = D_8011FC28[3];
                            }
                        }
                    }
                }
            } while (list[++m] != 0xFFFF);
        }
        if (hit == NULL) {
            break;
        }
        func_80117500(hit, v);
        ret = 1;
        found[n++] = hit;
    }
    pos[0] = v[0] - (off[0] << 16);
    pos[2] = v[2] - (off[2] << 16);
    return ret;
}


s32 func_80117B24(s32 *pos, s16 *off, s16 flag)
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
        t = &D_8011FBF4;
    } else {
        t = &D_8011FC00;
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
                    D_8011FC28[j] = d;
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


s32 func_80117DE8(s32 *pos, s16 *off)
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
        t = &D_8011FBF4;
    } else {
        t = &D_8011FC00;
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
                D_8011FC28[j] = d;
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

#define U(p, o) (*(u16 *)((u8 *)(p) + (o)))

s32 func_80118054(u8 *a)
{
    u8 *t = D_800E7E80;
    u8 *p;
    s32 ang;
    u16 b;

    switch (a[0x78]) {
    case 0: {
        u16 az = U(a, 0x76);
        u16 tz = U(t, 0x36);
        u16 ax = U(a, 0x74);
        u16 tx = U(t, 0x2E);
        s16 dz = az - tz;
        s16 dx = ax - tx;

        if (dz * dz + dx * dx < H(a, 0x68) * H(a, 0x68)) {
            U(t, 0x2E) = ax;
            U(t, 0x36) = U(a, 0x76);
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
        H(a, 0x64) = func_80084080((s16)(U(a, 0x76) - U(t, 0x36)) * (s16)(U(a, 0x76) - U(t, 0x36)) +
                                   (s16)(U(a, 0x74) - U(t, 0x2E)) * (s16)(U(a, 0x74) - U(t, 0x2E)));
        if ((H(a, 0x64) = H(a, 0x64) / H(t, 0x44)) == 0) {
            H(a, 0x64) = 1;
        }
        H(a, 0x64) = 0x1000 / H(a, 0x64);
        H(a, 0x66) = 0x1000;
        H(a, 0x74) -= U(t, 0x2E);
        H(a, 0x76) -= U(t, 0x36);
        a[0x78]++;
        break;
    case 4:
        p = *(u8 **)(a + 0x6C);
        if ((H(a, 0x66) -= H(a, 0x64)) <= 0) {
            H(a, 0x66) = 0;
        }
        H(t, 0x2E) = U(p, 4) - H(a, 0x66) * H(a, 0x74) / 4096;
        H(t, 0x36) = U(p, 6) - H(a, 0x66) * H(a, 0x76) / 4096;
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

extern u16 D_1F800160;
extern u16 D_1F800164;

s32 f_UpdateTinyMouseVillageEntranceActor(u8 *a)
{
    u8 *t = D_800E7E80;
    u16 dx = D_1F800160 - U(a, 0x2E);
    u16 dz = D_1F800164 - U(a, 0x36);
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
        e = U(a, 0x72) + U(a, 0x74);
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
        H(a, 0x64) += U(a, 0x76);
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
        H(t, 0x2E) = U(a, 0x2E) + func_80083F50(-H(a, 0x64)) * H(a, 0x66) / 4096;
        H(t, 0x36) = U(a, 0x36) + func_80083E80(-H(a, 0x64)) * H(a, 0x66) / 4096;
        if (H(t, 0x44) == 0) {
            return 1;
        }
        break;
    }
    return 0;
}

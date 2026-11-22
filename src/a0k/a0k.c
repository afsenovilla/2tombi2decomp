#include "common.h"
#include "game.h"
#include "m2c.h"
#include "gte.h"

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_801095C8);

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

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_801097DC);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_8010996C);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_80109AC8);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_80109C0C);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_80109DBC);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_80109F14);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_8010A034);

extern u8 **D_1F800154;
extern u8 D_1F80015C;
extern u8 D_1F800183;
extern u8 **D_1F80013C;
extern u8 D_1F800144;
extern u8 D_1F800182;
extern u8 **D_1F800148;
extern u8 D_1F800150;
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

typedef struct {
    u8 pad[0xA];
    s16 count;
    u8 *entries;
    u32 pending;
    u32 done;
} RewardSet;
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

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_8010A6F0);

typedef struct { u16 acc, inc, max, dec; } SpeedTbl;
extern SpeedTbl D_800A455C[];
extern SpeedTbl D_800A4574;
extern u16 D_1F8000F2;
#define S16(o) (*(s16 *)(a + (o)))
#define U16(o) (*(u16 *)(a + (o)))
typedef struct { s16 pad; s16 x; s16 pad2; s16 y; s16 pad3; s16 z; } PosV;
extern u8 D_800BF80E_58ec;
extern u16 D_1F800192;
extern u8 D_1F800137;
extern u8 D_800BF808[];
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
extern s32 D_800BF85C;
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

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_8010B760);

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

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_8010F544);

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

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_8011014C);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", menu);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", f_UpdateBerryNutsRetryMenu);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_80110938);

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

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_8011133C);

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

extern s16 D_1F800240;
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

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_80112884);

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

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_80113C50);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", f_UpdateBerryNutsMinigameController);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_80114170);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_801142C0);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", f_UpdateBerryNutsHostDialogue);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_801147D0);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", f_UpdateTinyMouseVillageNpcActor);

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

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_801163E0);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_80116708);

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

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_80116B9C);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_80116E68);

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

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_80117500);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_8011778C);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_80117B24);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_80117DE8);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", func_80118054);

INCLUDE_ASM("asm/a0k/nonmatchings/a0k", f_UpdateTinyMouseVillageEntranceActor);

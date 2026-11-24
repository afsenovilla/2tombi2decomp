#include "common.h"
#include "game.h"
#include "m2c.h"
#include "gte.h"

extern u8 D_1F800137;
extern u8 D_800BF840;
extern u8 D_800E7E81;

void func_8010A528(u8 *a) {
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

void func_8010A528();
u8 *func_8010A6E8(void)
{
    u8 *a = func_8007A980(0, 3, 1);

    if (a == NULL) {
        return NULL;
    }
    *(void **)(a + 0x1C) = func_8010A528;
    a[2] = 1;
    a[0x28] |= 0x80;
    return a;
}

s32 func_8010A73C(u8 *a, s32 b) {
    s32 s = (func_80083F50(M2C_FIELD(a, s16 *, 0x56)) * M2C_FIELD(a, s16 *, 0x44)) >> 4;
    s32 c = func_80083E80(M2C_FIELD(a, s16 *, 0x56)) * M2C_FIELD(a, s16 *, 0x44);

    M2C_FIELD(a, s32 *, 0x2C) += s;
    M2C_FIELD(a, s32 *, 0x34) -= c >> 4;
    if (b != 0) {
        return func_8010A7D8(a);
    }
    return 0;
}

extern s16 D_1F8000C0_65b0[];
s32 func_8010A7D8(u8 *a) {
    s16 z = (-func_80083E80(M2C_FIELD(a, s16 *, 0x56)) * M2C_FIELD(a, s16 *, 0x80)) >> 12;
    s16 *v;

    v = D_1F8000C0_65b0;
    v[0] = (func_80083F50(M2C_FIELD(a, s16 *, 0x56)) * M2C_FIELD(a, s16 *, 0x80)) >> 12;
    v[1] = M2C_FIELD(a, s16 *, 0x86) - M2C_FIELD(a, s16 *, 0x84);
    v[2] = z;
    return func_801258A4(a + 0x2C, v) != 0;
}

typedef struct { s16 x, y, z, pad; } AreaSVec;
extern AreaSVec D_1F8000C0;
extern s32 D_8012C580[];
s32 func_8010A868(u8 *a) {
    s16 y;

    if (a[0x29] == 0) {
        D_1F8000C0.x = 0;
        y = M2C_FIELD(a, s16 *, 0x86) - M2C_FIELD(a, s16 *, 0x84);
        D_1F8000C0.z = 0;
        D_1F8000C0.y = y;
        if (func_80125C5C(a + 0x2C, &D_1F8000C0, 0) > 0) {
            a[0x29] = 1;
        }
    }
    return a[0x29];
}

typedef struct { s16 a, b, c, d; } SpeedRow8010A8D0;
extern SpeedRow8010A8D0 D_800A455C_c872[];
extern SpeedRow8010A8D0 D_800A4574_8b42;
extern u8 D_800BF808_1760[];
extern u16 D_1F8000F2_1841;
#define B8(o) (*(u8 *)(a + (o)))
#define I16(o) (*(s16 *)(a + (o)))
#define W16(o) (*(u16 *)(a + (o)))
void func_8010A8D0(u8 *a) {
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
    if (D_800BF808_1760[0xE] != 0 && D_800BF808_1760[0x45] != 0) {
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
    ang = (((f & 0x7F) << 5) - D_1F8000F2_1841 + 0x1000) & 0xFFF;
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
extern u8 D_800BF80E;
extern u16 D_1F800192;
extern u8 D_1F80027A;
extern u8 D_800BF80A;
static inline void fall_step(u8 *a)
{
    func_8010B634(a);
    if (a[0x29] != 0) {
        if (*(s16 *)(a + 0x50) > 0x1E00) {
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
void func_8010ACB8(u8 *a)
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
    ang = (((c & 0x7F) << 5) - D_1F8000F2_1841 + 0x1000) & 0xFFF;
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
extern u8 D_800E7E80[];
void func_8010AEC4(u8 *a)
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

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8010B068);

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
void func_8010B2D0(u8 *a) {
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

void func_8010B458(u8 *a)
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

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8010B634);

void func_8010B8B8(u8 *a)
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

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8010BABC);

void func_8010BD80(u8 *a)
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
    func_8010B634(a);
    if (a[0x29] != 0) {
        if (*(s16 *)(a + 0x50) > 0x1E00) {
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

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8010BEBC);

extern s16 D_1F80019E;
extern u8 D_800BFE55;
extern u16 D_1F80017C;
extern u16 D_1F800210;
extern u16 D_800BF812;
#define S16(p, o) (*(s16 *)((u8 *)(p) + (o)))
extern s32 D_1F80009C_baed;
extern s16 D_1F80018E;
extern u8 *D_1F800184;
extern u16 D_1F80008C;
void func_8010C510(u8 *a)
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

void func_8010C6E4(u8 *a)
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
    func_8010B634(a);
    if (a[0x29] != 0) {
        if (*(s16 *)(a + 0x50) > 0x1E00) {
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

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8010C8E4);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8010CF30);

void func_8010CFAC(u8 *a)
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

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8010D288);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8010D6B4);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8010DA78);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8010DBE4);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8010E1F4);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8010E3D8);

void func_8010EA30(u8 *a)
{
    s32 d;
    s32 e;

    switch (a[6]) {
    case 0:
        func_80074590(0x23, 0, 0);
        func_80054D14(a, 0x57, 0);
        I16(0x44) = 0x1000;
        I16(0x7C) = a[0x2B] << 4;
        a[6]++;
        break;
    case 1:
        func_80076D68(a);
        I16(0x56) = func_800776F8((s16)(W16(0x7C) + 0x800), I16(0x56), 0x80);
        d = (func_80083F50(I16(0x7C)) * I16(0x44)) >> 4;
        e = (func_80083E80(I16(0x7C)) * I16(0x44)) >> 4;
        *(s32 *)(a + 0x2C) += d;
        *(s32 *)(a + 0x34) -= e;
        W16(0x44) -= 0x100;
        if (I16(0x44) < 0) {
            I16(0x44) = 0;
            a[6]++;
            func_80054D14(a, 2, 7);
        }
        break;
    case 2:
        func_80076D68(a);
        a[5] = 0;
        a[6] = 0;
        a[7] = 0;
        a[0] &= 3;
        break;
    }
}

void func_8010EBA8(u8 *a)
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
        D_800BF808_1760[6] = 0;
        func_8004ED0C(D_800BF808_1760[3], 1);
        if (D_800BF808_1760[2] == 2) {
            a[0] |= 2;
        } else if (D_800BF808_1760[2] == 3) {
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
            D_800BF808_1760[2] = 0;
            D_800BF808_1760[6] = 1;
        }
        break;
    case 3:
        func_80076D68(a);
        break;
    }
}

extern u16 D_1F800170;
extern u16 D_1F800166;
extern u16 D_1F800190;
/* func_8010F948, inlined */
static inline void inl_8010F948(u8 *a)
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
void func_8010ED88(u8 *a) {
    if ((D_800ECF54 & D_1F800170) || (a[0x174] & 0x30)) {
        a[0x165] = 1;
    } else {
        a[0x165] = 0;
    }
    switch (a[5]) {
    case 0x0:
        func_8010D288(a);
        if (D_1F800137 != 0 && a[5] == 0) {
            a[0] = 3;
            D_800BF80E = 1;
            a[4] = 4;
            D_1F800166 = 0;
            D_1F800190 = 0;
        }
        break;
    case 0x1:
        func_8010D6B4(a);
        break;
    case 0x2:
        func_8010DBE4(a);
        if (D_1F800137 != 0 && a[5] == 2) {
            a[0] = 3;
            D_800BF80E = 1;
            a[4] = 4;
            D_1F800166 = 0;
            D_1F800190 = 0;
        }
        break;
    case 0x3:
        func_8010DA78(a);
        break;
    case 0x4:
        inl_8010F948(a);
        break;
    case 0x5:
        func_8010E1F4(a);
        break;
    case 0x6:
        func_8010E3D8(a);
        break;
    case 0x7:
        func_8010EA30(a);
        break;
    case 0x11:
        func_8005F2F0(a);
        break;
    case 0x12:
        func_8010EBA8(a);
        if (D_1F800137 != 0) {
            if (D_800BF80A < 4) {
                a[0] = 3;
            }
            a[4] = 4;
            D_1F800166 = 0;
            D_1F800190 = 0;
        }
        break;
    case 0x38:
        func_8010B8B8(a);
        break;
    case 0x39:
        func_8010BABC(a);
        break;
    case 0x3A:
        func_800624B4(a);
        break;
    case 0x1B:
        func_80061A7C(a);
        break;
    case 0x1F:
        func_8010BEBC(a);
        if (D_1F800137 != 0) {
            a[0] = 3;
            D_800BF80E = 1;
            a[4] = 4;
            D_1F800166 = 0;
            D_1F800190 = 0;
        }
        break;
    }
}

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8010F01C);

extern u16 D_800E7E68;
extern u8 D_800BF80F;
void func_8010F63C(u8 *a) {
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
        func_8010ED88(a);
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
        func_8010F01C(a);
        func_800597AC(a);
        D_800E7E68 = held;
        D_800ECF54 = pad;
        break;
    }
}

extern s16 D_1F8001C6;
s32 func_8010F798(u8 *a) {
    s32 r;
    s32 d;

    if (a[4] == 4) {
        return 0;
    }
    r = 0x6C;
    if (*(s16 *)(a + 0x17E) & 0x8000) {
        r = 0x82;
    }
    d = *(u16 *)(a + 0x2E) - 0x2300;
    if ((u16)(r + d) <= r * 2 && (u32)(*(u16 *)(a + 0x36) - 0x2937) < 0x9F) {
        if ((u16)(*(u16 *)(a + 0x32) + 0xDAC) < 0x141) {
            D_1F8001C6 = 1;
            a[5] = 6;
            a[6] = 0;
            a[7] = 0;
            return 1;
        }
    } else {
        return 0;
    }
    return 0;
}

void func_8010F84C(u8 *a) {
    u16 x = M2C_FIELD(a, u16 *, 0x2E);

    if ((u16)(x - 0x1BF0) < 0x1A8) {
        if (M2C_FIELD(a, s16 *, 0x36) < 0x28E1) {
            M2C_FIELD(a, s16 *, 0x36) = 0x28E1;
        }
    } else if ((u16)(x - 0x1D98) < 0xD80) {
        if (M2C_FIELD(a, s16 *, 0x36) < 0x29E0) {
            M2C_FIELD(a, s16 *, 0x36) = 0x29E0;
        }
    } else if ((s16)x >= 0x2B18 && M2C_FIELD(a, s16 *, 0x36) < 0x297B) {
        M2C_FIELD(a, s16 *, 0x36) = 0x297B;
    }
}

extern s32 D_8012B5BC[];
void func_8010F8DC(u8 *a) {
    s32 d;

    if (a[5] < 2 && (M2C_FIELD(a, s16 *, 0x6A) & 0xF000) == 0x1000) {
        d = (s16)(-0x8000 - (M2C_FIELD(a, s16 *, 0x56) << 4));
        if (d < 0) {
            d = -d;
        }
        if (d <= 0x2000) {
            a[5] = 5;
            a[6] = 0;
            a[7] = 0;
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
extern u8 D_1F800137;
typedef struct {
    s16 pad0;
    s16 x;
    s16 pad4;
    s16 y;
    s16 pad8;
    s16 z;
} HiPos;
void func_8010F948(u8 *a)
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

extern u8 D_1F800236;
extern u8 D_800BF871;
void func_8010CFAC(u8 *a);
void func_8010F9E4(u8 *a) {
    u8 *e;
    s32 m;

    func_8010A6E8();
    a[1] = 1;
    m = D_1F800236;
    M2C_FIELD(a, s16 *, 0x6A) = 0;
    if (m == 5) {
        if (D_800BF871 == 1) {
            goto c00;
        }
        M2C_FIELD(a, s16 *, 0x56) = 0x400;
    } else if (D_800BF871 == 8) {
        D_1F800137 = 2;
        a[4] = 4;
        M2C_FIELD(a, s16 *, 0x56) = 0x800;
    } else {
    c00:
        M2C_FIELD(a, s16 *, 0x56) = 0xC00;
    }
    M2C_FIELD(a, s16 *, 0x58) = 0;
    M2C_FIELD(a, s16 *, 0x172) = 0;
    func_80054D14(a, 2, 0);
    e = func_8003315C(a);
    if (e != NULL) {
        M2C_FIELD(e, void **, 0x1C) = func_8010CFAC;
    }
    D_1F8001C6 = 0;
}

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8010FAB0);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8010FBFC);

extern u8 **D_1F80014C;
extern u8 D_1F800152;
extern u8 D_1F800182;
s32 func_8010FD30(u8 *a, s32 r, s32 h) {
    u8 **l;
    u8 *e;
    s16 dx;
    s16 dz;
    s32 k;
    u16 d;

    l = D_1F80014C;
    D_1F800182 = D_1F800152;
    while (D_1F800182 != 0) {
        e = *l;
        D_1F800182--;
        l++;
        k = e[0];
        if (k == 1 && e[2] == 0x22) {
            dx = *(u16 *)(a + 0x2C) - *(u16 *)(e + 0x2E);
            dz = *(u16 *)(a + 0x34) - *(u16 *)(e + 0x36);
            d = func_80084080(dx * dx + dz * dz);
            if (r + *(s16 *)(e + 0x80) < d) {
                return 0;
            }
            if ((u16)((*(u16 *)(a + 0x30) - *(u16 *)(e + 0x32)) + (*(u16 *)(e + 0x84) + h)) > h * 2 + *(s16 *)(e + 0x86)) {
                return 0;
            }
            e[0x2B] = k;
            return 1;
        }
    }
    return 0;
}

extern s16 D_1F80018C;
extern u8 D_800BF873;
void func_8010FE90(u8 *a, u8 *b)
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

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8010FFF4);

extern u16 D_1F80009C;

void func_801101D4(u8 *a, u8 *b, s32 k)
{
    s16 ang;

    if (func_8002300C(a, b, *(s16 *)(b + 0x80) * k) == 0) {
        return;
    }
    ang = D_1F80009C & 0xFFF;
    if ((b[2] == 0x25 || !(*(s16 *)(a + 0x17E) & 0x8200)) && D_1F80018E == 0 && D_1F800137 == 0 && !(b[0] & 2)) {
        if (abs((s16)((ang - *(u16 *)(a + 0x56)) << 4)) < 0x2001 && (a[5] != 0x1F || b == *(u8 **)(a + 0x10))) {
            do {
                D_1F80018E = 0x1200;
            } while (0);
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

void func_80110370(u8 *a, u8 *b)
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

extern u8 D_800BF9C7;
extern u8 D_800BF8C0;

void func_8011053C(u8 *a, u8 *b)
{
    s16 ang;
    u8 k;

    if (b[0] & 2) {
        return;
    }
    if (func_8002300C(a, b, *(s16 *)(b + 0x80) * 3) == 0) {
        return;
    }
    if (D_1F800137 == 0 && (u16)(*(u16 *)(a + 0x2E) - *(u16 *)(b + 0x2E) + 0x96) < 0x12D) {
        if (a[5] < 2) {
            if (!(D_800BF9C7 & 0x80)) {
                D_1F800137 = 2;
                b[0x29] = 1;
            }
        } else if (D_800BF8C0 != 0xFF && a[5] == 2) {
            k = (*(u8 **)(a + 0x10))[8];
            if (k == a[5]) {
                a[6] = 1;
                *(s16 *)(a + 0x7A) = 0x230C;
                D_1F800137 = k;
                *(s16 *)(a + 0x7E) = 0x2B4E;
            }
        }
    }
    if (*(s16 *)(a + 0x80) + *(s16 *)(b + 0x80) >= D_1F80008C) {
        s32 s;
        s32 c;

        ang = (D_1F80009C + 0x800) & 0xFFF;
        s = (func_80083F50(ang) * (*(s16 *)(a + 0x80) + *(s16 *)(b + 0x80))) >> 12;
        c = func_80083E80(ang) * (*(s16 *)(a + 0x80) + *(s16 *)(b + 0x80));
        *(s16 *)(a + 0x2E) = *(u16 *)(b + 0x2E) + s;
        *(s16 *)(a + 0x36) = *(u16 *)(b + 0x36) - (c >> 12);
    }
}

void func_801106F0(u8 *a, u8 *b)
{
    s16 ang;

    if (*(s16 *)(a + 0x17E) & 0x8200) {
        if (func_8002300C(a, b, *(s16 *)(b + 0x80)) == 0) {
            return;
        }
        ang = D_1F80009C & 0xFFF;
    } else {
        if (func_8002300C(a, b, *(s16 *)(b + 0x80) * 2) == 0) {
            return;
        }
        b[0x2B] = 1;
        if (D_1F80008C > *(s16 *)(a + 0x80) + *(s16 *)(b + 0x80) + 0x5A) {
            return;
        }
        b[0x2B] = 2;
        ang = D_1F80009C & 0xFFF;
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

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_801108A0);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80110AB8);

#define U(p, o) (*(u16 *)((p) + (o)))
#define S(p, o) (*(s16 *)((p) + (o)))
#define L(p, o) (*(s32 *)((p) + (o)))

s32 func_80110C7C(u8 *a, u8 *b, u8 *c)
{
    s32 r;
    s16 x;
    s32 w;

    r = 0x32;
    if (a[0xD] & 0x10) {
        r = 0x5A;
    }
    if ((u16)(U(a, 0x32) - (u16)L(c, 0x30) + (U(a, 0x84) + U(b, 0x84))) > S(a, 0x86) + S(b, 0x86)) {
        return 0;
    }
    w = U(b, 0x80);
    if ((u16)(U(a, 0x36) - (u16)L(c, 0x34) + (r + w)) > r * 2 + S(b, 0x82)) {
        return 0;
    }
    if ((u16)(r + (U(a, 0x2E) - (u16)L(c, 0x2C) + 0x8C)) > r * 2 + 0x118) {
        return 0;
    }
    x = U(a, 0x2E);
    if (x < L(c, 0x2C) - 0x8C) {
        U(a, 0x2E) = (u16)L(c, 0x2C) - 0x8C;
    } else if (S(a, 0x36) < L(c, 0x34) + (s16)w - 0x118 && L(c, 0x2C) + 0x8C < x) {
        U(a, 0x2E) = (u16)L(c, 0x2C) + 0x8C;
    }
    if (L(c, 0x34) + S(b, 0x80) < S(a, 0x36)) {
        U(a, 0x36) = (u16)L(c, 0x34) + U(b, 0x80);
    }
    U(a, 0x36) -= 10;
    if (S(a, 0x32) >= L(c, 0x30) - S(b, 0x84) - S(a, 0x84)) {
        U(a, 0x32) = (u16)L(c, 0x30) - U(b, 0x84) - U(a, 0x84);
        func_80022C78(a);
    }
}

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80110E20);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80111184);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_801114B0);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80111640);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_801117B0);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80111974);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80111D24);

extern u8 **D_1F800158;
extern u8 D_1F80015E;

void func_80111FB4(u8 *a)
{
    u8 **l = D_1F800158;
    u8 *p;
    s16 dx, dz;
    s32 d;

    D_1F800182 = D_1F80015E;
    while (D_1F800182 != 0) {
        p = *l;
        D_1F800182--;
        l++;
        if ((p[0] & 1) && p[2] == 5) {
            dx = *(u16 *)(a + 0x2E) - *(u16 *)(p + 0x2E);
            dz = *(u16 *)(a + 0x36) - *(u16 *)(p + 0x36);
            d = func_80084080(dx * dx + dz * dz);
            if ((u16)d > *(s16 *)(a + 0x80) + *(s16 *)(p + 0x80)) {
                return;
            }
            if ((u16)((*(u16 *)(a + 0x32) - *(u16 *)(p + 0x32)) + (*(u16 *)(p + 0x84) + (*(u16 *)(a + 0x86) - *(u16 *)(a + 0x84)))) > *(s16 *)(a + 0x86) + *(s16 *)(p + 0x86)) {
                return;
            }
            a[0x29] = 1;
            if (p[0x2B] == 0) {
                p[0x2B] = 1;
                p[8] = 2;
                func_800517F8(p);
                func_8004ED94(0x2F, 0x41);
            }
        }
    }
}

extern u8 D_1F800150;
extern u8 **D_1F800148;
extern u8 **D_1F80013C;
extern u8 D_1F800144;
void func_80112140(void *a)
{
    u8 **l = D_1F800148;
    u8 *e;

    D_1F800182 = D_1F800150;
    while (D_1F800182 != 0) {
        e = *l;
        D_1F800182--;
        l++;
        if (e[0] & 1) {
            switch (e[2]) {
            case 0xE: case 0xF: case 0x19: case 0x22: case 0x25: case 0x27:
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

#define F16(p, o) M2C_FIELD(p, s16 *, o)
extern s8 D_800BF808_c1f7[];
extern u16 D_800BFE56;
typedef struct {
    s16 v[4];
} Box8;
extern Box8 D_801287E8[];
extern s8 D_800BF80D;
extern u8 **D_1F800154;
extern u8 D_1F80015C;
extern u8 D_1F800183;
/* func_80112654, inlined */
static inline void inl_80112654(u8 *a) {
    s8 *g;

    if (a[0x17B] == 0) {
        g = D_800BF808_c1f7;
        if (g[5] == 0 && ((u8 *)g)[0x31] == 0 && M2C_FIELD(a, s16 *, 0x2E) > 0x2710 && M2C_FIELD(a, s16 *, 0x36) < 0xAF0) {
            D_1F800236 = 1;
            D_1F800137 = 2;
            g[7] = 2;
            g[0x31] = 1;
            M2C_FIELD(g, s16 *, 0x32) = 0x102;
        }
    }
}
/* func_80112738, inlined */
static inline void inl_80112738(u8 *a) {
    u8 *g = D_800BF808_1760;
    s32 i;
    s32 r;
    Box8 *p;

    if (g[0xE] != 0 && g[0xF] == 7 && !(D_800BFE56 & 4)) {
        p = D_801287E8;
        for (i = 0; i < 2; i++, p++) {
            r = func_8010FAB0(a, p);
            if (r != 0 && !(a[0] & 4) && a[5] < 2) {
                a[0] = 7;
                a[0x2B] = (r - 1) << 6;
                a[5] = 7;
                a[6] = 0;
                a[7] = 0;
            }
        }
    }
}
/* func_80112A98, inlined */
static inline void inl_80112A98(void *a)
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
                func_801106F0(a, e);
            } else if (e[2] == 8) {
                func_80110370(a, e);
            }
        }
    }
}
/* func_80112B5C, inlined */
static inline void inl_80112B5C(u8 *a) {
    u8 **l;
    u8 *e;

    if (F16(a, 0x16E) != 0 && D_800BF80D == 0 && !(M2C_FIELD(a, u16 *, 0x17E) & 0x200)) {
        l = D_1F800154;
        D_1F800182 = *(u8 *)0x1F80015C;
        while (D_1F800182 != 0) {
            e = *l;
            D_1F800182--;
            l++;
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
                    func_80111D24(a, e);
                    break;
                }
            }
        }
    }
}
/* func_80112C58, inlined */
static inline void inl_80112C58(void) {
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
                func_80112140(a);
                break;
            }
        }
    }
}
void func_801122A4(void) {
    u8 *g = D_800E7E80;

    func_8002288C(g);
    switch (g[0]) {
    case 1:
    case 3:
    case 4:
    case 5:
    case 7:
        inl_80112B5C(g);
        inl_80112A98(g);
        func_80111974(g);
        inl_80112738(g);
        break;
    case 0:
    case 2:
    case 6:
        break;
    }
    inl_80112C58();
    inl_80112654(g);
}

void func_80112654(u8 *a) {
    s8 *g;

    if (a[0x17B] == 0) {
        g = D_800BF808_c1f7;
        if (g[5] == 0 && ((u8 *)g)[0x31] == 0 && M2C_FIELD(a, s16 *, 0x2E) > 0x2710 && M2C_FIELD(a, s16 *, 0x36) < 0xAF0) {
            D_1F800236 = 1;
            D_1F800137 = 2;
            g[7] = 2;
            g[0x31] = 1;
            M2C_FIELD(g, s16 *, 0x32) = 0x102;
        }
    }
}

typedef struct { u8 pad0[7]; u8 unk7; u8 pad8[0x29]; u8 unk31; s16 unk32; } AreaState808_7;
extern AreaState808_7 D_800BF808;
void func_801126DC(u8 *a) {
    if (M2C_FIELD(a, s16 *, 0x2E) > 0x2710 && M2C_FIELD(a, s16 *, 0x36) < 0xAF0) {
        D_1F800236 = 1;
        D_1F800137 = 2;
        D_800BF808.unk7 = 2;
        D_800BF808.unk31 = 1;
        D_800BF808.unk32 = 0x102;
    }
}

void func_80112738(u8 *a) {
    u8 *g = D_800BF808_1760;
    s32 i;
    s32 r;
    Box8 *p;

    if (g[0xE] != 0 && g[0xF] == 7 && !(D_800BFE56 & 4)) {
        p = D_801287E8;
        for (i = 0; i < 2; i++, p++) {
            r = func_8010FAB0(a, p);
            if (r != 0 && !(a[0] & 4) && a[5] < 2) {
                a[0] = 7;
                a[0x2B] = (r - 1) << 6;
                a[5] = 7;
                a[6] = 0;
                a[7] = 0;
            }
        }
    }
}

void func_8011281C(void *arg0, void *arg1) {
    if (!(M2C_FIELD(arg0, u16 *, 0x17E) & 0x200) && (func_80022F04() != 0)) {
        M2C_FIELD(arg1, s8 *, 0) = 2;
        M2C_FIELD(arg1, s8 *, 4) = 2;
    }
}

void func_80112864(u8 *a, u8 *b) {
    s16 d;
    s32 ang;

    if (func_8002300C(a, b, M2C_FIELD(b, s16 *, 0x80)) == 0) {
        return;
    }
    if (M2C_FIELD(a, s16 *, 0x17E) & 0x8200) {
        return;
    }
    ang = D_1F80009C & 0xFFF;
    if (D_1F80018E == 0 && D_1F800137 == 0 && !(b[0] & 2)) {
        d = (ang - M2C_FIELD(a, u16 *, 0x56)) << 4;
        if (abs(d) <= 0x2000 && (a[5] != 0x1F || b == M2C_FIELD(a, u8 **, 0x10))) {
            D_1F80018E = 0x1200;
            D_1F800184 = b;
            D_800BF840 = 0x4B;
        }
    }
}

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80112958);

void func_80112A98(void *a)
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
                func_801106F0(a, e);
            } else if (e[2] == 8) {
                func_80110370(a, e);
            }
        }
    }
}

#define F16(p, o) M2C_FIELD(p, s16 *, o)
void func_80112B5C(u8 *a) {
    u8 **l;
    u8 *e;

    if (F16(a, 0x16E) != 0 && D_800BF80D == 0 && !(M2C_FIELD(a, u16 *, 0x17E) & 0x200)) {
        l = D_1F800154;
        D_1F800182 = *(u8 *)0x1F80015C;
        while (D_1F800182 != 0) {
            e = *l;
            D_1F800182--;
            l++;
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
                    func_80111D24(a, e);
                    break;
                }
            }
        }
    }
}

void func_80112C58(void) {
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
                func_80112140(a);
                break;
            }
        }
    }
}

extern u8 D_800BF818;
extern u8 *D_1F800138;
s32 func_80112D08(u8 *a) {
    switch (a[5]) {
    case 0: {
        u8 *g = D_800BF808_1760;
        if (g[0x10] != 1) {
            return 0;
        }
        a[3] = g[0xF] + 1;
        func_800269BC(a);
        a[5]++;
        break;
    }
    case 1: {
        u8 *g = D_800BF808_1760;
        if (g[7] != 0) {
            return 0;
        }
        func_800269EC(a);
        *(s16 *)(D_1F800138 + 0x4E) = 2;
        a[5]++;
        g[0x10] = 2;
        return 1;
    }
    case 2:
        if (D_800BF80F != 0) {
            return 0;
        }
        func_800269FC(a);
        a[5]++;
        break;
    case 3:
        if (D_800BF818 != 3) {
            return 0;
        }
        func_800269BC(a);
        a[5]++;
        break;
    case 4: {
        u8 *g = D_800BF808_1760;
        if (g[7] != 0) {
            return 0;
        }
        func_80026A1C(a);
        func_800269EC(a);
        *(s16 *)(D_1F800138 + 0x4E) = 4;
        g[0x10] = 4;
        a[5]++;
        break;
    }
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

extern u8 *D_80128C48[];

void f_SpawnCoalMiningTownSceneActorsFromPlacementTable(u8 *a, s32 mode)
{
    u8 *e;
    u8 *g;
    u8 *h;
    u8 *p;

    *(s16 *)(a + 8) = 0;
    e = D_80128C48[mode];
    if (e[0] == 0xFF) {
        return;
    }
    g = D_800BF808_1760;
    h = (u8 *)&D_800BF870;
    do {
        if (mode != 0 && *(s16 *)(a + 8) >= 0xF) {
            goto next;
        }
        switch (e[0xA]) {
        case 0:
            break;
        case 1:
            *(s16 *)(g + 8) = *(s16 *)(e + 4);
            *(s16 *)(g + 0xA) = *(s16 *)(e + 6);
            *(s16 *)(g + 0xC) = *(s16 *)(e + 8);
            break;
        case 2:
            switch (e[3]) {
            case 0:
                if (h[0x189] != 1) {
                    goto next;
                }
                if (h[0x191] & 2) {
                    break;
                }
                goto next;
            case 1:
                if (h[0x189] == 0) {
                    goto next;
                }
                if (h[0x18A] < 2) {
                    break;
                }
                goto next;
            case 2:
                if (h[0x18A] != 3) {
                    goto next;
                }
                break;
            case 3:
                if ((s8)h[0x56] > 0) {
                    break;
                }
                goto next;
            case 4:
                if (h[0x189] >= 5) {
                    break;
                }
                goto next;
            }
            break;
        case 3:
            switch (e[3]) {
            case 1:
                if (h[0x18A] != 0x14) {
                    goto next;
                }
                break;
            case 2:
                if (h[0x56] != 0xFF) {
                    goto next;
                }
                break;
            }
            break;
        case 4:
            if (h[0x189] != 0) {
                break;
            }
            goto next;
        case 5:
            if (h[0x194] == 0) {
                goto next;
            }
            if (h[0x8D] == 0) {
                break;
            }
            goto next;
        case 6:
            if (h[0x56] == 0xFF) {
                goto next;
            }
            break;
        case 7:
            if (h[0x56] != 0xFF) {
                goto next;
            }
            break;
        case 8:
            if (h[0x8D] != 0xFF) {
                goto next;
            }
            break;
        case 9:
            if (h[0x56] != 0xFF) {
                goto next;
            }
            if (h[0xAC] == 0xFF) {
                goto next;
            }
            break;
        case 10:
            if (h[0x98] == 0xFF) {
                goto next;
            }
            break;
        case 11:
            if (h[0x9F] != 0xFF) {
                goto next;
            }
            break;
        case 12:
            if (h[0x54] == 0xFF) {
                goto next;
            }
            break;
        }
        p = func_80072DDC(a, e[0], e[1], e[2]);
        if (p != NULL) {
            *(s32 *)(p + 0x2C) = *(s16 *)(e + 4) << 16;
            *(s32 *)(p + 0x30) = *(s16 *)(e + 6) << 16;
            *(s32 *)(p + 0x34) = *(s16 *)(e + 8) << 16;
            p[3] = e[3];
            *(s16 *)(p + 0x54) = 0;
            *(s16 *)(p + 0x56) = 0;
            *(s16 *)(p + 0x58) = 0;
            *(s32 *)(p + 0x1C) = *(s32 *)(e + 0xC);
            if (mode != 0) {
                *(u8 **)(a + (*(s16 *)(a + 8) << 2) + 0xC) = p;
                (*(s16 *)(a + 8))++;
            }
        }
    next:
        e += 0x10;
    } while (e[0] != 0xFF);
}

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8011321C);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80113394);

extern u8 *D_800BF544_37fb;
extern u8 *D_800ED8C8_35cc;
#define OT4 (*(u32 *)(ot + 0x10))
extern s16 D_1F800160;
extern s16 D_1F800164;
extern void func_80083DE0(void *, s32, s32, s32, s32);
void func_80113628(void) {
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
    x = (D_1F800160 - 0x840) / 182;
    y = 0xD0 - (D_1F800164 - 0xA7F) / 182;
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
    *(s16 *)(p + 0xA) = y - 4;
    *(u16 *)(p + 0xE) = 0x3D3F;
    p[0xC] = 0x40;
    p[0xD] = 0x68;
    p[6] = b;
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
    *(s16 *)(p + 0xA) = 0x90;
    *(u16 *)(p + 0xE) = 0x3D7F;
    p[0xD] = 0xB0;
    p[0xC] = 0;
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
    func_80083DE0(p3, 0, 0, 0xF, 0);
    ot3 = D_800ED8C8_35cc;
    *(u32 *)(q2 + 0x14) = (*(u32 *)(ot3 + 0x10)) | 0x02000000;
    do {
        (*(u32 *)(ot3 + 0x10)) = (u32)p3;
    } while (0);
    D_800BF544_37fb += 0xC;
}

void func_80113824(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 4);
    switch (temp_v1) {                              /* irregular */
    case 0:
        M2C_FIELD(arg0, u8 *, 4) = 1U;
        f_SpawnCoalMiningTownSceneActorsFromPlacementTable(arg0, 0U);
        func_8004D8D8(5, 0);
        func_8011321C(0);
        return;
    case 1:
        if (func_80112D08(arg0) != 0) {
            f_SpawnCoalMiningTownSceneActorsFromPlacementTable(arg0, M2C_FIELD(arg0, u8 *, 3));
        }
        func_80026A68(arg0);
        func_8011321C(1);
        return;
    case 3:
        func_8007ADD0(arg0);
        /* fallthrough */
    case 2:
        return;
    }
}

void f_UpdateCoalMiningTownInteriorDoorPartTransition(u8 *a, u8 *p) {
    s32 done;

    switch (a[5]) {
    case 0:
        a[5]++;
        *(u16 *)(p + 0xE) = *(u16 *)(p + 0xA);
        func_80072FE0(a, p);
        break;
    case 1:
        if (D_800BF818 == 2) {
            a[5]++;
        }
        break;
    case 2:
        if (func_80073194(a, p) != 0) {
            a[5]++;
        }
        break;
    case 3: {
        u8 *g = D_800BF808_1760;
        if (g[0x10] == 3) {
            a[5]++;
        } else if (g[0x10] == 7) {
            g[0x10] = 0;
            a[5] = 6;
            func_80074590(0x17, 0, 0);
        } else if (g[0x10] == 9) {
            g[0x10] = 0;
            a[5] = 9;
            func_80074590(0x17, 0, 0);
        }
        break;
    }
    case 4:
        if (func_8007302C(a, p) != 0) {
            a[5]++;
        }
        break;
    case 6:
        if (func_8007302C(a, p) != 0) {
            a[5]++;
        }
        break;
    case 7:
        if (D_800BF818 == 8) {
            a[5]++;
        }
        break;
    case 8:
        if (func_800730C8(a, p) != 0) {
            a[5] = 3;
            func_80074590(0x18, 0, 0);
            D_800BF818 = 0;
        }
        break;
    case 9:
        done = 0;
        switch (a[0x46]) {
        case 0:
            W16(0x50) += 0x40;
            if (I16(0x50) > I16(0x5A) + 0x400) {
                W16(0x50) = 0x400;
                done = 1;
            }
            break;
        case 1:
            W16(0x50) -= 0x40;
            if (I16(0x50) < I16(0x5A) - 0x400) {
                I16(0x50) = -0x400;
                done = 1;
            }
            break;
        }
        *(u16 *)(p + 0xA) = W16(0x5A) - W16(0x50);
        if (done) {
            W16(0x40) = 0xC;
            a[5]++;
        }
        break;
    case 10:
        if (D_800BF818 == 10) {
            a[5]++;
        }
        break;
    case 11:
        done = 0;
        switch (a[0x46]) {
        case 0:
            W16(0x50) -= 0x40;
            if (I16(0x50) < 0) {
                W16(0x50) = 0;
                done = 1;
            }
            break;
        case 1:
            W16(0x50) += 0x40;
            if (I16(0x50) > 0) {
                W16(0x50) = 0;
                done = 1;
            }
            break;
        }
        *(u16 *)(p + 0xA) = W16(0x5A) - W16(0x50);
        if (done) {
            a[5] = 3;
            func_80074590(0x18, 0, 0);
            D_800BF818 = 0;
        }
        break;
    }
}

#define FP(p, o) M2C_FIELD(p, u8 **, o)
void func_80113BC4(u8 *a) {
    u8 *g;

    f_UpdateCoalMiningTownInteriorDoorPartTransition(a, FP(a, 0xC4));
    M2C_FIELD(FP(a, 0xC8), s16 *, 0xA) = M2C_FIELD(FP(a, 0xC4), u16 *, 0xA);
    switch (a[6]) {
    case 0:
        g = D_800BF808_1760;
        if (g[0xE] != 0 && g[7] == 0) {
            a[6] = 1;
            M2C_FIELD(FP(a, 0xC4), s32 *, 0x40) = 0;
        }
        break;
    case 1:
        if (D_800BF80F != 0) {
            func_80051B04(FP(a, 0xC4), 0xC, M2C_FIELD(FP(a, 0xC4), u16 *, 0x38));
            a[6] += 2;
        } else if (a[5] >= 6) {
            a[6] = 2;
            func_80051B04(FP(a, 0xC4), 0xC, M2C_FIELD(FP(a, 0xC4), u16 *, 0x38));
        }
        break;
    case 2:
        if (a[5] < 6) {
            M2C_FIELD(FP(a, 0xC4), s32 *, 0x40) = 0;
            a[6]--;
        }
        break;
    }
}

void func_80113D08(u8 *a) {
    u8 *g;

    f_UpdateCoalMiningTownInteriorDoorPartTransition(a, FP(a, 0xC4));
    M2C_FIELD(FP(a, 0xC8), s16 *, 0xA) = M2C_FIELD(FP(a, 0xC4), u16 *, 0xA);
    switch (a[6]) {
    case 0:
        g = D_800BF808_1760;
        if (g[0xE] != 0 && g[7] == 0) {
            a[6] = 1;
            M2C_FIELD(FP(a, 0xC4), s32 *, 0x40) = 0;
        }
        break;
    case 1:
        if (D_800BF80F != 0) {
            func_80051B04(FP(a, 0xC4), 0xC, M2C_FIELD(FP(a, 0xC4), u16 *, 0x38));
            a[6] += 2;
        } else if (a[5] >= 6) {
            a[6] = 2;
            func_80051B04(FP(a, 0xC4), 0xC, M2C_FIELD(FP(a, 0xC4), u16 *, 0x38));
        }
        break;
    case 2:
        if (a[5] < 6) {
            M2C_FIELD(FP(a, 0xC4), s32 *, 0x40) = 0;
            a[6]--;
        }
        break;
    }
}

extern u8 D_800BF817;
extern u16 D_800E7EEA;
s32 func_801176EC(s32 a, s32 b);
void func_80113E4C(u8 *a) {
    u8 *g;

    switch (func_801176EC(D_800E7EEA & 0xF0, D_800BF817)) {
    case 3:
        f_UpdateCoalMiningTownInteriorDoorPartTransition(a, FP(a, 0xC4));
        M2C_FIELD(FP(a, 0xC8), s16 *, 0xA) = M2C_FIELD(FP(a, 0xC4), u16 *, 0xA);
        break;
    case 4:
        f_UpdateCoalMiningTownInteriorDoorPartTransition(a, FP(a, 0xCC));
        M2C_FIELD(FP(a, 0xD0), s16 *, 0xA) = M2C_FIELD(FP(a, 0xCC), u16 *, 0xA);
        break;
    case 5:
        f_UpdateCoalMiningTownInteriorDoorPartTransition(a, FP(a, 0xD4));
        M2C_FIELD(FP(a, 0xD8), s16 *, 0xA) = M2C_FIELD(FP(a, 0xD4), u16 *, 0xA);
        break;
    case 6:
        f_UpdateCoalMiningTownInteriorDoorPartTransition(a, FP(a, 0xDC));
        M2C_FIELD(FP(a, 0xE0), s16 *, 0xA) = M2C_FIELD(FP(a, 0xDC), u16 *, 0xA);
        break;
    }
    switch (a[6]) {
    case 0:
        g = D_800BF808_1760;
        if (g[0xE] != 0 && g[7] == 0) {
            a[6] = 1;
            M2C_FIELD(FP(a, 0xC4), s32 *, 0x40) = 0;
            M2C_FIELD(FP(a, 0xCC), s32 *, 0x40) = 0;
            M2C_FIELD(FP(a, 0xD4), s32 *, 0x40) = 0;
            M2C_FIELD(FP(a, 0xDC), s32 *, 0x40) = 0;
        }
        break;
    case 1:
        if (D_800BF80F != 0) {
            func_80051B04(FP(a, 0xC4), 0xC, M2C_FIELD(FP(a, 0xC4), u16 *, 0x38));
            func_80051B04(FP(a, 0xCC), 0xC, M2C_FIELD(FP(a, 0xCC), u16 *, 0x38));
            func_80051B04(FP(a, 0xD4), 0xC, M2C_FIELD(FP(a, 0xD4), u16 *, 0x38));
            func_80051B04(FP(a, 0xDC), 0xC, M2C_FIELD(FP(a, 0xDC), u16 *, 0x38));
            a[6]++;
        }
        break;
    case 2:
        break;
    }
}

void func_80114024(u8 *a) {
    u8 *g;
    u16 v;
    u8 *p0;
    u8 *p1;
    u8 *p2;
    u8 *p3;

    f_UpdateCoalMiningTownInteriorDoorPartTransition(a, FP(a, 0xC4));
    p0 = FP(a, 0xC4);
    p1 = FP(a, 0xC8);
    p3 = FP(a, 0xD0);
    p2 = FP(a, 0xCC);
    v = M2C_FIELD(p0, u16 *, 0xA);
    M2C_FIELD(p1, s16 *, 0xA) = v;
    M2C_FIELD(p2, s16 *, 0xA) = v;
    M2C_FIELD(p3, s16 *, 0xA) = v;
    switch (a[6]) {
    case 0:
        g = D_800BF808_1760;
        if (g[0xE] != 0 && g[7] == 0) {
            a[6] = 1;
            M2C_FIELD(FP(a, 0xC4), s32 *, 0x40) = 0;
            M2C_FIELD(FP(a, 0xCC), s32 *, 0x40) = 0;
        }
        break;
    case 1:
        if (D_800BF80F != 0) {
            func_80051B04(FP(a, 0xC4), 0xC, M2C_FIELD(FP(a, 0xC4), u16 *, 0x38));
            func_80051B04(FP(a, 0xCC), 0xC, M2C_FIELD(FP(a, 0xCC), u16 *, 0x38));
            a[6] += 2;
        } else if (a[5] >= 6) {
            a[6] = 2;
            func_80051B04(FP(a, 0xC4), 0xC, M2C_FIELD(FP(a, 0xC4), u16 *, 0x38));
            func_80051B04(FP(a, 0xCC), 0xC, M2C_FIELD(FP(a, 0xCC), u16 *, 0x38));
        }
        break;
    case 2:
        if (a[5] < 6) {
            M2C_FIELD(FP(a, 0xC4), s32 *, 0x40) = 0;
            M2C_FIELD(FP(a, 0xCC), s32 *, 0x40) = 0;
            a[6]--;
        }
        break;
    }
}

typedef struct { u8 n; u8 pad; } Coal9A34;
void *func_8007AAE8();
extern s16 D_800ED098;
extern u8 *D_800ECF88;
extern u8 *D_800ECFC8;
extern void *D_800ECFCC_7069;
extern u8 D_80139F38[];
extern Coal9A34 D_80129A34[];
extern s16 D_80129A58[];
extern s16 *D_801299F0[];
/* door part (cases 0 / 5) */
static inline void coal_door_part_inl(u8 *a)
{
    u8 *g;

    f_UpdateCoalMiningTownInteriorDoorPartTransition(a, FP(a, 0xC4));
    M2C_FIELD(FP(a, 0xC8), s16 *, 0xA) = M2C_FIELD(FP(a, 0xC4), u16 *, 0xA);
    switch (a[6]) {
    case 0:
        g = D_800BF808_1760;
        if (g[0xE] != 0 && g[7] == 0) {
            a[6] = 1;
            M2C_FIELD(FP(a, 0xC4), s32 *, 0x40) = 0;
        }
        break;
    case 1:
        if (D_800BF80F != 0) {
            func_80051B04(FP(a, 0xC4), 0xC, M2C_FIELD(FP(a, 0xC4), u16 *, 0x38));
            a[6]++;
        }
        break;
    case 2:
        break;
    }
}

void f_UpdateCoalMiningTownInteriorSceneryAssemblyActor(u8 *a)
{
    s32 i;
    u8 *base;
    s32 *offs;
    s16 *src;
    u8 *q;
    s32 k;

    switch (a[4]) {
    case 0:
        a[8] = D_80129A34[a[3]].n;
        if (D_800ED098 < a[8]) {
            a[4] = 3;
            break;
        }
        a[9] = a[8];
        a[4]++;
        if (a[3] == 7) {
            base = D_800ECFC8;
        } else {
            base = D_800ECF88;
        }
        a[0xD] = 0;
        a[0xB] = 0;
        *(s16 *)(a + 0x54) = 0;
        *(s16 *)(a + 0x56) = (D_80129A58[a[3]] << 12) / 360;
        i = 0;
        *(s16 *)(a + 0x58) = 0;
        src = D_801299F0[a[3]];
        offs = (s32 *)(base + 4);
        for (; i < a[8]; i++) {
            q = func_8007AAE8();
            FP(a, 0xC0 + i * 4) = q;
            *(s16 *)(q + 6) = *src++;
            *(s16 *)(FP(a, 0xC0 + i * 4) + 0) = *src++;
            *(s16 *)(FP(a, 0xC0 + i * 4) + 2) = *src++;
            *(s16 *)(FP(a, 0xC0 + i * 4) + 4) = *src++;
            *(s16 *)(FP(a, 0xC0 + i * 4) + 8) = *src++;
            *(s16 *)(FP(a, 0xC0 + i * 4) + 0xA) = *src++;
            *(s16 *)(FP(a, 0xC0 + i * 4) + 0xC) = *src++;
            k = *src;
            *(u8 **)(FP(a, 0xC0 + i * 4) + 0x40) = base + offs[k];
            *(s16 *)(FP(a, 0xC0 + i * 4) + 0x38) = k;
            src++;
        }
        switch (a[3]) {
        case 3:
            a[0x46] = 1;
            a[0xBF] = 0;
            break;
        case 0:
        case 1:
        case 2:
        case 4:
        case 5:
        case 6:
            a[0x46] = 1;
            a[0xBF] = 1;
            break;
        case 7:
            if (D_800BFE56 & 4) {
                a[8] = 1;
                break;
            }
            *(s16 *)(a + 0xB8) = 0x1000;
            *(s16 *)(a + 0xBA) = 0x1000;
            *(s16 *)(a + 0xBC) = 0x1000;
            *(s16 *)(a + 0x88) = 0;
            *(s16 *)(a + 0x8A) = 0;
            *(s16 *)(a + 0x8C) = 0;
            *(void **)(a + 0x3C) = D_800ECFCC_7069;
            func_80077C40(a, D_80139F38, 4);
            break;
        }
        break;
    case 1:
        switch (a[3]) {
        case 0:
            coal_door_part_inl(a);
            break;
        case 1:
            func_80113BC4(a);
            break;
        case 2:
            func_80113D08(a);
            break;
        case 3:
            break;
        case 4:
            func_80113E4C(a);
            break;
        case 5:
            coal_door_part_inl(a);
            break;
        case 6:
            func_80114024(a);
            break;
        case 7:
            break;
        }
        if (a[3] == 7 && !(D_800BFE56 & 4)) {
            a[1] = 1;
            func_80076D68(a);
            func_800518FC(a);
        } else {
            a[1] = 1;
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

s32 func_80114650(u8 *a, u8 *b) {
    s32 r = 0;

    switch (a[0x46]) {
    case 0:
        M2C_FIELD(a, s16 *, 0x50) -= 0x40;
        if (M2C_FIELD(a, s16 *, 0x50) < 0) {
            M2C_FIELD(a, s16 *, 0x50) = 0;
            r = 1;
        }
        break;
    case 1:
        M2C_FIELD(a, s16 *, 0x50) += 0x40;
        if (M2C_FIELD(a, s16 *, 0x50) > 0) {
            M2C_FIELD(a, s16 *, 0x50) = 0;
            r = 1;
        }
        break;
    }
    M2C_FIELD(b, s16 *, 0xA) = M2C_FIELD(a, s16 *, 0x5A) - M2C_FIELD(a, s16 *, 0x50);
    return r;
}

extern u8 D_800BFA03;
void func_801146D8(u8 *a) {
    u8 *s = *(u8 **)(a + 0x10);
    u8 *q;
    u8 v;

    switch (a[5]) {
    case 0:
        *(u16 *)(a + 0x2E) = *(u16 *)(*(u8 **)(s + 0xD0) + 0x2C) + ((func_80083F50(*(s16 *)(a + 0x56)) * 16) >> 12);
        *(u16 *)(a + 0x32) = *(u16 *)(*(u8 **)(s + 0xD0) + 0x30) + 0x80;
        *(u16 *)(a + 0x36) = *(u16 *)(*(u8 **)(s + 0xD0) + 0x34) - ((func_80083E80(*(s16 *)(a + 0x56)) * 32) >> 12);
        break;
    case 1:
        *(s16 *)(a + 0x4A) = -0x3000;
        *(s16 *)(a + 0x50) = 0x380;
        *(u8 **)(a + 0x14) = *(u8 **)(s + 0x10);
        q = *(u8 **)(a + 0x14);
        *(u16 *)(a + 0x2E) = *(u16 *)(q + 0x2C);
        *(u16 *)(a + 0x32) = *(u16 *)(q + 0x2E);
        *(u16 *)(a + 0x36) = *(u16 *)(q + 0x30);
        a[5]++;
        break;
    case 2:
        q = *(u8 **)(a + 0x14);
        *(u16 *)(a + 0x4A) += *(u16 *)(a + 0x50);
        if (*(s16 *)(a + 0x4A) >= 0x2000) {
            *(s16 *)(a + 0x4A) = 0x2000;
        }
        *(s32 *)(a + 0x30) += *(s16 *)(a + 0x4A) << 8;
        if (*(s16 *)(a + 0x4A) >= 0 && *(s16 *)(a + 0x32) >= *(s16 *)(q + 0x2E) - 0x40) {
            a[0x18] = a[0x19] = a[0x1A] = 0x7F;
            *(u16 *)(a + 0x32) = *(u16 *)(q + 0x2E) - 0x20;
            a[5]++;
        }
        break;
    case 3:
        if (D_800BFA03 == 0xF) {
            a[0xD] = 3;
            a[5]++;
        }
        {
            s16 d = (a[0x18] >> 1) - 0x20;
            *(u16 *)(a + 0x32) = *(u16 *)(*(u8 **)(a + 0x14) + 0x2E) - d;
        }
        break;
    case 4:
        a[0x18] = a[0x19] = a[0x1A] = v = a[0x18] - 4;
        if ((s8)v <= 0) {
            D_800BFA03 = 0x10;
            a[0x18] = a[0x19] = a[0x1A] = 0;
            a[4] = 3;
        }
        {
            s16 d = (a[0x18] >> 1) - 0x20;
            *(u16 *)(a + 0x32) = *(u16 *)(*(u8 **)(a + 0x14) + 0x2E) - d;
        }
        break;
    }
    if (func_8007778C(a) != 0) {
        func_800517F8(a);
    }
}

void f_UpdateCoalMiningTownScenePropActor();
extern void *D_800ECF80;
extern u8 D_80139100[];
extern u8 D_800BF816;
extern u8 D_1F8000D0[];
extern u8 D_1F800000[];
extern u8 D_80129A7C[];
/* func_80114CC8, inlined */
static inline void inl_80114CC8(u8 *a) {
    u8 *p;

    if (func_80051B70(a, 0xC, 0x26) == 0) {
        M2C_FIELD(a, s16 *, 0x54) = 0;
        M2C_FIELD(a, s16 *, 0x56) = 0;
        M2C_FIELD(a, s16 *, 0x58) = 0;
        p = func_80072DDC(a, 0x81, 3, 0x10);
        M2C_FIELD(p, void **, 0x1C) = f_UpdateCoalMiningTownScenePropActor;
        p[3] = 1;
        M2C_FIELD(p, s16 *, 0x2E) = M2C_FIELD(a, s16 *, 0x2E);
        M2C_FIELD(p, s16 *, 0x32) = M2C_FIELD(a, s16 *, 0x32) + 0x136;
        M2C_FIELD(p, s16 *, 0x36) = M2C_FIELD(a, s16 *, 0x36);
    }
}
/* func_80114D80, inlined */
static inline void inl_80114D80(u8 *a) {
    M2C_FIELD(a, void **, 0x3C) = D_800ECF80;
    func_80077B38(a, D_80139100, 0x16);
    a[0xD] = 1;
    M2C_FIELD(a, s16 *, 0x5C) = 0;
    a[0xB] = 0x13;
    M2C_FIELD(a, s16 *, 0x54) = 0;
    M2C_FIELD(a, s16 *, 0x56) = 0;
    M2C_FIELD(a, s16 *, 0x58) = 0;
    a[0x47] = 0;
    a[8] = 0;
}
/* func_80114E9C, inlined */
static inline void inl_80114E9C(u8 *a) {
    M2C_FIELD(a, void **, 0x3C) = D_800ECF80;
    func_80077B38(a, D_80139100, 0x14);
    a[0xD] = 1;
    M2C_FIELD(a, s16 *, 0x5C) = 0;
    a[0xB] = 0x10;
    M2C_FIELD(a, s16 *, 0x54) = 0;
    M2C_FIELD(a, s16 *, 0x56) = 0;
    M2C_FIELD(a, s16 *, 0x58) = 0;
    a[0x47] = 0;
    a[8] = 0;
}
/* func_8011501C, inlined */
static inline void inl_8011501C(void *arg0) {
    M2C_UNK var_a2;

    var_a2 = 0x38;
    if ((u8) D_800BFA03 >= 4U) {
        var_a2 = 0x39;
    }
    if (func_80051B70(arg0, 0xC, var_a2) == 0) {
        M2C_FIELD(arg0, u8 *, 0xD) = (u8) (M2C_FIELD(arg0, u8 *, 0xD) | 4);
        M2C_FIELD(M2C_FIELD(arg0, void **, 0xC0), s8 *, 0x3F) = 0x50;
        M2C_FIELD(arg0, s16 *, 0x54) = 0;
        M2C_FIELD(arg0, s16 *, 0x56) = 0;
        M2C_FIELD(arg0, s16 *, 0x58) = 0;
        func_800517F8(arg0);
    }
}
/* func_80115148, inlined */
static inline void inl_80115148(u8 *a) {
    if (func_80051B70(a, 0xC, 0x3E) == 0) {
        a[0xD] = 0;
        M2C_FIELD(a, s16 *, 0x54) = 0;
        M2C_FIELD(a, s16 *, 0x56) = 0x898;
        M2C_FIELD(a, s16 *, 0x58) = 0;
    }
}
/* func_80114DE4, inlined */
static inline void inl_80114DE4(u8 *a) {
    u8 *s;
    u8 *m;

    if (D_800BF816 == 0) {
        a[4] = 3;
        return;
    }
    a[1] = M2C_FIELD(a, u8 **, 0x10)[1];
    func_80077B5C(a);
    s = D_1F8000D0;
    m = D_1F800000;
    M2C_FIELD(a, s16 *, 0x56) = -M2C_FIELD(s, s16 *, 0x22);
    func_80051794(m);
    func_800847F0(a + 0x54, m);
    func_80084110(s + 0x28, m, a + 0x98);
    M2C_FIELD(a, s32 *, 0xAC) = M2C_FIELD(a, s16 *, 0x2E);
    M2C_FIELD(a, s32 *, 0xB0) = M2C_FIELD(a, s16 *, 0x32);
    M2C_FIELD(a, s32 *, 0xB4) = M2C_FIELD(a, s16 *, 0x36);
}
/* func_80114F98, inlined */
static inline void inl_80114F98(u8 *a) {
    switch (a[6]) {
    case 0:
        a[6]++;
        func_80040CDC(a, NULL, D_80129A7C);
        a[0x70] = 1;
        break;
    case 1:
        func_80041098(a);
        if (a[0x70] == 0xFF) {
            a[4] = 3;
            func_80042310();
        }
        break;
    }
}
/* func_80115090, inlined */
static inline void inl_80115090(void *arg0) {
    if (D_800BF870.pad1[0x192] == 3) {
        func_80051B04(M2C_FIELD(arg0, s32 *, 0xC0), 0xC, 0x39);
        D_800BF870.pad1[0x192] = 4;
    }
    func_8007778C(arg0);
}
void f_UpdateCoalMiningTownScenePropActor(u8 *a)
{
    switch (a[4]) {
    case 0:
        a[4] = 1;
        switch (a[3]) {
        case 0:
            inl_80114CC8(a);
            break;
        case 1:
            inl_80114D80(a);
            break;
        case 2:
            inl_80114E9C(a);
            break;
        case 9:
            inl_8011501C(a);
            break;
        case 12:
            inl_80115148(a);
            break;
        }
        break;
    case 1:
        switch (a[3]) {
        case 0:
            func_8007778C(a);
            func_800517F8(a);
            break;
        case 1:
            inl_80114DE4(a);
            break;
        case 2:
            a[1] = 1;
            func_80077B5C(a);
            break;
        case 3:
            inl_80114F98(a);
            break;
        case 9:
            inl_80115090(a);
            break;
        case 12:
            func_801146D8(a);
            break;
        }
        break;
    case 2:
        break;
    default:
        func_8007A624(a);
        break;
    }
}

void f_UpdateCoalMiningTownScenePropActor();
void func_80114CC8(u8 *a) {
    u8 *p;

    if (func_80051B70(a, 0xC, 0x26) == 0) {
        M2C_FIELD(a, s16 *, 0x54) = 0;
        M2C_FIELD(a, s16 *, 0x56) = 0;
        M2C_FIELD(a, s16 *, 0x58) = 0;
        p = func_80072DDC(a, 0x81, 3, 0x10);
        M2C_FIELD(p, void **, 0x1C) = f_UpdateCoalMiningTownScenePropActor;
        p[3] = 1;
        M2C_FIELD(p, s16 *, 0x2E) = M2C_FIELD(a, s16 *, 0x2E);
        M2C_FIELD(p, s16 *, 0x32) = M2C_FIELD(a, s16 *, 0x32) + 0x136;
        M2C_FIELD(p, s16 *, 0x36) = M2C_FIELD(a, s16 *, 0x36);
    }
}

void func_80114D54(s32 arg0) {
    func_8007778C();
    func_800517F8(arg0);
}

void func_80114D80(u8 *a) {
    M2C_FIELD(a, void **, 0x3C) = D_800ECF80;
    func_80077B38(a, D_80139100, 0x16);
    a[0xD] = 1;
    M2C_FIELD(a, s16 *, 0x5C) = 0;
    a[0xB] = 0x13;
    M2C_FIELD(a, s16 *, 0x54) = 0;
    M2C_FIELD(a, s16 *, 0x56) = 0;
    M2C_FIELD(a, s16 *, 0x58) = 0;
    a[0x47] = 0;
    a[8] = 0;
}

void func_80114DE4(u8 *a) {
    u8 *s;
    u8 *m;

    if (D_800BF816 == 0) {
        a[4] = 3;
        return;
    }
    a[1] = M2C_FIELD(a, u8 **, 0x10)[1];
    func_80077B5C(a);
    s = D_1F8000D0;
    m = D_1F800000;
    M2C_FIELD(a, s16 *, 0x56) = -M2C_FIELD(s, s16 *, 0x22);
    func_80051794(m);
    func_800847F0(a + 0x54, m);
    func_80084110(s + 0x28, m, a + 0x98);
    M2C_FIELD(a, s32 *, 0xAC) = M2C_FIELD(a, s16 *, 0x2E);
    M2C_FIELD(a, s32 *, 0xB0) = M2C_FIELD(a, s16 *, 0x32);
    M2C_FIELD(a, s32 *, 0xB4) = M2C_FIELD(a, s16 *, 0x36);
}

void func_80114E9C(u8 *a) {
    M2C_FIELD(a, void **, 0x3C) = D_800ECF80;
    func_80077B38(a, D_80139100, 0x14);
    a[0xD] = 1;
    M2C_FIELD(a, s16 *, 0x5C) = 0;
    a[0xB] = 0x10;
    M2C_FIELD(a, s16 *, 0x54) = 0;
    M2C_FIELD(a, s16 *, 0x56) = 0;
    M2C_FIELD(a, s16 *, 0x58) = 0;
    a[0x47] = 0;
    a[8] = 0;
}

void func_80114F00(void *arg0) {
    M2C_FIELD(arg0, s8 *, 1) = 1;
    func_80077B5C();
}

void f_UpdateCoalMiningTownScenePropActor();
void func_80114F24(u8 *a) {
    u8 *p = func_80072DDC(a, 1, 3, 0x10);

    M2C_FIELD(p, void **, 0x1C) = f_UpdateCoalMiningTownScenePropActor;
    p[3] = 3;
    M2C_FIELD(p, s16 *, 0x2E) = M2C_FIELD(a, s16 *, 0x2E);
    M2C_FIELD(p, s16 *, 0x32) = M2C_FIELD(a, s16 *, 0x32);
    M2C_FIELD(p, s16 *, 0x36) = M2C_FIELD(a, s16 *, 0x36);
    func_80042354(1, 1);
}

void func_80114F90(void) {
}

void func_80114F98(u8 *a) {
    switch (a[6]) {
    case 0:
        a[6]++;
        func_80040CDC(a, NULL, D_80129A7C);
        a[0x70] = 1;
        break;
    case 1:
        func_80041098(a);
        if (a[0x70] == 0xFF) {
            a[4] = 3;
            func_80042310();
        }
        break;
    }
}

void func_8011501C(void *arg0) {
    M2C_UNK var_a2;

    var_a2 = 0x38;
    if ((u8) D_800BFA03 >= 4U) {
        var_a2 = 0x39;
    }
    if (func_80051B70(arg0, 0xC, var_a2) == 0) {
        M2C_FIELD(arg0, u8 *, 0xD) = (u8) (M2C_FIELD(arg0, u8 *, 0xD) | 4);
        M2C_FIELD(M2C_FIELD(arg0, void **, 0xC0), s8 *, 0x3F) = 0x50;
        M2C_FIELD(arg0, s16 *, 0x54) = 0;
        M2C_FIELD(arg0, s16 *, 0x56) = 0;
        M2C_FIELD(arg0, s16 *, 0x58) = 0;
        func_800517F8(arg0);
    }
}

void func_80115090(void *arg0) {
    if (D_800BF870.pad1[0x192] == 3) {
        func_80051B04(M2C_FIELD(arg0, s32 *, 0xC0), 0xC, 0x39);
        D_800BF870.pad1[0x192] = 4;
    }
    func_8007778C(arg0);
}

void f_UpdateCoalMiningTownScenePropActor();
u8 *func_801150EC(s32 a) {
    u8 *p = func_8007A980(1, 3, 1);

    if (p == NULL) {
        return NULL;
    }
    p[0x2] = 16;
    p[0x3] = 12;
    M2C_FIELD(p, void **, 0x1C) = f_UpdateCoalMiningTownScenePropActor;
    M2C_FIELD(p, s32 *, 0x10) = a;
    return p;
}

extern s32 D_800BF844;
#define PLAYER (*(u8 **)&D_800BF844)
void func_80115148(u8 *a) {
    if (func_80051B70(a, 0xC, 0x3E) == 0) {
        a[0xD] = 0;
        M2C_FIELD(a, s16 *, 0x54) = 0;
        M2C_FIELD(a, s16 *, 0x56) = 0x898;
        M2C_FIELD(a, s16 *, 0x58) = 0;
    }
}

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8011518C);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_801152A8);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_801154DC);

s32 func_80115620(s32 arg0, s32 arg1, s32 arg2) {
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

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80115794);

extern s16 D_1F8000EE;
void func_80115994(u8 *a, s16 b)
{
    s16 v;
    s16 y;
    s16 d;
    u8 *c;

    if (a[0x64] == 1) {
        s32 ang;
        u8 *g = D_800BF808_1760;
        if (g[0xE] != 0 && g[0xF] != 7) {
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

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80115AAC);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80115D84);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80115F58);

void func_801167A8(void)
{
    CameraState *c = &g_CameraState;

    c->unk6C = 0x500;
    c->unk6E = 0xA0;
}

void func_801167C4(u8 *a, s32 ang) {
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

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_801168A0);

void func_80116918(u8 *a) {
    u8 *t = D_800E7E80;
    s16 v[6];

    switch (a[4]) {
    case 0:
        M2C_FIELD(a, s16 *, 0x70) = 0x1400 - D_1F8000F2_1841;
        a[4]++;
        break;
    case 1:
        v[1] = M2C_FIELD(t, s16 *, 0x2E);
        v[3] = M2C_FIELD(t, s16 *, 0x32) - 0x20;
        v[5] = M2C_FIELD(t, s16 *, 0x36);
        func_8006E3F4(a, v);
        func_80115794(a, t, M2C_FIELD(a, s16 *, 0x70));
        func_80115994(a, (s16)(M2C_FIELD(t, s16 *, 0x32) - 0x20));
        break;
    }
}

extern s16 D_80129C04[];
/* func_80117658, inlined */
static inline s32 inl_80117658(s32 k) {
    s32 r = 0;

    if (k == 5) {
        r = 0;
    } else if (k == 6) {
        r = 1;
    } else if (k == 7) {
        r = 2;
    } else if (k == 8) {
        r = 3;
    } else if (k == 10) {
        r = 4;
    } else if (k == 12) {
        r = 5;
    } else if (k == 13) {
        r = 6;
    } else if (k == 9) {
        r = 7;
    } else if (k == 14) {
        r = 8;
    }
    return r;
}
/* func_801176EC, inlined */
static inline s32 inl_801176EC(s32 a, s32 b) {
    s32 r;

    switch (b) {
    case 1:
        r = 1;
        break;
    case 2:
        r = 2;
        break;
    case 3:
        r = 11;
        break;
    case 4:
        if (a == 0) {
            r = 6;
        } else if (a == 0x20) {
            r = 5;
        } else if (a == 0x40) {
            r = 4;
        } else {
            r = 3;
        }
        break;
    case 5:
        if (a == 0) {
            r = 9;
        } else {
            r = 10;
        }
        break;
    case 6:
        if (a == 0) {
            r = 7;
        } else {
            r = 8;
        }
        break;
    case 7:
        r = 12;
        break;
    case 0:
    default:
        r = 0;
        break;
    }
    return r;
}
void func_801169D8(a)
u8 *a;
{
    u8 *e = D_800E7E80;
    s16 k;

    switch (a[6]) {
    case 0:
        if ((M2C_FIELD(e, s16 *, 0x6A) & 0xF000) == 0x2000) {
            s32 t;
            u8 c;
            t = inl_80117658(M2C_FIELD(e, u16 *, 0x6A) & 0x1F);
            t = inl_801176EC(M2C_FIELD(e, u16 *, 0x6A) & 0xF0, t);
            c = a[3];
            if (c == t) {
                M2C_FIELD(a, s16 *, 0x40) = 0x3C;
                a[6]++;
                k = D_80129C04[c];
                if (k != -1) {
                    M2C_FIELD(a, u8 **, 0x14) = func_8007E038(k, 2);
                } else {
                    M2C_FIELD(a, u8 **, 0x14) = NULL;
                }
            }
        }
        break;
    case 1:
        if (M2C_FIELD(a, s16 *, 0x40) != 0) {
            M2C_FIELD(a, s16 *, 0x40)--;
        }
        if ((M2C_FIELD(e, s16 *, 0x6A) & 0xF000) != 0x2000 && M2C_FIELD(a, s16 *, 0x40) == 0) {
            if (M2C_FIELD(a, u8 **, 0x14) != NULL) {
                M2C_FIELD(a, u8 **, 0x14)[4] = 2;
                M2C_FIELD(a, u8 **, 0x14) = NULL;
            }
            a[6] = 0;
        }
        break;
    }
}

typedef struct { u8 pad0[7]; u8 unk7; u8 pad8[7]; u8 unkF; u8 unk10; } AreaState808_10;
extern AreaState808_10 D_800BF808_7eac;
void func_80116C14(a)
u8 *a;
{
    u8 *e = D_800E7E80;
    s32 c;
    s32 t;
    s16 k;
    s32 r;
    u8 *p;

    switch (a[6]) {
    case 0:
        if (((M2C_FIELD(e, s16 *, 0x6A) & 0xF000) == 0x2000 && e[0x17B] == 0) || D_800BF818 == 5) {
            c = inl_80117658(M2C_FIELD(e, u16 *, 0x6A) & 0x1F);
            t = inl_801176EC(M2C_FIELD(e, u16 *, 0x6A) & 0xF0, c);
            if (c == a[0xBE]) {
                if (a[3] == t) {
                    D_800BF808_7eac.unk10 = 1;
                    D_800BF808_7eac.unkF = c;
                    D_1F8001C6 = 1;
                    a[0x5E] = 0;
                    k = D_80129C04[t];
                    if (k != -1) {
                        M2C_FIELD(a, u8 **, 0x14) = func_8007E038(k, 2);
                    } else {
                        M2C_FIELD(a, u8 **, 0x14) = NULL;
                    }
                    if (a[0xBF] != 0) {
                        func_80074590(0x17, 0, 0xF);
                    }
                    if (M2C_FIELD(e, s16 *, 0x6A) != 0x2009) {
                        e[0x145] = 0;
                        func_80054198(e);
                        e[5] = 0;
                        e[6] = 0;
                        e[7] = 0;
                    }
                } else {
                    a[0x5E] = 1;
                }
                a[6]++;
            }
        }
        break;
    case 1:
        if (func_80072E60(a) != 0 && D_800BF816 != 0) {
            a[6]++;
            func_80072EFC(a);
        }
        break;
    case 2:
        r = D_800BF808_7eac.unk10;
        if (r == 2 && D_800BF808_7eac.unk7 == 0) {
            p = M2C_FIELD(a, u8 **, 0x14);
            a[6]++;
            if (p != NULL) {
                p[4] = r;
                M2C_FIELD(a, u8 **, 0x14) = NULL;
            }
        }
        break;
    case 3:
        if (((M2C_FIELD(e, s16 *, 0x6A) & 0xF000) == 0x2000 && e[0x17B] == 0) || D_800BF818 == 6) {
            t = inl_801176EC(M2C_FIELD(e, u16 *, 0x6A) & 0xF0, D_800BF817);
            if (a[3] == t) {
                D_800BF818 = 3;
                a[0x5E] = 0;
                if (a[0xBF] != 0) {
                    func_80074590(0x17, 0, 0xF);
                }
                if (M2C_FIELD(e, s16 *, 0x6A) != 0x2009) {
                    e[0x145] = 0;
                    func_80054198(e);
                    e[5] = 0;
                    e[6] = 0;
                    e[7] = 0;
                }
            } else {
                if (a[0x5E] == 0) {
                    M2C_FIELD(a, u16 *, 0x56) = M2C_FIELD(a, u16 *, 0x5A);
                    func_800517F8(a);
                }
                a[0x5E] = 1;
            }
            a[6]++;
        }
        break;
    case 4:
        if (D_800BF808_7eac.unk10 == 4 && D_800BF808_7eac.unk7 == 0) {
            a[6]++;
        }
        break;
    case 5:
        r = 0;
        switch (a[0x46]) {
        case 0:
            *(s16 *)(a + 0x50) += 0x40;
            if (*(s16 *)(a + 0x50) > 0) {
                *(s16 *)(a + 0x50) = 0;
                r = 1;
            }
            break;
        case 1:
            *(s16 *)(a + 0x50) -= 0x40;
            if (*(s16 *)(a + 0x50) < 0) {
                *(s16 *)(a + 0x50) = 0;
                r = 1;
            }
            break;
        }
        *(u16 *)(a + 0x56) = *(u16 *)(a + 0x5A) - *(u16 *)(a + 0x50);
        if (r != 0) {
            if (a[0x5E] == 0 && a[0xBF] != 0) {
                func_80074590(0x18, 0, 0xF);
            }
            a[6] = 0;
            a[0x5E] = 2;
        }
        break;
    }
}

extern u8 D_800BF8BE;
extern u8 D_80129BF4[];
/* func_8011778C, inlined */
static inline void func_8011778C_inl(u8 *a)
{
    switch (a[5]) {
    case 0:
        if (D_800BF8BE == 0xFF) {
            a[5] = 1;
            return;
        }
        func_801169D8(a);
        return;
    case 1:
        func_80116C14(a);
        return;
    }
}

void func_8011718C(u8 *a)
{
    switch (a[4]) {
    case 0:
        if (func_80051B70(a, 0xC, D_80129BF4[a[3]]) != 0) {
            break;
        }
        a[0x5E] = 2;
        *(s16 *)(a + 0x50) = 0;
        *(s32 *)(a + 0x14) = 0;
        a[0xBF] = 1;
        a[0x28] |= 0x80;
        a[4]++;
        *(s16 *)(a + 0x5A) = *(s16 *)(a + 0x56);
        switch (a[3]) {
        case 0:
            a[0x46] = 1;
            a[0xBE] = 0;
            break;
        case 1:
            a[0x46] = 1;
            a[0xBE] = 1;
            break;
        case 2:
            a[0x46] = 1;
            a[0xBE] = 2;
            break;
        case 3:
            a[0x46] = 1;
            a[0xBE] = 4;
            break;
        case 4:
            a[0x46] = 1;
            a[0xBE] = 4;
            break;
        case 5:
            a[0x46] = 1;
            a[0xBE] = 4;
            break;
        case 6:
            a[0x46] = 1;
            a[0xBE] = 4;
            break;
        case 7:
            a[0x46] = 1;
            a[0xBE] = 6;
            break;
        case 8:
            a[0x46] = 1;
            a[0xBE] = 6;
            break;
        case 9:
            a[0x46] = 1;
            a[0xBE] = 5;
            break;
        case 10:
            break;
        case 11:
            a[0xBF] = 0;
            *(s32 *)(*(u8 **)(a + 0xC0) + 0x40) = 0;
            a[0xBE] = 3;
            break;
        case 12:
            a[0xBF] = 0;
            *(s32 *)(*(u8 **)(a + 0xC0) + 0x40) = 0;
            a[0xBE] = 7;
            break;
        case 13:
            a[0xBF] = 0;
            *(s32 *)(*(u8 **)(a + 0xC0) + 0x40) = 0;
            a[0xBE] = 8;
            break;
        }
        func_800517F8(a);
        break;
    case 1:
        switch (a[3]) {
        case 0:
            func_8011778C_inl(a);
            break;
        case 1:
            func_8011778C_inl(a);
            break;
        case 2:
            func_8011778C_inl(a);
            break;
        case 3:
            func_8011778C_inl(a);
            break;
        case 4:
            func_8011778C_inl(a);
            break;
        case 5:
            func_8011778C_inl(a);
            break;
        case 6:
            func_8011778C_inl(a);
            break;
        case 7:
            func_8011778C_inl(a);
            break;
        case 8:
            func_8011778C_inl(a);
            break;
        case 9:
            func_8011778C_inl(a);
            break;
        case 10:
            break;
        case 11:
            func_80116C14(a);
            break;
        case 12:
            func_80116C14(a);
            break;
        case 13:
            if (a[5] == 0) {
                func_801169D8(a);
            }
            break;
        }
        if (func_8007778C(a) != 0 && a[0x5E] == 0) {
            func_800517F8(a);
        }
        if (D_800BF816 != 0) {
            a[1] = 0;
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

s32 func_801175D0(u8 *a) {
    s32 r = 0;

    switch (a[0x46]) {
    case 0:
        M2C_FIELD(a, s16 *, 0x50) += 0x40;
        if (M2C_FIELD(a, s16 *, 0x50) > 0) {
            M2C_FIELD(a, s16 *, 0x50) = 0;
            r = 1;
        }
        break;
    case 1:
        M2C_FIELD(a, s16 *, 0x50) -= 0x40;
        if (M2C_FIELD(a, s16 *, 0x50) < 0) {
            M2C_FIELD(a, s16 *, 0x50) = 0;
            r = 1;
        }
        break;
    }
    M2C_FIELD(a, s16 *, 0x56) = M2C_FIELD(a, s16 *, 0x5A) - M2C_FIELD(a, s16 *, 0x50);
    return r;
}

s32 func_80117658(s32 k) {
    s32 r = 0;

    if (k == 5) {
        r = 0;
    } else if (k == 6) {
        r = 1;
    } else if (k == 7) {
        r = 2;
    } else if (k == 8) {
        r = 3;
    } else if (k == 10) {
        r = 4;
    } else if (k == 12) {
        r = 5;
    } else if (k == 13) {
        r = 6;
    } else if (k == 9) {
        r = 7;
    } else if (k == 14) {
        r = 8;
    }
    return r;
}

s32 func_801176EC(s32 a, s32 b) {
    s32 r;

    switch (b) {
    case 1:
        r = 1;
        break;
    case 2:
        r = 2;
        break;
    case 3:
        r = 11;
        break;
    case 4:
        if (a == 0) {
            r = 6;
        } else if (a == 0x20) {
            r = 5;
        } else if (a == 0x40) {
            r = 4;
        } else {
            r = 3;
        }
        break;
    case 5:
        if (a == 0) {
            r = 9;
        } else {
            r = 10;
        }
        break;
    case 6:
        if (a == 0) {
            r = 7;
        } else {
            r = 8;
        }
        break;
    case 7:
        r = 12;
        break;
    case 0:
    default:
        r = 0;
        break;
    }
    return r;
}

void func_8011778C(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 5);
    switch (temp_v1) {                              /* irregular */
    case 0:
        if (D_800BF8BE == 0xFF) {
            M2C_FIELD(arg0, u8 *, 5) = 1U;
            return;
        }
        func_801169D8();
        return;
    case 1:
        func_80116C14();
        return;
    }
}

extern u8 D_800BF8BE;
void func_801177F8(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 5);
    switch (temp_v1) {                              /* irregular */
    case 0:
        if (D_800BF8BE == 0xFF) {
            M2C_FIELD(arg0, u8 *, 5) = 1U;
            return;
        }
        func_801169D8();
        return;
    case 1:
        func_80116C14();
        return;
    }
}

extern u8 D_800BF8BE;
void func_80117864(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 5);
    switch (temp_v1) {                              /* irregular */
    case 0:
        if (D_800BF8BE == 0xFF) {
            M2C_FIELD(arg0, u8 *, 5) = 1U;
            return;
        }
        func_801169D8();
        return;
    case 1:
        func_80116C14();
        return;
    }
}

extern u8 D_800BF8BE;
void func_801178D0(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 5);
    switch (temp_v1) {                              /* irregular */
    case 0:
        if (D_800BF8BE == 0xFF) {
            M2C_FIELD(arg0, u8 *, 5) = 1U;
            return;
        }
        func_801169D8();
        return;
    case 1:
        func_80116C14();
        return;
    }
}

extern u8 D_800BF8BE;
void func_8011793C(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 5);
    switch (temp_v1) {                              /* irregular */
    case 0:
        if (D_800BF8BE == 0xFF) {
            M2C_FIELD(arg0, u8 *, 5) = 1U;
            return;
        }
        func_801169D8();
        return;
    case 1:
        func_80116C14();
        return;
    }
}

extern u8 D_800BF8BE;
void func_801179A8(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 5);
    switch (temp_v1) {                              /* irregular */
    case 0:
        if (D_800BF8BE == 0xFF) {
            M2C_FIELD(arg0, u8 *, 5) = 1U;
            return;
        }
        func_801169D8();
        return;
    case 1:
        func_80116C14();
        return;
    }
}

extern u8 D_800BF8BE;
void func_80117A14(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 5);
    switch (temp_v1) {                              /* irregular */
    case 0:
        if (D_800BF8BE == 0xFF) {
            M2C_FIELD(arg0, u8 *, 5) = 1U;
            return;
        }
        func_801169D8();
        return;
    case 1:
        func_80116C14();
        return;
    }
}

extern u8 D_800BF8BE;
void func_80117A80(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 5);
    switch (temp_v1) {                              /* irregular */
    case 0:
        if (D_800BF8BE == 0xFF) {
            M2C_FIELD(arg0, u8 *, 5) = 1U;
            return;
        }
        func_801169D8();
        return;
    case 1:
        func_80116C14();
        return;
    }
}

extern u8 D_800BF8BE;
void func_80117AEC(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 5);
    switch (temp_v1) {                              /* irregular */
    case 0:
        if (D_800BF8BE == 0xFF) {
            M2C_FIELD(arg0, u8 *, 5) = 1U;
            return;
        }
        func_801169D8();
        return;
    case 1:
        func_80116C14();
        return;
    }
}

extern u8 D_800BF8BE;
void func_80117B58(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 5);
    switch (temp_v1) {                              /* irregular */
    case 0:
        if (D_800BF8BE == 0xFF) {
            M2C_FIELD(arg0, u8 *, 5) = 1U;
            return;
        }
        func_801169D8();
        return;
    case 1:
        func_80116C14();
        return;
    }
}

void func_80117BC4(void) {
}

void func_80117BCC(void) {
    func_80116C14();
}

void func_80117BEC(void) {
    func_80116C14();
}

void func_80117C0C(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 5) == 0) {
        func_801169D8();
    }
}

typedef struct { s16 w, h; } BoxWH;
extern s16 D_80129C20[];
extern BoxWH D_80129C40[];
void func_80117C3C(u8 *a)
{
    s16 *t;
    BoxWH *b;
    s16 w;

    switch (a[4]) {
    case 0:
        t = D_80129C20;
        if (func_80051B70(a, 0xC, t[a[3]]) != 0) {
            break;
        }
        a[0] = 1;
        a[0x29] = 0;
        a[4]++;
        b = (BoxWH *)(((t[a[3]] - 0xB) << 2) + (s32)D_80129C40);
        w = b->w;
        M2C_FIELD(a, s16 *, 0x80) = w;
        M2C_FIELD(a, s16 *, 0x82) = w * 2;
        w = b->h;
        M2C_FIELD(a, s16 *, 0x84) = w;
        M2C_FIELD(a, s16 *, 0x86) = w;
        break;
    case 1:
        if (func_8007778C(a) != 0) {
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

typedef struct { u8 pad[0xC0]; u8 *parts[1]; } PartsOwner80117D64;
#define D64_I16(o) (*(s16 *)(a->pad + (o)))
#define D64_W16(o) (*(u16 *)(a->pad + (o)))
void func_80117D64(PartsOwner80117D64 *a) {
    switch (a->pad[4]) {
    case 0:
        a->pad[8] = 1;
        if (D_800ED098 <= 0) {
            a->pad[4] = 3;
            break;
        }
        D64_I16(0x80) = 0x50;
        D64_I16(0x82) = 0xA0;
        a->pad[9] = 1;
        a->pad[0] = 1;
        a->pad[0xD] = 0;
        a->pad[0xB] = 0;
        a->pad[0x29] = 0;
        D64_I16(0x84) = 0xC4;
        D64_I16(0x86) = 0xC4;
        a->pad[4]++;
        a->parts[0] = func_8007AAE8();
        *(s16 *)(a->parts[0] + 6) = -1;
        *(s16 *)(a->parts[0] + 0) = 0;
        *(s16 *)(a->parts[0] + 2) = 0;
        *(s16 *)(a->parts[0] + 4) = 0;
        *(s16 *)(a->parts[0] + 8) = 0;
        *(s16 *)(a->parts[0] + 0xA) = 0;
        *(s16 *)(a->parts[0] + 0xC) = 0;
        D64_I16(0xB8) = 0x1000;
        D64_I16(0xBA) = 0x1000;
        D64_I16(0xBC) = 0x1000;
        *(s16 *)(a->parts[0] + 0x38) = 0x1000;
        *(s16 *)(a->parts[0] + 0x3A) = 0x1000;
        *(s16 *)(a->parts[0] + 0x3C) = 0x1000;
        D64_W16(0x60) = D64_W16(0x32);
        a->pad[0x2B] = 0;
        if (a->pad[3] == 0) {
            a->pad[5] = 2;
            func_80051B04(a->parts[0], 0xC, 0xE);
        } else {
            func_80051B04(a->parts[0], 0xC, 0x27);
        }
        break;
    case 1:
        if (func_8007778C(a) == 0) {
            break;
        }
        switch (a->pad[5]) {
        case 0:
            if (a->pad[0x2B] != 0) {
                a->pad[0] = 3;
                D64_I16(0x40) = 8;
                a->pad[5]++;
                func_80074590(0x88, 0, 0);
            }
            break;
        case 1:
            if (--D64_I16(0x40) == 0) {
                a->pad[0x2B] = 2;
                a->pad[0] = 2;
                a->pad[5]++;
            }
            D64_W16(0xBA) -= 0x1D0;
            break;
        case 2:
            break;
        }
        func_80051844(a);
        break;
    case 2:
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

typedef struct { u8 pad[0xC0]; u8 *parts[1]; } PartsOwner80117FC0;
extern u8 D_800BFA0B;
#define FC0_I16(o) (*(s16 *)(a->pad + (o)))
#define FC0_W16(o) (*(u16 *)(a->pad + (o)))
void func_80117FC0(PartsOwner80117FC0 *a) {
    u8 *base;

    switch (a->pad[4]) {
    case 0:
        a->pad[8] = 1;
        if (D_800ED098 <= 0) {
            a->pad[4] = 3;
            break;
        }
        a->pad[9] = 1;
        a->pad[0] = 1;
        a->pad[4]++;
        base = D_800ECFC8;
        a->pad[0xD] = 4;
        FC0_I16(0x80) = 0x3C;
        FC0_I16(0x82) = 0x78;
        a->pad[0xB] = 0;
        a->pad[0x29] = 0;
        FC0_I16(0x84) = 0xC4;
        FC0_I16(0x86) = 0xC4;
        a->parts[0] = func_8007AAE8();
        *(s16 *)(a->parts[0] + 6) = -1;
        *(s16 *)(a->parts[0] + 0) = 0;
        *(s16 *)(a->parts[0] + 2) = 0;
        *(s16 *)(a->parts[0] + 4) = 0;
        *(s16 *)(a->parts[0] + 8) = 0;
        *(s16 *)(a->parts[0] + 0xA) = 0;
        *(s16 *)(a->parts[0] + 0xC) = 0;
        {
            s32 *offs = (s32 *)(base + 4);
            *(u8 **)(a->parts[0] + 0x40) = base + *(volatile s32 *)&(offs[0x12]);
        }
        a->parts[0][0x3F] = 8;
        FC0_W16(0x60) = FC0_W16(0x32);
        a->pad[0x2B] = 0;
        if (a->pad[3] == 0x65 && (D_800BFA0B & 1)) {
            a->pad[0] = 3;
            a->pad[0x2B] = 2;
            a->pad[5] = 2;
            FC0_W16(0x32) += 0x78;
        }
        break;
    case 1:
        if (D_800BF816 == 0) {
            a->pad[4] = 3;
            break;
        }
        if (func_8007778C(a) == 0) {
            break;
        }
        switch (a->pad[5]) {
        case 0:
            if (a->pad[0x2B] != 0) {
                a->pad[0] = 3;
                FC0_I16(0x40) = 8;
                a->pad[5]++;
            }
            break;
        case 1:
            if (--FC0_I16(0x40) == 0) {
                a->pad[0x2B] = 2;
                a->pad[5]++;
            }
            FC0_W16(0x32) += 0xF;
            break;
        case 2:
            if (a->pad[0x2B] == 0) {
                FC0_I16(0x40) = 8;
                a->pad[5]++;
            }
            break;
        case 3:
            if (--FC0_I16(0x40) == 0) {
                a->pad[5] = 0;
                a->pad[0x2B] = 0;
                a->pad[0] = 1;
            }
            FC0_W16(0x32) -= 0xF;
            break;
        }
        func_800517F8(a);
        break;
    case 2:
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

typedef struct {
    u8 b0, b1, b2, b3;
    s16 x, y, z, pad;
    void *fn;
} Placement16;
extern Placement16 D_80129C4C[];
void func_80118280(u8 *a, s32 i) {
    Placement16 *p = &D_80129C4C[i];
    u8 *e;

    e = func_8007AA38(a, p->b1 | ((p->b0 & 0x7F) << 8), 0, 0);
    if (e != NULL) {
        M2C_FIELD(e, u8 **, 0x10) = a;
        e[2] = p->b2;
        e[0x28] = p->b0;
        M2C_FIELD(a, u8 **, 0x14) = e;
        M2C_FIELD(e, s32 *, 0x2C) = p->x << 16;
        M2C_FIELD(e, s32 *, 0x30) = p->y << 16;
        M2C_FIELD(e, s32 *, 0x34) = p->z << 16;
        e[3] = p->b3;
        M2C_FIELD(e, s16 *, 0x54) = 0;
        M2C_FIELD(e, s16 *, 0x56) = 0;
        M2C_FIELD(e, s16 *, 0x58) = 0;
        M2C_FIELD(e, void **, 0x1C) = p->fn;
    }
}

typedef struct { u8 pad[0xC0]; u8 *parts[1]; } PartsOwner80118354;
typedef struct { u8 b0; u8 b1; s16 v[6]; s16 idx; } PartInit80118354;
extern u8 *D_800ECFD0;
extern PartInit80118354 D_80129C6C[];
void func_801255C0(s32 arg0);
void func_80118354(PartsOwner80118354 *a) {
    s32 i;
    u8 *base;
    s32 *offs;
    PartInit80118354 *e;
    u8 *q;

    switch (a->pad[4]) {
    case 0:
        a->pad[8] = 0xE;
        if (D_800ED098 < a->pad[8]) {
            a->pad[4] = 3;
            break;
        }
        a->pad[9] = a->pad[8];
        a->pad[0] = 1;
        a->pad[4]++;
        base = D_800ECFD0;
        a->pad[0xD] = 4;
        i = 0;
        a->pad[0xB] = 0;
        offs = (s32 *)(base + 4);
        for (; i < a->pad[8]; i++) {
            q = func_8007AAE8();
            a->parts[i] = q;
            *(s16 *)(q + 6) = -1;
            q[0x3E] = D_80129C6C[i].b0;
            q[0x3F] = 0x1E;
            *(s16 *)(q + 0) = D_80129C6C[i].v[0];
            *(s16 *)(q + 2) = D_80129C6C[i].v[1];
            *(s16 *)(q + 4) = D_80129C6C[i].v[2];
            *(s16 *)(q + 8) = D_80129C6C[i].v[3];
            *(s16 *)(q + 0xA) = D_80129C6C[i].v[4];
            *(s16 *)(q + 0xC) = D_80129C6C[i].v[5];
            *(u8 **)(q + 0x40) = base + offs[D_80129C6C[i].idx];
            *(s16 *)(q + 0x38) = D_80129C6C[i].idx;
        }
        *(s16 *)(a->pad + 0x80) = 0x23A;
        *(s16 *)(a->pad + 0x82) = 0x474;
        *(s16 *)(a->pad + 0x84) = 0x80;
        *(s16 *)(a->pad + 0x86) = 0xD2;
        func_80051C8C(a);
        break;
    case 1:
        a->pad[1] = 1;
        func_80077EBC(a);
        switch (a->pad[5]) {
        case 0:
            if (D_800BF8BE == 0xFF) {
                a->pad[5] = 1;
                *(s16 *)(a->pad + 0x40) = 0;
            }
            break;
        case 1:
            func_801255C0(0xC);
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

extern u8 D_800A3CC0[];
extern s16 D_80129D4C[];
extern s16 D_80129D54[];
extern u8 D_80129D5C[];
void f_UpdateBuryItInTheSandPitActor(u8 *a)
{
    u8 *g;
    u8 *h;
    s32 k;

    switch (a[4]) {
    case 0:
        if (func_80051B70(a, 0xC, 0x3B) != 0) {
            break;
        }
        M2C_FIELD(a, s16 *, 0x80) = 0xBB;
        M2C_FIELD(a, s16 *, 0x82) = 0x180;
        a[0] = 1;
        M2C_FIELD(a, s16 *, 0x84) = 0x190;
        M2C_FIELD(a, s16 *, 0x86) = 0x190;
        a[0x29] = 0;
        a[0x2B] = 0;
        a[4]++;
        func_80040CDC(a, 0, D_800A3CC0);
        h = (u8 *)&D_800BF870;
        M2C_FIELD(a, s16 *, 0x32) = D_80129D4C[h[0x157] & 0x7F];
        if (h[0x50] == 0xFF) {
            a[4] = 2;
            a[0] = 3;
        }
        func_800517F8(a);
        break;
    case 1:
        if (func_8007778C(a) != 0) {
            if (a[0x2B] == 1) {
                g = (u8 *)&D_800BF870;
                k = g[0x157];
                k &= 0x7F;
                func_8004ED94(D_80129D54[k], 0x41);
                {
                    s16 *t = D_80129D4C;
                    do { k++; } while (0);
                    M2C_FIELD(a, s16 *, 0x32) = t[k];
                }
                g[0x157]++;
                func_800517F8(a);
                a[0x2B] = 0;
                if (k == 3) {
                    func_80040C00(0xC);
                    g[0x157] |= 0x80;
                    a[4] = 2;
                    a[0] = k;
                    a[5] = 0x80;
                }
            }
            if (a[5] == 0) {
                switch (a[6]) {
                case 0:
                    if (a[0x29] != 0) {
                        a[0x70] = 1;
                        a[6]++;
                    }
                    break;
                case 1:
                    if (a[0x70] == 0xFF) {
                        func_80040D68(a, D_80129D5C);
                        a[0x70] = 1;
                        a[6]++;
                    }
                    break;
                case 2:
                    if (a[0x70] == 0xFF) {
                        D_800BF870.pad1[0x156] |= 0x80;
                        a[5]++;
                    }
                    break;
                }
                func_80041098(a);
            }
        }
        a[0x29] = 0;
        a[0x2B] = 0;
        break;
    case 2:
        if (func_8007778C(a) != 0) {
            func_800517F8(a);
        }
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

s32 func_80118860(void) {
    func_801167A8();
    return 1;
}

typedef struct { u8 pad[0xC0]; u8 *parts[1]; } PartsOwner80118880;
extern s32 D_800ECFCC;
extern u8 D_8012A114[];
extern s16 *D_8012A100[];
void func_80118880(PartsOwner80118880 *a) {
    s32 i;
    s16 *t;
    u8 *base;
    s32 *offs;
    u8 *q;
    s16 v;

    a->pad[8] = D_8012A114[a->pad[3] * 2];
    if (D_800ED098 < a->pad[8]) {
        a->pad[4] = 3;
        return;
    }
    a->pad[9] = a->pad[8];
    i = 0;
    base = D_800ECFC8;
    a->pad[0xD] = 0;
    a->pad[0xB] = 0;
    *(s16 *)(a->pad + 0x54) = 0;
    *(s16 *)(a->pad + 0x56) = 0;
    *(s16 *)(a->pad + 0x58) = 0;
    t = D_8012A100[a->pad[3]];
    offs = (s32 *)(base + 4);
    for (; i < a->pad[8]; i++) {
        q = func_8007AAE8();
        a->parts[i] = q;
        *(s16 *)(q + 6) = *t++;
        *(s16 *)(a->parts[i] + 0) = *t++;
        *(s16 *)(a->parts[i] + 2) = *t++;
        *(s16 *)(a->parts[i] + 4) = *t++;
        *(s16 *)(a->parts[i] + 8) = *t++;
        *(s16 *)(a->parts[i] + 0xA) = *t++;
        *(s16 *)(a->parts[i] + 0xC) = *t++;
        *(u8 **)(a->parts[i] + 0x40) = base + offs[*t];
        *(s16 *)(a->parts[i] + 0x38) = 0x1000;
        *(s16 *)(a->parts[i] + 0x3A) = 0x1000;
        *(s16 *)(a->parts[i] + 0x3C) = 0x1000;
        t++;
    }
    *(s16 *)(a->pad + 0xB8) = 0x1000;
    *(s16 *)(a->pad + 0xBA) = 0x1000;
    *(s16 *)(a->pad + 0xBC) = 0x1000;
    *(s16 *)(a->pad + 0x88) = 0;
    *(s16 *)(a->pad + 0x8A) = 0;
    *(s16 *)(a->pad + 0x8C) = 0;
    *(s32 *)(a->pad + 0x3C) = D_800ECFCC;
    a->pad[0x5E] = 0;
    switch (a->pad[3]) {
    case 0:
        func_80077C40(a, D_80139F38, 0);
        *(s16 *)(a->pad + 0x80) = 0x190;
        *(s16 *)(a->pad + 0x82) = 0x320;
        *(s16 *)(a->pad + 0x84) = 0x5A7;
        *(s16 *)(a->pad + 0x86) = 0x5A7;
        break;
    case 1:
        *(s16 *)(a->pad + 0x80) = 10;
        *(s16 *)(a->pad + 0x82) = 10;
        *(s16 *)(a->pad + 0x84) = 10;
        *(s16 *)(a->pad + 0x86) = 10;
        break;
    case 2:
        func_80077C40(a, D_80139F38, 2);
        *(s16 *)(a->pad + 0x80) = 0xDC;
        *(s16 *)(a->pad + 0x82) = 0x1B8;
        *(s16 *)(a->pad + 0x84) = 0x1B3;
        *(s16 *)(a->pad + 0x86) = 0x1B3;
        break;
    case 3:
    case 4:
        func_80118280(a->pad, a->pad[3] - 3);
        func_80077C40(a, D_80139F38, 3);
        *(s16 *)(a->pad + 0x80) = 0xDC;
        *(s16 *)(a->pad + 0x82) = 0x1B8;
        *(s16 *)(a->pad + 0x84) = 0x1B3;
        *(s16 *)(a->pad + 0x86) = 0x1B3;
        a->pad[0x47] = 0;
        break;
    }
    a->pad[0] = 1;
    a->pad[4]++;
}

s32 func_80118B50(s32 arg0) {
    if (M2C_FIELD(arg0, s16 *, 0x40) != 0) {
        if ((func_80119694(arg0, (s32) M2C_FIELD(arg0, s16 *, 0x2E), (s32) M2C_FIELD(arg0, s16 *, 0x36)) << 0x10) != 0) {
            M2C_FIELD(arg0, s8 *, 5) = 3;
        }
    } else if (D_800BF870.pad1[0x18D] & 0x80) {
        if ((func_80119694(arg0, (s32) (s16) ((u16) M2C_FIELD(arg0, s16 *, 0x2E) - 0x14A), (s32) (s16) ((u16) M2C_FIELD(arg0, s16 *, 0x36) - 0x10E)) << 0x10) != 0) {
            M2C_FIELD(arg0, s8 *, 5) = 1;
            M2C_FIELD(arg0, s8 *, 6) = 0;
            M2C_FIELD(arg0, s8 *, 0x5E) = 4;
        }
    } else if ((func_80119694(arg0, (s32) (s16) ((u16) M2C_FIELD(arg0, s16 *, 0x2E) - 0x118), (s32) (s16) ((u16) M2C_FIELD(arg0, s16 *, 0x36) - 0x10E)) << 0x10) != 0) {
        D_800BF870.pad1[0x18D] = 3;
        M2C_FIELD(arg0, s8 *, 5) = 0;
    }
    return func_801255A4((s32) (M2C_FIELD(arg0, u16 *, 0x44) << 0x10) >> 0x18);
}

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80118C54);

s32 func_8011A280(u8 *a);
s32 func_80119D58(u8 *a, s32 b);
s32 func_80119DEC(u8 *a);
void func_8011903C(u8 *a) {
    s32 s = a[6];
    s32 one = 1;

    switch (s) {
    case 0:
        if ((*(u8 **)(a + 0x14))[0x2B] == 2) {
            *(s16 *)(a + 0x40) = one;
            a[6]++;
        }
        break;
    case 1:
        if ((s16)func_80119D58(a, 0) != 0) {
            if (*(s16 *)(a + 0x40) != 0) {
                a[6]++;
            } else {
                a[5] = 2;
                a[6] = 0;
            }
        }
        break;
    case 2:
        if (a[0x2B] == one && D_800BF80A == one && func_8011A280(a) != 0 && (s16)func_80119DEC(a) != 0) {
            a[0] = 2;
            a[5] = one;
            a[6] = 0;
            a[0x5E] = one;
        }
        break;
    case 3:
        if ((s16)func_80119D58(a, 1) != 0) {
            if (*(s16 *)(a + 0x40) != 0) {
                a[5] = 3;
            } else {
                (*(u8 **)(a + 0x14))[0x2B] = 0;
                a[0] = one;
            }
            a[6] = 0;
        }
        break;
    }
}

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_801191B0);

s32 func_80119D58(u8 *a, s32 b);
s32 func_80119DEC(u8 *a);
void func_80119390(u8 *a) {
    s32 s = a[6];
    s32 one = 1;

    switch (s) {
    case 0:
        if ((*(u8 **)(a + 0x14))[0x2B] == 2) {
            *(s16 *)(a + 0x40) = one;
            a[6]++;
        }
        break;
    case 1:
        if ((s16)func_80119D58(a, 0) != 0) {
            if (*(s16 *)(a + 0x40) != 0) {
                a[6]++;
            } else {
                a[5] = 2;
                a[6] = 0;
            }
        }
        break;
    case 2:
        if (a[0x2B] == one && D_800BF808_1760[2] == one && (D_800BF808_1760[3] == 0x83 || D_800BF808_1760[3] == 0x84) && (s16)func_80119DEC(a) != 0) {
            a[0] = 2;
            a[5] = one;
            a[6] = 0;
            a[0x5E] = 2;
        }
        break;
    case 3:
        if ((s16)func_80119D58(a, 1) != 0) {
            if (*(s16 *)(a + 0x40) != 0) {
                a[5] = 3;
            } else {
                a[0] = one;
                (*(u8 **)(a + 0x14))[0x2B] = 0;
            }
            a[6] = 0;
        }
        break;
    }
}

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80119510);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80119694);

void func_80119990(void *arg0);
void func_801199EC(u8 *a);
void func_80119ADC(u8 *a);
void func_80119BAC(u8 *a);
void func_80119C7C(u8 *a);
void func_80119880(u8 *a) {
    switch (a[4]) {
    case 0:
        func_80118880(a);
        break;
    case 1:
        a[1] = 1;
        func_80077EBC(a);
        switch (a[3]) {
        case 0:
            func_80119990(a);
            break;
        case 1:
            func_801199EC(a);
            break;
        case 2:
            func_80119ADC(a);
            break;
        case 3:
            func_80119BAC(a);
            break;
        case 4:
            func_80119C7C(a);
            break;
        }
        func_800518FC(a);
        break;
    case 2:
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

extern u8 D_800BF8BE;
void func_80119990(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 5);
    switch (temp_v1) {                              /* irregular */
    case 0:
        if (D_800BF8BE == 0xFF) {
            M2C_FIELD(arg0, u8 *, 5) = 1U;
            return;
        }
        return;
    case 1:
        func_80076D68();
        break;
    }
}

void func_80123470();
void func_801199EC(u8 *a) {
    u8 *e;

    switch (a[5]) {
    case 0:
        if (D_800BF8BE == 0xFF) {
            a[5] = 1;
            M2C_FIELD(a, s16 *, 0x40) = 0;
            M2C_FIELD(a, s16 *, 0x42) = 0x1E;
        }
        break;
    case 1:
        M2C_FIELD(a, s16 *, 0x40) = (M2C_FIELD(a, u16 *, 0x40) + 1) & 7;
        func_801255C0(0x20);
        if (--M2C_FIELD(a, s16 *, 0x42) == 0) {
            e = func_80072DDC(a, 0, 2, 0x20);
            if (e != NULL) {
                e[3] = 2;
                e[0] = 1;
                M2C_FIELD(e, void **, 0x1C) = func_80123470;
                e[0x28] |= 0x80;
            }
            M2C_FIELD(a, s16 *, 0x42) = (u8)func_8009A450() + 0x1E;
        }
        break;
    }
}

extern u8 D_800BF9FE;
void func_80119ADC(u8 *a) {
    switch (a[5]) {
    case 0:
        func_8011A10C(a);
        break;
    case 1:
        if ((s16)func_80119F78(a)) {
            if (M2C_FIELD(a, s16 *, 0x40) != 0) {
                a[5] = 2;
                a[6] = 0;
            } else {
                a[5] = 0;
                D_800BF9FE = 0;
            }
        }
        break;
    case 2:
        func_80118B50((s32)a);
        break;
    case 3:
        func_80118C54(a);
        break;
    }
    a[0x2B] = 0;
}

void func_80119BAC(u8 *a) {
    switch (a[5]) {
    case 0:
        func_8011903C(a);
        break;
    case 1:
        if ((s16)func_80119F78(a)) {
            if (M2C_FIELD(a, s16 *, 0x40) != 0) {
                a[5] = 2;
                a[6] = 0;
            } else {
                a[5] = 0;
                a[6] = 3;
            }
        }
        break;
    case 2:
        func_8011A1F0(a);
        break;
    case 3:
        func_801191B0(a);
        break;
    }
    a[0x2B] = 0;
}

void func_80119C7C(u8 *a) {
    switch (a[5]) {
    case 0:
        func_80119390(a);
        break;
    case 1:
        if ((s16)func_80119F78(a)) {
            if (M2C_FIELD(a, s16 *, 0x40) != 0) {
                a[5] = 2;
                a[6] = 0;
            } else {
                a[0] = 1;
                a[5] = 0;
                a[6] = 2;
                M2C_FIELD(a, s16 *, 0x40) = 1;
            }
        }
        break;
    case 2:
        func_8011A348(a);
        break;
    case 3:
        func_80119510(a);
        break;
    }
    a[0x2B] = 0;
}

#define P(a, o) M2C_FIELD(a, u8 **, o)
s32 func_80119D58(u8 *a, s32 b) {
    if (b == 0) {
        M2C_FIELD(P(a, 0xC4), s16 *, 8) += 0x80;
        if (M2C_FIELD(P(a, 0xC4), s16 *, 8) >= 0x400) {
            M2C_FIELD(P(a, 0xC4), s16 *, 8) = 0x400;
            a[0x47] = 1;
            return 1;
        }
    } else {
        M2C_FIELD(P(a, 0xC4), s16 *, 8) -= 0x80;
        if (M2C_FIELD(P(a, 0xC4), s16 *, 8) <= 0) {
            M2C_FIELD(P(a, 0xC4), s16 *, 8) = 0;
            a[0x47] = 0;
            return 1;
        }
    }
    return 0;
}

extern u8 D_80129E18[];
s32 func_80119DEC(u8 *a) {
    u8 *g = D_800BF808_1760;
    u8 *p;

    p = func_8006FB0C(a, g[3]);
    M2C_FIELD(g, u8 **, 0x3C) = p;
    if (p != NULL) {
        p[0x5E] = 0;
        func_80040CDC(a, D_80139F38, D_80129E18);
        a[0x70] = 1;
        func_80042354(1, 1);
        return 1;
    }
    return 0;
}

#define FU16(p, o) M2C_FIELD(p, u16 *, o)
#define FP(p, o) M2C_FIELD(p, u8 **, o)
extern u8 *D_800BF844_3cf3;
u8 *func_8011C94C(s32 arg0, s8 arg1);
s32 func_80119E68(u8 *a, s32 k, u8 *e) {
    u8 *t = D_800BF844_3cf3;
    u8 *g;

    switch (k) {
    case 0:
        e = func_8011C94C(a, 0);
        break;
    case 1:
        e = func_8006FC34(a, F16(a, 0x60));
        break;
    case 2:
        e = func_8006FB0C(a, F16(a, 0x60));
        break;
    }
    if (e != NULL) {
        g = D_800BF808_1760;
        F16(a, 0x40) = 0;
        FP(g, 0x3C)[4] = 2;
        FP(g, 0x3C) = e;
        F16(e, 0x2E) = FU16(t, 0x2E);
        F16(e, 0x32) = FU16(t, 0x32);
        F16(e, 0x36) = FU16(t, 0x36);
        if (k != 0) {
            e[5] = 1;
            F16(e, 0x60) = 0;
            e[0x5F] |= 1;
        }
        return 1;
    }
    return 0;
}

extern void *D_80129FB8[];
s32 func_80119F78(u8 *a) {
    func_80041098(a);
    if (a[0x71] != 0xFF) {
        return 0;
    }
    switch (a[6]) {
    case 0:
        func_80040D68(a, D_80129FB8[a[0x5E]]);
        a[0x70] = 1;
        a[6]++;
        break;
    case 1:
        return 1;
    }
    return 0;
}

s32 func_8011A010(u8 *a) {
    if (a[3] == 2 && M2C_FIELD(a, s16 *, 0x62) == 0) {
        if ((u16)(M2C_FIELD(a, u16 *, 0x60) - 0x81) < 2) {
            return 3;
        }
        return 2;
    }
    return 2;
}

extern u8 D_800BF9EB;
s32 func_8011A058(u8 *a) {
    if (a[3] == 2 && M2C_FIELD(a, s16 *, 0x62) == 0) {
        if (M2C_FIELD(a, s16 *, 0x60) == 0x4A) {
            return 3;
        }
        return 2;
    }
    return 2;
}

s32 func_8011A098(u8 *a) {
    if (a[3] == 2 && M2C_FIELD(a, s16 *, 0x62) == 0) {
        if (M2C_FIELD(a, s16 *, 0x60) == 0x93) {
            return 3;
        }
        return 2;
    }
    return 2;
}

s32 func_8011A0D8(u8 *a) {
    if (a[3] != 3) {
        return 2;
    }
    if (M2C_FIELD(a, s16 *, 0x60) == 0x7B) {
        return 3;
    }
    return 2;
}

void func_8011A10C(u8 *a) {
    u8 *g = (u8 *)&D_800BF870;
    u8 *t;

    if (g[0x18E] == 1) {
        a[5] = 2;
        a[6] = 0;
        *(s16 *)(a + 0x40) = 1;
        return;
    }
    if (a[0x2B] == 1) {
        t = D_800BF808_1760;
        if (t[2] == 1 && (t[3] == 0x7F || t[3] == 0x80 || t[3] == 0x92) && (s16)func_80119DEC(a) != 0) {
            s32 k = t[3];
            *(s16 *)(a + 0x62) = 0;
            *(s16 *)(a + 0x40) = 1;
            *(s16 *)(a + 0x60) = k;
            g[0x18E] = 0x81;
            a[5] = 1;
            a[6] = 0;
            a[0x5E] = 0;
        }
    }
}

void func_8011A1F0(u8 *a) {
    if (M2C_FIELD(a, s16 *, 0x40) != 0) {
        if ((s16)func_80119694(a, M2C_FIELD(a, s16 *, 0x2E), M2C_FIELD(a, s16 *, 0x36)) != 0) {
            a[5] = 0;
            a[6] = 3;
        }
    } else if ((s16)func_80119694(a, M2C_FIELD(a, s16 *, 0x2E), (s16)(M2C_FIELD(a, s16 *, 0x36) - 0x1C2)) != 0) {
        a[5] = 1;
        a[6] = 0;
        a[0x5E] = 5;
    }
}

extern u8 D_800BF80B;
extern u8 D_800BF901;
s32 func_8011A280(u8 *a) {
    switch (D_800BF80B) {
    case 0x85:
        M2C_FIELD(a, s16 *, 0x60) = 0x49;
        break;
    case 0x79:
    case 0x7A:
        if (D_800BF901 == 0xFF) {
            M2C_FIELD(a, s16 *, 0x60) = 0x7B;
        } else {
            M2C_FIELD(a, s16 *, 0x60) = 0x7A;
        }
        break;
    case 0x81:
        if (D_800BF901 == 0xFF) {
            M2C_FIELD(a, s16 *, 0x60) = 0x83;
        } else {
            M2C_FIELD(a, s16 *, 0x60) = D_800BF80B;
        }
        break;
    case 0x82:
        if (D_800BF901 == 0xFF) {
            M2C_FIELD(a, s16 *, 0x60) = 0x84;
        } else {
            M2C_FIELD(a, s16 *, 0x60) = D_800BF80B;
        }
        break;
    default:
        return 0;
    }
    return 1;
}

void func_8011A348(u8 *a) {
    GameState *g;

    if (M2C_FIELD(a, s16 *, 0x40) != 0) {
        if ((s16)func_80119694(a, M2C_FIELD(a, s16 *, 0x2E), M2C_FIELD(a, s16 *, 0x36)) != 0) {
            g = &D_800BF870;
            if (g->pad1[0x19A] == 0) {
                g->pad1[0x19A]++;
                a[5] = 1;
                M2C_FIELD(a, s16 *, 0x40) = 0;
                a[6] = 0;
                a[0x5E] = 5;
            } else {
                a[5] = 0;
                a[6] = 3;
            }
        }
    } else if ((s16)func_80119694(a, M2C_FIELD(a, s16 *, 0x2E), (s16)(M2C_FIELD(a, s16 *, 0x36) - 0x1C2)) != 0) {
        D_800BF870.pad1[0x19A]++;
        a[5] = 0;
        a[6] = 3;
    }
}

INCLUDE_ASM("asm/a02/nonmatchings/a02", f_UpdateLetsMakeAPotSequence);

/* func_8011AB34, inlined */
static inline void inl_8011AB34(u8 *a) {
    if (func_80051B70(a, 0xC, 0x34) == 0) {
        a[0xD] |= 4;
        M2C_FIELD(a, u8 **, 0xC0)[0x3F] = 0xEC;
        a[0] = 1;
        M2C_FIELD(a, s16 *, 0x80) = 0x64;
        M2C_FIELD(a, s16 *, 0x82) = 0xC8;
        M2C_FIELD(a, s16 *, 0x84) = 0x3C;
        M2C_FIELD(a, s16 *, 0x86) = 0x78;
        M2C_FIELD(a, s16 *, 0x48) = 0x18;
        M2C_FIELD(a, s16 *, 0x54) = 0;
        M2C_FIELD(a, s16 *, 0x56) = 0;
        M2C_FIELD(a, s16 *, 0x58) = 0;
        a[0x2B] = 0;
        M2C_FIELD(a, s16 *, 0x4C) = 0x20;
    }
}
void func_8011A8D4(u8 *a) {
    switch (a[4]) {
    case 0:
        a[4] = 1;
        switch (a[3]) {
        case 0:
        case 3:
            inl_8011AB34(a);
            break;
        case 1:
        case 2:
            if (func_80051B70(a, 0xC, 0x33) == 0) {
                a[0] = 2;
                M2C_FIELD(a, s16 *, 0x54) = 0;
                M2C_FIELD(a, s16 *, 0x56) = 0;
                M2C_FIELD(a, s16 *, 0x58) = 0;
            }
            break;
        }
        break;
    case 1:
        switch (a[3]) {
        case 3:
            if (D_800BF816 == 0) {
                a[4] = 3;
                break;
            }
        case 0:
            f_UpdateLetsMakeAPotSequence(a);
            break;
        case 1:
            if (D_800BF816 == 0) {
                a[4] = 3;
                break;
            }
        case 2:
            a[1] = 1;
            func_80077EBC(a);
            func_800517F8(a);
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

void func_8011A8D4();
s32 func_8011AAC0(u8 *a) {
    u8 t;
    u8 *p = func_80072DDC(0, 129, 4, 36);

    if (p == NULL) {
        return 0;
    }
    M2C_FIELD(p, s16 *, 0x2E) = 3540;
    M2C_FIELD(p, s16 *, 0x32) = -2090;
    M2C_FIELD(p, s16 *, 0x36) = 6050;
    t = a[0x5E];
    M2C_FIELD(p, void **, 0x1C) = func_8011A8D4;
    p[0x3] = t;
    return 1;
}

void func_8011AB34(u8 *a) {
    if (func_80051B70(a, 0xC, 0x34) == 0) {
        a[0xD] |= 4;
        M2C_FIELD(a, u8 **, 0xC0)[0x3F] = 0xEC;
        a[0] = 1;
        M2C_FIELD(a, s16 *, 0x80) = 0x64;
        M2C_FIELD(a, s16 *, 0x82) = 0xC8;
        M2C_FIELD(a, s16 *, 0x84) = 0x3C;
        M2C_FIELD(a, s16 *, 0x86) = 0x78;
        M2C_FIELD(a, s16 *, 0x48) = 0x18;
        M2C_FIELD(a, s16 *, 0x54) = 0;
        M2C_FIELD(a, s16 *, 0x56) = 0;
        M2C_FIELD(a, s16 *, 0x58) = 0;
        a[0x2B] = 0;
        M2C_FIELD(a, s16 *, 0x4C) = 0x20;
    }
}

void func_8011ABC8(u8 *a) {
    if (func_80051B70(a, 0xC, 0x33) == 0) {
        a[0] = 2;
        M2C_FIELD(a, s16 *, 0x54) = 0;
        M2C_FIELD(a, s16 *, 0x56) = 0;
        M2C_FIELD(a, s16 *, 0x58) = 0;
    }
}

void func_8011AC0C(void *arg0) {
    M2C_FIELD(arg0, s8 *, 1) = 1;
    func_80077EBC();
    func_800517F8(arg0);
}

typedef struct { u8 pad[0xC0]; u8 *parts[1]; } PartsOwner8011AC40;
extern u8 D_800E8008[];
#define AC40_I16(o) (*(s16 *)(a->pad + (o)))
#define AC40_W16(o) (*(u16 *)(a->pad + (o)))
#define AC40_S32(o) (*(s32 *)(a->pad + (o)))
void func_8011AC40(PartsOwner8011AC40 *a) {
    u8 *g = D_800E8008;
    s32 one = 1;
    s32 i;

    switch (a->pad[5]) {
    case 0:
        if (D_800BFA03 == 5) {
            g[0x64] = 8;
            func_8006CBA8(a->pad + 0x2C);
            AC40_I16(0x40) = 0x3C;
            AC40_I16(0x48) = 0x5000;
            a->pad[6] = 0;
            a->pad[5]++;
        }
        break;
    case 1:
        if (--AC40_I16(0x40) <= 0) {
            a->pad[5]++;
        }
        break;
    case 2:
        a->pad[1] = one;
        func_80077EBC(a);
        switch (a->pad[6]) {
        case 0:
            AC40_S32(0x2C) -= AC40_I16(0x48) << 8;
            if (AC40_S32(0x2C) <= 0x2C000000) {
                D_800BFA03 = 7;
                AC40_I16(0x4A) = -0x2800;
                AC40_S32(0x2C) = 0x2C000000;
                AC40_I16(0x50) = 0x380;
                a->pad[6]++;
            }
            break;
        case 1:
            AC40_W16(0x58) = (AC40_W16(0x32) + 0xD3E) * 2;
        case 2:
        case 3:
            AC40_W16(0x4A) += AC40_W16(0x50);
            AC40_S32(0x30) += AC40_I16(0x4A) << 8;
            if (AC40_S32(0x30) >= (s32)0xF2C20000) {
                AC40_S32(0x30) = 0xF2C20000;
                AC40_I16(0x58) = 0;
                AC40_I16(0x4A) = -0x2800;
                AC40_I16(0x50) = (-(a->pad[6] << 2) + (a->pad[6] << 5)) << 7;
                if (++a->pad[6] >= 4) {
                    g[0x64] = 7;
                    D_800BFA03 = 6;
                    a->pad[6] = 0;
                    a->pad[5]++;
                }
            }
            break;
        }
        *(u16 *)(g + 0x3A) = AC40_W16(0x2E);
        for (i = 1; i < a->pad[8]; i++) {
            *(u16 *)(a->parts[i] + 0xC) -= AC40_I16(0x48) >> 3;
        }
        break;
    case 3:
        if (D_1F800137 == 0) {
            a->pad[3] = one;
            a->pad[5] = 0;
            a->pad[6] = 0;
        }
        a->pad[1] = one;
        func_80077EBC(a);
        break;
    }
}

typedef struct { u8 pad[0xC0]; u8 *parts[2]; } PartsOwner8011AEF0;
typedef struct { s32 v[4]; } Tbl8011AEF0;
extern Tbl8011AEF0 D_801096DC;
#define EF0_I16(o) (*(s16 *)(a->pad + (o)))
#define EF0_W16(o) (*(u16 *)(a->pad + (o)))
#define EF0_S32(o) (*(s32 *)(a->pad + (o)))
void func_8011AEF0(PartsOwner8011AEF0 *a) {
    u8 *g = D_800E7E80;
    Tbl8011AEF0 tbl;
    s32 d;
    s32 i;

    switch (a->pad[6]) {
    case 0:
        if (a->pad[0x70] == 0xFF) {
            func_80054DAC(g, 0x19, 4);
            g[5] = 0x21;
            g[6] = 0;
            EF0_I16(0x4A) = -0x3200;
            EF0_I16(0x50) = 0x380;
            a->pad[6]++;
        }
        func_80041098(a);
        break;
    case 1: {
        s32 k;
        *(u16 *)(g + 0x2E) += 0xC;
        if (*(s16 *)(g + 0x2E) >= 0x2BF2) {
            *(s16 *)(g + 0x2E) = 0x2BF2;
        }
        EF0_W16(0x4A) += EF0_W16(0x50);
        *(s32 *)(g + 0x30) += EF0_I16(0x4A) << 8;
        do {
            k = -0xD52;
        } while (0);
        if (EF0_I16(0x4A) >= 0 && *(s16 *)(g + 0x32) >= k - *(s16 *)(g + 0x84)) {
            tbl = D_801096DC;
            func_80074590(3, 0, 0);
            *(s16 *)(g + 0x2E) = 0x2BF2;
            *(u16 *)(g + 0x32) = k - *(u16 *)(g + 0x84);
            func_80054DAC(g, tbl.v[func_8009A450() & 3], 8);
            EF0_I16(0x48) = 0;
            EF0_I16(0x4E) = 0xC0;
            *(u16 *)(a->parts[1] + 0xC) &= 0xFFF;
            a->pad[6]++;
        }
        break;
    }
    case 2:
        if (EF0_I16(0x2E) >= 0x32C8) {
            D_1F800236 = 2;
            D_1F800137 = 2;
            D_800BF808_1760[7] = 2;
            D_800BF808_1760[0x31] = 1;
            *(s16 *)(D_800BF808_1760 + 0x32) = 0x400;
            a->pad[6]++;
        }
    case 3:
        EF0_W16(0x48) += EF0_W16(0x4E);
        if (EF0_I16(0x48) >= 0x4000) {
            EF0_I16(0x48) = 0x4000;
        }
        EF0_S32(0x2C) += EF0_I16(0x48) << 8;
        d = (s16)EF0_W16(0x48) >> 6;
        if (d < 0x100) {
            d = 0x100;
        }
        for (i = 1; i < a->pad[8]; i++) {
            *(u16 *)(a->parts[i] + 0xC) += d;
        }
        if (*(s16 *)(a->parts[1] + 0xC) >= 0x1000) {
            *(u16 *)(a->parts[1] + 0xC) &= 0xFFF;
            func_80074590(0x89, 0, 0);
        }
        *(u16 *)(g + 0x2E) = EF0_W16(0x2E);
        break;
    }
}

void func_8011B1FC(u8 *a)
{
    u8 *t = D_800E7E80;
    s32 i;
    s32 d;
    u8 *q;

    switch (a[6]) {
    case 0:
        t[0] = 2;
        *(s16 *)(t + 0x2E) = 0x38A4;
        *(s16 *)(t + 0x36) = 0x2D82;
        *(s16 *)(t + 0x56) = 0x800;
        t[5] = 0x21;
        t[6] = 0;
        *(s16 *)(t + 0x32) = -0xD52 - *(s16 *)(t + 0x84);
        I16(0x40) = 0;
        I16(0x48) = 0;
        I16(0x4E) = 0xC0;
        a[6]++;
        break;
    case 1:
        W16(0x48) += W16(0x4E);
        if (I16(0x48) >= 0x4000) {
            I16(0x48) = 0x4000;
        }
        d = I16(0x48) >> 6;
        if (d < 0x100) {
            d = 0x100;
        }
        for (i = 1; i < a[8]; i++) {
            *(u16 *)(*(u8 **)(a + i * 4 + 0xC0) + 0xC) -= d;
        }
        q = *(u8 **)(a + 0xC4);
        if (*(s16 *)(q + 0xC) < -0xFFF) {
            *(s16 *)(q + 0xC) = *(u16 *)(q + 0xC) & 0xFFF;
            func_80074590(0x89, 0, 0);
        }
        *(s32 *)(a + 0x2C) -= I16(0x48) << 8;
        if (I16(0x2E) <= 0x2C00) {
            func_80054DAC(t, 0x19, 4);
            I16(0x48) = -0x3800;
            I16(0x4E) = 0x380;
            func_80074590(0x32, -6, 0x37);
            *(s32 *)(a + 0x2C) = 0x2C000000;
            I16(0x4A) = -0x2800;
            I16(0x50) = 0x380;
            a[6]++;
        }
        *(s16 *)(t + 0x2E) = I16(0x2E);
        break;
    case 2:
        I16(0x58) = (W16(0x32) + 0xD3E) * 2;
    case 3:
        for (i = 1; i < a[8]; i++) {
            *(u16 *)(*(u8 **)(a + i * 4 + 0xC0) + 0xC) += I16(0x48) >> 2;
        }
    case 4:
        W16(0x4A) += W16(0x50);
        *(s32 *)(a + 0x30) += I16(0x4A) << 8;
        if (*(s32 *)(a + 0x30) >= (s32)0xF2C20000) {
            func_80074590(0x2F, -0xE, 0);
            I16(0x58) = 0;
            *(s32 *)(a + 0x30) = 0xF2C20000;
            I16(0x4A) = -0x2800;
            I16(0x50) = (-(a[6] << 2) + (a[6] << 5)) << 7;
            a[6]++;
        }
    case 5:
        i = 0;
        *(u16 *)(t + 0x2E) -= 0x10;
        if (*(s16 *)(t + 0x2E) < 0x29FF) {
            *(s16 *)(t + 0x2E) = 0x29FE;
            i = 1;
        }
        W16(0x48) += W16(0x4E);
        if (I16(0x48) >= 0x3000) {
            I16(0x48) = 0x3000;
        }
        *(s32 *)(t + 0x30) += I16(0x48) << 8;
        if (*(s16 *)(t + 0x32) >= -0xC80 - *(s16 *)(t + 0x84)) {
            i++;
        }
        if (a[6] == 5 && i == 2) {
            func_80074590(3, 0, 0);
            func_80054DAC(t, 2, 4);
            *(s16 *)(t + 0x2E) = 0x29FE;
            *(s16 *)(t + 0x32) = -0xC80 - *(s16 *)(t + 0x84);
            a[0x2B] = 0;
            t[0] = 3;
            D_800BF871 = 0;
            D_1F800137 = 0;
            a[5] = 0;
        }
        break;
    }
}

typedef struct { s16 a, b, c, d, e; } PartInit10;
extern PartInit10 D_8012A160[];
extern u8 D_8012A194[];
void func_8011B5C4(u8 *a)
{
    s32 i;
    PartInit10 *t;
    s16 *p;
    s32 rs_k16 = 5;

    switch (a[4]) {
    case 0:
        a[8] = rs_k16;
        if (D_800ED098 < 5) {
            a[4] = 3;
            break;
        }
        a[9] = 5;
        a[0xD] = 0;
        a[0xB] = 0;
        a[4]++;
        for (i = 0; i < a[8]; i++) {
            p = func_8007AAE8();
            *(s16 **)(a + i * 4 + 0xC0) = p;
            p[3] = D_8012A160[i].a;
            p[0] = D_8012A160[i].b;
            p[1] = D_8012A160[i].c;
            p[2] = D_8012A160[i].d;
            p[4] = 0;
            p[5] = 0;
            p[6] = 0;
            func_80051B04(p, 0xC, D_8012A160[i].e);
        }
        a[0] = 1;
        M2C_FIELD(a, s16 *, 0x80) = 0x12C;
        M2C_FIELD(a, s16 *, 0x82) = 0x258;
        M2C_FIELD(a, s16 *, 0x84) = 0xB4;
        M2C_FIELD(a, s16 *, 0x86) = 0x168;
        M2C_FIELD(a, s16 *, 0x58) = 0;
        M2C_FIELD(a, s16 *, 0x56) = 0;
        M2C_FIELD(a, s16 *, 0x54) = 0;
        switch (a[3]) {
        case 0:
            M2C_FIELD(a, s16 *, 0x2E) = 0x38A4;
            M2C_FIELD(a, s16 *, 0x32) = -0xD3E;
            M2C_FIELD(a, s16 *, 0x36) = 0x2D82;
            break;
        case 1:
            if (D_800BF871 == 8) {
                M2C_FIELD(a, s16 *, 0x2E) = 0x38A4;
                a[5] = 2;
            } else {
                M2C_FIELD(a, s16 *, 0x2E) = 0x2C00;
            }
            M2C_FIELD(a, s16 *, 0x32) = -0xD3E;
            M2C_FIELD(a, s16 *, 0x36) = 0x2D82;
            break;
        }
        break;
    case 1:
        switch (a[3]) {
        case 0:
            func_8011AC40(a);
            break;
        case 1:
            switch (a[5]) {
            case 0:
                if (func_8007778C(a) != 0 && a[0x2B] != 0) {
                    a[0x2B] = 0;
                    D_800E7E80[0] = 2;
                    func_80040CDC(a, 0, D_8012A194);
                    a[0x70] = 2;
                    a[6] = 0;
                    a[5]++;
                }
                break;
            case 1:
                a[1] = 1;
                func_80077EBC(a);
                func_8011AEF0(a);
                break;
            case 2:
                a[1] = 1;
                func_80077EBC(a);
                func_8011B1FC(a);
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

void func_8011B5C4();
void func_8011B8AC(s32 arg0, s8 arg1) {
    void *temp_v0;

    temp_v0 = func_8007A980(3, 4, 0);
    M2C_FIELD(temp_v0, s8 *, 2) = 0x25;
    M2C_FIELD(temp_v0, s8 *, 3) = arg1;
    M2C_FIELD(temp_v0, M2C_UNK **, 0x1C) = (M2C_UNK *)func_8011B5C4;
    M2C_FIELD(temp_v0, s32 *, 0x10) = arg0;
}

extern u8 D_800A3CD0[];
extern u8 D_8012A1C8[];
static inline void inl_init(u8 *a)
{
    if (func_80051B70(a, 0xC, 0x3A) == 0) {
        M2C_FIELD(a, s16 *, 0x80) = 0x3C;
        M2C_FIELD(a, s16 *, 0x82) = 0x78;
        M2C_FIELD(a, s16 *, 0x84) = 0x64;
        a[0] = 1;
        M2C_FIELD(a, s16 *, 0x86) = 0xC8;
        a[0x2B] = 0;
        M2C_FIELD(a, s16 *, 0x58) = 0;
        M2C_FIELD(a, s16 *, 0x56) = 0;
        M2C_FIELD(a, s16 *, 0x54) = 0;
        a[4]++;
        func_800517F8(a);
    }
}
static inline void inl_talk(u8 *a)
{
    u8 *b = a;
    a[1] = 1;
    func_80077EBC(a);
    if (a[0x70] == 0xFF) {
        if (a[6] == 0) {
            func_80040D68(a, D_8012A1C8);
            a[0x70] = 2;
            a[6]++;
        } else {
            a[0x2B] = 0;
            a[5] = 0;
        }
    }
    func_80041098(b);
}
void func_8011B904(u8 *a)
{
    switch (a[4]) {
    case 0:
        inl_init(a);
        break;
    case 1:
        if (D_800BFA03 >= 3) {
            a[4] = 3;
            break;
        }
        switch (a[5]) {
        case 0:
            if (func_8007778C(a) != 0 && a[0x2B] != 0) {
                func_80040CDC(a, 0, D_800A3CD0);
                a[0x70] = 2;
                a[6] = 0;
                a[5]++;
            }
            break;
        case 1:
            inl_talk(a);
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

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8011BACC);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8011BC0C);

extern u16 D_8012A208[];
void func_8011BE48(u8 *a) {
    s32 one = 1;
    u16 *p;
    u16 k;

    switch (a[4]) {
    case 0:
        if (func_80051B70(a, 0xC, 0x37) == 0) {
            a[0] = one;
            *(s16 *)(a + 0x80) = 0x64;
            *(s16 *)(a + 0x82) = 0xC8;
            *(s16 *)(a + 0x86) = 0xC8;
            *(s16 *)(a + 0x84) = 0x64;
            a[0x2B] = 0;
            p = &D_8012A208[a[3] * 3];
            *(u16 *)(a + 0x2E) = *p++;
            *(u16 *)(a + 0x32) = *p++;
            k = *p;
            *(s16 *)(a + 0x58) = 0;
            *(s16 *)(a + 0x56) = 0;
            *(s16 *)(a + 0x54) = 0;
            *(s16 *)(a + 0x40) = 0;
            a[4]++;
            *(u16 *)(a + 0x36) = k;
        }
        break;
    case 1:
        if (D_800BF816 == 0) {
            a[4] = 3;
            break;
        }
        func_8011BC0C(a);
        if (func_8007778C(a)) {
            func_800517F8(a);
        }
        break;
    case 2:
    case 3:
        func_8007A624(a);
        break;
    }
}

void func_8011BE48();
u8 *func_8011BF84(u8 *a, s32 b) {
    u8 *p = func_8007A980(1, 4, 0);

    if (p != NULL) {
        M2C_FIELD(p, void **, 0x1C) = func_8011BE48;
        p[2] = 0x28;
        p[3] = b;
        M2C_FIELD(p, u8 **, 0x10) = a;
        p[0x28] |= 0x80;
        return p;
    }
    return NULL;
}

void func_8011BFF4(void *arg0, void *arg1, s16 arg2, s32 arg3) {
    M2C_FIELD(arg0, s16 *, 0x58) = 0;
    M2C_FIELD(arg0, u16 *, 0x2E) = (u16) ((s32) (M2C_FIELD(M2C_FIELD(arg1, void **, 0xD0), s32 *, 0x2C) + M2C_FIELD(M2C_FIELD(arg1, void **, 0xDC), s32 *, 0x2C)) / 2);
    M2C_FIELD(arg0, u16 *, 0x2E) = (u16) (M2C_FIELD(arg0, u16 *, 0x2E) + ((s32) (func_80083F50(M2C_FIELD(arg1, s16 *, 0x56)) * arg2) >> 0xC));
    M2C_FIELD(arg0, u16 *, 0x36) = (u16) ((s32) (M2C_FIELD(M2C_FIELD(arg1, void **, 0xD0), s32 *, 0x34) + M2C_FIELD(M2C_FIELD(arg1, void **, 0xDC), s32 *, 0x34)) / 2);
    M2C_FIELD(arg0, u16 *, 0x36) = (u16) (M2C_FIELD(arg0, u16 *, 0x36) - ((s32) (func_80083E80(M2C_FIELD(arg1, s16 *, 0x56)) * arg2) >> 0xC));
    M2C_FIELD(arg0, s16 *, 0x32) = (s16) (arg3 + ((s32) (M2C_FIELD(M2C_FIELD(arg1, void **, 0xD0), s32 *, 0x30) + M2C_FIELD(M2C_FIELD(arg1, void **, 0xDC), s32 *, 0x30)) / 2));
}

void func_8011C100(u8 *a)
{
    u8 *g;

    switch (a[4]) {
    case 0:
        M2C_FIELD(a, s16 *, 0x5C) = 0;
        M2C_FIELD(a, void **, 0x3C) = D_800ECF80;
        func_80077B38(a, D_80139100, 5);
        a[0xB] = 0x10;
        M2C_FIELD(a, s16 *, 0x68) = 0x79;
        a[0] = 2;
        a[0xD] = 0;
        a[0x47] = 0;
        a[8] = 0;
        M2C_FIELD(a, s16 *, 0x5A) = 0;
        M2C_FIELD(a, s16 *, 0x80) = 0x32;
        M2C_FIELD(a, s16 *, 0x82) = 0x64;
        M2C_FIELD(a, s16 *, 0x84) = 0x32;
        M2C_FIELD(a, s16 *, 0x86) = 0x64;
        func_8004B354(a, 0);
        a[4]++;
        break;
    case 1:
        switch (a[5]) {
        case 0:
            g = D_800BF808_1760;
            if (g[0xE] != 0 && g[0xF] == 3) {
                a[0] = 1;
                a[5]++;
            }
            break;
        case 1:
            if (D_800BF816 == 0) {
                a[0] = 2;
                a[5] = 0;
                break;
            }
            func_8004B374(a, 0);
            a[1] = 1;
            func_80077EBC(a);
            break;
        }
        break;
    case 2:
        func_80040B48(0x4F);
        func_8004A3D4(a);
        a[4]++;
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

extern u8 D_800BF9FA;
#define S32(o) (*(s32 *)(a + (o)))
void f_UpdateFreedCharlesSequence(u8 *a) {
    s32 dx;
    s32 dz;

    switch (a[5]) {
    case 0:
        switch (a[6]) {
        case 0:
            if (D_800BF9FE != 3) {
                break;
            }
            a[0xB] &= 0x3F;
            func_80041768(a, 0x14, 4);
            dx = 0x24B8 - I16(0x2E);
            dz = 0x2134 - I16(0x36);
            I16(0x4A) = -0x2800;
            I16(0x50) = 0x380;
            a[6]++;
            I16(0x48) = ((dx / 24) << 8) + dx % 24;
            I16(0x4C) = ((dz / 24) << 8) + dz % 24;
            break;
        case 1:
            if ((S32(0x2C) += I16(0x48) << 8) < 0x24B9) {
                I16(0x2E) = 0x24B8;
            }
            if ((S32(0x34) += I16(0x4C) << 8) < 0x2135) {
                I16(0x36) = 0x2134;
            }
        case 2:
            W16(0x4A) += W16(0x50);
            S32(0x30) += I16(0x4A) << 8;
            if (I16(0x32) >= -0x744) {
                a[0xB] = (a[0xB] & 0xC0) | 0x40;
                func_80041768(a, 0x58, 4);
                I16(0x32) = -0x744;
                I16(0x4A) = -0x2800;
                I16(0x50) = I16(0x50) * 3;
                a[6]++;
            }
            break;
        case 3:
            D_800BF9FA = 7;
            a[6] = 0;
            a[5]++;
            break;
        }
        break;
    case 1:
        if (D_800BF9FA == 10) {
            a[0x70] = 2;
            a[5]++;
        }
        break;
    case 2:
        if (a[0x70] == 0xFF) {
            a[4] = 3;
        }
        break;
    }
    func_80041098(a);
    func_8004190C(a);
}

extern s32 D_800ECF58[];
extern u8 D_801290E0[];
extern u8 D_80139240_0000[];
extern u8 D_8012A214[];
void func_8011C9C8(u8 *a);
void func_8011CA78(void *arg0);
void func_8011C52C(u8 *a)
{
    s32 v;
    s32 k;

    switch (a[4]) {
    case 0:
        if (a[5] == 0) {
            a[5]++;
            break;
        }
        a[5] = 0;
        if (func_800519E0(a, 0xF, D_800ECF58[0x4C / 4], D_801290E0) != 0) {
            break;
        }
        v = D_800ECF58[0x38 / 4];
        k = a[3];
        a[0xB] = 0x40;
        a[0] = 9;
        M2C_FIELD(a, s16 *, 0x80) = 0xAA;
        M2C_FIELD(a, s16 *, 0x82) = 0x154;
        M2C_FIELD(a, s16 *, 0x84) = 0x80;
        M2C_FIELD(a, s16 *, 0x86) = 0xF0;
        a[0x2B] = 0;
        a[0x29] = 0;
        M2C_FIELD(a, s32 *, 0x3C) = v;
        switch (k) {
        case 0:
            M2C_FIELD(a, s16 *, 0x32) = -0x7A8;
            M2C_FIELD(a, s16 *, 0x56) = 0x600;
            func_80040CDC(a, D_80139240_0000, D_8012A214);
            func_800416A8(a, -1, 0);
            func_80041718(a, 0x58, 0);
            break;
        case 1:
            func_8011C9C8(a);
            break;
        }
        a[0x7B] = 0x29;
        M2C_FIELD(a, s16 *, 0x58) = 0;
        M2C_FIELD(a, s16 *, 0x54) = 0;
        a[4]++;
        break;
    case 1:
        a[1] = 1;
        func_80077E7C(a);
        switch (a[3]) {
        case 0:
            f_UpdateFreedCharlesSequence(a);
            break;
        case 1:
            func_8011CA78(a);
            break;
        }
        func_800518FC(a);
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

extern u8 D_800A3E58[];
extern u8 D_800BFAFD;
extern s16 D_800E7ED6;
extern u8 *D_8012A570;
void func_8011C710(u8 *a) {
    if (a[0x71] == 0xFF) {
        switch (a[0x5E]) {
        case 0:
            if (D_800BFAFD != 0) {
                a[0] = 2;
                a[0x5E] = 2;
                func_80040D68(a, D_8012A570);
            } else {
                a[0x5E] = 1;
                func_80040D68(a, D_800A3E58);
            }
            a[0x70] = 1;
            break;
        case 1:
            a[5] = 0;
            break;
        case 2:
            a[4] = 3;
            break;
        }
    }
    if (a[0x5E] == 2) {
        s32 r = func_80085690(D_1F800164 - F16(a, 0x36), F16(a, 0x2E) - D_1F800160);
        D_800E7ED6 = r & 0xFFF;
    }
}

s32 func_8011C810(u8 *a) {
    u8 *g;
    u8 *p;

    switch (a[6]) {
    case 0:
        *(s16 *)(a + 0x40) = 8;
        a[6]++;
    case 1:
        if (*(u16 *)(*(u8 **)(a + 0x38) + 4) != 0) {
            g = D_800BF808_1760;
            (*(u8 **)(g + 0x3C))[4] = 2;
            func_80074590(8, 6, -0x1E);
            if (--*(s16 *)(a + 0x40) == 0) {
                a[6] = 0;
                return 1;
            }
            a[6]++;
            p = func_8006FDE8(a, 0);
            *(u8 **)(g + 0x3C) = p;
            if (p != NULL) {
                if (*(u16 *)(*(u8 **)(a + 0x38) + 4) == 1) {
                    p[0x5E] = 1;
                } else {
                    p[0x5E] = 4;
                }
            }
        }
        break;
    case 2:
        if (*(u16 *)(*(u8 **)(a + 0x38) + 4) == 0) {
            a[6] = 1;
        }
        break;
    }
    return 0;
}

void func_8011C52C();
u8 *func_8011C94C(s32 arg0, s8 arg1) {
    void *temp_v0;

    temp_v0 = func_8007A980(3, 9, 0);
    M2C_FIELD(temp_v0, s8 *, 2) = 1;
    M2C_FIELD(temp_v0, s8 *, 3) = arg1;
    M2C_FIELD(temp_v0, M2C_UNK **, 0x1C) = (M2C_UNK *)func_8011C52C;
    M2C_FIELD(temp_v0, u8 *, 0x28) = (u8) (M2C_FIELD(temp_v0, u8 *, 0x28) | 0x80);
    return temp_v0;
}

s32 func_8011C9A0(u8 *a) {
    func_801229D4(a, 0);
    D_800BF9EB = 0;
    return 1;
}

extern u8 D_8012A3C0[];
void func_8011C9C8(u8 *a) {
    GameState *g;

    func_80051B04(M2C_FIELD(a, u8 **, 0xD0), 0x13, 0x10);
    func_80051B04(M2C_FIELD(a, u8 **, 0xDC), 0x13, 0x11);
    func_80040CDC(a, D_80139240_0000, D_8012A3C0);
    func_80041718(a, 0x2D, 0);
    M2C_FIELD(a, s16 *, 0x56) = 0xA00;
    func_80126C18(a);
    g = &D_800BF870;
    if (g->pad1[0xAB] == 0) {
        a[0x5E] = 0;
    } else if (g->pad1[0x28C] == 0) {
        a[0x5E] = 1;
    } else {
        a[0x5E] = 2;
    }
}

void func_8011CA78(void *arg0) {
    u8 temp_v1;

    func_80041098();
    func_8004190C(arg0);
    temp_v1 = M2C_FIELD(arg0, u8 *, 5);
    switch (temp_v1) {                              /* irregular */
    case 0:
        func_8011CB20(arg0);
        return;
    case 1:
        f_AdvanceStarvingCharlesDialogue(arg0);
        return;
    case 2:
        func_8011C710(arg0);
        return;
    case 3:
        func_8011CCD0(arg0);
        return;
    }
}

void func_8011CB20(u8 *a) {
    s32 k = a[0x2B];
    u8 *g;
    u8 *p;

    switch (k) {
    case 2:
        g = D_800BF808_1760;
        if ((*(u32 *)D_800BF808_1760 & 0xFFFF0000) != 0x85010000) {
            return;
        }
        p = func_8006FB0C(a, g[3]);
        M2C_FIELD(g, u8 **, 0x3C) = p;
        if (p != NULL) {
            p[0x5E] = 0;
        }
        a[6] = k;
    case 3:
        func_80042354(1, 3);
        func_80040D68(a, D_800A3CD0);
        a[0x70] = 1;
        a[5] = 1;
        break;
    }
}

extern u8 D_8012A508[];
extern u8 D_8012A538[];
extern u8 *D_8012A568[];
void f_AdvanceStarvingCharlesDialogue(u8 *a) {
    s32 k;

    if (a[0x71] == 0xFF) {
        switch (k = a[6]) {
        case 0:
            if (D_800BFAFD != 0) {
                func_80040D68(a, D_8012A508);
                a[6]++;
                break;
            }
        case 1:
            func_80040D68(a, D_8012A568[a[0x5E]]);
            a[5] = 2;
            a[6] = 0;
            break;
        case 2:
            func_80040D68(a, D_8012A538);
            a[5] = 3;
            a[6] = 0;
            a[0x5E] = k;
            break;
        }
        a[0x70] = 1;
    }
}

void func_8011CCD0(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x71) == 0xFF) {
        func_8004D4F4(0x85, 1);
        M2C_FIELD(arg0, s8 *, 0x5E) = 1;
        M2C_FIELD(arg0, s8 *, 5) = 0;
    }
}

extern u8 D_800A3D18_ed09[];
s32 f_RunTabbyHouseResidentConversation(u8 *a) {
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
            t = *(u8 **)(a + 0x14);
            func_80040D68(a, *(void **)(t + 0xC));
            a[0x7A] = t[0x10];
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

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8011CE8C);

void func_8011D390(u8 *a) {
    switch (a[5]) {
    case 0:
        if (func_8007778C(a) != 0) {
            func_80076D68(a);
            if (D_1F800137 == 0) {
                if (!(a[0x2B] & 2)) {
                    a[0] = 3;
                    a[6] = 0;
                    a[5] = 2;
                }
                if (a[0x2B] == 3) {
                    func_80042354(1, 1);
                    a[6] = 0;
                    a[5]++;
                }
            }
        }
        break;
    case 1:
        if (f_RunTabbyHouseResidentConversation(a) != 0) {
            a[5] = 0;
        }
        break;
    case 2:
        if (func_8007778C(a) != 0) {
            func_80076D68(a);
            if ((a[0x2B] & 2) || D_1F800137 != 0) {
                a[0] = 9;
                func_80041768(a, a[0x7B], 8);
                a[5] = 0;
            } else {
                func_8011CE8C(a);
            }
        }
        break;
    }
}

extern u8 D_80129158[];
extern s32 D_8012AD0C[];
extern u8 D_800BFA05;
s32 func_80126C18(u8 *a);
void func_8011D4E8(u8 *a)
{
    s32 *t;
    s32 v;
    u8 *p;
    u8 k;
    s32 i;

    switch (a[4]) {
    case 0:
        t = D_800ECF58;
        M2C_FIELD(a, s32 *, 0x3C) = t[0x38 / 4];
        if (func_800519E0(a, (a[3] & 0x20) ? 0x10 : 0xF, (a[3] & 0x40) ? t[0x54 / 4] : t[0x50 / 4], D_80129158) == 0) {
            a[0xB] = 0x40;
            a[0] = 9;
            M2C_FIELD(a, s16 *, 0x80) = 0xAA;
            M2C_FIELD(a, s16 *, 0x82) = 0x154;
            M2C_FIELD(a, s16 *, 0x84) = 0xC8;
            M2C_FIELD(a, s16 *, 0x58) = 0;
            M2C_FIELD(a, s16 *, 0x54) = 0;
            M2C_FIELD(a, s16 *, 0x86) = 0x168;
            a[0x2B] = 0;
            a[0x29] = 0;
        }
        if (!(a[3] & 0x80)) {
            v = D_8012AD0C[a[3] & 0x1F];
            M2C_FIELD(a, s32 *, 0x1C) = v;
            if (v == 0) {
                func_8007A624(a);
                break;
            }
            M2C_FIELD(a, s16 *, 0x56) = 0;
            break;
        }
        if (M2C_FIELD(a, u8 **, 0x14)[3] != 0xFF) {
            i = a[9] - 1;
            func_80051B04(*(u8 **)(a + (i << 2) + 0xC0), 0x1B, M2C_FIELD(a, u8 **, 0x14)[3]);
        }
        func_80040CDC(a, D_80139240_0000, M2C_FIELD(M2C_FIELD(a, u8 **, 0x14), u8 **, 0xC));
        func_80041718(a, a[0x7B], 0);
        func_80126C18(a);
        a[4]++;
        break;
    case 1:
        if (D_800BFA05 == 2) {
            a[4] = 3;
        }
        if (!(a[0x5F] & 0xF)) {
            switch (a[5]) {
            case 0:
                if (func_8007778C(a) != 0) {
                    func_80076D68(a);
                    if (D_1F800137 == 0 && a[0x2B] == 3) {
                        func_80042354(1, 1);
                        a[6] = 0;
                        a[5]++;
                    }
                }
                break;
            case 1:
                if (f_RunTabbyHouseResidentConversation(a) != 0) {
                    a[5] = 0;
                }
                break;
            }
        } else {
            func_8011D390(a);
        }
        if (a[1] != 0) {
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

extern u8 D_800BF9F9;
extern u8 *D_8012AA68[];
extern u8 *D_8012ACF0[];
static inline s32 tabby_spawn_inl(u8 *owner, u8 *e)
{
    s32 i;
    u8 *p;
    u8 k;

    for (i = 0; e[0] != 0xFF; e += 0x14) {
        p = func_8007A980(3, 9, 0);
        if (p == NULL) {
            return 0;
        }
        if (owner != NULL) {
            p[0x28] |= 0x80;
            *(u8 **)(owner + i * 4 + 0xC) = p;
        }
        *(void **)(p + 0x1C) = func_8011D4E8;
        p[3] = e[1] + (i - 0x80);
        p[2] = 0x15;
        *(s16 *)(p + 0x56) = *(s16 *)(e + 0xA);
        p[0x5F] = e[0];
        *(u8 **)(p + 0x14) = e;
        p[0x7B] = e[2];
        *(s16 *)(p + 0x2E) = *(s16 *)(e + 4);
        *(s16 *)(p + 0x32) = *(s16 *)(e + 6);
        *(s16 *)(p + 0x36) = *(s16 *)(e + 8);
        i++;
    }
    return 1;
}

void f_UpdateTabbyHouseSceneController(u8 *a)
{
    s16 i;
    s32 j;
    u8 *g;
    u8 *h;
    u8 *p;

    switch (a[4]) {
    case 0:
        for (i = 0; i < 0x10; i++) {
            *(u8 **)(a + (i << 2) + 0xC) = NULL;
        }
        if (tabby_spawn_inl(NULL, D_8012AA68[D_800BF9F9]) != 0) {
            a[4]++;
        }
        break;
    case 1:
        switch (a[5]) {
        case 0:
            g = D_800BF808_1760;
            if (g[0xE] != 0 && g[0xF] == 7) {
                if (tabby_spawn_inl(a, D_8012ACF0[D_800BF9F9]) == 0) {
                    break;
                }
                a[5]++;
            }
            h = (u8 *)&D_800BF870;
            switch (h[0x195]) {
            case 1:
                if (D_800BF816 == 0) {
                    h[0x195] = 2;
                }
                break;
            case 2:
                h[0x195] = 0;
                tabby_spawn_inl(NULL, D_8012AA68[h[0x189]]);
                break;
            }
            break;
        case 1:
            if (D_800BF816 == 0) {
                for (j = 0; j < 0x10; j++) {
                    p = *(u8 **)(a + j * 4 + 0xC);
                    if (p != NULL) {
                        p[4] = 3;
                        *(u8 **)(a + j * 4 + 0xC) = NULL;
                    }
                }
                a[5] = 0;
            }
            break;
        }
        break;
    case 2:
    case 3:
        func_8007ADD0(a);
        break;
    }
}

void func_8011DBD8(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 5);
    switch (temp_v1) {                              /* irregular */
    case 0:
        if (func_8007778C(arg0) != 0) {
            func_80076D68(arg0);
            if ((*(u8 *)0x1F800137 == 0) && (M2C_FIELD(arg0, u8 *, 0x2B) == 3)) {
                func_80042354(1, 1);
                M2C_FIELD(arg0, s8 *, 6) = 0;
                M2C_FIELD(arg0, u8 *, 5) = (u8) (M2C_FIELD(arg0, u8 *, 5) + 1);
                return;
            }
        }
        return;
    case 1:
        if (f_RunTabbyHouseResidentConversation(arg0) != 0) {
            M2C_FIELD(arg0, u8 *, 5) = 0U;
        }
        break;
    }
}

void func_8011E2D8(u8 *a);
void func_8011E3A8(void *arg0);
void func_8011DC88(u8 *a)
{
    switch (a[4]) {
    case 0:
        { s32 i = a[9] - 1; func_80051B04(*(u8 **)(a + (i << 2) + 0xC0), 0x1B, 3); }
        func_80040CDC(a, D_80139240_0000, D_800A3CC0);
        if (D_800BF8BE != 0xFF) {
            a[0x5E] = 0xFF;
            func_80041718(a, 1, 0);
        } else {
            a[0x5E] = 0;
            func_80041718(a, 0x21, 0);
        }
        M2C_FIELD(a, s16 *, 0x56) = 0x300;
        M2C_FIELD(a, s16 *, 0x40) = 0x78;
        a[4]++;
        break;
    case 1:
        func_8007778C(a);
        func_80041098(a);
        func_8004190C(a);
        switch (a[5]) {
        case 0:
            func_8011DE1C(a);
            break;
        case 1:
            func_8011E2D8(a);
            break;
        case 2:
            func_8011E3A8(a);
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

extern u8 D_800A3CC0_459e;
u8 *func_80072DDC();
void func_80123470(u8 *);
void func_8011DE1C(u8 *a) {
    u8 *p;

    if (a[0x5E] == 0xFF) {
        return;
    }
    if (a[0x2B] == 3) {
        func_80041768(a, 0x22, 8);
        func_80040D68(a, &D_800A3CC0_459e);
        a[0x70] = 1;
        *(u16 *)(a + 0x40) = 1;
        a[5] = 1;
        a[6] = 0;
        return;
    }
    switch (a[6]) {
    case 0:
        if (*(u16 *)(*(u8 **)(a + 0x38) + 4) != 0) {
            p = func_80072DDC(a, 0, 2, 0x20);
            if (p != NULL) {
                p[0] = 1;
                p[3] = 0;
                *(void **)(p + 0x1C) = func_80123470;
            }
            a[6]++;
        }
        break;
    case 1:
        if (a[0x79] == 1) {
            func_80041768(a, 0x22, 8);
            *(u16 *)(a + 0x40) = (func_8009A450() & 0xFF) + 0x1E;
            a[6]++;
        }
        break;
    case 2:
        if (--*(s16 *)(a + 0x40) < 0) {
            func_80041768(a, 0x21, 8);
            a[6] = 0;
        }
        break;
    }
}

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8011DF98);

extern u8 D_8012AD54[];
extern u8 D_8012AD64[];
extern u8 *D_8012AE64[];
void func_8011E2D8(u8 *a) {
    u8 *g;

    if (a[0x71] != 0xFF) {
        return;
    }
    if (M2C_FIELD(a, s16 *, 0x40) != 0) {
        g = (u8 *)&D_800BF870;
        if (g[0x91] == 0xFF) {
            a[0x5E] = 2;
            func_80040D68(a, D_8012AD54);
        } else if (g[0x28B] != 0) {
            a[0x5E] = 1;
            func_80040D68(a, D_8012AD64);
        } else {
            a[0x5E] = 0;
            func_80040D68(a, D_8012AD54);
        }
        M2C_FIELD(a, s16 *, 0x40) = 0;
    } else {
        func_80040D68(a, D_8012AE64[a[0x5E]]);
        a[5] = 2;
    }
    a[0x70] = 1;
}

void func_8011E3A8(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x71) == 0xFF) {
        M2C_FIELD(arg0, s8 *, 5) = 0;
        M2C_FIELD(arg0, s8 *, 6) = 0;
    }
}

s32 func_8011E3C8(u8 *a) {
    u8 *e = D_800E8008;

    switch (a[0x78]) {
    case 0:
        e[0x76] = 1;
        M2C_FIELD(a, s16 *, 0x40) = 0x5A;
        a[0x78]++;
    case 1:
        if (!(D_1F80017C & 7)) {
            func_80074590(0x86, 0, 0);
        }
        if (--M2C_FIELD(a, s16 *, 0x40) < 0) {
            e[0x76] = 0;
            return 1;
        }
        break;
    }
    return 0;
}

extern u8 D_8012AE70[];
void func_8011E674(u8 *a);
void func_8011E6EC(u8 *a);
void func_8011E76C(void *arg0);
void func_8011E47C(u8 *a)
{
    u8 *g;
    u8 *t;
    u8 k;

    switch (a[4]) {
    case 0:
        func_80051B04(M2C_FIELD(a, u8 **, 0xCC), 0x14, 0xF);
        M2C_FIELD(M2C_FIELD(a, u8 **, 0xD0), s32 *, 0x40) = 0;
        func_80040CDC(a, D_80139240_0000, D_800A3CD0);
        func_80041718(a, 0, 0);
        g = (u8 *)&D_800BF870;
        if (g[0x53] == 0) {
            a[0x5E] = 3;
        } else if (g[0x97] == 0xFF) {
            if (g[0x98] == 0xFF) {
                a[0x5E] = 5;
            } else {
                a[0x5E] = 4;
            }
        } else if (g[0x96] == 0) {
            a[0x5E] = 0;
        } else if (g[0x96] == 0xFF) {
            a[0x5E] = 2;
        } else {
            a[0x5E] = 1;
        }
        t = D_8012AE70;
        M2C_FIELD(a, u8 **, 0x14) = t;
        a[0x5F] = D_8012AE70[0];
        k = t[2];
        a[4]++;
        a[0x7B] = k;
        break;
    case 1:
        a[1] = 1;
        func_80077E7C(a);
        func_80041098(a);
        func_8004190C(a);
        switch (a[5]) {
        case 0:
            func_8011E674(a);
            break;
        case 1:
            func_8011E6EC(a);
            break;
        case 2:
            func_8011E76C(a);
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

extern M2C_UNK D_800A3D18;
void func_8011E674(u8 *a) {
    if (a[0x2B] == 3) {
        func_80040D68(a, &D_800A3D18);
        a[0x70] = 1;
        func_80042354(1, 1);
        a[5] = 1;
    } else if (D_1F800137 == 0) {
        func_8011CE8C(a);
    }
}

extern void *D_8012AEFC[];
void func_8011E6EC(u8 *a) {
    if (a[0x71] == 0xFF) {
        func_80040D68(a, D_8012AEFC[a[0x5E]]);
        if (a[0x5E] == 3) {
            func_80041768(a, 0x13, 4);
        } else {
            func_80041768(a, 0xA, 4);
        }
        a[0x70] = 1;
        a[5] = 2;
    }
}

void func_8011E76C(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x71) == 0xFF) {
        if (M2C_FIELD(arg0, u8 *, 0x5E) == 0) {
            M2C_FIELD(arg0, u8 *, 0x5E) = 1U;
        }
        func_80041768(arg0, 0, 4);
        M2C_FIELD(arg0, s8 *, 5) = 0;
        M2C_FIELD(arg0, s8 *, 6) = 0;
    }
}

extern u8 D_8012AF40[];
extern u8 D_8012B0C8[];
extern u8 D_8012B130[];
extern u8 D_8012B100[];
extern u8 D_8012AF14[];
void func_8011EF70(void *arg0);
void func_8011EFC8(u8 *a);
void func_8011E7C8(u8 *a)
{
    u8 *g;
    u8 *p;
    u8 *t;

    switch (a[4]) {
    case 0:
        g = (u8 *)&D_800BF870;
        switch (g[0x8D]) {
        case 0:
            if (g[0x194] != 0) {
                func_80040CDC(a, D_80139240_0000, D_8012AF40);
                func_80041718(a, 0, 0);
                M2C_FIELD(a, s16 *, 0x2E) = 0xCBA;
                M2C_FIELD(a, s16 *, 0x36) = 0x1388;
                M2C_FIELD(a, s16 *, 0x56) = 0xC00;
                a[0x5E] = 0xFF;
                a[5] = 3;
            } else {
                func_80040CDC(a, D_80139240_0000, D_8012B0C8);
                func_80041718(a, 0x11, 0);
                M2C_FIELD(a, s16 *, 0x56) = 0x800;
                p = func_8006FDE8(a, 1);
                D_800BF844_3cf3 = p;
                if (p != NULL) {
                    p[0x5E] = 2;
                    M2C_FIELD(p, s16 *, 0x60) = 0x40;
                    M2C_FIELD(p, s16 *, 0x62) = 0x20;
                    M2C_FIELD(p, s16 *, 0x56) = M2C_FIELD(a, s16 *, 0x56);
                }
                a[0x5E] = 3;
            }
            break;
        case 1:
            if (g[0x290] != 0) {
                func_80040CDC(a, D_80139240_0000, D_8012B0C8);
                a[0x5E] = 1;
            } else {
                func_80040CDC(a, D_80139240_0000, D_8012B130);
                a[0x5E] = 0;
            }
            func_80041718(a, 0x13, 0);
            break;
        case 0xFF:
            func_80040CDC(a, D_80139240_0000, D_8012B100);
            func_80041718(a, 0, 0);
            a[0x5E] = 2;
            t = D_8012AF14;
            M2C_FIELD(a, u8 **, 0x14) = t;
            a[0x5F] = D_8012AF14[0];
            a[0x7B] = t[2];
            break;
        }
        a[4]++;
        break;
    case 1:
        if (a[0x5E] != 0xFF) {
            a[1] = 1;
            func_80077E7C(a);
        }
        func_80041098(a);
        func_8004190C(a);
        switch (a[5]) {
        case 0:
            func_8011EF70(a);
            break;
        case 1:
            func_8011EFC8(a);
            break;
        case 2:
            func_8011EAD4(a);
            break;
        case 3:
            func_8011ECC8(a);
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

extern u8 D_8012B130_7a52;
extern u8 D_8012B100_e437;
extern u8 D_80139240_1c46;
extern u8 D_8012AF40_c290;
void func_8011EAD4(u8 *a) {
    u8 *e = D_800E8008;
    s32 s;

    if (a[0x71] == 0xFF) {
        s = a[0x5E];
        a[0] = 1;
        switch (s) {
        case 0:
            func_80040D68(a, &D_8012B130_7a52);
            break;
        case 1:
            a[0x5E] = 2;
        case 2:
            func_80041768(a, 0, 8);
            func_80040D68(a, &D_8012B100_e437);
            *(u8 **)(a + 0x14) = D_8012AF14;
            a[0x5F] = D_8012AF14[0];
            a[0x7B] = D_8012AF14[2];
            break;
        case 3:
            a[0x5E] = 0xFF;
            D_800BF870.pad1[0x193]++;
            func_80040CDC(a, &D_80139240_1c46, &D_8012AF40_c290);
            func_80041718(a, 0, 0);
            a[5] = 3;
            a[6] = 0;
            return;
        }
        a[5] = 0;
        a[6] = 0;
    } else if (a[0x71] == 0) {
        a[0x70] = 1;
        a[6]++;
    }
    if (a[0x5E] == 3) {
        switch (a[6]) {
        case 1:
            *(u16 *)(D_800BF844_3cf3 + 0x56) = *(u16 *)(a + 0x56);
            break;
        case 3:
            e[0x64] = 8;
        case 4:
            func_8006CBA8(a + 0x2C);
            {
                s32 r = func_80085690(D_1F800164 - *(s16 *)(a + 0x36), *(s16 *)(a + 0x2E) - D_1F800160);
                D_800E7ED6 = r & 0xFFF;
            }
            break;
        }
    }
}

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8011ECC8);

void func_8011EF70(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x2B) == 3) {
        M2C_FIELD(arg0, s8 *, 0) = 2;
        M2C_FIELD(arg0, s8 *, 0x70) = 1;
        M2C_FIELD(arg0, s8 *, 5) = 1;
        return;
    }
    if (M2C_FIELD(arg0, u8 *, 0x5E) == 2) {
        func_8011CE8C();
    }
}

extern void *D_8012B370[];
void func_8011EFC8(u8 *a)
{
    if (a[0x71] == 0xFF) {
        func_80040D68(a, D_8012B370[a[0x5E]]);
        a[5] = 2;
        a[6] = 0;
        a[0x70] = 1;
    }
}

u8 *func_8006FDE8();
s32 func_8011F028(u8 *a) {
    u8 *e;
    u8 *p;
    u8 one;
    s32 x;
    s32 y;
    s32 z;

    e = func_8006FDE8(a, 2);
    if (e == NULL) {
        return 0;
    }
    one = 1;
    x = 0xD34;
    y = -0x7A1;
    z = 0x17A2;
    *(u8 **)(a + 0x14) = e;
    e[5] = one;
    *(s16 *)(e + 0x2E) = x;
    *(s16 *)(e + 0x32) = y;
    *(s16 *)(e + 0x36) = z;
    *(s16 *)(e + 0x60) = 0;
    p = func_8006FB0C(a, 0x4B);
    if (p == NULL) {
        e[4] = 3;
        *(u8 **)(a + 0x14) = NULL;
        return 0;
    }
    D_800BF844_3cf3 = p;
    p[5] = one;
    *(s16 *)(p + 0x2E) = x;
    *(s16 *)(p + 0x32) = y;
    *(s16 *)(p + 0x36) = z;
    *(s16 *)(p + 0x54) = 0x400;
    *(s16 *)(p + 0x60) = 0;
    p[0x5F] |= 1;
    return 1;
}

s32 func_8011F10C(void *arg0) {
    D_800BF844 = M2C_FIELD(arg0, s32 *, 0x14);
    return 1;
}

extern u8 D_800BF822;
s32 func_8011F120(u8 *a) {
    s32 one;

    switch (a[0x78]) {
    case 0:
        func_8004ED0C(0x93, 4);
        func_8004D650(0x93, 1);
        a[0x78]++;
        break;
    case 1:
        if (D_800BF80E != 0) {
            func_80041768(a, 0x20, 4);
            a[0x78]++;
        }
        break;
    case 2:
        if ((*(u8 **)(a + 0x38))[4] != 0) {
            D_800BF844_3cf3[4] = 2;
            func_800440E4(D_800E7E80, 2, 4);
            a[0x78]++;
        }
        break;
    case 3:
        if (a[0x79] != 1) {
            return 0;
        }
        func_80041768(a, 0, 4);
        a[0x78]++;
        break;
    case 4:
        one = 1;
        if (!(D_800BF822 & one)) {
            return one;
        }
        break;
    }
    return 0;
}

extern u8 D_800BFB47;
extern u8 D_8012B3D4[];
extern u8 D_800A3D18_5587;
extern u8 D_8012B400;
extern u8 D_8012B3E4;
extern u8 D_8012B3DC;
extern u8 D_800A3E58_fde9;
extern u8 D_8012B394;
void func_8011F23C(u8 *a) {
    s32 s = a[5];
    s32 one = 1;

    switch (s) {
    case 0:
        if (!func_8007778C(a)) {
            return;
        }
        func_8004190C(a);
        if (D_1F800137 != 0) {
            return;
        }
        if (!(a[0x2B] & 2) && a[0x5E] != one) {
            a[0] = 3;
            a[6] = 0;
            a[5] = one;
            return;
        }
        if (a[0x2B] == 3) {
            func_80042354(1, 1);
            if (a[0x5E] != 1) {
                func_80040D68(a, &D_800A3D18_5587);
            } else {
                func_80040D68(a, &D_8012B400);
            }
            a[0x70] = 2;
            a[6] = 0;
            a[5] = 2;
        }
        break;
    case 1:
        if (!func_8007778C(a)) {
            return;
        }
        func_80076D68(a);
        if ((a[0x2B] & 2) || D_1F800137 != 0) {
            a[0] = 9;
            func_80041768(a, a[0x7B], 8);
            a[5] = 0;
        } else {
            func_8011CE8C(a);
        }
        break;
    case 2:
        a[1] = one;
        func_80077E7C(a);
        func_8004190C(a);
        if (a[0x70] == 0xFF) {
            switch (a[6]) {
            case 0:
                a[0x7A] = D_8012B3D4[a[0x5E] * 2];
                if (a[0x5E] != 0) {
                    func_80040D68(a, &D_8012B3E4);
                } else {
                    func_80040D68(a, &D_8012B3DC);
                }
                a[0x70] = 2;
                a[6]++;
                break;
            case 1:
                switch (a[0x5E]) {
                case 2:
                    func_80040D68(a, &D_800A3E58_fde9);
                    break;
                case 0:
                    func_80040D68(a, &D_800A3E58_fde9);
                    break;
                case 1:
                    if (D_800BFB47 == 0) {
                        func_80040D68(a, &D_800A3E58_fde9);
                    } else {
                        func_80040D68(a, &D_8012B394);
                        a[0x5E] = 2;
                    }
                    break;
                }
                a[0x70] = 2;
                a[6]++;
                break;
            case 2:
                a[5] = 0;
                break;
            }
        }
        func_80041098(a);
        break;
    }
}

extern u8 D_8012B380[];
void func_8011F504(u8 *a) {
    s32 one = 1;
    u8 *g;
    u8 k;

    switch (a[4]) {
    case 0:
        func_80040CDC(a, D_80139240_0000, D_800A3D18_ed09);
        g = (u8 *)&D_800BF870;
        if (!(*(u16 *)(g + 0x5E6) & 4)) {
            a[0x5E] = 0;
        } else if (g[0xCB] != 0xFF) {
            a[0x5E] = one;
        } else {
            a[0x5E] = 2;
        }
        a[0x7B] = 0;
        func_80041718(a, 0, 0);
        *(s16 *)(a + 0x56) = 0xC02;
        *(u8 **)(a + 0x14) = D_8012B380;
        a[0x5F] = D_8012B380[0];
        k = D_8012B380[2];
        a[4]++;
        a[0x7B] = k;
        break;
    case 1:
        func_8011F23C(a);
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

s32 func_8011F640(u8 *a) {
    u8 *p;

    switch (a[0x78]) {
    case 0:
        p = func_8006FB0C(a, 0x93);
        if (p != NULL) {
            func_800440E4(D_800E7E80, 0xCF, 2);
            D_800BF844_3cf3 = p;
            M2C_FIELD(p, s16 *, 0x60) = -0x10;
            p[0x5E] = 0;
            a[0x78]++;
        }
        break;
    case 1:
        if (D_800BF80E != 0) {
            return 1;
        }
        break;
    }
    return 0;
}

extern u8 D_8012B430[];
extern u8 D_8012B450[];
extern u8 D_8012B460[];
extern u8 D_8012B470[];
void func_8011F6EC(u8 *a) {
    u8 *g;

    switch (a[5]) {
    case 0:
        if (func_8007778C(a) == 0 || D_1F800137 != 0) {
            return;
        }
        if (a[0x2B] == 3) {
            a[0] = a[0x2B];
            func_80042354(1, 1);
            func_80040D68(a, D_800A3D18_ed09);
            a[0x70] = 2;
            a[6] = 0;
            a[5]++;
        }
        break;
    case 1:
        a[1] = 1;
        func_80077E7C(a);
        if (a[0x70] == 0xFF) {
            switch (a[6]) {
            case 0:
                switch (D_800BF9F9) {
                case 1:
                case 2:
                case 3:
                    g = (u8 *)&D_800BF870;
                    if (!(g[0x191] & 1)) {
                        g[0x191] |= 1;
                        func_80040D68(a, D_8012B430);
                    } else {
                        func_80040D68(a, D_8012B450);
                    }
                    break;
                case 4:
                case 5:
                    func_80040D68(a, D_8012B460);
                    break;
                case 6:
                default:
                    func_80040D68(a, D_8012B470);
                    break;
                }
                a[0x70] = 2;
                a[6]++;
                break;
            case 1:
                *(u16 *)(a + 0x40) = 0x10;
                a[6]++;
                break;
            case 2:
                if (--*(s16 *)(a + 0x40) == 0) {
                    a[0] = 9;
                    a[5] = 0;
                }
                break;
            }
        }
        break;
    }
    func_80041098(a);
    func_8004190C(a);
}

extern M2C_UNK D_80139240;
void func_8011F8E0(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 4);
    switch (temp_v1) {                              /* irregular */
    case 0:
        func_80040CDC(arg0, &D_80139240, &D_800A3D18);
        func_80041718(arg0, 0, 0);
        M2C_FIELD(arg0, s8 *, 0x7B) = 0;
        M2C_FIELD(arg0, s16 *, 0x56) = 0xC00;
        M2C_FIELD(arg0, u8 *, 4) = (u8) (M2C_FIELD(arg0, u8 *, 4) + 1);
        return;
    case 1:
        func_8011F6EC(arg0);
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

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8011F9B4);

void func_8011D4E8();
void *func_8011FFFC(void) {
    void *temp_v0;

    temp_v0 = func_8007A980(3, 9, 0);
    M2C_FIELD(temp_v0, s8 *, 2) = 0x15;
    M2C_FIELD(temp_v0, s8 *, 3) = 7;
    M2C_FIELD(temp_v0, M2C_UNK **, 0x1C) = (M2C_UNK *)func_8011D4E8;
    M2C_FIELD(temp_v0, s16 *, 0x2E) = 0x38A4;
    M2C_FIELD(temp_v0, s16 *, 0x32) = -0xD0C;
    M2C_FIELD(temp_v0, s16 *, 0x36) = 0x2D8A;
    M2C_FIELD(temp_v0, s32 *, 0x14) = func_801150EC(temp_v0);
    return temp_v0;
}

extern M2C_UNK D_8012B490;
extern M2C_UNK D_80139240;
void func_80120070(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 4);
    switch (temp_v1) {                              /* irregular */
    case 0:
        func_80040CDC(arg0, &D_80139240, &D_8012B490);
        func_80041718(arg0, 0x10, 0);
        M2C_FIELD(arg0, s8 *, 0x7B) = 0;
        M2C_FIELD(arg0, s16 *, 0x56) = 0x800;
        M2C_FIELD(arg0, u8 *, 4) = (u8) (M2C_FIELD(arg0, u8 *, 4) + 1);
        return;
    case 1:
        func_8011F9B4(arg0);
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

extern u8 D_800BF8C1;
#define ANIM_START(a, anim) ({ s32 _r; if (func_8007778C(a) && (a)[0x2B] == 3) { func_80040D68(a, anim); (a)[0x70] = 2; _r = 1; } else { _r = 0; } _r; })
extern u8 D_8012B4E0;
void func_80120144(u8 *a) {
    switch (a[5]) {
    case 0:
        if (!func_8007778C(a)) {
            return;
        }
        func_8004190C(a);
        if (D_1F800137 != 0) {
            return;
        }
        if (a[0x2B] == 3) {
            a[0] = 3;
            func_80042354(1, 1);
            func_80040D68(a, &D_800A3D18_5587);
            a[0x70] = 2;
            a[6] = 0;
            a[5]++;
        }
        break;
    case 1:
        a[1] = 1;
        func_80077E7C(a);
        func_8004190C(a);
        if (a[0x70] == 0xFF) {
            switch (a[6]) {
            case 0:
                if (D_800BF901 != 0) {
                    if (D_800BF901 == 0xFF) {
                        a[0x7A] = 0xC;
                    } else {
                        a[0x7A] = 0xB;
                    }
                }
                func_80040D68(a, &D_8012B4E0);
                a[0x70] = 2;
                a[6]++;
                break;
            case 1:
                *(u16 *)(a + 0x40) = 0x10;
                a[6]++;
                break;
            case 2:
                if (--*(s16 *)(a + 0x40) == 0) {
                    a[0] = 9;
                    a[5] = 0;
                }
                break;
            }
        }
        break;
    }
    func_80041098(a);
}

void func_801202DC(u8 *a)
{
    s32 i;

    switch (a[4]) {
    case 0:
        func_80040CDC(a, D_80139240_0000, D_800A3D18_ed09);
        i = a[9] - 1;
        func_80051B04(*(u8 **)(a + (i << 2) + 0xC0), 0x1B, 4);
        func_80041718(a, 1, 0);
        if (D_800BF8BE == 0xFF) {
            a[0x7A] = 10;
        } else {
            a[0x7A] = 9;
        }
        a[0x7B] = 1;
        M2C_FIELD(a, s16 *, 0x56) = 0x400;
        a[4]++;
        break;
    case 1:
        func_80120144(a);
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

extern u8 D_8012B504[];
void func_80120564(u8 *a);
void func_80120610(u8 *a);
void func_8012067C(u8 *a);
void func_801203F0(u8 *a)
{
    switch (a[4]) {
    case 0:
        func_80040CDC(a, D_80139240_0000, D_8012B504);
        func_80041718(a, 0, 0);
        if (D_800BF901 < 2) {
            a[0x5E] = 0;
        } else if (D_800BF901 == 0xFF) {
            a[0x5E] = 2;
        } else {
            a[0x5E] = 1;
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
            func_80120564(a);
            break;
        case 1:
            func_80120610(a);
            break;
        case 2:
            func_8012067C(a);
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

extern u8 D_8012B5C8[];
void func_80120564(u8 *a) {
    GameState *g;
    u8 s;

    if (a[0x2B] == 3) {
        func_80040D68(a, D_8012B504);
        a[0x70] = 1;
        func_80041768(a, 0, 8);
        func_80042354(1, 1);
        a[5] = 1;
    } else {
        g = &D_800BF870;
        s = g->pad1[0x19A];
        if (s == 2) {
            g->pad1[0x19A] = 0;
            func_80040D68(a, D_8012B5C8);
            a[0x70] = 1;
            a[0x5E] = 3;
            a[5] = s;
        }
    }
}

void func_80120610(u8 *a) {
    if (a[0x71] == 0xFF) {
        func_80040D68(a, D_8012B5BC[a[0x5E]]);
        func_80041768(a, 10, 4);
        a[0x70] = 1;
        a[5] = 2;
    }
}

void func_8012067C(u8 *a) {
    if (a[0x71] == 0xFF) {
        switch (a[0x5E]) {
        case 0:
            D_800BF870.pad1[0x90]++;
            a[0x5E]++;
            break;
        case 3:
            a[4] = 3;
            return;
        }
        func_80041768(a, 0, 4);
        a[5] = 0;
        a[6] = 0;
    }
}

#define ANIM_START(a, anim) ({ s32 _r; if (func_8007778C(a) && (a)[0x2B] == 3) { func_80040D68(a, anim); (a)[0x70] = 2; _r = 1; } else { _r = 0; } _r; })
extern u8 D_800A3D08;
extern u8 D_8012B670;
void func_80120718(u8 *a) {
    switch (a[5]) {
    case 0:
        if (D_800BF8C1 == 0xFF) {
            a[4] = 3;
            return;
        }
        if (ANIM_START(a, &D_800A3D08)) {
            a[6] = 0;
            a[5]++;
        }
        break;
    case 1:
        if (a[0x70] == 0xFF) {
            if (a[6] == 0) {
                func_80040D68(a, &D_8012B670);
                a[0x70] = 2;
                a[6]++;
            } else {
                a[5] = 0;
            }
        }
        a[1] = 1;
        func_80077E7C(a);
        break;
    }
    if (a[1] != 0) {
        func_80041098(a);
        func_8004190C(a);
    }
}

extern u8 D_800A3CF0;
extern u8 D_8012B688;
extern u8 D_8012B7E0;
extern u8 D_8012B8A8;
extern u8 D_8012B918;
s32 func_80126C18(u8 *a);
void func_80120848(u8 *a) {
    switch (a[5]) {
    case 0:
        if (D_1F800137 == 0) {
            D_800BF870.pad1[0x190] |= 2;
            func_80042354(1, 1);
            func_80040D68(a, &D_800A3CF0);
            a[0x70] = 2;
            a[6] = 0;
            a[5]++;
        }
        break;
    case 1:
        if (a[6] >= 2) {
            a[1] = 1;
            func_80077E7C(a);
        }
        if (a[0x70] == 0xFF) {
            switch (a[6]) {
            case 0:
                func_80040D68(a, &D_8012B688);
                break;
            case 1:
                *(s16 *)(a + 0x2E) = 0x2C24;
                *(s16 *)(a + 0x32) = -0x1011;
                *(s16 *)(a + 0x36) = 0x2648;
                *(s16 *)(a + 0x56) = 0;
                func_80126C18(a);
                func_80040D68(a, &D_8012B7E0);
                break;
            case 2:
                if (D_800BF8C0 == 0xFF) {
                    *(s16 *)(a + 0x80) = 0x5A;
                    *(s16 *)(a + 0x82) = 0xB4;
                    func_80040D68(a, &D_8012B8A8);
                } else {
                    func_80040D68(a, &D_8012B918);
                }
                break;
            case 3:
                if (D_800BF8C0 == 0xFF) {
                    a[4] = 2;
                } else {
                    a[0xBF] = 1;
                    a[5] = 0;
                }
                break;
            }
            a[0x70] = 2;
            a[6]++;
        }
        break;
    }
    func_80041098(a);
    func_8004190C(a);
}

extern u8 D_8012B650;
extern u8 D_8012B944;
extern u8 D_8012B994;
static inline s32 func_80120A3C_start(u8 *a) {
    if (func_8007778C(a) && a[0x2B] == 3) {
        func_80040D68(a, &D_8012B650);
        a[0x70] = 2;
        return 1;
    }
    return 0;
}
void func_80120A3C(u8 *a) {
    switch (a[5]) {
    case 0:
        if (func_80120A3C_start(a)) {
            func_80042354(1, 3);
            a[6] = 0;
            a[5]++;
        }
        break;
    case 1:
        if (a[0x70] == 0xFF) {
            switch (a[6]) {
            case 0:
                if (D_800BF8C0 == 0xFF) {
                    func_80040D68(a, &D_8012B944);
                } else {
                    func_80040D68(a, &D_8012B994);
                }
                a[0x70] = 2;
                a[6]++;
                break;
            case 1:
                if (D_800BF8C0 == 0xFF) {
                    *(s16 *)(a + 0x80) = 0x5A;
                    a[0xBF] = 0;
                    *(s16 *)(a + 0x82) = 0xB4;
                    func_80040D68(a, &D_8012B8A8);
                    a[0x70] = 2;
                    a[6] = 3;
                    a[5] = 1;
                } else {
                    a[5] = 0;
                }
                break;
            }
        }
        a[1] = 1;
        func_80077E7C(a);
        break;
    }
    if (a[1] != 0) {
        func_80041098(a);
        func_8004190C(a);
    }
}

extern u8 D_8012B9F8;
void func_80120BE0(u8 *a) {
    switch (a[5]) {
    case 0:
        if (ANIM_START(a, &D_8012B650)) {
            func_80042354(1, 3);
            a[5]++;
        }
        break;
    case 1:
        if (a[0x70] == 0xFF) {
            func_80040D68(a, &D_8012B9F8);
            a[0x70] = 2;
            a[5]++;
        }
        a[1] = 1;
        func_80077E7C(a);
        break;
    case 2:
        if (a[0x70] == 0xFF) {
            a[4] = 2;
        }
        a[1] = 1;
        func_80077E7C(a);
        break;
    }
    if (a[1] != 0) {
        func_80041098(a);
        func_8004190C(a);
    }
}

extern u8 D_800E807E;
s32 func_80120D1C(u8 *a) {
    s16 v[6];
    s32 i;
    s32 r;
    s32 k;

    switch (a[0x78]) {
    case 0:
        if (*(u16 *)(*(u8 **)(a + 0x38) + 4) == 0) {
            break;
        }
        D_800E807E = 1;
        func_80074590(0x80, -8, 0x1E);
        D_800BFA03 = 3;
        *(s16 *)(a + 0x72) = 0;
        a[0x78]++;
        break;
    case 1:
        if ((*(u16 *)(a + 0x72))++ & 1) {
            break;
        }
        v[1] = 0x2E6E;
        v[3] = -0xC80;
        v[5] = 0x2D7E;
        i = (func_8009A450() + 2) & 3;
        k = 0x100;
        while (--i != -1) {
            r = func_8009A450() & 0xFF;
            r = r * r / k;
            if (func_8009A450() & 1) {
                r = -r;
            }
            v[1] += r;
            r = func_8009A450() & 0xFF;
            r = r * r / k;
            if (func_8009A450() & 1) {
                r = -r;
            }
            v[5] += r;
            v[3] -= func_8009A450() & 0x1F;
            func_8003116C(0, v, -0x1E);
        }
        if (*(s16 *)(a + 0x72) < 0x18) {
            break;
        }
        D_800E807E = 0;
        a[0x78]++;
        break;
    case 2:
        if (D_800BFA03 == 4) {
            return 1;
        }
        break;
    }
    return 0;
}

extern u8 D_8012BBFC;
extern u8 D_8012BCD4;
extern u8 D_8012BD54;
extern u8 D_8012BD74;
extern u8 D_8012BDC4;
extern u8 D_8012BE74;
void func_8011B8AC(s32 arg0, s8 arg1);
void *func_8011FFFC(void);
extern u8 *D_1F800214;
static inline void func_80120F70_aim(u8 *a, u8 *e, s32 z, s32 x) {
    u8 *o = D_1F800214;

    func_80041438(a, (s16)func_80085690(*(s16 *)(a + 0x36) - z, x - *(s16 *)(a + 0x2E)), 0x120);
    func_80041438(o, (s16)func_80085690(*(s16 *)(o + 0x36) - z, x - *(s16 *)(o + 0x2E)), 0x120);
    func_80041438(e, (s16)func_80085690(*(s16 *)(e + 0x36) - z, x - *(s16 *)(e + 0x2E)), 0x120);
}
void func_80120F70(u8 *a) {
    u8 *e = D_800E7E80;
    u8 *q;

    switch (a[5]) {
    case 0:
        if (ANIM_START(a, &D_800A3CC0_459e)) {
            a[6] = 0;
            a[5]++;
        }
        break;
    case 1:
        if (a[0x70] == 0xFF) {
            switch (a[6]) {
            case 0:
                func_80040D68(a, &D_8012BBFC);
                a[0x70] = 2;
                break;
            case 1:
                *(s16 *)(e + 0x2E) = 0x2C24;
                *(s16 *)(e + 0x32) = -0xD0C;
                *(s16 *)(e + 0x36) = 0x2EE0;
                *(u8 **)(a + 0x14) = ((u8 *(*)(u8 *, s32))func_8011B8AC)(a, 0);
                func_80040D68(a, &D_8012BCD4);
                a[0x70] = 2;
                break;
            case 2:
                *(u8 **)(a + 0x14) = ((u8 *(*)(u8 *))func_8011FFFC)(a);
                func_80040D68(a, &D_8012BD54);
                a[0x70] = 2;
                break;
            case 3:
                func_80040D68(a, &D_8012BD74);
                a[0x70] = 2;
                break;
            case 4:
                func_80040D68(a, &D_8012BDC4);
                a[0x70] = 2;
                break;
            case 5:
                *(s16 *)(a + 0x80) = 0x1E;
                *(s16 *)(a + 0x82) = 0x3C;
                func_80040D68(a, &D_8012BE74);
                a[0x70] = 2;
                break;
            case 6:
                a[4] = 3;
                break;
            }
            a[6]++;
        } else {
            switch (a[6]) {
            case 2:
            case 3:
                q = *(u8 **)(a + 0x14);
                func_80120F70_aim(a, e, *(s16 *)(q + 0x36), *(s16 *)(q + 0x2E));
                break;
            case 5:
                if (D_800BFA03 < 0xD) {
                    q = *(u8 **)(*(u8 **)(a + 0x14) + 0x10);
                    func_80120F70_aim(a, e, *(s16 *)(q + 0x30), *(s16 *)(q + 0x2C));
                }
                break;
            }
        }
        a[1] = 1;
        func_80077E7C(a);
        break;
    }
    if (a[1] != 0) {
        func_80041098(a);
        func_8004190C(a);
    }
}

extern u8 D_8012BFA4;
void func_80121268(u8 *a) {
    switch (a[5]) {
    case 0:
        if (ANIM_START(a, &D_800A3D08)) {
            a[6] = 0;
            a[5]++;
        }
        break;
    case 1:
        if (a[0x70] == 0xFF) {
            if (a[6] == 0) {
                if (D_800BF870.pad1[0x57] == 0) {
                    a[0x7A] = 0x1C;
                } else if (D_800BF870.pad1[0x56] != 0xFF) {
                    a[0x7A] = 0x1D;
                } else {
                    a[0x7A] = 0x20;
                }
                func_80040D68(a, &D_8012BFA4);
                a[0x70] = 2;
                a[6]++;
            } else {
                a[5] = 0;
            }
        }
        a[1] = 1;
        func_80077E7C(a);
        break;
    }
    if (a[1] != 0) {
        func_80041098(a);
        func_8004190C(a);
    }
}

extern u8 D_80129258[];
s32 func_80126C18(u8 *a);
void f_UpdateGranActor(u8 *a)
{
    switch (a[4]) {
    case 0:
        if (a[5] == 0) {
            a[5]++;
            break;
        }
        a[5] = 0;
        if (func_800519E0(a, 0xF, D_800ECF58[0x5C / 4], D_80129258) != 0) {
            break;
        }
        M2C_FIELD(a, s32 *, 0x3C) = D_800ECF58[0x38 / 4];
        func_80040CDC(a, D_80139240_0000, D_800A3D18_ed09);
        a[0x7B] = 4;
        func_80041718(a, 4, 0);
        a[0xB] = 0x40;
        a[0] = 9;
        M2C_FIELD(a, s16 *, 0x80) = 0xAA;
        M2C_FIELD(a, s16 *, 0x82) = 0x154;
        M2C_FIELD(a, s16 *, 0x84) = 0xE0;
        M2C_FIELD(a, s16 *, 0x58) = 0;
        M2C_FIELD(a, s16 *, 0x54) = 0;
        M2C_FIELD(a, s16 *, 0x86) = 0x180;
        a[0x2B] = 0;
        a[0x29] = 0;
        switch (a[3]) {
        case 0:
            M2C_FIELD(a, s16 *, 0x56) = 0x400;
            break;
        case 1:
            M2C_FIELD(a, s16 *, 0x56) = 0;
            switch (D_800BF9FA) {
            case 0:
                a[0xBF] = 0;
                break;
            case 1:
                a[0xBF] = 1;
                break;
            }
            func_8011BF84(a, 0);
            break;
        case 2:
            M2C_FIELD(a, s16 *, 0x56) = 0;
            func_8011BF84(a, 1);
            break;
        case 3:
            M2C_FIELD(a, s16 *, 0x56) = 0x400;
            func_80041718(a, 0xF, 0);
            a[0x7B] = 0;
            break;
        case 4:
            M2C_FIELD(a, s16 *, 0x56) = 0xC00;
            break;
        }
        func_80126C18(a);
        a[5] = 0;
        a[4]++;
        break;
    case 1:
        switch (a[3]) {
        case 0:
            func_80120718(a);
            break;
        case 1:
            switch (a[0xBF]) {
            case 0:
                func_80120848(a);
                break;
            case 1:
                func_80120A3C(a);
                break;
            }
            break;
        case 2:
            func_80120BE0(a);
            break;
        case 3:
            func_80120F70(a);
            break;
        case 4:
            func_80121268(a);
            break;
        }
        if (a[1] != 0) {
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

s32 func_8012167C(void) {
    u8 *p = PLAYER;

    M2C_FIELD(p, s16 *, 0x58) += 0x190;
    if (M2C_FIELD(p, s16 *, 0x58) >= 0xC00) {
        M2C_FIELD(p, s16 *, 0x58) = 0xC00;
        return 1;
    }
    return 0;
}

s32 func_801216C0(void *arg0) {
    void *temp_v1;

    temp_v1 = M2C_FIELD(arg0, void **, 0x14);
    M2C_FIELD(temp_v1, u16 *, 0x50) = (u16) (M2C_FIELD(temp_v1, u16 *, 0x50) - 0x96);
    return 1;
}

extern s8 D_1F8000F2[];
extern void *D_800BF844_5c02;
s32 func_801216E0(s32 arg0) {
    u8 temp_v1;
    void *temp_a0;
    void *temp_v0;

    temp_v1 = M2C_FIELD(arg0, u8 *, 0x78);
    switch (temp_v1) {                              /* irregular */
    case 0:
        temp_v0 = func_8006FB0C(arg0, 0x17);
        M2C_FIELD(arg0, void **, 0x14) = temp_v0;
        D_800BF844_5c02 = temp_v0;
        temp_a0 = M2C_FIELD(arg0, void **, 0x14);
        if (temp_a0 != NULL) {
            M2C_FIELD(temp_a0, s16 *, 0x60) = 0x60;
            M2C_FIELD(temp_a0, s16 *, 0x62) = 0x78;
            M2C_FIELD(temp_a0, s8 *, 0x5E) = 1;
            M2C_FIELD(temp_a0, u8 *, 0x5F) = (u8) (M2C_FIELD(temp_a0, u8 *, 0x5F) | 1);
            M2C_FIELD(arg0, u8 *, 0x78) = (u8) (M2C_FIELD(arg0, u8 *, 0x78) + 1);
        }
        return 0;
    case 1:
        M2C_FIELD(M2C_FIELD(arg0, void **, 0x14), s16 *, 0x56) = (s16) (-(s32) *((u16 *)D_1F8000F2) & 0xFFF);
        return 1;
    default:
        return 0;
    }
}

extern s32 D_800ECF90;
extern s32 D_800ECFB8;
extern s32 D_800ECFBC;
extern s32 D_800ECFC0;
extern u8 D_800BF90E;
extern u8 D_801292D0[];
extern u8 D_801293C8[];
void func_801217A0(u8 *a) {
    s32 r;

    *(s32 *)(a + 0x3C) = D_800ECF90;
    if (a[3] == 1) {
        if (D_800BF90E != 0xFF) {
            a[0x5E] = 3;
        } else {
            a[0x5E] = 5;
        }
        if (func_800519E0(a, 0xF, D_800ECFB8, D_801292D0) != 0) {
            return;
        }
        func_80040CDC(a, D_80139240_0000, D_800A3CD0);
        func_80041718(a, 0, 0);
        *(s16 *)(a + 0x56) = 0x600;
    } else {
        if (D_800BF870.pad1[0x9D] == 0xFF) {
            a[0x5E] = 4;
        } else if (D_800BF870.pad1[0x9E] == 0xFF) {
            a[0x5E] = 2;
        } else if (D_800BF870.pad1[0x9D] != 0) {
            a[0x5E] = 1;
        } else {
            a[0x5E] = 0;
        }
        if (a[0x5E] < 2) {
            r = func_800519E0(a, 0xF, D_800ECFC0, D_801293C8);
        } else {
            r = func_800519E0(a, 0xF, D_800ECFBC, D_801293C8);
        }
        if (r != 0) {
            return;
        }
        func_80040CDC(a, D_80139240_0000, D_800A3CD0);
        func_80041718(a, 0x23, 0);
        *(s16 *)(a + 0x56) = 0;
    }
    a[0xB] = 0x40;
    a[0] = 9;
    *(s16 *)(a + 0x54) = 0;
    *(s16 *)(a + 0x58) = 0;
    *(s16 *)(a + 0x80) = 0x78;
    *(s16 *)(a + 0x82) = 0xF0;
    *(s16 *)(a + 0x84) = 0x78;
    *(s16 *)(a + 0x86) = 0xF0;
    a[0x2B] = 0;
    a[0x29] = 0;
    a[4]++;
}

extern void *D_8012C248[];
extern u8 D_800BF9DA;
extern u8 D_8012BFC8[];
void func_80121948(u8 *a) {
    u8 *g;

    if (a[0x2B] == 3) {
        switch (a[0x5E]) {
        case 2:
            D_800BF9DA = 1;
        case 0:
            func_80040D68(a, D_8012BFC8);
            a[0x70] = 1;
            a[5] = 1;
            break;
        case 1:
        case 4:
        case 5:
            func_80040D68(a, D_800A3CC0);
            a[0x70] = 1;
            a[5] = 1;
            break;
        case 3:
            func_80040D68(a, D_8012C248[a[0x5E]]);
            a[0x70] = 1;
            a[5] = 2;
            D_800BF9DA = 2;
            break;
        default:
            a[0x70] = 1;
            a[5] = 1;
            break;
        }
    } else {
        g = (u8 *)&D_800BF870;
        if (g[0x16A] == 1) {
            func_80040D68(a, D_8012C248[a[0x5E]]);
            a[0x70] = 1;
            a[5] = 2;
            g[0x16A] = 2;
        } else if (g[0x16A] == 2) {
            func_80040D68(a, D_8012BFC8);
            a[0x70] = 1;
            a[5] = 1;
        }
    }
}

void func_80121BB4(u8 *a);
void func_80121C10(u8 *a);
void func_80121AA4(u8 *a) {
    switch (a[4]) {
    case 0:
        func_801217A0(a);
        break;
    case 1:
        a[1] = 1;
        func_80077E7C(a);
        func_80041098(a);
        func_8004190C(a);
        switch (a[5]) {
        case 0:
            func_80121948(a);
            break;
        case 1:
            func_80121BB4(a);
            break;
        case 2:
            func_80121C10(a);
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

void func_80121BB4(u8 *a)
{
    if (a[0x71] == 0xFF) {
        func_80040D68(a, D_8012C248[a[0x5E]]);
        a[0x70] = 1;
        a[5] = 2;
    }
}

void func_80121C10(u8 *a) {
    if (a[0x71] == 0xFF) {
        switch (a[0x5E]) {
        case 3:
            D_800BF9DA = 0;
        case 2:
            a[0x5E] += 2;
            break;
        case 0:
            a[0x5E] = 1;
            break;
        }
        a[5] = 0;
    }
}

extern u8 D_801291D8[];
extern u8 D_8012C278;
void func_80121C74(u8 *a) {
    if (func_800519E0(a, 0x10, D_800ECF58[0x58 / 4], D_801291D8) == 0) {
        { s32 i = a[9] - 1; func_80051B04(*(u8 **)(a + (i << 2) + 0xC0), 0x1B, 5); }
        *(s32 *)(a + 0x3C) = D_800ECF58[0x38 / 4];
        func_80040CDC(a, D_80139240_0000, &D_8012C278);
        func_80041718(a, 3, 0);
        *(s16 *)(a + 0x56) = 0x800;
        a[0] = 9;
        *(s16 *)(a + 0x80) = 0xAA;
        *(s16 *)(a + 0x82) = 0x154;
        *(s16 *)(a + 0x84) = 0x78;
        *(s16 *)(a + 0x86) = 0xF0;
        *(s16 *)(a + 0x54) = 0;
        *(s16 *)(a + 0x58) = 0;
        a[0xB] = 0;
        a[0x2B] = 0;
        a[0x29] = 0;
        *(s16 *)(a + 0x40) = 0x1E;
        a[4]++;
        if (D_800BF870.pad1[0x94] == 0xFF) {
            a[0x5E] = 3;
        } else if (D_800BF870.pad1[0x1AD] != 0) {
            a[0x5E] = 1;
        } else {
            a[0x5E] = 0;
        }
    }
}

extern u8 D_8012C298;
s32 func_801222DC(u8 *a);
u8 *func_8006FB0C();
void func_80121DA4(u8 *a) {
    u8 *g;
    u8 *p;

    switch (a[0x2B]) {
    case 2:
        g = D_800BF808_1760;
        if (g[2] == 1 && func_801222DC(a)) {
            p = func_8006FB0C(a, g[3]);
            *(u8 **)(g + 0x3C) = p;
            if (p != NULL) {
                p[0x5E] = 0;
            }
            func_80040D68(a, &D_8012C298);
    case 3:
            *(s16 *)(a + 0x80) = 0;
            *(s16 *)(a + 0x82) = 0;
            a[0x70] = 1;
            a[5] = 1;
            return;
        }
    default:
        if (--*(s16 *)(a + 0x40) == 0) {
            switch (a[6]) {
            case 0:
                func_80041768(a, 0x17, 0xC);
                a[6]++;
                break;
            case 1:
                func_80041768(a, 3, 0xC);
                a[6] = 0;
                break;
            }
            *(s16 *)(a + 0x40) = (func_8009A450() & 0xFF) + 0x1E;
        }
    }
}

extern u8 D_800BFA1E;
void func_801221EC(void *arg0);
void func_80122264(void *arg0);
void func_80121ED8(u8 *a) {
    if (a[0x71] == 0xFF) {
        switch (a[0x5E]) {
        case 0:
            D_800BFA1E = 1;
        case 2:
            a[0x5E]++;
            break;
        case 1:
        case 3:
            break;
        default:
            func_8004D4F4(*(s16 *)(a + 0x60), 1);
            if (D_800BF870.pad1[0x94] == 0xFF) {
                a[0x5E] = 3;
            } else {
                D_800BF870.pad1[0x1AD] = 1;
                a[0x5E] = 1;
            }
            break;
        }
        func_80040D68(a, &D_8012C278);
        *(s16 *)(a + 0x80) = 0xAA;
        *(s16 *)(a + 0x82) = 0x154;
        a[5] = 0;
        a[6] = 0;
    } else if (a[0x71] == 0) {
        a[0x70] = 1;
        a[6]++;
    }
    switch (a[0x5E]) {
    case 0:
        if (a[6] == 0) {
            func_801221EC(a);
        }
        break;
    case 2:
        if (a[6] == 1) {
            func_80122264(a);
        }
        break;
    }
}

void func_80122030(u8 *a) {
    switch (a[4]) {
    case 0:
        func_80121C74(a);
        break;
    case 1:
        a[1] = 1;
        func_80077E7C(a);
        func_80041098(a);
        func_8004190C(a);
        switch (a[5]) {
        case 0:
            func_80121DA4(a);
            break;
        case 1:
            func_80122140(a);
            break;
        case 2:
            func_80121ED8(a);
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

void func_80122140(u8 *a) {
    if (a[0x71] == 0xFF) {
        func_80040D68(a, D_8012C580[a[0x5E]]);
        a[0x70] = 1;
        M2C_FIELD(a, s16 *, 0x40) = 1;
        a[5] = 2;
        a[6] = 0;
    }
}

s32 func_801221A8(void) {
    u8 *p = PLAYER;

    if (p != NULL) {
        p[5] = 1;
        M2C_FIELD(p, s16 *, 0x2E) = 0x22C4;
        M2C_FIELD(p, s16 *, 0x32) = -0xAF0;
        M2C_FIELD(p, s16 *, 0x60) = 0;
        M2C_FIELD(p, s16 *, 0x36) = 0x1EBE;
        return 1;
    }
    return 0;
}

void func_801221EC(void *arg0) {
    if (M2C_FIELD(arg0, s16 *, 0x40) != 0) {
        if (M2C_FIELD(M2C_FIELD(arg0, void **, 0x38), u16 *, 4) != 0) {
            func_80074590(0xA, -3, 0);
            M2C_FIELD(arg0, s16 *, 0x40) = 0;
        }
    } else if (M2C_FIELD(M2C_FIELD(arg0, void **, 0x38), u16 *, 4) == 0) {
        M2C_FIELD(arg0, s16 *, 0x40) = 1;
    }
}

void func_80122264(void *arg0) {
    if (M2C_FIELD(arg0, s16 *, 0x40) != 0) {
        if (M2C_FIELD(M2C_FIELD(arg0, void **, 0x38), u16 *, 2) != 0) {
            func_80074590(0x33, 0xC, 0);
            M2C_FIELD(arg0, s16 *, 0x40) = 0;
        }
    } else if (M2C_FIELD(M2C_FIELD(arg0, void **, 0x38), u16 *, 2) == 0) {
        M2C_FIELD(arg0, s16 *, 0x40) = 1;
    }
}

s32 func_801222DC(u8 *a) {
    u8 *g = D_800BF808_1760;

    M2C_FIELD(a, s16 *, 0x60) = g[3];
    switch (g[3]) {
    case 0x7B:
        a[0x5E] = 2;
        M2C_FIELD(a, s16 *, 0x60) = 0x66;
        break;
    case 0x78:
        a[0x5E] = 2;
        M2C_FIELD(a, s16 *, 0x60) = 0x67;
        break;
    case 0x7E:
        a[0x5E] = 2;
        M2C_FIELD(a, s16 *, 0x60) = 0x68;
        break;
    case 0x79:
        a[0x5E] = 4;
        break;
    case 0x7A:
        a[0x5E] = 5;
        break;
    case 0x77:
        a[0x5E] = 6;
        break;
    case 0x7C:
        a[0x5E] = 7;
        break;
    case 0x7D:
        a[0x5E] = 8;
        break;
    default:
        M2C_FIELD(a, s16 *, 0x60) = -1;
        return 0;
    }
    return 1;
}

s32 func_801223B4(u8 *a) {
    u8 *p = func_8006FB0C(a, M2C_FIELD(a, s16 *, 0x60));

    PLAYER = p;
    if (p != NULL) {
        p[0x5E] = 2;
        p[0x5F] |= 1;
        return 1;
    }
    return 0;
}

extern u8 D_8012C67C[];
void func_80122404(u8 *a) {
    s32 s;
    s32 one;
    u8 k;

    if (D_800BF816 == 0) {
        a[4] = 3;
        return;
    }
    s = a[5];
    one = 1;
    switch (s) {
    case 0:
        k = D_8012C67C[0];
        *(u8 **)(a + 0x14) = D_8012C67C;
        a[0x7B] = 0xF;
        a[0x5F] = k;
        a[5]++;
    case 1:
        if (!func_8007778C(a)) {
            break;
        }
        func_80076D68(a);
        if (D_1F800137 != 0) {
            break;
        }
        if (!(a[0x2B] & 2)) {
            a[6] = 0;
            a[5] = 3;
        }
        if (a[0x2B] == 3) {
            func_80042354(1, 1);
            a[6] = 0;
            a[5]++;
        }
        break;
    case 2:
        if (f_RunTabbyHouseResidentConversation(a)) {
            a[5] = one;
        }
        break;
    case 3:
        if (!func_8007778C(a)) {
            break;
        }
        func_80076D68(a);
        if ((a[0x2B] & 2) || D_1F800137 != 0) {
            if (a[0x46] != 0x14) {
                func_80041768(a, a[0x7B], 4);
            }
            a[5] = one;
            break;
        }
        func_8011CE8C(a);
        if (a[6] == 3 && !(D_1F80017C & 0x1F) && !(func_8009A450() & 3)) {
            func_80041768(a, 0x14, 4);
        }
        break;
    }
}

extern u8 D_8012C690;
void func_801225EC(u8 *a) {
    switch (a[5]) {
    case 0:
        if (func_8007778C(a) && a[0x2B] == 3) {
            func_80042354(1, 1);
            func_80040D68(a, &D_800A3D18_5587);
            a[0x70] = 2;
            a[6] = 0;
            a[5]++;
        }
        break;
    case 1:
        a[1] = 1;
        func_80077E7C(a);
        func_80041098(a);
        if (a[0x70] == 0xFF) {
            if (a[6] == 0) {
                if (D_800BF870.pad1[0xB4] != 0xFF) {
                    a[0x7A] = 0x1E;
                } else if (D_800BF870.pad1[0x56] != D_800BF870.pad1[0xB4]) {
                    a[0x7A] = 0x1F;
                } else {
                    a[0x7A] = 0x21;
                }
                func_80040D68(a, &D_8012C690);
                a[0x70] = 2;
                a[6]++;
            } else {
                a[5] = 0;
            }
        }
        break;
    }
    if (a[1] != 0) {
        func_8004190C(a);
    }
}

extern u8 D_80129348[];
extern u8 D_8012C5A4[];
s32 func_80126C18(u8 *a);
void func_80122728(u8 *a)
{
    switch (a[4]) {
    case 0:
        if (a[5] == 0) {
            a[5]++;
            break;
        }
        a[5] = 0;
        if (func_800519E0(a, 0xF, D_800ECF58[0x48 / 4], D_80129348) != 0) {
            break;
        }
        M2C_FIELD(a, s32 *, 0x3C) = D_800ECF58[0x38 / 4];
        func_80040CDC(a, D_80139240_0000, D_800A3D18_ed09);
        a[0xB] = 0x40;
        a[0] = 9;
        M2C_FIELD(a, s16 *, 0x80) = 0xAA;
        M2C_FIELD(a, s16 *, 0x82) = 0x154;
        M2C_FIELD(a, s16 *, 0x84) = 0x90;
        M2C_FIELD(a, s16 *, 0x86) = 0xF0;
        a[0x2B] = 0;
        a[0x29] = 0;
        M2C_FIELD(a, s16 *, 0x58) = 0;
        M2C_FIELD(a, s16 *, 0x56) = 0;
        M2C_FIELD(a, s16 *, 0x54) = 0;
        switch (a[3]) {
        case 0:
            M2C_FIELD(a, s32 *, 0x2C) = 0x266A0000;
            M2C_FIELD(a, s32 *, 0x30) = 0xF8F80000;
            M2C_FIELD(a, s32 *, 0x34) = 0x28DE0000;
            a[0x7B] = 0;
            M2C_FIELD(a, s16 *, 0x56) = 0x400;
            break;
        case 1:
            a[0x7B] = 0xF;
            M2C_FIELD(a, s16 *, 0x56) = 0x400;
            break;
        case 2:
            a[0x7B] = 0;
            M2C_FIELD(a, s16 *, 0x56) = 0xC00;
            break;
        }
        func_80126C18(a);
        func_80041718(a, a[0x7B], 0);
        a[4]++;
        break;
    case 1:
        switch (a[3]) {
        case 0:
            switch (a[5]) {
            case 0:
                func_80040D68(a, D_8012C5A4);
                a[0x70] = 2;
                a[5]++;
                break;
            case 1:
                if (a[0x70] == 0xFF) {
                    a[3] = 1;
                    a[5] = 0;
                }
                break;
            }
            a[1] = 1;
            func_80077E7C(a);
            func_80041098(a);
            func_8004190C(a);
            break;
        case 1:
            func_80122404(a);
            break;
        case 2:
            func_801225EC(a);
            break;
        }
        if (a[1] != 0) {
            func_800518FC(a);
        }
        a[0x2B] = 0;
        a[0x29] = 0;
        break;
    case 2:
    case 3:
        func_8007A624(a);
        break;
    }
}

void func_80122728();
void func_801229D4(s32 arg0, s8 arg1) {
    void *temp_v0;

    temp_v0 = func_8007A980(3, 9, 0);
    M2C_FIELD(temp_v0, s8 *, 2) = 0x1D;
    M2C_FIELD(temp_v0, s8 *, 3) = arg1;
    M2C_FIELD(temp_v0, M2C_UNK **, 0x1C) = (M2C_UNK *)func_80122728;
    M2C_FIELD(temp_v0, u8 *, 0x28) = (u8) (M2C_FIELD(temp_v0, u8 *, 0x28) | 0x80);
}

s32 func_80122A28(u8 *a) {
    u8 *t = D_1F800214;
    s16 v[6];

    switch (a[0x78]) {
    case 0:
        v[1] = 0x24A4;
        v[3] = M2C_FIELD(t, s16 *, 0x32);
        v[5] = M2C_FIELD(t, s16 *, 0x36);
        func_80070F00(a, 1, v);
        func_800708B4(3);
        a[0x78]++;
        break;
    case 1:
        if (t[3] == 0) {
            return 1;
        }
        break;
    }
    return 0;
}

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80122AC4);

void func_80122EA8(u8 *a) {
    s16 v[6];
    s32 i;
    s32 s, c;

    i = 0;
    M2C_FIELD(a, s16 *, 0x56) = 0;
    do {
        i++;
        s = (func_80083F50(M2C_FIELD(a, s16 *, 0x56)) * 70) >> 12;
        c = func_80083E80(M2C_FIELD(a, s16 *, 0x56));
        M2C_FIELD(a, s16 *, 0x56) += 0x400;
        v[1] = M2C_FIELD(a, s16 *, 0x2E) + s;
        v[3] = M2C_FIELD(a, s16 *, 0x32);
        v[5] = M2C_FIELD(a, s16 *, 0x36) - ((c * 70) >> 12);
        func_8003116C(0, v, -0x5A);
    } while (i < 4);
}

#define S32(o) (*(s32 *)(a + (o)))
void func_80122F6C(u8 *a) {
    switch (a[5]) {
    case 0:
        W16(0x44) += 0x180;
        if (I16(0x44) > 0x1800) {
            W16(0x44) = 0x1800;
        }
        S32(0x30) += I16(0x44) << 8;
        W16(0x2E) += W16(0x4E);
        W16(0x32) += W16(0x50);
        if (--I16(0x40) == 0) {
            W16(0x2E) = 0x13F6;
            I16(0x32) = -0xD42;
            func_8003116C(0, a + 0x2C, 0);
            a[8] = 0xD0;
            a[5]++;
        }
        break;
    case 1:
        W16(0x36) -= W16(0x42);
        if (I16(0x36) < 0x24FD) {
            a[0x29] = 0;
            W16(0x42) = 10;
            W16(0x44) = 0;
            a[5]++;
        }
        break;
    case 2:
        func_80077B5C(a);
        W16(0x36) -= W16(0x42);
        W16(0x44) += 0x300;
        if (I16(0x44) > 0x3000) {
            W16(0x44) = 0x3000;
        }
        S32(0x30) += I16(0x44) << 8;
        if (I16(0x32) >= -0xC39) {
            I16(0x32) = -0xC3A;
            W16(0x42) = 0xF;
            a[5]++;
        }
        break;
    case 3:
        W16(0x32) += (func_80083E80(0x133) * I16(0x42)) >> 12;
        W16(0x2E) -= (func_80083F50(0x133) * I16(0x42)) >> 12;
        if (I16(0x2E) < 0x10E0) {
            W16(0x42) = 5;
            W16(0x44) = 0;
            a[8] = 0;
            a[0x5E] = 1;
            a[5]++;
        }
        break;
    case 4:
        if (I16(0x42) != 0) {
            W16(0x2E) -= W16(0x42);
            W16(0x42)--;
        }
        W16(0x44) += 0x300;
        if (I16(0x44) > 0x3000) {
            W16(0x44) = 0x3000;
        }
        S32(0x30) += I16(0x44) << 8;
        if (I16(0x32) >= -0x64B) {
            W16(0x44) = 0;
            W16(0x40) = 8;
            a[5]++;
        }
        break;
    case 5:
        func_80077B5C(a);
        if (--I16(0x40) == 0) {
            if (a[3] == 1) {
                D_800BF844 = 0;
            }
            a[4] = 3;
        }
        W16(0x7A) -= 0x100;
        W16(0x7C) -= 0xCC;
        W16(0x7E) -= 0xCC;
        break;
    }
}

void func_8012328C(u8 *a)
{
    u8 *p;

    switch (a[5]) {
    case 0:
        W16(0x44) += 0x300;
        if (I16(0x44) > 0x3000) {
            I16(0x44) = 0x3000;
        }
        *(s32 *)(a + 0x30) += I16(0x44) << 8;
        if (I16(0x32) >= -0x98C) {
            I16(0x32) = -0x98D;
            p = func_8003116C(0, a + 0x2C, 0);
            p[0x28] |= 0x80;
            a[5]++;
        }
        break;
    case 1:
        W16(0x2E) += W16(0x42);
        if (I16(0x2E) >= 0x2309) {
            a[0x29] = 0;
            I16(0x44) = 0;
            a[5]++;
        }
        break;
    case 2:
        W16(0x36) -= W16(0x42);
        if (I16(0x36) < 0x2968) {
            a[0x29] = 0;
            I16(0x44) = 0;
            a[5]++;
        }
        break;
    case 3:
        W16(0x36) -= W16(0x42);
        if (I16(0x42) != 0) {
            W16(0x42)--;
        }
        W16(0x44) += 0x300;
        if (I16(0x44) > 0x3000) {
            I16(0x44) = 0x3000;
        }
        *(s32 *)(a + 0x30) += I16(0x44) << 8;
        if (I16(0x32) >= -0x8B0) {
            a[0x29] = 0;
            I16(0x44) = 0;
            a[4] = 3;
            a[5]++;
        }
        break;
    }
}

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80123470);

void func_801236C8(u8 *a) {
    *(s32 *)(a + 0x3C) = D_800ECF58[0x38 / 4];
    if (func_800519E0(a, 0x10, D_800ECF58[0x50 / 4], D_80129158) == 0) {
        func_80051B04(*(u8 **)(a + 0xC4), 0x14, 0x10);
        { s32 i = a[9] - 1; *(s32 *)(*(u8 **)(a + (i << 2) + 0xC0) + 0x40) = 0; }
        func_80040CDC(a, D_80139240_0000, D_800A3CD0);
        func_80041718(a, 0x13, 0);
        if (D_800BF870.pad1[0x8E] == 0xFF) {
            func_80041718(a, 2, 0);
            a[0x5E] = 4;
        } else if (D_800BF870.pad1[0x8D] == 0xFF) {
            a[3] = 1;
            if (D_800BF870.itemCounts[0x4A] != 0) {
                a[0x5E] = 3;
            } else {
                a[0x5E] = 2;
            }
        } else if ((D_800BF870.pad1[0x8D] & 2) && D_800BF870.itemCounts[0x4B] != 0) {
            a[0x5E] = 1;
        } else {
            a[0x5E] = 0;
        }
        a[0] = 9;
        *(s16 *)(a + 0x80) = 0xAA;
        *(s16 *)(a + 0x82) = 0x154;
        *(s16 *)(a + 0x84) = 0xC8;
        *(s16 *)(a + 0x54) = 0;
        *(s16 *)(a + 0x56) = 0;
        *(s16 *)(a + 0x58) = 0;
        a[0xB] = 0;
        *(s16 *)(a + 0x86) = 0x168;
        a[0x2B] = 0;
        a[0x29] = 0;
        a[4]++;
    }
}

extern u8 D_8012C8BC;
extern u8 D_8012C6BC;
void func_8012383C(u8 *a) {
    u8 *p;

    switch (a[0x2B]) {
    case 2:
        if (D_800BF808_1760[2] == 1 && (D_800BF808_1760[3] == 0x80 || D_800BF808_1760[3] == 0x92 || D_800BF808_1760[3] == 0x7F)) {
            *(s16 *)(a + 0x60) = D_800BF808_1760[3];
            p = func_8006FB0C(a, D_800BF808_1760[3]);
            *(u8 **)(D_800BF808_1760 + 0x3C) = p;
            if (p != NULL) {
                p[0x5E] = 0;
            }
            func_80040D68(a, &D_8012C8BC);
            a[0x70] = 1;
            a[5] = 4;
        }
        break;
    case 3:
        func_80041768(a, 2, 8);
        if (a[0x5E] == 4) {
            func_80040D68(a, &D_800A3D08);
        } else {
            if (a[0x5E] == 3) {
                func_80042354(1, 3);
            } else {
                func_80042354(1, 1);
            }
            func_80040D68(a, &D_8012C6BC);
        }
        a[0x70] = 1;
        a[5] = 1;
        break;
    }
}

extern u8 D_800BFAFE;
extern void *D_8012C914_7d7d[];
void func_80123DA4(void *arg0);
void func_8012396C(u8 *a) {
    s32 n = 0;

    if (a[0x71] == 0xFF) {
        switch (a[0x5E]) {
        case 0: {
            u8 *g = (u8 *)&D_800BF870;
            g[0x8E] |= 2;
            if (g[0x28F] != 0) {
                n = 1;
            }
            break;
        }
        case 1:
            if (D_800BFAFE != 0) {
                func_80042354(1, 3);
                n = 2;
            } else {
                a[0x5E] = 2;
                a[3] = 1;
            }
            break;
        case 3:
            a[0x5E] = 4;
            a[3] = 0;
            break;
        }
        if (n != 0) {
            a[0x5E] += n;
            func_80040D68(a, D_8012C914_7d7d[a[0x5E]]);
        } else {
            func_80040D68(a, D_800A3E58);
            a[5] = 3;
        }
        a[6] = 0;
        a[0x70] = 1;
    } else if (a[0x71] == 0) {
        a[0x70] = 1;
        a[6]++;
    }
    switch (a[0x5E]) {
    case 1:
        if (a[6] == 1 && D_800BF844_3cf3 != 0) {
            *(s16 *)(D_800BF844_3cf3 + 0x56) = 0xC00;
            a[6]++;
        }
        break;
    case 3:
        switch (a[6]) {
        case 1:
            func_8004190C(a);
            if (a[0x46] == 0x17) {
                func_80123DA4(a);
            }
            break;
        case 3: {
            u8 *g = D_800BF808_1760;
            (*(u8 **)(g + 0x3C))[0x5F] |= 1;
            *(s16 *)(*(u8 **)(g + 0x3C) + 0x62) = 0x20;
        }
            a[6]++;
        case 4:
            *(u16 *)(D_800BF844_3cf3 + 0x56) = *(u16 *)(a + 0x56);
            break;
        }
        break;
    }
}

void func_80123CD8(u8 *a);
void func_80123D38(void *arg0);
void func_80123D54(void *arg0);
void func_80123BB8(u8 *a) {
    switch (a[4]) {
    case 0:
        func_801236C8(a);
        break;
    case 1:
        a[1] = 1;
        func_80077E7C(a);
        func_80041098(a);
        func_8004190C(a);
        switch (a[5]) {
        case 0:
            func_8012383C(a);
            break;
        case 1:
            func_80123CD8(a);
            break;
        case 2:
            func_8012396C(a);
            break;
        case 3:
            func_80123D38(a);
            break;
        case 4:
            func_80123D54(a);
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

extern s32 D_8012C914[];
void func_80123CD8(u8 *a) {
    if (a[0x71] == 0xFF) {
        func_80040D68(a, D_8012C914[a[0x5E]]);
        a[0x70] = 1;
        a[5] = 2;
        a[6] = 0;
    }
}

void func_80123D38(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x71) == 0xFF) {
        M2C_FIELD(arg0, s8 *, 5) = 0;
    }
}

void func_80123D54(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x71) == 0xFF) {
        func_8004D4F4(M2C_FIELD(arg0, s16 *, 0x60), 1);
        M2C_FIELD(arg0, s8 *, 5) = 0;
    }
}

extern s32 D_800BF844;
s32 func_80123D94(void) {
    D_800BF844 = 0;
    return 1;
}

void func_80123DA4(void *arg0) {
    if (M2C_FIELD(arg0, s16 *, 0x40) != 0) {
        if (M2C_FIELD(M2C_FIELD(arg0, void **, 0x38), u16 *, 2) != 0) {
            func_80074590(0x2E, -0xC, -0x28);
            M2C_FIELD(arg0, s16 *, 0x40) = 0;
        }
    } else if (M2C_FIELD(M2C_FIELD(arg0, void **, 0x38), u16 *, 2) == 0) {
        M2C_FIELD(arg0, s16 *, 0x40) = 1;
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
void func_80124138(u8 *a, s32 *p0, s32 *p1, s32 *p2);
void func_80123E1C(u8 *a) {
    s32 p[6];
    s32 ang;
    s32 s;
    s32 dx;
    s32 dz;
    s16 y;

    D_800A3F90 = 0x3E80;
    y = D_1F8000D0_959d.yaw;
    D_800A3F94 = 0x16C;
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
    func_80124138(a, &p[0], &p[2], &p[4]);
}

extern s8 *D_800ECF58_3138[];
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
void func_80124138(u8 *a, s32 *p0, s32 *p1, s32 *p2) {
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
void func_80124678(u8 *a)
{
    u16 *p = D_800ECF78;
    u16 t;

    *(u16 **)(a + 0xC) = p;
    *(u16 *)(a + 8) = p[0];
    t = p[1];
    a[7] = 0;
    *(u16 *)(a + 0xA) = t;
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
u32 *func_801246A4(u32 *f, u32 *ot, s32 n)
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
u32 *func_8012496C(u32 *f, u32 *ot, s32 n)
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

#define gte_SetRotMatrix(r0) __asm__ volatile("lw	$12, 0( %0 );" "lw	$13, 4( %0 );" "ctc2	$12, $0;" "ctc2	$13, $1;" "lw	$12, 8( %0 );" "lw	$13, 12( %0 );" "lw	$14, 16( %0 );" "ctc2	$12, $2;" "ctc2	$13, $3;" "ctc2	$14, $4" : : "r"(r0) : "$12", "$13", "$14")
#define gte_SetTransMatrix(r0) __asm__ volatile("lw	$12, 20( %0 );" "lw	$13, 24( %0 );" "ctc2	$12, $5;" "lw	$14, 28( %0 );" "ctc2	$13, $6;" "ctc2	$14, $7" : : "r"(r0) : "$12", "$13", "$14")
extern u8 D_1F8000F8[];
extern void *D_800ED8C8_a098;
typedef struct {
    u8 pad0[6];
    u8 count;
    u8 pad7[5];
    u32 *tbl;
    u16 list[1];
} PartList;
void func_80124CB8(PartList *a)
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
    ot = D_800ED8C8_a098;
    tbl = a->tbl;
    gte_SetRotMatrix(D_1F8000F8);
    gte_SetTransMatrix(D_1F8000F8);
    for (; p < end; p++) {
        e = &tbl[*p];
        v = *e;
        r = func_801246A4(e + 1, ot, v & 0xFF);
        v >>= 16;
        func_8012496C(r, ot, v & 0xFF);
    }
}

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80124DB8);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80125100);

void func_8012555C(u32 *p, void *b)
{
    u32 lo = *p;
    u32 packed;

    packed = lo;
    lo = packed & 0xFFFF;
    p += 4;
    func_80125100(func_80124DB8(p, b, lo), b, packed >> 16);
}

extern u16 D_8012C928;
void func_801255A4(s32 arg0) {
    D_8012C928 = (D_8012C928 + arg0) & 0xFF;
}

extern u16 D_8012C92A;
extern u16 D_8012C92C;
void func_801255C0(s32 arg0) {
    u16 temp_a0;
    u16 temp_v0;
    u16 temp_v1;

    temp_v1 = D_8012C92A + arg0;
    D_8012C92A = temp_v1;
    if ((u32) (temp_v1 & 0xFFFF) >= 0x180U) {
        D_8012C92A = temp_v1 - 0x180;
    }
    temp_a0 = D_8012C92C;
    temp_v0 = temp_a0 + 0x100;
    D_8012C92C = temp_v0;
    if ((u32) (temp_v0 & 0xFFFF) >= 0x800U) {
        D_8012C92C = temp_a0 - 0x700;
    }
}

extern s32 D_801390E0[];
void func_80125618(u8 *a, s32 *b) {
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
        i = D_801390E0[1] > D_801390E0[0];
        break;
    case 5:
        i = (D_801390E0[2] > D_801390E0[0]) * 2;
        break;
    case 9:
        i = 0;
        if (D_801390E0[3] > D_801390E0[0]) {
            i = 3;
        }
        break;
    case 6:
        i = 1;
        if (D_801390E0[2] > D_801390E0[1]) {
            i = 2;
        }
        break;
    case 10:
        i = 1;
        if (D_801390E0[3] > D_801390E0[1]) {
            i = 3;
        }
        break;
    case 12:
        i = 2;
        if (D_801390E0[3] > D_801390E0[2]) {
            i = 3;
        }
        break;
    case 11:
        if (D_801390E0[3] > D_801390E0[0]) {
            i = 1;
            if (D_801390E0[3] > D_801390E0[1]) {
                i = 3;
            }
        } else {
            i = D_801390E0[1] > D_801390E0[0];
        }
        break;
    case 13:
        if (D_801390E0[3] > D_801390E0[0]) {
            i = 2;
            if (D_801390E0[3] > D_801390E0[2]) {
                i = 3;
            }
        } else {
            i = (D_801390E0[2] > D_801390E0[0]) * 2;
        }
        break;
    case 14:
        if (D_801390E0[3] > D_801390E0[1]) {
            i = 2;
            if (D_801390E0[3] > D_801390E0[2]) {
                i = 3;
            }
        } else {
            i = 1;
            if (D_801390E0[2] > D_801390E0[1]) {
                i = 2;
            }
        }
        break;
    case 7:
        if (D_801390E0[2] > D_801390E0[0]) {
            i = 1;
            if (D_801390E0[2] > D_801390E0[1]) {
                i = 2;
            }
        } else {
            i = D_801390E0[1] > D_801390E0[0];
        }
        break;
    case 15:
    default:
        m = D_801390E0[0];
        i = 0;
        for (j = 1; j < 4; j++) {
            v = &D_801390E0[j];
            if (m < *v) {
                i = j;
                m = *v;
            }
        }
        break;
    }
    m = D_801390E0[i];
    p = a + i * 4;
    d = *(s16 *)(p + 0x20) * m;
    j = *(s16 *)(p + 0x22) * m;
    b[0] -= d;
    b[2] -= j;
}

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_801258A4);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80125C5C);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80125F7C);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80126240);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_801265AC);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80126968);

s32 func_80126C18(u8 *a) {
    s16 y = M2C_FIELD(a, s16 *, 0x32);
    s32 i;

    a[0x29] = 0;
    M2C_FIELD(a, s16 *, 0x32) = y - 0x80;
    for (i = 0; i < 200; i++) {
        if (func_8010A868(a) != 0) {
            a[0x29] = 0;
            return 1;
        }
        M2C_FIELD(a, s16 *, 0x32) += 0x20;
    }
    M2C_FIELD(a, s16 *, 0x32) = y;
    return 0;
}

s32 func_80126C94(u8 *a) {
    u16 f;
    s16 g;

    switch (a[0x78]) {
    case 0:
        D_800BF818 = a[0x74];
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

typedef struct { u8 b[6]; } Tbl6D24;
extern Tbl6D24 D_8010A4A4;
#define U(p, o) (*(u16 *)((p) + (o)))
#define S(p, o) (*(s16 *)((p) + (o)))

s32 func_80126D24(u8 *a)
{
    Tbl6D24 t = D_8010A4A4;
    u8 *s = a + 0x50;
    s32 d;
    s16 k;

    switch (a[4]) {
    case 0:
        *(s32 *)(a + 0x48) = 0;
        *(s32 *)(a + 0x4C) = 0;
        S(a, 0x50) = 0;
        S(s, 2) = 0;
        k = S(a, 0x2E);
        S(s, 8) = -2;
        S(s, 4) = k;
        a[4] = 1;
    case 1:
        d = S(a, 0x2E);
        d = S(s, 4) - d;
        d -= 0xC8;
        d *= d;
        d = 0x112 - (d >> 8);
        d /= 16;
        S(s, 6) = d;
        if ((s16)d <= 0) {

            a[4] = 2;
            break;
        }
        U(a, 0x2E) += U(s, 8);
        U(s, 8) += (-0x19 - S(s, 8)) >> 1;
        U(s, 2)++;
        if (S(s, 2) >= 0xC) {
            S(s, 2) = 0;
        }
        U(s, 0) = t.b[S(s, 2) >> 1];
        a[1] = 1;
        U(a, 0x4A) += 0x44;
        break;
    case 2:
    case 3:
        func_8007A624(a);
        break;
    }
}

extern u8 D_80138990[];
typedef struct { u8 pad[0x48]; s16 r[3]; } RotAct;
void func_80126EA8(u8 *a)
{
    u8 *p;
    s32 k;
    switch (a[4]) {
    case 0:
        *(s32 *)(a + 0x50) = 0x100;
        *(s32 *)(a + 0x54) = 0x100;
        a[1] = 1;
        a[4] = 1;
        *(s16 *)(a + 0x48) = 0;
        *(s16 *)(a + 0x4A) = 0;
        *(s16 *)(a + 0x4C) = 0;
        *(s16 *)(a + 0x4E) = 0x78;
    case 1:
        p = *(u8 **)(a + 0x38);
        *(u8 **)(a + 0x34) = p;
        if (p == NULL) {
            *(u8 **)(a + 0x34) = D_80138990;
        }
        ((RotAct *)a)->r[0] += func_80083F50(D_1F80017C >> 7) >> 5;
        ((RotAct *)a)->r[1] += func_80083F50(D_1F80017C >> 4) >> 7;
        ((RotAct *)a)->r[2] += func_80083F50(D_1F80017C * 2) >> 6;
        a[1] = 1;
        break;
    case 2:
        switch (a[5]) {
        case 0:
            a[5] = 1;
        case 1:
            *(s32 *)(a + 0x50) -= 0x10;
            if (*(s32 *)(a + 0x50) < 0) {
                *(s32 *)(a + 0x50) = 0;
            }
            *(s32 *)(a + 0x54) += 0x80;
            if (++a[6] > 16) {
                a[4] = 3;
            }
            a[1] = 1;
            break;
        }
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

typedef struct {
    u32 tag;
    u32 rgbc;
    s16 x0, y0;
    u8 u0, v0;
    u16 clut;
    s16 x1, y1;
    u8 u1, v1;
    u16 tpage;
    s16 x2, y2;
    u8 u2, v2;
    u16 pad1;
    s16 x3, y3;
    u8 u3, v3;
    u16 pad2;
} AreaPolyFT4;
extern u32 *D_800ED8C8;
AreaPolyFT4 *func_80127034(AreaPolyFT4 *p, s32 x, s32 y, s32 w, s32 h, s16 c, s16 cy) {
    u32 rgbc;
    u16 clut;
    s16 x0, x1;

    if (c <= 0) return p; {
        rgbc = ((c | 0x2E00) << 16) | ((c << 8) | c);
        clut = ((cy + 0x1F0) << 6) | 0x17;
        x0 = x - w;
        x1 = x + w;
        p->u0 = p->u2 = 0xB9;
        p->u1 = p->u3 = 0xE7;
        p->v0 = p->v1 = 0x51;
        p->v2 = p->v3 = 0x67;
        *(u32 *)((u8 *)p + 4) = rgbc;
        p->tpage = 0x35;
        p->clut = clut;
        p->x0 = p->x2 = x0;
        p->x1 = p->x3 = x1;
        p->y0 = p->y1 = y - h;
        p->y2 = p->y3 = y;
        p->tag = D_800ED8C8[4] | 0x09000000;
        D_800ED8C8[4] = (u32)p;
        p++;
        p->u0 = p->u2 = 0xB9;
        p->u1 = p->u3 = 0xE7;
        p->v0 = p->v1 = 0x67;
        p->v2 = p->v3 = 0x51;
        *(u32 *)((u8 *)p + 4) = rgbc;
        p->tpage = 0x35;
        p->clut = clut;
        p->x0 = p->x2 = x0;
        p->x1 = p->x3 = x1;
        p->y0 = p->y1 = y;
        p->y2 = p->y3 = y + h;
        p->tag = D_800ED8C8[4] | 0x09000000;
        D_800ED8C8[4] = (u32)p;
        return p + 1;
    }

}

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80127170);

#define U32(p, o) M2C_FIELD(p, u32 *, o)
void func_80127678(u8 *a) {
    u32 v;

    switch (a[4]) {
    case 0:
        U32(a, 0x50) = 0x303030;
        a[1] = 1;
        U32(a, 0x58) = 0x1000;
        U32(a, 0x5C) = 0;
        U32(a, 0x48) = 0;
        U32(a, 0x4C) = 0;
        a[4] = 1;
        a[5] = 0;
    case 1:
        a[1] = 1;
        {s32 c = a[5]; if (c == 0) {
            if (U32(a, 0x58) != 0) {
                U32(a, 0x58) -= 0x100;
            } else {
                a[5] = c + 1;
            }
        }}
        if ((U32(a, 0x5C) += 0x20) >= 0xC0) {
            U32(a, 0x5C) = 0;
        }
        break;
    case 2:
        v = U32(a, 0x58);
        a[1] = 1;
        if (v <= 0x1000) {
            U32(a, 0x58) = v + 0x111;
        } else {
            a[4] = 3;
        }
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

#define gte_ldfcdir(r0, r1, r2) __asm__ volatile("ctc2	%0, $21;" "ctc2	%1, $22;" "ctc2	%2, $23" : : "r"(r0), "r"(r1), "r"(r2))
extern s32 D_1F800090[];
extern u8 D_801386BC[];
extern u8 D_80138794[];
void func_80127784(u8 *a) {
    s32 *d;
    s32 t;

    d = D_1F800090;
    gte_ldfcdir(0, 0, 0);
    t = M2C_FIELD(a, u16 *, 0x4A) + 0x400;
    *d = M2C_FIELD(a, s32 *, 0x58);
    M2C_FIELD(a, s16 *, 0x4A) = t;
    func_800318A0(a + 0x2C, a + 0x50, a + 0x48);
    M2C_FIELD(a, s16 *, 0x4A) -= 0x400;
    func_80027768(D_801386BC, 0, -0x14, M2C_FIELD(a, s32 *, 0x5C));
    if (a[0x2B] != 0) {
        func_800318A0(a + 0x2C, a + 0x50, a + 0x48);
        func_80027768(D_80138794, 0, -0x14, M2C_FIELD(a, s32 *, 0x5C));
    }
}

extern u8 D_8013886C[];
void func_80127860(u8 *p) {
    u8 c[4];
    s32 *d;

    c[0] = c[1] = c[2] = p[0x56];
    d = D_1F800090;
    gte_ldfcdir(0, 0, 0);
    *d = 0;
    func_800318A0(p + 0x2C, c, p + 0x48);
    func_80027768(D_8013886C, 0, -0x32, M2C_FIELD(p, s16 *, 0x50));
}

typedef struct { u8 pad[0xC0]; u8 *parts[1]; } PartsOwner;
typedef struct { s16 v[4]; } PartInit;
extern PartInit D_80138A08[];
s32 func_801278D8(PartsOwner *a)
{
    s32 i;
    u8 *q;

    a->pad[8] = 2;
    if (D_800ED098 < a->pad[8]) {
        a->pad[4] = 3;
        return 1;
    }
    a->pad[9] = 2;
    a->pad[0xD] = 0;
    a->pad[0x18] = 0xFF;
    a->pad[0x19] = 0xFF;
    a->pad[0x1A] = 0xFF;
    a->pad[0xB] = 0;
    *(s16 *)(a->pad + 0x54) = 0;
    *(s16 *)(a->pad + 0x56) = 0;
    *(s16 *)(a->pad + 0x58) = 0;
    for (i = 0; i < a->pad[9]; i++) {
        q = func_8007AAE8();
        a->parts[i] = q;
        *(s16 *)(q + 6) = D_80138A08[i].v[0];
        *(s16 *)(a->parts[i] + 0) = D_80138A08[i].v[1];
        *(s16 *)(a->parts[i] + 2) = D_80138A08[i].v[2];
        *(s16 *)(a->parts[i] + 4) = D_80138A08[i].v[3];
        *(s16 *)(a->parts[i] + 8) = 0;
        *(s16 *)(a->parts[i] + 0xA) = 0;
        *(s16 *)(a->parts[i] + 0xC) = 0;
        func_80051B04(a->parts[i], 0xC, i + 0x35);
    }
    a->pad[6] = 0;
    a->pad[8] = 1;
    a->pad[0x2B] = 0;
    return 0;
}

s16 func_800776F8();
#define C0 (*(u8 **)(a + 0xC0))
#define C4 (*(u8 **)(a + 0xC4))

void f_UpdateBlastTheRockSequence(u8 *a)
{
    s16 v[6];
    s32 i;
    u8 *p;

    switch (a[5]) {
    case 0:
        W16(0x32) += 8;
        if (func_8010A868(a) != 0) {
            a[5]++;
        }
        break;
    case 1:
        if (D_1F800137 != 0 || (D_1F80017C & 0x1F)) {
            a[0xD] = 0;
        } else {
            a[0xD] |= 2;
        }
        if (a[0xBF] != 0) {
            a[0xD] = 0;
            a[5]++;
        }
        break;
    case 2:
        i = 0;
        if (a[9] != 0) {
            do {
                *(s16 *)(*(u8 **)(a + i * 4 + 0xC0) + 8) = func_800776F8(0, *(s16 *)(*(u8 **)(a + i * 4 + 0xC0) + 8), 0x18);
                i++;
            } while (i < a[9]);
        }
        if (*(s16 *)(C0 + 8) == 0) {
            a[5]++;
        }
        break;
    case 3:
        if (a[0xBF] == 0) {
            a[5]++;
            a[0x2B] |= 2;
            if (a[8] == 2) {
                func_80074590(0x1C, -0xA, 0x2A);
            }
        }
        break;
    case 4:
        *(s16 *)(C0 + 8) = func_800776F8(0xF00, *(s16 *)(C0 + 8), 0x18);
        if (*(s16 *)(C0 + 8) < 0xF39) {
            *(s16 *)(C4 + 8) = func_800776F8(0x100, *(s16 *)(C4 + 8), 0x4C);
            *(u16 *)(C4 + 2) += 2;
        }
        *(u16 *)(C4 + 4) += 0x12;
        if (a[8] == 2 && !(D_1F80017C & 3)) {
            v[1] = *(s16 *)(C4 + 0x2C) + ((func_80083E80(I16(0x56)) * 0x60) / 0x1000);
            v[3] = *(s16 *)(C4 + 0x30) + 0x20;
            v[5] = *(s16 *)(C4 + 0x34) + ((func_80083F50(I16(0x56)) * 0x60) / 0x1000);
            func_8003116C(0, v, -0x5A);
        }
        if (*(s16 *)(C0 + 8) == 0xF00) {
            I16(0x40) = 0x12;
            a[5]++;
            if (a[8] == 2) {
                func_8010FD30(C4, 0, 0x32);
            }
        }
        break;
    case 5:
        if (a[8] == 2 && !(D_1F80017C & 3)) {
            func_8003116C(0, v, -0x5A);
            v[1] = *(s16 *)(C4 + 0x2C) + ((func_80083E80(I16(0x56)) * 0x30) / 0x1000);
            v[3] = *(s16 *)(C4 + 0x30) + 0x20;
            v[5] = *(s16 *)(C4 + 0x34) + ((func_80083F50(I16(0x56)) * 0x30) / 0x1000);
        }
        if (I16(0x40) == 0xF) {
            a[8] = 1;
        }
        if (--I16(0x40) == 0) {
            a[0x2B] = 0;
            *(s16 *)(C4 + 2) = D_80138A08[1].v[2];
            *(s16 *)(C4 + 4) = D_80138A08[1].v[3];
            *(s16 *)(C4 + 8) = 0;
            a[5] = 1;
        }
        break;
    }
    switch (a[6]) {
    case 0:
        if (a[0x2B] & 1) {
            func_80074590(0x1C, -0x10, 0x2A);
            a[6]++;
        }
        break;
    case 1:
        if (a[0x2B] == 0) {
            a[6] = 0;
        }
        break;
    }
}

extern u16 D_80138A18[];
void func_80127EDC(u8 *a) {
    s32 one = 1;
    s32 i;

    switch (a[4]) {
    case 0:
        if (func_801278D8(a) == 0) {
            *(s16 *)(a + 0x80) = 0x50;
            *(s16 *)(a + 0x82) = 0xA0;
            *(s16 *)(a + 0x84) = 0x96;
            *(s16 *)(a + 0x86) = 0x96;
            a[0] = one;
            a[0x29] = 0;
            a[0xBF] = 0;
            a[4]++;
            for (i = 0; i < a[9]; i++) {
                *(s16 *)(*(u8 **)(a + i * 4 + 0xC0) + 8) = 0xF00;
            }
        }
        break;
    case 1:
        if (D_800BF816 == 0) {
            if (func_8007778C(a)) {
                f_UpdateBlastTheRockSequence(a);
                func_800517F8(a);
            }
        } else {
            *(u16 *)(a + 0x2E) = D_80138A18[0];
            *(u16 *)(a + 0x32) = D_80138A18[1];
            *(u16 *)(a + 0x36) = D_80138A18[2];
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

void func_80128034(u8 *a, void *b) {
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
        if (a[0x29] == 0 && func_8010A868(a) == 0) {
            break;
        }
        I16(0x4A) = 0;
        a[5]++;
        break;
    }
    func_8004B374(a, b);
}

INCLUDE_ASM("asm/a02/nonmatchings/a02", f_UpdateTabbyHouseResidentActor);

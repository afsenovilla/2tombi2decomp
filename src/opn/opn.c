#include "common.h"
#include "game.h"
#include "m2c.h"

typedef struct { u16 lo; s16 hi; } OpnFix;
typedef struct { OpnFix at[3]; } OpnCam;
extern OpnCam D_1F8000D0;
#define H(p, o) (*(s16 *)((u8 *)(p) + (o)))

void func_8018A13C(u8 *a, u8 *b)
{
    if (++H(a, 0x42) >= 0x17) {
        H(a, 0x42) = 0x16;
    }
    g_CameraState.focusX = H(b, 0x60) + (0x8DA - H(b, 0x60)) * H(a, 0x42) / 22;
    g_CameraState.focusY = H(b, 0x62) + (-0x320 - H(b, 0x62)) * H(a, 0x42) / 22;
    g_CameraState.focusZ = H(b, 0x64) + (0x128C - H(b, 0x64)) * H(a, 0x42) / 22;
    D_1F8000D0.at[0].hi = H(b, 0x66) + (0xBEC - H(b, 0x66)) * H(a, 0x42) / 22;
    D_1F8000D0.at[1].hi = H(b, 0x68) + (-0x3E8 - H(b, 0x68)) * H(a, 0x42) / 22;
    D_1F8000D0.at[2].hi = H(b, 0x6A) + (0xC73 - H(b, 0x6A)) * H(a, 0x42) / 22;
}

INCLUDE_ASM("asm/opn/nonmatchings/opn", func_8018A300);

s32 func_8018AAA4(u8 *a, s32 target, s32 cur)
{
    s32 d, r;
    s16 e;
    d = (target - cur) & 0xFFF;
    e = d;
    if (d == 0) {
        return cur & 0xFFF;
    }
    if ((u32)e < 0x800) {
        if (d >= 0x100) {
            r = cur + 0x40;
        } else if (d >= 0x30) {
            r = cur + 0x10;
        } else if (d >= 0x20) {
            r = cur + 8;
        } else {
            r = cur + 1;
            if (d >= 0x10) {
                r = cur + 4;
            }
        }
        if (e >= 0x100) {
            *(u16 *)(a + 0x74) = 2;
        } else {
            *(u16 *)(a + 0x74) |= 1;
        }
    } else {
        r = cur - 0x40;
        if (d > 0xF00) {
            r = cur - 0x10;
            if (d > 0xFD0) {
                r = cur - 8;
                if (d > 0xFE0) {
                    r = cur - 4;
                    if (d > 0xFF0) {
                        r = cur - 1;
                    }
                }
            }
        }
        if (e <= 0xF00) {
            *(u16 *)(a + 0x74) = 2;
        } else {
            *(u16 *)(a + 0x74) |= 1;
        }
    }
    return r & 0xFFF;
}

typedef struct { s16 x, y, z, w; } OpnPoint;
extern OpnPoint D_8018D390[];

s32 func_8018AB78(u8 *a, u8 *b)
{
    OpnPoint *p;
    OpnCam *c;
    s16 dx, dy, dz;
    s32 sq, d;
    p = &D_8018D390[*(s16 *)(b + 0x72)];
    c = &D_1F8000D0;
    dz = p->z - c->at[2].hi;
    dx = p->x - c->at[0].hi;
    *(s16 *)(b + 0x66) = func_80085690(dz, dx) - 0x400;
    sq = dx * dx + dz * dz;
    d = func_80084080(sq);
    dy = p->y - c->at[1].hi;
    *(s16 *)(b + 0x68) = func_80085690(dy, d);
    *(s16 *)(b + 0x7A) = p->w;
    d = func_80084080(sq + dy + dy);
    *(s32 *)(a + 0x5C) = d;
    return d < 0x50;
}

INCLUDE_ASM("asm/opn/nonmatchings/opn", func_8018AC84);

INCLUDE_ASM("asm/opn/nonmatchings/opn", func_8018B924);

extern u8 D_800BF9ED;
extern u16 D_1F80017C;

void func_8018BD30(u8 *a)
{
    u16 t;
    switch (a[5]) {
    case 0:
        if (D_800BF9ED != 0) {
            a[1] = 1;
            a[0x147] = 0;
            *(s16 *)(a + 0x56) = 0;
            *(s16 *)(a + 0x58) = 0;
            a[5]++;
        }
        t = D_1F80017C;
        if ((t & 0x1F) == 0 || ((t & 0xF) == 0 && (func_8009A450() & 1))) {
            func_80074590(2, 0, 0);
        }
        break;
    case 1:
        func_8018A300(a, func_80076D68(a));
        break;
    case 2:
        *(s16 *)(a + 0x50) = 0;
        a[0x145] = 0;
        func_80054198(a);
        a[4] = 6;
        a[5] = 0;
        a[6] = 0;
        a[7] = 0;
        break;
    }
}

extern u8 D_800BF80E;
extern s32 D_1F800184;
extern u8 D_800BF89C;
extern u8 D_800E7E80[];

void func_8018BE40(u8 *a)
{
    u8 *t;

    switch (a[6]) {
    case 0:
        D_800BF80E = 0;
        a[6]++;
    case 1:
        if (func_80076D68(a) == 1) {
            D_800BF80E = 1;
        }
        if (D_1F800184 == 1) {
            *(s16 *)(a + 0x50) = 0;
            *(s16 *)(a + 0x4A) = 0;
        } else {
            func_80065478(a, 1);
        }
        break;
    }
    if (D_800BF89C == 3) {
        t = D_800E7E80;
        t[4] = 7;
        t[5] = 0;
        t[6] = 0;
        t[7] = 0;
    }
}

INCLUDE_ASM("asm/opn/nonmatchings/opn", func_8018BF08);

INCLUDE_ASM("asm/opn/nonmatchings/opn", func_8018C574);

extern u8 D_8012DA04[];

u8 *func_8018C7D8(void *a)
{
    u8 *r = func_80072DDC(a, 0, 3, 0x10);

    if (r == NULL) {
        return NULL;
    }
    r[3] = 1;
    *(void **)(r + 0x1C) = D_8012DA04;
    return r;
}

extern s32 D_8014A270;
#define P(p, o) (*(u8 **)((u8 *)(p) + (o)))

void func_8018C820(u8 *a)
{
    switch (a[6]) {
    case 0:
        if (D_800BF9ED < 0x46) {
            break;
        }
        H(P(a, 0xC4), 8) = H(a, 0x64);
        a[6]++;
        break;
    case 1:
        if (D_800BF9ED < 0x4B) {
            break;
        }
        H(a, 0x76) = 1;
        D_8014A270 = func_80074590(0x81, 0, 0x2A);
        H(a, 0x48) = 0x100;
        H(a, 0x4E) = 0x100;
        H(a, 0x40) = 0;
        a[6]++;
        break;
    case 2:
        H(P(a, 0xC4), 8) += H(a, 0x48) >> 8;
        if (H(P(a, 0xC4), 8) >= H(a, 0x66)) {
            H(P(a, 0xC4), 8) = H(a, 0x66);
            if (H(a, 0x40) != 0) {
                H(a, 0x48) = 0;
                H(a, 0x4E) = 0;
                a[6]++;
                break;
            }
            func_80074AF0(D_8014A270);
            D_8014A270 = 0;
            func_80074590(0x82, 0, 0);
            H(a, 0x48) = -0xA00;
            H(a, 0x4E) = 0x200;
            H(a, 0x76) = 2;
            H(a, 0x40) = 1;
        }
        H(a, 0x48) += H(a, 0x4E);
        if (H(a, 0x48) > 0x1600) {
            H(a, 0x48) = 0x1600;
        }
        break;
    case 3:
        if (D_800BF89C == 2) {
            break;
        }
        H(a, 0x76) = 0;
        H(P(a, 0xC4), 8) = 0xF0;
        func_801314B4(a);
        func_8013892C(a);
        a[5] = 0;
        a[6] = 0;
        break;
    }
}

INCLUDE_ASM("asm/opn/nonmatchings/opn", func_8018CA1C);

typedef struct {
    s16 pad0;
    s16 x;
    s16 pad4;
    s16 y;
    s16 pad8;
    s16 z;
} HiPos;
typedef struct {
    u8 pad0[8];
    u8 count;
    u8 pad9[0xB7];
    u8 *parts[4];
} PartOwner;

void func_8018CCFC(PartOwner *a, s16 b)
{
    HiPos p;

    p.x = *(s16 *)(a->parts[a->count - 1] + 0x2C);
    p.y = *(s16 *)(a->parts[a->count - 1] + 0x30);
    p.z = *(s16 *)(a->parts[a->count - 1] + 0x34);
    func_80027144(*(void **)(a->parts[a->count - 1] + 0x40), &p, 0x800, b);
    func_80074590(0xC, 0, 0);
}


void func_8018CDC4(u8 *a)
{
    u8 *o;

    switch (a[6]) {
    case 0:
        o = *(u8 **)(a + 0x10);
        if (*(s16 *)(a + 0x6A) == 0) {
            if (*(s16 *)(o + 0x76) == 1) {
                a[6] = 0;
                a[5]++;
            }
        } else {
            a[5] = 2;
            a[6] = 0;
        }
        break;
    case 1:
        if (D_800BF89C != 2) {
            a[4] = 3;
        }
        break;
    }
}

INCLUDE_ASM("asm/opn/nonmatchings/opn", func_8018CE40);

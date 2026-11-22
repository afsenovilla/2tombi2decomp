#include "common.h"
#include "game.h"
#include "m2c.h"

INCLUDE_ASM("asm/opn/nonmatchings/opn", func_8018A13C);

INCLUDE_ASM("asm/opn/nonmatchings/opn", func_8018A300);

INCLUDE_ASM("asm/opn/nonmatchings/opn", func_8018AAA4);

INCLUDE_ASM("asm/opn/nonmatchings/opn", func_8018AB78);

INCLUDE_ASM("asm/opn/nonmatchings/opn", func_8018AC84);

INCLUDE_ASM("asm/opn/nonmatchings/opn", func_8018B924);

INCLUDE_ASM("asm/opn/nonmatchings/opn", func_8018BD30);

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

INCLUDE_ASM("asm/opn/nonmatchings/opn", func_8018C820);

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

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

INCLUDE_ASM("asm/opn/nonmatchings/opn", func_8018BE40);

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

INCLUDE_ASM("asm/opn/nonmatchings/opn", func_8018CCFC);

extern u8 D_800BF89C;

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

#include "common.h"
#include "game.h"
#include "m2c.h"

INCLUDE_ASM("asm/crd/nonmatchings/crd", func_8018A1E8);

INCLUDE_ASM("asm/crd/nonmatchings/crd", func_8018A428);

INCLUDE_ASM("asm/crd/nonmatchings/crd", func_8018AEB8);

INCLUDE_ASM("asm/crd/nonmatchings/crd", func_8018B020);

INCLUDE_ASM("asm/crd/nonmatchings/crd", func_8018B1A4);

INCLUDE_ASM("asm/crd/nonmatchings/crd", func_8018B478);

INCLUDE_ASM("asm/crd/nonmatchings/crd", func_8018B660);

INCLUDE_ASM("asm/crd/nonmatchings/crd", func_8018B7E4);

INCLUDE_ASM("asm/crd/nonmatchings/crd", func_8018BA68);

INCLUDE_ASM("asm/crd/nonmatchings/crd", func_8018BF74);

INCLUDE_ASM("asm/crd/nonmatchings/crd", func_8018C4B4);

INCLUDE_ASM("asm/crd/nonmatchings/crd", func_8018C790);

INCLUDE_ASM("asm/crd/nonmatchings/crd", func_8018CCCC);

INCLUDE_ASM("asm/crd/nonmatchings/crd", func_8018CE40);

INCLUDE_ASM("asm/crd/nonmatchings/crd", func_8018D26C);

INCLUDE_ASM("asm/crd/nonmatchings/crd", func_8018D418);

INCLUDE_ASM("asm/crd/nonmatchings/crd", func_8018D74C);

INCLUDE_ASM("asm/crd/nonmatchings/crd", func_8018DB28);

extern u16 D_800E7E68;
extern u8 *D_1F800138;

void func_8018DC2C(u8 *a)
{
    u16 k;

    switch (a[1]) {
    case 0:
        a[0x50] = 0;
        a[1]++;
        break;
    case 1:
        if (++a[0x50] >= 11) {
            a[1]++;
        }
        break;
    case 2:
        if (a[0x4A] != 0xFC && a[0x4A] != 1 && a[0x4B] != 0xFC && a[0x4B] != 1) {
            a[2] = 0;
            a[1] = 0;
            a[0] = 1;
        }
        break;
    }
    k = D_800E7E68;
    if (k & 0x2000) {
        if (!(a[0x3C] & 1)) {
            *(s16 *)(D_1F800138 + 0x50) = 2;
            return;
        }
        *(s16 *)(D_1F800138 + 0x50) = 3;
    } else if (k & 0x1000) {
        *(s16 *)(D_1F800138 + 0x50) = 3;
    }
}

INCLUDE_ASM("asm/crd/nonmatchings/crd", func_8018DD38);

INCLUDE_ASM("asm/crd/nonmatchings/crd", func_8018DFEC);

INCLUDE_ASM("asm/crd/nonmatchings/crd", func_8018E2B4);

INCLUDE_ASM("asm/crd/nonmatchings/crd", func_8018E54C);

INCLUDE_ASM("asm/crd/nonmatchings/crd", func_8018E6BC);

INCLUDE_ASM("asm/crd/nonmatchings/crd", func_8018E95C);

INCLUDE_ASM("asm/crd/nonmatchings/crd", func_8018EC00);

INCLUDE_ASM("asm/crd/nonmatchings/crd", func_8018ED94);

INCLUDE_ASM("asm/crd/nonmatchings/crd", func_8018EFDC);

INCLUDE_ASM("asm/crd/nonmatchings/crd", func_8018F280);

INCLUDE_ASM("asm/crd/nonmatchings/crd", func_8018F414);

INCLUDE_ASM("asm/crd/nonmatchings/crd", func_8018F548);

INCLUDE_ASM("asm/crd/nonmatchings/crd", func_8018F660);

INCLUDE_ASM("asm/crd/nonmatchings/crd", func_8018F854);

INCLUDE_ASM("asm/crd/nonmatchings/crd", func_8018FA88);

INCLUDE_ASM("asm/crd/nonmatchings/crd", func_8018FBCC);

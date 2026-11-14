#include "common.h"
#include "game.h"
#include "m2c.h"

INCLUDE_ASM("asm/sop/nonmatchings/sop", func_80109164);

INCLUDE_ASM("asm/sop/nonmatchings/sop", func_801092B4);

INCLUDE_ASM("asm/sop/nonmatchings/sop", func_80109450);

extern s8 D_1F800138[];
extern M2C_UNK D_800BE0F0;
extern M2C_UNK D_800EF478;

void func_80109750(void) {
    func_8001DC40(&D_800EF478, M2C_FIELD(&D_800BE0F0, s32 *, 0) + M2C_FIELD(*((void **)D_1F800138), u8 *, 0x6E), 0x800);
    func_8001DC40((M2C_UNK *)0x8018A000, M2C_FIELD(&D_800BE0F0, s32 *, 8) + ((u32) M2C_FIELD(&D_800EF478, u32 *, 0) >> 0xB), M2C_FIELD(&D_800EF478, s32 *, 4) - M2C_FIELD(&D_800EF478, u32 *, 0));
    func_80044E84(0x8018A000, 0x1F8000);
}

INCLUDE_ASM("asm/sop/nonmatchings/sop", func_801097E4);

INCLUDE_ASM("asm/sop/nonmatchings/sop", func_80109860);

extern u8 D_800BF9B4;
extern M2C_UNK D_800ED018;
extern M2C_UNK D_800F2418;
void func_801098E8(void) {
    func_80109FE0(&D_800F2418);
    func_8003C048();
    if (D_800BF9B4 != 5) {
        func_8010C26C(&D_800ED018);
    }
}

INCLUDE_ASM("asm/sop/nonmatchings/sop", func_80109934);

INCLUDE_ASM("asm/sop/nonmatchings/sop", func_801099B4);

INCLUDE_ASM("asm/sop/nonmatchings/sop", func_80109C80);

INCLUDE_ASM("asm/sop/nonmatchings/sop", func_80109FE0);

INCLUDE_ASM("asm/sop/nonmatchings/sop", func_8010A0E0);

INCLUDE_ASM("asm/sop/nonmatchings/sop", func_8010A3AC);

extern u16 *D_800ECF78;

void func_8010A8D4(u8 *a)
{
    u16 *p = D_800ECF78;
    u16 t;

    *(u16 **)(a + 0xC) = p;
    *(u16 *)(a + 8) = p[0];
    t = p[1];
    a[7] = 0;
    *(u16 *)(a + 0xA) = t;
}

INCLUDE_ASM("asm/sop/nonmatchings/sop", func_8010A900);

INCLUDE_ASM("asm/sop/nonmatchings/sop", func_8010AB38);

INCLUDE_ASM("asm/sop/nonmatchings/sop", func_8010ACFC);

INCLUDE_ASM("asm/sop/nonmatchings/sop", func_8010AE30);

INCLUDE_ASM("asm/sop/nonmatchings/sop", func_8010AE9C);

INCLUDE_ASM("asm/sop/nonmatchings/sop", func_8010AF60);

INCLUDE_ASM("asm/sop/nonmatchings/sop", func_8010B078);

INCLUDE_ASM("asm/sop/nonmatchings/sop", func_8010B11C);

INCLUDE_ASM("asm/sop/nonmatchings/sop", func_8010B2D4);

INCLUDE_ASM("asm/sop/nonmatchings/sop", func_8010B44C);

INCLUDE_ASM("asm/sop/nonmatchings/sop", func_8010B498);

INCLUDE_ASM("asm/sop/nonmatchings/sop", func_8010B4E0);

INCLUDE_ASM("asm/sop/nonmatchings/sop", func_8010B588);

INCLUDE_ASM("asm/sop/nonmatchings/sop", func_8010B798);

INCLUDE_ASM("asm/sop/nonmatchings/sop", func_8010B8AC);

INCLUDE_ASM("asm/sop/nonmatchings/sop", func_8010B990);

INCLUDE_ASM("asm/sop/nonmatchings/sop", func_8010BAF8);

extern s32 D_800ECF80;
extern M2C_UNK D_8010D490;
void func_8010BC8C(void *arg0) {
    u8 temp_v1;
    void *temp_s0;

    temp_v1 = M2C_FIELD(arg0, u8 *, 4);
    switch (temp_v1) {                              /* irregular */
    case 0:
        M2C_FIELD(arg0, u8 *, 4) = 1U;
        if (M2C_FIELD(arg0, u8 *, 3) == 0) {
            temp_s0 = M2C_FIELD(arg0, void **, 0x10);
            M2C_FIELD(arg0, s32 *, 0x3C) = (s32) D_800ECF80;
            func_80077B38(arg0, &D_8010D490, 0);
            M2C_FIELD(arg0, s8 *, 0xD) = 0;
            M2C_FIELD(arg0, s16 *, 0x5C) = 0;
            M2C_FIELD(arg0, s8 *, 0xB) = 0x10;
            M2C_FIELD(arg0, s16 *, 0x5A) = 0;
            M2C_FIELD(arg0, s8 *, 0x47) = 0;
            M2C_FIELD(arg0, s8 *, 8) = 0;
            M2C_FIELD(arg0, u16 *, 0x2E) = (u16) M2C_FIELD(M2C_FIELD(temp_s0, void **, 0xDC), u16 *, 0x2C);
            M2C_FIELD(arg0, s16 *, 0x32) = (s16) (M2C_FIELD(M2C_FIELD(temp_s0, void **, 0xDC), u16 *, 0x30) + 0x14);
            M2C_FIELD(arg0, s16 *, 0x36) = (s16) (M2C_FIELD(M2C_FIELD(temp_s0, void **, 0xDC), u16 *, 0x34) - 0x50);
            return;
        }
    case 2:
        return;
    case 1:
        if (M2C_FIELD(arg0, u8 *, 3) == 0) {
            func_8010BAF8(arg0);
            return;
        }
        break;
    case 3:
        func_8007A624(arg0);
        break;
    }
}

INCLUDE_ASM("asm/sop/nonmatchings/sop", func_8010BDB8);

INCLUDE_ASM("asm/sop/nonmatchings/sop", func_8010BE04);

INCLUDE_ASM("asm/sop/nonmatchings/sop", func_8010BEAC);

INCLUDE_ASM("asm/sop/nonmatchings/sop", func_8010BF54);

INCLUDE_ASM("asm/sop/nonmatchings/sop", func_8010BFFC);

INCLUDE_ASM("asm/sop/nonmatchings/sop", func_8010C26C);

INCLUDE_ASM("asm/sop/nonmatchings/sop", func_8010C678);

INCLUDE_ASM("asm/sop/nonmatchings/sop", func_8010C6A0);

INCLUDE_ASM("asm/sop/nonmatchings/sop", func_8010C79C);

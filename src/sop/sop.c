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

extern u8 D_800E8008[];

void func_801097E4(void)
{
    u8 *c = D_800E8008;

    switch (c[0]) {
    case 0:
        c[0] = 1;
        c[0x64] = 0;
        break;
    case 1:
        switch (c[0x64]) {
        case 0:
            func_8006E3B0(c, c + 0x38);
            break;
        case 1:
            c[0x64] = 0;
            break;
        }
        break;
    }
}

typedef struct {
    s16 x, y, z;
    s16 pad;
    void *fn;
} SpawnDef;
extern SpawnDef D_8010C98C[];

void func_80109860(void)
{
    s32 i;
    u8 *r;
    SpawnDef *d;

    d = D_8010C98C;
    for (i = 0; i < 3; i++) {
        r = func_8007A980(3, 3, 1);
        *(s16 *)(r + 0x2E) = d->x;
        *(s16 *)(r + 0x32) = d->y;
        *(s16 *)(r + 0x36) = d->z;
        *(void **)(r + 0x1C) = d->fn;
        d++;
    }
}

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

extern u8 *D_1F800138_5432;

void func_80109934(void)
{
    u8 *p = D_1F800138_5432;

    switch (*(u16 *)(p + 0x52)) {
    case 0:
        *(s16 *)(p + 0x62) = 0;
        func_8001D71C(0xE);
        (*(s16 *)(D_1F800138_5432 + 0x52))++;
        break;
    case 1:
        if (func_8010C79C() != 0) {
            (*(s16 *)(D_1F800138_5432 + 0x52))++;
        }
        break;
    case 2:
        break;
    }
}

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

void func_8010AB38();
extern u8 D_8002AB5C[];

u8 *func_8010AE30(void *a)
{
    u8 *r = func_8007A980(0, 6, 1);

    if (r == NULL) {
        return NULL;
    }
    *(void **)(r + 0x1C) = func_8010AB38;
    r[0xB] = 0x20;
    *(void **)(r + 0x10) = a;
    *(void **)(r + 0x18) = D_8002AB5C;
    r[0x28] |= 0x80;
    return r;
}

INCLUDE_ASM("asm/sop/nonmatchings/sop", func_8010AE9C);

INCLUDE_ASM("asm/sop/nonmatchings/sop", func_8010AF60);

extern u8 D_8010C974[];
extern u8 D_800BF80F;

s32 func_8010B078(u8 *a)
{
    switch (a[0x78]) {
    case 0:
        D_800BF9B4 = 5;
        func_8006CBD0(D_800E8008, D_8010C974);
        *(s16 *)(a + 0x42) = 10;
        a[0x78]++;
        goto end;
    case 1:
        if (--*(s16 *)(a + 0x42) == 0) {
            D_800BF80F = 1;
            return 1;
        }
    end:
    default:
        return 0;
    }
}

INCLUDE_ASM("asm/sop/nonmatchings/sop", func_8010B11C);

INCLUDE_ASM("asm/sop/nonmatchings/sop", func_8010B2D4);

void func_8010B2D4();
void func_8010BC8C();

u8 *func_8010B44C(void *a)
{
    u8 *r = func_80072DDC(a, 3, 3, 0x1A);

    if (r != NULL) {
        *(void **)(r + 0x1C) = func_8010B2D4;
        *(void **)(r + 0x10) = a;
    }
    return r;
}

extern u8 D_8001B860[];

s32 func_8010B498(u8 *a)
{
    *(s16 *)(a + 0x2E) = 0x3E80;
    *(s16 *)(a + 0x32) = -0xF30;
    *(s16 *)(a + 0x36) = 0x4EB5;
    *(s16 *)(a + 0x56) = 0x800;
    func_80077C40(a, D_8001B860, 0);
    return 1;
}

extern u8 D_8010CAB8[];
extern void *D_800ECF80_1c35;
extern u8 D_8010D490_65f3[];

void func_8010B4E0(u8 *a)
{
    switch (a[5]) {
    case 0:
        if (func_8010B11C() != 0) {
            a[5]++;
            func_80040CDC(a, D_8001B860, D_8010CAB8);
            a[0x70] = 1;
        }
        break;
    case 1:
        func_80041098(a);
        if (a[0x70] == 0xFF) {
            a[5]++;
        }
        break;
    case 2:
        break;
    }
}

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

u8 *func_8010BDB8(void *a)
{
    u8 *r = func_80072DDC(a, 0, 3, 0x1E);

    if (r != NULL) {
        *(void **)(r + 0x1C) = func_8010BC8C;
        *(void **)(r + 0x10) = a;
    }
    return r;
}

void func_8010BE04(u8 *a)
{
    u8 *o = *(u8 **)(a + 0x10);

    *(void **)(a + 0x3C) = D_800ECF80_1c35;
    func_80077B38(a, D_8010D490_65f3, 0);
    a[0xD] = 0;
    *(s16 *)(a + 0x5C) = 0;
    a[0xB] = 0x10;
    *(s16 *)(a + 0x5A) = 0;
    a[0x47] = 0;
    a[8] = 0;
    *(s16 *)(a + 0x2E) = *(s16 *)(*(u8 **)(o + 0xDC) + 0x2C);
    *(s16 *)(a + 0x32) = *(s16 *)(*(u8 **)(o + 0xDC) + 0x30) + 0x14;
    *(s16 *)(a + 0x36) = *(s16 *)(*(u8 **)(o + 0xDC) + 0x34) - 0x50;
}

void func_8010BEAC(u8 *a)
{
    s16 *q = (s16 *)(a + 0x50);

    switch (a[4]) {
    case 0:
        a[4] = 1;
        *(s16 *)(a + 0x48) = 0x400;
        *(s16 *)(a + 0x4A) = 0;
        *(s32 *)(a + 0x4C) = 0;
        *(s16 *)(a + 0x50) = 0;
    case 1:
        a[1] = 1;
        *(s16 *)(a + 0x4E) -= 0x20;
        if ((*q -= 9) < 0) {
            *q += 0x54;
        }
        break;
    case 2:
    case 3:
        func_8007A624(a);
        break;
    }
}

typedef struct {
    u8 b[4];
} Bytes4;
extern Bytes4 D_80108FF0;
extern s32 D_1F800090;
extern u8 D_8010CC08[];

void func_8010BF54(u8 *a)
{
    Bytes4 v = D_80108FF0;
    s16 *q = (s16 *)(a + 0x50);
    s32 i;

    D_1F800090 = 0;
    for (i = 0; i < 2; i++) {
        func_80031D24(a + 0x2C, &v, a + 0x48);
        func_80027768(D_8010CC08, 0, 0, *q);
        *(s16 *)(a + 0x4E) += 0x800;
    }
}

INCLUDE_ASM("asm/sop/nonmatchings/sop", func_8010BFFC);

INCLUDE_ASM("asm/sop/nonmatchings/sop", func_8010C26C);

extern u8 D_8010D390[];

void func_8010C678(void)
{
    s32 i = 2;
    u8 *p = D_8010D390 + i;

    for (; i >= 0; i--) {
        *p-- = 0;
    }
}

INCLUDE_ASM("asm/sop/nonmatchings/sop", func_8010C6A0);

INCLUDE_ASM("asm/sop/nonmatchings/sop", func_8010C79C);

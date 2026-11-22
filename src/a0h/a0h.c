#include "common.h"
#include "game.h"
#include "m2c.h"

INCLUDE_ASM("asm/a0h/nonmatchings/a0h", func_801090DC);

INCLUDE_ASM("asm/a0h/nonmatchings/a0h", func_801092D4);

INCLUDE_ASM("asm/a0h/nonmatchings/a0h", func_801094F8);

extern u8 **D_1F80013C;
extern u8 D_1F800144;
extern u8 D_1F800182_5650;
extern u8 D_1F800183;
extern u8 D_1F800182_5650;
extern u8 D_1F800182_5650;
extern u8 D_1F800182_5650;
extern u8 D_1F800182_5650;
extern u8 D_1F800182_5650;

void func_8010963C(void)
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
            for (D_1F800182_5650 = D_1F800183; D_1F800182_5650 != 0; D_1F800182_5650--) {
            }
        }
    }
}

INCLUDE_ASM("asm/a0h/nonmatchings/a0h", func_801096E8);

INCLUDE_ASM("asm/a0h/nonmatchings/a0h", f_DispatchStrengthTowerTombaContacts);

extern u16 D_800BF812;

void func_80109CC4(u8 *a)
{
    u16 limit = D_800BF812;

    if (!(a[0x145] & 1)) {
        if (*(s16 *)(a + 0x32) >= (s16)limit - *(s16 *)(a + 0x62)) {
            *(u16 *)(a + 0x32) = limit - *(u16 *)(a + 0x62);
            func_80022C78(a);
        }
    }
}

extern u8 D_800BF808[];

void func_80109D24(u8 *a)
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

extern s8 D_1F800182[];

void func_80109D94(void *arg0, void *arg1) {
    if (func_80022F04() != 0) {
        if (func_8001E860(arg0, arg1, 0, 0x100) & 0x80) {
            M2C_FIELD(arg0, s8 *, 0x2B) = 2;
            M2C_FIELD(arg1, s8 *, 0) = 2;
            M2C_FIELD(arg1, s8 *, 4) = 2;
            M2C_FIELD(arg1, s8 *, 5) = 6;
            M2C_FIELD(arg1, s8 *, 6) = 0;
        }
        M2C_FIELD(arg1, s8 *, 0x2B) = 1;
        *((s8 *)D_1F800182) = 0;
    }
}

extern u8 D_1F800150;

void func_80109E10(u8 *a)
{
    u8 **l;
    u8 *e;

    for (D_1F800182_5650 = D_1F800150; D_1F800182_5650 != 0; D_1F800182_5650--) {
    }
    l = D_1F80013C;
    D_1F800182_5650 = D_1F800144;
    while (D_1F800182_5650 != 0) {
        e = *l;
        D_1F800182_5650--;
        l++;
        if ((e[0] & 1) && e[2] == 8) {
            func_8002423C(a, e);
        }
    }
}

extern u8 **D_1F80013C;
extern u8 D_1F800144;
extern u8 D_1F800182_5650;

void func_80109EE8(void *a)
{
    u8 **l = D_1F80013C;
    u8 *e;

    D_1F800182_5650 = D_1F800144;
    while (D_1F800182_5650 != 0) {
        e = *l;
        D_1F800182_5650--;
        l++;
        if (e[0] & 1) {
            if (e[0xC] == 9) {
                func_801090DC(a, e);
            } else if (e[2] == 8) {
                func_800205CC(a, e);
            }
        }
    }
}

INCLUDE_ASM("asm/a0h/nonmatchings/a0h", func_80109FAC);

INCLUDE_ASM("asm/a0h/nonmatchings/a0h", func_8010A0AC);

extern u8 D_1F800152;
extern u8 D_1F800182_5650;
extern s32 D_1F800080;

s32 func_8010A1AC(void)
{
    for (D_1F800182_5650 = D_1F800152; D_1F800182_5650 != 0; D_1F800182_5650--) {
    }
    return D_1F800080;
}


void func_8010A1E4(void *arg0) {
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

typedef struct {
    s16 pad0;
    s16 x;
    s16 pad4;
    s16 y;
    s16 pad8;
    s16 z;
} HiPos;
extern u8 D_800E7E80[];
extern u8 D_1F8000D0[];

void func_8010A248(u8 *a)
{
    u8 *t = D_800E7E80;
    HiPos v;
    u8 *c;

    switch (a[2]) {
    case 0:
        c = D_1F8000D0;
        *(s16 *)(a + 0x56) = 0;
        *(s16 *)(c + 0x1E) = -0xABE;
        a[2]++;
        *(s16 *)(c + 0x2) = 0xC0A;
        *(s16 *)(c + 0x6) = -0x1558;
        *(s16 *)(c + 0xA) = 0x12C1;
    case 1:
        a[0x64] &= 0x7F;
        if (t[0x2A] == 9) {
            a[0x64] |= 0x80;
            *(s16 *)(a + 0xA) = *(s16 *)(t + 0x2E);
            *(s16 *)(a + 0xE) = *(s16 *)(t + 0x32);
            *(s16 *)(a + 0x12) = *(s16 *)(t + 0x36);
            func_8006E3F4(a, t + 0x2C);
            v.x = 0xC0A;
            v.y = -0x1558;
            v.z = 0x12C1;
            func_8006CEC4(D_1F8000D0, &v, 0xE0);
        }
        break;
    }
}

INCLUDE_ASM("asm/a0h/nonmatchings/a0h", func_8010A33C);

extern u8 D_800BF816;
extern u8 D_800E806C;
extern s32 D_1F800184;

void func_8010A39C(void)
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

INCLUDE_ASM("asm/a0h/nonmatchings/a0h", f_UpdateStrengthTowerExitDoorSequence);

INCLUDE_ASM("asm/a0h/nonmatchings/a0h", func_8010A574);


s32 func_8010A854(u8 *a, s16 id)
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

INCLUDE_ASM("asm/a0h/nonmatchings/a0h", func_8010A918);

INCLUDE_ASM("asm/a0h/nonmatchings/a0h", func_8010ABE8);

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
extern Spawn *D_8010C60C[];
extern Pos D_800BF808_76d5;
typedef struct { u8 x, y, z; s8 t; } Spark;
typedef struct { s16 a, b, c, d; } S8;
typedef struct { s16 x, y, z, pad; } SV;
typedef struct { s16 x, y, z; } V3;
typedef struct { s16 x, y, z, pad; } SVec;
typedef struct { u16 x, p0, y, p1, z, p2; } LVec;
typedef struct { u16 a, b; } Range;

void func_8010ACF8(Owner *a, s32 sel)
{
    Spawn *e;
    u8 *p;
    a->count = 0;
    e = D_8010C60C[sel];
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

extern u8 D_800BF917;
void func_8010AE70(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 4);
    switch (temp_v1) {                              /* irregular */
    case 0:
        M2C_FIELD(arg0, u8 *, 4) = 1U;
        func_8010ACF8(arg0, 0U);
        func_8004D8D8(0xE, 0);
        func_800752B4(0);
        func_80075D24(0x1FFF);
        return;
    case 1:
        if (func_80026AD0(arg0) != 0) {
            func_8010ACF8(arg0, M2C_FIELD(arg0, u8 *, 3));
        }
        if (D_800BF917 != 0xFF) {
            func_80040C00(0x63);
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

INCLUDE_ASM("asm/a0h/nonmatchings/a0h", func_8010AF58);

INCLUDE_ASM("asm/a0h/nonmatchings/a0h", func_8010B240);

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

void func_8010B5BC(PartList *a)
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
        r = func_8010AF58(e + 1, ot, v & 0xFF);
        v >>= 16;
        func_8010B240(r, ot, v & 0xFF);
    }
}

INCLUDE_ASM("asm/a0h/nonmatchings/a0h", func_8010B6BC);

INCLUDE_ASM("asm/a0h/nonmatchings/a0h", func_8010B960);


void func_8010BC94(u32 *p, void *b)
{
    u32 lo = *p;
    u32 packed;

    packed = lo;
    lo = packed & 0xFFFF;
    p += 4;
    func_8010B960(func_8010B6BC(p, b, lo), b, packed >> 16);
}

INCLUDE_ASM("asm/a0h/nonmatchings/a0h", func_8010BCDC);

INCLUDE_ASM("asm/a0h/nonmatchings/a0h", func_8010BFBC);

extern u16 *D_800ECF78;

void func_8010C4FC(u8 *a)
{
    u16 *p = D_800ECF78;
    u16 t;

    *(u16 **)(a + 0xC) = p;
    *(u16 *)(a + 8) = p[0];
    t = p[1];
    a[7] = 0;
    *(u16 *)(a + 0xA) = t;
}

INCLUDE_ASM("asm/a0h/nonmatchings/a0h", f_UpdateStrengthTowerInteriorEntranceActor);

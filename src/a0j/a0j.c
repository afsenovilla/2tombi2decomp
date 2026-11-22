#include "common.h"
#include "game.h"
#include "m2c.h"

INCLUDE_ASM("asm/a0j/nonmatchings/a0j", func_801090C4);

INCLUDE_ASM("asm/a0j/nonmatchings/a0j", func_80109238);

INCLUDE_ASM("asm/a0j/nonmatchings/a0j", func_8010945C);

INCLUDE_ASM("asm/a0j/nonmatchings/a0j", func_801095A0);

INCLUDE_ASM("asm/a0j/nonmatchings/a0j", f_DispatchGoldenTowerTombaContacts);

extern u16 D_800BF812;

void func_80109AD4(u8 *a)
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

void func_80109B34(u8 *a)
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

extern u8 D_1F800150;
extern u8 D_1F800182;
extern u8 D_1F800144;
extern u8 **D_1F80013C;

void func_80109BA4(u8 *a)
{
    u8 **l;
    u8 *e;

    for (D_1F800182 = D_1F800150; D_1F800182 != 0; D_1F800182--) {
    }
    l = D_1F80013C;
    D_1F800182 = D_1F800144;
    while (D_1F800182 != 0) {
        e = *l;
        D_1F800182--;
        l++;
        if ((e[0] & 1) && e[2] == 8) {
            func_8002423C(a, e);
        }
    }
}


void func_80109C7C(void *a)
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
                func_801090C4(a, e);
            } else if (e[2] == 8) {
                func_800205CC(a, e);
            }
        }
    }
}

INCLUDE_ASM("asm/a0j/nonmatchings/a0j", func_80109D40);

INCLUDE_ASM("asm/a0j/nonmatchings/a0j", func_80109E40);


s32 func_80109F40(void) {
    return *(s32 *)0x1F800080;
}


void func_80109F50(void *arg0) {
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

INCLUDE_ASM("asm/a0j/nonmatchings/a0j", func_80109FB4);

extern u8 D_800BF816;
extern s32 D_1F800184;
extern u16 D_1F800210;
typedef struct {
    u8 pad0[5];
    u8 x5;
    u8 x6;
    u8 pad7[0x139];
    u16 x140;
    u8 pad142[0x29];
    u8 x16B;
} Area7E80;
extern Area7E80 D_800E7E80_eac2;

void func_8010A0BC(void)
{
    func_80054198(&D_800E7E80_eac2);
    D_800BF816 = 1;
    D_1F800184 = 0;
    D_800E7E80_eac2.x5 = 0x24;
    D_800E7E80_eac2.x6 = 0;
    D_800E7E80_eac2.x16B = 8;
    D_1F800210 = D_800E7E80_eac2.x140;
}

extern u16 *D_800ECF78;
extern u8 D_800E806C;
extern u8 D_800E7E80[];
extern void *D_800ECF80;
extern u8 D_8010D8AC[];
void func_8010CA1C();

void func_8010A11C(void)
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
extern Spawn *D_8010D504[];
extern Pos D_800BF808_76d5;
typedef struct { u8 x, y, z; s8 t; } Spark;
typedef struct { s16 a, b, c, d; } S8;
typedef struct { s16 x, y, z, pad; } SV;
typedef struct { s16 x, y, z; } V3;
typedef struct { s16 x, y, z, pad; } SVec;
typedef struct { u16 x, p0, y, p1, z, p2; } LVec;
typedef struct { u16 a, b; } Range;

void func_8010A174(Owner *a, s32 sel)
{
    Spawn *e;
    u8 *p;
    a->count = 0;
    e = D_8010D504[sel];
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


void func_8010A2EC(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 4);
    switch (temp_v1) {                              /* irregular */
    case 0:
        M2C_FIELD(arg0, u8 *, 4) = 1U;
        func_8010A174(arg0, 0U);
        func_800752B4(0);
        func_80075D24(0x1FFF);
        return;
    case 1:
        if (func_80026AD0(arg0) != 0) {
            func_8010A174(arg0, M2C_FIELD(arg0, u8 *, 3));
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

INCLUDE_ASM("asm/a0j/nonmatchings/a0j", func_8010A3AC);

INCLUDE_ASM("asm/a0j/nonmatchings/a0j", func_8010A69C);

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

void func_8010AA20(PartList *a)
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
        r = func_8010A3AC(e + 1, ot, v & 0xFF);
        v >>= 16;
        func_8010A69C(r, ot, v & 0xFF);
    }
}

INCLUDE_ASM("asm/a0j/nonmatchings/a0j", func_8010AB20);

INCLUDE_ASM("asm/a0j/nonmatchings/a0j", func_8010ADC4);


void func_8010B0F8(u32 *p, void *b)
{
    u32 lo = *p;
    u32 packed;

    packed = lo;
    lo = packed & 0xFFFF;
    p += 4;
    func_8010ADC4(func_8010AB20(p, b, lo), b, packed >> 16);
}

INCLUDE_ASM("asm/a0j/nonmatchings/a0j", func_8010B140);

INCLUDE_ASM("asm/a0j/nonmatchings/a0j", func_8010B420);


void func_8010B960(u8 *a)
{
    u16 *p = D_800ECF78;
    u16 t;

    *(u16 **)(a + 0xC) = p;
    *(u16 *)(a + 8) = p[0];
    t = p[1];
    a[7] = 0;
    *(u16 *)(a + 0xA) = t;
}

INCLUDE_ASM("asm/a0j/nonmatchings/a0j", func_8010B98C);

INCLUDE_ASM("asm/a0j/nonmatchings/a0j", func_8010BAD8);

INCLUDE_ASM("asm/a0j/nonmatchings/a0j", func_8010BC8C);

INCLUDE_ASM("asm/a0j/nonmatchings/a0j", f_UpdateGoldenTowerPigElderActor);


s32 func_8010C1D4(void *a)
{
    u8 *r = func_80072DDC(a, 0, 3, 0x10);

    if (r != NULL) {
        *(void **)(r + 0x1C) = func_8010CA1C;
        r[3] = 2;
    }
    return 1;
}

extern s32 D_800BF850;
void func_8010C218(void) {
    D_800BF850 = 1;
}

extern s32 D_800BF850;
s32 func_8010C228(void) {
    D_800BF850 = 2;
    return 1;
}

typedef struct {
    s16 pad0;
    s16 x;
    s16 pad4;
    s16 y;
    s16 pad8;
    s16 z;
} HiPos;
extern u8 D_800E8008[];
extern s16 D_1F800160;
extern s16 D_1F800162;
extern s16 D_1F800164;
extern u8 D_1F8000D0[];

s32 func_8010C23C(u8 *a)
{
    u8 *c = D_800E8008;
    HiPos v;

    switch (a[0x78]) {
    case 0:
        func_8006E1C0(a[3] | 0x80);
        a[0x78]++;
        goto end;
    case 1:
        *(s16 *)(c + 0xA) = D_1F800160;
        *(s16 *)(c + 0xE) = D_1F800162;
        *(s16 *)(c + 0x12) = D_1F800164;
        func_8006E3F4(c, c + 8);
        v.x = 0x1103;
        v.y = -0x2203;
        v.z = 0x1137;
        if (func_8006CEC4(D_1F8000D0, &v, 0xE0) != 0) {
            c[0x66] = 3;
            return 1;
        }
    end:
    default:
        return 0;
    }
}

extern u8 D_8010D904[];
extern u8 D_8010D5F4[];

s32 func_8010C320(u8 *a)
{
    switch (a[6]) {
    case 0:
        if (a[0x2B] != 3) {
            return 0;
        }
        a[6]++;
        func_80042354(1, 2);
        func_80040CDC(a, D_8010D904, D_8010D5F4);
        a[0x70] = 1;
        break;
    case 1:
        func_80041098(a);
        if (a[0x70] != 0xFF) {
            return 0;
        }
        a[6] = 0;
        func_80042310();
        return 1;
    }
    return 0;
}

extern u8 D_8010D6DC[];

s32 func_8010C3D4(u8 *a)
{
    switch (a[6]) {
    case 0:
        if (a[0x2B] != 3) {
            return 0;
        }
        a[6]++;
        func_80042354(1, 2);
        func_80040CDC(a, D_8010D904, D_8010D6DC);
        a[0x70] = 1;
        break;
    case 1:
        func_80041098(a);
        if (a[0x70] != 0xFF) {
            return 0;
        }
        a[6] = 0;
        func_80042310();
        return 1;
    }
    return 0;
}

extern u8 D_8010D7B4[];

s32 func_8010C488(u8 *a)
{
    switch (a[6]) {
    case 0:
        if (a[0x2B] != 3) {
            return 0;
        }
        a[6]++;
        func_80042354(1, 2);
        func_80040CDC(a, D_8010D904, D_8010D7B4);
        a[0x70] = 1;
        break;
    case 1:
        func_80041098(a);
        if (a[0x70] != 0xFF) {
            return 0;
        }
        a[6] = 0;
        func_80042310();
        return 1;
    }
    return 0;
}

extern u8 D_8010D7E4[];

s32 func_8010C53C(u8 *a)
{
    switch (a[6]) {
    case 0:
        if (a[0x2B] != 3) {
            return 0;
        }
        a[6]++;
        func_80042354(1, 2);
        func_80040CDC(a, D_8010D904, D_8010D7E4);
        a[0x70] = 1;
        break;
    case 1:
        func_80041098(a);
        if (a[0x70] != 0xFF) {
            return 0;
        }
        a[6] = 0;
        func_80042310();
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/a0j/nonmatchings/a0j", func_8010C5F0);


s32 func_8010C958(u8 *a, s16 id)
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

INCLUDE_ASM("asm/a0j/nonmatchings/a0j", func_8010CA1C);


void func_8010CDCC(u8 *a)
{
    u8 *r;

    func_80051B70(a, 0xC, 0);
    a[0xD] |= 4;
    (*(u8 **)(a + 0xC0))[0x3F] = 0xE0;
    func_800517F8(a);
    r = func_80072DDC(a, 1, 3, 0x10);
    if (r != NULL) {
        r[3] = 1;
        *(void **)(r + 0x1C) = func_8010CA1C;
        *(s16 *)(r + 0x2E) = *(s16 *)(a + 0x2E);
        *(s16 *)(r + 0x32) = *(s16 *)(a + 0x32);
        *(s16 *)(r + 0x36) = *(s16 *)(a + 0x36);
    }
}


void func_8010CE6C(void) {
    func_8007778C();
}

extern void *D_800ECF80;
extern u8 D_8010D8AC[];

void func_8010CE8C(u8 *a)
{
    *(void **)(a + 0x3C) = D_800ECF80;
    func_80077B38(a, D_8010D8AC, 5);
    a[0xD] = 1;
    a[0xB] = 0x10;
    *(s16 *)(a + 0x5C) = 0;
    *(s16 *)(a + 0x5A) = 0;
    a[0x47] = 0;
    a[8] = 0xC0;
}


void func_8010CEEC(void *arg0) {
    u8 temp_v0;

    temp_v0 = M2C_FIELD(M2C_FIELD(arg0, void **, 0x10), u8 *, 1);
    M2C_FIELD(arg0, u8 *, 1) = temp_v0;
    if (temp_v0 & 0xFF) {
        func_8010D1F0();
    }
    func_80077B5C(arg0);
}


void func_8010CF3C(u8 *a)
{
    *(void **)(a + 0x3C) = D_800ECF80;
    func_80077B38(a, D_8010D8AC, 6);
    a[0xD] = 0;
    *(s16 *)(a + 0x5C) = 0;
    a[0xB] = 0x10;
    *(s16 *)(a + 0x5A) = 0;
    a[0x47] = 0;
    a[8] = 0;
}

INCLUDE_ASM("asm/a0j/nonmatchings/a0j", func_8010CF94);


void func_8010D094(u8 *a)
{
    u8 *o = *(u8 **)(a + 0x10);

    *(void **)(a + 0x3C) = D_800ECF80;
    func_80077B38(a, D_8010D8AC, 4);
    a[0xB] = 0x10;
    a[0xD] = 0;
    *(s16 *)(a + 0x5C) = 0;
    *(s16 *)(a + 0x5A) = 0;
    a[0x47] = 0;
    a[8] = 0xE0;
    *(s16 *)(a + 0x2E) = *(s16 *)(o + 0x2E);
    *(s16 *)(a + 0x32) = *(s16 *)(o + 0x32) - 0x118;
    *(s16 *)(a + 0x36) = *(s16 *)(o + 0x36);
}


void func_8010D124(void *arg0) {
    if (D_800BF870.pad1[0x29B] != 0) {
        M2C_FIELD(arg0, s8 *, 4) = 3;
        M2C_FIELD(&D_800BF870, s8 *, 0x5E5) = 1;
    }
    M2C_FIELD(arg0, s8 *, 1) = 1;
}

typedef struct { u16 start; u16 len; } AudioSeg;
extern AudioSeg D_8010D83C[];
extern AudioSeg D_8010D854[];
extern s32 D_1F80021C;

void func_8010D154(s16 a, s16 i)
{
    AudioSeg *t;
    s32 ch, off, p;
    switch (a) {
    case 0:
        t = D_8010D83C;
        ch = 3;
        off = 0;
        break;
    case 1:
        t = D_8010D854;
        ch = 0x11;
        off = 0x31C;
        break;
    default:
        return;
    }
    p = D_1F80021C + t[i].start * 32 + off * 32;
    func_8001D2A8(ch, p, p + (t[i].len + 1) * 32, 0);
}

#define gte_ldv0(r0) __asm__ volatile("lwc2	$0, 0( %0 );" "lwc2	$1, 4( %0 )" : : "r"(r0))
extern u8 D_800BF873;
extern s32 D_1F800084;
extern s32 D_1F800088;

void func_8010D1F0(u8 *a)
{
    SV v;
    s32 r;
    if (D_800BF873 == 0) {
        v.x = *(s16 *)(a + 0x2E);
        v.y = *(s16 *)(a + 0x32);
        v.z = *(s16 *)(a + 0x36);
        func_800329E0(6);
        gte_ldv0(&v);
        if (func_800317CC(-0x20) == 0) {
            D_1F800088 = D_1F800084;
            r = (func_8009A450() & 0x3F) + 0x40;
            func_8002E680(0, 0x40, r | (r << 8), 0);
        }
    }
}

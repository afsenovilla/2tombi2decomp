#include "common.h"
#include "game.h"
#include "m2c.h"

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_801092BC);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_801093F4);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80109630);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80109ACC);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80109F7C);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8010A3D0);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8010A550);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8010A6E0);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8010A93C);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8010ACA8);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8010AE50);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8010B010);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8010B128);

extern s8 D_800BF808[];

void func_8010B444(u8 *a)
{
    u16 v;
    s32 m;
    if (D_800BF808[5] == 0) {
        v = *(u16 *)(a + 0x6A);
        m = v & 0xF00;
        if (v & 0x8000) {
            *(u16 *)(a + 0x6A) = 0;
            D_800BF808[0x16] = 0;
            if (m == 0x700) {
                a[0] = 3;
                a[4] = 2;
                a[5] = 5;
                a[6] = 0;
                a[7] = 0;
            } else if (m == 0x900) {
                a[0x2B] = (*(s16 *)(a + 0x56) + 0x800) >> 4;
                func_80022D08(a, 0, 1, 1);
            }
        }
    }
}

extern u8 D_1F800137;

void func_8010B4E4(u8 *a)
{
    u16 v;
    s32 m;
    if (D_1F800137 == 0 && D_800BF808[5] == 0) {
        v = *(u16 *)(a + 0x6A);
        m = v & 0xF00;
        if (v & 0x8000) {
            *(u16 *)(a + 0x6A) = 0;
            D_800BF808[0x16] = 0;
            if (m == 0x700) {
                a[0] = 3;
                a[4] = 2;
                a[5] = 5;
                a[6] = 0;
                a[7] = 0;
            } else if (m == 0x900) {
                a[0x2B] = (*(s16 *)(a + 0x56) + 0x800) >> 4;
                func_80022D08(a, 0, 1, 1);
            }
        }
    }
}

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8010B590);

extern u8 **D_1F800148;
extern u8 D_1F800150;
extern u8 D_1F800182;

void func_8010B680(u8 *a)
{
    u8 **l = D_1F800148;
    u8 *p;
    D_1F800182 = D_1F800150;
    while (D_1F800182 != 0) {
        p = *l;
        D_1F800182--;
        l++;
        if ((p[0] & 1) && p[2] == 8) {
            func_80109630(a, p, *(void **)(p + 0xC0));
        }
    }
}


s32 func_8010B734(void) {
    return 0;
}

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8010B73C);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8010B938);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8010BC10);

extern s8 D_1F80027E[];
extern u8 D_800BFA1A;

void func_8010BD50(void *arg0) {
    *((s8 *)D_1F80027E) = 1;
    func_8006F0E4();
    M2C_FIELD(arg0, s8 *, 1) = 1;
    func_80055D5C(arg0);
    M2C_FIELD(arg0, s16 *, 0x142) = 0;
    M2C_FIELD(arg0, s16 *, 0x58) = 0;
    func_80054198(arg0);
    func_80055284(arg0);
    func_80054D14(arg0, 2, 0);
    func_8003315C(arg0);
    if (!(D_800BFA1A & 2)) {
        func_80042354(1, 5);
        func_8001CF2C();
        M2C_FIELD(arg0, s8 *, 4) = 4;
    }
}


void func_8010BDF4(void *arg0) {
    s16 temp_a1;
    s16 temp_v0;
    s16 var_v0;
    s16 var_v1;

    temp_a1 = M2C_FIELD(arg0, s16 *, 0x44);
    var_v0 = temp_a1;
    if (temp_a1 < 0) {
        var_v0 = -var_v0;
    }
    temp_v0 = var_v0 - 0xE0;
    var_v1 = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        var_v1 = 0;
    }
    if (temp_a1 >= 0) {
        M2C_FIELD(arg0, s16 *, 0x44) = var_v1;
        return;
    }
    M2C_FIELD(arg0, s16 *, 0x44) = (s16) -var_v1;
}

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8010BE38);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8010BE80);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8010C0A4);


void func_8010C300(void) {
}


void func_8010C308(void) {
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
extern Spawn *D_801182B4[];
extern Pos D_800BF808_76d5;
typedef struct { u8 x, y, z; s8 t; } Spark;
typedef struct { s16 a, b, c, d; } S8;
typedef struct { s16 x, y, z, pad; } SV;
typedef struct { s16 x, y, z; } V3;
typedef struct { s16 x, y, z, pad; } SVec;
typedef struct { u16 x, p0, y, p1, z, p2; } LVec;
typedef struct { u16 a, b; } Range;

void func_8010C310(Owner *a, s32 sel)
{
    Spawn *e;
    u8 *p;
    a->count = 0;
    e = D_801182B4[sel];
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


void func_8010C488(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 4);
    switch (temp_v1) {                              /* irregular */
    case 0:
        M2C_FIELD(arg0, u8 *, 4) = 1U;
        func_8010C310(arg0, 0U);
        func_800310F4(0xC05, 0);
        func_800752B4(1);
        func_80075D24(0x1FFF);
        return;
    case 1:
        if (func_80026AD0(arg0) != 0) {
            func_8010C310(arg0, M2C_FIELD(arg0, u8 *, 3));
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

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8010C554);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8010C778);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8010C948);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8010CA34);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8010CB44);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8010D1F0);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8010D884);

extern u8 D_800BF809;
extern s16 D_1F800160_71b4;
extern s16 D_1F800164_d75f;

void func_8010E0E8(u8 *a)
{
    s32 s;
    if (D_800BF809 != 0) {
        return;
    }
    switch (s = a[6]) {
    case 0:
        func_80041768(a, 0xB, 4);
        func_80074590(0x8A, 0, 0);
        *(s16 *)(a + 0x40) = 0x5A;
        a[6]++;
        break;
    case 1:
        if (*(s16 *)(a + 0x40) < 0x1E && func_8010C948(a) != 0) {
            a[0] = 2;
            func_80041768(a, 3, 4);
            func_8010CA34(a);
            a[5] = s;
            a[6] = s;
            a[7] = 0;
            break;
        }
        if (--*(s16 *)(a + 0x40) == 0) {
            func_80041768(a, 0, 0xA);
            a[5] = 0;
            a[6] = 0;
            *(s16 *)(a + 0x64) = 0;
        }
        *(s16 *)(a + 0x56) = func_800776F8((s16)func_800782B0(a + 0x2C, D_1F800160_71b4, D_1F800164_d75f), *(s16 *)(a + 0x56), 0x80);
        break;
    }
}

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8010E22C);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8010EF30);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8010F144);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8010F43C);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8010F544);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", f_UpdateLastEvilPigProjectileAttack);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8010FC1C);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80110118);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80110540);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_801106A4);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80110800);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80110A98);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_801110BC);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_801113B4);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8011159C);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80111770);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_8011199C);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80111AB0);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80111C5C);

extern S8 D_80124E20[];
extern s32 D_80124D80[];
extern u8 D_80124E00[];

void func_80111E00(u8 *a)
{
    s32 i;
    s32 c, g, b;
    for (i = 0; i < 0x20; i++) {
        c = ((0x20 - i) * a[5]) / 32 + 1;
        g = c - (c >> 4);
        b = c - (c >> 3);
        if (D_80124E20[i].d == 0) {
            D_80124D80[i] = 0;
            if (i != 0) {
                D_80124D80[i - 1] = 0;
            }
            if (i != 0x1F) {
                D_80124D80[i + 1] = 0;
            }
            break;
        }
        if (i < 2) {
            D_80124D80[i] = 0;
            D_80124E00[i] = 0x10;
        } else {
            D_80124D80[i] = (b << 16) | (g << 8) | c;
            D_80124E00[i] = 0x21 - i;
        }
    }
    func_80029664(D_80124E20, i, D_80124D80, D_80124E00);
}

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80111F18);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_801120AC);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_801121E8);

#define P(p, o) (*(void **)((u8 *)(p) + (o)))

void func_80112704(u8 *a)
{
    s16 v;
    switch (a[4]) {
    case 0:
        a[4] = 1;
        v = (func_8009A450() & 0x1FF) + 0x180;
        *(s16 *)(a + 0x4A) = v;
        *(s16 *)(a + 0x48) = v;
    case 1:
        if ((P(a, 0x34) = P(a, 0x38)) == 0) {
            a[4] = 2;
        } else if (func_8002B278(a) == 0) {
            func_80031780(a);
        }
        break;
    case 2:
    case 3:
        func_8007A624(a);
        break;
    }
}

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_801127BC);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80112880);


void func_80112974(u8 *a)
{
    switch (a[4]) {
    case 0:
        a[4]++;
        a[7] = 0;
        *(s32 *)(a + 0x48) = func_8009A450();
        *(s32 *)(a + 0x4C) = func_8009A450();
    case 1:
        if (++a[7] >= 0x10) {
            a[4] = 2;
        } else {
            a[1] = 1;
        }
        break;
    case 2:
    case 3:
        func_8007A624(a);
        break;
    }
}

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80112A24);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80112CF0);

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

void func_80113050(PartList *a)
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
        r = func_80112A24(e + 1, ot, v & 0xFF);
        v >>= 16;
        func_80112CF0(r, ot, v & 0xFF);
    }
}

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80113150);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_801133F4);


void func_80113728(u32 *p, void *b)
{
    u32 lo = *p;
    u32 packed;

    packed = lo;
    lo = packed & 0xFFFF;
    p += 4;
    func_801133F4(func_80113150(p, b, lo), b, packed >> 16);
}

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80113770);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80113A28);

extern u16 *D_800ECF78;

void func_80113F68(u8 *a)
{
    u16 *p = D_800ECF78;
    u16 t;

    *(u16 **)(a + 0xC) = p;
    *(u16 *)(a + 8) = p[0];
    t = p[1];
    a[7] = 0;
    *(u16 *)(a + 0xA) = t;
}

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80113F94);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_801141B0);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_801144F4);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80114608);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80114AA8);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80114CEC);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80114DE8);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80114ECC);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80115194);

extern Cam D_1F8000D0;
extern SVec D_1F8000C0;
extern LVec D_1F8000A0;
extern void *D_801245BC[];

s32 func_801153D4(u8 *a)
{
    switch (a[6]) {
    case 0:
        a[6]++;
        D_1F8000C0.x = 0;
        D_1F8000C0.y = -0x690;
        D_1F8000C0.z = 0x3E8;
        func_80084470(D_1F8000D0.m, &D_1F8000C0, &D_1F8000A0);
        *(u16 *)(a + 0x2E) = D_1F8000D0.pos[0].hi + D_1F8000A0.x;
        *(u16 *)(a + 0x32) = D_1F8000D0.pos[1].hi + D_1F8000A0.y;
        *(u16 *)(a + 0x36) = D_1F8000D0.pos[2].hi + D_1F8000A0.z;
        func_80040CDC(a, 0, D_801245BC[D_800BF870.unk0 - 10]);
        a[0x70] = 1;
        goto end;
    case 1:
        func_80041098(a);
        if (a[0x70] == 0xFF) {
            return 1;
        }
    end:
    default:
        return 0;
    }
}

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_801154F8);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_801158B8);

extern s8 D_1F800160[];
extern s8 D_1F800164[];
extern s8 D_1F800246[];
extern s8 D_1F80024C[];

void func_801159FC(void *arg0) {
    M2C_UNK var_a0;
    void *temp_s1;

    temp_s1 = *((void **)D_1F80024C);
    if (*((u8 *)D_1F800246) == 0) {
        M2C_FIELD(arg0, u8 *, 5) = 0U;
        M2C_FIELD(arg0, s8 *, 6) = 0;
        M2C_FIELD(arg0, s8 *, 7) = 2;
        M2C_FIELD(arg0, s16 *, 0x64) = 0;
        M2C_FIELD(arg0, u16 *, 0x56) = (u16) M2C_FIELD(arg0, u16 *, 0x62);
    } else {
        M2C_FIELD(arg0, u16 *, 0x56) = func_800776F8((s16) (func_800782B0(arg0 + 0x2C, *((s16 *)D_1F800160), *((s16 *)D_1F800164)) - 0x400), (s16) M2C_FIELD(arg0, u16 *, 0x56), 0x80);
        M2C_FIELD(M2C_FIELD(arg0, void **, 0xC0), s16 *, 8) = func_800776F8(0, M2C_FIELD(M2C_FIELD(arg0, void **, 0xC0), s16 *, 8), 0x80);
        func_80114ECC(arg0);
        if (M2C_FIELD(arg0, u8 *, 0x29) != 0) {
            var_a0 = 0x88;
            if (M2C_FIELD(temp_s1, s16 *, 0x6E) == 1) {
                var_a0 = 0x89;
            }
            func_80074590(var_a0, 0, 0);
            M2C_FIELD(arg0, s8 *, 6) = 0;
            M2C_FIELD(arg0, s16 *, 0x64) = 0;
            M2C_FIELD(arg0, s8 *, 7) = 3;
            M2C_FIELD(arg0, u8 *, 5) = (u8) (M2C_FIELD(arg0, u8 *, 5) + 1);
        }
    }
    M2C_FIELD(arg0, s16 *, 0x32) = (s16) (M2C_FIELD(arg0, u16 *, 0x7C) + (func_80083E80(M2C_FIELD(arg0, s16 *, 0x60)) >> 4));
    M2C_FIELD(arg0, s16 *, 0x60) = (s16) (((u16) M2C_FIELD(arg0, s16 *, 0x60) + 0x40) & 0xFFF);
}

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80115B28);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80115EEC);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_801163C4);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80116520);

extern u8 D_800E806E;

s32 func_801169E0(u8 *p)
{
    switch (p[0x78]) {
    case 0:
        p[0x78]++;
        func_8006E1C0(8);
        g_CameraState.focusX = *(u16 *)(p + 0x2E);
        g_CameraState.focusY = *(u16 *)(p + 0x32) + 0x4B0;
        g_CameraState.focusZ = *(u16 *)(p + 0x36);
        goto end;
    case 1:
        if (D_800E806E == 3) {
            return 1;
        }
    end:
    default:
        return 0;
    }
}

extern s16 D_80124448[];
extern s16 D_800E8046;

s32 func_80116A70(u8 *p)
{
    s16 y;

    switch (p[0x78]) {
    case 0:
        p[0x78]++;
        *(s32 *)(p + 0x38) = func_8003116C(D_80124448[D_800BF870.unk0 - 10], p + 0x2C, -0x32);
        goto end;
    case 1:
        y = *(u16 *)(p + 0x32) + 0x10;
        *(s16 *)(p + 0x32) = y;
        *(s16 *)(*(u8 **)(p + 0x38) + 0x2E) = y;
        if (*(s16 *)(p + 0x32) >= D_800E8046 - 0xF0) {
            return 1;
        }
    end:
    default:
        return 0;
    }
}


s32 func_80116B1C(void *arg0) {
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x38), s8 *, 4) = 2;
    func_80074590(0x37, 0x16, 0);
    return 1;
}

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80116B50);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_80116CB0);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", f_UpdateEvilPigBattleProjectile);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_801175B8);

extern s32 D_8012460C[];

void func_80117720(u8 *a)
{
    func_80051B04(*(void **)(a + 0xC0), 0xC, D_8012460C[a[0x5E] - 1]);
    func_80074590(0x8D, 0, 0);
}


u8 func_80117774(u8 *a)
{
    s16 *p = (s16 *)(a + 0x60);
    s16 v;
    if (a[0x5F] == 0) {
        if (*(s16 *)(a + 0x44) >= 0) {
            v = *(s16 *)(a + 0x80);
        } else {
            v = -*(s16 *)(a + 0x80);
        }
        if (func_80045CAC(a, v, 0, *p) != 0) {
            a[0x5F] = a[0xBE] | 4;
        }
    }
    return a[0x5F];
}


void func_80117800(void *arg0) {
    s16 temp_s0;
    s32 temp_lo;
    s32 temp_s2;

    if (M2C_FIELD(arg0, u8 *, 0x5F) == 0) {
        temp_s0 = M2C_FIELD(arg0, s16 *, 0x60);
        temp_s2 = func_80083F50(temp_s0) * M2C_FIELD(arg0, s16 *, 0x44);
        temp_lo = -func_80083E80(temp_s0) * M2C_FIELD(arg0, s16 *, 0x44);
        M2C_FIELD(arg0, s32 *, 0x2C) = (s32) (M2C_FIELD(arg0, s32 *, 0x2C) + temp_s2);
        M2C_FIELD(arg0, s32 *, 0x34) = (s32) (M2C_FIELD(arg0, s32 *, 0x34) + temp_lo);
    }
    M2C_FIELD(arg0, s32 *, 0x30) = (s32) (M2C_FIELD(arg0, s32 *, 0x30) + (M2C_FIELD(arg0, s16 *, 0x50) << 0xC));
}

extern Range D_80124C94[];
extern Range D_80124CAC[];
extern Range D_80124CD0[];
extern Range D_80124D08[];
extern u8 *D_1F80021C;

void func_801178A0(s16 kind, s16 idx)
{
    Range *t;
    s32 n, base;
    u8 *p;
    switch (kind) {
    case 0:
        t = D_80124C94;
        n = 3;
        base = 0;
        break;
    case 1:
        t = D_80124CAC;
        n = 0x1B;
        base = 0x300;
        break;
    case 2:
        t = D_80124CD0;
        n = 0x1F;
        base = 0x1C8;
        break;
    case 3:
        t = D_80124D08;
        n = 9;
        base = 0x272;
        break;
    default:
        return;
    }
    p = D_1F80021C + t[idx].a * 32 + base * 32;
    func_8001D2A8(n, p, p + (t[idx].b + 1) * 32, 0);
}

extern s16 D_800BED82;
extern M2C_UNK D_801246AC;
void func_80117988(void) {
    func_80075448(0xA, &D_801246AC, 0x10, D_800BED82);
}

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", func_801179BC);

INCLUDE_ASM("asm/a0b/nonmatchings/a0b", f_SpawnLastEvilPigBattleProjectile);

#define gte_ldv0m(p) __asm__ volatile("lwc2	$0, %0;" "lwc2	$1, %1" : : "m"(((s32 *)(p))[0]), "m"(((s32 *)(p))[1]))
extern s32 D_1F800084[];
extern s32 D_1F800088;
extern s32 D_1F800090;
extern s16 D_1F8001A6;
extern u16 D_1F8001A0;

u8 func_801180E8(u8 *a)
{
    s16 ang;
    if (a[0x29] == 0) {
        if (a[0xBE] == 0) {
            ang = *(u16 *)(a + 0x60);
        } else {
            ang = *(u16 *)(a + 0x60) + 0x800;
        }
        a[0x29] = func_800455C0(a, 0, 0, ang);
        if (a[0x29] != 0) {
            if (D_1F8001A6 & 0x8000) {
                *(s16 *)(a + 0x40) = 0;
            }
            a[0x29] &= 1;
            if (a[0x29] != 0) {
                func_80049674(a);
                *(u16 *)(a + 0x60) = D_1F8001A0;
            }
        }
    }
    return a[0x29];
}


s32 func_801181AC(u8 *a)
{
    s16 h = -0x1E;
    s16 ang;
    s16 d = 0x3C;
    if (a[0xBE] == 0) {
        ang = *(u16 *)(a + 0x60);
    } else {
        ang = *(u16 *)(a + 0x60) + 0x800;
    }
    if (func_80045CAC(a, d, h, ang) == 0 && func_80045CAC(a, d, (s16)(0x64 - h), ang) == 0) {
        return 0;
    }
    a[0x5F] = 1;
    return 1;
}

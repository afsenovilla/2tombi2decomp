#include "common.h"
#include "game.h"
#include "m2c.h"

#define H(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define U(p, o) (*(u16 *)((u8 *)(p) + (o)))
extern u16 D_1F80009C;
extern u8 D_1F800137;
extern u16 D_1F80018E;
extern u16 D_1F80018C;
extern u8 D_800BF840;
extern u16 D_1F80008C;

void func_801090F0(u8 *a, u8 *b)
{
    s32 k;
    s32 g;
    s32 m;
    s32 c;
    s32 x, y;
    if (func_8002300C(a, b, H(b, 0x80) * 4) == 0) {
        return;
    }
    k = D_1F80009C + 0x800;
    b[0x2B] = 1;
    if (D_1F800137 == 0) {
        m = U(a, 0x140) - 0x400;
        g = func_80085690(-(s16)(U(b, 0x36) - U(a, 0x36)), (s16)(U(b, 0x2E) - U(a, 0x2E))) << 4;
        if (abs((s16)(g - m * 16)) < 0x1000) {
            D_1F80018E = 0x4100;
            D_1F80018C = U(a, 0x140) - 0x400;
            D_800BF840 = 0x42;
        } else {
            c = U(a, 0x140) + 0x400;
            if (abs((s16)(g - c * 16)) < 0x1000) {
                D_1F80018C = c;
                D_1F80018E = 0x4200;
                D_800BF840 = 0x43;
            }
        }
    }
    if (H(a, 0x80) + H(b, 0x80) + 0x50 < D_1F80008C) {
        return;
    }
    b[0x2B] = 2;
    if (H(a, 0x80) + H(b, 0x80) < D_1F80008C) {
        return;
    }
    x = (func_80083F50((s16)k) * (H(a, 0x80) + H(b, 0x80))) >> 12;
    y = (func_80083E80((s16)k) * (H(a, 0x80) + H(b, 0x80))) >> 12;
    U(a, 0x2E) = U(b, 0x2E) + x;
    U(a, 0x36) = U(b, 0x36) - y;
}

extern s16 D_1F800150_058c;
extern u8 D_1F800182;
extern u8 **D_1F800148;
extern u8 D_1F800182;
extern u8 D_1F800182;
extern u8 D_1F800182;
extern u8 D_1F800182;
extern u8 D_1F800182;
extern u8 *D_800F2738;
void func_801092E8(void)
{
    u8 *a;
    u8 **p;
    u8 *b;
    s32 r;
    if (D_1F800150_058c == 0) {
        return;
    }
    for (a = D_800F2738; a != NULL; a = *(u8 **)(a + 0x24)) {
        if ((a[0] & 1) && a[0x2B] == 0) {
            p = D_1F800148;
            D_1F800182 = *(u8 *)&D_1F800150_058c;
            while (D_1F800182 != 0) {
                b = *p;
                D_1F800182--;
                p++;
                if (b[0] & 1) {
                    switch (b[2]) {
                    case 12:
                        func_80023618(a, b);
                        break;
                    case 18:
                        func_800216B4(a, b, 0);
                    case 32:
                        if (func_80022F04(a, b) != 0) {
                            if (a[2] == 3 || a[2] == 9) {
                                r = func_8001DC9C(a, b, 0, 0);
                            } else {
                                r = func_8001E860(a, b, 0, 0);
                                b[0x2B] = 1;
                            }
                            if (!(r & 0x80)) {
                                D_1F800182 = 0;
                            }
                        }
                        break;
                    }
                }
            }
        }
    }
}

INCLUDE_ASM("asm/a0i/nonmatchings/a0i", func_8010949C);

INCLUDE_ASM("asm/a0i/nonmatchings/a0i", f_DispatchWisdomTowerTombaContacts);

extern u16 D_800BF812;
void func_80109AD8(u8 *a)
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
void func_80109B38(u8 *a)
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

extern u8 **D_1F80013C;
extern u8 D_1F800144;
void func_80109BA8(void *a)
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
                func_801090F0(a, e);
            } else if (e[2] == 8) {
                func_800205CC(a, e);
            }
        }
    }
}

extern u8 D_1F800150;
void func_80109C6C(u8 *a0)
{
    u8 *a = a0;
    u8 **p;
    u8 *b;
    p = D_1F800148;
    D_1F800182 = D_1F800150;
    while (D_1F800182 != 0) {
        b = *p;
        D_1F800182--;
        p++;
        if (b[0] & 1) {
            switch (b[2]) {
            case 14:
            case 15:
                func_8001FAE0(a, b);
                break;
            case 12:
                func_80020868(a, b);
                break;
            case 31:
                func_80023764(a, b);
                break;
            case 18:
            case 32:
                func_8002311C(a, b);
                break;
            }
        }
    }
}

extern s16 D_1F800144_138c;
void func_80109D6C(void)
{
    u8 *a;
    u8 **p;
    u8 *b;
    if (D_1F800144_138c == 0) {
        return;
    }
    for (a = D_800F2738; a != NULL; a = *(u8 **)(a + 0x24)) {
        if ((a[0] & 1) && a[0x2B] == 0) {
            p = D_1F80013C;
            D_1F800182 = *(u8 *)&D_1F800144_138c;
            while (D_1F800182 != 0) {
                b = *p;
                D_1F800182--;
                p++;
                if ((b[0] & 1) && b[2] == 8) {
                    func_80021394(a, b, 0x100);
                }
            }
        }
    }
}

void func_80109E6C(u8 *a)
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

extern u8 D_1F800152;
extern s32 D_1F800080;
s32 func_80109F44(void)
{
    for (D_1F800182 = D_1F800152; D_1F800182 != 0; D_1F800182--) {
    }
    return D_1F800080;
}

INCLUDE_ASM("asm/a0i/nonmatchings/a0i", f_UpdateTombaWisdomTowerRockAction);

void func_8010A554(void *arg0) {
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

INCLUDE_ASM("asm/a0i/nonmatchings/a0i", func_8010A5B8);

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
void func_8010A788(void)
{
    func_80054198(&D_800E7E80_eac2);
    D_800BF816 = 1;
    D_1F800184 = 0;
    D_800E7E80_eac2.x5 = 0x24;
    D_800E7E80_eac2.x6 = 0;
    D_800E7E80_eac2.x16B = 8;
    D_1F800210 = D_800E7E80_eac2.x140;
}

extern u8 D_800E806C;
extern u8 D_800E7E80[];
void func_8010A7E8(void)
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

extern u8 D_1F800236;
#define H(p, o) (*(s16 *)((u8 *)(p) + (o)))
void f_UpdateWisdomTowerExitDoorSequence(u8 *a)
{
    u8 *t;
    switch (a[5]) {
    case 0:
        H(a, 0x40) = 0xF;
        a[5]++;
        break;
    case 1:
        if (--H(a, 0x40) == -1) {
            a[5]++;
        }
        break;
    case 2:
        if (func_80072F14(a) != 0) {
            a[7] = 1;
            a[0] = 1;
            a[5]++;
        }
        break;
    case 3:
        if (D_800E7E80[0x2A] != a[0x2A]) {
            a[5]++;
        }
        break;
    case 4:
        t = D_800E7E80;
        if (t[0x2A] == a[0x2A] && t[5] == 0) {
            a[5]++;
            D_1F800137 = 2;
            if (a[0xBF] != 0) {
                func_80074590(0x17, 0, 0xF);
            }
        }
        break;
    case 5:
        if (func_80072E60(a) != 0) {
            a[5]++;
            D_1F800236 = 1;
            D_800BF808[0x31] = 1;
            D_800BF808[7] = 2;
            H(D_800BF808, 0x32) = 0x614;
        }
        break;
    }
}

INCLUDE_ASM("asm/a0i/nonmatchings/a0i", func_8010A9C0);

s32 func_8010ACA0(u8 *a, s16 id)
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

INCLUDE_ASM("asm/a0i/nonmatchings/a0i", func_8010AD64);

#define H(p, o) (*(s16 *)((u8 *)(p) + (o)))
void func_8010AD64();
void func_8010B06C(u8 *a)
{
    s32 i, j;
    u8 *c;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 3; j++) {
            c = func_80072DDC(a, 1, 4, 0x20);
            if (c != NULL) {
                c[3] = j + 1;
                *(void **)(c + 0x1C) = func_8010AD64;
                H(c, 0x56) = c[3] * 0x200 + 0x71A;
                H(c, 0x56) += (func_8009A450() & 0x3F) - 0x1F;
                H(c, 0x2E) = H(a, 0x2E) + (func_80083F50(H(c, 0x56)) >> 4);
                H(c, 0x32) = H(a, 0x32) + (i - 2) * 200;
                H(c, 0x36) = H(a, 0x36) + (-func_80083E80(H(c, 0x56)) >> 4);
            }
        }
    }
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
extern Spawn *D_8010CA7C[];
extern Pos D_800BF808_76d5;
typedef struct { u8 x, y, z; s8 t; } Spark;
typedef struct { s16 a, b, c, d; } S8;
typedef struct { s16 x, y, z, pad; } SV;
typedef struct { s16 x, y, z; } V3;
typedef struct { s16 x, y, z, pad; } SVec;
typedef struct { u16 x, p0, y, p1, z, p2; } LVec;
typedef struct { u16 a, b; } Range;
void func_8010B17C(Owner *a, s32 sel)
{
    Spawn *e;
    u8 *p;
    a->count = 0;
    e = D_8010CA7C[sel];
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

extern u8 D_800BF918;
void func_8010B2F4(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 4);
    switch (temp_v1) {                              /* irregular */
    case 0:
        M2C_FIELD(arg0, u8 *, 4) = 1U;
        func_8010B17C(arg0, 0U);
        func_8004D8D8(0xF, 0);
        func_800752B4(0);
        func_80075D24(0x1FFF);
        return;
    case 1:
        if (func_80026AD0(arg0) != 0) {
            func_8010B17C(arg0, M2C_FIELD(arg0, u8 *, 3));
        }
        if (D_800BF918 != 0xFF) {
            func_80040C00(0x64);
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

INCLUDE_ASM("asm/a0i/nonmatchings/a0i", func_8010B3DC);

INCLUDE_ASM("asm/a0i/nonmatchings/a0i", func_8010B6C4);

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
void func_8010BA40(PartList *a)
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
        r = func_8010B3DC(e + 1, ot, v & 0xFF);
        v >>= 16;
        func_8010B6C4(r, ot, v & 0xFF);
    }
}

INCLUDE_ASM("asm/a0i/nonmatchings/a0i", func_8010BB40);

INCLUDE_ASM("asm/a0i/nonmatchings/a0i", func_8010BDE4);

void func_8010C118(u32 *p, void *b)
{
    u32 lo = *p;
    u32 packed;

    packed = lo;
    lo = packed & 0xFFFF;
    p += 4;
    func_8010BDE4(func_8010BB40(p, b, lo), b, packed >> 16);
}

INCLUDE_ASM("asm/a0i/nonmatchings/a0i", func_8010C160);

INCLUDE_ASM("asm/a0i/nonmatchings/a0i", func_8010C440);

extern u16 *D_800ECF78;
void func_8010C980(u8 *a)
{
    u16 *p = D_800ECF78;
    u16 t;

    *(u16 **)(a + 0xC) = p;
    *(u16 *)(a + 8) = p[0];
    t = p[1];
    a[7] = 0;
    *(u16 *)(a + 0xA) = t;
}

extern u16 D_8010CAB4[][2];
extern s32 D_1F80021C;

void f_UpdateWisdomTowerInteriorEntranceActor(s16 a, s16 b)
{
    s32 base;
    u16 *t;
    if (a == 0) {
        t = D_8010CAB4[0];
        base = D_1F80021C;
        base += t[b * 2] * 32;
        func_8001D2A8(3, base, base + (t[b * 2 + 1] + 1) * 32, 0);
    }
}

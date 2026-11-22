#include "common.h"
#include "game.h"
#include "m2c.h"

INCLUDE_ASM("asm/a0j/nonmatchings/a0j", func_801090C4);

extern u8 **D_1F800154;
extern u8 D_1F80015C;
extern u8 D_1F800183;
extern u8 D_1F800182;
extern u8 D_1F800150;
extern u8 **D_1F80013C;
extern u8 D_1F800144;
#define TOWER_SCAN_LIST(e)                                          \
    {                                                    \
        u8 **m;                                          \
        u8 *o;                                           \
        D_1F800182 = D_1F800150;                         \
        while (D_1F800182 != 0) {                        \
            D_1F800182--;                                \
        }                                                \
        m = D_1F80013C;                                  \
        D_1F800182 = D_1F800144;                         \
        while (D_1F800182 != 0) {                        \
            o = *m;                                      \
            D_1F800182--;                                \
            m++;                                         \
            if ((o[0] & 1) && o[2] == 8) {               \
                func_8002423C(e, o);                     \
            }                                            \
        }                                                \
    }
void func_80109238(void)
{
    u8 **l = D_1F800154;
    u8 *e;
    D_1F800183 = D_1F80015C;
    while (D_1F800183 != 0) {
        e = *l;
        D_1F800183--;
        l++;
        if (!(e[0] & 2)) {
            switch (e[2]) {
            case 1:
                if (e[3] == 1) {
                    TOWER_SCAN_LIST(e);
                }
                break;
            case 0:
            case 4:
                TOWER_SCAN_LIST(e);
                break;
            }
        }
    }
}

extern s16 D_1F800144_138c;
extern s16 D_1F800150_058c;
extern u8 **D_1F800148;
void func_8010945C(void)
{
    u8 **q;
    u8 **p;
    u8 *a;
    u8 *b;
    q = D_1F80013C;
    D_1F800183 = *(u8 *)&D_1F800144_138c;
    if (D_1F800150_058c == 0) {
        return;
    }
    while (D_1F800183 != 0) {
        a = *q;
        D_1F800183--;
        q++;
        if (a[0] != 2 && !(a[0] & 8)) {
            p = D_1F800148;
            D_1F800182 = *(u8 *)&D_1F800150_058c;
            while (D_1F800182 != 0) {
                b = *p;
                D_1F800182--;
                p++;
                if ((b[0] & 1) && (b[2] == 12 || b[2] == 31)) {
                    func_8002421C(a, b);
                }
            }
        }
    }
}

extern u8 D_1F800182;
extern u8 D_1F800182;
extern u8 D_1F800182;
extern u8 D_1F800182;
extern u8 D_1F800182;
extern u8 *D_800F2738;
void func_801095A0(void)
{
    u8 *a;
    u8 **p;
    u8 *b;
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
                        break;
                    }
                }
            }
        }
    }
}

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

void func_80109D40(u8 *a)
{
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
            case 18:
                func_8002311C(a, b);
                break;
            case 31:
                func_80023764(a, b);
                break;
            }
        }
    }
}

void func_80109E40(void)
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
extern u8 D_1F800137;
void func_80109FB4(u8 *a)
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
        *(s16 *)(c + 0x2) = 0xF05;
        *(s16 *)(c + 0x6) = -0x70C;
        *(s16 *)(c + 0xA) = 0x128C;
    case 1:
        if (D_1F800137 == 1) {
            break;
        }
        a[0x64] &= 0x7F;
        if (t[0x2A] == 9) {
            a[0x64] |= 0x80;
            *(s16 *)(a + 0xA) = *(s16 *)(t + 0x2E);
            *(s16 *)(a + 0xE) = *(s16 *)(t + 0x32);
            *(s16 *)(a + 0x12) = *(s16 *)(t + 0x36);
            func_8006E3F4(a, t + 0x2C);
            v.x = 0xF05;
            v.y = -0x70C;
            v.z = 0x128C;
            func_8006CEC4(D_1F8000D0, &v, 0xE0);
        }
        break;
    }
}

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

typedef struct {
    u32 tag;
    u32 rgb0;
    u16 x0, y0;
    u32 uv0;
    u32 rgb1;
    u16 x1, y1;
    u32 uv1;
    u32 rgb2;
    u16 x2, y2;
    u16 uv2;
    u16 pad;
} T2PolyGT3;
#define T2_ldv3t(r0)                                                                                                   \
    __asm__ volatile("lwc2 $0, 0x10(%0);"                                                                              \
                     "lw $12, 0x14(%0);"                                                                               \
                     "lwc2 $2, 0x18(%0);"                                                                              \
                     "mtc2 $12, $1;"                                                                                   \
                     "lwc2 $4, 0x1C(%0);"                                                                              \
                     "srl $12, $12, 16;"                                                                               \
                     "mtc2 $12, $3;"                                                                                   \
                     "lwc2 $5, 0x20(%0)"                                                                               \
                     :                                                                                                 \
                     : "r"(r0)                                                                                         \
                     : "$12")
#define T2_rtpt() __asm__ volatile(".word 0x4A280030")
#define T2_nclip() __asm__ volatile(".word 0x4B400006")
#define T2_avsz3() __asm__ volatile(".word 0x4B58002D")
#define T2_stflg(r0) __asm__ volatile("cfc2 $12, $31;" "nop;" "sw $12, 0( %0 )" : : "r"(r0) : "$12", "memory")
#define T2_stopz(r0) __asm__ volatile("swc2 $24, 0( %0 )" : : "r"(r0) : "memory")
#define T2_stotz(r0) __asm__ volatile("swc2 $7, 0( %0 )" : : "r"(r0) : "memory")
#define T2_stsxy3_gt3(r0)                                                                                              \
    __asm__ volatile("swc2 $12, 8( %0 );" "swc2 $13, 20( %0 );" "swc2 $14, 32( %0 )" : : "r"(r0) : "memory")
#define T2_stsz1(r0) __asm__ volatile("swc2 $17, 0( %0 )" : : "r"(r0) : "memory")
#define T2_stsz2(r0) __asm__ volatile("swc2 $18, 0( %0 )" : : "r"(r0) : "memory")
#define T2_stsz3(r0) __asm__ volatile("swc2 $19, 0( %0 )" : : "r"(r0) : "memory")
extern void *D_800BF544;

u32 *func_8010AB20(u32 *f, u32 *ot, s32 n)
{
    s32 sz[3];
    s32 *otz = (s32 *)0x1F800004;
    T2PolyGT3 *p = D_800BF544;
    s32 *flg = (s32 *)0x1F800000;
    u32 c;
    u32 mode;
    s32 b, e;
    u32 *o;

    while (n-- != 0) {
        T2_ldv3t(f);
        p->rgb0 = f[0];
        T2_rtpt();
        p->uv0 = f[2];
        p->uv1 = f[3];
        c = f[1];
        T2_stflg(flg);
        if (*flg >= 0) {
            T2_nclip();
            p->rgb1 = c & 0xF0F0F0;
            T2_stopz(flg);
            if (*flg > 0) {
                T2_stsxy3_gt3(p);
                if ((p->x0 < 320 || p->x1 < 320 || p->x2 < 320) && (p->y0 < 240 || p->y1 < 240 || p->y2 < 240)) {
                    p->rgb2 = (c << 4) & 0xF0F0F0;
                    mode = c >> 24;
                    if (mode != 0) {
                        T2_stsz1(&sz[0]);
                        T2_stsz2(&sz[1]);
                        T2_stsz3(&sz[2]);
                        if (mode == 1) {
                            if (sz[0] > sz[1]) {
                                b = sz[2];
                                if (b < sz[0]) {
                                    b = sz[0];
                                }
                                e = b;
                            } else {
                                b = sz[2];
                                if (b < sz[1]) {
                                    b = sz[1];
                                }
                                e = b;
                            }
                        } else {
                            if (sz[0] < sz[1]) {
                                b = sz[2];
                                if (sz[0] < b) {
                                    b = sz[0];
                                }
                                e = b;
                            } else {
                                b = sz[2];
                                if (sz[1] < b) {
                                    b = sz[1];
                                }
                                e = b;
                            }
                        }
                        *otz = e >> 2;
                    } else {
                        T2_avsz3();
                        T2_stotz(otz);
                    }
                    e = *otz >> 10;
                    *otz = (*otz >> e) + (e << 9);
                    if ((u32)(*otz - 4) >= 0x7FC) {
                        *otz = -1;
                    }
                    if (*otz >= 0) {
                        p->uv2 = ((u16 *)f)[0x11];
                        do {
                            o = ot + *otz;
                            p->tag = *o | 0x09000000;
                            *o = (u32)p;
                        } while (0);
                        p++;
                    }
                }
            }
        }
        f += 9;
    }
    D_800BF544 = p;
    return f;
}

typedef struct {
    u32 tag;
    u32 rgb0;
    u16 x0, y0;
    u32 uv0;
    u32 rgb1;
    u16 x1, y1;
    u32 uv1;
    u32 rgb2;
    u16 x2, y2;
    u32 uv2;
    u32 rgb3;
    u16 x3, y3;
    u32 uv3;
} T2PolyGT4;
#define T2_ldv3p(r0)                                                                                                   \
    __asm__ volatile("lw $12, 0x18(%0);"                                                                               \
                     "lwc2 $0, 0x14(%0);"                                                                              \
                     "mtc2 $12, $1;"                                                                                   \
                     "srl $12, $12, 16;"                                                                               \
                     "mtc2 $12, $3;"                                                                                   \
                     "lwc2 $2, 0x1C(%0);"                                                                              \
                     "lw $12, 0x24(%0);"                                                                               \
                     "lwc2 $4, 0x20(%0);"                                                                              \
                     "mtc2 $12, $5"                                                                                    \
                     :                                                                                                 \
                     : "r"(r0)                                                                                         \
                     : "$12")
#define T2_ldv1p(r0)                                                                                                   \
    __asm__ volatile("lw $12, 0x24(%0);"                                                                               \
                     "lwc2 $0, 0x28(%0);"                                                                              \
                     "srl $12, $12, 16;"                                                                               \
                     "mtc2 $12, $1"                                                                                    \
                     :                                                                                                 \
                     : "r"(r0)                                                                                         \
                     : "$12")
#define T2_rtps() __asm__ volatile(".word 0x4A180001")
#define T2_avsz4() __asm__ volatile(".word 0x4B68002E")
#define T2_stsxy(r0) __asm__ volatile("swc2 $14, 0( %0 )" : : "r"(r0) : "memory")
#define T2_stsxy3_gt4(r0)                                                                                              \
    __asm__ volatile("swc2 $12, 8( %0 );" "swc2 $13, 20( %0 );" "swc2 $14, 32( %0 )" : : "r"(r0) : "memory")
#define T2_stsz0(r0) __asm__ volatile("swc2 $16, 0( %0 )" : : "r"(r0) : "memory")

u32 *func_8010ADC4(u32 *f, u32 *ot, s32 n)
{
    s32 sz[4];
    s32 *otz = (s32 *)0x1F800004;
    T2PolyGT4 *p = D_800BF544;
    s32 *flg = (s32 *)0x1F800000;
    u32 c;
    u32 mode;
    s32 b, a, v, e;
    u32 *o;

    while (n-- != 0) {
        T2_ldv3p(f);
        c = f[0];
        p->rgb0 = c & 0xFFF0F0F0;
        T2_rtpt();
        p->rgb1 = (c << 4) & 0xF0F0F0;
        c = f[1];
        T2_stflg(flg);
        if (*flg >= 0) {
            T2_nclip();
            p->uv0 = f[2];
            T2_stopz(flg);
            if (*flg > 0) {
                T2_stsxy3_gt4(p);
                T2_ldv1p(f);
                p->rgb2 = c & 0xF0F0F0;
                T2_rtps();
                p->rgb3 = (c << 4) & 0xF0F0F0;
                p->uv1 = f[3];
                T2_stflg(flg);
                if (*flg >= 0) {
                    T2_stsxy(&p->x3);
                    if ((p->x0 < 320 || p->x1 < 320 || p->x2 < 320 || p->x3 < 320) &&
                        (p->y0 < 240 || p->y1 < 240 || p->y2 < 240 || p->y3 < 240)) {
                        p->uv1 = f[3];
mode = c >> 24;
if (mode != 0) {
T2_stsz0(&sz[0]);
T2_stsz1(&sz[1]);
T2_stsz2(&sz[2]);
T2_stsz3(&sz[3]);
do {
if (mode == 1) {
a = sz[1];
if (a < sz[0]) {
a = sz[0];
}
b = sz[3];
if (b < sz[2]) {
b = sz[2];
}
if (b < a) {
b = a;
}
} else {
a = sz[1];
if (sz[0] < a) {
a = sz[0];
}
b = sz[3];
if (sz[2] < b) {
b = sz[2];
}
if (a < b) {
b = a;
}
}
*otz = b >> 2;
} while (0);
} else {
T2_avsz4();
do {
T2_stotz(otz);
} while (0);
do {
e = *otz >> 10;
*otz = (*otz >> e) + (e << 9);
} while (0);
do {
if ((u32)(*otz - 4) >= 0x7FC) {
*otz = -1;
}
} while (0);
if (*otz >= 0) {
do {
o = ot + *otz;
p->tag = *o | 0x0C000000;
*o = (u32)p;
} while (0);
v = f[4];
p->uv2 = v;
p->uv3 = (u32)v >> 16;
p++;
}
}
}
}
}
}
        f += 11;
    }
    D_800BF544 = p;
    return f;
}

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

extern s16 D_1F800160;
extern s16 D_1F800162;
extern s16 D_1F800164;
#define H(p, o) (*(s16 *)((u8 *)(p) + (o)))
s32 func_8010B98C(u8 *a)
{
    HiPos v;
    u8 *c;
    s16 t;
    switch (a[0x78]) {
    case 0:
        a[0x78]++;
        H(a, 0x40) = 0x3C;
        c = func_80072DDC(a, 0, 3, 0x10);
        if (c != NULL) {
            *(void **)(c + 0x1C) = func_8010CA1C;
            c[3] = 3;
        }
    case 1:
        t = --H(a, 0x40);
        if (t == -1) {
            func_8004D4C4(0x58, 1);
            func_8004B2E8();
            return 1;
        }
        if (t & 1) {
            v.x = D_1F800160;
            v.y = D_1F800162 - 0xC8;
            v.z = D_1F800164;
            func_8003116C(0x2C, &v, -0x20);
        }
        if (H(a, 0x40) % 20 == 0) {
            func_80074590(0x38, 0x1E, 0);
        }
        return 0;
    }
    return 0;
}

extern u8 D_8010D904[];
extern u8 D_8010D50C[];
extern u8 D_8010D70C[];
extern u8 D_8010D5AC[];
s32 func_8010BAD8(u8 *a)
{
    u8 *g;
    s32 ok;
    switch (a[6]) {
    case 0:
        if (a[0x2B] != 3) {
            return 0;
        }
        a[6] = 1;
        func_80042354(1, 2);
        func_80040CDC(a, D_8010D904, D_8010D50C);
        a[0x70] = 1;
        break;
    case 1:
        func_80041098(a);
        if (a[0x70] != 0xFF) {
            return 0;
        }
        a[6]++;
        g = (u8 *)&D_800BF870;
        ok = g[0x246] && g[0x249] && g[0x24C] && g[0x2DF] && g[0x2E0] && g[0x27B];
        if (ok) {
            func_80040CDC(a, D_8010D904, D_8010D70C);
            a[0xBF] = 1;
        } else {
            func_80040CDC(a, D_8010D904, D_8010D5AC);
            a[0xBF] = 0;
        }
        a[0x70] = 1;
        break;
    case 2:
        func_80041098(a);
        if (a[0x70] != 0xFF) {
            return 0;
        }
        a[6] = 0;
        func_80042310();
        if (a[0xBF] != 0) {
            return 2;
        }
        return 1;
    }
    return 0;
}

extern u8 D_8010D624[];
extern u8 D_8010D694[];
s32 func_8010BC8C(u8 *a)
{
    u8 *g;
    s32 ok;
    switch (a[6]) {
    case 0:
        if (a[0x2B] != 3) {
            return 0;
        }
        a[6] = 1;
        func_80042354(1, 2);
        func_80040CDC(a, D_8010D904, D_8010D624);
        a[0x70] = 1;
        break;
    case 1:
        func_80041098(a);
        if (a[0x70] != 0xFF) {
            return 0;
        }
        a[6]++;
        g = (u8 *)&D_800BF870;
        ok = g[0x246] && g[0x249] && g[0x24C] && g[0x2DF] && g[0x2E0] && g[0x27B];
        if (ok) {
            func_80040CDC(a, D_8010D904, D_8010D70C);
            a[0xBF] = 1;
        } else {
            func_80040CDC(a, D_8010D904, D_8010D694);
            a[0xBF] = 0;
        }
        a[0x70] = 1;
        break;
    case 2:
        func_80041098(a);
        if (a[0x70] != 0xFF) {
            return 0;
        }
        a[6] = 0;
        func_80042310();
        if (a[0xBF] != 0) {
            return 2;
        }
        return 1;
    }
    return 0;
}

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

extern u8 D_800E8008[];
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

#define P(p, o) (*(void **)((u8 *)(p) + (o)))
void func_8010CF94(u8 *a)
{
    u8 *t = D_800E7E80;
    u8 *o = P(a, 0x10);
    switch (a[5]) {
    case 0:
        if (D_800BF850 == 1) {
            func_8004ED94(0x6F, 0x42);
            a[5]++;
        }
        func_8004BD64(a, 0, P(t, 0xDC), P(t, 0xD0), 0);
        break;
    case 1:
        if (D_800BF850 == 2) {
            func_8004ED94(0x2C, 0x42);
            a[4] = 3;
        }
        func_8004BD64(a, 0, P(o, 0xDC), P(o, 0xD0), 0);
        *(s16 *)(a + 0x2E) -= 0x30;
        break;
    }
    a[1] = 1;
}

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

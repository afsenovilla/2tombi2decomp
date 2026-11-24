#include "common.h"
#include "game.h"
#include "m2c.h"
#include "gte.h"

INCLUDE_ASM("asm/sop/nonmatchings/sop", func_80109164);

extern u8 D_800E8008[];
extern u8 *D_1F800138_5432;
extern M2C_UNK D_800ED018;
extern M2C_UNK D_800F2418;
extern u8 D_80100400[];
extern u8 D_1F800234;
/* func_801097E4, inlined */
static inline void inl_801097E4(void)
{
    u8 *c = D_800E8008;

    switch (c[0]) {
    case 0:
        c[0]++;
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
/* func_80109934, inlined */
static inline void inl_80109934(void)
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
void func_801092B4(void)
{
    u8 *p = D_1F800138_5432;

    if (*(s16 *)(p + 0x60) == 0) {
        func_8002655C(D_80100400);
        func_8010A0E0(&D_800F2418);
        func_8007B008();
        D_1F800234 = 1;
        inl_801097E4();
        func_80075A80();
        if (D_800BF870.pad1[0x143] != 5) {
            func_8010BFFC(&D_800ED018);
        }
        func_80109FE0(&D_800F2418);
        func_8003C048();
        if (D_800BF870.pad1[0x143] != 5) {
            func_8010C26C(&D_800ED018);
        }
        D_1F800234 = 0;
    } else {
        *(s16 *)(p + 0x60) -= 1;
    }
    inl_80109934();
}

typedef struct {
    s16 x, y, z;
    s16 pad;
    void *fn;
} SpawnDef;
extern SpawnDef D_8010C98C[];
typedef struct { u8 pad[0x4C]; u16 a4C, a4E, a50, a52, a54; } St138b;
extern u8 D_8010C95C[];
extern u8 D_800F2418_9a6f[];
extern u8 D_1F800137;
extern u8 D_800BF839;
extern u16 D_800E7E68;
extern u8 D_800BF9B4;
void func_80109164();
/* func_80109860, inlined */
static inline void inl_80109860(void)
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
void func_80109450(void)
{
    u8 *p, *q, *r, *t, *w, *x;
    u8 c;
    St138b *y;

    switch (*(u16 *)(D_1F800138_5432 + 0x50)) {
    case 0:
        func_8007E9C8(0xFFFFFF, 0, 0);
        func_80044BD4(func_80109164, 0, 0, 3);
        func_8007B18C();
        func_800796DC();
        func_80078610();
        func_8010A8D4(D_800F2418_9a6f);
        inl_80109860();
        func_8006CBD0(D_800E8008, D_8010C95C);
        func_8006E3B0(D_800E8008, D_800E8008 + 0x38);
        p = D_1F800138_5432;
        (*(u16 *)(p + 0x50))++;
        func_80075240();
        q = D_1F800138_5432;
        *(s16 *)(q + 0x60) = 0x1E;
        *(s16 *)(q + 0x52) = 0;
        *(s16 *)(q + 0x54) = 0;
        q[0x6C] = 0x1F;
        D_1F800137 = 1;
        break;
    case 1:
        c = D_1F800138_5432[0x6C] * 8;
        func_8007E9C8((c << 16) | (c << 8) | c, 0, 0);
        D_1F800138_5432[0x6C]--;
        r = D_1F800138_5432;
        if (r[0x6C] == 0) {
            r[0x6C] = 0x1F;
            (*(u16 *)(r + 0x50))++;
        }
        goto common;
    case 2:
        func_801092B4();
        if (D_800BF839 != 0 || (D_800E7E68 & 8)) {
            t = D_1F800138_5432;
            (*(u16 *)(t + 0x50))++;
        }
        break;
    case 3:
        c = -(D_1F800138_5432[0x6C] * 8);
        func_8007E9C8((c << 16) | (c << 8) | c, 0, 0);
        D_1F800138_5432[0x6C]--;
        w = D_1F800138_5432;
        if (w[0x6C] == 0) {
            (*(u16 *)(w + 0x50))++;
        }
    common:
        func_801092B4();
        break;
    case 4:
        func_8001CF2C();
        y = (St138b *)D_1F800138_5432;
        D_1F800137 = 0;
        y->a4E = 0;
        y->a50 = 0;
        y->a52 = 0;
        y->a54 = 0;
        y->a4C++;
        D_800BF870.pad1[0x143] = 0;
        break;
    }
}

extern s8 D_1F800138[];
extern M2C_UNK D_800BE0F0;
extern M2C_UNK D_800EF478;
void func_80109750(void) {
    func_8001DC40(&D_800EF478, M2C_FIELD(&D_800BE0F0, s32 *, 0) + M2C_FIELD(*((void **)D_1F800138), u8 *, 0x6E), 0x800);
    func_8001DC40((M2C_UNK *)0x8018A000, M2C_FIELD(&D_800BE0F0, s32 *, 8) + ((u32) M2C_FIELD(&D_800EF478, u32 *, 0) >> 0xB), M2C_FIELD(&D_800EF478, s32 *, 4) - M2C_FIELD(&D_800EF478, u32 *, 0));
    func_80044E84(0x8018A000, 0x1F8000);
}

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

void func_801098E8(void) {
    func_80109FE0(&D_800F2418);
    func_8003C048();
    if (D_800BF9B4 != 5) {
        func_8010C26C(&D_800ED018);
    }
}

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
u32 *func_801099B4(u32 *f, u32 *ot, s32 n)
{
    s32 sz[6];
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
                    __asm__ volatile("nop");
                    p->rgb2 = (c << 4) & 0xF0F0F0;
                    mode = c >> 24;
                    switch (mode) {
                    case 1:
                        T2_stsz1(&sz[0]);
                        T2_stsz2(&sz[1]);
                        T2_stsz3(&sz[2]);
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
                        goto store;
                    case 2:
                        T2_stsz1(&sz[3]);
                        T2_stsz2(&sz[4]);
                        T2_stsz3(&sz[5]);
                        if (sz[3] < sz[4]) {
                            b = sz[5];
                            if (sz[3] < b) {
                                b = sz[3];
                            }
                            e = b;
                        } else {
                            b = sz[5];
                            if (sz[4] < b) {
                                b = sz[4];
                            }
                            e = b;
                        }
                    store:
                        *otz = e >> 2;
                        break;
                    default:
                        T2_avsz3();
                        T2_stotz(otz);
                        break;
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
u32 *func_80109C80(u32 *f, u32 *ot, s32 n)
{
    s32 sz[8];
    s32 *otz = (s32 *)0x1F800004;
    T2PolyGT4 *p = D_800BF544;
    s32 *flg = (s32 *)0x1F800000;
    u32 c;
    u32 w;
    u32 mode;
    s32 b, a, v, e;
    u32 *o;

    while (n-- != 0) {
        T2_ldv3p(f);
        w = f[0];
        p->rgb0 = w & 0xFFF0F0F0;
        T2_rtpt();
        p->rgb1 = (w << 4) & 0xF0F0F0;
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
                        mode = c >> 24;
                        switch (mode) {
                        case 1:
                            T2_stsz0(&sz[0]);
                            T2_stsz1(&sz[1]);
                            T2_stsz2(&sz[2]);
                            T2_stsz3(&sz[3]);
                            do {
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
                                e = b;
                            } while (0);
                            goto store;
                        case 2:
                            T2_stsz0(&sz[4]);
                            T2_stsz1(&sz[5]);
                            T2_stsz2(&sz[6]);
                            T2_stsz3(&sz[7]);
                            do {
                                a = sz[5];
                                if (sz[4] < a) {
                                    a = sz[4];
                                }
                                b = sz[7];
                                if (sz[6] < b) {
                                    b = sz[6];
                                }
                                if (a < b) {
                                    b = a;
                                }
                                e = b;
                            } while (0);
                        store:
                            *otz = e >> 2;
                            break;
                        default:
                            T2_avsz4();
                            T2_stotz(otz);
                            break;
                        }
                        do {
                            e = *otz >> 10;
                            *otz = (*otz >> e) + (e << 9);
                        } while (0);
                        if ((u32)(*otz - 4) >= 0x7FC) {
                            *otz = -1;
                        }
                        if (*otz >= 0) {
                            v = f[4];
                            p->uv2 = v;
                            p->uv3 = (u32)v >> 16;
                            do {
                                o = ot + *otz;
                                p->tag = *o | 0x0C000000;
                                *o = (u32)p;
                            } while (0);
                            p++;
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
void func_80109FE0(PartList *a)
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
        r = func_801099B4(e + 1, ot, v & 0xFF);
        v >>= 16;
        func_80109C80(r, ot, v & 0xFF);
    }
}

typedef struct {
    s32 vx, vy;
} T2Pt32;
typedef struct {
    u8 pad0[2];
    s16 x;
    u8 pad4[6];
    s16 y;
    u8 padC[0x14];
    s16 rx;
    u16 ry;
} T2CamD0;
extern T2CamD0 D_1F8000D0_3bb0;
extern s32 D_800A3F90;
extern s32 D_800A3F94;
void func_8010A0E0(u8 *a)
{
    T2Pt32 v0, v1, v2;
    T2CamD0 *c = &D_1F8000D0_3bb0;
    s32 ang, r, dx, dz;
    u16 t;
    u16 *q;

    q = *(u16 **)(a + 0xC);
    ((u16 *)a)[4] = *q++;
    ((u16 *)a)[5] = *q;
    D_800A3F90 = 0x5780;
    t = c->ry;
    D_800A3F94 = 0x1C7;
    ang = (-(s16)t - D_800A3F94) & 0xFFF;
    v0.vx = c->x;
    v0.vy = c->y;
    v1.vx = v0.vx + ((func_80083E80(ang) * D_800A3F90) >> 12);
    v1.vy = v0.vy + ((func_80083F50(ang) * D_800A3F90) >> 12);
    ang = (D_800A3F94 - (s16)c->ry) & 0xFFF;
    v2.vx = v0.vx + ((func_80083E80(ang) * D_800A3F90) >> 12);
    v2.vy = v0.vy + ((func_80083F50(ang) * D_800A3F90) >> 12);
    r = abs(func_80083E80(c->rx));
    dx = (func_80083E80(-(s16)c->ry) * r) >> 12;
    dz = (func_80083F50(-(s16)c->ry) * r) >> 12;
    dx = (dx * D_800A3F90 * 5) >> 16;
    dz = (dz * D_800A3F90 * 5) >> 16;
    v1.vx -= dx;
    v1.vy -= dz;
    v2.vx -= dx;
    v0.vx -= dx;
    v2.vy -= dz;
    v0.vy -= dz;
    v0.vx /= 640;
    v0.vy /= 640;
    v1.vx /= 640;
    v1.vy /= 640;
    v2.vx /= 640;
    v2.vy /= 640;
    a[6] = 0;
    func_8010A3AC(a, &v0, &v1, &v2);
}

#define GH(p, o) (*(s16 *)((u8 *)(p) + (o)))
typedef struct { u8 pad[0x10]; u16 cells[1]; } GridCellList;
static inline void tri_span_70a8(u8 *a, s32 y, s32 l, s32 r) {
    s32 x;
    s16 *p;
    s32 off;

    if (y >= 0 && y < GH(a, 0xA)) {
        if (r >= GH(a, 8)) r = GH(a, 8) - 1;
        x = l;
        if (x < 0) x = 0;
        p = *(s16 **)(a + 0xC);
        p += 2;
        off = x * GH(a, 0xA) + y;
        while (p += off, x <= r) {
            if (*p != -1) {
                u8 n = a[6];
                if (n < 0xFE) {
                    a[6] = n + 1;
                    ((GridCellList *)a)->cells[n] = *p;
                }
            }
            off = GH(a, 0xA);
            x++;
        }
    }
}
void func_8010A3AC(u8 *a, s32 *p0, s32 *p1, s32 *p2) {
    s32 x0 = p0[0], y0 = p0[1];
    s32 x1 = p1[0], y1 = p1[1];
    s32 x2 = p2[0], y2 = p2[1];
    s32 t, dx1, dx2, dy1, dy2;
    s32 xl, xr, y;
    s32 sl1, sl2, sl3;

    if (y1 == y0 && y1 == y2) return;
    if (y1 < y0) { t = x0; x0 = x1; x1 = t; t = y0; y0 = y1; y1 = t; }
    if (y2 < y0) { t = x0; x0 = x2; x2 = t; t = y0; y0 = y2; y2 = t; }
    if (y2 < y1) { t = x1; x1 = x2; x2 = t; t = y1; y1 = y2; y2 = t; }
    dx1 = x1 - x0;
    dx2 = x2 - x0;
    dy1 = y1 - y0;
    dy2 = y2 - y0;
    if (y1 == y0) {
        if (x0 < x1) { xl = x0 << 16; xr = x1 << 16; }
        else { xl = x1 << 16; xr = x0 << 16; }
        sl1 = 0;
    } else {
        xl = xr = x0 << 16;
        sl1 = (dx1 << 16) / dy1;
    }
    xr += 0x10000;
    if (y1 == y2) sl2 = 0;
    else sl2 = ((x2 - x1) << 16) / (y2 - y1);
    sl3 = (dx2 << 16) / dy2;
    if (-dy2 * dx1 + dx2 * dy1 > 0) {
        for (y = y0; y < y1; y++) { tri_span_70a8(a, y, xl >> 16, xr >> 16); xl += sl1; xr += sl3; }
        for (; y <= y2; y++) { tri_span_70a8(a, y, xl >> 16, xr >> 16); xl += sl2; xr += sl3; }
    } else {
        for (y = y0; y < y1; y++) { tri_span_70a8(a, y, xl >> 16, xr >> 16); xr += sl1; xl += sl3; }
        for (; y <= y2; y++) { tri_span_70a8(a, y, xl >> 16, xr >> 16); xl += sl3; xr += sl2; }
    }
}

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

extern u8 D_800ECF58[];
extern u8 D_80017FE8[];
extern u8 D_800E7E80[];
extern u8 D_800A3FA8[];
extern u8 D_8010CA28[];
u8 *func_8010AE30(void *a);
void func_8010ACFC(u8 *a)
{
    u8 *t;

    switch (a[4]) {
    case 0:
        func_80067DA8(D_800E7E80);
        t = D_800ECF58;
        if (func_800519E0(a, 0x11, *(void **)(t + 0xBC), D_800A3FA8) != 0) {
            break;
        }
        *(void **)(a + 0x3C) = *(void **)(t + 0x10);
        a[0x47] = 0xFF;
        a[4]++;
        func_80040CDC(a, D_80017FE8, D_8010CA28);
        func_80054D14(a, 8, 0);
        a[0x70] = 2;
        *(s16 *)(a + 0x84) = 0x8C;
        func_8010AE30(a);
        break;
    case 1:
        if (func_8007778C(a) != 0) {
            func_800518FC(a);
        }
        func_80041098(a);
        func_8004190C(a);
        break;
    case 2:
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

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

extern u8 D_8010C968[];
extern u8 D_800BF80F;
s32 func_8010AE9C(u8 *a)
{
    switch (a[0x78]) {
    case 0:
        D_800BF9B4 = 2;
        func_8006CBD0(D_800E8008, D_8010C968);
        a[0x78]++;
        goto end;
    case 1:
        *(s16 *)(a + 0x2E) = 0x104B;
        *(s16 *)(a + 0x36) = 0x4AB5;
        *(s16 *)(a + 0x56) = 0x400;
        func_8010BDB8(a);
        a[0x78]++;
        goto end;
    case 2:
        D_800BF80F = 1;
        return 1;
    end:
    default:
        return 0;
    }
}

s32 func_8010AF60(u8 *a)
{
    switch (a[0x78]) {
    case 0:
        a[0x78] = 1;
        *(s16 *)(a + 0x42) = 0x1E;
        break;
    case 1:
        if (--*(s16 *)(a + 0x42) != 0) {
            return 0;
        }
        D_800BF9B4 = 3;
        func_80054D14(a, 0xB4, 4);
        *(s16 *)(a + 0x42) = 0x28;
        a[0x78]++;
        break;
    case 2:
        if (--*(s16 *)(a + 0x42) != 0) {
            return 0;
        }
        func_80054D14(a, 2, 6);
        *(s16 *)(a + 0x42) = 0x1E;
        a[0x78]++;
        break;
    case 3:
        if (--*(s16 *)(a + 0x42) == 0) {
            return 1;
        }
        break;
    }
    return 0;
}

extern u8 D_8010C974[];
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

extern u8 D_8010CB08[];
void func_8010B798(u8 *a)
{
    u8 *t;

    switch (a[4]) {
    case 0:
        t = D_800ECF58;
        if (func_800519E0(a, 0xF, *(void **)(t + 0x48), D_8010CB08) != 0) {
            break;
        }
        *(void **)(a + 0x3C) = *(void **)(t + 0x10);
        func_80077C40(a, D_80017FE8, 2);
        *(s16 *)(a + 0x84) = 0x60;
        a[3] = 1;
        a[4]++;
        *(s16 *)(a + 0x32) -= 0x60;
        func_8010AE30(a);
        break;
    case 1:
        func_8007778C(a);
        func_8010B588(a);
        func_8004190C(a);
        func_800518FC(a);
        break;
    case 2:
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

s32 func_8010B8AC(u8 *a)
{
    switch (a[0x78]) {
    case 0:
        *(s16 *)(a + 0x4A) = -0x3000;
        a[0x78]++;
        break;
    case 1:
        if (a[1] == 0) {
            func_80074590(7, 0, 0);
            a[0x78]++;
        }
    case 2:
        if ((*(s16 *)(a + 0x4A) += 0x360) > 0x3E00) {
            *(s16 *)(a + 0x4A) = 0x3E00;
        }
        *(s32 *)(a + 0x30) += *(s16 *)(a + 0x4A) << 8;
        *(s16 *)(a + 0x2E) -= 0x10;
        break;
    }
    return 0;
}

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

typedef struct { s16 x, y, w, h; } ClutRectS;
typedef struct {
    u8 *ptr;
    u8 *clut;
    s16 x;
    s16 y;
} ClutCycleS;
extern ClutCycleS D_8010D2FC[];
void func_8010C6A0(void)
{
    ClutRectS r;
    s32 i;
    ClutCycleS *e;
    u8 *data;

    e = D_8010D2FC;
    for (i = 0; i < 3; i++, e++) {
        if ((s8)--D_8010D390[i] <= 0) {
            if (e->ptr[0] == 0xFF) {
                e->ptr -= e->ptr[1];
            }
            data = e->clut + e->ptr[0] * 32;
            D_8010D390[i] = e->ptr[1];
            r.x = e->x;
            r.y = e->y;
            r.w = 16;
            r.h = 1;
            func_80081218(&r, data);
            e->ptr += 2;
        }
    }
}

INCLUDE_ASM("asm/sop/nonmatchings/sop", func_8010C79C);

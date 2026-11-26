#include "common.h"
#include "game.h"
#include "m2c.h"
#include "gte.h"

extern u16 D_800BF812;

void func_80109208(u8 *a)
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
void func_80109268(u8 *a)
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

s32 func_801092D8(void) {
    return *(s32 *)0x1F800080;
}

#define H(p, o) (*(s16 *)((u8 *)(p) + (o)))
typedef struct {
    s16 pad;
    s16 x, y, z;
} PartPos;
extern u8 D_800BFA58_9b2e;
extern PartPos D_801178E0[];
extern u8 D_1F800137;
/* func_801094B8, inlined */
static inline void inl_801094B8(u8 *a)
{
    s32 k = 0x27;
    s32 i;

    if (D_800BFA58_9b2e == 0) {
        k = 0x26;
    }
    for (i = 0; i < a[9]; i++) {
        func_80051B04(((u8 **)(a + 0xC0))[i], k, i);
        *(s16 *)(((u8 **)(a + 0xC0))[i] + 0) = D_801178E0[i].x;
        *(s16 *)(((u8 **)(a + 0xC0))[i] + 2) = D_801178E0[i].y;
        *(s16 *)(((u8 **)(a + 0xC0))[i] + 4) = D_801178E0[i].z;
    }
}
void func_801092E8(u8 *a)
{
    GameState *g = &D_800BF870;

    g->pad1[0x5E4] = 0;
    func_80055284();
    switch (g->pad1[0]) {
    case 0:
        a[1] = 0;
        break;
    case 1:
        a[1] = 1;
        func_80042354(1, 6);
        break;
    case 2:
        a[1] = 1;
        func_8003315C(a);
        break;
    case 3:
        a[1] = 1;
        H(a, 0x56) = 0x800;
        func_8003315C(a);
        func_80042354(1, 6);
        break;
    case 4:
        a[1] = 1;
        func_8003315C(a);
        inl_801094B8(a);
        break;
    case 5:
        a[1] = 1;
        H(a, 0x56) = 0x800;
        func_8003315C(a);
        break;
    }
    H(a, 0x142) = 0;
    H(a, 0x58) = 0;
    func_80054198(a);
    func_80054D14(a, 2, 0);
    D_1F800137 = 1;
    a[4] = 4;
    a[5] = 0x21;
    a[6] = 0;
    a[7] = 0;
}

void func_801094B8(u8 *a)
{
    s32 k = 0x27;
    s32 i;
    PartPos *t;
    u8 **pp;

    if (D_800BFA58_9b2e == 0) {
        k = 0x26;
    }
    for (i = 0; i < a[9]; i++) {
        func_80051B04(((u8 **)(a + 0xC0))[i], k, i);
        *(s16 *)(((u8 **)(a + 0xC0))[i] + 0) = D_801178E0[i].x;
        *(s16 *)(((u8 **)(a + 0xC0))[i] + 2) = D_801178E0[i].y;
        *(s16 *)(((u8 **)(a + 0xC0))[i] + 4) = D_801178E0[i].z;
    }
}

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", f_UpdateEndingIllustrationTransition);

#define H(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define U(p, o) (*(u16 *)((u8 *)(p) + (o)))
typedef struct { s16 k; u8 pad[10]; } CamEnt;
extern CamEnt D_80113D08[];
extern CamEnt D_801131BC[];
extern CamEnt D_80114EE4[];
extern u8 D_800BF80F;
extern u8 D_800BFA55;
void func_8010983C(u8 *a)
{
    u8 *g;
    CamEnt *t;
    s32 m;
    s32 m2;
    CamEnt *t2;

    switch (a[2]) {
    case 0:
        switch (a[3]) {
        case 0:
            a[0x64] |= 0x80;
            D_800BFA55 = 0;
            H(a, 0x6A) = 0;
            func_8006CBD0(a, D_80114EE4);
            U(a, 0x68) = 0x3C;
            a[3]++;
            func_8003116C(0x1600, a + 8, 0);
            break;
        case 1:
            if (--H(a, 0x68) == 0) {
                a[3]++;
                func_8006CBD0(a, &D_80113D08[H(a, 0x6A)++]);
                D_800BFA55 = 1;
            }
            break;
        case 2:
            func_8006CBD0(a, &D_80113D08[H(a, 0x6A)++]);
            a[3]++;
            break;
        case 3:
            t = D_80113D08;
            m = -1;
            if (H(a, 0x6A) != m) {
                func_8006CBD0(a, &t[H(a, 0x6A)]);
                H(a, 0x6A)++;
                if (t[H(a, 0x6A)].k == 0) {
                    H(a, 0x6A) = m;
                }
            }
            if (H(a, 0x6A) == m) {
                a[3]++;
                D_800BF80F = 2;
            }
            break;
        case 4:
            if (D_800BF80F == 0) {
                D_800BFA55 = 4;
                a[3] = 0;
                H(a, 0x6A) = 0;
                a[2]++;
                func_8006CBD0(a, D_801131BC);
            }
            break;
        }
        break;
    case 1:
        switch (a[3]) {
        case 0:
            D_800BF80F = 1;
            a[3]++;
            func_8006CBD0(a, &D_801131BC[H(a, 0x6A)]);
            break;
        case 1:
            if (D_800BF80F == 0) {
                a[3] = 2;
                D_800BFA55 = 5;
            }
            break;
        case 2:
            t2 = D_801131BC;
            m2 = -1;
            if (H(a, 0x6A) != m2) {
                func_8006CBD0(a, &t2[H(a, 0x6A)]);
                H(a, 0x6A)++;
                if (t2[H(a, 0x6A)].k == 0) {
                    H(a, 0x6A) = m2;
                }
            }
            if (H(a, 0x6A) >= 0xDD) {
                a[3] = 0;
                a[2]++;
                g = D_800BF808;
                g[7] = 2;
                g[0x31] = 3;
                H(g, 0x32) = 0x1502;
            }
            break;
        case 3:
            t2 = D_801131BC;
            m2 = -1;
            if (H(a, 0x6A) != m2) {
                func_8006CBD0(a, &t2[H(a, 0x6A)]);
                H(a, 0x6A)++;
                if (t2[H(a, 0x6A)].k == 0) {
                    H(a, 0x6A) = m2;
                }
            }
            break;
        }
        break;
    }
    func_8006E3B0(a, a + 0x38);
}

extern CamEnt D_80114EFC[];
extern u8 D_800BFA57;
void f_UpdateEndingArea2CameraSequence(u8 *a)
{
    s32 pad[4];

    switch (a[2]) {
    case 0:
        D_800BFA55 = 0;
        H(a, 0x6A) = 1;
        a[2]++;
        a[0x64] |= 0x80;
        func_8006CBD0(a, D_80114EFC);
        H(a, 0x68) = 0;
        break;
    case 1:
        if (D_800BFA57 == 1) {
            a[2]++;
            func_8006CBD0(a, &D_80114EFC[H(a, 0x6A)++]);
        }
        break;
    case 2:
        if (D_800BFA57 == 3) {
            func_8006CC1C(a, &D_80114EFC[H(a, 0x6A)++], 0x1E);
            a[2]++;
        }
        break;
    case 3:
        func_8006CDCC(a);
        if (D_800BFA57 == 5) {
            func_8006CC1C(a, &D_80114EFC[H(a, 0x6A)++], 0x1E);
            a[2]++;
        }
        break;
    case 4:
        func_8006CDCC(a);
        if (D_800BFA57 == 6) {
            H(a, 0x68) = 0x14;
            a[2]++;
        }
        break;
    case 5:
        if (--H(a, 0x68) == 0) {
            a[2]++;
            func_8006CC1C(a, &D_80114EFC[H(a, 0x6A)++], 0x1E);
        }
        break;
    case 6:
        func_8006CDCC(a);
        if (D_800BFA57 == 0xE) {
            func_8006CC1C(a, &D_80114EFC[H(a, 0x6A)++], 0x1E);
            a[2]++;
        }
        break;
    case 7:
        func_8006CDCC(a);
        if (D_800BFA57 == 0xF) {
            func_8006CC1C(a, &D_80114EFC[H(a, 0x6A)++], 0x1E);
            a[2]++;
        }
        break;
    case 8:
        func_8006CDCC(a);
        if (D_800BFA57 == 0x18) {
            func_8006CC1C(a, &D_80114EFC[H(a, 0x6A)++], 0x3C);
            a[2]++;
        }
        break;
    case 9:
        if (func_8006CDCC(a) != 0) {
            a[2]++;
        }
        break;
    }
    func_8006E3B0(a, a + 0x38);
}

extern CamEnt D_80114F68[];
extern u8 D_800BE0E4;
void f_UpdateEndingArea4CameraSequence(u8 *a)
{
    s32 pad[4];

    switch (a[2]) {
    case 0:
        D_800BFA55 = 0;
        H(a, 0x6A) = 1;
        a[2]++;
        a[0x64] |= 0x80;
        func_8006CBD0(a, D_80114F68);
        func_8001D71C(0xC);
        H(a, 0x68) = 0x3C;
        break;
    case 1:
        if (!(D_800BE0E4 & 0x80) || --H(a, 0x68) == 0) {
            H(a, 0x68) = 0x3C;
            a[2]++;
        }
        break;
    case 2:
        if (--H(a, 0x68) == 0) {
            func_8006CC1C(a, &D_80114F68[H(a, 0x6A)++], 0x3C);
            a[2]++;
        }
        break;
    case 3:
        if (func_8006CDCC(a) != 0) {
            func_8006CBD0(a, &D_80114F68[H(a, 0x6A)++]);
            D_800BFA55 = 1;
            a[2]++;
        }
        break;
    case 4:
        if (D_800BFA57 == 1) {
            a[2]++;
        }
        break;
    case 5:
        func_8006CBD0(a, &D_80114F68[H(a, 0x6A)++]);
        D_800BFA55 = 2;
        a[2]++;
        break;
    case 6:
        if (D_800BFA55 == 3) {
            func_8006CBD0(a, &D_80114F68[H(a, 0x6A)++]);
            a[2]++;
        }
        break;
    case 7:
        break;
    }
    func_8006E3B0(a, a + 0x38);
}

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", f_UpdateEndingArea5MysteryCameraSequence);

extern u8 D_800BF871;
extern u8 D_800BF84C;
extern u8 D_80114F5C[];
void func_8010A680(u8 *a)
{
    switch (D_800BF871) {
    case 0:
        break;
    case 1:
        func_8010983C(a);
        break;
    case 2:
        f_UpdateEndingArea2CameraSequence(a);
        break;
    case 3:
        if (a[2] == 0) {
            D_800BFA55 = 0;
            a[0x64] |= 0x80;
            func_8006CBD0(a, D_80114F5C);
            func_8006E3B0(a, a + 0x38);
            a[2]++;
        }
        break;
    case 4:
        f_UpdateEndingArea4CameraSequence(a);
        break;
    case 5:
        f_UpdateEndingArea5MysteryCameraSequence(a);
        break;
    }
    D_800BF84C = 1;
}

extern u8 *D_800BF544;
extern u8 *D_800ED8C8;
extern s16 D_800E7ED6;
extern u8 D_8011605C[];
void func_8010A768(u8 *a)
{
    if (a[2] == 0) {
        D_800BFA55 = 0;
        a[0x64] |= 0x80;
        func_8006CBD0(a, D_80114F5C);
        func_8006E3B0(a, a + 0x38);
        a[2]++;
    }
}

void func_8010A7D0(void) {
}

void func_8010A7D8(void) {
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
extern Spawn *D_80115448[];
extern Pos D_800BF808_76d5;
typedef struct { u8 x, y, z; s8 t; } Spark;
typedef struct { s16 a, b, c, d; } S8;
typedef struct { s16 x, y, z, pad; } SV;
typedef struct { s16 x, y, z; } V3;
typedef struct { s16 x, y, w, h; } ClutRect;
typedef struct { s16 m[3][3]; s16 pad; s32 t[3]; } AreaMatrix;
typedef struct { s16 x, y, z, pad; } AreaSVec;
typedef struct { u8 pad[0x28]; AreaMatrix m; } AreaScratchD0;
typedef struct { s16 x, y, z, pad; } SVecL;
typedef struct { u16 x, p0, y, p1, z, p2; } LVecL;
typedef struct { u16 a, b; } Range;
void func_8010A7E0(Owner *a, s32 sel)
{
    Spawn *e;
    u8 *p;
    a->count = 0;
    e = D_80115448[sel];
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

extern s32 D_800BF850;
extern s16 D_800BED80;
void func_8010A958(u8 *a)
{
    u8 *s;

    switch (a[4]) {
    case 0:
        a[4] = 1;
        func_8010A7E0(a, 0);
        func_800752B4(0);
        func_80075D24(0x1FFF);
        D_800BF850 = 0;
        break;
    case 1:
        if (func_80026AD0(a) != 0) {
            func_8010A7E0(a, a[3]);
        }
        func_80026A68(a);
        if (D_800BED80 == 11) {
            s = D_800BF808;
            if (*(s32 *)(s + 0x48) != 0) {
                func_8008DE74(11, 0x7F, 0x21C);
                *(s32 *)(s + 0x48) = 0;
            }
        }
        break;
    case 2:
        break;
    case 3:
        func_8007ADD0(a);
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
u32 *func_8010AA4C(u32 *f, u32 *ot, s32 n)
{
    s32 sz[6];
    s32 *otz = (s32 *)0x1F800004;
    T2PolyGT3 *p = (T2PolyGT3 *)D_800BF544;
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
                    mode = (c >> 24) & 3;
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
                        } else {
                            b = sz[2];
                            if (b < sz[1]) {
                                b = sz[1];
                            }
                        }
                        *otz = (b >> 2) + 100;
                        break;
                    case 2:
                        T2_stsz1(&sz[3]);
                        T2_stsz2(&sz[4]);
                        T2_stsz3(&sz[5]);
                        if (sz[3] > sz[4]) {
                            b = sz[5];
                            if (b < sz[3]) {
                                b = sz[3];
                            }
                        } else {
                            b = sz[5];
                            if (b < sz[4]) {
                                b = sz[4];
                            }
                        }
                        *otz = b >> 2;
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
    D_800BF544 = (u8 *)p;
    return f;
}

#define T2_rtpt() __asm__ volatile(".word 0x4A280030")
#define T2_nclip() __asm__ volatile(".word 0x4B400006")
#define T2_stflg(r0) __asm__ volatile("cfc2 $12, $31;" "nop;" "sw $12, 0( %0 )" : : "r"(r0) : "$12", "memory")
#define T2_stopz(r0) __asm__ volatile("swc2 $24, 0( %0 )" : : "r"(r0) : "memory")
#define T2_stotz(r0) __asm__ volatile("swc2 $7, 0( %0 )" : : "r"(r0) : "memory")
#define T2_stsz1(r0) __asm__ volatile("swc2 $17, 0( %0 )" : : "r"(r0) : "memory")
#define T2_stsz2(r0) __asm__ volatile("swc2 $18, 0( %0 )" : : "r"(r0) : "memory")
#define T2_stsz3(r0) __asm__ volatile("swc2 $19, 0( %0 )" : : "r"(r0) : "memory")
extern u8 *D_800BF544;
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
u32 *func_8010AD40(u32 *f, u32 *ot, s32 n)
{
    s32 sz[8];
    s32 *otz = (s32 *)0x1F800004;
    T2PolyGT4 *p = (T2PolyGT4 *)D_800BF544;
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
                        mode = (c >> 24) & 3;
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
                            } while (0);
                            *otz = b >> 2;
                            break;
                        case 2:
                            T2_stsz0(&sz[4]);
                            T2_stsz1(&sz[5]);
                            T2_stsz2(&sz[6]);
                            T2_stsz3(&sz[7]);
                            do {
                                a = sz[5];
                                if (a < sz[4]) {
                                    a = sz[4];
                                }
                                b = sz[7];
                                if (b < sz[6]) {
                                    b = sz[6];
                                }
                                if (b < a) {
                                    b = a;
                                }
                            } while (0);
                            *otz = (b >> 2) + 100;
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
    D_800BF544 = (u8 *)p;
    return f;
}

#define gte_SetRotMatrix(r0) __asm__ volatile("lw	$12, 0( %0 );" "lw	$13, 4( %0 );" "ctc2	$12, $0;" "ctc2	$13, $1;" "lw	$12, 8( %0 );" "lw	$13, 12( %0 );" "lw	$14, 16( %0 );" "ctc2	$12, $2;" "ctc2	$13, $3;" "ctc2	$14, $4" : : "r"(r0) : "$12", "$13", "$14")
#define gte_SetTransMatrix(r0) __asm__ volatile("lw	$12, 20( %0 );" "lw	$13, 24( %0 );" "ctc2	$12, $5;" "lw	$14, 28( %0 );" "ctc2	$13, $6;" "ctc2	$14, $7" : : "r"(r0) : "$12", "$13", "$14")
extern u8 D_1F8000F8[];
extern void *D_800ED8C8_a098;
typedef struct {
    u8 pad0[6];
    u8 count;
    u8 pad7[5];
    u32 *tbl;
    u16 list[1];
} PartList;
void func_8010B0B8(PartList *a)
{
    u16 *p;
    u16 *end;
    void *ot;
    u32 *tbl;
    u32 *e;
    u32 v;
    void *r;
    if (a->count == 0) {
        return;
    }
    gte_SetRotMatrix(D_1F8000F8);
    gte_SetTransMatrix(D_1F8000F8);
    p = a->list;
    end = &a->list[a->count];
    ot = D_800ED8C8_a098;
    tbl = a->tbl;
    for (; p < end; p++) {
        e = &tbl[*p];
        v = *e;
        r = func_8010AA4C(e + 1, ot, v & 0xFF);
        v >>= 16;
        func_8010AD40(r, ot, v & 0xFF);
    }
}

void func_8010B1B8(u32 *p, void *b)
{
    u32 lo = *p;
    u32 packed;

    packed = lo;
    lo = packed & 0xFFFF;
    p += 4;
    f_DispatchEndingAreaCameraSequence(func_80112DEC(p, b, lo), b, packed >> 16);
}

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_8010B200);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_8010B4EC);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_8010B61C);

extern u16 *D_800ECF78;
void func_8010B8EC(u8 *a)
{
    u16 *p = D_800ECF78;
    u16 t;

    *(u16 **)(a + 0xC) = p;
    *(u16 *)(a + 8) = p[0];
    t = p[1];
    a[7] = 0;
    *(u16 *)(a + 0xA) = t;
}

extern u8 *D_800ECF84;
extern s16 D_1F8000F0;
extern s16 D_1F8000F2;
void func_8010B918(u8 *a)
{
    s32 pad;
    u8 *p = D_800ECF84;
    s32 x, y;
    u16 n;

    switch (a[0]) {
    case 0:
        a[0] = 1;
        a[3] = 0;
        *(u16 *)(a + 4) = *(u16 *)(p + 0);
        *(u16 *)(a + 6) = *(u16 *)(p + 2);
        *(u16 *)(a + 8) = *(u16 *)(p + 4);
        *(u16 *)(a + 0xA) = *(u16 *)(p + 6);
        *(u16 *)(a + 0xC) = *(u16 *)(p + 8);
        *(u16 *)(a + 0xE) = *(u16 *)(p + 0xA);
        a[0x10] = p[0xC];
        a[0x11] = p[0xD];
        {
            u16 l1 = *(u16 *)(p + 0xE);
            u16 l0 = *(u16 *)(p + 0x10);
        *(u16 *)(a + 0x2C) = 0x900;
        *(u16 *)(a + 0x2E) = 0x8E8;
        {
            u8 *b0 = p + 0x14;
            u8 *b1 = b0 + l0;
            u8 *b2 = b1 + l1;
        *(u8 **)(a + 0x1C) = b2;
        *(u8 **)(a + 0x18) = b0;
        *(u8 **)(a + 0x14) = b1;
        }
        }
        *(u8 **)(a + 0x34) = *(u8 **)(a + 0x1C);
        *(u16 *)(a + 0x30) = (*(u16 *)(a + 0x2C) * a[0x10]) / 144;
        *(u16 *)(a + 0x32) = (*(u16 *)(a + 0x2E) * a[0x11]) / 144;
        a[0x38] = 1;
        break;
    case 2: break;
    case 1:
        { s32 k = D_1F8000F2; u16 w = *(u16 *)(a + 0x2C); x = ((w + 0x140) >> 1) - ((k * w) >> 12); }
        while (x < 0) {
            x += *(u16 *)(a + 0x30);
        }
        while (x >= *(u16 *)(a + 0x30)) {
            x -= *(u16 *)(a + 0x30);
        }
        y = ((D_1F8000F0 * *(u16 *)(a + 0x2E)) >> 12) + a[0x11] * 8 - 0x20;
        while (y < 0) {
            y += *(u16 *)(a + 0x32);
        }
        while (y >= *(u16 *)(a + 0x32)) {
            y -= *(u16 *)(a + 0x32);
        }
        if (--*(s8 *)(a + 0x38) <= 0) {
            a[3] = 1;
        }
        *(s16 *)(a + 0x28) = x;
        *(s16 *)(a + 0x2A) = y;
        break;
    }
}

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_8010BB64);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_8010BCA8);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_8010BE30);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_8010C1D8);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_8010C7F4);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_8010CA30);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", f_UpdateEndingIllustrationPanels);

extern u16 D_1F800160_3621;
extern u16 D_1F800162;
extern u16 D_1F800164_7d8c;
void func_8010CF6C(u8 *a0)
{
    u8 *a = a0;
    u16 x, y, z;
    switch (a[4]) {
    case 0:
        *(s32 *)(a + 0x50) = 0;
        a[4] = 1;
    case 1:
        x = D_1F800160_3621;
        y = D_1F800162;
        z = D_1F800164_7d8c;
        *(u16 *)(a + 0x2C) = x;
        *(u16 *)(a + 0x2E) = y;
        *(u16 *)(a + 0x30) = z;
        *(s32 *)(a + 0x50) -= 10;
        if (D_800BFA55 < 4) {
            a[1] = 1;
        } else {
            a[4] = 3;
        }
        break;
    case 2:
    case 3:
        func_8007A624(a);
        break;
    }
}

extern s32 D_8011A6C4;
extern s32 D_8011A6C8;
extern s32 D_8011A6CC;
extern s32 D_8011A6D0;
void f_ResetEndingIllustrationState(void) {
    D_8011A6C4 = 0;
    D_8011A6C8 = 0;
    D_8011A6CC = -0x100;
    D_8011A6D0 = 0;
}

void func_8010D058(s32 i, s32 b, s32 c, s32 d, s32 e)
{
    u8 *m = D_800BF544;

    func_80083DE0(m, b, c, d, e);
    func_80083C30(D_800ED8C8 + i * 4, m);
    D_800BF544 = m + 0xC;
}

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", f_UpdateEndingContinuePrompt);

extern s32 D_800BF854;
extern u8 D_801158AC[];
extern u8 D_801159F4[];
extern u8 D_80115A14[];
/* func_8010D490, inlined */
static inline void inl_8010D490(u8 *a)
{
    u8 *s;

    if (a[5] == 0) {
        func_80041098(a);
        if (a[0x70] == 0xFF) {
            s = D_800BF808;
            s[0x31] = 3;
            *(s16 *)(s + 0x32) = 0x1503;
            a[5]++;
        }
    }
    f_UpdateEndingContinuePrompt(a);
}
/* func_8010D504, inlined */
static inline void inl_8010D504(u8 *a)
{
    u8 *s;

    func_80041098(a);
    if (a[0x70] == 0xFF) {
        s = D_800BF808;
        s[7] = 2;
        s[0x31] = 3;
        *(s16 *)(s + 0x32) = 0x1505;
        a[4] = 3;
    }
}
void f_UpdateEndingScriptController(u8 *a)
{
    u8 *p;

    switch (a[4]) {
    case 0:
        D_800BF870.pad1[0x17A] = 0;
        D_800BF870.pad1[0x1E5] = 0;
        D_800BF870.pad1[0x1E6] = 0;
        D_800BF854 = 0;
        switch (D_800BF870.pad1[0]) {
        case 2:
            func_80040CDC(a, 0, D_801158AC);
            break;
        case 4:
            func_80040CDC(a, 0, D_801159F4);
            break;
        case 5:
            func_80040CDC(a, 0, D_80115A14);
            break;
        }
        a[0x70] = 2;
        a[4]++;
        break;
    case 1:
        switch (D_800BF871) {
        case 2:
            inl_8010D490(a);
            break;
        case 4:
            inl_8010D504(a);
            break;
        case 5:
            func_80041098(a);
            if (a[0x70] == 0xFF) {
                a[4] = 3;
            }
            break;
        }
        p = D_800BF808;
        (*(s32 *)(p + 0x4C))++;
        break;
    case 2:
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

extern u8 D_800BF841;
s32 func_8010D460(void *arg0) {
    D_800BF841 = M2C_FIELD(arg0, u8 *, 0x72);
    return 1;
}

s32 func_8010D474(void *arg0) {
    M2C_FIELD(arg0, u8 *, 7) = (u8) (M2C_FIELD(arg0, u8 *, 7) + M2C_FIELD(arg0, u8 *, 0x72));
    return 1;
}

void func_8010D490(u8 *a)
{
    u8 *s;

    if (a[5] == 0) {
        func_80041098(a);
        if (a[0x70] == 0xFF) {
            s = D_800BF808;
            s[0x31] = 3;
            *(s16 *)(s + 0x32) = 0x1503;
            a[5]++;
        }
    }
    f_UpdateEndingContinuePrompt(a);
}

void func_8010D504(u8 *a)
{
    u8 *s;

    func_80041098(a);
    if (a[0x70] == 0xFF) {
        s = D_800BF808;
        s[7] = 2;
        s[0x31] = 3;
        *(s16 *)(s + 0x32) = 0x1505;
        a[4] = 3;
    }
}

void func_8010D558(void *arg0) {
    func_80041098();
    if (M2C_FIELD(arg0, u8 *, 0x70) == 0xFF) {
        M2C_FIELD(arg0, s8 *, 4) = 3;
    }
}

#define W(p, o) (*(s32 *)((u8 *)(p) + (o)))
void func_8010C1D8(u8 *a);
void func_8010D590(u8 *a)
{
    u8 *p = a + 0x60;
    s16 v;
    s32 t;
    s32 h;


    switch (a[4]) {
    case 0:
        a[0xB] = 0x20;
        W(a, 0x18) = (s32)func_8010C1D8;
        H(a, 0x80) = 0x46;
        H(a, 0x82) = 0x8C;
        a[0] = 2;
        a[4] = 1;
        a[5] = 0;
        a[6] = 0;
        a[7] = 0;
        H(a, 0x40) = 0;
        H(a, 0x42) = 0x100;
        a[0x29] = 0;
        H(a, 0x44) = 0;
    case 1:
        H(a, 0x40) += 0x100;
        if (H(a, 0x40) >= 0x600) {
            H(a, 0x40) -= 0x600;
        }
        h = H(a, 0x42);
        t = h * 704;
        v = (h * 24) / 32;
        H(p, 0xC) = v;
        H(p, 8) = v;
        if (v < 0x1000) {
            H(p, 0xC) = 0x1000;
            H(p, 8) = 0x1000;
        }
        switch (a[3]) {
        case 0:
        case 1:
        case 2:
        case 3:
            do {
                H(p, 0xA) = t / 32;
            } while (0);
            break;
        case 4:
            H(p, 0xA) = t / 45;
            break;
        case 7:
            H(p, 0xA) = -t / 45;
            break;
        case 6:
            H(p, 0xA) = t / 45;
            break;
        case 5:
            do {
                H(p, 0xA) = t / 32;
            } while (0);
            break;
        }
        H(p, 0) = U(a, 0x2E);
        H(p, 4) = U(a, 0x36);
        switch (a[3]) {
        case 4:
            H(p, 2) = U(a, 0x32) - (H(a, 0x42) * 504) / 256;
            break;
        case 7:
            H(p, 2) = U(a, 0x32) + (H(a, 0x42) * 504) / 256;
            break;
        case 6:
            H(p, 2) = U(a, 0x32) - (H(a, 0x42) * 504) / 256;
            break;
        case 0:
        case 1:
        case 2:
        case 3:
        case 5:
            H(p, 2) = U(a, 0x32) - (H(a, 0x42) * 896) / 256;
            break;
        }
        H(p, 0x10) = H(a, 0x42) * 16;
        if (a[3] != 8) {
            H(a, 0x84) = H(a, 0x86) = U(a, 0x32) - U(p, 2) + 0xC8;
        } else {
            H(a, 0x84) = 0;
            H(a, 0x86) = abs(H(a, 0x32) - H(p, 2)) + 0xC8;
        }
        H(a, 0x80) = 0x64;
        H(a, 0x82) = 0xC8;
        H(a, 0x54) = 0;
        H(a, 0x56) = -D_1F8000F2;
        H(a, 0x58) = 0;
        func_8007703C(a);
        break;
    case 2:
    case 3:
        func_8007A624(a);
        break;
    }
}

extern u8 D_800ECF58_6b74_80a7[];
extern u8 D_800A4BC8[];
extern u16 D_80115CB4[];
extern u8 *D_80115C9C[];
extern u8 D_8011B154[];
extern s16 D_1F800160;
extern s16 D_1F800164;
void func_8010D8F0(u8 *a)
{
    u8 *g;

    switch (a[4]) {
    case 0:
        g = D_800ECF58_6b74_80a7;
        if (func_800519E0(a, 0xC, *(s32 *)(g + 0x48), D_800A4BC8) != 0) {
            break;
        }
        *(s32 *)(a + 0x3C) = *(s32 *)(g + 0x4C);
        H(a, 0x56) = D_80115CB4[D_800BF870.pad1[0]];
        func_80040CDC(a, D_8011B154, D_80115C9C[D_800BF870.pad1[0]]);
        func_80041718(a, 0, 0);
        H(a, 0x80) = 0x8C;
        H(a, 0x82) = 0x118;
        H(a, 0x84) = 0x88;
        H(a, 0x86) = 0x110;
        a[0x70] = 1;
        H(a, 0xB8) = 0xC00;
        H(a, 0xBA) = 0xC00;
        H(a, 0xBC) = 0xC00;
        H(a, 0x50) = 0;
        H(a, 0x60) = 0;
        a[4]++;
        break;
    case 1:
        a[1] = 1;
        func_80077E7C(a);
        func_80041098(a);
        if (D_800BF841 == 0) {
            *(s32 *)(a + 0x30) += func_80083E80(H(a, 0x50) += 0x40) << 5;
            func_8004190C(a);
        }
        switch (D_800BF871) {
        case 3:
            break;
        case 4:
            if (a[5] == 1) {
                if ((H(a, 0x32) -= 8) < -0x833) {
                    a[5]++;
                }
            }
            break;
        case 5:
            H(a, 0x56) = func_80085690(H(a, 0x36) - D_1F800164, D_1F800160 - H(a, 0x2E)) & 0xFFF;
            break;
        }
        func_800518FC(a);
        break;
    case 2:
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

s32 func_8010DB44(void *arg0) {
    void *temp_v1;

    temp_v1 = M2C_FIELD(arg0, s16 *, 0x72) + arg0;
    M2C_FIELD(temp_v1, u8 *, 4) = (u8) (M2C_FIELD(temp_v1, u8 *, 4) + 1);
    return 1;
}

#define W(p, o) (*(s32 *)((u8 *)(p) + (o)))
extern u8 *D_1F800248;
extern s32 D_800ECF58_a4fb[];
extern u8 D_8011A738[];
extern u8 D_80117868[];
extern u16 D_80116050[];
extern s32 D_80116038[];
void func_8010DB68(u8 *a)
{
    s32 s = a[4];
    u8 *p;
    u8 *o;

    switch (s) {
    case 0:
        p = (u8 *)D_800ECF58_a4fb;
        if (func_800519E0(a, 0xF, W(p, 0x94), D_80117868) == 0) {
            W(a, 0x3C) = W(p, 0x38);
            H(a, 0x56) = D_80116050[D_800BF870.pad1[0]];
            func_80040CDC(a, D_8011A738, D_80116038[D_800BF870.pad1[0]]);
            func_80041718(a, 9, 0);
            H(a, 0x80) = 0x60;
            H(a, 0x82) = 0xC0;
            H(a, 0x84) = 0x80;
            H(a, 0x86) = 0xF0;
            a[0x70] = 1;
            a[0x5E] = 0;
            H(a, 0x60) = 0;
            a[4]++;
            a[0xB] = (a[0xB] & 0xC0) | 0x80;
        }
        break;
    case 1:
        a[1] = 1;
        func_80077E7C(a);
        func_80041098(a);
        if (a[0x5E] == 0) {
            func_8004190C(a);
        }
        switch (D_800BF871) {
        case 3:
            break;
        case 4:
            switch (a[5]) {
            case 1:
                H(a, 0x44) = 0xC00;
                H(a, 0x48) = func_80083F50(H(a, 0x56)) >> 4;
                H(a, 0x4C) = -func_80083E80(H(a, 0x56)) >> 4;
                H(a, 0x4A) = -0x2000;
                H(a, 0x50) = 0x100;
                a[0xB] &= 0x3F;
                a[5]++;
            case 2:
                W(a, 0x30) += H(a, 0x4A) << 8;
                W(a, 0x2C) += H(a, 0x48) * H(a, 0x44);
                H(a, 0x4A) += H(a, 0x50);
                W(a, 0x34) += H(a, 0x4C) * H(a, 0x44);
                if (H(a, 0x32) >= -0x4B0) {
                    a[5]++;
                }
                break;
            }
            break;
        case 5:
            switch (a[5]) {
            case 0:
                a[0xB] &= 0x3F;
                a[5]++;
                o = D_1F800248;
                H(a, 0x4E) = U(a, 0x2E) - U(o, 0x2E);
                H(a, 0x50) = U(a, 0x32) - U(o, 0x32);
                H(a, 0x52) = U(a, 0x36) - U(o, 0x36);
            case 1:
                func_80111CFC(a);
                H(a, 0x32) += 0x14;
                break;
            case 2:
                func_80111CFC(a);
                break;
            case 3:
                H(a, 0x44) = 0xC00;
                H(a, 0x48) = func_80083F50(H(a, 0x56)) >> 4;
                H(a, 0x4C) = -func_80083E80(H(a, 0x56)) >> 4;
                H(a, 0x4A) = -0x2000;
                H(a, 0x50) = 0x100;
                H(a, 0x40) = 0x1E;
                a[5]++;
            case 4:
                W(a, 0x30) += H(a, 0x4A) << 8;
                H(a, 0x4A) += H(a, 0x50);
                W(a, 0x2C) += H(a, 0x48) * H(a, 0x44);
                W(a, 0x34) += H(a, 0x4C) * H(a, 0x44);
                if (--H(a, 0x40) <= 0) {
                    a[5]++;
                }
                break;
            }
            break;
        }
        func_800518FC(a);
        break;
    case 2:
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

s32 func_8010DF90(void *arg0) {
    void *temp_v1;

    temp_v1 = M2C_FIELD(arg0, s16 *, 0x72) + arg0;
    M2C_FIELD(temp_v1, u8 *, 4) = (u8) (M2C_FIELD(temp_v1, u8 *, 4) + 1);
    return 1;
}

s32 func_8010DFB4(void *arg0) {
    M2C_FIELD(arg0, s8 *, 0x5E) = 1;
    return 1;
}

s32 func_8010DFC4(u8 *a)
{
    if (D_800BF841 != 0) {
        a[0x5E] = 1;
        return 1;
    }
    return 0;
}

#define S16F(p, o) (((struct { u8 pad[o]; s16 v; } *)(p))->v)
#define U8F(p, o) (((struct { u8 pad[o]; u8 v; } *)(p))->v)
typedef struct {
    s16 vx, vy, vz, pad;
} SVec;
typedef struct {
    s32 vx, vy, vz, pad;
} LVec;
extern SVec D_1F8000C0;
extern LVec D_1F8000A0;
extern u8 *D_1F80024C;
extern u8 D_800BFA56;
extern u8 D_80117338[];
extern u8 D_8011AF2C[];
extern u8 D_800A3D18[];
/* func_8010E45C, inlined */
static inline void inl_8010E45C(u8 *a)
{
    u8 *o;

    D_1F8000C0.vx = -0x55;
    D_1F8000C0.vy = -0x7E;
    D_1F8000C0.vz = 0x1F;
    func_80084470(D_1F800248 + 0x98, &D_1F8000C0, &D_1F8000A0);
    o = D_1F800248;
    *(s16 *)(a + 0x2E) = *(s16 *)(o + 0x2E) + D_1F8000A0.vx;
    *(s16 *)(a + 0x32) = *(s16 *)(o + 0x32) + D_1F8000A0.vy;
    *(s16 *)(a + 0x36) = *(s16 *)(o + 0x36) + D_1F8000A0.vz;
    *(s16 *)(a + 0x56) = *(s16 *)(o + 0x56);
}
/* func_8010E530, inlined */
static inline void inl_8010E530(u8 *a)
{
    *(s16 *)(a + 0x56) = 0x1BC;
    D_800E7ED6 = 0x309;
    a[0xB] = (a[0xB] & 0xC0) | 0x80;
    func_80041718(a, 3, 0);
    func_80040D68(a, D_8011605C);
    a[0x70] = 2;
}
/* func_8010E5F0, inlined */
static inline void inl_8010E5F0(u8 *a)
{
    a[0xB] = (a[0xB] & 0xC0) | 0x80;
    func_80041718(a, 3, 0);
    *(s16 *)(a + 0x56) = func_800782B0(a + 0x2C, D_1F800160, D_1F800164);
    D_1F80024C = a;
}
void func_8010DFEC(u8 *a)
{
    s32 *o;
    s32 v;

    switch (a[4]) {
    case 0:
        o = D_800ECF58_a4fb;
        if (func_800519E0(a, 0xF, o[0x58 / 4], D_80117338) != 0) {
            break;
        }
        if (D_800BF870.pad1[0] != 1) {
            func_80051B04(*(u8 **)(a + 0xC0), 0x16, 0x10);
            func_80051B04(*(u8 **)(a + 0xC4), 0x16, 0xF);
        }
        a[4]++;
        func_80040CDC(a, D_8011AF2C, D_800A3D18);
        v = o[0x80 / 4];
        U8F(a, 0x7B) = 3;
        S16F(a, 0x80) = 0x50;
        S16F(a, 0x82) = 0xA0;
        S16F(a, 0x84) = 0xA0;
        S16F(a, 0x86) = 0x140;
        *(s32 *)(a + 0x3C) = v;
        switch (D_800BF870.pad1[0]) {
        case 1:
            func_80041718(a, 1, 0);
            break;
        case 2:
            inl_8010E530(a);
            break;
        case 5:
            inl_8010E5F0(a);
            break;
        }
        break;
    case 1:
        switch (D_800BF870.pad1[0]) {
        case 1:
            inl_8010E45C(a);
            break;
        case 2:
            if (a[5] == 0) {
                func_80041098(a);
                if (a[0x70] == 0xFF) {
                    a[5]++;
                }
            }
            break;
        case 5:
            switch (a[5]) {
            case 0:
                if (D_800BF870.pad1[0x1E5] >= 2) {
                    func_80041718(a, 8, 4);
                    a[5]++;
                }
                break;
            case 1:
                if (D_800BF870.pad1[0x1E6] >= 3) {
                    func_80041718(a, 10, 4);
                    a[5]++;
                }
                break;
            }
            *(s16 *)(a + 0x56) = func_800776F8((s16)func_800782B0(a + 0x2C, D_1F800160, D_1F800164), *(s16 *)(a + 0x56), 0x80);
            break;
        }
        a[1] = 1;
        func_80077E7C(a);
        func_800518FC(a);
        if (D_800BF841 == 0) {
            func_8004190C(a);
        }
        break;
    case 2:
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

extern s32 D_800ECFD8;
extern s32 D_800ECF90;
s32 func_8010E3D4(u8 *p)
{
    if (!(*(s16 *)(p + 0x72) & 0x8000)) {
        *(s32 *)(p + 0x3C) = D_800ECFD8;
        *(void **)(p + 0x7C) = D_8011AF2C;
    } else {
        *(s32 *)(p + 0x3C) = D_800ECF90;
        *(void **)(p + 0x7C) = D_8011A738;
    }
    func_80041718(p, *(u16 *)(p + 0x72) & 0xFFF, 0);
    return 1;
}

void func_8010E438(s32 a)
{
    func_80041718(a, 1, 0);
}

void func_8010E45C(u8 *a)
{
    u8 *o;

    D_1F8000C0.vx = -0x55;
    D_1F8000C0.vy = -0x7E;
    D_1F8000C0.vz = 0x1F;
    func_80084470(D_1F800248 + 0x98, &D_1F8000C0, &D_1F8000A0);
    o = D_1F800248;
    *(s16 *)(a + 0x2E) = *(s16 *)(o + 0x2E) + D_1F8000A0.vx;
    *(s16 *)(a + 0x32) = *(s16 *)(o + 0x32) + D_1F8000A0.vy;
    *(s16 *)(a + 0x36) = *(s16 *)(o + 0x36) + D_1F8000A0.vz;
    *(s16 *)(a + 0x56) = *(s16 *)(o + 0x56);
}

s32 func_8010E51C(void *arg0) {
    D_800BF850 = (s32) M2C_FIELD(arg0, s16 *, 0x72);
    return 1;
}

void func_8010E530(u8 *a)
{
    *(s16 *)(a + 0x56) = 0x1BC;
    D_800E7ED6 = 0x309;
    a[0xB] = (a[0xB] & 0xC0) | 0x80;
    func_80041718(a, 3, 0);
    func_80040D68(a, D_8011605C);
    a[0x70] = 2;
}

void func_8010E598(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 5) == 0) {
        func_80041098();
        if (M2C_FIELD(arg0, u8 *, 0x70) == 0xFF) {
            M2C_FIELD(arg0, u8 *, 5) = (u8) (M2C_FIELD(arg0, u8 *, 5) + 1);
        }
    }
}

void func_80111744();
void func_8010E5F0(u8 *a)
{
    a[0xB] = (a[0xB] & 0xC0) | 0x80;
    func_80041718(a, 3, 0);
    *(s16 *)(a + 0x56) = func_800782B0(a + 0x2C, D_1F800160, D_1F800164);
    D_1F80024C = a;
}

void func_8010E650(u8 *a)
{
    switch (a[5]) {
    case 0:
        if (D_800BFA56 >= 2) {
            func_80041718(a, 8, 4);
            a[5]++;
        }
        break;
    case 1:
        if (D_800BFA57 >= 3) {
            func_80041718(a, 10, 4);
            a[5]++;
        }
        break;
    }
    *(s16 *)(a + 0x56) = func_800776F8((s16)func_800782B0(a + 0x2C, D_1F800160, D_1F800164), *(s16 *)(a + 0x56), 0x80);
}

extern u8 D_8011AD3C[];
extern u8 D_80116374[];
extern u8 D_801162BC[];
extern u8 D_801162DC[];
void f_UpdateEndingCompletionBranchScript(u8 *a)
{
    u8 *g;
    s32 n, m;

    switch (a[5]) {
    case 0:
        a[5] = 1;
        func_80040CDC(a, D_8011AD3C, D_80116374);
        a[0x70] = 2;
        break;
    case 1:
        func_80041098(a);
        if (a[0x70] == 0xFF) {
            a[5]++;
            g = (u8 *)&D_800BF808_76d5;
            n = W(g, 0x50);
            m = W(g, 0x54);
            if (n < 0x85) {
                if (n < 0x64) {
                    a[0x7A] = 2;
                } else {
                    a[0x7A] = 3;
                }
                func_80040CDC(a, D_8011AD3C, D_801162BC);
                a[0xBF] = 0;
            } else {
                if (m == 4) {
                    a[0x7A] = 5;
                    a[0xBF] = 2;
                } else {
                    a[0x7A] = 4;
                    a[0xBF] = 1;
                }
                func_80040CDC(a, D_8011AD3C, D_801162DC);
            }
            a[0x70] = 2;
        }
        break;
    case 2:
        func_80041098(a);
        if (a[0x70] == 0xFF) {
            a[5]++;
            func_80074EEC();
            {
                u8 *g2 = (u8 *)&D_800BF808_76d5;
                g2[7] = 2;
                if (a[0xBF] == 0) {
                    g2[0x31] = 8;
                } else {
                    g2[0x31] = 3;
                    H(g2, 0x32) = 0x1504;
                }
            }
        }
        break;
    }
}

extern u8 D_80117438[];
void func_8010E8B8(u8 *a)
{
    u8 *g;
    u8 *s;

    switch (a[4]) {
    case 0:
        g = D_800ECF58_6b74_80a7;
        if (func_800519E0(a, 0xD, *(s32 *)(g + 0x60), D_80117438) != 0) {
            break;
        }
        *(s32 *)(a + 0x3C) = *(s32 *)(g + 0x88);
        H(a, 0x80) = 0x50;
        H(a, 0x82) = 0xA0;
        H(a, 0x84) = 0xA0;
        H(a, 0x86) = 0x120;
        a[4]++;
        a[0xB] = (a[0xB] & 0xC0) | 0x80;
        s = (u8 *)&D_800BF870;
        switch (s[1]) {
        case 3:
            if (s[0xC9] == 0xFF) {
                u8 *p = D_800BF808;
                W(p, 0x54)++;
            }
            if (s[0xCA] == 0xFF) {
                u8 *p = D_800BF808;
                W(p, 0x54)++;
            }
            if (s[0xCC] == 0xFF) {
                u8 *p = D_800BF808;
                W(p, 0x54)++;
            }
            if (s[0xCD] == 0xFF) {
                u8 *p = D_800BF808;
                W(p, 0x54)++;
            }
            {
                u8 *p = D_800BF808;
                W(p, 0x50) = H(s, 0x3A) - W(p, 0x54);
            }
            func_80077C40(a, D_8011AD3C, 0);
            break;
        case 4:
            func_80077C40(a, D_8011AD3C, 0);
            H(a, 0x56) = func_800782B0(a + 0x2C, D_1F800160, D_1F800164);
            break;
        case 5:
            func_80077C40(a, D_8011AD3C, 1);
            H(a, 0x56) = func_800782B0(a + 0x2C, D_1F800160, D_1F800164);
            break;
        }
        break;
    case 1:
        switch (D_800BF871) {
        case 3:
            f_UpdateEndingCompletionBranchScript(a);
            break;
        case 4:
        case 5:
            if (D_800BF841 != 0) {
                a[1] = 1;
                func_80077E7C(a);
                return;
            }
            H(a, 0x56) = func_800776F8((s16)func_800782B0(a + 0x2C, D_1F800160, D_1F800164), H(a, 0x56), 0x80);
            break;
        }
        a[1] = 1;
        func_80077E7C(a);
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

s32 func_8010EB90(u8 *a)
{
    u8 *r = func_80072DDC(a, 0, 3, 0x10);

    if (r != NULL) {
        *(void **)(r + 0x1C) = func_80111744;
        r[3] = 5;
        r[0x5E] = a[0xBF] - 1;
        return 1;
    }
    return 0;
}

extern s8 D_800BFA58;
extern M2C_UNK D_800E7E80;
s32 func_8010EBF0(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0xBF) == 1) {
        D_800BFA58 = 0;
    } else {
        D_800BFA58 = 1;
    }
    func_801094B8(&D_800E7E80);
    return 1;
}

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_8010EC30);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_8010EF28);

void func_8010F250(u8 *a)
{
    if (D_800BF841 != 0) {
        a[1] = 1;
        func_80077E7C(a);
        return;
    }
    switch (a[5]) {
    case 0:
        if (D_800BFA56 != 0) {
            a[5]++;
            func_80041718(a, 1, 4);
        }
        break;
    case 1:
        if (D_800BFA57 != 0) {
            a[5] = 2;
            func_80041718(a, 0, 4);
        }
        break;
    }
    *(s16 *)(a + 0x56) = func_800776F8((s16)func_800782B0(a + 0x2C, D_1F800160, D_1F800164), *(s16 *)(a + 0x56), 0x80);
    a[1] = 1;
    func_80077E7C(a);
    func_8004190C(a);
    func_800518FC(a);
}

extern u8 D_801173B0[];
extern u8 D_8011AC80[];
extern u8 D_801163F8[];
void func_8010F34C(u8 *a)
{
    s32 *o;
    s32 s = a[4];

    switch (s) {
    case 0:
        o = D_800ECF58_a4fb;
        if (func_800519E0(a, 0x11, o[0x50 / 4], D_801173B0) != 0) {
            break;
        }
        a[4]++;
        func_80040CDC(a, D_8011AC80, D_800A3D18);
        *(s32 *)(a + 0x3C) = o[0x90 / 4];
        func_80041718(a, 0, 0);
        *(s16 *)(a + 0x80) = 0x60;
        *(s16 *)(a + 0x82) = 0xC0;
        *(s16 *)(a + 0x84) = 0xA0;
        *(s16 *)(a + 0x86) = 0x150;
        a[0xB] = (a[0xB] & 0xC0) | 0x80;
        if (D_800BF871 == 4) {
            D_800E7ED6 = 0x800;
            func_80040D68(a, D_801163F8);
            a[0x70] = 2;
        }
        *(s16 *)(a + 0x56) = func_800782B0(a + 0x2C, D_1F800160, D_1F800164);
        break;
    case 1:
        switch (D_800BF870.pad1[0]) {
        case 4:
            if (D_800BF870.pad1[0x1E4] >= 2) {
                a[1] = s;
            }
            if (a[5] == 0) {
                inl_8010D504(a);
            }
            if (a[1] != 0) {
                func_80077E7C(a);
                func_8004190C(a);
                func_800518FC(a);
            }
            break;
        case 5:
            func_8010F250(a);
            break;
        }
        break;
    case 2:
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

extern u8 D_800A43E8[];
extern u8 D_8001B354[];
extern u8 D_800E7E80_f78d[];
extern s16 D_801164B0[];
extern s16 D_80116D98[];
extern s16 D_1F8000C0_65b0[];
extern s32 D_1F8000A0_5306[];
extern s16 D_1F800162_a8d4;
static inline void follow(u8 *a, s16 *t, s32 lim)
{
    if (H(a, 0x42) != -1) {
        s16 *p = &t[H(a, 0x42) * 3];
        H(a, 0x2E) = p[0];
        H(a, 0x32) = p[1];
        H(a, 0x36) = p[2];
        if (++H(a, 0x42) >= lim) {
            H(a, 0x42) = -1;
        }
    }
}
static inline s16 *at(s16 *t, u8 *a)
{
    return &t[H(a, 0x42) * 3];
}
void func_8010F56C(u8 *a)
{
    u8 *g;
    s16 *p;
    s16 *p_f;

    switch (a[4]) {
    case 0:
        g = D_800ECF58_6b74_80a7;
        if (func_800519E0(a, 0x12, *(s32 *)(g + 0x14), D_800A43E8) != 0) {
            break;
        }
        *(s32 *)(a + 0x3C) = *(s32 *)(g + 0x18);
        H(a, 0x80) = 0x8C;
        H(a, 0x82) = 0x118;
        H(a, 0x84) = 0x88;
        H(a, 0x86) = 0x110;
        a[4]++;
        switch (D_800BF871) {
        case 1:
            H(a, 0x42) = 0;
            func_80077C40(a, D_8001B354, 3);
            func_80054D14(D_800E7E80_f78d, 0xE4, 0);
            H(a, 0x2E) = 0x50;
            H(a, 0x36) = -0x50;
            H(a, 0x32) = 0;
            D_1F800248 = a;
            break;
        case 5:
            func_80077C40(a, D_8001B354, 5);
            H(a, 0x56) = func_800782B0(a + 0x2C, D_1F800160, D_1F800164);
            a[0xB] = (a[0xB] & 0xC0) | 0x40;
            break;
        }
        break;
    case 1:
        if (D_800BF841 != 0) {
            a[1] = 1;
            func_80077E7C(a);
            break;
        }
        func_8004190C(a);
        switch (D_800BF871) {
        case 1:
            switch (a[5]) {
            case 0:
                if (D_800BFA55 != 1) {
                    break;
                }
                a[5]++;
                follow(a, D_801164B0, 0x17C);
                break;
            case 1:
                follow(a, D_801164B0, 0x17C);
                if (D_800BFA55 == 4) {
                    H(a, 0x42) = 0;
                    a[5]++;
                }
                break;
            case 2:
                p = D_80116D98;
                H(a, 0x2E) = p[0];
                H(a, 0x32) = p[1];
                H(a, 0x36) = p[2];
                H(a, 0x56) = func_800782B0(a + 0x2C, p[0], p[2]);
                a[5]++;
                break;
            case 3:
                if (D_800BFA55 == 5) {
                    a[5]++;
                }
                break;
            case 4:
                p_f = at(D_80116D98, a);
                H(a, 0x56) = func_800782B0(a + 0x2C, p_f[0], p_f[2]);
                if (H(a, 0x42) >= 0xDD) {
                    a[5]++;
                }
            case 5:
                follow(a, D_80116D98, 0xF0);
                break;
            }
            {
                s16 *v = D_1F8000C0_65b0;
                s32 *o = D_1F8000A0_5306;

                v[0] = -5;
                v[1] = -0x6E;
                v[2] = 0;
                func_80084470(a + 0x98, v, o);
                {
                u8 *pl = D_800E7E80_f78d;
                s16 x, y, z;

                H(pl, 0x2E) = x = H(a, 0x2E) + D_1F8000A0_5306[0];
                H(pl, 0x32) = y = H(a, 0x32) + o[1];
                D_1F800160 = x;
                H(pl, 0x36) = z = H(a, 0x36) + o[2];
                D_1F800162_a8d4 = y;
                H(pl, 0x56) = H(a, 0x56);
                D_1F800164 = z;
                a[1] = 1;
                func_80077E7C(a);
                }
            }
            break;
        case 5:
            a[1] = 1;
            func_80077E7C(a);
            break;
        }
        func_800518FC(a);
        break;
    case 2:
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

extern u8 D_801177F0[];
extern u8 D_8011A738_e3cb_78c6[];
void func_8010FA48(u8 *a)
{
    u8 *g;
    u8 *s;

    switch (a[4]) {
    case 0:
        g = D_800ECF58_6b74_80a7;
        if (func_800519E0(a, 0xF, *(s32 *)(g + 0x7C), D_801177F0) == 0) {
            *(s32 *)(a + 0x3C) = *(s32 *)(g + 0x38);
            if (D_800BF871 == 4) {
                func_80077C40(a, D_8011A738_e3cb_78c6, 0x11);
            } else {
                func_80077C40(a, D_8011A738_e3cb_78c6, 2);
            }
            *(s16 *)(a + 0x80) = 0x80;
            *(s16 *)(a + 0x82) = 0x100;
            *(s16 *)(a + 0x84) = 0xE0;
            a[4]++;
            a[0xB] = (a[0xB] & 0xC0) | 0x80;
            MEMBER_AT(s16, a, 0x86) = 0x180;
            *(s16 *)(a + 0x56) = func_800782B0(a + 0x2C, D_1F800160, D_1F800164);
        }
        break;
    case 1:
        s = (u8 *)&D_800BF870;
        if (s[1] == 4) {
            if (a[5] != 0) {
                break;
            }
            if (s[0x1E5] >= 2) {
                a[5] = 1;
                break;
            }
            a[1] = 1;
            goto tail;
        }
        if (D_800BF841 != 0) {
            a[1] = 1;
            func_80077E7C(a);
            break;
        }
        if (a[5] == 0 && s[0x1E7] >= 3) {
            a[5] = 1;
            func_80077CFC(a, D_8011A738_e3cb_78c6, 0x11, 4);
        }
        a[1] = 1;
    tail:
        func_80077E7C(a);
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

/* extern */
M2C_UNK func_800518FC(void *);
/* extern */
s32 func_800519E0(void *, M2C_UNK, s32, M2C_UNK *);
/* extern */
M2C_UNK func_80077C40(void *, M2C_UNK *, M2C_UNK);
/* extern */
M2C_UNK func_80077E7C(void *);
/* extern */
s16 func_800782B0(void *, s16, s16);
/* extern */
M2C_UNK func_8007A624(void *);
/* extern */
extern u8 D_800BFA55;
extern M2C_UNK D_800ECF58_6b74;
extern M2C_UNK D_801174A0;
extern M2C_UNK D_8011AEAC;
void func_8010FC58(u8 *a)
{
    u8 *g;

    switch (a[4]) {
    case 0:
        g = (u8 *)&D_800ECF58_6b74;
        if (func_800519E0(a, 0x11, *(s32 *)(g + 0x54), &D_801174A0) == 0) {
            *(s32 *)(a + 0x3C) = (s32) *(s32 *)(g + 0x8C);
            func_80077C40(a, &D_8011AEAC, 1);
            *(s16 *)(a + 0x80) = 0x80;
            *(s16 *)(a + 0x82) = 0x100;
            *(s16 *)(a + 0x84) = 0xA0;
            a[4]++;
            a[0xB] = (u8) ((a[0xB] & 0xC0) | 0x80);
            MEMBER_AT(s16, a, 0x86) = 0x130;
            *(s16 *)(a + 0x56) = func_800782B0(a + 0x2C, D_1F800160, D_1F800164);
            return;
        }
        break;
    case 1:
        if (a[5] == 0) {
            if ((u8) D_800BFA55 >= 2U) {
                a[5] = 1;
                return;
            }
            a[1] = 1;
            func_80077E7C(a);
            func_8004190C(a);
            func_800518FC(a);
            return;
        }
        break;
    case 2:
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

/* extern */
M2C_UNK func_800518FC(void *);
/* extern */
s32 func_800519E0(void *, M2C_UNK, s32, M2C_UNK *);
/* extern */
M2C_UNK func_80077C40(void *, M2C_UNK *, M2C_UNK);
/* extern */
M2C_UNK func_80077E7C(void *);
/* extern */
s16 func_800782B0(void *, s16, s16);
/* extern */
M2C_UNK func_8007A624(void *);
/* extern */
extern u8 D_800BFA55;
extern M2C_UNK D_80117590;
extern M2C_UNK D_8011A738_e3cb;
void func_8010FDB4(u8 *a)
{
    u8 *g;

    switch (a[4]) {
    case 0:
        g = (u8 *)&D_800ECF58_6b74;
        if (func_800519E0(a, 0xF, *(s32 *)(g + 0x74), &D_80117590) == 0) {
            *(s32 *)(a + 0x3C) = (s32) *(s32 *)(g + 0x38);
            func_80077C40(a, &D_8011A738_e3cb, 7);
            *(s16 *)(a + 0x80) = 0x5A;
            *(s16 *)(a + 0x82) = 0xB4;
            *(s16 *)(a + 0x84) = 0x80;
            a[4]++;
            a[0xB] = (u8) ((a[0xB] & 0xC0) | 0x80);
            MEMBER_AT(s16, a, 0x86) = 0xE0;
            *(s16 *)(a + 0x56) = func_800782B0(a + 0x2C, D_1F800160, D_1F800164);
            return;
        }
        break;
    case 1:
        if (a[5] == 0) {
            if ((u8) D_800BFA55 >= 2U) {
                a[5] = 1;
                return;
            }
            a[1] = 1;
            func_80077E7C(a);
            func_8004190C(a);
            func_800518FC(a);
            return;
        }
        break;
    case 2:
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

typedef struct { u8 pad[0x38]; s32 x38; u8 pad2[0x28]; s32 x64; s32 x68; s32 x6C; s32 x70; } OtCtx;
extern OtCtx D_800ECF58;
typedef struct { u8 pad[0x80]; s16 w[4]; } Box80;
extern u8 D_80117688[];
void func_8010FF10(u8 *a)
{
    s32 s = a[4];
    switch (s) {
    case 0:
        if (func_800519E0(a, 15, D_800ECF58.x68, D_80117688) != 0) {
            break;
        }
        *(s32 *)(a + 0x3C) = D_800ECF58.x38;
        func_80077C40(a, D_8011A738, 3);
        *(s16 *)(a + 0x80) = 0x60;
        *(s16 *)(a + 0x82) = 0xC0;
        *(s16 *)(a + 0x84) = 0x80;
        a[4]++;
        a[0xB] = (a[0xB] & 0xC0) | 0x80;
        ((Box80 *)a)->w[3] = 0x100;
        *(s16 *)(a + 0x56) = func_800782B0(a + 0x2C, D_1F800160, D_1F800164);
        break;
    case 1:
        if (D_800BF841 != 0) {
            a[1] = s;
            func_80077E7C(a);
            break;
        }
        *(s16 *)(a + 0x56) = func_800776F8((s16)func_800782B0(a + 0x2C, D_1F800160, D_1F800164), *(s16 *)(a + 0x56), 0x80);
        a[1] = s;
        func_80077E7C(a);
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

extern u8 D_80117610[];
void func_80110094(u8 *a)
{
    s32 s = a[4];
    switch (s) {
    case 0:
        if (func_800519E0(a, 15, D_800ECF58.x6C, D_80117610) != 0) {
            break;
        }
        *(s32 *)(a + 0x3C) = D_800ECF58.x38;
        func_80077C40(a, D_8011A738, 1);
        *(s16 *)(a + 0x80) = 0x60;
        *(s16 *)(a + 0x82) = 0xC0;
        *(s16 *)(a + 0x84) = 0x80;
        a[4]++;
        a[0xB] = (a[0xB] & 0xC0) | 0x80;
        ((Box80 *)a)->w[3] = 0xE0;
        *(s16 *)(a + 0x56) = func_800782B0(a + 0x2C, D_1F800160, D_1F800164);
        break;
    case 1:
        if (D_800BF841 != 0) {
            a[1] = s;
            func_80077E7C(a);
            break;
        }
        *(s16 *)(a + 0x56) = func_800776F8((s16)func_800782B0(a + 0x2C, D_1F800160, D_1F800164), *(s16 *)(a + 0x56), 0x80);
        a[1] = s;
        func_80077E7C(a);
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

extern u8 D_80117700[];
void func_80110218(u8 *a)
{
    s32 s = a[4];
    switch (s) {
    case 0:
        if (func_800519E0(a, 15, D_800ECF58.x70, D_80117700) != 0) {
            break;
        }
        *(s32 *)(a + 0x3C) = D_800ECF58.x38;
        func_80077C40(a, D_8011A738, 0);
        *(s16 *)(a + 0x80) = 0x60;
        *(s16 *)(a + 0x82) = 0xC0;
        *(s16 *)(a + 0x84) = 0x80;
        a[4]++;
        a[0xB] = (a[0xB] & 0xC0) | 0x80;
        ((Box80 *)a)->w[3] = 0xD0;
        *(s16 *)(a + 0x56) = func_800782B0(a + 0x2C, D_1F800160, D_1F800164);
        break;
    case 1:
        if (D_800BF841 != 0) {
            a[1] = s;
            func_80077E7C(a);
            break;
        }
        *(s16 *)(a + 0x56) = func_800776F8((s16)func_800782B0(a + 0x2C, D_1F800160, D_1F800164), *(s16 *)(a + 0x56), 0x80);
        a[1] = s;
        func_80077E7C(a);
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

extern u8 D_80117518[];
void func_8011039C(u8 *a)
{
    s32 s = a[4];
    switch (s) {
    case 0:
        if (func_800519E0(a, 15, D_800ECF58.x64, D_80117518) != 0) {
            break;
        }
        *(s32 *)(a + 0x3C) = D_800ECF58.x38;
        if (D_800BF871 == 4) {
            func_80077C40(a, D_8011A738, 4);
        } else {
            func_80077C40(a, D_8011A738, 5);
        }
        *(s16 *)(a + 0x80) = 0x80;
        *(s16 *)(a + 0x82) = 0x100;
        *(s16 *)(a + 0x84) = 0x80;
        a[4]++;
        a[0xB] = (a[0xB] & 0xC0) | 0x80;
        ((Box80 *)a)->w[3] = 0x144;
        *(s16 *)(a + 0x56) = func_800782B0(a + 0x2C, D_1F800160, D_1F800164);
        break;
    case 1:
        if (D_800BF841 != 0) {
            a[1] = s;
            func_80077E7C(a);
            break;
        }
        *(s16 *)(a + 0x56) = func_800776F8((s16)func_800782B0(a + 0x2C, D_1F800160, D_1F800164), *(s16 *)(a + 0x56), 0x80);
        a[1] = s;
        func_80077E7C(a);
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

/* extern */
s16 func_800776F8(s16, s16, M2C_UNK);
/* extern */
extern M2C_UNK D_800ECF58_6b74;
extern M2C_UNK D_80117778;
void func_80110548(u8 *a)
{
    u8 *g;

    switch (a[4]) {
    case 0:
        g = (u8 *)&D_800ECF58_6b74;
        if (func_800519E0(a, 0xF, *(s32 *)(g + 0x78), &D_80117778) == 0) {
            *(s32 *)(a + 0x3C) = (s32) *(s32 *)(g + 0x38);
            func_80077C40(a, &D_8011A738_e3cb, 0x10);
            *(s16 *)(a + 0x80) = 0x60;
            *(s16 *)(a + 0x82) = 0xC0;
            *(s16 *)(a + 0x84) = 0x80;
            a[4]++;
            a[0xB] = (u8) ((a[0xB] & 0xC0) | 0x80);
            MEMBER_AT(s16, a, 0x86) = 0x13A;
            *(s16 *)(a + 0x56) = func_800782B0(a + 0x2C, D_1F800160, D_1F800164);
            return;
        }
        break;
    case 1:
        *(s16 *)(a + 0x56) = func_800776F8(func_800782B0(a + 0x2C, D_1F800160, D_1F800164), *(s16 *)(a + 0x56), 0x80);
        a[1] = 1;
        func_80077E7C(a);
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

extern Range D_8011A5BC[];
extern Range D_8011A5D4[];
extern Range D_8011A640[];
extern u8 *D_1F80021C;
void func_801106A8(s16 kind, s16 idx)
{
    Range *t;
    s32 n, base;
    u8 *p;
    switch (kind) {
    case 0:
        t = D_8011A5BC;
        n = 3;
        base = 0;
        break;
    case 1:
        t = D_8011A5D4;
        n = 0x1F;
        base = 843;
        break;
    case 2:
        t = D_8011A640;
        n = 18;
        base = 1083;
        break;
    default:
        return;
    }
    p = D_1F80021C + t[idx].a * 32 + base * 32;
    func_8001D2A8(n, p, p + (t[idx].b + 1) * 32, 0);
}

extern s16 D_800A4F7E;
extern M2C_UNK D_801179E0;
extern M2C_UNK D_80118AA8;
extern M2C_UNK D_80119AA0;
void func_80110774(void) {
    func_80075448(0xA, &D_801179E0, 0x16, D_800A4F7E);
    func_80075448(0xB, &D_80118AA8, 0x10, D_800A4F7E);
    func_80075448(0xC, &D_80119AA0, 0x10, D_800A4F7E);
}

extern s16 D_800ED098;
typedef struct { u8 pad[0xC0]; u8 *parts[1]; } PartsOwner;
typedef struct { s16 v[5]; } PartInit5;
extern PartInit5 D_8011A678[];
void func_801107DC(PartsOwner *a)
{
    s32 i;
    u8 *q;

    a->pad[8] = 2;
    if (D_800ED098 < a->pad[8]) {
        a->pad[4] = 3;
        return;
    }
    a->pad[9] = 2;
    a->pad[0xD] = 0;
    for (i = 0; i < a->pad[8]; i++) {
        q = func_8007AAE8();
        a->parts[i] = q;
        *(s16 *)(q + 6) = D_8011A678[i].v[0];
        *(s16 *)(a->parts[i] + 0) = D_8011A678[i].v[1];
        *(s16 *)(a->parts[i] + 2) = D_8011A678[i].v[2];
        *(s16 *)(a->parts[i] + 4) = D_8011A678[i].v[3];
        *(s16 *)(a->parts[i] + 8) = 0;
        *(s16 *)(a->parts[i] + 0xA) = 0;
        *(s16 *)(a->parts[i] + 0xC) = 0;
        func_80051B04(a->parts[i], 0xC, D_8011A678[i].v[4]);
    }
    *(s16 *)(a->pad + 0x80) = 0x8C;
    *(s16 *)(a->pad + 0x82) = 0x118;
    *(s16 *)(a->pad + 0x84) = 0x8C;
    *(s16 *)(a->pad + 0x86) = 0x8C;
    a->pad[0xB] = (a->pad[0xB] & 0xC0) | 0x80;
}

extern PartInit5 D_8011A68C[];
void func_80110918(PartsOwner *a)
{
    s32 i;
    u8 *q;
    s32 n;

    a->pad[8] = 3;
    n = 3;
    if (D_800ED098 < n) {
        a->pad[4] = n;
        return;
    }
    a->pad[9] = n;
    a->pad[0xD] = 0;
    for (i = 0; i < a->pad[8]; i++) {
        q = func_8007AAE8();
        a->parts[i] = q;
        *(s16 *)(q + 6) = D_8011A68C[i].v[0];
        *(s16 *)(a->parts[i] + 0) = D_8011A68C[i].v[1];
        *(s16 *)(a->parts[i] + 2) = D_8011A68C[i].v[2];
        *(s16 *)(a->parts[i] + 4) = D_8011A68C[i].v[3];
        *(s16 *)(a->parts[i] + 8) = 0;
        *(s16 *)(a->parts[i] + 0xA) = 0;
        *(s16 *)(a->parts[i] + 0xC) = 0;
        func_80051B04(a->parts[i], 0xC, D_8011A68C[i].v[4]);
    }
    *(s16 *)(a->parts[0] + 0xA) = 0x400;
    a->pad[0x5E] = 0;
    func_800517F8(a);
    D_1F800248 = (u8 *)a;
}

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_80110A44);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_80110BA0);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_80111094);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_80111298);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_801115A4);

extern void *D_800ECF80;
extern u8 D_8011A6D4[];
/* func_80111BF4, inlined */
static inline void inl_80111BF4(void *a)
{
    func_80051B70(a, 0xC, 0x5);
    func_800517F8(a);
}
/* func_80111DB0, inlined */
static inline void inl_80111DB0(void *a)
{
    func_80051B70(a, 0xC, 0x6);
    func_800517F8(a);
}
/* func_80111DF0, inlined */
static inline void inl_80111DF0(u8 *a)
{
    u8 *s;
    s32 n;

    if (a[5] == 0) {
        a[5] = 1;
        s = D_800BF808;
        if (*(s32 *)(s + 0x54) != 0) {
            n = *(s32 *)(s + 0x50) * 100 + *(s32 *)(s + 0x54);
        } else {
            n = *(s32 *)(s + 0x50);
        }
        *(s16 *)(a + 0xE) = func_80079634(n, a + 0x44);
        *(s16 *)(a + 0x54) = *(s16 *)(a + 0x2E);
        *(s16 *)(a + 0x56) = *(s16 *)(a + 0x32);
        *(s16 *)(a + 0x58) = *(s16 *)(a + 0x36);
    }
    if (D_800BFA58_9b2e != 0) {
        a[4] = 1;
        a[5] = 0;
    } else {
        a[4] = 0;
    }
}
/* func_80111EB0, inlined */
static inline void inl_80111EB0(u8 *a)
{
    *(void **)(a + 0x3C) = D_800ECF80;
    if (a[0x5E] == 0) {
        func_80077B38(a, D_8011A6D4, 1);
    } else {
        func_80077B38(a, D_8011A6D4, 2);
    }
    a[0xB] = 0x10;
    *(s16 *)(a + 0x2E) = 0x640;
    *(s16 *)(a + 0x32) = -0x35C;
    *(s16 *)(a + 0x5C) = 0;
    *(s16 *)(a + 0x5A) = 0;
    a[0x47] = 0;
    *(s16 *)(a + 0x36) = 0x960;
}
/* func_80111FA4, inlined */
static inline void inl_80111FA4(u8 *a)
{
    s32 k;
    s16 x, z, y, w;

    *(void **)(a + 0x3C) = D_800ECF80;
    k = 4;
    if (D_800BFA58_9b2e == 0) {
        k = 3;
    }
    if (a[0x5E] != 0) {
        k += 2;
    }
    func_80077B38(a, D_8011A6D4, k);
    a[0xB] = 0x10;
    a[0x47] = 0;
    x = D_1F800160;
    z = D_1F800164;
    *(s16 *)(a + 0x5C) = 0;
    *(s16 *)(a + 0x5A) = 0;
    *(s16 *)(a + 0x2E) = x;
    *(s16 *)(a + 0x60) = x;
    *(s16 *)(a + 0x36) = z;
    *(s16 *)(a + 0x64) = z;
    if (a[0x5E] != 0) {
        y = D_1F800162 - 0x96;
        *(s16 *)(a + 0x66) = 0;
        *(s16 *)(a + 0x68) = 0x40;
        do {
            *(s16 *)(a + 0x32) = y;
        } while (0);
        *(s16 *)(a + 0x62) = y;
    } else {
        *(s16 *)(a + 0x66) = 0x578;
        w = D_1F800162;
        *(s16 *)(a + 0x68) = 0x80;
        *(s16 *)(a + 0x32) = w;
        *(s16 *)(a + 0x62) = w;
    }
}
/* func_80112130, inlined */
static inline void inl_80112130(u8 *a)
{
    *(void **)(a + 0x3C) = D_800ECF80;
    func_80077B38(a, D_8011A6D4, 0x7);
    *(s16 *)(a + 0x5C) = 0;
    a[0xB] = 0x10;
    *(s16 *)(a + 0x5A) = 0;
    a[0x47] = 0;
}
/* func_80111C28, inlined */
static inline void inl_80111C28(void *arg0) {
    M2C_FIELD(arg0, s8 *, 1) = 1;
}
/* func_80111C34, inlined */
static inline void inl_80111C34(u8 *a)
{
    switch (a[5]) {
    case 0:
        if (D_800BFA58_9b2e >= 2) {
            a[5]++;
        }
        break;
    case 1:
        *(s16 *)(*(u8 **)(a + 0xC4) + 8) -= 0x80;
        if (*(s16 *)(*(u8 **)(a + 0xC4) + 8) < -0x6FF) {
            a[5]++;
            D_800BFA58_9b2e = 3;
        }
        break;
    }
    a[1] = 1;
    func_80077E7C(a);
    func_800517F8(a);
}
/* func_80111DE4, inlined */
static inline void inl_80111DE4(void *arg0) {
    M2C_FIELD(arg0, s8 *, 1) = 1;
}
/* func_8011208C, inlined */
static inline void inl_8011208C(u8 *a)
{
    s32 v;

    *(s16 *)(a + 0x2E) = *(s16 *)(a + 0x60);
    a[1] = 1;
    v = abs((func_80083E80(*(s16 *)(a + 0x66)) << 4) >> 12);
    *(s16 *)(a + 0x32) = *(s16 *)(a + 0x62) - v;
    *(s16 *)(a + 0x36) = *(s16 *)(a + 0x64) + ((func_80083F50(*(s16 *)(a + 0x66)) * *(s16 *)(a + 0x68)) >> 12);
    *(s16 *)(a + 0x62) += 4 + (func_8009A450() & 3);
    *(s16 *)(a + 0x66) += 0x30;
}
void func_80111744(u8 *a)
{
    switch (a[4]) {
    case 0:
        a[4] = 1;
        switch (a[3]) {
        case 0:
            inl_80111BF4(a);
            break;
        case 1:
            func_801107DC(a);
            break;
        case 2:
            func_80110918(a);
            break;
        case 3:
            inl_80111DB0(a);
            break;
        case 4:
            inl_80111DF0(a);
            break;
        case 5:
            inl_80111EB0(a);
            break;
        case 6:
            inl_80111FA4(a);
            break;
        case 7:
            inl_80112130(a);
            break;
        }
        break;
    case 1:
        switch (a[3]) {
        case 0:
            inl_80111C28(a);
            break;
        case 1:
            inl_80111C34(a);
            break;
        case 2:
            func_80111094(a);
            break;
        case 3:
            inl_80111DE4(a);
            break;
        case 4:
            func_80111298(a);
            break;
        case 5:
            func_801115A4(a);
            break;
        case 6:
            inl_8011208C(a);
            break;
        case 7:
            a[1] = 1;
            break;
        }
        break;
    case 2:
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

void func_80111BF4(void *a)
{
    func_80051B70(a, 0xC, 0x5);
    func_800517F8(a);
}

void func_80111C28(void *arg0) {
    M2C_FIELD(arg0, s8 *, 1) = 1;
}

void func_80111C34(u8 *a)
{
    switch (a[5]) {
    case 0:
        if (D_800BFA58_9b2e >= 2) {
            a[5]++;
        }
        break;
    case 1:
        *(s16 *)(*(u8 **)(a + 0xC4) + 8) -= 0x80;
        if (*(s16 *)(*(u8 **)(a + 0xC4) + 8) < -0x6FF) {
            a[5]++;
            D_800BFA58_9b2e = 3;
        }
        break;
    }
    a[1] = 1;
    func_80077E7C(a);
    func_800517F8(a);
}

void func_80111CFC(u8 *a)
{
    u8 *o;

    D_1F8000C0.vx = *(s16 *)(a + 0x4E);
    D_1F8000C0.vy = *(s16 *)(a + 0x50);
    D_1F8000C0.vz = *(s16 *)(a + 0x52);
    func_80084470(D_1F800248 + 0x98, &D_1F8000C0, &D_1F8000A0);
    o = D_1F800248;
    *(s16 *)(a + 0x2E) = *(s16 *)(o + 0x2E) + D_1F8000A0.vx;
    *(s16 *)(a + 0x32) = *(s16 *)(o + 0x32) + D_1F8000A0.vy;
    *(s16 *)(a + 0x36) = *(s16 *)(o + 0x36) + D_1F8000A0.vz;
}

void func_80111DB0(void *a)
{
    func_80051B70(a, 0xC, 0x6);
    func_800517F8(a);
}

void func_80111DE4(void *arg0) {
    M2C_FIELD(arg0, s8 *, 1) = 1;
}

void func_80111DF0(u8 *a)
{
    u8 *s;
    s32 n;

    if (a[5] == 0) {
        a[5] = 1;
        s = D_800BF808;
        if (*(s32 *)(s + 0x54) != 0) {
            n = *(s32 *)(s + 0x50) * 100 + *(s32 *)(s + 0x54);
        } else {
            n = *(s32 *)(s + 0x50);
        }
        *(s16 *)(a + 0xE) = func_80079634(n, a + 0x44);
        *(s16 *)(a + 0x54) = *(s16 *)(a + 0x2E);
        *(s16 *)(a + 0x56) = *(s16 *)(a + 0x32);
        *(s16 *)(a + 0x58) = *(s16 *)(a + 0x36);
    }
    if (D_800BFA58_9b2e != 0) {
        a[4] = 1;
        a[5] = 0;
    } else {
        a[4] = 0;
    }
}

void func_80111EB0(u8 *a)
{
    *(void **)(a + 0x3C) = D_800ECF80;
    if (a[0x5E] == 0) {
        func_80077B38(a, D_8011A6D4, 1);
    } else {
        func_80077B38(a, D_8011A6D4, 2);
    }
    a[0xB] = 0x10;
    *(s16 *)(a + 0x2E) = 0x640;
    *(s16 *)(a + 0x32) = -0x35C;
    *(s16 *)(a + 0x5C) = 0;
    *(s16 *)(a + 0x5A) = 0;
    a[0x47] = 0;
    *(s16 *)(a + 0x36) = 0x960;
}

u8 *func_80111F3C(void *a, u8 b)
{
    u8 *r = func_80072DDC(0, 0, 3, 0x10);

    if (r != NULL) {
        *(void **)(r + 0x1C) = func_80111744;
        r[3] = 6;
        r[0x5E] = b;
        *(void **)(r + 0x10) = a;
    }
    return r;
}

void func_80111FA4(u8 *a)
{
    s32 k;
    s16 x, z, y, w;

    *(void **)(a + 0x3C) = D_800ECF80;
    k = 4;
    if (D_800BFA58_9b2e == 0) {
        k = 3;
    }
    if (a[0x5E] != 0) {
        k += 2;
    }
    func_80077B38(a, D_8011A6D4, k);
    a[0xB] = 0x10;
    a[0x47] = 0;
    x = D_1F800160;
    z = D_1F800164;
    *(s16 *)(a + 0x5C) = 0;
    *(s16 *)(a + 0x5A) = 0;
    *(s16 *)(a + 0x2E) = x;
    *(s16 *)(a + 0x60) = x;
    *(s16 *)(a + 0x36) = z;
    *(s16 *)(a + 0x64) = z;
    if (a[0x5E] != 0) {
        y = D_1F800162_a8d4 - 0x96;
        *(s16 *)(a + 0x66) = 0;
        *(s16 *)(a + 0x68) = 0x40;
        do {
            *(s16 *)(a + 0x32) = y;
        } while (0);
        *(s16 *)(a + 0x62) = y;
    } else {
        *(s16 *)(a + 0x66) = 0x578;
        w = D_1F800162_a8d4;
        *(s16 *)(a + 0x68) = 0x80;
        *(s16 *)(a + 0x32) = w;
        *(s16 *)(a + 0x62) = w;
    }
}

void func_8011208C(u8 *a)
{
    s32 v;

    *(s16 *)(a + 0x2E) = *(s16 *)(a + 0x60);
    a[1] = 1;
    v = abs((func_80083E80(*(s16 *)(a + 0x66)) << 4) >> 12);
    *(s16 *)(a + 0x32) = *(s16 *)(a + 0x62) - v;
    *(s16 *)(a + 0x36) = *(s16 *)(a + 0x64) + ((func_80083F50(*(s16 *)(a + 0x66)) * *(s16 *)(a + 0x68)) >> 12);
    *(s16 *)(a + 0x62) += 4 + (func_8009A450() & 3);
    *(s16 *)(a + 0x66) += 0x30;
}

void func_80112130(u8 *a)
{
    *(void **)(a + 0x3C) = D_800ECF80;
    func_80077B38(a, D_8011A6D4, 0x7);
    *(s16 *)(a + 0x5C) = 0;
    a[0xB] = 0x10;
    *(s16 *)(a + 0x5A) = 0;
    a[0x47] = 0;
}

void func_80112180(void *arg0) {
    M2C_FIELD(arg0, s8 *, 1) = 1;
}

s32 f_AdvanceEndingScriptedPresentation(u8 *a)
{
    u8 *o;

    switch (a[0x78]) {
    case 0:
        if (*(s16 *)(a + 0x74) >= 0) {
            a[0x7A] = a[0x74];
        }
        a[0x78]++;
    case 1:
        if ((*(u8 **)(a + 0x10) = func_8007DEF8((s16)(*(u16 *)(a + 0x72) | 0x1000), a[0x7A], 3)) != NULL) {
            D_800BF870.pad1[0x1E5]++;
            a[0x78]++;
        }
        break;
    case 2:
        o = *(u8 **)(a + 0x10);
        if (o[4] != 2) {
            return 0;
        }
        o[4] = 3;
        D_800BF870.pad1[0x1E6]++;
        a[0x78]++;
        break;
    case 3:
        *(u8 **)(a + 0x10) = NULL;
        return 1;
    }
    return 0;
}

extern void (*D_8009D1D4[])(void);
extern void (*D_8009D22C[])(void);
extern void (*D_8009D314[])(u8 *);
extern void (*D_8009D52C[])(u8 *);
extern void (*D_800A4AF8[])(void);
extern void (*D_800A4B50[])(void);
extern void (*D_800A4AA0[])(u8 *);
extern u16 D_1F80017C;
#define S16(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define U16(p, o) (*(u16 *)((u8 *)(p) + (o)))
s32 func_801122B4(u8 *a)
{
    u8 *g = D_800E7E80_f78d;
    u8 *o;
    u16 k;
    s16 n;
    s16 h;
    u8 snd;
    s32 vol;

    o = *(u8 **)(a + 0x6C);
    k = U16(o, 0xA);
    switch (a[0x78]) {
    case 0:
        g[5] = 0x21;
        g[6] = 0;
        n = S16(a, 0x64) >> 8;
        if (n == 0) {
            n = 10;
        }
        S16(a, 0x48) = U16(a, 0x74) - U16(g, 0x2E);
        S16(a, 0x4C) = U16(a, 0x76) - U16(g, 0x36);
        S16(a, 0x64) = (s16)func_80084080(S16(a, 0x4C) * S16(a, 0x4C) + S16(a, 0x48) * S16(a, 0x48)) / n;
        if (S16(a, 0x64) == 0) {
            S16(a, 0x64) = 1;
        }
        S16(a, 0x64) = 0x1000 / S16(a, 0x64);
        S16(a, 0x44) = 0x1000;
        n = k;
        if (n == -1) {
            S16(g, 0x56) = func_80085690(-S16(a, 0x4C), S16(a, 0x48)) & 0xFFF;
        } else if (n == 0) {
            a[0x78] = 2;
            return 0;
        }
        S16(a, 0x66) = func_80085690(-S16(a, 0x4C), S16(a, 0x48)) & 0xFFF;
        a[0x78]++;
    case 1:
        if (func_80041438(g, S16(a, 0x66), 0x100) != 0) {
            a[0x78]++;
        }
        if ((s16)k == 1) {
            return 0;
        }
    case 2:
        func_80054D14(g, U16(a, 0x72) & 0xFFF, 4);
        S16(a, 0x44) -= U16(a, 0x64);
        if (S16(a, 0x44) <= 0) {
            S16(a, 0x44) = 0;
        }
        S16(g, 0x2E) = U16(o, 4) - S16(a, 0x44) * S16(a, 0x48) / 0x1000;
        S16(g, 0x36) = U16(o, 6) - S16(a, 0x44) * S16(a, 0x4C) / 0x1000;
        if (S16(a, 0x44) == 0) {
            if (!(S16(a, 0x72) & 0x8000)) {
                func_80054DAC(g, 2, 4);
            }
            return 1;
        }
        h = S16(a, 0x68);
        if (h != 0) {
            snd = S16(a, 0x6A);
            vol = (S16(a, 0x6A) & 0xFF00) >> 8;
            if (h & 0x3F) {
                if (!(D_1F80017C & h)) {
                    func_80074590(snd, 0, (s8)vol);
                }
            } else if (h & 0x80) {
                if ((*(u8 **)(g + 0x38))[4] != 0) {
                    if (!(h & 0x40)) {
                        S16(a, 0x68) = h | 0x40;
                        func_80074590(snd, 0, (s8)vol);
                    }
                } else {
                    S16(a, 0x68) = h & 0xFFBF;
                }
            }
        }
        break;
    }
    return 0;
}

typedef struct {
    s16 x, y, w, h;
} Rect16;
typedef struct {
    u32 *vlcbuf[2];
    s32 vlcid;
    u16 *imgbuf[2];
    s32 imgid;
    Rect16 rect[2];
    s32 rectid;
    Rect16 slice;
    s32 isdone;
} DecEnv;
typedef struct {
    u32 unk0;
    u8 *buf;
    u32 unk8;
} MovieDef;
extern MovieDef D_8011A6AC[];
extern DecEnv D_1F800000;
extern u8 *D_1F800138;
extern u8 D_1F800135;
extern u8 D_1F80019C;
extern u8 D_1F80019D;
extern s32 D_1F800034;
extern s16 D_800E809C;
extern char D_80109180[];
extern char D_80109198[];
extern char D_801091C4[];
void func_801129D4(void);
s32 func_80112660(s32 idx)
{
    u8 buf[0x18];
    u8 c;
    s32 n;
    u8 *p;
    u16 t;
    u8 *p_f;

    if (D_1F80019D != 0) {
        *(s16 *)(D_1F800138 + 0x4E) = 7;
    }
    switch (*(u16 *)(D_1F800138 + 0x4E)) {
    case 0:
        p = D_1F800138;
        p[0x69] = idx;
        c = 0x80;
        (MEMBER_AT(s16, p, 0x4E))++;
        do {
        } while (func_80089BAC(0xE, &c, 0) == 0);
        break;
    case 1:
    case 2:
    case 3:
        (*(s16 *)(D_1F800138 + 0x4E))++;
        break;
    case 4:
        func_8008B8F0(buf, D_8011A6AC[idx].unk0);
        p_f = D_1F800138;
        t = *(u16 *)(p_f + 0x4E);
        D_1F80019C = 1;
        *(s16 *)(p_f + 0x4E) = t + 1;
        func_80075A30();
        break;
    case 5:
        func_80112AE0(&D_1F800000, 0, 0, 0, 0x100);
        func_80112BA0((s32)buf, (s32)func_801129D4);
        if (func_80112C40(&D_1F800000, (s16)D_8011A6AC[idx].unk8) == -1) {
            func_8009A730(D_80109180);
            *(s16 *)(D_1F800138 + 0x4E) = 7;
            return 0;
        }
        (*(s16 *)(D_1F800138 + 0x4E))++;
    case 6:
        func_8009C784(D_1F800000.vlcbuf[D_1F800000.vlcid], 0);
        func_8009C800(D_1F800000.imgbuf[D_1F800000.imgid], D_1F800000.slice.w * D_1F800000.slice.h / 2);
        if (func_80112C40(&D_1F800000, (s16)D_8011A6AC[idx].unk8) == -1) {
            func_8009A730(D_80109198);
            *(s16 *)(D_1F800138 + 0x4E) = 7;
        }
        n = 0x800000;
        while (D_1F800000.isdone == 0) {
            if (--n == 0) {
                func_8009A730(D_801091C4);
                D_1F800000.isdone = 1;
                D_1F800000.rectid = D_1F800135;
                D_1F800000.slice.x = D_1F800000.rect[D_1F800000.rectid].x;
                D_1F800000.slice.y = D_1F800000.rect[D_1F800000.rectid].y;
            }
        }        D_1F800034 = 0;
        D_1F80019C = 2;
        *(volatile s16 *)&D_800E809C = 1;
        break;
    case 7:
        func_8001CF00(0);
        func_8009C820(0);
        func_8009C8BC(0);
        func_8008CD40();
        func_8008CCE0();
        do {
        } while (func_80089E1C(9, 0, 0) == 0);
        D_1F80019C = 0;
        D_1F80019D = 0;
        return 1;
    }
    return 0;
}

void func_801129D4(void)
{
    Rect16 r;
    s32 id;
    r = D_1F800000.slice;
    id = D_1F800000.imgid;
    D_1F800000.imgid = 1 - id;
    D_1F800000.slice.x += 16;
    if (D_1F800000.slice.x < D_1F800000.rect[D_1F800000.rectid].x + D_1F800000.rect[D_1F800000.rectid].w) {
        func_8009C800(D_1F800000.imgbuf[D_1F800000.imgid], D_1F800000.slice.w * D_1F800000.slice.h / 2);
    } else {
        D_1F800000.isdone = 1;
        D_1F800000.rectid = D_1F800135;
        D_1F800000.slice.x = D_1F800000.rect[D_1F800000.rectid].x;
        D_1F800000.slice.y = D_1F800000.rect[D_1F800000.rectid].y;
    }
    func_80081218(&r, D_1F800000.imgbuf[id]);
}

typedef struct {
    u16 id;
    u16 type;
    u16 secCount;
    u16 nSectors;
    u32 frameCount;
    u32 bsHeadSize;
    u16 width;
    u16 height;
} StHeader;
void func_80112AE0(DecEnv *d, s16 x0, s16 y0, s16 x1, s16 y1)
{
    u8 *b;
    s32 i;
    b = D_8011A6AC[D_1F800138[0x69]].buf;
    d->vlcid = 0;
    d->imgid = 0;
    d->rect[0].x = x0;
    d->rect[0].y = y0;
    d->rect[1].x = x1;
    d->rect[1].y = y1;
    d->isdone = 0;
    i = 1 - D_1F800135;
    d->vlcbuf[0] = (u32 *)b;
    d->rectid = i;
    d->vlcbuf[1] = (u32 *)(b + 0x12000);
    d->imgbuf[0] = (u16 *)(b + 0x24000);
    d->imgbuf[1] = (u16 *)(b + 0x26000);
    d->slice.x = d->rect[i].x;
    d->slice.y = d->rect[i].y;
    d->slice.w = 0x10;
    d->slice.h = 0xF0;
}

extern u32 D_1F800250;
void func_80112BA0(s32 a, s32 b)
{
    u8 *buf = D_8011A6AC[D_1F800138[0x69]].buf;

    func_8009C620(0);
    func_8009C8BC(b);
    func_80089870(buf + 0x28000, 0x20);
    func_8008CEB0(0, 1, -1, 0, 0);
    func_80112D98(a);
}

typedef struct {
    u32 *vlcbuf[2];
    s32 vlcid;
} VlcEnv;
s32 func_80112C40(VlcEnv *dec, s32 b)
{
    s32 cnt = 2000;
    u32 *next;

    while ((next = (u32 *)func_80112CDC(dec, b)) == NULL) {
        if (--cnt == 0) {
            return -1;
        }
    }
    dec->vlcid = 1 - dec->vlcid;
    func_8009CCE0(next, dec->vlcbuf[dec->vlcid]);
    func_8008CF40(next);
    return 0;
}

u32 *func_80112CDC(DecEnv *dec, u32 limit)
{
    u32 *addr;
    StHeader *sector;
    s32 cnt = 2000;
    u32 n;

    while (func_8008D030(&addr, &sector)) {
        if (--cnt == 0) {
            return 0;
        }
    }
    if (sector->frameCount >= limit) {
        *(s16 *)(D_1F800138 + 0x4E) = 7;
    }
    n = sector->frameCount;
    dec->rect[0].w = dec->rect[1].w = sector->width;
    dec->rect[0].h = dec->rect[1].h = sector->height;
    D_1F800250 = n;
    dec->slice.h = sector->height;
    return addr;
}

void func_80112D98(s32 a)
{
    s32 n = 0x1C0;

    do {
        while (func_80089BAC(2, a, 0) == 0) {
        }
    } while (func_8008CC30(n) == 0);
}

// ASM by design: hand-written GTE routine (no stack frame, trapping add / addi / sub, `or rd, $zero, rs` moves: never emitted by gcc 2.8.1).
INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_80112DEC);

// ASM by design: hand-written GTE routine (no stack frame, trapping add / addi / sub, `or rd, $zero, rs` moves: never emitted by gcc 2.8.1).
INCLUDE_ASM("asm/a0l/nonmatchings/a0l", f_DispatchEndingAreaCameraSequence);

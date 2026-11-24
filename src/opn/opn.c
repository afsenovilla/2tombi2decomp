#include "common.h"
#include "game.h"
#include "m2c.h"

typedef struct { u16 lo; s16 hi; } OpnFix;
typedef struct { OpnFix at[3]; } OpnCam;
extern OpnCam D_1F8000D0;
#define H(p, o) (*(s16 *)((u8 *)(p) + (o)))

void func_8018A13C(u8 *a, u8 *b)
{
    if (++H(a, 0x42) >= 0x17) {
        H(a, 0x42) = 0x16;
    }
    g_CameraState.focusX = H(b, 0x60) + (0x8DA - H(b, 0x60)) * H(a, 0x42) / 22;
    g_CameraState.focusY = H(b, 0x62) + (-0x320 - H(b, 0x62)) * H(a, 0x42) / 22;
    g_CameraState.focusZ = H(b, 0x64) + (0x128C - H(b, 0x64)) * H(a, 0x42) / 22;
    D_1F8000D0.at[0].hi = H(b, 0x66) + (0xBEC - H(b, 0x66)) * H(a, 0x42) / 22;
    D_1F8000D0.at[1].hi = H(b, 0x68) + (-0x3E8 - H(b, 0x68)) * H(a, 0x42) / 22;
    D_1F8000D0.at[2].hi = H(b, 0x6A) + (0xC73 - H(b, 0x6A)) * H(a, 0x42) / 22;
}

#define U(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define W(p, o) (*(s32 *)((u8 *)(p) + (o)))
typedef struct { u8 pad0[0x3A]; s16 fx; u8 pad3C[2]; s16 fy; u8 pad40[2]; s16 fz; } OpnCamState;
extern OpnCamState D_800E8008;
extern u8 D_80100690[];
extern u8 D_800BF9ED;
extern u8 D_800E806C;

void func_8018A300(u8 *a, s32 arg1)
{
    u8 *buf = D_80100690;
    s32 hit;

    switch (a[6]) {
    case 0:
        H(a, 0x42) = 0;
        H(a, 0x4A) = -0x3800;
        H(a, 0x48) = 0x20;
        H(a, 0x40) = 0x25;
        a[6]++;
        H(a, 0x4E) = (H(a, 0x7A) - H(a, 0x2E)) / 37;
        H(a, 0x50) = (H(a, 0x7C) - H(a, 0x32)) / 37;
        H(a, 0x52) = (H(a, 0x7E) - H(a, 0x36)) / 37;
        H(buf, 0x60) = D_800E8008.fx;
        H(buf, 0x62) = D_800E8008.fy;
        H(buf, 0x64) = D_800E8008.fz;
        H(buf, 0x66) = D_1F8000D0.at[0].hi;
        H(buf, 0x68) = D_1F8000D0.at[1].hi;
        H(buf, 0x6A) = D_1F8000D0.at[2].hi;
        func_80074590(7, 0, 0);
        break;
    case 1:
        if (H(a, 0x40) >= 0xF) {
            H(a, 0x58) += H(a, 0x48);
        }
        if (H(a, 0x40) != 0) {
            H(a, 0x40)--;
            H(a, 0x2E) += H(a, 0x4E);
            H(a, 0x36) += H(a, 0x52);
            H(a, 0x32) += H(a, 0x50);
            if (H(a, 0x40) == 0) {
                func_80054D14(a, 0x14, 4);
            }
        }
        if (H(a, 0x4A) > 0) {
            func_80054D14(a, 0x26, 2);
            H(a, 0x48) += 0x20;
            if (H(a, 0x48) > 0x200) {
                H(a, 0x48) = 0x200;
            }
            H(a, 0x58) += H(a, 0x48);
            if (H(a, 0x58) >= 0x1FC0) {
                H(a, 0x58) = 0x2000;
                func_80054D14(a, 0x1E, 4);
            }
        }
        H(a, 0x4A) += 0x220;
        if (H(a, 0x4A) > 0x2000) {
            H(a, 0x4A) = 0x2000;
        }
        W(a, 0x30) += H(a, 0x4A) << 8;
        if (H(a, 0x40) < 0x16) {
            func_8018A13C(a, buf);
        }
        hit = 0;
        if ((u16)(U(a, 0x2E) - U(a, 0x7A) + 0x64) < 0xC9 && (u16)(U(a, 0x32) - U(a, 0x7C) + 0x64) < 0xC9) {
            func_80054D14(a, 0x1E, 4);
            func_800312D4(7, a + 0x2C, -0x14);
            hit = 1;
            H(a, 0x2E) = H(a, 0x7A);
            H(a, 0x36) = H(a, 0x7E);
            H(a, 0x32) = H(a, 0x7C) - 0x50;
        }
        if (hit != 0) {
            D_800BF9ED = 0x14;
            H(a, 0x58) = 0;
            H(a, 0x40) = 4;
            a[6]++;
            D_800E8008.fx = 0x8DA;
            D_800E8008.fy = -0x320;
            D_800E8008.fz = 0x128C;
            D_1F8000D0.at[0].hi = 0xBEC;
            D_1F8000D0.at[1].hi = -0x3E8;
            D_1F8000D0.at[2].hi = 0xC73;
        }
        break;
    case 3:
        func_8003315C(a);
        D_800E806C = 7;
        D_800BF9ED = 0x1E;
        H(a, 0x4A) = -0x3000;
        a[6]++;
        func_80054D14(a, 0x5A, 2);
    case 4:
        H(a, 0x4A) += 0x180;
        if (H(a, 0x4A) > 0x3000) {
            H(a, 0x4A) = 0x3000;
        }
        H(a, 0x2E) += 0xA;
        W(a, 0x30) += H(a, 0x4A) << 8;
        if (H(a, 0x4A) > 0 && H(a, 0x32) >= -0x36F) {
            func_80074590(3, 0, 0);
            H(a, 0x32) = -0x370;
            H(a, 0x4A) = -0x2000;
            a[6]++;
        }
        H(a, 0x58) = (H(a, 0x58) + 0x200) & 0xFFF;
        func_8006CBA8(a + 0x2C);
        break;
    case 5:
        a[6]++;
    case 6:
        H(a, 0x58) = (H(a, 0x58) + 0x100) & 0xFFF;
        H(a, 0x4A) += 0x180;
        if (H(a, 0x4A) > 0x3000) {
            H(a, 0x4A) = 0x3000;
        }
        H(a, 0x2E) += 0xA;
        W(a, 0x30) += H(a, 0x4A) << 8;
        if (H(a, 0x4A) > 0) {
            func_80055D5C(a);
            func_8005444C(a);
            if (a[0x29] != 0) {
                func_80074590(3, 0, 0);
                H(a, 0x58) = 0;
                H(a, 0x4A) = -0x1800;
                a[6]++;
                func_80054D14(a, 0x19, 0);
            }
        }
        func_8006CBA8(a + 0x2C);
        break;
    case 7:
        H(a, 0x4A) += 0x300;
        if (H(a, 0x4A) > 0x3000) {
            H(a, 0x4A) = 0x3000;
        }
        H(a, 0x2E) += 8;
        W(a, 0x30) += H(a, 0x4A) << 8;
        func_80055D5C(a);
        func_8005444C(a);
        if (a[0x29] != 0) {
            func_80074590(3, 0, 0);
            H(a, 0x58) = 0;
            a[6]++;
            func_80054D14(a, 0x17, 2);
            D_800E806C = 8;
        }
        func_8006CBA8(a + 0x2C);
        break;
    case 8:
        if (arg1 == 1) {
            func_80054D14(a, 0xC8, 2);
            H(a, 0x40) = 0x14;
            a[6]++;
        }
        D_1F8000D0.at[0].hi += 8;
        if (D_1F8000D0.at[0].hi > 0xD48) {
            D_1F8000D0.at[0].hi = 0xD48;
        }
        break;
    case 9:
        if (--H(a, 0x40) == 0) {
            a[6]++;
            D_800E8008.fx = 0xAA0;
            D_800E8008.fy = -0x384;
            D_800E8008.fz = 0xF80;
        }
        D_1F8000D0.at[0].hi += 8;
        if (D_1F8000D0.at[0].hi > 0xD48) {
            D_1F8000D0.at[0].hi = 0xD48;
        }
        break;
    case 10:
        D_1F8000D0.at[0].hi += 8;
        if (D_1F8000D0.at[0].hi > 0xD48) {
            D_1F8000D0.at[0].hi = 0xD48;
            func_80054D14(a, 2, 0);
            D_800BF9ED = 0x28;
            H(a, 0x40) = 0xA;
            a[6]++;
        }
        break;
    case 11:
        a[6]++;
    case 12:
        if (D_800BF9ED == 0x32) {
            func_8006CBA8(a + 0x2C);
            H(a, 0x40) = 0x14;
            a[6]++;
        }
        break;
    case 2:
    case 13:
        if (--H(a, 0x40) == 0) {
            a[6]++;
        }
        break;
    case 14:
        func_80070724(0xA, 1, 0);
        a[6] = 0;
        a[5]++;
        break;
    }
}

s32 func_8018AAA4(u8 *a, s32 target, s32 cur)
{
    s32 d, r;
    s16 e;
    d = (target - cur) & 0xFFF;
    e = d;
    if (d == 0) {
        return cur & 0xFFF;
    }
    if ((u32)e < 0x800) {
        if (d >= 0x100) {
            r = cur + 0x40;
        } else if (d >= 0x30) {
            r = cur + 0x10;
        } else if (d >= 0x20) {
            r = cur + 8;
        } else {
            r = cur + 1;
            if (d >= 0x10) {
                r = cur + 4;
            }
        }
        if (e >= 0x100) {
            *(u16 *)(a + 0x74) = 2;
        } else {
            *(u16 *)(a + 0x74) |= 1;
        }
    } else {
        r = cur - 0x40;
        if (d > 0xF00) {
            r = cur - 0x10;
            if (d > 0xFD0) {
                r = cur - 8;
                if (d > 0xFE0) {
                    r = cur - 4;
                    if (d > 0xFF0) {
                        r = cur - 1;
                    }
                }
            }
        }
        if (e <= 0xF00) {
            *(u16 *)(a + 0x74) = 2;
        } else {
            *(u16 *)(a + 0x74) |= 1;
        }
    }
    return r & 0xFFF;
}

typedef struct { s16 x, y, z, w; } OpnPoint;
extern OpnPoint D_8018D390[];
s32 func_8018AB78(u8 *a, u8 *b)
{
    OpnPoint *p;
    OpnCam *c;
    s16 dx, dy, dz;
    s32 sq, d;
    p = &D_8018D390[*(s16 *)(b + 0x72)];
    c = &D_1F8000D0;
    dz = p->z - c->at[2].hi;
    dx = p->x - c->at[0].hi;
    *(s16 *)(b + 0x66) = func_80085690(dz, dx) - 0x400;
    sq = dx * dx + dz * dz;
    d = func_80084080(sq);
    dy = p->y - c->at[1].hi;
    *(s16 *)(b + 0x68) = func_80085690(dy, d);
    *(s16 *)(b + 0x7A) = p->w;
    d = func_80084080(sq + dy + dy);
    *(s32 *)(a + 0x5C) = d;
    return d < 0x50;
}

/* turn the 16.16 angle at a + off towards tgt */
static inline void opn_steer(u8 *a, s32 off, s32 tgt, s32 sd, s32 su)
{
    u8 *p = a + off;
    s32 d = (tgt - U(p, 2)) & 0xFFF;
    s16 e = d;

    if (e != 0) {
        if (e > 0x800) {
            if (e > 0xFF0) {
                U(p, 2) = U(p, 2) - 1;
            } else {
                W(a, off) -= ((0x1000 - d) << 16) >> sd;
            }
        } else if (e < 0x10) {
            U(p, 2) = U(p, 2) + 1;
        } else {
            W(a, off) += e << su;
        }
    }
}
/* the same, 1 once the angle is (nearly) there */
static inline s32 opn_steer_done(u8 *a, s32 off, s32 tgt)
{
    u8 *p = a + off;
    s32 d = (tgt - U(p, 2)) & 0xFFF;
    s16 e = d;

    if (e == 0) {
        return 1;
    }
    if (e > 0x800) {
        if (e > 0xFF0) {
            U(p, 2) = U(p, 2) - 1;
            return 1;
        }
        W(a, off) -= ((0x1000 - d) << 16) >> 4;
    } else {
        if (e < 0x10) {
            U(p, 2) = U(p, 2) + 1;
            return 1;
        }
        W(a, off) += e << 12;
    }
    return 0;
}

void func_8018AC84(u8 *a, u8 *b)
{
    s32 r0;

    switch (a[3]) {
    case 0:
        if (--H(a, 0x68) == 0) {
            a[3]++;
        }
        opn_steer(a, 0x48, U(b, 0x6A), 5, 11);
        opn_steer(a, 0x44, U(b, 0x6C), 7, 11);
        break;
    case 1:
        H(b, 0x74) = 1;
        H(b, 0x6A) = func_8018AAA4(b, H(b, 0x66), H(b, 0x6A));
        H(b, 0x6C) = func_8018AAA4(b, H(b, 0x68), H(b, 0x6C));
        if (func_8018AB78(a, b) != 0) {
            H(b, 0x72)++;
            if (H(b, 0x7A) != 0) {
                a[3]++;
                H(b, 0x74) = 0;
                func_8018AB78(a, b);
            } else {
                func_8018AB78(a, b);
            }
        }
        opn_steer(a, 0x48, U(b, 0x6A), 5, 11);
        opn_steer(a, 0x44, U(b, 0x6C), 7, 11);
        break;
    case 2:
        if (H(b, 0x60) < 0x800) {
            r0 = opn_steer_done(a, 0x48, U(b, 0x66));
            r0 += opn_steer_done(a, 0x44, U(b, 0x68));
            if (r0 == 2) {
                D_800BF9ED = 0x3C;
                a[3]++;
            }
        }
        break;
    case 3:
        if (H(b, 0x78) < 0x1000) {
            H(b, 0x78) += 0x100;
            if (H(b, 0x78) >= 0x1000) {
                H(b, 0x78) = 0x1000;
            }
            H(b, 0x76) = (u32)(func_80083E80(H(b, 0x78)) * 25) >> 10;
        } else {
            H(b, 0x76) = 0;
        }
        if (D_800BF9ED == 0x46) {
            a[3]++;
        }
        opn_steer(a, 0x48, U(b, 0x66), 4, 12);
        opn_steer(a, 0x44, U(b, 0x68), 4, 12);
        break;
    case 4:
        H(a, 0x68) = 1;
        a[3]++;
        H(b, 0x72)++;
        func_8018AB78(a, b);
        break;
    case 5:
        H(b, 0x74) = 1;
        H(b, 0x6A) = func_8018AAA4(b, H(b, 0x66), H(b, 0x6A));
        H(b, 0x6C) = func_8018AAA4(b, H(b, 0x68), H(b, 0x6C));
        if (func_8018AB78(a, b) != 0) {
            H(b, 0x72)++;
            if (H(b, 0x7A) != 0) {
                a[3]++;
                H(b, 0x74) = 5;
                H(a, 0x6A) = 0x3C;
                D_800BF9ED = 0x4B;
                func_8018AB78(a, b);
            } else {
                func_8018AB78(a, b);
            }
        }
        if (H(a, 0x68) == 0) {
            opn_steer(a, 0x48, U(b, 0x66), 5, 11);
            opn_steer(a, 0x44, U(b, 0x68), 7, 11);
            break;
        }
        r0 = opn_steer_done(a, 0x48, U(b, 0x6A));
        r0 += opn_steer_done(a, 0x44, U(b, 0x6C));
        if (r0 == 2) {
            H(a, 0x68) = 0;
        }
        break;
    case 6:
        if (H(a, 0x6A) == 0) {
            r0 = opn_steer_done(a, 0x48, U(b, 0x66));
            r0 += opn_steer_done(a, 0x44, U(b, 0x68));
            if (H(b, 0x76) >= -0x18F) {
                H(b, 0x76) -= 0x20;
            }
            if (r0 == 2) {
                H(a, 0x6A) = 0x3C;
                a[3]++;
                H(b, 0x72)++;
                func_8018AB78(a, b);
            }
        } else {
            H(a, 0x6A)--;
        }
        break;
    case 7:
        if (H(a, 0x6A) == 0) {
            r0 = opn_steer_done(a, 0x48, U(b, 0x66));
            r0 += opn_steer_done(a, 0x44, U(b, 0x68));
            if (r0 == 2) {
                a[3]++;
                H(b, 0x74) = 1;
                H(b, 0x60) = 0x1000;
            }
        } else {
            H(a, 0x6A)--;
            if (H(b, 0x76) >= -0x18F) {
                H(b, 0x76) -= 0x20;
            }
        }
        break;
    case 8:
        H(b, 0x6A) = func_8018AAA4(b, H(b, 0x66), H(b, 0x6A));
        H(b, 0x6C) = func_8018AAA4(b, H(b, 0x68), H(b, 0x6C));
        if (func_8018AB78(a, b) != 0) {
            H(b, 0x72)++;
            if (H(b, 0x7A) != 0) {
                a[3]++;
            } else {
                func_8018AB78(a, b);
            }
        }
        opn_steer(a, 0x48, U(b, 0x6A), 5, 11);
        opn_steer(a, 0x44, U(b, 0x6C), 7, 11);
        break;
    case 9:
        H(b, 0x74) = 0;
        a[3]++;
    case 10:
        if (H(b, 0x76) < 0) {
            H(b, 0x76) += 0x20;
        }
        if (H(b, 0x60) < 0xE00) {
            D_800BF9ED = 0x50;
            a[0x64] = 0xA;
            a[0x67] = 0;
            a[1] = 0;
            a[2] = 0;
            a[3]++;
            *(volatile u8 *)(a + 3) = 0;
        }
        break;
    case 11:
        break;
    }
}

INCLUDE_ASM("asm/opn/nonmatchings/opn", func_8018B924);

extern u16 D_1F80017C;
void func_8018BD30(u8 *a)
{
    u16 t;
    switch (a[5]) {
    case 0:
        if (D_800BF9ED != 0) {
            a[1] = 1;
            a[0x147] = 0;
            *(s16 *)(a + 0x56) = 0;
            *(s16 *)(a + 0x58) = 0;
            a[5]++;
        }
        t = D_1F80017C;
        if ((t & 0x1F) == 0 || ((t & 0xF) == 0 && (func_8009A450() & 1))) {
            func_80074590(2, 0, 0);
        }
        break;
    case 1:
        func_8018A300(a, func_80076D68(a));
        break;
    case 2:
        *(s16 *)(a + 0x50) = 0;
        a[0x145] = 0;
        func_80054198(a);
        a[4] = 6;
        a[5] = 0;
        a[6] = 0;
        a[7] = 0;
        break;
    }
}

extern u8 D_800BF80E;
extern s32 D_1F800184;
extern u8 D_800BF89C;
extern u8 D_800E7E80[];
void func_8018BE40(u8 *a)
{
    u8 *t;

    switch (a[6]) {
    case 0:
        D_800BF80E = 0;
        a[6]++;
    case 1:
        if (func_80076D68(a) == 1) {
            D_800BF80E = 1;
        }
        if (D_1F800184 == 1) {
            *(s16 *)(a + 0x50) = 0;
            *(s16 *)(a + 0x4A) = 0;
        } else {
            func_80065478(a, 1);
        }
        break;
    }
    if (D_800BF89C == 3) {
        t = D_800E7E80;
        t[4] = 7;
        t[5] = 0;
        t[6] = 0;
        t[7] = 0;
    }
}

INCLUDE_ASM("asm/opn/nonmatchings/opn", func_8018BF08);

INCLUDE_ASM("asm/opn/nonmatchings/opn", func_8018C574);

extern u8 D_8012DA04[];
u8 *func_8018C7D8(void *a)
{
    u8 *r = func_80072DDC(a, 0, 3, 0x10);

    if (r == NULL) {
        return NULL;
    }
    r[3] = 1;
    *(void **)(r + 0x1C) = D_8012DA04;
    return r;
}

extern s32 D_8014A270;
#define P(p, o) (*(u8 **)((u8 *)(p) + (o)))
void func_8018C820(u8 *a)
{
    switch (a[6]) {
    case 0:
        if (D_800BF9ED < 0x46) {
            break;
        }
        H(P(a, 0xC4), 8) = H(a, 0x64);
        a[6]++;
        break;
    case 1:
        if (D_800BF9ED < 0x4B) {
            break;
        }
        H(a, 0x76) = 1;
        D_8014A270 = func_80074590(0x81, 0, 0x2A);
        H(a, 0x48) = 0x100;
        H(a, 0x4E) = 0x100;
        H(a, 0x40) = 0;
        a[6]++;
        break;
    case 2:
        H(P(a, 0xC4), 8) += H(a, 0x48) >> 8;
        if (H(P(a, 0xC4), 8) >= H(a, 0x66)) {
            H(P(a, 0xC4), 8) = H(a, 0x66);
            if (H(a, 0x40) != 0) {
                H(a, 0x48) = 0;
                H(a, 0x4E) = 0;
                a[6]++;
                break;
            }
            func_80074AF0(D_8014A270);
            D_8014A270 = 0;
            func_80074590(0x82, 0, 0);
            H(a, 0x48) = -0xA00;
            H(a, 0x4E) = 0x200;
            H(a, 0x76) = 2;
            H(a, 0x40) = 1;
        }
        H(a, 0x48) += H(a, 0x4E);
        if (H(a, 0x48) > 0x1600) {
            H(a, 0x48) = 0x1600;
        }
        break;
    case 3:
        if (D_800BF89C == 2) {
            break;
        }
        H(a, 0x76) = 0;
        H(P(a, 0xC4), 8) = 0xF0;
        func_801314B4(a);
        func_8013892C(a);
        a[5] = 0;
        a[6] = 0;
        break;
    }
}

typedef struct {
    u8 pad0[8];
    u8 count;
    u8 pad9[0xB7];
    u8 *parts[4];
} PartOwner;
extern u8 **D_800E7E74;
extern s16 D_800ED098;
extern s16 D_8018D470[];
void func_8018CCFC(PartOwner *a, s16 b);

void func_8018CA1C(u8 *a)
{
    switch (a[6]) {
    case 0:
        H(a, 0x40) = 3;
        H(a, 0x42) = 0;
        a[7] = 0;
        a[6]++;
        break;
    case 1:
        if (--H(a, 0x42) < 0) {
            switch (a[7]) {
            case 0:
                func_8018CCFC((PartOwner *)a, 8);
                a[7]++;
                break;
            case 1:
                func_8018CCFC((PartOwner *)a, 4);
                break;
            }
            D_800ED098++;
            {
                u8 **p = D_800E7E74;
                D_800E7E74 = p - 1;
                p[-1] = ((PartOwner *)a)->parts[a[8] - 1];
            }
            H(a, 0x42) = 5;
            a[9] = a[8] = a[8] - 1;
            if (--H(a, 0x40) == 0) {
                a[6]++;
            }
        }
        break;
    case 2:
        if (--H(a, 0x42) < 0) {
            func_8018CCFC((PartOwner *)a, 4);
            H(((PartOwner *)a)->parts[a[8] - 1], 0) = D_8018D470[0];
            H(((PartOwner *)a)->parts[a[8] - 1], 2) = D_8018D470[1];
            H(((PartOwner *)a)->parts[a[8] - 1], 4) = D_8018D470[2];
            H(((PartOwner *)a)->parts[a[8] - 1], 8) = D_8018D470[3];
            H(((PartOwner *)a)->parts[a[8] - 1], 0xA) = D_8018D470[4];
            H(((PartOwner *)a)->parts[a[8] - 1], 0xC) = D_8018D470[5];
            H(((PartOwner *)a)->parts[a[8] - 1], 0x38) = 0x1000;
            H(((PartOwner *)a)->parts[a[8] - 1], 0x3A) = 0x1000;
            H(((PartOwner *)a)->parts[a[8] - 1], 0x3C) = 0x1000;
            a[5] = 0;
            a[6] = 1;
            func_80051B04(((PartOwner *)a)->parts[a[8] - 1], 0x1C, 0x1C);
        }
        break;
    }
}

typedef struct {
    s16 pad0;
    s16 x;
    s16 pad4;
    s16 y;
    s16 pad8;
    s16 z;
} HiPos;
void func_8018CCFC(PartOwner *a, s16 b)
{
    HiPos p;

    p.x = *(s16 *)(a->parts[a->count - 1] + 0x2C);
    p.y = *(s16 *)(a->parts[a->count - 1] + 0x30);
    p.z = *(s16 *)(a->parts[a->count - 1] + 0x34);
    func_80027144(*(void **)(a->parts[a->count - 1] + 0x40), &p, 0x800, b);
    func_80074590(0xC, 0, 0);
}

void func_8018CDC4(u8 *a)
{
    u8 *o;

    switch (a[6]) {
    case 0:
        o = *(u8 **)(a + 0x10);
        if (*(s16 *)(a + 0x6A) == 0) {
            if (*(s16 *)(o + 0x76) == 1) {
                a[6] = 0;
                a[5]++;
            }
        } else {
            a[5] = 2;
            a[6] = 0;
        }
        break;
    case 1:
        if (D_800BF89C != 2) {
            a[4] = 3;
        }
        break;
    }
}

INCLUDE_ASM("asm/opn/nonmatchings/opn", func_8018CE40);

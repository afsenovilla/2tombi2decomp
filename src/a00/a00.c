#include "common.h"
#include "game.h"
#include "m2c.h"
#include "gte.h"

#define H(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define U(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define W(p, o) (*(s32 *)((u8 *)(p) + (o)))
extern s16 D_1F80019E;
extern u16 D_1F80017C_0fe7;
#define SP19E D_1F80019E

void f_UpdateA00TombaWaterSurfaceMotion(u8 *a, s32 mode) {
    s16 v[6];
    s16 dy;
    s16 t;

    if (a[0x145] & 1) {
        return;
    }
    dy = -0x14;
    if (H(a, 0x17E) < 0) {
        dy = -0xA;
    }
    switch (a[7]) {
    case 0:
        func_80058304(a, 2);
        t = U(a, 0x4A) - 0x3200;
        if (t < 0) {
            H(a, 0x50) = 0x1400;
        } else {
            if (t > 0xC00) {
                t = 0xC00;
            }
            H(a, 0x50) = t / 2 + 0x1400;
        }
        a[7]++;
    case 1:
        W(a, 0x30) += H(a, 0x50) << 8;
        if ((s16)(H(a, 0x50) -= 0x180) <= 0) {
            a[7]++;
        }
        break;
    case 2:
        if (D_800BF870.unk0 == 0) {
            func_800312D4(0x10E, a + 0x2C, -0xA);
        } else if (D_800BF870.unk0 == 6) {
            func_800312D4(0x70E, a + 0x2C, -0xA);
        } else if (D_800BF870.unk0 == 0xE) {
            func_800312D4(0xF0D, a + 0x2C, -0xA);
        }
        a[7]++;
    case 3:
    case 4:
        W(a, 0x30) -= H(a, 0x50) << 8;
        if (a[7] == 3) {
            H(a, 0x50) += 0x180;
        } else {
            H(a, 0x50) += 0x80;
        }
        if (H(a, 0x50) >= 0x1000) {
            H(a, 0x50) = 0x1000;
        }
        if (SP19E + dy >= H(a, 0x32)) {
            H(a, 0x32) = SP19E;
            if (D_800BF870.unk0 == 0) {
                func_8003116C(0x10D, a + 0x2C, -0xA);
            } else if (D_800BF870.unk0 == 6) {
                func_800312D4(0x704, a + 0x2C, -0xA);
            } else if (D_800BF870.unk0 == 0xE) {
                func_800312D4(0xF06, a + 0x2C, -0xA);
            }
            H(a, 0x32) += dy;
            if (a[0x146] == 0 && !(a[0x14A] & 2)) {
                a[7] = 6;
            } else {
                a[7] = 5;
            }
            H(a, 0x50) = 0;
        }
        break;
    case 5:
        W(a, 0x30) += H(a, 0x50) << 8;
        if ((s16)(H(a, 0x50) += 0x80) >= 0x600) {
            H(a, 0x50) = 0;
            a[7]--;
        }
        break;
    case 6:
        if (SP19E + dy < H(a, 0x32)) {
            W(a, 0x30) -= H(a, 0x50) << 8;
            if ((s16)(H(a, 0x50) += 0x100) >= 0x1000) {
                H(a, 0x50) = 0x1000;
            }
            if (SP19E + dy >= H(a, 0x32)) {
                H(a, 0x32) = SP19E;
                if (D_800BF870.unk0 == 0) {
                    func_8003116C(0x10D, a + 0x2C, -0xA);
                } else if (D_800BF870.unk0 == 6) {
                    func_800312D4(0x704, a + 0x2C, -0xA);
                } else if (D_800BF870.unk0 == 0xE) {
                    func_800312D4(0xF06, a + 0x2C, -0xA);
                }
                H(a, 0x50) = 0;
                H(a, 0x32) += dy;
            }
        } else if (a[0x146] != 0 || (a[0x14A] & 2)) {
            a[7] = 5;
        }
        if (mode != 0) {
            mode = 7;
        } else {
            mode = 3;
        }
        if (!(D_1F80017C_0fe7 & mode)) {
            v[1] = U(a, 0x2E) + ((func_80083F50(H(a, 0x56) + 0x800) * 100) >> 12);
            v[3] = SP19E + 0x1E;
            v[5] = U(a, 0x36) - ((func_80083E80(H(a, 0x56) + 0x800) * 100) >> 12);
            func_8003116C(8, v, -0x50);
        }
        break;
    }
    if (SP19E + H(a, 0x62) / 2 < H(a, 0x32)) {
        a[0x148] = 1;
    } else {
        a[0x148] = 0;
    }
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8010A7F8);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8010AC20);

void func_8010AD68(void *arg0, void *arg1) {
    s32 temp_lo;
    s32 temp_s0;
    s32 temp_s0_2;
    s32 temp_s2_2;
    s32 temp_s3;
    void *temp_s2;

    temp_s2 = M2C_FIELD(arg0, void **, 0x10);
    M2C_FIELD(arg0, u16 *, 0x32) = (u16) (M2C_FIELD(temp_s2, u16 *, 0x30) + ((s32) (func_80083F50(M2C_FIELD(temp_s2, s16 *, 0xC)) * M2C_FIELD(arg0, s16 *, 0x156)) >> 0xC));
    M2C_FIELD(arg0, u16 *, 0x32) = (u16) (M2C_FIELD(arg0, u16 *, 0x32) + ((s32) (func_80083F50(M2C_FIELD(arg0, s16 *, 0x58)) * M2C_FIELD(arg0, s16 *, 0x64)) >> 0xC));
    temp_s0 = (s32) (func_80083E80(M2C_FIELD(temp_s2, s16 *, 0xC)) * M2C_FIELD(arg0, s16 *, 0x156)) >> 0xC;
    temp_s3 = (s32) (func_80083E80(M2C_FIELD(arg1, s16 *, 0x56)) * (s16) temp_s0) >> 0xC;
    M2C_FIELD(arg0, u16 *, 0x2E) = (u16) (M2C_FIELD(temp_s2, u16 *, 0x2C) - ((s32) (func_80083F50(M2C_FIELD(arg1, s16 *, 0x56)) * (s16) temp_s0) >> 0xC));
    M2C_FIELD(arg0, u16 *, 0x36) = (u16) (M2C_FIELD(temp_s2, u16 *, 0x34) + temp_s3);
    temp_s0_2 = (s32) (func_80083E80(M2C_FIELD(arg0, s16 *, 0x58)) * M2C_FIELD(arg0, s16 *, 0x64)) >> 0xC;
    temp_s2_2 = (s32) (func_80083E80(M2C_FIELD(arg0, s16 *, 0x56)) * (s16) temp_s0_2) >> 0xC;
    temp_lo = func_80083F50(M2C_FIELD(arg0, s16 *, 0x56)) * (s16) temp_s0_2;
    M2C_FIELD(arg0, u16 *, 0x36) = (u16) (M2C_FIELD(arg0, u16 *, 0x36) + temp_s2_2);
    M2C_FIELD(arg0, u16 *, 0x2E) = (u16) (M2C_FIELD(arg0, u16 *, 0x2E) - (temp_lo >> 0xC));
}

#define F16(p, o) M2C_FIELD(p, s16 *, o)
extern u16 D_800ECF54;
void f_UpdateA00TombaVerticalClimb(u8 *a) {
    s32 k;

    switch (a[6]) {
    case 0:
        func_80054198(a);
        func_80054D14(a, 0x40, 0);
        a[7] = 0;
        a[6]++;
    case 1:
        if (D_800ECF54 & 0x10) {
            if (!(D_1F80017C_0fe7 & 3)) {
                func_80074590(0x97, 0, -0x1E);
            }
            k = 0;
            func_80054D14(a, 0x41, 0);
            func_80076D68(a);
        } else if (D_800ECF54 & 0x40) {
            if (!(D_1F80017C_0fe7 & 3)) {
                func_80074590(0x97, 0, -0x1E);
            }
            k = 1;
            func_80054D14(a, 0x43, 0);
            func_80076D68(a);
        } else {
            func_80076D68(a);
            func_80054D14(a, 0x40, 4);
            k = 2;
        }
        if (func_8006271C(a, k) != 0 && func_80055824() != 0) {
            a[5] = 4;
            a[6] = 2;
            a[0x164] = 0;
            M2C_FIELD(a, s32 *, 0x158) = 0;
            a[7] = 0;
            F16(a, 0x58) = 0;
            F16(a, 0x40) = 8;
            func_80074590(0x1D, 0, 0);
            func_80055E28(a, 0);
            a[0x149] = (a[0x14A] & 1) + 2;
            func_80054D14(a, 0x14, 0);
        }
        break;
    }
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8010B07C);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8010B29C);

extern u8 D_800ECF58_742e[];
extern u8 D_8001B7B0[];
extern u8 D_800BF809;
extern u8 D_8014AABC_4433[];
#define H(p, o) (*(s16 *)((u8 *)(p) + (o)))
extern u8 *D_800ECF84;
extern s16 D_1F8000F0;
extern s16 D_1F8000F2;
typedef struct { s16 x, y, z, pad; } SVecDD58;
extern SVecDD58 D_1F8000C0_317e;
extern u8 D_1F800000[];
extern u8 D_1F8000D0_b839[];
extern s8 D_800BF80D;
extern u8 D_800E7E80_d97c;
extern u8 D_8014ABE8[];
extern u8 D_8014AC08[];
extern s16 D_1F800160_71b4;
extern s16 D_1F800162;
extern s16 D_1F800164_d75f;
extern u8 D_1F80027A;
void func_8010B42C(u8 *a, u8 *b)
{
    u8 *p = *(u8 **)(a + 0x10);
    s32 t, u, s;
    s16 r;
    s16 x;
    s16 z;

    t = (func_80083F50(H(p, 0xC)) * H(a, 0x156)) >> 12;
    u = func_80083E80(H(p, 0xC)) * H(a, 0x152);
    H(a, 0x32) = t + (H(p, 0x30) + (-u >> 12));
    r = (func_80083F50(H(p, 0xC) + 0x400) * H(a, 0x156)) >> 12;
    s = (func_80083F50(H(p, 0xA)) * r) >> 12;
    u = func_80083E80(H(p, 0xA)) * r;
    x = H(p, 0x2C) - (u >> 12);
    z = H(p, 0x34) + s;
    r = (func_80083F50(H(p, 0xC)) * H(a, 0x152)) >> 12;
    u = func_80083E80(H(b, 0x56)) * r;
    H(a, 0x2E) = x;
    H(a, 0x36) = z + (u >> 12);
    r = (func_80083E80(H(a, 0x58)) * H(a, 0x64)) >> 12;
    z = (func_80083E80(H(a, 0x56)) * r) >> 12;
    u = func_80083F50(H(a, 0x56)) * r;
    H(a, 0x36) += z;
    H(a, 0x2E) -= u >> 12;
    H(a, 0x32) += (func_80083F50(H(a, 0x58)) * H(a, 0x64)) >> 12;
}

s32 func_8010B600(s32 arg0) {
    u8 temp_v1;
    void *temp_s1;

    temp_s1 = M2C_FIELD(arg0, void **, 0x158);
    if (M2C_FIELD(temp_s1, u8 *, 0xC) == 4) {
        temp_v1 = M2C_FIELD(temp_s1, u8 *, 2);
        if (temp_v1 == 5) {
            return func_8010B29C(arg0, (s32) temp_s1);
        }
        if (temp_v1 == 8) {
            M2C_FIELD(temp_s1, s8 *, 0x29) = 1;
            M2C_FIELD(temp_s1, s16 *, 0x60) = (s16) -(s16) M2C_FIELD(arg0, u16 *, 0x152);
            func_800635D4(arg0, 1);
            func_80076D68(arg0);
            if ((M2C_FIELD(arg0, u8 *, 0x169) == 0) && (D_800ECF54 & (*(u16 *)0x1F800172 | 0x50))) {
                M2C_FIELD(arg0, s16 *, 0x58) = 0;
                func_8010B42C(arg0, (s32) temp_s1);
                return (s32) D_800ECF54;
            }
            func_8010B42C(arg0, (s32) temp_s1);
            if (func_80049280(arg0, 0, M2C_FIELD(arg0, s16 *, 0x62)) != 0) {
                M2C_FIELD(arg0, s8 *, 0x29) = 1;
                M2C_FIELD(arg0, u16 *, 0x6A) = (u16) *(u16 *)0x1F8001A6;
                func_80049674(arg0);
                M2C_FIELD(arg0, u16 *, 0x142) = (u16) *(u16 *)0x1F8001A2;
                M2C_FIELD(temp_s1, s8 *, 0x29) = 0;
                M2C_FIELD(arg0, s8 *, 0x164) = 0;
                M2C_FIELD(arg0, void **, 0x158) = NULL;
                func_80054198(arg0);
                M2C_FIELD(arg0, s8 *, 5) = 0;
                M2C_FIELD(arg0, s8 *, 6) = 0;
                M2C_FIELD(arg0, s8 *, 7) = 0;
                func_80054D14(arg0, 2, 4);
            }
            /* Duplicate return node #10. Try simplifying control flow for better match */
            return 0;
        }
        /* Duplicate return node #10. Try simplifying control flow for better match */
        return 0;
    }
    return 0;
}

extern s16 D_1F80016C;
extern s16 D_1F80016E;
extern u8 D_800BF840;
void func_8010B754(u8 *a, u8 *b) {
    if (++H(a, 0x42) >= 6) {
        if ((D_800ECF54 & D_1F80016C) && a[0x147] == 0) {
            a[7] = 0;
            H(a, 0x154) = 0;
            H(a, 0x42) = 0;
            a[0] |= 4;
            func_80054D14(a, 0x37, 0);
            return;
        } else if ((D_800ECF54 & D_1F80016E) && a[0x147] == 1) {
            a[7] = 0;
            H(a, 0x154) = 0;
            H(a, 0x42) = 0;
            a[0] |= 4;
            func_80054D14(a, 0x37, 0);
            return;
        }
    }
    if ((D_800ECF54 & D_1F80016C) && a[0x147] == 1) {
        a[7] = 6;
        func_80054D14(a, 0xA8, 0);
    } else if ((D_800ECF54 & D_1F80016E) && a[0x147] == 0) {
        a[7] = 6;
        func_80054D14(a, 0xA8, 0);
    } else if (D_800ECF54 & 0x10) {
        a[7] = 5;
        func_80054D14(a, 0x34, 0);
        func_80062A30(a, b, 0);
    } else if (D_800ECF54 & 0x40) {
        a[7] = 5;
        func_80054D14(a, 0x3D, 0);
        func_80062A30(a, b, 1);
    } else if (H(a, 0x42) >= 0x97) {
        D_800BF840 = 0x48;
    }
}

void f_UpdateA00TombaClingOrientation0(u8 *a, u8 *b, s32 f) {
    u8 *p;
    s16 ang;

    a[0x160] = 0;
    if (f == 0) {
        switch (a[7]) {
        case 0:
            func_80063098(a);
            func_80076D68(a);
            break;
        case 1:
            func_80063158(a);
            func_80076D68(a);
            break;
        case 2:
            a[0x5E] = 0;
            H(a, 0x42) = 0;
            func_80054D14(a, 0x29, 4);
            H(a, 0x40) = 0x5A;
            a[7]++;
        case 3:
            if (--H(a, 0x40) == 0) {
                H(a, 0x40) = 0x5A;
                a[7]++;
                if (!(func_8009A450() & 1)) {
                    func_80054D14(a, 0x28, 0);
                } else {
                    func_80054D14(a, 0x27, 0);
                }
            }
            func_8010B754(a, b);
            func_80076D68(a);
            break;
        case 4:
            if (--H(a, 0x40) == 0) {
                a[7]--;
                H(a, 0x40) = ((func_8009A450() & 3) + 3) * 30;
                if (H(a, 0x42) < 8) {
                    H(a, 0x42) = 8;
                }
                func_80054D14(a, 0x29, 4);
            }
            func_8010B754(a, b);
            func_80076D68(a);
            break;
        case 5:
            func_80076D68(a);
            if (D_800ECF54 & 0x10) {
                if (!(D_1F80017C_0fe7 & 3)) {
                    func_80074590(0x27, -5, -0x46);
                }
                func_80054D14(a, 0x34, 0);
                func_80062A30(a, b, 0);
            } else if (D_800ECF54 & 0x40) {
                if (!(D_1F80017C_0fe7 & 3)) {
                    func_80074590(0x27, -3, -0x46);
                }
                func_80054D14(a, 0x3D, 0);
                func_80062A30(a, b, 1);
            } else {
                a[7] = 3;
                H(a, 0x42) = 8;
                func_80054D14(a, 0x29, 4);
                H(a, 0x40) = 0x5A;
            }
            break;
        case 6:
            if (D_800ECF54 & 0xF0) {
                if ((D_800ECF54 & D_1F80016C) && a[0x147] == 0) {
                    a[7] = 0;
                    H(a, 0x154) = 0;
                    H(a, 0x42) = 0;
                    a[0] |= 4;
                    func_80054D14(a, 0x37, 0);
                } else if ((D_800ECF54 & D_1F80016E) && a[0x147] == 1) {
                    a[7] = 0;
                    H(a, 0x154) = 0;
                    H(a, 0x42) = 0;
                    a[0] |= 4;
                    func_80054D14(a, 0x37, 0);
                } else if (D_800ECF54 & 0x10) {
                    a[7] = 5;
                    func_80054D14(a, 0x34, 0);
                    func_80062A30(a, b, 0);
                } else if (D_800ECF54 & 0x40) {
                    a[7] = 5;
                    func_80054D14(a, 0x3D, 0);
                    func_80062A30(a, b, 1);
                } else {
                    func_80076D68(a);
                }
            } else {
                H(a, 0x40) = 0x5A;
                H(a, 0x42) = 8;
                a[7] = 3;
                func_80054D14(a, 0xA9, 0);
            }
            break;
        }
    }
    p = *(u8 **)(a + 0x10);
    if (*(s32 *)(a + 0x158) != 0) {
        ang = H(a, 0x56) + 0x800;
        H(a, 0x2E) = H(p, 0x2C) + ((func_80083F50(ang) * H(a, 0x152)) >> 12);
        H(a, 0x36) = H(p, 0x34) - ((func_80083E80(ang) * H(a, 0x152)) >> 12);
    }
    H(a, 0x32) = H(p, 0x30) + H(a, 0x156);
}

void func_8010BD7C(u8 *a, u8 *b) {
    if (++H(a, 0x42) >= 6) {
        if ((D_800ECF54 & D_1F80016C) && a[0x147] == 0) {
            a[7] = 0;
            H(a, 0x154) = 0;
            H(a, 0x42) = 0;
            a[0] |= 4;
            func_80054D14(a, 0x38, 0);
            return;
        } else if ((D_800ECF54 & D_1F80016E) && a[0x147] == 1) {
            a[7] = 0;
            H(a, 0x154) = 0;
            H(a, 0x42) = 0;
            a[0] |= 4;
            func_80054D14(a, 0x38, 0);
            return;
        }
    }
    if ((D_800ECF54 & D_1F80016C) && a[0x147] == 1) {
        a[7] = 6;
        func_80054D14(a, 0xAA, 0);
    } else if ((D_800ECF54 & D_1F80016E) && a[0x147] == 0) {
        a[7] = 6;
        func_80054D14(a, 0xAA, 0);
    } else if (H(a, 0x42) >= 0x97) {
        D_800BF840 = 0x48;
    }
}

void f_UpdateA00TombaClingOrientation1(u8 *a, u8 *b, s32 f) {
    u8 *p;
    s16 ang;

    a[0x160] = 1;
    if (f == 0) {
        switch (a[7]) {
        case 0:
            func_80063098(a);
            func_80076D68(a);
            break;
        case 1:
            func_80063158(a);
            func_80076D68(a);
            break;
        case 2:
            a[0x5E] = 0;
            H(a, 0x42) = 0;
            func_80054D14(a, 0x31, 4);
            H(a, 0x40) = 0x5A;
            a[7]++;
        case 3:
            if (--H(a, 0x40) == 0) {
                H(a, 0x40) = 0x5A;
                a[7]++;
                if (!(func_8009A450() & 1)) {
                    func_80054D14(a, 0x30, 0);
                } else {
                    func_80054D14(a, 0x2E, 0);
                }
            }
            if (b[0x5E] == 1) {
                a[7] = 5;
                if (!(func_8009A450() & 1)) {
                    func_80054D14(a, 0x32, 0);
                } else {
                    func_80054D14(a, 0x2D, 0);
                }
            } else {
                func_8010BD7C(a, b);
                func_80076D68(a);
            }
            break;
        case 4:
            if (--H(a, 0x40) == 0) {
                a[7]--;
                if (H(a, 0x42) < 8) {
                    H(a, 0x42) = 8;
                }
                func_80054D14(a, 0x31, 4);
                H(a, 0x40) = ((func_8009A450() & 3) + 3) * 30;
            }
            func_8010BD7C(a, b);
            func_80076D68(a);
            break;
        case 5:
            if (func_80076D68(a) == 1) {
                a[7] = 3;
                if (H(a, 0x42) < 8) {
                    H(a, 0x42) = 8;
                }
                func_80054D14(a, 0x31, 4);
                H(a, 0x40) = ((func_8009A450() & 3) + 3) * 30;
            }
            func_8010BD7C(a, b);
            break;
        case 6:
            if (D_800ECF54 & 0xA0) {
                if ((D_800ECF54 & D_1F80016C) && a[0x147] == 0) {
                    a[7] = 0;
                    H(a, 0x154) = 0;
                    H(a, 0x42) = 0;
                    a[0] |= 4;
                    func_80054D14(a, 0x38, 0);
                } else if ((D_800ECF54 & D_1F80016E) && a[0x147] == 1) {
                    a[7] = 0;
                    H(a, 0x154) = 0;
                    H(a, 0x42) = 0;
                    a[0] |= 4;
                    func_80054D14(a, 0x38, 0);
                } else {
                    func_80076D68(a);
                }
            } else {
                H(a, 0x40) = 0x5A;
                H(a, 0x42) = 8;
                a[7] = 3;
                func_80054D14(a, 0xAB, 0);
            }
            break;
        }
    }
    p = *(u8 **)(a + 0x10);
    if (*(s32 *)(a + 0x158) != 0) {
        ang = H(a, 0x56) + 0x800;
        H(a, 0x2E) = H(p, 0x2C) + ((func_80083F50(ang) * H(a, 0x152)) >> 12);
        H(a, 0x36) = H(p, 0x34) - ((func_80083E80(ang) * H(a, 0x152)) >> 12);
    }
    H(a, 0x32) = H(p, 0x30) + H(a, 0x156);
}

/* func_8010C9F8, inlined */
static inline void inl_8010C9F8(u8 *a, u8 *b, s32 f) {
    s16 ang;

    a[0x160] = 0;
    if (f == 0) {
        func_80054D14(a, 0x29, 4);
    }
    a[7] = 0;
    func_80076D68(a);
    ang = M2C_FIELD(a, s16 *, 0x56) + 0x800;
    M2C_FIELD(a, s16 *, 0x2E) = M2C_FIELD(b, s16 *, 0x2E) + ((func_80083F50(ang) * M2C_FIELD(a, s16 *, 0x152)) >> 12);
    M2C_FIELD(a, s16 *, 0x36) = M2C_FIELD(b, s16 *, 0x36) - ((func_80083E80(ang) * M2C_FIELD(a, s16 *, 0x152)) >> 12);
    M2C_FIELD(a, s16 *, 0x32) = M2C_FIELD(b, s16 *, 0x32) + M2C_FIELD(a, s16 *, 0x156);
    if (b[0x5E] == 2) {
        M2C_FIELD(a, s32 *, 0x158) = 0;
        a[0x164] = 0;
        M2C_FIELD(a, s16 *, 0x40) = 8;
        func_80056D44(a, 0);
    }
}
void func_8010C290(u8 *a, s32 f) {
    u8 *b = M2C_FIELD(a, u8 **, 0x158);

    switch (b[0xC]) {
    case 4:
        switch (b[2]) {
        case 0:
            f_UpdateA00TombaClingOrientation1(a, b, f);
            break;
        case 1:
            f_UpdateA00TombaClingOrientation0(a, b, f);
            break;
        }
        break;
    case 5:
        if (b[2] == 2) {
            inl_8010C9F8(a, b, f);
        }
        break;
    }
}

extern u16 D_1F80019E_7f82;
extern s16 D_1F8001A4_f18c;
s32 func_8010C40C(u8 *a, u8 *b) {
    s16 v[8];

    switch ((U(b, 0x6A) >> 8) & 0xF) {
    case 1:
        v[1] = U(a, 0x2E);
        v[3] = D_1F80019E_7f82;
        v[5] = U(a, 0x36);
        if (b[0x145] != 0) {
            func_8003116C(0x10D, v, -0xA);
            v[3] += 0x50;
            func_8003116C(0x107, v, -0xA);
            func_80074590(7, 0, 0);
            return 2;
        }
        func_8003116C(8, v, -0x50);
        return 1;
    case 2:
        if (func_800489E4(a, H(a, 0x32)) == 0) {
            return 0;
        }
        if (H(b, 0x32) + H(b, 0x84) - D_1F8001A4_f18c < 0x15) {
            return 4;
        }
        v[1] = U(a, 0x2E);
        v[3] = D_1F8001A4_f18c;
        v[5] = U(a, 0x36);
        func_8003116C(0x10D, v, -0xA);
        if ((s16)abs(H(b, 0x44)) > 0x1000) {
            v[1] = U(a, 0x2E);
            v[3] = D_1F8001A4_f18c;
            v[5] = U(a, 0x36);
            func_8003116C(8, v, -0x50);
        }
        return 3;
    }
    return 0;
}

#define H_f12c(p, o) (*(s16 *)((u8 *)(p) + (o)))
extern u8 D_80146ED0[];
void f_UpdateTombaInteriorEntry(u8 *a, u8 *b) {
    u8 k;
    s32 r;
    s32 v;
    s16 w;

    switch (a[5]) {
    case 0:
        k = b[0x181];
        if (k == 0 || a[0x5F] == 0) {
            a[0x5F] = k;
            r = func_8010C40C(a, b);
            if (r != 0) {
                a[5] = r;
                if (r == 2) {
                    H_f12c(a, 0xE) = 10;
                    return;
                }
                w = abs(H_f12c(b, 0x44));
                if (w > 0x3800) {
                    w = 0x3800;
                }
                H_f12c(a, 0xE) = D_80146ED0[w >> 11];
                if (w > 0x800) {
                    a[6] = 0;
                    return;
                }
                a[6] = 1;
                return;
            }
        }
        break;
    case 1:
    case 3:
        if (--H_f12c(a, 0xE) == 0) {
            goto reset;
        }
        if (a[6] != 0) {
            v = H_f12c(b, 0x44);
            if (v < 0) {
                v = -v;
            }
            if (v > 0x800) {
                goto reset;
            }
            if (b[0x145] != 0) {
                a[5] = 0;
            }
        }
        break;
    case 2:
        if (--H_f12c(a, 0xE) == 0) {
    case 4:
        reset:
            a[5] = 0;
        }
        break;
    }
}

extern s8 D_1F800138[];
extern s8 D_1F80019B[];
void func_8010C740(void) {
    func_80045258(M2C_FIELD(*((volatile void **)D_1F800138), u8 *, 0x6E), 0xF);
    *((volatile s8 *)D_1F80019B) = 1;
    func_80051FB4();
}

#define F16(p, o) M2C_FIELD(p, s16 *, o)
void func_8010C780(u8 *a) {
    s32 k;

    if (D_800ECF54 & 0x10) {
        k = 0;
        func_80054D14(a, 0x41, 0);
        func_80076D68(a);
    } else if (D_800ECF54 & 0x40) {
        k = 1;
        func_80054D14(a, 0x43, 0);
        func_80076D68(a);
    } else {
        k = 2;
    }
    if (func_8010B07C(a, k) != 0 && func_80055824() != 0) {
        a[5] = 4;
        a[6] = 2;
        F16(a, 0x44) = 0;
        a[0x164] = 0;
        M2C_FIELD(a, s32 *, 0x158) = 0;
        a[7] = 0;
        F16(a, 0x58) = 0;
        F16(a, 0x40) = 8;
        func_80074590(0x1D, 0, 0);
        func_80055E28(a, 0);
        a[0x149] = (a[0x14A] & 1) + 2;
        func_80054D14(a, 0x14, 0);
    }
}

void func_8010C87C(void) {
    func_8010A7F8();
}

void func_8010C89C(void *a, void *b)
{
    func_80056B48(a, 1);
    f_UpdateA00TombaWaterSurfaceMotion(a, b);
    func_80055D5C(a);
}

extern u16 D_1F800172;
extern u16 D_1F8001A6;
extern u16 D_1F8001A2;
s32 func_8010C8E4(u8 *a, u8 *b) {
    b[0x29] = 1;
    M2C_FIELD(b, s16 *, 0x60) = -M2C_FIELD(a, s16 *, 0x152);
    func_800635D4(a, 1);
    func_80076D68(a);
    if (a[0x169] == 0 && (D_800ECF54 & (D_1F800172 | 0x50))) {
        M2C_FIELD(a, s16 *, 0x58) = 0;
        func_8010B42C(a, b);
        return D_800ECF54;
    }
    func_8010B42C(a, b);
    if (func_80049280(a, 0, M2C_FIELD(a, s16 *, 0x62)) != 0) {
        a[0x29] = 1;
        M2C_FIELD(a, s16 *, 0x6A) = D_1F8001A6;
        func_80049674(a);
        M2C_FIELD(a, s16 *, 0x142) = D_1F8001A2;
        b[0x29] = 0;
        a[0x164] = 0;
        M2C_FIELD(a, s32 *, 0x158) = 0;
        func_80054198(a);
        a[5] = 0;
        a[6] = 0;
        a[7] = 0;
        func_80054D14(a, 2, 4);
    }
    return 0;
}

void func_8010C9F8(u8 *a, u8 *b, s32 f) {
    s16 ang;

    a[0x160] = 0;
    if (f == 0) {
        func_80054D14(a, 0x29, 4);
    }
    a[7] = 0;
    func_80076D68(a);
    ang = M2C_FIELD(a, s16 *, 0x56) + 0x800;
    M2C_FIELD(a, s16 *, 0x2E) = M2C_FIELD(b, s16 *, 0x2E) + ((func_80083F50(ang) * M2C_FIELD(a, s16 *, 0x152)) >> 12);
    M2C_FIELD(a, s16 *, 0x36) = M2C_FIELD(b, s16 *, 0x36) - ((func_80083E80(ang) * M2C_FIELD(a, s16 *, 0x152)) >> 12);
    M2C_FIELD(a, s16 *, 0x32) = M2C_FIELD(b, s16 *, 0x32) + M2C_FIELD(a, s16 *, 0x156);
    if (b[0x5E] == 2) {
        M2C_FIELD(a, s32 *, 0x158) = 0;
        a[0x164] = 0;
        M2C_FIELD(a, s16 *, 0x40) = 8;
        func_80056D44(a, 0);
    }
}

extern u16 D_1F8001A4;
void func_8010CAEC(u8 *a)
{
    s16 v[8];

    v[1] = *(u16 *)(a + 0x2E);
    v[3] = D_1F8001A4;
    v[5] = *(u16 *)(a + 0x36);
    func_8003116C(0x10D, v, -0xA);
    v[3] += 0x50;
    func_8003116C(0x107, v, -0xA);
    func_80074590(7, 0, 0);
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_InitializeA00InteriorState);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateA00InteriorCamera);

void func_8010CED0(u8 *a) {
    s16 x = D_1F800160_71b4;
    s32 d;

    if (x < 0x1451) {
        M2C_FIELD(a, s32 *, 0x28) = 0;
        M2C_FIELD(a, s16 *, 0x26) = 0;
    } else if (x < 0x1E79) {
        M2C_FIELD(a, s32 *, 0x28) = 0;
        M2C_FIELD(a, s16 *, 0x26) = -800;
    } else if (x < 0x20D1) {
        d = x - 0x1E78;
        M2C_FIELD(a, s16 *, 0x26) = ((d * 0x32000) / 600 >> 8) - 800;
    } else if (x < 0x2969) {
        M2C_FIELD(a, s16 *, 0x26) = 0;
    } else if (x < 0x2AF9) {
        d = x - 0x2968;
        M2C_FIELD(a, s16 *, 0x26) = (d * 3) >> 2;
    } else {
        M2C_FIELD(a, s16 *, 0x26) = 300;
    }
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateFishermensTownCamera);

extern s16 D_1F8000D0[];
extern u8 D_800BF9DD;
void func_8010D89C(u8 *a) {

    switch (a[4]) {
    case 0:
        H_f12c(a, 0x68) = 0x28;
        a[4]++;

        D_1F8000D0[7] = 0x34FD;
        D_1F8000D0[9] = -0xD52;
        D_1F8000D0[11] = 0x1332;
        D_1F8000D0[1] = 0x3207;
        D_1F8000D0[3] = -0x12F3;
        D_1F8000D0[5] = 0x1290;
        func_8006D02C(a);
        break;
    case 1:
        if (--H_f12c(a, 0x68) == 0) {
            a[4]++;
            D_1F8000D0[1] = 0x3BDC;
            D_1F8000D0[3] = -0x6F7;
            D_1F8000D0[5] = 0x1283;
        }
        break;
    case 2:
        func_8006E3B0(a, a + 0x38);

        if (D_1F8000D0[9] < -0x334) {
            a[4]++;
            D_1F8000D0[1] = 0x34FB;
            D_1F8000D0[5] = 0x1608;
            D_1F8000D0[3] = -0x4B0;
        }
        break;
    case 3:
        if (D_800BF9DD == 0xF) {
            a[4]++;
        }

        if (D_1F8000D0[9] < -0x37A) {
            if ((D_1F8000D0[3] += 0x10) >= -0xC7) {
                D_1F8000D0[3] = -0xC8;
            }
        }
        func_8006E3B0(a, a + 0x38);
        break;
    case 4:
        *(s32 *)(a + 0x58) = 0;
        a[0x67] = 0;
        a[0x64] = 6;
        break;
    }
}

extern s8 D_1F800138[];
extern s8 D_1F80019B[];
void func_8010DA70(void) {
    func_80045258(M2C_FIELD(*((volatile void **)D_1F800138), u8 *, 0x6E), 0xF);
    *((volatile s8 *)D_1F80019B) = 1;
    func_80051FB4();
}

extern u8 D_800E7E80[];
extern u8 D_800BF808_1760[];
extern u8 D_800E8008[];
extern s32 D_1F800184;
void func_8010DAB0(void) {
    u8 *t = D_800E7E80;
    u8 *g = D_800BF808_1760;
    u8 *e = D_800E8008;
    s16 *v;

    t[0x16B] = 0;
    g[0xE] = 0;
    e[0x64] = 0;
    D_1F800184 = 0;
    if (g[0xF] == 2) {
        t[0x2A] = 0x1F;
        v = D_1F8000D0;
        M2C_FIELD(e, s16 *, 0xA) = 0x4F00;
        M2C_FIELD(e, s16 *, 0x12) = 0x1AEE;
        v[0xB] = 0x1AEE;
        v[1] = 0x5716;
        v[7] = 0x4F00;
        v[5] = 0x1BE1;
        t[0x147] = 0;
        g[0x17] = 0;
    }
    func_80054198(t);
    t[5] = 0x24;
    t[6] = 0;
}

extern u8 D_80146EEC[];
extern u8 D_800BF871;
void func_8010DB58(u8 *a) {
    s16 *v;

    switch (a[2]) {
    case 0:
        a[2]++;
        if ((a[3] = D_80146EEC[D_800BF871]) == 9) {
            v = D_1F8000D0;
            v[1] = 0x354F;
            v[3] = -0xF8D;
            v[5] = 0x1BFD;
        }
    case 1:
        f_UpdateFishermensTownCamera();
        break;
    }
}

extern s16 D_800E7FFE;
extern u8 D_800BF821;
void func_8010DBE4(u8 *a) {
    s32 d;

    if (D_800E7FFE & 0x8000) {
        M2C_FIELD(a, s16 *, 0x26) = 0;
        return;
    }
    if (D_800BF821 != 0) {
        M2C_FIELD(a, s16 *, 0x26) = -600;
        return;
    }
    if (D_1F800160_71b4 < 0x364D) {
        d = D_1F800160_71b4 - 0x2D50;
        M2C_FIELD(a, s16 *, 0x26) = 0;
        if (d > 0) {
            M2C_FIELD(a, s16 *, 0x26) = ((d * 0x7800) / 2300) >> 8;
        }
    }
}

void func_8010DC74(u8 *a, s32 target, s32 step) {
    s32 v = M2C_FIELD(a, s32 *, 0x28);

    if (v == target) {
        return;
    }
    if (v < target) {
        M2C_FIELD(a, s32 *, 0x28) = v + step;
        if (target < v + step) {
            M2C_FIELD(a, s32 *, 0x28) = target;
        }
    } else {
        M2C_FIELD(a, s32 *, 0x28) = v - step;
        if (v - step < target) {
            M2C_FIELD(a, s32 *, 0x28) = target;
        }
    }
}

extern s8 D_800BF808[];
extern u8 D_1F800137;
extern s32 D_1F80009C;
void func_8010DCB8(u8 *a, u8 *b) {
    s32 t, u;

    if (D_1F800137 != 0 || D_800BF808[5] != 0) {
        return;
    }
    if (M2C_FIELD(a, s16 *, 0x17E) & 0x8200) {
        if (func_8002300C(a, b, 0x20) != 0) {
            if (!(a[0] & 4)) {
                t = (func_80083F50(D_1F80009C + 0x800) * (M2C_FIELD(a, s16 *, 0x80) + 0x20)) >> 12;
                u = func_80083E80(D_1F80009C + 0x800) * (M2C_FIELD(a, s16 *, 0x80) + 0x20);
                M2C_FIELD(a, s16 *, 0x2E) = M2C_FIELD(b, s16 *, 0x2E) + t;
                M2C_FIELD(a, s16 *, 0x36) = M2C_FIELD(b, s16 *, 0x36) - (u >> 12);
            }
            M2C_FIELD(a, s8 *, 0x5F) = func_80077768((s16)(*(u16 *)&D_1F80009C + 0x800), M2C_FIELD(a, s16 *, 0x140), 1) + 2;
        }
    } else if (func_80022F04(a, b) != 0) {
        b[0x29] = 1;
        D_1F800137 = 2;
        D_800BF808[0x39] = 1;
    }
}

#define F16(p, o) M2C_FIELD(p, s16 *, o)
#define FU16(p, o) M2C_FIELD(p, u16 *, o)
extern u8 D_1F800182_5650;
void func_8010DE0C(u8 *a, u8 *b) {
    u8 *q = a + 0x60;
    u32 k;
    s32 s;
    s32 c;

    if (D_1F800137 != 0) {
        return;
    }
    if (D_800BF80D != 0) {
        return;
    }
    if (func_8002300C(a, b, 0x50) == 0) {
        return;
    }
    if (a[0x5F] == 0x10) {
        if ((u16)(FU16(a, 0x84) + (FU16(a, 0x32) - (FU16(b, 0x32) + (FU16(b, 0x86) - FU16(b, 0x84))) + 20)) <= F16(a, 0x86) + 40) {
            k = a[0x46] >> 1;
            if ((s32)k >= 0) {
                if ((s32)k < 2) {
                    s = (func_80083F50(F16(q, 8) + 0x800) * (F16(a, 0x80) + 0x20)) >> 12;
                    c = func_80083E80(F16(q, 8) + 0x800) * (F16(a, 0x80) + 0x20);
                    F16(a, 0x2E) = FU16(b, 0x2E) + s;
                    F16(a, 0x36) = FU16(b, 0x36) - (c >> 12);
                    F16(a, 0x32) = FU16(b, 0x32) + (FU16(b, 0x86) - FU16(b, 0x84));
                } else if ((s32)k < 4) {
                    F16(a, 0x32) = FU16(b, 0x32) + (FU16(b, 0x86) - FU16(b, 0x84));
                    F16(a, 0x2E) = FU16(b, 0x2E);
                    F16(a, 0x36) = FU16(b, 0x36);
                }
            }
            func_8001E860(a, b, 0, 0x100);
        } else {
            func_8001E860(a, b, 0, 0);
        }
        D_1F800182_5650 = 0;
    } else if (!(func_8001E860(a, b, 0, 0) & 0x80)) {
        D_1F800182_5650 = 0;
    }
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8010DFD8);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_ResolveTombaSpecialCylinderContact);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_HandleFishermensTownTombaHazardsAndBounds);

typedef struct { u8 pad0[7]; u8 unk7; u8 pad8[6]; u8 unkE; u8 unkF; u8 pad10[0x21]; u8 unk31; s16 unk32; } AreaState808_E;
extern AreaState808_E D_800BF808_9a69;
extern u8 D_1F800236;
extern u8 D_800E7FEB;
/* func_80114CD0, inlined */
static inline void inl_80114CD0(u8 *a) {
    AreaState808_E *g = &D_800BF808_9a69;

    if (g->unkE != 0 && g->unkF == 2 && M2C_FIELD(a, s16 *, 0x32) < -0xE74 && M2C_FIELD(a, s16 *, 0x36) < 0x1451) {
        D_1F800137 = 2;
        g->unk7 = 2;
        g->unk31 = 1;
        g->unk32 = 0x100;
        D_1F800236 = 1;
    }
}
/* func_80114D48, inlined */
static inline void inl_80114D48(u8 *a) {
    u8 *g = D_800BF808_1760;
    u16 lim = M2C_FIELD(g, u16 *, 0xA);

    switch (g[0xF]) {
    case 2:
        if (D_800E7FEB != 8) {
            break;
        }
        if (M2C_FIELD(a, s16 *, 0x36) < 0x1A05) {
            M2C_FIELD(a, s16 *, 0x36) = 0x1A04;
        }
    case 0:
    case 1:
        if (!(a[0x145] & 1) && M2C_FIELD(a, s16 *, 0x32) >= (s16)lim - M2C_FIELD(a, s16 *, 0x62)) {
            M2C_FIELD(a, s16 *, 0x32) = lim - M2C_FIELD(a, u16 *, 0x62);
            func_80022C78(a);
        }
        break;
    }
}
void f_EnforceA00TombaBoundsAndInteriorExit(u8 *a) {
    if (D_800BF808_1760[0xE] != 0) {
        inl_80114D48(a);
    } else if (D_1F800137 == 0) {
        f_HandleFishermensTownTombaHazardsAndBounds(a);
    }
    if (a[0x17B] == 0) {
        AreaState808_E *g = &D_800BF808_9a69;
        if ((s8)g->pad0[5] == 0 && g->unk31 == 0) {
            inl_80114CD0(a);
        }
    }
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_ResolveTombaType13ActorContact);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8010EC58);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8010F034);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_ResolveTombaBoxPartContact);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_ResolveTombaOrientedWallContact);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_ResolveActiveColliderOrientedWallContact);

void func_80110024(u8 *a, u8 *b, u8 *c) {
    u8 *q = a + 0x60;
    s32 r;
    s32 s1;
    u16 x;
    u16 z;
    u16 y;
    s16 dx;
    s16 dz;
    s32 t;
    s32 u;

    r = (func_80083E80(F16(c, 0xC)) * 0x6E) >> 12;
    s1 = (func_80083E80(F16(b, 0x56)) * (s16)r) >> 12;
    x = FU16(c, 0x2C) - ((func_80083F50(F16(b, 0x56)) * (s16)r) >> 12);
    dx = FU16(a, 0x2E) - x;
    z = FU16(c, 0x34) + s1;
    dz = FU16(a, 0x36) - z;
    if ((u16)func_80084080(dx * dx + dz * dz) > F16(a, 0x80) + F16(b, 0x80)) {
        return;
    }
    y = FU16(c, 0x30) + ((func_80083F50(F16(c, 0xC)) * 0x6E) >> 12);
    if ((u16)((FU16(a, 0x32) - y) + (FU16(a, 0x84) + FU16(b, 0x84))) > F16(a, 0x86) + F16(b, 0x86)) {
        return;
    }
    if (a[0x5F] == 0x10) {
        switch (a[0x46] >> 1) {
        case 0:
        case 1:
            t = (func_80083F50(F16(q, 8) + 0x800) * (F16(a, 0x80) + F16(b, 0x80))) >> 12;
            u = func_80083E80(F16(q, 8) + 0x800) * (F16(a, 0x80) + F16(b, 0x80));
            F16(a, 0x2E) = x + t;
            F16(a, 0x32) = y;
            F16(a, 0x36) = z - (u >> 12);
            break;
        case 2:
        case 3:
            F16(a, 0x2E) = x;
            F16(a, 0x36) = z;
            F16(a, 0x32) = FU16(a, 0x84) + (y + (FU16(b, 0x86) - FU16(b, 0x84)));
            break;
        }
    } else {
        b[0x2B] = 1;
        b[0x5F] = FU16(a, 0x56) >> 4;
    }
    func_8001E860(a, b, c, 0x200);
    D_1F800182_5650 = 0;
}

extern s8 D_1F800182[];
void func_80110298(void *arg0, void *arg1) {
    s32 temp_lo;
    s32 temp_s0_2;
    u32 temp_v1;
    void *temp_s0;
    void *var_s1;

    temp_s0 = arg0 + 0x60;
    var_s1 = arg1;
loop_1:
    if (func_80022E04(arg0, arg1, M2C_FIELD(var_s1, void **, 0xC0)) != 0) {
        if (M2C_FIELD(arg0, u8 *, 0x5F) == 0x10) {
            temp_v1 = (u8) M2C_FIELD(arg0, u8 *, 0x46) >> 1;
            if ((s32) temp_v1 >= 0) {
                if ((s32) temp_v1 < 2) {
                    temp_s0_2 = (s32) (func_80083F50(M2C_FIELD(temp_s0, s16 *, 8) + 0x800) * (M2C_FIELD(arg0, s16 *, 0x80) + M2C_FIELD(arg1, s16 *, 0x80))) >> 0xC;
                    temp_lo = func_80083E80(M2C_FIELD(temp_s0, s16 *, 8) + 0x800) * (M2C_FIELD(arg0, s16 *, 0x80) + M2C_FIELD(arg1, s16 *, 0x80));
                    M2C_FIELD(arg0, s16 *, 0x2E) = (s16) (M2C_FIELD(M2C_FIELD(var_s1, void **, 0xC0), u16 *, 0x2C) + temp_s0_2);
                    M2C_FIELD(arg0, s16 *, 0x36) = (s16) (M2C_FIELD(M2C_FIELD(var_s1, void **, 0xC0), u16 *, 0x34) - (temp_lo >> 0xC));
                    M2C_FIELD(arg0, u16 *, 0x32) = (u16) M2C_FIELD(M2C_FIELD(var_s1, void **, 0xC0), u16 *, 0x30);
                } else if ((s32) temp_v1 < 4) {
                    M2C_FIELD(arg0, u16 *, 0x32) = (u16) (M2C_FIELD(arg0, u16 *, 0x84) + (M2C_FIELD(M2C_FIELD(var_s1, void **, 0xC0), u16 *, 0x30) + M2C_FIELD(arg1, u16 *, 0x84)));
                }
            }
        }
        func_8001E860(arg0, arg1, M2C_FIELD(var_s1, void **, 0xC0), 0x200);
        *((s8 *)D_1F800182) = 0;
        return;
    }
    var_s1 += 4;
    if ((s32) var_s1 >= (s32) (arg1 + 8)) {
        return;
    }
    goto loop_1;
}

#define F16(p, o) M2C_FIELD(p, s16 *, o)
#define FU16(p, o) M2C_FIELD(p, u16 *, o)
extern s32 D_1F800088;
extern u8 *D_1F800084;
s32 func_8011040C(u8 *a, u8 *b, u8 *c) {
    s16 rad, ox, oz, dx, dz;
    u16 r, ah, ay;
    s32 h;

    rad = (func_80083E80(F16(c, 0xC)) * 110) >> 12;
    ox = (func_80083E80(F16(b, 0x56)) * rad) >> 12;
    oz = (func_80083F50(F16(b, 0x56)) * rad) >> 12;
    dx = FU16(a, 0x14C) - (FU16(c, 0x2C) - oz);
    dz = FU16(a, 0x150) - (FU16(c, 0x34) + ox);
    r = func_80084080(dx * dx + dz * dz);
    if (F16(b, 0x80) + D_1F800088 < r) {
        return 0;
    }
    h = ((func_80083F50(F16(c, 0xC)) * 110) >> 12) + FU16(c, 0x30);
    ay = FU16(a, 0x14E);
    ah = FU16(a, 0x68);
    if ((u16)(ay - h + (FU16(b, 0x84) + ah)) > F16(b, 0x86) + ((s16)ah << 1)) {
        return 0;
    }
    F16(a, 0x156) = 110;
    D_1F800084 = c;
    return 1;
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_ResolveTombaOrientedPlatformContact);

s32 func_80110CA0(u8 *a, u8 *b) {
    s16 dx = FU16(a, 0x2E) - FU16(b, 0x2E);
    s16 dz = FU16(a, 0x36) - FU16(b, 0x36);
    s32 d = func_80084080(dx * dx + dz * dz);
    u16 ra;
    u16 rb;
    u16 b84;
    u16 a84;
    u16 b86;
    s16 dy;
    s16 h;
    s16 e;
    s16 f;
    s16 s;

    ra = FU16(a, 0x80);
    rb = FU16(b, 0x80);
    if ((u16)d > F16(a, 0x80) + F16(b, 0x80)) {
        return -1;
    }
    b84 = FU16(b, 0x84);
    a84 = FU16(a, 0x84);
    b86 = FU16(b, 0x86);
    dy = FU16(a, 0x32) - FU16(b, 0x32);
    h = (b84 + FU16(a, 0x86)) - a84;
    if ((u16)(dy + h) > F16(a, 0x86) + F16(b, 0x86)) {
        return -1;
    }
    s = ra + rb - d;
    if (dy < 0) {
        dy = -dy;
        e = h;
        f = -h;
    } else {
        f = e = a84 + (b86 - b84);
    }
    if (s < (s16)(e - dy)) {
        return 0;
    }
    if (f <= 0) {
        return 2;
    }
    return 3;
}

extern u8 **D_1F800158;
s32 func_80110DE8(u8 *a) {
    s8 r;
    u8 **l;
    u8 *e;
    s32 k;
    u8 t;

    r = D_800BF80D;
    if (r != 0) {
        return r;
    }
    l = D_1F800158;
    D_1F800182_5650 = *(u8 *)0x1F80015E;
    while (D_1F800182_5650 != 0) {
        e = *l;
        (D_1F800182_5650)--;
        l++;
        if ((e[0] & 1) && (t = e[2]) == 1 && e[3] == 0) {
            k = func_80110CA0(a, e);
            if (k == 2) {
                a[0] = k;
                a[4] = k;
                a[5] = 0;
                a[6] = 0;
                e[0] = k;
                e[4] = k;
                e[5] = t;
                e[6] = 0;
            }
            return 1;
        }
    }
    return 0;
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_ResolveCarriedChickSurfaceContact);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80111128);

#define H(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define U(p, o) (*(u16 *)((u8 *)(p) + (o)))
extern u16 D_1F80018E_f9ee;
extern u16 D_1F80018C;
extern u16 D_1F80008C;
void f_ResolveTombaPlaneSwitchActorContact(u8 *a, u8 *b)
{
    s32 k;
    s32 g;
    s32 m;
    s32 c;
    s32 x, y;
    if (func_8002300C(a, b, H(b, 0x80) * 4) == 0) {
        return;
    }
    b[0x2B] = 1;
    if (D_1F800137 == 0) {
        m = U(a, 0x140) - 0x400;
        g = func_80085690(-(s16)(U(b, 0x36) - U(a, 0x36)), (s16)(U(b, 0x2E) - U(a, 0x2E))) << 4;
        if (abs((s16)(g - m * 16)) < 0x1000) {
            D_1F80018E_f9ee = 0x4100;
            D_1F80018C = U(a, 0x140) - 0x400;
            D_800BF840 = 0x42;
        } else {
            c = U(a, 0x140) + 0x400;
            if (abs((s16)(g - c * 16)) < 0x1000) {
                D_1F80018C = c;
                D_1F80018E_f9ee = 0x4200;
                D_800BF840 = 0x43;
            }
        }
    }
    if (H(a, 0x80) + H(b, 0x80) + 60 < D_1F80008C) {
        return;
    }
    b[0x2B] = 2;
    if (H(a, 0x80) + H(b, 0x80) < D_1F80008C) {
        return;
    }
    x = (func_80083F50(D_1F80009C + 0x800) * (H(a, 0x80) + H(b, 0x80))) >> 12;
    y = (func_80083E80(D_1F80009C + 0x800) * (H(a, 0x80) + H(b, 0x80))) >> 12;
    U(a, 0x2E) = U(b, 0x2E) + x;
    U(a, 0x36) = U(b, 0x36) - y;
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_ResolveActorPairType0Contact);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_ResolveActorPairType3Contact);

s32 func_80111A00(u8 *a, u8 *b, u8 *c)
{
    s16 dx = *(u16 *)(a + 0x14C) - *(u16 *)(c + 0x2C);
    s16 dz = *(u16 *)(a + 0x150) - *(u16 *)(c + 0x34);
    u16 d = func_80084080(dx * dx + dz * dz);
    u16 cy;
    s16 t;
    u16 h;

    if (*(s16 *)(b + 0x80) + D_1F800088 < d) {
        return 0;
    }
    {
        s32 k = *(u16 *)(a + 0x14E);
        cy = *(u16 *)(c + 0x30);
        k = k - cy + 0x64;
        h = *(volatile u16 *)(a + 0x68);
        k = (u16)(h + k);
        if ((s16)h + 0xC8 < k) {
            return 0;
        }
    }
    t = *(u16 *)(a + 0x32) - cy;
    if ((u16)(t + 0x3C) >= 0x51) {
        if (t < 0) {
            *(s16 *)(a + 0x156) = -0x3C;
        } else {
            *(s16 *)(a + 0x156) = 0x14;
        }
    } else {
        *(s16 *)(a + 0x156) = t;
    }
    D_1F800084 = c;
    {
        u16 w = *(u16 *)(b + 0x80);
        D_1F800182_5650 = 0;
        *(s16 *)(a + 0x152) = w + 0x1E;
    }
    return 1;
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_ResolveTombaSelectedCompoundContact);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80111E18);

extern s32 D_1F80009C_c31a_cacf;
extern s32 D_1F800098;
s32 f_ResolveTombaInteractiveCylinderContact(u8 *a, u8 *b, u8 *c) {
    s16 dx, dz, dy, e, f, v;
    u16 h, bh, ah;
    u16 r;
    s32 ang, s, t, m;
    s32 o;

    o = 0;
    if (b[3] == 5) {
        o = -70;
    }
    dx = FU16(a, 0x2E) - (FU16(c, 0x2C) + o);
    dz = FU16(a, 0x36) - FU16(c, 0x34);
    r = func_80084080(dx * dx + dz * dz);
    if (r > F16(a, 0x80) + F16(b, 0x80)) {
        return 0;
    }
    dy = FU16(a, 0x32) - FU16(c, 0x30);
    ah = FU16(a, 0x84); bh = FU16(b, 0x84); h = ah + bh;
    if ((u16)(dy + h) > F16(a, 0x86) + F16(b, 0x86)) {
        return 0;
    }
    if (dy < 0) {
        dy = -dy;
        e = h;
        f = -h;
    } else {
        f = e = (FU16(b, 0x86) - bh) + (FU16(a, 0x86) - ah);
    }
    ang = func_80085690(-dz, dx);
    s = F16(a, 0x80) + F16(b, 0x80) - (s16)r;
    D_1F80009C_c31a_cacf = ang;
    if (s < e - dy || s < 3) {
        m = (func_80083F50(ang) * (F16(a, 0x80) + F16(b, 0x80))) >> 12;
        t = func_80083E80(D_1F80009C_c31a_cacf) * (F16(a, 0x80) + F16(b, 0x80));
        F16(a, 0x2E) = m + (FU16(c, 0x2C) + o);
        MEMBER_AT(s16, a, 0x36) = FU16(c, 0x34) - (t >> 12);
        a[0x60] = 1;
        a[0x5F] = func_80077768((s16)D_1F80009C_c31a_cacf, F16(a, 0x140), 1) + 2;
        if (func_80077768(F16(a, 0x56), (s16)D_1F80009C_c31a_cacf, 0) != 0) {
            if (b[0x5F] == 1) {
                if (a[4] == 1 && a[5] != 0x13) {
                    s32 d = D_1F80009C_c31a_cacf;
                    a[5] = 0x13;
                    a[6] = 0;
                    a[7] = 0;
                    a[0x2B] = d >> 4;
                }
            } else if (a[0x165] != 0) {
                if (D_1F800098 != 1) {
                    goto ret1;
                }
                if (F16(a, 0x44) < 0) {
                    dx = -F16(a, 0x44);
                } else {
                    dx = F16(a, 0x44);
                }
                if (dx <= 0x1A00) {
                    goto ret1;
                }
                if (a[4] != 1) {
                    goto ret1;
                }
                if (a[5] != 0x13) {
                    s32 d2 = D_1F80009C_c31a_cacf;
                    a[5] = 0x13;
                    a[6] = 0;
                    a[7] = 0;
                    a[0x2B] = d2 >> 4;
                    D_1F80009C_c31a_cacf = (D_1F80009C_c31a_cacf - 0x400) & 0xFFF;
                    if (D_1F80009C_c31a_cacf < 0x800) {
                        b[0x2B] = 2;
                    } else {
                        b[0x2B] = 3;
                    }
                }
            }
        }
    ret1:
        return 1;
    }
    if (a[0x145] & 1) {
        return 0;
    }
    a[0x29] = 1;
    M2C_FIELD(a, s32 *, 0x30) = (M2C_FIELD(c, s32 *, 0x30) + f) << 16;
    F16(b, 0x44) = F16(a, 0x44);
    b[0x29] = 1;
    if (F16(b, 0x62) != 0 && !(a[0] & 4) && a[0x145] == 2 && a[4] < 2) {
        if (func_80055844() != 0) {
            a[0x145] = 0;
            b[0x5E] = 2;
            a[0x148] = 0;
            F16(a, 0x50) = 0;
            a[5] = 0x17;
            a[6] = 0;
            a[7] = 0;
            goto done;
        }
        if (a[5] != 0x17 || F16(a, 0x4A) > 0x2C00) {
            a[0x145] = 0;
            b[0x5E] = 1;
            a[0x148] = 0;
            F16(a, 0x50) = 0;
            a[5] = 0x17;
            a[6] = 0;
            a[7] = 0;
            goto done;
        }
    }
    func_80022C78(a);
    b[0x5E] = 0;
done:
    return 2;
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_ResolveActiveColliderType0Contact);

extern u8 **D_1F800148;
extern u8 D_1F800150;
extern u8 **D_1F80013C;
extern u8 D_1F800144;
/* func_80111710, inlined */
static inline void inl_80111710(u8 *a)
{
    u8 **l = D_1F80013C;
    u8 *p;
    D_1F800182_5650 = D_1F800144;
    while (D_1F800182_5650 != 0) {
        p = *l;
        D_1F800182_5650--;
        l++;
        if ((p[0] & 1) && p[2] == 8) {
            func_8002423C(a, p);
        }
    }
}
void f_ResolveActorAgainstA00CollisionLists(u8 *a) {
    u8 **l = D_1F800148;
    u8 *p;
    s32 r;

    D_1F800182_5650 = D_1F800150;
    while (D_1F800182_5650 != 0) {
        p = *l;
        D_1F800182_5650--;
        l++;
        if (p[0] & 1) {
            if (p[2] == 3) {
                func_8002423C(a, p);
            } else if (p[2] == 0) {
                switch (func_80023D48(a, p, *(s32 *)(p + 0xC8), 0)) {
                case 0:
                    if (*(u16 *)(p + 0x60) & 2) {
                        if (func_80023D48(a, p, *(s32 *)(p + 0xCC), 0) == 2) {
                            goto hit;
                        }
                    }
                    break;
                case 2:
                hit:
                    a[0x5F] = p[0x5E];
                    D_1F800182_5650 = 0;
                    break;
                default:
                    D_1F800182_5650 = 0;
                    break;
                }
            }
        }
    }
    inl_80111710(a);
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_ResolveA00ActorPairContacts);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_ResolveA00PlatformPairContacts);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_ResolveTombaQuestAndSpecialContacts);

typedef struct { u8 pad[0xC0]; u8 *parts[1]; } PartsOwner;
extern u8 *D_1F800184_6cc7;
extern s16 D_1F80018E;
/* func_80114F94, inlined */
static inline void inl_80114F94(u8 *a, u8 *b) {
    b[0x29] = 0;
    if (a[0x16B] != 0) {
        if (D_1F800184_6cc7 == b) {
            f_ResolveTombaSelectedCompoundContact(a, b, M2C_FIELD(b, u8 **, 0xC4));
        }
        return;
    }
    switch (func_80111E18(a, b, M2C_FIELD(b, u8 **, 0xC8))) {
    case 2:
        b[0x29] = 1;
        if (D_1F80018E != 0) {
            D_1F80018E = 0x10;
        }
        break;
    case 0:
        if ((M2C_FIELD(b, u16 *, 0x60) & 2) && func_80111E18(a, b, M2C_FIELD(b, u8 **, 0xCC)) == 2) {
            b[0x29] = 0x81;
            if (D_1F80018E != 0) {
                D_1F80018E = 0x20;
            }
        }
        break;
    }
}
/* func_80114664, inlined */
static inline void inl_80114664(u8 *a, u8 *b) {
    b[0x29] = 0;
    switch (f_ResolveTombaBoxPartContact(a, b, M2C_FIELD(b, u8 **, 0xC4), 1)) {
    case 0:
        break;
    case 2:
        goto hit;
    }
    switch (f_ResolveTombaBoxPartContact(a, b, M2C_FIELD(b, u8 **, 0xC0), 0)) {
    case 0:
        break;
    case 2:
    hit:
        b[0x29] = 1;
        break;
    }
}
/* f_ResolveTombaMultipartActorContact, inlined */
static inline void inl_ResolveTombaMultipartActorContact(u8 *a, PartsOwner *b) {
    s32 i;

    for (i = 2; i < b->pad[8] - 1; i++) {
        if (F16(b->parts[i], 0x16) == 2) {
            return;
        }
        if (i == b->pad[8] - 2 && F16(b->parts[b->pad[8] - 1], 0x16) == 0) {
            if (func_80022E04(a, b, b->parts[i]) != 0) {
                b->pad[0x29] = 1;
                b->pad[0x47] = func_80077768((s16)D_1F80009C, F16(a, 0x56), 1);
                return;
            }
        } else if (func_8001F650(a, b, b->parts[i]) != 0) {
            return;
        }
    }
}
void f_ResolveTombaActorContacts(u8 *a) {
    u8 **p;
    u8 *b;

    p = D_1F800148;
    D_1F800182_5650 = D_1F800150;
    while (D_1F800182_5650 != 0) {
        b = *p;
        D_1F800182_5650--;
        p++;
        if (b[0] & 1) {
            switch (b[2]) {
            case 0:
                inl_80114F94(a, b);
                break;
            case 1:
                func_8001F650(a, b, M2C_FIELD(b, u8 **, 0xC0));
                break;
            case 2:
            case 4:
            case 7:
                func_8010EC58(a, b, M2C_FIELD(b, u8 **, 0xC0));
                break;
            case 3:
                f_ResolveTombaInteractiveCylinderContact(a, b, M2C_FIELD(b, u8 **, 0xC0));
                break;
            case 5:
                do {
                    do {
                        inl_80114664(a, b);
                    } while (0);
                } while (0);
                break;
            case 6:
                f_ResolveTombaOnNetBridge(a, b);
                break;
            case 8:
                f_ResolveTombaOrientedWallContact(a, b, M2C_FIELD(b, u8 **, 0xC0));
                break;
            case 14:
            case 15:
                func_8001FAE0(a, b);
                break;
            case 16:
                inl_ResolveTombaMultipartActorContact(a, (PartsOwner *)b);
                break;
            case 17:
                func_8010F034(a, b, M2C_FIELD(b, u8 **, 0xC4));
                break;
            case 12:
                func_80020868(a, b);
                break;
            case 18:
                func_8002311C(a, b);
                break;
            case 24:
            case 44:
                func_80020B08(a, b);
                break;
            case 101:
                func_8010DCB8(a, b);
                break;
            case 9:
            case 50:
            case 75:
                func_8001FC50(a, b);
                break;
            }
        }
    }
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_ResolveActiveColliderStaticContacts);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_ResolveActiveColliderActorContacts);

extern u8 D_1F800183;
extern u8 **D_1F800154;
extern u8 D_1F80015C;
/* f_ResolveA00ActiveActorCollisionCandidates, inlined */
static inline void inl_ResolveA00ActiveActorCollisionCandidates(void) {
    u8 **list = D_1F800154;
    u8 *a;

    for (D_1F800183 = D_1F80015C; D_1F800183 != 0;) {
        a = *list++;
        D_1F800183--;
        if (!(a[0] & 2)) {
            switch (a[2]) {
            case 1:
                if (a[3] != 1) {
                    break;
                }
            case 0:
            case 4:
            case 7:
                f_ResolveActorAgainstA00CollisionLists(a);
                break;
            }
        }
    }
}
void f_UpdateA00CollisionInteractions(void) {
    u8 *g = D_800E7E80;

    func_8002288C(g);
    switch (g[0]) {
    default:
    case 1:
    case 3:
    case 4:
    case 5:
    case 7:
        do {
            func_80022760(g);
        } while (0);
        f_ResolveTombaQuestAndSpecialContacts(g);
    case 2:
        if (*(u32 *)(g + 0x158) < 2) {
            f_ResolveTombaActorContacts(g);
        }
    case 0:
    case 6:
        break;
    }
    func_80022554();
    f_ResolveActiveColliderStaticContacts();
    f_ResolveActiveColliderActorContacts();
    inl_ResolveA00ActiveActorCollisionCandidates();
    f_ResolveA00ActorPairContacts();
    f_ResolveA00PlatformPairContacts();
    f_EnforceA00TombaBoundsAndInteriorExit(g);
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_FindTombaSupportActor);

extern s8 D_1F80027B[];
void func_801140D0(void *arg0) {
    if ((M2C_FIELD(arg0, u8 *, 0x181) == 0) && ((M2C_FIELD(arg0, u8 *, 0x146) != 4) || (*((u8 *)D_1F80027B) == 0))) {
        M2C_FIELD(arg0, s16 *, 0x6A) = 0;
        if (M2C_FIELD(arg0, u8 *, 5) == 6) {
            M2C_FIELD(arg0, u8 *, 5) = 0x32U;
            M2C_FIELD(arg0, u8 *, 0x149) = (u8) ((M2C_FIELD(arg0, u8 *, 0x149) & 1) | 2);
        } else {
            M2C_FIELD(arg0, u8 *, 5) = 0x1DU;
            M2C_FIELD(arg0, s8 *, 6) = 0;
        }
        M2C_FIELD(arg0, s8 *, 4) = 1;
        M2C_FIELD(arg0, s8 *, 7) = 0;
        if (M2C_FIELD(arg0, u8 *, 0x144) == 1) {
            M2C_FIELD(arg0, u8 *, 0x144) = 0U;
        }
    }
}

extern u8 D_800BF818;
extern u8 D_8014A258[];
extern u8 *D_1F800080_ddd3;
void func_8011415C(u8 *a, u8 *b) {
    s16 t;

    if (func_80024BD8(a, b, M2C_FIELD(b, u8 **, 0xC0)) != 0) {
        b[0x29] = 1;
        t = M2C_FIELD(b, s16 *, 0x80) + M2C_FIELD(a, s16 *, 0x80);
        a[0x164] = 1;
        a[0x15C] = 0;
        D_1F800080_ddd3 = b;
        D_1F800182_5650 = 0;
        M2C_FIELD(a, s16 *, 0x152) = t - 0xC;
    }
}

extern u8 *D_800F2738;
extern s16 D_1F80009C_c31a;
void func_801141C8(u8 *a) {
    u8 *p;
    s32 r;

    for (p = D_800F2738; p != NULL; p = M2C_FIELD(p, u8 **, 0x24)) {
        if ((p[0] & 1) && p[0x2B] == 0) {
            if (func_80022F04(p, a) != 0) {
                if (func_80077768(0, D_1F80009C_c31a, 0) != 0) {
                    a[0x2B] = 4;
                } else {
                    a[0x2B] = 2;
                }
                func_8001E860(p, a, 0, 0);
                r = 1;
            } else {
                r = 0;
            }
            if (r != 0) {
                break;
            }
        }
    }
}

void func_80114290(u8 *a, u8 *b) {
    if (func_80111A00(a, b, M2C_FIELD(b, u8 **, 0xC8)) != 0) {
        D_1F800080_ddd3 = b;
        a[0x15C] = 0;
        a[0x164] = 1;
        b[0x29] = 1;
    } else if ((M2C_FIELD(b, u16 *, 0x60) & 2) && func_80111A00(a, b, M2C_FIELD(b, u8 **, 0xCC)) != 0) {
        D_1F800080_ddd3 = b;
        a[0x15C] = 1;
        a[0x164] = 1;
        b[0x29] = 0x81;
    }
}

void func_80114320(u8 *a, u8 *b) {
    if (func_80024338(a, b) != 0) {
        if (b[3] == 1) {
            M2C_FIELD(a, s16 *, 0x156) = -0x58;
        } else {
            M2C_FIELD(a, s16 *, 0x156) = -0x1E;
        }
        M2C_FIELD(a, s16 *, 0x152) = M2C_FIELD(b, u16 *, 0x80) + M2C_FIELD(a, u16 *, 0x80) - 12;
        b[0x5E] = 1;
        a[0x164] = 1;
        D_1F800080_ddd3 = b;
        D_1F800182_5650 = 0;
    }
}

typedef struct { u8 pad[0x60]; s32 unk60; s32 unk64; } AreaStateF58;
extern s8 *D_800ECF58[];
extern u8 D_8014C0BC[];
extern u8 D_8014DE54[];
void func_801143A4(u8 *a, u8 *b) {
    if (func_80022F04(a, b) != 0) {
        b[0x2B] = 1;
        b[0x46] = M2C_FIELD(a, u16 *, 0x56) >> 4;
        func_8001E860(a, b, 0, 0);
        D_1F800182_5650 = 0;
    }
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80114408);

s32 func_80114528(s32 arg0, s32 arg1) {
    return func_8010EC58(arg0, arg1, M2C_FIELD(arg1, s32 *, 0xC0));
}

void f_ResolveTombaMultipartActorContact(u8 *a, PartsOwner *b) {
    s32 i;

    for (i = 2; i < b->pad[8] - 1; i++) {
        if (F16(b->parts[i], 0x16) == 2) {
            return;
        }
        if (i == b->pad[8] - 2 && F16(b->parts[b->pad[8] - 1], 0x16) == 0) {
            if (func_80022E04(a, b, b->parts[i]) != 0) {
                b->pad[0x29] = 1;
                b->pad[0x47] = func_80077768((s16)D_1F80009C, F16(a, 0x56), 1);
                return;
            }
        } else if (func_8001F650(a, b, b->parts[i]) != 0) {
            return;
        }
    }
}

s32 func_80114640(s32 arg0, s32 arg1) {
    return func_8010F034(arg0, arg1, M2C_FIELD(arg1, s32 *, 0xC4));
}

void func_80114664(u8 *a, u8 *b) {

    b[0x29] = 0;
    switch (f_ResolveTombaBoxPartContact(a, b, M2C_FIELD(b, u8 **, 0xC4), 1)) {
    case 0:
        break;
    case 2:
        goto hit;
    }
    switch (f_ResolveTombaBoxPartContact(a, b, M2C_FIELD(b, u8 **, 0xC0), 0)) {
    case 0:
        break;
    case 2:
    hit:
        b[0x29] = 1;
        break;
    }
}

void func_801146E0(u8 *a, u8 *b) {
    s32 i;

    for (i = 2; i < b[8]; i++) {
        if (F16(((u8 **)(b + 0xC0))[i], 0x16) == 2) {
            return;
        }
        if (func_80022E04(a, b, ((u8 **)(b + 0xC0))[i]) != 0) {
            func_8001E860(a, b, ((u8 **)(b + 0xC0))[i], 0);
            func_80074590(0x8D, 0, 0);
            D_1F800182_5650 = 0;
            return;
        }
    }
}

extern s8 D_1F800182[];
void func_8011479C(s32 arg0, M2C_UNK arg1) {
    if (func_80022F04() != 0) {
        func_8001E860(arg0, arg1, 0, 0);
        *((s8 *)D_1F800182) = 0;
    }
}

void func_801147EC(u8 *a, u8 *b) {
    u16 t, u;

    if (func_80024BD8(a, b, M2C_FIELD(b, u8 **, 0xC4)) != 0 && a[0x147] == 0) {
        if (M2C_FIELD(M2C_FIELD(b, u8 **, 0xC4), s32 *, 0x2C) - M2C_FIELD(b, s16 *, 0x80) >= M2C_FIELD(a, s16 *, 0x2E)) {
            M2C_FIELD(a, s16 *, 0x156) = 20;
            t = M2C_FIELD(b, u16 *, 0x80);
            u = M2C_FIELD(a, u16 *, 0x80);
            a[0x164] = 2;
            D_1F800080_ddd3 = b;
            D_1F800182_5650 = 0;
            M2C_FIELD(a, s16 *, 0x152) = -(t + u);
        }
    }
}

extern void *D_1F800080;
void func_80114888(u8 *a, u8 *b)
{
    if (func_8011040C(a, b, *(void **)(b + 0xC0)) != 0) {
        a[0x164] = 3;
        D_1F800080 = b;
        D_1F800182_5650 = 0;
    }
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_801148D8);

extern void *D_1F800080;
extern u8 D_1F800182_5650;
void func_8011499C(u8 *a, u8 *b)
{
    if (func_80024BD8(a, b, *(void **)(b + 0xC4)) != 0) {
        b[0x29] = 1;
        a[0x164] = 3;
        D_1F800080 = b;
        D_1F800182_5650 = 0;
    }
}

void f_ResolveActorPairMultipartContact(u8 *a, PartsOwner *b) {
    s32 i;

    for (i = 2; i < b->pad[8] - 1; i++) {
        if (F16(b->parts[i], 0x16) == 2) {
            return;
        }
        if (i == b->pad[8] - 2 && F16(b->parts[b->pad[8] - 1], 0x16) == 0) {
            if (func_80023D48(a, b, b->parts[i], a[2] == 3) != 0) {
                b->pad[0x29] = 1;
                b->pad[0x47] = func_80077768((s16)D_1F80009C, F16(a, 0x56), 1);
                return;
            }
        } else if (func_80023870(a, b, b->parts[i]) != 0) {
            return;
        }
    }
}

void func_80114AF4(u8 *a, u8 *b) {
    s32 r = func_80023D48(a, b, M2C_FIELD(b, u8 **, 0xC8), 0);

    if (r != 0) {
        if (r == 2) {
            a[0x5F] = b[0x5E];
        }
        D_1F800182_5650 = 0;
    } else if (M2C_FIELD(b, u16 *, 0x60) & 2) {
        if (func_80023D48(a, b, M2C_FIELD(b, u8 **, 0xCC), 0) == 2) {
            a[0x5F] = b[0x5E];
            D_1F800182_5650 = 0;
        }
    }
}

extern u8 *D_8014C804_6a3a;
extern u16 D_8014C800;
void func_80114B8C(u8 *a, u8 *b) {
    if (func_80023870(a, b, M2C_FIELD(b, u8 **, 0xC0)) != 0) {
        D_1F800182_5650 = 0;
    }
}

void func_80114BBC(u8 *a, u8 *b) {
    s32 k = 3;

    if (f_ResolveActorPairType3Contact(a, b, M2C_FIELD(b, u8 **, 0xC0), a[2] == k) != 0) {
        if (a[2] == k && b[0x5F] == 1) {
            a[0] = k;
            a[0x2B] = D_1F80009C >> 4;
            a[4] = 2;
            a[5] = 0;
            a[6] = 0;
        }
        D_1F800182_5650 = 0;
    }
}

void func_80114C5C(u8 *a, s32 b) {
    if (b == 0) {
        D_800BF871 = 0;
        return;
    }
    if (a[0x2A] >= 0x16 && a[0x2A] < 0x19) {
        D_800BF871 = 8;
        return;
    }
    if (a[0x2A] == 0x22) {
        if (M2C_FIELD(a, s16 *, 0x2E) >= 0x4753) {
            D_800BF871 = 3;
            return;
        }
        D_800BF871 = 2;
    }
}

extern s8 D_800BF9E5;
void func_80114CD0(u8 *a) {
    AreaState808_E *g = &D_800BF808_9a69;

    if (g->unkE != 0 && g->unkF == 2 && M2C_FIELD(a, s16 *, 0x32) < -0xE74 && M2C_FIELD(a, s16 *, 0x36) < 0x1451) {
        D_1F800137 = 2;
        g->unk7 = 2;
        g->unk31 = 1;
        g->unk32 = 0x100;
        D_1F800236 = 1;
    }
}

void func_80114D48(u8 *a) {
    u8 *g = D_800BF808_1760;
    u16 lim = M2C_FIELD(g, u16 *, 0xA);

    switch (g[0xF]) {
    case 2:
        if (D_800E7FEB != 8) {
            break;
        }
        if (M2C_FIELD(a, s16 *, 0x36) < 0x1A05) {
            M2C_FIELD(a, s16 *, 0x36) = 0x1A04;
        }
    case 0:
    case 1:
        if (!(a[0x145] & 1) && M2C_FIELD(a, s16 *, 0x32) >= (s16)lim - M2C_FIELD(a, s16 *, 0x62)) {
            M2C_FIELD(a, s16 *, 0x32) = lim - M2C_FIELD(a, u16 *, 0x62);
            func_80022C78(a);
        }
        break;
    }
}

s32 func_80114DF4(u8 *a, u8 *b) {
    if (func_80022F04(a, b) != 0) {
        if (func_80077768(0, D_1F80009C_c31a, 0) != 0) {
            b[0x2B] = 4;
        } else {
            b[0x2B] = 2;
        }
        func_8001E860(a, b, 0, 0);
        return 1;
    }
    return 0;
}

void func_80114E74(u8 *a, u8 *b) {
    if (a[0x164] != 5 || a[0x147] != b[0x47]) {
        if (func_80022F04(a, b) != 0) {
            b[0] = 2;
            b[4] = 2;
            b[5] = 0;
            b[6] = 0;
        }
    }
}

void func_80114ED4(u8 *a, u8 *b) {
    s32 i;

    for (i = 0; i < 2; i++) {
        if (func_80023D48(a, b, ((u8 **)(b + 0xC0))[i], 0) != 0) {
            D_1F800182_5650 = 0;
            return;
        }
    }
}

extern s8 D_1F800182[];
void func_80114F54(s32 arg0, void *arg1) {
    if (func_80022F04() != 0) {
        M2C_FIELD(arg1, s8 *, 0) = 2;
        M2C_FIELD(arg1, s8 *, 4) = 2;
        M2C_FIELD(arg1, s8 *, 5) = 0;
        *((s8 *)D_1F800182) = 0;
    }
}

void func_80114F94(u8 *a, u8 *b) {
    b[0x29] = 0;
    if (a[0x16B] != 0) {
        if (D_1F800184_6cc7 == b) {
            f_ResolveTombaSelectedCompoundContact(a, b, M2C_FIELD(b, u8 **, 0xC4));
        }
        return;
    }
    switch (func_80111E18(a, b, M2C_FIELD(b, u8 **, 0xC8))) {
    case 2:
        b[0x29] = 1;
        if (D_1F80018E != 0) {
            D_1F80018E = 0x10;
        }
        break;
    case 0:
        if ((M2C_FIELD(b, u16 *, 0x60) & 2) && func_80111E18(a, b, M2C_FIELD(b, u8 **, 0xCC)) == 2) {
            b[0x29] = 0x81;
            if (D_1F80018E != 0) {
                D_1F80018E = 0x20;
            }
        }
        break;
    }
}

s32 func_80115084(s32 arg0, s32 arg1) {
    return func_8001F650(arg0, arg1, M2C_FIELD(arg1, s32 *, 0xC0));
}

s32 func_801150A8(s32 arg0, s32 arg1) {
    return f_ResolveTombaInteractiveCylinderContact(arg0, arg1, M2C_FIELD(arg1, s32 *, 0xC0));
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_801150CC);

void func_801151F4(u8 *a, u8 *b)
{
    s32 v;

    if (func_8002313C(a, b, *(void **)(b + 0xC0)) != 0) {
        func_8001E860(a, b, *(void **)(b + 0xC0), 0x400);
        v = D_1F80009C;
        b[0x2B] = 1;
        b[0x46] = v >> 4;
        if (a[0x5E] != 0) {
            b[0x2B] = 0x81;
        }
        D_1F800182_5650 = 0;
    }
}

void f_ResolveA00ActiveActorCollisionCandidates(void) {
    u8 **list = D_1F800154;
    u8 *a;

    for (D_1F800183 = D_1F80015C; D_1F800183 != 0;) {
        a = *list++;
        D_1F800183--;
        if (!(a[0] & 2)) {
            switch (a[2]) {
            case 1:
                if (a[3] != 1) {
                    break;
                }
            case 0:
            case 4:
            case 7:
                f_ResolveActorAgainstA00CollisionLists(a);
                break;
            }
        }
    }
}

void func_8011534C(u8 *a)
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

extern u32 *D_800ED8C8_065b;
typedef struct {
    u32 tag;
    u32 rgbc;
    u32 xy;
    u16 uv;
    u16 clut;
} T2Sprt16;
extern T2Sprt16 *D_800BF544_e6cf;
void func_80115598(u8 *a)
{
    s32 w2 = a[0x10] * 2;
    s32 size = w2 * a[0x11];
    u16 sx = U(a, 0x28);
    u16 sy = U(a, 0x2A);
    s16 x0 = sx - 160;
    s16 y0 = sy - 120;
    s16 row, col, x, y, c;
    T2Sprt16 *p, *start, *last, *q;
    u16 t;
    u16 k;
    s32 yy;

    last = NULL;

    row = y0 >> 4;
    if (row < 0) {
        do {
            row += a[0x11];
        } while (row < 0);
    }
    while (row >= a[0x11]) {
        row -= a[0x11];
    }
    sx = -sx + 0x98;
    sy = -sy + 0x70;
    row *= w2;
    col = x0 >> 4;
    if (col < 0) {
        do {
            col += a[0x10];
        } while (col < 0);
    }
    while (col >= a[0x10]) {
        col -= a[0x10];
    }
    col <<= 1;
    p = D_800BF544_e6cf;
    start = p;
    for (y = y0; y < y0 + 0x100; y += 16) {
        c = col;
        yy = (y & 0xFFF0) + (s16)sy;
        for (x = x0; x < x0 + 0x160;) {
            t = *(u16 *)(*(u8 **)(a + 0x14) + (row + c));
            c += 2;
            last = p;
            if (c >= w2) {
                c = 0;
            }
            p->xy = (((x & 0xFFF0) + (s16)sx) & 0xFFFF) | (yy << 16);
            p->uv = ((t << 4) & 0xF0) | (((t & 0xF0) + 8) << 8);
            k = U(a, 6);
            p->rgbc = 0x7D808080;
            ((u8 *)p)[3] = 3;
            ((u8 *)p)[7] = 0x7C;
            p->clut = k + ((t & 0xF00) >> 2);
            p++;
            x += 16;
            last->tag = (u32)p | 0x03000000;
        }
        row += w2;
        if (row >= size) {
            row -= size;
        }
    }
    last->tag = (last->tag & 0xFF000000) | D_800ED8C8_065b[0x7FF];
    func_80083DE0(p, 0, 0, U(a, 4), 0);
    p->tag = (u32)start | 0x02000000;
    q = p;
    p = (T2Sprt16 *)((u32 *)p + 3);
    *(T2Sprt16 **)&D_800ED8C8_065b[0x7FF] = q;
    D_800BF544_e6cf = p;
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_801158E0);

typedef struct { s16 x, y, w, h; } ClutRect;
typedef struct {
    u8 *ptr;
    u8 *clut;
    s16 x;
    s16 y;
} ClutCycle;

extern ClutCycle D_80147D84[];
extern s8 D_8014C4F0[];
extern u8 D_800BF873;
void func_80115B88(s32 arg0) {
    ClutRect r;
    s32 i;
    ClutCycle *e;
    u8 *data;

    if (arg0 == 0) {
        s8 *p;
        i = 11;
        p = &D_8014C4F0[i];
        do {
            *p-- = 0;
        } while (--i >= 0);
        return;
    }
    e = D_80147D84;
    for (i = 0; i < 12; i++, e++) {
        if (--D_8014C4F0[i] <= 0) {
            if (e->ptr[0] == 0xFF) {
                e->ptr -= e->ptr[1];
            }
            data = e->clut + e->ptr[0] * 32;
            D_8014C4F0[i] = e->ptr[1];
            r.x = e->x;
            r.y = e->y;
            r.w = 16;
            r.h = 1;
            func_80081218(&r, data);
            e->ptr += 2;
        }
    }
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_SpawnFishermensTownActorsFromPlacementTable);

#define GS1(o) (g1[o])
#define GS2(o) (g2[o])
#define GS3(o) (g3[o])
#define GS4(o) (g4[o])
#define W_d1fb(p, o) (*(s32 *)((u8 *)(p) + (o)))
extern u8 D_1F800230;
extern u8 D_1F80019A;
extern u8 D_800BF830;
extern u8 D_800BF80F;
void func_80116094(u8 *a) {
    u8 *t = D_800E7E80;
    u8 *s = D_800BF808_1760;
    u8 *g1;
    u8 *g2;
    u8 *g3;
    u8 *g4;

    if (s[0xE] == 0) {
        g1 = (u8 *)&D_800BF870;
        if (GS1(0x16F) == 0 && (GS1(0x162) == 0 || GS1(0x162) == 0xFF)) {
            if (func_8005308C() != 0 && s[0x28] == 0xFF) {
                if (t[0x164] == 0) {
                    t[4] = 4;
                    t[5] = 0x21;
                    t[6] = 0;
                    func_80054D14(t, 2, 6);
                }
                func_80042354(1, 3);
                GS1(0x16F) = 0x41;
                func_80070724(0xE, 4, 0x19);
            }
        }
        g2 = (u8 *)&D_800BF870;
        if (GS2(0x16F) & 0x40) {
            if (D_1F800137 == 0) {
                GS2(0x16F) &= 0xBF;
            }
            D_1F800230 = 1;
        }
        g3 = (u8 *)&D_800BF870;
        if (GS3(0x85) == 0 && GS3(0x179) == 0 && t[0x2A] == 0x1F && H_f12c(t, 0x36) < 0x1ACD && H_f12c(t, 0x32) < -0xF9F) {
            if (func_8005308C() != 0 && D_800BF830 == 0xFF) {
                func_80042354(1, 2);
                GS3(0x179) = 1;
                func_80070724(0, 5, 9);
            } else {
                H_f12c(t, 0x36) = 0x1ACC;
            }
        }
        g4 = (u8 *)&D_800BF870;
        if (GS4(0x46) == 0 && D_1F80019A != 1 && GS4(0x2C) >= 4 && D_800BF80F == 0) {
            func_80040B48(2);
        }
    } else if (s[0xF] == 0) {
        if (H_f12c(t, 0x36) >= 0x140B) {
            W_d1fb(t, 0x34) = 0x140A0000;
            D_1F800164_d75f = H_f12c(t, 0x36);
        }
    } else if (s[0xF] == 1) {
        if (H_f12c(t, 0x36) < 0x226) {
            W_d1fb(t, 0x34) = 0x2260000;
            D_1F800164_d75f = H_f12c(t, 0x36);
        }
    }
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateFishermensTownAmbientAudio);

void func_801167AC(u8 *a) {
    u8 *g;

    switch (a[4]) {
    case 0:
        a[4] = 1;
        f_SpawnFishermensTownActorsFromPlacementTable(a, 0);
        g = D_800BF808_1760;
        if (g[0xE] != 0 && g[0xF] == 2) {
            a[3] = g[0xF] + 1;
            f_SpawnFishermensTownActorsFromPlacementTable(a, 3);
            a[5] = 3;
        }
        func_8004D8D8(0, 0);
        func_80115B88(0);
        func_8013EDD0();
        break;
    case 1:
        if (func_80026AD0(a) != 0) {
            f_SpawnFishermensTownActorsFromPlacementTable(a, a[3]);
        }
        func_80116094(a);
        func_80026A68(a);
        func_80115B88(1);
        break;
    case 2:
        break;
    case 3:
        func_8007ADD0(a);
        break;
    }
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", block);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateCrabBasketRewardDrop);

typedef struct { s16 x, y, z; } SVec3T;
extern SVec3T D_1F8000C0_4e9b;
extern u8 D_800BF9E5_1228;
void func_80116E3C(u8 *a) {
    s32 n;
    u8 *g;

    switch (a[0x5E]) {
    case 0:
        block(a);
        break;
    case 1:
        f_UpdateCrabBasketRewardDrop(a);
        break;
    case 2:
        *(s16 *)(a + 0x54) = 0x800;
        g = D_800E7E80;
        n = 3;
        if (g[0x145] == 0 || g[0x146] != 0) {
            D_1F8000C0_4e9b.x = 6;
            D_1F8000C0_4e9b.y = 0xA;
            D_1F8000C0_4e9b.z = 0x1C;
        } else {
            n = 4;
            D_1F8000C0_4e9b.x = 0x3C;
            D_1F8000C0_4e9b.y = 8;
            D_1F8000C0_4e9b.z = 0x48;
        }
        if (D_800BF9E5_1228 == 7) {
            a[4] = 3;
            break;
        }
        func_80051614(a, &D_1F8000C0_4e9b, n, 0);
        a[1] = 1;
        func_80077EFC(a);
        break;
    }
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_HandleKainenHouseQuestItemActor);

/* func_80117460, inlined */
static inline void inl_80117460(u8 *a) {
    if (func_80051B70(a, 1, 2) == 0) {
        M2C_FIELD(a, s16 *, 0x80) = 0x28;
        M2C_FIELD(a, s16 *, 0x82) = 0x50;
        M2C_FIELD(a, s16 *, 0x84) = 0x4B;
        M2C_FIELD(a, s16 *, 0x86) = 0x73;
        M2C_FIELD(a, s16 *, 0x54) = 0;
        M2C_FIELD(a, s16 *, 0x56) = 0;
        M2C_FIELD(a, s16 *, 0x58) = 0;
        a[0x29] = 0;
        if (*(u8 *)&D_800BF9E5 == 4) {
            a[0x5E] = 1;
        }
    }
}
void func_80117228(u8 *a) {
    switch (a[4]) {
    case 0:
        switch (a[3]) {
        case 0:
            func_8004BEF4(a);
            break;
        case 1:
            inl_80117460(a);
            break;
        }
        a[4]++;
        break;
    case 1:
        switch (a[3]) {
        case 0:
            if (a[0x5E] == 0) {
                f_HandleKainenHouseQuestItemActor(a);
            }
            break;
        case 1:
            func_80116E3C(a);
            break;
        }
        break;
    case 2:
        switch (a[3]) {
        case 0:
            break;
        case 1:
            if (a[5] == 0 && func_80040C00(6) >= 0) {
                func_80040B48(7);
                func_8004D4C4(0x29, 1);
                func_8004B0D8(a);
                a[0x5E] = 2;
                a[4] = 1;
                a[5] = 0;
                a[6] = 0;
                D_800BF9E5 = 6;
            }
            break;
        }
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

void f_HandleBeachQuestPickup();
void f_HandleTownQuestRewardVisualActor();
void func_80117228();
void f_HandleFeedChicksSceneActor();
void f_HandleTownCreatureActor();
u8 *f_SpawnCrabBasketRewardActor(s32 a, s32 b) {
    u8 *p = func_80072DDC(a, 129, 5, 1);

    if (p == NULL) {
        return NULL;
    }
    p[0x3] = 1;
    p[0x5E] = b;
    M2C_FIELD(p, void **, 0x1C) = func_80117228;
    return p;
}

void func_80117460(u8 *a) {
    if (func_80051B70(a, 1, 2) == 0) {
        M2C_FIELD(a, s16 *, 0x80) = 0x28;
        M2C_FIELD(a, s16 *, 0x82) = 0x50;
        M2C_FIELD(a, s16 *, 0x84) = 0x4B;
        M2C_FIELD(a, s16 *, 0x86) = 0x73;
        M2C_FIELD(a, s16 *, 0x54) = 0;
        M2C_FIELD(a, s16 *, 0x56) = 0;
        M2C_FIELD(a, s16 *, 0x58) = 0;
        a[0x29] = 0;
        if (*(u8 *)&D_800BF9E5 == 4) {
            a[0x5E] = 1;
        }
    }
}

void func_801174D8(u8 *a) {
    s32 n;
    u8 *g;

    M2C_FIELD(a, s16 *, 0x54) = 0x800;
    g = D_800E7E80;
    n = 3;
    if (g[0x145] == 0 || g[0x146] != 0) {
        D_1F8000C0_4e9b.x = 6;
        D_1F8000C0_4e9b.y = 0xA;
        D_1F8000C0_4e9b.z = 0x1C;
    } else {
        n = 4;
        D_1F8000C0_4e9b.x = 0x3C;
        D_1F8000C0_4e9b.y = 8;
        D_1F8000C0_4e9b.z = 0x48;
    }
    if (D_800BF9E5_1228 == 7) {
        a[4] = 3;
        return;
    }
    func_80051614(a, &D_1F8000C0_4e9b, n, 0);
    a[1] = 1;
    func_80077EFC(a);
}

void func_801175A8(void *arg0) {
    if ((M2C_FIELD(arg0, u8 *, 5) == 0) && (func_80040C00(6) >= 0)) {
        func_80040B48(7);
        func_8004D4C4(0x29, 1);
        func_8004B0D8(arg0);
        M2C_FIELD(arg0, s8 *, 0x5E) = 2;
        M2C_FIELD(arg0, s8 *, 4) = 1;
        M2C_FIELD(arg0, u8 *, 5) = 0U;
        M2C_FIELD(arg0, s8 *, 6) = 0;
        D_800BF9E5 = 6;
    }
}

void func_80117628(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x5E) == 0) {
        f_HandleKainenHouseQuestItemActor();
    }
}

#define FP(p, o) M2C_FIELD(p, u8 **, o)
extern s32 D_800ECF80;
extern u8 D_8014C808[];
extern u8 D_80148574[];
extern u8 D_1F800207_9c67;
/* func_80117D7C, inlined */
static inline void inl_80117D7C(u8 *a, u8 *p) {

    a[0xB] = 0x10;
    a[8] = 0xF8;
    a[0x47] = 0;
    M2C_FIELD(a, s16 *, 0x5A) = 0;
    a[0xD] = 0;
    M2C_FIELD(a, s32 *, 0x3C) = D_800ECF80;
    func_80077B38(a, D_8014C808, 1);
    M2C_FIELD(a, s32 *, 0x2C) = 0x13D20000;
    M2C_FIELD(a, s32 *, 0x30) = 0xF7E00000;
    M2C_FIELD(a, s32 *, 0x34) = 0x15AA0000;
    M2C_FIELD(a, s16 *, 0x80) = 0x3C;
    M2C_FIELD(a, s16 *, 0x82) = 0x78;
    M2C_FIELD(a, s16 *, 0x84) = 0x50;
    M2C_FIELD(a, s16 *, 0x86) = 0xA0;
    a[0] = 4;
    M2C_FIELD(p, s16 *, 6) = M2C_FIELD(a, s16 *, 0x2E);
    M2C_FIELD(p, s16 *, 8) = M2C_FIELD(a, s16 *, 0x32) - 0x1A4;
    M2C_FIELD(p, s16 *, 0xA) = M2C_FIELD(a, s16 *, 0x36);
    M2C_FIELD(p, s16 *, 0x16) = 0x1E;
    a[4]++;
    func_8004B354(a, 0);
}
/* func_80117E5C, inlined */
static inline void inl_80117E5C(u8 *a) {
    func_8004D4C4(0x3A, 1);
    func_8004B0D8(a);
    a[4] = 3;
}
/* func_80117E98, inlined */
static inline void inl_80117E98(u8 *a) {
    s16 *q = M2C_FIELD(a, s16 **, 0x10);
    s16 x, y, z;

    if (func_8007778C(a) != 0) {
        if (a[5] == 2) {
            x = D_1F800160_71b4;
            y = D_1F800162;
            z = D_1F800164_d75f;
            M2C_FIELD(a, s16 *, 0x2E) = x;
            M2C_FIELD(a, s16 *, 0x32) = y;
            M2C_FIELD(a, s16 *, 0x36) = z;
        } else {
            M2C_FIELD(a, s16 *, 0x2E) = q[0] - 0x20;
            M2C_FIELD(a, s16 *, 0x32) = q[1] + 0x50;
        }
        func_80077B5C(a);
        func_8004B374(a, 0);
    }
}
/* func_80117FAC, inlined */
static inline void inl_80117FAC(u8 *a) {
    s32 r;

    switch (a[5]) {
    case 0:
        func_8004D4F4(0x28, 1);
        func_8004ED94(0x2D, 0x42);
        func_8004B0D8(a);
        r = func_8004BD04(a, 0, 0);
        if (r != 0) {
            func_8004BEA8(0x28, r);
            func_80042354(1, 1);
            D_800BF870.pad1[0x16B] |= 1;
        }
        a[5]++;
        break;
    case 1:
        if (func_8005308C() != 0) {
            func_80040CDC(a, 0, D_80148574);
            a[0x70] = 2;
            a[5]++;
        }
        break;
    case 2:
        if (a[0x70] == 0xFF) {
            a[4] = 3;
        } else {
            func_80041098(a);
        }
        break;
    }
}
/* func_801180CC, inlined */
static inline void inl_801180CC(u8 *a) {
    u8 *p = FP(a, 0x10);

    if (D_1F800207_9c67 < 5 && func_8007778C(a) != 0) {
        if (a[5] == 2) {
            u16 x = D_1F800160_71b4;
            u16 y = D_1F800162;
            u16 z = D_1F800164_d75f;
            F16(a, 0x2E) = x;
            F16(a, 0x32) = y;
            F16(a, 0x36) = z;
        } else {
            F16(a, 0x2E) = FU16(p, 0) + ((F16(FP(a, 0xC0), 0x1A) * 9) >> 8);
            F16(a, 0x32) = FU16(p, 2) + ((F16(FP(a, 0xC0), 0x20) * 9) >> 8);
            F16(a, 0x58) = -FU16(p, 0xC);
        }
        func_800517F8(a);
        func_8004B374(a, 1);
    }
}
/* func_801181BC, inlined */
static inline void inl_801181BC(void *arg0, void *arg1) {
    if (M2C_FIELD(arg0, u8 *, 0x2B) == 2) {
        M2C_FIELD(arg1, s16 *, 0x14) = 0x2000;
        return;
    }
    M2C_FIELD(arg1, s16 *, 0x14) = -0x2000;
}
/* func_801181E0, inlined */
static inline void inl_801181E0(u8 *a, u8 *b) {
    if (a[0x2B] == 2) {
        if (M2C_FIELD(b, s16 *, 0xE) < 0x800) {
            M2C_FIELD(b, s16 *, 0xE) -= 0x1000;
        } else {
            M2C_FIELD(b, s16 *, 0xE) = -M2C_FIELD(b, s16 *, 0xE);
        }
        M2C_FIELD(b, s16 *, 0x14) = 0xC00;
    } else {
        if (M2C_FIELD(b, s16 *, 0xE) < -0x7FF) {
            M2C_FIELD(b, s16 *, 0xE) = -M2C_FIELD(b, s16 *, 0xE);
        } else {
            M2C_FIELD(b, s16 *, 0xE) += 0x1000;
        }
        M2C_FIELD(b, s16 *, 0x14) = -0xC00;
    }
}
void f_HandleRareFishOrBlueBucketPickup(u8 *a)
{
    u8 st = a[4];
    u8 *s = FP(a, 0x10);
    s32 r;
    s32 t;

    switch (st) {
    case 0:
        switch (a[3]) {
        case 0:
            inl_80117D7C(a, s);
            break;
        case 1:
            a[0] = 4;
            a[0x5E] = 0;
            if (func_80051B70(a, 1, 0) == 0) {
                M2C_FIELD(a, s32 *, 0x2C) = 0x28D20000;
                M2C_FIELD(a, s32 *, 0x30) = 0xF9E80000;
                M2C_FIELD(a, s32 *, 0x34) = 0x0F800000;
                M2C_FIELD(a, s16 *, 0x80) = 0x46;
                M2C_FIELD(a, s16 *, 0x82) = 0x8C;
                M2C_FIELD(a, s16 *, 0x84) = 0x8C;
                M2C_FIELD(a, s16 *, 0x86) = 0x8C;
                M2C_FIELD(s, s16 *, 6) = M2C_FIELD(a, s16 *, 0x2E);
                M2C_FIELD(s, s16 *, 8) = M2C_FIELD(a, s16 *, 0x32) - 0x190;
                M2C_FIELD(s, s16 *, 0xA) = M2C_FIELD(a, s16 *, 0x36);
                M2C_FIELD(s, s16 *, 0xC) = 0x52;
                a[4]++;
                func_8004B354(a, 1);
            }
            break;
        }
        break;
    case 1:
        switch (a[5]) {
        case 0:
            if (a[0x5E] == 1) {
                func_80074590(0x92, 0, 0);
                F16(s, 0x18) = 0x24;
                F16(s, 0x1A) = 0x580;
                F16(s, 0x14) = 0x2800;
                a[5]++;
            } else if (a[3] == 0) {
                if (F16(s, 0x14) == 0) {
                    if (--F16(s, 0x16) < 0) {
r = func_8009A450();
F16(s, 0x16) = (r & 3) * 0x1E + (s16)((func_8009A450() >> 11) + 0x1E);
                        F16(s, 0x14) = (-((func_8009A450() & 7) + 10)) << 8;
                    }
                }
            } else {
                a[0x2B] = 0;
                func_801141C8(a);
                if (a[0x2B] != 0) {
                    switch (a[3]) {
                    case 0:
                        inl_801181BC(a, s);
                        break;
                    case 1:
                        inl_801181E0(a, s);
                        break;
                    }
                }
            }
            break;
        case 1:
            if (F16(s, 0x18) == 0 || a[0x5E] == 0) {
                F16(s, 0x14) = -0x2800;
                F16(s, 0x1A) = 0x200;
                switch (a[3]) {
                case 0:
                    F16(a, 0x36) = 0x1590;
                    break;
                case 1:
                    F16(a, 0x36) = 0xF80;
                    break;
                }
                a[0] = 1;
                a[0x5E] = 2;
                a[5]++;
            } else {
                F16(s, 0x18)--;
            }
            break;
        }
        switch (a[3]) {
        case 0:
            inl_80117E98(a);
            break;
        case 1:
            inl_801180CC(a);
            break;
        }
        break;
    case 2:
        switch (a[3]) {
        case 0:
            inl_80117E5C(a);
            break;
        case 1:
            inl_80117FAC(a);
            break;
        }
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

void f_HandleRareFishOrBlueBucketPickup();
u8 *f_SpawnRareFishPickup(u8 *a) {
    GameState *g = &D_800BF870;
    u8 *p;

    if (g->pad1[0x27D] == 0) {
        if (g->pad1[0x14F] & 1) {
            return NULL;
        }
        p = func_8007A980(0, 5, 0);
        if (p != NULL) {
            M2C_FIELD(p, void **, 0x1C) = f_HandleRareFishOrBlueBucketPickup;
            M2C_FIELD(p, u8 **, 0x10) = a + 0x60;
            p[2] = 2;
            p[3] = 0;
            return p;
        }
    }
    return NULL;
}

void func_80117D7C(u8 *a) {
    u8 *p;

    a[0xB] = 0x10;
    a[8] = 0xF8;
    a[0x47] = 0;
    M2C_FIELD(a, s16 *, 0x5A) = 0;
    a[0xD] = 0;
    p = M2C_FIELD(a, u8 **, 0x10);
    M2C_FIELD(a, s32 *, 0x3C) = D_800ECF80;
    func_80077B38(a, D_8014C808, 1);
    M2C_FIELD(a, s32 *, 0x2C) = 0x13D20000;
    M2C_FIELD(a, s32 *, 0x30) = 0xF7E00000;
    M2C_FIELD(a, s32 *, 0x34) = 0x15AA0000;
    M2C_FIELD(a, s16 *, 0x80) = 0x3C;
    M2C_FIELD(a, s16 *, 0x82) = 0x78;
    M2C_FIELD(a, s16 *, 0x84) = 0x50;
    M2C_FIELD(a, s16 *, 0x86) = 0xA0;
    a[0] = 4;
    M2C_FIELD(p, s16 *, 6) = M2C_FIELD(a, s16 *, 0x2E);
    M2C_FIELD(p, s16 *, 8) = M2C_FIELD(a, s16 *, 0x32) - 0x1A4;
    M2C_FIELD(p, s16 *, 0xA) = M2C_FIELD(a, s16 *, 0x36);
    M2C_FIELD(p, s16 *, 0x16) = 0x1E;
    a[4]++;
    func_8004B354(a, 0);
}

void func_80117E5C(void *arg0) {
    func_8004D4C4(0x3A, 1);
    func_8004B0D8(arg0);
    M2C_FIELD(arg0, s8 *, 4) = 3;
}

void func_80117E98(u8 *a) {
    s16 *q = M2C_FIELD(a, s16 **, 0x10);
    s16 x, y, z;

    if (func_8007778C(a) != 0) {
        if (a[5] == 2) {
            x = D_1F800160_71b4;
            y = D_1F800162;
            z = D_1F800164_d75f;
            M2C_FIELD(a, s16 *, 0x2E) = x;
            M2C_FIELD(a, s16 *, 0x32) = y;
            M2C_FIELD(a, s16 *, 0x36) = z;
        } else {
            M2C_FIELD(a, s16 *, 0x2E) = q[0] - 0x20;
            M2C_FIELD(a, s16 *, 0x32) = q[1] + 0x50;
        }
        func_80077B5C(a);
        func_8004B374(a, 0);
    }
}

extern u8 D_800BF9DC;
void f_HandleRareFishOrBlueBucketPickup();
u8 *f_SpawnBlueBucketPickup(u8 *a) {
    u8 *p;

    if (!(D_800BF9DC & 1)) {
        p = func_8007A980(1, 5, 0);
        if (p != NULL) {
            M2C_FIELD(p, void **, 0x1C) = f_HandleRareFishOrBlueBucketPickup;
            M2C_FIELD(p, u8 **, 0x10) = a + 0x60;
            p[2] = 2;
            p[3] = 1;
            return p;
        }
    }
    return NULL;
}

void func_80117FAC(u8 *a) {
    s32 r;

    switch (a[5]) {
    case 0:
        func_8004D4F4(0x28, 1);
        func_8004ED94(0x2D, 0x42);
        func_8004B0D8(a);
        r = func_8004BD04(a, 0, 0);
        if (r != 0) {
            func_8004BEA8(0x28, r);
            func_80042354(1, 1);
            D_800BF870.pad1[0x16B] |= 1;
        }
        a[5]++;
        break;
    case 1:
        if (func_8005308C() != 0) {
            func_80040CDC(a, 0, D_80148574);
            a[0x70] = 2;
            a[5]++;
        }
        break;
    case 2:
        if (a[0x70] == 0xFF) {
            a[4] = 3;
        } else {
            func_80041098(a);
        }
        break;
    }
}

#define FP(p, o) M2C_FIELD(p, u8 **, o)
void func_801180CC(u8 *a) {
    u8 *p = FP(a, 0x10);
    u8 *c;

    if (*(u8 *)0x1F800207 < 5 && func_8007778C() != 0) {
        if (a[5] == 2) {
            u16 x = D_1F800160_71b4;
            u16 y = D_1F800162;
            u16 z = D_1F800164_d75f;
            F16(a, 0x2E) = x;
            F16(a, 0x32) = y;
            F16(a, 0x36) = z;
        } else {
            F16(a, 0x2E) = FU16(p, 0) + ((F16(FP(a, 0xC0), 0x1A) * 9) >> 8);
            F16(a, 0x32) = FU16(p, 2) + ((F16(FP(a, 0xC0), 0x20) * 9) >> 8);
            F16(a, 0x58) = -FU16(p, 0xC);
        }
        func_800517F8(a);
        func_8004B374(a, 1);
    }
}

void func_801181BC(void *arg0, void *arg1) {
    if (M2C_FIELD(arg0, u8 *, 0x2B) == 2) {
        M2C_FIELD(arg1, s16 *, 0x14) = 0x2000;
        return;
    }
    M2C_FIELD(arg1, s16 *, 0x14) = -0x2000;
}

void func_801181E0(u8 *a, u8 *b) {
    if (a[0x2B] == 2) {
        if (M2C_FIELD(b, s16 *, 0xE) < 0x800) {
            M2C_FIELD(b, s16 *, 0xE) -= 0x1000;
        } else {
            M2C_FIELD(b, s16 *, 0xE) = -M2C_FIELD(b, s16 *, 0xE);
        }
        M2C_FIELD(b, s16 *, 0x14) = 0xC00;
    } else {
        if (M2C_FIELD(b, s16 *, 0xE) < -0x7FF) {
            M2C_FIELD(b, s16 *, 0xE) = -M2C_FIELD(b, s16 *, 0xE);
        } else {
            M2C_FIELD(b, s16 *, 0xE) += 0x1000;
        }
        M2C_FIELD(b, s16 *, 0x14) = -0xC00;
    }
}

extern s32 D_800ECF58_6489;
extern u8 D_80017334[];
extern u8 D_800BFAF9;
extern s16 D_1F8000C0[];
/* func_801188A0, inlined */
static inline void inl_801188A0(u8 *a) {
    a[4] = 3;
    func_8004D4C4(0x78, 1);
    func_8004B0D8(a);
    D_800BF870.pad1[0x179] &= ~(1 << M2C_FIELD(a, s16 *, 0x60));
    D_800BF870.pad1[0x179] &= ~(1 << (M2C_FIELD(a, s16 *, 0x60) + 4));
    func_80040C00(0x4E);
}
void f_HandleBeachQuestPickup(u8 *a)
{
    u8 *p;
    u8 *g;
    s16 *v;
    u8 *q;
    s16 *w;

    switch (a[4]) {
    case 0:
        switch (a[3]) {
        case 0:
            a[0xB] = 0x10;
            a[0x47] = 0;
            F16(a, 0x5A) = 0;
            F16(a, 0x5C) = 0;
            a[0xD] = 0;
            M2C_FIELD(a, s32 *, 0x3C) = D_800ECF80;
            func_80077B38(a, D_8014C808, 0xF);
            F16(a, 0x80) = 0x14;
            F16(a, 0x82) = 0x28;
            F16(a, 0x84) = 0x14;
            F16(a, 0x86) = 0x28;
            func_8004B354(a, 0);
            break;
        case 1:
            a[0xB] = 0x10;
            a[0x47] = 0;
            F16(a, 0x5A) = 0;
            F16(a, 0x5C) = 0;
            a[0xD] = 0;
            M2C_FIELD(a, s32 *, 0x3C) = D_800ECF80;
            func_80077B38(a, D_8014C808, 0);
            F16(a, 0x2E) = 0x436C;
            F16(a, 0x32) = -0x76C;
            F16(a, 0x36) = 0x2BC0;
            F16(a, 0x80) = 0x1E;
            F16(a, 0x82) = 0x28;
            F16(a, 0x84) = 0x10;
            F16(a, 0x86) = 0x20;
            break;
        case 2:
            a[0xB] = 0x12;
            F16(a, 0x56) = -0x180;
            F16(a, 0x58) = 0x700;
            a[0x47] = 0;
            F16(a, 0x54) = 0;
            F16(a, 0x5C) = 0;
            a[0xD] = 0;
            M2C_FIELD(a, s32 *, 0x3C) = D_800ECF58_6489;
            func_80077B38(a, D_80017334, 2);
            F16(a, 0x80) = 0x1E;
            F16(a, 0x82) = 0x28;
            F16(a, 0x84) = 0x10;
            F16(a, 0x86) = 0x20;
            break;
        case 3:
            a[0xB] = 0x10;
            a[0x47] = 0;
            F16(a, 0x5A) = 0;
            F16(a, 0x5C) = 0;
            a[0xD] = 0;
            M2C_FIELD(a, s32 *, 0x3C) = D_800ECF80;
            func_80077B38(a, D_8014C808, 0x1A);
            F16(a, 0x80) = 0x20;
            F16(a, 0x82) = 0x40;
            F16(a, 0x84) = 0x14;
            a[0] = 1;
            F16(a, 0x86) = 0x28;
            func_8004B354(a, 0);
            break;
        }
        a[4]++;
        break;
    case 1:
        switch (a[3]) {
        case 0:
            q = FP(a, 0x10);
            switch (a[5]) {
            case 0:
                a[5] = 1;
                F16(a, 0x60) = -0x3C;
                F16(a, 0x62) = 0;
                F16(a, 0x64) = 0;
            case 1:
                if (q[0x3F] != 0) {
                    a[1] = 1;
                    func_80077EFC(a);
                    if (F16(q, 0x16) == 2) {
                        a[0] = 2;
                    } else {
                        a[0] = 1;
                    }
                    w = D_1F8000C0;
                    func_80051D90(q, a + 0x60, w);
                    F16(a, 0x2E) = D_1F8000C0[0];
                    F16(a, 0x32) = w[1];
                    F16(a, 0x36) = w[2];
                    func_8004B374(a, 0);
                }
                break;
            }
            break;
        case 1:
            g = D_800E7E80;
            switch (a[0x5E]) {
            case 0:
                switch (a[5]) {
                case 0:
                    a[5] = 1;
                    a[0] = 1;
                    break;
                case 1:
                    func_8007778C(a);
                    func_80077B5C(a);
                    break;
                }
                break;
            case 1:
                switch (a[5]) {
                case 0:
                    a[5] = 1;
                    a[0x47] = 1;
                    F16(a, 0x60) = 0;
                    F16(a, 0x62) = 0;
                    F16(a, 0x64) = 0;
                    a[8] = 0xF0;
                    break;
                case 1:
                    if (D_800BFAF9 == 0) {
                        a[4] = 3;
                        break;
                    }
                    func_8004BD64(a, 1, FP(g, 0xDC), 0, a + 0x60);
                    func_8007778C(a);
                    func_80077B5C(a);
                    break;
                }
                break;
            }
            break;
        case 2:
            p = FP(a, 0x10);
            switch (a[5]) {
            case 0:
                F16(a, 0x64) = 0x36;
                a[5] = 1;
                F16(a, 0x66) = 0x50;
                F16(a, 0x68) = 0;
                func_8004B354(a, 0);
                break;
            case 1:
                if (p[0x3F] != 0) {
                    a[1] = 1;
                    func_80077EFC(a);
                    if (F16(p, 0x16) == 2) {
                        a[0] = 2;
                    } else {
                        a[0] = 1;
                    }
                    v = D_1F8000C0;
                    func_80051D90(FP(a, 0x10), a + 0x64, v);
                    F16(a, 0x2E) = D_1F8000C0[0];
                    F16(a, 0x32) = v[1];
                    F16(a, 0x36) = v[2];
                    func_8004B374(a, 0);
                }
                break;
            }
            break;
        case 3:
            if (func_8007778C(a) != 0) {
                func_8004B374(a, 0);
            }
            break;
        }
        break;
    case 2:
        switch (a[3]) {
        case 0:
            if (func_80040B48(5) >= 0) {
                func_8004D4C4(0x24, 1);
                func_8004B0D8(a);
            }
            a[4] = 3;
            break;
        case 1:
            func_8004D4C4(0x45, 1);
            func_8004B0D8(a);
            a[4] = 3;
            D_800BF870.pad1[0x16E] |= 0x20;
            break;
        case 2:
            inl_801188A0(a);
            break;
        case 3:
            func_8004D4C4(0x53, 1);
            func_8004B0D8(a);
            a[4] = 3;
            D_800BF870.pad1[0x17D] |= 2;
            break;
        }
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

u8 *func_8011884C(s32 a, s32 b) {
    u8 *p = func_80072DDC(a, 0, 5, 3);

    if (p == NULL) {
        return NULL;
    }
    p[0x3] = 2;
    M2C_FIELD(p, s16 *, 0x60) = b;
    M2C_FIELD(p, void **, 0x1C) = f_HandleBeachQuestPickup;
    return p;
}

void func_801188A0(u8 *a) {
    a[4] = 3;
    func_8004D4C4(0x78, 1);
    func_8004B0D8(a);
    D_800BF870.pad1[0x179] &= ~(1 << M2C_FIELD(a, s16 *, 0x60));
    D_800BF870.pad1[0x179] &= ~(1 << (M2C_FIELD(a, s16 *, 0x60) + 4));
    func_80040C00(0x4E);
}

u8 *f_SpawnGoldFishhookPickup(s32 a, s32 b) {
    u8 *p = func_80072DDC(a, 0, 5, 3);

    if (p == NULL) {
        return NULL;
    }
    p[0x3] = 1;
    p[0x5E] = b;
    M2C_FIELD(p, void **, 0x1C) = f_HandleBeachQuestPickup;
    return p;
}

u8 *func_80118974(s32 a) {
    u8 *p = func_80072DDC(a, 0, 5, 3);

    if (p == NULL) {
        return NULL;
    }
    p[0x3] = 0;
    M2C_FIELD(p, void **, 0x1C) = f_HandleBeachQuestPickup;
    return p;
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_801189B8);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80118B10);

extern u8 D_801485F0[];
/* func_80119254, inlined */
static inline void inl_80119254(u8 *a) {
    u8 *p = FP(a, 0x10);
    u16 t;

    switch (a[6]) {
    case 0:
        a[6] = 1;
        a[0x2A] = D_801485F0[F16(a, 0x40)];
        F16(a, 0x2E) = FU16(p, 0x2C);
        F16(a, 0x32) = FU16(p, 0x30) + 0xF0;
        t = FU16(p, 0x34);
        F16(a, 0x4A) = 0x1000;
        F16(a, 0x50) = 0x200;
        F16(a, 0x36) = t;
        break;
    case 1:
        M2C_FIELD(a, s32 *, 0x30) += F16(a, 0x4A) << 8;
        F16(a, 0x4A) += FU16(a, 0x50);
        func_8004766C(a);
        if (func_80049250(a, 0, (s16)(FU16(a, 0x86) - FU16(a, 0x84))) != 0) {
            a[6]++;
        }
        break;
    case 2: break;
    }
}
void func_80118DB0(u8 *a) {
    u8 *p;

    switch (a[5]) {
    case 0:
        p = FP(a, 0x10);
        a[5] = 1;
        a[0x47] = p[0x5E];
        break;
    case 1:
        p = FP(a, 0x10);
        if (p[0x5E] == 0) {
            a[5] = 2;
            a[0] = 1;
            FP(a, 0x10) = *(u8 **)(p + (F16(p, 0x6C) << 2) + 0xC0);
        }
        break;
    case 2:
        inl_80119254(a);
        func_8007778C(a);
        break;
    }
    if (a[1] != 0) {
        func_80077B5C(a);
    }
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateA00PickupHandlerCase9);

void func_80119160(void *arg0, s32 arg1, void *arg2) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 6);
    switch (temp_v1) {                              /* irregular */
    case 0:
        M2C_FIELD(arg0, s16 *, 0x4A) = -0x800;
        M2C_FIELD(arg0, u8 *, 6) = 1U;
        M2C_FIELD(arg0, u16 *, 0x50) = 0x180U;
        /* fallthrough */
    case 1:
        M2C_FIELD(arg0, s32 *, 0x30) = (s32) (M2C_FIELD(arg0, s32 *, 0x30) + (M2C_FIELD(arg0, s16 *, 0x4A) << 8));
        M2C_FIELD(arg0, s16 *, 0x4A) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0x4A) + M2C_FIELD(arg0, u16 *, 0x50));
        if ((M2C_FIELD(arg2, s32 *, 0x30) - 0x8C) < M2C_FIELD(arg0, s16 *, 0x32)) {
            M2C_FIELD(arg0, s16 *, 0x4A) = -0x800;
            M2C_FIELD(arg0, u16 *, 0x50) = 0x300U;
            M2C_FIELD(arg0, u8 *, 6) = (u8) (M2C_FIELD(arg0, u8 *, 6) + 1);
            return;
        }
        return;
    case 2:
        M2C_FIELD(arg0, s32 *, 0x30) = (s32) (M2C_FIELD(arg0, s32 *, 0x30) + (M2C_FIELD(arg0, s16 *, 0x4A) << 8));
        M2C_FIELD(arg0, s16 *, 0x4A) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0x4A) + M2C_FIELD(arg0, u16 *, 0x50));
        if ((M2C_FIELD(arg2, s32 *, 0x30) - 0x8C) < M2C_FIELD(arg0, s16 *, 0x32)) {
            M2C_FIELD(arg0, s8 *, 5) = 1;
            M2C_FIELD(arg0, u8 *, 6) = 0U;
        }
        return;
    }
}

void func_80119254(u8 *a) {
    u8 *p = FP(a, 0x10);
    u16 t;

    switch (a[6]) {
    case 0:
        a[6] = 1;
        a[0x2A] = D_801485F0[F16(a, 0x40)];
        F16(a, 0x2E) = FU16(p, 0x2C);
        F16(a, 0x32) = FU16(p, 0x30) + 0xF0;
        t = FU16(p, 0x34);
        F16(a, 0x4A) = 0x1000;
        F16(a, 0x50) = 0x200;
        F16(a, 0x36) = t;
        break;
    case 1:
        M2C_FIELD(a, s32 *, 0x30) += F16(a, 0x4A) << 8;
        F16(a, 0x4A) += FU16(a, 0x50);
        func_8004766C(a);
        if (func_80049250(a, 0, (s16)(FU16(a, 0x86) - FU16(a, 0x84))) != 0) {
            a[6]++;
        }
        break;
    case 2: break;
    }
}

void func_80119350(u8 *a) {
    u8 *p = FP(a, 0x10);
    s32 t;

    switch (a[5]) {
    case 0:
        a[5]++;
        a[0xB] = 0x10;
        a[0x47] = 1;
        F16(a, 0x5A) = 0x200;
        a[8] = 0xFC;
        F16(a, 0x88) = -0x38;
        F16(a, 0x8A) = 0x20;
        F16(a, 0x8C) = 0;
    case 1:
        t = F16(FP(a, 0x10), 0x16);
        if (t == 2) {
            a[0] = t;
        } else {
            a[0] = 1;
        }
        if (p[0x3F] != 0) {
            a[1] = 1;
            func_80077EFC(a);
            func_80051D90(p, a + 0x88, D_1F8000C0);
            F16(a, 0x2E) = D_1F8000C0[0];
            F16(a, 0x32) = D_1F8000C0[1];
            F16(a, 0x36) = D_1F8000C0[2];
        }
        break;
    }
}

void func_80119454(u8 *a) {
    u8 *q = M2C_FIELD(a, u8 **, 0x10);

    switch (a[5]) {
    case 0:
        a[5]++;
        a[0] = 1;
        M2C_FIELD(a, s16 *, 0x54) = 0xC00;
        M2C_FIELD(a, s16 *, 0x56) = 0x200;
        func_8004B354(a, 1);
    case 1:
        M2C_FIELD(a, s16 *, 0x2E) = M2C_FIELD(q, s16 *, 0x2C);
        M2C_FIELD(a, s16 *, 0x32) = M2C_FIELD(q, s16 *, 0x30) - 0x14;
        M2C_FIELD(a, s16 *, 0x36) = M2C_FIELD(q, s16 *, 0x34);
        if (func_8007778C(a) != 0) {
            func_80051844(a);
            func_8004B374(a, 1);
        }
        break;
    }
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80119510);

static inline s32 gc_submit(u8 *a) {
    s32 i;
    s32 k;
    u8 *e;

    i = 0;
    do {
        if ((a[0x5F] >> i) & 1) {
            k = i + 4;
            e = func_8011C610(a, k);
            if (e != NULL) {
                e[0x28] |= 0x80;
                D_800BF870.pad1[0x172] |= 1 << k;
                a[0x5F] -= 1 << i;
                func_8004D604(0x2A, 1);
                return 1;
            }
        }
        i++;
    } while (i < 3);
    return 0;
}
s32 f_SubmitPendingGoldenCrabs(u8 *a) {
    u8 *t = D_800E7E80;
    s16 r;

    switch (a[7]) {
    case 0:
        if ((s8)a[0x70] <= 0) {
            a[7]++;
        }
        break;
    case 1:
        if (gc_submit(a) != 0) {
            H_f12c(a, 0x40) = 0x48;
            a[7]++;
        } else {
            a[7] = 3;
        }
        break;
    case 2:
        if (--H_f12c(a, 0x40) == 0) {
            a[7]--;
        }
        break;
    case 3:
        func_8006CBA8(t + 0x2C);
        a[7]++;
        H_f12c(a, 0x42) = func_800782B0(t + 0x2C, H_f12c(a, 0x2E), H_f12c(a, 0x36)) & 0xFFF;
    case 4:
        r = func_800776F8(H_f12c(a, 0x42), H_f12c(t, 0x56), 0x100);
        H_f12c(t, 0x56) = r;
        if (r == H_f12c(a, 0x42)) {
            a[7] = 0;
            return 1;
        }
        break;
    }
    return 0;
}

extern u8 D_800BF80E;
extern u8 D_80148680[];
extern u8 D_801486F0[];
extern u8 D_801486F8[];
extern u8 D_80148708[];
extern u8 D_80148718[];
extern u8 D_80148720[];
/* func_8011AC5C, inlined */
static inline s32 inl_8011AC5C(u8 *a) {
    s32 i;

    a[0x5F] = 0;
    if (D_800BF870.pad1[0x172] == 0) {
        return 0;
    }
    for (i = 0; i < 3; i++) {
        if (((D_800BF870.pad1[0x172] >> i) & 1) && !((D_800BF870.pad1[0x172] >> (i + 4)) & 1)) {
            a[0x5F] |= 1 << i;
        }
    }
    return a[0x5F];
}
void func_80119828(u8 *a) {
    switch (a[6]) {
    case 0:
        if (a[0x2B] == 3) {
            func_80042354(1, 1);
            func_80040D68(a, D_80148680);
            a[0x70] = 1;
            a[6]++;
        } else {
            M2C_FIELD(a, s16 *, 0x56) = func_800782B0(a + 0x2C, D_1F800160_71b4, D_1F800164_d75f);
        }
        break;
    case 1:
        if (a[0x71] == 0xFF && D_800BF80E != 0) {
            if (D_800BF870.pad1[0x16D] == 0) {
                D_800BF870.pad1[0x16D] = 1;
                if (inl_8011AC5C(a) != 0) {
                    D_800E7E80[5] = 0x26;
                    D_800E7E80[6] = 0;
                    if (a[0x5F] & 4) {
                        func_80040D68(a, D_80148708);
                        a[5] = 3;
                    } else {
                        func_80040D68(a, D_801486F8);
                        a[5] = 2;
                    }
                } else {
                    func_80040D68(a, D_801486F0);
                    a[5] = 1;
                }
            } else if (inl_8011AC5C(a) != 0) {
                D_800E7E80[5] = 0x26;
                D_800E7E80[6] = 0;
                func_80040D68(a, D_80148720);
                a[5] = 5;
            } else {
                func_80040D68(a, D_80148718);
                a[5] = 4;
            }
            a[6] = 0;
        }
        break;
    }
}

extern u8 D_800BF843;
extern u8 D_800BF9E3;
extern u8 D_80148698[];
void f_HandleGoldenCrabDialogueFirstVisit(u8 *a) {
    switch (a[6]) {
    case 0:
        func_80070724(1, 0, 0x63);
        func_80070888(D_80148698);
        a[6]++;
        break;
    case 1:
        if (D_800BF843 == 1 && func_800707E0() != 0) {
            a[6]++;
        }
        break;
    case 2:
        if (func_80070830() != 0) {
            a[0x70] = 1;
            a[7] = 0;
            a[6]++;
        }
        break;
    case 3:
        if (f_SubmitPendingGoldenCrabs(a) != 0) {
            if ((D_800BF9E3 & 0x70) == 0x70) {
                a[5] = 7;
                a[6] = 0;
            } else {
                a[0x70] = 1;
                a[6]++;
            }
        }
        break;
    case 4:
        if ((s8)a[0x70] <= 0) {
            a[6]++;
        }
        break;
    case 5:
        func_80070798();
        a[5] = 6;
        a[6] = 0;
        break;
    }
}

extern u8 D_801486A0[];
void f_HandleGoldenCrabDialogueRepeatVisit(u8 *a) {
    s32 n;

    switch (a[6]) {
    case 0:
        n = 1;
        a[0x70] = n;
        a[6] += n;
        func_80070724(n, 0, 0x63);
        func_80070888(D_801486A0);
        break;
    case 1:
        if (D_800BF843 == 1 && (s8)a[0x70] <= 0) {
            a[7] = 0;
            a[6]++;
        }
        break;
    case 2:
        if (f_SubmitPendingGoldenCrabs(a) != 0) {
            if ((D_800BF9E3 & 0x70) == 0x70) {
                a[5] = 7;
                a[6] = 0;
            } else {
                a[6]++;
            }
        }
        break;
    case 3:
        if (D_800BF843 == 1 && func_800707E0() != 0) {
            a[6]++;
        }
        break;
    case 4:
        if (func_80070830() != 0) {
            func_80070798();
            a[5] = 6;
            a[6] = 0;
        }
        break;
    }
}

#define STH(p, o) (*(s16 *)((u8 *)(p) + (o)))
extern u8 D_8014886C[];
typedef struct { u8 pad[0x12]; s16 a; s16 b; s16 c; } StgT;
extern StgT D_8014886C_a7c3;
void f_StageWindmillCutsceneActor(u8 *a) {

    switch (a[7]) {
    case 0:
        a[0x70] = 1;
        func_80041B08(a, (u8 *)&D_8014886C_a7c3.a, 0xF);
        STH(a, 0x42) = func_800782B0(a + 0x2C, D_8014886C_a7c3.a, D_8014886C_a7c3.c);
        a[7]++;
        break;
    case 1:
        if (a[0x70] == 0) {
            a[7]++;
        }
        break;
    case 2:
        if (func_80041438(a, STH(a, 0x42), 0x80) != 0) {
            a[7]++;
            func_80041718(a, 2, 2);
        }
        break;
    case 3:
        if (func_80041BF0(a) != 0) {
            func_80041718(a, 0, 2);
            if (a[0x70] == 0) {
                a[0x70] = 1;
                a[7]++;
            }
        }
        break;
    case 4:
        if (a[0x70] == 0) {
            func_80041718(a, 5, 0);
            a[7]++;
        }
        break;
    case 5:
        if (a[0x79] == 1) {
            func_80074590(0x32, 0, 0);
            a[7] = 0;
            a[6]++;
        }
        break;
    }
}

#define WH(p, o) (*(s16 *)((u8 *)(p) + (o)))
extern u8 *D_1F800214;
#define SP214 D_1F800214
extern u8 D_800BF9DE;
s32 f_ApplyWindmillCutsceneTransition(u8 *a) {
    u8 *t = D_800E7E80;
    u8 st = D_800BF9DE;
    s32 k;
    u8 *d;

    if (a[7] == st) {
        return 0;
    }
    a[7] = st;
    switch (st) {
    case 4:
        func_80054D14(t, 0xB4, 0);
        func_80041768(SP214, 4, 0);
        return 0;
    case 5:
        k = 0xA00;
        WH(t, 0x56) = k;
        func_80054D14(t, 0xB9, 0);
        func_80041768(SP214, 8, 0);
        WH(SP214, 0x56) = k;
        break;
    case 7:
        WH(t, 0x56) = 0x400;
        WH(SP214, 0x56) = 0x400;
        WH(SP214, 0x52) = WH(t, 0x36) + 10;
        func_80054DAC(t, 0xB4, 0);
        return 0;
    case 9:
    case 11:
        func_80041718(SP214, 4, 0);
        func_80054DAC(t, 0xB4, 0);
        return 0;
    case 12:
        func_800708B4(1);
        func_80041768(SP214, 8, 0);
        return 1;
    case 13:
        func_80041768(a, 8, 0);
        func_800707B0();
        return 1;
    case 16:
        func_800708B4(2);
        WH(a, 0x4A) = 0;
        func_80041768(a, 9, 2);
        if (func_80070870() <= 0) {
            func_800707B0();
        }
        return 1;
    case 18:
        d = D_8014886C;
        WH(a, 0x2E) = WH(d, 0xC);
        WH(a, 0x32) = WH(d, 0xE);
        WH(a, 0x36) = WH(d, 0x10);
        WH(a, 0x56) = 0;
        WH(t, 0x2E) = 0x4FC2;
        WH(t, 0x32) = -0xA4C;
        WH(t, 0x36) = 0x1A00;
        WH(t, 0x56) = 0x400;
        break;
    case 19:
        WH(SP214, 0x56) = 0x400;
        break;
    case 20:
        WH(t, 0x56) = 0x800;
        WH(SP214, 0x56) = 0x800;
        WH(SP214, 0x52) = WH(t, 0x36) + 0x5A;
        func_80041718(a, 4, 0);
        func_80041718(SP214, 3, 0);
        func_80054D14(t, 0xC1, 0);
        func_8006CBA8(t + 0x2C);
        D_800E8008[0x64] = 1;
        WH(D_800E8008, 0x6E) = 0x180;
        WH(D_800E8008, 0x70) = 0x240;
        break;
    case 21:
        func_80074590(0x72, 0, 0);
        a[0x70] = 1;
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_RunWinsWindmillCutscene);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_HandleWinConversationState);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8011A804);

extern s32 D_800ECF58_a4fb[];
extern u8 D_801485F8[];
extern u8 D_8014C9C0[];
void func_8011A928(u8 *a)
{
    s32 *t;
    s32 v;
    switch (a[4]) {
    case 0:
        t = D_800ECF58_a4fb;
        if (func_800519E0(a, 0x11, t[0x3C / 4], D_801485F8) != 0) {
            break;
        }
        v = t[0x50 / 4];
        a[0xB] = 0;
        M2C_FIELD(a, s16 *, 0x58) = 0;
        M2C_FIELD(a, s16 *, 0x56) = 0;
        M2C_FIELD(a, s16 *, 0x54) = 0;
        a[0xBE] = 0;
        M2C_FIELD(a, s32 *, 0x3C) = v;
        func_80040CDC(a, D_8014C9C0, D_80148680);
        if (a[3] == 0) {
            M2C_FIELD(a, s16 *, 0x80) = 0xC8;
            a[0] = 1;
            M2C_FIELD(a, s16 *, 0x82) = 0x190;
            a[0x7B] = 1;
        } else {
            M2C_FIELD(a, s16 *, 0x56) = 0x800;
            a[0] = 9;
            M2C_FIELD(a, s16 *, 0x80) = 0x50;
            M2C_FIELD(a, s16 *, 0x82) = 0xA0;
            a[0x7B] = 0;
        }
        M2C_FIELD(a, s16 *, 0x84) = 0x80;
        M2C_FIELD(a, s16 *, 0x86) = 0x120;
        func_80041718(a, a[0x7B], 0);
        a[4]++;
        break;
    case 1:
        switch (a[3]) {
        case 0:
            f_HandleWinConversationState(a);
            if (D_800BF9DE < 0x16 && func_80077F3C(a) != 0) {
                func_800518FC(a);
            }
            break;
        case 1:
            func_8011A804(a);
            break;
        }
        if (a[1] != 0) {
            func_800518FC(a);
        }
        a[0x2B] = 0;
        break;
    case 2:
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

s32 func_8011AB00(u8 *a) {
    u8 *t = D_1F800214;

    switch (a[0x78]) {
    case 0:
        M2C_FIELD(a, s16 *, 0x42) = func_800782B0(t + 0x2C, M2C_FIELD(a, s16 *, 0x2E), M2C_FIELD(a, s16 *, 0x36)) & 0xFFF;
        a[0x78]++;
        break;
    case 1:
        return func_80041438(t, M2C_FIELD(a, s16 *, 0x42), 0x100);
    }
    return 0;
}

s32 func_8011AB84(u8 *a) {
    switch (a[0x78]) {
    case 0:
        M2C_FIELD(a, s16 *, 0x42) = 15;
        a[0x78]++;
        D_800BF818 = 8;
        goto end;
    case 1:
        if (--M2C_FIELD(a, s16 *, 0x42) == 0) {
            return 1;
        }
    end:
    default:
        return 0;
    }
}

s32 func_8011ABF0(u8 *a) {
    switch (a[0x78]) {
    case 0:
        M2C_FIELD(a, s16 *, 0x42) = 18;
        a[0x78]++;
        D_800BF818 = 9;
        goto end;
    case 1:
        if (--M2C_FIELD(a, s16 *, 0x42) == 0) {
            return 1;
        }
    end:
    default:
        return 0;
    }
}

s32 func_8011AC5C(u8 *a) {
    s32 i;

    a[0x5F] = 0;
    if (D_800BF870.pad1[0x172] == 0) {
        return 0;
    }
    for (i = 0; i < 3; i++) {
        if (((D_800BF870.pad1[0x172] >> i) & 1) && !((D_800BF870.pad1[0x172] >> (i + 4)) & 1)) {
            a[0x5F] |= 1 << i;
        }
    }
    return a[0x5F];
}

s32 func_8011ACDC(u8 *a) {
    s32 i;
    s32 k;
    u8 *e;
    GameState *g;
    s32 one;

    i = 0;
    g = &D_800BF870;
    one = 1;
    do {
        if ((a[0x5F] >> i) & 1) {
            k = i + 4;
            e = func_8011C610(a, k);
            if (e != NULL) {
                e[0x28] |= 0x80;
                g->pad1[0x172] |= one << k;
                a[0x5F] -= one << i;
                func_8004D604(0x2A, 1);
                return 1;
            }
        }
        i++;
    } while (i < 3);
    return 0;
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateWindmillExplosionDebris);

void f_UpdateWindmillFallingActor(u8 *a) {
    u32 st = D_800BF9DE;
    s32 t;

    if (st >= 4) {
        switch (a[7]) {
        case 0:
            H(a, 0x40) = 0x1E;
            a[7]++;
            break;
        case 1:
            if ((H(a, 0x32) += 8) >= -0x95B) {
                H(a, 0x32) = -0x95C;
            }
            if (H(a, 0x40) != 0) {
                H(a, 0x40)--;
                switch (a[3]) {
                case 3:
                    U(a, 0x2E) -= 6;
                    U(a, 0x36) += 6;
                    break;
                case 7:
                    U(a, 0x2E) -= 6;
                    U(a, 0x36) -= 6;
                    break;
                case 8:
                    U(a, 0x2E) += 6;
                    U(a, 0x36) -= 6;
                    break;
                case 9:
                    U(a, 0x2E) += 6;
                    U(a, 0x36) += 6;
                    break;
                }
            } else {
                a[7]++;
            }
            break;
        case 2:
            if (st >= 5) {
                a[5] = 0;
                a[6] = 0;
                a[7] = 0;
                if (a[3] == 3) {
                    a[3] = 0xA;
                } else {
                    a[3] += 4;
                }
            }
            break;
        }
    } else {
        switch (a[6]) {
        case 0:
            func_80077B38(a, D_8014C808, 8);
            H(a, 0x60) = H(a, 0x32);
            a[6]++;
            if (a[3] & 1) {
                H(a, 0x40) = 0xF;
            } else {
                H(a, 0x40) = 1;
            }
            break;
        case 1:
            if (--H(a, 0x40) == 0) {
                if (func_8009A450(st) & 1) {
                    a[6] = 2;
                    H(a, 0x4C) = 0x200;
                    H(a, 0x52) = -8;
                } else {
                    a[6] = 5;
                    H(a, 0x4C) = -0x200;
                    H(a, 0x52) = 8;
                }
            }
            break;
        case 2:
            U(a, 0x5A) = (U(a, 0x5A) - 0x10) & 0xFFF;
            W(a, 0x30) += -0x14000;
            W(a, 0x34) += H(a, 0x4C) << 8;
            if ((H(a, 0x4C) += H(a, 0x52)) < -0x200) {
                func_80077B38(a, D_8014C808, 0xC);
                a[6]++;
            }
            break;
        case 3:
        case 6:
            W(a, 0x30) += 0x28000;
            if (H(a, 0x32) >= H(a, 0x60)) {
                W(a, 0x30) = H(a, 0x60) << 16;
                a[6]++;
                func_80077B38(a, D_8014C808, 8);
            }
            break;
        case 4:
            t = (U(a, 0x5A) - 0x40) & 0xFFF;
            U(a, 0x5A) = t;
            if (t < 0x40) {
                H(a, 0x4C) = -0x200;
                U(a, 0x5A) = 0;
                H(a, 0x52) = 8;
                a[6]++;
            }
            break;
        case 5:
            U(a, 0x5A) = (U(a, 0x5A) + 0x10) & 0xFFF;
            W(a, 0x30) += -0x14000;
            W(a, 0x34) += H(a, 0x4C) << 8;
            if ((H(a, 0x4C) += H(a, 0x52)) > 0x200) {
                func_80077B38(a, D_8014C808, 0xC);
                a[6]++;
            }
            break;
        case 7:
            t = (U(a, 0x5A) + 0x40) & 0xFFF;
            U(a, 0x5A) = t;
            if (t >= 0xFC0) {
                H(a, 0x40) = 1;
                a[6] = 1;
                U(a, 0x5A) = 0;
            }
            break;
        }
    }
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8011B738);

#define KSH(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define KSW(p, o) (*(s32 *)((u8 *)(p) + (o)))
void func_8011BC3C(u8 *a) {
    s32 r;
    s32 c;

    r = func_80077B5C(a);
    switch (a[7]) {
    case 0:
        func_80077B38(a, D_8014C808, 0xB);
        a[7]++;
        break;
    case 1:
        if (r != 0) {
            func_80074590(5, 0, 0);
            a[0x5F] = 0;
            a[0x29] = 0;
            KSH(a, 0x4A) = -((func_8009A450() & 0x7FF) + 0x2600);
            a[7]++;
        }
        break;
    case 2:
        KSW(a, 0x30) += KSH(a, 0x4A) << 8;
        if ((KSH(a, 0x4A) += 0x400) > 0x3000) {
            KSH(a, 0x4A) = 0x3000;
        }
        func_8004766C(a);
        if ((c = func_80049250(a, 0, 0x14)) == 1) {
            KSH(a, 0x4A) = 0;
            a[0x29] = c;
        }
        if (a[0x29] != 0) {
            func_80074590(3, 3, -0xA);
            func_80077B38(a, D_8014C808, 0xA);
            a[7]++;
        }
        break;
    case 3:
        if (r != 0) {
            a[6] = 0;
            a[7] = 0;
        }
        break;
    }
}

void func_8011BDB8(u8 *a) {
    s32 r;

    r = func_80077B5C(a);
    r |= func_80077B5C(a);
    switch (a[7]) {
    case 0:
        func_80077B38(a, D_8014C808, 0xB);
        a[7]++;
        break;
    case 1:
        if (r != 0) {
            KSH(a, 0x4A) = -((func_8009A450() & 0x7FF) + 0x2600);
            a[7]++;
        }
        break;
    case 2:
        KSW(a, 0x30) += KSH(a, 0x4A) << 8;
        if ((KSH(a, 0x4A) += 0x400) > 0x3000) {
            KSH(a, 0x4A) = 0x3000;
        }
        if (KSH(a, 0x32) >= -0x7BC) {
            KSH(a, 0x32) = -0x7BC;
            func_80077B38(a, D_8014C808, 0xA);
            a[7]++;
        }
        break;
    case 3:
        if (r != 0) {
            a[6] = 0;
            a[7] = 0;
        }
        break;
    }
}

#define KSH(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define KSW(p, o) (*(s32 *)((u8 *)(p) + (o)))
extern u8 D_800BF9E0;
void f_UpdateKainenHouseSceneActor(u8 *a) {
    s32 r;

    if (func_8007778C(a) == 0) {
        return;
    }
    r = func_80077B5C(a);
    switch (a[5]) {
    case 0:
        func_80077B38(a, D_8014C808, 0xB);
        a[5]++;
        break;
    case 1:
        if (r != 0) {
            KSH(a, 0x4A) = -((func_8009A450() & 0x7FF) + 0x2600);
            a[5]++;
        }
        break;
    case 2:
        KSW(a, 0x30) += KSH(a, 0x4A) << 8;
        KSH(a, 0x4A) += 0x400;
        if (KSH(a, 0x32) >= -0x7BC) {
            KSH(a, 0x32) = -0x7BC;
            func_80077B38(a, D_8014C808, 0xA);
            a[5]++;
        }
        break;
    case 3:
        if (r != 0) {
            KSH(a, 0x40) = func_8009A450() & 0x1F;
            a[5]++;
        }
        break;
    case 4:
        if (D_800BF9E0 >= 0x11) {
            func_80077B38(a, D_8014C808, 7);
            a[5]++;
        } else if (--KSH(a, 0x40) <= 0) {
            a[5] = 0;
        }
        break;
    }
    if (D_800BF9E0 >= 0x12) {
        a[4] = 3;
    }
}

void func_8011C090(u8 *a) {
    GameState *g;
    u8 v;

    if (D_800BF80D == 0) {
        g = &D_800BF870;
        v = g->pad1[0x172];
        func_8004ED94((v & 1) + ((v >> 1) & 1) + ((v >> 2) & 1) + 0x26, 0x42);
        func_8004B0D8(a);
        func_8004D4F4(0x2A, 1);
        v = g->pad1[0x172] |= 1 << a[3];
        if ((v & 3) == 3) {
            g->pad1[0x174] = 7;
        }
        if ((v & 7) == 7) {
            func_80040C00(7);
            func_80040B48(8);
        }
    }
    a[4] = 3;
}

extern u8 D_800BF8BC;
extern u8 D_800E7EAA;
typedef struct {
    s16 x, y, z;
    u8 b;
    u8 pad;
} GCrabPos;
extern GCrabPos D_80148914[];
typedef struct {
    s16 x, y, z, pad;
} GCrabVec;
static inline void gcrab_idle(u8 *a) {
    s32 r;

    if (D_800E7EAA >= 0x1A && func_80077870(a) != 0) {
        switch (a[6]) {
        case 0:
            r = func_8009A450() & 7;
            if (r == 0) {
                a[6] = 2;
            } else if (r < 5) {
                a[6] = 1;
            }
            a[7] = 0;
            break;
        case 1:
            func_8011BC3C(a);
            break;
        case 2:
            func_80077B5C(a);
            switch (a[7]) {
            case 0:
                func_80077B38(a, D_8014C808, 7);
                H_f12c(a, 0x40) = (func_8009A450() & 0x1F) + 0x20;
                a[7]++;
                break;
            case 1:
                if (--H_f12c(a, 0x40) == 0) {
                    a[6] = 0;
                    a[7] = 0;
                }
                break;
            }
            break;
        }
    }
}
void f_HandleGoldenCrabAndWindmillActor(u8 *a) {
    GCrabVec v;
    GCrabPos *e;
    s32 k;
    u8 *p;

    switch (a[4]) {
    case 0:
        a[4] = 1;
        *(s32 *)(a + 0x3C) = D_800ECF80;
        a[0xD] = 0;
        H_f12c(a, 0x5C) = 0;
        a[0xB] = 0x10;
        a[0x47] = 0;
        H_f12c(a, 0x5A) = 0;
        func_80077B38(a, D_8014C808, 8);
        H_f12c(a, 0x80) = 0x32;
        H_f12c(a, 0x82) = 0x64;
        H_f12c(a, 0x84) = 0x46;
        H_f12c(a, 0x86) = 0x64;
        a[0x29] = 0;
        H_f12c(a, 0x60) = 0;
        H_f12c(a, 0x62) = 0;
        k = a[3];
        switch (k) {
        case 0:
        case 1:
            e = &D_80148914[k];
            a[0] = 1;
            H_f12c(a, 0x2E) = e->x;
            H_f12c(a, 0x32) = e->y;
            H_f12c(a, 0x36) = e->z;
            a[0x2A] = e->b;
            break;
        case 3:
            if (D_800BF8BC == 0xFF) {
                a[4] = k;
            }
            break;
        }
        break;
    case 1:
        switch (a[3]) {
        case 0:
            gcrab_idle(a);
            break;
        case 1:
            gcrab_idle(a);
            break;
        case 2:
            p = *(u8 **)(a + 0x10);
            v.x = -2;
            v.y = 0;
            v.z = -0x16;
            func_8004BD64(a, 1, *(s32 *)(p + 0xDC), *(s32 *)(p + 0xDC), &v);
            func_80077B5C(a);
            a[1] = 1;
            func_80077E7C(a);
            break;
        case 3:
        case 7:
        case 8:
        case 9:
            f_UpdateWindmillFallingActor(a);
            func_80077B5C(a);
            a[1] = 1;
            func_80077E7C(a);
            break;
        case 4:
        case 5:
        case 6:
            func_8011B738(a);
            break;
        case 10:
        case 11:
        case 12:
        case 13:
            f_UpdateWindmillExplosionDebris(a);
            break;
        case 20:
            if (func_8007778C(a) != 0) {
                f_UpdateKainenHouseSceneActor(a);
            }
            break;
        }
        a[0x29] = 0;
        break;
    case 2:
        a[1] = 1;
        func_80077E7C(a);
        switch (a[5]) {
        case 0:
        case 2:
            func_8011C090(a);
            break;
        case 1:
            if (a[6] == 0) {
                a[6] = 1;
                H_f12c(a, 0x5A) = 0;
                func_80077B38(a, D_8014C808, 0xC);
            }
            break;
        }
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

void f_HandleGoldenCrabAndWindmillActor();
void func_80135D64();
void f_HandleCurvedSupportContactActor();
void func_8013A900();
u8 *func_8011C610(s32 a, u8 b) {
    u8 *p = func_8007A980(0, 2, 0);

    if (p == NULL) {
        return NULL;
    }
    M2C_FIELD(p, void **, 0x1C) = f_HandleGoldenCrabAndWindmillActor;
    M2C_FIELD(p, s32 *, 0x10) = a;
    p[0x2] = 4;
    p[0x3] = b;
    return p;
}

#define NH(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define NW(p, o) (*(s32 *)((u8 *)(p) + (o)))
extern s8 D_800BF9EB;
extern u8 *D_800BF860;
extern u8 D_80148924[];
extern u8 D_80148974[];
extern u8 D_801489A4[];
extern u8 D_8014DC2C[];
void f_HandleNetBridgeRaiseNpcInteraction(u8 *a) {
    u8 *g;
    u8 *p;
    s32 n;
    u8 *e;

    switch (a[5]) {
    case 0:
        D_800BF9EB = 0;
        a[0] = 9;
        NW(a, 0x2C) = 0x3A340000;
        NW(a, 0x30) = 0xF5E20000;
        NW(a, 0x34) = 0x03840000;
        a[0x2A] = 0xC;
        NH(a, 0x56) = 0;
        a[0x46] = 6;
        func_80077C40(a, D_8014DC2C, 6);
        a[5]++;
        break;
    case 1:
        g = D_800BF808;
        if (g[0xE] != 0 && g[0xF] == 1 && func_8007778C(a) != 0 && a[0x2B] == 3) {
            D_800BF870.pad1[0x17A] = 0;
            if (D_800BF870.itemCounts[0x24] != 0) {
                func_80042354(1, 1);
            } else {
                func_80042354(1, 3);
            }
            D_800BF860 = a;
            if (D_800BF870.pad1[0x170] == 0) {
                func_80040CDC(a, D_8014DC2C, D_80148924);
                D_800BF870.pad1[0x170] = 1;
                n = 2;
            } else if (D_800BF870.itemCounts[0x24] != 0) {
                e = D_800E8008;
                func_8006E1C0(1);
                NW(e, 0x38) = 0x393A0000;
                NW(e, 0x3C) = 0xF5740000;
                NW(e, 0x40) = 0x02EE0000;
                NH(e, 0x6E) = 0x10E;
                NH(e, 0x70) = 0x9C4;
                NH(e, 0x6C) = 0x420;
                e[0x66] = 0;
                func_80070724(0xD, 8, 0x8B);
                a[0] = 2;
                func_80040CDC(a, D_8014DC2C, D_801489A4);
                n = 0xA;
                a[0x70] = 2;
            } else {
                func_80040CDC(a, D_8014DC2C, D_80148974);
                n = 2;
            }
            a[5] = n;
            a[0x70] = 2;
        }
        break;
    case 2:
        a[1] = 1;
        func_80077E7C(a);
        if (a[0x70] == 0xFF) {
            if (D_800BF870.itemCounts[0x24] != 0) {
                a[0] = 2;
                func_80040CDC(a, D_8014DC2C, D_801489A4);
                a[0x70] = 2;
                a[5] = 0xA;
            } else {
                func_8006E1E4();
                D_800BF870.pad1[0x17A] = 2;
                a[5] = 3;
            }
        }
        break;
    case 3:
        a[1] = 1;
        func_80077E7C(a);
        if (D_800BF830 == 0xFF) {
            func_80042310();
            a[5] = 1;
        }
        break;
    case 10:
        a[1] = 1;
        func_80077E7C(a);
        if (a[0x70] == 0xFF) {
            p = func_80072DDC(0, 3, 2, 3);
            if (p != NULL) {
                *(void **)(p + 0x1C) = f_HandleTownCreatureActor;
                p[3] = 0x81;
                NH(p, 0x2E) = 0x385A;
                NH(p, 0x32) = -0x98C;
                NH(p, 0x36) = 0x1801;
            }
            func_8011C610(0, 0);
            func_8011C610(0, 1);
            D_800BF870.pad1[0x174] = 2;
            D_800BF870.pad1[0x17E] = 1;
            a[4] = 2;
        }
        break;
    }
    if (a[5] >= 2) {
        func_80041098(a);
    }
    func_8004190C(a);
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8011CA04);

extern u8 D_800BF89C;
extern s32 D_800ECFA4;
void func_8011CD14(u8 *a);
void func_8011CBD0(u8 *a)
{
    s32 v;

    switch (a[4]) {
    case 0:
        if (D_800BF89C >= 4) {
            v = D_800ECFA4;
            a[0xB] = 0x40;
            M2C_FIELD(a, s16 *, 0x80) = 0x64;
            M2C_FIELD(a, s16 *, 0x82) = 0xC8;
            M2C_FIELD(a, s16 *, 0x84) = 0xC0;
            M2C_FIELD(a, s16 *, 0x58) = 0;
            M2C_FIELD(a, s16 *, 0x56) = 0;
            M2C_FIELD(a, s16 *, 0x54) = 0;
            a[0] = 1;
            a[0x2B] = 0;
            M2C_FIELD(a, s16 *, 0x86) = 0x150;
            a[5] = 0;
            M2C_FIELD(a, s32 *, 0x3C) = v;
            a[4]++;
        }
        break;
    case 1:
        switch (a[3]) {
        case 0:
            f_HandleNetBridgeRaiseNpcInteraction(a);
            break;
        case 1:
            func_8011CA04(a);
            break;
        }
        if (a[1] != 0) {
            func_800518FC(a);
        }
        a[0x2B] = 0;
        func_8011CD14(a);
        break;
    case 2:
        a[4]++;
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

extern void *D_800ECF94;
extern u8 D_8014BFB4[];
void func_8011CD14(u8 *a) {
    switch (a[7]) {
    case 0:
        if (a[1] != 0 && func_800519E0(a, 0xF, D_800ECF94, D_8014BFB4) == 0) {
            a[7]++;
        }
        break;
    case 1:
        if (a[1] == 0) {
            func_8007ADDC(a);
            a[7]--;
        }
        break;
    }
}

s32 func_8011CDB8(u8 *a) {
    switch (a[0x78]) {
    case 0:
        M2C_FIELD(a, s16 *, 0x72) = 5;
        a[0x78]++;
        break;
    case 1:
        if (--M2C_FIELD(a, s16 *, 0x72) == 0) {
            D_800BF818 = 7;
            M2C_FIELD(a, s16 *, 0x72) = 20;
            a[0x78]++;
        }
        break;
    case 2:
        if (--M2C_FIELD(a, s16 *, 0x72) == 0) {
            return 1;
        }
        break;
    }
    return 0;
}

s32 func_8011CE64(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x7A) == 1) {
        func_80040B48(0x4E);
    }
    return 1;
}

void f_AdvanceKainenHouseRescueSequence(u8 *a, s32 f) {
    s16 v[6];
    u8 *p;
    s32 ok;
    s32 n;
    u8 *g;
    u8 c;

    switch (a[7]) {
    case 0:
        if (a[0x70] == 0 && (g = (u8 *)D_800BF808, g[2] == 0)) {
            *(u8 **)(g + 0x58) = a;
            a[0x70] = 2;
            a[7]++;
        }
        break;
    case 1:
        if (a[0x70] == 0) {
            if ((s16)f == 0) {
                D_800BF9E0 = 2;
            } else {
                D_800BF9E0 = 0xC;
            }
            a[7]++;
        }
        break;
    case 2:
        ok = 0;
        if ((s16)f == 0) {
            ok = D_800BF9E0 == 3;
        } else if (D_800BF9E0 == 0xD) {
            ok = 1;
        }
        if (ok) {
            func_800440E4(D_800E7E80, 2, 4);
            a[0x70] = 2;
            a[7]++;
        }
        break;
    case 3:
        if (a[0x70] == 0) {
            a[0x47] = 0;
            a[0x70] = 2;
            a[7]++;
        }
        break;
    case 4:
        if (a[0x70] == 0) {
            a[0x47] = 1;
            a[0x70] = 2;
            a[7]++;
        }
        break;
    case 5:
        if (a[0x70] == 0) {
            H_f12c(a, 0x40) = 5;
            a[7]++;
        }
        break;
    case 6:
        if (*(u16 *)(*(u8 **)(a + 0x38) + 4) != 0) {
            if (*(u16 *)(*(u8 **)(a + 0x38) + 4) == 1) {
                p = *(u8 **)(a + 0xDC);
            } else {
                p = *(u8 **)(a + 0xD0);
            }
            v[1] = H_f12c(p, 0x2C);
            v[3] = H_f12c(p, 0x30);
            v[5] = H_f12c(p, 0x34);
            func_8003116C(0xE, v, 0);
        }
        if (--H_f12c(a, 0x40) == 0) {
            c = a[0x18];
            if ((s16)f == 0) {
                n = c + 8;
            } else {
                n = c + 0xC;
            }
            a[0x1A] = n;
            a[0x18] = a[0x19] = *(volatile u8 *)(a + 0x1A);
            if ((s8)a[0x18] < 0) {
                a[0x1A] = 0x7F;
                a[0x19] = 0x7F;
                a[0x18] = 0x7F;
                a[0x70] = 2;
                a[0xD] &= 0xFD;
                a[7]++;
                return;
            }
            H_f12c(a, 0x40) = 5;
        }
        break;
    }
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_HandleKainenInteraction);

extern u8 D_80148D2C[];
static inline s32 func_8011D8AC_inl(u8 *a) {
    AreaStateF58 *g = (AreaStateF58 *)D_800ECF58;
    s32 t;

    if (func_800519E0(a, 0xD, g->unk60, D_8014C0BC) == 0) {
        t = g->unk64;
        M2C_FIELD(a, u8 **, 0x7C) = D_8014DE54;
        M2C_FIELD(a, s32 *, 0x3C) = t;
        return 1;
    }
    return 0;
}
void f_HandleKainenNpcActor(u8 *a)
{
    switch (a[4]) {
    case 0:
        if (func_8011D8AC_inl(a) == 0) {
            break;
        }
        a[0xB] = 0x40;
        a[0] = 9;
        *(s16 *)(a + 0x80) = 0x50;
        *(s16 *)(a + 0x82) = 0xA0;
        *(s16 *)(a + 0x84) = 0xA0;
        *(s16 *)(a + 0x86) = 0x120;
        *(s32 *)(a + 0x2C) = 0x26DE0000;
        *(s32 *)(a + 0x30) = 0xFC040000;
        a[0x2B] = 0;
        a[0x29] = 0;
        *(s16 *)(a + 0x58) = 0;
        *(s16 *)(a + 0x56) = 0;
        *(s16 *)(a + 0x54) = 0;
        *(s32 *)(a + 0x34) = 0x16440000;
        switch (a[3]) {
        case 0:
            *(s16 *)(a + 0x56) = 0xC00;
            a[0x7B] = 7;
            break;
        case 1:
            *(s16 *)(a + 0x56) = 0x400;
            a[0x7B] = 0;
            break;
        }
        func_80041718(a, a[0x7B], 0);
        a[4]++;
        break;
    case 1:
        switch (a[3]) {
        case 0:
            f_HandleKainenInteraction(a);
            break;
        case 1:
            switch (a[5]) {
            case 0:
                if (D_1F800207_9c67 == 10 && D_1F800160_71b4 < 0x1F40) {
                    break;
                }
                if (func_8007778C(a) == 0) {
                    if (D_800BF8BC == 0xFF) {
                        a[4] = 3;
                    }
                } else if (a[0x2B] == 3) {
                    a[0x7A] = 0x14;
                    func_80042354(1, 1);
                    func_80040D68(a, D_80148D2C);
                    a[0x70] = 2;
                    a[5]++;
                }
                break;
            case 1:
                a[1] = 1;
                func_80077E7C(a);
                if (a[0x70] == 0xFF) {
                    a[5]--;
                }
                break;
            }
            func_80041098(a);
            func_8004190C(a);
            break;
        }
        if (a[1] != 0) {
            func_800518FC(a);
            func_8011D82C(a);
        }
        a[0x2B] = 0;
        break;
    case 2:
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

extern u8 *D_800ECFB8;
extern u8 D_8014934C[];
void func_8011D82C(u8 *a) {
    u8 *base = D_800ECFB8;
    s32 *t = (s32 *)(base + 4);
    s32 v;

    switch (D_8014934C[a[0x46]]) {
    case 0:
        M2C_FIELD(M2C_FIELD(a, u8 **, 0xD0), u8 **, 0x40) = base + t[4];
        v = t[7];
        break;
    case 1:
        M2C_FIELD(M2C_FIELD(a, u8 **, 0xD0), u8 **, 0x40) = base + t[13];
        v = t[14];
        break;
    default:
        return;
    }
    M2C_FIELD(M2C_FIELD(a, u8 **, 0xDC), u8 **, 0x40) = base + v;
}

s32 func_8011D8AC(u8 *a) {
    AreaStateF58 *g = (AreaStateF58 *)D_800ECF58;
    s32 t;

    if (func_800519E0(a, 0xD, g->unk60, D_8014C0BC) == 0) {
        t = g->unk64;
        M2C_FIELD(a, u8 **, 0x7C) = D_8014DE54;
        M2C_FIELD(a, s32 *, 0x3C) = t;
        return 1;
    }
    return 0;
}

void f_HandleKainenNpcActor();
u8 *func_8011D910(u8 *a0, s32 a1) {
    u8 *r;

    if ((r = func_8007A980(3, 9, 0)) == NULL) {
        return NULL;
    }
    r[2] = 6;
    r[3] = a1;
    *(void **)(r + 0x1C) = f_HandleKainenNpcActor;
    if (r[3] == 0) {
        *(void **)(r + 0x10) = a0 + 0x60;
    }
    return r;
}

void func_8012185C(void *arg0);
void func_8012175C(u8 *a);
void func_801217F4(u8 *a);
void f_HandleFeedChicksSceneActor(u8 *a)
{
    switch (a[4]) {
    case 0:
        f_InitializeFeedChicksSceneActor(a);
        return;
    case 1:
        func_8007778C(a);
        if (a[0x2B] != 0) {
            a[0x2B]--;
        } else {
            switch (a[5]) {
            case 0:
                func_80076D68(a);
                if (a[3] == 3 || (D_800BF809 == 0 && D_1F800137 == 0)) {
                    if (a[3] & 1) {
                        f_UpdateFeedChicksActorEndpointTransit(a);
                    } else {
                        f_UpdateFeedChicksActorSplinePatrol(a);
                    }
                    func_8012185C(a);
                }
                break;
            case 1:
                if (a[3] == 3) {
                    func_8011F088(a);
                    func_8012185C(a);
                } else if (D_800BF809 == 0 && D_1F800137 == 0) {
                    f_UpdateFeedChicksActorRoaming(a);
                    func_8012185C(a);
                }
                break;
            case 2:
                if (D_800BF809 == 0) {
                    f_UpdateFeedChicksActorTombaReaction(a);
                }
                break;
            case 3:
                if (a[3] == 3 || (D_800BF809 == 0 && D_1F800137 == 0)) {
                    f_UpdateFeedChicksActorRecoveryOrExit(a);
                    func_80076D68(a);
                    func_80076D68(a);
                    func_80076D68(a);
                }
                break;
            case 4:
                func_8011FC78(a);
                func_8012185C(a);
                break;
            case 5:
                func_80076D68(a);
                func_80120C50(a);
                break;
            }
        }
        a[0x29] = 0;
        if (a[1] != 0) {
            func_800518FC(a);
        }
        break;
    case 2:
        func_8007778C(a);
        switch (a[5]) {
        case 0:
        case 4:
        case 5:
        case 6:
            if (D_800BF809 == 0 && D_1F800137 == 0) {
                func_801206F4(a);
            }
            break;
        case 1:
            func_8012175C(a);
            break;
        case 11:
            func_801217F4(a);
            if (func_80080750(a, 0, 0) != 0) {
                a[4] = 3;
                return;
            }
            a[5] = 2;
        case 2:
        case 7:
        case 8:
            func_80120A64(a);
            break;
        case 3:
        case 9:
        case 10:
            break;
        }
        a[0x29] = 0;
        if (a[1] != 0) {
            func_800518FC(a);
        }
        break;
    case 3:
        if (a[0x1B] & 0x40) {
            a[0x1B] &= ~0x40;
        } else {
            M2C_FIELD(M2C_FIELD(a, u8 **, 0x10), s32 *, 0xC) = 0;
            func_8007A624(a);
        }
        break;
    }
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_InitializeFeedChicksSceneActor);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateFeedChicksActorSplinePatrol);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateFeedChicksActorEndpointTransit);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8011E7CC);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateFeedChicksActorRoaming);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8011F088);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateFeedChicksActorTombaReaction);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateFeedChicksActorRecoveryOrExit);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8011FC78);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_ResolveFeedChicksActorFacingAngle);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8011FF78);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_TryStartFeedChicksActorTombaReaction);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_AdvanceFeedChicksActorMotion);

extern u8 *D_80149460[];
s32 func_801205EC(u8 *a) {
    u8 *t;
    s16 r;
    s16 k;
    s32 y;
    s16 d;

    t = D_80149460[a[3]];
    t += F16(a, 0x6C) * 6 + 2;
    r = func_8009A450() & 0xF;
    k = 1;
    if (r >= 6) {
        k = 3;
        if (r < 11) {
            k = 2;
        }
    }
    if (F16(a, 0x68) == k) {
        F16(a, 0x42) = r;
        r = 3;
        F16(a, 0x4A) = 0;
    } else {
        y = *(u16 *)t + k * 0x96 - 0x32;
                d = y - FU16(a, 0x32);
        F16(a, 0x42) = d;
        if (d > 0) {
            F16(a, 0x48) = 0x800;
            F16(a, 0x4A) = 0x800;
            F16(a, 0x4C) = 0x40;
        } else {
            F16(a, 0x48) = -0x800;
            F16(a, 0x4A) = -0x800;
            F16(a, 0x4C) = -0x40;
        }
        r = 4;
    }
    F16(a, 0x68) = k;
    return r;
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_801206F4);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80120A64);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80120C50);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_HandleFeedTheChicksController);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_SelectFeedChicksNpcSpawn);

extern u8 D_800BF9F3;
void f_UpdateFeedChicksNpcPresence(u8 *a) {
    u8 x;

    F16(a, 0xA) = 0;
    x = D_800E7EAA;
    switch (a[3]) {
    case 0:
        if (D_1F800160_71b4 < 0x3265) {
            if (D_800BF9F3 & 2) {
                F16(a, 0xA) = 1;
            }
        } else {
            F16(a, 0xA) = 1;
        }
        break;
    case 1:
        if (!((u8)(x - 12) < 10)) {
            F16(a, 0xA) = 2;
        }
        break;
    case 3:
        if (D_1F800160_71b4 < 0x34BC || !((u8)x < 18)) {
            F16(a, 0xA) = 2;
        }
        break;
    case 5:
        if ((u8)x != 3 && ((u8)x != 10 || D_1F800160_71b4 >= 0x170D)) {
            F16(a, 0xA) = 1;
        }
        break;
    }
    if (F16(a, 0xA) != 0) {
        M2C_FIELD(a, s32 *, 0x10) = 0x1E;
    }
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8012138C);

s16 func_801214AC(u8 *a, s16 k) {
    s32 m = k << 5;

    if (((M2C_FIELD(a, s16 *, 0x66) - M2C_FIELD(a, s16 *, 0x56)) & 0xFFF) < 0x800) {
        if (M2C_FIELD(a, s16 *, 0x66) < M2C_FIELD(a, s16 *, 0x56)) {
            M2C_FIELD(a, s16 *, 0x66) += 0x1000;
        }
        return m;
    }
    if (M2C_FIELD(a, s16 *, 0x56) < M2C_FIELD(a, s16 *, 0x66)) {
        M2C_FIELD(a, s16 *, 0x66) -= 0x1000;
    }
    return -m;
}

extern s16 D_8014A240[];
s32 f_AdvanceFeedChicksActorTurn(u8 *a) {
    M2C_FIELD(a, s16 *, 0x56) += M2C_FIELD(a, s16 *, 0x50);
    if ((M2C_FIELD(a, s16 *, 0x50) > 0 && M2C_FIELD(a, s16 *, 0x56) >= M2C_FIELD(a, s16 *, 0x66)) ||
        (M2C_FIELD(a, s16 *, 0x50) < 0 && M2C_FIELD(a, s16 *, 0x56) <= M2C_FIELD(a, s16 *, 0x66))) {
        return 1;
    }
    return 0;
}

s32 func_80121574(void) {
    s32 r = func_8009A450() & 0xF;

    if (r < 5) {
        return 0x5A;
    }
    if (r < 11) {
        return 0x96;
    }
    return 0xD2;
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_CheckFeedChicksActorRoutePointDistance);

extern u8 D_8014E1A4[];
void func_8012175C(u8 *a) {
    if (a[6] == 0) {
        a[0x5E] = 0;
        a[0x1B] &= 0xBF;
        func_80077C40(a, D_8014E1A4, 7);
        func_80026100(6);
        func_80074590(0x99, 0, 0);
        M2C_FIELD(a, s16 *, 0x84) = 0x28;
        M2C_FIELD(a, s16 *, 0x86) = 0x50;
        a[6]++;
    }
    if (M2C_FIELD(a, s16 *, 0x72) == 0) {
        func_80076D68(a);
    }
}

extern s16 D_800E7ED6;
void func_801217F4(u8 *a) {
    if (a[3] == 0) {
        switch (M2C_FIELD(a, s16 *, 0x60)) {
        case 8:
        case 9:
        case 10:
        case 12:
        case 13:
        case 14:
            a[0x2A] = 1;
            return;
        case 3:
        case 4:
        case 5:
        case 16:
        case 17:
        case 18:
            a[0x2A] = 0xA;
            break;
        }
    }
}

void func_8012185C(void *arg0) {
    s16 temp_v1;

    temp_v1 = M2C_FIELD(M2C_FIELD(arg0, void **, 0x10), s16 *, 0xA);
    switch (temp_v1) {                              /* irregular */
    case 1:
        M2C_FIELD(arg0, s8 *, 4) = 3;
        return;
    case 2:
        M2C_FIELD(arg0, s8 *, 5) = 3;
        M2C_FIELD(arg0, s8 *, 6) = 0;
        M2C_FIELD(arg0, s8 *, 7) = 1;
        return;
    }
}

void f_SpawnFeedChicksNpc(u8 *a) {
    u8 *p = func_80072DDC((s32)a, 3, 2, 7);

    if (p != NULL) {
        M2C_FIELD(p, void **, 0x1C) = f_HandleFeedChicksSceneActor;
        p[3] = a[3];
        M2C_FIELD(p, s16 *, 0x6C) = M2C_FIELD(a, s16 *, 0x8);
        M2C_FIELD(a, u8 **, 0xC) = p;
        if (a[3] == 3) {
            M2C_FIELD(a, s32 *, 0x10) = 0x1E;
        } else {
            M2C_FIELD(a, s32 *, 0x10) = 0x546;
        }
    }
}

void func_80121918(s32 a, s32 b, s32 c) {
    u8 *p = func_80072DDC(a, 3, 2, 7);

    if (p != NULL) {
        M2C_FIELD(p, void **, 0x1C) = f_HandleFeedChicksSceneActor;
        p[0x3] = 6;
        M2C_FIELD(p, s16 *, 0x68) = b;
        p[0x5E] = c;
    }
}

extern u8 D_8014C02C[];
extern u8 D_8014E4EC[];
void func_80122D58(u8 *a);
void func_80121B44(u8 *a);
void func_80121CF8(u8 *a);
void func_80122CA4(u8 *a);
void func_80122BF4(u8 *a);
void func_80121978(u8 *a)
{
    u8 *g;

    switch (a[4]) {
    case 0:
        g = (u8 *)D_800ECF58;
        if (func_800519E0(a, 0x12, *(s32 *)(g + 0x74), D_8014C02C) != 0) {
            break;
        }
        *(s32 *)(a + 0x3C) = *(s32 *)(g + 0x78);
        func_80077C40(a, D_8014E4EC, 0);
        *(s16 *)(a + 0x80) = 0x8C;
        *(s16 *)(a + 0x82) = 0x118;
        *(s16 *)(a + 0x84) = 0x80;
        *(s16 *)(a + 0x86) = 0x100;
        a[0xB] = 0;
        a[0x2B] = 0;
        *(s16 *)(a + 0x44) = 0x180;
        a[0x47] = 0;
        a[4]++;
        break;
    case 1:
        switch (a[3]) {
        case 0:
            f_HandleNetBridgeCutsceneTrigger(a);
            break;
        case 1:
            func_80122D58(a);
            break;
        case 2:
            break;
        case 0x5F:
            f_HandleStuckFishhookQuestNpc(a);
            break;
        case 0x60:
            func_80121B44(a);
            break;
        case 0x61:
            func_80121CF8(a);
            break;
        case 0x62:
            func_80122CA4(a);
            break;
        case 0x63:
            func_8018BF08(a);
            break;
        }
        func_80122BF4(a);
        a[0x2B] = 0;
        break;
    case 2:
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

extern u8 D_801494B0[];
void func_80121B44(u8 *a) {
    u8 k;

    switch (a[5]) {
    case 0:
        a[0] = 9;
        H_f12c(a, 0x80) = 0x50;
        H_f12c(a, 0x82) = 0xA0;
        H_f12c(a, 0x84) = 0x80;
        H_f12c(a, 0x86) = 0xE0;
        a[0xB] = 0;
        a[5]++;
        func_80077CFC(a, D_8014E4EC, 4, 4);
        H_f12c(a, 0x56) = 0xC00;
        a[0x5E] = 0;
        break;
    case 1:
        k = a[0x2B];
        if (k == 3) {
            func_80042354(1, 1);
            if (a[0x5E] == 0) {
                a[5]++;
                func_80077CFC(a, D_8014E4EC, 9, 4);
                a[0x5E] = 1;
            } else {
                a[5] = k;
            }
        }
        break;
    case 2:
        H_f12c(a, 0x32) += 0x50;
        H_f12c(a, 0x36) += 0x50;
        if (a[0x79] != 0) {
            a[5]++;
        }
        break;
    case 3:
        a[5]++;
        func_80040CDC(a, D_8014E4EC, D_801494B0);
        a[0x70] = 1;
        break;
    case 4:
        func_80041098(a);
        if (a[0x70] == 0xFF) {
            a[5] = 1;
            func_80042310();
        }
        break;
    }
    func_8004190C(a);
    func_8007778C(a);
    func_800518FC(a);
}

extern u8 D_801494D0[];
void func_80121CF8(u8 *a)
{
    switch (a[5]) {
    case 0:
        a[0] = 9;
        M2C_FIELD(a, s16 *, 0x80) = 0x50;
        M2C_FIELD(a, s16 *, 0x82) = 0xA0;
        M2C_FIELD(a, s16 *, 0x84) = 0x80;
        a[5] = 1;
        M2C_FIELD(a, s16 *, 0x86) = 0xE0;
        a[0xB] = 0;
        func_80077CFC(a, D_8014E4EC, 0, 4);
        break;
    case 1:
        if (a[0x2B] == 3) {
            a[5] = 2;
            func_80042354(1, 1);
        }
        break;
    case 2:
        a[5]++;
        func_80040CDC(a, D_8014E4EC, D_801494D0);
        a[0x70] = 1;
        break;
    case 3:
        func_80041098(a);
        if (a[0x70] == 0xFF) {
            a[5] = 1;
            func_80042310();
        }
        break;
    }
    func_8004190C(a);
    func_8007778C(a);
    func_800518FC(a);
}

extern u8 D_8014959C[];
extern u8 D_8014967C[];
extern u8 D_80149684[];
extern u8 D_800BF9B5;
extern u8 D_800E806C;
s32 f_FinishStuckFishhookLineSequence(u8 *a) {
    switch (a[6]) {
    case 0:
        H_f12c(a, 0x40) = 0x41;
        a[6]++;
    case 1:
        if (--H_f12c(a, 0x40) == -1) {
            func_80077C40(a, D_8014E4EC, 7);
            a[6]++;
        }
        break;
    case 2:
        if (D_800BF9B5 == 4 && a[0x79] != 0) {
            a[0x47] = 0;
            a[6]++;
        }
        break;
    case 3:
        a[6]++;
        func_80040CDC(a, D_8014E4EC, D_8014959C);
        a[0x70] = 1;
        break;
    case 4:
        func_80041098(a);
        if (a[0x70] == 0xFF) {
            a[6]++;
            if (D_800BFAF9 == 0) {
                func_80040CDC(a, D_8014E4EC, D_8014967C);
            } else {
                func_80040CDC(a, D_8014E4EC, D_80149684);
            }
            a[0x70] = 1;
        }
        break;
    case 5:
        func_80041098(a);
        if (a[0x70] == 0xFF) {
            func_80042310();
            D_800E806C = 0;
            return 1;
        }
        break;
    }
    return 0;
}

extern u8 D_80149754[];
extern u8 D_80149774[];
extern u8 D_8014977C[];
s32 func_80121FD8(u8 *p) {
    switch (p[6]) {
    case 0:
        if (p[0x2B] == 3) {
            p[6] = 1;
            func_80042354(1, 1);
        }
        break;
    case 1:
        p[6] = 2;
        if (D_800BF870.itemCounts[0x45] != 0) {
            func_80040CDC(p, D_8014E4EC, D_80149754);
        } else if (D_800BF870.pad1[0x86] != 0xFF) {
            func_80040CDC(p, D_8014E4EC, D_80149774);
        } else {
            func_80040CDC(p, D_8014E4EC, D_8014977C);
        }
        p[0x70] = 1;
        break;
    case 2:
        func_80041098(p);
        if (p[0x70] == 0xFF) {
            func_80042310();
            return 1;
        }
        break;
    }
    return 0;
}

#define P(p, o) (*(u8 **)((u8 *)(p) + (o)))
extern u8 D_801494FC[];
extern u8 D_80149564[];
extern u8 *D_800BF868;
extern u8 D_800BF8F6;
extern u8 D_800BF8F7;
extern s32 D_800ECFCC;
u8 *func_80072DDC();
void func_80127798();
/* func_80122FAC, inlined */
static inline s32 func_80122FAC_inl(u8 *a) {
    s32 one = 1;

    switch (a[6]) {
    case 0:
        if (a[0x2B] == 3) {
            a[6] = one;
            func_80042354(1, 1);
            D_800BF870.pad1[0x144] = one;
        }
        break;
    case 1:
        a[6] = 2;
        func_80040CDC(a, D_8014E4EC, D_801494FC);
        a[0x70] = 1;
        break;
    case 2:
        func_80041098(a);
        if (a[0x70] == 0xFF) {
            func_80042310();
            func_80040B48(0x42);
            D_800BF870.pad1[0x144] = 2;
            return 1;
        }
        break;
    }
    return 0;
}
/* func_801230A4, inlined */
static inline s32 func_801230A4_inl(u8 *p) {
    switch (p[6]) {
    case 0:
        if (p[0x2B] == 3) {
            p[6] = 1;
            func_80042354(1, 1);
        }
        break;
    case 1:
        p[6] = 2;
        func_80040CDC(p, D_8014E4EC, D_80149564);
        p[0x70] = 1;
        break;
    case 2:
        func_80041098(p);
        if (p[0x70] == 0xFF) {
            func_80042310();
            return 1;
        }
        break;
    }
    return 0;
}
void f_HandleStuckFishhookQuestNpc(u8 *a)
{
    u8 *e = D_800E7E80;
    GameState *g;
    GameState *g2;
    u8 *p;
    s32 r;
    s32 r2;

    switch (a[5]) {
    case 0:
        a[0] = 9;
        H_f12c(a, 0x80) = 0x50;
        H_f12c(a, 0x82) = 0xA0;
        H_f12c(a, 0x84) = 0x80;
        H_f12c(a, 0x86) = 0xE0;
        H_f12c(a, 0x56) = -0x400;
        a[0xB] = 1;
        H_f12c(a, 0x54) = 0;
        H_f12c(a, 0x58) = 0;
        a[0x47] = 3;
        a[5]++;
        func_8007ADDC(a);
        break;
    case 1:
        g = &D_800BF870;
        if (g->pad1[0x85] == 0xFF) {
            a[5] = 5;
            a[0x47] = 0;
            break;
        }
        p = func_80072DDC(a, 1, 2, 0x2F);
        *(void **)(p + 0x1C) = func_80127798;
        if (p == NULL) {
            break;
        }
        D_800BF868 = p;
        if (g->pad1[0x144] == 0) {
            a[5] = 2;
        } else {
            a[5] = 3;
        }
        break;
    case 2:
        g2 = &D_800BF870;
        if (g2->pad1[0x144] == 3) {
            a[5] = 4;
            a[6] = 0;
            break;
        }
        r = func_80122FAC_inl(a);
        if (r != 0) {
            a[5]++;
            a[6] = 0;
        }
        break;
    case 3:
        if (D_800BF9B5 == 3) {
            a[5] = 4;
            a[6] = 0;
            break;
        }
        r = func_801230A4_inl(a);
        if (r != 0) {
            a[6] = 0;
        }
        break;
    case 4:
        r = f_FinishStuckFishhookLineSequence(a);
        if (r != 0) {
            a[5]++;
            a[6] = 0;
        }
        break;
    case 5:
        r = func_80121FD8(a);
        if (r != 0) {
            a[6] = 0;
        }
        break;
    }
    switch (a[7]) {
    case 0:
        if (D_1F800207_9c67 < 0x19) {
            r2 = 0;
            break;
        }
        if (func_800519E0(a, 0x12, D_800ECFCC, D_8014C02C) != 0) {
            r2 = 1;
            break;
        }
        a[7]++;
        if (D_800BF8F6 == 0xFF) {
            func_80077C40(a, D_8014E4EC, 4);
        } else {
            func_80077C40(a, D_8014E4EC, 0xF);
        }
        r2 = 1;
        break;
    case 1:
        r2 = 1;
        if (D_1F800207_9c67 < 0x19) {
            func_8007ADDC(a);
            r2 = 0;
            a[7]--;
        }
        break;
    }
    if (r2 == 0) {
        if (D_800BF8F7 == 0xFF) {
            a[4] = 3;
        }
        return;
    }
    if (D_1F800137 != 0 || (u8)(e[0x2A] - 0x20) < 4) {
        a[1] = 1;
        func_80077E7C(a);
    } else if (a[0x47] == 3 && D_1F800162 < -0xCE3) {
        a[1] = 2;
        func_80077E7C(a);
    }
    if (a[1] != 0) {
        func_8004190C(a);
        func_800518FC(a);
    }
}

extern u8 D_80149794[];
extern u8 D_80149854[];
extern u16 D_800BF830_3521;
/* func_801232DC, inlined */
static inline s32 func_801232DC_inl(u8 *a) {
    switch (a[6]) {
    case 0:
        a[6] = 1;
        func_80040CDC(a, D_8014E4EC, D_80149794);
        a[0x70] = 1;
        D_800BF870.pad1[0x17A] = 0;
        break;
    case 1:
        func_80041098(a);
        if (a[0x70] == 0xFF) {
            a[6]++;
        }
        break;
    case 2:
        if (D_800BF830_3521 == 0xFFFF) {
            a[6] = 3;
            D_800BF870.pad1[0x16C] = 1;
            func_80042310();
        }
        break;
    case 3:
        a[6] = 0;
        return 1;
    }
    return 0;
}
/* func_801233DC, inlined */
static inline s32 func_801233DC_inl(u8 *a) {
    switch (a[6]) {
    case 0:
        a[6] = 1;
        func_80040CDC(a, D_8014E4EC, D_80149854);
        a[0x70] = 1;
        break;
    case 1:
        func_80041098(a);
        if (a[0x70] == 0xFF) {
            a[6]++;
            func_80042310();
        }
        break;
    case 2:
        a[6] = 0;
        return 1;
    }
    return 0;
}
void f_HandleNetBridgeCutsceneTrigger(u8 *a)
{
    u8 *e = D_800E7E80;
    GameState *g = &D_800BF870;
    u8 f = g->pad1[0x16C];
    u8 k;

    if (f >= 2) {
        a[3] = 1;
        a[5] = 0;
        a[6] = 0;
        a[7] = 0;
        return;
    }
    switch (a[5]) {
    case 0:
        H_f12c(a, 0x80) = 0x3C;
        H_f12c(a, 0x82) = 0x78;
        H_f12c(a, 0x84) = 0x80;
        a[5] = 1;
        H_f12c(a, 0x86) = 0xE0;
        if (g->pad1[0x16C] == 0) {
            a[0] = 2;
        } else {
            a[0] = 9;
        }
        H_f12c(a, 0x2E) = 0x3958;
        H_f12c(a, 0x32) = -0x822;
        H_f12c(a, 0x36) = 0x10CC;
        H_f12c(a, 0x56) = 0xC00;
        a[0x2A] = 0x10;
        a[0x2B] = 0;
        func_80077CFC(a, D_8014E4EC, 4, 4);
        a[0xB] = 1;
        a[0x47] = 0;
        break;
    case 1:
        if (f == 0) {
            if ((u8)(e[0x2A] - 0x10) < 2 && H_f12c(e, 0x36) >= 0x1109) {
                H_f12c(e, 0x36) = 0x1108;
                if (e[0x29] != 0) {
                    func_80054198(e);
                    a[5] = 2;
                    func_80042354(1, 1);
                }
            }
        } else if ((u8)(e[0x2A] - 0x10) < 2 && H_f12c(e, 0x36) >= 0x111D) {
            H_f12c(e, 0x36) = 0x111C;
        } else if ((k = a[0x2B]) == 3 && e[0x29] != 0) {
            func_80054198(e);
            a[5] = k;
            func_80042354(1, 1);
        }
        break;
    case 2:
        if (func_801232DC_inl(a) != 0) {
            a[5] = 1;
            a[0] = 9;
        }
        break;
    case 3:
        if (func_801233DC_inl(a) != 0) {
            a[5] = 1;
        }
        break;
    }
    if (func_8007778C(a) != 0) {
        func_8004190C(a);
        func_800518FC(a);
    }
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80122974);

extern s16 D_1F8000C8[];
void func_80122BF4(u8 *a) {
    u8 *p;
    s16 *v;
    s16 *w;

    if (a[0xB] == 1) {
        p = M2C_FIELD(a, u8 **, 0xE8);
        v = D_1F8000C0;
        v[0] = 0;
        v[1] = -0x77;
        v[2] = 0;
        w = D_1F8000C8;
        func_800844C0(p + 0x18, v, w);
        M2C_FIELD(a, s16 *, 0x4E) = w[0] + M2C_FIELD(p, s16 *, 0x2C);
        M2C_FIELD(a, s16 *, 0x50) = w[1] + M2C_FIELD(p, s16 *, 0x30);
        M2C_FIELD(a, s16 *, 0x52) = w[2] + M2C_FIELD(p, s16 *, 0x34);
    }
}

extern u8 D_800BF8B9;
void func_80122CA4(u8 *a) {
    if (D_800BF8B9 != 0xFF) {
        a[4] = 3;
        return;
    }
    switch (a[6]) {
    case 0:
        a[6]++;
        a[0] = 2;
        M2C_FIELD(a, s16 *, 0x56) = 0x400;
        a[0xB] = 0;
        M2C_FIELD(a, s16 *, 0x40) = 8;
        func_80077CFC(a, D_8014E4EC, 4, 4);
        break;
    case 1:
        func_80076D68(a);
        break;
    }
    func_800518FC(a);
    func_8007778C(a);
}

void func_80122D58(u8 *a) {
    switch (a[5]) {
    case 0:
        a[5]++;
        a[0] = 2;
        a[0xB] = 1;
        M2C_FIELD(a, s16 *, 0x2E) = 0x3900;
        M2C_FIELD(a, s16 *, 0x32) = -0xAE0;
        M2C_FIELD(a, s16 *, 0x36) = 0x240;
        M2C_FIELD(a, s16 *, 0x56) = 0x400;
        func_80077CFC(a, D_8014E4EC, 4, 4);
        break;
    }
    if (func_8007778C(a) != 0) {
        func_80076D68(a);
        func_800518FC(a);
    }
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80122DF0);

s32 func_80122F0C(s32 a) {
    u8 *p = func_80072DDC(a, 0, 3, 16);

    if (p == NULL) {
        return 0;
    }
    p[0x3] = 6;
    M2C_FIELD(p, void **, 0x1C) = f_HandleTownQuestRewardVisualActor;
    return 1;
}

s32 func_80122F5C(s32 a) {
    u8 *p = func_80072DDC(a, 0, 3, 16);

    if (p == NULL) {
        return 0;
    }
    p[0x3] = 7;
    M2C_FIELD(p, void **, 0x1C) = f_HandleTownQuestRewardVisualActor;
    return 1;
}

s32 func_80122FAC(u8 *a) {
    s32 one = 1;

    switch (a[6]) {
    case 0:
        if (a[0x2B] == 3) {
            a[6] = one;
            func_80042354(1, 1);
            D_800BF9B5 = one;
        }
        break;
    case 1:
        a[6] = 2;
        func_80040CDC(a, D_8014E4EC, D_801494FC);
        a[0x70] = 1;
        break;
    case 2:
        func_80041098(a);
        if (a[0x70] == 0xFF) {
            func_80042310();
            func_80040B48(0x42);
            D_800BF9B5 = 2;
            return 1;
        }
        break;
    }
    return 0;
}

s32 func_801230A4(u8 *p) {
    switch (p[6]) {
    case 0:
        if (p[0x2B] == 3) {
            p[6] = 1;
            func_80042354(1, 1);
        }
        break;
    case 1:
        p[6] = 2;
        func_80040CDC(p, D_8014E4EC, D_80149564);
        p[0x70] = 1;
        break;
    case 2:
        func_80041098(p);
        if (p[0x70] == 0xFF) {
            func_80042310();
            return 1;
        }
        break;
    }
    return 0;
}

s32 func_80123180(s32 arg0) {
    M2C_FIELD(arg0, s32 *, 0x14) = f_SpawnGoldFishhookPickup(arg0, 1);
    return 1;
}

s32 func_801231B0(void) {
    func_8004D650(0x45, 1);
    func_8004ED0C(0x45, 4);
    return 1;
}

s32 func_801231E0(u8 *a, s32 r) {
    switch (a[7]) {
    case 0:
        if (D_1F800207_9c67 < 0x19) {
            r = 0;
            break;
        }
        if (func_800519E0(a, 0x12, D_800ECFCC, D_8014C02C) != 0) {
            r = 1;
            break;
        }
        a[7]++;
        if (D_800BF8F6 == 0xFF) {
            func_80077C40(a, D_8014E4EC, 4);
        } else {
            func_80077C40(a, D_8014E4EC, 0xF);
        }
        r = 1;
        break;
    case 1:
        r = 1;
        if (D_1F800207_9c67 < 0x19) {
            func_8007ADDC(a, 1);
            r = 0;
            a[7]--;
        }
        break;
    }
    return r;
}

extern s8 D_800BF9DD_c419;
s32 func_801232DC(u8 *a) {
    switch (a[6]) {
    case 0:
        a[6] = 1;
        func_80040CDC(a, D_8014E4EC, D_80149794);
        a[0x70] = 1;
        D_800BF9EB = 0;
        break;
    case 1:
        func_80041098(a);
        if (a[0x70] == 0xFF) {
            a[6]++;
        }
        break;
    case 2:
        if (D_800BF830_3521 == 0xFFFF) {
            a[6] = 3;
            D_800BF9DD_c419 = 1;
            func_80042310();
        }
        break;
    case 3:
        a[6] = 0;
        return 1;
    }
    return 0;
}

s32 func_801233DC(u8 *a) {
    switch (a[6]) {
    case 0:
        a[6] = 1;
        func_80040CDC(a, D_8014E4EC, D_80149854);
        a[0x70] = 1;
        break;
    case 1:
        func_80041098(a);
        if (a[0x70] == 0xFF) {
            a[6]++;
            func_80042310();
        }
        break;
    case 2:
        a[6] = 0;
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_801234A4);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80123C94);

#define H_f12c(p, o) (*(s16 *)((u8 *)(p) + (o)))
void f_AnimateSmallFishSuspendedMotion(u8 *a) {
    switch (a[5]) {
    case 0:
        a[5]++;
        func_80077B38(a, D_8014C808, 3);
        H_f12c(a, 0x40) = 0x5A;
        H_f12c(a, 0x48) = 0x10;
        H_f12c(a, 0x4E) = -2;
        H_f12c(a, 0x64) = 0;
        H_f12c(a, 0x68) = 0;
    case 1:
    case 3:
        if (--H_f12c(a, 0x40) == 0) {
            a[5]++;
        }
        break;
    case 2:
        H_f12c(a, 0x64) += H_f12c(a, 0x48);
        H_f12c(a, 0x48) += H_f12c(a, 0x4E);
        if ((H_f12c(a, 0x56) += 0x80) == 0x800) {
            H_f12c(a, 0x40) = 0x5A;
            H_f12c(a, 0x48) = -0x10;
            H_f12c(a, 0x4E) = 2;
            a[5]++;
        }
        break;
    case 4:
        H_f12c(a, 0x64) += H_f12c(a, 0x48);
        H_f12c(a, 0x48) += H_f12c(a, 0x4E);
        if ((H_f12c(a, 0x56) -= 0x80) == 0) {
            a[5] = 1;
            H_f12c(a, 0x40) = 0x5A;
            H_f12c(a, 0x48) = 0x10;
            H_f12c(a, 0x4E) = -2;
        }
        break;
    }
    func_80077B5C(a);
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_AnimateReleasedSmallFishBounce);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_801241BC);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_AnimateNetBridgeFishIdle);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_801244E8);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateNetBridgeFishAfterCollapse);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_AnimateNetBridgeFishDropSequence);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80124C6C);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_HandleSmallFishActor);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_SpawnSmallFishActor);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_801253E8);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_801255CC);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_DeliverCarriedChickToNest);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80125C4C);

void func_80125FE0(u8 *a);
void func_801261FC(u8 *a);
void func_80125E0C(u8 *a) {
    switch (a[4]) {
    case 0:
        func_801253E8(a);
        break;
    case 1:
        func_8007778C(a);
        switch (a[5]) {
        case 0:
            func_80125FE0(a);
            break;
        case 1:
            func_801255CC(a);
            break;
        case 2:
            f_DeliverCarriedChickToNest(a);
            break;
        }
        if (a[1] != 0) {
            func_800518FC(a);
        }
        break;
    case 2:
        func_8007778C(a);
        switch (a[5]) {
        case 0 ... 1:
            break;
        case 2 ... 3:
            func_801261FC(a);
            break;
        }
        if (a[1] != 0) {
            func_800518FC(a);
        }
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

extern u8 D_800BF9F2;
void func_80125E0C();
s32 f_EnsureCarriedChickActor(u8 *a) {
    s32 n;
    u8 *p;

    if (a[3] == 0) {
        n = D_800BF9F2 & 0xF;
    } else {
        n = D_800BF9F2 >> 4;
    }
    if (n == 0) {
        p = func_80072DDC(a, 2, 2, 0x13);
        if (p != NULL) {
            M2C_FIELD(p, void **, 0x1C) = func_80125E0C;
            p[3] = a[3];
        }
    }
    return n;
}

void func_80125FE0(u8 *a) {
    s16 v = M2C_FIELD(M2C_FIELD(M2C_FIELD(a, u8 **, 0x10), u8 **, 0xC4), s16 *, 0x8);

    if (v > 0x800) {
        v |= 0xF000;
    }
    M2C_FIELD(a, s16 *, 0x54) = v >> 1;
    if (a[0x2B] != 0) {
        func_80125C4C(a);
    }
}

s32 f_UpdateCarriedChickCollision(u8 *a) {
    switch (a[7]) {
    case 0:
        if (M2C_FIELD(a, s16 *, 0x4A) >= 0) {
            a[0xBF] = 2;
            a[7]++;
        }
    case 1:
        M2C_FIELD(a, s16 *, 0x4A) += 0x200;
        if (M2C_FIELD(a, s16 *, 0x4A) > 0x2000) {
            M2C_FIELD(a, s16 *, 0x4A) = 0x2000;
        }
        if (a[0x29] != 0) {
            a[0xBF] = 0;
            return 1;
        }
        break;
    }
    return 0;
}

void func_801260CC(void *arg0) {
    if (func_80077768(M2C_FIELD(arg0, u8 *, 0x46) * 0x10, M2C_FIELD(arg0, s16 *, 0x56), 0) != 0) {
        M2C_FIELD(arg0, s16 *, 0x44) = -0x800;
        M2C_FIELD(arg0, s8 *, 0x5F) = 1;
    } else {
        M2C_FIELD(arg0, s16 *, 0x44) = 0x800;
        M2C_FIELD(arg0, s8 *, 0x5F) = 0;
    }
    M2C_FIELD(arg0, s16 *, 0x4A) = -0x1800;
    M2C_FIELD(arg0, s8 *, 0xBF) = 1;
    M2C_FIELD(arg0, s8 *, 0x2B) = 0;
}

void f_UpdateCarriedChickMotion(void *arg0) {
    s16 temp_v1;

    temp_v1 = M2C_FIELD(arg0, s16 *, 0x44);
    M2C_FIELD(arg0, s32 *, 0x2C) = (s32) (M2C_FIELD(arg0, s32 *, 0x2C) + (temp_v1 * M2C_FIELD(arg0, s16 *, 0x48)));
    M2C_FIELD(arg0, s32 *, 0x34) = (s32) (M2C_FIELD(arg0, s32 *, 0x34) + (temp_v1 * M2C_FIELD(arg0, s16 *, 0x4C)));
    if (M2C_FIELD(arg0, u8 *, 0xBF) == 0) {
        if (M2C_FIELD(arg0, u8 *, 0x29) != 0) {
            M2C_FIELD(arg0, s32 *, 0x30) = (s32) (M2C_FIELD(arg0, s32 *, 0x30) + (M2C_FIELD(arg0, s16 *, 0x44) * M2C_FIELD(arg0, s16 *, 0x4A)));
        } else {
            M2C_FIELD(arg0, u16 *, 0x32) = (u16) (M2C_FIELD(arg0, u16 *, 0x32) + 8);
        }
    } else {
        M2C_FIELD(arg0, u16 *, 0x32) = (u16) (M2C_FIELD(arg0, u16 *, 0x32) + ((s32) ((u16) M2C_FIELD(arg0, s16 *, 0x4A) << 0x10) >> 0x18));
    }
    M2C_FIELD(arg0, u16 *, 0x54) = (u16) ((M2C_FIELD(arg0, u16 *, 0x54) + ((s32) ((u16) M2C_FIELD(arg0, s16 *, 0x44) << 0x10) >> 0x14)) & 0xFFF);
}

void func_801261FC(u8 *a) {
    a[4] = 1;
    if (func_80077768(D_800E7ED6, M2C_FIELD(a, s16 *, 0x56), 0) != 0) {
        a[0x46] = (u32)(M2C_FIELD(a, s16 *, 0x56) + 0x800) >> 4;
    } else {
        a[0x46] = M2C_FIELD(a, u16 *, 0x56) >> 4;
    }
    func_80125C4C(a);
}

extern u8 D_800BF8F1;
void func_80127420(void *arg0);
void func_80126264(u8 *a)
{
    s32 r;
    s32 k;

    switch (a[4]) {
    case 0:
        f_InitializeNestChickActor(a);
        break;
    case 1:
        func_8007778C(a);
        switch (a[5]) {
        case 0:
            func_80127420(a);
            break;
        case 1:
            func_801266C8(a);
            break;
        case 2:
            func_8012681C(a);
            break;
        case 3:
            f_UpdateNestChickQuestState(a);
            break;
        }
        func_80077B5C(a);
        break;
    case 2:
        k = a[5];
        if (k < 4) if (k >= 2) {
            if (D_800BF8F1 == 0) {
                r = func_80040B48(0x3D);
            } else {
                r = func_80040C00(0x3C);
            }
            if (r >= 0) {
                func_8004D4C4(a[0x5E] == 0 ? 0x39 : 0x38, 1);
                func_8004B0D8(a);
                a[0x5E] |= 8;
                if (a[3] == 1) {
                    a[0x5E] <<= 4;
                    D_800BF870.pad1[0x181] &= 0xF;
                } else {
                    D_800BF870.pad1[0x181] &= 0xF0;
                }
                D_800BF870.pad1[0x181] |= a[0x5E];
            }
            a[4] = 3;
        }
        func_8007778C(a);
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

typedef struct { u8 pad[0xC0]; u8 *parts[2]; } NestParent;
void f_InitializeNestChickActor(u8 *a) {
    NestParent *l;
    s32 m = a[3];
    s32 b;

    a[4]++;
    b = D_800ECF80;
    a[0xB] = 0x10;
    a[0xD] = 0;
    H_f12c(a, 0x5A) = 0;
    a[8] = 0;
    *(s32 *)(a + 0x3C) = b;
    switch (m) {
    case 0:
    case 1:
        func_80077B38(a, D_8014C808, 0x16);
        l = *(NestParent **)(a + 0x10);
        a[0x47] = 0;
        H_f12c(a, 0x2E) = H_f12c(l->parts[H_f12c(a, 0x60)], 0x2C);
        H_f12c(a, 0x32) = H_f12c(l->parts[H_f12c(a, 0x60)], 0x30);
        H_f12c(a, 0x36) = H_f12c(l->parts[H_f12c(a, 0x60)], 0x34);
        if (H_f12c(a, 0x60) & 1) {
            a[0x2A] = 0xA;
        } else {
            a[0x2A] = 1;
        }
        break;
    case 2:
    case 4:
    case 5:
        if (a[3] & 1) {
            func_80077B38(a, D_8014C808, 0x1B);
            H_f12c(a, 0x40) = 1;
        } else if (a[3] & 2) {
            func_80077B38(a, D_8014C808, 0x17);
            H_f12c(a, 0x40) = 4;
        } else {
            func_80077B38(a, D_8014C808, 0xD);
            H_f12c(a, 0x40) = 1;
        }
        a[0x47] = 1;
        H_f12c(a, 0x2E) = 0x1040;
        H_f12c(a, 0x32) = -0xA8C;
        H_f12c(a, 0x36) = 0x1A41;
        if (a[3] & 1) {
            H_f12c(a, 0x4A) = -0x1600;
        } else if (H_f12c(a, 0x68) == 0) {
            H_f12c(a, 0x4A) = -0x1A00;
        } else {
            H_f12c(a, 0x4A) = -0x1200;
        }
        H_f12c(a, 0x50) = 0x100;
        H_f12c(a, 0x44) = 0x800;
        H_f12c(a, 0x64) = 1;
        a[0x2A] = 3;
        a[5] = 3;
        break;
    case 3:
        func_80077B38(a, D_8014C808, 0x17);
        H_f12c(a, 0x2E) = 0x1040;
        H_f12c(a, 0x32) = -0xABC;
        if (H_f12c(a, 0x68) & 1) {
            H_f12c(a, 0x36) = 0x1B41;
        } else {
            H_f12c(a, 0x36) = 0x1BD1;
        }
        H_f12c(a, 0x44) = 0;
        H_f12c(a, 0x40) = 1;
        H_f12c(a, 0x64) = 0;
        a[0x2A] = 3;
        a[0x47] = 1;
        a[5] = 3;
        a[6] = 1;
        break;
    }
    func_8004766C(a);
    func_80049760(a);
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_801266C8);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8012681C);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80126AA8);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_HandleFeedChicksInventoryUse);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_RestoreFedChicksFromProgress);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateNestChickQuestState);

void func_80126264();
s32 f_SpawnNestChickFromParent(u8 *a) {
    u8 *p = func_80072DDC(a, 0, 2, 0x14);

    if (p != NULL) {
        M2C_FIELD(p, void **, 0x1C) = func_80126264;
        p[3] = a[3];
        if (M2C_FIELD(a, u16 *, 0x7A) & 0x40) {
            M2C_FIELD(p, s16 *, 0x5C) = 0x343F;
            p[0x5E] = 4;
        } else {
            M2C_FIELD(p, s16 *, 0x5C) = 0x347F;
            p[0x5E] = 0;
        }
        M2C_FIELD(p, s16 *, 0x60) = (M2C_FIELD(a, u16 *, 0x7A) >> 4) & 3;
        return 1;
    }
    return 0;
}

void func_80127420(void *arg0) {
    if (M2C_FIELD(M2C_FIELD(arg0, void **, 0x10), u8 *, 0x5E) == 0) {
        M2C_FIELD(arg0, s16 *, 0x40) = 0x14;
        M2C_FIELD(arg0, s16 *, 0x4A) = 0x14;
        M2C_FIELD(arg0, s8 *, 5) = 1;
    }
}

void func_80127450(u8 *a) {
    switch (M2C_FIELD(a, s16 *, 0x64)) {
    case 1:
        if (M2C_FIELD(a, s16 *, 0x4A) >= 0) {
            M2C_FIELD(a, s16 *, 0x64)++;
        }
    case 2:
        M2C_FIELD(a, s16 *, 0x4A) += M2C_FIELD(a, s16 *, 0x50);
        if (M2C_FIELD(a, s16 *, 0x4A) > 0x2000) {
            M2C_FIELD(a, s16 *, 0x4A) = 0x2000;
        }
        break;
    }
}

extern u8 *D_1F800218;
typedef struct { u8 pad[0xC0]; u8 *parts[1]; } AreaPartsOwner;
s32 func_801274BC(u8 *a) {
    s16 d;

    d = M2C_FIELD(M2C_FIELD(a, AreaPartsOwner **, 0x10)->parts[M2C_FIELD(a, s16 *, 0x60)], s16 *, 0x2C) - M2C_FIELD(a, s16 *, 0x2E);
    if (d >= 0x259) {
        return 1;
    }
    if (d >= 0xFB) {
        return -1;
    }
    return 0;
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_DeliverChickItemToNest);

s32 f_FeedChicksAtNest(u8 *a) {
    u8 *e;
    u8 *g;

    e = func_80072DDC(a, 0, 2, 0x14);
    if (e != NULL) {
        func_8004D650(0x4D, 1);
        M2C_FIELD(e, void **, 0x1C) = func_80126264;
        e[3] = 4;
        g = (u8 *)&D_800BF870;
        M2C_FIELD(e, s16 *, 0x5C) = 0;
        if (g[0x82] == 1) {
            M2C_FIELD(e, s16 *, 0x68) = 0;
            g[0x82] |= 0x10;
            e[0x5E] = g[0x183] & 4;
        } else {
            M2C_FIELD(e, s16 *, 0x68) = 1;
            e[0x5E] = (g[0x183] >> 4) & 4;
        }
        func_8004ED94(e[0x5E] ? 0x4D : 0x4E, 0x41);
        M2C_FIELD(a, s32 *, 0x24) = 0x1E;
        return 1;
    }
    return 0;
}

void func_80126264();
s32 f_UseNishikiWingsAtNest(u8 *a) {
    u8 *p = func_80072DDC(a, 0, 2, 0x14);

    if (p != NULL) {
        func_8004D604(0x54, 1);
        M2C_FIELD(p, void **, 0x1C) = func_80126264;
        p[3] = 5;
        M2C_FIELD(p, s16 *, 0x5C) = 0;
        M2C_FIELD(a, s32 *, 0x24) = 0x1E;
        return 1;
    }
    return 0;
}

typedef struct {
    s16 x, y, z;
} SVec3Q;
#define W_d1fb(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define C0 (*(u8 **)(a + 0xC0))
extern s16 D_800E8078;
extern SVec3Q D_1F8000C0_cda2;
void func_80127798(u8 *a) {
    u8 *t;
    u8 *e;
    s16 dx, dz;
    s32 dy;
    s32 x, y, z;
    s32 ang;
    s16 n;
    s32 k;

    switch (a[4]) {
    case 0:
        if (func_80051B70(a, 0xC, 0x52) != 0) {
            return;
        }
        H_f12c(a, 0x2E) = 0x4F00;
        H_f12c(a, 0x32) = -0x12A2;
        H_f12c(a, 0x36) = 0x2A6C;
        a[0] = 1;
        a[0x29] = 0;
        H_f12c(a, 0x58) = -0xE3;
        a[4]++;
        H_f12c(C0, 0x38) = 0x1000;
        H_f12c(C0, 0x3A) = 0x1000;
        H_f12c(C0, 0x3C) = 0x1000;
        H_f12c(a, 0xB8) = 0x1400;
        H_f12c(a, 0xBA) = 0x1400;
        H_f12c(a, 0xBC) = 0x1400;
        H_f12c(a, 0x80) = 0x30;
        H_f12c(a, 0x82) = 0x60;
        H_f12c(a, 0x84) = 0x40;
        H_f12c(a, 0x86) = 0x40;
        a[0x2A] = 0x1D;
        func_80041194(a, 0, 0, 0);
        break;
    case 1:
        if ((u8)(D_1F800207_9c67 - 0x1D) < 3 || D_800BF9B5 == 1) {
            if (func_8007778C(a) != 0) {
                func_80051844(a);
            }
        }
        break;
    case 2:
        t = D_800E7E80;
        switch (a[5]) {
        case 1:
            if (t[0x147] != 0) {
                H_f12c(a, 0x58) = H_f12c(a, 0x62);
            } else {
                H_f12c(a, 0x58) = (0x1000 - H_f12c(a, 0x62)) & 0xFFF;
            }
            break;
        case 2:
            a[0] = 1;
            a[4] = 1;
            a[5] = 0;
            H_f12c(a, 0x58) = 0xE3;
            break;
        case 3:
            switch (a[6]) {
            case 0:
                D_800BF9B5 = 3;
                func_80042354(1, 1);
                func_80040B48(0x42);
                a[6]++;
                break;
            case 1:
                if (t[0x29] != 0) {
                    H_f12c(a, 0x40) = 6;
                    a[6]++;
                }
                break;
            case 2:
                if (--H_f12c(a, 0x40) == 0) {
                    t[4] = 4;
                    t[5] = 0x21;
                    t[6] = 0;
                    t[0x29] = 0;
                    t[0x147] = 1;
                    func_80054198(t);
                    func_80054D14(t, 0x71, 8);
                    a[6]++;
                    dz = 0x204C - H_f12c(t, 0x36);
                    dx = 0x49B3 - H_f12c(t, 0x2E);
                    dy = -0x56C - *(u16 *)(t + 0x32);
                    ang = func_80085690(-dz, dx);
                    n = 0x40;
                    H_f12c(t, 0x56) = (ang + 0x800) & 0xFFF;
                    H_f12c(a, 0x40) = 0x40;
                    x = (dx << 8) / n;
                    y = ((s16)dy << 8) / n;
                    z = (dz << 8) / n;
                    H_f12c(a, 0x4A) = -0x3000;
                    H_f12c(a, 0x4E) = x;
                    H_f12c(a, 0x50) = y;
                    H_f12c(a, 0x52) = z;
                    e = D_800E8008;
                    H_f12c(e, 0x6E) = -0x100;
                    e[0x64] = 1;
                    H_f12c(e, 0x70) = 0;
                    H_f12c(e, 0x6C) = -0x578;
                    func_80074590(0x25, 0, 0);
                }
                break;
            case 3:
                if (H_f12c(a, 0x40) != 0) {
                    H_f12c(a, 0x40)--;
                    W_d1fb(t, 0x2C) += H_f12c(a, 0x4E) << 8;
                    W_d1fb(t, 0x30) += H_f12c(a, 0x50) << 8;
                    W_d1fb(t, 0x34) += H_f12c(a, 0x52) << 8;
                    t[0x29] = 0;
                } else {
                    a[6]++;
                    D_800E8078 = 0x800;
                }
                if ((H_f12c(a, 0x4A) += 0x180) > 0x3000) {
                    H_f12c(a, 0x4A) = 0x3000;
                }
                W_d1fb(t, 0x30) += H_f12c(a, 0x4A) << 8;
                break;
            case 4:
                D_800BF9B5 = 4;
                H_f12c(t, 0x2E) = 0x49B3;
                H_f12c(t, 0x32) = -0x56C;
                H_f12c(t, 0x36) = 0x204C;
                t[0x29] = 1;
                t[0x2A] = 0x22;
                D_1F800207_9c67 = 0x22;
                a[4]++;
                break;
            }
            D_1F8000C0_cda2.x = 0;
            k = W_d1fb(t, 0xDC);
            D_1F8000C0_cda2.y = 0;
            D_1F8000C0_cda2.z = 0;
            func_8004BD64(a, 0, k, k, &D_1F8000C0_cda2);
            func_8006CBA8(t + 0x2C);
            break;
        }
        func_80051844(a);
        a[1] = 1;
        func_80077E7C(a);
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80127D1C);

void func_80127D1C();
s32 func_801280E8(u8 *a) {
    u8 *g = (u8 *)&D_800BF870;
    u8 *e;

    if (g[0xC6] & 2) {
        goto fail;
    }
    if (g[0x164] != 0) {
        return 0;
    }
    e = func_80072DDC(a, 0, 2, 0x56);
    if (e == NULL) {
    fail:
        return 0;
    }
    M2C_FIELD(e, void **, 0x1C) = func_80127D1C;
    M2C_FIELD(e, s16 *, 0x2E) = M2C_FIELD(a, s16 *, 0x2E);
    M2C_FIELD(e, s16 *, 0x32) = M2C_FIELD(a, s16 *, 0x32);
    M2C_FIELD(e, s16 *, 0x36) = M2C_FIELD(a, s16 *, 0x36);
    e[0x2A] = a[0x2A];
    g[0x164] = 1;
    func_8003116C(0x30, e + 0x2C, -0xA);
    func_80074590(0x37, 0x20, 0);
    return 1;
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_801281B8);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_InitializeRareFishOrBucketController);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_801284AC);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateBlueBucketPendulumMotion);

extern s8 D_1F800207[];
/* func_8012894C, inlined */
static inline s32 inl_8012894C(s32 arg0) {
    s32 var_v0;
    u8 temp_v1;
    void *temp_v0;

    temp_v1 = M2C_FIELD(arg0, u8 *, 5);
    switch (temp_v1) {                              /* irregular */
    case 0:
        temp_v0 = M2C_FIELD(arg0, void **, 0x10);
        if ((temp_v0 == NULL) || (M2C_FIELD(temp_v0, u8 *, 0x5E) == 2)) {
            M2C_FIELD(arg0, s8 *, 0xB) = 0;
            M2C_FIELD(arg0, void **, 0x10) = NULL;
            M2C_FIELD(arg0, u8 *, 5) = (u8) (M2C_FIELD(arg0, u8 *, 5) + 1);
        }
        var_v0 = (u8) *((u8 *)D_1F800207) < 6U;
        if (var_v0 != 0) {
            func_801281B8(arg0);
            return f_UpdateBlueBucketPendulumMotion(arg0);
        }
        return var_v0;
    case 1:
        var_v0 = func_801281B8(arg0);
        return var_v0;
    default:
        return 1;
    }
}
void f_HandleRareFishOrBucketSuspension(u8 *a) {
    u8 *p;

    switch (a[4]) {
    case 0:
        f_InitializeRareFishOrBucketController(a);
        break;
    case 1:
        switch (a[3]) {
        case 0:
            switch (a[5]) {
            case 0:
                p = M2C_FIELD(a, u8 **, 0x10);
                if (p == NULL || p[0x5E] == 2) {
                    a[0xB] = 0;
                    M2C_FIELD(a, u8 **, 0x10) = NULL;
                    a[5]++;
                }
            case 1:
                func_801281B8(a);
                break;
            }
            break;
        case 1:
            inl_8012894C((s32)a);
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

s32 func_801288D8(s32 arg0) {
    u8 temp_v1;
    void *temp_v0;

    temp_v1 = M2C_FIELD(arg0, u8 *, 5);
    switch (temp_v1) {                              /* irregular */
    case 0:
        temp_v0 = M2C_FIELD(arg0, void **, 0x10);
        if ((temp_v0 == NULL) || (M2C_FIELD(temp_v0, u8 *, 0x5E) == 2)) {
            M2C_FIELD(arg0, s8 *, 0xB) = 0;
            M2C_FIELD(arg0, void **, 0x10) = NULL;
            M2C_FIELD(arg0, u8 *, 5) = (u8) (M2C_FIELD(arg0, u8 *, 5) + 1);
        }
        /* fallthrough */
    case 1:
        return func_801281B8(arg0);
    default:
        return 1;
    }
}

s32 func_8012894C(s32 arg0) {
    s32 var_v0;
    u8 temp_v1;
    void *temp_v0;

    temp_v1 = M2C_FIELD(arg0, u8 *, 5);
    switch (temp_v1) {                              /* irregular */
    case 0:
        temp_v0 = M2C_FIELD(arg0, void **, 0x10);
        if ((temp_v0 == NULL) || (M2C_FIELD(temp_v0, u8 *, 0x5E) == 2)) {
            M2C_FIELD(arg0, s8 *, 0xB) = 0;
            M2C_FIELD(arg0, void **, 0x10) = NULL;
            M2C_FIELD(arg0, u8 *, 5) = (u8) (M2C_FIELD(arg0, u8 *, 5) + 1);
        }
        var_v0 = (u8) *((u8 *)D_1F800207) < 6U;
        if (var_v0 != 0) {
            func_801281B8(arg0);
            return f_UpdateBlueBucketPendulumMotion(arg0);
        }
        return var_v0;
    case 1:
        var_v0 = func_801281B8(arg0);
        /* Duplicate return node #9. Try simplifying control flow for better match */
        return var_v0;
    default:
        return 1;
    }
}

extern u8 D_8001B860[];
extern u8 *D_80149E50[];
extern u8 *D_800E7EB8;
void f_RunA00Event4ItemUseCutscene(u8 *a) {
    switch (a[6]) {
    case 0:
        func_80040CDC(a, D_8001B860, D_80149E50[D_800BF830]);
        a[0x70] = 2;
        a[6]++;
        break;
    case 1:
        if (a[0x70] == 0) {
            *(u8 **)(a + 0x10) = NULL;
            a[0x70] = 1;
            a[6]++;
        }
        break;
    case 2:
        if (*(u8 **)(a + 0x10) != NULL) {
            func_800440E4(D_800E7E80, 0xBD, 4);
            H_f12c(a, 0x40) = 0x28;
            a[6]++;
        }
        break;
    case 3:
        if (--H_f12c(a, 0x40) == 0) {
            func_80040C00(4);
            func_800440E4(D_800E7E80, 0xBE, 4);
            a[6]++;
        }
        break;
    case 4:
        if (D_800E7EB8[4] == 2) {
            func_80074810(3, 0);
            a[6]++;
        }
    case 5:
        if (D_800BF80E != 0) {
            func_800440E4(D_800E7E80, 2, 4);
            a[0x70] = 2;
            a[6] = 6;
        }
        break;
    case 6:
        if (a[0x70] == 0xFF) {
            func_80070798();
        }
        break;
    }
    func_80041098(a);
    func_80070E60(a);
    func_8004190C(a);
}

#define CGH(p, o) (*(s16 *)((u8 *)(p) + (o)))
void f_RunNetBridgeCogInstallationCutscene(u8 *a) {
    u8 *g;

    switch (a[6]) {
    case 0:
        func_80040CDC(a, D_8001B860, D_80149E50[D_800BF830]);
        a[0x70] = 2;
        a[6]++;
        break;
    case 1:
        if (a[0x70] == 0) {
            func_8004D688(0x24, 1);
            D_800BF9DD = 9;
            a[0x70] = 2;
            a[6]++;
        }
        break;
    case 2:
        if (a[0x70] == 0) {
            g = (u8 *)D_800BF808;
            CGH(g, 0x22) = 0xB4;
            CGH(g, 0x1E) = 0;
            CGH(g, 0x26) = 0xFA;
            a[0x70] = 2;
            a[6]++;
        }
        break;
    case 3:
        if (func_8007101C(a, 0) != 0 && a[0x70] == 0) {
            a[0x70] = 2;
            a[6]++;
        }
        break;
    case 4:
        if (a[0x70] == 0xFF) {
            func_80070798();
        }
        break;
    }
    func_80041098(a);
    func_80070E60(a);
    func_8004190C(a);
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_HandleGoldFishhookRecovery);

extern u8 *D_80149E70;
extern u8 D_800BFAD8;
void func_80129008(u8 *a) {
    switch (a[6]) {
    case 0:
        func_80040CDC(a, D_8001B860, D_80149E50[D_800BF830]);
        a[0x70] = 2;
        a[6]++;
        break;
    case 1:
        if (a[0x70] == 0xFF) {
            if (D_800BFAD8 != 0) {
                func_80040CDC(a, D_8001B860, D_80149E70);
                a[0x70] = 2;
                a[0xBF] = 0xD;
                a[6] = 1;
            } else {
                func_80070798();
            }
        }
        break;
    }
    func_80041098(a);
    func_80070E60(a);
    func_8004190C(a);
}

s32 func_80129100(u8 *a) {
    if (((M2C_FIELD(a, u16 *, 0x72) - M2C_FIELD(a, u16 *, 0x58)) & 0xFFF) < 0x800) {
        M2C_FIELD(a, s16 *, 0x58) += 0x3C;
    } else {
        M2C_FIELD(a, s16 *, 0x58) -= 0x3C;
    }
    if (((M2C_FIELD(a, s16 *, 0x72) - M2C_FIELD(a, s16 *, 0x58)) & 0xFFF) < 0x3C) {
        M2C_FIELD(a, s16 *, 0x58) = M2C_FIELD(a, s16 *, 0x72);
        return 1;
    }
    return 0;
}

void f_UpdateKainenHouseRotatingEffect(u8 *a) {
    u8 *p;
    s32 d;

    if (func_8007778C(a) != 0) {
        switch (a[5]) {
        case 0:
            if (D_800BF870.pad1[0x47] == 0xFF) {
                a[5] = 5;
                H_f12c(a, 0x94) = 0x40;
            } else if (D_800BF870.pad1[0x16F] >= 7) {
                a[5] = 3;
                H_f12c(a, 0x94) = 0x100;
            } else {
                a[5] = 1;
                H_f12c(a, 0x94) = 0x200;
            }
            break;
        case 1:
            if (D_800BF9E0 >= 6) {
                a[5]++;
            }
            break;
        case 2:
            if ((H_f12c(a, 0x94) -= 0x20) <= 0x100) {
                H_f12c(a, 0x94) = 0x100;
                a[5]++;
            }
            break;
        case 3:
            if (D_800BF9E0 >= 0x10) {
                a[5]++;
            }
            break;
        case 4:
            if ((H_f12c(a, 0x94) -= 8) <= 0x40) {
                H_f12c(a, 0x94) = 0x40;
                a[5]++;
            }
            break;
        case 5:
            break;
        }
        p = *(u8 **)(a + 0xC0);
        d = *(u16 *)(a + 0x94);
        H_f12c(p, 0xC) += d;
        func_800517F8(a, d);
    }
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateWindmillInteriorEffect);

void func_801295B4(u8 *a)
{
    s32 i;
    u8 *o;

    for (i = 0; i < a[8]; i++) {
        o = ((u8 **)(a + 0xC0))[i];
        D_1F8000C0_317e.x = *(s16 *)(o + 0x2C);
        D_1F8000C0_317e.y = *(s16 *)(o + 0x30);
        D_1F8000C0_317e.z = *(s16 *)(o + 0x34);
        func_80084110(&D_1F8000D0_b839[0x28], o + 0x18, D_1F800000);
        func_80084220(&D_1F8000C0_317e, D_1F800000 + 0x14);
        { u8 *d = D_1F8000D0_b839;
        *(s32 *)(D_1F800000 + 0x14) += *(s32 *)(d + 0x3C);
        *(s32 *)(D_1F800000 + 0x18) += *(s32 *)(d + 0x40);
        *(s32 *)(D_1F800000 + 0x1C) += *(s32 *)(d + 0x44); }
        func_80084660(D_1F800000);
        func_80084690(D_1F800000);
        func_8012A2D8(a, o);
    }
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_801296E0);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_InitializeTableDrivenInteriorEffect);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_InitializeLinkedWindmillInteriorEffect);

extern u8 D_800BF816;
void f_HandleInteriorEffectActor(u8 *a)
{
    u8 *g;
    u8 *c;
    s32 i;
    u8 *p;
    u8 *g_f;

    switch (a[4]) {
    case 0:
        switch (a[3]) {
        case 0 ... 2:
            func_801296E0(a);
            break;
        case 3:
            f_InitializeTableDrivenInteriorEffect(a);
            break;
        case 4:
            f_InitializeLinkedWindmillInteriorEffect(a);
            break;
        }
        break;
    case 1:
        switch (a[3]) {
        case 0:
            g = D_800E7E80;
            if (g[0x2A] == 0x1F) {
                if (M2C_FIELD(g, s16 *, 0x36) < 0x2206) {
                    a[1] = 1;
                }
            } else if ((u8)(g[0x2A] - 0x1A) < 5 && g[0x147] == 1) {
                a[1] = g[0x147];
            } else {
                func_8007778C(a);
            }
            if (a[1] != 0) {
                c = M2C_FIELD(a, u8 **, 0xC0);
                M2C_FIELD(c, s16 *, 0xC) += 0x10;
                func_800517F8(a);
            }
            break;
        case 1:
            g_f = D_800E7E80;
            if ((u32)(g_f[0x2A] - 0x17) < 5 && g_f[0x147] == 1) {
                a[1] = g_f[0x147];
                c = M2C_FIELD(a, u8 **, 0xC0);
                M2C_FIELD(c, s16 *, 0xC) += 0x10;
                func_800517F8(a);
            }
            break;
        case 2:
            f_UpdateKainenHouseRotatingEffect(a);
            break;
        case 3:
            f_UpdateWindmillInteriorEffect(a);
            break;
        case 4:
            if (D_800BF816 == 0 || D_800BF8BC == 0xFF) {
                a[4] = 3;
                break;
            }
            if (a[5] == 0) {
                for (i = 0; i < a[8]; i++) {
                    p = *(u8 **)(a + i * 4 + 0xC0);
                    if (M2C_FIELD(p, s16 *, 8) < -0x7F) {
                        M2C_FIELD(p, s16 *, 8) += 0x10;
                    }
                }
            }
            a[1] = 1;
            func_80051C8C(a);
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

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateCurvedSupportGeometry);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8012A0B8);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8012A2D8);

void func_8012A43C(u8 *a) {
    u8 *p;
    u8 *s;
    u8 *c;

    a[8]--;
    func_8003CCA4();
    a[8]++;
    p = ((PartsOwner *)a)->parts[a[8] - 1];
    D_1F8000C0[0] = FU16(p, 0x2C);
    D_1F8000C0[1] = FU16(p, 0x30);
    D_1F8000C0[2] = FU16(p, 0x34);
    func_80084110(D_1F8000D0_b839 + 0x28, p + 0x18, D_1F800000);
    func_80084220(D_1F8000C0, D_1F800000 + 0x14);
    s = D_1F800000;
    c = D_1F8000D0_b839;
    M2C_FIELD(s, s32 *, 0x14) += M2C_FIELD(c, s32 *, 0x3C);
    M2C_FIELD(s, s32 *, 0x18) += M2C_FIELD(c, s32 *, 0x40);
    M2C_FIELD(s, s32 *, 0x1C) += M2C_FIELD(c, s32 *, 0x44);
    func_80084660(s);
    func_80084690(s);
    func_8012A2D8(a, p);
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8012A54C);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_SpawnWindmillCollapseDebrisPieces);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_AdvanceWindmillCollapseEffectPoint);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_AnimateWindmillCollapseOpening);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_AnimateWindmillCollapseMainSequence);

#define CH(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define CPART(a, i) (((PartsOwner *)(a))->parts[i])
typedef struct { s16 pad0, pad2, y, pad6, x8, xA, xC, padE; } CollapseT;
extern u8 D_80149F84[];
extern CollapseT D_80149F90[];
void f_AnimateWindmillCollapseFinale(u8 *a) {
    s16 v[6];
    u8 *e = D_800E8008;
    u8 *p;
    s32 i, n, k;
    s16 t;

    switch (a[6]) {
    case 0:
        i = 2;
        if (D_800BF9DE >= 0x15) {
            a[6] = 6;
            break;
        }
        a[6]++;
        for (; i < a[8] - 2; i++) {
            p = CPART(a, i);
            CH(p, 2) = 0xBB8;
        }
        break;
    case 1:
        i = 2;
        if (D_800BF9DE == 0x11) {
            a[6]++;
            for (; i < a[8] - 2; i++) {
                p = CPART(a, i);
                CH(p, 2) = -0xBB8;
                CH(p, 0x12) = 0;
                CH(p, 0x10) = 1;
                CH(p, 0x16) = 0;
                CH(p, 0x14) = 0x40;
            }
            CH(a, 0x40) = 2;
            CH(a, 0x42) = 0;
            a[0x2B] = 0;
            CH(a, 0x60) = 0;
        }
        break;
    case 2:
        i = 2;
        if (D_800BF9DE >= 0x12) {
            for (; i <= CH(a, 0x40); i++) {
                if (i >= a[8] - 2) {
                    break;
                }
                p = CPART(a, D_80149F84[i]);
                CH(p, 2) += CH(p, 0x12);
                CH(p, 0x12) += CH(p, 0x10);
                CH(p, 0xC) += 0x40;
                if (CH(p, 2) > D_80149F90[D_80149F84[i]].y) {
                    CH(p, 2) = D_80149F90[D_80149F84[i]].y;
                }
            }
            if (!(++CH(a, 0x42) & 3)) {
                CH(a, 0x40)++;
            }
            i = 2;
            if (D_800BF9DE == 0x13) {
                a[6]++;
                for (; i < a[8] - 2; i++) {
                    p = CPART(a, i);
                    CH(p, 2) = -0x960;
                    CH(p, 0x12) = 0x10;
                    CH(p, 0x10) = 2;
                    CH(p, 0x16) = 0;
                    CH(p, 0x14) = 0x40;
                    CH(p, 8) = D_80149F90[i].x8;
                    CH(p, 0xA) = D_80149F90[i].xA;
                    CH(p, 0xC) = D_80149F90[i].xC;
                }
                CH(a, 0x40) = 2;
                CH(a, 0x42) = 0;
                a[0x2B] = 0;
                CH(a, 0x60) = 0;
                CH(a, 0x62) = 0x1F;
            }
        }
        break;
    case 3:
        i = 2;
        a[0x2B] = 0;
        if (i <= CH(a, 0x40)) {
            for (; i <= CH(a, 0x40); i++) {
                if (i >= a[8] - 2) {
                    break;
                }
                p = CPART(a, i);
                CH(p, 2) += CH(p, 0x12);
                CH(p, 0x12) += CH(p, 0x10);
                if (CH(p, 2) > D_80149F90[i].y) {
                    CH(p, 2) = D_80149F90[i].y;
                    if (CH(p, 0x16) == 0) {
                        func_80074590(0x85, -0xA, 0x1B);
                        if (i < 6) {
                            {
                                s32 j, ang, x, s, c2;
                                u8 *q;

                                ang = 0x400;
                                for (j = 0; j < 5; j++) {
                                    x = (s16)ang;
                                    s = (func_80083F50(x) * 200) >> 12;
                                    c2 = func_80083E80(x);
                                    ang += 0x199;
                                    v[1] = CH(p, 0x2C) + s;
                                    v[3] = CH(p, 0x30) + 0x5A;
                                    v[5] = CH(p, 0x34) - ((c2 * 300) >> 12);
                                    q = func_8003116C(0, v, -0x64);
                                    q[0x28] |= 0x80;
                                }
                            }
                        }
                        CH(p, 0x12) = -0xC;
                        CH(p, 0x10) = 4;
                        CH(p, 0x16)++;
                        a[0x2B] = 1;
                        func_80054DAC(D_800E7E80, 0xB4, 0);
                    }
                }
            }
            for (i = 2; i <= CH(a, 0x40); i++) {
                n = a[8];
                if (i >= n - 2) {
                    break;
                }
                p = CPART(a, i);
                k = CH(p, 0x16);
                if (k == 0) {
                } else if (k == 1) {
                    CH(p, 0xC) += CH(p, 0x14);
                    if ((CH(p, 0x14) -= 0x40) < -0x40) {
                        CH(p, 0x14) = 0x20;
                        CH(p, 0x16)++;
                    }
                    a[0x2B] = 1;
                } else if (k == 2) {
                    CH(p, 0xC) += CH(p, 0x14);
                    if ((CH(p, 0x14) -= 0x20) < -0x20) {
                        if (i < 6) {
                            {
                                s32 j, ang, x, s, c2;
                                u8 *q;

                                ang = 0x400;
                                for (j = 0; j < 5; j++) {
                                    x = (s16)ang;
                                    s = (func_80083F50(x) * 200) >> 12;
                                    c2 = func_80083E80(x);
                                    ang += 0x199;
                                    v[1] = CH(p, 0x2C) + s;
                                    v[3] = CH(p, 0x30) + 0x5A;
                                    v[5] = CH(p, 0x34) - ((c2 * 300) >> 12);
                                    q = func_8003116C(0, v, -0x64);
                                    q[0x28] |= 0x80;
                                }
                            }
                        }
                        CH(p, 0x16)++;
                    }
                    a[0x2B] = 1;
                } else {
                    if (i == n - 3) {
                        a[6]++;
                        D_800BF870.pad1[0x16D] = 0x14;
                    }
                }
            }
        }
        if (!(++CH(a, 0x42) & CH(a, 0x62))) {
            t = ++CH(a, 0x40);
            if (t >= 8) {
                CH(a, 0x62) = 7;
            } else if (t >= 5) {
                CH(a, 0x62) = 0xF;
            }
        }
        if (a[0x2B] != 0) {
            if (CH(a, 0x60) == 0) {
                e[0x76] = 1;
                CH(a, 0x60) = 1;
            }
            a[0x2B] = 0;
        } else {
            if (e[0x76] != 0) {
                e[0x76] = 3;
            }
            CH(a, 0x60) = 0;
        }
        break;
    case 4:
        CH(a, 0x40) = 0x14;
        a[6]++;
        break;
    case 5:
        if (--CH(a, 0x40) == 0) {
            a[6]++;
            D_800BF9DE = 0x15;
        }
        break;
    case 6:
        break;
    }
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateA00InteriorTransitionActor);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_HandleA00InteriorSceneEffectActor);

u8 *func_8012CE30(u8 *a, s32 b, s32 i) {
    u8 *p = func_8003116C(D_8014A240[i], b, -0x64);

    if (p != NULL) {
        M2C_FIELD(p, u8 **, 0x10) = a;
        p[0x28] |= 0x80;
        return p;
    }
    return NULL;
}

s16 f_GetWindmillControllerBearing(u8 *a) {
    u8 *t = D_1F800218;
    s16 dx = M2C_FIELD(t, s16 *, 0x2E) - M2C_FIELD(a, s16 *, 0x2);
    s16 dz = M2C_FIELD(t, s16 *, 0x36) - M2C_FIELD(a, s16 *, 0xA);

    return func_80085690(-dz, dx);
}

void func_8012CEE0(u8 *a) {
    if (a[0x5F] == 0) {
        func_80074590(6, 4, 0x1E);
        a[0x5F] = D_8014A258[(M2C_FIELD(M2C_FIELD(a, u8 **, 0xC0), u16 *, 0x16) >> 6) & 7];
    } else {
        a[0x5F]--;
    }
}

void f_UpdateKainenHouseWobbleWide(void *arg0) {
    u8 temp_v1;

    if (M2C_FIELD(arg0, s16 *, 0x50) != 0) {
        temp_v1 = M2C_FIELD(arg0, u8 *, 6);
        switch (temp_v1) {                          /* irregular */
        case 0:
            M2C_FIELD(arg0, u8 *, 6) = 1U;
            M2C_FIELD(arg0, s16 *, 0x4A) = 0;
            M2C_FIELD(arg0, u16 *, 0x5A) = (u16) (M2C_FIELD(arg0, u16 *, 0x56) + 0x700);
            /* fallthrough */
        case 1:
            M2C_FIELD(arg0, u16 *, 0x56) = (u16) (M2C_FIELD(arg0, u16 *, 0x5A) + ((s32) (func_80083F50(M2C_FIELD(arg0, s16 *, 0x4A)) << 9) >> 0xC));
            M2C_FIELD(arg0, s16 *, 0x4A) = (s16) (((u16) M2C_FIELD(arg0, s16 *, 0x4A) + (u16) M2C_FIELD(arg0, s16 *, 0x50)) & 0xFFF);
            break;
        case 2:
            M2C_FIELD(arg0, u16 *, 0x56) = (u16) (M2C_FIELD(arg0, u16 *, 0x5A) + ((s32) (func_80083F50(M2C_FIELD(arg0, s16 *, 0x4A)) << 8) >> 0xC));
            M2C_FIELD(arg0, s16 *, 0x4A) = (s16) (((u16) M2C_FIELD(arg0, s16 *, 0x4A) + (M2C_FIELD(arg0, s16 *, 0x50) * 2)) & 0xFFF);
            break;
        }
        if (M2C_FIELD(arg0, s16 *, 0x4A) == 0) {
            M2C_FIELD(arg0, u8 *, 6) = (u8) ((func_8009A450() & 1) + 1);
        }
    }
}

void f_UpdateKainenHouseWobbleNarrow(void *arg0) {
    u8 temp_v1;

    if (M2C_FIELD(arg0, s16 *, 0x50) != 0) {
        temp_v1 = M2C_FIELD(arg0, u8 *, 6);
        switch (temp_v1) {                          /* irregular */
        case 0:
            M2C_FIELD(arg0, u8 *, 6) = 1U;
            M2C_FIELD(arg0, s16 *, 0x4A) = 0;
            M2C_FIELD(arg0, u16 *, 0x5A) = (u16) (M2C_FIELD(arg0, u16 *, 0x56) + 0x300);
            /* fallthrough */
        case 1:
            M2C_FIELD(arg0, u16 *, 0x56) = (u16) (M2C_FIELD(arg0, u16 *, 0x5A) + ((s32) (func_80083F50(M2C_FIELD(arg0, s16 *, 0x4A)) << 8) >> 0xC));
            M2C_FIELD(arg0, s16 *, 0x4A) = (s16) (((u16) M2C_FIELD(arg0, s16 *, 0x4A) + (u16) M2C_FIELD(arg0, s16 *, 0x50)) & 0xFFF);
            break;
        case 2:
            M2C_FIELD(arg0, u16 *, 0x56) = (u16) (M2C_FIELD(arg0, u16 *, 0x5A) + ((s32) (func_80083F50(M2C_FIELD(arg0, s16 *, 0x4A)) << 7) >> 0xC));
            M2C_FIELD(arg0, s16 *, 0x4A) = (s16) (((u16) M2C_FIELD(arg0, s16 *, 0x4A) + (M2C_FIELD(arg0, s16 *, 0x50) * 2)) & 0xFFF);
            break;
        }
        if (M2C_FIELD(arg0, s16 *, 0x4A) == 0) {
            M2C_FIELD(arg0, u8 *, 6) = (u8) ((func_8009A450() & 1) + 1);
        }
    }
}

void f_UpdateKainenHouseWobbleInverted(void *arg0) {
    u8 temp_v1;

    if (M2C_FIELD(arg0, s16 *, 0x50) != 0) {
        temp_v1 = M2C_FIELD(arg0, u8 *, 6);
        switch (temp_v1) {                          /* irregular */
        case 0:
            M2C_FIELD(arg0, u8 *, 6) = 1U;
            M2C_FIELD(arg0, s16 *, 0x4A) = 0;
            M2C_FIELD(arg0, u16 *, 0x5A) = (u16) (M2C_FIELD(arg0, u16 *, 0x56) - 0x300);
            /* fallthrough */
        case 1:
            M2C_FIELD(arg0, u16 *, 0x56) = (u16) (M2C_FIELD(arg0, u16 *, 0x5A) - ((s32) (func_80083F50(M2C_FIELD(arg0, s16 *, 0x4A)) << 8) >> 0xC));
            M2C_FIELD(arg0, s16 *, 0x4A) = (s16) (((u16) M2C_FIELD(arg0, s16 *, 0x4A) + (u16) M2C_FIELD(arg0, s16 *, 0x50)) & 0xFFF);
            break;
        case 2:
            M2C_FIELD(arg0, u16 *, 0x56) = (u16) (M2C_FIELD(arg0, u16 *, 0x5A) - ((s32) (func_80083F50(M2C_FIELD(arg0, s16 *, 0x4A)) << 7) >> 0xC));
            M2C_FIELD(arg0, s16 *, 0x4A) = (s16) (((u16) M2C_FIELD(arg0, s16 *, 0x4A) + (M2C_FIELD(arg0, s16 *, 0x50) * 2)) & 0xFFF);
            break;
        }
        if (M2C_FIELD(arg0, s16 *, 0x4A) == 0) {
            M2C_FIELD(arg0, u8 *, 6) = (u8) ((func_8009A450() & 1) + 1);
        }
    }
}

void f_UpdateKainenHouseWobbleEffect(u8 *a) {
    switch (a[5]) {
    case 0:
        if (D_800BF870.pad1[0x47] == 0xFF) {
            a[5] = 5;
            H_f12c(a, 0x50) = 0x10;
        } else if (D_800BF870.pad1[0x16F] >= 8) {
            a[5] = 3;
            H_f12c(a, 0x50) = 0xC0;
        } else {
            a[5] = 1;
            H_f12c(a, 0x50) = 0x100;
        }
        break;
    case 1:
        if (D_800BF9E0 >= 7) {
            a[5]++;
        }
        break;
    case 2:
        if (H_f12c(a, 0x50) > 0xC0) {
            H_f12c(a, 0x50) -= 0x10;
        } else {
            a[5]++;
        }
        break;
    case 3:
        if (D_800BF9E0 >= 0x11) {
            a[5]++;
        }
        break;
    case 4:
        if (H_f12c(a, 0x50) > 0x10) {
            H_f12c(a, 0x50) -= 8;
        } else {
            a[5]++;
        }
        break;
    case 5:
        break;
    }
    switch (a[3]) {
    case 0:
    case 1:
        f_UpdateKainenHouseWobbleWide(a);
        return;
    case 2:
        f_UpdateKainenHouseWobbleNarrow(a);
        return;
    case 3:
        f_UpdateKainenHouseWobbleInverted(a);
        return;
    }
}

extern s16 D_8014A260[];
extern s16 D_8014A268[];
void func_8012D404(u8 *a) {
    switch (a[4]) {
    case 0:
        if (func_80051B70(a, 0xC, D_8014A260[a[3]]) == 0) {
            a[4]++;
            M2C_FIELD(a, s16 *, 0x54) = D_8014A268[a[3]];
        }
        break;
    case 1:
        if (func_8007778C(a) != 0) {
            f_UpdateKainenHouseWobbleEffect(a);
            func_800517F8(a);
        }
        break;
    case 2:
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

extern u8 D_800BF9DF;
extern s16 D_1F8000DE;
void f_HandleGoldFishhookScenePropActor(u8 *a)
{
    u8 *e = D_800E7E80;
    GameState *g;
    u8 v;

    switch (a[4]) {
    case 0:
        if (func_80051B70(a, 0xC, a[3] + 0x48) != 0) {
            break;
        }
        a[0] = 1;
        a[4]++;
        if (a[3] < 2) {
            if (D_800BF9DF != 0) {
                a[4] = 3;
                break;
            }
            a[0xB] = 0;
        } else {
            a[0xB] = 2;
        }
        func_800517F8(a);
        break;
    case 1:
        if (D_1F800207_9c67 < 0x16) {
            break;
        }
        if (D_1F800207_9c67 == 0x16 && *(s16 *)(e + 0x36) < 0x2A30) {
            break;
        }
        if (D_800BF80D != 0) {
            a[1] = 1;
            break;
        }
        switch (a[3]) {
        case 0:
            switch (a[5]) {
            case 0:
                if (D_800BF9DF & 2) {
                    a[6] = 0;
                    a[5]++;
                }
                if (D_1F800207_9c67 < 0x17) {
                    break;
                }
                a[1] = 1;
                break;
            case 1:
                if (a[6] == 0) {
                    *(s16 *)(a + 0x32) += 4;
                    if (*(s16 *)(a + 0x32) >= -0x64E) {
                        a[0x1A] = 0x7F;
                        a[0x19] = 0x7F;
                        a[0x18] = 0x7F;
                        a[0xD] = 2;
                        a[6]++;
                    }
                } else if (a[6] == 1) {
                    v = a[0x18] - 3;
                    a[0x1A] = v;
                    a[0x19] = v;
                    a[0x18] = v;
                    if ((s8)v <= 0) {
                        if (a[3] == 0) {
                            D_800BF870.pad1[0x16E] |= 4;
                        } else {
                            D_800BF870.pad1[0x16E] |= 8;
                        }
                        a[0x1A] = 0;
                        a[0x19] = 0;
                        a[0x18] = 0;
                        a[4] = 3;
                    }
                }
                a[1] = 1;
                func_800517F8(a);
                break;
            }
            break;
        case 1:
            switch (a[5]) {
            case 0:
                if (D_800BF9DF & 2) {
                    a[6] = 0;
                    a[5]++;
                }
                if (D_1F800207_9c67 < 0x1C || D_1F8000DE < 0x3F8C) {
                    break;
                }
                a[1] = 1;
                break;
            case 1:
                switch (a[6]) {
                case 0:
                    *(s16 *)(a + 0x32) += 4;
                    if (*(s16 *)(a + 0x32) >= -0x64E) {
                        a[0x1A] = 0x7F;
                        a[0x19] = 0x7F;
                        a[0x18] = 0x7F;
                        a[0xD] = 2;
                        a[6]++;
                    }
                    break;
                case 1:
                    v = a[0x18] - 3;
                    a[0x1A] = v;
                    a[0x19] = v;
                    a[0x18] = v;
                    if ((s8)v <= 0) {
                        if (a[3] == 0) {
                            D_800BF870.pad1[0x16E] |= 4;
                        } else {
                            D_800BF870.pad1[0x16E] |= 8;
                        }
                        a[0x1A] = 0;
                        a[0x19] = 0;
                        a[0x18] = 0;
                        a[4] = 3;
                    }
                    break;
                }
                a[1] = 1;
                func_800517F8(a);
                break;
            }
            break;
        case 2:
        case 3:
            if (D_800BF9DF != 0 || D_1F800207_9c67 >= 0x1F) {
                a[1] = 1;
            }
            break;
        case 4:
            if (D_800BF9DF != 0 || D_1F800207_9c67 >= 0x20) {
                a[1] = 1;
            }
            break;
        case 5:
            g = &D_800BF870;
            if (g->pad1[0x144] == 3 || g->pad1[0x16E] != 0 || (u32)(D_1F800207_9c67 - 0x1E) >= 2) {
                a[1] = 1;
            }
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

void func_8012D908(u8 *a) {
    s8 v;

    switch (a[6]) {
    case 0:
        if ((F16(a, 0x32) += 4) >= -0x64E) {
            a[0x1A] = 0x7F;
            a[0x19] = 0x7F;
            a[0x18] = 0x7F;
            a[0xD] = 2;
            a[6]++;
        }
        break;
    case 1:
        v = a[0x18] - 3;
        a[0x1A] = v;
        a[0x19] = v;
        a[0x18] = v;
        if (v <= 0) {
            if (a[3] == 0) {
                D_800BF870.pad1[0x16E] |= 4;
            } else {
                D_800BF870.pad1[0x16E] |= 8;
            }
            a[0x1A] = 0;
            a[0x19] = 0;
            a[0x18] = 0;
            a[4] = 3;
        }
        break;
    }
    a[1] = 1;
    func_800517F8(a);
}

/* tools/dispatch.py draft of f_HandleTownQuestRewardVisualActor (a00, 0x430 bytes): 4 inlined bodies
 * register maps (body -> here): 
 *   f_InitializeTownQuestRewardVisualModel_inl (a00:f_InitializeTownQuestRewardVisualModel, cover 1.00, regs 1.00): same registers
 *   inl_8012DE34 (a00:func_8012DE34, cover 1.00, regs 1.00): s0->s1, s1->s0
 *   inl_8012DF50 (a00:func_8012DF50, cover 1.00, regs 1.00): same registers
 *   inl_8012E1E4 (a00:func_8012E1E4, cover 1.00, regs 1.00): same registers
 * notes:
 *   f_InitializeTownQuestRewardVisualModel_inl: code inside the copy is also reached from outside (.L8012DB08 8012DB08: a tail gcc cross-jumped, or a case entering it): that path is missing from the draft; write it out in full (gcc merges the identical tails again), from tools/decomp.py's draft
 *   f_InitializeTownQuestRewardVisualModel_inl: replaces 8012DABC-8012DB2C
 *   inl_8012DE34: replaces 8012DB60-8012DC0C
 *   inl_8012DF50: replaces 8012DC20-8012DC9C
 *   inl_8012E1E4: code inside the copy is also reached from outside (.L8012DDE8 8012DDE8, .L8012DDFC 8012DDFC: a tail gcc cross-jumped, or a case entering it): that path is missing from the draft; write it out in full (gcc merges the identical tails again), from tools/decomp.py's draft
 *   inl_8012E1E4: replaces 8012DD4C-8012DE14
 * next: fix the draft's types and the helper calls' arguments, then
 *   python3 -I tools/ccheck.py THIS.c --prog a00 --func f_HandleTownQuestRewardVisualActor --sbs
 *   python3 -I tools/install_c.py THIS.c --prog a00 */

extern u8 D_800E7E80[];
/* f_InitializeTownQuestRewardVisualModel, inlined */
static inline void f_InitializeTownQuestRewardVisualModel_inl(u8 *a) {
    if (func_80051B70(a, 0xC, 0x4F) == 0) {
        switch (a[3]) {
        case 3:
            M2C_FIELD(M2C_FIELD(a, u8 **, 0xC0), s16 *, 0x8) = 0xB6;
            break;
        case 4:
            M2C_FIELD(M2C_FIELD(a, u8 **, 0xC0), s16 *, 0x8) = -0xB6;
            break;
        }
        func_800517F8(a);
    }
}
/* func_8012DE34, inlined */
static inline void inl_8012DE34(u8 *a) {
    u8 *g = D_800E7E80;

    switch (a[5]) {
    case 0:
        if (D_800BF9DD == 9) {
            a[5] = 1;
            M2C_FIELD(a, s32 *, 0x3C) = D_800ECF80;
            func_80077B38(a, D_8014C808, 0xF);
            M2C_FIELD(a, s16 *, 0x60) = 0x40;
            M2C_FIELD(a, s16 *, 0x62) = 0;
            M2C_FIELD(a, s16 *, 0x64) = -0x20;
        }
        break;
    case 1:
        func_8004BD64(a, 2, M2C_FIELD(g, s32 *, 0xDC), M2C_FIELD(g, s32 *, 0xD0), a + 0x60);
        a[1] = 1;
        if (D_800BF9DD == 0xB) {
            a[4] = 3;
        }
        break;
    }
}
/* func_8012DF50, inlined */
static inline void inl_8012DF50(u8 *a) {
    u8 *p = M2C_FIELD(a, u8 **, 0x10);

    switch (a[5]) {
    case 0:
        a[5]++;
        M2C_FIELD(a, s32 *, 0x3C) = D_800ECF80;
        func_80077B38(a, D_8014C808, 2);
        M2C_FIELD(a, s16 *, 0x60) = 0x20;
        M2C_FIELD(a, s16 *, 0x62) = 0x10;
        M2C_FIELD(a, s16 *, 0x64) = 0;
    case 1:
        func_8004BD64(a, 1, M2C_FIELD(p, void **, 0xDC), 0, a + 0x60);
        a[1] = p[1];
        break;
    }
}
/* func_8012E1E4, inlined */
static inline void inl_8012E1E4(u8 *a) {
    u8 *p = M2C_FIELD(a, u8 **, 0x10);

    switch (a[5]) {
    case 0:
        a[5]++;
        M2C_FIELD(a, s32 *, 0x3C) = D_800ECF80;
        func_80077B38(a, D_8014C808, 0xE);
        M2C_FIELD(a, s16 *, 0x60) = -0xC8;
        M2C_FIELD(a, s16 *, 0x62) = 0x30;
        M2C_FIELD(a, s16 *, 0x64) = 0;
    case 1:
        func_8004BD64(a, 2, 0, M2C_FIELD(p, s32 *, 0xD0), a + 0x60);
        a[1] = p[1];
        if (D_800BF9B5 == 6) {
            func_8004D4C4(0x23, 1);
            func_8004B0D8(a);
            a[4] = 3;
        }
        break;
    }
}
void f_HandleTownQuestRewardVisualActor(u8 *a)
{
    u8 *p;

    switch (a[4]) {
    case 0:
        a[4] = 1;
        switch (a[3]) {
        case 0:
        case 1:
        case 2:
        case 6:
        case 7:
            a[0xB] = 0x10;
            a[0xD] = 0;
            M2C_FIELD(a, s16 *, 0x5C) = 0;
            M2C_FIELD(a, s16 *, 0x5A) = 0;
            a[0x47] = 0;
            M2C_FIELD(a, s16 *, 0x60) = 0;
            a[8] = 0xF0;
            break;
        case 3:
        case 4:
            f_InitializeTownQuestRewardVisualModel_inl(a);
            break;
        case 5:
            if (func_80051B70(a, 0xC, 7) == 0) {
                func_800517F8(a);
            }
            break;
        }
        break;
    case 1:
        switch (a[3]) {
        case 0:
            inl_8012DE34(a);
            break;
        case 1:
            func_8018C574(a);
            break;
        case 2:
            inl_8012DF50(a);
            break;
        case 3:
        case 4:
        case 5:
            func_8007778C(a);
            break;
        case 6:
            p = M2C_FIELD(a, u8 **, 0x10);
            switch (a[5]) {
            case 0:
                a[5]++;
                M2C_FIELD(a, s32 *, 0x3C) = D_800ECF80;
                func_80077B38(a, D_8014C808, 0x11);
                M2C_FIELD(a, s16 *, 0x60) = -0xC8;
                M2C_FIELD(a, s16 *, 0x62) = 0x20;
                M2C_FIELD(a, s16 *, 0x64) = 0;
            case 1:
                func_8004BD64(a, 2, 0, M2C_FIELD(p, s32 *, 0xD0), a + 0x60);
                a[1] = p[1];
                if (D_800BF9B5 == 5) {
                    func_8004D4C4(0xE, 1);
                    func_8004B0D8(a);
                    a[4] = 3;
                }
                break;
            }
            break;
        case 7:
            inl_8012E1E4(a);
            break;
        }
        break;
    case 2:
        if (a[3] == 2) {
            func_8004D4C4(0x1D, 1);
            func_8004B0D8(a);
            a[4] = 3;
        }
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

void func_8012DE34(u8 *a) {
    u8 *g = D_800E7E80;

    switch (a[5]) {
    case 0:
        if (D_800BF9DD == 9) {
            a[5] = 1;
            M2C_FIELD(a, s32 *, 0x3C) = D_800ECF80;
            func_80077B38(a, D_8014C808, 0xF);
            M2C_FIELD(a, s16 *, 0x60) = 0x40;
            M2C_FIELD(a, s16 *, 0x62) = 0;
            M2C_FIELD(a, s16 *, 0x64) = -0x20;
        }
        break;
    case 1:
        func_8004BD64(a, 2, M2C_FIELD(g, s32 *, 0xDC), M2C_FIELD(g, s32 *, 0xD0), a + 0x60);
        a[1] = 1;
        if (D_800BF9DD == 0xB) {
            a[4] = 3;
        }
        break;
    }
}

u8 *func_8012DF08(s32 a) {
    u8 *p = func_80072DDC(a, 128, 3, 16);

    if (p == NULL) {
        return NULL;
    }
    p[0x3] = 2;
    M2C_FIELD(p, void **, 0x1C) = f_HandleTownQuestRewardVisualActor;
    return p;
}

void func_8012DF50(u8 *a) {
    u8 *p = M2C_FIELD(a, u8 **, 0x10);

    switch (a[5]) {
    case 0:
        a[5]++;
        M2C_FIELD(a, s32 *, 0x3C) = D_800ECF80;
        func_80077B38(a, D_8014C808, 2);
        M2C_FIELD(a, s16 *, 0x60) = 0x20;
        M2C_FIELD(a, s16 *, 0x62) = 0x10;
        M2C_FIELD(a, s16 *, 0x64) = 0;
    case 1:
        func_8004BD64(a, 1, M2C_FIELD(p, void **, 0xDC), 0, a + 0x60);
        a[1] = p[1];
        break;
    }
}

void func_8012DFF8(void *arg0) {
    func_8004D4C4(0x1D, 1);
    func_8004B0D8(arg0);
    M2C_FIELD(arg0, s8 *, 4) = 3;
}

void func_8012E034(void *arg0)
{
  int new_var;
  *((s8 *) (((signed char *) arg0) + 0xB)) = 0x10;
  *((s8 *) (((signed char *) arg0) + 0xD)) = 0;
  *((s16 *) (((signed char *) arg0) + 0x5C)) = 0;
  *((s16 *) (((signed char *) arg0) + 0x5A)) = 0;
  *((s8 *) (((signed char *) arg0) + 0x47)) = 0;
  *((s16 *) (((signed char *) arg0) + 0x60)) = 0;
  new_var = 0xF0;
  *((s8 *) (((signed char *) arg0) + 8)) = new_var;
}

void f_InitializeTownQuestRewardVisualModel(u8 *a) {
    if (func_80051B70(a, 0xC, 0x4F) == 0) {
        switch (a[3]) {
        case 3:
            M2C_FIELD(M2C_FIELD(a, u8 **, 0xC0), s16 *, 0x8) = 0xB6;
            break;
        case 4:
            M2C_FIELD(M2C_FIELD(a, u8 **, 0xC0), s16 *, 0x8) = -0xB6;
            break;
        }
        func_800517F8(a);
    }
}

void func_8012E0D0(void *a)
{
    if (func_80051B70(a, 0xC, 7) == 0) {
        func_800517F8(a);
    }
}

void func_8012E10C(u8 *a) {
    u8 *p = M2C_FIELD(a, u8 **, 0x10);

    switch (a[5]) {
    case 0:
        a[5]++;
        M2C_FIELD(a, s32 *, 0x3C) = D_800ECF80;
        func_80077B38(a, D_8014C808, 0x11);
        M2C_FIELD(a, s16 *, 0x60) = -0xC8;
        M2C_FIELD(a, s16 *, 0x62) = 0x20;
        M2C_FIELD(a, s16 *, 0x64) = 0;
    case 1:
        func_8004BD64(a, 2, 0, M2C_FIELD(p, s32 *, 0xD0), a + 0x60);
        a[1] = p[1];
        if (D_800BF9B5 == 5) {
            func_8004D4C4(0xE, 1);
            func_8004B0D8(a);
            a[4] = 3;
        }
        break;
    }
}

void func_8012E1E4(u8 *a) {
    u8 *p = M2C_FIELD(a, u8 **, 0x10);

    switch (a[5]) {
    case 0:
        a[5]++;
        M2C_FIELD(a, s32 *, 0x3C) = D_800ECF80;
        func_80077B38(a, D_8014C808, 0xE);
        M2C_FIELD(a, s16 *, 0x60) = -0xC8;
        M2C_FIELD(a, s16 *, 0x62) = 0x30;
        M2C_FIELD(a, s16 *, 0x64) = 0;
    case 1:
        func_8004BD64(a, 2, 0, M2C_FIELD(p, s32 *, 0xD0), a + 0x60);
        a[1] = p[1];
        if (D_800BF9B5 == 6) {
            func_8004D4C4(0x23, 1);
            func_8004B0D8(a);
            a[4] = 3;
        }
        break;
    }
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8012E2BC);

void func_8012E478(u8 *a) {
    switch (a[4]) {
    case 0:
        switch (a[0x5E]) {
        case 0:
            func_8012E2BC(a);
            break;
        case 1:
        case 2:
            func_8012E678(a);
            break;
        }
        break;
    case 1:
        func_8007778C(a);
        func_8012E70C(a);
        break;
    case 2:
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

void func_8012E478();
u8 *func_8012E53C(u8 *a, s32 b, s16 *c) {
    u8 *p = func_80072DDC(a, 0, 3, 0x11);

    if (p != NULL) {
        M2C_FIELD(p, void **, 0x1C) = func_8012E478;
        p[3] = 0;
        p[0x5E] = 0;
        M2C_FIELD(p, s16 *, 0x40) = ((s16)b >> 4) + 2;
        M2C_FIELD(p, s16 *, 0x2E) = c[0];
        M2C_FIELD(p, s16 *, 0x32) = c[1];
        M2C_FIELD(p, s16 *, 0x36) = c[2];
    }
    return p;
}

u8 *func_8012E5CC(u8 *a, s16 *b, s16 *c) {
    u8 *p = func_80072DDC(a, 0, 3, 0x11);
    s32 r;

    if (p != NULL) {
        M2C_FIELD(p, void **, 0x1C) = func_8012E478;
        r = func_8009A450() & 0xF0;
        p[0x5E] = 1;
        M2C_FIELD(p, s16 *, 0x2E) = b[0];
        M2C_FIELD(p, s16 *, 0x32) = b[1] - r;
        M2C_FIELD(p, s16 *, 0x36) = b[2] + r;
        M2C_FIELD(p, s16 *, 0x48) = c[0];
        M2C_FIELD(p, s16 *, 0x4C) = c[2];
    }
    return p;
}

void func_8012E678(u8 *a) {
    s32 r = func_8009A450() & 3;
    a[0x3] = r;

    a[0xB] = 0x12;
    a[0x8] = 0xC4;
    M2C_FIELD(a, s16 *, 0x40) = 0x5A;
    a[0xD] = 0;
    M2C_FIELD(a, s16 *, 0x5C) = 0;
    M2C_FIELD(a, s16 *, 0x5A) = 0;
    M2C_FIELD(a, s16 *, 0x60) = 1;
    a[0x4]++;
    func_8012E7EC(a);
    M2C_FIELD(a, s32 *, 0x3C) = D_800ECF80;
    func_80077B38(a, D_8014C808, r + 0x12);
}

void func_8012E70C(u8 *a) {
    s16 s;
    s16 c;
    s32 m;
    s32 d;
    s16 e;

    c = --M2C_FIELD(a, s16 *, 0x40);
    if (a[1] == 0 || c <= 0) {
        if (a[0x5E] == 2) {
            M2C_FIELD(a, u8 **, 0x10)[0x5E] = 0;
        }
        a[4] = 3;
        return;
    }
    s = M2C_FIELD(a, s16 *, 0x44);
    m = s * M2C_FIELD(a, s16 *, 0x48);
    e = M2C_FIELD(a, s16 *, 0x4E);
    d = M2C_FIELD(a, s16 *, 0x4A) >> 8;
    M2C_FIELD(a, s16 *, 0x32) += d;
    M2C_FIELD(a, s16 *, 0x54) += e;
    M2C_FIELD(a, s32 *, 0x2C) += m;
    M2C_FIELD(a, s32 *, 0x34) += s * M2C_FIELD(a, s16 *, 0x4C);
    if ((s16)func_8012E87C(a)) {
        func_8012E7EC(a);
    }
}

void func_8012E7EC(u8 *a) {
    s16 r = func_8009A450();

    if (r & 1) {
        M2C_FIELD(a, s16 *, 0x44) = 0x800;
    } else {
        M2C_FIELD(a, s16 *, 0x44) = -0x800;
    }
    if (r & 2) {
        M2C_FIELD(a, s16 *, 0x4E) = 0x180;
    } else {
        M2C_FIELD(a, s16 *, 0x54) = 0;
        M2C_FIELD(a, s16 *, 0x4E) = 0;
    }
    M2C_FIELD(a, s16 *, 0x4A) = (r & 0x700) + 0x1000;
    M2C_FIELD(a, s16 *, 0x50) = (r & 0x30) - 0x100;
    M2C_FIELD(a, s16 *, 0x60) = -0x400 - (r & 0x70);
    M2C_FIELD(a, s16 *, 0x44) += r & 0x300;
}

s32 func_8012E87C(void *arg0) {
    u16 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u16 *, 0x4A) + M2C_FIELD(arg0, u16 *, 0x50);
    M2C_FIELD(arg0, u16 *, 0x4A) = temp_v1;
    return M2C_FIELD(arg0, s16 *, 0x60) >= (s16) temp_v1;
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateTownBarrelChildTransforms);

extern u8 D_800BF9D2;
u8 *func_80146348(u8 *a, void *b);
void f_HandleTownBarrelSeesawController(u8 *a)
{
    u16 f;

    switch (a[4]) {
    case 0:
        f_InitializeTownBarrelSeesawController(a);
        break;
    case 1:
        if (func_80130AC4(a) != 0) {
            a[1] = 1;
            func_80077EBC(a);
        }
        switch (a[5]) {
        case 0:
            func_8012F494(a);
            break;
        case 1:
            if (D_1F800137 == 0) {
                f_UpdateBarrelSeesawRide(a);
            }
            break;
        case 2:
            f_RotateSelectedTownBarrel(a);
            break;
        case 3:
            func_80130524(a);
            break;
        case 4:
            f_BeginScriptedBarrelRotation(a);
            break;
        case 5:
            func_8018C820(a);
            break;
        }
        f_TriggerBarrelLinkedSegments(a);
        func_801316CC(a);
        if (D_800BF9D2 == 0) {
            if (!(M2C_FIELD(a, u16 *, 0x78) & 1)) {
                M2C_FIELD(a, u16 *, 0x78) = 5;
                a[5] = 4;
                a[6] = 0;
            }
        } else if (D_800BF9D2 == 0xFF) {
            if (!(M2C_FIELD(a, u16 *, 0x78) & 1)) {
                M2C_FIELD(a, s16 *, 0x78) = -0x7FFB;
                a[5] = 4;
                a[6] = 0;
            }
        } else {
            f = M2C_FIELD(a, u16 *, 0x78);
            if (f & 1) {
                if (f & 0x8000) {
                    M2C_FIELD(a, s16 *, 0x78) = -0x7FFE;
                } else {
                    M2C_FIELD(a, u16 *, 0x78) = 2;
                }
                if (M2C_FIELD(a, s16 *, 0x48) > 0) {
                    M2C_FIELD(a, s16 *, 0x4E) = -0x80;
                } else if (M2C_FIELD(a, s16 *, 0x48) < 0) {
                    M2C_FIELD(a, s16 *, 0x4E) = 0x80;
                }
            }
        }
        if (a[3] == 0) {
            func_80146348(a, M2C_FIELD(a, u8 **, 0xC8));
        }
        if (a[1] != 0) {
            f_UpdateTownBarrelChildTransforms(a);
        }
        a[0x2B] = 0;
        break;
    case 2:
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_InitializeTownBarrelSeesawController);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8012F494);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateBarrelSeesawRide);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_RotateSelectedTownBarrel);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80130524);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80130788);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_HandleBarrelSeesawContact);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80130AC4);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateBarrelLinkedSegmentSequence);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_TriggerBarrelLinkedSegments);

typedef struct {
    u8 flags;
    u8 pad;
    s16 id;
} PickupLink;
extern PickupLink D_801485BC[];
void f_HideCollectedBarrelLinkedPickups(AreaPartsOwner *a) {
    PickupLink *t = D_801485BC;
    s16 i = 2;
    s16 k = (s8)a->pad[0x63] & 0x7F;
    PickupLink *e;
    u8 r;

loop:
    e = &t[k];
    if ((e++)[1].flags & 0x80) {
        r = func_8004D868(e->id, 1);
    } else {
        r = func_8004D7EC(e->id, 1);
    }
    if (r != 0) {
        a->parts[i][0x3E] |= 0x10;
    }
    if (i == 2 && (M2C_FIELD(a, u16 *, 0x60) & 2)) {
        i++;
        k++;
        if (i < 4) {
            goto loop;
        }
    }
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_BeginScriptedBarrelRotation);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateBarrelSeesawSupportHeight);

void f_ApplyBarrelSeesawContactImpulse(u8 *a) {
    u8 k = a[0x2B];
    s32 t;

    if (k == 0) {
        return;
    }
    switch (a[0x47] & 3) {
    case 0:
        if (k != 2) {
            M2C_FIELD(a, s16 *, 0x48) -= 0x2000;
        } else {
            M2C_FIELD(a, s16 *, 0x48) += 0x2000;
        }
        break;
    case 2:
        if (k == 2) {
            M2C_FIELD(a, s16 *, 0x48) -= 0x2000;
        } else {
            M2C_FIELD(a, s16 *, 0x48) += 0x2000;
        }
        break;
    }
    t = a[0x2B];
    a[0x2B] = 0;
    a[6] = 1;
    M2C_FIELD(a, s16 *, 0x6C) = t;
}

void f_RestoreTownBarrelOrientations(void *arg0) {
    s16 temp_v0;

    if ((M2C_FIELD(arg0, u16 *, 0x60) & 4) && ((M2C_FIELD(arg0, s16 *, 0x62) & 0xFF00) != 0xFF00)) {
        temp_v0 = 1 << ((u32) ((u16) M2C_FIELD(arg0, s16 *, 0x62) & 0x7F00) >> 8);
        if (D_800BF9D2 & temp_v0) {
            M2C_FIELD(M2C_FIELD(arg0, void **, 0xC8), s16 *, 0xC) = 0x800;
        } else {
            M2C_FIELD(M2C_FIELD(arg0, void **, 0xC8), s16 *, 0xC) = 0;
        }
        if ((M2C_FIELD(arg0, u16 *, 0x60) & 2) && !(M2C_FIELD(arg0, s16 *, 0x62) & 0x8000)) {
            if (D_800BF9D2 & (s16) (temp_v0 * 2)) {
                M2C_FIELD(M2C_FIELD(arg0, void **, 0xCC), s16 *, 0xC) = 0x800;
                return;
            }
            M2C_FIELD(M2C_FIELD(arg0, void **, 0xCC), s16 *, 0xC) = 0;
        }
    }
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_801316CC);

void f_ActivateBarrelLinkedSegmentPair(AreaPartsOwner *a, s16 k0, s16 flag) {
    s16 k = k0;
    s16 t = (flag != 0) << 11;
    s16 ang;

    if ((a->pad[0x5E] & 2) && M2C_FIELD(a, s16 *, 0x6C) == k) {
        ang = M2C_FIELD(a, u16 *, 0x6E) & 0xFFF;
    } else {
        ang = M2C_FIELD(a->parts[k], u16 *, 0xC);
    }
    if (ang == t) {
        k = k * 4 - 2;
    } else {
        k = k * 4 - 4;
    }
    if (!(M2C_FIELD(a, u16 *, 0x60) & 2)) {
        k--;
    }
    a->parts[k][0x3E] = 1;
    a->parts[k + 1][0x3E] = 1;
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80131840);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80131D08);

s32 f_SettleDryingRackGrabHandleRotation(AreaPartsOwner *a) {
    s16 v = M2C_FIELD(a, s16 *, 0x44);
    s16 ang = M2C_FIELD(a->parts[0], u16 *, 0xC);
    ang &= 0xFFF;

    if (v > 0) {
        v -= 10;
        if (v < 0) {
            v = 0;
        }
    } else {
        v += 10;
        if (v > 0) {
            v = 0;
        }
    }
    if (ang > 0x800) {
        ang += v;
        if (ang >= 0x1000) {
        settle:
            if (abs(v) < 0x8C) {
                return 1;
            }
        } else if (v < 0x96) {
            v += 0x1E;
        }
    } else {
        ang += v;
        if (ang <= 0) {
            goto settle;
        }
        if (v >= -0x95) {
            v -= 0x1E;
        }
    }
    M2C_FIELD(a, s16 *, 0x44) = v;
    M2C_FIELD(a->parts[0], s16 *, 0xC) = ang;
    return 0;
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateDryingRackGrabHandle);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80132400);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80132548);

extern s8 D_1F800160[];
void func_8013259C(void *arg0) {
    u8 temp_a0;
    u8 temp_v1;
    u8 temp_v1_2;

    temp_a0 = M2C_FIELD(arg0, u8 *, 4);
    switch (temp_a0) {                              /* switch 1; irregular */
    case 0:                                         /* switch 1 */
        func_8013272C(arg0);
        return;
    case 1:                                         /* switch 1 */
        temp_v1 = M2C_FIELD(arg0, u8 *, 3);
        if ((temp_v1 == temp_a0) || (temp_v1 == 5)) {
            if ((D_800BF89C == 2) || (D_800E7EAA != temp_a0)) {
                goto block_13;
            }
        } else {
block_13:
            if (*((s16 *)D_1F800160) < 0x4651) {
                func_8007778C(arg0);
            }
        }
        temp_v1_2 = M2C_FIELD(arg0, u8 *, 5);
        switch (temp_v1_2) {                        /* switch 2; irregular */
        case 0:                                     /* switch 2 */
            func_80132954(arg0);
            break;
        case 2:                                     /* switch 2 */
            func_80132D58(arg0);
            break;
        case 3:                                     /* switch 2 */
            f_UpdateAquaticPlantGrabMotion(arg0);
            break;
        case 4:                                     /* switch 2 */
            func_80133500(arg0);
            break;
        }
        f_UpdateAquaticPlantRotationKick(arg0);
        f_UpdateAquaticPlantHitWobble(arg0);
        M2C_FIELD(arg0, s8 *, 0x29) = 0;
        if (M2C_FIELD(arg0, u8 *, 1) != 0) {
            func_800518FC(arg0);
            return;
        }
        return;
    case 2:                                         /* switch 1 */
        func_80133184(arg0);
        return;
    case 3:                                         /* switch 1 */
        func_8007A624(arg0);
        break;
    }
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8013272C);

extern s8 D_1F80017C[];
typedef struct { s16 x, y, z; } AreaVec3s;
extern AreaVec3s D_8014A684[];
void func_80132954(u8 *a) {
    s16 i;

    switch (a[6]) {
    case 0:
        if (--M2C_FIELD(a, s16 *, 0x40) <= 0) {
            a[6]++;
        }
        break;
    case 1:
        if (!(*(u16 *)D_1F80017C & 0xF)) {
            M2C_FIELD(a, s16 *, 0xB8) = D_8014A684[M2C_FIELD(a, s16 *, 0x7A)].x;
            M2C_FIELD(a, s16 *, 0xBA) = D_8014A684[M2C_FIELD(a, s16 *, 0x7A)].y;
            M2C_FIELD(a, s16 *, 0xBC) = D_8014A684[M2C_FIELD(a, s16 *, 0x7A)].z;
            M2C_FIELD(a, s16 *, 0x7A) = (M2C_FIELD(a, s16 *, 0x7A) + 1) & 7;
        }
        break;
    }
    if ((s16)f_SyncAquaticPlantLinkedState(a) == 0 && (s16)f_ClassifyAquaticPlantContact(a) == 1) {
        f_ConfigureAquaticPlantMotion(a, 0);
        a[5] = 3;
        a[6] = 0;
        M2C_FIELD(a, s16 *, 0x6C) = 0;
    }
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateAquaticPlantHitWobble);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80132D58);

extern u8 D_800E7E80[];
void f_UpdateAquaticPlantGrabMotion(u8 *a)
{
    s32 r = 0;
    s32 t;
    u8 *g;

    switch (a[6]) {
    case 0:
        M2C_FIELD(*(u8 **)(a + 0xC0), u16 *, 0x38) += M2C_FIELD(a, u16 *, 0x4E);
        M2C_FIELD(*(u8 **)(a + 0xC0), u16 *, 0x3A) -= M2C_FIELD(a, u16 *, 0x50);
        if (M2C_FIELD(*(u8 **)(a + 0xC0), u16 *, 0x3A) < M2C_FIELD(a, s16 *, 0x74) - M2C_FIELD(a, s16 *, 0x40)) {
            M2C_FIELD(*(u8 **)(a + 0xC0), u16 *, 0x3A) = M2C_FIELD(a, s16 *, 0x74) - M2C_FIELD(a, s16 *, 0x40);
            r = 1;
        }
        t = r;
        break;
    case 1:
        M2C_FIELD(*(u8 **)(a + 0xC0), u16 *, 0x38) -= M2C_FIELD(a, u16 *, 0x4E);
        M2C_FIELD(*(u8 **)(a + 0xC0), u16 *, 0x3A) += M2C_FIELD(a, u16 *, 0x50);
        if (M2C_FIELD(a, s16 *, 0x74) + M2C_FIELD(a, s16 *, 0x40) < M2C_FIELD(*(u8 **)(a + 0xC0), u16 *, 0x3A)) {
            M2C_FIELD(*(u8 **)(a + 0xC0), u16 *, 0x3A) = M2C_FIELD(a, s16 *, 0x74) + M2C_FIELD(a, s16 *, 0x40);
            r = 1;
        }
        t = r;
        break;
    default:
        t = r;
    }
    if (t) {
        M2C_FIELD(a, s16 *, 0x40) -= M2C_FIELD(a, s16 *, 0x4A);
        if (M2C_FIELD(a, s16 *, 0x40) <= 0) {
            M2C_FIELD(*(u8 **)(a + 0xC0), u16 *, 0x3A) = M2C_FIELD(a, s16 *, 0x74);
            if (M2C_FIELD(a, s16 *, 0x68) == 1 || M2C_FIELD(a, s16 *, 0x6C) != 0) {
                M2C_FIELD(*(u8 **)(a + 0xC0), u16 *, 0x38) = M2C_FIELD(a, s16 *, 0x64);
                M2C_FIELD(*(u8 **)(a + 0xC0), u16 *, 0x3A) = M2C_FIELD(a, s16 *, 0x66);
                a[5] = 0;
                a[6] = 0;
                M2C_FIELD(a, s16 *, 0x40) = 0x14;
            } else {
                a[5] = 4;
            }
            return;
        }
        a[6] = 1 - a[6];
    }
    if (M2C_FIELD(a, s16 *, 0x6C) == 0) {
        if (a[0x5E] == 0) {
            if (a[0x29] != 0 && a[6] == 0) {
                g = D_800E7E80;
                if (!(g[0x145] & 1) && g[0x164] == 0) {
                    M2C_FIELD(g, u16 *, 0x32) += 5;
                }
            }
        } else {
            f_ConfigureAquaticPlantMotion(a, a[0x5E]);
            a[6] = 1;
            M2C_FIELD(a, s16 *, 0x6C) = 1;
        }
    } else if ((s16)f_ClassifyAquaticPlantContact(a)) {
        M2C_FIELD(*(u8 **)(a + 0xC0), u16 *, 0x38) = M2C_FIELD(a, s16 *, 0x64);
        M2C_FIELD(*(u8 **)(a + 0xC0), u16 *, 0x3A) = M2C_FIELD(a, s16 *, 0x66);
        f_ConfigureAquaticPlantMotion(a, 0);
        a[6] = 0;
        M2C_FIELD(a, s16 *, 0x6C) = 0;
    }
    if (M2C_FIELD(a, s16 *, 0x50) > 0x20) {
        M2C_FIELD(a, s16 *, 0x50)--;
    }
    f_UpdateAquaticPlantCollisionBounds(a);
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80133184);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_SyncAquaticPlantLinkedState);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_SpawnAquaticPlantActors);

void func_80133500(u8 *a)
{
    if (a[0x29] == 0) {
        f_ConfigureAquaticPlantMotion(a, 1);
        a[5] = 3;
        a[6] = 1;
        *(s16 *)(a + 0x6C) = 1;
    }
}

#define P0(a) M2C_FIELD(a, u8 **, 0xC0)
typedef union {
    u8 b[0xC0];
    s16 h[0x60];
} ActorH;
#define H(o) h[(o) / 2]
void f_UpdateAquaticPlantRotationKick(u8 *a) {
    switch (F16(a, 0x78)) {
    case 1:
        F16(P0(a), 0xC) = FU16(P0(a), 0xC) + FU16(P0(a), 0x14);
        F16(P0(a), 0x14) -= 8;
        if (F16(P0(a), 0x14) < -0x20) {
            F16(a, 0x78) = 0;
            F16(P0(a), 0xC) = 0;
        }
        break;
    case 2:
        F16(P0(a), 0xC) = FU16(P0(a), 0xC) - FU16(P0(a), 0x14);
        F16(P0(a), 0x14) -= 8;
        if (F16(P0(a), 0x14) < -0x20) {
            F16(a, 0x78) = 0;
            F16(P0(a), 0xC) = 0;
        }
        break;
    }
    if (a[0x2B] != 0) {
        F16(a, 0x78) = 0;
        F16(P0(a), 0xC) = 0;
    }
}

void f_ConfigureAquaticPlantMotion(ActorH *a, s16 k) {
    a->H(0x50) = a->H(0x4E) = a->H(0x62) * 32 + 0x30;
    switch (k) {
    case 0:
        a->H(0x4A) = 0x10;
        a->H(0x74) = a->H(0x66) - (a->H(0x66) >> 4);
        a->H(0x40) = a->H(0x66) >> 5;
        break;
    case 1:
        a->H(0x4A) = 0x20;
        a->H(0x74) = a->H(0x66);
        a->H(0x40) = a->H(0x66) >> 5;
        a->H(0x40) += a->H(0x66) >> 6;
        break;
    case 2:
        a->H(0x4A) = 0x40;
        a->H(0x74) = a->H(0x66);
        a->H(0x40) = a->H(0x66) >> 3;
        a->H(0x4E) += 0x70;
        a->H(0x50) += 0x70;
        break;
    }
}

s32 f_ClassifyAquaticPlantContact(u8 *a) {
    if (a[0x29] != 0) {
        if (M2C_FIELD(a, s16 *, 0x78) == 0) {
            if (M2C_FIELD(a, s16 *, 0x44) > 0) {
                M2C_FIELD(a, s16 *, 0x78) = 1;
                M2C_FIELD(M2C_FIELD(a, u8 **, 0xC0), s16 *, 0x14) = 0x20;
            } else if (M2C_FIELD(a, s16 *, 0x44) < 0) {
                M2C_FIELD(a, s16 *, 0x78) = 2;
                M2C_FIELD(M2C_FIELD(a, u8 **, 0xC0), s16 *, 0x14) = 0x20;
            }
        }
        if (M2C_FIELD(a, s16 *, 0x68) == 0) {
            return 1;
        }
        return 2;
    }
    return 0;
}

void f_UpdateAquaticPlantCollisionBounds(u8 *a) {
    s32 k1, k2, t;

    if (a[3] == 5) {
        k1 = 0x76;
        k2 = 0xF5;
    } else {
        k1 = 0x80;
        k2 = 0x113;
    }
    t = (k1 * M2C_FIELD(M2C_FIELD(a, u8 **, 0xC0), u16 *, 0x38)) >> 12;
    M2C_FIELD(a, s16 *, 0x80) = t;
    M2C_FIELD(a, s16 *, 0x82) = t << 1;
    t = (k2 * M2C_FIELD(M2C_FIELD(a, u8 **, 0xC0), u16 *, 0x3A)) >> 12;
    M2C_FIELD(a, s16 *, 0x84) = t;
    M2C_FIELD(a, s16 *, 0x86) = t << 1;
}

#define SWH(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define SWU(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define PP(p) (*(u8 **)((u8 *)(p) + 0xC0))
extern s16 D_8014A6E4[];
extern s16 D_8014A6F4[][2];
static inline s32 swing_hit(u8 *a) {
    if (a[0x2B] != 0) {
        a[6] = 4;
        if (func_80077768(a[0x5F] << 4, SWH(a, 0x56), 0)) {
            SWH(a, 0x44) = 0x100;
        } else {
            SWH(a, 0x44) = -0x100;
        }
        a[0x2B] = 0;
        return 1;
    }
    return 0;
}
void f_UpdateSingleSegmentSwingMotion(u8 *a) {
    u8 *t = D_800E7E80;
    s16 ang;
    s16 vel;

    if (SWH(a, 0x62) != 0) {
        SWH(a, 0x62) = 0;
        SWH(a, 0x32) = D_8014A6E4[a[3]];
        a[6] = 0;
        SWH(PP(a), 0xC) = 0;
        SWH(a, 0x44) = 0;
    }
    switch (a[6]) {
    case 0:
        SWH(a, 0x42) = 0;
        a[6] = 1;
    case 1:
        if (a[0x29] == 0) {
            if (swing_hit(a)) {
                break;
            }
            if (a[0x46] != 0) {
                a[0x46]--;
                break;
            }
            SWH(PP(a), 0xC) = (u32)func_80083F50(SWH(a, 0x42)) >> 5;
            SWH(a, 0x42) += 0x44 + (func_8009A450() >> 8);
            break;
        }
        a[6] = 2;
    case 2:
        if (a[0x29] == 0) {
            a[6] = 3;
            break;
        }
        if (t[0x147] != 0) {
            SWH(PP(a), 0xC) = -SWH(t, 0x58);
        } else {
            SWH(PP(a), 0xC) = SWH(t, 0x58);
        }
        if (t[0x168] >= 3) {
            if (t[0x147] != 0) {
                SWH(a, 0x32) -= (t[0x168] - 2) * 6;
            } else {
                SWH(a, 0x32) += (t[0x168] - 2) * 6;
            }
            if (SWH(a, 0x32) < D_8014A6F4[a[3]][1]) {
                SWH(a, 0x32) = D_8014A6F4[a[3]][1];
            }
            if (D_8014A6F4[a[3]][0] < SWH(a, 0x32)) {
                SWH(a, 0x32) = D_8014A6F4[a[3]][0];
            }
        }
        break;
    case 3:
        switch (t[0x168]) {
        case 0:
            SWH(a, 0x44) = 0x20;
            break;
        case 1:
            SWH(a, 0x44) = 0x30;
            break;
        case 2:
            SWH(a, 0x44) = 0x40;
            break;
        default:
            SWH(a, 0x44) = 0x80;
            break;
        }
        if (t[0x147] != 0) {
            SWH(a, 0x44) = -SWH(a, 0x44);
        }
        a[6] = 4;
    case 4:
        if (a[0x29] != 0) {
            a[6] = 1;
            break;
        }
        if (swing_hit(a)) {
            break;
        }
        vel = SWH(a, 0x44);
        ang = SWH(PP(a), 0xC);
        ang += vel;
        if ((u16)(ang + 0x800) > 0x1000) {
            ang &= 0xFFF;
            if (ang > 0x800) {
                ang |= 0xF000;
            }
        }
        if (vel > 0) {
            vel -= 8;
            if (vel < 0) {
                vel = 0;
            }
        } else {
            vel += 8;
            if (vel > 0) {
                vel = 0;
            }
        }
        if (ang > 0) {
            vel -= 0x14;
        } else {
            vel += 0x14;
        }
        if (abs(ang) < 0x20 && abs(vel) < 0x14) {
            ang = 0;
            vel = 0;
            a[6] = 0;
        }
        SWH(a, 0x44) = vel;
        SWH(PP(a), 0xC) = ang;
        break;
    }
}

void f_HandleSingleSegmentSwingActor(u8 *a)
{
    s16 v;

    switch (a[4]) {
    case 0:
        if (func_80051B70(a, 0xC, 0x14) != 0) {
            break;
        }
        a[0x2A] = 0x22;
        M2C_FIELD(a, s16 *, 0x80) = 0x1E;
        M2C_FIELD(a, s16 *, 0x82) = 0x3C;
        M2C_FIELD(a, s16 *, 0x84) = 0x32;
        a[4] = 1;
        a[0] = 1;
        a[0x29] = 0;
        a[0x46] = 0;
        M2C_FIELD(a, s16 *, 0x86) = 0x64;
        func_8004766C(a);
        M2C_FIELD(a, s16 *, 0x42) = 0;
        v = D_8014A6E4[a[3]];
        M2C_FIELD(a, s16 *, 0x60) = -0xC8;
        M2C_FIELD(a, s16 *, 0x32) = v;
        break;
    case 1:
        f_UpdateSingleSegmentSwingMotion(a);
        if (D_800E7EAA < 0x1C) {
            M2C_FIELD(a, s16 *, 0x62) = 1;
            break;
        }
        if (D_800E7EAA == 0x22) {
            a[1] = 1;
            func_80077EBC(a);
        } else if (func_800778E4(a, M2C_FIELD(a, s16 *, 0x60)) == 0) {
            M2C_FIELD(a, s16 *, 0x62) = 1;
            break;
        }
        func_8004766C(a);
        func_800517F8(a);
        break;
    case 2:
    case 3:
        func_8007A624(a);
        break;
    }
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80133D6C);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_DrawNetBridgeStrip);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_DrawNetBridgeSupportStrips);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_AnimateNetBridgeCollapse);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateCollapsedNetBridgeMotion);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_ResolveTombaOnNetBridge);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80134C5C);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_ResolveActorOnNetBridge);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80134FD8);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateRopeSwingInteraction);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80135D64);

u8 *func_801360F4(s32 a, u8 b) {
    u8 *p = func_8007A980(2, 4, 0);

    if (p == NULL) {
        return NULL;
    }
    M2C_FIELD(p, void **, 0x1C) = func_80135D64;
    M2C_FIELD(p, s32 *, 0x10) = a;
    p[0x2] = 7;
    p[0x3] = b;
    return p;
}

#define W_d1fb(p, o) (*(s32 *)((u8 *)(p) + (o)))
extern s16 D_1F8001A0;
static inline s32 pend_flag(void) {
    if (D_1F800207_9c67 < 0x18 || D_800BF816 == 1) {
        return 1;
    }
    return 0;
}
void f_HandleA00PendulumPlatformActor(u8 *a)
{
    s16 ang;
    s16 sp;
    s16 z0;

    switch (a[4]) {
    case 0:
        if (func_80051B70(a, 0xC, 6) != 0) {
            return;
        }
        H_f12c(a, 0x80) = 0x240;
        a[0x29] = 0;
        H_f12c(a, 0x82) = 0x480;
        a[0] |= 1;
        func_8004766C(a);
        func_80048750(a);
        H_f12c(a, 0x56) = D_1F8001A0;
        H_f12c(a, 0x90) = H_f12c(a, 0x2E);
        H_f12c(a, 0x92) = H_f12c(a, 0x32);
        H_f12c(a, 0x94) = H_f12c(a, 0x36);
        H_f12c(a, 0x54) = 0;
        H_f12c(a, 0x58) = 0;
        H_f12c(a, 0x62) = 0;
        a[4] = 1;
        a[5] = 0;
        W_d1fb(a, 0x68) = 0;
    case 1:
        switch (a[5]) {
        case 0:
        case 1:
            if (pend_flag()) {
                return;
            }
            H_f12c(a, 0x44) = 0;
            H_f12c(a, 0x40) = 0;
            H_f12c(a, 0x64) = H_f12c(a, 0x44);
            H_f12c(*(u8 **)(a + 0xC0), 0xC) = 0x100;
            a[5] = 2;
        case 2:
            if (D_800BF809 == 0) {
                ang = H_f12c(a, 0x44);
                sp = H_f12c(*(u8 **)(a + 0xC0), 0xC);
                if (ang > 0x500) {
                    ang -= 0x20;
                    if (ang > 0x4000) {
                        ang = 0x4000;
                    } else if (ang < 0) {
                        ang = 0;
                    }
                } else if (ang < -0x500) {
                    ang += 0x20;
                    if (ang < -0x4000) {
                        ang = -0x4000;
                    } else if (ang > 0) {
                        ang = 0;
                    }
                }
                if (a[0x29] == 1) {
                    H_f12c(a, 0x40) = 0;
                    ang += H_f12c(a, 0x60) >> 2;
                } else {
                    ang -= sp / 8;
                }
                sp += ang >> 8;
                if (sp < -0x400) {
                    sp = -0x400;
                    if (ang < 0) {
                        ang = abs(ang) >> 2;
                        if (ang > 0) {
                            ang = 0;
                        }
                    }
                } else if (sp > 0x400) {
                    sp = 0x400;
                    if (ang > 0) {
                        ang = -abs(ang) >> 2;
                        if (ang < 0) {
                            ang = 0;
                        }
                    }
                }
                z0 = H_f12c(a, 0x36);
                H_f12c(a, 0x36) = U(a, 0x94) + ((func_80083E80(sp) * 0x340) >> 12);
                if (a[0x29] == 1) {
                    u8 *e = D_800E7E80;
                    U(e, 0x36) += U(a, 0x36) - z0;
                }
                H_f12c(*(u8 **)(a + 0xC0), 0xC) = sp;
                H_f12c(a, 0x44) = ang;
                a[0x29] = 0;
            }
            if (pend_flag()) {
                a[5] = 1;
            } else {
                if (D_800E7EAA == 0x1F) {
                    func_8007703C(a);
                } else if (D_800E7EAA != 0x22) {
                    func_8007778C(a);
                }
                if (a[1] != 0) {
                    func_800517F8(a);
                    if (D_800BF809 == 0) {
                        if (abs(ang) < 0x100) {
                            func_80074AF0(W_d1fb(a, 0x68));
                            W_d1fb(a, 0x68) = 0;
                        } else if (abs(H_f12c(a, 0x64)) < 0x100) {
                            func_80074AF0(W_d1fb(a, 0x68));
                            W_d1fb(a, 0x68) = func_80074590(0x81, 0, 0);
                        }
                    }
                }
            }
            H_f12c(a, 0x64) = ang;
            break;
        }
        break;
    case 2:
    case 3:
        func_8007A624(a);
        break;
    }
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_801365C4);

#define FP(p, o) M2C_FIELD(p, u8 **, o)
void func_80136748(u8 *a) {
    u8 *c;
    u8 *s;
    func_8003CCA4();
    D_1F8000C0[0] = FU16(FP(a, 0xC8), 0x2C);
    D_1F8000C0[1] = FU16(FP(a, 0xC8), 0x30);
    D_1F8000C0[2] = FU16(FP(a, 0xC8), 0x34) + 0x2E;
    func_80084470(D_1F8000D0_b839 + 0x28, D_1F8000C0, D_1F800000 + 0x14);
    s = D_1F800000;
    c = D_1F8000D0_b839;
    M2C_FIELD(s, s32 *, 0x14) += M2C_FIELD(c, s32 *, 0x3C);
    M2C_FIELD(s, s32 *, 0x18) += M2C_FIELD(c, s32 *, 0x40);
    M2C_FIELD(s, s32 *, 0x1C) += M2C_FIELD(c, s32 *, 0x44);
    func_80084660(D_1F8000D0_b839 + 0x28);
    func_80084690(D_1F800000);
    func_801365C4(a, F16(a, 0xBA));
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8013681C);

#define BH(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define BW(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define BPART(a, i) (*(u8 **)((u8 *)(a) + (i) * 4 + 0xC0))
typedef struct { s32 x, y, z; } BV3W;
typedef struct { s16 a, b, c, d, e; } BRow5;
extern s16 D_800ED098;
extern BRow5 D_8014A7E4[];
extern u8 D_800BF822;
void func_80136954(u8 *a) {
    s32 i, k;
    s16 e;
    BRow5 *r;
    u8 *pa;
    u8 *q;
    u8 *g;
    u8 *t;

    switch (a[4]) {
    case 0:
        if (D_800ED098 < 4) {
            a[4] = 3;
            break;
        }
        a[8] = 4;
        a[9] = 4;
        a[0xB] = 3;
        i = 0;
        a[0xD] = 0;
        a[4]++;
        if (a[8] != 0) {
            r = D_8014A7E4;
            pa = a;
        loop:
                q = func_8007AAE8();
                *(u8 **)(pa + 0xC0) = q;
                BH(q, 6) = r->a;
                BH(*(u8 **)(pa + 0xC0), 0) = r->b;
                BH(*(u8 **)(pa + 0xC0), 2) = r->c;
                BH(*(u8 **)(pa + 0xC0), 4) = r->d;
                BW(*(u8 **)(pa + 0xC0), 8) = 0;
                BW(*(u8 **)(pa + 0xC0), 0xC) = 0;
                func_80051B04(*(u8 **)(pa + 0xC0), 0xC, r->e);
                i++;
                r++;
                pa += 4;
                if (i < a[8]) {
                    goto loop;
                }
        }
        BH(a, 0x60) = 0xF;
        BH(a, 0x62) = 0x3BBF;
        BH(a, 0x64) = 0x70F0;
        BH(a, 0x66) = 0x70F8;
        BH(a, 0x68) = -0x7710;
        BH(a, 0x6A) = -0x7708;
        BH(a, 0x6C) = 0x28;
        BH(a, 0x6E) = 0;
        BH(a, 0xBA) = 0xF0;
        BH(a, 0x50) = 0;
        a[0x2B] = 0;
        break;
    case 1:
        if (func_8007778C(a) == 0) {
            break;
        }
        switch (a[5]) {
        case 1:
            break;
        case 0:
            if (D_800BF870.pad1[0x48] == 0xFF) {
                if (D_800BF870.pad1[0xC6] == 0) {
                    func_80051B04(*(u8 **)(a + 0xC0), 0xC, 0xB);
                    a[5] = 1;
                } else if (!(D_800BF870.pad1[0x1DA] & 1)) {
                    a[0] = 1;
                    BH(a, 0x80) = 0x15E;
                    BH(a, 0x82) = 0x2BC;
                    BH(a, 0x84) = 0xC8;
                    BH(a, 0x86) = 0x190;
                    func_80051B04(*(u8 **)(a + 0xC0), 0xC, 0xB);
                    a[5] = 4;
                } else {
                    a[5] = 1;
                }
            } else {
                a[5] = 2;
            }
            break;
        case 2:
            if (D_800BF9DD == 0xC) {
                a[5]++;
            }
            break;
        case 3:
            func_8013681C(a);
            break;
        case 4:
            switch (a[6]) {
            case 0:
                if (a[0x2B] == 3) {
                    D_800E7E80[4] = 4;
                    D_800E7E80[5] = 0x21;
                    D_800E7E80[6] = 0;
                    D_800E7E80[0x61] = 0;
                    a[0] = 2;
                    a[6]++;
                    func_80042354(1, 1);
                }
                break;
            case 1:
                if (D_800BF80E != 0) {
                    func_800440E4(D_800E7E80, 0xCF, 4);
                    a[6]++;
                }
                break;
            case 2:
                g = (u8 *)D_800BF808;
                if (g[6] != 0) {
                    u8 *q2 = func_8006FF10(a, 0x24);
                    *(u8 **)(g + 0x3C) = q2;
                    if (q2 != NULL) {
                        t = D_800E7E80;
                        *(BV3W *)(q2 + 0x2C) = *(BV3W *)(t + 0x2C);
                        func_80051B04(*(u8 **)(a + 0xC0), 0xC, 0x4E);
                        D_800BF870.pad1[0x1DA] |= 1;
                        func_800440E4(t, 2, 4);
                        a[6]++;
                    }
                }
                break;
            case 3:
                if (!(D_800BF822 & 1)) {
                    func_80042310();
                    a[6] = 0;
                    a[5] = 1;
                }
                break;
            }
            break;
        }
        func_800517F8(a);
        a[0x2B] = 0;
        break;
    case 2:
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

extern u8 D_800BF89C;
extern u8 D_800E7EAA;
void func_80136D9C(void *arg0) {
    u8 temp_v1;
    u8 temp_v1_2;

    temp_v1 = M2C_FIELD(arg0, u8 *, 4);
    switch (temp_v1) {                              /* switch 1; irregular */
    case 0:                                         /* switch 1 */
        func_80136F08(arg0);
        return;
    case 1:                                         /* switch 1 */
        if ((D_800BF89C == 2) || (M2C_FIELD(arg0, u8 *, 3) != 2) || (D_800E7EAA != temp_v1)) {
            func_8007778C(arg0);
        }
        temp_v1_2 = M2C_FIELD(arg0, u8 *, 5);
        switch (temp_v1_2) {                        /* switch 2; irregular */
        case 0:                                     /* switch 2 */
            if (M2C_FIELD(arg0, u8 *, 3) != 3) {
                func_80138A64(arg0);
            } else {
                func_8018CDC4(arg0);
            }
            break;
        case 1:                                     /* switch 2 */
            if (D_800BF809 == 0) {
                f_UpdateSegmentedTownActorSequence(arg0);
            }
            break;
        case 2:                                     /* switch 2 */
            func_8018CA1C(arg0);
            break;
        }
        if (M2C_FIELD(arg0, u8 *, 1) != 0) {
            func_801389C8(arg0);
            return;
        }
    case 2:                                         /* switch 1 */
        return;
    case 3:                                         /* switch 1 */
        func_8007A624(arg0);
        break;
    }
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80136F08);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateSegmentedTownActorSequence);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_EmitSegmentedTownActorEffect);

typedef struct { u8 hdr[0x10]; s16 f[9]; s16 pad; } MorphRecA;
typedef struct { u8 hdr[0x14]; s16 f[12]; } MorphRecB;
typedef struct { u8 pad[0xC0]; u8 *parts[2]; } MorphActor;
extern u8 *D_800ECFC8;
extern s16 D_8014C4FC[];
extern s16 D_8014C60C[];
extern s16 D_8014C63C[];
extern s16 D_8014C74C[];
void f_ConfigureSegmentedTownActorMorph(u8 *a, s16 n, s16 sel) {
    u8 *base;
    s32 *offs;
    u8 *from, *to, *p;
    MorphRecA *ra, *fa, *ta;
    MorphRecB *rb, *fb, *tb;
    s16 *d1, *d2;
    s32 i;
    s32 cnt;

    if (a[3] == 0) return;
    *(s16 *)(a + 0x60) = n;
    base = D_800ECFC8;
    offs = (s32 *)(base + 4);
    switch (sel) {
    case 0:
        from = base + offs[0x18];
        to = base + offs[0x19];
        break;
    case 1:
        from = base + offs[0x19];
        to = base + offs[0x1A];
        break;
    case 2:
        from = base + offs[0x1A];
        to = base + offs[0x19];
        break;
    case 3:
        from = base + offs[0x19];
        to = base + offs[0x18];
        break;
    case 4:
        to = base + offs[0x18];
        from = *(u8 **)(((MorphActor *)a)->parts[a[9] - 1] + 0x40);
        break;
    }
    p = *(u8 **)(((MorphActor *)a)->parts[a[9] - 1] + 0x40);
    cnt = *(u16 *)p;
    ra = (MorphRecA *)(p + 0x10);
    rb = (MorphRecB *)&ra[cnt];
    fa = (MorphRecA *)(from + 0x10);
    fb = (MorphRecB *)&fa[cnt];
    ta = (MorphRecA *)(to + 0x10);
    tb = (MorphRecB *)&ta[cnt];
    if (a[3] & 1) {
        d1 = D_8014C4FC;
        d2 = D_8014C60C;
    } else if (a[3] == 2) {
        d1 = D_8014C63C;
        d2 = D_8014C74C;
    }
    for (i = 0; i < cnt; i++) {
        d1[0] = (ta->f[0] - fa->f[0]) / n;
        d1[1] = (ta->f[1] - fa->f[1]) / n;
        d1[2] = (ta->f[2] - fa->f[2]) / n;
        d1[3] = (ta->f[4] - fa->f[4]) / n;
        d1[4] = (ta->f[5] - fa->f[5]) / n;
        d1[5] = (ta->f[3] - fa->f[3]) / n;
        d1[6] = (ta->f[6] - fa->f[6]) / n;
        d1[7] = (ta->f[7] - fa->f[7]) / n;
        d1[8] = (ta->f[8] - fa->f[8]) / n;
        ra->f[0] = fa->f[0];
        ra->f[1] = fa->f[1];
        ra->f[2] = fa->f[2];
        ra->f[4] = fa->f[4];
        ra->f[5] = fa->f[5];
        ra->f[3] = fa->f[3];
        ra->f[6] = fa->f[6];
        ra->f[7] = fa->f[7];
        ra->f[8] = fa->f[8];
        d1 += 9;
        fa++;
        ta++;
        ra++;
    }
    cnt = *(u16 *)(p + 2);
    for (i = 0; i < cnt; i++) {
        d2[0] = (tb->f[0] - fb->f[0]) / n;
        d2[1] = (tb->f[1] - fb->f[1]) / n;
        d2[2] = (tb->f[2] - fb->f[2]) / n;
        d2[3] = (tb->f[4] - fb->f[4]) / n;
        d2[4] = (tb->f[5] - fb->f[5]) / n;
        d2[5] = (tb->f[3] - fb->f[3]) / n;
        d2[6] = (tb->f[6] - fb->f[6]) / n;
        d2[7] = (tb->f[7] - fb->f[7]) / n;
        d2[8] = (tb->f[8] - fb->f[8]) / n;
        d2[9] = (tb->f[10] - fb->f[10]) / n;
        d2[10] = (tb->f[11] - fb->f[11]) / n;
        d2[11] = (tb->f[9] - fb->f[9]) / n;
        rb->f[0] = fb->f[0];
        rb->f[1] = fb->f[1];
        rb->f[2] = fb->f[2];
        rb->f[4] = fb->f[4];
        rb->f[5] = fb->f[5];
        rb->f[3] = fb->f[3];
        rb->f[6] = fb->f[6];
        rb->f[7] = fb->f[7];
        rb->f[8] = fb->f[8];
        rb->f[10] = fb->f[10];
        rb->f[11] = fb->f[11];
        rb->f[9] = fb->f[9];
        d2 += 12;
        fb++;
        tb++;
        rb++;
    }
}

typedef struct { u8 pad[0x10]; s16 v[9]; s16 pad2; } MV9;
typedef struct { u8 pad[0x14]; s16 v[12]; } MV12;
s32 func_801386A0(u8 *a) {
    u8 k = a[3];
    u16 *h;
    MV9 *p;
    MV12 *q;
    s16 *s;
    s16 *u;
    s32 i;
    s32 n;

    if (k == 0) {
        return 0;
    }
    h = *(u16 **)(((MorphActor *)a)->parts[a[9] - 1] + 0x40);
    n = h[0];
    p = (MV9 *)(h + 8);
    q = (MV12 *)(p + n);
    if (k & 1) {
        s = D_8014C4FC;
        u = D_8014C60C;
    } else if (k == 2) {
        s = D_8014C63C;
        u = D_8014C74C;
    }
    for (i = 0; i < n; i++) {
        p->v[0] += s[0];
        p->v[1] += s[1];
        p->v[2] += s[2];
        p->v[4] += s[3];
        p->v[5] += s[4];
        p->v[3] += s[5];
        p->v[6] += s[6];
        p->v[7] += s[7];
        p->v[8] += s[8];
        s += 9;
        p++;
    }
    n = h[1];
    for (i = 0; i < n; i++) {
        q->v[0] += u[0];
        q->v[1] += u[1];
        q->v[2] += u[2];
        q->v[4] += u[3];
        q->v[5] += u[4];
        q->v[3] += u[5];
        q->v[6] += u[6];
        q->v[7] += u[7];
        q->v[8] += u[8];
        q->v[10] += u[9];
        q->v[11] += u[10];
        q->v[9] += u[11];
        u += 12;
        q++;
    }
    return --*(s16 *)(a + 0x60) == 0;
}

void func_80136D9C();
void f_SpawnSegmentedTownActor(u8 *a) {
    u8 *p = func_80072DDC(a, 3, 4, 0xA);

    if (p != NULL) {
        M2C_FIELD(p, void **, 0x1C) = func_80136D9C;
        M2C_FIELD(p, s16 *, 0x2E) = M2C_FIELD(a, s16 *, 0x2E);
        M2C_FIELD(p, s16 *, 0x32) = M2C_FIELD(a, s16 *, 0x32);
        M2C_FIELD(p, s16 *, 0x36) = M2C_FIELD(a, s16 *, 0x36);
        if (a[3] != 0) {
            p[3] = a[3];
        } else if (D_800BF89C == 2) {
            p[3] = 3;
        } else {
            p[3] = 0;
        }
    }
}

typedef struct {
    u8 b[0xC0];
    u8 *parts[1];
} PartsActor;
void func_801389C8(PartsActor *a0) {
    PartsActor *a = a0;
    s32 pad[4];
    s32 i;
    u8 *p;

    func_80051C8C(a);
    for (i = 0; i < a->b[8]; i++) {
        p = a->parts[i];
        func_800517BC(D_1F800000, M2C_FIELD(p, s16 *, 0x38), M2C_FIELD(p, s16 *, 0x3A), M2C_FIELD(p, s16 *, 0x3C));
        func_80084250(p + 0x18, D_1F800000);
    }
}

void func_80138A64(u8 *a) {
    u8 *p;

    if (M2C_FIELD(a, s16 *, 0x6A) != 0 && a[3] != 0) {
        if (--M2C_FIELD(a, s16 *, 0x40) < 0) {
            D_800BF821 = 0;
            M2C_FIELD(a, s16 *, 0x6A) = 0;
        }
    }
    p = M2C_FIELD(a, u8 **, 0x10);
    if (M2C_FIELD(a, s16 *, 0x6A) == 0 && M2C_FIELD(p, s16 *, 0x76) == 1) {
        if (a[3] != 0 && M2C_FIELD(p, s16 *, 0x78) == 0) {
            D_800BF821 = 1;
        }
        a[6] = 0;
        a[5]++;
    }
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_HandleA00Warp0813Entrance);

extern u8 D_800BF8F9;
extern u8 D_800E7FF4;
extern u8 D_8014AA00[];
void f_HandleTinyMousesHouseEntrance(u8 *a) {
    u8 *g = D_800E7E80;
    s32 k;

    if (g[0x174] & 4) {
        switch (a[6]) {
        case 0:
            if (D_800BF871 == 9) {
                a[0] = 2;
                H_f12c(a, 0x50) = 0x400;
                a[6]++;
                func_80072EFC(a);
                H_f12c(a, 0x40) = 0xF;
            } else {
                a[6] = 3;
            }
            break;
        case 1:
            if (--H_f12c(a, 0x40) == -1) {
                a[6]++;
            }
            break;
        case 2:
            if (func_80072F14(a) != 0) {
                a[0] = 1;
                a[6]++;
                D_800BF871 = 0;
            }
            break;
        case 3:
            if (a[0x29] != 0 && g[0x29] != 0 && g[0x17B] == 0) {
                if (D_1F800137 == 0) {
                    D_1F800137 = 2;
                }
                if (D_800BF8F9 == 0) {
                    func_80040B48(0x45);
                    a[6]++;
                } else {
                    a[6] += 2;
                    func_80074590(0x17, 0, 0xF);
                }
            }
            break;
        case 4:
            if (func_80042728(g) != 0) {
                a[6]++;
                func_80074590(0x17, 0, 0xF);
            }
            break;
        case 5:
            if (func_80072E60(a) != 0) {
                a[6]++;
                D_1F800236 = 1;
                D_800BF808[0x31] = 1;
                D_800BF808[7] = 2;
                H_f12c(D_800BF808, 0x32) = 0x1400;
            }
            break;
        }
    }
    k = a[5];
    switch (k) {
    case 0:
        if (!(D_800E7FF4 & 4) && D_800BF8F9 == 0 && (*(u32 *)(a + 0x28) & 0xFF00FF00)) {
            a[5] = 1;
        }
        break;
    case 1:
        if (func_8005308C() != 0) {
            if (!(D_800E7FF4 & 4)) {
                a[5]++;
                H_f12c(a, 0xB8) = H_f12c(a, 0x60);
                H_f12c(a, 0xBA) = H_f12c(a, 0x62);
                H_f12c(a, 0xBC) = H_f12c(a, 0x64);
                func_80042354(1, 1);
                func_80040CDC(a, 0, D_8014AA00);
                a[0x70] = k;
            } else {
                a[5] = 0;
                func_80040B48(0x45);
            }
        }
        break;
    case 2:
        func_80041098(a);
        if (a[0x70] == 0xFF) {
            func_80042310();
            a[5] = 0;
            a[0x46] = 0;
            H_f12c(a, 0x60) = H_f12c(a, 0xB8);
            H_f12c(a, 0x62) = H_f12c(a, 0xBA);
            H_f12c(a, 0x64) = H_f12c(a, 0xBC);
        }
        break;
    }
    func_800735F4(a, 0x47);
}

typedef struct { s16 x, y, z; u8 b6; u8 pad7; s16 h8, hA; } EntrancePt;
extern u8 D_8014A9A8[];
extern u8 D_8014A9B0[];
extern EntrancePt D_8014A9B8[];
extern u32 D_800BF814;
extern u8 D_800BF81F;
extern u8 D_800BF9DB;
extern u8 D_800E7FC7;
void f_HandleFishermensTownEntranceActor(u8 *a)
{
    u8 v;
    u8 *g;
    u8 *e;
    u8 *g_f;

    switch (a[4]) {
    case 0:
        if (func_80051B70(a, 0xC, D_8014A9A8[a[3]]) != 0) {
            break;
        }
        a[4]++;
        a[0xBF] = 1;
        H_f12c(a, 0x50) = 0;
        a[0x29] = 0;
        a[0x28] |= 0x80;
        H_f12c(a, 0x5A) = H_f12c(a, 0x56);
        v = D_8014A9B0[a[3]];
        if (v != 0) {
            a[0x2A] = v;
            if (D_8014A9B8[a[3]].x != 0) {
                H_f12c(a, 0x60) = D_8014A9B8[a[3]].x - H_f12c(a, 0x2E);
            } else {
                H_f12c(a, 0x60) = D_8014A9B8[a[3]].x;
            }
            if (D_8014A9B8[a[3]].z != 0) {
                H_f12c(a, 0x64) = D_8014A9B8[a[3]].z - H_f12c(a, 0x36);
            } else {
                H_f12c(a, 0x64) = D_8014A9B8[a[3]].z;
            }
            H_f12c(a, 0x62) = D_8014A9B8[a[3]].y;
            a[0x5F] = D_8014A9B8[a[3]].b6;
            H_f12c(a, 0x82) = D_8014A9B8[a[3]].h8;
            H_f12c(a, 0x80) = H_f12c(a, 0x82) / 2;
            {
                s16 t = D_8014A9B8[a[3]].hA;
                a[0] = 1;
                H_f12c(a, 0x86) = t;
            }
            H_f12c(a, 0x84) = H_f12c(a, 0x86) / 2;
        }
        switch (a[3]) {
        case 2:
            a[0x46] = 1;
            g = (u8 *)D_800BF808;
            if (g[0xE] != 0 && g[0xF] == 2) {
                a[4] = 1;
                a[5] = 0;
                a[6] = 2;
                func_80072EFC(a);
            }
            break;
        case 0:
        case 1:
        case 3:
            a[0x46] = 1;
            break;
        case 4:
            a[0x46] = 0;
            break;
        case 5:
            H_f12c(a, 0x56) -= 0x600;
            break;
        }
        break;
    case 1:
        g_f = (u8 *)D_800BF808;
        if (g_f[0xE] != 0) {
            if (g_f[0xF] == a[3]) {
                func_80077EBC(a);
            }
        } else if (a[3] == 2 && D_1F800207_9c67 >= 0x1D) {
            func_8007703C(a);
        } else {
            func_8007778C(a);
        }
        switch (a[3]) {
        case 0:
            e = D_800E7E80;
            switch (a[5]) {
            case 0:
                if (e[0x2A] == a[0x2A] && e[5] == 0) {
                    a[5] = 1;
                    D_1F800137 = 2;
                }
                break;
            case 1:
                a[5] = 2;
                a[0x29] = 1;
                D_800BF81F = (1 - a[0x5F]) << 4;
            case 2:
                if (func_80073328(a) != 0) {
                    a[5]++;
                }
                break;
            case 3:
                if (e[0x2A] != a[0x2A]) {
                    a[5] = 0;
                }
                break;
            }
            break;
        case 1:
            func_80073328(a);
            func_800735F4(a, 0x45);
            break;
        case 2:
            func_80073328(a);
            func_800735F4(a, 0x46);
            if ((D_800BF814 & 0xFFFF0000) == 0x2010000) {
                a[0x2A] = 0x26;
                if (D_800BF8BC == 0xFF) {
                    a[0x5F] = 0;
                } else {
                    a[0x5F] = 1;
                }
            } else {
                a[0x2A] = 0x1F;
                a[0x5F] = 0;
            }
            break;
        case 3:
            switch (a[5]) {
            case 0:
                if (D_800BF9DB & 1) {
                    a[5] = 2;
                } else {
                    a[5] = 1;
                }
                break;
            case 1:
                switch (a[6]) {
                case 0:
                    if (a[0x29] != 0) {
                        a[6] = 1;
                        func_80054198(D_800E7E80);
                        func_8004ED94(0x6D, 0x41);
                        func_80074590(0x19, 0, 0xF);
                    }
                    break;
                case 1:
                    if (a[0x29] == 0 && (D_800E7FC7 & 1) == a[0x5F]) {
                        a[6] = 0;
                    }
                    break;
                }
                break;
            case 2:
                f_HandleA00Warp0813Entrance(a);
                break;
            }
            break;
        case 4:
            f_HandleTinyMousesHouseEntrance(a);
            break;
        case 5:
            break;
        }
        if (a[1] != 0) {
            func_800517F8(a);
        }
        a[0x29] = 0;
        a[0x2B] = 0;
        break;
    case 2:
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

typedef struct { u16 x, y, z, w; } CurvePt;
extern CurvePt D_8014AA38[];
void f_HandleCurvedSupportContactActor(u8 *a)
{
    u8 *p = *(u8 **)(a + 0x10);
    s16 num, den, h;
    s16 t;

    switch (a[4]) {
    case 0:
        if (func_80051B70(a, 0xC, 0x16) != 0) {
            break;
        }
        a[4]++;
        U(a, 0x2E) = D_8014AA38[p[3] * 2 + a[3]].x;
        U(a, 0x32) = D_8014AA38[p[3] * 2 + a[3]].y;
        U(a, 0x36) = D_8014AA38[p[3] * 2 + a[3]].z;
        H_f12c(a, 0x54) = 0;
        if (p[3] == 0) {
            H_f12c(a, 0x56) = 0;
        } else {
            H_f12c(a, 0x56) = 0x400;
        }
        H_f12c(a, 0x58) = 0;
        break;
    case 1:
        if (D_1F800207_9c67 < 0x17 || D_1F800207_9c67 == 0x22) {
            break;
        }
        if (p[3] == 0) {
            if (a[3] == 0) {
                den = U(p, 0x4E) - U(p, 0x80);
                num = U(a, 0x2E) - U(p, 0x80);
            } else {
                den = U(p, 0x82) - U(p, 0x4E);
                num = U(p, 0x82) - U(a, 0x2E);
            }
        } else {
            if (a[3] == 0) {
                den = U(p, 0x52) - U(p, 0x84);
                num = U(a, 0x36) - U(p, 0x84);
            } else {
                den = U(p, 0x86) - U(p, 0x52);
                num = U(p, 0x86) - U(a, 0x36);
            }
        }
        t = (num << 10) / den;
        h = U(p, 0x50) - U(p, 0x32);
        U(a, 0x32) = U(p, 0x32) + ((h * func_80083E80(t)) >> 12) - 0x60;
        if (func_8007778C(a) != 0) {
            func_800517F8(a);
        }
        break;
    case 2:
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

u8 *func_80139838(s32 a, u8 b) {
    u8 *p = func_8007A980(1, 4, 0);

    if (p == NULL) {
        return NULL;
    }
    M2C_FIELD(p, void **, 0x1C) = f_HandleCurvedSupportContactActor;
    M2C_FIELD(p, s32 *, 0x10) = a;
    p[0x2] = 13;
    p[0x3] = b;
    return p;
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_InitializeDryingRackControllerState);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80139A70);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_DeployDryingRackSegments);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_RetractDryingRackSegments);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8013A008);

typedef struct { s16 x, y; } S16Pair;
extern S16Pair D_8014AA58[];
/* func_8013A784, inlined */
static inline void inl_8013A784(u8 *a) {
    s32 lim;
    s32 y;

    if (a[3] == 0) {
        lim = M2C_FIELD(a, s16 *, 0x68);
        y = lim << 16;
    } else {
        lim = M2C_FIELD(a, s16 *, 0x62);
        y = lim << 16;
    }
    do {
        M2C_FIELD(a, s32 *, 0x30) += M2C_FIELD(a, s16 *, 0x50) << 8;
        func_800517F8(a);
        f_DeployDryingRackSegments(a);
    } while (M2C_FIELD(a, s16 *, 0x32) < lim);
    M2C_FIELD(a, s32 *, 0x30) = y;
}
void f_SpawnStarShapedCogPickup(u8 *a) {
    s32 i;
    u8 *e;

    M2C_FIELD(a, s16 *, 0x60) = -0x92E;
    M2C_FIELD(a, s16 *, 0x62) = -0x550;
    M2C_FIELD(a, s16 *, 0x64) = -0x46A;
    M2C_FIELD(a, s16 *, 0x66) = 0x1E0;
    M2C_FIELD(a, s16 *, 0x68) = -0x788;
    M2C_FIELD(a, s16 *, 0x50) = 0x980;
    M2C_FIELD(a, s32 *, 0x2C) = 0x24C30000;
    M2C_FIELD(a, s32 *, 0x34) = 0x14F10000;
    a[0x5E] = 0;
    M2C_FIELD(a, s16 *, 0x54) = 0;
    M2C_FIELD(a, s16 *, 0x56) = 0;
    M2C_FIELD(a, s16 *, 0x58) = 0;
    M2C_FIELD(a, s32 *, 0x30) = M2C_FIELD(a, s16 *, 0x60) << 16;
    for (i = 0; i < a[8]; i++) {
        M2C_FIELD(M2C_FIELD(a, u8 **, 0xC0 + i * 4), s16 *, 6) = i - 1;
        M2C_FIELD(M2C_FIELD(a, u8 **, 0xC0 + i * 4), s16 *, 0) = 0;
        M2C_FIELD(M2C_FIELD(a, u8 **, 0xC0 + i * 4), s16 *, 2) = D_8014AA58[i].x;
        M2C_FIELD(M2C_FIELD(a, u8 **, 0xC0 + i * 4), s16 *, 4) = D_8014AA58[i].y;
        M2C_FIELD(M2C_FIELD(a, u8 **, 0xC0 + i * 4), s32 *, 8) = 0;
        M2C_FIELD(M2C_FIELD(a, u8 **, 0xC0 + i * 4), s32 *, 0xC) = 0;
        M2C_FIELD(M2C_FIELD(a, u8 **, 0xC0 + i * 4), s16 *, 0x14) = -1;
        M2C_FIELD(M2C_FIELD(a, u8 **, 0xC0 + i * 4), s16 *, 0x10) = -2;
        M2C_FIELD(M2C_FIELD(a, u8 **, 0xC0 + i * 4), s16 *, 0x16) = 0;
        M2C_FIELD(M2C_FIELD(a, u8 **, 0xC0 + i * 4), u8 *, 0x3E) = i;
        M2C_FIELD(M2C_FIELD(a, u8 **, 0xC0 + i * 4), u8 *, 0x3F) = 0;
    }
    inl_8013A784(a);
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_HandleDryingRackController);

void f_HandleDryingRackController();
u8 *func_8013A730(s32 a) {
    u8 *p = func_8007A980(3, 4, 0);

    if (p == NULL) {
        return NULL;
    }
    M2C_FIELD(p, void **, 0x1C) = f_HandleDryingRackController;
    M2C_FIELD(p, s32 *, 0x10) = a;
    p[0x2] = 16;
    return p;
}

void func_8013A784(u8 *a) {
    s32 lim;
    s32 y;

    if (a[3] == 0) {
        lim = M2C_FIELD(a, s16 *, 0x68);
        y = lim << 16;
    } else {
        lim = M2C_FIELD(a, s16 *, 0x62);
        y = lim << 16;
    }
    do {
        M2C_FIELD(a, s32 *, 0x30) += M2C_FIELD(a, s16 *, 0x50) << 8;
        func_800517F8(a);
        f_DeployDryingRackSegments(a);
    } while (M2C_FIELD(a, s16 *, 0x32) < lim);
    M2C_FIELD(a, s32 *, 0x30) = y;
}

s32 func_8013A818(AreaPartsOwner *a) {
    s32 i;
    u8 *g;

    if (D_800ED098 < 0xD) {
        return 1;
    }
    a->pad[8] = 0xD;
    a->pad[9] = 0xD;
    a->pad[0xB] = 0;
    a->pad[0xD] = 0;
    for (i = 0; i < a->pad[8]; i++) {
        a->parts[i] = func_8007AAE8();
        func_80051B04(a->parts[i], 0xC, i + 0x26);
    }
    g = (u8 *)&D_800BF870;
    a->pad[3] = 0;
    if (g[0x268] == 0 && g[0x49] != 0xFF) {
        func_80118974((s32)a->parts[4]);
    }
    f_SpawnStarShapedCogPickup(a);
    f_InitializeDryingRackControllerState(a);
    return 0;
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8013A900);

u8 *func_8013AC34(s32 a, u8 b) {
    u8 *p = func_8007A980(2, 4, 0);

    if (p == NULL) {
        return NULL;
    }
    M2C_FIELD(p, void **, 0x1C) = func_8013A900;
    M2C_FIELD(p, s32 *, 0x10) = a;
    p[0x2] = 17;
    p[0x3] = b;
    return p;
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8013AC98);

void func_8013ADBC(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 4);
    switch (temp_v1) {                              /* irregular */
    case 0:
        M2C_FIELD(arg0, s16 *, 0x80) = 0x50;
        M2C_FIELD(arg0, s16 *, 0x82) = 0xA0;
        M2C_FIELD(arg0, s16 *, 0x84) = 0xC8;
        M2C_FIELD(arg0, s16 *, 0x86) = 0x190;
        M2C_FIELD(arg0, u8 *, 4) = 1U;
        M2C_FIELD(arg0, s8 *, 0) = 1;
        M2C_FIELD(arg0, s8 *, 0xB) = 0;
        M2C_FIELD(arg0, s8 *, 0x2B) = 0;
        M2C_FIELD(arg0, s8 *, 0x29) = 0;
        M2C_FIELD(arg0, u8 *, 0x5E) = 0U;
        M2C_FIELD(arg0, s16 *, 0x40) = 0x1E;
        return;
    case 1:
        if (func_8007778C(arg0) != 0) {
            func_8013AC98(arg0);
        }
        M2C_FIELD(arg0, s8 *, 0x29) = 0;
        M2C_FIELD(arg0, s8 *, 0x2B) = 0;
        return;
    case 2:
        if (M2C_FIELD(arg0, u8 *, 5) == 0) {
            M2C_FIELD(arg0, u8 *, 4) = 1U;
            M2C_FIELD(arg0, s8 *, 0) = 1;
            M2C_FIELD(arg0, s8 *, 0x29) = 1;
            M2C_FIELD(arg0, u8 *, 5) = (u8) M2C_FIELD(arg0, u8 *, 0x5E);
        }
        func_8013AC98(arg0);
        return;
    case 3:
        func_8007A624(arg0);
        return;
    }
}

void func_8013AEC0(void *arg0) {
    M2C_FIELD(arg0, s16 *, 0x80) = 0x50;
    M2C_FIELD(arg0, s16 *, 0x82) = 0xA0;
    M2C_FIELD(arg0, s16 *, 0x84) = 0xC8;
    M2C_FIELD(arg0, s16 *, 0x86) = 0x190;
    M2C_FIELD(arg0, s16 *, 0x40) = 0x1E;
}

void func_8013AEEC(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 5) == 0) {
        M2C_FIELD(arg0, s8 *, 4) = 1;
        M2C_FIELD(arg0, s8 *, 0) = 1;
        M2C_FIELD(arg0, s8 *, 0x29) = 1;
        M2C_FIELD(arg0, u8 *, 5) = (u8) M2C_FIELD(arg0, u8 *, 0x5E);
    }
}

typedef struct { s16 unk0; s16 x, y, z; } PartPose;
extern PartPose D_8014AABC[3];
extern PartPose D_8014AAD4[3];
typedef struct { u8 pad[0x5E]; u8 pose; u8 pad2[0xC0 - 0x5F]; s16 *parts[3]; } PosedActor;
void func_8013AF18(PosedActor *a, s32 b, s32 c) {
    s32 i;

    for (i = 0; i < 3; i++) {
        if (b == 0) {
            func_80051B04(a->parts[i], c, i);
            a->parts[i][0] = D_8014AABC[i].x;
            a->parts[i][1] = D_8014AABC[i].y;
            a->parts[i][2] = D_8014AABC[i].z;
        } else {
            func_80051B04(a->parts[i], c, i + 3);
            a->parts[i][0] = D_8014AAD4[i].x;
            a->parts[i][1] = D_8014AAD4[i].y;
            a->parts[i][2] = D_8014AAD4[i].z;
        }
    }
    a->pose = b;
}

void D_8004C930();
void f_UpdateMagicFlowerWateringSequence(u8 *a, s32 b) {
    u16 v;
    u8 *p;

    switch (a[5]) {
    case 0:
        if (a[0x29] == 1) {
            a[5]++;
            func_8013AF18(a, 0, b);
            func_80077C40(a, D_8001B7B0, 0);
            D_800BF870.pad1[0x1A2] |= 1 << a[3];
            func_8004ED94(0x5B, 0x41);
        }
        break;
    case 1:
        if (a[0x29] == 2) {
            F16(a, 0x50) = 0;
            a[5]++;
            func_8003116C(8, a + 0x2C, -0x20);
        }
        break;
    case 2:
        v = (F16(a, 0x50) + 0x100) & 0xFFF;
        F16(a, 0x50) = v;
        if (v == 0) {
            F16(a, 0xBA) = 0x1000;
            a[5]++;
            break;
        }
        if (v == 0xC00) {
            p = func_80072DDC(a, 0, 5, 4);
            if (p != NULL) {
                M2C_FIELD(p, void **, 0x1C) = D_8004C930;
                F16(p, 0x2E) = F16(a, 0x2E);
                F16(p, 0x32) = F16(a, 0x32) - 0x78;
                F16(p, 0x36) = F16(a, 0x36);
                p[3] = 0xC;
            }
            M2C_FIELD(a, u8 **, 0x10) = p;
        }
        F16(a, 0xBA) += (func_80083E80(F16(a, 0x50)) << 8) >> 12;
        break;
    case 3:
        if (M2C_FIELD(a, u8 **, 0x10)[4] == 3) {
            D_1F800137 = 0;
            a[5]++;
        }
        break;
    case 4:
        if (a[0x29] == 1) {
            F16(a, 0x52) = 0;
            F16(a, 0x44) = 0x200;
            a[5]++;
        }
        break;
    case 5:
        F16(a, 0x52) = (F16(a, 0x52) + 0x200) & 0xFFF;
        F16(a, 0x58) = (func_80083E80(F16(a, 0x52)) * F16(a, 0x44)) >> 12;
        if (F16(a, 0x52) == 0) {
            a[5]++;
            F16(a, 0x44) -= 0x80;
            func_8003116C(8, a + 0x2C, -0x20);
        }
        break;
    case 6:
        F16(a, 0x52) = (F16(a, 0x52) + 0x200) & 0xFFF;
        F16(a, 0x58) = (func_80083E80(F16(a, 0x52)) * F16(a, 0x44)) >> 12;
        if (F16(a, 0x52) == 0) {
            a[5]++;
        }
        break;
    case 7:
        if (a[0x29] == 2) {
            D_1F800137 = 0;
            a[5] = 4;
        }
        break;
    }
}

void f_HandleMagicFlowerActor(u8 *a)
{
    s32 s = a[4];
    u8 *g;

    switch (s) {
    case 0:
        g = D_800ECF58_742e;
        if (func_800519E0(a, 3, *(s32 *)(g + 0x7C), D_8014AABC_4433) == 0) {
            *(s32 *)(a + 0x3C) = *(s32 *)(g + 0x80);
            {
                u8 *st = (u8 *)&D_800BF870;
                if (st[3] != 0) {
                    a[4] = 3;
                    break;
                }
                if ((st[0x1A3] >> a[3]) & 1) {
                    a[0x5E] = 0;
                    func_80077C40(a, D_8001B7B0, 0);
                } else {
                    func_8013AF18(a, 1, 0x1F);
                    func_80077C40(a, D_8001B7B0, 1);
                }
            }
            a[0] = 1;
            *(s16 *)(a + 0x80) = 0x190;
            *(s16 *)(a + 0x82) = 0x320;
            *(s16 *)(a + 0x84) = 0xB4;
            *(s16 *)(a + 0x86) = 0xB4;
            a[0x29] = 0;
            a[0x2B] = 0;
            a[4]++;
            if (a[0x5E] == 0) {
                a[5] = 4;
            }
        }
        break;
    case 1:
        if (func_8007778C(a) != 0) {
            func_80076D68(a);
            switch (a[6]) {
            case 2:
                a[0] = s;
                a[6] = 0;
                D_800BF809 = 0;
            case 0:
                if (a[0x2B] == 3) {
                    *(s16 *)(a + 0x40) = 0x1E;
                    a[6]++;
                    if (a[0x5E] == 0) {
                        func_8004ED94(0x62, 0x41);
                    } else {
                        func_8004ED94(0x61, 0x41);
                    }
                    D_800BF809 = 1;
                }
                break;
            case 1:
                if (--*(s16 *)(a + 0x40) == 0) {
                    a[0] = 2;
                    a[6]++;
                }
                break;
            }
            f_UpdateMagicFlowerWateringSequence(a, 0x1F);
            func_800518FC(a);
        }
        a[0x29] = 0;
        a[0x2B] = 0;
        break;
    case 2:
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

extern s16 D_1F8001A2_3da0;
typedef struct {
    u8 b[0x56];
    s16 h56;
    u8 pad58[8];
    s16 h60;
    s16 h62;
    u8 pad64[0x5C];
    u8 *parts[3];
} DoorActor;
s32 f_InitializeEvilPigDoorActor(DoorActor *a, s16 *d) {
    s32 i;
    s32 n;
    s16 x, y;

    a->b[8] = 3;
    if (D_800ED098 < 3) {
        return 1;
    }
    n = 3;
    a->b[9] = n;
    a->b[0xD] = 4;
    M2C_FIELD(a->b, s16 *, 0x80) = 0x80;
    M2C_FIELD(a->b, s16 *, 0x82) = 0x100;
    M2C_FIELD(a->b, s16 *, 0x84) = 0xDC;
    M2C_FIELD(a->b, s16 *, 0x86) = 0x1C2;
    a->b[0xB] = 0;
    M2C_FIELD(a->b, s16 *, 0xB8) = 0x1000;
    M2C_FIELD(a->b, s16 *, 0xBA) = 0x1000;
    M2C_FIELD(a->b, s16 *, 0xBC) = 0x1000;
    for (i = 0; i < a->b[8]; i++) {
        a->parts[i] = func_8007AAE8();
        M2C_FIELD(a->parts[i], s16 *, 6) = *d++;
        M2C_FIELD(a->parts[i], s16 *, 0) = *d++;
        M2C_FIELD(a->parts[i], s16 *, 2) = *d++;
        M2C_FIELD(a->parts[i], s16 *, 4) = *d++;
        M2C_FIELD(a->parts[i], s16 *, 8) = 0;
        M2C_FIELD(a->parts[i], s16 *, 0xA) = 0;
        M2C_FIELD(a->parts[i], s16 *, 0xC) = 0;
        M2C_FIELD(a->parts[i], s16 *, 0x38) = 0x1000;
        M2C_FIELD(a->parts[i], s16 *, 0x3A) = 0x1000;
        M2C_FIELD(a->parts[i], s16 *, 0x3C) = 0x1000;
        func_80051B04(a->parts[i], 0xC, *d++);
    }
    a->parts[0][0x3F] = 0x20;
    a->parts[1][0x3F] = 0xF0;
    a->parts[2][0x3F] = 0xF0;
    a->b[0x29] = 0;
    a->b[0x2B] = 0;
    func_8004766C(a->b);
    func_80048750(a->b);
    x = D_1F8001A0;
    y = D_1F8001A2_3da0;
    a->h60 = x;
    a->h62 = y;
    a->h56 = x;
    M2C_FIELD(a->parts[0], s16 *, 0xA) = M2C_FIELD(a->b, s16 *, 0x7C);
    return 0;
}

void f_InitializeEvilPigDoorFromTravelState(u8 *a, s32 b) {
    s32 i;
    s32 found;

    for (i = 0; i < D_800BF870.pad1[0x12]; i++) {
        if ((D_800BF870.pad1[0x13 + i] & 0x7F) == M2C_FIELD(a, s16 *, 0x7E)) {
            found = 1;
            goto done;
        }
    }
    found = 0;
done:
    if (found == 0) {
        goto dead;
    }
    if ((D_800BF870.pad1[0x1A8] >> a[3]) & 1) {
        a[4] = 3;
        return;
    }
    if (f_InitializeEvilPigDoorActor(a, b) != 0) {
    dead:
        a[4] = 3;
        return;
    }
    if (D_800BF870.pad1[0] == M2C_FIELD(a, s16 *, 0x7A)) {
        M2C_FIELD(M2C_FIELD(a, u8 **, 0xC4), s16 *, 0xA) = 0x800;
        M2C_FIELD(M2C_FIELD(a, u8 **, 0xC8), s16 *, 0xA) = 0x800;
        a[4] = 1;
        a[5] = 0;
        a[0x5E] = 2;
    } else if ((D_800BF870.pad1[0x1A6] >> a[3]) & 1) {
        M2C_FIELD(M2C_FIELD(a, u8 **, 0xC4), s16 *, 0xA) = 0x800;
        M2C_FIELD(M2C_FIELD(a, u8 **, 0xC8), s16 *, 0xA) = 0x800;
        a[0] = 1;
        a[4] = 1;
        a[5] = 0;
        a[0x5E] = 1;
    } else {
        a[5]++;
    }
}

extern u8 D_800BF841;
extern u8 D_800E806E;
extern u16 D_1F8000D6;
void f_OpenEvilPigDoor(u8 *a) {
    u8 *t;

    switch (a[5]) {
    case 0:
        D_1F800137 = 2;
        D_800BF841 = 1;
        func_8006E1C0(8);
        func_8006CBA8(a + 0x2C);
        D_1F8000D6 = FU16(a, 0x32);
        a[5]++;
        break;
    case 1:
        if ((D_800E806E & 3) == 3) {
            t = D_800E7E80;
            a[5]++;
            a[0x46] = func_80077768((s16)func_80085690(-(s16)(FU16(a, 0x36) - FU16(t, 0x36)), (s16)(FU16(a, 0x2E) - FU16(t, 0x2E))), F16(a, 0x60), 0);
            func_80074590(0x17, -0x12, 0x1E);
        }
        break;
    case 2:
        if (a[0x46] == 0) {
            F16(M2C_FIELD(a, u8 **, 0xC4), 0xA) -= 0x40;
            F16(M2C_FIELD(a, u8 **, 0xC8), 0xA) += 0x40;
            if (F16(M2C_FIELD(a, u8 **, 0xC4), 0xA) < -0x7FF) {
                a[5]++;
            }
        } else {
            F16(M2C_FIELD(a, u8 **, 0xC4), 0xA) += 0x40;
            F16(M2C_FIELD(a, u8 **, 0xC8), 0xA) -= 0x40;
            if (F16(M2C_FIELD(a, u8 **, 0xC4), 0xA) >= 0x800) {
                a[5]++;
            }
        }
        break;
    case 3:
        F16(a, 0x40) = 30;
        a[5]++;
        break;
    case 4:
        if (--F16(a, 0x40) == 0) {
            D_1F800137 = 0;
            D_800BF841 = 0;
            func_8006E1E4();
            D_800BF870.pad1[0x1A6] |= 1 << a[3];
            a[0x5E] = 1;
            a[0] = 1;
            a[5] = 0;
        }
        break;
    }
}

void func_8013BAB0(u8 *a) {
    u8 *t = D_800E7E80;
    u8 v;

    switch (a[5]) {
    case 0:
        if (a[0x29] != 0) {
            a[5] = 1;
            v = func_80077768((s16)func_80085690(-(s16)(FU16(a, 0x36) - FU16(t, 0x36)), (s16)(FU16(a, 0x2E) - FU16(t, 0x2E))), F16(a, 0x60), 0);
            a[0x46] = v;
            if (v == 0) {
                F16(a, 0x44) = 0x800;
            } else {
                F16(a, 0x44) = -0x800;
            }
        }
        break;
    case 1:
        if (F16(t, 0x32) > F16(a, 0x32)) {
            F16(t, 0x32) = FU16(t, 0x32) - 20;
            if (F16(t, 0x32) < F16(a, 0x32)) {
                F16(t, 0x32) = FU16(a, 0x32);
            }
        } else if (F16(t, 0x32) < F16(a, 0x32)) {
            F16(t, 0x32) = FU16(t, 0x32) + 20;
            if (F16(t, 0x32) > F16(a, 0x32)) {
                F16(t, 0x32) = FU16(a, 0x32);
            }
        }
        M2C_FIELD(t, s32 *, 0x2C) += F16(a, 0x44) * F16(t, 0x48);
        M2C_FIELD(t, s32 *, 0x34) += F16(a, 0x44) * F16(t, 0x4C);
        func_8004766C(t);
        func_80048750(t);
        F16(t, 0xB8) -= 0x80;
        F16(t, 0xBA) -= 0x80;
        F16(t, 0xBC) -= 0x80;
        if (FU16(t, 0xB8) < 0x101) {
            a[5]++;
        }
        break;
    case 2:
        a[5] = 3;
        D_1F800236 = 7;
        D_800BF808_1760[0x31] = 1;
        F16(D_800BF808_1760, 0x32) = a[0xBF] << 4;
        break;
    }
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8013BCC8);

extern ClutCycle D_8014ABDC[];
extern s8 D_8014C77C[];
void func_8013C0BC(s32 arg0) {
    ClutRect r;
    s32 i;
    ClutCycle *e;
    u8 *data;

    if (arg0 == 0) {
        for (i = 0; i < 1; i++) {
            D_8014C77C[i] = 0;
        }
        return;
    }
    e = D_8014ABDC;
    for (i = 0; i < 1; i++, e++) {
        if (--D_8014C77C[i] <= 0) {
            if (e->ptr[0] == 0xFF) {
                e->ptr -= e->ptr[1];
            }
            data = e->clut + e->ptr[0] * 32;
            D_8014C77C[i] = e->ptr[1];
            r.x = e->x;
            r.y = e->y;
            r.w = 16;
            r.h = 1;
            func_80081218(&r, data);
            e->ptr += 2;
        }
    }
}

void func_8013C1DC(u8 *a)
{
    switch (a[4]) {
    case 0:
        switch (a[5]) {
        case 0:
            func_8013C0BC(0);
            a[0xBF] = 0xE0;
            *(s16 *)(a + 0x7E) = 0x1B;
            *(s16 *)(a + 0x7C) = 0x400;
            *(s16 *)(a + 0x7A) = 0xB;
            *(s16 *)(a + 0x78) = 0x30;
            a[5]++;
        case 1:
            f_InitializeEvilPigDoorFromTravelState(a, D_8014ABE8);
            break;
        case 2:
            if (func_80078240(D_1F800160_71b4 - *(s16 *)(a + 0x2E), D_1F800162 - *(s16 *)(a + 0x32), D_1F800164_d75f - *(s16 *)(a + 0x36)) <= 1000
                && D_1F80027A == 0 && D_800E7E80_d97c != 6 && D_800BF80D == 0) {
                a[4] = 1;
                a[5] = 0;
                a[0x5E] = 0;
            }
            break;
        }
        break;
    case 1:
        if (func_8007778C(a) != 0) {
            func_8013C0BC(1);
            func_80051844(a);
        }
        switch (a[0x5E]) {
        case 0:
            f_OpenEvilPigDoor(a);
            a[0x29] = 0;
            break;
        case 1:
            func_8013BAB0(a);
            a[0x29] = 0;
            break;
        case 2:
            func_8013BCC8(a, D_8014AC08);
            a[0x29] = 0;
            break;
        default:
            a[0x29] = 0;
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

extern u8 D_8014AC18[];
extern u8 D_8014AF20[];
void f_UpdateKainenHouseProgressEffectActor(u8 *a)
{
    u8 *p;
    s32 t;
    u8 k;
    s32 c;

    switch (a[4]) {
    case 0:
        if (D_800BF9E0 < 0x1C) {
            M2C_FIELD(a, u16 *, 4) = 1;
        } else {
            a[4] = 3;
            break;
        }
    case 1:
        if (D_800E7FEB == 1) {
            break;
        }
        p = M2C_FIELD(a, u8 **, 0x38);
        M2C_FIELD(a, u8 **, 0x34) = p;
        if (p == NULL) {
            M2C_FIELD(a, u8 **, 0x34) = D_8014AC18;
            k = a[3];
            c = 0x80;
if (k == c) {
                M2C_FIELD(a, u8 **, 0x34) = NULL;
                a[4] = 3;
                break;
            }
            if (k < 2) {
                t = D_800BF9E0 < 6;
            } else {
                t = D_800BF9E0 < 0x10;
            }
            if (t == 0) {
                M2C_FIELD(a, u8 **, 0x34) = D_8014AF20;
                a[3] = c;
            }
        }
        if (D_800E7EAA < 0xC) {
            if (func_8002B278(a) == 0) {
                func_80031780(a);
            }
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

typedef struct { s16 x, y, z, w; } Particle8;
void f_UpdateKainenHouseFallingParticleActor(u8 *a)
{
    s32 n;
    s32 i;
    Particle8 *p;
    u8 *g;

    switch (a[4]) {
    case 0:
        if (D_800BF9E0 >= 0x1C) {
            a[4] = 3;
            break;
        }
        if (D_800BF9E0 < 6) {
            M2C_FIELD(a, s16 *, 0x4E) = 7;
            n = 7;
        } else {
            M2C_FIELD(a, s16 *, 0x4E) = 1;
            n = 1;
        }
        p = (Particle8 *)(a + 0x50);
        while (n > 0) {
            p->x = M2C_FIELD(a, s16 *, 0x2C) + func_80032A44(0, 0x80);
            p->y = M2C_FIELD(a, s16 *, 0x2E) + func_80032A44(-0x80, 0);
            n--;

            p->z = M2C_FIELD(a, s16 *, 0x30) + func_80032A44(0, 0x20);

            p->w = func_80032A44(0xE0, 0x120);
            p++;

        }
        a[4] = 1;
    case 1:
        g = D_800E7E80;
        if (g[0x16B] == 1) {
            break;
        }
        if (g[0x2A] >= 0xC || (M2C_FIELD(a, s32 *, 0x34) = M2C_FIELD(a, s32 *, 0x38)) == 0) {
            a[4] = 3;
            break;
        }
        p = (Particle8 *)(a + 0x50);
        if (D_800BF9E0 < 6) {
            for (i = 0; i < M2C_FIELD(a, s16 *, 0x4E); i++) {
                p->x += -1 + ((func_8009A450() >> 7) & 3);
                p->y = (s16)(p->y - 0xE) - ((func_8009A450() >> 8) & 0xF);
                p->z += -2 + ((func_8009A450() >> 7) & 3);
                p++;
            }
        } else {
            for (i = 0; i < M2C_FIELD(a, s16 *, 0x4E); i++) {
                p->x += -3 + ((func_8009A450() >> 7) & 7);
                p->y = (s16)(p->y - 0xE) - ((func_8009A450() >> 8) & 0xF);
                p->z += -4 + ((func_8009A450() >> 7) & 7);
                p++;
            }
        }
        if (func_8002B278(a) == 0) {
            func_80031780(a);
        }
        break;
    case 2:
    case 3:
        func_8007A624(a);
        break;
    }
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8013C7F0);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8013C9C0);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8013CDD4);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8013D454);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8013D588);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8013D828);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8013D9D4);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8013DBE4);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8013DD34);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8013E08C);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8013E424);

#define W(p, o) M2C_FIELD(p, u32 *, o)
typedef struct {
    u8 b[6][4];
} FlickerTbl;
extern FlickerTbl D_8010A070;
void func_8013E620(u8 *a) {
    FlickerTbl t = D_8010A070;

    switch (a[4]) {
    case 0:
        a[4] = 1;
        W(a, 0x60) = 0x100;
        W(a, 0x64) = 0x200;
        W(a, 0x68) = 0x200;
        W(a, 0x6C) = 0x100;
        M2C_FIELD(a, s16 *, 0x32) = -200;
    case 1:
    case 2:
        W(a, 0x60) -= W(a, 0x60) >> 2;
        W(a, 0x64) -= W(a, 0x64) >> 2;
        W(a, 0x68) -= W(a, 0x68) >> 2;
        W(a, 0x6C) -= W(a, 0x6C) >> 2;
        if (W(a, 0x6C) < 9) {
            a[4] = 3;
        }
        if (++a[7] >= 6) {
            a[7] = 0;
        }
        W(a, 0x50) = (W(a, 0x60) * t.b[a[7]][0]) >> 4;
        W(a, 0x54) = (W(a, 0x64) * t.b[a[7]][1]) >> 4;
        W(a, 0x58) = (W(a, 0x68) * t.b[a[7]][2]) >> 4;
        W(a, 0x5C) = (W(a, 0x6C) * t.b[a[7]][3]) >> 4;
        a[1] = 1;
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

extern u8 D_800A0B38[];
extern u8 D_8014BD14[];
extern u8 D_8014BD48[];
void func_8013E840(u8 *a)
{
    s16 sp[6];
    s8 *s = (s8 *)(a + 0x50);
    u8 *e;

    switch (a[4]) {
    case 0:
        *(u8 **)(a + 0x50) = D_800A0B38;
        *(s32 *)(a + 0x48) = 0;
        *(s16 *)(a + 0x4C) = 0;
        s[4] = 0;
        a[0x29] = 0;
        *(s16 *)(a + 4) = 1;
    case 1:
        *(u8 **)(a + 0x3C) = D_8014BD14 + s[4] * 4;
        a[0x29] = D_8014BD48[s[4]];
        if (++s[4] >= 0xC) {
            a[4] = 2;
        } else {
            func_8002B278(a);
        }
        switch (a[5]) {
        case 2: break;
        case 0:
            if (++s[4] >= 6) {
                a[5] = 1;
            }
            break;
        case 1:
            sp[1] = *(s16 *)(a + 0x2C);
            sp[3] = *(s16 *)(a + 0x2E) - 0x8C;
            sp[5] = *(s16 *)(a + 0x30);
            e = func_8003116C(8, sp, 0);
            if (e != NULL) {
                e[0x28] = a[0x28];
            }
            a[5]++;
            break;
        }
        break;
    case 2:
    case 3:
        func_8007A624(a);
        break;
    }
}

typedef struct {
    s16 x, y, z, pad;
} SVec4;
void func_8013E9D8(u8 *a) {
    SVec4 v;
    SVec4 w;

    v.x = M2C_FIELD(M2C_FIELD(a, s16 **, 0x14), s16 *, 0);
    v.y = M2C_FIELD(M2C_FIELD(a, s16 **, 0x14), s16 *, 2);
    v.z = M2C_FIELD(M2C_FIELD(a, s16 **, 0x14), s16 *, 4);
    w.x = M2C_FIELD(a, s16 *, 0x4E);
    w.y = M2C_FIELD(a, s16 *, 0x50);
    w.z = M2C_FIELD(a, s16 *, 0x52);
    func_8013DD34(&v, &w);
    func_8003CCA4(a);
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8013EA64);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8013EBA0);

extern u8 D_8014BCC0[];
extern u8 D_8014BCAC[];
void func_8013EC48(u8 *a) {
    u8 *p;

    switch (a[4]) {
    case 0:
        M2C_FIELD(a, u8 **, 0x40) = D_8014BCC0;
        M2C_FIELD(a, u8 **, 0x50) = D_8014BCAC;
        M2C_FIELD(a, s32 *, 0x48) = 0;
        M2C_FIELD(a, s16 *, 0x4C) = 0;
        a[4] = 1;
    case 1:
        p = M2C_FIELD(a, u8 **, 0x40);
        M2C_FIELD(a, u8 **, 0x3C) = p;
        if (p == NULL) {
            a[4] = 2;
            break;
        }
        if (func_8002B278(a) == 0) {
            func_80031744(a);
        }
        break;
    case 2:
    case 3:
        func_8007A624(a);
        break;
    }
}

extern s8 D_1F800090[];
void func_8013ED08(void *arg0) {
    *((s32 *)D_1F800090) = 0;
    func_800318A0(arg0 + 0x2C, arg0 + 0x54, arg0 + 0x48);
    func_80027768(M2C_FIELD(arg0, s32 *, 0x50), 0, M2C_FIELD(arg0, s16 *, 0x32), M2C_FIELD(arg0, u8 *, 7));
}

void func_8013ED54(u8 *a) {
    SVec4 v;
    SVec4 w;

    v.x = M2C_FIELD(M2C_FIELD(a, s16 **, 0x14), s16 *, 0);
    v.y = M2C_FIELD(M2C_FIELD(a, s16 **, 0x14), s16 *, 2);
    v.z = M2C_FIELD(M2C_FIELD(a, s16 **, 0x14), s16 *, 4);
    w.x = M2C_FIELD(a, s16 *, 0x4E);
    w.y = M2C_FIELD(a, s16 *, 0x50);
    w.z = M2C_FIELD(a, s16 *, 0x52);
    func_8013DD34(&v, &w);
}

typedef struct { s16 x, y, z, pad; } RingVec;
extern RingVec D_8014C780[];
void func_8013EDD0(void) {
    s32 i;
    s32 ang;
    RingVec *p;

    p = D_8014C780;
    for (i = 0; i < 15; i++, p++) {
        ang = (i << 12) / 15;
        p->x = func_80083F50(ang) >> 4;
        p->y = 0;
        p->z = func_80083E80(ang) >> 4;
    }
    p->x = D_8014C780[0].x;
    p->y = D_8014C780[0].y;
    p->z = D_8014C780[0].z;
}

typedef struct { s16 pos; s16 vel; } RiseMotion;
void func_8013EEA0(u8 *a) {
    RiseMotion *m = (RiseMotion *)(a + 0x50);

    switch (a[4]) {
    case 0:
        m->pos = 20;
        a[4] = 1;
        m->vel = 10;
    case 1:
        func_8002B278(a);
        m->pos += m->vel;
        if (m->pos > 0xC8) {
            a[4] = 2;
        }
        break;
    case 2:
    case 3:
        func_8007A624(a);
        break;
    }
}

extern s32 D_1F800090_3460;
void func_8013EF58(u8 *a)
{
    u8 buf[0x30];
    void *m;
    s32 y;

    func_800318A0(a + 0x2C, a + 0x50, a + 0x48);
    m = *(void **)(a + 0x3C);
    y = *(s16 *)(a + 0x32);
    D_1F800090_3460 = *(s32 *)(a + 0x54);
    func_80027768(m, 0, y, a[0x29]);
}

extern s32 D_800A3F90;
extern s32 D_800A3F94;
s32 f_GetA00GridCellValue(s32 x, s32 y);
void f_CollectA00GridCellsInsideTriangle(u8 *a, s32 *p0, s32 *p1, s32 *p2);
void f_CollectVisibleA00GridCellsForCamera(u8 *a) {
    s32 v[6];
    s32 ox = 0;
    s32 oz = ox;
    u32 ang = D_1F8000D0[0x11] & 0xFFF;
    s16 gx, gz;
    s32 k, s, dx, dz;
    u16 g;

    if (D_1F800137 != 0) {
        gx = D_1F8000D0[7] / 640;
        gz = D_1F8000D0[0xB] / 640;
        D_8014C800 = f_GetA00GridCellValue(gx, gz);
    } else {
        gx = D_1F800160_71b4 / 640;
        gz = D_1F800164_d75f / 640;
        D_8014C800 = f_GetA00GridCellValue(gx, gz);
    }
    g = *(volatile u16 *)&D_8014C800 & 0xF;
    D_8014C800 = g;
    switch (g) {
    case 1:
    case 2:
        if (ang - 0x200 > 0xC00) D_800A3F90 = 0x2F80;
        else D_800A3F90 = 0x2580;
        D_800A3F90 = 0x2580;
        D_800A3F94 = 0x155;
        break;
    case 4:
    case 8:
        D_800A3F90 = 0x2D00;
        D_800A3F94 = 0x155;
        break;
    }
    switch (D_1F800207_9c67) {
    case 1:
        D_800A3F90 = 0x3700;
        D_800A3F94 = 0x1C7;
        if (D_1F800160_71b4 >= 0x2454 && ang - 0x200 > 0xC00) D_800A3F90 = 0x3E80;
        break;
    case 4: case 5: case 6: case 7: case 8: case 9: case 10:
        if (ang - 0x801 < 0x7FF) {
            ox = -(func_80083E80(-D_1F8000D0[0x11]) * 640) >> 12;
            oz = -(func_80083F50(-D_1F8000D0[0x11]) * 640) >> 12;
            D_800A3F90 = 0x3980;
            D_800A3F94 = 0x13E;
        }
        break;
    case 17: case 18: case 19: case 20: case 21:
        D_800A3F90 = 0x3C00;
        D_800A3F94 = 0x1C7;
        break;
    default:
        D_800A3F90 = 0x3200;
        D_800A3F94 = 0x1C7;
        break;
    }
    k = (-D_1F8000D0[0x11] - D_800A3F94) & 0xFFF;
    v[0] = D_1F8000D0[1] + ox;
    v[1] = D_1F8000D0[5] + oz;
    v[2] = v[0] + ((func_80083E80(k) * D_800A3F90) >> 12);
    v[3] = v[1] + ((func_80083F50(k) * D_800A3F90) >> 12);
    k = (D_800A3F94 - D_1F8000D0[0x11]) & 0xFFF;
    v[4] = v[0] + ((func_80083E80(k) * D_800A3F90) >> 12);
    v[5] = v[1] + ((func_80083F50(k) * D_800A3F90) >> 12);
    s = __builtin_abs(func_80083E80(D_1F8000D0[0x10]));
    dx = (func_80083E80(-D_1F8000D0[0x11]) * s) >> 12;
    dz = (func_80083F50(-D_1F8000D0[0x11]) * s) >> 12;
    dx = (dx * D_800A3F90 * 5) >> 16;
    dz = (dz * D_800A3F90 * 5) >> 16;
    v[2] -= dx;
    v[3] -= dz;
    v[4] -= dx;
    v[0] -= dx;
    v[5] -= dz;
    v[1] -= dz;
    v[0] /= 640;
    v[1] /= 640;
    v[2] /= 640;
    v[3] /= 640;
    v[4] /= 640;
    v[5] /= 640;
    a[6] = 0;
    f_CollectA00GridCellsInsideTriangle(a, &v[0], &v[2], &v[4]);
}

s32 f_TestA00GridCellMask(s32 x, s32 y);
#define GH(p, o) (*(s16 *)((u8 *)(p) + (o)))
typedef struct { u8 pad[0x10]; u16 cells[1]; } A00CellList;
static inline void tri_span(u8 *a, s32 y, s32 l, s32 r) {
    s32 x;
    s16 *p;
    s32 off;

    if (y >= 0 && y < GH(a, 0xA)) {
        if (r >= GH(a, 8)) r = GH(a, 8) - 1;
        x = l;
        if (x < 0) x = 0;
        p = (s16 *)D_800ECF58[8];
        p += 2;
        off = x * GH(a, 0xA) + y;
        while (p += off, x <= r) {
            if (*p != -1 && (s16)f_TestA00GridCellMask(x, y) != 0) {
                u8 n = a[6];
                if (n < 0xFE) {
                    a[6] = n + 1;
                    ((A00CellList *)a)->cells[n] = *p;
                }
            }
            off = GH(a, 0xA);
            x++;
        }
    }
}
void f_CollectA00GridCellsInsideTriangle(u8 *a, s32 *p0, s32 *p1, s32 *p2) {
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
        for (y = y0; y < y1; y++) { tri_span(a, y, xl >> 16, xr >> 16); xl += sl1; xr += sl3; }
        for (; y <= y2; y++) { tri_span(a, y, xl >> 16, xr >> 16); xl += sl2; xr += sl3; }
    } else {
        for (y = y0; y < y1; y++) { tri_span(a, y, xl >> 16, xr >> 16); xr += sl1; xl += sl3; }
        for (; y <= y2; y++) { tri_span(a, y, xl >> 16, xr >> 16); xl += sl3; xr += sl2; }
    }
}

s32 f_TestA00GridCellMask(s32 x, s32 y) {
    return D_8014C804_6a3a[y * 52 + x] & (D_8014C800 << 4);
}

s32 f_GetA00GridCellValue(s32 x, s32 y) {
    return D_8014C804_6a3a[y * 52 + x];
}

extern s8 *D_8014C804;
void func_8013FB4C(u8 *a)
{
    s8 **t = D_800ECF58;
    u16 *p = (u16 *)t[8];
    u16 v;

    *(u16 **)(a + 0xC) = p;
    *(u16 *)(a + 8) = p[0];
    v = p[1];
    a[7] = 0;
    *(u16 *)(a + 0xA) = v;
    D_8014C804 = t[9];
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
u32 *f_DrawTownCreatureGt3Batch(u32 *f, u32 *ot, s32 n)
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
#define T2_rtpt() __asm__ volatile(".word 0x4A280030")
#define T2_rtps() __asm__ volatile(".word 0x4A180001")
#define T2_nclip() __asm__ volatile(".word 0x4B400006")
#define T2_avsz4() __asm__ volatile(".word 0x4B68002E")
#define T2_stflg(r0) __asm__ volatile("cfc2 $12, $31;" "nop;" "sw $12, 0( %0 )" : : "r"(r0) : "$12", "memory")
#define T2_stopz(r0) __asm__ volatile("swc2 $24, 0( %0 )" : : "r"(r0) : "memory")
#define T2_stotz(r0) __asm__ volatile("swc2 $7, 0( %0 )" : : "r"(r0) : "memory")
#define T2_stsxy(r0) __asm__ volatile("swc2 $14, 0( %0 )" : : "r"(r0) : "memory")
#define T2_stsxy3_gt4(r0)                                                                                              \
    __asm__ volatile("swc2 $12, 8( %0 );" "swc2 $13, 20( %0 );" "swc2 $14, 32( %0 )" : : "r"(r0) : "memory")
#define T2_stsz0(r0) __asm__ volatile("swc2 $16, 0( %0 )" : : "r"(r0) : "memory")
#define T2_stsz1(r0) __asm__ volatile("swc2 $17, 0( %0 )" : : "r"(r0) : "memory")
#define T2_stsz2(r0) __asm__ volatile("swc2 $18, 0( %0 )" : : "r"(r0) : "memory")
#define T2_stsz3(r0) __asm__ volatile("swc2 $19, 0( %0 )" : : "r"(r0) : "memory")
#define T2_rtpt() __asm__ volatile(".word 0x4A280030")
#define T2_nclip() __asm__ volatile(".word 0x4B400006")
#define T2_stflg(r0) __asm__ volatile("cfc2 $12, $31;" "nop;" "sw $12, 0( %0 )" : : "r"(r0) : "$12", "memory")
#define T2_stopz(r0) __asm__ volatile("swc2 $24, 0( %0 )" : : "r"(r0) : "memory")
#define T2_stotz(r0) __asm__ volatile("swc2 $7, 0( %0 )" : : "r"(r0) : "memory")
#define T2_stsz1(r0) __asm__ volatile("swc2 $17, 0( %0 )" : : "r"(r0) : "memory")
#define T2_stsz2(r0) __asm__ volatile("swc2 $18, 0( %0 )" : : "r"(r0) : "memory")
#define T2_stsz3(r0) __asm__ volatile("swc2 $19, 0( %0 )" : : "r"(r0) : "memory")
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
u32 *f_DrawTownCreatureGt4Batch(u32 *f, u32 *ot, s32 n)
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
void func_801401B8(PartList *a)
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
        r = f_DrawTownCreatureGt3Batch(e + 1, ot, v & 0xFF);
        v >>= 16;
        f_DrawTownCreatureGt4Batch(r, ot, v & 0xFF);
    }
}

typedef struct { u8 b[8]; } AnimEnt8;
extern AnimEnt8 D_8014BF04[];
extern u8 D_8014BF58[];
extern u8 D_8014BF54[];
extern u8 *D_800ECFB0;
extern u8 D_8014CDA8[];
void func_801402B8(u8 *a, s32 k, s32 m) {
    u8 *q = a + 0x60;
    AnimEnt8 *e;
    s32 idx;
    u8 *base;
    s32 *tbl;
    u8 *r;

    if (a[0x46] == k) {
        return;
    }
    a[0x46] = k;
    if ((m & 0xFF) == 0) {
        func_80077C40(a, D_8014CDA8, k);
    } else {
        func_80077CFC(a, D_8014CDA8, k, (u8)m);
    }
    idx = *(u16 *)(P(a, 0x38) + 2);
    e = &D_8014BF04[idx];
    H_f12c(a, 0x80) = e->b[0];
    H_f12c(a, 0x82) = e->b[1];
    H_f12c(a, 0x84) = e->b[2];
    H_f12c(a, 0x86) = e->b[3];
    H_f12c(q, 0x1C) = (s8)e->b[4];
    H_f12c(q, 0x1E) = (s8)e->b[5];
    base = D_800ECFB0;
    tbl = (s32 *)(base + 4);
    P(P(a, 0xC4), 0x40) = base + tbl[D_8014BF58[e->b[6] & 0xF]];
    P(P(a, 0xE4), 0x40) = base + tbl[D_8014BF54[e->b[7] & 0xF]];
    r = a + 0x60;
    if (e->b[7] & 0x80) {
        P(P(a, 0xFC), 0x40) = base + tbl[0x16];
    } else {
        P(P(a, 0xFC), 0x40) = base + tbl[0xF];
    }
if (D_8014BF04[idx].b[7] & 0x10) { H_f12c(r, 2) |= 8; } else { H_f12c(r, 2) &= 0xFFF7; }
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8014047C);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80140544);

#define HU(p, o) (*(u16 *)((u8 *)(p) + (o)))
extern u16 D_1F8001A0_6940;
s32 f_UpdateTownCreatureTerrainContact(u8 *a) {
    u8 *q;
    s16 res;
    s32 r;

    res = 0;
    q = a + 0x60;
    if (func_8004766C(a) == 0) {
        return 0;
    }
    if (a[0x2A] == 0xC && H_f12c(a, 0x36) < 0x58C) {
        H_f12c(a, 0x36) = 0x58C;
    }
    if ((r = func_8004954C(a, 0x50, -0x1E)) == 1) {
        res |= 2;
        if (HU(q, 2) & r) {
            a[0x5F] = 2;
        } else {
            a[0x5F] = 3;
        }
    }
    if (a[0x29] == 0) {
        r = func_80049250(a, 0, 0x50);
        if (r & 1) {
            {
                u16 t1 = D_1F8001A6;
                u16 t2 = D_1F8001A4;
                HU(q, 8) = t1;
                HU(q, 0xA) = t2;
            }
            a[0x29] = 1;
            func_80049674(a);
            HU(q, 0) = D_1F8001A0_6940;
            if (HU(q, 2) & 1) {
                H_f12c(a, 0x58) = (0x1000 - D_1F8001A2) & 0xFFF;
            } else {
                H_f12c(a, 0x58) = D_1F8001A2;
            }
        } else if (r != 0) {
            {
                u16 t1 = D_1F8001A6;
                u16 t2 = D_1F8001A4;
                HU(q, 8) = t1;
                HU(q, 0xA) = t2;
            }
        } else {
            func_80049760(a);
            HU(q, 0) = D_1F8001A0_6940;
        }
    } else {
        func_80049760(a);
        HU(q, 0) = D_1F8001A0_6940;
    }
    if (!(HU(q, 2) & 4)) {
        if (HU(q, 2) & 1) {
            H_f12c(a, 0x56) = (D_1F8001A0_6940 - 0x800) & 0xFFF;
        } else {
            H_f12c(a, 0x56) = D_1F8001A0_6940;
        }
    }
    return res;
}

/* func_80145EA4, inlined */
static inline s16 inl_80145EA4(u8 *a) {
    u8 *q = a + 0x60;
    s32 h = M2C_FIELD(a, u16 *, 0x60);
    s8 r;

    r = (u32)((h - func_800782B0(a + 0x2C, D_1F800160_71b4, D_1F800164_d75f) + 0x400) & 0xFFF) > 0x800;
    if (M2C_FIELD(q, u16 *, 2) & 1) {
        if (!r) return 1;
    } else {
        if (r) return 1;
    }
    return 0;
}
s32 f_UpdateTownCreatureFaceTomba(u8 *a) {
    switch (a[6]) {
    case 0:
        if (!(D_800E7FFE & 0x8200) && inl_80145EA4(a)) {
            H_f12c(a, 6) = 1;
        } else {
            H_f12c(a, 6) = 2;
        }
        break;
    case 1:
        if ((s16)f_UpdateTownCreatureTurnaround(a) != 0) {
            H_f12c(a, 6) = 2;
        }
        break;
    default:
        H_f12c(a, 6) = 2;
        goto end;
    }
    H_f12c(a, 0x32) += 0x10;
    f_UpdateTownCreatureTerrainContact(a);
end:
    return 0;
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_801409C0);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateTownCreatureKnockbackBounce);

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_8014103C);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateTownCreatureFleeRun);

static inline s16 inl_wall(u8 *a) {
    u8 *q;

    if (a[0x5F] == 0) return 0;
    q = a + 0x60;
    if (a[0x5F] == 3) {
        if (HU(q, 2) & 1) return 1;
        return 0;
    }
    if (!(HU(q, 2) & 1)) return 1;
    return 0;
}

s16 f_UpdateTownCreatureStraightRun(u8 *a) {
    u8 *q = a + 0x60;
    s16 res = 0;
    s32 dx, dz;

    switch (a[7]) {
    case 0:
        HU(q, 2) &= 0xFFFB;
        f_UpdateTownCreatureTerrainContact(a);
        func_801402B8(a, 0, 8);
        H_f12c(a, 0x4E) = 0xE00;
        a[7]++;
    case 1:
        if (inl_80145EA4(a)) {
            a[7]++;
        } else if (D_800E7E80_d97c & 2) {
            a[7] = 2;
            res = 1;
        }
        break;
    case 2:
        if (func_800781E0(H_f12c(a, 0x2E) - D_1F800160_71b4, H_f12c(a, 0x36) - D_1F800164_d75f) >= 0x140) {
            res = 1;
        }
        break;
    }
    dx = H_f12c(a, 0x48) * H_f12c(a, 0x4E);
    dz = H_f12c(a, 0x4C) * H_f12c(a, 0x4E);
    if (HU(a, 0x62) & 1) {
        W_d1fb(a, 0x2C) -= dx;
        W_d1fb(a, 0x34) -= dz;
    } else {
        W_d1fb(a, 0x2C) += dx;
        W_d1fb(a, 0x34) += dz;
    }
    if (inl_wall(a)) {
        res = -1;
    }
    H_f12c(a, 0x32) += 0x10;
    f_UpdateTownCreatureTerrainContact(a);
    if (res == 0 && a[0x66] == 0x81 && a[0x29] == 0 && a[4] == 1) {
        W_d1fb(a, 4) = 0x20501;
    }
    return res;
}

s32 func_80141AC4(u8 *a, s32 anim, s32 spd) {
    u8 *q = a + 0x60;
    s32 res = 0;
    s32 dx, dz;
    s32 f;

    if (a[7] == 0) {
        HU(q, 2) &= 0xFFFB;
        func_801402B8(a, (s16)anim, 8);
        H_f12c(a, 0x4E) = spd;
        a[7]++;
    }
    dx = H_f12c(a, 0x48) * H_f12c(a, 0x4E);
    dz = H_f12c(a, 0x4C) * H_f12c(a, 0x4E);
    if (HU(q, 2) & 1) {
        W_d1fb(a, 0x2C) -= dx;
        W_d1fb(a, 0x34) -= dz;
    } else {
        W_d1fb(a, 0x2C) += dx;
        W_d1fb(a, 0x34) += dz;
    }
    H_f12c(a, 0x32) += 0x10;
    f_UpdateTownCreatureTerrainContact(a);
    f = 0;
    if (a[0x66] == 0x81 && a[0x29] == 0 && a[4] == 1) {
        W_d1fb(a, 4) = 0x20501;
        f = 1;
    }
    if (f == 0) {
        if (a[7] >= 0x14) {
            res = 1;
        } else {
            a[7]++;
        }
    }
    return res;
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateTownCreatureHopAndBrake);

s32 f_UpdateTownCreatureVerticalLaunch(u8 *a) {
    u8 *q = a + 0x60;
    s32 res = 0;

    switch (a[7]) {
    case 0:
        HU(q, 2) &= 0xFFFB;
        f_UpdateTownCreatureTerrainContact(a);
        func_801402B8(a, 0xE, 0);
        H_f12c(a, 0x4E) = 0x300;
        H_f12c(a, 0x50) = -0x1400;
        a[7]++;
    case 1:
        if ((H_f12c(a, 0x50) += 0x100) >= -0x100) {
            a[7]++;
        }
        break;
    case 2:
        if ((H_f12c(a, 0x50) += 0x40) >= 0) {
            func_801402B8(a, 0x11, 8);
            a[7]++;
        }
        break;
    case 3:
        if ((H_f12c(a, 0x50) -= 0x40) < -0x9FF) {
            H_f12c(a, 0x50) = -0xA00;
            H_f12c(a, 0x40) = 0x14;
            a[7]++;
        }
        break;
    case 4:
        if (H_f12c(a, 0x40)-- <= 0) {
            res = 1;
        }
        break;
    }
    W_d1fb(a, 0x30) += H_f12c(a, 0x50) << 8;
    return res;
}

s32 f_UpdateTownCreatureLaunchLanding(u8 *a) {
    u8 *q = a + 0x60;
    s32 res = 0;
    s32 dx, dz;

    switch (a[7]) {
    case 0:
        HU(q, 2) &= 0xFFFB;
        func_801402B8(a, 0x11, 8);
        a[0x29] = 0;
        a[7]++;
    case 1:
        f_UpdateTownCreatureTerrainContact(a);
        if (a[0x29] != 0) {
            func_801402B8(a, 0xF, 0);
            H_f12c(a, 0x58) = 0;
            a[7]++;
        } else {
            dx = H_f12c(a, 0x48) * H_f12c(a, 0x4E);
            dz = H_f12c(a, 0x4C) * H_f12c(a, 0x4E);
            if (HU(a, 0x62) & 1) {
                W_d1fb(a, 0x2C) -= dx;
                W_d1fb(a, 0x34) -= dz;
            } else {
                W_d1fb(a, 0x2C) += dx;
                W_d1fb(a, 0x34) += dz;
            }
            H_f12c(a, 0x50) += 0x80;
            if (H_f12c(a, 0x58) < 0x12C) {
                H_f12c(a, 0x58) += 0x14;
            }
        }
        break;
    default:
        H_f12c(a, 0x32) += 0x10;
        f_UpdateTownCreatureTerrainContact(a);
        if (a[7] >= 0x14) {
            res = 1;
        } else {
            a[7]++;
        }
        break;
    }
    W_d1fb(a, 0x30) += H_f12c(a, 0x50) << 8;
    return res;
}

s32 f_UpdateTownCreaturePostKnockbackRecovery(u8 *a) {
    u8 *q = a + 0x60;
    s32 res = 0;
    s32 k;

    switch (a[7]) {
    case 0:
        HU(q, 2) &= 0xFFFB;
        H_f12c(a, 0x58) = 0;
        if (HU(a, 4) == 0x402) {
            a[7] = 2;
            break;
        }
        func_801402B8(a, 2, 3);
        H_f12c(a, 0x42) = 0xD2;
        a[7]++;
    case 1:
        H_f12c(a, 0x32) += 0x10;
        f_UpdateTownCreatureTerrainContact(a);
        if (--H_f12c(a, 0x42) == -1) {
            if (a[4] == 2) {
                a[7]++;
            } else {
                res = 1;
            }
        }
        break;
    case 2:
        k = 8;
        if (HU(a, 4) == 0x402) {
            k = 0x14;
        }
        if (func_8009A450() & 0x8000) { func_801402B8(a, 0xC, k); } else { func_801402B8(a, 0x1F, k); }
        H_f12c(a, 0x42) = 0x10E;
        H_f12c(a, 0x58) = 0;
        a[7]++;
    case 3:
        H_f12c(a, 0x32) += 0x10;
        f_UpdateTownCreatureTerrainContact(a);
        if (--H_f12c(a, 0x42) == -1) {
            res = 1;
        }
        break;
    }
    a[0x29] = 0;
    return res;
}

extern u8 D_8014BEB4[];
s32 f_UpdateTownCreatureRandomIdle(u8 *a) {
    u8 *q = a + 0x60;
    s32 res = 0;

    switch (a[7]) {
    case 0:
        HU(q, 2) &= 0xFFFB;
        switch (D_8014BEB4[func_8009A450() & 0xF]) {
        case 0:
            a[7] = 1;
            break;
        case 1:
            a[7] = 5;
            break;
        case 2:
            a[7] = 9;
            break;
        }
        H_f12c(a, 0x40) = 0x2D;
        func_801402B8(a, 0x15, 8);
        H_f12c(a, 0x4E) = 0;
    case 1:
    case 5:
    case 9:
        if (--H_f12c(a, 0x40) == -1) {
            if (a[7] == 1) {
                res = 1;
            } else {
                a[7]++;
            }
        }
        break;
    case 6:
    case 10:
        switch (a[7]) {
        case 6:
            func_801402B8(a, 0x14, 8);
            break;
        case 10:
            func_801402B8(a, 0x15, 8);
            break;
        }
        H_f12c(a, 0x40) = 0x2D;
        a[7] = 1;
        break;
    }
    H_f12c(a, 0x32) += 0x10;
    f_UpdateTownCreatureTerrainContact(a);
    return res;
}

extern u8 D_8014BEA4[];
/* func_8014601C, inlined */
static inline s16 inl_8014601C(u8 *a) {
    s16 d = func_800781E0(M2C_FIELD(a, s16 *, 0x2E) - D_1F800160_71b4, M2C_FIELD(a, s16 *, 0x36) - D_1F800164_d75f);

    if ((D_800E7FFE & 0x8200) || d > 0x640) {
        return -1;
    }
    if (d >= 0x44D) {
        return 0;
    }
    if (d >= 0x259) {
        return 1;
    }
    return 2;
}

s32 f_UpdateTownCreatureIdleDecision(u8 *a) {
    u8 *q = a + 0x60;
    s32 res = 0;
    s32 dx, dz;

    switch (a[7]) {
    case 0:
        HU(q, 2) &= 0xFFFB;
        a[7]++;
    case 1:
        H_f12c(a, 0x40) = D_8014BEA4[func_8009A450() & 0xF];
        func_801402B8(a, 0x16, 8);
        H_f12c(a, 0x48) = H_f12c(a, 0x4A) = H_f12c(a, 0x4C) = 0;
        a[7]++;
    case 2:
        if (H_f12c(a, 0x40)-- > 0) {
            if (inl_wall(a)) {
                res = 3;
                if (func_8009A450() & 0x8000) {
                    res = 2;
                }
                break;
            }
            if ((H_f12c(a, 0x4E) = HU(*(u8 **)(a + 0x38), 4)) & 1) {
                q[7] = 1;
                if (inl_8014601C(a) > 0) {
                    res = 4;
                }
            }
            dx = H_f12c(a, 0x48) * H_f12c(a, 0x4E);
            dz = H_f12c(a, 0x4C) * H_f12c(a, 0x4E);
            if (HU(a, 0x62) & 1) {
                W_d1fb(a, 0x2C) -= dx;
                W_d1fb(a, 0x34) -= dz;
            } else {
                W_d1fb(a, 0x2C) += dx;
                W_d1fb(a, 0x34) += dz;
            }
        } else {
            if (inl_8014601C(a) > 0) {
                res = 4;
            } else {
                res = 1;
            }
        }
        break;
    }
    H_f12c(a, 0x32) += 0x10;
    f_UpdateTownCreatureTerrainContact(a);
    return res;
}

s16 f_UpdateTownCreatureApproachTomba(u8 *a, s32 dist, s32 spd) {
    u8 *q;
    s16 res = 0;
    s32 d;
    s32 dx, dz;
    s16 t;

    d = func_800781E0(H_f12c(a, 0x2E) - D_1F800160_71b4, H_f12c(a, 0x36) - D_1F800164_d75f);
    q = a + 0x60;
    switch (a[7]) {
    case 0:
        if (d < dist) {
            res = 1;
            break;
        }
        HU(q, 2) &= 0xFFFB;
        func_801402B8(a, 4, 0);
        H_f12c(a, 0x4E) = 0;
        H_f12c(a, 0x42) = 0x3C;
        a[7]++;
    case 1:
        if (d < dist) {
            res = 1;
        } else {
            H_f12c(a, 0x4E) += (spd - H_f12c(a, 0x4E)) >> 2;
        }
        t = --H_f12c(a, 0x42);
        if (t <= 0) {
            res = 1;
        }
        if ((t & 7) == 0) {
            func_8003116C(0, a + 0x2C, -5);
        }
        break;
    }
    if (inl_wall(a)) {
        res = -1;
    }
    H_f12c(a, 0x32) += 0x10;
    f_UpdateTownCreatureTerrainContact(a);
    dx = H_f12c(a, 0x48) * H_f12c(a, 0x4E);
    dz = H_f12c(a, 0x4C) * H_f12c(a, 0x4E);
    if (HU(a, 0x62) & 1) {
        W_d1fb(a, 0x2C) -= dx;
        W_d1fb(a, 0x34) -= dz;
    } else {
        W_d1fb(a, 0x2C) += dx;
        W_d1fb(a, 0x34) += dz;
    }
    if (res == 0 && a[0x66] == 0x81 && a[0x29] == 0 && a[4] == 1) {
        W_d1fb(a, 4) = 0x20501;
    }
    return res;
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateTownCreatureLeapingCharge);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateTownCreatureExtendedLeap);

s32 f_UpdateTownCreatureJumpingAttack(u8 *a) {
    s32 res = 0;
    s32 dx, dz;

    dx = H_f12c(a, 0x48) * H_f12c(a, 0x4E);
    dz = H_f12c(a, 0x4C) * H_f12c(a, 0x4E);
    if (HU(a, 0x62) & 1) {
        W_d1fb(a, 0x2C) -= dx;
        W_d1fb(a, 0x34) -= dz;
    } else {
        W_d1fb(a, 0x2C) += dx;
        W_d1fb(a, 0x34) += dz;
    }
    switch (a[7]) {
    case 0:
        func_801402B8(a, 0x2A, 0xA);
        H_f12c(a, 0x42) = 5;
        a[7]++;
    case 1:
        if (--H_f12c(a, 0x42) <= 0) {
            a[7]++;
        }
        H_f12c(a, 0x4E) += -H_f12c(a, 0x4E) >> 4;
        H_f12c(a, 0x32) += 0x10;
        f_UpdateTownCreatureTerrainContact(a);
        return res;
    case 2:
        func_8003116C(0, a + 0x2C, -0x32);
        H_f12c(a, 0x4E) = 0xD28;
        H_f12c(a, 0x50) = -0xF;
        func_801402B8(a, 0x2B, 0);
        H_f12c(a, 0x58) = 0;
        a[7]++;
    case 3:
        H_f12c(a, 0x32) += H_f12c(a, 0x50);
        H_f12c(a, 0x50)++;
        f_UpdateTownCreatureTerrainContact(a);
        if (H_f12c(a, 0x50) < 0) {
            return res;
        }
        a[7]++;
        break;
    case 4:
        func_801402B8(a, 0x2C, H_f12c(a, 0x42) = 4);
        a[7]++;
    case 5:
        H_f12c(a, 0x32) += H_f12c(a, 0x50);
        H_f12c(a, 0x50)++;
        f_UpdateTownCreatureTerrainContact(a);
        if (H_f12c(a, 0x50) >= 0x19) {
            H_f12c(a, 0x50) = 0x19;
        }
        if (--H_f12c(a, 0x42) > 0) {
            return res;
        }
        a[7]++;
        break;
    case 6:
        func_801402B8(a, 0x2D, 6);
        a[7]++;
    case 7:
        H_f12c(a, 0x32) += H_f12c(a, 0x50);
        if (++H_f12c(a, 0x50) >= 0x19) {
            H_f12c(a, 0x50) = 0x19;
        }
        f_UpdateTownCreatureTerrainContact(a);
        if (a[0x29] != 0) {
            func_8003116C(0, a + 0x2C, -0x32);
            func_801402B8(a, 0x2E, 6);
            H_f12c(a, 0x50) = 0;
            H_f12c(a, 0x42) = 0xA;
            a[7]++;
        }
        break;
    case 8:
        H_f12c(a, 0x4E) += -H_f12c(a, 0x4E) >> 2;
        H_f12c(a, 0x32) += 0x10;
        f_UpdateTownCreatureTerrainContact(a);
        if (--H_f12c(a, 0x42) <= 0) {
            res = 1;
        }
        break;
    }
    return res;
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateTownCreatureBehaviorState);

s32 f_UpdateTownCreatureVariantActivation(u8 *a) {
    u8 *q = a + 0x60;
    s32 res = 0;
    s32 k;

    switch (a[7]) {
    case 0:
    case 1:
        switch (a[3]) {
        case 2:
            k = 7;
            break;
        case 3:
        case 4:
            k = 0x1B;
            break;
        case 5:
            k = 6;
            break;
        case 1:
        default:
            k = 0x12;
            break;
        }
        func_801402B8(a, k, 0);
        HU(q, 2) &= 0xFFFB;
        f_UpdateTownCreatureTerrainContact(a);
        a[7] = 2;
    case 2:
        if ((u32)func_80078240(D_1F800160_71b4 - H_f12c(a, 0x2E), D_1F800162 - H_f12c(a, 0x32), D_1F800164_d75f - H_f12c(a, 0x36)) < 0x3C0) {
            a[7]++;
        }
        break;
    case 3:
        switch (a[3]) {
        case 2:
            k = 7;
            res = 1;
            break;
        case 3:
        case 4:
            k = 0x1D;
            break;
        case 5:
            k = 0x34;
            break;
        case 1:
        default:
            k = 0x13;
            break;
        }
        func_801402B8(a, k, 8);
        H_f12c(a, 0x40) = 0x28;
        a[7]++;
    case 4:
        if (--H_f12c(a, 0x40) <= 0) {
            a[7]++;
        }
        break;
    case 5:
        func_801402B8(a, 7, 8);
        H_f12c(a, 0x40) = 0x1E;
        a[7]++;
    case 6:
        if (--H_f12c(a, 0x40) <= 0) {
            res = 1;
        }
        break;
    }
    H_f12c(a, 0x32) += 0x10;
    f_UpdateTownCreatureTerrainContact(a);
    return res;
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateTownCreatureInteractionLifecycle);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_HandleTownCreatureActor);

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateTownCreatureSpawner);

void f_UpdateCrabBasketCarrierSequence(u8 *a) {
    u8 *q = a + 0x60;
    s32 dx, dz;

    switch (a[7]) {
    case 0:
        W_d1fb(a, 0x10) = (s32)f_SpawnCrabBasketRewardActor((s32)a, 0);
        W_d1fb(a, 0x14) = 0;
        HU(q, 2) |= 1;
        H_f12c(a, 0x50) = 0;
        a[7]++;
    case 1:
        func_801402B8(a, 0x23, 8);
        H_f12c(a, 0x4E) = 0x800;
        H_f12c(a, 0x40) = 0x14;
        a[7]++;
    case 2:
        dx = H_f12c(a, 0x48) * H_f12c(a, 0x4E);
        dz = H_f12c(a, 0x4C) * H_f12c(a, 0x4E);
        if (HU(a, 0x62) & 1) {
            W_d1fb(a, 0x2C) -= dx;
            W_d1fb(a, 0x34) -= dz;
        } else {
            W_d1fb(a, 0x2C) += dx;
            W_d1fb(a, 0x34) += dz;
        }
        if (--H_f12c(a, 0x40) <= 0) {
            a[7]++;
        }
        break;
    case 3:
        func_801402B8(a, 0x24, 8);
        H_f12c(a, 0x40) = 0x10;
        a[7]++;
    case 4:
        if (--H_f12c(a, 0x40) <= 0) {
            H_f12c(a, 0x40) = 0x10;
            a[7]++;
            HU(q, 2) |= 4;
        }
        break;
    case 5:
        H_f12c(a, 0x56) += 0x80;
        if (H_f12c(a, 0x40)-- <= 0) {
            a[7] = 1;
            HU(q, 2) ^= 1;
            H_f12c(a, 0x56) = 0;
            HU(q, 2) &= 0xFFFB;
        }
        break;
    }
    f_UpdateTownCreatureTerrainContact(a);
    H_f12c(a, 0x32) += 0x14;
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateLinkedTownCreatureActor);

s32 func_80145C78(s32 k, u8 *b) {
    if (k < 4) {
        return M2C_FIELD(b, s16 *, 0xA) >= 0x125C;
    }
    if (k == 7) {
        return M2C_FIELD(b, s16 *, 0xA) >= 0x125C;
    }
    if ((u32)(k - 4) < 8) {
        return 1;
    }
    return 2;
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80145CD0);

extern s8 D_1F800160[];
extern s8 D_1F800164[];
s32 func_80145DD4(s32 arg0, s32 arg1) {
    return (u32) (((arg1 - func_800782B0(arg0 + 0x2C, *((s16 *)D_1F800160), *((s16 *)D_1F800164))) + 0x400) & 0xFFF) >= 0x801U;
}

s32 func_80145E20(u8 *a) {
    u8 *q = a + 0x60;
    s32 h = M2C_FIELD(a, u16 *, 0x60);
    s8 r;

    r = (u32)((h - func_800782B0(a + 0x2C, D_1F800160_71b4, D_1F800164_d75f) + 0x400) & 0xFFF) > 0x800;
    if (r) {
        M2C_FIELD(q, u16 *, 2) |= 1;
    } else {
        M2C_FIELD(q, u16 *, 2) &= 0xFFFE;
    }
    return r;
}

s32 func_80145EA4(u8 *a) {
    u8 *q = a + 0x60;
    s32 h = M2C_FIELD(a, u16 *, 0x60);
    s8 r;

    r = (u32)((h - func_800782B0(a + 0x2C, D_1F800160_71b4, D_1F800164_d75f) + 0x400) & 0xFFF) > 0x800;
    if (M2C_FIELD(q, u16 *, 2) & 1) {
        if (!r) return 1;
    } else {
        if (r) return 1;
    }
    return 0;
}

extern s8 D_1F800160[];
extern s8 D_1F800164[];
void func_80145F30(void *arg0) {
    s16 temp_a2;

    temp_a2 = M2C_FIELD(arg0, s16 *, 0x2E);
    func_800781E0(temp_a2 - *((s16 *)D_1F800160), M2C_FIELD(arg0, s16 *, 0x36) - *((s16 *)D_1F800164), temp_a2);
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", func_80145F6C);

s32 func_8014601C(u8 *a) {
    s16 d = func_800781E0(M2C_FIELD(a, s16 *, 0x2E) - D_1F800160_71b4, M2C_FIELD(a, s16 *, 0x36) - D_1F800164_d75f);

    if ((D_800E7FFE & 0x8200) || d > 0x640) {
        return -1;
    }
    if (d >= 0x44D) {
        return 0;
    }
    if (d >= 0x259) {
        return 1;
    }
    return 2;
}

s16 func_801460A4(void *arg0) {
    s16 temp_v0;

    temp_v0 = f_UpdateTownCreatureKnockbackBounce();
    if ((u8) M2C_FIELD(arg0, u8 *, 7) < 3U) {
        M2C_FIELD(arg0, s16 *, 0x58) = 0;
    }
    return temp_v0;
}

s32 f_UpdateTownCreatureTurnaround(u8 *a) {
    s32 r = 0;
    u8 *q = a + 0x60;

    switch (a[7]) {
    case 0:
        M2C_FIELD(q, u16 *, 2) &= ~4;
        func_801402B8(a, 0x1A, 8);
        M2C_FIELD(a, s16 *, 0x4E) = 0;
        a[7] = 1;
    case 1:
        if (M2C_FIELD(M2C_FIELD(a, u8 **, 0x38), u16 *, 4) != 0) {
            M2C_FIELD(q, u16 *, 2) ^= 1;
            M2C_FIELD(a, s16 *, 0x56) += 0x800;
            func_801402B8(a, 7, 0);
            a[7] = 2;
        }
        break;
    default:
        if (a[7] >= 0x14) {
            r = 1;
        } else {
            a[7]++;
        }
        break;
    }
    M2C_FIELD(a, s16 *, 0x32) += 0x10;
    f_UpdateTownCreatureTerrainContact(a);
    return r;
}

s32 func_801461E4(u8 *a, s32 b, u8 c) {
    u16 *f = (u16 *)(a + 0x60);
    s32 r = 0;

    if (a[7] == 0) {
        f[1] &= 0xFFFB;
        func_801402B8(a, (s16)b, 8);
        a[7] = c;
        M2C_FIELD(a, s16 *, 0x4E) = 0;
    }
    if (a[7] < 2) {
        r = 1;
    } else {
        a[7]--;
    }
    M2C_FIELD(a, s16 *, 0x32) += 0x10;
    f_UpdateTownCreatureTerrainContact(a);
    return r;
}

s32 func_80146288(s16 *v, u32 r) {
    return (u32)func_80078240(D_1F800160_71b4 - v[0], D_1F800162 - v[1], D_1F800164_d75f - v[2]) < r;
}

u8 *func_801462E4(s32 a, s32 b) {
    u8 *p = func_80072DDC(0, 3, 2, 3);

    if (p != NULL) {
        M2C_FIELD(p, void **, 0x1C) = f_HandleTownCreatureActor;
        p[0x3] = b;
        M2C_FIELD(p, s32 *, 0x10) = 0;
        M2C_FIELD(p, s32 *, 0x14) = a;
    }
    return p;
}

u8 *func_80146348(u8 *a, void *b) {
    u8 *g = D_800BF808_1760;
    u8 *p;

    if (g[0x1B] & 0x80) {
        return NULL;
    }
    p = func_80072DDC(a, 3, 2, 3);
    if (p != NULL) {
        g[0x1B] |= 0x80;
        p[3] = 0x80;
        M2C_FIELD(p, u8 **, 0x10) = a;
        M2C_FIELD(p, void **, 0x14) = b;
        M2C_FIELD(p, void **, 0x1C) = f_HandleTownCreatureActor;
    }
    return p;
}

extern u8 D_800BF823;
void func_801463EC(u8 *a) {
    switch (a[4]) {
    case 0:
        a[4] = 1;
        a[5] = 0;
        D_800BF823 = 0;
        break;
    case 1:
        if (D_1F800137 == 0) {
            f_UpdateTownCreatureSpawner(a);
        }
        break;
    case 2:
    case 3:
        func_8007ADD0(a);
        break;
    }
}

void func_80146478(u32 *p, void *b)
{
    u32 lo = *p;
    u32 packed;

    packed = lo;
    lo = packed & 0xFFFF;
    p += 4;
    f_UpdateWindmillCollapseParticleActor(func_801465EC(p, b, lo), b, packed >> 16);
}

INCLUDE_ASM("asm/a00/nonmatchings/a00", f_ApplyOverlayModelFrameRange);

// ASM by design: hand-written GTE routine (no stack frame, trapping add / addi / sub, `or rd, $zero, rs` moves: never emitted by gcc 2.8.1).
INCLUDE_ASM("asm/a00/nonmatchings/a00", func_801465EC);

// ASM by design: hand-written GTE routine (no stack frame, trapping add / addi / sub, `or rd, $zero, rs` moves: never emitted by gcc 2.8.1).
INCLUDE_ASM("asm/a00/nonmatchings/a00", f_UpdateWindmillCollapseParticleActor);

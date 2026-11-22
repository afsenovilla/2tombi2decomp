#include "common.h"
#include "game.h"
#include "m2c.h"
#include "gte.h"

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8010A528);

void func_8010A528();
u8 *func_8010A6E8(void)
{
    u8 *a = func_8007A980(0, 3, 1);

    if (a == NULL) {
        return NULL;
    }
    *(void **)(a + 0x1C) = func_8010A528;
    a[2] = 1;
    a[0x28] |= 0x80;
    return a;
}

s32 func_8010A73C(u8 *a, s32 b) {
    s32 s = (func_80083F50(M2C_FIELD(a, s16 *, 0x56)) * M2C_FIELD(a, s16 *, 0x44)) >> 4;
    s32 c = func_80083E80(M2C_FIELD(a, s16 *, 0x56)) * M2C_FIELD(a, s16 *, 0x44);

    M2C_FIELD(a, s32 *, 0x2C) += s;
    M2C_FIELD(a, s32 *, 0x34) -= c >> 4;
    if (b != 0) {
        return func_8010A7D8(a);
    }
    return 0;
}

extern s16 D_1F8000C0_65b0[];
s32 func_8010A7D8(u8 *a) {
    s16 z = (-func_80083E80(M2C_FIELD(a, s16 *, 0x56)) * M2C_FIELD(a, s16 *, 0x80)) >> 12;
    s16 *v;

    v = D_1F8000C0_65b0;
    v[0] = (func_80083F50(M2C_FIELD(a, s16 *, 0x56)) * M2C_FIELD(a, s16 *, 0x80)) >> 12;
    v[1] = M2C_FIELD(a, s16 *, 0x86) - M2C_FIELD(a, s16 *, 0x84);
    v[2] = z;
    return func_801258A4(a + 0x2C, v) != 0;
}

typedef struct { s16 x, y, z, pad; } AreaSVec;
extern AreaSVec D_1F8000C0;
extern s32 D_8012C580[];
s32 func_8010A868(u8 *a) {
    s16 y;

    if (a[0x29] == 0) {
        D_1F8000C0.x = 0;
        y = M2C_FIELD(a, s16 *, 0x86) - M2C_FIELD(a, s16 *, 0x84);
        D_1F8000C0.z = 0;
        D_1F8000C0.y = y;
        if (func_80125C5C(a + 0x2C, &D_1F8000C0, 0) > 0) {
            a[0x29] = 1;
        }
    }
    return a[0x29];
}

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8010A8D0);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8010ACB8);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8010AEC4);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8010B068);

typedef struct {
    u16 type;
    u8 pad2[6];
    u8 mag0;
    u8 mag1;
    u8 x;
    u8 y;
} AreaPadAnalog;
extern AreaPadAnalog D_800ECF48;
extern u16 D_800ECF54;
void func_8010B2D0(u8 *a) {
    AreaPadAnalog *p = &D_800ECF48;
    u8 m;

    if (p->y + p->x != 0 && p->type == 7) {
        m = p->mag1;
        if (m < p->mag0) {
            m = p->mag0;
        }
        a[0x14B] = m;
        a[0x147] = ((u32)func_80085690((s8)p->y, (s8)p->x) & 0xFFF) >> 5;
        return;
    }
    switch (D_800ECF54 & 0xF0) {
    case 0x20:
        a[0x147] = 0;
        break;
    case 0x80:
        a[0x147] = 0x40;
        break;
    case 0x10:
        a[0x147] = 0x60;
        break;
    case 0x40:
        a[0x147] = 0x20;
        break;
    case 0x30:
        a[0x147] = 0x70;
        break;
    case 0x60:
        a[0x147] = 0x10;
        break;
    case 0x90:
        a[0x147] = 0x50;
        break;
    case 0xC0:
        a[0x147] = 0x30;
        break;
    default:
        a[0x147] |= 0x80;
        a[0x14B] = 0;
        return;
    }
    a[0x14B] = 3;
}

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8010B458);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8010B634);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8010B8B8);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8010BABC);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8010BD80);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8010BEBC);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8010C510);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8010C6E4);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8010C8E4);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8010CF30);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8010CFAC);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8010D288);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8010D6B4);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8010DA78);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8010DBE4);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8010E1F4);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8010E3D8);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8010EA30);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8010EBA8);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8010ED88);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8010F01C);

extern u16 D_800E7E68;
extern u8 D_800BF80F;
extern u8 D_1F800137;
extern u16 D_1F800166;
extern u16 D_1F800190;
void func_8010F63C(u8 *a) {
    u16 held;
    u16 pad;

    switch (a[4]) {
    case 0:
        func_80058648(a, 0);
        break;
    case 1:
        held = D_800E7E68;
        pad = D_800ECF54;
        if (D_800BF80F != 0 || D_1F800137 != 0) {
            D_800E7E68 = 0;
            D_800ECF54 = 0;
            if (D_800ECF48.type == 7) {
                D_800ECF48.x = 0;
                D_800ECF48.y = 0;
            }
        }
        func_8010ED88(a);
        func_800597AC(a);
        D_800E7E68 = held;
        D_800ECF54 = pad;
        break;
    case 2:
    case 3:
        break;
    case 4:
        held = D_800E7E68;
        pad = D_800ECF54;
        if (D_1F800137 == 0) {
            D_800E7E68 = 0;
            D_800ECF54 = 0;
        } else {
            D_800E7E68 = D_1F800166;
            D_800ECF54 = D_1F800190;
        }
        if (D_800ECF48.type == 7) {
            D_800ECF48.x = 0;
            D_800ECF48.y = 0;
        }
        func_8010F01C(a);
        func_800597AC(a);
        D_800E7E68 = held;
        D_800ECF54 = pad;
        break;
    }
}

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8010F798);

void func_8010F84C(u8 *a) {
    u16 x = M2C_FIELD(a, u16 *, 0x2E);

    if ((u16)(x - 0x1BF0) < 0x1A8) {
        if (M2C_FIELD(a, s16 *, 0x36) < 0x28E1) {
            M2C_FIELD(a, s16 *, 0x36) = 0x28E1;
        }
    } else if ((u16)(x - 0x1D98) < 0xD80) {
        if (M2C_FIELD(a, s16 *, 0x36) < 0x29E0) {
            M2C_FIELD(a, s16 *, 0x36) = 0x29E0;
        }
    } else if ((s16)x >= 0x2B18 && M2C_FIELD(a, s16 *, 0x36) < 0x297B) {
        M2C_FIELD(a, s16 *, 0x36) = 0x297B;
    }
}

extern s32 D_8012B5BC[];
void func_8010F8DC(u8 *a) {
    s32 d;

    if (a[5] < 2 && (M2C_FIELD(a, s16 *, 0x6A) & 0xF000) == 0x1000) {
        d = (s16)(-0x8000 - (M2C_FIELD(a, s16 *, 0x56) << 4));
        if (d < 0) {
            d = -d;
        }
        if (d <= 0x2000) {
            a[5] = 5;
            a[6] = 0;
            a[7] = 0;
        }
    }
}

typedef struct {
    u8 pad[0xA];
    s16 count;
    u8 *entries;
    u32 pending;
    u32 done;
} RewardSet;
extern u8 D_1F800137;
typedef struct {
    s16 pad0;
    s16 x;
    s16 pad4;
    s16 y;
    s16 pad8;
    s16 z;
} HiPos;
void func_8010F948(u8 *a)
{
    u8 *o = *(u8 **)(a + 0x10);

    switch (a[6]) {
    case 0:
        o[0x2B] = 1;
        a[6]++;
    case 1:
        func_80076D68(a);
        if (D_1F800137 == 0) {
            a[0x180] = 0x14;
            a[4] = 1;
            a[5] = 0;
            a[6] = 0;
            a[7] = 0;
            func_80054D14(a, 2, 6);
        }
        break;
    }
}

extern u8 D_1F800236;
extern s16 D_1F8001C6;
extern u8 D_800BF871;
void func_8010CFAC(void);
void func_8010F9E4(u8 *a) {
    u8 *e;
    s32 m;

    func_8010A6E8();
    a[1] = 1;
    m = D_1F800236;
    M2C_FIELD(a, s16 *, 0x6A) = 0;
    if (m == 5) {
        if (D_800BF871 == 1) {
            goto c00;
        }
        M2C_FIELD(a, s16 *, 0x56) = 0x400;
    } else if (D_800BF871 == 8) {
        D_1F800137 = 2;
        a[4] = 4;
        M2C_FIELD(a, s16 *, 0x56) = 0x800;
    } else {
    c00:
        M2C_FIELD(a, s16 *, 0x56) = 0xC00;
    }
    M2C_FIELD(a, s16 *, 0x58) = 0;
    M2C_FIELD(a, s16 *, 0x172) = 0;
    func_80054D14(a, 2, 0);
    e = func_8003315C(a);
    if (e != NULL) {
        M2C_FIELD(e, void **, 0x1C) = func_8010CFAC;
    }
    D_1F8001C6 = 0;
}

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8010FAB0);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8010FBFC);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8010FD30);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8010FE90);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8010FFF4);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_801101D4);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80110370);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8011053C);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_801106F0);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_801108A0);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80110AB8);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80110C7C);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80110E20);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80111184);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_801114B0);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80111640);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_801117B0);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80111974);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80111D24);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80111FB4);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80112140);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_801122A4);

extern s8 D_800BF808_c1f7[];
void func_80112654(u8 *a) {
    s8 *g;

    if (a[0x17B] == 0) {
        g = D_800BF808_c1f7;
        if (g[5] == 0 && ((u8 *)g)[0x31] == 0 && M2C_FIELD(a, s16 *, 0x2E) > 0x2710 && M2C_FIELD(a, s16 *, 0x36) < 0xAF0) {
            D_1F800236 = 1;
            D_1F800137 = 2;
            g[7] = 2;
            g[0x31] = 1;
            M2C_FIELD(g, s16 *, 0x32) = 0x102;
        }
    }
}

typedef struct { u8 pad0[7]; u8 unk7; u8 pad8[0x29]; u8 unk31; s16 unk32; } AreaState808_7;
extern AreaState808_7 D_800BF808;
void func_801126DC(u8 *a) {
    if (M2C_FIELD(a, s16 *, 0x2E) > 0x2710 && M2C_FIELD(a, s16 *, 0x36) < 0xAF0) {
        D_1F800236 = 1;
        D_1F800137 = 2;
        D_800BF808.unk7 = 2;
        D_800BF808.unk31 = 1;
        D_800BF808.unk32 = 0x102;
    }
}

extern u8 D_800BF808_1760[];
extern u16 D_800BFE56;
typedef struct {
    s16 v[4];
} Box8;
extern Box8 D_801287E8[];
void func_80112738(u8 *a) {
    u8 *g = D_800BF808_1760;
    s32 i;
    s32 r;
    Box8 *p;

    if (g[0xE] != 0 && g[0xF] == 7 && !(D_800BFE56 & 4)) {
        p = D_801287E8;
        for (i = 0; i < 2; i++, p++) {
            r = func_8010FAB0(a, p);
            if (r != 0 && !(a[0] & 4) && a[5] < 2) {
                a[0] = 7;
                a[0x2B] = (r - 1) << 6;
                a[5] = 7;
                a[6] = 0;
                a[7] = 0;
            }
        }
    }
}

void func_8011281C(void *arg0, void *arg1) {
    if (!(M2C_FIELD(arg0, u16 *, 0x17E) & 0x200) && (func_80022F04() != 0)) {
        M2C_FIELD(arg1, s8 *, 0) = 2;
        M2C_FIELD(arg1, s8 *, 4) = 2;
    }
}

extern u16 D_1F80009C;
extern s16 D_1F80018E;
extern u8 *D_1F800184;
extern u8 D_800BF840;
void func_80112864(u8 *a, u8 *b) {
    s16 d;
    s32 ang;

    if (func_8002300C(a, b, M2C_FIELD(b, s16 *, 0x80)) == 0) {
        return;
    }
    if (M2C_FIELD(a, s16 *, 0x17E) & 0x8200) {
        return;
    }
    ang = D_1F80009C & 0xFFF;
    if (D_1F80018E == 0 && D_1F800137 == 0 && !(b[0] & 2)) {
        d = (ang - M2C_FIELD(a, u16 *, 0x56)) << 4;
        if (abs(d) <= 0x2000 && (a[5] != 0x1F || b == M2C_FIELD(a, u8 **, 0x10))) {
            D_1F80018E = 0x1200;
            D_1F800184 = b;
            D_800BF840 = 0x4B;
        }
    }
}

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80112958);

extern u8 **D_1F80013C;
extern u8 D_1F800144;
extern u8 D_1F800182;
void func_80112A98(void *a)
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
                func_801106F0(a, e);
            } else if (e[2] == 8) {
                func_80110370(a, e);
            }
        }
    }
}

#define F16(p, o) M2C_FIELD(p, s16 *, o)
extern s8 D_800BF80D;
extern u8 **D_1F800154;

void func_80112B5C(u8 *a) {
    u8 **l;
    u8 *e;

    if (F16(a, 0x16E) != 0 && D_800BF80D == 0 && !(M2C_FIELD(a, u16 *, 0x17E) & 0x200)) {
        l = D_1F800154;
        D_1F800182 = *(u8 *)0x1F80015C;
        while (D_1F800182 != 0) {
            e = *l;
            D_1F800182--;
            l++;
            if (e[0] == 1) {
                switch (e[2]) {
                case 0:
                case 1:
                case 2:
                case 3:
                case 4:
                    func_80022060(a, e);
                    break;
                case 5:
                    func_80111D24(a, e);
                    break;
                }
            }
        }
    }
}

extern u8 D_1F80015C;
extern u8 D_1F800183;
void func_80112C58(void) {
    u8 **list = D_1F800154;
    u8 *a;

    for (D_1F800183 = D_1F80015C; D_1F800183 != 0;) {
        a = *list++;
        D_1F800183--;
        if (!(a[0] & 2)) {
            switch (a[2]) {
            case 0:
            case 4:
            case 5:
                func_80112140(a);
                break;
            }
        }
    }
}

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80112D08);

INCLUDE_ASM("asm/a02/nonmatchings/a02", f_SpawnCoalMiningTownSceneActorsFromPlacementTable);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8011321C);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80113394);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80113628);

void func_80113824(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 4);
    switch (temp_v1) {                              /* irregular */
    case 0:
        M2C_FIELD(arg0, u8 *, 4) = 1U;
        f_SpawnCoalMiningTownSceneActorsFromPlacementTable(arg0, 0U);
        func_8004D8D8(5, 0);
        func_8011321C(0);
        return;
    case 1:
        if (func_80112D08(arg0) != 0) {
            f_SpawnCoalMiningTownSceneActorsFromPlacementTable(arg0, M2C_FIELD(arg0, u8 *, 3));
        }
        func_80026A68(arg0);
        func_8011321C(1);
        return;
    case 3:
        func_8007ADD0(arg0);
        /* fallthrough */
    case 2:
        return;
    }
}

INCLUDE_ASM("asm/a02/nonmatchings/a02", f_UpdateCoalMiningTownInteriorDoorPartTransition);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80113BC4);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80113D08);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80113E4C);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80114024);

INCLUDE_ASM("asm/a02/nonmatchings/a02", f_UpdateCoalMiningTownInteriorSceneryAssemblyActor);

s32 func_80114650(u8 *a, u8 *b) {
    s32 r = 0;

    switch (a[0x46]) {
    case 0:
        M2C_FIELD(a, s16 *, 0x50) -= 0x40;
        if (M2C_FIELD(a, s16 *, 0x50) < 0) {
            M2C_FIELD(a, s16 *, 0x50) = 0;
            r = 1;
        }
        break;
    case 1:
        M2C_FIELD(a, s16 *, 0x50) += 0x40;
        if (M2C_FIELD(a, s16 *, 0x50) > 0) {
            M2C_FIELD(a, s16 *, 0x50) = 0;
            r = 1;
        }
        break;
    }
    M2C_FIELD(b, s16 *, 0xA) = M2C_FIELD(a, s16 *, 0x5A) - M2C_FIELD(a, s16 *, 0x50);
    return r;
}

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_801146D8);

INCLUDE_ASM("asm/a02/nonmatchings/a02", f_UpdateCoalMiningTownScenePropActor);

void f_UpdateCoalMiningTownScenePropActor();
void func_80114CC8(u8 *a) {
    u8 *p;

    if (func_80051B70(a, 0xC, 0x26) == 0) {
        M2C_FIELD(a, s16 *, 0x54) = 0;
        M2C_FIELD(a, s16 *, 0x56) = 0;
        M2C_FIELD(a, s16 *, 0x58) = 0;
        p = func_80072DDC(a, 0x81, 3, 0x10);
        M2C_FIELD(p, void **, 0x1C) = f_UpdateCoalMiningTownScenePropActor;
        p[3] = 1;
        M2C_FIELD(p, s16 *, 0x2E) = M2C_FIELD(a, s16 *, 0x2E);
        M2C_FIELD(p, s16 *, 0x32) = M2C_FIELD(a, s16 *, 0x32) + 0x136;
        M2C_FIELD(p, s16 *, 0x36) = M2C_FIELD(a, s16 *, 0x36);
    }
}

void func_80114D54(s32 arg0) {
    func_8007778C();
    func_800517F8(arg0);
}

extern void *D_800ECF80;
extern u8 D_80139100[];
void func_80114D80(u8 *a) {
    M2C_FIELD(a, void **, 0x3C) = D_800ECF80;
    func_80077B38(a, D_80139100, 0x16);
    a[0xD] = 1;
    M2C_FIELD(a, s16 *, 0x5C) = 0;
    a[0xB] = 0x13;
    M2C_FIELD(a, s16 *, 0x54) = 0;
    M2C_FIELD(a, s16 *, 0x56) = 0;
    M2C_FIELD(a, s16 *, 0x58) = 0;
    a[0x47] = 0;
    a[8] = 0;
}

extern u8 D_800BF816;
extern u8 D_1F8000D0[];
extern u8 D_1F800000[];
void func_80114DE4(u8 *a) {
    u8 *s;
    u8 *m;

    if (D_800BF816 == 0) {
        a[4] = 3;
        return;
    }
    a[1] = M2C_FIELD(a, u8 **, 0x10)[1];
    func_80077B5C(a);
    s = D_1F8000D0;
    m = D_1F800000;
    M2C_FIELD(a, s16 *, 0x56) = -M2C_FIELD(s, s16 *, 0x22);
    func_80051794(m);
    func_800847F0(a + 0x54, m);
    func_80084110(s + 0x28, m, a + 0x98);
    M2C_FIELD(a, s32 *, 0xAC) = M2C_FIELD(a, s16 *, 0x2E);
    M2C_FIELD(a, s32 *, 0xB0) = M2C_FIELD(a, s16 *, 0x32);
    M2C_FIELD(a, s32 *, 0xB4) = M2C_FIELD(a, s16 *, 0x36);
}

void func_80114E9C(u8 *a) {
    M2C_FIELD(a, void **, 0x3C) = D_800ECF80;
    func_80077B38(a, D_80139100, 0x14);
    a[0xD] = 1;
    M2C_FIELD(a, s16 *, 0x5C) = 0;
    a[0xB] = 0x10;
    M2C_FIELD(a, s16 *, 0x54) = 0;
    M2C_FIELD(a, s16 *, 0x56) = 0;
    M2C_FIELD(a, s16 *, 0x58) = 0;
    a[0x47] = 0;
    a[8] = 0;
}

void func_80114F00(void *arg0) {
    M2C_FIELD(arg0, s8 *, 1) = 1;
    func_80077B5C();
}

void f_UpdateCoalMiningTownScenePropActor();
void func_80114F24(u8 *a) {
    u8 *p = func_80072DDC(a, 1, 3, 0x10);

    M2C_FIELD(p, void **, 0x1C) = f_UpdateCoalMiningTownScenePropActor;
    p[3] = 3;
    M2C_FIELD(p, s16 *, 0x2E) = M2C_FIELD(a, s16 *, 0x2E);
    M2C_FIELD(p, s16 *, 0x32) = M2C_FIELD(a, s16 *, 0x32);
    M2C_FIELD(p, s16 *, 0x36) = M2C_FIELD(a, s16 *, 0x36);
    func_80042354(1, 1);
}

void func_80114F90(void) {
}

extern u8 D_80129A7C[];
void func_80114F98(u8 *a) {
    switch (a[6]) {
    case 0:
        a[6]++;
        func_80040CDC(a, NULL, D_80129A7C);
        a[0x70] = 1;
        break;
    case 1:
        func_80041098(a);
        if (a[0x70] == 0xFF) {
            a[4] = 3;
            func_80042310();
        }
        break;
    }
}

extern u8 D_800BFA03;
void func_8011501C(void *arg0) {
    M2C_UNK var_a2;

    var_a2 = 0x38;
    if ((u8) D_800BFA03 >= 4U) {
        var_a2 = 0x39;
    }
    if (func_80051B70(arg0, 0xC, var_a2) == 0) {
        M2C_FIELD(arg0, u8 *, 0xD) = (u8) (M2C_FIELD(arg0, u8 *, 0xD) | 4);
        M2C_FIELD(M2C_FIELD(arg0, void **, 0xC0), s8 *, 0x3F) = 0x50;
        M2C_FIELD(arg0, s16 *, 0x54) = 0;
        M2C_FIELD(arg0, s16 *, 0x56) = 0;
        M2C_FIELD(arg0, s16 *, 0x58) = 0;
        func_800517F8(arg0);
    }
}

void func_80115090(void *arg0) {
    if (D_800BF870.pad1[0x192] == 3) {
        func_80051B04(M2C_FIELD(arg0, s32 *, 0xC0), 0xC, 0x39);
        D_800BF870.pad1[0x192] = 4;
    }
    func_8007778C(arg0);
}

void f_UpdateCoalMiningTownScenePropActor();
u8 *func_801150EC(s32 a) {
    u8 *p = func_8007A980(1, 3, 1);

    if (p == NULL) {
        return NULL;
    }
    p[0x2] = 16;
    p[0x3] = 12;
    M2C_FIELD(p, void **, 0x1C) = f_UpdateCoalMiningTownScenePropActor;
    M2C_FIELD(p, s32 *, 0x10) = a;
    return p;
}

extern s32 D_800BF844;
#define PLAYER (*(u8 **)&D_800BF844)
void func_80115148(u8 *a) {
    if (func_80051B70(a, 0xC, 0x3E) == 0) {
        a[0xD] = 0;
        M2C_FIELD(a, s16 *, 0x54) = 0;
        M2C_FIELD(a, s16 *, 0x56) = 0x898;
        M2C_FIELD(a, s16 *, 0x58) = 0;
    }
}

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8011518C);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_801152A8);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_801154DC);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80115620);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80115794);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80115994);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80115AAC);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80115D84);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80115F58);

void func_801167A8(void)
{
    CameraState *c = &g_CameraState;

    c->unk6C = 0x500;
    c->unk6E = 0xA0;
}

extern u8 D_800E7E80[];
void func_801167C4(u8 *a, s32 ang) {
    u8 *t = D_800E7E80;
    u8 *sc;
    s16 r;
    s16 x, z;

    r = -(func_80083F50(M2C_FIELD(a, s16 *, 0xA)) * (M2C_FIELD((sc = D_1F8000D0), s16 *, 0x1E) + M2C_FIELD(a, s32 *, 0x58))) >> 12;
    x = M2C_FIELD(t, s16 *, 0x2E) + ((func_80083F50((s16)ang) * r) >> 12);
    z = M2C_FIELD(t, s16 *, 0x36) - ((func_80083E80((s16)ang) * r) >> 12);
    M2C_FIELD(sc, s16 *, 0x2) = x;
    M2C_FIELD(sc, s16 *, 0xA) = z;
    a[0x66] |= 1;
}

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_801168A0);

extern u16 D_1F8000F2_1841;
void func_80116918(u8 *a) {
    u8 *t = D_800E7E80;
    s16 v[6];

    switch (a[4]) {
    case 0:
        M2C_FIELD(a, s16 *, 0x70) = 0x1400 - D_1F8000F2_1841;
        a[4]++;
        break;
    case 1:
        v[1] = M2C_FIELD(t, s16 *, 0x2E);
        v[3] = M2C_FIELD(t, s16 *, 0x32) - 0x20;
        v[5] = M2C_FIELD(t, s16 *, 0x36);
        func_8006E3F4(a, v);
        func_80115794(a, t, M2C_FIELD(a, s16 *, 0x70));
        func_80115994(a, (s16)(M2C_FIELD(t, s16 *, 0x32) - 0x20));
        break;
    }
}

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_801169D8);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80116C14);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8011718C);

s32 func_801175D0(u8 *a) {
    s32 r = 0;

    switch (a[0x46]) {
    case 0:
        M2C_FIELD(a, s16 *, 0x50) += 0x40;
        if (M2C_FIELD(a, s16 *, 0x50) > 0) {
            M2C_FIELD(a, s16 *, 0x50) = 0;
            r = 1;
        }
        break;
    case 1:
        M2C_FIELD(a, s16 *, 0x50) -= 0x40;
        if (M2C_FIELD(a, s16 *, 0x50) < 0) {
            M2C_FIELD(a, s16 *, 0x50) = 0;
            r = 1;
        }
        break;
    }
    M2C_FIELD(a, s16 *, 0x56) = M2C_FIELD(a, s16 *, 0x5A) - M2C_FIELD(a, s16 *, 0x50);
    return r;
}

s32 func_80117658(s32 k) {
    s32 r = 0;

    if (k == 5) {
        r = 0;
    } else if (k == 6) {
        r = 1;
    } else if (k == 7) {
        r = 2;
    } else if (k == 8) {
        r = 3;
    } else if (k == 10) {
        r = 4;
    } else if (k == 12) {
        r = 5;
    } else if (k == 13) {
        r = 6;
    } else if (k == 9) {
        r = 7;
    } else if (k == 14) {
        r = 8;
    }
    return r;
}

s32 func_801176EC(s32 a, s32 b) {
    s32 r;

    switch (b) {
    case 1:
        r = 1;
        break;
    case 2:
        r = 2;
        break;
    case 3:
        r = 11;
        break;
    case 4:
        if (a == 0) {
            r = 6;
        } else if (a == 0x20) {
            r = 5;
        } else if (a == 0x40) {
            r = 4;
        } else {
            r = 3;
        }
        break;
    case 5:
        if (a == 0) {
            r = 9;
        } else {
            r = 10;
        }
        break;
    case 6:
        if (a == 0) {
            r = 7;
        } else {
            r = 8;
        }
        break;
    case 7:
        r = 12;
        break;
    case 0:
    default:
        r = 0;
        break;
    }
    return r;
}

extern u8 D_800BF8BE;
void func_8011778C(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 5);
    switch (temp_v1) {                              /* irregular */
    case 0:
        if (D_800BF8BE == 0xFF) {
            M2C_FIELD(arg0, u8 *, 5) = 1U;
            return;
        }
        func_801169D8();
        return;
    case 1:
        func_80116C14();
        return;
    }
}

extern u8 D_800BF8BE;
void func_801177F8(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 5);
    switch (temp_v1) {                              /* irregular */
    case 0:
        if (D_800BF8BE == 0xFF) {
            M2C_FIELD(arg0, u8 *, 5) = 1U;
            return;
        }
        func_801169D8();
        return;
    case 1:
        func_80116C14();
        return;
    }
}

extern u8 D_800BF8BE;
void func_80117864(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 5);
    switch (temp_v1) {                              /* irregular */
    case 0:
        if (D_800BF8BE == 0xFF) {
            M2C_FIELD(arg0, u8 *, 5) = 1U;
            return;
        }
        func_801169D8();
        return;
    case 1:
        func_80116C14();
        return;
    }
}

extern u8 D_800BF8BE;
void func_801178D0(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 5);
    switch (temp_v1) {                              /* irregular */
    case 0:
        if (D_800BF8BE == 0xFF) {
            M2C_FIELD(arg0, u8 *, 5) = 1U;
            return;
        }
        func_801169D8();
        return;
    case 1:
        func_80116C14();
        return;
    }
}

extern u8 D_800BF8BE;
void func_8011793C(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 5);
    switch (temp_v1) {                              /* irregular */
    case 0:
        if (D_800BF8BE == 0xFF) {
            M2C_FIELD(arg0, u8 *, 5) = 1U;
            return;
        }
        func_801169D8();
        return;
    case 1:
        func_80116C14();
        return;
    }
}

extern u8 D_800BF8BE;
void func_801179A8(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 5);
    switch (temp_v1) {                              /* irregular */
    case 0:
        if (D_800BF8BE == 0xFF) {
            M2C_FIELD(arg0, u8 *, 5) = 1U;
            return;
        }
        func_801169D8();
        return;
    case 1:
        func_80116C14();
        return;
    }
}

extern u8 D_800BF8BE;
void func_80117A14(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 5);
    switch (temp_v1) {                              /* irregular */
    case 0:
        if (D_800BF8BE == 0xFF) {
            M2C_FIELD(arg0, u8 *, 5) = 1U;
            return;
        }
        func_801169D8();
        return;
    case 1:
        func_80116C14();
        return;
    }
}

extern u8 D_800BF8BE;
void func_80117A80(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 5);
    switch (temp_v1) {                              /* irregular */
    case 0:
        if (D_800BF8BE == 0xFF) {
            M2C_FIELD(arg0, u8 *, 5) = 1U;
            return;
        }
        func_801169D8();
        return;
    case 1:
        func_80116C14();
        return;
    }
}

extern u8 D_800BF8BE;
void func_80117AEC(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 5);
    switch (temp_v1) {                              /* irregular */
    case 0:
        if (D_800BF8BE == 0xFF) {
            M2C_FIELD(arg0, u8 *, 5) = 1U;
            return;
        }
        func_801169D8();
        return;
    case 1:
        func_80116C14();
        return;
    }
}

extern u8 D_800BF8BE;
void func_80117B58(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 5);
    switch (temp_v1) {                              /* irregular */
    case 0:
        if (D_800BF8BE == 0xFF) {
            M2C_FIELD(arg0, u8 *, 5) = 1U;
            return;
        }
        func_801169D8();
        return;
    case 1:
        func_80116C14();
        return;
    }
}

void func_80117BC4(void) {
}

void func_80117BCC(void) {
    func_80116C14();
}

void func_80117BEC(void) {
    func_80116C14();
}

void func_80117C0C(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 5) == 0) {
        func_801169D8();
    }
}

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80117C3C);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80117D64);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80117FC0);

typedef struct {
    u8 b0, b1, b2, b3;
    s16 x, y, z, pad;
    void *fn;
} Placement16;
extern Placement16 D_80129C4C[];
void func_80118280(u8 *a, s32 i) {
    Placement16 *p = &D_80129C4C[i];
    u8 *e;

    e = func_8007AA38(a, p->b1 | ((p->b0 & 0x7F) << 8), 0, 0);
    if (e != NULL) {
        M2C_FIELD(e, u8 **, 0x10) = a;
        e[2] = p->b2;
        e[0x28] = p->b0;
        M2C_FIELD(a, u8 **, 0x14) = e;
        M2C_FIELD(e, s32 *, 0x2C) = p->x << 16;
        M2C_FIELD(e, s32 *, 0x30) = p->y << 16;
        M2C_FIELD(e, s32 *, 0x34) = p->z << 16;
        e[3] = p->b3;
        M2C_FIELD(e, s16 *, 0x54) = 0;
        M2C_FIELD(e, s16 *, 0x56) = 0;
        M2C_FIELD(e, s16 *, 0x58) = 0;
        M2C_FIELD(e, void **, 0x1C) = p->fn;
    }
}

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80118354);

INCLUDE_ASM("asm/a02/nonmatchings/a02", f_UpdateBuryItInTheSandPitActor);

s32 func_80118860(void) {
    func_801167A8();
    return 1;
}

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80118880);

s32 func_80118B50(s32 arg0) {
    if (M2C_FIELD(arg0, s16 *, 0x40) != 0) {
        if ((func_80119694(arg0, (s32) M2C_FIELD(arg0, s16 *, 0x2E), (s32) M2C_FIELD(arg0, s16 *, 0x36)) << 0x10) != 0) {
            M2C_FIELD(arg0, s8 *, 5) = 3;
        }
    } else if (D_800BF870.pad1[0x18D] & 0x80) {
        if ((func_80119694(arg0, (s32) (s16) ((u16) M2C_FIELD(arg0, s16 *, 0x2E) - 0x14A), (s32) (s16) ((u16) M2C_FIELD(arg0, s16 *, 0x36) - 0x10E)) << 0x10) != 0) {
            M2C_FIELD(arg0, s8 *, 5) = 1;
            M2C_FIELD(arg0, s8 *, 6) = 0;
            M2C_FIELD(arg0, s8 *, 0x5E) = 4;
        }
    } else if ((func_80119694(arg0, (s32) (s16) ((u16) M2C_FIELD(arg0, s16 *, 0x2E) - 0x118), (s32) (s16) ((u16) M2C_FIELD(arg0, s16 *, 0x36) - 0x10E)) << 0x10) != 0) {
        D_800BF870.pad1[0x18D] = 3;
        M2C_FIELD(arg0, s8 *, 5) = 0;
    }
    return func_801255A4((s32) (M2C_FIELD(arg0, u16 *, 0x44) << 0x10) >> 0x18);
}

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80118C54);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8011903C);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_801191B0);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80119390);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80119510);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80119694);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80119880);

extern u8 D_800BF8BE;
void func_80119990(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 5);
    switch (temp_v1) {                              /* irregular */
    case 0:
        if (D_800BF8BE == 0xFF) {
            M2C_FIELD(arg0, u8 *, 5) = 1U;
            return;
        }
        return;
    case 1:
        func_80076D68();
        break;
    }
}

void func_80123470();
void func_801199EC(u8 *a) {
    u8 *e;

    switch (a[5]) {
    case 0:
        if (D_800BF8BE == 0xFF) {
            a[5] = 1;
            M2C_FIELD(a, s16 *, 0x40) = 0;
            M2C_FIELD(a, s16 *, 0x42) = 0x1E;
        }
        break;
    case 1:
        M2C_FIELD(a, s16 *, 0x40) = (M2C_FIELD(a, u16 *, 0x40) + 1) & 7;
        func_801255C0(0x20);
        if (--M2C_FIELD(a, s16 *, 0x42) == 0) {
            e = func_80072DDC(a, 0, 2, 0x20);
            if (e != NULL) {
                e[3] = 2;
                e[0] = 1;
                M2C_FIELD(e, void **, 0x1C) = func_80123470;
                e[0x28] |= 0x80;
            }
            M2C_FIELD(a, s16 *, 0x42) = (u8)func_8009A450() + 0x1E;
        }
        break;
    }
}

extern u8 D_800BF9FE;
void func_80119ADC(u8 *a) {
    switch (a[5]) {
    case 0:
        func_8011A10C(a);
        break;
    case 1:
        if ((s16)func_80119F78(a)) {
            if (M2C_FIELD(a, s16 *, 0x40) != 0) {
                a[5] = 2;
                a[6] = 0;
            } else {
                a[5] = 0;
                D_800BF9FE = 0;
            }
        }
        break;
    case 2:
        func_80118B50((s32)a);
        break;
    case 3:
        func_80118C54(a);
        break;
    }
    a[0x2B] = 0;
}

void func_80119BAC(u8 *a) {
    switch (a[5]) {
    case 0:
        func_8011903C(a);
        break;
    case 1:
        if ((s16)func_80119F78(a)) {
            if (M2C_FIELD(a, s16 *, 0x40) != 0) {
                a[5] = 2;
                a[6] = 0;
            } else {
                a[5] = 0;
                a[6] = 3;
            }
        }
        break;
    case 2:
        func_8011A1F0(a);
        break;
    case 3:
        func_801191B0(a);
        break;
    }
    a[0x2B] = 0;
}

void func_80119C7C(u8 *a) {
    switch (a[5]) {
    case 0:
        func_80119390(a);
        break;
    case 1:
        if ((s16)func_80119F78(a)) {
            if (M2C_FIELD(a, s16 *, 0x40) != 0) {
                a[5] = 2;
                a[6] = 0;
            } else {
                a[0] = 1;
                a[5] = 0;
                a[6] = 2;
                M2C_FIELD(a, s16 *, 0x40) = 1;
            }
        }
        break;
    case 2:
        func_8011A348(a);
        break;
    case 3:
        func_80119510(a);
        break;
    }
    a[0x2B] = 0;
}

#define P(a, o) M2C_FIELD(a, u8 **, o)
s32 func_80119D58(u8 *a, s32 b) {
    if (b == 0) {
        M2C_FIELD(P(a, 0xC4), s16 *, 8) += 0x80;
        if (M2C_FIELD(P(a, 0xC4), s16 *, 8) >= 0x400) {
            M2C_FIELD(P(a, 0xC4), s16 *, 8) = 0x400;
            a[0x47] = 1;
            return 1;
        }
    } else {
        M2C_FIELD(P(a, 0xC4), s16 *, 8) -= 0x80;
        if (M2C_FIELD(P(a, 0xC4), s16 *, 8) <= 0) {
            M2C_FIELD(P(a, 0xC4), s16 *, 8) = 0;
            a[0x47] = 0;
            return 1;
        }
    }
    return 0;
}

extern u8 D_80139F38[];
extern u8 D_80129E18[];
s32 func_80119DEC(u8 *a) {
    u8 *g = D_800BF808_1760;
    u8 *p;

    p = func_8006FB0C(a, g[3]);
    M2C_FIELD(g, u8 **, 0x3C) = p;
    if (p != NULL) {
        p[0x5E] = 0;
        func_80040CDC(a, D_80139F38, D_80129E18);
        a[0x70] = 1;
        func_80042354(1, 1);
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80119E68);

extern void *D_80129FB8[];
s32 func_80119F78(u8 *a) {
    func_80041098(a);
    if (a[0x71] != 0xFF) {
        return 0;
    }
    switch (a[6]) {
    case 0:
        func_80040D68(a, D_80129FB8[a[0x5E]]);
        a[0x70] = 1;
        a[6]++;
        break;
    case 1:
        return 1;
    }
    return 0;
}

s32 func_8011A010(u8 *a) {
    if (a[3] == 2 && M2C_FIELD(a, s16 *, 0x62) == 0) {
        if ((u16)(M2C_FIELD(a, u16 *, 0x60) - 0x81) < 2) {
            return 3;
        }
        return 2;
    }
    return 2;
}

extern u8 D_800BF9EB;
s32 func_8011A058(u8 *a) {
    if (a[3] == 2 && M2C_FIELD(a, s16 *, 0x62) == 0) {
        if (M2C_FIELD(a, s16 *, 0x60) == 0x4A) {
            return 3;
        }
        return 2;
    }
    return 2;
}

s32 func_8011A098(u8 *a) {
    if (a[3] == 2 && M2C_FIELD(a, s16 *, 0x62) == 0) {
        if (M2C_FIELD(a, s16 *, 0x60) == 0x93) {
            return 3;
        }
        return 2;
    }
    return 2;
}

s32 func_8011A0D8(u8 *a) {
    if (a[3] != 3) {
        return 2;
    }
    if (M2C_FIELD(a, s16 *, 0x60) == 0x7B) {
        return 3;
    }
    return 2;
}

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8011A10C);

void func_8011A1F0(u8 *a) {
    if (M2C_FIELD(a, s16 *, 0x40) != 0) {
        if ((s16)func_80119694(a, M2C_FIELD(a, s16 *, 0x2E), M2C_FIELD(a, s16 *, 0x36)) != 0) {
            a[5] = 0;
            a[6] = 3;
        }
    } else if ((s16)func_80119694(a, M2C_FIELD(a, s16 *, 0x2E), (s16)(M2C_FIELD(a, s16 *, 0x36) - 0x1C2)) != 0) {
        a[5] = 1;
        a[6] = 0;
        a[0x5E] = 5;
    }
}

extern u8 D_800BF80B;
extern u8 D_800BF901;
s32 func_8011A280(u8 *a) {
    switch (D_800BF80B) {
    case 0x85:
        M2C_FIELD(a, s16 *, 0x60) = 0x49;
        break;
    case 0x79:
    case 0x7A:
        if (D_800BF901 == 0xFF) {
            M2C_FIELD(a, s16 *, 0x60) = 0x7B;
        } else {
            M2C_FIELD(a, s16 *, 0x60) = 0x7A;
        }
        break;
    case 0x81:
        if (D_800BF901 == 0xFF) {
            M2C_FIELD(a, s16 *, 0x60) = 0x83;
        } else {
            M2C_FIELD(a, s16 *, 0x60) = D_800BF80B;
        }
        break;
    case 0x82:
        if (D_800BF901 == 0xFF) {
            M2C_FIELD(a, s16 *, 0x60) = 0x84;
        } else {
            M2C_FIELD(a, s16 *, 0x60) = D_800BF80B;
        }
        break;
    default:
        return 0;
    }
    return 1;
}

void func_8011A348(u8 *a) {
    GameState *g;

    if (M2C_FIELD(a, s16 *, 0x40) != 0) {
        if ((s16)func_80119694(a, M2C_FIELD(a, s16 *, 0x2E), M2C_FIELD(a, s16 *, 0x36)) != 0) {
            g = &D_800BF870;
            if (g->pad1[0x19A] == 0) {
                g->pad1[0x19A]++;
                a[5] = 1;
                M2C_FIELD(a, s16 *, 0x40) = 0;
                a[6] = 0;
                a[0x5E] = 5;
            } else {
                a[5] = 0;
                a[6] = 3;
            }
        }
    } else if ((s16)func_80119694(a, M2C_FIELD(a, s16 *, 0x2E), (s16)(M2C_FIELD(a, s16 *, 0x36) - 0x1C2)) != 0) {
        D_800BF870.pad1[0x19A]++;
        a[5] = 0;
        a[6] = 3;
    }
}

INCLUDE_ASM("asm/a02/nonmatchings/a02", f_UpdateLetsMakeAPotSequence);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8011A8D4);

void func_8011A8D4();
s32 func_8011AAC0(u8 *a) {
    u8 t;
    u8 *p = func_80072DDC(0, 129, 4, 36);

    if (p == NULL) {
        return 0;
    }
    M2C_FIELD(p, s16 *, 0x2E) = 3540;
    M2C_FIELD(p, s16 *, 0x32) = -2090;
    M2C_FIELD(p, s16 *, 0x36) = 6050;
    t = a[0x5E];
    M2C_FIELD(p, void **, 0x1C) = func_8011A8D4;
    p[0x3] = t;
    return 1;
}

void func_8011AB34(u8 *a) {
    if (func_80051B70(a, 0xC, 0x34) == 0) {
        a[0xD] |= 4;
        M2C_FIELD(a, u8 **, 0xC0)[0x3F] = 0xEC;
        a[0] = 1;
        M2C_FIELD(a, s16 *, 0x80) = 0x64;
        M2C_FIELD(a, s16 *, 0x82) = 0xC8;
        M2C_FIELD(a, s16 *, 0x84) = 0x3C;
        M2C_FIELD(a, s16 *, 0x86) = 0x78;
        M2C_FIELD(a, s16 *, 0x48) = 0x18;
        M2C_FIELD(a, s16 *, 0x54) = 0;
        M2C_FIELD(a, s16 *, 0x56) = 0;
        M2C_FIELD(a, s16 *, 0x58) = 0;
        a[0x2B] = 0;
        M2C_FIELD(a, s16 *, 0x4C) = 0x20;
    }
}

void func_8011ABC8(u8 *a) {
    if (func_80051B70(a, 0xC, 0x33) == 0) {
        a[0] = 2;
        M2C_FIELD(a, s16 *, 0x54) = 0;
        M2C_FIELD(a, s16 *, 0x56) = 0;
        M2C_FIELD(a, s16 *, 0x58) = 0;
    }
}

void func_8011AC0C(void *arg0) {
    M2C_FIELD(arg0, s8 *, 1) = 1;
    func_80077EBC();
    func_800517F8(arg0);
}

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8011AC40);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8011AEF0);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8011B1FC);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8011B5C4);

extern M2C_UNK func_8011B5C4;
void func_8011B8AC(s32 arg0, s8 arg1) {
    void *temp_v0;

    temp_v0 = func_8007A980(3, 4, 0);
    M2C_FIELD(temp_v0, s8 *, 2) = 0x25;
    M2C_FIELD(temp_v0, s8 *, 3) = arg1;
    M2C_FIELD(temp_v0, M2C_UNK **, 0x1C) = &func_8011B5C4;
    M2C_FIELD(temp_v0, s32 *, 0x10) = arg0;
}

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8011B904);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8011BACC);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8011BC0C);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8011BE48);

void func_8011BE48();
u8 *func_8011BF84(u8 *a, s32 b) {
    u8 *p = func_8007A980(1, 4, 0);

    if (p != NULL) {
        M2C_FIELD(p, void **, 0x1C) = func_8011BE48;
        p[2] = 0x28;
        p[3] = b;
        M2C_FIELD(p, u8 **, 0x10) = a;
        p[0x28] |= 0x80;
        return p;
    }
    return NULL;
}

void func_8011BFF4(void *arg0, void *arg1, s16 arg2, s32 arg3) {
    M2C_FIELD(arg0, s16 *, 0x58) = 0;
    M2C_FIELD(arg0, u16 *, 0x2E) = (u16) ((s32) (M2C_FIELD(M2C_FIELD(arg1, void **, 0xD0), s32 *, 0x2C) + M2C_FIELD(M2C_FIELD(arg1, void **, 0xDC), s32 *, 0x2C)) / 2);
    M2C_FIELD(arg0, u16 *, 0x2E) = (u16) (M2C_FIELD(arg0, u16 *, 0x2E) + ((s32) (func_80083F50(M2C_FIELD(arg1, s16 *, 0x56)) * arg2) >> 0xC));
    M2C_FIELD(arg0, u16 *, 0x36) = (u16) ((s32) (M2C_FIELD(M2C_FIELD(arg1, void **, 0xD0), s32 *, 0x34) + M2C_FIELD(M2C_FIELD(arg1, void **, 0xDC), s32 *, 0x34)) / 2);
    M2C_FIELD(arg0, u16 *, 0x36) = (u16) (M2C_FIELD(arg0, u16 *, 0x36) - ((s32) (func_80083E80(M2C_FIELD(arg1, s16 *, 0x56)) * arg2) >> 0xC));
    M2C_FIELD(arg0, s16 *, 0x32) = (s16) (arg3 + ((s32) (M2C_FIELD(M2C_FIELD(arg1, void **, 0xD0), s32 *, 0x30) + M2C_FIELD(M2C_FIELD(arg1, void **, 0xDC), s32 *, 0x30)) / 2));
}

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8011C100);

INCLUDE_ASM("asm/a02/nonmatchings/a02", f_UpdateFreedCharlesSequence);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8011C52C);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8011C710);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8011C810);

extern M2C_UNK func_8011C52C;
void func_8011C94C(s32 arg0, s8 arg1) {
    void *temp_v0;

    temp_v0 = func_8007A980(3, 9, 0);
    M2C_FIELD(temp_v0, s8 *, 2) = 1;
    M2C_FIELD(temp_v0, s8 *, 3) = arg1;
    M2C_FIELD(temp_v0, M2C_UNK **, 0x1C) = &func_8011C52C;
    M2C_FIELD(temp_v0, u8 *, 0x28) = (u8) (M2C_FIELD(temp_v0, u8 *, 0x28) | 0x80);
}

s32 func_8011C9A0(u8 *a) {
    func_801229D4(a, 0);
    D_800BF9EB = 0;
    return 1;
}

extern u8 D_80139240_0000[];
extern u8 D_8012A3C0[];
void func_8011C9C8(u8 *a) {
    GameState *g;

    func_80051B04(M2C_FIELD(a, u8 **, 0xD0), 0x13, 0x10);
    func_80051B04(M2C_FIELD(a, u8 **, 0xDC), 0x13, 0x11);
    func_80040CDC(a, D_80139240_0000, D_8012A3C0);
    func_80041718(a, 0x2D, 0);
    M2C_FIELD(a, s16 *, 0x56) = 0xA00;
    func_80126C18(a);
    g = &D_800BF870;
    if (g->pad1[0xAB] == 0) {
        a[0x5E] = 0;
    } else if (g->pad1[0x28C] == 0) {
        a[0x5E] = 1;
    } else {
        a[0x5E] = 2;
    }
}

void func_8011CA78(void *arg0) {
    u8 temp_v1;

    func_80041098();
    func_8004190C(arg0);
    temp_v1 = M2C_FIELD(arg0, u8 *, 5);
    switch (temp_v1) {                              /* irregular */
    case 0:
        func_8011CB20(arg0);
        return;
    case 1:
        f_AdvanceStarvingCharlesDialogue(arg0);
        return;
    case 2:
        func_8011C710(arg0);
        return;
    case 3:
        func_8011CCD0(arg0);
        return;
    }
}

extern u8 D_800A3CD0[];
void func_8011CB20(u8 *a) {
    s32 k = a[0x2B];
    u8 *g;
    u8 *p;

    switch (k) {
    case 2:
        g = D_800BF808_1760;
        if ((*(u32 *)D_800BF808_1760 & 0xFFFF0000) != 0x85010000) {
            return;
        }
        p = func_8006FB0C(a, g[3]);
        M2C_FIELD(g, u8 **, 0x3C) = p;
        if (p != NULL) {
            p[0x5E] = 0;
        }
        a[6] = k;
    case 3:
        func_80042354(1, 3);
        func_80040D68(a, D_800A3CD0);
        a[0x70] = 1;
        a[5] = 1;
        break;
    }
}

extern u8 D_800BFAFD;
extern u8 D_8012A508[];
extern u8 D_8012A538[];
extern u8 *D_8012A568[];

void f_AdvanceStarvingCharlesDialogue(u8 *a) {
    s32 k;

    if (a[0x71] == 0xFF) {
        switch (k = a[6]) {
        case 0:
            if (D_800BFAFD != 0) {
                func_80040D68(a, D_8012A508);
                a[6]++;
                break;
            }
        case 1:
            func_80040D68(a, D_8012A568[a[0x5E]]);
            a[5] = 2;
            a[6] = 0;
            break;
        case 2:
            func_80040D68(a, D_8012A538);
            a[5] = 3;
            a[6] = 0;
            a[0x5E] = k;
            break;
        }
        a[0x70] = 1;
    }
}

void func_8011CCD0(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x71) == 0xFF) {
        func_8004D4F4(0x85, 1);
        M2C_FIELD(arg0, s8 *, 0x5E) = 1;
        M2C_FIELD(arg0, s8 *, 5) = 0;
    }
}

INCLUDE_ASM("asm/a02/nonmatchings/a02", f_RunTabbyHouseResidentConversation);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8011CE8C);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8011D390);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8011D4E8);

INCLUDE_ASM("asm/a02/nonmatchings/a02", f_UpdateTabbyHouseSceneController);

void func_8011DBD8(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 5);
    switch (temp_v1) {                              /* irregular */
    case 0:
        if (func_8007778C(arg0) != 0) {
            func_80076D68(arg0);
            if ((*(u8 *)0x1F800137 == 0) && (M2C_FIELD(arg0, u8 *, 0x2B) == 3)) {
                func_80042354(1, 1);
                M2C_FIELD(arg0, s8 *, 6) = 0;
                M2C_FIELD(arg0, u8 *, 5) = (u8) (M2C_FIELD(arg0, u8 *, 5) + 1);
                return;
            }
        }
        return;
    case 1:
        if (f_RunTabbyHouseResidentConversation(arg0) != 0) {
            M2C_FIELD(arg0, u8 *, 5) = 0U;
        }
        break;
    }
}

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8011DC88);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8011DE1C);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8011DF98);

extern u8 D_8012AD54[];
extern u8 D_8012AD64[];
extern u8 *D_8012AE64[];
void func_8011E2D8(u8 *a) {
    u8 *g;

    if (a[0x71] != 0xFF) {
        return;
    }
    if (M2C_FIELD(a, s16 *, 0x40) != 0) {
        g = (u8 *)&D_800BF870;
        if (g[0x91] == 0xFF) {
            a[0x5E] = 2;
            func_80040D68(a, D_8012AD54);
        } else if (g[0x28B] != 0) {
            a[0x5E] = 1;
            func_80040D68(a, D_8012AD64);
        } else {
            a[0x5E] = 0;
            func_80040D68(a, D_8012AD54);
        }
        M2C_FIELD(a, s16 *, 0x40) = 0;
    } else {
        func_80040D68(a, D_8012AE64[a[0x5E]]);
        a[5] = 2;
    }
    a[0x70] = 1;
}

void func_8011E3A8(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x71) == 0xFF) {
        M2C_FIELD(arg0, s8 *, 5) = 0;
        M2C_FIELD(arg0, s8 *, 6) = 0;
    }
}

extern u8 D_800E8008[];
extern u16 D_1F80017C;
s32 func_8011E3C8(u8 *a) {
    u8 *e = D_800E8008;

    switch (a[0x78]) {
    case 0:
        e[0x76] = 1;
        M2C_FIELD(a, s16 *, 0x40) = 0x5A;
        a[0x78]++;
    case 1:
        if (!(D_1F80017C & 7)) {
            func_80074590(0x86, 0, 0);
        }
        if (--M2C_FIELD(a, s16 *, 0x40) < 0) {
            e[0x76] = 0;
            return 1;
        }
        break;
    }
    return 0;
}

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8011E47C);

extern M2C_UNK D_800A3D18;
void func_8011E674(u8 *a) {
    if (a[0x2B] == 3) {
        func_80040D68(a, &D_800A3D18);
        a[0x70] = 1;
        func_80042354(1, 1);
        a[5] = 1;
    } else if (D_1F800137 == 0) {
        func_8011CE8C(a);
    }
}

extern void *D_8012AEFC[];
void func_8011E6EC(u8 *a) {
    if (a[0x71] == 0xFF) {
        func_80040D68(a, D_8012AEFC[a[0x5E]]);
        if (a[0x5E] == 3) {
            func_80041768(a, 0x13, 4);
        } else {
            func_80041768(a, 0xA, 4);
        }
        a[0x70] = 1;
        a[5] = 2;
    }
}

void func_8011E76C(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x71) == 0xFF) {
        if (M2C_FIELD(arg0, u8 *, 0x5E) == 0) {
            M2C_FIELD(arg0, u8 *, 0x5E) = 1U;
        }
        func_80041768(arg0, 0, 4);
        M2C_FIELD(arg0, s8 *, 5) = 0;
        M2C_FIELD(arg0, s8 *, 6) = 0;
    }
}

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8011E7C8);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8011EAD4);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8011ECC8);

void func_8011EF70(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x2B) == 3) {
        M2C_FIELD(arg0, s8 *, 0) = 2;
        M2C_FIELD(arg0, s8 *, 0x70) = 1;
        M2C_FIELD(arg0, s8 *, 5) = 1;
        return;
    }
    if (M2C_FIELD(arg0, u8 *, 0x5E) == 2) {
        func_8011CE8C();
    }
}

extern void *D_8012B370[];
void func_8011EFC8(u8 *a)
{
    if (a[0x71] == 0xFF) {
        func_80040D68(a, D_8012B370[a[0x5E]]);
        a[5] = 2;
        a[6] = 0;
        a[0x70] = 1;
    }
}

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8011F028);

s32 func_8011F10C(void *arg0) {
    D_800BF844 = M2C_FIELD(arg0, s32 *, 0x14);
    return 1;
}

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8011F120);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8011F23C);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8011F504);

extern u8 D_800BF80E;
extern u8 *D_800BF844_3cf3;
s32 func_8011F640(u8 *a) {
    u8 *p;

    switch (a[0x78]) {
    case 0:
        p = func_8006FB0C(a, 0x93);
        if (p != NULL) {
            func_800440E4(D_800E7E80, 0xCF, 2);
            D_800BF844_3cf3 = p;
            M2C_FIELD(p, s16 *, 0x60) = -0x10;
            p[0x5E] = 0;
            a[0x78]++;
        }
        break;
    case 1:
        if (D_800BF80E != 0) {
            return 1;
        }
        break;
    }
    return 0;
}

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8011F6EC);

extern M2C_UNK D_80139240;
void func_8011F8E0(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 4);
    switch (temp_v1) {                              /* irregular */
    case 0:
        func_80040CDC(arg0, &D_80139240, &D_800A3D18);
        func_80041718(arg0, 0, 0);
        M2C_FIELD(arg0, s8 *, 0x7B) = 0;
        M2C_FIELD(arg0, s16 *, 0x56) = 0xC00;
        M2C_FIELD(arg0, u8 *, 4) = (u8) (M2C_FIELD(arg0, u8 *, 4) + 1);
        return;
    case 1:
        func_8011F6EC(arg0);
        if (M2C_FIELD(arg0, u8 *, 1) != 0) {
            func_800518FC(arg0);
        }
        M2C_FIELD(arg0, s8 *, 0x2B) = 0;
        return;
    case 3:
        func_8007A624(arg0);
        /* fallthrough */
    case 2:
        return;
    }
}

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8011F9B4);

extern M2C_UNK func_8011D4E8;
void *func_8011FFFC(void) {
    void *temp_v0;

    temp_v0 = func_8007A980(3, 9, 0);
    M2C_FIELD(temp_v0, s8 *, 2) = 0x15;
    M2C_FIELD(temp_v0, s8 *, 3) = 7;
    M2C_FIELD(temp_v0, M2C_UNK **, 0x1C) = &func_8011D4E8;
    M2C_FIELD(temp_v0, s16 *, 0x2E) = 0x38A4;
    M2C_FIELD(temp_v0, s16 *, 0x32) = -0xD0C;
    M2C_FIELD(temp_v0, s16 *, 0x36) = 0x2D8A;
    M2C_FIELD(temp_v0, s32 *, 0x14) = func_801150EC(temp_v0);
    return temp_v0;
}

extern M2C_UNK D_8012B490;
extern M2C_UNK D_80139240;
void func_80120070(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 4);
    switch (temp_v1) {                              /* irregular */
    case 0:
        func_80040CDC(arg0, &D_80139240, &D_8012B490);
        func_80041718(arg0, 0x10, 0);
        M2C_FIELD(arg0, s8 *, 0x7B) = 0;
        M2C_FIELD(arg0, s16 *, 0x56) = 0x800;
        M2C_FIELD(arg0, u8 *, 4) = (u8) (M2C_FIELD(arg0, u8 *, 4) + 1);
        return;
    case 1:
        func_8011F9B4(arg0);
        if (M2C_FIELD(arg0, u8 *, 1) != 0) {
            func_800518FC(arg0);
        }
        M2C_FIELD(arg0, s8 *, 0x2B) = 0;
        return;
    case 3:
        func_8007A624(arg0);
        /* fallthrough */
    case 2:
        return;
    }
}

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80120144);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_801202DC);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_801203F0);

extern u8 D_8012B504[];
extern u8 D_8012B5C8[];
void func_80120564(u8 *a) {
    GameState *g;
    u8 s;

    if (a[0x2B] == 3) {
        func_80040D68(a, D_8012B504);
        a[0x70] = 1;
        func_80041768(a, 0, 8);
        func_80042354(1, 1);
        a[5] = 1;
    } else {
        g = &D_800BF870;
        s = g->pad1[0x19A];
        if (s == 2) {
            g->pad1[0x19A] = 0;
            func_80040D68(a, D_8012B5C8);
            a[0x70] = 1;
            a[0x5E] = 3;
            a[5] = s;
        }
    }
}

void func_80120610(u8 *a) {
    if (a[0x71] == 0xFF) {
        func_80040D68(a, D_8012B5BC[a[0x5E]]);
        func_80041768(a, 10, 4);
        a[0x70] = 1;
        a[5] = 2;
    }
}

void func_8012067C(u8 *a) {
    if (a[0x71] == 0xFF) {
        switch (a[0x5E]) {
        case 0:
            D_800BF870.pad1[0x90]++;
            a[0x5E]++;
            break;
        case 3:
            a[4] = 3;
            return;
        }
        func_80041768(a, 0, 4);
        a[5] = 0;
        a[6] = 0;
    }
}

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80120718);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80120848);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80120A3C);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80120BE0);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80120D1C);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80120F70);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80121268);

INCLUDE_ASM("asm/a02/nonmatchings/a02", f_UpdateGranActor);

s32 func_8012167C(void) {
    u8 *p = PLAYER;

    M2C_FIELD(p, s16 *, 0x58) += 0x190;
    if (M2C_FIELD(p, s16 *, 0x58) >= 0xC00) {
        M2C_FIELD(p, s16 *, 0x58) = 0xC00;
        return 1;
    }
    return 0;
}

s32 func_801216C0(void *arg0) {
    void *temp_v1;

    temp_v1 = M2C_FIELD(arg0, void **, 0x14);
    M2C_FIELD(temp_v1, u16 *, 0x50) = (u16) (M2C_FIELD(temp_v1, u16 *, 0x50) - 0x96);
    return 1;
}

extern s8 D_1F8000F2[];
extern void *D_800BF844_5c02;
s32 func_801216E0(s32 arg0) {
    u8 temp_v1;
    void *temp_a0;
    void *temp_v0;

    temp_v1 = M2C_FIELD(arg0, u8 *, 0x78);
    switch (temp_v1) {                              /* irregular */
    case 0:
        temp_v0 = func_8006FB0C(arg0, 0x17);
        M2C_FIELD(arg0, void **, 0x14) = temp_v0;
        D_800BF844_5c02 = temp_v0;
        temp_a0 = M2C_FIELD(arg0, void **, 0x14);
        if (temp_a0 != NULL) {
            M2C_FIELD(temp_a0, s16 *, 0x60) = 0x60;
            M2C_FIELD(temp_a0, s16 *, 0x62) = 0x78;
            M2C_FIELD(temp_a0, s8 *, 0x5E) = 1;
            M2C_FIELD(temp_a0, u8 *, 0x5F) = (u8) (M2C_FIELD(temp_a0, u8 *, 0x5F) | 1);
            M2C_FIELD(arg0, u8 *, 0x78) = (u8) (M2C_FIELD(arg0, u8 *, 0x78) + 1);
        }
        return 0;
    case 1:
        M2C_FIELD(M2C_FIELD(arg0, void **, 0x14), s16 *, 0x56) = (s16) (-(s32) *((u16 *)D_1F8000F2) & 0xFFF);
        return 1;
    default:
        return 0;
    }
}

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_801217A0);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80121948);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80121AA4);

extern void *D_8012C248[];
void func_80121BB4(u8 *a)
{
    if (a[0x71] == 0xFF) {
        func_80040D68(a, D_8012C248[a[0x5E]]);
        a[0x70] = 1;
        a[5] = 2;
    }
}

extern u8 D_800BF9DA;
void func_80121C10(u8 *a) {
    if (a[0x71] == 0xFF) {
        switch (a[0x5E]) {
        case 3:
            D_800BF9DA = 0;
        case 2:
            a[0x5E] += 2;
            break;
        case 0:
            a[0x5E] = 1;
            break;
        }
        a[5] = 0;
    }
}

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80121C74);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80121DA4);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80121ED8);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80122030);

void func_80122140(u8 *a) {
    if (a[0x71] == 0xFF) {
        func_80040D68(a, D_8012C580[a[0x5E]]);
        a[0x70] = 1;
        M2C_FIELD(a, s16 *, 0x40) = 1;
        a[5] = 2;
        a[6] = 0;
    }
}

s32 func_801221A8(void) {
    u8 *p = PLAYER;

    if (p != NULL) {
        p[5] = 1;
        M2C_FIELD(p, s16 *, 0x2E) = 0x22C4;
        M2C_FIELD(p, s16 *, 0x32) = -0xAF0;
        M2C_FIELD(p, s16 *, 0x60) = 0;
        M2C_FIELD(p, s16 *, 0x36) = 0x1EBE;
        return 1;
    }
    return 0;
}

void func_801221EC(void *arg0) {
    if (M2C_FIELD(arg0, s16 *, 0x40) != 0) {
        if (M2C_FIELD(M2C_FIELD(arg0, void **, 0x38), u16 *, 4) != 0) {
            func_80074590(0xA, -3, 0);
            M2C_FIELD(arg0, s16 *, 0x40) = 0;
        }
    } else if (M2C_FIELD(M2C_FIELD(arg0, void **, 0x38), u16 *, 4) == 0) {
        M2C_FIELD(arg0, s16 *, 0x40) = 1;
    }
}

void func_80122264(void *arg0) {
    if (M2C_FIELD(arg0, s16 *, 0x40) != 0) {
        if (M2C_FIELD(M2C_FIELD(arg0, void **, 0x38), u16 *, 2) != 0) {
            func_80074590(0x33, 0xC, 0);
            M2C_FIELD(arg0, s16 *, 0x40) = 0;
        }
    } else if (M2C_FIELD(M2C_FIELD(arg0, void **, 0x38), u16 *, 2) == 0) {
        M2C_FIELD(arg0, s16 *, 0x40) = 1;
    }
}

s32 func_801222DC(u8 *a) {
    u8 *g = D_800BF808_1760;

    M2C_FIELD(a, s16 *, 0x60) = g[3];
    switch (g[3]) {
    case 0x7B:
        a[0x5E] = 2;
        M2C_FIELD(a, s16 *, 0x60) = 0x66;
        break;
    case 0x78:
        a[0x5E] = 2;
        M2C_FIELD(a, s16 *, 0x60) = 0x67;
        break;
    case 0x7E:
        a[0x5E] = 2;
        M2C_FIELD(a, s16 *, 0x60) = 0x68;
        break;
    case 0x79:
        a[0x5E] = 4;
        break;
    case 0x7A:
        a[0x5E] = 5;
        break;
    case 0x77:
        a[0x5E] = 6;
        break;
    case 0x7C:
        a[0x5E] = 7;
        break;
    case 0x7D:
        a[0x5E] = 8;
        break;
    default:
        M2C_FIELD(a, s16 *, 0x60) = -1;
        return 0;
    }
    return 1;
}

s32 func_801223B4(u8 *a) {
    u8 *p = func_8006FB0C(a, M2C_FIELD(a, s16 *, 0x60));

    PLAYER = p;
    if (p != NULL) {
        p[0x5E] = 2;
        p[0x5F] |= 1;
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80122404);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_801225EC);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80122728);

extern M2C_UNK func_80122728;
void func_801229D4(s32 arg0, s8 arg1) {
    void *temp_v0;

    temp_v0 = func_8007A980(3, 9, 0);
    M2C_FIELD(temp_v0, s8 *, 2) = 0x1D;
    M2C_FIELD(temp_v0, s8 *, 3) = arg1;
    M2C_FIELD(temp_v0, M2C_UNK **, 0x1C) = &func_80122728;
    M2C_FIELD(temp_v0, u8 *, 0x28) = (u8) (M2C_FIELD(temp_v0, u8 *, 0x28) | 0x80);
}

extern u8 *D_1F800214;
s32 func_80122A28(u8 *a) {
    u8 *t = D_1F800214;
    s16 v[6];

    switch (a[0x78]) {
    case 0:
        v[1] = 0x24A4;
        v[3] = M2C_FIELD(t, s16 *, 0x32);
        v[5] = M2C_FIELD(t, s16 *, 0x36);
        func_80070F00(a, 1, v);
        func_800708B4(3);
        a[0x78]++;
        break;
    case 1:
        if (t[3] == 0) {
            return 1;
        }
        break;
    }
    return 0;
}

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80122AC4);

void func_80122EA8(u8 *a) {
    s16 v[6];
    s32 i;
    s32 s, c;

    i = 0;
    M2C_FIELD(a, s16 *, 0x56) = 0;
    do {
        i++;
        s = (func_80083F50(M2C_FIELD(a, s16 *, 0x56)) * 70) >> 12;
        c = func_80083E80(M2C_FIELD(a, s16 *, 0x56));
        M2C_FIELD(a, s16 *, 0x56) += 0x400;
        v[1] = M2C_FIELD(a, s16 *, 0x2E) + s;
        v[3] = M2C_FIELD(a, s16 *, 0x32);
        v[5] = M2C_FIELD(a, s16 *, 0x36) - ((c * 70) >> 12);
        func_8003116C(0, v, -0x5A);
    } while (i < 4);
}

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80122F6C);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8012328C);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80123470);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_801236C8);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8012383C);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_8012396C);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80123BB8);

extern s32 D_8012C914[];
void func_80123CD8(u8 *a) {
    if (a[0x71] == 0xFF) {
        func_80040D68(a, D_8012C914[a[0x5E]]);
        a[0x70] = 1;
        a[5] = 2;
        a[6] = 0;
    }
}

void func_80123D38(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x71) == 0xFF) {
        M2C_FIELD(arg0, s8 *, 5) = 0;
    }
}

void func_80123D54(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x71) == 0xFF) {
        func_8004D4F4(M2C_FIELD(arg0, s16 *, 0x60), 1);
        M2C_FIELD(arg0, s8 *, 5) = 0;
    }
}

extern s32 D_800BF844;
s32 func_80123D94(void) {
    D_800BF844 = 0;
    return 1;
}

void func_80123DA4(void *arg0) {
    if (M2C_FIELD(arg0, s16 *, 0x40) != 0) {
        if (M2C_FIELD(M2C_FIELD(arg0, void **, 0x38), u16 *, 2) != 0) {
            func_80074590(0x2E, -0xC, -0x28);
            M2C_FIELD(arg0, s16 *, 0x40) = 0;
        }
    } else if (M2C_FIELD(M2C_FIELD(arg0, void **, 0x38), u16 *, 2) == 0) {
        M2C_FIELD(arg0, s16 *, 0x40) = 1;
    }
}

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80123E1C);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80124138);

extern u16 *D_800ECF78;
void func_80124678(u8 *a)
{
    u16 *p = D_800ECF78;
    u16 t;

    *(u16 **)(a + 0xC) = p;
    *(u16 *)(a + 8) = p[0];
    t = p[1];
    a[7] = 0;
    *(u16 *)(a + 0xA) = t;
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

u32 *func_801246A4(u32 *f, u32 *ot, s32 n)
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
                        if (sz[3] > sz[4]) {
                            b = sz[5];
                            if (b < sz[3]) {
                                b = sz[3];
                            }
                            e = b;
                        } else {
                            b = sz[5];
                            if (b < sz[4]) {
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

u32 *func_8012496C(u32 *f, u32 *ot, s32 n)
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
extern void *D_800ED8C8_a098;
typedef struct {
    u8 pad0[6];
    u8 count;
    u8 pad7[5];
    u32 *tbl;
    u16 list[1];
} PartList;
void func_80124CB8(PartList *a)
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
    ot = D_800ED8C8_a098;
    tbl = a->tbl;
    gte_SetRotMatrix(D_1F8000F8);
    gte_SetTransMatrix(D_1F8000F8);
    for (; p < end; p++) {
        e = &tbl[*p];
        v = *e;
        r = func_801246A4(e + 1, ot, v & 0xFF);
        v >>= 16;
        func_8012496C(r, ot, v & 0xFF);
    }
}

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80124DB8);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80125100);

void func_8012555C(u32 *p, void *b)
{
    u32 lo = *p;
    u32 packed;

    packed = lo;
    lo = packed & 0xFFFF;
    p += 4;
    func_80125100(func_80124DB8(p, b, lo), b, packed >> 16);
}

extern u16 D_8012C928;
void func_801255A4(s32 arg0) {
    D_8012C928 = (D_8012C928 + arg0) & 0xFF;
}

extern u16 D_8012C92A;
extern u16 D_8012C92C;
void func_801255C0(s32 arg0) {
    u16 temp_a0;
    u16 temp_v0;
    u16 temp_v1;

    temp_v1 = D_8012C92A + arg0;
    D_8012C92A = temp_v1;
    if ((u32) (temp_v1 & 0xFFFF) >= 0x180U) {
        D_8012C92A = temp_v1 - 0x180;
    }
    temp_a0 = D_8012C92C;
    temp_v0 = temp_a0 + 0x100;
    D_8012C92C = temp_v0;
    if ((u32) (temp_v0 & 0xFFFF) >= 0x800U) {
        D_8012C92C = temp_a0 - 0x700;
    }
}

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80125618);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_801258A4);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80125C5C);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80125F7C);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80126240);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_801265AC);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80126968);

s32 func_80126C18(u8 *a) {
    s16 y = M2C_FIELD(a, s16 *, 0x32);
    s32 i;

    a[0x29] = 0;
    M2C_FIELD(a, s16 *, 0x32) = y - 0x80;
    for (i = 0; i < 200; i++) {
        if (func_8010A868(a) != 0) {
            a[0x29] = 0;
            return 1;
        }
        M2C_FIELD(a, s16 *, 0x32) += 0x20;
    }
    M2C_FIELD(a, s16 *, 0x32) = y;
    return 0;
}

extern u8 D_800BF818;
s32 func_80126C94(u8 *a) {
    u16 f;
    s16 g;

    switch (a[0x78]) {
    case 0:
        D_800BF818 = a[0x74];
        g = M2C_FIELD(a, s16 *, 0x76);
        f = M2C_FIELD(a, u16 *, 0x74);
        D_1F8001C6 = g;
        if (!(f & 1)) {
            return 1;
        }
        M2C_FIELD(a, s16 *, 0x72) = 0x10;
        a[0x78]++;
        break;
    case 1:
        if (--M2C_FIELD(a, s16 *, 0x72) == 0) {
            return 1;
        }
        break;
    }
    return 0;
}

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80126D24);

extern u8 D_80138990[];
typedef struct { u8 pad[0x48]; s16 r[3]; } RotAct;

void func_80126EA8(u8 *a)
{
    u8 *p;
    s32 k;
    switch (a[4]) {
    case 0:
        *(s32 *)(a + 0x50) = 0x100;
        *(s32 *)(a + 0x54) = 0x100;
        a[1] = 1;
        a[4] = 1;
        *(s16 *)(a + 0x48) = 0;
        *(s16 *)(a + 0x4A) = 0;
        *(s16 *)(a + 0x4C) = 0;
        *(s16 *)(a + 0x4E) = 0x78;
    case 1:
        p = *(u8 **)(a + 0x38);
        *(u8 **)(a + 0x34) = p;
        if (p == NULL) {
            *(u8 **)(a + 0x34) = D_80138990;
        }
        ((RotAct *)a)->r[0] += func_80083F50(D_1F80017C >> 7) >> 5;
        ((RotAct *)a)->r[1] += func_80083F50(D_1F80017C >> 4) >> 7;
        ((RotAct *)a)->r[2] += func_80083F50(D_1F80017C * 2) >> 6;
        a[1] = 1;
        break;
    case 2:
        switch (a[5]) {
        case 0:
            a[5] = 1;
        case 1:
            *(s32 *)(a + 0x50) -= 0x10;
            if (*(s32 *)(a + 0x50) < 0) {
                *(s32 *)(a + 0x50) = 0;
            }
            *(s32 *)(a + 0x54) += 0x80;
            if (++a[6] > 16) {
                a[4] = 3;
            }
            a[1] = 1;
            break;
        }
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

typedef struct {
    u32 tag;
    u32 rgbc;
    s16 x0, y0;
    u8 u0, v0;
    u16 clut;
    s16 x1, y1;
    u8 u1, v1;
    u16 tpage;
    s16 x2, y2;
    u8 u2, v2;
    u16 pad1;
    s16 x3, y3;
    u8 u3, v3;
    u16 pad2;
} AreaPolyFT4;
extern u32 *D_800ED8C8;
AreaPolyFT4 *func_80127034(AreaPolyFT4 *p, s32 x, s32 y, s32 w, s32 h, s16 c, s16 cy) {
    u32 rgbc;
    u16 clut;
    s16 x0, x1;

    if (c <= 0) return p; {
        rgbc = ((c | 0x2E00) << 16) | ((c << 8) | c);
        clut = ((cy + 0x1F0) << 6) | 0x17;
        x0 = x - w;
        x1 = x + w;
        p->u0 = p->u2 = 0xB9;
        p->u1 = p->u3 = 0xE7;
        p->v0 = p->v1 = 0x51;
        p->v2 = p->v3 = 0x67;
        *(u32 *)((u8 *)p + 4) = rgbc;
        p->tpage = 0x35;
        p->clut = clut;
        p->x0 = p->x2 = x0;
        p->x1 = p->x3 = x1;
        p->y0 = p->y1 = y - h;
        p->y2 = p->y3 = y;
        p->tag = D_800ED8C8[4] | 0x09000000;
        D_800ED8C8[4] = (u32)p;
        p++;
        p->u0 = p->u2 = 0xB9;
        p->u1 = p->u3 = 0xE7;
        p->v0 = p->v1 = 0x67;
        p->v2 = p->v3 = 0x51;
        *(u32 *)((u8 *)p + 4) = rgbc;
        p->tpage = 0x35;
        p->clut = clut;
        p->x0 = p->x2 = x0;
        p->x1 = p->x3 = x1;
        p->y0 = p->y1 = y;
        p->y2 = p->y3 = y + h;
        p->tag = D_800ED8C8[4] | 0x09000000;
        D_800ED8C8[4] = (u32)p;
        return p + 1;
    }

}

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80127170);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80127678);

#define gte_ldfcdir(r0, r1, r2) __asm__ volatile("ctc2	%0, $21;" "ctc2	%1, $22;" "ctc2	%2, $23" : : "r"(r0), "r"(r1), "r"(r2))
extern s32 D_1F800090[];
extern u8 D_801386BC[];
extern u8 D_80138794[];
void func_80127784(u8 *a) {
    s32 *d;
    s32 t;

    d = D_1F800090;
    gte_ldfcdir(0, 0, 0);
    t = M2C_FIELD(a, u16 *, 0x4A) + 0x400;
    *d = M2C_FIELD(a, s32 *, 0x58);
    M2C_FIELD(a, s16 *, 0x4A) = t;
    func_800318A0(a + 0x2C, a + 0x50, a + 0x48);
    M2C_FIELD(a, s16 *, 0x4A) -= 0x400;
    func_80027768(D_801386BC, 0, -0x14, M2C_FIELD(a, s32 *, 0x5C));
    if (a[0x2B] != 0) {
        func_800318A0(a + 0x2C, a + 0x50, a + 0x48);
        func_80027768(D_80138794, 0, -0x14, M2C_FIELD(a, s32 *, 0x5C));
    }
}

extern u8 D_8013886C[];
void func_80127860(u8 *p) {
    u8 c[4];
    s32 *d;

    c[0] = c[1] = c[2] = p[0x56];
    d = D_1F800090;
    gte_ldfcdir(0, 0, 0);
    *d = 0;
    func_800318A0(p + 0x2C, c, p + 0x48);
    func_80027768(D_8013886C, 0, -0x32, M2C_FIELD(p, s16 *, 0x50));
}

typedef struct { u8 pad[0xC0]; u8 *parts[1]; } PartsOwner;
typedef struct { s16 v[4]; } PartInit;
extern s16 D_800ED098;
extern PartInit D_80138A08[];

s32 func_801278D8(PartsOwner *a)
{
    s32 i;
    u8 *q;

    a->pad[8] = 2;
    if (D_800ED098 < a->pad[8]) {
        a->pad[4] = 3;
        return 1;
    }
    a->pad[9] = 2;
    a->pad[0xD] = 0;
    a->pad[0x18] = 0xFF;
    a->pad[0x19] = 0xFF;
    a->pad[0x1A] = 0xFF;
    a->pad[0xB] = 0;
    *(s16 *)(a->pad + 0x54) = 0;
    *(s16 *)(a->pad + 0x56) = 0;
    *(s16 *)(a->pad + 0x58) = 0;
    for (i = 0; i < a->pad[9]; i++) {
        q = func_8007AAE8();
        a->parts[i] = q;
        *(s16 *)(q + 6) = D_80138A08[i].v[0];
        *(s16 *)(a->parts[i] + 0) = D_80138A08[i].v[1];
        *(s16 *)(a->parts[i] + 2) = D_80138A08[i].v[2];
        *(s16 *)(a->parts[i] + 4) = D_80138A08[i].v[3];
        *(s16 *)(a->parts[i] + 8) = 0;
        *(s16 *)(a->parts[i] + 0xA) = 0;
        *(s16 *)(a->parts[i] + 0xC) = 0;
        func_80051B04(a->parts[i], 0xC, i + 0x35);
    }
    a->pad[6] = 0;
    a->pad[8] = 1;
    a->pad[0x2B] = 0;
    return 0;
}

INCLUDE_ASM("asm/a02/nonmatchings/a02", f_UpdateBlastTheRockSequence);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80127EDC);

INCLUDE_ASM("asm/a02/nonmatchings/a02", func_80128034);

INCLUDE_ASM("asm/a02/nonmatchings/a02", f_UpdateTabbyHouseResidentActor);

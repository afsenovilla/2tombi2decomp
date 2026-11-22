#include "common.h"
#include "game.h"
#include "m2c.h"

extern s8 D_800BF808_c1f7[];
extern u8 D_1F800137;
extern s32 D_1F80009C;
typedef struct { u8 pad[0x60]; s32 unk60; s32 unk64; } AreaStateF58;
typedef struct { u8 pad0[7]; u8 unk7; u8 pad8[6]; u8 unkE; u8 unkF; u8 pad10[0x21]; u8 unk31; s16 unk32; } AreaState808_E;
typedef struct { u8 pad[0xC0]; u8 *parts[1]; } AreaPartsOwner;
typedef struct { s16 unk0; s16 x, y, z; } PartPose;
typedef struct { u8 pad[0x5E]; u8 pose; u8 pad2[0xC0 - 0x5F]; s16 *parts[3]; } PosedActor;
typedef struct { s16 x, y, w, h; } ClutRect;
typedef struct {
    u8 *ptr;
    u8 *clut;
    s16 x;
    s16 y;
} ClutCycle;
typedef struct { s16 x, y, z, pad; } RingVec;
typedef struct { s16 pos; s16 vel; } RiseMotion;

void func_8010A51C(u8 *a, u8 *b) {
    s32 t, u;

    if (D_1F800137 != 0 || D_800BF808_c1f7[5] != 0) {
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
        D_800BF808_c1f7[0x39] = 1;
    }
}

#define F16(p, o) M2C_FIELD(p, s16 *, o)
#define FU16(p, o) M2C_FIELD(p, u16 *, o)
extern s8 D_800BF80D;
extern u8 D_1F800182;
#define F16(p, o) M2C_FIELD(p, s16 *, o)
#define FU16(p, o) M2C_FIELD(p, u16 *, o)
extern u8 D_1F800182;

void func_8010A670(u8 *a, u8 *b) {
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
        D_1F800182 = 0;
    } else if (!(func_8001E860(a, b, 0, 0) & 0x80)) {
        D_1F800182 = 0;
    }
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8010A83C);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8010A9A8);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8010ABB0);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8010AE10);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8010AF38);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8010B104);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8010B1E8);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8010B328);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8010B598);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8010B9FC);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8010BDE4);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8010BF50);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8010C0BC);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8010C22C);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8010C378);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8010C538);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8010C90C);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8010CD84);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8010CED8);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8010D334);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8010D9AC);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8010DAF0);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8010DC80);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8010DEB4);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8010E080);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8010E2A4);

extern u8 **D_1F80013C;
extern u8 D_1F800144;
extern u8 D_1F800183;
extern u8 D_1F800182;
extern u8 D_1F800182;
extern u8 D_1F800182;
extern u8 D_1F800182;

void func_8010E420(void)
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
            for (D_1F800182 = D_1F800183; D_1F800182 != 0; D_1F800182--) {
            }
        }
    }
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8010E4CC);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8010E7C0);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8010EA88);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8010ED98);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8010EF9C);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8010F110);

extern u16 D_800BF812;

void func_8010F214(u8 *p)
{
    u16 h = D_800BF812;

    if (!(p[0x145] & 1) && !(*(s16 *)(p + 0x32) < (s16)h - *(s16 *)(p + 0x62))) {
        *(s16 *)(p + 0x32) = h - *(s16 *)(p + 0x62);
        func_80022C78(p);
        p[0x29] |= 0x80;
    }
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8010F288);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8010F35C);


s32 func_8010F3D8(s32 arg0, s32 arg1) {
    return func_8010B598(arg0, arg1, M2C_FIELD(arg1, s32 *, 0xC0));
}

extern u8 D_1F800182;
extern u8 D_1F800182;

void func_8010F3FC(u8 *a, u8 *b)
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
        D_1F800182 = 0;
    }
}


void func_8010F47C(void) {
    func_8010BDE4();
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8010F49C);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8010F590);

extern u8 D_800BFAD7;

void func_8010F614(u8 *a, u8 *b)
{
    if (func_80022F04(a, b) != 0) {
        if (b[3] == 0 || D_800BFAD7 == 0) {
            a[0x2B] = *(s32 *)0x1F80009C >> 4;
            func_80022D08(a, b, 1, 0);
        }
        b[0] = 2;
        b[4] = 2;
        b[5] = 2;
        b[6] = 0;
    }
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8010F6A4);


void func_8010F790(void *a0, u8 *a1)
{
    if (a1[0x5E] == 0) {
        func_8002192C(a0, a1, 0);
    }
}


void func_8010F7C0(void *a0, u8 *a1)
{
    s32 v = a1[3];

    if (v < 6) {
        if (v != 0) {
            func_800216B4(a0, a1, 0);
        }
    }
}

extern u8 D_1F800150;
extern u8 D_1F800182;
extern u8 **D_1F80013C;
extern u8 D_1F800144;
typedef struct {
    u8 x0;
    u8 pad1;
    s16 x2;
} S4;
typedef struct {
    s16 x0;
    s16 x2;
    u8 pad4[6];
} S10;
typedef struct {
    s16 v[3];
} S16x3;
typedef struct {
    u8 x[8];
} S8;

void func_8010F7FC(void *a0)
{
    u8 **list;
    u8 *e;

    for (D_1F800182 = D_1F800150; D_1F800182 != 0; D_1F800182--) {
    }
    list = D_1F80013C;
    D_1F800182 = D_1F800144;
    while (D_1F800182 != 0) {
        e = *list++;
        D_1F800182--;
        if ((e[0] & 1) && e[2] == 8) {
            func_8002423C(a0, e);
        }
    }
}

extern u8 **D_1F80014C;
extern u8 D_1F800152;
extern s32 D_1F800080;

s32 func_8010F8D4(u8 *a)
{
    u8 **l = D_1F80014C;
    u8 *p;
    D_1F800182 = D_1F800152;
    while (D_1F800182 != 0) {
        p = *l;
        D_1F800182--;
        l++;
        if ((p[0] & 1) && p[2] == 0x58) {
            func_8010D9AC(a, p);
        }
    }
    return D_1F800080;
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8010F98C);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8010FB44);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8010FF9C);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_801100F4);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80110AA0);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_801114B8);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_801120C4);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80112238);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80112418);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_801125E4);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80112970);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80112BCC);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80112F84);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80113190);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8011332C);


void func_801135C8(void) {
    func_801100F4();
}


void func_801135E8(void) {
    func_80110AA0();
}


void func_80113608(void) {
    func_801114B8();
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80113628);


s32 func_801136C4(u8 *a)
{
    u8 *b = *(u8 **)(a + 0x158);

    if (b[0xC] != 4) {
        return 0;
    }
    if (b[2] != 0x58) {
        return 0;
    }
    return func_80112F84(a, b);
}

extern u16 D_1F8001A4;

void func_8011370C(u8 *a)
{
    s16 v[8];

    v[1] = *(u16 *)(a + 0x2E);
    v[3] = D_1F8001A4;
    v[5] = *(u16 *)(a + 0x36);
    func_800312D4(0x909, v, -0xA);
    v[3] += 0x50;
    func_800312D4(0x90A, v, -0xA);
    func_80074590(7, 0, 0);
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80113780);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8011399C);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80113AD8);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80113DDC);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80114118);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_801144D4);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80114A70);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80114B90);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80114C1C);

extern s8 D_1F800138[];
extern s8 D_1F80019B[];

void func_80114C78(void) {
    func_80045258(M2C_FIELD(*((volatile void **)D_1F800138), u8 *, 0x6E), 0xF);
    *((volatile s8 *)D_1F80019B) = 1;
    func_80051FB4();
}

extern s8 D_1F800138[];
extern s8 D_1F80019B[];

void func_80114CB8(void) {
    func_80045258(M2C_FIELD(*((volatile void **)D_1F800138), u8 *, 0x6E), 8);
    *((volatile s8 *)D_1F80019B) = 1;
    func_80051FB4();
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", f_SpawnWaterTempleSceneActorsFromPlacementTable);

extern ClutCycle D_80142EA8[];
extern s8 D_801485CC[];
extern u8 D_800BF873;

void func_801152F0(s32 arg0) {
    ClutRect r;
    s32 i;
    ClutCycle *e;
    u8 *data;

    if (arg0 == 0) {
        s8 *p;
        i = 24;
        p = &D_801485CC[i];
        do {
            *p-- = 0;
        } while (--i >= 0);
        return;
    }
    if (D_800BF873) {
        return;
    }
    e = D_80142EA8;
    for (i = 0; i < 25; i++, e++) {
        if (--D_801485CC[i] <= 0) {
            if (e->ptr[0] == 0xFF) {
                e->ptr -= e->ptr[1];
            }
            data = e->clut + e->ptr[0] * 32;
            D_801485CC[i] = e->ptr[1];
            r.x = e->x;
            r.y = e->y;
            r.w = 16;
            r.h = 1;
            func_80081218(&r, data);
            e->ptr += 2;
        }
    }
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80115428);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_801155D4);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8011597C);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80115AEC);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80115BE0);

INCLUDE_ASM("asm/a08/nonmatchings/a08", f_UpdateWaterTempleQuestItemPickupActor);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_801161C4);

extern s8 D_800BFA33;
void func_80116254(void *arg0) {
    func_8004D4C4(0x9E, 1);
    func_8004B0D8(arg0);
    D_800BFA33 = 2;
    M2C_FIELD(arg0, s8 *, 4) = 3;
}

void f_UpdateWaterTempleQuestItemPickupActor();

s32 func_8011629C(u8 *a)
{
    u8 *p = func_80072DDC(a, 1, 5, 3);

    if (p == NULL) {
        return 0;
    }
    *(void **)(p + 0x1C) = f_UpdateWaterTempleQuestItemPickupActor;
    p[3] = 0;
    p[5] = 1;
    *(s16 *)(p + 0x2E) = *(s16 *)(*(u8 **)(a + 0xD4) + 0x2C);
    *(s16 *)(p + 0x32) = *(s16 *)(*(u8 **)(a + 0xD4) + 0x30);
    *(s16 *)(p + 0x36) = *(s16 *)(*(u8 **)(a + 0xD4) + 0x34);
    return 1;
}

extern s32 D_800ECF80;
extern u8 D_801486EC[];

void func_80116330(u8 *a) {
    a[0xB] = 0x10;
    a[0x47] = 0;
    M2C_FIELD(a, s16 *, 0x5A) = 0;
    M2C_FIELD(a, s16 *, 0x5C) = 0;
    a[0xD] = 0;
    M2C_FIELD(a, s32 *, 0x3C) = D_800ECF80;
    func_80077B38(a, D_801486EC, 16);
    a[0] = 1;
    M2C_FIELD(a, s16 *, 0x80) = 0x14;
    M2C_FIELD(a, s16 *, 0x82) = 0x28;
    M2C_FIELD(a, s16 *, 0x84) = 0x14;
    M2C_FIELD(a, s16 *, 0x86) = 0x28;
    func_8004B354(a, 0);
}


void func_801163B0(s32 arg0) {
    if (func_8007778C() != 0) {
        func_8004B374(arg0, 0);
    }
}


void func_801163E4(void *arg0) {
    if (func_80040B48(0x2B) >= 0) {
        func_8004D4C4(0x27, 1);
        func_8004B0D8(arg0);
    }
    M2C_FIELD(arg0, s8 *, 4) = 3;
}

void func_80116430(u8 *a) {
    a[0xB] = 0x10;
    a[0x47] = 0;
    M2C_FIELD(a, s16 *, 0x5A) = 0;
    M2C_FIELD(a, s16 *, 0x5C) = 0;
    a[0xD] = 0;
    M2C_FIELD(a, s32 *, 0x3C) = D_800ECF80;
    func_80077B38(a, D_801486EC, 1);
    M2C_FIELD(a, s16 *, 0x68) = 0xA1;
    a[0] = 1;
    M2C_FIELD(a, s16 *, 0x80) = 0x28;
    M2C_FIELD(a, s16 *, 0x82) = 0x50;
    M2C_FIELD(a, s16 *, 0x84) = 0x28;
    M2C_FIELD(a, s16 *, 0x86) = 0x50;
    M2C_FIELD(a, s16 *, 0x60) = M2C_FIELD(a, s16 *, 0x32);
    func_8004B354(a, 0);
}


void func_801164C0(void *arg0) {
    u16 temp_a0;

    func_8007778C();
    temp_a0 = (M2C_FIELD(arg0, u16 *, 0x40) + 0x40) & 0xFFF;
    M2C_FIELD(arg0, u16 *, 0x40) = temp_a0;
    M2C_FIELD(arg0, s16 *, 0x32) = (s16) (M2C_FIELD(arg0, u16 *, 0x60) + (func_80083E80(temp_a0) >> 8));
    func_8004B374(arg0, 0);
}


void func_80116518(void *arg0) {
    func_8004A3D4();
    D_800BF870.pad1[0x1CE] |= 0x40;
    M2C_FIELD(arg0, s8 *, 4) = 3;
}

void func_8011655C(u8 *a) {
    a[0xB] = 0x10;
    a[0x47] = 0;
    M2C_FIELD(a, s16 *, 0x5A) = 0;
    M2C_FIELD(a, s16 *, 0x5C) = 0;
    a[0xD] = 0;
    M2C_FIELD(a, s32 *, 0x3C) = D_800ECF80;
    func_80077B38(a, D_801486EC, 7);
    M2C_FIELD(a, s16 *, 0x68) = 0xA5;
    a[0] = 1;
    M2C_FIELD(a, s16 *, 0x80) = 0x28;
    M2C_FIELD(a, s16 *, 0x82) = 0x50;
    M2C_FIELD(a, s16 *, 0x84) = 0xA;
    M2C_FIELD(a, s16 *, 0x86) = 0x14;
    func_8004B354(a, 0);
}


void func_801165EC(s32 arg0) {
    func_8007778C();
    func_8004B374(arg0, 0);
}


void func_8011661C(void *arg0) {
    if (func_80040B48(0x89) >= 0) {
        func_8004A3D4(arg0);
        D_800BF870.pad1[0xCC] |= 0x80;
    }
    M2C_FIELD(arg0, s8 *, 4) = 3;
}

void func_80116674(u8 *a) {
    a[0xB] = 0x10;
    a[0x47] = 0;
    M2C_FIELD(a, s16 *, 0x5A) = 0;
    M2C_FIELD(a, s16 *, 0x5C) = 0;
    a[0xD] = 0;
    M2C_FIELD(a, s32 *, 0x3C) = D_800ECF80;
    func_80077B38(a, D_801486EC, 3);
    M2C_FIELD(a, s16 *, 0x68) = 0xA3;
    a[0x2A] = 0x1A;
    M2C_FIELD(a, s16 *, 0x80) = 0x64;
    M2C_FIELD(a, s16 *, 0x82) = 0xC8;
    M2C_FIELD(a, s16 *, 0x84) = 0x28;
    M2C_FIELD(a, s16 *, 0x86) = 0x50;
    func_8004B354(a, 0);
}

extern u8 D_1F800207;
void func_8012485C();
extern u8 D_800BF8DF;

void func_80116704(u8 *p)
{
    func_8007778C(p);
    if (D_1F800207 == 0x1A) {
        p[0] = 1;
    } else {
        p[0] = 2;
    }
    func_8004B374(p, 0);
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80116750);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80116904);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80116D3C);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80116F70);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80117198);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8011731C);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80117628);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80117920);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80117E84);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80118374);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80118514);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_801187F4);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80118CC4);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8011920C);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80119578);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8011973C);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_801198CC);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80119A48);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80119C84);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80119EC4);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8011A0F8);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8011A7E8);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8011AD6C);

#define W(p, o) M2C_FIELD(p, u32 *, o)
typedef struct {
    u8 b[6][4];
} FlickerTbl;
extern FlickerTbl D_80109B60;

void func_8011B124(u8 *a) {
    FlickerTbl t = D_80109B60;

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


s32 func_8011B344(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    void *temp_v0;

    temp_v0 = func_8003116C(0x917, arg0, (s16) arg1);
    if (temp_v0 != NULL) {
        M2C_FIELD(temp_v0, s16 *, 0x50) = (s16) arg2;
        M2C_FIELD(temp_v0, s16 *, 0x54) = (s16) arg3;
    }
    return (s32) temp_v0;
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8011B398);

#define gte_ldfcdir(r0, r1, r2) __asm__ volatile("ctc2	%0, $21;" "ctc2	%1, $22;" "ctc2	%2, $23" : : "r"(r0), "r"(r1), "r"(r2))
extern s32 D_1F800090[];
void f_UpdateWaterTempleQuestPropActor();

void func_8011B4A8(u8 *p)
{
    u8 buf[0x30];
    s32 *d;
    s32 v, a, b;

    func_800318A0(p + 0x2C, p + 0x50, p + 0x48);
    d = D_1F800090;
    gte_ldfcdir(0, 0, 0);
    v = *(s32 *)(p + 0x54);
    a = *(s32 *)(p + 0x3C);
    b = *(s16 *)(p + 0x32);
    *d = v;
    func_80027768(a, 0, b, p[0x29]);
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8011B510);

void func_8011B5EC(u8 *p)
{
    u8 buf[0x30];
    s32 *d;
    s32 v, a, b;

    func_800318A0(p + 0x2C, p + 0x50, p + 0x48);
    d = D_1F800090;
    gte_ldfcdir(0, 0, 0);
    v = *(s32 *)(p + 0x54);
    a = *(s32 *)(p + 0x3C);
    b = *(s16 *)(p + 0x32);
    *d = v;
    func_80027768(a, 0, b, p[0x29]);
}

typedef struct {
    s16 a;
    s16 b;
    s16 c;
    s16 d;
} SV;
extern u8 D_800A1CD4[];
extern u8 D_80144C10[];
extern s32 D_1F800090_3460;
extern u8 D_800BF808[];

void func_8011B654(u8 *p)
{
    SV v;

    v.a = *(s16 *)(p + 0x2E);
    v.b = *(s16 *)(p + 0x32);
    v.c = *(s16 *)(p + 0x36);
    func_800318A0(&v, D_800A1CD4, p + 0x54);
    D_1F800090_3460 = 0;
    func_80027768(D_80144C10, 0, -0xA, p[0x60]);
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8011B6C0);

void func_8011B7E4(u8 *p) {
    s32 *d = D_1F800090;
    s32 i;

    gte_ldfcdir(0, 0, 0);
    *d = 0;
    for (i = 0; i < 4; i++) {
        func_80031AC4(p + 0x2C, p + 0x50, p + 0x48);
        func_80027768(M2C_FIELD(p, s32 *, 0x3C), 0, M2C_FIELD(p, s16 *, 0x32), 0);
        M2C_FIELD(p, s16 *, 0x4E) += 0x400;
    }
    func_80027CB4(p);
}

void func_8011B878(u8 *a)
{
    u32 v;
    switch (a[4]) {
    case 0:
        *(s16 *)(a + 0x32) = -330;
        a[4] = 1;
        a[5] = 0;
    case 1:
        v = a[5];
        a[1] = 1;
        if (v < 36) {
            a[5] = v + 1;
        }
        break;
    case 2:
    case 3:
        func_8007A624(a);
        break;
    }
}

extern RingVec D_80148668[];

void func_8011B900(void) {
    s32 i;
    s32 ang;
    RingVec *p;

    p = D_80148668;
    for (i = 0; i < 15; i++, p++) {
        ang = (i << 12) / 15;
        p->x = func_80083F50(ang) >> 4;
        p->y = 0;
        p->z = func_80083E80(ang) >> 4;
    }
    p->x = D_80148668[0].x;
    p->y = D_80148668[0].y;
    p->z = D_80148668[0].z;
}

void func_8011B9D0(u8 *a) {
    RiseMotion *m = (RiseMotion *)(a + 0x50);

    switch (a[4]) {
    case 0:
        m->pos = 20;
        a[4] = 1;
        m->vel = 10;
        M2C_FIELD(m, s16 *, 4) = 200;
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

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8011BA90);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8011BB40);

#define AREA_gte_ldv0(r0) __asm__ volatile("lwc2	$0, 0( %0 );" "lwc2	$1, 4( %0 )" : : "r"(r0))
typedef struct { s16 x, y, z, pad; } AreaSVec;
extern u8 D_80143D48[];
extern s32 D_80143D44;
extern s32 D_1F800084;
extern s32 D_1F800088;

void func_8011BC14(u8 *a) {
    AreaSVec v;
    u8 *p;
    s32 r, k;

    p = M2C_FIELD(a, u8 **, 0x78);
    if (p == NULL) {
        p = D_80143D48;
    }
    func_800329E0(6);
    v.x = M2C_FIELD(a, s16 *, 0x2E);
    v.y = M2C_FIELD(a, s16 *, 0x32);
    v.z = M2C_FIELD(a, s16 *, 0x36);
    AREA_gte_ldv0(&v);
    if (func_800317CC(-10) == 0) {
        D_1F800088 = D_1F800084;
        r = func_8009A450();
        k = D_80143D44;
        r &= 0x7FF;
        D_1F800090_3460 = r;
        M2C_FIELD(a, u8 **, 0x78) = func_80027A4C(p, k);
    }
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8011BCC8);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8011BD98);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8011BF0C);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8011BFA8);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8011C0C0);

typedef struct { u8 pad[0x48]; s32 unk48; } AreaState808;
extern s8 D_1F80017C[];
typedef struct { s16 x, y, z; } AreaVec3s;
extern AreaVec3s D_8014527C[];

void func_8011C148(u8 *a) {
    s16 i;

    switch (a[6]) {
    case 0:
        if (--M2C_FIELD(a, s16 *, 0x40) <= 0) {
            a[6]++;
        }
        break;
    case 1:
        if (!(*(u16 *)D_1F80017C & 0xF)) {
            M2C_FIELD(a, s16 *, 0xB8) = D_8014527C[M2C_FIELD(a, s16 *, 0x7A)].x;
            M2C_FIELD(a, s16 *, 0xBA) = D_8014527C[M2C_FIELD(a, s16 *, 0x7A)].y;
            M2C_FIELD(a, s16 *, 0xBC) = D_8014527C[M2C_FIELD(a, s16 *, 0x7A)].z;
            M2C_FIELD(a, s16 *, 0x7A) = (M2C_FIELD(a, s16 *, 0x7A) + 1) & 7;
        }
        break;
    }
    if ((s16)func_8011CC48(a)) {
        func_8011CB58(a, 0);
        a[5] = 3;
        a[6] = 0;
        M2C_FIELD(a, s16 *, 0x6C) = 0;
    }
}

#define F16(p, o) M2C_FIELD(p, s16 *, o)
#define C0(p) M2C_FIELD(p, u8 **, 0xC0)
#define F16(p, o) M2C_FIELD(p, s16 *, o)
#define C0(p) M2C_FIELD(p, u8 **, 0xC0)

void func_8011C260(u8 *a)
{
    s16 s = F16(a, 0x76);
    u8 *g;

    switch (s) {
    case 0:
        if (a[0x2B] == 0) {
            return;
        }
        F16(a, 0x76)++;
        break;
    case 1:
        if (a[0x2B] & 0x80) {
            F16(a, 0x48) = F16(a, 0x4C) = 0x200;
            g = D_800BF808;
            if (M2C_FIELD(g, s32 *, 0x50) == 0) {
                func_8004CBD8(a, 0);
                M2C_FIELD(g, s32 *, 0x50) = s;
            }
        } else {
            F16(a, 0x48) = F16(a, 0x4C) = 0x180;
        }
        F16(a, 0x52) = -8;
        if (func_80077768(a[0x46] << 4, F16(a, 0x56), 1)) {
            F16(a, 0x4C) = -F16(a, 0x4C);
            F16(a, 0x52) = -F16(a, 0x52);
        }
        a[0x2B] = 0;
        a[0x5F] = 1;
        if (a[1]) {
            func_80074590(0xF, -5, 0);
        }
        F16(a, 0x76)++;
        break;
    case 2:
        F16(C0(a), 0xC) += F16(a, 0x4C);
        if (F16(C0(a), 0xC) < -F16(a, 0x48) || F16(a, 0x48) < F16(C0(a), 0xC)) {
            if (F16(a, 0x4C) > 0) {
                F16(C0(a), 0xC) = F16(a, 0x48);
            } else {
                F16(C0(a), 0xC) = -F16(a, 0x48);
            }
            F16(a, 0x48) -= 0x18;
            if (F16(a, 0x48) <= 0) {
                F16(C0(a), 0xC) = 0;
                F16(a, 0x76) = 0;
                break;
            }
            if (F16(a, 0x48) <= 0xA0) {
                a[0x5F] = 0;
            }
            F16(a, 0x4C) = -F16(a, 0x4C);
            F16(a, 0x52) = -F16(a, 0x52);
        }
        F16(a, 0x4C) += F16(a, 0x52);
        if (F16(a, 0x4C) > 0 && F16(a, 0x4C) < 0x60) {
            F16(a, 0x4C) = 0x60;
        } else if (F16(a, 0x4C) < 0) {
            if (F16(a, 0x4C) > -0x60) {
                F16(a, 0x4C) = -0x60;
            }
        }
        break;
    }
    if (a[0x2B]) {
        F16(a, 0x76) = 1;
    }
}

extern u8 D_800E7E80[];

void func_8011C4BC(u8 *a)
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
            if (M2C_FIELD(a, s16 *, 0x6C) != 0) {
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
            func_8011CB58(a, a[0x5E]);
            a[6] = 1;
            M2C_FIELD(a, s16 *, 0x6C) = 1;
        }
    } else if ((s16)func_8011CC48(a)) {
        M2C_FIELD(*(u8 **)(a + 0xC0), u16 *, 0x38) = M2C_FIELD(a, s16 *, 0x64);
        M2C_FIELD(*(u8 **)(a + 0xC0), u16 *, 0x3A) = M2C_FIELD(a, s16 *, 0x66);
        func_8011CB58(a, 0);
        a[6] = 0;
        M2C_FIELD(a, s16 *, 0x6C) = 0;
    }
    if (M2C_FIELD(a, s16 *, 0x50) > 0x20) {
        M2C_FIELD(a, s16 *, 0x50)--;
    }
    func_8011CCAC(a);
}

void func_8011C754(void *arg0) {
    u8 temp_v1;
    u8 temp_v1_2;

    temp_v1 = M2C_FIELD(arg0, u8 *, 4);
    switch (temp_v1) {                              /* switch 1; irregular */
    case 0:                                         /* switch 1 */
        func_8011C890(arg0);
        return;
    case 1:                                         /* switch 1 */
        func_8007778C(arg0);
        if (D_800BF873 == 0) {
            temp_v1_2 = M2C_FIELD(arg0, u8 *, 5);
            switch (temp_v1_2) {                    /* switch 2; irregular */
            case 0:                                 /* switch 2 */
                func_8011C148(arg0);
                break;
            case 3:                                 /* switch 2 */
                func_8011C4BC(arg0);
                break;
            case 4:                                 /* switch 2 */
                func_8011C974(arg0);
                break;
            }
            func_8011CA98(arg0);
            func_8011C260(arg0);
            M2C_FIELD(arg0, s8 *, 0x29) = 0;
        }
        if (M2C_FIELD(arg0, u8 *, 1) != 0) {
            func_800518FC(arg0);
            return;
        }
        return;
    case 2:                                         /* switch 1 */
        func_8011C9C4(arg0);
        return;
    case 3:                                         /* switch 1 */
        func_8007A624(arg0);
        break;
    }
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8011C890);


void func_8011C974(u8 *a)
{
    if (a[0x29] == 0) {
        func_8011CB58(a, 1);
        a[5] = 3;
        a[6] = 1;
        *(s16 *)(a + 0x6C) = 1;
    }
}

void func_8011C9C4(u8 *a) {
    func_80027144(M2C_FIELD(M2C_FIELD(a, u8 **, 0xC0), s32 *, 0x40), a + 0x2C, 0xA00, -0x7FDC);
    func_80074590(0xC, 0, 0);
    M2C_FIELD(a, s16 *, 0x32) -= 0x96;
    func_80027144(M2C_FIELD(M2C_FIELD(a, u8 **, 0xC0), s32 *, 0x40), a + 0x2C, 0xA00, 0x2C);
    func_80074590(0xC, 0, 0);
    if (func_80040B48(0x7F) >= 0) {
        D_800BF870.pad1[0x15C] |= 2;
        if (++D_800BF870.pad1[0x1C0] >= 10) {
            func_8004ED94(0x6E, 0x41);
        }
    }
    a[4] = 3;
}

void func_8011CA98(u8 *a)
{
    switch (F16(a, 0x78)) {
    case 1:
        F16(C0(a), 0xC) += F16(C0(a), 0x14);
        F16(C0(a), 0x14) -= 8;
        if (F16(C0(a), 0x14) < -0x20) {
            F16(a, 0x78) = 0;
            F16(C0(a), 0xC) = 0;
        }
        break;
    case 2:
        F16(C0(a), 0xC) -= F16(C0(a), 0x14);
        F16(C0(a), 0x14) -= 8;
        if (F16(C0(a), 0x14) < -0x20) {
            F16(a, 0x78) = 0;
            F16(C0(a), 0xC) = 0;
        }
        break;
    }
    if (a[0x2B]) {
        F16(a, 0x78) = 0;
        F16(C0(a), 0xC) = 0;
    }
}

void func_8011CB58(u8 *a, s16 b)
{
    s32 v = (F16(a, 0x62) << 5) + 0x30;

    F16(a, 0x4E) = v;
    F16(a, 0x50) = v;
    switch (b) {
    case 0:
        F16(a, 0x4A) = 0x10;
        F16(a, 0x74) = F16(a, 0x66) - (F16(a, 0x66) >> 4);
        F16(a, 0x40) = F16(a, 0x66) >> 5;
        break;
    case 1:
        F16(a, 0x74) = F16(a, 0x66);
        F16(a, 0x40) = F16(a, 0x66) >> 5;
        F16(a, 0x40) += F16(a, 0x66) >> 6;
        F16(a, 0x4A) = 0x20;
        break;
    case 2:
        F16(a, 0x74) = F16(a, 0x66);
        F16(a, 0x40) = F16(a, 0x66) >> 3;
        F16(a, 0x4E) += 0x70;
        F16(a, 0x50) += 0x70;
        F16(a, 0x4A) = 0x40;
        break;
    }
}


s32 func_8011CC48(u8 *a)
{
    s16 v;

    if (a[0x29] != 0) {
    if (*(s16 *)(a + 0x78) == 0) {
        v = *(s16 *)(a + 0x44);
        if (v > 0) {
            *(s16 *)(a + 0x78) = 1;
            *(s16 *)(*(u8 **)(a + 0xC0) + 0x14) = 0x20;
        } else if (v < 0) {
            *(s16 *)(a + 0x78) = 2;
            *(s16 *)(*(u8 **)(a + 0xC0) + 0x14) = 0x20;
        }
    }
    return 1;
    }
    return 0;
}


void func_8011CCAC(void *arg0) {
    s32 temp_v0_2;
    u32 temp_v0;

    temp_v0 = (u16) M2C_FIELD(M2C_FIELD(arg0, void **, 0xC0), u16 *, 0x38) >> 5;
    M2C_FIELD(arg0, s16 *, 0x80) = (s16) temp_v0;
    M2C_FIELD(arg0, s16 *, 0x82) = (s16) (temp_v0 * 2);
    temp_v0_2 = (s32) (M2C_FIELD(M2C_FIELD(arg0, void **, 0xC0), u16 *, 0x3A) * 0x113) >> 0xC;
    M2C_FIELD(arg0, s16 *, 0x84) = (s16) temp_v0_2;
    M2C_FIELD(arg0, s16 *, 0x86) = (s16) (temp_v0_2 * 2);
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8011CD00);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8011CEA4);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8011D144);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8011D3A0);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8011D458);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8011D798);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8011DAA4);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8011DE38);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8011DFA4);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8011E1BC);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8011E438);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8011E608);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8011E884);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8011EBA8);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8011ECE4);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8011EE7C);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8011F030);

INCLUDE_ASM("asm/a08/nonmatchings/a08", f_UpdateWaterTempleEntranceAndDoorActor);


void func_8011FC88(u8 *p)
{
    u8 *s = D_800BF808;
    s16 x, z;

    if (s[0xE] && s[0xF] == p[3]) {
        x = *(s16 *)(p + 0x88) + 0x163;
        z = *(s16 *)(p + 0x8C) + 0xB2;
    } else {
        x = *(s16 *)(p + 0x88);
        z = *(s16 *)(p + 0x8C);
    }
    *(s16 *)(p + 0x2E) = x;
    *(s16 *)(p + 0x36) = z;
    func_80073328(p);
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8011FCF4);


void func_8011FD74(void *arg0) {
    if (M2C_FIELD(arg0, s16 *, 0x66) == 0) {
        func_8011DE38();
        func_8011D798(arg0);
    } else {
        func_8011DAA4(arg0);
    }
    func_800735F4(arg0, 0x7E);
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8011FDD0);

extern u8 D_800E7FF4;
void func_8011FECC(s32 arg0) {
    if (D_800E7FF4 & 4) {
        func_80073328();
    }
    func_800735F4(arg0, 0x67);
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8011FF10);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8011FF9C);

void func_80122544();

void func_80120068(void *a0)
{
    u8 *r = func_80072DDC(a0, 1, 4, 0x4F);

    if (r) {
        *(void **)(r + 0x1C) = func_80122544;
        r[3] = 2;
    }
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_801200AC);


void func_801201C4(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 0x5E);
    switch (temp_v1) {                              /* irregular */
    case 0:
        func_8011EE7C(arg0);
        break;
    case 1:
        func_8011F030(arg0);
        break;
    }
    M2C_FIELD(arg0, s8 *, 1) = 1;
    func_80077EBC(arg0);
}

extern PartPose D_80145400[3];
extern PartPose D_80145418[3];

void func_8012022C(PosedActor *a, s32 b, s32 c) {
    s32 i;

    for (i = 0; i < 3; i++) {
        if (b == 0) {
            func_80051B04(a->parts[i], c, i);
            a->parts[i][0] = D_80145400[i].x;
            a->parts[i][1] = D_80145400[i].y;
            a->parts[i][2] = D_80145400[i].z;
        } else {
            func_80051B04(a->parts[i], c, i + 3);
            a->parts[i][0] = D_80145418[i].x;
            a->parts[i][1] = D_80145418[i].y;
            a->parts[i][2] = D_80145418[i].z;
        }
    }
    a->pose = b;
}

extern u8 D_8001B7B0[];
void D_8004C930();

void func_80120338(u8 *a, s32 b) {
    u16 v;
    u8 *p;

    switch (a[5]) {
    case 0:
        if (a[0x29] == 1) {
            a[5]++;
            func_8012022C(a, 0, b);
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

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_801205F8);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80120848);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80120998);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80120BC8);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80121040);


s32 func_80121110(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x452) == 0xFF) {
        D_800BF870.pad1[0x3B] = 1;
        D_800BF870.pad1[0x1DE] |= 1;
    }
    if (M2C_FIELD(arg0, u8 *, 0x4FA) == 0xFF) {
        D_800BF870.pad1[0x3C] = 1;
        D_800BF870.pad1[0x1DE] |= 2;
    }
    if (M2C_FIELD(arg0, u8 *, 0x449) == 0xFF) {
        D_800BF870.pad1[0x3D] = 1;
        D_800BF870.pad1[0x1DE] |= 4;
    }
    if (M2C_FIELD(arg0, u8 *, 0x44E) == 0xFF) {
        D_800BF870.pad1[0x3E] = 1;
        D_800BF870.pad1[0x1DE] |= 8;
    }
    return 1;
}


void func_801211BC(u8 *p, u8 *a, u8 *b)
{
    u8 n, m;
    s32 i;

    m = n = 0;
    for (i = 0; i < 0x100; i++) {
        u8 v = (p + i)[0x444];
        if (v != 0) {
            n++;
            if (v == 0xFF) {
                m++;
            }
        }
    }
    *a = n;
    *b = m;
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80121208);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_801214FC);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80121AD8);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80121C2C);

void func_8013DDD4();

void func_80122064(void)
{
    u8 *r = func_80072DDC(0, 1, 2, 0xCE);

    if (r) {
        *(void **)(r + 0x1C) = func_8013DDD4;
        *(s16 *)(r + 0x2E) = 0x445C;
        *(s16 *)(r + 0x32) = -0x1529;
        *(s16 *)(r + 0x36) = 0x1040;
    }
}

void f_UpdateWaterTempleQuestPropActor();
extern s16 D_801459AC[];
extern u8 *D_800BF844;

void func_801220BC(void)
{
    u8 *r = func_80072DDC(0, 1, 3, 0x10);

    if (r) {
        *(void **)(r + 0x1C) = f_UpdateWaterTempleQuestPropActor;
        r[3] = 0x11;
    }
}


s32 func_80122104(u8 *p)
{
    *(s16 *)(p + 0x42) = 0x1E;
    if (*(s16 *)(p + 0x32) == -0xEC0) {
        p[0x5E] = 1;
    } else {
        *(s16 *)(p + 0x32) += 8;
        if (*(s16 *)(p + 0x32) < -0xEC0) {
            return 0;
        }
        *(s16 *)(p + 0x32) = -0xEC0;
        p[0x5E] = 1;
        func_80074590(0x1A, -8, 0);
    }
    return 1;
}

extern s32 D_800BF850;
extern u8 D_8014549C[];

s32 func_8012217C(u8 *p)
{
    s32 s = p[6];
    u8 *g;

    switch (s) {
    case 0:
        if (p[0x29] == 0) {
            break;
        }
        p[6] = 1;
        g = D_800E7E80;
        func_80054198(g);
        *(s16 *)(g + 0x2E) = *(u16 *)(p + 0x2E);
        *(s16 *)(g + 0x36) = *(u16 *)(p + 0x36);
        D_800BF850 = 1;
        func_80042354(1, 2);
        return 0;
    case 1:
        p[6] = 2;
        func_80040CDC(p, 0, D_8014549C);
        p[0x70] = s;
        break;
    case 2:
        func_80041098(p);
        if (p[0x70] != 0xFF) {
            return 0;
        }
        p[6] = 0;
        func_80042310();
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", f_InsertPigNosePanelIntoTempleTower);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80122544);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8012282C);

extern u8 D_800BFA3F;
void func_80122938(void *arg0) {
    M2C_FIELD(arg0, s8 *, 1) = 1;
    func_80077EBC();
    if (D_800BFA3F & 0x20) {
        func_80027144(M2C_FIELD(M2C_FIELD(arg0, void **, 0xC0), s32 *, 0x40), arg0 + 0x2C, 0x800, 8);
        M2C_FIELD(arg0, s8 *, 4) = 3;
    }
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80122998);

void func_80122998();

void func_80122C70(u8 *a0)
{
    u8 *r = func_80072DDC(a0, 1, 4, 0x53);

    if (r) {
        *(void **)(r + 0x1C) = func_80122998;
        r[3] = a0[3];
    }
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80122CC0);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80123028);

INCLUDE_ASM("asm/a08/nonmatchings/a08", f_UpdateWaterTempleMechanismActor);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_801237A0);


s32 func_8012388C(void *arg0) {
    M2C_FIELD(arg0, u8 *, 0x47) = (u8) M2C_FIELD(arg0, u8 *, 0x72);
    return 1;
}


s32 func_801238A0(void *arg0) {
    u16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, u16 *, 0xBA) - 0x60;
    M2C_FIELD(arg0, u16 *, 0xBA) = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        M2C_FIELD(arg0, u16 *, 0xBA) = 0U;
        return 1;
    }
    return 0;
}

void f_UpdateWaterTempleMechanismActor();
extern u8 D_800BF809;

u8 *func_801238D0(void *a0, u8 a1)
{
    u8 *r = func_8007A980(1, 4, 0);

    if (r == 0) {
        return 0;
    }
    r[2] = 0x54;
    r[3] = a1;
    *(void **)(r + 0x1C) = f_UpdateWaterTempleMechanismActor;
    *(void **)(r + 0x10) = a0;
    r[0x28] |= 0x80;
    return r;
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80123940);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80123A48);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80123AE4);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80123BF0);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80123D10);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80123E60);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80124074);


s32 func_80124128(void *arg0) {
    s16 temp_v0;
    s16 temp_v0_2;
    s32 var_v0;
    void *temp_a0;
    void *temp_a0_2;

    if (M2C_FIELD(arg0, u8 *, 0x29) != 0) {
        temp_a0 = M2C_FIELD(arg0, void **, 0xC8);
        if (M2C_FIELD(temp_a0, s16 *, 2) < -0x1C0) {
            temp_v0 = (u16) M2C_FIELD(temp_a0, s16 *, 2) + 8;
            M2C_FIELD(temp_a0, s16 *, 2) = temp_v0;
            var_v0 = 1;
            if (temp_v0 >= -0x1C0) {
                func_80074590(0x1A, 0xA, 0);
                M2C_FIELD(M2C_FIELD(arg0, void **, 0xC8), s16 *, 2) = -0x1C0;
                goto block_5;
            }
            /* Duplicate return node #10. Try simplifying control flow for better match */
            return var_v0;
        }
        M2C_FIELD(arg0, s16 *, 0x40) = 0xF;
block_5:
        return 1;
    }
    temp_a0_2 = M2C_FIELD(arg0, void **, 0xC8);
    var_v0 = 0;
    if (M2C_FIELD(temp_a0_2, s16 *, 2) >= -0x1FF) {
        temp_v0_2 = (u16) M2C_FIELD(temp_a0_2, s16 *, 2) - 8;
        M2C_FIELD(temp_a0_2, s16 *, 2) = temp_v0_2;
        if (temp_v0_2 < -0x1FF) {
            func_80074590(0x1A, 0x10, -0x1E);
            M2C_FIELD(M2C_FIELD(arg0, void **, 0xC8), s16 *, 2) = -0x200;
        }
        var_v0 = 0;
    }
    return var_v0;
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80124210);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80124600);

extern s16 D_1F800160;
extern s16 D_1F800164;
extern u8 D_800BF8E2;
void func_80137C5C();

s32 func_80124698(u8 *p)
{
    s32 dx = D_1F800160 - *(s16 *)(p + 0x2E);
    s32 dz = D_1F800164 - *(s16 *)(p + 0x36);

    return func_80084080(dx * dx + dz * dz);
}

void func_801246F0(u8 *a) {
    switch (a[4]) {
    case 0:
        func_80051B70(a, 0xC, 0x68);
        M2C_FIELD(a, s16 *, 0x80) = 0x40;
        M2C_FIELD(a, s16 *, 0x82) = 0x80;
        M2C_FIELD(a, s16 *, 0x86) = 0x40;
        a[0] = 1;
        M2C_FIELD(a, s16 *, 0x84) = 0;
        M2C_FIELD(a, s16 *, 0xBA) = 0x800;
        a[4]++;
        break;
    case 1:
        if (func_8013900C(a)) {
            func_80051844(a);
        }
        break;
    case 2:
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

void func_801246F0();

s32 func_801247C4(u8 *a)
{
    u8 *p = func_80072DDC(a, 1, 4, 0x58);

    if (p != NULL) {
        *(void **)(p + 0x1C) = func_801246F0;
        p[3] = a[3];
        p[0x2A] = a[0x2A];
        *(s16 *)(p + 0x2E) = *(s16 *)(a + 0x7C);
        *(s16 *)(p + 0x32) = *(s16 *)(a + 0x32);
        *(s16 *)(p + 0x36) = *(s16 *)(a + 0x7E);
        *(s16 *)(p + 0x56) = *(s16 *)(a + 0x60);
        *(s16 *)(p + 0x54) = 0;
        *(s16 *)(p + 0x58) = 0;
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8012485C);


u8 *func_80124A48(void *a0)
{
    u8 *r = func_80072DDC(a0, 1, 4, 0x59);

    if (r) {
        *(void **)(r + 0x1C) = func_8012485C;
        r[0x5E] = 0;
        r[0x28] |= 0x80;
    }
    return r;
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80124A94);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80124C14);

void func_80124DEC(u8 *a, s32 b) {
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
    if (func_80124C14(a, b) != 0) {
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

#define FU16(p, o) M2C_FIELD(p, u16 *, o)
#define FU16(p, o) M2C_FIELD(p, u16 *, o)
extern u8 D_800BF841;
extern u8 D_800E806E;
extern u16 D_1F8000D6;

void func_80124F48(u8 *a) {
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

extern u8 D_1F800236;

void func_80125190(u8 *a) {
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
        D_800BF808[0x31] = 1;
        F16(D_800BF808, 0x32) = a[0xBF] << 4;
        break;
    }
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_801253A8);

extern ClutCycle D_8014579C[];
extern s8 D_801486E8[];

void func_8012579C(s32 arg0) {
    ClutRect r;
    s32 i;
    ClutCycle *e;
    u8 *data;

    if (arg0 == 0) {
        for (i = 0; i < 1; i++) {
            D_801486E8[i] = 0;
        }
        return;
    }
    e = D_8014579C;
    for (i = 0; i < 1; i++, e++) {
        if (--D_801486E8[i] <= 0) {
            if (e->ptr[0] == 0xFF) {
                e->ptr -= e->ptr[1];
            }
            data = e->clut + e->ptr[0] * 32;
            D_801486E8[i] = e->ptr[1];
            r.x = e->x;
            r.y = e->y;
            r.w = 16;
            r.h = 1;
            func_80081218(&r, data);
            e->ptr += 2;
        }
    }
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_801258BC);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80125B10);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80125D88);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80125F6C);

INCLUDE_ASM("asm/a08/nonmatchings/a08", f_UpdateWaterTempleInteriorEnvironmentActor);

extern u8 D_800BF8F5;
extern u8 D_800BF80F;
extern u8 D_8014597C[];

void func_801267D4(u8 *a)
{
    s32 s = a[5];
    s32 r;

    switch (s) {
    case 0:
        if (D_800BF8F5 == 0xFF) {
            a[5] = 2;
        } else {
            a[5] = 1;
        }
        break;
    case 1:
        switch (a[6]) {
        case 0:
            if (D_800BF80F != 0) {
                r = 0;
                goto done;
            }
            a[6] = s;
            func_80042354(1, 2);
            func_80040CDC(a, 0, D_8014597C);
            a[0x70] = s;
            break;
        case 1:
            func_80041098(a);
            if (a[0x70] != 0xFF) {
                r = 0;
                goto done;
            }
            a[6] = 0;
            func_80042310();
            r = 1;
            goto done;
        default:
            r = 0;
            goto done;
        }
        r = 0;
    done:
        if (r) {
            a[5]++;
        }
        break;
    case 2:
        break;
    }
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_801268D8);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80126AD8);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80126C68);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80126E24);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_801273B4);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_801277E0);

typedef struct { u8 pad[0xC0]; u8 *parts[1]; } PartsOwner;
typedef struct { s16 v[4]; } PartInit;
extern s16 D_800ED098;
extern PartInit D_801459C4[];
extern u8 D_800BF922;

void func_801279DC(PartsOwner *a)
{
    s32 i;
    u8 *q;

    a->pad[8] = 2;
    if (D_800ED098 < a->pad[8]) {
        a->pad[4] = 3;
        return;
    }
    a->pad[9] = 2;
    a->pad[0xD] = 4;
    a->pad[0xB] = 0;
    for (i = 0; i < a->pad[8]; i++) {
        q = func_8007AAE8();
        a->parts[i] = q;
        *(s16 *)(q + 6) = D_801459C4[i].v[0];
        *(s16 *)(a->parts[i] + 0) = D_801459C4[i].v[1];
        *(s16 *)(a->parts[i] + 2) = D_801459C4[i].v[2];
        *(s16 *)(a->parts[i] + 4) = D_801459C4[i].v[3];
        *(s16 *)(a->parts[i] + 8) = 0;
        *(s16 *)(a->parts[i] + 0xA) = 0;
        *(s16 *)(a->parts[i] + 0xC) = 0;
        func_80051B04(a->parts[i], 0xC, i + 0x55);
        a->parts[i][0x3F] = 8;
    }
    *(s16 *)(a->pad + 0x56) = 0x400;
    *(s16 *)(a->pad + 0x54) = 0;
    *(s16 *)(a->pad + 0x58) = 0;
    if (D_800BF922 == 0xFF) {
        a->pad[5] = 2;
        *(s16 *)(a->parts[1] + 8) = -0x700;
    }
}

extern PartInit D_801459D4[];

void func_80127B34(PartsOwner *a)
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
    a->pad[0xB] = 0;
    for (i = 0; i < a->pad[8]; i++) {
        q = func_8007AAE8();
        a->parts[i] = q;
        *(s16 *)(q + 6) = D_801459D4[i].v[0];
        *(s16 *)(a->parts[i] + 0) = D_801459D4[i].v[1];
        *(s16 *)(a->parts[i] + 2) = D_801459D4[i].v[2];
        *(s16 *)(a->parts[i] + 4) = D_801459D4[i].v[3];
        *(s16 *)(a->parts[i] + 8) = 0;
        *(s16 *)(a->parts[i] + 0xA) = 0;
        *(s16 *)(a->parts[i] + 0xC) = 0;
        func_80051B04(a->parts[i], 0xC, i + 0x64);
    }
    *(s16 *)(a->pad + 0x54) = 0;
    *(s16 *)(a->pad + 0x56) = 0x400;
    *(s16 *)(a->pad + 0x58) = 0;
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80127C58);

INCLUDE_ASM("asm/a08/nonmatchings/a08", f_UpdateWaterTempleQuestPropActor);


void func_80128BF8(u8 *p)
{
    func_80051B70(p, 0xC, D_801459AC[p[3]]);
    func_800517F8(p);
}

extern u16 D_1F8000E2;
s32 func_800778E4(void *, s16);
s32 func_80128C40(u8 *a0)
{
    return func_800778E4(a0, D_1F8000E2 - *(u16 *)(a0 + 0x32));
}

extern u8 D_800BFA31;

void func_80128C78(u8 *p)
{
    u8 v = D_800BFA31;

    if (v < 4) {
        func_80051B70(p, 0xC, 0x13);
    } else if (v < 7) {
        func_80051B70(p, 0xC, 0x14);
    } else {
        func_80051B70(p, 0xC, 0x15);
    }
    func_800517F8(p);
}

s32 func_80128CE4(u8 *a0)
{
    return func_800778E4(a0, D_1F8000E2 - *(u16 *)(a0 + 0x32));
}

void f_UpdateWaterTempleQuestPropActor();

u8 *func_80128D1C(void *a0)
{
    u8 *r = func_80072DDC(a0, 0x80, 3, 0x10);

    if (r) {
        *(void **)(r + 0x1C) = f_UpdateWaterTempleQuestPropActor;
        r[3] = 5;
    }
    return r;
}


void func_80128D60(u8 *p)
{
    *(s32 *)(p + 0x3C) = D_800ECF80;
    func_80077B38(p, D_801486EC, 0x9);
    p[0xB] = 0x10;
    *(s16 *)(p + 0x5C) = 0;
    *(s16 *)(p + 0x5A) = 0;
    p[0x47] = 0;
    p[8] = 0xF0;
}

extern u8 D_800BFA4E;
void func_80128DB8(void *arg0) {
    void *temp_v1;

    temp_v1 = M2C_FIELD(arg0, void **, 0x10);
    if (D_800BFA4E == 1) {
        func_8004D4C4(0x54, 1);
        func_8004B0D8(arg0);
        M2C_FIELD(arg0, s8 *, 4) = 3;
        return;
    }
    func_8004BD64(arg0, 0, M2C_FIELD(temp_v1, s32 *, 0xD8), M2C_FIELD(temp_v1, s32 *, 0xCC), 0);
    M2C_FIELD(arg0, s8 *, 1) = 1;
}


void func_80128E30(u8 *p)
{
    func_80051B70(p, 0xC, 0x20);
    if (D_800BF8E2 == 0xFF) {
        p[5] = 10;
    } else {
        *(s16 *)(p + 0x2E) = 0x3FC;
        *(s16 *)(p + 0x36) = 0x7F0;
    }
}


void func_80128E88(u8 *p)
{
    if (D_800BF8E2 == 0xFF) {
        p[4] = 3;
    } else {
        func_80051B70(p, 0xC, 0x21);
    }
}


void func_80128EC8(u8 *p)
{
    if (D_800BF8E2 == 0xFF) {
        p[4] = 3;
    } else {
        func_80051B70(p, 0xC, 0x22);
    }
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80128F08);


void func_80128FA4(u8 *p)
{
    func_80051B70(p, 0xC, 0x1F);
    func_800517F8(p);
    if (D_800BF8DF == 0xFF) {
        p[5] = 1;
    }
}

extern u8 D_800BFA3A;

void func_80128FF0(u8 *p)
{
    switch (p[5]) {
    case 0:
        if (D_800BFA3A >= 0xB) {
            p[5] = 1;
        }
        break;
    case 1:
        p[1] = 1;
        func_800517F8(p);
        break;
    }
}

void D_8004C930();

u8 *func_80129050(u8 *a) {
    u8 *p = func_80072DDC(a, 0, 5, 4);

    if (p != NULL) {
        M2C_FIELD(p, void **, 0x1C) = D_8004C930;
        M2C_FIELD(p, s16 *, 0x2E) = M2C_FIELD(a, u16 *, 0x2E);
        M2C_FIELD(p, s16 *, 0x32) = M2C_FIELD(a, u16 *, 0x32) - M2C_FIELD(a, s16 *, 0x84) / 2;
        M2C_FIELD(p, s16 *, 0x36) = M2C_FIELD(a, u16 *, 0x36);
        p[3] = 39;
    }
    return p;
}

extern u8 D_800BFB22;
extern M2C_UNK D_801459BC;
void func_801290DC(void *arg0) {
    if ((D_800BFB22 != 0) || (D_800ED098 < 2)) {
        M2C_FIELD(arg0, s8 *, 4) = 3;
        return;
    }
    func_80051B70(arg0, 0xC, 0x4D);
    func_801268D8(arg0, &D_801459BC, 4, 0xC, 0x4E);
    M2C_FIELD(arg0, s8 *, 0) = 1;
    M2C_FIELD(arg0, s16 *, 0x80) = 0xF8;
    M2C_FIELD(arg0, s16 *, 0x82) = 0x1F0;
    M2C_FIELD(arg0, s16 *, 0x84) = 0x220;
    M2C_FIELD(arg0, s16 *, 0x86) = 0x220;
    M2C_FIELD(arg0, s8 *, 0x29) = 0;
    M2C_FIELD(arg0, s8 *, 0x5F) = 0;
    func_8004766C(arg0);
    func_80048750(arg0);
    M2C_FIELD(arg0, u16 *, 0x60) = (u16) *(u16 *)0x1F8001A0;
    func_800517F8(arg0);
    M2C_FIELD(arg0, s32 *, 0x10) = func_8003116C(0x90B, arg0 + 0x2C, -0x20);
}


u8 *func_801291BC(void *a0)
{
    u8 *r = func_80072DDC(a0, 1, 3, 0x10);

    if (r) {
        *(void **)(r + 0x1C) = f_UpdateWaterTempleQuestPropActor;
        r[3] = 0xB;
        r[0x28] |= 0x80;
    }
    return r;
}

extern u8 D_800BF871;

void func_8012920C(u8 *p)
{
    if (func_80051B70(p, 0xC, 0x6C) == 0) {
        *(s16 *)(p + 0x56) = 0xACD;
        *(s16 *)(p + 0x58) = 0xC5C;
        *(s16 *)(p + 0x2E) = 0x224D;
        *(s16 *)(p + 0x32) = -0x1580;
        *(s16 *)(p + 0x54) = 0;
        *(s16 *)(p + 0x36) = 0x325E;
    }
}

extern u8 D_800BF816;
void func_80129268(void *arg0) {
    if (D_800BF816 == 0) {
        M2C_FIELD(arg0, s8 *, 4) = 3;
        return;
    }
    if (func_8007778C(arg0) != 0) {
        func_800517F8(arg0);
    }
}


void func_801292B8(void *a)
{
    if (func_80051B70(a, 0xC, 0x2B) == 0) {
        func_800517F8(a);
    }
}


void func_801292F4(void *arg0) {
    M2C_FIELD(arg0, s8 *, 1) = 1;
}


void func_80129300(u8 *p)
{
    if (func_80051B70(p, 0xC, 0x58) == 0) {
        p[0xD] |= 4;
        (*(u8 **)(p + 0xC0))[0x3F] = 0x1E;
        p[0] = 1;
        *(s16 *)(p + 0x80) = 0x78;
        *(s16 *)(p + 0x82) = 0xF0;
        *(s16 *)(p + 0x84) = 0x1C0;
        *(s16 *)(p + 0x86) = 0x1C0;
        func_800517F8(p);
    }
}


void func_80129374(void) {
    func_8007778C();
}


void func_80129394(void *arg0) {
    M2C_FIELD(arg0, s16 *, 0x2E) = 0x40C9;
    M2C_FIELD(arg0, s16 *, 0x32) = -0xEB8;
    M2C_FIELD(arg0, s16 *, 0x36) = 0x10ED;
}

extern u8 D_800BF928;

void func_801293B0(u8 *p)
{
    if (func_80051B70(p, 0xC, 0x57) == 0) {
        if (D_800BF928 == 0xFF) {
            p[5] = 1;
            *(s16 *)(p + 0x2E) = 0x40C9;
            *(s16 *)(p + 0x32) = -0xEB8;
            *(s16 *)(p + 0x36) = 0x10ED;
        } else {
            p[5] = 0;
        }
        *(s16 *)(p + 0x54) = 0;
        *(s16 *)(p + 0x56) = 0;
        *(s16 *)(p + 0x58) = 0;
    }
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80129424);

extern s16 D_1F800162;

void func_801294B4(s16 a0)
{
    u8 *r = func_80072DDC(0, 0, 3, 0x10);

    if (r) {
        *(void **)(r + 0x1C) = f_UpdateWaterTempleQuestPropActor;
        r[3] = 0x12;
        *(s16 *)(r + 0x60) = a0;
    }
}

typedef struct {
    u8 pad0[0x4E];
    s16 x4E;
    u8 pad50[6];
    s16 x56;
    u8 pad58[0x14];
    s16 x6C;
    s16 x6E;
    u8 pad70[0x4E];
    u8 xBE;
} T4814;
typedef struct {
    s16 pad0;
    s16 a;
    s16 pad4;
    s16 b;
    s16 pad8;
    s16 c;
} S13AE38;

void func_80129508(u8 *p)
{
    *(s32 *)(p + 0x3C) = D_800ECF80;
    func_80077B38(p, D_801486EC, 0xC);
    p[0xD] = 0;
    *(s16 *)(p + 0x5C) = 0;
    p[0xB] = 0x10;
    *(s16 *)(p + 0x5A) = 0;
    p[0x47] = 0;
}

extern u8 D_800BFA32;
void func_8012955C(void *arg0) {
    if (((s32) D_800BFA32 >> M2C_FIELD(arg0, s16 *, 0x60)) & 1) {
        M2C_FIELD(arg0, s8 *, 4) = 3;
        return;
    }
    M2C_FIELD(arg0, s8 *, 1) = 1;
    func_8004DAEC(arg0);
    M2C_FIELD(arg0, u16 *, 0x2E) = (u16) (M2C_FIELD(arg0, u16 *, 0x2E) + 0x20);
}

extern s8 D_800BF93E;

void func_801295C4(u8 *a) {
    if (func_80051B70(a, 0xC, 0x6B) == 0) {
        M2C_FIELD(a, s16 *, 0x56) = 0x4FC;
        M2C_FIELD(a, s16 *, 0x58) = 0;
        M2C_FIELD(a, s16 *, 0x54) = 0;
        M2C_FIELD(a, s16 *, 0x40) = 0;
        M2C_FIELD(a, s32 *, 0x10) = 0;
        if (*(u8 *)&D_800BF93E == 0xFF) {
            a[5] = 10;
            a[0xD] |= 4;
            M2C_FIELD(a, u8 **, 0xC0)[0x3F] = 0xF6;
        }
    }
}


u8 *func_8012963C(void *a0)
{
    u8 *r = func_80072DDC(a0, 1, 3, 0x10);

    if (r == 0) {
        return 0;
    }
    r[3] = 0x14;
    *(void **)(r + 0x1C) = f_UpdateWaterTempleQuestPropActor;
    *(void **)(r + 0x10) = a0;
    *(s16 *)(r + 0x36) = 0;
    *(s16 *)(r + 0x2E) = 0;
    *(s16 *)(r + 0x32) = 0x140;
    return r;
}


void func_801296A0(u8 *p)
{
    if (func_80051B70(p, 0xC, 0x6E) == 0) {
        *(s16 *)(p + 0x58) = 0;
        *(s16 *)(p + 0x56) = 0;
        *(s16 *)(p + 0x54) = 0;
    }
}


void func_801296E0(void *arg0) {
    if (D_800BFA3A == 0xB) {
        M2C_FIELD(arg0, s8 *, 4) = 3;
        return;
    }
    M2C_FIELD(arg0, s8 *, 1) = 1;
    func_800517F8();
}

void func_80129720(u8 *a)
{
    if (func_80051B70(a, 0xC, 0x6D) == 0) {
        *(s16 *)(a + 0x58) = 0;
        *(s16 *)(a + 0x56) = 0;
        *(s16 *)(a + 0x54) = 0;
    }
}


void func_80129760(void *arg0) {
    M2C_FIELD(arg0, s8 *, 1) = 1;
    func_800517F8();
}


u8 *func_80129784(void *a0)
{
    u8 *r = func_80072DDC(0, 0, 3, 0x10);

    if (r) {
        *(void **)(r + 0x1C) = f_UpdateWaterTempleQuestPropActor;
        *(void **)(r + 0x10) = a0;
        r[3] = 0x16;
        r[0x28] |= 0x80;
    }
    return r;
}


void func_801297E8(u8 *p)
{
    *(s32 *)(p + 0x3C) = D_800ECF80;
    func_80077B38(p, D_801486EC, 5);
    p[0xD] = 0;
    *(s16 *)(p + 0x5C) = 0;
    p[0xB] = 0x10;
    *(s16 *)(p + 0x5A) = 0;
    p[0x47] = 0;
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8012983C);

extern u8 D_800BFA42;

void func_80129924(u8 *p)
{
    if (D_800BFA42) {
        p[4] = 3;
    } else {
        func_80051B70(p, 0xC, 0x6C);
    }
}

extern M2C_UNK func_8011973C;
void func_80129960(void *arg0) {
    M2C_FIELD(arg0, s8 *, 0xB) = 0x20;
    M2C_FIELD(arg0, M2C_UNK **, 0x18) = &func_8011973C;
    M2C_FIELD(arg0, s16 *, 0x2E) = 0x3053;
    M2C_FIELD(arg0, s16 *, 0x32) = -0x1116;
    M2C_FIELD(arg0, s16 *, 0x36) = 0x17C3;
    M2C_FIELD(arg0, s16 *, 0x84) = 0xC8;
    M2C_FIELD(arg0, s16 *, 0x80) = 0;
    M2C_FIELD(arg0, s16 *, 0x82) = 0;
    M2C_FIELD(arg0, s16 *, 0x86) = 0x190;
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_801299A8);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80129A5C);


void func_80129B40(void *arg0) {
    M2C_FIELD(arg0, s8 *, 0) = 1;
    M2C_FIELD(arg0, s16 *, 0x80) = 0x40;
    M2C_FIELD(arg0, s16 *, 0x82) = 0x80;
    M2C_FIELD(arg0, s16 *, 0x84) = 0x190;
    M2C_FIELD(arg0, s16 *, 0x86) = 0x320;
}

extern u8 D_800BF8E3;
void func_80129B6C(void *arg0) {
    if (D_800BF8E3 == 0xFF) {
        M2C_FIELD(arg0, s8 *, 4) = 3;
        return;
    }
    M2C_FIELD(arg0, s8 *, 1) = 1;
    func_80077EBC();
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80129BAC);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8012A06C);

typedef struct {
    s16 x, y, w, h;
} RECT16;

void func_8012A638(RECT16 *a) {
    RECT16 r;
    u16 buf[16];
    s32 i, j, k;
    u16 c;
    u16 g;
    s32 cr, cg, cb;

    r.w = 16;
    r.h = 1;
    for (i = 0; i < a->w; i += 16) {
        r.x = a->x + i;
        r.y = a->y;
        for (j = 0; j < a->h; j++) {
            func_80081278(&r, buf);
            func_80080F6C(0);
            for (k = 0; k < 16; k++) {
                c = buf[k];
                cg = c >> 5;
                cb = c >> 10;
                cr = c & 0x1F;
                g = cr * 77 + (cg & 0x1F) * 150 + (cb & 0x1F) * 29;
                g >>= 8;
                c &= 0x8000;
                if (g >= 32) {
                    g = 31;
                }
                buf[k] = c | (g << 10) | (g << 5) | g;
            }
            func_80081218(&r, buf);
            func_80080F6C(0);
            r.y++;
        }
    }
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8012A7CC);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8012A9DC);

extern S8 D_80145A70[];

void func_8012AADC(void)
{
    u32 i;

    if (D_800BF873) {
        for (i = 0; i < 6; i++) {
            func_8012A638(&D_80145A70[i]);
        }
    }
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8012AB30);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8012AEC0);

extern u16 *D_800ECF78;

void func_8012B3E8(u8 *a)
{
    u16 *p = D_800ECF78;
    u16 t;

    *(u16 **)(a + 0xC) = p;
    *(u16 *)(a + 8) = p[0];
    t = p[1];
    a[7] = 0;
    *(u16 *)(a + 0xA) = t;
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8012B414);

typedef struct { s16 x0; s16 id; u8 k; u8 p5; s16 v6; s16 v8; } Entry10;
extern Entry10 D_80145AA0[];
void f_UpdateLastEvilPigAccessActor();

u8 *func_8012B89C(u8 *a, s32 i)
{
    Entry10 *t = D_80145AA0;
    Entry10 *e = &t[i];
    u8 *p;

    if (func_8004D7EC(e->id, 1)) {
        return NULL;
    }
    p = func_80072DDC(a, 2, 2, 8);
    if (p != NULL) {
        *(void **)(p + 0x1C) = f_UpdateLastEvilPigAccessActor;
        p[0x5E] = 0;
        *(s16 *)(p + 0xE) = e->id;
        p[3] = e->k;
        *(s16 *)(p + 0x68) = e->v6;
        *(s16 *)(p + 0x60) = e->v8;
        if (*(s16 *)(p + 0x68) == 0) {
            *(s16 *)(p + 0x62) = 1;
        } else {
            *(s16 *)(p + 0x62) = 4;
        }
        *(s16 *)(p + 0x64) = 2;
        p[0x2A] = 0;
        return p;
    }
    return NULL;
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", f_UpdateLastEvilPigAccessActor);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8012BC44);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8012BF5C);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8012C018);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8012C118);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8012C3A4);

INCLUDE_ASM("asm/a08/nonmatchings/a08", f_UpdateNishikiBirdNestActor);


s32 func_8012C8AC(void *arg0) {
    func_80128D1C(arg0);
    return 1;
}

extern u8 D_800BFA48;

s32 func_8012C8CC(u8 *p)
{
    if (D_800BFA48 == 0) {
        p[0x7A] = 1;
    } else if (D_800BFA48 == 1) {
        p[0x7A] = 2;
    } else {
        p[0x7A] = 3;
    }
    return 1;
}

extern s8 D_800E807E;
s32 func_8012C904(void) {
    D_800E807E = 1;
    return 1;
}

extern s8 D_800E807E;
s32 func_8012C918(void) {
    D_800E807E = 0;
    return 1;
}

extern u8 D_8001B4DC[];
extern u8 D_80145E80[];

void func_8012C928(u8 *a)
{
    s32 s;
    s32 r;

    switch (a[5]) {
    case 0:
        s = a[6];
        switch (s) {
        case 0:
            if (D_800BFA4E < 30) {
                r = 0;
                goto done;
            }
            a[6] = 1;
            r = 0;
            goto done;
        case 1:
            a[6] = 2;
            func_80040CDC(a, D_8001B4DC, D_80145E80);
            a[0x70] = s;
            break;
        case 2:
            func_80041098(a);
            if (a[0x70] != 0xFF) {
                r = 0;
                goto done;
            }
            a[6] = 0;
            func_80042310();
            r = 1;
            goto done;
        default:
            r = 0;
            goto done;
        }
        r = 0;
    done:
        if (r) {
            a[5]++;
        }
        break;
    case 1:
        func_8012C3A4(a);
        break;
    }
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8012CA40);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8012CCD4);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8012CF20);

extern void *D_801461F0[];

void func_8012D000(u8 *a)
{
    if (a[0x71] == 0xFF) {
        func_80040D68(a, D_801461F0[a[0x5E]]);
        a[5] = 2;
        a[6] = 0;
        a[0x70] = 1;
    }
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8012D060);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8012D144);


s32 func_8012D1C4(void *arg0) {
    func_80051B04(M2C_FIELD(arg0, s32 *, 0xC0), 0x1B, 0xF);
    return 1;
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8012D1EC);

extern u8 D_800BFB06;

s32 func_8012D270(u8 *a)
{
    if (D_800BFB06 != 0) {
        a[0x5E] = 4;
        return 3;
    }
    return 2;
}


s32 func_8012D298(u8 *p)
{
    if ((*(s32 *)(p + 0x14) = func_8012D398(p)) != 0) {
        func_8004D650(0x52, 1);
        return 1;
    }
    return 0;
}


s32 func_8012D2DC(void *arg0) {
    void *temp_v1;

    if (M2C_FIELD(arg0, s16 *, 0x72) == 0) {
        M2C_FIELD(arg0, u8 *, 6) = (u8) (M2C_FIELD(arg0, u8 *, 6) + 1);
    } else {
        temp_v1 = M2C_FIELD(arg0, void **, 0x14);
        M2C_FIELD(temp_v1, u8 *, 5) = (u8) (M2C_FIELD(temp_v1, u8 *, 5) + 1);
    }
    return 1;
}


s32 func_8012D320(void) {
    func_8004ED0C(0x52, 4);
    return 1;
}


s32 func_8012D344(void)
{
    u8 *e = D_800E7E80;

    if (e[0x29] == 0x81 && D_1F800162 >= -0x157C) {
        if (*(s16 *)(e + 0x17E) & 0x8200) {
            return 3;
        }
        return 2;
    }
    return 0;
}

void func_8012CCD4();

u8 *func_8012D398(void *a)
{
    u8 *r = func_80072DDC(a, 1, 3, 0x26);

    if (r != NULL) {
        *(void **)(r + 0x1C) = func_8012CCD4;
    }
    return r;
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8012D3D4);


void func_8012D560(void *arg0) {
    s32 temp_s1;

    temp_s1 = arg0 + 0x2C;
    func_80027144(M2C_FIELD(M2C_FIELD(arg0, void **, 0xC0), s32 *, 0x40), temp_s1, 0x700, 0x18);
    func_80074590(0xC, 0, 0);
    M2C_FIELD(arg0, u16 *, 0x32) = (u16) (M2C_FIELD(arg0, u16 *, 0x32) + 0x64);
    func_80027144(M2C_FIELD(M2C_FIELD(arg0, void **, 0xC0), s32 *, 0x40), temp_s1, 0x800, -0x7FE8);
    func_80074590(0xC, 0, 0);
    if (func_801238D0(arg0, 5) != 0) {
        D_800BF870.pad1[0x1C7] += 1;
    }
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", f_UpdateRareCrabPickupActor);


void func_8012D8F4(void *arg0) {
    u16 temp_v0;
    u16 temp_v0_2;
    u8 temp_s1;

    func_8004766C();
    temp_s1 = M2C_FIELD(arg0, u8 *, 5);
    switch (temp_s1) {                              /* irregular */
    case 0:
        temp_v0 = M2C_FIELD(arg0, u16 *, 0x32) - 0xA;
        M2C_FIELD(arg0, u16 *, 0x32) = temp_v0;
        if (M2C_FIELD(arg0, s16 *, 0x64) >= (s16) temp_v0) {
            M2C_FIELD(arg0, u16 *, 0x32) = (u16) M2C_FIELD(arg0, s16 *, 0x64);
            M2C_FIELD(arg0, u8 *, 5) = 2U;
            return;
        }
        return;
    case 1:
        temp_v0_2 = M2C_FIELD(arg0, u16 *, 0x32) + 0xA;
        M2C_FIELD(arg0, u16 *, 0x32) = temp_v0_2;
        if ((s16) temp_v0_2 >= M2C_FIELD(arg0, s16 *, 0x64)) {
            M2C_FIELD(arg0, u16 *, 0x32) = (u16) M2C_FIELD(arg0, s16 *, 0x64);
            M2C_FIELD(arg0, u8 *, 5) = 2U;
            return;
        }
        if ((M2C_FIELD(arg0, u8 *, 0x29) != 0) || (func_80049250(arg0, 0, 0x1E) == temp_s1)) {
            M2C_FIELD(arg0, u8 *, 5) = 3U;
            return;
        }
        break;
    case 2:
        if (M2C_FIELD(arg0, s16 *, 0x4A) == 0) {
            func_8011B344(arg0 + 0x2C, -0xA, 0x14, 0x64);
        }
        M2C_FIELD(arg0, u16 *, 0x32) = (u16) ((u16) M2C_FIELD(arg0, s16 *, 0x64) + (func_80083E80(M2C_FIELD(arg0, s16 *, 0x4A)) >> 7));
        M2C_FIELD(arg0, s16 *, 0x4A) = (s16) (((u16) M2C_FIELD(arg0, s16 *, 0x4A) + 0x40) & 0xFFF);
        break;
    }
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8012DA44);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8012DC6C);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8012DE84);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8012DFDC);


s32 func_8012E168(u8 *p)
{
    if (func_8012DFDC(p[0x2A]) == 0) {
        return 0;
    }
    return func_8007778C(p);
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8012E1A4);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8012E274);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8012E61C);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8012E6CC);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8012E82C);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8012EA68);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8012ED44);


void func_8012EE20(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 5);
    switch (temp_v1) {                              /* irregular */
    case 0:
        if (D_800BFA42 != 0) {
            M2C_FIELD(arg0, s8 *, 0x29) = 0;
            M2C_FIELD(arg0, u8 *, 5) = (u8) (M2C_FIELD(arg0, u8 *, 5) + 1);
            return;
        }
        func_8012E82C(arg0);
        return;
    case 1:
        func_8012E82C(arg0);
        if (((M2C_FIELD(arg0, u8 *, 3) + 1) * 2) == D_800BFA42) {
            M2C_FIELD(arg0, s8 *, 4) = 2;
            M2C_FIELD(arg0, u8 *, 5) = 0U;
            M2C_FIELD(arg0, s8 *, 0x29) = 2;
        }
        return;
    }
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8012EEC8);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8012F5F0);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8012F820);


s32 func_8012FB28(u8 *p)
{
    if (func_8012FB64(p[3]) == 0) {
        return 0;
    }
    return func_8007778C(p);
}


s32 func_8012FB64(u8 a)
{
    u8 v;

    if (a == 0) {
        if (D_1F800207 < 0x18) {
            return 0;
        }
    } else {
        v = D_1F800207;
        if (v < 11 && v != 7) {
            return 0;
        }
    }
    return 1;
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8012FBB4);


void func_8012FC74(u8 *p, s32 a1)
{
    SV v;

    if (p[1]) {
        v.a = *(s16 *)(p + 0x2E);
        v.c = *(s16 *)(p + 0x36);
        v.b = *(s16 *)(p + 0x7C);
        func_8011BD98(9, &v, a1);
        func_80074590(7, 7, -0x28);
    }
}

void func_8012EEC8();

u8 *func_8012FCD8(u8 *a0, u8 a1)
{
    u8 *r = func_80072DDC(a0, 1, 2, 0x5C);

    if (r) {
        *(void **)(r + 0x1C) = func_8012EEC8;
        r[3] = a0[3];
        r[0x5E] = a1;
    }
    return r;
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8012FD38);

extern u8 D_80148E68[];
extern u8 D_800A3D40[];

void func_8012FDEC(u8 *a)
{
    u8 *g;
    u8 c;

    func_80040CDC(a, D_80148E68, D_800A3D40);
    *(s16 *)(a + 0x56) = 0x800;
    g = (u8 *)&D_800BF870;
    c = g[0xC3];
    if (c == 0xFF) {
        if (g[0x88] == c) {
            a[0x5E] = 4;
        } else {
            a[0x5E] = 3;
        }
        func_80041718(a, 1, 0);
    } else if (g[0x1C1] >= 10) {
        a[0x5E] = 2;
        func_80041718(a, 1, 0);
    } else {
        if (c & 0x80) {
            a[0x5E] = 1;
        } else {
            a[0x5E] = 0;
        }
        func_80041718(a, 0, 0);
    }
    *(s16 *)(a + 0x80) = 0xA5;
    *(s16 *)(a + 0x82) = 0x14A;
    *(s16 *)(a + 0x84) = 0x96;
    *(s16 *)(a + 0x86) = 0x1C2;
    if (D_800BFA31 >= 10) {
        *(s16 *)(a + 0x2E) = 0x19A0;
        *(s16 *)(a + 0x32) = -0x1559;
        *(s16 *)(a + 0x36) = 0x2D50;
    }
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8012FF00);

INCLUDE_ASM("asm/a08/nonmatchings/a08", f_UpdateClosedClamshellQuestActor);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8013036C);

extern void *D_801463B0[];

void func_80130424(u8 *a)
{
    if (a[0x71] == 0xFF) {
        func_80040D68(a, D_801463B0[a[0x5E]]);
        a[5] = 2;
        a[6] = 0;
        a[0x70] = 1;
    }
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80130484);


void func_80130500(void *arg0) {
    u8 temp_v1;

    func_8007778C();
    func_80041098(arg0);
    func_8004190C(arg0);
    temp_v1 = M2C_FIELD(arg0, u8 *, 5);
    switch (temp_v1) {                              /* irregular */
    case 0:
        func_8013036C(arg0);
        break;
    case 1:
        func_80130424(arg0);
        break;
    case 2:
        func_80130484(arg0);
        break;
    }
    if (M2C_FIELD(arg0, u8 *, 1) != 0) {
        func_800518FC(arg0);
    }
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_801305AC);

extern void *D_801465F4[];

void func_80130644(u8 *a)
{
    if (a[0x71] == 0xFF) {
        func_80040D68(a, D_801465F4[a[0x5E]]);
        a[5] = 2;
        a[6] = 0;
        a[0x70] = 1;
    }
}


void func_801306A4(u8 *p)
{
    u8 *q;

    if (p[0x71] == 0xFF) {
        q = *(u8 **)(p + 0x14);
        switch (p[0x5E]) {
        case 2:
            p[0] = 9;
        case 0:
            p[0x5E]++;
        case 1:
            q[0x5E] = 0;
            D_800BF809 = 0;
            break;
        }
        p[5] = 0;
    }
}


s32 func_80130714(u8 *a)
{
    if (D_800BFAD7 != 0) {
        a[0x5E] = 0x2;
        return 3;
    }
    return 2;
}


void func_8013073C(u8 *a)
{
    u8 *g;

    *(s32 *)(a + 0x14) = func_80124A48(a);
    func_80040CDC(a, D_80148E68, D_800A3D40);
    func_80041718(a, 1, 0);
    *(s16 *)(a + 0x56) = 0x140;
    g = (u8 *)&D_800BF870;
    if (g[0x88] == 0xFF) {
        a[0x5E] = 3;
    } else if (g[0x88] == 0) {
        a[0x5E] = 0;
        a[0] = 2;
    } else if (g[0x267]) {
        a[0x5E] = 2;
        a[0] = 2;
    } else {
        a[0x5E] = 1;
        a[0] = 2;
    }
    *(s16 *)(a + 0x80) = 0xAE;
    *(s16 *)(a + 0x82) = 0x15C;
    *(s16 *)(a + 0x84) = 0x96;
    *(s16 *)(a + 0x86) = 0x12C;
}


void func_8013080C(void *arg0) {
    u8 temp_v1;

    M2C_FIELD(arg0, s8 *, 1) = 1;
    func_80077E7C();
    func_80041098(arg0);
    func_8004190C(arg0);
    temp_v1 = M2C_FIELD(arg0, u8 *, 5);
    switch (temp_v1) {                              /* irregular */
    case 0:
        func_801305AC(arg0);
        break;
    case 1:
        func_80130644(arg0);
        break;
    case 2:
        func_801306A4(arg0);
        break;
    }
    func_800518FC(arg0);
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_801308B0);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80130BA0);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80130CE0);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80130F84);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_801310D8);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8013169C);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80131964);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80131BC4);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_801320B4);

INCLUDE_ASM("asm/a08/nonmatchings/a08", f_UpdateGiantFishActor);

extern u8 D_800BFB53;

s32 func_80132468(void)
{
    if (D_800BFB53 != 0) {
        return 0x3;
    }
    return 0x2;
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80132488);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80132564);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8013263C);


s32 func_8013271C(void *arg0) {
    if (M2C_FIELD(arg0, s16 *, 0x72) != 0) {
        M2C_FIELD(arg0, s8 *, 0xBF) = 1;
    } else {
        M2C_FIELD(arg0, s8 *, 0xBF) = 0;
    }
    return 1;
}


s32 func_80132740(void *arg0) {
    M2C_FIELD(arg0, u8 *, 0x7B) = (u8) M2C_FIELD(arg0, u8 *, 0x72);
    return 1;
}


s32 func_80132754(s32 arg0) {
    void *temp_v0;

    temp_v0 = func_80031220(0x919, 0, -0x1E);
    if (temp_v0 != NULL) {
        M2C_FIELD(temp_v0, s32 *, 0x10) = arg0;
    }
    return 1;
}


s32 func_80132794(void *arg0) {
    M2C_FIELD(arg0, u8 *, 0x5F) = (u8) M2C_FIELD(arg0, u8 *, 0x72);
    return 1;
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_801327A8);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80132BC8);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80132DD4);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80132F90);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_801331A8);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8013342C);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_801336F0);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80133CB8);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80133E8C);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8013404C);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_801345B4);


s32 func_80134814(T4814 *a)
{
    switch (a->x6E) {
    case 0:
        if (a->xBE) {
            a->x4E = -0x80;
            a->x6C = a->x56 - 0x800;
        } else {
            a->x4E = 0x80;
            a->x6C = a->x56 + 0x800;
        }
        a->x6E++;
    case 1:
        a->x56 += a->x4E;
        if (a->xBE) {
            if (a->x6C < a->x56) {
                break;
            }
            a->x56 = a->x6C;
            a->x6E = -1;
            a->xBE ^= 1;
            return 1;
        } else {
            if (a->x56 < a->x6C) {
                break;
            }
            a->x56 = a->x6C;
            a->x6E = -1;
            a->xBE ^= 1;
            return 1;
        }
    }
    return 0;
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80134904);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_801349CC);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80134B2C);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80134CEC);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80134E44);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80134F68);


void func_8013500C(void *arg0) {
    u16 temp_v0;
    u8 temp_v1;

    if (func_80135158() != -1) {
        func_80135574(arg0, 0x64, 0x12C);
        temp_v1 = M2C_FIELD(arg0, u8 *, 6);
        switch (temp_v1) {                          /* irregular */
        case 0:
            func_80051B04(M2C_FIELD(arg0, s32 *, 0xC4), 0x19, 0x10);
            func_80135630(arg0, 0, 6);
            M2C_FIELD(arg0, u8 *, 6) = (u8) (M2C_FIELD(arg0, u8 *, 6) + 1);
            return;
        case 1:
            temp_v0 = M2C_FIELD(arg0, u16 *, 0x40) - 1;
            M2C_FIELD(arg0, u16 *, 0x40) = temp_v0;
            if ((temp_v0 << 0x10) == 0) {
                func_80051B04(M2C_FIELD(arg0, s32 *, 0xC4), 0x19, 1);
                M2C_FIELD(arg0, s8 *, 5) = 0xA;
                M2C_FIELD(arg0, u8 *, 6) = 0U;
                M2C_FIELD(arg0, u16 *, 0x40) = 6U;
            }
            break;
        }
    }
}


void func_801350D8(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 6) == 0) {
        M2C_FIELD(arg0, u8 *, 0x1B) = (u8) (M2C_FIELD(arg0, u8 *, 0x1B) & 0xBF);
        func_80051B04(M2C_FIELD(arg0, s32 *, 0xC4), 0x19, 0xF);
        func_80135630(arg0, 0x12, 4);
        func_80026100(8);
        func_80074590(0x85, 0, 0);
        M2C_FIELD(arg0, u8 *, 6) = (u8) (M2C_FIELD(arg0, u8 *, 6) + 1);
    }
}


s32 func_80135158(void *a0)
{
    func_8004766C(a0);
    if (func_80134CEC(a0) != 0) {
        return -1;
    }
    return 0;
}


void func_80135194(void *arg0) {
    s16 temp_v0;

    if (func_80134904() < 2) {
        if (M2C_FIELD(arg0, s16 *, 0x70) < 0x47F) {
            M2C_FIELD(arg0, s16 *, 0x72) = 1;
        } else {
            goto block_4;
        }
    } else {
        temp_v0 = func_80135230(arg0);
        if (temp_v0 < 0x1FE) {
block_4:
            M2C_FIELD(arg0, s16 *, 0x72) = 2;
        } else if (temp_v0 < 0x352) {
            M2C_FIELD(arg0, s16 *, 0x72) = 1;
        } else {
            M2C_FIELD(arg0, s16 *, 0x72) = 0;
        }
    }
    func_80135630(arg0, M2C_FIELD(arg0, s16 *, 0x72) + 8, 4);
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80135230);

extern s8 D_1F800164_6889[];
extern s8 D_1F800164_6889[];
extern s16 D_800E7FFE;
extern s8 D_1F800160_d288[];

s32 func_801352CC(u8 *a) {
    s16 dz, dx;

    if (D_800E7FFE & 0x8200) {
        return 0;
    }
    dx = *(u16 *)D_1F800160_d288 - M2C_FIELD(a, u16 *, 0x2E);
    dz = *(u16 *)D_1F800164_6889 - M2C_FIELD(a, u16 *, 0x36);
    return func_80077768((s16)-func_80085690(dz, dx), M2C_FIELD(a, s16 *, 0x56), 0) != 0;
}

extern u16 D_1F8000E2;

s32 func_80135354(void *a0)
{
    if (func_80135388(a0) == 0) {
        return 0;
    }
    return func_8007778C(a0);
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80135388);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80135424);

extern s8 D_1F8001A0[];

void func_801354F4(void *arg0) {
    u16 temp_a0;

    if (M2C_FIELD(arg0, u8 *, 0xBF) != 0) {
        func_80049760();
    } else {
        func_80049674(arg0);
    }
    temp_a0 = *((u16 *)D_1F8001A0);
    M2C_FIELD(arg0, u16 *, 0x60) = temp_a0;
    if (M2C_FIELD(arg0, s16 *, 0x6E) == -1) {
        if (M2C_FIELD(arg0, u8 *, 0xBE) == 0) {
            M2C_FIELD(arg0, u16 *, 0x56) = temp_a0;
            return;
        }
        M2C_FIELD(arg0, u16 *, 0x56) = (u16) ((temp_a0 + 0x800) & 0xFFF);
    }
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80135574);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80135630);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_801356F8);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80135CB8);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80135EE8);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_801364F8);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_801366A4);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8013698C);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80136C94);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80136DE0);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80136F5C);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_801371CC);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8013731C);

s32 func_80137410(T4814 *a)
{
    switch (a->x6E) {
    case 0:
        if (a->xBE) {
            a->x4E = -0x80;
            a->x6C = a->x56 - 0x800;
        } else {
            a->x4E = 0x80;
            a->x6C = a->x56 + 0x800;
        }
        a->x6E++;
    case 1:
        a->x56 += a->x4E;
        if (a->xBE) {
            if (a->x6C < a->x56) {
                break;
            }
            a->x56 = a->x6C;
            a->x6E = -1;
            a->xBE ^= 1;
            return 1;
        } else {
            if (a->x56 < a->x6C) {
                break;
            }
            a->x56 = a->x6C;
            a->x6E = -1;
            a->xBE ^= 1;
            return 1;
        }
    }
    return 0;
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80137500);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_801375D4);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80137780);

s32 func_80137898(u8 *a) {
    s16 dz, dx;

    if (D_800E7FFE & 0x8200) {
        return 0;
    }
    dx = *(u16 *)D_1F800160_d288 - M2C_FIELD(a, u16 *, 0x2E);
    dz = *(u16 *)D_1F800164_6889 - M2C_FIELD(a, u16 *, 0x36);
    return func_80077768((s16)-func_80085690(dz, dx), M2C_FIELD(a, s16 *, 0x56), 0) != 0;
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80137920);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_801379BC);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80137A90);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80137B18);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80137C5C);


void func_8013829C(s32 arg0) {
    void *temp_a0;

    temp_a0 = M2C_FIELD(arg0, void **, 0x10);
    if (temp_a0 != NULL) {
        M2C_FIELD(arg0, u16 *, 0x2E) = (u16) M2C_FIELD(M2C_FIELD(temp_a0, void **, 0xC0), u16 *, 0x2C);
        M2C_FIELD(arg0, u16 *, 0x32) = (u16) M2C_FIELD(M2C_FIELD(temp_a0, void **, 0xC0), u16 *, 0x30);
        M2C_FIELD(arg0, u16 *, 0x36) = (u16) M2C_FIELD(M2C_FIELD(temp_a0, void **, 0xC0), u16 *, 0x34);
        M2C_FIELD(arg0, u16 *, 0x56) = (u16) M2C_FIELD(temp_a0, u16 *, 0x56);
        M2C_FIELD(M2C_FIELD(arg0, void **, 0xC0), u16 *, 0xC) = (u16) M2C_FIELD(M2C_FIELD(temp_a0, void **, 0xC0), u16 *, 0xC);
        M2C_FIELD(arg0, u16 *, 0x60) = (u16) M2C_FIELD(temp_a0, u16 *, 0x60);
        M2C_FIELD(arg0, u8 *, 0xBE) = (u8) M2C_FIELD(temp_a0, u8 *, 0xBE);
        M2C_FIELD(arg0, u8 *, 0xBF) = (u8) M2C_FIELD(temp_a0, u8 *, 0xBF);
        if (M2C_FIELD(arg0, u8 *, 4) == 1) {
            M2C_FIELD(temp_a0, u8 *, 0x47) = (u8) M2C_FIELD(arg0, u8 *, 0x47);
            M2C_FIELD(temp_a0, u8 *, 0x2B) = (u8) M2C_FIELD(arg0, u8 *, 0x2B);
        }
        if (M2C_FIELD(temp_a0, u8 *, 1) != 0) {
            M2C_FIELD(arg0, s8 *, 1) = 1;
            func_80077E7C(arg0);
            func_800517F8(arg0);
        }
    }
}


u8 *func_80138398(u8 *a0)
{
    u8 *r = func_80072DDC(a0, 1, 2, 0x5F);

    if (r) {
        *(void **)(r + 0x1C) = func_80137C5C;
        r[3] = a0[3] | 0x80;
    }
    return r;
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_801383F0);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80138784);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80138B08);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80138CFC);

typedef struct {
    u8 pad0[0x50];
    s16 x50;
    u8 pad52[4];
    s16 x56;
    u8 pad58[0x14];
    s16 x6C;
    s16 x6E;
    u8 pad70[0x4E];
    u8 xBE;
} T8E10;

s32 func_80138E10(T8E10 *a)
{
    switch (a->x6E) {
    case 0:
        if (a->xBE) {
            a->x50 = -0x80;
            a->x6C = a->x56 - 0x800;
        } else {
            a->x50 = 0x80;
            a->x6C = a->x56 + 0x800;
        }
        a->x6E++;
    case 1:
        a->x56 += a->x50;
        if (a->xBE) {
            if (a->x6C < a->x56) {
                break;
            }
            a->x56 = a->x6C;
            a->x6E = -1;
            a->xBE ^= 1;
            return 1;
        } else {
            if (a->x56 < a->x6C) {
                break;
            }
            a->x56 = a->x6C;
            a->x6E = -1;
            a->xBE ^= 1;
            return 1;
        }
    }
    return 0;
}

extern M2C_UNK D_80149A50;
void func_80138F00(void *arg0) {
    s8 temp_v0;
    u16 temp_v0_2;
    u16 var_v0;
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 6);
    switch (temp_v1) {                              /* irregular */
    case 0:
        M2C_FIELD(arg0, u16 *, 0x40) = 0x1EU;
        func_80077C40(arg0, &D_80149A50, 9);
        M2C_FIELD(M2C_FIELD(arg0, void **, 0xD0), s16 *, 0x38) = 0x1000;
        M2C_FIELD(M2C_FIELD(arg0, void **, 0xD0), s16 *, 0x3A) = 0x1000;
        M2C_FIELD(M2C_FIELD(arg0, void **, 0xD0), s16 *, 0x3C) = 0x1000;
        temp_v0 = (M2C_FIELD(arg0, u8 *, 0x2B) & 1) ^ 1;
        M2C_FIELD(arg0, s8 *, 0xBE) = temp_v0;
        if (temp_v0 != 0) {
            var_v0 = (M2C_FIELD(arg0, u16 *, 0x60) + 0x800) & 0xFFF;
        } else {
            var_v0 = M2C_FIELD(arg0, u16 *, 0x60);
        }
        M2C_FIELD(arg0, u16 *, 0x56) = var_v0;
        M2C_FIELD(arg0, s16 *, 0x6E) = -1;
        M2C_FIELD(arg0, u8 *, 6) = (u8) (M2C_FIELD(arg0, u8 *, 6) + 1);
        /* fallthrough */
    case 1:
        temp_v0_2 = M2C_FIELD(arg0, u16 *, 0x40) - 1;
        M2C_FIELD(arg0, u16 *, 0x40) = temp_v0_2;
        if ((temp_v0_2 << 0x10) == 0) {
            M2C_FIELD(arg0, s8 *, 5) = 0;
            M2C_FIELD(arg0, u8 *, 6) = 3U;
            M2C_FIELD(arg0, s8 *, 7) = 0;
            func_80077CFC(arg0, &D_80149A50, 0, 4);
        }
        return;
    }
}

s32 func_8013900C(void *a0)
{
    if (func_8013910C(a0) == 0) {
        return 0;
    }
    return func_8007778C(a0);
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80139040);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8013910C);

s32 func_801391C4(u8 *a) {
    s16 dz, dx;

    if (D_800E7FFE & 0x8200) {
        return 0;
    }
    dx = *(u16 *)D_1F800160_d288 - M2C_FIELD(a, u16 *, 0x2E);
    dz = *(u16 *)D_1F800164_6889 - M2C_FIELD(a, u16 *, 0x36);
    return func_80077768((s16)-func_80085690(dz, dx), M2C_FIELD(a, s16 *, 0x56), 0) != 0;
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8013924C);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80139458);

INCLUDE_ASM("asm/a08/nonmatchings/a08", f_UpdateWaterTempleMermaidAndGearNpcActor);

extern s32 D_800BF860;
s32 func_801398C0(s32 arg0) {
    D_800BF860 = arg0;
    return 1;
}

extern s32 D_800BF860;
s32 func_801398D0(void) {
    return D_800BF860 == 0;
}


s32 func_801398E0(void *arg0) {
    D_800BF870.pad1[0x1D5] = (D_800BF870.pad1[0x1D5] | (1 << M2C_FIELD(arg0, u8 *, 0x47))) & 0xEF;
    func_80074590(0x1A, 0x1B, 0);
    return 1;
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8013992C);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_801399B4);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80139A9C);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80139CEC);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80139E58);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8013A208);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8013A398);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8013A578);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8013A630);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8013A6A8);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8013A7D4);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8013A9F8);

extern u8 D_800BFB28;

s32 func_8013AE4C(u8 *p)
{
    if (D_800BFB28 == 0) {
        p[0x7A] = 0xA;
    } else {
        p[0x7A] = 0xF;
    }
    return 1;
}


s32 func_8013AE78(void *a0)
{
    u8 *r = func_80072DDC(a0, 2, 3, 0x10);

    if (r != 0) {
        *(void **)(r + 0x1C) = f_UpdateWaterTempleQuestPropActor;
        r[3] = 0x1A;
        r[0x28] |= 0x80;
        func_8004D604(0x50, 1);
        return 1;
    }
    return 0;
}


s32 func_8013AEE0(void *a0)
{
    S13AE38 v;
    u8 *e;

    e = D_800E7E80;
    v.a = *(s16 *)(e + 0x2E);
    v.b = *(s16 *)(e + 0x32) - 0xC8;
    v.c = 0x15ED;
    func_80070F00(a0, 1, &v);
    func_800708B4(3);
    return 1;
}


s32 func_8013AF30(void) {
    return M2C_FIELD(*(void **)0x1F800214, u8 *, 3) == 0;
}

extern u8 D_80148790[];
extern u8 D_80147694[];
extern u8 D_8014767C[];
extern s32 D_800BF854;

void func_8013AF48(u8 *a)
{
    s32 s = a[6];
    u8 *g;

    switch (s) {
    case 0:
        if (D_800BF80F == 0) {
            {
                s32 one = 1;
                a[6] = one;
                func_80042354(one, 2);
            }
            g = (u8 *)&D_800BF870;
            if ((*(u16 *)(g + 0x2E) & 0x200) || (g[0x11] & 4)) {
                func_80040CDC(a, D_80148790, D_80147694);
            } else {
                func_80040CDC(a, D_80148790, D_8014767C);
            }
            a[0x70] = 1;
        }
        break;
    case 1:
        func_80041098(a);
        if (a[0x70] == 0xFF) {
            a[6]++;
            func_80042310();
            D_1F800137 = 2;
            D_800BF854 = s;
        }
        break;
    }
}

extern u8 D_801478E4[];

s32 func_8013B058(u8 *a)
{
    switch (a[6]) {
    case 0:
        if (D_800BF80F != 0) {
            return 0;
        }
        {
            s32 one = 1;
            a[6] = one;
            func_80042354(one, 2);
        }
        func_80040CDC(a, D_80148790, D_801478E4);
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

extern u8 D_80147924[];
extern u8 D_8014791C[];

void func_8013B110(u8 *a)
{
    switch (a[6]) {
    case 0:
        if (a[0x2B] == 3) {
            {
                s32 one = 1;
                a[6] = one;
                func_80042354(one, 2);
            }
            if (D_800BF928 == 0xFF) {
                func_80040CDC(a, D_80148790, D_80147924);
            } else {
                func_80040CDC(a, D_80148790, D_8014791C);
            }
            a[0x70] = 1;
        }
        break;
    case 1:
        func_80041098(a);
        if (a[0x70] == 0xFF) {
            a[6] = 0;
            func_80042310();
        }
        break;
    }
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8013B1DC);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8013B32C);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8013B49C);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8013B6FC);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8013B9F8);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8013BB64);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8013BCAC);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8013BF30);


s32 func_8013BFD0(void *arg0) {
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x14), s8 *, 5) = 1;
    return 1;
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8013BFE4);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8013C170);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8013C354);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8013C530);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8013C6B4);


s32 func_8013C860(u8 *p)
{
    u8 *a = D_800BF844;

    a[5] = 1;
    a[0x5E] = 0;
    *(s16 *)(a + 0x60) = 0;
    a[6] = 0;
    *(s16 *)(p + 0x48) = *(s16 *)(a + 0x2E) = 0x1A90;
    *(s16 *)(p + 0x4A) = *(s16 *)(a + 0x32) = -0x125E;
    *(s16 *)(p + 0x4C) = *(s16 *)(a + 0x36) = 0x2CEC;
    return 1;
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8013C8A8);

extern M2C_UNK D_800A3D90;
void func_8013CAC0(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x2B) == 3) {
        func_80042354(1, 1);
        func_80040D68(arg0, &D_800A3D90);
        M2C_FIELD(arg0, s8 *, 0x70) = 1;
        M2C_FIELD(arg0, s8 *, 5) = 1;
    }
}

extern void *D_80147E24[];

void func_8013CB14(u8 *a)
{
    if (a[0x71] == 0xFF) {
        func_80040D68(a, D_80147E24[a[0x5E]]);
        a[5] = 2;
        a[0x70] = 1;
    }
}


void func_8013CB70(u8 *p)
{
    u8 *g;

    if (p[0x71] == 0xFF) {
        switch (p[0x5E]) {
        case 0:
            g = (u8 *)&D_800BF870;
            g[0xCD] |= 0x40;
        case 2:
            p[0x5E]++;
            break;
        }
        p[5] = 0;
    }
}

extern u8 D_800BFB59;

s32 func_8013CBD4(u8 *a)
{
    if (D_800BFB59 != 0) {
        a[0x5E] = 0x2;
        return 3;
    }
    return 2;
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8013CBFC);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8013CF34);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8013D178);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8013D3C0);

extern u8 D_800BF80E;
s32 func_8013D4EC(void *arg0) {
    u16 temp_v0;

    if ((D_800BF80E != 0) || (temp_v0 = M2C_FIELD(arg0, u16 *, 0x72), M2C_FIELD(arg0, u16 *, 0x72) = (u16) (temp_v0 - 1), ((temp_v0 << 0x10) <= 0))) {
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8013D528);


s32 func_8013D614(u8 *p)
{
    s32 i = 0;

    p[0xD] |= 4;
    for (; i < p[9]; i++) {
        (*(u8 **)(p + 0xC0 + i * 4))[0x3F] = 0xF1;
    }
    return 1;
}


s32 func_8013D65C(void *arg0) {
    M2C_FIELD(arg0, u16 *, 0x58) = (u16) M2C_FIELD(arg0, u16 *, 0x72);
    return 1;
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8013D670);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8013D874);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8013DC04);

void func_8013DC04();

u8 *func_8013DD48(u8 *a, s32 b) {
    u8 *p = func_80072DDC(0, 0, 2, 71);

    if (p != NULL) {
        M2C_FIELD(p, void **, 0x1C) = func_8013DC04;
        p[0x3] = b;
        p[0x28] = (p[0x28] | 0x80);
        M2C_FIELD(p, s16 *, 0x2E) = M2C_FIELD(a, u16 *, 0x2);
        M2C_FIELD(p, s16 *, 0x32) = M2C_FIELD(a, u16 *, 0x6);
        M2C_FIELD(p, s16 *, 0x36) = M2C_FIELD(a, u16 *, 0xA);
    }
    return p;
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8013DDD4);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8013E038);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8013E278);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8013E3E0);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8013E638);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8013EB88);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8013F03C);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8013F150);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8013F40C);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8013F57C);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8013F6E4);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8013F8B4);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8013FA00);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8013FCD4);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8013FEEC);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_801401AC);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80140314);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80140608);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80140730);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80140834);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_8014095C);


void func_80140C00(u8 *p, u8 a1)
{
    p[0x50] = a1;
    p[0x44] = 0;
    p[0x4B] = 0xFC;
    p[0x4A] = 0xFC;
    (p + p[0x46])[0x48] = 0;
    (p + p[0x46])[0x4E] = 0xFF;
    p[3] = 100;
    p[0x46] = 0xFF;
    p[0x47] = 0;
    p[0] = 0x6D;
}

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80140C4C);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80140E10);

INCLUDE_ASM("asm/a08/nonmatchings/a08", func_80140FBC);

INCLUDE_ASM("asm/a08/nonmatchings/a08", f_UpdateWaterTempleRaftNpcActor);

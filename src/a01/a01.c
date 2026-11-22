#include "common.h"
#include "game.h"
#include "m2c.h"

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80109F7C);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8010A0F0);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8010A32C);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8010A530);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8010AA20);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8010AC3C);


s32 func_8010ACB8(s32 arg0, s32 arg1) {
    s32 var_a3;
    void *temp_a1;

    temp_a1 = M2C_FIELD(arg0, void **, 0x158);
    var_a3 = 0;
    if ((M2C_FIELD(temp_a1, u8 *, 0xC) == 4) && (M2C_FIELD(temp_a1, u8 *, 2) == 0x17)) {
        var_a3 = func_8010A530(arg0, (s32) temp_a1, arg1);
    }
    return var_a3;
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8010AD08);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8010AE30);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8010AF6C);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8010B604);

extern s8 D_1F800138[];
extern s8 D_1F80019B[];

void func_8010BAA4(void) {
    func_80045258(M2C_FIELD(*((volatile void **)D_1F800138), u8 *, 0x6E), 0xF);
    *((volatile s8 *)D_1F80019B) = 1;
    func_80051FB4();
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8010BAE4);

extern s8 D_800BF808[];
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

void func_8010BB74(u8 *a, u8 *b) {
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
extern s8 D_800BF80D;
extern u8 D_1F800182_5650;

void func_8010BCC8(u8 *a, u8 *b) {
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

extern u8 D_1F800253;
#define F16(p, o) M2C_FIELD(p, s16 *, o)
#define FU16(p, o) M2C_FIELD(p, u16 *, o)

s32 func_8010BE94(u8 *a, u8 *b) {
    s16 dx, dz, dy, d;
    u16 h, r, bh, ah;
    s32 y;

    dx = F16(a, 0x2E) - F16(b, 0x2E);
    dz = F16(a, 0x36) - F16(b, 0x36);
    r = func_80084080(dx * dx + dz * dz);
    if (F16(a, 0x80) + F16(b, 0x80) < r) {
        return -1;
    }
    {
        dy = FU16(a, 0x32) - FU16(b, 0x32);
        bh = FU16(b, 0x84); ah = FU16(a, 0x84); h = bh + ah;
        if ((u16)(dy + h) > F16(a, 0x86) + F16(b, 0x86)) {
        fail:
            return -1;
        }
        if (dy < 0) {
            d = -h;
        } else {
            d = (F16(b, 0x86) - bh) + (F16(a, 0x86) - ah);
        }
        if (d <= 0) {
            if (a[0x145] & 1) {
                goto fail;
            }
            b[0x29] = 1;
            M2C_FIELD(a, s32 *, 0x30) = (F16(b, 0x32) + d) << 16;
            func_80022C78(a);
            return 2;
        }
        y = F16(b, 0x32) + d;
        D_1F800253 = 4;
        M2C_FIELD(a, s32 *, 0x30) = y << 16;
        if (a[0x145] == 1 && F16(a, 0x4A) < 0) {
            F16(a, 0x4A) = 0;
        }
        return 3;
    }
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8010C008);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8010C2EC);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8010C498);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8010C6EC);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8010C7BC);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8010C928);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8010CA24);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8010CF68);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8010D188);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8010D3E0);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8010D568);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8010D90C);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8010DBEC);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8010DF24);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8010E0C4);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8010E1E8);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8010E338);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8010E4B0);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8010E6BC);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8010E8D8);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8010ED60);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8010EEA8);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8010EFBC);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8010F240);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8010F40C);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8010F690);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8010F87C);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8010FB64);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8010FD5C);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_801100A8);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80110214);

extern u16 D_800BFE56;
extern u8 D_800E7E80[];

void func_801103C0(u8 *a, u8 *b) {
    if (func_8010C008(a, b, M2C_FIELD(b, u8 **, 0xC0)) == 2 && D_800BF80D == 0 && !(D_800BFE56 & 2) &&
        M2C_FIELD(a, s16 *, 0x32) >= -0x987) {
        M2C_FIELD(a, s16 *, 0x6A) = -0x7900;
    }
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80110430);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80110504);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_801105B8);


void func_8011064C(void *a, u8 *b)
{
    if (b[0x47] == 2) {
        func_8010C008(a, b, *(void **)(b + 0xC0));
    } else {
        func_8001F650(a, b, *(void **)(b + 0xC0));
    }
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80110694);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80110788);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8011080C);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_801108D4);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80110968);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80110A18);

extern s8 D_1F800182[];
extern s16 D_800E7EB2;

void func_80110A94(void *arg0, void *arg1) {
    if ((M2C_FIELD(arg1, s16 *, 0x32) >= (D_800E7EB2 - 0x8C)) && (func_80022F04() != 0)) {
        if (func_8001DC9C(arg0, arg1, 0, 0x80) & 0x80) {
            M2C_FIELD(arg0, s8 *, 0x2B) = 2;
            M2C_FIELD(arg1, s8 *, 0) = 2;
            M2C_FIELD(arg1, s8 *, 4) = 2;
            M2C_FIELD(arg1, s8 *, 5) = 6;
            M2C_FIELD(arg1, s8 *, 6) = 0;
        }
        M2C_FIELD(arg1, s8 *, 0x2B) = 1;
        *((s8 *)D_1F800182) = 0;
    }
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80110B2C);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80110BB8);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80110CB8);

INCLUDE_ASM("asm/a01/nonmatchings/a01", f_SpawnPipeAreaSceneActorsFromPlacementTable);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_801112C0);

INCLUDE_ASM("asm/a01/nonmatchings/a01", f_UpdatePipeAreaSceneController);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80111620);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80111BE0);

extern u8 D_800BF873;
extern u8 D_800BF816;
extern s32 D_80135314;
extern u8 *D_800BF544;
extern u32 *D_800ED8C8;

void func_80111C58(void) {
    u8 buf[16];

    if (D_800BF873 == 0 && D_800BF816 == 0) {
        if (--D_80135314 < 0) {
            func_8003116C(0x200, buf, 0);
            D_80135314 = (func_8009A450() >> 12) + 1;
        }
    }
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80111CCC);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80111D74);


void func_80111ECC(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 4);
    switch (temp_v1) {                              /* irregular */
    case 0:
        if (M2C_FIELD(arg0, u8 *, 0x5E) == 0) {
            func_8004BEF4(arg0);
        }
        M2C_FIELD(arg0, u8 *, 4) = (u8) (M2C_FIELD(arg0, u8 *, 4) + 1);
        return;
    case 1:
        if (M2C_FIELD(arg0, u8 *, 0x5E) == 0) {
            func_80111D74(arg0);
            return;
        }
        return;
    case 2:
        func_8004B9C8(arg0);
        return;
    case 3:
        func_8007A624(arg0);
        break;
    }
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80111F94);

INCLUDE_ASM("asm/a01/nonmatchings/a01", f_UpdatePipeAreaQuestPickupActor);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80112784);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80112808);

void func_80113B40();
void f_UpdatePipeAreaQuestPickupActor();
void f_UpdatePipeAreaScenePropActor();
void func_8012B464();

u8 *func_801128B8(s32 a, s32 b) {
    u8 *p = func_80072DDC(a, 1, 5, 3);

    if (p == NULL) {
        return NULL;
    }
    p[0x3] = b;
    M2C_FIELD(p, void **, 0x1C) = f_UpdatePipeAreaQuestPickupActor;
    return p;
}


u8 *func_80112904(s32 a) {
    u8 *p = func_80072DDC(a, 1, 5, 3);

    if (p == NULL) {
        return NULL;
    }
    p[0x3] = 0;
    M2C_FIELD(p, void **, 0x1C) = f_UpdatePipeAreaQuestPickupActor;
    return p;
}

void f_UpdatePipeAreaScenePropActor();
void f_UpdatePipeAreaQuestPickupActor();

u8 *func_80112948(s32 a0) {
    u8 *p = func_80072DDC(a0, 0, 5, 3);

    if (p == NULL) {
        return NULL;
    }
    p[3] = 2;
    M2C_FIELD(p, void **, 0x1C) = f_UpdatePipeAreaQuestPickupActor;
    return p;
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80112990);


void func_80112A20(s32 arg0) {
    func_8007778C();
    func_8004B374(arg0, 0);
}


void func_80112A50(void *arg0) {
    func_8004D4C4(0x7F, 1);
    func_8004B0D8(arg0);
    M2C_FIELD(arg0, s8 *, 4) = 3;
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80112A8C);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80112B10);

extern M2C_UNK D_80135628;
void func_80112BB8(void *arg0) {
    u8 temp_v1;

    func_80041098();
    temp_v1 = M2C_FIELD(arg0, u8 *, 6);
    switch (temp_v1) {                              /* irregular */
    case 0:
        func_80112CB8(arg0);
        if (M2C_FIELD(arg0, u8 *, 0x71) == 0xFF) {
            func_80040D68(arg0, &D_80135628);
            M2C_FIELD(arg0, s8 *, 0x70) = 1;
            M2C_FIELD(arg0, u8 *, 6) = (u8) (M2C_FIELD(arg0, u8 *, 6) + 1);
            return;
        }
        return;
    case 1:
        func_80112CB8(arg0);
        if (M2C_FIELD(arg0, u8 *, 0x71) == 0) {
            M2C_FIELD(arg0, s16 *, 0x36) = 0x2340;
            M2C_FIELD(arg0, s8 *, 0x70) = 1;
            M2C_FIELD(arg0, u8 *, 6) = (u8) (M2C_FIELD(arg0, u8 *, 6) + 1);
            return;
        }
        break;
    case 2:
        if (M2C_FIELD(arg0, u8 *, 0x71) == 0xFF) {
            M2C_FIELD(arg0, s8 *, 0) = 1;
            M2C_FIELD(arg0, s8 *, 5) = 0;
            M2C_FIELD(arg0, u8 *, 6) = 0U;
            M2C_FIELD(arg0, u8 *, 3) = (u8) (M2C_FIELD(arg0, u8 *, 3) & 0x7F);
            M2C_FIELD(arg0, u16 *, 0x68) = (u16) M2C_FIELD(arg0, u16 *, 0x60);
        }
        break;
    }
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80112CB8);

extern u8 *D_800BF844;
extern u8 D_80135C38[];
extern u8 D_80135BE8[];
extern u8 *D_80138FFC_e406;
extern u8 D_80139000;

s32 func_80112DA0(u8 *a) {
    M2C_FIELD(a, s16 *, 0x32) += 8;
    if (M2C_FIELD(a, s16 *, 0x32) >= -0x1AB2) {
        M2C_FIELD(a, s16 *, 0x32) = -0x1AB2;
        return 1;
    }
    return 0;
}


u8 *func_80112DD8(u8 *a) {
    u8 t;
    u8 *p = func_80072DDC(a, 0, 5, 3);

    if (p == NULL) {
        return NULL;
    }
    t = a[3];
    M2C_FIELD(p, void **, 0x1C) = f_UpdatePipeAreaQuestPickupActor;
    p[0x3] = (t & 1) + 6;
    M2C_FIELD(p, s16 *, 0x2E) = M2C_FIELD(a, u16 *, 0x2E);
    M2C_FIELD(p, s16 *, 0x32) = M2C_FIELD(a, u16 *, 0x32);
    M2C_FIELD(p, s16 *, 0x36) = M2C_FIELD(a, u16 *, 0x36);
    return p;
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80112E58);


void func_80112EDC(void) {
    func_8007778C();
}


void func_80112EFC(void *arg0) {
    if (func_80040C00(0x65) >= 0) {
        func_8004D4C4(0x3E, 1);
        func_8004B0D8(arg0);
        D_800BF870.pad1[0x17B] += 1 << ((M2C_FIELD(arg0, u8 *, 3) & 1) * 2);
    }
    M2C_FIELD(arg0, s8 *, 4) = 3;
}

extern u8 D_800BF871;
extern s32 D_800ECF80;
extern M2C_UNK D_80139294;
void func_80112F6C(void *arg0) {
    if (D_800BF871 != 0x1A) {
        M2C_FIELD(arg0, s8 *, 4) = 3;
        return;
    }
    M2C_FIELD(arg0, s8 *, 0xB) = 0x10;
    M2C_FIELD(arg0, s16 *, 0x5A) = 0;
    M2C_FIELD(arg0, s8 *, 0x47) = 0;
    M2C_FIELD(arg0, s16 *, 0x5C) = 0;
    M2C_FIELD(arg0, s8 *, 0xD) = 0;
    M2C_FIELD(arg0, s32 *, 0x3C) = (s32) D_800ECF80;
    func_80077B38(arg0, &D_80139294, 0xE);
    M2C_FIELD(arg0, s8 *, 0) = 1;
    M2C_FIELD(arg0, s16 *, 0x80) = 0x20;
    M2C_FIELD(arg0, s16 *, 0x82) = 0x40;
    M2C_FIELD(arg0, s16 *, 0x84) = 0x20;
    M2C_FIELD(arg0, s16 *, 0x86) = 0x40;
    func_8004B354(arg0, 0);
    M2C_FIELD(arg0, s16 *, 0x68) = 0x92;
}


void func_80113014(s32 arg0) {
    func_8007778C();
    func_8004B374(arg0, 0);
}


void func_80113044(void *arg0) {
    M2C_FIELD(arg0, s8 *, 3) = 0xF;
    func_8004A828();
    func_8004B354(arg0, 0);
    M2C_FIELD(arg0, s8 *, 0xB) = 0x10;
    M2C_FIELD(arg0, s8 *, 3) = 9;
    M2C_FIELD(arg0, s8 *, 0) = 1;
}


void func_80113094(void *arg0) {
    M2C_FIELD(arg0, s8 *, 1) = 1;
    func_80077EFC();
    func_8004B374(arg0, 0);
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_801130CC);

extern u8 D_800BFA06;
void func_801132B8(void *arg0) {
    u8 temp_v1;
    void *temp_s1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 5);
    temp_s1 = M2C_FIELD(M2C_FIELD(arg0, void **, 0x10), void **, 0xC0);
    switch (temp_v1) {                              /* irregular */
    case 0:
        if (D_800BFA06 & 2) {
            M2C_FIELD(arg0, u8 *, 5) = 3U;
        } else {
            M2C_FIELD(arg0, u8 *, 5) = 1U;
        }
        M2C_FIELD(arg0, s8 *, 0) = 1;
        func_8004B354(arg0, 1);
        M2C_FIELD(arg0, s16 *, 0xB8) = 0x1800;
        M2C_FIELD(arg0, s16 *, 0xBA) = 0x1800;
        M2C_FIELD(arg0, s16 *, 0xBC) = 0x1800;
        break;
    case 1:
        if (D_800BFA06 & 2) {
            M2C_FIELD(arg0, u8 *, 5) = 2U;
            M2C_FIELD(arg0, s8 *, 6) = 0;
        }
        break;
    case 2:
        if (func_801130CC(arg0) != 0) {
            M2C_FIELD(arg0, u8 *, 5) = (u8) (M2C_FIELD(arg0, u8 *, 5) + 1);
        }
        break;
    }
    M2C_FIELD(arg0, u16 *, 0x2E) = (u16) M2C_FIELD(temp_s1, u16 *, 0x2C);
    M2C_FIELD(arg0, s16 *, 0x32) = (s16) (M2C_FIELD(temp_s1, u16 *, 0x30) - 0x48);
    M2C_FIELD(arg0, u16 *, 0x36) = (u16) M2C_FIELD(temp_s1, u16 *, 0x34);
    if (func_8007778C(arg0) != 0) {
        func_80051844(arg0);
        func_8004B374(arg0, 1);
    }
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_801133F4);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80113490);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80113554);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80113710);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_801139D4);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80113B40);

void func_801139D4();
void f_UpdatePipeAreaBridgeActor();

u8 *func_80113CB4(u8 *a) {
    u8 *p = func_80072DDC((s32)a, 0, 3, 0xF);

    if (p != NULL) {
        M2C_FIELD(p, void **, 0x1C) = func_801139D4;
        p[3] = 0;
    }
    M2C_FIELD(a, u8 **, 0x14) = p;
    return p;
}


u8 *func_80113D04(s32 a) {
    u8 *p = func_80072DDC(a, 0, 3, 15);

    if (p != NULL) {
        M2C_FIELD(p, void **, 0x1C) = func_80113B40;
        p[0x3] = 0;
    }
    return p;
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80113D44);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80113EB8);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80114018);

INCLUDE_ASM("asm/a01/nonmatchings/a01", f_UpdateCoalMiningTownEntranceOpeningSequence);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80114380);

INCLUDE_ASM("asm/a01/nonmatchings/a01", f_UpdateTurboTrolleyLiftSequence);

INCLUDE_ASM("asm/a01/nonmatchings/a01", f_UpdateQuickTrolleyDescentSequence);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80114A28);

INCLUDE_ASM("asm/a01/nonmatchings/a01", f_UpdatePipeAreaTrolleyCutscene);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80114E50);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80115088);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80115278);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80115428);

INCLUDE_ASM("asm/a01/nonmatchings/a01", f_UpdatePipeAreaScenePropActor);


void func_80115BF4(s32 arg0) {
    if (func_8007778C() != 0) {
        func_80051844(arg0);
        func_8004B374(arg0, 1);
    }
}


void func_80115C34(u8 *a)
{
    if (func_80051B70(a, 0xC, 0x1F) == 0) {
        *(s16 *)(a + 0x54) = 0;
        *(s16 *)(a + 0x56) = 0;
        *(s16 *)(a + 0x58) = 0;
    }
}


void func_80115C74(void *arg0) {
    func_800517F8();
    M2C_FIELD(arg0, s8 *, 1) = 1;
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80115CA0);

extern s8 D_800BF9FB;
void func_80115D0C(void *arg0) {
    func_80051B04(M2C_FIELD(arg0, s32 *, 0xC0), 0xC, 0x31);
    func_80051B04(M2C_FIELD(arg0, s32 *, 0xC4), 0xC, 0x32);
    func_80051B04(M2C_FIELD(arg0, s32 *, 0xC8), 0xC, 0x32);
    func_80051B04(M2C_FIELD(arg0, s32 *, 0xCC), 0xC, 0x33);
    func_80051B04(M2C_FIELD(arg0, s32 *, 0xD0), 0xC, 0x33);
    D_800BF9FB = 0;
}

void func_8012AF08();
void f_UpdatePipeAreaQuestSceneryActor();
void func_8011F7CC();
void func_8013362C();
void func_8011A27C();

u8 *func_80115D84(s32 a) {
    u8 *p = func_8007A980(1, 3, 1);

    if (p == NULL) {
        return NULL;
    }
    p[0x2] = 16;
    p[0x3] = 5;
    M2C_FIELD(p, void **, 0x1C) = f_UpdatePipeAreaScenePropActor;
    M2C_FIELD(p, s32 *, 0x10) = a;
    return p;
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80115DE0);

extern u8 D_800BF9FD;
extern u8 *D_800F2738;

void func_80115EC0(u8 *a) {
    if (func_80051B70(a, 0xC, 0x44) == 0) {
        M2C_FIELD(a, s16 *, 0x60) = a[2];
        a[2] = 0x10;
        func_800517F8(a);
    }
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80115F08);


u8 *func_80115F70(s32 a0) {
    u8 *p = func_80072DDC(a0, 2, 4, 0x12);

    if (p != NULL) {
        M2C_FIELD(p, void **, 0x1C) = f_UpdatePipeAreaScenePropActor;
        p[3] = 7;
    }
    return p;
}


void func_80115FB4(u8 *a)
{
    func_80051B70(a, 0xC, 0x4A);
    *(s16 *)(a + 0x54) = 0;
    *(s16 *)(a + 0x56) = 0;
    *(s16 *)(a + 0x58) = 0;
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80115FEC);


u8 *func_801160A4(s32 a, s32 b) {
    u8 *p = func_80072DDC(a, 0, 3, 16);

    if (p != NULL) {
        M2C_FIELD(p, void **, 0x1C) = f_UpdatePipeAreaScenePropActor;
        p[0x3] = 9;
        p[0x5E] = b;
    }
    return p;
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_801160F8);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80116194);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80116294);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8011638C);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80116620);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80116740);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80116994);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80117188);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80117290);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_801175D0);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80117A00);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80117BCC);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80118070);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80118F90);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80119104);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80119320);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80119778);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_801199DC);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80119AAC);

extern s8 D_1F800160[];
extern s8 D_1F800164[];

s32 func_80119B80(s32 arg0, s32 arg1) {
    return (u32) (((arg1 - func_800782B0(arg0 + 0x2C, *((s16 *)D_1F800160), *((s16 *)D_1F800164))) + 0x400) & 0xFFF) >= 0x801U;
}

extern s16 D_1F800160_71b4;
extern s16 D_1F800164_d75f;

s32 func_80119BCC(u8 *a) {
    u8 *q = a + 0x60;
    s32 h = M2C_FIELD(q, u16 *, 4);
    s8 r;

    r = (u32)((h - func_800782B0(a + 0x2C, D_1F800160_71b4, D_1F800164_d75f) + 0x400) & 0xFFF) > 0x800;
    if (r) {
        M2C_FIELD(q, u16 *, 6) |= 1;
    } else {
        M2C_FIELD(q, u16 *, 6) &= 0xFFFE;
    }
    return r;
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80119C4C);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80119CD4);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80119D84);


s32 func_80119E28(void) {
    return D_80135BE8[(func_8009A450() >> 8) & 0xF];
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80119E60);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80119F10);


s32 func_80119F94(void) {
    return D_80135C38[func_8009A450() & 0xF];
}


s32 func_80119FC8(u8 *a) {
    switch (a[3]) {
    case 3:
        return -0x1401;
    case 4:
        return -0x1280;
    }
}

extern u8 D_800BF8BF;

s32 func_80119FF8(u8 *a) {
    switch (a[3]) {
    case 3:
        return -0x18FA;
    case 4:
        if (D_800BF8BF == 0xFF) {
            return -0x1280;
        }
        return -0x1B58;
    }
}

extern u8 D_800E7FE4;
extern u16 D_1F800160_3621;
extern u16 D_1F800162;

s32 func_8011A03C(u8 *a) {
    if (D_800E7FE4 != 1) {
        return 0;
    }
    switch (a[3]) {
    case 3:
        return (u16)(D_1F800160_3621 - 0x42CD) < 0x383;
    case 4:
        return D_1F800164_d75f < 0x1A90;
    }
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8011A0A0);

extern u8 D_800BF9EB;
extern M2C_UNK D_80135D20;
void func_8011A168(void *arg0) {
    u8 temp_s1;
    void *temp_v0;

    temp_s1 = M2C_FIELD(arg0, u8 *, 5);
    switch (temp_s1) {                              /* irregular */
    case 0:
        if (M2C_FIELD(arg0, u8 *, 0x70) == 0xFF) {
            M2C_FIELD(arg0, u8 *, 5) = 1U;
        }
        break;
    case 1:
        temp_v0 = M2C_FIELD(arg0, void **, 0x14);
        M2C_FIELD(arg0, s16 *, 0x56) = (s16) (func_80085690(M2C_FIELD(arg0, s16 *, 0x36) - M2C_FIELD(temp_v0, s16 *, 0x36), M2C_FIELD(temp_v0, s16 *, 0x2E) - M2C_FIELD(arg0, s16 *, 0x2E)) & 0xFFF);
        if (D_800BF9EB == temp_s1) {
            func_80040D68(arg0, &D_80135D20);
            M2C_FIELD(arg0, u8 *, 0x70) = 2U;
            M2C_FIELD(arg0, u8 *, 5) = (u8) (M2C_FIELD(arg0, u8 *, 5) + 1);
        }
        break;
    case 2:
        if (M2C_FIELD(arg0, u8 *, 0x70) == 0xFF) {
            M2C_FIELD(arg0, s8 *, 4) = 3;
        }
        break;
    }
    M2C_FIELD(arg0, s8 *, 1) = 1;
    func_80077E7C(arg0);
    func_80041098(arg0);
    func_8004190C(arg0);
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8011A27C);


u8 *func_8011A43C(s32 a, s32 b) {
    u8 *p = func_8007A980(3, 9, 0);

    if (p == NULL) {
        return NULL;
    }
    p[0x2] = 1;
    p[0x3] = b;
    M2C_FIELD(p, void **, 0x1C) = func_8011A27C;
    M2C_FIELD(p, s32 *, 0x14) = a;
    p[0x28] = (p[0x28] | 0x80);
    return p;
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8011A4AC);

INCLUDE_ASM("asm/a01/nonmatchings/a01", f_UpdateKainenActor);


s32 func_8011A984(s32 a0) {
    u8 *p = func_80072DDC(a0, 1, 3, 0x10);

    if (p != NULL) {
        M2C_FIELD(p, void **, 0x1C) = f_UpdatePipeAreaScenePropActor;
        p[3] = 8;
    }
    return 1;
}

extern u8 D_8013995C[];
extern u8 D_80135D88[];

s32 func_8011A9C8(u8 *p) {
    switch (p[6]) {
    case 0:
        if (p[0x2B] == 3) {
            p[6] = 1;
            func_80042354(1, 1);
        }
        break;
    case 1:
        p[6] = 2;
        func_80040CDC(p, D_8013995C, D_80135D88);
        p[0x70] = 1;
        break;
    case 2:
        func_80041098(p);
        if (p[0x70] == 0xFF) {
            p[6] = 0;
            func_80042310();
            return 1;
        }
        break;
    }
    return 0;
}

extern u8 D_80135F24[];
typedef struct { s16 m[3][3]; s16 pad; s32 t[3]; } AreaMatrix;
typedef struct { s16 x, y, z, pad; } AreaSVec;
typedef struct { u8 pad[0x28]; AreaMatrix m; } AreaScratchD0;

s32 func_8011AAA4(u8 *p) {
    switch (p[6]) {
    case 0:
        if (p[0x2B] == 3) {
            p[6] = 1;
            func_80042354(1, 1);
        }
        break;
    case 1:
        p[6] = 2;
        func_80040CDC(p, D_8013995C, D_80135F24);
        p[0x70] = 1;
        break;
    case 2:
        func_80041098(p);
        if (p[0x70] == 0xFF) {
            p[6] = 0;
            func_80042310();
            return 1;
        }
        break;
    }
    return 0;
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8011AB80);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8011ADA0);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8011AE9C);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8011AFF0);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8011B100);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8011B268);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8011B3EC);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8011B594);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8011B6B0);

INCLUDE_ASM("asm/a01/nonmatchings/a01", f_UpdateCapperActor);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8011BDC4);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8011BED0);

void func_8011BED0();

void func_8011C06C(u8 *a) {
    u8 *p = func_80072DDC((s32)a, 0, 3, 0x13);

    if (p != NULL) {
        M2C_FIELD(p, void **, 0x1C) = func_8011BED0;
        p[3] = 0;
        M2C_FIELD(p, s16 *, 0x60) = a[3];
        M2C_FIELD(p, s16 *, 0x2E) = M2C_FIELD(a, s16 *, 0x2E);
        M2C_FIELD(p, s16 *, 0x32) = M2C_FIELD(a, s16 *, 0x32);
        M2C_FIELD(p, s16 *, 0x36) = M2C_FIELD(a, s16 *, 0x36);
        p[0x5E] = 0;
        M2C_FIELD(a, u8 **, 0x14) = p;
    }
}


void func_8011C0E8(u8 *a) {
    u8 *g = D_800E7E80;
    s16 dz = M2C_FIELD(g, s16 *, 0x36) - M2C_FIELD(a, s16 *, 0x36);
    s16 dx = M2C_FIELD(g, s16 *, 0x2E) - M2C_FIELD(a, s16 *, 0x2E);

    a[0xBE] = func_80077768((s16)func_80085690(-dz, dx), M2C_FIELD(a, s16 *, 0x60), 0);
}


void func_8011C158(u8 *a) {
    switch (a[0x5E]) {
    case 0:
        if (a[3] == 1) {
            M2C_FIELD(a, s16 *, 0x84) = 0x320;
        } else {
            M2C_FIELD(a, s16 *, 0x84) = 0xA0;
        }
        break;
    case 1:
        M2C_FIELD(a, s16 *, 0x84) = 0x78;
        break;
    }
    M2C_FIELD(a, s16 *, 0x86) = M2C_FIELD(a, s16 *, 0x84);
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8011C19C);


void func_8011C270(s32 arg0)
{
  void *temp_v1;
  temp_v1 = *((void **) (((signed char *) arg0) + 0x10));
  if (temp_v1)
  {
  }
  if (temp_v1 != 0)
  {
    *((s8 *) (((signed char *) temp_v1) + 4)) = 3;
    *((void **) (((signed char *) arg0) + 0x10)) = 0;
  }
  return 3;
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8011C290);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8011C314);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8011C3C0);


void func_8011C46C(u8 *a) {
    a[0] = 1;
    a[4] = 1;
    a[5] = 1;
    a[6] = 0;
    if (func_800778E4(a, (s16)(D_1F800162 - M2C_FIELD(a, u16 *, 0x32))) != 0) {
        func_800517F8(a);
    }
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8011C4D0);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8011C6E4);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8011C854);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8011C998);

INCLUDE_ASM("asm/a01/nonmatchings/a01", f_UpdateAnemoneCaptureSequence);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8011CF9C);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8011D104);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8011D2C4);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8011D540);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8011D754);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8011D8C8);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8011D9E4);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8011DBA4);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8011DC4C);


void func_8011DCE0(u8 *a) {
    if (a[6] == 0) {
        a[0x5E] = 0;
        func_8011DE34(a, 0xF, 2, 3);
        func_80026100(0x10);
        a[6]++;
    }
}


u8 *func_8011DD38(void) {
    u8 *p;

    for (p = D_800F2738; p != NULL; p = M2C_FIELD(p, u8 **, 0x24)) {
        if ((M2C_FIELD(p, u32 *, 0) & 0xFF00FF) == 1) {
            return p;
        }
    }
    return NULL;
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8011DD88);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8011DE34);

typedef struct {
    u8 pad0[0x38];
    u8 *p38;
    u8 pad3C[0x24];
    s16 h60[0x34];
    u8 *pC8;
} ActorDF;

s16 func_8011DF24(ActorDF *a, s32 i) {
    s32 r = func_80076D68();
    s32 j = i + 1;
    s16 v;

    func_8011D9E4(a, j);
    if (a->h60[j] != 2) {
        a->h60[i] = 0;
    } else {
        v = *(s16 *)(a->p38 + 4) >> 4;
        if (v != a->h60[i]) {
            func_80051B04(a->pC8, 0x15, v);
            a->h60[i] = v;
        }
    }
    return r;
}


void func_8011DFEC(u8 *a) {
    u8 *p = func_8003116C(0x201, a + 0x2C, 0);

    if (p != NULL) {
        M2C_FIELD(p, u8 **, 0x10) = a;
        M2C_FIELD(a, u8 **, 0x10) = p;
        p[7] = 0;
        M2C_FIELD(p, s16 *, 0x2E) -= 0x30;
    }
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8011E040);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8011E0C0);

extern M2C_UNK D_8013618C;
extern M2C_UNK D_801361B4;
extern M2C_UNK D_801393C0;
void func_8011E1D4(void *arg0) {
    M2C_UNK *var_a2;
    u8 temp_v1;

    if (func_8007778C() != 0) {
        temp_v1 = M2C_FIELD(arg0, u8 *, 5);
        switch (temp_v1) {                          /* irregular */
        case 0:
            if (M2C_FIELD(arg0, u8 *, 0x2B) == 3) {
                func_80042354(1, 1);
                func_80070724(1, 0, 0x9A);
                if (D_800BF870.pad1[0x247] != 0) {
                    var_a2 = &D_8013618C;
                    if (D_800BF870.pad1[0x4C] != 0xFF) {
                        M2C_FIELD(arg0, s8 *, 0x7A) = 0x11;
                    } else if (!(M2C_FIELD(&D_800BF870, u16 *, 0x5E6) & 4)) {
                        M2C_FIELD(arg0, s8 *, 0x7A) = 0x12;
                    } else {
                        M2C_FIELD(arg0, s8 *, 0x7A) = 0x13;
                    }
                } else if (D_800BF870.pad1[0x4C] != 0) {
                    var_a2 = &D_8013618C;
                    M2C_FIELD(arg0, s8 *, 0x7A) = 0x10;
                } else {
                    var_a2 = &D_801361B4;
                }
                func_80040CDC(arg0, &D_801393C0, var_a2);
                M2C_FIELD(arg0, u8 *, 0x70) = 2U;
                M2C_FIELD(arg0, u8 *, 5) = (u8) (M2C_FIELD(arg0, u8 *, 5) + 1);
            }
            func_80076D68(arg0);
            return;
        case 1:
            if (M2C_FIELD(arg0, u8 *, 0x70) == 0xFF) {
                M2C_FIELD(arg0, u8 *, 5) = 0U;
            }
            func_80041098(arg0);
            func_8004190C(arg0);
            break;
        }
    }
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8011E324);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8011E404);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8011E6D0);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8011E804);

extern u8 D_800A3D40[];

void func_8011E9E8(u8 *a) {
    if (a[0x2B] == 3) {
        func_80040D68(a, D_800A3D40);
        a[0x70] = 1;
        if (a[0x5E] == 4 || a[0x5E] == 6) {
            func_80042354(1, 3);
        } else {
            func_80042354(1, 1);
        }
        a[5] = 1;
    }
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8011EA60);


s32 func_8011EAE4(void *arg0) {
    M2C_FIELD(arg0, s8 *, 5) = 2;
    M2C_FIELD(arg0, s8 *, 6) = 2;
    M2C_FIELD(arg0, s8 *, 0x5E) = 4;
    return 1;
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8011EB00);

extern s8 D_1F800164[];
extern s8 D_1F800207[];
extern M2C_UNK D_80136808;
extern M2C_UNK D_8013687C;

void func_8011ECFC(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 5);
    switch (temp_v1) {                              /* irregular */
    case 0:
        func_8007778C(arg0);
        if (D_800BF8BF != 0) {
            M2C_FIELD(arg0, u8 *, 5) = 1U;
        } else if ((M2C_FIELD(arg0, u8 *, 1) != 0) && (*((u8 *)D_1F800207) == 0x10) && (*((s16 *)D_1F800164) >= 0x399E) && (func_8005308C() != 0)) {
            func_80042354(1, 1);
            func_80040D68(arg0, &D_8013687C);
            M2C_FIELD(arg0, u8 *, 0x70) = 2U;
            M2C_FIELD(arg0, u8 *, 5) = 2U;
        }
        break;
    case 1:
        func_8007778C(arg0);
        if (D_800BF870.pad1[0x4E] == 0xFF) {
            M2C_FIELD(arg0, u8 *, 5) = 0U;
            M2C_FIELD(arg0, s8 *, 0xBF) = 1;
        } else if ((M2C_FIELD(arg0, u8 *, 1) != 0) && (M2C_FIELD(arg0, u8 *, 0x2B) == 3)) {
            func_80042354(1, 1);
            if (D_800BF870.pad1[0x17F] & 1) {
                M2C_FIELD(arg0, s8 *, 0x7A) = 1;
            } else {
                D_800BF870.pad1[0x17F] |= 1;
                M2C_FIELD(arg0, s8 *, 0x7A) = 0;
            }
            func_80040D68(arg0, &D_80136808);
            M2C_FIELD(arg0, u8 *, 0x70) = 2U;
            M2C_FIELD(arg0, u8 *, 5) = (u8) (M2C_FIELD(arg0, u8 *, 5) + 1);
        }
        break;
    case 2:
        if (M2C_FIELD(arg0, u8 *, 0x70) == 0xFF) {
            M2C_FIELD(arg0, u8 *, 5) = 1U;
        }
        M2C_FIELD(arg0, u8 *, 1) = 1U;
        func_80077E7C(arg0);
        break;
    }
    func_80041098(arg0);
    func_8004190C(arg0);
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", f_UpdateGranRemoveCappersDialogue);

INCLUDE_ASM("asm/a01/nonmatchings/a01", f_UpdateGranPostPipeAreaDialogue);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8011F2A4);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8011F4B8);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8011F7CC);


u8 *func_8011FB2C(s32 a, s32 b) {
    u8 *p = func_8007A980(3, 9, 0);

    if (p == NULL) {
        return NULL;
    }
    p[0x2] = 22;
    p[0x3] = b;
    M2C_FIELD(p, void **, 0x1C) = func_8011F7CC;
    return p;
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8011FB80);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8011FC88);

INCLUDE_ASM("asm/a01/nonmatchings/a01", f_HandleThirstyMinerInteraction);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8011FEF8);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80120200);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80120308);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80120420);

extern void *D_80137114[];

void func_80120508(u8 *a)
{
    if (a[0x71] == 0xFF) {
        func_80040D68(a, D_80137114[a[0x5E]]);
        a[5] = 2;
        a[0x70] = 1;
    }
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", f_ReturnThirstyMinerToIdleScript);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_801205E4);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_801206D8);


s32 func_801207DC(void) {
    if (M2C_FIELD(D_800BF844, s16 *, 0x68) == 0x62) {
        return 3;
    }
    return 2;
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80120804);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_801208B4);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80120C34);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80120DA0);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80120F00);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_801210A4);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_801213F4);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80121678);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80121BAC);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80121F54);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8012212C);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_801222FC);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80122A2C);


void func_80122ADC(s32 arg0) {
    void *temp_a1;

    temp_a1 = M2C_FIELD(arg0, void **, 0x10);
    if (temp_a1 != NULL) {
        M2C_FIELD(temp_a1, u16 *, 0x2C) = (u16) M2C_FIELD(arg0, u16 *, 0x2E);
        M2C_FIELD(temp_a1, s16 *, 0x2E) = (s16) (M2C_FIELD(arg0, u16 *, 0x32) + M2C_FIELD(arg0, u16 *, 0x72));
        M2C_FIELD(temp_a1, u16 *, 0x30) = (u16) M2C_FIELD(arg0, u16 *, 0x36);
    }
}


void func_80122B20(s32 arg0)
{
  void *temp_v1;
  ;
  if ((*((void **) (((signed char *) arg0) + 0x10))) != 0)
  {
    *((s8 *) (((signed char *) (*((void **) (((signed char *) arg0) + 0x10)))) + 4)) = 3;
    *((void **) (((signed char *) arg0) + 0x10)) = 0;
    *((s8 *) (((signed char *) arg0) + 0x5E)) = 0;
  }
  return 3;
}


void func_80122B44(void *arg0, M2C_UNK arg1) {
    func_80051B04(M2C_FIELD(arg0, s32 *, 0xC0), 0xC, arg1);
    M2C_FIELD(arg0, s16 *, 0xE) = 0;
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80122B78);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80122C08);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80122CAC);


s32 func_80122D4C(u8 *a) {
    return func_8004954C(a, M2C_FIELD(a, s16 *, 0x80), -0x5A) != 0;
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80122D70);


s32 func_80122E3C(u8 *a) {
    u8 *g = D_800E7E80;
    s16 dz = M2C_FIELD(g, s16 *, 0x36) - M2C_FIELD(a, s16 *, 0x36);
    s16 dx = M2C_FIELD(g, s16 *, 0x2E) - M2C_FIELD(a, s16 *, 0x2E);

    return func_80077768((s16)func_80085690(-dz, dx), M2C_FIELD(a, s16 *, 0x60), 0);
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80122EA8);


void func_80122F80(u8 *a, s32 b) {
    if (a[0xBE] == 0) {
        M2C_FIELD(a, s16 *, 0x44) = b;
    } else {
        M2C_FIELD(a, s16 *, 0x44) = -b;
    }
    func_8004130C(a, 0);
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80122FBC);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80123078);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8012322C);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_801233A8);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8012364C);

INCLUDE_ASM("asm/a01/nonmatchings/a01", f_UpdatePipeAreaPersistentSceneryRewardActor);


void func_80123A48(u8 *a) {
    u8 *p = func_8003116C(0x201, 0, 0);

    if (p != NULL) {
        M2C_FIELD(p, u8 **, 0x10) = a;
        p[7] = 0;
    }
    M2C_FIELD(a, u8 **, 0x14) = p;
    M2C_FIELD(a, s16 *, 0x80) = 0x64;
    M2C_FIELD(a, s16 *, 0x82) = 0xC8;
    M2C_FIELD(a, s16 *, 0x84) = 0x100;
    M2C_FIELD(a, s16 *, 0x86) = 0x100;
    a[0x5E] = 0;
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80123AAC);


void func_80123B40(void *arg0) {
    u8 temp_v0;
    void *temp_v1;
    void *temp_v1_2;

    temp_v1 = M2C_FIELD(arg0, void **, 0x10);
    M2C_FIELD(arg0, u16 *, 0x2E) = (u16) M2C_FIELD(temp_v1, u16 *, 0x2E);
    M2C_FIELD(arg0, u16 *, 0x32) = (u16) M2C_FIELD(temp_v1, u16 *, 0x32);
    M2C_FIELD(arg0, u16 *, 0x36) = (u16) M2C_FIELD(temp_v1, u16 *, 0x36);
    temp_v0 = M2C_FIELD(temp_v1, u8 *, 1);
    M2C_FIELD(arg0, u8 *, 1) = temp_v0;
    if (temp_v0 & 0xFF) {
        func_80077E7C();
    }
    temp_v1_2 = M2C_FIELD(arg0, void **, 0x14);
    M2C_FIELD(temp_v1_2, u16 *, 0x2C) = (u16) M2C_FIELD(arg0, u16 *, 0x2E);
    M2C_FIELD(temp_v1_2, s16 *, 0x2E) = (s16) (M2C_FIELD(arg0, u16 *, 0x32) - 0x40);
    M2C_FIELD(temp_v1_2, u16 *, 0x30) = (u16) M2C_FIELD(arg0, u16 *, 0x36);
}


void func_80123BD8(void) {
    func_8007778C();
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80123BF8);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80123CFC);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80123F28);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80123FF8);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80124164);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80124250);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_801244E4);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8012464C);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_801247C8);

INCLUDE_ASM("asm/a01/nonmatchings/a01", f_UpdateMythicalTowerEntranceTransition);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80124CF8);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80124F14);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_801250B8);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80125214);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80125304);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8012540C);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80125548);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_801256EC);

INCLUDE_ASM("asm/a01/nonmatchings/a01", f_UpdatePipeAreaEntranceAndDoorActor);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80126140);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8012623C);


void func_80126354(s32 arg0) {
    func_80073328();
    func_800735F4(arg0, 0x52);
}


void func_80126384(u8 *a) {
    if (((D_800BF9FD >> 2) & 3) == 3) {
        a[0x5E] = 1;
        a[5] = 0;
        a[6] = 0;
        a[7] = 0;
    } else {
        func_800735F4(a, 0x4A);
    }
}


void func_801263D4(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 5) == 0) {
        M2C_FIELD(arg0, u8 *, 5) = 1U;
        M2C_FIELD(arg0, u16 *, 0x32) = (u16) M2C_FIELD(arg0, u16 *, 0x8A);
    }
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_801263F8);

extern u8 D_800E7FF4;
void func_801264B4(s32 arg0) {
    if (D_800E7FF4 & 4) {
        func_80073328();
    }
    func_800735F4(arg0, 0x67);
}

extern u16 D_1F80017C;
extern u8 D_800BF916;

void f_UpdateMythicalTowerEntranceEffect(u8 *a) {
    switch (a[0x5E]) {
    case 0:
        switch (a[5]) {
        case 0:
            if (D_800BF916 == 1) {
                a[5] = 1;
                func_800313A0(0x20A, a + 0x2C, -0x20, a + 0x54);
                func_80074590(0xD, -0x1D, 0);
            }
            break;
        case 1:
            if (D_800BF916 >= 2) {
                a[0x5E] = 1;
                a[5] = 0;
            }
            if (!(D_1F80017C & 0xF)) {
                func_80074590(0xD, -0x1D, 0);
            }
            break;
        }
        a[1] = 0;
        break;
    case 1:
        f_UpdateMythicalTowerEntranceTransition(a);
        func_800735F4(a, 0x6A);
        break;
    case 2:
        func_80124CF8(a);
        func_800735F4(a, 0x6A);
        break;
    }
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80126608);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_801267E8);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80126A80);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80126C1C);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80126D50);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80126EB0);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80126F60);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8012702C);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80127298);


void func_801273AC(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 4);
    switch (temp_v1) {                              /* irregular */
    case 0:
        if (func_80051B70(arg0, 0xC, 3) == 0) {
            M2C_FIELD(arg0, s8 *, 0xB) = 0;
            M2C_FIELD(arg0, u8 *, 0xD) = (u8) (M2C_FIELD(arg0, u8 *, 0xD) | 4);
            M2C_FIELD(M2C_FIELD(arg0, void **, 0xC0), s8 *, 0x3F) = 0x40;
            M2C_FIELD(arg0, s8 *, 0x29) = 0;
            M2C_FIELD(arg0, s8 *, 0x2B) = 0;
            M2C_FIELD(arg0, s8 *, 0x5E) = 0;
            M2C_FIELD(arg0, s16 *, 0x4A) = 0;
            M2C_FIELD(arg0, s16 *, 0x60) = 0;
            M2C_FIELD(arg0, u8 *, 4) = (u8) (M2C_FIELD(arg0, u8 *, 4) + 1);
        }
        M2C_FIELD(arg0, s16 *, 0x2E) = 0x4180;
        M2C_FIELD(arg0, s16 *, 0x32) = -0x19F2;
        M2C_FIELD(arg0, s16 *, 0x36) = 0x2340;
        func_800517F8(arg0);
        return;
    case 1:
        func_8012702C(arg0);
        return;
    case 3:
        func_8007A624(arg0);
        /* fallthrough */
    case 2:
        return;
    }
}


void func_8012749C(u8 *a) {
    if (func_80051B70(a, 0xC, 3) == 0) {
        a[0xB] = 0;
        a[0xD] |= 4;
        M2C_FIELD(a, u8 **, 0xC0)[0x3F] = 0x40;
        a[0x29] = 0;
        a[0x2B] = 0;
        a[0x5E] = 0;
        M2C_FIELD(a, s16 *, 0x4A) = 0;
        M2C_FIELD(a, s16 *, 0x60) = 0;
        a[4]++;
    }
}


void func_8012750C(u8 *a) {
    u8 *p;

    a[0x47] = 0;
    p = func_80072DDC((s32)a, 1, 4, 0x15);
    if (p != NULL) {
        M2C_FIELD(p, void **, 0x1C) = f_UpdatePipeAreaBridgeActor;
        M2C_FIELD(a, u8 **, 0x3C) = p;
    }
    func_80126608(a);
}


void func_80127560(void *arg0) {
    M2C_FIELD(arg0, s16 *, 0x2E) = 0x4180;
    M2C_FIELD(arg0, s16 *, 0x32) = -0x19F2;
    M2C_FIELD(arg0, s16 *, 0x36) = 0x2340;
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8012757C);

INCLUDE_ASM("asm/a01/nonmatchings/a01", f_UpdatePipeAreaBridgeMotion);

INCLUDE_ASM("asm/a01/nonmatchings/a01", f_UpdatePipeAreaBridgeRevealCamera);

INCLUDE_ASM("asm/a01/nonmatchings/a01", f_UpdatePipeAreaBridgeActor);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80127DC4);

INCLUDE_ASM("asm/a01/nonmatchings/a01", f_UpdatePipeAreaMudballSurpriseCarrierActor);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8012866C);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_801286F4);


s32 func_801287D0(void *arg0, s32 arg1) {
    s32 var_a0;

    var_a0 = 0;
    if ((M2C_FIELD(arg0, s16 *, 0x32) >= -0x7CF) && !(((s32) D_800BF870.pad1[0x18B] >> arg1) & 1)) {
        var_a0 = func_80112948(arg0);
        D_800BF870.pad1[0x18B] |= 1 << arg1;
        M2C_FIELD(arg0, s8 *, 0xBF) = 2;
    }
    return var_a0;
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80128864);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80128B08);

extern AreaSVec D_1F8000C0;
extern AreaScratchD0 D_1F8000D0;
extern AreaMatrix D_1F800000;

void func_80129114(u8 *a) {
    D_1F8000C0.x = M2C_FIELD(M2C_FIELD(a, u8 **, 0xC0), s16 *, 0x2C);
    D_1F8000C0.y = M2C_FIELD(M2C_FIELD(a, u8 **, 0xC0), s16 *, 0x30);
    D_1F8000C0.z = M2C_FIELD(M2C_FIELD(a, u8 **, 0xC0), s16 *, 0x34);
    func_80084110(&D_1F8000D0.m, M2C_FIELD(a, u8 **, 0xC0) + 0x18, &D_1F800000);
    func_80084220(&D_1F8000C0, D_1F800000.t);
    D_1F800000.t[0] += D_1F8000D0.m.t[0];
    D_1F800000.t[1] += D_1F8000D0.m.t[1];
    D_1F800000.t[2] += D_1F8000D0.m.t[2];
    func_80084660(&D_1F800000);
    func_80084690(&D_1F800000);
    func_80128B08(a);
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_801291F4);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80129394);

INCLUDE_ASM("asm/a01/nonmatchings/a01", f_UpdatePullAndOpenGateSegmentTransform);

INCLUDE_ASM("asm/a01/nonmatchings/a01", f_UpdatePullAndOpenGateSegment);

INCLUDE_ASM("asm/a01/nonmatchings/a01", f_SynchronizePullAndOpenGateAssembly);

INCLUDE_ASM("asm/a01/nonmatchings/a01", f_UpdatePipeAreaInteractiveSceneryActor);

void f_UpdatePipeAreaMudballSurpriseCarrierActor();

void func_8012AB50(u8 *a) {
    u8 t;
    u8 *p = func_8007A980(2, 4, 0);

    if (p != NULL) {
        M2C_FIELD(p, void **, 0x1C) = f_UpdatePipeAreaMudballSurpriseCarrierActor;
        p[0x2] = 22;
        t = a[3];
        M2C_FIELD(p, u8 **, 0x10) = a;
        p[0x3] = t;
        p[0x2A] = a[0x2A];
    }
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8012ABB4);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8012AC84);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8012AF08);


u8 *func_8012B2D8(void) {
    u8 *p = func_8007A980(1, 4, 0);

    if (p == NULL) {
        return NULL;
    }
    p[0x2] = 29;
    p[0x3] = 0;
    M2C_FIELD(p, void **, 0x1C) = func_8012AF08;
    return p;
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8012B324);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8012B464);


void func_8012B5CC(void *arg0) {
    M2C_FIELD(arg0, s16 *, 0x80) = 0x12C;
    M2C_FIELD(arg0, s16 *, 0x82) = 0x258;
    M2C_FIELD(arg0, s16 *, 0x84) = 0x1F4;
    M2C_FIELD(arg0, s16 *, 0x86) = 0x3E8;
    M2C_FIELD(arg0, s8 *, 0x2A) = 0x10;
    M2C_FIELD(arg0, s32 *, 0x2C) = 0x37400000;
    M2C_FIELD(arg0, s32 *, 0x30) = 0xE6E70000;
    M2C_FIELD(arg0, s32 *, 0x34) = 0x3D540000;
}


void func_8012B610(void *arg0) {
    M2C_FIELD(arg0, s16 *, 0x80) = 0xC8;
    M2C_FIELD(arg0, s16 *, 0x82) = 0x190;
    M2C_FIELD(arg0, s16 *, 0x84) = 0x284;
    M2C_FIELD(arg0, s16 *, 0x86) = 0x508;
    M2C_FIELD(arg0, s8 *, 0x2A) = 0xF;
    M2C_FIELD(arg0, s32 *, 0x2C) = 0x30400000;
    M2C_FIELD(arg0, s32 *, 0x30) = 0xED9C0000;
    M2C_FIELD(arg0, s32 *, 0x34) = 0x3F160000;
}


u8 *func_8012B654(s32 a, s32 b) {
    u8 *p = func_80072DDC(0, 1, 4, 31);

    if (p == NULL) {
        return NULL;
    }
    M2C_FIELD(p, void **, 0x1C) = func_8012B464;
    p[0x3] = b;
    M2C_FIELD(p, s16 *, 0x58) = 0;
    M2C_FIELD(p, s16 *, 0x56) = 0;
    M2C_FIELD(p, s16 *, 0x54) = 0;
    M2C_FIELD(p, s32 *, 0x10) = a;
    p[0x28] = (p[0x28] | 0x80);
    return p;
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8012B6CC);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8012B86C);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8012BA60);

INCLUDE_ASM("asm/a01/nonmatchings/a01", f_UpdatePipeAreaQuestSceneryActor);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8012C18C);


u8 *func_8012C2B4(void) {
    u8 *p = func_8007A980(2, 4, 0);

    if (p == NULL) {
        return NULL;
    }
    p[0x2] = 32;
    p[0x3] = 2;
    M2C_FIELD(p, void **, 0x1C) = f_UpdatePipeAreaQuestSceneryActor;
    return p;
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8012C304);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8012C410);

extern PartPose D_80137A1C[3];
extern PartPose D_80137A34[3];

void func_8012C4F4(PosedActor *a, s32 b, s32 c) {
    s32 i;

    for (i = 0; i < 3; i++) {
        if (b == 0) {
            func_80051B04(a->parts[i], c, i);
            a->parts[i][0] = D_80137A1C[i].x;
            a->parts[i][1] = D_80137A1C[i].y;
            a->parts[i][2] = D_80137A1C[i].z;
        } else {
            func_80051B04(a->parts[i], c, i + 3);
            a->parts[i][0] = D_80137A34[i].x;
            a->parts[i][1] = D_80137A34[i].y;
            a->parts[i][2] = D_80137A34[i].z;
        }
    }
    a->pose = b;
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8012C600);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8012C8C0);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8012CB28);

void func_8012CD00(u8 *a, s32 b) {
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
    if (func_8012CB28(a, b) != 0) {
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

void func_8012CE5C(u8 *a) {
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

extern u8 D_800BF808_1760[];
extern u8 D_1F800236;

void func_8012D0A4(u8 *a) {
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

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8012D2BC);

extern ClutCycle D_80137B3C[];
extern s8 D_80138FF8[];

void func_8012D6B0(s32 arg0) {
    ClutRect r;
    s32 i;
    ClutCycle *e;
    u8 *data;

    if (arg0 == 0) {
        for (i = 0; i < 1; i++) {
            D_80138FF8[i] = 0;
        }
        return;
    }
    e = D_80137B3C;
    for (i = 0; i < 1; i++, e++) {
        if (--D_80138FF8[i] <= 0) {
            if (e->ptr[0] == 0xFF) {
                e->ptr -= e->ptr[1];
            }
            data = e->clut + e->ptr[0] * 32;
            D_80138FF8[i] = e->ptr[1];
            r.x = e->x;
            r.y = e->y;
            r.w = 16;
            r.h = 1;
            func_80081218(&r, data);
            e->ptr += 2;
        }
    }
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8012D7D0);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8012D9E8);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8012E014);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8012E1B4);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8012E370);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8012E4B4);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8012E5F8);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8012E6A0);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8012E74C);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8012E868);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8012E974);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8012EA70);


void func_8012EB1C(u8 *a) {
    switch (a[4]) {
    case 0:
        a[4] = 1;
        M2C_FIELD(a, s32 *, 0x50) = 0;
        M2C_FIELD(a, s16 *, 0x4E) = 0;
        M2C_FIELD(a, s16 *, 0x32) = -50;
    case 1:
        if (D_1F80017C & 1) {
            if (++M2C_FIELD(a, s16 *, 0x4E) == 25) {
                D_800BF916 = 2;
                a[4] = 2;
            }
        }
        a[1] = 1;
        break;
    case 2:
        M2C_FIELD(a, u32 *, 0x50) += 0xCC;
        if (M2C_FIELD(a, u32 *, 0x50) >= 0x1000) {
            a[4] = 3;
        }
        a[1] = 1;
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8012EC08);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8012EC78);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8012ED88);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8012EE14);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8012F188);


s32 func_8012F864(s32 x, s32 y) {
    return D_80138FFC_e406[y * 52 + x] & D_80139000;
}

extern s8 *D_800ECF58[];
extern s8 *D_80138FFC;

void func_8012F89C(u8 *a)
{
    s8 **t = D_800ECF58;
    u16 *p = (u16 *)t[8];
    u16 v;

    *(u16 **)(a + 0xC) = p;
    *(u16 *)(a + 8) = p[0];
    v = p[1];
    a[7] = 0;
    *(u16 *)(a + 0xA) = v;
    D_80138FFC = t[9];
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8012F8D8);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8013000C);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80130838);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80130D9C);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_801311FC);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_801316A8);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80131BB0);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_801321C4);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80132358);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80132690);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_801329C4);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80132DC0);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80132EFC);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80132F5C);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80132FD0);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80133574);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8013362C);


u8 *func_80133900(s32 a) {
    u8 *p = func_8007A980(1, 2, 0);

    if (p == NULL) {
        return NULL;
    }
    M2C_FIELD(p, void **, 0x1C) = func_8013362C;
    M2C_FIELD(p, s32 *, 0x10) = a;
    p[0x2] = 26;
    p[0x3] = 0;
    return p;
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80133958);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80133CAC);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80133D74);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80133F38);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_801341E8);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_801342C8);

INCLUDE_ASM("asm/a01/nonmatchings/a01", f_UpdatePipeAreaTrolleyNpcDialogue);

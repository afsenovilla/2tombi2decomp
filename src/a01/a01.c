#include "common.h"
#include "game.h"
#include "m2c.h"

typedef struct {
    u8 pad[0xD0];
    s32 *p0;
    u8 pad2[8];
    s32 *p1;
} PairOwner;

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80109F7C);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8010A0F0);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8010A32C);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8010A530);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8010AA20);

s32 func_8010AC3C(u8 *a) {
    u8 *p = M2C_FIELD(a, u8 **, 0x158);
    s32 r;

    if (p[0xC] == 4 && p[2] == 0x16) {
        r = func_8010A0F0(a, p);
        if (M2C_FIELD(a, s16 *, 0x32) >= -0xB7B) {
            M2C_FIELD(a, s16 *, 0x16E) = 0;
            func_800232F4(a);
        }
        return r;
    }
    return 0;
}

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

extern u8 D_800E8008[];
extern u8 D_800E7E80[];
extern u8 D_800BF817;
extern u8 D_800BF816;
extern s32 D_1F800184;
void func_8010BAE4(void) {
    u8 *g = D_800E8008;
    u8 *t = D_800E7E80;

    func_80054198(t);
    t[5] = 0x24;
    if (D_800BF817 == 4) {
        t[6] = 6;
    } else if (D_800BF817 == 5) {
        t[6] = 5;
    } else {
        t[6] = 0;
    }
    t[0x16B] = 0;
    D_800BF816 = 0;
    g[0x64] = 0;
    D_1F800184 = 0;
}

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
void func_801103C0(u8 *a, u8 *b) {
    if (func_8010C008(a, b, M2C_FIELD(b, u8 **, 0xC0)) == 2 && D_800BF80D == 0 && !(D_800BFE56 & 2) &&
        M2C_FIELD(a, s16 *, 0x32) >= -0x987) {
        M2C_FIELD(a, s16 *, 0x6A) = -0x7900;
    }
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80110430);

extern u8 *D_1F800080_ddd3;
extern s16 D_1F800166;
extern s16 D_1F800190;
void func_80110504(u8 *a, u8 *b) {
    s32 k = 2;
    u16 t, u;

    if (b[0x47] != k && func_80024BD8(a, b, M2C_FIELD(b, u8 **, 0xC0)) != 0) {
        t = M2C_FIELD(b, u16 *, 0x80);
        b[0x29] = 1;
        u = M2C_FIELD(a, u16 *, 0x80);
        a[0x164] = 1;
        a[0x15C] = 0;
        D_1F800080_ddd3 = b;
        D_1F800182_5650 = 0;
        M2C_FIELD(a, s16 *, 0x152) = t + u - 12;
        if (b[3] >= 11) {
            D_1F800137 = k;
            a[4] = 4;
            D_1F800166 = 0;
            D_1F800190 = 0;
        }
    }
}

void func_801105B8(u8 *a, u8 *b) {
    if (func_80022F04(a, b) != 0) {
        if ((u16)(M2C_FIELD(a, u16 *, 0x84) + (M2C_FIELD(a, u16 *, 0x32) - M2C_FIELD(b, u16 *, 0x32) + 0x78)) <= M2C_FIELD(a, s16 *, 0x86) + 0x78) {
            if (func_8001DC9C(a, b, 0, 1) & 0x80) {
                a[0x2B] = 2;
            }
            D_1F800182_5650 = 0;
        }
    }
}

void func_8011064C(void *a, u8 *b)
{
    if (b[0x47] == 2) {
        func_8010C008(a, b, *(void **)(b + 0xC0));
    } else {
        func_8001F650(a, b, *(void **)(b + 0xC0));
    }
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80110694);

extern s32 D_1F800084;
extern s32 D_1F80008C;
void func_80110788(u8 *a, u8 *b) {
    u8 v;

    if (b[2] == 0x19) {
        v = b[0xBF];
    } else {
        v = b[0x5E];
    }
    if (v == 0 && func_8002300C(a, b, M2C_FIELD(b, s16 *, 0x80) + 0x190) != 0) {
        if (D_1F80008C < D_1F800084) {
            D_1F800084 = D_1F80008C;
            D_1F800080_ddd3 = b;
        }
    }
}

extern u8 D_800BF808_1760[];
void func_8011080C(u8 *a) {
    u8 *g = D_800BF808_1760;
    u16 lim = M2C_FIELD(g, u16 *, 0xA);

    if (g[0xF] == 2) {
        if (M2C_FIELD(a, s16 *, 0x36) >= 0x41E7) {
            lim += 0x28;
        }
    } else if (g[0xF] == 5) {
        if (M2C_FIELD(a, s16 *, 0x2E) < 0x19DF) {
            M2C_FIELD(a, s16 *, 0x2E) = 0x19DF;
        }
    }
    if (!(a[0x145] & 1) && M2C_FIELD(a, s16 *, 0x32) >= (s16)lim - M2C_FIELD(a, s16 *, 0x62)) {
        M2C_FIELD(a, s16 *, 0x32) = lim - M2C_FIELD(a, u16 *, 0x62);
        func_80022C78(a);
        a[0x29] |= 0x80;
    }
}

s32 func_801108D4(u8 *a, u8 *b) {
    if (b[0x5E] != 0) {
        return 0;
    }
    if (func_80022F04(a, b) == 0) {
        return 0;
    }
    if (b[0x5E] == 0) {
        if (func_8001DC9C(a, b, 0, 2) & 0x80) {
            a[0x2B] = 2;
        }
    }
    D_1F800182_5650 = 0;
    return 1;
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80110968);

void func_80110A18(u8 *a, u8 *b) {
    u16 t;

    if (b[0xBF] != 0 && func_80024BD8(a, b, M2C_FIELD(b, u8 **, 0xC0)) != 0) {
        M2C_FIELD(a, s16 *, 0x156) = 20;
        t = M2C_FIELD(b, u16 *, 0x80) + M2C_FIELD(a, u16 *, 0x80);
        a[0x164] = 2;
        D_1F800080_ddd3 = b;
        D_1F800182_5650 = 0;
        M2C_FIELD(a, s16 *, 0x152) = t - 0x28;
    }
}

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

void func_80110B2C(u8 *a, u8 *b) {
    s32 r = func_8001F40C(a, b, 1);

    if (r >= 0) {
        if (a[0x164] == 12) {
            func_8001FF7C(a, b, r, 4);
        } else if (b[3] == 3 || b[3] == 4) {
            func_8001FF7C(a, b, r, 2);
        } else {
            func_8001FF7C(a, b, r, 1);
        }
    }
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80110BB8);

extern u8 D_1F800183;
typedef struct {
    u8 pad0[0xC0];
    s32 xC0[1];
} S11130C;
typedef struct {
    s16 pad0;
    s16 a;
    s16 pad4;
    s16 b;
    s16 pad8;
    s16 c;
} S13AE38;
extern u8 **D_1F800154;
extern u8 D_1F80015C;
typedef struct { u8 pad[0xC0]; u8 *parts[1]; } PartsOwner;
typedef struct { s16 v[4]; } PartInit;
typedef struct { s16 v[5]; } PartInit5;
typedef struct { u8 pad[0x48]; s32 unk48; } AreaState808;
typedef struct { s16 x, y, z; } AreaVec3s;
typedef struct { s16 x, y, z, pad; } AreaSVec;
typedef struct { s16 m[3][3]; s16 pad; s32 t[3]; } AreaMatrix;
typedef struct { u8 pad[0x28]; AreaMatrix m; } AreaScratchD0;
typedef struct { s16 x0; s16 id; u8 k; u8 p5; s16 v6; s16 v8; } Entry10;
typedef struct {
    s16 x, y, w, h;
} RECT16;
typedef struct {
    u8 x[8];
} S8;
typedef struct {
    u8 b[6][4];
} FlickerTbl;
void func_80110CB8(void) {
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
                func_8010EFBC(a);
                break;
            }
        }
    }
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", f_SpawnPipeAreaSceneActorsFromPlacementTable);

// nearcopy: 12 words off, C from a07 func_80113C20
#include "common.h"
#include "game.h"
#include "m2c.h"
#include "psyq/inline_c.h"
extern ClutCycle D_801352CC[];
extern s8 D_80138FD0[];
void func_801112C0(s32 arg0) {
    ClutRect r;
    s32 i;
    ClutCycle *e;
    u8 *data;
    u8 *g = (u8 *)&D_800BF870;

    if (*(u16 *)(g + 0x5E6) & 2) {
        return;
    }

    if (arg0 == 0) {
        s8 *p;
        i = 5;
        p = &D_80138FD0[i];
        do {
            *p-- = 0;
        } while (--i >= 0);
        return;
    }
    if (g[3]) {
        return;
    }
    e = D_801352CC;
    for (i = 0; i < 6; i++, e++) {
        if (--D_80138FD0[i] <= 0) {
            if (e->ptr[0] == 0xFF) {
                e->ptr -= e->ptr[1];
            }
            data = e->clut + e->ptr[0] * 32;
            D_80138FD0[i] = e->ptr[1];
            r.x = e->x;
            r.y = e->y;
            r.w = 16;
            r.h = 1;
            func_80081218(&r, data);
            e->ptr += 2;
        }
    }
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", f_UpdatePipeAreaSceneController);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80111620);

typedef struct {
    s16 x, y, w, h;
} RectA;
extern u8 *D_800BF544;
extern void *D_800ED8C8_a098;
void func_80111BE0(void) {
    RectA r;
    u8 *p;

    p = D_800BF544;
    r.x = 0x3F0;
    r.y = 0xE5;
    r.w = 0x10;
    r.h = 1;
    func_80083CE0(p, &r, 0x3F0, 0xEB);
    func_80083C30(D_800ED8C8_a098, p);
    D_800BF544 = (p = p + 0x18);
}

extern u8 D_800BF873;
extern s32 D_80135314;
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

typedef struct {
    s16 lo, hi;
} Range16;
extern Range16 D_80135BA0[];
extern u8 D_1F800207_9c67;
s32 func_80111CCC(s32 x) {
    u8 v;
    s32 k;
    s32 i;

    k = -1;
    v = D_1F800207_9c67;
    for (i = 0; i < 6; i++) {
        if (v >= D_80135BA0[i].lo && v <= D_80135BA0[i].hi) {
            k = i;
            break;
        }
    }
    if (k < 0) {
        return 0;
    }
    if (x >= D_80135BA0[k].lo && x <= D_80135BA0[k].hi) {
        return 1;
    }
    return 0;
}

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

extern u16 D_1F800160_3621;
s32 func_80112784(void) {
    GameState *g = &D_800BF870;

    if ((g->pad1[0x10] & 4) || (M2C_FIELD(g, u16 *, 0x2E) & 0x200) || g->pad1[2] != 0 || g->pad1[0x18E] != 0) {
        return 0;
    }
    if (D_1F800207_9c67 != 10) {
        return 0;
    }
    return (u16)(D_1F800160_3621 - 0x50F0) < 0x1F0;
}

extern u8 D_800BF9FF;
void f_UpdatePipeAreaQuestPickupActor();
void func_80112808(s32 k) {
    u8 *p = func_80072DDC(NULL, 0, 5, 3);
    u8 *g;

    if (p != NULL) {
        g = D_800BF808_1760;
        g[2] = 1;
        g[3] = k;
        func_8004D650(k, 1);
        M2C_FIELD(p, void **, 0x1C) = f_UpdatePipeAreaQuestPickupActor;
        switch (k) {
        case 0x7C:
            p[3] = 0x83;
            D_800BF9FF = 3;
            break;
        case 0x7D:
            p[3] = 0x84;
            D_800BF9FF = 4;
            break;
        }
    }
}

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

extern s32 D_800ECF80;
extern u8 D_80139294_2487[];
void func_80112990(u8 *a) {
    a[0xB] = 0x11;
    M2C_FIELD(a, s16 *, 0x7A) = 0x1C00;
    M2C_FIELD(a, s16 *, 0x7C) = 0x1C00;
    M2C_FIELD(a, s16 *, 0x7E) = 0x1C00;
    M2C_FIELD(a, s16 *, 0x5A) = 0;
    a[0x47] = 0;
    M2C_FIELD(a, s16 *, 0x5C) = 0;
    a[0xD] = 0;
    M2C_FIELD(a, s32 *, 0x3C) = D_800ECF80;
    func_80077B38(a, D_80139294_2487, 4);
    a[0] = 1;
    M2C_FIELD(a, s16 *, 0x80) = 0x20;
    M2C_FIELD(a, s16 *, 0x82) = 0x40;
    M2C_FIELD(a, s16 *, 0x84) = 0x20;
    M2C_FIELD(a, s16 *, 0x86) = 0x40;
    func_8004B354(a, 0);
}

void func_80112A20(s32 arg0) {
    func_8007778C();
    func_8004B374(arg0, 0);
}

void func_80112A50(void *arg0) {
    func_8004D4C4(0x7F, 1);
    func_8004B0D8(arg0);
    M2C_FIELD(arg0, s8 *, 4) = 3;
}

void func_80112A8C(u8 *a) {
    switch (a[6]) {
    case 0:
        if (a[0x2B] != 0) {
            func_80112B10(a);
            a[6]++;
        }
        break;
    case 1:
        if (a[0x2B] == 0) {
            a[6] = 0;
        }
        break;
    }
    a[0x2B] = 0;
}

void func_80112B10(u8 *a) {
    switch (M2C_FIELD(a, s16 *, 0x68)) {
    case 0x7C:
        M2C_FIELD(a, s32 *, 0x3C) = D_800ECF80;
        func_80077B38(a, D_80139294_2487, 7);
        M2C_FIELD(a, s16 *, 0x68) = 0x7D;
        a[3] = 4;
        D_800BF9FF = 4;
        break;
    case 0x7D:
        M2C_FIELD(a, s32 *, 0x3C) = D_800ECF80;
        func_80077B38(a, D_80139294_2487, 8);
        a[0xD] = 1;
        M2C_FIELD(a, s16 *, 0x68) = 0x7E;
        a[3] = 5;
        D_800BF9FF = 5;
        break;
    }
}

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

extern PairOwner D_800E7E80_6978;
void func_80112CB8(u8 *a) {
    PairOwner *g = &D_800E7E80_6978;

    M2C_FIELD(a, s16 *, 0x2E) = (g->p0[0x2C / 4] + g->p1[0x2C / 4]) / 2;
    M2C_FIELD(a, s16 *, 0x32) = (g->p0[0x30 / 4] + g->p1[0x30 / 4]) / 2;
    M2C_FIELD(a, s16 *, 0x36) = (g->p0[0x34 / 4] + g->p1[0x34 / 4]) / 2;
    M2C_FIELD(a, s16 *, 0x2E) += func_80083F50(M2C_FIELD(g, s16 *, 0x56)) >> 6;
    M2C_FIELD(a, s16 *, 0x2E) += func_80083F50(M2C_FIELD(g, s16 *, 0x56)) >> 8;
    M2C_FIELD(a, s16 *, 0x32) -= 0x14;
}

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

void func_80112E58(u8 *a) {
    a[0xB] = 0x11;
    M2C_FIELD(a, s16 *, 0x7A) = 0x1C00;
    M2C_FIELD(a, s16 *, 0x7C) = 0x1C00;
    M2C_FIELD(a, s16 *, 0x7E) = 0x1C00;
    M2C_FIELD(a, s16 *, 0x5A) = 0;
    a[0x47] = 0;
    M2C_FIELD(a, s16 *, 0x5C) = 0;
    a[0xD] = 0;
    M2C_FIELD(a, s32 *, 0x3C) = D_800ECF80;
    func_80077B38(a, D_80139294_2487, 0xC);
    a[0] = 1;
    M2C_FIELD(a, s16 *, 0x80) = 0x20;
    M2C_FIELD(a, s16 *, 0x82) = 0x40;
    M2C_FIELD(a, s16 *, 0x84) = 0x20;
    M2C_FIELD(a, s16 *, 0x86) = 0x40;
}

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

void func_801133F4(u8 *a) {
    u8 *q = M2C_FIELD(M2C_FIELD(a, u8 **, 0x10), u8 **, 0xC0);

    switch (a[5]) {
    case 0:
        a[5]++;
        a[0] = 1;
        func_8004B354(a, 0);
    case 1:
        M2C_FIELD(a, s16 *, 0x2E) = M2C_FIELD(q, s16 *, 0x2C);
        M2C_FIELD(a, s16 *, 0x32) = M2C_FIELD(q, s16 *, 0x30) - 0x48;
        M2C_FIELD(a, s16 *, 0x36) = M2C_FIELD(q, s16 *, 0x34);
        if (func_8007778C(a) != 0) {
            func_8004B374(a, 0);
        }
        break;
    }
}

void func_80113490(u8 *a) {
    switch (a[5]) {
    case 0:
        a[5]++;
        a[0] = 1;
        M2C_FIELD(a, s16 *, 0x4A) = 0;
    case 1:
        M2C_FIELD(a, s16 *, 0x4A) += 0x300;
        if (M2C_FIELD(a, s16 *, 0x4A) > 0x3000) {
            M2C_FIELD(a, s16 *, 0x4A) = 0x3000;
        }
        M2C_FIELD(a, s32 *, 0x30) += M2C_FIELD(a, s16 *, 0x4A) << 8;
        if (a[0x29] == 0) {
            func_8004766C(a);
            func_80049250(a, 0, (s16)(M2C_FIELD(a, u16 *, 0x86) - M2C_FIELD(a, u16 *, 0x84)));
        }
        break;
    }
    func_8007778C(a);
    a[0x29] = 0;
}

extern u8 D_800BF818;
void func_80113554(u8 *a, u8 *b) {
    u8 *t;

    switch (a[5]) {
    case 0:
        a[5]++;
        F16(b, 0xE) = F16(b, 0xA);
        func_80072FE0(a);
        a[0x5E] = 1;
        break;
    case 1:
        if (D_800BF818 == 2) {
            F16(a, 0x40) = 0;
            a[5]++;
        }
        break;
    case 2:
        if (++F16(a, 0x40) >= 0x19 && func_80073194(a) != 0) {
            a[0x5E] = 0;
            a[5]++;
        }
        break;
    case 3:
        t = D_800BF808_1760;
        if (t[0x10] == 3) {
            a[0x5E] = 1;
            a[5]++;
        } else if (t[0x10] == 7) {
            t[0x10] = 0;
            a[5] = 6;
            func_80074590(0x17, 0, 0);
            a[0x5E] = 1;
        }
        break;
    case 4:
        if (func_8007302C(a) != 0) {
            a[5]++;
        }
        break;
    case 6:
        if (func_8007302C(a) != 0) {
            F16(a, 0x40) = 0x18;
            a[5]++;
        }
        break;
    case 7:
        if (--F16(a, 0x40) == 0) {
            a[5]++;
        }
        break;
    case 8:
        if (func_800730C8(a) != 0) {
            a[5] = 3;
            func_80074590(0x18, 0, 0);
            D_800BF818 = 0;
        }
        break;
    }
}

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

extern u8 D_800BF909;
s32 func_80115CA0(u8 *a, s32 b) {
    u8 *t = D_800E7E80;

    if (*(s16 *)(t + 0x36) >= 0x4149) {
        *(s16 *)(t + 0x36) = 0x4149;
        if (b == 2) {
            if (D_1F800137 == 1) {
                return 1;
            }
            if (D_800BF909 == 0xFF) {
                D_1F800137 = b;
                return 1;
            }
        }
    }
    return 0;
}

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

void func_80115DE0(u8 *a) {
    PairOwner *g;

    if (func_80051B70(a, 0xC, 0x18) != 0) {
        return;
    }
    g = &D_800E7E80_6978;
    M2C_FIELD(a, s16 *, 0x2E) = (g->p0[0x2C / 4] + g->p1[0x2C / 4]) / 2;
    M2C_FIELD(a, s16 *, 0x32) = (g->p0[0x30 / 4] + g->p1[0x30 / 4]) / 2;
    M2C_FIELD(a, s16 *, 0x36) = (g->p0[0x34 / 4] + g->p1[0x34 / 4]) / 2;
    M2C_FIELD(a, s16 *, 0x32) -= 0x20;
    M2C_FIELD(a, s16 *, 0x58) = 0;
    M2C_FIELD(a, s16 *, 0x56) = 0;
    M2C_FIELD(a, s16 *, 0x54) = 0;
    M2C_FIELD(a, s16 *, 0x80) = 0x40;
    M2C_FIELD(a, s16 *, 0x82) = 0x80;
    M2C_FIELD(a, s16 *, 0x84) = 0x64;
    M2C_FIELD(a, s16 *, 0x86) = 0x64;
}

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

extern s16 D_1F8000C0_65b0[];
void func_80115FEC(u8 *a) {
    u8 *p = M2C_FIELD(a, u8 **, 0x10);
    s16 *v;
    GameState *g;

    D_1F8000C0_65b0[0] = 0;
    v = D_1F8000C0_65b0;
    v[1] = 0x62;
    v[2] = -0x20;
    func_8004BD64(a, 2, M2C_FIELD(p, void **, 0xDC), M2C_FIELD(p, void **, 0xD0), v);
    g = &D_800BF870;
    if (g->pad1[0x1CD] == 1) {
        a[4] = 3;
        func_8004D4F4(0x1C, 1);
        func_80026100(g->pad1[0xE]);
        func_8004ED94(0x70, 0x41);
        func_8004B2E8(a);
    }
    a[1] = 1;
    func_800517F8(a);
}

u8 *func_801160A4(s32 a, s32 b) {
    u8 *p = func_80072DDC(a, 0, 3, 16);

    if (p != NULL) {
        M2C_FIELD(p, void **, 0x1C) = f_UpdatePipeAreaScenePropActor;
        p[0x3] = 9;
        p[0x5E] = b;
    }
    return p;
}

void func_801160F8(u8 *a) {
    M2C_FIELD(a, s32 *, 0x3C) = D_800ECF80;
    func_80077B38(a, D_80139294_2487, func_8009A450() % 3 + 0x10);
    a[0xB] = 0x10;
    M2C_FIELD(a, s16 *, 0x2E) = 0x4C2C;
    M2C_FIELD(a, s16 *, 0x32) = -0x7EC;
    a[0xD] = 0;
    M2C_FIELD(a, s16 *, 0x5C) = 0;
    M2C_FIELD(a, s16 *, 0x5A) = 0;
    a[0x47] = 0;
    a[8] = 0;
    M2C_FIELD(a, s16 *, 0x36) = 0x1D60;
}

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

extern u8 *D_800ECFC4;
extern u8 D_80139B24[];
void func_801199DC(u8 *a, s32 k, s32 f) {
    u8 *b;
    s32 *t;
    s32 s;

    if (a[0x46] != k) {
        a[0x46] = k;
        b = D_800ECFC4;
        t = (s32 *)(b + 4);
        switch (k) {
        case 5:
            s = 0x13;
            break;
        case 0xD:
        case 0xF:
        case 0x11:
            s = 0x12;
            break;
        default:
            s = 1;
            break;
        }
        M2C_FIELD(M2C_FIELD(a, u8 **, 0xC4), u8 **, 0x40) = b + t[s];
        if (!(f & 0xFF)) {
            func_80077C40(a, D_80139B24, k);
        } else {
            func_80077CFC(a, D_80139B24, k, (u8)f);
        }
    }
}

typedef struct {
    s16 x, y, z;
} SV3;
void func_80119AAC(u8 *a) {
    SV3 p;
    SV3 s;

    s.x = (M2C_FIELD(M2C_FIELD(a, u8 **, 0xC4), s16 *, 0x18) * 0x5F) >> 4;
    s.y = (M2C_FIELD(M2C_FIELD(a, u8 **, 0xC4), s16 *, 0x1E) * 0x5F) >> 4;
    s.z = (M2C_FIELD(M2C_FIELD(a, u8 **, 0xC4), s16 *, 0x24) * 0x5F) >> 4;
    p.x = M2C_FIELD(M2C_FIELD(a, u8 **, 0xC4), s16 *, 0x2C);
    p.y = M2C_FIELD(M2C_FIELD(a, u8 **, 0xC4), s16 *, 0x30);
    p.z = M2C_FIELD(M2C_FIELD(a, u8 **, 0xC4), s16 *, 0x34);
    func_80133CAC(0, a, &p, &s);
}

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

extern s16 D_800E7FFE;
extern u8 D_80135BF8[];
extern u8 D_80135C08[];
extern u8 D_80135C18[];
s32 func_80119E60(u8 *a) {
    s32 d = func_800781E0(M2C_FIELD(a, s16 *, 0x2E) - D_1F800160_71b4, M2C_FIELD(a, s16 *, 0x36) - D_1F800164_d75f);
    u8 *t;

    if (D_800E7FFE & 0x8200) {
        return 0;
    }
    if (d > 0x640) {
        return 0;
    }
    if (d >= 0x385) {
        t = D_80135BF8;
    } else if (d >= 0x12D) {
        t = D_80135C08;
    } else {
        t = D_80135C18;
    }
    return t[(func_8009A450() >> 8) & 0xF];
}

extern u16 D_1F8001A0;
void func_80119F10(u8 *a) {
    u8 *q = a + 0x60;

    func_80116620(a);
    func_8004766C(a);
    func_80049760(a);
    M2C_FIELD(q, s16 *, 4) = D_1F8001A0;
    if (func_800493E8(a, 0, -0x5A) != 0 || func_80049250(a, 0, 0x5A) != 0) {
        a[5] = 0;
        a[6] = 0;
    }
    a[0x29] = 0;
}

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

s32 func_8011A0A0(u8 *a, s16 lo, s16 hi) {
    s32 s;

    switch (a[3]) {
    case 3:
        hi = -0x1401;
        break;
    case 4:
        hi = -0x1280;
        break;
    }
    if (M2C_FIELD(a, s16 *, 0x32) >= hi) {
        s = 1;
        if (a[5] != s) {
            a[5] = s;
            a[6] = 0;
            return 1;
        }
    } else {
        switch (a[3]) {
        case 3:
            lo = -0x18FA;
            break;
        case 4:
            lo = -0x1B58;
            if (D_800BF8BF == 0xFF) {
                lo = -0x1280;
            }
            break;
        }
        if (M2C_FIELD(a, s16 *, 0x32) < lo) {
            s = 2;
            if (a[5] != s) {
                a[5] = s;
                a[6] = 0;
                return 1;
            }
        }
    }
    return 0;
}

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

extern s16 D_800E7FEE;
void func_8011B594(u8 *a) {
    GameState *g;
    s16 t;

    if (func_8007778C(a) != 0) {
        func_800517F8(a);
    }
    switch (a[6]) {
    case 0:
        if (D_800E7FEE != 0) {
            g = &D_800BF870;
            g->pad1[0x183] |= 1 << a[3];
            g->pad1[0x184]++;
            if (g->pad1[0x4D] != 0xFF && g->pad1[0x184] == 8) {
                func_80040C00(10);
                g->pad1[0x188] = 1;
            }
        }
        M2C_FIELD(a, s16 *, 0x4A) = -0x20;
        a[6]++;
    case 1:
        if (a[1] == 0) {
            a[4] = 3;
            break;
        }
        t = M2C_FIELD(a, s16 *, 0x4A);
        M2C_FIELD(a, s16 *, 0x58) += 0x100;
        M2C_FIELD(a, s16 *, 0x32) += t;
        M2C_FIELD(a, s16 *, 0x4A) += 3;
        break;
    }
}

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

void func_8011C19C(u8 *a) {
    u8 *e;

    if (M2C_FIELD(a, u8 **, 0x10) != NULL) {
        return;
    }
    if (a[3] == 1) {
        e = func_8003116C(0x202, 0, 0);
        if (e != NULL) {
            M2C_FIELD(e, u8 **, 0x10) = a;
            M2C_FIELD(a, u8 **, 0x10) = e;
            M2C_FIELD(e, s16 *, 0x2C) = M2C_FIELD(a, s16 *, 0x2E);
            M2C_FIELD(e, s16 *, 0x2E) = M2C_FIELD(a, s16 *, 0x32) - 0x30;
            M2C_FIELD(e, s16 *, 0x30) = M2C_FIELD(a, s16 *, 0x36);
            e[7] = 1;
        }
    } else {
        e = func_8003116C(0x201, 0, 0);
        if (e != NULL) {
            M2C_FIELD(e, u8 **, 0x10) = a;
            M2C_FIELD(a, u8 **, 0x10) = e;
            M2C_FIELD(e, s16 *, 0x2C) = M2C_FIELD(a, s16 *, 0x2E);
            M2C_FIELD(e, s16 *, 0x2E) = M2C_FIELD(a, s16 *, 0x32) - 0x30;
            M2C_FIELD(e, s16 *, 0x30) = M2C_FIELD(a, s16 *, 0x36);
            e[7] = 0;
        }
    }
}

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

void func_8011C290(u8 *a) {
    GameState *g;

    if (D_800E7FEE != 0) {
        g = &D_800BF870;
        g->pad1[0x183] |= 1 << a[3];
        g->pad1[0x184]++;
        if (g->pad1[0x4D] != 0xFF && g->pad1[0x184] == 8) {
            func_80040C00(10);
            g->pad1[0x188] = 1;
        }
    }
}

void func_8011C314(u8 *a) {
    switch (a[6]) {
    case 0:
        a[6]++;
        M2C_FIELD(a, s16 *, 0x40) = 0x78;
    case 1:
        if (--M2C_FIELD(a, s16 *, 0x40) == 0) {
            a[5] = 0;
            a[6] = 0;
            a[0x5E] = 0;
        }
        break;
    }
    func_8011AFF0(a);
    if (func_800778E4(a, (s16)(D_1F800162 - M2C_FIELD(a, u16 *, 0x32))) != 0) {
        func_800517F8(a);
    }
}

void func_8011C3C0(u8 *a) {
    switch (a[6]) {
    case 0:
        a[6]++;
        M2C_FIELD(a, s16 *, 0x40) = 0x78;
    case 1:
        if (--M2C_FIELD(a, s16 *, 0x40) == 0) {
            a[5] = 0;
            a[6] = 0;
            a[0x5E] = 0;
        }
        break;
    }
    func_8011AFF0(a);
    if (func_800778E4(a, (s16)(D_1F800162 - M2C_FIELD(a, u16 *, 0x32))) != 0) {
        func_800517F8(a);
    }
}

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

extern u16 D_1F800164_7d8c;
s32 func_8011DBA4(u8 *a) {
    s16 dx, dz;

    if (D_800E7FFE & 0x8200) {
        return 0;
    }
    dx = D_1F800160_3621 - M2C_FIELD(a, u16 *, 0x2E);
    dz = D_1F800164_7d8c - M2C_FIELD(a, u16 *, 0x36);
    if (dx * dx + dz * dz > 0x64000) {
        return 0;
    }
    return (u16)(M2C_FIELD(a, u16 *, 0x32) - D_1F800162) <= M2C_FIELD(a, s16 *, 0x6E);
}

typedef struct {
    s16 x, y;
} Pair16;
extern Pair16 D_80136174[];
void func_8011DC4C(u8 *a, s16 k) {
    s32 t;

    M2C_FIELD(a, s16 *, 0x60) = D_80136174[k].x;
    M2C_FIELD(a, s16 *, 0x62) = D_80136174[k].y;
    M2C_FIELD(a, s16 *, 0x64) = (-func_80083E80(M2C_FIELD(a, s16 *, 0x56)) * M2C_FIELD(a, s16 *, 0x60)) >> 12;
    t = func_80083F50(M2C_FIELD(a, s16 *, 0x56)) * M2C_FIELD(a, s16 *, 0x60);
    M2C_FIELD(a, s16 *, 0x6C) = k;
    M2C_FIELD(a, s16 *, 0x60) = t >> 12;
}

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

typedef struct {
    u8 pad0[0x38];
    u8 *p38;
    u8 pad3C[0x24];
    s16 h60[0x34];
    u8 *pC8;
} ActorDF;
void func_8011DD88(ActorDF *a, s32 i) {
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
}

typedef struct {
    u8 pad[0x60];
    s16 v[8];
} ArrActor60;
extern u8 D_80139FE0[];
void func_8011DE34(ArrActor60 *a, s32 k, s32 f, s32 i) {
    s16 n;

    if (f == 0) {
        func_80077C40(a, D_80139FE0, k);
    } else {
        func_80077CFC(a, D_80139FE0, k, (s16)f);
    }
    func_8011D9E4(a, i + 1);
    if (a->v[i + 1] != 2) {
        a->v[i] = 0;
        return;
    }
    n = (s16)M2C_FIELD(M2C_FIELD(a, u8 **, 0x38), u16 *, 4) >> 4;
    if (n != a->v[i]) {
        func_80051B04(M2C_FIELD(a, u8 **, 0xC8), 0x15, n);
        a->v[i] = n;
    }
}

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

void func_8011E040(u8 *a) {
    u8 *p = M2C_FIELD(a, u8 **, 0x10);

    if (p != NULL) {
        p[4] = 3;
        M2C_FIELD(a, u8 **, 0x10) = NULL;
    }
    func_80112DD8(a);
    func_8003116C(0x24, a + 0x2C, -10);
    D_800BF870.pad1[0x17B] += 1 << ((a[3] & 0x7F) * 2);
    a[4] = 3;
}

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

extern u8 D_801393C0_27b3[];
void func_8011E324(AreaPartsOwner *a) {
    switch (a->pad[4]) {
    case 0:
        M2C_FIELD(a, s16 *, 0x56) = 0x400;
        a->pad[0x7B] = 1;
        func_80051B04(a->parts[a->pad[9] - 1], 0x1A, 4);
        func_80077C40(a, D_801393C0_27b3, 1);
        a->pad[0x2B] = 0;
        a->pad[4]++;
    case 1:
        func_8011E1D4(a);
        if (a->pad[1] != 0) {
            func_800518FC(a);
        }
        a->pad[0x2B] = 0;
        break;
    case 2:
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

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

extern void *D_8013677C[];
extern u8 D_801367D0[];
void func_8011EA60(u8 *a) {
    if (a[0x71] == 0xFF) {
        func_80041768(a, 5, 4);
        func_80040D68(a, D_8013677C[a[0x5E]]);
        a[0x70] = 1;
        a[5] = 2;
        a[6] = D_801367D0[a[0x5E]];
    }
}

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

extern u8 D_800ECF58_742e[];
extern u8 D_8013581C[];
extern u8 D_80137124[];
extern u8 D_800BF910;
void func_80120420(u8 *a) {
    u8 *g = D_800ECF58_742e;

    M2C_FIELD(a, s32 *, 0x3C) = M2C_FIELD(g, s32 *, 0x38);
    if (func_800519E0(a, 0xF, M2C_FIELD(g, s32 *, 0x3C), D_8013581C) != 0) {
        return;
    }
    func_80040CDC(a, D_801393C0_27b3, D_80137124);
    if (D_800BF910 == 0xFF) {
        a[0x5E] = 1;
        func_80041718(a, 0, 0);
    } else {
        a[0x5E] = 0;
        func_80041718(a, 0xD, 0);
    }
    M2C_FIELD(a, s16 *, 0x56) = 0x800;
    a[0] = 9;
    M2C_FIELD(a, s16 *, 0x80) = 0xB4;
    M2C_FIELD(a, s16 *, 0x82) = 0x168;
    M2C_FIELD(a, s16 *, 0x84) = 0x78;
    M2C_FIELD(a, s16 *, 0x54) = 0;
    M2C_FIELD(a, s16 *, 0x58) = 0;
    a[0xB] = 0;
    M2C_FIELD(a, s16 *, 0x86) = 0xF0;
    a[0x2B] = 0;
    a[0x29] = 0;
    M2C_FIELD(a, s32 *, 0x14) = 0;
    a[4]++;
}

extern void *D_80137114[];
void func_80120508(u8 *a)
{
    if (a[0x71] == 0xFF) {
        func_80040D68(a, D_80137114[a[0x5E]]);
        a[5] = 2;
        a[0x70] = 1;
    }
}

extern u8 D_800A3E38[];
extern u8 D_800A3E28[];
void f_ReturnThirstyMinerToIdleScript(u8 *a) {
    if (a[0x71] == 0xFF) {
        switch (a[0x5E]) {
        case 0 ... 1:
            func_80040D68(a, D_800A3E38);
            break;
        case 2 ... 3:
            a[0x5E] -= 2;
            func_80040D68(a, D_800A3E28);
            break;
        }
        a[0x70] = 1;
        a[5] = 0;
    }
}

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

void func_80122A2C(u8 *a) {
    u8 *p;

    if (a[0xBF] != 0 || a[0x5E] != 0) {
        return;
    }
    p = func_8003116C(0x203, 0, 0);
    if (p != NULL) {
        M2C_FIELD(p, u8 **, 0x10) = a;
        M2C_FIELD(a, u8 **, 0x10) = p;
        M2C_FIELD(p, s16 *, 0x2C) = M2C_FIELD(a, s16 *, 0x2E);
        M2C_FIELD(p, s16 *, 0x2E) = M2C_FIELD(a, s16 *, 0x32) + M2C_FIELD(a, s16 *, 0x72);
        M2C_FIELD(p, s16 *, 0x30) = M2C_FIELD(a, s16 *, 0x36);
        M2C_FIELD(p, s32 *, 0x34) = (M2C_FIELD(a, s16 *, 0x6A) << 16) + 0x100;
        a[0x5E] = 1;
    } else {
        M2C_FIELD(a, u8 **, 0x10) = NULL;
        a[0x5E] = 0;
    }
}

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

s32 func_80122B78(u8 *a) {
    u8 *p = M2C_FIELD(a, u8 **, 0x10);
    s32 r = 0;
    s16 h;

    if (p != NULL) {
        h = M2C_FIELD(p, s32 *, 0x34) >> 16;
        h += 0x10;
        if (h > 0x200) {
            h = 0x200;
            r = 1;
        }
        M2C_FIELD(a, s16 *, 0x72) = (0xA0 - h) / 2;
        M2C_FIELD(a, s16 *, 0x6A) = h;
        M2C_FIELD(p, s32 *, 0x34) = (h << 16) + 0x100;
    } else {
        r = 1;
        M2C_FIELD(a, s16 *, 0x72) = -0xB0;
        M2C_FIELD(a, s16 *, 0x6A) = 0x200;
    }
    return r;
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80122C08);

extern s16 D_1F8001A4;
s32 func_80122CAC(u8 *a) {
    if (func_80049280(a, (M2C_FIELD(a, s16 *, 0x44) >> 8) + 0x20, (M2C_FIELD(a, s16 *, 0x4A) * M2C_FIELD(a, s16 *, 0x44)) >> 16) == 0 &&
        M2C_FIELD(a, s16 *, 0x32) - D_1F8001A4 < -500) {
        return 1;
    }
    if (a[0x2A] != 0x10) {
        return 0;
    }
    if (M2C_FIELD(a, s16 *, 0x36) < 0x36D9) {
        return 0;
    }
    M2C_FIELD(a, s16 *, 0x36) = 0x36D8;
    return 1;
}

s32 func_80122D4C(u8 *a) {
    return func_8004954C(a, M2C_FIELD(a, s16 *, 0x80), -0x5A) != 0;
}

s32 func_80122D70(u8 *a) {
    switch (a[7]) {
    case 0:
        M2C_FIELD(a, s16 *, 0x58) = 0;
        if (a[0xBE] == 0) {
            M2C_FIELD(a, s16 *, 0x64) = (M2C_FIELD(a, u16 *, 0x60) + 0x800) & 0xFFF;
        } else {
            M2C_FIELD(a, s16 *, 0x64) = M2C_FIELD(a, u16 *, 0x60);
        }
        a[7]++;
        break;
    case 1:
        M2C_FIELD(a, s16 *, 0x56) = func_800776F8(M2C_FIELD(a, s16 *, 0x64), M2C_FIELD(a, s16 *, 0x56), 0x100);
        if (M2C_FIELD(a, s16 *, 0x64) == M2C_FIELD(a, s16 *, 0x56)) {
            a[0xBE] = 1 - a[0xBE];
            return 1;
        }
        break;
    }
    return 0;
}

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

extern u8 D_80137230[];
void func_80122FBC(u8 *a) {
    u8 *p;

    switch (a[6]) {
    case 0:
        func_80113CB4(a);
        M2C_FIELD(a, s16 *, 0x40) = D_80137230[func_8009A450() & 3] << 6;
        a[6]++;
        break;
    case 1:
        if (--M2C_FIELD(a, s16 *, 0x40) == 0) {
            p = M2C_FIELD(a, u8 **, 0x14);
            a[5] = 2;
            a[6] = 0;
            a[7] = 0;
            if (p != NULL) {
                p[4] = 3;
            }
        }
        break;
    }
    func_801208B4(a);
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80123078);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8012322C);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_801233A8);

s32 func_8012364C(u8 *a) {
    switch (a[0x78]) {
    case 0:
        func_8011A43C(a, 0);
        D_800BF9EB = 0;
        a[0x78]++;
        break;
    case 1:
        if (D_800BF9EB == 2) {
            return 1;
        }
        break;
    }
    return 0;
}

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

void func_80123AAC(u8 *a) {
    u8 *p = func_8003116C(0x202, 0, 0);

    if (p != NULL) {
        M2C_FIELD(p, u8 **, 0x10) = a;
        M2C_FIELD(p, s16 *, 0x2C) = M2C_FIELD(a, s16 *, 0x2E);
        M2C_FIELD(p, s16 *, 0x2E) = M2C_FIELD(a, s16 *, 0x32) - 0x30;
        M2C_FIELD(p, s16 *, 0x30) = M2C_FIELD(a, s16 *, 0x36);
        p[7] = 2;
    }
    M2C_FIELD(a, s16 *, 0x80) = 0xC8;
    M2C_FIELD(a, s16 *, 0x82) = 0x190;
    M2C_FIELD(a, s16 *, 0x84) = 0x2D0;
    M2C_FIELD(a, u8 **, 0x14) = p;
    M2C_FIELD(a, s16 *, 0x86) = 0x310;
    a[0x5E] = 0;
}

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

void func_80123CFC();
s32 func_80123F28(u8 *a) {
    u8 *g = (u8 *)&D_800BF870;
    u8 *e;

    if (g[0xC6] & 0x4) {
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
    M2C_FIELD(e, void **, 0x1C) = func_80123CFC;
    M2C_FIELD(e, s16 *, 0x2E) = M2C_FIELD(a, s16 *, 0x2E);
    M2C_FIELD(e, s16 *, 0x32) = M2C_FIELD(a, s16 *, 0x32);
    M2C_FIELD(e, s16 *, 0x36) = M2C_FIELD(a, s16 *, 0x36);
    e[0x2A] = a[0x2A];
    g[0x164] = 1;
    func_8003116C(0x30, e + 0x2C, -0xA);
    func_80074590(0x37, 0x20, 0);
    return 1;
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80123FF8);

extern s16 D_1F80016C;
extern s16 D_1F80016E;
void func_80124164(u8 *a) {
    u8 *g = D_800E7E80;

    if (D_1F800160_71b4 < 0x19B8) {
        return;
    }
    switch (a[6]) {
    case 0:
        if (M2C_FIELD(g, s16 *, 0x2E) < 0x1C4D) {
            D_1F800190 = D_1F80016C;
            a[6]++;
        }
        break;
    case 1:
        if (M2C_FIELD(g, s16 *, 0x2E) < 0x1C4D) {
            D_1F800190 = D_1F80016C;
        } else {
            D_1F800190 = D_1F80016E;
            a[6]++;
        }
        break;
    case 2:
        if (g[0x147] != 0) {
            D_1F800190 = 0;
            a[6]++;
        } else {
            D_1F800190 = D_1F80016E;
        }
        break;
    }
}

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

void func_801263F8(u8 *a) {
    switch (a[0x5E]) {
    case 0:
        if (((D_800BF9FD >> 2) & 3) == 3) {
            a[0x5E] = 1;
            a[5] = 0;
            a[6] = 0;
            a[7] = 0;
        } else {
            func_800735F4(a, 0x4A);
        }
        break;
    case 1:
        func_8012464C(a);
        break;
    case 2:
        if (a[5] == 0) {
            a[5] = 1;
            M2C_FIELD(a, s16 *, 0x32) = M2C_FIELD(a, s16 *, 0x8A);
        }
        break;
    }
}

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

extern s16 D_80137600[];
void func_80126EB0(u8 *a) {
    if (a[3] == 1) {
        M2C_FIELD(a, s16 *, 0x56) = 0x180;
    } else if (a[3] == 2) {
        M2C_FIELD(a, s16 *, 0x56) = 0xB9A;
    } else if (a[3] == 3) {
        M2C_FIELD(a, s16 *, 0x56) = 0xA0;
    }
    a[0x47] = 0;
    func_80126608(a);
    M2C_FIELD(a, s16 *, 0x80) = 0x32;
    M2C_FIELD(a, s16 *, 0x82) = 0x64;
    M2C_FIELD(a, s16 *, 0x84) = D_80137600[a[3]] + 0x5A;
    M2C_FIELD(a, s16 *, 0x86) = D_80137600[a[3]] + 0xDC;
}

typedef struct {
    s16 x, y, z;
} AVec3;
extern AVec3 D_80137614[];
extern s16 D_8013764C[];
void func_80126F60(u8 *a) {
    u8 *p;

    M2C_FIELD(a, s16 *, 0x2E) = D_80137614[a[3]].x;
    M2C_FIELD(a, s16 *, 0x32) = D_80137614[a[3]].y;
    M2C_FIELD(a, s16 *, 0x36) = D_80137614[a[3]].z;
    p = M2C_FIELD(a, u8 **, 0x10);
    M2C_FIELD(a, s16 *, 0x54) = M2C_FIELD(p, s16 *, 0x54);
    M2C_FIELD(a, s16 *, 0x56) = M2C_FIELD(p, s16 *, 0x56);
    M2C_FIELD(a, s16 *, 0x58) = M2C_FIELD(p, s16 *, 0x58);
    M2C_FIELD(a, s16 *, 0x80) = 0x32;
    M2C_FIELD(a, s16 *, 0x82) = 0x64;
    M2C_FIELD(a, s16 *, 0x84) = D_8013764C[a[3]] + 0x5A;
    M2C_FIELD(a, s16 *, 0x86) = D_8013764C[a[3]] + 0xDC;
}

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

extern u8 D_800BF80F;
extern s8 D_800E807E;
s32 func_80127DC4(u8 *a) {
    switch (a[7]) {
    case 0:
        a[7]++;
        a[0xBF] = 2;
        M2C_FIELD(a, s16 *, 0x42) = 8;
        D_800E807E = 1;
        if (D_800BF80F == 0) {
            func_80074590(0x84, 0, 0);
        }
    case 1:
        M2C_FIELD(M2C_FIELD(a, u8 **, 0xC0), s16 *, 2) = ((D_1F80017C & 3) - 2) * 12;
        if (--M2C_FIELD(a, s16 *, 0x42) == 0) {
            D_800E807E = 0;
            return 1;
        }
        return 0;
    }
    return 0;
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", f_UpdatePipeAreaMudballSurpriseCarrierActor);

void func_8012866C(u8 *a) {
    s16 *v = D_1F8000C0_65b0;
    u8 *p = M2C_FIELD(a, u8 **, 0x10);

    func_80051D20(p, a + 0x88, v);
    M2C_FIELD(a, s16 *, 0x2E) = v[0];
    M2C_FIELD(a, s16 *, 0x32) = v[1];
    M2C_FIELD(a, s16 *, 0x36) = v[2];
    M2C_FIELD(a, s16 *, 0x56) = M2C_FIELD(p, s16 *, 0x56);
    func_800517F8(a);
}

typedef struct {
    s16 x, y, z;
} SVec3T;
extern SVec3T D_1F8000C0_4e9b;
void f_UpdatePipeAreaPersistentSceneryRewardActor();
void func_801286F4(u8 *a) {
    u8 *p = M2C_FIELD(a, u8 **, 0x10);
    u8 *e;

    func_80051D20(p, a + 0x88, &D_1F8000C0_4e9b);
    M2C_FIELD(a, s16 *, 0x2E) = D_1F8000C0_4e9b.x;
    M2C_FIELD(a, s16 *, 0x32) = D_1F8000C0_4e9b.y;
    M2C_FIELD(a, s16 *, 0x36) = D_1F8000C0_4e9b.z;
    M2C_FIELD(a, s16 *, 0x56) = M2C_FIELD(p, s16 *, 0x56);
    func_800517F8(a);
    if (M2C_FIELD(a, s16 *, 0xE) == 5 && !(D_800BFA06 & 1)) {
        e = func_80072DDC(a, 0, 2, 0x1E);
        if (e != NULL) {
            M2C_FIELD(e, void **, 0x1C) = f_UpdatePipeAreaPersistentSceneryRewardActor;
            e[3] = 0;
            a[0] = 3;
        }
    }
}

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

void func_8012ABB4(u8 *a) {
    s32 n;
    s32 x;

    if (a[0x47] == 2) {
        return;
    }
    if (a[0x2B] != 0) {
        n = (u16)(M2C_FIELD(M2C_FIELD(a, u8 **, 0xC0), u16 *, 0x3A) / 320);
        if (n == 0) {
            n = 1;
        } else if (n >= 5) {
            n = 4;
        }
        M2C_FIELD(a, s16 *, 0x7C) = 0;
        M2C_FIELD(a, s16 *, 0x7E) = n * 8;
        func_80074590(0x81, 0, 0);
        return;
    }
    x = (M2C_FIELD(a, u16 *, 0x7C) + 0x1E0) & 0xFFF;
    M2C_FIELD(a, s16 *, 0x7C) = x;
    if (x < 0x1E0 && M2C_FIELD(a, s16 *, 0x7E) != 0) {
        M2C_FIELD(a, s16 *, 0x7E) -= 8;
    }
}

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

extern u8 D_800BF9FA;
extern u8 D_1F800233;
void func_8012C410(u8 *a) {
    switch (a[5]) {
    case 0 ... 5:
        a[0] = 1;
        a[4] = 1;
        break;
    case 6:
        func_800521F4(0, 1, 0xC0, 4);
        D_800BF9FA = 0x19;
        func_80042354(1, 1);
        func_80054198(D_800E7E80);
        func_80027144(M2C_FIELD(M2C_FIELD(a, u8 **, 0xC0), s32 *, 0x40), a + 0x2C, 0x600, 8);
        func_80074590(0xC, 0, 0);
        func_80074810(0x97, 0);
        func_80043B88(1);
        *(volatile u8 *)&D_1F800233 = 1;
        func_8001D71C(1);
        a[4] = 3;
        break;
    }
}

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

extern u8 D_8001B7B0[];
void D_8004C930();
void func_8012C600(u8 *a, s32 b) {
    u16 v;
    u8 *p;

    switch (a[5]) {
    case 0:
        if (a[0x29] == 1) {
            a[5]++;
            func_8012C4F4(a, 0, b);
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

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8012C8C0);

extern s16 D_800ED098;
extern s16 D_1F8001A0_b0de;
extern s16 D_1F8001A2;
typedef struct {
    u8 b[0x56];
    s16 h56;
    u8 pad58[8];
    s16 h60;
    s16 h62;
    u8 pad64[0x5C];
    u8 *parts[3];
} DoorActor;
s32 func_8012CB28(DoorActor *a, s16 *d) {
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
    x = D_1F8001A0_b0de;
    y = D_1F8001A2;
    a->h60 = x;
    a->h62 = y;
    a->h56 = x;
    M2C_FIELD(a->parts[0], s16 *, 0xA) = M2C_FIELD(a->b, s16 *, 0x7C);
    return 0;
}

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

#define AREA_gte_ldv0(r0) __asm__ volatile("lwc2	$0, 0( %0 );" "lwc2	$1, 4( %0 )" : : "r"(r0))
typedef struct {
    s16 x, y, z, pad;
} SVecE;
extern s32 D_1F800088;
extern s32 D_1F800090_3460;
void func_8012E5F8(u8 *a) {
    SVecE v;
    s32 t;
    u8 *q = a;

    func_800329E0(6);
    v.x = M2C_FIELD(a, s16 *, 0x2E);
    v.y = M2C_FIELD(a, s16 *, 0x32);
    v.z = M2C_FIELD(a, s16 *, 0x36);
    AREA_gte_ldv0(&v);
    if (func_800317CC(0) != 0) {
        func_80031780(a);
    } else {
        t = *(volatile s32 *)&D_1F800084;
        *(volatile s32 *)&D_1F800090_3460 = 0;
        D_1F800088 = t;
        M2C_FIELD(q, s32 *, 0x64) = func_80027A4C(M2C_FIELD(q, s32 *, 0x60), M2C_FIELD(q, s32 *, 0x70));
    }
}

void func_8012E6A0(u8 *a) {
    u8 *p;

    switch (a[4]) {
    case 0:
        a[4] = 1;
    case 1:
        M2C_FIELD(a, s16 *, 0x2E) -= 4;
        p = M2C_FIELD(a, u8 **, 0x38);
        M2C_FIELD(a, u8 **, 0x34) = p;
        if (p == NULL) {
            a[4] = 2;
            break;
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

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8012E74C);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8012E868);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8012E974);

void func_8012EA70(u8 *a) {
    u8 *p;

    switch (a[4]) {
    case 0:
        a[4] = 1;
    case 1:
        M2C_FIELD(a, s16 *, 0x2E) -= 0x12;
        p = M2C_FIELD(a, u8 **, 0x38);
        M2C_FIELD(a, u8 **, 0x34) = p;
        if (p == NULL) {
            a[4] = 2;
            break;
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

#define gte_ldfcdir(r0, r1, r2) __asm__ volatile("ctc2	%0, $21;" "ctc2	%1, $22;" "ctc2	%2, $23" : : "r"(r0), "r"(r1), "r"(r2))
extern s32 D_1F800090[];
extern u8 D_800A1CD4[];
extern u8 D_80137D94[];
extern s16 D_801388EC;
extern s16 D_801388EE;
extern s16 D_80139004;
extern s16 D_801388F0;
extern u8 D_80138AC0[];
void func_8012EC08(u8 *p) {
    s32 *d = D_1F800090;

    gte_ldfcdir(0, 0, 0);
    *d = M2C_FIELD(p, s32 *, 0x50);
    func_800318A0(p + 0x2C, D_800A1CD4, p + 0x48);
    func_80027768(D_80137D94, M2C_FIELD(p, s16 *, 0x4E), M2C_FIELD(p, s16 *, 0x32), 0);
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_8012EC78);

#define gte_ldfcdir(r0, r1, r2) __asm__ volatile("ctc2	%0, $21;" "ctc2	%1, $22;" "ctc2	%2, $23" : : "r"(r0), "r"(r1), "r"(r2))
void func_8012ED88(u8 *p) {
    s32 *d = D_1F800090;
    s32 i;

    gte_ldfcdir(0, 0, 0);
    *d = 0;
    for (i = 0; i < 4; i++) {
        func_80031AC4(p + 0x2C, p + 0x50, p + 0x48);
        func_80027768(M2C_FIELD(p, s32 *, 0x3C), 0, M2C_FIELD(p, s16 *, 0x32), 0);
        M2C_FIELD(p, s16 *, 0x4E) += 0x400;
    }
}

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

void func_801321C4(RECT16 *a) {
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

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80132358);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80132690);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_801329C4);

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_80132DC0);

#define AREA_gte_lddp(r0) __asm__ volatile("mtc2	%0, $8" : : "r"(r0))
#define AREA_gte_ldrgb_r(r0) __asm__ volatile("mtc2	%0, $6" : : "r"(r0))
#define AREA_gte_dpcs() __asm__ volatile("nop;" "nop;" ".word 0x4A780010")
#define AREA_gte_strgb(r0) __asm__ volatile("swc2	$22, 0( %0 )" : : "r"(r0) : "memory")
extern u32 D_1F800080;
void func_80132EFC(u32 *p, s32 b) {
    u32 s = D_1F800080 * 0x41C64E6D + 0x3039;

    D_1F800080 = s;
    AREA_gte_lddp(b / 4 + (s >> 22));
    AREA_gte_ldrgb_r(*p);
    AREA_gte_dpcs();
    AREA_gte_strgb(p);
}

void func_80132F5C(void) {
    u32 i;
    u8 *p;

    D_801388EC = 0;
    D_801388EE = 0;
    D_80139004 = 0;
    D_801388F0 = 0;
    if (D_800BF873 != 0) {
        for (i = 0, p = D_80138AC0; i < 6; i++, p += 8) {
            func_801321C4(p);
        }
    }
}

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

#define GTE_RTPT() __asm__ volatile("nop;" "nop;" ".word 0x4A280030")
#define GTE_RTPS() __asm__ volatile("nop;" "nop;" ".word 0x4A180001")
#define GTE_NCLIP() __asm__ volatile("nop;" "nop;" ".word 0x4B400006")
#define GTE_AVSZ4() __asm__ volatile("nop;" "nop;" ".word 0x4B68002E")
s32 func_801341E8(u8 *poly, u8 *v, s32 *flag) {
    s32 otz;
    s32 n;

    gte_ldv3c(v);
    GTE_RTPT();
    gte_stflg(flag);
    if (*flag < 0) {
        return -1;
    }
    gte_stsxy3_gt3(poly);
    GTE_NCLIP();
    gte_stopz(flag);
    n = *flag;
    if (n < 0) {
        n = -n;
    }
    if (n < 8) {
        return -1;
    }
    gte_ldv0(v + 0x18);
    GTE_RTPS();
    gte_stflg(flag);
    if (*flag < 0) {
        return -1;
    }
    gte_stsxy(poly + 0x2C);
    GTE_AVSZ4();
    gte_stotz(&otz);
    return otz;
}

INCLUDE_ASM("asm/a01/nonmatchings/a01", func_801342C8);

INCLUDE_ASM("asm/a01/nonmatchings/a01", f_UpdatePipeAreaTrolleyNpcDialogue);

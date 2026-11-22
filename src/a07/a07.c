#include "common.h"
#include "game.h"
#include "m2c.h"
#include "gte.h"

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8010A660);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8010A7FC);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8010A8F0);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8010AAA8);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8010ABE4);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8010AE18);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8010AFFC);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8010B1E0);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8010B3F8);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8010B5BC);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8010B6F4);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8010B944);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8010BAD0);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8010BC9C);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8010BE08);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8010BF14);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8010C0B8);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8010C1C8);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8010C3C4);

INCLUDE_ASM("asm/a07/nonmatchings/a07", f_DispatchCircusMovingActorContacts);

INCLUDE_ASM("asm/a07/nonmatchings/a07", f_DispatchCircusActorContacts);

INCLUDE_ASM("asm/a07/nonmatchings/a07", f_DispatchCircusActorContactCleanup);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8010CA60);

INCLUDE_ASM("asm/a07/nonmatchings/a07", f_DispatchCircusSupportContacts);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8010CD8C);

extern u8 D_800BF808[];
void func_80118184();
void func_8010CEDC(u8 *p)
{
    if (p[0x17B] == 0 && (s8)D_800BF808[5] == 0 && D_800BF808[0x31] == 0) {
        func_8010A7FC();
    }
}

extern u8 *D_800BF844;
s32 func_8010CF30(u8 *p)
{
    if (p[0x174]) {
        return 1;
    }
    {
        u32 r = *(u16 *)(p + 0x17E) & 0x200;
        return r != 0;
    }
}

extern s8 D_1F80009C[];
void func_8010CF5C(void *arg0, void *arg1) {
    s32 temp_lo;
    s32 temp_s0;

    if (func_80022F04() != 0) {
        temp_s0 = (s32) (func_80083F50(*((s32 *)D_1F80009C)) * (M2C_FIELD(arg0, s16 *, 0x80) + M2C_FIELD(arg1, s16 *, 0x80))) >> 0xC;
        temp_lo = func_80083E80(*((s32 *)D_1F80009C)) * (M2C_FIELD(arg0, s16 *, 0x80) + M2C_FIELD(arg1, s16 *, 0x80));
        M2C_FIELD(arg0, s16 *, 0x2E) = (s16) (M2C_FIELD(arg1, u16 *, 0x2E) + temp_s0);
        M2C_FIELD(arg0, s16 *, 0x36) = (s16) (M2C_FIELD(arg1, u16 *, 0x36) - (temp_lo >> 0xC));
    }
}

typedef struct { s16 x, y, z, pad; } AreaSVec;
typedef struct {
    u16 type;
    u8 pad2[6];
    u8 mag0;
    u8 mag1;
    u8 x;
    u8 y;
} AreaPadAnalog;
typedef struct { u8 pad0[7]; u8 unk7; u8 pad8[0x29]; u8 unk31; s16 unk32; } AreaState808_7;
extern u8 **D_1F800154;
extern u8 D_1F80015C;
extern u8 D_1F800183;
void func_8010D004(void) {
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
                f_DispatchCircusSupportContacts(a);
                break;
            }
        }
    }
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8010D0B4);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8010D49C);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8010D6A8);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8010D84C);

extern AreaPadAnalog D_800ECF48;
extern u16 D_800ECF54;
void func_8010DAB4(u8 *a) {
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

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8010DC3C);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8010DE18);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8010DF90);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8010E244);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8010E448);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8010E728);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8010E864);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8010EEB8);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8010F08C);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8010F28C);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8010F954);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8010FC30);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8010FF78);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80110258);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_801103D8);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80110850);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80110A30);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_801110F8);

INCLUDE_ASM("asm/a07/nonmatchings/a07", f_UpdateCircusRestrictedTombaActionState);

INCLUDE_ASM("asm/a07/nonmatchings/a07", f_UpdateCircusTombaActionState);

extern u16 D_800E7E68;
extern u8 D_800BF80F;
extern u8 D_1F800137;
extern u16 D_1F800166;
extern u16 D_1F800190;
void func_80112220(u8 *a) {
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
        f_UpdateCircusRestrictedTombaActionState(a);
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
        f_UpdateCircusTombaActionState(a);
        func_800597AC(a);
        D_800E7E68 = held;
        D_800ECF54 = pad;
        break;
    }
}

extern u8 D_800BF80E;
void func_8011237C(u8 *a)
{
    u8 *o = *(u8 **)(a + 0x10);

    switch (a[6]) {
    case 0:
        o[0x2B] = 1;
        a[6]++;
        D_800BF80E = 1;
    case 1:
        func_80076D68(a);
        if (D_1F800137 == 0) {
            D_800BF80E = 0;
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

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80112428);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80112508);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80112770);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_801128BC);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_801129A8);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80112B1C);

// nearcopy: 9 words off, C from a0k func_8010B5EC
#include "common.h"
#include "game.h"
#include "m2c.h"
#include "gte.h"
extern u8 D_1F8000D0[];
extern s16 D_1F8000EE;
extern u8 D_800BF816;
void func_80112CE8(u8 *a, s16 b)
{
    s16 v;
    s16 y;
    s16 d;
    u8 *c;

    if (a[0x64] == 1) {
        s32 ang;
        if (D_800BF816 != 0) {
            ang = *(s16 *)(a + 0x6E);
        } else {
            ang = *(s16 *)(a + 0xA);
        }
        v = -(func_80083E80(ang) * *(s16 *)(a + 0x6C)) >> 12;
    } else {
        v = (func_80083E80(*(s16 *)(a + 0xA)) * (D_1F8000EE + *(s32 *)(a + 0x58))) >> 12;
    }
    y = b + v;
    *(s16 *)(a + 0xE) = y;
    c = D_1F8000D0;
    d = *(s16 *)(c + 6) - y;
    if ((u16)(d + 10) >= 21) {
        *(s32 *)(c + 4) -= d << 13;
    } else {
        *(s16 *)(c + 6) = y;
        a[0x66] |= 2;
    }
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80112DEC);

extern u8 D_800E7E80[];
extern u8 D_1F8000D0[];
void func_80113394(u8 *a, s32 ang) {
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

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80113470);

typedef struct {
    s16 a;
    s16 b;
    s16 c;
    s16 d;
} SV;
extern u8 D_800BFA2D;
extern u8 *D_800BF860_c64f;
extern u8 D_800BFA2C;
void f_UpdateCircusClosetKeyActor();
void func_801134E8(u8 *a0, u8 *a1)
{
    s32 neg = 0;
    s16 d = *(u16 *)(a1 + 0x36) - 0x2968;
    s16 m = d;

    if (d < 0) {
        neg = 1;
        m = -d;
    }
    m = m / 4;
    if (m > 0x300) {
        m = 0x300;
    }
    if (!neg) {
        m = 0x800 - m;
    } else {
        m = m + 0x800;
    }
    *(s16 *)(a0 + 0x52) = m;
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80113550);

void func_80113644(void)
{
    CameraState *c = &g_CameraState;

    c->unk6C = 0x500;
    c->unk6E = 0x100;
}

extern u16 D_1F8000F2;
void func_80113660(u8 *a) {
    u8 *t = D_800E7E80;
    s16 v[6];

    switch (a[4]) {
    case 0:
        M2C_FIELD(a, s16 *, 0x52) = 0x1400 - D_1F8000F2;
        a[4]++;
        break;
    case 1:
        v[1] = M2C_FIELD(t, s16 *, 0x2E);
        v[3] = M2C_FIELD(t, s16 *, 0x32) - 0x80;
        v[5] = M2C_FIELD(t, s16 *, 0x36);
        func_8006E3F4(a, v);
        func_80112B1C(a, t, M2C_FIELD(a, s16 *, 0x52));
        func_80112CE8(a, (s16)(M2C_FIELD(t, s16 *, 0x32) - 0x80));
        break;
    }
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", f_UpdateCircusInteriorSceneTransition);

INCLUDE_ASM("asm/a07/nonmatchings/a07", f_SpawnCircusSceneActorsFromPlacementTable);

typedef struct { s16 x, y, w, h; } ClutRect;
typedef struct {
    u8 *ptr;
    u8 *clut;
    s16 x;
    s16 y;
} ClutCycle;
extern ClutCycle D_80132B14[];
extern s8 D_8013FF40[];
extern u8 D_800BF873;
void func_80113C20(s32 arg0) {
    ClutRect r;
    s32 i;
    ClutCycle *e;
    u8 *data;

    if (arg0 == 0) {
        s8 *p;
        i = 4;
        p = &D_8013FF40[i];
        do {
            *p-- = 0;
        } while (--i >= 0);
        return;
    }
    if (D_800BF873) {
        return;
    }
    e = D_80132B14;
    for (i = 0; i < 5; i++, e++) {
        if (--D_8013FF40[i] <= 0) {
            if (e->ptr[0] == 0xFF) {
                e->ptr -= e->ptr[1];
            }
            data = e->clut + e->ptr[0] * 32;
            D_8013FF40[i] = e->ptr[1];
            r.x = e->x;
            r.y = e->y;
            r.w = 16;
            r.h = 1;
            func_80081218(&r, data);
            e->ptr += 2;
        }
    }
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80113D58);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_801140A0);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80114294);

#define W(p, o) M2C_FIELD(p, u32 *, o)
typedef struct {
    u8 b[6][4];
} FlickerTbl;
extern FlickerTbl D_801094E8;
void func_801143C0(u8 *a) {
    FlickerTbl t = D_801094E8;

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

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_801145E0);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80114770);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8011490C);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80114ADC);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80114CF8);

#define gte_ldfcdir(r0, r1, r2) __asm__ volatile("ctc2	%0, $21;" "ctc2	%1, $22;" "ctc2	%2, $23" : : "r"(r0), "r"(r1), "r"(r2))
extern s32 D_1F800090[];
extern u8 D_80133F20[];
extern u8 D_80133F90[];
void func_80114F9C(u8 *p)
{
    s32 *d = D_1F800090;

    gte_ldfcdir(0, 0, 0);
    *d = *(s32 *)(p + 0x54);
    func_800318A0(p + 0x2C, p + 0x50, p + 0x48);
    func_80027768(*(s32 *)(p + 0x3C), *(u16 *)(p + 0x44), *(s16 *)(p + 0x32), p[0x29]);
}

void func_80115008(u8 *a)
{
    switch (a[4]) {
    case 0:
        *(s16 *)(a + 0x32) = -0x5A;
        a[4] = 1;
        a[5] = 0x1E;
        *(s32 *)(a + 0x50) = 0;
        {
            s32 h = func_8009A450();
            *(s32 *)(a + 0x54) = (h << 16) | func_8009A450() | 1;
        }
    case 1:
        { u8 c = a[5]; a[5] = c + 0xFF; if (c == 0) {
            a[4] = 2;
        } }
        a[1] = 1;
        *(s32 *)(a + 0x50) += 2;
        break;
    case 2:
    case 3:
        func_8007A624(a);
        break;
    }
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_801150DC);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80115174);

void func_80115174();
u8 *func_80115334(void)
{
    u8 *a = func_8007A980(0, 3, 1);

    if (a == NULL) {
        return NULL;
    }
    *(void **)(a + 0x1C) = func_80115174;
    a[2] = 1;
    a[0x28] |= 0x80;
    return a;
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80115388);

#define F16(p, o) M2C_FIELD(p, s16 *, o)
extern u8 D_800BF818_7697;
void func_8011545C(u8 *a, u8 *b) {
    u8 *t;

    switch (a[5]) {
    case 0:
        a[5]++;
        F16(b, 0xE) = F16(b, 0xA);
        func_80072FE0(a);
        a[0x5E] = 1;
        break;
    case 1:
        if (D_800BF818_7697 == 2) {
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
        t = D_800BF808;
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
            D_800BF818_7697 = 0;
        }
        break;
    }
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80115618);

typedef struct { u8 pad[0xC0]; u8 *parts[1]; } PartsOwner;
typedef struct { s16 v[4]; } PartInit;
extern s16 D_800ED098;
extern PartInit D_80133030[];
extern u8 D_800BF8DC;
void func_80115A2C(PartsOwner *a)
{
    s32 i;
    u8 *q;
    s32 k;

    a->pad[8] = 3;
    k = 3;
    if (D_800ED098 < k) {
        a->pad[4] = k;
        return;
    }
    a->pad[9] = k;
    a->pad[0xD] = 0;
    a->pad[0xB] = 0;
    *(s16 *)(a->pad + 0x54) = 0;
    *(s16 *)(a->pad + 0x56) = 0;
    *(s16 *)(a->pad + 0x58) = 0;
    for (i = 0; i < a->pad[8]; i++) {
        q = func_8007AAE8();
        a->parts[i] = q;
        *(s16 *)(q + 6) = D_80133030[i].v[0];
        *(s16 *)(a->parts[i] + 0) = D_80133030[i].v[1];
        *(s16 *)(a->parts[i] + 2) = D_80133030[i].v[2];
        *(s16 *)(a->parts[i] + 4) = D_80133030[i].v[3];
        *(s16 *)(a->parts[i] + 8) = 0;
        *(s16 *)(a->parts[i] + 0xA) = 0;
        *(s16 *)(a->parts[i] + 0xC) = 0;
        func_80051B04(a->parts[i], 0xC, i + 0x20);
    }
    a->pad[0x2B] = 0;
    if (D_800BF8DC == 0xFF) {
        a->pad[4] = 3;
        return;
    }
    *(s16 *)(a->pad + 0x4E) = *(s16 *)(a->pad + 0x2E);
    *(s16 *)(a->pad + 0x50) = *(s16 *)(a->pad + 0x32);
    *(s16 *)(a->pad + 0x52) = *(s16 *)(a->pad + 0x36);
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", f_UpdateClownStatueDestructionSequence);

void func_80116538(PartsOwner *a)
{
    s32 i;
    u8 *q;

    s32 k;
    a->pad[8] = 3;
    k = 3;
    if (D_800ED098 < k) {
        a->pad[4] = k;
        return;
    }
    a->pad[9] = 3;
    a->pad[0xD] = 4;
    a->pad[0xBF] = 0;
    for (i = 0; i < a->pad[8]; i++) {
        q = func_8007AAE8();
        a->parts[i] = q;
        *(s16 *)(q + 6) = -1;
        *(s16 *)(a->parts[i] + 0) = 0;
        *(s16 *)(a->parts[i] + 2) = 0;
        *(s16 *)(a->parts[i] + 4) = 0;
        *(s16 *)(a->parts[i] + 8) = 0;
        *(s16 *)(a->parts[i] + 0xA) = 0;
        *(s16 *)(a->parts[i] + 0xC) = 0;
        func_80051B04(a->parts[i], 0xC, i + 0x33);
        a->parts[i][0x3F] = 0;
    }
}

extern PartInit D_80133048[];
void func_80116634(PartsOwner *a)
{
    s32 i;
    u8 *q;
    PartInit *t;

    a->pad[8] = 2;
    if (D_800ED098 < a->pad[8]) {
        a->pad[4] = 3;
        return;
    }
    a->pad[9] = 2;
    a->pad[0xD] = 0;
    a->pad[0xB] = 0;
    *(s16 *)(a->pad + 0x54) = 0;
    *(s16 *)(a->pad + 0x56) = 0;
    *(s16 *)(a->pad + 0x58) = 0;
    for (i = 0; i < a->pad[8]; i++) {
        q = func_8007AAE8();
        a->parts[i] = q;
        *(s16 *)(q + 6) = D_80133048[i].v[0];
        *(s16 *)(a->parts[i] + 0) = D_80133048[i].v[1];
        *(s16 *)(a->parts[i] + 2) = D_80133048[i].v[2];
        *(s16 *)(a->parts[i] + 4) = D_80133048[i].v[3];
        *(s16 *)(a->parts[i] + 8) = 0;
        *(s16 *)(a->parts[i] + 0xA) = 0;
        *(s16 *)(a->parts[i] + 0xC) = 0;
        func_80051B04(a->parts[i], 0xC, i + 0x25);
    }
    *(s16 *)(a->parts[1] + 0xC) = 0x1000;
    a->pad[0x2B] = 0;
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80116764);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80116A0C);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80116B88);

void func_80117048(void *arg0) {
    if (D_800BFA2C != 0) {
        M2C_FIELD(arg0, s8 *, 6) = 0xA;
    } else {
        M2C_FIELD(arg0, s8 *, 6) = 0;
    }
    func_80051B70(arg0, 0xC, 0x14);
    M2C_FIELD(arg0, s16 *, 0x56) = -0x400;
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8011709C);

void func_80116B88();
extern s32 D_800ECF80_d353;
extern u8 D_8013FF68[];
u8 *func_8011718C(void *a0)
{
    u8 *r = func_80072DDC(a0, 0, 3, 0x10);

    if (r == 0) {
        return 0;
    }
    r[3] = 3;
    *(void **)(r + 0x1C) = func_80116B88;
    *(void **)(r + 0x10) = a0;
    r[0x28] |= 0x80;
    return r;
}

void func_801171EC(u8 *p)
{
    *(s32 *)(p + 0x3C) = D_800ECF80_d353;
    func_80077B38(p, D_8013FF68, 0xC);
    p[0xB] = 0x10;
    *(s16 *)(p + 0x2E) = 0x67E;
    *(s16 *)(p + 0x32) = -0xAF0;
    p[0xD] = 0;
    *(s16 *)(p + 0x5C) = 0;
    *(s16 *)(p + 0x5A) = 0;
    p[0x47] = 0;
    p[8] = 0;
    *(s16 *)(p + 0x36) = 0x1AC2;
}

void func_8011725C(void *arg0) {
    if (D_800BF816 == 0) {
        M2C_FIELD(arg0, s8 *, 4) = 3;
        return;
    }
    func_8007778C();
}

extern u8 D_800BFA3C;
void func_80117294(u8 *p)
{
    switch (p[5]) {
    case 0:
        if (D_800BFA3C) {
            p[5] = 1;
        }
        break;
    case 1:
        p[1] = 1;
        func_800517F8(p);
        break;
    }
}

void func_801172F0(void *a)
{
    func_80051B70(a, 0xC, 0x37);
    func_800517F8(a);
}

void func_80117324(void) {
    func_8007778C();
}

extern u8 D_80017FE8[];
extern s32 D_800ECF68;
extern u8 D_8014005C_9175[];
extern s32 D_800ECF90;
u8 *func_80117344(void *a0, u8 a1)
{
    u8 *r = func_80072DDC(a0, 2, 3, 0x10);

    if (r == 0) {
        return 0;
    }
    r[3] = 6;
    *(void **)(r + 0x1C) = func_80116B88;
    *(void **)(r + 0x10) = a0;
    r[0x5E] = a1;
    return r;
}

void func_80116B88(u8 *);
u8 *func_801173A8(void *owner)
{
    u8 *e = func_80072DDC(owner, 0, 3, 0x10);

    if (e != 0) {
        *(void **)(e + 0x1C) = func_80116B88;
        e[3] = 7;
    }
    return e;
}

extern u16 D_800E7FFE;
extern u16 D_800BFE56;
void func_801173EC(u8 *p)
{
    *(s32 *)(p + 0x3C) = D_800ECF80_d353;
    func_80077B38(p, D_8013FF68, 0xD);
    p[0xB] = 0x10;
    *(s16 *)(p + 0x5C) = 0;
    *(s16 *)(p + 0x5A) = 0;
    p[0x47] = 0;
    p[8] = 0xF0;
}

u8 *func_80117444(void *a0)
{
    u8 *r = func_80072DDC(a0, 0, 3, 0x10);

    if (r == 0) {
        return 0;
    }
    r[3] = 8;
    *(void **)(r + 0x1C) = func_80116B88;
    *(void **)(r + 0x10) = a0;
    r[0x28] |= 0x80;
    return r;
}

extern void *D_800ECF80;
void func_801174A4(u8 *a)
{
    *(void **)(a + 0x3C) = D_800ECF80;
    func_80077B38(a, D_8013FF68, 0x7);
    a[0xD] = 0;
    *(s16 *)(a + 0x5C) = 0;
    a[0xB] = 0x10;
    *(s16 *)(a + 0x5A) = 0;
    a[0x47] = 0;
    a[8] = 0;
}

void func_801174FC(void *arg0) {
    void *temp_s0;

    temp_s0 = M2C_FIELD(arg0, void **, 0x10);
    M2C_FIELD(arg0, s16 *, 0x2E) = (s16) (M2C_FIELD(M2C_FIELD(temp_s0, void **, 0xC0), u16 *, 0x2C) + ((s32) (func_80083F50(M2C_FIELD(temp_s0, s16 *, 0x56)) * 0x32) >> 0xC));
    M2C_FIELD(arg0, u16 *, 0x32) = (u16) M2C_FIELD(M2C_FIELD(temp_s0, void **, 0xC0), u16 *, 0x30);
    M2C_FIELD(arg0, s16 *, 0x36) = (s16) (M2C_FIELD(M2C_FIELD(temp_s0, void **, 0xC0), u16 *, 0x34) - ((s32) (func_80083E80(M2C_FIELD(temp_s0, s16 *, 0x56)) * 0x32) >> 0xC));
    M2C_FIELD(arg0, u16 *, 0x56) = (u16) M2C_FIELD(temp_s0, s16 *, 0x56);
    func_8007778C(arg0);
}

void func_80116B88();
u8 *func_801175B8(void *a)
{
    u8 *r = func_80072DDC(a, 0, 3, 0x10);

    if (r != NULL) {
        *(void **)(r + 0x1C) = func_80116B88;
        r[3] = 0x9;
    }
    return r;
}

void func_801175FC(u8 *p)
{
    *(s32 *)(p + 0x3C) = D_800ECF80_d353;
    func_80077B38(p, D_8013FF68, 0x10);
    p[0xB] = 0x10;
    p[0xD] = 1;
    *(s16 *)(p + 0x5C) = 0;
    *(s16 *)(p + 0x5A) = 0;
    p[0x47] = 0;
    p[8] = 0xF0;
}

void func_8011765C(void *arg0) {
    M2C_FIELD(arg0, s8 *, 1) = 1;
    func_80077B5C();
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80117680);

void func_80117680();
u8 *func_801178E4(s32 unused)
{
    u8 *r = func_8007A980(1, 3, 1);

    if (r == 0) {
        return 0;
    }
    r[2] = 0x12;
    r[3] = 0;
    *(void **)(r + 0x1C) = func_80117680;
    r[0x28] |= 0x80;
    return r;
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8011793C);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80117AB8);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80117D4C);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80117FE0);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80118184);

extern void *D_800BF864;
void func_80118270(void *arg0) {
    void *temp_v1;

    temp_v1 = arg0 + 0x60;
    M2C_FIELD(arg0, s16 *, 0x60) = 0;
    M2C_FIELD(temp_v1, s16 *, 2) = 0x299F;
    M2C_FIELD(temp_v1, s16 *, 4) = -0xC80;
    D_800BF864 = arg0;
}

u8 *func_80118294(void *a0)
{
    u8 *r = func_80072DDC(a0, 0, 3, 0x18);

    if (r == 0) {
        return 0;
    }
    r[3] = 1;
    *(void **)(r + 0x1C) = func_80118184;
    *(void **)(r + 0x10) = a0;
    return r;
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", f_UpdateCircusSeesawLaunchedActorSequence);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80118BB4);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80118EDC);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80119070);

void func_8011926C(u8 *a)
{
    if (--*(s16 *)(a + 0x40) == 0) {
        *(s16 *)(a + 0x40) = 15;
        if (*(s16 *)(a + 0x42) == 0) {
            func_80077B38(a, D_8013FF68, 8);
        } else {
            func_80077B38(a, D_8013FF68, 9);
        }
        *(s16 *)(a + 0x42) ^= 1;
    }
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_801192F0);

void func_80119454();
u8 *func_801193DC(void *a)
{
    u8 *r = func_80072DDC(a, 1, 3, 0x28);

    if (r != NULL) {
        *(void **)(r + 0x1C) = func_80119454;
    }
    return r;
}

void func_80119070();
u8 *func_80119418(void *a0)
{
    u8 *r = func_80072DDC(a0, 0, 3, 0x27);

    if (r) {
        *(void **)(r + 0x1C) = func_80119070;
    }
    return r;
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80119454);

INCLUDE_ASM("asm/a07/nonmatchings/a07", f_UpdateCircusGearMechanismActor);

INCLUDE_ASM("asm/a07/nonmatchings/a07", f_UpdateCircusInteriorEntranceTransition);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80119C84);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80119DA0);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80119F74);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8011A174);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8011A398);

void func_8011A83C(void) {
    f_UpdateCircusInteriorEntranceTransition();
}

void func_8011A85C(void) {
    f_UpdateCircusInteriorEntranceTransition();
}

void func_8011A87C(void) {
    f_UpdateCircusInteriorEntranceTransition();
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8011A89C);

void func_8011A980(void) {
    f_UpdateCircusInteriorEntranceTransition();
}

void func_8011A9A0(void) {
    if ((D_800BF870.pad1[0x67] != 0) || (M2C_FIELD(&D_800BF870, u16 *, 0x2E) & 0x200)) {
        f_UpdateCircusInteriorEntranceTransition();
    }
}

void func_8011A9EC(void) {
    f_UpdateCircusInteriorEntranceTransition();
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8011AA0C);

void func_8011AAFC(void) {
    f_UpdateCircusInteriorEntranceTransition();
}

void func_8011AB1C(void) {
    f_UpdateCircusInteriorEntranceTransition();
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8011AB3C);

typedef struct { s16 m[3][3]; s16 pad; s32 t[3]; } AreaMatrix;
extern AreaSVec D_1F8000C0_f4ad;
typedef struct { u8 pad[0x28]; AreaMatrix m; } AreaScratchD0;
extern AreaScratchD0 D_1F8000D0_2539;
extern AreaMatrix D_1F800000;
void func_8011AD44(u8 *a) {
    D_1F8000C0_f4ad.x = M2C_FIELD(M2C_FIELD(a, u8 **, 0xC0), s16 *, 0x2C);
    D_1F8000C0_f4ad.y = M2C_FIELD(M2C_FIELD(a, u8 **, 0xC0), s16 *, 0x30);
    D_1F8000C0_f4ad.z = M2C_FIELD(M2C_FIELD(a, u8 **, 0xC0), s16 *, 0x34);
    func_80084110(&D_1F8000D0_2539.m, M2C_FIELD(a, u8 **, 0xC0) + 0x18, &D_1F800000);
    func_80084220(&D_1F8000C0_f4ad, D_1F800000.t);
    D_1F800000.t[0] += D_1F8000D0_2539.m.t[0];
    D_1F800000.t[1] += D_1F8000D0_2539.m.t[1];
    D_1F800000.t[2] += D_1F8000D0_2539.m.t[2];
    func_80084660(&D_1F800000);
    func_80084690(&D_1F800000);
    func_8011AB3C(a);
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8011AE24);

void func_8011B030(u8 *a)
{
    s32 s = a[4];
    switch (s) {
    case 0:
        func_8011AE24(a);
        break;
    case 1:
        *(s16 *)(a + 0x56) = -D_1F8000F2;
        func_800517F8(a);
        a[1] = s;
        func_80077EBC(a);
        a[0x2B] = 0;
        break;
    case 2:
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

void func_8011B0E0(void *arg0) {
    M2C_FIELD(arg0, s16 *, 0x56) = (s16) -(s16) *(u16 *)0x1F8000F2;
    func_800517F8();
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8011B10C);

void func_8011B3B8(u8 *a) {
    switch (a[4]) {
    case 0:
        a[4] = 1;
        a[0] = 1;
        if (a[3] == 0) {
            M2C_FIELD(a, s16 *, 0x80) = 0x9C;
            M2C_FIELD(a, s16 *, 0x82) = 0x138;
            M2C_FIELD(a, s16 *, 0x84) = 0xC8;
            M2C_FIELD(a, s16 *, 0x86) = 0x12C;
        }
        a[0x29] = 0;
        break;
    case 1:
        if (a[3] == 0) {
            func_8011B10C(a);
        }
        func_8007778C(a);
        a[0x29] = 0;
        break;
    case 2:
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8011B480);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8011B650);

INCLUDE_ASM("asm/a07/nonmatchings/a07", f_UpdateCircusClothesLockerActor);

void func_8011BAB4(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 4);
    switch (temp_v1) {                              /* irregular */
    case 0:
        func_8011B650();
        return;
    case 1:
        f_UpdateCircusClothesLockerActor();
        return;
    case 3:
        func_8007A624();
        /* fallthrough */
    case 2:
        return;
    }
}

typedef struct { s16 p0, x, p4, y, p8, z; } HV;
extern u8 *D_1F800214_120a;
s32 func_8011BB38(u8 *a)
{
    HV v;
    u8 *g = D_1F800214_120a;

    switch (a[0x78]) {
    default:
        return 0;
    case 0:
        v.x = 0x63A;
        v.y = -0xAF0;
        v.z = 0x1B5C;
        func_80070F00(g, 1, &v);
        func_800708B4(3);
        a[0x78]++;
        break;
    case 1:
        if (g[3] == 0) {
            func_800708B4(1);
            *(s16 *)(a + 0x4A) = 0;
            return 1;
        }
        return 0;
    }
    return 0;
}

extern s8 D_1F800214[];
s32 func_8011BBE4(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x14) = func_80117444(*((s32 *)D_1F800214));
    return 1;
}

extern s8 D_1F800214[];
s32 func_8011BC1C(void *arg0) {
    func_80041718(*((s32 *)D_1F800214), 0, 4);
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x14), s8 *, 4) = 3;
    return 1;
}

typedef struct { u8 pad[0x60]; s32 unk60; s32 unk64; } AreaStateF58;
typedef struct { u8 pad0[7]; u8 unk7; u8 pad8[6]; u8 unkE; u8 unkF; u8 pad10[0x21]; u8 unk31; s16 unk32; } AreaState808_E;
typedef struct { u8 pad[0xC0]; u8 *parts[1]; } AreaPartsOwner;
typedef struct { s16 unk0; s16 x, y, z; } PartPose;
extern PartPose D_80133210[3];
extern PartPose D_80133228[3];
typedef struct { u8 pad[0x5E]; u8 pose; u8 pad2[0xC0 - 0x5F]; s16 *parts[3]; } PosedActor;
typedef struct { s16 x, y, z, pad; } RingVec;
typedef struct { s16 pos; s16 vel; } RiseMotion;
void func_8011BC60(PosedActor *a, s32 b, s32 c) {
    s32 i;

    for (i = 0; i < 3; i++) {
        if (b == 0) {
            func_80051B04(a->parts[i], c, i);
            a->parts[i][0] = D_80133210[i].x;
            a->parts[i][1] = D_80133210[i].y;
            a->parts[i][2] = D_80133210[i].z;
        } else {
            func_80051B04(a->parts[i], c, i + 3);
            a->parts[i][0] = D_80133228[i].x;
            a->parts[i][1] = D_80133228[i].y;
            a->parts[i][2] = D_80133228[i].z;
        }
    }
    a->pose = b;
}

extern u8 D_8001B7B0[];
void D_8004C930();
void func_8011BD6C(u8 *a, s32 b) {
    u16 v;
    u8 *p;

    switch (a[5]) {
    case 0:
        if (a[0x29] == 1) {
            a[5]++;
            func_8011BC60(a, 0, b);
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

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8011C02C);

void func_8011C2D0(u8 *a0)
{
    u8 *r = func_80072DDC(a0, 1, 3, 0x10);

    if (r) {
        *(void **)(r + 0x1C) = func_80116B88;
        r[3] = 5;
        *(s16 *)(r + 0x2E) = *(s16 *)(a0 + 0x2E);
        *(s16 *)(r + 0x32) = *(s16 *)(a0 + 0x32);
        *(s16 *)(r + 0x36) = *(s16 *)(a0 + 0x36);
    }
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8011C340);

void func_8011C4D0(void *arg0) {
    void *temp_a0;
    void *temp_a0_2;
    void *temp_a0_3;
    void *temp_a0_4;
    void *temp_a1;
    void *temp_a1_2;
    void *temp_a2;
    void *temp_a3;

    temp_a1 = M2C_FIELD(arg0, void **, 0xC0);
    temp_a3 = M2C_FIELD(arg0, void **, 0x10);
    temp_a2 = M2C_FIELD(arg0, s32 *, 0x14) + 0x60;
    M2C_FIELD(temp_a2, s16 *, 4) = (s16) (M2C_FIELD(temp_a1, u16 *, 0x2C) + ((s32) -(M2C_FIELD(temp_a1, s16 *, 0x1A) * 0xA0) >> 0xC));
    temp_a1_2 = M2C_FIELD(arg0, void **, 0xC0);
    M2C_FIELD(temp_a2, s16 *, 6) = (s16) (M2C_FIELD(temp_a1_2, u16 *, 0x30) + ((s32) -(M2C_FIELD(temp_a1_2, s16 *, 0x20) * 0xA0) >> 0xC));
    temp_a0 = M2C_FIELD(arg0, void **, 0xC0);
    M2C_FIELD(temp_a2, s16 *, 8) = (s16) (M2C_FIELD(temp_a0, u16 *, 0x34) + ((s32) -(M2C_FIELD(temp_a0, s16 *, 0x26) * 0xA0) >> 0xC));
    temp_a0_2 = M2C_FIELD(temp_a3, void **, 0xC0);
    M2C_FIELD(temp_a2, s16 *, 0xC) = (s16) (M2C_FIELD(temp_a0_2, u16 *, 0x2C) + ((s32) -(M2C_FIELD(temp_a0_2, s16 *, 0x18) * 0xA0) >> 0xC));
    temp_a0_3 = M2C_FIELD(temp_a3, void **, 0xC0);
    M2C_FIELD(temp_a2, s16 *, 0xE) = (s16) ((M2C_FIELD(temp_a0_3, u16 *, 0x30) + ((s32) -(M2C_FIELD(temp_a0_3, s16 *, 0x1E) * 0xA0) >> 0xC)) - 0xC8);
    temp_a0_4 = M2C_FIELD(temp_a3, void **, 0xC0);
    M2C_FIELD(temp_a2, s16 *, 0x10) = (s16) (M2C_FIELD(temp_a0_4, u16 *, 0x34) + ((s32) -(M2C_FIELD(temp_a0_4, s16 *, 0x24) * 0xA0) >> 0xC));
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", f_UpdateCircusWellLidActor);

INCLUDE_ASM("asm/a07/nonmatchings/a07", f_UpdateCircusSeesawActor);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8011CF1C);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8011D10C);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8011D2D8);

void func_8011D410(u8 *a)
{
    switch (a[4]) {
    case 0:
        *(s16 *)(a + 0x80) = 0x10E;
        *(s16 *)(a + 0x82) = 0x1F4;
        *(s16 *)(a + 0x84) = 0x64;
        a[4] = 1;
        a[0] = 1;
        *(s16 *)(a + 0x86) = 0xC8;
        break;
    case 1:
        func_8007778C(a);
        break;
    case 2:
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

extern u8 D_800BF809;
extern u8 D_800BF8E9;
extern u8 D_800E7EEF;
void func_8011D4AC(u8 *a)
{
    s16 sp[8];

    switch (a[4]) {
    case 0:
        if (func_80051B70(a, 0xC, 0x38) == 0) {
            *(s16 *)(a + 0x80) = 0x50;
            *(s16 *)(a + 0x82) = 0xA0;
            *(s16 *)(a + 0x84) = 0x140;
            *(s16 *)(a + 0x86) = 0x140;
            a[0] = 1;
            a[0x2B] = 0;
            a[0x29] = 0;
            *(s16 *)(a + 0x54) = 0;
            *(s16 *)(a + 0x56) = 0x638;
            *(s16 *)(a + 0x58) = 0;
            a[4]++;
        }
        break;
    case 1:
        if (a[0x29] != 0 && D_800BF8E9 == 0) {
            func_80040B48(0x35);
        }
        if (func_8007778C(a) != 0) {
            func_800517F8(a);
        }
        a[0x2B] = 0;
        a[0x29] = 0;
        break;
    case 2:
        switch (a[6]) {
        case 0:
            if (D_800E7EEF != 0x15) {
                a[0] = 1;
                a[4] = 1;
                a[5] = 0;
                a[6] = 0;
                a[0x29] = 0;
                if (func_8007778C(a) != 0) {
                    func_800517F8(a);
                }
            } else {
                a[6] = 1;
                func_80040C00(0x35);
                D_800BF870.pad1[0x1CC] |= 1 << a[3];
                func_8006E1C0(8, &D_800BF870);
                sp[1] = *(s16 *)(a + 0x2E);
                sp[3] = *(s16 *)(a + 0x32) - *(s16 *)(a + 0x84) / 2;
                sp[5] = *(s16 *)(a + 0x36);
                func_8006CBA8(sp);
                func_8003116C(0x37, sp, -0x20);
                func_80027144(*(s32 *)(*(u8 **)(a + 0xC0) + 0x40), sp, 0x700, 8);
                func_80074590(0xC, 0, 0);
                func_80027144(*(s32 *)(*(u8 **)(a + 0xC0) + 0x40), a + 0x2C, 0x700, 8);
                func_80074590(0xC, 0, 0);
            }
            break;
        case 1:
            if (D_800BF809 == 0) {
                a[4] = 3;
                func_8006E1E4();
            }
            break;
        }
        break;
    case 3:
        func_8007A624(a);
        break;
    }
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8011D724);

extern s8 D_800BF818;
s32 func_8011D9A0(void) {
    D_800BF818 = 7;
    return 1;
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8011D9B4);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8011DC14);

extern void *D_80133610[];
void func_8011DCEC(u8 *a)
{
    if (a[0x71] == 0xFF) {
        func_80040D68(a, D_80133610[a[0x5E]]);
        a[5] = 2;
        a[0x70] = 1;
    }
}

void func_8011DD48(u8 *a)
{
    if (a[0x71] == 0xFF) {
        switch (a[0x5E]) {
        case 0:
        case 3:
            a[0x5E]++;
            break;
        case 2:
            func_8004D4F4(*(s16 *)(a + 0x60), 1);
            a[0x5E] = 1;
            break;
        }
        a[5] = 0;
    }
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8011DDD0);

extern u8 D_800BF913;
s32 func_8011DEB8(u8 *a)
{
    u8 *g;
    if (D_800BF913 == 0xFF) {
        return 0;
    }
    g = D_800BF808;
    *(s16 *)(a + 0x60) = g[3];
    switch (g[3]) {
    case 0x67:
        a[0x5E] = 3;
        break;
    case 0x59 ... 0x5C:
    case 0x66:
    case 0x68:
        a[0x5E] = 2;
        break;
    default:
        *(s16 *)(a + 0x60) = -1;
        return 0;
    }
    return 1;
}

s32 func_8011DF48(u8 *a)
{
    switch (a[0x78]) {
    default:
        return 0;
    case 0:
        *(s16 *)(a + 0x40) = 0x3C;
        *(s16 *)(a + 0x42) = 6;
        a[0x78]++;
        break;
    case 1:
        if (--*(s16 *)(a + 0x42) <= 0) {
            *(s16 *)(a + 0x42) = 6;
            func_80074590(8, 6, -0x1E);
        }
        if (--*(s16 *)(a + 0x40) <= 0) {
            return 1;
        }
        break;
    }
    return 0;
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8011DFF8);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8011E13C);

extern u8 D_800ECF58[];
extern u8 D_80131960[];
extern u8 D_800A3CD0[];
void func_8011E248(u8 *p)
{
    u8 *s = D_800ECF58;

    *(s32 *)(p + 0x3C) = *(s32 *)(s + 0x38);
    if (func_800519E0(p, 0xF, *(s32 *)(s + 0x6C), D_80131960) == 0) {
        func_80040CDC(p, D_8014005C_9175, D_800A3CD0);
        func_80041718(p, 9, 0);
        p[0x5E] = D_800BFA2D;
        *(s16 *)(p + 0x80) = 0x78;
        p[0xB] = 0x40;
        *(s16 *)(p + 0x84) = 0x78;
        p[0] = 9;
        *(s16 *)(p + 0x82) = 0xF0;
        *(s16 *)(p + 0x54) = 0;
        *(s16 *)(p + 0x56) = 0;
        *(s16 *)(p + 0x58) = 0;
        *(s16 *)(p + 0x86) = 0xD2;
        p[0x2B] = 0;
        p[0x29] = 0;
        p[4]++;
    }
}

extern void *D_801337B0[];
void func_8011E310(u8 *p)
{
    if (p[0x71] == 0xFF) {
        func_80040D68(p, D_801337B0[p[0x5E]]);
        p[0x70] = 1;
        p[5] = 2;
    }
}

void func_8011E36C(u8 *p)
{
    if (p[0x71] == 0xFF) {
        switch (p[0x5E]) {
        case 0:
            p[0x5E]++;
            D_800BFA2D = 1;
            break;
        case 2:
            p[4] = 3;
            return;
        }
        p[5] = 0;
        p[6] = 0;
        *(s16 *)(p + 0x40) = 0x1E;
    }
}

extern u8 D_800BFB05;
s32 func_8011E3D4(u8 *a)
{
    if (D_800BFB05 != 0) {
        a[0x5E] = 2;
        return 3;
    }
    return 2;
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8011E3FC);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8011E554);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8011E688);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8011E900);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8011EB04);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8011EDB8);

s32 func_8011EE70(u8 *p)
{
    u8 *e = D_800E7E80;

    switch (p[0x78]) {
    case 0:
        p[0x78] = 1;
        D_800BF80E = 0;
        e[5] = 0x29;
        e[6] = 0;
        goto end;
    case 1:
        if (D_800BF80E) {
            return 1;
        }
    end:
    default:
        return 0;
    }
}

s32 func_8011EED4(void *arg0) {
    func_801173A8(arg0);
    func_8004D604(0x36, 1);
    D_800BF870.pad1[0x1C6] += 1;
    return 1;
}

s32 func_8011EF18(void *arg0) {
    M2C_FIELD(arg0, s8 *, 0xBF) = 1;
    return 1;
}

s32 func_8011EF28(void *arg0) {
    return M2C_FIELD(arg0, u8 *, 0xBF) == 0;
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8011EF34);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8011EFF8);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8011F190);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8011F6A4);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8011F7F4);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8011FA0C);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8011FC50);

void func_80120004(u8 *a)
{
    s32 k = 0x80;
    s32 t = D_800ECF90;

    *(s16 *)(a + 0x58) = 0;
    *(s16 *)(a + 0x54) = 0;
    a[0xB] = k;
    a[0] = 9;
    *(s32 *)(a + 0x3C) = t;
    if (!(D_800BFE56 & k)) {
        *(s16 *)(a + 0x80) = 0xC0;
        *(s16 *)(a + 0x82) = 0x180;
        *(s16 *)(a + 0x84) = 0xE0;
        *(s16 *)(a + 0x86) = 0x16C;
    } else {
        *(s16 *)(a + 0x82) = 0x100;
        *(s16 *)(a + 0x84) = 0xA0;
        *(s16 *)(a + 0x80) = k;
        *(s16 *)(a + 0x86) = 0x145;
        if (a[3] & 0x40) {
            *(s16 *)(a + 0x86) = 0x140;
        }
    }
    a[0x2B] = 0;
    a[0x29] = 0;
    a[0x5E] = 0;
}

void func_8012009C(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 0x5E);
    switch (temp_v1) {                              /* irregular */
    case 0:
        if ((M2C_FIELD(arg0, u8 *, 1) != 0) && (func_8011EF34(arg0) != 0)) {
            M2C_FIELD(arg0, u8 *, 0x5E) = 1U;
            return;
        }
        return;
    case 1:
        if (M2C_FIELD(arg0, u8 *, 1) == 0) {
            func_8007ADDC(arg0);
            M2C_FIELD(arg0, u8 *, 0x5E) = 0U;
        }
        break;
    }
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80120120);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80120344);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_801207AC);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80120A00);

s32 func_80120C30(u8 *p)
{
    switch (p[0x78]) {
    case 0:
        p[0x47] = p[0x72];
        p[0x78]++;
        break;
    case 1:
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80120C7C);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80120D64);

extern M2C_UNK D_80133EF8;
extern M2C_UNK D_80133FB8;
void func_80120EC8(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x2B) == 3) {
        if (f_CompleteUseTheSeesawEventIfResolved() == 0) {
            func_80040D68(arg0, &D_80133FB8);
            M2C_FIELD(arg0, s8 *, 0x70) = 1;
            return;
        }
        func_80040D68(arg0, &D_80133EF8);
        M2C_FIELD(arg0, s8 *, 0x70) = 1;
        M2C_FIELD(arg0, s8 *, 5) = 1;
    }
}

void func_80120F38(u8 *p)
{
    if (p[0x71] == 0xFF) {
        if (p[0x5E] == 0) {
            func_80040D68(p, D_80133F20);
        } else {
            func_80040D68(p, D_80133F90);
        }
        p[0x70] = 1;
        p[5] = 2;
    }
}

void func_80120FA4(void *arg0) {
    u8 temp_v0;

    if (M2C_FIELD(arg0, u8 *, 0x71) == 0xFF) {
        temp_v0 = M2C_FIELD(arg0, u8 *, 0x5E);
        if (temp_v0 == 0) {
            M2C_FIELD(arg0, u8 *, 0x5E) = (u8) (temp_v0 + 1);
        }
        M2C_FIELD(arg0, s8 *, 5) = 0;
    }
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80120FD4);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_801211B0);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_801214AC);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8012168C);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_801218B0);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80121AB4);

extern u8 D_800BF81E;
extern s32 D_1F80023C;
s32 func_80121C64(u8 *a)
{
    u8 *t = D_800E7E80;

    switch (a[0x78]) {
    case 0:
        if (*(u16 *)(t + 0x17E) & 0x180) {
            return 1;
        }
        D_800BF81E = 0;
        t[4] = 4;
        t[5] = 0x21;
        t[6] = 0;
        t[7] = 0;
        D_1F80023C = *(s32 *)(t + 4);
        if (t[0x6F] == 0) {
            func_8004ED0C(0x10, 0);
        } else {
            func_8004EDDC(t[0x6F], 0x10);
        }
        t[0x6F] = 0x10;
        t[5] = 0x3A;
        t[6] = 0;
        a[0x78]++;
        break;
    case 1:
        if (t[5] == 0x21) {
            return 1;
        }
        break;
    }
    return 0;
}

s32 func_80121D58(u8 *a)
{
    HV v;
    u8 *g = D_1F800214_120a;

    switch (a[0x78]) {
    default:
        return 0;
    case 0:
        v.x = 0x2288;
        v.y = -0xB22;
        v.z = 0x39BC;
        func_80070F00(g, 1, &v);
        func_800708B4(3);
        a[0x78]++;
        break;
    case 1:
        if (g[3] == 0) {
            func_800708B4(1);
            *(s16 *)(a + 0x4A) = 0;
            return 1;
        }
        return 0;
    }
    return 0;
}

s32 func_80121E04(void *arg0) {
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x14), s8 *, 4) = 3;
    return 1;
}

s32 func_80121E18(void) {
    func_8004D650(0x32, 1);
    return 1;
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80121E3C);

extern M2C_UNK D_800A3D18;
extern M2C_UNK D_8014005C;
void func_80121FF8(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 4);
    switch (temp_v1) {                              /* irregular */
    case 0:
        func_80040CDC(arg0, &D_8014005C, &D_800A3D18);
        M2C_FIELD(arg0, s8 *, 0x7B) = 0x17;
        func_80041718(arg0, 0x17, 0);
        M2C_FIELD(arg0, s16 *, 0x56) = 0xC00;
        M2C_FIELD(arg0, s16 *, 0x58) = 0;
        M2C_FIELD(arg0, s16 *, 0x54) = 0;
        if (D_800BFE56 & 0x80) {
            M2C_FIELD(arg0, s16 *, 0x32) = -0xAA0;
        }
        M2C_FIELD(arg0, u8 *, 4) = (u8) (M2C_FIELD(arg0, u8 *, 4) + 1);
        return;
    case 1:
        func_80121E3C(arg0);
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

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_801220F8);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_801222A4);

extern M2C_UNK D_8013439C;
extern M2C_UNK D_80134664;
void func_801224E8(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x2B) == 3) {
        if (f_CompleteUseTheSeesawEventIfResolved() == 0) {
            func_80040D68(arg0, &D_80134664);
            M2C_FIELD(arg0, s8 *, 0x70) = 1;
            return;
        }
        func_80040D68(arg0, &D_8013439C);
        M2C_FIELD(arg0, s8 *, 0x70) = 1;
        M2C_FIELD(arg0, s8 *, 5) = 1;
    }
}

extern void *D_801346CC[];
void func_80122558(u8 *a)
{
    if (a[0x71] == 0xFF) {
        func_80040D68(a, D_801346CC[a[0x5E]]);
        a[0x70] = 1;
        a[5] = 2;
    }
}

extern u8 D_800BFB48;
s32 func_801225B4(void)
{
    if (D_800BFB48 != 0) {
        return 2;
    }
    return 3;
}

s32 func_801225D4(void *arg0) {
    M2C_FIELD(arg0, u8 *, 6) = (u8) (M2C_FIELD(arg0, u8 *, 6) + 1);
    return 1;
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_801225EC);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80122874);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80122ABC);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80122D04);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80122E90);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80122F88);

extern M2C_UNK D_800A3D18;
extern u16 D_800BFE56;
extern M2C_UNK D_8014005C;
void func_80123294(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 4);
    switch (temp_v1) {                              /* irregular */
    case 0:
        func_80040CDC(arg0, &D_8014005C, &D_800A3D18);
        if (!(D_800BFE56 & 0x80)) {
            M2C_FIELD(arg0, u8 *, 0x7B) = 0x17U;
        } else {
            M2C_FIELD(arg0, u8 *, 0x7B) = 1U;
            M2C_FIELD(arg0, u16 *, 0x32) = (u16) (M2C_FIELD(arg0, u16 *, 0x32) - 0x20);
        }
        func_80041718(arg0, M2C_FIELD(arg0, u8 *, 0x7B), 0);
        M2C_FIELD(arg0, s16 *, 0x58) = 0;
        M2C_FIELD(arg0, s16 *, 0x54) = 0;
        M2C_FIELD(arg0, s16 *, 0x56) = 0x578;
        M2C_FIELD(arg0, u8 *, 4) = (u8) (M2C_FIELD(arg0, u8 *, 4) + 1);
        return;
    case 1:
        func_80122F88(arg0);
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

INCLUDE_ASM("asm/a07/nonmatchings/a07", f_UpdateCircusCharlesHintDialogue);

extern M2C_UNK D_800A3D18;
extern M2C_UNK D_8014005C;
void func_80123698(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 4);
    switch (temp_v1) {                              /* irregular */
    case 0:
        func_80040CDC(arg0, &D_8014005C, &D_800A3D18);
        M2C_FIELD(arg0, s8 *, 0x7B) = 0x17;
        func_80041718(arg0, 0x17, 0);
        M2C_FIELD(arg0, s16 *, 0x58) = 0;
        M2C_FIELD(arg0, s16 *, 0x54) = 0;
        M2C_FIELD(arg0, s16 *, 0x56) = 0;
        M2C_FIELD(arg0, u8 *, 4) = (u8) (M2C_FIELD(arg0, u8 *, 4) + 1);
        return;
    case 1:
        f_UpdateCircusCharlesHintDialogue(arg0);
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

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80123774);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8012397C);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80124F44);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80125184);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80125400);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80125604);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_801258E4);

s32 func_80125AE0(u8 *p)
{
    func_80041718(p, 0x28, 8);
    *(s32 *)(p + 0x14) = func_8012C770(p, 1);
    return 1;
}

s32 func_80125B20(u8 *a)
{
    switch (a[0x78]) {
    case 0:
        (*(u8 **)(a + 0x14))[5] = 1;
        func_80041718(a, 0x19, 4);
        a[0x78]++;
        break;
    case 1:
        if ((*(u8 **)(a + 0x14))[0x5E] == 0) {
            return 1;
        }
        break;
    }
    return 0;
}

s32 func_80125BAC(u8 *a)
{
    u8 *t = D_800E7E80;

    switch (a[0x78]) {
    case 0:
        if (*(u16 *)(t + 0x17E) & 0x180) {
            return 1;
        }
        D_800BF81E = 0;
        t[4] = 4;
        t[5] = 0x21;
        t[6] = 0;
        t[7] = 0;
        D_1F80023C = *(s32 *)(t + 4);
        if (t[0x6F] == 0) {
            func_8004ED0C(0x10, 0);
        } else {
            func_8004EDDC(t[0x6F], 0x10);
        }
        t[0x6F] = 0x10;
        t[5] = 0x3A;
        t[6] = 0;
        a[0x78]++;
        break;
    case 1:
        if (t[5] == 0x21) {
            return 1;
        }
        break;
    }
    return 0;
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80125CA0);

s32 func_80125D68(void)
{
    u8 *t = D_800E7E80;
    s16 d, e;

    if (t[5] != 2) {
        return 0;
    }
    d = *(u16 *)(t + 0x2E) - 0x231C;
    if ((u16)(*(u16 *)(t + 0x80) + d) > *(s16 *)(t + 0x82) + 0x708) {
        return 0;
    }
    e = *(u16 *)(t + 0x36) - 0x22FB;
    return *(s16 *)(t + 0x82) + 0xD48 >= (u16)(*(u16 *)(t + 0x80) + e);
}

void func_80125DD8(u8 *p, s32 a1)
{
    SV v;

    if ((u16)(*(u16 *)(p + 0x36) - 0x2560) < 0x87F) {
        if (a1) {
            v.a = *(s16 *)(p + 0x2E);
        } else {
            v.a = 0x25B2;
        }
        v.b = -0xA00;
        v.c = *(s16 *)(p + 0x36);
        func_8002AE0C(&v, 0x60, 1);
    }
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80125E40);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80125F40);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80126188);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80126270);

INCLUDE_ASM("asm/a07/nonmatchings/a07", f_UpdateCircusPaonAtWellActor);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80126BD8);

void func_80126D6C(void *arg0) {
    if (M2C_FIELD(M2C_FIELD(arg0, void **, 0x38), u16 *, 2) == 0) {
        func_80074590(0x82, 0, 0);
        func_800521F4(0, 0, 0xF1, 2);
        M2C_FIELD(arg0, s16 *, 0x68) = 0x80;
    }
}

s32 func_80126DCC(void) {
    return (u32) ((*(u16 *)0x1F800162 + 0xCA8) & 0xFFFF) >= 0x439U;
}

s32 func_80126DEC(u8 *a)
{
    s32 z = (-func_80083E80(*(s16 *)(a + 0x56)) * *(s16 *)(a + 0x80)) >> 12;
    s32 x = func_80083F50(*(s16 *)(a + 0x56)) * *(s16 *)(a + 0x80);
    AreaSVec *v = &D_1F8000C0_f4ad;
    D_1F8000C0_f4ad.x = x >> 12;
    v->y = *(s16 *)(a + 0x86) - *(s16 *)(a + 0x84);
    v->z = z;
    return func_8012EE08(a + 0x2C, v, 0) != 0;
}

extern s16 D_800E7FFE_1cd3;
extern s16 D_1F800160;
extern s16 D_1F800162;
extern s16 D_1F800164;
s32 func_80126E80(u8 *a)
{
    if (!(D_800E7FFE_1cd3 & 0x8200)) {
        if (D_1F800162 >= -0xABD) {
            s16 dx = D_1F800160 - *(s16 *)(a + 0x2E);
            s16 dz = D_1F800164 - *(s16 *)(a + 0x36);
            if (func_80084080(dx * dx + dz * dz) < 0x384) {
                return 1;
            }
        }
    }
    return 0;
}

s32 func_80126F1C(u8 *p)
{
    switch (p[0x78]) {
    case 0:
        D_800BF860_c64f = p;
        D_800BFA2C = 0xF;
        p[0x78]++;
        goto end;
    case 1:
        if (D_800BFA2C == 0x11) {
            return 1;
        }
    end:
    default:
        return 0;
    }
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80126F84);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_801271BC);

void func_80126F84();
s32 func_80127358(u8 *a, s32 b)
{
    u8 *p = func_80072DDC(a, 0, 2, 0x56);

    if (p != NULL) {
        *(void **)(p + 0x1C) = func_80126F84;
        p[0x28] |= 0x80;
        *(s16 *)(p + 0x2E) = *(s16 *)(*(u8 **)(a + 0xD0) + 0x2C);
        *(s16 *)(p + 0x32) = *(s16 *)(*(u8 **)(a + 0xD0) + 0x30);
        *(s16 *)(p + 0x36) = *(s16 *)(*(u8 **)(a + 0xD0) + 0x34);
        p[3] = b;
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_801273F8);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_801274C8);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80127690);

extern u8 D_800BFA45;
s32 func_801278F8(void)
{
    if (D_800BFA45 & 2) {
        return 3;
    }
    return 2;
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8012791C);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80127B20);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80127CC0);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80127EB8);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_801281C4);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_801283C0);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80128594);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80128798);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80128980);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80128BAC);

s32 func_80128DA0(u8 *p)
{
    if (*(s16 *)(p + 0x72) & 0x8000) {
        *(s32 *)(p + 0x3C) = D_800ECF68;
        *(void **)(p + 0x7C) = D_80017FE8;
    } else {
        *(s32 *)(p + 0x3C) = D_800ECF90;
        *(void **)(p + 0x7C) = D_8014005C_9175;
    }
    func_80041718(p, *(u16 *)(p + 0x72) & 0x7FFF, 0);
    return 1;
}

void func_80128E04(void) {
    s32 sp10;

    func_80036560(5, &sp10);
    func_80078894(sp10);
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80128E34);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80129170);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80129360);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_801294A4);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_801296AC);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80129900);

extern s8 D_1F800214[];
s32 func_80129B38(void) {
    func_8004BEC4();
    func_801178E4(*((s32 *)D_1F800214));
    return 1;
}

s32 func_80129B68(u8 *a) {
    switch (a[0x78]) {
    case 0:
        func_80041718(a, 0x2E, 4);
        M2C_FIELD(a, u8 **, 0x14)[5] = 1;
        a[0x78]++;
        break;
    case 1:
        if (M2C_FIELD(a, u8 **, 0x14)[5] == 2) {
            return 1;
        }
        break;
    }
    return 0;
}

extern void *D_800BF860;
s32 func_80129BF4(void *arg0) {
    M2C_FIELD(arg0, s16 *, 0x40) = 1;
    D_800BF860 = arg0;
    return 1;
}

s32 func_80129C0C(void *arg0) {
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x14), s8 *, 4) = 3;
    return 1;
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80129C20);

s32 func_80129E88(s32 arg0) {
    s32 var_s0;

    var_s0 = 0;
    do {
        func_8004190C(arg0);
        var_s0 += 1;
    } while (var_s0 < 4);
    func_800518FC(arg0);
    return 1;
}

s32 func_80129ED8(void *arg0) {
    M2C_FIELD(arg0, s8 *, 0x5E) = 1;
    return 1;
}

s32 func_80129EE8(void)
{
    u8 *a = D_800BF844;
    u8 *b = *(u8 **)(a + 0xC0);

    a[0xD] |= 4;
    b[0x3F] = 0xED;
    *(s16 *)(a + 0x62) = 0x10;
    return 1;
}

s32 func_80129F1C(void *arg0) {
    M2C_FIELD(arg0, u8 *, 6) = (u8) (M2C_FIELD(arg0, u8 *, 6) + 1);
    return 1;
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80129F34);

INCLUDE_ASM("asm/a07/nonmatchings/a07", f_UpdateCircusIceCandyAndTinyPigActor);

INCLUDE_ASM("asm/a07/nonmatchings/a07", f_UpdatePigBallItemInteraction);

INCLUDE_ASM("asm/a07/nonmatchings/a07", f_UpdateIceCandyAndTinyPigRewardSequence);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8012A7A4);

extern void *D_80136154[];
void func_8012A894(u8 *a)
{
    if (a[0x71] == 0xFF) {
        func_80040D68(a, D_80136154[a[0x5E]]);
        a[0x70] = 1;
        a[5] = 2;
    }
}

void func_8012A8F0(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x71) == 0xFF) {
        M2C_FIELD(arg0, s8 *, 5) = 0;
    }
}

s32 func_8012A90C(void *arg0) {
    if (M2C_FIELD(arg0, s16 *, 0x62) != 0) {
        M2C_FIELD(arg0, s16 *, 0x62) = 0;
        return 3;
    }
    return 2;
}

s32 func_8012A930(u8 *p)
{
    u8 *g = (u8 *)&D_800BF870;

    if (g[0x2BA] != 0) {
        g[0xC5] |= 2;
        p[0x5E] = 3;
        return 3;
    }
    return 2;
}

s32 func_8012A96C(u8 *a)
{
    u8 *g = (u8 *)&D_800BF870;

    g[0x1BA] += 1 + g[0x2BA];
    func_8004D650(0x76, g[0x2BA]);
    if (g[0x1BA] >= 0x1E) {
        a[0x5E] = 4;
        return 3;
    }
    return 2;
}

extern u8 D_800BFB2A;
s32 func_8012A9DC(void)
{
    if (D_800BFB2A < 10) {
        return 3;
    }
    func_8004D650(0x76, 10);
    func_8004ED94(0x5D, 0x41);
    return 2;
}

s32 func_8012AA28(u8 *p)
{
    u8 *g = (u8 *)&D_800BF870;

    if (++g[0x1BF] == 5) {
        p[0] = 2;
        p[0x5F] = 0;
        p[0x5E] = 9;
        p[6] = 0;
        return 3;
    }
    return 2;
}

void func_8012C60C();
s32 func_8012AA74(u8 *p)
{
    u8 *s = D_800BF808;
    s32 v = s[3];

    if (v < 0x45) {
        if (v >= 0x40) {
            *(s16 *)(p + 0x60) = s[3];
            if (f_CompleteUseTheSeesawEventIfResolved()) {
                p[0x5E] = 8;
            }
            return 1;
        }
    }
    *(s16 *)(p + 0x60) = -1;
    return 0;
}

s32 func_8012AAE4(void *arg0) {
    s16 temp_a0;
    s32 var_v0;

    temp_a0 = M2C_FIELD(arg0, s16 *, 0x60);
    var_v0 = 2;
    if (temp_a0 != -1) {
        func_8004D4F4(temp_a0, 1);
        M2C_FIELD(arg0, s16 *, 0x60) = -1;
        var_v0 = 3;
    }
    return var_v0;
}

s32 func_8012AB2C(void *arg0) {
    M2C_FIELD(arg0, u8 *, 6) = (u8) (M2C_FIELD(arg0, u8 *, 6) + 1);
    return 1;
}

s32 func_8012AB44(void *arg0) {
    return M2C_FIELD(arg0, u8 *, 0xBF) == M2C_FIELD(arg0, s16 *, 0x72);
}

s32 func_8012AB5C(void)
{
    u8 *g = (u8 *)&D_800BF870;

    if (g[0x1BF] == 5) {
        g[0x1BF]++;
        return 3;
    }
    return 2;
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8012AB88);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8012ACC0);

INCLUDE_ASM("asm/a07/nonmatchings/a07", f_UpdateTriangleGearRewardPresentation);

INCLUDE_ASM("asm/a07/nonmatchings/a07", f_UpdateEarthPigBagRewardPresentation);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8012B1B4);

void func_8012B1B4();
u8 *func_8012B3FC(void *a0)
{
    u8 *r = func_80072DDC(a0, 0, 5, 3);

    if (r == 0) {
        return 0;
    }
    r[3] = 0;
    *(void **)(r + 0x1C) = func_8012B1B4;
    *(void **)(r + 0x10) = a0;
    return r;
}

u8 *func_8012B44C(void)
{
    u8 *r = func_80072DDC(0, 1, 5, 3);

    if (r == 0) {
        return 0;
    }
    r[3] = 1;
    *(void **)(r + 0x1C) = func_8012B1B4;
    *(void **)(r + 0x10) = 0;
    return r;
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", f_UpdateCircusThrownQuestObject);

INCLUDE_ASM("asm/a07/nonmatchings/a07", f_UpdateCircusClosetKeyActor);

u8 *func_8012C104(void *a0, u8 a1)
{
    u8 *r = func_80072DDC(a0, 1, 5, 5);

    if (r == 0) {
        return 0;
    }
    r[3] = a1;
    *(void **)(r + 0x1C) = f_UpdateCircusClosetKeyActor;
    *(void **)(r + 0x10) = a0;
    r[0x28] |= 0x80;
    return r;
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8012C16C);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8012C340);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8012C60C);

u8 *func_8012C770(void *a0, u8 a1)
{
    u8 *r = func_80072DDC(a0, 1, 5, 5);

    if (r == 0) {
        return 0;
    }
    r[3] = 1;
    r[0x5E] = a1;
    *(void **)(r + 0x1C) = func_8012C60C;
    *(void **)(r + 0x10) = a0;
    r[0x28] |= 0x80;
    return r;
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8012C7E0);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8012CAA8);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8012CDF4);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8012D2B4);

typedef struct {
    s16 x, y, w, h;
} RECT16;
void func_8012D880(RECT16 *a) {
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

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8012DA14);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8012DBB4);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8012DE60);

extern s16 *D_1F80028C;
void func_8012E1A0(u32 *a0, void *a1)
{
    u32 *s1;
    s32 s0;
    u32 w;
    s16 *o;

    s1 = a0;
    a0 += 4;

    if (D_800BF873) {
        o = (s16 *)D_1F80028C;
        { s32 x = o[0x17]; s32 y = o[0x19]; s32 z = o[0x1B]; s0 = func_80078240(x - D_1F800160, y - D_1F800162, z - D_1F800164) << 1; }
        gte_ldfcdir(0, 0, 0);
        w = *s1;
        func_8012D2B4(func_8012CDF4(a0, a1, w & 0xFFFF, s0), a1, w >> 16, s0);
    } else {
        w = *s1;
        f_UpdateCircusLockerNpcActor(func_801311D0(a0, a1, w & 0xFFFF), a1, w >> 16);
    }
}

typedef struct {
    u8 x[8];
} S8;
extern S8 D_80136248[];
void func_8012E2A0(void)
{
    u32 i;

    if (D_800BF873) {
        for (i = 0; i < 5; i++) {
            func_8012D880(&D_80136248[i]);
        }
    }
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8012E2F4);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8012E610);

extern u16 *D_800ECF78;
void func_8012EB50(u8 *a)
{
    u16 *p = D_800ECF78;
    u16 t;

    *(u16 **)(a + 0xC) = p;
    *(u16 *)(a + 8) = p[0];
    t = p[1];
    a[7] = 0;
    *(u16 *)(a + 0xA) = t;
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8012EB7C);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8012EE08);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8012F1BC);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8012F480);

extern u8 *D_800ECF84;
extern s16 D_1F8000F0;
extern s16 D_1F8000F2_a096;
void func_8012F6EC(u8 *a)
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
        { s32 k = D_1F8000F2_a096; u16 w = *(u16 *)(a + 0x2C); x = ((w + 0x140) >> 1) - ((k * w) >> 12); }
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

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8012F938);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8012FC50);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_8012FFD4);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80130374);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80130730);

extern u8 D_800E8008[];
extern u8 D_1F8000DC[];
s32 func_801309E0(u8 *a)
{
    u8 *g = D_800E8008;
    u8 s = a[0x78];
    s32 pad[4];

    switch (s) {
    case 0:
        if (!(*(u16 *)(a + 0x72) & 1)) {
            func_8006E1C0(7);
        } else {
            g[0x64] = 7;
        }
        if (*(s16 *)(a + 0x66) == 0) {
            func_8006CBD0(g, *(s32 *)(a + 0x74));
            if (*(s16 *)(a + 0x64) != 0) {
                *(s16 *)(a + 0x4E) = *(s16 *)(g + 0x3A);
                *(s16 *)(a + 0x50) = *(s16 *)(g + 0x3E);
                *(s16 *)(a + 0x52) = *(s16 *)(g + 0x42);
            }
            return 1;
        }
        func_8006CBA8(D_1F8000DC);
        func_8006CC1C(g, *(s32 *)(a + 0x74), *(s16 *)(a + 0x66));
        if (*(s16 *)(a + 0x64) != 0) {
            *(s16 *)(a + 0x4E) = *(s16 *)(g + 0x3A);
            *(s16 *)(a + 0x50) = *(s16 *)(g + 0x3E);
            *(s16 *)(a + 0x52) = *(s16 *)(g + 0x42);
        }
        if (*(s16 *)(a + 0x68) != 0) {
            return 1;
        }
        a[0x78]++;
        break;
    case 1:
        if (*(s16 *)(a + 0x64) != 0) {
            *(s16 *)(g + 0x3A) = *(s16 *)(a + 0x4E);
            *(s16 *)(g + 0x3E) = *(s16 *)(a + 0x50);
            *(s16 *)(g + 0x42) = *(s16 *)(a + 0x52);
        }
        {
            s32 r = func_8006CDCC(g);
            if (*(s16 *)(a + 0x64) != 0) {
                *(s16 *)(a + 0x4E) = *(s16 *)(g + 0x3A);
                *(s16 *)(a + 0x50) = *(s16 *)(g + 0x3E);
                *(s16 *)(a + 0x52) = *(s16 *)(g + 0x42);
            }
            if (r == s) {
                return 1;
            }
        }
        break;
    
    }
    return 0;
}

s32 func_80130BA4(u8 *a) {
    s16 y = M2C_FIELD(a, s16 *, 0x32);
    s32 i;

    a[0x29] = 0;
    M2C_FIELD(a, s16 *, 0x32) = y - 0x80;
    for (i = 0; i < 200; i++) {
        if (f_TestCircusActorGroundContact(a) != 0) {
            a[0x29] = 0;
            return 1;
        }
        M2C_FIELD(a, s16 *, 0x32) += 0x20;
    }
    M2C_FIELD(a, s16 *, 0x32) = y;
    return 0;
}

extern s16 D_1F8001C6;
s32 func_80130C20(u8 *a) {
    u16 f;
    s16 g;

    switch (a[0x78]) {
    case 0:
        D_800BF818_7697 = a[0x74];
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

s32 func_80130CB0(void *a0)
{
    if (func_8007778C(a0) == 0) {
        return 0;
    }
    func_8004190C(a0);
    return D_1F800137 == 0;
}

s32 f_CompleteUseTheSeesawEventIfResolved(void)
{
    s32 a = D_800E7FFE & 0x180;
    s32 b = D_800BFE56 & 0x80;

    if (a | b) {
        func_80040C00(0x23);
        return 1;
    }
    return 0;
}

s32 func_80130D44(void)
{
    if (D_800E7FFE & 0x180) {
        func_80040C00(0x23);
        return 1;
    }
    return 0;
}

void func_80130D80(u8 a0)
{
    s32 a = D_800E7FFE & 0x180;
    s32 b = D_800BFE56 & 0x80;

    if (a | b) {
        func_80042354(1, a0);
    } else {
        func_80042354(1, 2);
    }
}

void func_80130DD8(u8 a0)
{
    if (D_800E7FFE & 0x180) {
        func_80042354(1, a0);
    } else {
        func_80042354(1, 2);
    }
}

s32 func_80130E20(u8 *a, s32 b) {
    s32 s = (func_80083F50(M2C_FIELD(a, s16 *, 0x56)) * M2C_FIELD(a, s16 *, 0x44)) >> 4;
    s32 c = func_80083E80(M2C_FIELD(a, s16 *, 0x56)) * M2C_FIELD(a, s16 *, 0x44);

    M2C_FIELD(a, s32 *, 0x2C) += s;
    M2C_FIELD(a, s32 *, 0x34) -= c >> 4;
    if (b != 0) {
        return f_TestCircusActorForwardCollision(a);
    }
    return 0;
}

s32 f_TestCircusActorForwardCollision(u8 *a)
{
    s32 z = (-func_80083E80(*(s16 *)(a + 0x56)) * *(s16 *)(a + 0x80)) >> 12;
    s32 x = func_80083F50(*(s16 *)(a + 0x56)) * *(s16 *)(a + 0x80);
    AreaSVec *v = &D_1F8000C0_f4ad;
    D_1F8000C0_f4ad.x = x >> 12;
    v->y = *(s16 *)(a + 0x86) - *(s16 *)(a + 0x84);
    v->z = z;
    return func_8012EE08(a + 0x2C, v, 1) != 0;
}

extern s16 D_1F8000C0[];
s32 f_TestCircusActorGroundContact(u8 *p)
{
    if (p[0x29] == 0) {
        D_1F8000C0[0] = 0;
        D_1F8000C0[1] = *(u16 *)(p + 0x86) - *(u16 *)(p + 0x84);
        D_1F8000C0[2] = 0;
        if (func_8012F1BC(p + 0x2C, D_1F8000C0, 0) > 0) {
            p[0x29] = 1;
        }
    }
    return p[0x29];
}

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_80130FB8);

INCLUDE_ASM("asm/a07/nonmatchings/a07", func_801311D0);

INCLUDE_ASM("asm/a07/nonmatchings/a07", f_UpdateCircusLockerNpcActor);

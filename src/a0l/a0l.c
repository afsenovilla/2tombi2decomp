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

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_801092E8);

typedef struct {
    s16 pad;
    s16 x, y, z;
} PartPos;
extern u8 D_800BFA58_9b2e;
extern PartPos D_801178E0[];
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

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_8010983C);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", f_UpdateEndingArea2CameraSequence);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", f_UpdateEndingArea4CameraSequence);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", f_UpdateEndingArea5MysteryCameraSequence);

extern u8 D_800BF871;
extern u8 D_800BF84C;
extern u8 D_800BFA55;
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

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_8010AA4C);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_8010AD40);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_8010B0B8);

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

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", f_UpdateEndingScriptController);

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

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_8010D590);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_8010D8F0);

s32 func_8010DB44(void *arg0) {
    void *temp_v1;

    temp_v1 = M2C_FIELD(arg0, s16 *, 0x72) + arg0;
    M2C_FIELD(temp_v1, u8 *, 4) = (u8) (M2C_FIELD(temp_v1, u8 *, 4) + 1);
    return 1;
}

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_8010DB68);

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

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_8010DFEC);

extern u8 D_8011AF2C[];
extern s32 D_800ECFD8;
extern u8 D_8011A738[];
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

typedef struct {
    s16 vx, vy, vz, pad;
} SVec;
typedef struct {
    s32 vx, vy, vz, pad;
} LVec;
extern SVec D_1F8000C0;
extern LVec D_1F8000A0;
extern u8 *D_1F800248;
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

extern s16 D_1F800160;
extern s16 D_1F800164;
extern u8 *D_1F80024C;
void func_80111744();
void func_8010E5F0(u8 *a)
{
    a[0xB] = (a[0xB] & 0xC0) | 0x80;
    func_80041718(a, 3, 0);
    *(s16 *)(a + 0x56) = func_800782B0(a + 0x2C, D_1F800160, D_1F800164);
    D_1F80024C = a;
}

extern u8 D_800BFA56;
extern u8 D_800BFA57;
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

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", f_UpdateEndingCompletionBranchScript);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_8010E8B8);

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

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_8010F34C);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_8010F56C);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_8010FA48);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_8010FC58);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_8010FDB4);

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

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_80110548);

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

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_80111744);

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

extern void *D_800ECF80;
extern u8 D_8011A6D4[];
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

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_80111FA4);

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

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", f_AdvanceEndingScriptedPresentation);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_801122B4);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_80112660);

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
extern DecEnv D_1F800000;
extern u8 D_1F800135;
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
typedef struct {
    u32 unk0;
    u8 *buf;
    u32 unk8;
} MovieDef;
extern MovieDef D_8011A6AC[];
extern u8 *D_1F800138;
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

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", func_80112DEC);

INCLUDE_ASM("asm/a0l/nonmatchings/a0l", f_DispatchEndingAreaCameraSequence);

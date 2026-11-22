#include "common.h"
#include "game.h"
#include "m2c.h"

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80109314);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_8010944C);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80109688);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_801097FC);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80109AE0);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80109C00);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80109F08);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_8010A0C8);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_8010A234);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_8010A3D8);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_8010A554);

void func_8010A788(void *a, u8 *b)
{
    if (b[0x47] == 2) {
        func_801097FC(a, b, *(void **)(b + 0xC0));
    } else {
        func_8001F650(a, b, *(void **)(b + 0xC0));
    }
}

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_8010A7D0);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_8010A824);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_8010A8A0);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_8010A988);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_8010AA94);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_8010AC84);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_8010B0FC);

extern s8 D_1F80027E[];
extern u8 D_800BFA1A;

void func_8010B338(void *arg0) {
    *((s8 *)D_1F80027E) = 1;
    func_8006F0E4();
    M2C_FIELD(arg0, s8 *, 1) = 1;
    func_80055D5C(arg0);
    M2C_FIELD(arg0, s16 *, 0x142) = 0;
    M2C_FIELD(arg0, s16 *, 0x58) = 0;
    func_80054198(arg0);
    func_80055284(arg0);
    func_80054D14(arg0, 2, 0);
    func_8003315C(arg0);
    if (!(D_800BFA1A & 1)) {
        func_80042354(1, 5);
        func_8001CF2C();
        M2C_FIELD(arg0, s8 *, 4) = 4;
    }
}


s32 func_8010B3DC(s32 arg0, s32 arg1) {
    s32 var_a3;
    void *temp_a1;

    temp_a1 = M2C_FIELD(arg0, void **, 0x158);
    var_a3 = 0;
    if ((M2C_FIELD(temp_a1, u8 *, 0xC) == 4) && (M2C_FIELD(temp_a1, u8 *, 2) == 0x17)) {
        var_a3 = func_8010AC84(arg0, (s32) temp_a1, arg1);
    }
    return var_a3;
}

s32 func_8010B42C(u8 *a)
{
    u8 *b = *(u8 **)(a + 0x158);

    if (b[0xC] != 4) {
        return 0;
    }
    if (b[2] != 0x16) {
        return 0;
    }
    return func_8010B0FC(a, b);
}

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_8010B474);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_8010B698);


void func_8010B824(void) {
}


void func_8010B82C(void) {
}

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
extern Spawn *D_80118EB8[];
extern Pos D_800BF808;

void func_8010B834(Owner *a, s32 sel)
{
    Spawn *e;
    u8 *p;
    a->count = 0;
    e = D_80118EB8[sel];
    while (e->kind != 0xFF) {
        if (sel == 0 || a->count < 15) {
            switch (e->mode) {
            case 0:
                break;
            case 1:
                D_800BF808.x = e->x;
                D_800BF808.y = e->y;
                D_800BF808.z = e->z;
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

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_8010B9AC);


void func_8010BAD4(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 4);
    switch (temp_v1) {                              /* irregular */
    case 0:
        M2C_FIELD(arg0, u8 *, 4) = 1U;
        func_8010B834(arg0, 0U);
        func_8010B9AC(0);
        func_80113708();
        func_800752B4(0);
        func_80075D24(0x1FFF);
        return;
    case 1:
        if (func_80026AD0(arg0) != 0) {
            func_8010B834(arg0, M2C_FIELD(arg0, u8 *, 3));
        }
        func_80026A68(arg0);
        func_80113724();
        func_8010B9AC(1);
        return;
    case 3:
        func_8007ADD0(arg0);
        /* fallthrough */
    case 2:
        return;
    }
}

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_8010BBB4);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_8010BDD8);

extern u8 D_800E7E80[];
#define H(p, o) (*(s16 *)((u8 *)(p) + (o)))

s32 func_8010BFA8(u8 *a)
{
    u8 *p = D_800E7E80;
    s16 dx, dz;
    if (p[0x144] == 1) {
        dx = H(p, 0x2E) - H(a, 0x2E);
        dz = H(p, 0x36) - H(a, 0x36);
        if ((u16)func_80084080(dx * dx + dz * dz) <= H(p, 0x80) + H(a, 0x80) + 0x122) {
            return (u16)(H(p, 0x32) - H(a, 0x32) + 0x258 + (H(p, 0x84) + H(a, 0x84))) <= H(p, 0x86) + H(a, 0x84) + 0x258;
        }
    }
    return 0;
}

extern u8 *D_8011BC80[][2];

void f_SelectNextEvilPigAttack(u8 *a)
{
    s32 low;
    s16 v;
    u16 c;
    u8 *t;
    u8 **tt;
    s32 r;
    if (D_800BF870.unk0 == 0xF) {
        low = *(s16 *)(a + 0x6E) < 3;
    } else {
        low = *(s16 *)(a + 0x6E) < 2;
    }
    t = D_8011BC80[D_800BF870.unk0 - 10][low];
    c = *(u16 *)(a + 0x66);
    v = t[c & 0xF];
    *(u16 *)(a + 0x66) = c + 1;
    a[6] = 0;
    switch (v) {
    case 0:
        *(u16 *)(a + 0x64) = 1;
        a[5] = 1;
        break;
    case 1:
        *(u16 *)(a + 0x64) = 2;
        a[5] = 1;
        break;
    case 2:
        *(u16 *)(a + 0x64) = 3;
        a[5] = 2;
        break;
    case 3:
        *(u16 *)(a + 0x64) = 4;
        a[5] = 2;
        break;
    case 4:
    default:
        *(u16 *)(a + 0x64) = 5;
        if (func_8009A450() & 0x40) {
            a[5] = 3;
        } else {
            a[5] = 1;
        }
        break;
    }
}

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", f_SelectEvilPigArenaTarget);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", f_UpdateEvilPigRelocationAttack);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", f_UpdateEvilPigRushAttack);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_8010D748);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", f_UpdateEvilPigHitAndCaptureState);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_8010E590);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_8010E7A4);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", f_UpdateEvilPigCenterEffectAttack);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_8010ECF0);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", f_UpdateEvilPigBattleActor);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", f_UpdateEvilPigBattleIntroduction);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_8010F97C);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_8010FD74);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_8011024C);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_801103F4);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80110698);

void func_801109CC(u32 *p, void *b)
{
    u32 lo = *p;
    u32 packed;

    packed = lo;
    lo = packed & 0xFFFF;
    p += 4;
    func_80110698(func_801103F4(p, b, lo), b, packed >> 16);
}

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80110A14);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80110CF8);

extern u16 *D_800ECF78;

void func_80111238(u8 *a)
{
    u16 *p = D_800ECF78;
    u16 t;

    *(u16 **)(a + 0xC) = p;
    *(u16 *)(a + 8) = p[0];
    t = p[1];
    a[7] = 0;
    *(u16 *)(a + 0xA) = t;
}

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80111264);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_801113A0);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80111564);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80111670);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_801117C8);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80111980);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80111B68);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80111D3C);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_8011212C);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80112244);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80112384);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_8011253C);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80112764);

#define gte_ldfcdir(r0, r1, r2) __asm__ volatile("ctc2	%0, $21;" "ctc2	%1, $22;" "ctc2	%2, $23" : : "r"(r0), "r"(r1), "r"(r2))
#define gte_ldv0m(p) __asm__ volatile("lwc2	$0, %0;" "lwc2	$1, %1" : : "m"(((s32 *)(p))[0]), "m"(((s32 *)(p))[1]))
extern s32 D_1F800084[];
extern s32 D_1F800088;
extern s32 D_1F800090[];
extern u8 D_8011E9FC[];
extern u8 D_8011E9B4[];
extern u8 D_8011EB2C[];

void func_80112990(u8 *a)
{
    s32 s;
    u8 *b = a;
    s32 *p = D_1F800084;
    s32 *d = D_1F800090;
    gte_ldfcdir(0, 0, 0);
    *d = 0;
    func_800329E0(6);
    gte_ldv0m(b + 0x2C);
    if (func_800317CC(*(s16 *)(a + 0x32)) == 0) {
        s = func_80083E80(*(s16 *)(a + 0x48)) >> 3;
        s += func_80083E80(*(s16 *)(a + 0x4E)) >> 8;
        if (s < 0x10) {
            s = 0x10;
        }
        D_1F800088 = *p = (*p * s) >> 8;
        func_8002847C(D_8011E9FC, D_8011EB2C[b[5] >> 1], 0);
        func_8002847C(D_8011E9B4, D_8011EB2C[b[6] >> 1], 0);
    }
}

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80112AA4);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80112C50);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80112DF4);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80112F0C);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_801130A0);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_801131DC);


void func_801136F8(void) {
}


void func_80113700(void) {
}

extern M2C_UNK D_80127974;
void func_80113708(void) {
    M2C_FIELD(&D_80127974, s8 *, 0) = 0;
    M2C_FIELD(&D_80127974, s8 *, 1) = 0;
    M2C_FIELD(&D_80127974, s8 *, 2) = 0;
    M2C_FIELD(&D_80127974, s8 *, 3) = 0;
}

extern M2C_UNK D_80127974;
void func_80113724(void) {
    if (M2C_FIELD(&D_80127974, u8 *, 0) == 0) {
        M2C_FIELD(&D_80127974, s16 *, 4) = 0;
        func_800310F4(0xB00, 0);
        M2C_FIELD(&D_80127974, u8 *, 0) = 1U;
    }
}

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80113768);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_8011384C);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80113904);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80113A20);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80113AC0);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80113B78);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80113C70);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80113D4C);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80113DDC);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80113EA4);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80113F84);

void func_80114020(u8 *a)
{
    switch (a[4]) {
    case 0:
        a[4]++;
        a[7] = 0;
        *(s32 *)(a + 0x48) = func_8009A450();
        *(s32 *)(a + 0x4C) = func_8009A450();
    case 1:
        if (++a[7] >= 0x10) {
            a[4] = 2;
        } else {
            a[1] = 1;
        }
        break;
    case 2:
    case 3:
        func_8007A624(a);
        break;
    }
}

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_801140D0);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_801142EC);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80114630);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80114784);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_801149D8);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80114B38);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80114C6C);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80114D50);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80114DB0);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80114E64);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80115338);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80115418);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80115700);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80115958);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80115C24);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80115DF0);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80115FF4);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_801160C4);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80116194);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", f_CopyEvilPigCaptureDeformationVertices);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", f_UpdateEvilPigCaptureDeformation);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80116634);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80116874);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", f_UpdateEvilPigRobeRewardActor);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", f_MoveEvilPigCaptureActorTowardBoss);

extern s8 D_1F800160[];
extern s8 D_1F800164[];
extern s8 D_1F800246[];
extern s8 D_1F80024C[];

void func_80116E9C(void *arg0) {
    M2C_UNK var_a0;
    void *temp_s1;

    temp_s1 = *((void **)D_1F80024C);
    if (*((u8 *)D_1F800246) == 0) {
        M2C_FIELD(arg0, u8 *, 5) = 0U;
        M2C_FIELD(arg0, s8 *, 6) = 0;
        M2C_FIELD(arg0, s8 *, 7) = 2;
        M2C_FIELD(arg0, s16 *, 0x64) = 0;
        M2C_FIELD(arg0, u16 *, 0x56) = (u16) M2C_FIELD(arg0, u16 *, 0x62);
    } else {
        M2C_FIELD(arg0, u16 *, 0x56) = func_800776F8((s16) (func_800782B0(arg0 + 0x2C, *((s16 *)D_1F800160), *((s16 *)D_1F800164)) - 0x400), (s16) M2C_FIELD(arg0, u16 *, 0x56), 0x80);
        M2C_FIELD(M2C_FIELD(arg0, void **, 0xC0), s16 *, 8) = func_800776F8(0, M2C_FIELD(M2C_FIELD(arg0, void **, 0xC0), s16 *, 8), 0x80);
        f_UpdateEvilPigCaptureDeformation(arg0);
        if (M2C_FIELD(arg0, u8 *, 0x29) != 0) {
            var_a0 = 0x88;
            if (M2C_FIELD(temp_s1, s16 *, 0x6E) == 1) {
                var_a0 = 0x89;
            }
            func_80074590(var_a0, 0, 0);
            M2C_FIELD(arg0, s8 *, 6) = 0;
            M2C_FIELD(arg0, s16 *, 0x64) = 0;
            M2C_FIELD(arg0, s8 *, 7) = 3;
            M2C_FIELD(arg0, u8 *, 5) = (u8) (M2C_FIELD(arg0, u8 *, 5) + 1);
        }
    }
    M2C_FIELD(arg0, s16 *, 0x32) = (s16) (M2C_FIELD(arg0, u16 *, 0x7C) + (func_80083E80(M2C_FIELD(arg0, s16 *, 0x60)) >> 4));
    M2C_FIELD(arg0, s16 *, 0x60) = (s16) (((u16) M2C_FIELD(arg0, s16 *, 0x60) + 0x40) & 0xFFF);
}

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", f_UpdateEvilPigCaptureApproachSequence);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", f_UpdateEvilPigDefeatAndRewardSequence);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80117864);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_801179C0);

extern u8 D_800E806E;

s32 func_80117EC8(u8 *p)
{
    switch (p[0x78]) {
    case 0:
        p[0x78]++;
        func_8006E1C0(8);
        g_CameraState.focusX = *(u16 *)(p + 0x2E);
        g_CameraState.focusY = *(u16 *)(p + 0x32) + 0x4B0;
        g_CameraState.focusZ = *(u16 *)(p + 0x36);
        goto end;
    case 1:
        if (D_800E806E == 3) {
            return 1;
        }
    end:
    default:
        return 0;
    }
}

extern s16 D_80126FAC[];
extern s16 D_800E8046;

s32 func_80117F58(u8 *p)
{
    s16 y;

    switch (p[0x78]) {
    case 0:
        p[0x78]++;
        *(s32 *)(p + 0x38) = func_8003116C(D_80126FAC[D_800BF870.unk0 - 10], p + 0x2C, -0x32);
        goto end;
    case 1:
        y = *(u16 *)(p + 0x32) + 0x10;
        *(s16 *)(p + 0x32) = y;
        *(s16 *)(*(u8 **)(p + 0x38) + 0x2E) = y;
        if (*(s16 *)(p + 0x32) >= D_800E8046 - 0xF0) {
            return 1;
        }
    end:
    default:
        return 0;
    }
}


s32 func_80118004(void *arg0) {
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x38), s8 *, 4) = 2;
    func_80074590(0x37, 0x16, 0);
    return 1;
}

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80118038);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80118158);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_801185FC);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80118754);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_801187E8);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_801188C0);

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80118A5C);

void func_80118A5C();

u8 *func_80118C8C(s32 a)
{
    u8 *p = func_8007A980(0, 2, 0);
    if (p == 0) {
        return 0;
    }
    *(void **)(p + 0x1C) = func_80118A5C;
    p[2] = 0x4B;
    p[3] = a;
    return p;
}


void func_80118CE0(s32 arg0) {
    s32 temp_s0;

    temp_s0 = arg0 + 0x2C;
    func_8003116C(0xB05, temp_s0, -0x1E);
    func_8003116C(0xB05, temp_s0, -0x1E);
    func_8003116C(0xB09, temp_s0, -0x28);
    func_8003116C(0xB0B, temp_s0, 0);
}

INCLUDE_ASM("asm/a0a/nonmatchings/a0a", func_80118D40);

extern s16 D_800BED82;
extern M2C_UNK D_801271F4;
void f_UpdateEvilPigBagOfferingSequence(void) {
    func_80075448(0xA, &D_801271F4, 0x10, D_800BED82);
}

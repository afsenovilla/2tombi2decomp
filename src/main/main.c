#include "common.h"
#include "game.h"
#include "m2c.h"
#include "gte.h"

extern volatile u8 D_800BE0E4;
void f_CloseCooperativeWorkerThread(s32);
void f_SetCdAudioMixEnabled(s32);
s32 CdControlB(u8 com, u8 *param, u8 *result);

extern u8 D_800ED018_eeff[];
extern u8 *D_800F2738_2edb;

void func_8001CAC0(void)
{
    u8 *p = D_800ED018_eeff;

    switch (D_800BF870.unk0) {
    case 0:
        func_8011534C(p);
        break;
    case 4:
        func_8013EE84(p);
        break;
    case 5:
        func_80136CDC(p);
        break;
    case 6:
        func_8014189C(p);
        break;
    case 7:
        func_8012F6EC(p);
        break;
    case 10:
        func_801140D0(p);
        break;
    case 11:
        func_80113F94(p);
        break;
    case 13:
        func_80116980(p);
        break;
    case 15:
        func_80116560(p);
        break;
    case 21:
        func_8010B918(p);
        break;
    }
}

extern u8 D_1F8000F8[];
typedef struct Entry8w { u8 pad0[6]; u16 flags; } Entry8w;
extern Entry8w *D_800A54A8_6044[];
extern u8 D_800A55B0[];
extern u8 *D_800A2B84[];
#define gte_lddqa(r0) __asm__ volatile("ctc2 %0, $27" : : "r"(r0))
#define gte_lddqb0() __asm__ volatile("addiu $10, $0, 0; ctc2 $10, $28" : : : "$10")
void func_8001CBA8(u8 *a, u8 n)
{
    s32 i;

    if (n == 0xFF) {
        i = 0;
        n = 0;
    } else {
        i = 1;
    }
    for (; i < 2; i++, n++) {
        (a + n)[0x48] = 0;
        (a + n)[0x4A] = 0xFC;
        (a + n)[0x4C] = 0;
        (a + n)[0x4E] = 0xFF;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_8001CC00);

extern u16 D_1F8001A2;
extern s32 D_1F800080;
extern u8 D_8011600C[];
extern u8 D_801189C4[];
s32 func_8001CE04(u8 cmd, u8 *param, u8 *result)
{
    CdControlF(cmd, param);
    for (;;) {
        switch (CdSync(1, result)) {
        case 2:
            return 0;
        case 5:
            f_YieldCurrentCooperativeWorker(1);
            return 1;
        }
        f_YieldCurrentCooperativeWorker(1);
    }
}

void func_8001CE90(s32 arg0, u8 *param, u8 *result) {
    func_8001CE04(arg0 & 0xFF, param, result);
}

s32 func_8001CEB0(s32 arg0, s32 arg1) {
    s8 sp10;
    s32 var_v0;

    var_v0 = CdMode();
    if (var_v0 != arg0) {
        sp10 = (s8) arg0;
        func_8001CE04(0xE, (u8 *) &sp10, arg1);
        var_v0 = f_YieldCurrentCooperativeWorker(2);
    }
    return var_v0;
}

extern s32 D_800BE108;
extern u8 D_800BF808[];
extern u8 D_800A4F88[];
extern s8 D_1F800090[];
s32 f_SetActorModelResources(void *, s32, s32);
s32 func_8001DC40(void *, s32, s32, void *);
void SpuSetCommonAttr(void *);
void func_8002847C(void *, s32, s32);
typedef struct CdMixAttr {
    /* 0x00 */ u32 mask;
    /* 0x04 */ u8 pad4[0x14];
    /* 0x18 */ s32 mix;
    /* 0x1C */ u8 pad1C[0xC];
} CdMixAttr;
void f_SetCdAudioMixEnabled(s32 mix)
{
    CdMixAttr attr;

    attr.mask = 0x200;
    attr.mix = mix;
    SpuSetCommonAttr(&attr);
}

void f_StopVoicePlayback(void)
{
    u8 result[8];

    f_CloseCooperativeWorkerThread(2);
    D_800BE0E4 = 0;
    f_SetCdAudioMixEnabled(0);
    while (CdControlB(9, 0, 0) == 0)
        ;
}

extern volatile u8 D_800BE0E4;
void f_RequestStreamedAudioStop(void) {
    D_800BE0E4 |= 0x10;
}

s32 func_8001CF94(s32 arg0) {
    s32 var_v0;

    if ((arg0 & 0x11) || (var_v0 = arg0 & 2, (var_v0 == 0))) {
        var_v0 = f_YieldCurrentCooperativeWorker(2);
    }
    return var_v0;
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_8001CFC8);

INCLUDE_ASM("asm/main/nonmatchings/main", f_StartStreamedAudioRange);

INCLUDE_ASM("asm/main/nonmatchings/main", f_StartStreamedAudioTrack);

typedef struct { u8 unk0; u8 pad1[0x5DD]; u8 u5DE; } GsArea_D41C;
extern GsArea_D41C D_800BF870_d41c;
extern s32 D_1F80021C;
void func_8001D41C(s16 id, s16 x)
{
    if (id == -1) {
        f_StopVoicePlayback();
        return;
    }
    if (id == -2) {
        f_StartStreamedAudioRange(0, D_1F80021C, D_1F80021C + 1, 0);
        return;
    }
    if (D_800BF870_d41c.u5DE == 1) {
        D_800BE0E4 = 2;
        return;
    }
    switch (D_800BF870_d41c.unk0) {
    case 0:
        func_801464C0(id, x);
        break;
    case 1:
        func_801342C8(id, x);
        break;
    case 2:
        func_8012816C(id, x);
        break;
    case 4:
        func_8013E3D4(id, x);
        break;
    case 5:
        func_8013AA50(id, x);
        break;
    case 6:
        func_801404DC(id, x);
        break;
    case 7:
        func_80130FB8(id, x);
        break;
    case 8:
        func_8013D670(id, x);
        break;
    case 9:
        func_8010DF68(id, x);
        break;
    case 10:
        func_80118D40(id, x);
        break;
    case 11:
        func_801178A0(id, x);
        break;
    case 12:
        func_80117194(id, x);
        break;
    case 13:
        func_80116EE0(id, x);
        break;
    case 14:
        func_801173C4(id, x);
        break;
    case 15:
        func_8011A35C(id, x);
        break;
    case 16:
        func_8010D248(id, x);
        break;
    case 17:
        func_8010C528(id, x);
        break;
    case 18:
        func_8010C9AC(id, x);
        break;
    case 19:
        func_8010D154(id, x);
        break;
    case 20:
        func_801173D4(id, x);
        break;
    case 21:
        func_801106A8(id, x);
        break;
    }
}

extern u8 *D_800BF544_37fb;
extern u32 *D_800ED8C8;
typedef struct { u8 b[8]; } Bytes8_368;
extern Bytes8_368 D_80015368;
extern u8 D_800BF84B;
extern u8 D_1F800137_104c;
typedef struct { u8 ch; u8 mode; u16 start; u16 len; } VoiceLine_110;
extern VoiceLine_110 D_8009D110[];
extern u8 *D_1F800220;
extern u8 D_800FB162;
extern u8 D_800BE0E4_9d53;
extern u8 D_800ECF48_7ec2[];
extern u8 D_1F80019A;
extern u8 D_800FB167;
void f_PlayOrStopVoiceLine(s16 id)
{
    VoiceLine_110 *e;
    u8 *s;
    u8 *end;
    s32 ch;

    if (id < 0) {
        f_StopVoicePlayback();
        return;
    }
    e = &D_8009D110[id];
    s = D_1F800220 + e->start * 8;
    end = s + e->len * 8;
    ch = e->ch;
    if (e->mode == 0 && D_800FB162 == 1) {
        *(volatile u8 *)&D_800BE0E4_9d53 = 2;
        return;
    }
    f_StartStreamedAudioRange(ch, s, end, e->mode);
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_8001D7C4);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8001D940);

extern s8 D_1F800138[];
extern s8 D_1F80019B[];
void func_8001DB38(void) {
    func_8001D940(*((void **)D_1F800138));
    if (M2C_FIELD(*((void **)D_1F800138), u8 *, 0x6C) != 0) {
        *((s8 *)D_1F80019B) = 1;
    }
    f_TerminateCurrentCooperativeWorker();
}

extern u8 D_800FB160_9a03[];
extern s16 D_800BE220;
extern u8 D_800BED7C[];
extern u8 D_800A1EB8[];
extern u8 D_800A1EA0[];
extern u8 D_1F800236_18be;
void func_8001DB38();
s32 func_8001DB8C(void *dest, s32 sector, s32 bytes)
{
    WorkerState *w = WORKER_STATE;

    f_CloseCooperativeWorkerThread(1);
    g_DiscReadDest = dest;
    g_DiscReadSector = sector;
    *(volatile s32 *)&g_DiscReadWords = (bytes + 3) / 4;
    f_OpenCooperativeWorkerThread(1, func_8001DB38);
    while (w->busy != 0) {
        f_YieldCurrentCooperativeWorker(1);
    }
    return bytes;
}

extern s32 D_1F8001F8;
extern s32 D_1F8001F0;
extern volatile s32 D_1F8001F4;
s32 func_8001DC40(void *a, s32 b, s32 c, void *d)
{
    D_1F8001F8 = (s32)a;
    D_1F8001F0 = b;
    D_1F8001F4 = (c + 3) / 4;
    func_8001D940(*(void **)D_1F800138);
    return c;
}

INCLUDE_ASM("asm/main/nonmatchings/main", f_ApplyActiveColliderBlockingResponse);

INCLUDE_ASM("asm/main/nonmatchings/main", f_ApplyActiveColliderImpactResponse);

extern s32 D_1F80009C;
extern u8 D_800BF816;
extern s32 D_1F800098_bca3;
extern u8 D_1F800253;
s32 f_TestWrappedAngleSide(s32 a, s32 b, s32 flip);
static inline void Supported_EC3C(u8 *a, u8 *b, s32 y)
{
    s32 c;
    s32 d;
    u16 k;

    b[0x29] = 1;
    a[0x29] = 1;
    a[0x145] = 0;
    *(s16 *)(a + 0x4A) = 0;
    *(s16 *)(a + 0x50) = 0;
    a[0x148] = 0;
    *(s32 *)(a + 0x30) = y << 16;
    if (a[0x78] == 0 && D_800BF816 == 0) {
        if (*(s16 *)(a + 0x17E) >= 0) {
            if (*(s16 *)(a + 0x84) != 0x8C) {
                k = *(u16 *)(a + 0x84);
                d = *(u16 *)(a + 0x32) - 0x8C;
                *(u16 *)(a + 0x32) = k + d;
            }
        } else {
            if (*(s16 *)(a + 0x84) != 0x46) {
                k = *(u16 *)(a + 0x84);
                d = *(u16 *)(a + 0x32) - 0x46;
                *(u16 *)(a + 0x32) = k + d;
            }
        }
    }
}
s32 func_8001EC3C(a, b)
    u8 *a;
    u8 *b;
{
    s16 dx = *(u16 *)(a + 0x2E) - *(u16 *)(b + 0x2E);
    s16 dz = *(u16 *)(a + 0x36) - *(u16 *)(b + 0x36);
    s32 d = SquareRoot0(dx * dx + dz * dz);
    s16 dy;
    s16 h;
    s16 h2;
    s16 t;

    if ((u16)d > *(s16 *)(a + 0x80) + *(s16 *)(b + 0x80)) {
        return -1;
    }
    dy = *(u16 *)(a + 0x32) - *(u16 *)(b + 0x32);
    t = *(u16 *)(b + 0x84) + *(u16 *)(a + 0x84);
    if ((u16)(dy + t) > *(s16 *)(a + 0x86) + *(s16 *)(b + 0x86)) {
        return -1;
    }
    if (dy < 0) {
        dy = -dy;
        h = t;
        h2 = -t;
    } else {
        h = (*(u16 *)(b + 0x86) - *(u16 *)(b + 0x84)) + (*(u16 *)(a + 0x86) - *(u16 *)(a + 0x84));
        h2 = h;
    }
    D_1F80009C = ratan2(-dz, dx);
    if (h2 < 0 && h - dy < 0x1A) {
        if (a[0x145] & 1) {
            return -1;
        }
        Supported_EC3C(a, b, *(s16 *)(b + 0x32) + h2);
        return 2;
    }
    if (*(s16 *)(a + 0x80) + *(s16 *)(b + 0x80) - (s16)d < h - dy) {
        if (!(a[0] & 4)) {
            s32 c = (rcos(D_1F80009C) * (*(s16 *)(a + 0x80) + *(s16 *)(b + 0x80))) >> 12;
            s32 t = rsin(D_1F80009C) * (*(s16 *)(a + 0x80) + *(s16 *)(b + 0x80));
            *(u16 *)(a + 0x2E) = *(u16 *)(b + 0x2E) + c;
            *(u16 *)(a + 0x36) = *(u16 *)(b + 0x36) - (t >> 12);
        }
        if (h - dy >= 0x92) {
            a[0x60] = 1;
        }
        a[0x5F] = f_TestWrappedAngleSide(*(s16 *)&D_1F80009C, *(s16 *)(a + 0x140), 1) + 2;
        return 1;
    }
    if (h2 <= 0) {
        if (a[0x145] & 1) {
            return -1;
        }
        Supported_EC3C(a, b, *(s16 *)(b + 0x32) + h2);
        return 2;
    }
    if (D_1F800098_bca3 != 0) {
        return 3;
    }
    D_1F800253 = 4;
    *(s32 *)(a + 0x30) = (MEMBER_AT(s16, b, 0x32) + h2) << 16;
    if (a[0x145] == 1 && *(s16 *)(a + 0x4A) < 0) {
        *(s16 *)(a + 0x4A) = 0;
    }
    return 3;
}

s32 f_TestWrappedAngleSide(s32 a, s32 b, s32 flip);
static inline void Supported_F054(u8 *a, s32 y)
{
    s32 c;
    s32 d;
    u16 k;

    a[0x29] = 1;
    a[0x145] = 0;
    *(s16 *)(a + 0x4A) = 0;
    *(s16 *)(a + 0x50) = 0;
    a[0x148] = 0;
    *(s32 *)(a + 0x30) = y << 16;
    if (a[0x78] == 0 && D_800BF816 == 0) {
        if (*(s16 *)(a + 0x17E) >= 0) {
            if (*(s16 *)(a + 0x84) != 0x8C) {
                k = *(u16 *)(a + 0x84);
                d = *(u16 *)(a + 0x32) - 0x8C;
                *(u16 *)(a + 0x32) = k + d;
            }
        } else {
            if (*(s16 *)(a + 0x84) != 0x46) {
                k = *(u16 *)(a + 0x84);
                d = *(u16 *)(a + 0x32) - 0x46;
                *(u16 *)(a + 0x32) = k + d;
            }
        }
    }
}
s32 func_8001F054(u8 *a, u8 *b)
{
    s16 dx = *(u16 *)(a + 0x2E) - *(u16 *)(b + 0x2E);
    s16 dz = *(u16 *)(a + 0x36) - *(u16 *)(b + 0x36);
    s32 d = SquareRoot0(dx * dx + dz * dz);
    s16 dy;
    s16 h;
    s16 h2;
    s16 t;

    if ((u16)d > *(s16 *)(a + 0x80) + *(s16 *)(b + 0x80)) {
        return -1;
    }
    dy = *(u16 *)(a + 0x32) - *(u16 *)(b + 0x32);
    t = *(u16 *)(b + 0x84) + *(u16 *)(a + 0x84);
    if ((u16)(dy + t) > *(s16 *)(a + 0x86) + *(s16 *)(b + 0x86)) {
        return -1;
    }
    if (dy < 0) {
        dy = -dy;
        h = t;
        h2 = -t;
    } else {
        h = (*(u16 *)(b + 0x86) - *(u16 *)(b + 0x84)) + (*(u16 *)(a + 0x86) - *(u16 *)(a + 0x84));
        h2 = h;
    }
    D_1F80009C = ratan2(-dz, dx);
    if (h2 < 0 && h - dy < 0x1A) {
        if (a[0x145] & 1) {
            return -1;
        }
        Supported_F054(a, *(s16 *)(b + 0x32) + h2);
        return 2;
    }
    if (*(s16 *)(a + 0x80) + *(s16 *)(b + 0x80) - (s16)d < h - dy) {
        if (!(a[0] & 4)) {
            s32 c = (rcos(D_1F80009C) * (*(s16 *)(a + 0x80) + *(s16 *)(b + 0x80))) >> 12;
            s32 t = rsin(D_1F80009C) * (*(s16 *)(a + 0x80) + *(s16 *)(b + 0x80));
            *(u16 *)(a + 0x2E) = *(u16 *)(b + 0x2E) + c;
            *(u16 *)(a + 0x36) = *(u16 *)(b + 0x36) - (t >> 12);
        }
        if (h - dy >= 0x92) {
            a[0x60] = 1;
        }
        a[0x5F] = f_TestWrappedAngleSide(*(s16 *)&D_1F80009C, *(s16 *)(a + 0x140), 1) + 2;
        return 1;
    }
    if (a[0x145] & 1) {
        return -1;
    }
    Supported_F054(a, *(s16 *)(b + 0x32) + h2);
    return 2;
}

s32 f_ClassifyTombaActorCylinderContact(u8 *a, u8 *b, s32 mode)
{
    s16 dx = *(u16 *)(a + 0x2E) - *(u16 *)(b + 0x2E);
    s16 dz = *(u16 *)(a + 0x36) - *(u16 *)(b + 0x36);
    s32 d = SquareRoot0(dx * dx + dz * dz);
    s16 dy;
    s16 h;
    s16 e;
    s16 k;
    s16 y0;
    s16 t;

    if ((u16)d > *(s16 *)(a + 0x80) + *(s16 *)(b + 0x80)) {
        return -1;
    }
    dy = *(u16 *)(a + 0x32) - *(u16 *)(b + 0x32);
    h = *(u16 *)(b + 0x84) + *(u16 *)(a + 0x84);
    if ((u16)(dy + h) > *(s16 *)(a + 0x86) + *(s16 *)(b + 0x86)) {
        return -1;
    }
    D_1F80009C = ratan2(-dz, dx);
    y0 = dy;
    e = MEMBER_AT(u16, a, 0x80) + MEMBER_AT(u16, b, 0x80) - d;
    if (dy < 0) {
        dy = -dy;
    } else {
        h = (*(u16 *)(b + 0x86) - *(u16 *)(b + 0x84)) + (*(u16 *)(a + 0x86) - *(u16 *)(a + 0x84));
    }
    t = h - dy;
    if (y0 < -((k = *(u16 *)(a + 0x84)) / 2)) {
        return e >= t;
    }
    if (e < t) {
        return 2;
    }
    if (*(u16 *)(a + 0x17E) & 0x200) {
        return 3;
    }
    if (D_1F800098_bca3 != 0) {
        return 3;
    }
    if (mode != 0) {
        return 3;
    }
    D_1F800253 = 4;
    *(u16 *)(a + 0x32) = *(u16 *)(b + 0x32) + (MEMBER_AT(u16, b, 0x86) - MEMBER_AT(u16, b, 0x84)) + (*(u16 *)(a + 0x86) - k);
    if (a[0x145] == 1 && *(s16 *)(a + 0x4A) < 0) {
        *(s16 *)(a + 0x4A) = 0;
    }
    return 3;
}

extern s8 D_1F800182[];
/* f_TestActorAgainstPartCylinderBounds, inlined */
static inline s32 TestPartCyl_2AC8(u8 *a, u8 *b, u8 *p)
{
    s16 dx = *(u16 *)(a + 0x2E) - *(u16 *)(p + 0x2C);
    s16 dz = *(u16 *)(a + 0x36) - *(u16 *)(p + 0x34);
    s32 d = SquareRoot0(dx * dx + dz * dz);

    if ((u16)d > *(s16 *)(a + 0x80) + *(s16 *)(b + 0x80) || (u16)((*(u16 *)(a + 0x32) - *(u16 *)(p + 0x30)) + (*(u16 *)(a + 0x84) + *(u16 *)(b + 0x84))) > *(s16 *)(a + 0x86) + *(s16 *)(b + 0x86)) {
        return 0;
    }
    D_1F80009C = ratan2(-dz, dx);
    return 1;
}
s32 f_ResolveActorAgainstPartCylinderContact(u8 *a, u8 *b, u8 *p)
{
    s32 c;
    s32 t;
    s32 side;

    if (!TestPartCyl_2AC8(a, b, p)) {
        return 0;
    }
    if (!(a[0] & 4)) {
        c = (rcos(D_1F80009C) * (*(s16 *)(a + 0x80) + *(s16 *)(b + 0x80))) >> 12;
        t = rsin(D_1F80009C) * (*(s16 *)(a + 0x80) + *(s16 *)(b + 0x80));
        *(u16 *)(a + 0x2E) = *(u16 *)(p + 0x2C) + c;
        *(u16 *)(a + 0x36) = *(u16 *)(p + 0x34) - (t >> 12);
    }
    a[0x60] = 1;
    side = f_TestWrappedAngleSide(*(s16 *)&D_1F80009C, *(s16 *)(a + 0x140), 1) + 2;
    a[0x5F] = side;
    if (a[0x164] != 0) {
        return 2;
    }
    if (!(a[0x149] & 4) && a[0x147] == (side & 1)) {
        *(s16 *)(a + 0x44) = 0;
    }
    return 1;
}

extern s32 D_1F80008C_f832;
/* f_TestActorCylinderOverlap, inlined */
static inline s32 TestCyl_0B08(u8 *a, u8 *b)
{
    s16 dx = *(u16 *)(a + 0x2E) - *(u16 *)(b + 0x2E);
    s16 dz = *(u16 *)(a + 0x36) - *(u16 *)(b + 0x36);
    s32 d = SquareRoot0(dx * dx + dz * dz);

    if ((u16)d > *(s16 *)(a + 0x80) + *(s16 *)(b + 0x80)) {
        return 0;
    }
    if ((u16)((*(u16 *)(a + 0x32) - *(u16 *)(b + 0x32)) + (*(u16 *)(a + 0x84) + *(u16 *)(b + 0x84))) > *(s16 *)(a + 0x86) + *(s16 *)(b + 0x86)) {
        return 0;
    }
    D_1F80008C_f832 = (s16)d;
    D_1F80009C = ratan2(-dz, dx, d);
    return 1;
}
s32 f_ResolveTombaRadialContactAndSide(u8 *a, u8 *b)
{
    s32 c;
    s32 t;

    if (!TestCyl_0B08(a, b)) {
        return 0;
    }
    if (!(a[0] & 4)) {
        c = (rcos(D_1F80009C) * (*(s16 *)(a + 0x80) + *(s16 *)(b + 0x80))) >> 12;
        t = rsin(D_1F80009C) * (*(s16 *)(a + 0x80) + *(s16 *)(b + 0x80));
        *(u16 *)(a + 0x2E) = *(u16 *)(b + 0x2E) + c;
        *(u16 *)(a + 0x36) = *(u16 *)(b + 0x36) - (t >> 12);
    }
    a[0x5F] = f_TestWrappedAngleSide(*(s16 *)&D_1F80009C, *(s16 *)(a + 0x140), 1) + 2;
    return 1;
}

s32 f_TestActorOffsetCylinderOverlap(u8 *a, u8 *b)
{
    s16 dx = *(u16 *)(a + 0x2E) - (*(u16 *)(b + 0x2E) + *(u16 *)(b + 0x60));
    s16 dz = *(u16 *)(a + 0x36) - (*(u16 *)(b + 0x36) + *(u16 *)(b + 0x64));
    s32 d = SquareRoot0(dx * dx + dz * dz);

    if ((u16)d > *(s16 *)(a + 0x80) + *(s16 *)(b + 0x80)) {
        return 0;
    }
    if ((u16)((*(u16 *)(a + 0x32) - (*(u16 *)(b + 0x32) + *(u16 *)(b + 0x62))) + (*(u16 *)(a + 0x84) + *(u16 *)(b + 0x84))) > *(s16 *)(a + 0x86) + *(s16 *)(b + 0x86)) {
        return 0;
    }
    D_1F80009C = ratan2(-dz, dx);
    return 1;
}

extern u16 D_1F80018C_c065;
extern u16 D_1F80018E;
extern u8 D_800BF840;
void f_ResolveTombaPlaneTransitionActorContact(u8 *a, u8 *b)
{
    s16 dx;
    s16 dz;
    s32 d;
    s32 ang;

    if (a[0x145] != 0) {
        return;
    }
    dx = *(u16 *)(b + 0x2E) - *(u16 *)(a + 0x2E);
    dz = *(u16 *)(b + 0x36) - *(u16 *)(a + 0x36);
    d = SquareRoot0(dx * dx + dz * dz);
    if ((u16)d > *(s16 *)(b + 0x80) + *(s16 *)(a + 0x80)) {
        return;
    }
    if ((u16)((*(u16 *)(a + 0x32) - *(u16 *)(b + 0x32)) + (*(u16 *)(a + 0x84) + *(u16 *)(b + 0x84))) > *(s16 *)(a + 0x86) + *(s16 *)(b + 0x86)) {
        return;
    }
    ang = ratan2(-dz, dx);
    if ((u32)((ang - *(u16 *)(a + 0x140) + 0x580) & 0xFFF) >= 0x301) {
        return;
    }
    if (D_1F800137_104c != 0) {
        return;
    }
    D_1F80018C_c065 = ang & 0xFFF;
    b[0x2B] = 1;
    if (b[2] == 0xE || b[2] == 0x39) {
        D_1F80018E = 0x4400;
    } else {
        D_1F80018E = 0x4800;
    }
    if (a[0x61] != 0x80) {
        D_800BF840 = 0x44;
    }
}

void func_8001FC50(u8 *a, u8 *b)
{
    s16 dx;
    s16 dz;
    s32 d;
    s32 ang;

    if (*(s16 *)(a + 0x17E) & 0x8200) {
        return;
    }
    if (a[0x145] != 0) {
        return;
    }
    dx = *(u16 *)(b + 0x2E) - *(u16 *)(a + 0x2E);
    dz = *(u16 *)(b + 0x36) - *(u16 *)(a + 0x36);
    d = SquareRoot0(dx * dx + dz * dz);
    if ((u16)d > *(s16 *)(b + 0x80) + *(s16 *)(a + 0x80)) {
        return;
    }
    if ((u16)((*(u16 *)(a + 0x32) - *(u16 *)(b + 0x32)) + (*(u16 *)(a + 0x84) + *(u16 *)(b + 0x84))) > *(s16 *)(a + 0x86) + *(s16 *)(b + 0x86)) {
        return;
    }
    ang = ratan2(-dz, dx);
    if ((u32)((ang - *(u16 *)(a + 0x140) + 0x580) & 0xFFF) >= 0x301) {
        return;
    }
    if (D_1F800137_104c != 0) {
        return;
    }
    D_1F80018C_c065 = ang & 0xFFF;
    b[0x2B] = 1;
    D_1F80018E = 0x4840;
    if (a[0x61] != 0x80) {
        D_800BF840 = 0x45;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/main", f_StartActorImpactOrTombaRebound);

INCLUDE_ASM("asm/main/nonmatchings/main", f_ResolveTombaActorImpactResponse);

INCLUDE_ASM("asm/main/nonmatchings/main", f_ResolveTombaConfiguredActorContact);

s32 f_TestWrappedAngleSide(s32 a, s32 b, s32 flip);
/* f_ApplyTombaSupportedContactState, inlined */
static inline void Supported_05B4(u8 *a)
{
    s32 c;
    s32 d;
    u16 k;

    a[0x29] = 1;
    a[0x145] = 0;
    *(s16 *)(a + 0x4A) = 0;
    *(s16 *)(a + 0x50) = 0;
    a[0x148] = 0;
    if (a[0x78] == 0 && D_800BF816 == 0) {
        if (*(s16 *)(a + 0x17E) >= 0) {
            c = 0x8C;
            k = *(u16 *)(a + 0x84);
            if (*(s16 *)(a + 0x84) == c) {
                return;
            }
            d = *(u16 *)(a + 0x32) - 0x8C;
        } else {
            c = 0x46;
            k = *(u16 *)(a + 0x84);
            if (*(s16 *)(a + 0x84) == c) {
                return;
            }
            d = *(u16 *)(a + 0x32) - 0x46;
        }
        *(u16 *)(a + 0x32) = k + d;
    }
}
void f_ResolveTombaType8ActorContact(u8 *a, u8 *b)
{
    s32 c;
    s32 x;
    s32 t;

    if (b[0] == 5) {
        if (!(*(u16 *)(a + 0x17E) & 0x200) && a[0x78] == 0) {
            f_ResolveTombaRadialContactAndSide(a, b);
        }
        return;
    }
    if (*(s16 *)(a + 0x17E) & 0x8000) {
        func_8001EC3C(a, b);
        return;
    }
    c = f_ClassifyTombaActorCylinderContact(a, b, 0);
    if (c < 0) {
        return;
    }
    if (b[0] == 1) {
        if (a[0x144] == 1 && c < 2) {
            f_StartActorImpactOrTombaRebound(b, -0x7FFE, 3, 0x1E);
            return;
        }
        if (*(u16 *)(a + 0x17E) & 0x200) {
            return;
        }
        if (!(c & 1)) {
            if (!(a[0] & 4)) {
                x = (rcos(D_1F80009C) * (*(s16 *)(a + 0x80) + *(s16 *)(b + 0x80))) >> 12;
                t = rsin(D_1F80009C) * (*(s16 *)(a + 0x80) + *(s16 *)(b + 0x80));
                *(u16 *)(a + 0x2E) = *(u16 *)(b + 0x2E) + x;
                *(u16 *)(a + 0x36) = *(u16 *)(b + 0x36) - (t >> 12);
            }
            a[0x60] = 1;
            a[0x5F] = f_TestWrappedAngleSide(*(s16 *)&D_1F80009C, *(s16 *)(a + 0x140), 1) + 2;
            return;
        }
        if (c != 1) {
            return;
        }
        if (a[0x145] & 1) {
            return;
        }
        *(u16 *)(a + 0x32) = *(u16 *)(b + 0x32) - (*(u16 *)(a + 0x84) + *(u16 *)(b + 0x84));
        Supported_05B4(a);
        return;
    }
    if (*(u16 *)(a + 0x17E) & 0x200) {
        return;
    }
    if (a[0x145] & 1) {
        return;
    }
    b[0x29] = 1;
}

extern u8 D_1F800230_d8aa;
extern u8 D_800BF81F;
extern int rcos(int a);
extern int rsin(int a);
void f_ArmTombaFacingInteraction44(u8 *a, u8 *b)
{
    s16 ang;
    s32 x;
    s32 t;
    s32 w;
    s32 h;
    u8 *b_p = b;

    b_p[0x29] = 0;
    if ((D_800BF808[0xE] == 0 || D_800BF808[0xF] == b_p[3]) && a[0x2A] == b_p[0x2A] && f_TestActorOffsetCylinderOverlap(a, b_p) != 0) {
        if (b_p[0x5F] == 0) {
            ang = *(u16 *)(a + 0x140);
        } else {
            ang = *(u16 *)(a + 0x140) + 0x800;
        }
        x = (rcos(ang) * (*(s16 *)(a + 0x80) + *(s16 *)(b_p + 0x80))) >> 12;
        t = (rsin(ang) * (*(s16 *)(a + 0x80) + *(s16 *)(b_p + 0x80))) >> 12;
        w = *(s16 *)&D_1F80009C;
        *(u16 *)(a + 0x2E) = x + (*(u16 *)(b_p + 0x2E) + *(u16 *)(b_p + 0x60));
        MEMBER_AT(u16, a, 0x36) = (*(u16 *)(b_p + 0x36) + *(u16 *)(b_p + 0x64)) - t;
        h = *(s16 *)(a + 0x140);
        a[0x5F] = f_TestWrappedAngleSide(w, h, 1) + 2;
        if (b_p[0x5F] != a[0x147] && D_1F800230_d8aa == 0 && D_800BF808[7] == 0) {
            if (D_800BF870.pad1[2] != 0) {
                switch (D_800BF870.unk0) {
                case 1:
                    if (a[0x2A] == 0x49 || a[0x2A] == 0x19 || a[0x2A] == 0x1A || a[0x2A] == 0x27) {
                        goto set;
                    }
                    if (a[0x2A] != 0x2B) {
                        break;
                    }
                    goto set;
                case 5:
                    if (a[0x2A] == 8 && *(s16 *)(a + 0x36) >= 0x2969) {
                            b_p[0x29] = 1;
                            D_800BF81F = (1 - b_p[0x5F]) * 16;
                            break;
                    }
                    break;
                case 6:
                    if (a[0x2A] == 7 && *(s16 *)(a + 0x2E) < 0x1CE8) {
                            b_p[0x29] = 1;
                            D_800BF81F = (1 - b_p[0x5F]) * 16;
                            break;
                    }
                    break;
                case 8:
                    if (a[0x2A] != 0x1F) {
                        break;
                    }
                case 9:
                set:
                    b_p[0x29] = 1;
                    D_800BF81F = (1 - b_p[0x5F]) * 16;
                    break;
                }
            } else {
                b_p[0x29] = 1;
                D_800BF808[0x17] = (1 - b_p[0x5F]) * 16;
            }
        }
    }
}

s32 func_80020B08(u8 *a, u8 *b)
{
    if (b[0] & 2) {
        return 0;
    }
    if (TestCyl_0B08(a, b)) {
        b[0x29] = 1;
        return 1;
    }
    return 0;
}

s32 f_ClassifyActorCylinderContact(u8 *a, u8 *b)
{
    s16 dx = *(u16 *)(a + 0x2E) - *(u16 *)(b + 0x2E);
    s16 dz = *(u16 *)(a + 0x36) - *(u16 *)(b + 0x36);
    s32 d = SquareRoot0(dx * dx + dz * dz);
    s16 dy;
    s16 h;
    s16 y0;

    if ((u16)d > *(s16 *)(a + 0x80) + *(s16 *)(b + 0x80)) {
        return -1;
    }
    dy = *(u16 *)(a + 0x32) - *(u16 *)(b + 0x32);
    h = *(u16 *)(a + 0x84) + *(u16 *)(b + 0x84);
    if ((u16)(dy + h) > *(s16 *)(a + 0x86) + *(s16 *)(b + 0x86)) {
        return -1;
    }
    y0 = dy;
    if (dy < 0) {
        dy = -dy;
    } else {
        h = (*(u16 *)(b + 0x86) - *(u16 *)(b + 0x84)) + (*(u16 *)(a + 0x86) - *(u16 *)(a + 0x84));
    }
    if (*(s16 *)(a + 0x80) + *(s16 *)(b + 0x80) - (s16)d < h - dy) {
        D_1F80009C = ratan2(-dz, dx);
        return 1;
    }
    if (y0 <= 0) {
        return 2;
    }
    return 3;
}

INCLUDE_ASM("asm/main/nonmatchings/main", f_ClassifyActiveColliderPartCylinderContact);

s32 f_ResolveActiveColliderPartContact(u8 *a, u8 *b, u8 *p, s32 k)
{
    u8 *m = a + 0x60;
    s32 c;
    s32 t;
    s32 r;

    if (!TestPartCyl_2AC8(a, b, p)) {
        return 0;
    }
    if (a[0x5F] == 0x10) {
        c = (rcos(*(s16 *)(m + 8) + 0x800) * (*(s16 *)(a + 0x80) + *(s16 *)(b + 0x80))) >> 12;
        t = rsin(*(s16 *)(m + 8) + 0x800) * (*(s16 *)(a + 0x80) + *(s16 *)(b + 0x80));
        *(u16 *)(a + 0x2E) = *(u16 *)(b + 0xAC) + c;
        *(u16 *)(a + 0x36) = *(u16 *)(b + 0xB4) - (t >> 12);
    }
    r = f_ApplyActiveColliderImpactResponse(a, b, p, k);
    b[0x2B] = 1;
    if (!(r & 0x80)) {
        *(u8 *)D_1F800182 = 0;
    }
    return 1;
}

s32 func_80021150(u8 *a, u8 *b, u8 *p, s32 k)
{
    u8 *m = a + 0x60;
    s32 c;
    s32 t;

    if (!TestPartCyl_2AC8(a, b, p)) {
        return 0;
    }
    if (a[0x5F] == 0x10) {
        switch (a[0x46] >> 1) {
        case 0:
        case 1:
            c = (rcos(*(s16 *)(m + 8) + 0x800) * (*(s16 *)(a + 0x80) + *(s16 *)(b + 0x80))) >> 12;
            t = rsin(*(s16 *)(m + 8) + 0x800) * (*(s16 *)(a + 0x80) + *(s16 *)(b + 0x80));
            *(u16 *)(a + 0x2E) = *(u16 *)(p + 0x2C) + c;
            *(u16 *)(a + 0x36) = *(u16 *)(p + 0x34) - (t >> 12);
            *(u16 *)(a + 0x32) = *(u16 *)(p + 0x30);
            break;
        case 2:
        case 3:
            *(u16 *)(a + 0x2E) = *(u16 *)(p + 0x2C);
            *(u16 *)(a + 0x36) = *(u16 *)(p + 0x34);
            *(u16 *)(a + 0x32) = *(u16 *)(a + 0x84) + (*(u16 *)(p + 0x30) + (*(u16 *)(b + 0x86) - *(u16 *)(b + 0x84)));
            break;
        }
    } else {
        b[0x2B] = 1;
    }
    if (!(f_ApplyActiveColliderImpactResponse(a, b, p, k) & 0x80)) {
        *(u8 *)D_1F800182 = 0;
    }
    return 1;
}

/* The case dispatch is written as gotos: a switch gives another compare tree. */
s32 f_ResolveActiveColliderConfiguredActorContact(u8 *a, u8 *b, s32 k)
{
    u8 *m = a + 0x60;
    s32 c;
    s32 t;
    s16 dy;
    s16 h;
    s16 side;
    s32 r;

    if (!TestCyl_0B08(a, b)) {
        return 0;
    }
    if ((*(u32 *)b & 0xFF00FF) == 0x80003) {
        b[0x29] = 1;
        r = f_ApplyActiveColliderImpactResponse(a, b, 0, 0);
    } else {
        if (a[0x5F] == 0x10) {
            {
                s32 sw = a[0x46] >> 1;
                if (sw == 2) goto c2;
                if (sw >= 3) {
                    if (sw == 3) goto top;
                    goto done;
                }
                if (sw < 0) goto done;
                goto snap;
            }
        c2:
            dy = *(u16 *)(a + 0x32) - *(u16 *)(b + 0x32);
            side = dy;
            if (dy < 0) {
                h = *(u16 *)(b + 0x84) + *(u16 *)(a + 0x84);
                side = -dy;
            } else {
                h = (*(u16 *)(b + 0x86) - *(u16 *)(b + 0x84)) + (*(u16 *)(a + 0x86) - *(u16 *)(a + 0x84));
            }
            if (!(*(s16 *)(a + 0x80) + *(s16 *)(b + 0x80) - D_1F80008C_f832 < h - side)) {
                goto top;
            }
        snap:
            c = (rcos(*(s16 *)(m + 8) + 0x800) * (*(s16 *)(a + 0x80) + *(s16 *)(b + 0x80))) >> 12;
            t = rsin(*(s16 *)(m + 8) + 0x800) * (*(s16 *)(a + 0x80) + *(s16 *)(b + 0x80));
            *(u16 *)(a + 0x2E) = *(u16 *)(b + 0x2E) + c;
            *(u16 *)(a + 0x36) = *(u16 *)(b + 0x36) - (t >> 12);
            goto done;
        top:
            *(u16 *)(a + 0x2E) = *(u16 *)(b + 0x2E);
            *(u16 *)(a + 0x36) = *(u16 *)(b + 0x36);
            *(u16 *)(a + 0x32) = *(u16 *)(a + 0x84) + (*(u16 *)(b + 0x32) + (*(u16 *)(b + 0x86) - *(u16 *)(b + 0x84)));
        }
    done:
        r = f_ApplyActiveColliderImpactResponse(a, b, 0, k);
    }
    b[0x2B] = 1;
    if (!(r & 0x80)) {
        *(u8 *)D_1F800182 = 0;
    }
    return 1;
}

s32 f_ResolveActiveColliderActorContact(u8 *a, u8 *b, s32 k)
{
    s32 r;

    if (!TestCyl_0B08(a, b)) {
        return 0;
    }
    r = f_ApplyActiveColliderImpactResponse(a, b, 0, k);
    b[0x2B] = 1;
    if (!(r & 0x80)) {
        *(u8 *)D_1F800182 = 0;
    }
    return 1;
}

void func_80021800(u8 *a, u8 *b)
{
    if (TestCyl_0B08(a, b)) {
        f_ApplyActiveColliderImpactResponse(a, b, 0, 0x100);
        b[0x2B] = 1;
        *(u8 *)D_1F800182 = 0;
    }
}

s32 f_ResolveActiveColliderStaticActorContact(u8 *a, u8 *b, s32 flag)
{
    s32 r;

    if (!TestCyl_0B08(a, b)) {
        return 0;
    }
    if (b[0] & 8) {
        r = f_ApplyActiveColliderImpactResponse(a, b, 0, 0) & 0x80;
    } else if (flag == 0) {
        r = f_ApplyActiveColliderBlockingResponse(a, b, 0, 0x800) & 0x80;
    } else {
        r = f_ApplyActiveColliderBlockingResponse(a, b, 0, 0) & 0x80;
    }
    if (!r) {
        *(u8 *)D_1F800182 = 0;
    }
    return 1;
}

s32 func_80021AB0(u8 *a, u8 *b, s32 flag)
{
    u8 *m = a + 0x60;
    s32 c;
    s32 t;
    s16 dy;
    s16 h;
    s16 side;
    s32 r;

    if (!TestCyl_0B08(a, b)) {
        return 0;
    }
    if (b[0] & 8) {
        r = f_ApplyActiveColliderImpactResponse(a, b, 0, 0) & 0x80;
    } else if (b[0] == 1 && a[2] == 2 && a[0x5F] == 0x10) {
        {
            s32 sw = a[0x46] >> 1;
            if (sw == 2) goto c2;
            if (sw >= 3) {
                if (sw == 3) goto top;
                goto done;
            }
            if (sw < 0) goto done;
            goto snap;
        }
    c2:
        dy = *(u16 *)(a + 0x32) - *(u16 *)(b + 0x32);
        side = dy;
        if (dy < 0) {
            h = *(u16 *)(b + 0x84) + *(u16 *)(a + 0x84);
            side = -dy;
        } else {
            h = (*(u16 *)(b + 0x86) - *(u16 *)(b + 0x84)) + (*(u16 *)(a + 0x86) - *(u16 *)(a + 0x84));
        }
        if (!(*(s16 *)(a + 0x80) + *(s16 *)(b + 0x80) - D_1F80008C_f832 < h - side)) {
            goto top;
        }
    snap:
        c = (rcos(*(s16 *)(m + 8) + 0x800) * (*(s16 *)(a + 0x80) + *(s16 *)(b + 0x80))) >> 12;
        t = rsin(*(s16 *)(m + 8) + 0x800) * (*(s16 *)(a + 0x80) + *(s16 *)(b + 0x80));
        *(u16 *)(a + 0x2E) = *(u16 *)(b + 0x2E) + c;
        *(u16 *)(a + 0x36) = *(u16 *)(b + 0x36) - (t >> 12);
        goto done;
    top:
        *(u16 *)(a + 0x2E) = *(u16 *)(b + 0x2E);
        *(u16 *)(a + 0x36) = *(u16 *)(b + 0x36);
        *(u16 *)(a + 0x32) = *(u16 *)(a + 0x84) + (*(u16 *)(b + 0x32) + (*(u16 *)(b + 0x86) - *(u16 *)(b + 0x84)));
    done:
        r = f_ApplyActiveColliderBlockingResponse(a, b, 0, 0x1100) & 0x80;
    } else if (flag == 0) {
        r = f_ApplyActiveColliderBlockingResponse(a, b, 0, 0x800) & 0x80;
    } else {
        r = f_ApplyActiveColliderBlockingResponse(a, b, 0, 0) & 0x80;
    }
    if (!r) {
        *(u8 *)D_1F800182 = 0;
    }
    return 1;
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_80021DF4);

void func_80021F34(u8 *a, u8 *b)
{
    if (TestCyl_0B08(a, b)) {
        if (!(f_ApplyActiveColliderBlockingResponse(a, b, 0, 0) & 0x80)) {
            *(u8 *)D_1F800182 = 0;
        }
    }
}

extern u8 D_1F80027A;
extern s8 D_800BF81E;
void f_RetireActorOnTombaContact(u8 *a, u8 *b)
{
    if (D_1F80027A == 0 && TestCyl_0B08(a, b)) {
        b[0] = 2;
        b[4] = 2;
        b[5] = 0;
        b[6] = 0;
        D_800BF81E = 0;
    }
}

/* static inline Test3794_2190: func_80023794, inlined */
extern u8 D_800A29CC[][8];

static inline s32 Test3794_2190(u8 *a, u8 *pos, u8 *r)
{
    s16 dx = *(u16 *)(a + 0x2E) - *(u16 *)(pos + 4);
    s16 dz = *(u16 *)(a + 0x36) - *(u16 *)(pos + 8);
    s32 d = SquareRoot0(dx * dx + dz * dz);

    if ((u16)d > *(s16 *)(a + 0x80) + r[4]) {
        return 0;
    }
    return (u16)((*(u16 *)(a + 0x32) - *(u16 *)(pos + 6)) + (*(u16 *)(a + 0x84) + r[5])) <= *(s16 *)(a + 0x86) + r[5] * 2;
}
void func_80022190(u8 *a, u8 *e)
{
    u8 *m = e + 0x60;
    u8 *p = *(u8 **)(m + 0xC);
    s32 i;

    for (i = 0; i < *(s16 *)(m + 0xA); i++, p += 0x10) {
        u8 *r = D_800A29CC[p[3]];
        s32 one = 1;
        if (*(s32 *)(m + 0x10) & (one << i)) {
            if (Test3794_2190(a, p, r)) {
                *(s32 *)(m + 0x14) |= one << i;
                *(s32 *)(m + 0x10) &= ~(one << i);
                func_8004D19C(e, p, 0);
                return;
            }
        }
    }
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_80022330);

INCLUDE_ASM("asm/main/nonmatchings/main", f_ResolveFlag40ActorClass5Contacts);

extern s8 D_800BF80D;
extern s8 D_1F800182[];
extern s8 D_1F800154[];
extern s8 D_1F80015C[];
void f_ResolveTombaClass5ActorContacts(u8 *a)
{
    u8 **list;
    u8 *e;

    if (*(s16 *)(a + 0x16E) == 0 || D_800BF80D != 0 || (*(u16 *)(a + 0x17E) & 0x200)) {
        return;
    }
    list = *(u8 ***)D_1F800154;
    *(u8 *)D_1F800182 = *(u8 *)D_1F80015C;
    while (*(u8 *)D_1F800182 != 0) {
        e = *list;
        *(u8 *)D_1F800182 = *(u8 *)D_1F800182 - 1;
        list++;
        if (e[0] == 1) {
            switch (e[2]) {
            case 4:
                if (e[0x5E] == 2) {
                    func_80114E74(a, e);
                    break;
                }
            case 0: case 1: case 2: case 3: case 7:
                f_RetireActorOnTombaContact(a, e);
                break;
            case 6:
                func_80022190(a, e);
                break;
            }
        }
    }
}

INCLUDE_ASM("asm/main/nonmatchings/main", f_PrepareTombaCollisionFrame);

extern s8 *D_800ECF68;
extern u8 D_80017FE8[];
extern s8 *D_800ECF58[];
extern void (*D_8009D1D4[])(void);
extern void *D_80017334_ae99[];
typedef struct SVec { s16 vx, vy, vz, pad; } SVec;
void func_80022A80(void)
{
    if (D_800BF870.unk0 != 3) {
        D_8009D1D4[D_800BF870.unk0]();
    }
}

s32 func_80022AC8(u8 *a, u8 *b, u8 *p, s32 k)
{
    s32 r;

    if (!TestPartCyl_2AC8(a, b, p)) {
        return 0;
    }
    r = f_ApplyActiveColliderImpactResponse(a, b, p, k);
    b[0x2B] = 1;
    if (!(r & 0x80)) {
        *(u8 *)D_1F800182 = 0;
    }
    return 1;
}

extern u8 D_800BFE55;
extern u8 D_800BF81E_6fe1;
extern s32 D_800A3AC4[];
extern s32 D_800BFE34;
extern u16 D_1F800160;
extern u16 D_1F800162;
extern u16 D_1F800164;
extern s32 D_1F800080;
extern s32 D_1F800084_8c7c;
extern u16 D_1F8000D0_fb20[];
s32 f_ApplyTombaEnvironmentalDamage(u8 *t, s32 dmg)
{
    if (D_800BFE55 != 0) {
        return 0;
    }
    t[0] |= 2;
    if (*(s16 *)(t + 0x17E) < 0) {
        dmg *= 2;
    }
    *(s16 *)(t + 0x16E) -= dmg;
    if (*(s16 *)(t + 0x16E) <= 0) {
        *(s16 *)(t + 0x16E) = 0;
        D_800BF80D = -1;
    }
    D_800BF81E_6fe1 = 0;
    return 1;
}

void f_ApplyTombaSupportedContactState(u8 *a)
{
    s32 c;
    s32 d;
    u16 k;

    a[0x29] = 1;
    a[0x145] = 0;
    *(s16 *)(a + 0x4A) = 0;
    *(s16 *)(a + 0x50) = 0;
    a[0x148] = 0;
    if (a[0x78] == 0 && D_800BF816 == 0) {
        if (*(s16 *)(a + 0x17E) >= 0) {
            c = 0x8C;
            k = *(u16 *)(a + 0x84);
            if (*(s16 *)(a + 0x84) == c) {
                return;
            }
            d = *(u16 *)(a + 0x32) - 0x8C;
        } else {
            c = 0x46;
            k = *(u16 *)(a + 0x84);
            if (*(s16 *)(a + 0x84) == c) {
                return;
            }
            d = *(u16 *)(a + 0x32) - 0x46;
        }
        *(u16 *)(a + 0x32) = k + d;
    }
}

extern u8 D_800BF839;
/* f_ApplyTombaEnvironmentalDamage, inlined */
static inline s32 EnvDamage_2D3C(u8 *t, s32 dmg)
{
    if (D_800BFE55 != 0) {
        return 0;
    }
    t[0] |= 2;
    if (*(s16 *)(t + 0x17E) < 0) {
        dmg *= 2;
    }
    *(s16 *)(t + 0x16E) -= dmg;
    if (*(s16 *)(t + 0x16E) <= 0) {
        *(s16 *)(t + 0x16E) = 0;
        D_800BF80D = -1;
    }
    D_800BF81E_6fe1 = 0;
    return 1;
}
s32 f_TryApplyTombaActorDamage(u8 *t, u8 *src, s32 dmg, s32 force)
{
    if (*(u16 *)(t + 0x17E) & 0x200) {
        return 0;
    }
    if (D_800BFE55 != 0) {
        return 0;
    }
    if (t[0x144] == 2) {
        return 0;
    }
    if (*(s16 *)(t + 0x16E) == 0) {
        return 0;
    }
    if (D_800BF839 != 0) {
        return 0;
    }
    if (D_1F800137_104c != 0) {
        return 0;
    }
    if (t[0] & 2) {
        return 0;
    }
    if (force == 0 && (src[0] & 2)) {
        return 0;
    }
    return EnvDamage_2D3C(t, dmg);
}

s32 f_TestActorAgainstPartCylinderOverlap(u8 *a, u8 *b, u8 *p)
{
    s16 dx = *(u16 *)(a + 0x2E) - *(u16 *)(p + 0x2C);
    s16 dz = *(u16 *)(a + 0x36) - *(u16 *)(p + 0x34);
    s32 d = SquareRoot0(dx * dx + dz * dz);

    if ((u16)d > *(s16 *)(a + 0x80) + *(s16 *)(b + 0x80)) {
        return 0;
    }
    if ((u16)((*(u16 *)(a + 0x32) - *(u16 *)(p + 0x30)) + (*(u16 *)(a + 0x84) + *(u16 *)(b + 0x84))) > *(s16 *)(a + 0x86) + *(s16 *)(b + 0x86)) {
        return 0;
    }
    D_1F80009C = ratan2(-dz, dx);
    return 1;
}

extern s32 D_1F80008C_f832;
s32 f_TestActorCylinderOverlap(u8 *a, u8 *b)
{
    s16 dx = *(u16 *)(a + 0x2E) - *(u16 *)(b + 0x2E);
    s16 dz = *(u16 *)(a + 0x36) - *(u16 *)(b + 0x36);
    s32 d = SquareRoot0(dx * dx + dz * dz);

    if ((u16)d > *(s16 *)(a + 0x80) + *(s16 *)(b + 0x80)) {
        return 0;
    }
    if ((u16)((*(u16 *)(a + 0x32) - *(u16 *)(b + 0x32)) + (*(u16 *)(a + 0x84) + *(u16 *)(b + 0x84))) > *(s16 *)(a + 0x86) + *(s16 *)(b + 0x86)) {
        return 0;
    }
    D_1F80008C_f832 = (s16)d;
    D_1F80009C = ratan2(-dz, dx, d);
    return 1;
}

s32 f_TestActorCylinderOverlapWithRadius(u8 *a, u8 *b, s32 r)
{
    s16 dx = *(u16 *)(b + 0x2E) - *(u16 *)(a + 0x2E);
    s16 dz = *(u16 *)(b + 0x36) - *(u16 *)(a + 0x36);
    s32 d = SquareRoot0(dx * dx + dz * dz);

    if ((u16)d > *(s16 *)(a + 0x80) + r) {
        return 0;
    }
    if ((u16)((*(u16 *)(a + 0x32) - *(u16 *)(b + 0x32)) + (*(u16 *)(a + 0x84) + *(u16 *)(b + 0x84))) > *(s16 *)(a + 0x86) + *(s16 *)(b + 0x86)) {
        return 0;
    }
    D_1F80008C_f832 = (s16)d;
    D_1F80009C = ratan2(-dz, dx, d);
    return 1;
}

void f_ResolveTombaType12ActorContact(void) {
    func_8001EC3C();
}

s32 f_TestActorAgainstPartCylinderBounds(u8 *a, u8 *b, u8 *p)
{
    s16 dx = *(u16 *)(a + 0x2E) - *(u16 *)(p + 0x2C);
    s16 dz = *(u16 *)(a + 0x36) - *(u16 *)(p + 0x34);
    s32 d = SquareRoot0(dx * dx + dz * dz);

    if ((u16)d > *(s16 *)(a + 0x80) + *(s16 *)(b + 0x80) || (u16)((*(u16 *)(a + 0x32) - *(u16 *)(p + 0x30)) + (*(u16 *)(a + 0x84) + *(u16 *)(b + 0x84))) > *(s16 *)(a + 0x86) + *(s16 *)(b + 0x86)) {
        return 0;
    }
    D_1F80009C = ratan2(-dz, dx);
    return 1;
}

extern u16 D_800A4A6C[];
extern u16 D_800E7FFE;
extern u16 D_1F8001A2;
void func_80023238(u8 *a, u8 *b)
{
    if (D_800E7FFE & 0x200) {
        return;
    }
    if (*(u8 **)(a + 0x10) != NULL) {
        return;
    }
    *(u8 **)(a + 0x10) = b;
    a[0x2B] = 2;
    *(u16 *)(b + 0x2E) = *(u16 *)(a + 0x2E);
    *(u16 *)(b + 0x32) = *(u16 *)(a + 0x32);
    *(u16 *)(b + 0x36) = *(u16 *)(a + 0x36);
}

extern u8 D_800BFE55;
extern u8 D_1F800137_104c;
extern u8 *D_800BF844;
extern u8 D_800BF4F8[];
s32 f_CanTombaTakeDamage(u8 *t)
{
    if (*(s16 *)(t + 0x16E) == 0 || D_800BF839 != 0) {
        return 0;
    }
    if (D_800BFE55 != 0) {
        return 0;
    }
    if (D_1F800137_104c != 0 || (t[0] & 2)) {
        return 0;
    }
    return 1;
}

extern s8 D_800BF80D;
extern s8 D_800BF81E;
void func_800232F4(void *arg0) {
    if (M2C_FIELD(arg0, s16 *, 0x16E) <= 0) {
        M2C_FIELD(arg0, s16 *, 0x16E) = 0;
        D_800BF80D = -1;
    }
    D_800BF81E = 0;
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_80023320);

void func_8002343C(void *arg0) {
    M2C_FIELD(arg0, s8 *, 0) = 2;
    M2C_FIELD(arg0, s8 *, 4) = 2;
    M2C_FIELD(arg0, s8 *, 5) = 2;
    M2C_FIELD(arg0, s8 *, 6) = 0;
}

void func_80023454(void *arg0) {
    M2C_FIELD(arg0, s8 *, 0) = 2;
    M2C_FIELD(arg0, s8 *, 4) = 2;
    M2C_FIELD(arg0, s8 *, 5) = 7;
    M2C_FIELD(arg0, s8 *, 6) = 0;
}

void func_80023470(void *arg0) {
    M2C_FIELD(arg0, s8 *, 0) = 2;
    M2C_FIELD(arg0, s8 *, 4) = 2;
    M2C_FIELD(arg0, s8 *, 5) = 8;
    M2C_FIELD(arg0, s8 *, 6) = 0;
}

void func_8002348C(void *arg0) {
    M2C_FIELD(arg0, s8 *, 0) = 3;
    M2C_FIELD(arg0, s8 *, 4) = 2;
    M2C_FIELD(arg0, s8 *, 5) = 0;
    M2C_FIELD(arg0, s8 *, 6) = 0;
}

void func_800234A8(void *arg0) {
    M2C_FIELD(arg0, s8 *, 0) = 3;
    M2C_FIELD(arg0, s8 *, 4) = 2;
    M2C_FIELD(arg0, s8 *, 5) = 4;
    M2C_FIELD(arg0, s8 *, 6) = 0;
}

void func_800234C8(void *arg0) {
    M2C_FIELD(arg0, s8 *, 0) = 3;
    M2C_FIELD(arg0, s8 *, 4) = 2;
    M2C_FIELD(arg0, s8 *, 5) = 5;
    M2C_FIELD(arg0, s8 *, 6) = 0;
}

void func_800234E8(void *arg0) {
    M2C_FIELD(arg0, s8 *, 0) = 3;
    M2C_FIELD(arg0, s8 *, 4) = 2;
    M2C_FIELD(arg0, s8 *, 5) = 6;
    M2C_FIELD(arg0, s8 *, 6) = 0;
}

void func_80023508(void *arg0) {
    M2C_FIELD(arg0, s8 *, 0) = 3;
    M2C_FIELD(arg0, s8 *, 4) = 2;
    M2C_FIELD(arg0, s8 *, 5) = 0xA;
    M2C_FIELD(arg0, s8 *, 6) = 0;
}

void func_80023528(void *arg0) {
    M2C_FIELD(arg0, s8 *, 0) = 3;
    M2C_FIELD(arg0, s8 *, 4) = 2;
    M2C_FIELD(arg0, s8 *, 5) = 0xB;
    M2C_FIELD(arg0, s8 *, 6) = 0;
}

s32 func_80023548(void *a, void *b)
{
    s32 cls = f_ClassifyTombaActorCylinderContact(a, b, 1);

    if (cls < 0) {
        return 0;
    }
    f_ResolveTombaActorImpactResponse(a, b, cls, 1);
    return 1;
}

extern u8 D_800BE1F8_296f[];
s32 func_800235A0(u8 *t, u8 *other)
{
    s32 c = f_ClassifyTombaActorCylinderContact(t, other, 1);

    if (c < 0) {
        return 0;
    }
    if (t[0x164] == 0xC) {
        f_ResolveTombaActorImpactResponse(t, other, c, 4);
    } else {
        f_ResolveTombaActorImpactResponse(t, other, c, 1);
    }
    return 1;
}

void f_ResolveActiveColliderOffsetActorContact(void *arg0, void *arg1) {
    if ((M2C_FIELD(arg0, u8 *, 0x2A) == M2C_FIELD(arg1, u8 *, 0x2A)) && (f_TestActorOffsetCylinderOverlap(arg0, arg1) != 0)) {
        f_ApplyActiveColliderImpactResponse(arg0, arg1, 0, 0);
        if ((u32) (M2C_FIELD(arg0, u8 *, 2) - 1) < 9U) {
            M2C_FIELD(arg1, s8 *, 0x2B) = 1;
        }
        *((s8 *)D_1F800182) = 0;
    }
}

extern u8 D_1F800182_5650;
void func_8002369C(u8 *a, u8 *b)
{
    if (f_ClassifyActorCylinderContact(a, b) >= 0) {
        a[0x2B] = 2;
        b[0x2B] = 2;
        if (!(D_800E7FFE & 0x200) && *(u8 **)(a + 0x10) == NULL) {
            *(u8 **)(a + 0x10) = b;
            a[0x2B] = 2;
            *(u16 *)(b + 0x2E) = *(u16 *)(a + 0x2E);
            *(u16 *)(b + 0x32) = *(u16 *)(a + 0x32);
            *(u16 *)(b + 0x36) = *(u16 *)(a + 0x36);
        }
        b[0x46] = a[0x46] & 1;
        f_PlaySoundEffect(0x2F, 0, 0);
        f_SpawnImpactTransientEffect(2, a + 0x2C, a[0x5E], a + 0x68);
        D_1F800182_5650 = 0;
    }
}

void func_80023764(s32 arg0, void *arg1) {
    if (f_ResolveTombaRadialContactAndSide((u8 *)arg0, arg1) != 0) {
        M2C_FIELD(arg1, s8 *, 0x29) = 1;
    }
}

s32 func_80023794(u8 *a, u8 *pos, u8 *r)
{
    s16 dx = *(u16 *)(a + 0x2E) - *(u16 *)(pos + 4);
    s16 dz = *(u16 *)(a + 0x36) - *(u16 *)(pos + 8);
    s32 d = SquareRoot0(dx * dx + dz * dz);

    if ((u16)d > *(s16 *)(a + 0x80) + r[4]) {
        return 0;
    }
    return (u16)((*(u16 *)(a + 0x32) - *(u16 *)(pos + 6)) + (*(u16 *)(a + 0x84) + r[5])) <= *(s16 *)(a + 0x86) + r[5] * 2;
}

s32 f_TestWrappedAngleSide(s32 a, s32 b, s32 flip);
s32 f_PushActorOutsidePartCylinder(u8 *a, u8 *b, u8 *p)
{
    s16 dx = *(u16 *)(a + 0x2E) - *(u16 *)(p + 0x2C);
    s16 dz = *(u16 *)(a + 0x36) - *(u16 *)(p + 0x34);
    s32 d = SquareRoot0(dx * dx + dz * dz);
    s32 c;
    s32 t;

    if ((u16)d > *(s16 *)(a + 0x80) + *(s16 *)(b + 0x80)) {
        return 0;
    }
    if ((u16)((*(u16 *)(a + 0x32) - *(u16 *)(p + 0x30)) + (*(u16 *)(b + 0x84) + (*(u16 *)(a + 0x86) - *(u16 *)(a + 0x84)))) > *(s16 *)(a + 0x86) + *(s16 *)(b + 0x86)) {
        return 0;
    }
    D_1F80009C = ratan2(-dz, dx);
    if (a[0xC] == 2) {
        a[0x5F] = f_TestWrappedAngleSide(*(s16 *)&D_1F80009C, *(s16 *)(a + 0x60), 1) + 2;
    }
    c = (rcos(D_1F80009C) * (*(s16 *)(a + 0x80) + *(s16 *)(b + 0x80))) >> 12;
    t = rsin(D_1F80009C) * (*(s16 *)(a + 0x80) + *(s16 *)(b + 0x80));
    *(u16 *)(a + 0x2E) = *(u16 *)(p + 0x2C) + c;
    *(u16 *)(a + 0x36) = *(u16 *)(p + 0x34) - (t >> 12);
    return 1;
}

INCLUDE_ASM("asm/main/nonmatchings/main", f_ResolveActorPairCylinderContactClass);

INCLUDE_ASM("asm/main/nonmatchings/main", f_ResolveActorPartCylinderContactClass);

s32 func_800240FC(u8 *a, u8 *b)
{
    s16 dx = *(u16 *)(a + 0x2E) - *(u16 *)(b + 0x2E);
    s16 dz = *(u16 *)(a + 0x36) - *(u16 *)(b + 0x36);
    s32 d = SquareRoot0(dx * dx + dz * dz);

    if ((u16)d > *(s16 *)(a + 0x80) + *(s16 *)(b + 0x80)) {
        return 0;
    }
    if ((u16)((*(u16 *)(a + 0x32) - *(u16 *)(b + 0x32)) + ((*(u16 *)(b + 0x84) + *(u16 *)(a + 0x86)) - *(u16 *)(a + 0x84))) > *(s16 *)(a + 0x86) + *(s16 *)(b + 0x86)) {
        return 0;
    }
    D_1F80009C = ratan2(-dz, dx);
    return 1;
}

extern s8 D_800E80A8[];
typedef struct { u8 pad0[0xC]; s32 x; s32 y; s32 z; } CameraTarget;
extern CameraTarget D_1F8000D0;
extern s8 D_800BF88E;
extern s8 D_800E7E80[];
s32 f_ResolveActorPairCylinderContactClass(void *a, void *b, s32 cls);
void func_800241FC(void *a, void *b)
{
    f_ResolveActorPairCylinderContactClass(a, b, 0);
}

void func_8002421C(void *a, void *b)
{
    f_ResolveActorPairCylinderContactClass(a, b, 1);
}

s32 f_SnapActorOntoCylinderTop(u8 *a, u8 *b)
{
    s16 dx;
    s16 dz;
    s32 d;

    if (*(s16 *)(a + 0x4A) >= 0) {
        dx = *(u16 *)(a + 0x2E) - *(u16 *)(b + 0x2E);
        dz = *(u16 *)(a + 0x36) - *(u16 *)(b + 0x36);
        d = SquareRoot0(dx * dx + dz * dz);
        if ((u16)d > *(s16 *)(a + 0x80) + *(s16 *)(b + 0x80)
            || (u16)((*(u16 *)(a + 0x32) - *(u16 *)(b + 0x32)) + ((*(u16 *)(b + 0x84) + *(u16 *)(a + 0x86)) - *(u16 *)(a + 0x84))) > *(s16 *)(a + 0x86) + *(s16 *)(b + 0x86)) {
            return -1;
        }
        *(u16 *)(a + 0x32) = *(u16 *)(b + 0x32) - ((*(u16 *)(b + 0x84) + *(u16 *)(a + 0x86)) - *(u16 *)(a + 0x84));
        a[0x29] = 1;
        return 2;
    }
    return -1;
}

extern s32 D_1F800088;
s32 f_TestTombaSupportPointAgainstActorBounds(u8 *a, u8 *b)
{
    s16 dx = *(u16 *)(a + 0x14C) - *(u16 *)(b + 0x2E);
    s16 dz = *(u16 *)(a + 0x150) - *(u16 *)(b + 0x36);
    s32 d = SquareRoot0(dx * dx + dz * dz);

    if ((u16)d > *(s16 *)(b + 0x80) + D_1F800088
        || (u16)((*(u16 *)(a + 0x14E) - *(u16 *)(b + 0x32)) + (*(u16 *)(b + 0x84) + *(u16 *)(a + 0x68))) > *(s16 *)(b + 0x86) + *(s16 *)(a + 0x68) * 2) {
        return 0;
    }
    D_1F80008C_f832 = ratan2(-dz, dx);
    {
        u16 y = *(u16 *)(a + 0x32) - *(u16 *)(b + 0x32);
        D_1F800084_8c7c = 0;
        *(u16 *)(a + 0x156) = y;
    }
    return 1;
}

extern s8 D_1F800084[];
extern s8 D_1F8001A0[];
extern s8 D_1F8001A6[];
s32 func_80024448(s32 arg0) {
    s32 temp_v0;
    s32 var_a3;
    u16 temp_v1;

    var_a3 = 0x25;
    if (M2C_FIELD(arg0, s16 *, 0x17E) >= 0) {
        var_a3 = 0x4A;
    }
    M2C_FIELD(arg0, u8 *, 0x17D) = 0U;
    temp_v0 = func_80046A44(arg0, (s32) M2C_FIELD(arg0, s16 *, 0x66), (s32) (s16) ((s32) M2C_FIELD(arg0, u16 *, 0x68) * -1), var_a3);
    if (temp_v0 != 0) {
        M2C_FIELD(arg0, u8 *, 0x17D) = (u8) (((u16) *((u16 *)D_1F8001A6) >> 0xB) & 3);
        func_80048654(arg0);
        temp_v1 = *((u16 *)D_1F8001A0);
        M2C_FIELD(arg0, u16 *, 0x140) = temp_v1;
        if (M2C_FIELD(arg0, u8 *, 0x147) != 0) {
            M2C_FIELD(arg0, u16 *, 0x56) = (u16) ((temp_v1 - 0x800) & 0xFFF);
        } else {
            M2C_FIELD(arg0, u16 *, 0x56) = temp_v1;
        }
        if (temp_v0 == 2) {
            if (M2C_FIELD(arg0, u8 *, 0x17D) & 1) {
                M2C_FIELD(arg0, s8 *, 0x164) = 7;
                f_UpdateTombaForwardContactProbe(arg0);
            } else {
                goto block_10;
            }
        } else {
block_10:
            M2C_FIELD(arg0, s8 *, 0x164) = 4;
        }
        M2C_FIELD(arg0, s8 *, 0x15C) = (s8) temp_v0;
        *((s32 *)D_1F800084) = 0;
        return 1;
    }
    return 0;
}

extern s8 D_1F800137[];
extern void (*D_8009D22C[])(void);
extern u8 **D_1F800158_fd3d;
extern u8 D_1F80015E_6ff1;
/* f_UpdateTombaForwardContactProbe, inlined */
static inline void FwdProbe_4448(u8 *a)
{
    s16 r;
    s32 p;

    if (a[0x147] != 0) {
        *(u16 *)(a + 0x56) = (*(u16 *)(a + 0x140) - 0x800) & 0xFFF;
    } else {
        *(u16 *)(a + 0x56) = *(u16 *)(a + 0x140);
    }
    if (*(s16 *)(a + 0x17E) >= 0) {
        r = *(u16 *)(a + 0x66) - 0x1E;
        D_1F800088 = 0x28;
    } else {
        r = *(u16 *)(a + 0x66) - 0xA;
        D_1F800088 = 0x14;
    }
    *(s16 *)(a + 0x14C) = *(u16 *)(a + 0x2E) + ((rcos(*(s16 *)(a + 0x56)) * r) >> 12);
    p = rsin(*(s16 *)(a + 0x56)) * r;
    *(s16 *)(a + 0x14E) = *(u16 *)(a + 0x32) - *(u16 *)(a + 0x68);
    *(s16 *)(a + 0x150) = *(u16 *)(a + 0x36) - (p >> 12);
}
/* func_80024D34, inlined */
static inline s32 Scan_4448(u8 *a)
{
    u8 **list;
    u8 *e;

    if (!(*(u16 *)(a + 0x17E) & 0x200)) {
        list = D_1F800158_fd3d;
        D_1F800182_5650 = D_1F80015E_6ff1;
        while (D_1F800182_5650 != 0) {
            e = *list;
            D_1F800182_5650--;
            list++;
            if ((e[0] & 4) && e[2] == 2) {
                func_80114320(a, e);
            }
        }
    }
    return D_1F800080;
}
s32 f_FindTombaSupportInteractionTarget(u8 *a, s32 flag)
{
    s32 r;

    if (a[0x16B] != 0) {
        return 0;
    }
    if ((u8)D_1F800137[0] != 0) {
        return 0;
    }
    if (flag == 0 && a[0x144] >= 2) {
        return 0;
    }
    D_1F800080 = 0;
    D_1F800088 = 0;
    FwdProbe_4448(a);
    if (D_800BF870.unk0 == 0) {
        r = Scan_4448(a);
        if (r != 0) {
            return r;
        }
    }
    r = ((s32 (*)(u8 *))D_8009D22C[D_800BF870.unk0])(a);
    if (r != 0) {
        return r;
    }
    r = func_80024448((s32)a);
    if (r != 0) {
        return r;
    }
    return 0;
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_80024794);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800248D0);

void f_UpdateTombaForwardContactProbe(u8 *a)
{
    s16 r;
    s32 p;

    if (a[0x147] != 0) {
        *(u16 *)(a + 0x56) = (*(u16 *)(a + 0x140) - 0x800) & 0xFFF;
    } else {
        *(u16 *)(a + 0x56) = *(u16 *)(a + 0x140);
    }
    if (*(s16 *)(a + 0x17E) >= 0) {
        r = *(u16 *)(a + 0x66) - 0x1E;
        D_1F800088 = 0x28;
    } else {
        r = *(u16 *)(a + 0x66) - 0xA;
        D_1F800088 = 0x14;
    }
    *(s16 *)(a + 0x14C) = *(u16 *)(a + 0x2E) + ((rcos(*(s16 *)(a + 0x56)) * r) >> 12);
    p = rsin(*(s16 *)(a + 0x56)) * r;
    *(s16 *)(a + 0x14E) = *(u16 *)(a + 0x32) - *(u16 *)(a + 0x68);
    *(s16 *)(a + 0x150) = *(u16 *)(a + 0x36) - (p >> 12);
}

s32 f_TestTombaSupportPointAgainstPartBounds(u8 *a, u8 *b, u8 *p)
{
    s16 dx = *(u16 *)(a + 0x14C) - *(u16 *)(p + 0x2C);
    s16 dz = *(u16 *)(a + 0x150) - *(u16 *)(p + 0x34);
    s32 d = SquareRoot0(dx * dx + dz * dz);

    if ((u16)d > *(s16 *)(b + 0x80) + D_1F800088
        || (u16)((*(u16 *)(a + 0x14E) - *(u16 *)(p + 0x30)) + (*(u16 *)(b + 0x84) + *(u16 *)(a + 0x68))) > *(s16 *)(b + 0x86) + *(s16 *)(a + 0x68) * 2) {
        return 0;
    }
    D_1F80008C_f832 = ratan2(-dz, dx);
    {
        u16 y = *(u16 *)(a + 0x32) - *(u16 *)(p + 0x30);
        D_1F800084_8c7c = (s32)p;
        *(u16 *)(a + 0x156) = y;
    }
    return 1;
}

extern s8 D_1F800214[];
extern s32 D_800A3EC8;
typedef struct Range8b { s32 sector; s32 size; } Range8b;
extern Range8b D_800BE118_9ace[];
extern u8 D_800BF88D;
extern u8 D_1F800251;
void func_80024CF4(void)
{
    D_8009D22C[D_800BF870.unk0]();
}

s32 func_80024D34(u8 *a)
{
    u8 **list;
    u8 *e;

    if (!(*(u16 *)(a + 0x17E) & 0x200)) {
        list = D_1F800158_fd3d;
        D_1F800182_5650 = D_1F80015E_6ff1;
        while (D_1F800182_5650 != 0) {
            e = *list;
            D_1F800182_5650--;
            list++;
            if ((e[0] & 4) && e[2] == 2) {
                func_80114320(a, e);
            }
        }
    }
    return D_1F800080;
}

extern u8 D_800E7EEF;
extern u8 D_80017334[];
void f_InitializeHudTombaAnimation(u8 *a)
{
    switch (D_800E7EEF) {
    case 0x12:
        f_StartActorTimedFrameSequence(a, D_80017334, 0x28);
        a[0xD] |= 0x80;
        break;
    case 0x13:
        f_StartActorTimedFrameSequence(a, D_80017334, 0x27);
        a[0xD] |= 0x80;
        break;
    case 0x14:
        f_StartActorTimedFrameSequence(a, D_80017334, 0x25);
        a[0xD] |= 0x80;
        break;
    case 0x15:
        f_StartActorTimedFrameSequence(a, D_80017334, 0x179);
        a[0xD] |= 0x80;
        break;
    case 0x16:
        f_StartActorTimedFrameSequence(a, D_80017334, 0x26);
        a[0xD] |= 0x80;
        break;
    default:
        f_StartActorTimedFrameSequence(a, D_80017334, 0x24);
        a[0xD] &= 0x7F;
        break;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_80024F18);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800251F0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80025588);

typedef struct UiRect { s16 x, y, w, h; } UiRect;
extern u8 D_800A4554[];
extern u8 D_800BF87E;
extern u16 D_1F80017C_0fe7;
extern void *D_800173C0;
extern void *D_800173BC;
void func_80025744(u8 *a)
{
    struct { u8 b0; u8 b1; s16 h2; } q;
    UiRect r;
    GameState *g;
    void **tbl;
    void *qp;
    s32 flag;

    q.b1 = 8;
    q.h2 = -0x8000;
    r.x = 0x20;
    q.b0 = 0;
    r.w = 0;
    r.h = 0;
    r.y = 0xC8;
    f_DrawPackedUiQuadFrame(&r, *(void **)(a + 0x38), *(void **)(a + 0x3C), &q);
    tbl = (void **)D_80017334;
    g = &D_800BF870;
    qp = &q;
    q.h2 = 0;
    r.w = g->pad1[0xE] - 0x18;
    r.x += 0x18;
    f_DrawPackedUiQuadFrame(&r, tbl[0x29], *(void **)(a + 0x3C), qp);
    r.x += r.w;
    r.w = 0;
    f_DrawPackedUiQuadFrame(&r, tbl[0x2A], *(void **)(a + 0x3C), qp);
    if (g->pad1[0xD] != 0) {
        r.x = 0x32;
        r.y = 0xCC;
        r.w = g->pad1[0xD];
        flag = 0;
        switch (D_800E7EEF) {
        case 0x12:
            if (D_800BF87E >= (D_800A4554[0] >> 1)) { flag = 1; }
            break;
        case 0x13:
            if (D_800BF87E >= (D_800A4554[1] >> 1)) { flag = 1; }
            break;
        case 0x14:
            if (D_800BF87E >= (D_800A4554[2] >> 1)) { flag = 1; }
            break;
        case 0x15:
            if (D_800BF87E >= (D_800A4554[3] >> 1)) { flag = 1; }
            break;
        case 0x16:
            if (D_800BF87E >= (D_800A4554[4] >> 1)) { flag = 1; }
            break;
        default:
            goto draw;
        }
    draw:
        if (flag && (D_1F80017C_0fe7 & 3)) {
            f_DrawPackedUiQuadFrame(&r, D_800173C0, *(void **)(a + 0x3C), &q);
        } else {
            f_DrawPackedUiQuadFrame(&r, D_800173BC, *(void **)(a + 0x3C), &q);
        }
    }
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_80025934);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80025B78);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80025D98);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80026024);

typedef struct Linked { u8 pad0; u8 active; u8 pad2[0x1A]; void (*callback)(struct Linked *); u8 pad20[4]; struct Linked *next; } Linked;
extern Linked *D_800F2738;
extern Linked *D_800F2624;
extern s8 *D_800ECF58[];
extern u8 D_800ED058_93c7[];
void f_AddEvilPigRobePower(u8 n)
{
    GameState *g = &D_800BF870;

    g->pad1[0xD] += n;
    if (g->pad1[0xE] < g->pad1[0xD]) {
        g->pad1[0xD] = g->pad1[0xE];
    }
    D_800ED058_93c7[0xD] |= 1;
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_80026148);

s32 func_8002623C(u8 *a)
{
    switch (a[4]) {
    case 0:
        a[4]++;
        *(s16 *)(a + 0x12) = 0x2D;
        goto end;
    case 1:
        if (--*(s16 *)(a + 0x12) == 0) {
            a[0xD] &= 0xFE;
            return 1;
        }
    end:
    default:
        return 0;
    }
}

extern u16 D_800E7E68;
void func_800262A8(void *arg0) {
    if (D_800E7E68 & 0xC00) {
        M2C_FIELD(arg0, u8 *, 8) = (u8) (1 - M2C_FIELD(arg0, u8 *, 8));
    }
}

void func_800262D8(u8 *a, void *b, void *c, s16 d)
{
    f_DrawPackedUiQuadFrame(b, ((void **)D_80017334)[d], *(void **)(a + 0x3C), c);
}

void func_80026320(u8 *a, void *b, void *c, s16 d)
{
    f_DrawPackedUiSpriteFrame(b, ((void **)D_80017334)[d], *(void **)(a + 0x3C), c);
}

extern u8 *D_800FB168;
extern u8 *D_800F2624_9bdb;
extern u16 *D_1F8001C8;
extern u16 *D_1F8001CC;
extern u16 *D_1F8001D0;
extern u16 *D_1F8001D4_793a;
extern u16 *D_1F8001D8;
extern u16 *D_1F8001DC;
extern u8 D_80100400_8e62[];
extern void (*D_8009D314[])(u8 *);
extern u8 D_800EC188_8e7d[];
extern void (*D_8009D52C[])(u8 *);
typedef struct { u8 pad[0x48]; s32 n; } Counter48_808;
void func_80026368(void)
{
    u8 *e = D_80100400_8e62;
    s32 i;

    for (i = 0; i < 8; i++, e += 0x4C) {
        if (e[0] != 0) {
            D_8009D314[e[2]](e);
        }
    }
}

extern u8 D_1F8000D0_b839[];
extern u16 D_1F8001A0_6940;
extern u8 *D_8009D414[];
void func_800263E8(void)
{
    u8 *list = D_8009D414[D_800BF870.unk0];
    u8 *e;

    while (*list != 0xFF) {
        e = func_8007AD98();
        e[0] = 1;
        e[2] = *list++;
    }
}

typedef struct CameraTarget2 { u8 pad0[2]; u16 x; u8 pad4[2]; u16 y; u8 pad8[2]; u16 z; } CameraTarget2;
extern CameraTarget2 D_1F8000D0_d63a;
extern s8 D_800BF808_c1f7[];
extern void *D_800174C4;
typedef struct ChildList {
    /* 0x0 */ u8 pad0[8];
    /* 0x8 */ s16 count;
    /* 0xA */ u8 padA[2];
    /* 0xC */ u8 *children[1];
} ChildList;
void func_80026470(void)
{
    s8 *p = D_800BF808_c1f7;

    if (p[5] < 2 && ((u8 *)p)[0x31] == 0) {
        return;
    }
    f_SetStreamedAudioVolumeTarget(0);
}

typedef struct SoundHandle3 { u32 id; u8 pad4[8]; } SoundHandle3;
extern SoundHandle3 D_800BE238_0a61[];
extern u32 D_800BE358;
extern s16 D_800ED098;
extern u32 *D_800E7E74_7ca1;
void func_8006F2D0();
void func_800264BC(void)
{
    if (D_800BF808_c1f7[5] < 2 && ((u8 *)D_800BF808_c1f7)[0x31] == 0) {
        return;
    }
    f_SetStreamedAudioVolumeTarget(-1);
    f_SetStreamedAudioVolumeTarget(0x47FF);
}

void func_80026510(void)
{
    s8 *p = D_800BF808_c1f7;

    if (p[5] < 2 && ((u8 *)p)[0x31] == 0) {
        return;
    }
    f_SetStreamedAudioVolumeTarget(-1);
}

extern u8 D_800BF80F_fcc6;
extern u8 D_800ED06D;
void func_800264BC(void);
void func_8002655C(u8 *a)
{
    u8 *g;
    u8 c;
    u8 v;
    s32 one;

    switch (a[4]) {
    case 0:
        a[4]++;
        f_SetStreamedAudioVolumeTarget(-1);
        f_SetStreamedAudioVolumeTarget(0x47FF);
        switch (D_1F800236_18be) {
        case 5:
        case 6:
            *(s16 *)(a + 8) = 0x7F;
            *(s16 *)(a + 0xA) = 2;
            a[3] = 1;
            break;
        case 7:
        case 8:
            D_1F800236_18be = 0;
        case 0:
            *(s16 *)(a + 8) = 0x1F;
            *(s16 *)(a + 0xA) = 8;
            a[3] = 0;
            break;
        case 1:
        case 2:
        case 3:
        case 4:
        case 9:
            D_1F800236_18be = 0;
            *(s16 *)(a + 8) = 0x1F;
            *(s16 *)(a + 0xA) = 8;
            a[3] = 1;
            break;
        }
        f_DrawFullscreenOverlay(0xFFFFFF, a[3], 4);
        func_80050970();
        break;
    case 1:
        c = *(s16 *)(a + 0xA) * *(s16 *)(a + 8);
        f_DrawFullscreenOverlay((c << 16) | (c << 8) | c, a[3], 4);
        if (--*(s16 *)(a + 8) == 0) {
            a[4]++;
            D_800BF80F_fcc6 = 0;
        }
        break;
    case 2:
        g = D_800BF808;
        if (g[0x41] == 0 && D_800ED06D == 0) {
            if (g[7] == 2) {
                func_80026470();
                *(s16 *)(a + 8) = 0x1F;
                *(s16 *)(a + 0xA) = 8;
                a[3] = 0;
                a[4]++;
            } else if (g[7] == 4) {
                func_80026470();
                *(s16 *)(a + 8) = 0x1F;
                *(s16 *)(a + 0xA) = 8;
                a[3] = 1;
                a[4]++;
            }
        }
        break;
    case 3:
        c = -(*(s16 *)(a + 8) * 8);
        f_DrawFullscreenOverlay((c << 16) | (c << 8) | c, a[3], 4);
        g = D_800BF808;
        if (!(g[7] & 0x80)) {
            (*(s16 *)(a + 8))--;
        }
        if (*(s16 *)(a + 8) == 0) {
            a[4]++;
            g[7] = 0;
            func_80026510();
        }
        break;
    case 4:
        f_DrawFullscreenOverlay(0xFFFFFF, a[3], 4);
        v = D_800BF80F_fcc6;
        one = 1;
        if (v != 0) {
            if (v == one) {
                a[3] = 0;
            } else if (v == 3) {
                a[3] = one;
            }
            ((void (*)(s32))func_800264BC)(one);
            a[4] = 1;
            *(s16 *)(a + 8) = 0x1F;
            *(s16 *)(a + 0xA) = 8;
        }
        break;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_80026864);

extern u8 D_800BF849;
extern u8 D_1F800137_104c;
extern s8 *D_800ECF58[];
extern s8 D_1F800214[];
extern u8 D_800A4A94[];
extern u8 *D_800BF844;
s32 f_InitializeSinglePartActorModel(void *, s32, s32);
void f_RequestInteriorTransitionGateMode2(u8 *gate)
{
    s32 state = D_1F800137_104c;

    D_800BF80F_fcc6 = 2;
    if (state == 1) {
        gate[1] = state;
        return;
    }
    D_1F800137_104c = 2;
}

extern s8 D_800BF80F;
void f_RequestInteriorTransitionGateMode1(void) {
    D_800BF80F = 1;
}

void f_ReleaseInteriorTransitionControl(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 1) != 0) {
        M2C_FIELD(arg0, u8 *, 1) = 0U;
        return;
    }
    *((s8 *)D_1F800137) = 0;
}

void f_RetireInteriorSceneChildren(ChildList *l)
{
    s32 i;

    for (i = 0; i < l->count; i++) {
        if (l->children[i] != NULL) {
            l->children[i][4] = 3;
            l->children[i] = NULL;
        }
    }
    l->count = 0;
}

extern u16 D_800ECF54_4583[];
extern u16 D_800BED8C;
extern u8 *D_800BED88_191b;
extern u8 D_800E80A8_42d3[];
typedef struct ChildList2 {
    /* 0x0 */ u8 pad0[3];
    /* 0x3 */ u8 active;
    /* 0x4 */ u8 pad4[4];
    /* 0x8 */ s16 count;
    /* 0xA */ u8 padA[2];
    /* 0xC */ u8 *children[1];
} ChildList2;
void func_80026A68(ChildList2 *l)
{
    s32 i;

    if (l->active != 0) {
        for (i = 0; i < l->count; i++) {
            if (l->children[i] != NULL && l->children[i][4] == 3) {
                l->children[i] = NULL;
            }
        }
    }
}

extern u8 D_800BF818_7697;
void f_RequestInteriorTransitionGateMode1(void);
s32 func_80026AD0(u8 *a)
{
    u8 *g;

    switch (a[5]) {
    case 0:
        {
            u8 *h = D_800BF808;

            if (h[0x10] != 1) {
                return 0;
            }
            a[3] = h[0xF] + 1;
        }
        f_RequestInteriorTransitionGateMode2(a);
        a[5]++;
        break;
    case 1:
        g = D_800BF808;
        if (g[7] != 0) {
            return 0;
        }
        ((void (*)(u8 *))f_RequestInteriorTransitionGateMode1)(a);
        f_StopVoicePlayback();
        *(s16 *)(*(u8 **)D_1F800138 + 0x4C) = 3;
        *(s16 *)(*(u8 **)D_1F800138 + 0x4E) = 0;
        a[5] = 6;
        g[0x10] = 2;
        break;
    case 2:
        if (D_800BF80F_fcc6 != 0) {
            return 0;
        }
        f_ReleaseInteriorTransitionControl(a);
        a[5]++;
        break;
    case 3:
        if (D_800BF818_7697 != 3) {
            return 0;
        }
        f_RequestInteriorTransitionGateMode2(a);
        a[5]++;
        break;
    case 4:
        g = D_800BF808;
        if (g[7] != 0) {
            return 0;
        }
        f_RetireInteriorSceneChildren(a);
        ((void (*)(u8 *))f_RequestInteriorTransitionGateMode1)(a);
        *(s16 *)(*(u8 **)D_1F800138 + 0x4C) = 2;
        *(s16 *)(*(u8 **)D_1F800138 + 0x4E) = 4;
        g[0x10] = 4;
        a[5]++;
        break;
    case 5:
        if (D_800BF80F_fcc6 != 0) {
            return 0;
        }
        a[5] = 0;
        f_ReleaseInteriorTransitionControl(a);
        return 0;
    case 6:
        a[5] = 2;
        return 1;
    }
    return 0;
}

void func_80026C88(void)
{
    s32 i = 0;
    void (**t)(u8 *) = D_8009D52C;
    u8 *e = D_800EC188_8e7d;

    for (; i < 0x28; i++, e += 0x40) {
        if (e[0] != 0) {
            t[e[1]](e);
        }
    }
}

u8 *func_80026D08(u8 *out, u16 *hdr, u8 *prims, s32 i)
{
    u8 *p;

    if (i >= hdr[0]) {
        return prims + hdr[0] * 0x24;
    }
    p = (u8 *)(i * 0x24 + (s32)prims);
    out[0x33] = (p[3] & 2) | 0x24;
    out[0x34] = p[8];
    out[0x35] = p[9];
    out[0x38] = p[0xC];
    out[0x39] = p[0xD];
    out[0x3C] = p[0x22];
    out[0x3D] = p[0x23];
    *(u16 *)(out + 0x3A) = *(u16 *)(p + 0xE);
    *(u16 *)(out + 0x36) = *(u16 *)(p + 0xA);
    out[0x30] = p[0];
    out[0x31] = p[1];
    out[0x32] = p[2];
    return NULL;
}

u8 *func_80026DD8(u8 *out, u16 *hdr, u8 *prims, s32 i)
{
    u8 *p;

    if (i >= hdr[1]) {
        return prims + hdr[1] * 0x2C;
    }
    p = (u8 *)(i * 0x2C + (s32)prims);
    out[0x33] = (p[3] & 2) | 0x24;
    out[0x34] = p[8];
    out[0x35] = p[9];
    out[0x38] = p[0xC];
    out[0x39] = p[0xD];
    out[0x3C] = p[0x10];
    out[0x3D] = p[0x11];
    *(u16 *)(out + 0x3A) = *(u16 *)(p + 0xE);
    *(u16 *)(out + 0x36) = *(u16 *)(p + 0xA);
    out[0x30] = p[0];
    out[0x31] = p[1];
    out[0x32] = p[2];
    return NULL;
}

u8 *func_80026EB8(u8 *out, u16 *hdr, u8 *prims, s32 i)
{
    u8 *p;

    if (i >= hdr[2]) {
        return prims + hdr[2] * 0x24;
    }
    p = (u8 *)(i * 0x24 + (s32)prims);
    out[0x33] = (p[3] & 2) | 0x24;
    out[0x34] = p[4];
    out[0x35] = p[5];
    out[0x38] = p[8];
    out[0x39] = p[9];
    out[0x3C] = p[0xC];
    out[0x3D] = p[0xD];
    *(u16 *)(out + 0x3A) = *(u16 *)(p + 0xA);
    *(u16 *)(out + 0x36) = *(u16 *)(p + 6);
    out[0x30] = p[0];
    out[0x31] = p[1];
    out[0x32] = p[2];
    return NULL;
}

u8 *func_80026F88(u8 *out, u16 *hdr, u8 *prims, s32 i)
{
    u8 *p;

    if (i >= hdr[3]) {
        return prims + hdr[3] * 0x28;
    }
    p = (u8 *)(i * 0x28 + (s32)prims);
    out[0x33] = (p[3] & 2) | 0x24;
    out[0x34] = p[4];
    out[0x35] = p[5];
    out[0x38] = p[8];
    out[0x39] = p[9];
    out[0x3C] = p[0xC];
    out[0x3D] = p[0xD];
    *(u16 *)(out + 0x3A) = *(u16 *)(p + 0xA);
    *(u16 *)(out + 0x36) = *(u16 *)(p + 6);
    out[0x30] = p[0];
    out[0x31] = p[1];
    out[0x32] = p[2];
    return NULL;
}

extern u8 D_800F2740[];
extern u8 D_800FB11C[];
extern u8 D_800ED8C0[];
extern s32 *D_800E7E74;
extern u16 D_1F8001B2;
extern u16 D_1F8001B4;
extern u16 D_1F8001B6;
extern u16 D_1F8001B8;
void func_8002B7B0(u8 *);
void func_8002B3A4(u8 *);
void f_InitializeEffectSlotFromTemplateIndex(void *a, u16 *t, s32 n)
{
    void *r = func_80026D08(a, t, t + 8, n);

    if (r == 0) {
        return;
    }
    n -= t[0];
    r = func_80026DD8(a, t, r, n);
    if (r == 0) {
        return;
    }
    n -= t[1];
    r = func_80026EB8(a, t, r, n);
    if (r == 0) {
        return;
    }
    func_80026F88(a, t, r, n - t[2]);
}

extern void (*D_800A4AF8[])(void);
extern void (*D_800A4B50[])(void);
typedef struct EventReward { u8 pad0; u8 ap; u8 pad2[10]; } EventReward;
extern EventReward D_800A33C8[];
extern s32 D_800A3B38[];
s16 f_CountEffectTemplates(u16 *c)
{
    s32 n = c[0] + c[1];

    n += c[2];
    n += c[3];
    n += c[4];
    n += c[5];
    n += c[6];
    n += c[7];
    return n;
}

INCLUDE_ASM("asm/main/nonmatchings/main", f_SpawnEffectTemplateInstances);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80027254);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800275D4);

INCLUDE_ASM("asm/main/nonmatchings/main", f_DrawPackedGouraudQuadStream);

INCLUDE_ASM("asm/main/nonmatchings/main", f_DrawProjectedSpriteDefinitionStream);

extern s8 D_1F80008C[];
void func_80031780(u8 *p);
#define gte_ldv0_2C(r0) __asm__ volatile("lwc2 $0, 0x2C(%0); lwc2 $1, 0x30(%0)" : : "r"(r0))
/* f_SetEffectProjectionTransform, inlined */
static inline void SetProj_7CB4(s32 dqa)
{
    gte_SetRotMatrix(D_1F8000F8);
    gte_SetTransMatrix(D_1F8000F8);
    gte_lddqa(dqa);
    gte_lddqb0();
}
/* sprite depth projection, inlined */
static inline s32 ProjZ(u8 *a)
{
    s32 *flag = &D_1F800080;
    s32 *otz = (s32 *)D_1F800084;
    s32 *sxy = (s32 *)D_1F80008C;
    u16 h = *(u16 *)(a + 0x32);
    s32 e;

    gte_rtps();
    gte_stflg(flag);
    if (*flag < 0) {
        return 1;
    }
    gte_stsz(flag);
    if (*flag <= 0) {
        return 1;
    }
    *flag = (*flag >> 2) + (s16)h;
    if (*flag < 4) {
        *flag = 4;
    }
    e = *flag >> 10;
    *flag = (*flag >> e) + (e << 9);
    if ((u32)(*flag - 4) >= 0x7FC) {
        *flag = -1;
    }
    if (*flag < 0) {
        return 1;
    }
    gte_stsxy(sxy);
    gte_stopz(otz);
    return 0;
}
void func_80027CB4(u8 *a)
{
    s32 *flag = &D_1F800080;
    s32 *otz = (s32 *)D_1F800084;
    s32 *o2 = &D_1F800088;
    s32 *z = (s32 *)D_1F800090;
    s32 d = *(s32 *)(a + 0x34);

    if (d == 0) {
        return;
    }
    SetProj_7CB4(6);
    gte_ldv0_2C(a);
    if (ProjZ(a)) {
        func_80031780(a);
        return;
    }
    *o2 = *otz;
    *z = 0;
    *(s32 *)(a + 0x38) = f_DrawProjectedSpriteDefinitionStream(d, (*(u16 *)(a + 0x46) << 16) | *(u16 *)(a + 0x44));
}

void func_80027E5C(a)
    u8 *a;
{
    s32 *flag = &D_1F800080;
    s32 *otz = (s32 *)D_1F800084;
    s32 *o2 = &D_1F800088;
    s32 *z = (s32 *)D_1F800090;
    s32 d = *(s32 *)(a + 0x34);

    if (d == 0) {
        return;
    }
    SetProj_7CB4(6);
    gte_ldv0_2C(a);
    if (ProjZ(a)) {
        func_80031780(a);
        return;
    }
    *otz = (*otz * a[6]) >> 4;
    *o2 = *otz;
    *z = 0;
    *(s32 *)(a + 0x38) = f_DrawProjectedSpriteDefinitionStream(d, (*(u16 *)(a + 0x46) << 16) | *(u16 *)(a + 0x44));
}

void func_8002801C(u8 *a)
{
    s32 *flag = &D_1F800080;
    s32 *otz = (s32 *)D_1F800084;
    s32 *o2 = &D_1F800088;
    s32 *z = (s32 *)D_1F800090;
    s32 d = *(s32 *)(a + 0x34);

    if (d == 0) {
        return;
    }
    SetProj_7CB4(6);
    gte_ldv0_2C(a);
    if (ProjZ(a)) {
        func_80031780(a);
        return;
    }
    {
        s32 x;
        s32 y;
        s32 h = *(s16 *)(a + 0x4A);

        x = (*otz >> 8) * h;
        y = *(s16 *)(a + 0x48);
        *z = 0;
        *o2 = x;
        *otz = (*otz >> 8) * y;
    }
    *(s32 *)(a + 0x38) = f_DrawProjectedSpriteDefinitionStream(d, (*(u16 *)(a + 0x46) << 16) | *(u16 *)(a + 0x44));
}

void func_800281EC(u8 *a0)
{
    u8 *a = a0;
    s32 *otz = (s32 *)D_1F800084;
    s32 *z = (s32 *)D_1F800090;
    s32 d;
    s16 i;
    u8 *v;

    if (*(s32 *)(a + 0x34) == 0) {
        return;
    }
    if (a[3] == 0x21) {
        SetProj_7CB4(4);
    } else {
        SetProj_7CB4(6);
    }
    i = 0;
    v = a + 0x50;
    *z = 0;
    d = *(s32 *)(a + 0x34);
    func_80031780(a);
    do {
        s32 *o2 = &D_1F800088;
        gte_ldv0(v);
        if (ProjZ(a) == 0) {
            *otz = (*otz * *(s16 *)(v + 6)) >> 8;
            *o2 = *otz;
            f_DrawProjectedSpriteDefinitionStream(d, (*(u16 *)(a + 0x46) << 16) | *(u16 *)(a + 0x44));
        }
        i++;
        v += 8;
    } while (i < *(s16 *)(a + 0x4E));
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_8002847C);

void func_800286CC(u8 *a)
{
    s32 *otz = (s32 *)D_1F800084;
    s32 *o2 = &D_1F800088;
    u8 *p = *(u8 **)(a + 0x3C);
    u32 sc = *(u32 *)(a + 0x34);
    u8 c;

    if (p == 0) {
        return;
    }
    c = *p;
    if (c & 0x80) {
        *(u8 **)(a + 0x40) = 0;
        c &= 0x7F;
    } else {
        *(u8 **)(a + 0x40) = p + 1;
    }
    SetProj_7CB4(6);
    gte_ldv0_2C(a);
    if (ProjZ(a) == 0) {
        s32 t;
        *(s32 *)D_1F800090 = 0;
        *o2 = (u32)(*otz * (sc >> 16)) >> 8;
        t = (*(s32 **)(a + 0x50))[c];
        *otz = (u32)(*otz * (sc & 0xFFFF)) >> 8;
        func_8002847C(t, 0, 0);
    }
}

extern s32 D_1F800000[];
extern s16 D_1F800002[];
extern s16 D_1F800004[];
extern s32 D_1F800014[];
extern s32 D_1F8000D0_42d8[];
extern u8 D_800A203C[];
extern u8 D_8009F05C[];
extern void (*D_800A4AA0[])(u8 *);
extern s32 (*D_800A3B78[])(u8 *);
extern u8 D_800A1CD4[];
extern s32 D_1F800090_e8ac;
void func_800288AC(u8 *a)
{
    s32 *z = &D_1F800090_e8ac;
    s32 pad[12];
    s32 v[3];
    u8 *pos;
    u8 *p;
    s32 k;

    p = *(u8 **)(a + 0x3C);
    if (p != NULL) {
        RotMatrix_gte((s16 *)(a + 0x48), D_1F800000);
        v[0] = p[0] * 4;
        v[1] = p[1] * 4;
        v[2] = p[2] * 4;
        ScaleMatrix(D_1F800000, v);
        pos = a + 0x2C;
        gte_SetRotMatrix(D_1F8000F8);
        gte_ldclmv(D_1F800000);
        gte_rtir();
        gte_stclmv(D_1F800000);
        gte_ldclmv(D_1F800002);
        gte_rtir();
        gte_stclmv(D_1F800002);
        gte_ldclmv(D_1F800004);
        gte_rtir();
        gte_stclmv(D_1F800004);
        gte_ldv0(pos);
        gte_rtv0();
        gte_stlvnl(D_1F800014);
        D_1F800000[5] += D_1F8000D0_42d8[15];
        D_1F800000[6] += D_1F8000D0_42d8[16];
        D_1F800000[7] += D_1F8000D0_42d8[17];
        gte_SetRotMatrix(D_1F800000);
        gte_SetTransMatrix(D_1F800000);
        if (p[3] & 0x40) {
            *z = 0x1000 - ((p[3] & 0x3F) << 6);
            k = 0;
        } else {
            *z = 0;
            k = p[3] & 0xF;
        }
        if (p[3] & 0x80) {
            p += 4;
            *(s32 *)(a + 0x40) = 0;
        } else {
            p += 4;
            *(u8 **)(a + 0x40) = p;
        }
        gte_ldfcdir(0, 0, 0);
        f_DrawPackedGouraudQuadStream(*(u8 **)(a + 0x50), k, *(s16 *)(a + 0x32), a[0x29]);
    }
}

void func_80028B70(u8 *a)
{
    s32 *z = (s32 *)D_1F800090;
    s32 pad[4];
    s32 v[3];
    u8 *pos;
    u8 *p;
    u8 *m;
    s32 b;

    p = *(u8 **)(a + 0x3C);
    if (p != NULL) {
        b = p[0];
        if (b & 0x80) {
            *(s32 *)(a + 0x40) = 0;
            b &= 0x7F;
        } else {
            *(u8 **)(a + 0x40) = p + 1;
        }
        m = (*(u8 ***)(a + 0x50))[b];
        gte_ldfcdir(0, 0, 0);
        *z = 0;
        RotMatrix_gte((s16 *)(a + 0x48), D_1F800000);
        v[0] = D_800A1CD4[0] * 4;
        v[1] = D_800A1CD4[1] * 4;
        v[2] = D_800A1CD4[2] * 4;
        ScaleMatrix(D_1F800000, v);
        pos = a + 0x2C;
        gte_SetRotMatrix(D_1F8000F8);
        gte_ldclmv(D_1F800000);
        gte_rtir();
        gte_stclmv(D_1F800000);
        gte_ldclmv(D_1F800002);
        gte_rtir();
        gte_stclmv(D_1F800002);
        gte_ldclmv(D_1F800004);
        gte_rtir();
        gte_stclmv(D_1F800004);
        gte_ldv0(pos);
        gte_rtv0();
        gte_stlvnl(D_1F800014);
        D_1F800000[5] += D_1F8000D0_42d8[15];
        D_1F800000[6] += D_1F8000D0_42d8[16];
        D_1F800000[7] += D_1F8000D0_42d8[17];
        gte_SetRotMatrix(D_1F800000);
        gte_SetTransMatrix(D_1F800000);
        f_DrawPackedGouraudQuadStream(m, 0, *(s16 *)(a + 0x32), 0);
    }
}

typedef struct { void *p0; void *p4; u16 *p8; } FxDef_8E30;
extern FxDef_8E30 D_800A20B4[];
extern FxDef_8E30 D_8014BD54[];
extern FxDef_8E30 D_8013882C[];
extern FxDef_8E30 D_801389E4[];
extern FxDef_8E30 D_8011BC4C[];
extern FxDef_8E30 D_80143C1C[];
extern FxDef_8E30 D_8014034C[];
extern FxDef_8E30 D_8014C868[];
extern FxDef_8E30 D_80132DE0[];
extern FxDef_8E30 D_80145138[];
extern FxDef_8E30 D_8010E578[];
extern FxDef_8E30 D_8011EB94[];
extern FxDef_8E30 D_8011C09C[];
extern FxDef_8E30 D_8011DCB8[];
extern FxDef_8E30 D_8011CBD8[];
extern FxDef_8E30 D_8011CF0C[];
extern FxDef_8E30 D_801208D4[];
extern FxDef_8E30 D_8010D5D8[];
extern FxDef_8E30 D_8010C65C[];
extern FxDef_8E30 D_8010CACC[];
extern FxDef_8E30 D_8010D8AC[];
extern FxDef_8E30 D_8011FC0C[];
extern FxDef_8E30 D_801158A0[];
void f_InitializeTransientEffectActor(u8 *a, s32 id)
{
    FxDef_8E30 *d;
    u16 c = id & 0xFF;

    switch (id >> 8) {
    default:
        a[3] = c;
        d = &D_800A20B4[id & 0xFF];
        break;
    case 1:
        a[3] = c | 0x80;
        d = &D_8014BD54[c];
        break;
    case 2:
        a[3] = c | 0x80;
        d = &D_8013882C[c];
        break;
    case 3:
        a[3] = c | 0x80;
        d = &D_801389E4[c];
        break;
    case 4:
        a[3] = c | 0x80;
        d = &D_8011BC4C[c];
        break;
    case 5:
        a[3] = c | 0x80;
        d = &D_80143C1C[c];
        break;
    case 6:
        a[3] = c | 0x80;
        d = &D_8014034C[c];
        break;
    case 7:
        a[3] = c | 0x80;
        d = &D_8014C868[c];
        break;
    case 8:
        a[3] = c | 0x80;
        d = &D_80132DE0[c];
        break;
    case 9:
        a[3] = c | 0x80;
        d = &D_80145138[c];
        break;
    case 10:
        a[3] = c | 0x80;
        d = &D_8010E578[c];
        break;
    case 11:
        a[3] = c | 0x80;
        d = &D_8011EB94[c];
        break;
    case 12:
        a[3] = c | 0x80;
        d = &D_8011C09C[c];
        break;
    case 13:
        a[3] = c | 0x80;
        d = &D_8011DCB8[c];
        break;
    case 14:
        a[3] = c | 0x80;
        d = &D_8011CBD8[c];
        break;
    case 15:
        a[3] = c | 0x80;
        d = &D_8011CF0C[c];
        break;
    case 16:
        a[3] = c | 0x80;
        d = &D_801208D4[c];
        break;
    case 17:
        a[3] = c | 0x80;
        d = &D_8010D5D8[c];
        break;
    case 18:
        a[3] = c | 0x80;
        d = &D_8010C65C[c];
        break;
    case 19:
        a[3] = c | 0x80;
        d = &D_8010CACC[c];
        break;
    case 20:
        a[3] = c | 0x80;
        d = &D_8010D8AC[c];
        break;
    case 21:
        a[3] = c | 0x80;
        d = &D_8011FC0C[c];
        break;
    case 22:
        a[3] = c | 0x80;
        d = &D_801158A0[c];
        break;
    }
    a[0xB] = 0x20;
    *(void **)(a + 0x1C) = d->p0;
    *(void **)(a + 0x18) = d->p4;
    if (d->p8 != NULL) {
        *(u16 *)(a + 0x44) = d->p8[0];
        *(u16 *)(a + 0x46) = d->p8[1];
        *(u16 **)(a + 0x38) = d->p8 + 2;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_8002918C);

extern u8 D_800A1D88[];
extern u8 D_800A1D68[];
extern u8 D_800A1D78[];
extern u8 D_800A1CD8[];
extern u8 D_800A1E78[];
extern u8 D_800A1E28[];
extern u8 D_800A1E50[];
extern u8 D_800A1D98[];
void func_80027E5C();
void func_800288AC();
void func_80031780(u8 *p);
void func_80031708(void *arg0);
void func_800292B8(u8 *a)
{
    switch (a[4]) {
    case 0:
        if (a[6] == 0x20) {
            *(u8 **)(a + 0x40) = D_800A1D88;
        } else if (a[6] == 0x10) {
            *(u8 **)(a + 0x40) = D_800A1D68;
        } else {
            *(u8 **)(a + 0x40) = D_800A1D78;
        }
        *(u8 **)(a + 0x50) = D_800A1CD8;
        a[4] = 1;
        a[0x29] = 0;
    case 1:
        if ((*(s32 *)(a + 0x34) = *(s32 *)(a + 0x38)) == 0) {
            if (*(void **)(a + 0x18) == func_80027E5C) {
                a[4] = 2;
                break;
            }
            *(void **)(a + 0x18) = func_800288AC;
        }
        if ((*(s32 *)(a + 0x3C) = *(s32 *)(a + 0x40)) == 0) {
            if (*(void **)(a + 0x18) == func_800288AC) {
                a[4] = 2;
                break;
            }
            *(void **)(a + 0x18) = func_80027E5C;
        }
        if (func_8002B278(a) == 0) {
            func_80031780(a);
            func_80031708(a);
        }
        break;
    case 2:
    case 3:
        f_ResolveEffectEightByteStreamPayload(a);
        break;
    }
}

void func_800293F4(u8 *a)
{
    switch (a[4]) {
    case 0:
        if (a[6] == 0x20) {
            *(u8 **)(a + 0x40) = D_800A1E78;
        } else if (a[6] == 0x10) {
            *(u8 **)(a + 0x40) = D_800A1E28;
        } else {
            *(u8 **)(a + 0x40) = D_800A1E50;
        }
        *(u8 **)(a + 0x50) = D_800A1D98;
        a[4] = 1;
        a[0x29] = 0;
    case 1:
        if ((*(s32 *)(a + 0x34) = *(s32 *)(a + 0x38)) == 0) {
            if (*(void **)(a + 0x18) == func_80027E5C) {
                a[4] = 2;
                break;
            }
            *(void **)(a + 0x18) = func_800288AC;
        }
        if ((*(s32 *)(a + 0x3C) = *(s32 *)(a + 0x40)) == 0) {
            if (*(void **)(a + 0x18) == func_800288AC) {
                a[4] = 2;
                break;
            }
            *(void **)(a + 0x18) = func_80027E5C;
        }
        if (func_8002B278(a) == 0) {
            func_80031780(a);
            func_80031708(a);
        }
        break;
    case 2:
    case 3:
        f_ResolveEffectEightByteStreamPayload(a);
        break;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_80029530);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80029664);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80029B40);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80029F6C);

extern int rand(void);
s32 f_ResolveEffectEightByteStreamPayload();
void func_8002A584(u8 *a)
{
    u8 *q = a + 0x50;
    u8 *def = *(u8 **)(a + 0x10);
    u8 *t;
    u8 *e;
    s32 i;
    s32 z;
    s32 dy;

    switch (a[4]) {
    case 0:
        for (i = 0; i < 10; i++) {
            q[i * 4 + 0] = rand();
            q[i * 4 + 1] = rand();
            q[i * 4 + 2] = 0;
            q[i * 4 + 3] = rand() & 0x1F;
        }
        a[4] = 1;
        if (def[2] < 4) {
            a[5] = 2;
        } else if (def[2] < 7) {
            a[5] = 0;
        } else {
            a[5] = 1;
        }
    case 1:
        t = (u8 *)D_800E7E80;
        if ((t[0x146] & 4) || t[0x146] == 0 || def[4] >= 2 || def[0] == 1) {
            a[4] = 2;
            break;
        }
        e = *(u8 **)(t + 0xC0) + 0x18;
        if (a[5] == 1) {
            if (t[0x164] != 0) {
                dy = -0xA0;
                *(u16 *)(a + 0x2C) = *(u16 *)(e + 0x14) + ((*(s16 *)(e + 4) * dy) >> 12);
                z = *(s16 *)(e + 0x10) * dy;
                dy = -0x38;
            } else {
                dy = -0xB4;
                *(u16 *)(a + 0x2C) = *(u16 *)(e + 0x14) + ((*(s16 *)(e + 0) * dy) >> 12);
                z = *(s16 *)(e + 0xC) * dy;
                dy = -0x10;
            }
        } else {
            dy = -0x64;
            *(u16 *)(a + 0x2C) = *(u16 *)(e + 0x14) + ((*(s16 *)(e + 4) * dy) >> 12);
            z = *(s16 *)(e + 0x10) * dy;
            dy = -0xC;
        }
        {
            u16 h = *(u16 *)(e + 0x1C);
            __asm__ volatile("");
            *(u16 *)(a + 0x30) = h + (z >> 12);
        }
        *(u16 *)(a + 0x2E) = *(u16 *)(e + 0x18) + dy;
        for (i = 0; i < 10; i++) {
            if ((s8)(q[i * 4 + 3] -= 3) <= 0) {
                if (a[6] == 2) {
                    q[i * 4 + 3] = (rand() & 0xF) + 0x20;
                } else {
                    q[i * 4 + 3] = (rand() & 0xF) + 0x13;
                }
                q[i * 4 + 0] = rand();
                q[i * 4 + 1] = rand();
            }
        }
        a[1] = 1;
        break;
    case 2:
    case 3:
        f_ResolveEffectEightByteStreamPayload(a);
        break;
    }
}

extern u8 D_800A1FC4[];
extern u8 D_8009FB0C[];
/* f_SetEffectRenderTransform, inlined */
static inline void SetRT_C138(void *pos, u8 *scale, s16 *rot)
{
    s32 v[3];

    RotMatrix_gte(rot, D_1F800000);
    v[0] = scale[0] * 4;
    v[1] = scale[1] * 4;
    v[2] = scale[2] * 4;
    ScaleMatrix(D_1F800000, v);
    gte_SetRotMatrix(D_1F8000F8);
    gte_ldclmv(D_1F800000);
    gte_rtir();
    gte_stclmv(D_1F800000);
    gte_ldclmv(D_1F800002);
    gte_rtir();
    gte_stclmv(D_1F800002);
    gte_ldclmv(D_1F800004);
    gte_rtir();
    gte_stclmv(D_1F800004);
    gte_ldv0(pos);
    gte_rtv0();
    gte_stlvnl(D_1F800014);
    D_1F800000[5] += D_1F8000D0_42d8[15];
    D_1F800000[6] += D_1F8000D0_42d8[16];
    D_1F800000[7] += D_1F8000D0_42d8[17];
    gte_SetRotMatrix(D_1F800000);
    gte_SetTransMatrix(D_1F800000);
}
void func_8002A834(u8 *a0)
{
    u8 *a = a0;
    s32 *z = (s32 *)D_1F800090;
    u8 *pp = a + 0x50;
    s16 rot[4];
    u8 sc[4];
    u8 *c;
    u8 *p;
    s32 i;

    c = &D_800A1FC4[(*(u8 **)(a + 0x10))[2] * 4];
    gte_ldfcdir(c[0] << 4, c[1] << 4, c[2] << 4);
    rot[0] = *(u16 *)(a + 0x48);
    rot[1] = *(u16 *)(a + 0x4A);
    rot[2] = *(u16 *)(a + 0x4C);
    *z = 0xFFF;
    for (i = 0; i < 10; i++) {
        sc[0] = sc[1] = sc[2] = pp[i * 4 + 3];
        rot[0] = pp[i * 4 + 0] << 4;
        rot[1] = pp[i * 4 + 1] << 4;
        rot[2] = pp[i * 4 + 2] << 4;
        SetRT_C138(a + 0x2C, sc, rot);
        f_DrawPackedGouraudQuadStream(D_8009FB0C, 0, *(s16 *)(a + 0x32), 0);
    }
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_8002AB5C);

extern u8 D_8009FAE8[];
extern u8 D_800A1CCC[];
extern s8 D_1F800094[];
void func_8002AE0C(u8 *a, s32 s, s32 mode)
{
    s32 *z = (s32 *)D_1F800090;
    u8 *sc = (u8 *)D_1F800094;
    s16 pos[4];
    s32 k;
    u8 m;

    gte_ldfcdir(0, 0, 0);
    sc[1] = 0x10;
    if (mode == 0) {
        pos[0] = *(u16 *)(a + 0x2E);
        pos[1] = *(u16 *)(a + 0x32) + *(u16 *)(a + 0x86) - *(u16 *)(a + 0x84);
        pos[2] = *(u16 *)(a + 0x36);
        sc[2] = sc[0] = s >> 3;
        SetRT_C138(pos, sc, (s16 *)(a + 0x54));
    } else {
        sc[0] = sc[2] = s >> 3;
        SetRT_C138(a, sc, (s16 *)D_800A1CCC);
    }
    m = D_800BF870.unk0;
    if (m == 1 || m == 2) {
        *z = 0x800;
        k = -10;
    } else if (m == 7) {
        *z = 0x400;
        k = -3;
    } else {
        *z = 0;
        k = -10;
    }
    f_DrawPackedGouraudQuadStream(D_8009FAE8, 0, k, 0);
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_8002B278);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8002B3A4);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8002B7B0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8002B8F4);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8002BAFC);

#define gte_ldv0_58(r0) __asm__ volatile("lwc2 $0, 0x58(%0); lwc2 $1, 0x5C(%0)" : : "r"(r0))
void func_8002BC9C(u8 *a)
{
    s32 *otz = (s32 *)D_1F800084;
    s32 *o2 = &D_1F800088;
    u8 *p;
    u8 *m;
    s32 b;
    s32 i;
    s32 d;

    *(s32 *)D_1F800090 = 0;
    p = *(u8 **)(a + 0x3C);
    if (p != NULL) {
        b = p[0];
        if (b & 0x80) {
            *(s32 *)(a + 0x40) = 0;
            b &= 0x7F;
        } else {
            *(u8 **)(a + 0x40) = p + 1;
        }
        m = (*(u8 ***)(a + 0x50))[b];
        gte_ldfcdir(0, 0, 0);
        for (i = 0; i < 4; i++) {
            SetRT_C138(a + 0x2C, D_800A1CD4, (s16 *)(a + 0x48));
            f_DrawPackedGouraudQuadStream(m, 0, *(s16 *)(a + 0x32), 0);
            *(u16 *)(a + 0x4A) += 0x400;
        }
    }
    if ((u32)(a[3] - 0x14) < 2) {
        d = *(s32 *)(a + 0x34);
        if (d == 0) {
            return;
        }
        SetProj_7CB4(6);
        gte_ldv0_58(a);
        if (ProjZ(a)) {
            func_80031780(a);
            return;
        }
        {
            s32 k = (*(u16 *)(a + 0x46) << 16) | *(u16 *)(a + 0x44);

            *o2 = *otz;
            *(s32 *)(a + 0x38) = f_DrawProjectedSpriteDefinitionStream(d, k);
        }
    }
}

void func_8002C138(u8 *a)
{
    s16 rot[4];
    s16 pos[4];
    u8 *sc;
    s16 r = 0;

    sc = D_800A203C + (*(s16 *)(a + 0x60) >> 1) * 5;
    rot[0] = 0;
    rot[1] = *(u16 *)(a + 0x56);
    if (*(u16 *)(a + 0x60) & 1) {
        r = 0xAA;
    }
    rot[2] = r;
    pos[0] = *(u16 *)(a + 0x2E);
    pos[1] = *(u16 *)(a + 0x32);
    pos[2] = *(u16 *)(a + 0x36);
    gte_ldfcdir(0, 0, 0);
    *(s32 *)D_1F800090 = 0;
    SetRT_C138(pos, sc, rot);
    f_DrawPackedGouraudQuadStream(D_8009F05C, sc[3], -10, sc[4]);
}

extern u8 D_800A0700[];
extern u8 D_800A06DC[];
extern u8 D_800A06B8[];
extern u8 D_800A0694[];
void func_8002C3EC(u8 *a)
{
    switch (a[4]) {
    case 0:
        *(u16 *)(a + 0x4C) += rand();
        *(s32 *)(a + 4) = 1;
        *(s32 *)(a + 0x50) = 0x101010;
        *(s32 *)(a + 0x58) = 0;
    case 1:
        if (a[7] > 0x10) {
            a[4] = 2;
            break;
        }
        *(s32 *)(a + 0x34) = *(s32 *)(a + 0x38);
        switch (a[7]) {
        case 0:
            *(u8 **)(a + 0x54) = D_800A0700;
            break;
        case 1:
            *(u8 **)(a + 0x54) = D_800A06DC;
            break;
        case 2:
            *(u8 **)(a + 0x54) = D_800A06B8;
            break;
        case 3:
            *(u8 **)(a + 0x54) = D_800A0694;
            break;
        case 4:
            *(s32 *)(a + 0x58) = 1;
            break;
        case 5:
            *(s32 *)(a + 0x58) = 2;
            break;
        default:
            *(u8 **)(a + 0x54) = NULL;
            break;
        }
        func_8002B278(a);
        a[7]++;
        break;
    case 2: case 3:
        f_ResolveEffectEightByteStreamPayload(a);
        break;
    }
}

void func_8002C548(u8 *a)
{
    switch (a[4]) {
    case 0:
        *(u16 *)(a + 0x4C) += rand();
        *(s32 *)(a + 4) = 1;
        *(s32 *)(a + 0x50) = 0x101010;
        *(s32 *)(a + 0x58) = 0;
    case 1:
        if (a[7] > 0x10) {
            a[4] = 2;
            break;
        }
        *(s32 *)(a + 0x34) = *(s32 *)(a + 0x38);
        switch (a[7]) {
        case 0:
            *(u8 **)(a + 0x54) = D_800A0700;
            *(s32 *)(a + 0x58) = 3;
            break;
        case 1:
            *(u8 **)(a + 0x54) = D_800A06DC;
            break;
        case 2:
            *(u8 **)(a + 0x54) = D_800A06B8;
            break;
        case 3:
            *(u8 **)(a + 0x54) = D_800A0694;
            break;
        case 4:
            *(s32 *)(a + 0x58) = 4;
            break;
        case 5:
            *(s32 *)(a + 0x58) = 5;
            break;
        default:
            *(u8 **)(a + 0x54) = NULL;
            break;
        }
        func_8002B278(a);
        a[7]++;
        break;
    case 2: case 3:
        f_ResolveEffectEightByteStreamPayload(a);
        break;
    }
}

void func_8002C6AC(u8 *a)
{
    func_80027CB4(a);
    if (*(s32 *)(a + 0x54) != 0) {
        *(s32 *)D_1F800090 = 0;
        gte_ldfcdir(0, 0, 0);
        SetRT_C138(a + 0x2C, a + 0x50, (s16 *)(a + 0x48));
        f_DrawPackedGouraudQuadStream(*(s32 *)(a + 0x54), *(s32 *)(a + 0x58), -10, 0);
    }
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_8002C920);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8002CD18);

extern s32 D_800A2064;
extern u8 D_800A172C[];
typedef struct { u8 b[4]; } B4_D65C;
extern B4_D65C D_800102B4;
/* sprite depth projection without height bias, inlined */
static inline s32 ProjZ2(void)
{
    s32 *flag = &D_1F800080;
    s32 *otz = (s32 *)D_1F800084;
    s32 *sxy = (s32 *)D_1F80008C;
    s32 e;

    gte_rtps();
    gte_stflg(flag);
    if (*flag < 0) {
        return 1;
    }
    gte_stsz(flag);
    if (*flag <= 0) {
        return 1;
    }
    *flag = *flag >> 2;
    if (*flag < 4) {
        *flag = 4;
    }
    e = *flag >> 10;
    *flag = (*flag >> e) + (e << 9);
    if ((u32)(*flag - 4) >= 0x7FC) {
        *flag = -1;
    }
    if (*flag < 0) {
        return 1;
    }
    gte_stsxy(sxy);
    gte_stopz(otz);
    return 0;
}
void func_8002D65C(u8 *a0)
{
    u8 *a = a0;
    s32 *o2 = &D_1F800088;
    s32 *otz = &D_1F800084_8c7c;
    s16 pos[4];
    B4_D65C sc;
    s16 rot[4];
    s16 p2[4];
    s32 d;
    s32 r;
    s32 ang;
    s32 i;
    s32 j;
    s32 y;

    r = 0;
    ang = 0;
    d = *(s32 *)(a + 0x34);
    if (d == 0) {
        return;
    }
    SetProj_7CB4(6);
    *(s32 *)D_1F800090 = 0;
    gte_ldfcdir(0, 0, 0);
    for (i = 0; i < 8; i++) {
        pos[0] = *(u16 *)(a + 0x2C) + ((rcos(ang) * 1200) >> 12);
        pos[2] = *(u16 *)(a + 0x30) + ((rsin(ang) * 1200) >> 12);
        y = *(u16 *)(a + 0x2E) + *(u16 *)(a + 0x4E);
        pos[1] = y - 0xC00;
        if (i >= 4) {
            pos[1] = y - 0xA80;
        }
        for (j = 0; j < 8; j++) {
            gte_ldv0(pos);
            if (ProjZ2() == 0) {
                u16 hi = *(u16 *)(a + 0x46);
                s32 z = *otz;
                s32 k = (hi << 16) | *(u16 *)(a + 0x44);

                *o2 = z;
                *otz -= *otz >> 2;
                r = f_DrawProjectedSpriteDefinitionStream(d, k);
            }
            pos[1] += 0x300;
        }
        j = 3;
        if (i == j) {
            ang += 0x200;
        }
        ang += 0x400;
    }
    *(s32 *)(a + 0x38) = r;
    {
    s32 *z = (s32 *)D_1F800090;

    sc = D_800102B4;
    memset(rot, 0, 8);
    p2[1] = *(u16 *)(a + 0x2E);
    p2[0] = *(u16 *)(a + 0x2C);
    p2[2] = *(u16 *)(a + 0x30);
    SetRT_C138(p2, sc.b, rot);
    *z = 0;
    if (D_1F800236_18be == j) {
        D_800A2064 -= 6;
    } else {
        D_800A2064 += 6;
    }
    D_800A2064 &= 0x3F;
    gte_ldfcdir(0, 0, 0);
    f_DrawPackedGouraudQuadStream(D_800A172C, 0, 0, (s16)D_800A2064);
    }
}

void func_8002DBE4(u8 *a)
{
    s32 *flag = &D_1F800080;
    s32 *otz = (s32 *)D_1F800084;
    s32 *o2 = &D_1F800088;
    s32 *z = (s32 *)D_1F800090;
    s32 d = *(s32 *)(a + 0x34);

    if (d == 0) {
        return;
    }
    SetProj_7CB4(6);
    gte_ldv0_2C(a);
    if (ProjZ(a) == 0) {
        u16 hi;
        *o2 = *otz;
        hi = *(u16 *)(a + 0x46);
        *z = a[7] << 4;
        *(s32 *)(a + 0x38) = f_DrawProjectedSpriteDefinitionStream(d, (hi << 16) | *(u16 *)(a + 0x44));
    }
}

void func_8002DD88(u8 *a)
{
    s32 *flag = &D_1F800080;
    s32 *otz = (s32 *)D_1F800084;
    s32 *o2 = &D_1F800088;
    s32 *sxy = (s32 *)D_1F80008C;
    s32 *z = (s32 *)D_1F800090;
    s32 d = *(s32 *)(a + 0x34);

    SetProj_7CB4(6);
    gte_ldv0_2C(a);
    if (ProjZ(a) == 0) {
        u32 x, y;
        u16 hi;

        gte_ldfcdir(0, 0, 0);
        x = *otz * *(u32 *)(a + 0x58);
        y = *otz * *(u32 *)(a + 0x54);
        *z = *(s32 *)(a + 0x50);
        *o2 = x >> 8;
        hi = *(u16 *)(a + 0x46);
        *otz = y >> 8;
        *(s32 *)(a + 0x38) = f_DrawProjectedSpriteDefinitionStream(d, (hi << 16) | *(u16 *)(a + 0x44));
    }
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_8002DF68);

#define W(p, o) (*(u32 *)((p) + (o)))
typedef struct {
    u8 b[6][4];
} FlickerTbl_E1E8;
extern FlickerTbl_E1E8 D_800102BC;
extern s32 D_1F800160_faaf;
s32 f_ResolveEffectEightByteStreamPayload();
void func_8002E1E8(u8 *a)
{
    FlickerTbl_E1E8 t = D_800102BC;

    switch (a[4]) {
    case 0:
        a[4] = 1;
        W(a, 0x64) = 0x400;
        W(a, 0x6C) = 0x200;
        W(a, 0x60) = 0;
        W(a, 0x68) = 0;
        *(s16 *)(a + 0x32) = -200;
    case 1:
    case 2:
        if (a[4] == 1) {
            W(a, 0x60) += (0x200 - W(a, 0x60)) >> 5;
            W(a, 0x68) += (0x400 - W(a, 0x68)) >> 5;
        } else {
            W(a, 0x64) -= W(a, 0x64) >> 2;
            W(a, 0x68) += W(a, 0x68) >> 4;
            W(a, 0x6C) -= W(a, 0x6C) >> 2;
            if (W(a, 0x6C) < 9) {
                a[4] = 3;
            }
        }
        if (++a[7] >= 6) {
            a[7] = 0;
        }
        W(a, 0x50) = (W(a, 0x60) * t.b[a[7]][0]) >> 4;
        W(a, 0x54) = (W(a, 0x64) * t.b[a[7]][1]) >> 4;
        W(a, 0x58) = (W(a, 0x68) * t.b[a[7]][2]) >> 4;
        {
            u32 k = W(a, 0x6C) * t.b[a[7]][3];

            *(s32 *)(a + 0x2C) = D_1F800160_faaf;
            *(u16 *)(a + 0x30) = D_1F800164;
            a[1] = 1;
            W(a, 0x5C) = k >> 4;
        }
        break;
    case 3:
        f_ResolveEffectEightByteStreamPayload(a);
        break;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_8002E458);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8002E680);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8002ECD8);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8002EF58);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8002F230);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8002F36C);

extern u8 D_800E7E7C;
void func_8002F514(s32 kind, s32 owner)
{
    u8 *e;
    u8 *t;
    s16 pos[3];
    s16 *pp;

    switch (kind) {
    case 2:
        e = NULL;
        func_80023528(owner);
        break;
    case 3:
        if (D_800E7E7C < 7 || (t = f_AllocateActorRecordByType(0, 6, 1)) == NULL) {
            e = NULL;
        } else {
            *(s16 *)(t + 0x32) = -0xC8;
            f_InitializeTransientEffectActor(t, 0x32);
            e = t;
        }
        break;
    case 4:
        if (D_800E7E7C < 7 || (t = f_AllocateActorRecordByType(0, 6, 1)) == NULL) {
            e = NULL;
        } else {
            *(s16 *)(t + 0x32) = -0xC8;
            f_InitializeTransientEffectActor(t, 0x33);
            e = t;
        }
        break;
    case 1:
        if (D_800E7E7C < 7 || (t = f_AllocateActorRecordByType(0, 6, 1)) == NULL) {
            e = NULL;
        } else {
            *(s16 *)(t + 0x32) = -0xC8;
            f_InitializeTransientEffectActor(t, 0x2A);
            e = t;
        }
        break;
    case 5:
        if (D_800E7E7C < 7 || (t = f_AllocateActorRecordByType(0, 6, 1)) == NULL) {
            e = NULL;
        } else {
            *(s16 *)(t + 0x32) = -0xC8;
            f_InitializeTransientEffectActor(t, 0x31);
            e = t;
        }
        break;
    case 6:
    default:
        pos[0] = D_1F800160;
        pos[1] = D_1F800162 - 0xC8;
        pos[2] = D_1F800164;
        pp = pos;
        if (D_800E7E7C < 7 || (t = f_AllocateActorRecordByType(0, 6, 1)) == NULL) {
            e = NULL;
        } else {
            if (pp != NULL) {
                *(u16 *)(t + 0x2C) = pp[0];
                *(u16 *)(t + 0x2E) = pp[1];
                *(u16 *)(t + 0x30) = pp[2];
            }
            *(s16 *)(t + 0x32) = -0xC8;
            f_InitializeTransientEffectActor(t, 0x36);
            e = t;
        }
        break;
    }
    if (owner != 0 && e != NULL) {
        *(s32 *)(e + 0x10) = owner;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_8002F738);

extern s8 D_1F800088_f8dc[];
extern s16 D_1F800160_f8dc;
extern s16 D_1F800162_f8dc;
extern s16 D_1F800164_f8dc;
extern s32 D_8009EB7C[];
/* sprite depth projection with a -0x14 depth bias, inlined */
static inline s32 ProjZ_F8DC(void)
{
    s32 *flag = &D_1F800080;
    s32 *otz = (s32 *)D_1F800084;
    s32 *sxy = (s32 *)D_1F80008C;
    s32 e;

    gte_rtps();
    gte_stflg(flag);
    if (*flag < 0) {
        return 1;
    }
    gte_stsz(flag);
    if (*flag <= 0) {
        return 1;
    }
    *flag = (*flag >> 2) - 0x14;
    if (*flag < 4) {
        *flag = 4;
    }
    e = *flag >> 10;
    *flag = (*flag >> e) + (e << 9);
    if ((u32)(*flag - 4) >= 0x7FC) {
        *flag = -1;
    }
    if (*flag < 0) {
        return 1;
    }
    gte_stsxy(sxy);
    gte_stopz(otz);
    return 0;
}
void func_8002F8DC(u8 *a0)
{
    u8 *a = a0;
    s32 *otz = (s32 *)D_1F800084;
    s32 *o2 = (s32 *)D_1F800088_f8dc;
    s32 *z = (s32 *)D_1F800090;
    s16 pts[5][4];
    s32 col[5];
    u8 sz[8];
    s32 d0;
    s32 d1;
    s32 d2;
    s32 i;
    u8 *ps;
    s32 *pc;
    s16 *pos;
    s32 k;
    s32 m;
    s16 *p;

    i = 0;
    ps = sz;
    pc = col;
    pos = (s16 *)(a + 0x2C);
    k = a[7];
    d0 = D_1F800160_f8dc - *(s16 *)(a + 0x2C);
    d1 = D_1F800162_f8dc - pos[1];
    d2 = D_1F800164_f8dc - pos[2];
    do {
        if (i == 0 || i == 4) {
            *pc = 0;
            *ps = 0;
        } else {
            *pc = 0x9850E0;
            *ps = (5 - i) * 2;
        }
        m = 0;
        if (k >= 0) {
            m = k;
            if (k > 0x80) {
                m = 0x80;
            }
        }
        p = pts[i];
        p[0] = pos[0] + ((d0 * m) >> 7);
        p[1] = pos[1] + ((d1 * m) >> 7) - ((rsin(m * 16) * pos[3]) >> 12);
        p[2] = pos[2] + ((d2 * m) >> 7);
        ps++;
        pc++;
        i++;
        k -= 0xD;
    } while (i < 5);
    func_80029664(pts, 5, col, sz);
    if (a[7] <= 0x80) {
        SetProj_7CB4(6);
        gte_ldv0(pts);
        if (ProjZ_F8DC() == 0) {
            {
                s32 r = rand() & 0x7FF;
                s32 h = (a[6] << 7) - 0x3FF;
                *z = r + h;
            }
            *otz = (*otz * (a[6] + 0x10)) >> 4;
            *o2 = *otz;
            f_DrawProjectedSpriteDefinitionStream(D_8009EB7C, D_8009EB7C[-1]);
        }
    }
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_8002FC40);

extern u8 D_8009F3E0[];
typedef struct { u8 b[4]; } B4_FDD0;
extern B4_FDD0 D_800102EC;
void func_8002FDD0(u8 *a)
{
    s16 pos[4];
    B4_FDD0 sc;
    s32 y = *(s16 *)(a + 0x50);
    s16 *p = (s16 *)(a + 0x50);
    s32 k;
    s32 i;

    sc = D_800102EC;
    if (y < 0) {
        y = 0;
    }
    k = p[1];
    pos[0] = *(u16 *)(a + 0x2C);
    pos[2] = *(u16 *)(a + 0x30);
    pos[1] = *(u16 *)(a + 0x2E) - y * 10;
    gte_ldfcdir(0x1E0, 0x3C0, 0x640);
    {
        s32 c = 0x1000;

        *(s32 *)D_1F800090 = c;
    }
    for (i = 0; i < 4; i++) {
        SetRT_C138(pos, sc.b, (s16 *)(a + 0x48));
        f_DrawPackedGouraudQuadStream(D_8009F3E0, 0, *(s16 *)(a + 0x32), k);
        *(u16 *)(a + 0x4A) += 0x400;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_800300D8);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80030264);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800308C0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80030A3C);

extern s32 D_1F800020_edd9[];
void f_SetIdentityMatrix(s32 *m);
typedef struct { u8 b[12]; } B12_0D68;
typedef struct { u8 b[9]; } B9_0D68;
extern B12_0D68 D_800102F0;
extern B9_0D68 D_800102FC;
/* func_80031D24, inlined */
static inline void SetRTY_1D24(void *pos, u8 *scale, s16 *rot)
{
    s32 v[3];

    RotMatrix_gte(rot, D_1F800000);
    f_SetIdentityMatrix(D_1F800020_edd9);
    RotMatrixY(rot[3], D_1F800020_edd9);
    MulMatrix(D_1F800000, D_1F800020_edd9);
    v[0] = scale[0] * 4;
    v[1] = scale[1] * 4;
    v[2] = scale[2] * 4;
    ScaleMatrix(D_1F800000, v);
    gte_SetRotMatrix(D_1F8000F8);
    gte_ldclmv(D_1F800000);
    gte_rtir();
    gte_stclmv(D_1F800000);
    gte_ldclmv(D_1F800002);
    gte_rtir();
    gte_stclmv(D_1F800002);
    gte_ldclmv(D_1F800004);
    gte_rtir();
    gte_stclmv(D_1F800004);
    gte_ldv0(pos);
    gte_rtv0();
    gte_stlvnl(D_1F800014);
    D_1F800000[5] += D_1F8000D0_42d8[15];
    D_1F800000[6] += D_1F8000D0_42d8[16];
    D_1F800000[7] += D_1F8000D0_42d8[17];
    gte_SetRotMatrix(D_1F800000);
    gte_SetTransMatrix(D_1F800000);
}
void func_80030D68(u8 *a0)
{
    u8 *a = a0;
    B12_0D68 sc;
    B9_0D68 col;
    s32 *z = (s32 *)D_1F800090;
    u8 k;
    u8 *c;
    s32 i;
    s32 d;

    k = a[5] >> 1;
    sc = D_800102F0;
    col = D_800102FC;
    c = &col.b[k * 3];
    gte_ldfcdir(c[0] << 4, c[1] << 4, c[2] << 4);
    d = k << 5;
    *z = 0xFFF;
    for (i = 0; i < 4; i++) {
        SetRTY_1D24(a + 0x2C, &sc.b[k * 4], (s16 *)(a + 0x48));
        f_DrawPackedGouraudQuadStream(D_8009F3E0, 0, 0, d);
        *(u16 *)(a + 0x4E) += 0x400;
    }
}

s32 f_SpawnTransientEffect(s32 arg0, s32 arg1) {
    s32 temp_v0;

    if ((u8) D_800E7E7C >= 7U) {
        temp_v0 = f_AllocateActorRecordByType(0, 6, 1);
        if (temp_v0 != 0) {
            M2C_FIELD(temp_v0, s16 *, 0x32) = (s16) arg1;
            f_InitializeTransientEffectActor(temp_v0, arg0);
            return temp_v0;
        }
    }
    return 0;
}

extern u8 D_800E7E7C;
s32 f_SpawnTransientEffectAtFixedPosition(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_v0;

    if (((u8) D_800E7E7C < 7U) || (temp_v0 = f_AllocateActorRecordByType(0, 6, 1), (temp_v0 == 0))) {
        return 0;
    }
    if (arg1 != 0) {
        M2C_FIELD(temp_v0, u16 *, 0x2C) = (u16) M2C_FIELD(arg1, u16 *, 2);
        M2C_FIELD(temp_v0, u16 *, 0x2E) = (u16) M2C_FIELD(arg1, u16 *, 6);
        M2C_FIELD(temp_v0, u16 *, 0x30) = (u16) M2C_FIELD(arg1, u16 *, 0xA);
    }
    M2C_FIELD(temp_v0, s16 *, 0x32) = (s16) arg2;
    f_InitializeTransientEffectActor(temp_v0, arg0);
    return temp_v0;
}

extern u8 D_800E7E7C;
s32 f_SpawnTransientEffectAtShortPosition(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_v0;

    if (((u8) D_800E7E7C < 7U) || (temp_v0 = f_AllocateActorRecordByType(0, 6, 1), (temp_v0 == 0))) {
        return 0;
    }
    if (arg1 != 0) {
        M2C_FIELD(temp_v0, u16 *, 0x2C) = (u16) M2C_FIELD(arg1, u16 *, 0);
        M2C_FIELD(temp_v0, u16 *, 0x2E) = (u16) M2C_FIELD(arg1, u16 *, 2);
        M2C_FIELD(temp_v0, u16 *, 0x30) = (u16) M2C_FIELD(arg1, u16 *, 4);
    }
    M2C_FIELD(temp_v0, s16 *, 0x32) = (s16) arg2;
    f_InitializeTransientEffectActor(temp_v0, arg0);
    return temp_v0;
}

u8 *f_SpawnFlaggedTransientEffectAtFixedPosition(s32 id, u8 *pos, s16 y)
{
    u8 *e;
    u8 *t;

    if (D_800E7E7C < 7) {
        e = NULL;
        goto done;
    }
    t = (u8 *)f_AllocateActorRecordByType(0, 6, 1);
    if (t == NULL) {
        e = NULL;
        goto done;
    }
    {
        if (pos != NULL) {
            *(u16 *)(t + 0x2C) = *(u16 *)(pos + 2);
            *(u16 *)(t + 0x2E) = *(u16 *)(pos + 6);
            *(u16 *)(t + 0x30) = *(u16 *)(pos + 0xA);
        }
        *(s16 *)(t + 0x32) = y;
        f_InitializeTransientEffectActor(t, id);
        e = t;
    }
done:
    if (e != NULL) {
        e[0x28] |= 0x80;
    }
    return e;
}

u8 *f_SpawnMovingTransientEffectAtFixedPosition(s32 id, u8 *pos, s16 y, u16 *vel)
{
    u8 *t;

    if (D_800E7E7C >= 7 && (t = (u8 *)f_AllocateActorRecordByType(0, 6, 1)) != NULL) {
    *(u16 *)(t + 0x2C) = *(u16 *)(pos + 2);
    *(u16 *)(t + 0x2E) = *(u16 *)(pos + 6);
    *(u16 *)(t + 0x30) = *(u16 *)(pos + 0xA);
    *(s16 *)(t + 0x32) = y;
    *(u16 *)(t + 0x48) = vel[0];
    *(u16 *)(t + 0x4A) = vel[1];
    *(u16 *)(t + 0x4C) = vel[2];
    f_InitializeTransientEffectActor(t, id);
    return t;
    }
    return NULL;
}

s32 f_AllocateActorRecordByType(u8 type, u8 b, s32 c);
s32 f_SpawnImpactTransientEffect(s32 kind, u8 *pos, s16 flag, u16 *rot)
{
    s32 e;

    if (D_800E7E7C < 7U || (e = f_AllocateActorRecordByType(0, 6, 1)) == 0) {
        return 0;
    }
    M2C_FIELD(e, u16 *, 0x2C) = *(u16 *)(pos + 2);
    M2C_FIELD(e, u16 *, 0x2E) = *(u16 *)(pos + 6);
    M2C_FIELD(e, u16 *, 0x30) = *(u16 *)(pos + 0xA);
    M2C_FIELD(e, s16 *, 0x32) = -0x50;
    M2C_FIELD(e, s16 *, 0x48) = 0;
    M2C_FIELD(e, u16 *, 0x4A) = rot[0];
    M2C_FIELD(e, u16 *, 0x4C) = rot[1];
    M2C_FIELD(e, u8 *, 0x28) |= 0x80;
    f_InitializeTransientEffectActor(e, kind);
    M2C_FIELD(e, u8 *, 6) = flag ? 0x18 : 0x10;
    return e;
}

extern u8 D_800E7E80_f78d[];
typedef struct { u8 pad[0xC0]; u8 *parts[64]; } PartOwner;
extern PartOwner *D_1F800214_50e7;
void func_80059ED8(u8 *);
void func_8002AB5C(u8 *);
void func_80029B40(u8 *);
void func_80029F6C(u8 *);
u8 *f_SpawnLinkedActorTrailEffect(u8 *owner, u8 kind)
{
    u8 *a = f_AllocateActorRecordByType(0, 6, 1);

    if (a == 0) {
        return 0;
    }
    *(void **)(a + 0x1C) = func_80029B40;
    a[0xB] = 0x20;
    *(u8 **)(a + 0x10) = owner;
    *(void **)(a + 0x18) = func_80029F6C;
    a[3] = kind;
    a[0x28] |= 0x80;
    return a;
}

/* f_SpawnTransientEffectAtFixedPosition, inlined */
static inline u8 *SpawnFixed_15D4(s32 id, u8 *pos, s16 y)
{
    u8 *t;

    if (D_800E7E7C < 7) {
        return NULL;
    }
    t = (u8 *)f_AllocateActorRecordByType(0, 6, 1);
    if (t == NULL) {
        return NULL;
    }
    if (pos != NULL) {
        *(u16 *)(t + 0x2C) = *(u16 *)(pos + 2);
        *(u16 *)(t + 0x2E) = *(u16 *)(pos + 6);
        *(u16 *)(t + 0x30) = *(u16 *)(pos + 0xA);
    }
    *(s16 *)(t + 0x32) = y;
    f_InitializeTransientEffectActor(t, id);
    return t;
}
void f_SpawnActorImpactEffectPair(u8 *pos)
{
    u8 *e;

    e = SpawnFixed_15D4(9, pos, -0x14);
    if (e != NULL) {
        *(s32 *)(e + 0x48) = 0x1000100;
    }
    e = SpawnFixed_15D4(5, pos, -0x19);
    if (e != NULL) {
        *(s32 *)(e + 0x48) = 0x1000100;
    }
}

void func_80031708(void *arg0)
{
  void **new_var;
  void *new_var2;
  void *temp_v1;
  new_var2 = arg0;
  temp_v1 = *((void **) (((signed char *) new_var2) + 0x3C));
  if (temp_v1 != 0)
  {
    if ((*((u8 *) (((signed char *) temp_v1) + 3))) & 0x80)
    {
      *((void **) (((signed char *) new_var2) + 0x40)) = 0;
      ;
      *((void **) (((signed char *) new_var2) + 0x3C)) = 0;
      return;
    }
    *((void **) (((signed char *) new_var2) + 0x40)) = (void *) (temp_v1 + 4);
  }
}

void func_80031744(void *arg0)
{
  u8 *temp_v1;
  signed char *new_var;
  new_var = (signed char *) arg0;
  temp_v1 = *((u8 **) (new_var + 0x3C));
  if (temp_v1 != 0)
  {
    if ((*temp_v1) & 0x80)
    {
      *((void **) (new_var + 0x40)) = 0;
      *((u8 **) (new_var + 0x3C)) = 0;
      return;
    }
    *((void **) (new_var + 0x40)) = (void *) (temp_v1 + 1);
  }
}

extern s32 *D_800E7E74;
extern u8 D_800E7E80_f78d[];
typedef struct { s32 x, y, z; } Vec3i_74C;
typedef struct { u8 pad[0x1C]; Vec3i_74C v; } ConvTarget_74C;
typedef struct { u8 pad[0x2C]; Vec3i_74C pos; } PosHolder_858;
void func_80031780(u8 *p)
{
    s32 *e = *(s32 **)(p + 0x34);
    s32 w;

    if (e == 0) {
        return;
    }
    do {
        w = e[1];
        e += 2;
    } while (!(w & 0xC0000000));
    if (w & 0x40000000) {
        *(s32 *)(p + 0x38) = 0;
        *(s32 *)(p + 0x34) = 0;
    } else {
        *(s32 **)(p + 0x38) = e;
    }
}

s32 f_ProjectEffectPointToScreenAndDepth(s16 bias)
{
    s32 *flag = &D_1F800080;
    s32 *otz = (s32 *)D_1F800084;
    s32 *sxy = (s32 *)D_1F80008C;
    s32 e;

    gte_rtps();
    gte_stflg(flag);
    if (*flag < 0) {
        return 1;
    }
    gte_stsz(flag);
    if (*flag <= 0) {
        return 1;
    }
    *flag = (*flag >> 2) + bias;
    if (*flag < 4) {
        *flag = 4;
    }
    e = *flag >> 10;
    *flag = (*flag >> e) + (e << 9);
    if ((u32)(*flag - 4) >= 0x7FC) {
        *flag = -1;
    }
    if (*flag < 0) {
        return 1;
    }
    gte_stsxy(sxy);
    gte_stopz(otz);
    return 0;
}

void f_SetIdentityMatrix(s32 *m);
void f_SetEffectRenderTransform(void *pos, u8 *scale, s16 *rot)
{
    s32 v[3];

    RotMatrix_gte(rot, D_1F800000);
    v[0] = scale[0] * 4;
    v[1] = scale[1] * 4;
    v[2] = scale[2] * 4;
    ScaleMatrix(D_1F800000, v);
    gte_SetRotMatrix(D_1F8000F8);
    gte_ldclmv(D_1F800000);
    gte_rtir();
    gte_stclmv(D_1F800000);
    gte_ldclmv(D_1F800002);
    gte_rtir();
    gte_stclmv(D_1F800002);
    gte_ldclmv(D_1F800004);
    gte_rtir();
    gte_stclmv(D_1F800004);
    gte_ldv0(pos);
    gte_rtv0();
    gte_stlvnl(D_1F800014);
    D_1F800000[5] += D_1F8000D0_42d8[15];
    D_1F800000[6] += D_1F8000D0_42d8[16];
    D_1F800000[7] += D_1F8000D0_42d8[17];
    gte_SetRotMatrix(D_1F800000);
    gte_SetTransMatrix(D_1F800000);
}

void f_SetIdentityMatrix(s32 *m);
void func_80031AC4(void *pos, u8 *scale, s16 *rot)
{
    s32 v[3];

    RotMatrix_gte(rot, D_1F800000);
    f_SetIdentityMatrix(D_1F800020_edd9);
    RotMatrixX(rot[3], D_1F800020_edd9);
    MulMatrix(D_1F800000, D_1F800020_edd9);
    v[0] = scale[0] * 4;
    v[1] = scale[1] * 4;
    v[2] = scale[2] * 4;
    ScaleMatrix(D_1F800000, v);
    gte_SetRotMatrix(D_1F8000F8);
    gte_ldclmv(D_1F800000);
    gte_rtir();
    gte_stclmv(D_1F800000);
    gte_ldclmv(D_1F800002);
    gte_rtir();
    gte_stclmv(D_1F800002);
    gte_ldclmv(D_1F800004);
    gte_rtir();
    gte_stclmv(D_1F800004);
    gte_ldv0(pos);
    gte_rtv0();
    gte_stlvnl(D_1F800014);
    D_1F800000[5] += D_1F8000D0_42d8[15];
    D_1F800000[6] += D_1F8000D0_42d8[16];
    D_1F800000[7] += D_1F8000D0_42d8[17];
    gte_SetRotMatrix(D_1F800000);
    gte_SetTransMatrix(D_1F800000);
}

void func_80031D24(void *pos, u8 *scale, s16 *rot)
{
    s32 v[3];

    RotMatrix_gte(rot, D_1F800000);
    f_SetIdentityMatrix(D_1F800020_edd9);
    RotMatrixY(rot[3], D_1F800020_edd9);
    MulMatrix(D_1F800000, D_1F800020_edd9);
    v[0] = scale[0] * 4;
    v[1] = scale[1] * 4;
    v[2] = scale[2] * 4;
    ScaleMatrix(D_1F800000, v);
    gte_SetRotMatrix(D_1F8000F8);
    gte_ldclmv(D_1F800000);
    gte_rtir();
    gte_stclmv(D_1F800000);
    gte_ldclmv(D_1F800002);
    gte_rtir();
    gte_stclmv(D_1F800002);
    gte_ldclmv(D_1F800004);
    gte_rtir();
    gte_stclmv(D_1F800004);
    gte_ldv0(pos);
    gte_rtv0();
    gte_stlvnl(D_1F800014);
    D_1F800000[5] += D_1F8000D0_42d8[15];
    D_1F800000[6] += D_1F8000D0_42d8[16];
    D_1F800000[7] += D_1F8000D0_42d8[17];
    gte_SetRotMatrix(D_1F800000);
    gte_SetTransMatrix(D_1F800000);
}

void func_80031F84(void *pos, u8 *scale, s16 *rot)
{
    s32 v[3];

    RotMatrix_gte(rot, D_1F800000);
    f_SetIdentityMatrix(D_1F800020_edd9);
    RotMatrixY(rot[3], D_1F800020_edd9);
    MulMatrix(D_1F800000, D_1F800020_edd9);
    v[0] = scale[0];
    v[1] = scale[1];
    v[2] = scale[2];
    ScaleMatrix(D_1F800000, v);
    gte_SetRotMatrix(D_1F8000F8);
    gte_ldclmv(D_1F800000);
    gte_rtir();
    gte_stclmv(D_1F800000);
    gte_ldclmv(D_1F800002);
    gte_rtir();
    gte_stclmv(D_1F800002);
    gte_ldclmv(D_1F800004);
    gte_rtir();
    gte_stclmv(D_1F800004);
    gte_ldv0(pos);
    gte_rtv0();
    gte_stlvnl(D_1F800014);
    D_1F800000[5] += D_1F8000D0_42d8[15];
    D_1F800000[6] += D_1F8000D0_42d8[16];
    D_1F800000[7] += D_1F8000D0_42d8[17];
    gte_SetRotMatrix(D_1F800000);
    gte_SetTransMatrix(D_1F800000);
}

void func_800321D8(void *pos, u8 *scale, s16 *rot)
{
    s32 v[3];

    RotMatrixZYX(rot, D_1F800000);
    v[0] = scale[0] * 4;
    v[1] = scale[1] * 4;
    v[2] = scale[2] * 4;
    ScaleMatrix(D_1F800000, v);
    gte_SetRotMatrix(D_1F8000F8);
    gte_ldclmv(D_1F800000);
    gte_rtir();
    gte_stclmv(D_1F800000);
    gte_ldclmv(D_1F800002);
    gte_rtir();
    gte_stclmv(D_1F800002);
    gte_ldclmv(D_1F800004);
    gte_rtir();
    gte_stclmv(D_1F800004);
    gte_ldv0(pos);
    gte_rtv0();
    gte_stlvnl(D_1F800014);
    D_1F800000[5] += D_1F8000D0_42d8[15];
    D_1F800000[6] += D_1F8000D0_42d8[16];
    D_1F800000[7] += D_1F8000D0_42d8[17];
    gte_SetRotMatrix(D_1F800000);
    gte_SetTransMatrix(D_1F800000);
}

void func_800323FC(void *pos, u8 *scale, s16 *rot)
{
    s32 v[3];

    RotMatrixZYX(rot, D_1F800000);
    f_SetIdentityMatrix(D_1F800020_edd9);
    RotMatrixY(rot[3], D_1F800020_edd9);
    MulMatrix(D_1F800000, D_1F800020_edd9);
    v[0] = scale[0] * 4;
    v[1] = scale[1] * 4;
    v[2] = scale[2] * 4;
    ScaleMatrix(D_1F800000, v);
    gte_SetRotMatrix(D_1F8000F8);
    gte_ldclmv(D_1F800000);
    gte_rtir();
    gte_stclmv(D_1F800000);
    gte_ldclmv(D_1F800002);
    gte_rtir();
    gte_stclmv(D_1F800002);
    gte_ldclmv(D_1F800004);
    gte_rtir();
    gte_stclmv(D_1F800004);
    gte_ldv0(pos);
    gte_rtv0();
    gte_stlvnl(D_1F800014);
    D_1F800000[5] += D_1F8000D0_42d8[15];
    D_1F800000[6] += D_1F8000D0_42d8[16];
    D_1F800000[7] += D_1F8000D0_42d8[17];
    gte_SetRotMatrix(D_1F800000);
    gte_SetTransMatrix(D_1F800000);
}

void func_8003265C(void *pos, u8 *scale, s16 *rot)
{
    s32 v[3];

    RotMatrixZYX(rot, D_1F800000);
    f_SetIdentityMatrix(D_1F800020_edd9);
    RotMatrixX(rot[3], D_1F800020_edd9);
    MulMatrix(D_1F800000, D_1F800020_edd9);
    v[0] = scale[0] * 4;
    v[1] = scale[1] * 4;
    v[2] = scale[2] * 4;
    ScaleMatrix(D_1F800000, v);
    gte_SetRotMatrix(D_1F8000F8);
    gte_ldclmv(D_1F800000);
    gte_rtir();
    gte_stclmv(D_1F800000);
    gte_ldclmv(D_1F800002);
    gte_rtir();
    gte_stclmv(D_1F800002);
    gte_ldclmv(D_1F800004);
    gte_rtir();
    gte_stclmv(D_1F800004);
    gte_ldv0(pos);
    gte_rtv0();
    gte_stlvnl(D_1F800014);
    D_1F800000[5] += D_1F8000D0_42d8[15];
    D_1F800000[6] += D_1F8000D0_42d8[16];
    D_1F800000[7] += D_1F8000D0_42d8[17];
    gte_SetRotMatrix(D_1F800000);
    gte_SetTransMatrix(D_1F800000);
}

void func_800328BC(void *arg0, M2C_UNK arg1) {
    f_DrawProjectedSpriteDefinitionStream(arg1, (M2C_FIELD(arg0, u16 *, 0x46) << 0x10) | M2C_FIELD(arg0, u16 *, 0x44));
}

void f_DrawEffectPrimitiveListWithoutDepthCue(void *list)
{
    *(s32 *)D_1F800090 = 0;
    func_8002847C(list, 0, 0);
}

void func_80032918(u8 *a)
{
    switch (a[4]) {
    case 0:
        a[6] = 0x10;
        *(s32 *)(a + 0x34) = *(s32 *)(a + 0x38);
        a[4] = 1;
        if (a[3] == 0x37) {
            *(u16 *)(a + 0x44) += 0x40;
        }
    case 1:
        if ((*(s32 *)(a + 0x34) = *(s32 *)(a + 0x38)) == 0) {
            a[4] = 2;
            break;
        }
        if (func_8002B278(a) == 0) {
            func_80031780(a);
        }
        break;
    case 2:
    case 3:
        f_ResolveEffectEightByteStreamPayload(a);
        break;
    }
}

void f_SetEffectProjectionTransform(s32 dqa)
{
    gte_SetRotMatrix(D_1F8000F8);
    gte_SetTransMatrix(D_1F8000F8);
    gte_lddqa(dqa);
    gte_lddqb0();
}

s32 func_80032A44(s32 arg0, s32 arg1)
{
  s32 new_var;
  new_var = (s32) (rand() * (arg1 - arg0));
  new_var = new_var >> 0xF;
  return new_var + arg0;
}

s32 func_80032A88(s32 arg0) {
    return (s32) (rand() - 0x4000) >> arg0;
}

void func_80032AB4(void *pos, u8 *scale)
{
    s32 v[3];

    v[0] = scale[0] * 4;
    v[1] = scale[1] * 4;
    v[2] = scale[2] * 4;
    ScaleMatrix(D_1F800000, v);
    gte_SetRotMatrix(D_1F8000F8);
    gte_ldclmv(D_1F800000);
    gte_rtir();
    gte_stclmv(D_1F800000);
    gte_ldclmv(D_1F800002);
    gte_rtir();
    gte_stclmv(D_1F800002);
    gte_ldclmv(D_1F800004);
    gte_rtir();
    gte_stclmv(D_1F800004);
    gte_ldv0(pos);
    gte_rtv0();
    gte_stlvnl(D_1F800014);
    D_1F800000[5] += D_1F8000D0_42d8[15];
    D_1F800000[6] += D_1F8000D0_42d8[16];
    D_1F800000[7] += D_1F8000D0_42d8[17];
    gte_SetRotMatrix(D_1F800000);
    gte_SetTransMatrix(D_1F800000);
}

void func_80032CBC(void *pos, u8 *scale)
{
    s32 v[3];

    v[0] = scale[0];
    v[1] = scale[1];
    v[2] = scale[2];
    ScaleMatrix(D_1F800000, v);
    gte_SetRotMatrix(D_1F8000F8);
    gte_ldclmv(D_1F800000);
    gte_rtir();
    gte_stclmv(D_1F800000);
    gte_ldclmv(D_1F800002);
    gte_rtir();
    gte_stclmv(D_1F800002);
    gte_ldclmv(D_1F800004);
    gte_rtir();
    gte_stclmv(D_1F800004);
    gte_ldv0(pos);
    gte_rtv0();
    gte_stlvnl(D_1F800014);
    D_1F800000[5] += D_1F8000D0_42d8[15];
    D_1F800000[6] += D_1F8000D0_42d8[16];
    D_1F800000[7] += D_1F8000D0_42d8[17];
    gte_SetRotMatrix(D_1F800000);
    gte_SetTransMatrix(D_1F800000);
}

s32 func_80032EB8(s16 bias)
{
    s32 *flag = &D_1F800080;
    s32 *otz = (s32 *)D_1F800084;
    s32 *sxy = (s32 *)D_1F80008C;
    s32 e;

    gte_rtps();
    gte_stflg(flag);
    if (*flag < 0) {
        goto ret1;
    }
    gte_stsz(flag);
    if (*flag > 0) {
        goto cont;
    }
ret1:
    return 1;
big:
    *flag = 0x7FD;
    goto test;
cont:
    *flag = (*flag >> 2) + bias;
    if (*flag < 4) {
        *flag = 4;
    }
    e = *flag >> 10;
    *flag = (*flag >> e) + (e << 9);
    if (*flag >= 0x7FE) {
        goto big;
    }
    if (*flag < 4) {
        *flag = -1;
    }
test:
    if (*flag < 0) {
        return 1;
    }
    gte_stsxy(sxy);
    gte_stopz(otz);
    return 0;
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_80032F98);

void func_80033080(s32 arg0) {
    func_80027E5C();
    func_800288AC(arg0);
}

void func_800330AC(u8 *a)
{
    switch (a[4]) {
    case 0:
        a[4]++;
        *(void **)(a + 0x40) = D_800A1EB8;
        *(void **)(a + 0x50) = D_800A1EA0;
        *(s16 *)(a + 0x32) = -0x32;
        *(s32 *)(a + 0x34) = 0x1000100;
    case 1: {
        void *p = *(void **)(a + 0x40);

        *(void **)(a + 0x3C) = p;
        if (p == 0) {
            a[4] = 3;
        } else {
            a[1] = 1;
        }
        break;
    }
    case 2:
    case 3:
        f_ResolveEffectEightByteStreamPayload(a);
        break;
    }
}

u8 *f_SpawnLinkedActorShadow(u8 *owner)
{
    u8 *a;

    if (D_800E7E7C >= 7) {
        a = f_AllocateActorRecordByType(0, 6, 1);
        if (a != 0) {
            *(void **)(a + 0x1C) = func_80059ED8;
            a[0xB] = 0x20;
            *(u8 **)(a + 0x10) = owner;
            *(void **)(a + 0x18) = func_8002AB5C;
            a[0x28] |= 0x80;
            return a;
        }
    }
    return 0;
}

u8 *f_SpawnLinkedActorSpriteRingEffect(u8 *src, void *owner, s32 v, s32 y)
{
    u8 *e;

    if (src[0x1B] & 0x40) {
        return 0;
    }
    e = f_AllocateActorRecordByType(0, 6, 1);
    if (e == 0) {
        return 0;
    }
    e[0xB] = 0x20;
    *(void **)(e + 0x1C) = func_8002B7B0;
    *(void **)(e + 0x10) = owner;
    *(u8 **)(e + 0x14) = src;
    *(s32 *)(e + 0x50) = v;
    *(s16 *)(e + 0x32) = y;
    *(void **)(e + 0x18) = func_8002B3A4;
    return e;
}

extern u8 D_800A0C5C[];
extern u8 D_800A0DCC[];
void func_80033278(u8 *a)
{
    s16 v;
    u8 *p;

    switch (a[4]) {
    case 0:
        if (D_1F800236_18be == 3) {
            *(s16 *)(a + 0x4A) = 0x6E;
        } else {
            *(s16 *)(a + 0x4A) = -0x6E;
        }
        *(s16 *)(a + 0x4E) = 0;
        *(u8 **)(a + 0x38) = NULL;
        a[4] = 1;
    case 1:
        p = *(u8 **)(a + 0x38);
        a[1] = 1;
        *(u8 **)(a + 0x34) = p;
        if (p == NULL) {
            u8 *q;

            if (D_1F800236_18be == 3) {
                q = D_800A0C5C;
            } else {
                q = D_800A0DCC;
            }
            *(u8 **)(a + 0x38) = q;
            *(u8 **)(a + 0x34) = q;
        }
        v = *(u16 *)(a + 0x4E) + *(u16 *)(a + 0x4A);
        *(s16 *)(a + 0x4E) = v;
        if (v > 0x300) {
            *(s16 *)(a + 0x4E) = v - 0x300;
        } else if (v < -0x300) {
            *(s16 *)(a + 0x4E) = v + 0x300;
        }
        break;
    case 2:
    case 3:
        f_ResolveEffectEightByteStreamPayload();
        break;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_80033380);

extern s32 D_800A2068[];
void func_80033450(u8 *a)
{
    s32 one = 1;

    switch (a[4]) {
    case 0:
        *(s32 *)(a + 0x5C) = 0xC010C;
        a[4] = one;
        a[5] = 0;
        *(s32 *)(a + 0x58) = 0;
        *(s32 *)(a + 0x60) = 0x1000;
    case 1:
        a[5]++;
        *(s32 *)(a + 0x64) = D_800A2068[a[5]];
        if (a[5] < 4) {
            *(s32 *)(a + 0x5C) += *(s32 *)(a + 0x60);
            *(s32 *)(a + 0x60) -= 0x300;
            *(s32 *)(a + 0x58) += 0xCC;
        } else if (a[5] < 16) {
            *(s32 *)(a + 0x5C) += 0x200;
            *(s32 *)(a + 0x58) += 0x174;
        } else {
            a[4] = 2;
            break;
        }
        a[1] = 1;
        break;
    case 2:
    case 3:
        f_ResolveEffectEightByteStreamPayload();
        break;
    }
}

extern u8 D_800E7FF9;
s32 f_ResolveEffectEightByteStreamPayload();
void func_80033560(u8 *a)
{
    switch (a[4]) {
    case 0:
        a[4] = 1;
        a[7] = 0;
        a[0x29] = 0;
        break;
    case 1:
        a[1] = 1;
        a[0x29] = (a[0x29] - 1) & 0x1F;
        if (D_800E7FF9 == 0) {
            a[4] = 2;
        }
        break;
    case 2:
        if ((s8)a[7] < 0) {
            a[4] = 3;
            break;
        }
        a[1] = 1;
        a[7] += 0xC;
        break;
    case 3:
        f_ResolveEffectEightByteStreamPayload(a);
        break;
    }
}

void func_80033630(u8 *a)
{
    switch (a[4]) {
    case 0:
        *(s32 *)(a + 0x48) = 0;
        *(s16 *)(a + 0x4C) = 0;
        a[4] = 1;
        a[5] = 0xFF;
        *(u16 *)(a + 0x2E) += 0x78;
    case 1:
        if (++a[5] >= 6) {
            a[4] = 2;
        } else {
            a[1] = 1;
        }
        break;
    case 2:
    case 3:
        f_ResolveEffectEightByteStreamPayload(a);
        break;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_800336DC);

extern u16 D_800A239C[];
extern void *D_800174AC;
extern void *D_800174B0;
extern u8 D_800E7E80_f78d[];
extern u8 *D_1F8001E4;
extern u8 *D_1F8001D4;
void func_8003393C(u8 *a, u8 c)
{
    struct { u8 b0; u8 b1; s16 h2; } q;
    UiRect r;
    u16 *t = D_800A239C;

    r.x = t[0];
    r.y = t[1];
    r.w = t[2];
    r.h = t[3];
    q.b1 = c;
    q.b0 = 0;
    q.h2 = 0;
    f_DrawPackedUiQuadFrame(&r, D_800174AC, *(void **)(a + 4), &q);
}

void func_800339A4(u8 *a, u8 c)
{
    struct { u8 b0; u8 b1; s16 h2; } q;
    UiRect r;
    u16 *t = D_800A239C;

    r.x = t[4];
    r.y = t[5];
    r.w = t[6];
    r.h = t[7];
    q.b1 = c;
    q.b0 = 0;
    q.h2 = 0;
    f_DrawPackedUiQuadFrame(&r, D_800174B0, *(void **)(a + 4), &q);
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_80033A0C);

typedef struct { u8 a; u8 b; u16 c; } SprAttr_3AC8;
typedef struct { s16 x; s16 y; s32 z; } SprPos_3AC8;
u8 *f_SpawnLinkedActorTrailEffect(u8 *owner, u8 kind);
void f_DrawPauseMenuButtonIcon(s32 button, s16 x, s16 y, u8 b)
{
    SprAttr_3AC8 attr;
    SprPos_3AC8 pos;
    s32 i;

    switch (button) {
    case 0x8000:
        i = 0x77;
        break;
    case 0x4000:
        i = 0x75;
        break;
    case 0x2000:
        i = 0x74;
        break;
    case 0x1000:
    default:
        i = 0x76;
        break;
    }
    attr.c = 0x7CBE;
    attr.b = b;
    attr.a = 0;
    pos.x = x;
    pos.y = y;
    pos.z = 0;
    f_DrawPackedUiSpriteFrame(&pos, D_80017334_ae99[i], D_800ECF58[0], &attr);
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_80033B94);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80033FF4);

void func_800342EC(u8 *a, s16 x, s16 y, u8 c)
{
    struct { u8 b0; u8 b1; s16 h2; } q;
    struct { s16 x; s16 y; s32 z; } pos;

    pos.x = x;
    q.b1 = c;
    q.b0 = 0;
    q.h2 = 0;
    pos.y = y;
    pos.z = 0;
    f_DrawPackedUiSpriteFrame(&pos, D_800174C4, *(void **)(a + 4), &q);
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_80034338);

s32 func_80034548(s32 arg0) {
    func_80033FF4(arg0, 0x65);
    func_800336DC(arg0, 0, 0, 0x6C);
    func_80033B94(arg0, 0, 0x64);
    f_DrawFullscreenOverlay(0x404040, 0, 0x74);
    func_800336DC(arg0, 3, 3, 0x84);
    return func_8007FCC8(0, 0, 0x140, 0xF0, /* extra? */ 0x81);
}

void func_800345D8(u8 *a)
{
    s32 i;

    for (i = 0; i < 4; i++) {
        if (i == a[8]) {
            a[i + 0xC] = 0;
            a[i + 0x10] = 0;
            a[i + 0x14] = 0x64;
        } else {
            a[i + 0xC] = 2;
            a[i + 0x10] = 3;
            a[i + 0x14] = 0x84;
        }
    }
}

void func_80034634(void *arg0) {
    s32 temp_a0;

    temp_a0 = M2C_FIELD(arg0, s32 *, 0x28);
    if (temp_a0 != 0) {
        f_ResolveEffectEightByteStreamPayload(temp_a0);
        M2C_FIELD(arg0, s32 *, 0x28) = 0;
    }
}

void func_80034670(void *arg0) {
    M2C_FIELD(arg0, s8 *, 1) = 0;
    M2C_FIELD(arg0, s8 *, 2) = 0;
    M2C_FIELD(arg0, s8 *, 3) = 0;
    M2C_FIELD(arg0, s8 *, 0x1C) = 0;
    M2C_FIELD(arg0, s8 *, 0x1D) = 0;
    M2C_FIELD(arg0, s8 *, 0x1E) = 0;
    M2C_FIELD(arg0, s8 *, 0x1F) = 0;
    f_PlaySequencedMusic(1);
    func_80034634(arg0);
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_800346BC);

s32 func_8003499C(void) {
    return 0;
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_800349A4);

extern u8 D_800BF81C;
s32 func_80034BE0(s32 unused, s32 item, s32 mode)
{
    u8 *t = (u8 *)D_800E7E80;
    u8 *g = (u8 *)&D_800BF870;

    if (g[3] != 0 || (g[0x11] & 4) || (*(u16 *)(g + 0x2E) & 0x200) || (D_800BF870.unk0 == 7 && g[0x276] != 0)) {
        if (mode == 1) {
            return 1;
        }
        return 4;
    }
    if (mode == 1) {
        return 0;
    }
    if (item == (u8)D_800BF88E) {
        if (item == t[0x6E]) {
            D_800BF81C = 2;
        } else {
            D_800BF81C = 0;
        }
        D_800BF88E = 0;
        return 0;
    }
    if (item != t[0x6E]) {
        D_800BF81C = 1;
    } else {
        D_800BF81C = 0;
    }
    D_800BF88E = item;
    return 0;
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_80034CE0);

extern void *D_800A3ED8;
extern u8 D_80106228[];
typedef struct { s32 sector; s32 size; } FileLoc_1E0;
extern FileLoc_1E0 D_800BE1E0_8c5b[];
extern void *D_800A3ECC[];
extern s16 D_1F8000F2;
extern u8 D_800A3B0C_b8ee;
s32 func_80035088(void *unused, s32 item, s32 mode)
{
    u8 *g = (u8 *)&D_800BF870;

    if ((g[0x11] & 4) || (*(u16 *)(g + 0x2E) & 0x200)) {
        if (mode == 1) {
            return 1;
        }
        return 4;
    }
    if (mode == 1) {
        return 0;
    }
    if (g[0x5E5]) {
        g[0x5E5] = 0;
        func_8004D6F4(item);
    } else {
        g[0x5E5] = 1;
        func_8004D6D4(item);
    }
    return 0;
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_8003511C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80035218);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80035338);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80035424);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80035528);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800355B4);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80035640);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80035738);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80035FAC);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80036240);

u8 func_80078770(u8 a, u8 b);
void func_800364AC(s32 mode, u32 sub, s32 *outMode, s32 *outRes)
{
    s32 m;

    if (mode == 0) {
        m = 0;
    } else if (mode == 1) {
        if (sub < 3) {
            m = 1;
        } else {
            m = 2;
            sub = 0;
        }
    } else if (mode == 2) {
        if (sub == 0) {
            m = 4;
            goto clear;
        } else if (sub == 1) {
            m = 5;
            sub = 0;
        } else {
            m = 5;
            sub = 1;
        }
    } else if (mode == 3) {
        m = 6;
    } else if (mode == 4) {
        m = 7;
        sub = 0;
    } else if (mode == 5) {
        m = 8;
        sub = 0;
    } else {
        m = 0;
    clear:
        sub = 0;
    }
    *outMode = m;
    *outRes = ((s32 (*)(s32, u8))func_80078770)(m, sub);
}

extern char D_800172A4[];
extern char D_800172A8[];
extern u8 D_800A2854[];
typedef struct { u8 pad[0xA4]; void *a; void *pad2; void *b; } MenuText_854;
extern u8 *D_800BF544_37fb;
extern u32 *D_800ED8C8;
typedef struct { s32 x, y, z; } Vec3i_F08;
typedef struct { u8 pad[0x1C]; Vec3i_F08 v; } ConvTarget_F08;
s32 f_GetPauseMenuEquipmentGroupRange(s32 g, s32 *start)
{
    s32 n;

    if (g == 0) {
        n = 2;
        goto zero;
    }
    if (g == 1) {
        n = 4;
        *start = 2;
    } else if (g == 2) {
        n = 3;
        *start = 6;
    } else if (g == 3) {
        n = 3;
        *start = 9;
    } else if (g == 4) {
        n = 1;
        *start = 0xC;
    } else if (g == 5) {
        n = 1;
        *start = 0xD;
    } else {
        n = 0;
    zero:
        *start = 0;
    }
    return n;
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_800365F0);

s32 func_80036708(void *p)
{
    s32 i;

    for (i = 0; i < 6; i++) {
        if (func_800365F0(p, 1) == 0) {
            return i != 0;
        }
    }
    return 1;
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_8003675C);

s32 func_8003687C(void *p)
{
    s32 i;

    for (i = 0; i < 6; i++) {
        if (func_8003675C(p, 1) == 0) {
            return i != 0;
        }
    }
    return 1;
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_800368D0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80036A14);

s32 func_80036AE8(s32 arg0) {
    func_80036A14(arg0, 0);
    func_80036A14(arg0, 1);
    return func_80036A14(arg0, 2);
}

void func_80036B28(u8 *arg0, u8 *arg1) {
    s32 temp_v0;
    s32 var_v1;
    u8 *var_s0;
    u8 *var_s1;
    u8 temp_v0_2;

    var_s1 = arg0;
    var_s0 = arg1;
    temp_v0 = strlen(arg0);
    var_v1 = 0;
    if (temp_v0 > 0) {
        do {
            temp_v0_2 = *var_s1;
            if (temp_v0_2 == 0xA) {
                *var_s0 = 0x20;
                var_s0 += 1;
                var_s1 += 1;
            } else {
                *var_s0 = temp_v0_2;
                var_s1 += 1;
                var_s0 += 1;
            }
            var_v1 += 1;
        } while (var_v1 < temp_v0);
    }
    *var_s0 = 0;
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_80036BAC);

extern u8 D_800BF873;
s32 func_80036D90(s32 arg0) {
    if ((D_800BF873 != 0) && ((arg0 == 0) || (arg0 == 5))) {
        return 1;
    }
    return 0;
}

extern s16 D_800ED098;
extern s32 *D_800E7E74;
extern u8 D_800A24E4[];
extern u8 D_800BF88C;
extern u8 D_800E7EEC;
extern u16 D_1F800172_5cdb;
extern u8 **D_800A54A8[];
void func_80071B44(u8 *src, s32 n, s32 kind);
s32 func_80036DC4(s32 i)
{
    if (D_800BF873 != 0) {
        if (D_800A24E4[i] == 0) {
            return 1;
        }
    }
    return 0;
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_80036DFC);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800376EC);

extern void *D_800174BC;
extern void *D_800BF544;
extern s16 D_801003F8;
void func_80037894(u8 *ui, s16 y, u8 c)
{
    struct { u8 b0; u8 b1; s16 h2; } q;
    struct { s16 x; s16 y; s32 wh; } r;
    void *res = D_800174BC;
    s32 i = 0;
    s32 x = 0x18;

    q.b1 = c;
    q.b0 = 0;
    q.h2 = 0;
    r.y = y;
    r.wh = 0;
    do {
        r.x = x;
        x += 8;
        i++;
        f_DrawPackedUiSpriteFrame(&r, res, *(void **)(ui + 4), &q);
    } while (i < 0x22);
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_8003791C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80037B6C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80037E44);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800384EC);

s32 func_800386C0(u8 *p)
{
    if (p[0x1F] < p[0x21] - 1) {
        p[0x1F]++;
        if (p[0x1F] >= p[0x1E] + 6) {
            p[0x1E]++;
        }
        return 1;
    }
    return 0;
}

extern u8 D_1F800231;
extern s32 D_800BF808_4426[];
extern s16 D_1F800180;
s32 func_80038708(u8 *p)
{
    s32 i;
    s32 last = p[0x21] - 1;

    for (i = 0; i < 6; i++) {
        if (p[0x1F] >= last) {
            return i != 0;
        }
        p[0x1F]++;
        p[0x1E]++;
    }
    return 1;
}

s32 func_80038758(u8 *a)
{
    if (a[0x1F] != 0) {
        a[0x1F]--;
        if (a[0x1F] < a[0x1E]) {
            a[0x1E]--;
        }
        return 1;
    }
    return 0;
}

s32 func_80038794(u8 *p)
{
    s32 i;

    for (i = 0; i < 6; i++) {
        if (p[0x1F] == 0) {
            return i != 0;
        }
        p[0x1F]--;
        if (p[0x1E] != 0) {
            p[0x1E]--;
        }
    }
    return 1;
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_800387E0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80038A00);

s32 func_80038F7C(s32 id)
{
    s16 alt;
    s32 r;

    if (id & 0x80) {
        alt = 1;
        id &= 0x7F;
    } else {
        alt = 0;
    }
    if (id == 0x17) {
        r = alt ? 0x13D : 0xDB;
    } else if (id == 0x18) {
        r = alt ? 0x13E : 0xDC;
    } else if (id == 0x19) {
        r = alt ? 0x140 : 0xDE;
    } else if (id == 0x1A) {
        r = alt ? 0x141 : 0xDF;
    } else if (id == 0x1B) {
        r = alt ? 0x13F : 0xDD;
    } else {
        r = alt ? 0x142 : 0xE0;
    }
    return r;
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_80039034);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80039110);

extern u8 D_800E806E;
extern u8 D_800BF843;
typedef struct { s16 x, y, z; u8 flags; u8 pad; } SpawnPoint_8824;
extern SpawnPoint_8824 *D_800A54A8_86de[];
void func_8003989C(u8 *p)
{
    s32 i = 0;

    while (D_800A3AC4[i + 1] != 0) {
        if ((D_800BF870.flags5C4 >> i) & 1) {
            p[0x23]++;
        }
        i++;
    }
}

s32 func_8003990C(s32 n)
{
    s32 i = 0;
    s32 cnt = 0;

    while (D_800A3AC4[i + 1] != 0) {
        if ((D_800BFE34 >> i) & 1) {
            if (n == cnt) {
                return i;
            }
            cnt++;
        }
        i++;
    }
    return 0;
}

s32 func_80039978(u8 *p)
{
    if (p[0x1F] < p[0x23] - 1) {
        p[0x1F]++;
        if (p[0x1F] >= p[0x1E] + 5) {
            p[0x1E]++;
        }
        return 1;
    }
    return 0;
}

s32 func_800399C0(u8 *a)
{
    if (a[0x1F] != 0) {
        a[0x1F]--;
        if (a[0x1F] < a[0x1E]) {
            a[0x1E]--;
        }
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_800399FC);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80039BCC);

s32 func_80039E80(u8 *s, u8 *p)
{
    if (s[0] == 0x20) {
        return -1;
    }
    D_1F800180 = 0x20;
    p[0xC] = ((s[0] + 0x20) % 32) * 8;
    p[0xD] = ((s[0] + D_1F800180) / 32) * 16 + 8;
    p[0x14] = p[0xC] + 8;
    p[0x1C] = p[0xC];
    p[0x24] = p[0xC] + 8;
    if (p[0x14] == 0) {
        p[0x14] = 0xFF;
        p[0x24] = 0xFF;
    }
    p[0x15] = p[0xD];
    p[0x1D] = p[0xD] + 0x10;
    p[0x25] = p[0xD] + 0x10;
    return 0;
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_80039F4C);

extern u8 D_800BF80E_58ec;
extern s32 D_1F800184;
extern s16 D_800BF82A;
extern u8 D_800FB164;
typedef struct { s16 seq; s16 id; s16 mode; s16 on; } SeqSlot_368;
extern SeqSlot_368 D_800BE368[];
s32 func_8003A1E4(u8 *a, u8 *b)
{
    s32 v = a[8] >> 1;

    if (a[8] & 1) {
        b = (u8 *)(u32)b[0x3F];
        if ((s32)b == v) {
            return 0;
        }
        if ((s32)b < v) {
            return -((v - (s32)b) * 12);
        }
        return ((s32)b - v) * 12;
    }
    b = (u8 *)(u32)b[0x3F];
    if ((s32)b >= v) {
        return ((s32)b - v) * 12 + 6;
    }
    return -((v - (s32)b) * 12) + 6;
}

void func_8003A290(u8 *a, u8 *b)
{
    switch (b[0x3E]) {
    case 0:
        b[0x3E] = 1;
        *(s16 *)(b + 0x16) = (func_8003A1E4(a, b) * 16) / 24;
        *(s16 *)(b + 0x10) = 0;
        *(s16 *)(b + 0x12) = (rand() & 0xF) - 0xC0;
        *(s16 *)(b + 0x8) = (rand() & 0x3F) << 6;
    case 1:
        *(s16 *)(b + 0x0) = *(s16 *)(b + 0x10) >> 4;
        *(s16 *)(b + 0x10) += *(s16 *)(b + 0x16);
        *(s16 *)(b + 0x2) += *(s16 *)(b + 0x12) >> 4;
        *(s16 *)(b + 0x12) += 0x10;
        *(s16 *)(b + 0x8) += 0x80;
        if (*(s16 *)(b + 0x2) >= 0) {
            *(s16 *)(b + 0x0) = func_8003A1E4(a, b);
            *(s16 *)(b + 0x8) = 0;
            b[0x3E]++;
        }
        break;
    case 2:
        if (b[0x3F] == 0) {
            a[5]++;
        }
        break;
    }
}

extern u8 D_800E7E81;
void func_8003A3E8(void *a, u8 *s)
{
    switch (s[0x3E]) {
    case 0:
        s[0x3E]++;
        *(s16 *)s = func_8003A1E4(a, s);
        *(s16 *)(s + 0x12) = (rand() & 0x1F) << 7;
    case 1:
        *(s16 *)(s + 2) = (rcos(*(s16 *)(s + 0x12)) * 3) >> 12;
        *(s16 *)(s + 0x12) += 0x80;
        break;
    }
}

void func_8003A470(u8 *a, u8 *b)
{
    switch (b[0x3E]) {
    case 0:
        b[0x3E] = 1;
        *(s16 *)(b + 0x12) = -0x180;
    case 1:
        b[0x3E]++;
        *(s16 *)(b + 0x12) = (rand() & 0x1F) - 0xC0;
        *(s16 *)(b + 0x16) = 6;
        *(s16 *)(b + 0x10) = *(u16 *)(b + 0x0) * 16;
        *(s16 *)(b + 0x38) = (func_8003A1E4(a, b) * 16) / *(s16 *)(b + 0x16);
        break;
    case 2:
        *(s16 *)(b + 0x2) += *(s16 *)(b + 0x12) >> 4;
        *(s16 *)(b + 0x12) += 0x20;
        *(s16 *)(b + 0x10) += *(s16 *)(b + 0x38);
        *(s16 *)(b + 0x0) = *(s16 *)(b + 0x10) >> 4;
        *(s16 *)(b + 0x8) += 0xC;
        if (*(s16 *)(b + 0x2) >= 0xF0) {
            b[0x3E]++;
        }
        break;
    case 3:
        if (b[0x3F] == 0) {
            a[4] = 2;
        }
        break;
    }
}

void func_8003A5E4(u8 *a, u8 *b)
{
    switch (b[0x3E]) {
    case 0:
        b[0x3E]++;
        if (*(s16 *)b < 0) {
            *(s16 *)(b + 0x10) = *(s16 *)b / 3 - 5;
        } else {
            *(s16 *)(b + 0x10) = *(s16 *)b / 3 + 5;
        }
        *(s16 *)(b + 0x12) = -0x100;
    case 1:
        *(s16 *)(b + 0x0) += *(s16 *)(b + 0x10);
        *(s16 *)(b + 0x2) += *(s16 *)(b + 0x12) >> 4;
        *(s16 *)(b + 0x12) += 0x20;
        if (*(s16 *)(b + 0x12) > 0x100) {
            *(s16 *)(b + 0x12) = -0xC0;
            b[0x3E]++;
        }
        break;
    case 2:
        *(s16 *)(b + 0x0) += *(s16 *)(b + 0x10);
        *(s16 *)(b + 0x2) += *(s16 *)(b + 0x12) >> 4;
        *(s16 *)(b + 0x12) += 0x18;
        if (*(s16 *)(b + 0x12) > 0xC0) {
            *(s16 *)(b + 0x12) = -0x80;
            b[0x3E]++;
        }
        break;
    case 3:
        *(s16 *)(b + 0x0) += *(s16 *)(b + 0x10);
        *(s16 *)(b + 0x2) += *(s16 *)(b + 0x12) >> 4;
        *(s16 *)(b + 0x12) += 0x10;
        if (*(s16 *)(b + 0x12) > 0x80) {
            b[0x3E]++;
        }
        break;
    case 4:
        if (b[0x3F] == 0) {
            a[4] = 2;
        }
        break;
    }
}

typedef struct ActorY36 { u8 pad0[0x36]; s16 y; } ActorY36;
void func_8003A790(u8 *a)
{
    s32 i;

    switch (a[5]) {
    case 0:
        for (i = 0; i < a[8]; i++) {
            func_8003A290(a, ((PartOwner *)a)->parts[i]);
        }
        ((ActorY36 *)a)->y -= 0x10;
        if (((ActorY36 *)a)->y < D_801003F8 + 8) {
            ((ActorY36 *)a)->y = D_801003F8 + 8;
            a[0x5E] = 1;
        }
        break;
    case 1:
        a[5]++;
        *(s16 *)(a + 0x40) = 0x3C;
        for (i = 0; i < a[8]; i++) {
            ((PartOwner *)a)->parts[i][0x3E] = 0;
        }
    case 2:
        if (--*(s16 *)(a + 0x40) == -1) {
            for (i = 0; i < a[8]; i++) {
                ((PartOwner *)a)->parts[i][0x3E] = 0;
            }
            a[0x5E] = 2;
            a[5]++;
        } else {
            for (i = 0; i < a[8]; i++) {
                func_8003A3E8(a, ((PartOwner *)a)->parts[i]);
            }
        }
        break;
    case 3:
        for (i = 0; i < a[8]; i++) {
            func_8003A5E4(a, ((PartOwner *)a)->parts[i]);
        }
        break;
    }
}

void func_8003A9A0(u8 *a)
{
    s32 i;

    switch (a[5]) {
    case 0:
        for (i = 0; i < a[8]; i++) {
            func_8003A290(a, ((PartOwner *)a)->parts[i]);
        }
        ((ActorY36 *)a)->y -= 0x10;
        if (((ActorY36 *)a)->y < D_801003F8 + 8) {
            ((ActorY36 *)a)->y = D_801003F8 + 8;
            a[0x5E] = 1;
        }
        break;
    case 1:
        *(s16 *)(a + 0x40) = 0x28;
        a[5]++;
        for (i = 0; i < a[8]; i++) {
            ((PartOwner *)a)->parts[i][0x3E] = 0;
        }
    case 2:
        if (--*(s16 *)(a + 0x40) == -1) {
            for (i = 0; i < a[8]; i++) {
                ((PartOwner *)a)->parts[i][0x3E] = 0;
            }
            func_80040AA4(*(s16 *)(a + 0x60), 2);
            D_800ED058_93c7[0x14]++;
            a[5]++;
        } else {
            for (i = 0; i < a[8]; i++) {
                func_8003A3E8(a, ((PartOwner *)a)->parts[i]);
            }
        }
        break;
    case 3: case 4:
        a[5]++;
    case 5:
        a[0x5E] = 2;
        for (i = 0; i < a[8]; i++) {
            func_8003A470(a, ((PartOwner *)a)->parts[i]);
        }
        *(s16 *)(a + 0x36) -= 4;
        break;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_8003ABE4);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8003AD48);

INCLUDE_ASM("asm/main/nonmatchings/main", f_ApplyActorSpriteUvOrientation);

INCLUDE_ASM("asm/main/nonmatchings/main", f_BuildActorSpriteQuadVertices);

INCLUDE_ASM("asm/main/nonmatchings/main", f_ProjectAndQueueFourVertexPrimitive);

extern u8 D_1F800247;
void f_DrawActorModelByRenderMode(u8 *a);
void f_UpdateAndDrawTombaModel(void) {
    u8 *a = D_800E7E80_f78d;

    if (a[0xD] & 0xD0) {
        a[0xD] |= 2;
        if (!(a[0xD] & 0x20)) {
            if (a[0xD] & 0x10) {
                u8 p = D_1F800247;
                if (!(p & 0x30) && (p & 3) >= 2) {
                    a[0x18] = 0xD0;
                    a[0x19] = 0xD0;
                    a[0x1A] = 0xD0;
                } else if (a[0xD] & 0x80) {
                    a[0x18] = ((s16)rsin((D_1F800247 & 0xF) << 7) >> 6) + 0x30;
                    a[0x19] = 0x20;
                    a[0x1A] = 0x20;
                } else if (a[0xD] & 0x40) {
                    a[0x18] = 0x20;
                    a[0x19] = 0x20;
                    a[0x1A] = 0x20;
                } else {
                    a[0x18] = 0x80;
                    a[0x19] = 0x80;
                    a[0x1A] = 0x80;
                }
            } else {
                s32 v;
                if (a[0xD] & 0x80) {
                    v = ((s16)rsin((D_1F800247 & 0xF) << 7) >> 6) + 0x10;
                } else {
                    v = 0;
                }
                a[0x18] = v + 0x20;
                a[0x19] = 0x20;
                a[0x1A] = 0x20;
            }
        }
    } else {
        a[0xD] = 0;
    }
    func_800597AC(a);
    if (a[1] != 0) {
        u8 s = a[8];

        if ((*(u16 *)(a + 0x17E) & 0x20) && a[0x179] != 0) {
            a[8] = a[9];
        }
        f_DrawActorModelByRenderMode(a);
        a[8] = s;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_8003B704);

extern u8 D_1F800136;
extern s8 D_1F800144[];
extern s8 D_1F800146[];
extern s8 D_1F80013C[];
extern s8 D_1F800140[];
extern u8 D_800F2410;
void f_DrawClass2And9ActorRenderQueue(void)
{
    s32 n;
    u8 **list;
    u8 *e;
    u16 cnt;
    void *old;

    if (D_1F800136 == 0) {
        cnt = *(u16 *)D_1F800144;
        *(u16 *)D_1F800144 = 0;
        old = *(void **)D_1F80013C;
        *(void **)D_1F80013C = &D_800F2410;
        *(u16 *)D_1F800146 = cnt;
        *(void **)D_1F800140 = old;
    }
    n = *(s16 *)D_1F800146;
    list = *(u8 ***)D_1F800140;
    while (n != 0) {
        e = *list++;
        n--;
        if (e[1] != 0) {
            switch (e[0xB]) {
            case 0: case 15: case 64: case 79: case 128: case 143:
                f_DrawActorModelByRenderMode(e);
                if (e[0xB] & 0x40) {
                    func_8002AE0C(e, 0x50, 0);
                } else if (e[0xB] & 0x80) {
                    func_8002AE0C(e, *(s16 *)(e + 0x80), 0);
                }
                break;
            case 1: case 65: case 129:
                func_80122974(e);
                if (e[0xB] & 0x40) {
                    func_8002AE0C(e, 0x50, 0);
                } else if (e[0xB] & 0x80) {
                    func_8002AE0C(e, *(s16 *)(e + 0x80), 0);
                }
                break;
            case 16:
                f_DrawActorSpritePartsWithZRotation(e);
                break;
            case 17:
                f_DrawActorSpritePartsWithScaleAndZRotation(e);
                break;
            case 18:
                func_8003C5F8(e);
                break;
            case 19:
                func_8003C788(e);
                break;
            case 21:
                f_DrawActorSpritePartsWithZRotation(e);
            case 22:
                (*(void (**)(u8 *))(e + 0x7C))(e);
                break;
            case 32:
                (*(void (**)(u8 *))(e + 0x18))(e);
                break;
            }
        }
    }
}

extern s8 D_1F800150[];
extern s8 D_1F800152[];
extern s8 D_1F800148[];
extern s8 D_1F80014C[];
extern u8 D_800F26C8;
void f_DrawClass4ActorRenderQueue(void)
{
    s32 n;
    u8 **list;
    u8 *e;
    u16 cnt;
    void *old;
    u8 area;

    if (D_1F800136 == 0) {
        cnt = *(u16 *)D_1F800150;
        *(u16 *)D_1F800150 = 0;
        old = *(void **)D_1F800148;
        *(void **)D_1F800148 = &D_800F26C8;
        *(u16 *)D_1F800152 = cnt;
        *(void **)D_1F80014C = old;
    }
    n = *(s16 *)D_1F800152;
    list = *(u8 ***)D_1F80014C;
    while (n != 0) {
        e = *list++;
        n--;
        if (e[1] != 0) {
            switch (e[0xB]) {
            case 0: case 15:
                f_DrawActorModelByRenderMode(e);
                break;
            case 1:
                area = D_800BF870.unk0;
                if (area == 0) {
                    func_801341E8(e);
                } else if (area == 6) {
                    func_80123C14(e);
                }
                break;
            case 2:
                area = D_800BF870.unk0;
                if (area == 1) {
                    func_80129114(e);
                } else if (area == 6) {
                    func_80120D2C(e);
                } else if (area == 7) {
                    func_8011AD44(e);
                } else if (area == 10) {
                    func_80115338(e);
                } else if (area == 15) {
                    func_80117984(e);
                }
                break;
            case 3:
                func_80136748(e);
                break;
            case 16:
                f_DrawActorSpritePartsWithZRotation(e);
                break;
            case 23:
                (*(void (**)(u8 *))(e + 0x7C))(e);
            case 17:
                f_DrawActorSpritePartsWithScaleAndZRotation(e);
                break;
            case 21:
                f_DrawActorSpritePartsWithZRotation(e);
            case 22:
                (*(void (**)(u8 *))(e + 0x7C))(e);
                break;
            case 32:
                (*(void (**)(u8 *))(e + 0x18))(e);
                break;
            }
        }
    }
}

extern s8 D_1F80028C[];
extern s8 D_1F80015E[];
extern s8 D_1F800158[];
void f_DrawClass5ActorRenderQueue(void)
{
    s32 n;
    u8 **list;
    u8 *e;
    u16 cnt;
    void *old;

    if (D_1F800136 == 0) {
        cnt = *(u16 *)D_1F80015C;
        *(u16 *)D_1F80015C = 0;
        old = *(void **)D_1F800154;
        *(void **)D_1F800154 = &D_800F2738_2edb;
        *(u16 *)D_1F80015E = cnt;
        *(void **)D_1F800158 = old;
    }
    n = *(s16 *)D_1F80015E;
    list = *(u8 ***)D_1F800158;
    while (n != 0) {
        e = *list++;
        n--;
        if (e[1] != 0) {
            switch (e[0xB]) {
            case 0: case 15:
                f_DrawActorModelByRenderMode(e);
                break;
            case 16:
                f_DrawActorSpritePartsWithZRotation(e);
                break;
            case 17:
                f_DrawActorSpritePartsWithScaleAndZRotation(e);
                break;
            case 18:
                func_8003C5F8(e);
                break;
            case 19:
                func_8003C788(e);
                break;
            case 31:
                if (D_800BF870.unk0 == 20) {
                    func_8010FC70(e);
                } else {
                    func_8004CC88(e);
                }
                break;
            }
        }
    }
}

void f_DrawPresentationActorList(void)
{
    u8 *a;
    u8 *next;
    s16 *t;
    u8 prim[0x28];
    s16 v[16];

    a = D_800F2624_9bdb;
    while (a != NULL) {
        next = *(u8 **)(a + 0x24);
        if (a[1] != 0) {
            switch (a[0xB]) {
            case 0:
            case 15:
                f_DrawActorModelByRenderMode(a);
                break;
            case 1:
                func_8003F174(a, 0);
                break;
            case 2:
                func_8003EF9C(a);
                break;
            case 4:
                func_80039F4C(a);
                break;
            case 3:
                func_8012A43C(a);
                break;
            case 5:
                func_801295B4(a);
                break;
            case 6:
                func_80129114(a);
                break;
            case 7:
                func_8013DD58(a);
                break;
            case 8:
                func_800726D4(a);
                break;
            case 16:
                f_DrawActorSpritePartsWithZRotation(a);
                break;
            case 17:
                f_DrawActorSpritePartsWithScaleAndZRotation(a);
                break;
            case 18:
                func_8003C5F8(a);
                break;
            case 19:
                func_8003C788(a);
                break;
            case 20:
                if (D_800BF870.unk0 == 4) {
                    func_8011BE5C(a);
                    break;
                }
                t = *(s16 **)(a + 0x38);
                if (t != NULL) {
                    f_ApplyActorSpriteUvOrientation(prim, *(u8 * volatile *)(a + 0x3C) + *(s16 *)(*(u8 * volatile *)(a + 0x3C) + (*t << 2) + 2), 0);
                    prim[7] = 0x2D;
                    v[0] = *(s16 *)(a + 0x60);
                    v[1] = *(s16 *)(a + 0x62);
                    v[2] = *(s16 *)(a + 0x64);
                    v[4] = *(s16 *)(a + 0x66);
                    v[5] = *(s16 *)(a + 0x68);
                    v[6] = *(s16 *)(a + 0x6A);
                    v[8] = *(s16 *)(a + 0x6C);
                    v[9] = *(s16 *)(a + 0x6E);
                    v[10] = *(s16 *)(a + 0x70);
                    v[12] = *(s16 *)(a + 0x72);
                    v[13] = *(s16 *)(a + 0x74);
                    v[14] = *(s16 *)(a + 0x76);
                    SetRotMatrix(D_1F8000F8);
                    SetTransMatrix(D_1F8000F8);
                    f_ProjectAndQueueFourVertexPrimitive(prim, v, 0x10);
                }
                break;
            case 32:
                (*(void (**)(u8 *))(a + 0x18))(a);
                break;
            }
        }
        a = next;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/main", f_DrawActorSpritePartsWithZRotation);

INCLUDE_ASM("asm/main/nonmatchings/main", f_DrawActorSpritePartsWithScaleAndZRotation);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8003C5F8);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8003C788);

INCLUDE_ASM("asm/main/nonmatchings/main", f_DrawActorSpriteParts);

void f_DrawActorModelByRenderMode(u8 *a)
{
    void *old;
    void *end;
    s32 flag;

    flag = a[0xB] == 0xF;
    *(u8 **)D_1F80028C = a;
    switch (a[0xD] & 0xB) {
    case 0: case 4:
        f_BuildActorModelPartPrimitives(a, flag);
        break;
    case 2:
        old = D_800BF544;
        f_BuildActorModelPartPrimitives(a, flag);
        func_8003D584(a, old, D_800BF544);
        break;
    case 8:
        old = D_800BF544;
        f_BuildActorModelPartPrimitives(a, flag);
        func_8003F344(a, old, D_800BF544);
        break;
    case 1:
        old = D_800BF544;
        f_BuildActorModelPartPrimitives(a, flag);
        end = D_800BF544;
        if (a[0x1B] != 0) {
            func_8003F3F4(a, old, end);
        } else {
            func_8003F4C4(a, old, end);
        }
        break;
    case 3:
        old = D_800BF544;
        f_BuildActorModelPartPrimitives(a, flag);
        func_8003F594(a, old, D_800BF544);
        break;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/main", f_BuildActorModelPartPrimitives);

void f_DrawCurrentAreaEnvironment(void *a)
{
    switch (D_800BF870.unk0) {
    case 0:
        func_801401B8(a);
        break;
    case 1:
        func_80132358(a);
        break;
    case 2:
        func_80124CB8(a);
        break;
    case 4:
        func_801185F0(a);
        break;
    case 5:
        func_8013606C(a);
        break;
    case 6:
        func_8013CD34(a);
        break;
    case 7:
        func_8012DA14(a);
        break;
    case 8:
        func_8012A7CC(a);
        break;
    case 10:
        func_8011024C(a);
        break;
    case 11:
        func_80113050(a);
        break;
    case 12:
        func_80113DB4(a);
        break;
    case 13:
        func_80113628(a);
        break;
    case 14:
        func_80114320(a);
        break;
    case 15:
        func_80115364(a);
        break;
    case 16:
        func_8010C2A4(a);
        break;
    case 17:
        func_8010B5BC(a);
        break;
    case 18:
        func_8010BA40(a);
        break;
    case 19:
        func_8010AA20(a);
        break;
    case 20:
        func_80115F1C(a);
        break;
    case 21:
        func_8010B0B8(a);
        break;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/main", f_DrawTemplateEffectSlot);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8003D584);

void f_DrawCurrentAreaTilemapLayer(void)
{
    if (D_800BF870.unk0 == 0x15) {
        func_8010BE30(D_800ED018_eeff);
        return;
    }
    if (D_800BF870.pad1[2] != 0) {
        return;
    }
    switch (D_800BF870.unk0) {
    case 0:
        func_80115598(D_800ED018_eeff);
        break;
    case 4:
        func_8013F0DC(D_800ED018_eeff);
        break;
    case 5:
        func_80136F28(D_800ED018_eeff);
        break;
    case 6:
        func_80141A94(D_800ED018_eeff);
        break;
    case 7:
        func_8012F938(D_800ED018_eeff);
        break;
    case 10:
        func_801142EC(D_800ED018_eeff);
        break;
    case 11:
        func_801141B0(D_800ED018_eeff);
        break;
    case 13:
        func_80116B9C(D_800ED018_eeff);
        break;
    case 15:
        func_80116778(D_800ED018_eeff);
        break;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_8003E030);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8003E264);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8003E448);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8003E894);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8003EA88);

extern u32 *D_800BF544_5fe3;
typedef struct { unsigned addr : 24; unsigned len : 8; } PTag_F264;
typedef struct { PTag_F264 tag; u32 code[2]; } DrMode_F264;
#define setaddr_(p, _addr) (((PTag_F264 *)(p))->addr = (u32)(_addr))
#define getaddr_(p) (u32)(((PTag_F264 *)(p))->addr)
#define addPrim_(ot, p) setaddr_(p, getaddr_(ot)), setaddr_(ot, p)
INCLUDE_ASM("asm/main/nonmatchings/main", func_8003EBE0);

void f_DrawActiveWorldActors(void)
{
    u8 *a = D_800F2738_2edb;
    u8 *next;

    while (a != NULL) {
        next = *(u8 **)(a + 0x24);
        if (a[1] != 0) {
            switch (a[0xB]) {
            case 0: case 15:
                f_DrawActorModelByRenderMode(a);
                break;
            case 1:
                f_DrawActorModelByRenderMode(a);
                func_8003B704(a);
                break;
            case 16:
                f_DrawActorSpritePartsWithZRotation(a);
                if (a[2] == 1) {
                    func_8003B704(a);
                }
                break;
            case 32:
                (*(void (**)(u8 *))(a + 0x18))(a);
                break;
            }
        }
        a = next;
    }
}

void func_8003EF9C(u8 *a)
{
    s32 flag = a[0xB] == 0xF;
    void *old;

    switch (a[0xD] & 0xF) {
    case 0:
        func_8003F07C(a, flag);
        break;
    case 2:
        old = D_800BF544;
        func_8003F07C(a, flag);
        func_8003D584(a, old, D_800BF544);
        break;
    }
}

extern u8 D_800EC188;
void f_DrawActiveTemplateEffectSlots(void) {
    s32 var_s1;
    u8 *var_s0;

    var_s1 = 0;
    var_s0 = &D_800EC188;
    do {
        if (*var_s0 != 0) {
            f_DrawTemplateEffectSlot(var_s0);
        }
        var_s1 += 1;
        var_s0 += 0x40;
    } while (var_s1 < 0x28);
}

void f_DrawModelPrimitiveStreamForCurrentArea(u32 *a, void *b, s32 c);
void func_8003F07C(u8 *a, s32 b)
{
    s32 i;

    if (a[8] == 0) {
        return;
    }
    gte_SetRotMatrix(D_1F8000F8);
    gte_SetTransMatrix(D_1F8000F8);
    for (i = 0; i < a[9]; i++) {
        if (i >= a[8]) {
            return;
        }
        f_DrawModelPrimitiveStreamForCurrentArea(*(u32 **)(*(u8 **)(a + 0xC0 + i * 4) + 0x40), D_800ED8C8, b);
    }
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_8003F174);

void func_8003F264(void)
{
    DrMode_F264 *p;
    s32 n = D_800A3B0C_b8ee;

    if (n >= 3) {
        return;
    }
    if (n == 0) {
        return;
    }
    p = (DrMode_F264 *)D_800BF544_5fe3;
    SetDrawStp(p, 1);
    addPrim_(&D_800ED8C8[0x7FF], p);
    p++;
    D_800BF544_5fe3 = (u32 *)p;
}

u8 func_8003F2F8(u8 a, u8 b)
{
    s32 d = a - 0x7F;
    s32 s;
    u8 r;

    s = b + d;
    r = s;
    if (s < 0) {
        r = 0;
    }
    return r;
}

u8 func_8003F31C(u8 a, u8 b)
{
    s32 s;
    u8 r;

    s = a + b;
    r = s;
    if (s >= 0x100) {
        r = 0xFF;
    }
    return r;
}

void func_8003F344(u8 *a, u8 *p, u8 *end)
{
    while (p < end) {
        switch (p[7] & 0xFC) {
        case 0x3C:
            *(u16 *)(p + 0xE) = *(u16 *)(a + 0x5C);
            p += 0x34;
            break;
        case 0x24:
            *(u16 *)(p + 0xE) = *(u16 *)(a + 0x5C);
            p += 0x20;
            break;
        case 0x2C:
        case 0x34:
            *(u16 *)(p + 0xE) = *(u16 *)(a + 0x5C);
            p += 0x28;
            break;
        case 0x30:
            p += 0x1C;
            break;
        case 0x38:
            p += 0x24;
            break;
        case 0x20:
            p += 0x14;
            break;
        case 0x28:
            p += 0x18;
            break;
        }
    }
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_8003F3F4);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8003F4C4);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8003F594);

extern u8 D_1F800234_8e95;
void f_DrawModelPrimitiveStreamForCurrentArea(u32 *a, void *b, s32 c)
{
    if (D_1F800234_8e95 == 0 && !(c & 1)) {
        switch (D_800BF870.unk0) {
        case 0:
            func_80146478(a, b);
            return;
        case 1:
            func_80132DC0(a, b);
            return;
        case 2:
            func_8012555C(a, b);
            return;
        case 4:
            func_8013DAFC(a, b);
            return;
        case 5:
            func_801362CC(a, b);
            return;
        case 6:
            func_8013D568(a, b);
            return;
        case 7:
            func_8012E1A0(a, b);
            return;
        case 8:
            func_8012A9DC(a, b);
            return;
        case 20:
            func_80116B14(a, b);
            return;
        case 21:
            func_8010B1B8(a, b);
            return;
        }
    }
    func_800803DC(a, b);
}

s32 func_8003F7A0(void *v, void *sxy)
{
    s32 z;

    gte_ldv0(v);
    gte_rtps();
    gte_stsxy(sxy);
    gte_stszotz(&z);
    return z;
}

#define gte_rtpt_b() __asm__ volatile("nop; nop; .word 0x4A280030")
#define gte_nclip_b() __asm__ volatile("nop; nop; .word 0x4B400006")
#define gte_avsz4_b() __asm__ volatile("nop; nop; .word 0x4B68002E")
#define gte_rtps_b2() __asm__ volatile("nop; nop; .word 0x4A180001")
s32 func_8003F7D8(u8 *p, u8 *v, s32 *flag)
{
    s32 otz;

    gte_ldv3c(v);
    gte_rtpt_b();
    gte_stflg(flag);
    if (*flag < 0) {
        return -1;
    }
    gte_stsxy3_g3(p);
    gte_nclip_b();
    gte_stopz(flag);
    gte_ldv0(v + 0x18);
    gte_rtps_b2();
    gte_stflg(flag);
    if (*flag < 0) {
        return -1;
    }
    gte_stsxy(p + 0x20);
    gte_avsz4_b();
    gte_stotz(&otz);
    return otz;
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_8003F898);

extern M2C_UNK D_800F2418;
void func_8003F9A8(void) {
    func_8004FD30();
    func_80025D98();
    f_DrawClass5ActorRenderQueue();
    f_DrawActiveWorldActors();
    f_UpdateAndDrawTombaModel();
    f_DrawClass2And9ActorRenderQueue();
    f_DrawClass4ActorRenderQueue();
    f_DrawCurrentAreaEnvironment(&D_800F2418);
    f_DrawActiveTemplateEffectSlots();
    f_DrawCurrentAreaTilemapLayer();
    f_DrawPresentationActorList();
}

void func_8003FA1C(void) {
    f_UpdateAndDrawTombaModel();
    f_DrawPresentationActorList();
}

void func_8003FA44(void) {
    func_8004FD30();
    func_80025D98();
    f_DrawClass5ActorRenderQueue();
    f_DrawActiveWorldActors();
    f_UpdateAndDrawTombaModel();
    f_DrawClass2And9ActorRenderQueue();
    f_DrawClass4ActorRenderQueue();
    f_DrawPresentationActorList();
    f_DrawActiveTemplateEffectSlots();
}

void func_8003FAA4(u8 *a)
{
    s32 v;

    if (a[0xB] & 0x40) {
        v = 0x50;
    } else if (a[0xB] & 0x80) {
        v = *(s16 *)(a + 0x80);
    } else {
        return;
    }
    func_8002AE0C(a, v, 0);
}

void func_8003FAE8(s16 z, s16 stp)
{
    DrMode_F264 *p = (DrMode_F264 *)D_800BF544_5fe3;

    SetDrawStp(p, stp);
    addPrim_(&D_800ED8C8[z], p);
    p++;
    D_800BF544_5fe3 = (u32 *)p;
}

void func_8003FB84(void) {
    *((s32 *)D_1F80008C) = 0xFF;
}

extern s8 D_1F80008C[];
extern s8 D_1F800090[];
extern s8 D_1F800098[];
extern s8 D_800A3B0C;
void func_8003FB94(void) {
    *((s32 *)D_1F80008C) = 0;
    *((s32 *)D_1F800090) = 0;
    *((s32 *)D_1F800094) = 0;
    *((s32 *)D_1F800098) = 0;
    D_800A3B0C = 2;
}

void func_8003FBC4(void *arg0) {
    f_ResolveActorAreaPlanePosition();
    f_ResolveActorTerrainSurfaceOrientation(arg0);
    M2C_FIELD(arg0, u16 *, 0x56) = (u16) *(u16 *)0x1F8001A0;
}

extern u16 D_1F8001A0_6940;
extern char D_80015458[];
extern char D_8001546C[];
extern s32 D_800BE1E0[];
typedef struct { u8 b[8]; } Bytes8_EE0;
extern Bytes8_EE0 D_80016EE0;
extern u8 *D_800E8098;
extern u8 *D_800F239C;
extern u8 *D_800F2624_9bdb;
typedef struct { u32 pos; u32 size; char name[16]; } CdFileLite;
void func_8003FC00(u8 *a)
{
    f_ResolveActorAreaPlanePosition(a);
    do {
        *(s16 *)(a + 0x32) += 10;
    } while (f_ProbeActorTerrainAlongFacing(a, 0, (s16)(*(s16 *)(a + 0x86) - *(s16 *)(a + 0x84))) == 0);
    f_ResolveActorTerrainSurfaceOrientation(a);
    {
        u16 x = D_1F8001A0_6940;
        u16 y = D_1F8001A2;
        *(u16 *)(a + 0x56) = x;
        *(u16 *)(a + 0x58) = y;
    }
}

void func_8003FC78(void *arg0) {
    M2C_FIELD(arg0, s16 *, 0x58) = 0;
    M2C_FIELD(arg0, s16 *, 0x56) = (s16) (M2C_FIELD(arg0, u8 *, 0x2A) * 0x10);
}

s32 func_8003FC8C(u8 *a)
{
    u8 *g = D_800BF808;

    if (g[0xE] != 1) {
        return 0;
    }
    if (g[0xF] != *(s16 *)(a + 0x6A)) {
        return 0;
    }
    f_ResolveActorAreaPlanePosition();
    f_ResolveActorTerrainSurfaceOrientation(a);
    *(u16 *)(a + 0x56) = D_1F8001A0_6940;
    *(u16 *)(a + 0x32) = *(u16 *)(g + 0xA);
    return 1;
}

extern s8 D_1F80017C[];
void func_8003FD10(void *arg0) {
    u16 temp_v0;
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 6);
    switch (temp_v1) {                              /* irregular */
    case 0:
        if (M2C_FIELD(arg0, u8 *, 0x2B) != 0) {
            M2C_FIELD(arg0, u8 *, 6) = 1U;
            M2C_FIELD(arg0, u8 *, 0x2B) = 0U;
            M2C_FIELD(arg0, u16 *, 0x40) = 0x10U;
            return;
        }
        return;
    case 1:
        if (M2C_FIELD(arg0, u8 *, 0x2B) != 0) {
            M2C_FIELD(arg0, u8 *, 0x2B) = 0U;
            M2C_FIELD(arg0, u16 *, 0x40) = 0x10U;
        }
        temp_v0 = M2C_FIELD(arg0, u16 *, 0x40) - 1;
        M2C_FIELD(arg0, u16 *, 0x40) = temp_v0;
        if ((s16) temp_v0 == -1) {
            M2C_FIELD(arg0, u8 *, 6) = (u8) (M2C_FIELD(arg0, u8 *, 6) - 1);
        }
        M2C_FIELD(M2C_FIELD(arg0, void **, 0xC0), s16 *, 2) = (s16) ((*((u16 *)D_1F80017C) & 1) * 6);
        M2C_FIELD(M2C_FIELD(arg0, void **, 0xC0), s16 *, 0) = (s16) (((rand() & 3) - 2) * 6);
        break;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_8003FE00);

extern s8 D_1F80017C[];
void func_8003FED8(void *arg0) {
    u16 temp_v0;
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 6);
    switch (temp_v1) {                              /* irregular */
    case 0:
        f_PlaySoundEffect(0x19, 0, 0);
        M2C_FIELD(arg0, s8 *, 0) = 1;
        M2C_FIELD(arg0, u16 *, 0x40) = 0x10U;
        M2C_FIELD(arg0, u8 *, 6) = (u8) (M2C_FIELD(arg0, u8 *, 6) + 1);
        break;
    case 1:
        temp_v0 = M2C_FIELD(arg0, u16 *, 0x40) - 1;
        M2C_FIELD(arg0, u16 *, 0x40) = temp_v0;
        if ((s16) temp_v0 == -1) {
            M2C_FIELD(arg0, s8 *, 5) = 0;
            M2C_FIELD(arg0, u8 *, 6) = 0U;
        }
        M2C_FIELD(M2C_FIELD(arg0, void **, 0xC0), s16 *, 2) = (s16) ((*((u16 *)D_1F80017C) & 1) * 6);
        M2C_FIELD(M2C_FIELD(arg0, void **, 0xC0), s16 *, 0) = (s16) (((rand() & 3) - 2) * 6);
        break;
    }
    if (M2C_FIELD(arg0, u8 *, 0x5E) == 2) {
        M2C_FIELD(M2C_FIELD(arg0, void **, 0x10), s8 *, 0x5E) = 0;
    }
}

void func_8004AAC4(u8 *a);
void func_8004C238(u8 *a);
void func_8003FFCC(u8 *a)
{
    u8 *n;
    u8 *g;
    u8 *c;

    switch (a[6]) {
    case 0:
        f_PlaySoundEffect(0x1A, 0, 0);
        *(u16 *)(a + 0x90) = 0x100;
        a[6]++;
        if (*(s16 *)(a + 0x64) == 1) {
            n = f_AllocateActor(a, a[0x68], 5, 0);
            *(void **)(n + 0x1C) = func_8004AAC4;
        } else {
            n = f_AllocateActor(a, a[0x68], 5, 4);
            *(void **)(n + 0x1C) = func_8004C238;
        }
        if (a[0x28] & 0x80) {
            n[0x28] |= 0x80;
            *(u16 *)(n + 0x6A) = *(u16 *)(a + 0x6A);
        } else {
            *(u16 *)(n + 0x6A) = 0;
        }
        if (D_800BF870.unk0 == 2 || D_800BF870.unk0 == 7) {
            *(s32 *)(n + 0x2C) = *(s32 *)(a + 0x2C);
            *(s32 *)(n + 0x34) = *(s32 *)(a + 0x34);
            *(s32 *)(n + 0x30) = *(s32 *)(a + 0x30) - 0x28;
        } else {
            g = D_800E7E80_f78d;
            *(s32 *)(n + 0x2C) = *(s32 *)(g + 0x2C);
            *(s32 *)(n + 0x34) = *(s32 *)(g + 0x34);
            *(s32 *)(n + 0x30) = *(s32 *)(a + 0x30) - 0x28;
            n[0x2A] = g[0x2A];
        }
        n[0x46] = a[0x46];
        n[3] = a[0x60];
        n[0x5E] = a[0x62];
        *(s16 *)(n + 0x60) = 1;
        *(u16 *)(n + 0x62) = *(u16 *)(a + 0xE);
        *(u16 *)(n + 0x64) = *(u16 *)(a + 0x64);
        *(u16 *)(n + 0x66) = *(u16 *)(a + 0x66);
        *(s16 *)(n + 0x4A) = 0;
        break;
    case 1:
        c = *(u8 **)(a + 0xC4);
        *(u16 *)(c + 8) -= *(u16 *)(a + 0x90);
        *(u16 *)(a + 0x90) -= 0x18;
        if (*(s16 *)(*(u8 **)(a + 0xC4) + 8) < -0x4FF) {
            if (a[3] == 0) {
                f_UpdateEvent(0x38);
            }
            switch (a[0x5E]) {
            case 0:
            case 5:
                a[5] = 3;
                break;
            case 1:
            case 4:
            case 6:
                a[5] = 4;
                break;
            case 2:
                a[5] = 4;
                break;
            case 7:
                a[5] = 5;
                break;
            }
            a[6] = 0;
        }
        break;
    }
}

s32 f_ProbeActorTerrainAlongFacing(s32 arg0, s32 arg1, s32 arg2);
void func_8004022C(u8 *a)
{
    switch (a[6]) {
    case 0:
        *(s16 *)(a + 0x4A) = 0x1000;
        a[6] = 1;
        *(s16 *)(a + 0x50) = 0x200;
        break;
    case 1:
        if (a[0x29] != 0) {
            a[6] = 2;
            break;
        }
        *(s32 *)(a + 0x30) += *(s16 *)(a + 0x4A) << 8;
        *(u16 *)(a + 0x4A) += *(u16 *)(a + 0x50);
        if (*(s16 *)(a + 0x4A) > 0x3000) {
            *(s16 *)(a + 0x4A) = 0x3000;
        }
        f_ResolveActorAreaPlanePosition(a);
        if (a[0x29] != 0 || f_ProbeActorTerrainAlongFacing((s32)a, 0, (s16)(*(u16 *)(a + 0x86) - *(u16 *)(a + 0x84)))) {
            a[6]++;
        }
        break;
    case 2:
        f_SpawnEffectTemplateInstances(*(void **)(*(u8 **)(a + 0xC0) + 0x40), a + 0x2C, 0x700, 8);
        f_PlaySoundEffect(0xC, 0, 0);
        a[4] = 3;
        if (a[0x5E] == 5) {
            ((Counter48_808 *)D_800BF808)->n--;
        }
        break;
    }
}

void func_80040390(u8 *a)
{
    if (a[0x29] != 0) {
        f_SpawnEffectTemplateInstances(*(void **)(*(u8 **)(a + 0xC0) + 0x40), a + 0x2C, 0x700, 8);
        f_PlaySoundEffect(0xC, 0, 0);
        a[4] = 3;
        if (a[0x5E] == 5) {
            ((Counter48_808 *)D_800BF808)->n--;
        }
    }
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_80040410);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80040558);

s32 f_GetEventAPReward(s32 event, s32 low)
{
    s32 v = D_800A33C8[event].ap;

    if (low == 0) {
        v >>= 4;
    } else {
        v &= 0xF;
    }
    return D_800A3B38[v];
}

void func_8003AD48(void);
u8 *func_800727D4(void *owner, s32 ev, s32 kind);
extern u8 D_800E8008_f2dc[];
u8 *func_80040AA4(s32 x, s32 kind)
{
    u8 *a = (u8 *)f_AllocateActorRecordByType(4, 3, 1);

    if (a != NULL) {
        *(void **)(a + 0x1C) = func_8003AD48;
        a[2] = 0xB;
        a[3] = kind;
        *(s16 *)(a + 0x60) = x;
        a[0x28] |= 0x80;
        D_800BF808[0x41]++;
        ((void (*)(u8 *, s32, s32))func_800727D4)(a, x, kind);
        return a;
    }
    return NULL;
}

typedef struct { s32 w[8]; } PopupReq32;
extern s16 D_800E7FEE;
typedef struct { void *t[8]; } AudioBanks_05C;
extern AudioBanks_05C D_8001005C;
extern u8 *D_1F800224;
extern u16 D_800E7EAE;
extern u16 D_800E7EB6;
s32 f_StartEvent(s32 ev)
{
    u8 *g;
    s32 r;

    if (D_800E7FEE == 0) {
        return -1;
    }
    g = (u8 *)&D_800BF870;
    if (g[ev + 0x44] != 0) {
        return 0;
    }
    g[ev + 0x44] = 1;
    *(u16 *)(g + 0x38) += 1;
    r = f_GetEventAPReward(ev, 0);
    *(s32 *)(g + 4) += r;
    D_800ED058_93c7[D_800ED058_93c7[0x15] + 0x16] = ev;
    D_800ED058_93c7[D_800ED058_93c7[0x15] + 0x1C] = 0;
    D_800ED058_93c7[0x15] += 1;
    return 1;
}

s32 f_UpdateEvent(s32 ev)
{
    u8 *g;
    s32 r;

    if (D_800E7FEE == 0) {
        return -1;
    }
    g = (u8 *)&D_800BF870;
    if (g[ev + 0x44] == 0) {
        *(u16 *)(g + 0x38) += 1;
    }
    if (g[ev + 0x44] != 0xFF) {
    g[ev + 0x44] = 0xFF;
    *(u16 *)(g + 0x3A) += 1;
    r = f_GetEventAPReward(ev, 1);
    *(s32 *)(g + 4) += r;
    D_800ED058_93c7[D_800ED058_93c7[0x15] + 0x16] = ev;
    D_800ED058_93c7[D_800ED058_93c7[0x15] + 0x1C] = 1;
    D_800ED058_93c7[0x15] += 1;
    return 1;
    }
    return 0;
}

extern u8 D_800BF80E_58ec;
extern s32 D_1F800184;
typedef struct { u8 pad[0x48]; s32 bits; } Bits48_808;
void f_InitializeActorScript(u8 *a, void *skel, u16 *cmd)
{
    *(void **)(a + 0x7C) = skel;
    a[0x46] = 0xFF;
    *(s32 *)(a + 0x10) = 0;
    a[0x70] = 0;
    a[0x78] = 0;
    f_LoadActorScriptCommand(a, cmd);
    a[0x71] = 0;
    if (cmd[0] & 0x1000) {
        a[0x71] = 2;
    }
    if (cmd[0] & 0x4000) {
        a[0x71] |= 4;
    }
}

void f_LoadActorScript(void *arg0, u16 *arg1) {
    M2C_FIELD(arg0, s8 *, 0x70) = 0;
    M2C_FIELD(arg0, s8 *, 0x78) = 0;
    f_LoadActorScriptCommand();
    M2C_FIELD(arg0, u8 *, 0x71) = 0U;
    if (*arg1 & 0x1000) {
        M2C_FIELD(arg0, u8 *, 0x71) = 2U;
    }
    if (*arg1 & 0x4000) {
        M2C_FIELD(arg0, u8 *, 0x71) = (u8) (M2C_FIELD(arg0, u8 *, 0x71) | 4);
    }
}

extern u16 D_800A4582;
extern u16 D_800A457C[];
extern u16 D_1F800174_de41;
extern u8 D_800BF9B4[];
extern u8 D_800BF87D;
void f_LoadActorScriptCommand(u8 *a, u16 *cmd)
{
    *(u16 **)(a + 0x6C) = cmd;
    *(u16 *)(a + 0x72) = cmd[1];
    *(u16 *)(a + 0x74) = cmd[2];
    *(u16 *)(a + 0x76) = cmd[3];
    if (cmd[0] & 0x2000) {
        cmd += 4;
        *(u16 *)(a + 0x64) = cmd[0];
        *(u16 *)(a + 0x66) = cmd[1];
        *(u16 *)(a + 0x68) = cmd[2];
        *(u16 *)(a + 0x6A) = cmd[3];
    }
}

s32 func_80040E54(u8 *a, s32 b)
{
    u8 *cmd = *(u8 **)(a + 0x6C);
    u16 f = *(u16 *)cmd;
    s32 r = ((f & 0x1000) != 0) * 4;
    s32 g = (s16)f;

    switch (g & 0xE000) {
    case 0:
        f_LoadActorScriptCommand(a, (u16 *)(cmd + 8));
        break;
    case 0x2000:
        f_LoadActorScriptCommand(a, (u16 *)(cmd + 0x10));
        break;
    case 0x4000:
        if (b == 0) {
            f_LoadActorScriptCommand(a, *(u16 **)(cmd + 0xC));
            r++;
        } else {
            f_LoadActorScriptCommand(a, (u16 *)(cmd + 0x10));
        }
        break;
    case 0x6000:
        if (b == 0) {
            f_LoadActorScriptCommand(a, *(u16 **)(cmd + 0x14));
            r++;
        } else {
            f_LoadActorScriptCommand(a, (u16 *)(cmd + 0x18));
        }
        break;
    case 0x8000:
    case 0xA000:
    case 0xC000:
    case 0xE000:
        return 2;
    }
    if (g & 0x800) {
        r = 6;
    }
    return r;
}

extern u16 D_800BF89E;
s32 f_ApplyActorScriptTransition(u8 *a)
{
    s32 r;

    switch (((s32 (*)(u8 *))func_80040E54)(a)) {
    case 0:
        if (a[0x70] == 2) {
            a[0x71] = a[0x70];
            r = 1;
        } else {
            r = 0;
            a[0x71] = 0;
            a[0x70] = 0;
        }
        a[0x78] = 0;
        break;
    case 1:
        if (a[0x70] == 2) {
            a[0x71] = 6;
            r = 1;
        } else {
            r = 0;
            a[0x71] = 4;
            a[0x70] = 0;
        }
        a[0x78] = 0;
        break;
    case 2:
        r = 0;
        a[0x70] = 0xFF;
        a[0x71] = 0xFF;
        break;
    case 4:
        r = 1;
        a[0x71] = 2;
        a[0x78] = 0;
        break;
    case 5:
        r = 1;
        a[0x71] = 6;
        a[0x78] = 0;
        break;
    case 6:
        r = 0;
        a[0x71] = 0;
        a[0x70] = 0;
        a[0x78] = 0;
        break;
    case 3:
    default:
        r = -1;
        break;
    }
    return r;
}

#define SCRIPT_APPLY(a, k) ((s32 (*)(u8 *, s32))f_ApplyActorScriptTransition)(a, k)
s32 f_RunActorScriptInterpreter(u8 *a)
{
    s32 r;

    do {
        r = 0;
        if (*(s8 *)(a + 0x70) <= 0) {
            goto end;
        }
        switch (D_800A3B78[**(u16 **)(a + 0x6C) & 0x7FF](a)) {
        case 0:
            a[0x71] |= 1;
            return 1;
        case 1:
        case 3:
            r = SCRIPT_APPLY(a, 0);
            break;
        case 2:
            r = SCRIPT_APPLY(a, 1);
            break;
        }
    } while (r == 1);
end:
    return 0;
}

INCLUDE_ASM("asm/main/nonmatchings/main", f_PlaceActorOnTerrainSurface);

void func_800412CC(void *arg0) {
    M2C_FIELD(arg0, M2C_UNK (**)(), 0x74)();
}

s32 func_800412F4(void *arg0) {
    M2C_FIELD(arg0, s8 *, 0xBE) = (s8) (M2C_FIELD(arg0, u8 *, 0x72) & 1);
    return 1;
}

s32 f_ApplyActorOrientationToRotation(void *arg0, s32 arg1) {
    s32 var_v0;

    if (M2C_FIELD(arg0, u8 *, 0xBE) != 0) {
        M2C_FIELD(arg0, u16 *, 0x56) = (u16) ((M2C_FIELD(arg0, u16 *, 0x60) - 0x800) & 0xFFF);
        if (arg1 != 0) {
            var_v0 = (0x1000 - ((s32) (M2C_FIELD(arg0, u16 *, 0x62) << 0x10) >> 0x11)) & 0xFFF;
            goto block_5;
        }
    } else {
        M2C_FIELD(arg0, u16 *, 0x56) = (u16) M2C_FIELD(arg0, u16 *, 0x60);
        if (arg1 != 0) {
            var_v0 = (s32) (M2C_FIELD(arg0, u16 *, 0x62) << 0x10) >> 0x11;
block_5:
            M2C_FIELD(arg0, s16 *, 0x58) = (s16) var_v0;
        }
    }
    return 1;
}

extern s8 D_1F800214[];
extern u8 D_800BF808[];
typedef struct SoundHandle { u8 volume; u8 pad1[11]; } SoundHandle;
extern SoundHandle D_800BE238[];
u8 *f_SpawnAreaIndexedPersistentPickup(void *, s32, s32);
void func_80041378(u8 *actor)
{
    f_ApplyActorOrientationToRotation(actor, *(s16 *)(actor + 0x72));
}

INCLUDE_ASM("asm/main/nonmatchings/main", f_StepAngleTowardTarget);

s32 f_StepActorYawTowardAngle(s32 arg0, s16 arg1, s16 arg2) {
    return f_StepAngleTowardTarget(arg0 + 0x56, arg1, arg2);
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_80041468);

s32 func_8004162C(u8 *p)
{
    PartOwner *who;
    s32 idx;

    if (*(s16 *)(p + 0x72) & 0x8000) {
        who = D_1F800214_50e7;
    } else {
        who = (PartOwner *)p;
    }
    idx = *(u16 *)(p + 0x72) & 0x7FFF;
    if (*(s16 *)(p + 0x74) == -1) {
        *(s32 *)(who->parts[idx] + 0x40) = 0;
    } else {
        f_SetActorPartModel(who->parts[idx], *(s16 *)(p + 0x74), *(s16 *)(p + 0x76));
    }
    return 1;
}

s32 f_SetActorModelResources(void *p, s32 idx, s32 c)
{
    u8 *a = p;

    if ((s16)idx < 0) {
        *(s8 **)(a + 0x3C) = D_800ECF68;
        *(u8 **)(a + 0x7C) = D_80017FE8;
    } else {
        *(s8 **)(a + 0x3C) = D_800ECF58[(s16)idx];
        *(s32 *)(a + 0x7C) = c;
    }
    return 1;
}

void func_800416F0(u8 *actor)
{
    f_SetActorModelResources(actor, *(s16 *)(actor + 0x72), *(s32 *)(actor + 0x74));
}

s32 f_SetActorAnimation(s32 arg0, s32 arg1, s32 arg2) {
    M2C_FIELD(arg0, s8 *, 0x46) = (s8) arg1;
    M2C_FIELD(arg0, s8 *, 0x79) = 0;
    if ((s16) arg2 == 0) {
        f_StartActorSkeletalAnimation(arg0, M2C_FIELD(arg0, s32 *, 0x7C), arg1);
    } else {
        f_StartActorSkeletalAnimationBlend(arg0, M2C_FIELD(arg0, s32 *, 0x7C), arg1, (s32) (s16) arg2);
    }
    return 1;
}

s32 f_SetActorAnimationIfChanged(u8 *a, s32 anim, s16 c)
{
    if (a[0x46] != (u8)anim) {
        return f_SetActorAnimation((s32)a, anim, c);
    }
    return 1;
}

s32 f_PlaySoundEffect();
s32 func_8004179C(u8 *a)
{
    u8 *s;
    u16 f;
    s32 r;

    if (*(u16 *)(a + 0x72) & 1) {
        s = *(u8 **)D_1F800214;
    } else {
        s = a;
    }
    switch (a[0x78]) {
    case 0:
        if (*(s16 *)(a + 0x74) == -1) {
            *(s16 *)(a + 0x74) = a[0x7B];
        }
        f_SetActorAnimationIfChanged(s, *(s16 *)(a + 0x74), *(s16 *)(a + 0x76));
        if (!(*(u16 *)(a + 0x72) & 2)) {
            return 1;
        }
        if (!(**(u16 **)(a + 0x6C) & 0x2000)) {
            a[0x78] = 2;
        } else {
            a[0x78] = 1;
        }
        break;
    case 1:
        f = *(u16 *)(a + 0x66);
        if (!(*(s16 *)(a + 0x66) & 0x8000)) {
            if ((f & 0xFF) == (*(u8 **)(s + 0x38))[4]) {
                f_PlaySoundEffect(a[0x68], 0, 0);
                *(u16 *)(a + 0x66) |= 0x8000;
            }
        } else if ((f & 0xFF) != (*(u8 **)(s + 0x38))[4]) {
            *(u16 *)(a + 0x66) = f & 0x7FFF;
        }
    case 2:
        r = 1;
        if (s[0x79] == r) {
            return r;
        }
        break;
    }
    return 0;
}

s32 f_AdvanceActorAnimationAndStoreCompletion(void *arg0) {
    M2C_FIELD(arg0, s8 *, 0x79) = f_AdvanceActorSkeletalAnimation();
    return 1;
}

s32 f_ProbeActorTerrainAlongFacing(s32 arg0, s32 arg1, s32 arg2);
u8 func_80041938(u8 *a, s16 x, s16 z)
{
    s32 r;
    u8 t;

    if (a[0x29] == 0) {
        r = f_ProbeActorTerrainAlongFacing((s32)a, x, z);
        a[0x29] = r;
        if ((r & 0xFF) == 0) {
            return r;
        }
        t = r & 1;
        a[0x29] = t;
        if (t != 0) {
            a[0x29] = t | 0x80;
            f_ApplyTerrainProfileOrientationToActor(a);
            *(u16 *)(a + 0x62) = *(u16 *)0x1F8001A2;
        }
    }
    return a[0x29];
}

s32 func_800419C4(u8 *a, s16 b, s16 c)
{
    if (f_ProbeActorTerrainAlongFacing(a, b, c) != 1) {
        return 0;
    }
    f_ApplyTerrainProfileOrientationToActor(a);
    *(u16 *)(a + 0x62) = D_1F8001A2;
    return 1;
}

extern u8 D_800BF809;
extern u16 D_800ECF54;
s32 func_80041A1C(u8 *a, s32 flags)
{
    if ((D_1F800137_104c != 0 || D_800BF809 != 0) && (flags & 2)) {
        return 1;
    }
    *(s32 *)(a + 0x2C) += *(s16 *)(a + 0x48) * *(s16 *)(a + 0x44);
    *(s32 *)(a + 0x34) += *(s16 *)(a + 0x4C) * *(s16 *)(a + 0x44);
    if (!(flags & 1)) {
        *(s32 *)(a + 0x30) += *(s16 *)(a + 0x4A) * *(s16 *)(a + 0x44);
    }
    return 1;
}

extern s8 D_1F8001A0[];
s32 func_80041AC0(s32 arg0) {
    s32 temp_s1;

    temp_s1 = f_ResolveActorAreaPlanePosition(arg0);
    f_ApplyAreaPlaneDirectionToActor(arg0);
    M2C_FIELD(arg0, u16 *, 0x60) = (u16) *((u16 *)D_1F8001A0);
    return temp_s1;
}

INCLUDE_ASM("asm/main/nonmatchings/main", f_InitializeActorFixedStepMotion);

s32 f_AdvanceActorFixedStepMotion(u8 *a)
{
    if (*(s16 *)(a + 0x40) != 0) {
        *(u16 *)(a + 0x40) -= 1;
        *(s32 *)(a + 0x2C) += *(s16 *)(a + 0x4E) << 8;
        *(s32 *)(a + 0x30) += *(s16 *)(a + 0x50) << 8;
        *(s32 *)(a + 0x34) += *(s16 *)(a + 0x52) << 8;
        return 0;
    }
    return 1;
}

s32 func_80041C54(u8 *a)
{
    u8 *p;
    u8 *q;

    switch (a[0x78]) {
    case 0:
        if (*(s16 *)(a + 0x74) >= 0) {
            a[0x7A] = a[0x74];
        }
        a[0x78]++;
    case 1:
        p = f_SpawnScriptedPresentationActor(*(s16 *)(a + 0x72), a[0x7A], *(s16 *)(a + 0x76));
        *(u8 **)(a + 0x10) = p;
        if (p == NULL) {
            break;
        }
        if ((u16)(*(u16 *)(a + 0x76) - 1) < 2) {
            return 1;
        }
        goto inc;
    case 2:
        q = *(u8 **)(a + 0x10);
        if (q[4] != 2) {
            return 0;
        }
        q[4] = 3;
    inc:
        a[0x78]++;
        break;
    case 3:
        *(u8 **)(a + 0x10) = NULL;
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_80041D60);

s32 func_80041F34(u8 *a)
{
    if (a == 0) {
        goto ok;
    }
    if (a[5] == 3) {
        if (*(u16 *)(a + 0x42) == 0xFFFF) {
            *(u16 *)(a + 0x42) = 0;
        }
        if ((D_800E7E68 & D_1F800174_de41) && !(a[0x46] & 1)) {
            a[5] = 10;
            goto ok;
        }
    }
    return 0;
ok:
    return 1;
}

void func_80041FA8(void *arg0) {
    func_80041F34(M2C_FIELD(arg0, s32 *, 0x10));
}

extern u8 D_800A55C8[];
extern void *D_800A2B64[];
void f_DrawUiQuadResource(s16, s16, s32, s32);
s32 func_80041FCC(u8 *p)
{
    if (p != NULL) {
        if (p[5] != 3) {
            return 0;
        }
        p[5] = 10;
    }
    return 1;
}

void func_80041FF8(void *arg0) {
    func_80041FCC(M2C_FIELD(arg0, s32 *, 0x10));
}

s32 func_8004201C(u8 *p)
{
    u8 *q = D_800BF9B4 + *(s16 *)(p + 0x72);

    switch (p[0x78]) {
    case 0:
        *q = p[0x74];
        p[0x78]++;
        goto end;
    case 1:
        if (*q == *(s16 *)(p + 0x76)) {
            return 1;
        }
    end:
    default:
        return 0;
    }
}

u32 func_80042090(void *arg0) {
    u16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, u16 *, 0x72) - 1;
    M2C_FIELD(arg0, u16 *, 0x72) = temp_v0;
    return (u32) (temp_v0 << 0x10) >> 0x1F;
}

extern s16 D_1F8000C0[];
extern u16 D_1F8000C8_208b[];
extern u8 *D_800E7F50;
extern u8 D_800BF80A_8fc3;
s32 func_800420AC(u8 *p)
{
    switch (*(s16 *)(p + 0x72)) {
    case 0:
        if (D_800BF870.pad1[*(s16 *)(p + 0x74) + 0x143] == *(s16 *)(p + 0x76)) {
            return 1;
        }
        break;
    case 1:
        if (D_800BF870.pad1[*(s16 *)(p + 0x74) + 0x143] & *(s16 *)(p + 0x76)) {
            return 1;
        }
        break;
    case 2:
        if (!(D_800BF870.pad1[*(s16 *)(p + 0x74) + 0x143] & *(s16 *)(p + 0x76))) {
            return 1;
        }
        break;
    }
    return 0;
}

s32 func_80042170(u8 *a)
{
    switch (*(s16 *)(a + 0x72)) {
    case 0:
        if (a[0x79] != 1) {
            break;
        }
        return 1;
    case 1:
        if ((*(u8 **)D_1F800214)[0x79] != 1) {
            break;
        }
        return 1;
    }
    return 0;
}

s32 func_800421CC(u8 *a)
{
    switch (*(s16 *)(a + 0x72)) {
    case 0:
        if (D_800E806E != 3) {
            break;
        }
        return 1;
    case 1:
        if (f_UpdateCameraTransformInterpolation(&g_CameraState) != 1) {
            break;
        }
        return 1;
    }
    return 0;
}

extern u8 D_800BF843;
s32 func_8004223C(void *arg0) {
    return D_800BF843 == M2C_FIELD(arg0, s16 *, 0x72);
}

s32 func_80042258(u8 *p)
{
    switch (p[0x78]) {
    case 0:
        *(s16 *)(p + 0x64) = 0;
        p[0x78]++;
        goto end;
    case 1:
        if (*(u16 *)(p + 0x72) & 1) {
            D_800E7EAE = *(u16 *)(p + 0x74);
        }
        if (*(u16 *)(p + 0x72) & 2) {
            D_800E7EB6 = *(u16 *)(p + 0x76);
        }
        if (D_800BF80E_58ec != 0) {
            return 1;
        }
        if (++*(s16 *)(p + 0x64) >= 0x1F4) {
            return 1;
        }
    end:
    default:
        return 0;
    }
}

extern s8 D_1F800137[];
s32 f_EndScriptedInteractionAudio(void) {
    f_RequestStreamedAudioStop();
    f_PlaySoundEffect(0x7F, 0, 0);
    *((s8 *)D_1F800137) = 0;
    f_PlayAreaBackgroundTrack(D_800BF870.unk0);
    return 1;
}

s32 f_PlaySoundEffect();
s32 f_BeginScriptedInteractionAudio(s32 flag, s32 idx)
{
    Bytes8_368 t = D_80015368;
    u8 i = idx;

    f_RequestStreamedAudioStop();
    D_800BF84B = 0;
    if (i != 0) i = idx - 1;
    f_PlaySoundEffect(t.b[i], 0, 0);
    D_1F800137_104c = flag;
    return 1;
}

void func_800423FC(void *arg0) {
    if (M2C_FIELD(arg0, s16 *, 0x72) != 0) {
        f_BeginScriptedInteractionAudio((u8) M2C_FIELD(arg0, s16 *, 0x72), M2C_FIELD(arg0, u8 *, 0x74));
        return;
    }
    f_EndScriptedInteractionAudio();
}

typedef struct { u8 pad[0x144]; u8 flags[1]; } Flags_2448;
s32 func_80042448(u8 *a)
{
    switch (*(s16 *)(a + 0x72)) {
    case 0:
        ((Flags_2448 *)&D_800BF870)->flags[*(s16 *)(a + 0x74)] = a[0x76];
        break;
    case 1:
        ((Flags_2448 *)&D_800BF870)->flags[*(s16 *)(a + 0x74)] |= a[0x76];
        break;
    case 2:
        ((Flags_2448 *)&D_800BF870)->flags[*(s16 *)(a + 0x74)] &= a[0x76];
        break;
    }
    return 1;
}

void f_ConfigureScriptActorConversation(u8 a, u8 b, u8 c);
void func_8007074C(u8 a, u8 b, u8 c, Vec3i_74C v);
s32 func_800424F0(u8 *a)
{
    union { s16 h[6]; Vec3i_74C v; } u;

    switch (a[0x78]) {
    case 0:
        if (D_800BF843 != 0) {
            return 1;
        }
        if (*(u16 *)(a + 0x76) & 4) {
            u.h[1] = *(u16 *)(a + 0x64);
            u.h[3] = *(u16 *)(a + 0x66);
            u.h[5] = *(u16 *)(a + 0x68);
            ((void (*)(s32, s32, s32, Vec3i_74C))func_8007074C)(*(u16 *)(a + 0x72) & 0xFFF, *(s16 *)(a + 0x74), *(s16 *)(a + 0x76), u.v);
        } else {
            ((void (*)(s32, s32, s32))f_ConfigureScriptActorConversation)(*(u16 *)(a + 0x72) & 0xFFF, *(s16 *)(a + 0x74), *(s16 *)(a + 0x76));
        }
        if (*(s16 *)(a + 0x72) & 0x8000) {
            return 1;
        }
        a[0x78]++;
        break;
    case 1:
        if (D_800BF843 == 1) {
            return 1;
        }
        break;
    }
    return 0;
}

s32 func_800425FC(u8 *a)
{
    switch (a[0x78]) {
    case 0:
        f_StartCurrentScriptActorConversation();
        a[0x78]++;
        break;
    case 1:
        if (D_800BF843 == 0) {
            return 1;
        }
        break;
    }
    return 0;
}

s32 func_8004266C(void *arg0) {
    f_SetCurrentScriptActorMode(M2C_FIELD(arg0, u8 *, 0x72));
    return 1;
}

s32 func_80042690(u8 *a)
{
    s16 v[8];

    v[1] = *(u16 *)(a + 0x72);
    v[3] = *(u16 *)(a + 0x74);
    v[5] = *(u16 *)(a + 0x76);
    f_SetScriptActorInteractionOffset(a, 1, v);
    f_SetCurrentScriptActorMode(3);
    return 1;
}

s32 func_800426D8(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x2C) = (s32) (M2C_FIELD(arg0, s16 *, 0x72) << 0x10);
    M2C_FIELD(arg0, s32 *, 0x30) = (s32) (M2C_FIELD(arg0, s16 *, 0x74) << 0x10);
    M2C_FIELD(arg0, s32 *, 0x34) = (s32) (M2C_FIELD(arg0, s16 *, 0x76) << 0x10);
    if (*M2C_FIELD(arg0, u16 **, 0x6C) & 0x2000) {
        M2C_FIELD(arg0, u8 *, 0x2A) = (u8) M2C_FIELD(arg0, u8 *, 0x64);
    }
    return 1;
}

s32 f_IsEventPresentationComplete(void)
{
    if (D_800ED06D == 0 && D_800BF849 == 0) {
        return 1;
    }
    return 0;
}

s32 func_80042758(u8 *p)
{
    switch (p[0x78]) {
    case 0:
        if (*(s16 *)(p + 0x72) >= 0) {
            if (f_StartEvent(*(s16 *)(p + 0x72)) != 1) {
                return 1;
            }
            if (*(s16 *)(p + 0x74) != 0) {
                return 1;
            }
        }
        p[0x78]++;
        goto end;
    case 1:
        return f_IsEventPresentationComplete();
    end:
    default:
        return 0;
    }
}

s32 func_800427F4(u8 *p)
{
    switch (p[0x78]) {
    case 0:
        if (f_UpdateEvent(*(s16 *)(p + 0x72)) != 1) {
            return 1;
        }
        if (*(s16 *)(p + 0x74) != 0) {
            return 1;
        }
        p[0x78]++;
        goto end;
    case 1:
        return f_IsEventPresentationComplete();
    end:
    default:
        return 0;
    }
}

extern s8 D_800BF80A;
s32 func_80042884(void) {
    D_800BF80A = 0;
    return 1;
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_80042894);

extern s16 D_1F800160_71b4;
extern s16 D_1F800162_a8d4;
extern s16 D_1F800164_d75f;
void f_RestorePreviousCameraMode(void);
void f_SetCameraMode(u8 mode);
s32 func_80042A8C(u8 *a)
{
    u8 *c = D_800E8008_f2dc;

    c[0x66] = 0;
    switch (*(s16 *)(a + 0x72)) {
    case -1:
        f_RestorePreviousCameraMode();
        return 1;
    case 0:
        ((void (*)(s32))f_SetCameraMode)(*(s16 *)(a + 0x74));
        break;
    case 1:
        c[0x64] = a[0x74];
        break;
    }
    switch (*(s16 *)(a + 0x76)) {
    case 0:
        *(s32 *)(c + 0x38) = *(s16 *)(a + 0x64) << 16;
        *(s32 *)(c + 0x3C) = *(s16 *)(a + 0x66) << 16;
        *(s32 *)(c + 0x40) = *(s16 *)(a + 0x68) << 16;
        break;
    case 1:
        *(s32 *)(c + 0x38) = D_1F800160_71b4 << 16;
        *(s32 *)(c + 0x3C) = (D_1F800162_a8d4 - 0x8C) << 16;
        *(s32 *)(c + 0x40) = D_1F800164_d75f << 16;
        break;
    }
    return 1;
}

s32 func_80042BAC(u16 *p)
{
    CameraState *c = &g_CameraState;
    u16 t;

    c->unk6E = p[0x39];
    c->unk70 = p[0x3A];
    t = p[0x3B];
    c->unk66 = 0;
    c->unk6C = t;
    return 1;
}

extern u8 D_800E7FC7;
extern u16 D_800E7FC0;
s32 func_80042BDC(u8 *a)
{
    u8 *c = D_800E8008_f2dc;
    s32 d;
    s16 v;

    if (*(s16 *)(a + 0x72) == 0) {
        f_SetCameraMode(1);
    } else {
        c[0x64] = 1;
    }
    *(s16 *)(c + 0x6E) = 0x130;
    *(s32 *)(c + 0x38) = D_1F800160_71b4 << 16;
    *(s32 *)(c + 0x3C) = (D_1F800162_a8d4 - 0x8C) << 16;
    *(s32 *)(c + 0x40) = D_1F800164_d75f << 16;
    switch (*(s16 *)(a + 0x74)) {
    case 0:
        d = 0x240;
        break;
    case 3:
        d = -0x180;
        break;
    case 1:
        d = 0x180;
        break;
    case 2:
        d = 0x180;
        break;
    default:
        d = 0x180;
        break;
    }
    if (*(s16 *)(a + 0x74) < 2 && D_800E7FC7 != 0) {
        d = -d;
    }
    *(s16 *)(c + 0x70) = d + (D_800E7FC0 + *(u16 *)(c + 0x52));
    v = *(u16 *)(a + 0x76);
    *(s16 *)(c + 0x6C) = v;
    if (v == 0) {
        *(s16 *)(c + 0x6C) = 0x480;
    }
    c[0x66] = 0;
    return 1;
}

s32 func_80042D28(u8 *a)
{
    u8 *g = D_800E8008_f2dc;

    switch (a[0x78]) {
    case 0:
        switch (*(s16 *)(a + 0x72)) {
        case -1:
        off:
            g[0x76] = 0;
            return 1;
        case 0:
            g[0x76] = 1;
            return 1;
        default:
            g[0x76] = 1;
            a[0x78]++;
            break;
        }
        break;
    case 1:
        if (--*(s16 *)(a + 0x72) < 0) {
            goto off;
        }
        break;
    default:
        break;
    }
    return 0;
}

s32 func_80042DCC(void *arg0) {
    M2C_FIELD(arg0, u8 *, 0xD) = (u8) (M2C_FIELD(arg0, u8 *, 0xD) | 2);
    M2C_FIELD(arg0, u8 *, 0x18) = (u8) M2C_FIELD(arg0, u8 *, 0x72);
    M2C_FIELD(arg0, u8 *, 0x19) = (u8) M2C_FIELD(arg0, u8 *, 0x74);
    M2C_FIELD(arg0, u8 *, 0x1A) = (u8) M2C_FIELD(arg0, u8 *, 0x76);
    return 1;
}

s32 func_80042DF8(void *arg0) {
    M2C_FIELD(arg0, u8 *, 0xD) = (u8) (M2C_FIELD(arg0, u8 *, 0xD) & 0xFD);
    return 1;
}

s32 func_80042E10(u8 *a)
{
    s32 k;
    u16 j;

    switch (a[0x78]) {
    case 0:
        k = *(u16 *)(a + 0x72) & 7;
        j = k;
        if (k != 0) {
            if (D_800BF808[7] == 0) {
                D_800BF808[7] = j;
            }
            if (*(s16 *)(a + 0x72) & 0x8000) {
                return 1;
            }
        }
        a[0x78]++;
        break;
    case 1:
        if (D_800BF80F_fcc6 == 0) {
            return 1;
        }
        break;
    default:
        break;
    }
    return 0;
}

s32 f_PlaySoundEffect();
s32 func_80042EA4(u8 *a, u16 *flags, s32 snd)
{
    s32 id = snd;
    u16 v;

    snd &= 0xFF00;
    snd >>= 8;

    if (*(s16 *)flags == 0) {
        return 0;
    }
    v = *flags;
    if (v & 0x3F) {
        if (D_1F80017C_0fe7 & *(s16 *)flags) {
            return 0;
        }
        ((void (*)(u8, s32, s8))f_PlaySoundEffect)(id, 0, snd);
        return 0;
    }
    if (!(v & 0x80)) {
        return 0;
    }
    if (*(*(u8 **)(a + 0x38) + 4) != 0) {
        if (v & 0x40) {
            return 0;
        }
        *flags = v | 0x40;
        ((void (*)(u8, s32, s8))f_PlaySoundEffect)(id, 0, snd);
        return 1;
    }
    *flags = v & 0xFFBF;
    return 0;
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_80042F70);

INCLUDE_ASM("asm/main/nonmatchings/main", f_RunScriptedActorInterpolatedMovementCommand);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800433FC);

s32 func_80043634(u8 *p)
{
    u16 v = *(u16 *)(p + 0x72);
    u8 *e;

    if (v & 0x1000) {
        D_800BF844 = f_SpawnAreaLinkedWeaponPickupActor(p, v & 0xFFF);
    } else {
        D_800BF844 = f_SpawnAreaLinkedItemPickupActor(p, v & 0xFFF);
    }
    e = D_800BF844;
    if (e != 0) {
        e[0x5E] = p[0x74];
        *(u16 *)(e + 0x60) = *(u16 *)(p + 0x76);
    }
    return 1;
}

s32 func_800436BC(u8 *p)
{
    u8 *b = D_800BF844;

    if (*(s16 *)(p + 0x72) == -1) {
        b[4] = 2;
        b[5] = 0;
        *(u16 *)(b + 0x74) = *(u16 *)(p + 0x74);
    } else {
        b[5] = p[0x72];
        b[0x5E] = p[0x74];
        *(u16 *)(b + 0x60) = *(u16 *)(p + 0x76);
    }
    b[6] = 0;
    return 1;
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_80043720);

s32 func_80043858(u8 *p)
{
    u8 *a = f_SpawnLinkedItemPickupActor(p, *(s16 *)(p + 0x72));

    D_800BF844 = a;
    if (a != 0) {
        ((PosHolder_858 *)a)->pos = ((PosHolder_858 *)D_800E7E80_f78d)->pos;
        return 1;
    }
    return 0;
}

s32 func_800438B4(u8 *actor)
{
    if (*(s16 *)(actor + 0x72) == actor[0x7A]) {
        return 3;
    }
    return 2;
}

s32 func_800438D4(s16 op, u8 a, u8 b)
{
    switch (op) {
    case -1:
        return 3;
    case 0:
        if (a == b) {
            return 3;
        }
        break;
    case 1:
        if (a <= b) {
            return 3;
        }
        break;
    case 2:
        if (b <= a) {
            return 3;
        }
        break;
    case 3:
        if (a & b) {
            return 3;
        }
        break;
    }
    return 2;
}

void func_80043964(u8 *p)
{
    func_800438D4(*(s16 *)(p + 0x72), D_800BF870.pad1[*(s16 *)(p + 0x74) + 0x143], p[0x76]);
}

void func_800439A4(u8 *p)
{
    func_800438D4(*(s16 *)(p + 0x72), D_800BF870.pad1[*(s16 *)(p + 0x74) + 0x43], p[0x76]);
}

s32 func_800439E4(void *arg0) {
    f_StartControllerVibration(0, M2C_FIELD(arg0, u8 *, 0x74), M2C_FIELD(arg0, u8 *, 0x76), M2C_FIELD(arg0, u8 *, 0x72));
    return 1;
}

s32 func_80043A10(void *arg0) {
    f_PlaySoundEffect(M2C_FIELD(arg0, u8 *, 0x72), M2C_FIELD(arg0, s8 *, 0x74), M2C_FIELD(arg0, s8 *, 0x76));
    return 1;
}

extern u8 D_1F800233_33a2;
void f_StopNonReservedSequencedMusic(void);
s32 func_80043A40(u8 *a)
{
    f_StopNonReservedSequencedMusic();
    switch (a[0x78]) {
    case 0:
        switch (*(s16 *)(a + 0x72)) {
        case 1:
        case 3:
            D_1F800233_33a2 = 1;
        case 0:
            f_PlayOrStopVoiceLine(*(s16 *)(a + 0x74));
            if (*(s16 *)(a + 0x72) == 3) {
                a[0x78]++;
                break;
            }
            return 1;
        case 2:
            D_1F800233_33a2 = 0;
            *(s16 *)(a + 0x72) = 0;
            a[0x78] = 2;
            break;
        default:
            return 0;
        }
        break;
    case 1:
        if (--*(s16 *)(a + 0x76) > 0) {
            break;
        }
        D_1F800233_33a2 = 0;
        return 1;
    case 2:
        if (++*(s16 *)(a + 0x72) >= 0x3C) {
            return 1;
        }
        if (!(D_800BE0E4 & 0x80)) {
            return 1;
        }
        break;
    default:
        return 0;
    }
    return 0;
}

extern s8 D_800BF84C;
s32 f_SetSharedScriptControlFlag(s32 arg0, s32 arg1) {
    if (!(arg1 & 0xFF)) {
        D_800BF84C = 0;
    } else {
        D_800BF84C = 1;
    }
    return 1;
}

void func_80043BB0(u8 *actor)
{
    f_SetSharedScriptControlFlag(actor, actor[0x72]);
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_80043BD4);

extern u16 D_1F800190_b2e0;
extern u16 D_1F800192;
extern u16 D_1F80016C_4910;
extern u16 D_1F80016E_cd4b;
s32 func_80043D8C(u8 *a, s32 k)
{
    s32 one = 1;
    u8 *e;
    u16 v;
    u8 *s;

    switch (a[0x78]) {
    case 0:
        if (*(s16 *)(a + 0x76) != 0) {
            D_1F800190_b2e0 = 0;
            e = (u8 *)D_800E7E80;
            v = *(u16 *)(a + 0x74);
            e[5] = 0x1F;
            e[6] = 0;
            D_1F800192 = v;
            a[0x78] = one;
        } else {
            a[0x78] = 2;
        }
        break;
    case 1:
        D_1F800190_b2e0 = 0;
        if (D_800BF816 == (k & 0xFF)) {
            a[0x78]++;
        } else if (*(s16 *)(a + 0x74) == 0) {
            D_1F800190_b2e0 = D_1F80016C_4910;
        } else {
            D_1F800190_b2e0 = D_1F80016E_cd4b;
        }
        break;
    case 2:
        s = D_800BF808;
        if (s[0xE] != (k & 0xFF)) {
            return 0;
        }
        if (s[6] == one) {
            return 1;
        }
        break;
    }
    return 0;
}

s32 func_80043D8C(u8 *a, s32 k);
void f_QueueItemMessage(s32, s32);
void func_80043E9C(void *a)
{
    func_80043D8C(a, 1);
}

void func_80043EBC(void *a)
{
    func_80043D8C(a, 0);
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_80043EDC);

extern s8 D_1F800207[];
extern u8 D_800E7EAA;
s32 func_80044090(void) {
    *((u8 *)D_1F800207) = D_800E7EAA;
    return 1;
}

typedef struct Entry8 { u8 pad0[6]; u16 flags; } Entry8;
extern Entry8 *D_800A54A8_7082[];
typedef struct Slot4C { u8 used; u8 pad[0x4B]; } Slot4C;
extern Slot4C D_80100400[];
typedef struct Range8 { s32 sector; s32 size; } Range8;
extern Range8 D_800BE118[];
extern u8 D_800A4A84[];
extern u8 D_800A4A8C[];
typedef struct Slot40 { u8 used; u8 pad[0x3F]; } Slot40;
extern Slot40 D_800EC188_44f3[];
s32 func_800440A8(u8 *p)
{
    s8 *d = D_800E7E80;

    d[0x2A] = p[0x72];
    *(u16 *)(d + 0x2E) = *(u16 *)(p + 0x74);
    *(u16 *)(d + 0x32) = *(u16 *)(p + 0x76);
    *(u16 *)(d + 0x36) = *(u16 *)(p + 0x64);
    return 1;
}

extern u8 D_800E7E80_f78d[];
void func_8004BB38();
extern u16 D_800BED8C;
extern u16 *D_800BED88;
void f_StartTombaScriptedAnimation(u8 *t, s32 anim, s16 blend)
{
    if (t[0x164] == 0) {
        f_SetTombaAnimation(t, anim & 0x7FFF, blend);
        if (anim & 0x8000) {
            t[5] = 0x26;
        } else {
            t[5] = 0x22;
        }
        t[6] = 0;
    }
}

void f_PlaySoundEffectWithPitchOffset(s32 arg0, s8 arg1);
s32 func_80044144(u8 *a)
{
    u8 *e = (u8 *)D_800E7E80;
    u16 f;

    switch (a[0x78]) {
    case 0:
        if (e[0x164] != 0) {
            return 1;
        }
        if (*(s16 *)(a + 0x72) == 2) {
            f_StartTombaScriptedAnimation(e, *(s16 *)(a + 0x74) | 0x8000, *(s16 *)(a + 0x76));
        } else {
            f_StartTombaScriptedAnimation(e, *(s16 *)(a + 0x74), *(s16 *)(a + 0x76));
        }
        if (*(s16 *)(a + 0x72) != 0) {
            return 1;
        }
        if (!(**(u16 **)(a + 0x6C) & 0x2000)) {
            a[0x78] = 2;
        } else {
            a[0x78] = 1;
        }
        break;
    case 1:
        f = *(u16 *)(a + 0x66);
        if (!(*(s16 *)(a + 0x66) & 0x8000)) {
            if ((f & 0xFF) == (*(u8 **)(e + 0x38))[4]) {
                f_PlaySoundEffectWithPitchOffset(a[0x68], 0);
                *(u16 *)(a + 0x66) |= 0x8000;
            }
        } else if ((f & 0xFF) != (*(u8 **)(e + 0x38))[4]) {
            *(u16 *)(a + 0x66) = f & 0x7FFF;
        }
    case 2:
        if (D_800BF80E_58ec != 0) {
            return 1;
        }
        break;
    }
    return 0;
}

s32 func_800442A0(u8 *p)
{
    u8 *t = D_800E7E80_f78d;
    u8 *who = p;

    if (*(s16 *)(p + 0x72) & 0x8000) {
        who = *(u8 **)D_1F800214;
    }
    f_SetActorAnimation(who, *(s16 *)(p + 0x74), 4);
    f_StartTombaScriptedAnimation(t, *(s16 *)(p + 0x76), 4);
    return 1;
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_80044308);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800444EC);

typedef struct { u8 pad[0x3C]; u8 *p3C; } Gs808_46A4;
extern Gs808_46A4 D_800BF808_84c1;
extern u8 D_800BF822;
s32 func_800446A4(u8 *a)
{
    u16 v;
    s32 r;
    s16 anim;

    switch (a[0x78]) {
    case 0:
        f_StartTombaScriptedAnimation(D_800E7E80_f78d, 0xCF, 2);
        v = *(u16 *)(a + 0x72);
        if (v & 0x2000) {
            D_800BF844 = func_8006FC34(a, v & 0x3FF);
        } else if (v & 0x1000) {
            D_800BF844 = f_SpawnAreaLinkedWeaponPickupActor(a, v & 0x3FF);
        } else {
            D_800BF844 = f_SpawnAreaLinkedItemPickupActor(a, v & 0x3FF);
        }
        if (D_800BF808_84c1.p3C != NULL) {
            if (**(u16 **)(a + 0x6C) & 0x2000) {
                *(u16 *)(D_800BF808_84c1.p3C + 0x60) = *(u16 *)(a + 0x64);
            }
            D_800BF808_84c1.p3C[0x5E] = 0;
        }
        if (!(*(u16 *)(a + 0x72) & 0x800)) {
            f_QueueItemMessage(*(u16 *)(a + 0x72) & 0x3FF, 4);
            f_RemoveItemWithoutMessage(*(u16 *)(a + 0x72) & 0x3FF, 1);
        }
        a[0x78]++;
        break;
    case 1:
        if (D_800BF80E_58ec != 0) {
            f_SetActorAnimation((s32)a, *(s16 *)(a + 0x74), 4);
            a[0x78]++;
        }
        break;
    case 2:
        if ((*(u8 **)(a + 0x38))[4] != 0) {
            if (!(*(u16 *)(a + 0x72) & 0x4000)) {
                D_800BF844[4] = 2;
            } else {
                *(u16 *)(D_800BF808_84c1.p3C + 0x60) = *(u16 *)(a + 0x66);
                *(u16 *)(D_800BF808_84c1.p3C + 0x62) = *(u16 *)(a + 0x6A);
                D_800BF808_84c1.p3C[0x5E] = a[0x68];
            }
            f_StartTombaScriptedAnimation(D_800E7E80_f78d, 2, 4);
            a[0x78]++;
        }
        break;
    case 3:
        if (a[0x79] == 1) {
            if (*(u16 *)(a + 0x72) & 0x4000) {
                *(u16 *)(D_800BF808_84c1.p3C + 0x60) = *(u16 *)(a + 0x66);
                D_800BF808_84c1.p3C[0x5E] = *(u16 *)(a + 0x68) >> 8;
            }
            anim = *(s16 *)(a + 0x76);
            if (anim >= 0) {
                f_SetActorAnimation((s32)a, anim, 4);
            }
            a[0x78]++;
        }
        break;
    case 4:
        r = 1;
        if (D_800BF822 & r) {
            break;
        }
        return r;
    }
    return 0;
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_8004491C);

s32 func_80044B38(u8 *p)
{
    u8 *t = D_800E7E80_f78d;

    switch (p[0x78]) {
    case 0:
        *(s16 *)(p + 0x74) = f_CalculateYawFromPositionToPoint(t + 0x2C, *(s16 *)(p + 0x2E), *(s16 *)(p + 0x36));
        *(s16 *)(t + 0x58) = 0;
        p[0x78]++;
        goto end;
    case 1:
        if (f_StepActorYawTowardAngle(t, *(s16 *)(p + 0x74), *(s16 *)(p + 0x72)) != 0) {
            return 1;
        }
    end:
    default:
        return 0;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/main", f_StartCooperativeWorker);

extern s32 D_800BE100;          /* first sector of TOMBA2.DAT? (added to every read) */
void f_OpenCooperativeWorkerThread(s32, void (*)());
void func_8001DB38();

// Starts reading `size` bytes from disc sector D_800BE100 + `sector` to `dst` on the cooperative worker; 0 when
// the worker is still busy.
s32 f_StartCooperativeDiscRead(void *dst, s32 sector, s32 size)
{
    WorkerState *w = WORKER_STATE;

    g_DiscReadPending = 0;
    f_CloseCooperativeWorkerThread(2);
    if (w->busy != 0) {
        return 0;
    }
    g_DiscReadDest = dst;
    g_DiscReadSector = D_800BE100 + sector;
    g_DiscReadWords = (size + 3) / 4;
    w->active = 1;
    f_OpenCooperativeWorkerThread(1, func_8001DB38);
    return 1;
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_80044D8C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80044E84);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80044F58);

void func_80045080(void *dst, u8 i, s32 c, void *d)
{
    func_8001DC40(dst, D_800BE118[i].sector, D_800BE118[i].size, d);
}

void func_800450BC(void **out, s32 i)
{
    void *v;

    if (i == 3) {
        v = D_800A3ED8;
    } else {
        func_8001DB8C(D_80106228, D_800BE1E0_8c5b[i].sector, D_800BE1E0_8c5b[i].size);
        f_YieldCurrentCooperativeWorker(1);
        v = D_800A3ECC[i];
    }
    out[0] = v;
    out[1] = GetGp();
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_8004514C);

INCLUDE_ASM("asm/main/nonmatchings/main", f_LoadResourceChunkIntoGroup);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800452C0);

void func_80045558(s32 arg0, s32 arg1, s32 arg2, void *arg3) {
    func_80045080((void *)0x8018A000, arg0 & 0xFF, arg2, arg3);
}

s32 func_80045580(s32 i)
{
    return f_StartCooperativeDiscRead((void *)0x8018A000, D_800A3EC8, D_800BE118_9ace[i].size) != 0;
}

extern s8 D_1F8001BC[];
extern s8 D_1F8001BE[];
extern s8 D_1F8001C0[];
extern s8 D_1F8001C4[];
s32 f_ProbeActorTerrainAtOffset(u8 *arg0, s16 arg1, s32 arg2, s16 arg3)
{
    s32 temp_a1;
    s32 temp_lo;
    s32 temp_s0;
    u16 k;

    temp_s0 = (s32) (-rsin(arg3) * arg1) >> 0xC;
    temp_lo = rcos(arg3) * arg1;
    *((s16 *)D_1F8001BE) = *(u16 *)(arg0 + 0x32) + arg2;
    *((s16 *)D_1F8001C0) = *(u16 *)(arg0 + 0x36) + temp_s0;
    temp_a1 = temp_lo >> 0xC;
    *((s16 *)D_1F8001BC) = *(u16 *)(arg0 + 0x2E) + temp_a1;
    if (f_FindTerrainCellForActorProbe(arg0, temp_a1) != 0) {
        if (f_ResolveTerrainProbeVerticalContact() != 0) {
            k = *(u16 *)D_1F8001A6;
            switch (k & 0xF00) {
            case 0x100:
                if (D_800BF873 != 0) {
                    u16 v = *(u16 *)(arg0 + 0x32) + *(u16 *)D_1F8001C4;

                    *(u16 *)D_1F8001A6 = k & 0xFF;
                    *(u16 *)(arg0 + 0x32) = v;
                    return 1;
                }
            case 0x600:
            case 0x700:
                return 2;
            }
            *(u16 *)(arg0 + 0x32) += *(u16 *)D_1F8001C4;
            return 1;
        }
        return 0;
    }
    return 0;
}

INCLUDE_ASM("asm/main/nonmatchings/main", f_ResolveTerrainProbeVerticalContact);

INCLUDE_ASM("asm/main/nonmatchings/main", f_EvaluateTerrainVerticalSurface);

extern s16 D_1F8001C2;
extern u16 *D_1F8001E0;
extern s16 *D_1F8001EC;
s32 func_800459D0(s16 k)
{
    s32 hi, lo;
    s32 y;
    s16 v;

    if (D_1F8001EC[2] > 0) {
        hi = D_1F8001EC[1] + D_1F8001EC[2];
        lo = D_1F8001EC[1];
    } else {
        hi = D_1F8001EC[1];
        lo = hi + D_1F8001EC[2];
    }
    y = *(s16 *)D_1F8001BE;
    if (hi < y) {
zero:
        return 0;
    }
    if (y >= lo - 0x80) {
        if (*D_1F8001E0 & 8) {
            v = D_1F8001EC[1] + ((D_1F8001EC[2] * D_1F8001C2) >> 6);
        } else {
            v = D_1F8001EC[1] + (D_1F8001EC[2] * (D_1F8001C2 - k)) / (s16)(k ^ 0x3F);
        }
        if (v < *(s16 *)D_1F8001BE) {
            goto zero;
        }
        *(s16 *)D_1F8001C4 = v - *(u16 *)D_1F8001BE;
        *(u16 *)D_1F8001A6 = D_1F8001EC[0];
        return 1;
    }
    return -1;
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_80045B30);

INCLUDE_ASM("asm/main/nonmatchings/main", f_ResolveActorRadialTerrainContact);

INCLUDE_ASM("asm/main/nonmatchings/main", f_ResolveTerrainProbeHorizontalSurfaceBySideMask);

INCLUDE_ASM("asm/main/nonmatchings/main", f_EvaluateTerrainHorizontalSurface);

INCLUDE_ASM("asm/main/nonmatchings/main", f_TestActorRadialTerrainContact);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80046A44);

INCLUDE_ASM("asm/main/nonmatchings/main", f_ResolveActorDirectionalTerrainContact);

INCLUDE_ASM("asm/main/nonmatchings/main", f_ResolveTerrainProbeSurfaceBySideMask);

INCLUDE_ASM("asm/main/nonmatchings/main", f_ClassifyActorDirectionalTerrainContact);

extern s16 D_1F8001C6;
void f_SelectAreaPlaneCollisionTables(u8 i);
s32 f_ResolveActorAreaPlanePosition(u8 *a)
{
    s32 r;
    s16 x, z;

    *(s16 *)D_1F8001BC = *(s16 *)(a + 0x2E);
    *(s16 *)D_1F8001BE = *(s16 *)(a + 0x32);
    *(s16 *)D_1F8001C0 = *(s16 *)(a + 0x36);
    do {
        r = f_ProjectActorOntoAreaPlane(a);
        f_SelectAreaPlaneCollisionTables(a[0x2A]);
        if (f_FindAreaPlaneCollisionCell() == 0) {
            return 0;
        }
        if (!(*D_1F8001E0 & 0x4000)) {
            break;
        }
        a[0x2A] = *(u8 *)D_1F8001E0;
    } while (*D_1F8001E0 & 0x4000);
    f_ComputeAreaPlaneCellCorrection();
    f_SelectAreaPlaneVerticalProfile();
    x = *(s16 *)D_1F8001BC + D_1F8001C2;
    z = *(s16 *)D_1F8001C0 + D_1F8001C6;
    *(s16 *)D_1F8001BC = x;
    *(s16 *)D_1F8001C0 = z;
    *(s16 *)(a + 0x2E) = x;
    *(s16 *)(a + 0x36) = z;
    return r;
}

INCLUDE_ASM("asm/main/nonmatchings/main", f_ProjectActorOntoAreaPlane);

INCLUDE_ASM("asm/main/nonmatchings/main", f_ProjectTerrainProbeOntoAreaPlane);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80047B5C);

INCLUDE_ASM("asm/main/nonmatchings/main", f_FindAreaPlaneCollisionCell);

INCLUDE_ASM("asm/main/nonmatchings/main", f_SelectAreaPlaneVerticalProfile);

INCLUDE_ASM("asm/main/nonmatchings/main", f_ComputeAreaPlaneCellCorrection);

INCLUDE_ASM("asm/main/nonmatchings/main", f_ProjectProbeWithinTerrainCell);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80048654);

INCLUDE_ASM("asm/main/nonmatchings/main", f_ResolveActorTerrainSurfaceOrientation);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80048894);

INCLUDE_ASM("asm/main/nonmatchings/main", f_QueryActorTerrainSurface);

INCLUDE_ASM("asm/main/nonmatchings/main", f_SelectTerrainSurfaceForProbeHeight);

extern u16 *D_800ECF74;
extern u8 D_1F8001FE;
extern u16 D_1F8001BA;
extern u8 D_1F8001FC;
extern u8 D_1F8001FD;
extern u16 D_1F8001AA;
extern u16 D_1F8001AE;
extern u16 D_1F8001AC;
extern u16 D_1F8001B0;
void func_80048D3C(void)
{
    u16 *h;
    u16 *p;
    u16 a, b, t;

    switch (D_800BF870.unk0) {
    case 2: case 3: case 7: case 20: case 21:
        return;
    }
    h = D_800ECF74;
    D_1F8001FE = 1;
    D_1F8001C8 = h;
    p = h + h[1];
    a = p[0];
    b = p[1];
    D_1F8001CC = p + 10;
    D_1F8001B2 = a;
    D_1F8001B6 = b;
    D_1F8001B4 = p[2];
    D_1F8001B8 = p[3];
    D_1F8001BA = p[4];
    D_1F8001D0 = p + p[6];
    D_1F8001D4 = (u8 *)(p + p[7]);
    D_1F8001D8 = p + p[8];
    D_1F8001DC = p + p[9];
    t = p[5];
    D_1F8001FC = t;
    D_1F8001FD = t >> 8;
    if (a <= b) {
        D_1F8001AA = a;
        D_1F8001AE = b - a;
    } else {
        D_1F8001AA = b;
        D_1F8001AE = a - b;
    }
    if (D_1F8001B4 <= D_1F8001B8) {
        D_1F8001AC = D_1F8001B4;
        D_1F8001B0 = D_1F8001B8 - D_1F8001B4;
    } else {
        D_1F8001AC = D_1F8001B8;
        D_1F8001B0 = D_1F8001B4 - D_1F8001B8;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/main", f_LoadAreaPlaneDescriptor);

INCLUDE_ASM("asm/main/nonmatchings/main", f_TransitionOrClampAreaPlaneEndpoint);

INCLUDE_ASM("asm/main/nonmatchings/main", f_SelectAreaPlaneContainingPosition);

s32 f_ProbeActorTerrainAlongFacing(s32 arg0, s32 arg1, s32 arg2) {
    return f_ProbeActorTerrainAtOffset(arg0, (s32) (s16) arg1, (s32) (s16) arg2, (s32) M2C_FIELD(arg0, s16 *, 0x56));
}

s32 f_ClassifyActorTerrainAlongFacing(s32 arg0, s32 arg1, s32 arg2) {
    return f_ClassifyActorTerrainAtOffset(arg0, (s32) (s16) arg1, (s32) (s16) arg2, (s32) M2C_FIELD(arg0, s16 *, 0x56));
}

s32 f_ClassifyActorTerrainAtOffset(u8 *arg0, s16 arg1, s32 arg2, s16 arg3)
{
    s32 temp_a1;
    s32 temp_lo;
    s32 temp_s0;
    u16 k;

    temp_s0 = (s32) (-rsin(arg3) * arg1) >> 0xC;
    temp_lo = rcos(arg3) * arg1;
    *((s16 *)D_1F8001BE) = *(u16 *)(arg0 + 0x32) + arg2;
    *((s16 *)D_1F8001C0) = *(u16 *)(arg0 + 0x36) + temp_s0;
    temp_a1 = temp_lo >> 0xC;
    *((s16 *)D_1F8001BC) = *(u16 *)(arg0 + 0x2E) + temp_a1;
    if (f_FindTerrainCellForActorProbe(arg0, temp_a1) != 0) {
        if (f_ResolveTerrainProbeVerticalContact() != 0) {
            k = *(u16 *)D_1F8001A6;
            switch (k & 0xF00) {
            case 0x100:
                if (D_800BF873 != 0) {
                    *(u16 *)D_1F8001A6 = k & 0xFF;
                    return 1;
                }
            case 0x600:
            case 0x700:
                return 2;
            }
            return 1;
        }
        return 0;
    }
    return 0;
}

void func_800493E8(u8 *actor, s16 a, s16 b)
{
    func_80049418(actor, a, b, *(s16 *)(actor + 0x56));
}

extern s8 D_1F8001A6[];
s32 func_80049418(void *arg0, s16 arg1, s32 arg2, s16 arg3) {
    s32 temp_a1;
    s32 temp_lo;
    s32 temp_s0;

    temp_s0 = (s32) (-rsin(arg3) * arg1) >> 0xC;
    temp_lo = rcos(arg3) * arg1;
    *((s16 *)D_1F8001BE) = M2C_FIELD(arg0, u16 *, 0x32) + arg2;
    *((s16 *)D_1F8001C0) = M2C_FIELD(arg0, u16 *, 0x36) + temp_s0;
    temp_a1 = temp_lo >> 0xC;
    *((s16 *)D_1F8001BC) = M2C_FIELD(arg0, u16 *, 0x2E) + temp_a1;
    if (f_FindTerrainCellForActorProbe(arg0, temp_a1) != 0) {
        if (func_80049800() != 0) {
            if ((*((u16 *)D_1F8001A6) & 0xF00) == 0x100) {
                return 2;
            }
            M2C_FIELD(arg0, u16 *, 0x32) = (u16) (M2C_FIELD(arg0, u16 *, 0x32) + *((u16 *)D_1F8001C4));
            return 1;
        }
        /* Duplicate return node #6. Try simplifying control flow for better match */
        return 0;
    }
    return 0;
}

s32 func_8004951C(s32 arg0, s32 arg1, s32 arg2) {
    return func_80045B30(arg0, (s32) (s16) arg1, (s32) (s16) arg2, (s32) M2C_FIELD(arg0, s16 *, 0x56));
}

s32 f_ResolveActorFacingTerrainContact(s32 arg0, s32 arg1, s32 arg2) {
    return f_ResolveActorRadialTerrainContact(arg0, (s32) (s16) arg1, (s32) (s16) arg2, (s32) M2C_FIELD(arg0, s16 *, 0x56));
}

s32 func_8004957C(s32 arg0, s32 arg1, s32 arg2) {
    return f_TestActorRadialTerrainContact(arg0, (s32) (s16) arg1, (s32) (s16) arg2, (s32) M2C_FIELD(arg0, s16 *, 0x56));
}

s32 f_ResolveActorDirectionalTerrainAlongFacing(s32 arg0, s32 arg1, s32 arg2) {
    return f_ResolveActorDirectionalTerrainContact(arg0, (s32) (s16) arg1, (s32) (s16) arg2, (s32) M2C_FIELD(arg0, s16 *, 0x56));
}

s32 f_ClassifyActorDirectionalTerrainAlongFacing(s32 arg0, s32 arg1, s32 arg2) {
    return f_ClassifyActorDirectionalTerrainContact(arg0, (s32) (s16) arg1, (s32) (s16) arg2, (s32) M2C_FIELD(arg0, s16 *, 0x56));
}

s32 func_8004960C(u8 *a, s32 b)
{
    u8 *p;

    if (b != 0) {
        b = *(u16 *)(D_1F8001E4 + 6) >> 8;
    } else {
        b = D_1F8001E4[6];
    }
    p = D_1F8001D4 + *(u16 *)(D_1F8001E4 + 2) * 8 + b * 8;
    a[0x2A] = *p;
    return 1;
}

extern u8 *D_1F8001E8;
void f_ApplyTerrainProfileOrientationToActor(u8 *a)
{
    s8 *p = (s8 *)D_1F8001E8;
    s16 y = p[1];
    s16 z = p[2];
    s16 x = p[0];
    s32 z2 = z;
    s32 x2 = x;
    s16 r;

    D_1F8001A0_6940 = -ratan2(z2, x2) & 0xFFF;
    r = ratan2((s16)y, (s16)SquareRoot0(x2 * x2 + z2 * z2));
    *(s16 *)(a + 0x48) = x << 2;
    *(s16 *)(a + 0x4A) = y << 2;
    *(s16 *)(a + 0x4C) = z << 2;
    D_1F8001A2 = r;
}

void f_ApplyAreaPlaneDirectionToActor(u8 *a)
{
    s32 c;
    s32 s;
    s32 ang;
    u16 t;

    ang = ratan2(D_1F8001B8 - D_1F8001B4, D_1F8001B6 - D_1F8001B2) & 0xFFF;

    D_1F8001A0_6940 = ang;
    c = rcos(ang);
    s = rsin((s16)D_1F8001A0_6940);
    D_1F8001A2 = 0;
    t = D_1F8001A0_6940;
    *(s16 *)(a + 0x48) = c >> 4;
    *(s16 *)(a + 0x4C) = s >> 4;
    D_1F8001A0_6940 = -t & 0xFFF;
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_80049800);

typedef struct { u8 on; u8 flags; u8 pad[10]; } SpuVoiceSlot_238;
extern SpuVoiceSlot_238 D_800BE238_df3f[];
extern s16 D_800BED80;
extern s32 D_800BED78;
typedef struct { s16 h0; s16 y; u8 pad[0x88]; } PopupLine_474;
s32 f_FindTerrainCellForActorProbe(u8 *a)
{
    do {
        f_ProjectTerrainProbeOntoAreaPlane(a);
        f_SelectAreaPlaneCollisionTables(D_1F8001FE);
        if (f_FindAreaPlaneCollisionCell() == 0) {
            return 0;
        }
        if (!(*D_1F8001E0 & 0x4000)) {
            return 1;
        }
        a[0x2A] = *(u8 *)D_1F8001E0;
    } while (*D_1F8001E0 & 0x4000);
    return 1;
}

void f_SelectAreaPlaneCollisionTables(u8 i)
{
    u16 *base = D_1F8001C8;
    u16 *h = base + base[i];

    D_1F8001CC = h + 10;
    D_1F8001D0 = h + h[6];
    D_1F8001D4_793a = h + h[7];
    D_1F8001D8 = h + h[8];
    D_1F8001DC = h + h[9];
}

void func_800499E8(void)
{
    CdFileLite f;

    D_1F80019A = 0;
    if (CdSearchFile(&f, D_80015458) == 0) {
        printf(D_8001546C, D_80015458);
    } else {
        D_800BE1E0[0] = CdPosToInt(&f);
        D_800BE1E0[1] = f.size;
    }
    func_80052078(0);
}

typedef struct { u8 pad0[0xA]; s16 sA; u8 padC[2]; u8 uE; u8 uF; } Gs808_9A60;
extern Gs808_9A60 D_800BF808_f4d3;
extern u8 D_800E7FEB;
void func_800493E8(u8 *actor, s16 a, s16 b);
void func_80049A60(u8 *a, s32 alt)
{
    s32 r;

    switch (a[5]) {
    case 0:
        *(s16 *)(a + 0x4A) = -0x3000;
        *(u16 *)(a + 0x50) = 0x200;
        a[5]++;
        if (alt == 0) {
            a[0x18] = 0;
        } else {
            a[0x18] = 0xFF;
            a[0x19] = 0xFF;
            a[0x1A] = 0xFF;
        }
        break;
    case 1:
        *(s32 *)(a + 0x30) += *(s16 *)(a + 0x4A) << 8;
        *(u16 *)(a + 0x4A) += *(u16 *)(a + 0x50);
        if (*(s16 *)(a + 0x4A) >= 0) {
            a[5]++;
        } else {
            if (*(s16 *)(a + 0x4A) >= -0x17FF) {
                a[0] = 1;
            }
            f_ResolveActorAreaPlanePosition(a);
            if (((s32 (*)(u8 *, s16, s16))func_800493E8)(a, 0, -*(u16 *)(a + 0x84)) != 0) {
                a[0] = 1;
                *(s16 *)(a + 0x4A) = 0;
                a[5]++;
            }
        }
        break;
    case 2:
        *(s32 *)(a + 0x30) += *(s16 *)(a + 0x4A) << 8;
        if (*(s16 *)(a + 0x4A) < 0x3000) {
            *(u16 *)(a + 0x4A) += *(u16 *)(a + 0x50);
        }
        if (a[0x29] != 0) {
            *(s16 *)(a + 0x4A) = 0;
            a[5]++;
            break;
        }
        if (a[0x28] & 0x80) {
            if (D_800E7FEB == 8) {
                if (D_800BF808_f4d3.uE == 1 && D_800BF808_f4d3.uF == *(s16 *)(a + 0x6A)
                    && *(s16 *)(a + 0x32) + (*(s16 *)(a + 0x86) - *(s16 *)(a + 0x84)) >= D_800BF808_f4d3.sA) {
                    *(u16 *)(a + 0x32) = (u16)D_800BF808_f4d3.sA - (*(u16 *)(a + 0x86) - *(u16 *)(a + 0x84));
                    goto five;
                }
            } else {
                f_ResolveActorAreaPlanePosition(a);
                if (f_ProbeActorTerrainAlongFacing(a, 0, (s16)(*(u16 *)(a + 0x86) - *(u16 *)(a + 0x84))) != 0) {
                    a[5] = 5;
                    *(s16 *)(a + 0x4A) = 0;
                }
            }
        } else {
            f_ResolveActorAreaPlanePosition(a);
            r = f_ProbeActorTerrainAlongFacing(a, 0, (s16)(*(u16 *)(a + 0x86) - *(u16 *)(a + 0x84)));
            if (r == 1) {
                goto five;
            }
            if (r == 2) {
                if (!(*(s16 *)D_1F8001A6 & 0x8000)) {
                    goto five;
                }
                if (D_800BF870.unk0 == 8) {
                    goto five;
                }
                if (D_800BF870.unk0 != 1 || a[2] == 0) {
                    a[5] = 6;
                }
            }
        }
        break;
    five:
        a[5] = 5;
        *(s16 *)(a + 0x4A) = 0;
        break;
    case 3:
        if ((!(a[0x28] & 0x80) || (D_800BF808_f4d3.uE != 0 && D_800BF808_f4d3.uF == *(s16 *)(a + 0x6A))) && a[0x29] == 0) {
            *(s16 *)(a + 0x4A) = 0x2000;
            a[5]--;
        }
        break;
    case 6:
        *(s32 *)(a + 0x30) += *(s16 *)(a + 0x4A) << 8;
        if (*(s16 *)(a + 0x4A) < 0x3000) {
            *(u16 *)(a + 0x4A) += *(u16 *)(a + 0x50);
        }
        if (func_80077ACC(a, *(s16 *)(a + 0x2E), *(s16 *)(a + 0x32), *(s16 *)(a + 0x36)) == 0) {
            a[4] = 3;
        }
        break;
    }
    if (alt == 0) {
        if (!(*(u16 *)D_1F80017C & 0x1F)) {
            a[0xD] |= 0x20;
        } else {
            a[0xD] &= 0xDF;
        }
    } else if (!(*(u16 *)D_1F80017C & 0x1F)) {
        a[0xD] |= 2;
    } else {
        a[0xD] &= 0xFD;
    }
}

s32 f_GrantPickupHealth(u8 *a, s32 n)
{
    u8 *t = (u8 *)D_800E7E80;
    s32 h;
    s32 ne;
    s32 ne_c;

    switch (a[7]) {
    case 0:
        h = *(s16 *)(t + 0x16E);
        if (h <= 0) {
            return 0;
        }
        ne = *(s16 *)(t + 0x170) != h;
        ne_c = ne;
        a[7] = 1;
        *(s16 *)(a + 0x40) = 0x10;
        D_800ED058_93c7[9] |= 2;
        *(s16 *)(t + 0x16E) += n;
        if (*(s16 *)(t + 0x16E) >= D_800BF870.pad1[0xC]) {
            *(s16 *)(t + 0x16E) = D_800BF870.pad1[0xC];
        }
        if (ne_c) {
            *(s16 *)(t + 0x170) = *(s16 *)(t + 0x16E) - 1;
        } else {
            *(s16 *)(t + 0x170) = *(s16 *)(t + 0x16E);
        }
        func_80072114(a, n, t, h);
        return 0;
    case 1:
        if (--*(s16 *)(a + 0x40) == -1) {
            D_800ED058_93c7[9] &= 0xFD;
            return 1;
        }
        return 0;
    }
    return 0;
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_80049F80);

/* f_DespawnGrabbedItem, inlined */
static inline s32 Despawn_A2A0(s32 arg0) {
    s32 temp_v0;

    temp_v0 = f_SpawnTransientEffect(0x1F, -0x8C);
    if (temp_v0 != 0) {
        M2C_FIELD(temp_v0, u8 *, 0x28) = (u8) (M2C_FIELD(temp_v0, u8 *, 0x28) | 0x80);
        M2C_FIELD(temp_v0, u16 *, 0x2C) = (u16) M2C_FIELD(arg0, u16 *, 0x2E);
        M2C_FIELD(temp_v0, u16 *, 0x2E) = (u16) M2C_FIELD(arg0, u16 *, 0x32);
        M2C_FIELD(temp_v0, u16 *, 0x30) = (u16) M2C_FIELD(arg0, u16 *, 0x36);
    }
    return f_PlaySoundEffect(0x28, 0, 0);
}
s32 func_8004A118(u8 *a)
{
    u8 *g;
    s32 k;
    u8 c;

    switch (a[6]) {
    case 0:
        if (D_800E7FEE <= 0) {
            break;
        }
        Despawn_A2A0((s32)a);
        g = (u8 *)&D_800BF870;
        c = ++g[0x12];
        if (c == 1) {
            f_QueueResourceMessage(0x17, 0x41);
            return 1;
        }
        if (c != 2) {
            goto one;
        }
        k = (g[0xAE] == 0xFF) ? 0xE : ((g[0xD] < 8) ? 0xE : 0x17);
        f_QueueResourceMessage(k, 0x41);
        {
            u8 *h = (u8 *)&D_800BF870;
            h[0x12] -= 2;
        }
        a[7] = 0;
        a[6]++;
        D_800ED058_93c7[9] |= 2;
    case 1:
    one:
        if (func_80049F80(a)) {
            D_800ED058_93c7[9] &= ~2;
            return 1;
        }
        break;
    }
    return 0;
}

s32 func_8004A2A0(u8 *a)
{
    u8 *g;
    s32 k;

    switch (a[6]) {
    case 0:
        if (D_800E7FEE <= 0) {
            break;
        }
        Despawn_A2A0((s32)a);
        g = (u8 *)&D_800BF870;
        k = (g[0xAE] == 0xFF) ? 0xC : ((g[0xD] < 8) ? 0xC : 0x16);
        f_QueueResourceMessage(k, 0x41);
        a[7] = 0;
        a[6]++;
        D_800ED058_93c7[9] |= 2;
    case 1:
        if (func_80049F80(a)) {
            D_800ED058_93c7[9] &= ~2;
            return 1;
        }
        break;
    }
    return 0;
}

extern u8 D_800BFB24;
extern u8 D_800BFB26;
extern u8 D_800BFB28;
void f_AddItemWithMessage(s32 item, s32 n);
void f_AddItemWithoutMessage(s32 item, s32 n);
void f_RemoveItemWithoutMessage(s32 item, s32 count);
void f_QueueResourceMessage(s16 id, u8 arg);
s32 f_GrantNonGemPickupReward(u8 *a)
{
    s32 it;
    u8 *h;
    s32 ev;
    s32 m;
    u8 *e;

    if (D_800E7FEE == 0) {
        return 0;
    }
    switch (*(s16 *)(a + 0x68)) {
    case 1:
        it = *(s16 *)(a + 0x68);
        f_AddItemWithMessage(it, 1);
        ev = 0x1E;
        goto set_ev;
    case 4:
        f_StartEvent(9);
    case 2:
    case 3:
    case 5:
    case 7:
    case 8:
    case 9:
        it = *(s16 *)(a + 0x68);
        f_AddItemWithMessage(it, 1);
        D_800BF88C = it;
        D_800E7EEC = it;
        break;
    case 6:
        it = *(s16 *)(a + 0x68);
        f_AddItemWithMessage(it, 1);
        ev = 0xF;
    set_ev:
        D_800BF88C = it;
        D_800E7EEC = it;
        f_UpdateEvent(ev);
        break;
    case 0xB:
        f_AddItemWithMessage(0xB, 1);
        {
            u8 *tt = (u8 *)D_800E7E80;
            u8 vv = 1;
            u8 *gg = (u8 *)&D_800BF870;
            gg[0x1D] = vv;
            tt[0x6D] = vv;
            func_80067DA8(tt);
            gg[0x15F]++;
        }
        break;
    case 0xC:
        f_AddItemWithMessage(0xC, 1);
        {
            u8 *tt = (u8 *)D_800E7E80;
            u8 vv = 2;
            u8 *gg = (u8 *)&D_800BF870;
            gg[0x1D] = vv;
            tt[0x6D] = vv;
            func_80067DA8(tt);
            gg[0x15F]++;
        }
        break;
    case 0x89:
        f_AddItemWithoutMessage(0x60, 2);
        f_QueueItemMessage(0x89, 2);
        break;
    case 0x57:
        f_AddItemWithoutMessage(0x4D, 2);
        f_QueueItemMessage(0x57, 2);
        f_StartEvent(0x3E);
        break;
    case 0x8A:
        f_AddItemWithoutMessage(0x7C, 3);
        f_QueueItemMessage(0x8A, 2);
        goto ev50;
    case 0x70:
        if (D_800BFB24 == 0) {
            f_AddItemWithoutMessage(0x70, 1);
            m = 0x10;
        } else {
            f_AddItemWithoutMessage(0x6F, 1);
            f_RemoveItemWithoutMessage(0x70, 1);
            m = 0x11;
        }
        goto msg;
    case 0x72:
        if (D_800BFB26 == 0) {
            f_AddItemWithoutMessage(0x72, 1);
            m = 0x12;
        } else {
            f_AddItemWithoutMessage(0x71, 1);
            f_RemoveItemWithoutMessage(0x72, 1);
            m = 0x13;
        }
        goto msg;
    case 0x74:
        if (D_800BFB28 == 0) {
            f_AddItemWithoutMessage(0x74, 1);
            m = 0x14;
        } else {
            f_AddItemWithoutMessage(0x73, 1);
            f_RemoveItemWithoutMessage(0x74, 1);
            m = 0x15;
        }
    msg:
        f_QueueResourceMessage(m, 0x41);
        break;
    case 0x2F:
        f_AddItemWithMessage(*(s16 *)(a + 0x68), 1);
        f_StartEvent(0x18);
        break;
    case 0x47:
        f_AddItemWithMessage(*(s16 *)(a + 0x68), 1);
        f_StartEvent(0x4D);
        break;
    case 0x6A:
        f_AddItemWithMessage(*(s16 *)(a + 0x68), 1);
        f_UpdateEvent(0x58);
        break;
    case 0x6B:
        f_AddItemWithMessage(*(s16 *)(a + 0x68), 1);
        f_UpdateEvent(0x59);
        break;
    case 0x7C:
        f_AddItemWithMessage(*(s16 *)(a + 0x68), 1);
    ev50:
        f_StartEvent(0x50);
        break;
    case 0xA6:
        f_AddItemWithMessage(*(s16 *)(a + 0x68), 1);
        func_80114F24(a);
        break;
    case 0xA0:
    case 0xA1:
    case 0xA2:
    case 0xA3:
        func_80115AEC(a);
        break;
    case 0x91:
        h = (u8 *)&D_800BF870;
        if (h[0xD] == 8) {
            h[0xD] = h[0xC];
        }
        h[0xC] = 0x10;
        {
            u8 *p = (u8 *)D_800E7E80;
            s16 x = h[0xD];

            *(s16 *)(p + 0x16E) = x;
            *(s16 *)(p + 0x170) = x;
        }
        f_QueueResourceMessage(0xF, 0x41);
        e = (u8 *)f_SpawnTransientEffect(0x711, 0);
        if (e != NULL) {
            e[0x28] |= 0x80;
        }
        break;
    case 0x96:
    case 0x97:
    case 0x99:
    case 0x9A:
        {
            u8 *k = (u8 *)&D_800BF870;

            *(s32 *)(k + 4) += 100000;
        }
        func_80071B44((s32)a, 100000, 0);
    default:
        f_AddItemWithMessage(*(s16 *)(a + 0x68), 1);
        break;
    }
    Despawn_A2A0((s32)a);
    return 1;
}

INCLUDE_ASM("asm/main/nonmatchings/main", f_InitializeSpriteGroundPickupFromRewardSelector);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8004A9A4);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8004AAC4);

s32 f_DespawnGrabbedItem(s32 arg0) {
    s32 temp_v0;

    temp_v0 = f_SpawnTransientEffect(0x1F, -0x8C);
    if (temp_v0 != 0) {
        M2C_FIELD(temp_v0, u8 *, 0x28) = (u8) (M2C_FIELD(temp_v0, u8 *, 0x28) | 0x80);
        M2C_FIELD(temp_v0, u16 *, 0x2C) = (u16) M2C_FIELD(arg0, u16 *, 0x2E);
        M2C_FIELD(temp_v0, u16 *, 0x2E) = (u16) M2C_FIELD(arg0, u16 *, 0x32);
        M2C_FIELD(temp_v0, u16 *, 0x30) = (u16) M2C_FIELD(arg0, u16 *, 0x36);
    }
    return f_PlaySoundEffect(0x28, 0, 0);
}

extern u8 D_1F800020[];
extern s16 D_1F8000C8[];
void func_8004B150(u8 *a, s32 mode)
{
    if (a[5] == 0) {
        a[5]++;
        a[0] = 1;
        if (mode == 0) {
            a[0x18] = 0;
        } else {
            a[0x18] = 0xFF;
            a[0x19] = 0xFF;
            a[0x1A] = 0xFF;
        }
    }
    if (mode == 0) {
        if (!(D_1F80017C_0fe7 & 0x1F)) {
            a[0xD] |= 0x20;
        } else {
            a[0xD] &= 0xDF;
        }
    } else {
        if (!(D_1F80017C_0fe7 & 0x1F)) {
            a[0xD] |= 2;
        } else {
            a[0xD] &= 0xFD;
        }
    }
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_8004B208);

void func_8004B2E8(void)
{
    u8 *e = f_SpawnTransientEffect(0x1F, -0x8C);
    u16 x, y, z;

    if (e != 0) {
        e[0x28] |= 0x80;
        x = D_1F800160;
        y = D_1F800162;
        z = D_1F800164;
        *(s16 *)(e + 0x2C) = x;
        *(s16 *)(e + 0x2E) = y;
        *(s16 *)(e + 0x30) = z;
    }
    f_PlaySoundEffect(0x28, 0, 0);
}

void f_SetPickupWhiteTintEnabled(void *arg0, s32 arg1)
{
  unsigned long new_var;
  new_var = 0xFF;
  if (arg1 == 0)
  {
    *((s8 *) (((signed char *) arg0) + 0x18)) = 0;
    return;
  }
  *((s8 *) (((signed char *) arg0) + 0x18)) = new_var;
  *((s8 *) (((signed char *) arg0) + 0x19)) = new_var;
  *((s8 *) (((signed char *) arg0) + 0x1A)) = new_var;
}

extern s8 D_1F80017C[];
void f_UpdatePickupBlinkRenderFlag(void *arg0, s32 arg1) {
    if (arg1 == 0) {
        if (!(*((u16 *)D_1F80017C) & 0x1F)) {
            M2C_FIELD(arg0, u8 *, 0xD) = (u8) (M2C_FIELD(arg0, u8 *, 0xD) | 0x20);
            return;
        }
        M2C_FIELD(arg0, u8 *, 0xD) = (u8) (M2C_FIELD(arg0, u8 *, 0xD) & 0xDF);
        return;
    }
    if (!(*((u16 *)D_1F80017C) & 0x1F)) {
        M2C_FIELD(arg0, u8 *, 0xD) = (u8) (M2C_FIELD(arg0, u8 *, 0xD) | 2);
        return;
    }
    M2C_FIELD(arg0, u8 *, 0xD) = (u8) (M2C_FIELD(arg0, u8 *, 0xD) & 0xFD);
}

s32 func_8004B3F4(s32 a, s32 b)
{
    GameState *g = &D_800BF870;

    *(s32 *)((u8 *)g + 4) += b;
    func_80071B44(a, b, 0);
    return 1;
}

extern s8 D_800BF820;
s32 func_8004B428(s32 arg0) {
    s32 temp_v0;

    temp_v0 = f_SpawnTransientEffect(0x1F, -0x8C);
    if (temp_v0 != 0) {
        M2C_FIELD(temp_v0, u8 *, 0x28) = (u8) (M2C_FIELD(temp_v0, u8 *, 0x28) | 0x80);
        M2C_FIELD(temp_v0, u16 *, 0x2C) = (u16) M2C_FIELD(arg0, u16 *, 0x2E);
        M2C_FIELD(temp_v0, u16 *, 0x2E) = (u16) M2C_FIELD(arg0, u16 *, 0x32);
        M2C_FIELD(temp_v0, u16 *, 0x30) = (u16) M2C_FIELD(arg0, u16 *, 0x36);
    }
    f_PlaySoundEffect(0x28, 0, 0);
    D_800BF820 = 1;
    return 1;
}

void func_8004B4B0(s32 item)
{
    f_AddItemWithMessage(item, 1);
    D_800BF88C = item;
    D_800E7EEC = item;
}

void func_8004B4E8(s32 item, u8 v)
{
    f_AddItemWithMessage(item, 1);
    D_800BF88D = v;
    D_800E7E80[0x6D] = v;
    func_80067DA8(D_800E7E80);
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_8004B528);

s32 f_UpdateActorUnscaledModelTransforms(s32 arg0);
void f_ResetTombaControlState(void *arg0);
u8 *f_AllocateActor(u8 *owner, u8 flags, u8 kind, u8 type);
void f_QueueClass5ActorForRender(s32 arg0);
s16 f_CalculateYawFromPositionToPoint(s16 *pos, s16 x, s16 z);
/* f_SpawnBackEquipmentProxyActor, inlined */
static inline u8 *SpawnBack_B788(void *owner, u8 item, s16 clut)
{
    u8 *a = f_AllocateActor(owner, 0x81, 5, 1);

    if (a != NULL) {
        *(void **)(a + 0x1C) = func_8004BB38;
        a[3] = 0;
        *(s16 *)(a + 0x5C) = clut;
        do { /* a macro in the original source, probably */
            a[0x5E] = item;
        } while (0);
    }
    return a;
}
void func_8004B788(u8 *a)
{
    u8 *t = (u8 *)D_800E7E80;
    u8 *o = *(u8 **)(a + 0x14);
    u8 *g;
    u8 *n;
    u8 *p;
    u8 *q;
    s32 r;

    switch (a[5]) {
    case 0:
        if (t[5] != 0x12) {
            return;
        }
        a[5] = 1;
        {
            s32 x = *(s16 *)(o + 0x2E);
            s32 z = *(s16 *)(o + 0x36);

            D_1F800137[0] = 2;
            *(s16 *)(a + 0x60) = f_CalculateYawFromPositionToPoint((s16 *)(t + 0x2C), x, z);
        }
        f_ResetTombaControlState(t);
        return;
    case 1:
        if (f_StepActorYawTowardAngle((s32)t, *(s16 *)(a + 0x60), 0x100)) {
            a[5]++;
        }
        *(u16 *)(a + 0x56) = *(u16 *)(t + 0x56);
        break;
    case 2:
        r = func_8004B528(a, o);
        if (r == 1) {
            a[5]++;
            o[0x29] = r;
        }
        break;
    case 3:
        if (func_8004B528(a, o) == 2) {
            g = (u8 *)&D_800BF870;
            if (g[0] == 0 && g[0x48] != 0xFF) {
                n = SpawnBack_B788(a, 0, 0);
                if (n != NULL) {
                    g[0x1E] = 0x28;
                    t[0x6E] = 0x28;
                    *(u8 **)(t + 0x74) = n;
                }
            }
            a[4] = 3;
            o[0x29] = 2;
        }
        break;
    }
    p = *(u8 **)(t + 0xDC);
    q = *(u8 **)(t + 0xD0);
    *(s16 *)(a + 0x2E) = (*(s32 *)(p + 0x2C) + *(s32 *)(q + 0x2C)) / 2;
    *(s16 *)(a + 0x32) = (*(s32 *)(p + 0x30) + *(s32 *)(q + 0x30)) / 2;
    *(s16 *)(a + 0x36) = (*(s32 *)(p + 0x34) + *(s32 *)(q + 0x34)) / 2;
    if (a[0x28] & 0x7F) {
        f_UpdateActorUnscaledModelTransforms((s32)a);
    }
draw:
    a[1] = 1;
    f_QueueClass5ActorForRender((s32)a);
}

INCLUDE_ASM("asm/main/nonmatchings/main", f_FillEquippedBucketFromSource);

/* func_8004BEF4, inlined */
static inline void Init_BB38(u8 *a)
{
    s32 r;
    u16 k = *(u16 *)(a + 0x5C);

    if (k == 0) {
        r = f_InitializeSinglePartActorModel(a, 1, 0);
    } else if (k == 1) {
        r = f_InitializeSinglePartActorModel(a, 1, 1);
    } else {
        r = f_InitializeSinglePartActorModel(a, 1, 0x17);
    }
    if (r == 0) {
        *(s16 *)(a + 0x80) = 0x46;
        *(s16 *)(a + 0x82) = 0x8C;
        *(s16 *)(a + 0x84) = 0x64;
        *(s16 *)(a + 0x86) = 0x64;
        *(s16 *)(a + 0x54) = 0;
        *(s16 *)(a + 0x56) = 0;
        *(s16 *)(a + 0x58) = 0;
        a[0x29] = 0;
    }
}
void func_8004BB38(u8 *a)
{
    u8 v;

    switch (a[4]) {
    case 0:
        a[4] = 1;
        if (a[3] != 0) {
            break;
        }
        Init_BB38(a);
        break;
    case 1:
        if (a[3] != 0) {
            break;
        }
        switch (a[0x5E]) {
        case 0:
            switch (a[5]) {
            case 0:
                a[0] = 3;
                *(s16 *)(a + 0x88) = -0x50;
                a[5] = 1;
                *(s16 *)(a + 0x8A) = 0x14;
                *(s16 *)(a + 0x8C) = 0;
            case 1:
                func_80051614(a, a + 0x88, 0, 0);
                v = D_800E7E81;
                a[1] = v;
                if (v != 0) {
                    f_QueueClass5ActorForRender((s32)a);
                }
                break;
            }
            break;
        case 1:
            func_8004B788(a);
            break;
        }
        break;
    case 2:
        if (a[3] == 0) {
            f_FillEquippedBucketFromSource(a);
        }
        break;
    case 3:
        f_ResolveEffectEightByteStreamPayload(a);
        break;
    }
}

u8 *f_SpawnBackEquipmentProxyActor(void *owner, u8 item, s16 clut)
{
    u8 *a = f_AllocateActor(owner, 0x81, 5, 1);

    if (a != NULL) {
        *(void **)(a + 0x1C) = func_8004BB38;
        a[3] = 0;
        *(s16 *)(a + 0x5C) = clut;
        do { /* a macro in the original source, probably */
            a[0x5E] = item;
        } while (0);
    }
    return a;
}

INCLUDE_ASM("asm/main/nonmatchings/main", f_PositionActorFromModelParts);

void f_SetEquippedBackItemActor(s8 item, s32 actor)
{
    D_800BF88E = item;
    D_800E7E80[0x6E] = item;
    *(s32 *)(D_800E7E80 + 0x74) = actor;
}

void f_ClearBackItem(void)
{
    D_800BF81C = 0;
    D_800BF88E = 0;
    D_800E7E80[0x6E] = 0;
    (*(u8 **)(D_800E7E80 + 0x74))[4] = 3;
    *(s32 *)(D_800E7E80 + 0x74) = 0;
}

void func_8004BEF4(u8 *a)
{
    s32 r;
    u16 k = *(u16 *)(a + 0x5C);

    if (k == 0) {
        r = f_InitializeSinglePartActorModel(a, 1, 0);
    } else if (k == 1) {
        r = f_InitializeSinglePartActorModel(a, 1, 1);
    } else {
        r = f_InitializeSinglePartActorModel(a, 1, 0x17);
    }
    if (r == 0) {
        *(s16 *)(a + 0x80) = 0x46;
        *(s16 *)(a + 0x82) = 0x8C;
        *(s16 *)(a + 0x84) = 0x64;
        *(s16 *)(a + 0x86) = 0x64;
        *(s16 *)(a + 0x54) = 0;
        *(s16 *)(a + 0x56) = 0;
        *(s16 *)(a + 0x58) = 0;
        a[0x29] = 0;
    }
}

void func_8004BF84(u8 *a)
{
    u8 v;

    switch (a[5]) {
    case 0:
        a[5]++;
        a[0] = 3;
        *(s16 *)(a + 0x88) = -0x50;
        *(s16 *)(a + 0x8A) = 0x14;
        *(s16 *)(a + 0x8C) = 0;
    case 1:
        func_80051614(a, a + 0x88, 0, 0);
        v = D_800E7E81;
        a[1] = v;
        if (v != 0) {
            f_QueueClass5ActorForRender(a);
        }
        break;
    }
}

void func_8004C01C(u8 *a)
{
    switch (a[0x5E]) {
    case 0:
        switch (a[5]) {
        case 0:
            a[5] = 1;
            a[0] = 3;
            *(s16 *)(a + 0x88) = -0x50;
            *(s16 *)(a + 0x8A) = 0x14;
            *(s16 *)(a + 0x8C) = 0;
        case 1:
            func_80051614(a, a + 0x88, 0, 0);
            if ((a[1] = D_800E7E81) != 0) {
                f_QueueClass5ActorForRender((s32)a);
            }
            break;
        }
        break;
    case 1:
        func_8004B788(a);
        break;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/main", f_SpawnAreaIndexedPersistentPickup);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8004C238);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8004C930);

u8 *f_SpawnAreaIndexedPersistentPickupOnce(void *area, u8 idx)
{
    Bits48_808 *g;
    s32 bit;
    u8 *r;

    if (D_800BF870.unk0 == 0) {
        g = (Bits48_808 *)D_800BF808;
        bit = 1 << idx;
        if (g->bits & bit) {
            return 0;
        }
        r = f_SpawnAreaIndexedPersistentPickup(area, idx, 0);
        if (r != 0) {
            g->bits |= bit;
        }
        return r;
    }
    return f_SpawnAreaIndexedPersistentPickup(area, idx, 0);
}

void func_8004CC64(void *a, u8 b)
{
    f_SpawnAreaIndexedPersistentPickup(a, b, 1);
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_8004CC88);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8004CE14);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8004D0D4);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8004D19C);

typedef struct { u8 pad[0x13]; u8 n; u8 ids[1]; } List_D298;
void func_8004D298(s32 k)
{
    s32 id;
    s32 i;

    if (k == 0) {
        id = 0x17;
    } else if (k == 1) {
        id = 0x18;
    } else if (k == 2) {
        id = 0x19;
    } else if (k == 3) {
        id = 0x1A;
    } else if (k == 4) {
        id = 0x1B;
    } else {
        id = 0x1C;
    }
    for (i = 0; i < ((List_D298 *)&D_800BF870)->n; i++) {
        if (((List_D298 *)&D_800BF870)->ids[i] == id) {
            ((List_D298 *)&D_800BF870)->ids[i] |= 0x80;
            return;
        }
    }
}

typedef struct { u8 kind; u8 pad[11]; } ItemDef_D330;
typedef struct {
    u8 pad0[0x13];
    u8 nKey;
    u8 keys[0x1D];
    u8 n31;
    u8 n32;
    u8 pad33[0x211];
    u8 counts[0x100];
    u8 order[0x100];
} Inv_D330;
extern Inv_D330 D_800BF870_inv;
extern ItemDef_D330 D_800A2BE8[];
void f_AddInventoryQuantity(s32 item, s32 n)
{
    s32 i;

    if ((u32)(item - 0x17) < 6) {
        D_800BF870_inv.keys[D_800BF870_inv.nKey] = item;
        D_800BF870_inv.nKey++;
    }
    if (D_800BF870_inv.counts[item] == 0) {
        if (D_800A2BE8[item].kind == 0) {
            for (i = 0; i < 0x100; i++) {
                if (D_800BF870_inv.counts[i] != 0 && D_800A2BE8[i].kind == 0) {
                    D_800BF870_inv.order[i]++;
                }
            }
            D_800BF870_inv.order[item] = 0;
            D_800BF870_inv.n32++;
        } else {
            for (i = 0; i < 0x100; i++) {
                if (D_800BF870_inv.counts[i] != 0 && D_800A2BE8[i].kind != 0) {
                    D_800BF870_inv.order[i]++;
                }
            }
            D_800BF870_inv.order[item] = 0;
            D_800BF870_inv.n31++;
        }
    }
    D_800BF870_inv.counts[item] += n;
    if (D_800BF870_inv.counts[item] >= 100) {
        D_800BF870_inv.counts[item] = 99;
    }
}

void f_AddItemWithMessage(s32 item, s32 n) {
    f_AddInventoryQuantity(item, n);
    f_QueueItemMessage(item, 2);
}

void f_AddItemWithoutMessage(s32 item, s32 n) {
    f_AddInventoryQuantity(item, n);
}

void f_CompactInventoryAfterRemoval(s32 item)
{
    s32 i;
    s32 o;

    if (D_800BF870_inv.counts[item] == 0) {
        o = D_800BF870_inv.order[item];
        D_800BF870_inv.order[item] = 0;
        if (D_800A2BE8[item].kind == 0) {
            D_800BF870_inv.n32--;
            for (i = 0; i < 0x100; i++) {
                if (D_800A2BE8[i].kind == 0 && o < D_800BF870_inv.order[i]) {
                    D_800BF870_inv.order[i]--;
                }
            }
        } else {
            D_800BF870_inv.n31--;
            for (i = 0; i < 0x100; i++) {
                if (D_800A2BE8[i].kind != 0 && o < D_800BF870_inv.order[i]) {
                    D_800BF870_inv.order[i]--;
                }
            }
        }
    }
}

void f_RemoveItemWithMessage(s32 item, s32 count)
{
    D_800BF870.itemCounts[item] -= count;
    f_QueueItemMessage(item, 1);
    f_CompactInventoryAfterRemoval(item);
}

void f_RemoveItemWithoutMessage(s32 item, s32 count)
{
    D_800BF870.itemCounts[item] -= count;
    f_CompactInventoryAfterRemoval(item);
}

void f_RemoveItemWithAltMessage(s32 item, s32 count)
{
    D_800BF870.itemCounts[item] -= count;
    f_QueueItemMessage(item, 4);
    f_CompactInventoryAfterRemoval(item);
}

void func_8004D6D4(s32 item)
{
    f_QueueItemMessage(item, 0);
}

void func_8004D6F4(s32 item)
{
    f_QueueItemMessage(item, 3);
}

typedef struct { u8 pad[0x444]; u8 world[0x80]; u8 other[0x80]; } Bits_D7EC;
typedef struct { u8 pad[0x10]; s32 y; u16 pad14; } Cam_DA30;
extern Cam_DA30 D_1F8000D0_d44f;
void func_8004D714(s32 n, u8 other)
{
    s16 bit;
    s32 byte = n / 8;

    bit = n - byte * 8;
    if (!other) {
        ((Bits_D7EC *)&D_800BF870)->world[(s16)byte] |= 1 << bit;
    } else {
        ((Bits_D7EC *)&D_800BF870)->other[(s16)byte] |= 1 << bit;
    }
}

extern s16 D_800BF808_e253[];
typedef struct SpuAttrLite { u32 mask; s16 mvolL; s16 mvolR; s16 h8; s16 hA; s16 hC; s16 hE; s16 h10; s16 h12; } SpuAttrLite;
extern SpuAttrLite D_800BE1F8;
typedef struct Slot4Cb { u8 b[0x4C]; } Slot4Cb;
extern Slot4Cb D_80100400_fb37[];
void func_8004D79C(s32 n)
{
    s32 byte = n / 8;
    s32 bit = n - byte * 8;

    D_800BF870.appleBits[(s16)byte] |= 1 << (s16)bit;
}

s32 f_TestWorldOrOtherPickupCollectedBit(s32 n, u8 other)
{
    s16 bit;
    s32 byte = n / 8;

    bit = n - byte * 8;
    if (!other) {
        return ((Bits_D7EC *)&D_800BF870)->world[(s16)byte] & (1 << bit);
    }
    return ((Bits_D7EC *)&D_800BF870)->other[(s16)byte] & (1 << bit);
}

s32 f_TestAppleCollectedBit(s32 n)
{
    s16 bit;
    s32 byte = n / 8;

    bit = n - byte * 8;
    return D_800BF870.appleBits[(s16)byte] & (1 << bit);
}

void func_8004D8B0(void)
{
    s32 i = 0x7F;
    u8 *p = (u8 *)&D_800BF870 + i;

    do {
        p[0x544] = 0;
        i--;
        p--;
    } while (i >= 0);
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_8004D8D8);

typedef struct { s16 vx, vy, vz, pad; } SVec_9DD0;
extern SVec_9DD0 D_1F8000C0_18ff;
extern SVec_9DD0 D_1F8000C8_65f7;
s32 f_UpdateUsedItemAttachmentPresentation(u8 *a)
{
    u8 *o;

    D_1F8000C0_18ff.vx = 0x14;
    *(s16 *)((u8 *)&D_1F8000C0_18ff + 2) = 0;
    o = D_800E7F50;
    *(s16 *)((u8 *)&D_1F8000C0_18ff + 4) = 0x32;
    ApplyMatrixSV(o + 0x18, &D_1F8000C0_18ff, &D_1F8000C8_65f7);
    *(u16 *)(a + 0x2E) = D_1F8000C8_65f7.vx + *(u16 *)(o + 0x2C);
    *(u16 *)(a + 0x32) = D_1F8000C8_65f7.vy + *(u16 *)(o + 0x30);
    *(u16 *)(a + 0x36) = D_1F8000C8_65f7.vz + *(u16 *)(o + 0x34);
    f_TestAndQueueActorForRender(a);
    f_AdvanceActorTimedFrameSequence(a);
    return D_800BF80A_8fc3 == 0;
}

s32 func_8004DBB0(void) {
    return D_800BF80A_8fc3 == 0;
}

s32 func_8004DBC0(s32 id)
{
    switch (id) {
    case 0x5C:
        return 0xBE;
    case 0x5B:
        return 0xBF;
    case 0x5A:
        return 0x103;
    case 0x59:
        return 0x160;
    case 0x69:
        return 0x138;
    case 0x66:
        return 0x113;
    case 0x6E:
        return 0x165;
    case 0x6D:
        return 0x164;
    case 0x6C:
        return 0x163;
    case 0x6A:
        return 0x139;
    case 0x6B:
        return 0x13A;
    case 0x68:
        return 0x114;
    case 0x67:
        return 0x112;
    case 0x98:
        return 0x166;
    case 0xA6:
        return 0x17D;
    case 0xA7:
        return 0x17C;
    case 0x5E:
        return 0xFE;
    case 0x5D:
        return 0xFF;
    }
    return 0;
}

extern s32 D_800ECF58_6489;
void f_StartActorTimedFrameSequence(u8 *actor, u16 **table, s32 index);
void func_8004DF94(u8 *a);
void func_8004E414(u8 *a);
void func_8004E808(u8 *a);
void func_8004E928(u8 *a);
void func_8004DE04(u8 *a);
u8 *func_8004DC84(s32 k, s32 mode)
{
    u8 *a = f_AllocateActor(NULL, 0x80, 3, 5);
    void *fn;
    s32 n;

    if (a == NULL) {
        return NULL;
    }
    if (mode == 0) {
        *(void **)(a + 0x1C) = func_8004DE04;
    } else if (mode == 1) {
        *(void **)(a + 0x1C) = func_8004DF94;
    } else if (mode == 2) {
        *(void **)(a + 0x1C) = func_8004E414;
    } else if (mode == 3) {
        *(void **)(a + 0x1C) = func_8004E808;
    } else if (mode == 4) {
        *(void **)(a + 0x1C) = func_8004E928;
    } else {
        *(void **)(a + 0x1C) = func_8004DE04;
    }
    *(s16 *)(a + 0x60) = k;
    n = func_8004DBC0(k);
    *(s32 *)(a + 0x3C) = D_800ECF58_6489;
    f_StartActorTimedFrameSequence(a, D_80017334, n);
    if (mode != 3) {
        u8 *s = D_800BF808;

        s[2] = 1;
        s[3] = k;
        D_1F800137_104c = 2;
    }
    return a;
}

void func_8004DD90(u8 *p)
{
    if (f_GrantPickupHealth(p, 1)) {
        if (--*(s16 *)(p + 0x42) == 0 || D_800E7FEE == D_800BF87D) {
            p[4] = 2;
        } else {
            p[7] = 0;
        }
    }
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_8004DE04);

typedef struct { u8 pad0[9]; u8 u9; } Flags058_DF94;
extern Flags058_DF94 D_800ED058_c3b3;
extern s32 D_800BF880;
extern u8 D_800BF881;
void func_8004DF94(u8 *a)
{
    u8 *t = D_800E7E80_f78d;

    switch (a[4]) {
    case 0:
        a[4] = 1;
        a[0xB] = 0x10;
        a[0xD] = 0;
        a[0x47] = 0;
        *(s16 *)(a + 0x5A) = 0;
        *(s16 *)(a + 0x5C) = 0;
        break;
    case 1:
        switch ((s16)(*(u16 *)(a + 0x60) - 0x66)) {
        case 3:
            if (f_UpdateUsedItemAttachmentPresentation(a) != 0) {
                f_ApplyTombaStatusCommand(t, 2);
                a[4] = 2;
            }
            break;
        case 0:
            switch (a[5]) {
            case 0:
                    if (f_UpdateUsedItemAttachmentPresentation(a) != 0) {
                        *(s16 *)(a + 0x42) = 0x10;
                        a[5]++;
                        if (D_800BF881 & 8) {
                            f_ApplyTombaStatusCommand(t, 2);
                        }
                    }
                break;
            case 1:
                func_8004DD90(a);
                break;
            }
            D_800ED058_c3b3.u9 |= 2;
            break;
        case 8:
            if (f_UpdateUsedItemAttachmentPresentation(a) != 0) {
                if (D_800BF880 & 0x3000) {
                    f_ApplyTombaStatusCommand(t, 5);
                } else {
                    f_ApplyTombaStatusCommand(t, 4);
                }
                a[4] = 2;
            }
            break;
        case 7:
            if (f_UpdateUsedItemAttachmentPresentation(a) != 0) {
                if (D_800BF881 & 4) {
                    f_ApplyTombaStatusCommand(t, 7);
                } else {
                    f_ApplyTombaStatusCommand(t, 6);
                }
                a[4] = 2;
            }
            break;
        case 4:
            if (f_UpdateUsedItemAttachmentPresentation(a) != 0) {
                if (!(D_800BF881 & 1)) {
                    f_ApplyTombaStatusCommand(t, 8);
                } else {
                    f_ApplyTombaStatusCommand(t, 9);
                }
                a[4] = 2;
            }
            break;
        case 5:
            if (f_UpdateUsedItemAttachmentPresentation(a) != 0) {
                f_ApplyTombaStatusCommand(D_800E7E80_f78d, 0xA);
                a[4] = 2;
            }
            break;
        case 2:
            switch (a[5]) {
            case 0:
                    if (f_UpdateUsedItemAttachmentPresentation(a) != 0) {
                        *(s16 *)(a + 0x42) = 0x10;
                        a[5]++;
                        if ((D_800BF881 & 2) || (D_800BF881 & 1)) {
                            f_ApplyTombaStatusCommand(D_800E7E80_f78d, 0xA);
                        }
                    }
                break;
            case 1:
                func_8004DD90(a);
                break;
            }
            D_800ED058_c3b3.u9 |= 2;
            break;
        case 1:
            switch (a[5]) {
            case 0:
                    if (f_UpdateUsedItemAttachmentPresentation(a) != 0) {
                        *(s16 *)(a + 0x42) = 0x10;
                        a[5]++;
                    }
                break;
            case 1:
                func_8004DD90(a);
                break;
            }
            D_800ED058_c3b3.u9 |= 2;
            break;
        }
        a[1] = 1;
        break;
    case 2:
        a[4]++;
        D_1F800137_104c = 0;
        D_800ED058_c3b3.u9 &= 0xFD;
        break;
    case 3:
        f_ResolveEffectEightByteStreamPayload(a);
        break;
    }
}

extern u8 D_1F800207_9c67;
s32 func_8004E29C(u8 *a)
{
    switch (*(s16 *)(a + 0x60)) {
    case 0x6F: case 0x70:
        if (D_800BF870.unk0 != 1) {
            return 0;
        }
        if (D_1F800207_9c67 != 0xB) {
            return 0;
        }
        if (D_1F800164_d75f >= 0x1495) {
            return 0;
        }
        if (D_800BF870.pad1[0xA5] != 0) {
            return 2;
        }
        f_StartEvent(0x62);
        return 1;
    case 0x71: case 0x72:
        if (D_800BF870.unk0 != 4) {
            return 0;
        }
        if (D_1F800207_9c67 != 0xF) {
            return 0;
        }
        if (D_1F800164_d75f >= 0x16D2) {
            return 0;
        }
        if (D_800BF870.pad1[0xA6] != 0) {
            return 2;
        }
        f_StartEvent(0x63);
        return 1;
    case 0x73: case 0x74:
        if (D_800BF870.unk0 != 6) {
            return 0;
        }
        if (D_1F800207_9c67 != 0xE) {
            return 0;
        }
        if (D_1F800164_d75f < 0x5FE0) {
            return 0;
        }
        if (D_800BF870.pad1[0xA7] != 0) {
            return 2;
        }
        f_StartEvent(0x64);
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_8004E414);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8004E808);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8004E928);

s16 f_MeasureEncodedMessageLine(u8 *msg, u8 *len)
{
    u8 *start;
    s32 w = 0;

    if (len != NULL) {
        start = msg;
    }
    for (;;) {
        switch (*msg) {
        case 0xFB:
            w += 8;
            break;
        case 0xFA:
        case 0xFF:
            if (len != NULL) {
                *len = msg - start;
            }
            return w;
        default:
            if (*msg < 0xC0) {
                w += 8;
            }
            break;
        }
        msg++;
    }
}

u8 *func_8004EAD0(u8 *out, u8 *src)
{
    u8 *s;
    u8 c;

    switch (src[0]) {
    case 0:
        *out = 0xF4;
        break;
    case 1:
        *out = 0xF2;
        break;
    case 2:
        *out = 0xF3;
        break;
    default:
        *out = 0xF0;
        break;
    }
    s = *(u8 **)(src + 4);
    for (out++; *s != 0; s++, out++) {
        c = *s;
        if (c == '\n' || c == ' ') {
            *out = 0xFB;
        } else {
            *out = c - 0x20;
        }
    }
    *out++ = 0xF0;
    *out = 0xFF;
    return out;
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_8004EB94);

void f_QueueItemMessage(s32 item, s32 kind)
{
    u16 msg[3];
    s32 style;

    msg[1] = kind | 0x8000;
    msg[2] = 0xFFFE;
    msg[0] = item;
    switch ((s16)kind) {
    case 0:
    case 3:
        style = 0x40;
        break;
    case 2:
        style = 0x42;
        break;
    case 1:
    default:
        style = 0x41;
        break;
    }
    f_QueuePopupMessage(msg, 1, style);
}

void f_QueuePopupMessage(u8 *text, s32, s32);
// Queues resource message `id` of the message bank as a pop-up.
void f_QueueResourceMessage(s16 id, u8 arg)
{
    f_QueuePopupMessage(D_800BF548.text + D_800BF548.offsets[id], -1, arg);
}

void func_8004EDDC(s16 a, s16 b)
{
    u16 m[6];

    m[1] = 0x8003;
    m[2] = 0xFFFF;
    m[4] = 0x8000;
    m[0] = a;
    m[3] = b;
    m[5] = 0xFFFE;
    f_QueuePopupMessage(m, 2, 0x40);
}

void f_ResetPopupRequest(PopupRequest *req)
{
    u32 none = 0xFFFF;
    s32 i;

    for (i = 11; i >= 0; i--) {
        req->entries[i] = none;
    }
    req->count = 0;
}

void *memset(void *, s32, s32);
void f_ResetPopupDisplayEntry(PopupDisplayEntry *e)
{
    memset(e, 0, sizeof(PopupDisplayEntry));
    e->unk3D = 0xFF;
    e->unk10 = 0xFF;
}

typedef struct { s32 w[0x23]; } Popup_EE90;
typedef struct { u8 pad[8]; s16 count; u8 padA[2]; Popup_EE90 e[1]; } PopupList_EE90;
void f_RemoveOldestPopupDisplayEntry(PopupList_EE90 *m)
{
    s32 i;

    m->count--;
    for (i = 0; i < m->count; i++) {
        m->e[i] = m->e[i + 1];
    }
    f_ResetPopupDisplayEntry((PopupDisplayEntry *)&m->e[i]);
}

// Copies one segment of an encoded message (bytes up to the 0xFA page break or the 0xFF end) and ends the copy
// with 0xFF; returns the end of the copy.
u8 *f_CopyEncodedMessageSegment(u8 *dst, u8 *src)
{
    u32 page = 0xFA;
    u32 end = 0xFF;

    do {
        *dst++ = *src++;
    } while (*src != page && *src != end);
    *dst = end;
    return dst;
}

extern u8 D_800BE1F8_296f[];
u8 *f_FindEncodedMessagePage(u8 *p, s32 n)
{
    if (n == 0) { return p; }
    for (;;) {
        if (*p == 0xFA) {
            if (--n == 0) { return p + 1; }
        }
        p++;
    }
}

extern u8 D_800E7E81;
u8 f_MeasureEncodedMessageBlock(u8 *msg, s16 *maxw)
{
    s32 n = 0;
    u8 len;
    s16 w;

    *maxw = 0;
    for (;;) {
        w = f_MeasureEncodedMessageLine(msg, &len);
        msg += len;
        if (*maxw < w) {
            *maxw = w;
        }
        n++;
        if (*msg == 0xFF) {
            break;
        }
        msg++;
    }
    return n;
}

INCLUDE_ASM("asm/main/nonmatchings/main", f_FormatPopupPayloadPage);

INCLUDE_ASM("asm/main/nonmatchings/main", f_AppendPopupDisplayEntry);

void f_PromoteNextPopupRequest(u8 *m)
{
    PopupReq32 *q;
    s32 i;
    PopupReq32 spare;

    func_80077D64();
    q = (PopupReq32 *)(m + 0x1B0);
    f_AppendPopupDisplayEntry(m, q);
    if (--*(s16 *)(m + 0xA) > 0) {
        i = 0;
        do {
            i++;
            q[0] = q[1];
            q++;
        } while (i < *(s16 *)(m + 0xA));
    }
    f_ResetPopupRequest(q);
}

void func_8004F430(void *arg0) {
    if (M2C_FIELD(arg0, s16 *, 0xA) != 0) {
        f_PromoteNextPopupRequest(arg0);
        M2C_FIELD(arg0, s16 *, 4) = 0;
        M2C_FIELD(arg0, s8 *, 1) = 1;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_8004F474);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8004F514);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8004F6D0);

INCLUDE_ASM("asm/main/nonmatchings/main", f_ForcePromotePopupRequest);

typedef struct { u16 *src; u16 entries[12]; u8 kind; u8 pad[3]; } PopReq_FA44;
typedef struct { u8 pad[0xA]; s16 n; u8 pad2[0x1A4]; PopReq_FA44 req[8]; } PopBank_FA44;
void f_ForcePromotePopupRequest(PopBank_FA44 *b);
void f_ResetPopupRequest(PopupRequest *req);

/* K&R definition: the narrow s16 / u8 parameters keep retail's register choice while matching the (u8 *, s32, s32) prototype above. */
void f_QueuePopupMessage(text, mode, kind)
    u8 *text;
    s16 mode;
    u8 kind;
{
    u16 *msg = (u16 *)text;
    PopBank_FA44 *b = (PopBank_FA44 *)&D_800BF548;
    PopReq_FA44 *r;
    u16 *d;
    u16 c;

    if (b->n >= 8) {
        f_ForcePromotePopupRequest(b);
    }
    r = &b->req[b->n];
    f_ResetPopupRequest((PopupRequest *)r);
    if (mode == -1) {
        r->src = msg;
    } else {
        u16 *s = msg;
        c = *msg;
        d = r->entries;
        while (c != 0xFFFE) {
            s++;
            *d = c;
            c = *s;
            d++;
        }
        *d = 0xFFFE;
    }
    r->kind = kind;
    b->n++;
}

void func_8004FB20(void) {
    memset(&D_800BF548, 0, 0x2BC);
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_8004FB4C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8004FD30);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8004FE84);

void func_8004FFB4(s16 *r, u32 kind, u8 flags, s32 ot)
{
    u8 *p = D_800BF544;
    u8 u1, u0, v0;
    u32 *o;

    D_800BF544 = p + 0x28;
    p[7] = 0x2C;
    if (flags & 0x80) {
        p[7] = 0x2E;
    }
    if (flags & 0x40) {
        *(u16 *)(p + 0xE) = (((flags & 0x1F) + 0x1F0) << 6) | 0x3F;
    } else {
        *(u16 *)(p + 0xE) = (((flags & 0x1F) + 0x1F0) << 6) | 0x3E;
    }
    if (flags & 0x20) {
        p[6] = 0x40;
        p[5] = 0x40;
        p[4] = 0x40;
    } else {
        p[7] |= 1;
    }
    *(u16 *)(p + 0x16) = 0x5F;
    *(s16 *)(p + 0x8) = r[0];
    *(s16 *)(p + 0xA) = r[1];
    *(s16 *)(p + 0x10) = r[0] + r[2];
    *(s16 *)(p + 0x12) = r[1];
    *(s16 *)(p + 0x18) = r[0];
    *(s16 *)(p + 0x1A) = r[1] + r[3];
    *(s16 *)(p + 0x20) = r[0] + r[2];
    *(s16 *)(p + 0x22) = r[1] + r[3];
    switch (kind) {
    case 0:
        u0 = 0xC0;
        v0 = 0x88;
        u1 = 0xC8;
        p[0xD] = v0;
        p[0x15] = v0;
        v0 = 0x90;
        p[0xC] = u0;
        p[0x14] = u1;
        p[0x1C] = u0;
        p[0x1D] = v0;
        p[0x24] = u1;
        p[0x25] = v0;
        break;
    case 1:
        u0 = 0xF0;
        v0 = 0x88;
        u1 = 0xF8;
        p[0xD] = v0;
        p[0x15] = v0;
        v0 = 0x90;
        p[0xC] = u0;
        p[0x14] = u1;
        p[0x1C] = u0;
        p[0x1D] = v0;
        p[0x24] = u1;
        p[0x25] = v0;
        break;
    case 2:
        u0 = 0xD0;
        v0 = 0x89;
        u1 = 0xD8;
        p[0xD] = v0;
        p[0x15] = v0;
        v0 = 0x8F;
        p[0xC] = u0;
        p[0x14] = u1;
        p[0x1C] = u0;
        p[0x1D] = v0;
        p[0x24] = u1;
        p[0x25] = v0;
        break;
    case 3:
        u0 = 0xE0;
        v0 = 0x89;
        u1 = 0xE8;
        p[0xD] = v0;
        p[0x15] = v0;
        v0 = 0x8F;
        p[0xC] = u0;
        p[0x14] = u1;
        p[0x1C] = u0;
        p[0x1D] = v0;
        p[0x24] = u1;
        p[0x25] = v0;
        break;
    case 4:
        u0 = 0xD8;
        v0 = 0x88;
        u1 = 0xDF;
        p[0xD] = v0;
        p[0x15] = v0;
        v0 = 0x8F;
        p[0xC] = u0;
        p[0x14] = u1;
        p[0x1C] = u0;
        p[0x1D] = v0;
        p[0x24] = u1;
        p[0x25] = v0;
        break;
    }
    o = D_800ED8C8 + ot;
    *(u32 *)p = *o | 0x09000000;
    *o = (u32)p;
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_8005019C);

extern volatile u16 D_800E809C_da0a;
void func_800506B4(void) {
    D_800E809C_da0a += 1;
}

void func_800506D0(void)
{
    u8 *p;

    for (p = (u8 *)0x801FE000; p < (u8 *)0x801FE150; p += 0x70) {
        if (*(u16 *)p == 1) {
            if (--*(s16 *)(p + 2) == 0) {
                *(u16 *)p = 2;
            }
        }
    }
}

extern u8 D_800EA0BC[];
extern s16 D_800E7E70;
extern s16 D_800E7E72;
void func_80050738(void)
{
    u8 *d0 = D_800EA0BC;
    u8 *d1 = d0 + 0x2070;
    u8 *s0;
    u8 *s1;

    SetDefDrawEnv(d0, 0, 0, 0x140, 0xF0);
    SetDefDrawEnv(d1, 0, 0x100, 0x140, 0xF0);
    SetDefDispEnv(d0 - 0x14, 0, 0x100, 0x140, 0xF0);
    SetDefDispEnv(d0 + 0x205C, 0, 0, 0x140, 0xF0);
    s0 = d0 - 0xC;
    s1 = d0 + 0x2064;
    MEMBER_AT(s16, s0, 4) = 0x100;
    MEMBER_AT(s16, s0, 6) = 0xE0;
    MEMBER_AT(s16, s1, 4) = 0x100;
    MEMBER_AT(s16, s1, 6) = 0xE0;
    d0[0x19] = 0;
    d0[0x1A] = 0;
    d0[0x1B] = 0;
    d1[0x19] = 0;
    d1[0x1A] = 0;
    d1[0x1B] = 0;
    MEMBER_AT(s16, s0, 0) = D_800E7E70;
    MEMBER_AT(s16, s0, 2) = D_800E7E72;
    MEMBER_AT(s16, s1, 0) = D_800E7E70;
    MEMBER_AT(s16, s1, 2) = D_800E7E72;
}

extern u16 D_1F800170;
extern u16 D_1F800174_de41;
extern u16 D_1F800176;
void func_8007263C(u8 *);
typedef struct { u8 pad[0x18]; u8 isbg; u8 r0, g0, b0; } DrawEnvLite_E80A8;
void f_SetDoubleBufferedClearColor(u8 r, u8 g, u8 b)
{
    u8 *base = D_800E80A8_42d3;
    DrawEnvLite_E80A8 *e0;
    DrawEnvLite_E80A8 *e1;
    u8 bg = base[0x202C];
    u8 r0, g0, b0;
    u8 *gs;

    base[0x409C] = 1;
    base[0x202C] = 1;
    e0 = (DrawEnvLite_E80A8 *)(base + 0x2014);
    r0 = base[0x202D];
    g0 = base[0x202E];
    b0 = base[0x202F];
    e1 = (DrawEnvLite_E80A8 *)(base + 0x4084);
    e0->r0 = r;
    e0->g0 = g;
    e0->b0 = b;
    e1->r0 = r;
    e1->g0 = g;
    e1->b0 = b;
    gs = (u8 *)&D_800BF870;
    gs[0x37] = (bg << 7) | 1;
    gs[0x34] = r0;
    gs[0x35] = g0;
    gs[0x36] = b0;
}

void func_80050894(s8 v)
{
    D_800E80A8[0x409C] = v;
    D_800E80A8[0x202C] = v;
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_800508A8);

extern u8 D_800BF816;
void func_80050970(void) {
    if (D_800BF816 != 0) {
        f_SetDoubleBufferedClearColor(0, 0, 0);
        return;
    }
    func_800508A8();
}

extern s16 D_801003F8;
void func_800509B4(void) {
    D_800E7E70 = 0;
    D_800E7E72 = 8;
    InitGeom();
    SetGeomOffset(0xA0, 0x78);
    D_801003F8 = 0x15E;
    SetGeomScreen(0x15E);
    func_80050738();
}

extern s8 D_1F800135[];
extern s8 D_1F80019B[];
extern s8 D_1F80019C[];
extern s8 D_1F800233[];
extern s8 D_1F800234[];
extern s8 D_1F800235[];
extern s8 D_1F800236[];
extern s8 D_1F80023B[];
extern s8 D_1F80027E[];
extern s16 D_800E809C;
void func_80050A0C(void) {
    D_800E809C = 0;
    *((s8 *)D_1F800235) = 2;
    *((s8 *)D_1F800135) = 0;
    *((s8 *)D_1F80019C) = 0;
    *((s8 *)D_1F80023B) = 0;
    *((s8 *)D_1F800233) = 0;
    *((s8 *)D_1F800236) = 0;
    *((s8 *)D_1F800234) = 0;
    *((s8 *)D_1F80019B) = 0;
    *((s8 *)D_1F80027E) = 0;
    srand(0x45);
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_80050A80);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80050B08);

INCLUDE_ASM("asm/main/nonmatchings/main", f_UpdateActorScaledPartTransforms);

INCLUDE_ASM("asm/main/nonmatchings/main", f_UpdateActorUnscaledPartTransforms);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80051464);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80051614);

void f_SetIdentityMatrix(s32 *m)
{
    m[0] = 0x1000;
    m[1] = 0;
    m[2] = 0x1000;
    m[3] = 0;
    m[4] = 0x1000;
    m[5] = 0;
    m[6] = 0;
    m[7] = 0;
}

void f_SetScaleMatrix(void *arg0, s16 arg1, s16 arg2, s16 arg3) {
    M2C_FIELD(arg0, s32 *, 0) = (s32) arg1;
    M2C_FIELD(arg0, s32 *, 4) = 0;
    M2C_FIELD(arg0, s32 *, 8) = (s32) arg2;
    M2C_FIELD(arg0, s32 *, 0xC) = 0;
    M2C_FIELD(arg0, s32 *, 0x10) = (s32) arg3;
    M2C_FIELD(arg0, s32 *, 0x14) = 0;
    M2C_FIELD(arg0, s32 *, 0x18) = 0;
    M2C_FIELD(arg0, s32 *, 0x1C) = 0;
}

s32 f_UpdateActorUnscaledModelTransforms(s32 arg0) {
    RotMatrix_gte(arg0 + 0x54, arg0 + 0x98);
    M2C_FIELD(arg0, s32 *, 0xAC) = (s32) M2C_FIELD(arg0, s16 *, 0x2E);
    M2C_FIELD(arg0, s32 *, 0xB0) = (s32) M2C_FIELD(arg0, s16 *, 0x32);
    M2C_FIELD(arg0, s32 *, 0xB4) = (s32) M2C_FIELD(arg0, s16 *, 0x36);
    return f_UpdateActorUnscaledPartTransforms(arg0);
}

void f_UpdateActorScaledModelTransforms(u8 *a)
{
    s32 *m = D_1F800000;
    s16 y = *(s16 *)(a + 0xBA);
    s32 x = *(s16 *)(a + 0xB8);
    s16 z;

    m[1] = 0;
    m[3] = 0;
    m[5] = 0;
    m[6] = 0;
    m[7] = 0;
    m[0] = x;
    z = *(s16 *)(a + 0xBC);
    m[2] = y;
    m[4] = z;
    RotMatrix_gte(a + 0x54, D_1F800020_edd9);
    MulMatrix0(D_1F800020_edd9, D_1F800000, a + 0x98);
    *(s32 *)(a + 0xAC) = *(s16 *)(a + 0x2E);
    *(s32 *)(a + 0xB0) = *(s16 *)(a + 0x32);
    *(s32 *)(a + 0xB4) = *(s16 *)(a + 0x36);
    f_UpdateActorScaledPartTransforms(a);
}

void f_UpdateActorScaledOffsetModelTransforms(u8 *a)
{
    s32 *m = D_1F800000;
    s16 y = *(s16 *)(a + 0xBA);
    s32 x = *(s16 *)(a + 0xB8);
    s16 z;

    m[1] = 0;
    m[3] = 0;
    m[5] = 0;
    m[6] = 0;
    m[7] = 0;
    m[0] = x;
    z = *(s16 *)(a + 0xBC);
    m[2] = y;
    m[4] = z;
    RotMatrix_gte(a + 0x54, D_1F800020_edd9);
    MulMatrix0(D_1F800020_edd9, D_1F800000, a + 0x98);
    ApplyMatrix(a + 0x98, a + 0x88, a + 0xAC);
    *(s32 *)(a + 0xAC) += *(s16 *)(a + 0x2E);
    *(s32 *)(a + 0xB0) += *(s16 *)(a + 0x32);
    *(s32 *)(a + 0xB4) += *(s16 *)(a + 0x36);
    f_UpdateActorScaledPartTransforms(a);
}

s32 f_AllocateActorModelPart(void);
s32 f_InitializeMultiPartActorModel(u8 *a, s32 n, u8 *base, u16 *def)
{
    s32 i;
    u8 *p;
    s32 *offs;
    u8 *a_p = a;
    u16 *d;

    if (D_800ED098 < n) {
        a_p[9] = 0;
        a_p[4] = 3;
        return 1;
    }
    d = def;
    a_p[9] = n;
    *(s16 *)(a_p + 0xBC) = 0x1000;
    *(s16 *)(a_p + 0xBA) = 0x1000;
    *(s16 *)(a_p + 0xB8) = 0x1000;
    a_p[8] = n;
    a_p[0xD] = 0;
    offs = (s32 *)(base + 4);

    for (i = 0; i < a_p[9]; i++) {
        p = f_AllocateActorModelPart();
        ((u8 **)(a_p + 0xC0))[i] = p;
        *(u16 *)(p + 6) = *d++;
        *(u16 *)(p + 0) = *d++;
        *(u16 *)(p + 2) = *d++;
        *(u16 *)(p + 4) = *d++;
        *(s16 *)(p + 0x38) = 0x1000;
        *(s16 *)(p + 0x3A) = 0x1000;
        *(s16 *)(p + 0x3C) = 0x1000;
        *(u8 **)(p + 0x40) = base + offs[i];
    }
    return 0;
}

void f_SetActorPartModel(u8 *actor, s32 bank, s32 index)
{
    s8 *base = D_800ECF58[bank];
    s32 *entry = (s32 *)base + index;

    *(s8 **)(actor + 0x40) = base + entry[1];
}

void func_80051B34(void *arg0, void *arg1) {
    M2C_FIELD(arg1, s32 *, 0) = (s32) M2C_FIELD(arg0, s32 *, 0);
    M2C_FIELD(arg1, s32 *, 4) = (s32) M2C_FIELD(arg0, s32 *, 4);
    M2C_FIELD(arg1, s32 *, 8) = (s32) M2C_FIELD(arg0, s32 *, 8);
    M2C_FIELD(arg1, s32 *, 0xC) = (s32) M2C_FIELD(arg0, s32 *, 0xC);
    M2C_FIELD(arg1, s32 *, 0x10) = (s32) M2C_FIELD(arg0, s32 *, 0x10);
}

/* f_SetActorPartModel, inlined */
static inline void SetModel_1B74(u8 *actor, s32 bank, s32 index)
{
    s8 *base = D_800ECF58[bank];
    s32 *entry = (s32 *)base + index;

    *(s8 **)(actor + 0x40) = base + entry[1];
}
s32 f_InitializeSinglePartActorModel(void *av, s32 bank, s32 index)
{
    u8 *a = av;

    if (D_800ED098 <= 0) {
        a[4] = 3;
        return 1;
    }
    a[8] = 1;
    a[9] = 1;
    a[0xD] = 0;
    *(s16 *)(a + 0xBC) = 0x1000;
    *(s16 *)(a + 0xBA) = 0x1000;
    *(s16 *)(a + 0xB8) = 0x1000;
    *(u8 **)(a + 0xC0) = (u8 *)f_AllocateActorModelPart();
    *(s16 *)(*(u8 **)(a + 0xC0) + 6) = -1;
    *(s16 *)(*(u8 **)(a + 0xC0) + 0) = 0;
    *(s16 *)(*(u8 **)(a + 0xC0) + 2) = 0;
    *(s16 *)(*(u8 **)(a + 0xC0) + 4) = 0;
    *(s16 *)(*(u8 **)(a + 0xC0) + 8) = 0;
    *(s16 *)(*(u8 **)(a + 0xC0) + 0xA) = 0;
    *(s16 *)(*(u8 **)(a + 0xC0) + 0xC) = 0;
    *(s16 *)(*(u8 **)(a + 0xC0) + 0x38) = 0x1000;
    *(s16 *)(*(u8 **)(a + 0xC0) + 0x3A) = 0x1000;
    *(s16 *)(*(u8 **)(a + 0xC0) + 0x3C) = 0x1000;
    SetModel_1B74(*(u8 **)(a + 0xC0), bank, index);
    return 0;
}

s32 func_80051C8C(s32 arg0) {
    s32 temp_s1;

    temp_s1 = arg0 + 0x98;
    M2C_FIELD(arg0, s32 *, 0x98) = 0x1000;
    M2C_FIELD(arg0, s32 *, 0x9C) = 0;
    M2C_FIELD(arg0, s32 *, 0xA0) = 0x1000;
    M2C_FIELD(arg0, s32 *, 0xA4) = 0;
    M2C_FIELD(arg0, s32 *, 0xA8) = 0x1000;
    M2C_FIELD(arg0, s32 *, 0xAC) = 0;
    M2C_FIELD(arg0, s32 *, 0xB0) = 0;
    M2C_FIELD(arg0, s32 *, 0xB4) = 0;
    RotMatrixX((s32) M2C_FIELD(arg0, s16 *, 0x54), temp_s1);
    RotMatrixY((s32) M2C_FIELD(arg0, s16 *, 0x56), temp_s1);
    RotMatrixZ((s32) M2C_FIELD(arg0, s16 *, 0x58), temp_s1);
    M2C_FIELD(arg0, s32 *, 0xAC) = (s32) M2C_FIELD(arg0, s16 *, 0x2E);
    M2C_FIELD(arg0, s32 *, 0xB0) = (s32) M2C_FIELD(arg0, s16 *, 0x32);
    M2C_FIELD(arg0, s32 *, 0xB4) = (s32) M2C_FIELD(arg0, s16 *, 0x36);
    return func_80051464(arg0);
}

void func_80051D20(void *arg0, s32 arg1, void *arg2) {
    ApplyMatrixSV(arg0 + 0x98);
    M2C_FIELD(arg2, u16 *, 0) = (u16) (M2C_FIELD(arg2, u16 *, 0) + M2C_FIELD(arg0, u16 *, 0xAC));
    M2C_FIELD(arg2, u16 *, 2) = (u16) (M2C_FIELD(arg2, u16 *, 2) + M2C_FIELD(arg0, u16 *, 0xB0));
    M2C_FIELD(arg2, u16 *, 4) = (u16) (M2C_FIELD(arg2, u16 *, 4) + M2C_FIELD(arg0, u16 *, 0xB4));
}

void f_TransformPointByModelPart(void *arg0, s32 arg1, void *arg2) {
    ApplyMatrixSV(arg0 + 0x18);
    M2C_FIELD(arg2, u16 *, 0) = (u16) (M2C_FIELD(arg2, u16 *, 0) + M2C_FIELD(arg0, u16 *, 0x2C));
    M2C_FIELD(arg2, u16 *, 2) = (u16) (M2C_FIELD(arg2, u16 *, 2) + M2C_FIELD(arg0, u16 *, 0x30));
    M2C_FIELD(arg2, u16 *, 4) = (u16) (M2C_FIELD(arg2, u16 *, 4) + M2C_FIELD(arg0, u16 *, 0x34));
}

void func_80051E00(void)
{
    u8 *tcb = *(u8 **)0x110;
    WorkerState *w = (WorkerState *)0x801FE000;
    s32 i = 0;
    s32 mode = 0x40000404;
    u32 stack = 0x801FEA00;

    for (; i < 3; i++) {
        tcb += 0xC0;
        w->busy = 0;
        w->stack = stack;
        w->active = 0;
        w->unk6F = 0;
        w++;
        stack += 0x800;
        *(s32 *)(tcb + 0x94) = mode;
    }
}

extern s8 D_1F800138[];
void func_80051E60(void) {
    u16 temp_v1;
    void *temp_v0;
    void *temp_v0_2;
    void *temp_v1_2;

    *((void **)D_1F800138) = (void *)0x801FE000;
    do {
        temp_v1 = M2C_FIELD(*((void **)D_1F800138), u16 *, 0);
        if (temp_v1 != 2) {
            if (temp_v1 == 3) {
                EnterCriticalSection();
                temp_v0_2 = *((void **)D_1F800138);
                M2C_FIELD(*((void **)D_1F800138), s32 *, 4) = OpenTh(M2C_FIELD(temp_v0_2, s32 *, 0xC), M2C_FIELD(temp_v0_2, s32 *, 8), M2C_FIELD(temp_v0_2, s32 *, 0x10));
                ExitCriticalSection();
                goto block_4;
            }
        } else {
block_4:
            temp_v1_2 = *((void **)D_1F800138);
            M2C_FIELD(temp_v1_2, u16 *, 0) = 4U;
            ChangeTh(M2C_FIELD(temp_v1_2, s32 *, 4));
        }
        temp_v0 = *((void **)D_1F800138) + 0x70;
        *((void **)D_1F800138) = temp_v0;
    } while ((u32) temp_v0 <= 0x801FE14FU);
}

void f_OpenCooperativeWorkerThread(s32 i, void (*entry)())
{
    WorkerState *w = &WORKER_SLOTS[i];

    w->entry = (u32)entry;
    w->gp = GetGp();
    w->busy = 2;
    w->unk6F = 0;
    EnterCriticalSection();
    w->thread = OpenTh(w->entry, w->stack, w->gp);
    ExitCriticalSection();
}

extern s8 D_1F800138[];
void f_YieldCurrentCooperativeWorker(s16 arg0) {
    void *temp_v1;

    temp_v1 = *((void **)D_1F800138);
    M2C_FIELD(temp_v1, s16 *, 2) = arg0;
    M2C_FIELD(temp_v1, s16 *, 0) = 1;
    ChangeTh(0xFF000000);
}

extern WorkerState *D_1F800138_fd56;
extern s32 D_800E7E80_34c0[];
void f_TerminateCurrentCooperativeWorker(void)
{
    WorkerState *w = D_1F800138_fd56;

    w->active = 0;
    w->busy = 0;
    D_1F800138_fd56->unk6F = 0;
    EnterCriticalSection();
    CloseTh(D_1F800138_fd56->thread);
    ExitCriticalSection();
    ChangeTh(0xFF000000);
}

void f_CloseCooperativeWorkerThread(s32 i)
{
    WorkerState *w = (WorkerState *)((u8 *)0x801FE000 + i * 0x70);

    if (w->busy != 0) {
        w->busy = 0;
        w->active = 0;
        w->unk6F = 0;
        EnterCriticalSection();
        CloseTh(w->thread);
        ExitCriticalSection();
    }
}

extern s8 D_1F800138[];
void func_80052078(s32 arg0) {
    void *temp_v1;

    func_800450BC(*((void **)D_1F800138) + 0xC, arg0);
    temp_v1 = *((void **)D_1F800138);
    M2C_FIELD(temp_v1, s16 *, 0) = 3;
    M2C_FIELD(temp_v1, s8 *, 0x6F) = 0;
    EnterCriticalSection();
    CloseTh(M2C_FIELD(*((void **)D_1F800138), s32 *, 4));
    ExitCriticalSection();
    ChangeTh(0xFF000000);
}

void func_800520E0(void)
{
    u8 *pad;
    u8 *s;

    func_8007B328();
    pad = D_800BF4F8;
    *(u16 *)(pad + 2) = 0xFFFF;
    s = D_800ECF48_7ec2;
    *(s16 *)(s + 2) = 0;
    s[4] = 0;
    s[5] = 0;
    s[6] = 0;
    s[7] = 0;
    PadInitDirect(pad, pad + 0x22);
    PadEnableCom(1);
    PadStartCom();
}

s16 func_80052144(s32 arg0, s32 arg1) {
    s16 var_a1;
    s16 var_a2;
    s16 var_v1;
    u32 temp_a0;

    var_v1 = 0;
    if ((arg1 << 0x10) == 0) {
        var_a1 = 0x80;
        var_a2 = 0x20;
    } else {
        var_a1 = 0x10;
        var_a2 = 0x40;
    }
    temp_a0 = arg0 & 0xFF;
    if (temp_a0 < 0x58U) {
        var_v1 = var_a1;
    } else if (temp_a0 >= 0xA9U) {
        var_v1 = var_a2;
    }
    return var_v1;
}

s32 func_80052198(s32 a, u8 *out)
{
    s32 t = a + 0x80;
    u8 v;
    s32 r;

    *out = t;
    if ((s8)a < 0) {
        v = t;
    } else {
        v = 0x7F - a;
    }
    if (v < 0x29) {
        r = 0;
        *out = 0;
    } else if (v < 0x44) {
        r = 1;
    } else if (v < 0x62) {
        r = 2;
    } else {
        r = 3;
    }
    return r;
}

void f_StartControllerVibration(u8 port, u8 lo, u8 hi, u8 dur)
{
    u8 *v = D_800ECF48_7ec2;

    if (D_1F80019A == 1) {
        return;
    }
    if (D_800FB167 != 0) {
        return;
    }
    if (*(u16 *)(v + 2) == 0) {
        return;
    }
    if (v[6] != 0) {
        return;
    }
    if (*(u16 *)(v + 4) != 0) {
        return;
    }
    v[4] = lo;
    v[5] = hi;
    PadSetAct(port, v + 4, 2);
    v[7] = dur;
    v[6] = 1;
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_8005229C);

extern u8 D_800ECF48_7ec2[];
extern u8 D_800A3FA0[];
typedef struct Slot40c { u8 pad0[7]; u8 index; u8 pad8[4]; s16 scale; u8 padE[0x32]; } Slot40c;
extern Slot40c D_800EC188_d83b[];
extern u16 D_1F800198;
extern u8 D_80017304[];
void func_8005245C(void)
{
    u8 *p = D_800ECF48_7ec2;

    p[4] = 0;
    p[5] = 0;
    PadSetAct(0, p + 4, 2);
    if (PadGetState(0) == 6) {
        PadSetActAlign(0, D_800A3FA0);
    }
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_800524B4);

void func_800527C8();
u8 *func_800525D0(void *owner, s32 slot)
{
    u8 *a = f_AllocateActor(owner, 0x84, 3, 0);

    if (a != NULL) {
        *(void **)(a + 0x1C) = func_800527C8;
        a[3] = slot;
        *(void **)(a + 0x10) = owner;
    }
    return a;
}

void func_8005262C(void *arg0) {
    u16 temp_v0;
    u16 temp_v0_2;

    temp_v0 = M2C_FIELD(arg0, u16 *, 0x44) + 0x200;
    M2C_FIELD(arg0, u16 *, 0x44) = temp_v0;
    if ((s16) temp_v0 >= 0x1801) {
        M2C_FIELD(arg0, u16 *, 0x44) = 0x1800U;
    }
    temp_v0_2 = M2C_FIELD(arg0, u16 *, 0x4A) + 0x200;
    M2C_FIELD(arg0, u16 *, 0x4A) = temp_v0_2;
    if ((s16) temp_v0_2 >= 0x1001) {
        M2C_FIELD(arg0, u16 *, 0x4A) = 0x1000U;
    }
    M2C_FIELD(arg0, s32 *, 0x30) = (s32) (M2C_FIELD(arg0, s32 *, 0x30) - ((s16) M2C_FIELD(arg0, u16 *, 0x4A) << 8));
}

void func_80052694(u8 *a)
{
    *(s16 *)(a + 0x44) -= 0x40;
    if (*(s16 *)(a + 0x44) < 0xA00) {
        *(s16 *)(a + 0x44) = 0xA00;
    }
    *(s16 *)(a + 0x4A) += 0xA0;
    if (*(s16 *)(a + 0x4A) > 0x1000) {
        *(s16 *)(a + 0x4A) = 0x1000;
    }
    *(s32 *)(a + 0x30) += *(s16 *)(a + 0x4A) << 8;
    if (*(s16 *)(a + 0x32) > *(s16 *)(a + 0x66)) {
        *(s16 *)(a + 0x32) = *(s16 *)(a + 0x66);
    }
}

typedef struct { void *p0; void *p4; u8 *p8; } UiBank_F58;
extern UiBank_F58 D_800ECF58_02d8;
void func_80052720(u8 *a)
{
    s16 ang;
    s32 c;

    ang = f_StepWrappedAngleToward((s16)f_CalculateYawFromPositionToPoint(a + 0x2C, *(s16 *)(a + 0x64), *(s16 *)(a + 0x68)),
                                   *(s16 *)(a + 0x56), 0x18);
    *(s16 *)(a + 0x56) = ang;
    c = (rcos(ang) * *(s16 *)(a + 0x44)) >> 4;
    {
        s32 s = (rsin(*(s16 *)(a + 0x56)) * *(s16 *)(a + 0x44)) >> 4;
        *(s32 *)(a + 0x2C) += c;
        *(s32 *)(a + 0x34) -= s;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_800527C8);

extern s16 D_1F800166_e9f9;
extern s16 D_1F800190_19b8;
u8 f_TryPrepareTombaForInteraction(void)
{
    u8 *t = D_800E7E80_f78d;

    if (t[4] != 1) {
        return 0;
    }
    if (t[5] >= 2) {
        if (t[0x164] != 0) {
            goto ok;
        }
        if ((*(u32 *)(t + 4) & 0xFFFF00) != 0x20200) {
            goto fail;
        }
    }
    if (t[0x164] == 0) {
        f_ResetTombaControlState(t);
    }
ok:
    D_1F800166_e9f9 = 0;
    D_1F800190_19b8 = 0;
    D_1F800230_d8aa = 1;
    D_800BF81E_6fe1 = 0;
    return 1;
fail:
    D_1F800230_d8aa = t[4];
    return 0;
}

void func_8005314C(u8 *a)
{
    s32 hi = (*(s16 *)(a + 0x6A) >> 12) & 7;
    s32 id, x, y;

    switch ((*(s16 *)(a + 0x6A) >> 8) & 0xF) {
    case 5: case 6:
        if (hi == 0) {
            id = 0x8A;
            x = 0xB;
            y = -0x32;
            break;
        }
    case 0: case 3: case 4: case 8:
        id = 3;
        x = 0;
        y = 0;
        break;
    case 10:
        id = 0x90;
        x = 0xB;
        y = -0x32;
        break;
    default:
        return;
    }
    f_PlaySoundEffect(id, x, y);
}

void func_800531DC(void *arg0) {
    switch (D_800BF870.unk0) {                      /* irregular */
    case 1:
        if (M2C_FIELD(arg0, s16 *, 0x32) < -0x295A) {
            M2C_FIELD(arg0, s16 *, 0x32) = -0x295A;
            return;
        }
        return;
    case 5:
        if ((u32) (D_800BF870.pad1[0] - 1) < 3U) {
            if (M2C_FIELD(arg0, s16 *, 0x32) < -0x3B1A) {
                M2C_FIELD(arg0, s16 *, 0x32) = -0x3B1A;
                return;
            }
        } else {
            return;
        }
        break;
    case 6:
        if (M2C_FIELD(arg0, u8 *, 0x2A) == 0xE) {
            if (M2C_FIELD(arg0, s16 *, 0x32) < -0x1DD5) {
                M2C_FIELD(arg0, s16 *, 0x32) = -0x1DD5;
            }
        }
        break;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_800532A0);

s32 func_8005344C(void *arg0) {
    if ((D_800BF870.unk0 == 4) && !(M2C_FIELD(&D_800BF870, u16 *, 0x5E6) & 0x10) && ((M2C_FIELD(arg0, u16 *, 0x6A) & 0xF00) == 0x500)) {
        M2C_FIELD(arg0, s8 *, 0x16A) = 0xC;
        M2C_FIELD(arg0, s8 *, 5) = 0x37;
        M2C_FIELD(arg0, s8 *, 6) = 0;
        M2C_FIELD(arg0, s8 *, 7) = 0;
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_800534B0);

s32 func_800535D4(void *arg0) {
    return M2C_FIELD(arg0, u8 *, 0x176) + 1;
}

extern u8 D_800BF8A3;
s32 f_CanTombaStartAttack(u8 *a, s32 b)
{
    if (D_800F2410 == 0) {
        return 0;
    }
    switch (a[0x6C]) {
    case 0: case 1: case 2: case 6: case 7: case 8:
        return 1;
    case 3: case 4:
        return D_1F800231 < 1;
    case 5:
        return D_1F800231 < 2;
    case 9:
        if (b != 0) {
            return 0;
        }
        return D_1F800251 == 0;
    }
    return 0;
}

void func_80053670(u8 *a, s32 b, s32 c)
{
    s32 d;

    if (c != 8) {
        a[0x176] = a[0x6C];
    }
    d = func_800535D4(a);
    switch (a[0x176]) {
    case 0: case 1: case 2: case 6: case 7: case 8:
        if (c != 8) {
            func_800534B0(a, b, c, d);
        }
        if (b == 0) {
            a[0x79] = 1;
            return;
        }
        break;
    case 3: case 4: case 5:
        a[0x79] = 0;
        if (c != 8) {
            func_800534B0(a, b, c, d);
        }
        return;
    case 9:
        a[0x79] = 0;
        if (c != 8) {
            func_800534B0(a, b, c, d + 1);
        }
        return;
    }
    a[0x79] = 0;
}

s32 func_8005376C(u8 *p)
{
    switch (p[0x176]) {
    case 0: case 1: case 2: case 6: case 7: case 8:
        return p[0x79] != 0;
    case 3: case 4: case 5: case 9:
        return 0;
    }
    return 0;
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_800537B8);

void func_800538E0(u8 *a, u16 *pos, s32 flag)
{
    s16 v[6];
    u8 *e;
    s32 m;

    if (flag == 0) {
        m = (*(u16 *)(a + 0x6A) >> 8) & 0xF;
        if (m == 0 || m == 3) {
            v[1] = pos[1];
            v[3] = pos[3] + *(u16 *)(a + 0x84);
            v[5] = pos[5];
            e = f_SpawnTransientEffectAtFixedPosition(0x35, v, -0x5A);
            if (e != 0) {
                e[0x28] |= 0x80;
            }
        }
    }
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_80053968);

s32 func_80053BF8(void *arg0, s32 arg1)
{
  unsigned char temp_v1;
  u8 temp_v0;
  temp_v0 = *((u8 *) (((signed char *) arg0) + 0x61));
  if (temp_v0 != 0)
  {
    if (temp_v0 & 1)
    {
      *((u8 *) (((signed char *) arg0) + 0)) = (u8) ((*((u8 *) (((signed char *) arg0) + 0))) & 7);
      if (arg1 != 0)
      {
        temp_v1 = ((u8) (*((u8 *) (((signed char *) arg0) + 0x61)))) >> 4;
        switch (temp_v1)
        {
          case 2:
            if (((*((s16 *) (((signed char *) arg0) + 0x16C))) & 0xC000) == 0xC000)
          {
            func_80047B5C(arg0, 0);
            if ((*((u16 *) 0x1F8001A8)) & 8)
            {
              func_8004960C(arg0, 0);
              f_ApplyAreaPlaneDirectionToActor(arg0);
              *((u16 *) (((signed char *) arg0) + 0x140)) = (u16) (*((u16 *) 0x1F8001A0));
            }
          }
            break;

          case 3:
            *((s8 *) (((signed char *) arg0) + 0x16B)) = 1;
            break;

          case 4:
            *((s8 *) (((signed char *) arg0) + 0x16B)) = 0;
            break;

        }

        *((u8 *) (((signed char *) arg0) + 0x61)) = 0U;
        *((u8 *) (((signed char *) arg0) + 0)) = (u8) ((*((u8 *) (((signed char *) arg0) + 0))) & 3);
      }
      return 1;
    }
    *((u8 *) (((signed char *) arg0) + 0x61)) = 0U;
    goto block_17;
  }
  block_17:
  return 0;

}

void f_ReleaseTombaInteractionTarget(u8 *t)
{
    u8 *o = *(u8 **)(t + 0x158);

    if (o != 0 && (s32)o != 1) {
        switch (o[0xC]) {
        case 2:
        case 5:
        case 9:
            o[0x5E] = 0;
            break;
        case 4:
            if ((u32)(o[2] - 0x2F) >= 2) {
                o[0x29] = 0;
            }
            break;
        }
    }
    *(u8 **)(t + 0x158) = 0;
    t[0x164] = 0;
}

void f_ClearTombaInteractionState(u8 *a)
{
    u8 *p;

    switch (a[0x78]) {
    case 1: case 4: case 5: case 6: case 7: case 8: case 9:
        p = *(u8 **)(a + 0x10);
        p[0] = 2;
        p[0x2B] = *(u16 *)(a + 0x56) >> 4;
        p[4] = 2;
        p[5] = 2;
        p[6] = 0;
        p[0x28] |= 0x80;
        break;
    case 2:
        p = *(u8 **)(a + 0x10);
        p[4] = 2;
        p[5] = 3;
        p[6] = 0;
        break;
    case 3:
        p = *(u8 **)(a + 0x10);
        p[0] = 2;
        p[4] = 2;
        p[5] = 1;
        p[6] = 0;
        break;
    }
    a[0x144] = 0;
    a[0x78] = 0;
    a[0x181] = 0;
    f_ReleaseTombaInteractionTarget(a);
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_80053E50);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80053FDC);

void f_ResetTombaControlState(void *arg0) {
    s8 temp_v0;

    if ((M2C_FIELD(arg0, u8 *, 0x146) != 4) || (M2C_FIELD(arg0, u8 *, 0) != 2)) {
        M2C_FIELD(arg0, s16 *, 0x44) = 0;
        M2C_FIELD(arg0, s16 *, 0x182) = 0;
        if (M2C_FIELD(arg0, u8 *, 2) != 0) {
            M2C_FIELD(arg0, s8 *, 0x149) = 2;
            return;
        }
        M2C_FIELD(arg0, s16 *, 0x50) = 0;
        M2C_FIELD(arg0, s8 *, 0x148) = 0;
        temp_v0 = M2C_FIELD(arg0, u8 *, 0x147) + 2;
        M2C_FIELD(arg0, s8 *, 0x14A) = temp_v0;
        M2C_FIELD(arg0, s8 *, 0x149) = temp_v0;
    }
}

#define PROBE_800493E8 ((s32 (*)(u8 *, s32, s32))func_800493E8)
s32 f_ResolveTombaOverheadTerrainContact(u8 *a, s32 b)
{
    s16 z;
    s32 x;
    s32 r;
    u8 *p;
    s32 xx;
    s32 zz;
    s16 z1;
    u8 v;

    D_1F800253 &= 4;
    if (a[0x16B] != 0) {
        return 0;
    }
    z = -0x82;
    if (a[0x145] != 0) {
        z = -0x5A;
        if (*(s16 *)(a + 0x4A) < -0x2700) {
            z = -0x78;
        }
    }
    x = 0x38;
    if (*(s16 *)(a + 0x17E) < 0) {
        z = z / 2;
        x = 0x1C;
    }
    if (!(b & 1)) {
        z1 = z;
        r = PROBE_800493E8(a, x, z1);
        if (r == 0) {
            r = PROBE_800493E8(a, -x, z1);
        }
    } else {
        r = PROBE_800493E8(a, 0, z);
    }
    if (r == 0) {
        return 0;
    }
hit:
    if (r == 2) {
        if ((*(u16 *)D_1F8001A6 & 0xF00) == 0x100) {
            D_1F800253 = 1;
        }
        return 0;
    }
    if ((a[0x145] & 1) && *(s16 *)(a + 0x4A) < 0) {
        *(s16 *)(a + 0x4A) = 0;
    }
    if (!(b & 2)) {
        if (*(s16 *)D_1F8001A6 & 0x8000) {
            if (D_800BF873 == 0) {
                if (!(*(u16 *)(a + 0x17E) & 0x200)) {
                    f_TryApplyTombaActorDamage(a, 0, 1, 1);
                }
                D_1F800253 = 2;
            } else {
                D_1F800253 = 3;
            }
        } else {
            D_1F800253 = 3;
        }
    }
    return 1;
}

void func_800543C0(u8 *a)
{
    u8 *o;
    s32 d;

    if (a[0x16B] != 0 || a[0x29] != 0) {
        return;
    }
    if (a[0x78] != 0) {
        o = *(u8 **)(a + 0x10);
        d = (*(s16 *)(o + 0x86) - *(s16 *)(o + 0x84)) - (*(s16 *)(a + 0x32) - *(s16 *)(o + 0x32));
    } else {
        d = *(s16 *)(a + 0x62);
    }
    f_ProbeActorTerrainAlongFacing(a, 0, (s16)d);
}

extern u16 D_1F80019E;
extern u16 D_1F8001A4;
extern u16 D_1F8001A8;
s32 f_ResolveTombaGroundTerrainContact(u8 *a)
{
    s32 alt = 0;
    u16 half;
    s32 z;
    s16 zz;
    s32 x;
    u8 r;
    u16 f;

    *(u16 *)(a + 0x16C) = 0;
    *(u16 *)(a + 0x6A) = 0;
    if (a[0x16B] != 0) {
        goto end;
    }
    if (a[0x29] != 0) {
        goto end;
    }
    if (*(s16 *)(a + 0x17E) >= 0) {
        half = *(u16 *)(a + 0x80);
    } else {
        half = *(s16 *)(a + 0x80) / 2;
    }
    if (a[0x78] != 0) {
        u8 *l = *(u8 **)(a + 0x10);
        z = (*(s16 *)(l + 0x86) - *(s16 *)(l + 0x84)) - (*(s16 *)(a + 0x32) - *(s16 *)(l + 0x32));
    } else {
        z = *(s16 *)(a + 0x62);
    }
    if (a[0x61] != 0) {
        r = a[0x29] = f_ProbeActorTerrainAlongFacing((s32)a, 0, (s16)z);
test:
        if (r != 0) {
            goto found;
        }
        goto end;
    }
    zz = z;
    if ((a[0x29] = f_ProbeActorTerrainAlongFacing((s32)a, 0, zz)) != 0) {
        goto found;
    }
    alt = 1;
    if ((a[0x29] = f_ProbeActorTerrainAlongFacing((s32)a, (s16)half, zz)) != 0) {
        goto found;
    }
    r = a[0x29] = f_ProbeActorTerrainAlongFacing((s32)a, (s16)-half, zz);
    goto test;
found:
    D_1F80019E = D_1F8001A4;
    f = *(u16 *)D_1F8001A6;
    *(u16 *)(a + 0x6A) = f;
    if (alt == 1 && (f & 0x8000) && ((f & 0xF00) == 0x100 || (f & 0xF00) == 0x200)) {
        *(u16 *)(a + 0x6A) = 0;
    }
    a[0x29] &= 1;
    if (a[0x29] != 0) {
        *(u16 *)(a + 0x50) = 0;
        a[0x29] |= 0x80;
        if (alt == 0) {
            *(u16 *)(a + 0x16C) = D_1F8001A8;
        } else {
            *(u16 *)(a + 0x16C) = 0;
        }
        f_ApplyTerrainProfileOrientationToActor(a);
        *(u16 *)(a + 0x142) = D_1F8001A2;
    }
end:
    return a[0x29];
}

INCLUDE_ASM("asm/main/nonmatchings/main", f_UpdateTombaForwardTerrainContact);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80054790);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8005490C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80054B34);

extern u8 D_800A44F0[];
extern u8 D_800A44E0[];
extern u8 D_800A44E8[];
extern u8 D_800A44D0[];
s32 f_SetTombaAnimationIfChanged(u8 *t, s32 anim, s32 blend);
void func_80054C08(u8 *a, s32 mode)
{
    s16 k = (u32)(func_800535D4(a) - 7) < 3;
    u8 *t;

    if (mode != 0) {
        if (k) {
            t = D_800A44F0;
            mode = t[a[0xBE]];
        } else {
            t = D_800A44E0;
            mode = (t + (a[0x14A] & 6))[a[0xBE]];
        }
        f_SetTombaAnimationIfChanged(a, mode, 0);
        return;
    }
    if (k) {
        t = D_800A44E8;
        mode = t[a[0xBE]];
    } else {
        t = D_800A44D0;
        mode = t[a[0x14A] & 6];
    }
    if (a[0x46] == mode) {
        return;
    }
    a[0x46] = mode;
    func_80054790(a, mode);
    *(u8 **)(a + 0x38) = ((u8 **)D_80017FE8)[mode] + *(s16 *)(*(u8 **)(a + 0x38) + 2) * 8;
    func_80076904(a);
}

extern void *D_800ECF58_449d;
s32 f_SetTombaAnimationIfChanged(u8 *t, s32 anim, s32 blend)
{
    if (t[0x46] == (u8)anim) {
        return 0;
    }
    t[0x46] = anim;
    func_80054790(t, anim);
    if ((s16)blend == 0) {
        f_StartActorSkeletalAnimation(t, D_80017FE8, anim);
    } else {
        f_StartActorSkeletalAnimationBlend(t, D_80017FE8, anim, (s16)blend);
    }
    return 1;
}

void f_SetTombaAnimation(u8 *t, s32 anim, s16 blend)
{
    t[0x46] = anim;
    func_80054790(t);
    if (blend == 0) {
        f_StartActorSkeletalAnimation(t, D_80017FE8, anim);
    } else {
        f_StartActorSkeletalAnimationBlend(t, D_80017FE8, anim, blend);
    }
}

void f_SelectTombaContactAnimation6AOr6C(u8 *a, s32 mode, s32 base)
{
    s32 anim;

    switch (mode) {
    case 1:
        anim = base + 0x6A;
        break;
    case 0:
        if (a[0x147] == (a[0x16A] & 1)) {
            anim = base + 0x6A;
            break;
        }
    default:
        anim = base + 0x6C;
        break;
    case 2:
        anim = base + 0x6C;
        break;
    }
    f_SetTombaAnimationIfChanged(a, anim, 0);
}

INCLUDE_ASM("asm/main/nonmatchings/main", f_UpdateTombaGroundMovementAnimation);

void f_UpdateTombaModelOrientationFromFacing(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x29) != 0) {
        if (M2C_FIELD(arg0, u8 *, 0x147) != 0) {
            M2C_FIELD(arg0, u16 *, 0x56) = (u16) ((M2C_FIELD(arg0, u16 *, 0x140) - 0x800) & 0xFFF);
            if (M2C_FIELD(arg0, u8 *, 0x145) == 0) {
                M2C_FIELD(arg0, s16 *, 0x58) = (s16) ((0x1000 - ((s32) (M2C_FIELD(arg0, u16 *, 0x142) << 0x10) >> 0x11)) & 0xFFF);
            }
        } else {
            M2C_FIELD(arg0, u16 *, 0x56) = (u16) M2C_FIELD(arg0, u16 *, 0x140);
            if (M2C_FIELD(arg0, u8 *, 0x145) == 0) {
                M2C_FIELD(arg0, s16 *, 0x58) = (s16) ((s32) (M2C_FIELD(arg0, u16 *, 0x142) << 0x10) >> 0x11);
            }
        }
    } else {
        if (M2C_FIELD(arg0, u8 *, 0x147) != 0) {
            M2C_FIELD(arg0, u16 *, 0x56) = (u16) ((M2C_FIELD(arg0, u16 *, 0x140) - 0x800) & 0xFFF);
            return;
        }
        M2C_FIELD(arg0, u16 *, 0x56) = (u16) M2C_FIELD(arg0, u16 *, 0x140);
    }
}

void f_ApplyTombaFacingYaw(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x147) != 0) {
        M2C_FIELD(arg0, u16 *, 0x56) = (u16) ((M2C_FIELD(arg0, u16 *, 0x140) - 0x800) & 0xFFF);
        return;
    }
    M2C_FIELD(arg0, u16 *, 0x56) = (u16) M2C_FIELD(arg0, u16 *, 0x140);
}

void func_800552B8(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x147) != 0) {
        M2C_FIELD(arg0, u16 *, 0x58) = (u16) ((0x1000 - M2C_FIELD(arg0, u16 *, 0x142)) & 0xFFF);
        return;
    }
    M2C_FIELD(arg0, u16 *, 0x58) = (u16) M2C_FIELD(arg0, u16 *, 0x142);
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_800552EC);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80055390);

INCLUDE_ASM("asm/main/nonmatchings/main", f_TryStartTombaContactAction);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80055704);

s32 func_800557EC(u8 *p)
{
    if (p[0x148] == 0) {
        if (D_800E7E68 & D_1F800172_5cdb) {
            return 1;
        }
    }
    return 0;
}

extern s8 D_1F800172[];
extern u16 D_800E7E68;
s32 func_80055824(void) {
    return (D_800E7E68 & *((u16 *)D_1F800172)) != 0;
}

extern s8 D_1F800172[];
extern u16 D_800ECF54;
s32 func_80055844(void) {
    return (D_800ECF54 & *((u16 *)D_1F800172)) != 0;
}

extern s8 D_1F800172[];
extern s8 D_1F800174[];
extern s8 D_1F800230[];
extern u16 D_800E7E68;
s32 func_80055864(void) {
    s32 var_v0;

    if (*((u8 *)D_1F800230) != 0) {
        return 0;
    }
    var_v0 = ((D_800E7E68 & *((u16 *)D_1F800172)) != 0) * 2;
    if (D_800E7E68 & *((u16 *)D_1F800174)) {
        var_v0 |= 1;
    }
    return var_v0;
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_800558B4);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800559F4);

s32 func_80055C30(u8 *p)
{
    if (*(s16 *)(p + 0x16E) == 0) {
        return 0;
    }
    if (D_1F800137_104c != 0) {
        return 0;
    }
    if ((p[0x29] & 0x80) && (*(u16 *)(p + 0x6A) & 0x10)) {
        p[5] = 0xB;
        p[6] = 0;
        p[7] = 0;
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_80055C9C);

extern s8 D_1F800137[];
extern s8 D_1F80018C[];
extern s8 D_1F8001A0[];
extern s8 D_1F800207[];
extern s8 D_1F800210[];
void f_UpdateTombaMovementOrientation(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 0x16B);
    if (temp_v1 != 0) {
        if (temp_v1 == 8) {
            M2C_FIELD(arg0, u16 *, 0x140) = (u16) *((u16 *)D_1F800210);
        } else {
            M2C_FIELD(arg0, u16 *, 0x140) = (u16) *((u16 *)D_1F80018C);
        }
        M2C_FIELD(arg0, s16 *, 0x48) = (s16) (rcos((s16) M2C_FIELD(arg0, u16 *, 0x140)) >> 4);
        M2C_FIELD(arg0, s16 *, 0x4C) = (s16) -(rsin((s16) M2C_FIELD(arg0, u16 *, 0x140)) >> 4);
        if (M2C_FIELD(arg0, u8 *, 0x29) != 0) {
            M2C_FIELD(arg0, s16 *, 0x4A) = 0;
        }
    } else {
        f_ResolveActorAreaPlanePosition(arg0);
        f_ApplyAreaPlaneDirectionToActor(arg0);
        M2C_FIELD(arg0, u16 *, 0x140) = (u16) *((u16 *)D_1F8001A0);
        if (*((u8 *)D_1F800137) != 1) {
            *((u8 *)D_1F800207) = M2C_FIELD(arg0, u8 *, 0x2A);
        }
    }
}

extern s8 D_1F80016C[];
extern s8 D_1F80016E[];
extern M2C_UNK D_800ECF48;
extern u16 D_800ECF54;
u8 f_ReadTombaDirectionalInput(void *arg0, s32 arg1) {
    u8 temp_v1;
    u8 temp_v1_2;
    u8 var_v0;

    temp_v1 = M2C_FIELD(arg0, u8 *, 0x14A) & 1;
    M2C_FIELD(arg0, u8 *, 0x14A) = temp_v1;
    if (D_800ECF54 & 0xA0) {
        if (D_800ECF54 & *((s16 *)D_1F80016C)) {
            M2C_FIELD(arg0, u8 *, 0x14A) = 0U;
        } else if (D_800ECF54 & *((s16 *)D_1F80016E)) {
            M2C_FIELD(arg0, u8 *, 0x14A) = 1U;
        }
        if (M2C_FIELD(&D_800ECF48, u16 *, 0) == 7) {
            M2C_FIELD(arg0, u8 *, 0x14B) = (u8) M2C_FIELD(&D_800ECF48, u8 *, 8);
        } else {
            M2C_FIELD(arg0, u8 *, 0x14B) = 3U;
        }
    } else {
        M2C_FIELD(arg0, u8 *, 0x14A) = (u8) (temp_v1 | 2);
        M2C_FIELD(arg0, u8 *, 0x14B) = 0U;
    }
    if (D_800ECF54 & 0x10) {
        var_v0 = M2C_FIELD(arg0, u8 *, 0x14A) | 4;
        goto block_13;
    }
    if (D_800ECF54 & 0x40) {
        var_v0 = M2C_FIELD(arg0, u8 *, 0x14A) | 8;
block_13:
        M2C_FIELD(arg0, u8 *, 0x14A) = var_v0;
    }
    if (arg1 != 0) {
        temp_v1_2 = M2C_FIELD(arg0, u8 *, 0x14A);
        if (!(temp_v1_2 & 2)) {
            M2C_FIELD(arg0, s8 *, 0x147) = (s8) (temp_v1_2 & 1);
            f_ApplyTombaFacingYaw(arg0);
        }
    }
    return M2C_FIELD(arg0, u8 *, 0x14A);
}

void f_SetTombaJumpLaunchVelocity(u8 *t, s32 boost)
{
    if (t[0x174] & 0x30) {
        *(u16 *)(t + 0x4A) = D_800A4582;
    } else {
        *(u16 *)(t + 0x4A) = D_800A457C[t[0x6D]];
    }
    if (boost != 0 && (*(u16 *)(t + 0x17E) & 0x180)) {
        *(u16 *)(t + 0x4A) += 0x1940;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/main", f_UpdateTombaHorizontalMovementSpeed);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80056878);

typedef struct { u8 pad[0x40]; void *p40; void *p44; } UiBankB_F58;
extern UiBankB_F58 D_800ECF58_674d;
extern u8 *D_1F800214_120a;
extern u8 D_800A4BC8[];
extern u8 D_8001B860[];
extern u16 D_800A3CD0[];
void f_AdvanceTombaAlongMovementVector(u8 *t, s32 noY)
{
    *(s32 *)(t + 0x2C) += *(s16 *)(t + 0x48) * *(s16 *)(t + 0x44);
    *(s32 *)(t + 0x34) += *(s16 *)(t + 0x4C) * *(s16 *)(t + 0x44);
    if (noY == 0) {
        *(s32 *)(t + 0x30) += *(s16 *)(t + 0x4A) * *(s16 *)(t + 0x44);
    }
    if (t[0x16B] == 0 && t[0x61] == 0) {
        f_UpdateTombaForwardTerrainContact(t, 0);
    } else {
        t[0x5F] &= 0xFB;
    }
}

void f_DetachTombaFromSupport(u8 *a, s32 keep);
void f_UpdateTombaLostGroundSupportMotion(u8 *a, s32 b)
{
    u8 *g;

    if ((a[0x29] | a[0x145]) != 0) {
        if (*(s16 *)(a + 0x50) > 0x1400) {
            func_8005314C(a);
        }
        *(s16 *)(a + 0x50) = 0;
        a[0x148] = 0;
        return;
    }
    g = D_800BF808;
    if (((s8 *)g)[5] == 0 && g[0x40] != 0) {
        f_DetachTombaFromSupport(a, 0);
        return;
    }
    *(s16 *)(a + 0x50) += 0x800;
    if (*(s16 *)(a + 0x50) > 0x3E00) {
        *(s16 *)(a + 0x50) = 0x3E00;
    }
    if (*(s16 *)(a + 0x50) >= 0x1E00) {
        a[0x148] = 1;
        if (b == 0 && a[0x146] != 4) {
            f_DetachTombaFromSupport(a, 0);
            if (*(u16 *)(a + 0x17E) & 0x40) {
                *(s16 *)(a + 0x4A) = *(s16 *)(a + 0x50) / 4;
            } else {
                *(s16 *)(a + 0x4A) = *(s16 *)(a + 0x50);
            }
            *(s16 *)(a + 0x50) = 0;
        }
    }
    *(s32 *)(a + 0x30) += *(s16 *)(a + 0x50) << 8;
}

extern s16 D_800A45A0[];
extern s16 D_800A4588[];
extern u16 D_1F800238;
void f_DetachTombaFromSupport(u8 *a, s32 keep)
{
    a[0x181] = 0;
    *(s16 *)(a + 0x182) = 0;
    a[0x16A] = 0;
    f_ClearTombaInteractionState(a);
    a[0x178] = 0;
    if (a[0x146] & 3) {
        *(s16 *)(a + 0x58) = 0;
        a[0x145] = 1;
        a[0x29] = 0;
        a[0x148] = 0;
        *(s16 *)(a + 0x4A) = 0;
        a[5] = 6;
        a[7] = 1;
    } else {
        if (keep == 0) {
            *(s16 *)(a + 0x58) = 0;
            f_SetTombaAnimationIfChanged(a, 0x14, 0);
        }
        a[0x167] = 0x10;
        a[0x146] = 0;
        a[0x145] = 1;
        a[0x29] = 0;
        a[0x144] = 0;
        a[0x148] = 0;
        *(s16 *)(a + 0x4A) = 0;
        a[5] = 2;
        a[6] = 1;
        a[7] = 1;
    }
}

extern u16 D_800A4588_8cc4[];
extern u16 D_800A45A0_e73f[];
void func_80056E08(u8 *a)
{
    u16 *t;

    if (D_800ECF54 & *(u16 *)D_1F800172) {
        if (++a[0x167] >= 0xFF) {
            a[0x167] = 0xFE;
        }
    } else if (a[0x167] < 0xB) {
        if (*(u16 *)(a + 0x17E) & 0x180) {
            *(u16 *)(a + 0x4A) += D_800A45A0_e73f[a[0x167]];
        } else {
            *(u16 *)(a + 0x4A) += D_800A4588_8cc4[a[0x167]];
        }
        a[0x167] = 0x10;
        if (*(s16 *)(a + 0x4A) > 0) {
            *(s16 *)(a + 0x4A) = 0;
        }
    }
}

void func_80056EC8(u8 *p)
{
    u8 *a = *(u8 **)(p + 0x104);
    u8 *e;

    *(s16 *)(a + 0xA) = 0x280;
    *(s16 *)(a + 0x38) = 0x200;
    *(s16 *)(a + 0x3A) = 0x200;
    *(s16 *)(a + 0x3C) = 0x200;
    a = *(u8 **)(p + 0x108);
    *(s16 *)(a + 0xA) = 0xD80;
    *(s16 *)(a + 0x38) = 0x200;
    *(s16 *)(a + 0x3A) = 0x200;
    *(s16 *)(a + 0x3C) = 0x200;
    e = f_SpawnTransientEffect(0x22, 0);
    if (e != 0) {
        e[0x28] |= 0x80;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_80056F3C);

s32 f_StepWrappedAngleToward(s32 a, s32 b, s32 step);
void func_8005706C(u8 *a, s32 b)
{
    *(u16 *)(a + 0x4A) += 0x360;
    if (*(s16 *)(a + 0x4A) >= 0) {
        if (*(u16 *)(a + 0x17E) & 0x40) {
            if ((u8)(a[0x46] - 0x14) < 2 || a[0x46] == 0x62 || a[0x46] == 0x12) {
                f_SetTombaAnimationIfChanged(a, 0xCA, 6);
                a[0x178] = 0;
            }
        } else {
            a[0x178] = 0;
            func_80056EC8(a);
        }
        a[0x145] = 2;
        a[7]++;
        if (!(b & 2)) {
            a[0x144] = 1;
        }
    } else {
        *(s32 *)(a + 0x30) += *(s16 *)(a + 0x4A) << 8;
    }
}

s32 func_80057150(u8 *a, s32 b)
{
    s32 st = 0;

    if (*(u16 *)(a + 0x17E) & 0x40) {
        if (a[0x46] == 0xCB) {
            if (*(u16 *)(*(u8 **)(a + 0x38) + 6) & 0x8000) {
                f_SetTombaAnimationIfChanged(a, 0xCA, 4);
                st = 2;
            } else {
                st = 1;
            }
        } else if (a[0x46] == 0xCA) {
            if (D_800E7E68 & *(u16 *)D_1F800172) {
                f_SetTombaAnimationIfChanged(a, 0xCB, 4);
                f_PlaySoundEffect(0x35, 0, 0);
                st = 1;
            } else {
                st = 2;
            }
        }
    } else {
        st = 2;
    }
    if (st == 1) {
        return 0x300;
    }
    if (st == 2) {
        if (a[0x146] != 0 || a[0x78] != 0) {
            b = 8;
        }
        if (!(a[0x14A] & 2) && (a[0x14A] & 1) == a[0x147]) {
            if (b != 8) {
                *(s16 *)(a + 0x58) = f_StepWrappedAngleToward(0x60, *(s16 *)(a + 0x58), 0x10);
            }
        } else if (a[0x14A] & 8) {
            if (b != 8) {
                *(s16 *)(a + 0x58) = f_StepWrappedAngleToward(0xF00, *(s16 *)(a + 0x58), 0x20);
            }
            return 0x1A00;
        } else {
            if (b != 8) {
                *(s16 *)(a + 0x58) = f_StepWrappedAngleToward(0, *(s16 *)(a + 0x58), 0x40);
            }
        }
    }
    return 0xE00;
}

s32 func_800572EC(u8 *a, s32 b)
{
    s16 lim;
    u8 r;

    f_ResolveTombaOverheadTerrainContact(a, 0);
    if (a[0x29] != 0) {
        return 0;
    }
    lim = func_80057150(a, b);
    if (*(u16 *)(a + 0x17E) & 0x40) {
        if ((u8)(a[0x46] - 0x14) < 2 || a[0x46] == 0x62 || a[0x46] == 0x12) {
            f_SetTombaAnimationIfChanged(a, 0xCA, 6);
            a[0x178] = 0;
        }
    } else if (a[0x14A] & 8) {
        a[0x178]++;
    }
    if (++a[0x178] < 10) {
        lim = 0;
    } else if (a[0x178] >= 0xFF) {
        a[0x178] = 0xFF;
    }
    *(u16 *)(a + 0x4A) += 0x360;
    if (*(s16 *)(a + 0x4A) > lim) {
        *(s16 *)(a + 0x4A) = lim;
    }
    *(s32 *)(a + 0x30) += *(s16 *)(a + 0x4A) << 8;
    if (b == 2) {
        if ((r = a[0x29] = f_ClassifyActorTerrainAlongFacing(a, 0, (s16)(*(s16 *)(a + 0x62) * 2))) != 0) {
            return r;
        }
    } else if (*(s16 *)(a + 0x4A) >= 0 && !(b & 2) && a[0x144] == 0) {
        a[0x144] = 1;
    }
    f_ResolveTombaGroundTerrainContact(a);
    return 0;
}

void func_8005749C(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x146) != 0) {
        M2C_FIELD(arg0, s16 *, 0x58) = 0;
    }
    M2C_FIELD(arg0, s8 *, 0x178) = 0;
    M2C_FIELD(arg0, s8 *, 0x167) = 0;
    M2C_FIELD(arg0, s8 *, 0x145) = 1;
    M2C_FIELD(arg0, s8 *, 0x29) = 0;
    M2C_FIELD(arg0, s16 *, 0x6A) = 0;
    M2C_FIELD(arg0, s8 *, 0x144) = 0;
    M2C_FIELD(arg0, s8 *, 0x148) = 0;
    M2C_FIELD(arg0, u8 *, 7) = (u8) (M2C_FIELD(arg0, u8 *, 7) + 1);
}

extern u8 D_800BF848;
void f_UpdateTombaAirborneMotion(u8 *a, s32 b)
{
    s32 pos[3];
    s32 fl;
    s32 g;

    fl = *(s16 *)(a + 0x17E);
    switch (a[7]) {
    case 0:
        func_8005749C(a);
        if (!(b & 1)) {
            f_SetTombaJumpLaunchVelocity(a, 1);
            if (a[0x165] != 0) {
                *(u16 *)(a + 0x4A) -= 0x580;
            }
            if (a[0x78] == 6) {
                *(u16 *)(a + 0x4A) -= 0x1000;
            }
        }
    case 1:
        f_ResolveTombaOverheadTerrainContact(a, 0);
        func_800543C0(a);
        if (!(b & 0x10) && D_800BF848 == 0 && a[0x61] == 0 && (fl & 0x60)) {
            func_8005706C(a, b);
        } else {
            g = 0x360;
            if (!(b & 1) && (fl & 0x180)) {
                g = 0x120;
            }
            *(u16 *)(a + 0x4A) += g;
            if (*(s16 *)(a + 0x4A) >= 0) {
                a[0x145] = 2;
                a[7]++;
                if (!(b & 2)) {
                    a[0x144] = 1;
                }
            }
            *(s32 *)(a + 0x30) += *(s16 *)(a + 0x4A) << 8;
        }
        if (!(b & 1)) {
            func_80056E08(a);
        }
        if (D_800BF848 & 3) {
            if (a[0x144] == 1) {
                a[0x144] = 0;
            }
            if (b < 2 && (D_800E7E68 & *(u16 *)D_1F800172)) {
                a[7] = 0;
                a[0x145] = 1;
                f_SetTombaAnimationIfChanged(a, 0x14, 4);
                f_PlaySoundEffect(0x1D, 0, 0);
                return;
            }
            a[7] = 2;
            a[0x145] = 2;
        }
        break;
    case 2:
    case 3:
        if (fl & 0x20) {
            func_80056F3C(a);
        }
        if (!(b & 0x10) && D_800BF848 == 0 && a[0x61] == 0 && ((fl & 0x40) || a[0x179] == 1)) {
            if (func_800572EC(a, b) != 0) {
                return;
            }
            goto check;
        }
        f_ResolveTombaOverheadTerrainContact(a, 0);
        if (a[0x29] != 0) {
            goto land;
        }
        if (fl & 0x60) {
            if (b != 8) {
                *(s16 *)(a + 0x58) = f_StepWrappedAngleToward(0, *(s16 *)(a + 0x58), 0x40);
            }
            if (fl & 0x20) {
                if (a[0x14A] & 8) {
                    a[0x178]++;
                }
                if (++a[0x178] >= 0xFF) {
                    a[0x178] = 0xFF;
                }
            }
        }
        g = 0x360;
        if (!(b & 1) && a[0x46] == 0xE5) {
            g = 0x500;
        }
        *(u16 *)(a + 0x4A) += g;
        if (*(s16 *)(a + 0x4A) > 0x3E00) {
            *(s16 *)(a + 0x4A) = 0x3E00;
        }
        *(s32 *)(a + 0x30) += *(s16 *)(a + 0x4A) << 8;
        if (b == 2) {
            if (D_800BF848 != 0 && (D_800E7E68 & *(u16 *)D_1F800172)) {
                a[7] = 0;
                a[0x145] = 1;
                f_PlaySoundEffect(0x1D, 0, 0);
                return;
            }
            if ((a[0x29] = f_ClassifyActorTerrainAlongFacing((s32)a, 0, (s16)(*(s16 *)(a + 0x62) * 2))) != 0) {
                return;
            }
        } else if (D_800BF848 != 0) {
            if (a[0x144] == 1) {
                a[0x144] = 0;
            }
            if (b < 2 && (D_800E7E68 & *(u16 *)D_1F800172)) {
                a[7] = 0;
                a[0x145] = 1;
                f_SetTombaAnimationIfChanged(a, 0x14, 4);
                f_PlaySoundEffect(0x1D, 0, 0);
                return;
            }
        } else if (*(s16 *)(a + 0x4A) >= 0 && !(b & 2) && a[0x144] == 0) {
            a[0x144] = 1;
        }
        f_ResolveTombaGroundTerrainContact(a);
check:
        if (a[0x29] == 0) {
            break;
        }
land:
        a[0x148] = 0;
        *(s16 *)(a + 0x50) = 0;
        if (a[0x144] < 2) {
            a[0x144] = 0;
        }
        a[0x145] = 0;
        pos[0] = *(s32 *)(a + 0x2C);
        pos[1] = *(s32 *)(a + 0x30);
        pos[2] = *(s32 *)(a + 0x34);
        if (a[0x147] != 0) {
            pos[0] += *(s16 *)(a + 0x48) * 0x2800;
            pos[2] += *(s16 *)(a + 0x4C) * 0x2800;
        } else {
            pos[0] -= *(s16 *)(a + 0x48) * 0x2800;
            pos[2] -= *(s16 *)(a + 0x4C) * 0x2800;
        }
        func_800538E0(a, (u16 *)pos, 0);
        func_8005314C(a);
        break;
    }
}

s32 f_TryStartTombaSupportInteraction(u8 *a)
{
    if ((*(s32 *)(a + 0x158) = f_FindTombaSupportInteractionTarget(a, 0)) != 0) {
        a[0x16A] = 0;
        a[0x181] = 0;
        *(s32 *)(a + 0x10) = *(s32 *)D_1F800084;
        *(s16 *)(a + 0x6A) = 0;
        *(s16 *)(a + 0x58) = 0;
        a[0x145] = 0;
        a[0x144] = 0;
        a[6] = 0;
        a[7] = 0;
        a[0x14A] = a[0x147] | 2;
        switch (a[0x164]) {
        case 0x81:
            a[5] = 0x18;
            a[0] = 6;
            *(s16 *)(a + 0x44) = 0;
            a[6] = 0xC;
            a[0x164] &= 1;
            f_PlaySoundEffect(5, 0, 0);
            break;
        case 1:
        case 9:
        case 0xB:
            *(s16 *)(a + 0x44) = 0;
            a[5] = 4;
            f_PlaySoundEffect(5, 0, 0);
            break;
        case 2:
        case 7:
        case 8:
            *(s16 *)(a + 0x44) = 0;
            a[5] = 7;
            f_PlaySoundEffect(5, 0, 0);
            break;
        case 3:
            a[5] = 8;
            f_PlaySoundEffect(5, 0, 0);
            break;
        case 6:
            a[5] = 0x16;
            f_PlaySoundEffect(4, 0, 0);
            break;
        case 4:
            a[5] = 0x14;
            f_PlaySoundEffect(4, 0, 0);
            break;
        case 5:
        case 0xA:
            a[5] = 0x15;
            f_PlaySoundEffect(4, 0, 0);
            break;
        }
        return 1;
    }
    return 0;
}

void func_80057C08(void *arg0, s32 arg1) {
    u8 temp_v0;
    u8 temp_v0_2;

    if ((((s32 (*)())f_TryStartTombaSupportInteraction)() == 0) && (arg1 != 2)) {
        if ((M2C_FIELD(arg0, u8 *, 0x29) == 0) && (M2C_FIELD(arg0, u16 *, 0x17E) & 0x180)) {
            if (arg1 == 0) {
                if (M2C_FIELD(arg0, u8 *, 0x16A) == 0) {
                    if (func_80055824() != 0) {
                        M2C_FIELD(arg0, s16 *, 0x58) = 0;
                        M2C_FIELD(arg0, s8 *, 5) = 0x1C;
                        if (M2C_FIELD(arg0, u8 *, 0x145) == 2) {
                            M2C_FIELD(arg0, s8 *, 6) = 1;
                            f_SetTombaAnimationIfChanged(arg0, 0xE5, 4);
                            return;
                        }
                        M2C_FIELD(arg0, s8 *, 6) = 0;
                        return;
                    }
                    goto block_11;
                }
                goto block_10;
            }
            goto block_16;
        }
block_10:
        if (arg1 == 0) {
block_11:
            if ((M2C_FIELD(arg0, u8 *, 0x16A) == 0) && (f_TryStartTombaContactAction(arg0, 0) != 0)) {
                M2C_FIELD(arg0, s8 *, 6) = 0;
                temp_v0 = M2C_FIELD(arg0, u8 *, 0x14A) & 0xE;
                M2C_FIELD(arg0, u8 *, 0x14A) = temp_v0;
                M2C_FIELD(arg0, u8 *, 0x14A) = (u8) (temp_v0 | M2C_FIELD(arg0, u8 *, 0x147));
                if (M2C_FIELD(arg0, u8 *, 0x29) != 0) {
                    M2C_FIELD(arg0, s8 *, 5) = 5;
                    M2C_FIELD(arg0, s8 *, 7) = 0;
                    return;
                }
                M2C_FIELD(arg0, s8 *, 5) = 6;
                return;
            }
            goto block_16;
        }
block_16:
        if ((M2C_FIELD(arg0, u8 *, 0x29) != 0) && (func_800532A0(arg0) == 0)) {
            M2C_FIELD(arg0, s8 *, 7) = 0;
            temp_v0_2 = M2C_FIELD(arg0, u8 *, 0x14A) & 0xE;
            M2C_FIELD(arg0, u8 *, 0x14A) = temp_v0_2;
            M2C_FIELD(arg0, u8 *, 0x14A) = (u8) (temp_v0_2 | M2C_FIELD(arg0, u8 *, 0x147));
            if (M2C_FIELD(arg0, u8 *, 0x149) & 2) {
                M2C_FIELD(arg0, s8 *, 5) = 2;
                M2C_FIELD(arg0, s8 *, 6) = 2;
                f_SetTombaAnimationIfChanged(arg0, 0x17, 1);
                return;
            }
            M2C_FIELD(arg0, s8 *, 5) = 1;
            M2C_FIELD(arg0, s8 *, 6) = 0;
            f_UpdateTombaGroundMovementAnimation(arg0, 1);
        }
    }
}

INCLUDE_ASM("asm/main/nonmatchings/main", f_SetTombaMiniatureForm);

INCLUDE_ASM("asm/main/nonmatchings/main", f_RebuildTombaAppearanceModelParts);

typedef struct { u8 unk0; u8 pad1[0x1E]; u8 u1F; u8 pad20[0xE]; s16 s2E; } GsStat_82F8;
extern GsStat_82F8 D_800BF870_82f8;
void f_ApplyTombaStatusCommand(u8 *a, s32 cmd)
{
    u8 v;
    u16 t;

    switch (cmd) {
    case 0:
        if (!(a[0x174] & 8)) {
            f_QueueResourceMessage(0x3A, 0x41);
            a[0x174] |= 8;
            a[0xD] |= 0x42;
        }
        break;
    case 1:
        if (a[0x174] & 8) {
            f_SpawnTransientEffect(0x25, 0);
            a[0x174] &= 0xF7;
            a[0xD] &= 0xBD;
            f_QueueResourceMessage(0x3B, 0x41);
        }
        break;
    case 2:
        if (a[0x174] & 8) {
            f_QueueResourceMessage(0x3B, 0x41);
            a[0x174] &= 0xF7;
            a[0xD] &= 0xBD;
        }
        break;
    case 3:
        a[0x174] |= 0x20;
        a[0xD] |= 0x12;
        f_QueueResourceMessage(0x4B, 0x41);
        D_1F800247 = 0;
        break;
    case 4:
        a[0x174] |= 0x10;
        a[0xD] |= 0x12;
        f_QueueResourceMessage(0x4B, 0x41);
        D_1F800247 = 0;
        break;
    case 5:
        a[0x174] &= 0xCF;
        a[0xD] &= 0xED;
        f_QueueResourceMessage(0x4C, 0x41);
        break;
    case 6:
        a[0x174] |= 4;
        f_SetTombaMiniatureForm(a, 1);
        D_800BF89E = *(u16 *)(a + 0x17E);
        f_QueueResourceMessage(0x49, 0x41);
        break;
    case 7:
        a[0x174] &= 0xFB;
        f_SetTombaMiniatureForm(a, 0);
        D_800BF89E = *(u16 *)(a + 0x17E);
        f_QueueResourceMessage(0x4A, 0x41);
        break;
    case 8:
    case 13:
        v = a[0x174];
        if (!(v & 1)) {
            a[0x174] = (v & 0xFD) | 1;
            f_QueueResourceMessage(0x45, 0x41);
            if (cmd == 13) {
                f_PlaySoundEffect(0x39, 0, 0);
            } else {
                a[5] = 0x38;
                a[6] = 2;
            }
        }
        break;
    case 9:
    case 14:
        v = a[0x174];
        if (!(v & 2)) {
            a[0x174] = (v & 0xFE) | 2;
            f_QueueResourceMessage(0x47, 0x41);
            if (cmd == 14) {
                f_PlaySoundEffect(0x3A, 0, 0);
            } else {
                a[5] = 0x39;
                a[6] = 2;
            }
        }
        break;
    case 10:
        a[0x174] &= 0xFC;
        if (D_800BF881 & 1) {
            f_QueueResourceMessage(0x46, 0x41);
        } else if (D_800BF881 & 2) {
            f_QueueResourceMessage(0x48, 0x41);
        }
        break;
    case 11:
        if (a[0x174] & 0x20) {
            f_QueueResourceMessage(0x4C, 0x41);
        }
        t = a[0x174];
        a[0x174] = t & 0xDF;
        if (!(t & 0x10)) {
            a[0xD] &= 0xED;
        }
        break;
    case 12:
        a[0x174] = 0;
        a[0xD] = 0;
        if (*(s16 *)(a + 0x17E) & 0x8000) {
            t = *(u16 *)(a + 0x17E) & 0x7FFF;
            *(u16 *)(a + 0x17E) = t;
            D_800BF89E = t;
        }
        if (*(u16 *)(a + 0x17E) & 0x200) {
            a[0x6F] = 0;
            D_800BF870_82f8.u1F = 0;
            *(u16 *)(a + 0x17E) = 0x10;
            D_800BF870_82f8.s2E = 0x10;
        }
        break;
    }
    D_800BF881 = a[0x174];
}

INCLUDE_ASM("asm/main/nonmatchings/main", f_InitializeTombaPlayerActor);

extern s8 D_1F800137[];
extern s8 D_1F800166[];
extern s8 D_1F800190[];
extern s8 D_800BF80E;
void func_800588BC(void *arg0) {
    if ((*((u8 *)D_1F800137) != 0) && (M2C_FIELD(arg0, u8 *, 0x164) != 0)) {
        M2C_FIELD(arg0, s8 *, 0) = 3;
        D_800BF80E = 1;
        M2C_FIELD(arg0, s8 *, 4) = 4;
        M2C_FIELD(arg0, s8 *, 0x169) = 8;
        *((s16 *)D_1F800166) = 0;
        *((s16 *)D_1F800190) = 0;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_80058918);

extern s8 D_800BF80E;
void func_80058F24(void *arg0) {
    if (*(u8 *)0x1F800137 == 0) {
        D_800BF80E = 0;
        M2C_FIELD(arg0, s8 *, 0) = 3;
        M2C_FIELD(arg0, s16 *, 0x172) = 0x3C;
        M2C_FIELD(arg0, s8 *, 4) = 1;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_80058F5C);

extern u8 D_1F800232;
extern u16 D_1F800166_b02d;
extern u8 D_1F80019B_e707;
extern u8 D_800BF89C;
void func_8005950C(u8 *a)
{
    u16 s68;
    u16 s54;
    u16 m;
    u8 st;

    switch (a[4]) {
    case 0:
        f_InitializeTombaPlayerActor(a, 0);
        break;
    case 1:
        s68 = D_800E7E68;
        s54 = D_800ECF54;
        if (D_1F800230_d8aa != 0) {
            m = ~D_1F800174_de41;
            D_800ECF54 = s54 & m;
            D_800E7E68 = s68 & m;
        }
        if (D_800BF80F_fcc6 != 0 || D_1F800137_104c != 0) {
            D_800E7E68 = 0;
            D_800ECF54 = 0;
        }
        func_80055C9C(a, *(s16 *)(a + 0x140));
        func_80058918(a);
        if (a[0x146] == 0) {
            D_1F800232 = 1;
        }
        func_800597AC(a);
        func_80053FDC(a, 0);
        D_800E7E68 = s68;
        D_800ECF54 = s54;
        break;
    case 2:
        a[0x17B] = 1;
        func_80067CA4(a);
        func_800597AC(a);
        break;
    case 4:
        s68 = D_800E7E68;
        s54 = D_800ECF54;
        a[0xD] &= 0x7F;
        if (D_1F800137_104c == 0) {
            D_800E7E68 = 0;
            D_800ECF54 = 0;
        } else {
            D_800E7E68 = D_1F800166_b02d;
            D_800ECF54 = D_1F800190_b2e0;
        }
        func_80055C9C(a, *(s16 *)(a + 0x140));
        func_80058F5C(a);
        func_800597AC(a);
        func_80053E50(a);
        D_800E7E68 = s68;
        D_800ECF54 = s54;
        break;
    case 5:
        func_8018BD30(a);
        func_800597AC(a);
        break;
    case 6:
        func_8018BE40(a);
        func_800597AC(a);
        break;
    case 7:
        st = a[5];
        switch (st) {
        case 0:
            f_StopVoicePlayback();
            a[5]++;
            break;
        case 1:
            if (func_80045580(1) != 0) {
                a[5]++;
            }
            break;
        case 2:
            if (D_1F80019B_e707 != 0) {
                D_800BF89C = 4;
                f_EndScriptedInteractionAudio();
                a[4] = 1;
                a[5] = 0;
                a[6] = 0;
                a[7] = 0;
                *(s16 *)(*(u8 **)D_1F800138 + 0x4C) = 2;
                *(s16 *)(*(u8 **)D_1F800138 + 0x4E) = 1;
            }
            break;
        }
        f_AdvanceActorSkeletalAnimation(a);
        break;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_800597AC);

extern void *D_800A4BBC[];
extern u8 D_800BF830;
void func_80059C60(void)
{
    u8 *t = D_800E7E80_f78d;

    if (t[0] != 0) {
        D_1F800247++;
        switch (t[4]) {
        case 0:
            f_InitializeTombaPlayerActor(t, 1);
            if (D_1F800236_18be < 3) {
                if (*(s16 *)(t + 0x17E) & 0x8000) {
                    *(u16 *)(t + 0x32) += 0x46;
                }
                f_SetTombaAnimationIfChanged(t, 4, 0);
            } else {
                f_SetTombaAnimationIfChanged(t, 2, 0);
            }
            t[1] = 1;
            break;
        case 1:
            f_AdvanceActorSkeletalAnimation(t);
            break;
        }
    }
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_80059D28);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80059ED8);

typedef struct {
    u8 anim;
    u8 dur;
    u8 dir;
    u8 flags;
} TombaPoseStep_5A39C;
extern TombaPoseStep_5A39C D_800A4610[];
extern s8 D_800E807E;
s32 f_StepWrappedAngleToward(s32 a, s32 b, s32 step);
void func_8005A39C(u8 *a, s32 arg1)
{
    s32 m;
    s32 t;
    s32 x;
    u8 f;

    if (a[2] == 0) {
        a[0x177] |= 1;
    }
    switch (a[7]) {
    case 0:
        *(s16 *)(a + 0x40) = 0;
        *(s16 *)(a + 0x150) = 0;
        a[7]++;
    case 1:
        if (a[0x6E] == 0) {
            if (a[2] != 0) {
                f_SetTombaAnimationIfChanged(a, D_800A4610[*(s16 *)(a + 0x40)].anim, 4);
            } else {
                m = *(u16 *)(a + 0x6A) & 0xF00;
                if (m == 0x100 || m == 0x200) {
                    if (D_800A4610[*(s16 *)(a + 0x40)].anim != 0xAF && D_800A4610[*(s16 *)(a + 0x40)].anim != 0xB1) {
                        f_SetTombaAnimationIfChanged(a, D_800A4610[*(s16 *)(a + 0x40)].anim, 4);
                    }
                } else {
                    f_SetTombaAnimationIfChanged(a, D_800A4610[*(s16 *)(a + 0x40)].anim, 4);
                }
            }
        } else if (D_800A4610[*(s16 *)(a + 0x40)].anim != 0xB1) {
            f_SetTombaAnimationIfChanged(a, D_800A4610[*(s16 *)(a + 0x40)].anim, 4);
        }
        *(u16 *)(a + 0x14C) = D_800A4610[*(s16 *)(a + 0x40)].dur;
        if (D_800A4610[*(s16 *)(a + 0x40)].dur == 0xFF) {
            a[7] = 6;
            break;
        }
        if (D_800A4610[*(s16 *)(a + 0x40)].flags & 1) {
            D_800E807E = (D_800A4610[*(s16 *)(a + 0x40)].flags & 2) + 6;
            a[7]++;
        } else {
            a[7] = 3;
        }
        break;
    case 2:
        D_800E807E = (D_800A4610[*(s16 *)(a + 0x40)].flags & 2) + 7;
    case 3:
        if (arg1 == 1) {
            if (--*(s16 *)(a + 0x14C) == 0) {
                a[7] = 1;
                (*(s16 *)(a + 0x40))++;
            }
        }
        if (*(s16 *)(a + 0x150) != D_800A4610[*(s16 *)(a + 0x40)].dir) {
            t = D_800A4610[*(s16 *)(a + 0x40)].dir;
            x = 0;
            if (t == 1) {
                x = a[0x147] != 0;
            }
            t = t + x * 2;
            t <<= 10;
            *(s16 *)(a + 0x14E) = f_StepWrappedAngleToward((s16)t, *(s16 *)(a + 0x14E), 0x80);
            if (*(s16 *)(a + 0x14E) == t) {
                *(s16 *)(a + 0x150) = D_800A4610[*(s16 *)(a + 0x40)].dir;
            }
        }
        f = D_800A4610[*(s16 *)(a + 0x40)].flags;
        if (f & 4) {
            if (*(u16 *)(*(u8 **)(a + 0x38) + 2) == 0xE) {
                D_800E807E = (f & 2) + 6;
                a[7] = 2;
            }
            if (*(u16 *)(*(u8 **)(a + 0x38) + 2) == 0x11) {
                a[7] = 3;
            }
        }
        break;
    case 7:
        a[6] = 3;
        a[7]++;
        break;
    case 8:
        if (arg1 == 1) {
            a[7] = 0;
            f_SetTombaAnimationIfChanged(a, 2, 6);
        }
        break;
    }
}

void func_8005A714(u8 *a)
{
    s32 hi = (*(s16 *)(a + 0x6A) >> 12) & 7;

    switch ((*(s16 *)(a + 0x6A) >> 8) & 0xF) {
    case 1: case 2:
        f_PlaySoundEffect(2, 0, 0);
        if (a[0x46] == 0x10) {
            *(s16 *)(a + 0x40) = 0xB;
        } else {
            *(s16 *)(a + 0x40) = 9;
        }
        return;
    case 10:
        f_PlaySoundEffect(0x90, 1, -0x3C);
        if (a[0x46] == 0x10) {
            *(s16 *)(a + 0x40) = 0xB;
        } else {
            *(s16 *)(a + 0x40) = 9;
        }
        return;
    case 5: case 6:
        if (hi == 0) {
            f_PlaySoundEffect(0x8A, 1, -0x3C);
            if (a[0x46] == 0x10) {
                *(s16 *)(a + 0x40) = 0xB;
            } else {
                *(s16 *)(a + 0x40) = 9;
            }
            return;
        }
    }
    switch (a[0x46]) {
    case 4: case 6: case 8: case 10:
        if (*(s16 *)(a + 0x42) == 0) { f_PlaySoundEffect(0, -3, 0); } else { f_PlaySoundEffect(0, 5, 0); }
        *(s16 *)(a + 0x40) = 9;
        *(s16 *)(a + 0x42) = ~*(s16 *)(a + 0x42) & 1;
        break;
    case 12: case 14: case 0xE0:
        f_PlaySoundEffect(1, 0, 0);
        *(s16 *)(a + 0x40) = 9;
        break;
    case 0x10:
        f_PlaySoundEffect(1, 0, 0);
        *(s16 *)(a + 0x40) = 0xB;
        func_800538E0(a, a + 0x2C, 0);
        break;
    default:
        *(s16 *)(a + 0x40) = 9;
        break;
    }
}

extern u8 D_800BF816;
void func_8005A910(void *arg0) {
    if ((D_800BF816 != 0) || (M2C_FIELD(arg0, u8 *, 0x17C) == 0) || (M2C_FIELD(arg0, u16 *, 0x17E) & 0x640)) {
        func_8005A970();
        return;
    }
    func_80112B50();
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_8005A970);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8005ACC8);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8005AEE4);

s32 func_8005B134(s32 unused, u8 *a)
{
    if (a[0xC] != 2) {
        return -1;
    }
    switch (a[2]) {
    case 3:
        return 0;
    case 7:
        return 1;
    case 16:
        return 0x82;
    case 0:
        return 3;
    case 25:
        return 0x84;
    case 17:
        return 5;
    case 41:
        return 6;
    case 27:
        if (a[3] & 3) {
            return 0x8B;
        }
        return 0x87;
    case 28:
    case 39:
        return 8;
    case 13:
        return 9;
    case 45:
        return 0xA;
    case 69:
        return 0xC;
    case 95:
        return 0x8D;
    case 94:
        return 0xE;
    case 92:
        return 0x8F;
    }
    return -1;
}

extern u16 D_800A46AC[];
void func_8005B20C(u8 *a, s32 b)
{
    u8 *t = *(u8 **)(a + 0x10);

    if (b == 0) {
        t[0x2A] = a[0x2A];
        *(s32 *)(t + 0x2C) = *(s32 *)(a + 0x2C);
        *(s32 *)(t + 0x34) = *(s32 *)(a + 0x34);
        if (*(s16 *)(a + 0x17E) >= 0) {
            *(u16 *)(t + 0x32) = *(u16 *)(a + 0x32) + *(u16 *)(t + 0x84) + 0x50;
        } else {
            *(u16 *)(t + 0x32) = *(u16 *)(a + 0x32) + *(u16 *)(t + 0x84) + 0x28;
        }
        if (a[0x78] < 6) {
            *(u16 *)(t + 0x56) = *(u16 *)(a + 0x56);
        }
        if (a[0x78] == 6) {
            *(s16 *)(a + 0x58) = -0x100;
            *(s16 *)(t + 0x58) = -0x100;
        } else {
            *(u16 *)(t + 0x58) = *(u16 *)(a + 0x58);
        }
        return;
    }
    t[0x2A] = a[0x2A];
    *(s16 *)(t + 0x2E) = (*(s32 *)(*(u8 **)(a + 0xDC) + 0x2C) + *(s32 *)(*(u8 **)(a + 0xD0) + 0x2C)) / 2;
    *(s16 *)(t + 0x32) = (*(s32 *)(*(u8 **)(a + 0xDC) + 0x30) + *(s32 *)(*(u8 **)(a + 0xD0) + 0x30)) / 2;
    *(s16 *)(t + 0x36) = (*(s32 *)(*(u8 **)(a + 0xDC) + 0x34) + *(s32 *)(*(u8 **)(a + 0xD0) + 0x34)) / 2;
    *(u16 *)(t + 0x56) = *(u16 *)(a + 0x56);
    *(u16 *)(t + 0x58) = D_800A46AC[*(s16 *)(a + 0x40)];
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_8005B370);

s32 func_8005B5E4(u8 *a)
{
    switch (a[2]) {
    case 1: case 8: case 19: case 51:
        return 1;
    case 0: case 16: case 25: case 27: case 95:
        return 2;
    case 65:
        return 3;
    case 64:
        return 4;
    }
    return 0;
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_8005B63C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8005C138);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8005C26C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8005C8A0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8005CDF8);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8005D16C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8005D530);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8005DE54);

typedef struct { u8 pad0[0x2E]; u16 x; u8 pad30[6]; u16 z; } Pos_E580;
extern u16 D_1F800188;
extern u16 D_1F80018A;
extern u16 D_1F800194;
void func_8005E580(u8 *a)
{
    s32 t;
    s16 v;
    s32 r;

    switch (a[6]) {
    case 0:
        a[0x61] = 0x30;
        f_ResetTombaControlState(a);
        ((Pos_E580 *)a)->x = D_1F800188;
        ((Pos_E580 *)a)->z = D_1F80018A;
        f_SetTombaAnimationIfChanged(a, 2, 4);
        a[6]++;
        D_1F800194 = (D_1F80018C_c065 - 0x800) & 0xFFF;
    case 1:
    case 3:
        t = D_1F800194 & 0xFFF;
        v = f_StepWrappedAngleToward(t, *(s16 *)(a + 0x56), 0x100);
        *(s16 *)(a + 0x56) = v;
        if (v == t) {
            a[6]++;
        }
        f_AdvanceActorSkeletalAnimation(a);
        *(u16 *)(a + 0x32) += 8;
        f_UpdateTombaLostGroundSupportMotion(a, 1);
        break;
    case 2:
        f_ReadTombaDirectionalInput(a, 0);
        r = func_800558B4(a);
        if (r != 1) {
            a[0x61] = 0;
            a[6]++;
            a[0x147] = a[0x14A] & 1;
            f_ResetTombaControlState(a);
            if (a[0x147] != 0) {
                D_1F800194 = (*(u16 *)(a + 0x140) - 0x800) & 0xFFF;
            } else {
                D_1F800194 = *(u16 *)(a + 0x140);
            }
        } else {
            D_800BF840 = 0x80;
            a[0x61] = 0x31;
            a[6] = 5;
            a[0x147] = r;
            a[0] |= 4;
            f_ResetTombaControlState(a);
        }
        f_AdvanceActorSkeletalAnimation(a);
        *(u16 *)(a + 0x32) += 8;
        f_UpdateTombaLostGroundSupportMotion(a, 1);
        break;
    case 4:
        a[0x61] = 0;
        a[5] = 0;
        a[6] = 0;
        a[7] = 0;
        a[0] &= 3;
        f_AdvanceActorSkeletalAnimation(a);
        *(u16 *)(a + 0x32) += 8;
        f_UpdateTombaLostGroundSupportMotion(a, 1);
        break;
    case 5:
        a[0x2A] = 0;
        D_1F800207_9c67 = 0;
        *(s16 *)(a + 0x58) = 0;
        f_SetTombaAnimationIfChanged(a, 0x63, 0);
        a[0x16B] = 2;
        *(s16 *)(a + 0x4A) = -0x3000;
        a[0x29] = 0;
        *(s16 *)(a + 0x44) = -0xA00;
        a[6]++;
    case 6:
        f_AdvanceActorSkeletalAnimation(a);
        f_AdvanceTombaAlongMovementVector(a, 1);
        f_UpdateTombaMovementOrientation(a);
        f_UpdateTombaAirborneMotion(a, 0x11);
        if (a[0x145] == 2) {
            f_SetTombaAnimationIfChanged(a, 0x64, 6);
        }
        if (a[0x29] != 0) {
            f_SetTombaAnimationIfChanged(a, 0x17, 1);
            *(s16 *)(a + 0x44) = 0;
            a[0x16B] = 1;
            a[6]++;
        }
        break;
    case 7:
        if (func_80055824() != 0) {
            a[0x61] = 0;
            a[5] = 2;
            a[6] = 0;
            a[7] = 0;
            a[0] &= 3;
        } else if ((D_800ECF54 & 0x10) || f_AdvanceActorSkeletalAnimation(a) == 1) {
            goto reset;
        } else {
            f_ReadTombaDirectionalInput(a, 0);
            if ((D_800ECF54 & 0x10) || !(a[0x14A] & 2)) {
            reset:
                a[0x61] = 0;
                a[5] = 0;
                a[6] = 0;
                a[7] = 0;
                a[0] &= 3;
                f_SetTombaAnimationIfChanged(a, 2, 3);
            }
        }
        *(u16 *)(a + 0x32) += 8;
        f_UpdateTombaLostGroundSupportMotion(a, 1);
        break;
    }
}

typedef struct { u8 pad0[0x2E]; u16 x; u8 pad30[6]; u16 z; } Pos_E8FC;
void func_8005E8FC(u8 *a)
{
    s32 t;
    s16 v;

    switch (a[6]) {
    case 0:
        a[0x61] = 0x30;
        f_ResetTombaControlState(a);
        ((Pos_E8FC *)a)->x = D_1F800188;
        ((Pos_E8FC *)a)->z = D_1F80018A;
        f_SetTombaAnimationIfChanged(a, 2, 4);
        a[6]++;
        D_1F800194 = D_1F80018C_c065 & 0xFFF;
    case 1:
    case 3:
        t = D_1F800194 & 0xFFF;
        v = f_StepWrappedAngleToward(t, *(s16 *)(a + 0x56), 0x100);
        *(s16 *)(a + 0x56) = v;
        if (v == t) {
            a[6]++;
        }
        f_AdvanceActorSkeletalAnimation(a);
        *(u16 *)(a + 0x32) += 8;
        f_UpdateTombaLostGroundSupportMotion(a, 1);
        break;
    case 2:
        f_ReadTombaDirectionalInput(a, 0);
        if (func_800558B4(a) != 2) {
            a[0x61] = 0;
            a[6]++;
            a[0x147] = a[0x14A] & 1;
            f_ResetTombaControlState(a);
            if (a[0x147] != 0) {
                D_1F800194 = (*(u16 *)(a + 0x140) - 0x800) & 0xFFF;
            } else {
                D_1F800194 = *(u16 *)(a + 0x140);
            }
        } else {
            D_800BF840 = 0x81;
            a[0x61] = 0x31;
            a[6] = 5;
            a[0x147] = 0;
            a[0] |= 4;
            f_ResetTombaControlState(a);
        }
        f_AdvanceActorSkeletalAnimation(a);
        *(u16 *)(a + 0x32) += 8;
        f_UpdateTombaLostGroundSupportMotion(a, 1);
        break;
    case 4:
        a[0x61] = 0;
        a[5] = 0;
        a[6] = 0;
        a[7] = 0;
        a[0] &= 3;
        f_AdvanceActorSkeletalAnimation(a);
        *(u16 *)(a + 0x32) += 8;
        f_UpdateTombaLostGroundSupportMotion(a, 1);
        break;
    case 5:
        a[0x2A] = 0;
        D_1F800207_9c67 = 0;
        *(s16 *)(a + 0x58) = 0;
        f_SetTombaAnimationIfChanged(a, 0x63, 0);
        a[0x16B] = 2;
        *(s16 *)(a + 0x4A) = -0x3000;
        a[0x29] = 0;
        *(s16 *)(a + 0x44) = 0xA00;
        a[6]++;
    case 6:
        f_AdvanceActorSkeletalAnimation(a);
        f_AdvanceTombaAlongMovementVector(a, 1);
        f_UpdateTombaMovementOrientation(a);
        f_UpdateTombaAirborneMotion(a, 0x11);
        if (a[0x145] == 2) {
            f_SetTombaAnimationIfChanged(a, 0x64, 6);
        }
        if (a[0x29] != 0) {
            f_SetTombaAnimationIfChanged(a, 0x17, 1);
            *(s16 *)(a + 0x44) = 0;
            a[0x16B] = 1;
            a[6]++;
        }
        break;
    case 7:
        if (func_80055824() != 0) {
            a[0x61] = 0;
            a[5] = 2;
            a[6] = 0;
            a[7] = 0;
            a[0] &= 3;
        } else if ((D_800ECF54 & 0x40) || f_AdvanceActorSkeletalAnimation(a) == 1) {
            goto reset;
        } else {
            f_ReadTombaDirectionalInput(a, 0);
            if ((D_800ECF54 & 0x40) || !(a[0x14A] & 2)) {
            reset:
                a[0x61] = 0;
                a[5] = 0;
                a[6] = 0;
                a[7] = 0;
                a[0] &= 3;
                f_SetTombaAnimationIfChanged(a, 2, 3);
            }
        }
        *(u16 *)(a + 0x32) += 8;
        f_UpdateTombaLostGroundSupportMotion(a, 1);
        break;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_8005EC70);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8005EF48);

void func_8005F1B0(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 6);
    switch (temp_v1) {                              /* irregular */
    case 0:
        f_PlaySoundEffect(0x23, 0, 0);
        f_ClearTombaInteractionState(arg0);
        M2C_FIELD(arg0, s16 *, 0x58) = 0;
        M2C_FIELD(arg0, s8 *, 0x61) = 0;
        M2C_FIELD(arg0, s8 *, 0x146) = 0;
        func_800663A8(arg0, 1);
        /* fallthrough */
    case 1:
        func_80066478(arg0);
        return;
    case 2:
        func_80066538(arg0);
        if (M2C_FIELD(arg0, u8 *, 0x29) != 0) {
            func_8005314C(arg0);
            M2C_FIELD(arg0, s8 *, 0x145) = 0;
            M2C_FIELD(arg0, s8 *, 0x144) = 0;
            M2C_FIELD(arg0, u16 *, 0x50) = 0U;
            M2C_FIELD(arg0, s8 *, 0x148) = 0;
            M2C_FIELD(arg0, s8 *, 4) = 1;
            M2C_FIELD(arg0, u8 *, 6) = 0U;
            M2C_FIELD(arg0, s8 *, 7) = 0;
            if (func_8005344C(arg0) == 0) {
                M2C_FIELD(arg0, s16 *, 0x44) = 0;
                f_SetTombaAnimationIfChanged(arg0, 2, 4);
                M2C_FIELD(arg0, s8 *, 5) = 0;
            }
        } else if (M2C_FIELD(arg0, s16 *, 0x4A) >= 0x2701) {
            M2C_FIELD(arg0, s8 *, 4) = 1;
            M2C_FIELD(arg0, u16 *, 0x50) = (u16) M2C_FIELD(arg0, s16 *, 0x4A);
            f_DetachTombaFromSupport(arg0, 0);
            M2C_FIELD(arg0, s16 *, 0x4A) = (s16) M2C_FIELD(arg0, u16 *, 0x50);
        }
        f_UpdateTombaModelOrientationFromFacing(arg0);
        return;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/main", f_UpdateTombaEquipmentChangeAction);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8005FA84);

typedef struct { u8 u0; u8 u1; u8 u2; u8 u3; u8 pad4[2]; u8 u6; u8 u7; u8 pad8[0x29]; u8 u31; } Gs808_FB54;
extern Gs808_FB54 D_800BF808_fb54;
extern u8 D_800BFA47;
extern u8 D_1F80027A;
void func_8005FB54(u8 *a)
{
    u8 *g;
    s16 v;
    s16 y;
    u16 t;

    D_1F80027A = 1;
    a[0x17B] = 1;
    switch (a[6]) {
    case 0:
        g = D_800BF808;
        g[6] = 0;
        if (D_800BFA47 != 0x80) {
            f_QueueItemMessage(g[3], 1);
        }
        f_ClearTombaInteractionState(a);
        f_ResetTombaControlState(a);
        a[0xD] &= 0x7F;
        if (g[2] == 2) {
            a[0] |= 6;
            g[1] = 1;
        } else if (g[2] == 3) {
            a[0] = 6;
            g[1] = 1;
            func_8005FA84(a);
            break;
        }
        f_SetTombaAnimationIfChanged(a, 0x72, 4);
        a[6]++;
    case 1:
        if (f_AdvanceActorSkeletalAnimation(a) == 1) {
            a[6]++;
            f_SetTombaAnimationIfChanged(a, 0x73, 2);
        }
        break;
    case 2:
        if (f_AdvanceActorSkeletalAnimation(a) == 1) {
            if (D_800BF808_fb54.u2 == 2) {
                D_800BF808_fb54.u1 = 0;
                D_1F800137_104c = 0;
                a[0] = 3;
                *(s16 *)(a + 0x172) = 0x1E;
                a[5] = 0;
                a[6] = 0;
                a[7] = 0;
                f_SetTombaAnimationIfChanged(a, 2, 5);
            } else {
                a[0] &= 3;
                a[6]++;
            }
            D_800BF808_fb54.u2 = 0;
            D_800BF808_fb54.u6 = 1;
        }
        break;
    case 4:
        a[0x17A] = 1;
        f_AdvanceActorSkeletalAnimation(a);
        if (a[2] == 0) {
            v = f_StepWrappedAngleToward((s16)(*(u16 *)(a + 0x140) + 0x400), *(s16 *)(a + 0x56), 0x100);
            *(s16 *)(a + 0x56) = v;
            if (v != ((*(s16 *)(a + 0x140) + 0x400) & 0xFFF)) {
                break;
            }
        } else {
            y = f_CalculateYawFromPositionToPoint(a + 0x2C, (s16)D_1F8000D0_fb20[1], (s16)D_1F8000D0_fb20[5]);
            v = f_StepWrappedAngleToward(y, *(s16 *)(a + 0x56), 0x100);
            *(s16 *)(a + 0x56) = v;
            if (v != (y & 0xFFF)) {
                break;
            }
        }
        if (f_IsEventPresentationComplete() != 0) {
            if (--*(s16 *)(a + 0x40) == 0) {
                *(s16 *)(a + 0x40) = 0x14;
                a[6]++;
                f_SetTombaAnimationIfChanged(a, 0x72, 4);
            }
        }
        break;
    case 5:
        a[0x17A] = 1;
        f_AdvanceActorSkeletalAnimation(a);
        if (--*(s16 *)(a + 0x40) == 0) {
            *(s16 *)(a + 0x7A) = 0;
            *(s16 *)(a + 0x7C) = 0;
            *(s16 *)(a + 0x7E) = 0;
            func_8006804C(a);
            a[6]++;
        }
        break;
    case 6:
        a[0x17A] = 1;
        f_AdvanceActorSkeletalAnimation(a);
        if (*(s16 *)(a + 0x7E) != 0) {
            a[6]++;
            D_800BF808_fb54.u7 = 4;
            D_800BF808_fb54.u31 = 1;
            *(s16 *)(a + 0x40) = 0x14;
            *(s16 *)(a + 0x42) = 0xC;
        }
        break;
    case 7:
        a[0x17A] = 1;
        f_AdvanceActorSkeletalAnimation(a);
        if (!(*(u16 *)D_1F80017C & 7)) {
            f_PlaySoundEffect(0x38, *(s8 *)(a + 0x42), 0);
            *(u16 *)(a + 0x42) += 2;
            if (*(s16 *)(a + 0x42) > 0x1A) {
                *(s16 *)(a + 0x42) = 0x1A;
            }
        }
        *(u16 *)(a + 0x32) -= 10;
        if (--*(s16 *)(a + 0x40) == 0) {
            D_800BF808_fb54.u7 |= 0x80;
            *(s16 *)(a + 0x40) = 0x14;
            a[6]++;
        }
        break;
    case 8:
        a[0x17A] = 1;
        if (--*(s16 *)(a + 0x40) == 0) {
            D_800BF808_fb54.u7 &= 0x7F;
            D_1F800236_18be = 5;
            a[6]++;
        }
    case 9:
        if (!(*(u16 *)D_1F80017C & 7)) {
            f_PlaySoundEffect(0x38, *(s8 *)(a + 0x42), 0);
            *(u16 *)(a + 0x42) += 2;
            if (*(s16 *)(a + 0x42) > 0x1A) {
                *(s16 *)(a + 0x42) = 0x1A;
            }
        }
        a[0x17A] = 1;
        f_AdvanceActorSkeletalAnimation(a);
        *(u16 *)(a + 0x32) -= 10;
        break;
    case 10:
        a[0x17A] = 1;
        f_AdvanceActorSkeletalAnimation(a);
        if (f_IsEventPresentationComplete() != 0) {
            a[6] = 5;
            *(s16 *)(a + 0x40) = 1;
        }
        break;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_80060064);

s32 func_80060268(u8 *a)
{
    u16 k = D_800ECF54;
    u8 v;

    if (k & 0x10) {
        a[0x169] |= 2;
        goto end;
    }
    if (k & 0xA0) {
        v = a[0x5F];
        if (v != 0 && a[0x147] == (v & 1)) {
            return 0;
        }
        if (a[0x147] == (a[0x14A] & 1)) {
            if (++D_1F800238 >= 6) {
                a[0x169] = 1;
            }
            a[0x169] |= 1;
            return 1;
        } else {
            D_1F800238 = 0;
            a[0x169] |= 2;
            return 2;
        }
    }
end:
    return 0;
}

extern u8 D_800A46F0[];
void func_8006032C(u8 *a, s32 keep)
{
    s16 r;
    u8 v;

    switch (a[0x169]) {
    case 0:
        break;
    case 1:
        r = D_1F800238 % 6;
        if (r == 0) {
            a[0x168] = a[0x168] + 1;
        } else {
            if (r >= 5) {
                r = 4;
            }
            a[0x168] = r + a[0x168];
        }
        if (a[0x168] >= 0x10) {
            a[0x168] = 0xF;
        }
        break;
    case 2:
    case 3:
        v = a[0x168] - 2;
        a[0x168] = v;
        if ((s8)v < 0) {
            a[0x168] = 0;
        }
        break;
    }
    if (keep == 0) {
        a[0x169] = 0;
    }
    D_1F800238 = 0;
    *(s16 *)(a + 0x44) = D_800A46F0[a[0x168]];
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006042C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80060544);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80060A80);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80060C60);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80061A7C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80061C64);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800620D0);

extern s8 D_800BF80E;
void func_8006228C(void *arg0) {
    u16 temp_v0;
    u16 temp_v0_3;
    u8 temp_v0_2;
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 6);
    switch (temp_v1) {                              /* irregular */
    case 0:
        M2C_FIELD(arg0, s8 *, 0x146) = 0;
        f_ClearTombaInteractionState(arg0);
        f_ResetTombaControlState(arg0);
        f_SetTombaAnimationIfChanged(arg0, 0xE0, 4);
        f_PlaySoundEffect(0x3A, 0, 0);
        M2C_FIELD(arg0, u8 *, 0x167) = 0x1EU;
        M2C_FIELD(arg0, s8 *, 7) = 0;
        M2C_FIELD(arg0, u16 *, 0x40) = 7U;
        M2C_FIELD(arg0, s16 *, 0x42) = 0;
        M2C_FIELD(arg0, u8 *, 6) = (u8) (M2C_FIELD(arg0, u8 *, 6) + 1);
        /* fallthrough */
    case 1:
        f_UpdateTombaHorizontalMovementSpeed(arg0, M2C_FIELD(arg0, u8 *, 0x147));
        f_AdvanceActorSkeletalAnimation(arg0);
        f_AdvanceTombaAlongMovementVector(arg0, 0);
        f_UpdateTombaMovementOrientation(arg0);
        M2C_FIELD(arg0, u16 *, 0x32) = (u16) (M2C_FIELD(arg0, u16 *, 0x32) + 8);
        f_ResolveTombaGroundTerrainContact(arg0);
        if (M2C_FIELD(arg0, u8 *, 0x29) != 0) {
            temp_v0 = M2C_FIELD(arg0, u16 *, 0x40) - 1;
            M2C_FIELD(arg0, u16 *, 0x40) = temp_v0;
            if ((temp_v0 << 0x10) == 0) {
                func_8005A714(arg0);
            }
        }
        f_UpdateTombaLostGroundSupportMotion(arg0, 1);
        f_UpdateTombaModelOrientationFromFacing(arg0);
        temp_v0_2 = M2C_FIELD(arg0, u8 *, 0x167);
        if (temp_v0_2 == 0) {
            if (M2C_FIELD(arg0, u8 *, 0x29) != 0) {
                M2C_FIELD(arg0, s8 *, 5) = 0;
                M2C_FIELD(arg0, u8 *, 6) = 0U;
                return;
            }
            f_DetachTombaFromSupport(arg0, 0);
            return;
        }
        M2C_FIELD(arg0, u8 *, 0x167) = (u8) (temp_v0_2 - 1);
        return;
    case 2:
        D_800BF80E = 0;
        M2C_FIELD(arg0, s8 *, 0x146) = 0;
        f_ClearTombaInteractionState(arg0);
        f_ResetTombaControlState(arg0);
        f_SetTombaAnimationIfChanged(arg0, 0xDF, 4);
        f_PlaySoundEffect(0x3A, 0, 0);
        M2C_FIELD(arg0, u16 *, 0x40) = 0x1EU;
        M2C_FIELD(arg0, u8 *, 6) = (u8) (M2C_FIELD(arg0, u8 *, 6) + 1);
        return;
    case 3:
        f_AdvanceActorSkeletalAnimation(arg0);
        f_UpdateTombaModelOrientationFromFacing(arg0);
        temp_v0_3 = M2C_FIELD(arg0, u16 *, 0x40) - 1;
        M2C_FIELD(arg0, u16 *, 0x40) = temp_v0_3;
        if ((temp_v0_3 << 0x10) == 0) {
            D_800BF80E = 1;
            M2C_FIELD(arg0, s8 *, 4) = 4;
            M2C_FIELD(arg0, s8 *, 5) = 0x20;
            M2C_FIELD(arg0, u8 *, 6) = 0U;
            M2C_FIELD(arg0, s8 *, 7) = 0;
        }
        return;
    }
}

extern s32 D_1F80023C;
extern u8 D_800BF88F;
extern u16 D_801FE0E0;
extern void *D_800ED014;
extern u32 D_800FB170[];
void func_800624B4(u8 *a)
{
    u8 *p;
    u8 *e;
    s32 i;

    a[0x17B] = 1;
    D_1F80027A = 2;
    switch (a[6]) {
    case 0:
        p = D_800BF808;
        p[6] = 0;
        a[0] = 6;
        p[1] = 1;
        if (a[2] == 0) {
            f_ClearTombaInteractionState(a);
            f_UpdateTombaModelOrientationFromFacing(a);
        }
        D_800BF88F = a[0x6F];
        f_ApplyTombaClothesAppearanceAndPhysics(a);
        f_StopVoicePlayback();
        if (a[2] == 0) {
            f_UpdateTombaMovementOrientation(a);
        }
        a[6]++;
        f_AdvanceActorSkeletalAnimation(a);
        e = (u8 *)f_SpawnTransientEffect(0x1E, 0);
        if (e != NULL) {
            e[0x28] |= 0x80;
        }
        f_PlaySoundEffect(0x37, 0x16, 0x1E);
        *(u8 **)(a + 0x10) = e;
        *(s16 *)(a + 0x40) = 5;
        break;
    case 1:
        if (*(s16 *)(a + 0x40) == 0) {
            a[1] = 0;
            a[6]++;
        } else {
            (*(s16 *)(a + 0x40))--;
        }
        break;
    case 2:
        if (D_801FE0E0 != 0) {
            f_StopVoicePlayback();
            break;
        }
        a[6]++;
        break;
    case 3:
        i = *(u16 *)(a + 0x17E) & 0xF;
        if (f_StartCooperativeDiscRead(D_800ED014, D_800FB170[i * 2] >> 11, D_800FB170[i * 2 + 1] - D_800FB170[i * 2]) != 0) {
            a[6]++;
        }
        break;
    case 4:
        if (D_1F80019B_e707 != 0) {
            e = *(u8 **)(a + 0x10);
            if (e != NULL) {
                e[4] = 2;
                e[5] = 0;
            }
            f_RebuildTombaAppearanceModelParts(a);
            a[1] = 1;
            if (D_1F800137_104c != 1) {
                f_PlayAreaBackgroundTrack(D_800BF870.unk0);
            }
            a[0] = 3;
            *(s32 *)(a + 4) = D_1F80023C;
            *(s16 *)(a + 0x172) = 0x1E;
            if (D_1F800137_104c == 2) {
                D_1F800137_104c = 0;
            }
            D_800BF809 = 0;
        }
        break;
    }
}

extern u8 D_800A4700[];
static inline void PlaceOnSupport_271C(u8 *a, u8 *s, s16 ang, s32 r0)
{
    s32 r = r0;

    *(u16 *)(a + 0x2E) = *(u16 *)(s + 0x2C) + ((rcos(ang) * r) >> 12);
    *(u16 *)(a + 0x36) = *(u16 *)(s + 0x34) - ((rsin(ang) * r) >> 12);
}
s32 func_8006271C(u8 *a, s32 f)
{
    u8 *s = *(u8 **)(a + 0x10);
    u8 *b = *(u8 **)(a + 0x158);
    s16 r;
    u16 ang;
    s32 i;
    u16 v;

    r = 0x20;
    if (*(s16 *)(a + 0x17E) >= 0) {
        r = 0x40;
    }
    ang = *(u16 *)(a + 0x56) + 0x800;
    PlaceOnSupport_271C(a, s, ang, r);
    i = f;
    if (a[0x165] != 0) {
        i = f + 3;
    }
    v = (s8)D_800A4700[i];
    switch (f) {
    case 0:
        *(u16 *)(a + 0x156) += v;
        if (*(s16 *)(a + 0x156) < -*(s16 *)(b + 0x84)) {
            *(s16 *)(a + 0x156) = -*(s16 *)(b + 0x84);
        }
        break;
    case 1:
        *(u16 *)(a + 0x156) += v;
        break;
    }
    *(u16 *)(a + 0x32) = *(u16 *)(s + 0x30) + *(u16 *)(a + 0x156);
    f_UpdateTombaForwardContactProbe(a);
    if (D_800BF870.unk0 == 0) {
        if (!func_801148D8(a, b)) {
            goto detach;
        }
        *(u8 **)(a + 0x10) = *(u8 **)D_1F800084;
        s = *(u8 **)(a + 0x10);
        PlaceOnSupport_271C(a, s, ang, r);
        *(u16 *)(a + 0x32) = *(u16 *)(s + 0x30) + *(u16 *)(a + 0x156);
        if (f_ResolveTombaGroundTerrainContact(a) & 1) {
            a[0x164] = 0;
            *(s32 *)(a + 0x158) = 0;
            a[5] = 0;
            a[6] = 0;
            f_SetTombaAnimationIfChanged(a, 2, 3);
            return 0;
        }
        return 1;
    } else if (D_800BF870.unk0 == 6) {
        if (!func_80110E60(a, b)) {
            goto detach;
        }
        *(u8 **)(a + 0x10) = *(u8 **)D_1F800084;
        s = *(u8 **)(a + 0x10);
        PlaceOnSupport_271C(a, s, ang, r);
        *(u16 *)(a + 0x32) = *(u16 *)(s + 0x30) + *(u16 *)(a + 0x156);
        if (f_ResolveTombaGroundTerrainContact(a) & 1) {
            a[0x164] = 0;
            *(s32 *)(a + 0x158) = 0;
            a[5] = 0;
            a[6] = 0;
            f_SetTombaAnimationIfChanged(a, 2, 3);
            return 0;
        }
        return 1;
    }
detach:
    a[0x164] = 0;
    *(s32 *)(a + 0x158) = 0;
    f_DetachTombaFromSupport(a, 0);
    return 0;
}

void f_UpdateTombaClingVerticalMotion(u8 *a, u8 *b, s32 f)
{
    u16 y;
    u16 spd;
    s32 y0;
    s32 k;

    if (f == 3) {
        if (f_ResolveTombaGroundTerrainContact(a) & 1) {
            *(s16 *)(a + 0x4A) = 0;
            *(s16 *)(a + 0x50) = 0;
            a[0x148] = 0;
            b[0x29] = 0;
            a[0x164] = 0;
            *(s32 *)(a + 0x158) = 0;
            a[5] = 0;
            a[6] = 0;
            f_SetTombaAnimationIfChanged(a, 2, 3);
        }
        return;
    }
    if (f & 4) {
        *(s16 *)(a + 0x4A) += 4;
        if (*(s16 *)(a + 0x4A) >= 0x1E) {
            *(s16 *)(a + 0x4A) = 0x1E;
        }
        spd = *(u16 *)(a + 0x4A);
    } else {
        s32 i;

        if (a[0x165] != 0) {
            i = (f & 1) + 3;
        } else {
            i = f & 1;
        }
        spd = (s8)D_800A4700[i];
    }
    if (!(f & 1)) {
        do {
            y = *(u16 *)(a + 0x156);
        } while (0);
        *(s16 *)(a + 0x6A) = 0;
        y0 = *(s16 *)(a + 0x156);
        if (b[2] == 0x17 && b[0x47] != 2) {
            if (f & 2) {
                y -= 0x30;
                *(u16 *)(a + 0x156) = y - (*(s16 *)(b + 0x4A) >> 8);
            } else {
                *(u16 *)(a + 0x156) = y + (spd - (*(s16 *)(b + 0x4A) >> 8));
            }
        } else {
            *(u16 *)(a + 0x156) += spd;
        }
        if (f_ResolveTombaOverheadTerrainContact(a, 1) != 0) {
            *(s16 *)(a + 0x156) = y0;
        }
        if (*(s16 *)(a + 0x156) < -*(s16 *)(b + 0x84)) {
            *(s16 *)(a + 0x156) = -*(s16 *)(b + 0x84);
        }
        return;
    }
    y = *(u16 *)(a + 0x156) + spd;
    do {
        *(u16 *)(a + 0x156) = y;
    } while (0);
    if ((f & 0x80) || (b[2] == 0x17 && b[0x47] != 2)) {
        k = 0;
        if (*(s16 *)(a + 0x17E) < 0) {
            k = 0x50;
        }
        if ((s16)y > k + (*(s16 *)(b + 0x86) - *(s16 *)(b + 0x84)) + *(s16 *)(a + 0x68)) {
            *(s16 *)(a + 0x4A) = 0;
            *(s16 *)(a + 0x50) = 0;
            a[0x148] = 0;
            b[0x29] = 0;
            a[0x164] = 0;
            *(s32 *)(a + 0x158) = 0;
            *(s16 *)(a + 0x44) = 0;
            *(u16 *)(a + 0x156) += 0x2C;
            f_DetachTombaFromSupport(a, 0);
            if (b[2] == 0x17) {
                *(u16 *)(a + 0x4A) = *(u16 *)(b + 0x4A);
                y = *(u16 *)(a + 0x156) + 0x2C;
                *(u16 *)(a + 0x156) = y;
                if (*(u16 *)(a + 0x17E) & 0x60) {
                    *(u16 *)(a + 0x156) = y + ((*(u16 *)(b + 0x4A) & 0x1F00) >> 5);
                }
            }
            return;
        }
    } else if (*(s16 *)(b + 0x86) - *(s16 *)(b + 0x84) < *(s16 *)(a + 0x156)) {
        *(u16 *)(a + 0x156) = *(u16 *)(b + 0x86) - *(u16 *)(b + 0x84);
    }
    if (!(f & 0x40) && (f_ResolveTombaGroundTerrainContact(a) & 1)) {
        b[0x29] = 0;
        a[0x164] = 0;
        *(s32 *)(a + 0x158) = 0;
        a[6] = 0;
        a[7] = 0;
        if (f == 0x85) {
            a[0x147] = 1 - a[0x147];
            f_ResetTombaControlState(a);
            a[5] = 0x35;
            return;
        }
        *(s16 *)(a + 0x4A) = 0;
        *(s16 *)(a + 0x50) = 0;
        a[0x148] = 0;
        a[5] = 0;
        f_SetTombaAnimationIfChanged(a, 2, 3);
    }
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_80062D8C);

typedef struct { u8 pad[0x147]; u8 b147; u8 pad148[0x14]; u8 b15C; } A3098;
void func_80063098(u8 *a)
{
    *(s16 *)(a + 0x154) += 0x20;
    if (*(s16 *)(a + 0x154) > 0x200) {
        *(s16 *)(a + 0x154) = 0x200;
    }
    *(u16 *)(a + 0x42) += *(u16 *)(a + 0x154);
    if ((a[0x147] ^ a[0x15C]) == 0) {
        *(u16 *)(a + 0x56) -= *(u16 *)(a + 0x154);
    } else {
        *(u16 *)(a + 0x56) += *(u16 *)(a + 0x154);
    }
    if (*(s16 *)(a + 0x42) > 0x400) {
        f_PlaySoundEffect(0x1B, 0, 0);
        D_800BF840 = 0x88;
        a[7]++;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_80063158);

s32 func_800633B0(u8 *a)
{
    switch (D_800BF870.unk0) {
    case 0:
        func_8010C290(a);
        break;
    case 1:
        if (func_8010ACB8(a) == 1) {
            return 1;
        }
        break;
    case 4:
        if (func_80115EF0(a) == 1) {
            return 1;
        }
        break;
    case 5:
        func_80110F78(a);
        break;
    case 6:
        func_80114730(a);
        break;
    case 10:
        if (func_8010B3DC(a) == 1) {
            return 1;
        }
        break;
    case 12:
        func_8010CE90(a);
        break;
    case 15:
        if (func_8010BA04(a) == 1) {
            return 1;
        }
        break;
    }
    if (a[5] == 4 || a[5] == 9) {
        return 0;
    }
    return 1;
}

extern u16 D_800ECF54;
s32 func_800634A8(s32 arg0) {
    s32 temp_lo;
    s32 temp_s0;
    s32 temp_s1;

    f_UpdateTombaSupportSwingMotion(arg0, 1);
    f_AdvanceActorSkeletalAnimation(arg0);
    if ((M2C_FIELD(arg0, u8 *, 0x169) == 0) && (D_800ECF54 & (*(u16 *)0x1F800172 | 0x50))) {
        M2C_FIELD(arg0, u16 *, 0x2E) = (u16) M2C_FIELD(arg0, u16 *, 0x14C);
        M2C_FIELD(arg0, u16 *, 0x36) = (u16) M2C_FIELD(arg0, u16 *, 0x150);
        M2C_FIELD(arg0, s16 *, 0x32) = (s16) (M2C_FIELD(arg0, u16 *, 0x14E) + M2C_FIELD(arg0, u16 *, 0x64));
        return (s32) D_800ECF54;
    }
    temp_s0 = (s32) (rsin(M2C_FIELD(arg0, s16 *, 0x58)) * (s16) M2C_FIELD(arg0, u16 *, 0x64)) >> 0xC;
    temp_s1 = (s32) (rsin(M2C_FIELD(arg0, s16 *, 0x56)) * (s16) temp_s0) >> 0xC;
    temp_lo = rcos((s32) M2C_FIELD(arg0, s16 *, 0x56)) * (s16) temp_s0;
    M2C_FIELD(arg0, u16 *, 0x36) = (u16) (M2C_FIELD(arg0, u16 *, 0x150) + temp_s1);
    M2C_FIELD(arg0, u16 *, 0x2E) = (u16) (M2C_FIELD(arg0, u16 *, 0x14C) - (temp_lo >> 0xC));
    M2C_FIELD(arg0, s16 *, 0x32) = (s16) (M2C_FIELD(arg0, u16 *, 0x14E) + ((s32) (rcos((s32) M2C_FIELD(arg0, s16 *, 0x58)) * (s16) M2C_FIELD(arg0, u16 *, 0x64)) >> 0xC));
    return 0;
}

INCLUDE_ASM("asm/main/nonmatchings/main", f_UpdateTombaSupportSwingMotion);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80063B94);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80063ECC);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80063F9C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80064358);

void func_80064524(void *arg0) {
    u8 temp_v1;

    M2C_FIELD(arg0, s8 *, 6) = 2;
    M2C_FIELD(arg0, s8 *, 7) = 0;
    f_ReleaseTombaInteractionTarget(arg0);
    M2C_FIELD(arg0, s16 *, 0x58) = 0;
    M2C_FIELD(arg0, s16 *, 0x40) = 8;
    f_PlaySoundEffect(0x1D, 0, 0);
    f_ReadTombaDirectionalInput(arg0, 0);
    temp_v1 = M2C_FIELD(arg0, u8 *, 0x14A);
    if (temp_v1 & 2) {
        M2C_FIELD(arg0, s8 *, 0x147) = (s8) (M2C_FIELD(arg0, u8 *, 0x149) & 1);
    } else {
        M2C_FIELD(arg0, s8 *, 0x147) = (s8) (temp_v1 & 1);
        M2C_FIELD(arg0, u8 *, 0x149) = (u8) (M2C_FIELD(arg0, u8 *, 0x14A) & 1);
    }
    f_ApplyTombaFacingYaw(arg0);
    f_SetTombaAnimationIfChanged(arg0, 0x14, 0);
}

void func_800645CC(void *arg0) {
    M2C_FIELD(arg0, s8 *, 5) = 9;
    M2C_FIELD(arg0, s8 *, 6) = 0;
    M2C_FIELD(arg0, s8 *, 7) = 0;
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_800645E0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006483C);

void func_80064BA0(u8 *a)
{
    u8 *s;
    volatile s32 r;

    switch (a[6]) {
    case 0:
        *(s16 *)(a + 0x6A) = 0;
        f_SetTombaAnimationIfChanged(a, 0x1A, 0);
        a[0x169] = 0x18;
        a[7] = 0;
        a[0x168] = 1;
        a[6]++;
        if ((*(u32 *)(a + 0x17C) & 0x04400200) == 0x200) {
            a[0x164] = 0;
            *(u8 **)(a + 0x158) = NULL;
            *(s16 *)(a + 0x32) = *(u16 *)(a + 0x14E) + *(u16 *)(a + 0x64);
            f_DetachTombaFromSupport(a, 0);
            break;
        }
    case 1:
        s = *(u8 **)(a + 0x158);
        if (s == (u8 *)1) {
            r = func_800634A8(a);
        } else {
            switch (D_800BF870.unk0) {
            case 0:
                r = func_8010B600(a);
                break;
            case 1:
                r = func_8010AC3C(a);
                break;
            case 4:
                r = func_801161EC(a);
                break;
            case 6:
                r = func_80114784(a);
                break;
            case 8:
                r = func_801136C4(a);
                break;
            case 10:
                r = func_8010B42C(a);
                break;
            case 12:
                r = func_8010CDA4(a);
                break;
            }
        }
        if (r & 0x40) {
            if (s != (u8 *)1) {
                s[0x29] = 0;
            }
            a[0x164] = 0;
            *(u8 **)(a + 0x158) = NULL;
            f_DetachTombaFromSupport(a, 0);
        } else if (r & (D_1F800172_5cdb | 0x10)) {
            if (s != (u8 *)1) {
                s[0x29] = 0;
            }
            a[7] = 0;
            a[6]++;
        }
        break;
    case 2:
        func_8006483C(a, 0);
        if (a[0x29] != 0) {
            *(s16 *)(a + 0x4A) = 0;
            *(u16 *)(a + 0x50) = 0;
            a[0x144] = 0;
            *(u8 **)(a + 0x158) = NULL;
            a[0x164] = 0;
            a[7] = 0;
            *(s16 *)(a + 0x44) = 0;
            a[0x145] = 0;
            func_8005314C(a);
            a[5] = 2;
            a[6] = 2;
            f_SetTombaAnimationIfChanged(a, 0x17, 1);
        } else if (*(s16 *)(a + 0x4A) > 0x2800) {
            *(s16 *)(a + 0x44) = 0;
            *(u8 **)(a + 0x158) = NULL;
            a[0x164] = 0;
            *(u16 *)(a + 0x50) = *(u16 *)(a + 0x4A);
            f_DetachTombaFromSupport(a, 0);
            *(s16 *)(a + 0x4A) = *(u16 *)(a + 0x50);
        }
        f_UpdateTombaModelOrientationFromFacing(a);
        break;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_80064E48);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006506C);

void func_80065374(void) {
    switch (D_800BF870.unk0) {                           /* irregular */
    case 0:
        func_8010AECC();
        return;
    case 5:
        func_80110CB8();
        return;
    case 6:
        func_80113E3C();
        return;
    }
}

void func_800653F4(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 6);
    switch (temp_v1) {                              /* irregular */
    case 0:
        f_ResetTombaControlState(arg0);
        f_SetTombaAnimationIfChanged(arg0, 0x40, 0);
        M2C_FIELD(arg0, s8 *, 7) = 0;
        M2C_FIELD(arg0, u8 *, 6) = (u8) (M2C_FIELD(arg0, u8 *, 6) + 1);
        /* fallthrough */
    case 1:
        if (D_800BF870.unk0 == 0) {
            func_8010C780(arg0);
        }
        return;
    }
}

extern u8 D_800BF816;
void f_UpdateTombaTransitionTerrainContact(void *arg0, s32 arg1) {
    if ((D_800BF816 == 0) || (arg1 == 0)) {
        M2C_FIELD(arg0, s16 *, 0x16C) = 0;
        M2C_FIELD(arg0, s16 *, 0x6A) = 0;
        M2C_FIELD(arg0, s8 *, 0x29) = 1;
        return;
    }
    f_ResolveTombaGroundTerrainContact(arg0);
    f_UpdateTombaLostGroundSupportMotion(arg0, 1);
}

void func_800654D4(u8 *a)
{
    u16 ang;

    switch (a[6]) {
    case 0:
        *(s16 *)(a + 0x58) = 0;
        D_800BF80E_58ec = 0;
        a[6]++;
        f_SetTombaAnimationIfChanged(a, 2, 0);
    case 1:
        ang = D_1F800192 & 0xFFF;
        if ((*(s16 *)(a + 0x56) = f_StepWrappedAngleToward(ang, *(s16 *)(a + 0x56), 0x100)) == ang) {
            a[6]++;
            D_800BF80E_58ec = 1;
        }
        break;
    case 2:
        break;
    }
    f_AdvanceActorSkeletalAnimation(a);
    f_UpdateTombaTransitionTerrainContact(a, 1);
}

extern s8 D_800BF80E;
void func_800655A0(void *arg0) {
    M2C_FIELD(arg0, s16 *, 0x58) = 0;
    D_800BF80E = 0;
    M2C_FIELD(arg0, s8 *, 5) = 0x1E;
    M2C_FIELD(arg0, u8 *, 6) = (u8) (M2C_FIELD(arg0, u8 *, 6) + 1);
    ((void (*)(void))func_800654D4)();
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_800655DC);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800656FC);

void func_8006585C(u8 *t)
{
    switch (t[6]) {
    case 0:
        t[6]++;
    case 1:
        f_AdvanceActorSkeletalAnimation(t);
        D_800BF80E_58ec = 1;
        break;
    }
    if (D_1F800184 == 2) {
        f_UpdateTombaMovementOrientation(t);
        *(s16 *)(t + 0x50) = 0;
        *(s16 *)(t + 0x4A) = 0;
    } else {
        f_UpdateTombaTransitionTerrainContact(t, 0);
    }
}

void func_800658E4(u8 *t)
{
    s32 m;

    switch (t[6]) {
    case 0:
        D_800BF80E_58ec = 0;
        t[6]++;
    case 1:
        if (f_AdvanceActorSkeletalAnimation(t) == 1) {
            D_800BF80E_58ec = 1;
        }
        m = D_1F800184;
        if (m == 1) {
            goto zero;
        }
        if (m == 2) {
            f_UpdateTombaMovementOrientation(t);
        zero:
            *(s16 *)(t + 0x50) = 0;
            *(s16 *)(t + 0x4A) = 0;
            break;
        }
        f_UpdateTombaTransitionTerrainContact(t, 1);
        break;
    }
}

void func_80065990(u8 *a)
{
    switch (a[6]) {
    case 0:
        D_800BF80E_58ec = 0;
        a[6]++;
    case 1:
        if (f_AdvanceActorSkeletalAnimation(a) == 1) {
            f_SetTombaAnimationIfChanged(a, 2, 4);
            D_800BF80E_58ec = 1;
        }
        if (D_1F800184 == 1) {
            goto stop;
        }
        if (D_1F800184 == 2) {
            f_UpdateTombaMovementOrientation(a);
        stop:
            *(s16 *)(a + 0x50) = 0;
            *(s16 *)(a + 0x4A) = 0;
            break;
        }
        f_UpdateTombaTransitionTerrainContact(a, 1);
        break;
    }
}

void func_80065A54(u8 *a)
{
    switch (a[6]) {
    case 0:
        f_ClearTombaInteractionState(a);
        if (D_1F800137_104c == 1) {
            D_800BF80E = 0;
            *(s16 *)(a + 0x40) = 0xE;
        } else {
            switch (D_800BF870.unk0) {
            case 1:
                *(s16 *)(a + 0x40) = 0x26;
                break;
            case 6:
                if (a[0x2A] == 9) {
                    *(s16 *)(a + 0x40) = 6;
                } else {
                    *(s16 *)(a + 0x40) = 0x1C;
                }
                break;
            default:
                *(s16 *)(a + 0x40) = 0x1C;
                break;
            }
        }
        a[0x146] = 0;
        a[0x147] = D_800BF81F >> 4;
        a[6]++;
        f_ResetTombaControlState(a);
        *(s16 *)(a + 0x4A) = 0;
        f_SetTombaAnimationIfChanged(a, 4, 0);
        if (a[0x147] == 0) {
            *(s16 *)(a + 0x44) = 0x1000;
        } else {
            *(s16 *)(a + 0x44) = -0x1000;
        }
        f_UpdateTombaModelOrientationFromFacing(a);
        break;
    case 1:
        f_AdvanceActorSkeletalAnimation(a);
        if (a[0x145] != 0) {
            f_AdvanceTombaAlongMovementVector(a, 1);
            f_UpdateTombaMovementOrientation(a);
            *(u16 *)(a + 0x32) += 8;
            f_ResolveTombaGroundTerrainContact(a);
            f_UpdateTombaLostGroundSupportMotion(a, 1);
        } else {
            f_AdvanceTombaAlongMovementVector(a, 0);
            f_UpdateTombaMovementOrientation(a);
            f_UpdateTombaTransitionTerrainContact(a, 1);
        }
        if (--*(s16 *)(a + 0x40) == 0) {
            a[6]++;
        }
        f_UpdateTombaModelOrientationFromFacing(a);
        if ((s16)(*(s16 *)(a + 0x40) % 7) == 0) {
            f_PlaySoundEffect(0, 5, 0);
        }
        break;
    case 2:
        a[0] = 3;
        *(s16 *)(a + 0x172) = 0x1E;
        a[5] = 0;
        a[6] = 0;
        a[7] = 0;
        f_ResetTombaControlState(a);
        f_SetTombaAnimationIfChanged(a, 2, 3);
        if (D_1F800137_104c == 1) {
            D_800BF80E = 1;
        }
        f_UpdateTombaModelOrientationFromFacing(a);
        break;
    case 3:
        switch (a[7]) {
        case 0:
            *(s16 *)(a + 0x40) = 0x14;
            a[7] = 2;
            break;
        case 1:
            *(s16 *)(a + 0x40) = 1;
            a[7]++;
            break;
        case 2:
            if (--*(s16 *)(a + 0x40) == 0) {
                a[5] = 7;
                a[0] = 3;
                a[6] = 2;
                a[7] = 0;
                *(s16 *)(a + 0x172) = 0x1E;
            }
            break;
        }
        break;
    case 4:
        switch (a[7]) {
        case 0:
            f_ClearTombaInteractionState(a);
            *(s16 *)(a + 0x40) = 0x1C;
            a[7]++;
            f_ResetTombaControlState(a);
            f_SetTombaAnimationIfChanged(a, 4, 0);
            if (a[0x147] == 0) {
                *(s16 *)(a + 0x44) = 0x1000;
            } else {
                *(s16 *)(a + 0x44) = -0x1000;
            }
            f_UpdateTombaModelOrientationFromFacing(a);
            break;
        case 1:
            f_AdvanceActorSkeletalAnimation(a);
            f_AdvanceTombaAlongMovementVector(a, 0);
            f_UpdateTombaMovementOrientation(a);
            *(u16 *)(a + 0x32) += 8;
            f_ResolveTombaGroundTerrainContact(a);
            f_UpdateTombaLostGroundSupportMotion(a, 1);
            if (--*(s16 *)(a + 0x40) == 0) {
                a[7]++;
            }
            f_UpdateTombaModelOrientationFromFacing(a);
            if ((s16)(*(s16 *)(a + 0x40) % 7) == 0) {
                f_PlaySoundEffect(0, 5, 0);
            }
            break;
        case 2:
            a[0] = 3;
            *(s16 *)(a + 0x172) = 0x1E;
            a[5] = 0;
            a[6] = 0;
            a[7] = 0;
            f_ResetTombaControlState(a);
            f_SetTombaAnimationIfChanged(a, 2, 3);
            if (D_1F800137_104c == 2) {
                D_1F800137_104c = 0;
            }
            f_UpdateTombaModelOrientationFromFacing(a);
            break;
        }
        break;
    case 5:
        f_ClearTombaInteractionState(a);
        if (D_1F800137_104c == 1) {
            D_800BF80E = 0;
        }
        *(s16 *)(a + 0x40) = 0x26;
        a[0x146] = 0;
        a[0x147] = D_800BF81F >> 4;
        f_ResetTombaControlState(a);
        *(s16 *)(a + 0x4A) = 0;
        f_SetTombaAnimationIfChanged(a, 4, 0);
        if (a[0x147] == 0) {
            *(s16 *)(a + 0x44) = 0x800;
        } else {
            *(s16 *)(a + 0x44) = -0x800;
        }
        f_UpdateTombaModelOrientationFromFacing(a);
        a[6] = 1;
        break;
    case 6:
        f_ClearTombaInteractionState(a);
        if (D_1F800137_104c == 1) {
            D_800BF80E = 0;
        }
        *(s16 *)(a + 0x40) = 0x25;
        a[0x146] = 0;
        a[0x147] = D_800BF81F >> 4;
        a[6]++;
        f_ResetTombaControlState(a);
        *(s16 *)(a + 0x4A) = 0;
        f_SetTombaAnimationIfChanged(a, 4, 0);
        if (a[0x147] == 0) {
            *(s16 *)(a + 0x44) = 0x1000;
        } else {
            *(s16 *)(a + 0x44) = -0x1000;
        }
        f_UpdateTombaModelOrientationFromFacing(a);
        break;
    case 7:
        f_AdvanceActorSkeletalAnimation(a);
        f_AdvanceTombaAlongMovementVector(a, 0);
        f_UpdateTombaMovementOrientation(a);
        *(u16 *)(a + 0x32) += 8;
        f_ResolveTombaGroundTerrainContact(a);
        if (--*(s16 *)(a + 0x40) == 0) {
            a[6] = 2;
        }
        f_UpdateTombaModelOrientationFromFacing(a);
        if ((s16)(*(s16 *)(a + 0x40) % 7) == 0) {
            f_PlaySoundEffect(0, 5, 0);
        }
        break;
    case 8:
        f_ClearTombaInteractionState(a);
        *(s16 *)(a + 0x40) = 0x1C;
        a[0x146] = 0;
        a[0x147] = D_800BF81F >> 4;
        a[6] = 1;
        f_ResetTombaControlState(a);
        *(s16 *)(a + 0x4A) = 0;
        f_SetTombaAnimationIfChanged(a, 4, 0);
        if (a[0x147] == 0) {
            *(s16 *)(a + 0x44) = 0x1000;
        } else {
            *(s16 *)(a + 0x44) = -0x1000;
        }
        f_UpdateTombaModelOrientationFromFacing(a);
        break;
    case 9:
        *(s16 *)(a + 0x40) = 0x14;
        f_ClearTombaInteractionState(a);
        a[0x146] = 0;
        a[0x147] = D_800BF81F >> 4;
        a[6] = 1;
        f_ResetTombaControlState(a);
        *(s16 *)(a + 0x4A) = 0;
        f_SetTombaAnimationIfChanged(a, 4, 0);
        if (a[0x147] == 0) {
            *(s16 *)(a + 0x44) = 0x1000;
        } else {
            *(s16 *)(a + 0x44) = -0x1000;
        }
        f_UpdateTombaModelOrientationFromFacing(a);
        break;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_800660AC);

extern s8 D_1F800236[];
extern s16 D_800E7EFE;
void func_800661E0(void *arg0) {
    f_AdvanceActorSkeletalAnimation();
    if ((*((u8 *)D_1F800236) == 5) && (M2C_FIELD(arg0, u8 *, 6) == 0)) {
        M2C_FIELD(arg0, u16 *, 0x32) = (u16) (M2C_FIELD(arg0, u16 *, 0x32) + 0xA);
        if (f_ResolveTombaGroundTerrainContact(arg0) != 0) {
            M2C_FIELD(arg0, u8 *, 6) = (u8) (M2C_FIELD(arg0, u8 *, 6) + 1);
            D_800E7EFE = 1;
        }
    }
}

void func_8006625C(u8 *t)
{
    if (D_800BFE55 != 0) {
        return;
    }
    f_ApplyTombaEnvironmentalDamage(t, 1);
    f_PlaySoundEffect(*(s16 *)(t + 0x16E) == 0 ? 0x24 : 0x23, 0, 0);
    f_StartControllerVibration(0, 0x81, 0x81, 0xF);
    *(u16 *)(t + 0x170) = *(u16 *)(t + 0x16E);
    f_ApplyTombaStatusCommand(t, 0xB);
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_800662D8);

void func_800663A8(u8 *a, s32 flag)
{
    if (f_TestWrappedAngleSide(*(s16 *)(a + 0x140), a[0x2B] << 4, 0)) {
        *(s16 *)(a + 0x58) = -0x300;
        a[0x147] = 0;
        *(s16 *)(a + 0x44) = -0x1000;
    } else {
        *(s16 *)(a + 0x58) = -0x300;
        a[0x147] = 1;
        *(s16 *)(a + 0x44) = 0x1000;
    }
    a[0x149] = a[0x14A] = a[0x147] + 2;
    if (flag == 0) {
        f_SetTombaAnimationIfChanged(a, 0x57, 0);
    } else {
        f_SetTombaAnimationIfChanged(a, 0x56, 0);
    }
    *(s16 *)(a + 0x4A) = -0x2800;
    a[7] = 0;
    *(s16 *)(a + 0x40) = 0;
    a[0x145] = 1;
    a[0x29] = 0;
    a[6]++;
    f_UpdateTombaModelOrientationFromFacing(a);
}

void func_80066478(void *arg0)
{
  int new_var;
  s16 temp_v0_2;
  u16 temp_v0;
  if ((*((s16 *) (((signed char *) arg0) + 0x4A))) >= (-0x23FF))
  {
    new_var = -0x200U;
    temp_v0 = (*((u16 *) (((signed char *) arg0) + 0x58))) + 0x40;
    *((u16 *) (((signed char *) arg0) + 0x58)) = temp_v0;
    if (((s16) temp_v0) >= (-0x1FF))
    {
      *((u16 *) (((signed char *) arg0) + 0x58)) = new_var;
      f_AdvanceActorSkeletalAnimation();
    }
  }
  f_AdvanceTombaAlongMovementVector(arg0, 1);
  f_UpdateTombaMovementOrientation(arg0);
  f_ResolveTombaOverheadTerrainContact(arg0, 3);
  temp_v0_2 = ((u16) (*((s16 *) (((signed char *) arg0) + 0x4A)))) + 0x400;
  *((s16 *) (((signed char *) arg0) + 0x4A)) = temp_v0_2;
  if ((temp_v0_2 << 0x10) > 0)
  {
    *((s8 *) (((signed char *) arg0) + 0x145)) = 2;
    *((u8 *) (((signed char *) arg0) + 6)) = (u8) ((*((u8 *) (((signed char *) arg0) + 6))) + 1);
  }
  *((s32 *) (((signed char *) arg0) + 0x30)) = (s32) ((*((s32 *) (((signed char *) arg0) + 0x30))) + ((*((s16 *) (((signed char *) arg0) + 0x4A))) << 8));
}

void func_80066538(void *arg0) {
    u16 temp_v0;
    u16 temp_v0_2;

    temp_v0 = M2C_FIELD(arg0, u16 *, 0x58) + 0x40;
    M2C_FIELD(arg0, u16 *, 0x58) = temp_v0;
    if ((temp_v0 << 0x10) > 0) {
        M2C_FIELD(arg0, s8 *, 0x144) = 1;
        M2C_FIELD(arg0, u16 *, 0x58) = 0U;
    }
    f_AdvanceActorSkeletalAnimation(arg0);
    f_AdvanceTombaAlongMovementVector(arg0, 1);
    f_UpdateTombaMovementOrientation(arg0);
    f_ResolveTombaOverheadTerrainContact(arg0, 3);
    temp_v0_2 = M2C_FIELD(arg0, u16 *, 0x4A) + 0x400;
    M2C_FIELD(arg0, u16 *, 0x4A) = temp_v0_2;
    if ((s16) temp_v0_2 >= 0x2801) {
        M2C_FIELD(arg0, u16 *, 0x4A) = 0x2800U;
    }
    M2C_FIELD(arg0, u16 *, 0x40) = (u16) (M2C_FIELD(arg0, u16 *, 0x40) + 1);
    M2C_FIELD(arg0, s32 *, 0x30) = (s32) (M2C_FIELD(arg0, s32 *, 0x30) + ((s16) M2C_FIELD(arg0, u16 *, 0x4A) << 8));
    f_ResolveTombaGroundTerrainContact(arg0);
}

s32 func_800665F4(u8 *a)
{
    u16 k;
    u8 *g;

    if (*(s16 *)(a + 0x6A) & 0x8000) {
        k = *(u16 *)(a + 0x6A) & 0xF00;
        if (k == 0x100 || k == 0x200) {
            if (*(u16 *)(a + 0x17E) & 0x100) {
                g = (u8 *)&D_800BF870;
                if (D_800BF870.unk0 == 0) {
                    func_801140D0(a);
                } else if (D_800BF870.unk0 == 6) {
                    if (!(*(u16 *)(g + 0x5E6) & 0x40)) {
                        a[5] = 4;
                        a[6] = 0xB;
                    } else {
                        func_80110DD0(a);
                    }
                } else if (D_800BF870.unk0 == 8) {
                    func_8010F110(a);
                } else if (D_800BF870.unk0 == 0xE) {
                    func_8010A3DC(a);
                }
                a[0x144] = 0;
                *(s16 *)(a + 0x58) = 0;
                *(s16 *)(a + 0x50) = 0;
                a[0x145] = 0;
                a[0x148] = 0;
            } else {
                a[5] = 4;
                a[6] = 0xB;
            }
            return 1;
        }
        return 0;
    }
    return 0;
}

void func_8006670C(void *arg0) {
    u16 temp_v0;
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 6);
    switch (temp_v1) {                              /* irregular */
    case 0:
        f_PlaySoundEffect(0x23, 0, 0);
        f_SpawnFlaggedTransientEffectAtFixedPosition(6, arg0 + 0x2C, -0x50);
        M2C_FIELD(arg0, s8 *, 0x61) = 0;
        M2C_FIELD(arg0, s8 *, 0x146) = 0;
        M2C_FIELD(arg0, s8 *, 0x181) = 0;
        func_800663A8(arg0, 0);
        /* fallthrough */
    case 1:
        func_80066478(arg0);
        return;
    case 2:
        func_80066538(arg0);
        if (func_800665F4(arg0) == 0) {
            if (M2C_FIELD(arg0, u8 *, 0x29) != 0) {
                func_8005314C(arg0);
                M2C_FIELD(arg0, s8 *, 0x144) = 0;
                M2C_FIELD(arg0, s16 *, 0x58) = 0;
                M2C_FIELD(arg0, u16 *, 0x50) = 0U;
                M2C_FIELD(arg0, s8 *, 0x145) = 0;
                M2C_FIELD(arg0, s8 *, 0x148) = 0;
                M2C_FIELD(arg0, s8 *, 4) = 1;
                M2C_FIELD(arg0, u8 *, 6) = 0U;
                M2C_FIELD(arg0, s8 *, 7) = 0;
                if (func_8005344C(arg0) == 0) {
                    M2C_FIELD(arg0, s16 *, 0x44) = 0;
                    f_SetTombaAnimationIfChanged(arg0, 2, 0);
                    M2C_FIELD(arg0, s8 *, 5) = 0;
                }
            } else if ((M2C_FIELD(arg0, s16 *, 0x4A) >= 0x2800) || (M2C_FIELD(arg0, s16 *, 0x40) >= 0xD)) {
                M2C_FIELD(arg0, u16 *, 0x50) = (u16) M2C_FIELD(arg0, s16 *, 0x4A);
                M2C_FIELD(arg0, s8 *, 4) = 1;
                f_DetachTombaFromSupport(arg0, 0);
                temp_v0 = M2C_FIELD(arg0, u16 *, 0x50);
                M2C_FIELD(arg0, u16 *, 0x50) = 0U;
                M2C_FIELD(arg0, s16 *, 0x4A) = (s16) temp_v0;
            }
            f_UpdateTombaModelOrientationFromFacing(arg0);
        }
        return;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_80066878);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80066DE8);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80066FA8);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800674F4);

typedef struct { u8 unk0; u8 pad1[0x5E5]; u16 f5E6; } GsArea_762C;
extern GsArea_762C D_800BF870_762c;
typedef struct { u8 pad0[0x3A]; u16 x; u8 pad3C[2]; u16 y; u8 pad40[2]; u16 z; u8 pad44[0x20]; u8 u64; } Cam_762C;
extern Cam_762C D_800E8008_a455;
extern u8 D_800BFAD7;
void func_8006762C(u8 *a)
{
    s32 pad[4];

    switch (a[6]) {
    case 0:
        if (D_800BFAD7 == 0) {
            func_8006625C(a);
        }
    case 11:
        f_ApplyTombaStatusCommand(a, 2);
        f_ClearTombaInteractionState(a);
        f_PlaySoundEffect(0x24, 0, 0);
        D_800BF80D = 1;
        a[6] = 6;
        break;
    case 1:
    case 6:
        D_1F8001A4 = D_1F80019E;
        if (D_800BF870_762c.unk0 == 0) {
            func_8010CAEC(a);
        } else if (D_800BF870_762c.unk0 == 6) {
            if (!(D_800BF870_762c.f5E6 & 0x40)) {
                f_PlaySoundEffect(0x8B, 0, 0);
            }
            func_801147CC(a);
        } else if (D_800BF870_762c.unk0 == 8) {
            func_8011370C(a);
        } else if (D_800BF870_762c.unk0 == 13) {
            func_8010ACC0(a);
        } else if (D_800BF870_762c.unk0 == 14) {
            func_8010B4F4(a);
        }
        a[0x145] = 0;
        a[0x146] = 0;
        a[0x61] = 0;
        f_ResetTombaControlState(a);
        f_SetTombaAnimationIfChanged(a, 0x71, 0);
        f_UpdateTombaModelOrientationFromFacing(a);
        *(s16 *)(a + 0x4A) = 0x2400;
        *(s16 *)(a + 0x58) = 0;
        *(s16 *)(a + 0x40) = 10;
        a[7] = 0;
        a[6]++;
        break;
    case 2:
    case 7:
        if (--*(s16 *)(a + 0x40) == -1) {
            D_800E8008_a455.u64 = 8;
            D_800E8008_a455.x = D_1F800160;
            D_800E8008_a455.y = D_1F800162;
            D_800E8008_a455.z = D_1F800164;
            *(s16 *)(a + 0x40) = 20;
            a[6]++;
        }
        func_800674F4(a);
        f_AdvanceActorSkeletalAnimation(a);
        break;
    case 3:
    case 8:
        if (--*(s16 *)(a + 0x40) == 0) {
            if (a[6] == 8) {
                func_800662D8(a, 1);
            } else {
                func_800662D8(a, 0);
            }
            D_800BF808[5] = 2;
            D_800BF808[7] = 2;
            a[6]++;
            func_8005245C();
        }
        func_800674F4(a);
        f_AdvanceActorSkeletalAnimation(a);
        break;
    case 4:
    case 9:
        if (D_800BF808[7] == 0) {
            D_800BF808[5] = 3;
            a[6]++;
        }
        func_800674F4(a);
        f_AdvanceActorSkeletalAnimation(a);
        break;
    case 5:
    case 10:
        func_800674F4(a);
        f_AdvanceActorSkeletalAnimation(a);
        break;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_800678E8);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80067A40);

void func_80067CA4(u8 *a)
{
    switch (a[5]) {
    case 0:
        func_8006670C(a);
        func_80053FDC(a, 0);
        break;
    case 1:
        func_80066878(a);
        break;
    case 2:
        func_80066DE8(a);
        func_80053FDC(a, 0);
        break;
    case 3:
        func_80066FA8(a);
        func_80053FDC(a, 1);
        break;
    case 4:
        func_8006762C(a);
        break;
    case 5:
        func_800678E8(a);
        break;
    case 6:
        if (D_800BF870.unk0 == 5) {
            func_801105FC(a);
        } else {
            func_8010B938(a);
        }
        func_80053FDC(a, 1);
        break;
    case 7:
        func_80067A40(a);
        break;
    }
}

typedef struct {
    s16 x, y, w, h;
} Rect_7DA8;
extern u16 D_800A4800[];
extern u16 D_800A4840[];
extern u16 D_800A4880[];
extern u16 D_800A48C0[];
extern u16 D_800A4900[];
extern u16 D_800A4940[];
extern u16 D_800A4980[];
extern u16 D_800A49A0[];
extern u16 D_800A49C0[];
void func_80067DA8()
{
    Rect_7DA8 r;
    u16 *a, *b, *c, *d, *e;

    switch (D_800BF88D) {
    case 0:
        a = D_800A4800;
        b = a + 0x10;
        c = D_800A48C0;
        d = c + 0x10;
        e = D_800A4980;
        break;
    case 1:
        a = D_800A4840;
        b = a + 0x10;
        c = D_800A4900;
        d = c + 0x10;
        e = D_800A49A0;
        break;
    case 2:
        a = D_800A4880;
        b = a + 0x10;
        c = D_800A4940;
        d = c + 0x10;
        e = D_800A49C0;
        break;
    default:
        return;
    }
    r.w = 0x10;
    r.h = 1;
    r.x = 0x1F0;
    r.y = 0x1E2;
    LoadImage(&r, a);
    r.y = 0x1E5;
    LoadImage(&r, b);
    r.y = 0x1C9;
    LoadImage(&r, c);
    r.y = 0x1D0;
    LoadImage(&r, d);
    r.y = 0x1B3;
    LoadImage(&r, e);
}

void f_ApplyTombaClothesAppearanceAndPhysics(u8 *a)
{
    switch (a[0x6F]) {
    case 0:
        *(u16 *)(a + 0x17E) = (*(u16 *)(a + 0x17E) & 0x8000) | 0x10;
        break;
    case 17:
        *(u16 *)(a + 0x17E) = 0x10A;
        break;
    case 15:
        *(u16 *)(a + 0x17E) = 0x41;
        break;
    case 18:
        *(u16 *)(a + 0x17E) = 0x404;
        break;
    case 19:
        *(u16 *)(a + 0x17E) = 0x805;
        break;
    case 20:
        *(u16 *)(a + 0x17E) = 0x1006;
        break;
    case 21:
        *(u16 *)(a + 0x17E) = (*(u16 *)(a + 0x17E) & 0x8000) | 0x2007;
        break;
    case 22:
        *(u16 *)(a + 0x17E) = 0x4008;
        break;
    case 14:
        *(u16 *)(a + 0x17E) = 0x22;
        break;
    case 108:
        *(u16 *)(a + 0x17E) = 0x209;
        break;
    case 16:
        *(u16 *)(a + 0x17E) = 0x83;
        break;
    }
    if (a[0x174] & 4) {
        *(u16 *)(a + 0x17E) |= 0x8000;
    }
    D_800BF89E = *(u16 *)(a + 0x17E);
    f_InitializeHudTombaAnimation(D_800ED058_93c7);
}

void func_80067FE4(void *arg0) {
    u8 temp_v1;

    if (M2C_FIELD(arg0, u8 *, 0x6E) != 0) {
        M2C_FIELD(M2C_FIELD(arg0, void **, 0x74), s8 *, 4) = 3;
    }
    temp_v1 = M2C_FIELD(arg0, u8 *, 0x6E);
    if ((temp_v1 == 0x28) || (temp_v1 == 0x61)) {
        M2C_FIELD(arg0, void **, 0x74) = f_SpawnBackEquipmentProxyActor(arg0, 0, 0);
    }
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006804C);

typedef struct {
    u8 pad0[4]; u8 s4; u8 s5; u8 pad6[0x22]; u8 f28; u8 pad29[3];
    u16 f2C; u16 f2E; u16 f30; u16 f32; u16 f34; u16 f36; u8 pad38[0x18];
    s32 f50; s32 f54; s32 f58; u8 pad5C[6]; s16 f62;
} Actor_8214;
void func_80068214(Actor_8214 *o)
{
    Actor_8214 *a;

    if (D_1F800236_18be == 6) {
        func_800525D0(o, 1);
        return;
    }
    a = (Actor_8214 *)f_SpawnTransientEffect(0x1B, -0x60);
    if (a != NULL) {
        a->f28 |= 0x80;
        a->f2C = o->f2E;
        a->f2E = o->f32 + o->f62 * 2;
        a->f30 = o->f36;
        a->f54 = 0x200;
        a->f58 = 0x200;
        a->s4 = 1;
        a->f50 = 0;
        a->s5 = 4;
    }
}

void func_800682C4(u8 *a, s32 flag)
{
    u8 *g = (u8 *)&D_800BF870;

    a[0x6C] = g[0x1C];
    a[0x176] = g[0x1C];
    a[0x6D] = g[0x1D];
    a[0x6F] = g[0x1F];
    a[0x6E] = g[0x1E];
    a[0x174] = g[0x11];
    if (a[0x174] & 8) {
        a[0xD] = 0x42;
    }
    if (a[0x174] & 0x30) {
        a[0xD] |= 0x12;
    }
    *(s32 *)(a + 0x70) = 0;
    *(s32 *)(a + 0x74) = 0;
    func_80067DA8(a);
    f_ApplyTombaClothesAppearanceAndPhysics(a);
    if (flag == 0) {
        func_80067FE4(a);
        if (g[0x175] == 6) {
            func_8011740C(a, 2);
        }
    }
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_800683B8);

void func_80068610(void *arg0, void *arg1) {
    u16 temp_v0;
    u16 temp_v0_2;

    if (M2C_FIELD(arg0, u8 *, 7) == 0) {
        temp_v0 = M2C_FIELD(arg0, u16 *, 0x4C) + ((s32) (M2C_FIELD(arg1, u16 *, 0xC) << 0x10) >> 0x12);
        M2C_FIELD(arg0, u16 *, 0x4C) = temp_v0;
        if ((s16) temp_v0 >= 0x501) {
            M2C_FIELD(arg0, u8 *, 7) = (u8) (M2C_FIELD(arg0, u8 *, 7) + 1);
        }
    } else {
        temp_v0_2 = M2C_FIELD(arg0, u16 *, 0x4C) - ((s32) (M2C_FIELD(arg1, u16 *, 0xC) << 0x10) >> 0x12);
        M2C_FIELD(arg0, u16 *, 0x4C) = temp_v0_2;
        if ((s16) temp_v0_2 < -0x200) {
            M2C_FIELD(arg0, u8 *, 7) = 0U;
        }
    }
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_80068698);

/* a05 func_80126598, inlined (rsin / rcos, angle at 0xBE) */
static inline void Move_8A94(u8 *a)
{
    s32 v, x, z;

    *(u16 *)(a + 0x58) += 0x200;
    *(s32 *)(a + 0x30) += rsin(*(s16 *)(a + 0xBE)) * *(s16 *)(a + 0x44) * 0x10;
    v = (rcos(*(s16 *)(a + 0xBE)) * *(s16 *)(a + 0x44)) >> 4;
    x = *(s16 *)(a + 0x48) * v;
    z = *(s16 *)(a + 0x4C) * v;
    *(s32 *)(a + 0x2C) += x;
    *(s32 *)(a + 0x34) += z;
    if (!(a[0x46] & 8)) {
        *(s16 *)(a + 0x56) = ratan2(-z, x);
    }
}
void func_80068A94(u8 *a)
{
    u8 *b = a + 0x60;

    if (a[0x2B] != 0) {
        a[0] = 2;
        a[4] = 2;
        a[5] = 0;
    } else if (--*(s16 *)(a + 0x40) == 0) {
        a[0x2B] = 2;
        a[0] = 2;
        a[4] = 3;
    }
    Move_8A94(a);
    if (func_80069858(a, 0, 0)) {
        a[0x2B] = 2;
        f_PlaySoundEffect(0xE, 0, 0);
        f_SpawnImpactTransientEffect(2, a + 0x2C, 0, (u16 *)(b + 8));
    }
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_80068BE8);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80068E68);

void func_80068FBC(u8 *a)
{
    switch (a[4]) {
    case 0:
        func_80068E68(a);
        break;
    case 1:
        switch (a[5]) {
        case 0:
            a[1] = 1;
            if (a[3] & 0x80) {
                f_UpdateActorUnscaledModelTransforms((s32)a);
            } else {
                f_UpdateActorScaledOffsetModelTransforms(a);
            }
            break;
        case 1:
            a[0] = 1;
            a[0x2B] = 0;
            a[5]++;
        case 2:
            func_80068A94(a);
            if (a[3] & 0x80) {
                f_UpdateActorUnscaledModelTransforms((s32)a);
            } else {
                f_UpdateActorScaledOffsetModelTransforms(a);
            }
            if (!f_TestActorVisibilityWithXYZOffset(a, 0, 0, 0)) {
                if (--*(s16 *)(a + 0x42) == 0) {
                    a[4] = 3;
                    a[0x2B] = 2;
                    a[0] = 2;
                }
            }
            break;
        }
        break;
    case 2:
        func_80068BE8(a);
        break;
    case 3:
        func_8007AB44(a);
        break;
    }
}

void func_8006914C(u8 *a)
{
    u8 *b;
    u8 s;
    u8 t;

    s = a[0];
    b = a + 0x60;
    if (s == 2) {
        *(s16 *)(a + 0x44) = 0;
        a[0x2B] = 1;
        a[4] = s;
        t = D_1F800251;
        *(s16 *)(b + 0xE) = 1;
        D_1F800251 = t - 1;
    }
}

void func_8006918C(u8 *a, s32 check)
{
    u8 *t = D_800E7E80_f78d;
    s32 hit;

    if (check != 0) {
        hit = 0;
        if (!(a[0x46] & 4) && t[0x5F] != 0) {
            hit = (t[0x5F] & 1) == t[0x147];
        }
        if (hit) {
            goto spawn;
        }
    }
    if (func_80069858(a, 0, 0) != 0) {
    spawn:
        a[0] = 2;
        f_PlaySoundEffect(0xE, 0, 0);
        f_SpawnImpactTransientEffect(2, a + 0x2C, 0, a + 0x68);
        func_8006914C(a);
    }
}

void func_8006923C(u8 *a)
{
    u8 *p = a + 0x60;

    switch ((a[0x46] >> 1) & 3) {
    case 0:
    case 1:
        *(s16 *)(p + 0xA) = 0;
        break;
    case 2:
        *(s16 *)(p + 0xA) = 0xE80;
        break;
    case 3:
        *(s16 *)(p + 0xA) = 0xC00;
        break;
    }
    *(s16 *)(a + 0x40) = 1;
    *(s16 *)(a + 0x44) = 0x6E;
    a[0x46] &= 7;
    f_PlaySoundEffect(0x22, 0, 0);
    func_8006B020(a, 2);
    *(u16 *)(a + 0x56) = *(u16 *)(p + 8);
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_80069300);

extern u16 D_800A4A6C_tbl2[][2];
void func_80069634(u8 *a)
{
    *(u16 *)(a + 0x44) = D_800A4A6C_tbl2[a[2] - 1][a[0x5E]];
    if (a[0x5E] != 0) {
        *(s16 *)(a + 0x40) = 2;
    } else {
        *(s16 *)(a + 0x40) = 1;
    }
}

void func_80069688(u8 *a)
{
    u8 *b = a + 0x60;

    if (a[0x5E] == 0) {
        *(s16 *)(b + 0x16) = D_800A4A84[a[2]];
    } else {
        *(s16 *)(b + 0x16) = D_800A4A8C[a[2]];
    }
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_800696C4);

extern s16 D_1F80018C_67a7;
s32 func_80069858(u8 *a, s32 b, s32 c)
{
    if (D_800E7FEB != 0) {
        s16 x = rcos(D_1F80018C_67a7) >> 4;
        s32 ang = D_1F80018C_67a7;

        *(s16 *)(a + 0x48) = x;
        *(s16 *)(a + 0x4C) = -(rsin(ang) >> 4);
    } else {
        if (f_ResolveActorAreaPlanePosition(a) < 0) {
            f_ApplyAreaPlaneDirectionToActor(a);
            return 1;
        }
        f_ApplyAreaPlaneDirectionToActor(a);
    }
    if (c != 0) {
        return 0;
    }
    if (b == 0) {
        if (a[0x2B] != 0) {
            return 0;
        }
    }
    if (D_800E7FEB == 0) {
        return func_800696C4(a, (u8)(a[2] - 2) < 2);
    }
    return 0;
}

extern s32 D_1F800208;
extern s16 D_1F800200;
extern s16 D_1F800202;
extern s16 D_1F800204;
s32 func_80069948(u8 *a)
{
    s32 r = func_80069858(a, 0, 0);

    if (r != 0) {
        a[0] = 2;
        a[0x2B] = 2;
        if (r == 2) {
            {
                            u16 x = *(u16 *)(a + 0x2E);

                            D_1F800208 = 1;
                            D_1F800200 = x;
                        }
            D_1F800202 = *(u16 *)(a + 0x32);
            D_1F800204 = *(u16 *)(a + 0x36);
            a[0x29] = 1;
            a[5] = r;
            a[6] = 0;
            a[7] = 0;
            f_PlaySoundEffect(0xC, 0, 0);
            f_SpawnImpactTransientEffect(1, a + 0x2C, a[0x5E], (u16 *)(a + 0x68));
            return 2;
        }
        f_PlaySoundEffect(0xE, 0, 0);
        f_SpawnImpactTransientEffect(2, a + 0x2C, a[0x5E], (u16 *)(a + 0x68));
        return 1;
    }
    return 0;
}

s16 func_80069A2C(u8 *a, s16 x, s16 y, s16 z)
{
    u8 *r = a + 0x60;
    s32 dx = x - *(s16 *)(a + 0x2E);
    s32 dy = y - *(s16 *)(a + 0x32);
    s32 dz = z - *(s16 *)(a + 0x36);
    s32 c = rcos(-*(s16 *)(r + 8));
    s32 s = rsin(-*(s16 *)(r + 8));

    return ratan2(dy, (c * dx + s * dz) >> 12);
}

void func_80069AE4(u16 *a)
{
    struct { u8 pad[0xDC]; u16 *p; } *g = (void *)D_800E7E80;

    a[0x17] = g->p[0x16];
    a[0x19] = g->p[0x18];
    a[0x1B] = g->p[0x1A];
}

void func_80069B28(void)
{
    Linked *a = D_800F2738;
    Linked *next;

    while (a != NULL) {
        next = a->next;
        a->callback(a);
        a = next;
    }
}

extern u8 *D_800E7F5C;
extern s32 D_800BE358_bdda;
s32 func_80069B6C(u8 *a)
{
    u8 *t = D_800E7F5C;

    if ((u16)(*(u16 *)(t + 0x34) - *(u16 *)(a + 0x36) + 0xE6) >= 0x1CD) {
        return 0;
    }
    if ((u16)(*(u16 *)(t + 0x2C) - *(u16 *)(a + 0x2E) + 0xE6) >= 0x1CD) {
        return 0;
    }
    return (u16)(*(u16 *)(t + 0x30) - *(u16 *)(a + 0x32) + 0xE6) < 0x1CD;
}

extern u8 D_1F80027C;
void func_80069BEC(u8 *a, s32 flag)
{
    u8 *m = a + 0x60;

    switch ((a[0x46] >> 1) & 3) {
    case 0:
    case 1:
        D_1F80027C = 0;
        *(s16 *)(m + 0xA) = 0;
        break;
    case 2:
        D_1F80027C = 1;
        *(s16 *)(m + 0xA) = 0xE40;
        break;
    case 3:
        D_1F80027C = 2;
        if (a[2] == 1) {
                    *(s16 *)(m + 0xA) = 0xC10;
                } else {
                    *(s16 *)(m + 0xA) = 0xC00;
                }
        break;
    }
    a[0x46] &= 7;
    *(s16 *)(a + 0x58) = *(s16 *)(m + 0xA);
    f_PlaySoundEffect(0x22, 0, 0);
    func_80069634(a);
    func_80069AE4((u16 *)a);
    if (flag == 0) {
        ((u8 *(*)())f_SpawnLinkedActorTrailEffect)(a, a[2] - 1);
    }
}

extern s32 D_1F800280;
void func_80069CD8(u8 *a, s32 b)
{
    u8 *q = (u8 *)D_1F800280;
    u8 *m = a + 0x60;
    u8 *p = (u8 *)b;
    s16 r;
    s32 dz;
    s32 dx;
    u16 x;
    u16 y;
    u16 z;
    s16 d;
    u16 v;
    s32 c;
    s32 sn;

    if (q[0xC] == 4) {
        switch (q[2]) {
        case 23:
            *(s16 *)(m + 2) -= *(s16 *)(q + 0x4A) >> 8;
            if (*(s16 *)(m + 2) < -*(s16 *)(q + 0x84)) {
                *(s16 *)(m + 2) = -*(s16 *)(q + 0x84);
            }
            *(u16 *)(a + 0x2E) = *(u16 *)(p + 0x2C) + *(u16 *)(m + 0);
            *(u16 *)(a + 0x32) = *(u16 *)(p + 0x30) + *(u16 *)(m + 2);
            *(u16 *)(a + 0x36) = *(u16 *)(p + 0x34) + *(u16 *)(m + 4);
            break;
        case 2:
        case 4:
        case 7:
            r = (rsin(*(s16 *)(p + 0xC)) * 0x6E) >> 12;
            dz = (rsin(*(s16 *)(q + 0x56)) * r) >> 12;
            dx = (rcos(*(s16 *)(q + 0x56)) * r) >> 12;
            x = *(u16 *)(p + 0x2C) - dx;
            z = *(u16 *)(p + 0x34) + dz;
            y = *(u16 *)(p + 0x30) + ((rcos(*(s16 *)(p + 0xC)) * 0x6E) >> 12);
            switch (a[0x46] >> 1) {
            case 0:
            case 1:
                c = (rcos(*(s16 *)(m + 0x18) + 0x800) * (*(s16 *)(a + 0x80) + *(s16 *)(q + 0x80))) >> 12;
                sn = (rsin(*(s16 *)(m + 0x18) + 0x800) * (*(s16 *)(a + 0x80) + *(s16 *)(q + 0x80))) >> 12;
                *(u16 *)(a + 0x2E) = x + c;
                *(u16 *)(a + 0x32) = y;
                *(u16 *)(a + 0x36) = z - sn;
                break;
            case 2:
            case 3:
                *(u16 *)(a + 0x2E) = x;
                *(u16 *)(a + 0x36) = z;
                *(u16 *)(a + 0x32) = *(u16 *)(a + 0x84) + (y + (*(u16 *)(q + 0x86) - *(u16 *)(q + 0x84)));
                break;
            }
            break;
        case 8:
            if (D_800BF870.unk0 == 0xB) {
                d = *(u16 *)(a + 0x2E) - *(u16 *)(p + 0x2C);
            } else {
                d = *(u16 *)(a + 0x36) - *(u16 *)(p + 0x34);
            }
            if (D_800BF870.unk0 == 0xC && q[3] == 0) {
                v = (u32)-(rsin(*(s16 *)(p + 0xC)) * d) >> 12;
            } else {
                v = (u32)(rsin(*(s16 *)(p + 0xC)) * d) >> 12;
            }
            *(u16 *)(a + 0x2E) = *(u16 *)(p + 0x2C) + *(u16 *)(m + 0);
            *(u16 *)(a + 0x32) = *(u16 *)(p + 0x30) + v + (u16)(*(u16 *)(a + 0x84) + 0x40);
            *(u16 *)(a + 0x36) = *(u16 *)(p + 0x34) + *(u16 *)(m + 4);
            break;
        default:
            *(u16 *)(a + 0x2E) = *(u16 *)(p + 0x2C) + *(u16 *)(m + 0);
            *(u16 *)(a + 0x32) = *(u16 *)(p + 0x30) + *(u16 *)(m + 2);
            *(u16 *)(a + 0x36) = *(u16 *)(p + 0x34) + *(u16 *)(m + 4);
            break;
        }
    } else {
        *(u16 *)(a + 0x2E) = *(u16 *)(p + 0x2C) + *(u16 *)(a + 0x60);
        *(u16 *)(a + 0x32) = *(u16 *)(p + 0x30) + *(u16 *)(m + 2);
        *(u16 *)(a + 0x36) = *(u16 *)(p + 0x34) + *(u16 *)(m + 4);
    }
}

extern u8 D_1F80027B;
extern u8 D_1F80023A;
void func_8006A080(u8 *a)
{
    u8 *m = a + 0x60;
    u8 *t = (u8 *)D_800E7E80;
    u8 *p;
    u8 k;

    switch (a[6]) {
    case 0:
        *(s16 *)(m + 6) = 3;
        if (t[0x146] != 0 && *(s16 *)(t + 0x16E) != 0) {
            t[5] = 0x19;
            t[6] = 0;
            t[7] = 0;
            a[6]++;
        }
        break;
    case 1:
        *(u16 *)(m + 8) = *(u16 *)(t + 0x56);
        *(u16 *)(m + 0xA) = *(u16 *)(t + 0x58);
        break;
    }
    p = (u8 *)D_1F800208;
    if (p != (u8 *)1) {
        if (p != 0) {
            if ((s32)p < 0) {
                if ((k = p[0xC]) == 2 && p[0] != 1) {
                    D_1F800208 = 0;
                    if (D_1F80027B != k && t[0x146] == 4) {
                        t[0x146] = 0;
                    }
                } else {
                    *(u16 *)(a + 0x2E) = *(u16 *)(p + 0x2E) + *(u16 *)(m + 0);
                    *(u16 *)(a + 0x32) = *(u16 *)(p + 0x32) + *(u16 *)(m + 2);
                    *(u16 *)(a + 0x36) = *(u16 *)(p + 0x36) + *(u16 *)(m + 4);
                }
            } else {
                func_80069CD8(a, (s32)p);
            }
        }
        func_80069858(a, 0, 1);
    }
    D_1F800200 = *(u16 *)(a + 0x2E);
    D_1F800202 = *(u16 *)(a + 0x32);
    D_1F800204 = *(u16 *)(a + 0x36);
    if (t[0x146] == 0) {
        a[0] = 2;
        a[4]++;
        t[0x79] = 0;
        D_1F80023A = 0;
    }
}

void func_8006A240(u8 *a)
{
    u8 *m = a + 0x60;

    switch (a[7]) {
    case 0:
        a[7] = 1;
        *(s16 *)(m + 6) = 3;
    case 1:
        if (a[0x2B] != 0) {
            a[6] = 8;
            *(s16 *)(a + 0x44) = 0;
            return;
        }
        *(s16 *)(a + 0x40) = 1;
        a[7]++;
        return;
    case 2:
        if (a[0x2B] != 0) {
            a[6] = 8;
            *(s16 *)(a + 0x44) = 0;
            return;
        }
        if (--*(s16 *)(a + 0x40) == 0) {
            a[7]++;
        }
        return;
    case 3:
        if (a[2] == 1) {
            *(s16 *)(a + 0x44) -= *(s16 *)(m + 0x16);
            if (*(s16 *)(a + 0x44) < 0 || a[0x2B] != 0) {
                *(s16 *)(a + 0x44) = 0;
                a[0] = 2;
                a[6]++;
            }
        } else {
            *(s16 *)(a + 0x44) -= *(s16 *)(m + 0x16);
            if (*(s16 *)(a + 0x44) < 0x46 || a[0x2B] != 0) {
                *(s16 *)(a + 0x44) = 0;
                a[0] = 2;
                a[6]++;
            }
        }
        break;
    }
}

extern u8 D_1F800252;
void func_8006A384(u8 *a)
{
    u8 *m = a + 0x60;
    u8 *t = (u8 *)D_800E7E80;
    u16 ang;
    s32 n;
    s32 i;
    s32 d;
    s32 len;
    s32 step;

    switch (a[6]) {
    case 0:
        func_80069BEC(a, 0);
        a[6]++;
        break;
    case 1:
        func_80069AE4((u16 *)a);
        if (--*(s16 *)(a + 0x40) == 0) {
            f_PlaySoundEffect(0xB, 0, 0);
            a[0] = 1;
            a[6]++;
            if (func_80069948(a) == 1) {
                a[6] = 8;
                *(s16 *)(a + 0x44) = 0;
            }
        }
        break;
    case 2:
        if (a[0x29] == 0) {
            func_80069AE4((u16 *)a);
            a[7] = 0;
            a[6]++;
            if (a[0x2B] != 0 || func_80069948(a) == 1) {
                a[6] = 8;
                *(s16 *)(a + 0x44) = 0;
            }
        } else {
            a[5] = 2;
            a[6] = 0;
            a[7] = 0;
        }
        break;
    case 3:
        func_8006A240(a);
        if (a[0x29] != 0) {
            a[5] = 2;
            a[6] = 0;
            a[7] = 0;
        }
        break;
    case 4:
        a[6]++;
        *(s16 *)(m + 0xA) -= 0x500;
    case 5:
        *(s16 *)(m + 6) = 2;
        *(s16 *)(m + 0xA) -= 0x40;
        *(s16 *)(a + 0x44) += 0x28;
        if (*(s16 *)(a + 0x44) > 0x3C) {
            *(s16 *)(a + 0x40) = 0;
            a[6]++;
        }
        break;
    case 6:
        D_1F800252 = 1;
        MEMBER_AT(s16, m, 0x12) = 1;
        *(s16 *)(m + 0x14) = f_CalculateYawFromPositionToPoint((s16 *)(a + 0x2C), MEMBER_AT(s16, MEMBER_AT(u8 *, t, 0xDC), 0x2C),
                                                               MEMBER_AT(s16, MEMBER_AT(u8 *, t, 0xDC), 0x34));
        *(s16 *)(m + 0xA) = func_80069A2C(a, *(s16 *)(*(u8 **)(t + 0xDC) + 0x2C), *(s16 *)(*(u8 **)(t + 0xDC) + 0x30),
                                          *(s16 *)(*(u8 **)(t + 0xDC) + 0x34));
        *(s16 *)(a + 0x44) += 0x32;
        if (*(s16 *)(a + 0x44) > 0x1A4) {
            *(s16 *)(a + 0x44) = 0x1A4;
        }
        if (func_80069B6C(a) == 0) {
            break;
        }
    case 7:
        a[0] = 2;
        a[4]++;
        if (t[0x146] & 1) {
            t[0x79] = 0;
        }
        *(u16 *)(a + 0x2E) = *(u16 *)(*(u8 **)(t + 0xDC) + 0x2C);
        *(u16 *)(a + 0x32) = *(u16 *)(*(u8 **)(t + 0xDC) + 0x30);
        *(u16 *)(a + 0x36) = *(u16 *)(*(u8 **)(t + 0xDC) + 0x34);
        return;
    case 8:
        D_1F800252 = 1;
        a[0] = 2;
        a[4]++;
        if (t[0x146] & 1) {
            t[0x79] = 0;
        }
        return;
    }
    if (t[0x146] == 0) {
        a[0] = 2;
        a[4] = 3;
        return;
    }
    if (a[6] < 3) {
        return;
    }
    if (a[0x46] & 1) {
        ang = 0x800 - *(u16 *)(m + 0xA);
    } else {
        ang = *(u16 *)(m + 0xA);
    }
    if (*(s16 *)(m + 0x12) == 0) {
        n = *(s16 *)(a + 0x44) / 64;
        i = 0;
        if (n > 0) {
            s32 sa;
            sa = (s16)ang;
            step = 0x40;
            do {
                *(s32 *)(a + 0x30) += (rsin(sa) * step) << 4;
                d = (rcos(sa) * step) >> 4;
                *(s32 *)(a + 0x2C) += *(s16 *)(a + 0x48) * d;
                *(s32 *)(a + 0x34) += *(s16 *)(a + 0x4C) * d;
                if (func_80069948(a) != 0) {
                    return;
                }
            } while (++i < n);
        }
        len = *(u16 *)(a + 0x44) & 0x3F;
        if (len != 0) {
            *(s32 *)(a + 0x30) += (rsin((s16)ang) * len) << 4;
            d = (rcos((s16)ang) * len) >> 4;
            *(s32 *)(a + 0x2C) += *(s16 *)(a + 0x48) * d;
            *(s32 *)(a + 0x34) += *(s16 *)(a + 0x4C) * d;
            func_80069948(a);
        }
    } else {
        *(s32 *)(a + 0x30) += (rsin((s16)ang) * *(s16 *)(a + 0x44)) << 4;
        d = (rcos((s16)ang) * *(s16 *)(a + 0x44)) >> 4;
        if (d < 0) {
            d = -d;
        }
        *(s32 *)(a + 0x2C) += (rcos(*(s16 *)(m + 0x14)) * d) >> 4;
        *(s32 *)(a + 0x34) -= (rsin(*(s16 *)(m + 0x14)) * d) >> 4;
    }
}

s32 func_8006A8C8(s32 arg0) {
    s32 temp_v0;

    temp_v0 = f_SpawnTransientEffect(0x27, 0);
    if (temp_v0 != 0) {
        M2C_FIELD(temp_v0, s32 *, 0x10) = arg0;
    }
    return temp_v0;
}

void func_8006A900(u8 *a)
{
    u8 *t = (u8 *)D_800E7E80;
    u8 *m = a + 0x60;
    s32 r;
    s32 h;
    s16 ang;
    s16 d;
    s32 k;

    switch (a[6]) {
    case 0:
        {
            s32 k = 1;
            a[6] = k;
            *(s16 *)(a + 0x40) = k;
        }
        *(s16 *)(a + 0x56) = 0;
        *(s16 *)(a + 0x54) = 0;
        *(s16 *)(a + 0x58) = 0;
    case 1:
        if (--*(s16 *)(a + 0x40) == 0) {
            if (t[0xBE] != 0) {
                f_PlaySoundEffect(0xA, 0, 0);
                *(s16 *)(a + 0x40) = 0xA;
            } else {
                f_PlaySoundEffect(9, 0, 0);
                *(s16 *)(a + 0x40) = 0x12;
            }
        }
        r = 0x37;
        if (t[0xBE] != 0) {
            r = 0x6E;
            h = 0x78;
            if (a[0x5E] == 0) {
                a[0x5E] = 1;
                func_8006A8C8((s32)a);
            }
            *(s16 *)(m + 0xA) += 0x1C0;
            ang = *(u16 *)(t + 0x56) + 0x180;
        } else {
            *(s16 *)(m + 0xA) += 0x100;
            h = 0x41;
            ang = *(u16 *)(t + 0x56) + 0x200;
        }
        d = (r * rcos(*(u16 *)(m + 0xA) &= 0xFFF)) >> 12;
        *(u16 *)(a + 0x2E) = *(u16 *)(*(u8 **)(t + 0xDC) + 0x2C) + ((rcos(ang) * d) >> 12);
        *(u16 *)(a + 0x32) = *(u16 *)(*(u8 **)(t + 0xDC) + 0x30) + ((h * rsin(*(s16 *)(m + 0xA))) >> 12);
        *(u16 *)(a + 0x36) = *(u16 *)(*(u8 **)(t + 0xDC) + 0x34) - ((rsin(ang) * d) >> 12);
        *(s16 *)(a + 0x56) = ang;
        if (a[2] != 1) {
            *(u16 *)(*(u8 **)(a + 0xC0) + 0xC) = *(u16 *)(m + 0xA);
        }
        if (t[0x144] == 2 || t[0x146] == 0) {
            a[5] = 0;
            a[4]++;
            break;
        }
        if (t[0x146] == 3) {
            *(u16 *)(a + 0x2E) = *(u16 *)(t + 0x2E);
            *(u16 *)(a + 0x32) = *(u16 *)(t + 0x32);
            *(u16 *)(a + 0x36) = *(u16 *)(t + 0x36);
            a[0x46] = t[0x14A];
            *(s16 *)(a + 0x54) = 0;
            *(s16 *)(a + 0x58) = 0;
            if (t[5] == 9) {
                *(s16 *)(a + 0x56) = *(u16 *)(t + 0x56) - 0x800;
            } else {
                *(s16 *)(a + 0x56) = *(u16 *)(t + 0x56);
            }
            *(u16 *)(m + 8) = *(u16 *)(a + 0x56);
            a[0x2A] = t[0x2A];
            a[5] = k = 1;
            func_80069BEC(a, 1);
            *(s16 *)(*(u8 **)(a + 0xC0) + 0xC) = 0;
            a[6] = k;
            func_80069688(a);
        }
        break;
    }
}

void func_8006ABF4(u8 *a)
{
    a[0xB] = 0x10;
    a[0xD] = 0;
    *(s16 *)(a + 0x5C) = 0;
    *(s8 **)(a + 0x3C) = D_800ECF58[0];
    f_StartActorTimedFrameSequence(a, D_80017334, 0x36);
}

void func_8006AC38(u8 *a)
{
    a[0xB] = 0x10;
    a[0xD] = 0;
    *(s16 *)(a + 0x5C) = 0;
    *(s8 **)(a + 0x3C) = D_800ECF58[0];
    f_StartActorTimedFrameSequence(a, D_80017334, 0x13C);
}

void func_8006AC7C(void *actor, s32 i)
{
    f_InitializeSinglePartActorModel(actor, 1, D_800A4A94[i]);
}

extern u8 D_800E7E82;
void func_8006ACAC(u8 *a)
{
    u8 *sub = a + 0x60;

    switch (a[2]) {
    case 1:
        func_8006ABF4(a);
        *(s16 *)(a + 0x80) = 0x32;
        *(s16 *)(a + 0x82) = 0x64;
        *(s16 *)(a + 0x86) = 0x64;
        *(s16 *)(a + 0x84) = 0x32;
        a[8] = 0xF6;
        break;
    case 2:
    case 3:
        func_8006AC7C(a, a[2]);
        a[0xB] = 1;
        *(s16 *)(a + 0x80) = 0x32;
        *(s16 *)(a + 0x82) = 0x64;
        *(s16 *)(a + 0x84) = 0x32;
        *(s16 *)(a + 0x86) = 0x64;
        break;
    case 4:
    case 5:
    case 6:
        func_8006AC7C(a, a[2]);
        a[0xB] = 0;
        *(s16 *)(a + 0x80) = 0x32;
        *(s16 *)(a + 0x82) = 0x64;
        *(s16 *)(a + 0x84) = 0x32;
        *(s16 *)(a + 0x86) = 0x64;
        break;
    case 7:
    case 8:
    case 9:
        func_8006AC7C(a, a[2]);
        *(s16 *)(a + 0x80) = 0x64;
        *(s16 *)(a + 0x82) = 0xC8;
        *(s16 *)(a + 0x84) = 0x5A;
        a[0xB] = 0;
        *(s16 *)(a + 0x86) = 0x82;
        break;
    case 11:
        func_8006AC38(a);
        *(s16 *)(a + 0x80) = 0x32;
        *(s16 *)(a + 0x82) = 0x64;
        *(s16 *)(a + 0x84) = 0x32;
        *(s16 *)(a + 0x86) = 0x64;
        break;
    }
    *(s16 *)(sub + 0x12) = 0;
    a[0x29] = 0;
    *(s16 *)(a + 0x54) = 0;
    *(s16 *)(a + 0x58) = 0;
    if (a[2] == 6) {
        *(s16 *)(a + 0xB8) = 0x1800;
        *(s16 *)(a + 0xBA) = 0x1800;
        *(s16 *)(a + 0xBC) = 0x1800;
    } else {
        *(s16 *)(a + 0xB8) = 0x1000;
        *(s16 *)(a + 0xBA) = 0x1000;
        *(s16 *)(a + 0xBC) = 0x1000;
    }
    a[1] = 1;
    a[0x2B] = 0;
    *(s16 *)(a + 0x44) = 0;
    a[0x5E] = 0;
    if (D_800E7E82 == 0) {
        func_80069858(a, 0, 1);
    }
}

void func_8006AE28(u8 *a)
{
    u8 *m = a + 0x60;
    u8 s;

    switch (a[4]) {
    case 0:
if (a[2] == 1) {
            a[0x5F] = 0x20;
        } else {
            a[0x5F] = 0x10;
        }
        func_8006ACAC(a);
        *(u16 *)(m + 8) = *(u16 *)(a + 0x56);
        a[4]++;
        *(s16 *)(m + 6) = 0;
        *(s16 *)(m + 0xA) = 0;
        *(s16 *)(m + 0xC) = 0;
        a[0] = 2;
        if (a[3] == 0) {
            a[5] = 1;
            func_80069688(a);
        } else {
            ((u8 *(*)())f_SpawnLinkedActorTrailEffect)(a, a[2] - 1);
        }
    case 1:
        s = a[5];
        switch (s) {
        case 0:
            func_8006A900(a);
            if (a[2] != 1) {
                f_UpdateActorUnscaledModelTransforms((s32)a);
            }
            break;
        case 1:
            func_8006A384(a);
            if (a[2] != s) {
                f_UpdateActorUnscaledModelTransforms((s32)a);
            }
            break;
        case 2:
            func_8006A080(a);
            f_UpdateActorUnscaledModelTransforms((s32)a);
            break;
        }
        a[1] = 1;
        break;
    case 2:
        a[4]++;
        break;
    case 3:
        func_8007AB44(a);
        break;
    }
}

void func_8006AFC4(u8 *a)
{
    u8 *b = *(u8 **)(a + 0x10);

    if (b != NULL && b[0] == 1 && b[4] == b[0]) {
        *(u16 *)(b + 0x2E) = *(u16 *)(a + 0x2E);
        *(u16 *)(b + 0x32) = *(u16 *)(a + 0x32);
        *(u16 *)(b + 0x36) = *(u16 *)(a + 0x36);
    }
}

void func_8006B020(u8 *a, s32 mode)
{
    s32 k = 0;

    switch (mode) {
    case 0:
        if (a[2] == 6) {
            k = 1;
        }
        D_1F8000C8[0] = 0;
        D_1F8000C8[1] = 0;
        D_1F8000C8[2] = -0x10;
        break;
    case 2:
        D_1F8000C8[0] = 0;
        D_1F8000C8[1] = 0;
        D_1F8000C8[2] = -0x40;
        break;
    case 1:
        D_1F8000C8[0] = 0x96;
        D_1F8000C8[1] = 0;
        D_1F8000C8[2] = 0;
        break;
    }
    func_80051614(a, D_1F8000C8, 7, k);
}

void func_8006B0D8(u8 *a)
{
    u8 *b;
    u8 s;
    u8 t;

    if (a[2] != 4) {
        s = a[0];
        b = a + 0x60;
        if (s == 2) {
            a[0x2B] = s;
            a[1] = 0;
            a[4] = s;
            t = D_1F800231;
            *(s16 *)(b + 0xE) = 1;
            D_1F800231 = t - 1;
        }
    }
}

void func_8006B124(u8 *a, s32 flag)
{
    u8 *m = a + 0x60;

    switch ((a[0x46] >> 1) & 3) {
    case 0:
    case 1:
        *(s16 *)(m + 0xA) = 0;
        break;
    case 2:
        *(s16 *)(m + 0xA) = 0xE40;
        break;
    case 3:
        *(s16 *)(m + 0xA) = 0xC20;
        break;
    }
    a[0x46] &= 7;
    f_PlaySoundEffect(0x22, 0, 0);
    func_80069634(a);
    func_8006B020(a, 0);
    if (flag == 0) {
        ((u8 *(*)())f_SpawnLinkedActorTrailEffect)(a, a[2] - 1);
    }
    {
        u16 r = *(u16 *)(m + 8);

        *(s16 *)(a + 0x42) = 2;
        *(u16 *)(a + 0x56) = r;
    }
}

void func_8006B1FC(u8 *a)
{
    u8 *m = a + 0x60;

    switch (a[7]) {
    case 0:
        a[7] = 1;
    case 1:
        if (a[0x2B] >= 2) {
            *(u16 *)(a + 0x44) = 0;
            a[7] = 3;
            return;
        }
        a[7]++;
        break;
    case 2:
        if (a[0x2B] == 1) {
            *(u16 *)(a + 0x42) = 2;
            a[0x2B] = 0;
        } else if (a[0x2B] >= 2) {
            *(u16 *)(a + 0x44) = 0;
        }
        a[7]++;
        break;
    case 3:
        *(u16 *)(a + 0x44) -= *(u16 *)(m + 0x16);
        *(u16 *)(m + 0xA) -= 0x80;
        if (a[0x2B] == 1) {
            if (--*(s16 *)(a + 0x42) == 0) {
                a[0x2B] = 0;
                *(u16 *)(a + 0x42) = 2;
            }
        }
        if (*(s16 *)(a + 0x44) < 0 || a[0x2B] >= 2) {
            a[0x2B] = 2;
            *(u16 *)(a + 0x44) = 0;
            a[7] = 0;
            a[6]++;
            switch ((a[0x46] >> 1) & 3) {
            case 0:
            case 1:
                *(u16 *)(m + 0xA) = 0xC00;
                break;
            case 2:
                *(u16 *)(m + 0xA) = 0x980;
                break;
            case 3:
                *(u16 *)(m + 0xA) = 0x700;
                break;
            }
        }
        break;
    }
}

s32 func_8006B390(u8 *a)
{
    s32 k;

    if (func_80069858(a, 0, 0) != 0) {
        k = a[2];
        if (k == 4) {
            if (a[0x2B] != 0) {
                return 1;
            }
        } else if (k >= 4) {
            if (k < 7) {
                f_PlaySoundEffect(0x2C, 0, 0);
                f_PlaySoundEffect(0x2D, 0, 0);
                f_SpawnEffectTemplateInstances(*(void **)(*(u8 **)(a + 0xC0) + 0x40), a + 0x2C, 0x400, 0x15);
                f_PlaySoundEffect(0xC, 0, 0);
            }
        }
        if (*(s16 *)(a + 0x44) > 0) {
            *(s16 *)(a + 0x44) = 0;
        }
        f_PlaySoundEffect(0x2F, 0, 0);
        f_SpawnImpactTransientEffect(2, a + 0x2C, a[0x5E], (u16 *)(a + 0x68));
        a[0] = 2;
        a[0x2B] = 2;
        func_8006B0D8(a);
        return 1;
    }
    return 0;
}

s16 func_80069A2C(u8 *a, s16 x, s16 y, s16 z);
s32 f_StepWrappedAngleToward(s32 a, s32 b, s32 step);
void func_8006B494(u8 *a)
{
    u8 *m = a + 0x60;
    u8 *t = (u8 *)D_800E7E80;
    u16 ang;
    s32 sp;
    s32 n;
    s32 i;
    s32 d;
    s32 len;
    s32 step;

    switch (a[6]) {
    case 0:
        func_8006B124(a, 0);
        a[6]++;
        break;
    case 1:
        func_8006B020(a, 0);
        if (--*(s16 *)(a + 0x40) == 0) {
            f_PlaySoundEffect(0xB, 0, 0);
            a[0] = 1;
            *(s16 *)(a + 0x54) = 0;
            a[6]++;
            if (func_8006B390(a) != 0 && a[2] == 4) {
                a[0x2B] = 2;
                a[4] = 2;
            }
        }
        break;
    case 2:
        a[7] = 0;
        a[6]++;
        *(s16 *)(m + 6) = 0;
        if (a[0x2B] >= 2) {
            *(s16 *)(a + 0x44) = 0;
        }
        break;
    case 3:
        func_8006B1FC(a);
        func_8006B0D8(a);
        break;
    case 4:
        a[6]++;
        *(s16 *)(m + 0x10) = 0x40;
    case 5:
        if (a[0x2B] == 1) {
            if (--*(s16 *)(a + 0x42) == 0) {
                a[0x2B] = 0;
                *(s16 *)(a + 0x42) = 2;
            }
        }
        *(s16 *)(a + 0x44) += 0x12;
        if (*(s16 *)(a + 0x44) > 0x50) {
            a[0x2B] = 2;
            *(s16 *)(a + 0x40) = 0;
            a[6]++;
        }
        func_8006B0D8(a);
        *(s16 *)(m + 0xA) = f_StepWrappedAngleToward(
            ((s16 (*)())func_80069A2C)(a, *(s32 *)(*(u8 **)(t + 0xDC) + 0x2C), *(s32 *)(*(u8 **)(t + 0xDC) + 0x30),
                               *(s32 *)(*(u8 **)(t + 0xDC) + 0x34)),
            *(s16 *)(m + 0xA), *(s16 *)(m + 0x10));
        *(s16 *)(m + 0x10) += *(s16 *)(a + 0x44);
        break;
    case 6:
        *(s16 *)(m + 0xA) = ((s16 (*)())func_80069A2C)(a, *(s32 *)(*(u8 **)(t + 0xDC) + 0x2C), *(s32 *)(*(u8 **)(t + 0xDC) + 0x30),
                                          *(s32 *)(*(u8 **)(t + 0xDC) + 0x34));
        *(s16 *)(m + 0x12) = 1;
        *(s16 *)(m + 0x14) = f_CalculateYawFromPositionToPoint((s16 *)(a + 0x2C), *(s16 *)(*(u8 **)(t + 0xDC) + 0x2C),
                                                               *(s16 *)(*(u8 **)(t + 0xDC) + 0x34));
        *(s16 *)(a + 0x44) += 0x32;
        if (*(s16 *)(a + 0x44) > 0x1A4) {
            *(s16 *)(a + 0x44) = 0x1A4;
        }
        if (func_80069B6C(a) == 0) {
            break;
        }
    case 7:
        a[1] = 0;
        a[0] = 2;
        a[4]++;
        *(s16 *)(m + 0xE) = 1;
        *(u16 *)(a + 0x2E) = *(u16 *)(t + 0x2E);
        *(u16 *)(a + 0x32) = *(u16 *)(t + 0x32);
        D_1F800231--;
        *(u16 *)(a + 0x36) = *(u16 *)(t + 0x36);
        return;
    }
    if (a[6] < 3) {
        return;
    }
    *(u16 *)(a + 0x58) += 0x280;
    if (a[0x46] & 1) {
        ang = 0x800 - *(u16 *)(m + 0xA);
    } else {
        ang = *(u16 *)(m + 0xA);
    }
    sp = rsin((s16)ang) * 0x50 / 100;
    if (*(s16 *)(m + 0x12) == 0) {
        n = *(s16 *)(a + 0x44) / 64;
        i = 0;
        if (n > 0) {
            step = 0x40;
            do {
                *(s32 *)(a + 0x30) += sp << 10;
                d = (rcos((s16)ang) * step) >> 4;
                *(s32 *)(a + 0x2C) += *(s16 *)(a + 0x48) * d;
                *(s32 *)(a + 0x34) += *(s16 *)(a + 0x4C) * d;
                if (func_8006B390(a) != 0) {
                    return;
                }
            } while (++i < n);
        }
        len = *(u16 *)(a + 0x44) & 0x3F;
        if (len != 0) {
            *(s32 *)(a + 0x30) += (sp * len) << 4;
            d = (rcos((s16)ang) * len) >> 4;
            *(s32 *)(a + 0x2C) += *(s16 *)(a + 0x48) * d;
            *(s32 *)(a + 0x34) += *(s16 *)(a + 0x4C) * d;
            func_8006B390(a);
        }
    } else {
        *(s32 *)(a + 0x30) += (sp * *(s16 *)(a + 0x44)) << 4;
        d = (rcos((s16)ang) * *(s16 *)(a + 0x44)) >> 4;
        if (d < 0) {
            d = -d;
        }
        *(s32 *)(a + 0x2C) += (rcos(*(s16 *)(m + 0x14)) * d) >> 4;
        *(s32 *)(a + 0x34) -= (rsin(*(s16 *)(m + 0x14)) * d) >> 4;
    }
}

void func_8006B9DC(u8 *a)
{
    u8 *t = (u8 *)D_800E7E80;
    u8 *m = a + 0x60;
    u8 kind;

    switch (a[6]) {
    case 0:
        {
        s32 k = 1;
        a[6] = k;
        *(s16 *)(a + 0x40) = k;
        }
    case 1:
        if (--*(s16 *)(a + 0x40) == 0) {
            if (t[0xBE] != 0) {
                f_PlaySoundEffect(0xA, 0, 0);
                *(s16 *)(a + 0x40) = 0xA;
            } else {
                f_PlaySoundEffect(9, 0, 0);
                *(s16 *)(a + 0x40) = 0x12;
            }
        }
        if (t[0xBE] != 0 && a[0x5E] == 0) {
            a[0x5E] = 1;
            func_8006A8C8((s32)a);
        }
        if (t[0x144] == 2 || t[0x146] == 0) {
            a[5] = 0;
            a[4]++;
        } else if (t[0x146] == 3) {
            a[0x46] = t[0x14A];
            if (t[5] == 9) {
                *(u16 *)(m + 8) = *(u16 *)(t + 0x56) - 0x800;
            } else {
                *(u16 *)(m + 8) = *(u16 *)(t + 0x56);
            }
            kind = t[0x2A];
            a[5] = 1;
            a[0x2A] = kind;
            func_8006B124(a, 1);
            func_80069688(a);
            a[6] = 1;
        }
        func_8006B020(a, 0);
        break;
    }
}

void func_8006BB6C(u8 *a)
{
    u8 *m = a + 0x60;

    switch (a[4]) {
    case 0:
        a[0x5F] = 0x40;
        func_8006ACAC(a);
        *(s32 *)(a + 0x10) = 0;
        a[4]++;
        *(u16 *)(m + 8) = *(u16 *)(a + 0x56);
        *(u16 *)(a + 0x56) = 0;
        *(s16 *)(m + 0xA) = 0;
        *(s16 *)(m + 6) = 1;
        *(s16 *)(m + 0xE) = 0;
        a[0] = 2;
        *(s16 *)(a + 0x54) = 0x400;
        a[0x2B] = 0;
        if (a[3] == 0) {
            a[5] = 1;
            func_80069688(a);
        } else {
            ((u8 *(*)())f_SpawnLinkedActorTrailEffect)(a, a[2] - 1);
        }
    case 1:
        a[1] = 1;
        switch (a[5]) {
        case 0:
            func_8006B9DC(a);
            break;
        case 1:
            func_8006B494(a);
            if (*(s16 *)(m + 6) == 0) {
                if (a[2] == 6) {
                    f_UpdateActorScaledModelTransforms(a);
                } else {
                    f_UpdateActorUnscaledModelTransforms((s32)a);
                }
            }
            func_8006AFC4(a);
            break;
        }
        break;
    case 2:
        a[1] = 0;
        a[4]++;
        break;
    case 3:
        if (*(s16 *)(m + 0xE) == 0) {
            D_1F800231--;
        }
        func_8007AB44(a);
        break;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006BD20);

void func_8006BDF0(u8 *a, s32 quiet)
{
    u8 *t;
    u8 *p;

    a[0x46] &= 1;
    t = D_800E7E80_f78d;
    p = a + 0x60;
    if (t[5] == 9) {
        *(u16 *)(p + 8) = *(u16 *)(t + 0x56) - 0x800;
    } else {
        *(u16 *)(p + 8) = *(u16 *)(t + 0x56);
    }
    *(u16 *)(p + 0xA) = 0x400;
    f_PlaySoundEffect(0x22, 0, 0);
    if (quiet == 0) {
        ((void (*)(u8 *, s32))f_SpawnLinkedActorTrailEffect)(a, a[2] - 1);
    }
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006BE88);

typedef struct { u8 pad[0x30]; s32 y; } ActorY_C0C4;
extern ActorY_C0C4 D_800E7E80_1c87;
void func_8006C0C4(u8 *a)
{
    u8 *g = D_800E7E80_f78d;
    u32 s;
    s32 n7;

    switch (a[6]) {
    case 0:
        func_8006BDF0(a, 0);
        a[6]++;
        break;
    case 1:
        a[6]++;
        if (a[0x5E] == 0) {
            f_PlaySoundEffect(0xB, -2, 0);
            *(u16 *)(a + 0x40) = 4;
        } else {
            f_PlaySoundEffect(0xB, -4, 0);
            *(u16 *)(a + 0x40) = 2;
        }
        break;
    case 2:
        n7 = 7;
        if (--*(s16 *)(a + 0x40) == 0) {
            *(s16 *)(a + 0x80) = 0x64;
            *(s16 *)(a + 0x82) = 0xC8;
            *(s16 *)(a + 0x84) = 0xA0;
            *(s16 *)(a + 0x86) = 0x104;
            a[0] = 1;
            a[6]++;
            if (a[0x5E] == 0) {
                *(u16 *)(a + 0x40) = 8;
            } else {
                *(u16 *)(a + 0x40) = n7;
            }
            *(u16 *)(a + 0x42) = 3;
            func_8006BD20(a);
        }
        break;
    case 3:
        if (a[0x2B] == 1) {
            if (--*(s16 *)(a + 0x42) == 0) {
                *(u16 *)(a + 0x42) = 3;
                a[0x2B] = 0;
            }
        }
        func_8006BE88(a);
        s = a[0x2B];
        if (s >= 2) {
            if (s == 2) {
                g[0x79] = s;
            }
            *(u16 *)(a + 0x40) = 10;
            *(u16 *)(a + 0x42) = 0x155;
            a[6]++;
        } else if (--*(s16 *)(a + 0x40) == 0) {
            D_800E807E = 0;
            a[0] = 2;
            a[4] = 3;
            if (g[0x146] & 1) {
                g[0x79] = 0;
            }
        }
        break;
    case 4:
        if (*(s16 *)(a + 0x42) < 0x800) {
            D_800E7E80_1c87.y -= rsin(*(s16 *)(a + 0x42)) << 8;
            *(u16 *)(a + 0x42) += 0x155;
        }
        if (--*(s16 *)(a + 0x40) == 0) {
            D_800E807E = 0;
            a[0] = 2;
            a[4] = 3;
            if (g[0x146] & 1) {
                g[0x79] = 0;
            }
        }
        break;
    }
    if (g[0x146] == 0) {
        D_800E807E = 0;
        a[0] = 2;
        a[0x2B] = 2;
        a[4] = 2;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006C328);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006C478);

void func_8002C138();
void func_8006C59C(void *arg0) {
    M2C_FIELD(arg0, s16 *, 0x44) = 0x1000;
    M2C_FIELD(arg0, s16 *, 0x80) = 0x3C;
    M2C_FIELD(arg0, s16 *, 0x82) = 0x78;
    M2C_FIELD(arg0, s16 *, 0x84) = 0x64;
    M2C_FIELD(arg0, s16 *, 0x86) = 0xC8;
    M2C_FIELD(arg0, s8 *, 0) = 1;
    M2C_FIELD(arg0, s16 *, 0x40) = 0xD;
    M2C_FIELD(arg0, s8 *, 0xB) = 0x20;
    M2C_FIELD(arg0, s8 *, 0x5F) = 0;
    M2C_FIELD(arg0, s8 *, 0x2B) = 0;
    M2C_FIELD(arg0, s16 *, 0x42) = 0;
    M2C_FIELD(arg0, M2C_UNK **, 0x18) = &func_8002C138;
    M2C_FIELD(arg0, s16 *, 0x60) = 0;
    M2C_FIELD(arg0, u8 *, 4) = (u8) (M2C_FIELD(arg0, u8 *, 4) + 1);
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006C608);

void func_8006C77C(void)
{
    if (D_800BF870.unk0 != 3) {
        D_800A4AF8[D_800BF870.unk0]();
    }
}

void func_8006C7C4(void)
{
    if (D_800BF870.unk0 != 3) {
        D_800A4B50[D_800BF870.unk0]();
    }
}

typedef struct CamClampY { u8 pad0[0x12]; s16 y; } CamClampY;
extern CamClampY D_1F8000D0_8dc8;
void func_8006C80C(void)
{
    CamClampY *c;


    switch (D_800BF870.unk0) {
    case 1:
        c = &D_1F8000D0_8dc8;
        if (c->y < -0x279C) {
            c->y = -0x279C;
        }
        break;
    case 4:
        if (D_800BF870.pad1[0] == 7) {
            if ((s16)D_800E7EB6 < 0x1A90) {
                
                if (D_1F8000D0_8dc8.y > -0x1C84) {
                    D_1F8000D0_8dc8.y = -0x1C84;
                } else if (D_1F8000D0_8dc8.y > -0x1964) {
                    D_1F8000D0_8dc8.y = -0x1964;
                }
            }
        } else {
            c = &D_1F8000D0_8dc8;
            if (c->y >= -0x19C7) {
                c->y = -0x19C8;
            }
        }
        break;
    case 6:
        if (D_1F800207_9c67 == 0xE) {
            c = &D_1F8000D0_8dc8;
            if (c->y < -0x1C20) {
                c->y = -0x1C20;
            }
        } else {
            c = &D_1F8000D0_8dc8;
            if (c->y < -0x23F0) {
                c->y = -0x23F0;
            }
        }
        break;
    case 10:
        c = &D_1F8000D0_8dc8;
        if (c->y < -0x870) {
            c->y = -0x870;
        }
        break;
    case 13:
        c = &D_1F8000D0_8dc8;
        if (c->y >= -0x577) {
            c->y = -0x578;
        }
        break;
    }
}

extern u16 D_1F8000D6;
void func_8006C988(u8 *a)
{
    s32 r;

    switch (a[0x76]) {
    case 0:
        break;
    case 1:
        *(u16 *)(a + 0x86) = D_1F8000D0_fb20[1];
        *(u16 *)(a + 0x88) = D_1F8000D0_fb20[3];
        *(u16 *)(a + 0x8A) = D_1F8000D0_fb20[5];
        a[0x76] = 2;
        break;
    case 2:
        r = rand();
        D_1F8000D0_fb20[1] = *(s16 *)(a + 0x86) - 0x10 + (r & 0x1F);
        r = rand();
        D_1F8000D0_fb20[5] = *(s16 *)(a + 0x8A) - 0x10 + (r & 0x1F);
        r = rand();
        D_1F8000D0_fb20[3] = *(s16 *)(a + 0x88) - 8 + (r & 0xF);
        f_StartControllerVibration(0, 0, 0x81, 2);
        break;
    case 3:
        D_1F8000D0_fb20[1] = *(u16 *)(a + 0x86);
        D_1F8000D0_fb20[3] = *(u16 *)(a + 0x88);
        D_1F8000D0_fb20[5] = *(u16 *)(a + 0x8A);
        a[0x76] = 0;
        break;
    case 4:
        *(u16 *)(a + 0x88) = D_1F8000D6;
        a[0x76] = 5;
        break;
    case 5:
        r = rand();
        D_1F8000D6 = *(s16 *)(a + 0x88) - 0x20 + (r & 0x3F);
        f_StartControllerVibration(0, 0, 0xF1, 2);
        break;
    case 6:
        *(u16 *)(a + 0x88) = D_1F8000D6;
        a[0x76] = 7;
    case 7:
        if (a[0x64] == 0) {
            r = rand();
            D_1F8000D6 = *(s16 *)(a + 0x88) - 0x20 + (r & 0x3F);
            f_StartControllerVibration(0, 0, 0x81, 2);
        }
        a[0x76] = 0;
        break;
    case 8:
        *(u16 *)(a + 0x88) = D_1F8000D6;
        a[0x76] = 9;
    case 9:
        if (a[0x64] == 0) {
            r = rand();
            D_1F8000D6 = *(s16 *)(a + 0x88) - 0x10 + (r & 0x1F);
            f_StartControllerVibration(0, 0, 0x81, 2);
        }
        a[0x76] = 0;
        break;
    }
}

void f_SetCameraFocusPosition(u16 *pos)
{
    CameraState *cam = &g_CameraState;

    cam->focusX = pos[1];
    cam->focusY = pos[3];
    cam->focusZ = pos[5];
}

void f_SetCameraTransform(u8 *cam, u16 *t)
{
    CameraTarget2 *c = &D_1F8000D0_d63a;

    c->x = t[0];
    c->y = t[1];
    c->z = t[2];
    *(u16 *)(cam + 0x3A) = t[3];
    *(u16 *)(cam + 0x3E) = t[4];
    *(u16 *)(cam + 0x42) = t[5];
}

INCLUDE_ASM("asm/main/nonmatchings/main", f_StartCameraTransformInterpolation);

s32 f_UpdateCameraTransformInterpolation(u8 *c)
{
    if (*(s16 *)(c + 0x84) == 0) {
        return 1;
    }
    *(s16 *)(c + 0x84) -= 1;
    D_1F8000D0_42d8[0] += *(s16 *)(c + 0x78) << 9;
    D_1F8000D0_42d8[1] += *(s16 *)(c + 0x7A) << 9;
    D_1F8000D0_42d8[2] += *(s16 *)(c + 0x7C) << 9;
    *(s32 *)(c + 0x38) += *(s16 *)(c + 0x7E) << 9;
    *(s32 *)(c + 0x3C) += *(s16 *)(c + 0x80) << 9;
    *(s32 *)(c + 0x40) += *(s16 *)(c + 0x82) << 9;
    return 0;
}

s16 f_ClampSignedCameraDelta(s16 arg0, s16 arg1) {
    s16 var_v1;

    var_v1 = arg0;
    if (arg0 >= 0) {
        if (arg1 < arg0) {
            var_v1 = arg1;
        }
    } else if (arg0 < -arg1) {
        var_v1 = -arg1;
    }
    return var_v1;
}

s32 f_ApproachFixedPosition3D(u8 *a, u8 *b, s32 lim)
{
    s32 n = 0;
    u16 t;
    u16 d;

    t = *(u16 *)(b + 2);
    d = t - *(u16 *)(a + 2);
    if ((u16)(d + 10) >= 21) {
        if (lim != 0) {
            d = f_ClampSignedCameraDelta(d, lim);
        }
        *(s32 *)(a + 0) += (d << 16) >> 3;
    } else {
        *(u16 *)(a + 2) = t;
        n = 1;
    }
    t = *(u16 *)(b + 6);
    d = t - *(u16 *)(a + 6);
    if ((u16)(d + 10) >= 21) {
        if (lim != 0) {
            d = f_ClampSignedCameraDelta(d, lim);
        }
        *(s32 *)(a + 4) += (d << 16) >> 3;
    } else {
        *(u16 *)(a + 6) = t;
        n++;
    }
    t = *(u16 *)(b + 0xA);
    d = t - *(u16 *)(a + 0xA);
    if ((u16)(d + 10) >= 21) {
        if (lim != 0) {
            d = f_ClampSignedCameraDelta(d, lim);
        }
        *(s32 *)(a + 8) += (d << 16) >> 3;
    } else {
        *(u16 *)(a + 0xA) = t;
        n++;
    }
    return n == 3;
}

INCLUDE_ASM("asm/main/nonmatchings/main", f_RebuildCameraViewTransform);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006D2AC);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006D654);

void f_SetCameraPositionHorizontal(s32 unused, s32 *pos)
{
    CameraTarget *c = &D_1F8000D0;

    c->x = pos[0];
    c->z = pos[2];
}

extern s8 D_1F8000E0[];
void f_SetCameraPositionVertical(s32 arg0, void *arg1) {
    *((s32 *)D_1F8000E0) = M2C_FIELD(arg1, s32 *, 4);
}

typedef struct { u8 pad[0xC]; s32 x; s32 y; s32 z; } CamH_DA30;
extern CamH_DA30 D_1F8000D0_8d1c;
s32 f_ApproachCameraPositionHorizontal(void *unused, u8 *t)
{
    CamH_DA30 *c;
    s16 d;
    s32 r;

    c = &D_1F8000D0_8d1c;
    d = *(u16 *)(t + 2) - *(u16 *)((u8 *)c + 0xE);
    r = 1;
    if ((u16)(d + 10) >= 21) {
        c->x += (f_ClampSignedCameraDelta(d, 0x1800) << 16) >> 3;
        r = 0;
    } else {
        c->x = *(s32 *)(t + 0);
    }
    c = &D_1F8000D0_8d1c;
    d = *(u16 *)(t + 0xA) - *(u16 *)((u8 *)c + 0x16);
    if ((u16)(d + 10) >= 21) {
        c->z += (f_ClampSignedCameraDelta(d, 0x1800) << 16) >> 3;
        r = 0;
    } else {
        r &= 1;
        c->z = *(s32 *)(t + 8);
    }
    return r;
}

s32 f_ApproachCameraPositionVertical(void *unused, u8 *t)
{
    Cam_DA30 *c = &D_1F8000D0_d44f;
    s16 d = *(u16 *)(t + 6) - *(u16 *)((u8 *)c + 0x12);
    s32 r = 1;

    if ((u16)(d + 10) >= 21) {
        c->y += (f_ClampSignedCameraDelta(d, 0x1600) << 16) >> 3;
        r = 0;
    } else {
        c->y = *(s32 *)(t + 4);
    }
    return r;
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006DAD8);

typedef struct { s32 x; s32 y; s32 z; s16 pad; s16 bx; s16 pad10[3]; s16 bz; } Cam_DC38;
extern Cam_DC38 D_1F8000D0_6683;
void func_8006DC38(u8 *a)
{
    s32 r = (rcos(*(s16 *)(a + 0x6E)) * *(s16 *)(a + 0x6C)) >> 12;
    s32 x = D_1F8000D0_6683.bx + ((rcos(*(s16 *)(a + 0x70)) * r) >> 12);
    s32 z = (rsin(*(s16 *)(a + 0x70)) * r) >> 12;

    D_1F8000D0_6683.x = x << 16;
    D_1F8000D0_6683.z = (D_1F8000D0_6683.bz - z) << 16;
    a[0x66] |= 1;
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006DCF4);

void func_8006DEF0(u8 *a)
{
    s32 s = (rsin(*(s16 *)(a + 0x6E)) * *(s16 *)(a + 0x6C)) >> 12;
    u8 *c = D_1F8000D0_b839;
    s32 d = *(u16 *)(c + 6) + s - *(u16 *)(c + 0x12);

    if ((u16)(d + 10) >= 0x15) {
        *(s32 *)(c + 4) -= (d << 16) >> 3;
    } else {
        *(u16 *)(c + 6) = *(u16 *)(c + 0x12) - s;
        a[0x66] |= 2;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006DF88);

void func_8006E010(u8 *a)
{
    u8 *g = D_800E7E80_f78d;
    s16 t;

    if (g[0x164] == 3) {
        switch (g[0x168]) {
        case 0:
        case 1:
            t = 0;
            break;
        case 2:
            t = -0x80;
            break;
        case 3:
            t = -0x100;
            break;
        case 4:
        default:
            t = -0x180;
            break;
        }
        if (t < *(s32 *)(a + 0x34)) {
            *(s32 *)(a + 0x34) -= 8;
            if (t >= *(s32 *)(a + 0x34)) {
                *(s32 *)(a + 0x34) = t;
            }
        } else {
            *(s32 *)(a + 0x34) += 8;
            if (*(s32 *)(a + 0x34) >= t) {
                *(s32 *)(a + 0x34) = t;
            }
        }
    } else if (*(s32 *)(a + 0x34) > 0) {
        *(s32 *)(a + 0x34) -= 8;
        if (*(s32 *)(a + 0x34) <= 0) {
            *(s32 *)(a + 0x34) = 0;
        }
    } else {
        *(s32 *)(a + 0x34) += 8;
        if (*(s32 *)(a + 0x34) >= 0) {
            *(s32 *)(a + 0x34) = 0;
        }
    }
}

void func_8006C80C(void);
void func_8006E0F0(u8 *c)
{
    u8 *t = (u8 *)D_800E7E80;

    func_8006D2AC(c);
    f_ApproachCameraPositionHorizontal(c, c + 8);
    func_8006D654(c);
    f_ApproachCameraPositionVertical(c, c + 8);
    ((void (*)(u8 *))func_8006C80C)(c);
    if (c[0x76] == 0 && t[0x17A] == 0) {
        func_8006DCF4(c);
    }
    f_RebuildCameraViewTransform(c);
    if (c[0x77] == 0) {
        func_8006E010(c);
    }
    D_1F8000D0_42d8[17] -= *(s32 *)(c + 0x28) + *(s32 *)(c + 0x34);
}

void f_SetCameraMode(u8 mode)
{
    CameraState *c = &g_CameraState;
    u8 old = c->mode;

    c->mode = mode;
    c->unk4 = 0;
    c->unk5 = 0;
    c->unk6 = 0;
    c->previousMode = old;
}

void f_RestorePreviousCameraMode(void)
{
    s8 *p = D_800E7E80;
    CameraState *c = &g_CameraState;

    if ((u8)p[2] == 1) {
        c->mode = 0;
        *(s32 *)((u8 *)c + 0xC) = *(s32 *)(p + 0x30);
        return;
    }
    *(s32 *)((u8 *)c + 0xC) = *(s32 *)(p + 0x30);
    c->mode = c->previousMode;
}

void func_8006E228(void *arg0, M2C_UNK arg1) {
    ((s32 (*)())f_ApproachCameraPositionHorizontal)();
    f_ApproachCameraPositionVertical(arg0, arg1);
    M2C_FIELD(arg0, u16 *, 0xE) = (u16) *(u16 *)0x1F8000E2;
    if (M2C_FIELD(arg0, u8 *, 0x76) == 0) {
        func_8006DAD8(arg0);
        func_8006DEF0(arg0);
    }
    f_RebuildCameraViewTransform(arg0);
}

void func_8006E294(void *arg0, M2C_UNK arg1) {
    f_SetCameraPositionHorizontal(arg0, arg1);
    f_SetCameraPositionVertical(arg0, arg1);
    if (M2C_FIELD(arg0, u8 *, 0x76) == 0) {
        func_8006DC38(arg0);
        func_8006DF88(arg0, 1);
    }
    f_RebuildCameraViewTransform(arg0);
}

void func_8006E2FC(void *arg0, M2C_UNK arg1) {
    f_SetCameraPositionHorizontal(arg0, arg1);
    f_SetCameraPositionVertical(arg0, arg1);
    if (M2C_FIELD(arg0, u8 *, 0x76) == 0) {
        func_8006DAD8(arg0);
        func_8006DEF0(arg0);
    }
    f_RebuildCameraViewTransform(arg0);
}

void func_8006E360(s32 arg0, M2C_UNK arg1) {
    func_8006D654();
    f_SetCameraPositionHorizontal(arg0, arg1);
    f_SetCameraPositionVertical(arg0, arg1);
    f_RebuildCameraViewTransform(arg0);
}

void f_SnapCameraPositionAndRebuildView(void *cam, void *pos)
{
    f_SetCameraPositionHorizontal(cam, pos);
    f_SetCameraPositionVertical(cam, pos);
    f_RebuildCameraViewTransform(cam);
}

void f_ApproachCameraPositionAndRebuildView(void *arg0, M2C_UNK arg1) {
    if (((s32 (*)())f_ApproachCameraPositionHorizontal)() != 0) {
        M2C_FIELD(arg0, u8 *, 0x66) = (u8) (M2C_FIELD(arg0, u8 *, 0x66) | 1);
    }
    if (f_ApproachCameraPositionVertical(arg0, arg1) != 0) {
        M2C_FIELD(arg0, u8 *, 0x66) = (u8) (M2C_FIELD(arg0, u8 *, 0x66) | 2);
    }
    f_RebuildCameraViewTransform(arg0);
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006E464);

extern s8 D_1F8000EE[];
void func_8006E8F8(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x24) = 0;
    M2C_FIELD(arg0, s32 *, 0x28) = 0;
    *((s16 *)D_1F8000EE) = -0x6D6;
    M2C_FIELD(arg0, s16 *, 0x56) = 0x100;
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006E918);

void f_UpdateCameraFollowTomba(void)
{
    u8 *c = (u8 *)&g_CameraState;
    u8 *t = D_800E7E80_f78d;

    *(u16 *)(c + 0xE) = *(u16 *)(t + 0x32) - 0xC8;
    *(u16 *)(c + 0xA) = *(u16 *)(t + 0x2E);
    *(u16 *)(c + 0x12) = *(u16 *)(t + 0x36);
    f_SetCameraPositionHorizontal(c, c + 8);
    f_SetCameraPositionVertical(c, c + 8);
    func_8006E918(c);
    f_RebuildCameraViewTransform(c);
}

void func_8006EA7C(u8 *a)
{
    *(s16 *)(a + 0x56) = 0x100;
    a[0x72] = 0;
    a[0x76] = 0;
    a[0x77] = 0;
    a[0x74] = 0;
    *(s16 *)(a + 0x6) = 0;
    *(s32 *)(a + 0xC) = *(s32 *)D_1F8000E0;
    *(s16 *)(a + 0x52) = 0x400;
    *(s16 *)(a + 0x22) = 0xF0;
    *(s16 *)(a + 0x8C) = 0;
    switch (D_800BF870.unk0) {
    case 0:
        if (D_800BF89C == 2) {
            a[0x64] = 7;
            *(s16 *)(a + 0x3A) = 0xABA;
            *(s16 *)(a + 0x3E) = -0x320;
            *(s16 *)(a + 0x42) = 0xEE0;
            D_1F8000D0_fb20[1] = 0xD3B;
            *(s16 *)&D_1F8000D0_fb20[3] = -0xA83;
            D_1F8000D0_fb20[5] = 0xDB2;
            break;
        }
        if (D_800BF816 != 0) {
            break;
        }
        a[0x64] = 0;
        goto common;
    case 2: case 7: case 20:
        a[0x64] = 0;
        break;
    case 3:
        a[0x64] = 0xE;
        break;
    case 16: case 17: case 18: case 19:
        a[0x64] = 0x80;
        break;
    default:
        a[0x64] = 0;
    common:
        func_8006E0F0(a);
        func_8006E918(a);
        break;
    }
    if ((u8)(D_1F800236[0] - 5) < 2) {
        f_SetCameraFocusPosition(D_800E7E80_f78d + 0x2C);
        *(s16 *)(a + 0x3E) += 0x3E8;
        if (D_800E7E80_f78d[2] == 0) {
            *(s16 *)(a + 0x3E) -= 0x8C;
            *(s16 *)(a + 0xE) = *(s16 *)(a + 0x3E);
            a[0x64] = 0xF;
            *(s16 *)(a + 0x6C) = 0x578;
            *(s16 *)(a + 0x6E) = 0x40;
            *(s16 *)(a + 0x70) = *(u16 *)(D_800E7E80_f78d + 0x140) + 0x400;
            func_8006E294(a, a + 0x38);
            f_SnapCameraPositionAndRebuildView(a, D_800E7E80_f78d + 0x2C);
        }
    }
}

extern u8 D_800E7EAC[];
extern s32 D_800E7EB0;
void func_8006EC44(void)
{
    u8 *c = D_800E8008_f2dc;

    switch (c[0]) {
    case 0:
        c[0] = 1;
        func_8006EA7C(c);
        break;
    case 1:
        if (c[1] != 0) {
            if (c[1] != c[0]) {
                break;
            }
        } else {
            c[1] = c[0];
            c[2] = 0;
            c[3] = 0;
        }
        c[0x66] = 0;
        switch (c[0x64] & 0x3F) {
        case 0:
            switch (D_800BF870.unk0) {
            case 2:
                func_80115F58(c);
                break;
            case 7:
                func_80112DEC(c);
                break;
            case 20:
                func_8010AD0C(c);
                break;
            default:
                if (!(c[0x64] & 0x80)) {
                    func_8006E0F0(c);
                    func_8006E464(c);
                }
                D_800A4AA0[D_800BF870.unk0](c);
                break;
            }
            break;
        case 1:
            switch (D_800BF870.unk0) {
            case 2:
                func_80116918(c);
                break;
            case 7:
                func_80113660(c);
                break;
            case 20:
                func_8010B2F0(c);
                break;
            default:
                func_8006E228(c, c + 0x38);
                break;
            }
            break;
        case 2:
            func_8006E294(c, c + 0x38);
            break;
        case 3:
            func_8006E360(c, c + 0x38);
            break;
        case 4:
            func_8006E2FC(c, c + 0x38);
            break;
        case 5:
            f_SnapCameraPositionAndRebuildView(c, D_800E7EAC);
            break;
        case 6:
            c[0x64] = 0;
            *(s32 *)(c + 0xC) = D_800E7EB0;
            break;
        case 8:
            f_ApproachCameraPositionAndRebuildView(c, c + 0x38);
            break;
        case 9:
            func_8018B924(c);
            break;
        case 10:
            func_8010D89C(c);
            break;
        case 11:
        case 12:
            c[0x64] = 0;
            c[2] = 0;
            c[3] = 0;
            break;
        case 13:
            c[0x64] = 6;
            break;
        case 7:
        case 14:
            f_SnapCameraPositionAndRebuildView(c, c + 0x38);
            break;
        case 15:
            f_ApproachCameraPositionAndRebuildView(c, D_800E7EAC);
            break;
        case 17:
            func_80111AB4(c);
            break;
        }
        func_8006C988(c);
        break;
    }
}

typedef struct { u8 b[4]; } Bytes4_058;
extern Bytes4_058 D_80010058;
void func_8006EF38(void)
{
    u8 *c = (u8 *)&g_CameraState;
    s32 dx;
    s32 dz;
    u16 *d;

    if ((u32)(D_1F800236_18be - 3) < 2) {
        dx = (rcos(*(s16 *)(c + 0x70)) * 500) >> 12;
        dz = (rsin(*(s16 *)(c + 0x70)) * 500) >> 12;
        d = (u16 *)D_1F8000D0_b839;
        d[1] = *(u16 *)(c + 0x3A) + dx;
        d[5] = *(u16 *)(c + 0x42) + dz;
        *(u16 *)(c + 0x70) += 8;
        f_SnapCameraPositionAndRebuildView(c, c + 0x38);
    }
}

extern s32 D_800BFE48;
s32 func_8006EFF4(s32 arg0) {
    return ((s32) D_800BFE48 >> arg0) & 1;
}

void func_8006F00C(s32 bit)
{
    D_800BF870.flags5D8 |= 1 << bit;
}

void func_8006F02C(s32 bit)
{
    D_800BF870.flags5C4 |= 1 << bit;
}

void func_8006F04C(void)
{
    s32 i;
    u8 *g;

    if (D_800BF840 & 0x80) {
        i = D_800BF840 & 0xF;
        switch (i) {
        case 0: case 1: case 6:
            g = (u8 *)&D_800BF870 + i;
            if (g[0x5CA] < 3) {
                g[0x5CA]++;
                break;
            }
            func_8006F00C(i);
            break;
        case 7: case 8:
            func_8006F02C(i);
            func_8006F00C(i);
            break;
        }
        D_800BF840 = 0;
    }
}

u8 *f_SpawnTombaMovementHintController(void)
{
    u8 *a = f_AllocateActorRecordByType(2, 3, 1);

    if (a == NULL) {
        return NULL;
    }
    *(void **)(a + 0x1C) = func_8006F2D0;
    a[2] = 1;
    a[0x28] |= 0x80;
    return a;
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006F138);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006F2D0);

INCLUDE_ASM("asm/main/nonmatchings/main", f_InitializeLinkedPickupFromVisualDefinition);

extern s16 *D_800A3E80[];
extern u8 D_800A4BB8[];
extern s16 *D_800A3EA4[];
u8 *f_AllocateActor(u8 *owner, u8 flags, u8 kind, u8 type);
u8 *f_SpawnAreaLinkedItemPickupActor(u8 *owner, s16 id)
{
    s16 *p = D_800A3E80[D_800BF870.unk0];
    s32 i;
    u8 *e;

    for (; *p != -1; p += 3) {
        if ((s16)*(u16 *)p == id) {
            break;
        }
    }
    if (*p != -1) {
        for (i = 0; i < 3; i++) {
            e = f_AllocateActor(owner, D_800A4BB8[i], 3, 4);
            if (e != NULL) {
                goto found;
            }
        }
        return NULL;
found:
        if (f_InitializeLinkedPickupFromVisualDefinition(owner, e, p, id) == 0) {
            return NULL;
        }
        return e;
    }
    return NULL;
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006FC34);

u8 *f_SpawnAreaLinkedWeaponPickupActor(u8 *owner, s16 id)
{
    s16 *p = D_800A3EA4[D_800BF870.unk0];
    s32 i;
    u8 *e;

    for (; *p != -1; p += 3) {
        if ((s16)*(u16 *)p == id) {
            break;
        }
    }
    if (*p != -1) {
        for (i = 0; i < 3; i++) {
            e = f_AllocateActor(owner, D_800A4BB8[i], 3, 4);
            if (e != NULL) {
                goto found;
            }
        }
        return NULL;
found:
        if (f_InitializeLinkedPickupFromVisualDefinition(owner, e, p, id) == 0) {
            return NULL;
        }
        return e;
    }
    return NULL;
}

void func_80070018(u8 *a);
u8 *f_SpawnLinkedItemPickupActor(u8 *owner, s16 id)
{
    s32 i;
    u8 *e;

    i = 0;
    do {
        e = f_AllocateActor(owner, D_800A4BB8[i], 3, 4);
        if (e != NULL) {
            goto found;
        }
        i++;
    } while (i < 3);
    return NULL;
found:
    *(void **)(e + 0x1C) = func_80070018;
    *(u8 **)(e + 0x10) = owner;
    *(s16 *)(e + 0x68) = id;
    e[0x28] |= 0x80;
    if (D_800BF816 == 0) {
        e[0xBE] = 0;
    } else {
        e[0xBE] = 1;
    }
    e[0x5F] = 1;
    *(s16 *)(e + 0x74) = 0;
    e[4] = 2;
    return e;
}

s32 func_8006FFE8(void)
{
    u8 *p = D_800BF844;

    if (p != NULL) {
        p[0x5F] |= 1;
        return 1;
    }
    return 0;
}

void func_80070018(u8 *a)
{
    u8 *p;
    s32 r;

    switch (a[4]) {
    case 0:
        a[4] = 1;
        break;
    case 1:
        if (a[0xBE] != 0 && D_800BF816 == 0) {
            a[4] = 2;
            break;
        }
        p = *(u8 **)(a + 0x10);
        switch (a[5]) {
        case 0:
            func_800702C0(a);
            break;
        case 1:
            func_80070650(a);
            break;
        }
        if (a[1] = p[1]) {
            if (a[0x5F] & 0x80) {
                f_AdvanceActorTimedFrameSequence(a);
            } else {
                f_UpdateActorUnscaledModelTransforms(a);
            }
        }
        break;
    case 2:
        if (*(s16 *)(a + 0x74) != 0) {
            (*(s16 *)(a + 0x74))--;
            p = *(u8 **)(a + 0x10);
            if (a[1] = p[1]) {
                if (a[0x5F] & 0x80) {
                    f_AdvanceActorTimedFrameSequence(a);
                } else {
                    f_UpdateActorUnscaledModelTransforms(a);
                }
            }
        } else if (a[0x5F] & 1) {
            if (a[0x5F] & 2) {
                switch (a[3]) {
                case 0:
                    r = f_GrantPickupHealth(a, 1);
                    break;
                case 1:
                    r = f_GrantPickupHealth(a, 2);
                    break;
                case 4:
                    r = func_8004B3F4((s32)a, 100);
                    break;
                case 5:
                    r = func_8004B3F4((s32)a, 200);
                    break;
                case 6:
                    r = func_8004B3F4((s32)a, 500);
                    break;
                case 7:
                    r = func_8004B3F4((s32)a, 1000);
                    break;
                case 11:
                    r = func_8004B3F4((s32)a, 100000);
                    break;
                case 15:
                    r = func_8004A118(a);
                    break;
                case 16:
                    r = func_8004A2A0(a);
                    break;
                case 17:
                    r = func_8004B428(a);
                    break;
                }
                if (r != 0) {
                    a[4] = 3;
                }
            } else if (f_GrantNonGemPickupReward(a) != 0) {
                a[4] = 3;
            }
        } else {
            a[4] = 3;
        }
        break;
    case 3:
        f_ResolveEffectEightByteStreamPayload(a);
        break;
    }
}

void func_800702C0(u8 *a)
{
    u8 *o;
    u8 *q;
    u16 r;
    u16 ang;

    r = *(u16 *)(a + 0x62);
    o = MEMBER_AT(u8 *, a, 0x10);
    ang = *(u16 *)(o + 0x56);
    switch (a[0x5E]) {
    case 0:
        *(u16 *)(a + 0x2E) = (*(s32 *)(MEMBER_AT(u8 *, D_800E7E80, 0xD0) + 0x2C) + *(s32 *)(MEMBER_AT(u8 *, D_800E7E80, 0xDC) + 0x2C)) / 2;
        *(u16 *)(a + 0x32) = (*(s32 *)(MEMBER_AT(u8 *, D_800E7E80, 0xD0) + 0x30) + *(s32 *)(MEMBER_AT(u8 *, D_800E7E80, 0xDC) + 0x30)) / 2;
        *(u16 *)(a + 0x36) = (*(s32 *)(MEMBER_AT(u8 *, D_800E7E80, 0xD0) + 0x34) + *(s32 *)(MEMBER_AT(u8 *, D_800E7E80, 0xDC) + 0x34)) / 2;
        *(u16 *)(a + 0x32) += *(u16 *)(a + 0x60);
        ang = *(u16 *)(D_800E7E80 + 0x56);
        r = 0x20;
        break;
    case 1:
        *(u16 *)(a + 0x2E) = *(u16 *)(MEMBER_AT(u8 *, o, 0xDC) + 0x2C);
        *(u16 *)(a + 0x32) = *(u16 *)(MEMBER_AT(u8 *, o, 0xDC) + 0x30);
        *(u16 *)(a + 0x36) = *(u16 *)(MEMBER_AT(u8 *, o, 0xDC) + 0x34);
        *(u16 *)(a + 0x32) += *(u16 *)(a + 0x60);
        break;
    case 2:
        *(u16 *)(a + 0x2E) = (*(s32 *)(MEMBER_AT(u8 *, o, 0xD0) + 0x2C) + *(s32 *)(MEMBER_AT(u8 *, o, 0xDC) + 0x2C)) / 2;
        *(u16 *)(a + 0x32) = (*(s32 *)(MEMBER_AT(u8 *, o, 0xD0) + 0x30) + *(s32 *)(MEMBER_AT(u8 *, o, 0xDC) + 0x30)) / 2;
        *(u16 *)(a + 0x36) = (*(s32 *)(MEMBER_AT(u8 *, o, 0xD0) + 0x34) + *(s32 *)(MEMBER_AT(u8 *, o, 0xDC) + 0x34)) / 2;
        *(u16 *)(a + 0x32) += *(u16 *)(a + 0x60);
        break;
    case 3:
        *(u16 *)(a + 0x2E) = *(u16 *)(MEMBER_AT(u8 *, o, 0xC0) + 0x2C) - ((rcos(*(s16 *)(o + 0x56)) * *(s16 *)(o + 0x80) / 2) >> 12);
        *(u16 *)(a + 0x32) = *(u16 *)(MEMBER_AT(u8 *, o, 0xC0) + 0x30);
        *(u16 *)(a + 0x36) = *(u16 *)(MEMBER_AT(u8 *, o, 0xC0) + 0x34) + ((rsin(*(s16 *)(o + 0x56)) * *(s16 *)(o + 0x80) / 2) >> 12);
        *(u16 *)(a + 0x32) += *(u16 *)(a + 0x60);
        break;
    case 4:
        *(u16 *)(a + 0x2E) = *(u16 *)(MEMBER_AT(u8 *, o, 0xD0) + 0x2C);
        *(u16 *)(a + 0x32) = *(u16 *)(MEMBER_AT(u8 *, o, 0xD0) + 0x30);
        *(u16 *)(a + 0x36) = *(u16 *)(MEMBER_AT(u8 *, o, 0xD0) + 0x34);
        *(u16 *)(a + 0x32) += *(u16 *)(a + 0x60);
        break;
    case 5:
        *(u16 *)(a + 0x2E) = *(u16 *)(MEMBER_AT(u8 *, D_800E7E80, 0xDC) + 0x2C);
        *(u16 *)(a + 0x32) = *(u16 *)(MEMBER_AT(u8 *, D_800E7E80, 0xDC) + 0x30);
        *(u16 *)(a + 0x36) = *(u16 *)(MEMBER_AT(u8 *, D_800E7E80, 0xDC) + 0x34);
        *(u16 *)(a + 0x32) += *(u16 *)(a + 0x60);
        break;
    case 6:
        *(u16 *)(a + 0x2E) = *(u16 *)(MEMBER_AT(u8 *, D_800E7E80, 0xD0) + 0x2C);
        *(u16 *)(a + 0x32) = *(u16 *)(MEMBER_AT(u8 *, D_800E7E80, 0xD0) + 0x30);
        *(u16 *)(a + 0x36) = *(u16 *)(MEMBER_AT(u8 *, D_800E7E80, 0xD0) + 0x34);
        *(u16 *)(a + 0x32) += *(u16 *)(a + 0x60);
        break;
    case 7:
        *(u16 *)(a + 0x2E) = *(u16 *)(MEMBER_AT(u8 *, o, 0xE4) + 0x2C);
        *(u16 *)(a + 0x32) = *(u16 *)(MEMBER_AT(u8 *, o, 0xE4) + 0x30);
        *(u16 *)(a + 0x36) = *(u16 *)(MEMBER_AT(u8 *, o, 0xE4) + 0x34);
        *(u16 *)(a + 0x32) += *(u16 *)(a + 0x60);
        break;
    }
    *(u16 *)(a + 0x2E) += (rcos((s16)ang) * (s16)r) >> 12;
    *(u16 *)(a + 0x36) += (-rsin((s16)ang) * (s16)r) >> 12;
}

void func_80070650(void *arg0) {
    u16 temp_v0;

    if (M2C_FIELD(arg0, s16 *, 0x60) != 0) {
        temp_v0 = M2C_FIELD(arg0, u16 *, 0x2E) + 8;
        M2C_FIELD(arg0, u16 *, 0x2E) = temp_v0;
        if ((s16) temp_v0 >= M2C_FIELD(arg0, s16 *, 0x60)) {
            M2C_FIELD(arg0, u16 *, 0x2E) = (u16) M2C_FIELD(arg0, s16 *, 0x60);
            M2C_FIELD(arg0, s16 *, 0x60) = 0;
        }
    }
}

s32 func_80070698(s32 n)
{
    s32 r = rand() & (n - 1);

    r = r * r / n;
    if (rand() & 1) {
        r = -r;
    }
    return r;
}

void f_ConfigureScriptActorConversation(u8 a, u8 b, u8 c)
{
    (*(u8 **)D_1F800214)[0xBF] = a;
    D_800BF808[0x28] = b;
    D_800BF808[0x29] = c;
    D_800BF808[0x3B] = 0;
}

void func_8007074C(u8 a, u8 b, u8 c, Vec3i_74C v)
{
    f_ConfigureScriptActorConversation(a, b, c);
    ((ConvTarget_74C *)D_800BF808)->v = v;
}

extern s8 D_1F800214[];
void f_StartCurrentScriptActorConversation(void) {
    void *temp_v1;

    temp_v1 = *((void **)D_1F800214);
    M2C_FIELD(temp_v1, s8 *, 6) = 0;
    M2C_FIELD(temp_v1, s8 *, 5) = 3;
}

s32 f_TrySetCurrentScriptActorStateActive(void)
{
    u8 *a = *(u8 **)D_1F800214;

    if (a[0x70] == 0) {
        a[0x70] = 1;
        return 1;
    }
    return 0;
}

s32 f_TryStartCurrentScriptActorAnimation2(void)
{
    u8 *a = *(u8 **)D_1F800214;

    if (a[0x70] == 0) {
        f_SetActorAnimation(a, 2, 2);
        a[0x70] = 1;
        return 1;
    }
    return 0;
}

s32 f_TrySetCurrentScriptActorAnimation0(void)
{
    s8 *a = *(s8 **)D_1F800214;

    if (a[0x70] > 0) {
        return 0;
    }
    f_SetActorAnimation(a, 0, 2);
    return 1;
}

s8 f_GetCurrentScriptActorControlState(void) {
    return M2C_FIELD(*(void **)0x1F800214, s8 *, 0x70);
}

extern s8 D_1F800214[];
void f_LoadCurrentScriptActorScript(s32 arg0) {
    f_LoadActorScript(*((s32 *)D_1F800214), arg0);
}

void f_SetCurrentScriptActorMode(s8 arg0) {
    void *temp_v0;

    temp_v0 = *(void **)0x1F800214;
    M2C_FIELD(temp_v0, s8 *, 6) = 0;
    M2C_FIELD(temp_v0, s8 *, 3) = arg0;
}

void func_800708CC(u8 *a)
{
    u8 *g;

    *(s16 *)(a + 0x44) = 0x400;
    g = D_800BF808;
    a[3] = 0;
    *(u16 *)(g + 0x1E) = *(u16 *)(a + 0x4E) = *(u16 *)(a + 0x2E);
    *(u16 *)(g + 0x22) = *(u16 *)(a + 0x50) = *(u16 *)(a + 0x32);
    *(u16 *)(g + 0x26) = *(u16 *)(a + 0x52) = *(u16 *)(a + 0x36);
    a[6] = 0;
    a[5] = 2;
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007091C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80070BD0);

void f_UpdateActorOrbitAroundAnchor(u8 *a)
{
    *(s16 *)(a + 0x2E) = *(u16 *)(a + 0x4E) + rcos(*(s16 *)(a + 0x44)) * 24 / 4096;
    *(s16 *)(a + 0x32) = *(u16 *)(a + 0x50) + rsin(*(s16 *)(a + 0x44) * 2) * 24 / 4096;
    *(s16 *)(a + 0x36) = *(u16 *)(a + 0x52);
    *(s16 *)(a + 0x44) = (*(u16 *)(a + 0x44) + 0x20) & 0xFFF;
}

void f_SetScriptActorInteractionOffset(u8 *a, s32 mode, Vec3i_F08 *v)
{
    u8 *g;

    switch (mode) {
    case 0:
        g = D_800BF808;
        *(s16 *)(g + 0x1E) = D_1F800160 - *(u16 *)(a + 0x2E);
        *(s16 *)(g + 0x22) = D_1F800162 - *(u16 *)(a + 0x32);
        *(s16 *)(g + 0x26) = D_1F800164 - *(u16 *)(a + 0x36);
        break;
    case 1:
        ((ConvTarget_F08 *)D_800BF808)->v = *v;
        break;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/main", f_ApproachShortCoordinate);

INCLUDE_ASM("asm/main/nonmatchings/main", f_UpdateScriptedInteractionApproach);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80071260);

void func_800713F8(u8 *a)
{
    switch (a[6]) {
    case 0:
        {
            u16 **t = D_800A4BBC[D_800BF870.unk0];
            f_InitializeActorScript(a, D_8001B860, t[D_800BF830]);
        }
        a[0x70] = 2;
        a[6]++;
        break;
    case 1:
        if (a[0x70] == 0xFF) {
            f_StartCurrentScriptActorConversation();
        }
        break;
    }
    f_RunActorScriptInterpreter(a);
    f_UpdateActorOrbitAroundAnchor(a);
    f_AdvanceActorAnimationAndStoreCompletion(a);
}

s32 func_800714C0(u8 *a, s16 v)
{
    switch (a[6]) {
    case 0:
        *(s16 *)(a + 0x4A) = v;
        a[6]++;
        goto end;
    case 1:
        *(s16 *)(a + 0x4A) += 0x100;
        if (*(s16 *)(a + 0x4A) > 0x3000) {
            *(s16 *)(a + 0x4A) = 0x3000;
        }
        *(s32 *)(a + 0x30) += *(s16 *)(a + 0x4A) << 8;
        if (D_800BF82A < *(s16 *)(a + 0x32)) {
            *(s16 *)(a + 0x32) = D_800BF82A;
            return 1;
        }
    end:
    default:
        return 0;
    }
}

void func_8007156C(u8 *a)
{
    switch (a[3]) {
    case 0:
        if (a[0x79] == 1) {
            f_SetActorAnimationIfChanged(a, 0, 4);
        }
        f_UpdateActorOrbitAroundAnchor(a);
        break;
    case 1:
        break;
    case 2:
        if (func_800714C0(a, 0)) {
            a[3] = 3;
        }
        break;
    case 3:
        if (f_UpdateScriptedInteractionApproach(a, 1)) {
            a[3] = 0;
        }
        break;
    case 4:
        D_800BF843 = 3;
        switch (a[6]) {
        case 0:
            f_SetScriptActorInteractionOffset(a, 0, 0);
            a[6]++;
            break;
        case 1:
            f_UpdateScriptedInteractionApproach(a, 0);
            f_UpdateActorOrbitAroundAnchor(a);
            break;
        }
        break;
    case 5:
        if (f_UpdateScriptedInteractionApproach(a, 0)) {
            a[3] = 0;
        } else {
            D_800BF843 = 3;
        }
        f_UpdateActorOrbitAroundAnchor(a);
        break;
    }
    f_RunActorScriptInterpreter(a);
    f_AdvanceActorAnimationAndStoreCompletion(a);
}

void func_800716B4(u8 *a)
{
    void *bank;

    D_1F800214_120a = a;
    if (f_InitializeMultiPartActorModel(a, 0xC, D_800ECF58_674d.p40, D_800A4BC8) != 0) {
        return;
    }
    bank = D_800ECF58_674d.p44;
    a[0xB] = 0xF;
    *(s32 *)(a + 0x34) = 0;
    *(s32 *)(a + 0x30) = 0;
    *(s32 *)(a + 0x2C) = 0;
    *(s16 *)(a + 0xBC) = 0x200;
    *(s16 *)(a + 0xBA) = 0x200;
    *(s16 *)(a + 0xB8) = 0x200;
    *(s16 *)(a + 0x58) = 0;
    *(s16 *)(a + 0x56) = 0;
    *(s16 *)(a + 0x54) = 0;
    a[0x7B] = 0;
    *(void **)(a + 0x3C) = bank;
    f_InitializeActorScript(a, D_8001B860, D_800A3CD0);
    a[4]++;
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_80071768);

void func_80071A3C(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 4);
    switch (temp_v1) {                              /* irregular */
    case 0:
        func_800716B4(arg0);
        if ((D_800BF870.pad1[0x270] != 0) && (D_800BF870.unk0 == 4)) {
            func_8011B79C(arg0);
            return;
        }
        if ((D_800BF870.pad1[0x275] != 0) && (D_800BF870.unk0 == 7)) {
            func_801178E4(arg0);
            return;
        }
    case 2:
        return;
    case 1:
        func_80071768(arg0);
        if (M2C_FIELD(arg0, u8 *, 1) != 0) {
            f_UpdateActorScaledOffsetModelTransforms(arg0);
            return;
        }
        break;
    case 3:
        f_ResolveEffectEightByteStreamPayload(arg0);
        break;
    }
}

u8 f_FormatIntegerText(s32 v, char *out);
void func_80072520(u8 *a);
void func_80071B44(u8 *src, s32 n, s32 kind)
{
    u8 *a = f_AllocateActor(src, 0x80, 3, 0xD);
    u8 *old;

    if (a == NULL) {
        return;
    }
    *(void **)(a + 0x1C) = func_80072520;
    a[3] = kind;
    if ((kind & 0xFF) == 1) {
        u8 *g = (u8 *)&D_800BF870;

        *(s32 *)(g + 4) += n;
        *(u16 *)(a + 0x54) = *(u16 *)(src + 0x2E);
        *(u16 *)(a + 0x56) = *(u16 *)(src + 0x32);
        *(u16 *)(a + 0x58) = *(u16 *)(src + 0x36);
    }
    *(s16 *)(a + 0xE) = ((s16 (*)(s32, u8 *))f_FormatIntegerText)(n, a + 0x44);
    *(s16 *)(a + 0x5C) = (n >= 5000) ? 0x7C3E : 0x7C7E;
    f_PlaySoundEffect(0x11, 0xF, 0);
    {
        u8 *s = D_800BF808;

        old = *(u8 **)(s + 0x34);
        if (old != NULL) {
            old[4] = 3;
        }
        *(u8 **)(s + 0x34) = a;
    }
}

void func_80071C48(void *arg0, s16 arg1, s16 arg2) {
    u16 temp_v0;
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 6);
    switch (temp_v1) {                              /* irregular */
    case 0:
        temp_v0 = (M2C_FIELD(arg0, u16 *, 0x60) + 0x100) & 0xFFF;
        M2C_FIELD(arg0, u16 *, 0x60) = temp_v0;
        if (temp_v0 == 0) {
            M2C_FIELD(arg0, u8 *, 6) = (u8) (M2C_FIELD(arg0, u8 *, 6) + 1);
        }
        M2C_FIELD(arg0, s16 *, 0x2E) = arg1;
        M2C_FIELD(arg0, s32 *, 0x30) = (s32) ((arg2 << 0x10) + (rsin((s16) M2C_FIELD(arg0, u16 *, 0x60)) * M2C_FIELD(arg0, s16 *, 0x82) * 0x10));
        return;
    case 1:
        M2C_FIELD(arg0, s16 *, 0x2E) = arg1;
        M2C_FIELD(arg0, s16 *, 0x32) = arg2;
        return;
    }
}

typedef struct { u8 pad[0x60]; u16 v[16]; } Arr_1CF4;
typedef struct { u8 pad[0x60]; s16 s[16]; } ArrS_1CF4;
void func_80071CF4(u8 *a, s32 x, s16 y, s32 i)
{
    s32 x0 = x;
    s16 y0 = y;
    s16 *st = (s16 *)(a + (i + 7) * 2);
    u16 v;

    switch (st[0x30]) {
    case 0:
        if (*(s16 *)(a + 0x42) >= i) {
            v = (((Arr_1CF4 *)a)->v[i] + 0x100) & 0xFFF;
            ((Arr_1CF4 *)a)->v[i] = v;
            if (v == 0) {
                st[0x30]++;
            }
        }
        *(s16 *)(a + 0x2E) = x0 + *(s16 *)(a + 0x82) * i;
        *(s32 *)(a + 0x30) = (y0 << 16) + ((rsin(((ArrS_1CF4 *)a)->s[i]) * *(s16 *)(a + 0x82)) << 4);
        break;
    case 1:
        *(s16 *)(a + 0x32) = y;
        *(s16 *)(a + 0x2E) = x + *(s16 *)(a + 0x82) * i;
        break;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_80071DFC);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80072114);

void func_800721DC(u8 *a, s16 x, s16 y)
{
    u16 v;
    s32 t;

    switch (a[6]) {
    case 0:
        v = (*(u16 *)(a + 0x5A) + 0x100) & 0xFFF;
        *(u16 *)(a + 0x5A) = v;
        if (v == 0) {
            a[6]++;
        }
        t = rsin(*(s16 *)(a + 0x5A)) * *(s16 *)(a + 0x82);
        *(s16 *)(a + 0x2E) = x;
        *(s32 *)(a + 0x30) = (y << 16) + (t << 4);
        break;
    case 1:
        v = (*(u16 *)(a + 0x5A) + 0x100) & 0xFFF;
        *(u16 *)(a + 0x5A) = v;
        if (v == 0) {
            a[6]++;
        }
        t = rsin(*(s16 *)(a + 0x5A)) * *(s16 *)(a + 0x82);
        *(s16 *)(a + 0x2E) = x;
        *(s32 *)(a + 0x30) = (y << 16) + (t << 3);
        break;
    case 2:
        *(s16 *)(a + 0x2E) = x;
        *(s16 *)(a + 0x32) = y;
        break;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_80072308);

void func_80072520(u8 *a)
{
    switch (a[4]) {
    case 0:
        a[4]++;
        *(s16 *)(a + 0x40) = 0x3C;
        break;
    case 1:
        switch (a[3]) {
        case 0:
        case 1:
            func_80071DFC(a);
            break;
        case 2:
            func_80072308(a);
            break;
        }
        break;
    case 2:
        break;
    case 3:
        f_ResolveEffectEightByteStreamPayload(a);
        break;
    }
}

u8 *func_800725D4(s16 *h)
{
    u8 *a = f_AllocateActorRecordByType(1, 3, 1);

    if (a == 0) {
        return 0;
    }
    a[2] = 0x17;
    *(void **)(a + 0x1C) = func_8007263C;
    *(s16 **)(a + 0x10) = h;
    a[0x28] |= 0x80;
    *h = -1;
    return a;
}

void func_8007263C(u8 *a)
{
    switch (a[4]) {
    case 0:
        a[0xB] = 8;
        a[4]++;
        break;
    case 1:
        if (**(s16 **)(a + 0x10) == -2) {
            a[4] = 3;
        } else {
            a[1] = 1;
        }
        break;
    case 2:
    case 3:
        f_ResolveEffectEightByteStreamPayload();
        break;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_800726D4);

u8 f_FormatIntegerText(s32 v, char *out);
void func_80072898(void);
u8 *func_800727D4(void *owner, s32 ev, s32 kind)
{
    s32 ap = f_GetEventAPReward(ev, kind);
    u8 *a;

    if (ap == 0 || (a = (u8 *)f_AllocateActorRecordByType(0, 3, 1)) == NULL) {
        return NULL;
    }
    *(void **)(a + 0x1C) = func_80072898;
    a[2] = 0x1D;
    a[3] = kind;
    *(s16 *)(a + 0x60) = ev;
    *(void **)(a + 0x10) = owner;
    a[0x28] |= 0x80;
    *(s16 *)(a + 0xE) = ((s16 (*)(s32, u8 *))f_FormatIntegerText)(ap, a + 0x44);
    *(s16 *)(a + 0x5C) = 0x7C7E;
    return a;
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_80072898);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80072A78);

u8 *f_AllocateActor(u8 *owner, u8 flags, u8 kind, u8 type)
{
    u8 *r;

    if (kind == 3) {
        r = f_AllocateActorRecordByType(flags & 0x7F, 3, 1);
    } else {
        r = f_AllocateActorRecordByType(flags & 0x7F, kind, 0);
    }
    if (r == 0) {
        return 0;
    }
    r[0x28] = flags;
    *(u8 **)(r + 0x10) = owner;
    r[2] = type;
    return r;
}

s32 f_OpenInteriorEntranceDoor(u8 *a)
{
    s32 r = 0;

    switch (a[0x46]) {
    case 0:
        *(s16 *)(a + 0x50) -= 0x40;
        if (*(s16 *)(a + 0x50) < -0x400) {
            *(s16 *)(a + 0x50) = -0x400;
            r = 1;
        }
        break;
    case 1:
        *(s16 *)(a + 0x50) += 0x40;
        if (*(s16 *)(a + 0x50) > 0x400) {
            *(s16 *)(a + 0x50) = 0x400;
            r = 1;
        }
        break;
    }
    *(u16 *)(a + 0x56) = *(u16 *)(a + 0x5A) + *(u16 *)(a + 0x50);
    return r;
}

void f_ApplyInteriorEntranceDoorMirroredYaw(void *arg0) {
    M2C_FIELD(arg0, s16 *, 0x56) = (s16) (M2C_FIELD(arg0, u16 *, 0x5A) - M2C_FIELD(arg0, u16 *, 0x50));
}

s32 f_CloseInteriorEntranceDoor(u8 *a)
{
    s32 r = 0;

    switch (a[0x46]) {
    case 0:
        *(s16 *)(a + 0x50) += 0x40;
        if (*(s16 *)(a + 0x50) > 0) {
            *(s16 *)(a + 0x50) = 0;
            r = 1;
        }
        break;
    case 1:
        *(s16 *)(a + 0x50) -= 0x40;
        if (*(s16 *)(a + 0x50) < 0) {
            *(s16 *)(a + 0x50) = 0;
            r = 1;
        }
        break;
    }
    if (r != 0 && a[0xBF] != 0) {
        f_PlaySoundEffect(0x18, 0, 0xF);
    }
    *(u16 *)(a + 0x56) = *(u16 *)(a + 0x5A) - *(u16 *)(a + 0x50);
    return r;
}

void f_InitializeInteriorDoorPartOpenYaw(void *arg0, void *arg1) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 0x46);
    switch (temp_v1) {                              /* irregular */
    case 0:
        M2C_FIELD(arg1, s16 *, 0x12) = -0x400;
        M2C_FIELD(arg1, s16 *, 0xA) = (s16) (M2C_FIELD(arg1, u16 *, 0xE) - 0x400);
        return;
    case 1:
        M2C_FIELD(arg1, s16 *, 0x12) = 0x400;
        M2C_FIELD(arg1, s16 *, 0xA) = (s16) (M2C_FIELD(arg1, u16 *, 0xE) + 0x400);
        return;
    }
}

s32 f_OpenInteriorDoorPart(u8 *p, u8 *d)
{
    s32 r = 0;

    switch (p[0x46]) {
    case 0:
        *(s16 *)(d + 0x12) -= 0x40;
        if (*(s16 *)(d + 0x12) < -0x400) {
            *(s16 *)(d + 0x12) = -0x400;
            r = 1;
        }
        break;
    case 1:
        *(s16 *)(d + 0x12) += 0x40;
        if (*(s16 *)(d + 0x12) > 0x400) {
            *(s16 *)(d + 0x12) = 0x400;
            r = 1;
        }
        break;
    }
    *(u16 *)(d + 0xA) = *(u16 *)(d + 0xE) - *(u16 *)(d + 0x12);
    return r;
}

s32 f_CloseInteriorDoorPart(u8 *a, u8 *p)
{
    s32 r = 0;

    switch (a[0x46]) {
    case 0:
        *(s16 *)(p + 0x12) += 0x40;
        if (*(s16 *)(p + 0x12) > 0) {
            *(s16 *)(p + 0x12) = 0;
            r = 1;
        }
        break;
    case 1:
        *(s16 *)(p + 0x12) -= 0x40;
        if (*(s16 *)(p + 0x12) < 0) {
            *(s16 *)(p + 0x12) = 0;
            r = 1;
        }
        break;
    }
    if (r != 0 && a[0xBF] != 0) {
        f_PlaySoundEffect(0x18, 0, 0xF);
    }
    *(u16 *)(p + 0xA) = *(u16 *)(p + 0xE) - *(u16 *)(p + 0x12);
    return r;
}

s32 f_CloseMirroredInteriorDoorPart(u8 *a, u8 *p)
{
    s32 r = 0;

    switch (a[0x46]) {
    case 0:
        *(s16 *)(p + 0x12) += 0x40;
        if (*(s16 *)(p + 0x12) > 0) {
            *(s16 *)(p + 0x12) = 0;
            r = 1;
        }
        break;
    case 1:
        *(s16 *)(p + 0x12) -= 0x40;
        if (*(s16 *)(p + 0x12) < 0) {
            *(s16 *)(p + 0x12) = 0;
            r = 1;
        }
        break;
    }
    if (r != 0 && a[0xBF] != 0) {
        f_PlaySoundEffect(0x18, 0, 0xF);
    }
    *(u16 *)(p + 0xA) = *(u16 *)(p + 0xE) + *(u16 *)(p + 0x12);
    return r;
}

void f_PrepareInteriorTransition(u8 *door)
{
    u8 *t;

    door[0] = 2;
    t = D_800E7E80_f78d;
    if (door[0xBF] != 0) {
        f_PlaySoundEffect(0x17, 0, 0xF);
    }
    t[0x145] = 0;
    f_ResetTombaControlState(t);
    t[5] = 0;
    t[6] = 0;
    t[7] = 0;
}

void f_BeginInteriorEntryTransition(u8 *door)
{
    f_PrepareInteriorTransition(door);
    D_800BF808[0x10] = 1;
    D_800BF808[0xF] = door[3];
}

extern s8 D_800BF818;
void f_BeginInteriorExitTransition(void *arg0) {
    f_PrepareInteriorTransition(arg0);
    D_800BF818 = 3;
}

typedef struct { u8 pad0[7]; u8 u7; u8 pad8[7]; u8 uF; u8 u10; } Gs808_7318;
extern Gs808_7318 D_800BF808_f0b6;
s32 f_UpdateInteriorEntranceDoorTransition(u8 *a)
{
    u8 *t = D_800E7E80_f78d;

    switch (a[6]) {
    case 0:
        if (a[0x29] != 0 && t[0x29] != 0 && t[0x17B] == 0) {
            a[6]++;
            f_BeginInteriorEntryTransition(a);
            if (D_1F800137_104c == 0) {
                D_1F800137_104c = 2;
            }
            break;
        }
        if (D_800BF808_f0b6.u10 == 5 && D_800BF808_f0b6.uF == a[3]) {
            a[6]++;
            f_BeginInteriorEntryTransition(a);
            return 0;
        }
        return 0;
    case 1:
        if (f_OpenInteriorEntranceDoor(a) != 0 && D_800BF816 != 0) {
            a[6]++;
            f_ApplyInteriorEntranceDoorMirroredYaw(a);
            return 0;
        }
        break;
    case 2:
        if (D_800BF808_f0b6.u10 == 2 && D_800BF808_f0b6.u7 == 0) {
            a[0] = 1;
            a[6]++;
            a[0x5F] = 1 - a[0x5F];
            *(u16 *)(a + 0x84) += 0x320;
            *(u16 *)(a + 0x86) += 0x320;
            break;
        }
        return 0;
    case 3:
        if (a[0x29] != 0 && t[0x29] != 0 && t[0x17B] == 0) {
            if (D_800BF80F_fcc6 != 0) {
                return 0;
            }
            a[6]++;
            f_BeginInteriorExitTransition(a);
            if (D_1F800137_104c == 0) {
                D_1F800137_104c = 2;
            }
            break;
        }
        if (D_800BF808_f0b6.u10 == 6 && D_800BF808_f0b6.u7 == 0) {
            a[6]++;
            f_BeginInteriorExitTransition(a);
            return 0;
        }
        return 0;
    case 4:
        if (D_800BF808_f0b6.u10 == 4 && D_800BF808_f0b6.u7 == 0) {
            a[6]++;
            D_800BF808_f0b6.u10 = 0;
            break;
        }
        return 0;
    case 5:
        if (f_CloseInteriorEntranceDoor(a) != 0) {
            a[0] = 1;
            a[6] = 0;
            a[0x5F] = 1 - a[0x5F];
            *(u16 *)(a + 0x84) -= 0x320;
            *(u16 *)(a + 0x86) -= 0x320;
            return 1;
        }
        break;
    }
    return 0;
}

INCLUDE_ASM("asm/main/nonmatchings/main", f_UpdateEntranceContactIndicator);

s32 func_80073750(u8 *s)
{
    s32 n[2];
    s32 flag = 0;
    s32 r;

    n[1] = 0;
    n[0] = 0;
    while (*s != 0) {
        if (*s == 10) {
            flag = 1;
        }
        s++;
        if (flag) {
            n[1]++;
        } else {
            n[0]++;
        }
    }
    if (flag) {
        r = n[1];
        if (r < n[0]) {
            r = n[0];
        }
        r = -r;
    } else {
        r = n[0];
    }
    return r;
}

void func_800737F8(s32 arg)
{
    struct { s16 x; s16 y; s16 w; s16 h; } r;
    char *name = f_GetWarpSectionDisplayName(D_800BF870.unk0, arg);
    s32 n = func_80073750(name);
    s32 x;

    if (n < 0) {
        r.h = 0x20;
        n = -n;
    } else {
        r.h = 0x10;
    }
    x = 0xA0 - n * 4;
    f_DrawTallMenuText((s16)x, 0x50, 0, name, 0);
    r.y = 0x50;
    r.x = x;
    r.w = n * 8;
    func_8005019C(&r, 7, 1, 0);
}

void f_DrawTallMenuText(s16 x, s32 y, s16 c, s32 d, s32 e);
void func_800738B0(void)
{
    s16 r[4];
    s32 *tab;
    s32 n;
    s32 x;

    f_DrawPauseMenuButtonIcon(0x4000, 0xBC, 0x58, 0);
    f_DrawPauseMenuButtonIcon(0x2000, 0xBC, 0x6C, 0);
    tab = (s32 *)D_800A2854;
    n = func_80073750((u8 *)tab[3]);
    x = 0xA0 - n * 4;
    r[0] = x;
    r[1] = 0x3C;
    r[2] = n * 8;
    r[3] = 0x3C;
    f_DrawTallMenuText(x, 0x3C, 0, tab[3], 0);
    f_DrawTallMenuText(0x80, 0x50, 0, tab[4], 0);
    f_DrawTallMenuText(0x80, 0x64, 0, tab[5], 0);
    if (r[0] > 0x78) {
        r[0] = 0x78;
        r[2] = 0x50;
    }
    func_8005019C(r, 7, 1, 1);
}

typedef struct { u8 unk0; u8 u1; u8 pad2[0x1E]; s32 x; s32 y; s32 z; u8 pad2C[0x59C]; u8 u5C8; } GsSign_39AC;
extern GsSign_39AC D_800BF870_39ac;
extern s16 D_800A4C80[];
extern u8 D_800E7E85;
extern u8 D_800BF84A;
void func_800739AC(u8 *a)
{
    u8 *g = D_800E7E80_f78d;
    u8 *p;
    u16 v;


    switch (a[4]) {
    case 0:
        if (f_InitializeSinglePartActorModel(a, 0xC, D_800A4C80[D_800BF870_39ac.unk0]) != 0) {
            break;
        }
        a[0] = 1;
        a[4]++;
        if (D_800BF870_39ac.unk0 == 2 || D_800BF870_39ac.unk0 == 7 || D_800BF870_39ac.unk0 == 0x14) {
            *(s16 *)(a + 0x80) = 0xA0;
            *(s16 *)(a + 0x82) = 0x140;
        } else {
            *(s16 *)(a + 0x80) = 0x12C;
            *(s16 *)(a + 0x82) = 0x258;
        }
        *(s16 *)(a + 0x84) = 0xED;
        *(s16 *)(a + 0x86) = 0xED;
        a[0x2B] = 0;
        if (D_800BF870_39ac.unk0 == 5 && a[3] == 5) {
            a[0xB] = 0xF;
        }
        break;
    case 1:
        if (f_TestAndQueueActorForRender(a) == 0) {
            a[0x2B] = 0;
            break;
        }
        switch (a[5]) {
        case 5:
            a[0] = 1;
            a[5] = 0;
        case 0:
            if (a[0x2B] == 3) {
                a[5]++;
                D_800BF870_39ac.u1 = a[3];
                f_UnlockWarpDestinationAndAreaDoor(D_800BF870_39ac.unk0, D_800BF870_39ac.u1);
            }
            break;
        case 1:
            if ((D_800BF870_39ac.unk0 == 2 || D_800BF870_39ac.unk0 == 7) && D_800E7E85 != 0x1F) {
                a[5] = 4;
            } else {
                func_800737F8(a[3]);
                if (D_800E7E68 & 0x2000) {
                    a[5]++;
                    f_PlaySoundEffect(0x11, 0, 0);
                }
            }
            break;
        case 2:
            func_800738B0();
            v = D_800E7E68;
            if (v & 0x4000) {
                a[5]++;
                f_PlaySoundEffect(0x11, 0, 0);
            } else if (v & 0x2000) {
                a[5] = 4;
                f_PlaySequencedMusic(1);
            }
            break;
        case 3:
            D_1F800136 = 2;
            D_800BF84A = 0;
            D_800BF870_39ac.x = *(s32 *)(g + 0x2C);
            D_800BF870_39ac.y = *(s32 *)(g + 0x30);
            D_800BF870_39ac.z = *(s32 *)(g + 0x34);
            D_800BF870_39ac.u5C8 = g[0x2A];
            p = *(u8 **)D_1F800138;
            *(s16 *)(p + 0x50) = 0;
            p[0x6B] = 8;
            a[5]++;
            f_SetDoubleBufferedClearColor(0, 0, 0);
            break;
        case 4:
            a[0] = 2;
            a[5]++;
            break;
        }
        a[0x2B] = 0;
        f_UpdateActorUnscaledModelTransforms(a);
        break;
    case 2:
        break;
    case 3:
        f_ResolveEffectEightByteStreamPayload(a);
        break;
    }
}

extern s16 D_800A4C94[];
extern u16 D_800A4CA8[];
extern u16 D_800BFE56;
void func_80073CD8(u8 *a)
{
    u16 id;
    u8 *p;
    u8 *q;

    switch (a[4]) {
    case 0:
        if (f_InitializeSinglePartActorModel(a, 0xC, D_800A4C94[D_800BF870.unk0]) != 0) {
            break;
        }
        a[0x2B] = 0;
        *(u8 **)(a + 0x14) = NULL;
        *(s16 *)(a + 0x54) = 0;
        *(s16 *)(a + 0x58) = 0;
        a[4]++;
        if (D_800BF870.unk0 == 2 || D_800BF870.unk0 == 7 || D_800BF870.unk0 == 0x14) {
            a[0] = 1;
            *(s16 *)(a + 0x80) = 0xA0;
            *(s16 *)(a + 0x82) = 0x140;
            *(s16 *)(a + 0x84) = 0xED;
            *(s16 *)(a + 0x86) = 0xED;
        } else {
            if (D_800BF870.pad1[2] == 0) {
                a[0] = 1;
            }
            *(s16 *)(a + 0x80) = 0x12C;
            *(s16 *)(a + 0x82) = 0x258;
            *(s16 *)(a + 0x84) = 0xCB;
            *(s16 *)(a + 0x86) = 0xCB;
        }
        switch (a[3]) {
        case 2:
            a[8] = 0;
            *(s16 *)(a + 0x56) = 0xC00;
            break;
        case 8:
            a[0xB] = 0xF;
            break;
        case 12:
        case 13:
        case 14:
            *(s16 *)(a + 0x56) = 0x400;
            *(s16 *)(a + 0x80) = 0x3C;
            *(s16 *)(a + 0x82) = 0x78;
            *(s16 *)(a + 0x84) = 0x3E;
            a[8] = 0;
            *(s16 *)(a + 0x86) = 0x7C;
            break;
        case 17:
            if (D_800BFE56 & 0x10) {
                *(u16 *)(a + 0x32) += 0x64;
            }
            break;
        case 20:
            a[8] = 0;
            break;
        case 5:
        case 6:
        case 7:
        case 29:
        case 30:
            *(s16 *)(a + 0x56) = 0;
            break;
        case 32:
            *(s16 *)(a + 0x56) = 0x4D0;
            break;
        case 21:
        case 22:
        case 23:
        case 24:
            a[0] = 1;
            break;
        }
        break;
    case 1:
        f_TestAndQueueActorForRender(a);
        switch (a[5]) {
        case 4:
            a[0] = 1;
            a[5] = 0;
        case 0:
            if (a[0x2B] == 3) {
                a[5]++;
                switch (a[3]) {
                case 12:
                    if (f_StartEvent(0x4E) != 0) {
                        a[5] = 5;
                    }
                    break;
                case 13:
                    if (f_StartEvent(0x50) != 0) {
                        a[5] = 5;
                    }
                    break;
                case 14:
                    if (f_StartEvent(0x4F) != 0) {
                        a[5] = 5;
                    }
                    break;
                }
            }
            break;
        case 1:
        case 5:
            if (a[3] == 2) {
                if (D_800BF870.pad1[0x96] == 0xFF) {
                    id = 0x16;
                    goto call;
                }
                if (D_800BF870.pad1[0x52] != 0) {
                    id = 0x15;
                    goto call;
                }
            }
            id = D_800A4CA8[a[3]];
        call:
            if ((*(u8 **)(a + 0x14) = func_8007E110((s16)id, 0)) != NULL) {
                a[5]++;
            }
            break;
        case 6:
            if (f_IsEventPresentationComplete() != 0) {
                a[5] = 2;
            }
            break;
        case 2:
            if (D_800E7E68 & D_1F800174_de41) {
                a[5]++;
            }
            break;
        case 3:
            q = *(u8 **)(a + 0x14);
            if (q[4] < 2) {
                q[4] = 2;
                *(u8 **)(a + 0x14) = NULL;
            }
            a[0] = 2;
            a[5]++;
            break;
        }
        if (a[5] != 4 && (D_800BF870.unk0 == 2 || D_800BF870.unk0 == 7 || D_800BF870.unk0 == 0x14)) {
            p = *(u8 **)(a + 0x14);
            if (p != NULL && D_800E7E85 != 0x1F) {
                p[4] = 2;
                *(u8 **)(a + 0x14) = NULL;
                a[0] = 1;
                a[5] = 0;
            }
        }
        a[0x2B] = 0;
        f_UpdateActorUnscaledModelTransforms(a);
        break;
    case 2:
        break;
    case 3:
        f_ResolveEffectEightByteStreamPayload(a);
        break;
    }
}

void func_8004C930();
u8 *func_8007413C(u8 *a)
{
    u8 *p = f_AllocateActor(a, 0, 5, 4);

    if (p != NULL) {
        *(void **)(p + 0x1C) = func_8004C930;
        *(u16 *)(p + 0x2E) = *(u16 *)(a + 0x2E);
        *(u16 *)(p + 0x32) = *(u16 *)(a + 0x32) - *(s16 *)(a + 0x84) / 2;
        *(u16 *)(p + 0x36) = *(u16 *)(a + 0x36);
        {
            u8 k = a[3];
            p[0x28] |= 0x80;
            p[3] = k + 0x2B;
        }
    }
    return p;
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_800741DC);

typedef struct { u8 type; u8 a; u8 b; u8 c; s8 d; u8 e; s8 vol; u8 pad; } SfxDef_4D18;
extern SfxDef_4D18 D_800A4D18[];
extern SfxDef_4D18 *D_800A4EF8[];
void f_PlaySequencedMusic(s32 arg);
s32 f_PlaySoundEffect(id, pitch, voladj)
    u8 id;
    s8 pitch;
    s8 voladj;
{
    SfxDef_4D18 *d;
    u8 type;
    s16 flag;
    s16 vol;
    s16 p;
    u8 *g;
    u8 n = id;

    if ((s8)id >= 0) {
        if ((u8)n >= 0x70) {
            switch ((u8)n) {
            case 0x70:
                f_PlaySequencedMusic(2);
                goto ret0;
            case 0x71:
                f_PlaySequencedMusic(3);
                goto ret0;
            case 0x72:
                f_PlaySequencedMusic(4);
                goto ret0;
            case 0x73:
                f_PlaySequencedMusic(5);
                goto ret0;
            case 0x74:
                f_PlaySequencedMusic(6);
                goto ret0;
            case 0x75:
                f_PlaySequencedMusic(7);
                goto ret0;
            case 0x79:
                f_PlaySequencedMusic(0xD);
                goto ret0;
            case 0x76:
            case 0x7A:
                f_PlaySequencedMusic(0xA);
                goto ret0;
            case 0x77:
            case 0x7B:
                f_PlaySequencedMusic(0xB);
                goto ret0;
            case 0x78:
            case 0x7C:
                f_PlaySequencedMusic(0xC);
                goto ret0;
            case 0x7F:
                f_StopNonReservedSequencedMusic();
                goto ret0;
            }
            goto ret0;
        }
        d = &D_800A4D18[(u8)n];
        type = d->type;
        if (type != 4 && D_1F800137_104c != 0) {
            type = 1;
        }
        flag = 0;
    } else {
        if ((u8)n >= 0xE1) {
        ret0:
            return 0;
        }
        d = D_800A4EF8[D_800BF870.unk0];
        d += id & 0x7F;
        type = d->type;
        if (type != 4 && D_1F800137_104c != 0) {
            type = 1;
        }
        flag = 0x80;
    }
    g = D_800FB160_9a03;
    p = d->vol + voladj;
    if (g[5] == 0) {
        vol = 0;
    } else {
        p = p * g[5];
        vol = p / 9;
        if (vol < 0) {
            vol = 0;
        } else if (vol >= 0x80) {
            vol = 0x7F;
        }
    }
    return f_QueueSoundEffectVoice(type, d->a, d->b, d->c | flag, d->d + pitch, d->e, vol, vol);
}

void f_PlaySoundEffectWithPitchOffset(s32 arg0, s8 arg1) {
    f_PlaySoundEffect(arg0 & 0xFF, arg1, 0);
}

void func_8007483C(s32 arg0, s8 arg1, s8 arg2) {
    f_PlaySoundEffect(arg0 & 0xFF, arg1, arg2);
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007486C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007496C);

void f_SetSoundEffectHandleVolume(u8 handle)
{
    SoundHandle *h = &D_800BE238[handle];

    h->volume = 10;
}

u32 func_80074A60(s32 vol, s32 ang)
{
    u16 hi, lo;

    ang = (ang - D_1F8000F2) & 0xFFF;
    if (ang > 0x800) {
        ang = 0x1000 - ang;
    }
    if (ang < 0x400) {
        hi = (u32)(ang * vol) >> 10;
        if (hi >= 0x80) {
            hi = 0x7F;
        }
        lo = vol;
    } else {
        hi = vol;
        lo = (u32)((0x800 - ang) * vol) >> 10;
        if (lo >= 0x80) {
            lo = 0x7F;
        }
    }
    return (hi << 16) | lo;
}

void f_ComputeDirectionalStereoVolume(u32 handle)
{
    u8 i = handle;
    SoundHandle3 *h = &D_800BE238_0a61[i];

    if ((h->id & ~0xFF) == (handle & ~0xFF)) {
        D_800BE358 |= 1 << i;
        ((u8 *)h)[1] = 0;
    }
}

void func_80074B44(void)
{
    s32 i;
    s32 mask = 0;

    for (i = D_800BED78; i < 0x18; i++) {
        mask |= 1 << i;
        D_800BE238_df3f[i].on = 0;
        D_800BE238_df3f[i].flags &= 0xC0;
    }
    D_800BE358_bdda = mask;
    SpuSetKey(0, mask);
}

extern s8 D_1F80027E[];
void func_80074BC4(void) {
    *((s8 *)D_1F80027E) = 0;
    f_StopVoicePlayback();
    func_80074B44();
    f_StopSequencedMusic();
}

extern u8 D_800FB165;
extern s8 D_800BE22A;
char SsSetReservedVoice(char);
void f_PlaySequencedMusic(s32 arg)
{
    s32 n = arg & 0x7F;
    s32 play;
    u32 t;
    s32 i;
    s16 cnt;
    u8 v;
    s16 vol;

    t = arg & 0x80;
    play = t == 0;
    if ((u32)n >= 14) {
        return;
    }
    switch (n) {
    case 0:
    case 1:
    case 11:
    case 12:
        if ((u16)(D_800BED80 - 2) < 2) {
            return;
        }
    case 2:
    case 3:
        if ((u16)(D_800BED80 - 4) < 4 || D_800BED80 == 10 || D_800BED80 == 13) {
            D_800BE22A = D_800BED80 | 0x80;
        }
        break;
    default:
        if ((u16)(D_800BED80 - 1) < 3) {
            D_800BE22A = arg;
            return;
        }
        break;
    }
    f_StopSequencedMusic();
    D_800BED80 = n;
    SsSetReservedVoice(D_800BE368[n].mode);
    switch (n) {
    case 0 ... 3:
    case 11:
    case 12:
        vol = D_800FB165 * 127 / 9;
        break;
    default:
        vol = D_800FB164 * 127 / 9;
        break;
    }
    if (D_800BF870.unk0 == 0x15) {
        vol = D_800FB164 * 127 / 9;
    }
    SsSeqSetVol(D_800BE368[D_800BED80].seq, vol, vol);
    SsSeqPlay(D_800BE368[D_800BED80].seq, 1, play);
    D_800BED78 = cnt = D_800BE368[D_800BED80].mode;
    for (i = 0; i < cnt; i++) {
        *(s32 *)&D_800BE238_df3f[i] = -1;
    }
}

void f_StopSequencedMusic(void)
{
    s32 i;

    if (D_800BED80 != -1) {
        SsSeqStop(D_800BE368[D_800BED80].seq);
        for (i = 0; i < D_800BED78; i++) {
            D_800BE238_df3f[i].on = 0;
            D_800BE238_df3f[i].flags &= 0xC0;
        }
        D_800BED78 = 0;
        D_800BED80 = -1;
        SsSetReservedVoice(0);
    }
}

extern s8 D_800BE22A;
void f_StopNonReservedSequencedMusic(void) {
    D_800BE22A = 0;
    if (D_800BED80 >= 4) {
        f_StopSequencedMusic();
    }
}

INCLUDE_ASM("asm/main/nonmatchings/main", f_PlayAreaBackgroundTrack);

extern s8 D_1F80023B[];
extern s8 D_800BE22B;
void func_80075024(s32 arg0) {
    s8 var_s0;

    var_s0 = 0x14;
    if ((arg0 & 0xFF) == 5) {
        var_s0 = 0x13;
    }
    f_ControlStreamedAudioTrack(var_s0, 1);
    *((s8 *)D_1F80023B) = var_s0;
    D_800BE22B = 0;
}

extern s8 D_1F80023B[];
extern s8 D_800BE22B;
void func_80075070(s8 arg0) {
    *((s8 *)D_1F80023B) = arg0;
    D_800BE22B = 1;
    f_SetStreamedAudioVolumeTarget(0);
}

extern s8 D_1F80023B[];
void func_800750A4(s8 arg0) {
    f_ControlStreamedAudioTrack(arg0 & 0xFF, 1);
    *((s8 *)D_1F80023B) = arg0;
}

s32 f_ControlStreamedAudioTrack(s32 track)
{
    if (track == 0xFF) {
        return D_800BE0E4_9d53 & 4;
    }
    if (track == 0xFE) {
        f_StopVoicePlayback();
        return;
    }
    f_StartStreamedAudioTrack(track);
    return 0;
}

extern u8 D_800BE3D8[];
typedef struct { u32 mask; s32 mode; s16 left; s16 right; s32 delay; s32 feedback; } RevAttr_5130;
void func_80075130(void)
{
    RevAttr_5130 attr;
    s32 i;

    SsInit();
    SsSetReservedVoice(0x18);
    SsSetAutoKeyOffMode(0);
    SpuSetKey(0, 0xFFFFFF);
    SsSetTickMode(1);
    SsSetTableSize(D_800BE3D8, 0xE, 1);
    SsSetMVol(0x7F, 0x7F);
    SsStart();
    D_800BED78 = 0;
    D_800BED80 = -1;
    func_800752B4(2);
    D_800BE358 = 0;
    for (i = 0xD; i >= 0; i--) {
        D_800BE368[i].on = 0;
    }
    attr.mask = 7;
    attr.mode = 0x102;
    attr.left = 0x4000;
    attr.right = 0x4000;
    SpuReserveReverbWorkArea(1);
    SpuSetReverbModeParam(&attr);
    SpuSetReverb(1);
    SpuSetReverbDepth(&attr);
    SpuSetReverbVoice(1, 0xFFFFFF);
    D_800BE1F8_296f[0x32] = 0;
    D_800BE1F8_296f[0x33] = 0;
}

void func_80075240(void)
{
    u8 *a;

    func_80075D58();
    a = D_800BE1F8_296f;
    *(s16 *)(a + 0x2A) = 0x7FFF;
    *(s16 *)(a + 0x2C) = 0x7FFF;
    *(s16 *)(a + 0x2E) = 0x1FFF;
    *(s16 *)(a + 0x30) = 0x1FFF;
    *(s32 *)D_800BE1F8_296f = 0x300;
    *(s32 *)(a + 0x18) = 0;
    *(s32 *)(a + 0x14) = 0;
    func_80075824(a);
    SpuSetCommonAttr(a);
    *(s32 *)D_800BE1F8_296f = 0;
    a[0x32] = 0;
    a[0x33] = 0;
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_800752B4);

void func_800753AC(void *dst, s32 sector, s32 size, void *slot)
{
    func_8001DC40(dst, D_800BE108 + sector, size, slot);
}

void func_800753D4(s16 *arg0, M2C_UNK arg1, M2C_UNK arg2) {
    s16 temp_v0;

    temp_v0 = SsVabOpenHead(arg1, -1);
    *arg0 = temp_v0;
    *arg0 = SsVabTransBody(arg2, temp_v0);
loop_1:
    if ((SsVabTransCompleted(0) << 0x10) == 0) {
        f_YieldCurrentCooperativeWorker(1);
        goto loop_1;
    }
}

void f_OpenSequencedMusicSlot(s16 slot, void *data, s16 mode, s16 id)
{
    SeqSlot_368 *e = &D_800BE368[slot];
    s16 vol;

    e->id = id;
    vol = D_800FB164 * 127 / 9;
    e->seq = SsSeqOpen(data, id);
    e->mode = mode;
    e->on = 1;
    SsSeqSetVol(e->seq, vol, vol);
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_800754F4);

extern s16 D_800A4F7E;
void func_800753AC(void *dst, s32 sector, s32 size, void *slot);
u8 *func_8007566C(s16 idx, u8 *buf)
{
    u16 *tbl = (u16 *)0x80182000;
    SeqSlot_368 *e;
    s32 i;
    s32 *hdr;
    u16 *t;
    s32 size;

    if (D_800A4F7E >= 0) {
        SsVabClose(D_800A4F7E);
        D_800A4F7E = -1;
    }
    for (i = 10; i < 14; i++) {
        if (D_800BE368[i].on != 0) {
            SsSeqClose(D_800BE368[i].seq);
            D_800BE368[i].on = 0;
        }
    }
    t = (u16 *)(idx * 2 + (s32)tbl);
    size = (t[1] - t[0]) << 11;
    hdr = (s32 *)(buf + (size - 0x800));
    ((void (*)(void *, s32, s32))func_800753AC)(buf, t[0], size);
    func_800753D4(&D_800A4F7E, buf + hdr[0], buf + hdr[1]);
    switch (D_800BF870.unk0) {
    case 10:
        func_80118E28();
        break;
    case 11:
        func_80117988();
        break;
    case 12:
        func_8011727C();
        break;
    case 13:
        func_80116FC8();
        break;
    case 14:
        func_801174AC();
        break;
    case 15:
        func_8011A428();
        break;
    case 5:
        func_8013AC40();
        break;
    case 20:
        func_801174B0();
        break;
    case 21:
        func_80110774();
        break;
    }
    return buf + hdr[1];
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_80075824);

void func_80075A30(void)
{
    SpuAttrLite *a = &D_800BE1F8;

    a->h12 = 0x7FFF;
    a->h10 = 0x7FFF;
    a->mask |= 0xC3;
    a->mvolR = 0x3FFF;
    a->mvolL = 0x3FFF;
    SpuSetCommonAttr(a);
    D_800BE1F8.mask = 0;
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_80075A80);

void f_SetStreamedAudioVolumeTarget(s32 x)
{
    u8 *a = D_800BE1F8_296f;

    if (x < 0) {
        *(s16 *)(a + 0x2A) = -x;
        *(s16 *)(a + 0x2C) = -x;
        return;
    }
    if (x > 0x7FFF) {
        x = 0x7FFF;
    }
    *(s16 *)(a + 0x2A) = x;
}

void f_RefreshSoundEffectHandleLifetime(s32 x)
{
    u8 *a = D_800BE1F8_296f;

    if (x < 0) {
        *(s16 *)(a + 0x2E) = -x;
        *(s16 *)(a + 0x30) = -x;
        return;
    }
    if (x >= 0x2000) {
        x = 0x1FFF;
    }
    *(s16 *)(a + 0x2E) = x;
}

void func_80075D58(void)
{
    u8 *o = D_800FB160_9a03;

    D_800BE220 = o[4] * 0x7FFF / 9;
    if (o[3] == 0) {
        D_800BED7C[0] = 0x80;
        D_800BED7C[1] = 0;
        D_800BED7C[2] = 0x80;
        D_800BED7C[3] = 0;
        SsSetStereo();
    } else {
        D_800BED7C[0] = 0x40;
        D_800BED7C[1] = 0x40;
        D_800BED7C[2] = 0x40;
        D_800BED7C[3] = 0x40;
        SsSetMono();
    }
    CdMix(D_800BED7C);
}

INCLUDE_ASM("asm/main/nonmatchings/main", f_QueueSoundEffectVoice);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80075F0C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80075FF8);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80076904);

static inline void SkelAnimStartFrame(u8 *a)
{
    u8 *s;
    u16 v;

    *(s16 *)(a + 0xE) = *(u16 *)(*(u8 **)(a + 0x38) + 6) & 0xFFF;
    func_80076904(a);
    s = *(u8 **)(a + 0x38);
    v = *(u16 *)(s + 6);
    if (v & 0x2000) {
        switch (v & 0xC000) {
        case 0:
            func_80075FF8(a, s + 8, *(s16 *)(a + 0xE));
            break;
        case 0x4000:
        case 0xC000:
            func_80075FF8(a, *(void **)(s + 8), *(s16 *)(a + 0xE));
            break;
        case 0x8000:
            break;
        }
    }
}
s32 f_AdvanceActorSkeletalAnimation(u8 *a)
{
    u16 t = *(u16 *)(a + 0xE);
    s16 n = (t & 0xFFF) - 1;
    u8 *s;

    if (n != 0) {
        if (*(s32 *)(a + 0x38) >= 0) {
            func_80075F0C(a, n);
            *(u16 *)(a + 0xE) = n + (*(u16 *)(a + 0xE) & 0x1000);
            return 2;
        }
        *(u16 *)(a + 0xE) = n + (t & 0x1000);
        return 0;
    }
    s = *(u8 **)(a + 0x38);
    switch (*(s16 *)(s + 6) & 0xC000) {
    case 0:
        if (!(t & 0x1000)) {
            *(u8 **)(a + 0x38) = s + 8;
        }
        SkelAnimStartFrame(a);
        break;
    case 0x4000:
        if (!(t & 0x1000)) {
            *(u8 **)(a + 0x38) = s + 8;
            *(u8 **)(a + 0x38) = *(u8 **)(s + 8);
        }
        SkelAnimStartFrame(a);
        break;
    case 0x8000:
        *(u16 *)(a + 0xE) = *(u16 *)(s + 6) & 0xFFF;
        return 1;
    case 0xC000:
        if (!(t & 0x1000)) {
            *(u8 **)(a + 0x38) = s + 8;
            *(u8 **)(a + 0x38) = *(u8 **)(s + 8);
        }
        SkelAnimStartFrame(a);
        return 1;
    }
    return 0;
}

/* f_QueueClass2Or9ActorForRender, inlined */
static inline void QueueC2_703C(s32 arg0) {
    void *temp_a0;

    if (*((s16 *)D_1F800144) < 0x18) {
        temp_a0 = *((void **)D_1F80013C);
        *((void **)D_1F80013C) = temp_a0 - 4;
        M2C_FIELD(temp_a0, s32 *, -4) = arg0;
        *((s16 *)D_1F800144) = (u16) *((s16 *)D_1F800144) + 1;
    }
}
/* f_QueueClass4ActorForRender, inlined */
static inline void QueueC4_703C(s32 arg0) {
    void *temp_a0;

    if (*((s16 *)D_1F800150) < 0x28) {
        temp_a0 = *((void **)D_1F800148);
        *((void **)D_1F800148) = temp_a0 - 4;
        M2C_FIELD(temp_a0, s32 *, -4) = arg0;
        *((s16 *)D_1F800150) = (u16) *((s16 *)D_1F800150) + 1;
    }
}
/* f_QueueClass5ActorForRender, inlined */
static inline void QueueC5_703C(s32 arg0) {
    void *temp_a0;

    if (*((s16 *)D_1F80015C) < 0x1C) {
        temp_a0 = *((void **)D_1F800154);
        *((void **)D_1F800154) = temp_a0 - 4;
        M2C_FIELD(temp_a0, s32 *, -4) = arg0;
        *((s16 *)D_1F80015C) = (u16) *((s16 *)D_1F80015C) + 1;
    }
}
void func_8007703C(u8 *a)
{
    a[1] = 1;
    switch (a[0xC]) {
    case 2:
    case 9:
        QueueC2_703C((s32)a);
        break;
    case 4:
        QueueC4_703C((s32)a);
        break;
    case 5:
        QueueC5_703C((s32)a);
        break;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/main", f_TestActorVisibilityAndQueueForRender);

s32 f_StepWrappedAngleToward(s32 a, s32 b, s32 step)
{
    s32 d = (a - b) & 0xFFF;
    s16 e = d;
    s32 r;

    if (e == 0) {
        return b & 0xFFF;
    }
    if ((u32)e < 0x800) {
        if (e >= (s16)step) {
            r = b + step;
            goto done;
        }
    } else if (0x1000 - (s16)step >= e) {
        r = b - step;
        goto done;
    }
    r = b + d;
done:
    return r & 0xFFF;
}

s32 f_TestWrappedAngleSide(s32 a, s32 b, s32 flip)
{
    s32 d = ((a - b) - 0x400) & 0xFFF;

    if (!flip) {
        return d < 0x800;
    }
    return (d < 0x800) ^ 1;
}

typedef struct { u8 pad0[0x2E]; u16 x; u8 pad30[2]; u16 y; u8 pad34[2]; u16 z; } ActorPos_778C;
s32 f_TestAndQueueActorForRender(ActorPos_778C *a)
{
    s16 dx, dy, dz;
    D_1F800080 = 0;
    D_1F800084_8c7c = 0;
    dx = a->x - D_1F8000D0_fb20[1];
    dy = a->y - D_1F8000D0_fb20[3];
    dz = a->z - D_1F8000D0_fb20[5];
    return f_TestActorVisibilityAndQueueForRender(a, dx, dy, dz);
}

s32 f_TestAndQueueActorForRenderMode2(ActorPos_778C *a)
{
    s16 dx, dy, dz;
    D_1F800080 = 0;
    D_1F800084_8c7c = 2;
    dx = a->x - D_1F8000D0_fb20[1];
    dy = a->y - D_1F8000D0_fb20[3];
    dz = a->z - D_1F8000D0_fb20[5];
    return f_TestActorVisibilityAndQueueForRender(a, dx, dy, dz);
}

s32 func_80077870(ActorPos_778C *a)
{
    s16 dx, dy, dz;
    D_1F800080 = 0;
    D_1F800084_8c7c = 1;
    dx = a->x - D_1F8000D0_fb20[1];
    dy = a->y - D_1F8000D0_fb20[3];
    dz = a->z - D_1F8000D0_fb20[5];
    return f_TestActorVisibilityAndQueueForRender(a, dx, dy, dz);
}

s32 f_TestAndQueueActorForRenderWithYOffset(u8 *a, s32 y)
{
    s16 dx, dy, dz;
    D_1F800080 = 0;
    D_1F800084_8c7c = 0;
    dx = *(u16 *)(a + 0x2E) - D_1F8000D0_fb20[1];
    dy = *(u16 *)(a + 0x32) + y - D_1F8000D0_fb20[3];
    dz = *(u16 *)(a + 0x36) - D_1F8000D0_fb20[5];
    return f_TestActorVisibilityAndQueueForRender(a, dx, dy, dz);
}

s32 func_80077958(u8 *a, s32 x, s32 y)
{
    s16 dx, dy, dz;
    D_1F800080 = 0;
    dx = *(u16 *)(a + 0x2E) + x - D_1F8000D0_fb20[1];
    D_1F800084_8c7c = 0;
    dy = *(u16 *)(a + 0x32) + y - D_1F8000D0_fb20[3];
    dz = *(u16 *)(a + 0x36) - D_1F8000D0_fb20[5];
    return f_TestActorVisibilityAndQueueForRender(a, dx, dy, dz);
}

s32 func_800779D0(u8 *a, s32 x, s32 y, s32 z)
{
    s16 dx, dy, dz;
    D_1F800080 = 0;
    dx = *(u16 *)(a + 0x2E) + x - D_1F8000D0_fb20[1];
    D_1F800084_8c7c = 0;
    dy = *(u16 *)(a + 0x32) + y - D_1F8000D0_fb20[3];
    dz = *(u16 *)(a + 0x36) + z - D_1F8000D0_fb20[5];
    return f_TestActorVisibilityAndQueueForRender(a, dx, dy, dz);
}

s32 f_TestActorVisibilityWithXYZOffset(u8 *a, s32 x, s32 y, s32 z)
{
    s16 dx, dy, dz;
    D_1F800080 = 1;
    dx = *(u16 *)(a + 0x2E) + x - D_1F8000D0_fb20[1];
    D_1F800084_8c7c = 0;
    dy = *(u16 *)(a + 0x32) + y - D_1F8000D0_fb20[3];
    dz = *(u16 *)(a + 0x36) + z - D_1F8000D0_fb20[5];
    return f_TestActorVisibilityAndQueueForRender(a, dx, dy, dz);
}

s32 func_80077ACC(void *a, s32 x, s32 y, s32 z)
{
    s16 dx, dy, dz;
    D_1F800080 = 1;
    dx = x - D_1F8000D0_fb20[1];
    D_1F800084_8c7c = 4;
    dy = y - D_1F8000D0_fb20[3];
    dz = z - D_1F8000D0_fb20[5];
    return f_TestActorVisibilityAndQueueForRender(a, dx, dy, dz);
}

void f_StartActorTimedFrameSequence(u8 *actor, u16 **table, s32 index)
{
    u16 *seq = table[index];
    u16 frames = seq[1];

    *(u16 **)(actor + 0x38) = seq;
    *(u16 *)(actor + 0xE) = frames & 0x3FFF;
}

/* f_AdvanceActorTimedFrameSequence: adapted from Tombi-Decomp's AnimAdvance (src/AnimAdvance.c, MIT) */
typedef struct AnimFrameEntry { char p0[2]; unsigned short v; } AnimFrameEntry;
typedef struct { char p0[0xE]; short t; char p1[0x28]; AnimFrameEntry *a; } AnimTimedActor;
int f_AdvanceActorTimedFrameSequence(AnimTimedActor *o)
{
    AnimFrameEntry *e, *n;
    unsigned short v;

    o->t = o->t - 1;
    if (o->t != 0) return 0;
    e = o->a;
    v = e->v;
    switch (v & 0xc000) {
    case 0:
        n = e + 1;
        goto set;
    case 0x4000:
        o->a = e + 1;
        n = *(AnimFrameEntry **)(e + 1);
    set:
        o->a = n;
        o->t = n->v & 0x3fff;
        break;
    case 0x8000:
        o->t = v & 0x3fff;
        return 1;
    case 0xc000:
        o->a = e + 1;
        n = *(AnimFrameEntry **)(e + 1);
        o->a = n;
        o->t = n->v & 0x3fff;
        return 1;
    }
    return 0;
}

void f_StartActorSkeletalAnimation(u8 *a, u8 **tbl, s32 i)
{
    u8 *s = tbl[i];
    u16 f = *(u16 *)(s + 6);
    u16 v;

    *(u8 **)(a + 0x38) = s;
    *(s16 *)(a + 0xE) = f & 0xFFF;
    func_80076904(a);
    v = *(u16 *)(s + 6);
    if (v & 0x2000) {
        switch (v & 0xC000) {
        case 0:
            func_80075FF8(a, s + 8, *(s16 *)(a + 0xE));
            break;
        case 0x4000:
        case 0xC000:
            func_80075FF8(a, *(void **)(s + 8), *(s16 *)(a + 0xE));
            break;
        case 0x8000:
            break;
        }
    }
}

void f_StartActorSkeletalAnimationBlend(u8 *a, void **table, s32 i, s32 blend)
{
    s16 b = blend;
    void *seq = table[i];

    *(void **)(a + 0x38) = seq;
    func_80075FF8(a, seq, b);
    func_80075F0C(a, b);
    *(s16 *)(a + 0xE) = blend + 0x1000;
}

void func_80077D64(void)
{
    if (!(D_800BF808[0x3A] & 0x80)) {
        D_800BF808[0x3A] = 0x81;
    }
}

void func_80077D8C(void)
{
    u8 *g = D_800BF808;
    u8 v = g[0x3A];

    if (v == 0) {
        return;
    }
    switch (v & 0x7F) {
    case 1:
        f_PlaySoundEffect(0x29, 2, -0x41);
        g[0x3A] = 0x87;
        break;
    case 2:
        f_PlaySoundEffect(0x2A, 2, -0x41);
        g[0x3A] = 0;
        break;
    default:
        D_800BF808[0x3A]--;
        break;
    }
}

void f_SetActorRenderTint(void *arg0, s8 arg1, s8 arg2, s8 arg3) {
    M2C_FIELD(arg0, s8 *, 0x18) = arg1;
    M2C_FIELD(arg0, s8 *, 0x19) = arg2;
    M2C_FIELD(arg0, s8 *, 0x1A) = arg3;
    M2C_FIELD(arg0, u8 *, 0xD) = (u8) (M2C_FIELD(arg0, u8 *, 0xD) | 2);
}

s32 func_80077E3C(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_v0;

    temp_v0 = func_80075FF8(arg0, arg1, (s32) (s16) arg2);
    M2C_FIELD(arg0, s16 *, 0xE) = (s16) (arg2 + 0x1000);
    return temp_v0;
}

void f_QueueClass2Or9ActorForRender(s32 arg0) {
    void *temp_a0;

    if (*((s16 *)D_1F800144) < 0x18) {
        temp_a0 = *((void **)D_1F80013C);
        *((void **)D_1F80013C) = temp_a0 - 4;
        M2C_FIELD(temp_a0, s32 *, -4) = arg0;
        *((s16 *)D_1F800144) = (u16) *((s16 *)D_1F800144) + 1;
    }
}

void f_QueueClass4ActorForRender(s32 arg0) {
    void *temp_a0;

    if (*((s16 *)D_1F800150) < 0x28) {
        temp_a0 = *((void **)D_1F800148);
        *((void **)D_1F800148) = temp_a0 - 4;
        M2C_FIELD(temp_a0, s32 *, -4) = arg0;
        *((s16 *)D_1F800150) = (u16) *((s16 *)D_1F800150) + 1;
    }
}

void f_QueueClass5ActorForRender(s32 arg0) {
    void *temp_a0;

    if (*((s16 *)D_1F80015C) < 0x1C) {
        temp_a0 = *((void **)D_1F800154);
        *((void **)D_1F800154) = temp_a0 - 4;
        M2C_FIELD(temp_a0, s32 *, -4) = arg0;
        *((s16 *)D_1F80015C) = (u16) *((s16 *)D_1F80015C) + 1;
    }
}

s32 func_80077F3C(ActorPos_778C *a)
{
    s16 dx, dy, dz;
    D_1F800080 = 0;
    D_1F800084_8c7c = 0x3;
    dx = a->x - D_1F8000D0_fb20[1];
    dy = a->y - D_1F8000D0_fb20[3];
    dz = a->z - D_1F8000D0_fb20[5];
    return f_TestActorVisibilityAndQueueForRender(a, dx, dy, dz);
}

INCLUDE_ASM("asm/main/nonmatchings/main", f_IntegerSquareRootRounded);

s32 f_ApproximateVectorLength2D(s32 x, s32 y)
{
    s32 t;

    if (x < 0) {
        x = -x;
    }
    if (y < 0) {
        y = -y;
    }
    if (x < y) {
        x ^= y;
        y ^= x;
        x ^= y;
    }
    t = y + (y >> 1);
    return x - (x >> 5) - (x >> 7) + (t >> 2) + (t >> 6);
}

s32 f_ApproximateVectorLength3D(s32 x, s32 y, s32 z)
{
    u32 s;

    if (x < 0) {
        x = -x;
    }
    if (y < 0) {
        y = -y;
    }
    if (z < 0) {
        z = -z;
    }
    if (x < y) {
        x ^= y;
        y ^= x;
        x ^= y;
    }
    if (x < z) {
        x ^= z;
        z ^= x;
        x ^= z;
    }
    s = y + z;
    return x - (x >> 4) + (s >> 2) + (s >> 3);
}

s16 f_CalculateYawFromPositionToPoint(s16 *pos, s16 x, s16 z)
{
    s32 dx = x;
    s32 dz = z;

    return ratan2(pos[5] - dz, dx - pos[1]);
}

INCLUDE_ASM("asm/main/nonmatchings/main", f_UnlockWarpDestinationAndAreaDoor);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800783DC);

void func_80078610(void)
{
    u8 *m = D_1F8000F8;
    u8 *c = D_800E8008_f2dc;
    u8 *t = (u8 *)D_800E7E80;
    u8 *v;
    s32 x, y, z;

    f_SetIdentityMatrix(m);
    f_SetIdentityMatrix(m + 0x20);
    v = m - 0x28;
    *(s16 *)(v + 0x1E) = -0x6D6;
    *(s16 *)(v + 0x1C) = 0x1000;
    *(s16 *)(v + 0x18) = 0;
    *(s16 *)(v + 0x1A) = 0;
    *(s16 *)(v + 0x20) = 0;
    *(s16 *)(v + 0x22) = 0;
    *(s16 *)(v + 0x24) = 0;
    *(s16 *)(c + 0x70) = 0x400;
    *(s32 *)(c + 0x58) = 0;
    *(s32 *)(c + 0x20) = 0;
    *(s32 *)(c + 0x24) = 0;
    *(s32 *)(c + 0x28) = 0;
    *(s32 *)(c + 0x14) = 0;
    *(s32 *)(c + 0x18) = 0;
    *(s16 *)(c + 0x6E) = 0x100;
    y = *(s32 *)(t + 0x30);
    x = *(s32 *)(t + 0x2C);
    z = *(s32 *)(t + 0x34);
    *(s16 *)(c + 0x6C) = 0x6D6;
    *(s32 *)(v + 0x10) = y;
    *(s32 *)(v + 0xC) = x;
    *(s32 *)(v + 0x14) = z;
    *(s32 *)(c + 8) = y;
    *(s32 *)(c + 0x10) = z;
    *(s32 *)(c + 0xC) = x;
    *(s32 *)(v + 0) = x;
    *(s32 *)(v + 4) = y - 0x1400000;
    *(s32 *)(v + 8) = z - 0x6D60000;
    f_RebuildCameraViewTransform(c, y - 0x1400000, x, z - 0x6D60000);
    if (D_800BF870.unk0 == 3) {
        D_801003F8 = 0xE9;
    } else {
        D_801003F8 = 0x15E;
    }
    SetGeomScreen(D_801003F8);
}

s32 func_80078738(u8 a, u8 b)
{
    Entry8 *row = D_800A54A8_7082[a];

    row += b;
    return (row->flags & 0x600) >> 9;
}

u8 func_80078770(u8 a, u8 b)
{
    return D_800A4F88[a * 4 + b];
}

u8 *f_GetWarpSectionDisplayName(s32 a, s32 b)
{
    u8 *e = (u8 *)D_800A54A8_6044[(u8)a] + (u8)b * 8;
    s32 k = (*(u16 *)(e + 6) & 0x600) >> 9;

    return *(D_800A2B84 + (D_800A55B0[a] + k));
}

void *func_800787F8(s32 i)
{
    u8 *idx = &D_800A55C8[i];

    return D_800A2B64[*idx];
}

typedef struct { u8 pad[0x20]; s32 x, y, z; } GS_8824;
typedef struct { u16 x; u8 y; u8 clut; s16 u; s16 v; } Glyph_C8C8;
extern u8 D_80016EE0_e006[8];
typedef struct { u8 b[8]; } B8_C8C8;
void func_80078824(void)
{
    SpawnPoint_8824 *s = &D_800A54A8_86de[D_800BF870.unk0][D_800BF870.pad1[0]];

    ((GS_8824 *)&D_800BF870)->x = s->x << 16;
    ((GS_8824 *)&D_800BF870)->y = s->y << 16;
    ((GS_8824 *)&D_800BF870)->z = s->z << 16;
    D_800BF870.pad5C8[0] = s->flags & 0x7F;
}

extern s32 D_800BFE50;
s32 f_TestWarpDestinationUnlocked(s32 arg0) {
    return D_800BFE50 & (1 << arg0);
}

extern u16 D_800F23A4;
/* func_800794C8, inlined */
static inline void Step_88AC(void)
{
    u16 *p;
    u16 t;

    if (--D_800BED8C == 0) {
        p = D_800BED88;
        if (p[1] == 0) {
            p += 2;
        }
        D_800ECF54_4583[0] = p[0];
        t = p[1];
        p += 2;
        D_800BED88 = p;
        D_800BED8C = t;
    }
}
void func_800788AC(void)
{
    D_800ECF54_4583[1] = D_800ECF54_4583[0];
    if (D_1F80019A == 1) {
        Step_88AC();
    } else {
        D_800ECF54_4583[0] = func_800524B4(0);
    }
    D_800E7E68 = D_800ECF54_4583[0] & ~D_800ECF54_4583[1];
    D_800F23A4 = D_800ECF54_4583[1] & ~D_800ECF54_4583[0];
    func_8005229C();
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_80078988);

INCLUDE_ASM("asm/main/nonmatchings/main", f_DrawMenuTextGlyphs);

void func_80079014(u32 *src, s32 idx)
{
    u32 *p;
    u32 *ot;
    u32 *ot_c;
    u32 *ot2;
    u32 *ot3;

    p = D_800BF544;
    __asm__ volatile("");

    do {
        ot = D_800ED8C8 + idx;
    } while (0);
    ot_c = ot;
    __asm__ volatile("");
    do {
        *p = *ot | 0x10000000;
    } while (0);
    __asm__ volatile("");
    *ot = (u32)p;
    __asm__ volatile("");
    p++;
    __asm__ volatile("");
    *p++ = 0xA0000000;
    __asm__ volatile("");
    *p++ = 0x01000380;
    __asm__ volatile("");
    *p++ = 0x60004;
    __asm__ volatile("");
    *p++ = *src++;
    *p++ = *src++;
    *p++ = *src++;
    *p++ = *src++;
    *p++ = *src++;
    *p++ = *src++;
    *p++ = *src++;
    *p++ = *src++;
    *p++ = *src++;
    *p++ = *src++;
    *p++ = *src++;
    *p++ = *src++;
    *p++ = 0x01000000;
    __asm__ volatile("");
    ot2 = D_800ED8C8 + idx;
    __asm__ volatile("");
    *p = *ot2 | 0x10000000;
    __asm__ volatile("");
    *ot2 = (u32)p;
    __asm__ volatile("");
    p++;
    __asm__ volatile("");
    *p++ = 0xA0000000;
    __asm__ volatile("");
    *p++ = 0x01060380;
    __asm__ volatile("");
    *p++ = 0x60004;
    __asm__ volatile("");
    *p++ = *src++;
    *p++ = *src++;
    *p++ = *src++;
    *p++ = *src++;
    *p++ = *src++;
    *p++ = *src++;
    *p++ = *src++;
    *p++ = *src++;
    *p++ = *src++;
    *p++ = *src++;
    *p++ = *src++;
    *p++ = *src++;
    *p++ = 0x01000000;
    __asm__ volatile("");
    ot3 = D_800ED8C8 + idx;
    __asm__ volatile("");
    *p = *ot3 | 0x10000000;
    __asm__ volatile("");
    *ot3 = (u32)p;
    __asm__ volatile("");
    p++;
    __asm__ volatile("");
    *p++ = 0xA0000000;
    __asm__ volatile("");
    *p++ = 0x010C0380;
    __asm__ volatile("");
    *p++ = 0x60004;
    __asm__ volatile("");
    *p++ = *src++;
    *p++ = *src++;
    *p++ = *src++;
    *p++ = *src++;
    *p++ = *src++;
    *p++ = *src++;
    *p++ = 0;
    __asm__ volatile("");
    *p++ = 0;
    __asm__ volatile("");
    *p++ = 0;
    __asm__ volatile("");
    *p++ = 0;
    __asm__ volatile("");
    *p++ = 0;
    __asm__ volatile("");
    *p++ = 0;
    __asm__ volatile("");
    *p++ = 0x01000000;
    __asm__ volatile("");
    D_800BF544 = p;
}

void f_DrawSmallMenuText(s16 x, s32 y, s16 c, s32 d, s32 e)
{
    D_1F800180 = -0x20;
    f_DrawMenuTextGlyphs(x | (y << 16), 0x80008, c, d, e);
}

void f_DrawTallMenuText(s16 x, s32 y, s16 c, s32 d, s32 e)
{
    D_1F800180 = 0x20;
    f_DrawMenuTextGlyphs(x | (y << 16), 0x100008, c, d, e);
}

s32 f_CalculateCenteredTextPositions(char **lines, s32 n, s32 *xs)
{
    s32 min = 0xA0;
    s32 i;
    s32 x;

    for (i = 0; i < n; i++) {
        x = 0xA0 - (strlen(lines[i]) >> 1) * 8;
        xs[i] = x;
        if (x < min) {
            min = x;
        }
    }
    return min - 0x10;
}

void func_80079464(s32 demo)
{
    D_1F80017C_0fe7 = 0;
    srand(0x45);
    D_800ECF54_4583[1] = 0;
    D_800ECF54_4583[0] = 0;
    D_800BED8C = 1;
    D_800BED88_191b = (u8 *)0x80157000 + (demo << 10);
}

void func_800794C8(void)
{
    u16 *p;
    u16 t;

    if (--D_800BED8C == 0) {
        p = D_800BED88;
        if (p[1] == 0) {
            p += 2;
        }
        D_800ECF54_4583[0] = p[0];
        t = p[1];
        p += 2;
        D_800BED88 = p;
        D_800BED8C = t;
    }
}

s32 func_80079528(u8 *arg0) {
    s32 var_v1;
    u8 *var_a0;

    var_a0 = arg0;
    var_v1 = 0;
    if (*var_a0 != 0) {
        do {
            var_a0 += 1;
            var_v1 += 1;
        } while (*var_a0 != 0);
    }
    return var_v1;
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_80079554);

u8 f_FormatIntegerText(s32 v, char *out)
{
    char buf[16];
    u8 n = (u32)v >> 31;
    char *p = buf;
    s32 d;

    do {
        d = v % 10;
        if (d < 0) {
            d = -d;
        }
        *p++ = d + '0';
        v /= 10;
    } while (v != 0);
    if (n != 0) {
        *p++ = '-';
    }
    n = p - buf;
    for (p--; p >= buf; p--) {
        *out++ = *p;
    }
    *out = 0;
    return n;
}

extern u8 D_800BF9D4;
extern u8 D_1F80027E_1248;
extern s32 D_1F800248;
extern u8 D_1F800246;
extern s32 D_1F80024C;
extern u8 D_1F800250;
extern u8 D_1F800259;
extern u8 D_1F80025A;
extern u8 D_1F80025B;
extern s32 D_1F800214_f5da;
extern u8 D_1F80023B_0a71;
void f_SetDoubleBufferedClearColor(u8 r, u8 g, u8 b);
void func_800796DC(void)
{
    u8 c;
    s32 v;

    memset(D_800BF808, 0, 0x68);
    D_800BF808[0x29] = 0xFF;
    D_800BF808[0x28] = 0xFF;
    D_1F80027E_1248 = 0;
    D_1F800248 = 0;
    D_1F800246 = 0;
    D_1F80024C = 0;
    D_1F800250 = 0;
    D_1F800259 = 0;
    D_1F80025A = 0;
    D_1F80025B = 0;
    D_1F80027A = 0;
    D_1F800230_d8aa = 0;
    D_800BF808[7] = 1;
    D_1F800136 = 0;
    D_1F800137_104c = 0;
    D_1F800184 = 0;
    D_1F800214_f5da = 0;
    D_1F800208 = 0;
    D_1F800280 = 0;
    D_1F800231 = 0;
    D_1F800251 = 0;
    D_1F800232 = 0;
    D_1F800253 = 0;
    D_1F800233_33a2 = 0;
    D_1F80023B_0a71 = 0;
    f_UnlockWarpDestinationAndAreaDoor(D_800BF870.unk0, D_800BF870.pad1[0]);
    func_800508A8();
    c = D_1F800236_18be;
    v = 0;
    if (c != 0 && (u32)(c - 7) >= 2) {
        v = 0xFF;
    }
    ((void (*)(s32, s32, s32))f_SetDoubleBufferedClearColor)(v, v, v);
    D_800BF9D4 = 0;
}

INCLUDE_ASM("asm/main/nonmatchings/main", f_NewGameSetDefaultValues);

extern u8 *D_800F23A8_c058;
typedef struct Pool88_98f8 { u8 pad0[0xC]; u8 c; u8 padD[0x17]; struct Pool88_98f8 *next; u8 type; u8 pad29[0x5F]; } Pool88_98f8;
extern Pool88_98f8 D_800ED8D8[52];
extern Pool88_98f8 *D_800E8098_3d1a;
typedef struct PoolC4_98f8 { u8 pad0[0xC]; u8 c; u8 padD[0x17]; struct PoolC4_98f8 *next; u8 type; u8 pad29[0x9B]; } PoolC4_98f8;
extern PoolC4_98f8 D_800EF478[58];
extern PoolC4_98f8 *D_800E80A0_8bd4;
extern u8 D_800E7E7D;
typedef struct PoolD0_98f8 { u8 pad0[0xC]; u8 c; u8 padD[0x17]; struct PoolD0_98f8 *next; u8 type; u8 pad29[0xA7]; } PoolD0_98f8;
extern PoolD0_98f8 D_800FE198[42];
extern PoolD0_98f8 *D_800F2398_86a8;
extern u8 D_800ED8CC;
typedef struct Pool108_98f8 { u8 pad0[0xC]; u8 c; u8 padD[0x17]; struct Pool108_98f8 *next; u8 type; u8 pad29[0xDF]; } Pool108_98f8;
extern Pool108_98f8 D_800FB858[40];
extern Pool108_98f8 *D_800ED8D4_e488;
extern u8 D_800ED8C5;
typedef struct Pool140_98f8 { u8 pad0[0xC]; u8 c; u8 padD[0x17]; struct Pool140_98f8 *next; u8 type; u8 pad29[0x117]; } Pool140_98f8;
extern Pool140_98f8 D_800FB218[5];
extern Pool140_98f8 *D_800ED8D0_6a4c;
extern u8 D_800ED8C4;
extern u8 D_800F2410_a6e3[];
extern u8 D_800F26C8_05e2[];
extern u8 D_800F2738_371f[];
void func_800798F8(void)
{
    s32 i;
    u8 k;

    D_800FB168 = 0;
    D_800F23A8_c058 = 0;
    D_800F2624_9bdb = 0;
    D_800F239C = 0;
    for (i = 0; i < 0x34; i++) {
        memset(&D_800ED8D8[i], 0, sizeof(D_800ED8D8[i]));
        D_800ED8D8[i].next = &D_800ED8D8[i + 1];
        D_800ED8D8[i].type = 0;
        D_800ED8D8[i].c = 0;
    }
    D_800ED8D8[i - 1].next = 0;
    D_800E8098_3d1a = D_800ED8D8;
    D_800E7E7C = 0x34;
    i = 0;
    k = 1;
    for (; i < 0x3A; i++) {
        memset(&D_800EF478[i], 0, sizeof(D_800EF478[i]));
        D_800EF478[i].next = &D_800EF478[i + 1];
        D_800EF478[i].type = k;
        D_800EF478[i].c = 0;
    }
    D_800EF478[i - 1].next = 0;
    D_800E80A0_8bd4 = D_800EF478;
    D_800E7E7D = 0x3A;
    i = 0;
    k = 2;
    for (; i < 0x2A; i++) {
        memset(&D_800FE198[i], 0, sizeof(D_800FE198[i]));
        D_800FE198[i].next = &D_800FE198[i + 1];
        D_800FE198[i].type = k;
        D_800FE198[i].c = 0;
    }
    D_800FE198[i - 1].next = 0;
    D_800F2398_86a8 = D_800FE198;
    D_800ED8CC = 0x2A;
    i = 0;
    k = 3;
    for (; i < 0x28; i++) {
        memset(&D_800FB858[i], 0, sizeof(D_800FB858[i]));
        D_800FB858[i].next = &D_800FB858[i + 1];
        D_800FB858[i].type = k;
        D_800FB858[i].c = 0;
    }
    D_800FB858[i - 1].next = 0;
    D_800ED8D4_e488 = D_800FB858;
    D_800ED8C5 = 0x28;
    i = 0;
    k = 4;
    for (; i < 0x5; i++) {
        memset(&D_800FB218[i], 0, sizeof(D_800FB218[i]));
        D_800FB218[i].next = &D_800FB218[i + 1];
        D_800FB218[i].type = k;
        D_800FB218[i].c = 0;
    }
    D_800FB218[i - 1].next = 0;
    D_800ED8D0_6a4c = D_800FB218;
    D_800ED8C4 = 0x5;
    *(u8 **)D_1F80013C = D_800F2410_a6e3;
    *(u8 **)D_1F800140 = D_800F2410_a6e3;
    *(s16 *)D_1F800146 = 0;
    *(s16 *)D_1F800144 = 0;
    *(u8 **)D_1F800148 = D_800F26C8_05e2;
    *(u8 **)D_1F80014C = D_800F26C8_05e2;
    *(s16 *)D_1F800152 = 0;
    *(s16 *)D_1F800150 = 0;
    *(u8 **)D_1F800154 = D_800F2738_371f;
    *(u8 **)D_1F800158 = D_800F2738_371f;
    *(s16 *)D_1F80015E = 0;
    *(s16 *)D_1F80015C = 0;
}

typedef struct FreeNodeA_8313 { u8 kind0; u8 pad1[9]; u8 uA; u8 padB; u8 uC; u8 padD[0x13]; struct FreeNodeA_8313 *prev; struct FreeNodeA_8313 *next; } FreeNodeA_8313;
extern FreeNodeA_8313 *D_800F2398_0c73;
extern FreeNodeA_8313 *D_800F239C_ee60;
extern FreeNodeA_8313 *D_800F23A0_43a0;
extern FreeNodeA_8313 *D_800F23A8_14aa;
extern FreeNodeA_8313 *D_800F2624_cee9;
extern FreeNodeA_8313 *D_800F2738_e681;
extern FreeNodeA_8313 *D_800FB168_2285;
extern FreeNodeA_8313 *D_800E8098_a875;
extern FreeNodeA_8313 *D_800E80A0_2bca;
FreeNodeA_8313 *f_AllocateActorFromPool2(FreeNodeA_8313 *at, u8 kind, s32 mode, s32 list);
FreeNodeA_8313 *f_AllocateActorFromPool0(FreeNodeA_8313 *at, u8 kind, s32 mode, s32 list)
{
    FreeNodeA_8313 *a;
    FreeNodeA_8313 **head;
    FreeNodeA_8313 **tail;

    if (D_800E7E7C >= 3) {
        a = D_800E8098_a875;
        D_800E7E7C--;
        D_800E8098_a875 = a->next;
        switch (list) {
        case 0:
        default:
            head = &D_800FB168_2285;
            tail = &D_800F23A8_14aa;
            break;
        case 1:
            head = &D_800F2624_cee9;
            tail = &D_800F239C_ee60;
            break;
        case 2:
            head = &D_800F2738_e681;
            tail = &D_800F23A0_43a0;
            break;
        }
        switch (mode) {
        case 0:
            if (at->prev != NULL) {
                a->prev = at->prev;
                a->next = at;
                at->prev->next = a;
                at->prev = a;
                break;
            }
        case 1:
            a->prev = NULL;
            a->next = *head;
            if (*head == NULL) {
                *tail = a;
            } else {
                (*head)->prev = a;
            }
            *head = a;
            break;
        case 2:
            if (at->next != NULL) {
                a->prev = at;
                a->next = at->next;
                at->next->prev = a;
                at->next = a;
                break;
            }
        case 3:
            a->prev = *tail;
            a->next = NULL;
            if (*tail == NULL) {
                *head = a;
            } else {
                (*tail)->next = a;
            }
            *tail = a;
            break;
        }
        a->uA = list;
        a->kind0 = 2;
        a->uC = kind;
        return a;
    }
    return NULL;
}

FreeNodeA_8313 *f_AllocateActorFromPool1(FreeNodeA_8313 *at, u8 kind, s32 mode, s32 list)
{
    FreeNodeA_8313 *a = D_800E80A0_2bca;
    FreeNodeA_8313 **head;
    FreeNodeA_8313 **tail;

    if (a != NULL) {
        D_800E7E7D--;
        D_800E80A0_2bca = a->next;
        switch (list) {
        case 0:
        default:
            head = &D_800FB168_2285;
            tail = &D_800F23A8_14aa;
            break;
        case 1:
            head = &D_800F2624_cee9;
            tail = &D_800F239C_ee60;
            break;
        case 2:
            head = &D_800F2738_e681;
            tail = &D_800F23A0_43a0;
            break;
        }
        switch (mode) {
        case 0:
            if (at->prev != NULL) {
                a->prev = at->prev;
                a->next = at;
                at->prev->next = a;
                at->prev = a;
                break;
            }
        case 1:
            a->prev = NULL;
            a->next = *head;
            if (*head == NULL) {
                *tail = a;
            } else {
                (*head)->prev = a;
            }
            *head = a;
            break;
        case 2:
            if (at->next != NULL) {
                a->prev = at;
                a->next = at->next;
                at->next->prev = a;
                at->next = a;
                break;
            }
        case 3:
            a->prev = *tail;
            a->next = NULL;
            if (*tail == NULL) {
                *head = a;
            } else {
                (*tail)->next = a;
            }
            *tail = a;
            break;
        }
        a->uA = list;
        a->kind0 = 2;
        a->uC = kind;
        return a;
    }
    return f_AllocateActorFromPool2(at, kind, mode, list);
}

extern FreeNodeA_8313 *D_800ED8D4_34bd;
extern FreeNodeA_8313 *D_800ED8D0_f3a6;
extern FreeNodeA_8313 *D_800F23A0;
FreeNodeA_8313 *f_AllocateActorFromPool2(FreeNodeA_8313 *at, u8 kind, s32 mode, s32 list)
{
    FreeNodeA_8313 *a = D_800F2398_0c73;
    FreeNodeA_8313 **head;
    FreeNodeA_8313 **tail;

    if (a != NULL) {
        D_800ED8CC--;
        D_800F2398_0c73 = a->next;
        switch (list) {
        case 0:
        default:
            head = &D_800FB168_2285;
            tail = &D_800F23A8_14aa;
            break;
        case 1:
            head = &D_800F2624_cee9;
            tail = &D_800F239C_ee60;
            break;
        case 2:
            head = &D_800F2738_e681;
            tail = &D_800F23A0;
            break;
        }
        switch (mode) {
        case 0:
            if (at->prev != NULL) {
                a->prev = at->prev;
                a->next = at;
                at->prev->next = a;
                at->prev = a;
                break;
            }
        case 1:
            a->prev = NULL;
            a->next = *head;
            if (*head == NULL) {
                *tail = a;
            } else {
                (*head)->prev = a;
            }
            *head = a;
            break;
        case 2:
            if (at->next != NULL) {
                a->prev = at;
                a->next = at->next;
                at->next->prev = a;
                at->next = a;
                break;
            }
        case 3:
            a->prev = *tail;
            a->next = NULL;
            if (*tail == NULL) {
                *head = a;
            } else {
                (*tail)->next = a;
            }
            *tail = a;
            break;
        }
        a->uA = list;
        a->kind0 = 2;
        a->uC = kind;
        return a;
    }
    return NULL;
}

FreeNodeA_8313 *f_AllocateActorFromPool3(FreeNodeA_8313 *at, u8 kind, s32 mode, s32 list)
{
    FreeNodeA_8313 *a = D_800ED8D4_34bd;
    FreeNodeA_8313 **head;
    FreeNodeA_8313 **tail;

    if (a != NULL) {
        D_800ED8C5--;
        D_800ED8D4_34bd = a->next;
        switch (list) {
        case 0:
        default:
            head = &D_800FB168_2285;
            tail = &D_800F23A8_14aa;
            break;
        case 1:
            head = &D_800F2624_cee9;
            tail = &D_800F239C_ee60;
            break;
        case 2:
            head = &D_800F2738_e681;
            tail = &D_800F23A0;
            break;
        }
        switch (mode) {
        case 0:
            if (at->prev != NULL) {
                a->prev = at->prev;
                a->next = at;
                at->prev->next = a;
                at->prev = a;
                break;
            }
        case 1:
            a->prev = NULL;
            a->next = *head;
            if (*head == NULL) {
                *tail = a;
            } else {
                (*head)->prev = a;
            }
            *head = a;
            break;
        case 2:
            if (at->next != NULL) {
                a->prev = at;
                a->next = at->next;
                at->next->prev = a;
                at->next = a;
                break;
            }
        case 3:
            a->prev = *tail;
            a->next = NULL;
            if (*tail == NULL) {
                *head = a;
            } else {
                (*tail)->next = a;
            }
            *tail = a;
            break;
        }
        a->uA = list;
        a->kind0 = 2;
        a->uC = kind;
        return a;
    }
    return NULL;
}

FreeNodeA_8313 *f_AllocateActorFromPool4(FreeNodeA_8313 *at, u8 kind, s32 mode, s32 list)
{
    FreeNodeA_8313 *a = D_800ED8D0_f3a6;
    FreeNodeA_8313 **head;
    FreeNodeA_8313 **tail;

    if (a != NULL) {
        D_800ED8C4--;
        D_800ED8D0_f3a6 = a->next;
        switch (list) {
        case 0:
        default:
            head = &D_800FB168_2285;
            tail = &D_800F23A8_14aa;
            break;
        case 1:
            head = &D_800F2624_cee9;
            tail = &D_800F239C_ee60;
            break;
        case 2:
            head = &D_800F2738_e681;
            tail = &D_800F23A0;
            break;
        }
        switch (mode) {
        case 0:
            if (at->prev != NULL) {
                a->prev = at->prev;
                a->next = at;
                at->prev->next = a;
                at->prev = a;
                break;
            }
        case 1:
            a->prev = NULL;
            a->next = *head;
            if (*head == NULL) {
                *tail = a;
            } else {
                (*head)->prev = a;
            }
            *head = a;
            break;
        case 2:
            if (at->next != NULL) {
                a->prev = at;
                a->next = at->next;
                at->next->prev = a;
                at->next = a;
                break;
            }
        case 3:
            a->prev = *tail;
            a->next = NULL;
            if (*tail == NULL) {
                *head = a;
            } else {
                (*tail)->next = a;
            }
            *tail = a;
            break;
        }
        a->uA = list;
        a->kind0 = 2;
        a->uC = kind;
        return a;
    }
    return NULL;
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007A464);

typedef struct FreeNodeA { u8 kind0; u8 pad1[9]; u8 uA; u8 padB; u8 uC; u8 padD[0x13]; struct FreeNodeA *prev; struct FreeNodeA *next; } FreeNodeA_A5A8;
extern FreeNodeA_A5A8 *D_800E8098_a5a8;
extern FreeNodeA_A5A8 *D_800F239C_a5a8;
extern FreeNodeA_A5A8 *D_800F2624_a5a8;
FreeNodeA_A5A8 *f_AllocatePresentationActor(u8 kind)
{
    FreeNodeA_A5A8 *a = D_800E8098_a5a8;
    FreeNodeA_A5A8 *next;
    FreeNodeA_A5A8 **tail;

    if (a != NULL) {
        next = a->next;
        a->next = NULL;
        D_800E7E7C--;
        D_800E8098_a5a8 = next;
        tail = &D_800F239C_a5a8;
        a->prev = *tail;
        if (*tail == NULL) {
            D_800F2624_a5a8 = a;
        } else {
            (*tail)->next = a;
        }
        *tail = a;
        a->uA = 1;
        a->kind0 = 2;
        a->uC = kind;
        return a;
    }
    return NULL;
}

typedef struct FreeNode { u8 pad0[0x20]; struct FreeNode *prev; struct FreeNode *next; u8 pad28[0x40]; } FreeNode;
extern FreeNode *D_800F2624_de6d;
extern FreeNode *D_800F239C_5f1e;
extern FreeNode *D_800FB168_adca;
extern FreeNode *D_800F23A8;
extern FreeNode *D_800E8098_af1b;
extern FreeNode *D_800E80A0;
extern FreeNode *D_800F2398;
extern FreeNode *D_800ED8D4;
extern FreeNode *D_800ED8D0;
s32 f_ResolveEffectEightByteStreamPayload(FreeNode *a)
{
    FreeNode **head;
    FreeNode **tail;

    if (((u8 *)a)[0xA] != 0) {
        head = &D_800F2624_de6d;
        tail = &D_800F239C_5f1e;
    } else {
        head = &D_800FB168_adca;
        tail = &D_800F23A8;
    }
    if (a->prev != NULL) {
        a->prev->next = a->next;
    } else {
        *head = a->next;
        if (a->next != NULL) {
            a->next->prev = NULL;
        }
    }
    if (a->next != NULL) {
        a->next->prev = a->prev;
    } else {
        *tail = a->prev;
        if (a->prev != NULL) {
            a->prev->next = NULL;
        }
    }
    ((u8 *)a)[0x28] &= 0x7F;
    switch (((u8 *)a)[0x28]) {
    case 0:
        D_800E7E7C++;
        a->next = D_800E8098_af1b;
        D_800E8098_af1b = a;
        break;
    case 1:
        D_800E7E7D++;
        a->next = D_800E80A0;
        D_800E80A0 = a;
        f_ReleaseActorModelParts(a);
        break;
    case 2:
        D_800ED8CC++;
        a->next = D_800F2398;
        D_800F2398 = a;
        f_ReleaseActorModelParts(a);
        break;
    case 3:
        D_800ED8C5++;
        a->next = D_800ED8D4;
        D_800ED8D4 = a;
        f_ReleaseActorModelParts(a);
        break;
    case 4:
        D_800ED8C4++;
        a->next = D_800ED8D0;
        D_800ED8D0 = a;
        f_ReleaseActorModelParts(a);
        break;
    }
    *(s32 *)((u8 *)a + 0x0) = 0;
    *(s32 *)((u8 *)a + 0x4) = 0;
    *(s32 *)((u8 *)a + 0x8) = 0;
    *(s32 *)((u8 *)a + 0xC) = 0;
    *(s32 *)((u8 *)a + 0x10) = 0;
    *(s32 *)((u8 *)a + 0x14) = 0;
    *(s32 *)((u8 *)a + 0x18) = 0;
    *(s32 *)((u8 *)a + 0x38) = 0;
    ((u8 *)a)[0x2A] = 0;
    ((u8 *)a)[0x2B] = 0;
    ((u8 *)a)[0x29] = 0;
    ((u8 *)a)[0x5E] = 0;
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007A810);

extern s8 D_1F80017C[];
void func_8007A8E0(void) {
    f_NewGameSetDefaultValues();
    *((s16 *)D_1F80017C) = 0;
}

void func_8007A904(void)
{
    u8 *a;
    u8 *n;

    for (a = D_800FB168; a != 0; a = n) {
        n = *(u8 **)(a + 0x24);
        a[1] = 0;
        (*(void (**)(u8 *))(a + 0x1C))(a);
    }
    for (a = D_800F2624_9bdb; a != 0; a = n) {
        n = *(u8 **)(a + 0x24);
        a[1] = 0;
        (*(void (**)(u8 *))(a + 0x1C))(a);
    }
}

s32 f_AllocateActorRecordByType(u8 type, u8 b, s32 c)
{
    switch (type) {
    case 0:
        return f_AllocateActorFromPool0(0, b, 3, c);
    case 1:
        return f_AllocateActorFromPool1(0, b, 3, c);
    case 2:
        return f_AllocateActorFromPool2(0, b, 3, c);
    case 3:
        return f_AllocateActorFromPool3(0, b, 3, c);
    case 4:
        return f_AllocateActorFromPool4(0, b, 3, c);
    }
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007AA38);

s32 f_AllocateActorModelPart(void)
{
    s32 *p;

    if (D_800ED098 > 0) {
        D_800ED098--;
        return *D_800E7E74++;
    }
    return 0;
}

void func_8007AB20(void) {
    func_8007A464(0, 3);
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007AB44);

extern M2C_UNK D_800E8008;
void func_8007AC14(void) {
    memset(&D_800E8008, 0, 0x90);
}

extern M2C_UNK D_800F2418;
void func_8007AC40(void) {
    memset(&D_800F2418, 0, 0x20C);
}

extern M2C_UNK D_80100660;
void func_8007AC6C(void) {
    memset(&D_80100660, 0, 0x30);
}

extern M2C_UNK D_800ED018;
void func_8007AC98(void) {
    memset(&D_800ED018, 0, 0x3C);
}

void func_8007ACC4(void)
{
    s32 i;
    Slot4Cb *s;

    for (i = 0, s = D_80100400_fb37; i < 8; i++, s++) {
        memset(s, 0, sizeof(Slot4Cb));
    }
}

extern M2C_UNK D_800ED058;
void func_8007AD14(void) {
    memset(&D_800ED058, 0, 0x40);
}

void func_8007AD40(void)
{
    s32 i;

    memset(D_800EC188_d83b, 0, 0xA00);
    for (i = 0; i < 40; i++) {
        D_800EC188_d83b[i].index = i & 7;
        D_800EC188_d83b[i].scale = 0x1000;
    }
}

Slot4C *func_8007AD98(void)
{
    Slot4C *s = D_80100400;
    s32 i;

    for (i = 0; i < 8; i++, s++) {
        if (s->used == 0) {
            return s;
        }
    }
    return NULL;
}

void f_RetireSceneController(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0) = 0;
    M2C_FIELD(arg0, s32 *, 4) = 0;
}

void f_ReleaseActorModelParts(u8 *a)
{
    s32 n = a[9];

    while (n != 0) {
        n--;
        D_800ED098++;
        *--D_800E7E74 = ((s32 *)(a + 0xC0))[n];
    }
    a[9] = 0;
}

extern u8 *D_800F23A0_9c78;
#define LNK_NEXT(p) (*(u8 **)((p) + 0x20))
#define LNK_PREV(p) (*(u8 **)((p) + 0x24))
void func_8007AE30(u8 *at, u8 *n, s32 mode, s32 list)
{
    u8 **tail;
    u8 **head;

    switch (list) {
    case 0:
    default:
        tail = &D_800FB168;
        head = &D_800F23A8_c058;
        break;
    case 1:
        tail = &D_800F2624_9bdb;
        head = &D_800F239C;
        break;
    case 2:
        tail = &D_800F2738_2edb;
        head = &D_800F23A0_9c78;
        break;
    }
    switch (mode) {
    case 0:
        if (LNK_NEXT(at) != NULL) {
            LNK_NEXT(n) = LNK_NEXT(at);
            LNK_PREV(n) = at;
            LNK_PREV(LNK_NEXT(at)) = n;
            LNK_NEXT(at) = n;
            return;
        }
    case 1:
        LNK_NEXT(n) = NULL;
        LNK_PREV(n) = *tail;
        if (*tail == NULL) {
            *head = n;
        } else {
            LNK_NEXT(*tail) = n;
        }
        *tail = n;
        return;
    case 2:
        if (LNK_PREV(at) != NULL) {
            LNK_NEXT(n) = at;
            LNK_PREV(n) = LNK_PREV(at);
            LNK_NEXT(LNK_PREV(at)) = n;
            LNK_PREV(at) = n;
            return;
        }
    case 3:
        LNK_NEXT(n) = *head;
        LNK_PREV(n) = NULL;
        if (*head == NULL) {
            *tail = n;
        } else {
            LNK_PREV(*head) = n;
        }
        *head = n;
        return;
    }
}

void func_8007AF88(u8 *a, u8 **head, u8 **tail)
{
    u8 *prev = *(u8 **)(a + 0x20);

    if (prev != 0) {
        *(u8 **)(prev + 0x24) = *(u8 **)(a + 0x24);
    } else {
        *head = *(u8 **)(a + 0x24);
        if (*(u8 **)(a + 0x24) != 0) {
            *(u8 **)(*(u8 **)(a + 0x24) + 0x20) = 0;
        }
    }
    if (*(u8 **)(a + 0x24) != 0) {
        *(u8 **)(*(u8 **)(a + 0x24) + 0x20) = *(u8 **)(a + 0x20);
    } else {
        *tail = *(u8 **)(a + 0x20);
        if (*(u8 **)(a + 0x20) != 0) {
            *(u8 **)(*(u8 **)(a + 0x20) + 0x24) = 0;
        }
    }
}

void func_8007B008(void)
{
    Linked *a = D_800F2624;
    Linked *next;

    while (a != NULL) {
        next = a->next;
        a->active = 0;
        a->callback(a);
        a = next;
    }
}

void func_8007B04C(void)
{
    u8 *a;
    u8 *n;

    for (a = D_800FB168; a != 0; a = n) {
        n = *(u8 **)(a + 0x24);
        a[1] = 0;
        if (a[0x28] & 0x80) {
            (*(void (**)(u8 *))(a + 0x1C))(a);
        }
    }
    for (a = D_800F2624_9bdb; a != 0; a = n) {
        n = *(u8 **)(a + 0x24);
        a[1] = 0;
        if (a[0x28] & 0x80) {
            (*(void (**)(u8 *))(a + 0x1C))(a);
        }
    }
}

void func_8007B0F0(void)
{
    s32 i = 0;
    u8 *p = D_800F2740;
    u8 *q;

    for (; i < 0x208; i++, p += 0x44) {
        memset(p, 0, 0x44);
    }
    q = D_800FB11C;
    D_800E7E74 = (s32 *)D_800ED8C0;
    for (i = 0; i < 0x208; i++, q -= 0x44) {
        *--D_800E7E74 = (s32)q;
    }
    D_800ED098 = 0x208;
}

/* func_8007B0F0, inlined */
static inline void Init_B0F0(void)
{
    s32 i = 0;
    u8 *p = D_800F2740;
    u8 *q;

    for (; i < 0x208; i++, p += 0x44) {
        memset(p, 0, 0x44);
    }
    q = D_800FB11C;
    D_800E7E74 = (s32 *)D_800ED8C0;
    for (i = 0; i < 0x208; i++, q -= 0x44) {
        *--D_800E7E74 = (s32)q;
    }
    D_800ED098 = 0x208;
}
void func_8007B18C(void)
{
    func_8004FB20();
    func_800798F8();
    Init_B0F0();
    func_8007ACC4();
    func_8007A810();
    func_8007AC14();
    func_8007AC40();
    func_8007AC6C();
    func_8007AC98();
    func_8007AD14();
    func_8007AD40();
}

Slot40 *f_AllocateTemplateEffectSlot(void)
{
    s32 i = 0;
    u32 one = 1;
    Slot40 *s = D_800EC188_44f3;

    for (; i < 0x28; i++, s++) {
        if (s->used == 0) {
            s->used = one;
            return s;
        }
    }
    return NULL;
}

void func_8007B2AC(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0) = 0;
    M2C_FIELD(arg0, s32 *, 4) = 0;
    M2C_FIELD(arg0, s16 *, 0xC) = 0x1000;
}

void func_8007B2C0(s32 reverse)
{
    if (reverse == 0) {
        D_1F800170 = 0x8000;
        D_1F800172_5cdb = 0x4000;
        D_1F800174_de41 = 0x2000;
        D_1F800176 = 0x1000;
    } else {
        D_1F800170 = 0x1000;
        D_1F800172_5cdb = 0x2000;
        D_1F800174_de41 = 0x4000;
        D_1F800176 = 0x8000;
    }
}

extern M2C_UNK D_800FB160;
void func_8007B328(void) {
    memset(&D_800FB160, 0, 8);
    M2C_FIELD(&D_800FB160, s8 *, 1) = 1;
    M2C_FIELD(&D_800FB160, s8 *, 4) = 7;
    M2C_FIELD(&D_800FB160, s8 *, 2) = 0;
    M2C_FIELD(&D_800FB160, s8 *, 3) = 0;
    M2C_FIELD(&D_800FB160, s8 *, 5) = 9;
    M2C_FIELD(&D_800FB160, s8 *, 6) = 0;
    M2C_FIELD(&D_800FB160, s8 *, 7) = 0;
    func_8007B2C0(0);
}

void func_8007B38C(void)
{
    u8 *g = (u8 *)&D_800BF870;
    u8 *s = D_800FB160_9a03;

    g[0x5DC] = s[6];
    g[0x33] = s[1];
    g[0x5DE] = s[2];
    g[0x5DF] = s[3];
    g[0x1A] = s[4];
    g[0x1B] = s[5];
    g[0x5DD] = s[7];
    func_8007B2C0(g[0x5DC]);
}

void func_8007B3F4(void)
{
    u8 *s = D_800FB160_9a03;
    u8 *g = (u8 *)&D_800BF870;

    s[6] = g[0x5DC];
    s[1] = g[0x33];
    s[2] = g[0x5DE];
    s[3] = g[0x5DF];
    s[4] = g[0x1A];
    s[5] = g[0x1B];
    s[7] = g[0x5DD];
    func_8007B2C0(s[6]);
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007B45C);

void func_8007BE18(u8 a)
{
    switch (*(u16 *)(*(u8 **)D_1F800138 + 0x50)) {
    case 0:
        func_8018FA88(a);
        break;
    case 1:
        func_8018FBCC();
        break;
    case 2:
        f_PlaySoundEffect(0x14, -9, 0);
        (*(u8 **)D_1F800138)[0x6B] = 1;
        D_800BF808[0] = 1;
        D_1F800136 = 1;
        *(u16 *)(*(u8 **)D_1F800138 + 0x50) = 0;
        break;
    case 3:
        f_PlaySoundEffect(0x11, 0, 0);
        (*(u8 **)D_1F800138)[0x6B] = 2;
        *(u16 *)(*(u8 **)D_1F800138 + 0x50) = 0;
        break;
    case 4:
        (*(u8 **)D_1F800138)[0x6B] = 7;
        *(u16 *)(*(u8 **)D_1F800138 + 0x50) = 0;
        break;
    case 5:
        f_PlaySoundEffect(0x11, 0, 0);
        (*(u8 **)D_1F800138)[0x6B] = 9;
        *(u16 *)(*(u8 **)D_1F800138 + 0x50) = 0;
        break;
    }
}

void func_8007BE18(u8 a);
s32 f_ControlStreamedAudioTrack(s32 track);
void func_80045558(s32 arg0, s32 arg1, s32 arg2, void *arg3);
void func_8007BF20(s32 a, s32 b)
{
    s32 v;

    switch (D_800BF84A) {
    case 0:
        f_StopVoicePlayback();
        ((void (*)(s32))func_80045558)(1);
        D_800BF808[0x42]++;
        if (b == 0) {
            ((s32 (*)(s32, s32))f_ControlStreamedAudioTrack)(0xC, 1);
            break;
        }
        if (D_1F800137_104c == 1) {
            break;
        }
        ((s32 (*)(s32, s32))f_ControlStreamedAudioTrack)(D_1F80023B_0a71, 1);
        break;
    case 1:
        ((void (*)(s32))func_8007BE18)(a);
        if (*(u16 *)(*(u8 **)D_1F800138 + 0x50) < 2) {
            break;
        }
        if (b == 0) {
            D_800BF84A = 3;
            break;
        }
        D_800BF808[0x42]++;
        f_StopVoicePlayback();
        break;
    case 2:
        v = func_80045580(1);
        goto chk;
    case 3:
        v = D_1F80019B_e707;
    chk:
        if (v != 0) {
            D_800BF808[0x42]++;
        }
        break;
    case 4:
        ((void (*)(s32))func_8007BE18)(a);
        if ((a != 0 || (*(u8 **)D_1F800138)[0x6B] != 7) && b == 1 && D_1F800137_104c != 1) {
            ((s32 (*)(s32, s32))f_ControlStreamedAudioTrack)(D_1F80023B_0a71, 1);
        }
        D_800BF84A = 0;
        break;
    }
}

s32 func_8007C0D0(u8 *a, s32 b)
{
    while (**(u8 **)(a + 0x14) != 0xFF) {
        if (**(u8 **)(a + 0x14) < 0xC0) {
            if (b == 1) {
                func_8007D0D0(a);
                a[5] = b;
                *(u8 **)(a + 0x14) += 1;
                a[0x2A] += 1;
                return 1;
            }
        } else {
            switch (**(u8 **)(a + 0x14)) {
            case 0xC0 ... 0xD0:
                if (b == 1) {
                    func_8007D0D0(a);
                    a[5] = b;
                    *(u8 **)(a + 0x14) += 1;
                    a[0x2A] += 1;
                    return 1;
                }
                break;
            case 0xF8 ... 0xF9:
                switch (a[3]) {
                case 0:
                    *(s16 *)(a + 0x42) = 0;
                    a[5] = 2;
                    break;
                case 1:
                    *(u16 *)(a + 0x42) = 0xFFFF;
                    a[5] = 3;
                    break;
                case 2:
                    *(s16 *)(a + 0x42) = 0x3C;
                    a[5] = 4;
                    break;
                case 3: case 4: case 5:
                    *(s16 *)(a + 0x42) = 0x3C;
                    a[5] = 5;
                    break;
                }
                *(u8 **)(a + 0x14) += 1;
                a[0x2A] += 1;
                return 1;
            case 0xFC:
                if (b == 1) {
                    *(s16 *)(a + 0x40) = 0xF;
                    a[5] = b;
                    *(u8 **)(a + 0x14) += 1;
                    return 1;
                }
                break;
            }
        }
        *(u8 **)(a + 0x14) += 1;
        a[0x2A] += 1;
    }
    a[5] = 2;
    *(u16 *)(a + 0x42) = 0xFFFF;
    return 0;
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007C2A4);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007C3CC);

extern u16 D_800BF9CA;
s32 func_8007C5E4(s32 arg0, s32 arg1, s32 arg2) {
    return func_8007C2A4(arg0, arg1, arg2 & 0xFF, ((D_800BF9CA + 1) | 0x80) & 0xFF, /* extra? */ 3);
}

extern u8 D_800BFA21;
s32 func_8007C620(s32 arg0, s32 arg1, s32 arg2) {
    return func_8007C2A4(arg0, arg1, arg2 & 0xFF, D_800BFA21 | 0x80, /* extra? */ 1);
}

extern u8 D_800BFA2A;
s32 func_8007C654(s32 arg0, s32 arg1, s32 arg2) {
    return func_8007C2A4(arg0, arg1, arg2 & 0xFF, D_800BFA2A | 0x80, /* extra? */ 1);
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007C688);

extern u8 D_800A58B8[];
extern u8 D_800A58C0[];
extern u8 D_800A58C8[];
extern u8 D_800A58D0[];
extern u8 D_800A58DC[];
typedef struct {
    u16 x;
    u8 c;
    u8 z;
    s16 w;
    s16 h;
} UiCell_C780;
UiCell_C780 *func_8007C780(UiCell_C780 *p, u16 *x, u8 c, s16 kind)
{
    u8 *s;
    u32 w;

    p->x = *x;
    p->c = c;
    p->z = 0;
    p->w = 8;
    p->h = 0x38;
    p++;
    p->x = *x += 8;
    p->c = c;
    p->z = 0;
    p->w = 0x80;
    p->h = 0x38;
    *x += 0x10;
    p++;
    switch (kind) {
    default:
        s = D_800A58DC;
        break;
    case 0:
        s = D_800A58B8;
        break;
    case 1:
        s = D_800A58C0;
        break;
    case 2:
        s = D_800A58C8;
        break;
    case 3:
        s = D_800A58D0;
        break;
    }
    w = *s;
    while (w != 0xFF) {
        if (w < 10) {
            w = *s * 8 + 0x80;
        } else {
            w = 0x60;
        }
        s++;
        p->x = *x;
        p->c = c;
        p->z = 0;
        p->w = w;
        p->h = 0x28;
        *x += 8;
        w = *s;
        p++;
    }
    return p;
}

Glyph_C8C8 *func_8007C8C8(Glyph_C8C8 *g, s32 c, u16 *x, u8 y)
{
    B8_C8C8 tmp = *(B8_C8C8 *)D_80016EE0_e006;

    c &= 0xFF;
    g->clut = 0x80;
    g->u = (c & 0xF) * 16;
    g->v = (c & 0xF0) + 0x78;
    g->x = *x;
    g->y = y;
    *x += 0x10;
    return g + 1;
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007C940);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007CC00);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007CDD4);

void func_8007CEEC(u8 *a, s16 *w, s16 *h)
{
    u8 *p;
    u8 c;
    s16 max;

    *w = 0;
    *h = 1;
    p = *(u8 **)(a + 0x10);
    c = *p;
    max = 0;
    if (c != 0xFF) {
        do {
            if (c >= 0xF8 && c <= 0xF9) {
                if (a[0x47] != 0 || a[3] >= 2) {
                    break;
                }
                *w += 2;
                break;
            } else if (c >= 0x60 && c <= 0xA0) {
                if (c <= 0x80) {
                    *w += 2;
                } else {
                    *w += 1;
                }
            } else if (c >= 0xCD && c <= 0xD0) {
                *w += 2;
            } else if (c >= 0xF0 && c <= 0xF7) {
            } else {
                switch (*p) {
                case 0xFA:
                    if (max < *w) {
                        max = *w;
                    }
                    *w = 0;
                    *h += 1;
                    break;
                case 0xC0: case 0xC1: case 0xC2:
                    *w += 8;
                    break;
                case 0xCA: case 0xCB:
                    *w += 4;
                    break;
                case 0xCC:
                    *w += 2;
                    break;
                case 0xC3: case 0xC9:
                    *w += 2;
                    break;
                case 0xC4:
                    *w += 9;
                    break;
                case 0xC5: case 0xC6:
                    *w += 0xA;
                    break;
                case 0xC7: case 0xC8:
                    *w += 0xC;
                    break;
                case 0xFC:
                    break;
                default:
                    *w += 1;
                    break;
                }
            }
            p++;
            c = *p;
        } while (c != 0xFF);
    }
    if (max < *w) {
        max = *w;
    }
    *w = max * 8;
    *h = *h * 16;
}

void func_8007D0D0(u8 *a)
{
    switch (a[3]) {
    case 2:
        *(s16 *)(a + 0x40) = 1;
        break;
    case 3: case 4: case 5:
        *(s16 *)(a + 0x40) = 1;
        break;
    case 0: case 1:
        switch (D_800BF8A3) {
        case 0:
            *(s16 *)(a + 0x40) = 3;
            return;
        case 1:
            *(s16 *)(a + 0x40) = 2;
            return;
        default:
            *(s16 *)(a + 0x40) = 1;
            return;
        }
    }
}

void func_8007D14C(u8 *a)
{
    *(u8 **)(a + 0x10) = *(u8 **)(a + 0x14);
    if (**(u8 **)(a + 0x14) == 0xFF) {
        a[5] = 0;
    } else {
        switch (func_8007C0D0(a, 1)) {
        case 0:
            a[5] = 0;
            break;
        case 1:
            a[0x46] |= 1;
            break;
        case 2:
            a[0x46] |= 0x81;
            break;
        }
    }
    if (a[5] != 0) {
        a[5] = 1;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007D208);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007D594);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007DA50);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007DC38);

void func_8007DDE0(u8 *a)
{
    s32 one = 1;
    s32 v;

    switch (a[4]) {
    case 0:
        a[0x18] = 7;
        v = *(s32 *)(a + 0x50) + *(u16 *)(*(u8 **)(a + 0x4C) + *(s16 *)(a + 0x5E) * 4);
        *(s32 *)(a + 0x10) = v;
        *(s32 *)(a + 0x14) = v;
        func_8007C0D0(a, 0);
        a[0x46] = one;
        a[4]++;
        D_800BF808[0x1A] |= 8;
        break;
    case 1:
        func_8007C940(a);
        func_8007CC00(a);
        func_8005019C(a + 0x54, a[0x18], 1, 2);
        break;
    case 2:
        a[4]++;
        break;
    case 3:
        D_800BF808[0x1A] &= 0xF7;
        f_ResolveEffectEightByteStreamPayload(a);
        break;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/main", f_SpawnScriptedPresentationActor);

INCLUDE_ASM("asm/main/nonmatchings/main", f_SpawnMovementHintActor);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007E110);

INCLUDE_ASM("asm/main/nonmatchings/main", f_DrawPackedUiQuadFrame);

INCLUDE_ASM("asm/main/nonmatchings/main", f_DrawPackedUiSpriteFrame);

void f_DrawUiQuadResource(s16 x, s16 y, s32 c, s32 idx)
{
    struct { u8 b0; u8 b1; s16 h2; } q;
    struct { s16 x, y; s32 z; } r;

    r.x = x;
    q.b1 = c;
    q.b0 = 0;
    q.h2 = 0;
    r.y = y;
    r.z = 0;
    f_DrawPackedUiQuadFrame(&r, ((void **)D_80017334)[(s16)idx], D_800ECF58[0], &q);
}

void f_DrawUiSpriteResource(void *res, s16 x, s16 y, u8 c, s16 idx)
{
    struct { u8 b0; u8 b1; s16 h2; } q;
    struct { s16 x, y; s32 z; } r;

    r.y = y;
    q.b1 = c;
    q.b0 = 0;
    q.h2 = 0;
    r.x = x;
    r.z = 0;
    f_DrawPackedUiSpriteFrame(&r, ((void **)D_80017334)[idx], res, &q);
}

void f_DrawMenuSelectionCursor(s16 x, s16 y, s32 c)
{
    f_DrawUiQuadResource(x, y, c, 0x98);
}

INCLUDE_ASM("asm/main/nonmatchings/main", f_DrawFullscreenOverlay);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007EAE4);

void func_8007ED5C(s32 sel)
{
    char *lines[4];
    s32 xs[2];
    s32 ys[2];
    s32 *tab;
    s32 i;
    s32 y;
    s32 m;

    tab = (s32 *)D_800A2854;
    lines[0] = (char *)tab[3];
    f_CalculateCenteredTextPositions(lines, 1, xs);
    i = 0;
    y = 0x68;
    f_DrawTallMenuText(xs[0], 0x50, i, (s32)lines[0], 0);
    lines[0] = (char *)tab[4];
    lines[1] = (char *)tab[5];
    m = f_CalculateCenteredTextPositions(lines, 2, xs);
loop:
    ys[i] = y;
    f_DrawTallMenuText(xs[i], (s16)ys[i], (sel == i) * 2, (s32)lines[i], 0);
    y += 0x18;
    if (++i < 2) {
        goto loop;
    }
    f_DrawMenuSelectionCursor(m, ys[sel] + 4, 0);
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007EE74);

void func_8007EF60(s32 sel)
{
    char *lines[4];
    s32 xs[4];
    s32 ys[4];
    s32 *tab;
    s32 i;
    s32 y;
    s32 m;

    tab = (s32 *)D_800A2854;
    lines[0] = (char *)tab[9];
    f_CalculateCenteredTextPositions(lines, 1, xs);
    i = 0;
    y = 0x68;
    f_DrawTallMenuText(xs[0], 0x50, i, (s32)lines[0], 0);
    lines[0] = (char *)tab[10];
    lines[1] = (char *)tab[11];
    m = f_CalculateCenteredTextPositions(lines, 2, xs);
loop:
    ys[i] = y;
    f_DrawTallMenuText(xs[i], (s16)ys[i], (sel == i) * 2, (s32)lines[i], 0);
    y += 0x18;
    if (++i < 2) {
        goto loop;
    }
    f_DrawMenuSelectionCursor(m, ys[sel] + 4, 0);
}

void func_8007F078(void)
{
    func_80078988(0x76, 0xC8, 0, D_800172A4, 0);
    f_DrawSmallMenuText(0x82, 0xC8, 6, ((MenuText_854 *)D_800A2854)->a, 0);
    func_80078988(0xC6, 0xC8, 0, D_800172A8, 0);
    f_DrawSmallMenuText(0xD2, 0xC8, 6, ((MenuText_854 *)D_800A2854)->b, 0);
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007F104);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007F250);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007F498);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007F73C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007F8F8);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007FC24);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007FCC8);

void f_DrawLoadingIndicator(void)
{
    if ((D_1F800198 >> 2) & 1) {
        f_DrawTallMenuText(0xA0, 0xB4, 0, D_80017304, 0);
    } else {
        f_DrawTallMenuText(0xA0, 0xB4, 6, D_80017304, 0);
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
u32 *func_8007FDB0(u32 *f, u32 *ot, s32 n)
{
    s32 sz[6];
    T2PolyGT3 *p = D_800BF544;
    u32 m = 0xFFF0F0F0;
    s32 *flg = &D_1F800080;
    s32 *otz = (s32 *)D_1F800084;
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
            p->rgb1 = c & m;
            T2_stopz(flg);
            if (*flg > 0) {
                T2_stsxy3_gt3(p);
                if ((p->x0 < 320 || p->x1 < 320 || p->x2 < 320) && (p->y0 < 240 || p->y1 < 240 || p->y2 < 240)) {
                    p->rgb2 = (c << 4) & m;
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
                            *otz = b >> 2;
                        } else {
                            b = sz[2];
                            if (b < sz[1]) {
                                b = sz[1];
                            }
                            *otz = b >> 2;
                        }
                        break;
                    case 2:
                        T2_stsz1(&sz[3]);
                        T2_stsz2(&sz[4]);
                        T2_stsz3(&sz[5]);
                        if (sz[3] < sz[4]) {
                            b = sz[5];
                            if (sz[3] < b) {
                                b = sz[3];
                            }
                            *otz = b >> 2;
                        } else {
                            b = sz[5];
                            if (sz[4] < b) {
                                b = sz[4];
                            }
                            *otz = b >> 2;
                        }
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

INCLUDE_ASM("asm/main/nonmatchings/main", func_8008007C);

void func_800803DC(u32 *p, void *b)
{
    u32 lo = *p;
    u32 packed;

    packed = lo;
    lo = packed & 0xFFFF;
    p += 4;
    func_8008007C(func_8007FDB0(p, b, lo), b, packed >> 16);
}

extern u16 *D_80017334_e22b[];
extern u8 D_1F80027A_3214[];
extern u16 D_1F80017C_7f8c[];
extern u16 D_1F8001A4_b8b0[];
s32 f_TestAndQueueActorForRender();
void func_80080424(u8 *a)
{
    s32 draw = 0;
    s32 k;
    s32 r;
    u16 t;

    switch (a[4]) {
    case 0:
        a[4] = 1;
        *(s32 *)(a + 0x3C) = D_800ECF58_6489;
        a[0xD] = 0;
        a[0xB] = 0x10;
        *(s16 *)(a + 0x5A) = 0;
        a[8] = 0;
        *(s16 *)(a + 0x5C) = 0;
        f_StartActorTimedFrameSequence(a, D_80017334_e22b, 0x162);
        a[0x47] = 0;
        f_ResolveActorAreaPlanePosition(a);
        k = a[3];
        *(s16 *)(a + 0x80) = 0x1E;
        *(s16 *)(a + 0x82) = 0x3C;
        *(s16 *)(a + 0x84) = 0x3C;
        a[0] = 1;
        *(s16 *)(a + 0x86) = 0x5A;
        *(u16 *)(a + 0x4A) = 0;
        if (k == 1) {
            *(u16 *)(a + 0x50) = 0x100;
        } else if (k == 2) {
            func_8012DE84(a, *(s16 *)(a + 0x32));
            t = *D_1F8001A4_b8b0;
            *(u16 *)(a + 0x64) = t;
            if (*(s16 *)(a + 0x32) < (s16)t) {
                a[5] = 1;
            }
        }
        *(u16 *)(a + 0x40) = 0x12C;
        a[0x29] = 0;
        break;
    case 1:
        if (*D_1F80027A_3214 != 0) {
            a[0x29] = 0;
            f_TestAndQueueActorForRender(a);
            break;
        }
        t = *(u16 *)(a + 0x40) - 1;
        *(u16 *)(a + 0x40) = t;
        switch (a[6]) {
        case 0:
            draw = 1;
            if ((s16)t < 0x5B) {
                a[6] = draw;
            }
            break;
        case 1:
            if (*D_1F80017C_7f8c & 3) {
                draw = 1;
            }
            if ((s16)t < 0x1F) {
                a[6] = 2;
            }
            break;
        case 2:
            if (*D_1F80017C_7f8c & 1) {
                draw = 1;
            }
            if ((s16)t <= 0) {
                a[4] = 3;
                a[0] = 2;
            }
            break;
        }
        if (draw) {
            ((s32 (*)())f_TestAndQueueActorForRender)(a, draw);
        }
        switch (a[3]) {
        case 1:
            *(u16 *)(a + 0x32) += *(s16 *)(a + 0x4A) >> 8;
            *(u16 *)(a + 0x4A) += *(u16 *)(a + 0x50);
            if (a[0x29] != 0) {
                draw = 1;
            } else {
                draw = f_ProbeActorTerrainAlongFacing(a, 0, 0x32);
            }
            if (draw == 1) {
                *(u16 *)(a + 0x4A) = 0;
            } else if (*(s16 *)(a + 0x32) > 0) {
                a[4] = 3;
                a[0] = 2;
            }
            if (*(s16 *)(a + 0x4A) > 0x2000) {
                *(u16 *)(a + 0x4A) = 0x2000;
            }
            break;
        case 2:
            func_8012D8F4(a);
            break;
        }
        a[0x29] = 0;
        break;
    case 2:
        if (f_StartEvent(0x81) >= 0) {
            f_AddItemWithMessage(0x76, 1);
            f_DespawnGrabbedItem(a);
        }
        a[4] = 3;
        break;
    case 3:
        f_ResolveEffectEightByteStreamPayload(a);
        break;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_80080750);

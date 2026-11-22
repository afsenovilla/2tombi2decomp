#include "common.h"
#include "game.h"
#include "m2c.h"

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_8001CBA8);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_8001EC3C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8001F054);

INCLUDE_ASM("asm/main/nonmatchings/main", f_ClassifyTombaActorCylinderContact);

INCLUDE_ASM("asm/main/nonmatchings/main", f_ResolveActorAgainstPartCylinderContact);

INCLUDE_ASM("asm/main/nonmatchings/main", f_ResolveTombaRadialContactAndSide);

INCLUDE_ASM("asm/main/nonmatchings/main", f_TestActorOffsetCylinderOverlap);

INCLUDE_ASM("asm/main/nonmatchings/main", f_ResolveTombaPlaneTransitionActorContact);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8001FC50);

INCLUDE_ASM("asm/main/nonmatchings/main", f_StartActorImpactOrTombaRebound);

INCLUDE_ASM("asm/main/nonmatchings/main", f_ResolveTombaActorImpactResponse);

INCLUDE_ASM("asm/main/nonmatchings/main", f_ResolveTombaConfiguredActorContact);

INCLUDE_ASM("asm/main/nonmatchings/main", f_ResolveTombaType8ActorContact);

INCLUDE_ASM("asm/main/nonmatchings/main", f_ArmTombaFacingInteraction44);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80020B08);

INCLUDE_ASM("asm/main/nonmatchings/main", f_ClassifyActorCylinderContact);

INCLUDE_ASM("asm/main/nonmatchings/main", f_ClassifyActiveColliderPartCylinderContact);

INCLUDE_ASM("asm/main/nonmatchings/main", f_ResolveActiveColliderPartContact);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80021150);

INCLUDE_ASM("asm/main/nonmatchings/main", f_ResolveActiveColliderConfiguredActorContact);

INCLUDE_ASM("asm/main/nonmatchings/main", f_ResolveActiveColliderActorContact);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80021800);

INCLUDE_ASM("asm/main/nonmatchings/main", f_ResolveActiveColliderStaticActorContact);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80021AB0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80021DF4);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80021F34);

INCLUDE_ASM("asm/main/nonmatchings/main", f_RetireActorOnTombaContact);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80022190);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_80022AC8);

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

INCLUDE_ASM("asm/main/nonmatchings/main", f_ApplyTombaSupportedContactState);

INCLUDE_ASM("asm/main/nonmatchings/main", f_TryApplyTombaActorDamage);

INCLUDE_ASM("asm/main/nonmatchings/main", f_TestActorAgainstPartCylinderOverlap);

INCLUDE_ASM("asm/main/nonmatchings/main", f_TestActorCylinderOverlap);

INCLUDE_ASM("asm/main/nonmatchings/main", f_TestActorCylinderOverlapWithRadius);

void f_ResolveTombaType12ActorContact(void) {
    func_8001EC3C();
}

INCLUDE_ASM("asm/main/nonmatchings/main", f_TestActorAgainstPartCylinderBounds);

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

extern u8 D_800BF839;
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
    if ((M2C_FIELD(arg0, u8 *, 0x2A) == M2C_FIELD(arg1, u8 *, 0x2A)) && (f_TestActorOffsetCylinderOverlap() != 0)) {
        f_ApplyActiveColliderImpactResponse(arg0, arg1, 0, 0);
        if ((u32) (M2C_FIELD(arg0, u8 *, 2) - 1) < 9U) {
            M2C_FIELD(arg1, s8 *, 0x2B) = 1;
        }
        *((s8 *)D_1F800182) = 0;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_8002369C);

void func_80023764(s32 arg0, void *arg1) {
    if (f_ResolveTombaRadialContactAndSide() != 0) {
        M2C_FIELD(arg1, s8 *, 0x29) = 1;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_80023794);

INCLUDE_ASM("asm/main/nonmatchings/main", f_PushActorOutsidePartCylinder);

INCLUDE_ASM("asm/main/nonmatchings/main", f_ResolveActorPairCylinderContactClass);

INCLUDE_ASM("asm/main/nonmatchings/main", f_ResolveActorPartCylinderContactClass);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800240FC);

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

INCLUDE_ASM("asm/main/nonmatchings/main", f_SnapActorOntoCylinderTop);

INCLUDE_ASM("asm/main/nonmatchings/main", f_TestTombaSupportPointAgainstActorBounds);

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

INCLUDE_ASM("asm/main/nonmatchings/main", f_FindTombaSupportInteractionTarget);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80024794);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800248D0);

INCLUDE_ASM("asm/main/nonmatchings/main", f_UpdateTombaForwardContactProbe);

INCLUDE_ASM("asm/main/nonmatchings/main", f_TestTombaSupportPointAgainstPartBounds);

extern s8 D_1F800214[];
extern void (*D_8009D22C[])(void);
extern s32 D_800A3EC8;
typedef struct Range8b { s32 sector; s32 size; } Range8b;
extern Range8b D_800BE118_9ace[];
extern u8 D_800BF88D;
extern u8 D_1F800251;
void func_80024CF4(void)
{
    D_8009D22C[D_800BF870.unk0]();
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_80024D34);

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

extern s8 D_1F800137[];
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

INCLUDE_ASM("asm/main/nonmatchings/main", func_80026D08);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80026DD8);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80026EB8);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80026F88);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_80027CB4);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80027E5C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8002801C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800281EC);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8002847C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800286CC);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800288AC);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80028B70);

INCLUDE_ASM("asm/main/nonmatchings/main", f_InitializeTransientEffectActor);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8002918C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800292B8);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800293F4);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80029530);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80029664);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80029B40);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80029F6C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8002A584);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8002A834);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8002AB5C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8002AE0C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8002B278);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8002B3A4);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8002B7B0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8002B8F4);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8002BAFC);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8002BC9C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8002C138);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_8002C6AC);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8002C920);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8002CD18);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8002D65C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8002DBE4);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8002DD88);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8002DF68);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8002E1E8);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_8002F8DC);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8002FC40);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8002FDD0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800300D8);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80030264);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800308C0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80030A3C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80030D68);

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

INCLUDE_ASM("asm/main/nonmatchings/main", f_SpawnImpactTransientEffect);

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

INCLUDE_ASM("asm/main/nonmatchings/main", f_SpawnActorImpactEffectPair);

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

INCLUDE_ASM("asm/main/nonmatchings/main", f_ProjectEffectPointToScreenAndDepth);

INCLUDE_ASM("asm/main/nonmatchings/main", f_SetEffectRenderTransform);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80031AC4);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80031D24);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80031F84);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800321D8);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800323FC);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8003265C);

void func_800328BC(void *arg0, M2C_UNK arg1) {
    f_DrawProjectedSpriteDefinitionStream(arg1, (M2C_FIELD(arg0, u16 *, 0x46) << 0x10) | M2C_FIELD(arg0, u16 *, 0x44));
}

void f_DrawEffectPrimitiveListWithoutDepthCue(void *list)
{
    *(s32 *)D_1F800090 = 0;
    func_8002847C(list, 0, 0);
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_80032918);

INCLUDE_ASM("asm/main/nonmatchings/main", f_SetEffectProjectionTransform);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_80032AB4);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80032CBC);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80032EB8);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_80033278);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80033380);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80033450);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80033560);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80033630);

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

INCLUDE_ASM("asm/main/nonmatchings/main", f_DrawPauseMenuButtonIcon);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_80034BE0);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_800364AC);

extern char D_800172A4[];
extern char D_800172A8[];
extern u8 D_800A2854[];
typedef struct { u8 pad[0xA4]; void *a; void *pad2; void *b; } MenuText_854;
extern u8 *D_800BF544_37fb;
extern u32 *D_800ED8C8;
extern u8 D_800BF816;
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
void func_80071B44(s32, s32, s32);
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
extern u8 D_1F8000F8[];
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

INCLUDE_ASM("asm/main/nonmatchings/main", func_80038F7C);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_80039E80);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_8003A290);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_8003A470);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_8003A790);

typedef struct ActorY36 { u8 pad0[0x36]; s16 y; } ActorY36;
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

INCLUDE_ASM("asm/main/nonmatchings/main", f_UpdateAndDrawTombaModel);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_8003F07C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8003F174);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8003F264);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_8003F7A0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8003F7D8);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_8003FAE8);

extern s8 D_1F80008C[];
void func_8003FB84(void) {
    *((s32 *)D_1F80008C) = 0xFF;
}

extern s8 D_1F80008C[];
extern s8 D_1F800090[];
extern s8 D_1F800094[];
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

INCLUDE_ASM("asm/main/nonmatchings/main", func_8004022C);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_80040AA4);

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

INCLUDE_ASM("asm/main/nonmatchings/main", f_UpdateEvent);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_80040E54);

extern u16 D_800BF89E;
s32 f_ApplyActorScriptTransition(u8 *a)
{
    s32 r;

    switch (func_80040E54(a)) {
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

INCLUDE_ASM("asm/main/nonmatchings/main", f_RunActorScriptInterpreter);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_8004179C);

s32 f_AdvanceActorAnimationAndStoreCompletion(void *arg0) {
    M2C_FIELD(arg0, s8 *, 0x79) = f_AdvanceActorSkeletalAnimation();
    return 1;
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_80041938);

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
extern u8 D_1F800230_d8aa;
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

INCLUDE_ASM("asm/main/nonmatchings/main", func_80041C54);

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
extern u8 D_800BF81C;
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

INCLUDE_ASM("asm/main/nonmatchings/main", f_BeginScriptedInteractionAudio);

void func_800423FC(void *arg0) {
    if (M2C_FIELD(arg0, s16 *, 0x72) != 0) {
        f_BeginScriptedInteractionAudio((u8) M2C_FIELD(arg0, s16 *, 0x72), M2C_FIELD(arg0, u8 *, 0x74));
        return;
    }
    f_EndScriptedInteractionAudio();
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_80042448);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800424F0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800425FC);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_80042A8C);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_80042BDC);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80042D28);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_80042E10);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80042EA4);

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

extern u8 D_800BF840;
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

INCLUDE_ASM("asm/main/nonmatchings/main", func_80043A40);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_80043D8C);

void func_80043D8C(void *, s32);
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

INCLUDE_ASM("asm/main/nonmatchings/main", func_80044144);

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

INCLUDE_ASM("asm/main/nonmatchings/main", f_ProbeActorTerrainAtOffset);

INCLUDE_ASM("asm/main/nonmatchings/main", f_ResolveTerrainProbeVerticalContact);

INCLUDE_ASM("asm/main/nonmatchings/main", f_EvaluateTerrainVerticalSurface);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800459D0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80045B30);

INCLUDE_ASM("asm/main/nonmatchings/main", f_ResolveActorRadialTerrainContact);

INCLUDE_ASM("asm/main/nonmatchings/main", f_ResolveTerrainProbeHorizontalSurfaceBySideMask);

INCLUDE_ASM("asm/main/nonmatchings/main", f_EvaluateTerrainHorizontalSurface);

INCLUDE_ASM("asm/main/nonmatchings/main", f_TestActorRadialTerrainContact);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80046A44);

INCLUDE_ASM("asm/main/nonmatchings/main", f_ResolveActorDirectionalTerrainContact);

INCLUDE_ASM("asm/main/nonmatchings/main", f_ResolveTerrainProbeSurfaceBySideMask);

INCLUDE_ASM("asm/main/nonmatchings/main", f_ClassifyActorDirectionalTerrainContact);

INCLUDE_ASM("asm/main/nonmatchings/main", f_ResolveActorAreaPlanePosition);

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

INCLUDE_ASM("asm/main/nonmatchings/main", f_ClassifyActorTerrainAtOffset);

void func_800493E8(u8 *actor, s16 a, s16 b)
{
    func_80049418(actor, a, b, *(s16 *)(actor + 0x56));
}

extern s8 D_1F8001A6[];
extern s8 D_1F8001BC[];
extern s8 D_1F8001BE[];
extern s8 D_1F8001C0[];
extern s8 D_1F8001C4[];
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

INCLUDE_ASM("asm/main/nonmatchings/main", f_ApplyTerrainProfileOrientationToActor);

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
extern u16 *D_1F8001E0;
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

INCLUDE_ASM("asm/main/nonmatchings/main", f_GrantPickupHealth);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80049F80);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8004A118);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8004A2A0);

INCLUDE_ASM("asm/main/nonmatchings/main", f_GrantNonGemPickupReward);

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

extern s32 D_1F800000[];
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

INCLUDE_ASM("asm/main/nonmatchings/main", func_8004B788);

INCLUDE_ASM("asm/main/nonmatchings/main", f_FillEquippedBucketFromSource);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8004BB38);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_8004C01C);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_8004D298);

INCLUDE_ASM("asm/main/nonmatchings/main", f_AddInventoryQuantity);

void f_AddItemWithMessage(s32 arg0) {
    f_AddInventoryQuantity();
    f_QueueItemMessage(arg0, 2);
}

void f_AddItemWithoutMessage(void) {
    f_AddInventoryQuantity();
}

INCLUDE_ASM("asm/main/nonmatchings/main", f_CompactInventoryAfterRemoval);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_8004D714);

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

INCLUDE_ASM("asm/main/nonmatchings/main", f_TestWorldOrOtherPickupCollectedBit);

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

INCLUDE_ASM("asm/main/nonmatchings/main", f_UpdateUsedItemAttachmentPresentation);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_8004DC84);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_8004DF94);

extern u8 D_1F800207_9c67;
extern s16 D_1F800164_d75f;
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

INCLUDE_ASM("asm/main/nonmatchings/main", f_RemoveOldestPopupDisplayEntry);

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

INCLUDE_ASM("asm/main/nonmatchings/main", f_QueuePopupMessage);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_80050738);

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

extern s16 D_800E7E70;
extern s16 D_800E7E72;
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

INCLUDE_ASM("asm/main/nonmatchings/main", f_UpdateActorScaledModelTransforms);

INCLUDE_ASM("asm/main/nonmatchings/main", f_UpdateActorScaledOffsetModelTransforms);

INCLUDE_ASM("asm/main/nonmatchings/main", f_InitializeMultiPartActorModel);

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

INCLUDE_ASM("asm/main/nonmatchings/main", f_InitializeSinglePartActorModel);

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
typedef struct Entry8w { u8 pad0[6]; u16 flags; } Entry8w;
extern Entry8w *D_800A54A8_6044[];
extern u8 D_800A55B0[];
extern u8 *D_800A2B84[];
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

extern s32 D_1F8000D0_42d8[];
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

INCLUDE_ASM("asm/main/nonmatchings/main", f_TryPrepareTombaForInteraction);

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

INCLUDE_ASM("asm/main/nonmatchings/main", f_ResolveTombaOverheadTerrainContact);

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

INCLUDE_ASM("asm/main/nonmatchings/main", f_ResolveTombaGroundTerrainContact);

INCLUDE_ASM("asm/main/nonmatchings/main", f_UpdateTombaForwardTerrainContact);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80054790);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8005490C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80054B34);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80054C08);

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

INCLUDE_ASM("asm/main/nonmatchings/main", f_UpdateTombaLostGroundSupportMotion);

INCLUDE_ASM("asm/main/nonmatchings/main", f_DetachTombaFromSupport);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80056E08);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_8005706C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80057150);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800572EC);

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

INCLUDE_ASM("asm/main/nonmatchings/main", f_UpdateTombaAirborneMotion);

INCLUDE_ASM("asm/main/nonmatchings/main", f_TryStartTombaSupportInteraction);

void func_80057C08(void *arg0, s32 arg1) {
    u8 temp_v0;
    u8 temp_v0_2;

    if ((f_TryStartTombaSupportInteraction() == 0) && (arg1 != 2)) {
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
extern u8 D_800BF881;
extern u8 D_1F800247;
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
extern u16 D_1F800190_b2e0;
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

INCLUDE_ASM("asm/main/nonmatchings/main", func_80059C60);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80059D28);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80059ED8);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8005A39C);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_8005B20C);

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
extern u16 D_1F80018C_c065;
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

INCLUDE_ASM("asm/main/nonmatchings/main", func_80060268);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006032C);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006271C);

INCLUDE_ASM("asm/main/nonmatchings/main", f_UpdateTombaClingVerticalMotion);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80062D8C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80063098);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_800654D4);

extern s8 D_800BF80E;
void func_800655A0(void *arg0) {
    M2C_FIELD(arg0, s16 *, 0x58) = 0;
    D_800BF80E = 0;
    M2C_FIELD(arg0, s8 *, 5) = 0x1E;
    M2C_FIELD(arg0, u8 *, 6) = (u8) (M2C_FIELD(arg0, u8 *, 6) + 1);
    func_800654D4();
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

INCLUDE_ASM("asm/main/nonmatchings/main", func_80065990);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80065A54);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_800663A8);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_800665F4);

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
extern u16 D_1F80019E;
extern u16 D_1F8001A4;
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

INCLUDE_ASM("asm/main/nonmatchings/main", func_80067DA8);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_80068214);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800682C4);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_80068A94);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80068BE8);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80068E68);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80068FBC);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006918C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006923C);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_80069858);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80069948);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_80069BEC);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80069CD8);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006A080);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006A240);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006A384);

s32 func_8006A8C8(s32 arg0) {
    s32 temp_v0;

    temp_v0 = f_SpawnTransientEffect(0x27, 0);
    if (temp_v0 != 0) {
        M2C_FIELD(temp_v0, s32 *, 0x10) = arg0;
    }
    return temp_v0;
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006A900);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006AE28);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006B124);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006B1FC);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006B390);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006B494);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006B9DC);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006BB6C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006BD20);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006BDF0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006BE88);

typedef struct { u8 pad[0x30]; s32 y; } ActorY_C0C4;
extern ActorY_C0C4 D_800E7E80_1c87;
extern s8 D_800E807E;
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

extern M2C_UNK func_8002C138;
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

INCLUDE_ASM("asm/main/nonmatchings/main", f_ApproachFixedPosition3D);

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

INCLUDE_ASM("asm/main/nonmatchings/main", f_ApproachCameraPositionHorizontal);

INCLUDE_ASM("asm/main/nonmatchings/main", f_ApproachCameraPositionVertical);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006DAD8);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006DC38);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006E0F0);

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
    f_ApproachCameraPositionHorizontal();
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
    if (f_ApproachCameraPositionHorizontal() != 0) {
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

extern u8 D_800E8008_f2dc[];
extern u8 D_800E7EAC[];
extern s32 D_800E7EB0;
extern void (*D_800A4AA0[])(u8 *);
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

INCLUDE_ASM("asm/main/nonmatchings/main", f_SpawnAreaLinkedItemPickupActor);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006FC34);

INCLUDE_ASM("asm/main/nonmatchings/main", f_SpawnAreaLinkedWeaponPickupActor);

extern u8 D_800A4BB8[];
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

INCLUDE_ASM("asm/main/nonmatchings/main", func_800702C0);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_800713F8);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_80071B44);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_80071CF4);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80071DFC);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80072114);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800721DC);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_800727D4);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_800738B0);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007413C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800741DC);

INCLUDE_ASM("asm/main/nonmatchings/main", f_PlaySoundEffect);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_80075130);

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

INCLUDE_ASM("asm/main/nonmatchings/main", f_AdvanceActorSkeletalAnimation);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007703C);

INCLUDE_ASM("asm/main/nonmatchings/main", f_TestActorVisibilityAndQueueForRender);

INCLUDE_ASM("asm/main/nonmatchings/main", f_StepWrappedAngleToward);

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

INCLUDE_ASM("asm/main/nonmatchings/main", f_AdvanceActorTimedFrameSequence);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_80078610);

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

INCLUDE_ASM("asm/main/nonmatchings/main", f_GetWarpSectionDisplayName);

void *func_800787F8(s32 i)
{
    u8 *idx = &D_800A55C8[i];

    return D_800A2B64[*idx];
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_80078824);

extern s32 D_800BFE50;
s32 f_TestWarpDestinationUnlocked(s32 arg0) {
    return D_800BFE50 & (1 << arg0);
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_800788AC);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80078988);

INCLUDE_ASM("asm/main/nonmatchings/main", f_DrawMenuTextGlyphs);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80079014);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_800796DC);

INCLUDE_ASM("asm/main/nonmatchings/main", f_NewGameSetDefaultValues);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800798F8);

INCLUDE_ASM("asm/main/nonmatchings/main", f_AllocateActorFromPool0);

INCLUDE_ASM("asm/main/nonmatchings/main", f_AllocateActorFromPool1);

INCLUDE_ASM("asm/main/nonmatchings/main", f_AllocateActorFromPool2);

INCLUDE_ASM("asm/main/nonmatchings/main", f_AllocateActorFromPool3);

INCLUDE_ASM("asm/main/nonmatchings/main", f_AllocateActorFromPool4);

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
extern u8 D_800E7E7D;
extern u8 D_800ED8CC;
extern u8 D_800ED8C5;
extern u8 D_800ED8C4;
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

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007AE30);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007B18C);

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

extern u8 D_1F80023B_0a71;
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

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007C780);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007C8C8);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007D14C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007D208);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007D594);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007DA50);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007DC38);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007DDE0);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007ED5C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007EE74);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007EF60);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007FDB0);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_80080424);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80080750);

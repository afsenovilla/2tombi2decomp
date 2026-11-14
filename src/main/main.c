#include "common.h"
#include "game.h"
#include "m2c.h"

extern volatile u8 D_800BE0E4;
void f_CloseCooperativeWorkerThread(s32);
void f_SetCdAudioMixEnabled(s32);
s32 CdControlB(u8 com, u8 *param, u8 *result);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8001CAC0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8001CBA8);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8001CC00);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8001CE04);


void func_8001CE90(s32 arg0) {
    func_8001CE04(arg0 & 0xFF);
}


s32 func_8001CEB0(s32 arg0, s32 arg1) {
    s8 sp10;
    s32 var_v0;

    var_v0 = CdMode();
    if (var_v0 != arg0) {
        sp10 = (s8) arg0;
        func_8001CE04(0xE, (s32) &sp10, arg1);
        var_v0 = f_YieldCurrentCooperativeWorker(2);
    }
    return var_v0;
}

extern s32 D_800BE108;
extern u8 D_800BF808[];
extern u8 D_800A4F88[];
extern s8 D_1F800090[];
void f_SetActorModelResources(void *, s32, s32);
void func_8001DC40(void *, s32, s32, void *);
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

INCLUDE_ASM("asm/main/nonmatchings/main", func_8001D41C);

INCLUDE_ASM("asm/main/nonmatchings/main", f_PlayOrStopVoiceLine);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_8001DB8C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8001DC40);

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

INCLUDE_ASM("asm/main/nonmatchings/main", f_ResolveTombaClass5ActorContacts);

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
extern s8 D_800BF80D;
extern u8 D_800BF81E_6fe1;
extern s32 D_800A3AC4[];
extern s32 D_800BFE34;
extern u16 D_1F800160;
extern u16 D_1F800162;
extern u16 D_1F800164;
extern u8 D_1F800137_104c;
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
extern u8 D_800BE0E4_9d53;
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
extern u8 D_800ECF48_7ec2[];

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

extern s8 D_1F800182[];
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

INCLUDE_ASM("asm/main/nonmatchings/main", f_InitializeHudTombaAnimation);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80024F18);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800251F0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80025588);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80025744);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80025934);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80025B78);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80025D98);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80026024);

typedef struct Linked { u8 pad0; u8 active; u8 pad2[0x1A]; void (*callback)(struct Linked *); u8 pad20[4]; struct Linked *next; } Linked;
extern Linked *D_800F2738;
extern Linked *D_800F2624;
extern s8 *D_800ECF58[];
extern u8 D_80017334[];
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

INCLUDE_ASM("asm/main/nonmatchings/main", func_8002623C);

extern u16 D_800E7E68;
void func_800262A8(void *arg0) {
    if (D_800E7E68 & 0xC00) {
        M2C_FIELD(arg0, u8 *, 8) = (u8) (1 - M2C_FIELD(arg0, u8 *, 8));
    }
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_800262D8);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80026320);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80026368);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800263E8);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_8002655C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80026864);

extern u8 D_800ED06D;
extern u8 D_800BF849;
extern u8 D_800BF80F_fcc6;
extern u8 D_1F800137_104c;
extern s8 *D_800ECF58[];
extern s8 D_1F800214[];
extern u8 D_800A4A94[];
extern u8 *D_800BF844;
void f_InitializeSinglePartActorModel(void *, s32, s32);

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

extern u16 D_1F80017C_0fe7;
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

INCLUDE_ASM("asm/main/nonmatchings/main", func_80026AD0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80026C88);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80026D08);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80026DD8);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80026EB8);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80026F88);

INCLUDE_ASM("asm/main/nonmatchings/main", f_InitializeEffectSlotFromTemplateIndex);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_8002C3EC);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8002C548);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_8002F514);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8002F738);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8002F8DC);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8002FC40);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8002FDD0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800300D8);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80030264);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800308C0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80030A3C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80030D68);

extern u8 D_800E7E7C;

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

INCLUDE_ASM("asm/main/nonmatchings/main", f_SpawnFlaggedTransientEffectAtFixedPosition);

INCLUDE_ASM("asm/main/nonmatchings/main", f_SpawnMovingTransientEffectAtFixedPosition);

INCLUDE_ASM("asm/main/nonmatchings/main", f_SpawnImpactTransientEffect);

INCLUDE_ASM("asm/main/nonmatchings/main", f_SpawnLinkedActorTrailEffect);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_800330AC);

INCLUDE_ASM("asm/main/nonmatchings/main", f_SpawnLinkedActorShadow);

INCLUDE_ASM("asm/main/nonmatchings/main", f_SpawnLinkedActorSpriteRingEffect);

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
typedef struct UiRect { s16 x, y, w, h; } UiRect;

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_800345D8);


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

INCLUDE_ASM("asm/main/nonmatchings/main", func_80035088);

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

INCLUDE_ASM("asm/main/nonmatchings/main", f_GetPauseMenuEquipmentGroupRange);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_80037894);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_80038758);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_800399C0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800399FC);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80039BCC);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80039E80);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80039F4C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8003A1E4);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8003A290);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8003A3E8);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8003A470);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8003A5E4);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8003A790);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8003A9A0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8003ABE4);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8003AD48);

INCLUDE_ASM("asm/main/nonmatchings/main", f_ApplyActorSpriteUvOrientation);

INCLUDE_ASM("asm/main/nonmatchings/main", f_BuildActorSpriteQuadVertices);

INCLUDE_ASM("asm/main/nonmatchings/main", f_ProjectAndQueueFourVertexPrimitive);

INCLUDE_ASM("asm/main/nonmatchings/main", f_UpdateAndDrawTombaModel);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8003B704);

INCLUDE_ASM("asm/main/nonmatchings/main", f_DrawClass2And9ActorRenderQueue);

INCLUDE_ASM("asm/main/nonmatchings/main", f_DrawClass4ActorRenderQueue);

INCLUDE_ASM("asm/main/nonmatchings/main", f_DrawClass5ActorRenderQueue);

INCLUDE_ASM("asm/main/nonmatchings/main", f_DrawPresentationActorList);

INCLUDE_ASM("asm/main/nonmatchings/main", f_DrawActorSpritePartsWithZRotation);

INCLUDE_ASM("asm/main/nonmatchings/main", f_DrawActorSpritePartsWithScaleAndZRotation);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8003C5F8);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8003C788);

INCLUDE_ASM("asm/main/nonmatchings/main", f_DrawActorSpriteParts);

INCLUDE_ASM("asm/main/nonmatchings/main", f_DrawActorModelByRenderMode);

INCLUDE_ASM("asm/main/nonmatchings/main", f_BuildActorModelPartPrimitives);

INCLUDE_ASM("asm/main/nonmatchings/main", f_DrawCurrentAreaEnvironment);

INCLUDE_ASM("asm/main/nonmatchings/main", f_DrawTemplateEffectSlot);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8003D584);

INCLUDE_ASM("asm/main/nonmatchings/main", f_DrawCurrentAreaTilemapLayer);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8003E030);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8003E264);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8003E448);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8003E894);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8003EA88);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8003EBE0);

INCLUDE_ASM("asm/main/nonmatchings/main", f_DrawActiveWorldActors);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8003EF9C);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_8003F2F8);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8003F31C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8003F344);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8003F3F4);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8003F4C4);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8003F594);

INCLUDE_ASM("asm/main/nonmatchings/main", f_DrawModelPrimitiveStreamForCurrentArea);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_8003FC00);


void func_8003FC78(void *arg0) {
    M2C_FIELD(arg0, s16 *, 0x58) = 0;
    M2C_FIELD(arg0, s16 *, 0x56) = (s16) (M2C_FIELD(arg0, u8 *, 0x2A) * 0x10);
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_8003FC8C);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_8003FFCC);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8004022C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80040390);

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

INCLUDE_ASM("asm/main/nonmatchings/main", f_StartEvent);

INCLUDE_ASM("asm/main/nonmatchings/main", f_UpdateEvent);

INCLUDE_ASM("asm/main/nonmatchings/main", f_InitializeActorScript);


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
extern s16 D_800E7FEE;
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

INCLUDE_ASM("asm/main/nonmatchings/main", f_ApplyActorScriptTransition);

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
void f_SpawnAreaIndexedPersistentPickup(void *, s32, s32);

void func_80041378(u8 *actor)
{
    f_ApplyActorOrientationToRotation(actor, *(s16 *)(actor + 0x72));
}

INCLUDE_ASM("asm/main/nonmatchings/main", f_StepAngleTowardTarget);


void f_StepActorYawTowardAngle(s32 arg0, s16 arg1, s16 arg2) {
    f_StepAngleTowardTarget(arg0 + 0x56, arg1, arg2);
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_80041468);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8004162C);

INCLUDE_ASM("asm/main/nonmatchings/main", f_SetActorModelResources);


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

INCLUDE_ASM("asm/main/nonmatchings/main", f_SetActorAnimationIfChanged);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_80041A1C);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_800420AC);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80042170);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800421CC);

extern u8 D_800BF843;
s32 func_8004223C(void *arg0) {
    return D_800BF843 == M2C_FIELD(arg0, s16 *, 0x72);
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_80042258);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_80042758);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800427F4);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_80043634);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_800438D4);

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
extern u16 D_800ECF54;

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_800446A4);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8004491C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80044B38);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_800450BC);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_80048D3C);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_8004960C);

INCLUDE_ASM("asm/main/nonmatchings/main", f_ApplyTerrainProfileOrientationToActor);

INCLUDE_ASM("asm/main/nonmatchings/main", f_ApplyAreaPlaneDirectionToActor);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80049800);

INCLUDE_ASM("asm/main/nonmatchings/main", f_FindTerrainCellForActorProbe);

INCLUDE_ASM("asm/main/nonmatchings/main", f_SelectAreaPlaneCollisionTables);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800499E8);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80049A60);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_8004B150);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_8004B3F4);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_8004B4B0);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_8004BEF4);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8004BF84);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8004C01C);

INCLUDE_ASM("asm/main/nonmatchings/main", f_SpawnAreaIndexedPersistentPickup);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8004C238);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8004C930);

INCLUDE_ASM("asm/main/nonmatchings/main", f_SpawnAreaIndexedPersistentPickupOnce);


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

INCLUDE_ASM("asm/main/nonmatchings/main", func_8004D8B0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8004D8D8);

INCLUDE_ASM("asm/main/nonmatchings/main", f_UpdateUsedItemAttachmentPresentation);

extern u8 D_800BF80A_8fc3;

s32 func_8004DBB0(void) {
    return D_800BF80A_8fc3 == 0;
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_8004DBC0);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_8004E29C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8004E414);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8004E808);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8004E928);

INCLUDE_ASM("asm/main/nonmatchings/main", f_MeasureEncodedMessageLine);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8004EAD0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8004EB94);

INCLUDE_ASM("asm/main/nonmatchings/main", f_QueueItemMessage);

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

INCLUDE_ASM("asm/main/nonmatchings/main", f_MeasureEncodedMessageBlock);

INCLUDE_ASM("asm/main/nonmatchings/main", f_FormatPopupPayloadPage);

INCLUDE_ASM("asm/main/nonmatchings/main", f_AppendPopupDisplayEntry);

INCLUDE_ASM("asm/main/nonmatchings/main", f_PromoteNextPopupRequest);


void func_8004F430(void *arg0) {
    if (M2C_FIELD(arg0, s16 *, 0xA) != 0) {
        f_PromoteNextPopupRequest();
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

INCLUDE_ASM("asm/main/nonmatchings/main", func_8004FFB4);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8005019C);

extern volatile u16 D_800E809C_da0a;

void func_800506B4(void) {
    D_800E809C_da0a += 1;
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_800506D0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80050738);

extern u16 D_1F800170;
extern u16 D_1F800174_de41;
extern u16 D_1F800176;
extern u8 D_800FB160_9a03[];
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

INCLUDE_ASM("asm/main/nonmatchings/main", f_StartControllerVibration);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_80052694);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80052720);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800527C8);

INCLUDE_ASM("asm/main/nonmatchings/main", f_TryPrepareTombaForInteraction);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8005314C);


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

INCLUDE_ASM("asm/main/nonmatchings/main", f_CanTombaStartAttack);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80053670);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8005376C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800537B8);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800538E0);

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

INCLUDE_ASM("asm/main/nonmatchings/main", f_ReleaseTombaInteractionTarget);

INCLUDE_ASM("asm/main/nonmatchings/main", f_ClearTombaInteractionState);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_800543C0);

INCLUDE_ASM("asm/main/nonmatchings/main", f_ResolveTombaGroundTerrainContact);

INCLUDE_ASM("asm/main/nonmatchings/main", f_UpdateTombaForwardTerrainContact);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80054790);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8005490C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80054B34);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80054C08);

INCLUDE_ASM("asm/main/nonmatchings/main", f_SetTombaAnimationIfChanged);

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

INCLUDE_ASM("asm/main/nonmatchings/main", f_SelectTombaContactAnimation6AOr6C);

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

INCLUDE_ASM("asm/main/nonmatchings/main", f_AdvanceTombaAlongMovementVector);

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

INCLUDE_ASM("asm/main/nonmatchings/main", f_ApplyTombaStatusCommand);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_8005950C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800597AC);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80059C60);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80059D28);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80059ED8);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8005A39C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8005A714);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_8005B134);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8005B20C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8005B370);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8005B5E4);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8005B63C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8005C138);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8005C26C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8005C8A0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8005CDF8);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8005D16C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8005D530);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8005DE54);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8005E580);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8005E8FC);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_8005FB54);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_800624B4);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006271C);

INCLUDE_ASM("asm/main/nonmatchings/main", f_UpdateTombaClingVerticalMotion);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80062D8C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80063098);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80063158);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800633B0);

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
    f_ReleaseTombaInteractionTarget();
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

INCLUDE_ASM("asm/main/nonmatchings/main", func_80064BA0);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006585C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800658E4);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006625C);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006762C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800678E8);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80067A40);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80067CA4);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80067DA8);

INCLUDE_ASM("asm/main/nonmatchings/main", f_ApplyTombaClothesAppearanceAndPhysics);


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

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006914C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006918C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006923C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80069300);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80069634);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80069688);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800696C4);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80069858);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80069948);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80069A2C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80069AE4);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_80069B6C);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006ACAC);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006B020);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006B0D8);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006B124);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006B1FC);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006B390);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006B494);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006B9DC);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006BB6C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006BD20);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006BDF0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006BE88);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006C0C4);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006C80C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006C988);


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

INCLUDE_ASM("asm/main/nonmatchings/main", f_UpdateCameraTransformInterpolation);


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

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006DEF0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006DF88);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006E010);

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

INCLUDE_ASM("asm/main/nonmatchings/main", f_UpdateCameraFollowTomba);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006EA7C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006EC44);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006EF38);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006F04C);

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

INCLUDE_ASM("asm/main/nonmatchings/main", f_SpawnLinkedItemPickupActor);

s32 func_8006FFE8(void)
{
    u8 *p = D_800BF844;

    if (p != NULL) {
        p[0x5F] |= 1;
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_80070018);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_80070698);


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

INCLUDE_ASM("asm/main/nonmatchings/main", func_800708CC);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007091C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80070BD0);

INCLUDE_ASM("asm/main/nonmatchings/main", f_UpdateActorOrbitAroundAnchor);

INCLUDE_ASM("asm/main/nonmatchings/main", f_SetScriptActorInteractionOffset);

INCLUDE_ASM("asm/main/nonmatchings/main", f_ApproachShortCoordinate);

INCLUDE_ASM("asm/main/nonmatchings/main", f_UpdateScriptedInteractionApproach);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80071260);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800713F8);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800714C0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007156C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800716B4);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_80072520);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007263C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800726D4);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800727D4);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80072898);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80072A78);

INCLUDE_ASM("asm/main/nonmatchings/main", f_AllocateActor);

INCLUDE_ASM("asm/main/nonmatchings/main", f_OpenInteriorEntranceDoor);


void f_ApplyInteriorEntranceDoorMirroredYaw(void *arg0) {
    M2C_FIELD(arg0, s16 *, 0x56) = (s16) (M2C_FIELD(arg0, u16 *, 0x5A) - M2C_FIELD(arg0, u16 *, 0x50));
}

INCLUDE_ASM("asm/main/nonmatchings/main", f_CloseInteriorEntranceDoor);


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

INCLUDE_ASM("asm/main/nonmatchings/main", f_OpenInteriorDoorPart);

INCLUDE_ASM("asm/main/nonmatchings/main", f_CloseInteriorDoorPart);

INCLUDE_ASM("asm/main/nonmatchings/main", f_CloseMirroredInteriorDoorPart);

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

INCLUDE_ASM("asm/main/nonmatchings/main", f_UpdateInteriorEntranceDoorTransition);

INCLUDE_ASM("asm/main/nonmatchings/main", f_UpdateEntranceContactIndicator);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80073750);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800737F8);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800738B0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800739AC);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80073CD8);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_80074A60);

void f_ComputeDirectionalStereoVolume(u32 handle)
{
    u8 i = handle;
    SoundHandle3 *h = &D_800BE238_0a61[i];

    if ((h->id & ~0xFF) == (handle & ~0xFF)) {
        D_800BE358 |= 1 << i;
        ((u8 *)h)[1] = 0;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_80074B44);

extern s8 D_1F80027E[];
void func_80074BC4(void) {
    *((s8 *)D_1F80027E) = 0;
    f_StopVoicePlayback();
    func_80074B44();
    f_StopSequencedMusic();
}

INCLUDE_ASM("asm/main/nonmatchings/main", f_PlaySequencedMusic);

INCLUDE_ASM("asm/main/nonmatchings/main", f_StopSequencedMusic);

extern s8 D_800BE22A;
extern s16 D_800BED80;
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

INCLUDE_ASM("asm/main/nonmatchings/main", f_OpenSequencedMusicSlot);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800754F4);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007566C);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_80075D58);

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

INCLUDE_ASM("asm/main/nonmatchings/main", f_TestAndQueueActorForRender);

INCLUDE_ASM("asm/main/nonmatchings/main", f_TestAndQueueActorForRenderMode2);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80077870);

INCLUDE_ASM("asm/main/nonmatchings/main", f_TestAndQueueActorForRenderWithYOffset);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80077958);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800779D0);

INCLUDE_ASM("asm/main/nonmatchings/main", f_TestActorVisibilityWithXYZOffset);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80077ACC);


void f_StartActorTimedFrameSequence(u8 *actor, u16 **table, s32 index)
{
    u16 *seq = table[index];
    u16 frames = seq[1];

    *(u16 **)(actor + 0x38) = seq;
    *(u16 *)(actor + 0xE) = frames & 0x3FFF;
}

INCLUDE_ASM("asm/main/nonmatchings/main", f_AdvanceActorTimedFrameSequence);

INCLUDE_ASM("asm/main/nonmatchings/main", f_StartActorSkeletalAnimation);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_80077D8C);


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

extern s8 D_1F80013C[];
extern s8 D_1F800144[];
void f_QueueClass2Or9ActorForRender(s32 arg0) {
    void *temp_a0;

    if (*((s16 *)D_1F800144) < 0x18) {
        temp_a0 = *((void **)D_1F80013C);
        *((void **)D_1F80013C) = temp_a0 - 4;
        M2C_FIELD(temp_a0, s32 *, -4) = arg0;
        *((s16 *)D_1F800144) = (u16) *((s16 *)D_1F800144) + 1;
    }
}

extern s8 D_1F800148[];
extern s8 D_1F800150[];
void f_QueueClass4ActorForRender(s32 arg0) {
    void *temp_a0;

    if (*((s16 *)D_1F800150) < 0x28) {
        temp_a0 = *((void **)D_1F800148);
        *((void **)D_1F800148) = temp_a0 - 4;
        M2C_FIELD(temp_a0, s32 *, -4) = arg0;
        *((s16 *)D_1F800150) = (u16) *((s16 *)D_1F800150) + 1;
    }
}

extern s8 D_1F800154[];
extern s8 D_1F80015C[];
void f_QueueClass5ActorForRender(s32 arg0) {
    void *temp_a0;

    if (*((s16 *)D_1F80015C) < 0x1C) {
        temp_a0 = *((void **)D_1F800154);
        *((void **)D_1F800154) = temp_a0 - 4;
        M2C_FIELD(temp_a0, s32 *, -4) = arg0;
        *((s16 *)D_1F80015C) = (u16) *((s16 *)D_1F80015C) + 1;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_80077F3C);

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

INCLUDE_ASM("asm/main/nonmatchings/main", f_ApproximateVectorLength3D);

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

INCLUDE_ASM("asm/main/nonmatchings/main", f_CalculateCenteredTextPositions);

void func_80079464(s32 demo)
{
    D_1F80017C_0fe7 = 0;
    srand(0x45);
    D_800ECF54_4583[1] = 0;
    D_800ECF54_4583[0] = 0;
    D_800BED8C = 1;
    D_800BED88_191b = (u8 *)0x80157000 + (demo << 10);
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_800794C8);


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

INCLUDE_ASM("asm/main/nonmatchings/main", f_FormatIntegerText);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800796DC);

INCLUDE_ASM("asm/main/nonmatchings/main", f_NewGameSetDefaultValues);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800798F8);

INCLUDE_ASM("asm/main/nonmatchings/main", f_AllocateActorFromPool0);

INCLUDE_ASM("asm/main/nonmatchings/main", f_AllocateActorFromPool1);

INCLUDE_ASM("asm/main/nonmatchings/main", f_AllocateActorFromPool2);

INCLUDE_ASM("asm/main/nonmatchings/main", f_AllocateActorFromPool3);

INCLUDE_ASM("asm/main/nonmatchings/main", f_AllocateActorFromPool4);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007A464);

INCLUDE_ASM("asm/main/nonmatchings/main", f_AllocatePresentationActor);

INCLUDE_ASM("asm/main/nonmatchings/main", f_ResolveEffectEightByteStreamPayload);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007A810);

extern s8 D_1F80017C[];
void func_8007A8E0(void) {
    f_NewGameSetDefaultValues();
    *((s16 *)D_1F80017C) = 0;
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007A904);

INCLUDE_ASM("asm/main/nonmatchings/main", f_AllocateActorRecordByType);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007AA38);

INCLUDE_ASM("asm/main/nonmatchings/main", f_AllocateActorModelPart);


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

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007AD40);

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

INCLUDE_ASM("asm/main/nonmatchings/main", f_ReleaseActorModelParts);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007AE30);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007AF88);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007B04C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007B0F0);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007BE18);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007BF20);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007C0D0);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007CEEC);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007D0D0);

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

INCLUDE_ASM("asm/main/nonmatchings/main", f_DrawUiQuadResource);

INCLUDE_ASM("asm/main/nonmatchings/main", f_DrawUiSpriteResource);


void f_DrawMenuSelectionCursor(s16 x, s16 y, s32 c)
{
    f_DrawUiQuadResource(x, y, c, 0x98);
}

INCLUDE_ASM("asm/main/nonmatchings/main", f_DrawFullscreenOverlay);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007EAE4);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007ED5C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007EE74);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007EF60);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007F078);

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

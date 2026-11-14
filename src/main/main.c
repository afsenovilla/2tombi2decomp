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

INCLUDE_ASM("asm/main/nonmatchings/main", func_8001CEB0);

INCLUDE_ASM("asm/main/nonmatchings/main", f_SetCdAudioMixEnabled);


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

INCLUDE_ASM("asm/main/nonmatchings/main", func_8001CF94);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_80022A80);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80022AC8);

INCLUDE_ASM("asm/main/nonmatchings/main", f_ApplyTombaEnvironmentalDamage);

INCLUDE_ASM("asm/main/nonmatchings/main", f_ApplyTombaSupportedContactState);

INCLUDE_ASM("asm/main/nonmatchings/main", f_TryApplyTombaActorDamage);

INCLUDE_ASM("asm/main/nonmatchings/main", f_TestActorAgainstPartCylinderOverlap);

INCLUDE_ASM("asm/main/nonmatchings/main", f_TestActorCylinderOverlap);

INCLUDE_ASM("asm/main/nonmatchings/main", f_TestActorCylinderOverlapWithRadius);


void f_ResolveTombaType12ActorContact(void) {
    func_8001EC3C();
}

INCLUDE_ASM("asm/main/nonmatchings/main", f_TestActorAgainstPartCylinderBounds);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80023238);

INCLUDE_ASM("asm/main/nonmatchings/main", f_CanTombaTakeDamage);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_80023548);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800235A0);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_80024448);

INCLUDE_ASM("asm/main/nonmatchings/main", f_FindTombaSupportInteractionTarget);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80024794);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800248D0);

INCLUDE_ASM("asm/main/nonmatchings/main", f_UpdateTombaForwardContactProbe);

INCLUDE_ASM("asm/main/nonmatchings/main", f_TestTombaSupportPointAgainstPartBounds);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80024CF4);

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

INCLUDE_ASM("asm/main/nonmatchings/main", f_AddEvilPigRobePower);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_80026470);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800264BC);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80026510);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8002655C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80026864);

INCLUDE_ASM("asm/main/nonmatchings/main", f_RequestInteriorTransitionGateMode2);

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

INCLUDE_ASM("asm/main/nonmatchings/main", f_RetireInteriorSceneChildren);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80026A68);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80026AD0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80026C88);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80026D08);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80026DD8);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80026EB8);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80026F88);

INCLUDE_ASM("asm/main/nonmatchings/main", f_InitializeEffectSlotFromTemplateIndex);

INCLUDE_ASM("asm/main/nonmatchings/main", f_CountEffectTemplates);

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

INCLUDE_ASM("asm/main/nonmatchings/main", f_SpawnTransientEffect);

INCLUDE_ASM("asm/main/nonmatchings/main", f_SpawnTransientEffectAtFixedPosition);

INCLUDE_ASM("asm/main/nonmatchings/main", f_SpawnTransientEffectAtShortPosition);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_80031780);

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

INCLUDE_ASM("asm/main/nonmatchings/main", f_DrawEffectPrimitiveListWithoutDepthCue);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_8003393C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800339A4);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80033A0C);

INCLUDE_ASM("asm/main/nonmatchings/main", f_DrawPauseMenuButtonIcon);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80033B94);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80033FF4);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800342EC);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80034338);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80034548);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_80036708);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8003675C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8003687C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800368D0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80036A14);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80036AE8);


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

INCLUDE_ASM("asm/main/nonmatchings/main", func_80036DC4);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80036DFC);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800376EC);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80037894);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8003791C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80037B6C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80037E44);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800384EC);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800386C0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80038708);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80038758);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80038794);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800387E0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80038A00);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80038F7C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80039034);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80039110);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8003989C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8003990C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80039978);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_8003FAA4);

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

INCLUDE_ASM("asm/main/nonmatchings/main", f_GetEventAPReward);

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

INCLUDE_ASM("asm/main/nonmatchings/main", f_LoadActorScriptCommand);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_80041378);

INCLUDE_ASM("asm/main/nonmatchings/main", f_StepAngleTowardTarget);


void f_StepActorYawTowardAngle(s32 arg0, s16 arg1, s16 arg2) {
    f_StepAngleTowardTarget(arg0 + 0x56, arg1, arg2);
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_80041468);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8004162C);

INCLUDE_ASM("asm/main/nonmatchings/main", f_SetActorModelResources);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800416F0);

INCLUDE_ASM("asm/main/nonmatchings/main", f_SetActorAnimation);

INCLUDE_ASM("asm/main/nonmatchings/main", f_SetActorAnimationIfChanged);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8004179C);


s32 f_AdvanceActorAnimationAndStoreCompletion(void *arg0) {
    M2C_FIELD(arg0, s8 *, 0x79) = f_AdvanceActorSkeletalAnimation();
    return 1;
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_80041938);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800419C4);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80041A1C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80041AC0);

INCLUDE_ASM("asm/main/nonmatchings/main", f_InitializeActorFixedStepMotion);

INCLUDE_ASM("asm/main/nonmatchings/main", f_AdvanceActorFixedStepMotion);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80041C54);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80041D60);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80041F34);


void func_80041FA8(void *arg0) {
    func_80041F34(M2C_FIELD(arg0, s32 *, 0x10));
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_80041FCC);


void func_80041FF8(void *arg0) {
    func_80041FCC(M2C_FIELD(arg0, s32 *, 0x10));
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_8004201C);


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

INCLUDE_ASM("asm/main/nonmatchings/main", func_80042690);


s32 func_800426D8(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x2C) = (s32) (M2C_FIELD(arg0, s16 *, 0x72) << 0x10);
    M2C_FIELD(arg0, s32 *, 0x30) = (s32) (M2C_FIELD(arg0, s16 *, 0x74) << 0x10);
    M2C_FIELD(arg0, s32 *, 0x34) = (s32) (M2C_FIELD(arg0, s16 *, 0x76) << 0x10);
    if (*M2C_FIELD(arg0, u16 **, 0x6C) & 0x2000) {
        M2C_FIELD(arg0, u8 *, 0x2A) = (u8) M2C_FIELD(arg0, u8 *, 0x64);
    }
    return 1;
}

INCLUDE_ASM("asm/main/nonmatchings/main", f_IsEventPresentationComplete);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80042758);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800427F4);

extern s8 D_800BF80A;
s32 func_80042884(void) {
    D_800BF80A = 0;
    return 1;
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_80042894);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80042A8C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80042BAC);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_800436BC);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80043720);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80043858);

s32 func_800438B4(u8 *actor)
{
    if (*(s16 *)(actor + 0x72) == actor[0x7A]) {
        return 3;
    }
    return 2;
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_800438D4);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80043964);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800439A4);


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

INCLUDE_ASM("asm/main/nonmatchings/main", func_80043BB0);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_800440A8);

INCLUDE_ASM("asm/main/nonmatchings/main", f_StartTombaScriptedAnimation);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80044144);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800442A0);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_80045080);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800450BC);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8004514C);

INCLUDE_ASM("asm/main/nonmatchings/main", f_LoadResourceChunkIntoGroup);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800452C0);


void func_80045558(s32 arg0) {
    func_80045080(0x8018A000, arg0 & 0xFF);
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_80045580);

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

INCLUDE_ASM("asm/main/nonmatchings/main", f_ProbeActorTerrainAlongFacing);

INCLUDE_ASM("asm/main/nonmatchings/main", f_ClassifyActorTerrainAlongFacing);

INCLUDE_ASM("asm/main/nonmatchings/main", f_ClassifyActorTerrainAtOffset);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800493E8);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_8004951C);

INCLUDE_ASM("asm/main/nonmatchings/main", f_ResolveActorFacingTerrainContact);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8004957C);

INCLUDE_ASM("asm/main/nonmatchings/main", f_ResolveActorDirectionalTerrainAlongFacing);

INCLUDE_ASM("asm/main/nonmatchings/main", f_ClassifyActorDirectionalTerrainAlongFacing);

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

INCLUDE_ASM("asm/main/nonmatchings/main", f_DespawnGrabbedItem);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8004B150);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8004B208);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8004B2E8);


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

INCLUDE_ASM("asm/main/nonmatchings/main", func_8004B428);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8004B4B0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8004B4E8);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8004B528);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8004B788);

INCLUDE_ASM("asm/main/nonmatchings/main", f_FillEquippedBucketFromSource);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8004BB38);

INCLUDE_ASM("asm/main/nonmatchings/main", f_SpawnBackEquipmentProxyActor);

INCLUDE_ASM("asm/main/nonmatchings/main", f_PositionActorFromModelParts);

void f_SetEquippedBackItemActor(s8 item, s32 actor)
{
    D_800BF88E = item;
    D_800E7E80[0x6E] = item;
    *(s32 *)(D_800E7E80 + 0x74) = actor;
}

INCLUDE_ASM("asm/main/nonmatchings/main", f_ClearBackItem);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8004BEF4);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8004BF84);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8004C01C);

INCLUDE_ASM("asm/main/nonmatchings/main", f_SpawnAreaIndexedPersistentPickup);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8004C238);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8004C930);

INCLUDE_ASM("asm/main/nonmatchings/main", f_SpawnAreaIndexedPersistentPickupOnce);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8004CC64);

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

INCLUDE_ASM("asm/main/nonmatchings/main", f_RemoveItemWithMessage);

INCLUDE_ASM("asm/main/nonmatchings/main", f_RemoveItemWithoutMessage);

INCLUDE_ASM("asm/main/nonmatchings/main", f_RemoveItemWithAltMessage);

void func_8004D6D4(s32 item)
{
    f_QueueItemMessage(item, 0);
}

void func_8004D6F4(s32 item)
{
    f_QueueItemMessage(item, 3);
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_8004D714);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8004D79C);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_8004DD90);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_8004EDDC);


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

INCLUDE_ASM("asm/main/nonmatchings/main", f_FindEncodedMessagePage);

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

INCLUDE_ASM("asm/main/nonmatchings/main", f_SetDoubleBufferedClearColor);

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

INCLUDE_ASM("asm/main/nonmatchings/main", f_UpdateActorUnscaledModelTransforms);

INCLUDE_ASM("asm/main/nonmatchings/main", f_UpdateActorScaledModelTransforms);

INCLUDE_ASM("asm/main/nonmatchings/main", f_UpdateActorScaledOffsetModelTransforms);

INCLUDE_ASM("asm/main/nonmatchings/main", f_InitializeMultiPartActorModel);

INCLUDE_ASM("asm/main/nonmatchings/main", f_SetActorPartModel);


void func_80051B34(void *arg0, void *arg1) {
    M2C_FIELD(arg1, s32 *, 0) = (s32) M2C_FIELD(arg0, s32 *, 0);
    M2C_FIELD(arg1, s32 *, 4) = (s32) M2C_FIELD(arg0, s32 *, 4);
    M2C_FIELD(arg1, s32 *, 8) = (s32) M2C_FIELD(arg0, s32 *, 8);
    M2C_FIELD(arg1, s32 *, 0xC) = (s32) M2C_FIELD(arg0, s32 *, 0xC);
    M2C_FIELD(arg1, s32 *, 0x10) = (s32) M2C_FIELD(arg0, s32 *, 0x10);
}

INCLUDE_ASM("asm/main/nonmatchings/main", f_InitializeSinglePartActorModel);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80051C8C);


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

INCLUDE_ASM("asm/main/nonmatchings/main", func_80051E00);

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

INCLUDE_ASM("asm/main/nonmatchings/main", f_OpenCooperativeWorkerThread);

extern s8 D_1F800138[];
void f_YieldCurrentCooperativeWorker(s16 arg0) {
    void *temp_v1;

    temp_v1 = *((void **)D_1F800138);
    M2C_FIELD(temp_v1, s16 *, 2) = arg0;
    M2C_FIELD(temp_v1, s16 *, 0) = 1;
    ChangeTh(0xFF000000);
}

INCLUDE_ASM("asm/main/nonmatchings/main", f_TerminateCurrentCooperativeWorker);

INCLUDE_ASM("asm/main/nonmatchings/main", f_CloseCooperativeWorkerThread);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_800520E0);


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

INCLUDE_ASM("asm/main/nonmatchings/main", func_80052198);

INCLUDE_ASM("asm/main/nonmatchings/main", f_StartControllerVibration);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8005229C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8005245C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800524B4);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800525D0);


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

INCLUDE_ASM("asm/main/nonmatchings/main", f_SetTombaAnimation);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_800557EC);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_80055C30);

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

INCLUDE_ASM("asm/main/nonmatchings/main", f_SetTombaJumpLaunchVelocity);

INCLUDE_ASM("asm/main/nonmatchings/main", f_UpdateTombaHorizontalMovementSpeed);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80056878);

INCLUDE_ASM("asm/main/nonmatchings/main", f_AdvanceTombaAlongMovementVector);

INCLUDE_ASM("asm/main/nonmatchings/main", f_UpdateTombaLostGroundSupportMotion);

INCLUDE_ASM("asm/main/nonmatchings/main", f_DetachTombaFromSupport);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80056E08);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80056EC8);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_800634A8);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_80069B28);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80069B6C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80069BEC);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80069CD8);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006A080);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006A240);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006A384);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006A8C8);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006A900);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006ABF4);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006AC38);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006AC7C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006ACAC);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006AE28);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006AFC4);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006C77C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006C7C4);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006C80C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006C988);

INCLUDE_ASM("asm/main/nonmatchings/main", f_SetCameraFocusPosition);

INCLUDE_ASM("asm/main/nonmatchings/main", f_SetCameraTransform);

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

INCLUDE_ASM("asm/main/nonmatchings/main", f_RestorePreviousCameraMode);


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

INCLUDE_ASM("asm/main/nonmatchings/main", f_SnapCameraPositionAndRebuildView);


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

INCLUDE_ASM("asm/main/nonmatchings/main", f_SpawnTombaMovementHintController);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006F138);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006F2D0);

INCLUDE_ASM("asm/main/nonmatchings/main", f_InitializeLinkedPickupFromVisualDefinition);

INCLUDE_ASM("asm/main/nonmatchings/main", f_SpawnAreaLinkedItemPickupActor);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006FC34);

INCLUDE_ASM("asm/main/nonmatchings/main", f_SpawnAreaLinkedWeaponPickupActor);

INCLUDE_ASM("asm/main/nonmatchings/main", f_SpawnLinkedItemPickupActor);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006FFE8);

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

INCLUDE_ASM("asm/main/nonmatchings/main", f_ConfigureScriptActorConversation);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007074C);

extern s8 D_1F800214[];
void f_StartCurrentScriptActorConversation(void) {
    void *temp_v1;

    temp_v1 = *((void **)D_1F800214);
    M2C_FIELD(temp_v1, s8 *, 6) = 0;
    M2C_FIELD(temp_v1, s8 *, 5) = 3;
}

INCLUDE_ASM("asm/main/nonmatchings/main", f_TrySetCurrentScriptActorStateActive);

INCLUDE_ASM("asm/main/nonmatchings/main", f_TryStartCurrentScriptActorAnimation2);

INCLUDE_ASM("asm/main/nonmatchings/main", f_TrySetCurrentScriptActorAnimation0);


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

INCLUDE_ASM("asm/main/nonmatchings/main", func_800725D4);

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

INCLUDE_ASM("asm/main/nonmatchings/main", f_PrepareInteriorTransition);

INCLUDE_ASM("asm/main/nonmatchings/main", f_BeginInteriorEntryTransition);

extern s8 D_800BF818;
void f_BeginInteriorExitTransition(void) {
    f_PrepareInteriorTransition();
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

INCLUDE_ASM("asm/main/nonmatchings/main", f_SetSoundEffectHandleVolume);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80074A60);

INCLUDE_ASM("asm/main/nonmatchings/main", f_ComputeDirectionalStereoVolume);

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

INCLUDE_ASM("asm/main/nonmatchings/main", f_ControlStreamedAudioTrack);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80075130);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80075240);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800752B4);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800753AC);


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

INCLUDE_ASM("asm/main/nonmatchings/main", func_80075A30);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80075A80);

INCLUDE_ASM("asm/main/nonmatchings/main", f_SetStreamedAudioVolumeTarget);

INCLUDE_ASM("asm/main/nonmatchings/main", f_RefreshSoundEffectHandleLifetime);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80075D58);

INCLUDE_ASM("asm/main/nonmatchings/main", f_QueueSoundEffectVoice);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80075F0C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80075FF8);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80076904);

INCLUDE_ASM("asm/main/nonmatchings/main", f_AdvanceActorSkeletalAnimation);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007703C);

INCLUDE_ASM("asm/main/nonmatchings/main", f_TestActorVisibilityAndQueueForRender);

INCLUDE_ASM("asm/main/nonmatchings/main", f_StepWrappedAngleToward);

INCLUDE_ASM("asm/main/nonmatchings/main", f_TestWrappedAngleSide);

INCLUDE_ASM("asm/main/nonmatchings/main", f_TestAndQueueActorForRender);

INCLUDE_ASM("asm/main/nonmatchings/main", f_TestAndQueueActorForRenderMode2);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80077870);

INCLUDE_ASM("asm/main/nonmatchings/main", f_TestAndQueueActorForRenderWithYOffset);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80077958);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800779D0);

INCLUDE_ASM("asm/main/nonmatchings/main", f_TestActorVisibilityWithXYZOffset);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80077ACC);

INCLUDE_ASM("asm/main/nonmatchings/main", f_StartActorTimedFrameSequence);

INCLUDE_ASM("asm/main/nonmatchings/main", f_AdvanceActorTimedFrameSequence);

INCLUDE_ASM("asm/main/nonmatchings/main", f_StartActorSkeletalAnimation);

INCLUDE_ASM("asm/main/nonmatchings/main", f_StartActorSkeletalAnimationBlend);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80077D64);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80077D8C);


void f_SetActorRenderTint(void *arg0, s8 arg1, s8 arg2, s8 arg3) {
    M2C_FIELD(arg0, s8 *, 0x18) = arg1;
    M2C_FIELD(arg0, s8 *, 0x19) = arg2;
    M2C_FIELD(arg0, s8 *, 0x1A) = arg3;
    M2C_FIELD(arg0, u8 *, 0xD) = (u8) (M2C_FIELD(arg0, u8 *, 0xD) | 2);
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_80077E3C);

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

INCLUDE_ASM("asm/main/nonmatchings/main", f_ApproximateVectorLength2D);

INCLUDE_ASM("asm/main/nonmatchings/main", f_ApproximateVectorLength3D);

INCLUDE_ASM("asm/main/nonmatchings/main", f_CalculateYawFromPositionToPoint);

INCLUDE_ASM("asm/main/nonmatchings/main", f_UnlockWarpDestinationAndAreaDoor);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800783DC);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80078610);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80078738);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80078770);

INCLUDE_ASM("asm/main/nonmatchings/main", f_GetWarpSectionDisplayName);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800787F8);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80078824);

extern s32 D_800BFE50;
s32 f_TestWarpDestinationUnlocked(s32 arg0) {
    return D_800BFE50 & (1 << arg0);
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_800788AC);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80078988);

INCLUDE_ASM("asm/main/nonmatchings/main", f_DrawMenuTextGlyphs);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80079014);

INCLUDE_ASM("asm/main/nonmatchings/main", f_DrawSmallMenuText);

INCLUDE_ASM("asm/main/nonmatchings/main", f_DrawTallMenuText);

INCLUDE_ASM("asm/main/nonmatchings/main", f_CalculateCenteredTextPositions);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80079464);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007ACC4);

extern M2C_UNK D_800ED058;
void func_8007AD14(void) {
    memset(&D_800ED058, 0, 0x40);
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007AD40);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007AD98);


void f_RetireSceneController(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0) = 0;
    M2C_FIELD(arg0, s32 *, 4) = 0;
}

INCLUDE_ASM("asm/main/nonmatchings/main", f_ReleaseActorModelParts);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007AE30);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007AF88);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007B008);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007B04C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007B0F0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007B18C);

INCLUDE_ASM("asm/main/nonmatchings/main", f_AllocateTemplateEffectSlot);


void func_8007B2AC(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0) = 0;
    M2C_FIELD(arg0, s32 *, 4) = 0;
    M2C_FIELD(arg0, s16 *, 0xC) = 0x1000;
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007B2C0);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007B38C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007B3F4);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007B45C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007BE18);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007BF20);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007C0D0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007C2A4);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007C3CC);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007C5E4);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007C620);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007C654);

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

INCLUDE_ASM("asm/main/nonmatchings/main", f_DrawMenuSelectionCursor);

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

INCLUDE_ASM("asm/main/nonmatchings/main", f_DrawLoadingIndicator);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007FDB0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8008007C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800803DC);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80080424);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80080750);

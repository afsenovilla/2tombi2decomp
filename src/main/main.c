#include "common.h"

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

INCLUDE_ASM("asm/main/nonmatchings/main", f_RequestStreamedAudioStop);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8001CF94);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8001CFC8);

INCLUDE_ASM("asm/main/nonmatchings/main", f_StartStreamedAudioRange);

INCLUDE_ASM("asm/main/nonmatchings/main", f_StartStreamedAudioTrack);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8001D41C);

INCLUDE_ASM("asm/main/nonmatchings/main", f_PlayOrStopVoiceLine);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8001D7C4);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8001D940);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8001DB38);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_800232F4);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80023320);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8002343C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80023454);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80023470);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8002348C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800234A8);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800234C8);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800234E8);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80023508);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80023528);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80023548);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800235A0);

INCLUDE_ASM("asm/main/nonmatchings/main", f_ResolveActiveColliderOffsetActorContact);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8002369C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80023764);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80023794);

INCLUDE_ASM("asm/main/nonmatchings/main", f_PushActorOutsidePartCylinder);

INCLUDE_ASM("asm/main/nonmatchings/main", f_ResolveActorPairCylinderContactClass);

INCLUDE_ASM("asm/main/nonmatchings/main", f_ResolveActorPartCylinderContactClass);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800240FC);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800241FC);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8002421C);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_800262A8);

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

INCLUDE_ASM("asm/main/nonmatchings/main", f_ReleaseInteriorTransitionControl);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_80031708);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80031744);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80031780);

INCLUDE_ASM("asm/main/nonmatchings/main", f_ProjectEffectPointToScreenAndDepth);

INCLUDE_ASM("asm/main/nonmatchings/main", f_SetEffectRenderTransform);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80031AC4);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80031D24);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80031F84);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800321D8);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800323FC);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8003265C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800328BC);

INCLUDE_ASM("asm/main/nonmatchings/main", f_DrawEffectPrimitiveListWithoutDepthCue);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80032918);

INCLUDE_ASM("asm/main/nonmatchings/main", f_SetEffectProjectionTransform);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80032A44);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_80034634);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80034670);

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
    temp_v0 = func_8009A600();
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

INCLUDE_ASM("asm/main/nonmatchings/main", func_8003F9A8);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_8003FB84);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8003FB94);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8003FBC4);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8003FC00);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8003FC78);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8003FC8C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8003FD10);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8003FE00);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8003FED8);

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

INCLUDE_ASM("asm/main/nonmatchings/main", f_LoadActorScript);

INCLUDE_ASM("asm/main/nonmatchings/main", f_LoadActorScriptCommand);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80040E54);

INCLUDE_ASM("asm/main/nonmatchings/main", f_ApplyActorScriptTransition);

INCLUDE_ASM("asm/main/nonmatchings/main", f_RunActorScriptInterpreter);

INCLUDE_ASM("asm/main/nonmatchings/main", f_PlaceActorOnTerrainSurface);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800412CC);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800412F4);

INCLUDE_ASM("asm/main/nonmatchings/main", f_ApplyActorOrientationToRotation);

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

INCLUDE_ASM("asm/main/nonmatchings/main", f_AdvanceActorAnimationAndStoreCompletion);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80041938);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800419C4);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80041A1C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80041AC0);

INCLUDE_ASM("asm/main/nonmatchings/main", f_InitializeActorFixedStepMotion);

INCLUDE_ASM("asm/main/nonmatchings/main", f_AdvanceActorFixedStepMotion);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80041C54);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80041D60);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80041F34);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80041FA8);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80041FCC);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80041FF8);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8004201C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80042090);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800420AC);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80042170);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800421CC);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8004223C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80042258);

INCLUDE_ASM("asm/main/nonmatchings/main", f_EndScriptedInteractionAudio);

INCLUDE_ASM("asm/main/nonmatchings/main", f_BeginScriptedInteractionAudio);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800423FC);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80042448);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800424F0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800425FC);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8004266C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80042690);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800426D8);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_80042DCC);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80042DF8);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80042E10);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80042EA4);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80042F70);

INCLUDE_ASM("asm/main/nonmatchings/main", f_RunScriptedActorInterpolatedMovementCommand);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800433FC);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80043634);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800436BC);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80043720);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80043858);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800438B4);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800438D4);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80043964);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800439A4);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800439E4);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80043A10);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80043A40);

INCLUDE_ASM("asm/main/nonmatchings/main", f_SetSharedScriptControlFlag);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80043BB0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80043BD4);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80043D8C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80043E9C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80043EBC);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80043EDC);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80044090);

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

INCLUDE_ASM("asm/main/nonmatchings/main", f_StartCooperativeDiscRead);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80044D8C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80044E84);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80044F58);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80045080);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800450BC);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8004514C);

INCLUDE_ASM("asm/main/nonmatchings/main", f_LoadResourceChunkIntoGroup);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800452C0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80045558);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_80049418);

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

INCLUDE_ASM("asm/main/nonmatchings/main", f_SetPickupWhiteTintEnabled);

INCLUDE_ASM("asm/main/nonmatchings/main", f_UpdatePickupBlinkRenderFlag);

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

INCLUDE_ASM("asm/main/nonmatchings/main", f_SetEquippedBackItemActor);

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

INCLUDE_ASM("asm/main/nonmatchings/main", f_AddItemWithMessage);

void f_AddItemWithoutMessage(void) {
    f_AddInventoryQuantity();
}

INCLUDE_ASM("asm/main/nonmatchings/main", f_CompactInventoryAfterRemoval);

INCLUDE_ASM("asm/main/nonmatchings/main", f_RemoveItemWithMessage);

INCLUDE_ASM("asm/main/nonmatchings/main", f_RemoveItemWithoutMessage);

INCLUDE_ASM("asm/main/nonmatchings/main", f_RemoveItemWithAltMessage);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8004D6D4);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8004D6F4);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8004D714);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8004D79C);

INCLUDE_ASM("asm/main/nonmatchings/main", f_TestWorldOrOtherPickupCollectedBit);

INCLUDE_ASM("asm/main/nonmatchings/main", f_TestAppleCollectedBit);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8004D8B0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8004D8D8);

INCLUDE_ASM("asm/main/nonmatchings/main", f_UpdateUsedItemAttachmentPresentation);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8004DBB0);

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

INCLUDE_ASM("asm/main/nonmatchings/main", f_QueueResourceMessage);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8004EDDC);

INCLUDE_ASM("asm/main/nonmatchings/main", f_ResetPopupRequest);

INCLUDE_ASM("asm/main/nonmatchings/main", f_ResetPopupDisplayEntry);

INCLUDE_ASM("asm/main/nonmatchings/main", f_RemoveOldestPopupDisplayEntry);

INCLUDE_ASM("asm/main/nonmatchings/main", f_CopyEncodedMessageSegment);

INCLUDE_ASM("asm/main/nonmatchings/main", f_FindEncodedMessagePage);

INCLUDE_ASM("asm/main/nonmatchings/main", f_MeasureEncodedMessageBlock);

INCLUDE_ASM("asm/main/nonmatchings/main", f_FormatPopupPayloadPage);

INCLUDE_ASM("asm/main/nonmatchings/main", f_AppendPopupDisplayEntry);

INCLUDE_ASM("asm/main/nonmatchings/main", f_PromoteNextPopupRequest);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8004F430);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8004F474);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8004F514);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8004F6D0);

INCLUDE_ASM("asm/main/nonmatchings/main", f_ForcePromotePopupRequest);

INCLUDE_ASM("asm/main/nonmatchings/main", f_QueuePopupMessage);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8004FB20);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8004FB4C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8004FD30);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8004FE84);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8004FFB4);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8005019C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800506B4);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800506D0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80050738);

INCLUDE_ASM("asm/main/nonmatchings/main", f_SetDoubleBufferedClearColor);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80050894);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800508A8);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80050970);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800509B4);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80050A0C);

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

INCLUDE_ASM("asm/main/nonmatchings/main", f_SetScaleMatrix);

INCLUDE_ASM("asm/main/nonmatchings/main", f_UpdateActorUnscaledModelTransforms);

INCLUDE_ASM("asm/main/nonmatchings/main", f_UpdateActorScaledModelTransforms);

INCLUDE_ASM("asm/main/nonmatchings/main", f_UpdateActorScaledOffsetModelTransforms);

INCLUDE_ASM("asm/main/nonmatchings/main", f_InitializeMultiPartActorModel);

INCLUDE_ASM("asm/main/nonmatchings/main", f_SetActorPartModel);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80051B34);

INCLUDE_ASM("asm/main/nonmatchings/main", f_InitializeSinglePartActorModel);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80051C8C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80051D20);

INCLUDE_ASM("asm/main/nonmatchings/main", f_TransformPointByModelPart);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80051E00);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80051E60);

INCLUDE_ASM("asm/main/nonmatchings/main", f_OpenCooperativeWorkerThread);

INCLUDE_ASM("asm/main/nonmatchings/main", f_YieldCurrentCooperativeWorker);

INCLUDE_ASM("asm/main/nonmatchings/main", f_TerminateCurrentCooperativeWorker);

INCLUDE_ASM("asm/main/nonmatchings/main", f_CloseCooperativeWorkerThread);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80052078);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_8005262C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80052694);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80052720);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800527C8);

INCLUDE_ASM("asm/main/nonmatchings/main", f_TryPrepareTombaForInteraction);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8005314C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800531DC);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800532A0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8005344C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800534B0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800535D4);

INCLUDE_ASM("asm/main/nonmatchings/main", f_CanTombaStartAttack);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80053670);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8005376C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800537B8);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800538E0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80053968);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80053BF8);

INCLUDE_ASM("asm/main/nonmatchings/main", f_ReleaseTombaInteractionTarget);

INCLUDE_ASM("asm/main/nonmatchings/main", f_ClearTombaInteractionState);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80053E50);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80053FDC);

INCLUDE_ASM("asm/main/nonmatchings/main", f_ResetTombaControlState);

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

INCLUDE_ASM("asm/main/nonmatchings/main", f_UpdateTombaModelOrientationFromFacing);

INCLUDE_ASM("asm/main/nonmatchings/main", f_ApplyTombaFacingYaw);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800552B8);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800552EC);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80055390);

INCLUDE_ASM("asm/main/nonmatchings/main", f_TryStartTombaContactAction);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80055704);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800557EC);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80055824);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80055844);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80055864);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800558B4);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800559F4);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80055C30);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80055C9C);

INCLUDE_ASM("asm/main/nonmatchings/main", f_UpdateTombaMovementOrientation);

INCLUDE_ASM("asm/main/nonmatchings/main", f_ReadTombaDirectionalInput);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_8005749C);

INCLUDE_ASM("asm/main/nonmatchings/main", f_UpdateTombaAirborneMotion);

INCLUDE_ASM("asm/main/nonmatchings/main", f_TryStartTombaSupportInteraction);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80057C08);

INCLUDE_ASM("asm/main/nonmatchings/main", f_SetTombaMiniatureForm);

INCLUDE_ASM("asm/main/nonmatchings/main", f_RebuildTombaAppearanceModelParts);

INCLUDE_ASM("asm/main/nonmatchings/main", f_ApplyTombaStatusCommand);

INCLUDE_ASM("asm/main/nonmatchings/main", f_InitializeTombaPlayerActor);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800588BC);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80058918);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80058F24);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80058F5C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8005950C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800597AC);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80059C60);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80059D28);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80059ED8);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8005A39C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8005A714);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8005A910);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_8005F1B0);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006228C);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_80064524);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800645CC);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800645E0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006483C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80064BA0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80064E48);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006506C);

extern u8 D_800BF870;

void func_80065374(void) {
    switch (D_800BF870) {                           /* irregular */
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

INCLUDE_ASM("asm/main/nonmatchings/main", func_800653F4);

INCLUDE_ASM("asm/main/nonmatchings/main", f_UpdateTombaTransitionTerrainContact);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800654D4);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800655A0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800655DC);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800656FC);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006585C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800658E4);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80065990);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80065A54);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800660AC);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800661E0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006625C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800662D8);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800663A8);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80066478);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80066538);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800665F4);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006670C);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_80067FE4);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006804C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80068214);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800682C4);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800683B8);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80068610);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006C59C);

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

INCLUDE_ASM("asm/main/nonmatchings/main", f_SetCameraPositionHorizontal);

INCLUDE_ASM("asm/main/nonmatchings/main", f_SetCameraPositionVertical);

INCLUDE_ASM("asm/main/nonmatchings/main", f_ApproachCameraPositionHorizontal);

INCLUDE_ASM("asm/main/nonmatchings/main", f_ApproachCameraPositionVertical);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006DAD8);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006DC38);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006DCF4);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006DEF0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006DF88);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006E010);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006E0F0);

INCLUDE_ASM("asm/main/nonmatchings/main", f_SetCameraMode);

INCLUDE_ASM("asm/main/nonmatchings/main", f_RestorePreviousCameraMode);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006E228);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006E294);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006E2FC);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006E360);

INCLUDE_ASM("asm/main/nonmatchings/main", f_SnapCameraPositionAndRebuildView);

INCLUDE_ASM("asm/main/nonmatchings/main", f_ApproachCameraPositionAndRebuildView);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006E464);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006E8F8);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006E918);

INCLUDE_ASM("asm/main/nonmatchings/main", f_UpdateCameraFollowTomba);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006EA7C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006EC44);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006EF38);

extern s32 D_800BFE48;

s32 func_8006EFF4(s32 arg0) {
    return ((s32) D_800BFE48 >> arg0) & 1;
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006F00C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8006F02C);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_80070650);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80070698);

INCLUDE_ASM("asm/main/nonmatchings/main", f_ConfigureScriptActorConversation);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007074C);

INCLUDE_ASM("asm/main/nonmatchings/main", f_StartCurrentScriptActorConversation);

INCLUDE_ASM("asm/main/nonmatchings/main", f_TrySetCurrentScriptActorStateActive);

INCLUDE_ASM("asm/main/nonmatchings/main", f_TryStartCurrentScriptActorAnimation2);

INCLUDE_ASM("asm/main/nonmatchings/main", f_TrySetCurrentScriptActorAnimation0);

INCLUDE_ASM("asm/main/nonmatchings/main", f_GetCurrentScriptActorControlState);

INCLUDE_ASM("asm/main/nonmatchings/main", f_LoadCurrentScriptActorScript);

INCLUDE_ASM("asm/main/nonmatchings/main", f_SetCurrentScriptActorMode);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_80071A3C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80071B44);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80071C48);

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

INCLUDE_ASM("asm/main/nonmatchings/main", f_ApplyInteriorEntranceDoorMirroredYaw);

INCLUDE_ASM("asm/main/nonmatchings/main", f_CloseInteriorEntranceDoor);

INCLUDE_ASM("asm/main/nonmatchings/main", f_InitializeInteriorDoorPartOpenYaw);

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

INCLUDE_ASM("asm/main/nonmatchings/main", f_PlaySoundEffectWithPitchOffset);

void func_8007483C(s32 arg0, s8 arg1, s8 arg2) {
    f_PlaySoundEffect(arg0 & 0xFF, arg1, arg2);
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007486C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007496C);

INCLUDE_ASM("asm/main/nonmatchings/main", f_SetSoundEffectHandleVolume);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80074A60);

INCLUDE_ASM("asm/main/nonmatchings/main", f_ComputeDirectionalStereoVolume);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80074B44);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80074BC4);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_80075024);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80075070);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800750A4);

INCLUDE_ASM("asm/main/nonmatchings/main", f_ControlStreamedAudioTrack);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80075130);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80075240);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800752B4);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800753AC);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800753D4);

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

INCLUDE_ASM("asm/main/nonmatchings/main", f_SetActorRenderTint);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80077E3C);

INCLUDE_ASM("asm/main/nonmatchings/main", f_QueueClass2Or9ActorForRender);

INCLUDE_ASM("asm/main/nonmatchings/main", f_QueueClass4ActorForRender);

INCLUDE_ASM("asm/main/nonmatchings/main", f_QueueClass5ActorForRender);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007A8E0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007A904);

INCLUDE_ASM("asm/main/nonmatchings/main", f_AllocateActorRecordByType);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007AA38);

INCLUDE_ASM("asm/main/nonmatchings/main", f_AllocateActorModelPart);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007AB20);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007AB44);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007AC14);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007AC40);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007AC6C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007AC98);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007ACC4);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007AD14);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007AD40);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007AD98);

INCLUDE_ASM("asm/main/nonmatchings/main", f_RetireSceneController);

INCLUDE_ASM("asm/main/nonmatchings/main", f_ReleaseActorModelParts);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007AE30);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007AF88);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007B008);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007B04C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007B0F0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007B18C);

INCLUDE_ASM("asm/main/nonmatchings/main", f_AllocateTemplateEffectSlot);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007B2AC);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007B2C0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8007B328);

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

INCLUDE_ASM("asm/main/nonmatchings/main", _bu_init);

INCLUDE_ASM("asm/main/nonmatchings/main", OpenEvent);

INCLUDE_ASM("asm/main/nonmatchings/main", TestEvent);

INCLUDE_ASM("asm/main/nonmatchings/main", EnableEvent);

INCLUDE_ASM("asm/main/nonmatchings/main", OpenTh);

INCLUDE_ASM("asm/main/nonmatchings/main", CloseTh);

INCLUDE_ASM("asm/main/nonmatchings/main", ChangeTh);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80080890);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800808A0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800808B0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800808E0);

INCLUDE_ASM("asm/main/nonmatchings/main", ChangeClearPAD);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80080930);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80080940);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80080ADC);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80080BE0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80080BF0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80080D64);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80080DC0);

extern u8 D_800A59A2;

u8 func_80080E64(void) {
    return D_800A59A2;
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_80080E74);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80080ED4);

INCLUDE_ASM("asm/main/nonmatchings/main", DrawSync);

INCLUDE_ASM("asm/main/nonmatchings/main", checkRECT);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800810F0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80081180);

INCLUDE_ASM("asm/main/nonmatchings/main", LoadImage);

INCLUDE_ASM("asm/main/nonmatchings/main", StoreImage);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800812D8);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80081390);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80081458);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80081504);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80081560);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800815D0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80081690);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80081768);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8008179C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80081C94);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80081CC8);

INCLUDE_ASM("asm/main/nonmatchings/main", SetDrawArea);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80081D78);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80081DB8);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80081FB0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80082220);

INCLUDE_ASM("asm/main/nonmatchings/main", f_EncodeGpuDrawAreaTopLeftCommand);

INCLUDE_ASM("asm/main/nonmatchings/main", f_EncodeGpuDrawAreaBottomRightCommand);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80082370);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8008238C);

extern s32 *D_800A5AA8;

s32 func_8008240C(void) {
    return *D_800A5AA8;
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_80082424);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80082504);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80082734);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80082970);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80082BF0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80082C14);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80082C28);

extern s32 *D_800A5AA8;
extern s32 *D_800A5AAC;
extern s32 *D_800A5AB0;
extern s32 *D_800A5AB4;

void func_80082C68(s32 arg0) {
    *D_800A5AA8 = 0x04000002;
    *D_800A5AAC = arg0;
    *D_800A5AB0 = 0;
    *D_800A5AB4 = 0x01000401;
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_80082CB0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80082CE0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80082D04);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80082FB4);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80083214);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80083364);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800834A0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800834D4);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80083618);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800836B8);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800837A4);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80083890);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800839D4);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80083AD0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80083AF8);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80083B20);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80083B30);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80083BF0);

INCLUDE_ASM("asm/main/nonmatchings/main", AddPrim);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80083C70);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80083CA0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80083CC0);

INCLUDE_ASM("asm/main/nonmatchings/main", SetDrawMove);

INCLUDE_ASM("asm/main/nonmatchings/main", SetTexWindow);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80083DB0);

INCLUDE_ASM("asm/main/nonmatchings/main", SetDrawMode);

INCLUDE_ASM("asm/main/nonmatchings/main", rsin);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80083EBC);

INCLUDE_ASM("asm/main/nonmatchings/main", rcos);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80083FF0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80083FF8);

INCLUDE_ASM("asm/main/nonmatchings/main", SquareRoot0);

INCLUDE_ASM("asm/main/nonmatchings/main", MulMatrix0);

INCLUDE_ASM("asm/main/nonmatchings/main", ApplyRotMatrix);

INCLUDE_ASM("asm/main/nonmatchings/main", MulMatrix);

INCLUDE_ASM("asm/main/nonmatchings/main", MulMatrix2);

INCLUDE_ASM("asm/main/nonmatchings/main", ApplyMatrix);

INCLUDE_ASM("asm/main/nonmatchings/main", ApplyMatrixSV);

INCLUDE_ASM("asm/main/nonmatchings/main", ScaleMatrix);

INCLUDE_ASM("asm/main/nonmatchings/main", SetRotMatrix);

INCLUDE_ASM("asm/main/nonmatchings/main", SetTransMatrix);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800846B0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800846D0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800846F0);

INCLUDE_ASM("asm/main/nonmatchings/main", RotTransPers);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80084730);

INCLUDE_ASM("asm/main/nonmatchings/main", TransposeMatrix);

INCLUDE_ASM("asm/main/nonmatchings/main", RotMatrix);

INCLUDE_ASM("asm/main/nonmatchings/main", RotMatrixZYX);

INCLUDE_ASM("asm/main/nonmatchings/main", RotMatrixX);

INCLUDE_ASM("asm/main/nonmatchings/main", RotMatrixY);

INCLUDE_ASM("asm/main/nonmatchings/main", RotMatrixZ);

INCLUDE_ASM("asm/main/nonmatchings/main", RotMatrixZXY);

INCLUDE_ASM("asm/main/nonmatchings/main", RotMatrix_gte);

INCLUDE_ASM("asm/main/nonmatchings/main", ratan2);

INCLUDE_ASM("asm/main/nonmatchings/main", _patch_gte);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800858BC);

INCLUDE_ASM("asm/main/nonmatchings/main", FlushCache);

INCLUDE_ASM("asm/main/nonmatchings/main", VSync);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80085A78);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80085B10);

INCLUDE_ASM("asm/main/nonmatchings/main", ResetCallback);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80085B50);

INCLUDE_ASM("asm/main/nonmatchings/main", DMACallback);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80085BB0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80085BE4);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80085C14);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80085C44);

extern u16 D_800AAD1A;

u16 CheckCallback(void) {
    return D_800AAD1A;
}

extern u16 *D_800ABDA8;

u16 func_80085C84(void) {
    return *D_800ABDA8;
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_80085C9C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80085CB4);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80085D8C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80085F5C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800860A4);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80086144);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800861BC);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800861E0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800861E8);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80086200);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80086210);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80086220);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80086230);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80086288);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800862F4);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80086320);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80086350);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8008639C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8008651C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800865C8);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800865F0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80086604);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80086620);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80086738);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80086764);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800867CC);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8008695C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80086970);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80086A3C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80086A80);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80086DB4);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80086EA4);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800870B4);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8008732C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800873BC);

INCLUDE_ASM("asm/main/nonmatchings/main", SysEnqIntRP);

INCLUDE_ASM("asm/main/nonmatchings/main", SysDeqIntRP);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80087458);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80087530);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800875DC);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800876A0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80087A40);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80087A60);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80087A80);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80087AA0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80087AEC);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80087BB8);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80087CB0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80087D84);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80087E2C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80087E64);

INCLUDE_ASM("asm/main/nonmatchings/main", PadSetAct);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80087F00);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80087F0C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80087F1C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80087FA0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80088210);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80088248);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8008831C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800883C4);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800887BC);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80088824);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80088840);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80088908);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800889A0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800889F4);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80088A54);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80088A74);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80088A88);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80088AA8);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80088AC8);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80088AE8);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80088B00);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80088C60);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80088CC8);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80088DBC);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80088DCC);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80088E88);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80089104);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8008913C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80089160);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80089194);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800892A4);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80089508);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800895E8);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80089620);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80089640);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800896E0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80089788);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800897F8);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80089860);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800898A0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80089930);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8008996C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80089994);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800899BC);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800899F0);

extern u8 D_800ABFC8;

u8 func_80089A00(void) {
    return D_800ABFC8;
}

extern u8 D_800ABFD8;

u8 func_80089A10(void) {
    return D_800ABFD8;
}

extern u8 D_800ABFD9;

u8 func_80089A20(void) {
    return D_800ABFD9;
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_80089A30);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80089A3C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80089AA8);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80089AC8);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80089ADC);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80089B10);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80089B44);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80089B64);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80089B84);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80089B98);

INCLUDE_ASM("asm/main/nonmatchings/main", CdControl);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80089CE8);

INCLUDE_ASM("asm/main/nonmatchings/main", CdControlB);

s32 func_80089F68(void) {
    func_8008B040();
    return 1;
}

s32 func_80089F88(void) {
    return func_8008B620() == 0;
}

s32 func_80089FA8(void) {
    return func_8008B720() == 0;
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_80089FC8);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80089FEC);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8008A00C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8008A110);

INCLUDE_ASM("asm/main/nonmatchings/main", f_ServiceCdControllerInterrupt);

INCLUDE_ASM("asm/main/nonmatchings/main", CD_sync);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8008A96C);

INCLUDE_ASM("asm/main/nonmatchings/main", CD_cw);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8008B040);

INCLUDE_ASM("asm/main/nonmatchings/main", CD_flush);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8008B19C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8008B28C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8008B2D8);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8008B4B8);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8008B620);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8008B720);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8008B80C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8008B818);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8008B8F0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8008BBC8);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8008BBE8);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8008BEAC);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8008BF50);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8008C1EC);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8008C260);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8008C294);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8008C508);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8008C5D8);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8008C7C0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8008C960);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8008CAFC);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8008CC00);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8008CC14);

INCLUDE_ASM("asm/main/nonmatchings/main", CdRead2);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8008CCB4);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8008CCE0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8008CD40);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8008CDC0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8008CE4C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8008CEB0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8008CF40);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8008CFF0);

INCLUDE_ASM("asm/main/nonmatchings/main", StGetNext);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8008D0F0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8008D110);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8008DA2C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8008DA58);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8008DC00);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8008DD7C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8008DDA0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8008DDD0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8008DE74);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8008DEF4);

INCLUDE_ASM("asm/main/nonmatchings/main", _SsInit);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8008E040);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8008E080);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8008E0C0);

INCLUDE_ASM("asm/main/nonmatchings/main", SsSeqOpen);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8008E390);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8008E410);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8008E790);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8008E860);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8008E930);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8008EA20);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8008EAD0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8008EB60);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8008EC60);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8008EDA0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8008EE10);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8008EE80);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8008EF40);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8008EFD0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8008F090);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8008F120);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8008F1B0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8008F260);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8008F2BC);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8008F360);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8008F420);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8008F4D0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8008F580);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8008F630);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8008F6F0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8008F7A0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8008F850);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8008F930);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8008F9D0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8008FA70);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8008FAA0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8008FAD0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8008FB00);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8008FB30);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8008FB60);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8008FC10);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8008FE40);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80090010);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800900F0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80090160);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80090210);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80090560);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80090598);

INCLUDE_ASM("asm/main/nonmatchings/main", Snd_SetPlayMode);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80090700);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80090750);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80090980);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800909A0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800909C0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80090A0C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80090A60);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80090AFC);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80090B34);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80090B64);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80090B98);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80090BD0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80090E40);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80091050);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800910F0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80091120);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8009121C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80091460);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80091810);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80091910);

INCLUDE_ASM("asm/main/nonmatchings/main", _SsSndStop);

INCLUDE_ASM("asm/main/nonmatchings/main", SsSeqStop);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80091B18);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80091B50);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80091D70);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80091EC0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80091F50);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80091FB8);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80092048);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80092080);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800922A0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80092310);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80092420);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80092660);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800929BC);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80092A30);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80092A70);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80092B00);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80092B9C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80092BB0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80092BF0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80092C10);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80092C30);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80092E00);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80092E3C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80092EA0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80092F4C);

INCLUDE_ASM("asm/main/nonmatchings/main", _SsVmDoAllocate);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800931A0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800931B0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800931C0);

INCLUDE_ASM("asm/main/nonmatchings/main", _SsVmInit);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800939A0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80093EBC);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8009401C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80094108);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8009413C);

INCLUDE_ASM("asm/main/nonmatchings/main", _SsVmAlloc);

INCLUDE_ASM("asm/main/nonmatchings/main", note2pitch);

INCLUDE_ASM("asm/main/nonmatchings/main", note2pitch2);

INCLUDE_ASM("asm/main/nonmatchings/main", SsPitchFromNote);

INCLUDE_ASM("asm/main/nonmatchings/main", vmNoiseOn);

INCLUDE_ASM("asm/main/nonmatchings/main", vmNoiseOff);

INCLUDE_ASM("asm/main/nonmatchings/main", _SsVmKeyOffNow);

INCLUDE_ASM("asm/main/nonmatchings/main", _SsVmKeyOnNow);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800950E0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800952CC);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800953B0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80095420);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80095470);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800954E0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80095530);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80095A9C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80095B00);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80095B48);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80095B90);

INCLUDE_ASM("asm/main/nonmatchings/main", _SsVmSelectToneAndVag);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80095D10);

INCLUDE_ASM("asm/main/nonmatchings/main", _SsVmVSetUp);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80096370);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80096380);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80096390);

INCLUDE_ASM("asm/main/nonmatchings/main", SsSetReservedVoice);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800963D0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80096480);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800964B4);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80096520);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80096554);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80096588);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80096590);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80096980);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80096A40);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80096A70);

INCLUDE_ASM("asm/main/nonmatchings/main", _SpuInit);

INCLUDE_ASM("asm/main/nonmatchings/main", SpuStart);

INCLUDE_ASM("asm/main/nonmatchings/main", _spu_init);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80096E70);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80097030);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800970EC);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80097194);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80097414);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80097498);

INCLUDE_ASM("asm/main/nonmatchings/main", _spu_FsetRXX);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80097540);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800975E4);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80097620);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80097678);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800976A0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800976C8);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80097730);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80097760);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800977C0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80097A90);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80097D90);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80097E10);

INCLUDE_ASM("asm/main/nonmatchings/main", _SpuSetAnyVoice);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80098100);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80098150);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80098220);

INCLUDE_ASM("asm/main/nonmatchings/main", _SpuIsInAllocateArea_);

INCLUDE_ASM("asm/main/nonmatchings/main", SpuSetReverbModeParam);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80098810);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80098CE0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80098D30);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80098DB0);

INCLUDE_ASM("asm/main/nonmatchings/main", SpuClearReverbWorkArea);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80098F80);

INCLUDE_ASM("asm/main/nonmatchings/main", SpuSetKey);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80099150);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800991B0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80099310);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80099370);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800993A0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80099450);

extern s32 D_800AC638;

s32 func_80099478(void) {
    return D_800AC638 != 1;
}

INCLUDE_ASM("asm/main/nonmatchings/main", SpuSetCommonAttr);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80099810);

INCLUDE_ASM("asm/main/nonmatchings/main", func_800998E4);

INCLUDE_ASM("asm/main/nonmatchings/main", SpuSetVoiceAttr);

INCLUDE_ASM("asm/main/nonmatchings/main", func_80099F70);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8009A040);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8009A170);

INCLUDE_ASM("asm/main/nonmatchings/main", SpuGetVoiceEnvelope);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8009A1F0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8009A31C);

INCLUDE_ASM("asm/main/nonmatchings/main", bzero);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8009A370);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8009A3A4);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8009A3E0);

INCLUDE_ASM("asm/main/nonmatchings/main", memset);

INCLUDE_ASM("asm/main/nonmatchings/main", rand);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8009A480);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8009A490);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8009A540);

INCLUDE_ASM("asm/main/nonmatchings/main", strcpy);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8009A600);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8009A640);

INCLUDE_ASM("asm/main/nonmatchings/main", todigit);

INCLUDE_ASM("asm/main/nonmatchings/main", printf);

INCLUDE_ASM("asm/main/nonmatchings/main", prnt);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8009AE10);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8009AE60);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8009AF5C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8009AF98);

INCLUDE_ASM("asm/main/nonmatchings/main", sprintf);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8009B940);

INCLUDE_ASM("asm/main/nonmatchings/main", puts);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8009BA10);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8009BA4C);

INCLUDE_ASM("asm/main/nonmatchings/main", _card_info);

INCLUDE_ASM("asm/main/nonmatchings/main", _card_write);

INCLUDE_ASM("asm/main/nonmatchings/main", _new_card);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8009BB10);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8009BB7C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8009BBB4);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8009BBE0);

extern s32 D_800ACF44;

s32 func_8009BBEC(void) {
    return D_800ACF44;
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_8009BBFC);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8009BC8C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8009BD1C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8009BD4C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8009BD84);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8009BDFC);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8009BE34);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8009BE9C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8009BEE0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8009BEF0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8009BF00);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8009BF10);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8009BF20);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8009BF34);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8009BF48);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8009BFC0);

INCLUDE_ASM("asm/main/nonmatchings/main", InitCARD2);

INCLUDE_ASM("asm/main/nonmatchings/main", StartCARD2);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8009C050);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8009C08C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8009C0D0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8009C0F8);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8009C18C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8009C1FC);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8009C230);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8009C2B0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8009C3F4);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8009C600);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8009C610);

void func_8009C620(s32 arg0) {
    if (arg0 == 0) {
        ResetCallback();
    }
    func_8009C8E0(arg0);
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_8009C654);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8009C6E0);

u16 func_8009C778(u16 *arg0) {
    return *arg0;
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_8009C784);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8009C800);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8009C820);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8009C85C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8009C898);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8009C8BC);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8009C8E0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8009C9D0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8009CA60);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8009CAEC);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8009CB80);

extern s32 *D_800AD098;

s32 func_8009CC14(void) {
    return *D_800AD098;
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_8009CC2C);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8009CCB0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8009CCE0);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8009D030);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8009D044);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8009D058);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8009D06C);

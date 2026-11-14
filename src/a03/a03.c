#include "common.h"
#include "game.h"
#include "m2c.h"

INCLUDE_ASM("asm/a03/nonmatchings/a03", f_UpdateTombaTrolleyRaceActor);

INCLUDE_ASM("asm/a03/nonmatchings/a03", f_UpdateTrolleyAttachedModelTransforms);

INCLUDE_ASM("asm/a03/nonmatchings/a03", func_80109BC8);

INCLUDE_ASM("asm/a03/nonmatchings/a03", func_80109C48);

INCLUDE_ASM("asm/a03/nonmatchings/a03", f_UpdateAndDrawTrolleyRiderModel);

INCLUDE_ASM("asm/a03/nonmatchings/a03", f_SetTrolleyHudSegmentEnabled);

INCLUDE_ASM("asm/a03/nonmatchings/a03", f_DrawTrolleyRaceHud);

extern M2C_UNK D_800F2418;
void func_8010B328(void) {
    func_8004FD30();
    func_80025D98();
    f_DrawTrolleyRaceHud();
    f_UpdateAndDrawTrolleyRiderModel();
    func_8003BCF4();
    func_801109D4(&D_800F2418);
    func_8003C048();
}

INCLUDE_ASM("asm/a03/nonmatchings/a03", f_UpdatePlayerTrolleyActor);

INCLUDE_ASM("asm/a03/nonmatchings/a03", func_8010B738);

INCLUDE_ASM("asm/a03/nonmatchings/a03", f_CollectNearbyTrolleySeeds);

INCLUDE_ASM("asm/a03/nonmatchings/a03", func_8010BBB8);

INCLUDE_ASM("asm/a03/nonmatchings/a03", f_InitializeTrolleyModelAndTrackState);

INCLUDE_ASM("asm/a03/nonmatchings/a03", f_SampleAirborneTrolleyTrack);

INCLUDE_ASM("asm/a03/nonmatchings/a03", f_SampleGroundedTrolleyTrack);

INCLUDE_ASM("asm/a03/nonmatchings/a03", func_8010C678);

INCLUDE_ASM("asm/a03/nonmatchings/a03", f_UpdateTrolleyRaceCamera);

INCLUDE_ASM("asm/a03/nonmatchings/a03", f_UpdateTrolleySteeringInput);

INCLUDE_ASM("asm/a03/nonmatchings/a03", f_UpdateUpgradedTrolleyPhysics);

INCLUDE_ASM("asm/a03/nonmatchings/a03", f_UpdateStandardTrolleyPhysics);

INCLUDE_ASM("asm/a03/nonmatchings/a03", f_UpdateTrolleyMovementAndCamera);

INCLUDE_ASM("asm/a03/nonmatchings/a03", f_UpdateTrolleyCourseProgressActor);

INCLUDE_ASM("asm/a03/nonmatchings/a03", f_UpdateDetachedTrolleyActor);

extern M2C_UNK D_8011B748;
s32 func_8010E820(void *arg0) {
    return (u32) &D_8011B748 < (u32) M2C_FIELD(arg0, u32 *, 0x60);
}

INCLUDE_ASM("asm/a03/nonmatchings/a03", func_8010E834);


void func_8010E8F4(s32 arg0) {
    s16 temp_v1;
    void *temp_a0;

    temp_a0 = arg0 + 0x60;
    temp_v1 = M2C_FIELD(temp_a0, s16 *, 0xC);
    if (temp_v1 < 0x8D0) {
        M2C_FIELD(temp_a0, s16 *, 0xC) = 0x8D0;
        return;
    }
    if (temp_v1 >= 0x1A81) {
        M2C_FIELD(temp_a0, s16 *, 0xC) = 0x1A80;
    }
}


void func_8010E92C(s32 arg0) {
    s16 temp_v1;
    void *temp_a0;

    temp_a0 = arg0 + 0x60;
    temp_v1 = M2C_FIELD(temp_a0, s16 *, 0xC);
    if (temp_v1 < 0x8D0) {
        M2C_FIELD(temp_a0, s16 *, 0xC) = 0x8D0;
        return;
    }
    if (temp_v1 >= 0x3511) {
        M2C_FIELD(temp_a0, s16 *, 0xC) = 0x3510;
    }
}

INCLUDE_ASM("asm/a03/nonmatchings/a03", func_8010E964);

INCLUDE_ASM("asm/a03/nonmatchings/a03", func_8010EC34);

extern u16 *D_800ECF78;

void func_8010F174(u8 *a)
{
    u16 *p = D_800ECF78;
    u16 t;

    *(u16 **)(a + 0xC) = p;
    *(u16 *)(a + 8) = p[0];
    t = p[1];
    a[7] = 0;
    *(u16 *)(a + 0xA) = t;
}

INCLUDE_ASM("asm/a03/nonmatchings/a03", f_SubdivideProjectedTrolleyQuad);

INCLUDE_ASM("asm/a03/nonmatchings/a03", f_DrawSubdividedTrolleyTexturedQuad);

INCLUDE_ASM("asm/a03/nonmatchings/a03", f_DrawTrolleyMeshTriangles);

INCLUDE_ASM("asm/a03/nonmatchings/a03", f_DrawTrolleyMeshQuads);

INCLUDE_ASM("asm/a03/nonmatchings/a03", func_801109D4);

INCLUDE_ASM("asm/a03/nonmatchings/a03", func_80110B00);

INCLUDE_ASM("asm/a03/nonmatchings/a03", f_UpdateTrolleyTrailActor);

INCLUDE_ASM("asm/a03/nonmatchings/a03", func_80111158);


void func_801113B4(s32 arg0) {
    func_80110B00(4, arg0 + 0x3C, 0x10);
}

INCLUDE_ASM("asm/a03/nonmatchings/a03", func_801113DC);

INCLUDE_ASM("asm/a03/nonmatchings/a03", f_UpdateTrolleyFinishMenu);

INCLUDE_ASM("asm/a03/nonmatchings/a03", f_UpdateTrolleyRetryMenu);

INCLUDE_ASM("asm/a03/nonmatchings/a03", f_UpdateTrolleyCourseOverlayActor);

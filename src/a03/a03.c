#include "common.h"
#include "game.h"
#include "m2c.h"

INCLUDE_ASM("asm/a03/nonmatchings/a03", f_UpdateTombaTrolleyRaceActor);

INCLUDE_ASM("asm/a03/nonmatchings/a03", f_UpdateTrolleyAttachedModelTransforms);

INCLUDE_ASM("asm/a03/nonmatchings/a03", func_80109BC8);

typedef struct CdMixAttr {
      u32 mask;
      u8 pad4[0x14];
      s32 mix;
      u8 pad1C[0xC];
} CdMixAttr;
extern u8 D_8011C0E8[];
typedef struct SVec { s16 vx, vy, vz, pad; } SVec;
typedef struct { u8 pad0[0xC]; s32 x; s32 y; s32 z; } CameraTarget;
typedef struct Range8b { s32 sector; s32 size; } Range8b;
typedef struct Linked { u8 pad0; u8 active; u8 pad2[0x1A]; void (*callback)(struct Linked *); u8 pad20[4]; struct Linked *next; } Linked;
typedef struct { u8 pad[0x48]; s32 n; } Counter48_808;
typedef struct CameraTarget2 { u8 pad0[2]; u16 x; u8 pad4[2]; u16 y; u8 pad8[2]; u16 z; } CameraTarget2;
typedef struct ChildList {
      u8 pad0[8];
      s16 count;
      u8 padA[2];
      u8 *children[1];
} ChildList;
typedef struct SoundHandle3 { u32 id; u8 pad4[8]; } SoundHandle3;
typedef struct ChildList2 {
      u8 pad0[3];
      u8 active;
      u8 pad4[4];
      s16 count;
      u8 padA[2];
      u8 *children[1];
} ChildList2;
typedef struct EventReward { u8 pad0; u8 ap; u8 pad2[10]; } EventReward;
typedef struct { u8 pad[0xC0]; u8 *parts[64]; } PartOwner;
typedef struct { s32 x, y, z; } Vec3i_74C;
typedef struct { u8 pad[0x1C]; Vec3i_74C v; } ConvTarget_74C;
typedef struct { u8 pad[0x2C]; Vec3i_74C pos; } PosHolder_858;
typedef struct UiRect { s16 x, y, w, h; } UiRect;
typedef struct { s32 sector; s32 size; } FileLoc_1E0;
typedef struct { u8 pad[0xA4]; void *a; void *pad2; void *b; } MenuText_854;
typedef struct { s32 x, y, z; } Vec3i_F08;
typedef struct { u8 pad[0x1C]; Vec3i_F08 v; } ConvTarget_F08;
typedef struct { s16 x, y, z; u8 flags; u8 pad; } SpawnPoint_8824;
typedef struct { u8 b[8]; } Bytes8_EE0;
typedef struct { u32 pos; u32 size; char name[16]; } CdFileLite;
typedef struct { u8 pad[0x48]; s32 bits; } Bits48_808;
typedef struct SoundHandle { u8 volume; u8 pad1[11]; } SoundHandle;
typedef struct Entry8 { u8 pad0[6]; u16 flags; } Entry8;
typedef struct Slot4C { u8 used; u8 pad[0x4B]; } Slot4C;
typedef struct Range8 { s32 sector; s32 size; } Range8;
typedef struct Slot40 { u8 used; u8 pad[0x3F]; } Slot40;
typedef struct SpuAttrLite { u32 mask; s16 mvolL; s16 mvolR; s16 h8; s16 hA; s16 hC; s16 hE; s16 h10; s16 h12; } SpuAttrLite;
typedef struct Slot4Cb { u8 b[0x4C]; } Slot4Cb;
typedef struct { u8 pad[0x18]; u8 isbg; u8 r0, g0, b0; } DrawEnvLite_E80A8;
typedef struct Slot40c { u8 pad0[7]; u8 index; u8 pad8[4]; s16 scale; u8 padE[0x32]; } Slot40c;
typedef struct Entry8w { u8 pad0[6]; u16 flags; } Entry8w;
typedef struct { u8 on; u8 flags; u8 pad[10]; } SpuVoiceSlot_238;

s32 func_80109C48(u8 *t, s32 anim, s32 blend)
{
    if (t[0x46] == (u8)anim) {
        return 0;
    }
    t[0x46] = anim;
    func_80054790(t, anim);
    if ((s16)blend == 0) {
        func_80077C40(t, D_8011C0E8, anim);
    } else {
        func_80077CFC(t, D_8011C0E8, anim, (s16)blend);
    }
    return 1;
}

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

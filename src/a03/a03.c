#include "common.h"
#include "game.h"
#include "m2c.h"

INCLUDE_ASM("asm/a03/nonmatchings/a03", f_UpdateTombaTrolleyRaceActor);

INCLUDE_ASM("asm/a03/nonmatchings/a03", f_UpdateTrolleyAttachedModelTransforms);

void func_80109BC8(u8 *a) {
    s32 n = 0;
    s32 i;

    for (i = 0; i < 7; i++) {
        if ((a[0x2B] >> i) & 1) {
            n++;
        }
    }
    if (n != 0) {
        func_8004D4F4(0x36, n);
        D_800BF870.pad1[0x187] |= a[0x2B];
    }
}

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

extern u8 D_80111AEC[];
void f_SetTrolleyHudSegmentEnabled(s32 i, s32 on) {
    if (i < 4) {
        if (on) {
            D_80111AEC[i * 8 + 0xA] |= 1;
        } else {
            D_80111AEC[i * 8 + 0xA] &= ~1;
        }
    } else if (i == 4) {
        if (on) {
            D_80111AEC[0x2A] |= 1;
            D_80111AEC[0x32] |= 1;
        } else {
            D_80111AEC[0x2A] &= ~1;
            D_80111AEC[0x32] &= ~1;
        }
    } else {
        if (on) {
            D_80111AEC[i * 8 + 0x12] |= 1;
        } else {
            D_80111AEC[i * 8 + 0x12] &= ~1;
        }
    }
}

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

#define F16(p, o) M2C_FIELD(p, s16 *, o)
#define FU16(p, o) M2C_FIELD(p, u16 *, o)
#define FP(p, o) M2C_FIELD(p, u8 **, o)
extern s8 D_800BF808[];
extern u8 D_80111BA8[];
/* func_8010E834, inlined */
static inline void inl_8010E834(u8 *a) {
    s8 *g = D_800BF808;
    u8 *q = a + 0x60;
    u8 b1[0x20];
    u8 b2[8];

    if (g[5] != 0) {
        return;
    }
    if ((u16)(M2C_FIELD(q, u16 *, 0xE) + 0x2AA) >= 0x555) {
        a[7] = 0;
        g[5] = 1;
        return;
    }
    if (!(q[0x12] & 1)) {
        return;
    }
    if (!(M2C_FIELD(M2C_FIELD(a, u8 **, 0x60), s16 *, 6) & 0x8000)) {
        return;
    }
    if (M2C_FIELD(f_SampleAirborneTrolleyTrack(M2C_FIELD(a, u8 **, 0x60), M2C_FIELD(q, s16 *, 0xA) - 0x3E8, b2, b1), s16 *, 6) & 0x8000) {
        a[7] = 1;
        g[5] = 1;
    }
}
void f_UpdateTrolleyMovementAndCamera(u8 *a) {
    u8 *q = a + 0x60;
    u8 *r;
    s32 d;

    q[0x12] &= 0xF1;
    FU16(a, 0x40)++;
    if (FP(a, 0x60) <= D_80111BA8) {
        F16(q, 0xC) = 0x8D0;
        F16(q, 0xE) = 0;
        F16(q, 0x10) = 0;
        F16(q, 0x16) = 0;
        q[0x12] |= 1;
    }
    if (a[4] == 1) {
        f_UpdateTrolleySteeringInput(a);
    } else {
        F16(q, 0xE) = F16(q, 0xE) >> 1;
        F16(q, 0x10) = F16(q, 0x10) >> 1;
        F16(q, 0xC) += (0x3C0 - F16(q, 0xC)) >> 6;
        if (F16(q, 0x16) < 0) {
            F16(q, 0x16)++;
        } else if (F16(q, 0x16) > 0) {
            F16(q, 0x16)--;
        }
    }
    if (D_800BF870.pad1[0x97] == 0xFF && D_800BF870.pad1[0x96] == D_800BF870.pad1[0x97]) {
        f_UpdateStandardTrolleyPhysics(a);
        r = a + 0x60;
        if (F16(r, 0xC) < 0x8D0) {
            F16(r, 0xC) = 0x8D0;
        } else if (F16(r, 0xC) > 0x3510) {
            F16(r, 0xC) = 0x3510;
        }
    } else {
        f_UpdateUpgradedTrolleyPhysics(a);
        r = a + 0x60;
        if (F16(r, 0xC) < 0x8D0) {
            F16(r, 0xC) = 0x8D0;
        } else if (F16(r, 0xC) > 0x1A80) {
            F16(r, 0xC) = 0x1A80;
        }
    }
    inl_8010E834(a);
    F16(a, 0x2E) = FU16(a, 0xAC);
    F16(a, 0x32) = FU16(a, 0xB0);
    F16(a, 0x36) = FU16(a, 0xB4);
    d = F16(q, 0xC) >> 2;
    F16(FP(a, 0xC4), 0xC) += d;
    F16(FP(a, 0xC8), 0xC) += d;
    F16(FP(a, 0xCC), 0xC) += d;
    F16(FP(a, 0xD0), 0xC) += d;
    if (a[4] == 1) {
        a[1] = 1;
        func_80077EBC(a);
    }
    func_80051300(a);
    f_UpdateTrolleyRaceCamera(a);
}

INCLUDE_ASM("asm/a03/nonmatchings/a03", f_UpdateTrolleyCourseProgressActor);

INCLUDE_ASM("asm/a03/nonmatchings/a03", f_UpdateDetachedTrolleyActor);

extern M2C_UNK D_8011B748;
s32 func_8010E820(void *arg0) {
    return (u32) &D_8011B748 < (u32) M2C_FIELD(arg0, u32 *, 0x60);
}

void func_8010E834(u8 *a) {
    s8 *g = D_800BF808;
    u8 *q = a + 0x60;
    u8 b1[0x20];
    u8 b2[8];

    if (g[5] != 0) {
        return;
    }
    if ((u16)(M2C_FIELD(q, u16 *, 0xE) + 0x2AA) >= 0x555) {
        a[7] = 0;
        g[5] = 1;
        return;
    }
    if (!(q[0x12] & 1)) {
        return;
    }
    if (!(M2C_FIELD(M2C_FIELD(a, u8 **, 0x60), s16 *, 6) & 0x8000)) {
        return;
    }
    if (M2C_FIELD(f_SampleAirborneTrolleyTrack(M2C_FIELD(a, u8 **, 0x60), M2C_FIELD(q, s16 *, 0xA) - 0x3E8, b2, b1), s16 *, 6) & 0x8000) {
        a[7] = 1;
        g[5] = 1;
    }
}

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

typedef struct {
    s16 x, y;
} Pair16;
extern Pair16 D_8011BB64;
extern u8 D_8011BB68[];
void func_801113DC(u8 *a) {
    u8 *p;
    s16 x, y;

    switch (a[4]) {
    case 0:
        a[4] = 1;
        x = D_8011BB64.x;
        y = D_8011BB64.y;
        M2C_FIELD(a, u8 **, 0x38) = NULL;
        M2C_FIELD(a, s16 *, 0x32) = 0;
        M2C_FIELD(a, s16 *, 0x44) = x;
        M2C_FIELD(a, s16 *, 0x46) = y;
    case 1:
        p = M2C_FIELD(a, u8 **, 0x38);
        M2C_FIELD(a, u8 **, 0x34) = p;
        if (p == NULL) {
            M2C_FIELD(a, u8 **, 0x38) = D_8011BB68;
            M2C_FIELD(a, u8 **, 0x34) = D_8011BB68;
        }
        a[1] = 1;
        break;
    case 2:
    case 3:
        func_8007A624(a);
        break;
    }
}

INCLUDE_ASM("asm/a03/nonmatchings/a03", f_UpdateTrolleyFinishMenu);

INCLUDE_ASM("asm/a03/nonmatchings/a03", f_UpdateTrolleyRetryMenu);

INCLUDE_ASM("asm/a03/nonmatchings/a03", f_UpdateTrolleyCourseOverlayActor);

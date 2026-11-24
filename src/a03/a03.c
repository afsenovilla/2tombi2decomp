#include "common.h"
#include "game.h"
#include "m2c.h"
#include "gte.h"

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

typedef struct TrkMat { s16 m[3][3]; s16 pad; s32 t[3]; } TrkMat;
typedef struct TrkNode {
    s16 pos[3];
    s16 flags;
    u8 pad8[8];
    s16 m[3][3];
    u8 pad22[2];
    union { s32 w; struct { s16 lo; s16 len; } h; } u2;
    union { s32 w; struct { s16 lo; s16 len; } h; } u;
    u8 pad2c[4];
} TrkNode;
extern TrkNode D_80111B48[];

TrkNode *f_SampleAirborneTrolleyTrack(TrkNode *n0, s32 dist, s16 *sv, TrkMat *m) {
    TrkNode *n = n0;
    s32 d = dist;
    TrkNode *cur;
    TrkNode *base;
    s32 t;
    s16 v;
    s32 dx, dy, dz;

    if (n == NULL) {
restart:
        n = D_80111B48;
    }
again:
    if (d >= 0) {
fwd:
        cur = n;
        n = cur + 1;
        if (n->u2.w == 0) goto found;
        if (d < cur->u2.h.len) goto found;
        do {
            d -= cur->u2.h.len;
        } while (0);
        goto fwd;
    } else {
        base = D_80111B48;
back:
        cur = n;
        n = cur - 1;
        if (n < base) {
            do {
                n++;
            } while (n->u2.w != 0);
            goto again;
        }
        d += n->u2.h.len;
        if (d < 0) goto back;
        {
            TrkNode *tmp = n;
            n = cur;
            cur = tmp;
        }
    }
found:
    if (n->u2.w == 0) goto restart;
    t = (d << 16) / cur->u2.h.len;
    dx = (n->pos[0] - cur->pos[0]) * t;
    dy = (n->pos[1] - cur->pos[1]) * t;
    dz = (n->pos[2] - cur->pos[2]) * t;
    v = cur->pos[0] + (dx >> 16);
    sv[0] = v;
    m->t[0] = v;
    v = cur->pos[1] + (dy >> 16);
    sv[1] = v;
    m->t[1] = v;
    v = cur->pos[2] + (dz >> 16);
    sv[2] = v;
    m->t[2] = v;
    sv[3] = d;
    {
        s16 (*cm)[3] = cur->m;
        if (!(n->flags & 0x8000)) {
            s16 (*nm)[3] = n->m;
            m->m[0][2] = cm[0][0] + (((nm[0][0] - cm[0][0]) * t) >> 16);
            m->m[1][2] = cm[1][0] + (((nm[1][0] - cm[1][0]) * t) >> 16);
            m->m[2][2] = cm[2][0] + (((nm[2][0] - cm[2][0]) * t) >> 16);
            m->m[0][1] = cm[0][1] + (((nm[0][1] - cm[0][1]) * t) >> 16);
            m->m[1][1] = cm[1][1] + (((nm[1][1] - cm[1][1]) * t) >> 16);
            m->m[2][1] = cm[2][1] + (((nm[2][1] - cm[2][1]) * t) >> 16);
            m->m[0][0] = cm[0][2] + (((nm[0][2] - cm[0][2]) * t) >> 16);
            m->m[1][0] = cm[1][2] + (((nm[1][2] - cm[1][2]) * t) >> 16);
            m->m[2][0] = cm[2][2] + (((nm[2][2] - cm[2][2]) * t) >> 16);
        }
    }
    return cur;
}

TrkNode *f_SampleGroundedTrolleyTrack(TrkNode *n0, s32 dist, s16 *sv, TrkMat *m) {
    TrkNode *n = n0;
    s32 d = dist;
    TrkNode *cur;
    TrkNode *base;
    s32 t;
    s16 v;
    s32 dx, dy, dz;

    if (n == NULL) {
restart:
        n = D_80111B48;
    }
again:
    if (d >= 0) {
fwd:
        cur = n;
        n = cur + 1;
        if (n->u2.w == 0) goto found;
        if (d < cur->u.h.len) goto found;
        do {
            d -= cur->u.h.len;
        } while (0);
        goto fwd;
    } else {
        base = D_80111B48;
back:
        cur = n;
        n = cur - 1;
        if (n < base) {
            do {
                n++;
            } while (n->u.w != 0);
            goto again;
        }
        d += n->u.h.len;
        if (d < 0) goto back;
        {
            TrkNode *tmp = n;
            n = cur;
            cur = tmp;
        }
    }
found:
    if (n->u.w == 0) goto restart;
    t = (d << 16) / cur->u.h.len;
    dx = (n->pos[0] - cur->pos[0]) * t;
    dy = (n->pos[1] - cur->pos[1]) * t;
    dz = (n->pos[2] - cur->pos[2]) * t;
    v = cur->pos[0] + (dx >> 16);
    sv[0] = v;
    m->t[0] = v;
    v = cur->pos[1] + (dy >> 16);
    sv[1] = v;
    m->t[1] = v;
    v = cur->pos[2] + (dz >> 16);
    sv[2] = v;
    m->t[2] = v;
    sv[3] = d;
    {
        s16 (*cm)[3] = cur->m;
        if (!(n->flags & 0x8000)) {
            s16 (*nm)[3] = n->m;
            m->m[0][2] = cm[0][0] + (((nm[0][0] - cm[0][0]) * t) >> 16);
            m->m[1][2] = cm[1][0] + (((nm[1][0] - cm[1][0]) * t) >> 16);
            m->m[2][2] = cm[2][0] + (((nm[2][0] - cm[2][0]) * t) >> 16);
            m->m[0][1] = cm[0][1] + (((nm[0][1] - cm[0][1]) * t) >> 16);
            m->m[1][1] = cm[1][1] + (((nm[1][1] - cm[1][1]) * t) >> 16);
            m->m[2][1] = cm[2][1] + (((nm[2][1] - cm[2][1]) * t) >> 16);
            m->m[0][0] = cm[0][2] + (((nm[0][2] - cm[0][2]) * t) >> 16);
            m->m[1][0] = cm[1][2] + (((nm[1][2] - cm[1][2]) * t) >> 16);
            m->m[2][0] = cm[2][2] + (((nm[2][2] - cm[2][2]) * t) >> 16);
        }
    }
    return cur;
}

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

extern s8 *D_800ECF58[];
#define GH(p, o) (*(s16 *)((u8 *)(p) + (o)))
typedef struct { u8 pad[0x10]; u16 cells[1]; } GridCellList;
static inline void tri_span_e610(u8 *a, s32 y, s32 l, s32 r) {
    s32 x;
    s16 *p;
    s32 off;

    if (y >= 0 && y < GH(a, 0xA)) {
        if (r >= GH(a, 8)) r = GH(a, 8) - 1;
        x = l;
        if (x < 0) x = 0;
        p = (s16 *)D_800ECF58[8];
        p += 2;
        off = x * GH(a, 0xA) + y;
        while (p += off, x <= r) {
            if (*p != -1) {
                u8 n = a[6];
                if (n < 0xFE) {
                    a[6] = n + 1;
                    ((GridCellList *)a)->cells[n] = *p;
                }
            }
            off = GH(a, 0xA);
            x++;
        }
    }
}
void func_8010EC34(u8 *a, s32 *p0, s32 *p1, s32 *p2) {
    s32 x0 = p0[0], y0 = p0[1];
    s32 x1 = p1[0], y1 = p1[1];
    s32 x2 = p2[0], y2 = p2[1];
    s32 t, dx1, dx2, dy1, dy2;
    s32 xl, xr, y;
    s32 sl1, sl2, sl3;

    if (y1 == y0 && y1 == y2) return;
    if (y1 < y0) { t = x0; x0 = x1; x1 = t; t = y0; y0 = y1; y1 = t; }
    if (y2 < y0) { t = x0; x0 = x2; x2 = t; t = y0; y0 = y2; y2 = t; }
    if (y2 < y1) { t = x1; x1 = x2; x2 = t; t = y1; y1 = y2; y2 = t; }
    dx1 = x1 - x0;
    dx2 = x2 - x0;
    dy1 = y1 - y0;
    dy2 = y2 - y0;
    if (y1 == y0) {
        if (x0 < x1) { xl = x0 << 16; xr = x1 << 16; }
        else { xl = x1 << 16; xr = x0 << 16; }
        sl1 = 0;
    } else {
        xl = xr = x0 << 16;
        sl1 = (dx1 << 16) / dy1;
    }
    xr += 0x10000;
    if (y1 == y2) sl2 = 0;
    else sl2 = ((x2 - x1) << 16) / (y2 - y1);
    sl3 = (dx2 << 16) / dy2;
    if (-dy2 * dx1 + dx2 * dy1 > 0) {
        for (y = y0; y < y1; y++) { tri_span_e610(a, y, xl >> 16, xr >> 16); xl += sl1; xr += sl3; }
        for (; y <= y2; y++) { tri_span_e610(a, y, xl >> 16, xr >> 16); xl += sl2; xr += sl3; }
    } else {
        for (y = y0; y < y1; y++) { tri_span_e610(a, y, xl >> 16, xr >> 16); xr += sl1; xl += sl3; }
        for (; y <= y2; y++) { tri_span_e610(a, y, xl >> 16, xr >> 16); xl += sl3; xr += sl2; }
    }
}

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

extern u16 D_800E7E68;
typedef struct { u8 pad[0x104]; u8 *s[6]; } TrolleyMenuText;
extern TrolleyMenuText D_800A2854;
typedef struct { s16 x, y, w, h; } TrolleyMenuRect;
s32 f_UpdateTrolleyFinishMenu(void) {
    u8 *strs[4];
    s32 ys[4];
    s32 xs[4];
    TrolleyMenuRect r;
    s32 i;
    s32 m;
    u8 sel;

    if (D_800E7E68 & 0x4000) {
        return *(u8 *)D_800BF808 + 1;
    }
    if (D_800E7E68 & 0x1000) {
        return 1;
    }
    if (D_800E7E68 & 0x40) {
        if (*(u8 *)D_800BF808 < 2) {
            *(u8 *)D_800BF808 = *(u8 *)D_800BF808 + 1;
            func_80074590(0x15, 0, 0);
        }
    } else if (D_800E7E68 & 0x10) {
        if (*(u8 *)D_800BF808 != 0) {
            *(u8 *)D_800BF808 = *(u8 *)D_800BF808 - 1;
            func_80074590(0x15, 0, 0);
        }
    }
    ys[0] = 0x50;
    ys[1] = 0x64;
    ys[2] = 0x78;
    strs[0] = D_800A2854.s[3];
    strs[1] = D_800A2854.s[4];
    strs[2] = D_800A2854.s[5];
    func_800793C4(strs, 3, xs);
    if (xs[0] < xs[1]) {
        m = xs[2];
        if (xs[0] < m) {
            m = xs[0];
        }
    } else {
        m = xs[2];
        if (xs[1] < m) {
            m = xs[1];
        }
    }
    for (i = 0; i < 3; i++) {
        s16 x = m;

        sel = *(u8 *)D_800BF808;
        func_80079374(x, (s16)ys[i], (sel == i) * 2, strs[i], 0);
    }
    func_8007E998(m - 0x10, ys[*(u8 *)D_800BF808] + 4, 0);
    r.x = m - 0x20;
    r.w = (0xA0 - m) * 2 + 0x30;
    r.h = 0x40;
    r.y = ys[0] - 4;
    func_8005019C(&r, 0, 1, 1);
    return 0;
}

s32 f_UpdateTrolleyRetryMenu(void) {
    u8 *strs[4];
    s32 ys[4];
    s32 xs[4];
    TrolleyMenuRect r;
    s32 i;
    s32 k;
    u8 sel;

    if (D_800E7E68 & 0x4000) {
        return *(u8 *)D_800BF808 + 1;
    }
    if (D_800E7E68 & 0x40) {
        if (*(u8 *)D_800BF808 == 0) {
            *(u8 *)D_800BF808 = *(u8 *)D_800BF808 + 1;
            func_80074590(0x15, 0, 0);
        }
    } else if (D_800E7E68 & 0x10) {
        if (*(u8 *)D_800BF808 != 0) {
            *(u8 *)D_800BF808 = *(u8 *)D_800BF808 - 1;
            func_80074590(0x15, 0, 0);
        }
    }
    strs[0] = D_800A2854.s[0];
    func_800793C4(strs, 1, xs);
    i = 0;
    func_80079374((s16)xs[0], 0x70, i, strs[0], 0);
    r.y = 0x6C;
    ys[0] = 0x84;
    ys[1] = 0x98;
    r.x = xs[0] - 0x10;
    r.w = (0xA0 - xs[0]) * 2 + 0x20;
    strs[0] = D_800A2854.s[1];
    strs[1] = D_800A2854.s[2];
    k = func_800793C4(strs, 2, xs);
loop:
    do {
        sel = *(u8 *)D_800BF808;
        func_80079374((s16)xs[i], (s16)ys[i], (sel == i) * 2, strs[i], 0);
    } while (0);
    i++;
    if (i < 2) {
        goto loop;
    }
    func_8007E998(k, ys[*(u8 *)D_800BF808] + 4, 0);
    r.h = 0x40;
    func_8005019C(&r, 0, 1, 1);
    return 0;
}

INCLUDE_ASM("asm/a03/nonmatchings/a03", f_UpdateTrolleyCourseOverlayActor);

#include "common.h"
#include "game.h"
#include "m2c.h"
#include "gte.h"

INCLUDE_ASM("asm/a03/nonmatchings/a03", f_UpdateTombaTrolleyRaceActor);

typedef struct { u8 pad[0xC0]; u8 *parts[64]; } PartOwner;
extern u8 D_1F800000[];
extern u8 D_1F800020[];
extern u8 D_1F800040[];
#define H16(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define W32(p, o) (*(s32 *)((u8 *)(p) + (o)))
void f_UpdateTrolleyAttachedModelTransforms(u8 *a) {
    u8 *o = *(u8 **)(a + 0x10);
    u8 *s = D_1F800000;
    u8 *m;
    s32 i;
    s32 pad[8];

    H16(a, 0x98) = H16(o, 0x98);
    H16(a, 0x9E) = H16(o, 0x9E);
    H16(a, 0xA4) = H16(o, 0xA4);
    H16(a, 0x9A) = H16(o, 0x9A);
    H16(a, 0xA0) = H16(o, 0xA0);
    H16(a, 0xA6) = H16(o, 0xA6);
    H16(a, 0x9C) = H16(o, 0x9C);
    H16(a, 0xA2) = H16(o, 0xA2);
    H16(a, 0xA8) = H16(o, 0xA8);
    func_800517BC(s, H16(a, 0xB8), H16(a, 0xBA), H16(a, 0xBC));
    m = a + 0x98;
    func_80084360(s, m);
    i = 0;
    H16(a, 0x2E) = H16(o, 0x2E) - ((H16(a, 0x9A) * H16(a, 0x84)) >> 12);
    H16(a, 0x32) = H16(o, 0x32) - ((H16(a, 0xA0) * H16(a, 0x84)) >> 12);
    H16(a, 0x36) = H16(o, 0x36) - ((H16(a, 0xA6) * H16(a, 0x84)) >> 12);
    H16(a, 0x2E) += (H16(a, 0x98) * 37) >> 11;
    H16(a, 0x32) += (H16(a, 0x9E) * 37) >> 11;
    H16(a, 0x36) += (H16(a, 0xA4) * 37) >> 11;
    func_80084470(m, a + 0x88, a + 0xAC);
    W32(a, 0xAC) += H16(a, 0x2E);
    W32(a, 0xB0) += H16(a, 0x32);
    W32(a, 0xB4) += H16(a, 0x36);
    if (a[8] != 0) {
        u8 *s0 = s;
        u8 *s1 = D_1F800020;
        u8 *s2 = D_1F800040;
        do {
            s32 k = H16(((PartOwner *)a)->parts[i], 6);
            func_800517BC(s0, H16(((PartOwner *)a)->parts[i], 0x38), H16(((PartOwner *)a)->parts[i], 0x3A), H16(((PartOwner *)a)->parts[i], 0x3C));
            func_80085480(((PartOwner *)a)->parts[i] + 8, s1);
            func_80084110(s1, s0, s2);
            if (k < 0) {
                func_80084110(a + 0x98, s2, ((PartOwner *)a)->parts[i] + 0x18);
                func_80084220(((PartOwner *)a)->parts[i], ((PartOwner *)a)->parts[i] + 0x2C);
                W32(((PartOwner *)a)->parts[i], 0x2C) += W32(a, 0xAC);
                W32(((PartOwner *)a)->parts[i], 0x30) += W32(a, 0xB0);
                W32(((PartOwner *)a)->parts[i], 0x34) += W32(a, 0xB4);
            } else {
                func_80084110(((PartOwner *)a)->parts[k] + 0x18, s2, ((PartOwner *)a)->parts[i] + 0x18);
                func_80084220(((PartOwner *)a)->parts[i], ((PartOwner *)a)->parts[i] + 0x2C);
                W32(((PartOwner *)a)->parts[i], 0x2C) += W32(((PartOwner *)a)->parts[k], 0x2C);
                W32(((PartOwner *)a)->parts[i], 0x30) += W32(((PartOwner *)a)->parts[k], 0x30);
                W32(((PartOwner *)a)->parts[i], 0x34) += W32(((PartOwner *)a)->parts[k], 0x34);
            }
            i++;
        } while (i < a[8]);
    }
}

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

extern u8 D_800E7E80[];
extern u8 D_1F800247;
void f_UpdateAndDrawTrolleyRiderModel(void) {
    u8 *a = D_800E7E80;

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
                    a[0x18] = ((s16)func_80083E80((D_1F800247 & 0xF) << 7) >> 6) + 0x30;
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
                    v = ((s16)func_80083E80((D_1F800247 & 0xF) << 7) >> 6) + 0x10;
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
    f_UpdateTrolleyAttachedModelTransforms(a);
    if (a[1] != 0) {
        func_8003CCA4(a);
    }
}

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
typedef struct { s32 obj; s32 idx; u8 pad8[8]; s32 a, b, c; s32 f1C; } TrkSeed_B738;
extern TrkSeed_B738 D_8011BA48[];
extern u8 D_800BF9F8;
void func_8010B738(void) {
    CameraTarget2 c;
    TrkSeed_B738 *e;
    s32 i;

    i = 0;
    e = D_8011BA48;
loop: {
        TrkNode *n = &D_80111B48[e->idx];
        if (!((D_800BF9F8 >> i) & 1)) {
            c.x = n->pos[0];
            c.y = n->pos[1];
            c.z = n->pos[2];
            c.x += (n->m[0][0] * e->a) >> 12;
            c.y += (n->m[1][0] * e->a) >> 12;
            c.z += (n->m[2][0] * e->a) >> 12;
            c.x += (n->m[0][1] * e->b) >> 12;
            c.y += (n->m[1][1] * e->b) >> 12;
            c.z += (n->m[2][1] * e->b) >> 12;
            c.x += (n->m[0][2] * e->c) >> 12;
            c.y += (n->m[1][2] * e->c) >> 12;
            c.z += (n->m[2][2] * e->c) >> 12;
            e->obj = func_8003116C(0x401, &c, 0, n);
            e->f1C = 0;
        } else {
            e->obj = 0;
        }
    }
    i++;
    e++;
    if (i < 5) goto loop;
}

extern u8 *D_1F800208;
extern TrkNode *D_8011BB50;
extern s32 D_8011BB54;
extern s32 D_8011BB58;
extern s32 D_8011BB5C;
typedef struct { s16 x, y, z; } TrkPos_B910;
void f_CollectNearbyTrolleySeeds(void) {
    u8 *r = D_800E7E80;
    u8 *a = D_1F800208;
    TrkPos_B910 p;
    TrkNode *cur;
    u8 *t;
    s32 i;

    f_UpdateTrolleyAttachedModelTransforms(r);
    {
        s16 x = *(s16 *)(((PartOwner *)r)->parts[1] + 0x2C);
        cur = *(TrkNode **)(a + 0x60);
        p.x = x;
    }
    p.y = *(s16 *)(((PartOwner *)r)->parts[1] + 0x30);
    p.z = *(s16 *)(((PartOwner *)r)->parts[1] + 0x34);
    t = a + 0x60;
    p.x -= (cur->m[0][2] * *(s16 *)(t + 0xA)) >> 12;
    p.y -= (cur->m[1][2] * *(s16 *)(t + 0xA)) >> 12;
    p.z -= (cur->m[2][2] * *(s16 *)(t + 0xA)) >> 12;
    if (D_8011BB50 != cur) {
        D_8011BB5C = 0;
    }
    if (!(*(s16 *)(r + 0x17E) & 0x8200)) {
        if (++D_8011BB5C < 3) {
            for (i = 0; i < 5; i++) {
                TrkNode *n = &D_80111B48[D_8011BA48[i].idx];
                u8 *o = (u8 *)D_8011BA48[i].obj;
                if (o != NULL) {
                    if (n == cur) {
                        s32 dx = *(s16 *)(o + 0x2C) - p.x;
                        s32 dy = *(s16 *)(o + 0x2E) - p.y;
                        s32 dz = *(s16 *)(o + 0x30) - p.z;
                        s32 d = (u16)func_80077FB0(dx * dx + dy * dy + dz * dz);
                        if (!(t[0x12] & 1)) {
                            d >>= 2;
                        }
                        if (d < 150) {
                            if (D_8011BA48[i].f1C == 0) {
                                u8 *s = func_800310F4(0x1F, 0);
                                if (s != NULL) {
                                    *(s16 *)(s + 0x2C) = *(s16 *)((u8 *)D_8011BA48[i].obj + 0x2C);
                                    *(s16 *)(s + 0x2E) = *(s16 *)((u8 *)D_8011BA48[i].obj + 0x2E);
                                    *(s16 *)(s + 0x30) = *(s16 *)((u8 *)D_8011BA48[i].obj + 0x30);
                                }
                                D_8011BA48[i].f1C = 1;
                                ((u8 *)D_8011BA48[i].obj)[4] = 2;
                                func_8004ED0C(0x36, 2);
                                r[0x2B] |= 1 << i;
                            }
                        } else {
                            D_8011BA48[i].f1C = 0;
                        }
                    } else {
                        D_8011BA48[i].f1C = 0;
                    }
                }
            }
        }
    }
    D_8011BB50 = *(TrkNode **)t;
    D_8011BB54 = *(s16 *)(t + 0xE);
    D_8011BB58 = *(s16 *)(t + 0x16);
}

typedef struct TrkMat { s16 m[3][3]; s16 pad; s32 t[3]; } TrkMat;
typedef struct { u8 pad0[0x12]; s16 h; s16 w; } TrkDims_BBB8;
extern TrkDims_BBB8 D_8011BAEC;
void func_8010BBB8(u8 *a, TrkMat *m, s32 ang) {
    TrkDims_BBB8 *d = &D_8011BAEC;
    s32 w = abs(d->w) + 0x1D;
    s32 h = abs(d->h) + 0x17;
    s32 c, s, x, y, z;
    s32 pad[2];

    if (ang < 0) {
        w = -w;
    }
    c = func_80083F50(ang);
    x = (w * c + h * func_80083E80(ang)) >> 12;
    s = func_80083E80(ang);
    y = (-w * s + h * func_80083F50(ang)) >> 12;
    x -= w;
    y -= h;
    m->t[0] += (x * m->m[0][2]) >> 12;
    m->t[1] += (x * m->m[1][2]) >> 12;
    m->t[2] += (x * m->m[2][2]) >> 12;
    m->t[0] += (y * m->m[0][1]) >> 12;
    m->t[1] += (y * m->m[1][1]) >> 12;
    m->t[2] += (y * m->m[2][1]) >> 12;
    z = -(abs(d->h) + 0x17) - *(s16 *)(a + 0x8A);
    m->t[0] += (z * m->m[0][1]) >> 12;
    m->t[1] += (z * m->m[1][1]) >> 12;
    m->t[2] += (z * m->m[2][1]) >> 12;
}

typedef struct { u16 v[7]; } TrkPartDef;
extern TrkPartDef D_8011BAEC_f106[];
extern u8 *D_800ECFA0;
extern u8 D_80111B48_f52e[];
typedef struct { s32 a, b; } TrkPair_BDEC;
extern TrkPair_BDEC D_8011BCD8[];
extern s32 D_8011C0D8;
extern s32 D_8011C0DC;
extern s32 D_1F80020C;
void f_UpdatePlayerTrolleyActor(u8 *a);
void f_InitializeTrolleyModelAndTrackState(u8 *a) {
    u8 *t = a + 0x60;
    TrkPartDef *d = D_8011BAEC_f106;
    GameState *g = &D_800BF870;
    u8 *base;
    s32 *offs;
    u8 *e;
    s32 i;

    a[8] = 5;
    a[9] = 5;
    base = D_800ECFA0;
    a[0xD] = 0;
    a[0xB] = 0;
    offs = (s32 *)(base + 4);
    for (i = 0; i < 5; d++, i++) {
        ((PartOwner *)a)->parts[i] = func_8007AAE8();
        *(u16 *)(((PartOwner *)a)->parts[i] + 6) = d->v[0];
        *(u16 *)(((PartOwner *)a)->parts[i] + 0) = d->v[1];
        *(u16 *)(((PartOwner *)a)->parts[i] + 2) = d->v[2];
        *(u16 *)(((PartOwner *)a)->parts[i] + 4) = d->v[3];
        *(u16 *)(((PartOwner *)a)->parts[i] + 8) = d->v[4];
        *(u16 *)(((PartOwner *)a)->parts[i] + 0xA) = d->v[5];
        *(u16 *)(((PartOwner *)a)->parts[i] + 0xC) = d->v[6];
        if (i == 0) {
            if (g->pad1[0x97] == 0xFF && g->pad1[0x96] == g->pad1[0x97]) {
                *(u8 **)(((PartOwner *)a)->parts[0] + 0x40) = base + offs[3];
            } else {
                *(u8 **)(((PartOwner *)a)->parts[i] + 0x40) = base + offs[0];
            }
        } else {
            *(u8 **)(((PartOwner *)a)->parts[i] + 0x40) = base + offs[1];
        }
    }
    *(s16 *)(a + 0x54) = 0;
    *(s16 *)(a + 0x56) = 0;
    *(s16 *)(a + 0x58) = 0;
    *(s16 *)(a + 0x8A) = 0;
    *(u8 **)t = D_80111B48_f52e;
    *(s16 *)(t + 0xC) = 0x8D0;
    t[0x12] = 1;
    *(s16 *)(t + 4) = 0;
    *(s16 *)(t + 6) = 0;
    *(s16 *)(t + 8) = 0;
    *(s16 *)(t + 0xA) = 0;
    *(s16 *)(t + 0x16) = 0;
    *(s16 *)(a + 0x4A) = 0;
    if (*(void **)(a + 0x1C) == f_UpdatePlayerTrolleyActor) {
        D_1F800208 = a;
        D_1F80020C = 0;
        e = func_800310F4(0x402, -0x3C);
        if (e != NULL) {
            *(s32 *)(e + 0x50) = 2;
            *(s32 *)(e + 0x54) = -0xA0;
            *(u8 **)(e + 0x10) = a;
        }
        e = func_800310F4(0x402, -0x3C);
        if (e != NULL) {
            *(s32 *)(e + 0x50) = 4;
            *(s32 *)(e + 0x54) = 0xA0;
            *(u8 **)(e + 0x10) = a;
        }
        {
            s32 *q0;
            s32 *q1;
            s32 *b;
            i = 0;
            b = &D_8011BCD8[0].a;
            q1 = b + 1;
            q0 = b;
            do {
                *q0 = 0;
                *q1 = 0;
                q1 += 2;
                i++;
                q0 += 2;
            } while (i < 0x80);
        }
        D_8011C0D8 = 0;
        D_8011C0DC = 0;
    }
    *(s16 *)(a + 0x42) = 0;
    *(s16 *)(t + 0x18) = 0;
    *(s16 *)(t + 0x1A) = 0;
    t[0x13] = 0;
}

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

extern s8 D_800BF80D;
extern u8 *D_8011BB60;
u8 *func_8007E038(s32, s32);
void f_UpdateTrolleyCourseProgressActor(u8 *a) {
    s32 y;

    switch (a[6]) {
    case 0:
        a[6] = 1;
        D_8011BB60 = func_8007E038(0x17, 3);
    case 1:
        f_UpdateTrolleyMovementAndCamera(a);
        y = *(s16 *)(a + 0x36);
        D_1F80020C &= ~7;
        if (y >= -0x5BA) {
            D_8011BB60[4] = 2;
            a[6]++;
        } else if (y >= -0x1829) {
            D_1F80020C |= 3;
        } else if (y >= -0x2960) {
            D_1F80020C |= 2;
        } else if (y >= -0x39C8) {
            D_1F80020C |= 1;
        }
        break;
    case 2:
        f_UpdateTrolleyMovementAndCamera(a);
        {
            s32 v = D_1F80020C & ~7;
            s32 z = *(s16 *)(a + 0x36);
            D_1F80020C = v;
            if (z >= 0xA72) {
                a[6]++;
            } else {
                D_1F80020C = v | 4;
            }
        }
        break;
    case 3:
        f_UpdateTrolleyMovementAndCamera(a);
        if (D_800BF80D != 0) {
            a[4] = 2;
        }
        break;
    }
}

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

#define gte_SetRotMatrix(r0) __asm__ volatile("lw	$12, 0( %0 );" "lw	$13, 4( %0 );" "ctc2	$12, $0;" "ctc2	$13, $1;" "lw	$12, 8( %0 );" "lw	$13, 12( %0 );" "lw	$14, 16( %0 );" "ctc2	$12, $2;" "ctc2	$13, $3;" "ctc2	$14, $4" : : "r"(r0) : "$12", "$13", "$14")
#define gte_SetTransMatrix(r0) __asm__ volatile("lw	$12, 20( %0 );" "lw	$13, 24( %0 );" "ctc2	$12, $5;" "lw	$14, 28( %0 );" "ctc2	$13, $6;" "ctc2	$14, $7" : : "r"(r0) : "$12", "$13", "$14")
#define gte_ldfcdir(r0, r1, r2) __asm__ volatile("ctc2	%0, $21;" "ctc2	%1, $22;" "ctc2	%2, $23" : : "r"(r0), "r"(r1), "r"(r2))
extern u8 D_1F8000F8[];
extern void *D_800ED8C8;
extern s32 D_8011C0E4;
extern s32 D_8011C0E0;
typedef struct {
    u8 pad0[6];
    u8 count;
    u8 pad7[5];
    u32 *tbl;
    u16 list[1];
} TrkPartList;
void func_801109D4(TrkPartList *a)
{
    u16 *p;
    u16 *end;
    void *ot;
    u32 *tbl;
    u32 *e;
    u32 v;
    void *r;
    if (a->count == 0) {
        return;
    }
    D_8011C0E4 = 0;
    D_8011C0E0 = 0;
    gte_ldfcdir(0, 0, 0);
    p = a->list;
    end = &a->list[a->count];
    tbl = a->tbl;
    ot = D_800ED8C8;
    gte_SetRotMatrix(D_1F8000F8);
    gte_SetTransMatrix(D_1F8000F8);
    for (; p < end; p++) {
        e = &tbl[*p];
        v = *e;
        r = f_DrawTrolleyMeshTriangles(e + 1, ot, v & 0xFF);
        v >>= 16;
        f_DrawTrolleyMeshQuads(r, ot, v & 0xFF);
    }
}

INCLUDE_ASM("asm/a03/nonmatchings/a03", func_80110B00);

INCLUDE_ASM("asm/a03/nonmatchings/a03", f_UpdateTrolleyTrailActor);

typedef struct { u16 a, b; } U16Pair_1158;
extern U16Pair_1158 D_8011BC28;
extern u8 D_8011BC2C[];
void func_80111158(u8 *a) {
    u8 *o = *(u8 **)(a + 0x10);
    u8 *t = o + 0x60;
    s32 k;
    u8 *p;

    switch (a[4]) {
    case 0:
        a[4] = 1;
        {
            u16 x = D_8011BC28.a;
            u16 y = D_8011BC28.b;
            *(u8 **)(a + 0x38) = NULL;
            *(u16 *)(a + 0x44) = x;
            *(u16 *)(a + 0x46) = y;
        }
    case 1:
        if (o[4] >= 2) {
            a[4] = 2;
            break;
        }
        p = *(u8 **)(a + 0x38);
        *(u8 **)(a + 0x34) = p;
        if (p == NULL) {
            *(u8 **)(a + 0x38) = D_8011BC2C;
            *(u8 **)(a + 0x34) = D_8011BC2C;
        }
        if (t[0x12] & *(s32 *)(a + 0x50)) {
            k = *(s32 *)(a + 0x54);
            *(s16 *)(a + 0x2C) = *(s16 *)(o + 0x2E);
            *(s16 *)(a + 0x2E) = *(s16 *)(o + 0x32);
            *(s16 *)(a + 0x30) = *(s16 *)(o + 0x36);
            *(s16 *)(a + 0x2C) += (*(s16 *)(o + 0x9C) * k) >> 12;
            *(s16 *)(a + 0x2E) += (*(s16 *)(o + 0xA2) * k) >> 12;
            *(s16 *)(a + 0x30) += (*(s16 *)(o + 0xA8) * k) >> 12;
            *(s16 *)(a + 0x2C) += -(*(s16 *)(o + 0x98) * 110) >> 12;
            *(s16 *)(a + 0x2E) += -(*(s16 *)(o + 0x9E) * 110) >> 12;
            *(s16 *)(a + 0x30) += -(*(s16 *)(o + 0xA4) * 110) >> 12;
            *(s16 *)(a + 0x2C) += (*(s16 *)(o + 0x9A) * 3) >> 6;
            *(s16 *)(a + 0x2E) += (*(s16 *)(o + 0xA0) * 3) >> 6;
            *(s16 *)(a + 0x30) += (*(s16 *)(o + 0xA6) * 3) >> 6;
            a[1] = 1;
        }
        break;
    case 2:
    case 3:
        func_8007A624(a);
        break;
    }
}

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

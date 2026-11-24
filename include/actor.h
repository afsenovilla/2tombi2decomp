#ifndef ACTOR_H
#define ACTOR_H

#include "common.h"

/* The actor record (0xC0 bytes, then the part pointers), as far as it is known. Names from Tomba2Edit's actor
 * simulator (game/actor_sim.py, docs/TOMBA2EDIT.md) and the matched functions; the type of each field is the access
 * the matched C uses most at that offset (a census of `a[0xNN]`, `H(a, 0xNN)`, `*(T *)(a + 0xNN)` and MEMBER_AT
 * over src/: 19k accesses, 2026-11-23), unknown fields are unk_XX. Other sizes at the same offset exist (the
 * positions are also read as s32 at 0x2C / 0x30 / 0x34, 0x0A as s16, 0x3C as a pointer, ...): m2c casts those.
 * Mainly for m2c drafts (tools/decomp.py --actor, tools/statemachine.py / dispatch.py --actor): matched C keeps its
 * byte-pointer forms (a[0x..], H(a, o), MEMBER_AT), which give the same code.
 * Pools: f_InitializeActorPools builds five pools of 0x34, 0x3A, 0x2A, 0x28 and 5 records; f_AllocateActor
 * (USA 0x80072DDC) takes one. State machines switch on state (a[4]) with sub-switches on mode (a[3]) / subState
 * (a[5]); list walkers test flags (a[0] & 1) and step through next (a + 0x24). */
typedef struct Actor {
    /* 0x00 */ u8 flags;            /* bit 0: in use (list walkers); T2E 0.5.0: the NPC template stores 9 here at init */
    /* 0x01 */ u8 active;
    /* 0x02 */ u8 kind;
    /* 0x03 */ u8 mode;             /* Tomba2Edit: slot; the second switch of the state machines */
    /* 0x04 */ u8 state;            /* the state machines' switch; 3: being destroyed (lifecycle); T2E: phase (0 init, 1 run, 3 release via func_8007A624) */
    /* 0x05 */ u8 subState;  /* T2E NPC template: 1 while its script runs */
    /* 0x06 */ u8 unk_06;
    /* 0x07 */ u8 unk_07;
    /* 0x08 */ u8 partFrame;
    /* 0x09 */ u8 partCount;
    /* 0x0A */ u8 unk_0A;           /* also s16 at 0x0A */
    /* 0x0B */ u8 renderKind;       /* also the render-mode mask */
    /* 0x0C */ u8 allocClass;       /* 6: transient effect */
    /* 0x0D */ u8 renderMode;
    /* 0x0E */ s16 unk_0E;          /* Tomba2Edit: pickupBit (u8) */
    /* 0x10 */ struct Actor *linked;
    /* 0x14 */ u8 *unk_14;          /* Tomba2Edit: quadKind (u8) */
    /* 0x18 */ void *unk_18;
    /* 0x1C */ void (*callback)(struct Actor *);
    /* 0x20 */ u8 *unk_20;
    /* 0x24 */ struct Actor *next;  /* list link (`for (p = D_800F2738; p; p = *(u8 **)(p + 0x24))`) */
    /* 0x28 */ u8 unk_28;
    /* 0x29 */ u8 unk_29;
    /* 0x2A */ u8 unk_2A;
    /* 0x2B */ u8 unk_2B;           /* list walkers skip an actor with it set; T2E NPC template: cleared each frame after the transforms */
    /* 0x2C */ u16 xFrac;           /* position: 16.16 fixed point, x at 0x2C (s32), integer part at 0x2E */
    /* 0x2E */ s16 x;
    /* 0x30 */ u16 yFrac;
    /* 0x32 */ s16 y;
    /* 0x34 */ u16 zFrac;
    /* 0x36 */ s16 z;
    /* 0x38 */ void *sequence;      /* animation list (4-byte entries, f_AdvanceActorTimedFrameSequence) */
    /* 0x3C */ void *bank;  /* T2E: the actor's file (+0x3c file) */
    /* 0x40 */ s16 unk_40;
    /* 0x42 */ s16 unk_42;
    /* 0x44 */ s16 unk_44;
    /* 0x46 */ u8 animation;        /* f_SetActorAnimation */
    /* 0x47 */ u8 unk_47;
    /* 0x48 */ s16 unk_48;
    /* 0x4A */ s16 unk_4A;
    /* 0x4C */ s16 unk_4C;
    /* 0x4E */ s16 unk_4E;
    /* 0x50 */ s16 unk_50;
    /* 0x52 */ s16 unk_52;
    /* 0x54 */ s16 turn;
    /* 0x56 */ s16 unk_56;  /* T2E NPC template: yaw (0..0xFFF) */
    /* 0x58 */ s16 unk_58;
    /* 0x5A */ s16 unk_5A;
    /* 0x5C */ s16 spriteClut;      /* f_DrawActorSpriteParts: CLUT over every piece when non-zero */
    /* 0x5E */ u8 pickupBehaviour;
    /* 0x5F */ u8 unk_5F;
    /* 0x60 */ s16 chestContents;   /* also the quad corners of quad actors */
    /* 0x62 */ s16 chestEffect;
    /* 0x64 */ s16 effectFlags;
    /* 0x66 */ s16 unk_66;
    /* 0x68 */ s16 itemId;
    /* 0x6A */ s16 interiorId;
    /* 0x6C */ s16 unk_6C;
    /* 0x6E */ s16 unk_6E;
    /* 0x70 */ u8 unk_70;  /* T2E NPC template: script status, 255 = finished */
    /* 0x71 */ u8 unk_71;
    /* 0x72 */ s16 unk_72;
    /* 0x74 */ s16 unk_74;
    /* 0x76 */ s16 unk_76;
    /* 0x78 */ u8 unk_78;
    /* 0x79 */ u8 animationDone;    /* cleared by f_SetActorAnimation */
    /* 0x7A */ u8 unk_7A;
    /* 0x7B */ u8 unk_7B;
    /* 0x7C */ s16 unk_7C;          /* Tomba2Edit: skeleton (a pointer, the ANMP table) in some actors */
    /* 0x7E */ s16 unk_7E;
    /* 0x80 */ s16 unk_80;  /* T2E: talk box (0x80..0x86) */
    /* 0x82 */ s16 unk_82;
    /* 0x84 */ s16 unk_84;
    /* 0x86 */ s16 unk_86;
    /* 0x88 */ s16 unk_88;
    /* 0x8A */ s16 unk_8A;
    /* 0x8C */ s16 unk_8C;
    /* 0x8E */ s16 unk_8E;
    /* 0x90 */ s16 unk_90;
    /* 0x92 */ s16 unk_92;
    /* 0x94 */ s16 unk_94;
    /* 0x96 */ u8 pad96[0x16];
    /* 0xAC */ s32 unk_AC;
    /* 0xB0 */ s32 unk_B0;
    /* 0xB4 */ s32 unk_B4;
    /* 0xB8 */ s16 unk_B8;  /* T2E: model scale x/y/z (0xB8..0xBC, 4096 = 1.0) */
    /* 0xBA */ s16 unk_BA;
    /* 0xBC */ s16 unk_BC;
    /* 0xBE */ u8 unk_BE;
    /* 0xBF */ u8 unk_BF;
    /* 0xC0 */ u8 *parts[2];        /* the part pointers (more in some actors) */
} Actor; /* 0xC8 */

#endif

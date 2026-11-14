#ifndef ACTOR_H
#define ACTOR_H

#include "common.h"

/* The actor record (0xC0 bytes, followed by up to 64 part pointers), as far as it is known. Offsets and meanings
 * from Tomba2Edit's actor simulator (game/actor_sim.py, docs/TOMBA2EDIT.md) and the matched functions; field types
 * are only fixed where a matched function proves the access size. Unknown bytes stay padN.
 * Pools: f_InitializeActorPools builds five pools of 0x34, 0x3A, 0x2A, 0x28 and 5 records; f_AllocateActor
 * (USA 0x80072DDC) takes one. */
typedef struct Actor {
    /* 0x00 */ u8 pad0;
    /* 0x01 */ u8 active;
    /* 0x02 */ u8 kind;
    /* 0x03 */ u8 slot;
    /* 0x04 */ u8 lifecycle;        /* 3: being destroyed */
    /* 0x05 */ u8 pad5[3];
    /* 0x08 */ u8 partFrame;
    /* 0x09 */ u8 partCount;
    /* 0x0A */ u8 padA;
    /* 0x0B */ u8 renderKind;       /* also the render-mode mask */
    /* 0x0C */ u8 allocClass;       /* 6: transient effect */
    /* 0x0D */ u8 renderMode;
    /* 0x0E */ u8 pickupBit;
    /* 0x0F */ u8 padF;
    /* 0x10 */ struct Actor *linked;
    /* 0x14 */ u8 quadKind;
    /* 0x15 */ u8 pad15[7];
    /* 0x1C */ void (*callback)(struct Actor *);
    /* 0x20 */ u8 pad20[8];
    /* 0x28 */ s32 flags;
    /* 0x2C */ s32 position[3];
    /* 0x38 */ void *sequence;
    /* 0x3C */ void *bank;
    /* 0x40 */ u8 pad40[6];
    /* 0x46 */ u8 animation;        /* f_SetActorAnimation */
    /* 0x47 */ u8 pad47[0xD];
    /* 0x54 */ s16 turn;
    /* 0x56 */ u8 pad56[6];
    /* 0x5C */ u16 spriteClut;      /* f_DrawActorSpriteParts: CLUT over every piece when non-zero */
    /* 0x5E */ u8 pickupBehaviour;
    /* 0x5F */ u8 pad5F;
    /* 0x60 */ u16 chestContents;   /* also the quad corners of quad actors */
    /* 0x62 */ u16 chestEffect;
    /* 0x64 */ u16 effectFlags;
    /* 0x66 */ u8 pad66[2];
    /* 0x68 */ u16 itemId;
    /* 0x6A */ u16 interiorId;
    /* 0x6C */ u8 pad6C[0xD];
    /* 0x79 */ u8 animationDone;    /* cleared by f_SetActorAnimation */
    /* 0x7A */ u8 pad7A[2];
    /* 0x7C */ void *skeleton;      /* the ANMP table f_StartActorSkeletalAnimation steps */
    /* 0x80 */ u8 pad80[0x40];
} Actor; /* size 0xC0; the part pointers follow (Actor.parts at 0xC0) */

#endif

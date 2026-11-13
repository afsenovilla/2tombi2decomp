#ifndef GAME_H
#define GAME_H

#include "common.h"

/* The global game state at 0x800BF870 (USA). Fields are added as functions using them are matched. */
typedef struct GameState {
    /* 0x000 */ u8 unk0;
    /* 0x001 */ u8 pad1[0x543];
    /* 0x544 */ u8 appleBits[1]; /* collected-apple flags, one bit per apple (f_TestAppleCollectedBit) */
} GameState;

extern GameState D_800BF870;

#endif

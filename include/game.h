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

/* The cooperative worker (a second thread for disc reads and streaming), state at 0x801FE070 (USA): reached
 * through a constant pointer, not a symbol (lui/ori). f_OpenCooperativeWorkerThread / f_CloseCooperativeWorkerThread. */
typedef struct WorkerState {
    /* 0x00 */ u16 busy;
    /* 0x02 */ u8 pad2[0x6A];
    /* 0x6C */ u8 active;
} WorkerState;
#define WORKER_STATE ((WorkerState *)0x801FE070)

/* A pop-up message request: a count and up to 12 entries (0xFFFF = empty). f_ResetPopupRequest. */
typedef struct PopupRequest {
    /* 0x00 */ s32 count;
    /* 0x04 */ u16 entries[12];
} PopupRequest;

/* Scratchpad variables with names (config/undefined_syms.ld); every other scratchpad byte is D_1F8xxxxx
 * (config/scratchpad.ld), declared `extern s8 D_1F8xxxxx[]` by the drafts. */
extern volatile u8 g_DiscReadPending;   /* 0x1F80019B, cleared before a cooperative disc read */
extern s32 g_DiscReadSector;            /* 0x1F8001F0 */
extern s32 g_DiscReadWords;             /* 0x1F8001F4 */
extern void *g_DiscReadDest;            /* 0x1F8001F8 */

#endif

#ifndef GAME_H
#define GAME_H

#include "common.h"

/* The global game state at 0x800BF870 (USA). Fields are added as functions using them are matched. */
typedef struct GameState {
    /* 0x000 */ u8 unk0;            /* current area? (switches over it pick per-area code) */
    /* 0x001 */ u8 pad1[0x543];     /* +0x244: item counts (f_RemoveItemWithoutMessage) */
    /* 0x544 */ u8 appleBits[0x80]; /* collected-apple flags, one bit per apple (f_TestAppleCollectedBit) */
    /* 0x5C4 */ s32 flags5C4;       /* bit flags set by func_8006F02C */
    /* 0x5C8 */ u8 pad5C8[0x10];
    /* 0x5D8 */ s32 flags5D8;       /* bit flags set by func_8006F00C */
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

/* One displayed pop-up (0x8C bytes, f_ResetPopupDisplayEntry). */
typedef struct PopupDisplayEntry {
    /* 0x00 */ u8 pad0[0x10];
    /* 0x10 */ u8 unk10;
    /* 0x11 */ u8 pad11[0x2C];
    /* 0x3D */ u8 unk3D;
    /* 0x3E */ u8 pad3E[0x4E];
} PopupDisplayEntry;

/* The resource message bank (0x2BC bytes, cleared by func_8004FB20): text offsets and the text they index. */
typedef struct MessageBank {
    /* 0x000 */ u8 pad0[0x2B4];
    /* 0x2B4 */ u16 *offsets;
    /* 0x2B8 */ u8 *text;
} MessageBank;
extern MessageBank D_800BF548;

/* Camera state (0x90 bytes) at 0x800E8008, named g_CameraState (config/undefined_syms.ld; the drafts still call it
 * D_800E8008). f_SetCameraMode. */
typedef struct CameraState {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ u8 unk4;
    /* 0x05 */ u8 unk5;
    /* 0x06 */ s16 unk6;
    /* 0x08 */ u8 pad8[0x32];
    /* 0x3A */ u16 focusX;          /* f_SetCameraFocusPosition */
    /* 0x3C */ u8 pad3C[2];
    /* 0x3E */ u16 focusY;
    /* 0x40 */ u8 pad40[2];
    /* 0x42 */ u16 focusZ;
    /* 0x44 */ u8 pad44[0x20];
    /* 0x64 */ u8 mode;
    /* 0x65 */ u8 pad65;
    /* 0x66 */ u8 unk66;
    /* 0x67 */ u8 previousMode;
    /* 0x68 */ u8 pad68[4];
    /* 0x6C */ u16 unk6C;
    /* 0x6E */ u16 unk6E;
    /* 0x70 */ u16 unk70;
    /* 0x72 */ u8 pad72[0x1E];
} CameraState;
extern CameraState g_CameraState;

/* Scratchpad variables with names (config/undefined_syms.ld); every other scratchpad byte is D_1F8xxxxx
 * (config/scratchpad.ld), declared `extern s8 D_1F8xxxxx[]` by the drafts. */
extern volatile u8 g_DiscReadPending;   /* 0x1F80019B, cleared before a cooperative disc read */
extern s32 g_DiscReadSector;            /* 0x1F8001F0 */
extern s32 g_DiscReadWords;             /* 0x1F8001F4 */
extern void *g_DiscReadDest;            /* 0x1F8001F8 */

#endif

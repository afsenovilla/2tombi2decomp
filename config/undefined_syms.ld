/* Symbols outside the programs (hardware, scratchpad), shared by every link. */
/* Scratchpad variables with names (include/game.h); config/scratchpad.ld defines every other byte as D_1F8xxxxx. */
g_DiscReadPending = 0x1F80019B;
g_DiscReadSector = 0x1F8001F0;
g_DiscReadWords = 0x1F8001F4;
g_DiscReadDest = 0x1F8001F8;

/* Typed names for globals the drafts know as D_xxxxxxxx (include/game.h). */
g_CameraState = 0x800E8008;

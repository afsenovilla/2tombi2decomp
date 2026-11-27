/* The libsnd / libspu calls sound.c does not implement: the return values the game waits for (an SPU address, a
 * sequence id for SsSepOpen), so the boot does not spin on them. */
#include "port_runtime.h"

typedef unsigned int u32;
static int next_seq;
static u32 spu_alloc = 0x1010;

int SsSepOpen(void *addr, int vab, int n) { return next_seq++ & 31; }
void SsSepClose(int s) {}
int SpuMalloc(int size) { int a = (int)spu_alloc; spu_alloc += (u32)(size + 15) & ~15u; return a; }
int SpuInitMalloc(int n, void *tbl) { return n; }
void SpuFree(u32 a) {}
int SpuSetTransferMode(int m) { return m; }
int SpuSetReverb(int on) { return on; }
int SpuReserveReverbWorkArea(int on) { return on; }
int SpuClearReverbWorkArea(int mode) { return 1; }

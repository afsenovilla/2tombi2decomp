/* libsnd / libspu replacements for stage 1: silent, but with the return values the game waits for (a VAB id, a
 * finished transfer, an SPU address), so the boot does not spin on them.  The real sound shim (a software SPU,
 * Tombi-Decomp's port2/shims/sound.c) is stage 2 work (docs/PORT.md). */
#include "port_runtime.h"

typedef unsigned int u32;
static int next_vab, next_seq;
static u32 spu_alloc = 0x1010;

int SsVabOpenHead(void *addr, int vab) { int id = vab >= 0 ? vab : next_vab++ & 15; if (port_verbose) port_printf("[port] SsVabOpenHead -> %d\n", id); return id; }
int SsVabOpenHeadSticky(void *addr, int vab, u32 sbaddr) { return SsVabOpenHead(addr, vab); }
int SsVabFakeHead(void *addr, int vab, u32 sbaddr) { return SsVabOpenHead(addr, vab); }
int SsVabTransBody(void *addr, int vab) { return vab; }
int SsVabTransCompleted(int mode) { return 1; }
void SsVabClose(int vab) {}
int SsSeqOpen(void *addr, int vab) { return next_seq++ & 31; }
int SsSepOpen(void *addr, int vab, int n) { return next_seq++ & 31; }
void SsSeqClose(int s) {}
void SsSepClose(int s) {}
int SsIsEos(int a, int b) { return 0; }
int SpuIsTransferCompleted(int flag) { return 1; }
u32 SpuSetTransferStartAddr(u32 a) { return a; }
u32 SpuWrite0(u32 size) { return size; }
u32 SpuRead(void *p, u32 size) { return size; }
int SpuMalloc(int size) { int a = (int)spu_alloc; spu_alloc += (u32)(size + 15) & ~15u; return a; }
int SpuInitMalloc(int n, void *tbl) { return n; }
void SpuFree(u32 a) {}
int SpuSetTransferMode(int m) { return m; }
int SpuSetReverb(int on) { return on; }
int SpuReserveReverbWorkArea(int on) { return on; }
int SpuClearReverbWorkArea(int mode) { return 1; }
void SpuGetAllKeysStatus(char *s) { for (int i = 0; i < 24; i++) s[i] = 0; }

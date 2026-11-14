// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// ASPSX 2.79
// Source: psx_tomba src/psyq/libcd/sys.c (MIT), cut to this function by tools/ptsrc.py.
extern char D_8001C110[];
#define SKIP_ASM
#include "pt/common.h"
#include "psyq/libcd.h"
extern int D_80095F64[];
extern CdlCB CD_cbsync;
extern s32 CD_debug;
extern CdlCB CD_cbready;
extern u8 CD_status;
extern CdlLOC CD_pos;
extern const char* CD_comstr[];
extern const char* CD_intstr[];
extern u8 CD_com;
extern u8 CD_mode;
int CdStatus(void);
int CdMode(void);
int CdLastCom(void);
CdlLOC* CdLastPos(void);
int CdReset(int mode);
void CdFlush(void);
s32 CdSetDebug(s32 level);
char* CdComstr(u_char com)
{
    if (com >= 0x1c) {
        return D_8001C110;
    }
    return CD_comstr[com];
}
char* CdIntstr(u_char intr);
int CdSync(int mode, u_char* result);
int CdReady(int mode, u_char* result);
CdlCB CdSyncCallback(CdlCB func);
CdlCB CdReadyCallback(CdlCB func);
int loop(u_char com, u_char* param, u_char* result, int arg3);
int CdControl(u_char com, u_char* param, u_char* result);
int CdControlF(u_char com, u_char* param);
int CdControlB(u_char com, u_char* param, u_char* result);
int CdMix(CdlATV* vol);
int CdGetSector(void* madr, int size);
void(*CdDataCallback(void (*func)()));
int CdDataSync(int mode);
CdlLOC* CdIntToPos(int i, CdlLOC* p);
int CdPosToInt(CdlLOC* p);

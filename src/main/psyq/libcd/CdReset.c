// CC gcc-2.8.1-psx
// FLAGS -O2 -G0
// ASPSX 2.79
// Source: psx_tomba src/psyq/libcd/sys.c (MIT), cut to this function by tools/ptsrc.py.
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
int CdReset(int mode)
{
    if (mode == CdlModeAP) {
        CD_initintr();
        return 1;
    }
    if (CD_init()) {
        return 0;
    }
    if (mode == CdlModeDA && CD_initvol()) {
        return 0;
    }
    return 1;
}
void CdFlush(void);
s32 CdSetDebug(s32 level);
char* CdComstr(u_char com);
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

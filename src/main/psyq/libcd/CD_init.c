// CC gcc-2.8.1-nocse
// FLAGS -O2 -G0 -mno-split-addresses
// AS gnu
// EPILOGUE sony
// Source: psyz (github.com/Xeeynamo/psyz, MIT) decomp/src/libcd/bios.c, function CD_init.
#include "common.h"
extern char D_8001C35C[];
extern char D_8001C350[];
typedef unsigned char u_char;
typedef unsigned long u_long;
typedef void (*CdlCB)(u_char,u_char *);
typedef struct {
 u_char minute;
 u_char second;
 u_char sector;
 u_char track;
} CdlLOC;
typedef struct {
    s8 cd_intr;
    u8 D_800B53D1;
    u8 D_800B53D2;
} flush;
struct init {
    flush* unk0;
    s32* unk4;
    u8* unk8;
    u8* unkC;
    CdlLOC* unk10;
    u_long* unk14;
};
extern CdlCB CD_cbsync;
extern CdlCB CD_cbready;
extern int CD_status;
extern int CD_status1;
extern u_char D_800ABFD8;
extern u_char D_800ABFD9;
extern volatile s8* cd_reg0;
extern volatile u8* cd_reg2;
extern volatile u8* cd_reg3;
extern volatile s32* cd_com_delay;
extern volatile flush cd_intr;
extern struct init D_800AC29C;
extern void(*callback);

int CD_init(void) {
    puts(D_8001C350);
    printf(D_8001C35C, &D_800AC29C);
    D_800ABFD9 = 0;
    D_800ABFD8 = 0;
    CD_cbready = 0;
    CD_cbsync = 0;
    CD_status1 = 0;
    CD_status = 0;
    ResetCallback();
    InterruptCallback(2, &callback);
    *cd_reg0 = 1;
    while (*cd_reg3 & 7) {
        *cd_reg0 = 1;
        *cd_reg3 = 7;
        *cd_reg2 = 7;
    }
    {volatile flush *p = &cd_intr;
    p->D_800B53D2 = 0;
    p->D_800B53D1 = p->D_800B53D2;
    p->cd_intr = 2;}
    *cd_reg0 = 0;
    *cd_reg3 = 0;
    *cd_com_delay = 0x1325;
    CD_cw(0x01, 0, 0, 0);
    if (CD_status & 0x10) {
        CD_cw(0x01, 0, 0, 0);
    }
    if (CD_cw(10, 0, 0, 0)) {
        return -1;
    }
    if (CD_cw(0x0c, 0, 0, 0)) {
        return -1;
    }
    if (CD_sync(0, 0) != 2) {
        return -1;
    }
    return 0;
}

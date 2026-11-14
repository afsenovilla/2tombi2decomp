// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// AS gnu
// Source: psx_tomba src/psyq/libcd/bios.c (MIT), cut to this function by tools/ptsrc.py.
#define SKIP_ASM
#include "pt/common.h"
#include "psyq/libstamp.h"
#include "psyq/libcd.h"
typedef struct {
    unsigned char sync;
    unsigned char ready;
    unsigned char c;
} CdlIntr;
typedef struct Result_t {
    int unk0;
    int unk4;
} Result_t;
extern char cd_result_sync[];
extern char cd_result_ready[];
extern char cd_result_end[];
extern int cd_alarm;
extern int cd_alarm_count;
extern char* cd_alarm_func[];
extern const char cd_id[];
extern PsyqStamp libcd_stamp;
extern CdlCB (*CD_cbsync)(u_char, u_char*);
extern CdlCB (*CD_cbready)(u_char, u_char*);
extern int CD_cbread;
extern int CD_debug;
extern int CD_status;
extern int CD_status1;
extern int CD_nopen;
extern CdlLOC CD_pos;
extern u_char CD_mode;
extern u_char CD_com;
extern const char* CD_comstr[];
extern const char* CD_intstr[];
extern int cd_com_ack[];
extern int cd_com_ready[];
extern int cd_com_stat[];
extern int cd_com_nparam[];
extern volatile u_char* cd_reg0;
extern volatile u_char* cd_reg1;
extern volatile u_char* cd_reg2;
extern volatile u_char* cd_reg3;
extern volatile int* cd_com_delay;
extern void* cd_spu;
extern volatile CdlIntr cd_intr;
extern void* cd_info[];
extern s32* cd_delay;
extern s32* cd_dpcr;
extern s32* cd_d3_madr;
extern s32* cd_d3_bcr;
extern volatile s32* cd_d3_chcr;
void CD_flush(void);
void callback(void);
void rescpy(void* _dst, void* _src);
int get_alarm(void);
int getintr(void);
int CD_sync(int mode, unsigned char* result);
int CD_ready(int arg0, u_char* arg1);
int CD_cw(u_char arg0, u_char* arg1, u_char* arg2, int arg3);
int CD_vol(CdlATV* vol);
void CD_flush(void);
int CD_initvol(void) {
    CdlATV vol;
    
    if (*((volatile u16*)((u32)cd_spu + 0x1b8)) == 0 &&
    *((volatile u16*)((u32)cd_spu + 0x1ba)) == 0) {
        
        *((volatile u16*)((u32)cd_spu + 0x180)) = 0x3fff;
        *((volatile u16*)((u32)cd_spu + 0x182)) = 0x3fff;
    }
    
    *((volatile u16*)((u32)cd_spu + 0x1b0)) = 0x3fff;
    *((volatile u16*)((u32)cd_spu + 0x1b2)) = 0x3fff;
    
    *((volatile u16*)((u32)cd_spu + 0x1aa)) =
    (1 << 15) | (1 << 14) | (1 << 0);
    vol.val0 = vol.val2 = 0x80;
    vol.val1 = vol.val3 = 0;
    *cd_reg0 = 2;
    *cd_reg2 = vol.val0;
    *cd_reg3 = vol.val1;
    *cd_reg0 = 3;
    *cd_reg1 = vol.val2;
    *cd_reg2 = vol.val3;
    *cd_reg3 = 0x20;
    return 0;
}
void CD_initintr(void);
extern const char cd_id[];
int CD_init(void);
int CD_datasync(int arg0);
int CD_getsector(int arg0, int arg1);
void CD_set_test_parmnum(int arg0);
void callback(void);

// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// ASPSX 2.79
// Source: psx_tomba src/psyq/libpress/libpress.c (MIT), cut to this function by tools/ptsrc.py.
#define SKIP_ASM
#include "pt/common.h"
extern u32 mdec_iq[];
extern u32 mdec_coef[];
extern u_int volatile* d0_madr;
extern u_int volatile* d0_bcr;
extern u_int volatile* d0_chcr;
extern u_int volatile* d1_madr;
extern u_int volatile* d1_bcr;
extern u_int volatile* d1_chcr;
extern u_int volatile* d2_madr;
extern u_int volatile* d2_bcr;
extern u_int volatile* d2_chcr;
extern u_int volatile* d3_madr;
extern u_int volatile* d3_bcr;
extern u_int volatile* d3_chcr;
extern u_int volatile* mdec0;
extern volatile u_long* mdec1;
extern u_int volatile* d_pcr;
int timeout(char* arg0);
typedef struct {
    u_char iq_y[64];
    u_char iq_c[64];
    short dct[64];
} DECDCTENV;
extern u32 mdec_iq[];
extern u32 mdec_coef[];
void MDEC_in(u_long* buf, int size);
int ResetCallback(void);
void MDEC_reset(int mode);
extern int DecDCTinCallback(void (*func)());
extern int DecDCToutCallback(void (*func)());
int DecDCToutCallback(void (*cb)());
int MDEC_in_sync(void);
u_long MDEC_status(void);
void MDEC_out(u_long* buf, int size);
int DecDCTinCallback(void (*cb)());
int MDEC_out_sync(void);
void DecDCTReset(int mode);
DECDCTENV* DecDCTGetEnv(DECDCTENV* env);
DECDCTENV* DecDCTPutEnv(DECDCTENV* env);
int DecDCTBufSize(u_long* bs);
void DecDCTin(u_long* buf, int mode);
void DecDCTout(u_long* buf, int size);
int DecDCTinSync(int mode);
int DecDCToutSync(int mode) {
    int result;
    if (mode == 0)
        result = MDEC_out_sync();
    else
        result = (MDEC_status() >> 24) & 1;
    return result;
}
int DecDCTinCallback(void (*cb)());
int DecDCToutCallback(void (*cb)());
void MDEC_reset(int mode);
void MDEC_in(u_long* buf, int size);
void MDEC_out(u_long* buf, int size);
int MDEC_in_sync(void);
int MDEC_out_sync(void);
u_long MDEC_status(void);
void print_status(void);
int timeout(char* arg0);

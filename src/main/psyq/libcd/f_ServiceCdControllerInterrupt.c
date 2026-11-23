// CC gcc-2.8.1-psx
// FLAGS -O2 -G0 -mno-split-addresses
// AS gnu
// Source: psy-q-decomp (github.com/sozud/psy-q-decomp, MIT) src/cd/bios.c, function getintr (Intr written through a local pointer in two cases).
#include "common.h"
int puts(const char*);
typedef unsigned int size_t;
typedef char Result_t[8];
typedef struct {
    unsigned char sync;
    unsigned char ready;
    unsigned char c;
} CD_intr;
extern Result_t D_80102730[3];
extern int D_800ABFC4;
extern int CD_status;
extern int CD_status1;
extern int D_800ABFD0;
extern unsigned char D_800ABFD9;
extern char* CD_comstr[32];
extern int D_800AC080[4][32];
extern volatile u8* cd_reg0;
extern volatile u8* cd_reg1;
extern volatile u8* cd_reg2;
extern volatile u8* cd_reg3;
extern volatile CD_intr cd_intr;
static inline void _memcpy(void* _dst, void* _src, size_t _size) {
    char* pDst = (char*)_dst;
    char* pSrc = (char*)_src;
    if (pDst == (0)) {
        return;
    }
    while (_size--) {
        *pDst++ = *pSrc++;
    }
}
extern char D_8001C288[], D_8001C294[], D_8001C2B0[], D_8001C2C4[];

int f_ServiceCdControllerInterrupt(void) {
    volatile char nReg;
    volatile Result_t buf;
    int i, j;
    int bHasError;
    *cd_reg0 = 1;
    nReg = *cd_reg3 & 0x7;
    if (nReg == 0) {
        return 0;
    }
    bHasError = 0;
    while (nReg != (*cd_reg3 & 7)) {
        nReg = *cd_reg3 & 0x7;
    }
    for (i = 0; i < 8; i++) {
        if ((*cd_reg0 & 0x20) == 0) {
            break;
        }
        buf[i] = *cd_reg1;
    }
    for (j = i; j < 8; j++) {
        buf[j] = 0;
    }
    *cd_reg0 = 1;
    *cd_reg3 = 7;
    *cd_reg2 = 7;
    if (nReg != 3 || D_800AC080[2][D_800ABFD9]) {
        if (!(CD_status & 0x10) && (buf[0] & 0x10)) {
            D_800ABFD0++;
        }
        CD_status = buf[0];
        CD_status1 = buf[1];
        bHasError = CD_status;
        bHasError &= (0x01 | 0x04 | 0x08 |
                      0x10);
    }
    if (nReg == 5) {
        if (D_800ABFC4 > 0) {
            printf(D_8001C288);
        }
        if (D_800ABFC4 > 0) {
            printf(D_8001C294, CD_comstr[D_800ABFD9], CD_status,
                   CD_status1);
        }
    }
    switch (nReg) {
    case 3:
        if (bHasError) {
            cd_intr.sync = 0x05;
            _memcpy(&D_80102730[0], &buf, sizeof(Result_t));
            return 2;
        }
        if (D_800AC080[0][D_800ABFD9]) {
            cd_intr.sync = 0x03;
            _memcpy(&D_80102730[0], &buf, sizeof(Result_t));
            return 1;
        }
        cd_intr.sync = 0x02;
        _memcpy(&D_80102730[0], &buf, sizeof(Result_t));
        return 2;
    case 2:
        cd_intr.sync = bHasError ? 0x05 : 0x02;
        _memcpy(&D_80102730[0], &buf, sizeof(Result_t));
        return 2;
    case 1:
        if (bHasError && i == 1) {
            bHasError = 0;
        }
        { volatile CD_intr *p = &cd_intr; p->ready = bHasError ? 0x05 : 0x01; }
        _memcpy(&D_80102730[1], &buf, sizeof(Result_t));
        *cd_reg0 = 0;
        *cd_reg3 = 0;
        return 4;
    case 4:
        { volatile CD_intr *p = &cd_intr; p->ready = p->c = 0x04; }
        _memcpy(&D_80102730[2], &buf, sizeof(Result_t));
        _memcpy(&D_80102730[1], &buf, sizeof(Result_t));
        return 4;
    case 5:
        cd_intr.sync = cd_intr.ready = 0x05;
        _memcpy(&D_80102730[0], &buf, sizeof(Result_t));
        _memcpy(&D_80102730[1], &buf, sizeof(Result_t));
        return 6;
    default:
        puts(D_8001C2B0);
        printf(D_8001C2C4, nReg);
        return 0;
    }
}

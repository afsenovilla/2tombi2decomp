// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// AS gnu
// Source: psyz (github.com/Xeeynamo/psyz, MIT) decomp/src/libgpu/tmd.c, function get_tim_addr.
#include "common.h"
extern char D_8001037C[];
extern char D_80010370[];
extern char D_80010364[];
typedef unsigned char u_char;
typedef unsigned long u_long;
typedef struct {
 short x, y;
 short w, h;
} RECT;
typedef struct {
 u_long mode;
 RECT *crect;
 u_long *caddr;
 RECT *prect;
 u_long *paddr;
} TIM_IMAGE;
extern int GetGraphDebug(void) ;
extern int GetTimSize(u_char *sjis);

int func_80016168(unsigned int* timaddr, TIM_IMAGE* img) {
    unsigned int clut_len;
    unsigned int img_len;
    if (*(int*)timaddr++ != 0x10) {
        return -1;
    }
    img->mode = *timaddr++;
    if (GetGraphDebug() == 2) {
        printf(D_80010364, 0x10);
    }
    if (GetGraphDebug() == 2) {
        printf(D_80010370, img->mode);
    }
    if (GetGraphDebug() == 2) {
        printf(D_8001037C, timaddr);
    }
    if (img->mode & 8) {
        clut_len = *timaddr >> 2;
        img->crect = (RECT*)(timaddr + 1);
        img->caddr = (u_long*)(timaddr + 3);
        timaddr = &timaddr[clut_len];
    } else {
        img->crect = 0;
        img->caddr = 0;
        clut_len = 0;
    }
    img_len = *timaddr >> 2;
    img->prect = (RECT*)(timaddr + 1);
    img->paddr = (u_long*)(timaddr + 3);
    return (int)(2 + clut_len + img_len);
}

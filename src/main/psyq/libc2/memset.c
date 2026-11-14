// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// ASPSX 2.79
// Source: psx_tomba src/psyq/libc2/memset.c (MIT), cut to this function by tools/ptsrc.py.
#define SKIP_ASM
#include "pt/common.h"
void* memset(unsigned char* pMem, unsigned char val, int len) {
    unsigned char* pRet = 0;
    int remaining = len;
    if(pMem != 0){
        pRet = pMem;
        if (len <= 0){
            pRet = 0;
        }else{
            while(remaining > 0){
                *pMem = val;
                pMem++;
                remaining--;
            }
        }
    }
    return pRet;
}

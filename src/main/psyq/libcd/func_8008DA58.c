// CC gcc-2.8.1-psx
// FLAGS -O2 -G0 -mno-split-addresses
// AS gnu
// Source: psyz (github.com/Xeeynamo/psyz, MIT) decomp/src/libcd/c_011.c, function dma_execute.
#include "common.h"
extern char D_8001C5C0[];
typedef unsigned char u_char;
extern volatile u8 *D_800AC3A4;
extern volatile s32* D_800AC3BC;
extern volatile u8* D_800AC3C0;
typedef struct {
    s32 madr;
    s32 bcr;
    s32 chcr;
    s32 unk;
} DMA_CONTROL;

void func_8008DA58(s32 id, void* addr, u32 blocks, u32 size, u32 control,
                 u_char arg5, u32 arg6) {
    s32 i;
    s32 temp;
    s32 temp2;
    u8 v;
    volatile s32 ret;
    volatile s32* ptr;
    for (i = 0; *(volatile u32*)(0x1F801088 + (id << 4)) & 0x01000000; i++) {
        if (i == 0x10000) {
            printf(D_8001C5C0,
                   *(volatile u32*)(0x1F801088 + (id << 4)));
            break;
        }
    }
    if (arg5 == 1) {
        u8* q = (u8*)D_800AC3C0;
        v = q[2];
        v |= 1 << id;
        q[2] = v;
    } else {
        u8* q = (u8*)D_800AC3C0;
        v = q[2];
        v &= ~(1 << id);
        q[2] = v;
    }
    do {
        ret = *(volatile s32*)D_800AC3C0;
    } while (0);
    temp2 = id << 2;
    temp2 = temp2 + 3;
    temp = 1;
    temp = temp << temp2;
    ptr = &((volatile DMA_CONTROL*)0x1F801080)[id].madr;
    temp2 = *D_800AC3BC;
    temp2 |= temp;
    *D_800AC3BC = temp2;
    *ptr++ = (s32)addr;
    *ptr++ = (blocks << 16) | size;
    while (!(*D_800AC3A4 & 0x40)) {
    }
    *ptr = control;
    do {
        ret = *ptr;
    } while (0);
}

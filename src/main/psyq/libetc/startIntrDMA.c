// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// AS gnu
// Source: psx_tomba src/psyq/libetc/intr_dma.c (MIT), cut to this function by tools/ptsrc.py.
#define SKIP_ASM
#include "pt/common.h"
typedef void (*Callback)();
extern volatile unsigned long* dma_dicr;
extern Callback dma_callbacks[];
extern unsigned long* dma_madr;
Callback setIntrDMA(int index, Callback callback);
void trapIntrDMA(void);
void DMA_memclr(int* ptr, int size);
void* startIntrDMA(void)
{
    DMA_memclr(&dma_callbacks, 8);
    *dma_dicr = 0;
    InterruptCallback(3, &trapIntrDMA);
    return &setIntrDMA;
}
void trapIntrDMA(void);
Callback setIntrDMA(int index, Callback callback);
void DMA_memclr(int* ptr, int size);

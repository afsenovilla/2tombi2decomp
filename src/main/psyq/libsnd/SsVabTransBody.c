// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// AS gnu
// Source: psyz (github.com/Xeeynamo/psyz, MIT) decomp/src/libsnd/vs_vtb.c, function SsVabTransBody.
#include "common.h"
typedef unsigned char u_char;
typedef unsigned long u_long;
extern unsigned long SpuRead (unsigned char *addr, unsigned long size);
extern unsigned long SpuRead (unsigned char *addr, unsigned long size);
extern long SpuSetTransferMode (long mode);
extern unsigned long SpuSetTransferStartAddr (unsigned long addr);
extern void (* volatile _spu_transferCallback)();
extern void (* volatile _spu_IRQCallback)();
extern u8 _svm_vab_used[16];
extern unsigned D_80105D78[16];
extern s32 D_80105D30[16];
void _spu_setInTransfer(s32);

short SsVabTransBody(u_char* addr, short vabid) {
    unsigned vab_start;
    if (vabid >= 0 && vabid <= 16) {
        if (_svm_vab_used[vabid] == 2) {
            vab_start = D_80105D78[vabid];
            SpuSetTransferMode(0);
            if (SpuSetTransferStartAddr(vab_start) != 0) {
                SpuRead(addr, (u_long)D_80105D30[vabid]);
                _svm_vab_used[vabid] = 1;
                return vabid;
            }
        }
    }
    _spu_setInTransfer(0);
    return -1;
}

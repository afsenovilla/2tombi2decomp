#include "common.h"

void DecDCTReset(s32 arg0) {
    if (arg0 == 0) {
        ResetCallback();
    }
    func_8009C8E0(arg0);
}

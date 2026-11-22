// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// AS gnu
#include "common.h"
extern volatile u16 *D_800AC604;
extern s32 D_800AC590;
static inline s32 SpuRGetAllKeysStatus_i(s32 min, s32 max, s8 *status) {
    s32 voice;
    u16 volumex;

    if (min < 0) {
        min = 0;
    }
    if (min >= 24) {
        return -3;
    }
    if (max >= 24) {
        max = 23;
    }
    if (max < 0 || max < min) {
        return -3;
    }
    max++;
    for (voice = min; voice < max; voice++) {
        volumex = D_800AC604[(8 * voice) + 6];
        if (D_800AC590 & (u32)(1 << voice)) {
            if (volumex != 0) {
                status[voice] = 1;
            } else {
                status[voice] = 3;
            }
        } else {
            if (volumex != 0) {
                status[voice] = 2;
            } else {
                status[voice] = 0;
            }
        }
    }
    return 0;
}

void SpuGetAllKeysStatus(s8 *status) {
    SpuRGetAllKeysStatus_i(0, 24, status);
}

// CC gcc-2.8.1-psx
// FLAGS -O2 -G0 -mno-split-addresses
// ASPSX 2.79
#define SKIP_ASM
#include "pt/common.h"
#include "pt/libpad/padlocal.h"

int PadInfoAct(int channel, int index, int field) {
    padPort *obj;
    PadCapabilityRecord *entry;

    obj = _padFuncPort2Info(channel);
    if (index < 0) {
        return obj->actuatorCount;
    }
    if (index >= obj->actuatorCount) {
        return 0;
    }

    entry = &obj->capabilities[index];
    switch (field) {
    case 1:
        return entry->protocol[0];
    case 2:
        return entry->protocol[1];
    case 3:
        return entry->payloadBytes;
    case 4:
        return entry->activationCost;
    case 5:
        return entry->high_bit;
    default:
        return 0;
    }
}

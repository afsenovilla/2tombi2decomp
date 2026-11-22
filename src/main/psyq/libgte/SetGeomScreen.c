// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// ASPSX 2.79
#define SKIP_ASM
#include "pt/common.h"
#include "psyq/libgte.h"
#include "pt/libgte/gte_local.h"
#include "psyq/inline_c.h"

void SetGeomScreen(long h) {
    gte_SetGeomScreen(h);
}

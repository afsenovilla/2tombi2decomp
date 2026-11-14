// CC gcc-2.8.1-psx
// FLAGS -O2 -G0
// ASPSX 2.79
// Source: psx_tomba src/psyq/libgte/mtx_09.c (MIT), cut to this function by tools/ptsrc.py.
#define SKIP_ASM
#include "pt/common.h"
#include "psyq/libgte.h"
#include "pt/libgte/gte_local.h"
void SetRotMatrix(MATRIX* m) {
    gte_ldmatrix_t(m, 0, 1, 2, 3, 4);
}
void SetLightMatrix(MATRIX* m);
void SetColorMatrix(MATRIX* m);

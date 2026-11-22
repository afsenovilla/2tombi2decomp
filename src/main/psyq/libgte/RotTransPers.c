// CC gcc-2.8.1-psx
// FLAGS -O2 -G0 -mno-split-addresses -fno-delayed-branch
// AS gnu
#define SKIP_ASM
#include "pt/common.h"
#include "psyq/libgte.h"
#include "pt/libgte/gte_local.h"
#include "psyq/inline_c.h"
#undef gte_rtps_b
#define gte_rtps_b() __asm__ volatile("nop; .word 0x4A180001")

long RotTransPers(SVECTOR* v0, long* sxy, long* p, long* flag) {
    long f;
    long sz;

    gte_ldv0(v0);
    gte_rtps_b();
    gte_stsxy(sxy);
    gte_stdp(p);
    gte_read_flag(f);
    gte_read_sz3(sz);
    *flag = f;
    return sz >> 2;
}

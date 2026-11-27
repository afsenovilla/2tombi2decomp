/* Software GTE (COP2): the register file and the commands the game uses (RTPS, RTPT, NCLIP, AVSZ3, AVSZ4, NCCS,
 * NCCT, MVMVA for the library helpers).  The gte_* macros of the game sources are translated by
 * port/tools/gen_port.py into port_gte_mtc2/mfc2/ctc2/cfc2/op calls on this file.
 * Precision follows the documented hardware behaviour (psx-spx "GTE"), with the hardware UNR divide (since 2026-11-28;
 * it was an exact rounded division); checked against tools/psxemu/gte.py by tools/gte_diff.py. */
#include "port_runtime.h"
/* From Tombi-Decomp's port2/runtime/gte.c (MIT, same author); the depth-cue, GPF / GPL, SQR and OP commands were
   added for Tomba! 2. */

typedef int s32;
typedef unsigned int u32;
typedef short s16;
typedef unsigned short u16;
typedef long long s64;
typedef unsigned long long u64;

/* (not static: the 3DS build's game code reads and writes the registers in line, include/port_prelude.h) */
s32 port_gte_D[32];   /* data registers */
s32 port_gte_C[32];   /* control registers */
u32 port_gte_FLAG;
#define D port_gte_D
#define C port_gte_C
#define FLAG port_gte_FLAG

#define VX(n) ((s16)(D[(n) * 2] & 0xFFFF))
#define VY(n) ((s16)((u32)D[(n) * 2] >> 16))
#define VZ(n) ((s16)(D[(n) * 2 + 1] & 0xFFFF))
#define IR0 D[8]
#define IR1 D[9]
#define IR2 D[10]
#define IR3 D[11]
#define MAC0 D[24]
#define MAC1 D[25]
#define MAC2 D[26]
#define MAC3 D[27]
#define M16LO(r) ((s16)(C[r] & 0xFFFF))
#define M16HI(r) ((s16)((u32)C[r] >> 16))

/* the 3 x 3 matrix of 16-bit elements held by control registers base.. (0 rotation, 8 light, 16 light colour) */
static void mat(int base, s16 m[3][3]) {
    m[0][0] = M16LO(base);
    m[0][1] = M16HI(base);
    m[0][2] = M16LO(base + 1);
    m[1][0] = M16HI(base + 1);
    m[1][1] = M16LO(base + 2);
    m[1][2] = M16HI(base + 2);
    m[2][0] = M16LO(base + 3);
    m[2][1] = M16HI(base + 3);
    m[2][2] = M16LO(base + 4);
}

/* v saturated to lo..hi; FLAG gets the bit flag when v was out of range */
static s32 clampf(s64 v, s32 lo, s32 hi, u32 flag) {
    if (v < lo) {
        FLAG |= flag;
        return lo;
    }
    if (v > hi) {
        FLAG |= flag;
        return hi;
    }
    return (s32)v;
}
/* IR1..IR3 = MAC1..MAC3 saturated (lm: to 0..0x7FFF, else to -0x8000..0x7FFF) */
static void set_ir(int lm) {
    s32 lo = lm ? 0 : -0x8000;
    IR1 = clampf(MAC1, lo, 0x7FFF, 1u << 24);
    IR2 = clampf(MAC2, lo, 0x7FFF, 1u << 23);
    IR3 = clampf(MAC3, lo, 0x7FFF, 1u << 22);
}

/* --widescreen top-down rooms (runtime/ws_topdown.c): screen X added to RTPS / RTPT while the scene's objects are
   drawn, so the frame keeps inside the map picture at its edges; 0 otherwise (identity) */
int port_gte_dx;

static inline s32 clamp32(s32 v, s32 lo, s32 hi, u32 flag) {
    if (v < lo) {
        FLAG |= flag;
        return lo;
    }
    if (v > hi) {
        FLAG |= flag;
        return hi;
    }
    return v;
}
/* floor((a + b + c) / 4096) of three 32-bit products, in 32 bits (their sum does not fit) */
static inline s32 sum3_12(s32 a, s32 b, s32 c) {
    return (a >> 12) + (b >> 12) + (c >> 12) + (((a & 0xFFF) + (b & 0xFFF) + (c & 0xFFF)) >> 12);
}
/* (the rotation's products are 16 x 16 bits: 32-bit multiplies, and the translation, a multiple of 4096 once shifted,
   is added after the sum's own shift: the same values as the 64-bit sums, a third of the game's time on an Old 3DS) */
/* (in line: RTPT's three share the matrix and the screen registers they load) */
static inline __attribute__((always_inline)) void rtp(int n, int last) {
    s32 x = VX(n),
        y = VY(n),
        z = VZ(n);
    s64 m1 = (s64)C[5] + sum3_12(M16LO(0) * x, M16HI(0) * y, M16LO(1) * z);
    s64 m2 = (s64)C[6] + sum3_12(M16HI(1) * x, M16LO(2) * y, M16HI(2) * z);
    s64 m3 = (s64)C[7] + sum3_12(M16LO(3) * x, M16HI(3) * y, M16LO(4) * z);
    MAC1 = (s32)m1;
    MAC2 = (s32)m2;
    MAC3 = (s32)m3;
    IR1 = clamp32(MAC1, -0x8000, 0x7FFF, 1u << 24);
    IR2 = clamp32(MAC2, -0x8000, 0x7FFF, 1u << 23);
    IR3 = clamp32(MAC3, -0x8000, 0x7FFF, 1u << 22);
    /* SZ FIFO */
    D[16] = D[17];
    D[17] = D[18];
    D[18] = D[19];
    D[19] = clampf(m3, 0, 0xFFFF, 1u << 18);
    u32 h = (u16)C[26], sz = (u32)D[19];
    u32 q;
    if (h < sz * 2) {
        /* the hardware's UNR divide (psx-spx "GTE Division Inaccuracy"; tools/psxemu/gte.py _divide): a reciprocal
           from a 257-entry table and two Newton steps; it differs from the exact rounded quotient by a unit now and
           then (a screen y off by one in RotTransPers on 1 of 300 inputs before) */
        static unsigned char unr[0x101];
        if (!unr[0]) for (int i = 0; i < 0x101; i++) { int t = (0x40000 / (i + 0x100) + 1) / 2 - 0x101; unr[i] = t > 0 ? (unsigned char)t : 0; }
        int z = 0;
        while (z < 16 && !((sz << z) & 0x8000)) z++;
        u32 n = h << z, d = sz << z;
        u32 u = unr[(d - 0x7FC0) >> 7] + 0x101;
        d = (0x2000080u - d * u) >> 8;
        d = (0x0000080u + d * u) >> 8;
        u64 nq = ((u64)n * d + 0x8000) >> 16;
        q = nq > 0x1FFFF ? 0x1FFFF : (u32)nq;
    } else {
        q = 0x1FFFF;
        FLAG |= 1u << 17;
    }
    s64 sx = (((s64)C[24] + (s64)IR1 * q) >> 16) + port_gte_dx;
    s64 sy = ((s64)C[25] + (s64)IR2 * q) >> 16;
    D[12] = D[13];
    D[13] = D[14];
    s32 SX = clampf(sx, -0x400, 0x3FF, 1u << 14),
        SY = clampf(sy, -0x400, 0x3FF, 1u << 13);
    D[14] = (SX & 0xFFFF) | ((u32)SY << 16);
    D[15] = D[14];
    if (last) {
        s64 m0 = (s64)(s16)C[27] * q + C[28];
        MAC0 = (s32)m0;
        IR0 = clampf(m0 >> 12, 0, 0x1000, 1u << 12);
    }
}

/* (NCCS / NCCT and MVMVA in 32 bits, as rtp: every product is 16 x 16 bits, a sum of three is shifted by parts
   (sum3_12), and what was a 64-bit value cut to 32 bits is the same sum made modulo 2^32) */
static inline void set_ir0(void) {   /* set_ir(1) */
    IR1 = clamp32(MAC1, 0, 0x7FFF, 1u << 24);
    IR2 = clamp32(MAC2, 0, 0x7FFF, 1u << 23);
    IR3 = clamp32(MAC3, 0, 0x7FFF, 1u << 22);
}
static void ncc(int n) {
    s32 x = VX(n),
        y = VY(n),
        z = VZ(n);
    MAC1 = sum3_12(M16LO(8) * x, M16HI(8) * y, M16LO(9) * z);
    MAC2 = sum3_12(M16HI(9) * x, M16LO(10) * y, M16HI(10) * z);
    MAC3 = sum3_12(M16LO(11) * x, M16HI(11) * y, M16LO(12) * z);
    set_ir0();
    s32 a = IR1, b = IR2, d = IR3;   /* (0 .. 0x7FFF) */
    MAC1 = (s32)((u32)C[13] + (u32)sum3_12(M16LO(16) * a, M16HI(16) * b, M16LO(17) * d));
    MAC2 = (s32)((u32)C[14] + (u32)sum3_12(M16HI(17) * a, M16LO(18) * b, M16HI(18) * d));
    MAC3 = (s32)((u32)C[15] + (u32)sum3_12(M16LO(19) * a, M16HI(19) * b, M16LO(20) * d));
    set_ir0();
    u32 rgbc = (u32)D[6];
    MAC1 = (s32)((rgbc & 0xFF) * (u32)IR1) >> 8;            /* (colour x IR << 4 >> 12: under 2^23) */
    MAC2 = (s32)(((rgbc >> 8) & 0xFF) * (u32)IR2) >> 8;
    MAC3 = (s32)(((rgbc >> 16) & 0xFF) * (u32)IR3) >> 8;
    set_ir0();
    u32 R = clamp32(MAC1 >> 4, 0, 255, 1u << 21),
        G = clamp32(MAC2 >> 4, 0, 255, 1u << 20),
        B = clamp32(MAC3 >> 4, 0, 255, 1u << 19);
    D[20] = D[21];
    D[21] = D[22];
    D[22] = R | (G << 8) | (B << 16) | (rgbc & 0xFF000000u);
}

/* colour FIFO push from MAC1..3 >> 4 with the code byte of RGBC */
static void push_rgb(void) {
    u32 R = clamp32(MAC1 >> 4, 0, 255, 1u << 21), G = clamp32(MAC2 >> 4, 0, 255, 1u << 20),
        B = clamp32(MAC3 >> 4, 0, 255, 1u << 19);
    D[20] = D[21];
    D[21] = D[22];
    D[22] = R | (G << 8) | (B << 16) | ((u32)D[6] & 0xFF000000u);
}
/* depth cue of MAC1..3 (already the colour << 12 or a product): towards the far colour by IR0 */
static void dcue(int sf, int lm, s64 m1, s64 m2, s64 m3) {
    int sh = sf ? 12 : 0;
    s32 i1 = clampf(((s64)C[21] * 4096 - m1) >> sh, -0x8000, 0x7FFF, 1u << 24);
    s32 i2 = clampf(((s64)C[22] * 4096 - m2) >> sh, -0x8000, 0x7FFF, 1u << 23);
    s32 i3 = clampf(((s64)C[23] * 4096 - m3) >> sh, -0x8000, 0x7FFF, 1u << 22);
    MAC1 = (s32)((m1 + (s64)i1 * (s16)IR0) >> sh);
    MAC2 = (s32)((m2 + (s64)i2 * (s16)IR0) >> sh);
    MAC3 = (s32)((m3 + (s64)i3 * (s16)IR0) >> sh);
    set_ir(lm);
    push_rgb();
}
/* Added for Tomba! 2 (from the psx-spx GTE description): DPCS / DPCT / INTPL / DCPL, GPF / GPL, SQR, OP */
/* NCS / NCT / NCDS / NCDT / CC / CDP (tools/psxemu/gte.py _ncd / _color_mul, 64-bit sums): unused on the routes
   checked so far (gte_more logged none), added so that no area meets a missing command */
static void set_mac3(s64 a, s64 b, s64 c, int sh, int lm) {
    MAC1 = (s32)(a >> sh); MAC2 = (s32)(b >> sh); MAC3 = (s32)(c >> sh);
    set_ir(lm);
}
static void back_light(int sh, int lm) {             /* BK << 12 + LCM x IR */
    s64 i1 = (s16)IR1, i2 = (s16)IR2, i3 = (s16)IR3;
    set_mac3(((s64)C[13] << 12) + M16LO(16) * i1 + M16HI(16) * i2 + M16LO(17) * i3,
             ((s64)C[14] << 12) + M16HI(17) * i1 + M16LO(18) * i2 + M16HI(18) * i3,
             ((s64)C[15] << 12) + M16LO(19) * i1 + M16HI(19) * i2 + M16LO(20) * i3, sh, lm);
}
static void color_mul(int sh, int lm, int depth) {   /* RGBC x IR << 4, optionally depth-cued towards FC by IR0 */
    u32 c = (u32)D[6];
    s64 p1 = ((s64)(c & 0xFF) * (s16)IR1) << 4, p2 = ((s64)((c >> 8) & 0xFF) * (s16)IR2) << 4,
        p3 = ((s64)((c >> 16) & 0xFF) * (s16)IR3) << 4;
    if (depth) {
        s32 t1 = clampf((((s64)C[21] << 12) - p1) >> sh, -0x8000, 0x7FFF, 1u << 24);
        s32 t2 = clampf((((s64)C[22] << 12) - p2) >> sh, -0x8000, 0x7FFF, 1u << 23);
        s32 t3 = clampf((((s64)C[23] << 12) - p3) >> sh, -0x8000, 0x7FFF, 1u << 22);
        s64 i0 = (s16)IR0;
        p1 += i0 * t1; p2 += i0 * t2; p3 += i0 * t3;
    }
    set_mac3(p1, p2, p3, sh, lm);
}
static void ncd(int n, int sh, int lm, int mode) {    /* mode 0 NCS, 1 NCC, 2 NCD */
    s64 x = VX(n), y = VY(n), z = VZ(n);
    set_mac3(M16LO(8) * x + M16HI(8) * y + M16LO(9) * z, M16HI(9) * x + M16LO(10) * y + M16HI(10) * z,
             M16LO(11) * x + M16HI(11) * y + M16LO(12) * z, sh, lm);
    back_light(sh, lm);
    if (mode) color_mul(sh, lm, mode == 2);
    push_rgb();
}
static void gte_more(u32 op) {
    int sf = (op >> 19) & 1, lm = (op >> 10) & 1, sh = sf ? 12 : 0;
    switch (op & 0x3F) {
    case 0x10: {                                                     /* DPCS: RGBC */
        u32 c = (u32)D[6];
        dcue(sf, lm, (s64)(c & 0xFF) << 16, (s64)((c >> 8) & 0xFF) << 16, (s64)((c >> 16) & 0xFF) << 16);
        break;
    }
    case 0x2A:                                                       /* DPCT: the three colours of the FIFO */
        for (int i = 0; i < 3; i++) {
            u32 c = (u32)D[20];
            dcue(sf, lm, (s64)(c & 0xFF) << 16, (s64)((c >> 8) & 0xFF) << 16, (s64)((c >> 16) & 0xFF) << 16);
        }
        break;
    case 0x11:                                                       /* INTPL: IR1..3 */
        dcue(sf, lm, (s64)(s16)IR1 << 12, (s64)(s16)IR2 << 12, (s64)(s16)IR3 << 12);
        break;
    case 0x29: {                                                     /* DCPL: RGBC x IR */
        u32 c = (u32)D[6];
        dcue(sf, lm, (s64)(c & 0xFF) * (s16)IR1 << 4, (s64)((c >> 8) & 0xFF) * (s16)IR2 << 4,
             (s64)((c >> 16) & 0xFF) * (s16)IR3 << 4);
        break;
    }
    case 0x3D:                                                       /* GPF: IR x IR0 */
        MAC1 = (s32)(((s64)(s16)IR1 * (s16)IR0) >> sh);
        MAC2 = (s32)(((s64)(s16)IR2 * (s16)IR0) >> sh);
        MAC3 = (s32)(((s64)(s16)IR3 * (s16)IR0) >> sh);
        set_ir(lm);
        push_rgb();
        break;
    case 0x3E:                                                       /* GPL: MAC + IR x IR0 */
        MAC1 = (s32)((((s64)MAC1 << sh) + (s64)(s16)IR1 * (s16)IR0) >> sh);
        MAC2 = (s32)((((s64)MAC2 << sh) + (s64)(s16)IR2 * (s16)IR0) >> sh);
        MAC3 = (s32)((((s64)MAC3 << sh) + (s64)(s16)IR3 * (s16)IR0) >> sh);
        set_ir(lm);
        push_rgb();
        break;
    case 0x28:                                                       /* SQR */
        MAC1 = (s32)(((s64)(s16)IR1 * (s16)IR1) >> sh);
        MAC2 = (s32)(((s64)(s16)IR2 * (s16)IR2) >> sh);
        MAC3 = (s32)(((s64)(s16)IR3 * (s16)IR3) >> sh);
        set_ir(lm);
        break;
    case 0x1E: ncd(0, sh, lm, 0); break;                             /* NCS */
    case 0x20: for (int i = 0; i < 3; i++) ncd(i, sh, lm, 0); break; /* NCT */
    case 0x13: ncd(0, sh, lm, 2); break;                             /* NCDS */
    case 0x16: for (int i = 0; i < 3; i++) ncd(i, sh, lm, 2); break; /* NCDT */
    case 0x1C: case 0x14:                                            /* CC / CDP */
        back_light(sh, lm);
        color_mul(sh, lm, (op & 0x3F) == 0x14);
        push_rgb();
        break;
    case 0x0C: {                                                     /* OP: cross product with the matrix diagonal */
        s32 d1 = M16LO(0), d2 = M16LO(2), d3 = M16LO(4);
        s32 i1 = (s16)IR1, i2 = (s16)IR2, i3 = (s16)IR3;
        MAC1 = (s32)(((s64)i3 * d2 - (s64)i2 * d3) >> sh);
        MAC2 = (s32)(((s64)i1 * d3 - (s64)i3 * d1) >> sh);
        MAC3 = (s32)(((s64)i2 * d1 - (s64)i1 * d2) >> sh);
        set_ir(lm);
        break;
    }
    default: {
        static int warned;
        if (warned++ < 20) port_printf("[port] GTE op %08x not implemented\n", op);
    }
    }
}

static void mvmva(u32 op) {
    int sf = (op >> 19) & 1,
        mx = (op >> 17) & 3,
        v = (op >> 15) & 3,
        cv = (op >> 13) & 3,
        lm = (op >> 10) & 1;
    s16 m[3][3];
    mat(mx == 0 ? 0 : mx == 1 ? 8 : 16, m);
    s32 x, y, z;
    if (v == 3) {
        x = (s16)IR1;
        y = (s16)IR2;
        z = (s16)IR3;
    } else {
        x = VX(v);
        y = VY(v);
        z = VZ(v);
    }
    u32 t1 = 0, t2 = 0, t3 = 0;
    if (cv == 0) {
        t1 = (u32)C[5];
        t2 = (u32)C[6];
        t3 = (u32)C[7];
    } else if (cv == 1) {
        t1 = (u32)C[13];
        t2 = (u32)C[14];
        t3 = (u32)C[15];
    } else if (cv == 2) {
        t1 = (u32)C[21];
        t2 = (u32)C[22];
        t3 = (u32)C[23];
    }
    if (sf) {
        MAC1 = (s32)(t1 + (u32)sum3_12(m[0][0] * x, m[0][1] * y, m[0][2] * z));
        MAC2 = (s32)(t2 + (u32)sum3_12(m[1][0] * x, m[1][1] * y, m[1][2] * z));
        MAC3 = (s32)(t3 + (u32)sum3_12(m[2][0] * x, m[2][1] * y, m[2][2] * z));
    } else {
        MAC1 = (s32)((t1 << 12) + (u32)(m[0][0] * x) + (u32)(m[0][1] * y) + (u32)(m[0][2] * z));
        MAC2 = (s32)((t2 << 12) + (u32)(m[1][0] * x) + (u32)(m[1][1] * y) + (u32)(m[1][2] * z));
        MAC3 = (s32)((t3 << 12) + (u32)(m[2][0] * x) + (u32)(m[2][1] * y) + (u32)(m[2][2] * z));
    }
    set_ir(lm);
}

void port_gte_op(unsigned long op) {
    FLAG = 0;
    switch (op & 0x3F) {
    case 0x01: /* RTPS */
        rtp(0, 1);
        break;
    case 0x30: /* RTPT */
        rtp(0, 0);
        rtp(1, 0);
        rtp(2, 1);
        break;
    case 0x06: {                                                     /* NCLIP */
        /* (modulo 2^32, what the 64-bit sum cut to 32 bits was) */
        s32 x0 = (s16)D[12],
            y0 = (s16)(D[12] >> 16),
            x1 = (s16)D[13],
            y1 = (s16)(D[13] >> 16);
        s32 x2 = (s16)D[14], y2 = (s16)(D[14] >> 16);
        MAC0 = (s32)((u32)(x0 * y1) + (u32)(x1 * y2) + (u32)(x2 * y0) - (u32)(x0 * y2) - (u32)(x1 * y0) -
                     (u32)(x2 * y1));
        break;
    }
    case 0x2D: {                                                     /* AVSZ3 */
        s64 m = (s64)(s16)C[29] * ((u16)D[17] + (u16)D[18] + (u16)D[19]);
        MAC0 = (s32)m;
        D[7] = clampf(m >> 12, 0, 0xFFFF, 1u << 18);
        break;
    }
    case 0x2E: {                                                     /* AVSZ4 */
        s64 m = (s64)(s16)C[30] * ((u16)D[16] + (u16)D[17] + (u16)D[18] + (u16)D[19]);
        MAC0 = (s32)m;
        D[7] = clampf(m >> 12, 0, 0xFFFF, 1u << 18);
        break;
    }
    case 0x1B: /* NCCS */
        ncc(0);
        break;
    case 0x3F: /* NCCT */
        ncc(0);
        ncc(1);
        ncc(2);
        break;
    case 0x12: /* MVMVA */
        mvmva((u32)op);
        break;
    default: gte_more((u32)op);
    }
    if (FLAG & 0x7F87E000u) FLAG |= 0x80000000u;
}

void port_gte_mtc2(int r, unsigned long v) {
    switch (r) {
    case 15: /* SXYP pushes */
        D[12] = D[13];
        D[13] = D[14];
        D[14] = (s32)v;
        D[15] = (s32)v;
        break;
    case 7: case 16: case 17: case 18: case 19:
        D[r] = (s32)(v & 0xFFFF);
        break;
    case 8: case 9: case 10: case 11:
        D[r] = (s16)v;
        break;
    case 28:
        D[28] = (s32)(v & 0x7FFF);
        IR1 = (v & 0x1F) << 7;
        IR2 = ((v >> 5) & 0x1F) << 7;
        IR3 = ((v >> 10) & 0x1F) << 7;
        break;
    case 30: {
        D[30] = (s32)v;
        s32 x = (s32)v;
        u32 u = x < 0 ? ~(u32)x : (u32)x;
        int n = 0;
        while (n < 32 && !(u & 0x80000000u)) {
            u <<= 1;
            n++;
        }
        D[31] = n;
        break;
    }
    case 29: case 31: break;
    default: D[r] = (s32)v;
    }
}

unsigned long port_gte_mfc2(int r) {
    switch (r) {
    case 1: case 3: case 5: case 8: case 9: case 10: case 11: return (unsigned long)(s32)(s16)D[r];
    case 7: case 16: case 17: case 18: case 19: return (u16)D[r];
    case 15: return (u32)D[14];
    case 28: case 29: {
        s32 r5 = IR1 >> 7,
            g5 = IR2 >> 7,
            b5 = IR3 >> 7;
        r5 = r5 < 0 ? 0 : r5 > 31 ? 31 : r5;
        g5 = g5 < 0 ? 0 : g5 > 31 ? 31 : g5;
        b5 = b5 < 0 ? 0 : b5 > 31 ? 31 : b5;
        return (u32)(r5 | (g5 << 5) | (b5 << 10));
    }
    default: return (u32)D[r];
    }
}

void port_gte_ctc2(int r, unsigned long v) {
    if (r == 31) {
        FLAG = v & 0x7FFFF000u;
        if (FLAG & 0x7F87E000u) FLAG |= 0x80000000u;
        return;
    }
    if (r == 4 || r == 12 || r == 20 || r == 26 || r == 27 || r == 29 || r == 30) v = (unsigned long)(s32)(s16)v;
    if (r == 26) v &= 0xFFFF;
    C[r] = (s32)v;
}

unsigned long port_gte_cfc2(int r) { return r == 31 ? FLAG : (u32)C[r]; }

void port_gte_unsupported(const char *ins) { port_fatal("GTE macro instruction not translated: %s", ins); }

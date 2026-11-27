#!/usr/bin/env python3
"""The port's software GTE (port/runtime/gte.c) against the reference emulator's (tools/psxemu/gte.py) on random
register states, command by command.

    python3 -I tools/gte_diff.py [--n 3000] [--seed 1] [--ops RTPS,RTPT,...] [--raw]

gte.c is compiled with a small driver as a 32-bit host program (build/gte_diff/drv, gcc -m32); each test sets the
same registers in both (mtc2 / ctc2 in an order without side effects), runs one command and compares every data and
control register as mfc2 / cfc2 read them (FLAG included).  States are "realistic" (vectors, matrices, offsets and
screen distance in the ranges the game uses) unless --raw (every register random).  Prints, per command, how many
tests differ and the first example with the differing registers.
"""
import argparse
import os
import random
import struct
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))
from psxemu.gte import GTE  # noqa: E402

DRIVER = r"""
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
void port_printf(const char *f, ...) { (void)f; }
void port_fatal(const char *f, ...) { (void)f; exit(2); }
void port_gte_op(unsigned long op);
void port_gte_mtc2(int r, unsigned long v);
unsigned long port_gte_mfc2(int r);
void port_gte_ctc2(int r, unsigned long v);
unsigned long port_gte_cfc2(int r);
static const int order[] = { 28, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 16, 17, 18, 19, 20, 21, 22, 23, 24,
                             25, 26, 27, 30 };
int main(void) {
    unsigned in[64], out[64];
    while (fread(in, 4, 64, stdin) == 64) {
        for (unsigned i = 0; i < sizeof order / sizeof order[0]; i++) port_gte_mtc2(order[i], in[1 + order[i]]);
        for (int r = 0; r < 31; r++) port_gte_ctc2(r, in[33 + r]);
        port_gte_ctc2(31, 0);
        port_gte_op(in[0]);
        for (int r = 0; r < 32; r++) out[r] = (unsigned)port_gte_mfc2(r);
        for (int r = 0; r < 32; r++) out[32 + r] = (unsigned)port_gte_cfc2(r);
        fwrite(out, 4, 64, stdout);
    }
    return 0;
}
"""
ORDER = [28, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 30]


def op(code, sf=1, lm=0, mx=0, v=0, cv=0):
    return (0x4A << 24 & 0) | (sf << 19) | (mx << 17) | (v << 15) | (cv << 13) | (lm << 10) | code


OPS = {
    "RTPS": [op(0x01)], "RTPT": [op(0x30)], "NCLIP": [op(0x06)], "AVSZ3": [op(0x2D)], "AVSZ4": [op(0x2E)],
    "NCCS": [op(0x1B, lm=1)], "NCCT": [op(0x3F, lm=1)], "NCDS": [op(0x13, lm=1)], "NCDT": [op(0x16, lm=1)],
    "NCS": [op(0x1E, lm=1)], "NCT": [op(0x20, lm=1)], "CC": [op(0x1C, lm=1)], "CDP": [op(0x14, lm=1)],
    "DPCS": [op(0x10)], "DPCT": [op(0x2A)], "DCPL": [op(0x29)], "INTPL": [op(0x11)],
    "SQR": [op(0x28), op(0x28, sf=0)], "OP": [op(0x0C), op(0x0C, sf=0)], "GPF": [op(0x3D), op(0x3D, sf=0)],
    "GPL": [op(0x3E), op(0x3E, sf=0)],
    "MVMVA": [op(0x12, sf=sf, lm=lm, mx=mx, v=v, cv=cv) for sf in (0, 1) for lm in (0, 1) for mx in (0, 1, 2)
              for v in (0, 1, 2, 3) for cv in (0, 1, 3)],
}
REG_NAMES = (["VXY0", "VZ0", "VXY1", "VZ1", "VXY2", "VZ2", "RGBC", "OTZ", "IR0", "IR1", "IR2", "IR3", "SXY0", "SXY1",
              "SXY2", "SXYP", "SZ0", "SZ1", "SZ2", "SZ3", "RGB0", "RGB1", "RGB2", "RES1", "MAC0", "MAC1", "MAC2",
              "MAC3", "IRGB", "ORGB", "LZCS", "LZCR"] +
             ["RT11", "RT13", "RT22", "RT31", "RT33", "TRX", "TRY", "TRZ", "L11", "L13", "L22", "L31", "L33", "RBK",
              "GBK", "BBK", "LR1", "LR3", "LG2", "LB1", "LB3", "RFC", "GFC", "BFC", "OFX", "OFY", "H", "DQA", "DQB",
              "ZSF3", "ZSF4", "FLAG"])


def pk(a, b):
    return (a & 0xFFFF) | (b & 0xFFFF) << 16


WIDE = [False]


def state(rng, raw):
    if raw:
        return [rng.getrandbits(32) for _ in range(32)], [rng.getrandbits(32) for _ in range(31)]
    w = WIDE[0]
    s16 = lambda lim: rng.randint(-0x8000, 0x7FFF) if w and rng.random() < 0.5 else rng.randint(-lim, lim)  # noqa: E731
    d = [0] * 32
    for n in range(3):
        d[n * 2] = pk(s16(3000), s16(3000))
        d[n * 2 + 1] = s16(3000) & 0xFFFF
    d[6] = rng.getrandbits(32)
    d[7] = rng.getrandbits(16)
    d[8] = rng.randint(0, 0x1000)
    for i in (9, 10, 11):
        d[i] = s16(0x7FFF) & 0xFFFF
    for i in (12, 13, 14):
        d[i] = pk(s16(400), s16(300))
    for i in (16, 17, 18, 19):
        d[i] = rng.randint(0, 0xFFFF)
    for i in (20, 21, 22):
        d[i] = rng.getrandbits(32)
    for i in (24, 25, 26, 27):
        d[i] = rng.getrandbits(32) if rng.random() < 0.5 else s16(100000) & 0xFFFFFFFF
    d[28] = rng.getrandbits(15)
    d[30] = rng.getrandbits(32)
    c = [0] * 31
    for base in (0, 8, 16):
        for k in range(4):
            c[base + k] = pk(s16(4096), s16(4096))
        c[base + 4] = s16(4096) & 0xFFFF
    for i in (5, 6, 7):
        c[i] = s16(20000) & 0xFFFFFFFF
    c[7] = rng.randint(-2000, 30000) & 0xFFFFFFFF
    if w:
        for i in (5, 6, 7):
            c[i] = rng.randint(-0x800000, 0x800000) & 0xFFFFFFFF if rng.random() < 0.5 else c[i]
    for i in (13, 14, 15, 21, 22, 23):
        c[i] = rng.randint(0, 0xFF0) & 0xFFFFFFFF
    c[24] = (rng.randint(100, 220) << 16) & 0xFFFFFFFF
    c[25] = (rng.randint(80, 160) << 16) & 0xFFFFFFFF
    c[26] = rng.randint(100, 1200)
    c[27] = s16(0x2000) & 0xFFFF
    c[28] = rng.randint(0, 0x2000000)
    c[29] = rng.randint(0, 0x300)
    c[30] = rng.randint(0, 0x300)
    return d, c


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--n", type=int, default=3000)
    ap.add_argument("--seed", type=int, default=1)
    ap.add_argument("--ops", default="")
    ap.add_argument("--raw", action="store_true")
    ap.add_argument("--wide", action="store_true", help="realistic layout, full 16-bit vectors / matrices, large translations")
    a = ap.parse_args()
    WIDE[0] = a.wide
    out_dir = os.path.join(ROOT, "build", "gte_diff")
    os.makedirs(out_dir, exist_ok=True)
    drv_c, drv = os.path.join(out_dir, "drv.c"), os.path.join(out_dir, "drv")
    open(drv_c, "w").write(DRIVER)
    subprocess.check_call(["gcc", "-m32", "-O1", "-w", "-I", os.path.join(ROOT, "port", "include"), "-o", drv, drv_c,
                           os.path.join(ROOT, "port", "runtime", "gte.c")])
    rng = random.Random(a.seed)
    names = [x for x in (a.ops.split(",") if a.ops else OPS)]
    tests = []
    for _ in range(a.n):
        name = rng.choice(names)
        cmd = rng.choice(OPS[name])
        d, c = state(rng, a.raw)
        tests.append((name, cmd, d, c))
    blob = b"".join(struct.pack("<64I", cmd, *d, *c) for _, cmd, d, c in tests)
    res = subprocess.run([drv], input=blob, stdout=subprocess.PIPE, check=True).stdout
    stats = {}
    for k, (name, cmd, d, c) in enumerate(tests):
        g = GTE()
        for r in ORDER:
            g.write_data(r, d[r])
        for r in range(31):
            g.write_ctrl(r, c[r])
        g.write_ctrl(31, 0)
        g.command(cmd)
        ref = [g.read_data(r) & 0xFFFFFFFF for r in range(32)] + [g.read_ctrl(r) & 0xFFFFFFFF for r in range(32)]
        port = list(struct.unpack_from("<64I", res, k * 256))
        diff = [i for i in range(64) if ref[i] != port[i]]
        st = stats.setdefault(name, [0, 0, None])
        st[0] += 1
        if diff:
            st[1] += 1
            if st[2] is None:
                st[2] = (cmd, ", ".join("%s emu %08x port %08x" % (REG_NAMES[i], ref[i], port[i]) for i in diff))
    bad = 0
    for name in sorted(stats):
        n, nd, ex = stats[name]
        print("%-6s %5d tests, %5d differ%s" % (name, n, nd, "" if not ex else "  e.g. cmd %08x: %s" % ex))
        bad += nd
    return 1 if bad else 0


if __name__ == "__main__":
    sys.exit(main())

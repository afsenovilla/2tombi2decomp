#!/usr/bin/env python3
"""The port's libgte / math shims (port/shims/psyq.c on port/runtime/gte.c) against the retail functions run in the
reference emulator, on random inputs (docs/EMU.md).  Builds the two files as a host shared library in build/emu_shim/
(undefined port symbols stubbed) and calls them through ctypes; the retail side is MAIN.EXE's own code in tools/psxemu.

  python3 -I tools/emu_shimcheck.py [--n 300] [--seed 2]

Prints, per function, how many inputs give another result, with one example.  2026-11-28: ratan2 (1 in 2 inputs off by
one), SquareRoot0 (exact in the port, Sony's table approximation in retail), RotMatrix (296 / 300 off by 1-2 in some
elements), RotTransPers (1 / 300: one screen y off by one); rsin, rcos, RotMatrixX/Y/Z, MulMatrix0, ApplyMatrix,
ApplyMatrixSV equal.
"""
import argparse
import ctypes
import os
import random
import struct
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))
from psxemu import machine as M, cpu as C  # noqa: E402


def build():
    out = os.path.join(ROOT, "build", "emu_shim")
    os.makedirs(out, exist_ok=True)
    so, srcs = os.path.join(out, "libshim.so"), [os.path.join(ROOT, "port", "shims", "psyq.c"), os.path.join(ROOT, "port", "runtime", "gte.c")]
    inc = ["-I" + os.path.join(ROOT, "port", d) for d in ("include", "runtime", "shims")]
    subprocess.run(["gcc", "-shared", "-fPIC", "-w", "-O1", "-o", so] + inc + srcs, check=True)
    und = subprocess.run(["nm", "-u", so], capture_output=True, text=True, check=True).stdout.split()
    stubs = os.path.join(out, "stubs.c")
    with open(stubs, "w") as f:
        f.write("".join("char %s[64];\n" % n for n in und if n not in ("U", "w", "v") and not n.startswith("_") and "@" not in n))
    subprocess.run(["gcc", "-shared", "-fPIC", "-w", "-O1", "-o", so] + inc + srcs + [stubs], check=True)
    return so


ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
ap.add_argument("--n", type=int, default=300)
ap.add_argument("--seed", type=int, default=2)
args = ap.parse_args()
lib = ctypes.CDLL(build())
def has(n):
    try:
        getattr(lib, n); return True
    except AttributeError:
        return False
# (2026-11-28 (2): the port dropped the ratan2 / SquareRoot0 / RotMatrix / RotTransPers shims: the retail code runs.
#  RotTransPers is still checked, as the port's GTE commands it would run: port/runtime/gte.c's RTPS)
if not has("RotTransPers"):
    for n in ("port_gte_mfc2", "port_gte_cfc2"): getattr(lib, n).restype = ctypes.c_uint32
    def _rtp(v, sxy, p, flag):
        b = v.raw; vx, vy, vz = struct.unpack_from("<3h", b)
        lib.port_gte_mtc2(0, (vx & 0xFFFF) | (vy & 0xFFFF) << 16); lib.port_gte_mtc2(1, vz & 0xFFFF)
        lib.port_gte_op(0x00180001)
        struct.pack_into("<I", sxy, 0, lib.port_gte_mfc2(14))
        return C.s32(lib.port_gte_mfc2(19)) >> 2, lib.port_gte_mfc2(14), C.s32(lib.port_gte_mfc2(8))
    lib_rtp = _rtp
skipped = [n for n in ("RotMatrix", "ratan2", "SquareRoot0") if not has(n)]
m = M.Machine(); c = m.cpu; c.R[29] = 0x801FFF00
A, B, D = 0x80100000, 0x80100100, 0x80100200          # scratch RAM for the retail calls
def call(n, *a): return C.s32(c.call(m.names[n], *[x & 0xFFFFFFFF for x in a], max_instr=200000))
def mat():  return [random.randint(-4096, 4096) for _ in range(9)] + [random.randint(-30000, 30000) for _ in range(3)]
def pack_m(v): return struct.pack("<9h2x3i", *v)
def unpack_m(b): return list(struct.unpack("<9h2x3i", b[:32]))
def sv(): return [random.randint(-4096, 4096) for _ in range(3)] + [0]
random.seed(args.seed); bad = {}
def chk(name, r, p, inp):
    if r != p: bad.setdefault(name, []).append((inp, r, p))
for _ in range(args.n):
    ang = [random.randint(-4096, 4096) for _ in range(3)] + [0]
    # RotMatrix
    c.write(A, struct.pack("<4h", *ang)); call("RotMatrix", A, B); r = unpack_m(c.read(B, 32))[:9]
    pb = ctypes.create_string_buffer(struct.pack("<4h", *ang)); pm = ctypes.create_string_buffer(32)
    if "RotMatrix" not in skipped:
        lib.RotMatrix(pb, pm); chk("RotMatrix", r, unpack_m(pm.raw)[:9], ang)
    for nm in ("RotMatrixX", "RotMatrixY", "RotMatrixZ"):
        m0 = mat(); a = random.randint(-4096, 4096)
        c.write(B, pack_m(m0)); call(nm, a, B); r = unpack_m(c.read(B, 32))[:9]
        pm = ctypes.create_string_buffer(pack_m(m0)); getattr(lib, nm)(a, pm); chk(nm, r, unpack_m(pm.raw)[:9], (a, m0))
    m0, m1 = mat(), mat()
    c.write(A, pack_m(m0)); c.write(B, pack_m(m1)); call("MulMatrix0", A, B, D); r = unpack_m(c.read(D, 32))[:9]
    pa, pb, pd = (ctypes.create_string_buffer(pack_m(x)) for x in (m0, m1, [0] * 12)); lib.MulMatrix0(pa, pb, pd)
    chk("MulMatrix0", r, unpack_m(pd.raw)[:9], (m0, m1))
    v = sv()
    c.write(A, pack_m(m0)); c.write(B, struct.pack("<4h", *v)); call("ApplyMatrix", A, B, D); r = list(struct.unpack("<3i", c.read(D, 12)))
    pa, pb, pd = ctypes.create_string_buffer(pack_m(m0)), ctypes.create_string_buffer(struct.pack("<4h", *v)), ctypes.create_string_buffer(16)
    lib.ApplyMatrix(pa, pb, pd); chk("ApplyMatrix", r, list(struct.unpack("<3i", pd.raw[:12])), (m0, v))
    call("ApplyMatrixSV", A, B, D); r = list(struct.unpack("<3h", c.read(D, 6)))
    pd = ctypes.create_string_buffer(8); lib.ApplyMatrixSV(pa, pb, pd); chk("ApplyMatrixSV", r, list(struct.unpack("<3h", pd.raw[:6])), (m0, v))
    # RotTransPers with the same GTE set-up on both sides
    t = [random.randint(-2000, 2000), random.randint(-2000, 2000), random.randint(500, 8000)]
    m0 = m0[:9] + t; h = random.choice([256, 512, 1000])
    c.write(A, pack_m(m0)); call("SetRotMatrix", A); call("SetTransMatrix", A); call("SetGeomScreen", h); call("SetGeomOffset", 160, 120)
    pa = ctypes.create_string_buffer(pack_m(m0)); lib.SetRotMatrix(pa); lib.SetTransMatrix(pa); lib.SetGeomScreen(h); lib.SetGeomOffset(160, 120)
    c.write(B, struct.pack("<4h", *v)); z = call("RotTransPers", B, D, D + 4, D + 8); r = (z, c.r32(D), C.s32(c.r32(D + 4)))
    o = ctypes.create_string_buffer(12)
    if has("RotTransPers"):
        z2 = lib.RotTransPers(ctypes.create_string_buffer(struct.pack("<4h", *v)), o, ctypes.byref(o, 4), ctypes.byref(o, 8))
        p = (z2, struct.unpack_from("<I", o.raw, 0)[0], struct.unpack_from("<i", o.raw, 4)[0])
    else:
        p = lib_rtp(ctypes.create_string_buffer(struct.pack("<4h", *v)), o, None, None)
    chk("RotTransPers", r, p, (m0, v, h))
for a in range(4096):
    for nm in ("rsin", "rcos"):
        chk(nm, call(nm, a), lib[nm](a), a)
for _ in range(args.n * 10):
    y, x = random.randint(-20000, 20000), random.randint(-20000, 20000)
    if "ratan2" not in skipped:
        lib.ratan2.restype = ctypes.c_int; chk("ratan2", call("ratan2", y, x), lib.ratan2(y, x), (y, x))
    v = random.randint(0, 1 << 28)
    if "SquareRoot0" not in skipped:
        lib.SquareRoot0.restype = ctypes.c_int; chk("SquareRoot0", call("SquareRoot0", v), lib.SquareRoot0(v), v)
if skipped:
    print("not shimmed (the retail code runs in the port): " + " ".join(skipped))
for k, v in sorted(bad.items()):
    print("%-14s %4d inputs differ, e.g. %s: retail %s, port %s" % (k, len(v), v[0][0], v[0][1], v[0][2]))

print("checked: rsin rcos (all angles), ratan2 SquareRoot0 (%d inputs), RotMatrix RotMatrixX/Y/Z MulMatrix0 ApplyMatrix "
      "ApplyMatrixSV RotTransPers (%d inputs)" % (args.n * 10, args.n))

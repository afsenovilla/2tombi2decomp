#!/usr/bin/env python3
"""Near misses among the library functions still in asm: compile each candidate (tools/libsweep.py) under every
compiler set-up and report how far the best one is from the retail bytes (differing words, size difference), so the
permuter (tools/permute.py) can be pointed at the closest. Writes build/libnear_<prog>.csv.

  python3 -I tools/libnear.py [--prog main] [--max-size 0x200] [-j N]
"""
import argparse, concurrent.futures as cf, csv, glob, os, re, shutil, struct, subprocess, sys, tempfile

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))
import cc, libsweep as L


def distance(obj, name, want):
    d = os.path.dirname(obj)
    subprocess.run(["mipsel-linux-gnu-objcopy", "-O", "binary", "-j", ".text", obj, d + "/t.bin"], check=True)
    text = open(d + "/t.bin", "rb").read()
    for l in subprocess.run(["mipsel-linux-gnu-nm", "-S", "--defined-only", obj], capture_output=True,
                            text=True).stdout.splitlines():
        p = l.split()
        if len(p) == 4 and p[3] == name:
            off, size = int(p[0], 16), int(p[1], 16)
            got = text[off:off + size]
            n = min(len(got), len(want)) // 4
            diff = sum(1 for i in range(n) if (struct.unpack("<I", got[4*i:4*i+4])[0] >> 26) !=
                       (struct.unpack("<I", want[4*i:4*i+4])[0] >> 26) or
                       (got[4*i:4*i+4] != want[4*i:4*i+4] and got[4*i+3] >> 2 not in (2, 3, 0x0F)))
            return diff + abs(len(got) - len(want)) // 4
    return None


def one(prog, name, binary, delta):
    addr, size = L.asm_info(prog, name)
    if addr is None or size is None:
        return None
    want = binary[addr - delta: addr - delta + size]
    best = None
    d = tempfile.mkdtemp(dir=os.path.join(ROOT, "build"))
    try:
        for kind, text in L.candidates(prog, name, None, None, ("pt", "m2c")):
            src = os.path.join(d, name + ".c")
            open(src, "w").write(text)
            for i, v in enumerate(L.VARIANTS):
                try:
                    cc.compile_c(src, os.path.join(d, "a.o"), v)
                except cc.CompileError:
                    continue
                dist = distance(os.path.join(d, "a.o"), name, want)
                if dist is not None and (best is None or dist < best[0]):
                    best = (dist, kind, i, size)
    finally:
        shutil.rmtree(d, ignore_errors=True)
    return (name,) + best if best else None


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--prog", default="main")
    ap.add_argument("--max-size", default="0x200")
    ap.add_argument("-j", type=int, default=os.cpu_count())
    a = ap.parse_args()
    lim = int(a.max_size, 0)
    names = []
    for f in glob.glob(os.path.join(ROOT, "src", a.prog, "psyq", "*", "*.c")):
        if "INCLUDE_ASM" in open(f).read():
            n = os.path.basename(f)[:-2]
            ad, sz = L.asm_info(a.prog, n)
            if sz and sz <= lim:
                names.append(n)
    binary, delta = L.prog_bytes(a.prog)
    with cf.ThreadPoolExecutor(a.j) as ex:
        rows = [r for r in ex.map(lambda n: one(a.prog, n, binary, delta), names) if r]
    rows.sort(key=lambda r: (r[1], r[4]))
    out = os.path.join(ROOT, "build", "libnear_%s.csv" % a.prog)
    with open(out, "w", newline="") as f:
        w = csv.writer(f)
        w.writerow(["name", "distance", "source", "variant", "size"])
        w.writerows(rows)
    print("%d / %d compile; distance <= 2: %d, <= 5: %d -> %s" % (len(rows), len(names),
          sum(r[1] <= 2 for r in rows), sum(r[1] <= 5 for r in rows), os.path.relpath(out, ROOT)))


if __name__ == "__main__":
    main()

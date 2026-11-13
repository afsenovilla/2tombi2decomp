#!/usr/bin/env python3
"""Find functions of a T2 program that are also in Tombi! 1 (PAL MAIN0.EXE, Tombi-Decomp checkout with game/MAIN0.EXE
and config/symbol_addrs_main0.txt): the same masked word sequence (call targets, lui and non-$sp offsets ignored, as
tools/funcstats.mask). Used for the Psy-Q library: names of static functions and the matched C of Tombi-Decomp.

  python3 -I tools/t1match.py [--prog main] [--t1 ../Tombi-Decomp] [--lib-only] [--csv build/t1match_main.csv]

Prints per T2 function: address, T2 name, T1 name, T1 source file when Tombi-Decomp has src/<T1 name>.c.
"""
import argparse, csv, glob, os, re, struct, sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))
from funcstats import mask, programs


def t1_funcs(t1):
    b = open(os.path.join(t1, "game", "MAIN0.EXE"), "rb").read()
    out = {}
    for l in open(os.path.join(t1, "config", "symbol_addrs_main0.txt")):
        m = re.match(r"\s*(\w+)\s*=\s*0x([0-9A-Fa-f]+);.*type:func.*size:0x([0-9A-Fa-f]+)", l)
        if m:
            a, s = int(m.group(2), 16), int(m.group(3), 16)
            off = a - 0x80010000 + 0x800
            fb = b[off:off + s]
            n = len(fb) // 4
            key = tuple(mask(w) for w in struct.unpack("<%dI" % n, fb[:n * 4]))
            out.setdefault(key, (m.group(1), a))
    return out


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--prog", default="main")
    ap.add_argument("--t1", default=os.path.join(os.path.dirname(ROOT), "Tombi-Decomp"))
    ap.add_argument("--lib-only", action="store_true")
    ap.add_argument("--csv")
    a = ap.parse_args()
    t1 = t1_funcs(a.t1)
    names = {}
    for l in open(os.path.join(ROOT, "config", "symbol_addrs_%s.txt" % a.prog)):
        m = re.match(r"\s*(\w+)\s*=\s*0x([0-9A-Fa-f]+);(.*)", l)
        if m:
            names[int(m.group(2), 16)] = (m.group(1), "psyq" in m.group(3))
    rows = []
    for prog, b, delta, ts, te, addrs in programs():
        if prog != a.prog:
            continue
        ends = list(addrs[1:]) + [te + delta]
        for s, e in zip(addrs, ends):
            fb = b[s - delta:e - delta]
            n = len(fb) // 4
            key = tuple(mask(w) for w in struct.unpack("<%dI" % n, fb[:n * 4]))
            hit = t1.get(key)
            if not hit:
                continue
            nm, lib = names.get(s, ("func_%08X" % s, False))
            if a.lib_only and not lib and not nm.startswith(("Ss", "_Ss", "Spu", "_spu", "Cd", "Gpu", "Pad")):
                pass
            srcf = os.path.join(a.t1, "src", hit[0] + ".c")
            rows.append(("%08X" % s, e - s, nm, hit[0], "%08X" % hit[1], os.path.exists(srcf)))
    for r in rows:
        print("%s %5d %-28s T1 %-28s %s %s" % (r[0], r[1], r[2], r[3], r[4], "src" if r[5] else "-"))
    print("%d functions found in T1 (%d with T1 C)" % (len(rows), sum(r[5] for r in rows)))
    if a.csv:
        with open(a.csv, "w", newline="") as f:
            w = csv.writer(f)
            w.writerow(["addr", "size", "t2_name", "t1_name", "t1_addr", "t1_src"])
            w.writerows(rows)


if __name__ == "__main__":
    main()

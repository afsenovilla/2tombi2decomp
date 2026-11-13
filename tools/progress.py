#!/usr/bin/env python3
"""Local progress: game code written in C (USA), counted like docs/PLAN.md (Psy-Q library and exact duplicates apart).

A function is done when its program's C files define it instead of INCLUDE_ASM-ing it (tools/build.py proves the
bytes). Programs still split as one asm block count as not started.

  python3 -I tools/progress.py
"""
import collections, glob, os, re, sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from funcstats import glabels, programs

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))


def asm_names(prog):
    out = set()
    for f in glob.glob(os.path.join(ROOT, "src", prog, "**", "*.c"), recursive=True):
        out |= set(re.findall(r"INCLUDE_ASM\([^,]+,\s*(\w+)\)", open(f).read()))
    return out


def addr_of(prog):
    """name -> start address, from the nonmatchings files (asm/<prog>/nonmatchings/**/NAME.s)."""
    out = {}
    for f in glob.glob(os.path.join(ROOT, "asm", prog, "nonmatchings", "**", "*.s"), recursive=True):
        m = re.search(r"/\* \w+ ([0-9A-F]{8}) [0-9A-F]{8} \*/", open(f).read())
        if m:
            out[os.path.basename(f)[:-2]] = int(m.group(1), 16)
    return out


def main():
    tot = collections.Counter()
    print("%-6s %10s %12s %8s" % ("prog", "functions", "bytes", "%"))
    for prog, b, delta, ts, te, addrs in programs():
        has_c = bool(glob.glob(os.path.join(ROOT, "src", prog, "**", "*.c"), recursive=True))
        pending = {addr_of(prog).get(n) for n in asm_names(prog)} if has_c else set(addrs)
        ends = sorted(addrs)[1:] + [te + delta]
        c = collections.Counter()
        for s, e in zip(sorted(addrs), ends):
            c["n"] += 1; c["B"] += e - s
            if s not in pending:
                c["d"] += 1; c["dB"] += e - s
        tot.update(c)
        if c["d"]:
            print("%-6s %4d/%-5d %6d/%-7d %6.2f" % (prog, c["d"], c["n"], c["dB"], c["B"], 100.0 * c["dB"] / c["B"]))
    print("%-6s %4d/%-5d %6d/%-7d %6.2f  (all code, library included; per-category figures: tools/funcstats.py)"
          % ("total", tot["d"], tot["n"], tot["dB"], tot["B"], 100.0 * tot["dB"] / tot["B"]))


if __name__ == "__main__":
    main()

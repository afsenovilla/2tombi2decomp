#!/usr/bin/env python3
"""Families of pending functions: every function still in asm, in every program (game files and Psy-Q library
files), grouped by its opcode sequence (registers, immediates, offsets and targets ignored: variants of one source
with other constants, fields or register choices), sorted by copies x size. The best targets for hand work: one
match gives the others through tools/nearcopy.py / tools/dupsweep.py (exact masked copies) or small edits.

  python3 -I tools/families.py [--min-copies 2] [--min-size 0x20] [--max-size 0x400] [--top 40] [--csv FILE]

Per family: copies, size (bytes, of the first), copies x size, programs, exact copies (the same masked words,
tools/funcstats.py mask()), the matched C functions of the same opcode sequence anywhere (a ready starting
point, `-` when none) and the member names. --csv writes every family (default build/families.csv).
"""
import argparse, collections, csv, os, re, struct, sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))
from funcstats import mask
import libsweep as L, nearcopy as N


def opkey(w):
    op = w >> 26
    if op == 0:
        return ("s", w & 0x3F)
    if op == 1:
        return ("r", (w >> 16) & 0x1F)
    if op == 0x12:
        return ("c2", (w >> 21) & 0x1F, w & 0x3F if (w >> 25) & 1 else 0)
    if op in (0x10, 0x11, 0x13):
        return ("c", op, (w >> 21) & 0x1F)
    return op


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--min-copies", type=int, default=2)
    ap.add_argument("--min-size", default="0x20")
    ap.add_argument("--max-size", default="0x400")
    ap.add_argument("--top", type=int, default=40)
    ap.add_argument("--csv", default=os.path.join(ROOT, "build", "families.csv"))
    a = ap.parse_args()
    lo, hi = int(a.min_size, 0), int(a.max_size, 0)
    fam = collections.defaultdict(list)      # opcode key -> [(prog, name, size, masked key)]
    done = collections.defaultdict(list)     # opcode key -> [(prog, name)] matched C
    for prog in N.progs_list():
        tp = N.Prog(prog)
        pending = set(tp.pending) | set(L.pending_files(prog))
        src = open(tp.src).read() if os.path.exists(tp.src) else ""
        inc = set(re.findall(r'INCLUDE_ASM\("[^"]+", (\w+)\);', src))
        for f in L.pending_files(prog).values():
            inc |= set(re.findall(r'INCLUDE_ASM\("[^"]+", (\w+)\);', open(f).read()))
        for name, (ad, size) in tp.funcs.items():
            if size < 8:
                continue
            b = tp.want(name)
            words = struct.unpack("<%dI" % (len(b) // 4), b[:len(b) // 4 * 4])
            k = tuple(opkey(w) for w in words)
            if name in pending:
                if lo <= size <= hi:
                    fam[k].append((prog, name, size, tuple(mask(w) for w in words)))
            elif name not in inc:
                done[k].append((prog, name))
    rows = []
    for k, mem in fam.items():
        if len(mem) < a.min_copies:
            continue
        exact = collections.Counter(m[3] for m in mem)
        progs = sorted({m[0] for m in mem})
        rows.append({"copies": len(mem), "size": mem[0][2], "score": len(mem) * mem[0][2], "programs": len(progs),
                     "exact": max(exact.values()), "matched": " ".join("%s:%s" % x for x in done.get(k, [])[:3]) or "-",
                     "members": " ".join("%s:%s" % (m[0], m[1]) for m in sorted(mem))})
    rows.sort(key=lambda r: (-r["score"], -r["copies"]))
    with open(a.csv, "w", newline="") as f:
        w = csv.DictWriter(f, fieldnames=list(rows[0]) if rows else ["copies"])
        w.writeheader()
        w.writerows(rows)
    print("%d families of %d+ pending functions (%d functions, 0x%X bytes); best first (copies x size):" %
          (len(rows), a.min_copies, sum(r["copies"] for r in rows), sum(r["score"] for r in rows)))
    print("%6s %5s %6s %5s %5s  %-30s %s" % ("score", "n", "size", "progs", "exact", "matched C (same opcodes)",
                                            "members"))
    for r in rows[:a.top]:
        mem = r["members"].split()
        print("%6d %5d %#6x %5d %5d  %-30s %s" % (r["score"], r["copies"], r["size"], r["programs"], r["exact"],
                                                  r["matched"][:30], " ".join(mem[:4]) + (" ..." if len(mem) > 4 else "")))
    print("all: " + os.path.relpath(a.csv, ROOT))


if __name__ == "__main__":
    main()

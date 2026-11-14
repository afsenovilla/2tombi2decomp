#!/usr/bin/env python3
"""Local progress per program, split into game code and the Psy-Q library (src/<prog>/psyq/), counted in functions
and bytes. A function is done when the C defines it (tools/build.py proves the bytes); library functions marked
`// ASM by design` (tools/asm_by_design.py) are done as assembly and shown apart.

  python3 -I tools/progress.py
"""
import collections, glob, os, re, sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from funcstats import glabels, programs

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))


def file_state(prog):
    """function name -> (library?, state) with state c / asm / pending, from src/<prog>/**/*.c."""
    out = {}
    for f in glob.glob(os.path.join(ROOT, "src", prog, "**", "*.c"), recursive=True):
        t = open(f).read()
        lib = "/psyq/" in f.replace(os.sep, "/")
        by_design = "// ASM by design:" in t
        for n in re.findall(r"INCLUDE_ASM\([^,]+,\s*(\w+)\)", t):
            out[n] = (lib, "asm" if by_design else "pending")
        if lib and "INCLUDE_ASM" not in t:
            out[os.path.basename(f)[:-2]] = (True, "c")
    return out


def addr_of(prog):
    out = {}
    for f in glob.glob(os.path.join(ROOT, "asm", prog, "*matchings", "**", "*.s"), recursive=True):
        m = re.search(r"/\* \w+ ([0-9A-F]{8}) [0-9A-F]{8} \*/", open(f).read())
        if m:
            out[m.group(1)] = os.path.basename(f)[:-2]
    return {int(k, 16): v for k, v in out.items()}


def main():
    total = collections.Counter()
    print("%-6s %-26s %-26s %-18s" % ("prog", "game in C", "library in C", "library asm by design"))
    for prog, b, delta, ts, te, addrs in programs():
        has_c = bool(glob.glob(os.path.join(ROOT, "src", prog, "**", "*.c"), recursive=True))
        st = file_state(prog) if has_c else {}
        names = addr_of(prog) if has_c else {}
        ends = list(addrs[1:]) + [te + delta]
        c = collections.Counter()
        for s, e in zip(addrs, ends):
            n = names.get(s)
            lib, state = st.get(n, (False, "c" if has_c else "pending")) if n else (False, "c" if has_c else "pending")
            if has_c and n is None:
                state = "c"   # in C (splat writes the .s of C functions too, so this is rare)
            cat = "lib" if lib else "game"
            c[cat + "_n"] += 1; c[cat + "_b"] += e - s
            if state in ("c", "asm"):
                c["%s_%s_n" % (cat, state)] += 1; c["%s_%s_b" % (cat, state)] += e - s
        total.update(c)
        if has_c:
            show(prog, c)
    show("total", total)


def show(prog, c):
    def part(cat, st):
        n, nn, bb, b = c["%s_%s_n" % (cat, st)], c[cat + "_n"], c["%s_%s_b" % (cat, st)], c[cat + "_b"]
        return "%4d/%-4d %6.2f%% of bytes" % (n, nn, 100.0 * bb / b if b else 0)
    print("%-6s %-26s %-26s %-18s" % (prog, part("game", "c"), part("lib", "c"), "%d" % c["lib_asm_n"]))


if __name__ == "__main__":
    main()

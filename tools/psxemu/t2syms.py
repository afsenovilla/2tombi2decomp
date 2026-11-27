#!/usr/bin/env python3
"""The address table of tools/psxemu for Tomba! 2 USA MAIN.EXE: every Psy-Q library function (name, address, library,
pure or not) and the game functions the HLE needs, from the matching build (build/main.elf names, asm/main/*/psyq/<lib>/
for the library of each function).  Names and addresses only: tools/psxemu/syms/main_usa.csv is committed, so the
emulator runs without a matching build.

  python3 -I tools/psxemu/t2syms.py            # rewrites tools/psxemu/syms/main_usa.csv (needs build/main.elf + asm/main)

"pure" follows port/tools/gen_t2.py (PURE_LIBS / PURE_GPU): plain CPU (+ GTE) code the emulator runs as retail MIPS;
every other library function touches hardware and is either HLE'd (machine.py) or a stub returning 0, as in the port.
"""
import os
import re
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
OUT = os.path.join(os.path.dirname(os.path.abspath(__file__)), "syms", "main_usa.csv")
PURE_LIBS = {"libc", "libc2", "libgte", "libsn"}
PURE_GPU = re.compile(r"^(Set(Poly|Line|Sprt|Tile|Semi|Shade|DrawMode|DrawTPage|DrawArea|DrawOffset|DrawStp|"
                      r"DrawEnv|Texwindow|DrawMove|DrawLoad)\w*|Get(TPage|Clut)|AddPrim\w*|CatPrim|TermPrim|"
                      r"NextPrim|IsEndPrim|MargePrim|DumpTPage|DumpClut|SetDefDrawEnv|SetDefDispEnv|setRECT)$")
# game functions the HLE refers to by name (none so far; kept for the table's format)
GAME_NAMES = set()


def main():
    syms = {}
    out = subprocess.run(["mipsel-linux-gnu-nm", os.path.join(ROOT, "build", "main.elf")], check=True,
                         stdout=subprocess.PIPE, universal_newlines=True).stdout
    for line in out.splitlines():
        p = line.split()
        if len(p) == 3 and not p[2].startswith(".") and not p[2].endswith(".NON_MATCHING"):
            syms.setdefault(p[2], int(p[0], 16))
    rows = []
    for kind in ("matchings", "nonmatchings"):
        base = os.path.join(ROOT, "asm", "main", kind, "psyq")
        for dp, _, fs in os.walk(base):
            lib = os.path.relpath(dp, base).split(os.sep)[0]
            for f in fs:
                n = f[:-2]
                if f.endswith(".s") and n in syms:
                    pure = lib in PURE_LIBS or (lib == "libgpu" and PURE_GPU.match(n) is not None)
                    rows.append((syms[n], n, lib, int(pure)))
    for n in GAME_NAMES:
        rows.append((syms[n], n, "game", 0))
    rows = sorted(set(rows))
    if not rows:
        sys.exit("no library functions found: run python3 tools/build.py main first")
    os.makedirs(os.path.dirname(OUT), exist_ok=True)
    with open(OUT, "w") as f:
        f.write("# tools/psxemu/t2syms.py: Psy-Q functions of Tomba! 2 USA MAIN.EXE (names and addresses only)\n")
        f.write("address,name,lib,pure\n")
        for a, n, lib, pure in rows:
            f.write("%08X,%s,%s,%d\n" % (a, n, lib, pure))
    print("%s: %d functions (%d pure)" % (os.path.relpath(OUT, ROOT), len(rows), sum(r[3] for r in rows)))


if __name__ == "__main__":
    main()

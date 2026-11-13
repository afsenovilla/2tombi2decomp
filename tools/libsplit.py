#!/usr/bin/env python3
"""Give every Psy-Q library function of a program its own C file (splat `c` subsegment), so each can be built with the
compiler / assembler Sony used for it (per-file `// CC`, `// FLAGS`, `// AS` headers, tools/build.py).

  python3 -I tools/libsplit.py [--prog main]

Needs a current split (asm/<prog>) and the library names (tools/name_lib.py). The library is the range covered by
the object signatures; each function start in it becomes `- [OFF, c, psyq/<lib>/<name>]` in config/<prog>.yaml,
replacing the subsegments there between the start of the library and the data segment. splat writes the missing
src/<prog>/psyq/<lib>/<name>.c files (INCLUDE_ASM) on the next split.
"""
import argparse, glob, os, re, sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))
import name_lib
from funcstats import glabels


def starts(prog):
    out = {}
    for f in glob.glob(os.path.join(ROOT, "asm", prog, "*matchings", "**", "*.s"), recursive=True):
        for a in glabels(f):
            out[a] = os.path.basename(f)[:-2]
    return out


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--prog", default="main")
    a = ap.parse_args()
    objs = name_lib.matches(a.prog, "/opt/psyq_sigs/440")
    lo, hi = objs[0][0], objs[-1][0] + objs[-1][1]
    st = starts(a.prog)
    y = open(os.path.join(ROOT, "config", a.prog + ".yaml")).read()
    vram = int(re.search(r"vram:\s*(0x\w+)", y).group(1), 16)
    start = int(re.search(r"type: code\n\s+start: (0x\w+)", y).group(1), 16)
    delta = vram - start
    lines = []
    for ad in sorted(x for x in st if lo <= x < hi):
        obj = [o for o in objs if o[0] <= ad < o[0] + o[1]]
        lib = obj[0][2].replace(".LIB", "").lower() if obj else "unknown"
        lines.append("      - [0x%X, c, psyq/%s/%s]" % (ad - delta, lib, st[ad]))
    # replace everything from the library start up to the data subsegment
    m = re.search(r"(?m)^      - \[0x(\w+), data, ", y)
    sub = list(re.finditer(r"(?m)^      - \[0x(\w+), (\w+), ([\w/]+)\]\n", y))
    keep = [s for s in sub if int(s.group(1), 16) < lo - delta or s.group(2) in ("data", "rodata", "bss")]
    if all(int(s.group(1), 16) != lo - delta for s in keep):
        pass
    head = y[:sub[0].start()]
    tail = y[sub[-1].end():]
    body = [s.group(0).rstrip("\n") for s in keep if int(s.group(1), 16) < lo - delta]
    body += lines
    body += [s.group(0).rstrip("\n") for s in keep if int(s.group(1), 16) >= hi - delta]
    open(os.path.join(ROOT, "config", a.prog + ".yaml"), "w").write(head + "\n".join(body) + "\n" + tail)
    print("%s: library 0x%08X..0x%08X, %d functions in their own files" % (a.prog, lo, hi, len(lines)))


if __name__ == "__main__":
    main()

#!/usr/bin/env python3
"""Install hand-written C (a scratch file of matched functions, checked with tools/ccheck.py) into src/<prog>/<prog>.c.

  python3 -I tools/install_c.py FILE.c [--prog main]

Each function replaces its INCLUDE_ASM line; the file's other top-level lines (types, externs, prototypes; not the
#include lines) go just before the first installed function, skipping lines already present in the target. Then the
linked build must be OK (tools/build.py <prog> --no-split), else the target is restored. Types that several programs
need belong in include/*.h instead.
"""
import argparse, os, re, subprocess, sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))
import ptsrc


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("src")
    ap.add_argument("--prog", default="main")
    a = ap.parse_args()
    path = os.path.join(ROOT, "src", a.prog, a.prog + ".c")
    old = open(path).read()
    t = old
    text = open(a.src).read()
    pre, funcs = [], []
    for kind, seg in ptsrc.items(text):
        s = seg.strip()
        if not s or (kind == "pp" and s.startswith("#include")):
            continue
        n = ptsrc.func_name(s) if s.endswith("}") else None
        if n:
            funcs.append((n, s))
        else:
            pre.append(s)
    lines = {}
    for n, body in funcs:
        line = 'INCLUDE_ASM("asm/%s/nonmatchings/%s", %s);' % (a.prog, a.prog, n)
        if line not in t:
            sys.exit("%s: no INCLUDE_ASM line for %s" % (path, n))
        lines[n] = (t.index(line), line)
    first = min(lines, key=lambda n: lines[n][0])     # the declarations go before the earliest function in the file
    for n, body in funcs:
        if n == first:
            extra = [p for p in pre if p not in t]
            body = "\n".join(extra + ([""] if extra else []) + [body])
        t = t.replace(lines[n][1], body)
    open(path, "w").write(t)
    r = subprocess.run([sys.executable, "tools/build.py", a.prog, "--no-split"], capture_output=True, text=True,
                       cwd=ROOT)
    if " OK " not in r.stdout:
        open(path, "w").write(old)
        sys.exit("linked build not OK, restored:\n" + r.stdout + r.stderr[-2500:])
    print("installed %d functions: %s" % (len(funcs), " ".join(n for n, _ in funcs)))


if __name__ == "__main__":
    main()

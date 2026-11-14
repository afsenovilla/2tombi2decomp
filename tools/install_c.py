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
    # a global the target declares with another type is used here under an alias name (config/aliases_<prog>.ld)
    import hashlib, libsweep
    aliases = libsweep.read_aliases(a.prog)
    decl_re = r"(?m)^(extern [^;(]*?\b(\w+)(?:\[[^\]]*\])?;)"
    theirs = {m.group(2): m.group(1) for m in re.finditer(decl_re, t)}
    for i, p in enumerate(pre):
        m = re.match(decl_re, p)
        if not m or m.group(2) not in theirs or theirs[m.group(2)] == m.group(1):
            continue
        k = m.group(2)
        am = re.fullmatch(r"(?:D|func)_([0-9A-F]{8})", k)
        if not am:
            sys.exit("%s is declared differently in %s; rename it by hand" % (k, path))
        new = "%s_%s" % (k, hashlib.sha1(p.encode()).hexdigest()[:4])
        aliases[new] = int(am.group(1), 16)
        pre[i] = re.sub(r"\b%s\b" % k, new, p)
        funcs = [(n, re.sub(r"\b%s\b" % k, new, b)) for n, b in funcs]
    libsweep.write_aliases(a.prog, aliases)
    lines = {}
    for n, body in funcs:
        line = 'INCLUDE_ASM("asm/%s/nonmatchings/%s", %s);' % (a.prog, a.prog, n)
        if line not in t:
            sys.exit("%s: no INCLUDE_ASM line for %s" % (path, n))
        lines[n] = (t.index(line), line)
    first = min(lines, key=lambda n: lines[n][0])     # the declarations go before the earliest function in the file
    before = t[:lines[first][0]]
    defined = set(re.findall(r"(?m)^[\w][\w \*]*?\b(\w+)\s*\([^;{}]*\)\s*\{", t))

    def wanted(p):
        if p in before:
            return False
        # prototypes are left out: the asm drafts call functions with the argument counts m2c saw (pass-through
        # arguments dropped), which a prototype would reject; calls compile the same without one
        m = re.match(r"[\w \*]+?\b(\w+)\s*\([^;{}]*\)\s*;$", p)
        return not m
    for n, body in funcs:
        if n == first:
            extra = [p for p in pre if wanted(p)]
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

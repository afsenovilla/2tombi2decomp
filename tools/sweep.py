#!/usr/bin/env python3
"""Sweep: draft every not-yet-decompiled function of a program with m2c (tools/decomp.py) and keep the drafts that
match the retail bytes as they come out.

  python3 -I tools/sweep.py [--prog main] [--max-size 0x80] [--install] [-j N]

Prints the matching names; --install replaces their INCLUDE_ASM lines in src/<prog>/*.c (the function plus the `extern`
declarations of the globals it uses; calls to functions without a prototype are left implicit) and then runs tools/build.py <prog> --no-split: if the linked
build is not OK, src is restored.
"""
import argparse, concurrent.futures as cf, glob, os, re, shutil, subprocess, sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))
import decomp as D


def pending(prog):
    out = []
    for f in glob.glob(os.path.join(ROOT, "src", prog, "**", "*.c"), recursive=True):
        out += re.findall(r'INCLUDE_ASM\("[^"]+", (\w+)\);', open(f).read())
    return out


def size_of(prog, name):
    t = open(D.find_asm(prog, name)).read()
    m = re.search(r"^nonmatching \w+,\s*(0x\w+)", t, re.M)
    return int(m.group(1), 16) if m else 1 << 30   # data words splat found in the text (dlabel): never drafted


def attempt(prog, name, ctx):
    r = subprocess.run([sys.executable, D.M2C, "--target", "mipsel-gcc-c", "--valid-syntax", "--context", ctx,
                        D.find_asm(prog, name)],
                       capture_output=True, text=True, cwd=ROOT)
    if r.returncode or not r.stdout.strip() or "Decompilation failure" in r.stdout:
        return name, None
    body = re.sub(r"(?m)^(extern )?\? ", r"\1s32 ", r.stdout)
    d = os.path.join(ROOT, "build", "sweep")
    os.makedirs(d, exist_ok=True)
    test = os.path.join(d, name + ".c")
    open(test, "w").write('#include "common.h"\n#include "game.h"\n#include "m2c.h"\n' + body)
    c = subprocess.run([sys.executable, "-I", os.path.join(ROOT, "tools", "ccheck.py"), test, "--prog", prog,
                        "--func", name], capture_output=True, text=True, cwd=ROOT)
    if c.returncode == 0 and c.stdout.startswith("OK"):
        fn = re.search(r"(?ms)^[^\n]*\b%s\(.*?^}\n" % re.escape(name), body)
        if not fn:
            return name, None
        # the globals it uses, declared just before it (file scope; a type clash with another draft fails the build)
        ext = [l for l in body.splitlines() if l.startswith("extern ")]
        return name, "\n".join(ext + ([""] if ext else []) + [fn.group(0).rstrip()])
    return name, None


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--prog", default="main")
    ap.add_argument("--max-size", default="0x80")
    ap.add_argument("--install", action="store_true")
    ap.add_argument("-j", type=int, default=os.cpu_count())
    a = ap.parse_args()
    lim = int(a.max_size, 0)
    names = [n for n in pending(a.prog) if size_of(a.prog, n) <= lim]
    ctx = D.context()
    with cf.ThreadPoolExecutor(a.j) as ex:
        res = [r for r in ex.map(lambda n: attempt(a.prog, n, ctx), names) if r[1]]
    print("%d / %d functions <= 0x%X match as drafted" % (len(res), len(names), lim))
    for n, _ in res:
        print("  " + n)
    if not a.install or not res:
        return
    files = glob.glob(os.path.join(ROOT, "src", a.prog, "**", "*.c"), recursive=True)
    backup = {f: open(f).read() for f in files}
    decl = {}   # global name -> its extern line; a draft whose extern disagrees with an earlier one is left out
    for t in backup.values():
        for l in re.findall(r"(?m)^extern [^;(]*?\b(\w+)(?:\[[^\]]*\])?;", t):
            pass
        for m in re.finditer(r"(?m)^(extern [^;(]*?\b(\w+)(?:\[[^\]]*\])?;)", t):
            decl[m.group(2)] = m.group(1)
    keep = []
    for n, fn in res:
        mine = {m.group(2): m.group(1) for m in re.finditer(r"(?m)^(extern [^;(]*?\b(\w+)(?:\[[^\]]*\])?;)", fn)}
        if any(k in decl and decl[k] != v for k, v in mine.items()):
            print("  skipped (type clash with an earlier declaration): " + n)
            continue
        decl.update(mine)
        keep.append((n, fn))
    res = keep
    def build_ok():
        b = subprocess.run([sys.executable, os.path.join(ROOT, "tools", "build.py"), a.prog, "--no-split"],
                           capture_output=True, text=True, cwd=ROOT)
        return " OK " in b.stdout

    def put(pairs):
        for f in files:
            t = backup[f]
            for n, fn in pairs:
                t = t.replace('INCLUDE_ASM("asm/%s/nonmatchings/%s", %s);' % (a.prog, a.prog, n), fn)
            open(f, "w").write(t)

    put(res)
    if not build_ok():   # find the drafts that break the link (e.g. new rodata) one at a time
        good = []
        for p in res:
            put(good + [p])
            if build_ok():
                good.append(p)
            else:
                print("  left out (linked build differs): " + p[0])
        put(good)
        res = good
        if not build_ok():
            put([])
            sys.exit("linked build not OK, src restored")
    print("installed %d functions; linked build OK" % len(res))


if __name__ == "__main__":
    main()

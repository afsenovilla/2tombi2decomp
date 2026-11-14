#!/usr/bin/env python3
"""Draft C for one function with m2c (github.com/matt-kempster/m2c, cloned to /opt/m2c by the bootstrap), using the
project headers as context, and optionally check the draft at once.

  python3 -I tools/decomp.py NAME [--prog main] [--check] [--write]

NAME: a function of asm/<prog>/nonmatchings. The context is include/common.h + every include/*.h, preprocessed
(build/ctx.c). --check compiles the draft with the game's compiler (tools/ccheck.py) and reports OK / DIFF;
--write also replaces the function's INCLUDE_ASM line in src/<prog>/*.c by the draft when it matches.
A draft is only a start: most functions need types and hand edits before they match.
"""
import argparse, glob, os, re, subprocess, sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
M2C = os.environ.get("M2C", "/opt/m2c/m2c.py")
CC = "/opt/oldgcc/gcc-2.8.1-psx"


def context():
    out = os.path.join(ROOT, "build", "ctx.c")
    os.makedirs(os.path.dirname(out), exist_ok=True)
    hs = ["common.h"] + sorted(os.path.basename(h) for h in glob.glob(os.path.join(ROOT, "include", "*.h"))
                               if os.path.basename(h) not in ("common.h", "m2c.h", "psyq_all.h"))
    src = "".join('#include "%s"\n' % h for h in hs)
    r = subprocess.run([CC + "/cpp", "-undef", "-D__GNUC__=2", "-DMIPSEL", "-D_LANGUAGE_C", "-DM2CTX", "-P",
                        "-I" + os.path.join(ROOT, "include"), "-I" + os.path.join(ROOT, "include", "psyq")], input=src, capture_output=True, text=True)
    if r.returncode:
        sys.exit(r.stderr)
    open(out, "w").write(re.sub(r"__asm__\(.*?\);", "", r.stdout, flags=re.S))
    return out


def find_asm(prog, name):
    hits = glob.glob(os.path.join(ROOT, "asm", prog, "nonmatchings", "**", name + ".s"), recursive=True)
    if not hits:
        sys.exit("no asm for %s in %s" % (name, prog))
    return hits[0]


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("name")
    ap.add_argument("--prog", default="main")
    ap.add_argument("--check", action="store_true")
    ap.add_argument("--write", action="store_true")
    a = ap.parse_args()
    r = subprocess.run([sys.executable, M2C, "--target", "mipsel-gcc-c", "--context", context(),
                        find_asm(a.prog, a.name)], capture_output=True, text=True, cwd=ROOT)
    draft = r.stdout
    if r.returncode or not draft.strip():
        sys.exit(r.stderr or "m2c failed")
    print(draft)
    if not (a.check or a.write):
        return
    test = os.path.join(ROOT, "build", "draft_%s.c" % a.name)
    body = re.sub(r"(?m)^(extern )?\? ", r"\1s32 ", draft)          # unknown return types of externs
    open(test, "w").write('#include "common.h"\n' + body)
    r = subprocess.run([sys.executable, "-I", os.path.join(ROOT, "tools", "ccheck.py"), test, "--prog", a.prog,
                        "--func", a.name], capture_output=True, text=True, cwd=ROOT)
    print(r.stdout + r.stderr[-2000:])
    if a.write and r.returncode == 0 and r.stdout.startswith("OK"):
        for f in glob.glob(os.path.join(ROOT, "src", a.prog, "**", "*.c"), recursive=True):
            t = open(f).read()
            line = re.search(r'INCLUDE_ASM\("[^"]+", %s\);' % re.escape(a.name), t)
            if line:
                fn = re.search(r"(?ms)^[^\n]*\b%s\(.*?^}\n" % re.escape(a.name), body).group(0)
                open(f, "w").write(t.replace(line.group(0), fn.rstrip()))
                print("written to %s (add any extern declarations it needs at the top)" % os.path.relpath(f, ROOT))
                break


if __name__ == "__main__":
    main()

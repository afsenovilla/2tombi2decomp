#!/usr/bin/env python3
"""Run decomp-permuter (github.com/simonlindholm/decomp-permuter, /opt/permuter) on one function with the game's
compiler pipeline. Starts from a C file holding the function (or the m2c draft when none is given).

  python3 -I tools/permute.py NAME [--prog main] [--src FILE.c] [--seconds 600] [-j N]

Sets up build/permute/NAME/ (base.c preprocessed, target.o from the retail asm, compile.sh = gcc 2.8.1 + maspsx 2.79
+ as) and runs the permuter for --seconds. Its best candidates land in build/permute/NAME/output-*/; a score of 0 is a
match: copy the function into src/ and check with tools/ccheck.py and tools/build.py.
"""
import argparse, os, re, subprocess, sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))
import decomp as D

CC = "/opt/oldgcc/gcc-2.8.1-psx"
COMPILE = """#!/bin/bash
# decomp-permuter compile script: $1 = input .c, $3 = output .o
set -e
T=$(mktemp -d)
{cc}/cpp -undef -D__GNUC__=2 -DMIPSEL -D_LANGUAGE_C -DPERMUTER -I{root}/include "$1" $T/a.i
{cc}/cc1 -O2 -G0 -funsigned-char -quiet -w $T/a.i -o $T/a.s
python3 /opt/maspsx/maspsx.py --aspsx-version=2.79 --expand-div < $T/a.s > $T/b.s
mipsel-linux-gnu-as -EL -march=r3000 -mtune=r3000 -no-pad-sections -O1 -G0 -I{root}/include $T/b.s -o "$3"
rm -rf $T
"""


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("name")
    ap.add_argument("--prog", default="main")
    ap.add_argument("--src")
    ap.add_argument("--seconds", type=int, default=600)
    ap.add_argument("-j", type=int, default=os.cpu_count())
    a = ap.parse_args()
    d = os.path.join(ROOT, "build", "permute", a.name)
    os.makedirs(d, exist_ok=True)
    if a.src:
        text = open(a.src).read()
    else:
        r = subprocess.run([sys.executable, D.M2C, "--target", "mipsel-gcc-c", "--context", D.context(),
                            D.find_asm(a.prog, a.name)], capture_output=True, text=True, cwd=ROOT)
        text = '#include "common.h"\n' + re.sub(r"(?m)^(extern )?\? ", r"\1s32 ", r.stdout)
    # keep only this function's body among the file's functions: other functions become prototypes is not needed;
    # the permuter scores the whole object, so the input must hold just this function.
    text = re.sub(r'(?m)^INCLUDE_ASM\(.*\);\s*$', "", text)
    src = os.path.join(d, "in.c")
    open(src, "w").write(text)
    pre = subprocess.run([CC + "/cpp", "-undef", "-D__GNUC__=2", "-DMIPSEL", "-D_LANGUAGE_C", "-DPERMUTER", "-P",
                          "-I" + os.path.join(ROOT, "include"), src], capture_output=True, text=True, check=True).stdout
    pre = re.sub(r"__asm__\(.*?\);", "", pre, flags=re.S)
    open(os.path.join(d, "base.c"), "w").write(pre)
    sh = os.path.join(d, "compile.sh")
    open(sh, "w").write(COMPILE.format(cc=CC, root=ROOT))
    os.chmod(sh, 0o755)
    subprocess.run(["mipsel-linux-gnu-as", "-EL", "-march=r3000", "-mtune=r3000", "-no-pad-sections", "-G0",
                    "-I" + os.path.join(ROOT, "include"), D.find_asm(a.prog, a.name), "-o",
                    os.path.join(d, "target.o")], check=True, cwd=ROOT)
    open(os.path.join(d, "settings.toml"), "w").write('func_name = "%s"\ncompiler_type = "gcc"\n' % a.name)
    print("permuter dir: " + os.path.relpath(d, ROOT))
    try:
        subprocess.run([sys.executable, "/opt/permuter/permuter.py", d, "-j", str(a.j), "--stop-on-zero"],
                       timeout=a.seconds, cwd=ROOT)
    except subprocess.TimeoutExpired:
        print("time limit reached; best candidates in %s/output-*" % os.path.relpath(d, ROOT))


if __name__ == "__main__":
    main()

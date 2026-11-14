#!/usr/bin/env python3
"""Guess every function's parameter count from its asm (the argument registers $a0..$a3 it reads before writing
them, scanning the code in order; a later one implies the earlier ones) and write prototypes for m2c's context,
so its drafts pass arguments a wrapper forwards untouched (`f(arg0, arg1, 0)` rather than `f(0)`).

  python3 -I tools/arity.py PROG   -> build/arity_<PROG>.h  (also used by tools/sweep.py)

Only functions without a C definition yet get a prototype, typed M2C_UNK (int).
"""
import glob, os, re, sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
REG = re.compile(r"\$(a[0-3])\b")


def arity(asm_text):
    seen_w, read = set(), set()
    for line in asm_text.splitlines():
        m = re.match(r"\s*/\* \w+ \w+ \w+ \*/\s+(\w[\w.]*)\s*(.*)", line)
        if not m:
            continue
        op, args = m.group(1), m.group(2).split("/*")[0]
        regs = REG.findall(args)
        if not regs:
            continue
        ops = [a.strip() for a in args.split(",")]
        dest = None
        if op not in ("sw", "sh", "sb", "swl", "swr", "beq", "bne", "bnez", "beqz", "bgez", "bltz", "blez", "bgtz",
                      "jr", "jalr", "mtlo", "mthi", "mtc2", "ctc2", "j", "jal", "mult", "multu", "div", "divu",
                      "sll_dummy") and ops and REG.fullmatch(ops[0]):
            dest = ops[0][1:]
        srcs = [r for r in regs] if dest is None else REG.findall(",".join(ops[1:]))
        for r in srcs:
            if r not in seen_w:
                read.add(r)
        if dest:
            seen_w.add(dest)
        if op in ("jal", "jalr"):
            break           # the callee's arguments are the caller's business from here
    if not read:
        return 0
    return max(int(r[1]) for r in read) + 1


def main():
    prog = sys.argv[1]
    defined = set()
    for f in glob.glob(os.path.join(ROOT, "src", prog, "**", "*.c"), recursive=True):
        defined |= set(re.findall(r"(?m)^[\w][\w \*]*?\b(\w+)\s*\([^;{}]*\)\s*\{", open(f).read()))
    out = ["/* Parameter counts guessed from the asm by tools/arity.py: m2c context only. */"]
    for f in sorted(glob.glob(os.path.join(ROOT, "asm", prog, "*matchings", "**", "*.s"), recursive=True)):
        name = os.path.basename(f)[:-2]
        if name in defined:
            continue
        t = open(f).read()
        if "\nglabel " not in "\n" + t:
            continue
        n = arity(t)
        out.append("M2C_UNK %s(%s);" % (name, ", ".join(["M2C_UNK"] * n) if n else "void"))
    os.makedirs(os.path.join(ROOT, "build"), exist_ok=True)
    open(os.path.join(ROOT, "build", "arity_%s.h" % prog), "w").write("\n".join(out) + "\n")
    print("%s: %d prototypes" % (prog, len(out) - 1))


if __name__ == "__main__":
    main()

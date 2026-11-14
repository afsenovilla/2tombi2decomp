#!/usr/bin/env python3
"""Mark the library functions that are hand-written assembly in Sony's own source, so they stay asm on purpose:
BIOS call stubs (`li $t2, 0xA0|0xB0|0xC0; jr $t2; li $t1, N`), syscall wrappers (Enter/ExitCriticalSection) and the
libsn start-up code. The file keeps its INCLUDE_ASM (the retail asm, generated from the disc) under a
`// ASM by design: ...` line; tools/progress.py counts these apart.

  python3 -I tools/asm_by_design.py [--prog main] [--write]
"""
import argparse, glob, os, re

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
MARK = "// ASM by design: "


def kind(asm):
    s = open(asm).read()
    ins = re.findall(r"\*/\s+(\w[\w.]*)", s)
    if len(ins) <= 4 and re.search(r"addiu\s+\$t2, \$zero, 0x[ABC]0\b", s) and "jr" in ins:
        return "BIOS call stub (jump through the A0/B0/C0 table), assembly in Sony's source"
    if len(ins) <= 6 and "syscall" in ins:
        return "syscall wrapper, assembly in Sony's source"
    if "__SN_ENTRY_POINT" in asm:
        return "libsn start-up code (crt0), assembly in Sony's source"
    return None


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--prog", default="main")
    ap.add_argument("--write", action="store_true")
    a = ap.parse_args()
    n = 0
    for f in sorted(glob.glob(os.path.join(ROOT, "src", a.prog, "psyq", "*", "*.c"))):
        t = open(f).read()
        if "INCLUDE_ASM" not in t or MARK in t:
            continue
        name = os.path.basename(f)[:-2]
        asm = glob.glob(os.path.join(ROOT, "asm", a.prog, "*matchings", "psyq", "*", name, name + ".s"))
        k = kind(asm[0]) if asm else None
        if k:
            n += 1
            print("%-28s %s" % (name, k))
            if a.write:
                open(f, "w").write(MARK + k + ".\n" + t)
    print("%d functions" % n)


if __name__ == "__main__":
    main()

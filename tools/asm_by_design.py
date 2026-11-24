#!/usr/bin/env python3
"""Mark the library functions that are hand-written assembly in Sony's own source, so they stay asm on purpose:
BIOS call stubs (`li $t2, 0xA0|0xB0|0xC0; jr $t2; li $t1, N`), syscall wrappers (Enter/ExitCriticalSection) and the
libsn start-up code. The file keeps its INCLUDE_ASM (the retail asm, generated from the disc) under a
`// ASM by design: ...` line; tools/progress.py counts these apart.

--game: the same for game code (src/<prog>/<prog>.c of every program, or --prog): a pending function is hand-written
assembly when it has no stack frame and uses instructions gcc 2.8.1 never emits for C: the trapping `add` / `addi` /
`sub` (gcc emits addu / addiu / subu) or `or rd, $zero, rs` moves (gcc's move is `addu rd, rs, $zero`). None of the
matched game functions has either (checked when the scan runs: a hit among them stops the tool). The mark is a
`// ASM by design: ...` line right above the INCLUDE_ASM line (tools/sync_src.py keeps it with the line).

  python3 -I tools/asm_by_design.py [--prog main] [--write]
  python3 -I tools/asm_by_design.py --game [--prog a00] [--write]
"""
import argparse, glob, os, re, sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

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


TRAP = re.compile(r"\*/\s+(add|addi|sub)\s+\$")
ORMOVE = re.compile(r"\*/\s+or\s+\$\w+, \$zero, \$\w+")
FRAME = re.compile(r"addiu\s+\$sp, \$sp, -")


def game_kind(asm):
    s = open(asm).read()
    if FRAME.search(s):
        return None
    why = []
    if TRAP.search(s):
        why.append("trapping add / addi / sub")
    if ORMOVE.search(s):
        why.append("`or rd, $zero, rs` moves")
    if not why:
        return None
    gte = " GTE" if re.search(r"\b(lwc2|mtc2|swc2)\b", s) else ""
    return "hand-written%s routine (no stack frame, %s: never emitted by gcc 2.8.1)" % (gte, ", ".join(why))


def game(a):
    import progress as P
    from nearcopy import progs_list
    progs = [a.prog] if a.prog else progs_list()
    # the signature must not occur in matched game code
    bad = [f for f in glob.glob(os.path.join(ROOT, "asm", "*", "matchings", "**", "*.s"), recursive=True)
           if "/psyq/" not in f.replace(os.sep, "/") and game_kind(f)]
    if bad:
        sys.exit("the signature occurs in matched C, not safe: " + ", ".join(os.path.relpath(f, ROOT) for f in bad[:5]))
    n = 0
    for prog in progs:
        path = os.path.join(ROOT, "src", prog, prog + ".c")
        if not os.path.exists(path):
            continue
        t = open(path).read()
        done = P.by_design(t)
        new = t
        for name in re.findall(r'(?m)^INCLUDE_ASM\("[^"]+", (\w+)\);', t):
            if name in done:
                continue
            asm = os.path.join(ROOT, "asm", prog, "nonmatchings", prog, name + ".s")
            k = game_kind(asm) if os.path.exists(asm) else None
            if not k:
                continue
            n += 1
            print("%-4s %-44s %s" % (prog, name, k))
            new = re.sub(r'(?m)^(INCLUDE_ASM\("[^"]+", %s\);)' % name, lambda m: MARK + k + ".\n" + m.group(1), new)
        if a.write and new != t:
            open(path, "w").write(new)
    print("%d functions%s" % (n, "" if a.write else " (--write marks them)"))


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--prog")
    ap.add_argument("--game", action="store_true", help="game code (src/<prog>/<prog>.c)")
    ap.add_argument("--write", action="store_true")
    a = ap.parse_args()
    if a.game:
        return game(a)
    a.prog = a.prog or "main"
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

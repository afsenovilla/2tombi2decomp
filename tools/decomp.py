#!/usr/bin/env python3
"""Draft C for one function with m2c (github.com/matt-kempster/m2c, cloned to /opt/m2c by the bootstrap), using the
project headers as context, and optionally check the draft at once.

  python3 -I tools/decomp.py NAME [--prog main] [--check] [--write]

NAME: a function of asm/<prog>/nonmatchings. The context is include/common.h + every include/*.h, preprocessed
(build/ctx.c). The program's jump tables (the jtbl_ blocks of asm/<prog>/data/*rodata*.s, gathered in
build/m2c_jtbl_<prog>.s) are passed too, so functions with a switch through a jump table decompile (m2c refuses a
`jr` without its table; the rest of the rodata is left out, so drafts keep D_ symbols instead of string literals).
--check compiles the draft with the game's compiler (tools/ccheck.py) and reports OK / DIFF; --write also replaces
the function's INCLUDE_ASM line in src/<prog>/*.c by the draft when it matches.
A draft is only a start: most functions need types and hand edits before they match. After the draft, a
`/* decomp.py: ... */` note flags each call whose m2c arguments include argument registers not written before the
`jal` in its block (a guessed argument from an older value, or a parameter passed through).
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


def jtbl_file(prog):
    """build/m2c_jtbl_<prog>.s: the jump tables of the program's rodata, for m2c (None when it has none)."""
    out = os.path.join(ROOT, "build", "m2c_jtbl_%s.s" % prog)
    srcs = sorted(glob.glob(os.path.join(ROOT, "asm", prog, "data", "*rodata*.s")))
    if not srcs:
        return None
    if os.path.exists(out) and os.path.getmtime(out) >= max(os.path.getmtime(s) for s in srcs):
        return out
    keep = ['.include "macro.inc"', '.section .rodata, "a"']
    for s in srcs:
        cur = False
        for l in open(s):
            m = re.match(r"\s*(end)?dlabel (\w+)", l)
            if m:
                cur = m.group(2).startswith("jtbl_") and not m.group(1)
                if m.group(1) and m.group(2).startswith("jtbl_"):
                    keep.append(l.rstrip())
            if cur:
                keep.append(l.rstrip())
    import threading
    tmp = out + ".%d.%d" % (os.getpid(), threading.get_ident())
    open(tmp, "w").write("\n".join(keep) + "\n")
    os.replace(tmp, out)
    return out


def m2c_cmd(prog, name, ctx, opts=()):
    """the m2c command line for one function: context, options, its .s and the program's jump tables."""
    jt = jtbl_file(prog)
    return [sys.executable, M2C, "--target", "mipsel-gcc-c"] + list(opts) + ["--context", ctx,
                                                                            find_asm(prog, name)] + ([jt] if jt else [])


def find_asm(prog, name):
    hits = glob.glob(os.path.join(ROOT, "asm", prog, "nonmatchings", "**", name + ".s"), recursive=True)
    if not hits:
        sys.exit("no asm for %s in %s" % (name, prog))
    return hits[0]


ARGREG = {"$a0": 0, "$a1": 1, "$a2": 2, "$a3": 3}
NODEST = re.compile(r"^(sb|sh|sw|swl|swr|swc2|b\w*|j|jal|jr|jalr|mult|multu|div|divu|mthi|mtlo|mtc\d|ctc\d|"
                    r"syscall|break|nop|cop2)$")


def guessed_args(prog, name, draft):
    """notes on the calls whose m2c draft passes more arguments than the argument registers written on every path
    to the `jal` since the function's entry or the previous call (m2c then takes a stale value: a guessed
    argument, or a parameter passed through when a path from the entry has no call): check the callee's real
    parameter count."""
    try:
        lines = open(find_asm(prog, name)).read().split("\n")
    except SystemExit:
        return []
    ins, labels, pend = [], {}, []
    for l in lines:
        m = re.match(r"\s*(\.L\w+):|\s*jlabel\s+(\.L\w+)", l)
        if m:
            pend.append(m.group(1) or m.group(2))
            continue
        m = re.match(r"\s*/\* \w+ ([0-9A-F]{8}) [0-9A-F]{8} \*/\s+(\S+)\s*(.*)$", l)
        if m:
            for lb in pend:
                labels[lb] = len(ins)
            pend = []
            ins.append((m.group(2), m.group(3), m.group(1)))
    n = len(ins)
    br = re.compile(r"^(b\w*|j|jr|jalr)$")
    jl = sorted(v for k, v in labels.items())
    succ = [[i + 1] if i + 1 < n else [] for i in range(n)]
    for i, (mn, ops, ad) in enumerate(ins):
        if br.match(mn) and i + 1 < n and mn != "jalr":
            tg = ops.split(",")[-1].strip()
            if mn == "jr":
                outs = [] if tg == "$ra" else jl            # a jump table: any label
            else:
                outs = [labels[tg]] if tg in labels else []
                if mn not in ("j", "b"):
                    outs.append(i + 2)
            succ[i + 1] = [x for x in outs if x < n]
    ALL = frozenset(range(4))
    state = [None] * n                                      # (written arg regs, reachable from the entry)
    state[0] = (frozenset(), True)
    work = [0]
    while work:
        i = work.pop()
        w, ent = state[i]
        mn, ops = ins[i][0], ins[i][1]
        if not NODEST.match(mn):
            d = ops.split(",")[0].strip()
            if d in ARGREG:
                w = w | {ARGREG[d]}
        if i > 0 and ins[i - 1][0] in ("jal", "jalr"):
            w, ent = ALL, False                              # after a call: no stale argument any more
        for s_ in succ[i]:
            old = state[s_]
            new = (w, ent) if old is None else (old[0] & w, old[1] or ent)
            if new != old:
                state[s_] = new
                work.append(s_)
    sys.path.insert(0, os.path.join(ROOT, "tools"))
    import install_c
    body = "\n".join(l for l in draft.split("\n") if l[:1].isspace())    # calls, not the extern prototypes
    out = []
    for i, (mn, ops, ad) in enumerate(ins):
        if mn != "jal" or state[i] is None or i + 1 >= n:
            continue
        w, ent = state[i]
        d = ins[i + 1][1].split(",")[0].strip() if not NODEST.match(ins[i + 1][0]) else ""
        if d in ARGREG:
            w = w | {ARGREG[d]}
        callee = ops.strip()
        counts = [c for c in install_c.calls(body, callee) if c]
        top = max(counts) if counts else 0
        missing = [k for k in range(top) if k not in w]
        if missing:
            out.append("/* decomp.py: %s at %s: %s not written on every path to the call (%s): check %s's real "
                       "parameter count */" % (callee, ad, ", ".join("a%d" % k for k in missing),
                                               "maybe parameters passed through" if ent else
                                               "m2c used an older value", callee))
    return out


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("name")
    ap.add_argument("--prog", default="main")
    ap.add_argument("--check", action="store_true")
    ap.add_argument("--write", action="store_true")
    a = ap.parse_args()
    r = subprocess.run(m2c_cmd(a.prog, a.name, context()), capture_output=True, text=True, cwd=ROOT)
    draft = r.stdout
    if r.returncode or not draft.strip():
        sys.exit(r.stderr or "m2c failed")
    print(draft)
    for note in guessed_args(a.prog, a.name, draft):
        print(note)
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

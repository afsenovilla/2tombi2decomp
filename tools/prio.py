#!/usr/bin/env python3
"""Register allocation priorities of one scratch function, from cc1's local / global allocation dumps.

  python3 -I tools/prio.py FILE.c [FUNC] [--prog P] [--cc C] [--flags F] [--all]

Compiles FILE.c as tools/cc.py would (its // CC / // FLAGS lines, or the overrides) with `-dl -dg` and prints, per
pseudo register of FUNC (default: the last function of the file): the uses (refs), the live length in insns,
whether it is local to a block (local-alloc) or global (global-alloc), the calls it crosses, the pseudo priority
floor_log2(refs) * refs / live_length that gcc 2.8 allocates by (higher first: it gets the first free register in
allocation order; a pseudo crossing calls wants a saved register), and the hard register it got. User variables
(`reg/v`) are named after the function's parameters and locals in declaration order (a guess: gcc numbers them in
that order; a variable without a register of its own, or an optimised-out one, shifts the names: check against
the insns with --all, which also prints the insns that set each pseudo). Highest priority first.

With the function's retail bytes (--prog, default main; any function with an address), the `retail` column gives
the register retail uses where ours uses that hard register (the compiled and retail instruction lists aligned on
opcodes / immediates, register operands paired over the equal runs; `s1 (s2 x3)` when they disagree), and the
pseudos whose register differs are listed with the priority they would need: local-alloc / global-alloc hand
the free registers out in priority order (a call-crossing pseudo takes the first free saved register, s0 up), so
a pseudo retail keeps in a lower saved register than ours needs a priority above the pseudo that got that one.

docs/STATUS.md "Register priority": wrapping a statement in `do { } while (0)` counts its refs more; the order of
declarations and a copy into a new variable change refs / live lengths (tools/regswap.py tries those).
"""
import argparse, math, os, re, shutil, subprocess, sys, tempfile

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))
import cc

HARD = {0: "zero", 1: "at", 2: "v0", 3: "v1", 4: "a0", 5: "a1", 6: "a2", 7: "a3", 24: "t8", 25: "t9", 28: "gp",
        29: "sp", 30: "fp", 31: "ra", 64: "hi", 65: "lo"}
HARD.update({8 + i: "t%d" % i for i in range(8)})
HARD.update({16 + i: "s%d" % i for i in range(8)})
REG = re.compile(r"^Register (\d+) used (\d+) times across (\d+) insns(?: in block (\d+))?(?:; crosses (\d+) calls?)?")


def sections(text):
    """{function name: text} of a dump file."""
    out = {}
    for m in re.finditer(r"^;; Function (\w+)\n(.*?)(?=^;; Function |\Z)", text, re.M | re.S):
        out[m.group(1)] = m.group(2)
    return out


def var_names(src, func):
    """parameter and local names of func's definition, in declaration order."""
    t = open(src).read()
    m = re.search(r"(?m)^[^\n;#]*\b%s\s*\(([^)]*)\)((?:\s*[^;{}()=#]+;)*)\s*\{" % re.escape(func), t)
    if not m:
        return []
    names = []
    if m.group(2).strip():     # K&R: the parameter list itself gives the order
        names += [x.strip() for x in m.group(1).split(",") if x.strip()]
    else:
        for p in m.group(1).split(","):
            pm = re.search(r"([A-Za-z_]\w*)\s*(?:\[[^\]]*\])?\s*$", p)
            if pm and pm.group(1) != "void":
                names.append(pm.group(1))
    body = t[m.end():]
    depth, i = 1, 0
    while i < len(body) and depth:
        depth += {"{": 1, "}": -1}.get(body[i], 0)
        i += 1
    for d in re.finditer(r"(?m)^\s+(?:(?:register|volatile|const|unsigned|signed|struct\s+\w+|union\s+\w+|"
                         r"[A-Za-z_]\w*)\s+)+\**\s*([A-Za-z_]\w*)\s*(?:\[[^\]]*\])*\s*(?:=[^;]*)?;", body[:i]):
        if d.group(1) not in names and d.group(0).split()[0] not in ("return", "goto", "case", "else"):
            names.append(d.group(1))
    return names


def retail_regs(src, func, prog, over):
    """{our hard register number: Counter of retail register numbers} over the aligned instructions of func, or
    None when it has no retail bytes."""
    import collections, difflib, struct
    import ccheck, inlined, nearcopy
    try:
        binary, delta, syms = ccheck.prog_info(prog)
    except Exception:
        return None
    sizes = ccheck.retail_sizes(prog)
    addr = syms.get(func) or (int(func[5:], 16) if re.fullmatch(r"func_[0-9A-Fa-f]{8}", func) else None)
    if addr is None or func not in sizes:
        return None
    want = binary[addr - delta: addr - delta + sizes[func]]
    d = tempfile.mkdtemp(prefix="tmp_prio_", dir=os.path.join(ROOT, "build"))
    try:
        cc.compile_c(src, d + "/a.o", over)
        diffs, ours, size = nearcopy.compare(d + "/a.o", func, want)
    except cc.CompileError:
        return None
    finally:
        shutil.rmtree(d, ignore_errors=True)
    if diffs is None:
        return None

    def dec(b):
        out = []
        for (w,) in struct.iter_unpack("<I", b[:len(b) // 4 * 4]):
            k, rg = inlined.regs(w)
            op = w >> 26
            if 1 <= op <= 7 or op in (2, 3):
                k = k[:2] if op == 1 else (op,)
            out.append((k, rg))
        return out
    a, b = dec(ours), dec(want)
    sm = difflib.SequenceMatcher(None, [x[0] for x in a], [x[0] for x in b], autojunk=False)
    cnt = collections.defaultdict(collections.Counter)
    for i, j, n in sm.get_matching_blocks():
        for k in range(n):
            for x, y in zip(a[i + k][1], b[j + k][1]):
                if x or y:
                    cnt[x][y] += 1
    return cnt


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("src")
    ap.add_argument("func", nargs="?")
    ap.add_argument("--cc")
    ap.add_argument("--flags")
    ap.add_argument("--all", action="store_true", help="also the insns that set each pseudo")
    ap.add_argument("--prog", default="main", help="the program whose retail bytes give the `retail` column")
    a = ap.parse_args()
    over = {k: v for k, v in (("cc", a.cc), ("flags", a.flags)) if v}
    o = cc.options(a.src, over)
    gcc = os.path.join(cc.OLDGCC, o["cc"])
    inc = os.path.join(ROOT, "include")
    d = tempfile.mkdtemp(prefix="tmp_prio_", dir=os.path.join(ROOT, "build"))
    try:
        subprocess.run([gcc + "/cpp", "-undef", "-D__GNUC__=2", "-DMIPSEL", "-D_LANGUAGE_C", "-I" + inc,
                        "-I" + inc + "/psyq", os.path.abspath(a.src), d + "/x.i"], check=True)
        r = subprocess.run([gcc + "/cc1", "-quiet", "-w", "-funsigned-char"] + o["flags"].split() +
                           ["-dl", "-dg", "x.i", "-o", "x.s"], cwd=d, capture_output=True, text=True)
        if r.returncode:
            sys.exit("cc1 failed:\n" + r.stderr[-2000:])
        lreg = sections(open(d + "/x.i.lreg").read())
        greg = sections(open(d + "/x.i.greg").read())
    finally:
        shutil.rmtree(d, ignore_errors=True)
    func = a.func or list(lreg)[-1]
    if func not in lreg:
        sys.exit("no %s in the dumps (functions: %s)" % (func, " ".join(lreg)))
    lt, gt = lreg[func], greg.get(func, "")
    disp = {}
    dm = re.search(r";; Register dispositions:\n(.*?)\n\n", gt, re.S)
    for x, h in re.findall(r"(\d+) in (\d+)", dm.group(1) if dm else ""):
        disp[int(x)] = int(h)
    # local-alloc's choices are in the lreg dump's insns (hard registers already substituted in greg's)
    rows = []
    for l in lt.split("\n"):
        m = REG.match(l)
        if not m:
            continue
        n, refs, live = int(m.group(1)), int(m.group(2)), int(m.group(3))
        pr = (int(math.log2(refs)) if refs > 0 else 0) * refs / max(live, 1)
        rows.append((n, refs, live, m.group(4), int(m.group(5) or 0), pr, l))
    uservars = sorted({int(x) for x in re.findall(r"\(reg/v:\w+ (\d+)\)", lt)})
    names = dict(zip(uservars, var_names(a.src, func)))
    rr = retail_regs(a.src, func, a.prog, over)
    print("%s: %d pseudos (%s, %s)%s" % (func, len(rows), o["cc"], o["flags"],
                                        "" if rr is not None else " (no retail bytes for the retail column)"))
    print("%6s %-12s %5s %5s %-8s %6s %8s  %-8s %s" % ("pseudo", "variable?", "refs", "live", "scope", "calls",
                                                       "priority", "hard reg", "retail" if rr is not None else ""))
    wrong = []
    ranked = sorted(rows, key=lambda r: -r[5])
    for n, refs, live, blk, calls, pr, l in ranked:
        h = disp.get(n)
        col = ""
        if rr is not None and h is not None and h in rr:
            c = rr[h].most_common()
            col = HARD.get(c[0][0], str(c[0][0])) + ("" if len(c) == 1 else " (" + ", ".join(
                "%s x%d" % (HARD.get(r, str(r)), k) for r, k in c[1:3]) + ")")
            if c[0][0] != h:
                wrong.append((n, h, c[0][0], pr, calls))
        print("%6d %-12s %5d %5d %-8s %6d %8.3f  %-8s %s" % (n, names.get(n, ""), refs, live,
                                                           "block %s" % blk if blk is not None else "global", calls,
                                                           pr, HARD.get(h, "-" if h is None else str(h)), col))
        if a.all:
            for im in re.finditer(r"\(insn \d+ \d+ \d+ \(set \(reg[/\w]*:\w+ %d\)\s*(.*?)\)\n" % n, lt):
                print("         = %s" % " ".join(im.group(1).split())[:100])
    if wrong:
        print("register differences (ours -> retail) and what would give retail's choice:")
        byhard = {}
        for n, refs, live, blk, calls, pr, l in rows:
            if disp.get(n) is not None:
                byhard.setdefault(disp[n], []).append((pr, n))
        for n, h, want, pr, calls in wrong:
            other = sorted(byhard.get(want, []), reverse=True)
            hint = ""
            if other:
                op, on = other[0]
                hint = "; %s is held by pseudo %d%s (priority %.3f): %s" % (
                    HARD.get(want, want), on, " (%s)" % names[on] if on in names else "", op,
                    "raise %d above it (more refs: a do { } while (0) wrap, a shorter live range: a copy into a new "
                    "local) or lower that one" % n if op >= pr else
                    "it already ranks below: the choice comes from conflicts / ties (declaration order, a copy of "
                    "a parameter)")
            print("  pseudo %d%s: %s -> %s%s" % (n, " (%s)" % names[n] if n in names else "", HARD.get(h, h),
                                                 HARD.get(want, want), hint))


if __name__ == "__main__":
    main()

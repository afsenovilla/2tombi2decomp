#!/usr/bin/env python3
"""NPC actor state machines: find them and draft them in the skeleton the matched ones share.

  python3 -I tools/npcsm.py --list [PROG ...] [--all]
  python3 -I tools/npcsm.py PROG NAME [NAME ...] [--out DIR] [--install]

The skeleton (AGENTS.md "Round 10 forms"; about 90 matched in a04-a08 by round 10):

    void f(u8 *a)
    {
        switch (a[4]) {
        case 0:              init: f_InitializeMultiPartActorModel (func_800519E0) / f_InitializeSinglePartActorModel
                             (func_80051B70) / f_InitializeActorScript (func_80040CDC), then a list of stores, a[4]++
        case 1:              the work: often a sub-switch on a[0x5E] / a[3] / a[5], closed by one of the model
                             transform updaters (func_800517F8 / func_80051844 / func_800518FC), a[0x2B] = 0
        case 2: break;
        case 3: f_ResolveEffectEightByteStreamPayload (func_8007A624)
        }
    }

--list: every pending function (still INCLUDE_ASM) of the programs (all by default) whose asm calls func_8007A624 and
one of the three init functions; `skel` = it also switches on byte 4 of its first argument at the top (an
`lbu $x, 0x4($a0)` among its first instructions); `upd` = the transform updater it calls; per-program counts.
--all also lists the pending callers of func_8007A624 without an init call (other actor kinds).

PROG NAME: build/npcsm/<prog>/<name>.c, m2c's draft rewritten into the skeleton (arg0 -> `u8 *a`, M2C_FIELD on it ->
`a[K]` / `*(T *)(a + K)`, `switch (a[4])` without the temporary, `a[4]++`, m2c's `case 3: ... /* fallthrough */
case 2: return;` kept and also tried as `case 2: break; case 3: ...; break;`), each variant ccheck'd and the best kept
(the others as <name>.alt<N>.c). A draft at most --perm-max (40) words off then gets tools/permlines.py over the plain
stores of case 0 (--perm-seconds 60; --no-perm skips it): retail's store order is the scheduler's, not m2c's (a0f
func_801183C8 went 6 -> 0 this way). --install runs tools/install_c.py on every draft that matches (build-checked).
"""
import argparse, collections, glob, os, re, subprocess, sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))

OUT = os.path.join(ROOT, "build", "npcsm")
CLOSE = "func_8007A624"
INIT = ("func_800519E0", "func_80051B70", "func_80040CDC")
UPD = ("func_800517F8", "func_80051844", "func_800518FC")


def progs_list():
    return sorted(os.path.basename(y)[:-5] for y in glob.glob(os.path.join(ROOT, "config", "*.yaml")))


def pending(prog):
    out = set()
    for f in glob.glob(os.path.join(ROOT, "src", prog, "*.c")):
        out |= set(re.findall(r'INCLUDE_ASM\("[^"]*",\s*(\w+)\)', open(f, errors="replace").read()))
    return out


def asm_files(prog):
    return {os.path.basename(s)[:-2]: s for s in
            glob.glob(os.path.join(ROOT, "asm", prog, "nonmatchings", "**", "*.s"), recursive=True)}


def info(path):
    t = open(path).read()
    ins = re.findall(r"/\* \w+ ([0-9A-F]{8}) [0-9A-F]{8} \*/\s+(\w+)\s*([^\n]*)", t)
    jals = [o.strip() for _, m, o in ins if m == "jal"]
    # the state byte: lbu $x, 0x4($a0) (or of the saved copy of a0) within the first 12 instructions
    copies = {"$a0"}
    skel = False
    for _, m, o in ins[:12]:
        mm = re.match(r"(\$\w+), \$a0, \$zero$", o)
        if m in ("addu", "or", "move") and mm:
            copies.add(mm.group(1))
        mm = re.match(r"\$\w+, 0x4\((\$\w+)\)$", o)
        if m == "lbu" and mm and mm.group(1) in copies:
            skel = True
    return {"size": len(ins) * 4, "jals": jals, "skel": skel, "addr": int(ins[0][0], 16) if ins else 0}


def listing(progs, every):
    rows = []
    for p in progs:
        pend = pending(p)
        for n, s in asm_files(p).items():
            if n not in pend:
                continue
            i = info(s)
            if CLOSE not in i["jals"]:
                continue
            init = [j for j in INIT if j in i["jals"]]
            if not init and not every:
                continue
            rows.append((p, n, i, init))
    rows.sort(key=lambda r: (r[0], r[2]["size"]))
    print("%-4s %-48s %6s %-4s %-30s %s" % ("prog", "name", "size", "skel", "init", "upd"))
    for p, n, i, init in rows:
        upd = [u for u in UPD if u in i["jals"]]
        print("%-4s %-48s %#6x %-4s %-30s %s" % (p, n, i["size"], "yes" if i["skel"] else "-",
                                                ",".join(init) or "-", ",".join(upd) or "-"))
    c = collections.Counter(r[0] for r in rows)
    cs = collections.Counter(r[0] for r in rows if r[2]["skel"])
    print("\n%d candidates (%d with the a[4] switch at the top), %#x bytes:" %
          (len(rows), sum(cs.values()), sum(r[2]["size"] for r in rows)))
    print("  " + ", ".join("%s %d/%d" % (p, cs[p], c[p]) for p in sorted(c)))
    return rows


# ---------------------------------------------------------------- drafting

def m2c(prog, name):
    import statemachine as SM
    return SM.m2c_body(prog, name)


def field(t, off, base="a"):
    t = t.strip()
    if t == "u8 *":
        return "%s[%s]" % (base, off)
    return "*(%s)(%s + %s)" % (t, base, off)


def skeletonise(body, name):
    """m2c's draft -> the skeleton's spelling. Returns the function text and its extern lines."""
    m = re.search(r"(?m)^[A-Za-z_][\w \*]*?\b%s\s*\(([^)]*)\)\s*\{" % re.escape(name), body)
    pre, fn = body[:m.start()], body[m.start():]
    params = [x.strip() for x in m.group(1).split(",")] if m.group(1).strip() not in ("", "void") else []
    ret = re.match(r"([\w \*]*?)\s*\b%s\s*\(" % re.escape(name), fn).group(1).strip()
    if not params:
        return pre, fn
    newp = ["u8 *a"] + ["%s" % x for x in params[1:]]
    fn = fn[fn.index("{"):]
    fn = re.sub(r"\barg0\b", "a", fn)
    # M2C_FIELD(a, T *, K) -> a[K] / *(T *)(a + K), loads and stores
    fn = re.sub(r"M2C_FIELD\(a, ([\w ]+\*), (0x[0-9A-Fa-f]+|\d+)\)", lambda mm: field(mm.group(1), mm.group(2)), fn)
    # the state temporary
    mm = re.search(r"(?m)^    (\w+) = a\[4\];\n    switch \(\1\) \{[^\n]*\n", fn)
    if mm:
        v = mm.group(1)
        fn = fn[:mm.start()] + "    switch (a[4]) {\n" + fn[mm.end():]
        if not re.search(r"\b%s\b" % v, fn[fn.index("switch"):]):
            fn = re.sub(r"(?m)^    [\w ]+\*?\s*%s;\n\n?" % v, "", fn, count=1)
    fn = re.sub(r"switch \(a\[4\]\) \{[^\n]*", "switch (a[4]) {", fn)
    fn = re.sub(r"\ba\[4\] = \(u8\) \(a\[4\] \+ 1\);", "a[4]++;", fn)
    fn = re.sub(r"\ba\[4\] = a\[4\] \+ 1;", "a[4]++;", fn)
    fn = re.sub(r"\(u8\) \(a\[(\w+)\] \+ 1\)", r"a[\1] + 1", fn)
    fn = re.sub(r"\s*/\* irregular \*/", "", fn)
    fn = re.sub(r"\(void \*\) a\b", "a", fn)
    head = "%s %s(%s)\n" % (ret or "void", name, ", ".join(newp))
    return pre, head + fn


def asm_lines(prog, name):
    import decomp
    t = open(decomp.find_asm(prog, name)).read()
    return re.findall(r"/\* \w+ [0-9A-F]{8} [0-9A-F]{8} \*/\s+(\w+)\s*([^\n]*)", t)


LOADT = {"lb": "s8", "lbu": "u8", "lh": "s16", "lhu": "u16", "lw": "s32", "sb": "u8", "sh": "s16", "sw": "s32"}


def fix_void_derefs(fn, ins):
    """m2c's `*(void *)0x1F800160` (a scratchpad word it could not type) -> the width of the asm's access."""
    def rep(mm):
        ad = mm.group(1)
        for m_, o in ins:
            if "(%s & 0xFFFF)" % ad in o and m_ in LOADT:
                return "*(%s *)%s" % (LOADT[m_], ad)
        return "*(s32 *)%s" % ad
    return re.sub(r"\*\(void \*\)(0x[0-9A-Fa-f]+)", rep, fn)


def scratch_syms(fn, ins):
    """`*(T *)0x1F80xxxx` -> the linker's D_1F80XXXX (config/scratchpad.ld: retail has relocations there);
    returns (fn, extern lines)."""
    ext = {}

    def rep(mm):
        t, ad = mm.group(1), int(mm.group(2), 16)
        n = "D_%08X" % ad
        ext[n] = "extern %s %s;" % (t, n)
        return n
    fn = re.sub(r"\*\((\w+) \*\)(0x1[Ff]80[0-9A-Fa-f]{4})\b", rep, fn)
    return fn, sorted(ext.values())


def global_bases(fn):
    """M2C_FIELD(&D_X, T *, K) used twice or more -> a `u8 *gN = (u8 *)&D_X;` local set right before the first
    statement using it (retail keeps the base in a register and loads at offsets)."""
    names = re.findall(r"M2C_FIELD\(&(D_\w+), [\w ]+\*, (?:0x[0-9A-Fa-f]+|\d+)\)", fn)
    multi = [n for n in dict.fromkeys(names) if names.count(n) > 1]
    if not multi:
        return None
    lines = fn.split("\n")
    decls = []
    for k, n in enumerate(multi):
        g = "g" if len(multi) == 1 else "g%d" % k
        decls.append("    u8 *%s;" % g)
        first = next(i for i, l in enumerate(lines) if "M2C_FIELD(&%s," % n in l)
        ind = re.match(r"\s*", lines[first]).group(0)
        lines.insert(first, "%s%s = (u8 *)&%s;" % (ind, g, n))
        lines = [re.sub(r"M2C_FIELD\(&%s, ([\w ]+\*), (0x[0-9A-Fa-f]+|\d+)\)" % n,
                        lambda mm: field(mm.group(1), mm.group(2), g), l) for l in lines]
    i = next(i for i, l in enumerate(lines) if l == "{")
    lines[i + 1:i + 1] = decls + ([""] if not lines[i + 1].startswith("    ") or "switch" in lines[i + 1] else [])
    return "\n".join(lines)


def segments(fn):
    """the top-level `switch (a[4])` cut into [labels, lines] (None when the shape is not found)."""
    lines = fn.split("\n")
    try:
        i = next(k for k, l in enumerate(lines) if l == "    switch (a[4]) {")
        j = next(k for k in range(i + 1, len(lines)) if lines[k] == "    }")
    except StopIteration:
        return None
    segs = []
    for l in lines[i + 1:j]:
        mm = re.match(r"    (case (\w+):|default:)$", l)
        if mm:
            lab = mm.group(2) if mm.group(2) else "default"
            if segs and not segs[-1][1]:
                segs[-1][0].append(lab)
            else:
                segs.append([[lab], []])
        elif segs:
            segs[-1][1].append(l)
        else:
            return None
    return lines[:i + 1], segs, lines[j:]


def ends(body):
    return bool(body) and body[-1].strip() in ("return;", "break;") and body[-1].startswith("        ") and \
        not body[-1].startswith("         ")


def subst_regs(seg_labels, body, unassigned, ins):
    """an m2c temporary never assigned (a register set in the dispatch head): the state byte -> the case's value,
    a constant `addiu $r, $zero, K` of the head -> K."""
    head = ins[:16]
    out = body
    for v in unassigned:
        mm = re.match(r"(?:temp|var)_(\w\d)", v)
        if not mm:
            continue
        reg = "$" + mm.group(1)
        val = None
        for m_, o in head:
            if m_ == "lbu" and re.match(r"\%s, 0x4\(" % reg, o) and len(seg_labels) == 1 and \
                    seg_labels[0].isdigit():
                val = seg_labels[0]
            mk = re.match(r"\%s, \$zero, (-?0x[0-9A-Fa-f]+|-?\d+)$" % reg, o)
            if m_ == "addiu" and mk:
                val = str(int(mk.group(1), 0))
        if val is not None:
            out = [re.sub(r"\b%s\b" % v, val, l) for l in out]
    return out


def restructure(fn, ins):
    """the skeleton's case order 0, 1, 2, 3 with `break;` ends; m2c's fall-through into the empty case 2 -> break;
    never-assigned temporaries replaced by their value; nested `return;` kept."""
    cut = segments(fn)
    if not cut:
        return None
    pre, segs, post = cut
    decl = "\n".join(pre)
    whole = fn
    unassigned = [v for v in re.findall(r"(?m)^    [\w ]+?\*?\s*(\w+);$", decl)
                  if not re.search(r"\b%s\s*=[^=]" % v, whole)]
    empty = [s for s in segs if all(l.strip() in ("", "return;", "break;") for l in s[1])]
    out = []
    order = []
    for k, (labs, body) in enumerate(segs):
        body = subst_regs(labs, body, unassigned, ins)
        if not ends(body):
            nxt = segs[k + 1] if k + 1 < len(segs) else None
            if nxt is None or nxt in empty:
                body = body + ["        break;"]
        elif body[-1].strip() == "return;":
            body = body[:-1] + ["        break;"]
        body = [re.sub(r"        /\* fallthrough \*/$", "", l) for l in body]
        body = [l for l in body if l != ""]
        if all(l.strip() in ("break;",) for l in body):
            body = ["        break;"]
        order.append((labs, body))
    # empty segments merged: one `case K: break;` per label, in numeric order after the non-empty ones that
    # precede them in value; fall-throughs between non-empty segments keep their order
    full = []
    for labs, body in order:
        if body == ["        break;"]:
            for l in labs:
                full.append(([l], body))
        else:
            full.append((labs, body))

    def key(x):
        try:
            return int(x[0][0], 0)
        except ValueError:
            return 1 << 30
    # keep chains (a segment that falls into the next) together
    chains, cur = [], []
    for labs, body in full:
        cur.append((labs, body))
        if ends(body):
            chains.append(cur)
            cur = []
    if cur:
        chains.append(cur)
    chains.sort(key=lambda c: key(c[0]))
    for c in chains:
        for labs, body in c:
            out += ["    %s" % ("default:" if l == "default" else "case %s:" % l) for l in labs] + body
    res = "\n".join(pre + out + post)
    # declarations left unused
    for v in unassigned:
        if not re.search(r"\b%s\b" % v, "\n".join(out)):
            res = re.sub(r"(?m)^    [\w ]+?\*?\s*%s;\n" % v, "", res, count=1)
    return re.sub(r"\{\n\n(    switch)", r"{\n\1", res)


def case23(fn):
    """m2c's `case 3: X; /* fallthrough */ case 2: return;` at the top level -> `case 2: break; case 3: X; break;`"""
    mm = re.search(r"(?ms)^    case 3:\n(.*?)        /\* fallthrough \*/\n    case 2:\n        return;\n", fn)
    if not mm:
        return None
    return fn[:mm.start()] + "    case 2:\n        break;\n    case 3:\n" + mm.group(1) + "        break;\n" + \
        fn[mm.end():]


def returns_to_breaks(fn):
    """`return;` at the case level of the top switch -> `break;` (same code: the switch ends the function)."""
    return re.sub(r"(?m)^        return;$", "        break;", fn)


def check(path, prog, name):
    r = subprocess.run([sys.executable, "-I", os.path.join(ROOT, "tools", "ccheck.py"), path, "--prog", prog,
                        "--func", name], capture_output=True, text=True, cwd=ROOT)
    out = (r.stdout + r.stderr).strip().splitlines()
    last = [l for l in out if re.match(r"(OK|DIFF|MISSING|compile|error)", l)] or out[-1:] or ["?"]
    last = last[-1]
    if last.startswith("OK"):
        return 0, last
    mm = re.search(r"score (\d+)", last) or re.search(r"(\d+) words? differ", last)
    return (int(mm.group(1)) if mm else 10 ** 6), last


def draft(prog, name, out_dir):
    import nearcopy as N
    body = m2c(prog, name)
    if not body:
        return None, "m2c failed"
    pre, fn = skeletonise(body, name)
    tp = N.Prog(prog)
    ins = asm_lines(prog, name)
    fn = fix_void_derefs(fn, ins)
    fn, ext = scratch_syms(fn, ins)
    pre = pre.rstrip() + "\n" + "".join(e + "\n" for e in ext if e not in pre)
    top = N.PRELUDE + "".join(i + "\n" for i in tp.includes) + "\n" + pre.strip() + "\n\n"
    variants = []
    r = restructure(fn, ins)
    if r:
        g = global_bases(r)
        if g:
            variants.append(g)
        variants.append(r)
    variants += [fn, returns_to_breaks(fn)]
    for v in list(variants):
        c = case23(v)
        if c:
            variants.append(c)
    seen, uniq = set(), []
    for v in variants:
        if v not in seen:
            seen.add(v)
            uniq.append(v)
    os.makedirs(os.path.join(out_dir, prog), exist_ok=True)
    out = os.path.join(out_dir, prog, name + ".c")
    scored = []
    for k, v in enumerate(uniq):
        open(out, "w").write(top + v.strip() + "\n")
        sc = check(out, prog, name)
        scored.append((sc[0], k, v, sc[1]))
        if sc[0] == 0:
            break
    scored.sort(key=lambda x: (x[0], x[1]))
    for f in glob.glob(os.path.join(out_dir, prog, name + ".alt*.c")):
        os.remove(f)
    hdr = "/* tools/npcsm.py draft of %s (%s): %s */\n" % (name, prog, scored[0][3])
    open(out, "w").write(hdr + top + scored[0][2].strip() + "\n")
    for j, s in enumerate(scored[1:], 1):
        open(os.path.join(out_dir, prog, "%s.alt%d.c" % (name, j)), "w").write(
            "/* tools/npcsm.py variant: %s */\n" % s[3] + top + s[2].strip() + "\n")
    return out, scored[0][3]


STORE = re.compile(r"^\s+(\*\(|a\[|M2C_FIELD\(a,)[^;]*\)?\s*[-+|&]?= [^;]*;$")


def perm_case0(path, prog, name, seconds):
    """tools/permlines.py over the plain stores of case 0 (the init's store list: retail's order is the
    scheduler's, not m2c's). Returns (score, best file) or None."""
    lines = open(path).read().split("\n")
    try:
        i = next(k for k, l in enumerate(lines) if l == "    switch (a[4]) {")
        j = next(k for k in range(i + 1, len(lines)) if re.match(r"    case 1:", lines[k]))
    except StopIteration:
        return None
    marked = 0
    for k in range(i, j):
        if STORE.match(lines[k]) and "func_" not in lines[k] and "a[4]" not in lines[k]:
            lines[k] += " //P"
            marked += 1
    if marked < 2:
        return None
    src = path[:-2] + ".perm.c"
    open(src, "w").write("\n".join(lines))
    r = subprocess.run([sys.executable, "-I", os.path.join(ROOT, "tools", "permlines.py"), src, name, "--prog",
                        prog, "--max-seconds", str(seconds)], capture_output=True, text=True, cwd=ROOT)
    mm = re.search(r"best: (\d+) words off \((.*)\)", r.stdout)
    if not mm:
        return None
    best = mm.group(2)
    if os.path.exists(best):
        open(best, "w").write(re.sub(r" //P$", "", open(best).read(), flags=re.M))
    return int(mm.group(1)), best


def install(path, prog):
    r = subprocess.run([sys.executable, "-I", os.path.join(ROOT, "tools", "install_c.py"), path, "--prog", prog],
                       capture_output=True, text=True, cwd=ROOT)
    return r.returncode == 0, (r.stdout + r.stderr).strip().splitlines()[-1:] or [""]


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--list", action="store_true")
    ap.add_argument("--all", action="store_true", help="with --list: also callers of func_8007A624 without init")
    ap.add_argument("--out", default=OUT)
    ap.add_argument("--install", action="store_true")
    ap.add_argument("--no-perm", dest="perm", action="store_false",
                    help="no tools/permlines.py pass over the case-0 stores of a near draft")
    ap.add_argument("--perm-max", type=int, default=40, help="permlines only for drafts at most this many words off")
    ap.add_argument("--perm-seconds", type=int, default=60)
    ap.add_argument("args", nargs="*")
    a = ap.parse_args()
    if a.list:
        listing(a.args or progs_list(), a.all)
        return
    if len(a.args) < 2:
        ap.error("PROG NAME [NAME ...] or --list")
    prog = a.args[0]
    names = a.args[1:]
    if names == ["ALL"]:
        pend = pending(prog)
        names = [n for n, s in sorted(asm_files(prog).items()) if n in pend and CLOSE in info(s)["jals"]
                 and any(j in info(s)["jals"] for j in INIT)]
    ok = 0
    for n in names:
        try:
            path, res = draft(prog, n, a.out)
        except Exception as e:
            print("%-40s draft failed: %s: %s" % (n, type(e).__name__, e))
            continue
        if not res.startswith("OK") and a.perm and path:
            mm = re.search(r"score (\d+)", res) or re.search(r"(\d+) words? differ", res)
            if mm and int(mm.group(1)) <= a.perm_max:
                pr = perm_case0(path, prog, n, a.perm_seconds)
                if pr and pr[0] == 0:
                    os.replace(pr[1], path)
                    res = "OK after permlines on the case-0 stores"
                elif pr:
                    res += " (permlines on the case-0 stores: %d, %s)" % (pr[0], os.path.relpath(pr[1], ROOT))
        line = "%-40s %s" % (n, res)
        if res.startswith("OK"):
            ok += 1
            if a.install:
                good, msg = install(path, prog)
                line += "  install: %s" % ("done" if good else "FAILED " + " ".join(msg))
        print(line + ("  -> %s" % os.path.relpath(path, ROOT) if path else ""), flush=True)
    print("%d / %d drafts match" % (ok, len(names)))


if __name__ == "__main__":
    main()

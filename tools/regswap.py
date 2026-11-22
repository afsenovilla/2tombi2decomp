#!/usr/bin/env python3
"""Register-swap search for near misses: source rewrites that change gcc's register choices but not the
statements, tried greedily on one function of a scratch file and scored by tools/ccheck.py score().

  python3 -I tools/regswap.py FILE.c FUNC [--prog main] [-j N] [--rounds 4] [--out FILE.regswap.c]
      [--only decl,split,reuse,fork,copy,wrap,temp] [--max-perm 720] [--pairs 6] [--install]

The rewrites (docs/STATUS.md "Register priority" / "Registers" recipes):
  - decl: the order of the local declarations at the top of the function body (every order when there are at
    most 6 lines (--max-perm), else every move of one line to another place); a line whose initialiser reads
    another local stays below it;
  - split: a store through a temporary (`*p = e;` -> `{ T t = e; *p = t; }`, T the type of a local of the same
    shape or s32 / s16 / u16 / u8);
  - reuse: one local replaced by another of the same declared type everywhere (its declaration dropped);
  - fork: a local assigned more than once gets a new variable from one of its later assignments on;
  - copy: a copy of a local (`x_c = x;` after its assignment) used in one later statement instead of it (retail
    `move a2,v0; move s4,a2`: one value in two registers);
  - wrap: one simple statement wrapped in `do { } while (0)` (more refs for its pseudos, no scheduling across);
  - temp: a parameter copied into a new local at the top and used through it.
Every round compiles every single rewrite of the current best text (in parallel) and keeps the best one while the
score goes down (when no single one helps, every second rewrite on top of the --pairs best first ones is tried
too); the best text so far is written to --out (default FILE.regswap.c) on every improvement, with a
`// regswap:` line listing what was applied. A match (score 0) is installed with --install (tools/install_c.py for
game code, tools/install_lib.py when the file has a `// CC` line).
"""
import argparse, concurrent.futures as cf, itertools, os, re, subprocess, sys, tempfile

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))
import ccheck

KEYWORDS = {"return", "if", "else", "for", "while", "do", "switch", "case", "default", "break", "continue", "goto",
            "sizeof"}
TYPEWORDS = {"s8", "u8", "s16", "u16", "s32", "u32", "int", "char", "short", "long", "unsigned", "signed", "void",
             "struct", "union", "volatile", "const", "register", "enum"}
DECL = re.compile(r"^(\s+)((?:(?:register|volatile|const|unsigned|signed|struct|union|enum)\s+)*[A-Za-z_]\w*)"
                  r"(\s+\**\s*|\s*\*+\s*)([A-Za-z_]\w*)\s*((?:\[[^\]]*\])*)\s*(=\s*[^;]*)?;\s*$")


def func_span(lines, func):
    """(index of the `{` line, index of the closing `}` line) of the definition of func."""
    text = "\n".join(lines)
    m = re.search(r"(?m)^[^\n;#]*\b%s\s*\([^;{]*\)(?:\s*[^;{}()=#]+;)*\s*\{" % re.escape(func), text)
    if not m:
        sys.exit("no definition of %s" % func)
    start = text.count("\n", 0, m.end())
    depth = 0
    for i in range(start, len(lines)):
        code = re.sub(r"//.*|\"(?:[^\"\\]|\\.)*\"|'(?:[^'\\]|\\.)*'", "", lines[i])
        depth += code.count("{") - code.count("}")
        if depth == 0 and i > start:
            return start, i
    sys.exit("no end of %s" % func)


def decls(lines, b, e):
    """[(line index, type text, name, pointer stars, array part, initialiser or '')] of the declarations at the
    top of the body (b: the `{` line)."""
    out = []
    i = b + 1
    while i < e:
        l = lines[i]
        if not l.strip():
            i += 1
            continue
        m = DECL.match(l)
        if not m or m.group(2).split()[0] in KEYWORDS or "," in l.split("=")[0]:
            break
        out.append((i, m.group(2), m.group(4), m.group(3).strip().replace(" ", ""), m.group(5), (m.group(6) or "")))
        i += 1
    return out


def params(lines, b, func):
    head = " ".join(lines[max(0, b - 3):b + 1])
    m = re.search(r"\b%s\s*\(([^)]*)\)" % re.escape(func), head)
    out = []
    if m:
        for p in m.group(1).split(","):
            pm = re.match(r"\s*(.*?)(\**)\s*([A-Za-z_]\w*)\s*$", p)
            if pm and pm.group(3) != "void" and pm.group(1).strip():
                out.append((pm.group(1).strip(), pm.group(2), pm.group(3)))
    return out


def sub_name(text, old, new):
    return re.sub(r"(?<![\w.>])\b%s\b" % re.escape(old), new, text)


def rewrites(text, func, only):
    """[(description, new text)] of every single rewrite of func in text."""
    lines = text.split("\n")
    b, e = func_span(lines, func)
    ds = decls(lines, b, e)
    names = [d[2] for d in ds]
    body_start = (ds[-1][0] + 1) if ds else b + 1
    out = []

    def join(ls):
        return "\n".join(ls)

    if "decl" in only and len(ds) >= 2:
        idx = [d[0] for d in ds]
        block = [lines[i] for i in idx]
        deps = {k: {j for j, d2 in enumerate(ds) if j != k and re.search(r"\b%s\b" % re.escape(d2[2]), ds[k][5])}
                for k in range(len(ds))}

        def ok(order):
            pos = {k: p for p, k in enumerate(order)}
            return all(pos[j] < pos[k] for k in deps for j in deps[k])
        orders = []
        if len(ds) <= 6:
            orders = [o for o in itertools.permutations(range(len(ds))) if list(o) != list(range(len(ds)))]
        else:
            for k in range(len(ds)):
                for p in range(len(ds)):
                    if p != k:
                        o = [x for x in range(len(ds)) if x != k]
                        o.insert(p, k)
                        orders.append(tuple(o))
        for o in orders[:MAX_PERM]:
            if not ok(o):
                continue
            ls = list(lines)
            for slot, k in zip(idx, o):
                ls[slot] = block[k]
            out.append(("decl order " + ",".join(ds[k][2] for k in o), join(ls)))
    if "reuse" in only:
        for (i1, t1, n1, s1, a1, _), (i2, t2, n2, s2, a2, init2) in itertools.permutations(ds, 2):
            if (t1, s1, a1) != (t2, s2, a2) or a1:
                continue
            ls = list(lines)
            if init2:      # its initialiser becomes an assignment of n1 below the declarations
                ls.insert(ds[-1][0] + 1, "%s%s %s;" % (re.match(r"\s*", lines[i2]).group(0), n1, init2.strip()))
            ls[i2] = None
            ls = [l for l in ls if l is not None]
            nb, ne = func_span(ls, func)
            for k in range(nb + 1, ne):
                ls[k] = sub_name(ls[k], n2, n1)
            out.append(("reuse %s for %s" % (n1, n2), join(ls)))
    if "fork" in only:
        for (i, t, n, s, a, init) in ds:
            if a:
                continue
            assigns = [k for k in range(body_start, e) if re.match(r"\s+%s\s*=(?!=)" % re.escape(n), lines[k])]
            if init:
                assigns = [i] + assigns
            for k in assigns[1:]:
                nn = n + "_f"
                ls = list(lines)
                for j in range(k, e):
                    ls[j] = sub_name(ls[j], n, nn)
                ls.insert(ds[-1][0] + 1, "%s%s %s%s;" % (re.match(r"\s*", lines[i]).group(0), t, s, nn))
                out.append(("fork %s at line %d" % (n, k - b), join(ls)))
    if "copy" in only:
        for (i, t, n, s, a, init) in ds:
            if a:
                continue
            assigns = [k for k in range(body_start, e) if re.match(r"\s+%s\s*=(?!=)" % re.escape(n), lines[k])]
            at = assigns[0] if assigns else (ds[-1][0] if init else None)
            if at is None:
                continue
            for j in range(at + 1, e):
                if not re.search(r"(?<![\w.>])\b%s\b" % re.escape(n), lines[j]) or \
                        re.match(r"\s+%s\s*=(?!=)" % re.escape(n), lines[j]):
                    continue
                ls = list(lines)
                ls[j] = sub_name(ls[j], n, n + "_c")
                ind = re.match(r"\s*", lines[at + 1] if at + 1 < e and lines[at + 1].strip() else lines[at]).group(0)
                ls.insert(at + 1, "%s%s_c = %s;" % (ind, n, n))
                ls.insert(ds[-1][0] + 1, "%s%s %s%s_c;" % (re.match(r"\s*", lines[i]).group(0), t, s, n))
                out.append(("copy %s for line %d" % (n, j - b), join(ls)))
    if "wrap" in only:
        for k in range(body_start, e):
            l = lines[k]
            st = l.strip()
            if not st.endswith(";") or st.startswith(("return", "break", "continue", "goto", "case", "default",
                                                      "do ", "}", "for", "while")) or DECL.match(l) and \
                    DECL.match(l).group(2).split()[0] not in KEYWORDS and not re.match(r"\s*\w+\s*=", l):
                continue
            if "//" in st or st.count(";") != 1:
                continue
            ind = l[:len(l) - len(l.lstrip())]
            ls = list(lines)
            ls[k] = "%sdo {\n%s    %s\n%s} while (0);" % (ind, ind, st, ind)
            out.append(("wrap line %d" % (k - b), join(ls)))
    if "split" in only:
        types = ["s32", "s16", "u16", "u8"]
        for k in range(body_start, e):
            l = lines[k]
            m = re.match(r"^(\s+)(.+?)\s*=(?!=)\s*(.+);\s*$", l)
            if not m or m.group(2).split()[0] in KEYWORDS or m.group(2) in names:
                continue
            lhs, rhs = m.group(2), m.group(3)
            if not re.search(r"[*\[.>]", lhs) and not re.match(r"[A-Za-z_]\w*$", lhs):
                continue
            if re.fullmatch(r"-?(0x[0-9A-Fa-f]+|\d+)|[A-Za-z_]\w*", rhs.strip()):
                continue
            ind = m.group(1)
            for t in types:
                ls = list(lines)
                ls[k] = "%s{\n%s    %s rs_t = %s;\n%s    %s = rs_t;\n%s}" % (ind, ind, t, rhs, ind, lhs, ind)
                out.append(("split line %d through %s" % (k - b, t), join(ls)))
    if "temp" in only:
        for t, s, n in params(lines, b, func):
            ls = list(lines)
            for j in range(b + 1, e):
                ls[j] = sub_name(ls[j], n, n + "_p")
            ins = ds[-1][0] + 1 if ds else b + 1
            ls.insert(ins, "    %s %s%s_p = %s;" % (t, s, n, n))
            out.append(("temp copy of parameter %s" % n, join(ls)))
    return out


MAX_PERM = 720


def main():
    global MAX_PERM
    ap = argparse.ArgumentParser()
    ap.add_argument("src")
    ap.add_argument("func")
    ap.add_argument("--prog", default="main")
    ap.add_argument("-j", type=int, default=os.cpu_count())
    ap.add_argument("--rounds", type=int, default=4)
    ap.add_argument("--out")
    ap.add_argument("--only", default="decl,split,reuse,fork,copy,wrap,temp")
    ap.add_argument("--max-perm", type=int, default=720)
    ap.add_argument("--install", action="store_true")
    ap.add_argument("--pairs", type=int, default=6, help="when no single rewrite helps, pairs on the N best (0: off)")
    a = ap.parse_args()
    MAX_PERM = a.max_perm
    only = set(a.only.split(","))
    out = a.out or re.sub(r"\.c$", "", a.src) + ".regswap.c"
    text = open(a.src).read()
    work = tempfile.mkdtemp(prefix="tmp_regswap_", dir=os.path.join(ROOT, "build"))
    d = os.path.dirname(os.path.abspath(a.src))

    def sc(t, k):
        # the candidate sits beside the scratch so its relative #include lines still resolve
        f = os.path.join(d, ".regswap_%d_%d.c" % (os.getpid(), k))
        open(f, "w").write(t)
        try:
            return ccheck.score(f, a.prog, a.func, work)
        finally:
            os.remove(f)
    try:
        best = sc(text, 0)
        if best is None:
            sys.exit("%s does not compile or has no %s" % (a.src, a.func))
        print("start: %d words off" % best, flush=True)
        applied = []
        for rnd in range(a.rounds):
            if best == 0:
                break
            cands = rewrites(text, a.func, only)
            with cf.ThreadPoolExecutor(a.j) as ex:
                scores = list(ex.map(lambda kv: sc(kv[1][1], kv[0] + 1), enumerate(cands)))
            ranked = sorted((s, i) for i, s in enumerate(scores) if s is not None)
            print("round %d: %d rewrites, best %s" % (rnd + 1, len(cands),
                  "%d (%s)" % (ranked[0][0], cands[ranked[0][1]][0]) if ranked else "-"), flush=True)
            pick = None
            if ranked and ranked[0][0] < best:
                pick = (ranked[0][0], [cands[ranked[0][1]][0]], cands[ranked[0][1]][1])
            elif a.pairs and ranked:
                # no single rewrite helps: a second rewrite on top of each of the --pairs best first ones
                firsts = [cands[i] for s, i in ranked[:a.pairs] if s <= best + 2]
                jobs = [(d1, d2, t2) for d1, t1 in firsts for d2, t2 in rewrites(t1, a.func, only)]
                with cf.ThreadPoolExecutor(a.j) as ex:
                    s2 = list(ex.map(lambda kv: sc(kv[1][2], kv[0] + 1), enumerate(jobs)))
                r2 = sorted((s, i) for i, s in enumerate(s2) if s is not None)
                print("round %d: %d pairs, best %s" % (rnd + 1, len(jobs), r2[0][0] if r2 else "-"), flush=True)
                if r2 and r2[0][0] < best:
                    d1, d2, t2 = jobs[r2[0][1]]
                    pick = (r2[0][0], [d1, d2], t2)
            if not pick:
                break
            best, text = pick[0], pick[2]
            applied += pick[1]
            open(out, "w").write("// regswap: %s (%d words off)\n" % ("; ".join(applied), best) + text)
        print("%s: %s -> %s" % (a.func, "MATCH" if best == 0 else "%d words off" % best,
                                os.path.relpath(out) if applied else "(nothing better)"))
        if best == 0 and a.install:
            tool = "install_lib.py" if re.search(r"(?m)^//\s*CC\s", text[:800]) else "install_c.py"
            r = subprocess.run([sys.executable, "-I", os.path.join(ROOT, "tools", tool), out, "--prog", a.prog],
                               capture_output=True, text=True, cwd=ROOT)
            print((r.stdout + r.stderr).strip().splitlines()[-1:])
    finally:
        subprocess.run(["rm", "-rf", work])


if __name__ == "__main__":
    main()

#!/usr/bin/env python3
"""Register-swap search for near misses: source rewrites that change gcc's register choices but not the
statements, tried greedily on one function of a scratch file and scored by tools/ccheck.py score().

  python3 -I tools/regswap.py FILE.c FUNC [--prog main] [-j N] [--rounds 4] [--out FILE.regswap.c]
      [--only decl,split,reuse,fork,copy,wrap,temp,load,const,member,volatile,goto,ternary,pathsplit,callres,abs]
      [--skip KIND,...] [--max-perm 720] [--pairs 6] [--max-cands 3000] [--max-seconds S] [--narrowing] [--install]

The rewrites (docs/STATUS.md "Register priority" / "Registers" recipes):
  - decl: the order of the local declarations at the top of the function body (every order when there are at
    most 6 lines (--max-perm), else every move of one line to another place); a line whose initialiser reads
    another local stays below it;
  - split: a store through a temporary (`*p = e;` -> `{ T t = e; *p = t; }`, T the type of a local of the same
    shape or s32 / s16 / u16 / u8); a T narrower than the store's target truncates the value: left out unless
    --narrowing (then flagged NARROWING), an unknown target type is flagged;
  - reuse: one local replaced by another of the same declared type everywhere (its declaration dropped);
  - fork: a local assigned more than once gets a new variable from one of its later assignments on;
  - copy: a copy of a local (`x_c = x;` after its assignment) used in one later statement instead of it (retail
    `move a2,v0; move s4,a2`: one value in two registers);
  - wrap: one simple statement, a run of two or three, or the span of one local's uses wrapped in
    `do { } while (0)` (more refs for its pseudos, no scheduling across; never around a break / continue / case);
  - temp: a parameter copied into a new local and used through it (`void f(u8 *a0) { u8 *a = a0; ...}`): each
    parameter alone, after the declarations or before them, and all parameters at once;
  - load: a read (field, array element, global, `*(T *)` / M2C_FIELD access) of a statement moved into a new
    local assigned just before the store one or two statements above it (`x = a[0x2E]; D = 0; a[0x2E] = x + t;`),
    or read at the top of the function when it only uses parameters and globals (loads first);
  - const: a literal as an early local (`s32 k = 3;` with the other declarations, or `k = 3;` just before its one
    use), each occurrence alone and all of one value, as s32 and as u8 / s16;
  - member: a cast access `*(T *)(p + o)` / `M2C_FIELD(p, T *, o)` as a struct member (`MEMBER_AT(T, p, o)` of include/common.h, the
    `S16F(p, o)` recipe: a non-QImode member never aliases a fixed scalar global) and back (a file macro of that
    form expanded to the cast);
  - volatile: one read made a volatile re-read (`*(volatile T *)&(e)`);
  - goto: a `goto L;` replaced by a copy of the code at L up to its return / break / goto (a duplicated tail
    instead of a shared one; the label goes when nothing jumps to it any more);
  - ternary: `x = c ? a : b;` / `return c ? a : b;` as if / else, and an if / else of two single assignments to
    one variable as a ternary;
  - pathsplit: a local assigned inside a nested block (an if arm, a case) renamed from there to the end of that
    block or case (one C variable per path where retail uses two registers);
  - callres: a call result stored through memory goes through an existing local that is dead there first
    (`p->x = f(a);` -> `v = f(a); p->x = v;`; the dead check is a forward scan: check loops by hand);
  - abs: `abs(E)` <-> `E < 0 ? -E : E` / `E >= 0 ? E : -E` / `__builtin_abs`, and `if (v < 0) v = -v;` -> abs.
Every round starts with the wrap and volatile rewrites; past --max-cands every kind gets its turn (round robin).
--max-seconds stops the search (the best text so far stays in --out).
Every round compiles every single rewrite of the current best text (in parallel) and keeps the best one while the
score goes down (when no single one helps, every second rewrite on top of the --pairs best first ones is tried
too); the best text so far is written to --out (default FILE.regswap.c) on every improvement, with a
`// regswap:` line listing what was applied. A match (score 0) is installed with --install (tools/install_c.py for
game code, tools/install_lib.py when the file has a `// CC` line).
"""
import argparse, collections, concurrent.futures as cf, itertools, os, re, subprocess, sys, tempfile

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
        if "," in l.split("=")[0] and multi_decl(l):
            i += 1
            continue                                    # `s32 a, b;`: multi_decl() / all_locals()
        m = DECL.match(l)
        if not m or m.group(2).split()[0] in KEYWORDS or "," in l.split("=")[0]:
            break
        out.append((i, m.group(2), m.group(4), m.group(3).strip().replace(" ", ""), m.group(5), (m.group(6) or "")))
        i += 1
    return out


def multi_decl(l):
    """[(type, name, stars, array)] of a declaration line with several declarators (`s32 a, *b, c[4];`), or []."""
    m = re.match(r"^\s+((?:(?:register|volatile|const|unsigned|signed|struct|union|enum)\s+)*[A-Za-z_]\w*)\s+"
                 r"([^;=(){}]+);\s*(//.*)?$", l)
    if not m or m.group(1).split()[0] in KEYWORDS:
        return []
    out = []
    for p in m.group(2).split(","):
        pm = re.match(r"\s*(\**)\s*([A-Za-z_]\w*)\s*((?:\[[^\]]*\])*)\s*$", p)
        if not pm:
            return []
        out.append((m.group(1), pm.group(2), pm.group(1), pm.group(3)))
    return out


def all_locals(lines, b, e, ds):
    """ds plus the names declared on multi-declarator lines at the top of the body (same tuple shape)."""
    out = list(ds)
    i = b + 1
    while i < e:
        l = lines[i]
        if not l.strip():
            i += 1
            continue
        md = multi_decl(l) if "," in l.split("=")[0] else []
        if md:
            out += [(i, t, n, s, a, "") for t, n, s, a in md]
        elif not DECL.match(l):
            break
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
    dsa = all_locals(lines, b, e, ds)
    names = [d[2] for d in dsa]
    body_start = max(d[0] for d in dsa) + 1 if dsa else b + 1
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
                ls.insert(body_start, "%s%s %s;" % (re.match(r"\s*", lines[i2]).group(0), n1, init2.strip()))
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
                ls.insert(body_start, "%s%s %s%s;" % (re.match(r"\s*", lines[i]).group(0), t, s, nn))
                out.append(("fork %s at line %d" % (n, k - b), join(ls)))
    if ("copy" in only or "keep" in only) and dsa:
        # a copy of a local (`x_c = x;` right after one of its assignments) used instead of it in later statements
        # that the copy dominates (same block or deeper, no case / label / loop back edge / reassignment between):
        # copy: one use; keep: every dominated use, or every one but the first (retail `move a0,v0`: the value
        # kept in its own register while the first one is reused)
        last_decl = body_start - 1
        for (i, t, n, s, a, init) in dsa:
            if a or re.search(r"&\s*%s\b" % re.escape(n), join(lines[body_start:e])):
                continue
            assigns = [k for k in range(body_start, e) if re.match(r"\s+%s\s*=(?!=)" % re.escape(n), lines[k])
                       and is_stmt(lines[k])]
            if init:
                assigns = [i] + assigns
            for at in assigns:
                uses = dominated_uses(lines, n, at, e)
                if not uses:
                    continue
                nn = "%s_c%d" % (n, at - b)
                if at < body_start:
                    continue                        # an initialised declaration: its copy would sit among them
                ind = indent(lines[at])
                sets = []
                if "copy" in only:
                    sets += [("copy %s (line %d) for line %d" % (n, at - b, j - b), [j]) for j in uses]
                if "keep" in only and len(uses) > 1:
                    sets += [("keep %s (line %d) in its own register for lines %d-%d" % (n, at - b, uses[0] - b,
                                                                                         uses[-1] - b), uses)]
                    sets += [("keep %s (line %d) in its own register for lines %d-%d (first use not)" % (
                        n, at - b, uses[1] - b, uses[-1] - b), uses[1:])]
                for desc, js in sets:
                    ls = list(lines)
                    for j in js:
                        ls[j] = sub_name(ls[j], n, nn)
                    ls.insert(at + 1, "%s%s = %s;" % (ind, nn, n))
                    ls.insert(last_decl + 1, "%s%s %s%s;" % (re.match(r"\s*", lines[i]).group(0), t, s, nn))
                    out.append((desc, join(ls)))
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
            lty = next((d[1] for d in ds if d[2] == lhs and not d[3].strip() and not d[4]), None) or \
                expr_type(lhs, text, lines, b, e)
            for t in types:
                # a temporary narrower than the target truncates the value: a different program, not a register
                # choice. Dropped unless --narrowing (then flagged); an unknown target type is flagged
                narrow = SIZES.get(t, 4) < SIZES.get(lty, 4) if lty in SIZES else None
                if narrow and not NARROWING:
                    continue
                ls = list(lines)
                ls[k] = "%s{\n%s    %s rs_t = %s;\n%s    %s = rs_t;\n%s}" % (ind, ind, t, rhs, ind, lhs, ind)
                out.append(("split line %d through %s%s" % (k - b, t, " (NARROWING: %s target, check it)" % lty
                                                           if narrow else "" if narrow is not None or t == "s32"
                                                           else " (target type unknown: check it does not truncate)"),
                            join(ls)))
    if "temp" in only:
        ps = params(lines, b, func)
        sets = [[p] for p in ps] + ([ps] if len(ps) > 1 else [])
        for group in sets:
            for where in ("after", "before"):
                if where == "before" and not ds:
                    continue
                ls = list(lines)
                for j in range(b + 1, e):
                    for t, s, n in group:
                        ls[j] = sub_name(ls[j], n, n + "_p")
                ins = body_start if where == "after" and ds else b + 1
                for t, s, n in reversed(group):
                    ls.insert(ins, "    %s %s%s_p = %s;" % (t, s, n, n))
                out.append(("temp copy of parameter%s %s%s" % ("s" if len(group) > 1 else "",
                                                               ",".join(g[2] for g in group),
                                                               " (first)" if where == "before" else ""), join(ls)))
    pnames = {p[2] for p in params(lines, b, func)}
    ins_decl = body_start if dsa else b + 1
    ind0 = re.match(r"\s*", lines[ds[0][0]]).group(0) if ds else "    "

    def with_decl(ls, decl, at=None):
        """ls with a declaration added at the end of the declarations (indices after it shift by one)."""
        ls = list(ls)
        ls.insert(ins_decl if at is None else at, ind0 + decl)
        return ls
    if "load" in only:
        stmts = [k for k in range(body_start, e) if is_stmt(lines[k])]
        n_out = 0
        for k in stmts:
            for (s0, s1, ex) in reads(lines[k]):
                ty = expr_type(ex, text, lines, b, e)
                ids = set(re.findall(r"[A-Za-z_]\w*", ex))
                # the statement(s) just above it at the same indentation that store through memory
                ind = indent(lines[k])
                prev = [j for j in range(k - 1, max(body_start, k - 4) - 1, -1)]
                for j in prev[:3]:
                    if not is_stmt(lines[j]) or indent(lines[j]) != ind:
                        break
                    if any(re.match(r"\s+%s\s*=(?!=)" % re.escape(x), lines[jj]) for x in ids
                           for jj in range(j, k)):
                        break                      # the read uses a variable set in between
                    if not is_store(lines[j]):
                        continue
                    nm = "rs_l%d" % n_out
                    ls = list(lines)
                    ls[k] = ls[k][:s0] + nm + ls[k][s1:]
                    ls.insert(j, "%s%s = %s;" % (ind, nm, ex))
                    ls = with_decl(ls, "%s %s;" % (ty, nm))
                    out.append(("load %s into a local before line %d" % (ex, j - b), join(ls)))
                    n_out += 1
                if ids and all(x in pnames or x not in names and not x[0].islower() or x in pnames or
                               x in ("u8", "s8", "u16", "s16", "u32", "s32", "M2C_FIELD") or re.match(r"D_\w+", x)
                               for x in ids if not re.fullmatch(r"(0x[0-9A-Fa-f]+|\d+)", x)) \
                        and not any(x in names for x in ids):
                    nm = "rs_l%d" % n_out
                    ls = list(lines)
                    ls[k] = ls[k][:s0] + nm + ls[k][s1:]
                    ls = with_decl(ls, "%s %s = %s;" % (ty, nm, ex))
                    out.append(("load %s at the top" % ex, join(ls)))
                    n_out += 1
    if "const" in only:
        occ = collections.defaultdict(list)
        for k in range(body_start, e):
            l = lines[k]
            if l.strip().startswith(("case ", "#")) or not l.strip():
                continue
            code = re.sub(r"//.*|/\*.*?\*/", "", l)
            for m in re.finditer(r"(?<![\w.\]])(-?)(0x[0-9A-Fa-f]+|\d+)\b(?![\w.])", code):
                if m.group(1) and re.search(r"[\w)\]]\s*$", code[:m.start()]):
                    continue                        # a binary minus
                if "[" in code[:m.start()] and DECL.match(l):
                    continue
                before = code[:m.start()].rstrip()
                if before.endswith(("M2C_FIELD(", "*,")) or re.search(r"M2C_FIELD\([^()]*,[^()]*\*\s*,\s*$", code[:m.start()]):
                    continue                        # a field offset
                v = int(m.group(2), 0) * (-1 if m.group(1) else 1)
                occ[v].append((k, m.start(), m.end()))
        n_out = 0
        for v, places in sorted(occ.items(), key=lambda kv: -len(kv[1]))[:24]:
            tys = ["s32"] + (["u8"] if 0 <= v < 256 else ["s16"] if -0x8000 <= v < 0x8000 else [])
            groups = [("all %d uses of %s" % (len(places), v), places)] if len(places) > 1 else []
            groups += [("use at line %d of %s" % (pl[0] - b, v), [pl]) for pl in places[:6]]
            for desc, pls in groups:
                for ty in tys:
                    nm = "rs_k%d" % n_out
                    n_out += 1
                    ls = list(lines)
                    for k, s0, s1 in sorted(pls, key=lambda x: (x[0], -x[1])):
                        ls[k] = ls[k][:s0] + nm + ls[k][s1:]
                    out.append(("const %s as an early %s local" % (desc, ty),
                                join(with_decl(ls, "%s %s = %s;" % (ty, nm, v)))))
                    if len(pls) == 1 and is_stmt(lines[pls[0][0]]):
                        ls2 = list(ls)
                        ls2.insert(pls[0][0], "%s%s = %s;" % (indent(lines[pls[0][0]]), nm, v))
                        out.append(("const %s as a %s local set just before" % (desc, ty),
                                    join(with_decl(ls2, "%s %s;" % (ty, nm)))))
    if "member" in only or "volatile" in only:
        macros = member_macros(text)
        allm = []
        for k in range(body_start, e):
            for s0, s1, ex, conv in casts(lines[k], macros):
                allm.append((k, s0, s1, ex, conv))
        if "member" in only:
            for k, s0, s1, ex, conv in allm:
                ls = list(lines)
                ls[k] = ls[k][:s0] + conv + ls[k][s1:]
                out.append(("member %s -> %s" % (ex, conv), add_member_macro(join(ls))))
            if len(allm) > 1:
                ls = list(lines)
                for k, s0, s1, ex, conv in sorted(allm, key=lambda x: (x[0], -x[1])):
                    ls[k] = ls[k][:s0] + conv + ls[k][s1:]
                out.append(("member: every cast access toggled", add_member_macro(join(ls))))
        if "volatile" in only:
            for k in range(body_start, e):
                if not is_stmt(lines[k]) and not re.match(r"\s*(if|while|switch)\b", lines[k]):
                    continue
                for s0, s1, ex in reads(lines[k]):
                    ty = expr_type(ex, text, lines, b, e)
                    ls = list(lines)
                    ls[k] = ls[k][:s0] + "*(volatile %s *)&(%s)" % (ty, ex) + ls[k][s1:]
                    out.append(("volatile re-read of %s at line %d" % (ex, k - b), join(ls)))
    if "goto" in only:
        for k in range(body_start, e):
            m = re.match(r"^(\s*)goto\s+(\w+);\s*$", lines[k])
            if not m:
                continue
            lab = [j for j in range(b, e) if re.match(r"^\s*%s:" % re.escape(m.group(2)), lines[j])]
            if not lab:
                continue
            tail = tail_block(lines, lab[0], e)
            if not tail or len(tail) > 16:
                continue
            base = min(indent(lines[j]) for j in tail if lines[j].strip()) if tail else ""
            ind = m.group(1)
            ls = list(lines)
            rep = []
            for j in tail:
                l = lines[j]
                if j == lab[0]:
                    l = re.sub(r"^\s*\w+:\s*", "", l)
                    if not l.strip():
                        continue
                    l = base + l
                rep.append(ind + l[len(base):] if l.startswith(base) else ind + l.strip())
            ls[k] = "\n".join(rep)
            txt = join(ls)
            if not re.search(r"\bgoto\s+%s\s*;" % re.escape(m.group(2)), txt):
                txt = re.sub(r"(?m)^(\s*)%s:\s*$\n?" % re.escape(m.group(2)), "", txt, count=1)
                txt = re.sub(r"(?m)^(\s*)%s:\s*" % re.escape(m.group(2)), r"\1", txt, count=1)
            out.append(("goto %s at line %d -> duplicated tail" % (m.group(2), k - b), txt))
    if "ternary" in only:
        for k in range(body_start, e):
            l = lines[k]
            m = re.match(r"^(\s*)(return\s+|[^=;?]+?=(?!=)\s*)(.+);\s*$", l)
            if m and "?" in m.group(3):
                tp = split_ternary(m.group(3))
                if tp:
                    c, x, y = tp
                    ind, lhs = m.group(1), m.group(2).rstrip()
                    if lhs.startswith("return"):
                        new = "%sif (%s) {\n%s    return %s;\n%s}\n%sreturn %s;" % (ind, c, ind, x, ind, ind, y)
                        new2 = "%sif (%s) {\n%s    return %s;\n%s} else {\n%s    return %s;\n%s}" % (
                            ind, c, ind, x, ind, ind, y, ind)
                        out.append(("ternary at line %d -> if / return" % (k - b), join(lines[:k] + [new] + lines[k + 1:])))
                        out.append(("ternary at line %d -> if / else return" % (k - b),
                                    join(lines[:k] + [new2] + lines[k + 1:])))
                    else:
                        new = "%sif (%s) {\n%s    %s %s;\n%s} else {\n%s    %s %s;\n%s}" % (
                            ind, c, ind, lhs, x, ind, ind, lhs, y, ind)
                        out.append(("ternary at line %d -> if / else" % (k - b), join(lines[:k] + [new] + lines[k + 1:])))
            # if (c) { v = x; } else { v = y; }  ->  v = c ? x : y;
            m = re.match(r"^(\s*)if \((.*)\) \{\s*$", l)
            if m and k + 4 < e:
                a1 = re.match(r"^\s*([A-Za-z_][\w\[\]\->.*]*?)\s*=(?!=)\s*(.+);\s*$", lines[k + 1])
                a2 = re.match(r"^\s*([A-Za-z_][\w\[\]\->.*]*?)\s*=(?!=)\s*(.+);\s*$", lines[k + 3])
                if a1 and a2 and lines[k + 2].strip() == "} else {" and lines[k + 4].strip() == "}" and \
                        a1.group(1) == a2.group(1):
                    new = "%s%s = (%s) ? %s : %s;" % (m.group(1), a1.group(1), m.group(2), a1.group(2), a2.group(2))
                    out.append(("if / else at line %d -> ternary" % (k - b), join(lines[:k] + [new] + lines[k + 5:])))
    if "pathsplit" in only:
        for (i, t, n, s, a, init) in ds:
            if a:
                continue
            for k in range(body_start, e):
                if not re.match(r"\s+%s\s*=(?!=)" % re.escape(n), lines[k]):
                    continue
                end = path_end(lines, k, e)
                if end is None or end <= k + 1 and not re.search(r"\b%s\b" % re.escape(n), lines[k].split("=", 1)[1]):
                    pass
                if end is None:
                    continue
                if not dead_after(lines, n, end, e):
                    continue                        # its value flows out of the path: renaming would change it
                nn = "%s_s%d" % (n, k - b)
                ls = list(lines)
                for j in range(k, end):
                    ls[j] = sub_name(ls[j], n, nn)
                ls.insert(body_start, "%s%s %s%s;" % (re.match(r"\s*", lines[i]).group(0), t, s, nn))
                out.append(("pathsplit %s from line %d to %d" % (n, k - b, end - b), join(ls)))
    if "wrap" in only:
        # a run of two or three simple statements, and the span of one local's uses (first to last mention, at one
        # indentation, braces balanced), in `do { } while (0)`; never around a break / continue / case (the
        # do-while would capture them)
        def wrappable(k1, k2):
            seg = lines[k1:k2 + 1]
            if indent(lines[k1]) != indent(lines[k2]) or any(
                    re.search(r"\b(break|continue)\s*;|^\s*(case\b|default\s*:)|^\s*\w+:\s*$|^\s*#", l)
                    for l in seg):
                return False
            depth = 0
            for l in seg:
                c = re.sub(r"//.*", "", l)
                depth += c.count("{") - c.count("}")
                if depth < 0:
                    return False
            return depth == 0 and not re.match(r"\s*(\}|else\b)", lines[k1]) and not \
                re.match(r"\s*else\b", lines[k2 + 1] if k2 + 1 < e else "")

        def wrapped(k1, k2):
            ind = indent(lines[k1])
            ls = list(lines)
            ls[k1:k2 + 1] = [ind + "do {"] + ["    " + l for l in lines[k1:k2 + 1]] + [ind + "} while (0);"]
            return join(ls)
        for k in range(body_start, e - 1):
            for n_ in (2, 3):
                k2 = k + n_ - 1
                if k2 < e and all(is_stmt(lines[j]) and indent(lines[j]) == indent(lines[k]) for j in range(k, k2 + 1)) \
                        and wrappable(k, k2):
                    out.append(("wrap lines %d-%d" % (k - b, k2 - b), wrapped(k, k2)))
        for (i, t, n, s_, a_, init) in ds:
            uses = [k for k in range(body_start, e) if re.search(r"(?<![\w.>])\b%s\b" % re.escape(n), lines[k])]
            if len(uses) >= 2 and uses[-1] - uses[0] < 40 and wrappable(uses[0], uses[-1]):
                out.append(("wrap the uses of %s (lines %d-%d)" % (n, uses[0] - b, uses[-1] - b),
                            wrapped(uses[0], uses[-1])))
    if "callres" in only:
        # a call's result stored through memory first goes into an existing local whose value is dead there
        # (`p->x = f(a);` -> `v = f(a); p->x = v;`): retail keeping the result in that local's register
        for k in range(body_start, e):
            m = re.match(r"^(\s+)(.+?)\s*=(?!=)\s*([A-Za-z_]\w*\s*\(.*\))\s*;\s*$", lines[k])
            if not m or m.group(3).split("(")[0].strip() in KEYWORDS or not is_stmt(lines[k]):
                continue
            lhs = m.group(2)
            for (i, t, n, s_, a_, init) in ds:
                if a_ or n == lhs or re.search(r"\b%s\b" % re.escape(n), m.group(3) + lhs) or \
                        not dead_after(lines, n, k + 1, e):
                    continue
                ls = list(lines)
                ls[k] = "%s%s = %s;\n%s%s = %s;" % (m.group(1), n, m.group(3), m.group(1), lhs, n)
                out.append(("call result of line %d through local %s" % (k - b, n), join(ls)))
    if "abs" in only:
        # abs(E) <-> E < 0 ? -E : E (and the >= / > / <= spellings, __builtin_abs)
        for k in range(body_start, e):
            l = lines[k]
            for m in re.finditer(r"\b(__builtin_abs|abs)\s*\(", l):
                end_ = balanced(l, m.end() - 1)
                if end_ is None:
                    continue
                x = l[m.end():end_ - 1]
                for desc, rep in (("ternary <", "((%s) < 0 ? -(%s) : (%s))" % (x, x, x)),
                                  ("ternary >=", "((%s) >= 0 ? (%s) : -(%s))" % (x, x, x)),
                                  ("other builtin", ("abs(%s)" if m.group(1) != "abs" else "__builtin_abs(%s)") % x)):
                    out.append(("abs at line %d as %s" % (k - b, desc), join(lines[:k] + [l[:m.start()] + rep +
                                                                                         l[end_:]] + lines[k + 1:])))
            for m in re.finditer(r"(\(\s*)?([A-Za-z_][\w\[\]\->.]*)\s*(<|<=|>=|>)\s*0\s*(\))?\s*\?\s*", l):
                if bool(m.group(1)) != bool(m.group(4)):
                    continue
                st = m.start()
                x = m.group(2).strip()
                rest = l[m.end():]
                pat = (r"\s*-\(?%s\)?\s*:\s*\(?%s\)?(?![\w\[])" if m.group(3) in ("<", "<=") else
                       r"\s*\(?%s\)?\s*:\s*-\(?%s\)?(?![\w\[])") % ((re.escape(x), re.escape(x)))
                mm = re.match(pat, rest)
                if not mm:
                    continue
                full_end = m.end() + mm.end()
                for desc, rep in (("abs()", "abs(%s)" % x), ("ternary <", "(%s < 0 ? -%s : %s)" % (x, x, x)),
                                  ("ternary >=", "(%s >= 0 ? %s : -%s)" % (x, x, x)),
                                  ("ternary >", "(%s > 0 ? %s : -%s)" % (x, x, x))):
                    nl = l[:st] + rep + l[full_end:]
                    if nl.count("(") == nl.count(")") and nl != l:
                        out.append(("abs ternary at line %d as %s" % (k - b, desc), join(lines[:k] + [nl] + lines[k + 1:])))
            m = re.match(r"^(\s*)if \(\s*([A-Za-z_]\w*)\s*<\s*0\s*\)\s*\{?\s*$", l)
            if m and k + 1 < e and re.match(r"^\s*%s\s*=\s*-\s*%s\s*;\s*$" % (m.group(2), m.group(2)), lines[k + 1]):
                close = 1 if l.rstrip().endswith("{") and k + 2 < e and lines[k + 2].strip() == "}" else 0
                if l.rstrip().endswith("{") and not close:
                    continue
                v = m.group(2)
                out.append(("if (%s < 0) %s = -%s at line %d as abs()" % (v, v, v, k - b),
                            join(lines[:k] + ["%s%s = abs(%s);" % (m.group(1), v, v)] + lines[k + 2 + close:])))
    if "callcopy" in only:
        # a call inside a bigger expression (`x = f(a) >> 12;`, `abs(f(a))`, `f(a) * k`) first copied into a local
        # (top-level or block-scoped): retail keeping the call result in its own register before the shift / abs
        n_out = 0
        for k in range(body_start, e):
            l = lines[k]
            if not is_stmt(l) and not re.match(r"\s*if \(", l):
                continue
            if re.match(r"\s*(\}\s*)?else\b", l):
                continue
            first = None
            for m in re.finditer(r"(?<![\w.>])([A-Za-z_]\w*)\s*\(", l):
                if m.group(1) in KEYWORDS or m.group(1) in TYPEWORDS or m.group(1) in ("M2C_FIELD", "MEMBER_AT") \
                        or re.fullmatch(r"[A-Z][A-Z0-9_]*", m.group(1)):
                    continue
                en = balanced(l, m.end() - 1)
                if en is None:
                    continue
                first = (m.start(), en)
                break
            if not first:
                continue
            s0, s1 = first
            call = l[s0:s1]
            before = l[:s0].rstrip()
            after = l[s1:].lstrip()
            if re.search(r"=\s*$", before) and after.startswith(";") or before.strip() == "" and after.startswith(";"):
                continue                            # already the whole right-hand side / a call statement
            nm = "rs_c%d" % n_out
            n_out += 1
            ind = indent(l)
            ls = list(lines)
            ls[k] = "%s%s = %s;\n%s" % (ind, nm, call, l[:s0] + nm + l[s1:])
            out.append(("callcopy of %s at line %d into a local" % (call.split("(")[0], k - b),
                        join(with_decl(ls, "s32 %s;" % nm))))
            if is_stmt(l):
                ls = list(lines)
                ls[k] = "%s{\n%s    s32 %s = %s;\n%s    %s\n%s}" % (ind, ind, nm, call, ind,
                                                                    (l[:s0] + nm + l[s1:]).strip(), ind)
                out.append(("callcopy of %s at line %d into a block-scoped local" % (call.split("(")[0], k - b),
                            join(ls)))
    if "barrier" in only:
        # an empty `__asm__ volatile("");` between two statements: a scheduler barrier that emits nothing
        for k in range(body_start, e - 1):
            if is_stmt(lines[k]) and (is_stmt(lines[k + 1]) or re.match(r"\s*(if|return|switch)\b", lines[k + 1])):
                ls = list(lines)
                ls.insert(k + 1, indent(lines[k]) + '__asm__ volatile("");')
                out.append(("barrier after line %d" % (k - b), join(ls)))
    if "swapif" in only or "perbranch" in only:
        for k in range(body_start, e):
            m = re.match(r"^(\s*)((?:\}\s*else\s+)?)if \((.*)\) \{\s*$", lines[k])
            if not m or m.group(2):
                continue
            arms = if_arms(lines, k, e)
            if not arms:
                continue
            (t0, t1), (f0, f1), close = arms
            ind = m.group(1)
            if "swapif" in only and f0 is not None and not m.group(2):
                # if (c) { A } else { B }  ->  if (!(c)) { B } else { A }
                ls = lines[:k] + ["%sif (!(%s)) {" % (ind, m.group(3))] + lines[f0:f1] + [ind + "} else {"] + \
                    lines[t0:t1] + lines[close:]
                out.append(("swap the if / else arms at line %d" % (k - b), join(ls)))
            if "perbranch" in only and f0 is not None and close + 1 < e:
                # v = K1 / v = K2 at the end of the arms, then `X = v;` (or another use of v) right after:
                # the use with its value in every arm, the local gone (one cross-jumped store)
                nxt = lines[close + 1]
                lt = [j for j in range(t0, t1) if lines[j].strip()]
                lf = [j for j in range(f0, f1) if lines[j].strip()]
                if not lt or not lf or not is_stmt(nxt):
                    continue
                ma = re.match(r"^\s*([A-Za-z_]\w*)\s*=(?!=)\s*(.+);\s*$", lines[lt[-1]])
                mb = re.match(r"^\s*([A-Za-z_]\w*)\s*=(?!=)\s*(.+);\s*$", lines[lf[-1]])
                if not ma or not mb or ma.group(1) != mb.group(1) or ma.group(1) not in names:
                    continue
                v = ma.group(1)
                if len(re.findall(r"(?<![\w.>])\b%s\b" % re.escape(v), nxt)) != 1 or \
                        re.match(r"\s*%s\s*=(?!=)" % re.escape(v), nxt) or not dead_after(lines, v, close + 2, e):
                    continue
                ia = indent(lines[lt[-1]])
                ls = list(lines)
                ls[lt[-1]] = ia + sub_name(nxt.strip(), v, "(%s)" % ma.group(2))
                ls[lf[-1]] = indent(lines[lf[-1]]) + sub_name(nxt.strip(), v, "(%s)" % mb.group(2))
                ls[close + 1] = None
                out.append(("per-branch %s at line %d instead of local %s" % (nxt.strip(), close + 1 - b, v),
                            join([x for x in ls if x is not None])))
    if "ptrlocal" in only:
        # globals read or written through pointer locals in a block (`{ s16 *p0 = &D_x; ... *p0 ... }`; the
        # scratchpad recipe: every lui first): a run of 1-4 statements, or the body of one case
        def globals_in(seg):
            gs = []
            for l in seg:
                for g in re.findall(r"(?<![\w.>&])(D_[0-9A-Fa-f]\w*)\b(?!\s*[\[(])", re.sub(r"//.*", "", l)):
                    if g not in gs and re.search(r"(?m)^extern\s+(?:volatile\s+)?[A-Za-z_]\w*\s+%s\s*;" % g, text):
                        gs.append(g)
            return gs

        def ptr_block(k1, k2, desc):
            seg = lines[k1:k2 + 1]
            gs = globals_in(seg)
            if not gs:
                return
            ind = indent(lines[k1])
            hdr = []
            for q, g in enumerate(gs):
                ty = re.search(r"(?m)^extern\s+((?:volatile\s+)?[A-Za-z_]\w*)\s+%s\s*;" % g, text).group(1)
                hdr.append("%s    %s *rs_p%d = &%s;" % (ind, ty, q, g))
            body = []
            for l in seg:
                for q, g in enumerate(gs):
                    l = re.sub(r"(?<![\w.>&])%s\b(?!\s*[\[(])" % g, "(*rs_p%d)" % q, l)
                body.append("    " + l)
            ls = lines[:k1] + [ind + "{"] + hdr + body + [ind + "}"] + lines[k2 + 1:]
            out.append(("ptrlocal %s for %s" % ("/".join(gs), desc), join(ls)))
        for k in range(body_start, e):
            for n_ in (1, 2, 3, 4):
                k2 = k + n_ - 1
                if k2 < e and all(is_stmt(lines[j]) and indent(lines[j]) == indent(lines[k]) for j in range(k, k2 + 1)):
                    ptr_block(k, k2, "lines %d-%d" % (k - b, k2 - b))
            if re.match(r"\s*case\b.*:\s*$", lines[k]):
                end = path_end(lines, k, e) or e
                j2 = end - 1
                while j2 > k and (not lines[j2].strip() or re.match(r"\s*(break|return)\b", lines[j2])):
                    j2 -= 1
                seg = list(range(k + 1, j2 + 1))
                if seg and all(not re.match(r"\s*(case\b|default\s*:|\w+:\s*$)", lines[j]) for j in seg):
                    depth = 0
                    for j in seg:
                        depth += lines[j].count("{") - lines[j].count("}")
                        if depth < 0:
                            break
                    if depth == 0 and not any(re.search(r"\bbreak\s*;", lines[j]) for j in seg):
                        ptr_block(k + 1, j2, "the case at line %d" % (k - b))
    return out


def if_arms(lines, k, e):
    """((then first, then end), (else first, else end) or (None, None), index of the closing `}` line) of an
    `if (...) {` line at k whose arms are plain blocks (`} else {`, not `} else if`), or None."""
    depth, j = 0, k
    t0, t1 = k + 1, None
    while j < e:
        c = re.sub(r"//.*|/\*.*?\*/", "", lines[j])
        if j > k and depth == 1 and re.match(r"^\s*\}\s*else\s*\{\s*$", c):
            if t1 is not None:
                return None
            t1 = j
            j += 1
            continue
        if j > k and depth == 1 and re.match(r"^\s*\}\s*else\b", c):
            return None                             # else if: not a plain pair
        depth += c.count("{") - c.count("}")
        if depth == 0:
            if t1 is None:
                return (t0, j), (None, None), j
            return (t0, t1), (t1 + 1, j), j
        j += 1
    return None


def assigns_to(l, n):
    return re.search(r"(?<![\w.>])\b%s\s*(=(?!=)|\+\+|--|[-+*/|&^%%]=|<<=|>>=)|(\+\+|--)\s*%s\b" % (
        re.escape(n), re.escape(n)), l)


def dominated_uses(lines, n, at, e):
    """the lines after `at` (an assignment of n) that read n and run only after it with its value: same block or
    deeper, no case / default / label line in between, no reassignment of n before them; with a loop between, n
    must not be assigned again anywhere after at (a back edge would bring another value)."""
    out, depth, loop = [], 0, False
    later_assign = any(assigns_to(lines[k], n) for k in range(at + 1, e))
    for j in range(at + 1, e):
        c = re.sub(r"//.*|/\*.*?\*/", "", lines[j])
        if re.match(r"^\s*(case\b.*:|default\s*:|[A-Za-z_]\w*\s*:(?!:))", c):
            break
        if re.match(r"^\s*(\}\s*)?(for|while|do)\b", c):
            loop = True
        for ch in c:
            depth += (ch == "{") - (ch == "}")
            if depth < 0:
                return out
        if re.search(r"(?<![\w.>])\b%s\b" % re.escape(n), c):
            m = assigns_to(c, n)
            rhs = c.split("=", 1)[1] if m and "=" in c else ""
            if m:
                if re.search(r"(?<![\w.>])\b%s\b" % re.escape(n), rhs) and not loop:
                    pass                            # reads before it writes: still the old value on the right
                break
            if loop and later_assign:
                break
            out.append(j)
    return out


def indent(l):
    return l[:len(l) - len(l.lstrip())]


def is_stmt(l):
    s = l.strip()
    return s.endswith(";") and not s.startswith(("return", "break", "continue", "goto", "case", "default", "}",
                                                 "do ", "for", "while", "if", "else", "//", "#")) and \
        s.count(";") == 1


def is_store(l):
    """an assignment through memory (`a[k] = `, `p->f = `, `*(T *)... = `, `M2C_FIELD(...) = `, `D_x = `)."""
    m = re.match(r"^\s*(.+?)\s*(?:[-+*/|&^]|<<|>>)?=(?!=)", l)
    if not m:
        return False
    lhs = m.group(1)
    return bool(re.search(r"[\[*]|->|M2C_FIELD|^D_|^\w+F\(", lhs.strip()))


def balanced(s, i):
    """index after the bracket group starting at s[i] (one of ( [ ), or None."""
    pairs = {"(": ")", "[": "]"}
    st = []
    for j in range(i, len(s)):
        c = s[j]
        if c in pairs:
            st.append(pairs[c])
        elif c in ")]":
            if not st or st.pop() != c:
                return None
            if not st:
                return j + 1
    return None


def reads(l):
    """[(start, end, text)] of the memory reads of a statement line (not its assignment target): M2C_FIELD(...),
    `*(T *)X`, `x[...]`, `p->f` chains and D_ globals."""
    s = l
    lhs_end = 0
    m = re.match(r"^\s*(.+?)\s*(?:[-+*/|&^]|<<|>>)?=(?!=)", s)
    if m and is_stmt(s) and not re.match(r"\s*(if|while|switch)\b", s):
        lhs_end = m.end()
    out = []
    i = lhs_end
    while i < len(s):
        mm = re.compile(r"M2C_FIELD\(|\*\(\s*(?:volatile\s+)?[A-Za-z_]\w*\s*\*+\s*\)\s*|"
                        r"(?<![\w.>])([A-Za-z_]\w*)(?=\s*(\[|->))|(?<![\w.>&])D_[0-9A-Fa-f]\w*\b(?!\s*[\[(])").search(s, i)
        if not mm:
            break
        st = mm.start()
        if mm.group(0).startswith("M2C_FIELD("):
            en = balanced(s, mm.end() - 1)
        elif mm.group(0).startswith("*("):
            j = mm.end()
            if j < len(s) and s[j] == "(":
                en = balanced(s, j)
            else:
                w = re.match(r"[A-Za-z_]\w*", s[j:])
                en = j + w.end() if w else None
        elif mm.group(1):
            en = mm.end()
            while True:
                rest = s[en:]
                if rest.lstrip().startswith("["):
                    en = balanced(s, en + len(rest) - len(rest.lstrip()))
                    if en is None:
                        break
                elif re.match(r"\s*->\s*\w+", rest):
                    en += re.match(r"\s*->\s*\w+", rest).end()
                else:
                    break
        else:
            en = mm.end()
        if en is None:
            i = mm.end()
            continue
        if st > 0 and s[:st].rstrip().endswith("&") and not s[:st].rstrip().endswith("&&"):
            i = en
            continue                                    # an address taken, not a read
        if re.match(r"\s*(\+\+|--|=(?!=)|[-+*/|&^]=)", s[en:]):
            i = en
            continue                                    # written (x++ / x = / x += in a condition)
        if s[:st].rstrip().endswith(("++", "--")):
            i = en
            continue
        out.append((st, en, s[st:en]))
        i = en
    return out[:8]


def expr_type(ex, text, lines, b, e):
    m = re.match(r"M2C_FIELD\([^,]+,\s*([\w\s]+?)\s*\*\s*,", ex)
    if m:
        return m.group(1)
    m = re.match(r"\*\(\s*(?:volatile\s+)?([A-Za-z_]\w*)\s*\*\s*\)", ex)
    if m:
        return m.group(1)
    m = re.match(r"([A-Za-z_]\w*)\s*\[[^\]]*\]\s*$", ex)
    if m:
        n = m.group(1)
        dm = re.search(r"(?<![\w])((?:unsigned\s+|signed\s+)?[A-Za-z_]\w*)\s*\*\s*%s\s*[,;)=]" % re.escape(n),
                       "\n".join(lines[max(0, b - 3):e]))
        if dm and dm.group(1) not in ("return", "struct"):
            return dm.group(1)
        dm = re.search(r"(?m)^extern\s+([A-Za-z_]\w*)\s+%s\s*\[" % re.escape(n), text)
        if dm:
            return dm.group(1)
    m = re.fullmatch(r"D_\w+", ex)
    if m:
        dm = re.search(r"(?m)^extern\s+((?:volatile\s+)?[A-Za-z_]\w*)\s+%s\s*;" % re.escape(ex), text)
        if dm:
            return dm.group(1)
    return "__typeof__(%s)" % ex


MEMBER = "#define MEMBER_AT(T, p, o) (((struct { u8 pad[o]; T v; } *)(p))->v)"


def member_macros(text):
    """{macro name: type} of the file's struct-member access macros (`#define S16F(p, o) (((struct { u8 pad[o];
    s16 v; } *)(p))->v)`)."""
    out = {}
    for m in re.finditer(r"(?m)^#define\s+(\w+)\((\w+),\s*(\w+)\)\s*\(\(\(struct\s*\{\s*u8\s+pad\[\3\];\s*"
                         r"([\w ]+?)\s+v;\s*\}\s*\*\)\s*\(\2\)\)->v\)", text):
        if m.group(1) != "MEMBER_AT":
            out[m.group(1)] = m.group(4)
    return out


def casts(l, macros):
    """[(start, end, text, toggled text)] of the cast accesses of a line with a literal offset, and of the uses
    of the file's member macros (toggled back to casts)."""
    out = []
    for m in re.finditer(r"M2C_FIELD\(", l):
        en = balanced(l, m.end() - 1)
        if en is None:
            continue
        parts = split_args(l[m.end():en - 1])
        if len(parts) == 3:
            tm = re.match(r"\s*([\w ]+?)\s*\*\s*$", parts[1])
            if tm and re.fullmatch(r"\s*(0x[0-9A-Fa-f]+|\d+)\s*", parts[2]):
                out.append((m.start(), en, l[m.start():en],
                            "MEMBER_AT(%s, %s, %s)" % (tm.group(1), parts[0].strip(), parts[2].strip())))
    for m in re.finditer(r"\*\(\s*([A-Za-z_]\w*)\s*\*\s*\)\s*\(", l):
        en = balanced(l, m.end() - 1)
        if en is None:
            continue
        inner = l[m.end():en - 1]
        # the base: a name or a member chain (`a-i + 4` is no base: a variable offset never becomes MEMBER_AT)
        im = re.fullmatch(r"\s*(?:\(\s*u8\s*\*\s*\)\s*)?([A-Za-z_]\w*(?:(?:->|\.)[A-Za-z_]\w*)*)\s*\+\s*"
                          r"(0x[0-9A-Fa-f]+|\d+)\s*", inner)
        if im:
            out.append((m.start(), en, l[m.start():en], "MEMBER_AT(%s, %s, %s)" % (m.group(1), im.group(1), im.group(2))))
    for name, ty in macros.items():
        for m in re.finditer(r"\b%s\(" % re.escape(name), l):
            en = balanced(l, m.end() - 1)
            if en is None:
                continue
            parts = split_args(l[m.end():en - 1])
            if len(parts) == 2:
                out.append((m.start(), en, l[m.start():en],
                            "(*(%s *)((u8 *)(%s) + (%s)))" % (ty, parts[0].strip(), parts[1].strip())))
    out.sort()
    keep, last = [], -1
    for x in out:
        if x[0] >= last:
            keep.append(x)
            last = x[1]
    return keep


def add_member_macro(text):
    """the MEMBER_AT macro (include/common.h has it) defined in a file that does not include common.h."""
    if "MEMBER_AT(" not in text or MEMBER in text or re.search(r'#include\s+"common.h"', text):
        return text
    m = list(re.finditer(r"(?m)^#include.*$", text))
    at = m[-1].end() if m else 0
    return text[:at] + "\n" + MEMBER + text[at:]


def split_args(s):
    out, depth, cur = [], 0, ""
    for c in s:
        if c in "([":
            depth += 1
        elif c in ")]":
            depth -= 1
        if c == "," and depth == 0:
            out.append(cur)
            cur = ""
        else:
            cur += c
    out.append(cur)
    return out


def split_ternary(s):
    """(cond, a, b) of a top-level `c ? a : b`, or None."""
    depth, q = 0, None
    for i, c in enumerate(s):
        if c in "([":
            depth += 1
        elif c in ")]":
            depth -= 1
        elif c == "?" and depth == 0 and q is None:
            q = i
        elif c == ":" and depth == 0 and q is not None:
            rest = s[i + 1:]
            if "?" in rest:
                return None
            return s[:q].strip(), s[q + 1:i].strip(), rest.strip()
    return None


def tail_block(lines, lab, e):
    """the line indices from a label to the end of its tail (a return, break or goto at the label's depth)."""
    out, depth = [], 0
    for j in range(lab, e):
        l = re.sub(r"//.*", "", lines[j])
        if j > lab and re.match(r"^\s*\w+:\s*$", l) and not l.strip().startswith("default"):
            return None                                 # another label inside
        if re.match(r"^\s*(case\b|default\s*:)", l) and j > lab:
            return None
        depth += l.count("{") - l.count("}")
        if depth < 0:
            return None
        out.append(j)
        if depth == 0 and re.match(r"^\s*(\w+:\s*)?(return\b.*;|break;|goto\s+\w+;)\s*$", l):
            return out
    return None


def dead_after(lines, n, end, e):
    """n holds no value at `end`: the path does not fall through into a next case, and the next mention of n is
    an assignment that does not read it (or there is none)."""
    prev = [l.strip() for l in lines[:end] if l.strip()]
    if prev and re.match(r"(case\b|default\s*:)", lines[end].strip() if end < e else "") and \
            not re.match(r"(break|return|goto|continue)\b", prev[-1]):
        return False
    for j in range(end, e):
        if re.search(r"(?<![\w.>])\b%s\b" % re.escape(n), lines[j]):
            m = re.match(r"\s+%s\s*=(?!=)(.*)$" % re.escape(n), lines[j])
            return bool(m) and not re.search(r"(?<![\w.>])\b%s\b" % re.escape(n), m.group(1))
    return True


def path_end(lines, k, e):
    """the index after the end of the block or case holding line k (None when that is the function's end)."""
    depth = 0
    for j in range(k + 1, e):
        l = re.sub(r"//.*", "", lines[j])
        if depth == 0 and re.match(r"^\s*(case\b|default\s*:)", l):
            return j
        depth += l.count("{") - l.count("}")
        if depth < 0:
            return j
    return None


MAX_PERM = 720
NARROWING = False
SIZES = {"u8": 1, "s8": 1, "char": 1, "s16": 2, "u16": 2, "short": 2, "s32": 4, "u32": 4, "int": 4, "long": 4}
# first in every round: the cheap rewrites that often decide a register; then every kind in turn up to --max-cands
FIRST = ("wrap", "volatile")


def kind_of(desc):
    k = desc.split()[0].rstrip(":")
    return {"if": "ternary", "call": "callres", "temp": "temp", "load": "load", "swap": "swapif",
            "per-branch": "perbranch"}.get(k, k)


def fair(cands, limit):
    """at most `limit` candidates: wrap / volatile ones first, then one of each kind in turn (decl orders alone
    used to fill the --max-cands budget of a big function before the later kinds were reached)."""
    if len(cands) <= limit:
        return sorted(cands, key=lambda c: kind_of(c[0]) not in FIRST)
    by = collections.OrderedDict()
    for c in cands:
        by.setdefault(kind_of(c[0]), []).append(c)
    order = [k for k in FIRST if k in by] + [k for k in by if k not in FIRST]
    out, i = [], 0
    while len(out) < limit:
        added = False
        for k in order:
            if i < len(by[k]):
                out.append(by[k][i])
                added = True
                if len(out) == limit:
                    break
        if not added:
            break
        i += 1
    return out


def main():
    global MAX_PERM
    ap = argparse.ArgumentParser()
    ap.add_argument("src")
    ap.add_argument("func")
    ap.add_argument("--prog", default="main")
    ap.add_argument("-j", type=int, default=os.cpu_count())
    ap.add_argument("--rounds", type=int, default=4)
    ap.add_argument("--out")
    ap.add_argument("--only", default="decl,split,reuse,fork,copy,keep,wrap,temp,load,const,member,volatile,goto,"
                                      "ternary,pathsplit,callres,abs,callcopy,barrier,swapif,perbranch,ptrlocal")
    ap.add_argument("--skip", default="", help="kinds left out of --only")
    ap.add_argument("--max-cands", type=int, default=3000, help="rewrites compiled per round at most")
    ap.add_argument("--max-perm", type=int, default=720)
    ap.add_argument("--install", action="store_true")
    ap.add_argument("--pairs", type=int, default=6, help="when no single rewrite helps, pairs on the N best (0: off)")
    ap.add_argument("--max-seconds", type=float, default=0, help="stop after this long (0: no limit); the best text "
                    "so far is kept")
    ap.add_argument("--narrowing", action="store_true", help="also try splits through a temporary narrower than "
                    "the store's target (they truncate the value; flagged NARROWING)")
    a = ap.parse_args()
    global NARROWING
    MAX_PERM = a.max_perm
    NARROWING = a.narrowing
    import time
    deadline = time.time() + a.max_seconds if a.max_seconds else None
    only = set(a.only.split(",")) - set(a.skip.split(","))
    out = a.out or re.sub(r"\.c$", "", a.src) + ".regswap.c"
    text = open(a.src).read()
    work = tempfile.mkdtemp(prefix="tmp_regswap_", dir=os.path.join(ROOT, "build"))
    d = os.path.dirname(os.path.abspath(a.src))

    def sc(t, k):
        # the candidate sits beside the scratch so its relative #include lines still resolve
        if deadline and k and time.time() > deadline:
            return None     # --max-seconds: the rest of the round is skipped
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
            if deadline and time.time() > deadline:
                print("--max-seconds reached", flush=True)
                break
            cands = fair(rewrites(text, a.func, only), a.max_cands)
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
                jobs = [(d1, d2, t2) for d1, t1 in firsts for d2, t2 in fair(rewrites(t1, a.func, only), a.max_cands)]
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

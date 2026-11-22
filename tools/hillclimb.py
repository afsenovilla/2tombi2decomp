#!/usr/bin/env python3
"""Greedy recipe search on m2c drafts: apply small source transforms one at a time and keep each one that lowers
the number of words that differ from retail, until the function matches or nothing helps.

  python3 -I tools/hillclimb.py [--prog main] [--max-size 0x200] [--names A,B] [-j N] [--install] [--rounds 6]

The transforms are the hand recipes of docs/STATUS.md that can be applied blindly:
  - `x = 1;` -> `x += 1;` (a state set in `case 0`: gcc knows it is 0 and reuses the compare constant);
  - one global extern made volatile (a store that must not move into a delay slot);
  - the type of one parameter or local (s32 / u8 / s8 / u16 / s16);
  - `if (c) { A } else { B }` -> `if (!(c)) { B } else { A }` (branch layout);
  - two adjacent simple statements swapped (load / store order);
  - an `M2C_FIELD(...)` read in a statement hoisted into a local (a read done before the stores);
  - a constant in a local (`s32 k = 3;`, every use or one), a narrow-type copy variable for a switch
    (`switch (j = x)` with j u8 / s8 / u16 / s16 / s32), a guarded do/while <-> while, one M2C_FIELD read made
    volatile (docs/STATUS.md 2026-11-22 (2));
  - a `default:` moved first in its switch or (when empty / `break;`) removed, `x = K + 1;` -> `x++;` in `case K:`,
    a scratchpad constant address `*(T *)0x1F80xxxx` as an extern `D_1F80xxxx`, a top-level early return
    inverted (`if (c) { return X; } ...; return Y;` <-> `if (!(c)) { ...; return Y; } return X;`)
    (docs/STATUS.md 2026-11-22 (4)).
Each candidate is compiled and compared by tools/ccheck.py; the score is the number of differing words plus the
size difference. Matches are written to build/hillclimb/<name>.c and, with --install, installed with
tools/install_c.py (linked-build checked, one at a time if needed).
"""
import argparse, concurrent.futures as cf, os, re, subprocess, sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))
import decomp as D
import sweep as S

HEAD = '#include "common.h"\n#include "game.h"\n#include "m2c.h"\n'
TYPES = ["s32", "u8", "s8", "u16", "s16"]


def score(src, prog, name):
    r = subprocess.run([sys.executable, "-I", os.path.join(ROOT, "tools", "ccheck.py"), src, "--prog", prog,
                        "--func", name, "-v"], capture_output=True, text=True, cwd=ROOT)
    out = r.stdout
    m = re.search(r"^(OK|DIFF) %s\b.*?(?:, (\d+) words differ)?$" % re.escape(name), out, re.M)
    if not m:
        return None
    if m.group(1) == "OK":
        return 0
    n = int(m.group(2) or 0)
    sz = re.search(r"size: got 0x(\w+) bytes, retail 0x(\w+)", out)
    if sz:
        n += abs(int(sz.group(1), 16) - int(sz.group(2), 16)) // 4
    return n


def block_end(t, i):
    """index just past the `}` matching the `{` at t[i]."""
    d = 0
    for j in range(i, len(t)):
        if t[j] == "{":
            d += 1
        elif t[j] == "}":
            d -= 1
            if d == 0:
                return j + 1
    return None


def candidates(body, name):
    out = []
    # `= 1;` -> `+= 1;`
    for m in re.finditer(r"(?m)^(\s+)([^\n=;]+?) = 1;$", body):
        out.append(body[:m.start()] + "%s%s += 1;" % (m.group(1), m.group(2)) + body[m.end():])
    # one extern volatile
    for m in re.finditer(r"(?m)^extern (?!volatile)([^;(]*;)$", body):
        out.append(body[:m.start()] + "extern volatile " + m.group(1) + body[m.end():])
    # parameter / local types
    fm = re.search(r"\b%s\(([^)]*)\)\s*\{" % re.escape(name), body)
    if fm:
        for pm in re.finditer(r"(\b(?:s32|u8|s8|u16|s16|u32)\b)(\s+\w+)", fm.group(1)):
            for t in TYPES:
                if t != pm.group(1):
                    a, b = fm.start(1) + pm.start(1), fm.start(1) + pm.end(1)
                    out.append(body[:a] + t + body[b:])
    for lm in re.finditer(r"(?m)^    (s32|u8|s8|u16|s16|u32) (\w+);$", body):
        for t in TYPES:
            if t != lm.group(1):
                out.append(body[:lm.start(1)] + t + body[lm.end(1):])
    # if / else swap
    for m in re.finditer(r"\bif \(", body):
        i = m.end() - 1
        d = 0
        for j in range(i, len(body)):
            d += {"(": 1, ")": -1}.get(body[j], 0)
            if d == 0:
                break
        cond = body[i + 1:j]
        k = body.find("{", j)
        if k < 0 or body[j + 1:k].strip():
            continue
        e1 = block_end(body, k)
        rest = body[e1:]
        em = re.match(r"\s*else\s*\{", rest)
        if not e1 or not em:
            continue
        k2 = e1 + em.end() - 1
        e2 = block_end(body, k2)
        if not e2:
            continue
        a, b = body[k + 1:e1 - 1], body[k2 + 1:e2 - 1]
        out.append(body[:m.start()] + "if (!(%s)) {%s} else {%s}" % (cond, b, a) + body[e2:])
    # adjacent simple statements swapped
    lines = body.split("\n")
    simple = re.compile(r"^\s+[^{}]*;$")
    for i in range(len(lines) - 1):
        a, b = lines[i], lines[i + 1]
        if simple.match(a) and simple.match(b) and not re.match(r"\s*(return|break|goto|case|default)", a + b) \
                and len(a) - len(a.lstrip()) == len(b) - len(b.lstrip()) and " = " in a and " = " in b:
            out.append("\n".join(lines[:i] + [b, a] + lines[i + 2:]))
    # hoist an M2C_FIELD read into a local just before its statement
    for m in re.finditer(r"(?m)^(\s+)(.*?)(M2C_FIELD\((\w+), (\w+) \*, (0x\w+|\d+)\))(?! =)(.*;)$", body):
        ind, pre, expr, typ = m.group(1), m.group(2), m.group(3), m.group(5)
        if "=" not in pre and not pre.startswith(("return", "if")):
            continue
        var = "hc_%d" % m.start()
        # a block of its own: gcc 2.8 (C89) wants declarations at the top of a block
        line = "%s{ %s %s = %s; %s%s%s }" % (ind, typ, var, expr, pre, var, m.group(7))
        out.append(body[:m.start()] + line + body[m.end():])
    out += new_candidates(body, name)
    out += round3_candidates(body, name)
    # void function -> s32 (retail leaves v0 live: an empty delay slot before the exit)
    vm = re.search(r"(?m)^void (%s\()" % re.escape(name), body)
    if vm:
        out.append(body[:vm.start()] + "s32 " + body[vm.start(1):])
    return out


def body_start(body, name):
    """index just past the `{` opening the function `name` (None when not found)."""
    m = re.search(r"\b%s\([^;{]*\)\s*\{" % re.escape(name), body)
    return m.end() if m else None


def new_candidates(body, name, max_lits=12):
    """the 2026-11-22 recipes: a constant in a local, a narrow-type copy variable for a switch, while <->
    guarded do/while, a volatile field reload."""
    out = []
    st = body_start(body, name)
    if st is None:
        return out
    head, fn = body[:st], body[st:]
    # a constant in a local (`s32 k = 3;` keeps it in a register / where retail has it): all uses, or one
    lits = {}
    for m in re.finditer(r"(?<![\w.])(0x[0-9A-Fa-f]+|[1-9]\d*)(?![\w.])", fn):
        pre = fn[:m.start()]
        line = pre[pre.rfind("\n") + 1:]
        if re.search(r"\bcase\s*$", pre) or re.search(r"\*\s*,\s*$", pre) or "[" in line and \
                re.match(r"\s*(?:s32|u32|s16|u16|s8|u8)\b[^=]*\[$", line):
            continue
        if re.match(r"\s*(?:s32|u32|s16|u16|s8|u8|void)\b[^=;]*$", line):
            continue     # a declaration's array size
        lits.setdefault(int(m.group(1), 0), []).append((m.start(), m.end()))
    for v, spans in list(lits.items())[:max_lits]:
        for pick in ([spans] + ([[s] for s in spans] if 1 < len(spans) <= 4 else [])):
            f = fn
            for a_, b_ in sorted(pick, reverse=True):
                f = f[:a_] + "hc_k" + f[b_:]
            out.append(head + "\n    s32 hc_k = 0x%X;" % v + f)
    # a narrow-type copy variable for a switch (`s32 k = x; u8 j = k;`, the cases on j)
    for m in re.finditer(r"\bswitch \(", fn):
        i, d = m.end() - 1, 0
        for j in range(i, len(fn)):
            d += {"(": 1, ")": -1}.get(fn[j], 0)
            if d == 0:
                break
        for ty in ("u8", "s8", "u16", "s16", "s32"):
            out.append(head + "\n    %s hc_s;" % ty + fn[:i + 1] + "hc_s = " + fn[i + 1:])
    # guarded do/while <-> while
    for m in re.finditer(r"(?m)^(\s*)if \((.*)\) \{\n\s*do \{\n", fn):
        k = fn.find("{", m.end() - 2)
        e = block_end(fn, k)
        tail = re.match(r" while \((.*)\);\n\s*\}", fn[e:]) if e else None
        if tail:
            inner = fn[k + 1:e - 1]
            out.append(head + fn[:m.start()] + "%swhile (%s) {%s}" % (m.group(1), tail.group(1), inner) +
                       fn[e + tail.end():])
    for m in re.finditer(r"(?m)^(\s*)while \((.*)\) \{", fn):
        e = block_end(fn, m.end() - 1)
        if e:
            inner = fn[m.end():e - 1]
            out.append(head + fn[:m.start()] + "%sif (%s) { do {%s} while (%s); }" %
                       (m.group(1), m.group(2), inner, m.group(2)) + fn[e:])
    # one field read made volatile (retail reloads it)
    for m in re.finditer(r"M2C_FIELD\(([^,]+), ([\w *]+?)\s*\*, ", fn):
        out.append(head + fn[:m.start()] + "M2C_FIELD(%s, %s volatile *, " % (m.group(1), m.group(2)) +
                   fn[m.end():])
    return out


def segments(fn, k):
    """[(label start, label end, segment end)] of the `case` / `default` labels of the switch block at fn[k] ('{')."""
    e = block_end(fn, k)
    if not e:
        return [], None
    labs, d, i = [], 0, k
    while i < e:
        c = fn[i]
        if c == "{":
            d += 1
        elif c == "}":
            d -= 1
        elif d == 1:
            m = re.match(r"(?:case [^:]+|default):", fn[i:])
            if m and re.match(r"\s", fn[i - 1]):
                labs.append((i, i + m.end()))
                i += m.end()
                continue
        i += 1
    out = [(a_, b_, labs[n + 1][0] if n + 1 < len(labs) else e - 1) for n, (a_, b_) in enumerate(labs)]
    return out, e


def round3_candidates(body, name):
    """the 2026-11-22 (4) recipes: default case first / removed, `x = K + 1` -> `x++` in `case K`, a scratchpad
    constant address as an extern symbol, an early return inverted."""
    out = []
    st = body_start(body, name)
    if st is None:
        return out
    head, fn = body[:st], body[st:]
    ends = lambda t: bool(re.search(r"\b(?:break|return[^;]*|goto \w+|continue);\s*$", t))
    for m in re.finditer(r"\bswitch \(", fn):
        k = fn.find("{", m.end())
        segs, e = segments(fn, k)
        if not segs:
            continue
        for n, (a_, b_, z) in enumerate(segs):
            if not fn[a_:b_].startswith("default"):
                continue
            seg = fn[a_:z].rstrip()
            # removed (a `default: break;` or an empty default)
            if re.fullmatch(r"default:\s*(?:break;)?", seg):
                out.append(head + fn[:a_] + fn[z:])
            # first (it must not fall into the next case, nor be fallen into)
            if n and ends(seg) and ends(fn[segs[n - 1][1]:a_]):
                first = segs[0][0]
                ind = fn[fn.rfind("\n", 0, first) + 1:first]
                out.append(head + fn[:first] + seg + "\n" + ind + fn[first:a_] + fn[z:])
        # `x = K + 1;` in `case K:` -> `x++;` (gcc reuses the register of the next compare constant)
        sw = fn[m.end():fn.rfind(")", m.end(), k)].strip()
        for a_, b_, z in segs:
            cm = re.match(r"case (0x[0-9A-Fa-f]+|\d+):", fn[a_:b_])
            if not cm:
                continue
            kv = int(cm.group(1), 0)
            for am in re.finditer(r"(?m)^(\s+)([^\n=;]+?) = (0x[0-9A-Fa-f]+|\d+);$", fn[b_:z]):
                if int(am.group(3), 0) == kv + 1 and am.group(2).strip() == sw:
                    i0, i1 = b_ + am.start(), b_ + am.end()
                    out.append(head + fn[:i0] + "%s%s++;" % (am.group(1), am.group(2)) + fn[i1:])
    # a scratchpad constant address as an extern symbol
    for m in re.finditer(r"\*\(((?:volatile )?\w+) \*\)0x(1F80[0-9A-Fa-f]{4})\b", body):
        sym = "D_%s" % m.group(2).upper()
        if re.search(r"\b%s\b" % sym, body):
            continue
        new = body.replace(m.group(0), sym)
        st2 = body_start(new, name)
        fs = new.rfind("\n", 0, new.rfind("\n", 0, st2)) + 1 if st2 else 0
        out.append(new[:fs] + "extern %s %s;\n" % (m.group(1), sym) + new[fs:])
    # early returns inverted at the top level of the body
    lines = fn.split("\n")
    for i, l in enumerate(lines):
        mm = re.match(r"^    if \((.*)\) \{$", l)
        if not mm:
            continue
        j = next((x for x in range(i + 1, len(lines)) if lines[x] == "    }"), None)
        if j is None:
            continue
        inner, rest = lines[i + 1:j], lines[j + 1:]
        close = next((x for x in range(len(rest)) if rest[x] == "}"), None)
        if close is None:
            continue
        tail, after = rest[:close], rest[close:]
        cond = mm.group(1)
        # if (c) { return X; } REST; return Y;   ->   if (!(c)) { REST; return Y; } return X;
        if len(inner) == 1 and inner[0].strip().startswith("return") and tail and \
                tail[-1].startswith("    return"):
            nl = lines[:i] + ["    if (!(%s)) {" % cond] + ["    " + x if x else x for x in tail] + \
                ["    }", "    " + inner[0].strip()] + after
            out.append(head + "\n".join(nl))
        # if (c) { BODY; return Y; } return X;   ->   if (!(c)) { return X; } BODY; return Y;
        if inner and inner[-1].strip().startswith("return") and len(tail) == 1 and \
                tail[0].startswith("    return"):
            nl = lines[:i] + ["    if (!(%s)) {" % cond, "    " + tail[0], "    }"] + \
                [x[4:] if x.startswith("        ") else x for x in inner] + after
            out.append(head + "\n".join(nl))
    return out


def climb(prog, name, ctx, rounds):
    _, draft = draft_of(prog, name, ctx)
    if draft is None:
        return name, None, None
    d = os.path.join(ROOT, "build", "hillclimb", prog)
    os.makedirs(d, exist_ok=True)
    test = os.path.join(d, name + ".try.c")

    def sc(body):
        open(test, "w").write(HEAD + body)
        return score(test, prog, name)
    best = sc(draft)
    if best is None:
        return name, None, None
    body = draft
    start = best
    for _ in range(rounds):
        if best == 0:
            break
        improved = False
        for c in candidates(body, name):
            s = sc(c)
            if s is not None and s < best:
                best, body, improved = s, c, True
                if best == 0:
                    break
        if not improved:
            break
    if best == 0:
        open(os.path.join(d, name + ".c"), "w").write(HEAD + body)
    print("%-40s %4s -> %s" % (name, start, "MATCH" if best == 0 else best), flush=True)
    return name, start, best


def draft_of(prog, name, ctx):
    r = subprocess.run(D.m2c_cmd(prog, name, ctx, ["--valid-syntax"]), capture_output=True, text=True, cwd=ROOT)
    if r.returncode or not r.stdout.strip() or "Decompilation failure" in r.stdout:
        return name, None
    body = S.fill_args(re.sub(r"(?m)^(extern )?\? ", r"\1s32 ", r.stdout), name)
    # functions used as values (callbacks) need a declaration
    vals = sorted(set(re.findall(r"(?<![\w(])((?:func|f)_\w+)\b(?!\s*\()", body)) - {name})
    decl = "".join("s32 %s();\n" % v for v in vals if not re.search(r"\b%s\s*\(" % v, open(ctx).read()))
    return name, decl + body


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--prog", default="main")
    ap.add_argument("--max-size", default="0x200")
    ap.add_argument("--names")
    ap.add_argument("-j", type=int, default=os.cpu_count())
    ap.add_argument("--rounds", type=int, default=6)
    ap.add_argument("--install", action="store_true")
    a = ap.parse_args()
    lim = int(a.max_size, 0)
    names = a.names.split(",") if a.names else [n for n in S.pending(a.prog) if S.size_of(a.prog, n) <= lim]
    ctx = S.prog_context(a.prog)
    with cf.ThreadPoolExecutor(a.j) as ex:
        res = list(ex.map(lambda n: climb(a.prog, n, ctx, a.rounds), names))
    won = [n for n, s, b in res if b == 0]
    better = sorted(((b, s, n) for n, s, b in res if s and b), key=lambda x: x[0])
    print("%d / %d functions match after the search" % (len(won), len(names)))
    for n in won:
        print("  " + n)
    print("closest left (words off, from the draft's):", ", ".join("%s %d<-%d" % (n, b, s) for b, s, n in better[:15]))
    if a.install and won:
        for n in won:
            r = subprocess.run([sys.executable, "-I", os.path.join(ROOT, "tools", "install_c.py"),
                                os.path.join(ROOT, "build", "hillclimb", a.prog, n + ".c"), "--prog", a.prog],
                               capture_output=True, text=True, cwd=ROOT)
            print("  %s: %s" % (n, (r.stdout + r.stderr).strip().splitlines()[-1:]))


if __name__ == "__main__":
    main()

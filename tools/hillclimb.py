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
  - an `M2C_FIELD(...)` read in a statement hoisted into a local (a read done before the stores).
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
        line = "%s%s %s = %s;\n%s%s%s%s" % (ind, typ, var, expr, ind, pre, var, m.group(7))
        out.append(body[:m.start()] + line + body[m.end():])
    return out


def climb(prog, name, ctx, rounds):
    _, draft = draft_of(prog, name, ctx)
    if draft is None:
        return name, None, None
    d = os.path.join(ROOT, "build", "hillclimb")
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
    return name, start, best


def draft_of(prog, name, ctx):
    r = subprocess.run([sys.executable, D.M2C, "--target", "mipsel-gcc-c", "--valid-syntax", "--context", ctx,
                        D.find_asm(prog, name)], capture_output=True, text=True, cwd=ROOT)
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
                                os.path.join(ROOT, "build", "hillclimb", n + ".c"), "--prog", a.prog],
                               capture_output=True, text=True, cwd=ROOT)
            print("  %s: %s" % (n, (r.stdout + r.stderr).strip().splitlines()[-1:]))


if __name__ == "__main__":
    main()

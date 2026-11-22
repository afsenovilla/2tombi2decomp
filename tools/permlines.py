#!/usr/bin/env python3
"""Statement-order permuter: move the lines marked `//P` of one function around until it matches.

  python3 -I tools/permlines.py FILE.c FUNC [--prog main] [-j N] [--window 12] [--max-pairs 4000] [--slots]
      [--out FILE.best.c] [--unsafe]

FILE.c is a ccheck scratch file. Mark each statement to move by ending its line with `//P` (one statement per
line). Every round tries every single move of one marked line to another line boundary of the function body, then
(when no single move helps) every pair of moves within --window lines of each line's place, and goes on from the
best result while the words off (tools/ccheck.py score()) go down. --slots instead permutes the marked lines
among their own lines (every order, at most --max-pairs). Candidates that do not compile are skipped. The best
file is written (default FILE.best.c) on every improvement, so it can be stopped at any time. Orders that put a
line before one it depends on (it reads a variable the other assigns, or the other reads / assigns a variable it
assigns; memory through pointers is not tracked) are not tried, unless --unsafe.

The recipes behind it (docs/STATUS.md): gcc 2.8 keeps a store written after the copy of a field below its load,
a statement whose value retail loads first goes earlier in the source, and store runs follow source order.
"""
import argparse, concurrent.futures as cf, functools, hashlib, itertools, os, re, sys, threading

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))
import ccheck


def body_range(lines, func):
    """(first, last) line indices strictly inside the body of `func`."""
    text = "\n".join(lines)
    m = re.search(r"(?m)^[^\n;#]*\b%s\s*\([^;{]*\)\s*\{" % re.escape(func), text)
    if not m:
        sys.exit("no definition of %s" % func)
    start = text.count("\n", 0, m.end())
    depth = 0
    for i in range(start, len(lines)):
        code = re.sub(r"//.*|\"(?:[^\"\\]|\\.)*\"|'(?:[^'\\]|\\.)*'", "", lines[i])
        depth += code.count("{") - code.count("}")
        if depth == 0 and i > start:
            return start + 1, i - 1
    sys.exit("no end of %s" % func)


def indent_at(lines, pos, last):
    nxt = lines[pos] if pos < len(lines) else ""
    if pos <= last and nxt.strip() and not nxt.strip().startswith("}"):
        return nxt[:len(nxt) - len(nxt.lstrip())]
    prv = lines[pos - 1] if pos > 0 else ""
    ind = prv[:len(prv) - len(prv.lstrip())]
    return ind + "    " if prv.rstrip().endswith("{") else ind


def move(lines, first, last, moves):
    """lines with each (marked line index, new position) applied; positions count in the original list (the
    line goes before that line)."""
    picked = {i for i, _ in moves}
    out = []
    ins = {}
    for i, p in moves:
        ins.setdefault(p, []).append(i)
    for k in range(len(lines) + 1):
        for i in ins.get(k, []):
            s = lines[i].strip()
            out.append(indent_at(lines, k, last) + s)
        if k < len(lines) and k not in picked:
            out.append(lines[k])
    return out


C_WORDS = {"if", "else", "for", "while", "do", "return", "switch", "case", "default", "break", "continue", "goto",
           "sizeof", "s8", "u8", "s16", "u16", "s32", "u32", "int", "char", "short", "long", "unsigned", "signed",
           "void", "struct", "union", "volatile", "const", "register", "static"}


@functools.lru_cache(maxsize=None)
def rw(line):
    """(variables written, identifiers read) of one source line: a write is a plain variable on the left of an
    assignment or ++ / -- (stores through pointers, fields and indexes are memory, not tracked)."""
    code = re.sub(r"//.*|/\*.*?\*/|\"(?:[^\"\\]|\\.)*\"|'(?:[^'\\]|\\.)*'", "", line)
    writes = set()
    for m in re.finditer(r"(?<![\w.>\]*])\s*\b([A-Za-z_]\w*)\s*(?:[-+*/%&|^]|<<|>>)?=(?!=)", code):
        writes.add(m.group(1))
    for m in re.finditer(r"(?:\+\+|--)\s*([A-Za-z_]\w*)\b(?!\s*(?:->|\.|\[))|"
                         r"(?<![\w.>\]])\b([A-Za-z_]\w*)\s*(?:\+\+|--)", code):
        writes.add(m.group(1) or m.group(2))
    ids = set(re.findall(r"\b([A-Za-z_]\w*)\b", code)) - C_WORDS
    # a plain `x = ...` does not read x
    plain = {m.group(1) for m in re.finditer(r"(?<![\w.>\]*])\s*\b([A-Za-z_]\w*)\s*=(?!=)", code)}
    return writes, ids - (plain - set(re.findall(r"=.*\b(%s)\b" % "|".join(plain), code)) if plain else set())


def legal(lines, first, last, order):
    """False when the new order (original line indices of the body) puts a line before a line it depends on
    (it reads a variable the other assigns, or the other reads / assigns a variable it assigns)."""
    pos = {i: k for k, i in enumerate(order)}
    info = {i: rw(lines[i]) for i in range(first, last + 1)}
    idx = sorted(info)
    for a_, b_ in itertools.combinations(idx, 2):       # a_ before b_ originally
        if pos.get(a_, a_) < pos.get(b_, b_):
            continue
        wa, ra = info[a_]
        wb, rb = info[b_]
        if wa & (rb | wb) or wb & ra:
            return False
    return True


def new_order(n, moves):
    """the original indices in the order move() puts them."""
    picked = {i for i, _ in moves}
    ins, out = {}, []
    for i, p in moves:
        ins.setdefault(p, []).append(i)
    for k in range(n + 1):
        out += ins.get(k, [])
        if k < n and k not in picked:
            out.append(k)
    return out


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("src")
    ap.add_argument("func")
    ap.add_argument("--prog", default="main")
    ap.add_argument("-j", type=int, default=os.cpu_count())
    ap.add_argument("--window", type=int, default=12, help="pair moves: at most this many lines from the start")
    ap.add_argument("--max-pairs", type=int, default=4000)
    ap.add_argument("--slots", action="store_true", help="permute the marked lines among their own lines")
    ap.add_argument("--out")
    ap.add_argument("--unsafe", action="store_true", help="also orders that move a line across one it depends on")
    a = ap.parse_args()
    a.src = os.path.abspath(a.src)
    out = a.out or re.sub(r"\.c$", "", a.src) + ".best.c"
    work = os.path.join(ROOT, "build", "permlines")
    os.makedirs(work, exist_ok=True)
    cache = {}

    def score(lines):
        t = "\n".join(lines)
        h = hashlib.sha1(t.encode()).hexdigest()
        if h not in cache:
            f = os.path.join(work, "%s_%s_%d.c" % (a.func, h[:12], threading.get_ident()))
            open(f, "w").write(t)
            try:
                cache[h] = ccheck.score(f, a.prog, a.func, work)
            finally:
                os.unlink(f)
        return cache[h]

    cur = open(a.src).read().split("\n")
    best = score(cur)
    if best is None:
        sys.exit("%s does not compile (or %s is not in it)" % (a.src, a.func))
    print("start: %d words off" % best, flush=True)
    ex = cf.ThreadPoolExecutor(a.j)

    def run(cands, label):
        nonlocal best, cur
        found = None
        futs = {ex.submit(score, c): (c, d) for c, d in cands}
        for f in cf.as_completed(futs):
            s = f.result()
            c, d = futs[f]
            if s is not None and s < best:
                best, found = s, (c, d)
                open(out, "w").write("\n".join(c))
                print("%d words off: %s %s -> %s" % (s, label, d, out), flush=True)
                if s == 0:
                    for g in futs:
                        g.cancel()
                    break
        if found:
            cur = found[0]
        return found is not None

    if a.slots:
        first, last = body_range(cur, a.func)
        idx = [i for i in range(first, last + 1) if cur[i].rstrip().endswith("//P")]
        body = [cur[i] for i in idx]
        cands = []
        for perm in itertools.islice(itertools.permutations(range(len(idx))), 1, a.max_pairs + 1):
            ls = list(cur)
            for slot, j in zip(idx, perm):
                ind = cur[slot][:len(cur[slot]) - len(cur[slot].lstrip())]
                ls[slot] = ind + body[j].strip()
            order = list(range(len(cur)))
            for slot, j in zip(idx, perm):
                order[slot] = idx[j]
            if a.unsafe or legal(cur, first, last, order):
                cands.append((ls, perm))
        run(cands, "order")
    else:
        while best:
            first, last = body_range(cur, a.func)
            marked = [i for i in range(first, last + 1) if cur[i].rstrip().endswith("//P")]
            if not marked:
                sys.exit("no line of %s ends with //P" % a.func)
            pos = range(first, last + 2)
            ok = lambda mv: a.unsafe or legal(cur, first, last, new_order(len(cur), mv))
            singles = [(move(cur, first, last, [(i, p)]), "line %d before %d" % (i + 1, p + 1))
                       for i in marked for p in pos if p not in (i, i + 1) and ok([(i, p)])]
            if run(singles, "move"):
                continue
            pairs = []
            for i, k in itertools.combinations(marked, 2):
                for p in pos:
                    if p in (i, i + 1) or abs(p - i) > a.window:
                        continue
                    for q in pos:
                        if q in (k, k + 1) or abs(q - k) > a.window or not ok([(i, p), (k, q)]):
                            continue
                        pairs.append((move(cur, first, last, [(i, p), (k, q)]),
                                      "lines %d, %d before %d, %d" % (i + 1, k + 1, p + 1, q + 1)))
            if not run(pairs[:a.max_pairs], "move"):
                break
    ex.shutdown(cancel_futures=True)
    print("best: %d words off%s" % (best, (" (%s)" % out) if os.path.exists(out) else ""))
    try:
        os.rmdir(work)
    except OSError:
        pass


if __name__ == "__main__":
    main()

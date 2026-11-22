#!/usr/bin/env python3
"""Variant tester: several versions of one function in one file, words off for each.

  python3 -I tools/variants.py FILE.c FUNC [--prog main] [-j N] [--set 'k=a|b|c' ...] [--alts K=ALTS.txt ...]
      [--write] [--sbs]

FILE.c holds a common head (includes, externs, helpers), then the variants, each starting with a line `//--`
(optionally `//-- a label`). Variant i is compiled as head + variant i and scored with tools/ccheck.py score()
(0 = match). With --set, `{k}` placeholders in the file are also expanded to every combination of the given
values (`\\n` in a value is a newline), for each variant; with --alts K=ALTS.txt, `{K}` is expanded to each block of
ALTS.txt, blocks separated by lines `@@` (multi-line statements; a placeholder on a line of its own takes the block
as lines). --write saves the best variant as FILE.best.c; --sbs
prints the side-by-side diff of the best one (tools/sbs.py).
"""
import argparse, concurrent.futures as cf, itertools, os, re, subprocess, sys, tempfile

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))
import ccheck


def split(text):
    """(head, [(label, text)]) of a file with `//--` separator lines (no separator: one variant, the file)."""
    parts = re.split(r"(?m)^//--[ \t]*(.*)\n", text)
    if len(parts) == 1:
        return "", [("", text)]
    head = parts[0]
    return head, [(parts[i].strip(), parts[i + 1]) for i in range(1, len(parts), 2)]


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("src")
    ap.add_argument("func")
    ap.add_argument("--prog", default="main")
    ap.add_argument("-j", type=int, default=os.cpu_count())
    ap.add_argument("--set", action="append", default=[], help="k=v1|v2|...: expand {k} to each value")
    ap.add_argument("--alts", action="append", default=[],
                    help="K=FILE: expand {K} to each alternative of FILE (alternatives separated by lines `@@`)")
    ap.add_argument("--write", action="store_true", help="save the best variant as FILE.best.c")
    ap.add_argument("--sbs", action="store_true", help="side-by-side diff of the best variant")
    a = ap.parse_args()
    head, vs = split(open(a.src).read())
    keys, vals = [], []     # vals: per key, [(text, label)]
    for s in a.set:
        k, v = s.split("=", 1)
        keys.append(k)
        vals.append([(x.replace("\\n", "\n"), x) for x in v.split("|")])
    for s in a.alts:      # file mode: multi-line alternatives, labelled by their number in the file
        k, f = s.split("=", 1)
        keys.append(k)
        blocks = [x for x in re.split(r"(?m)^@@[ \t]*\n", open(f).read() + "\n") if x.strip()]
        vals.append([(x.strip("\n"), "#%d" % n) for n, x in enumerate(blocks)])
    jobs = []
    for i, (label, body) in enumerate(vs):
        for combo in itertools.product(*vals):
            t = head + body
            for k, (v, _) in zip(keys, combo):
                # a placeholder alone on its line takes a multi-line block with that line's indentation
                ind = lambda m: "\n".join(m.group(1) + l if l.strip() else l for l in v.split("\n"))
                t = re.sub(r"(?m)^([ \t]*)\{%s\}[ \t]*$" % re.escape(k), ind, t)
                t = t.replace("{%s}" % k, v)
            name = "%d" % i + (" %s" % label if label else "") + \
                   ("".join(" %s=%s" % (k, lb) for k, (_, lb) in zip(keys, combo)))
            if all(t != j[1] for j in jobs):   # a variant without the placeholders once
                jobs.append((name, t))
    work = tempfile.mkdtemp(prefix="tmp_variants_", dir=os.path.join(ROOT, "build"))

    def run(job):
        f = os.path.join(work, "v%d.c" % id(job))
        open(f, "w").write(job[1])
        return ccheck.score(f, a.prog, a.func, work)
    try:
        with cf.ThreadPoolExecutor(a.j) as ex:
            res = list(ex.map(run, jobs))
        for (name, _), s in zip(jobs, res):
            print("%-8s %s" % ("MATCH" if s == 0 else ("error" if s is None else "%d off" % s), name), flush=True)
        ok = [(s, i) for i, s in enumerate(res) if s is not None]
        if not ok:
            sys.exit("no variant compiles")
        s, i = min(ok)
        print("best: %s (%s)" % (jobs[i][0], "match" if s == 0 else "%d words off" % s))
        if a.write:
            out = re.sub(r"\.c$", "", os.path.abspath(a.src)) + ".best.c"
            open(out, "w").write(jobs[i][1])
            print("written " + out)
        if a.sbs and s:
            f = os.path.join(work, "best.c")
            open(f, "w").write(jobs[i][1])
            subprocess.run([sys.executable, "-I", os.path.join(ROOT, "tools", "sbs.py"), f, a.func, "--prog", a.prog])
    finally:
        subprocess.run(["rm", "-rf", work])


if __name__ == "__main__":
    main()

#!/usr/bin/env python3
"""Tombi! 1's matched C (Tombi-Decomp, MIT) compiled with Tomba! 2's game pipeline and compared with every pending
function of the 29 programs.

  python3 -I tools/t1sweep.py [--t1 ../afsenovilla/tombi-decomp] [--files SUBSTR,...] [-j N] [--ratio 0.8]
      [--max-off 16] [--csv build/t1sweep.csv] [--keep]

Tombi-Decomp (github.com/afsenovilla/Tombi-Decomp, MIT) holds one C file per function: src/*.c (MAIN0.EXE, game code
and the Psy-Q library) and src/<overlay>/*.c. Its game files are taken (the library range of MAIN0.EXE,
0x8005B934..0x800E0000, and src/data / src/wip are left out; per-version copies `NAME_<serial>.c` only when NAME.c is
missing, preprocessed for that version), preprocessed with T1's headers (copied to a temporary build/t1sweep/inc in
both name cases, as T1's tools/matchcheck.py does, removed at the end unless --keep) and compiled as T2's game code
(gcc 2.8.1 + maspsx 2.79, `-O2 -G0 -funsigned-char`: T1's own `// CC` / `// FLAGS` / `// AS` lines are ignored; T1
itself was built with gcc 2.7.2). Every function of each object is compared by masked words (tools/funcstats.mask:
call targets, lui and non-$sp load / store / addiu offsets hidden) with every pending function (INCLUDE_ASM of
src/<prog>/<prog>.c) of the same length (words off) and, for lengths within 15 %, by difflib ratio (words off = the
unmatched words plus the length difference); a numpy opcode-histogram bound prunes the ratio pairs.

build/t1sweep.csv: one row per compiled T1 function with its closest pending T2 function (t1 file, t1 function,
words, prog, t2 name, words, words off, ratio), best first; the summary printed gives the failed files (first
error), the distribution of best matches and the closest pairs. A pair within a few words is a candidate for
tools/ccheck.py / tools/install_c.py after the T1 C is adapted (T2 names from the relocations as
tools/nearcopy.py fix_names does, T2 constants); a high ratio with more words off is hand work.
"""
import argparse, collections, concurrent.futures as cf, csv, difflib, glob, os, pickle, re, shutil, struct, subprocess, \
    sys, tempfile

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))
import cc
from funcstats import mask

T1_DEFAULT = os.path.join(os.path.dirname(ROOT), "afsenovilla", "tombi-decomp")
LIB_LO, LIB_HI = 0x8005B934, 0x800E0000          # Psy-Q library range of T1's MAIN0.EXE
SKIP_DIRS = {"data", "wip"}
VSUFFIX = re.compile(r"^(\w+?)_(scus94236|slps01144|slpm80165|pcpx96084|pcpx96093|slpm80186|slpm80167|papx90023|"
                     r"sces01330|beta980203)$")
GAME = dict(cc.DEFAULT)
CPP = os.path.join(cc.OLDGCC, GAME["cc"], "cpp")


def t1_files(t1, only):
    """[(path, version define)] of T1's game C files."""
    out = []
    for f in sorted(glob.glob(os.path.join(t1, "src", "*.c")) + glob.glob(os.path.join(t1, "src", "*", "*.c"))):
        rel = os.path.relpath(f, os.path.join(t1, "src"))
        if os.path.dirname(rel) in SKIP_DIRS:
            continue
        if only and not any(o in rel for o in only):
            continue
        head = open(f, errors="replace").read(400)
        base = os.path.basename(f)[:-2]
        ver = "VERSION_SCES_01331"
        m = VSUFFIX.match(base)
        if m:
            if os.path.exists(os.path.join(os.path.dirname(f), m.group(1) + ".c")):
                continue
            v = re.search(r"^//\s*VERSION\s+(\w+)", head, re.M)
            if v:
                ver = "VERSION_" + v.group(1)
        fn = re.search(r"^//\s*FUNC\s+([0-9a-fA-F]+)\s+\d+\s*(\w+)?", head, re.M)
        if fn and os.path.dirname(rel) == "" and LIB_LO <= int(fn.group(1), 16) < LIB_HI:
            continue
        if re.search(r"^//\s*AS\S*\s+gnu", head, re.M):
            continue                                    # T1's library recipe
        out.append((f, ver))
    return out


def make_inc(t1, dst):
    """T1's include tree with every top-level header under its own, upper and lower case name."""
    shutil.rmtree(dst, ignore_errors=True)
    os.makedirs(dst)
    inc = os.path.join(t1, "include")
    for f in os.listdir(inc):
        p = os.path.join(inc, f)
        if os.path.isdir(p):
            shutil.copytree(p, os.path.join(dst, f))
            continue
        for nm in {f, f.upper(), f.lower()}:
            shutil.copy(p, os.path.join(dst, nm))
    # T1's psyq/ headers come from its set-up (not in its repo): T2's include/psyq (Psy-Q 4.4) stands in, last
    return [dst, os.path.join(dst, "tomba"), os.path.join(ROOT, "include")]


def obj_funcs(obj):
    """{name: masked word tuple} of the functions in an object's .text."""
    b = obj + ".bin"
    subprocess.run(["mipsel-linux-gnu-objcopy", "-O", "binary", "-j", ".text", obj, b], check=True)
    text = open(b, "rb").read() if os.path.exists(b) else b""
    out = {}
    for l in subprocess.run(["mipsel-linux-gnu-nm", "-S", "--defined-only", obj], capture_output=True,
                            text=True).stdout.splitlines():
        p = l.split()
        if len(p) == 4 and p[2] in "Tt" and not p[3].startswith("__maspsx"):
            off, size = int(p[0], 16), int(p[1], 16)
            n = size // 4
            if n:
                out[p[3]] = tuple(mask(w) for w in struct.unpack("<%dI" % n, text[off:off + n * 4]))
    return out


def compile_one(job):
    f, ver, incs, work = job
    d = tempfile.mkdtemp(dir=work)
    try:
        src = os.path.join(d, "x.c")
        r = subprocess.run([CPP, "-undef", "-D__GNUC__=2", "-DMIPSEL", "-D_LANGUAGE_C", "-DSKIP_ASM", "-D" + ver] +
                           ["-I" + i for i in incs] + [f, src], capture_output=True, text=True)
        if r.returncode:
            return f, None, "cpp: " + (r.stderr.strip().splitlines() or ["?"])[-1][:200]
        try:
            cc.compile_c(src, os.path.join(d, "x.o"), dict(GAME))
        except cc.CompileError as e:
            lines = [l for l in str(e).splitlines() if "error" in l.lower() or "x.c:" in l] or str(e).splitlines()
            return f, None, "cc: " + (lines[0] if lines else "?")[:200]
        return f, obj_funcs(os.path.join(d, "x.o")), ""
    finally:
        shutil.rmtree(d, ignore_errors=True)


def pending_all(matched=False):
    """[(prog, name, masked key)] of every pending game function (INCLUDE_ASM in src/<prog>/<prog>.c); matched:
    every function of the programs (a positive control: T1 code T2 has in C already shows up)."""
    import nearcopy as N
    out = []
    for prog in N.progs_list():
        try:
            tp = N.Prog(prog)
        except Exception as e:                          # no asm / retail file: say so and go on
            print("t1sweep: %s skipped (%s)" % (prog, e))
            continue
        for name in sorted(tp.funcs if matched else tp.pending):
            if name in tp.funcs:
                out.append((prog, name, tp.key(name)))
    return out


def opclass(w):
    op = w >> 26
    return 64 + (w & 63) if op == 0 else op


def compare_all(t1, pend, ratio, workers):
    """per T1 function: (words off, ratio, prog, name, t2 words) of the closest pending function by words off, and
    (ratio, prog, name) of the one with the highest difflib ratio (any length within 15 %)."""
    import numpy as np
    H = np.zeros((len(pend), 128), dtype=np.int32)
    for i, (_, _, k) in enumerate(pend):
        for w in k:
            H[i, opclass(w)] += 1
    lens = np.array([len(p[2]) for p in pend])
    bylen = collections.defaultdict(list)
    for i, p in enumerate(pend):
        bylen[len(p[2])].append(i)
    res = {}
    for tk, key in t1.items():
        n = len(key)
        best = (10 ** 6, 0.0, "", "", 0)
        top = (0.0, "", "")
        for i in bylen.get(n, ()):
            nd = sum(1 for x, y in zip(key, pend[i][2]) if x != y)
            r = 1 - nd / n
            if nd < best[0]:
                best = (nd, r, pend[i][0], pend[i][1], n)
            if nd * 4 <= n and r > top[0]:
                top = (difflib.SequenceMatcher(None, key, pend[i][2], autojunk=False).ratio(), pend[i][0], pend[i][1])
        if n >= 6:
            h = np.zeros(128, dtype=np.int32)
            for w in key:
                h[opclass(w)] += 1
            sel = (lens >= int(n * 0.85)) & (lens <= int(n * 1.15) + 1) & (lens != n)
            bound = 2 * np.minimum(H, h).sum(1) / (lens + n)
            for i in np.nonzero(sel & (bound >= ratio))[0]:
                k2 = pend[i][2]
                sm = difflib.SequenceMatcher(None, key, k2, autojunk=False)
                if sm.quick_ratio() < ratio:
                    continue
                r = sm.ratio()
                if r > top[0]:
                    top = (r, pend[i][0], pend[i][1])
                if r < ratio:
                    continue
                nd = max(n, len(k2)) - sum(b.size for b in sm.get_matching_blocks())
                if (nd, -r) < (best[0], -best[1]):
                    best = (nd, r, pend[i][0], pend[i][1], len(k2))
        res[tk] = best + top
    return res


def compile_t1(a):
    """compile every T1 game file -> ({(file, function): masked key}, [(file, error)], files tried)."""
    files = t1_files(a.t1, a.files.split(",") if a.files else None)
    work = os.path.join(ROOT, "build", "t1sweep")
    incs = make_inc(a.t1, os.path.join(work, "inc"))
    tmp = tempfile.mkdtemp(dir=work, prefix="tmp")
    print("t1sweep: %d T1 game files" % len(files))
    t1, failed = {}, []
    try:
        with cf.ProcessPoolExecutor(a.j) as ex:
            for i, (f, fs, err) in enumerate(ex.map(compile_one, [(f, v, incs, tmp) for f, v in files],
                                                    chunksize=8)):
                rel = os.path.relpath(f, os.path.join(a.t1, "src"))
                if fs is None:
                    failed.append((rel, err))
                else:
                    for fn, k in fs.items():
                        t1[(rel, fn)] = k
                if i % 1000 == 999:
                    print("  %d / %d compiled" % (i + 1, len(files)), flush=True)
    finally:
        shutil.rmtree(tmp, ignore_errors=True)
        if not a.keep:
            shutil.rmtree(work, ignore_errors=True)
    return t1, failed, len(files)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--t1", default=T1_DEFAULT)
    ap.add_argument("--files", help="only T1 files whose path (under src/) contains one of these")
    ap.add_argument("-j", type=int, default=os.cpu_count() or 4)
    ap.add_argument("--ratio", type=float, default=0.8)
    ap.add_argument("--max-off", type=int, default=16, help="closest pairs listed up to this many words off")
    ap.add_argument("--csv", default=os.path.join(ROOT, "build", "t1sweep.csv"))
    ap.add_argument("--keep", action="store_true", help="keep build/t1sweep/inc")
    ap.add_argument("--matched", action="store_true", help="compare with every T2 function, matched ones too")
    ap.add_argument("--reuse", action="store_true", help="reuse the compiled T1 keys of the last run "
                    "(build/t1sweep_keys.pickle) instead of compiling again")
    a = ap.parse_args()
    cache = os.path.join(ROOT, "build", "t1sweep_keys.pickle")
    if a.reuse and os.path.exists(cache):
        t1, failed, nfiles = pickle.load(open(cache, "rb"))
    else:
        t1, failed, nfiles = compile_t1(a)
        pickle.dump((t1, failed, nfiles), open(cache, "wb"))
    print("t1sweep: %d files compiled (%d functions), %d failed" % (nfiles - len(failed), len(t1), len(failed)))
    errs = collections.Counter(re.sub(r"\S*x\.c:\d+:\s*", "", e)[:90] for _, e in failed)
    for e, c in errs.most_common(12):
        print("  %5d  %s" % (c, e))
    pend = pending_all(a.matched)
    print("t1sweep: %d %sT2 functions" % (len(pend), "" if a.matched else "pending "))
    keys = sorted(t1)
    chunks = [keys[i::a.j] for i in range(a.j)]
    res = {}
    with cf.ProcessPoolExecutor(a.j) as ex:
        for r in ex.map(compare_all, [{k: t1[k] for k in c} for c in chunks], [pend] * a.j, [a.ratio] * a.j,
                        [a.j] * a.j):
            res.update(r)
    rows = sorted(((v[0], -v[1], k, v) for k, v in res.items() if v[2]), key=lambda x: (x[0], x[1]))
    os.makedirs(os.path.dirname(a.csv), exist_ok=True)
    with open(a.csv, "w", newline="") as fh:
        w = csv.writer(fh)
        w.writerow(["t1_file", "t1_func", "t1_words", "prog", "t2_name", "t2_words", "words_off", "ratio",
                    "top_ratio", "top_prog", "top_name"])
        for nd, _, (rel, fn), v in rows:
            w.writerow([rel, fn, len(t1[(rel, fn)]), v[2], v[3], v[4], nd, "%.3f" % v[1], "%.3f" % v[5], v[6], v[7]])
    big = [x for x in rows if len(t1[x[2]]) >= 8]
    print("t1sweep: best match per T1 function of 8 words or more (%d of %d with any pair):" % (len(big), len(rows)))
    for lo, hi in ((0, 0), (1, 4), (5, 16)):
        print("  %2d-%-2d words off: %d" % (lo, hi, sum(1 for x in big if lo <= x[0] <= hi)))
    for r in (0.9, 0.8, 0.7, 0.6):
        print("  difflib ratio >= %.1f (any length within 15 %%): %d" % (r, sum(1 for x in big if x[3][5] >= r)))
    print("highest ratios (T1 file / function -> T2 prog name, ratio):")
    for x in sorted(big, key=lambda x: -x[3][5])[:12]:
        print("  %-48s %-28s -> %-4s %-36s %.3f" % (x[2][0], x[2][1], x[3][6], x[3][7], x[3][5]))
    seen = set()
    print("closest pairs (T1 file / function -> T2 prog name, words, off, ratio):")
    for nd, _, (rel, fn), v in big:
        if nd > a.max_off or (v[2], v[3]) in seen:
            continue
        seen.add((v[2], v[3]))
        print("  %-48s %-28s -> %-4s %-36s %4d %3d %.3f" % (rel, fn, v[2], v[3], v[4], nd, v[1]))
    print("wrote", os.path.relpath(a.csv, ROOT))


if __name__ == "__main__":
    main()

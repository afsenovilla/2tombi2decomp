#!/usr/bin/env python3
"""Sweep: draft every not-yet-decompiled function of a program with m2c (tools/decomp.py) and keep the drafts that
match the retail bytes as they come out.

  python3 -I tools/sweep.py [--prog main] [--max-size 0x80] [--install] [-j N]

Prints the matching names; --install replaces their INCLUDE_ASM lines in src/<prog>/*.c (the function plus the `extern`
declarations of the globals it uses; calls to functions without a prototype are left implicit) and then runs tools/build.py <prog> --no-split: if the linked
build is not OK, src is restored.
"""
import argparse, concurrent.futures as cf, glob, os, re, shutil, subprocess, sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))
import decomp as D


def prog_context(prog):
    """m2c context: the project headers plus every pending function's guessed parameter count (tools/arity.py)."""
    base = open(D.context()).read()
    subprocess.run([sys.executable, "-I", os.path.join(ROOT, "tools", "arity.py"), prog], cwd=ROOT,
                   capture_output=True)
    ar = os.path.join(ROOT, "build", "arity_%s.h" % prog)
    extra = open(ar).read() if os.path.exists(ar) else ""
    out = os.path.join(ROOT, "build", "ctx_%s.c" % prog)
    open(out, "w").write(base + "\ntypedef int M2C_UNK;\n" + extra)
    return out


def pending(prog):
    out = []
    for f in glob.glob(os.path.join(ROOT, "src", prog, "**", "*.c"), recursive=True):
        out += re.findall(r'INCLUDE_ASM\("[^"]+", (\w+)\);', open(f).read())
    return out


def size_of(prog, name):
    t = open(D.find_asm(prog, name)).read()
    m = re.search(r"^nonmatching \w+,\s*(0x\w+)", t, re.M)
    return int(m.group(1), 16) if m else 1 << 30   # data words splat found in the text (dlabel): never drafted


SCRATCH = re.compile(r"\(([\w ]+?\s*\*+)\s*\)\s*0x(1F8[0-9A-Fa-f]{5})\b")


def scratch_variants(body):
    """m2c writes scratchpad variables as constant addresses (`*(s32 *)0x1F8000E0`), which gcc reaches through $at;
    the game's source had symbols there (lui into a register). Variants with `(T *)D_1F8xxxxx` (declared
    `extern s8 D_1F8xxxxx[]`, config/scratchpad.ld), plain and volatile."""
    names = sorted(set(m.group(2).upper() for m in SCRATCH.finditer(body)))
    if not names:
        return []
    out = []
    for vol in ("", "volatile "):
        def rep(m):
            t = m.group(1).strip()
            return "((%s%s)D_%s)" % (vol, t, m.group(2).upper())
        b = SCRATCH.sub(rep, body)
        decl = "".join("extern s8 D_%s[];\n" % n for n in names)
        out.append(decl + b)
    return out


def fill_args(body, name):
    """m2c leaves unused leading parameters out (`f(void *arg1)` for a function that only reads $a1): put dummy
    `s32 argN` back for every missing lower index so the others land in the right registers."""
    m = re.search(r"\b%s\(([^)]*)\)\s*\{" % re.escape(name), body)
    if not m or not m.group(1).strip() or m.group(1).strip() == "void":
        return body
    params = [p.strip() for p in m.group(1).split(",")]
    idx = []
    for p in params:
        a = re.search(r"\barg(\d+)\s*$", p)
        if not a:
            return body
        idx.append(int(a.group(1)))
    if idx == list(range(len(idx))):
        return body
    full = []
    for i in range(max(idx) + 1):
        full.append(params[idx.index(i)] if i in idx else "s32 arg%d" % i)
    return body[:m.start(1)] + ", ".join(full) + body[m.end(1):]


def attempt(prog, name, ctx, m2c_opts=()):
    r = subprocess.run([sys.executable, D.M2C, "--target", "mipsel-gcc-c", "--valid-syntax", "--context", ctx] +
                       list(m2c_opts) + [D.find_asm(prog, name)],
                       capture_output=True, text=True, cwd=ROOT)
    if r.returncode or not r.stdout.strip() or "Decompilation failure" in r.stdout:
        return name, None
    body0 = fill_args(re.sub(r"(?m)^(extern )?\? ", r"\1s32 ", r.stdout), name)
    d = os.path.join(ROOT, "build", "sweep")
    os.makedirs(d, exist_ok=True)
    test = os.path.join(d, name + ".c")
    vol = re.sub(r"(?m)^extern (?!volatile)([^;(]*;)$", r"extern volatile \1", body0)
    for body in [body0] + scratch_variants(body0) + ([vol] if vol != body0 else []):
        open(test, "w").write('#include "common.h"\n#include "game.h"\n#include "m2c.h"\n' + body)
        c = subprocess.run([sys.executable, "-I", os.path.join(ROOT, "tools", "ccheck.py"), test, "--prog", prog,
                            "--func", name], capture_output=True, text=True, cwd=ROOT)
        if c.returncode == 0 and c.stdout.startswith("OK"):
            break
    if c.returncode == 0 and c.stdout.startswith("OK"):
        fn = re.search(r"(?ms)^[^\n]*\b%s\(.*?^}\n" % re.escape(name), body)
        if not fn:
            return name, None
        # the globals it uses, declared just before it (file scope; a type clash with another draft fails the build)
        ext = [l for l in body.splitlines() if l.startswith("extern ")]
        return name, "\n".join(ext + ([""] if ext else []) + [fn.group(0).rstrip()])
    return name, None


M2C_VARIANTS = [(), ("--descending-regs",), ("--no-andor",), ("--no-andor", "--descending-regs")]


def attempt_all(prog, name, ctx, many):
    for opts in (M2C_VARIANTS if many else M2C_VARIANTS[:1]):
        r = attempt(prog, name, ctx, opts)
        if r[1]:
            return r
    return name, None


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--prog", default="main")
    ap.add_argument("--max-size", default="0x80")
    ap.add_argument("--install", action="store_true")
    ap.add_argument("-j", type=int, default=os.cpu_count())
    ap.add_argument("--m2c-variants", action="store_true", help="also try m2c's --descending-regs / --no-andor drafts")
    a = ap.parse_args()
    lim = int(a.max_size, 0)
    names = [n for n in pending(a.prog) if size_of(a.prog, n) <= lim]
    ctx = prog_context(a.prog)
    with cf.ThreadPoolExecutor(a.j) as ex:
        res = [r for r in ex.map(lambda n: attempt_all(a.prog, n, ctx, a.m2c_variants), names) if r[1]]
    print("%d / %d functions <= 0x%X match as drafted" % (len(res), len(names), lim))
    for n, _ in res:
        print("  " + n)
    if not a.install or not res:
        return
    files = glob.glob(os.path.join(ROOT, "src", a.prog, "**", "*.c"), recursive=True)
    backup = {f: open(f).read() for f in files}
    decl = {}   # global name -> its extern line; a clashing draft gets the global under another name (an alias)
    hdrs = [open(h).read() for h in glob.glob(os.path.join(ROOT, "include", "*.h"))]
    for t in list(backup.values()) + hdrs:
        for l in re.findall(r"(?m)^extern [^;(]*?\b(\w+)(?:\[[^\]]*\])?;", t):
            pass
        for m in re.finditer(r"(?m)^(extern [^;(]*?\b(\w+)(?:\[[^\]]*\])?;)", t):
            decl[m.group(2)] = m.group(1)
    keep = []
    sys.path.insert(0, os.path.join(ROOT, "tools"))
    import libsweep
    aliases = libsweep.read_aliases(a.prog)
    for n, fn in res:
        mine = {m.group(2): m.group(1) for m in re.finditer(r"(?m)^(extern [^;(]*?\b(\w+)(?:\[[^\]]*\])?;)", fn)}
        clash = [k for k, v in mine.items() if k in decl and decl[k] != v]
        bad = False
        for k in clash:
            am = re.fullmatch(r"(?:D|func)_([0-9A-F]{8})", k)
            if not am:
                bad = True; break
            import hashlib
            new = "%s_%s" % (k, hashlib.sha1(mine[k].encode()).hexdigest()[:4])
            fn = re.sub(r"\b%s\b" % k, new, fn)
            aliases[new] = int(am.group(1), 16)
            mine[new] = mine.pop(k).replace(k, new)
        if bad:
            print("  skipped (type clash with an earlier declaration): " + n)
            continue
        decl.update(mine)
        keep.append((n, fn))
    res = keep
    libsweep.write_aliases(a.prog, aliases)
    def build_ok():
        b = subprocess.run([sys.executable, os.path.join(ROOT, "tools", "build.py"), a.prog, "--no-split"],
                           capture_output=True, text=True, cwd=ROOT)
        return " OK " in b.stdout

    def put(pairs):
        for f in files:
            t = backup[f]
            for n, fn in pairs:
                t = t.replace('INCLUDE_ASM("asm/%s/nonmatchings/%s", %s);' % (a.prog, a.prog, n), fn)
            open(f, "w").write(t)

    put(res)
    if not build_ok():   # find the drafts that break the link (e.g. new rodata) one at a time
        good = []
        for p in res:
            put(good + [p])
            if build_ok():
                good.append(p)
            else:
                print("  left out (linked build differs): " + p[0])
        put(good)
        res = good
        if not build_ok():
            put([])
            sys.exit("linked build not OK, src restored")
    print("installed %d functions; linked build OK" % len(res))


if __name__ == "__main__":
    main()

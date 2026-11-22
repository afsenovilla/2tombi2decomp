#!/usr/bin/env python3
"""Install hand-written C (a scratch file of matched functions, checked with tools/ccheck.py) into src/<prog>/<prog>.c.

  python3 -I tools/install_c.py FILE.c [--prog main]

Each function replaces its INCLUDE_ASM line; the file's other top-level lines (types, externs, prototypes; not the
#include lines) go just before the first installed function, skipping lines already present in the target. Then the
linked build must be OK (tools/build.py <prog> --no-split), else the target is restored. Types that several programs
need belong in include/*.h instead. Symbols the file names after another program (C copied from an overlay) are
first renamed to this program's names for the addresses the retail bytes give them (tools/nearcopy.py
fix_names(); a D_ address no file labels gets an alias line).
"""
import argparse, os, re, subprocess, sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))
import ptsrc


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("src")
    ap.add_argument("--prog", default="main")
    a = ap.parse_args()
    if os.environ.get("INSTALL_C_LOCKED") == a.prog:   # the one-at-a-time retries below run under our lock
        return install(a)
    # one installer per program at a time: the target .c and config/aliases_<prog>.ld are read, changed and maybe
    # restored, so two agents installing into the same program would undo each other's lines
    import fcntl
    os.makedirs(os.path.join(ROOT, "build"), exist_ok=True)
    with open(os.path.join(ROOT, "build", ".install_%s" % a.prog), "w") as lk:
        fcntl.flock(lk, fcntl.LOCK_EX)
        os.environ["INSTALL_C_LOCKED"] = a.prog
        return install(a)


def install(a):
    path = os.path.join(ROOT, "src", a.prog, a.prog + ".c")
    old = open(path).read()
    t = old
    text = open(a.src).read()
    # names another program uses for these addresses -> this program's (relocations read against retail)
    import nearcopy
    text, ren, new_aliases = nearcopy.fix_names(text, a.prog)
    if ren:
        print("renamed from the relocations: " + ", ".join("%s -> %s" % kv for kv in sorted(ren.items())))
    pre, funcs, includes = [], [], []
    for kind, seg in ptsrc.items(text):
        s = seg.strip()
        if not s:
            continue
        if kind == "pp" and s.startswith("#include"):
            if s not in t and not re.search(r'"(common|game|m2c|actor)\.h"', s):
                includes.append(s)   # e.g. psyq/inline_c.h for GTE macros: goes after the target's own includes
            continue
        n = ptsrc.func_name(s) if s.endswith("}") else None
        if n:
            funcs.append((n, s))
        else:
            pre.append(s)
    # a global the target declares with another type is used here under an alias name (config/aliases_<prog>.ld)
    import hashlib, libsweep
    aliases = libsweep.read_aliases(a.prog)
    aliases.update({k: v for k, v in new_aliases.items() if k not in aliases})
    decl_re = r"(?m)^(extern [^;(]*?\b(\w+)(?:\[[^\]]*\])*;)"
    theirs = {m.group(2): m.group(1) for m in re.finditer(decl_re, t)}
    for i, p in enumerate(pre):
        m = re.match(decl_re, p)
        if not m or m.group(2) not in theirs or theirs[m.group(2)] == m.group(1):
            continue
        k = m.group(2)
        am = re.fullmatch(r"(?:D|func)_([0-9A-F]{8})", k)
        if not am:
            sys.exit("%s is declared differently in %s; rename it by hand" % (k, path))
        new = "%s_%s" % (k, hashlib.sha1(p.encode()).hexdigest()[:4])
        aliases[new] = int(am.group(1), 16)
        pre[i] = re.sub(r"\b%s\b" % k, new, p)
        funcs = [(n, re.sub(r"\b%s\b" % k, new, b)) for n, b in funcs]
    ap_ = libsweep.aliases_path(a.prog)
    old_aliases = open(ap_).read() if os.path.exists(ap_) else None

    added = {k: v for k, v in aliases.items() if k not in libsweep.read_aliases(a.prog)}

    def restore_aliases():
        # only the lines this run added go: other lines may have come in meanwhile (merged, never a snapshot)
        cur = libsweep.read_aliases(a.prog)
        for k in added:
            cur.pop(k, None)
        if cur:
            libsweep.write_aliases(a.prog, cur)
        elif old_aliases is None and os.path.exists(ap_):
            os.remove(ap_)
    if added:
        cur = libsweep.read_aliases(a.prog)
        cur.update(added)
        libsweep.write_aliases(a.prog, cur)
    # a function that had equivalent C (tools/nonmatching.py) loses its whole NON_MATCHING block
    for n, _ in funcs:
        line = 'INCLUDE_ASM("asm/%s/nonmatchings/%s", %s);' % (a.prog, a.prog, n)
        t = re.sub(r"(?ms)^#ifdef NON_MATCHING\n(?:(?!^#endif).)*?^#else\n" + re.escape(line) + r"\n#endif$",
                   lambda m: line, t)
    lines = {}
    for n, body in funcs:
        line = 'INCLUDE_ASM("asm/%s/nonmatchings/%s", %s);' % (a.prog, a.prog, n)
        if line not in t:
            sys.exit("%s: no INCLUDE_ASM line for %s" % (path, n))
        lines[n] = (t.index(line), line)
    first = min(lines, key=lambda n: lines[n][0])     # the declarations go before the earliest function in the file
    before = t[:lines[first][0]]
    defined = set(re.findall(r"(?m)^[\w][\w \*]*?\b(\w+)\s*\([^;{}]*\)\s*\{", t))

    def wanted(p):
        if p in before:
            return False
        # prototypes are left out: the asm drafts call functions with the argument counts m2c saw (pass-through
        # arguments dropped), which a prototype would reject; calls compile the same without one
        m = re.match(r"[\w \*]+?\b(\w+)\s*\([^;{}]*\)\s*;$", p)
        if not m or p.startswith(("extern", "typedef")):
            return True
        # ... unless a function is used as a value (its address taken), which needs a declaration
        return any(re.search(r"\b%s\b(?!\s*\()" % m.group(1), b) for _, b in funcs)
    extra = [p for p in pre if wanted(p)]
    for p in extra:   # a declaration the file already has further down moves up to the new first use
        if p.startswith(("extern", "typedef", "struct", "union")) and p in t:
            t = t.replace(p + "\n", "", 1) if p + "\n" in t else t.replace(p, "", 1)
    for n, body in funcs:
        if n == first:
            body = "\n".join(extra + ([""] if extra else []) + [body])
        t = t.replace(lines[n][1], body)
    if includes:   # after the target's last #include line
        last = list(re.finditer(r"(?m)^#include .*$", t))
        at = last[-1].end() if last else 0
        t = t[:at] + "\n" + "\n".join(includes) + t[at:]
    open(path, "w").write(t)
    r = subprocess.run([sys.executable, "tools/build.py", a.prog, "--no-split"], capture_output=True, text=True,
                       cwd=ROOT)
    if " OK " not in r.stdout:
        open(path, "w").write(old)
        restore_aliases()
        if len(funcs) < 2:
            sys.exit("linked build not OK, restored:\n" + r.stdout + r.stderr[-2500:])
        # one function at a time: the others may still go in (a callee prototype in the target, for instance,
        # can change one function's code)
        print("linked build not OK with all %d; trying one at a time" % len(funcs))
        segs = ptsrc.items(text)
        done, failed = [], []
        for n, _ in funcs:
            one = "".join(seg for kind, seg in segs
                          if not (seg.strip().endswith("}") and ptsrc.func_name(seg.strip()) not in (None, n)))
            tmp = os.path.join(ROOT, "build", "install_one.c")
            open(tmp, "w").write(one)
            r = subprocess.run([sys.executable, "-I", os.path.abspath(__file__), tmp, "--prog", a.prog],
                               capture_output=True, text=True, cwd=ROOT)
            (done if "installed" in r.stdout else failed).append(n)
            if n in failed:
                print("  %s: %s" % (n, (r.stdout + r.stderr).strip().splitlines()[-1:]))
        print("installed %d functions: %s" % (len(done), " ".join(done)))
        if failed:
            sys.exit("not installed: " + " ".join(failed))
        return
    print("installed %d functions: %s" % (len(funcs), " ".join(n for n, _ in funcs)))


if __name__ == "__main__":
    main()

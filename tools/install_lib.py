#!/usr/bin/env python3
"""Install hand-written library C (a scratch file of matched Psy-Q functions) into the per-function library files
src/<prog>/psyq/<lib>/<name>.c, with the compiler set-up header that matches.

  python3 -I tools/install_lib.py FILE.c [--prog main] [--only NAME,...] [--auto] [--dry]

The scratch file's own set-up lines (// CC, // FLAGS, // ASPSX, // AS, // EPILOGUE, // RETURN, tools/cc.py) are
used when it has them; else (or with --auto) the set-ups of tools/libsweep.py VARIANTS + EPI_VARIANTS are tried in
order and the first that matches (tools/ccheck.py score) is written. Each function goes into the library file
whose INCLUDE_ASM names it (a file that holds more functions keeps the others), with the scratch's #include lines
and the declarations it uses (types, externs, prototypes, #defines, static inline helpers: a closure over the
identifiers). Names of another program (C copied from MAIN.EXE into boot) are renamed to this program's names for
the addresses the retail bytes give (tools/nearcopy.py fix_names(); unlabelled D_ addresses get an alias line).
Then the linked build (tools/build.py <prog> --no-split) must be OK, else the files are restored (one at a time when
several were installed). Takes the same per-program lock as tools/install_c.py.
K&R definitions (`s32 f(a, b) s32 a; u8 *b; {`) are functions like the others (tools/ptsrc.py items()). A scratch or
library file that includes a base header of its own (psyq_all.h, pt/common.h) does not get common.h added; extra
FLAGS of the scratch or of the library file being replaced (-fno-builtin, ...) are kept on every set-up tried.
The last line of a failure is `NOT INSTALLED: <names> (<reason>)`.
"""
import argparse, fcntl, glob, os, re, subprocess, sys, tempfile

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))
import ptsrc

SETUP = re.compile(r"^//\s*(CC|FLAGS|ASPSX|AS|EPILOGUE|RETURN)\s+.*$", re.M)
IDENT = re.compile(r"[A-Za-z_]\w*")


KW = ("extern", "const", "volatile", "static", "unsigned", "signed", "struct", "union", "typedef", "enum")


def split(text):
    """(set-up lines, #include lines, [(names, decl text)], {func: text}) of a scratch file."""
    setup = [m.group(0) for m in SETUP.finditer(text[:800])]
    includes, decls, funcs = [], [], {}
    # whole-line // comments outside braces go (they would glue the next #include to a declaration)
    keep, depth = [], 0
    for l in text.split("\n"):
        if depth == 0 and l.lstrip().startswith("//"):
            continue
        keep.append(l)
        depth += ptsrc.strip_comments(l).count("{") - ptsrc.strip_comments(l).count("}")
    text = "\n".join(keep)
    for kind, seg in ptsrc.items(text):
        s = seg.strip()
        if not s:
            continue
        s = "\n".join(l for l in s.split("\n") if not SETUP.match(l)).strip()
        s = re.sub(r"(?m)^//--.*\n?", "", s).strip()
        if not s:
            continue
        if kind == "pp":
            if s.startswith("#include"):
                includes.append(s)
            elif s.startswith(("#define", "#undef")):
                decls.append(([s.split()[1].split("(")[0]], s))
            continue
        n = ptsrc.func_name(s) if s.endswith("}") else None
        if n and not ptsrc.strip_comments(s).strip().startswith("static"):
            funcs[n] = s
        elif n:     # a static (inline) helper: a declaration of its name
            decls.append(([n], s))
        else:
            body = re.sub(r"\{.*\}", " ", s, flags=re.S)
            # a function pointer declared at file scope (not a function-pointer field inside a struct's braces)
            fp = re.findall(r"\(\s*\*\s*([A-Za-z_]\w*)\s*\)", body)
            if fp:
                names = fp[:1]
            elif re.search(r"\w\s*\(", body) and not s.startswith("typedef"):
                names = re.findall(r"([A-Za-z_]\w*)\s*\(", body)[:1]
            else:
                b = re.sub(r"\[[^\]]*\]|=.*", " ", body, flags=re.S)
                ids = [x for x in IDENT.findall(b) if x not in ("extern", "const", "volatile", "static", "unsigned",
                                                              "signed", "struct", "union", "typedef", "enum")]
                # every declarator of `extern T *a, *b;` (the last identifier of each comma-separated part)
                names = []
                for part in b.split(","):
                    pid = [x for x in IDENT.findall(part) if x not in KW]
                    if pid:
                        names.append(pid[-1])
                names = names or ids[-1:]
                if s.startswith(("struct", "union", "enum")) or re.match(r"typedef\s+(struct|union|enum)\s+\w+", s):
                    m = re.match(r"(?:typedef\s+)?(?:struct|union|enum)\s+(\w+)", s)
                    if m:
                        names.append(m.group(1))
            decls.append((names, s))
    return setup, includes, decls, funcs


def needed(body, name, decls):
    need, used = set(IDENT.findall(body)), []
    changed = True
    while changed:
        changed = False
        for names, c in decls:
            if c in used or name in names and not c.startswith("#"):
                continue
            if any(n in need for n in names):
                used.append(c)
                need |= set(IDENT.findall(c))
                changed = True
    return [c for _, c in decls if c in used]


BASE = re.compile(r'"(common|psyq_all|pt/common)\.h"')


def content(old, name, setup, includes, decls, body):
    rest = SETUP.sub("", old)
    own = re.findall(r"(?m)^#include .*$", rest)      # the library file's own includes stay (once, first)
    rest = re.sub(r"(?m)^#include .*\n", "", rest)
    rest = re.sub(r"(?m)^// (Source|Same function).*\n", "", rest).lstrip("\n")
    rest = re.sub(r'(?m)^INCLUDE_ASM\("[^"]+",\s*%s\);' % re.escape(name), lambda m: body, rest)
    inc = []
    for i in [x for x in own if not x.strip().endswith('"common.h"')] + includes:
        if i not in inc:
            inc.append(i)
    if not any(BASE.search(i) for i in inc):     # psyq_all.h / pt/common.h bring their own base types
        inc = ['#include "common.h"'] + inc
    elif any('"common.h"' in i for i in inc) and any(re.search(r'"(psyq_all|pt/common)\.h"', i) for i in inc):
        inc = [i for i in inc if '"common.h"' not in i]
    d = needed(body, name, decls)
    return "\n".join(setup) + "\n" + "\n".join(inc) + "\n" + ("\n".join(d) + "\n\n" if d else "\n") + rest


def extra_flags(*texts):
    """FLAGS tokens of the given files beyond the usual -O / -G / -mno-split-addresses (e.g. -fno-builtin)."""
    import libsweep as L
    usual = {f for v in L.VARIANTS + L.EPI_VARIANTS for f in v["flags"].split()}
    out = []
    for t in texts:
        for m in re.finditer(r"(?m)^//\s*FLAGS\s+(.*)$", t[:800]):
            for f in m.group(1).split():
                if f.startswith("-f") and f not in usual and f not in out:
                    out.append(f)
    return out


def with_flags(su, extra):
    out, seen = [], False
    for l in su:
        m = re.match(r"//\s*FLAGS\s+(.*)$", l)
        if m:
            seen = True
            l = "// FLAGS " + " ".join(m.group(1).split() + [f for f in extra if f not in m.group(1).split()])
        out.append(l)
    if not seen and extra:
        out.insert(1, "// FLAGS -O2 -G0 " + " ".join(extra))
    return out


def setups(fixed, auto, extra=()):
    import libsweep as L
    if fixed and not auto:
        return [with_flags(fixed, extra)]
    return [with_flags(L.header(v).strip().split("\n"), extra) for v in L.VARIANTS + L.EPI_VARIANTS]


def build_ok(prog):
    r = subprocess.run([sys.executable, "tools/build.py", prog, "--no-split"], capture_output=True, text=True, cwd=ROOT)
    return " OK " in r.stdout, r.stdout + r.stderr[-1500:]


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("src")
    ap.add_argument("--prog", default="main")
    ap.add_argument("--only", help="comma list of the functions to install")
    ap.add_argument("--auto", action="store_true", help="try the libsweep set-ups even when the file has its own")
    ap.add_argument("--dry", action="store_true", help="report what matches, change nothing")
    a = ap.parse_args()
    import ccheck, libsweep as L, nearcopy
    text = open(a.src).read()
    text, ren, new_aliases = nearcopy.fix_names(text, a.prog)
    if ren:
        print("renamed from the relocations: " + ", ".join("%s -> %s" % kv for kv in sorted(ren.items())))
    setup, includes, decls, funcs = split(text)
    files = L.pending_files(a.prog)
    os.makedirs(os.path.join(ROOT, "build"), exist_ok=True)
    lk = open(os.path.join(ROOT, "build", ".install_%s" % a.prog), "w")
    if not a.dry:
        fcntl.flock(lk, fcntl.LOCK_EX)
    done, failed = [], []
    work = tempfile.mkdtemp(prefix="tmp_install_lib_", dir=os.path.join(ROOT, "build"))
    try:
        for name, body in funcs.items():
            if a.only and name not in a.only.split(","):
                continue
            if name not in files:
                print("skip %s: no pending library file" % name)
                continue
            old = open(files[name]).read()
            hit = None
            for su in setups(setup, a.auto, extra_flags(text, old)):
                new = content(old, name, su, includes, decls, body)
                tmp = os.path.join(work, name + ".c")
                open(tmp, "w").write(new)
                if ccheck.score(tmp, a.prog, name, work) == 0:
                    hit = (su, new)
                    break
            if not hit:
                print("NO MATCH %s" % name)
                failed.append(name)
                continue
            print("match %s: %s -> %s" % (name, " | ".join(hit[0]), os.path.relpath(files[name], ROOT)))
            done.append((name, files[name], old, hit[1]))
        if a.dry or not done:
            if failed and not a.dry:
                print("NOT INSTALLED: %s (no set-up matches)" % " ".join(failed))
            return
        added = {k: v for k, v in new_aliases.items() if k not in L.read_aliases(a.prog)}
        if added:
            cur = L.read_aliases(a.prog)
            cur.update(added)
            L.write_aliases(a.prog, cur)
        for _, f, _, new in done:
            open(f, "w").write(new)
        ok, log = build_ok(a.prog)
        if ok:
            print("installed %d functions: %s" % (len(done), " ".join(n for n, *_ in done)))
            if failed:
                print("NOT INSTALLED: %s (no set-up matches)" % " ".join(failed))
            return
        for _, f, old, _ in done:
            open(f, "w").write(old)
        if len(done) == 1:
            restore_aliases(a.prog, added)
            print("linked build not OK, restored:\n" + log)
            print("NOT INSTALLED: %s (linked build not OK)" % " ".join([done[0][0]] + failed))
            sys.exit(1)
        kept = []
        for n, f, old, new in done:
            open(f, "w").write(new)
            if build_ok(a.prog)[0]:
                kept.append(n)
            else:
                open(f, "w").write(old)
                print("  %s: linked build not OK, left out" % n)
        if not kept:
            restore_aliases(a.prog, added)
        print("installed %d functions: %s" % (len(kept), " ".join(kept)))
        lost = [n for n, *_ in done if n not in kept] + failed
        if lost:
            print("NOT INSTALLED: %s (no match or linked build not OK)" % " ".join(lost))
    finally:
        subprocess.run(["rm", "-rf", work])


def restore_aliases(prog, added):
    import libsweep as L
    cur = L.read_aliases(prog)
    for k in added:
        cur.pop(k, None)
    if cur:
        L.write_aliases(prog, cur)
    elif os.path.exists(L.aliases_path(prog)):
        os.remove(L.aliases_path(prog))


if __name__ == "__main__":
    main()

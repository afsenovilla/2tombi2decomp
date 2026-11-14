#!/usr/bin/env python3
"""Copy matched C to the other programs' copies of the same function (the same masked word sequence: area overlays
carry many copies of shared code). The C of a matched function is compiled in place of the copy; when the bytes
match, the symbols it references are renamed to what the target program calls those addresses, and the result is
installed (src/<prog>/<prog>.c) when the linked build stays OK.

  python3 -I tools/dupsweep.py [--install] [--progs a00,a01,...]
"""
import argparse, collections, glob, os, re, shutil, struct, subprocess, sys, tempfile

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))
import cc, libsweep as L, ptsrc
from funcstats import mask, programs

PRELUDE = '#include "common.h"\n#include "game.h"\n#include "m2c.h"\n'


def c_functions(prog):
    """name -> (function text, extern lines before it) of the C definitions in src/<prog>/<prog>.c."""
    p = os.path.join(ROOT, "src", prog, prog + ".c")
    if not os.path.exists(p):
        return {}
    out, decls = {}, []
    segs = ptsrc.items(ptsrc.strip_comments(open(p).read()))
    for kind, seg in segs:   # every file-scope declaration (externs, types) is offered to each function
        s = seg.strip()
        if kind == "code" and not s.endswith("}") and (s.startswith(("extern ", "typedef ")) or
                                                        (s.startswith(("struct ", "union ")) and s.endswith("};"))):
            decls.append(s)
    for kind, seg in segs:
        s = seg.strip()
        if kind == "code" and s.endswith("}") and ptsrc.func_name(s):
            out[ptsrc.func_name(s)] = (s, decls)
    return out


def names_by_addr(prog):
    out = {}
    for p in [os.path.join(ROOT, "config", "symbol_addrs_%s.txt" % prog),
              os.path.join(ROOT, "build", "undefined_syms_auto.%s.txt" % prog),
              os.path.join(ROOT, "build", "undefined_funcs_auto.%s.txt" % prog),
              os.path.join(ROOT, "config", "aliases_%s.ld" % prog)]:
        if os.path.exists(p):
            for l in open(p):
                m = re.match(r"\s*(\w+)\s*=\s*0x([0-9A-Fa-f]+)", l)
                if m:
                    out.setdefault(int(m.group(2), 16), m.group(1))
    return out


GLOBAL_NAMES = set(re.findall(r"^\s*(\w+)\s*=", open(os.path.join(ROOT, "config", "undefined_syms.ld")).read(), re.M))


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--install", action="store_true")
    ap.add_argument("--progs")
    ap.add_argument("-v", action="store_true", help="print the build output of a copy that fails to link")
    a = ap.parse_args()
    progs = {p: (b, d, ts, te, ad) for p, b, d, ts, te, ad in programs()}
    sym = {}
    for p in progs:
        sym[p] = {}
        sp = os.path.join(ROOT, "config", "symbol_addrs_%s.txt" % p)
        for l in open(sp) if os.path.exists(sp) else []:
            m = re.match(r"\s*(\w+)\s*=\s*0x([0-9A-Fa-f]+)", l)
            if m:
                sym[p][m.group(1)] = int(m.group(2), 16)

    def key(p, start, end):
        b, d = progs[p][0], progs[p][1]
        fb = b[start - d:end - d]
        n = len(fb) // 4
        return tuple(mask(w) for w in struct.unpack("<%dI" % n, fb[:n * 4]))

    # every matched C function (game code) and its masked key
    sources = {}
    for p in progs:
        for name, (text, ext) in c_functions(p).items():
            ad = sym[p].get(name) or (int(name[5:], 16) if re.fullmatch(r"func_[0-9A-F]{8}", name) else None)
            if ad is None:
                continue
            addrs = progs[p][4]
            i = addrs.index(ad) if ad in addrs else None
            if i is None:
                continue
            end = addrs[i + 1] if i + 1 < len(addrs) else progs[p][3] + progs[p][1]
            sources.setdefault(key(p, ad, end), (p, name, text, ext))
    print("%d matched C functions to copy from" % len(sources))
    targets = [x for x in (a.progs.split(",") if a.progs else progs)]
    found = collections.defaultdict(list)
    for p in targets:
        src = os.path.join(ROOT, "src", p, p + ".c")
        if not os.path.exists(src):
            continue
        pend = set(re.findall(r'INCLUDE_ASM\("[^"]+", (\w+)\);', open(src).read()))
        nb = names_by_addr(p)
        b, d, ts, te, addrs = progs[p]
        addr_set = set(addrs)
        for i, ad in enumerate(addrs):
            end = addrs[i + 1] if i + 1 < len(addrs) else te + d
            try:
                name = L.asm_info(p, "x") and None
            except SystemExit:
                pass
            k = key(p, ad, end)
            if k not in sources:
                continue
            sp, sname, text, ext = sources[k]
            tname = nb.get(ad, "func_%08X" % ad)
            if tname not in pend:
                continue
            body = re.sub(r"\b%s\b" % re.escape(sname), tname, text)
            used = [e for e in ext if any(re.search(r"\b%s\b" % w, body) for w in
                                          re.findall(r"\b(\w+)\s*(?:\[[^\]]*\])?\s*;?$", e.rstrip(";"))[-1:])
                    or e.startswith(("typedef", "struct", "union"))]
            ext = used
            cand = PRELUDE + "\n".join(ext) + "\n" + body + "\n"
            t = tempfile.mkdtemp(dir=os.path.join(ROOT, "build"))
            try:
                open(t + "/x.c", "w").write(cand)
                cc.compile_c(t + "/x.c", t + "/a.o")
                syms = {}
                if not L.matches(t + "/a.o", tname, b[ad - d:end - d], syms):
                    continue
            except cc.CompileError:
                continue
            finally:
                shutil.rmtree(t, ignore_errors=True)
            # rename every referenced symbol to the target's name for that address (names the linker defines for
            # every program, config/undefined_syms.ld, and header-declared ones stay as they are)
            ren = {}
            for s_, at in syms.items():
                if s_ == tname or s_ in GLOBAL_NAMES:
                    continue
                want = nb.get(at) or ("func_%08X" % at if (at in addr_set or s_.startswith(("func_", "f_")))
                                      else "D_%08X" % at)
                if want != s_:
                    ren[s_] = want
            fn = body
            ex = list(ext)
            for s_, w in ren.items():
                fn = re.sub(r"\b%s\b" % re.escape(s_), w, fn)
                ex = [re.sub(r"\b%s\b" % re.escape(s_), w, e) for e in ex]
            found[p].append((tname, "\n".join(ex + [""] + [fn]) if ex else fn))
    print("found: " + ", ".join("%s %d" % (p, len(v)) for p, v in found.items()))
    if not a.install:
        return
    for p, items in found.items():
        path = os.path.join(ROOT, "src", p, p + ".c")
        old = open(path).read()
        t = old
        for n, fn in items:
            t = t.replace('INCLUDE_ASM("asm/%s/nonmatchings/%s", %s);' % (p, p, n), fn)
        open(path, "w").write(t)
        r = subprocess.run([sys.executable, "tools/build.py", p, "--no-split"], capture_output=True, text=True, cwd=ROOT)
        if " OK " in r.stdout:
            print("%s: installed %d" % (p, len(items)))
            continue
        good = []
        for n, fn in items:   # one at a time
            t = old
            for gn, gfn in good + [(n, fn)]:
                t = t.replace('INCLUDE_ASM("asm/%s/nonmatchings/%s", %s);' % (p, p, gn), gfn)
            open(path, "w").write(t)
            r = subprocess.run([sys.executable, "tools/build.py", p, "--no-split"], capture_output=True, text=True,
                               cwd=ROOT)
            if " OK " in r.stdout:
                good.append((n, fn))
            elif a.v:
                print("%s %s failed:\n%s" % (p, n, (r.stdout + r.stderr)[-1500:]))
        t = old
        for gn, gfn in good:
            t = t.replace('INCLUDE_ASM("asm/%s/nonmatchings/%s", %s);' % (p, p, gn), gfn)
        open(path, "w").write(t)
        print("%s: installed %d of %d" % (p, len(good), len(items)))


if __name__ == "__main__":
    main()

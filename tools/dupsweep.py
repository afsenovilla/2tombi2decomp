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


def imm_map(obj, name, want):
    """{compiled immediate: retail immediate} when the compiled function differs from `want` only in the 16-bit
    immediates of otherwise identical instructions (copies of shared code with other constants); None otherwise."""
    d = os.path.dirname(obj)
    subprocess.run(["mipsel-linux-gnu-objcopy", "-O", "binary", "-j", ".text", obj, d + "/t.bin"], check=True)
    text = open(d + "/t.bin", "rb").read()
    if len(text) < len(want):
        return None
    rel = set()
    for l in subprocess.run(["mipsel-linux-gnu-objdump", "-r", "-j", ".text", obj], capture_output=True,
                            text=True).stdout.splitlines():
        m = re.match(r"([0-9a-f]{8})\s+R_MIPS_", l)
        if m:
            rel.add(int(m.group(1), 16))
    out = {}
    for i in range(0, len(want), 4):
        g = struct.unpack("<I", text[i:i + 4])[0]
        w = struct.unpack("<I", want[i:i + 4])[0]
        if i in rel or g == w:
            continue
        op = g >> 26
        if (g >> 16) != (w >> 16) or op < 8 or op in (0x23, 0x21, 0x25, 0x20, 0x24, 0x2B, 0x29, 0x28):
            return None   # not an immediate-only difference (or a load/store offset)
        gi, wi = g & 0xFFFF, w & 0xFFFF
        if op in (8, 9, 0xA):   # addi/addiu/slti: signed
            gi, wi = gi - 0x10000 if gi & 0x8000 else gi, wi - 0x10000 if wi & 0x8000 else wi
        if out.get(gi, wi) != wi:
            return None
        out[gi] = wi
    return out or None


def patch_consts(body, m):
    """Replace each literal of the C body whose value is a key of m by its value, when it appears exactly once."""
    for a_, b_ in m.items():
        pats = [r"(?<![\w.])0x%X\b" % abs(a_), r"(?<![\w.])0x%x\b" % abs(a_)] if abs(a_) > 9 else []
        pats.append(r"(?<![\w.])%d\b" % abs(a_))
        hits = [(mm.start(), mm.end()) for pt in set(pats) for mm in re.finditer(pt, body)]
        hits = sorted(set(hits))
        if len(hits) != 1:
            return None
        st, en = hits[0]
        neg = body[:st].rstrip().endswith("-")
        if (a_ < 0) != neg:
            return None
        body = body[:st] + ("0x%X" % abs(b_)) + body[en:]
    return body


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
    scratch = {}
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
                    im = imm_map(t + "/a.o", tname, b[ad - d:end - d])
                    pb = patch_consts(body, im) if im else None
                    if pb is not None:
                        open(t + "/x.c", "w").write(PRELUDE + "\n".join(ext) + "\n" + pb + "\n")
                        cc.compile_c(t + "/x.c", t + "/a.o")
                        if L.matches(t + "/a.o", tname, b[ad - d:end - d], syms):
                            body = pb
                        else:
                            pb = None
                    if pb is None:
                        if a.v:
                            print("%s %s: copy of %s %s does not match" % (p, tname, sp, sname))
                        continue
            except cc.CompileError as e:
                if a.v:
                    print("%s %s: copy of %s %s does not compile: %s" % (p, tname, sp, sname, str(e)[-300:]))
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
            scratch[(p, tname)] = PRELUDE + "\n".join(ex) + "\n\n" + fn + "\n"
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
        # the rest through install_c.py, which aliases clashing global types and fixes declarations
        done = {gn for gn, _ in good}
        for n, fn in items:
            if n in done:
                continue
            tf = tempfile.NamedTemporaryFile("w", suffix=".c", dir=os.path.join(ROOT, "build"), delete=False)
            tf.write(scratch[(p, n)])
            tf.close()
            r = subprocess.run([sys.executable, "-I", "tools/install_c.py", tf.name, "--prog", p],
                               capture_output=True, text=True, cwd=ROOT)
            os.unlink(tf.name)
            if "installed" in r.stdout:
                good.append((n, fn))
            elif a.v:
                print("%s %s install_c failed:\n%s" % (p, n, (r.stdout + r.stderr)[-800:]))
        print("%s: installed %d of %d" % (p, len(good), len(items)))


if __name__ == "__main__":
    main()

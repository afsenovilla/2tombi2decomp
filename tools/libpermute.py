#!/usr/bin/env python3
"""Run the permuter over the library near misses of tools/libnear.py and install what reaches a match.

  python3 -I tools/libpermute.py [--prog main] [--max-distance 6] [--seconds 90] [--install]

For each function of build/libnear_<prog>.csv within the distance: the same candidate (psx_tomba cut or m2c draft)
and compiler set-up as libnear found best, decomp-permuter for --seconds (tools/permute.py). A zero-score output has
its function spliced back into the candidate (the permuter works on preprocessed text), is checked again like
libsweep (bytes and relocation symbols) and, with --install, written to src/<prog>/psyq/<lib>/<name>.c; the linked
build must stay OK.
"""
import argparse, csv, glob, os, re, shutil, subprocess, sys, tempfile

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))
import cc, libsweep as L, ptsrc


def func_text(text, name):
    for kind, seg in ptsrc.items(ptsrc.strip_comments(text)):
        if kind == "code" and seg.rstrip().endswith("}") and ptsrc.func_name(seg) == name:
            return seg.strip()
    return None


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--prog", default="main")
    ap.add_argument("--max-distance", type=int, default=6)
    ap.add_argument("--seconds", type=int, default=90)
    ap.add_argument("--install", action="store_true")
    a = ap.parse_args()
    rows = [r for r in csv.DictReader(open(os.path.join(ROOT, "build", "libnear_%s.csv" % a.prog)))
            if int(r["distance"]) <= a.max_distance]
    binary, delta = L.prog_bytes(a.prog)
    found = []
    for r in rows:
        name, v = r["name"], L.VARIANTS[int(r["variant"])]
        f = glob.glob(os.path.join(ROOT, "src", a.prog, "psyq", "*", name + ".c"))
        if not f or "INCLUDE_ASM" not in open(f[0]).read():
            continue
        cands = dict(L.candidates(a.prog, name, None, None, ("pt", "m2c")))
        text = next((t for k, t in cands.items() if k.split(":")[0] == r["source"].split(":")[0]), None)
        if not text:
            continue
        d = os.path.join(ROOT, "build", "permute_src")
        os.makedirs(d, exist_ok=True)
        src = os.path.join(d, name + ".c")
        open(src, "w").write(text)
        pdir = os.path.join(ROOT, "build", "permute", name)
        shutil.rmtree(pdir, ignore_errors=True)
        subprocess.run([sys.executable, "-I", "tools/permute.py", name, "--prog", a.prog, "--src", src,
                        "--seconds", str(a.seconds), "--cc", v["cc"], "--flags", v["flags"], "--as", v["as"],
                        "--aspsx", v.get("aspsx", "2.79"), "--quiet"], cwd=ROOT)
        outs = sorted(glob.glob(os.path.join(pdir, "output-0-*", "source.c")))
        if not outs:
            print("  %-30s no match (distance %s)" % (name, r["distance"]))
            continue
        body = func_text(open(outs[0]).read(), name)
        old = func_text(text, name)
        if not body or not old:
            continue
        new = text.replace(old, body) if old in text else None
        if new is None:
            # the candidate had comments inside the function: rebuild it from the stripped text
            new = ptsrc.strip_comments(text).replace(old, body)
        # check again with the real pipeline
        t = tempfile.mkdtemp(dir=os.path.join(ROOT, "build"))
        open(os.path.join(t, "x.c"), "w").write(new)
        ad, size = L.asm_info(a.prog, name)
        want = binary[ad - delta: ad - delta + size]
        ok, syms = False, {}
        try:
            cc.compile_c(os.path.join(t, "x.c"), os.path.join(t, "a.o"), v)
            ok = L.matches(os.path.join(t, "a.o"), name, want, syms)
        except cc.CompileError:
            pass
        shutil.rmtree(t, ignore_errors=True)
        print("  %-30s %s" % (name, "MATCH" if ok else "permuter zero but not confirmed"))
        if ok:
            found.append((name, f[0], v, r["source"], new, syms))
    print("%d / %d matched by the permuter" % (len(found), len(rows)))
    if not a.install or not found:
        return
    known, aliases = L.defined_symbols(a.prog), L.read_aliases(a.prog)
    for name, path, v, source, text, syms in found:
        if any(known.get(k, aliases.get(k, ad)) != ad for k, ad in syms.items()):
            print("  skipped %s (symbol address clash)" % name); continue
        for k, ad in syms.items():
            if k not in known:
                aliases[k] = ad
        old = open(path).read()
        open(path, "w").write(L.header(v) + L.note_for(source) + "// Permuted with decomp-permuter.\n" + text)
        b = subprocess.run([sys.executable, "tools/build.py", a.prog, "--no-split"], capture_output=True, text=True,
                           cwd=ROOT)
        L.write_aliases(a.prog, aliases)
        if " OK " not in b.stdout:
            open(path, "w").write(old)
            print("  left out %s (linked build differs)" % name)
    subprocess.run([sys.executable, "tools/build.py", a.prog, "--no-split"], cwd=ROOT)


if __name__ == "__main__":
    main()

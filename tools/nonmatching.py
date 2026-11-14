#!/usr/bin/env python3
"""Install equivalent (not byte-matching) C for functions that do not match yet, behind NON_MATCHING.

  python3 -I tools/nonmatching.py FILE.c [--prog main] [--note "why it differs"]

Each function of the scratch FILE.c replaces its INCLUDE_ASM line in src/<prog>/<prog>.c with

    #ifdef NON_MATCHING
    // NON_MATCHING: N words differ (tools/ccheck.py)
    <the file's declarations>
    <the function>
    #else
    INCLUDE_ASM("asm/<prog>/nonmatchings/<prog>", NAME);
    #endif

so the matching build (no NON_MATCHING) still links the retail asm, while a build with -DNON_MATCHING (the native
port) uses the C. The C is not verified byte for byte: the note records how far it is, and the function stays
pending in tools/progress.py (listed as "equivalent C"). Once it matches, tools/install_c.py replaces the whole
block with the plain function.

Checks before writing: the function compiles, it differs from retail (a matching one belongs in install_c.py), and
afterwards the matching build is still OK and src/<prog>/<prog>.c compiles with -DNON_MATCHING.
"""
import argparse, os, re, subprocess, sys, tempfile

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))
import cc, ptsrc


def ccheck(src, prog):
    r = subprocess.run([sys.executable, "-I", os.path.join(ROOT, "tools", "ccheck.py"), src, "--prog", prog],
                       capture_output=True, text=True, cwd=ROOT)
    res = {}
    for l in r.stdout.splitlines():
        m = re.match(r"(OK|DIFF)\s+(\w+)\s+\w+\s+\((\d+) bytes\)(?:, (\d+) words differ)?", l)
        if m:
            res[m.group(2)] = None if m.group(1) == "OK" else int(m.group(4) or 0)
    if not res:
        sys.exit("ccheck failed:\n" + r.stdout + r.stderr)
    return res


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("src")
    ap.add_argument("--prog", default="main")
    ap.add_argument("--note", default="")
    a = ap.parse_args()
    path = os.path.join(ROOT, "src", a.prog, a.prog + ".c")
    old = open(path).read()
    text = open(a.src).read()
    pre, funcs = [], []
    for kind, seg in ptsrc.items(text):
        s = seg.strip()
        if not s or (kind == "pp" and s.startswith("#include")):
            continue
        n = ptsrc.func_name(s) if s.endswith("}") else None
        (funcs.append((n, s)) if n else pre.append(s))
    diff = ccheck(a.src, a.prog)
    t = old
    for n, body in funcs:
        if diff.get(n, 0) is None:
            sys.exit("%s matches: install it with tools/install_c.py" % n)
        line = 'INCLUDE_ASM("asm/%s/nonmatchings/%s", %s);' % (a.prog, a.prog, n)
        if t.count(line) != 1:
            sys.exit("%s: no single INCLUDE_ASM line for %s" % (path, n))
        if re.search(r"#ifdef NON_MATCHING\n(?:(?!#endif).)*?" + re.escape(line), t, re.S):
            sys.exit("%s already has NON_MATCHING C" % n)
        uses = [p for p in pre if any(re.search(r"\b%s\b" % w, body)
                                      for w in re.findall(r"\b(\w+)\s*(?:\[[^\]]*\])?\s*[;)]?\s*;?$", p)[-1:])
                or p.startswith(("typedef", "struct", "union"))]
        note = "// NON_MATCHING: %s words differ (tools/ccheck.py)%s" % (diff.get(n, "?"),
                                                                       ("; " + a.note) if a.note else "")
        block = "\n".join(["#ifdef NON_MATCHING", note] + uses + [body, "#else", line, "#endif"])
        t = t.replace(line, block)
    open(path, "w").write(t)
    r = subprocess.run([sys.executable, "tools/build.py", a.prog, "--no-split"], capture_output=True, text=True,
                       cwd=ROOT)
    if " OK " not in r.stdout:
        open(path, "w").write(old)
        sys.exit("matching build not OK, restored:\n" + r.stdout + r.stderr[-2000:])
    d = tempfile.mkdtemp(dir=os.path.join(ROOT, "build"))
    try:
        cc.compile_c(path, d + "/nm.o", defines=["NON_MATCHING"])
    except cc.CompileError as e:
        open(path, "w").write(old)
        sys.exit("does not compile with -DNON_MATCHING, restored:\n%s" % str(e)[-2000:])
    finally:
        subprocess.run(["rm", "-rf", d])
    print("NON_MATCHING C for %d functions: %s" % (len(funcs), " ".join(n for n, _ in funcs)))


if __name__ == "__main__":
    main()

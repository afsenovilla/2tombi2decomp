#!/usr/bin/env python3
"""Library sweep: for every Psy-Q function file still INCLUDE_ASM (src/<prog>/psyq/<lib>/<name>.c), try C candidates
under several compiler set-ups (Sony built its libraries with other compilers than the game's) and install the
first that matches the retail bytes, with the // CC / // FLAGS / // ASPSX / // AS header that made it match.

  python3 -I tools/libsweep.py [--prog main] [--lib libc2] [--install] [-j N] [--source m2c|t1|both]

Candidates: the m2c draft (tools/decomp.py) and, with --source t1/both, Tombi-Decomp's matched C for the same
function (tools/t1match.py) when it is real C (its __asm__ wrappers are skipped). After --install the linked build of
the program must still be OK, else the installs are undone one by one.
"""
import argparse, concurrent.futures as cf, csv, glob, os, re, shutil, struct, subprocess, sys, tempfile

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))
import cc, decomp as D

VARIANTS = [
    {"cc": "gcc-2.8.1-psx", "as": "maspsx", "aspsx": "2.79", "flags": "-O2 -G0"},
    {"cc": "gcc-2.7.2-psx", "as": "maspsx", "aspsx": "2.79", "flags": "-O2 -G0"},
    {"cc": "gcc-2.7.2-psx", "as": "gnu", "flags": "-O2 -G0"},
    {"cc": "gcc-2.8.1-psx", "as": "gnu", "flags": "-O2 -G0"},
    {"cc": "gcc-2.7.2-psx", "as": "maspsx", "aspsx": "2.56", "flags": "-O2 -G0"},
    {"cc": "gcc-2.7.2-psx", "as": "maspsx", "aspsx": "2.79", "flags": "-O3 -G0"},
    {"cc": "gcc-2.7.2-psx", "as": "gnu", "flags": "-O3 -G0"},
    {"cc": "gcc-2.8.1-psx", "as": "maspsx", "aspsx": "2.79", "flags": "-O3 -G0"},
]


def prog_bytes(prog):
    y = open(os.path.join(ROOT, "config", prog + ".yaml")).read()
    path = re.search(r"target_path:\s*(\S+)", y).group(1)
    vram = int(re.search(r"vram:\s*(0x\w+)", y).group(1), 16)
    start = int(re.search(r"type: code\n\s+start: (0x\w+)", y).group(1), 16)
    return open(os.path.join(ROOT, path), "rb").read(), vram - start


def asm_info(prog, name):
    t = open(D.find_asm(prog, name)).read()
    m = re.search(r"^nonmatching \w+,\s*(0x\w+)", t, re.M)
    a = re.search(r"/\* \w+ ([0-9A-F]{8}) ", t)
    return (int(a.group(1), 16) if a else None), (int(m.group(1), 16) if m else None)


def matches(obj, name, want):
    """True when the function `name` in obj has exactly the retail bytes outside relocated fields."""
    d = os.path.dirname(obj)
    subprocess.run(["mipsel-linux-gnu-objcopy", "-O", "binary", "-j", ".text", obj, d + "/t.bin"], check=True)
    text = open(d + "/t.bin", "rb").read()
    nm = subprocess.run(["mipsel-linux-gnu-nm", "-S", "--defined-only", obj], capture_output=True, text=True).stdout
    off = size = None
    for l in nm.splitlines():
        p = l.split()
        if len(p) == 4 and p[3] == name and p[2] in "Tt":
            off, size = int(p[0], 16), int(p[1], 16)
    if off is None or size != len(want):
        return False
    rel = set()
    for l in subprocess.run(["mipsel-linux-gnu-objdump", "-r", "-j", ".text", obj], capture_output=True,
                            text=True).stdout.splitlines():
        m = re.match(r"([0-9a-f]{8})\s+R_MIPS_", l)
        if m:
            rel.add(int(m.group(1), 16))
    for i in range(0, size, 4):
        g = struct.unpack("<I", text[off + i:off + i + 4])[0]
        w = struct.unpack("<I", want[i:i + 4])[0]
        if off + i in rel:
            if g >> 26 in (2, 3):
                g, w = g & 0xFC000000, w & 0xFC000000
            else:
                g, w = g & 0xFFFF0000, w & 0xFFFF0000
        if g != w:
            return False
    return True


def candidates(prog, name, ctx, t1src):
    out = []
    r = subprocess.run([sys.executable, D.M2C, "--target", "mipsel-gcc-c", "--context", ctx, D.find_asm(prog, name)],
                       capture_output=True, text=True, cwd=ROOT)
    if r.returncode == 0 and r.stdout.strip():
        out.append(("m2c", '#include "common.h"\n' + re.sub(r"(?m)^(extern )?\? ", r"\1s32 ", r.stdout)))
    if t1src and "__asm__(" not in open(t1src).read():
        t = open(t1src).read()
        t = re.sub(r"(?m)^//.*\n", "", t)
        out.append(("t1", t))
    return out


def attempt(prog, name, ctx, t1src, binary, delta):
    addr, size = asm_info(prog, name)
    if addr is None or size is None:
        return name, None
    want = binary[addr - delta: addr - delta + size]
    d = tempfile.mkdtemp(dir=os.path.join(ROOT, "build"))
    try:
        for kind, text in candidates(prog, name, ctx, t1src):
            src = os.path.join(d, name + ".c")
            open(src, "w").write(text)
            for v in VARIANTS:
                try:
                    cc.compile_c(src, os.path.join(d, "a.o"), v)
                except cc.CompileError:
                    if v is VARIANTS[0]:
                        break      # does not compile at all
                    continue
                if matches(os.path.join(d, "a.o"), name, want):
                    return name, (kind, v, text)
    finally:
        shutil.rmtree(d, ignore_errors=True)
    return name, None


def header(v):
    h = ["// CC " + v["cc"], "// FLAGS " + v["flags"]]
    h.append("// AS gnu" if v["as"] == "gnu" else "// ASPSX " + v["aspsx"])
    return "\n".join(h) + "\n"


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--prog", default="main")
    ap.add_argument("--lib")
    ap.add_argument("--install", action="store_true")
    ap.add_argument("--source", default="both")
    ap.add_argument("-j", type=int, default=os.cpu_count())
    a = ap.parse_args()
    files = {}
    for f in glob.glob(os.path.join(ROOT, "src", a.prog, "psyq", a.lib or "*", "*.c")):
        if "INCLUDE_ASM" in open(f).read():
            files[os.path.basename(f)[:-2]] = f
    t1 = {}
    if a.source in ("t1", "both"):
        p = os.path.join(ROOT, "build", "t1match_%s.csv" % a.prog)
        if not os.path.exists(p):
            subprocess.run([sys.executable, "-I", "tools/t1match.py", "--prog", a.prog, "--csv", p], cwd=ROOT,
                           capture_output=True)
        t1dir = os.path.join(os.path.dirname(ROOT), "Tombi-Decomp", "src")
        for r in csv.DictReader(open(p)):
            if r["t1_src"] == "True" and r["t1_name"] == r["t2_name"]:
                t1[r["t2_name"]] = os.path.join(t1dir, r["t1_name"] + ".c")
    if a.source == "t1":
        files = {k: v for k, v in files.items() if k in t1}
    ctx = D.context()
    binary, delta = prog_bytes(a.prog)
    with cf.ThreadPoolExecutor(a.j) as ex:
        res = [r for r in ex.map(lambda n: attempt(a.prog, n, ctx, t1.get(n), binary, delta), sorted(files)) if r[1]]
    print("%d / %d library functions matched" % (len(res), len(files)))
    for n, (kind, v, _) in res:
        print("  %-32s %-4s %s" % (n, kind, header(v).replace("\n", " ")))
    if not a.install:
        return
    old = {n: open(files[n]).read() for n, _ in res}
    for n, (kind, v, text) in res:
        note = "// Source: Tombi-Decomp (matched C of the same Psy-Q function).\n" if kind == "t1" else ""
        open(files[n], "w").write(header(v) + note + text)

    def ok():
        b = subprocess.run([sys.executable, "tools/build.py", a.prog, "--no-split"], capture_output=True, text=True,
                           cwd=ROOT)
        return " OK " in b.stdout
    if not ok():   # find the ones that change the linked build: restore all, then add back one at a time
        for n, _ in res:
            open(files[n], "w").write(old[n])
        bad = []
        for n, (kind, v, text) in res:
            note = "// Source: Tombi-Decomp (matched C of the same Psy-Q function).\n" if kind == "t1" else ""
            open(files[n], "w").write(header(v) + note + text)
            if not ok():
                open(files[n], "w").write(old[n]); bad.append(n)
        print("left out (linked build differs): " + " ".join(bad))
    print("installed; linked build OK")


if __name__ == "__main__":
    main()

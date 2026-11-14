#!/usr/bin/env python3
"""Library sweep: for every Psy-Q function file still INCLUDE_ASM (src/<prog>/psyq/<lib>/<name>.c), try C candidates
under several compiler set-ups (Sony built its libraries with other compilers than the game's) and install the
first that matches the retail bytes, with the // CC / // FLAGS / // ASPSX / // AS header that made it match.

  python3 -I tools/libsweep.py [--prog main] [--lib libc2] [--install] [-j N] [--source m2c|t1|both]

Candidates, in this order: psx_tomba's library C cut to the function (tools/ptsrc.py), Tombi-Decomp's matched C for
the same function (tools/t1match.py; its __asm__ wrappers are skipped), the m2c draft (tools/decomp.py). After --install the linked build of
the program must still be OK, else the installs are undone one by one.
"""
import argparse, concurrent.futures as cf, csv, glob, os, re, shutil, struct, subprocess, sys, tempfile

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))
import cc, decomp as D, ptsrc

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


def reloc_symbols(obj, name, want, text, off):
    """{symbol: address} the retail bytes give the function's relocations (jal targets, %hi/%lo pairs), or None when
    one symbol would need two addresses. The object's own immediates are the addends (MIPS REL)."""
    out = {}
    rel = []
    for l in subprocess.run(["mipsel-linux-gnu-objdump", "-r", "-j", ".text", obj], capture_output=True,
                            text=True).stdout.splitlines():
        m = re.match(r"([0-9a-f]{8})\s+(R_MIPS_\w+)\s+(\S+)", l)
        if m:
            rel.append((int(m.group(1), 16), m.group(2), m.group(3)))
    word = lambda b, i: struct.unpack("<I", b[i:i + 4])[0]
    pend = {}
    for at, typ, sym in rel:
        i = at - off
        if not 0 <= i < len(want) or sym.startswith("."):
            continue
        g, w = word(text, at), word(want, i)
        if typ == "R_MIPS_26":
            addr = ((w & 0x3FFFFFF) << 2) | 0x80000000
            add = (g & 0x3FFFFFF) << 2
            val = addr - add
        elif typ == "R_MIPS_HI16":
            pend.setdefault(sym, []).append((g & 0xFFFF, w & 0xFFFF)); continue
        elif typ == "R_MIPS_LO16":
            sx = lambda v: v - 0x10000 if v & 0x8000 else v
            if not pend.get(sym):
                continue
            gh, wh = pend[sym][-1]
            val = ((wh << 16) + sx(w & 0xFFFF)) - ((gh << 16) + sx(g & 0xFFFF))
        else:
            continue
        val &= 0xFFFFFFFF
        if out.get(sym, val) != val:
            return None
        out[sym] = val
    return out


def matches(obj, name, want, syms=None):
    """True when the function `name` in obj has exactly the retail bytes outside relocated fields. With syms (a
    dict), also fills in the addresses its relocated symbols must have (reloc_symbols)."""
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
    if syms is not None:
        r = reloc_symbols(obj, name, want, text, off)
        if r is None:
            return False
        syms.update(r)
    return True


def candidates(prog, name, ctx, t1src, sources=("main", "pt", "t1", "m2c")):
    out = []
    if "main" in sources and prog != "main":   # the same function already matched in MAIN.EXE
        mf = glob.glob(os.path.join(ROOT, "src", "main", "psyq", "*", name + ".c"))
        if mf and "INCLUDE_ASM" not in open(mf[0]).read():
            t = re.sub(r"(?m)^//\s*(CC|FLAGS|ASPSX|AS)\s.*\n", "", open(mf[0]).read())
            out.append(("main:" + os.path.relpath(mf[0], ROOT), t))
    if "pt" in sources:
        text, f = ptsrc.cut(name)
        if text:
            out.append(("pt:" + f, text))
    r = subprocess.run([sys.executable, D.M2C, "--target", "mipsel-gcc-c", "--context", ctx, D.find_asm(prog, name)],
                       capture_output=True, text=True, cwd=ROOT) if "m2c" in sources else None
    if r and r.returncode == 0 and r.stdout.strip():
        out.append(("m2c", '#include "common.h"\n' + re.sub(r"(?m)^(extern )?\? ", r"\1s32 ", r.stdout)))
    if "t1" in sources and t1src and "__asm__(" not in open(t1src).read():
        t = open(t1src).read()
        t = re.sub(r"(?m)^//.*\n", "", t)
        out.append(("t1", t))
    return out


def attempt(prog, name, ctx, t1src, binary, delta, sources=("main", "pt", "t1", "m2c")):
    addr, size = asm_info(prog, name)
    if addr is None or size is None:
        return name, None
    want = binary[addr - delta: addr - delta + size]
    d = tempfile.mkdtemp(dir=os.path.join(ROOT, "build"))
    try:
        for kind, text in candidates(prog, name, ctx, t1src, sources):
            src = os.path.join(d, name + ".c")
            open(src, "w").write(text)
            for v in VARIANTS:
                try:
                    cc.compile_c(src, os.path.join(d, "a.o"), v)
                except cc.CompileError:
                    if v is VARIANTS[0]:
                        break      # does not compile at all
                    continue
                syms = {}
                if matches(os.path.join(d, "a.o"), name, want, syms):
                    return name, (kind, v, text, syms)
    finally:
        shutil.rmtree(d, ignore_errors=True)
    return name, None


def defined_symbols(prog):
    """name -> address of everything the link defines: config/symbol_addrs_<prog>.txt and splat's auto symbols."""
    out = {}
    for p in [os.path.join(ROOT, "config", "symbol_addrs_%s.txt" % prog),
              os.path.join(ROOT, "build", "undefined_syms_auto.%s.txt" % prog),
              os.path.join(ROOT, "build", "undefined_funcs_auto.%s.txt" % prog)]:
        if os.path.exists(p):
            for l in open(p):
                m = re.match(r"\s*(\w+)\s*=\s*0x([0-9A-Fa-f]+)", l)
                if m:
                    out[m.group(1)] = int(m.group(2), 16)
    # splat's own names (func_XXXXXXXX / D_XXXXXXXX) carry their address
    return out


def aliases_path(prog):
    return os.path.join(ROOT, "config", "aliases_%s.ld" % prog)


def read_aliases(prog):
    out = {}
    if os.path.exists(aliases_path(prog)):
        for l in open(aliases_path(prog)):
            m = re.match(r"\s*(\w+)\s*=\s*0x([0-9A-Fa-f]+);", l)
            if m:
                out[m.group(1)] = int(m.group(2), 16)
    return out


def write_aliases(prog, al):
    if not al:
        return
    with open(aliases_path(prog), "w") as f:
        f.write("/* Names used by library C taken from other projects (psx_tomba, Tombi-Decomp) for addresses this\n"
                " * program knows under another name; addresses read off the retail code by tools/libsweep.py. */\n")
        for k, ad in sorted(al.items(), key=lambda x: (x[1], x[0])):
            f.write("%s = 0x%08X;\n" % (k, ad))


def note_for(kind):
    if kind == "t1":
        return "// Source: Tombi-Decomp (matched C of the same Psy-Q function).\n"
    if kind.startswith("main:"):
        return "// Same function as %s (MAIN.EXE).\n" % kind[5:]
    if kind.startswith("pt:"):
        return "// Source: psx_tomba %s (MIT), cut to this function by tools/ptsrc.py.\n" % kind[3:]
    return ""


def header(v):
    h = ["// CC " + v["cc"], "// FLAGS " + v["flags"]]
    h.append("// AS gnu" if v["as"] == "gnu" else "// ASPSX " + v["aspsx"])
    return "\n".join(h) + "\n"


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--prog", default="main")
    ap.add_argument("--lib")
    ap.add_argument("--install", action="store_true")
    ap.add_argument("--source", default="main,pt,t1,m2c",
                    help="comma list of main (the MAIN.EXE file, for boot), pt (psx_tomba), t1 (Tombi-Decomp), m2c")
    ap.add_argument("-j", type=int, default=os.cpu_count())
    a = ap.parse_args()
    files = {}
    for f in glob.glob(os.path.join(ROOT, "src", a.prog, "psyq", a.lib or "*", "*.c")):
        if "INCLUDE_ASM" in open(f).read():
            files[os.path.basename(f)[:-2]] = f
    t1 = {}
    sources = tuple(a.source.split(","))
    if "t1" in sources:
        p = os.path.join(ROOT, "build", "t1match_%s.csv" % a.prog)
        if not os.path.exists(p):
            subprocess.run([sys.executable, "-I", "tools/t1match.py", "--prog", a.prog, "--csv", p], cwd=ROOT,
                           capture_output=True)
        t1dir = os.path.join(os.path.dirname(ROOT), "Tombi-Decomp", "src")
        for r in csv.DictReader(open(p)):
            if r["t1_src"] == "True" and r["t1_name"] == r["t2_name"]:
                t1[r["t2_name"]] = os.path.join(t1dir, r["t1_name"] + ".c")

    ctx = D.context()
    binary, delta = prog_bytes(a.prog)
    with cf.ThreadPoolExecutor(a.j) as ex:
        res = [r for r in ex.map(lambda n: attempt(a.prog, n, ctx, t1.get(n), binary, delta, sources), sorted(files))
               if r[1]]
    print("%d / %d library functions matched" % (len(res), len(files)))
    for n, (kind, v, _, _) in res:
        print("  %-32s %-4s %s" % (n, kind, header(v).replace("\n", " ")))
    if not a.install:
        return
    # symbols the new C needs: names the program does not define get an alias at the address the bytes give;
    # a name defined elsewhere at another address means the candidate is wrong
    known = defined_symbols(a.prog)
    aliases = read_aliases(a.prog)
    keep = []
    for r in res:
        n, (kind, v, text, syms) = r
        bad = [k for k, ad in syms.items() if known.get(k, aliases.get(k, ad)) != ad
               or (re.fullmatch(r"(D|func|jtbl)_[0-9A-F]{8}", k) and int(k[-8:], 16) != ad)]
        if bad:
            print("  dropped %s: %s would be at another address than the program has" % (n, ", ".join(bad)))
            continue
        for k, ad in syms.items():
            if k not in known:
                aliases[k] = ad
        keep.append(r)
    res = keep
    write_aliases(a.prog, aliases)
    old = {n: open(files[n]).read() for n, _ in res}
    for n, (kind, v, text, _) in res:
        open(files[n], "w").write(header(v) + note_for(kind) + text)

    def ok():
        b = subprocess.run([sys.executable, "tools/build.py", a.prog, "--no-split"], capture_output=True, text=True,
                           cwd=ROOT)
        return " OK " in b.stdout
    if not ok():   # find the ones that change the linked build: restore all, then add back one at a time
        for n, _ in res:
            open(files[n], "w").write(old[n])
        bad = []
        for n, (kind, v, text, _) in res:
            open(files[n], "w").write(header(v) + note_for(kind) + text)
            if not ok():
                open(files[n], "w").write(old[n]); bad.append(n)
        print("left out (linked build differs): " + " ".join(bad))
    print("installed; linked build OK")


if __name__ == "__main__":
    main()

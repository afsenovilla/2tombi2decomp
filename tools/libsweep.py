#!/usr/bin/env python3
"""Library sweep: for every Psy-Q function file still INCLUDE_ASM (src/<prog>/psyq/<lib>/<name>.c), try C candidates
under several compiler set-ups (Sony built its libraries with other compilers than the game's) and install the
first that matches the retail bytes, with the // CC / // FLAGS / // ASPSX / // AS header that made it match.

  python3 -I tools/libsweep.py [--prog main] [--lib libc2] [--install] [-j N] [--source m2c|t1|both] [--epilogue]
      [--nocse | --only-nocse] [--loop | --only-loop] [--names A,B]

Candidates, in this order: psx_tomba's library C cut to the function (tools/ptsrc.py), Tombi-Decomp's matched C for
the same function (tools/t1match.py; its __asm__ wrappers are skipped), the m2c draft (tools/decomp.py); compiler
set-ups: VARIANTS below (gcc 2.8.1 / 2.7.2, maspsx 2.79 / 2.56 or GNU as, -O1..-O3, -mno-split-addresses,
-fno-delayed-branch; --epilogue adds the // EPILOGUE sony and // RETURN sony ones, --nocse the gcc-2.8.1-nocse
ones, --only-nocse tries those alone, --loop / --only-loop the gcc-2.7.2-loop4 / gcc-2.8.1-loop2 /
gcc-2.8.1-nocse-loop2 ones). A candidate whose D_ / func_ names carry another program's addresses (psx_tomba and
Tombi-Decomp use Tombi's) gets one `#define OLD NEW` line per name, NEW being this program's name for the address
the bytes give. After --install the linked build of the program must still be OK, else the installs are undone
one by one.
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
    # the set-ups of docs/STATUS.md 2026-11-22 (2): most of libgpu / libcd / libspu / libc2 (no %hi hoisted out of
    # loops), void functions with one shared exit, and libsnd / libpad / the libcd and libetc statics
    {"cc": "gcc-2.8.1-psx", "as": "maspsx", "aspsx": "2.79", "flags": "-O2 -G0 -mno-split-addresses"},
    {"cc": "gcc-2.8.1-psx", "as": "gnu", "flags": "-O2 -G0 -mno-split-addresses -fno-delayed-branch"},
    {"cc": "gcc-2.8.1-psx", "as": "gnu", "flags": "-O2 -G0 -mno-split-addresses"},
    {"cc": "gcc-2.8.1-psx", "as": "maspsx", "aspsx": "2.79", "flags": "-O2 -G0 -mno-split-addresses -fno-delayed-branch"},
    {"cc": "gcc-2.7.2-psx", "as": "gnu", "flags": "-O1 -G0"},
    {"cc": "gcc-2.7.2-psx", "as": "maspsx", "aspsx": "2.79", "flags": "-O1 -G0"},
]
# --epilogue: the set-ups of docs/STATUS.md 2026-11-22 (4)-(5), Sony's epilogue (// EPILOGUE sony: most libsnd /
# libspu / libgpu functions with a frame) and Sony's single return (// RETURN sony: leaf functions with several
# returns; `sony first` keeps an early `return K;` after its test)
EPI_VARIANTS = []
for _f in ("-O2 -G0 -mno-split-addresses", "-O2 -G0"):
    for _a in ({"as": "gnu"}, {"as": "maspsx", "aspsx": "2.79"}):
        for _r in ({"epilogue": "sony"}, {"return": "sony"}, {"epilogue": "sony", "return": "sony"},
                   {"return": "sony first"}, {"return": "sony thread"}):
            EPI_VARIANTS.append(dict({"cc": "gcc-2.8.1-psx", "flags": _f}, **_a, **_r))
    EPI_VARIANTS.append({"cc": "gcc-2.7.2-psx", "flags": _f, "as": "gnu", "epilogue": "sony"})
# --nocse: Sony's library compiler without the post-reload CSE pass (/opt/oldgcc/gcc-2.8.1-nocse, made by
# tools/setup_native.sh; docs/STATUS.md 2026-11-22 (6)): no `move a2,a1` for two zero arguments, no `sllv` with a
# register holding 16, no deleted redundant moves. The usual library set-ups with it, plain and with Sony's
# epilogue / return.
NOCSE_VARIANTS = []
for _f in ("-O2 -G0 -mno-split-addresses", "-O2 -G0", "-O2 -G0 -mno-split-addresses -fno-delayed-branch"):
    for _a in ({"as": "gnu"}, {"as": "maspsx", "aspsx": "2.79"}):
        for _r in ({}, {"return": "sony"}, {"epilogue": "sony"}, {"epilogue": "sony", "return": "sony"},
                   {"return": "sony first"}, {"return": "sony thread"}):
            NOCSE_VARIANTS.append(dict({"cc": "gcc-2.8.1-nocse", "flags": _f}, **_a, **_r))
# --loop: the loop-hoisting compilers (tools/setup_native.sh; docs/STATUS.md 2026-11-23): Sony's library compiler
# hoisted more invariants out of loops with calls. gcc-2.7.2-loop4 (_spu_gcSPU, CdControl / F / B as is),
# gcc-2.8.1-loop2 and gcc-2.8.1-nocse-loop2 (SpuSetCommonAttr, CD_sync / CD_ready closest). Per-file set-ups:
# CD_cachefile matches only with the stock 2.7.2.
LOOP_VARIANTS = []
for _f in ("-O2 -G0", "-O2 -G0 -mno-split-addresses"):
    for _a in ({"as": "gnu"}, {"as": "maspsx", "aspsx": "2.79"}):
        for _r in ({}, {"epilogue": "sony"}):
            LOOP_VARIANTS.append(dict({"cc": "gcc-2.7.2-loop4", "flags": _f}, **_a, **_r))
for _cc in ("gcc-2.8.1-loop2", "gcc-2.8.1-nocse-loop2"):
    for _f in ("-O2 -G0 -mno-split-addresses", "-O2 -G0"):
        for _a in ({"as": "gnu"}, {"as": "maspsx", "aspsx": "2.79"}):
            for _r in ({}, {"return": "sony"}, {"epilogue": "sony"}, {"epilogue": "sony", "return": "sony"}):
                LOOP_VARIANTS.append(dict({"cc": _cc, "flags": _f}, **_a, **_r))


def apply_variant_args(a, variants=None):
    """--epilogue / --nocse / --only-nocse / --loop / --only-loop of libsweep and libnear on the VARIANTS list."""
    v = VARIANTS if variants is None else variants
    if getattr(a, "epilogue", False):
        v.extend(EPI_VARIANTS)
    if getattr(a, "only_nocse", False):
        v[:] = NOCSE_VARIANTS
    elif getattr(a, "nocse", False):
        v.extend(NOCSE_VARIANTS)
    if getattr(a, "only_loop", False):
        v[:] = LOOP_VARIANTS
    elif getattr(a, "loop", False):
        v.extend(LOOP_VARIANTS)


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


def reloc_symbols(obj, name, want, text, off, conflicts=None):
    """{symbol: address} the retail bytes give the function's relocations (jal targets, %hi/%lo pairs), or None when
    one symbol would need two addresses (with a `conflicts` dict: {symbol: set of addresses} of those, every one
    collected). The object's own immediates are the addends (MIPS REL)."""
    out = {}
    bad = {}
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
        if not 0 <= i < len(want) or (sym.startswith(".") and sym != ".rodata"):
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
            if conflicts is None:
                return None
            bad.setdefault(sym, {out[sym]}).add(val)
            continue
        out[sym] = val
    if bad:
        conflicts.update(bad)
        return None
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
    if off is None or size != len(want) or cc.text_size(obj) != size:   # nothing else in the object's text
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


_LIBCTX = {}


def lib_context(prog="main"):
    """include/psyq_all.h preprocessed for m2c (build/libctx_<prog>.c): typed Psy-Q signatures for the drafts, plus
    the guessed parameter counts of the program's functions without a header prototype (tools/arity.py)."""
    if prog not in _LIBCTX:
        out = os.path.join(ROOT, "build", "libctx_%s.c" % prog)
        r = subprocess.run([cc.OLDGCC + "/gcc-2.7.2-psx/cpp", "-undef", "-D__GNUC__=2", "-DMIPSEL", "-D_LANGUAGE_C",
                            "-DM2CTX", "-P", "-I" + os.path.join(ROOT, "include"),
                            "-I" + os.path.join(ROOT, "include", "psyq"), os.path.join(ROOT, "include", "psyq_all.h")],
                           capture_output=True, text=True)
        t = re.sub(r"__asm__\s*\(.*?\);", "", r.stdout, flags=re.S)
        t = re.sub(r"(?m)^#define M2C.*$", "", t)
        subprocess.run([sys.executable, "-I", os.path.join(ROOT, "tools", "arity.py"), prog], cwd=ROOT,
                       capture_output=True)
        ar = os.path.join(ROOT, "build", "arity_%s.h" % prog)
        known = set(re.findall(r"\b(\w+)\s*\(", t))
        if os.path.exists(ar):
            t += "\n" + "\n".join(l for l in open(ar) if re.match(r"M2C_UNK (\w+)\(", l)
                                   and re.match(r"M2C_UNK (\w+)\(", l).group(1) not in known)
        open(out, "w").write(t)
        _LIBCTX[prog] = out
    return _LIBCTX[prog]


def candidates(prog, name, ctx, t1src, sources=("main", "pt", "t1", "m2c")):
    out = []
    if "main" in sources and prog != "main":   # the same function already matched in MAIN.EXE
        mf = glob.glob(os.path.join(ROOT, "src", "main", "psyq", "*", name + ".c"))
        if mf and "INCLUDE_ASM" not in open(mf[0]).read():
            t = re.sub(r"(?m)^//\s*(CC|FLAGS|ASPSX|AS|EPILOGUE|RETURN)\s.*\n", "", open(mf[0]).read())
            out.append(("main:" + os.path.relpath(mf[0], ROOT), t))
    if "pt" in sources:
        text, f = ptsrc.cut(name)
        if text:
            out.append(("pt:" + f, text))
    r = subprocess.run(D.m2c_cmd(prog, name, lib_context(prog), ["--valid-syntax"]), capture_output=True, text=True,
                       cwd=ROOT) if "m2c" in sources else None
    if r and r.returncode == 0 and r.stdout.strip() and "Decompilation failure" not in r.stdout:
        out.append(("m2c", '#define %s %s_hdr\n#include "psyq_all.h"\n#undef %s\n' % (name, name, name) + r.stdout))
    if "t1" in sources and t1src and "__asm__(" not in open(t1src).read():
        t = open(t1src).read()
        t = re.sub(r"(?m)^//.*\n", "", t)
        out.append(("t1", t))
    return out


def rodata(obj):
    d = os.path.dirname(obj)
    subprocess.run(["mipsel-linux-gnu-objcopy", "-O", "binary", "-j", ".rodata", obj, d + "/r.bin"], check=True)
    return open(d + "/r.bin", "rb").read() if os.path.exists(d + "/r.bin") else b""


def strings_to_symbols(text, ro, base):
    """Replace the C string literals of `text`, found in the object's rodata `ro` (whose offset 0 the retail code
    puts at `base`), by `D_<address>` symbols of the retail strings (splat labels them in the rodata asm), so the
    function adds no rodata of its own."""
    out, decl = text, []
    code = "\n".join(l for l in text.split("\n") if not l.lstrip().startswith("#"))
    for lit in sorted(set(re.findall(r'"(?:[^"\\\n]|\\.)*"', code)), key=len, reverse=True):
        raw = bytes(lit[1:-1], "latin1").decode("unicode_escape").encode("latin1") + b"\0"
        off = ro.find(raw)
        if off < 0:
            return None
        name = "D_%08X" % (base + off)
        out = "\n".join(l if l.lstrip().startswith("#") else l.replace(lit, name) for l in out.split("\n"))
        decl.append("extern char %s[];" % name)
    return "\n".join(decl) + "\n" + out


def foreign_names(syms, known, aliases):
    """{name: this program's name} for the symbols a candidate gives another address than this program does (a
    psx_tomba / Tombi-Decomp D_ or func_ name carries Tombi's address)."""
    inv = {}
    for k, ad in list(known.items()) + list(aliases.items()):
        if not re.search(r"_[0-9a-f]{4}$", k):      # not an install_c type alias
            inv.setdefault(ad, k)
    out = {}
    for k, ad in syms.items():
        if k.startswith("."):
            continue
        if known.get(k, aliases.get(k, ad)) != ad or (re.fullmatch(r"(D|func|jtbl)_[0-9A-F]{8}", k)
                                                      and int(k[-8:], 16) != ad):
            out[k] = inv.get(ad) or ("func_%08X" % ad if k.startswith(("func_", "f_")) else "D_%08X" % ad)
    return out


def with_defines(text, ren):
    """`#define OLD NEW` lines in front of the candidate: it keeps its source's names for the reader."""
    return "".join("#define %s %s\n" % kv for kv in sorted(ren.items())) + text


def attempt(prog, name, ctx, t1src, binary, delta, sources=("main", "pt", "t1", "m2c"), names=None):
    try:
        addr, size = asm_info(prog, name)
    except SystemExit:    # no asm file for it
        return name, None
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
                    ro = rodata(os.path.join(d, "a.o"))
                    if ro.strip(b"\0") and ".rodata" in syms:
                        t2 = strings_to_symbols(text, ro, syms[".rodata"])
                        if t2 is None:
                            continue
                        text = t2
                        del syms[".rodata"]
                        open(src, "w").write(text)
                        cc.compile_c(src, os.path.join(d, "a.o"), v)
                        syms = {}
                        if not matches(os.path.join(d, "a.o"), name, want, syms) or rodata(os.path.join(d, "a.o")).strip(b"\0"):
                            continue
                    syms.pop(".rodata", None)
                    ren = foreign_names(syms, *names) if names else {}
                    if ren:   # map each foreign-address name to this program's with #define and check again
                        t2 = with_defines(text, ren)
                        open(src, "w").write(t2)
                        syms2 = {}
                        try:
                            cc.compile_c(src, os.path.join(d, "a.o"), v)
                        except cc.CompileError:
                            continue
                        if not matches(os.path.join(d, "a.o"), name, want, syms2):
                            continue
                        syms2.pop(".rodata", None)
                        text, syms = t2, syms2
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
    for k in ("epilogue", "return"):
        if v.get(k) and v[k] != "none":
            h.append("// %s %s" % (k.upper(), v[k]))
    return "\n".join(h) + "\n"


def pending_files(prog, lib=None):
    """name -> src/<prog>/psyq/<lib>/<name>.c of the library files whose own function is still INCLUDE_ASM (a file
    whose INCLUDE_ASM names another function, a split-off part, is not that function's)."""
    files = {}
    for f in glob.glob(os.path.join(ROOT, "src", prog, "psyq", lib or "*", "*.c")):
        n = os.path.basename(f)[:-2]
        if re.search(r'INCLUDE_ASM\("[^"]+", %s\);' % re.escape(n), open(f).read()):
            files[n] = f
    return files


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--prog", default="main")
    ap.add_argument("--lib")
    ap.add_argument("--install", action="store_true")
    ap.add_argument("--source", default="main,pt,t1,m2c",
                    help="comma list of main (the MAIN.EXE file, for boot), pt (psx_tomba), t1 (Tombi-Decomp), m2c")
    ap.add_argument("-j", type=int, default=os.cpu_count())
    ap.add_argument("--epilogue", action="store_true", help="also the EPILOGUE / RETURN sony set-ups (EPI_VARIANTS)")
    ap.add_argument("--nocse", action="store_true", help="also the gcc-2.8.1-nocse set-ups (NOCSE_VARIANTS)")
    ap.add_argument("--only-nocse", action="store_true", help="only the gcc-2.8.1-nocse set-ups")
    ap.add_argument("--loop", action="store_true", help="also the loop-hoisting compilers (LOOP_VARIANTS)")
    ap.add_argument("--only-loop", action="store_true", help="only the loop-hoisting set-ups")
    ap.add_argument("--names", help="comma list: only these functions")
    a = ap.parse_args()
    apply_variant_args(a)
    files = pending_files(a.prog, a.lib)
    if a.names:
        files = {k: v for k, v in files.items() if k in a.names.split(",")}
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
    names = (defined_symbols(a.prog), read_aliases(a.prog))
    with cf.ThreadPoolExecutor(a.j) as ex:
        res = [r for r in ex.map(lambda n: attempt(a.prog, n, ctx, t1.get(n), binary, delta, sources, names),
                                 sorted(files)) if r[1]]
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

#!/usr/bin/env python3
"""Compile a C file and compare each function in it with the retail bytes (fast check, no link).

  python3 -I tools/ccheck.py src/main/foo.c [--prog main] [--cc gcc-2.7.2-psx] [--aspsx 2.56] [--flags "-O2 -G0"]
      [--as gnu] [--epilogue sony] [--return sony] [--no-protos] [-v] [--func NAME] [--all] [--sbs [--sbs-all]]

Pipeline: tools/cc.py (the file's // CC, // FLAGS, // ASPSX, // AS headers; default the game's gcc 2.8.1 + ASPSX 2.79).
Each defined function is looked up by name in config/symbol_addrs_<prog>.txt or as func_XXXXXXXX, and compared word by
word with the retail file; relocated fields (jal target, %hi/%lo) are compared only where the object has no relocation.
The length must also be the retail one (asm/<prog>/nonmatchings `nonmatching NAME, SIZE`).
Prints OK / DIFF per function (with -v the differing words; for another length also `score N`, the aligned count
that score() and so regswap / variants / permlines report; `order only` when the function has retail's
instructions in another order: tools/prio.py --sched shows the scheduler priorities); --func NAME limits the check. --sbs prints a
side-by-side diff of every DIFF function, ours next to retail (tools/sbs.py; --sbs-all with the equal lines too).
Jump tables: the entries of every table the function's code addresses are compared with retail's jtbl (asm/<prog>/
data/*.s) as offsets into the function: a wrong case-to-label mapping (an empty case sent to another label) is a
DIFF (`code equal, jump table differs`) with the differing entries, not an OK that fails the link.
Declarations: a scratch prototype of a function src/<prog>/<prog>.c or src/main/main.c defines with another return
type (`void f();` for `u8 *f(...)`), or a data-style one (`extern u8 f[];`), is warned about, as calls with another
argument count are.
"""
import argparse, os, re, struct, subprocess, sys, tempfile

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))


def prog_info(prog):
    y = open(os.path.join(ROOT, "config", prog + ".yaml")).read()
    path = re.search(r"target_path:\s*(\S+)", y).group(1)
    vram = int(re.search(r"vram:\s*(0x\w+)", y).group(1), 16)
    start = int(re.search(r"type: code\n\s+start: (0x\w+)", y).group(1), 16)
    syms = {}
    p = os.path.join(ROOT, "config", "symbol_addrs_%s.txt" % prog)
    for l in open(p):
        m = re.match(r"\s*(\w+)\s*=\s*0x([0-9A-Fa-f]+)", l)
        if m:
            syms[m.group(1)] = int(m.group(2), 16)
    return open(os.path.join(ROOT, path), "rb").read(), vram - start, syms


def compile_c(src, a, d):
    import cc
    over = {k: v for k, v in (("cc", a.cc), ("aspsx", a.aspsx), ("flags", a.flags), ("as", a.asm),
                              ("epilogue", a.epilogue), ("return", a.ret)) if v}
    try:
        cc.compile_c(src, d + "/a.o", over)
    except cc.CompileError as e:
        sys.exit("compile error: %s" % e)
    subprocess.run(["mipsel-linux-gnu-objcopy", "-O", "binary", "-j", ".text", d + "/a.o", d + "/t.bin"], check=True)
    text = open(d + "/t.bin", "rb").read()
    funcs = []
    for l in subprocess.run(["mipsel-linux-gnu-nm", "-S", "--defined-only", d + "/a.o"], capture_output=True,
                            text=True).stdout.splitlines():
        p = l.split()
        if len(p) == 4 and p[2] in "Tt":
            funcs.append((p[3], int(p[0], 16), int(p[1], 16)))
    rel = set()
    for l in subprocess.run(["mipsel-linux-gnu-objdump", "-r", "-j", ".text", d + "/a.o"], capture_output=True,
                            text=True).stdout.splitlines():
        m = re.match(r"([0-9a-f]{8})\s+R_MIPS_", l)
        if m:
            rel.add(int(m.group(1), 16))
    return text, sorted(funcs, key=lambda f: f[1]), rel


def retail_sizes(prog):
    """name -> size of every function of a c-segment program (the `nonmatching NAME, 0xSIZE` line splat writes)."""
    import glob
    out = {}
    for f in glob.glob(os.path.join(ROOT, "asm", prog, "*matchings", "**", "*.s"), recursive=True):
        m = re.search(r"^nonmatching (\w+),\s*(0x[0-9A-Fa-f]+)", open(f).read(), re.M)
        if m:
            out[m.group(1)] = int(m.group(2), 16)
    return out


_INFO = {}


def score(src, prog, name, workdir=None, override=None):
    """Words off of function `name` compiled from src against retail (0: match; None: it does not compile or is
    not in the object). Equal sizes: the differing words (relocated fields masked); other sizes: the lines that
    differ in a difflib alignment of the masked words plus the size difference. For the search tools
    (permlines.py, variants.py); thread-safe, one temporary directory per call."""
    import cc
    if prog not in _INFO:
        _INFO[prog] = prog_info(prog) + (retail_sizes(prog),)
    binary, delta, syms, sizes = _INFO[prog]
    addr = syms.get(name) or (int(name[5:], 16) if re.fullmatch(r"func_[0-9A-Fa-f]{8}", name) else None)
    if addr is None or name not in sizes:
        raise SystemExit("no address / size for %s in %s" % (name, prog))
    want = binary[addr - delta: addr - delta + sizes[name]]
    d = tempfile.mkdtemp(dir=workdir or os.path.join(ROOT, "build"))
    try:
        cc.compile_c(src, d + "/a.o", override)
        sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
        import nearcopy
        diffs, ours, size = nearcopy.compare(d + "/a.o", name, want)
        if diffs is None:
            return None
        if size == len(want):
            return len(diffs)
        return nearcopy.aligned_off(ours, want) + abs(size - len(want)) // 4
    except cc.CompileError:
        return None
    finally:
        subprocess.run(["rm", "-rf", d])


INTLIKE = {"", "int", "s32", "signed int", "long", "signed", "unsigned int", "u32", "unsigned", "unsigned long"}


def norm_type(t):
    """a return type without storage words, spaces normalised (`static inline u8 *` -> `u8 *`)."""
    t = re.sub(r"\b(extern|static|inline|__inline__|register)\b", " ", t).replace("*", " * ")
    return " ".join(t.split())


def argcount_warnings(src, prog):
    """warn for every call in the scratch whose argument count differs from the parameter count of the callee's
    definition in src/<prog>/<prog>.c (and src/main/main.c, resident under every overlay): m2c drafts often drop
    or add arguments, which changes the scheduling around the call; install_c.py would cast such calls."""
    import install_c
    defs, rets = {}, {}
    for f in dict.fromkeys([os.path.join(ROOT, "src", prog, prog + ".c"), os.path.join(ROOT, "src", "main", "main.c")]):
        if not os.path.exists(f):
            continue
        for n, h, _ in install_c.heads(open(f).read()):
            if n in defs:
                continue
            hh = " ".join(h.split())
            m = re.match(r"(.*?)\b%s\s*\(([^()]*)\)\s*$" % re.escape(n), hh)    # K&R definitions: any count
            if m:
                k = install_c.params(m.group(2))
                if k is not None:
                    defs[n] = (k, os.path.relpath(f, ROOT))
            m = re.match(r"(.*?)\b%s\s*\(" % re.escape(n), hh)
            if m:
                rets[n] = (norm_type(m.group(1)), os.path.relpath(f, ROOT))
    text = open(src).read()
    own = {n for n, _, _ in install_c.heads(text)}
    # the scratch's declarations of functions the target program defines: another return type than the
    # definition's (an m2c `void f();` for an s32 function, `u8` for s32) changes the code around the call and
    # install_c drops the prototype, so the installed C differs; a data-style declaration (`extern u8 f[];`)
    # compiles calls through a pointer
    for m in re.finditer(r"(?m)^(?:extern\s+)?([\w][\w \*]*?)\b(\w+)\s*(\(|\[)[^;{}]*[)\]]\s*;", text):
        n = m.group(2)
        if n in own or n not in rets:
            continue
        if m.group(3) == "[":
            print("warning: line %d declares %s as data (%s); %s defines it as a function (%s): declare a "
                  "prototype and cast at the uses" % (text.count("\n", 0, m.start()) + 1, n, m.group(0).strip(),
                                                      rets[n][1], rets[n][0] or "int"))
        elif norm_type(m.group(1)) != rets[n][0] and not (
                {norm_type(m.group(1)), rets[n][0]} <= INTLIKE):
            print("warning: line %d declares %s returning `%s`; its definition in %s returns `%s`" % (
                text.count("\n", 0, m.start()) + 1, n, norm_type(m.group(1)) or "int", rets[n][1],
                rets[n][0] or "int"))
    seen = set()
    for n, (k, where) in defs.items():
        if n in own:
            continue
        for cm in re.finditer(r"(?<![\w.>])%s\s*\(" % re.escape(n), text):
            ls = text.rfind("\n", 0, cm.start()) + 1
            if not text[ls:ls + 1].isspace():
                continue        # a prototype at top level
            c, _ = install_c.arg_count(text, cm.end())
            if c != k and (n, c) not in seen:
                seen.add((n, c))
                print("warning: line %d calls %s with %d argument(s); its definition in %s has %d" % (
                    text.count("\n", 0, cm.start()) + 1, n, c, where, k))


def protos_differ(a, d):
    """the scratch compiled as tools/install_c.py installs it (prototypes dropped): {function: its bytes}, empty
    when dropping changes nothing in the text. install_c drops the scratch's prototypes of callees the target
    declares or leaves undeclared, so a narrow parameter type (u8 / s16) in a scratch prototype can make ccheck say
    OK while the installed C differs."""
    import install_c
    tp = os.path.join(ROOT, "src", a.prog, a.prog + ".c")
    keep = set(re.findall(r"(?m)^[\w][\w \*]*?\b(\w+)\s*\([^;{}]*\)\s*\{", open(tp).read())) \
        if os.path.exists(tp) else set()
    src = open(a.src).read()
    dropped = install_c.drop_prototypes(src, keep)
    if dropped == src:
        return {}
    d2 = os.path.join(d, "np")
    os.makedirs(d2, exist_ok=True)
    src2 = os.path.join(d2, os.path.basename(a.src))
    open(src2, "w").write(dropped)
    try:
        text2, funcs2, _ = compile_c(src2, a, d2)
    except SystemExit:
        print("warning: the scratch does not compile with its prototypes dropped (--no-protos): install_c "
              "will fail or change it")
        return {}
    except Exception:
        return {}
    return {n: text2[o:o + sz] for n, o, sz in funcs2}


def jtbl_warnings(obj, name, off, size, want, prog, addr):
    """Compare the jump tables the function's code reaches with retail's: ccheck masks the %hi / %lo of the table
    address and the rodata is not compared, so a wrong case-to-label mapping (an empty case sent to another
    label) passes as OK and fails only at link. For each table: our entries (labels inside the function, as
    offsets) against the retail jtbl's (asm/<prog>/data/*.s). -> list of warning lines."""
    import jtbl
    rel = []
    for l in subprocess.run(["mipsel-linux-gnu-objdump", "-r", obj], capture_output=True, text=True).stdout.splitlines():
        m = re.match(r"RELOCATION RECORDS FOR \[(\S+)\]", l)
        if m:
            sec = m.group(1)
            continue
        m = re.match(r"([0-9a-f]{8})\s+(R_MIPS_\w+)\s+(\S+)", l)
        if m:
            rel.append((sec, int(m.group(1), 16), m.group(2), m.group(3)))
    if not any(s_ == ".rodata" for s_, _, _, _ in rel):
        return []
    d = os.path.dirname(obj)
    subprocess.run(["mipsel-linux-gnu-objcopy", "-O", "binary", "-j", ".rodata", obj, d + "/r.bin"], check=True)
    rod = open(d + "/r.bin", "rb").read()
    subprocess.run(["mipsel-linux-gnu-objcopy", "-O", "binary", "-j", ".text", obj, d + "/tj.bin"], check=True)
    txt = open(d + "/tj.bin", "rb").read()
    wd = lambda b, i: struct.unpack("<I", b[i:i + 4])[0]
    ents = {o: wd(rod, o) for s_, o, t, sym in rel if s_ == ".rodata" and t == "R_MIPS_32" and sym == ".text"}
    tables = jtbl.retail_tables("asm/" + prog)
    out, hi = [], {}
    for s_, o, t, sym in rel:
        if s_ != ".text" or sym != ".rodata" or not off <= o < off + size:
            continue
        if t == "R_MIPS_HI16":
            hi[o] = o
            continue
        if t != "R_MIPS_LO16" or not hi:
            continue
        ho = max(h for h in hi if h < o) if any(h < o for h in hi) else None
        if ho is None:
            continue
        lo = lambda w: (w & 0xFFFF) - (0x10000 if w & 0x8000 else 0)
        ours_ro = ((wd(txt, ho) & 0xFFFF) << 16) + lo(wd(txt, o))
        i = o - off
        if i >= len(want) or ho - off >= len(want):
            continue
        r_addr = ((wd(want, ho - off) & 0xFFFF) << 16) + lo(wd(want, i))
        ret = tables.get("jtbl_%08X" % (r_addr & 0xFFFFFFFF))
        if ret is None or ours_ro not in ents:
            continue
        mine = []
        k = ours_ro
        while k in ents and len(mine) < len(ret):
            mine.append(ents[k] - off)
            k += 4
        theirs = [x - addr for x in ret]
        bad = [(j, a_, b_) for j, (a_, b_) in enumerate(zip(mine, theirs)) if a_ != b_]
        if len(mine) != len(theirs):
            out.append("warning: %s: jump table jtbl_%08X has %d entries, ours %d" % (
                name, r_addr & 0xFFFFFFFF, len(theirs), len(mine)))
        if bad:
            out.append("warning: %s: jump table jtbl_%08X differs from retail in %d of %d entries (passes ccheck, "
                       "fails the link): %s" % (name, r_addr & 0xFFFFFFFF, len(bad), len(theirs), ", ".join(
                           "[%d] ours +0x%X retail +0x%X" % b for b in bad[:6])))
    return out


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("src")
    ap.add_argument("--prog", default="main")
    ap.add_argument("--cc", help="override the file's // CC (default gcc-2.8.1-psx)")
    ap.add_argument("--aspsx", help="override // ASPSX (default 2.79)")
    ap.add_argument("--flags", help="override // FLAGS (default -O2 -G0)")
    ap.add_argument("--as", dest="asm", help="override // AS (maspsx or gnu)")
    ap.add_argument("--epilogue", help="override // EPILOGUE (sony, or none)")
    ap.add_argument("--return", dest="ret", help="override // RETURN (sony, or none)")
    ap.add_argument("--no-protos", action="store_true",
                    help="drop the prototypes as tools/install_c.py does (kept: functions used as values or defined "
                         "in the scratch or in src/<prog>/<prog>.c)")
    ap.add_argument("--skip-protos-check", action="store_true",
                    help="do not compile the scratch a second time with its prototypes dropped (the default warns "
                         "when that compile differs: install_c would produce different code)")
    ap.add_argument("-v", action="store_true")
    ap.add_argument("--all", action="store_true", help="also check the INCLUDE_ASM functions (sanity test)")
    ap.add_argument("--func", action="append", help="check only these functions (repeatable)")
    ap.add_argument("--sbs", action="store_true", help="side-by-side diff of each DIFF function (tools/sbs.py)")
    ap.add_argument("--sbs-all", action="store_true", help="with --sbs: print the equal lines too")
    ap.add_argument("--real", dest="sbs_real", action="store_true",
                    help="with --sbs: hide relocation-only differences (tools/sbs.py --real)")
    a, rest = ap.parse_known_args()
    a.cflags = rest
    binary, delta, syms = prog_info(a.prog)
    sizes = retail_sizes(a.prog)
    d = tempfile.mkdtemp()
    a.src = os.path.abspath(a.src)
    if a.no_protos:    # the scratch as tools/install_c.py would install it: prototypes dropped
        import install_c
        tp = os.path.join(ROOT, "src", a.prog, a.prog + ".c")
        keep = set(re.findall(r"(?m)^[\w][\w \*]*?\b(\w+)\s*\([^;{}]*\)\s*\{", open(tp).read())) \
            if os.path.exists(tp) else set()
        src2 = os.path.join(d, "noprotos_" + os.path.basename(a.src))
        open(src2, "w").write(install_c.drop_prototypes(open(a.src).read(), keep))
        a.src = src2
    argcount_warnings(a.src, a.prog)
    text, funcs, rel = compile_c(a.src, a, d)
    np_bytes = protos_differ(a, d) if not a.no_protos and not a.skip_protos_check else {}
    bad = 0
    asm_included = {n[:-len(".NON_MATCHING")] for n, _, _ in funcs if n.endswith(".NON_MATCHING")}
    if not a.all:   # INCLUDE_ASM functions are the retail bytes by construction: only the C ones are checked
        funcs = [f for f in funcs if f[0] not in asm_included and not f[0].endswith(".NON_MATCHING")]
    for name, off, size in funcs:
        if a.func and name not in a.func:
            continue
        addr = syms.get(name) or (int(name[5:], 16) if re.fullmatch(r"func_[0-9A-Fa-f]{8}", name) else None)
        if addr is None:
            print("?    %s (no address)" % name); continue
        want = binary[addr - delta: addr - delta + size]
        got = text[off: off + size]
        diffs = []
        for i in range(0, size, 4):
            g, w = struct.unpack("<I", got[i:i + 4])[0], struct.unpack("<I", want[i:i + 4])[0]
            if off + i in rel:
                op = g >> 26
                if op in (2, 3):
                    g, w = g & 0xFC000000, w & 0xFC000000
                else:
                    g, w = g & 0xFFFF0000, w & 0xFFFF0000
            if g != w:
                diffs.append((i, g, w))
        want_size = sizes.get(name)
        if want_size is not None and want_size != size:
            diffs.append((-1, size, want_size))
        jt = []
        if want_size is None or want_size == size:
            try:
                jt = jtbl_warnings(d + "/a.o", name, off, size, want, a.prog, addr)
            except Exception as e:     # never let the check itself stop a ccheck
                print("note: jump-table check failed: %s" % e)
        ok = not diffs and not jt
        bad += not ok
        order = ""
        if diffs and (want_size is None or want_size == size):
            # the same instructions in another order (relocated fields masked): the schedulers' choice
            wd = lambda b, i: struct.unpack("<I", b[i:i + 4])[0]
            rtop = {wd(got, i) >> 16 for i in range(0, size, 4) if off + i in rel}
            rjal = any(wd(got, i) >> 26 == 3 for i in range(0, size, 4) if off + i in rel)
            mk = lambda w, r: (w >> 26, "R") if (r or rjal) and w >> 26 == 3 else \
                (w >> 16, "R") if r or (w >> 16) in rtop else (w, "")
            ours_w = sorted(mk(wd(got, i), off + i in rel) for i in range(0, size, 4))
            want_w = sorted(mk(wd(want, i), False) for i in range(0, size, 4))
            if ours_w == want_w:
                order = " (order only: the same instructions; tools/prio.py %s %s --sched)" % (
                    os.path.relpath(a.src, ROOT) if a.src.startswith(ROOT) else a.src, name)
        aligned = ""
        if want_size is not None and want_size != size:
            # another length: the positional count is meaningless past the first insertion; the score of
            # score() (difflib-aligned words + the length difference), the number regswap / variants / permlines use
            import nearcopy
            aligned = " (score %d: %d word(s) %s, aligned)" % (
                nearcopy.aligned_off(got, binary[addr - delta: addr - delta + want_size]) +
                abs(size - want_size) // 4, abs(size - want_size) // 4, "extra" if size > want_size else "short")
        print("%s %s %08X (%d bytes)%s%s%s" % ("OK  " if ok else "DIFF", name, addr, size,
                                             "" if ok else ", %d words differ" % len(diffs) if diffs else ", code equal, jump table differs",
                                             aligned, order))
        for w_ in jt:
            print(w_)
        if name in np_bytes and np_bytes[name] != got:
            print("warning: %s compiles differently with the scratch's prototypes dropped (--no-protos): "
                  "install_c will produce different code (%s); drop narrow prototypes, cast at the call" % (
                      name, "%d bytes there" % len(np_bytes[name]) if len(np_bytes[name]) != size else
                      "first difference at +0x%X" % next(i for i in range(0, size, 4)
                                                         if np_bytes[name][i:i + 4] != got[i:i + 4])))
        if a.v:
            for i, g, w in diffs:
                if i < 0:
                    print("    size: got 0x%X bytes, retail 0x%X" % (g, w))
                else:
                    print("    +%03X got %08X want %08X" % (i, g, w))
        if a.sbs and not ok:
            import sbs
            n = want_size or size
            print(sbs.render(d + "/a.o", name, binary[addr - delta: addr - delta + n], a.prog, addr, a.sbs_all,
                             real=a.sbs_real))
    subprocess.run(["rm", "-rf", d])
    sys.exit(1 if bad else 0)


if __name__ == "__main__":
    main()

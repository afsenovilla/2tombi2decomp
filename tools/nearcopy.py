#!/usr/bin/env python3
"""Near-copy finder: put matched C into pending functions that are close variants of it.

  python3 -I tools/nearcopy.py [PROG ...] [--max-diff 8] [--max-frac 0.25] [--top 4] [--ratio 0.85] [-j N]
      [--names A,B] [--install] [--near] [-v]
  python3 -I tools/nearcopy.py --lib [main boot] [--max-diff 8] [--install] [-v]

For every pending function (an INCLUDE_ASM line of src/<prog>/<prog>.c; default every program) the matched C
functions of every program are ranked by their masked words (tools/funcstats.py mask(): relocated fields and
load/store/addiu offsets hidden):
  - same length and at most max(--max-diff, --max-frac * length) masked words differing (0 = an exact copy, what
    tools/dupsweep.py does);
  - with --ratio R, also other lengths within 15 % whose difflib ratio is >= R (these can only match after hand
    edits: they are written as near misses with --near, never installed).
The --top best distinct texts are compiled in place of the target (renamed, with the #define macros, static
inline helpers and declarations the body uses, transitively). When the bytes differ only in the 16-bit immediates
of otherwise identical instructions (constants, load/store offsets, andi/slti masks), the literals of the C are
patched: every occurrence, or a single one, of each differing value (an offset also as an index scaled by the
access size), up to three rounds; a one-word `move` / `li K` difference tries each use of each variable as K (or
each literal K as each variable), a `li K` / folded `addiu rs,K2` difference tries each literal K as each
`variable + K2` (or the reverse); an slti / sltiu constant also as the literal one below it (`x <= K`, a case
bound, a min / max clamp); constants of the static inline helpers the body uses are patched with it (the helper
copy goes with the scratch; tools/install_c.py renames it when the target's differs). --lib does the same for the
library files between MAIN.EXE and SCUS_944.54 (whole files copied with their set-up header). A match has the symbols it references renamed to what the target program calls
those addresses (relocations read against the retail bytes, callees too; names no program file defines, also
another program's alias names, get an alias line in config/aliases_<prog>.ld at install time).

Matches go to build/nearcopy/<prog>/<name>.c (install_c.py scratch files); --install installs them with
tools/install_c.py (linked build checked; files with clashing declarations go in separate batches). --near also
writes the closest attempt of every target that did not match to build/nearcopy/<prog>/near/<name>.c, headed by
how many words are off, where the C came from and a one-line summary of how the two retail functions differ
(`constants only`, an extra / missing block at +off, register changes, other callees): starting points for hand matching (--near alone implies
--ratio 0.8; pass --ratio to change it).
"""
import argparse, collections, concurrent.futures as cf, difflib, glob, itertools, os, re, shutil, struct, \
    subprocess, sys, tempfile

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))
import cc, dupsweep as DS, libsweep as L, ptsrc
from funcstats import mask

OUT = os.path.join(ROOT, "build", "nearcopy")
PRELUDE = DS.PRELUDE
SIGNED = {8, 9, 0xA, 0xB} | set(range(0x20, 0x40))      # addi addiu slti sltiu, loads and stores
ACCESS = {0x20: 1, 0x24: 1, 0x28: 1, 0x21: 2, 0x25: 2, 0x29: 2, 0x23: 4, 0x2B: 4, 0x22: 4, 0x26: 4, 0x2A: 4,
          0x2E: 4, 0x32: 4, 0x3A: 4}


def progs_list():
    return sorted(os.path.basename(y)[:-5] for y in glob.glob(os.path.join(ROOT, "config", "*.yaml")))


def asm_index(prog):
    """name -> (address, size) of every function of the program, from its splat .s files."""
    out = {}
    for f in glob.glob(os.path.join(ROOT, "asm", prog, "*matchings", "**", "*.s"), recursive=True):
        t = open(f).read(4000)
        m = re.search(r"^nonmatching (\w+),\s*(0x[0-9A-Fa-f]+)", t, re.M)
        a = re.search(r"/\* \w+ ([0-9A-F]{8}) [0-9A-F]{8} \*/", t)
        if m and a:
            out[m.group(1)] = (int(a.group(1), 16), int(m.group(2), 16))
    return out


def defined_names(prog):
    """every name the program's link defines (symbol files, aliases, splat labels of its .s files)."""
    out = set(DS.names_by_addr(prog).values()) | set(L.read_aliases(prog)) | DS.GLOBAL_NAMES
    for f in glob.glob(os.path.join(ROOT, "asm", prog, "**", "*.s"), recursive=True):
        out |= set(re.findall(r"^\s*(?:glabel|dlabel|jlabel|alabel)\s+(\w+)", open(f).read(), re.M))
    return out


class Prog:
    def __init__(self, prog):
        self.name = prog
        self.binary, self.delta = L.prog_bytes(prog)
        self.funcs = asm_index(prog)
        self.src = os.path.join(ROOT, "src", prog, prog + ".c")
        text = open(self.src).read() if os.path.exists(self.src) else ""
        self.pending = set(re.findall(r'INCLUDE_ASM\("[^"]+", (\w+)\);', text))
        # asm by design (tools/asm_by_design.py --game): still INCLUDE_ASM (no C source), never a target
        self.by_design = set(re.findall(r'(?m)^// ASM by design: [^\n]*\nINCLUDE_ASM\([^,]+,\s*(\w+)\)', text))
        self.includes = [l for l in re.findall(r"(?m)^#include .*$", text)
                         if not re.search(r'"(common|game|m2c)\.h"', l)]
        self.nb = DS.names_by_addr(prog)
        for n, (ad, _) in self.funcs.items():
            self.nb.setdefault(ad, n)
        self.addr_set = {ad for ad, _ in self.funcs.values()}

    def want(self, name):
        ad, size = self.funcs[name]
        return self.binary[ad - self.delta: ad - self.delta + size]

    def key(self, name):
        b = self.want(name)
        return tuple(mask(w) for w in struct.unpack("<%dI" % (len(b) // 4), b[:len(b) // 4 * 4]))


def compare(obj, name, want):
    """(differing word offsets [(i, ours, retail)], text, size or None) of `name` in obj against the retail bytes,
    relocated fields masked as libsweep.matches does. size None: not found; a size mismatch is reported as is."""
    d = os.path.dirname(obj)
    subprocess.run(["mipsel-linux-gnu-objcopy", "-O", "binary", "-j", ".text", obj, d + "/t.bin"], check=True)
    text = open(d + "/t.bin", "rb").read()
    off = size = None
    for l in subprocess.run(["mipsel-linux-gnu-nm", "-S", "--defined-only", obj], capture_output=True,
                            text=True).stdout.splitlines():
        p = l.split()
        if len(p) == 4 and p[3] == name and p[2] in "Tt":
            off, size = int(p[0], 16), int(p[1], 16)
    if off is None:
        return None, text, None
    rel = set()
    for l in subprocess.run(["mipsel-linux-gnu-objdump", "-r", "-j", ".text", obj], capture_output=True,
                            text=True).stdout.splitlines():
        m = re.match(r"([0-9a-f]{8})\s+R_MIPS_", l)
        if m:
            rel.add(int(m.group(1), 16) - off)
    diffs = []
    ours = text[off:off + size]
    for i in range(0, min(size, len(want)), 4):
        g = struct.unpack("<I", ours[i:i + 4])[0]
        w = struct.unpack("<I", want[i:i + 4])[0]
        if i in rel:
            mk = 0xFC000000 if g >> 26 in (2, 3) else 0xFFFF0000
            if g & mk == w & mk:
                continue
        elif g == w:
            continue
        diffs.append((i, g, w, i in rel))
    return diffs, ours, size


def words_off(diffs, size, want):
    if diffs is None:
        return 10 ** 6
    return len(diffs) + abs(size - len(want)) // 4


def aligned_off(ours, want):
    """words off for functions of different lengths: masked words aligned by difflib."""
    a = [mask(w) for w in struct.unpack("<%dI" % (len(ours) // 4), ours[:len(ours) // 4 * 4])]
    b = [mask(w) for w in struct.unpack("<%dI" % (len(want) // 4), want)]
    sm = difflib.SequenceMatcher(None, a, b, autojunk=False)
    return sum(max(i2 - i1, j2 - j1) for tag, i1, i2, j1, j2 in sm.get_opcodes() if tag != "equal")


def imm_pairs(diffs):
    """[(ours, retail, access size)] when every differing word is the same I-type instruction with another 16-bit
    immediate (no relocated field); None otherwise. One compiled value must map to one retail value."""
    out = {}
    for i, g, w, isrel in diffs:
        op = g >> 26
        if isrel or (g >> 16) != (w >> 16) or op < 8:
            return None
        gi, wi = g & 0xFFFF, w & 0xFFFF
        if op in SIGNED:
            gi = gi - 0x10000 if gi & 0x8000 else gi
            wi = wi - 0x10000 if wi & 0x8000 else wi
        if out.get(gi, (wi,))[0] != wi:
            return None
        out[gi] = (wi, ACCESS.get(op, 1), op)
    return [(g, w, s, op) for g, (w, s, op) in out.items()] or None


def literal_hits(body, v):
    """spans of the C literals that give the value v (a negative one with its minus sign)."""
    a = abs(v)
    hits = []
    for m in re.finditer(r"(?<![\w.])(?:0[xX]0*%x|%d)[uUlL]*(?![\w.])" % (a, a), body, re.I):
        st = m.start()
        pre = body[:st].rstrip()
        neg = pre.endswith("-") and not pre.endswith("--")
        if (v < 0) != neg:
            continue
        hits.append((len(pre) - 1 if neg else st, m.end()))
    return sorted(set(hits))


def lit(v, neg_ctx):
    """text for the value v replacing a literal (neg_ctx: the old literal carried its minus sign)."""
    if v < 0:
        return "-0x%X" % -v
    return ("+ 0x%X" % v) if neg_ctx else "0x%X" % v


def patches(body, pairs, limit=24):
    """C bodies with the literals of each (ours -> retail) pair replaced: every occurrence, or one of them (an
    offset also as an index scaled by the access size). At most `limit` combinations, the all-occurrences one
    first."""
    choices = []
    for g, w, size, op in pairs:
        opts = []
        alts = [(g // div, w // div) for div in ([1] + ([size] if size > 1 and g % size == 0 and w % size == 0
                                                         else []))]
        if op in (0xA, 0xB):    # slti / sltiu K+1: `x <= K`, `x > K`, a case bound or a min / max clamp
            alts.append((g - 1, w - 1))
        for gv, wv in alts:
            hits = literal_hits(body, gv)
            if hits:
                opts.append([(h, wv) for h in hits])
                if len(hits) > 1:
                    opts += [[(h, wv)] for h in hits]     # each occurrence alone (a repeated constant)
        if not opts:
            return []
        choices.append(opts)
    out = []
    for combo in itertools.islice(itertools.product(*choices), limit):
        reps = sorted((h, v) for opt in combo for h, v in opt)
        if any(a[0][1] > b[0][0] for a, b in zip(reps, reps[1:])):
            continue     # overlapping spans
        t = body
        for (st, en), v in reversed(reps):
            t = t[:st] + lit(v, t[st] == "-") + t[en:]
        out.append(t)
    return out


def _move_li(word):
    """('move', rd) / ('li', rt, value) / None for one instruction word."""
    op = word >> 26
    if op == 0 and word & 0x3F in (0x21, 0x25) and (word >> 16) & 0x1F == 0:
        return ("move", (word >> 11) & 0x1F)
    if op in (9, 0xD) and (word >> 21) & 0x1F == 0:
        v = word & 0xFFFF
        if op == 9 and v & 0x8000:
            v -= 0x10000
        return ("li", (word >> 16) & 0x1F, v)
    return None


def variables(body):
    """parameter and local variable names of a function definition."""
    head = body[:body.find("{")]
    names = re.findall(r"(\w+)\s*(?:\[[^\]]*\])?\s*[,)]", head[head.find("(") + 1:] + ")")
    names += re.findall(r"(?m)^\s+(?:(?:const|volatile|register|unsigned|signed|struct \w+|\w+)\s+)+\**\s*(\w+)\s*[;=\[]",
                        body[body.find("{"):])
    return [n for n in dict.fromkeys(names) if n not in ptsrc.KEYWORDS and n != "void"]


def form_patches(body, g, w, limit=24):
    """C bodies for a one-word diff where the code has `move` and retail `li K` (a variable there is the constant
    K in the target: each use of each variable replaced by K, one at a time) or the reverse (each literal K
    replaced by each variable)."""
    a, b = _move_li(g), _move_li(w)
    if not a or not b or a[0] == b[0] or a[1] != b[1]:
        return []
    start = body.find("{") + 1
    names = variables(body)
    out = []
    if a[0] == "move":
        for n in names:
            for m in re.finditer(r"(?<![\w.>])\b%s\b(?!\s*(?:[-+*/%%&|^]|<<|>>)?=[^=])(?!\s*\+\+|\s*--)" % n,
                                 body[start:]):
                at = start + m.start()
                out.append(body[:at] + lit(b[2], False) + body[at + len(n):])
    else:
        for st, en in literal_hits(body, a[2]):
            if st < start:
                continue
            for n in names:
                out.append(body[:st] + n + body[en:])
    return out[:limit]


def fold_patches(body, g, w, limit=24):
    """C bodies for a one-word diff between `li rt,K` and `addiu rt,rs,K2` (rs a register): retail folds a
    constant into an addition the C does not have (each literal K becomes each variable + K2), or the reverse
    (each `variable +/- K2` becomes K)."""
    a, b = _move_li(g), _move_li(w)
    op_g, op_w = g >> 26, w >> 26
    start = body.find("{") + 1
    out = []

    def addiu(x):
        if x >> 26 != 9 or (x >> 21) & 0x1F == 0:
            return None
        v = x & 0xFFFF
        return ((x >> 16) & 0x1F, v - 0x10000 if v & 0x8000 else v)
    if a and a[0] == "li" and addiu(w) and a[1] == addiu(w)[0]:
        k2 = addiu(w)[1]
        for st, en in literal_hits(body, a[2]):
            if st < start:
                continue
            for n in variables(body):
                out.append(body[:st] + "(%s %s 0x%X)" % (n, "-" if k2 < 0 else "+", abs(k2)) + body[en:])
    elif b and b[0] == "li" and addiu(g) and b[1] == addiu(g)[0]:
        k2 = addiu(g)[1]
        for m in re.finditer(r"\b([A-Za-z_]\w*)\s*([+-])\s*(0[xX][0-9A-Fa-f]+|\d+)\b", body[start:]):
            v = int(m.group(3), 0) * (-1 if m.group(2) == "-" else 1)
            if v == k2:
                out.append(body[:start + m.start()] + lit(b[2], False) + body[start + m.end():])
    return out[:limit]


def build_text(includes, decls, body):
    return PRELUDE + "".join(i + "\n" for i in includes) + "\n".join(decls) + "\n\n" + body + "\n"


def prepare(src_prog, sname, text, decls, tname):
    body = re.sub(r"\b%s\b" % re.escape(sname), tname, text)
    ext = DS.needed(body, decls)
    # functions used as values (callbacks) need a declaration
    for fnm in sorted(set(re.findall(r"(?<![\w(])((?:func_|f_)\w+)\b(?!\s*\()", body)) - {tname}):
        if not any(re.search(r"\b%s\b" % fnm, e) for e in ext):
            ext = ext + ["void %s();" % fnm]
    return body, ext


def attempt(tp, tname, cand, workdir):
    """try one candidate (nd, src_prog, src_name, text, decls, includes) for target tname of Prog tp.
    -> (words off, scratch text or None, syms) ; scratch text set on a match."""
    nd, sp, sname, text, decls, incs = cand
    want = tp.want(tname)
    body, ext = prepare(sp, sname, text, decls, tname)
    # static inline helpers go with the body: their constants are patched like the function's own (an inlined
    # copy with other constants; install_c renames a helper the target defines differently)
    helpers = [e for e in ext if ptsrc.strip_comments(e).strip().startswith("static") and e.rstrip().endswith("}")]
    if helpers:
        ext = [e for e in ext if e not in helpers]
        body = "\n\n".join(helpers) + "\n\n" + body
    fstart = re.compile(r"(?m)^[^\n;#]*\b%s\s*\(" % re.escape(tname))
    d = tempfile.mkdtemp(dir=workdir)
    best = (10 ** 6, None, None)
    try:
        cur = [body]
        seen = set()
        for rnd in range(4):
            nxt = []
            for b in cur:
                if b in seen:
                    continue
                seen.add(b)
                src = os.path.join(d, "x.c")
                open(src, "w").write(build_text(incs, ext, b))
                try:
                    cc.compile_c(src, os.path.join(d, "a.o"))
                except cc.CompileError:
                    continue
                diffs, ours, size = compare(os.path.join(d, "a.o"), tname, want)
                if diffs is None:
                    continue
                if size != len(want):
                    off = aligned_off(ours, want)
                    if off < best[0]:
                        best = (off, None, build_text(incs, ext, b))
                    continue
                off = len(diffs)
                if off == 0 and cc.text_size(os.path.join(d, "a.o")) == size:
                    syms = {}
                    if L.matches(os.path.join(d, "a.o"), tname, want, syms):
                        return 0, (b, ext, incs), syms
                if off < best[0]:
                    best = (off, None, build_text(incs, ext, b))
                pairs = imm_pairs(diffs)
                if pairs and rnd < 3:
                    nxt += patches(b, pairs)
                elif len(diffs) == 1 and not diffs[0][3] and rnd < 3:
                    m = fstart.search(b)
                    at = m.start() if m else 0
                    nxt += [b[:at] + x for x in form_patches(b[at:], diffs[0][1], diffs[0][2]) +
                            fold_patches(b[at:], diffs[0][1], diffs[0][2])]
            cur = nxt[:24]
            if not cur:
                break
    finally:
        shutil.rmtree(d, ignore_errors=True)
    return best


def renames(tp, tname, syms, defined):
    """{source name: target name} for the relocated symbols (the target's name for each address), and the
    names to add as aliases (no file of the target defines them)."""
    ren, new = {}, {}
    for s_, at in syms.items():
        if s_ == tname or s_.startswith(".") or s_ in DS.GLOBAL_NAMES:
            continue
        want = tp.nb.get(at) or ("func_%08X" % at if (at in tp.addr_set or s_.startswith(("func_", "f_")))
                                 else "D_%08X" % at)
        if want != s_:
            ren[s_] = want
        if want not in defined:
            new[want] = at
    return ren, new


def apply_renames(text, ren):
    if not ren:
        return text
    pat = re.compile(r"\b(%s)\b" % "|".join(re.escape(k) for k in sorted(ren, key=len, reverse=True)))
    return pat.sub(lambda m: ren[m.group(1)], text)


def name_addrs(prog):
    """name -> address of every name the program's link knows (symbol files, aliases, linker-wide names)."""
    out = {}
    for f in [os.path.join(ROOT, "config", "undefined_syms.ld"), os.path.join(ROOT, "config", "scratchpad.ld"),
              os.path.join(ROOT, "config", "symbol_addrs_%s.txt" % prog),
              os.path.join(ROOT, "build", "undefined_syms_auto.%s.txt" % prog),
              os.path.join(ROOT, "build", "undefined_funcs_auto.%s.txt" % prog), L.aliases_path(prog)]:
        if os.path.exists(f):
            for l in open(f):
                m = re.match(r"\s*(\w+)\s*=\s*0x([0-9A-Fa-f]+)", l)
                if m:
                    out.setdefault(m.group(1), int(m.group(2), 16))
    return out


def fix_names(text, prog, workdir=None):
    """Rename the symbols a scratch file's functions reference to the program's names for the addresses the
    retail bytes give them (the relocations read against retail): names from another program, or a splat name
    of another address. -> (new text, {old: new}, {alias name: address} for names no file of the program
    defines). Functions that do not compile or have no retail address are left alone."""
    import ccheck
    binary, delta, syms_ = ccheck.prog_info(prog)
    sizes = ccheck.retail_sizes(prog)
    known = name_addrs(prog)
    nb = DS.names_by_addr(prog)
    d = tempfile.mkdtemp(dir=workdir or os.path.join(ROOT, "build"))
    ren, alias = {}, {}
    try:
        src = os.path.join(d, "x.c")
        open(src, "w").write(text)
        try:
            cc.compile_c(src, os.path.join(d, "a.o"))
        except cc.CompileError:
            return text, {}, {}
        obj = os.path.join(d, "a.o")
        subprocess.run(["mipsel-linux-gnu-objcopy", "-O", "binary", "-j", ".text", obj, d + "/t.bin"], check=True)
        otext = open(d + "/t.bin", "rb").read()
        defined = None
        for l in subprocess.run(["mipsel-linux-gnu-nm", "-S", "--defined-only", obj], capture_output=True,
                                text=True).stdout.splitlines():
            p = l.split()
            if len(p) != 4 or p[2] not in "Tt":
                continue
            name, off, size = p[3], int(p[0], 16), int(p[1], 16)
            ad = syms_.get(name) or (int(name[5:], 16) if re.fullmatch(r"func_[0-9A-F]{8}", name) else None)
            if ad is None or sizes.get(name) != size:
                continue
            conf = {}
            got = L.reloc_symbols(obj, name, binary[ad - delta: ad - delta + size], otext, off, conf)
            for s_, ads in sorted(conf.items()):
                print("fix_names: %s: %s gets %d addresses from the retail relocations (%s): one C name for two "
                      "retail symbols (e.g. &buf[k] for the next symbol, or a struct base + offset); not renamed"
                      % (name, s_, len(ads), ", ".join("%08X" % x for x in sorted(ads))))
            for s_, at in (got or {}).items():
                if s_.startswith(".") or s_ == name:
                    continue
                emb = re.fullmatch(r"(?:D|func|jtbl)_([0-9A-F]{8})(?:_\w+)?", s_)
                have = known.get(s_, int(emb.group(1), 16) if emb and s_ not in known else None)
                if have == at:
                    new = s_
                else:
                    new = nb.get(at) or ("func_%08X" % at if s_.startswith(("func_", "f_")) else "D_%08X" % at)
                    if ren.get(s_, new) != new:
                        print("fix_names: %s is %s in one function and %s in %s: not renamed (two addresses for one "
                              "name; split it in two externs)" % (s_, ren[s_], new, name))
                        continue     # two addresses for one name: leave it to the build check
                    ren[s_] = new
                if new not in known and not re.fullmatch(r"func_[0-9A-F]{8}", new):
                    if defined is None:
                        defined = defined_names(prog)
                    if new not in defined:
                        # inside a table or past a label, or a name another program aliases (an install_c type
                        # alias D_xxxxxxxx_hash, a library name): no file of this program defines it
                        alias[new] = at
        ren = {k: v for k, v in ren.items() if k != v}
        return apply_renames(text, ren), ren, alias
    finally:
        shutil.rmtree(d, ignore_errors=True)


def load_sources(progs):
    """masked key -> list of (prog, name, text, decls, includes) of the matched C functions of every program."""
    out = collections.defaultdict(list)
    for p, tp in progs.items():
        for name, (text, decls) in DS.c_functions(p).items():
            if name not in tp.funcs:
                continue
            out[tp.key(name)].append((p, name, text, decls, tp.includes))
    return out


_INS = re.compile(r"/\* \w+ ([0-9A-F]{8}) [0-9A-F]{8} \*/\s+(\S+)\s*([^/\n]*)")


def _ins(prog, name):
    """[(offset, mnemonic, operands)] of a function's splat .s (any matchings dir), or None."""
    hits = glob.glob(os.path.join(ROOT, "asm", prog, "*matchings", "**", name + ".s"), recursive=True)
    if not hits:
        return None
    out = [(int(m.group(1), 16), m.group(2), m.group(3).strip()) for m in _INS.finditer(open(hits[0]).read())]
    return [(a - out[0][0], op, arg) for a, op, arg in out] if out else None


def near_summary(sp, sname, tprog, tname):
    """What differs between the source function's retail code and the target's, in a few words: `constants only`
    (same instructions, immediates differ), registers, an extra / missing block at +off, other callees. Relocated
    operands (%hi / %lo, labels) are compared by kind only; jal targets by name (a callee local to each overlay
    is not a difference)."""
    a, b = _ins(sp, sname), _ins(tprog, tname)
    if not a or not b:
        return "no asm to compare"
    norm = lambda x: re.sub(r"\.L[0-9A-F]+", ".L", re.sub(r"%(hi|lo)\([^)]*\)", r"%\1()", x))
    nums = lambda x: re.sub(r"-?\b(0x[0-9A-Fa-f]+|\d+)\b", "K", x)
    sm = difflib.SequenceMatcher(None, [x[1] for x in a], [x[1] for x in b], autojunk=False)
    consts, regs, blocks, calls = [], [], [], []
    local = lambda p, n: p != "main" and re.fullmatch(r"func_[0-9A-F]{8}", n)
    for tag, i1, i2, j1, j2 in sm.get_opcodes():
        if tag == "equal":
            for (_, op, x), (off, _, y) in zip(a[i1:i2], b[j1:j2]):
                if op in ("jal", "j") and x != y:
                    if not (local(sp, x) and local(tprog, y)) and op == "jal":
                        calls.append("%s->%s" % (x, y))
                elif norm(x) != norm(y):
                    (consts if nums(norm(x)) == nums(norm(y)) else regs).append(
                        "+%X %s" % (off, " -> ".join(re.findall(r"-?\b0x[0-9A-Fa-f]+\b|-?\b\d+\b", norm(x))[-1:] +
                                                   re.findall(r"-?\b0x[0-9A-Fa-f]+\b|-?\b\d+\b", norm(y))[-1:]))
                        if nums(norm(x)) == nums(norm(y)) else "+%X" % off)
        elif tag == "insert":
            blocks.append("extra %d words at +%X" % (j2 - j1, b[j1][0]))
        elif tag == "delete":
            blocks.append("missing %d words before +%X" % (i2 - i1, b[j1][0] if j1 < len(b) else len(b) * 4))
        else:
            blocks.append("%d -> %d words differ at +%X" % (i2 - i1, j2 - j1, b[j1][0]))
    parts = []
    if blocks:
        parts.append("; ".join(blocks[:4]) + (" ..." if len(blocks) > 4 else ""))
    if consts:
        parts.append("%d constant(s) (%s%s)" % (len(consts), ", ".join(consts[:4]), " ..." if len(consts) > 4 else ""))
    if regs:
        parts.append("%d operand / register change(s) (%s%s)" % (len(regs), " ".join(regs[:4]),
                                                                  " ..." if len(regs) > 4 else ""))
    if calls:
        parts.append("other callees: " + ", ".join(calls[:4]))
    if not parts:
        return "same retail code up to relocations (the C itself is off: types, names)"
    if consts and not (blocks or regs or calls):
        return "constants only: " + parts[0]
    return " | ".join(parts)


def find_candidates(key, sources, bylen, max_diff, max_frac, top, ratio):
    n = len(key)
    lim = max(max_diff, int(max_frac * n))
    cands, seen = [], set()
    for k2 in bylen.get(n, ()):
        nd = sum(1 for x, y in zip(key, k2) if x != y)
        if nd <= lim:
            for sp, sname, text, decls, incs in sources[k2]:
                if text not in seen:
                    seen.add(text)
                    cands.append((nd, sp, sname, text, decls, incs))
    if ratio:
        for L2 in range(int(n * 0.85), int(n * 1.15) + 2):
            if L2 == n:
                continue
            for k2 in bylen.get(L2, ()):
                sm = difflib.SequenceMatcher(None, key, k2, autojunk=False)
                if sm.real_quick_ratio() < ratio or sm.quick_ratio() < ratio or sm.ratio() < ratio:
                    continue
                nd = n - sum(b.size for b in sm.get_matching_blocks())
                for sp, sname, text, decls, incs in sources[k2]:
                    if text not in seen:
                        seen.add(text)
                        cands.append((nd + abs(L2 - n), sp, sname, text, decls, incs))
    cands.sort(key=lambda c: (c[0], c[1] != "main"))
    return cands[:top]


def install(prog, files, verbose):
    """install the scratch files of one program in batches whose declarations do not clash."""
    batches = []
    for f in files:
        t = ptsrc.strip_comments(open(f).read())
        decl = {}
        for kind, seg in ptsrc.items(t):
            s = seg.strip()
            if not s or s.startswith(("#include", "//")) or (s.endswith("}") and ptsrc.func_name(s)
                                                             and not s.startswith("static")):
                continue
            for n in DS.decl_names(s) or ():
                decl[n] = s
        for b in batches:
            if all(b["decl"].get(k, v) == v for k, v in decl.items()):
                b["decl"].update(decl)
                b["files"].append((f, t))
                break
        else:
            batches.append({"decl": dict(decl), "files": [(f, t)]})
    done = []
    for i, b in enumerate(batches):
        seen, parts, funcs = set(), [], []
        for f, t in b["files"]:
            for kind, seg in ptsrc.items(t):
                s = seg.strip()
                if not s:
                    continue
                if s.endswith("}") and ptsrc.func_name(s) and not s.startswith("static"):
                    funcs.append(s)
                elif s not in seen:
                    seen.add(s)
                    parts.append(s)
        tmp = os.path.join(OUT, prog, "_batch%d.c" % i)
        open(tmp, "w").write("\n".join(parts) + "\n\n" + "\n\n".join(funcs) + "\n")
        r = subprocess.run([sys.executable, "-I", os.path.join(ROOT, "tools", "install_c.py"), tmp, "--prog", prog],
                           capture_output=True, text=True, cwd=ROOT)
        m = re.search(r"installed \d+ functions: (.*)", r.stdout)
        got = m.group(1).split() if m else []
        done += got
        if verbose or not got:
            print("  %s batch %d: %s" % (prog, i, (r.stdout + r.stderr).strip().splitlines()[-1:]), flush=True)
        os.unlink(tmp)
    return done


def lib_matched(prog):
    """name -> text of the matched library files of a program (src/<prog>/psyq/<lib>/<name>.c without an
    INCLUDE_ASM of their own name)."""
    out = {}
    for f in glob.glob(os.path.join(ROOT, "src", prog, "psyq", "*", "*.c")):
        n = os.path.basename(f)[:-2]
        t = open(f).read()
        if not re.search(r'INCLUDE_ASM\("[^"]+", %s\);' % re.escape(n), t) and re.search(r"\b%s\s*\(" % n, t):
            out[n] = (f, t)
    return out


def lib_copies(targets, progs, max_diff, install, verbose):
    """--lib: each pending library file of the targets against the matched library files of the other programs
    (MAIN.EXE <-> SCUS_944.54: the same Psy-Q objects): the same masked words (or at most max_diff differing),
    the file copied with its set-up header, the function renamed, names fixed from the relocations
    (fix_names), scored by ccheck; a match is written in place of the pending file (the linked build checked)."""
    import ccheck
    src = {}       # masked key -> [(prog, name, text)]
    for p in progs:
        tp = progs[p]
        for n, (f, text) in lib_matched(p).items():
            if n in tp.funcs:
                src.setdefault(tp.key(n), []).append((p, n, text))
    bylen = collections.defaultdict(list)
    for k in src:
        bylen[len(k)].append(k)
    work = tempfile.mkdtemp(prefix="tmp_nearcopy_lib_", dir=os.path.join(ROOT, "build"))
    found = []
    try:
        for p in targets:
            tp = progs[p]
            for tname, f in sorted(L.pending_files(p).items()):
                if tname not in tp.funcs or "ASM by design" in open(f).read(400):
                    continue
                k = tp.key(tname)
                if len(k) < 8:
                    continue
                cands = []
                for k2 in bylen.get(len(k), ()):
                    nd = sum(1 for x, y in zip(k, k2) if x != y)
                    if nd <= min(max_diff, len(k) // 4):
                        cands += [(nd, sp, sn, tx) for sp, sn, tx in src[k2] if sp != p or sn != tname]
                best = None
                for nd, sp, sn, tx in sorted(cands, key=lambda c: c[0])[:4]:
                    text = re.sub(r"\b%s\b" % re.escape(sn), tname, tx)
                    text = re.sub(r'INCLUDE_ASM\("asm/%s/' % sp, 'INCLUDE_ASM("asm/%s/' % p, text)
                    text, ren, alias = fix_names(text, p, work)
                    tmp = os.path.join(work, tname + ".c")
                    open(tmp, "w").write(text)
                    s = ccheck.score(tmp, p, tname, work)
                    if s is not None and (best is None or s < best[0]):
                        best = (s, sp, sn, text, alias)
                    if s == 0:
                        break
                if best is None:
                    continue
                if best[0]:
                    if verbose or best[0] <= 4:
                        print("near %s %s: %d words off <- %s %s" % (p, tname, best[0], best[1], best[2]))
                    continue
                print("MATCH %s %s <- %s %s" % (p, tname, best[1], best[2]), flush=True)
                found.append((p, tname, f, best[3], best[4]))
    finally:
        shutil.rmtree(work, ignore_errors=True)
    print("library copies matched: %d" % len(found))
    if not install:
        return
    for p, tname, f, text, alias in found:
        old = open(f).read()
        old_al = L.read_aliases(p)
        if alias:
            al = dict(old_al)
            al.update({k: v for k, v in alias.items() if k not in al})
            L.write_aliases(p, al)
        open(f, "w").write(text)
        r = subprocess.run([sys.executable, "tools/build.py", p, "--no-split"], capture_output=True, text=True,
                           cwd=ROOT)
        if " OK " in r.stdout:
            print("installed %s %s" % (p, tname), flush=True)
        else:
            open(f, "w").write(old)
            if alias:
                L.write_aliases(p, old_al)
            print("NOT INSTALLED: %s %s (linked build not OK)" % (p, tname), flush=True)


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("progs", nargs="*", help="target programs (default: all)")
    ap.add_argument("--max-diff", type=int, default=8, help="differing masked words always allowed")
    ap.add_argument("--max-frac", type=float, default=0.25, help="... or this fraction of the length")
    ap.add_argument("--top", type=int, default=4, help="candidates tried per target")
    ap.add_argument("--ratio", type=float, help="also other lengths with this difflib ratio (near misses only)")
    ap.add_argument("--names", help="only these targets (comma list)")
    ap.add_argument("--min-words", type=int, default=6, help="skip targets shorter than this")
    ap.add_argument("--install", action="store_true")
    ap.add_argument("--near", action="store_true", help="write the closest attempt of the targets left")
    ap.add_argument("-j", type=int, default=os.cpu_count())
    ap.add_argument("-v", action="store_true")
    ap.add_argument("--lib", action="store_true", help="library files: pending ones against the matched library "
                    "files of the other programs (main <-> boot)")
    a = ap.parse_args()
    if a.near and a.ratio is None:
        a.ratio = 0.8     # --near: other lengths too (the near misses worth hand work are often a few words longer)
    allp = progs_list()
    progs = {p: Prog(p) for p in allp}
    if a.lib:
        lp = [p for p in (a.progs or ["main", "boot"])]
        return lib_copies(lp, {p: progs[p] for p in ("main", "boot")}, a.max_diff, a.install, a.v)
    sources = load_sources(progs)
    bylen = collections.defaultdict(list)
    for k in sources:
        bylen[len(k)].append(k)
    print("%d matched C functions (%d distinct masked keys) to copy from" %
          (sum(len(v) for v in sources.values()), len(sources)), flush=True)
    targets = a.progs or allp
    names = set(a.names.split(",")) if a.names else None
    jobs = []
    for p in targets:
        tp = progs[p]
        for tname in sorted(tp.pending):
            if tname not in tp.funcs or tname in tp.by_design or (names and tname not in names):
                continue
            k = tp.key(tname)
            if len(k) < a.min_words:
                continue
            c = find_candidates(k, sources, bylen, a.max_diff, a.max_frac, a.top, a.ratio)
            if c:
                jobs.append((p, tname, c))
    print("%d pending functions have candidates" % len(jobs), flush=True)
    os.makedirs(OUT, exist_ok=True)
    work = tempfile.mkdtemp(prefix="tmp_nearcopy_", dir=os.path.join(ROOT, "build"))

    def run(job):
        p, tname, cands = job
        tp = progs[p]
        best = (10 ** 6, None, None, None)
        for c in cands:
            off, res, extra = attempt(tp, tname, c, work)
            if off == 0:
                return p, tname, c, 0, res, extra
            if off < best[0]:
                best = (off, c, extra, None)
        return p, tname, best[1], best[0], None, best[2]

    found = collections.defaultdict(list)
    near = []
    try:
        with cf.ThreadPoolExecutor(a.j) as ex:
            for p, tname, c, off, res, extra in ex.map(run, jobs):
                tp = progs[p]
                if res is None:
                    if c is not None:
                        near.append((off, p, tname, c[1], c[2], extra))
                    continue
                body, ext, incs = res
                ren, _ = renames(tp, tname, extra, set())
                txt = "// nearcopy: from %s %s (%d masked words differed)\n" % (c[1], c[2], c[0]) + \
                    apply_renames(build_text(incs, ext, body), ren)
                os.makedirs(os.path.join(OUT, p), exist_ok=True)
                f = os.path.join(OUT, p, tname + ".c")
                open(f, "w").write(txt)
                found[p].append((tname, f, extra))
                print("MATCH %s %s <- %s %s (%d)" % (p, tname, c[1], c[2], c[0]), flush=True)
    finally:
        shutil.rmtree(work, ignore_errors=True)
    print("matched: %d (%s)" % (sum(len(v) for v in found.values()),
                                ", ".join("%s %d" % (p, len(v)) for p, v in sorted(found.items()))))
    near.sort()
    if a.near:
        for off, p, tname, sp, sname, txt in near:
            if txt:
                os.makedirs(os.path.join(OUT, p, "near"), exist_ok=True)
                summ = near_summary(sp, sname, p, tname)
                open(os.path.join(OUT, p, "near", tname + ".c"), "w").write(
                    "// nearcopy: %d words off, C from %s %s\n// retail diff: %s\n" % (off, sp, sname, summ) + txt)
                print("near %s %s: %d off <- %s %s: %s" % (p, tname, off, sp, sname, summ))
    if near:
        print("closest left (words off): " + ", ".join("%s %s %d<-%s:%s" % (p, t, o, sp, sn)
                                                      for o, p, t, sp, sn, _ in near[:30]))
    if not a.install:
        return
    total = 0
    for p, items in sorted(found.items()):
        tp = progs[p]
        defined = defined_names(p)
        added = {}
        for tname, f, syms in items:
            _, new = renames(tp, tname, syms, defined)
            added.update({k: v for k, v in new.items() if not re.fullmatch(r"func_[0-9A-F]{8}", k)})
        if added:   # a data address no file of the program labels (inside a table, past a label)
            al = L.read_aliases(p)
            al.update(added)
            L.write_aliases(p, al)
        done = install(p, [f for _, f, _ in items], a.v)
        total += len(done)
        print("%s: installed %d of %d" % (p, len(done), len(items)), flush=True)
    print("installed %d" % total)


if __name__ == "__main__":
    main()

#!/usr/bin/env python3
"""Near-copy finder: put matched C into pending functions that are close variants of it.

  python3 -I tools/nearcopy.py [PROG ...] [--max-diff 8] [--max-frac 0.25] [--top 4] [--ratio 0.85] [-j N]
      [--names A,B] [--install] [--near] [-v]

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
access size), up to three rounds. A match has the symbols it references renamed to what the target program calls
those addresses (relocations read against the retail bytes; names no program file defines get an alias line in
config/aliases_<prog>.ld at install time).

Matches go to build/nearcopy/<prog>/<name>.c (install_c.py scratch files); --install installs them with
tools/install_c.py (linked build checked; files with clashing declarations go in separate batches). --near also
writes the closest attempt of every target that did not match to build/nearcopy/<prog>/near/<name>.c, headed by
how many words are off and where the C came from: starting points for hand matching.
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
        out[gi] = (wi, ACCESS.get(op, 1))
    return [(g, w, s) for g, (w, s) in out.items()] or None


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
    for g, w, size in pairs:
        opts = []
        for div in ([1] + ([size] if size > 1 and g % size == 0 and w % size == 0 else [])):
            hits = literal_hits(body, g // div)
            if hits:
                opts.append([(h, w // div) for h in hits])
                if len(hits) > 1:
                    opts += [[(h, w // div)] for h in hits]
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
            got = L.reloc_symbols(obj, name, binary[ad - delta: ad - delta + size], otext, off)
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
                        continue     # two addresses for one name: leave it to the build check
                    ren[s_] = new
                if new not in known and re.fullmatch(r"D_[0-9A-F]{8}", new):
                    if defined is None:
                        defined = defined_names(prog)
                    if new not in defined:
                        alias[new] = at   # inside a table or past a label: no file defines the name
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
    a = ap.parse_args()
    allp = progs_list()
    progs = {p: Prog(p) for p in allp}
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
            if tname not in tp.funcs or (names and tname not in names):
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
                open(os.path.join(OUT, p, "near", tname + ".c"), "w").write(
                    "// nearcopy: %d words off, C from %s %s\n" % (off, sp, sname) + txt)
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

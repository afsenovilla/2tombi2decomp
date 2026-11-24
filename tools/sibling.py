#!/usr/bin/env python3
"""Variant from sibling: matched C put into a pending function of the same skeleton, edited from the asm diff.

  python3 -I tools/sibling.py [PROG ...] [--ratio 0.65] [--names A,B] [--top 3] [--rounds 5] [--install] [-j N]
  python3 -I tools/sibling.py --from PROG:NAME [--src FILE.c] [PROG ...] [--ratio 0.6] [--install]

tools/nearcopy.py installs matched C into pending functions that differ in 16-bit immediates only (same length).
This tool goes further, for the family template method of AGENTS.md (match one member, derive its siblings): the
candidates are the matched functions of every program whose masked words align with the target at difflib ratio
>= --ratio (other lengths too), or, with --from, one matched function (or a scratch's function, --src) against every
pending function of the programs named. Each candidate is compiled in place of the target (renamed, with the
declarations, macros and static inline helpers it uses: nearcopy.prepare), aligned with the retail words, and
edited in rounds (a beam of the best --beam texts per round) by what the alignment shows:

  - imm:   an immediate that differs in otherwise equal instructions (constants, offsets, masks; nearcopy
           patches(): every occurrence or one, an offset also as an index);
  - sign:  lh <-> lhu, lb <-> lbu (or lw for lh ...) at offset O: the access type of the C at that offset is
           flipped (`*(s16 *)(p + O)`, `MEMBER_AT(s16, p, O)`, `H(p, O)` / `W(p, O)`, `p[O]` rewritten as
           a cast);
  - store+: retail stores K (li / zero) at offset O where the C does not: a statement `*(T *)(base + O) = K;`
           with the base of the C store next to it, inserted after / before that statement;
  - store-: the C stores at offset O where retail does not: that statement is dropped.

Callees and symbols differ freely (relocations are masked in the comparison): a match has them renamed to the
target program's names for the addresses retail relocates (nearcopy.renames; alias lines for D_ addresses no file
labels are added at --install). Matches go to build/sibling/<prog>/<name>.c and the closest attempt of each target
left to build/sibling/<prog>/near/<name>.c headed by its words off and the edits applied; --install installs the
matches with tools/install_c.py (linked build checked).
"""
import argparse, collections, concurrent.futures as cf, difflib, os, re, shutil, struct, sys, tempfile

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))
import cc, nearcopy as N, libsweep as L
from funcstats import mask

OUT = os.path.join(ROOT, "build", "sibling")
LOADS = {0x20: (1, True), 0x24: (1, False), 0x21: (2, True), 0x25: (2, False), 0x23: (4, True)}
STORES = {0x28: 1, 0x29: 2, 0x2B: 4}
TYPES = {(1, True): "s8", (1, False): "u8", (2, True): "s16", (2, False): "u16", (4, True): "s32", (4, False): "u32"}
SIZE_OF = {"s8": 1, "u8": 1, "s16": 2, "u16": 2, "s32": 4, "u32": 4, "int": 4, "char": 1, "short": 2}


def words(b):
    return list(struct.unpack("<%dI" % (len(b) // 4), b[:len(b) // 4 * 4]))


def imm(w):
    v = w & 0xFFFF
    return v - 0x10000 if v & 0x8000 else v


def num(s):
    return int(s, 0)


NUM = r"(0[xX][0-9A-Fa-f]+|\d+)"


def access_spans(body, off, size):
    """[(start, end, type, rewrite(newtype) -> text)] of the C accesses of `size` bytes at offset `off`."""
    out = []
    for m in re.finditer(r"\*\s*\(\s*((?:unsigned |signed )?\w+)\s*\*\s*\)\s*\(([^()]*?(?:\([^()]*\)[^()]*?)*?)\s*\+\s*"
                         + NUM + r"\s*\)", body):
        if num(m.group(3)) == off and SIZE_OF.get(m.group(1), 0) in (0, size):
            t = m.group(0)
            out.append((m.start(), m.end(), m.group(1),
                        lambda nt, t=t, old=m.group(1): t.replace(old, nt, 1)))
    for m in re.finditer(r"MEMBER_AT\(\s*(\w+)\s*,\s*([^,()]+(?:\([^()]*\))?)\s*,\s*" + NUM + r"\s*\)", body):
        if num(m.group(3)) == off:
            t = m.group(0)
            out.append((m.start(), m.end(), m.group(1), lambda nt, t=t, old=m.group(1): t.replace(old, nt, 1)))
    for mac, sz in (("H", 2), ("W", 4), ("B", 1)):
        if sz != size:
            continue
        for m in re.finditer(r"(?<![\w.>])%s\(\s*([^,()]+(?:\([^()]*\))?)\s*,\s*%s\s*\)" % (mac, NUM), body):
            if num(m.group(2)) == off:
                base = m.group(1)
                out.append((m.start(), m.end(), mac,
                            lambda nt, b=base: "(*(%s *)((u8 *)(%s) + 0x%X))" % (nt, b, off)))
    if size == 1:
        for m in re.finditer(r"(?<![\w.>\]])(\w+)\s*\[\s*%s\s*\]" % NUM, body):
            if num(m.group(2)) == off:
                base = m.group(1)
                out.append((m.start(), m.end(), "u8[]", lambda nt, b=base: "(*(%s *)(%s + 0x%X))" % (nt, b, off)))
    return out


def statements(body):
    """[(start, end, text)] of the simple statements (one line ending in `;`) of a function body."""
    st = body.find("{") + 1
    out = []
    for m in re.finditer(r"(?m)^[ \t]+([^\n;{}]*;)[ \t]*$", body[st:]):
        out.append((st + m.start(), st + m.end(), m.group(1)))
    return out


def store_stmt(body, off, size):
    """statements assigning to an access of `size` bytes at offset `off`: [(start, end, text, base text)]."""
    out = []
    for s, e, t in statements(body):
        if "=" not in t or "==" in t.split("=")[0]:
            continue
        lhs = t.split("=")[0]
        loc = s + body[s:e].find(lhs)
        for a, b, ty, _ in access_spans(lhs, off, size):
            out.append((s, e, t, lhs[a:b]))
    return out


def stores_of(body):
    """every store statement whose target is a recognisable access: [(start, end, offset, base, form)]."""
    out = []
    for s, e, t in statements(body):
        lhs = t.split("=")[0] if "=" in t and not t.split("=")[1].startswith("=") else None
        if not lhs or re.search(r"[<>!]$", lhs.strip()):
            continue
        m = re.search(r"\*\s*\(\s*\w+\s*\*\s*\)\s*\((.+)\s*\+\s*" + NUM + r"\s*\)\s*$", lhs.strip()) or \
            re.search(r"MEMBER_AT\(\s*\w+\s*,\s*(.+?)\s*,\s*" + NUM + r"\s*\)\s*$", lhs.strip()) or \
            re.search(r"^\(?[HWB]\(\s*(.+?)\s*,\s*" + NUM + r"\s*\)\)?\s*$", lhs.strip()) or \
            re.search(r"^(\w+)\s*\[\s*" + NUM + r"\s*\]\s*$", lhs.strip())
        if m:
            out.append((s, e, num(m.group(2)), m.group(1).strip(), lhs.strip()))
    return out


def li_value(ws, i, reg):
    """the constant register `reg` holds at retail word i (zero, or the last `li` / `ori zero` before it)."""
    if reg == 0:
        return 0
    for j in range(i - 1, max(-1, i - 12), -1):
        w = ws[j]
        op = w >> 26
        if op in (9, 0xD) and (w >> 21) & 0x1F == 0 and (w >> 16) & 0x1F == reg:
            return imm(w) if op == 9 else w & 0xFFFF
        if op == 0xF and (w >> 16) & 0x1F == reg:
            return None
    return None


def swaps(fb):
    """bodies with two adjacent simple statements (consecutive lines) swapped: a store before / after a call."""
    out = []
    st = statements(fb)
    for (s1, e1, t1), (s2, e2, t2) in zip(st, st[1:]):
        if fb[e1:s2].strip() or re.match(r"\s*(return|break|continue|goto)\b", t1) or \
                re.match(r"\s*(return|break|continue|goto)\b", t2):
            continue
        out.append(("swap %s / %s" % (t1.strip()[:24], t2.strip()[:24]), fb[:s1] + fb[s2:e2] + fb[e1:s2] +
                    fb[s1:e1] + fb[e2:]))
    return out


def edits(body, ours, want, fstart, near=False):
    """candidate bodies from the alignment of our words with retail's: [(kind, text)]."""
    ours, rel = ours
    a, b = words(ours), words(want)
    sm = difflib.SequenceMatcher(None, [mask(w) for w in a], [mask(w) for w in b], autojunk=False)
    out, pairs = [], {}
    head, fb = body[:fstart], body[fstart:]
    sign_done, del_done, ins_done = set(), set(), set()
    ops = sm.get_opcodes()
    for tag, i1, i2, j1, j2 in ops:
        if tag in ("equal", "replace") and i2 - i1 == j2 - j1:
            for ii, (g, w) in enumerate(zip(a[i1:i2], b[j1:j2])):
                if g == w or i1 + ii in rel:
                    continue
                og, ow = g >> 26, w >> 26
                if og == ow and og >= 8 and g >> 16 == w >> 16:
                    gi, wi = imm(g), imm(w)
                    if og in (0xC, 0xD, 0xE):
                        gi, wi = g & 0xFFFF, w & 0xFFFF
                    pairs.setdefault((gi, wi), (gi, wi, N.ACCESS.get(og, 1), og))
                elif og in LOADS and ow in LOADS and (g & 0x03FFFFFF) == (w & 0x03FFFFFF) and \
                        LOADS[og][0] == LOADS[ow][0]:
                    off, nt = imm(g), TYPES[LOADS[ow]]
                    if (off, nt) in sign_done:
                        continue
                    sign_done.add((off, nt))
                    for s, e, ty, rw in access_spans(fb, off, LOADS[og][0]):
                        out.append(("sign +0x%X -> %s" % (off, nt), head + fb[:s] + rw(nt) + fb[e:]))
        if tag in ("delete", "replace"):
            for ii, g in enumerate(a[i1:i2]):
                if g >> 26 in STORES and i1 + ii not in rel:
                    off = imm(g)
                    if off in del_done:
                        continue
                    del_done.add(off)
                    for s, e, t, _ in store_stmt(fb, off, STORES[g >> 26]):
                        ls = fb.rfind("\n", 0, s) + 1
                        out.append(("store- +0x%X" % off, head + fb[:ls] + fb[e + 1:]))
        if tag in ("insert", "replace"):
            for j in range(j1, j2):
                w = b[j]
                if w >> 26 not in STORES or (w >> 21) & 0x1F == 1 or any(
                        x >> 26 == 0xF and (x >> 16) & 0x1F == (w >> 21) & 0x1F for x in b[max(0, j - 4):j]):
                    continue     # a %lo store (lui base just before): a symbol, not a field
                off, sz = imm(w), STORES[w >> 26]
                k = li_value(b, j, (w >> 16) & 0x1F)
                if k is None or (off, k) in ins_done:
                    continue
                ins_done.add((off, k))
                ty = {1: "u8", 2: "s16", 4: "s32"}[sz]
                have = store_stmt(fb, off, sz)
                for s, e, t, _ in have:     # the C stores there already: another value, not a second store
                    lhs, _, rhs = t.partition("=")
                    out.append(("store= +0x%X=%s" % (off, k), head + fb[:s] + fb[s:e].replace(
                        t, lhs + "= " + (hex(k) if k >= 0 else str(k)) + ";") + fb[e:]))
                if have:
                    continue
                for s, e, o2, base, lhs in stores_of(fb)[:40]:
                    if lhs.startswith("MEMBER_AT"):
                        new = "MEMBER_AT(%s, %s, 0x%X) = %s;" % (ty, base, off, hex(k) if k >= 0 else str(k))
                    else:
                        new = "*(%s *)(%s + 0x%X) = %s;" % (ty, base, off, hex(k) if k >= 0 else str(k))
                    ind = re.match(r"[ \t]*", fb[fb.rfind("\n", 0, s) + 1:]).group(0)
                    ls = fb.rfind("\n", 0, s) + 1
                    out.append(("store+ +0x%X=%s after +0x%X" % (off, k, o2), head + fb[:e] + "\n" + ind + new + fb[e:]))
                    out.append(("store+ +0x%X=%s before +0x%X" % (off, k, o2), head + fb[:ls] + ind + new + "\n" + fb[ls:]))
    if near:
        out += [(k, head + t) for k, t in swaps(fb)]
    pl = list(pairs.values())
    if pl:
        for t in N.patches(fb, pl, limit=12):
            out.append(("imm %s" % ",".join("%X->%X" % (g, w) for g, w, _, _ in pl[:3]), head + t))
        if len(pl) > 1:
            for p in pl[:6]:
                for t in N.patches(fb, [p], limit=4):
                    out.append(("imm %X->%X" % (p[0], p[1]), head + t))
    return out


def relocs(obj, tname):
    """word indexes of the function's relocated words in obj."""
    import subprocess
    off = None
    for l in subprocess.run(["mipsel-linux-gnu-nm", "--defined-only", obj], capture_output=True,
                            text=True).stdout.splitlines():
        p = l.split()
        if len(p) == 3 and p[2] == tname:
            off = int(p[0], 16)
    out = set()
    for l in subprocess.run(["mipsel-linux-gnu-objdump", "-r", "-j", ".text", obj], capture_output=True,
                            text=True).stdout.splitlines():
        m = re.match(r"([0-9a-f]{8})\s+R_MIPS_", l)
        if m and off is not None:
            out.add((int(m.group(1), 16) - off) // 4)
    return out


def score_obj(obj, tname, want):
    diffs, ours, size = N.compare(obj, tname, want)
    if diffs is None:
        return None, None
    rel = relocs(obj, tname)
    if size == len(want):
        return len(diffs), (ours, rel)
    return N.aligned_off(ours, want) + abs(size - len(want)) // 4, (ours, rel)


def attempt(tp, tname, cand, workdir, rounds=5, beam=3, cap=120):
    """-> (words off, (body, ext, incs) on a match else scratch text, syms or None, edit log)."""
    nd, sp, sname, text, decls, incs = cand
    want = tp.want(tname)
    body, ext = N.prepare(sp, sname, text, decls, tname)
    helpers = [e for e in ext if N.ptsrc.strip_comments(e).strip().startswith("static") and e.rstrip().endswith("}")]
    if helpers:
        ext = [e for e in ext if e not in helpers]
        body = "\n\n".join(helpers) + "\n\n" + body
    fre = re.compile(r"(?m)^[^\n;#]*\b%s\s*\(" % re.escape(tname))
    d = tempfile.mkdtemp(dir=workdir)
    seen = {}
    best = (10 ** 6, None, None, [])

    def run(b):
        if b in seen:
            return seen[b]
        src = os.path.join(d, "x.c")
        open(src, "w").write(N.build_text(incs, ext, b))
        try:
            cc.compile_c(src, os.path.join(d, "a.o"))
        except cc.CompileError:
            seen[b] = (None, None, None)
            return seen[b]
        off, ours = score_obj(os.path.join(d, "a.o"), tname, want)
        syms = None
        if off == 0 and cc.text_size(os.path.join(d, "a.o")) == len(want):
            syms = {}
            if not L.matches(os.path.join(d, "a.o"), tname, want, syms):
                off, syms = 1, None
        seen[b] = (off, ours, syms)
        return seen[b]
    try:
        off, ours, syms = run(body)
        if off is None:
            return best
        if off == 0 and syms is not None:
            return 0, (body, ext, incs), syms, []
        best = (off, N.build_text(incs, ext, body), None, [])
        beam_ = [(off, body, [], ours)]
        for rnd in range(rounds):
            nxt = list(beam_)
            fresh = False
            for off0, b, log, ours in beam_:
                m = fre.search(b)
                fs = m.start() if m else 0
                for kind, t in edits(b, ours, want, fs, off0 <= 12)[:cap]:
                    if t in seen:
                        continue
                    off, o2, syms = run(t)
                    if off is None:
                        continue
                    if off == 0 and syms is not None:
                        return 0, (t, ext, incs), syms, log + [kind]
                    nxt.append((off, t, log + [kind], o2))
            nxt.sort(key=lambda x: (x[0], len(x[2])))
            new_beam = nxt[:beam]
            if [x[1] for x in new_beam] == [x[1] for x in beam_]:
                break
            beam_ = new_beam
            if beam_[0][0] < best[0]:
                best = (beam_[0][0], N.build_text(incs, ext, beam_[0][1]), None, beam_[0][2])
    finally:
        shutil.rmtree(d, ignore_errors=True)
    return best


def candidates(progs, a):
    """[(prog, target, [cand ...])]"""
    sources = N.load_sources(progs)
    targets = a.progs or N.progs_list()
    names = set(a.names.split(",")) if a.names else None
    jobs = []
    if a.src_from:
        sp, sn = a.src_from.split(":")
        if a.src:
            import dupsweep as DS
            text = open(a.src).read()
            fn = DS.c_functions_text(text) if hasattr(DS, "c_functions_text") else None
            m = re.search(r"(?ms)^[\w][^\n;]*\b%s\s*\([^;{]*\)\s*\{.*?^\}" % re.escape(sn), text)
            if not m:
                sys.exit("%s not defined in %s" % (sn, a.src))
            decls = [x for x in re.findall(r"(?ms)^(?:typedef|extern|struct|#define|static)[^\n]*(?:\n[ \t}][^\n]*)*",
                                           text[:m.start()])]
            src = [(sp, sn, m.group(0), decls, progs[sp].includes)]
            key = progs[sp].key(sn)
        else:
            src, key = None, None
            for k, lst in sources.items():
                for e in lst:
                    if e[0] == sp and e[1] == sn:
                        src, key = [e], k
            if not src:
                sys.exit("%s %s is not matched C" % (sp, sn))
        for p in targets:
            tp = progs[p]
            for tname in sorted(tp.pending):
                if tname not in tp.funcs or tname in tp.by_design or (names and tname not in names):
                    continue
                k = tp.key(tname)
                if not 0.8 * len(key) <= len(k) <= 1.25 * len(key):
                    continue
                sm = difflib.SequenceMatcher(None, k, key, autojunk=False)
                if sm.real_quick_ratio() < a.ratio or sm.quick_ratio() < a.ratio or sm.ratio() < a.ratio:
                    continue
                nd = len(k) - sum(x.size for x in sm.get_matching_blocks())
                jobs.append((p, tname, [(nd,) + src[0]]))
        return jobs
    bylen = collections.defaultdict(list)
    for k in sources:
        bylen[len(k)].append(k)
    for p in targets:
        tp = progs[p]
        for tname in sorted(tp.pending):
            if tname not in tp.funcs or tname in tp.by_design or (names and tname not in names):
                continue
            k = tp.key(tname)
            if len(k) < 6:
                continue
            c = N.find_candidates(k, sources, bylen, 8, 0.25, a.top, a.ratio)
            if c:
                jobs.append((p, tname, c))
    return jobs


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("progs", nargs="*", help="target programs (default: all)")
    ap.add_argument("--ratio", type=float, default=0.65, help="difflib ratio of the masked words (default 0.65)")
    ap.add_argument("--names", help="only these targets (comma list)")
    ap.add_argument("--from", dest="src_from", help="PROG:NAME: this matched function (or --src's) as the source")
    ap.add_argument("--src", help="with --from: the scratch file holding NAME (a match not installed yet)")
    ap.add_argument("--top", type=int, default=3, help="candidates tried per target")
    ap.add_argument("--rounds", type=int, default=5)
    ap.add_argument("--beam", type=int, default=3)
    ap.add_argument("--install", action="store_true")
    ap.add_argument("-j", type=int, default=os.cpu_count())
    ap.add_argument("-v", action="store_true")
    a = ap.parse_args()
    progs = {p: N.Prog(p) for p in N.progs_list()}
    jobs = candidates(progs, a)
    print("%d pending functions have a sibling to start from" % len(jobs), flush=True)
    os.makedirs(OUT, exist_ok=True)
    work = tempfile.mkdtemp(prefix="tmp_sibling_", dir=os.path.join(ROOT, "build"))

    def run(job):
        p, tname, cands = job
        best = (10 ** 6, None, None, None, [])
        for c in cands:
            off, res, syms, log = attempt(progs[p], tname, c, work, a.rounds, a.beam)
            if off == 0:
                return p, tname, c, 0, res, syms, log
            if off < best[0]:
                best = (off, c, res, None, log)
        return p, tname, best[1], best[0], best[2], None, best[4]

    found = collections.defaultdict(list)
    try:
        with cf.ThreadPoolExecutor(a.j) as ex:
            for p, tname, c, off, res, syms, log in ex.map(run, jobs):
                tp = progs[p]
                if c is None:
                    continue
                if off == 0:
                    body, ext, incs = res
                    ren, _ = N.renames(tp, tname, syms, set())
                    txt = N.apply_renames(N.build_text(incs, ext, body), ren)
                    # a callee renamed to the target's function: the source's prototype of it may clash with
                    # the target's use (a void prototype for a function the target reads the value of)
                    for nm in {v for v in ren.values() if v.startswith(("func_", "f_"))}:
                        val = re.search(r"(?<![\w])%s\b(?!\s*\()" % re.escape(nm), txt.split("\n", 1)[-1]) and \
                            re.search(r"(?m)^[\w][\w \*]*\b%s\s*\([^;{}]*\)\s*;" % re.escape(nm), txt)
                        txt = re.sub(r"(?m)^[\w][\w \*]*\b%s\s*\([^;{}]*\)\s*;\n" % re.escape(nm),
                                     "s32 %s();\n" % nm if val else "", txt)
                    txt = "// sibling: from %s %s; edits: %s\n" % (c[1], c[2], "; ".join(log) or "none") + txt
                    os.makedirs(os.path.join(OUT, p), exist_ok=True)
                    f = os.path.join(OUT, p, tname + ".c")
                    open(f, "w").write(txt)
                    found[p].append((tname, f, syms))
                    print("MATCH %s %s <- %s %s (%s)" % (p, tname, c[1], c[2], "; ".join(log) or "as is"), flush=True)
                elif res:
                    os.makedirs(os.path.join(OUT, p, "near"), exist_ok=True)
                    open(os.path.join(OUT, p, "near", tname + ".c"), "w").write(
                        "// sibling: %d words off, C from %s %s; edits: %s\n// retail diff: %s\n" % (
                            off, c[1], c[2], "; ".join(log) or "none", N.near_summary(c[1], c[2], p, tname)) + res)
                    print("near %s %s: %d off <- %s %s (%s)" % (p, tname, off, c[1], c[2], "; ".join(log) or "-"),
                          flush=True)
    finally:
        shutil.rmtree(work, ignore_errors=True)
    print("matched: %d (%s)" % (sum(len(v) for v in found.values()),
                                ", ".join("%s %d" % (p, len(v)) for p, v in sorted(found.items()))))
    if not a.install:
        return
    total = 0
    for p, items in sorted(found.items()):
        tp = progs[p]
        defined = N.defined_names(p)
        added = {}
        for tname, f, syms in items:
            _, new = N.renames(tp, tname, syms, defined)
            added.update({k: v for k, v in new.items() if not re.fullmatch(r"func_[0-9A-F]{8}", k)})
        if added:
            al = L.read_aliases(p)
            al.update(added)
            L.write_aliases(p, al)
        old_out = N.OUT
        N.OUT = OUT
        try:
            done = N.install(p, [f for _, f, _ in items], a.v)
        finally:
            N.OUT = old_out
        total += len(done)
        print("%s: installed %d of %d: %s" % (p, len(done), len(items), " ".join(done)), flush=True)
    print("installed %d" % total)


if __name__ == "__main__":
    main()

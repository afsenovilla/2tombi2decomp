#!/usr/bin/env python3
"""Known inline bodies: pending functions that contain an inlined copy of a function already matched in C.

  python3 -I tools/inlined.py [PROG ...] [--from PROG,...] [--min-len 10] [--min-cover 0.8] [--names A,B]
      [--copies] [--top 60] [--csv build/inlined.csv]

Every function of every program (asm/<prog>/**/*.s) is turned into a normalised instruction list: nops, register
moves (`addu rd,rs,$zero`), the prologue / epilogue (`addiu $sp,$sp,K`, saves and restores of $s0-$s8 / $ra,
`jr $ra`) are dropped; each instruction keeps its opcode, function code, shift amount and immediate, except
relocated immediates (`%hi` / `%lo` / scratchpad `>> 16` / `& 0xFFFF` forms), branch offsets and $sp offsets,
which are masked; `jal` keeps its callee's name. Registers are not part of the key (renaming is allowed): the
report gives how consistently the matched body's registers map onto the pending ones (1.00: a pure renaming), and
`{op:K->K2}` for the immediates that differ between the body and the copy at the same place (an inlined copy with
other constants or field offsets: patch the helper or pass the value as a parameter).

For every matched C function (a target program's function that is not INCLUDE_ASM: game code and library files)
of --min-len normalised instructions or more, every pending function of the given programs (default all) sharing
enough 5-instruction runs with it is aligned with it (difflib on the instruction keys, in a window around the
longest common run): `cover` is the part of the matched body found there in order. Pending functions of about the
same length as the matched body are copies (tools/nearcopy.py's job) and are left out unless --copies.

Output: pending functions with a cover >= --min-cover, smallest first: the pending function, its size, the
matched function(s) found inside (program:name, cover, register consistency, the pending address range) and the
`static inline` helper of src/ that already copies that body (a `/* NAME, inlined */` comment above it), when there
is one. --csv writes every hit (default build/inlined.csv for all programs, build/inlined_<progs>.csv for a scope,
so runs over different scopes do not overwrite each other). Pending functions holding several matched bodies at
different places (dispatchers) are drafted by tools/dispatch.py.

--repeats: pending functions that hold one block of code several times (no matched body needed: a loop body or a
helper inlined or unrolled at each use): block length in normalised instructions, copies, register consistency
between the copies, how many immediates differ (other offsets / constants: a helper parameter), the address range
of each copy (build/repeats[_<progs>].csv). Write the block once as a `static inline` helper (decomp.py's draft of
the function shows its C at the first range) and call it at each copy.

Recipe: copy the matched C into the pending function's file as `static inline` (comment `/* NAME, inlined */`),
call it where the pending code has the copy (its `return 0` / `return 1` become the caller's branches), then
ccheck / install as usual (docs/STATUS.md, "Inlined functions").
"""
import argparse, collections, csv, difflib, glob, os, re, sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))
import libsweep as L, nearcopy as N

LINE = re.compile(r"/\* \w+ ([0-9A-F]{8}) ([0-9A-F]{8}) \*/\s+(\S+)\s*(.*)$")
SAVED = set(range(16, 24)) | {30, 31}
RELOC = re.compile(r"%hi|%lo|%gp_rel|>> 16\)|& 0xFFFF\)")
K = 5


def regs(w):
    """(key fields, register operands) of one instruction word."""
    op, rs, rt, rd, sa, fn = w >> 26, (w >> 21) & 31, (w >> 16) & 31, (w >> 11) & 31, (w >> 6) & 31, w & 0x3F
    if op == 0:
        if fn in (0, 2, 3):                       # sll srl sra
            return ("s", fn, sa), (rt, rd)
        if fn in (8, 9):                          # jr jalr
            return ("s", fn), (rs, rd) if fn == 9 else (rs,)
        if fn in (0x10, 0x12):                    # mfhi mflo
            return ("s", fn), (rd,)
        if fn in (0x11, 0x13):
            return ("s", fn), (rs,)
        if fn in (0x18, 0x19, 0x1A, 0x1B):        # mult div
            return ("s", fn), (rs, rt)
        if fn in (0xC, 0xD):
            return ("s", fn, w >> 6 & 0xFFFFF), ()
        return ("s", fn), (rs, rt, rd)
    if op == 1:
        return ("r", rt), (rs,)
    if op in (4, 5):
        return (op,), (rs, rt)
    if op in (6, 7):
        return (op,), (rs,)
    if op == 0x0F:
        return (op, w & 0xFFFF), (rt,)
    if op in (0x10, 0x11, 0x13):
        return ("c", op, rs, rd if rs in (0, 2, 4, 6) else w & 0x3FFFFFF), (rt,) if rs in (0, 2, 4, 6) else ()
    if op == 0x12:
        if (w >> 25) & 1:
            return ("c2", w & 0x1FFFFFF), ()
        return ("c2m", rs, rd), (rt,)
    return (op, w & 0xFFFF), (rs, rt)


def norm(lines):
    """normalised (key, regs, address) list of one function's (word, mnemonic, operands, address) lines."""
    out = []
    for w, mn, ops, ad in lines:
        if w == 0:
            continue
        op, rs, rt, rd, fn = w >> 26, (w >> 21) & 31, (w >> 16) & 31, (w >> 11) & 31, w & 0x3F
        if op == 0 and fn in (0x21, 0x25) and (rt == 0) != (rs == 0) and rd != 0:
            continue                               # move
        if op == 0 and fn == 8 and rs == 31:
            continue                               # jr $ra
        if op == 9 and rs == 29 and rt == 29:
            continue                               # addiu $sp,$sp,K
        if op in (0x23, 0x2B) and rs == 29 and rt in SAVED:
            continue                               # save / restore
        key, rg = regs(w)
        if op in (2, 3):
            key = (op, ops.strip().split()[0] if op == 3 else "")
        elif 4 <= op <= 7 or op in (0x14, 0x15, 0x16, 0x17) or op == 1:
            key = key[:2] if op == 1 else (op,)
        elif op == 0x0F and RELOC.search(ops):
            key = (op, "hi")
        elif op >= 8 and op != 0x0F and len(key) == 2 and (RELOC.search(ops) or rs == 29):
            key = (op, "lo" if rs != 29 else "sp")
        out.append((key, rg, ad))
    return out


def read_funcs(prog):
    """name -> list of (word, mnemonic, operands, address) of every function of the program's .s files."""
    out = {}
    for f in glob.glob(os.path.join(ROOT, "asm", prog, "*matchings", "**", "*.s"), recursive=True):
        name, lines = None, []
        for l in open(f):
            m = re.match(r"\s*glabel (\w+)", l)
            if m and name is None:
                name = m.group(1)
            m = LINE.search(l)
            if m:
                b = bytes.fromhex(m.group(2))
                lines.append((int.from_bytes(b, "little"), m.group(3), m.group(4), int(m.group(1), 16)))
        if name and lines:
            out[name] = lines
    return out


def pending_names(prog):
    tp = N.Prog(prog)
    return set(tp.pending) | set(L.pending_files(prog)), tp


def helpers():
    """matched name -> [helper name] from `/* NAME, inlined */` comments above static inline functions in src/."""
    out = collections.defaultdict(list)
    for f in glob.glob(os.path.join(ROOT, "src", "**", "*.c"), recursive=True):
        t = open(f).read()
        for m in re.finditer(r"/\*[^*]*?(\w+), inlined \*/\s*\n\s*static\s+inline\s+[^(]*?(\w+)\s*\(", t):
            out[m.group(1)].append("%s:%s" % (os.path.basename(os.path.dirname(f)), m.group(2)))
    return out


def reg_consistency(a, b, blocks):
    cnt = collections.defaultdict(collections.Counter)
    for i, j, n in blocks:
        for k in range(n):
            for x, y in zip(a[i + k][1], b[j + k][1]):
                if x != 0 or y != 0:
                    cnt[x][y] += 1
    tot = sum(sum(c.values()) for c in cnt.values())
    return sum(max(c.values()) for c in cnt.values()) / tot if tot else 1.0


def align(body, pend, j0, i0):
    """cover, blocks of the body against the window of pend around the seed body[i0] ~ pend[j0]."""
    n = len(body)
    lo, hi = max(0, j0 - i0 - n // 2), min(len(pend), j0 + (n - i0) + n // 2)
    sm = difflib.SequenceMatcher(None, [x[0] for x in body], [x[0] for x in pend[lo:hi]], autojunk=False)
    bl = [(i, j + lo, k) for i, j, k in sm.get_matching_blocks() if k]
    return sum(k for _, _, k in bl) / n, bl


def const_diffs(body, pend, blocks):
    """the immediates that differ between the body and its copy: pairs of instructions of the same opcode (and
    function / shift class) at the same place of a 'replace' run between two aligned blocks -> ["op:K->K2", ...]."""
    out = []
    prev_i, prev_j = 0, None
    for i, j, n in blocks:
        if prev_j is not None:
            a, b = body[prev_i:i], pend[prev_j:j]
            for x, y in zip(a, b) if len(a) == len(b) else ():
                kx, ky = x[0], y[0]
                if kx != ky and len(kx) == len(ky) and kx[:-1] == ky[:-1] and all(
                        isinstance(v, int) for v in (kx[-1], ky[-1])):
                    out.append("%s:%#x->%#x" % (OPNAME.get(kx[0], kx[0]) if kx[0] != "s" else
                                                "shift%d" % kx[1], kx[-1], ky[-1]))
        prev_i, prev_j = i + n, j + n
    return out


OPNAME = {8: "addi", 9: "addiu", 0xA: "slti", 0xB: "sltiu", 0xC: "andi", 0xD: "ori", 0xE: "xori", 0xF: "lui",
          0x20: "lb", 0x21: "lh", 0x23: "lw", 0x24: "lbu", 0x25: "lhu", 0x28: "sb", 0x29: "sh", 0x2B: "sw"}


def search(targets, sources, min_len=10, min_cover=0.8, only=None, copies=False, pending_only=None):
    """the hits of the matched bodies of `sources` in the pending functions of `targets` (list of dicts; the keys
    of the csv plus `_blocks` (body index, pending index, length), `_body` / `_pend` (normalised lists) and
    `_bk` / `_pk` ((prog, name) keys)). pending_only: a set of (prog, name) to search (default every one)."""
    pend, body = {}, {}            # (prog, name) -> normalised list
    size = {}
    for prog in sorted(set(targets) | set(sources)):
        if not os.path.isdir(os.path.join(ROOT, "asm", prog)):
            continue
        pn, tp = pending_names(prog)
        for name, lines in read_funcs(prog).items():
            nl = norm(lines)
            size[(prog, name)] = len(lines) * 4
            if name in pn:
                if prog in targets and name not in tp.by_design and (pending_only is None or (prog, name) in pending_only):
                    pend[(prog, name)] = nl
            elif prog in sources and len(nl) >= min_len and (only is None or name in only):
                body[(prog, name)] = nl
    # one body per distinct key sequence (copies of matched code in several programs)
    seen, bodies = {}, []
    for k in sorted(body, key=lambda k: (k[0] != "main", k)):
        sig = tuple(x[0] for x in body[k])
        if sig not in seen:
            seen[sig] = k
            bodies.append(k)
    index = collections.defaultdict(set)
    for pk, nl in pend.items():
        ks = [x[0] for x in nl]
        for i in range(len(ks) - K + 1):
            index[tuple(ks[i:i + K])].add(pk)
    common = {g for g, s in index.items() if len(s) > 150} if pending_only is None else set()
    hits = []
    for bk in bodies:
        b = body[bk]
        ks = [x[0] for x in b]
        grams = {tuple(ks[i:i + K]) for i in range(len(ks) - K + 1)} - common
        if not grams:
            continue
        c = collections.Counter()
        for g in grams:
            for pk in index.get(g, ()):
                c[pk] += 1
        need = max(2, int(len(grams) * min_cover * 0.5))
        for pk, n in c.items():
            if n < need or (pk == bk):
                continue
            p = pend[pk]
            is_copy = len(p) <= len(b) * 1.3
            if is_copy and not copies:
                continue
            pks = [x[0] for x in p]
            sm = difflib.SequenceMatcher(None, ks, pks, autojunk=False)
            i0, j0, m = sm.find_longest_match(0, len(ks), 0, len(pks))
            if m < K:
                continue
            cover, bl = align(b, p, j0, i0)
            if cover < min_cover:
                continue
            j1, j2 = bl[0][1], bl[-1][1] + bl[-1][2] - 1
            hits.append({"prog": pk[0], "name": pk[1], "size": size[pk], "from": "%s:%s" % bk,
                         "cover": round(cover, 2), "regs": round(reg_consistency(b, p, bl), 2),
                         "start": "%08X" % p[j1][2], "end": "%08X" % p[j2][2], "copy": int(is_copy),
                         "body_len": len(b), "consts": " ".join(const_diffs(b, p, bl)) or "-",
                         "_blocks": bl, "_body": b, "_pend": p, "_bk": bk, "_pk": pk})
    hl = helpers()
    for h in hits:
        h["helper"] = " ".join(hl.get(h["from"].split(":")[1], [])) or "-"
    hits.sort(key=lambda h: (h["size"], h["prog"], h["name"], -h["cover"]))
    return hits


FIELDS = ["prog", "name", "size", "from", "cover", "regs", "start", "end", "copy", "body_len", "helper", "consts"]


def csv_name(progs, src):
    """build/inlined.csv for a run over every program, build/inlined_<progs>[_from_<progs>].csv otherwise (two
    agents on different scopes do not overwrite each other's file)."""
    allp = N.progs_list()
    tag = "" if not progs or sorted(progs) == allp else "_" + "-".join(sorted(progs))
    if src and sorted(src) != allp:
        tag += "_from_" + "-".join(sorted(src))
    if len(tag) > 80:
        import hashlib
        tag = "_" + hashlib.sha1(tag.encode()).hexdigest()[:10]
    return os.path.join(ROOT, "build", "inlined%s.csv" % tag)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("progs", nargs="*", help="programs whose pending functions are searched (default all)")
    ap.add_argument("--from", dest="src", default="", help="programs whose matched functions are used (default all)")
    ap.add_argument("--min-len", type=int, default=10)
    ap.add_argument("--min-cover", type=float, default=0.8)
    ap.add_argument("--names", default="", help="only these matched functions")
    ap.add_argument("--copies", action="store_true", help="also pending functions of the matched body's length")
    ap.add_argument("--top", type=int, default=60)
    ap.add_argument("--csv", default=None, help="default build/inlined.csv (all programs) or "
                                                "build/inlined_<progs>.csv")
    ap.add_argument("--repeats", action="store_true", help="pending functions holding one block several times")
    a = ap.parse_args()
    allp = N.progs_list()
    targets = a.progs or allp
    if a.repeats:
        rows = repeats(targets, max(a.min_len, 12))
        out = os.path.join(ROOT, "build", "repeats%s.csv" % ("_" + "-".join(a.progs) if a.progs else ""))
        os.makedirs(os.path.dirname(out), exist_ok=True)
        with open(out, "w", newline="") as f:
            w = csv.writer(f)
            w.writerow(["prog", "name", "size", "block_len", "copies", "regs", "const_diffs", "where"])
            for r in rows:
                w.writerow([r[0], r[1], r[2], r[3], len(r[4]), "%.2f" % r[5], r[6], " ".join(r[4])])
        print("%d repeated blocks in pending functions (block of N normalised instructions x copies, best first):"
              % len(rows))
        for r in rows[:a.top]:
            print("%-4s %-44s %#6x  %3d x%d r%.2f consts %d  @%s" % (r[0], r[1], r[2], r[3], len(r[4]), r[5], r[6],
                                                                   " ".join(r[4][:4]) + (" ..." if len(r[4]) > 4
                                                                                         else "")))
        print("all: " + os.path.relpath(out, ROOT))
        return
    sources = a.src.split(",") if a.src else allp
    only = set(a.names.split(",")) if a.names else None
    if a.csv is None:
        a.csv = csv_name(a.progs, a.src.split(",") if a.src else [])
    hits = search(targets, sources, a.min_len, a.min_cover, only, a.copies)
    nb = len({h["from"] for h in hits})
    if a.csv:
        os.makedirs(os.path.dirname(a.csv), exist_ok=True)
        with open(a.csv, "w", newline="") as f:
            w = csv.DictWriter(f, fieldnames=FIELDS, extrasaction="ignore")
            w.writeheader()
            w.writerows(hits)
    byf = collections.OrderedDict()
    for h in hits:
        byf.setdefault((h["prog"], h["name"]), []).append(h)
    print("%d pending functions contain an inlined copy of matched code (%d hits from %d matched bodies); "
          "smallest first:" % (len(byf), len(hits), nb))
    for (prog, name), hs in list(byf.items())[:a.top]:
        hs.sort(key=lambda h: (-h["cover"] * h["body_len"]))
        print("%-4s %-44s %#6x  %s" % (prog, name, hs[0]["size"], "; ".join(
            "%s %.2f r%.2f @%s-%s%s%s%s" % (h["from"], h["cover"], h["regs"], h["start"], h["end"],
                                           " copy" if h["copy"] else "",
                                           " [" + h["helper"] + "]" if h["helper"] != "-" else "",
                                           " {%s}" % h["consts"] if h["consts"] != "-" else "")
            for h in hs[:3]) + (" (+%d)" % (len(hs) - 3) if len(hs) > 3 else "")))
    if a.csv:
        print("all: " + os.path.relpath(a.csv, ROOT))
    multi = [k for k, hs in byf.items() if len(spans(hs)) >= 2]
    if multi:
        print("%d of them hold several matched bodies at different places (dispatchers): "
              "python3 -I tools/dispatch.py --list" % len(multi))


def opk(key):
    """an instruction key without its immediate (copies of one loop body with other constants still line up)."""
    if key and key[0] in ("s", "r", "c", "c2", "c2m") or len(key) < 2:
        return key[:2] if key and key[0] == "s" else key
    return key[:1] + (key[1],) if key[1] in ("hi", "lo", "sp") or isinstance(key[1], str) else key[:1]


def repeats(targets, min_len=12):
    """pending functions holding one block of code several times (a loop body or helper inlined / unrolled at
    each use): [(prog, name, size, block length, [(start, end) addresses], register consistency, constants that
    differ between the first copy and the others)]. Keys without immediates; the longest block first, its
    sub-blocks not reported again."""
    out = []
    for prog in targets:
        if not os.path.isdir(os.path.join(ROOT, "asm", prog)):
            continue
        pn, tp = pending_names(prog)
        for name, lines in read_funcs(prog).items():
            if name not in pn or name in tp.by_design:
                continue
            nl = norm(lines)
            keys = [opk(k) for k, _, _ in nl]
            n = len(keys)
            if n < 2 * min_len:
                continue
            grams = collections.defaultdict(list)
            for i in range(n - K * 2 + 1):
                grams[tuple(keys[i:i + K * 2])].append(i)
            covered = set()
            found = []
            for g, pos in sorted(grams.items(), key=lambda kv: kv[1][0]):
                pos = [p_ for p_ in pos if p_ not in covered]
                if len(pos) < 2:
                    continue
                # non-overlapping occurrences, then the common extension forward
                occ = [pos[0]]
                for p_ in pos[1:]:
                    if p_ >= occ[-1] + K * 2:
                        occ.append(p_)
                if len(occ) < 2:
                    continue
                L = K * 2
                while all(o + L < n for o in occ) and len({keys[o + L] for o in occ}) == 1 and \
                        all(occ[j] + L < occ[j + 1] for j in range(len(occ) - 1)):
                    L += 1
                if L < min_len:
                    continue
                for o in occ:
                    covered.update(range(o, o + L))
                blocks = [(0, 0, L)]
                rc = min(reg_consistency(nl[occ[0]:occ[0] + L], nl[o:o + L], blocks) for o in occ[1:])
                consts = sum(1 for o in occ[1:] for j in range(L) if nl[occ[0] + j][0] != nl[o + j][0])
                found.append((L, ["%08X-%08X" % (nl[o][2], nl[o + L - 1][2]) for o in occ], rc, consts))
            for L, where, rc, consts in sorted(found, key=lambda f: -f[0] * len(f[1])):
                out.append((prog, name, len(lines) * 4, L, where, rc, consts))
    out.sort(key=lambda r: -r[3] * len(r[4]))
    return out


def spans(hs):
    """the hits of one pending function that do not overlap, best (cover * body length) first."""
    out = []
    for h in sorted(hs, key=lambda h: -float(h["cover"]) * int(h["body_len"])):
        s, e = int(h["start"], 16), int(h["end"], 16)
        if all(e < int(o["start"], 16) or s > int(o["end"], 16) for o in out):
            out.append(h)
    return sorted(out, key=lambda h: h["start"])


if __name__ == "__main__":
    main()

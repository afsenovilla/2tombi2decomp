#!/usr/bin/env python3
"""Bottom-up work queue: the pending functions of the given programs, the ones whose callees are all matched first.

  python3 -I tools/workqueue.py [PROG ...] [--top 30] [--min-size 0x40] [--max-size 0x2000] [--csv FILE]

For each pending game function (an INCLUDE_ASM line of src/<prog>/<prog>.c; library files too with --lib):
  - callees: the jal targets of its asm, resolved in its own program, then in MAIN.EXE (overlays call MAIN's
    functions by name or by func_<address>), then boot; `pend` = how many of them are still pending (asm), `ext` =
    targets found nowhere (named library / alias symbols: counted as matched), `jalr` = indirect calls;
  - size (bytes), jump tables (`jt`: rodata jump tables it dispatches through, tools/statemachine.py's candidates),
    inlined matched bodies (`inl`: hits in build/inlined.csv or build/inlined_<progs>.csv when tools/inlined.py has
    written one; `-` when no csv exists), family (`fam`: pending functions of any program with the same opcode
    sequence, tools/families.py; `exact`: of them the same masked words, which nearcopy / dupsweep fill from one
    match), and `callers`: pending functions of the scope that call it (matching it frees them). The last line names
the pending callees (any program) that block the most functions of the scope.
Rank: no pending callee first, then by value = size x exact copies (bytes gained with the copies), larger first.
Writes build/queue_<progs>.csv (every pending function) and prints the top of the list. The pending set is read from
the INCLUDE_ASM lines of src/ at every run (functions installed while it runs are dropped before the csv is written;
asm by design ones are never listed): rerun it rather than reading an old csv. The `inl` column comes from the last
tools/inlined.py csv; it is flagged when that csv is older than the last change of src/.
"""
import argparse, collections, csv, glob, os, re, struct, sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))
import libsweep as L, nearcopy as N, progress as P
from families import opkey
from funcstats import mask

JAL = re.compile(r"\bjal\s+(\w+)")


class Info:
    """per program: name -> (address, size), address -> name, the pending names."""
    def __init__(self, prog):
        self.prog = prog
        self.p = N.Prog(prog)
        self.funcs = self.p.funcs
        self.by_addr = {ad: n for n, (ad, _) in self.funcs.items()}
        st = P.file_state(prog)
        self.pending = {n for n, (lib, s) in st.items() if s in ("pending", "equiv") and n in self.funcs}
        self.lib = {n for n, (lib, s) in st.items() if lib}

    def canon(self, name):
        m = re.fullmatch(r"func_([0-9A-F]{8})", name)
        return self.by_addr.get(int(m.group(1), 16), name) if m and name not in self.funcs else name

    def status(self, name):
        """True (matched), False (pending) or None (not a function of this program)."""
        if name in self.funcs:
            return name not in self.pending
        m = re.fullmatch(r"func_([0-9A-F]{8})", name)
        if m and int(m.group(1), 16) in self.by_addr:
            return self.by_addr[int(m.group(1), 16)] not in self.pending
        return None


def asm_path(prog, name):
    hits = glob.glob(os.path.join(ROOT, "asm", prog, "nonmatchings", "**", name + ".s"), recursive=True)
    return hits[0] if hits else None


def inlined_hits(progs):
    import inlined as I
    for p in (I.csv_name(progs, []), os.path.join(ROOT, "build", "inlined.csv")):
        if os.path.exists(p):
            c = collections.Counter()
            for r in csv.DictReader(open(p)):
                c[(r["prog"], r["name"])] += 1
            return c, os.path.relpath(p, ROOT)
    return None, None


def families(infos):
    """(opcode key -> count of pending functions, masked key -> count) over every program."""
    fam, exact = collections.Counter(), collections.Counter()
    keys = {}
    for prog, inf in infos.items():
        for n in inf.pending:
            ad, size = inf.funcs[n]
            if size < 8:
                continue
            b = inf.p.want(n)
            words = struct.unpack("<%dI" % (len(b) // 4), b[:len(b) // 4 * 4])
            k1, k2 = tuple(opkey(w) for w in words), tuple(mask(w) for w in words)
            fam[k1] += 1
            exact[k2] += 1
            keys[(prog, n)] = (k1, k2)
    return fam, exact, keys


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("progs", nargs="*", help="programs (default: all)")
    ap.add_argument("--top", type=int, default=30)
    ap.add_argument("--min-size", default="0")
    ap.add_argument("--max-size", default="0x100000")
    ap.add_argument("--lib", action="store_true", help="include pending library files")
    ap.add_argument("--csv")
    a = ap.parse_args()
    allp = N.progs_list()
    progs = a.progs or allp
    for p in progs:
        if p not in allp:
            sys.exit("unknown program %s" % p)
    infos = {p: Info(p) for p in allp}   # every program: the families are counted over all of them
    fam, exact, keys = families(infos)
    inl, inl_src = inlined_hits(a.progs if a.progs and sorted(a.progs) != allp else [])
    lo, hi = int(a.min_size, 0), int(a.max_size, 0)
    rows, calls_of = [], {}
    for prog in progs:
        inf = infos[prog]
        look = [inf] + [infos[q] for q in ("main", "boot") if q != prog]
        for n in sorted(inf.pending, key=lambda n: inf.funcs[n][0]):
            if n in inf.lib and not a.lib:
                continue
            path = asm_path(prog, n)
            if not path:
                continue
            t = open(path).read()
            callees = []
            for c in JAL.findall(t):
                if c not in callees:
                    callees.append(c)
            pend, ext, pnames = 0, 0, []
            for c in callees:
                hit = next((i for i in look if i.status(c) is not None), None)
                if hit is None:
                    ext += 1
                elif not hit.status(c):
                    pend += 1
                    pnames.append(hit.canon(c) if hit is inf else "%s:%s" % (hit.prog, hit.canon(c)))
            calls_of[(prog, n)] = callees
            size = inf.funcs[n][1]
            k = keys.get((prog, n))
            rows.append({"prog": prog, "name": n, "addr": "%08X" % inf.funcs[n][0], "size": size, "size_hex": "%#x" % size,
                         "callees": len(callees), "pend": pend, "ext": ext,
                         "jalr": len(re.findall(r"\bjalr\s", t)),
                         "jt": len(set(re.findall(r"%hi\((jtbl_\w+)\)", t))),
                         "inl": inl.get((prog, n), 0) if inl is not None else "-",
                         "fam": fam[k[0]] if k else 1, "exact": exact[k[1]] if k else 1,
                         "callers": 0, "value": size * (exact[k[1]] if k else 1),
                         "pending_callees": " ".join(pnames)})
    # callers: pending functions of the scope that call each one (by name or by func_<address>)
    idx = {}
    for r in rows:
        idx[(r["prog"], r["name"])] = r
        idx[(r["prog"], "func_" + r["addr"])] = r
    for (prog, n), cs in calls_of.items():
        for c in cs:
            for q in (prog, "main", "boot"):
                r = idx.get((q, c))
                if r is not None:
                    r["callers"] += 1
                    break
    # never a stale list: drop what is no longer an INCLUDE_ASM line now (installed while this ran, e.g. by another
    # agent; the pending sets above were read at the start)
    now = {p: {n for n, (lib, st) in P.file_state(p).items() if st in ("pending", "equiv")} for p in progs}
    gone = [r for r in rows if r["name"] not in now[r["prog"]]]
    if gone:
        print("dropped %d function(s) installed meanwhile: %s" % (len(gone), " ".join(
            "%s:%s" % (r["prog"], r["name"]) for r in gone[:10])))
        rows = [r for r in rows if r["name"] in now[r["prog"]]]
    rows.sort(key=lambda r: (r["pend"] > 0, -r["value"], -r["size"]))
    tag = "all" if sorted(progs) == allp else "-".join(progs)
    out = a.csv or os.path.join(ROOT, "build", "queue_%s.csv" % tag)
    os.makedirs(os.path.dirname(out), exist_ok=True)
    with open(out, "w", newline="") as f:
        w = csv.DictWriter(f, fieldnames=list(rows[0]) if rows else ["prog"])
        w.writeheader()
        w.writerows(rows)
    ready = [r for r in rows if r["pend"] == 0]
    print("%d pending functions (0x%X bytes); %d (0x%X bytes) call no pending function.%s" % (
        len(rows), sum(r["size"] for r in rows), len(ready), sum(r["size"] for r in ready),
        "" if inl_src else " (no inlined.py csv: run tools/inlined.py %s for the inl column)" % " ".join(a.progs)))
    if inl_src:
        newest = max(os.path.getmtime(f) for p in progs for f in glob.glob(os.path.join(ROOT, "src", p, "**", "*.c"),
                                                                           recursive=True))
        print("inl from " + inl_src + ("" if os.path.getmtime(os.path.join(ROOT, inl_src)) >= newest else
                                       " (older than the last change of src/: bodies matched since are not in it; "
                                       "rerun tools/inlined.py for a fresh column)"))
    print("%-4s %-46s %6s %3s %4s %3s %3s %4s %5s %4s  %s" % ("prog", "name", "size", "jt", "pend", "inl", "fam",
                                                          "exact", "value", "clrs", "pending callees"))
    shown = [r for r in rows if lo <= r["size"] <= hi][:a.top]
    for r in shown:
        print("%-4s %-46s %#6x %3d %4d %3s %3d %4d %#5x %4d  %s" % (
            r["prog"], r["name"][:46], r["size"], r["jt"], r["pend"], r["inl"], r["fam"], r["exact"], r["value"],
            r["callers"], r["pending_callees"][:40]))
    need = collections.Counter(c for r in rows for c in r["pending_callees"].split())
    if need:
        print("pending callees that block the most functions here (match these first): " + ", ".join(
            "%s %d" % kv for kv in need.most_common(8)))
    print("all: " + os.path.relpath(out, ROOT))


if __name__ == "__main__":
    main()

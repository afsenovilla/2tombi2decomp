#!/usr/bin/env python3
"""Rank the still-asm game functions by how much the native port interprets them (docs/PORT.md 0.6).

  python3 -I tools/port_hot.py PROFILE.csv ... [--out build/port_hot.csv] [--top 30] [--all-states]

Each PROFILE.csv is the output of `build/port/tomba2 ... --interp-profile PROFILE.csv` (one row per interpreted pc:
pc, resident program, calls entered there, instructions executed there).  Every pc is mapped to the function of its
program (MAIN or the overlay resident at that address) from the splat asm index (asm/<prog>/, so run
`python3 tools/build.py` first), and summed per function over all the profiles.  The run label is the file's stem;
`areaX-...` stems count as area a0x (`area10-0` = a0g).

Written: build/port_hot.csv, one row per interpreted function: prog, name, addr, size, state (pending = an
INCLUDE_ASM target, equiv = NON_MATCHING C kept as asm, lib = Psy-Q library, by-design = asm by design, matched =
C the port still interprets: dropped by gen_t2.py or kept interpreted on purpose), calls, insns, share (of all
interpreted instructions), runs (labels where it ran).  Library and asm-by-design functions are never targets:
they are listed (state column) but left out of the ranking and of the totals of the summary.

Printed: the totals (how much of the interpreted instructions the top 50 / 200 pending functions cover), then per
agent scope of CLAUDE.md (main; a00-a01; a02-a03; a04-a08; a09-a0l + game/demo/opn/sop/crd + boot) the top N.
`tools/workqueue.py --hot build/port_hot.csv` puts the hot functions first.
"""
import argparse, bisect, collections, csv, os, re, sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))
import nearcopy as N, progress as P

SCOPES = [("main", ["main"]), ("a00-a01", ["a00", "a01"]), ("a02-a03", ["a02", "a03"]),
          ("a04-a08", ["a04", "a05", "a06", "a07", "a08"]),
          ("a09-a0l+", ["a09", "a0a", "a0b", "a0c", "a0d", "a0e", "a0f", "a0g", "a0h", "a0i", "a0j", "a0k", "a0l",
                        "game", "demo", "opn", "sop", "crd", "boot"])]
AREA = "0123456789abcdefghijkl"


def scope_of(prog):
    return next((s for s, ps in SCOPES if prog in ps), "?")


def label(path):
    stem = os.path.splitext(os.path.basename(path))[0]
    m = re.match(r"area([0-9A-Fa-f]+)", stem)
    if m and int(m.group(1), 16) < len(AREA):
        return "a0" + AREA[int(m.group(1), 16)]
    return stem


class ProgMap:
    def __init__(self, prog):
        funcs = N.asm_index(prog)
        self.items = sorted((ad, size, n) for n, (ad, size) in funcs.items())
        self.starts = [x[0] for x in self.items]
        st = P.file_state(prog)
        self.state = {}
        for n, (lib, s) in st.items():
            self.state[n] = "lib" if lib else {"asm": "by-design", "c": "matched"}.get(s, s)

    def find(self, pc):
        i = bisect.bisect_right(self.starts, pc) - 1
        if i >= 0:
            ad, size, n = self.items[i]
            if pc < ad + max(size, 4):
                return ad, size, n
        return None

    def state_of(self, n):
        return self.state.get(n, "matched")


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("profiles", nargs="+")
    ap.add_argument("--out", default=os.path.join(ROOT, "build", "port_hot.csv"))
    ap.add_argument("--top", type=int, default=30)
    a = ap.parse_args()
    maps, agg, unknown = {}, {}, collections.Counter()
    total = 0
    for path in a.profiles:
        lab = label(path)
        for r in csv.DictReader(open(path)):
            prog, pc, calls, insns = r["prog"], int(r["pc"], 16), int(r["calls"]), int(r["insns"])
            total += insns
            if prog not in maps:
                maps[prog] = ProgMap(prog) if os.path.isdir(os.path.join(ROOT, "asm", prog)) else None
            hit = maps[prog].find(pc) if maps[prog] else None
            if hit is None and prog != "main" and maps.get("main") is not None:
                hit = maps["main"].find(pc)   # MAIN code reached while an overlay is resident above it
                if hit:
                    prog = "main"
            if hit is None:
                unknown[prog] += insns
                continue
            ad, size, n = hit
            e = agg.setdefault((prog, n), {"prog": prog, "name": n, "addr": "%08X" % ad, "size": size,
                                           "state": maps[prog].state_of(n), "calls": 0, "insns": 0, "runs": set()})
            e["insns"] += insns
            if pc == ad:
                e["calls"] += calls
            if insns or calls:
                e["runs"].add(lab)
    rows = sorted(agg.values(), key=lambda e: -e["insns"])
    os.makedirs(os.path.dirname(a.out), exist_ok=True)
    with open(a.out, "w", newline="") as f:
        w = csv.writer(f)
        w.writerow(["prog", "name", "addr", "size", "state", "scope", "calls", "insns", "share", "runs"])
        for e in rows:
            w.writerow([e["prog"], e["name"], e["addr"], "%#x" % e["size"], e["state"], scope_of(e["prog"]), e["calls"],
                        e["insns"], "%.5f" % (e["insns"] / total if total else 0),
                        " ".join(sorted(e["runs"], key=lambda s: (s.startswith("a0"), s)))])
    by_state = collections.Counter()
    for e in rows:
        by_state[e["state"]] += e["insns"]
    print("%d profiles, %d interpreted instructions; by state: %s%s" % (
        len(a.profiles), total, ", ".join("%s %.1f %%" % (k, 100.0 * v / total) for k, v in by_state.most_common()),
        ("; not in any function: " + ", ".join("%s %d" % kv for kv in unknown.items())) if unknown else ""))
    pend = [e for e in rows if e["state"] in ("pending", "equiv")]
    pt = sum(e["insns"] for e in pend)
    for k in (10, 50, 200):
        s = sum(e["insns"] for e in pend[:k])
        print("top %3d pending functions: %.1f %% of the pending functions' interpreted instructions (%.1f %% of all), "
              "%#x bytes" % (k, 100.0 * s / pt if pt else 0, 100.0 * s / total if total else 0,
                             sum(e["size"] for e in pend[:k])))
    print("%d pending functions ran interpreted (%d instructions)" % (len(pend), pt))
    for sc, _ in SCOPES:
        sel = [e for e in pend if scope_of(e["prog"]) == sc]
        s = sum(e["insns"] for e in sel)
        print("\n== %s: %d functions, %.1f %% of the pending instructions" % (sc, len(sel), 100.0 * s / pt if pt else 0))
        print("%-4s %-44s %7s %10s %12s %6s  %s" % ("prog", "name", "size", "calls", "insns", "share", "runs"))
        for e in sel[:a.top]:
            runs = sorted(e["runs"])
            print("%-4s %-44s %#7x %10d %12d %5.2f%%  %s" % (
                e["prog"], e["name"][:44], e["size"], e["calls"], e["insns"], 100.0 * e["insns"] / pt,
                " ".join(runs) if len(runs) <= 6 else "%d runs" % len(runs)))
    print("\nall: " + os.path.relpath(a.out, ROOT))


if __name__ == "__main__":
    main()

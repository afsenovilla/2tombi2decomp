#!/usr/bin/env python3
"""Import function names from Tomba2Edit (github.com/SiergiejW/Tomba2Edit, Tomba Club research) into the EU splat
symbol files. Its decomp/symbols_us.json names USA-retail addresses ({name: [image, addr]}); its
decomp/builds/eu-retail.json lines EU code up with USA word by word ("code": [us_addr, eu_addr, words] runs). A
name is kept only when its USA address translates into an EU function start of our split (asm/<prog>/<prog>.s glabel),
so a wrong translation cannot land mid-function. Ghidra placeholders (FUN_*) are skipped; names stay as given.

  python3 -I tools/import_names.py /path/to/Tomba2Edit [--write] [--eu]

USA (config/, the reference) takes the addresses as they are; --eu translates them for config/eu/.

Without --write: prints the counts only. With it: rewrites config/symbol_addrs_<prog>.txt (name = 0xADDR; // type:func),
keeping lines added by hand (those without the `// t2e` tag).
"""
import bisect, collections, glob, json, os, re, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
VER = "eu" if "--eu" in sys.argv else ""


def starts(prog):
    from funcstats import glabels
    return glabels(os.path.join(ROOT, "asm", *([VER] if VER else []), prog, prog + ".s"))


def main():
    t2e = sys.argv[1]
    syms = json.load(open(os.path.join(t2e, "decomp", "symbols_us.json")))
    cfg = os.path.join(ROOT, "config")
    tab = {}
    if "--eu" in sys.argv:          # the EU configs (config/eu): translate through Tomba2Edit's USA->EU runs
        cfg = os.path.join(cfg, "eu")
        runs = json.load(open(os.path.join(t2e, "decomp", "builds", "eu-retail.json")))["images"]
        for img, t in runs.items():
            code = sorted((us, eu, 4 * n) for us, eu, n in t["code"])
            tab[img] = ([c[0] for c in code], code)
    else:                           # USA, the reference: Tomba2Edit's own addresses
        for img in set(v[0] for v in syms.values()):
            tab[img] = ([0], [(0, 0, 1 << 32)])
    out = collections.defaultdict(dict)
    stat = collections.Counter()
    seen_names = collections.Counter()
    # Tomba2Edit parks names it could not place on one shared address (e.g. 40 A00 names on 0x801467BC): an address
    # carrying more than one name is a failed placement, so all of its names are dropped.
    users = collections.Counter(tuple(v) for k, v in syms.items() if not k.startswith("FUN_"))
    for name, (img, us) in syms.items():
        if name.startswith("FUN_"):
            continue
        if users[(img, us)] > 1:
            stat["ambiguous (shared address)"] += 1
            continue
        stat["named"] += 1
        if img not in tab:
            stat["no image"] += 1; continue
        keys, code = tab[img]
        i = bisect.bisect_right(keys, us) - 1
        if i < 0 or not (code[i][0] <= us < code[i][0] + code[i][2]):
            stat["unmapped"] += 1; continue
        eu = code[i][1] + us - code[i][0]
        prog = img.lower()
        if not os.path.exists(os.path.join(ROOT, "asm", *([VER] if VER else []), prog, prog + ".s")):
            stat["no program"] += 1; continue
        out[prog][eu] = name
        seen_names[name] += 1
    res = {}
    for prog, d in out.items():
        st = starts(prog)
        ok = {a: n for a, n in d.items() if a in st}
        stat["not a function start"] += len(d) - len(ok)
        stat["kept"] += len(ok)
        res[prog] = ok
    # a name used twice (same routine in two overlays) gets the overlay suffix so the links stay unique per program
    print(dict(stat))
    for prog in sorted(res):
        print("  %-5s %d" % (prog, len(res[prog])))
    if "--write" in sys.argv:
        for prog, d in res.items():
            p = os.path.join(cfg, "symbol_addrs_%s.txt" % prog)
            keep = [l for l in open(p)] if os.path.exists(p) else []
            keep = [l for l in keep if "// t2e" not in l]
            mine = {re.match(r"\s*(\w+)", l).group(1) for l in keep if l.strip()}
            new = ["%s = 0x%08X; // type:func t2e\n" % (n, a) for a, n in sorted(d.items()) if n not in mine]
            open(p, "w").writelines(keep + new)


if __name__ == "__main__":
    main()

#!/usr/bin/env python3
"""Import function names from Tomba2Edit (github.com/SiergiejW/Tomba2Edit, Tomba Club research) into the EU splat
symbol files. Its decomp/symbols_us.json names USA-retail addresses ({name: [image, addr]}); its
decomp/builds/eu-retail.json lines EU code up with USA word by word ("code": [us_addr, eu_addr, words] runs). A
name is kept only when its USA address translates into an EU function start of our split (asm/<prog>/<prog>.s glabel),
so a wrong translation cannot land mid-function. Ghidra placeholders (FUN_*) are skipped; names stay as given.

  python3 -I tools/import_names.py /path/to/Tomba2Edit [--write]

Without --write: prints the counts only. With it: rewrites config/symbol_addrs_<prog>.txt (name = 0xADDR; // type:func),
keeping lines added by hand (those without the `// t2e` tag).
"""
import bisect, collections, glob, json, os, re, sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))


def starts(prog):
    p = os.path.join(ROOT, "asm", prog, prog + ".s")
    s = set(int(a, 16) for a in re.findall(r"^glabel func_([0-9A-F]{8})", open(p).read(), re.M))
    s |= set(int(a, 16) for a in re.findall(r"^glabel \w+\s*\n(?:.*\n)*?\s*/\* \w+ ([0-9A-F]{8})", open(p).read(), re.M))
    return s


def main():
    t2e = sys.argv[1]
    syms = json.load(open(os.path.join(t2e, "decomp", "symbols_us.json")))
    runs = json.load(open(os.path.join(t2e, "decomp", "builds", "eu-retail.json")))["images"]
    tab = {}
    for img, t in runs.items():
        code = sorted((us, eu, 4 * n) for us, eu, n in t["code"])
        tab[img] = ([c[0] for c in code], code)
    out = collections.defaultdict(dict)
    stat = collections.Counter()
    seen_names = collections.Counter()
    for name, (img, us) in syms.items():
        if name.startswith("FUN_"):
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
            p = os.path.join(ROOT, "config", "symbol_addrs_%s.txt" % prog)
            keep = [l for l in open(p)] if os.path.exists(p) else []
            keep = [l for l in keep if "// t2e" not in l]
            mine = {re.match(r"\s*(\w+)", l).group(1) for l in keep if l.strip()}
            new = ["%s = 0x%08X; // type:func t2e\n" % (n, a) for a, n in sorted(d.items()) if n not in mine]
            open(p, "w").writelines(keep + new)


if __name__ == "__main__":
    main()

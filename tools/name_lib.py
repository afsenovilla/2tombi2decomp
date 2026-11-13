#!/usr/bin/env python3
"""Name the Psy-Q 4.4 library functions of a program from the object signatures (lab313ru/psx_psyq_signatures,
/opt/psyq_sigs/440). Each signature is a whole library object with wildcarded relocations; where it matches, its
labels (the object's public functions; loc_* / text_* local labels skipped) name the addresses.

  python3 -I tools/name_lib.py [--prog main] [--write] [--sigs /opt/psyq_sigs/440]

--write appends `NAME = 0xADDR; // type:func psyq LIB/OBJ` to config/symbol_addrs_<prog>.txt for addresses not yet
named there (a name already used in the program is not added twice). splat then splits the code at those addresses.
Also prints, per library object, the address range it covers (for the library file layout).
"""
import argparse, glob, json, os, re, sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))


def prog_file(prog):
    y = open(os.path.join(ROOT, "config", prog + ".yaml")).read()
    path = re.search(r"target_path:\s*(\S+)", y).group(1)
    vram = int(re.search(r"vram:\s*(0x\w+)", y).group(1), 16)
    start = int(re.search(r"type: code\n\s+start: (0x\w+)", y).group(1), 16)
    return open(os.path.join(ROOT, path), "rb").read(), vram - start


def matches(prog, sigdir):
    """[(addr, size, lib, obj, [(name, addr)])] of every object signature found, longest first, no overlaps."""
    b, delta = prog_file(prog)
    objs = []
    for lib in sorted(glob.glob(os.path.join(sigdir, "*.json"))):
        for o in json.load(open(lib)):
            toks = o.get("sig", "").split()
            if len(toks) >= 8:
                objs.append((len(toks), os.path.basename(lib)[:-5], o["name"], toks, o.get("labels", [])))
    objs.sort(key=lambda x: -x[0])
    taken = []
    out = []
    for n, lib, obj, toks, labels in objs:
        pat = re.compile(b"".join(b"." if t == "??" else re.escape(bytes([int(t, 16)])) for t in toks), re.S)
        for m in pat.finditer(b):
            s = m.start()
            if s % 4 or any(s < e and s + n > a for a, e in taken):
                continue
            taken.append((s, s + n))
            names = [(l["name"], s + l["offset"] + delta) for l in labels
                     if not re.match(r"(loc|text|data|bss|rdata)_[0-9A-Fa-f]+$", l["name"])]
            out.append((s + delta, n, lib, obj, names))
    return sorted(out)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--prog", default="main")
    ap.add_argument("--sigs", default="/opt/psyq_sigs/440")
    ap.add_argument("--write", action="store_true")
    ap.add_argument("-v", action="store_true")
    a = ap.parse_args()
    res = matches(a.prog, a.sigs)
    p = os.path.join(ROOT, "config", "symbol_addrs_%s.txt" % a.prog)
    lines = open(p).read().splitlines(True) if os.path.exists(p) else []
    by_addr, by_name = {}, {}
    for l in lines:
        m = re.match(r"\s*(\w+)\s*=\s*0x([0-9A-Fa-f]+)", l)
        if m:
            by_addr[int(m.group(2), 16)] = m.group(1); by_name[m.group(1)] = int(m.group(2), 16)
    new, renamed = [], 0
    for addr, n, lib, obj, names in res:
        if a.v:
            print("%08X %6d %s:%s %s" % (addr, n, lib, obj, " ".join(x for x, _ in names)))
        for name, at in names:
            if at in by_addr:
                renamed += by_addr[at] != name
                continue
            if name in by_name:
                continue
            by_addr[at] = name; by_name[name] = at
            new.append("%s = 0x%08X; // type:func psyq %s/%s\n" % (name, at, lib.replace(".LIB", ""), obj.replace(".OBJ", "")))
    print("%s: %d objects, %d bytes; %d new names (%d addresses already named differently)"
          % (a.prog, len(res), sum(r[1] for r in res), len(new), renamed))
    if a.write and new:
        open(p, "a").writelines(new)


if __name__ == "__main__":
    main()

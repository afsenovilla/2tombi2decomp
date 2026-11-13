#!/usr/bin/env python3
"""Function census of the split programs: Psy-Q library functions (by object signature), code shared between programs
(the same masked word sequence in several overlays) and the game code left. Reads asm/<prog>/<prog>.s (glabel lines)
and the retail files of config/*.yaml. Prints a table; --csv writes one row per function.

  python3 -I tools/funcstats.py [--sigs /opt/psyq_sigs/440] [--csv build/funcs.csv]

--sigs: a Psy-Q signature directory of lab313ru/psx_psyq_signatures (one LIB.json per library; 440 = Psy-Q 4.4,
the version T2 links). The signatures are fetched at run time, never stored here.
"""
import argparse, collections, csv, glob, json, os, re, struct

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
MEMOPS = {0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x28, 0x29, 0x2A, 0x2B, 0x2E, 0x32, 0x3A}


def mask(w):
    op = w >> 26
    if op in (2, 3):
        return op << 26
    if op == 0x0F:
        return w & 0xFFFF0000
    if (op in MEMOPS or op in (8, 9, 0x0D)) and ((w >> 21) & 31) != 29:
        return w & 0xFFFF0000
    return w


def glabels(asm):
    """Start addresses of every function (glabel, named or not) of a splat .s file."""
    lines = open(asm).read().split("\n")
    out = set()
    for i, l in enumerate(lines):
        if l.startswith("glabel "):
            for m in lines[i + 1:i + 6]:
                mm = re.search(r"/\* \w+ ([0-9A-F]{8}) [0-9A-F]{8} \*/", m)
                if mm:
                    out.add(int(mm.group(1), 16))
                    break
    return out


def programs():
    for y in sorted(glob.glob(os.path.join(ROOT, "config", "*.yaml"))):
        t = open(y).read()
        prog = os.path.basename(y)[:-5]
        path = re.search(r"target_path:\s*(\S+)", t).group(1)
        vram = int(re.search(r"vram:\s*(0x\w+)", t).group(1), 16)
        start = int(re.search(r"type: code\n\s+start: (0x\w+)", t).group(1), 16)
        b = open(os.path.join(ROOT, path), "rb").read()
        code = re.findall(r"\[(0x\w+), (?:asm|c), [\w/]+\]", t)
        tstart = int(code[0], 16)
        m = re.search(r"\[(0x\w+), (?:data|bin), ", t)
        tend = int(m.group(1), 16) if m else len(b)
        asm = os.path.join(ROOT, "asm", prog, prog + ".s")
        if os.path.exists(asm):
            addrs = glabels(asm)
        else:   # c segments: one .s per function, nonmatchings/ (INCLUDE_ASM'd) or matchings/ (in C, or new)
            addrs = set()
            for f in glob.glob(os.path.join(ROOT, "asm", prog, "*matchings", "**", "*.s"), recursive=True):
                addrs |= glabels(f)
            syms = {}
            sp = os.path.join(ROOT, "config", "symbol_addrs_%s.txt" % prog)
            for l in open(sp) if os.path.exists(sp) else []:
                mm = re.match(r"\s*(\w+)\s*=\s*0x([0-9A-Fa-f]+)", l)
                if mm:
                    syms[mm.group(1)] = int(mm.group(2), 16)
            for f in glob.glob(os.path.join(ROOT, "src", prog, "**", "*.c"), recursive=True):
                for n in re.findall(r"^\w[\w \*]*?\b(\w+)\s*\([^;]*\)\s*\n\{", open(f).read(), re.M):
                    a = syms.get(n) or (int(n[5:], 16) if re.fullmatch(r"func_[0-9A-F]{8}", n) else None)
                    if a:
                        addrs.add(a)
        addrs = sorted(addrs)
        yield prog, b, vram - start, tstart, tend, sorted(addrs)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--sigs", default="/opt/psyq_sigs/440")
    ap.add_argument("--csv")
    a = ap.parse_args()
    sigs = []
    for lib in sorted(glob.glob(os.path.join(a.sigs, "*.json"))):
        for o in json.load(open(lib)):
            toks = o.get("sig", "").split()
            if len(toks) >= 16:
                pat = re.compile(b"".join(b"." if t == "??" else re.escape(bytes([int(t, 16)])) for t in toks), re.S)
                sigs.append((os.path.basename(lib)[:-5], o["name"], o.get("labels", []), pat))
    rows = []
    for prog, b, delta, ts, te, addrs in programs():
        lib = {}
        for libname, obj, labels, pat in sigs:
            for m in pat.finditer(b, ts, te):
                if m.start() % 4 == 0:
                    for off in range(m.start(), m.end(), 4):
                        lib.setdefault(off, "%s:%s" % (libname, obj))
        ends = addrs[1:] + [te + delta]
        for s, e in zip(addrs, ends):
            off = s - delta
            fb = b[off:e - delta]
            n = len(fb) // 4
            ws = struct.unpack("<%dI" % n, fb[: n * 4])
            key = hash(tuple(mask(w) for w in ws))
            libhit = lib.get(off)
            rows.append(dict(prog=prog, addr="%08X" % s, size=e - s, lib=libhit or "", key=key))
    seen = collections.defaultdict(list)
    for r in rows:
        if not r["lib"]:
            seen[r["key"]].append(r)
    for k, rs in seen.items():
        for r in rs[1:]:
            r["dup_of"] = "%s:%s" % (rs[0]["prog"], rs[0]["addr"])
    print("%-6s %6s %9s %6s %9s %6s %9s %6s %9s" % ("prog", "funcs", "bytes", "lib", "libB", "dup", "dupB", "game", "gameB"))
    tot = collections.Counter()
    for prog in dict.fromkeys(r["prog"] for r in rows):
        rs = [r for r in rows if r["prog"] == prog]
        c = collections.Counter()
        for r in rs:
            k = "lib" if r["lib"] else ("dup" if r.get("dup_of") else "game")
            c[k] += 1; c[k + "B"] += r["size"]; c["n"] += 1; c["B"] += r["size"]
        tot.update(c)
        print("%-6s %6d %9d %6d %9d %6d %9d %6d %9d" % (prog, c["n"], c["B"], c["lib"], c["libB"], c["dup"], c["dupB"], c["game"], c["gameB"]))
    c = tot
    print("%-6s %6d %9d %6d %9d %6d %9d %6d %9d" % ("total", c["n"], c["B"], c["lib"], c["libB"], c["dup"], c["dupB"], c["game"], c["gameB"]))
    if a.csv:
        with open(a.csv, "w", newline="") as f:
            w = csv.writer(f)
            w.writerow(["prog", "addr", "size", "lib", "dup_of"])
            for r in rows:
                w.writerow([r["prog"], r["addr"], r["size"], r["lib"], r.get("dup_of", "")])


if __name__ == "__main__":
    main()

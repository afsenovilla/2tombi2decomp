#!/usr/bin/env python3
"""Bring src/<prog>/<prog>.c in line with the current splat split after names or function starts changed
(config/symbol_addrs_<prog>.txt): run it after `tools/build.py <prog>` has re-split (asm/<prog>/nonmatchings).

  python3 -I tools/sync_src.py [--prog main]

1. Every `func_XXXXXXXX` token in src/<prog>/ whose address now has a name is replaced by that name.
2. The file's functions are re-laid in address order: C definitions are kept as written (with the extern / comment
   lines just above them), everything else becomes INCLUDE_ASM of the current nonmatchings file, so a function that
   splat now splits in two gets two lines. A C function whose address no longer starts a function is an error.
Then split again (tools/build.py does all of this: split, sync, split again when the file changed).
"""
import argparse, glob, os, re, sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))


def symbols(prog):
    out = {}
    for l in open(os.path.join(ROOT, "config", "symbol_addrs_%s.txt" % prog)):
        m = re.match(r"\s*(\w+)\s*=\s*0x([0-9A-Fa-f]+);", l)
        if m:
            out[m.group(1)] = int(m.group(2), 16)
    return out


def current(prog):
    """[(addr, name)] of the nonmatchings files (functions; dlabel data words included) in address order."""
    out = []
    # splat puts the functions INCLUDE_ASM'd by the C file in nonmatchings/, all others (C-defined or new) in matchings/
    for f in glob.glob(os.path.join(ROOT, "asm", prog, "*matchings", prog, "*.s")):
        m = re.search(r"/\* \w+ ([0-9A-F]{8}) ", open(f).read())
        if m:
            out.append((int(m.group(1), 16), os.path.basename(f)[:-2]))
    return sorted(out)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--prog", default="main")
    a = ap.parse_args()
    prog = a.prog
    sym = symbols(prog)
    addr2name = {v: k for k, v in sym.items()}
    path = os.path.join(ROOT, "src", prog, prog + ".c")
    text = open(path).read()
    # 1. renames
    def ren(m):
        ad = int(m.group(1), 16)
        return addr2name.get(ad, m.group(0))
    text = re.sub(r"\bfunc_([0-9A-F]{8})\b", ren, text)
    # 2. split into header + items
    item_re = re.compile(r'(?ms)^INCLUDE_ASM\("[^"]+", (\w+)\);\n|^(?:[^\n;{}]*\n)??([^\n;{}#]*?\b(\w+)\s*\([^;{}]*\)\s*\n?\{.*?^\}\n)')
    first = item_re.search(text)
    header, body = text[:first.start()], text[first.start():]
    cdefs = {}      # addr -> text (with its leading externs/comments)
    pending = ""
    pos = 0
    for m in item_re.finditer(body):
        gap = body[pos:m.start()]
        pos = m.end()
        if m.group(1):
            pending = ""
            continue
        name = m.group(3)
        ad = sym.get(name) or (int(name[5:], 16) if re.fullmatch(r"func_[0-9A-F]{8}", name) else None)
        lead = (pending + gap).strip("\n")
        pending = ""
        if ad is None:
            sys.exit("C function %s has no address (add it to config/symbol_addrs_%s.txt)" % (name, prog))
        cdefs[ad] = (lead + "\n" if lead else "") + m.group(2).rstrip("\n")
    cur = current(prog)
    starts = {ad for ad, _ in cur}
    for ad in list(cdefs):
        if ad in starts:
            continue
        # now in a file of its own (e.g. a library function, tools/libsplit.py): move the C there
        name = addr2name.get(ad, "func_%08X" % ad)
        own = [f for f in glob.glob(os.path.join(ROOT, "src", prog, "**", name + ".c"), recursive=True)
               if os.path.abspath(f) != os.path.abspath(path)]
        if not own:
            sys.exit("C function at %08X is no longer a function start in the split" % ad)
        t = open(own[0]).read()
        t2 = re.sub(r'INCLUDE_ASM\("[^"]+", %s\);' % name, lambda m: cdefs[ad], t)
        if t2 == t:
            sys.exit("%s: no INCLUDE_ASM line for %s" % (own[0], name))
        open(own[0], "w").write(t2)
        print("moved %s to %s" % (name, os.path.relpath(own[0], ROOT)))
        del cdefs[ad]
    out = [header.rstrip("\n") + "\n"]
    for ad, name in cur:
        if ad in cdefs:
            out.append(cdefs[ad])
        else:
            out.append('INCLUDE_ASM("asm/%s/nonmatchings/%s", %s);' % (prog, prog, name))
    new = "\n".join(out[:1]) + "\n" + "\n\n".join(out[1:]) + "\n"
    changed = new != open(path).read()
    open(path, "w").write(new)
    print(("changed " if changed else "unchanged ") + "%s: %d functions, %d in C" % (os.path.relpath(path, ROOT), len(cur), len(cdefs)))


if __name__ == "__main__":
    main()

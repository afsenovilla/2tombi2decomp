#!/usr/bin/env python3
"""Jump tables of C functions: keep the retail table in the program's rodata.

A `switch` compiled from C makes its own jump table in the object's .rodata, but the linked build keeps the
retail rodata (asm/<prog>/data/*.s), whose table points at the case labels `.L<addr>` that the function's asm
defined (jlabel). For each table in the compiler's assembly (after maspsx) this filter

  - finds the retail table of the same shape (same length, same entries equal to each other) whose labels fall
    inside the function,
  - points the code at it (%hi/%lo of jtbl_<addr> instead of the local table) and drops the local table,
  - defines the global `.L<addr>` labels the retail table names at the matching case labels.

The code bytes do not change (the C already matches), so the case labels land at the retail addresses.
"""
import functools, glob, os, re

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))


@functools.lru_cache(None)
def retail_tables(asm_dir):
    """jtbl name -> list of the label addresses of its entries, from the program's data .s files."""
    out = {}
    for f in glob.glob(os.path.join(ROOT, asm_dir, "data", "*.s")):
        cur = None
        for line in open(f):
            m = re.match(r"\s*dlabel (jtbl_[0-9A-F]{8})", line)
            if m:
                cur = out.setdefault(m.group(1), [])
                continue
            m = re.search(r"\.word \.L([0-9A-F]{8})\b", line)
            if m and cur is not None:
                cur.append(int(m.group(1), 16))
                continue
            if re.match(r"\s*enddlabel", line):
                cur = None
    return out


@functools.lru_cache(None)
def func_addrs(sym_files):
    out = {}
    for p in sym_files:
        p = os.path.join(ROOT, p)
        if not os.path.exists(p):
            continue
        for l in open(p):
            m = re.match(r"\s*(\w+)\s*=\s*0x([0-9A-Fa-f]+)", l)
            if m:
                out[m.group(1)] = int(m.group(2), 16)
    return out


def addr_of(sym_files, name):
    m = re.fullmatch(r"func_([0-9A-F]{8})", name)
    return int(m.group(1), 16) if m else func_addrs(sym_files).get(name)


def shape(entries):
    first = {}
    return tuple(first.setdefault(e, len(first)) for e in entries)


def filter_asm(text, asm_dir, sym_files):
    """asm_dir: the program's splat asm_path (asm/main); sym_files: tuple of its symbol_addrs files."""
    prog = tuple(sym_files)
    tables = retail_tables(asm_dir)
    if "$L" not in text or not tables:
        return text
    lines = text.split("\n")
    # tables sit inside their function (.ent .. .end), between `.section .rodata` and `.text`
    used = set()
    res = []
    i = 0
    fname = None
    pending = []   # (table label, entries) of the current function
    body_start = None
    while i < len(lines):
        line = lines[i]
        m = re.match(r"\s*\.ent\s+(\w+)", line)
        if m:
            fname, pending, body_start = m.group(1), [], len(res)
        if re.match(r"\s*\.section\s+\.rodata", line) and i + 2 < len(lines):
            j = i + 1
            while j < len(lines) and re.match(r"\s*\.align", lines[j]):
                j += 1
            lm = re.match(r"(\$L\d+):\s*$", lines[j]) if j < len(lines) else None
            if lm and fname:
                k = j + 1
                ents = []
                while k < len(lines) and re.match(r"\s*\.word\s+(\$L\d+)\s*$", lines[k]):
                    ents.append(re.match(r"\s*\.word\s+(\$L\d+)", lines[k]).group(1))
                    k += 1
                if ents and k < len(lines) and re.match(r"\s*\.text\s*$", lines[k]):
                    pending.append((lm.group(1), ents, len(res)))
                    i = k + 1   # drop the local table
                    continue
        if re.match(r"\s*\.end\s+\w+", line) and fname and pending:
            res = place(res, body_start, fname, pending, prog, tables, used)
            pending = []
        res.append(line)
        i += 1
    return "\n".join(res)


def place(res, start, fname, pending, prog, tables, used):
    fa = addr_of(prog, fname)
    if fa is None:
        raise SystemExit("jtbl: no address for %s (%s)" % (fname, prog))
    cands = sorted((n for n, e in tables.items() if n not in used and e and all(fa <= x < fa + 0x8000 for x in e)),
                   key=lambda n: min(tables[n]))
    body = res[start:]
    for lab, ents, _ in pending:
        want = shape(ents)
        hit = next((n for n in cands if n not in used and len(tables[n]) == len(ents)
                    and shape(tables[n]) == want), None)
        if hit is None:
            raise SystemExit("jtbl: no retail table for %s in %s" % (lab, fname))
        used.add(hit)
        addrs = dict(zip(ents, tables[hit]))
        body = [re.sub(r"%(hi|lo)\(\s*" + re.escape(lab) + r"\s*\)", r"%\1(" + hit + ")", l) for l in body]
        new = []
        for l in body:
            new.append(l)
            m = re.match(r"(\$L\d+):\s*$", l)
            if m and m.group(1) in addrs:
                a = ".L%08X" % addrs[m.group(1)]
                new += ["\t.globl\t" + a, a + ":"]
        body = new
    return res[:start] + body

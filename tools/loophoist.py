#!/usr/bin/env python3
"""Loop-hoisting diagnostic: what gcc's loop optimizer moved out of each loop, next to what retail loads before
vs inside its loops.

  python3 -I tools/loophoist.py FILE.c FUNC [--prog main] [--cc C] [--flags F] [--all]

FILE.c is compiled as tools/cc.py would (its // CC / // FLAGS lines, or the overrides) with cc1's -dL dump. Per
loop of FUNC (`Loop from A to B`): every movable gcc considered, `insn N: regno R (life L) savings S` and its fate
(moved to M / not desirable / ...), with the value the insn sets (a constant, a symbol's %hi, an address) read
from the dump's RTL; --all also lists the bivs / givs lines. Then, for ours (the compiled object) and for retail
(asm/<prog>/nonmatchings), each loop (a backward branch) with the constants / addresses (li, lui, addiu from $zero,
ori from $zero) loaded in the 24 instructions before it (hoisted) and inside it: a value retail hoists that we
load inside (or the reverse) is what to steer, e.g. with the library compiler's `loop_has_call` patch
(`// CC gcc-2.8.1-loop2`, AGENTS.md "Compilers" item 5), a constant as an early local, or the loop's shape.
"""
import argparse, os, re, shutil, subprocess, sys, tempfile

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))
import cc

MOV = re.compile(r"^Insn (\d+): regno (\d+) \(life (\d+)\),\s*(move-insn\s+)?savings (\d+)\s*(.*)$")


def sections(text):
    out = {}
    for m in re.finditer(r"^;; Function (\w+)\n(.*?)(?=^;; Function |\Z)", text, re.M | re.S):
        out[m.group(1)] = m.group(2)
    return out


def insn_src(dump, uid):
    """a short text of what insn `uid` sets: a constant, %hi(symbol), &symbol, or the RTL (shortened)."""
    m = re.search(r"^\((?:insn|call_insn) %s .*?(?=^\(|\Z)" % uid, dump, re.S | re.M)
    if not m:
        return "?"
    blk = " ".join(m.group(0).split())
    k = blk.find("(set (reg")
    if k < 0:
        return "?"
    k = blk.find(")", k) + 1          # past the destination
    while k < len(blk) and blk[k] == " ":
        k += 1
    depth, e = 0, k
    for e in range(k, len(blk)):
        depth += (blk[e] == "(") - (blk[e] == ")")
        if depth == 0:
            break
    s = blk[k:e + 1]
    sym = re.findall(r'symbol_ref:SI \("?([\w.]+)"?\)', s)
    ks = re.findall(r"const_int (-?\d+)", s)
    if s.startswith("(high"):
        return "%%hi(%s)" % (sym[0] if sym else "?")
    if s.startswith("(const_int"):
        v = int(ks[0])
        return "%d (0x%X)" % (v, v & 0xFFFFFFFF)
    if s.startswith(("(lo_sum", "(symbol_ref", "(const")) and sym:
        return "&%s" % sym[0]
    return s[:70]


def loops_of(ins):
    """[(loop start index, end index)] of a list of (address, mnemonic, operands): each backward branch."""
    out = []
    addr = {a: i for i, (a, _, _) in enumerate(ins)}
    for i, (a, mn, ops) in enumerate(ins):
        if mn.startswith("b") or mn == "j":
            m = re.search(r"(?:0x)?([0-9a-fA-F]+)\s*(?:<[^>]*>)?\s*$", ops)
            if m:
                t = int(m.group(1), 16)
                if t <= a and t in addr:
                    out.append((addr[t], i))
    return out


def consts(ins, i0, i1):
    """the constants / addresses loaded by ins[i0:i1]: li / lui / addiu or ori from $zero."""
    out = []
    for a, mn, ops in ins[i0:i1]:
        o = [x.strip().lstrip("$") for x in ops.split(",")]
        if mn == "lui":
            out.append("lui %s" % o[-1])
        elif mn == "li":
            out.append("li %s" % o[-1])
        elif mn in ("addiu", "ori") and len(o) == 3 and o[1] in ("zero", "0"):
            out.append("li %s" % o[2])
    return out


def ours_asm(src, func, over):
    d = tempfile.mkdtemp(prefix="tmp_loophoist_", dir=os.path.join(ROOT, "build"))
    try:
        cc.compile_c(src, d + "/a.o", over)
        out = subprocess.run(["mipsel-linux-gnu-objdump", "-dr", "--no-show-raw-insn", d + "/a.o"],
                             capture_output=True, text=True).stdout
    finally:
        shutil.rmtree(d, ignore_errors=True)
    m = re.search(r"<%s>:\n(.*?)(?:\n\n|\Z)" % re.escape(func), out, re.S)
    ins = []
    for l in (m.group(1) if m else "").split("\n"):
        r = re.match(r"\s*[0-9a-f]+:\s*R_MIPS_HI16\s+(\S+)", l)
        if r and ins and ins[-1][1] == "lui":
            ins[-1] = (ins[-1][0], "lui", re.sub(r",[^,]*$", ", %%hi(%s)" % r.group(1), ins[-1][2]))
            continue
        x = re.match(r"\s*([0-9a-f]+):\s+(\S+)\s*(.*)$", l)
        if x:
            ins.append((int(x.group(1), 16), x.group(2), x.group(3)))
    return ins


def retail_asm(prog, func):
    import decomp
    path = decomp.find_asm(prog, func)
    ins = []
    for l in open(path):
        m = re.match(r"\s*/\*\s*[0-9A-F]+\s+([0-9A-F]{8})\s+[0-9A-F]{8}\s*\*/\s+(\S+)\s*(.*)$", l)
        if m:
            ops = re.sub(r"\.L([0-9A-F]{8})", r"0x\1", m.group(3))
            ins.append((int(m.group(1), 16), m.group(2), ops))
    return ins


def report(label, ins):
    print("%s: %d instructions" % (label, len(ins)))
    base = ins[0][0] if ins else 0
    for i0, i1 in loops_of(ins):
        print("  loop +%X..+%X (%d insns): before %s | inside %s" % (
            ins[i0][0] - base, ins[i1][0] - base, i1 - i0 + 1, ", ".join(consts(ins, max(0, i0 - 24), i0)) or "-",
            ", ".join(consts(ins, i0, i1 + 1)) or "-"))


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("src")
    ap.add_argument("func")
    ap.add_argument("--prog", default="main")
    ap.add_argument("--cc")
    ap.add_argument("--flags")
    ap.add_argument("--all", action="store_true", help="also the biv / giv lines of the dump")
    a = ap.parse_args()
    over = {k: v for k, v in (("cc", a.cc), ("flags", a.flags)) if v}
    o = cc.options(a.src, over)
    gcc = os.path.join(cc.OLDGCC, o["cc"])
    inc = os.path.join(ROOT, "include")
    d = tempfile.mkdtemp(prefix="tmp_loophoist_", dir=os.path.join(ROOT, "build"))
    try:
        subprocess.run([gcc + "/cpp", "-undef", "-D__GNUC__=2", "-DMIPSEL", "-D_LANGUAGE_C", "-I" + inc,
                        "-I" + inc + "/psyq", os.path.abspath(a.src), d + "/x.i"], check=True)
        r = subprocess.run([gcc + "/cc1", "-quiet", "-w", "-funsigned-char"] + o["flags"].split() +
                           ["-dL", "x.i", "-o", "x.s"], cwd=d, capture_output=True, text=True)
        if r.returncode:
            sys.exit("cc1 failed:\n" + r.stderr[-2000:])
        dump = sections(open(d + "/x.i.loop").read()).get(a.func)
    finally:
        shutil.rmtree(d, ignore_errors=True)
    if dump is None:
        sys.exit("no %s in the loop dump" % a.func)
    print("gcc's loop pass (%s %s):" % (o["cc"], o["flags"]))
    for l in dump.split("\n"):
        if l.startswith("Loop from"):
            print("  " + l)
            continue
        m = MOV.match(l)
        if m:
            fate = m.group(6).strip() or "-"
            mv = re.search(r"moved to (\d+)", fate)
            print("    insn %s: reg %s life %s %ssavings %s  %-22s %s" % (
                m.group(1), m.group(2), m.group(3), "move-insn " if m.group(4) else "", m.group(5), fate,
                insn_src(dump, mv.group(1) if mv else m.group(1))))
        elif a.all and re.match(r"Insn \d+: (possible biv|giv|dest address)", l):
            print("    " + l)
    report("ours", ours_asm(a.src, a.func, over or None))
    try:
        report("retail", retail_asm(a.prog, a.func))
    except Exception as e:
        print("retail: %s" % e)


if __name__ == "__main__":
    main()

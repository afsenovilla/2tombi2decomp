#!/usr/bin/env python3
"""Side-by-side diff of a compiled C function and the retail one.

  python3 -I tools/sbs.py FILE.c FUNC [--prog main] [--all] [--width 52]
  python3 -I tools/ccheck.py FILE.c --prog P --func FUNC --sbs      (the same from ccheck, for every DIFF function)

Both sides are disassembled the same way (objdump of the raw words at address 0), so branch targets and `j` to a
local label read as offsets from the function start. Relocated fields are masked on both sides (ours: the object's
relocations; retail: the %hi/%lo/jal operands of the splat .s) and annotated with the symbol names, so a different
symbol name or address is not a difference. The two sides are aligned with difflib; marks: ' ' same, '|' changed,
'<' only ours, '>' only retail. --all prints the equal lines too (default: differing lines with 2 lines of context).
"""
import argparse, difflib, glob, os, re, struct, subprocess, sys, tempfile

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))
BRANCH = ("b", "bal", "beq", "bne", "beqz", "bnez", "blez", "bgtz", "bltz", "bgez", "bltzal", "bgezal", "beql",
          "bnel", "bc0f", "bc0t", "bc2f", "bc2t")


def disasm(words):
    """objdump text of each word (address 0, ABI register names)."""
    d = tempfile.mkdtemp(dir=os.path.join(ROOT, "build"))
    try:
        open(d + "/w.bin", "wb").write(struct.pack("<%dI" % len(words), *words))
        out = subprocess.run(["mipsel-linux-gnu-objdump", "-D", "-b", "binary", "-m", "mips:3000", "-EL",
                              "--no-show-raw-insn", d + "/w.bin"], capture_output=True, text=True).stdout
    finally:
        subprocess.run(["rm", "-rf", d])
    lines = {}
    for l in out.splitlines():
        m = re.match(r"\s*([0-9a-f]+):\s+(.*)$", l)
        if m:
            lines[int(m.group(1), 16)] = re.sub(r"\s+", " ", m.group(2).split("<")[0]).strip()
    return [lines.get(i * 4, ".word 0x%08x" % w) for i, w in enumerate(words)]


def retail_relocs(prog, name):
    """{word index: symbol} of the relocated operands of the retail function (splat .s)."""
    hits = glob.glob(os.path.join(ROOT, "asm", prog, "*matchings", "**", name + ".s"), recursive=True)
    out = {}
    if not hits:
        return out
    i = 0
    for l in open(hits[0]):
        m = re.match(r"\s*/\* \w+ \w+ \w+ \*/\s+(\S+)\s*(.*)", l)
        if not m:
            continue
        op, args = m.group(1), m.group(2)
        s = re.search(r"%(?:hi|lo)\(([^)]+)\)", args)
        if s:
            out[i] = s.group(1)
        elif op in ("jal", "j") and not args.strip().startswith(".L"):
            out[i] = args.strip()
        i += 1
    return out


def obj_function(obj, name):
    """(words, {word index: symbol}, section offset) of `name` in obj."""
    d = os.path.dirname(obj)
    subprocess.run(["mipsel-linux-gnu-objcopy", "-O", "binary", "-j", ".text", obj, d + "/sbs_t.bin"], check=True)
    text = open(d + "/sbs_t.bin", "rb").read()
    off = size = None
    for l in subprocess.run(["mipsel-linux-gnu-nm", "-S", "--defined-only", obj], capture_output=True,
                            text=True).stdout.splitlines():
        p = l.split()
        if len(p) == 4 and p[3] == name and p[2] in "Tt":
            off, size = int(p[0], 16), int(p[1], 16)
    if off is None:
        raise SystemExit("%s not in %s" % (name, obj))
    rel = {}
    for l in subprocess.run(["mipsel-linux-gnu-objdump", "-r", "-j", ".text", obj], capture_output=True,
                            text=True).stdout.splitlines():
        m = re.match(r"([0-9a-f]{8})\s+(R_MIPS_\w+)\s+(\S+)", l)
        if m and off <= int(m.group(1), 16) < off + size:
            rel[(int(m.group(1), 16) - off) // 4] = m.group(3)
    words = list(struct.unpack("<%dI" % (size // 4), text[off:off + size]))
    return words, rel, off


def lines_of(words, rel, j_base):
    """(display, key, branch target word index or None) per word. j_base(field) -> target offset from the function
    start of a `j`. Branch keys leave the target out: it is compared through the alignment afterwards."""
    out = []
    for i, (w, txt) in enumerate(zip(words, disasm(words))):
        op = txt.split()[0] if txt else ""
        key, tgt = txt, None
        if op in BRANCH:   # target as an offset from the function start (both sides at address 0)
            head, sep, last = txt.rpartition(",") if "," in txt else txt.partition(" ")
            try:
                tgt = int(last.strip(), 16)
                txt = "%s%s+0x%x" % (head, sep, tgt)
                key = "%s%sT" % (head, sep)
            except ValueError:
                pass
        if i in rel:
            sym = re.sub(r"[+-]0x[0-9a-f]+$", "", rel[i])
            if w >> 26 == 2 and (sym.startswith((".text", ".L")) or sym == ""):
                tgt = j_base(w)
                txt, key = "j +0x%x" % tgt, "j T"
            elif w >> 26 in (2, 3):
                key = op + " R"
                txt = "%s %s" % (op, rel[i])
            else:
                key = re.sub(r"(,|\s)(-?0x[0-9a-f]+|-?\d+)(\(|$)", r"\1R\3", txt, count=1)
                txt = "%s {%s}" % (txt, rel[i])
        elif w >> 26 == 2:
            tgt = j_base(w)
            txt, key = "j +0x%x" % tgt, "j T"
        out.append((txt, key, None if tgt is None else tgt // 4))
    return out


def render(obj, name, want, prog, addr, show_all=False, width=52):
    words, rel, off = obj_function(obj, name)
    ours = lines_of(words, rel, lambda w: ((w & 0x3FFFFFF) << 2) - off)
    rwords = list(struct.unpack("<%dI" % (len(want) // 4), want))
    theirs = lines_of(rwords, retail_relocs(prog, name),
                      lambda w: (((w & 0x3FFFFFF) << 2) | (addr & 0xF0000000)) - addr)
    sm = difflib.SequenceMatcher(None, [x[1] for x in ours], [x[1] for x in theirs], autojunk=False)
    ops = sm.get_opcodes()
    pair = {}   # ours word index -> retail word index, for the aligned equal lines
    for tag, i1, i2, j1, j2 in ops:
        if tag == "equal":
            pair.update({i1 + k: j1 + k for k in range(i2 - i1)})

    def target(i):   # a branch into lines only ours has lands on the next line both have
        while i < len(ours) and i not in pair:
            i += 1
        return pair.get(i, len(theirs))
    rows = []
    for tag, i1, i2, j1, j2 in ops:
        for k in range(max(i2 - i1, j2 - j1)):
            a = (i1 + k, ours[i1 + k][0]) if i1 + k < i2 else None
            b = (j1 + k, theirs[j1 + k][0]) if j1 + k < j2 else None
            mark = " " if tag == "equal" else ("|" if a and b else ("<" if a else ">"))
            if mark == " " and ours[a[0]][2] is not None and target(ours[a[0]][2]) != theirs[b[0]][2]:
                mark = "|"    # a branch to a line that does not correspond
            rows.append((mark, a, b))
    nd = sum(1 for r in rows if r[0] != " ")
    keep = set(range(len(rows))) if show_all else {j for i, r in enumerate(rows) if r[0] != " "
                                                   for j in range(i - 2, i + 3)}
    out = ["%-*s   %s" % (width + 6, "ours (%d words)" % len(words), "retail %08X (%d words)" % (addr, len(rwords)))]
    last = -1
    for i, (mark, a, b) in enumerate(rows):
        if i not in keep:
            continue
        if last >= 0 and i != last + 1:
            out.append("  ...")
        last = i
        la = "%4x %s" % (a[0] * 4, a[1]) if a else ""
        lb = "%4x %s" % (b[0] * 4, b[1]) if b else ""
        out.append("%-*s %s %s" % (width + 6, la[:width + 6], mark, lb))
    out.append("%d lines differ" % nd)
    return "\n".join(out)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("src")
    ap.add_argument("func")
    ap.add_argument("--prog", default="main")
    ap.add_argument("--all", action="store_true")
    ap.add_argument("--width", type=int, default=52)
    a, rest = ap.parse_known_args()
    import cc, ccheck
    binary, delta, syms = ccheck.prog_info(a.prog)
    addr = syms.get(a.func) or (int(a.func[5:], 16) if re.fullmatch(r"func_[0-9A-Fa-f]{8}", a.func) else None)
    sizes = ccheck.retail_sizes(a.prog)
    if addr is None or a.func not in sizes:
        sys.exit("no address / size for %s in %s" % (a.func, a.prog))
    d = tempfile.mkdtemp(dir=os.path.join(ROOT, "build"))
    try:
        cc.compile_c(os.path.abspath(a.src), d + "/a.o")
        print(render(d + "/a.o", a.func, binary[addr - delta: addr - delta + sizes[a.func]], a.prog, addr, a.all,
                     a.width))
    except cc.CompileError as e:
        sys.exit("compile error: %s" % e)
    finally:
        subprocess.run(["rm", "-rf", d])


if __name__ == "__main__":
    main()

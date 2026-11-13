#!/usr/bin/env python3
"""Compile a C file and compare each function in it with the retail bytes (fast check, no link).

  python3 -I tools/ccheck.py src/main/foo.c [--prog main] [--cc gcc-2.8.1-psx] [--aspsx 2.79] [--opt=-O2] [-G 0] [-v]

Pipeline (as Tombi-Decomp's ncheck): old-gcc 2.8.1 cpp + cc1 (the Psy-Q 4.4 compiler, docs/COMPILER.md; -O2 -G0 -funsigned-char unless overridden), maspsx, GNU as.
Each defined function is looked up by name in config/symbol_addrs_<prog>.txt or as func_XXXXXXXX, and compared word by
word with the retail file; relocated fields (jal target, %hi/%lo) are compared only where the object has no relocation.
The length must also be the retail one (asm/<prog>/nonmatchings `nonmatching NAME, SIZE`).
Prints OK / DIFF per function (with -v the differing words); --func NAME limits the check.
"""
import argparse, os, re, struct, subprocess, sys, tempfile

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))


def prog_info(prog):
    y = open(os.path.join(ROOT, "config", prog + ".yaml")).read()
    path = re.search(r"target_path:\s*(\S+)", y).group(1)
    vram = int(re.search(r"vram:\s*(0x\w+)", y).group(1), 16)
    start = int(re.search(r"type: code\n\s+start: (0x\w+)", y).group(1), 16)
    syms = {}
    p = os.path.join(ROOT, "config", "symbol_addrs_%s.txt" % prog)
    for l in open(p):
        m = re.match(r"\s*(\w+)\s*=\s*0x([0-9A-Fa-f]+)", l)
        if m:
            syms[m.group(1)] = int(m.group(2), 16)
    return open(os.path.join(ROOT, path), "rb").read(), vram - start, syms


def compile_c(src, a, d):
    gcc = "/opt/oldgcc/" + a.cc
    inc = os.path.join(ROOT, "include")
    subprocess.run([gcc + "/cpp", "-undef", "-D__GNUC__=2", "-DMIPSEL", "-D_LANGUAGE_C", "-I" + inc, "-I" + inc + "/psyq",
                    src, d + "/a.i"], check=True)
    subprocess.run([gcc + "/cc1", "-quiet", "-w", "-funsigned-char", a.O, "-G" + a.G] + a.cflags +
                   [d + "/a.i", "-o", d + "/a.s"], check=True)
    mas = subprocess.run([sys.executable, "/opt/maspsx/maspsx.py", "--aspsx-version=" + a.aspsx, "--expand-div"] +
                         (["-G" + a.G] if a.G != "0" else []), input=open(d + "/a.s").read(), check=True,
                         capture_output=True, text=True).stdout
    open(d + "/b.s", "w").write(mas)
    subprocess.run(["mipsel-linux-gnu-as", "-EL", "-march=r3000", "-mtune=r3000", "-no-pad-sections", "-O1", "-G0",
                    "-I" + inc, d + "/b.s", "-o", d + "/a.o"], check=True, cwd=ROOT)
    subprocess.run(["mipsel-linux-gnu-objcopy", "-O", "binary", "-j", ".text", d + "/a.o", d + "/t.bin"], check=True)
    text = open(d + "/t.bin", "rb").read()
    funcs = []
    for l in subprocess.run(["mipsel-linux-gnu-nm", "-S", "--defined-only", d + "/a.o"], capture_output=True,
                            text=True).stdout.splitlines():
        p = l.split()
        if len(p) == 4 and p[2] in "Tt":
            funcs.append((p[3], int(p[0], 16), int(p[1], 16)))
    rel = set()
    for l in subprocess.run(["mipsel-linux-gnu-objdump", "-r", "-j", ".text", d + "/a.o"], capture_output=True,
                            text=True).stdout.splitlines():
        m = re.match(r"([0-9a-f]{8})\s+R_MIPS_", l)
        if m:
            rel.add(int(m.group(1), 16))
    return text, sorted(funcs, key=lambda f: f[1]), rel


def retail_sizes(prog):
    """name -> size of every function of a c-segment program (the `nonmatching NAME, 0xSIZE` line splat writes)."""
    import glob
    out = {}
    for f in glob.glob(os.path.join(ROOT, "asm", prog, "nonmatchings", "**", "*.s"), recursive=True):
        m = re.search(r"^nonmatching (\w+),\s*(0x[0-9A-Fa-f]+)", open(f).read(), re.M)
        if m:
            out[m.group(1)] = int(m.group(2), 16)
    return out


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("src")
    ap.add_argument("--prog", default="main")
    ap.add_argument("--cc", default="gcc-2.8.1-psx")
    ap.add_argument("--aspsx", default="2.79")
    ap.add_argument("--opt", dest="O", default="-O2")
    ap.add_argument("-G", default="0")
    ap.add_argument("-v", action="store_true")
    ap.add_argument("--all", action="store_true", help="also check the INCLUDE_ASM functions (sanity test)")
    ap.add_argument("--func", action="append", help="check only these functions (repeatable)")
    a, rest = ap.parse_known_args()
    a.cflags = rest
    binary, delta, syms = prog_info(a.prog)
    sizes = retail_sizes(a.prog)
    d = tempfile.mkdtemp()
    a.src = os.path.abspath(a.src)
    text, funcs, rel = compile_c(a.src, a, d)
    bad = 0
    asm_included = {n[:-len(".NON_MATCHING")] for n, _, _ in funcs if n.endswith(".NON_MATCHING")}
    if not a.all:   # INCLUDE_ASM functions are the retail bytes by construction: only the C ones are checked
        funcs = [f for f in funcs if f[0] not in asm_included and not f[0].endswith(".NON_MATCHING")]
    for name, off, size in funcs:
        if a.func and name not in a.func:
            continue
        addr = syms.get(name) or (int(name[5:], 16) if re.fullmatch(r"func_[0-9A-Fa-f]{8}", name) else None)
        if addr is None:
            print("?    %s (no address)" % name); continue
        want = binary[addr - delta: addr - delta + size]
        got = text[off: off + size]
        diffs = []
        for i in range(0, size, 4):
            g, w = struct.unpack("<I", got[i:i + 4])[0], struct.unpack("<I", want[i:i + 4])[0]
            if off + i in rel:
                op = g >> 26
                if op in (2, 3):
                    g, w = g & 0xFC000000, w & 0xFC000000
                else:
                    g, w = g & 0xFFFF0000, w & 0xFFFF0000
            if g != w:
                diffs.append((i, g, w))
        want_size = sizes.get(name)
        if want_size is not None and want_size != size:
            diffs.append((-1, size, want_size))
        ok = not diffs
        bad += not ok
        print("%s %s %08X (%d bytes)%s" % ("OK  " if ok else "DIFF", name, addr, size, "" if ok else ", %d words differ" % len(diffs)))
        if a.v:
            for i, g, w in diffs:
                if i < 0:
                    print("    size: got 0x%X bytes, retail 0x%X" % (g, w))
                else:
                    print("    +%03X got %08X want %08X" % (i, g, w))
    subprocess.run(["rm", "-rf", d])
    sys.exit(1 if bad else 0)


if __name__ == "__main__":
    main()

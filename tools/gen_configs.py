#!/usr/bin/env python3
"""Writes the first splat configs (config/<prog>.yaml) of one disc version: the boot exe, MAIN.EXE and the BIN/*.BIN
overlays, as rodata / asm / data with the text boundaries found by a heuristic (first function prologue or call target,
last `jr ra` before a long run without one). The matching all-asm build (tools/build.py) proves the boundaries.

  python3 -I tools/gen_configs.py game/eu [--force]

Load addresses (docs/DISCS.md): area overlays A00..A0L 0x80109D84; GAME/DEMO 0x80106D80; OPN/CRD 0x80188000;
START.BIN is data (file names). Existing yamls are kept unless --force (they may carry hand-made splits).
"""
import hashlib, os, struct, sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
JR = 0x03E00008
LOADS = {"GAME": 0x80106D80, "DEMO": 0x80106D80, "OPN": 0x80188000, "CRD": 0x80188000}


def text_bounds(w, base, lo):
    n = len(w)
    jrs = [i for i, x in enumerate(w) if x == JR and i >= lo]
    pro = [i for i, x in enumerate(w) if (x & 0xFFFF8000) == 0x27BD8000 and i >= lo]
    tg = [((x & 0x3FFFFFF) << 2 | 0x80000000) for x in w if x >> 26 == 3]
    tg = [(t - base) // 4 for t in tg if base <= t < base + 4 * n]
    tg = [t for t in tg if t >= lo]
    start = min(pro[:1] + tg) if (pro or tg) else lo
    end = None
    for a, b in zip(jrs, jrs[1:] + [n + 10000]):
        if a >= start and b - a > 0x800:
            end = a + 2
            break
    return start, end


def yaml(prog, path, sha, base, header, rodata, text, data, size):
    hdr = "  - name: header\n    type: header\n    start: 0x0\n" if header else ""
    off0 = 0x800 if header else 0
    sub = []
    if text > rodata:
        sub.append("      - [0x%X, rodata, %s_rodata]" % (rodata, prog))
    sub.append("      - [0x%X, asm, %s]" % (text, prog))
    tail = size & ~3
    if data < tail:
        sub.append("      - [0x%X, data, %s_data]" % (data, prog))
    if tail < size:   # an odd-sized file: the last bytes as a blob (splat's data drops a partial word)
        sub.append("      - [0x%X, bin, %s_tail]" % (tail, prog))
    return """name: {name}
sha1: {sha}
options:
  basename: {p}
  target_path: {path}
  base_path: ..
  platform: psx
  compiler: PSYQ
  asm_path: asm/{p}
  src_path: src/{p}
  build_path: build
  ld_script_path: build/{p}.ld
  symbol_addrs_path:
    - config/symbol_addrs_{p}.txt
  undefined_funcs_auto_path: build/undefined_funcs_auto.{p}.txt
  undefined_syms_auto_path: build/undefined_syms_auto.{p}.txt
  find_file_boundaries: False
  disassemble_all: True
  asm_function_macro: glabel
  asm_jtbl_label_macro: jlabel
  asm_data_macro: dlabel
  generate_asm_macros_files: True
  asm_inc_header: ".include \\"macro.inc\\"\\n\\n.set noat\\n.set noreorder\\n\\n"
  section_order: [".rodata", ".text", ".data", ".bss"]
  subalign: 4
  string_encoding: ASCII
  rodata_string_guesser_level: 2
  data_string_guesser_level: 2
segments:
{hdr}  - name: {p}
    type: code
    start: 0x{o0:X}
    vram: 0x{base:08X}
    align: 4
    subalign: 4
    subsegments:
{sub}
  - [0x{size:X}]
""".format(name=os.path.basename(path), sha=sha, p=prog, path=path, hdr=hdr, o0=off0, base=base,
           sub="\n".join(sub), size=size)


def main():
    fs = sys.argv[1].rstrip("/")
    force = "--force" in sys.argv
    progs = []
    for f in sorted(os.listdir(fs)):
        if f.upper() == "MAIN.EXE":
            progs.append(("main", f))
        elif f[:4] in ("SCES", "SCUS", "SLPS"):
            progs.append(("boot", f))
    for f in sorted(os.listdir(os.path.join(fs, "BIN"))):
        if f.upper() != "START.BIN":
            progs.append((f[:-4].lower(), os.path.join("BIN", f)))
    for prog, rel in progs:
        out = os.path.join(ROOT, "config", prog + ".yaml")
        if os.path.exists(out) and not force:
            continue
        b = open(os.path.join(fs, rel), "rb").read()
        exe = b[:8] == b"PS-X EXE"
        if exe:
            base = struct.unpack("<I", b[0x18:0x1C])[0]
            body = b[0x800:]
        else:
            base = LOADS.get(prog.upper(), 0x80109D84)
            body = b
        n = len(body) // 4
        w = struct.unpack("<%dI" % n, body[: n * 4])
        lo = 0 if exe else 1
        s, e = text_bounds(w, base, lo)
        o0 = 0x800 if exe else 0
        size = len(b)
        rodata = o0
        data = o0 + 4 * e if e else size
        open(out, "w").write(yaml(prog, os.path.relpath(os.path.join(fs, rel), ROOT), hashlib.sha1(b).hexdigest(),
                                  base, exe, rodata, o0 + 4 * s, min(data, size), size))
        sym = os.path.join(ROOT, "config", "symbol_addrs_%s.txt" % prog)
        if not os.path.exists(sym):
            open(sym, "w").close()
        print("%-6s base %08X text %08X..%08X size 0x%X" % (prog, base, base + 4 * s, base + (data - o0), len(b)))


if __name__ == "__main__":
    main()

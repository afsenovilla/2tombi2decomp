"""The compiler pipeline, shared by tools/build.py, ccheck.py, sweep.py and libsweep.py.

Default: the game's Psy-Q 4.4 = old-gcc gcc-2.8.1-psx cc1 `-O2 -G0 -funsigned-char` + maspsx (ASPSX 2.79) + GNU as.
A C file can override it in its first lines (needed for the Psy-Q library, which Sony built with other compilers):
    // CC gcc-2.7.2-psx          old-gcc build under /opt/oldgcc
    // FLAGS -O2 -G0             cc1 options (replaces the default -O2 -G0)
    // ASPSX 2.56                maspsx --aspsx-version
    // AS gnu                    no maspsx: GNU as assembles cc1's output in reorder mode (`move` as addu), as
                                 Tombi-Decomp's library recipe
"""
import os, re, subprocess, sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
OLDGCC = "/opt/oldgcc"
DEFAULT = {"cc": "gcc-2.8.1-psx", "flags": "-O2 -G0", "aspsx": "2.79", "as": "maspsx"}
AS = ["mipsel-linux-gnu-as", "-EL", "-march=r3000", "-mtune=r3000", "-no-pad-sections", "-G0"]


def options(src, override=None):
    o = dict(DEFAULT)
    head = open(src, errors="replace").read(800)
    for k, key in (("CC", "cc"), ("FLAGS", "flags"), ("ASPSX", "aspsx"), ("AS", "as")):
        m = re.search(r"^//\s*%s\s+(.+?)\s*$" % k, head, re.M)
        if m:
            o[key] = m.group(1)
    o.update(override or {})
    return o


class CompileError(Exception):
    pass


def _run(cmd, **kw):
    r = subprocess.run(cmd, capture_output=True, text=True, cwd=ROOT, **kw)
    if r.returncode:
        raise CompileError("%s\n%s%s" % (" ".join(cmd), r.stdout, r.stderr))
    return r.stdout


def text_size(obj):
    for l in subprocess.run(["mipsel-linux-gnu-objdump", "-h", obj], capture_output=True, text=True).stdout.splitlines():
        p = l.split()
        if len(p) > 2 and p[1] == ".text":
            return int(p[2], 16)
    return 0


def pad_text(obj, asm, pad_to, assemble):
    """Library objects end with nops up to their 16-byte boundary: append them when the C gives less text."""
    if not pad_to:
        return
    have = text_size(obj)
    if have < pad_to <= have + 12:
        open(asm, "a").write("\n\t.section .text\n\t.space %d\n" % (pad_to - have))
        assemble()


def compile_c(src, obj, override=None, defines=(), pad_to=None, asm_filter=None):
    """src (.c) -> obj (.o) with the file's options; intermediate files beside obj. pad_to: the retail size of the
    file's text (a library function file), filled with nops when the compiled code is shorter by up to 12 bytes."""
    o = options(src, override)
    gcc = os.path.join(OLDGCC, o["cc"])
    base = obj[:-2]
    inc = os.path.join(ROOT, "include")
    _run([gcc + "/cpp", "-undef", "-D__GNUC__=2", "-DMIPSEL", "-D_LANGUAGE_C", "-I" + inc, "-I" + inc + "/psyq"] +
         ["-D" + d for d in defines] + [src, base + ".i"])
    _run([gcc + "/cc1", "-quiet", "-w", "-funsigned-char"] + o["flags"].split() + [base + ".i", "-o", base + ".cc.s"])
    s = open(base + ".cc.s").read()
    if o["as"] == "gnu":
        s = re.sub(r"(?m)^\tmove\t(\$[0-9a-z]+),(\$[0-9a-z]+)", r"\taddu\t\1,\2,$0", s)
        s = re.sub(r"(?m)^\t\.rdata$", "\t.section .rodata", s)
        open(base + ".mas.s", "w").write(s)

        def assemble():
            _run(AS + ["-O2", "-I" + inc, base + ".mas.s", "-o", obj])
            # GNU as gives MIPS ELF sections 16-byte alignment; the link packs the files at 4 bytes
            _run(["mipsel-linux-gnu-objcopy"] + ["--set-section-alignment=%s=4" % x
                                                 for x in (".text", ".data", ".bss", ".rodata")] + [obj])
        assemble()
        pad_text(obj, base + ".mas.s", pad_to, assemble)
        return o
    g = re.search(r"-G(\d+)", o["flags"])
    r = subprocess.run([sys.executable, "/opt/maspsx/maspsx.py", "--aspsx-version=" + o["aspsx"], "--expand-div"] +
                       (["-G" + g.group(1)] if g and g.group(1) != "0" else []),
                       input=s, capture_output=True, text=True)
    if r.returncode:
        raise CompileError("maspsx %s\n%s" % (src, r.stderr))
    open(base + ".mas.s", "w").write(asm_filter(r.stdout) if asm_filter else r.stdout)

    def assemble():
        _run(AS + ["-O1", "-I" + inc, base + ".mas.s", "-o", obj])
        _run(["mipsel-linux-gnu-objcopy"] + ["--set-section-alignment=%s=4" % x
                                             for x in (".text", ".data", ".bss", ".rodata")] + [obj])
    assemble()
    pad_text(obj, base + ".mas.s", pad_to, assemble)
    return o

"""The compiler pipeline, shared by tools/build.py, ccheck.py, sweep.py and libsweep.py.

Default: the game's Psy-Q 4.4 = old-gcc gcc-2.8.1-psx cc1 `-O2 -G0 -funsigned-char` + maspsx (ASPSX 2.79) + GNU as.
A C file can override it in its first lines (needed for the Psy-Q library, which Sony built with other compilers):
    // CC gcc-2.7.2-psx          old-gcc build under /opt/oldgcc
    // FLAGS -O2 -G0             cc1 options (replaces the default -O2 -G0)
    // ASPSX 2.56                maspsx --aspsx-version
    // AS gnu                    no maspsx: GNU as assembles cc1's output in reorder mode (`move` as addu), as
                                 Tombi-Decomp's library recipe
    // EPILOGUE sony             Sony's gcc build of the library (no exact copy here) left the epilogue alone: the insn
                                 reorg moved into `j $31`'s delay slot goes back before the register restores, and
                                 a restore of $31 just before `j $31` becomes `lw ra; addiu sp; jr ra; nop`
    // RETURN sony               one return per function, as Sony's library compiler: every `j $31` but the last
                                 one of the function branches to the last one, which becomes `jr ra; nop` (its
                                 delay-slot insn, if any, goes before it); gcc 2.8.1 emits a `j $31` per return
                                 path (leaf functions: memmove, strcmp, ...); with jump threading over the
                                 shared return (tools/sonyret.py). Runs after EPILOGUE sony.
    // RETURN sony first         the same, and an early `return K;` block that gcc moved to the end goes back
                                 after its branch, as in the C (`if (bad) return -1;` in libsnd)
"""
import os, re, subprocess, sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
OLDGCC = "/opt/oldgcc"
DEFAULT = {"cc": "gcc-2.8.1-psx", "flags": "-O2 -G0", "aspsx": "2.79", "as": "maspsx", "epilogue": "", "return": ""}
AS = ["mipsel-linux-gnu-as", "-EL", "-march=r3000", "-mtune=r3000", "-no-pad-sections", "-G0"]


def options(src, override=None):
    o = dict(DEFAULT)
    head = open(src, errors="replace").read(800)
    for k, key in (("CC", "cc"), ("FLAGS", "flags"), ("ASPSX", "aspsx"), ("AS", "as"), ("EPILOGUE", "epilogue"),
                   ("RETURN", "return")):
        m = re.search(r"^//\s*%s\s+(.+?)\s*$" % k, head, re.M)
        if m:
            o[key] = m.group(1)
    o.update(override or {})
    return o


class CompileError(Exception):
    pass


EPI = re.compile(r"((?:\tlw\t\$\d+,\d+\(\$sp\)\n)+)((?:\t(?!lw\t|#|\.)[^\n]*\n)?)(?:\t#nop\n)?"
                 r"\t\.set\tnoreorder\n\t\.set\tnomacro\n\tj\t\$31\n\t(addu\t\$sp,\$sp,\d+)\n\t\.set\tmacro\n"
                 r"\t\.set\treorder\n")


def sony_epilogue(s):
    """cc1 output -> the epilogue Sony's library compiler gave (// EPILOGUE sony)."""
    def rep(m):
        rest, insn, addu = m.group(1), m.group(2), m.group(3)
        last = rest.rstrip("\n").split("\n")[-1]
        if "$31," in last:
            return insn + rest + "\t" + addu + "\n\t.set\tnoreorder\n\tj\t$31\n\tnop\n\t.set\treorder\n"
        return (insn + rest + "\t.set\tnoreorder\n\t.set\tnomacro\n\tj\t$31\n\t" + addu +
                "\n\t.set\tmacro\n\t.set\treorder\n")
    return EPI.sub(rep, s)


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
    if o["epilogue"] == "sony":
        s = sony_epilogue(s)
    if o["return"].split()[:1] == ["sony"]:
        import sonyret
        s = sonyret.sony_return(s, o["return"] == "sony first")
    if o["as"] == "gnu":
        s = re.sub(r"(?m)^\tmove\t(\$[0-9a-z]+),(\$[0-9a-z]+)", r"\taddu\t\1,\2,$0", s)
        s = re.sub(r"(?m)^\t\.rdata$", "\t.section .rodata", s)
        open(base + ".mas.s", "w").write(asm_filter(s) if asm_filter else s)   # jump tables (tools/jtbl.py) too

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

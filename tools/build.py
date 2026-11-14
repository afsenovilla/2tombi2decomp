#!/usr/bin/env python3
"""All-asm / mixed matching build of the Tomba! 2 programs, checked against the retail files.

For each config/<prog>.yaml: splat split (asm/<prog>, build/<prog>.ld), assemble every .s with mipsel binutils, link,
objcopy to a flat binary and compare its sha1 with the yaml's sha1 (the retail file). A PS-X EXE gets its 0x800-byte
header from the header segment, so the whole file is compared.

  python3 tools/build.py [prog ...] [--no-split] [-j N] [--version eu]

Output under build/ (git-ignored). Exit status 1 if any program does not match.
"""
import argparse, concurrent.futures as cf, glob, hashlib, os, re, subprocess, sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
AS = ["mipsel-linux-gnu-as", "-EL", "-march=r3000", "-mtune=r3000", "-no-pad-sections", "-G0", "-Iinclude"]
LD = "mipsel-linux-gnu-ld"
OBJCOPY = "mipsel-linux-gnu-objcopy"


def run(cmd):
    r = subprocess.run(cmd, cwd=ROOT, capture_output=True, text=True)
    if r.returncode:
        sys.exit("FAILED: %s\n%s%s" % (" ".join(cmd), r.stdout, r.stderr))
    return r.stdout


GTE_LINE = re.compile(r"^(\s*/\* \w+ \w+ ([0-9A-F]{8}) \*/\s+)(\w+)\b.*$")
GTE_OPS = {"rtps", "rtpt", "nclip", "op", "dpcs", "intpl", "mvmva", "ncds", "cdp", "ncdt", "nccs", "cc", "ncs", "nct",
           "sqr", "dcpl", "dpct", "avsz3", "avsz4", "ncct", "gpf", "gpl"}


def fix_gte(path):
    """A GTE op whose word has different flag bits than splat's macro (e.g. avsz4 with sf=0) is emitted as .word."""
    txt = open(path).read().split("\n")
    changed = False
    for i, l in enumerate(txt):
        m = GTE_LINE.match(l)
        if m and m.group(3) in GTE_OPS:
            w = m.group(2)
            txt[i] = "%s.word 0x%s%s%s%s /* %s */" % (m.group(1), w[6:8], w[4:6], w[2:4], w[0:2], m.group(3))
            changed = True
    if changed:
        open(path, "w").write("\n".join(txt))


import cc as CCMOD   # the compiler pipeline (per-file // CC, // FLAGS, // ASPSX, // AS headers)


SEG_SIZE = {}   # src path -> retail size of its c subsegment (library files are padded to it)


def compile_c(src, obj):
    try:
        pad = SEG_SIZE.get(src) if "/psyq/" in src else None
        CCMOD.compile_c(os.path.join(ROOT, src), os.path.join(ROOT, obj), pad_to=pad)
    except CCMOD.CompileError as e:
        sys.exit("FAILED: %s" % e)


def objects(ld):
    return sorted(set(re.findall(r"(build/\S+?\.o)\(", open(os.path.join(ROOT, ld)).read())))


def build(prog, split, jobs, cfg="config"):
    y = open(os.path.join(ROOT, cfg, prog + ".yaml")).read()
    sha = re.search(r"^sha1:\s*(\w+)", y, re.M).group(1)
    ld = re.search(r"ld_script_path:\s*(\S+)", y).group(1)
    target = re.search(r"target_path:\s*(\S+)", y).group(1)
    if split:   # a clean split: renamed / re-split functions must not leave stale nonmatchings files behind
        apath = re.search(r"asm_path:\s*(\S+)", y).group(1)
        subprocess.run(["rm", "-rf", os.path.join(ROOT, apath)])
        run([sys.executable, "-m", "splat", "split", "%s/%s.yaml" % (cfg, prog)])
        if not cfg.endswith("eu") and os.path.exists(os.path.join(ROOT, "src", prog, prog + ".c")):
            if run([sys.executable, "-I", "tools/sync_src.py", "--prog", prog]).startswith("changed"):
                subprocess.run(["rm", "-rf", os.path.join(ROOT, apath)])
                run([sys.executable, "-m", "splat", "split", "%s/%s.yaml" % (cfg, prog)])
    bdir = re.search(r"build_path:\s*(\S+)", y).group(1)
    srcp = re.search(r"src_path:\s*(\S+)", y).group(1)
    subs = re.findall(r"(?m)^\s+- \[(0x\w+), (\w+)(?:, ([\w/]+))?\]", y)
    for (o1, t1, n1), (o2, _, _) in zip(subs, subs[1:]):
        if t1 == "c":
            SEG_SIZE["%s/%s.c" % (srcp, n1)] = int(o2, 16) - int(o1, 16)
    objs = objects(ld)

    def assemble(o):
        src = o[len(bdir) + 1:-2]
        os.makedirs(os.path.dirname(os.path.join(ROOT, o)), exist_ok=True)
        if src.endswith(".s"):
            fix_gte(os.path.join(ROOT, src))
            run(AS + ["-o", o, src])
        elif src.endswith(".c"):
            compile_c(src, o)
        elif src.endswith(".bin"):
            run(["mipsel-linux-gnu-ld", "-r", "-b", "binary", "-o", o, src])
        else:
            sys.exit("no rule for %s" % src)

    if split:   # splat writes nonmatchings/*.s with the same GTE macros: emit those as .word too
        for f in glob.glob(os.path.join(ROOT, "asm", "**", "nonmatchings", "**", "*.s"), recursive=True):
            fix_gte(f)
    with cf.ThreadPoolExecutor(jobs) as ex:
        list(ex.map(assemble, objs))
    elf = "%s/%s.elf" % (bdir, prog)
    extra = []
    al = os.path.join(cfg, "aliases_%s.ld" % prog)   # names library C from other projects uses (tools/libsweep.py)
    if os.path.exists(os.path.join(ROOT, al)):
        extra += ["-T", al]
    for k in ("undefined_syms_auto_path", "undefined_funcs_auto_path"):
        m = re.search(k + r":\s*(\S+)", y)
        if m and os.path.exists(os.path.join(ROOT, m.group(1))):
            extra += ["-T", m.group(1)]
    run([LD, "-EL", "-o", elf, "-T", ld, "-T", "config/undefined_syms.ld", "-T", "config/scratchpad.ld"] + extra + [ "--no-check-sections", "-nostdlib",
         "-Map", "%s/%s.map" % (bdir, prog)])
    out = "%s/%s.bin" % (bdir, prog)
    run([OBJCOPY, "-O", "binary", elf, out])
    data = open(os.path.join(ROOT, out), "rb").read()
    end = int(re.findall(r"^  - \[(0x[0-9A-Fa-f]+)\]\s*$", y, re.M)[-1], 16)
    if len(data) > end and not data[end:].strip(b"\0"):   # the link pads the last section to 4 bytes
        data = data[:end]
        open(os.path.join(ROOT, out), "wb").write(data)
    got = hashlib.sha1(data).hexdigest()
    ok = got == sha
    print("%-8s %s  %s (%s)" % (prog, "OK  " if ok else "DIFF", out, target))
    return ok


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("progs", nargs="*")
    ap.add_argument("--no-split", action="store_true")
    ap.add_argument("-j", type=int, default=os.cpu_count())
    ap.add_argument("--version", default="", help="eu: the configs of config/eu (USA, the reference, by default)")
    a = ap.parse_args()
    cfg = os.path.join("config", a.version) if a.version else "config"
    progs = a.progs or sorted(os.path.basename(p)[:-5] for p in glob.glob(os.path.join(ROOT, cfg, "*.yaml")))
    bad = [p for p in progs if not build(p, not a.no_split, a.j, cfg)]
    sys.exit(1 if bad else 0)


if __name__ == "__main__":
    main()

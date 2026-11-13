#!/usr/bin/env python3
"""All-asm / mixed matching build of the Tomba! 2 programs, checked against the retail files.

For each config/<prog>.yaml: splat split (asm/<prog>, build/<prog>.ld), assemble every .s with mipsel binutils, link,
objcopy to a flat binary and compare its sha1 with the yaml's sha1 (the retail file). A PS-X EXE gets its 0x800-byte
header from the header segment, so the whole file is compared.

  python3 tools/build.py [prog ...] [--no-split] [-j N]

Output under build/ (git-ignored). Exit status 1 if any program does not match.
"""
import argparse, concurrent.futures as cf, glob, hashlib, os, re, subprocess, sys

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


def objects(ld):
    return sorted(set(re.findall(r"(build/\S+?\.o)\(", open(os.path.join(ROOT, ld)).read())))


def build(prog, split, jobs):
    y = open(os.path.join(ROOT, "config", prog + ".yaml")).read()
    sha = re.search(r"^sha1:\s*(\w+)", y, re.M).group(1)
    ld = re.search(r"ld_script_path:\s*(\S+)", y).group(1)
    target = re.search(r"target_path:\s*(\S+)", y).group(1)
    if split:
        run([sys.executable, "-m", "splat", "split", "config/%s.yaml" % prog])
    objs = objects(ld)

    def assemble(o):
        src = o[len("build/"):-2]
        os.makedirs(os.path.dirname(os.path.join(ROOT, o)), exist_ok=True)
        if src.endswith(".s"):
            fix_gte(os.path.join(ROOT, src))
            run(AS + ["-o", o, src])
        elif src.endswith(".bin"):
            run(["mipsel-linux-gnu-ld", "-r", "-b", "binary", "-o", o, src])
        else:
            sys.exit("no rule for %s" % src)

    with cf.ThreadPoolExecutor(jobs) as ex:
        list(ex.map(assemble, objs))
    elf = "build/%s.elf" % prog
    extra = []
    for k in ("undefined_syms_auto_path", "undefined_funcs_auto_path"):
        m = re.search(k + r":\s*(\S+)", y)
        if m and os.path.exists(os.path.join(ROOT, m.group(1))):
            extra += ["-T", m.group(1)]
    run([LD, "-EL", "-o", elf, "-T", ld, "-T", "config/undefined_syms.ld"] + extra + [ "--no-check-sections", "-nostdlib",
         "-Map", "build/%s.map" % prog])
    out = "build/%s.bin" % prog
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
    a = ap.parse_args()
    progs = a.progs or sorted(os.path.basename(p)[:-5] for p in glob.glob(os.path.join(ROOT, "config", "*.yaml")))
    bad = [p for p in progs if not build(p, not a.no_split, a.j)]
    sys.exit(1 if bad else 0)


if __name__ == "__main__":
    main()

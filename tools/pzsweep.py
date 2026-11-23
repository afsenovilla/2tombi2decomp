#!/usr/bin/env python3
"""Library C from psyz and psy-q-decomp against every pending library function (whole files, all set-ups).

  python3 -I tools/pzsweep.py [--prog main,boot] [--src psyz,sz] [--files SUBSTR,...] [--all-files]
      [--all-variants] [--loop] [--cc CC,...] [--max-off 8] [-j N] [--install] [--out build/pzsweep]

Sources (MIT, cloned by tools/setup_native.sh; AGENTS.md "Compilers"):
  psyz          /opt/psyz/decomp/src (Psy-Q 4.0), headers /opt/psyz/decomp/include + the 4.0 SDK headers
                /opt/psyz_inc/og (setup_native.sh makes them from psyz's psyq400.tar.gz);
  sz            /opt/psy-q-decomp/src with -DVERSION=40, headers /opt/psy-q-decomp/include(/psxsdk) + src.
Every .c file of a library the project has (src/*/psyq/<lib>; --all-files: every file) is preprocessed as a whole (-DPERMUTER: its INCLUDE_ASM functions drop out)
and compiled under the library set-ups (tools/libsweep.py VARIANTS + the nocse and Sony-epilogue ones;
--all-variants: all of them; --loop adds the loop-hoisting compilers, --cc keeps only the named compilers), and every function of the object is compared, relocated fields masked, with every
pending library function of main / boot (src/<prog>/psyq/*/NAME.c still INCLUDE_ASM) of the same size, whatever
its name: unnamed statics and functions the sources call by another name are found too. A file is skipped when
no function of it comes within 25 % of a pending size under the first two set-ups.

A function with no word off is cut into a standalone scratch (the file's types, declarations and inline helpers,
the other functions as prototypes, globals as externs, the function renamed to the project's name, string
literals turned into the retail D_ symbols), checked again alone, and written to <out>/<prog>/<name>.c with its
set-up header and a `// Source:` line; --install installs it with tools/install_lib.py (the Source line is kept).
The closest attempt of every other pending function within --max-off words (and a fifth of its words; functions
of 0x20 bytes or more; the asm-by-design files are left out) is written to <out>/<prog>/near/ and listed (a start for hand matching: tools/ccheck.py --sbs, then the 4.0 -> 4.4 differences of AGENTS.md).
"""
import argparse, concurrent.futures as cf, glob, json, os, re, shutil, struct, subprocess, sys, tempfile, time

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))
import cc, libsweep as L, ptsrc

SOURCES = {
    "psyz": ("/opt/psyz/decomp/src", ["/opt/psyz/decomp/include", "/opt/psyz_inc/og", "/opt/psyz_inc"], [],
             "psyz (github.com/Xeeynamo/psyz, MIT) decomp/src"),
    "sz": ("/opt/psy-q-decomp/src", ["/opt/psy-q-decomp/include", "/opt/psy-q-decomp/include/psxsdk",
                                     "/opt/psy-q-decomp/src", "/opt/psy-q-decomp/src/snd"], ["VERSION=40"],
           "psy-q-decomp (github.com/sozud/psy-q-decomp, MIT) src"),
}
COMMON = {"u8", "s8", "u16", "s16", "u32", "s32"}


def variants(full, loop=False, ccs=None):
    """The set-ups tried. loop: also the loop-hoisting compilers (libsweep LOOP_VARIANTS; with full all of them,
    else those without Sony's return). ccs: only these compilers; a compiler no set-up names takes the set-ups of
    its stock family (gcc-2.7.2-* those of gcc-2.7.2-psx, gcc-2.8.1-* those of gcc-2.8.1-psx / -nocse), so
    `--cc gcc-2.7.2-loop4` runs every 2.7.2 set-up with it."""
    seen, out = set(), []
    pool = L.VARIANTS + L.EPI_VARIANTS + L.NOCSE_VARIANTS if full else \
        L.VARIANTS + [v for v in L.EPI_VARIANTS if v.get("epilogue") == "sony" and "return" not in v] + \
        [v for v in L.NOCSE_VARIANTS if "return" not in v and "epilogue" not in v]
    if loop:
        pool = pool + [v for v in L.LOOP_VARIANTS if full or "return" not in v]
    if ccs:
        allp = L.VARIANTS + L.EPI_VARIANTS + L.NOCSE_VARIANTS + L.LOOP_VARIANTS
        named = {v["cc"] for v in allp}
        sel = []
        for c in ccs:
            if c in named:
                sel += [v for v in (allp if full else pool + [v for v in L.LOOP_VARIANTS if "return" not in v])
                        if v["cc"] == c]
            else:
                fam = "gcc-2.7.2" if c.startswith("gcc-2.7.2") or "272" in c else "gcc-2.8.1"
                sel += [dict(v, cc=c) for v in pool if v["cc"].startswith(fam)]
        pool = sel
    for v in pool:
        k = json.dumps(v, sort_keys=True)
        if k not in seen:
            seen.add(k)
            out.append(v)
    return out


def over(v):
    return dict(v, epilogue=v.get("epilogue", ""), **{"return": v.get("return", "")})


def preprocess(f, inc, defs, out):
    cmd = ["cpp", "-undef", "-P", "-nostdinc", "-w", "-D__GNUC__=2", "-DPERMUTER", "-Dmips", "-D__OPTIMIZE__", "-D__mips__",
           "-Dpsx", "-D__psx__", "-D__psx", "-D_PSYQ", "-D__EXTENSIONS__", "-D_MIPSEL", "-DMIPSEL", "-D_LANGUAGE_C",
           "-DLANGUAGE_C", "-DWEAK_INCLUDE_ASM(F,N)=", "-DINCLUDE_RODATA(F,N)=", "-I" + os.path.dirname(f)] + ["-I" + i for i in inc] + ["-D" + d for d in defs] + [f, out]
    return subprocess.run(cmd, capture_output=True, text=True).returncode == 0


def obj_funcs(obj):
    """(text, relocated offsets, {name: (offset, size)}) of an object's .text."""
    subprocess.run(["mipsel-linux-gnu-objcopy", "-O", "binary", "-j", ".text", obj, obj + ".bin"], check=True)
    text = open(obj + ".bin", "rb").read() if os.path.exists(obj + ".bin") else b""
    rel = set()
    for l in subprocess.run(["mipsel-linux-gnu-objdump", "-r", "-j", ".text", obj], capture_output=True,
                            text=True).stdout.splitlines():
        m = re.match(r"([0-9a-f]{8})\s+R_MIPS_", l)
        if m:
            rel.add(int(m.group(1), 16))
    out = {}
    for l in subprocess.run(["mipsel-linux-gnu-nm", "-S", "--defined-only", obj], capture_output=True,
                            text=True).stdout.splitlines():
        p = l.split()
        if len(p) == 4 and p[2] in "Tt":
            out[p[3]] = (int(p[0], 16), int(p[1], 16))
    return text, rel, out


def words_off(text, rel, off, want):
    n = 0
    for i in range(0, len(want), 4):
        g = struct.unpack("<I", text[off + i:off + i + 4])[0]
        w = struct.unpack("<I", want[i:i + 4])[0]
        if off + i in rel:
            mk = 0xFC000000 if g >> 26 in (2, 3) else 0xFFFF0000
            g, w = g & mk, w & mk
        n += g != w
    return n


def pending(progs):
    """[(prog, lib, name, retail bytes)] of the pending library functions."""
    out = []
    for prog in progs:
        binary, delta = L.prog_bytes(prog)
        for name, f in sorted(L.pending_files(prog).items()):
            if "// ASM by design: " in open(f).read():
                continue                                # BIOS stubs, syscall wrappers: assembly in Sony's source
            try:
                addr, size = L.asm_info(prog, name)
            except SystemExit:
                continue
            if addr and size:
                out.append((prog, os.path.basename(os.path.dirname(f)), name, binary[addr - delta: addr - delta + size]))
    return out


def libs_of_project():
    return {os.path.basename(d).lower().replace("lib", "") for d in glob.glob(os.path.join(ROOT, "src", "*", "psyq", "*"))}


def source_files(srcs, all_files, only):
    libs = libs_of_project()
    out = []
    for s in srcs:
        root, inc, defs, note = SOURCES[s]
        for f in sorted(glob.glob(os.path.join(root, "**", "*.c"), recursive=True)):
            rel = os.path.relpath(f, root)
            if only and not any(o in rel for o in only):
                continue
            parts = [p.lower().replace("lib", "") for p in rel.split(os.sep)[:-1]]
            if all_files or any(p in libs for p in parts):
                out.append((s, f))
    return out


def sweep_file(job):
    """compile one source file under every set-up -> [(words off, prog, name, src fn, file, variant index)]."""
    s, f, pend, vs, max_off, work = job
    root, inc, defs, note = SOURCES[s]
    d = tempfile.mkdtemp(dir=work)
    res = []
    try:
        src = os.path.join(d, "x.c")
        if not preprocess(f, inc, defs, src):
            return res, "cpp failed"
        sizes = {len(p[3]) for p in pend}
        bysize = {}
        for p in pend:
            bysize.setdefault(len(p[3]), []).append(p)
        ok, err = 0, ""
        for vi, v in enumerate(vs):
            try:
                cc.compile_c(src, os.path.join(d, "x.o"), over(v))
            except cc.CompileError as e:
                err = err or (str(e).strip().splitlines() or [""])[-1][:160]
                if vi >= 3 and not ok:
                    break                               # neither compiler takes the file
                continue
            ok += 1
            text, rel, fs = obj_funcs(os.path.join(d, "x.o"))
            if ok == 2 and not any(any(0.8 * sz <= ln <= 1.25 * sz for sz in sizes) for _, ln in fs.values()):
                return res, "no function near a pending size"
            for fn, (off, size) in fs.items():
                for p in bysize.get(size, ()):
                    n = words_off(text, rel, off, p[3])
                    # a near miss: at most --max-off words and a fifth of the function (tiny functions of 4-6
                    # words come close to anything)
                    if n == 0 or n <= max_off and size >= 0x20 and n * 5 <= size // 4:
                        res.append((n, p[0], p[2], fn, f, vi))
        return res, "ok" if ok else "cc failed: " + err
    finally:
        shutil.rmtree(d, ignore_errors=True)


def split_multi(s):
    m = re.match(r"((?:extern\s+)?(?:[A-Za-z_]\w*\s+)+?)((?:\*\s*)*[A-Za-z_]\w*(?:\[[^\]]*\])*(?:\s*,\s*(?:\*\s*)*"
                 r"[A-Za-z_]\w*(?:\[[^\]]*\])*)+)\s*;$", s, re.S)
    if not m or "(" in s or "{" in s:
        return [s]
    return [m.group(1) + x.strip() + ";" for x in m.group(2).split(",")]


def cut(prog, our, f, fn, v, srcs_key, d):
    """standalone scratch text of fn from source file f renamed `our` (None when it does not match alone)."""
    root, inc, defs, note = SOURCES[srcs_key]
    ipath = os.path.join(d, "cut.i")
    if not preprocess(f, inc, defs, ipath):
        return None
    t = open(ipath).read()
    parts = []
    for kind, seg in ptsrc.items(ptsrc.strip_comments(t)):
        s = seg.strip()
        if not s or kind == "pp":
            continue
        if s.endswith("}") and ptsrc.func_name(s):
            n = ptsrc.func_name(s)
            if n == fn:
                parts.append(re.sub(r"^\s*static\s+", "", s))
            elif re.match(r"\s*(static\s+)?(extern\s+)?inline\b|\s*static\s+inline\b", s):
                parts.append(s)
            else:
                parts.append(re.sub(r"^\s*(static\s+|inline\s+)+", "", s[:s.find("{")]).strip() + ";")
            continue
        m = re.match(r"typedef\s+(?:signed|unsigned)\s+(?:char|short|int)\s+(\w+)\s*;$", s)
        if m and m.group(1) in COMMON or s.startswith("__asm__"):
            continue
        if re.match(r"(typedef|extern)\b", s) or re.match(r"(struct|union|enum)\s+\w*\s*\{", s) and s.endswith("};"):
            parts.append(s)
            continue
        if re.search(r"\)\s*;$", s) and "=" not in s:
            parts.append(re.sub(r"^\s*(static\s+|inline\s+)+", "", s))
            continue
        dd, depth, at = s[:-1], 0, None
        for k, ch in enumerate(dd):
            if ch in "({[":
                depth += 1
            elif ch in ")}]":
                depth -= 1
            elif ch == "=" and depth == 0:
                at = k
                break
        if at is not None:
            init, dd = dd[at + 1:].strip(), dd[:at]
            if re.search(r"\[\s*\]\s*$", dd) and init.startswith("{"):
                inner, depth2, n = init[1:init.rfind("}")], 0, 1
                for ch in inner:
                    if ch in "({[":
                        depth2 += 1
                    elif ch in ")}]":
                        depth2 -= 1
                    elif ch == "," and depth2 == 0:
                        n += 1
                n -= inner.strip().endswith(",")
                dd = re.sub(r"\[\s*\]\s*$", "[%d]" % n, dd)
            elif re.search(r"\[\s*\]\s*$", dd) and init.startswith('"'):
                dd = re.sub(r"\[\s*\]\s*$", "[%d]" % (len(eval(init)) + 1), dd)
        parts.append("extern " + re.sub(r"^\s*static\s+", "", dd).strip() + ";")
    parts = [x for s in parts for x in split_multi(s)]
    text = '#include "common.h"\n' + "\n".join(parts) + "\n"
    if our != fn:
        text = re.sub(r'"(?:[^"\\\n]|\\.)*"|\b%s\b' % re.escape(fn),
                      lambda m: m.group(0) if m.group(0).startswith('"') else our, text)
    binary, delta = L.prog_bytes(prog)
    addr, size = L.asm_info(prog, our)
    want = binary[addr - delta: addr - delta + size]
    src = os.path.join(d, our + ".c")
    open(src, "w").write(text)
    try:
        cc.compile_c(src, os.path.join(d, "a.o"), over(v))
    except cc.CompileError:
        return None
    syms = {}
    if not L.matches(os.path.join(d, "a.o"), our, want, syms):
        return None
    ro = L.rodata(os.path.join(d, "a.o"))
    if ro.strip(b"\0") and ".rodata" in syms:
        t2 = L.strings_to_symbols(text, ro, syms[".rodata"])
        if t2 is None:
            return None
        lines = t2.split("\n")
        ex = [l for l in lines if re.match(r"extern char D_[0-9A-F]{8}\[\];$", l)]
        rest = [l for l in lines if l not in ex]
        body = "\n".join(rest)
        for k, l in enumerate(ex):
            nm = re.search(r"D_[0-9A-F]{8}", l).group(0)
            if re.search(r"__builtin_\w+\([^;]*\b%s\b" % nm, body):
                ex[k] = "extern s32 %s[];" % nm            # copied by __builtin_memcpy: word loads
        i = rest.index('#include "common.h"')
        rest[i + 1:i + 1] = ex
        text = "\n".join(rest)
    rel = os.path.relpath(f, SOURCES[srcs_key][0])
    return L.header(v) + "// Source: %s/%s, function %s.\n" % (note, rel, fn) + text


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--prog", default="main,boot")
    ap.add_argument("--src", default="psyz,sz")
    ap.add_argument("--files", default="", help="only source files whose path has one of these substrings")
    ap.add_argument("--all-files", action="store_true")
    ap.add_argument("--all-variants", action="store_true")
    ap.add_argument("--loop", action="store_true", help="also the loop-hoisting compilers (gcc-2.7.2-loop4, ...)")
    ap.add_argument("--cc", help="comma list: only these compilers (an /opt/oldgcc name or a path; one no set-up "
                    "names takes the set-ups of its stock family)")
    ap.add_argument("--max-off", type=int, default=8)
    ap.add_argument("-j", type=int, default=os.cpu_count())
    ap.add_argument("--install", action="store_true")
    ap.add_argument("--out", default=os.path.join(ROOT, "build", "pzsweep"))
    a = ap.parse_args()
    progs = a.prog.split(",")
    srcs = [s for s in a.src.split(",") if os.path.isdir(SOURCES[s][0])]
    if not os.path.exists("/opt/psyz_inc/og/libgpu.h") and "psyz" in srcs:
        print("note: /opt/psyz_inc/og missing (bash tools/setup_native.sh makes it): psyz files may not preprocess")
    pend = pending(progs)
    vs = variants(a.all_variants, a.loop, a.cc.split(",") if a.cc else None)
    files = source_files(srcs, a.all_files, [x for x in a.files.split(",") if x])
    print("%d pending library functions (%s), %d source files, %d set-ups" % (len(pend), ",".join(progs),
                                                                              len(files), len(vs)), flush=True)
    work = tempfile.mkdtemp(prefix="tmp_pzsweep_", dir=os.path.join(ROOT, "build"))
    best = {}
    whys = {}
    t0 = time.time()
    try:
        with cf.ThreadPoolExecutor(a.j) as ex:
            jobs = {ex.submit(sweep_file, (s, f, pend, vs, a.max_off, work)): (s, f) for s, f in files}
            for k, fut in enumerate(cf.as_completed(jobs)):
                s, f = jobs[fut]
                res, why = fut.result()
                whys.setdefault(why.split(":")[0], []).append(os.path.relpath(f, "/opt"))
                for n, prog, name, fn, src, vi in res:
                    key = (prog, name)
                    if key not in best or n < best[key][0]:
                        best[key] = (n, fn, src, vi, s)
                        if n == 0:
                            print("  match: %s %s <- %s (%s) %s" % (prog, name, fn, os.path.relpath(src, "/opt"),
                                                                  L.header(vs[vi]).replace("\n", " ")), flush=True)
                if (k + 1) % 50 == 0:
                    print("  %d / %d files, %.0fs" % (k + 1, len(files), time.time() - t0), flush=True)
        print("files: " + ", ".join("%s %d" % (k, len(v)) for k, v in sorted(whys.items())))
        for k in ("cpp failed", "cc failed"):
            if whys.get(k):
                print("  %s: %s%s" % (k, " ".join(whys[k][:12]), " ..." if len(whys[k]) > 12 else ""))
        matched, near = [], []
        for (prog, name), (n, fn, src, vi, s) in sorted(best.items()):
            d = tempfile.mkdtemp(dir=work)
            try:
                text = cut(prog, name, src, fn, vs[vi], s, d) if n == 0 else None
            finally:
                shutil.rmtree(d, ignore_errors=True)
            if text:
                os.makedirs(os.path.join(a.out, prog), exist_ok=True)
                out = os.path.join(a.out, prog, name + ".c")
                open(out, "w").write(text)
                matched.append((prog, name, out))
            else:
                near.append((n, prog, name, fn, src, vi, s))
        print("%d matched (standalone checked), %d near (<= %d words off):" % (len(matched), len(near), a.max_off))
        for prog, name, out in matched:
            print("  %s %s: %s" % (prog, name, os.path.relpath(out, ROOT)))
        for n, prog, name, fn, src, vi, s in sorted(near):
            print("  near %s %s %d words off <- %s %s [%s]" % (prog, name, n, fn, os.path.relpath(src, "/opt"),
                                                             L.header(vs[vi]).replace("\n", " ").strip()))
            d = tempfile.mkdtemp(dir=work)
            try:
                os.makedirs(os.path.join(a.out, prog, "near"), exist_ok=True)
                # the near attempt: the whole file under its set-up, renamed (hand matching starts from here)
                txt = "// pzsweep: %d words off, %s from %s\n" % (n, fn, src) + L.header(vs[vi])
                pre = os.path.join(d, "n.i")
                if preprocess(src, SOURCES[s][1], SOURCES[s][2], pre):
                    open(os.path.join(a.out, prog, "near", name + ".i.c"), "w").write(txt + open(pre).read())
            finally:
                shutil.rmtree(d, ignore_errors=True)
        if a.install:
            for prog, name, out in matched:
                r = subprocess.run([sys.executable, "-I", os.path.join(ROOT, "tools", "install_lib.py"), out,
                                    "--prog", prog], capture_output=True, text=True, cwd=ROOT)
                last = (r.stdout + r.stderr).strip().splitlines()[-1:] or ["?"]
                print("  install %s %s: %s" % (prog, name, last[0]))
                if last[0].startswith("installed"):
                    keep_source_line(prog, name, open(out).read())
    finally:
        shutil.rmtree(work, ignore_errors=True)


def keep_source_line(prog, name, text):
    """the scratch's `// Source:` line in the installed file (after its set-up header) when install_lib dropped it."""
    m = re.search(r"(?m)^// Source: .*$", text)
    fs = glob.glob(os.path.join(ROOT, "src", prog, "psyq", "*", name + ".c"))
    if not m or not fs:
        return
    t = open(fs[0]).read()
    if "// Source:" in t:
        return
    ls = t.split("\n")
    i = 0
    while i < len(ls) and re.match(r"//\s*(CC|FLAGS|ASPSX|AS|EPILOGUE|RETURN)\s", ls[i]):
        i += 1
    ls.insert(i, m.group(0))
    open(fs[0], "w").write("\n".join(ls))


if __name__ == "__main__":
    main()

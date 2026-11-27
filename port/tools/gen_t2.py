#!/usr/bin/env python3
"""Generator of the native port (docs/PORT.md).  Adapted from Tombi-Decomp's port/tools/gen_port.py (same author,
MIT): the same two steps, rewritten for this repo's layout (one big src/<prog>/<prog>.c per program, the matching
build's ELF files in build/, the splat asm in asm/<prog>/).

  gen_t2.py sources OUTDIR PROG...     preprocess src/<prog>/*.c for the host, split them into top-level items,
                                       drop what the host cannot compile (functions with MIPS inline asm: they stay
                                       retail code and run in the MIPS interpreter), write OUTDIR/src/*.c and
                                       OUTDIR/sources.cmake
  gen_t2.py link OUTDIR NM OBJLIST     after compiling: resolve every undefined name against the matching build
                                       (OUTDIR/syms.ld: retail data -> its address; OUTDIR/thunks.S: code without
                                       native C -> a call thunk into the runtime), OUTDIR/funcmap.c (retail
                                       address -> native function, the Psy-Q address table with its policy)

Nothing here writes outside OUTDIR; src/ and the matching build are only read.
"""
import os
import re
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
PORT = os.path.join(ROOT, "port")
MIPS_NM = "mipsel-linux-gnu-nm"

# Psy-Q libraries whose code is plain CPU (+ GTE) work: interpreted when no shim exists.  Everything else in the
# library touches hardware (GPU / SPU / CD / SIO / DMA registers): a shim or a logged stub, never interpreted.
PURE_LIBS = {"libc", "libc2", "libgte", "libsn"}
PURE_GPU = re.compile(r"^(Set(Poly|Line|Sprt|Tile|Semi|Shade|DrawMode|DrawTPage|DrawArea|DrawOffset|DrawStp|"
                      r"DrawEnv|Texwindow|DrawMove|DrawLoad)\w*|Get(TPage|Clut)|AddPrim\w*|CatPrim|TermPrim|"
                      r"NextPrim|IsEndPrim|MargePrim|DumpTPage|DumpClut|SetDefDrawEnv|SetDefDispEnv|setRECT)$")


def run(cmd, **kw):
    return subprocess.run(cmd, check=True, stdout=subprocess.PIPE, universal_newlines=True, **kw).stdout


# ------------------------------------------------------------------------------------------------ retail symbols
def retail_syms(prog):
    """name -> address of every symbol of build/<prog>.elf (the matching build: aliases included)."""
    out = {}
    for line in run([MIPS_NM, os.path.join(ROOT, "build", prog + ".elf")]).splitlines():
        p = line.split()
        if len(p) != 3:
            continue
        a, t, n = p
        if n.endswith(".NON_MATCHING") or n.startswith("."):
            continue
        out.setdefault(n, int(a, 16))
    return out


def func_names(prog):
    """{name: (lib or None, pending)} for every function of the program (the splat asm files)."""
    out = {}
    for kind in ("matchings", "nonmatchings"):
        base = os.path.join(ROOT, "asm", prog, kind)
        for dp, _, fs in os.walk(base):
            rel = os.path.relpath(dp, base).split(os.sep)
            lib = rel[1] if len(rel) > 1 and rel[0] == "psyq" else None
            for f in fs:
                if f.endswith(".s"):
                    out[f[:-2]] = (lib, kind == "nonmatchings")
    return out


# ------------------------------------------------------------------------------------------------ C splitting
TOKEN = re.compile(r'"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'|[{}();=]|[A-Za-z_]\w*|\s+|.', re.S)


def split_items(text):
    """Top-level items of preprocessed C: ('func', name, header, body) or ('decl', text)."""
    items, cur, depth_b, depth_p = [], [], 0, 0
    toks = TOKEN.findall(text)
    i, n = 0, len(toks)
    while i < n:
        t = toks[i]
        cur.append(t)
        if t == "(":
            depth_p += 1
        elif t == ")":
            depth_p -= 1
        elif t == "{":
            if depth_b == 0 and depth_p == 0:
                # a function body when the last non-space token before it is ')' and no '=' at depth 0
                prev = [x for x in cur[:-1] if not x.isspace()]
                head = "".join(cur[:-1])
                is_func = prev and prev[-1] == ")" and "=" not in top_level(prev)
                if not is_func and prev:   # K&R definition: `f(a, b) int a; {`
                    is_func = prev[-1] == ";" and "(" in prev and "=" not in top_level(prev) and \
                        not re.match(r"\s*(typedef|struct|union|enum|extern)\b", head)
                if is_func:
                    j, d = i + 1, 1
                    while j < n and d:
                        if toks[j] == "{":
                            d += 1
                        elif toks[j] == "}":
                            d -= 1
                        j += 1
                    body = "".join(toks[i:j])
                    name = func_name(prev)
                    items.append(("func", name, head, body))
                    cur, i = [], j
                    continue
            depth_b += 1
        elif t == "}":
            depth_b -= 1
        elif t == ";" and depth_b == 0 and depth_p == 0:
            if not knr_continues(cur, toks, i):
                items.append(("decl", "".join(cur)))
                cur = []
        i += 1
    if "".join(cur).strip():
        items.append(("decl", "".join(cur)))
    return items


KNR_HEAD = re.compile(r"\b\w+\s*\(\s*([A-Za-z_]\w*(?:\s*,\s*[A-Za-z_]\w*)*)\s*\)\s*((?:[^;(){}]*;\s*)*)$")


def knr_continues(cur, toks, i):
    """At a ';' at depth 0: is this the parameter declarations of a K&R definition `f(a, b) T a; T b; {`?"""
    text = "".join(cur)
    m = KNR_HEAD.search(text)
    if not m or m.group(1).strip() == "void":
        return False
    look = []
    for t in toks[i + 1:]:
        if t == "{":
            break
        if t in ("(", ")", "=", "}"):
            return False
        look.append(t)
    else:
        return False
    decls = m.group(2) + "".join(look)
    if re.search(r"\b(extern|static|typedef|struct\s+\w+\s*\{)", decls):
        return False
    params = set(p.strip() for p in m.group(1).split(","))
    declared = set(re.findall(r"([A-Za-z_]\w*)\s*(?:\[[^\]]*\]\s*)*[;,]", decls))
    return declared <= params and params <= set(re.findall(r"[A-Za-z_]\w*", decls))


def top_level(toks):
    out, d = [], 0
    for t in toks:
        if t in "([":
            d += 1
        elif t in ")]":
            d -= 1
        elif d == 0:
            out.append(t)
    return out


def func_name(toks):
    """The identifier before the first '(' at depth 0 that is not '(*' (a function returning a pointer)."""
    for k, t in enumerate(toks):
        if t == "(" and k and re.match(r"[A-Za-z_]\w*$", toks[k - 1]) and toks[k - 1] not in ("__attribute__",):
            return toks[k - 1]
    return None


ASM_RE = re.compile(r"\b(__asm__|asm|__asm)\b")
DATA_NAME = re.compile(r"\b([A-Za-z_]\w*)\s*(?:\[[^\]]*\]\s*)*(?:=|;|,)")


def decl_names(text):
    """Names a top-level declaration defines (rough, enough for `T name[...] = {...};` and `T a, *b;`)."""
    s = re.sub(r"=\s*\{.*\}", "= 0", text, flags=re.S)       # drop brace initialisers
    s = re.sub(r'"(?:\\.|[^"\\])*"', '""', s)
    s = re.sub(r"=[^,;]*", "", s)                             # drop scalar initialisers
    s = re.sub(r"\([^()]*\)", "", s)
    names = []
    for part in s.rstrip().rstrip(";").split(","):
        m = re.search(r"([A-Za-z_]\w*)\s*(?:\[[^\]]*\]\s*)*$", part.strip())
        if m:
            names.append(m.group(1))
    return names


def to_extern(text):
    """`T name[N] = {...};` -> `extern T name[N];` (the one copy is the retail image's)."""
    s = re.sub(r"\s*=\s*\{.*\}\s*;\s*$", ";", text.strip(), flags=re.S)
    s = re.sub(r"\s*=\s*[^;]*;\s*$", ";", s, flags=re.S)
    s = re.sub(r"^\s*(static\s+)?", "", s)
    return "extern " + s



def emit(items, syms, funcs, rename, drop, native, arity=None, forwarded=None):
    out, spans, n_func, n_asm, n_ext = [], [], 0, 0, 0
    line = 2
    for k, it in enumerate(items):
        start = line
        piece = ""
        if it[0] == "func":
            _, name, head, body = it
            if ASM_RE.search(head + body) or name is None or k in drop:
                n_asm += k not in drop
                if name and not re.search(r"\bstatic\b", head) and name not in rename:
                    piece = prototype(head)             # the prototype: callers stay typed
            else:
                n_func += 1
                if name in funcs and not re.search(r"\bstatic\b", head):
                    native.append((name, syms.get(name)))
                if arity:
                    body = forward_short_calls(body, arity, forwarded if forwarded is not None else [])
                if name in rename:
                    h = re.sub(r"\b%s\b(?=\s*\()" % name, name + "__def", head, count=1)
                    piece = h + body + '\n__asm__(".globl %s\\n.set %s, %s__def");\n' % (name, name, name)
                else:
                    piece = head + body + "\n"
        else:
            txt = it[1]
            st = txt.strip()
            if ASM_RE.match(st):
                piece = ""
            elif re.match(r"(typedef|extern)\b", st) or "(" in st.split("=")[0] and "=" not in st:
                piece = txt
                fm = re.match(r"(?:extern\s+)?[^;{=]*?\b(\w+)\s*\([^;{]*\)\s*;$", st, re.S)
                if fm and fm.group(1) in rename and not st.startswith("typedef"):
                    piece = "\n" * txt.count("\n")       # a conflicting prototype: callers see an implicit int f()
            else:
                names = decl_names(st) if not re.match(r"(struct|union|enum)\b[^{]*\{[^}]*\}\s*;", st, re.S) else []
                if names and all(nm in syms for nm in names) and "{" not in st.split("=")[0]:
                    piece = "\n" + to_extern(st) + "\n"
                    n_ext += 1
                else:
                    piece = txt
        out.append(piece)
        line += piece.count("\n")
        spans.append((start, line))
    return out, spans, n_func, n_asm, n_ext, 0


def prototype(head):
    m = KNR_HEAD.search(head.rstrip())
    if m and m.group(1).strip() != "void" and m.group(2).strip():
        return head[:m.start(1)] + ");\n"   # K&R: `T f();`
    return head.rstrip() + ";\n"


def item_at(spans, line):
    for k, (a, b) in enumerate(spans):
        if a <= line <= b:
            return k
    return None


def host_errors(text, outdir):
    tmp = os.path.join(outdir, "check.c")
    open(tmp, "w").write(text)
    r = subprocess.run(["gcc", "-m32", "-fsyntax-only", "-w", "-std=gnu89", "-funsigned-char", "-ffreestanding",
                        "-fno-builtin", "-I" + os.path.join(PORT, "include"), tmp],
                       stdout=subprocess.PIPE, stderr=subprocess.STDOUT, universal_newlines=True,
                       env=dict(os.environ, LC_ALL="C"))
    errs = []
    for l in r.stdout.splitlines():
        m = re.match(r".*check\.c:(\d+):\d+: error: (.*)", l)
        if m:
            errs.append((int(m.group(1)), m.group(2)))
    return errs


# ------------------------------------------------------------------------------------------------ register-carried args
# A call with fewer arguments than the callee reads relied on $a0-$a3 still holding a value (T1 docs/PORT.md §2.1):
# on the host the missing ones are forwarded from the caller's own incoming arguments (PORT_ARG, port_prelude.h).
ASM_INS = re.compile(r"^\s*/\*\s*[0-9A-F]+ [0-9A-F]+ [0-9A-F]+ \*/\s+([a-z0-9.]+)\s*(.*)$")
ALL_READ = {"sw", "sh", "sb", "swl", "swr", "swc2", "beq", "bne", "beqz", "bnez", "bgez", "bltz", "blez", "bgtz",
            "jr", "jalr", "mult", "multu", "div", "divu", "mtc2", "ctc2", "mthi", "mtlo", "bgezal", "bltzal"}


def asm_arity(path):
    """1 + the highest $a register the function reads before writing it (linear scan; a call clobbers all)."""
    written, used = set(), set()
    for line in open(path):
        m = ASM_INS.match(line)
        if not m:
            continue
        op, args = m.group(1), m.group(2).split("/*")[0]
        regs = re.findall(r"\$(a[0-3]|[a-z0-9]+)", args)
        if op in ("jal",):
            written |= {"a0", "a1", "a2", "a3"}
            continue
        if op in ALL_READ:
            reads, dst = regs, None
        else:
            dst, reads = (regs[0], regs[1:]) if regs else (None, [])
            if op in ("lw", "lh", "lhu", "lb", "lbu", "lwl", "lwr", "mfc2", "cfc2", "lwc2"):
                reads = regs[1:] if op not in ("lwl", "lwr") else regs
        for r in reads:
            if r in ("a0", "a1", "a2", "a3") and r not in written:
                used.add(r)
        if dst in ("a0", "a1", "a2", "a3") and op not in ("mtc2", "ctc2", "lwc2"):
            written.add(dst)
    return 1 + max((int(r[1]) for r in used), default=-1)


def c_arity(head):
    m = KNR_HEAD.search(head.rstrip())
    if m and m.group(1).strip() != "void" and m.group(2).strip():
        return len(m.group(1).split(","))
    i = head.rfind(")")
    j, d = i, 0
    while j >= 0:
        if head[j] == ")":
            d += 1
        elif head[j] == "(":
            d -= 1
            if d == 0:
                break
        j -= 1
    params = head[j + 1:i].strip()
    if not params or params == "void":
        return 0
    return len(top_split(params))


def top_split(s):
    out, d, cur = [], 0, ""
    for ch in s:
        if ch in "([{":
            d += 1
        elif ch in ")]}":
            d -= 1
        if ch == "," and d == 0:
            out.append(cur)
            cur = ""
        else:
            cur += ch
    if cur.strip():
        out.append(cur)
    return out


# a direct call, or one through a cast of the function (install_c.py writes `((s32 (*)())f)()` for callers whose
# argument count differs from the definition)
CALL_RE = re.compile(r"(?:\(\s*\([^;{}()]*\(\s*\*\s*\)\s*\([^()]*\)\s*\)\s*([A-Za-z_]\w*)\s*\)|\b([A-Za-z_]\w*))\s*\(")


def forward_short_calls(body, arity, fixed):
    """Append PORT_ARG(i) to the calls in body that pass fewer arguments than the callee reads."""
    out, i, n = [], 0, 0
    while True:
        m = CALL_RE.search(body, i)
        if not m:
            out.append(body[i:])
            break
        name = m.group(1) or m.group(2)
        if name not in arity or (m.start() > 0 and body[m.start() - 1] in ".>"):
            out.append(body[i:m.end()])
            i = m.end()
            continue
        j, d = m.end(), 1
        while j < len(body) and d:
            if body[j] == "(":
                d += 1
            elif body[j] == ")":
                d -= 1
            j += 1
        inner = body[m.end():j - 1]
        args = top_split(inner)
        need = arity[name]
        if len(args) < need:
            extra = ["PORT_ARG(%d)" % k for k in range(len(args), need)]
            inner = ", ".join([a.strip() for a in args] + extra)
            fixed.append(name)
            n += 1
        out.append(body[i:m.end()] + forward_short_calls(inner, arity, []) + ")")
        i = j
    return "".join(out)

# ------------------------------------------------------------------------------------------------ sources
HOST_CPP = ["gcc", "-m32", "-E", "-P", "-w", "-undef", "-D__GNUC__=2", "-DMIPSEL", "-D_LANGUAGE_C", "-DPORT", "-DSKIP_ASM",
            "-DINCLUDE_ASM(F,N)=", "-DINCLUDE_RODATA(F,N)=", "-D__i386__=0"]


def sources(outdir, progs):
    srcdir = os.path.join(outdir, "src")
    os.makedirs(srcdir, exist_ok=True)
    report, files, native = [], [], []
    for prog in progs:
        syms = retail_syms(prog)
        funcs = func_names(prog)
        cfiles = sorted(f for f in os.listdir(os.path.join(ROOT, "src", prog)) if f.endswith(".c"))
        for cf in cfiles:
            path = os.path.join(ROOT, "src", prog, cf)
            pre = run(HOST_CPP + ["-I" + os.path.join(ROOT, "include"), "-I" + os.path.join(ROOT, "include", "psyq"),
                                  path])
            items = split_items(pre)
            rename, drop = set(), set()
            arity = {}
            for dp, _, fs in os.walk(os.path.join(ROOT, "asm", prog)):   # every function, Psy-Q included
                if os.sep + "data" in dp:
                    continue
                for f in fs:
                    if f.endswith(".s"):
                        arity[f[:-2]] = asm_arity(os.path.join(dp, f))
            for it in items:
                if it[0] == "func" and it[1] and not re.search(r"\bstatic\b", it[2]):
                    arity[it[1]] = c_arity(it[2])
            # static helpers with inline asm cannot be compiled; neither can their callers (transitively)
            dead = {it[1] for it in items if it[0] == "func" and it[1] and ASM_RE.search(it[2] + it[3])
                    and re.search(r"\bstatic\b", it[2])}
            while True:
                more = {k for k, it in enumerate(items) if it[0] == "func" and k not in drop and dead and
                        re.search(r"\b(%s)\s*\(" % "|".join(map(re.escape, dead)), it[3])}
                if not more:
                    break
                drop |= more
                dead |= {items[k][1] for k in more if re.search(r"\bstatic\b", items[k][2])}
            n_static_dead = len(drop)
            for attempt in range(12):
                forwarded = []
                out, spans, n_func, n_asm, n_ext, n_err = emit(items, syms, funcs, rename, drop, native_tmp := [],
                                                               arity, forwarded)
                text = '#include "port_prelude.h"\n' + "".join(out)
                errs = host_errors(text, outdir)
                if not errs:
                    break
                for line, msg in errs:
                    m = re.search(r"conflicting types for '(\w+)'|too many arguments to function '(\w+)'", msg)
                    if m:
                        m = re.match(r"(\w+)", m.group(1) or m.group(2))
                    if m and m.group(1) not in rename:
                        rename.add(m.group(1))
                        continue
                    k = item_at(spans, line)
                    if k is not None and items[k][0] == "func":
                        drop.add(k)
                    else:
                        print("[gen_t2] %s:%d: %s" % (cf, line, msg))
            else:
                print("[gen_t2] %s: errors left after the fix-up passes" % cf)
            native.extend((prog, n, a) for n, a in native_tmp)
            dst = os.path.join(srcdir, prog + "_" + cf)
            if not os.path.exists(dst) or open(dst).read() != text:
                open(dst, "w").write(text)
            files.append(dst)
            report.append("%s/%s: %d calls with register-carried arguments forwarded (PORT_ARG)" % (prog, cf, len(forwarded)))
            open(os.path.join(outdir, "forwarded_%s.txt" % prog), "w").write("\n".join(sorted(set(forwarded))) + "\n")
            report.append("%s/%s: %d native functions, %d left to the interpreter (inline asm), %d (host compile "
                          "errors), %d data definitions made extern, %d definitions renamed (conflicting earlier "
                          "declarations): %s" % (prog, cf, n_func, n_asm, len(drop), n_ext, len(rename),
                                                 " ".join(sorted(rename))))
            open(os.path.join(outdir, "dropped_%s.txt" % prog), "w").write(
                "\n".join(items[k][1] or "?" for k in sorted(drop)) + "\n")
    with open(os.path.join(outdir, "sources.cmake"), "w") as f:
        f.write("set(PORT_GAME_SOURCES\n%s)\n" % "".join("  %s\n" % p for p in files))
    with open(os.path.join(outdir, "native.txt"), "w") as f:
        for prog, name, addr in native:
            f.write("%s %s %s\n" % (prog, name, "%08X" % addr if addr is not None else "-"))
    with open(os.path.join(outdir, "sources_report.txt"), "w") as f:
        f.write("\n".join(report) + "\n")
    print("\n".join(report))


# ------------------------------------------------------------------------------------------------ link
def host_nm(nm, objs):
    defined, undef = {}, set()
    for o in objs:
        for line in run([nm, o]).splitlines():
            p = line.split()
            if len(p) == 2 and p[0] == "U":
                undef.add(p[1])
            elif len(p) == 3 and p[1] in "TDBRCVWtdbr":
                if p[1].isupper() or p[1] in "W":
                    defined.setdefault(p[2], (p[1], o))
    return defined, undef


ADDR_NAME = re.compile(r"^(?:func|D|jtbl|FUN|DAT|PTR)_([0-9A-Fa-f]{8})(?:_\w+)?$")


def link(outdir, nm, objlist):
    progs = ["main"]
    objs = [l.strip() for l in open(objlist) if l.strip()]
    defined, undef = host_nm(nm, objs)
    syms = retail_syms("main")
    funcs = func_names("main")
    by_addr_func = {}
    for name, (lib, pending) in funcs.items():
        if name in syms:
            by_addr_func.setdefault(syms[name], name)
    func_addrs = set(by_addr_func)
    shim_objs = {n for n, (t, o) in defined.items() if "/shims/" in o or "/runtime/" in o}

    ld, thunks, stubs, data_alias = [], [], [], 0
    for name in sorted(undef - set(defined)):
        if name.startswith("port_") or name in ("etext", "edata", "end") or name.startswith("__") and name not in syms:
            continue                       # runtime tables (funcmap.c), compiler helpers
        addr = syms.get(name)
        m = ADDR_NAME.match(name)
        if addr is None and m:
            addr = int(m.group(1), 16)
        if addr is None:
            stubs.append(name)
            thunks.append((name, 0))
            continue
        is_code = addr in func_addrs or (name.startswith("func_") and addr >= 0x80106228) or name in funcs
        if is_code:
            thunks.append((name, addr))
        else:
            ld.append("%s = 0x%08X;" % (name, addr))
            data_alias += 1
    # data the native C defines that is retail data: the retail image's copy wins
    overridden = 0
    for name, (t, o) in sorted(defined.items()):
        if t in "DBRC" and name in syms and "/shims/" not in o and "/runtime/" not in o and name not in funcs:
            ld.append("%s = 0x%08X;" % (name, syms[name]))
            overridden += 1
    with open(os.path.join(outdir, "syms.ld"), "w") as f:
        f.write("/* generated by port/tools/gen_t2.py link: retail data names -> their PS1 addresses */\n")
        f.write("\n".join(ld) + "\n")
    with open(os.path.join(outdir, "thunks.S"), "w") as f:
        f.write("/* generated by port/tools/gen_t2.py link: calls to code without native C -> runtime */\n")
        f.write(".text\n")
        for k, (name, addr) in enumerate(thunks):
            f.write('.globl %s\n%s:\n\tpushl $.Ln%d\n\tpushl $0x%08X\n\tcall port_resolve_call\n\taddl $8, %%esp\n'
                    '\tjmp *%%eax\n' % (name, name, k, addr))
        f.write(".section .rodata\n")
        for k, (name, addr) in enumerate(thunks):
            f.write('.Ln%d: .asciz "%s"\n' % (k, name))
    # funcmap: native functions by retail address; libmap: shims by retail address; libaddrs: policy
    native = []
    for line in open(os.path.join(outdir, "native.txt")):
        prog, name, a = line.split()
        if a != "-" and name in defined:
            native.append((int(a, 16), name))
    native.sort()
    lib = []
    for name, (l, pending) in funcs.items():
        if l and name in syms:
            a = syms[name]
            shim = name if name in shim_objs else None
            pure = l in PURE_LIBS or (l == "libgpu" and PURE_GPU.match(name))
            lib.append((a, name, l, shim, 1 if pure else 0))
    lib.sort()
    with open(os.path.join(outdir, "funcmap.c"), "w") as f:
        f.write('/* generated by port/tools/gen_t2.py link */\n#include "port_runtime.h"\n')
        for a, n in native:
            f.write("extern char %s[];\n" % n)
        for a, n, l, s, p in lib:
            if s:
                f.write("extern char %s[];\n" % s)
        f.write("const PortFunc port_funcmap[] = {\n")
        for a, n in native:
            f.write('  {0x%08X, %s, "%s"},\n' % (a, n, n))
        f.write("  {0, 0, 0}\n};\nconst int port_funcmap_count = %d;\n" % len(native))
        shims = [(a, n, s) for a, n, l, s, p in lib if s]
        f.write("const PortLib port_libmap[] = {\n")
        for a, n, s in shims:
            f.write('  {0x%08X, %s, "%s"},\n' % (a, s, n))
        f.write("  {0, 0, 0}\n};\nconst int port_libmap_count = %d;\n" % len(shims))
        f.write("const PortLibAddr port_libaddrs[] = {\n")
        for a, n, l, s, p in lib:
            f.write('  {0x%08X, %d, "%s", "%s"},\n' % (a, p, n, l))
        f.write("  {0, 0, 0, 0}\n};\nconst int port_libaddrs_count = %d;\n" % len(lib))
    rep = ["native functions with a retail address: %d" % len(native),
           "retail data names aliased: %d (+ %d native definitions overridden by the retail copy)" % (data_alias, overridden),
           "call thunks (code without native C): %d, of which %d unknown names (stubs)" % (len(thunks), len(stubs)),
           "Psy-Q functions: %d, shimmed %d, interpretable %d" % (len(lib), len(shims), sum(1 for x in lib if x[4] and not x[3])),
           "unknown names: " + " ".join(stubs)]
    with open(os.path.join(outdir, "link_report.txt"), "w") as f:
        f.write("\n".join(rep) + "\n")
    print("\n".join(rep[:4]))


if __name__ == "__main__":
    if sys.argv[1] == "sources":
        sources(sys.argv[2], sys.argv[3:])
    elif sys.argv[1] == "link":
        link(sys.argv[2], sys.argv[3], sys.argv[4])
    else:
        sys.exit(__doc__)

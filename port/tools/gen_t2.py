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
ASM_STMT = re.compile(r'\b(?:__asm__|__asm|asm)\s*(?:volatile|__volatile__)?\s*\(\s*((?:"(?:[^"\\]|\\.)*"\s*)*)'
                      r"((?::[^;]*?)?)\)\s*;")


def translate_asm(body):
    """MIPS inline asm in a function body (the GTE macros after cpp: `lhu $12, 0(%0); mtc2 $12, $9; ...`,
    `.word 0x4A180001`) -> C on the software GTE (runtime/gte.c) and a scratch register file; an empty asm
    statement (a scheduling barrier) -> nothing.  T1's translate_gte_define, applied to the expanded statements.
    Returns None when an instruction is outside the subset (the function stays retail code)."""
    def one(m):
        code = "".join(re.findall(r'"((?:[^"\\]|\\.)*)"', m.group(1))).replace("\\n", "\n").replace("\\t", " ")
        rest = m.group(2)
        secs = rest[1:].split(":") if rest.startswith(":") else []
        if len(secs) > 0 and secs[0].strip():
            raise ValueError("asm outputs")
        ins_ops = re.findall(r'"r"\s*\(((?:[^()]|\((?:[^()]|\([^()]*\))*\))*)\)', secs[1]) if len(secs) > 1 else []
        c = []

        def val(x):
            x = x.strip()
            if x.startswith("%"):
                return "(unsigned long)(%s)" % ins_ops[int(x[1:])]
            r = reg(x)
            return "0ul" if r == 0 else "_r[%d]" % r

        def reg(x):
            x = x.strip().lstrip("$")
            names = {"zero": 0, "at": 1, "v0": 2, "v1": 3, "a0": 4, "a1": 5, "a2": 6, "a3": 7, "t0": 8, "t1": 9,
                     "t2": 10, "t3": 11, "t4": 12, "t5": 13, "t6": 14, "t7": 15}
            return names[x] if x in names else int(x)

        def addr(x):
            q = re.match(r"(-?(?:0x[0-9A-Fa-f]+|\d+))?\(\s*(%\d+|\$\w+)\s*\)$", x.replace(" ", ""))
            if not q:
                raise ValueError("address " + x)
            return "((unsigned char *)%s + %s)" % (val(q.group(2)), q.group(1) or "0")

        for ins in re.split(r"[;\n]", code.replace("\t", " ")):
            ins = ins.strip()
            if not ins or ins == "nop":
                continue
            op, _, rest_ = ins.partition(" ")
            a = [x.strip() for x in rest_.split(",")] if rest_.strip() else []
            if op == ".word":
                c.append("port_gte_op(%s & 0x1FFFFFFu);" % a[0])
            elif op == "lwc2":
                c.append("port_gte_mtc2(%d, *(unsigned long *)%s);" % (reg(a[0]), addr(a[1])))
            elif op == "swc2":
                c.append("*(unsigned long *)%s = port_gte_mfc2(%d);" % (addr(a[1]), reg(a[0])))
            elif op == "mtc2":
                c.append("port_gte_mtc2(%d, %s);" % (reg(a[1]), val(a[0])))
            elif op == "ctc2":
                c.append("port_gte_ctc2(%d, %s);" % (reg(a[1]), val(a[0])))
            elif op == "mfc2":
                c.append("_r[%d] = port_gte_mfc2(%d);" % (reg(a[0]), reg(a[1])))
            elif op == "cfc2":
                c.append("_r[%d] = port_gte_cfc2(%d);" % (reg(a[0]), reg(a[1])))
            elif op in ("lw", "lhu", "lh", "lbu", "lb"):
                t = {"lw": "unsigned long", "lhu": "unsigned short", "lh": "short", "lbu": "unsigned char",
                     "lb": "signed char"}[op]
                c.append("_r[%d] = (unsigned long)(long)*(%s *)%s;" % (reg(a[0]), t, addr(a[1])))
            elif op in ("sw", "sh", "sb"):
                t = {"sw": "unsigned long", "sh": "unsigned short", "sb": "unsigned char"}[op]
                c.append("*(%s *)%s = (%s)%s;" % (t, addr(a[1]), t, val(a[0])))
            elif op in ("addiu", "addi"):
                c.append("_r[%d] = %s + (unsigned long)(%s);" % (reg(a[0]), val(a[1]), a[2]))
            elif op in ("addu", "add", "subu", "sub", "and", "or", "xor"):
                o = {"addu": "+", "add": "+", "subu": "-", "sub": "-", "and": "&", "or": "|", "xor": "^"}[op]
                c.append("_r[%d] = %s %s %s;" % (reg(a[0]), val(a[1]), o, val(a[2])))
            elif op in ("sra", "srl", "sll"):
                e = {"sra": "(unsigned long)((long)%s >> %s)", "srl": "%s >> %s", "sll": "%s << %s"}[op]
                c.append("_r[%d] = %s;" % (reg(a[0]), e % (val(a[1]), a[2])))
            elif op == "move":
                c.append("_r[%d] = %s;" % (reg(a[0]), val(a[1])))
            else:
                raise ValueError("instruction " + ins)
        if not c:
            return ";"
        used[0] = True
        return "{ " + " ".join(c) + " }"
    used = [False]
    try:
        out = ASM_STMT.sub(one, body)
    except (ValueError, IndexError, KeyError):
        return None
    if used[0]:   # one scratch register file per function (a macro may leave a value for the next one)
        k = out.index("{")
        out = out[:k + 1] + " unsigned long _r[32];" + out[k + 1:]
    return out

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



IDENT = re.compile(r"[A-Za-z_]\w*")


def retail_func_ptrs(text, addrs):
    """A game function named as a value (`*(void **)(b + 0x1C) = f_UpdateDetachedTrolleyActor;`,
    `if (*(void **)(a + 0x1C) == f_UpdatePlayerTrolleyActor)`) is its retail address, as in the retail image: actor
    update pointers set by the game's data and by C must compare equal, and a call through one reaches the native
    code through the SIGSEGV trampoline.  Calls, declarations (`name(`, `name[`) and members are left alone."""
    if not addrs:
        return text
    out, i = [], 0
    for m in IDENT.finditer(text):
        nm = m.group(0)
        if nm not in addrs:
            continue
        a, b = m.start(), m.end()
        j = b
        while j < len(text) and text[j] in " \t\n":
            j += 1
        if j < len(text) and text[j] in "([":
            continue
        if j < len(text) and text[j] == ")":      # `((T (*)())NAME)(...)`: a call through a cast stays direct
            j2 = j + 1
            while j2 < len(text) and text[j2] in " \t\n":
                j2 += 1
            if j2 < len(text) and text[j2] == "(":
                continue
        k = a - 1
        while k >= 0 and text[k] in " \t\n":
            k -= 1
        if k >= 0 and (text[k] == "." or text[k - 1:k + 1] == "->"):
            continue
        amp = k >= 0 and text[k] == "&" and not (k > 0 and text[k - 1] in "&")
        start = k if amp else a
        out.append(text[i:start])
        out.append("((void *)0x%08Xu)" % addrs[nm])
        i = b
    out.append(text[i:])
    return "".join(out)


# Ordering-table link stores (T1 gen_port.py port_kuseg_mask, "24-bit link"): the game links a primitive with
# `*o = (u32)p;`, `p` a KUSEG pointer on the console (its primitive buffer pointer D_800BF544 is kept masked with
# 0xFFFFFF).  The port hands native code the KSEG0 view of that pointer (runtime/mips_interp.c kcell), so it never
# touches 0x10000-0x1FFFFF (Windows has its own memory there); stored whole it would put 0x80 into the next tag's
# length byte, so the store keeps the 24-bit link the console stored.
KUSEG_LINK_STORE_RE = re.compile(r"^(\s*\*\s*(o|ot|ot\d|o\d)\s*=\s*)\(\s*(u32|s32|int|u_long|unsigned long|unsigned int)\s*\)\s*(\w+)\s*;", re.M)
KUSEG_LINK_STORES = [0]
def kuseg_link_stores(body):
    def sub(m):
        KUSEG_LINK_STORES[0] += 1
        return "%s((%s)%s & 0xFFFFFF); /* PORT: 24-bit link */" % (m.group(1), m.group(3), m.group(4))
    return KUSEG_LINK_STORE_RE.sub(sub, body)


def emit(items, syms, funcs, rename, drop, native, arity=None, forwarded=None, fptrs=None):
    out, spans, n_func, n_asm, n_ext = [], [], 0, 0, 0
    line = 2
    for k, it in enumerate(items):
        start = line
        piece = ""
        if it[0] == "func":
            _, name, head, body = it
            if ASM_RE.search(body) and not ASM_RE.search(head):
                t = translate_asm(body)
                if t is not None and not ASM_RE.search(t):
                    body = t
            if ASM_RE.search(head + body) or name is None or k in drop:
                n_asm += k not in drop
                if name and not re.search(r"\bstatic\b", head) and name not in rename:
                    piece = prototype(head)             # the prototype: callers stay typed
            else:
                n_func += 1
                if name in funcs and not re.search(r"\bstatic\b", head):
                    native.append((name, syms.get(name), ret_kind(head, name)))
                if arity:
                    body = forward_short_calls(body, arity, forwarded if forwarded is not None else [])
                    body = forward_indirect_calls(body, c_arity(head), forwarded if forwarded is not None else [])
                body = retail_func_ptrs(body, fptrs)
                body = kuseg_link_stores(body)
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
                elif "=" in txt:   # a table the C defines: its function pointers are retail addresses too
                    e = txt.index("=")
                    piece = txt[:e] + retail_func_ptrs(txt[e:], fptrs)
                else:
                    piece = txt
        out.append(piece)
        line += piece.count("\n")
        spans.append((start, line))
    return out, spans, n_func, n_asm, n_ext, 0


# How a native function's result reaches a MIPS caller (runtime/mips_interp.c): the i386 ABI leaves the upper bits of
# eax undefined for a char / short result, the R3000 code the game was compiled to extends it in $v0.  0 = 32 bits,
# 1 = u8, 2 = s8, 3 = u16, 4 = s16, 5 = void.
NARROW = {"u8": 1, "unsigned char": 1, "char": 1, "s8": 2, "signed char": 2, "M2C_UNK8": 2, "u16": 3,
          "unsigned short": 3, "unsigned short int": 3, "s16": 4, "short": 4, "signed short": 4, "short int": 4,
          "M2C_UNK16": 4, "void": 5}


def ret_kind(head, name):
    m = re.search(r"\b%s\s*\(" % re.escape(name), head)
    if not m:
        return 0
    t = head[:m.start()]
    t = re.sub(r"/\*.*?\*/", " ", t, flags=re.S)
    t = re.sub(r"\b(static|inline|extern|__inline__|__inline|const|volatile|register)\b", " ", t)
    t = t.strip().split("\n")[-1].strip() if "*" not in t else "*"
    t = " ".join(t.split())
    return NARROW.get(t, 0)


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


TYPE_WORDS = {"void", "int", "char", "short", "long", "unsigned", "signed", "u8", "s8", "u16", "s16", "u32", "s32",
              "M2C_UNK", "M2C_UNK8", "M2C_UNK16", "M2C_UNK32"}


def forward_short_calls(body, arity, fixed):
    """Append PORT_ARG(i) to the calls in body that pass fewer arguments than the callee reads."""
    out, i, n = [], 0, 0
    while True:
        m = CALL_RE.search(body, i)
        if not m:
            out.append(body[i:])
            break
        name = m.group(1) or m.group(2)
        # a block-scope prototype (`extern void f();`, `u8 *f();`) is not a call: an identifier right before the
        # name (a type), or a type word and stars (`x * f()` stays a call)
        before = re.search(r"([A-Za-z_]\w*)\s*(\**)\s*$", body[max(0, m.start() - 40):m.start()])
        decl = m.group(2) and before and before.group(1) not in ("return", "case", "else", "do", "sizeof") and \
            (not before.group(2) or before.group(1) in TYPE_WORDS)
        if name not in arity or decl or (m.start() > 0 and body[m.start() - 1] in ".>"):
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

_OTHER = {}
OVL_BASE = 0x80106228          # lowest overlay load address (GAME / DEMO); areas + SOP 0x80108F9C, OPN / CRD 0x8018A000
OVL_END = 0x80200000


_MAIN_BY_ADDR = []
_MAIN_CODE = {}


def code_addrs(syms, funcs):
    """{name: retail address} of every function name the C may use as a value: the program's own (prefixed for an
    overlay), MAIN's (Psy-Q included), and the program's other names for MAIN function addresses."""
    if not _MAIN_CODE:
        ms, mf = retail_syms("main"), func_names("main")
        _MAIN_CODE.update({n: ms[n] for n in mf if n in ms})
    out = dict(_MAIN_CODE)
    main_addrs = set(_MAIN_CODE.values())
    for n in funcs:
        if n in syms:
            out[n] = syms[n]
    for n, a in syms.items():
        if a in main_addrs and n not in out:
            out[n] = a
    return out



def main_arity_by_addr():
    if not _MAIN_BY_ADDR:
        ms = retail_syms("main")
        out = {}
        for dp, _, fs in os.walk(os.path.join(ROOT, "asm", "main")):
            if os.sep + "data" in dp:
                continue
            for f in fs:
                if f.endswith(".s") and f[:-2] in ms:
                    out[ms[f[:-2]]] = asm_arity(os.path.join(dp, f))
        _MAIN_BY_ADDR.append(out)
    return _MAIN_BY_ADDR[0]


def ovl_vram(prog):
    m = re.search(r"vram:\s*0x([0-9A-Fa-f]+)", open(os.path.join(ROOT, "config", prog + ".yaml")).read())
    return int(m.group(1), 16)


def ovl_prefixes(prog, syms):
    """{name: <prog>_name} for every symbol of build/<prog>.elf in the overlay region."""
    return {n: "%s_%s" % (prog, n) for n, a in syms.items()
            if OVL_BASE <= a < OVL_END and re.match(r"[A-Za-z_]\w*$", n) and not n.startswith("__")}



def other_arities(prog):
    """{name: max asm arity} over every program but PROG (overlay functions called from it by name)."""
    if prog not in _OTHER:
        out = {}
        for p in sorted(os.listdir(os.path.join(ROOT, "asm"))):
            if p == prog or not os.path.isdir(os.path.join(ROOT, "asm", p)):
                continue
            for dp, _, fs in os.walk(os.path.join(ROOT, "asm", p)):
                if os.sep + "data" in dp:
                    continue
                for f in fs:
                    if f.endswith(".s"):
                        k = asm_arity(os.path.join(dp, f))
                        if k > out.get(f[:-2], -1):
                            out[f[:-2]] = k
        _OTHER[prog] = out
    return _OTHER[prog]


def forward_indirect_calls(body, nparams, fixed):
    """A call through a function pointer with an empty argument list (`p->fn()`, `M2C_FIELD(a, T (**)(), 0x74)()`)
    relied on $a0-$a3 still holding the caller's own arguments (func_800412CC: `a->update()` with `a` in $a0): pass
    them on (PORT_ARG; extra arguments are harmless under cdecl).  `(*)()` / `(**)()` in a cast type are not calls."""
    n = min(nparams, 4)
    if n <= 0 or "()" not in body:
        return body
    out, i = [], 0
    while True:
        k = body.find("()", i)
        if k < 0:
            out.append(body[i:])
            break
        j = k - 1
        while j >= 0 and body[j].isspace():
            j -= 1
        call = False
        if j >= 0 and body[j] == ")":   # (not `tbl[i]()`: its declared type may say `(void)`)
            d, m = 0, j            # the matching '(' of the group before the "()"
            while m >= 0:
                if body[m] == ")":
                    d += 1
                elif body[m] == "(":
                    d -= 1
                    if d == 0:
                        break
                m -= 1
            inner = body[m + 1:j].strip()
            # (a cast to a `(void)` prototype says the callee takes nothing: `((u8 *(*)(void))func_8007AB20)()`)
            call = m >= 0 and inner != "" and set(inner) - set("* ") != set() and \
                not re.search(r"\(\s*void\s*\)", inner)
        if call:
            out.append(body[i:k] + "(" + ", ".join("PORT_ARG(%d)" % a for a in range(n)) + ")")
            fixed.append("<indirect>")
        else:
            out.append(body[i:k + 2])
        i = k + 2
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
        extra_cpp, prefix = [], {}
        if prog != "main":
            # an overlay: every name it defines in the overlay region gets a `<prog>_` prefix (the overlays share
            # their load addresses, and their names: func_80120308 is a different function in each area), through
            # a header of #defines included before the source; resolution stays by address (link step)
            prefix = ovl_prefixes(prog, syms)
            hdr = os.path.join(outdir, "ovl_%s.h" % prog)
            text = "".join("#define %s %s\n" % (k, v) for k, v in sorted(prefix.items()))
            if not os.path.exists(hdr) or open(hdr).read() != text:
                open(hdr, "w").write(text)
            extra_cpp = ["-include", hdr]
            syms = dict(syms)
            syms.update({v: syms[k] for k, v in prefix.items()})
            funcs = dict(funcs)
            funcs.update({prefix[k]: v for k, v in list(funcs.items()) if k in prefix})
        fptrs = code_addrs(syms, funcs)
        cfiles = sorted(f for f in os.listdir(os.path.join(ROOT, "src", prog)) if f.endswith(".c"))
        for cf in cfiles:
            path = os.path.join(ROOT, "src", prog, cf)
            pre = run(HOST_CPP + extra_cpp + ["-I" + os.path.join(ROOT, "include"),
                                              "-I" + os.path.join(ROOT, "include", "psyq"), path])
            items = split_items(pre)
            rename, drop = set(), set()
            arity = {}
            for dp, _, fs in os.walk(os.path.join(ROOT, "asm", prog)):   # every function, Psy-Q included
                if os.sep + "data" in dp:
                    continue
                for f in fs:
                    if f.endswith(".s"):
                        arity[f[:-2]] = asm_arity(os.path.join(dp, f))
            for k, v in prefix.items():
                if k in arity:
                    arity[v] = arity[k]
            # functions of other programs (the overlays MAIN dispatches to: func_800633B0 calls A01's
            # func_8010ACB8(a) with its own second argument still in $a1): the highest arity of any copy
            for nm, k in other_arities(prog).items():
                if nm not in arity:
                    arity[nm] = k
            if prog != "main":
                # MAIN functions under another name in this overlay's symbols (func_80076D68 for
                # f_AdvanceActorSkeletalAnimation): the arity of the MAIN function at that address
                by_addr = main_arity_by_addr()
                for nm, a in syms.items():
                    if a < OVL_BASE and nm not in arity and a in by_addr:
                        arity[nm] = by_addr[a]
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
                                                               arity, forwarded, fptrs)
                text = '#include "port_prelude.h"\n' + "".join(out)
                errs = host_errors(text, outdir)
                if os.environ.get("GEN_DEBUG"):
                    lines = text.split("\n")
                    for l_, m_ in errs[:10]:
                        print("[gen_t2 debug] %s:%d: %s | %s" % (cf, l_, m_, lines[l_ - 1].strip()[:120]))
                if not errs:
                    break
                for line, msg in errs:
                    m = re.search(r"conflicting types for '(\w+)'|too many arguments to function '(\w+)'", msg)
                    if m:
                        m = re.match(r"(\w+)", m.group(1) or m.group(2))
                    if m:   # (every error line of a renamed name: the rename fixes them all next pass)
                        rename.add(m.group(1))
                        continue
                    k = item_at(spans, line)
                    if k is not None and items[k][0] == "func":
                        drop.add(k)
                    else:
                        print("[gen_t2] %s:%d: %s" % (cf, line, msg))
                # a dropped static helper takes its callers with it (they would call an undefined name)
                gone = {items[k][1] for k in drop if items[k][1] and re.search(r"\bstatic\b", items[k][2])}
                while gone:
                    more = {k for k, it in enumerate(items) if it[0] == "func" and k not in drop and
                            re.search(r"\b(%s)\s*\(" % "|".join(map(re.escape, gone)), it[3])}
                    drop |= more
                    gone = {items[k][1] for k in more if re.search(r"\bstatic\b", items[k][2])}
            else:
                print("[gen_t2] %s: errors left after the fix-up passes" % cf)
            native.extend((prog, n, a, r) for n, a, r in native_tmp)
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
    with open(os.path.join(outdir, "progs.txt"), "w") as f:
        f.write("\n".join(progs) + "\n")
    with open(os.path.join(outdir, "sources.cmake"), "w") as f:
        f.write("set(PORT_GAME_SOURCES\n%s)\n" % "".join("  %s\n" % p for p in files))
    with open(os.path.join(outdir, "native.txt"), "w") as f:
        for prog, name, addr, rk in native:
            f.write("%s %s %s %d\n" % (prog, name, "%08X" % addr if addr is not None else "-", rk))
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
    progs = [l.strip() for l in open(os.path.join(outdir, "progs.txt")) if l.strip()] \
        if os.path.exists(os.path.join(outdir, "progs.txt")) else ["main"]
    ovls = [p for p in progs if p != "main"]
    objs = [l.strip() for l in open(objlist) if l.strip()]
    defined, undef = host_nm(nm, objs)
    syms = retail_syms("main")
    funcs = func_names("main")
    # overlays: their prefixed names, by program (`a01_func_80120308` -> a01's func_80120308)
    psyms, pfuncs, vram = {}, {}, {}
    for p in ovls:
        psyms[p] = retail_syms(p)
        pfuncs[p] = func_names(p)
        vram[p] = ovl_vram(p)
    # names the overlays give to MAIN addresses (their symbol files may name a MAIN datum differently)
    other = {}
    for p in ovls:
        for n, a in psyms[p].items():
            if a < OVL_BASE and n not in syms:
                other.setdefault(n, a)
    by_addr_func = {}
    for name, (lib, pending) in funcs.items():
        if name in syms:
            by_addr_func.setdefault(syms[name], name)
    func_addrs = set(by_addr_func)
    shim_objs = {n for n, (t, o) in defined.items() if "/shims/" in o or "/runtime/" in o}

    def split_prefix(name):
        for p in ovls:
            if name.startswith(p + "_") and name[len(p) + 1:] in psyms[p]:
                return p, name[len(p) + 1:]
        return None, name

    ld, thunks, stubs, data_alias = [], [], [], 0
    for name in sorted(undef - set(defined)):
        if name.startswith("port_") or name in ("etext", "edata", "end") or name.startswith("__") and name not in syms:
            continue                       # runtime tables (funcmap.c), compiler helpers
        if re.match(r"_?\w+@\d+$", name) or name.startswith("_imp__") or name.startswith("__imp_"):
            continue                       # Win32 imports of sys_win32_i386.c (stdcall-decorated names)
        p, base = split_prefix(name)
        if p:
            addr = psyms[p][base]
            is_code = base in pfuncs[p] or base.startswith("func_") or \
                any(base in pfuncs[q] and psyms[q].get(base) == addr for q in ovls)
        else:
            addr = syms.get(name, other.get(name))
            m = ADDR_NAME.match(name)
            if addr is None and m:
                addr = int(m.group(1), 16)
            if addr is None:
                stubs.append(name)
                thunks.append((name, 0))
                continue
            is_code = addr in func_addrs or (name.startswith("func_") and addr >= OVL_BASE) or name in funcs or \
                any(name in pfuncs[q] and psyms[q].get(name) == addr for q in ovls)
        if is_code:
            thunks.append((name, addr))
        else:
            ld.append("%s = 0x%08X;" % (name, addr))
            data_alias += 1
    # data the native C defines that is retail data: the retail image's copy wins
    overridden = 0
    for name, (t, o) in sorted(defined.items()):
        if t not in "DBRC" or "/shims/" in o or "/runtime/" in o:
            continue
        p, base = split_prefix(name)
        if p and base not in pfuncs[p]:
            ld.append("%s = 0x%08X;" % (name, psyms[p][base]))
            overridden += 1
        elif not p and name in syms and name not in funcs:
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
    # funcmap: native functions by retail address (an overlay's with its program and its first two code words, to
    # tell which overlay is resident); libmap: shims by retail address; libaddrs: policy
    bins = {}
    for p in ovls:
        path = os.path.join(ROOT, "build", p + ".bin")
        bins[p] = open(path, "rb").read() if os.path.exists(path) else b""
    native = []
    for line in open(os.path.join(outdir, "native.txt")):
        prog, name, a, rk = line.split()
        if a != "-" and name in defined:
            a = int(a, 16)
            ovl, w0, w1 = 0, 0, 0
            if prog != "main":
                ovl = ovls.index(prog) + 1
                off = a - vram[prog]
                b = bins[prog]
                if 0 <= off and off + 8 <= len(b):
                    w0 = int.from_bytes(b[off:off + 4], "little")
                    w1 = int.from_bytes(b[off + 4:off + 8], "little")
            native.append((a, ovl, name, int(rk), w0, w1))
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
        for a, o, n, rk, w0, w1 in native:
            f.write("extern char %s[];\n" % n)
        for a, n, l, s, p in lib:
            if s:
                f.write("extern char %s[];\n" % s)
        f.write("const PortOvl port_ovls[] = {\n  {\"main\", \"\", 0x80010000u},\n")
        for p in ovls:
            f.write('  {"%s", "BIN/%s.BIN", 0x%08Xu},\n' % (p, p.upper(), vram[p]))
        f.write("};\nconst int port_ovls_count = %d;\n" % (len(ovls) + 1))
        f.write("const PortFunc port_funcmap[] = {\n")
        for a, o, n, rk, w0, w1 in native:
            f.write('  {0x%08X, %s, "%s", %d, %d, 0x%08Xu, 0x%08Xu},\n' % (a, n, n, rk, o, w0, w1))
        f.write("  {0, 0, 0, 0, 0, 0, 0}\n};\nconst int port_funcmap_count = %d;\n" % len(native))
        shims = [(a, n, s) for a, n, l, s, p in lib if s]
        f.write("const PortLib port_libmap[] = {\n")
        for a, n, s in shims:
            f.write('  {0x%08X, %s, "%s"},\n' % (a, s, n))
        f.write("  {0, 0, 0}\n};\nconst int port_libmap_count = %d;\n" % len(shims))
        f.write("const PortLibAddr port_libaddrs[] = {\n")
        for a, n, l, s, p in lib:
            f.write('  {0x%08X, %d, "%s", "%s"},\n' % (a, p, n, l))
        f.write("  {0, 0, 0, 0}\n};\nconst int port_libaddrs_count = %d;\n" % len(lib))
    per = {}
    for a, o, n, rk, w0, w1 in native:
        per[o] = per.get(o, 0) + 1
    rep = ["native functions with a retail address: %d (%s)" % (len(native), ", ".join(
               "%s %d" % ((["main"] + ovls)[o], c) for o, c in sorted(per.items()))),
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

#!/usr/bin/env python3
"""Install hand-written C (a scratch file of matched functions, checked with tools/ccheck.py) into src/<prog>/<prog>.c.

  python3 -I tools/install_c.py FILE.c [--prog main]

Each function replaces its INCLUDE_ASM line; the file's other top-level lines (types, externs, prototypes; not the
#include lines) go just before the first installed function, skipping lines already present in the target. Then the
linked build must be OK (tools/build.py <prog> --no-split), else the target is restored. Types that several programs
need belong in include/*.h instead. Symbols the file names after another program (C copied from an overlay) are
first renamed to this program's names for the addresses the retail bytes give them (tools/nearcopy.py
fix_names(); a D_ address no file labels gets an alias line). A type the target already has (same text up to
layout) is not repeated (moved up when the target defines it further down); one it defines differently is renamed
here (Name_xxxx) and reported. Prototypes are dropped (m2c's argument counts), except those of functions used as
values or defined further down in the target; a call with fewer arguments than a kept prototype or an installed
definition is reported (it would not compile). tools/ccheck.py --no-protos compiles a scratch the same way.
`static inline` helpers go after the declarations (externs, types, prototypes) of the scratch, just above the first
installed function; a helper the target already has (same text) is not repeated (moved up when it is further down),
one it defines differently is renamed (Name_xxxx). K&R definitions (`s32 f(a, b) s32 a; u8 *b; {`) are installed
like the others (a prototype kept for one written further down is `T f();`). On failure the last line is
`NOT INSTALLED: <names> (<reason>)`.
"""
import argparse, hashlib, os, re, subprocess, sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))
import ptsrc

# a function definition header (K&R parameter declarations allowed before its `{`); group 2 is the name
HEAD = r"(?m)^([\w][\w \*]*?\b(%s)\s*\([^;{}]*\)(?:\s*[^;{}()=#]+;)*)\s*\{"


def heads(text, name=r"\w+"):
    """[(name, header text, offset)] of the function definitions in text (K&R ones too)."""
    return [(m.group(2), m.group(1), m.start()) for m in re.finditer(HEAD % name, text)]


def proto_of(header):
    """A prototype from a definition header: the header itself, or `T f();` for a K&R one."""
    h = " ".join(header.split())
    m = re.match(r"(.*?\b\w+)\s*\(([^()]*)\)\s*(.*)$", h)
    if m and m.group(3):      # K&R: parameter declarations follow the parentheses
        return m.group(1) + "();"
    return h + ";"


def non_int_return(p):
    """a prototype line whose return type is not int-like (a pointer, a narrower integer, a struct): a call
    without a declaration would read it as int."""
    m = re.match(r"\s*(?:extern\s+)?(.*?)\b\w+\s*\([^;{}]*\)\s*;\s*$", p.strip())
    if not m:
        return False
    r = " ".join(m.group(1).replace("*", " * ").split())
    return "*" in r or r not in ("", "int", "s32", "u32", "void", "unsigned int", "signed int", "long",
                                 "unsigned long", "unsigned", "signed")


def is_static(seg):
    return ptsrc.strip_comments(seg).strip().startswith("static")


def fail(msg, names):
    print(msg)
    print("NOT INSTALLED: %s (%s)" % (" ".join(names) or "-", msg.strip().splitlines()[0][:120]))
    sys.exit(1)


def norm(s):
    """A declaration's text with comments and layout gone (to compare two copies of a type)."""
    s = " ".join(ptsrc.strip_comments(s).split())
    return re.sub(r"\s*([{}();,\[\]*=])\s*", r"\1", s)


def type_names(s):
    """The names a type declaration defines: its typedef name(s) and its struct / union / enum tag."""
    s = ptsrc.strip_comments(s).strip()
    out = []
    m = re.match(r"(?:typedef\s+)?(?:struct|union|enum)\s+(\w+)\s*\{", s)
    if m:
        out.append(("tag", m.group(1)))
    if s.startswith("typedef"):
        body = re.sub(r"\{.*\}", " ", s, flags=re.S)
        fp = re.findall(r"\(\s*\*\s*(\w+)\s*\)\s*\(", body)
        names = fp or re.findall(r"(\w+)\s*(?:\[[^\]]*\]\s*)*[;,]", body)
        out += [("type", n) for n in names]
    return out


BUILTIN_TYPES = {"void", "char", "short", "int", "long", "float", "double", "signed", "unsigned", "const",
                 "volatile", "register", "struct", "union", "enum", "static", "extern", "inline"}
_HEADER_TYPES = None


def known_types(text):
    """typedef names of the text and of include/*.h (and include/psyq/*.h)."""
    global _HEADER_TYPES
    if _HEADER_TYPES is None:
        _HEADER_TYPES = set()
        import glob
        for h in glob.glob(os.path.join(ROOT, "include", "*.h")) + glob.glob(os.path.join(ROOT, "include", "psyq",
                                                                                          "*.h")):
            for kind, seg in ptsrc.items(ptsrc.strip_comments(open(h, errors="replace").read())):
                _HEADER_TYPES |= {n for k, n in type_names(seg) if k == "type"}
    out = set(_HEADER_TYPES)
    for kind, seg in ptsrc.items(ptsrc.strip_comments(text)):
        out |= {n for k, n in type_names(seg) if k == "type"}
    return out


def unknown_types(decl, known, ret=False):
    """the type names of a parameter list (or of a return type with ret) that are neither C keywords nor typedefs
    in `known` (a `struct X` tag is always fine)."""
    out = []
    parts = [decl] if ret else [x for x in decl.split(",")]
    for part in parts:
        tagged = bool(re.search(r"\b(struct|union|enum)\s+\w+", part))
        part = re.sub(r"\b(struct|union|enum)\s+\w+", " ", part)
        part = re.sub(r"\(\s*\*\s*\w*\s*\)\s*\([^()]*\)", " ", part)      # a function-pointer parameter
        ws = re.findall(r"[A-Za-z_]\w*", part)
        if not ret and (len(ws) > 1 or tagged and ws) and not part.rstrip().endswith("*"):
            ws = ws[:-1]                                     # the parameter's own name
        for w in ws:
            if w not in BUILTIN_TYPES and w not in known and w != "...":
                out.append(w)
    return out


def proto(p):
    """(name, parameter count or None for variadic / unknown) of a prototype line, or None."""
    m = re.match(r"[\w \*]+?\b(\w+)\s*\(([^;{}]*)\)\s*;$", p.strip())
    if not m or p.startswith(("extern", "typedef")):
        return None
    return m.group(1), params(m.group(2))


def params(args):
    a = args.strip()
    if "..." in a or a == "":
        return None    # variadic, or K&R `f()`: any count
    if a == "void":
        return 0
    return a.count(",") + 1


def arg_count(text, i):
    """(argument count, end offset) of the call whose `(` ends just before text[i]."""
    depth, n, empty = 1, 0, True
    while i < len(text) and depth:
        c = text[i]
        if c in "([{":
            depth += 1
        elif c in ")]}":
            depth -= 1
        elif c == "," and depth == 1:
            n += 1
        if depth and not c.isspace():
            empty = False
        i += 1
    return (0 if empty else n + 1), i


def calls(text, name):
    """Argument counts of every call of name in text."""
    return [arg_count(text, m.end())[0] for m in re.finditer(r"\b%s\s*\(" % re.escape(name), text)]


def cast_calls(t, funcs, only=None):
    """Calls of an installed function, after its definition (or a full prototype) in t, that pass another argument
    count than it has (an m2c draft's count, a pass-through dropped) would not compile: each becomes a call through
    a cast to an unprototyped pointer, `((RET (*)())f)(...)`, which compiles to the same `jal f` with the same
    argument promotions as the undeclared call it was. Returns (t, [(name, count)])."""
    done = []
    for n, body in funcs:
        hd = heads(body, re.escape(n))
        if not hd or proto_of(hd[0][1]).endswith("();"):
            continue    # K&R definitions take any argument count
        h = " ".join(hd[0][1].split())
        m = re.match(r"(.*?)\b%s\s*\(([^()]*)\)" % re.escape(n), h)
        k = params(m.group(2)) if m else None
        if not m or k is None:
            continue
        ret = " ".join(re.sub(r"\b(static|inline|extern)\b", " ", m.group(1)).split()) or "int"
        starts = [hm.start() for hm in re.finditer(HEAD % re.escape(n), t)]
        starts += [pm.start() for pm in re.finditer(r"(?m)^(?:extern\s+)?[A-Za-z_][\w \*]*?\b%s\s*\(([^;{}()]*)\)\s*;"
                                                    % re.escape(n), t) if params(pm.group(1)) is not None]
        if not starts:
            continue
        first = min(starts)
        spans = []
        inside = [body_span(t, fn) for fn in only] if only is not None else None
        for cm in re.finditer(r"(?<![\w.>])%s\s*\(" % re.escape(n), t):
            ls = t.rfind("\n", 0, cm.start()) + 1
            if cm.start() <= first or not t[ls:ls + 1].isspace():
                continue    # the definition / a prototype (top level), or before the first declaration
            if inside is not None and not any(sp and sp[0] <= cm.start() < sp[1] for sp in inside):
                continue    # only the calls inside these spans (the bodies just installed)
            c, _ = arg_count(t, cm.end())
            if c != k:
                spans.append((cm.start(), cm.end(), c))
        for a_, b_, c in reversed(spans):
            t = t[:a_] + "((%s (*)())%s)(" % (ret, n) + t[b_:]
        if spans:
            done.append((n, sorted({c for _, _, c in spans}), "((%s (*)())%s)(...)" % (ret, n)))
    return t, done


def body_span(t, name):
    """(start, end) of the definition of name in t (its header to the closing brace at column 0), or None."""
    hd = heads(t, re.escape(name))
    if not hd:
        return None
    end = t.find("\n}", hd[0][2])
    return (hd[0][2], end + 2) if end >= 0 else None


def dedupe_types(old, t):
    """A type name the install left defined twice at top level (it was defined at most once before): identical
    copies (up to layout) keep the first one only; different ones are reported."""
    def defs(text):
        out = {}
        for kind, seg in ptsrc.items(text):
            if kind == "code":
                for tn in type_names(seg):
                    out.setdefault(tn, []).append(seg.strip())
        return out
    before = defs(old)
    seen = set()
    for tn, segs in defs(t).items():
        if len(segs) < 2 or len(before.get(tn, [])) > 1 or tuple(segs) in seen:
            continue
        seen.add(tuple(segs))
        if all(norm(x) == norm(segs[0]) for x in segs[1:]):
            for x in segs[1:]:
                i = t.find(x, t.find(segs[0]) + len(segs[0]))
                if i >= 0:
                    t = t[:i] + t[i + len(x):]
            print("type %s was defined %d times after the install: the later copies removed" % (tn[1], len(segs)))
        else:
            print("warning: %s %s is defined %d times, differently: fix by hand" % (
                "struct tag" if tn[0] == "tag" else "type", tn[1], len(segs)))
    return t


def build_errors(out):
    """The useful lines of a failed tools/build.py run: compiler diagnostics (`file:line: ...`), link errors."""
    keep = [l for l in out.splitlines()
            if re.match(r"\S+:\d+: ", l) or "undefined reference" in l or "multiple definition" in l
            or re.search(r"\b(error|Error)\b", l) and not l.startswith("FAILED")]
    return keep


def link_diff(prog):
    """the first byte where build/<prog>.bin differs from the retail file, as `first difference at 0xADDR
    (FUNC+0xOFF)` from build/<prog>.map, or None."""
    try:
        import libsweep
        retail, delta = libsweep.prog_bytes(prog)
        ours = open(os.path.join(ROOT, "build", prog + ".bin"), "rb").read()
    except (OSError, AttributeError):
        return None
    n = min(len(ours), len(retail))
    off = next((i for i in range(n) if ours[i] != retail[i]), None)
    if off is None:
        return "the linked file is %#x bytes, retail %#x" % (len(ours), len(retail)) if len(ours) != len(retail) \
            else None
    off &= ~3
    addr = off + delta
    syms = []
    mp = os.path.join(ROOT, "build", prog + ".map")
    if os.path.exists(mp):
        for m in re.finditer(r"(?m)^\s+0x([0-9a-f]{8})\s+([A-Za-z_]\w*)\s*$", open(mp).read()):
            syms.append((int(m.group(1), 16), m.group(2)))
    best = max((x for x in syms if x[0] <= addr), default=None)
    at = " (%s+0x%X)" % (best[1], addr - best[0]) if best else ""
    import struct
    return "first difference at 0x%08X%s: ours %08X, retail %08X" % (
        addr, at, struct.unpack("<I", ours[off:off + 4].ljust(4, b"\0"))[0],
        struct.unpack("<I", retail[off:off + 4].ljust(4, b"\0"))[0])


NARROW = re.compile(r"^\s*(const\s+)?(volatile\s+)?(u8|s8|u16|s16|char|short|unsigned char|signed char|"
                    r"unsigned short|signed short|short int|unsigned short int)\s*\w*\s*$")


def narrow_params(p, name):
    """True when the prototype line p of name has a parameter narrower than int (u8 / s16 / char / short, not a
    pointer): with it, every other call in the target converts its argument (andi / sll+sra)."""
    m = re.search(r"\b%s\s*\(([^()]*)\)\s*;" % re.escape(name), p)
    if not m:
        return False
    return any(NARROW.match(x) for x in m.group(1).split(","))


def types_first(extra):
    """the kept declarations with the type definitions (typedef / struct / union / enum) first, each group in its
    own order: a prototype goes after the typedefs it uses."""
    def isty(p):
        q = p.lstrip()
        return q.startswith("typedef") or (q.startswith(("struct", "union", "enum")) and
                                           ("{" in q or re.match(r"(struct|union|enum)\s+\w+\s*;", q)))
    return [p for p in extra if isty(p)] + [p for p in extra if not isty(p)]


def drop_prototypes(text, keep=()):
    """The scratch with its top-level prototypes dropped as install() drops them: kept are the ones of functions
    used as values, defined in the scratch itself or named in keep (functions the target defines)."""
    items = ptsrc.items(text)
    bodies = [s for k, s in items if k == "code" and ptsrc.func_name(s.strip())]
    defined = {ptsrc.func_name(b.strip()) for b in bodies}
    # the dropped segments are cut out of the text itself: ptsrc.items() leaves out the newline after a
    # preprocessor line and a comment above one (the `// CC` set-up lines), so a re-join loses both
    out, pos = [], 0
    for k, seg in items:
        pr = proto(seg.strip()) if k == "code" else None
        if pr and pr[0] not in defined and pr[0] not in keep and \
                not any(re.search(r"\b%s\b(?!\s*\()" % pr[0], b) for b in bodies):
            at = text.find(seg, pos)
            if at >= 0:
                out.append(text[pos:at])
                pos = at + len(seg)
    out.append(text[pos:])
    return "".join(out)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("src")
    ap.add_argument("--prog", default="main")
    a = ap.parse_args()
    if os.environ.get("INSTALL_C_LOCKED") == a.prog:   # the one-at-a-time retries below run under our lock
        return install(a)
    if not os.path.exists(a.src):
        fail("%s: no such file" % a.src, [])
    # one installer per program at a time: the target .c and config/aliases_<prog>.ld are read, changed and maybe
    # restored, so two agents installing into the same program would undo each other's lines
    import fcntl
    os.makedirs(os.path.join(ROOT, "build"), exist_ok=True)
    with open(os.path.join(ROOT, "build", ".install_%s" % a.prog), "w") as lk:
        fcntl.flock(lk, fcntl.LOCK_EX)
        os.environ["INSTALL_C_LOCKED"] = a.prog
        return install(a)


def install(a):
    path = os.path.join(ROOT, "src", a.prog, a.prog + ".c")
    old = open(path).read()
    t = old
    text = open(a.src).read()
    # names another program uses for these addresses -> this program's (relocations read against retail)
    import nearcopy
    text, ren, new_aliases = nearcopy.fix_names(text, a.prog)
    if ren:
        print("renamed from the relocations: " + ", ".join("%s -> %s" % kv for kv in sorted(ren.items())))
    pre, funcs, includes = [], [], []
    for kind, seg in ptsrc.items(text):
        s = seg.strip()
        if not s:
            continue
        if kind == "pp" and s.startswith("#include"):
            s = s.replace('"psyq/inline_c.h"', '"gte.h"')     # the real GTE command words (include/gte.h)
            if s not in t and not re.search(r'"(common|game|m2c)\.h"', s):
                includes.append(s)   # e.g. gte.h for GTE macros, actor.h: goes after the target's own includes
            continue
        # a static (inline) helper goes with the declarations, before the first function that uses it
        n = ptsrc.func_name(s) if s.endswith("}") and not is_static(s) else None
        if n:
            funcs.append((n, s))
        else:
            pre.append(s)
    # m2c's `extern M2C_UNK func_X;` (or `extern s32 func_X;`) for a function the C calls: a function declaration,
    # none at all when the target already declares the function
    body_text = "\n".join(b for _, b in funcs) + "\n".join(x for x in pre if x.startswith("static"))
    for i, p in enumerate(pre):
        m = re.fullmatch(r"extern\s+(?:M2C_UNK|s32|\?)\s+(\w+)\s*;(?:\s*/\*[^*]*\*/)?", p)
        if m and re.search(r"\b%s\s*\(" % m.group(1), body_text):
            k = m.group(1)
            if re.search(r"(?m)^[^\n;{}()]*\b%s\s*\([^;{]*\)\s*[;{]" % k, t):
                pre[i] = ""
                print("extern %s: a function the target declares: declaration dropped" % k)
            else:
                pre[i] = "s32 %s();" % k
                print("extern %s: a function: declared `s32 %s();`" % (k, k))
    pre = [x for x in pre if x]
    # `extern s16 D_a, D_b;`: one declaration per name, so that the clash check below sees each of them
    split_pre = []
    for p in pre:
        m = re.fullmatch(r"(extern\s+(?:(?:volatile|const|unsigned|signed|struct|union|enum)\s+)*\w+)\s+"
                         r"([^;(){}=]+,[^;(){}=]+);", p)
        if m:
            for d in m.group(2).split(","):
                split_pre.append("%s %s;" % (m.group(1), d.strip()))
            print("split `%s` into %d declarations" % (p[:60], len(m.group(2).split(","))))
        else:
            split_pre.append(p)
    pre = split_pre
    # a scratch static helper no installed function (nor another used helper) calls: left out
    used_text = "\n".join(b for _, b in funcs)
    helpers = {ptsrc.func_name(p): p for p in pre if p.endswith("}") and is_static(p) and ptsrc.func_name(p)}
    used, grow = set(), True
    while grow:
        grow = False
        for hn, hp in helpers.items():
            if hn not in used and re.search(r"\b%s\b" % re.escape(hn), used_text):
                used.add(hn)
                used_text += "\n" + hp
                grow = True
    for hn in set(helpers) - used:
        print("unused scratch helper %s: left out" % hn)
        pre.remove(helpers[hn])
    # a macro the target defines with another body: ours is renamed (Name_xxxx), else the target's later
    # #define would silently change what our functions compile to (or ours what the target's code does)
    tmacros = {m.group(1): m.group(2) for m in re.finditer(r"(?m)^#\s*define\s+(\w+)((?:.*\\\n)*.*)$", t)}
    for i, p in enumerate(list(pre)):
        m = re.match(r"#\s*define\s+(\w+)((?:.*\\\n)*.*)$", p, re.S)
        if not m or m.group(1) not in tmacros or norm(m.group(2)) == norm(tmacros[m.group(1)]):
            continue
        k = m.group(1)
        new = "%s_%s" % (k, hashlib.sha1(p.encode()).hexdigest()[:4])
        print("warning: macro %s is defined with another body in the target (`#define %s%s`): renamed %s here" % (
            k, k, tmacros[k].strip()[:60], new))
        pre = [re.sub(r"\b%s\b" % k, new, q) for q in pre]
        funcs = [(fn, re.sub(r"\b%s\b" % k, new, b)) for fn, b in funcs]
    # a global the target declares with another type is used here under an alias name (config/aliases_<prog>.ld)
    import libsweep
    aliases = libsweep.read_aliases(a.prog)
    aliases.update({k: v for k, v in new_aliases.items() if k not in aliases})
    decl_re = r"(?m)^(extern [^;(]*?\b(\w+)(?:\[[^\]]*\])*;)"
    theirs = {m.group(2): m.group(1) for m in re.finditer(decl_re, t)}
    for i, p in enumerate(pre):
        m = re.match(decl_re, p)
        if not m or m.group(2) not in theirs or theirs[m.group(2)] == m.group(1):
            continue
        k = m.group(2)
        am = re.fullmatch(r"(?:D|func)_([0-9A-F]{8})", k)
        adr = int(am.group(1), 16) if am else nearcopy.name_addrs(a.prog).get(k)
        if adr is None:
            fail("%s is declared differently in %s and has no address; rename it by hand" % (k, path),
                 [n for n, _ in funcs])
        # an alias of that address the target already declares the scratch's way is used as is; otherwise a new
        # one, and the target's other names for the address are listed (one of them may be meant)
        same = [n for n, v in aliases.items() if v == adr and n != k and n in theirs]
        fit = [n for n in same if norm(re.sub(r"\b%s\b" % n, k, theirs[n])) == norm(m.group(1))]
        if fit:
            new = fit[0]
            print("extern %s clashes with the target's `%s`: using its alias %s (%s)" % (k, theirs[k], new,
                                                                                          theirs[new]))
        else:
            new = "%s_%s" % (k, hashlib.sha1(p.encode()).hexdigest()[:4])
            aliases[new] = adr
            print("extern %s clashes with the target's `%s`: new alias %s%s" % (
                k, theirs[k], new, "; the target's other names for %08X: %s" % (adr, ", ".join(
                    "%s (%s)" % (n, theirs[n]) for n in same)) if same else ""))
        pre[i] = re.sub(r"\b%s\b" % k, new, p)
        funcs = [(n, re.sub(r"\b%s\b" % k, new, b)) for n, b in funcs]
    ap_ = libsweep.aliases_path(a.prog)
    old_aliases = open(ap_).read() if os.path.exists(ap_) else None

    added = {k: v for k, v in aliases.items() if k not in libsweep.read_aliases(a.prog)}

    def restore_aliases():
        # only the lines this run added go: other lines may have come in meanwhile (merged, never a snapshot)
        cur = libsweep.read_aliases(a.prog)
        for k in added:
            cur.pop(k, None)
        if cur:
            libsweep.write_aliases(a.prog, cur)
        elif old_aliases is None and os.path.exists(ap_):
            os.remove(ap_)
    if added:
        cur = libsweep.read_aliases(a.prog)
        cur.update(added)
        libsweep.write_aliases(a.prog, cur)
    # a function that had equivalent C (tools/nonmatching.py) loses its whole NON_MATCHING block
    for n, _ in funcs:
        line = 'INCLUDE_ASM("asm/%s/nonmatchings/%s", %s);' % (a.prog, a.prog, n)
        t = re.sub(r"(?ms)^#ifdef NON_MATCHING\n(?:(?!^#endif).)*?^#else\n" + re.escape(line) + r"\n#endif$",
                   lambda m: line, t)
    lines = {}
    for n, body in funcs:
        line = 'INCLUDE_ASM("asm/%s/nonmatchings/%s", %s);' % (a.prog, a.prog, n)
        if line not in t:
            fail("%s: no INCLUDE_ASM line for %s" % (path, n), [n for n, _ in funcs])
        lines[n] = (t.index(line), line)
    first = min(lines, key=lambda n: lines[n][0])     # the declarations go before the earliest function in the file
    at = lines[first][0]
    before = t[:at]
    # types: one the target has (same text up to layout) is not repeated, or moves up from further down; one the
    # target defines differently is renamed here (Name_xxxx), never dropped
    tdefs = {}
    for kind, seg in ptsrc.items(t):
        if kind == "code":
            for _, n in type_names(seg):
                tdefs.setdefault(n, seg.strip())
    moved = []
    for i, p in enumerate(list(pre)):
        tn = type_names(p)
        have = [tdefs[n] for _, n in tn if n in tdefs]
        if not have:
            continue
        if all(norm(h) == norm(p) for h in have):
            h = have[0]
            if t.find(h) < at:
                pre[i] = None
            elif h not in moved:
                moved.append(h)
            continue
        for _, n in tn:
            if n in tdefs and norm(tdefs[n]) != norm(p):
                new = "%s_%s" % (n, hashlib.sha1(p.encode()).hexdigest()[:4])
                print("renamed type %s -> %s (the target defines %s differently)" % (n, new, n))
                pre = [re.sub(r"\b%s\b" % n, new, q) if q else q for q in pre]
                funcs = [(fn, re.sub(r"\b%s\b" % n, new, b)) for fn, b in funcs]
    # static helpers: one the target has with the same text is not repeated (moved up from further down), one it
    # defines differently is renamed here
    tfuncs = {}
    for kind, seg in ptsrc.items(t):
        if kind == "code" and seg.strip().endswith("}") and ptsrc.func_name(seg.strip()):
            tfuncs.setdefault(ptsrc.func_name(seg.strip()), seg.strip())
    for i, p in enumerate(list(pre)):
        if not p or not (p.endswith("}") and is_static(p)):
            continue
        hn = ptsrc.func_name(p)
        if hn not in tfuncs:
            continue
        h = tfuncs[hn]
        if norm(h) == norm(p):
            if t.find(h) < at:
                pre[i] = None
            elif h not in moved:
                moved.append(h)
            continue
        new = "%s_%s" % (hn, hashlib.sha1(p.encode()).hexdigest()[:4])
        print("renamed helper %s -> %s (the target defines %s differently)" % (hn, new, hn))
        pre = [re.sub(r"\b%s\b" % hn, new, q) if q else q for q in pre]
        funcs = [(fn, re.sub(r"\b%s\b" % hn, new, b)) for fn, b in funcs]
    pre = [p for p in pre if p]
    for h in moved:     # the target's copy further down goes: ours is inserted above its first use
        t = t.replace(h + "\n", "", 1) if h + "\n" in t else t.replace(h, "", 1)
        print("moved up: " + h.split("\n")[0][:70])
    at = t.index(lines[first][1])
    before = t[:at]
    later = {n for n, _, _ in heads(t[at:])}
    later |= {n for n, _ in funcs if n != first}

    def wanted(p):
        if p in before:
            return False
        # prototypes are left out: the asm drafts call functions with the argument counts m2c saw (pass-through
        # arguments dropped), which a prototype would reject; calls compile the same without one
        pr = proto(p)
        if not pr:
            return True
        # ... unless a function is used as a value (its address taken), which needs a declaration, or the target
        # defines it further down (a call before the definition would declare it `int f()`: conflicting types)
        if pr[0] in later and not heads(before, re.escape(pr[0])):
            return True     # (written as the definition's own header below)
        if non_int_return(p) and not re.search(r"(?m)^[^\n;{}()=]*\b%s\s*\(" % re.escape(pr[0]), t) and \
                any(re.search(r"(?<![\w.>])%s\s*\(" % re.escape(pr[0]), b) for _, b in funcs):
            return True     # an undeclared call would be `int f()`: another return type changes the caller
        return any(re.search(r"\b%s\b(?!\s*\()" % pr[0], b) for _, b in funcs)
    extra = [p for p in pre if wanted(p)]
    for i, p in enumerate(extra):
        pr = proto(p)
        if pr and non_int_return(p) and pr[0] not in later and not heads(t, re.escape(pr[0])):
            # kept for its return type only: K&R, so the drafts' argument counts still compile
            new = re.sub(r"\(([^()]*)\)\s*;\s*$", "();", p.strip())
            if new != p.strip():
                print("prototype %s kept for its return type, K&R: %s" % (pr[0], new))
            extra[i] = new
    # a kept prototype naming a type nobody defines (an m2c guess, a type of another program's file) would not
    # compile: it becomes `T f();` (or `s32 f();` when the return type is the unknown one)
    known = known_types(t + "\n" + "\n".join(q for q in pre if q))
    for i, p in enumerate(extra):
        pr = proto(p)
        if not pr:
            continue
        um = re.match(r"\s*(.*?)\b%s\s*\((.*)\)\s*;\s*$" % re.escape(pr[0]), p, re.S)
        if not um:
            continue
        bad = [w for w in unknown_types(um.group(2), known)]
        rbad = unknown_types(um.group(1), known, ret=True)
        if bad or rbad:
            new = "%s %s();" % ("s32" if rbad else um.group(1).strip(), pr[0])
            print("prototype %s: unknown type %s, declared K&R: %s" % (p.strip(), ", ".join(bad + rbad), new))
            extra[i] = new
    for i, p in enumerate(extra):   # a kept prototype takes the target's definition header: same types for sure
        pr = proto(p)
        if pr and pr[0] in later:
            hd = heads(t[at:] + "\n" + "\n".join(b for _, b in funcs), re.escape(pr[0]))
            if hd and norm(proto_of(hd[0][1])) != norm(p):
                full = proto_of(hd[0][1])
                fm = re.match(r"[^(]*?\b%s\s*\(([^)]*)\)" % re.escape(pr[0]), full)
                k = (params(fm.group(1)) or 0) if fm else 0
                few = [c for c in calls(t, pr[0]) + [c for _, b in funcs for c in calls(b, pr[0])] if c < k]
                if few:
                    # a call with fewer arguments (an m2c draft, a pass-through dropped) would not compile
                    # against the full prototype: keep the K&R declaration with the definition's return type
                    full = re.sub(r"\(([^()]*)\)\s*;\s*$", "();", full)
                    print("prototype of %s from its definition, K&R (calls with %s argument(s)): %s" % (
                        pr[0], "/".join(map(str, sorted(set(few)))), full))
                else:
                    print("prototype of %s from its definition: %s" % (pr[0], full))
                extra[i] = full
    # a prototype or a definition with N parameters makes a call with fewer arguments an error: say where
    sigs = {}
    for p in extra:
        pr = proto(p)
        if pr and pr[1]:
            sigs[pr[0]] = pr[1]
    for n, b in funcs:
        hd = heads(b, re.escape(n))
        m = re.match(r"[^(]*?\b%s\s*\(([^)]*)\)" % re.escape(n), b)
        kr = hd and proto_of(hd[0][1]).endswith("();")      # a K&R definition takes any argument count
        if m and params(m.group(1)) and not kr:
            sigs[n] = params(m.group(1))
    for n, k in sigs.items():
        if n in dict(funcs):
            continue    # calls of an installed function: cast_calls() below
        for where, text_ in [("the target", t)] + [(fn, b) for fn, b in funcs]:
            few = [c for c in calls(text_, n) if c < k]
            if few:
                print("warning: %s calls %s with %s argument(s), the %s has %d" %
                      (where, n, "/".join(map(str, sorted(set(few)))), "prototype" if n not in dict(funcs)
                       else "definition", k))
    # a prototype with a parameter narrower than int (u8 / s16) of a callee the target calls elsewhere and does not
    # define: it would change those other calls (argument conversions): K&R `T f();` instead (round 10 pitfall)
    for i, p in enumerate(extra):
        pr = proto(p)
        if pr and narrow_params(p, pr[0]) and pr[0] not in later and not heads(t, re.escape(pr[0])) and \
                calls(t, pr[0]):
            if re.search(r"(?m)^[^\n;{}()=]*\b%s\s*\([^;{}]*\)\s*;" % re.escape(pr[0]), t):
                print("prototype %s has a parameter narrower than int; the target declares %s already: dropped" % (
                    p.strip(), pr[0]))
                extra[i] = ""
                continue
            new = re.sub(r"\(([^()]*)\)\s*;\s*$", "();", p.strip())
            print("prototype %s has a parameter narrower than int and the target calls %s elsewhere: K&R %s "
                  "(cast at the call if the narrow conversion matters)" % (p.strip(), pr[0], new))
            extra[i] = new
    extra = [p for p in extra if p]
    extra = types_first(extra)
    # static helpers after every declaration (they use the externs / types / prototypes above them)
    extra = [p for p in extra if not (p.endswith("}") and is_static(p))] + \
        [p for p in extra if p.endswith("}") and is_static(p)]
    for p in extra:   # a declaration the file already has further down moves up to the new first use
        if p.startswith(("extern", "typedef", "struct", "union")) and p in t:
            t = t.replace(p + "\n", "", 1) if p + "\n" in t else t.replace(p, "", 1)
    for n, body in funcs:
        if n == first:
            body = "\n".join(extra + ([""] if extra else []) + [body])
        t = t.replace(lines[n][1], body)
    # a prototype the target already has for an installed function (`void f(void);` for one used as a value)
    # with other parameters than the definition: conflicting types; it becomes the definition's header (K&R
    # `T f();` when a call passes fewer arguments)
    for n, body in funcs:
        hd = heads(body, re.escape(n))
        if not hd:
            continue
        want = proto_of(hd[0][1])
        fm = re.match(r"[^(]*?\b%s\s*\(([^)]*)\)" % re.escape(n), want)
        k = (params(fm.group(1)) or 0) if fm else 0
        if k and any(c < k for c in calls(t, n)):
            want = re.sub(r"\(([^()]*)\)\s*;\s*$", "();", want)
        for m in list(re.finditer(r"(?m)^(?:extern\s+)?[A-Za-z_][\w \*]*?\b%s\s*\([^;{}()]*\)\s*;[ \t]*$"
                                  % re.escape(n), t)):
            if norm(m.group(0)) != norm(want) and not re.search(r"\(\s*\)\s*;", m.group(0)):
                t = t.replace(m.group(0), want, 1)
                print("prototype of %s in the target made the definition's: %s -> %s" % (n, m.group(0).strip(),
                                                                                         want))
    t, casted = cast_calls(t, funcs)
    # calls in the installed bodies of a function the target defines (or prototypes in full) before them with
    # another parameter count: through the same cast (they would not compile otherwise)
    inst = {n for n, _ in funcs}
    callees = {c for _, b in funcs for c in re.findall(r"(?<![\w.>])([A-Za-z_]\w*)\s*\(", b)} - inst
    tdef = [(n, h + " {}") for n, h, _ in heads(t) if n in callees]
    if tdef:
        t2, casted2 = cast_calls(t, tdef, only=inst)
        t = t2
        casted += casted2
    for n, cs, form in casted:
        print("calls of %s with %s argument(s) (another count than its definition) go through a cast: %s" % (
            n, "/".join(map(str, cs)), form))
    t = dedupe_types(old, t)
    if includes:   # after the target's last #include line
        last = list(re.finditer(r"(?m)^#include .*$", t))
        at = last[-1].end() if last else 0
        t = t[:at] + "\n" + "\n".join(includes) + t[at:]
    open(path, "w").write(t)
    r = subprocess.run([sys.executable, "tools/build.py", a.prog, "--no-split"], capture_output=True, text=True,
                       cwd=ROOT)
    if " OK " not in r.stdout:
        open(path, "w").write(old)
        restore_aliases()
        errs = build_errors(r.stdout + r.stderr)
        why = "linked build not OK, restored"
        if errs:
            print("the build failed (the target with this C does not compile / link); first lines:")
            print("\n".join("  " + l for l in errs[:12]))
            why = "does not build: %s" % errs[0].strip()
        elif "DIFF" in r.stdout:
            why = "linked build DIFF (compiles, other bytes), restored"
            where = link_diff(a.prog)
            if where:
                print(where)
                why += "; " + where
        if len(funcs) < 2:
            if not errs:
                print(r.stdout + r.stderr[-2500:])
            fail(why, [n for n, _ in funcs])
        # one function at a time: the others may still go in (a callee prototype in the target, for instance,
        # can change one function's code)
        print("linked build not OK with all %d; trying one at a time" % len(funcs))
        segs = ptsrc.items(text)
        done, failed = [], []
        for n, _ in funcs:
            one = "".join(seg for kind, seg in segs
                          if not (seg.strip().endswith("}") and not is_static(seg)
                                  and ptsrc.func_name(seg.strip()) not in (None, n)))
            tmp = os.path.join(ROOT, "build", "install_one.c")
            open(tmp, "w").write(one)
            r = subprocess.run([sys.executable, "-I", os.path.abspath(__file__), tmp, "--prog", a.prog],
                               capture_output=True, text=True, cwd=ROOT)
            (done if "installed" in r.stdout else failed).append(n)
            if n in failed:
                print("  %s: %s" % (n, (r.stdout + r.stderr).strip().splitlines()[-1:]))
        print("installed %d functions: %s" % (len(done), " ".join(done)))
        if (open(ap_).read() if os.path.exists(ap_) else None) != old_aliases:
            print("changed %s: commit config/aliases_%s.ld too" % (os.path.relpath(ap_, ROOT), a.prog))
        if failed:
            fail("%d of %d did not build" % (len(failed), len(funcs)), failed)
        return
    print("installed %d functions: %s" % (len(funcs), " ".join(n for n, _ in funcs)))
    if (open(ap_).read() if os.path.exists(ap_) else None) != old_aliases:
        print("changed %s: commit config/aliases_%s.ld too" % (os.path.relpath(ap_, ROOT), a.prog))


if __name__ == "__main__":
    main()

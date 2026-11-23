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


def calls(text, name):
    """Argument counts of every call of name in text."""
    out = []
    for m in re.finditer(r"\b%s\s*\(" % re.escape(name), text):
        i, depth, n, empty = m.end(), 1, 0, True
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
        out.append(0 if empty else n + 1)
    return out


def drop_prototypes(text, keep=()):
    """The scratch with its top-level prototypes dropped as install() drops them: kept are the ones of functions
    used as values, defined in the scratch itself or named in keep (functions the target defines)."""
    items = ptsrc.items(text)
    bodies = [s for k, s in items if k == "code" and ptsrc.func_name(s.strip())]
    defined = {ptsrc.func_name(b.strip()) for b in bodies}
    out = []
    for k, seg in items:
        pr = proto(seg.strip()) if k == "code" else None
        if pr and pr[0] not in defined and pr[0] not in keep and \
                not any(re.search(r"\b%s\b(?!\s*\()" % pr[0], b) for b in bodies):
            continue
        out.append(seg)
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
            if s not in t and not re.search(r'"(common|game|m2c|actor)\.h"', s):
                includes.append(s)   # e.g. psyq/inline_c.h for GTE macros: goes after the target's own includes
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
        return any(re.search(r"\b%s\b(?!\s*\()" % pr[0], b) for _, b in funcs)
    extra = [p for p in pre if wanted(p)]
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
        for where, text_ in [("the target", t)] + [(fn, b) for fn, b in funcs]:
            few = [c for c in calls(text_, n) if c < k]
            if few:
                print("warning: %s calls %s with %s argument(s), the %s has %d" %
                      (where, n, "/".join(map(str, sorted(set(few)))), "prototype" if n not in dict(funcs)
                       else "definition", k))
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
        if len(funcs) < 2:
            print(r.stdout + r.stderr[-2500:])
            fail("linked build not OK, restored", [n for n, _ in funcs])
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
        if failed:
            fail("%d of %d did not build" % (len(failed), len(funcs)), failed)
        return
    print("installed %d functions: %s" % (len(funcs), " ".join(n for n, _ in funcs)))


if __name__ == "__main__":
    main()

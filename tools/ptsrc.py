"""Library C from psx_tomba (github.com/hansbonini/psx_tomba, MIT per its README; cloned to /tmp/psx_tomba by
tools/setup_native.sh): find the file that defines a Psy-Q function and cut a standalone source for it.

The cut keeps the file's preprocessor lines, types and declarations, turns every other function definition into a
prototype and every global variable definition into an `extern` declaration (the data stays in the asm data
segments), and keeps the one function. Includes are pointed at include/pt (psx_tomba's base headers) and
include/psyq.
"""
import glob, os, re

PT = os.environ.get("PSX_TOMBA", "/tmp/psx_tomba")
_index = None


def strip_comments(t):
    out, i, n = [], 0, len(t)
    while i < n:
        c = t[i]
        if t.startswith("/*", i):
            j = t.find("*/", i + 2); i = n if j < 0 else j + 2; out.append(" "); continue
        if t.startswith("//", i):
            j = t.find("\n", i); i = n if j < 0 else j; continue
        if c in "\"'":
            j = i + 1
            while j < n and t[j] != c:
                j += 2 if t[j] == "\\" else 1
            out.append(t[i:j + 1]); i = j + 1; continue
        out.append(c); i += 1
    return "".join(out)


def items(t):
    """Top-level items: ('pp', line) or ('code', text) split at depth-0 ';' or the '}' closing a function body."""
    out, i, n, start, depth = [], 0, len(t), 0, 0
    while i < n:
        c = t[i]
        if depth == 0 and c == "#" and t[start:i].strip() == "":
            j = t.find("\n", i)
            while j > 0 and t[j - 1] == "\\":
                j = t.find("\n", j + 1)
            j = n if j < 0 else j
            out.append(("pp", t[i:j])); i = start = j; continue
        if c in "\"'":
            j = i + 1
            while j < n and t[j] != c:
                j += 2 if t[j] == "\\" else 1
            i = j + 1; continue
        if c == "{":
            depth += 1
        elif c == "}":
            depth -= 1
            if depth == 0:
                seg = t[start:i + 1]
                head = seg[:seg.find("{")]
                if re.search(r"\)\s*$", head) and "=" not in head:     # a function body ends here
                    out.append(("code", seg)); start = i + 1
        elif c == ";" and depth == 0:
            out.append(("code", t[start:i + 1])); start = i + 1
        i += 1
    return out


KEYWORDS = {"void", "int", "char", "short", "long", "unsigned", "signed", "struct", "union", "enum", "const",
            "volatile", "static", "inline", "register", "extern", "float", "double", "if", "while", "for", "return",
            "sizeof", "switch"}


def func_name(seg):
    """The name a function definition defines (also for functions returning function pointers)."""
    if "{" not in seg:
        return None
    head = seg[:seg.find("{")]
    if not re.search(r"\)\s*$", head) or "=" in head:
        return None
    for m in re.finditer(r"\b([A-Za-z_]\w*)\s*\(", head):
        if m.group(1) not in KEYWORDS:
            return m.group(1)
    return None


def index():
    global _index
    if _index is None:
        _index = {}
        for f in sorted(glob.glob(os.path.join(PT, "src", "psyq", "**", "*.c"), recursive=True)):
            for kind, seg in items(strip_comments(open(f, errors="replace").read())):
                if kind == "code" and seg.rstrip().endswith("}"):
                    n = func_name(seg)
                    if n:
                        _index.setdefault(n, f)
    return _index


def cut(name):
    """Standalone source for `name`, or None when psx_tomba has no C for it."""
    f = index().get(name)
    if not f:
        return None, None
    out = ["#define SKIP_ASM"]
    for kind, seg in items(strip_comments(open(f, errors="replace").read())):
        s = seg.strip()
        if kind == "pp":
            s = re.sub(r'#include\s+"common.h"', '#include "pt/common.h"', s)
            lib = os.path.basename(os.path.dirname(f))
            m = re.match(r'#include\s+"(\w+\.h)"', s)
            if m and os.path.exists(os.path.join(os.path.dirname(f), m.group(1))):   # a header beside the source
                s = '#include "pt/%s/%s"' % (lib, m.group(1))
            out.append(s); continue
        if not s:
            continue
        if s.endswith("}") and func_name(s):
            if func_name(s) == name:
                out.append(re.sub(r"^\s*static\s+", "", s))
            else:
                out.append(re.sub(r"^\s*(static\s+|inline\s+)+", "", s[:s.find("{")]).strip() + ";")
            continue
        # declarations: typedef / struct / enum / prototypes / externs stay; variable definitions become externs
        if re.match(r"(typedef|extern)\b", s) or re.match(r"(struct|union|enum)\s+\w*\s*\{", s) and s.endswith("};"):
            out.append(s); continue
        if re.search(r"\)\s*;$", s) and "=" not in s:                       # a prototype
            out.append(re.sub(r"^\s*(static\s+|inline\s+)+", "", s)); continue
        d = s[:-1]
        depth, cutat = 0, None
        for k, ch in enumerate(d):
            if ch in "({[": depth += 1
            elif ch in ")}]": depth -= 1
            elif ch == "=" and depth == 0:
                cutat = k; break
        if cutat is not None:
            d = d[:cutat]
        d = re.sub(r"^\s*static\s+", "", d).strip()
        d = re.sub(r"\[[^\]]*\]", "[]", d, count=1) if re.search(r"\[[^\]]*\]\s*$", d) else d
        out.append("extern " + d + ";")
    return "\n".join(out) + "\n", os.path.relpath(f, PT)
